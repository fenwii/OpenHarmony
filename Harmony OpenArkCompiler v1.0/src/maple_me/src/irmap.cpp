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
#include "irmap.h"
#include <queue>
#include "ssa_mir_nodes.h"
#include "ssa.h"
#include "mir_builder.h"

namespace maple {
// recursively invoke itself in a pre-order traversal of the dominator tree of
// the CFG to build the HSSA representation for the code in each BB
void IRMap::BuildBB(BB *bb, std::vector<bool> &bbIRMapProcessed) {
  if (bb == nullptr) {
    return;
  }
  BBId bbid = bb->GetBBId();
  if (bbIRMapProcessed[bbid.idx]) {
    return;
  }
  bbIRMapProcessed[bbid.idx] = true;
  curBB = bb;
  SetCurFunction(bb);
  // iterate phi list to update the definition by phi
  BuildPhiMeNode(bb);
  if (!bb->IsEmpty()) {
    for (auto &stmt : bb->GetStmtNodes()) {
      MeStmt *meStmt = BuildMeStmt(&stmt);
      bb->AddMeStmtLast(meStmt);
    }
  }
  // travesal bb's dominated tree
  ASSERT(bbid.idx < dom->GetDomChildrenSize(), " index out of range in IRMap::BuildBB");
  const MapleSet<BBId> &domChildren = dom->GetDomChildren(bbid.idx);
  for (auto bbit = domChildren.begin(); bbit != domChildren.end(); bbit++) {
    BBId childbbid = *bbit;
    BuildBB(GetBB(childbbid), bbIRMapProcessed);
  }
}

void IRMap::BuildPhiMeNode(BB *bb) {
  for (auto phi : bb->GetPhiList()) {
    OriginalSt *origst = phi.first;
    VersionSt *verSt = phi.second.GetResult();
    if (origst->IsPregOst()) {
      MeRegPhiNode *phimenode = NewInPool<MeRegPhiNode>();
      RegMeExpr *medef = GetOrCreateRegFromVerSt(verSt);
      phimenode->UpdateLHS(medef);
      phimenode->SetDefBB(bb);
      // build phi operands
      for (VersionSt *opnd : phi.second.GetPhiOpns()) {
        phimenode->GetOpnds().push_back(GetOrCreateRegFromVerSt(opnd));
      }
      bb->GetMeregphiList().insert(std::make_pair(medef->GetOstIdx(), phimenode));
    } else {
      MeVarPhiNode *phimenode = NewInPool<MeVarPhiNode>();
      VarMeExpr *medef = GetOrCreateVarFromVerSt(verSt);
      phimenode->UpdateLHS(medef);
      phimenode->SetDefBB(bb);
      // build phi operands
      for (VersionSt *opnd : phi.second.GetPhiOpns()) {
        phimenode->GetOpnds().push_back(GetOrCreateVarFromVerSt(opnd));
      }
      bb->GetMevarPhiList().insert(std::make_pair(medef->GetOStIdx(), phimenode));
    }
  }
}

VarMeExpr *IRMap::CreateVarMeExprVersion(const VarMeExpr *origExpr) {
  VarMeExpr *varmeexpr = New<VarMeExpr>(exprID++, origExpr->GetOStIdx(), verst2MeExprTable.size());
  verst2MeExprTable.push_back(varmeexpr);
  varmeexpr->InitBase(origExpr->GetOp(), origExpr->GetPrimType(), origExpr->GetNumOpnds());
  varmeexpr->SetFieldID(origExpr->GetFieldID());
  return varmeexpr;
}

MeExpr *IRMap::CreateAddrofMeExpr(MeExpr *expr) {
  if (expr->GetMeOp() == kMeOpVar) {
    VarMeExpr *varmeexpr = static_cast<VarMeExpr*>(expr);
    AddrofMeExpr addrofme(kInvalidExprID, varmeexpr->GetOStIdx());
    addrofme.SetOp(OP_addrof);
    addrofme.SetPtyp(PTY_ptr);
    return HashMeExpr(&addrofme);
  } else {
    ASSERT(expr->GetMeOp() == kMeOpIvar, "expecting IVarMeExpr");
    IvarMeExpr *ivarexpr = static_cast<IvarMeExpr*>(expr);
    OpMeExpr opmeexpr(kInvalidExprID);
    opmeexpr.SetFieldID(ivarexpr->GetFieldID());
    opmeexpr.SetTyIdx(ivarexpr->GetTyIdx());
    opmeexpr.SetOpnd(0, ivarexpr->GetBase());
    opmeexpr.SetOp(OP_iaddrof);
    opmeexpr.SetPtyp(PTY_ref);
    opmeexpr.SetNumOpnds(1);
    return HashMeExpr(&opmeexpr);
  }
}

VarMeExpr *IRMap::CreateNewGlobalTmp(GStrIdx strIdx, PrimType ptyp) {
  MIRSymbol *st =
      mirModule->GetMIRBuilder()->CreateSymbol((TyIdx)ptyp, strIdx, kStVar, kScGlobal, nullptr, kScopeGlobal);
  st->SetIsTmp(true);
  OriginalSt *oSt = ssaTab->CreateSymbolOriginalSt(st, 0, 0);
  VarMeExpr *varx = New<VarMeExpr>(exprID++, oSt->GetIndex(), oSt->GetZeroVersionIndex());
  varx->InitBase(OP_dread, ptyp, 0);
  return varx;
}

VarMeExpr *IRMap::CreateNewLocalRefVarTmp(GStrIdx strIdx, TyIdx tIdx) {
  MIRSymbol *st =
      mirModule->GetMIRBuilder()->CreateSymbol(tIdx, strIdx, kStVar, kScAuto, mirModule->CurFunction(), kScopeLocal);
  st->SetInstrumented();
  OriginalSt *oSt = ssaTab->CreateSymbolOriginalSt(st, mirModule->CurFunction()->GetPuidx(), 0);
  oSt->SetZeroVersionIndex(verst2MeExprTable.size());
  verst2MeExprTable.push_back(nullptr);
  oSt->GetVersionsIndex().push_back(oSt->GetZeroVersionIndex());
  VarMeExpr *newlocalrefvar = New<VarMeExpr>(exprID++, oSt->GetIndex(), verst2MeExprTable.size());
  verst2MeExprTable.push_back(newlocalrefvar);
  newlocalrefvar->InitBase(OP_dread, PTY_ref, 0);
  return newlocalrefvar;
}

RegMeExpr *IRMap::CreateRegMeExprVersion(const OriginalSt *pregOrgst) {
  RegMeExpr *regreadexpr =
      NewInPool<RegMeExpr>(exprID++, pregOrgst->GetPregIdx(), pregOrgst->GetPuIdx(), pregOrgst->GetIndex(), 0);
  regreadexpr->InitBase(OP_regread, pregOrgst->GetMIRPreg()->GetPrimType(), 0);
  regMeExprTable.push_back(regreadexpr);
  return regreadexpr;
}

RegMeExpr *IRMap::CreateRegMeExprVersion(const RegMeExpr *origExpr) {
  RegMeExpr *regreadexpr =
      NewInPool<RegMeExpr>(exprID++, origExpr->GetRegIdx(), origExpr->GetPuIdx(), origExpr->GetOstIdx(), 0);
  regreadexpr->InitBase(origExpr->GetOp(), origExpr->GetPrimType(), origExpr->GetNumOpnds());
  regMeExprTable.push_back(regreadexpr);
  return regreadexpr;
}

RegMeExpr *IRMap::CreateRefRegMeExpr(MIRSymbol *mirSt) {
  MIRFunction *mirfunc = mirModule->CurFunction();
  MIRType *sttype = mirSt->GetType();
  PrimType ptyp = sttype->GetPrimType();
  ASSERT(ptyp == PTY_ref || ptyp == PTY_ptr, "only PTY_ref or PTY_ptr");
  PregIdx regidx = mirfunc->GetPregTab()->CreateRefPreg(sttype);
  ASSERT(regidx <= 0xffff, "register oversized");
  MIRPreg *preg = mirfunc->GetPregTab()->PregFromPregIdx(regidx);
  if (!mirSt->IgnoreRC()) {
    preg->SetNeedRC();
  }
  OriginalSt *oSt = ssaTab->GetOriginalStTable().CreatePregOriginalSt(regidx, mirfunc->GetPuidx());
  RegMeExpr *regreadexpr = NewInPool<RegMeExpr>(exprID++, regidx, mirfunc->GetPuidx(), oSt->GetIndex(), 0);
  regreadexpr->InitBase(OP_regread, ptyp, 0);
  regMeExprTable.push_back(regreadexpr);
  return regreadexpr;
}

RegMeExpr *IRMap::CreateRegMeExpr(PrimType ptyp) {
  MIRFunction *mirfunc = mirModule->CurFunction();
  PregIdx regidx = mirfunc->GetPregTab()->CreatePreg(ptyp);
  ASSERT(regidx <= 0xffff, "register oversized");
  OriginalSt *oSt = ssaTab->GetOriginalStTable().CreatePregOriginalSt(regidx, mirfunc->GetPuidx());
  RegMeExpr *regreadexpr = NewInPool<RegMeExpr>(exprID++, regidx, mirfunc->GetPuidx(), oSt->GetIndex(), 0);
  regreadexpr->InitBase(OP_regread, ptyp, 0);
  regMeExprTable.push_back(regreadexpr);
  return regreadexpr;
}

RegMeExpr *IRMap::CreateRegRefMeExpr(MIRType *mirType) {
  MIRFunction *mirfunc = mirModule->CurFunction();
  PregIdx regidx = mirfunc->GetPregTab()->CreateRefPreg(mirType);
  ASSERT(regidx <= 0xffff, "register oversized");
  OriginalSt *oSt = ssaTab->GetOriginalStTable().CreatePregOriginalSt(regidx, mirfunc->GetPuidx());
  RegMeExpr *regreadexpr = NewInPool<RegMeExpr>(exprID++, regidx, mirfunc->GetPuidx(), oSt->GetIndex(), 0);
  regreadexpr->InitBase(OP_regread, mirType->GetPrimType(), 0);
  regMeExprTable.push_back(regreadexpr);
  return regreadexpr;
}

RegMeExpr *IRMap::CreateRegRefMeExpr(MeExpr *meExpr) {
  MIRType *mirType = nullptr;
  switch (meExpr->GetMeOp()) {
    case kMeOpVar: {
      VarMeExpr *varmeexpr = static_cast<VarMeExpr*>(meExpr);
      OriginalSt *oSt = ssaTab->GetOriginalStFromID(varmeexpr->GetOStIdx());
      ASSERT(oSt->GetTyIdx() != 0, "expect oSt->tyIdx to be initialized");
      mirType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(oSt->GetTyIdx());
      break;
    }
    case kMeOpIvar: {
      IvarMeExpr *ivarmeexpr = static_cast<IvarMeExpr*>(meExpr);
      MIRType *ptrmirtype = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ivarmeexpr->GetTyIdx());
      ASSERT(ptrmirtype->GetKind() == kTypePointer, "must be point type for ivar");
      MIRPtrType *realmirtype = static_cast<MIRPtrType*>(ptrmirtype);
      FieldID fieldID = ivarmeexpr->GetFieldID();
      if (fieldID > 0) {
        mirType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(realmirtype->GetPointedTyIdxWithFieldID(fieldID));
      } else {
        mirType = realmirtype->GetPointedType();
      }
      ASSERT(mirType->GetPrimType() == meExpr->GetPrimType() ||
             !(IsAddress(mirType->GetPrimType()) && IsAddress(meExpr->GetPrimType())),
             "inconsistent type");
      ASSERT(mirType->GetPrimType() == PTY_ref, "CreateRegRefMeExpr: only ref type expected");
      break;
    }
    case kMeOpOp:
      if (meExpr->GetOp() == OP_retype) {
        OpMeExpr *opmeexpr = static_cast<OpMeExpr*>(meExpr);
        ASSERT(opmeexpr->GetTyIdx() != 0, "expect opmeexpr->tyIdx to be initialized");
        mirType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(opmeexpr->GetTyIdx());
        break;
      }
    // fall thru
    default:
      return CreateRegMeExpr(PTY_ptr);
  }
  return CreateRegRefMeExpr(mirType);
}

