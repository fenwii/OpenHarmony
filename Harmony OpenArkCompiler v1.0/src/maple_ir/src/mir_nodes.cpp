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
#include "mir_nodes.h"
#include <algorithm>
#include <stack>
#include "mir_function.h"
#include "printing.h"
#include "maple_string.h"
#include "opcode_info.h"
#include "name_mangler.h"

namespace maple {
MIRModule *theModule;
uint32 StmtNode::stmtIDNext = 1;  // 0 is reserved
uint32 StmtNode::lastPrintedLineNum = 0;

const char *GetIntrinsicName(MIRIntrinsicID intrn) {
  switch (intrn) {
    default:
#define DEF_MIR_INTRINSIC(STR, NAME, INTRN_CLASS, RETURN_TYPE, ...) \
  case INTRN_##STR:                                                 \
    return #STR;
#include "intrinsics.def"
#undef DEF_MIR_INTRINSIC
  }
}

const char *BaseNode::GetOpName() const {
  return kOpcodeInfo.GetTableItemAt(GetOpCode()).name;
}

bool BaseNode::MayThrowException() {
  if (kOpcodeInfo.MayThrowException(GetOpCode())) {
    if (GetOpCode() != OP_array) {
      return true;
    }
    ArrayNode *arry = static_cast<ArrayNode*>(this);
    if (arry->GetBoundsCheck()) {
      return true;
    }
  } else if (GetOpCode() == OP_intrinsicop) {
    IntrinsicopNode *inNode = static_cast<IntrinsicopNode*>(this);
    if (inNode->GetIntrinsic() == INTRN_JAVA_ARRAY_LENGTH) {
      return true;
    }
  }
  for (size_t i = 0; i < NumOpnds(); i++)
    if (Opnd(i)->MayThrowException()) {
      return true;
    }
  return false;
}

bool AddrofNode::CheckNode(const MIRModule *mod) const {
  ASSERT(mod != nullptr, "mod is null");
  MIRSymbol *st = mod->CurFunction()->GetLocalOrGlobalSymbol(GetStIdx());
  MIRType *ty = st->GetType();
  switch (ty->GetKind()) {
    case kTypeScalar: {
#ifdef DYNAMICLANG
      if (GetPrimType() == PTY_dynany) {
        return true;
      } else {
        return IsPrimitiveScalar(GetPrimType());
      }
#else
      return IsPrimitiveScalar(GetPrimType());
#endif
    }
    case kTypeArray: {
      return GetPrimType() == PTY_agg;
    }
    case kTypeUnion:
    case kTypeStruct:
    case kTypeStructIncomplete: {
      if (GetFieldID() == 0) {
        return GetPrimType() == PTY_agg;
      } else {
        MIRStructType *structType = static_cast<MIRStructType*>(ty);
        TyIdx ftyidx = structType->GetFieldTyIdx(fieldID);
        MIRType *subType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ftyidx);
        MIRTypeKind subKind = subType->GetKind();
        return (subKind == kTypeBitField && VerifyPrimType(subType->GetPrimType(), GetPrimType())) ||
               (subKind == kTypeScalar && IsPrimitiveScalar(GetPrimType())) ||
               (subKind == kTypePointer && IsPrimitivePoint(GetPrimType())) ||
               (subKind == kTypeStruct && GetPrimType() == PTY_agg) || (ftyidx != 0 && GetPrimType() == PTY_agg);
      }
    }
    case kTypeClass:
    case kTypeClassIncomplete: {
      if (fieldID == 0) {
        return GetPrimType() == PTY_agg;
      } else {
        MIRClassType *classType = static_cast<MIRClassType*>(ty);
        MIRType *subType = classType->GetFieldType(fieldID);
        MIRTypeKind subKind = subType->GetKind();
        return (subKind == kTypeBitField && VerifyPrimType(subType->GetPrimType(), GetPrimType())) ||
               (subKind == kTypeScalar && IsPrimitiveScalar(GetPrimType())) ||
               (subKind == kTypePointer && IsPrimitivePoint(GetPrimType())) ||
               (subKind == kTypeStruct && GetPrimType() == PTY_agg);
      }
    }
    case kTypeInterface:
    case kTypeInterfaceIncomplete: {
      if (fieldID == 0) {
        return GetPrimType() == PTY_agg;
      } else {
        MIRInterfaceType *interfaceType = static_cast<MIRInterfaceType*>(ty);
        MIRType *subty = interfaceType->GetFieldType(fieldID);
        MIRTypeKind subKind = subty->GetKind();
        return (subKind == kTypeBitField && VerifyPrimType(subty->GetPrimType(), GetPrimType())) ||
               (subKind == kTypeScalar && IsPrimitiveScalar(GetPrimType())) ||
               (subKind == kTypePointer && IsPrimitivePoint(GetPrimType())) ||
               (subKind == kTypeStruct && GetPrimType() == PTY_agg);
      }
    }
    case kTypePointer:
      return IsPrimitivePoint(GetPrimType());
    case kTypeParam:
    case kTypeGenericInstant:
      return true;
    default:
      return false;
  }
}

bool AddrofNode::HasSymbol(MIRModule *mod, MIRSymbol *st) {
  ASSERT(mod != nullptr, "mod is null");
  return st == mod->CurFunction()->GetLocalOrGlobalSymbol(GetStIdx());
}

void BlockNode::AddStatement(StmtNode *stmt) {
  ASSERT(stmt != nullptr, "null ptr check");
  stmtNodeList.push_back(stmt);
}

void BlockNode::AppendStatementsFromBlock(BlockNode *blk) {
  ASSERT(blk != nullptr, "null ptr check");
  stmtNodeList.splice(stmtNodeList.end(), blk->GetStmtNodes());
}

/// Insert stmt as the first
void BlockNode::InsertFirst(StmtNode *stmt) {
  ASSERT(stmt != nullptr, "stmt is null");
  stmtNodeList.push_front(stmt);
}

/// Insert stmt as the last
void BlockNode::InsertLast(StmtNode *stmt) {
  ASSERT(stmt != nullptr, "stmt is null");
  stmtNodeList.push_back(stmt);
}

void BlockNode::ReplaceStmtWithBlock(StmtNode *stmtNode, BlockNode *blk) {
  stmtNodeList.splice(stmtNode, blk->GetStmtNodes());
  stmtNodeList.erase(stmtNode);
  stmtNode->SetNext(blk->GetLast()->GetNext());
}

void BlockNode::ReplaceStmt1WithStmt2(StmtNode *stmtNode1, StmtNode *stmtNode2) {
  if (stmtNode2 == stmtNode1) {
    // do nothing
  } else if (stmtNode2 == nullptr) {
    // delete stmtNode1
    stmtNodeList.erase(stmtNode1);
  } else {
    // replace stmtNode1 with stmtNode2
    stmtNodeList.insert(stmtNode1, stmtNode2);
    stmtNodeList.erase(stmtNode1);
  }
}

// remove sstmtNode1 from block
void BlockNode::RemoveStmt(StmtNode *stmtNode1) {
  ASSERT(stmtNode1 != nullptr, "delete a null stmtment");
  stmtNodeList.erase(stmtNode1);
}

/// Insert stmtNode2 before stmtNode1 in current block.
void BlockNode::InsertBefore(StmtNode *stmtNode1, StmtNode *stmtNode2) {
  stmtNodeList.insert(stmtNode1, stmtNode2);
}

/// Insert stmtNode2 after stmtNode1 in current block.
void BlockNode::InsertAfter(StmtNode *stmtNode1, StmtNode *stmtNode2) {
  stmtNodeList.insertAfter(stmtNode1, stmtNode2);
}

// insert all the stmts in inblock to the current block after stmt1
void BlockNode::InsertBlockAfter(BlockNode *inblock, StmtNode *stmt1) {
  ASSERT(stmt1 != nullptr, "null ptr check");
  ASSERT(!inblock->IsEmpty(), "NYI");
  stmtNodeList.splice(stmt1, inblock->GetStmtNodes());
}

void BaseNode::DumpBase(const MIRModule *mod, int32 indent) const {
  PrintIndentation(indent);
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " " << GetPrimTypeName(GetPrimType());
}

void CatchNode::Dump(const MIRModule *mod, int32 indent) const {
  PrintIndentation(indent);
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " {";
  size_t size = exceptionTyIdxVec.size();
  for (size_t i = 0; i < size; i++) {
    LogInfo::MapleLogger() << " ";
    GlobalTables::GetTypeTable().GetTypeFromTyIdx(exceptionTyIdxVec[i])->Dump(indent + 1);
  }
  LogInfo::MapleLogger() << " }" << std::endl;
}

void CatchNode::Dump(const MIRModule *mod) const {
  this->BaseNode::Dump(mod);
}

void UnaryNode::DumpOpnd(const MIRModule *mod, int indent) const {
  LogInfo::MapleLogger() << " (";
  uOpnd->Dump(mod, indent);
  LogInfo::MapleLogger() << ")";
}

void UnaryNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  DumpOpnd(mod, indent);
}

void TypeCvtNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " ";
  LogInfo::MapleLogger() << GetPrimTypeName(GetPrimType()) << " " << GetPrimTypeName(FromType());
  DumpOpnd(mod, indent);
}

void RetypeNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " ";
  LogInfo::MapleLogger() << GetPrimTypeName(GetPrimType()) << " ";
  MIRType *ty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  if (ty->GetKind() == kTypeScalar) {
    LogInfo::MapleLogger() << "<";
    ty->Dump(indent + 1);
    LogInfo::MapleLogger() << ">";
  } else {
    ty->Dump(indent + 1);
  }
  DumpOpnd(mod, indent);
}

void ExtractbitsNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " " << GetPrimTypeName(GetPrimType());
  if (GetOpCode() == OP_extractbits) {
    LogInfo::MapleLogger() << " " << static_cast<int32>(bitsOffset) << " " << static_cast<int32>(bitsSize);
  } else {
    LogInfo::MapleLogger() << " " << static_cast<int32>(bitsSize);
  }
  DumpOpnd(mod, indent);
}

void IreadNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  LogInfo::MapleLogger() << " ";
  GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(0);
  LogInfo::MapleLogger() << " " << fieldID;
  DumpOpnd(mod, indent);
}

void IreadoffNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " " << GetPrimTypeName(GetPrimType());
  LogInfo::MapleLogger() << " " << offset;
  DumpOpnd(mod, indent);
}

void IreadFPoffNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " " << GetPrimTypeName(GetPrimType());
  LogInfo::MapleLogger() << " " << offset;
}

void BinaryNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  BinaryOpnds::Dump(mod, indent);
}

void BinaryNode::Dump(const MIRModule *mod) const {
  this->BaseNode::Dump(mod);
}

void BinaryOpnds::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << " (";
  if (bOpnd[0]->IsLeaf() && bOpnd[1]->IsLeaf()) {
    bOpnd[0]->Dump(mod, 0);
    LogInfo::MapleLogger() << ", ";
    bOpnd[1]->Dump(mod, 0);
  } else {
    LogInfo::MapleLogger() << std::endl;
    PrintIndentation(indent + 1);
    bOpnd[0]->Dump(mod, indent + 1);
    LogInfo::MapleLogger() << "," << std::endl;
    PrintIndentation(indent + 1);
    bOpnd[1]->Dump(mod, indent + 1);
  }
  LogInfo::MapleLogger() << ")";
}

void ResolveFuncNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  MIRFunction *func = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(puIdx);
  LogInfo::MapleLogger() << " &" << func->GetName();
  BinaryOpnds::Dump(mod, indent);
}

void CompareNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " " << GetPrimTypeName(GetPrimType());
  LogInfo::MapleLogger() << " " << GetPrimTypeName(opndType);
  BinaryOpnds::Dump(mod, indent);
}

void CompareNode::Dump(const MIRModule *mod) const {
  this->BaseNode::Dump(mod);
}

void DepositbitsNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  LogInfo::MapleLogger() << " " << static_cast<int32>(bitsOffset) << " " << static_cast<int32>(bitsSize) << " (";
  if (GetBOpnd(0)->IsLeaf() && GetBOpnd(1)->IsLeaf()) {
    GetBOpnd(0)->Dump(mod, 0);
    LogInfo::MapleLogger() << ", ";
    GetBOpnd(1)->Dump(mod, 0);
  } else {
    LogInfo::MapleLogger() << std::endl;
    PrintIndentation(indent + 1);
    GetBOpnd(0)->Dump(mod, indent + 1);
    LogInfo::MapleLogger() << "," << std::endl;
    PrintIndentation(indent + 1);
    GetBOpnd(1)->Dump(mod, indent + 1);
  }
  LogInfo::MapleLogger() << ")";
}

void TernaryNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  LogInfo::MapleLogger() << " (";
  if (topnd[0]->IsLeaf() && topnd[1]->IsLeaf() && topnd[2]->IsLeaf()) {
    topnd[0]->Dump(mod, 0);
    LogInfo::MapleLogger() << ", ";
    topnd[1]->Dump(mod, 0);
    LogInfo::MapleLogger() << ", ";
    topnd[2]->Dump(mod, 0);
  } else {
    LogInfo::MapleLogger() << std::endl;
    PrintIndentation(indent + 1);
    topnd[0]->Dump(mod, indent + 1);
    LogInfo::MapleLogger() << "," << std::endl;
    PrintIndentation(indent + 1);
    topnd[1]->Dump(mod, indent + 1);
    LogInfo::MapleLogger() << "," << std::endl;
    PrintIndentation(indent + 1);
    topnd[2]->Dump(mod, indent + 1);
  }
  LogInfo::MapleLogger() << ")";
}

void NaryOpnds::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << " (";
  if (GetNopndSize() == 0) {
    LogInfo::MapleLogger() << ")";
    return;
  }
  if (GetNopndSize() == 1) {
    GetNopndAt(0)->Dump(mod, indent);
  } else {
    bool allisLeaf = true;
    for (size_t i = 0; i < GetNopndSize(); i++)
      if (!GetNopndAt(i)->IsLeaf()) {
        allisLeaf = false;
        break;
      }
    if (allisLeaf) {
      GetNopndAt(0)->Dump(mod, 0);
      for (size_t i = 1; i < GetNopndSize(); i++) {
        LogInfo::MapleLogger() << ", ";
        GetNopndAt(i)->Dump(mod, 0);
      }
    } else {
      LogInfo::MapleLogger() << std::endl;
      PrintIndentation(indent + 1);
      GetNopndAt(0)->Dump(mod, indent + 1);
      for (size_t i = 1; i < GetNopndSize(); i++) {
        LogInfo::MapleLogger() << "," << std::endl;
        PrintIndentation(indent + 1);
        GetNopndAt(i)->Dump(mod, indent + 1);
      }
    }
  }
  LogInfo::MapleLogger() << ")";
}

bool NaryOpnds::VerifyOpnds() const {
  bool nOpndsVerify = true;
  for (size_t i = 0; i < GetNopndSize(); i++) {
    if (!GetNopndAt(i)->Verify()) {
      nOpndsVerify = false;
      break;
    }
  }
  return nOpndsVerify;
}

void NaryNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  NaryOpnds::Dump(mod, indent);
}

MIRType *ArrayNode::GetArrayType(TypeTable *tt) const {
  MIRPtrType *pointType = MIR_DYN_CAST(tt->GetTypeFromTyIdx(tyIdx), MIRPtrType*);
  ASSERT(pointType != nullptr, "expect array type pointer");
  return tt->GetTypeFromTyIdx(pointType->GetPointedTyIdx());
}

BaseNode *ArrayNode::GetDim(const MIRModule *mod, TypeTable *tt, int i) {
  MIRArrayType *arrayType = static_cast<MIRArrayType*>(GetArrayType(tt));
  MIRConst *mirConst = mod->CurFuncCodeMemPool()->New<MIRConst>(tt->GetTypeFromTyIdx(arrayType->GetElemTyIdx()));
  return mod->CurFuncCodeMemPool()->New<ConstvalNode>(mirConst);
}

void ArrayNode::Dump(const MIRModule *mod, int32 indent) const {
  PrintIndentation(0);
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " ";
  if (boundsCheck) {
    LogInfo::MapleLogger() << "1 ";
  } else {
    LogInfo::MapleLogger() << "0 ";
  }
  LogInfo::MapleLogger() << GetPrimTypeName(GetPrimType());
  LogInfo::MapleLogger() << " ";
  GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(0);
  NaryOpnds::Dump(mod, indent);
}

bool ArrayNode::IsSameBase(ArrayNode *arry) {
  if (arry == this) {
    return true;
  }
  BaseNode *curBase = this->GetBase();
  BaseNode *otherBase = arry->GetBase();
  if (curBase->GetOpCode() != OP_addrof || otherBase->GetOpCode() != OP_addrof) {
    return false;
  }
  return static_cast<AddrofNode*>(curBase)->GetStIdx() == static_cast<AddrofNode*>(otherBase)->GetStIdx();
}

void IntrinsicopNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " " << GetPrimTypeName(GetPrimType());
  if (GetOpCode() == OP_intrinsicopwithtype) {
    LogInfo::MapleLogger() << " ";
    GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(indent + 1);
  }
  LogInfo::MapleLogger() << " " << GetIntrinsicName(GetIntrinsic());
  NaryOpnds::Dump(mod, indent);
}

void ConstvalNode::Dump(const MIRModule *mod, int32 indent) const {
  if (GetConstVal()->GetType()->GetKind() != kTypePointer) {
    BaseNode::DumpBase(mod, 0);
    LogInfo::MapleLogger() << " ";
  }
  GetConstVal()->Dump();
}

void ConststrNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  const std::string kStr = GlobalTables::GetUStrTable().GetStringFromStrIdx(UStrIdx(strIdx.GetIdx()));
  PrintString(kStr);
}

void Conststr16Node::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  const std::u16string kStr16 = GlobalTables::GetU16StrTable().GetStringFromStrIdx(U16StrIdx(strIdx.GetIdx()));
  // UTF-16 string are dumped as UTF-8 string in mpl to keep the printable chars in ascii form
  std::string str;
  NameMangler::UTF16ToUTF8(str, kStr16);
  PrintString(str);
}

void SizeoftypeNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  LogInfo::MapleLogger() << " ";
  GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(0);
}

void FieldsDistNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  LogInfo::MapleLogger() << " ";
  GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(0);
  LogInfo::MapleLogger() << " " << fieldID1 << " " << fieldID2;
}

void AddrofNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " " << GetPrimTypeName(GetPrimType());
  MIRSymbol *st = mod->CurFunction()->GetLocalOrGlobalSymbol(GetStIdx());
  LogInfo::MapleLogger() << (GetStIdx().Islocal() ? " %" : " $");
  LogInfo::MapleLogger() << st->GetName();
  if (fieldID != 0) {
    LogInfo::MapleLogger() << " " << fieldID;
  }
}

void RegreadNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " " << GetPrimTypeName(GetPrimType());
  if (regIdx >= 0) {
    LogInfo::MapleLogger()
        << " %" << mod->CurFunction()->GetPregTab()->PregFromPregIdx(static_cast<uint32>(regIdx))->GetPregNo();
  } else {
    LogInfo::MapleLogger() << " %%";
    if (regIdx == -kSregSp) {
      LogInfo::MapleLogger() << "SP";
    } else if (regIdx == -kSregFp) {
      LogInfo::MapleLogger() << "FP";
    } else if (regIdx == -kSregGp) {
      LogInfo::MapleLogger() << "GP";
    } else if (regIdx == -kSregThrownval) {
      LogInfo::MapleLogger() << "thrownval";
    } else if (regIdx == -kSregMethodhdl) {
      LogInfo::MapleLogger() << "methodhdl";
    } else {
      int32 retValIdx = (-regIdx) - kSregRetval0;
      LogInfo::MapleLogger() << "retval" << retValIdx;
    }
  }
}

void AddroffuncNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " " << GetPrimTypeName(GetPrimType());
  MIRFunction *func = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(puIdx);
  LogInfo::MapleLogger() << " &" << GlobalTables::GetGsymTable().GetSymbolFromStidx(func->GetStIdx().Idx())->GetName();
}

void AddroflabelNode::Dump(const MIRModule *mod, int32 indent) const {
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name << " " << GetPrimTypeName(GetPrimType());
  LogInfo::MapleLogger() << " @" << mod->CurFunction()->GetLabelName((LabelIdx)offset);
}

void StmtNode::DumpBase(const MIRModule *mod, int32 indent) const {
  if (srcPosition.FileNum() != 0 && srcPosition.LineNum() != 0 && srcPosition.LineNum() != lastPrintedLineNum &&
      mod->CurFunction()->WithLocInfo()) {
    LogInfo::MapleLogger() << "LOC " << srcPosition.FileNum() << " " << srcPosition.LineNum() << std::endl;
    lastPrintedLineNum = srcPosition.LineNum();
  }
  PrintIndentation(indent);
  LogInfo::MapleLogger() << kOpcodeInfo.GetTableItemAt(GetOpCode()).name;
}

void StmtNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << std::endl;
}

void StmtNode::Dump(const MIRModule *mod) const {
  this->BaseNode::Dump(mod);
}

// Get the next stmt skip the comment stmt.
StmtNode *StmtNode::GetRealNext() {
  StmtNode *stmt = this->GetNext();
  while (stmt != nullptr) {
    if (stmt->GetOpCode() != OP_comment) {
      break;
    }
    stmt = stmt->GetNext();
  }
  return stmt;
}

// insert this before pos
void StmtNode::InsertAfterThis(StmtNode *pos) {
  ASSERT(pos != nullptr, "null ptr check");
  this->SetNext(pos);
  if (pos->GetPrev()) {
    this->SetPrev(pos->GetPrev());
    pos->GetPrev()->SetNext(this);
  }
  pos->SetPrev(this);
}

// insert stmtnode after pos
void StmtNode::InsertBeforeThis(StmtNode *pos) {
  ASSERT(pos != nullptr, "null ptr check");
  this->SetPrev(pos);
  if (pos->GetNext()) {
    this->SetNext(pos->GetNext());
    pos->GetNext()->SetPrev(this);
  }
  pos->SetNext(this);
}

void DassignNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  MIRSymbol *st = mod->CurFunction()->GetLocalOrGlobalSymbol(stIdx);
  LogInfo::MapleLogger() << (st->IsLocal() ? " %" : " $");
  LogInfo::MapleLogger() << st->GetName() << " " << fieldID;
  LogInfo::MapleLogger() << " (";
  if (GetRHS()) {
    GetRHS()->Dump(mod, indent + 1);
  } else {
    LogInfo::MapleLogger() << "/*empty-rhs*/";
  }
  LogInfo::MapleLogger() << ")" << std::endl;
}

void RegassignNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " " << GetPrimTypeName(GetPrimType());
  if (regIdx >= 0) {
    LogInfo::MapleLogger()
        << " %" << mod->CurFunction()->GetPregTab()->PregFromPregIdx(static_cast<uint32>(regIdx))->GetPregNo();
  } else {
    LogInfo::MapleLogger() << " %%";
    if (regIdx == -kSregSp) {
      LogInfo::MapleLogger() << "SP";
    } else if (regIdx == -kSregFp) {
      LogInfo::MapleLogger() << "FP";
    } else if (regIdx == -kSregGp) {
      LogInfo::MapleLogger() << "GP";
    } else if (regIdx == -kSregThrownval) {
      LogInfo::MapleLogger() << "thrownval";
    } else if (regIdx == -kSregMethodhdl) {
      LogInfo::MapleLogger() << "methodhdl";
    } else if (regIdx == -kSregRetval0) {
      LogInfo::MapleLogger() << "retval0";
    }
  }
  LogInfo::MapleLogger() << " (";
  UnaryStmtNode::Opnd()->Dump(mod, indent + 1);
  LogInfo::MapleLogger() << ")" << std::endl;
}

void IassignNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " ";
  GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(0);
  LogInfo::MapleLogger() << " " << fieldID;
  LogInfo::MapleLogger() << " (";
  if (addrExpr->IsLeaf() && rhs->IsLeaf()) {
    addrExpr->Dump(mod, 0);
    LogInfo::MapleLogger() << ", ";
    rhs->Dump(mod, 0);
  } else {
    LogInfo::MapleLogger() << std::endl;
    PrintIndentation(indent + 1);
    addrExpr->Dump(mod, indent + 1);
    LogInfo::MapleLogger() << ", " << std::endl;
    PrintIndentation(indent + 1);
    rhs->Dump(mod, indent + 1);
  }
  LogInfo::MapleLogger() << ")" << std::endl;
}

void IassignoffNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " " << GetPrimTypeName(GetPrimType()) << " " << offset;
  BinaryOpnds::Dump(mod, indent);
  LogInfo::MapleLogger() << std::endl;
}

void IassignFPoffNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " " << GetPrimTypeName(GetPrimType()) << " " << offset;
  DumpOpnd(mod, indent);
  LogInfo::MapleLogger() << std::endl;
}

void GotoNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  if (offset == 0) {
    LogInfo::MapleLogger() << std::endl;
  } else {
    LogInfo::MapleLogger() << " @" << mod->CurFunction()->GetLabelName((LabelIdx)offset) << std::endl;
  }
}

void JsTryNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  if (catchOffset == 0) {
    LogInfo::MapleLogger() << " 0";
  } else {
    LogInfo::MapleLogger() << " @" << mod->CurFunction()->GetLabelName((LabelIdx)catchOffset);
  }
  if (finallyOffset == 0) {
    LogInfo::MapleLogger() << " 0" << std::endl;
  } else {
    LogInfo::MapleLogger() << " @" << mod->CurFunction()->GetLabelName((LabelIdx)finallyOffset) << std::endl;
  }
}

void TryNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " {";
  for (size_t i = 0; i < offsets.size(); i++) {
    int64 offset = offsets[i];
    LogInfo::MapleLogger() << " @" << mod->CurFunction()->GetLabelName((LabelIdx)offset);
  }
  LogInfo::MapleLogger() << " }" << std::endl;
}

void TryNode::Dump(const MIRModule *mod) const {
  this->BaseNode::Dump(mod);
}

void CondGotoNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " @" << mod->CurFunction()->GetLabelName((LabelIdx)offset);
  LogInfo::MapleLogger() << " (";
  Opnd()->Dump(mod, indent);
  LogInfo::MapleLogger() << ")" << std::endl;
}

void SwitchNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " (";
  switchOpnd->Dump(mod, indent);
  if (defaultLabel == 0) {
    LogInfo::MapleLogger() << ") 0 {";
  } else {
    LogInfo::MapleLogger() << ") @" << mod->CurFunction()->GetLabelName(defaultLabel) << " {";
  }
  for (auto it = switchTable.begin(); it != switchTable.end(); it++) {
    LogInfo::MapleLogger() << std::endl;
    PrintIndentation(indent + 1);
    LogInfo::MapleLogger() << std::hex << "0x" << (it)->first << std::dec;
    LogInfo::MapleLogger() << ": goto @" << mod->CurFunction()->GetLabelName((it)->second);
  }
  LogInfo::MapleLogger() << " }" << std::endl;
}

void RangegotoNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " (";
  Opnd()->Dump(mod, indent);
  LogInfo::MapleLogger() << ") " << tagOffset << " {";
  for (auto it = rangegotoTable.begin(); it != rangegotoTable.end(); it++) {
    LogInfo::MapleLogger() << std::endl;
    PrintIndentation(indent + 1);
    LogInfo::MapleLogger() << std::hex << "0x" << (it)->first << std::dec;
    LogInfo::MapleLogger() << ": goto @" << mod->CurFunction()->GetLabelName((it)->second);
  }
  LogInfo::MapleLogger() << " }" << std::endl;
}

void MultiwayNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " (";
  multiWayOpnd->Dump(mod, indent);
  if (defaultLabel == 0) {
    LogInfo::MapleLogger() << ") 0 {";
  } else {
    LogInfo::MapleLogger() << ") @" << mod->CurFunction()->GetLabelName(defaultLabel) << " {";
  }
  for (auto it = multiWayTable.begin(); it != multiWayTable.end(); it++) {
    LogInfo::MapleLogger() << std::endl;
    PrintIndentation(indent);
    LogInfo::MapleLogger() << " (";
    it->first->Dump(mod, indent + 1);
    LogInfo::MapleLogger() << "): goto @" << mod->CurFunction()->GetLabelName((it)->second);
  }
  LogInfo::MapleLogger() << " }" << std::endl;
}

void UnaryStmtNode::DumpOpnd(const MIRModule *mod, int indent) const {
  LogInfo::MapleLogger() << " (";
  uopnd->Dump(mod, indent);
  LogInfo::MapleLogger() << ")";
}

void UnaryStmtNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " (";
  if (uopnd) {
    uopnd->Dump(mod, indent);
  }
  LogInfo::MapleLogger() << ")" << std::endl;
}

void UnaryStmtNode::Dump(const MIRModule *mod) const {
  this->BaseNode::Dump(mod);
}

void GCMallocNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  LogInfo::MapleLogger() << " ";
  GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(0);
}

void JarrayMallocNode::Dump(const MIRModule *mod, int32 indent) const {
  BaseNode::DumpBase(mod, 0);
  LogInfo::MapleLogger() << " ";
  GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(0, false);
  DumpOpnd(mod, indent);
}

void IfStmtNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  LogInfo::MapleLogger() << " (";
  Opnd()->Dump(mod, indent);
  LogInfo::MapleLogger() << ")";
  thenPart->Dump(mod, indent);
  if (elsePart) {
    PrintIndentation(indent);
    LogInfo::MapleLogger() << "else {" << std::endl;
    for (auto &stmt : elsePart->GetStmtNodes()) {
      stmt.Dump(mod, indent + 1);
    }
    PrintIndentation(indent);
    LogInfo::MapleLogger() << "}" << std::endl;
  }
}

void WhileStmtNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  if (GetOpCode() == OP_while) {
    LogInfo::MapleLogger() << " (";
    Opnd()->Dump(mod, indent);
    LogInfo::MapleLogger() << ")";
    body->Dump(mod, indent);
  } else {  // OP_dowhile
    LogInfo::MapleLogger() << " {" << std::endl;
    for (auto &stmt : body->GetStmtNodes()) {
      stmt.Dump(mod, indent + 1);
    }
    PrintIndentation(indent);
    LogInfo::MapleLogger() << "} (";
    Opnd()->Dump(mod, indent);
    LogInfo::MapleLogger() << ")" << std::endl;
  }
}

void DoloopNode::DumpDoVar(const MIRModule *mod) const {
  if (isPreg) {
    LogInfo::MapleLogger() << " %"
                           << mod->CurFunction()->GetPregTab()->PregFromPregIdx(doVarStIdx.FullIdx())->GetPregNo()
                           << " (" << std::endl;
  } else {
    MIRSymbol *st = mod->CurFunction()->GetLocalOrGlobalSymbol(doVarStIdx);
    LogInfo::MapleLogger() << " %" << st->GetName().c_str() << " (" << std::endl;
  }
}

void DoloopNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  DumpDoVar(mod);
  PrintIndentation(indent + 1);
  startExpr->Dump(mod, indent + 1);
  LogInfo::MapleLogger() << "," << std::endl;
  PrintIndentation(indent + 1);
  condExpr->Dump(mod, indent + 1);
  LogInfo::MapleLogger() << "," << std::endl;
  PrintIndentation(indent + 1);
  incrExpr->Dump(mod, indent + 1);
  LogInfo::MapleLogger() << ")";
  doBody->Dump(mod, indent + 1);
}

void ForeachelemNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  MIRSymbol *st = mod->CurFunction()->GetLocalOrGlobalSymbol(elemStIdx);
  ASSERT(st != nullptr, "null ptr check");
  LogInfo::MapleLogger() << " %" << st->GetName().c_str();
  st = mod->CurFunction()->GetLocalOrGlobalSymbol(arrayStIdx);
  ASSERT(st != nullptr, "null ptr check");
  LogInfo::MapleLogger() << (arrayStIdx.Islocal() ? " %" : " $");
  LogInfo::MapleLogger() << st->GetName().c_str();
  loopBody->Dump(mod, indent + 1);
}

void BinaryStmtNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  BinaryOpnds::Dump(mod, indent);
  LogInfo::MapleLogger() << std::endl;
}

void AssertStmtNode::Dump(const MIRModule *mod, int32 indent) const {
  BinaryStmtNode::Dump(mod, indent);
}

void NaryStmtNode::Dump(const MIRModule *mod, int32 indent) const {
  StmtNode::DumpBase(mod, indent);
  NaryOpnds::Dump(mod, indent);
  LogInfo::MapleLogger() << std::endl;
}

void DumpCallReturns(const MIRModule *mod, CallReturnVector nrets, int32 indent) {
  ASSERT(mod != nullptr, "mod is null");
  const MIRFunction *mirFunc = mod->CurFunction();
  if (nrets.empty()) {
    LogInfo::MapleLogger() << " {}" << std::endl;
    return;
  } else if (nrets.size() == 1) {
    StIdx stIdx = nrets.begin()->first;
    RegFieldPair regFieldPair = nrets.begin()->second;
    if (!regFieldPair.IsReg()) {
      MIRSymbol *st = mod->CurFunction()->GetLocalOrGlobalSymbol(stIdx);
      ASSERT(st != nullptr, "st is null");
      uint16 fieldID = regFieldPair.GetFieldID();
      LogInfo::MapleLogger() << " { dassign ";
      LogInfo::MapleLogger() << (stIdx.Islocal() ? "%" : "$");
      LogInfo::MapleLogger() << st->GetName() << " " << fieldID << " }" << std::endl;
      return;
    } else {
      PregIdx16 regIdx = regFieldPair.GetPregIdx();
      MIRPreg *mirPreg = mirFunc->GetPregItem(static_cast<PregIdx>(regIdx));
      ASSERT(mirPreg != nullptr, "mirPreg is null");
      LogInfo::MapleLogger() << " { regassign";
      LogInfo::MapleLogger() << " " << GetPrimTypeName(mirPreg->GetPrimType());
      LogInfo::MapleLogger() << " %" << mirPreg->GetPregNo() << "}" << std::endl;
      return;
    }
  }
  LogInfo::MapleLogger() << " {" << std::endl;
  for (auto it = nrets.begin(); it != nrets.end(); it++) {
    PrintIndentation(indent + 2);
    StIdx stIdx = (it)->first;
    RegFieldPair regFieldPair = it->second;
    if (!regFieldPair.IsReg()) {
      uint16 fieldID = regFieldPair.GetFieldID();
      LogInfo::MapleLogger() << "dassign";
      MIRSymbol *st = mirFunc->GetLocalOrGlobalSymbol(stIdx);
      ASSERT(st != nullptr, "st is null");
      LogInfo::MapleLogger() << (stIdx.Islocal() ? " %" : " $");
      LogInfo::MapleLogger() << st->GetName() << " " << fieldID << std::endl;
    } else {
      PregIdx16 regidx = regFieldPair.GetPregIdx();
      MIRPreg *mirPreg = mirFunc->GetPregItem(static_cast<PregIdx>(regidx));
      ASSERT(mirPreg != nullptr, "mirPreg is null");
      LogInfo::MapleLogger() << "regassign"
                             << " " << GetPrimTypeName(mirPreg->GetPrimType());
      LogInfo::MapleLogger() << " %" << mirPreg->GetPregNo() << std::endl;
    }
  }
  PrintIndentation(indent + 1);
  LogInfo::MapleLogger() << "}" << std::endl;
}

MIRType *CallNode::GetCallReturnType() {
  if (!kOpcodeInfo.IsCallAssigned(GetOpCode())) {
    return nullptr;
  }
  ASSERT(GlobalTables::GetFunctionTable().GetFuncTable().empty() == false, "container check");
  MIRFunction *mirFunc = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(puIdx);
  return mirFunc->GetReturnType();
}

void CallNode::Dump(const MIRModule *mod, int32 indent, bool newline) const {
  StmtNode::DumpBase(mod, indent);
  if (tyIdx != 0) {
    LogInfo::MapleLogger() << " ";
    GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(indent + 1);
  }
  CHECK(puIdx < GlobalTables::GetFunctionTable().GetFuncTable().size(), "index out of range in CallNode::Dump");
  MIRFunction *func = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(puIdx);
  LogInfo::MapleLogger() << " &" << func->GetName();
  NaryOpnds::Dump(mod, indent);
  if (kOpcodeInfo.IsCallAssigned(GetOpCode())) {
    DumpCallReturns(mod, this->GetReturnVec(), indent);
  } else if (newline) {
    LogInfo::MapleLogger() << std::endl;
  }
}

