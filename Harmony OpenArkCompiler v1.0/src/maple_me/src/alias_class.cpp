/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reserved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 *     http://license.coscl.org.cn/MulanPSL
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v1 for more details.
 */
#include "alias_class.h"
#include "mpl_logging.h"
#include "opcode_info.h"
#include "ssa_mir_nodes.h"
#include "ssa_tab.h"
#include "mir_function.h"
#include "mir_builder.h"

namespace maple {

static inline bool IsReadOnlyOst(const OriginalSt *ost) {
  return (ost == nullptr) ? false : ost->GetMIRSymbol()->HasAddrOfValues();
}

static inline bool IsPotentialAddress(PrimType ptyp) {
  return IsAddress(ptyp) || IsPrimitiveDynType(ptyp);
}

static inline bool OriginalStIsZeroLevAndAuto(const OriginalSt *ost) {
  if (ost->GetIndirectLev() == 0 && ost->IsSymbolOst()) {
    MIRSymbol *sym = ost->GetMIRSymbol();
    return sym->GetStorageClass() == kScAuto || sym->GetStorageClass() == kScFormal;
  }
  return false;
}

bool AliasClass::CallHasNoSideEffectOrPrivateDefEffect(StmtNode *stmt, FuncAttrKind attrKind) {
  ASSERT(attrKind == FUNCATTR_nosideeffect || attrKind == FUNCATTR_noprivate_defeffect, "Not supportted attrKind");
  CallNode *callStmt = dynamic_cast<CallNode*>(stmt);
  if (callStmt == nullptr) {
    return false;
  }
  MIRFunction *callee = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(callStmt->GetPUIdx());
  bool hasAttr = false;
  if (callee->GetFuncAttrs().GetAttr(attrKind)) {
    hasAttr = true;
  } else if (!ignoreIPA) {
    hasAttr = (attrKind == FUNCATTR_nosideeffect) ? callee->IsNoDefEffect() : callee->IsNoPrivateDefEffect();
  }
  return hasAttr;
}

bool AliasClass::CallHasSideEffect(StmtNode *stmt) {
  return calleeHasSideEffect ? true : !CallHasNoSideEffectOrPrivateDefEffect(stmt, FUNCATTR_nosideeffect);
}

bool AliasClass::CallHasNoPrivateDefEffect(StmtNode *stmt) {
  return calleeHasSideEffect ? false : CallHasNoSideEffectOrPrivateDefEffect(stmt, FUNCATTR_noprivate_defeffect);
}

// here starts pass 1 code
AliasElem *AliasClass::FindOrCreateAliasElem(OriginalSt *ost) {
  OStIdx ostIdx = ost->GetIndex();
  CHECK_FATAL(ostIdx.idx > 0 && ostIdx.idx < osym2Elem.size(), "Invalid ost index");
  AliasElem *aelem = osym2Elem[ostIdx.idx];
  if (aelem != nullptr) {
    return aelem;
  }
  aelem = acMemPool->New<AliasElem>(id2Elem.size(), ost);
  if (ost->IsSymbolOst() && ost->GetIndirectLev() >= 0) {
    MIRSymbol *sym = ost->GetMIRSymbol();
    if (sym->IsGlobal() && !sym->HasAddrOfValues() && !sym->GetIsTmp()) {
      globalsMayAffectedByClinitCheck.insert(ostIdx);
      if (!sym->IsReflectionClassInfo()) {
        if (!ost->IsFinal() || InConstructorLikeFunc()) {
          globalsAffectedByCalls.insert(aelem->GetClassID());
        }
        aelem->SetNextLevNotAllDefsSeen(true);
      }
    }
  }
  if (aelem->GetOriginalSt()->IsFormal() || ost->GetIndirectLev() > 0) {
    aelem->SetNextLevNotAllDefsSeen(true);
  }
  id2Elem.push_back(aelem);
  osym2Elem[ostIdx.idx] = aelem;
  unionFind.NewMember();
  return aelem;
}

AliasElem *AliasClass::FindOrCreateExtraLevAliasElem(BaseNode *expr, TyIdx tyIdx, FieldID fieldId) {
  ASSERT(expr != nullptr, "nullptr check");
  AliasElem *ae = CreateAliasElemsExpr(kOpcodeInfo.IsTypeCvt(expr->GetOpCode()) ? expr->Opnd(0) : expr);
  if (ae == nullptr) {
    return nullptr;
  }
  OriginalSt *newOst = GetAliasAnalysisTable()->FindOrCreateExtraLevOriginalSt(ae->GetOriginalSt(), tyIdx, fieldId);
  ASSERT(newOst, "null ptr check");
  if (newOst->GetIndex().idx == osym2Elem.size()) {
    osym2Elem.push_back(nullptr);
    ssaTab->GetVersionStTable().CreateVersionSt(newOst, kInitVersion);
  }
  return FindOrCreateAliasElem(newOst);
}

AliasElem *AliasClass::CreateAliasElemsExpr(BaseNode *expr) {
  ASSERT(expr != nullptr, "nullptr check");
  switch (expr->GetOpCode()) {
    case OP_addrof: {
      AddrofSSANode *addrof = static_cast<AddrofSSANode*>(expr);
      FindOrCreateAliasElem(addrof->GetSSAVar()->GetOrigSt());
      OriginalSt *newost =
          GetAliasAnalysisTable()->FindOrCreateAddrofSymbolOriginalSt(addrof->GetSSAVar()->GetOrigSt());
      if (newost->GetIndex().idx == osym2Elem.size()) {
        osym2Elem.push_back(nullptr);
      }
      return FindOrCreateAliasElem(newost);
    }
    case OP_dread: {
      AddrofSSANode *dread = static_cast<AddrofSSANode*>(expr);
      return FindOrCreateAliasElem(dread->GetSSAVar()->GetOrigSt());
    }
    case OP_regread: {
      RegreadSSANode *rread = static_cast<RegreadSSANode*>(expr);
      return (rread->GetRegIdx() < 0) ? nullptr : FindOrCreateAliasElem(rread->GetSSAVar()->GetOrigSt());
    }
    case OP_iread:
    case OP_iaddrof: {
      IreadNode *iread = static_cast<IreadNode*>(expr);
      return FindOrCreateExtraLevAliasElem(iread->Opnd(0), iread->GetTyIdx(), iread->GetFieldID());
    }
    case OP_malloc:
    case OP_gcmalloc:
      return nullptr;
    case OP_add:
    case OP_sub:
    case OP_array: {
      for (size_t i = 1; i < expr->NumOpnds(); i++) {
        CreateAliasElemsExpr(expr->Opnd(i));
      }
      return CreateAliasElemsExpr(expr->Opnd(0));
    }
    case OP_intrinsicop: {
      IntrinsicopNode *intrn = static_cast<IntrinsicopNode*>(expr);
      if (intrn->GetIntrinsic() == INTRN_JAVA_MERGE && intrn->NumOpnds() == 1 &&
          intrn->GetNopndAt(0)->GetOpCode() == OP_dread) {
        return CreateAliasElemsExpr(intrn->GetNopndAt(0));
      }
      // fall-through
    }
    default:
      for (size_t i = 0; i < expr->NumOpnds(); i++) {
        CreateAliasElemsExpr(expr->Opnd(i));
      }
  }
  return nullptr;
}

// when a mustDef is a pointer, set its pointees' notAllDefsSeen flag to true
void AliasClass::SetNotAllDefsSeenForMustDefs(const StmtNode *callas) {
  MapleVector<MustDefNode> *mustDefs = SSAGenericGetMustDefNode(callas, &ssaTab->GetStmtsSSAPart());
  for (MustDefNode mustDef : *mustDefs) {
    AliasElem *aliasElem = FindOrCreateAliasElem(mustDef.GetResult()->GetOrigSt());
    aliasElem->SetNextLevNotAllDefsSeen(true);
  }
}

void AliasClass::ApplyUnionForDassignCopy(const AliasElem *lhsAe, const AliasElem *rhsAe, const BaseNode *rhs) {
  if (rhsAe == nullptr || rhsAe->GetOriginalSt()->GetIndirectLev() > 0 || rhsAe->IsNotAllDefsSeen()) {
    AliasElem *ae = FindAliasElem(lhsAe->GetOriginalSt());
    ae->SetNextLevNotAllDefsSeen(true);
    return;
  }
  if (!IsPotentialAddress(rhs->GetPrimType()) || HasMallocOpnd(rhs) ||
      (rhs->GetOpCode() == OP_addrof && IsReadOnlyOst(rhsAe->GetOriginalSt()))) {
    return;
  }
  unionFind.Union(lhsAe->GetClassID(), rhsAe->GetClassID());
}

void AliasClass::SetPtrOpndNextLevNADS(const BaseNode *opnd, AliasElem *ae, bool hasNoPrivateDefEffect) {
  if (IsPotentialAddress(opnd->GetPrimType()) && ae != nullptr &&
      !(hasNoPrivateDefEffect && ae->GetOriginalSt()->IsPrivate()) &&
      !(opnd->GetOpCode() == OP_addrof && IsReadOnlyOst(ae->GetOriginalSt()))) {
    ae->SetNextLevNotAllDefsSeen(true);
  }
}

// Set ae of the pointer-type opnds of a call as next_level_not_all_defines_seen
void AliasClass::SetPtrOpndsNextLevNADS(uint start, uint end, MapleVector<BaseNode*> &opnds,
                                        bool hasNoPrivateDefEffect) {
  for (uint i = start; i < end; i++) {
    BaseNode *opnd = opnds[i];
    SetPtrOpndNextLevNADS(opnd, CreateAliasElemsExpr(opnd), hasNoPrivateDefEffect);
  }
}

void AliasClass::ApplyUnionForCopies(StmtNode *stmt) {
  switch (stmt->GetOpCode()) {
    case OP_maydassign:
    case OP_dassign:
    case OP_regassign: {
      // RHS
      ASSERT(stmt->Opnd(0) != nullptr, "nullptr check");
      AliasElem *rhsAe = CreateAliasElemsExpr(stmt->Opnd(0));
      // LHS
      OriginalSt *ost = ssaTab->GetStmtsSSAPart().SSAPartOf(stmt)->GetSSAVar()->GetOrigSt();
      AliasElem *lhsAe = FindOrCreateAliasElem(ost);
      ASSERT(lhsAe != nullptr, "aliaselem of lhs should not be null");
      ApplyUnionForDassignCopy(lhsAe, rhsAe, stmt->Opnd(0));
      return;
    }
    case OP_iassign: {
      IassignNode *iass = static_cast<IassignNode*>(stmt);
      AliasElem *rhsAe = CreateAliasElemsExpr(iass->Opnd(1));
      AliasElem *lhsAe = FindOrCreateExtraLevAliasElem(iass->Opnd(0), iass->GetTyIdx(), iass->GetFieldID());
      ASSERT(lhsAe != nullptr, "aliaselem of lhs should not be null");
      ApplyUnionForDassignCopy(lhsAe, rhsAe, iass->Opnd(1));
      return;
    }
    case OP_throw: {
      SetPtrOpndNextLevNADS(stmt->Opnd(0), CreateAliasElemsExpr(stmt->Opnd(0)), false);
      return;
    }
    case OP_call:
    case OP_callassigned: {
      CallNode *call = static_cast<CallNode*>(stmt);
      ASSERT(call->GetPUIdx() < GlobalTables::GetFunctionTable().GetFuncTable().size(),
            "index out of range in AliasClass::ApplyUnionForCopies");
      SetPtrOpndsNextLevNADS(0, call->NumOpnds(), call->GetNopnd(), false);
      break;
    }
    case OP_icall:
    case OP_icallassigned:
    case OP_virtualcall:
    case OP_virtualicall:
    case OP_superclasscall:
    case OP_interfacecall:
    case OP_interfaceicall:
    case OP_customcall:
    case OP_polymorphiccall:
    case OP_virtualcallassigned:
    case OP_virtualicallassigned:
    case OP_superclasscallassigned:
    case OP_interfacecallassigned:
    case OP_interfaceicallassigned:
    case OP_customcallassigned:
    case OP_polymorphiccallassigned: {
      if (CallHasSideEffect(stmt)) {
        CallNode *call = static_cast<CallNode*>(stmt);
        SetPtrOpndsNextLevNADS(1, call->NumOpnds(), call->GetNopnd(), CallHasNoPrivateDefEffect(call));
      }
      break;
    }
    case OP_intrinsiccall:
    case OP_intrinsiccallassigned: {
      IntrinsiccallNode *innode = static_cast<IntrinsiccallNode*>(stmt);
      if (innode->GetIntrinsic() == INTRN_JAVA_POLYMORPHIC_CALL) {
        SetPtrOpndsNextLevNADS(0, innode->NumOpnds(), innode->GetNopnd(), false);
        break;
      }
      //  fallthrough;
    }
    default:
      for (size_t i = 0; i < stmt->NumOpnds(); i++) {
        CreateAliasElemsExpr(stmt->Opnd(i));
      }
  }
  if (kOpcodeInfo.IsCallAssigned(stmt->GetOpCode())) {
    SetNotAllDefsSeenForMustDefs(stmt);
  }
}

void AliasClass::CreateAssignSets() {
  // iterate through all the alias elems
  for (AliasElem *aliasElem : id2Elem) {
    uint id = aliasElem->GetClassID();
    uint rootID = unionFind.Root(id);
    if (unionFind.GetElementsNumber(rootID) > 1) {
      // only root id's have assignset
      if (id2Elem[rootID]->GetAssignSet() == nullptr) {
        id2Elem[rootID]->SetAssignSet(acMemPool->New<MapleSet<uint>>(std::less<uint>(), acAlloc.Adapter()));
      }
      id2Elem[rootID]->GetAssignSet()->insert(id);
    }
  }
}

void AliasClass::DumpAssignSets() {
  LogInfo::MapleLogger() << "/////// assign sets ///////\n";
  for (AliasElem *aliasElem : id2Elem) {
    if (unionFind.Root(aliasElem->GetClassID()) != aliasElem->GetClassID()) {
      continue;
    }

    if (aliasElem->GetAssignSet() == nullptr) {
      LogInfo::MapleLogger() << "Alone: ";
      aliasElem->Dump(mirModule);
      LogInfo::MapleLogger() << std::endl;
    } else {
      LogInfo::MapleLogger() << "Members of assign set " << aliasElem->GetClassID() << ": ";
      for (uint elemID : *(aliasElem->GetAssignSet())) {
        id2Elem[elemID]->Dump(mirModule);
      }
      LogInfo::MapleLogger() << std::endl;
    }
  }
}

void AliasClass::UnionAllPointedTos() {
  std::vector<AliasElem*> pointedTos;
  for (AliasElem *aliasElem : id2Elem) {
    if (aliasElem->GetOriginalSt()->GetIndirectLev() > 0) {
      aliasElem->SetNotAllDefsSeen(true);
      pointedTos.push_back(aliasElem);
    }
  }
  for (size_t i = 1; i < pointedTos.size(); i++) {
    unionFind.Union(pointedTos[0]->GetClassID(), pointedTos[i]->GetClassID());
  }
}

void AliasClass::UpdateNextLevelNodes(std::vector<OriginalSt*> &nextLevelOsts, const AliasElem &aliasElem) {
  for (uint elemID : *(aliasElem.GetAssignSet())) {
    for (OriginalSt *nextLevelNode : *(GetAliasAnalysisTable()->GetNextLevelNodes(id2Elem[elemID]->GetOriginalSt()))) {
      nextLevelOsts.push_back(nextLevelNode);
    }
  }
}

void AliasClass::UnionNodes(std::vector<OriginalSt*> &nextLevelOsts) {
  for (size_t i = 0; i < nextLevelOsts.size(); i++) {
    OriginalSt *ost1 = nextLevelOsts[i];
    for (size_t j = i + 1; j < nextLevelOsts.size(); j++) {
      OriginalSt *ost2 = nextLevelOsts[j];
      if ((ost1->GetFieldID() == 0 || ost2->GetFieldID() == 0 || ost1->GetFieldID() == ost2->GetFieldID()) &&
          (finalFieldAlias || !(ost1->IsFinal() || ost2->IsFinal()))) {
        unionFind.Union(FindAliasElem(ost1)->GetClassID(), FindAliasElem(ost2)->GetClassID());
        break;
      }
    }
  }
}

// process the union among the pointed's of assignsets
void AliasClass::ApplyUnionForPointedTos() {
  for (AliasElem *aliasElem : id2Elem) {
    if (aliasElem->GetAssignSet() == nullptr) {
      continue;
    }
    // apply union among the assignSet elements
    std::vector<OriginalSt*> nextLevelOsts;
    UpdateNextLevelNodes(nextLevelOsts, *aliasElem);
    UnionNodes(nextLevelOsts);
  }
}

void AliasClass::CollectRootIDOfNextLevelNodes(const OriginalSt *ost, std::set<uint> &rootIDOfNADSs) {
  for (OriginalSt *nextLevelNode : *(GetAliasAnalysisTable()->GetNextLevelNodes(ost))) {
    if (finalFieldAlias || !nextLevelNode->IsFinal()) {
      uint32 id = FindAliasElem(nextLevelNode)->GetClassID();
      rootIDOfNADSs.insert(unionFind.Root(id));
    }
  }
}

void AliasClass::UnionForNotAllDefsSeen() {
  std::set<uint> rootIDOfNADSs;
  for (AliasElem *ae : id2Elem) {
    if (ae->GetAssignSet() == nullptr) {
      if (ae->IsNotAllDefsSeen() || ae->IsNextLevNotAllDefsSeen()) {
        CollectRootIDOfNextLevelNodes(ae->GetOriginalSt(), rootIDOfNADSs);
      }
      continue;
    }
    for (uint elemIdA : *(ae->GetAssignSet())) {
      AliasElem *aeA = id2Elem[elemIdA];
      if (aeA->IsNotAllDefsSeen() || aeA->IsNextLevNotAllDefsSeen()) {
        for (uint elemIdB : *(ae->GetAssignSet())) {
          CollectRootIDOfNextLevelNodes(id2Elem[elemIdB]->GetOriginalSt(), rootIDOfNADSs);
        }
        break;
      }
    }
  }
  if (!rootIDOfNADSs.empty()) {
    uint elemIdA = *(rootIDOfNADSs.begin());
    rootIDOfNADSs.erase(rootIDOfNADSs.begin());
    for (uint elemIdB : rootIDOfNADSs) {
      unionFind.Union(elemIdA, elemIdB);
    }
    for (AliasElem *ae : id2Elem) {
      if (unionFind.Root(ae->GetClassID()) == unionFind.Root(elemIdA)) {
        ae->SetNotAllDefsSeen(true);
      }
    }
  }
}

// fabricate the imaginary not_all_def_seen AliasElem
AliasElem *AliasClass::FindOrCreateDummyNADSAe() {
  MIRSymbol *dummySym = mirModule->GetMIRBuilder()->GetOrCreateSymbol((TyIdx)PTY_i32, "__nads_dummysym__", kStVar,
                                                                      kScGlobal, nullptr, kScopeGlobal, false);
  ASSERT(dummySym != nullptr, "nullptr check");
  dummySym->SetIsTmp(true);
  dummySym->SetIsDeleted();
  OriginalSt *dummyOst = ssaTab->GetOriginalStTable().CreateSymbolOriginalSt(dummySym, 0, 0);
  ssaTab->GetVersionStTable().FindOrCreateVersionSt(dummyOst, kInitVersion);
  if (osym2Elem.size() == dummyOst->GetIndex().idx) {
    AliasElem *dummyAe = acMemPool->New<AliasElem>(osym2Elem.size(), dummyOst);
    dummyAe->SetNotAllDefsSeen(true);
    id2Elem.push_back(dummyAe);
    osym2Elem.push_back(dummyAe);
    unionFind.NewMember();
  }
  return osym2Elem[dummyOst->GetIndex().idx];
}

// TBAA
// Collect the alias groups. Each alias group is a map that maps the rootId to the ids aliasing with the root.
void AliasClass::CollectAliasGroups(std::map<uint, std::set<uint>> &aliasGroups) {
  // key is the root id. The set contains ids of aes that alias with the root.
  for (AliasElem *ae : id2Elem) {
    uint id = ae->GetClassID();
    uint rootID = unionFind.Root(id);
    if (id == rootID) {
      continue;
    }

    if (aliasGroups.find(rootID) == aliasGroups.end()) {
      std::set<uint> idsAliasWithRoot;
      aliasGroups.insert(make_pair(rootID, idsAliasWithRoot));
    }
    aliasGroups[rootID].insert(id);
  }
}

bool AliasClass::AliasAccordingToType(TyIdx tyidxA, TyIdx tyidxB) {
  MIRType *mirTypeA = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyidxA);
  MIRType *mirTypeB = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyidxB);
  if (mirTypeA == mirTypeB || mirTypeA == nullptr || mirTypeB == nullptr) {
    return true;
  }
  if (mirTypeA->GetKind() != mirTypeB->GetKind()) {
    return false;
  }
  switch (mirTypeA->GetKind()) {
    case kTypeScalar: {
      return (mirTypeA->GetPrimType() == mirTypeB->GetPrimType());
    }
    case kTypeClass: {
      Klass *klassA = klassHierarchy->GetKlassFromTyIdx(mirTypeA->GetTypeIndex());
      ASSERT(klassA != nullptr, "null ptr check");
      Klass *klassB = klassHierarchy->GetKlassFromTyIdx(mirTypeB->GetTypeIndex());
      ASSERT(klassB != nullptr, "null ptr check");
      return (klassA == klassB || klassA->GetKlassName() == NameMangler::kJavaLangObjectStr ||
              klassB->GetKlassName() == NameMangler::kJavaLangObjectStr ||
              klassHierarchy->IsSuperKlass(klassA, klassB) || klassHierarchy->IsSuperKlass(klassB, klassA));
    }
    case kTypePointer: {
      MIRType *pointedTypeA = (static_cast<MIRPtrType*>(mirTypeA))->GetPointedType();
      MIRType *pointedTypeB = (static_cast<MIRPtrType*>(mirTypeB))->GetPointedType();
      return AliasAccordingToType(pointedTypeA->GetTypeIndex(), pointedTypeB->GetTypeIndex());
    }
    case kTypeJArray: {
      MIRJarrayType *mirJarrayTypeA = static_cast<MIRJarrayType*>(mirTypeA);
      MIRJarrayType *mirJarrayTypeB = static_cast<MIRJarrayType*>(mirTypeB);
      return AliasAccordingToType(mirJarrayTypeA->GetElemTyIdx(), mirJarrayTypeB->GetElemTyIdx());
    }
    default:
      return true;
  }
}