VarMeExpr *IRMap::GetOrCreateVarFromVerSt(const VersionSt *verSt) {
  size_t vindex = verSt->GetIndex();
  ASSERT(vindex < verst2MeExprTable.size(), "GetOrCreateVarFromVerSt: index %d is out of range", vindex);
  MeExpr *meExpr = verst2MeExprTable.at(vindex);
  if (meExpr != nullptr) {
    return static_cast<VarMeExpr*>(meExpr);
  }
  OriginalSt *oSt = verSt->GetOrigSt();
  ASSERT(oSt->IsSymbolOst(), "GetOrCreateVarFromVerSt: wrong ost_type");
  VarMeExpr *varx = New<VarMeExpr>(exprID++, oSt->GetIndex(), vindex);
  ASSERT(!GlobalTables::GetTypeTable().GetTypeTable().empty(), "container check");
  varx->InitBase(OP_dread, GlobalTables::GetTypeTable().GetTypeFromTyIdx(oSt->GetTyIdx())->GetPrimType(), 0);
  varx->SetFieldID(oSt->GetFieldID());
  verst2MeExprTable[vindex] = varx;
  return varx;
}

VarMeExpr *IRMap::GetOrCreateZeroVersionVarMeExpr(OriginalSt *oSt) {
  ASSERT(oSt->GetZeroVersionIndex() < verst2MeExprTable.size(),
         "GetOrCreateZeroVersionVarMeExpr: version index of osym's kInitVersion out of range");
  if (oSt->GetZeroVersionIndex() == 0) {
    oSt->SetZeroVersionIndex(verst2MeExprTable.size());
    verst2MeExprTable.push_back(nullptr);
  }
  if (verst2MeExprTable[oSt->GetZeroVersionIndex()] == nullptr) {
    VarMeExpr *varmeexpr = New<VarMeExpr>(exprID++, oSt->GetIndex(), oSt->GetZeroVersionIndex());
    varmeexpr->SetFieldID(oSt->GetFieldID());
    varmeexpr->SetOp(OP_dread);
    ASSERT(!GlobalTables::GetTypeTable().GetTypeTable().empty(), "container check");
    varmeexpr->SetPtyp(GlobalTables::GetTypeTable().GetTypeFromTyIdx(oSt->GetTyIdx())->GetPrimType());
    varmeexpr->SetNumOpnds(0);
    verst2MeExprTable[oSt->GetZeroVersionIndex()] = varmeexpr;
    return varmeexpr;
  }
  return static_cast<VarMeExpr*>(verst2MeExprTable[oSt->GetZeroVersionIndex()]);
}

RegMeExpr *IRMap::GetOrCreateRegFromVerSt(const VersionSt *verSt) {
  size_t vindex = verSt->GetIndex();
  ASSERT(vindex < verst2MeExprTable.size(), " GetOrCreateRegFromVerSt: index %d is out of range", vindex);
  MeExpr *meExpr = verst2MeExprTable[vindex];
  if (meExpr != nullptr) {
    return static_cast<RegMeExpr*>(meExpr);
  }
  OriginalSt *oSt = verSt->GetOrigSt();
  ASSERT(oSt->IsPregOst(), "GetOrCreateRegFromVerSt: PregOST expected");
  RegMeExpr *regx =
      NewInPool<RegMeExpr>(exprID++, oSt->GetPregIdx(), mirModule->CurFunction()->GetPuidx(), oSt->GetIndex(), vindex);
  regx->InitBase(OP_regread, oSt->GetMIRPreg()->GetPrimType(), 0);
  regMeExprTable.push_back(regx);
  verst2MeExprTable[vindex] = regx;
  return regx;
}

MeExpr *IRMap::BuildLHSVar(const VersionSt *verSt, DassignMeStmt *defMeStmt, DassignNode *dassign) {
  VarMeExpr *medef = GetOrCreateVarFromVerSt(verSt);
  medef->SetDefStmt(defMeStmt);
  medef->SetDefBy(kDefByStmt);
  verst2MeExprTable.at(verSt->GetIndex()) = medef;
  return medef;
}

MeExpr *IRMap::BuildLHSReg(const VersionSt *verSt, RegassignMeStmt *defMeStmt, const RegassignNode *regassign) {
  RegMeExpr *medef = GetOrCreateRegFromVerSt(verSt);
  medef->SetPtyp(regassign->GetPrimType());
  medef->SetDefStmt(defMeStmt);
  medef->SetDefBy(kDefByStmt);
  verst2MeExprTable.at(verSt->GetIndex()) = medef;
  return medef;
}

IvarMeExpr *IRMap::BuildLHSIvar(MeExpr *baseAddr, IassignMeStmt *iassignMeStmt, FieldID fieldID) {
  IvarMeExpr *medef = New<IvarMeExpr>(exprID++);
  medef->SetFieldID(fieldID);
  medef->SetTyIdx(iassignMeStmt->GetTyIdx());
  medef->SetBase(baseAddr);
  medef->SetDefStmt(iassignMeStmt);
  medef->SetOp(OP_iread);
  medef->SetPtyp(iassignMeStmt->GetRHS()->GetPrimType());
  PutToBucket(medef->GetHashIndex() % mapHashLength, medef);
  return medef;
}

IvarMeExpr *IRMap::BuildLHSIvarFromIassMeStmt(IassignMeStmt *iassignMeStmt) {
  return BuildLHSIvar(iassignMeStmt->GetLHSVal()->GetBase(), iassignMeStmt, iassignMeStmt->GetLHSVal()->GetFieldID());
}