MIRType *IcallNode::GetCallReturnType() {
  return GlobalTables::GetTypeTable().GetTypeFromTyIdx(retTyIdx);
}

void IcallNode::Dump(const MIRModule *mod, int32 indent, bool newline) const {
  StmtNode::DumpBase(mod, indent);
  NaryOpnds::Dump(mod, indent);
  if (kOpcodeInfo.IsCallAssigned(GetOpCode())) {
    DumpCallReturns(mod, this->returnValues, indent);
  } else if (newline) {
    LogInfo::MapleLogger() << std::endl;
  }
}

MIRType *IntrinsiccallNode::GetCallReturnType() {
  CHECK_FATAL(intrinsic < INTRN_LAST, "Index out of bound in IntrinsiccallNode::GetCallReturnType");
  IntrinDesc *intrinDesc = &IntrinDesc::intrinTable[intrinsic];
  return intrinDesc->GetReturnType();
}

void IntrinsiccallNode::Dump(const MIRModule *mod, int32 indent, bool newline) const {
  StmtNode::DumpBase(mod, indent);
  if (tyIdx != 0) {
    LogInfo::MapleLogger() << " ";
    GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->Dump(indent + 1);
  }
  if (GetOpCode() == OP_intrinsiccall || GetOpCode() == OP_intrinsiccallassigned ||
      GetOpCode() == OP_intrinsiccallwithtype || GetOpCode() == OP_intrinsiccallwithtypeassigned) {
    LogInfo::MapleLogger() << " " << GetIntrinsicName(intrinsic);
  } else {
    LogInfo::MapleLogger() << " " << intrinsic;
  }
  NaryOpnds::Dump(mod, indent);
  if (kOpcodeInfo.IsCallAssigned(GetOpCode())) {
    DumpCallReturns(mod, this->GetReturnVec(), indent);
  } else if (newline) {
    LogInfo::MapleLogger() << std::endl;
  }
}

void CallinstantNode::Dump(const MIRModule *mod, int32 indent, bool newline) const {
  StmtNode::DumpBase(mod, indent);
  MIRFunction *func = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(GetPUIdx());
  LogInfo::MapleLogger() << " &" << func->GetName();
  MIRType *ty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(instVecTyIdx);
  LogInfo::MapleLogger() << "<";
  MIRInstantVectorType *instVecType = static_cast<MIRInstantVectorType*>(ty);
  instVecType->Dump(indent);
  LogInfo::MapleLogger() << ">";
  NaryOpnds::Dump(mod, indent);
  if (kOpcodeInfo.IsCallAssigned(GetOpCode())) {
    DumpCallReturns(mod, this->GetReturnVec(), indent);
  } else if (newline) {
    LogInfo::MapleLogger() << std::endl;
  }
}

void BlockNode::Dump(const MIRModule *mod, int32 indent, const MIRSymbolTable *theSymTab, MIRPregTable *thePregTab,
                     bool withInfo, bool isFuncbody) const {
  ASSERT(mod != nullptr, "mod is null");
  if (!withInfo) {
    LogInfo::MapleLogger() << " {" << std::endl;
  }
  // output puid for debugging purpose
  if (isFuncbody) {
    mod->CurFunction()->DumpFuncBody(indent);
    if (theSymTab != nullptr) {
      // print the locally declared type names
      for (auto it : mod->CurFunction()->GetTypeNameTab()->GetGStrIdxToTyIdxMap()) {
        const std::string &name = GlobalTables::GetStrTable().GetStringFromStrIdx(it.first);
        MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(it.second);
        PrintIndentation(indent + 1);
        LogInfo::MapleLogger() << "type %" << name << " ";
        if (type->GetKind() != kTypeByName) {
          type->Dump(indent + 2, true);
        } else {
          type->Dump(indent + 2);
        }
        LogInfo::MapleLogger() << std::endl;
      }
      // print the locally declared variables
      theSymTab->Dump(true, indent + 1);
      thePregTab->DumpRef(indent + 1);
    }
    LogInfo::MapleLogger() << std::endl;
    for (std::pair<GStrIdx, MIRAliasVars> it : mod->CurFunction()->GetAliasVarMap()) {
      LogInfo::MapleLogger() << "ALIAS %" << GlobalTables::GetStrTable().GetStringFromStrIdx(it.first) << " %"
                             << GlobalTables::GetStrTable().GetStringFromStrIdx(it.second.memPoolStrIdx) << " ";
      GlobalTables::GetTypeTable().GetTypeFromTyIdx(it.second.tyIdx)->Dump(0);
      if (it.second.sigStrIdx.GetIdx()) {
        LogInfo::MapleLogger() << " \"" << GlobalTables::GetStrTable().GetStringFromStrIdx(it.second.sigStrIdx) << "\"";
      }
      LogInfo::MapleLogger() << std::endl;
    }
  }
  if (srcPosition.FileNum() != 0 && srcPosition.LineNum() != 0 && srcPosition.LineNum() != lastPrintedLineNum &&
      mod->CurFunction()->WithLocInfo()) {
    LogInfo::MapleLogger() << "LOC " << srcPosition.FileNum() << " " << srcPosition.LineNum() << std::endl;
    lastPrintedLineNum = srcPosition.LineNum();
  }
  for (auto &stmt : GetStmtNodes()) {
    stmt.Dump(mod, indent + 1);
  }
  PrintIndentation(indent);
  LogInfo::MapleLogger() << "}" << std::endl;
}

void LabelNode::Dump(const MIRModule *mod, int32 indent) const {
  ASSERT(mod != nullptr, "mod is null");
  if (srcPosition.FileNum() != 0 && srcPosition.LineNum() != 0 && srcPosition.LineNum() != lastPrintedLineNum &&
      mod->CurFunction()->WithLocInfo()) {
    LogInfo::MapleLogger() << "LOC " << srcPosition.FileNum() << " " << srcPosition.LineNum() << std::endl;
    lastPrintedLineNum = srcPosition.LineNum();
  }
  LogInfo::MapleLogger() << "@" << mod->CurFunction()->GetLabelName(labelIdx) << " ";
}

void CommentNode::Dump(const MIRModule *mod, int32 indent) const {
  ASSERT(mod != nullptr, "mod is null");
  if (srcPosition.FileNum() != 0 && srcPosition.LineNum() != 0 && srcPosition.LineNum() != lastPrintedLineNum &&
      mod->CurFunction()->WithLocInfo()) {
    LogInfo::MapleLogger() << "LOC " << srcPosition.FileNum() << " " << srcPosition.LineNum() << std::endl;
    lastPrintedLineNum = srcPosition.LineNum();
  }
  PrintIndentation(indent);
  LogInfo::MapleLogger() << "#" << comment << std::endl;
}

// mirnode verification support
bool ExcludeSmallIntTypeVerify(const BaseNode *opnd) {
  switch (opnd->GetPrimType()) {
    case PTY_u1:
    case PTY_i8:
    case PTY_u8:
    case PTY_i16:
    case PTY_u16:
      return false;
    default:
      break;
  }
  return true;
}

bool ArithTypeVerify(const BaseNode *opnd) {
  ASSERT(opnd != nullptr, "null ptr check");
  bool verifyResult = ExcludeSmallIntTypeVerify(opnd);
  if (!verifyResult) {
    LogInfo::MapleLogger() << "\n#Error:u1,i8,u8,i16,u16 should not be used as types of arithmetic operations\n";
    opnd->Dump(theModule);
  }
  return verifyResult;
}

inline bool ReadTypeVerify(const BaseNode *opnd) {
  bool verifyResult = ExcludeSmallIntTypeVerify(opnd);
  if (!verifyResult) {
    LogInfo::MapleLogger()
        << "\n#Error:u1,i8,u8,i16,u16 should not be used as result types for dread/iread/regread/ireadoff/ireadfpoff\n";
    opnd->Dump(theModule);
  }
  return verifyResult;
}

inline bool IntTypeVerify(PrimType ptyp) {
  return ptyp == PTY_i32 || ptyp == PTY_u32 || ptyp == PTY_i64 || ptyp == PTY_u64;
}

inline bool UnaryTypeVerify0(PrimType ptyp) {
  bool verifyResult = IntTypeVerify(ptyp);
  if (!verifyResult) {
    LogInfo::MapleLogger() << "\n#Error:result type of bnot,extractbits,sext,zext must be in [i32,u32,i64,u64]\n";
  }
  return verifyResult;
}

bool ArithResTypeVerify(PrimType ptyp) {
  switch (ptyp) {
    case PTY_i32:
    case PTY_u32:
    case PTY_i64:
    case PTY_u64:
    case PTY_f32:
    case PTY_f64:
      return true;
    case PTY_a32:
    case PTY_a64:
    case PTY_ptr:
      return theModule->IsCModule();
    default:
      break;
  }
  return false;
}

inline bool UnaryTypeVerify1(PrimType ptyp) {
  bool verifyResult = ArithResTypeVerify(ptyp);
  if (!verifyResult) {
    LogInfo::MapleLogger() << "\n#Error:result type of abs,neg must be in [i32,u32,i64,u64,f32,f64]\n";
  }
  return verifyResult;
}

inline bool UnaryTypeVerify2(PrimType ptyp) {
  bool verifyResult = IsPrimitiveFloat(ptyp);
  if (!verifyResult) {
    LogInfo::MapleLogger() << "\n#Error:result-type of recip,sqrt must be in [f32,f64]\n";
  }
  return verifyResult;
}