int AliasClass::GetOffset(const Klass &super, Klass &base) const {
  int offset = 0;
  const Klass *superPtr = &super;
  const Klass *basePtr = &base;
  while (basePtr != superPtr) {
    basePtr = basePtr->GetSuperKlass();
    ASSERT(basePtr != nullptr, "null ptr check");
    offset++;
  }
  return offset;
}

bool AliasClass::AliasAccordingToFieldID(const OriginalSt *ostA, const OriginalSt *ostB) {
  if (ostA->GetFieldID() == 0 || ostB->GetFieldID() == 0) {
    return true;
  }
  MIRType *mirTypeA =
      GlobalTables::GetTypeTable().GetTypeFromTyIdx(GetAliasAnalysisTable()->GetPrevLevelNode(ostA)->GetTyIdx());
  MIRType *mirTypeB =
      GlobalTables::GetTypeTable().GetTypeFromTyIdx(GetAliasAnalysisTable()->GetPrevLevelNode(ostB)->GetTyIdx());
  if (mirTypeA->GetKind() == kTypePointer && mirTypeB->GetKind() == kTypePointer) {
    mirTypeA = (static_cast<MIRPtrType*>(mirTypeA))->GetPointedType();
    mirTypeB = (static_cast<MIRPtrType*>(mirTypeB))->GetPointedType();
  }
  if (mirTypeA->GetKind() != kTypeClass || mirTypeB->GetKind() != kTypeClass) {
    return true;
  }

  Klass *klassA = klassHierarchy->GetKlassFromTyIdx(mirTypeA->GetTypeIndex());
  ASSERT(klassA != nullptr, "null ptr check");
  Klass *klassB = klassHierarchy->GetKlassFromTyIdx(mirTypeB->GetTypeIndex());
  ASSERT(klassB != nullptr, "null ptr check");
  int offset = 0;
  if (klassHierarchy->IsSuperKlass(klassA, klassB)) {
    offset = GetOffset(*klassA, *klassB);
  } else if (klassHierarchy->IsSuperKlass(klassB, klassA)) {
    offset = -GetOffset(*klassB, *klassA);
  } else {
    return false;
  }
  return ((ostA->GetFieldID() + offset) == ostB->GetFieldID());
}