// build Me chilist from MayDefNode list
void IRMap::BuildChiList(MeStmt *meStmt, MapleMap<OStIdx, MayDefNode> &mayDefNodes,
                         MapleMap<OStIdx, ChiMeNode*> &outList) {
  for (auto it = mayDefNodes.begin(); it != mayDefNodes.end(); it++) {
    MayDefNode &maydefnode = it->second;
    VersionSt *opndst = maydefnode.GetOpnd();
    VersionSt *resst = maydefnode.GetResult();
    ChiMeNode *chimestmt = New<ChiMeNode>(meStmt);
    chimestmt->SetRHS(GetOrCreateVarFromVerSt(opndst));
    VarMeExpr *lhs = GetOrCreateVarFromVerSt(resst);
    lhs->SetDefBy(kDefByChi);
    lhs->SetDefChi(chimestmt);
    chimestmt->SetLHS(lhs);
    outList.insert(std::make_pair(lhs->GetOStIdx(), chimestmt));
  }
}

void IRMap::BuildMustDefList(MeStmt *meStmt, MapleVector<MustDefNode> &mustdeflist,
                             MapleVector<MustDefMeNode> &mustdefList) {
  for (auto it = mustdeflist.begin(); it != mustdeflist.end(); it++) {
    MustDefNode &mustdefnode = *it;
    VersionSt *verSt = mustdefnode.GetResult();
    VarMeExpr *lhs = GetOrCreateVarFromVerSt(verSt);
    ASSERT(lhs->GetMeOp() == kMeOpReg || lhs->GetMeOp() == kMeOpVar, "unexpected opcode");
    mustdefList.push_back(MustDefMeNode(lhs, meStmt));
  }
}

MeStmt *IRMap::BuildMeStmtWithNoSSAPart(StmtNode *stmt) {
  Opcode op = stmt->GetOpCode();
  switch (op) {
    case OP_jscatch:
    case OP_finally:
    case OP_endtry:
    case OP_cleanuptry:
    case OP_membaracquire:
    case OP_membarrelease:
    case OP_membarstorestore:
    case OP_membarstoreload:
      return New<MeStmt>(stmt);
    case OP_goto:
      return New<GotoMeStmt>(stmt);
    case OP_comment:
      return NewInPool<CommentMeStmt>(stmt);
    case OP_jstry:
      return New<JsTryMeStmt>(stmt);
    case OP_catch:
      return NewInPool<CatchMeStmt>(stmt);
    case OP_brfalse:
    case OP_brtrue: {
      CondGotoNode *condGotoNode = static_cast<CondGotoNode*>(stmt);
      CondGotoMeStmt *condGotoMeStmt = New<CondGotoMeStmt>(stmt);
      condGotoMeStmt->SetOpnd(0, BuildExpr(condGotoNode->Opnd(0)));
      return condGotoMeStmt;
    }
    case OP_try: {
      TryNode *tryNode = static_cast<TryNode*>(stmt);
      TryMeStmt *tryMeStmt = NewInPool<TryMeStmt>(stmt);
      for (size_t i = 0; i < tryNode->GetOffsetsCount(); i++) {
        tryMeStmt->OffsetsPushBack(tryNode->GetOffset(i));
      }
      return tryMeStmt;
    }
    case OP_assertnonnull:
    case OP_eval:
    case OP_free:
    case OP_switch: {
      UnaryStmtNode *unaryStmt = static_cast<UnaryStmtNode*>(stmt);
      UnaryMeStmt *unMeStmt =
          static_cast<UnaryMeStmt*>((op == OP_switch) ? NewInPool<SwitchMeStmt>(stmt) : New<UnaryMeStmt>(stmt));
      unMeStmt->SetOpnd(0, BuildExpr(unaryStmt->Opnd(0)));
      return unMeStmt;
    }
    default:
      CHECK_FATAL(false, "NYI");
  }
}

MeStmt *IRMap::BuildMeStmt(StmtNode *stmt) {
  AccessSSANodes *ssaPart = ssaTab->GetStmtsSSAPart().SSAPartOf(stmt);
  if (ssaPart == nullptr) {
    return BuildMeStmtWithNoSSAPart(stmt);
  }
  Opcode op = stmt->GetOpCode();
  switch (op) {
    case OP_dassign: {
      DassignMeStmt *meStmt = NewInPool<DassignMeStmt>(stmt);
      DassignNode *dassiNode = static_cast<DassignNode*>(stmt);
      meStmt->SetRHS(BuildExpr(dassiNode->GetRHS()));
      VarMeExpr *varlhs = static_cast<VarMeExpr*>(BuildLHSVar(ssaPart->GetSSAVar(), meStmt, dassiNode));
      meStmt->SetLHS(varlhs);
      BuildChiList(meStmt, ssaPart->GetMayDefNodes(), *(meStmt->GetChiList()));
      return meStmt;
    }
    case OP_regassign: {
      RegassignMeStmt *meStmt = New<RegassignMeStmt>(stmt);
      RegassignNode *regNode = static_cast<RegassignNode*>(stmt);
      meStmt->SetRHS(BuildExpr(regNode->Opnd(0)));
      RegMeExpr *regLHS = static_cast<RegMeExpr*>(BuildLHSReg(ssaPart->GetSSAVar(), meStmt, regNode));
      meStmt->SetLHS(regLHS);
      return meStmt;
    }
    case OP_iassign: {
      IassignNode *iasNode = static_cast<IassignNode*>(stmt);
      IassignMeStmt *meStmt = NewInPool<IassignMeStmt>(stmt);
      meStmt->SetTyIdx(iasNode->GetTyIdx());
      meStmt->SetRHS(BuildExpr(iasNode->GetRHS()));
      meStmt->SetLHSVal(BuildLHSIvar(BuildExpr(iasNode->Opnd(0)), meStmt, iasNode->GetFieldID()));
      BuildChiList(meStmt, ssaPart->GetMayDefNodes(), *(meStmt->GetChiList()));
      return meStmt;
    }
    case OP_maydassign: {
      MaydassignMeStmt *meStmt = NewInPool<MaydassignMeStmt>(stmt);
      DassignNode *dassiNode = static_cast<DassignNode*>(stmt);
      meStmt->SetRHS(BuildExpr(dassiNode->GetRHS()));
      meStmt->SetMayDassignSym(ssaPart->GetSSAVar()->GetOrigSt());
      meStmt->SetFieldID(dassiNode->GetFieldID());
      BuildChiList(meStmt, ssaPart->GetMayDefNodes(), *(meStmt->GetChiList()));
      return meStmt;
    }
    case OP_call:
    case OP_virtualcall:
    case OP_virtualicall:
    case OP_superclasscall:
    case OP_interfacecall:
    case OP_interfaceicall:
    case OP_customcall:
    case OP_polymorphiccall:
    case OP_callassigned:
    case OP_virtualcallassigned:
    case OP_virtualicallassigned:
    case OP_superclasscallassigned:
    case OP_interfacecallassigned:
    case OP_interfaceicallassigned:
    case OP_customcallassigned:
    case OP_polymorphiccallassigned: {
      CallMeStmt *callMeStmt = NewInPool<CallMeStmt>(stmt);
      CallNode *intrinNode = static_cast<CallNode*>(stmt);
      callMeStmt->SetPUIdx(intrinNode->GetPUIdx());
      for (size_t i = 0; i < intrinNode->NumOpnds(); i++) {
        callMeStmt->GetOpnds().push_back(BuildExpr(intrinNode->Opnd(i)));
      }
      BuildMuList(ssaPart->GetMayUseNodes(), *(callMeStmt->GetMuList()));
      if (kOpcodeInfo.IsCallAssigned(op)) {
        BuildMustDefList(callMeStmt, ssaPart->GetMustDefNodes(), *(callMeStmt->GetMustDefList()));
      }
      BuildChiList(callMeStmt, ssaPart->GetMayDefNodes(), *(callMeStmt->GetChiList()));
      return callMeStmt;
    }
    case OP_icall:
    case OP_icallassigned:
    case OP_intrinsiccall:
    case OP_xintrinsiccall:
    case OP_intrinsiccallwithtype:
    case OP_intrinsiccallassigned:
    case OP_intrinsiccallwithtypeassigned: {
      NaryMeStmt *naryMeStmt = (op == OP_icall || op == OP_icallassigned)
                                   ? static_cast<NaryMeStmt*>(NewInPool<IcallMeStmt>(stmt))
                                   : static_cast<NaryMeStmt*>(NewInPool<IntrinsiccallMeStmt>(stmt));
      NaryStmtNode *naryStmtNode = static_cast<NaryStmtNode*>(stmt);
      for (size_t i = 0; i < naryStmtNode->NumOpnds(); i++) {
        naryMeStmt->GetOpnds().push_back(BuildExpr(naryStmtNode->Opnd(i)));
      }
      BuildMuList(ssaPart->GetMayUseNodes(), *(naryMeStmt->GetMuList()));
      if (kOpcodeInfo.IsCallAssigned(op)) {
        BuildMustDefList(naryMeStmt, ssaPart->GetMustDefNodes(), *(naryMeStmt->GetMustDefList()));
      }
      BuildChiList(naryMeStmt, ssaPart->GetMayDefNodes(), *(naryMeStmt->GetChiList()));
      return naryMeStmt;
    }
    case OP_return: {
      NaryStmtNode *retStmt = static_cast<NaryStmtNode*>(stmt);
      RetMeStmt *meStmt = NewInPool<RetMeStmt>(stmt);
      for (size_t i = 0; i < retStmt->NumOpnds(); i++) {
        meStmt->GetOpnds().push_back(BuildExpr(retStmt->Opnd(i)));
      }
      BuildMuList(ssaPart->GetMayUseNodes(), *(meStmt->GetMuList()));
      return meStmt;
    }
    case OP_retsub: {
      WithMuMeStmt *retSub = NewInPool<WithMuMeStmt>(stmt);
      BuildMuList(ssaPart->GetMayUseNodes(), *(retSub->GetMuList()));
      return retSub;
    }
    case OP_gosub: {
      GosubMeStmt *goSub = NewInPool<GosubMeStmt>(stmt);
      BuildMuList(ssaPart->GetMayUseNodes(), *(goSub->GetMuList()));
      return goSub;
    }
    case OP_throw: {
      UnaryStmtNode *unaryNode = static_cast<UnaryStmtNode*>(stmt);
      ThrowMeStmt *tmeStmt = NewInPool<ThrowMeStmt>(stmt);
      tmeStmt->SetMeStmtOpndValue(BuildExpr(unaryNode->Opnd(0)));
      BuildMuList(ssaPart->GetMayUseNodes(), *(tmeStmt->GetMuList()));
      return tmeStmt;
    }
    case OP_syncenter:
    case OP_syncexit: {
      NaryStmtNode *naryNode = static_cast<NaryStmtNode*>(stmt);
      SyncMeStmt *naryStmt = NewInPool<SyncMeStmt>(stmt);
      for (size_t i = 0; i < naryNode->NumOpnds(); i++) {
        naryStmt->GetOpnds().push_back(BuildExpr(naryNode->Opnd(i)));
      }
      BuildMuList(ssaPart->GetMayUseNodes(), *(naryStmt->GetMuList()));
      BuildChiList(naryStmt, ssaPart->GetMayDefNodes(), *(naryStmt->GetChiList()));
      return naryStmt;
    }
    default: {
      ASSERT(false, "NYI");
      return nullptr;
    }
  }
}