inline bool BinaryTypeVerify(PrimType ptyp) {
  return ArithResTypeVerify(ptyp) || IsPrimitiveDynType(ptyp);
}

inline bool BinaryGenericVerify(const BaseNode *bOpnd0, const BaseNode *bOpnd1) {
  ASSERT(bOpnd0 != nullptr, "null ptr check");
  ASSERT(bOpnd1 != nullptr, "null ptr check");
  return bOpnd0->Verify() && bOpnd1->Verify() && ArithTypeVerify(bOpnd0) && ArithTypeVerify(bOpnd1);
}

inline bool CompareTypeVerify(PrimType pType) {
  bool verifyResult = IsPrimitiveInteger(pType);
  if (!verifyResult) {
    LogInfo::MapleLogger() << "\n#Error:result type of eq,ge,gt,le,lt,ne must be primitive integer\n";
  }
  return verifyResult;
}

enum PTYGroup {
  kPTYGi32u32a32,
  kPTYGi32u32a32PtrRef,
  kPTYGi64u64a64,
  kPTYGPtrRef,
  kPTYGDynall,
  kPTYGu1,
  kPTYGSimpleObj,
  kPTYGSimpleStr,
  kPTYGOthers
};

uint8 GetCompGroupID(const BaseNode *opnd) {
  switch (opnd->GetPrimType()) {
    case PTY_i32:
    case PTY_u32:
    case PTY_a32:
      return kPTYGi32u32a32;
    case PTY_i64:
    case PTY_u64:
    case PTY_a64:
      return kPTYGi64u64a64;
    case PTY_ref:
    case PTY_ptr:
      return kPTYGPtrRef;
    case PTY_dynany:
    case PTY_dyni32:
    case PTY_dynf64:
    case PTY_dynstr:
    case PTY_dynobj:
    case PTY_dynundef:
    case PTY_dynbool:
    case PTY_dynf32:
    case PTY_dynnone:
    case PTY_dynnull:
      return kPTYGDynall;
    case PTY_u1:
      return kPTYGu1;
    case PTY_simpleobj:
      return kPTYGSimpleObj;
    case PTY_simplestr:
      return kPTYGSimpleStr;
    default:
      return kPTYGOthers;
  }
}

/*
  Refer to C11 Language Specification.
  $ 6.3.1.8 Usual arithmetic conversions
 */
bool CompatibleTypeVerify(const BaseNode *opnd1, const BaseNode *opnd2) {
  uint8 groupID1 = GetCompGroupID(opnd1);
  uint8 groupID2 = GetCompGroupID(opnd2);
  Opcode opCode2 = opnd2->GetOpCode();
  bool verifyResult = groupID1 == groupID2;
  if (opCode2 == OP_gcmallocjarray || opCode2 == OP_gcpermallocjarray) {
    verifyResult = groupID1 == kPTYGi32u32a32;
  }
  if (!verifyResult) {
    LogInfo::MapleLogger() << "\n#Error:incompatible operand types :\n";
    opnd1->Dump(theModule);
    opnd2->Dump(theModule);
  }
  return verifyResult;
}

bool FloatIntCvtTypeVerify(PrimType resPType, PrimType opndPType) {
  bool resTypeVerf = resPType == PTY_i32 || resPType == PTY_u32 || resPType == PTY_i64 || resPType == PTY_u64;
  if (!resTypeVerf) {
    LogInfo::MapleLogger() << "\n#Error:result-type of ceil,floor,round,trunc must be in [i32,u32,i64,u64]\n";
  }
  bool opndTypeVerf = opndPType == PTY_f32 || opndPType == PTY_f64;
  if (!opndTypeVerf) {
    LogInfo::MapleLogger() << "\n#Error:oerand-type of ceil,floor,round,trunc must be in [f32,f64]\n";
  }
  return resTypeVerf && opndTypeVerf;
}

inline MIRTypeKind GetTypeKind(StIdx stIdx) {
  MIRSymbol *var = theModule->CurFunction()->GetLocalOrGlobalSymbol(stIdx);
  ASSERT(var != nullptr, "null ptr check");
  MIRType *type = var->GetType();
  ASSERT(type != nullptr, "null ptr check");
  return type->GetKind();
}

inline MIRTypeKind GetTypeKind(TyIdx tyIdx) {
  MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  ASSERT(type != nullptr, "null ptr check");
  return type->GetKind();
}

inline MIRType *GetPointedMIRType(TyIdx tyIdx) {
  MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  ASSERT(type != nullptr, "null ptr check");
  MIRPtrType *ptrType = dynamic_cast<MIRPtrType*>(type);
  ASSERT(ptrType != nullptr, "null pointer check");
  return ptrType->GetPointedType();
}

inline MIRTypeKind GetPointedTypeKind(TyIdx tyIdx) {
  MIRType *pointedType = GetPointedMIRType(tyIdx);
  ASSERT(pointedType != nullptr, "null ptr check");
  return pointedType->GetKind();
}

bool GetFieldType(MIRSrcLang srcLang, const MIRStructType *structType, FieldID targetFid, TyIdx &tid) {
  if (structType == nullptr) {
    return false;
  }
  // For Java module class, find targetFid in inheritance chain firstly
  if (srcLang == kSrcLangJava) {
    if (structType->GetKind() == kTypeClass || structType->GetKind() == kTypeClassIncomplete) {
      const MIRClassType *classType = static_cast<const MIRClassType*>(structType);
      std::stack<MIRStructType*> inheritChain;
      TyIdx parentTyIdx = classType->GetParentTyIdx();
      while (parentTyIdx.GetIdx() > 0) {
        MIRStructType *parentType =
            static_cast<MIRStructType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(parentTyIdx));
        inheritChain.push(parentType);
        parentTyIdx = static_cast<MIRClassType*>(parentType)->GetParentTyIdx();
      }
      targetFid -= inheritChain.size();
      while (!inheritChain.empty()) {
        MIRClassType *curClassType = static_cast<MIRClassType*>(inheritChain.top());
        if (0 < static_cast<uint32>(targetFid) && static_cast<uint32>(targetFid) <= curClassType->GetFieldsSize()) {
          tid = curClassType->GetFieldsElemt(targetFid - 1).second.first;
          return true;
        } else {
          targetFid -= curClassType->GetFieldsSize();
        }
        inheritChain.pop();
      }
      if (0 < static_cast<uint32>(targetFid) && static_cast<uint32>(targetFid) <= classType->GetFieldsSize()) {
        tid = classType->GetFieldsElemt(targetFid - 1).second.first;
        return true;
      }
    }
  }
  return false;
}

MIRTypeKind GetFieldTypeKind(const MIRStructType *structType, FieldID fieldId) {
  TyIdx fieldTyIdx;
  if (fieldId > 0) {
    bool isValid = GetFieldType(theModule->GetSrcLang(), structType, fieldId, fieldTyIdx);
    // when mpl does not have complete class info
    if (!isValid) {
      LogInfo::MapleLogger() << "\n#Error:field not found, must have complete class info\n";
      return kTypeInvalid;
    }
  } else {
    ASSERT(static_cast<unsigned>(-fieldId) < structType->GetParentFieldsSize() + 1, "array index out of range");
    fieldTyIdx = structType->GetParentFieldsElemt(-fieldId - 1).second.first;
  }
  return GetTypeKind(fieldTyIdx);
}

inline bool IsStructureTypeKind(MIRTypeKind kind) {
  return kind == kTypeStruct || kind == kTypeStructIncomplete || kind == kTypeUnion || kind == kTypeClass ||
         kind == kTypeClassIncomplete || kind == kTypeInterface || kind == kTypeInterfaceIncomplete;
}

inline bool IsStructureVerify(FieldID fieldID, StIdx stIdx) {
  if (fieldID != 0) {
    if (!IsStructureTypeKind(GetTypeKind(stIdx))) {
      LogInfo::MapleLogger() << "\n#Error:if fieldID is not 0, the variable must be a structure\n";
      return false;
    }
  }
  return true;
}

inline bool IsStructureVerify(FieldID fieldID, TyIdx tyIdx) {
  if (fieldID != 0) {
    if (!IsStructureTypeKind(GetTypeKind(tyIdx))) {
      LogInfo::MapleLogger() << "\n#Error:if fieldID is not 0, the variable must be a structure\n";
      return false;
    }
  }
  return true;
}

bool IsSignedType(const BaseNode *opnd) {
  switch (opnd->GetPrimType()) {
    case PTY_i32:
    case PTY_i64:
    case PTY_f32:
    case PTY_f64:
    case PTY_dyni32:
    case PTY_dynf32:
    case PTY_dynf64:
      return true;
    default:
      break;
  }
  return false;
}

inline bool BinaryStrictSignVerify0(const BaseNode *bOpnd0, const BaseNode *bOpnd1) {
  ASSERT(bOpnd0 != nullptr, "bOpnd0 is null");
  ASSERT(bOpnd1 != nullptr, "bOpnd1 is null");
  bool isDynany = (bOpnd0->GetPrimType() == PTY_dynany || bOpnd1->GetPrimType() == PTY_dynany);
  return isDynany || (IsSignedType(bOpnd0) && IsSignedType(bOpnd1)) || (!IsSignedType(bOpnd0) && !IsSignedType(bOpnd1));
}