void AliasClass::ProcessIdsAliasWithRoot(const std::set<uint> &idsAliasWithRoot, std::vector<uint> &newGroups) {
  for (uint idA : idsAliasWithRoot) {
    bool unioned = false;
    for (uint idB : newGroups) {
      OriginalSt *ostA = id2Elem[idA]->GetOriginalSt();
      OriginalSt *ostB = id2Elem[idB]->GetOriginalSt();
      if (AliasAccordingToType(GetAliasAnalysisTable()->GetPrevLevelNode(ostA)->GetTyIdx(),
                               GetAliasAnalysisTable()->GetPrevLevelNode(ostB)->GetTyIdx()) &&
          AliasAccordingToFieldID(ostA, ostB)) {
        unionFind.Union(idA, idB);
        unioned = true;
        break;
      }
    }
    if (!unioned) {
      newGroups.push_back(idA);
    }
  }
}

void AliasClass::ReconstructAliasGroups() {
  // map the root id to the set contains the ae-id that alias with the root.
  std::map<uint, std::set<uint>> aliasGroups;
  CollectAliasGroups(aliasGroups);
  unionFind.Reinit();
  // kv.first is the root id. kv.second is the id the alias with the root.
  for (auto oneGroup : aliasGroups) {
    std::vector<uint> newGroups;  // contains one id of each new alias group.
    uint rootId = oneGroup.first;
    std::set<uint> idsAliasWithRoot = oneGroup.second;
    newGroups.push_back(rootId);
    ProcessIdsAliasWithRoot(idsAliasWithRoot, newGroups);
  }
}

