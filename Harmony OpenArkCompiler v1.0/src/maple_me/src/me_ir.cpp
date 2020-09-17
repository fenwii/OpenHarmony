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
#include "me_ir.h"
#include "opcode_info.h"
#include "irmap.h"
#include "printing.h"
#include "me_ssa.h"
#include "mir_function.h"

namespace maple {

constexpr int32 kDefaultPrintIndentNum = 5;

bool MeExpr::IsTheSameWorkcand(MeExpr *meexpr) const {
  ASSERT((exprID != -1 || meexpr->GetExprID() != -1), "at least one of them should not be none initialized");
  if (exprID == meexpr->GetExprID()) {
    return true;
  }
  if (op != meexpr->GetOp()) {
    return false;
  }
  if (IsPrimitiveFloat(primType) != IsPrimitiveFloat(meexpr->GetPrimType())) {
    return false;
  }
  if (GetPrimTypeSize(primType) != GetPrimTypeSize(meexpr->GetPrimType())) {
    return false;
  }
  if (op == OP_cvt && primType != meexpr->GetPrimType()) {
    // exclude cvt for different return type
    return false;
  }
  if (op == OP_resolveinterfacefunc || op == OP_resolvevirtualfunc)
    if (static_cast<const OpMeExpr*>(this)->GetFieldID() != static_cast<OpMeExpr*>(meexpr)->GetFieldID()) {
      return false;
    }
  if (IsUseSameSymbol(meexpr)) {
    return true;
  }
  return false;
}

void MeExpr::UpdateDepth() {
  uint8 maxDepth = 0;
  for (int32 i = 0; i < GetNumOpnds(); i++) {
    MeExpr *opnd = GetOpnd(i);
    if (opnd == nullptr) {
      continue;
    }
    uint8 curDepth = opnd->GetDepth();
    if (curDepth > maxDepth) {
      maxDepth = curDepth;
    }
  }
  ASSERT(maxDepth < UINT8_MAX, "runtime check error");
  depth = (uint8)maxDepth + 1;
}

// get the definition of this
// for example:
// v2 = x + b
// v1 = v2
// then v1->ResolveMeExprValue() returns x+b
MeExpr *MeExpr::ResolveMeExprValue() {
  MeExpr *cmpOpLocal = this;
  while (cmpOpLocal != nullptr && cmpOpLocal->GetMeOp() == kMeOpVar) {
    VarMeExpr *varCmpOp = static_cast<VarMeExpr*>(cmpOpLocal);
    if (varCmpOp->GetDefBy() == kDefByStmt) {
      cmpOpLocal = static_cast<DassignMeStmt*>(varCmpOp->GetDefStmt())->GetRHS();
    } else if (varCmpOp->GetDefBy() == kDefByChi) {
      ChiMeNode *defchi = varCmpOp->GetDefChi();
      MeStmt *base = defchi->GetBase();
      if (base->GetOp() == OP_maydassign) {
        cmpOpLocal = static_cast<MaydassignMeStmt*>(base)->GetRHS();
      } else {
        cmpOpLocal = nullptr;
      }
    } else {
      cmpOpLocal = nullptr;
    }
  }
  return cmpOpLocal;
}

// get the definition VarMeExpr of this
// for expample:
// v2 = v3
// v1 = v2
// this = v1
// this->ResolveVarMeValue() returns v3;
// if no resolved VarMeExpr, return this
VarMeExpr *VarMeExpr::ResolveVarMeValue() {
  VarMeExpr *cmpop0 = this;
  while (true) {
    if (cmpop0->defBy == kDefByStmt) {
      DassignMeStmt *defStmt = static_cast<DassignMeStmt*>(cmpop0->def.defStmt);
      if (defStmt->GetRHS()->GetMeOp() != kMeOpVar) {
        break;
      }
      cmpop0 = static_cast<VarMeExpr*>(defStmt->GetRHS());
    } else {
      break;
    }
  }
  return cmpop0;
}

// *this can be any node, but *v must be VarMeExpr
bool MeExpr::IsSameVariableValue(VarMeExpr *v) const {
  if (v == this) {
    return true;
  }
  // look up x's value if it is variable or register
  if (meOp == kMeOpVar) {
    const VarMeExpr *xvar = static_cast<const VarMeExpr*>(this);
    if (xvar->GetDefBy() == kDefByStmt && xvar->GetDefStmt()->GetOp() == OP_dassign) {
      DassignMeStmt *xdass = static_cast<DassignMeStmt*>(xvar->GetDefStmt());
      if (xdass->GetRHS() == v) {
        return true;
      }
    }
  } else if (meOp == kMeOpReg) {
    const RegMeExpr *xreg = static_cast<const RegMeExpr*>(this);
    if (xreg->GetDefBy() == kDefByStmt && xreg->GetDefStmt()->GetOp() == OP_regassign) {
      RegassignMeStmt *xrass = static_cast<RegassignMeStmt*>(xreg->GetDefStmt());
      if (xrass->GetRHS() == v) {
        return true;
      }
    }
  }
  // look up v's value
  if (v->GetDefBy() == kDefByStmt && v->GetDefStmt()->GetOp() == OP_dassign) {
    DassignMeStmt *vdass = static_cast<DassignMeStmt*>(v->GetDefStmt());
    if (vdass->GetRHS() == this) {
      return true;
    }
  }
  return false;
}

// return true if the expression could throw exception; needs to be in sync with
// BaseNode::MayThrowException()
bool MeExpr::CouldThrowException() const {
  if (kOpcodeInfo.MayThrowException(op)) {
    if (op != OP_array) {
      return true;
    }
    if (static_cast<const NaryMeExpr*>(this)->GetBoundCheck()) {
      return true;
    }
  } else if (op == OP_intrinsicop) {
    if (static_cast<const NaryMeExpr*>(this)->GetIntrinsic() == INTRN_JAVA_ARRAY_LENGTH) {
      return true;
    }
  }
  for (int32 i = 0; i < GetNumOpnds(); i++) {
    if (GetOpnd(i)->CouldThrowException()) {
      return true;
    }
  }
  return false;
}

// search through the SSA graph to find a version with GetDefBy() == DefBYy_stmt
// visited is for avoiding processing a node more than once
RegMeExpr *RegMeExpr::FindDefByStmt(std::set<RegMeExpr*> *visited) {
  if (visited->find(this) != visited->end()) {
    return nullptr;
  }
  visited->insert(this);
  if (GetDefBy() == kDefByStmt) {
    return this;
  }
  if (GetDefBy() == kDefByPhi) {
    MeRegPhiNode *phireg = GetDefPhi();
    for (RegMeExpr *phiOpnd : phireg->GetOpnds()) {
      RegMeExpr *res = phiOpnd->FindDefByStmt(visited);
      if (res != nullptr) {
        return res;
      }
    }
  }
  return nullptr;
}

MeExpr *MeExpr::GetAddrExprBase() {
  switch (meOp) {
    case kMeOpAddrof:
    case kMeOpVar:
      return this;
    case kMeOpOp:
      if (op == OP_add || op == OP_sub) {
        OpMeExpr *opMeExpr = static_cast<OpMeExpr*>(this);
        return opMeExpr->GetOpnd(0)->GetAddrExprBase();
      }
      return this;
    case kMeOpNary:
      if (op == OP_array) {
        NaryMeExpr *naryExpr = static_cast<NaryMeExpr*>(this);
        ASSERT(naryExpr->GetOpnd(0) != nullptr, "");
        return naryExpr->GetOpnd(0)->GetAddrExprBase();
      }
      return this;
    case kMeOpReg: {
      RegMeExpr *baseVar = static_cast<RegMeExpr*>(this);
      std::set<RegMeExpr*> visited;
      baseVar = baseVar->FindDefByStmt(&visited);
      if (baseVar != nullptr && baseVar->GetDefBy() == kDefByStmt) {
        MeStmt *baseDefStmt = baseVar->GetDefStmt();
        RegassignMeStmt *regAssign = static_cast<RegassignMeStmt*>(baseDefStmt);
        MeExpr *rhs = regAssign->GetRHS();
        // Following we only consider array, add and sub
        // Prevent the following situation for reg %1
        // regAssign ref %1 (gcmallocjarray ref ...)
        if (rhs->op == OP_array || rhs->op == OP_add || rhs->op == OP_sub) {
          return rhs->GetAddrExprBase();
        }
      }
      return this;
    }
    default:
      return this;
  }
}

bool NaryMeExpr::IsUseSameSymbol(MeExpr *meexpr) const {
  NaryMeExpr *naryMeExpr = dynamic_cast<NaryMeExpr*>(meexpr);
  if (naryMeExpr == nullptr) {
    return false;
  }
  if (meexpr->GetOp() != GetOp() || naryMeExpr->GetIntrinsic() != intrinsic || naryMeExpr->tyIdx != tyIdx) {
    return false;
  }
  if (opnds.size() != naryMeExpr->GetOpnds().size()) {
    return false;
  }
  for (size_t i = 0; i < opnds.size(); i++) {
    if (!opnds[i]->IsUseSameSymbol(naryMeExpr->GetOpnd(i))) {
      return false;
    }
  }
  return true;
}

bool OpMeExpr::IsIdentical(const OpMeExpr *meexpr) {
  if (meexpr->GetOp() != GetOp()) {
    return false;
  }
  if (meexpr->GetPrimType() != GetPrimType() || meexpr->opndType != opndType || meexpr->bitsOffset != bitsOffset ||
      meexpr->bitsSize != bitsSize || meexpr->tyIdx != tyIdx || meexpr->fieldID != fieldID) {
    return false;
  }
  CHECK_FATAL(meexpr->opnds[0], "at least opnds[0] shouldn't be empty");
  CHECK_FATAL(opnds[0], "at least opnds[0] shouldn't be empty");
  if (meexpr->opnds[0]->GetExprID() != opnds[0]->GetExprID()) {
    return false;
  }
  if ((meexpr->opnds[1] && !opnds[1]) || (!meexpr->opnds[1] && opnds[1])) {
    return false;
  }
  if ((meexpr->opnds[1] && opnds[1] && meexpr->opnds[1]->GetExprID() != opnds[1]->GetExprID())) {
    return false;
  }
  if ((meexpr->opnds[2] && !opnds[2]) || (!meexpr->opnds[2] && opnds[2])) {
    return false;
  }
  if ((meexpr->opnds[2] && opnds[2] && meexpr->opnds[2]->GetExprID() != opnds[2]->GetExprID())) {
    return false;
  }
  return true;
}

bool NaryMeExpr::IsIdentical(NaryMeExpr *meexpr) const {
  if (meexpr->GetOp() != GetOp() || meexpr->tyIdx != tyIdx || meexpr->GetIntrinsic() != intrinsic ||
      meexpr->boundCheck != boundCheck) {
    return false;
  }
  if (meexpr->GetNumOpnds() != GetNumOpnds()) {
    return false;
  }
  for (uint8 i = 0; i < GetNumOpnds(); i++) {
    if (opnds[i]->GetExprID() != meexpr->GetOpnd(i)->GetExprID()) {
      // expression comparison
      return false;
    }
  }
  return true;
}

bool IvarMeExpr::IsUseSameSymbol(MeExpr *meexpr) const {
  if (meexpr->GetExprID() == GetExprID()) {
    return true;
  }
  IvarMeExpr *ivarMeExpr = dynamic_cast<IvarMeExpr*>(meexpr);
  if (ivarMeExpr == nullptr) {
    return false;
  }
  if (base->IsUseSameSymbol(ivarMeExpr->base) && fieldID == ivarMeExpr->fieldID) {
    return true;
  }
  return false;
}

bool IvarMeExpr::IsVolatile() {
  MIRPtrType *ty = static_cast<MIRPtrType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx));
  MIRType *pointedType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ty->GetPointedTyIdx());
  if (fieldID == 0) {
    return pointedType->HasVolatileField();
  }
  return static_cast<MIRStructType*>(pointedType)->IsFieldVolatile(fieldID);
}