void IRMap::BuildMuList(MapleMap<OStIdx, MayUseNode> &mayuselist, MapleMap<OStIdx, VarMeExpr*> &mulist) {
  for (std::pair<OStIdx, MayUseNode> mapitem : mayuselist) {
    MayUseNode &mayusenode = mapitem.second;
    VersionSt *verSt = mayusenode.GetOpnd();
    VarMeExpr *varmeexpr = GetOrCreateVarFromVerSt(verSt);
    mulist.insert(std::make_pair(varmeexpr->GetOStIdx(), varmeexpr));
  }
}

MeExpr *IRMap::BuildExpr(BaseNode *mirnode) {
  MeExpr *retmeexpr = nullptr;
  Opcode op = mirnode->GetOpCode();
  switch (op) {
    case OP_addrof: {
      AddrofSSANode *addrofnode = static_cast<AddrofSSANode*>(mirnode);
      VersionSt *verSt = addrofnode->GetSSAVar();
      OriginalSt *oSt = verSt->GetOrigSt();
      AddrofMeExpr addrofme(kInvalidExprID, oSt->GetIndex());
      addrofme.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      addrofme.SetFieldID(addrofnode->GetFieldID());
      retmeexpr = HashMeExpr(&addrofme);
      break;
    }
    case OP_dread: {
      AddrofSSANode *addrofnode = static_cast<AddrofSSANode*>(mirnode);
      VersionSt *verSt = addrofnode->GetSSAVar();
      VarMeExpr *varmeexpr = GetOrCreateVarFromVerSt(verSt);
      varmeexpr->InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      if (verSt->GetOrigSt()->IsRealSymbol()) {
        ASSERT(!verSt->GetOrigSt()->IsPregOst(), "not expect preg symbol here");
        varmeexpr->SetPtyp(
            GlobalTables::GetTypeTable().GetTypeFromTyIdx(verSt->GetOrigSt()->GetTyIdx())->GetPrimType());
        varmeexpr->SetFieldID(addrofnode->GetFieldID());
      }
      retmeexpr = varmeexpr;
      break;
    }
    case OP_regread: {
      RegreadSSANode *regnode = static_cast<RegreadSSANode*>(mirnode);
      VersionSt *verSt = regnode->GetSSAVar();
      RegMeExpr *regmeexpr = GetOrCreateRegFromVerSt(verSt);
      regmeexpr->InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = regmeexpr;
      break;
    }
    case OP_addroffunc: {
      AddroffuncNode *addfuncnode = static_cast<AddroffuncNode*>(mirnode);
      PUIdx puidx = addfuncnode->GetPUIdx();
      AddroffuncMeExpr addrfuncme(kInvalidExprID, puidx);
      addrfuncme.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&addrfuncme);
      break;
    }
    case OP_gcmalloc:
    case OP_gcpermalloc: {
      GCMallocNode *gcmallocnode = static_cast<GCMallocNode*>(mirnode);
      TyIdx tyidx = gcmallocnode->GetTyIdx();
      GcmallocMeExpr gcmallocme(kInvalidExprID, tyidx);
      gcmallocme.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&gcmallocme);
      break;
    }
    case OP_sizeoftype: {
      SizeoftypeNode *sizeoftypenode = static_cast<SizeoftypeNode*>(mirnode);
      SizeoftypeMeExpr sizemeexpr(kInvalidExprID, sizeoftypenode->GetTyIdx());
      sizemeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&sizemeexpr);
      break;
    }
    case OP_fieldsdist: {
      FieldsDistNode *fieldsDistNode = static_cast<FieldsDistNode*>(mirnode);
      FieldsDistMeExpr fieldsDistExpr(kInvalidExprID, fieldsDistNode->GetTyIdx(), fieldsDistNode->GetFiledID1(),
                                      fieldsDistNode->GetFiledID2());
      fieldsDistExpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&fieldsDistExpr);
      break;
    }
    case OP_iread: {
      IreadSSANode *ireadnode = static_cast<IreadSSANode*>(mirnode);
      IvarMeExpr ivarmeexpr(kInvalidExprID);
      ivarmeexpr.SetFieldID(ireadnode->GetFieldID());
      ivarmeexpr.SetTyIdx(ireadnode->GetTyIdx());
      ivarmeexpr.SetBase(BuildExpr(ireadnode->Opnd(0)));
      ivarmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      VersionSt *verSt = ireadnode->GetMayUse().GetOpnd();
      if (verSt != nullptr) {
        VarMeExpr *varmeexpr = GetOrCreateVarFromVerSt(verSt);
        ivarmeexpr.SetMuVal(varmeexpr);
      }
      retmeexpr = HashMeExpr(&ivarmeexpr);
      ASSERT(static_cast<IvarMeExpr*>(retmeexpr)->GetMu() != nullptr,
             "BuildExpr: ivar node cannot have mu == nullptr");
      break;
    }
    case OP_constval: {
      ConstvalNode *constnode = static_cast<ConstvalNode*>(mirnode);
      retmeexpr = CreateConstMeExpr(constnode->GetPrimType(), constnode->GetConstVal());
      break;
    }
    case OP_conststr: {
      ConststrNode *constnode = static_cast<ConststrNode*>(mirnode);
      ConststrMeExpr conststrmeexpr(kInvalidExprID, constnode->GetStrIdx());
      conststrmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&conststrmeexpr);
      break;
    }
    case OP_conststr16: {
      Conststr16Node *constnode = static_cast<Conststr16Node*>(mirnode);
      Conststr16MeExpr conststrmeexpr(kInvalidExprID, constnode->GetStrIdx());
      conststrmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&conststrmeexpr);
      break;
    }
    case OP_eq:
    case OP_ne:
    case OP_lt:
    case OP_gt:
    case OP_le:
    case OP_ge:
    case OP_cmpg:
    case OP_cmpl:
    case OP_cmp: {
      OpMeExpr opmeexpr(kInvalidExprID);
      CompareNode *cmpnode = static_cast<CompareNode*>(mirnode);
      opmeexpr.SetOpnd(0, BuildExpr(cmpnode->Opnd(0)));
      opmeexpr.SetOpnd(1, BuildExpr(cmpnode->Opnd(1)));
      opmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      opmeexpr.SetOpndType(cmpnode->GetOpndType());
      retmeexpr = HashMeExpr(&opmeexpr);
      static_cast<OpMeExpr*>(retmeexpr)->SetOpndType(cmpnode->GetOpndType());
      break;
    }
    case OP_ceil:
    case OP_cvt:
    case OP_floor:
    case OP_trunc: {
      OpMeExpr opmeexpr(kInvalidExprID);
      TypeCvtNode *tycvtnode = static_cast<TypeCvtNode*>(mirnode);
      opmeexpr.SetOpnd(0, BuildExpr(tycvtnode->Opnd(0)));
      opmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      opmeexpr.SetOpndType(tycvtnode->FromType());
      retmeexpr = HashMeExpr(&opmeexpr);
      break;
    }
    case OP_retype: {
      OpMeExpr opmeexpr(kInvalidExprID);
      RetypeNode *tycvtnode = static_cast<RetypeNode*>(mirnode);
      opmeexpr.SetOpnd(0, BuildExpr(tycvtnode->Opnd(0)));
      opmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      opmeexpr.SetOpndType(tycvtnode->FromType());
      opmeexpr.SetTyIdx(tycvtnode->GetTyIdx());
      retmeexpr = HashMeExpr(&opmeexpr);
      break;
    }
    case OP_abs:
    case OP_bnot:
    case OP_lnot:
    case OP_neg:
    case OP_recip:
    case OP_sqrt:
    case OP_alloca:
    case OP_malloc: {
      OpMeExpr opmeexpr(kInvalidExprID);
      UnaryNode *unnode = static_cast<UnaryNode*>(mirnode);
      opmeexpr.SetOpnd(0, BuildExpr(unnode->Opnd(0)));
      opmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&opmeexpr);
      break;
    }
    case OP_iaddrof: {
      OpMeExpr opmeexpr(kInvalidExprID);
      IreadNode *unnode = static_cast<IreadNode*>(mirnode);
      opmeexpr.SetTyIdx(unnode->GetTyIdx());
      opmeexpr.SetFieldID(unnode->GetFieldID());
      opmeexpr.SetOpnd(0, BuildExpr(unnode->Opnd(0)));
      opmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&opmeexpr);
      break;
    }
    case OP_sext:
    case OP_zext:
    case OP_extractbits: {
      OpMeExpr opmeexpr(kInvalidExprID);
      ExtractbitsNode *extnode = static_cast<ExtractbitsNode*>(mirnode);
      opmeexpr.SetOpnd(0, BuildExpr(extnode->Opnd(0)));
      opmeexpr.SetBitsOffSet(extnode->GetBitsOffset());
      opmeexpr.SetBitsSize(extnode->GetBitsSize());
      opmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&opmeexpr);
      break;
    }
    case OP_gcmallocjarray:
    case OP_gcpermallocjarray: {
      OpMeExpr opmeexpr(kInvalidExprID);
      JarrayMallocNode *gcnode = static_cast<JarrayMallocNode*>(mirnode);
      opmeexpr.SetOpnd(0, BuildExpr(gcnode->Opnd(0)));
      opmeexpr.GetTyIdx() = gcnode->GetTyIdx();
      opmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&opmeexpr);
      break;
    }
    case OP_resolveinterfacefunc:
    case OP_resolvevirtualfunc: {
      OpMeExpr opmeexpr(kInvalidExprID);
      ResolveFuncNode *rsnode = static_cast<ResolveFuncNode*>(mirnode);
      opmeexpr.SetOpnd(0, BuildExpr(rsnode->Opnd(0)));
      opmeexpr.SetOpnd(1, BuildExpr(rsnode->Opnd(1)));
      opmeexpr.SetFieldID(rsnode->GetPuIdx());
      opmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&opmeexpr);
      break;
    }
    case OP_sub:
    case OP_mul:
    case OP_div:
    case OP_rem:
    case OP_ashr:
    case OP_lshr:
    case OP_shl:
    case OP_max:
    case OP_min:
    case OP_band:
    case OP_bior:
    case OP_bxor:
    case OP_land:
    case OP_lior:
    case OP_add: {
      OpMeExpr opmeexpr(kInvalidExprID);
      BinaryNode *bnode = static_cast<BinaryNode*>(mirnode);
      opmeexpr.SetOpnd(0, BuildExpr(bnode->Opnd(0)));
      opmeexpr.SetOpnd(1, BuildExpr(bnode->Opnd(1)));
      opmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&opmeexpr);
      break;
    }
    case OP_select: {
      OpMeExpr opmeexpr(kInvalidExprID);
      TernaryNode *bnode = static_cast<TernaryNode*>(mirnode);
      opmeexpr.SetOpnd(0, BuildExpr(bnode->Opnd(0)));
      opmeexpr.SetOpnd(1, BuildExpr(bnode->Opnd(1)));
      opmeexpr.SetOpnd(2, BuildExpr(bnode->Opnd(2)));
      opmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&opmeexpr);
      break;
    }
    case OP_array: {
      ArrayNode *arrnode = static_cast<ArrayNode*>(mirnode);
      NaryMeExpr arrmeexpr(&tempAlloc, kInvalidExprID, arrnode->GetTyIdx(), INTRN_UNDEFINED, arrnode->GetBoundsCheck());
      for (size_t i = 0; i < arrnode->NumOpnds(); i++) {
        arrmeexpr.GetOpnds().push_back(BuildExpr(arrnode->Opnd(i)));
      }
      arrmeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&arrmeexpr);
      break;
    }
    case OP_intrinsicop: {
      IntrinsicopNode *intrinnode = static_cast<IntrinsicopNode*>(mirnode);
      size_t numopnds = intrinnode->NumOpnds();
      NaryMeExpr narymeexpr(&tempAlloc, kInvalidExprID, TyIdx(0), intrinnode->GetIntrinsic(), false);
      for (size_t i = 0; i < numopnds; i++) {
        narymeexpr.GetOpnds().push_back(BuildExpr(intrinnode->Opnd(i)));
      }
      narymeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&narymeexpr);
      break;
    }
    case OP_intrinsicopwithtype: {
      IntrinsicopNode *intrinnode = static_cast<IntrinsicopNode*>(mirnode);
      size_t numopnds = intrinnode->NumOpnds();
      NaryMeExpr narymeexpr(&irMapAlloc, kInvalidExprID, intrinnode->GetTyIdx(), intrinnode->GetIntrinsic(), false);
      for (size_t i = 0; i < numopnds; i++) {
        narymeexpr.GetOpnds().push_back(BuildExpr(intrinnode->Opnd(i)));
      }
      narymeexpr.InitBase(mirnode->GetOpCode(), mirnode->GetPrimType(), mirnode->GetNumOpnds());
      retmeexpr = HashMeExpr(&narymeexpr);
      break;
    }
    default:
      ASSERT(false, "NIY BuildExpe");
  }
  return retmeexpr;
}