void AliasClass::CollectNotAllDefsSeenAes() {
  for (AliasElem *ae : id2Elem) {
    if (ae->IsNotAllDefsSeen() && ae->GetClassID() == unionFind.Root(ae->GetClassID())) {
      notAllDefsSeenClassSetRoots.push_back(ae);
    }
  }
}

void AliasClass::CreateClassSets() {
  // iterate through all the alias elems
  for (AliasElem *aliasElem : id2Elem) {
    uint id = aliasElem->GetClassID();
    uint rootID = unionFind.Root(id);
    if (unionFind.GetElementsNumber(rootID) > 1) {
      if (id2Elem[rootID]->GetClassSet() == nullptr) {
        id2Elem[rootID]->SetClassSet(acMemPool->New<MapleSet<uint>>(std::less<uint>(), acAlloc.Adapter()));
      }
      aliasElem->SetClassSet(id2Elem[rootID]->GetClassSet());
      aliasElem->GetClassSet()->insert(id);
    }
  }
  CollectNotAllDefsSeenAes();
#if DEBUG
  for (AliasElem *aliasElem : id2Elem) {
    if (aliasElem->GetClassSet() != nullptr && aliasElem->IsNotAllDefsSeen() == false &&
        unionFind.Root(aliasElem->GetClassID()) == aliasElem->GetClassID()) {
      ASSERT(aliasElem->GetClassSet()->size() == unionFind.GetElementsNumber(aliasElem->GetClassID()),
             "AliasClass::CreateClassSets: wrong result");
    }
  }
#endif
}