bool IvarMeExpr::IsFinal() {
  MIRPtrType *ty = static_cast<MIRPtrType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx));
  MIRType *pointedTy = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ty->GetPointedTyIdx());
  if (fieldID == 0) {
    return false;
  }
  return static_cast<MIRStructType*>(pointedTy)->IsFieldFinal(fieldID);
}

/*
 * check paragma
 *   pragma 0 var %keySet <$Ljava_2Flang_2Fannotation_2FRCWeakRef_3B>
 */
bool IvarMeExpr::IsRCWeak() {
  MIRPtrType *ty = static_cast<MIRPtrType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx));
  MIRType *pointedType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ty->GetPointedTyIdx());
  if (pointedType->GetKind() == kTypeClass) {
    MIRClassType *classType = static_cast<MIRClassType*>(pointedType);
    return classType->IsFieldRCWeak(fieldID);
  }
  return false;
}

BB *VarMeExpr::GetDefByBBMeStmt(Dominance *dominance, MeStmtPtr &defMeStmt) {
  BB *bbx = nullptr;
  switch (defBy) {
    case kDefByNo: {
      bbx = dominance->GetCommonEntryBB();
      break;
    }
    case kDefByStmt: {
      defMeStmt = def.defStmt;
      bbx = defMeStmt->GetBB();
      break;
    }
    case kDefByMustDef: {
      MustDefMeNode *defMustDef = def.defMustDef;
      defMeStmt = defMustDef->GetBase();
      bbx = defMeStmt->GetBB();
      break;
    }
    case kDefByChi: {
      ChiMeNode *defchi = def.defChi;
      defMeStmt = defchi->GetBase();
      bbx = defMeStmt->GetBB();
      break;
    }
    case kDefByPhi: {
      MeVarPhiNode *defphi = def.defPhi;
      bbx = defphi->GetDefBB();
      break;
    }
    default:
      break;
  }
  return bbx;
}