void IRMap::PutToBucket(uint32 hashidx, MeExpr *meExpr) {
  MeExpr *headexpr = hashTable[hashidx];
  if (headexpr == nullptr) {
    hashTable[hashidx] = meExpr;
  } else {
    meExpr->SetNext(headexpr);
    hashTable[hashidx] = meExpr;
  }
}

/*
   Check if two IvarMeExpr are identical.
   If ivar_use is the first use of the same ivar coming from an iassign
   (ivar_def), then update its mu: ivar_def->mu = ivar_use->mu.
 */
static bool AreIvarIdentical(IvarMeExpr *ivarUse, IvarMeExpr *ivarDef) {
  if (ivarDef->GetBase()->GetExprID() != ivarUse->GetBase()->GetExprID()) {
    return false;
  }
  if (ivarDef->GetFieldID() != ivarUse->GetFieldID()) {
    return false;
  }
  if (ivarUse->GetTyIdx() != ivarDef->GetTyIdx()) {
    return false;
  }
  // check the two mu being identical
  if (ivarUse->GetMu() != ivarDef->GetMu()) {
    if (ivarDef->GetMu() != nullptr && ivarUse->GetMu() != nullptr && ivarDef->GetMu()->GetDefBy() == kDefByChi &&
        ivarUse->GetMu()->GetDefBy() == kDefByChi) {
      ChiMeNode *ivarDefChi = ivarDef->GetMu()->GetDefChi();
      ChiMeNode *ivarUseChi = ivarUse->GetMu()->GetDefChi();
      if (ivarDefChi->GetBase() != nullptr && ivarDefChi->GetBase() == ivarUseChi->GetBase()) {
        return true;
      }
    }
    if (ivarDef->GetMu() == nullptr && ivarDef->GetDefStmt() != nullptr && ivarUse->GetMu()) {
      IassignMeStmt *iass = ivarDef->GetDefStmt();
      if (iass->GetOp() != OP_iassign) {
        // this can happen due to use of placement new
        return false;
      }
      for (auto xit = iass->GetChiList()->begin(); xit != iass->GetChiList()->end();
           xit++) {
        ChiMeNode *chi = xit->second;
        if (chi->GetLHS()->GetExprID() == ivarUse->GetMu()->GetExprID()) {
          ivarDef->SetMuVal(ivarUse->GetMu());
          return true;
        }
      }
    }
    return false;
  }
  return true;
}