void AliasElem::Dump(MIRModule *mod) const {
  if (ost) {
    ost->Dump();
  }
  LogInfo::MapleLogger() << "id" << id << ((notAllDefsSeen) ? "? " : " ");
}

void AliasClass::DumpClassSets() {
  LogInfo::MapleLogger() << "/////// class sets ///////\n";
  for (AliasElem *aliaselem : id2Elem) {
    if (unionFind.Root(aliaselem->GetClassID()) != aliaselem->GetClassID()) {
      continue;
    }

    if (aliaselem->GetClassSet() == nullptr) {
      LogInfo::MapleLogger() << "Alone: ";
      aliaselem->Dump(mirModule);
      LogInfo::MapleLogger() << std::endl;
    } else {
      LogInfo::MapleLogger() << "Members of alias class " << aliaselem->GetClassID() << ": ";
      for (uint elemID : *(aliaselem->GetClassSet())) {
        id2Elem[elemID]->Dump(mirModule);
      }
      LogInfo::MapleLogger() << std::endl;
    }
  }
}

// here starts pass 2 code
void AliasClass::InsertMayUseExpr(BaseNode *expr) {
  for (size_t i = 0; i < expr->NumOpnds(); i++) {
    InsertMayUseExpr(expr->Opnd(i));
  }
  if (expr->GetOpCode() != OP_iread) {
    return;
  }
  AliasElem *rhsAe = CreateAliasElemsExpr(expr);
  if (rhsAe == nullptr) {
    rhsAe = FindOrCreateDummyNADSAe();
  }
  IreadSSANode *ireadNode = static_cast<IreadSSANode*>(expr);
  ireadNode->GetMayUse().SetOpnd(
      ssaTab->GetVersionStTable().GetVersionStFromID(rhsAe->GetOriginalSt()->GetZeroVersionIndex()));
  ASSERT(ireadNode->GetMayUse().GetOpnd() != nullptr, "AliasClass::InsertMayUseExpr(): iread cannot have empty mayuse");
}

// collect the mayUses caused by globalsAffectedByCalls.
void AliasClass::CollectMayUseFromGlobalsAffectedByCalls(std::set<OriginalSt*> &mayUseOsts) {
  for (uint elemID : globalsAffectedByCalls) {
    mayUseOsts.insert(id2Elem[elemID]->GetOriginalSt());
  }
}

// collect the mayUses caused by not_all_def_seen_ae(NADS).
void AliasClass::CollectMayUseFromNADS(std::set<OriginalSt*> &mayUseOsts) {
  for (AliasElem *notAllDefsSeenAE : notAllDefsSeenClassSetRoots) {
    if (notAllDefsSeenAE->GetClassSet() == nullptr) {
      // single mayUse
      mayUseOsts.insert(notAllDefsSeenAE->GetOriginalSt());
    } else {
      for (uint elemID : *(notAllDefsSeenAE->GetClassSet())) {
        AliasElem *ae = id2Elem[elemID];
        if (!OriginalStIsZeroLevAndAuto(ae->GetOriginalSt())) {
          mayUseOsts.insert(ae->GetOriginalSt());
        }
      }
    }
  }
}

// insert the ost of mayUseOsts into mayUseNodes
void AliasClass::InsertMayUseNode(std::set<OriginalSt*> &mayUseOsts, MapleMap<OStIdx, MayUseNode> *mayUseNodes) {
  for (OriginalSt *ost : mayUseOsts) {
    mayUseNodes->insert(std::make_pair(
        ost->GetIndex(), MayUseNode(ssaTab->GetVersionStTable().GetVersionStFromID(ost->GetZeroVersionIndex()))));
  }
}

// insert mayUse for Return-statement.
// two kinds of mayUse's are insert into the mayUseNodes:
// 1. mayUses caused by not_all_def_seen_ae;
// 2. mayUses caused by globalsAffectedByCalls.
void AliasClass::InsertMayUseReturn(const StmtNode *stmt) {
  std::set<OriginalSt*> mayUseOsts;
  // 1. collect mayUses caused by not_all_def_seen_ae.
  CollectMayUseFromNADS(mayUseOsts);
  // 2. collect mayUses caused by globals_affected_by_call.
  CollectMayUseFromGlobalsAffectedByCalls(mayUseOsts);
  MapleMap<OStIdx, MayUseNode> *mayUseNodes = SSAGenericGetMayUseNode(stmt, &ssaTab->GetStmtsSSAPart());
  InsertMayUseNode(mayUseOsts, mayUseNodes);
}

// collect next_level_nodes of the ost of ReturnOpnd into mayUseOsts
void AliasClass::CollectPtsToOfReturnOpnd(const OriginalSt *ost, std::set<OriginalSt*> &mayUseOsts) {
  for (OriginalSt *nextLevelOst : *(GetAliasAnalysisTable()->GetNextLevelNodes(ost))) {
    AliasElem *indAe = FindAliasElem(nextLevelOst);
    if (!indAe->IsNotAllDefsSeen() && (!indAe->GetOriginalSt()->IsFinal() || finalFieldAlias)) {
      if (indAe->GetClassSet() == nullptr) {
        mayUseOsts.insert(indAe->GetOriginalSt());
      } else {
        for (uint elemID : *(indAe->GetClassSet())) {
          mayUseOsts.insert(id2Elem[elemID]->GetOriginalSt());
        }
      }
    }
  }
}

// insert mayuses at a return stmt caused by its return operand being a pointer
void AliasClass::InsertReturnOpndMayUse(const StmtNode *stmt) {
  if (stmt != nullptr && stmt->GetOpCode() == OP_return && stmt->NumOpnds() != 0) {
    // insert mayuses for the return operand's next level
    BaseNode *retv = stmt->Opnd(0);
    AliasElem *ae = CreateAliasElemsExpr(retv);
    if (IsPotentialAddress(retv->GetPrimType()) && ae != nullptr && !ae->IsNextLevNotAllDefsSeen() &&
        !(retv->GetOpCode() == OP_addrof && IsReadOnlyOst(ae->GetOriginalSt()))) {
      std::set<OriginalSt*> mayUseOsts;
      if (ae->GetAssignSet() == nullptr) {
        CollectPtsToOfReturnOpnd(ae->GetOriginalSt(), mayUseOsts);
      } else {
        for (uint elemID : *(ae->GetAssignSet())) {
          CollectPtsToOfReturnOpnd(id2Elem[elemID]->GetOriginalSt(), mayUseOsts);
        }
      }
      // insert mayUses
      MapleMap<OStIdx, MayUseNode> *mayUseNodes = SSAGenericGetMayUseNode(stmt, &ssaTab->GetStmtsSSAPart());
      InsertMayUseNode(mayUseOsts, mayUseNodes);
    }
  }
}