bool VarMeExpr::IsUseSameSymbol(MeExpr *meexpr) const {
  VarMeExpr *varMeExpr = dynamic_cast<VarMeExpr*>(meexpr);
  if (varMeExpr == nullptr) {
    return false;
  }
  return ostIdx == varMeExpr->ostIdx;
}

bool VarMeExpr::IsPureLocal(SSATab *ssatab, const MIRFunction *mirfunc) const {
  MIRSymbol *st = ssatab->GetMIRSymbolFromID(ostIdx);
  return st->IsLocal() && !mirfunc->IsAFormal(st);
}

bool VarMeExpr::IsZeroVersion(SSATab *ssatab) const {
  ASSERT(vstIdx != 0, "VarMeExpr::IsZeroVersion: cannot determine because vstIdx is 0");
  OriginalSt *ost = ssatab->GetOriginalStFromID(ostIdx);
  return ost->GetZeroVersionIndex() == vstIdx;
}

bool RegMeExpr::IsUseSameSymbol(MeExpr *meExpr) const {
  RegMeExpr *regMeExpr = dynamic_cast<RegMeExpr*>(meExpr);
  if (regMeExpr == nullptr) {
    return false;
  }
  return ostIdx == regMeExpr->ostIdx;
}

BB *RegMeExpr::DefByBB() {
  switch (defBy) {
    case kDefByNo:
      return nullptr;
    case kDefByStmt:
      ASSERT(def.defStmt, "VarMeExpr::DefByBB: defStmt cannot be nullptr");
      return def.defStmt->GetBB();
    case kDefByPhi:
      ASSERT(def.defPhi, "VarMeExpr::DefByBB: defPhi cannot be nullptr");
      return def.defPhi->GetDefBB();
    case kDefByMustDef:
      ASSERT(def.defMustDef, "VarMeExpr::DefByBB: defMustDef cannot be nullptr");
      ASSERT(def.defMustDef->GetBase(), "VarMeExpr::DefByBB: defMustDef->base cannot be nullptr");
      return def.defMustDef->GetBase()->GetBB();
    default:
      ASSERT(false, "reg define unknown");
      return nullptr;
  }
}

bool AddrofMeExpr::IsUseSameSymbol(MeExpr *meexpr) const {
  AddrofMeExpr *varMeExpr = dynamic_cast<AddrofMeExpr*>(meexpr);
  if (!varMeExpr) {
    return false;
  }
  return ostIdx == varMeExpr->ostIdx;
}

bool OpMeExpr::IsUseSameSymbol(MeExpr *meexpr) const {
  if (meexpr->GetOp() != GetOp()) {
    return false;
  }
  OpMeExpr *opmeexpr = dynamic_cast<OpMeExpr*>(meexpr);
  if (opmeexpr == nullptr) {
    return false;
  }
  for (uint32 i = 0; i < kOpndNumOfOpMeExpr; i++) {
    if (opnds[i]) {
      if (!opmeexpr->opnds[i]) {
        return false;
      }
      if (!opnds[i]->IsUseSameSymbol(opmeexpr->opnds[i])) {
        return false;
      }
    } else {
      if (opmeexpr->opnds[i]) {
        return false;
      }
    }
  }
  return true;
}