MeExpr *IRMap::HashMeExpr(MeExpr *meExpr) {
  uint32 hidx = meExpr->GetHashIndex() % mapHashLength;
  switch (meExpr->GetMeOp()) {
    case kMeOpIvar: {
      IvarMeExpr *ivarmeexpr = static_cast<IvarMeExpr*>(meExpr);
      IvarMeExpr *itexpr = static_cast<IvarMeExpr*>(hashTable[hidx]);
      while (itexpr != nullptr) {
        if (itexpr->GetMeOp() == kMeOpIvar && AreIvarIdentical(ivarmeexpr, itexpr)) {
          return itexpr;
        }
        itexpr = static_cast<IvarMeExpr*>(itexpr->GetNext());
      }
      IvarMeExpr *newivarexpr = New<IvarMeExpr>(exprID++, *ivarmeexpr);
      PutToBucket(hidx, newivarexpr);
      return newivarexpr;
    }
    case kMeOpOp: {
      OpMeExpr *opmeexpr = static_cast<OpMeExpr*>(meExpr);
      if (!kOpcodeInfo.NotPure(opmeexpr->GetOp())) {
        MeExpr *itexpr = hashTable[hidx];
        while (itexpr != nullptr) {
          if (opmeexpr->IsIdentical(static_cast<OpMeExpr*>(itexpr))) {
            return itexpr;
          }
          itexpr = itexpr->GetNext();
        }
      }
      OpMeExpr *newopmeexpr = New<OpMeExpr>(*opmeexpr, exprID++);
      newopmeexpr->UpdateDepth();
      PutToBucket(hidx, newopmeexpr);
      return newopmeexpr;
    }
    case kMeOpConst: {
      ConstMeExpr *constmeexpr = static_cast<ConstMeExpr*>(meExpr);
      ConstMeExpr *itexpr = static_cast<ConstMeExpr*>(hashTable[hidx]);
      MIRConst *mirconst = constmeexpr->GetConstVal();
      while (itexpr != nullptr) {
        if (itexpr->GetMeOp() != kMeOpConst) {
          itexpr = static_cast<ConstMeExpr*>(itexpr->GetNext());
          continue;
        }
        MIRConst *itmirconst = itexpr->GetConstVal();
        if (*mirconst == *itmirconst && meExpr->GetPrimType() == itexpr->GetPrimType()) {
          return itexpr;
        }
        itexpr = static_cast<ConstMeExpr*>(itexpr->GetNext());
      }
      ConstMeExpr *newconstmeexpr = New<ConstMeExpr>(exprID++, mirconst);
      newconstmeexpr->InitBase(meExpr->GetOp(), meExpr->GetPrimType(), meExpr->GetNumOpnds());
      PutToBucket(hidx, newconstmeexpr);
      return newconstmeexpr;
    }
    case kMeOpConststr: {
      ConststrMeExpr *constmeexpr = static_cast<ConststrMeExpr*>(meExpr);
      ConststrMeExpr *itexpr = static_cast<ConststrMeExpr*>(hashTable[hidx]);
      UStrIdx strIdx = constmeexpr->GetStrIdx();
      while (itexpr != nullptr) {
        if (itexpr->GetMeOp() != kMeOpConststr) {
          itexpr = static_cast<ConststrMeExpr*>(itexpr->GetNext());
          continue;
        }
        UStrIdx itstridx = itexpr->GetStrIdx();
        if (itstridx == strIdx) {
          return itexpr;
        }
        itexpr = static_cast<ConststrMeExpr*>(itexpr->GetNext());
      }
      ConststrMeExpr *newconstmeexpr = New<ConststrMeExpr>(exprID++, strIdx);
      newconstmeexpr->InitBase(meExpr->GetOp(), meExpr->GetPrimType(), meExpr->GetNumOpnds());
      PutToBucket(hidx, newconstmeexpr);
      return newconstmeexpr;
    }
    case kMeOpConststr16: {
      Conststr16MeExpr *constmeexpr = static_cast<Conststr16MeExpr*>(meExpr);
      Conststr16MeExpr *itexpr = static_cast<Conststr16MeExpr*>(hashTable[hidx]);
      U16StrIdx strIdx = constmeexpr->GetStrIdx();
      while (itexpr != nullptr) {
        if (itexpr->GetMeOp() != kMeOpConststr16) {
          itexpr = static_cast<Conststr16MeExpr*>(itexpr->GetNext());
          continue;
        }
        U16StrIdx itstridx = itexpr->GetStrIdx();
        if (itstridx == strIdx) {
          return itexpr;
        }
        itexpr = static_cast<Conststr16MeExpr*>(itexpr->GetNext());
      }
      Conststr16MeExpr *newconstmeexpr = New<Conststr16MeExpr>(exprID++, strIdx);
      newconstmeexpr->InitBase(meExpr->GetOp(), meExpr->GetPrimType(), meExpr->GetNumOpnds());
      PutToBucket(hidx, newconstmeexpr);
      return newconstmeexpr;
    }
    case kMeOpSizeoftype: {
      SizeoftypeMeExpr *sizeoftypeexpr = static_cast<SizeoftypeMeExpr*>(meExpr);
      SizeoftypeMeExpr *itexpr = static_cast<SizeoftypeMeExpr*>(hashTable[hidx]);
      while (itexpr != nullptr) {
        if (itexpr->GetMeOp() != kMeOpSizeoftype) {
          itexpr = static_cast<SizeoftypeMeExpr*>(itexpr->GetNext());
          continue;
        }
        if (itexpr->GetTyIdx() == sizeoftypeexpr->GetTyIdx()) {
          return itexpr;
        }
        itexpr = static_cast<SizeoftypeMeExpr*>(itexpr->GetNext());
      }
      SizeoftypeMeExpr *newmeexpr = New<SizeoftypeMeExpr>(exprID++, sizeoftypeexpr->GetTyIdx());
      newmeexpr->InitBase(meExpr->GetOp(), meExpr->GetPrimType(), meExpr->GetNumOpnds());
      PutToBucket(hidx, newmeexpr);
      return newmeexpr;
    }
    case kMeOpFieldsDist: {
      FieldsDistMeExpr *fieldsDistExpr = static_cast<FieldsDistMeExpr*>(meExpr);
      FieldsDistMeExpr *itexpr = static_cast<FieldsDistMeExpr*>(hashTable[hidx]);
      while (itexpr != nullptr) {
        if (itexpr->GetMeOp() != kMeOpFieldsDist) {
          itexpr = static_cast<FieldsDistMeExpr*>(itexpr->GetNext());
          continue;
        }
        if (itexpr->GetTyIdx() == fieldsDistExpr->GetTyIdx() &&
            itexpr->GetFieldID1() == fieldsDistExpr->GetFieldID1() &&
            itexpr->GetFieldID2() == fieldsDistExpr->GetFieldID2()) {
          return itexpr;
        }
        itexpr = static_cast<FieldsDistMeExpr*>(itexpr->GetNext());
      }
      FieldsDistMeExpr *newmeexpr = New<FieldsDistMeExpr>(exprID++, fieldsDistExpr->GetTyIdx(),
                                                          fieldsDistExpr->GetFieldID1(), fieldsDistExpr->GetFieldID2());
      newmeexpr->InitBase(meExpr->GetOp(), meExpr->GetPrimType(), meExpr->GetNumOpnds());
      PutToBucket(hidx, newmeexpr);
      return newmeexpr;
    }
    case kMeOpAddrof: {
      AddrofMeExpr *addrofmeexpr = static_cast<AddrofMeExpr*>(meExpr);
      AddrofMeExpr *itexpr = static_cast<AddrofMeExpr*>(hashTable[hidx]);
      while (itexpr != nullptr) {
        if (itexpr->GetMeOp() != kMeOpAddrof) {
          itexpr = static_cast<AddrofMeExpr*>(itexpr->GetNext());
          continue;
        }
        if (itexpr->GetOstIdx() == addrofmeexpr->GetOstIdx() && itexpr->GetFieldID() == addrofmeexpr->GetFieldID()) {
          return itexpr;
        }
        itexpr = static_cast<AddrofMeExpr*>(itexpr->GetNext());
      }
      AddrofMeExpr *newaddrofmeexpr = New<AddrofMeExpr>(exprID++, addrofmeexpr->GetOstIdx());
      newaddrofmeexpr->InitBase(meExpr->GetOp(), meExpr->GetPrimType(), meExpr->GetNumOpnds());
      newaddrofmeexpr->SetFieldID(addrofmeexpr->GetFieldID());
      PutToBucket(hidx, newaddrofmeexpr);
      return newaddrofmeexpr;
    }
    case kMeOpNary: {
      NaryMeExpr *narymeexpr = static_cast<NaryMeExpr*>(meExpr);
      NaryMeExpr *itexpr = static_cast<NaryMeExpr*>(hashTable[hidx]);
      while (itexpr != nullptr) {
        if ((itexpr->GetOp() == OP_array ||
             (itexpr->GetOp() == OP_intrinsicop && IntrinDesc::intrinTable[itexpr->GetIntrinsic()].IsPure())) &&
            itexpr->IsIdentical(narymeexpr)) {
          return itexpr;
        }
        itexpr = static_cast<NaryMeExpr*>(itexpr->GetNext());
      }
      NaryMeExpr *newnarymeexpr = NewInPool<NaryMeExpr>(exprID++, *narymeexpr);
      newnarymeexpr->InitBase(meExpr->GetOp(), meExpr->GetPrimType(), meExpr->GetNumOpnds());
      newnarymeexpr->UpdateDepth();
      PutToBucket(hidx, newnarymeexpr);
      return newnarymeexpr;
    }
    case kMeOpAddroffunc: {
      AddroffuncMeExpr *funcmeexpr = static_cast<AddroffuncMeExpr*>(meExpr);
      AddroffuncMeExpr *itexpr = static_cast<AddroffuncMeExpr*>(hashTable[hidx]);
      while (itexpr != nullptr) {
        if (itexpr->GetMeOp() != kMeOpAddroffunc) {
          itexpr = static_cast<AddroffuncMeExpr*>(itexpr->GetNext());
          continue;
        }
        if (itexpr->GetPuIdx() == funcmeexpr->GetPuIdx()) {
          return itexpr;
        }
        itexpr = static_cast<AddroffuncMeExpr*>(itexpr->GetNext());
      }
      AddroffuncMeExpr *newexpr = New<AddroffuncMeExpr>(exprID++, funcmeexpr->GetPuIdx());
      newexpr->InitBase(meExpr->GetOp(), meExpr->GetPrimType(), meExpr->GetNumOpnds());
      PutToBucket(hidx, newexpr);
      return newexpr;
    }
    case kMeOpGcmalloc: {
      GcmallocMeExpr *gcmeexpr = static_cast<GcmallocMeExpr*>(meExpr);
      GcmallocMeExpr *newexpr = New<GcmallocMeExpr>(exprID++, gcmeexpr->GetTyIdx());
      newexpr->InitBase(meExpr->GetOp(), meExpr->GetPrimType(), meExpr->GetNumOpnds());
      PutToBucket(hidx, newexpr);
      return newexpr;
    }
    default:
      ASSERT(false, "not yet implement");
      return nullptr;
  }
}

