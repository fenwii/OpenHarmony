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
#include "java_intrn_lowering.h"
#include <fstream>
#include <algorithm>
#include <cstdio>

// JavaIntrnLowering lowers several kinds of intrinsics:
// 1. INTRN_JAVA_MERGE
//    Check if INTRN_JAVA_MERGE is legal:
//    if yes, turn it into a Retype or CvtType; if no, assert
// 2. INTRN_JAVA_FILL_NEW_ARRAY
//    Turn it into a jarray malloc and jarray element-wise assignment

namespace maple {
inline bool IsConstvalZero(BaseNode *n) {
  return (n->GetOpCode() == OP_constval && static_cast<ConstvalNode*>(n)->GetConstVal()->IsZero());
}

JavaIntrnLowering::JavaIntrnLowering(MIRModule *mod, KlassHierarchy *kh, bool dump) : FuncOptimizeImpl(mod, kh, dump) {
}


void JavaIntrnLowering::ProcessStmt(StmtNode *stmt) {
  if (stmt == nullptr) {
    return;
  }
  Opcode opcode = stmt->GetOpCode();
  switch (opcode) {
    case OP_dassign:
    case OP_regassign: {
      BaseNode *rhs = nullptr;
      if (opcode == OP_dassign) {
        DassignNode *dassign = static_cast<DassignNode*>(stmt);
        rhs = dassign->GetRHS();
      } else {
        RegassignNode *regassign = static_cast<RegassignNode*>(stmt);
        rhs = regassign->GetRHS();
      }
      if (rhs != nullptr && rhs->GetOpCode() == OP_intrinsicop) {
        IntrinsicopNode *intrinNode = static_cast<IntrinsicopNode*>(rhs);
        if (intrinNode->GetIntrinsic() == INTRN_JAVA_MERGE) {
          ProcessJavaIntrnMerge(stmt, intrinNode);
        }
      }
      break;
    }
    case OP_intrinsiccallwithtypeassigned: {
      IntrinsiccallNode *intrinCall = static_cast<IntrinsiccallNode*>(stmt);
      if (intrinCall->GetIntrinsic() == INTRN_JAVA_FILL_NEW_ARRAY) {
        ProcessJavaIntrnFillNewArray(intrinCall);
      }
      break;
    }
    default:
      break;
  }
}


void JavaIntrnLowering::ProcessJavaIntrnMerge(StmtNode *assignNode, const IntrinsicopNode *intrinNode) {
  CHECK_FATAL(intrinNode->GetNumOpnds() == 1, "invalid JAVA_MERGE intrinsic node");
  PrimType destType;
  DassignNode *dassign = nullptr;
  RegassignNode *regassign = nullptr;
  if (assignNode->GetOpCode() == OP_dassign) {
    dassign = static_cast<DassignNode*>(assignNode);
    MIRSymbol *dest = currFunc->GetLocalOrGlobalSymbol(dassign->GetStIdx());
    destType = dest->GetType()->GetPrimType();
  } else {
    regassign = static_cast<RegassignNode*>(assignNode);
    destType = regassign->GetPrimType();
  }
  BaseNode *resNode = intrinNode->Opnd(0);
  CHECK_FATAL(resNode != nullptr, "null ptr check");
  PrimType srcType = resNode->GetPrimType();
  if (destType != srcType) {
    resNode = JavaIntrnMergeToCvtType(destType, srcType, resNode);
  }
  if (assignNode->GetOpCode() == OP_dassign) {
    CHECK_FATAL(dassign != nullptr, "null ptr check");
    dassign->SetRHS(resNode);
  } else {
    CHECK_FATAL(regassign != nullptr, "null ptr check");
    regassign->SetRHS(resNode);
  }
}

BaseNode *JavaIntrnLowering::JavaIntrnMergeToCvtType(PrimType destType, PrimType srcType, BaseNode *src) {
  CHECK_FATAL(IsPrimitiveInteger(destType) || IsPrimitiveFloat(destType),
              "typemerge source type is not a primitive type");
  CHECK_FATAL(IsPrimitiveInteger(srcType) || IsPrimitiveFloat(srcType),
              "typemerge destination type is not a primitive type");
  // src i32, dest f32; src i64, dest f64.
  bool isPrimitive = IsPrimitiveInteger(srcType) && IsPrimitiveFloat(destType) &&
      GetPrimTypeBitSize(srcType) <= GetPrimTypeBitSize(destType);
  if (!(isPrimitive || (IsPrimitiveInteger(srcType) && IsPrimitiveInteger(destType)))) {
    CHECK_FATAL(false, "Wrong type in typemerge: srcType is %d; destType is %d", srcType, destType);
  }
  // src & dest are both of float type.
  MIRType *toType = GlobalTables::GetTypeTable().GetPrimType(destType);
  MIRType *fromType = GlobalTables::GetTypeTable().GetPrimType(srcType);
  if (IsPrimitiveInteger(srcType) && IsPrimitiveFloat(destType)) {
    if (GetPrimTypeBitSize(srcType) == GetPrimTypeBitSize(destType)) {
      return builder->CreateExprRetype(toType, fromType, src);
    } else {
      return builder->CreateExprTypeCvt(OP_cvt, toType, fromType, src);
    }
  } else if (IsPrimitiveInteger(srcType) && IsPrimitiveInteger(destType)) {
    if (GetPrimTypeBitSize(srcType) >= GetPrimTypeBitSize(destType)) {
      if (destType == PTY_u1) {  // e.g., type _Bool.
        return builder->CreateExprCompare(OP_ne, toType, fromType, src, builder->CreateIntConst(0, srcType));
      } else if (GetPrimTypeBitSize(srcType) > GetPrimTypeBitSize(destType)) {
        return builder->CreateExprTypeCvt(OP_cvt, toType, fromType, src);
      } else if (IsSignedInteger(srcType) != IsSignedInteger(destType)) {
        return builder->CreateExprTypeCvt(OP_cvt, toType, fromType, src);
      } else {
        src->SetPrimType(destType);
        return src;
      }
      // Force type cvt here because we currently do not run constant folding
      // or contanst propagation before CG. We may revisit this decision later.
    } else if (GetPrimTypeBitSize(srcType) < GetPrimTypeBitSize(destType)) {
      return builder->CreateExprTypeCvt(OP_cvt, toType, fromType, src);
    } else if (IsConstvalZero(src)) {
      return builder->CreateIntConst(0, destType);
    } else {
      CHECK_FATAL(false, "NYI. Don't know what to do");
    }
  } else {
    CHECK_FATAL(false, "NYI. Don't know what to do");
  }
}

void JavaIntrnLowering::ProcessJavaIntrnFillNewArray(IntrinsiccallNode *intrinCall) {
  // First create a new array.
  CHECK_FATAL(intrinCall->GetReturnVec().size() == 1, "INTRN_JAVA_FILL_NEW_ARRAY should have 1 return value");
  CallReturnPair retPair = intrinCall->GetCallReturnPair(0);
  bool isReg = retPair.second.IsReg();
  MIRType *retType = nullptr;
  if (!isReg) {
    retType = currFunc->GetLocalOrGlobalSymbol(retPair.first)->GetType();
  } else {
    PregIdx pregidx = retPair.second.GetPregIdx();
    MIRPreg *mirpreg = currFunc->GetPregTab()->PregFromPregIdx(pregidx);
    CHECK_FATAL(mirpreg->GetPrimType() == PTY_ref || mirpreg->GetPrimType() == PTY_ptr,
                "Dst preg needs to be a pointer or reference type");
    retType = mirpreg->GetMIRType();
  }
  CHECK_FATAL(retType->GetKind() == kTypePointer, "Return type of INTRN_JAVA_FILL_NEW_ARRAY should point to a Jarray");
  MIRType *arrayType = static_cast<MIRPtrType*>(retType)->GetPointedType();
  BaseNode *lenNode = builder->CreateIntConst(intrinCall->NumOpnds(), PTY_i32);
  JarrayMallocNode *newArrayNode = builder->CreateExprJarrayMalloc(OP_gcmallocjarray, retType, arrayType, lenNode);
  // Then fill each array element one by one.
  BaseNode *addrExpr = nullptr;
  StmtNode *assignStmt = nullptr;
  if (!isReg) {
    MIRSymbol *retSym = currFunc->GetLocalOrGlobalSymbol(retPair.first);
    assignStmt = builder->CreateStmtDassign(retSym, retPair.second.GetFieldID(), newArrayNode);
    currFunc->GetBody()->ReplaceStmt1WithStmt2(intrinCall, assignStmt);
    addrExpr = builder->CreateExprDread(retSym);
  } else {
    PregIdx pregidx = retPair.second.GetPregIdx();
    MIRPreg *mirpreg = currFunc->GetPregTab()->PregFromPregIdx(pregidx);
    assignStmt = builder->CreateStmtRegassign(mirpreg->GetPrimType(), pregidx, newArrayNode);
    currFunc->GetBody()->ReplaceStmt1WithStmt2(intrinCall, assignStmt);
    addrExpr = builder->CreateExprRegread(mirpreg->GetPrimType(), pregidx);
  }
  StmtNode *stmt = assignStmt;
  for (int i = 0; i < intrinCall->NumOpnds(); i++) {
    ArrayNode *arrayexpr = builder->CreateExprArray(arrayType, addrExpr, builder->CreateIntConst(i, PTY_i32));
    arrayexpr->SetBoundsCheck(false);
    StmtNode *storeStmt = builder->CreateStmtIassign(retType, 0, arrayexpr, intrinCall->Opnd(i));
    currFunc->GetBody()->InsertAfter(stmt, storeStmt);
    stmt = storeStmt;
  }
}

}  // namespace maple