void AliasClass::InsertMayUseAll(const StmtNode *stmt) {
  MapleMap<OStIdx, MayUseNode> *mayUseNodes = SSAGenericGetMayUseNode(stmt, &ssaTab->GetStmtsSSAPart());
  for (AliasElem *ae : id2Elem) {
    if (ae->GetOriginalSt() != nullptr && ae->GetOriginalSt()->GetIndirectLev() >= 0 &&
        !ae->GetOriginalSt()->IsPregOst()) {
      mayUseNodes->insert(std::make_pair(
          ae->GetOriginalSt()->GetIndex(),
          MayUseNode(ssaTab->GetVersionStTable().GetVersionStFromID(ae->GetOriginalSt()->GetZeroVersionIndex()))));
    }
  }
}

void AliasClass::CollectMayDefForDassign(const StmtNode *stmt, std::set<OriginalSt*> &mayDefOsts) {
  MayDefPartWithVersionSt *theSSAPart =
      static_cast<MayDefPartWithVersionSt*>(ssaTab->GetStmtsSSAPart().SSAPartOf(stmt));
  AliasElem *lhsAe = osym2Elem.at(theSSAPart->GetSSAVar()->GetOrigIdx().idx);
  ASSERT(lhsAe != nullptr, "aliaselem of lhs should not be null");
  if (lhsAe->GetClassSet() != nullptr) {
    for (uint elemID : *(lhsAe->GetClassSet())) {
      if (elemID != lhsAe->GetClassID()) {
        OriginalSt *ostOfAliasAE = id2Elem[elemID]->GetOriginalSt();
        if (ostOfAliasAE->GetTyIdx() == lhsAe->GetOriginalSt()->GetMIRSymbol()->GetTyIdx()) {
          mayDefOsts.insert(ostOfAliasAE);
        }
      }
    }
  }
}

void AliasClass::InsertMayDefNode(std::set<OriginalSt*> &mayDefOsts, MapleMap<OStIdx, MayDefNode> *mayDefNodes,
                                  StmtNode *stmt, BBId bbID) {
  for (OriginalSt *mayDefOst : mayDefOsts) {
    mayDefNodes->insert(std::make_pair(
        mayDefOst->GetIndex(),
        MayDefNode(ssaTab->GetVersionStTable().GetVersionStFromID(mayDefOst->GetZeroVersionIndex()), stmt)));
  }
}

void AliasClass::InsertMayDefDassign(StmtNode *stmt, BBId bbID) {
  std::set<OriginalSt*> mayDefOsts;
  CollectMayDefForDassign(stmt, mayDefOsts);
  MapleMap<OStIdx, MayDefNode> *mayDefNodes = SSAGenericGetMayDefNodes(stmt, &ssaTab->GetStmtsSSAPart());
  InsertMayDefNode(mayDefOsts, mayDefNodes, stmt, bbID);
}

void AliasClass::CollectMayDefForIassign(StmtNode *stmt, std::set<OriginalSt*> &mayDefOsts) {
  IassignNode *iass = static_cast<IassignNode*>(stmt);
  AliasElem *baseAe = CreateAliasElemsExpr(iass->Opnd(0));
  AliasElem *lhsAe = nullptr;
  if (baseAe != nullptr) {
    // get the next-level-ost that will be assigned to
    OriginalSt *lhsOst = nullptr;
    for (OriginalSt *nextLevelNode : *(GetAliasAnalysisTable()->GetNextLevelNodes(baseAe->GetOriginalSt()))) {
      if (nextLevelNode->GetFieldID() == iass->GetFieldID()) {
        lhsOst = nextLevelNode;
        break;
      }
    }
    ASSERT(lhsOst != nullptr, "AliasClass::InsertMayUseExpr: cannot find next level ost");
    lhsAe = osym2Elem[lhsOst->GetIndex().idx];
  } else {
    lhsAe = FindOrCreateDummyNADSAe();
  }
  // lhsAe does not alias with any ae
  if (lhsAe->GetClassSet() == nullptr) {
    mayDefOsts.insert(lhsAe->GetOriginalSt());
    return;
  }
  for (uint elemID : *(lhsAe->GetClassSet())) {
    AliasElem *aliasElem = id2Elem[elemID];
    OriginalSt *ostOfAliasAE = aliasElem->GetOriginalSt();
    if (aliasElem != lhsAe && OriginalStIsZeroLevAndAuto(ostOfAliasAE)) {
      continue;
    }
    mayDefOsts.insert(ostOfAliasAE);
  }
}

void AliasClass::InsertMayDefNodeExcludeFinalOst(std::set<OriginalSt*> &mayDefOsts,
                                                 MapleMap<OStIdx, MayDefNode> *mayDefNodes, StmtNode *stmt, BBId bbID) {
  for (OriginalSt *mayDefOst : mayDefOsts) {
    if (!mayDefOst->IsFinal()) {
      mayDefNodes->insert(std::make_pair(
          mayDefOst->GetIndex(),
          MayDefNode(ssaTab->GetVersionStTable().GetVersionStFromID(mayDefOst->GetZeroVersionIndex()), stmt)));
    }
  }
}

void AliasClass::InsertMayDefIassign(StmtNode *stmt, BBId bbID) {
  std::set<OriginalSt*> mayDefOsts;
  CollectMayDefForIassign(stmt, mayDefOsts);
  MapleMap<OStIdx, MayDefNode> *mayDefNodes = SSAGenericGetMayDefNodes(stmt, &ssaTab->GetStmtsSSAPart());
  if (mayDefNodes == nullptr) {
    return;
  }
  if (mayDefOsts.size() == 1) {
    InsertMayDefNode(mayDefOsts, mayDefNodes, stmt, bbID);
  } else {
    InsertMayDefNodeExcludeFinalOst(mayDefOsts, mayDefNodes, stmt, bbID);
  }
  ASSERT(!mayDefNodes->empty(), "AliasClass::InsertMayUseIassign(): iassign cannot have empty maydef");
}