// replace meExpr with repexpr. meExpr must be a kid of origexpr
// return repexpr's parent if replaced, otherwise return nullptr
MeExpr *IRMap::ReplaceMeExprExpr(MeExpr *origExpr, MeExpr *meExpr, MeExpr *repexpr) {
  if (origExpr->IsLeaf()) {
    return origExpr;
  }
  switch (origExpr->GetMeOp()) {
    case kMeOpOp: {
      OpMeExpr *opmeexpr = static_cast<OpMeExpr*>(origExpr);
      OpMeExpr newmeexpr(*opmeexpr, kInvalidExprID);
      bool needRehash = false;
      for (uint32 i = 0; i < kOpndNumOfOpMeExpr; i++) {
        if (!opmeexpr->GetOpnd(i)) {
          continue;
        }
        if (opmeexpr->GetOpnd(i) == meExpr) {
          needRehash = true;
          newmeexpr.SetOpnd(i, repexpr);
        } else if (!opmeexpr->GetOpnd(i)->IsLeaf()) {
          newmeexpr.SetOpnd(i, ReplaceMeExprExpr(newmeexpr.GetOpnd(i), meExpr, repexpr));
          if (newmeexpr.GetOpnd(i) != opmeexpr->GetOpnd(i)) {
            needRehash = true;
          }
        }
      }
      return needRehash ? HashMeExpr(&newmeexpr) : origExpr;
    }
    case kMeOpNary: {
      NaryMeExpr *narymeexpr = static_cast<NaryMeExpr*>(origExpr);
      NaryMeExpr newmeexpr(&irMapAlloc, kInvalidExprID, *narymeexpr);
      const MapleVector<MeExpr*> &opnds = narymeexpr->GetOpnds();
      bool needRehash = false;
      for (size_t i = 0; i < opnds.size(); i++) {
        MeExpr *opnd = opnds[i];
        if (opnd == meExpr) {
          newmeexpr.SetOpnd(i, repexpr);
          needRehash = true;
        } else if (!opnd->IsLeaf()) {
          newmeexpr.SetOpnd(i, ReplaceMeExprExpr(newmeexpr.GetOpnd(i), meExpr, repexpr));
          if (newmeexpr.GetOpnd(i) != opnd) {
            needRehash = true;
          }
        }
      }
      return needRehash ? HashMeExpr(&newmeexpr) : origExpr;
    }
    case kMeOpIvar: {
      IvarMeExpr *ivarexpr = static_cast<IvarMeExpr*>(origExpr);
      IvarMeExpr newmeexpr(kInvalidExprID, *ivarexpr);
      bool needRehash = false;
      if (ivarexpr->GetBase() == meExpr) {
        newmeexpr.SetBase(repexpr);
        needRehash = true;
      } else if (!ivarexpr->GetBase()->IsLeaf()) {
        newmeexpr.SetBase(ReplaceMeExprExpr(newmeexpr.GetBase(), meExpr, repexpr));
        if (newmeexpr.GetBase() != ivarexpr->GetBase()) {
          needRehash = true;
        }
      }
      return needRehash ? HashMeExpr(&newmeexpr) : origExpr;
    }
    default:
      ASSERT(false, "NYI");
      return nullptr;
  }
}

bool IRMap::ReplaceMeExprStmtOpnd(uint32 opndID, MeStmt *meStmt, MeExpr *meExpr, MeExpr *repExpr) {
  MeExpr *opnd = meStmt->GetOpnd(opndID);
  if (opnd == meExpr) {
    meStmt->SetOpnd(opndID, repExpr);
    return true;
  } else if (!opnd->IsLeaf()) {
    meStmt->SetOpnd(opndID, ReplaceMeExprExpr(opnd, meExpr, repExpr));
    return meStmt->GetOpnd(opndID) != opnd;
  }
  return false;
}

// replace meExpr in meStmt with repexpr
bool IRMap::ReplaceMeExprStmt(MeStmt *meStmt, MeExpr *meExpr, MeExpr *repexpr) {
  bool isReplaced = false;
  switch (meStmt->GetOp()) {
    case OP_dassign:
    case OP_regassign:
    case OP_maydassign:
    case OP_decref:
    case OP_decrefreset:
    case OP_incref:
    case OP_assertnonnull:
    case OP_eval:
    case OP_free:
    case OP_switch:
    case OP_brtrue:
    case OP_brfalse:
    case OP_throw: {
      isReplaced = ReplaceMeExprStmtOpnd(0, meStmt, meExpr, repexpr);
      break;
    }
    case OP_syncenter:
    case OP_syncexit:
    case OP_call:
    case OP_virtualcall:
    case OP_virtualicall:
    case OP_superclasscall:
    case OP_interfacecall:
    case OP_interfaceicall:
    case OP_customcall:
    case OP_polymorphiccall:
    case OP_icall:
    case OP_callassigned:
    case OP_virtualcallassigned:
    case OP_virtualicallassigned:
    case OP_superclasscallassigned:
    case OP_interfacecallassigned:
    case OP_interfaceicallassigned:
    case OP_customcallassigned:
    case OP_polymorphiccallassigned:
    case OP_icallassigned:
    case OP_return: {
      for (size_t i = 0; i < meStmt->NumMeStmtOpnds(); i++) {
        bool curOpndReplaced = ReplaceMeExprStmtOpnd(i, meStmt, meExpr, repexpr);
        isReplaced = isReplaced || curOpndReplaced;
      }
      break;
    }
    case OP_intrinsiccall:
    case OP_xintrinsiccall:
    case OP_intrinsiccallwithtype:
    case OP_intrinsiccallassigned:
    case OP_xintrinsiccallassigned:
    case OP_intrinsiccallwithtypeassigned: {
      for (size_t i = 0; i < meStmt->NumMeStmtOpnds(); i++) {
        MeExpr *opnd = meStmt->GetOpnd(i);
        if (opnd->IsLeaf() && opnd->GetMeOp() == kMeOpVar) {
          VarMeExpr *varmeexpr = static_cast<VarMeExpr*>(opnd);
          OriginalSt *orgsym = ssaTab->GetOriginalStFromID(varmeexpr->GetOStIdx());
          if (orgsym->IsSymbolOst() && orgsym->GetMIRSymbol()->GetAttr(ATTR_static)) {
            // its address may be taken
            continue;
          }
        }
        bool curOpndReplaced = ReplaceMeExprStmtOpnd(i, meStmt, meExpr, repexpr);
        isReplaced = isReplaced || curOpndReplaced;
      }
      break;
    }
    case OP_iassign: {
      IassignMeStmt *ivarstmt = static_cast<IassignMeStmt*>(meStmt);
      bool baseIsReplaced = ReplaceMeExprStmtOpnd(0, meStmt, meExpr, repexpr);
      if (baseIsReplaced) {
        ivarstmt->SetLHSVal(BuildLHSIvar(ivarstmt->GetOpnd(0), ivarstmt, ivarstmt->GetLHSVal()->GetFieldID()));
      }
      bool rhsReplaced = ReplaceMeExprStmtOpnd(1, meStmt, meExpr, repexpr);
      isReplaced = baseIsReplaced || rhsReplaced;
      break;
    }
    case OP_assertlt:
    case OP_assertge: {
      bool opnd0Replaced = ReplaceMeExprStmtOpnd(0, meStmt, meExpr, repexpr);
      bool opnd1Replaced = ReplaceMeExprStmtOpnd(1, meStmt, meExpr, repexpr);
      isReplaced = opnd0Replaced || opnd1Replaced;
      break;
    }
    default:
      ASSERT(false, "NYI");
  }
  return isReplaced;
}