// first, make sure it's int const and return true if the int const great or eq 0
bool ConstMeExpr::GeZero() const {
  return (GetIntValue() >= 0);
}

bool ConstMeExpr::GtZero() const {
  MIRIntConst *mirConst = dynamic_cast<MIRIntConst*>(constVal);
  if (mirConst == nullptr) {
    return false;
  }
  return (mirConst->GetValue() > 0);
}

bool ConstMeExpr::IsZero() const {
  return (GetIntValue() == 0);
}

bool ConstMeExpr::IsOne() const {
  MIRIntConst *mirConst = dynamic_cast<MIRIntConst*>(constVal);
  if (mirConst == nullptr) {
    return false;
  }
  return (mirConst->GetValue() == 1);
}

int64 ConstMeExpr::GetIntValue() const {
  MIRIntConst *mirConst = dynamic_cast<MIRIntConst*>(constVal);
  ASSERT(mirConst, "expect int const");
  return mirConst->GetValue();
}

void MeVarPhiNode::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "VAR:";
  irMap->GetSSATab()->GetOriginalStFromID(lhs->GetOStIdx())->Dump();
  LogInfo::MapleLogger() << " mx" << lhs->GetExprID();
  LogInfo::MapleLogger() << " = MEPHI{";
  for (size_t i = 0; i < opnds.size(); i++) {
    LogInfo::MapleLogger() << "mx" << opnds[i]->GetExprID();
    if (i != opnds.size() - 1) {
      LogInfo::MapleLogger() << ",";
    }
  }
  LogInfo::MapleLogger() << "}";
  if (!isLive) {
    LogInfo::MapleLogger() << " dead";
  }
  LogInfo::MapleLogger() << std::endl;
}

void MeRegPhiNode::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "REGVAR: " << lhs->GetRegIdx();
  LogInfo::MapleLogger() << "(%"
                         << irMap->GetMIRModule()->CurFunction()
                                                 ->GetPregTab()
                                                 ->PregFromPregIdx(static_cast<PregIdx>(lhs->GetRegIdx()))
                                                 ->GetPregNo()
                         << ")";
  LogInfo::MapleLogger() << " mx" << lhs->GetExprID();
  LogInfo::MapleLogger() << " = MEPHI{";
  for (size_t i = 0; i < opnds.size(); i++) {
    LogInfo::MapleLogger() << "mx" << opnds[i]->GetExprID();
    if (i != opnds.size() - 1) {
      LogInfo::MapleLogger() << ",";
    }
  }
  LogInfo::MapleLogger() << "}" << std::endl;
}

void VarMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << "VAR ";
  irMap->GetSSATab()->GetOriginalStFromID(ostIdx)->Dump();
  LogInfo::MapleLogger() << " (field)" << fieldID;
  LogInfo::MapleLogger() << " mx" << GetExprID();
  if (IsZeroVersion(irMap->GetSSATab())) {
    LogInfo::MapleLogger() << "<Z>";
  }
}

void RegMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << "REGINDX:" << regIdx;
  LogInfo::MapleLogger()
      << " %"
      << irMap->GetMIRModule()->CurFunction()->GetPregTab()->PregFromPregIdx(static_cast<PregIdx>(regIdx))->GetPregNo();
  LogInfo::MapleLogger() << " mx" << GetExprID();
}

void AddroffuncMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << "ADDROFFUNC:";
  LogInfo::MapleLogger() << GlobalTables::GetFunctionTable().GetFunctionFromPuidx(puIdx)->GetName();
  LogInfo::MapleLogger() << " mx" << GetExprID();
}

void GcmallocMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOp()).name << " " << GetPrimTypeName(GetPrimType());
  LogInfo::MapleLogger() << " ";
  GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(0);
  LogInfo::MapleLogger() << " mx" << GetExprID();
  LogInfo::MapleLogger() << " ";
}

void ConstMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << "CONST";
  LogInfo::MapleLogger() << " ";
  constVal->Dump();
  LogInfo::MapleLogger() << " mx" << GetExprID();
}

void ConststrMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << "CONSTSTR";
  LogInfo::MapleLogger() << " ";
  LogInfo::MapleLogger() << strIdx.GetIdx();
  LogInfo::MapleLogger() << " mx" << GetExprID();
}

void Conststr16MeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << "CONSTSTR16";
  LogInfo::MapleLogger() << " ";
  LogInfo::MapleLogger() << strIdx.GetIdx();
  LogInfo::MapleLogger() << " mx" << GetExprID();
}

void SizeoftypeMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOp()).name << " " << GetPrimTypeName(GetPrimType());
  LogInfo::MapleLogger() << " TYIDX:" << tyIdx.GetIdx();
  MIRType *mirType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  mirType->Dump(0);
  LogInfo::MapleLogger() << " mx" << GetExprID();
}

void FieldsDistMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOp()).name << " " << GetPrimTypeName(GetPrimType());
  LogInfo::MapleLogger() << " TYIDX:" << tyIdx.GetIdx();
  MIRType *mirType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  mirType->Dump(0);
  LogInfo::MapleLogger() << " (field)" << fieldID1;
  LogInfo::MapleLogger() << " (field)" << fieldID2;
  LogInfo::MapleLogger() << " mx" << GetExprID();
}

void AddrofMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << "ADDROF:";
  irMap->GetSSATab()->GetOriginalStFromID(ostIdx)->Dump();
  LogInfo::MapleLogger() << " (field)" << fieldID;
  LogInfo::MapleLogger() << " mx" << GetExprID();
}

void OpMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << "OP " << kOpcodeInfo.GetTableItemAt(GetOp()).name;
  LogInfo::MapleLogger() << " mx" << GetExprID();
  LogInfo::MapleLogger() << std::endl;
  ASSERT(opnds[0] != nullptr, "OpMeExpr::Dump: cannot have 0 operand");
  PrintIndentation(indent + 1);
  LogInfo::MapleLogger() << "opnd[0] = ";
  opnds[0]->Dump(irMap, indent + 1);
  if (opnds[1]) {
    LogInfo::MapleLogger() << std::endl;
  } else {
    return;
  }
  PrintIndentation(indent + 1);
  LogInfo::MapleLogger() << "opnd[1] = ";
  opnds[1]->Dump(irMap, indent + 1);
  if (opnds[2]) {
    LogInfo::MapleLogger() << std::endl;
  } else {
    return;
  }
  PrintIndentation(indent + 1);
  LogInfo::MapleLogger() << "opnd[2] = ";
  opnds[2]->Dump(irMap, indent + 1);
}

void IvarMeExpr::Dump(IRMap *irMap, int32 indent) const {
  LogInfo::MapleLogger() << "IVAR mx" << GetExprID();
  LogInfo::MapleLogger() << " " << GetPrimTypeName(GetPrimType());
  LogInfo::MapleLogger() << " TYIDX:" << tyIdx.GetIdx();
  MIRType *mirType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  mirType->Dump(0);
  LogInfo::MapleLogger() << " (field)" << fieldID << std::endl;
  PrintIndentation(indent + 1);
  LogInfo::MapleLogger() << "base = ";
  base->Dump(irMap, indent + 1);
  LogInfo::MapleLogger() << std::endl;
  PrintIndentation(indent + 1);
  LogInfo::MapleLogger() << "- MU: {";
  if (mu != nullptr) {
    mu->Dump(irMap);
  }
  LogInfo::MapleLogger() << "}";
}

void NaryMeExpr::Dump(IRMap *irMap, int32 indent) const {
  ASSERT(static_cast<size_t>(GetNumOpnds()) == opnds.size(), "array size error");
  if (GetOp() == OP_array) {
    LogInfo::MapleLogger() << "ARRAY ";
  } else if (GetOp() == OP_intrinsicop) {
    LogInfo::MapleLogger() << GetIntrinsicName(intrinsic);
  } else {
    ASSERT(GetOp() == OP_intrinsicopwithtype, "NaryMeExpr has bad GetOp()code");
    LogInfo::MapleLogger() << "INTRINOPWTY[" << intrinsic << "]";
  }
  LogInfo::MapleLogger() << " mx" << GetExprID() << std::endl;
  for (int32 i = 0; i < GetNumOpnds(); i++) {
    PrintIndentation(indent + 1);
    LogInfo::MapleLogger() << "opnd[" << i << "] = ";
    opnds[i]->Dump(irMap, indent + 1);
    if (i != GetNumOpnds() - 1) {
      LogInfo::MapleLogger() << std::endl;
    }
  }
}

MeExpr *DassignMeStmt::GetLHSRef(SSATab *ssatab, bool excludelocalrefvar) {
  VarMeExpr *l = GetVarLHS();
  ASSERT(l != nullptr, "null ptr check");
  if (l->GetPrimType() != PTY_ref) {
    return nullptr;
  }
  OriginalSt *ost = ssatab->GetOriginalStFromID(lhs->GetOStIdx());
  if (ost->IsIgnoreRC()) {
    return nullptr;
  }
  if (excludelocalrefvar && ost->IsLocal()) {
    return nullptr;
  }
  return l;
}

MeExpr *MaydassignMeStmt::GetLHSRef(SSATab *ssatab, bool excludelocalrefvar) {
  VarMeExpr *l = GetVarLHS();
  ASSERT(l != nullptr, "null ptr check");
  if (l->GetPrimType() != PTY_ref) {
    return nullptr;
  }
  OriginalSt *ost = ssatab->GetOriginalStFromID(l->GetOStIdx());
  if (ost->IsIgnoreRC()) {
    return nullptr;
  }
  if (excludelocalrefvar && ost->IsLocal()) {
    return nullptr;
  }
  return l;
}

MeExpr *IassignMeStmt::GetLHSRef(SSATab *ssatab, bool excludelocalrefvar) {
  MIRType *baseType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(lhsVar->GetTyIdx());
  ASSERT(baseType != nullptr, "null ptr check");
  MIRType *ptype = static_cast<MIRPtrType*>(baseType)->GetPointedType();
  MIRStructType *structType = dynamic_cast<MIRStructType*>(ptype);
  if (structType == nullptr) {
    if (dynamic_cast<MIRPtrType*>(ptype)) {
      if (lhsVar->GetFieldID() == 0) {
        if (static_cast<MIRPtrType*>(ptype)->GetPrimType() != PTY_ref) {
          return nullptr;
        }
      } else {
        MIRType *pptype = static_cast<MIRPtrType*>(ptype)->GetPointedType();
        TyIdx ftyidx = static_cast<MIRStructType*>(pptype)->GetFieldTyIdx(lhsVar->GetFieldID());
        if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(ftyidx)->GetPrimType() != PTY_ref) {
          return nullptr;
        }
      }
    } else if (ptype->GetKind() == kTypeJArray) {
      MIRType *pptype = static_cast<MIRPtrType*>(ptype)->GetPointedType();
      if (static_cast<MIRPtrType*>(pptype)->GetPrimType() != PTY_ref) {
        return nullptr;
      }
    } else {
      return nullptr;
    }
  } else {
    if (lhsVar->GetFieldID() == 0) {
      return nullptr;  // struct assign is not ref
    }
    if (structType->GetFieldType(lhsVar->GetFieldID())->GetPrimType() != PTY_ref) {
      return nullptr;
    }
  }
  return lhsVar;
}