void AliasClass::InsertMayDefUseSyncOps(StmtNode *stmt, BBId bbID) {
  std::set<uint> aliasSet;
  // collect the full alias set first
  for (size_t i = 0; i < stmt->NumOpnds(); i++) {
    BaseNode *addrBase = stmt->Opnd(i);
    if (addrBase->GetOpCode() == OP_addrof || addrBase->GetOpCode() == OP_dread ||
        addrBase->GetOpCode() == OP_regread) {
      OriginalSt *ost = (addrBase->GetOpCode() == OP_regread)
                            ? static_cast<RegreadSSANode*>(addrBase)->GetSSAVar()->GetOrigSt()
                            : static_cast<AddrofSSANode*>(addrBase)->GetSSAVar()->GetOrigSt();
      if (addrBase->GetOpCode() != OP_addrof) {
        // addrBase->op == OP_dread or OP_regread
        for (OriginalSt *nextLevelOst : *(GetAliasAnalysisTable()->GetNextLevelNodes(ost))) {
          AliasElem *opndAE = osym2Elem[nextLevelOst->GetIndex().idx];
          if (opndAE->GetClassSet() != nullptr) {
            aliasSet.insert(opndAE->GetClassSet()->cbegin(), opndAE->GetClassSet()->cend());
          }
        }
      }
    } else {
      for (AliasElem *notAllDefsSeenAE : notAllDefsSeenClassSetRoots) {
        if (notAllDefsSeenAE->GetClassSet() != nullptr) {
          aliasSet.insert(notAllDefsSeenAE->GetClassSet()->cbegin(), notAllDefsSeenAE->GetClassSet()->cend());
        } else if (notAllDefsSeenAE->GetOriginalSt() != nullptr) {
          aliasSet.insert(notAllDefsSeenAE->GetClassID());
        }
      }
    }
  }
  // do the insertion according to aliasSet
  MayDefMayUsePart *theSSAPart = static_cast<MayDefMayUsePart*>(ssaTab->GetStmtsSSAPart().SSAPartOf(stmt));
  for (uint elemid : aliasSet) {
    AliasElem *aliasElem = id2Elem[elemid];
    OriginalSt *ostOfAliasAE = aliasElem->GetOriginalSt();
    if (!ostOfAliasAE->IsFinal() && !OriginalStIsZeroLevAndAuto(ostOfAliasAE)) {
      OStIdx ostIdx = ostOfAliasAE->GetIndex();
      VersionSt *vst0 = ssaTab->GetVersionStTable().GetVersionStFromID(ostOfAliasAE->GetZeroVersionIndex());
      theSSAPart->GetMayUseNodes().insert(std::make_pair(ostIdx, MayUseNode(vst0)));
      theSSAPart->GetMayDefNodes().insert(std::make_pair(ostIdx, MayDefNode(vst0, stmt)));
    }
  }
}

// collect mayDefs caused by mustDefs
void AliasClass::CollectMayDefForMustDefs(const StmtNode *stmt, std::set<OriginalSt*> &mayDefOsts) {
  MapleVector<MustDefNode> *mustDefs = SSAGenericGetMustDefNode(stmt, &ssaTab->GetStmtsSSAPart());
  for (MustDefNode mustDef : *mustDefs) {
    VersionSt *vst = mustDef.GetResult();
    OriginalSt *ost = vst->GetOrigSt();
    AliasElem *lhsAe = osym2Elem[ost->GetIndex().idx];
    if (lhsAe->GetClassSet() == nullptr || lhsAe->IsNotAllDefsSeen()) {
      continue;
    }
    for (uint elemID : *(lhsAe->GetClassSet())) {
      AliasElem *ae = id2Elem[elemID];
      if (elemID != lhsAe->GetClassID() &&
          ae->GetOriginalSt()->GetTyIdx() == lhsAe->GetOriginalSt()->GetMIRSymbol()->GetTyIdx()) {
        mayDefOsts.insert(ae->GetOriginalSt());
      }
    }
  }
}

void AliasClass::CollectMayUseForCallOpnd(const StmtNode *stmt, std::set<OriginalSt*> &mayUseOsts) {
  for (size_t i = 0; i < stmt->NumOpnds(); i++) {
    BaseNode *expr = stmt->Opnd(i);
    InsertMayUseExpr(expr);

    if (!IsPotentialAddress(expr->GetPrimType())) {
      continue;
    }

    AliasElem *ae = CreateAliasElemsExpr(expr);
    if (ae == nullptr || ae->IsNextLevNotAllDefsSeen()) {
      continue;
    }

    if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(ae->GetOriginalSt()->GetTyIdx())->PointsToConstString()) {
      continue;
    }

    for (OriginalSt *nextLevelOst : *(GetAliasAnalysisTable()->GetNextLevelNodes(ae->GetOriginalSt()))) {
      AliasElem *indAe = FindAliasElem(nextLevelOst);

      if (indAe->GetOriginalSt()->IsFinal() && !finalFieldAlias) {
        continue;
      }

      if (indAe->GetClassSet() == nullptr) {
        mayUseOsts.insert(indAe->GetOriginalSt());
      } else {
        for (uint elemID : *(indAe->GetClassSet())) {
          mayUseOsts.insert(id2Elem[elemID]->GetOriginalSt());
        }
      }
    }
  }
}

void AliasClass::InsertMayDefNodeForCall(std::set<OriginalSt*> &mayDefOsts, MapleMap<OStIdx, MayDefNode> *mayDefNodes,
                                         StmtNode *stmt, BBId bbID, bool hasNoPrivateDefEffect) {
  for (OriginalSt *mayDefOst : mayDefOsts) {
    if (!hasNoPrivateDefEffect || !mayDefOst->IsPrivate()) {
      mayDefNodes->insert(std::make_pair(
          mayDefOst->GetIndex(),
          MayDefNode(ssaTab->GetVersionStTable().GetVersionStFromID(mayDefOst->GetZeroVersionIndex()), stmt)));
    }
  }
}

// Insert mayDefs and mayUses for the callees.
// Four kinds of mayDefs and mayUses are inserted, which are caused by callee
// opnds, not_all_def_seen_ae, globalsAffectedByCalls, and mustDefs.
void AliasClass::InsertMayDefUseCall(StmtNode *stmt, BBId bbID, bool hasSideEffect, bool hasNoPrivateDefEffect) {
  MayDefMayUsePart *theSSAPart = static_cast<MayDefMayUsePart*>(ssaTab->GetStmtsSSAPart().SSAPartOf(stmt));
  std::set<OriginalSt*> mayDefUseOstsA;
  // 1. collect mayDefs and mayUses caused by callee-opnds
  CollectMayUseForCallOpnd(stmt, mayDefUseOstsA);
  // 2. collect mayDefs and mayUses caused by not_all_def_seen_ae
  CollectMayUseFromNADS(mayDefUseOstsA);
  InsertMayUseNode(mayDefUseOstsA, &(theSSAPart->GetMayUseNodes()));
  // insert may def node, if the callee has side-effect.
  if (hasSideEffect) {
    InsertMayDefNodeForCall(mayDefUseOstsA, &(theSSAPart->GetMayDefNodes()), stmt, bbID, hasNoPrivateDefEffect);
  }
  // 3. insert mayDefs and mayUses caused by globalsAffectedByCalls
  std::set<OriginalSt*> mayDefUseOstsB;
  CollectMayUseFromGlobalsAffectedByCalls(mayDefUseOstsB);
  InsertMayUseNode(mayDefUseOstsB, &(theSSAPart->GetMayUseNodes()));
  // insert may def node, if the callee has side-effect.
  if (hasSideEffect) {
    InsertMayDefNodeExcludeFinalOst(mayDefUseOstsB, &(theSSAPart->GetMayDefNodes()), stmt, bbID);
    if (kOpcodeInfo.IsCallAssigned(stmt->GetOpCode())) {
      // 4. insert mayDefs caused by the mustDefs
      std::set<OriginalSt*> mayDefOstsC;
      CollectMayDefForMustDefs(stmt, mayDefOstsC);
      InsertMayDefNodeExcludeFinalOst(mayDefOstsC, &(theSSAPart->GetMayDefNodes()), stmt, bbID);
    }
  }
}