bool BinaryStrictSignVerify1(const BaseNode *bOpnd0, const BaseNode *bOpnd1, const BaseNode *res) {
  if (GetCompGroupID(res) == kPTYGDynall) {
    return BinaryStrictSignVerify0(bOpnd0, res) && BinaryStrictSignVerify0(bOpnd1, res) &&
           BinaryStrictSignVerify0(bOpnd0, bOpnd1);
  }
  return (IsSignedType(bOpnd0) && IsSignedType(bOpnd1) && IsSignedType(res)) ||
         (!IsSignedType(bOpnd0) && !IsSignedType(bOpnd1) && !IsSignedType(res));
}

bool UnaryNode::Verify() const {
  bool resTypeVerf = true;
  if (GetOpCode() == OP_bnot) {
    resTypeVerf = UnaryTypeVerify0(GetPrimType());
  } else if (GetOpCode() == OP_lnot) {
    if (!IsPrimitiveInteger(GetPrimType())) {
      resTypeVerf = false;
      LogInfo::MapleLogger() << "\n#Error:result-type of lnot must be primitive integer\n";
    }
  } else if (GetOpCode() == OP_abs || GetOpCode() == OP_neg) {
    resTypeVerf = UnaryTypeVerify1(GetPrimType());
  } else if (GetOpCode() == OP_recip || GetOpCode() == OP_sqrt) {
    resTypeVerf = UnaryTypeVerify2(GetPrimType());
  }
  bool opndTypeVerf = true;
  if (GetOpCode() != OP_lnot) {
    opndTypeVerf = ArithTypeVerify(uOpnd);
  }
  // When an opcode only specifies one type, check for compatibility
  // between the operands and the result-type.
  bool compVerf = CompatibleTypeVerify(uOpnd, this);
  bool opndExprVerf = uOpnd->Verify();
  return resTypeVerf && opndTypeVerf && compVerf && opndExprVerf;
}

bool TypeCvtNode::Verify() const {
  bool opndTypeVerf = true;
  bool opndSizeVerf = true;
  if (GetOpCode() == OP_ceil || GetOpCode() == OP_floor || GetOpCode() == OP_round || GetOpCode() == OP_trunc) {
    opndTypeVerf = FloatIntCvtTypeVerify(GetPrimType(), Opnd()->GetPrimType());
  } else if (GetOpCode() == OP_retype) {
    if (GetPrimTypeSize(GetPrimType()) != GetPrimTypeSize(Opnd()->GetPrimType())) {
      opndSizeVerf = false;
      LogInfo::MapleLogger() << "\n#Error:The size of opnd0 and prim-type must be the same\n";
    }
  }
  bool opndExprVerf = Opnd()->Verify();
  return opndTypeVerf && opndSizeVerf && opndExprVerf;
}

bool IreadNode::Verify() const {
  bool addrExprVerf = Opnd()->Verify();
  bool pTypeVerf = ReadTypeVerify(this);
  bool structVerf = true;
  if (GetTypeKind(tyIdx) != kTypePointer) {
    LogInfo::MapleLogger() << "\n#Error:<type> must be a pointer type\n";
    return false;
  }
  if (GetOpCode() == OP_iaddrof) {
    pTypeVerf = IsAddress(GetPrimType());
    if (!pTypeVerf) {
      LogInfo::MapleLogger() << "\n#Error:prim-type must be either ptr, ref, a32 or a64\n";
    }
  } else {
    if (fieldID == 0 && IsStructureTypeKind(GetPointedTypeKind(tyIdx))) {
      if (GetPrimType() != PTY_agg) {
        pTypeVerf = false;
        LogInfo::MapleLogger()
            << "\n#Error:If the content dereferenced is a structure, then <prim-type> should specify agg\n";
      }
    }
  }
  if (fieldID != 0) {
    if (!IsStructureTypeKind(GetPointedTypeKind(tyIdx))) {
      structVerf = false;
      LogInfo::MapleLogger() << "\n#Error:If field-id is not 0, then type must specify pointer to a structure\n";
    } else {
      MIRType *type = GetPointedMIRType(tyIdx);
      MIRStructType *stty = dynamic_cast<MIRStructType*>(type);
      if (GetOpCode() == OP_iread && stty->GetFieldsSize() != 0) {
        if (IsStructureTypeKind(GetFieldTypeKind(stty, fieldID))) {
          if (GetPrimType() != PTY_agg) {
            pTypeVerf = false;
            LogInfo::MapleLogger() << "\n#Error:If the field itself is a structure, prim-type should specify agg\n";
          }
        }
      }
    }
  }
  return addrExprVerf && pTypeVerf && structVerf;
}

bool RegreadNode::Verify() const {
  bool pTypeVerf = ReadTypeVerify(this);
  return pTypeVerf;
}

bool IreadoffNode::Verify() const {
  bool pTypeVerf = ReadTypeVerify(this);
  return pTypeVerf;
}

bool IreadFPoffNode::Verify() const {
  bool pTypeVerf = ReadTypeVerify(this);
  return pTypeVerf;
}

bool ExtractbitsNode::Verify() const {
  bool opndExprVerf = Opnd()->Verify();
  bool opndTypeVerf = ArithTypeVerify(Opnd());
  bool compVerf = CompatibleTypeVerify(Opnd(), this);
  bool resTypeVerf = UnaryTypeVerify0(GetPrimType());
  constexpr int kNumBitsInByte = 8;
  bool opnd0SizeVerf = (kNumBitsInByte * GetPrimTypeSize(Opnd()->GetPrimType()) >= bitsSize);
  if (!opnd0SizeVerf) {
    LogInfo::MapleLogger()
        << "\n#Error: The operand of extractbits must be large enough to contain the specified bitfield\n";
  }
  return opndExprVerf && opndTypeVerf && compVerf && resTypeVerf && opnd0SizeVerf;
}

bool BinaryNode::Verify() const {
  bool opndsVerf = BinaryGenericVerify(GetBOpnd(0), GetBOpnd(1));
  bool resTypeVerf = BinaryTypeVerify(GetPrimType());
  if (!resTypeVerf && theModule->IsCModule()) {
    if ((IsAddress(GetBOpnd(0)->GetPrimType()) && !IsAddress(GetBOpnd(1)->GetPrimType())) ||
        (!IsAddress(GetBOpnd(0)->GetPrimType()) && IsAddress(GetBOpnd(1)->GetPrimType()))) {
      resTypeVerf = true;  // don't print the same kind of error message twice
      if (GetOpCode() != OP_add && GetOpCode() != OP_sub) {
        LogInfo::MapleLogger() << "\n#Error: Only add and sub are allowed for pointer arithemetic\n";
        this->Dump(theModule);
      } else if (!IsAddress(GetPrimType())) {
        LogInfo::MapleLogger()
            << "\n#Error: Adding an offset to a pointer or subtracting one from a pointer should result in a pointer "
               "value\n";
        this->Dump(theModule);
      }
    }
  }
  if (!resTypeVerf) {
    LogInfo::MapleLogger()
        << "\n#Error:result type of [add,div,sub,mul,max,min] and [ashr,band,bior,bxor,land,lior,lshr,shl,rem] must "
           "be in [i32,u32,i64,u64,f32,f64,dynamic-type]\n";
    this->Dump(theModule);
  }
  bool comp0Verf = CompatibleTypeVerify(GetBOpnd(0), this);
  bool comp1Verf = CompatibleTypeVerify(GetBOpnd(1), this);
  bool signVerf = true;
  bool typeVerf = resTypeVerf && comp0Verf && comp1Verf;
  if (typeVerf) {
    if (GetOpCode() == OP_div || GetOpCode() == OP_mul || GetOpCode() == OP_rem || GetOpCode() == OP_max ||
        GetOpCode() == OP_min) {
      signVerf = BinaryStrictSignVerify1(GetBOpnd(0), GetBOpnd(1), this);
      if (!signVerf) {
        LogInfo::MapleLogger()
            << "\n#Error:the result and operands of [div,mul,rem,max,min] must be of the same sign\n";
      }
    }
  }
  return opndsVerf && typeVerf && signVerf;
}

bool CompareNode::Verify() const {
  bool opndsVerf = BinaryGenericVerify(GetBOpnd(0), GetBOpnd(1));
  bool compVerf = CompatibleTypeVerify(GetBOpnd(0), GetBOpnd(1));
  bool resTypeVerf = CompareTypeVerify(GetPrimType());
  if (!resTypeVerf) {
    this->Dump(theModule);
  }
  bool signVerf = true;
  bool typeVerf = compVerf && resTypeVerf;
  if (typeVerf && GetOpCode() != OP_eq && GetOpCode() != OP_ne) {
    signVerf = BinaryStrictSignVerify0(GetBOpnd(0), GetBOpnd(1));
    if (!signVerf) {
      LogInfo::MapleLogger() << "\n#Error:the operands of [ge,gt,le,lt] must be of the same sign\n";
    }
  }
  return opndsVerf && typeVerf && signVerf;
}