MeRegPhiNode *IRMap::CreateMeRegPhi(RegMeExpr *mevar) {
  MeRegPhiNode *phimereg = NewInPool<MeRegPhiNode>();
  phimereg->UpdateLHS(mevar);
  return phimereg;
}

MeVarPhiNode *IRMap::CreateMeVarPhi(VarMeExpr *mevar) {
  MeVarPhiNode *phimevar = NewInPool<MeVarPhiNode>();
  phimevar->UpdateLHS(mevar);
  return phimevar;
}

DassignMeStmt *IRMap::CreateDassignMeStmt(MeExpr *lhs, MeExpr *rhs, BB *curbb) {
  DassignMeStmt *meStmt = NewInPool<DassignMeStmt>();
  meStmt->SetRHS(rhs);
  VarMeExpr *var = static_cast<VarMeExpr*>(lhs);
  meStmt->SetLHS(var);
  var->SetDefBy(kDefByStmt);
  var->SetDefStmt(meStmt);
  meStmt->SetBB(curbb);
  return meStmt;
}

RegassignMeStmt *IRMap::CreateRegassignMeStmt(MeExpr *lhs, MeExpr *rhs, BB *curbb) {
  RegassignMeStmt *meStmt = New<RegassignMeStmt>();
  ASSERT(lhs->GetMeOp() == kMeOpReg, "Create regassign without lhs == regread");
  meStmt->SetRHS(rhs);
  RegMeExpr *reg = static_cast<RegMeExpr*>(lhs);
  meStmt->SetLHS(reg);
  reg->SetDefBy(kDefByStmt);
  reg->SetDefStmt(meStmt);
  meStmt->SetBB(curbb);
  return meStmt;
}

// get the false goto bb, if condgoto is brtrue, take the other bb of brture @lable
// otherwise, take the bb of @lable
BB *IRMap::GetFalseBrBB(CondGotoMeStmt *condgoto) {
  LabelIdx lblidx = (LabelIdx)condgoto->GetOffset();
  BB *gotobb = GetBBForLabIdx(lblidx);
  BB *bb = condgoto->GetBB();
  ASSERT(bb->GetSucc().size() == 2, "array size error");
  if (condgoto->GetOp() == OP_brfalse) {
    return gotobb;
  } else {
    return gotobb == bb->GetSucc(0) ? bb->GetSucc(1) : bb->GetSucc(0);
  }
}

MeExpr *IRMap::CreateConstMeExpr(PrimType ptyp, MIRConst *mirconst) {
  ConstMeExpr constmeexpr(kInvalidExprID, mirconst);
  constmeexpr.SetOp(OP_constval);
  constmeexpr.SetPtyp(ptyp);
  return HashMeExpr(&constmeexpr);
}

MeExpr *IRMap::CreateIntConstMeExpr(int64 value, PrimType ptyp) {
  MIRIntConst *intconst =
      mirModule->GetMemPool()->New<MIRIntConst>(value, GlobalTables::GetTypeTable().GetPrimType(ptyp));
  return CreateConstMeExpr(ptyp, intconst);
}

MeExpr *IRMap::CreateMeExprBinary(Opcode op, PrimType ptyp, MeExpr *expr0, MeExpr *expr1) {
  OpMeExpr opmeexpr(kInvalidExprID);
  opmeexpr.SetOpnd(0, expr0);
  opmeexpr.SetOpnd(1, expr1);
  opmeexpr.InitBase(op, ptyp, 2);
  return HashMeExpr(&opmeexpr);
}

MeExpr *IRMap::CreateMeExprSelect(PrimType ptyp, MeExpr *expr0, MeExpr *expr1, MeExpr *expr2) {
  OpMeExpr opmeexpr(kInvalidExprID);
  opmeexpr.SetOpnd(0, expr0);
  opmeexpr.SetOpnd(1, expr1);
  opmeexpr.SetOpnd(2, expr2);
  opmeexpr.InitBase(OP_select, ptyp, 3);
  return HashMeExpr(&opmeexpr);
}

MeExpr *IRMap::CreateMeExprCompare(Opcode op, PrimType resptyp, PrimType opndptyp, MeExpr *opnd0, MeExpr *opnd1) {
  OpMeExpr opmeexpr(kInvalidExprID);
  opmeexpr.SetOpnd(0, opnd0);
  opmeexpr.SetOpnd(1, opnd1);
  opmeexpr.InitBase(op, resptyp, 2);
  opmeexpr.SetOpndType(opndptyp);
  MeExpr *retmeexpr = HashMeExpr(&opmeexpr);
  static_cast<OpMeExpr*>(retmeexpr)->SetOpndType(opndptyp);
  return retmeexpr;
}

MeExpr *IRMap::CreateMeExprTypeCvt(PrimType ptyp, PrimType opndptyp, MeExpr *opnd0) {
  OpMeExpr opmeexpr(kInvalidExprID);
  opmeexpr.SetOpnd(0, opnd0);
  opmeexpr.InitBase(OP_cvt, ptyp, 1);
  opmeexpr.SetOpndType(opndptyp);
  return HashMeExpr(&opmeexpr);
}

IntrinsiccallMeStmt *IRMap::CreateIntrinsicCallMeStmt(MIRIntrinsicID idx, std::vector<MeExpr*> &opnds, TyIdx tyidx) {
  IntrinsiccallMeStmt *meStmt =
      NewInPool<IntrinsiccallMeStmt>(tyidx == 0 ? OP_intrinsiccall : OP_intrinsiccallwithtype, idx, tyidx);
  for (MeExpr *opnd : opnds) {
    meStmt->GetOpnds().push_back(opnd);
  }
  return meStmt;
}

IntrinsiccallMeStmt *IRMap::CreateIntrinsicCallAssignedMeStmt(MIRIntrinsicID idx, std::vector<MeExpr*> &opnds,
                                                              MeExpr *ret, TyIdx tyidx) {
  IntrinsiccallMeStmt *meStmt = NewInPool<IntrinsiccallMeStmt>(
      tyidx == 0 ? OP_intrinsiccallassigned : OP_intrinsiccallwithtypeassigned, idx, tyidx);
  for (MeExpr *opnd : opnds) {
    meStmt->GetOpnds().push_back(opnd);
  }
  if (ret != nullptr) {
    ASSERT(ret->GetMeOp() == kMeOpReg || ret->GetMeOp() == kMeOpVar, "unexpected opcode");
    MustDefMeNode *mustdef = New<MustDefMeNode>(ret, meStmt);
    meStmt->GetMustDefList()->push_back(*mustdef);
  }
  return meStmt;
}

MeExpr *IRMap::CreateAddrofMeExprFromNewSymbol(MIRSymbol *st, PUIdx puidx) {
  OriginalSt *baseOst = ssaTab->CreateSymbolOriginalSt(st, puidx, 0);
  AddrofMeExpr addrofme(kInvalidExprID, baseOst->GetIndex());
  addrofme.SetOp(OP_addrof);
  addrofme.SetPtyp(PTY_ptr);
  return HashMeExpr(&addrofme);
}

}  // namespace maple