void AliasClass::InsertMayUseNodeExcludeFinalOst(const std::set<OriginalSt*> &mayUseOsts,
                                                 MapleMap<OStIdx, MayUseNode> *mayUseNodes) {
  for (OriginalSt *mayUseOst : mayUseOsts) {
    if (!mayUseOst->IsFinal()) {
      mayUseNodes->insert(
          std::make_pair(mayUseOst->GetIndex(),
                         MayUseNode(ssaTab->GetVersionStTable().GetVersionStFromID(mayUseOst->GetZeroVersionIndex()))));
    }
  }
}

// Insert mayDefs and mayUses for intrinsiccall.
// Four kinds of mayDefs and mayUses are inserted, which are caused by callee
// opnds, not_all_def_seen_ae, globalsAffectedByCalls, and mustDefs.
void AliasClass::InsertMayDefUseIntrncall(StmtNode *stmt, BBId bbID) {
  MayDefMayUsePart *theSSAPart = static_cast<MayDefMayUsePart*>(ssaTab->GetStmtsSSAPart().SSAPartOf(stmt));
  IntrinsiccallNode *intrinNode = static_cast<IntrinsiccallNode*>(stmt);
  IntrinDesc *intrinDesc = &IntrinDesc::intrinTable[intrinNode->GetIntrinsic()];
  std::set<OriginalSt*> mayDefUseOsts;
  // 1. collect mayDefs and mayUses caused by not_all_defs_seen_ae
  CollectMayUseFromNADS(mayDefUseOsts);
  // 2. collect mayDefs and mayUses caused by globalsAffectedByCalls
  CollectMayUseFromGlobalsAffectedByCalls(mayDefUseOsts);
  InsertMayUseNodeExcludeFinalOst(mayDefUseOsts, &(theSSAPart->GetMayUseNodes()));
  if (!intrinDesc->HasNoSideEffect() || calleeHasSideEffect) {
    InsertMayDefNodeExcludeFinalOst(mayDefUseOsts, &(theSSAPart->GetMayDefNodes()), stmt, bbID);
  }
  if (kOpcodeInfo.IsCallAssigned(stmt->GetOpCode())) {
    // 3. insert maydefs caused by the mustdefs
    std::set<OriginalSt*> mayDefOsts;
    CollectMayDefForMustDefs(stmt, mayDefOsts);
    InsertMayDefNodeExcludeFinalOst(mayDefOsts, &(theSSAPart->GetMayDefNodes()), stmt, bbID);
  }
}

void AliasClass::InsertMayDefUseClinitCheck(IntrinsiccallNode *stmt, BBId bbID) {
  MayDefMayUsePart *theSSAPart = static_cast<MayDefMayUsePart*>(ssaTab->GetStmtsSSAPart().SSAPartOf(stmt));
  for (OStIdx ostIdx : globalsMayAffectedByClinitCheck) {
    AliasElem *ae = osym2Elem[ostIdx.idx];
    if (ae->GetOriginalSt() != nullptr) {
      OriginalSt *ostOfAE = ae->GetOriginalSt();
      std::string typeNameOfOst = ostOfAE->GetMIRSymbol()->GetName();
      std::string typeNameOfStmt = GlobalTables::GetTypeTable().GetTypeFromTyIdx(stmt->GetTyIdx())->GetName();
      if (typeNameOfOst.find(typeNameOfStmt) != std::string::npos) {
        theSSAPart->GetMayDefNodes().insert(std::make_pair(
            ostOfAE->GetIndex(),
            MayDefNode(ssaTab->GetVersionStTable().GetVersionStFromID(ostOfAE->GetZeroVersionIndex()), stmt)));
      }
    }
  }
  return;
}

void AliasClass::GenericInsertMayDefUse(StmtNode *stmt, BBId bbID) {
  switch (stmt->GetOpCode()) {
    case OP_return: {
      InsertMayUseReturn(stmt);
      // insert mayuses caused by its return operand being a pointer
      InsertReturnOpndMayUse(stmt);
      break;
    }
    case OP_throw: {
      if (mirModule->GetSrcLang() != kSrcLangJs && lessThrowAlias) {
        ASSERT(GetBB(bbID) != nullptr, "GetBB(bbID) is nullptr in AliasClass::GenericInsertMayDefUse");
        if (!GetBB(bbID)->IsGoto()) {
          InsertMayUseReturn(stmt);
        }
        // if the throw is handled as goto, no alias consequence
      } else {
        InsertMayUseAll(stmt);
      }
      break;
    }
    case OP_gosub:
    case OP_retsub: {
      InsertMayUseAll(stmt);
      return;
    }
    case OP_callassigned:
    case OP_virtualcallassigned:
    case OP_virtualicallassigned:
    case OP_superclasscallassigned:
    case OP_interfacecallassigned:
    case OP_interfaceicallassigned:
    case OP_customcallassigned:
    case OP_polymorphiccallassigned:
    case OP_icallassigned:
    case OP_call:
    case OP_virtualcall:
    case OP_virtualicall:
    case OP_superclasscall:
    case OP_interfacecall:
    case OP_interfaceicall:
    case OP_customcall:
    case OP_polymorphiccall:
    case OP_icall: {
      InsertMayDefUseCall(stmt, bbID, CallHasSideEffect(stmt), CallHasNoPrivateDefEffect(stmt));
      return;
    }
    case OP_intrinsiccallwithtype: {
      IntrinsiccallNode *innode = static_cast<IntrinsiccallNode*>(stmt);
      if (innode->GetIntrinsic() == INTRN_JAVA_CLINIT_CHECK) {
        InsertMayDefUseClinitCheck(innode, bbID);
      }
      InsertMayDefUseIntrncall(stmt, bbID);
      break;
    }
    case OP_intrinsiccall:
    case OP_xintrinsiccall:
    case OP_intrinsiccallassigned:
    case OP_xintrinsiccallassigned:
    case OP_intrinsiccallwithtypeassigned: {
      InsertMayDefUseIntrncall(stmt, bbID);
      break;
    }
    case OP_maydassign:
    case OP_dassign: {
      InsertMayDefDassign(stmt, bbID);
      break;
    }
    case OP_iassign: {
      InsertMayDefIassign(stmt, bbID);
      break;
    }
    case OP_syncenter:
    case OP_syncexit:
      InsertMayDefUseSyncOps(stmt, bbID);
    // fall-through
    default:
      break;
  }
  for (size_t i = 0; i < stmt->NumOpnds(); ++i) {
    InsertMayUseExpr(stmt->Opnd(i));
  }
}

}  // namespace maple