bool DepositbitsNode::Verify() const {
  bool opndsVerf = BinaryGenericVerify(GetBOpnd(0), GetBOpnd(1));
  bool resTypeVerf = IntTypeVerify(GetPrimType());
  constexpr int kNumBitsInByte = 8;
  bool opnd0SizeVerf = (kNumBitsInByte * GetPrimTypeSize(GetBOpnd(0)->GetPrimType()) >= bitsSize);
  if (!opnd0SizeVerf) {
    LogInfo::MapleLogger() << "\n#Error:opnd0 of depositbits must be large enough to contain the specified bitfield\n";
  }
  return opndsVerf && resTypeVerf && opnd0SizeVerf;
}

bool IntrinsicopNode::Verify() const {
  return VerifyOpnds();
}

bool TernaryNode::Verify() const {
  bool comp1Verf = CompatibleTypeVerify(topnd[1], this);
  bool comp2Verf = CompatibleTypeVerify(topnd[2], this);
  bool opnd0TypeVerf = IsPrimitiveInteger(topnd[0]->GetPrimType());
  if (!opnd0TypeVerf) {
    LogInfo::MapleLogger() << "\n#Error:select-opnd0 must be of integer type\n";
  }
  return comp1Verf && comp2Verf && opnd0TypeVerf;
}

bool SizeoftypeNode::Verify() const {
  return true;
}

bool ArrayNode::Verify() const {
  bool opndsVerf = VerifyOpnds();
  bool resTypeVerf = IsAddress(GetPrimType());
  bool opndsTypeVerf = true;
  if (!resTypeVerf) {
    LogInfo::MapleLogger() << "\n#Error:result-type of array must be in [ptr,ref,a32,a64]\n";
  }
  bool opnd0TypeVerf = IsAddress(GetNopndAt(0)->GetPrimType());
  if (!opnd0TypeVerf) {
    LogInfo::MapleLogger() << "\n#Error:result-type of array-opnd0 must be in [ptr,ref,a32,a64]\n";
  }
  for (size_t i = 1; i < NumOpnds(); i++) {
    if (!IntTypeVerify(GetNopndAt(i)->GetPrimType())) {
      opndsTypeVerf = false;
      LogInfo::MapleLogger() << "\n#Error:result of the array index operands must be in [i32,u32,i64,u64]\n";
    }
  }
  return opndsVerf && resTypeVerf && opnd0TypeVerf && opndsTypeVerf;
}

bool DassignNode::Verify() const {
  bool structVerf = IsStructureVerify(fieldID, stIdx);
  bool rhsVerf = GetRHS()->Verify();
  return structVerf && rhsVerf;
}

bool AddrofNode::Verify() const {
  bool pTypeVerf = true;
  bool structVerf = IsStructureVerify(fieldID, GetStIdx());
  if (GetOpCode() == OP_dread) {
    pTypeVerf = ReadTypeVerify(this);
    if (fieldID == 0 && IsStructureTypeKind(GetTypeKind(GetStIdx()))) {
      if (GetPrimType() != PTY_agg) {
        pTypeVerf = false;
        LogInfo::MapleLogger() << "\n#Error:if variable is a structure, prim-type should specify agg\n";
      }
    }
    if (fieldID != 0 && structVerf) {
      MIRSymbol *var = theModule->CurFunction()->GetLocalOrGlobalSymbol(GetStIdx());
      MIRType *type = var->GetType();
      MIRStructType *stty = dynamic_cast<MIRStructType*>(type);
      ASSERT(stty != nullptr, "null pointer check");
      if (IsStructureTypeKind(GetFieldTypeKind(stty, fieldID))) {
        if (GetPrimType() != PTY_agg) {
          pTypeVerf = false;
          LogInfo::MapleLogger() << "\n#Error:if the field itself is a structure, prim-type should specify agg\n";
        }
      }
    }
  } else {
    pTypeVerf = IsAddress(GetPrimType());
    if (!pTypeVerf) {
      LogInfo::MapleLogger()
          << "\n#Error:result-type of addrof,addroflabel,addroffunc,iaddrof must be in [ptr,ref,a32,a64]\n";
    }
  }
  return pTypeVerf && structVerf;
}

bool AddroffuncNode::Verify() const {
  bool addrTypeVerf = IsAddress(GetPrimType());
  if (!addrTypeVerf) {
    LogInfo::MapleLogger()
        << "\n#Error:result-type of addrof,addroflabel,addroffunc,iaddrof must be in [ptr,ref,a32,a64]\n";
  }
  return addrTypeVerf;
}

bool AddroflabelNode::Verify() const {
  bool addrTypeVerf = IsAddress(GetPrimType());
  if (!addrTypeVerf) {
    LogInfo::MapleLogger()
        << "\n#Error:result-type of addrof,addroflabel,addroffunc,iaddrof must be in [ptr,ref,a32,a64]\n";
  }
  return addrTypeVerf;
}

bool IassignNode::Verify() const {
  bool addrExpVerf = addrExpr->Verify();
  bool rhsVerf = rhs->Verify();
  bool structVerf = true;
  if (GetTypeKind(tyIdx) != kTypePointer) {
    LogInfo::MapleLogger() << "\n#Error:<type> must be a pointer type\n";
    return false;
  }
  if (fieldID != 0) {
    if (!IsStructureTypeKind(GetPointedTypeKind(tyIdx))) {
      structVerf = false;
      LogInfo::MapleLogger() << "\n#Error:If field-id is not 0, the computed address must correspond to a structure\n";
    }
  }
  return addrExpVerf && rhsVerf && structVerf;
}

bool IassignoffNode::Verify() const {
  bool addrVerf = GetBOpnd(0)->Verify();
  bool rhsVerf = GetBOpnd(1)->Verify();
  bool compVerf = CompatibleTypeVerify(this, GetBOpnd(1));
  return addrVerf && rhsVerf && compVerf;
}

bool IassignFPoffNode::Verify() const {
  bool rhsVerf = Opnd()->Verify();
  bool compVerf = CompatibleTypeVerify(this, Opnd());
  return rhsVerf && compVerf;
}

bool RegassignNode::Verify() const {
  bool rhsVerf = Opnd()->Verify();
  bool compVerf = CompatibleTypeVerify(this, Opnd());
  return rhsVerf && compVerf;
}

bool CondGotoNode::Verify() const {
  bool opndExprVerf = UnaryStmtNode::Opnd()->Verify();
  bool opndTypeVerf = true;
  if (!IsPrimitiveInteger(UnaryStmtNode::Opnd()->GetPrimType())) {
    opndTypeVerf = false;
    LogInfo::MapleLogger() << "\n#Error:the operand of brfalse and trfalse must be primitive integer\n";
  }
  return opndExprVerf && opndTypeVerf;
}

bool SwitchNode::Verify() const {
  bool opndExprVerf = switchOpnd->Verify();
  bool opndTypeVerf = IntTypeVerify(switchOpnd->GetPrimType());
  if (!opndTypeVerf) {
    LogInfo::MapleLogger() << "\n#Error: the operand of switch must be in [i32,u32,i64,u64]\n";
  }
  return opndExprVerf && opndTypeVerf;
}

bool BinaryStmtNode::Verify() const {
  return GetBOpnd(0)->Verify() && GetBOpnd(1)->Verify() && CompatibleTypeVerify(GetBOpnd(0), GetBOpnd(1)) &&
         BinaryStrictSignVerify0(GetBOpnd(0), GetBOpnd(1));
}

bool RangegotoNode::Verify() const {
  bool opndExprVerf = Opnd()->Verify();
  bool opndTypeVerf = IntTypeVerify(Opnd()->GetPrimType());
  if (!opndTypeVerf) {
    LogInfo::MapleLogger() << "\n#Error: the operand of rangegoto must be in [i32,u32,i64,u64]\n";
  }
  return opndExprVerf && opndTypeVerf;
}

bool BlockNode::Verify() const {
  for (auto &stmt : GetStmtNodes()) {
    if (!stmt.Verify()) {
      return false;
    }
  }
  return true;
}

bool DoloopNode::Verify() const {
  bool startVerf = startExpr->Verify();
  bool contVerf = condExpr->Verify();
  bool incrVerf = incrExpr->Verify();
  bool doBodyVerf = true;
  if (doBody) {
    doBodyVerf = doBody->Verify();
  }
  return startVerf && contVerf && incrVerf && doBodyVerf;
}

bool IfStmtNode::Verify() const {
  bool condVerf = Opnd()->Verify();
  bool thenVerf = true;
  bool elseVerf = true;
  if (thenPart) {
    thenVerf = thenPart->Verify();
  }
  if (elsePart) {
    elseVerf = elsePart->Verify();
  }
  return condVerf && thenVerf && elseVerf;
}

bool WhileStmtNode::Verify() const {
  bool condVerf = Opnd()->Verify();
  bool bodyVerf = true;
  if (body) {
    bodyVerf = body->Verify();
  }
  return condVerf && bodyVerf;
}

bool NaryStmtNode::Verify() const {
  return VerifyOpnds();
}

bool CallNode::Verify() const {
  return VerifyOpnds();
}

bool IcallNode::Verify() const {
  bool nOpndsVerf = true;
  for (size_t i = 0; i < NumOpnds(); i++) {
    if (!GetNopndAt(i)->Verify()) {
      nOpndsVerf = false;
      break;
    }
  }
  return nOpndsVerf;
}

bool IntrinsiccallNode::Verify() const {
  return VerifyOpnds();
}

}  // namespace maple