VarMeExpr *AssignedPart::GetAssignedPartLHSRef(SSATab *ssatab, bool excludelocalrefvar) {
  if (mustDefList.empty()) {
    return nullptr;
  }
  MeExpr *assignedLHS = mustDefList.front().GetLHS();
  VarMeExpr *theLHS = dynamic_cast<VarMeExpr*>(assignedLHS);
  if (theLHS == nullptr) {
    return nullptr;
  }
  if (theLHS->GetPrimType() != PTY_ref) {
    return nullptr;
  }
  OriginalSt *ost = ssatab->GetOriginalStFromID(theLHS->GetOStIdx());
  if (ost->IsIgnoreRC()) {
    return nullptr;
  }
  if (excludelocalrefvar && ost->IsLocal()) {
    return nullptr;
  }
  return theLHS;
}

// default Dump
void MeStmt::Dump(IRMap *irMap) const {
  if (op == OP_comment) {
    return;
  }
  irMap->GetMIRModule()->GetOut() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(op).name << std::endl;
}

// get the real next mestmt that is not a comment
MeStmt *MeStmt::GetNextMeStmt() {
  MeStmt *nextMeStmt = next;
  while (nextMeStmt != nullptr && nextMeStmt->op == OP_comment) {
    nextMeStmt = nextMeStmt->next;
  }
  return nextMeStmt;
}

void DassignMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << " ";
  lhs->Dump(irMap);
  LogInfo::MapleLogger() << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << "rhs = ";
  rhs->Dump(irMap, kDefaultPrintIndentNum);
  if (needIncref) {
    LogInfo::MapleLogger() << " [RC+]";
  }
  if (needDecref) {
    LogInfo::MapleLogger() << " [RC-]";
  }
  LogInfo::MapleLogger() << std::endl;
  DumpChiList(irMap, chiList);
}

void RegassignMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << " ";
  lhs->Dump(irMap);
  LogInfo::MapleLogger() << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << "rhs = ";
  rhs->Dump(irMap, kDefaultPrintIndentNum);
  if (needIncref) {
    LogInfo::MapleLogger() << " [RC+]";
  }
  LogInfo::MapleLogger() << std::endl;
}

void MaydassignMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << "rhs = ";
  rhs->Dump(irMap, kDefaultPrintIndentNum);
  if (needIncref) {
    LogInfo::MapleLogger() << " [RC+]";
  }
  if (needDecref) {
    LogInfo::MapleLogger() << " [RC-]";
  }
  LogInfo::MapleLogger() << std::endl;
  DumpChiList(irMap, chiList);
}

void ChiMeNode::Dump(IRMap *irMap) const {
  VarMeExpr *melhs = static_cast<VarMeExpr*>(lhs);
  VarMeExpr *merhs = static_cast<VarMeExpr*>(rhs);
  CHECK_FATAL(melhs != nullptr, "Node doesn't have lhs?");
  CHECK_FATAL(merhs != nullptr, "Node doesn't have rhs?");
  if (!DumpOptions::GetSimpleDump()) {
    LogInfo::MapleLogger() << "VAR:";
    irMap->GetSSATab()->GetOriginalStFromID(melhs->GetOStIdx())->Dump();
  }
  LogInfo::MapleLogger() << " mx" << melhs->GetExprID() << " = CHI{";
  LogInfo::MapleLogger() << "mx" << merhs->GetExprID() << "}";
}

void DumpMuList(IRMap *irMap, const MapleMap<OStIdx, VarMeExpr*> &mulist, int32 indent) {
  if (mulist.empty()) {
    return;
  }
  int count = 0;
  LogInfo::MapleLogger() << "---- MULIST: { ";
  for (auto it = mulist.begin();;) {
    if (!DumpOptions::GetSimpleDump()) {
      (*it).second->Dump(irMap);
    } else {
      LogInfo::MapleLogger() << "mx" << (*it).second->GetExprID();
    }
    it++;
    if (it == mulist.end()) {
      break;
    } else {
      LogInfo::MapleLogger() << ", ";
    }
    if (DumpOptions::GetDumpVsyNum() > 0 && ++count >= DumpOptions::GetDumpVsyNum()) {
      LogInfo::MapleLogger() << " ... ";
      break;
    }
  }
  LogInfo::MapleLogger() << " }\n";
}

void DumpChiList(IRMap *irMap, const MapleMap<OStIdx, ChiMeNode*> &chilist) {
  if (chilist.empty()) {
    return;
  }
  int count = 0;
  LogInfo::MapleLogger() << "---- CHILIST: { ";
  for (auto it = chilist.begin();;) {
    it->second->Dump(irMap);
    it++;
    if (it == chilist.end()) {
      break;
    } else {
      LogInfo::MapleLogger() << ", ";
    }
    if (DumpOptions::GetDumpVsyNum() > 0 && count++ >= DumpOptions::GetDumpVsyNum()) {
      LogInfo::MapleLogger() << " ... ";
      break;
    }
  }
  LogInfo::MapleLogger() << " }\n";
}

void IassignMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << "lhs = ";
  lhsVar->Dump(irMap, kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << "rhs = ";
  rhs->Dump(irMap, kDefaultPrintIndentNum);
  if (needIncref) {
    LogInfo::MapleLogger() << " [RC+]";
  }
  if (needDecref) {
    LogInfo::MapleLogger() << " [RC-]";
  }
  LogInfo::MapleLogger() << std::endl;
  DumpChiList(irMap, chiList);
}

void NaryMeStmt::DumpOpnds(IRMap *irMap) const {
  for (size_t i = 0; i < opnds.size(); i++) {
    PrintIndentation(kDefaultPrintIndentNum);
    LogInfo::MapleLogger() << "opnd[" << i << "] = ";
    opnds[i]->Dump(irMap, kDefaultPrintIndentNum);
    LogInfo::MapleLogger() << std::endl;
  }
}

void NaryMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << " ";
  DumpOpnds(irMap);
}

void AssignedPart::DumpAssignedPart(IRMap *irMap) const {
  LogInfo::MapleLogger() << "    assignedpart: {";
  for (auto it = mustDefList.begin(); it != mustDefList.end(); it++) {
    const MeExpr *lhsvar = (*it).GetLHS();
    lhsvar->Dump(irMap);
  }
  if (needIncref) {
    LogInfo::MapleLogger() << " [RC+]";
  }
  if (needDecref) {
    LogInfo::MapleLogger() << " [RC-]";
  }
  LogInfo::MapleLogger() << "}\n";
}

void CallMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << " ";
  if (tyIdx != 0) {
    LogInfo::MapleLogger() << " TYIDX:" << tyIdx.GetIdx();
    MIRType *mirType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
    mirType->Dump(0);
  }
  // target function name
  MIRFunction *func = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(puIdx);
  LogInfo::MapleLogger() << NameMangler::DecodeName(func->GetName()) << std::endl;
  DumpOpnds(irMap);
  DumpMuList(irMap, muList, 0);
  DumpChiList(irMap, chiList);
  DumpAssignedPart(irMap);
}

void IcallMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << " ";
  LogInfo::MapleLogger() << " TYIDX:" << retTyIdx.GetIdx();
  DumpOpnds(irMap);
  DumpMuList(irMap, muList, 0);
  DumpChiList(irMap, chiList);
  DumpAssignedPart(irMap);
}

void IntrinsiccallMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << " ";
  LogInfo::MapleLogger() << "TYIDX:" << tyIdx.GetIdx();
  MIRType *mirType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  if (mirType != nullptr) {
    mirType->Dump(0);
  }
  LogInfo::MapleLogger() << GetIntrinsicName(intrinsic) << std::endl;
  DumpOpnds(irMap);
  DumpMuList(irMap, muList, 0);
  DumpChiList(irMap, chiList);
  DumpAssignedPart(irMap);
}

void RetMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << std::endl;
  DumpOpnds(irMap);
  DumpMuList(irMap, muList, 1);
}

void CondGotoMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << "cond: ";
  GetOpnd()->Dump(irMap, kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << std::endl;
}

void UnaryMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << " unaryopnd: ";
  opnd->Dump(irMap, kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << std::endl;
}

void SwitchMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << "switchOpnd: ";
  GetOpnd()->Dump(irMap, kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << std::endl;
}

void GosubMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << std::endl;
  DumpMuList(irMap, *GetMuList(), 0);
  LogInfo::MapleLogger() << std::endl;
}

void ThrowMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << "throwopnd: ";
  opnd->Dump(irMap, kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << std::endl;
  DumpMuList(irMap, *GetMuList(), 0);
}

void SyncMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << std::endl;
  DumpOpnds(irMap);
  DumpMuList(irMap, muList, 0);
  DumpChiList(irMap, chiList);
}

bool MeStmt::IsTheSameWorkcand(MeStmt *mestmt) const {
  if (op != mestmt->op) {
    return false;
  }
  if (op == OP_dassign) {
    if (this->GetVarLHS()->GetOStIdx() != mestmt->GetVarLHS()->GetOStIdx()) {
      return false;
    }
  } else if (op == OP_intrinsiccallwithtype) {
    if (static_cast<const IntrinsiccallMeStmt*>(this)->GetTyIdx() !=
        static_cast<IntrinsiccallMeStmt*>(mestmt)->GetTyIdx()) {
      return false;
    }
    if (static_cast<const IntrinsiccallMeStmt*>(this)->GetIntrinsic() !=
        static_cast<IntrinsiccallMeStmt*>(mestmt)->GetIntrinsic()) {
      return false;
    }
  } else if (op == OP_callassigned) {
    const CallMeStmt *thisCass = static_cast<const CallMeStmt*>(this);
    CallMeStmt *cass = static_cast<CallMeStmt*>(mestmt);
    if (thisCass->GetPUIdx() != cass->GetPUIdx()) {
      return false;
    }
    if (thisCass->MustDefListSize() != cass->MustDefListSize()) {
      return false;
    }
    if (thisCass->MustDefListSize() > 0) {
      const VarMeExpr *thisVarMeExpr = static_cast<const VarMeExpr*>(thisCass->GetAssignedLHS());
      const VarMeExpr *varMeExpr = static_cast<const VarMeExpr*>(cass->GetAssignedLHS());
      if (thisVarMeExpr->GetOStIdx() != varMeExpr->GetOStIdx()) {
        return false;
      }
    }
  }
  // check the operands
  for (size_t i = 0; i < NumMeStmtOpnds(); ++i) {
    ASSERT(GetOpnd(i) != nullptr, "null ptr check");
    if (!GetOpnd(i)->IsUseSameSymbol(mestmt->GetOpnd(i))) {
      return false;
    }
  }
  return true;
}

