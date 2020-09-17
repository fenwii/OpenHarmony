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
#include "vtable_impl.h"
#include "vtable_analysis.h"
#include "itab_util.h"
#include "reflection_analysis.h"

// This phase is mainly to lower interfacecall into icall

namespace maple {
VtableImpl::VtableImpl(MIRModule *mod, KlassHierarchy *kh, bool dump) : FuncOptimizeImpl(mod, kh, dump) {
  mccItabFunc = builder->GetOrCreateFunction(kInterfaceMethod, TyIdx(PTY_ptr));
  mccItabFunc->SetAttr(FUNCATTR_nosideeffect);
  mirModule = mod;
  klassHierarchy = kh;
}

void VtableImpl::ProcessFunc(MIRFunction *func) {
  if (func->IsEmpty()) {
    return;
  }
  SetCurrentFunction(func);
  StmtNode *stmt = func->GetBody()->GetFirst();
  StmtNode *next = nullptr;
  while (stmt != nullptr) {
    next = stmt->GetNext();
    Opcode opcode = stmt->GetOpCode();
    switch (opcode) {
      case OP_regassign: {
        RegassignNode *regassign = static_cast<RegassignNode*>(stmt);
        BaseNode *rhs = regassign->Opnd();
        if (rhs->GetOpCode() == maple::OP_resolveinterfacefunc) {
          ReplaceResolveInterface(stmt, static_cast<ResolveFuncNode*>(rhs));
        }
        break;
      }
      case OP_interfaceicallassigned:
      case OP_virtualicallassigned: {
        CallNode *callNode = static_cast<CallNode*>(stmt);
        MIRFunction *callee = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(callNode->GetPUIdx());
        MemPool *currentFuncCodeMempool = builder->GetCurrentFuncCodeMp();
        IcallNode *icallNode =
            currentFuncCodeMempool->New<IcallNode>(builder->GetCurrentFuncCodeMpAllocator(), OP_icallassigned);
        icallNode->SetReturnVec(callNode->GetReturnVec());
        icallNode->SetRetTyIdx(callee->GetReturnTyIdx());
        icallNode->SetSrcPos(callNode->GetSrcPos());
        icallNode->GetNopnd().resize(callNode->GetNopndSize());
        icallNode->SetNumOpnds(icallNode->GetNopndSize());
        for (size_t i = 0; i < callNode->GetNopndSize(); i++) {
          icallNode->SetOpnd(callNode->GetNopndAt(i)->CloneTree(builder->GetCurrentFuncCodeMpAllocator()), i);
        }
        currFunc->GetBody()->ReplaceStmt1WithStmt2(stmt, icallNode);
        stmt = icallNode;
        // Fall-through
      }
      case OP_icallassigned: {
        IcallNode *icall = static_cast<IcallNode*>(stmt);
        BaseNode *firstParm = icall->GetNopndAt(0);
        if (firstParm->GetOpCode() == maple::OP_resolveinterfacefunc) {
          ReplaceResolveInterface(stmt, static_cast<ResolveFuncNode*>(firstParm));
        }
        break;
      }
      case OP_virtualcall:
      case OP_virtualcallassigned: {
        CHECK_FATAL(false, "VtableImpl::ProcessFunc does not expect to see virtucalcall");
        break;
      }
      case OP_interfacecall:
      case OP_interfacecallassigned: {
        CHECK_FATAL(false, "VtableImpl::ProcessFunc does not expect to see interfacecall");
        break;
      }
      case OP_superclasscallassigned: {
        CHECK_FATAL(false, "VtableImpl::ProcessFunc does not expect to see supercall");
        break;
      }
      default:
        break;
    }
    stmt = next;
  }
  if (trace) {
    func->Dump(false);
  }
}


void VtableImpl::ReplaceResolveInterface(StmtNode *stmt, const ResolveFuncNode *resolveNode) {
  std::string signature = VtableAnalysis::DecodeBaseNameWithType(
      GlobalTables::GetFunctionTable().GetFunctionFromPuidx(resolveNode->GetPuIdx()));
  int64 hashCode = GetHashIndex(signature.c_str());
  PregIdx pregItabAddress = currFunc->GetPregTab()->CreatePreg(PTY_ptr);
  RegassignNode *itabAddressAssign =
      builder->CreateStmtRegassign(PTY_ptr, pregItabAddress, resolveNode->GetTabBaseAddr());
  currFunc->GetBody()->InsertBefore(stmt, itabAddressAssign);
  // read funcvalue
  MIRType *compactPtrType = GlobalTables::GetTypeTable().GetCompactPtr();
  PrimType compactPtrPrim = compactPtrType->GetPrimType();
  BaseNode *offsetNode = builder->CreateIntConst(hashCode * kTabEntrySize, PTY_u32);
  BaseNode *addrNode = builder->CreateExprBinary(OP_add, GlobalTables::GetTypeTable().GetPtr(),
                                                 builder->CreateExprRegread(PTY_ptr, pregItabAddress), offsetNode);
  BaseNode *readFuncPtr = builder->CreateExprIread(
      compactPtrType, GlobalTables::GetTypeTable().GetOrCreatePointerType(compactPtrType), 0, addrNode);
  PregIdx pregFuncPtr = currFunc->GetPregTab()->CreatePreg(compactPtrPrim);
  RegassignNode *funcPtrAssign = builder->CreateStmtRegassign(compactPtrPrim, pregFuncPtr, readFuncPtr);
  currFunc->GetBody()->InsertBefore(stmt, funcPtrAssign);
  // In case not found in the fast path, fall to the slow path
  uint64 secondHashCode = GetSecondHashIndex(signature.c_str());
  MapleAllocator *currentFuncMpAllocator = builder->GetCurrentFuncCodeMpAllocator();
  CHECK_FATAL(currentFuncMpAllocator != nullptr, "null ptr check");
  MapleVector<BaseNode*> opnds(currentFuncMpAllocator->Adapter());
  opnds.push_back(builder->CreateExprRegread(PTY_ptr, pregItabAddress));
  opnds.push_back(builder->CreateIntConst(secondHashCode, PTY_u64));
  UStrIdx strIdx = GlobalTables::GetUStrTable().GetOrCreateStrIdxFromName(signature);
  MemPool *CurrentFunMp = builder->GetCurrentFuncCodeMp();
  CHECK_FATAL(CurrentFunMp != nullptr, "null ptr check");
  ConststrNode *signatureNode = CurrentFunMp->New<ConststrNode>(strIdx);
  signatureNode->SetPrimType(PTY_ptr);
  opnds.push_back(signatureNode);
  StmtNode *mccCallStmt =
      builder->CreateStmtCallRegassigned(mccItabFunc->GetPuidx(), opnds, pregFuncPtr, OP_callassigned);
  BaseNode *checkExpr = builder->CreateExprCompare(OP_eq, GlobalTables::GetTypeTable().GetUInt1(), compactPtrType,
                                                   builder->CreateExprRegread(compactPtrPrim, pregFuncPtr),
                                                   builder->CreateIntConst(0, compactPtrPrim));
  IfStmtNode *ifStmt = static_cast<IfStmtNode*>(builder->CreateStmtIf(checkExpr));
  ifStmt->GetThenPart()->AddStatement(mccCallStmt);
  currFunc->GetBody()->InsertBefore(stmt, ifStmt);
  if (stmt->GetOpCode() == OP_regassign) {
    RegassignNode *regAssign = static_cast<RegassignNode*>(stmt);
    regAssign->SetOpnd(builder->CreateExprRegread(compactPtrPrim, pregFuncPtr));
  } else {
    IcallNode *icall = static_cast<IcallNode*>(stmt);
    const size_t nopndSize = icall->GetNopndSize();
    CHECK_FATAL(nopndSize > 0, "container check");
    icall->SetNOpndAt(0, builder->CreateExprRegread(compactPtrPrim, pregFuncPtr));
  }
}

}  // namespace maple
