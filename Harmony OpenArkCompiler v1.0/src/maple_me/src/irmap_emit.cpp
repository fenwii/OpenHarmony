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
// This file contains methods to emit Maple IR nodes from MeExpr/MeStmt
#include "me_ir.h"
#include "irmap.h"
#include "mir_builder.h"
#include "orig_symbol.h"

namespace maple {
bool VarMeExpr::IsValidVerIdx(SSATab *ssaTab) {
  OriginalSt *ost = ssaTab->GetOriginalStFromID(ostIdx);
  if (ost == nullptr || !ost->IsSymbolOst()) {
    return false;
  }
  StIdx stIdx = ost->GetMIRSymbol()->GetStIdx();
  return stIdx.Islocal() ? ssaTab->mirModule.CurFunction()->GetSymTab()->IsValidIdx(stIdx.Idx())
                         : GlobalTables::GetGsymTable().IsValidIdx(stIdx.Idx());
}

BaseNode *VarMeExpr::EmitExpr(SSATab *ssaTab) {
  MIRSymbol *symbol = ssaTab->GetMIRSymbolFromID(GetOStIdx());
  if (symbol->IsLocal()) {
    symbol->ResetIsDeleted();
  }
  AddrofNode *addrofNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<AddrofNode>(
      OP_dread, PrimType(GetPrimType()), symbol->GetStIdx(), GetFieldID());
  ASSERT(addrofNode->GetPrimType() != kPtyInvalid, "runtime check error");
  ASSERT(IsValidVerIdx(ssaTab), "runtime check error");
  return addrofNode;
}

BaseNode *RegMeExpr::EmitExpr(SSATab *ssaTab) {
  RegreadNode *regRead = ssaTab->mirModule.CurFunction()->GetCodeMemPool()->New<RegreadNode>();
  regRead->SetPrimType(GetPrimType());
  regRead->SetRegIdx(regIdx);
  ASSERT(regIdx < 0 ||
         static_cast<uint32>(static_cast<int32>(regIdx)) < ssaTab->mirModule.CurFunction()->GetPregTab()->Size(),
         "RegMeExpr::EmitExpr: pregIdx exceeds preg table size");
  return regRead;
}

BaseNode *ConstMeExpr::EmitExpr(SSATab *ssaTab) {
  ConstvalNode *exprConst =
      ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<ConstvalNode>(PrimType(GetPrimType()), constVal);
  // if int const has been promoted from dyn int const, remove the type tag
  if (IsPrimitiveInteger(exprConst->GetPrimType())) {
    MIRIntConst *intConst = static_cast<MIRIntConst*>(exprConst->GetConstVal());
    intConst->SetValue(intConst->GetValueUnderType());
  }
  return exprConst;
}

BaseNode *ConststrMeExpr::EmitExpr(SSATab *ssaTab) {
  ConststrNode *exprConst =
      ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<ConststrNode>(PrimType(GetPrimType()), strIdx);
  return exprConst;
}

BaseNode *Conststr16MeExpr::EmitExpr(SSATab *ssaTab) {
  Conststr16Node *exprConst =
      ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<Conststr16Node>(PrimType(GetPrimType()), strIdx);
  return exprConst;
}

BaseNode *SizeoftypeMeExpr::EmitExpr(SSATab *ssaTab) {
  SizeoftypeNode *exprSizeoftype =
      ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<SizeoftypeNode>(PrimType(GetPrimType()), tyIdx);
  return exprSizeoftype;
}

BaseNode *FieldsDistMeExpr::EmitExpr(SSATab *ssaTab) {
  FieldsDistNode *exprSizeoftype = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<FieldsDistNode>(
      PrimType(GetPrimType()), tyIdx, fieldID1, fieldID2);
  return exprSizeoftype;
}

BaseNode *AddrofMeExpr::EmitExpr(SSATab *ssaTab) {
  MIRSymbol *symbol = ssaTab->GetMIRSymbolFromID(ostIdx);
  if (symbol->IsLocal()) {
    symbol->ResetIsDeleted();
  }
  AddrofNode *addrofNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<AddrofNode>(
      OP_addrof, PrimType(GetPrimType()), symbol->GetStIdx(), fieldID);
  return addrofNode;
}

BaseNode *AddroffuncMeExpr::EmitExpr(SSATab *ssaTab) {
  AddroffuncNode *addroffuncNode =
      ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<AddroffuncNode>(PrimType(GetPrimType()), puIdx);
  return addroffuncNode;
}

BaseNode *GcmallocMeExpr::EmitExpr(SSATab *ssaTab) {
  GCMallocNode *gcmallocNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<GCMallocNode>(
      Opcode(GetOp()), PrimType(GetPrimType()), tyIdx);
  return gcmallocNode;
}

BaseNode *OpMeExpr::EmitExpr(SSATab *ssaTab) {
  switch (GetOp()) {
    case OP_add:
    case OP_ashr:
    case OP_band:
    case OP_bior:
    case OP_bxor:
    case OP_div:
    case OP_land:
    case OP_lior:
    case OP_lshr:
    case OP_max:
    case OP_min:
    case OP_mul:
    case OP_rem:
    case OP_shl:
    case OP_sub: {
      BinaryNode *binaryNode =
          ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<BinaryNode>(Opcode(GetOp()), PrimType(GetPrimType()));
      binaryNode->SetBOpnd(opnds[0]->EmitExpr(ssaTab), 0);
      binaryNode->SetBOpnd(opnds[1]->EmitExpr(ssaTab), 1);
      return binaryNode;
    }
    case OP_eq:
    case OP_ne:
    case OP_lt:
    case OP_gt:
    case OP_le:
    case OP_ge:
    case OP_cmpl:
    case OP_cmpg:
    case OP_cmp: {
      CompareNode *cmpNode =
          ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<CompareNode>(Opcode(GetOp()), PrimType(GetPrimType()));
      cmpNode->SetBOpnd(opnds[0]->EmitExpr(ssaTab), 0);
      cmpNode->SetBOpnd(opnds[1]->EmitExpr(ssaTab), 1);
      cmpNode->SetOpndType(opndType);
      return cmpNode;
    }
    case OP_abs:
    case OP_bnot:
    case OP_lnot:
    case OP_neg:
    case OP_recip:
    case OP_sqrt:
    case OP_alloca:
    case OP_malloc: {
      UnaryNode *unaryNode =
          ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<UnaryNode>(Opcode(GetOp()), PrimType(GetPrimType()));
      unaryNode->SetOpnd(opnds[0]->EmitExpr(ssaTab));
      return unaryNode;
    }
    case OP_sext:
    case OP_zext:
    case OP_extractbits: {
      ExtractbitsNode *unode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<ExtractbitsNode>(
          Opcode(GetOp()), PrimType(GetPrimType()));
      unode->SetOpnd(opnds[0]->EmitExpr(ssaTab));
      unode->SetBitsOffset(bitsOffset);
      unode->SetBitsSize(bitsSize);
      return unode;
    }
    case OP_select: {
      TernaryNode *ternaryNode =
          ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<TernaryNode>(Opcode(GetOp()), PrimType(GetPrimType()));
      ternaryNode->SetOpnd(opnds[0]->EmitExpr(ssaTab), 0);
      ternaryNode->SetOpnd(opnds[1]->EmitExpr(ssaTab), 1);
      ternaryNode->SetOpnd(opnds[2]->EmitExpr(ssaTab), 2);
      return ternaryNode;
    }
    case OP_ceil:
    case OP_cvt:
    case OP_floor:
    case OP_trunc: {
      TypeCvtNode *cvtNode =
          ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<TypeCvtNode>(Opcode(GetOp()), PrimType(GetPrimType()));
      cvtNode->SetOpnd(opnds[0]->EmitExpr(ssaTab));
      cvtNode->SetFromType(opndType);
      return cvtNode;
    }
    case OP_retype: {
      RetypeNode *cvtNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<RetypeNode>(PrimType(GetPrimType()));
      cvtNode->SetOpnd(opnds[0]->EmitExpr(ssaTab));
      cvtNode->SetFromType(opndType);
      cvtNode->SetTyIdx(tyIdx);
      return cvtNode;
    }
    case OP_gcmallocjarray:
    case OP_gcpermallocjarray: {
      JarrayMallocNode *arrayMalloc = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<JarrayMallocNode>(
          Opcode(GetOp()), PrimType(GetPrimType()));
      arrayMalloc->SetOpnd(opnds[0]->EmitExpr(ssaTab));
      arrayMalloc->SetTyIdx(tyIdx);
      return arrayMalloc;
    }
    case OP_resolveinterfacefunc:
    case OP_resolvevirtualfunc: {
      ResolveFuncNode *resolveNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<ResolveFuncNode>(
          Opcode(GetOp()), PrimType(GetPrimType()));
      resolveNode->SetBOpnd(opnds[0]->EmitExpr(ssaTab), 0);
      resolveNode->SetBOpnd(opnds[1]->EmitExpr(ssaTab), 1);
      resolveNode->SetPuIdx(fieldID);
      return resolveNode;
    }
    case OP_iaddrof: {
      IaddrofNode *iaddrof =
          ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<IaddrofNode>(OP_iaddrof, PrimType(GetPrimType()));
      iaddrof->SetOpnd(opnds[0]->EmitExpr(ssaTab));
      iaddrof->SetTyIdx(tyIdx);
      iaddrof->SetFieldID(fieldID);
      return iaddrof;
    }
    default:
      ASSERT(false, "unexpected op");
      return nullptr;
  }
}

BaseNode *NaryMeExpr::EmitExpr(SSATab *ssaTab) {
  BaseNode *nodeToReturn = nullptr;
  NaryOpnds *nopndPart = nullptr;
  if (GetOp() == OP_array) {
    ArrayNode *arrayNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<ArrayNode>(
        &(ssaTab->mirModule), PrimType(GetPrimType()), tyIdx);
    arrayNode->SetNumOpnds(GetNumOpnds());
    arrayNode->SetBoundsCheck(GetBoundCheck());
    nopndPart = arrayNode;
    nodeToReturn = arrayNode;
  } else {
    IntrinsicopNode *intrinNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<IntrinsicopNode>(
        &(ssaTab->mirModule), GetOp(), PrimType(GetPrimType()), tyIdx);
    intrinNode->SetNumOpnds(GetNumOpnds());
    intrinNode->SetIntrinsic(intrinsic);
    nopndPart = intrinNode;
    nodeToReturn = intrinNode;
  }
  for (auto it = GetOpnds().begin(); it != GetOpnds().end(); it++) {
    nopndPart->GetNopnd().push_back((*it)->EmitExpr(ssaTab));
  }
  return nodeToReturn;
}

BaseNode *IvarMeExpr::EmitExpr(SSATab *ssaTab) {
  IreadNode *ireadNode =
      ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<IreadNode>(OP_iread, PrimType(GetPrimType()));
  ireadNode->SetOpnd(base->EmitExpr(ssaTab));
  ireadNode->SetFieldID(fieldID);
  ireadNode->SetTyIdx(tyIdx);
  ASSERT(ireadNode->GetPrimType() != kPtyInvalid, "");
  ASSERT(tyIdx != 0, "wrong tyIdx for iread node in me emit");
  ireadNode->SetTyIdx(tyIdx);
  return ireadNode;
}

StmtNode *MeStmt::EmitStmt(SSATab *ssaTab) {
  StmtNode *stmt = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<StmtNode>(Opcode(GetOp()));
  stmt->SetSrcPos(GetSrcPosition());
  return stmt;
}

StmtNode *DassignMeStmt::EmitStmt(SSATab *ssaTab) {
  DassignNode *dassignStmt = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<DassignNode>();
  MIRSymbol *symbol = ssaTab->GetMIRSymbolFromID(GetVarLHS()->GetOStIdx());
  if (symbol->IsLocal()) {
    symbol->ResetIsDeleted();
  }
  dassignStmt->SetStIdx(symbol->GetStIdx());
  dassignStmt->SetFieldID(GetVarLHS()->GetFieldID());
  dassignStmt->SetRHS(GetRHS()->EmitExpr(ssaTab));
  dassignStmt->SetSrcPos(GetSrcPosition());
  return dassignStmt;
}

StmtNode *RegassignMeStmt::EmitStmt(SSATab *ssaTab) {
  RegassignNode *regassignStmt = ssaTab->mirModule.GetMIRBuilder()->CreateStmtRegassign(
      lhs->GetPrimType(), lhs->GetRegIdx(), rhs->EmitExpr(ssaTab));
  regassignStmt->SetSrcPos(GetSrcPosition());
  return regassignStmt;
}

StmtNode *MaydassignMeStmt::EmitStmt(SSATab *ssaTab) {
  DassignNode *dassignStmt = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<DassignNode>();
  MIRSymbol *symbol = mayDSSym->GetMIRSymbol();
  if (symbol->IsLocal()) {
    symbol->ResetIsDeleted();
  }
  dassignStmt->SetStIdx(symbol->GetStIdx());
  dassignStmt->SetFieldID(fieldID);
  dassignStmt->SetRHS(rhs->EmitExpr(ssaTab));
  dassignStmt->SetSrcPos(GetSrcPosition());
  return dassignStmt;
}

void MeStmt::EmitCallReturnVector(SSATab *ssaTab, CallReturnVector *nrets) {
  MapleVector<MustDefMeNode> *mustDefs = GetMustDefList();
  if (mustDefs == nullptr || mustDefs->empty()) {
    return;
  }
  MeExpr *meExpr = mustDefs->front().GetLHS();
  if (meExpr->GetMeOp() == kMeOpVar) {
    OriginalSt *ost = ssaTab->GetOriginalStFromID(static_cast<VarMeExpr*>(meExpr)->GetOStIdx());
    MIRSymbol *symbol = ost->GetMIRSymbol();
    nrets->push_back(CallReturnPair(symbol->GetStIdx(), RegFieldPair(0, 0)));
  } else if (meExpr->GetMeOp() == kMeOpReg) {
    nrets->push_back(CallReturnPair(StIdx(), RegFieldPair(0, static_cast<RegMeExpr*>(meExpr)->GetRegIdx())));
  }
}

StmtNode *IassignMeStmt::EmitStmt(SSATab *ssaTab) {
  IassignNode *iassignNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<IassignNode>();
  iassignNode->SetTyIdx(tyIdx);
  iassignNode->SetFieldID(lhsVar->GetFieldID());
  iassignNode->SetAddrExpr(lhsVar->GetBase()->EmitExpr(ssaTab));
  iassignNode->SetRHS(rhs->EmitExpr(ssaTab));
  iassignNode->SetSrcPos(GetSrcPosition());
  return iassignNode;
}

StmtNode *CallMeStmt::EmitStmt(SSATab *ssaTab) {
  if (GetOp() != OP_icall && GetOp() != OP_icallassigned) {
    CallNode *callNode =
        ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<CallNode>(&(ssaTab->mirModule), Opcode(GetOp()));
    callNode->SetPUIdx(puIdx);
    callNode->SetTyIdx(tyIdx);
    callNode->GetNopnd().resize(NumMeStmtOpnds());
    for (size_t i = 0; i < NumMeStmtOpnds(); i++) {
      callNode->SetOpnd(GetOpnd(i)->EmitExpr(ssaTab), i);
    }
    callNode->SetNumOpnds(callNode->GetNopndSize());
    callNode->SetSrcPos(GetSrcPosition());
    if (kOpcodeInfo.IsCallAssigned(GetOp())) {
      EmitCallReturnVector(ssaTab, &callNode->GetReturnVec());
      for (size_t j = 0; j < callNode->GetReturnVec().size(); j++) {
        CallReturnPair retPair = callNode->GetReturnVec()[j];
        if (!retPair.second.IsReg()) {
          StIdx stIdx = retPair.first;
          if (stIdx.Islocal()) {
            MIRSymbolTable *symbolTab = ssaTab->mirModule.CurFunction()->GetSymTab();
            MIRSymbol *symbol = symbolTab->GetSymbolFromStIdx(stIdx.Idx());
            symbol->ResetIsDeleted();
          }
        }
      }
    }
    return callNode;
  } else {
    IcallNode *icallNode =
        ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<IcallNode>(&(ssaTab->mirModule), Opcode(GetOp()));
    icallNode->GetNopnd().resize(NumMeStmtOpnds());
    for (size_t i = 0; i < NumMeStmtOpnds(); i++) {
      icallNode->SetOpnd(GetOpnd(i)->EmitExpr(ssaTab), i);
    }
    icallNode->SetNumOpnds(icallNode->GetNopndSize());
    icallNode->SetSrcPos(GetSrcPosition());
    if (kOpcodeInfo.IsCallAssigned(GetOp())) {
      EmitCallReturnVector(ssaTab, &icallNode->GetReturnVec());
      icallNode->SetRetTyIdx(TyIdx(PTY_void));
      for (size_t j = 0; j < icallNode->GetReturnVec().size(); j++) {
        CallReturnPair retPair = icallNode->GetReturnVec()[j];
        if (!retPair.second.IsReg()) {
          StIdx stIdx = retPair.first;
          MIRSymbolTable *symbolTab = ssaTab->mirModule.CurFunction()->GetSymTab();
          MIRSymbol *symbol = symbolTab->GetSymbolFromStIdx(stIdx.Idx());
          icallNode->SetRetTyIdx(symbol->GetType()->GetTypeIndex());
          if (stIdx.Islocal()) {
            symbol->ResetIsDeleted();
          }
        } else {
          PregIdx pregIdx = (PregIdx)retPair.second.GetPregIdx();
          MIRPreg *preg = ssaTab->mirModule.CurFunction()->GetPregTab()->PregFromPregIdx(pregIdx);
          icallNode->SetRetTyIdx(TyIdx(preg->GetPrimType()));
        }
      }
    }
    return icallNode;
  }
}

StmtNode *IcallMeStmt::EmitStmt(SSATab *ssaTab) {
  IcallNode *icallNode =
      ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<IcallNode>(&(ssaTab->mirModule), Opcode(GetOp()));
  icallNode->GetNopnd().resize(NumMeStmtOpnds());
  for (size_t i = 0; i < NumMeStmtOpnds(); i++) {
    icallNode->SetOpnd(GetOpnd(i)->EmitExpr(ssaTab), i);
  }
  icallNode->SetNumOpnds(icallNode->GetNopndSize());
  icallNode->SetSrcPos(GetSrcPosition());
  if (kOpcodeInfo.IsCallAssigned(GetOp())) {
    EmitCallReturnVector(ssaTab, &icallNode->GetReturnVec());
    icallNode->SetRetTyIdx(TyIdx(PTY_void));
    for (size_t j = 0; j < icallNode->GetReturnVec().size(); j++) {
      CallReturnPair retPair = icallNode->GetReturnVec()[j];
      if (!retPair.second.IsReg()) {
        StIdx stIdx = retPair.first;
        MIRSymbolTable *symbolTab = ssaTab->mirModule.CurFunction()->GetSymTab();
        MIRSymbol *symbol = symbolTab->GetSymbolFromStIdx(stIdx.Idx());
        icallNode->SetRetTyIdx(symbol->GetType()->GetTypeIndex());
        if (stIdx.Islocal()) {
          symbol->ResetIsDeleted();
        }
      } else {
        PregIdx pregIdx = (PregIdx)retPair.second.GetPregIdx();
        MIRPreg *preg = ssaTab->mirModule.CurFunction()->GetPregTab()->PregFromPregIdx(pregIdx);
        icallNode->SetRetTyIdx(TyIdx(preg->GetPrimType()));
      }
    }
  }
  return icallNode;
}

StmtNode *IntrinsiccallMeStmt::EmitStmt(SSATab *ssaTab) {
  IntrinsiccallNode *callNode =
      ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<IntrinsiccallNode>(&(ssaTab->mirModule), Opcode(GetOp()));
  callNode->SetIntrinsic(intrinsic);
  callNode->SetTyIdx(tyIdx);
  callNode->GetNopnd().resize(NumMeStmtOpnds());
  for (size_t i = 0; i < NumMeStmtOpnds(); i++) {
    callNode->SetOpnd(GetOpnd(i)->EmitExpr(ssaTab), i);
  }
  callNode->SetNumOpnds(callNode->GetNopndSize());
  callNode->SetSrcPos(GetSrcPosition());
  if (kOpcodeInfo.IsCallAssigned(GetOp())) {
    EmitCallReturnVector(ssaTab, &callNode->GetReturnVec());
    for (size_t j = 0; j < callNode->GetReturnVec().size(); j++) {
      CallReturnPair retPair = callNode->GetReturnVec()[j];
      if (!retPair.second.IsReg()) {
        StIdx stIdx = retPair.first;
        if (stIdx.Islocal()) {
          MIRSymbolTable *symbolTab = ssaTab->mirModule.CurFunction()->GetSymTab();
          MIRSymbol *symbol = symbolTab->GetSymbolFromStIdx(stIdx.Idx());
          symbol->ResetIsDeleted();
        }
      }
    }
  }
  return callNode;
}

StmtNode *NaryMeStmt::EmitStmt(SSATab *ssaTab) {
  NaryStmtNode *naryStmt =
      ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<NaryStmtNode>(&(ssaTab->mirModule), Opcode(GetOp()));
  naryStmt->GetNopnd().resize(NumMeStmtOpnds());
  for (size_t i = 0; i < NumMeStmtOpnds(); i++) {
    naryStmt->SetOpnd(opnds[i]->EmitExpr(ssaTab), i);
  }
  naryStmt->SetNumOpnds(naryStmt->GetNopndSize());
  naryStmt->SetSrcPos(GetSrcPosition());
  return naryStmt;
}

StmtNode *UnaryMeStmt::EmitStmt(SSATab *ssaTab) {
  UnaryStmtNode *unaryStmt = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<UnaryStmtNode>(Opcode(GetOp()));
  unaryStmt->SetOpnd(opnd->EmitExpr(ssaTab), 0);
  unaryStmt->SetSrcPos(GetSrcPosition());
  if (GetNotNeedLock()) {
    ssaTab->mirModule.GetRcNoNeedingLock().insert(unaryStmt->GetStmtID());
  }
  return unaryStmt;
}

StmtNode *GotoMeStmt::EmitStmt(SSATab *ssaTab) {
  GotoNode *gotoNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<GotoNode>(OP_goto);
  gotoNode->SetOffset(offset);
  gotoNode->SetSrcPos(GetSrcPosition());
  return gotoNode;
}

StmtNode *CondGotoMeStmt::EmitStmt(SSATab *ssaTab) {
  CondGotoNode *cgNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<CondGotoNode>(Opcode(GetOp()));
  cgNode->SetOffset(offset);
  cgNode->SetOpnd(GetOpnd()->EmitExpr(ssaTab));
  cgNode->SetSrcPos(GetSrcPosition());
  return cgNode;
}

StmtNode *JsTryMeStmt::EmitStmt(SSATab *ssaTab) {
  JsTryNode *jtNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<JsTryNode>();
  jtNode->SetCatchOffset(catchOffset);
  jtNode->SetFinallyOffset(finallyOffset);
  jtNode->SetSrcPos(GetSrcPosition());
  return jtNode;
}

StmtNode *TryMeStmt::EmitStmt(SSATab *ssaTab) {
  TryNode *tryNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<TryNode>(&(ssaTab->mirModule));
  tryNode->ResizeOffsets(offsets.size());
  for (size_t i = 0; i < offsets.size(); i++) {
    tryNode->SetOffset(offsets[i], i);
  }
  tryNode->SetSrcPos(GetSrcPosition());
  return tryNode;
}

StmtNode *CatchMeStmt::EmitStmt(SSATab *ssaTab) {
  CatchNode *catchNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<CatchNode>(&(ssaTab->mirModule));
  catchNode->SetExceptionTyIdxVec(exceptionTyIdxVec);
  catchNode->SetSrcPos(GetSrcPosition());
  return catchNode;
}

StmtNode *SwitchMeStmt::EmitStmt(SSATab *ssaTab) {
  SwitchNode *switchNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<SwitchNode>(&(ssaTab->mirModule));
  switchNode->SetDefaultLabel(defaultLabel);
  switchNode->SetSwitchTable(switchTable);
  switchNode->SetSwitchOpnd(GetOpnd()->EmitExpr(ssaTab));
  switchNode->SetSrcPos(GetSrcPosition());
  return switchNode;
}

StmtNode *CommentMeStmt::EmitStmt(SSATab *ssaTab) {
  CommentNode *commentNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<CommentNode>(&(ssaTab->mirModule));
  commentNode->SetComment(comment);
  commentNode->SetSrcPos(GetSrcPosition());
  return commentNode;
}

StmtNode *ThrowMeStmt::EmitStmt(SSATab *ssaTab) {
  UnaryStmtNode *unaryStmt = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<UnaryStmtNode>(OP_throw);
  unaryStmt->SetOpnd(opnd->EmitExpr(ssaTab), 0);
  unaryStmt->SetSrcPos(GetSrcPosition());
  return unaryStmt;
}

StmtNode *GosubMeStmt::EmitStmt(SSATab *ssaTab) {
  GotoNode *gosubNode = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<GotoNode>(OP_gosub);
  gosubNode->SetOffset(offset);
  gosubNode->SetSrcPos(GetSrcPosition());
  return gosubNode;
}

StmtNode *AssertMeStmt::EmitStmt(SSATab *ssaTab) {
  AssertStmtNode *assertStmt = ssaTab->mirModule.CurFunction()->GetCodeMempool()->New<AssertStmtNode>(Opcode(GetOp()));
  assertStmt->SetBOpnd(opnds[0]->EmitExpr(ssaTab), 0);
  assertStmt->SetBOpnd(opnds[1]->EmitExpr(ssaTab), 1);
  assertStmt->SetSrcPos(GetSrcPosition());
  return assertStmt;
}

}  // namespace maple