void AssertMeStmt::Dump(IRMap *irMap) const {
  LogInfo::MapleLogger() << "||MEIR|| " << kOpcodeInfo.GetTableItemAt(GetOp()).name << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << "opnd[0] = ";
  opnds[0]->Dump(irMap, kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << std::endl;
  PrintIndentation(kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << "opnd[1] = ";
  opnds[1]->Dump(irMap, kDefaultPrintIndentNum);
  LogInfo::MapleLogger() << std::endl;
}

BB *VarMeExpr::DefByBB() {
  switch (defBy) {
    case kDefByNo:
      return nullptr;
    case kDefByStmt:
      ASSERT(def.defStmt, "VarMeExpr::DefByBB: defStmt cannot be nullptr");
      return def.defStmt->GetBB();
    case kDefByPhi:
      ASSERT(def.defPhi, "VarMeExpr::DefByBB: defPhi cannot be nullptr");
      return def.defPhi->GetDefBB();
    case kDefByChi: {
      ASSERT(def.defChi, "VarMeExpr::DefByBB: defChi cannot be nullptr");
      ASSERT(def.defChi->GetBase(), "VarMeExpr::DefByBB: defChi->base cannot be nullptr");
      return def.defChi->GetBase()->GetBB();
    }
    case kDefByMustDef: {
      ASSERT(def.defMustDef, "VarMeExpr::DefByBB: defMustDef cannot be nullptr");
      ASSERT(def.defMustDef->GetBase(), "VarMeExpr::DefByBB: defMustDef->base cannot be nullptr");
      return def.defMustDef->GetBase()->GetBB();
    }
    default:
      ASSERT(false, "var define unknown");
      return nullptr;
  }
}

bool VarMeExpr::IsVolatile(SSATab *ssatab) {
  OriginalSt *ost = ssatab->GetOriginalStFromID(ostIdx);
  if (!ost->IsSymbolOst()) {
    return false;
  }
  MIRSymbol *sym = ost->GetMIRSymbol();
  if (sym->IsVolatile()) {
    return true;
  }
  MIRType *ty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(sym->GetTyIdx());
  if (fieldID == 0) {
    return (ty->HasVolatileField());
  }
  MIRStructType *structType = static_cast<MIRStructType*>(ty);
  return structType->IsFieldVolatile(fieldID);
}

MeExpr *MeExpr::FindSymAppearance(OStIdx oidx) {
  if (meOp == kMeOpVar) {
    if (static_cast<VarMeExpr*>(this)->GetOStIdx() == oidx) {
      return this;
    }
    return nullptr;
  }
  for (uint8 i = 0; i < GetNumOpnds(); i++) {
    MeExpr *retx = GetOpnd(i)->FindSymAppearance(oidx);
    if (retx != nullptr) {
      return retx;
    }
  }
  return nullptr;
}

bool MeExpr::SymAppears(OStIdx oidx) {
  return FindSymAppearance(oidx) != nullptr;
}

bool MeExpr::HasIvar() const {
  if (meOp == kMeOpIvar) {
    return true;
  }
  for (uint8 i = 0; i < GetNumOpnds(); i++) {
    ASSERT(GetOpnd(i) != nullptr, "null ptr check");
    if (GetOpnd(i)->HasIvar()) {
      return true;
    }
  }
  return false;
}


// check if MeExpr can be a pointer to something that requires incref for its
// assigned target
bool MeExpr::PointsToSomethingThatNeedsIncRef() {
  if (op == OP_retype) {
    return true;
  }
  if (meOp == kMeOpVar || meOp == kMeOpIvar) {
    return true;
  }
  if (meOp == kMeOpReg) {
    RegMeExpr *r = static_cast<RegMeExpr*>(this);
    return r->GetRegIdx() != -kSregThrownval;
  }
  return false;
}

MapleMap<OStIdx, ChiMeNode*> *GenericGetChiListFromVarMeExprInner(VarMeExpr *expr,
                                                                   std::unordered_set<VarMeExpr*> &visited) {
  if (expr == nullptr || expr->GetDefBy() == kDefByNo || visited.find(expr) != visited.end()) {
    return nullptr;
  }
  visited.insert(expr);
  if (expr->GetDefBy() == kDefByPhi) {
    MeVarPhiNode *phime = expr->GetDefPhi();
    MapleVector<VarMeExpr*> &phiopnds = phime->GetOpnds();
    for (auto it = phiopnds.begin(); it != phiopnds.end(); it++) {
      VarMeExpr *meexpr = *it;
      MapleMap<OStIdx, ChiMeNode*> *chiList = GenericGetChiListFromVarMeExprInner(meexpr, visited);
      if (chiList != nullptr) {
        return chiList;
      }
    }
  } else if (expr->GetDefBy() == kDefByChi) {
    return expr->GetDefChi()->GetBase()->GetChiList();
  } else {
    // NYI
    return nullptr;
  }
  return nullptr;
}

MapleMap<OStIdx, ChiMeNode*> *GenericGetChiListFromVarMeExpr(VarMeExpr *expr) {
  std::unordered_set<VarMeExpr*> visited;
  return GenericGetChiListFromVarMeExprInner(expr, visited);
}

void MeStmt::SetCallReturn(MeExpr *curexpr) {
  ASSERT(GetMustDefList() != nullptr, "null ptr check");
  MustDefMeNode &mustDefMeNode = GetMustDefList()->front();
  mustDefMeNode.UpdateLHS(curexpr);
}

bool DumpOptions::simpleDump = false;
int DumpOptions::dumpVsymNum = 0;
}  // namespace maple
