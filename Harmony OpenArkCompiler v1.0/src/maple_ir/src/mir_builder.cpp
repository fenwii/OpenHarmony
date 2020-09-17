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
#include "mir_builder.h"
#include <string>
#include <iostream>

namespace maple {
// This is for compiler-generated metadata 1-level struct
void MIRBuilder::AddIntFieldConst(const MIRStructType *sType, MIRAggConst *newConst, uint32 fieldID, int64 constValue) {
  if (sType != nullptr && newConst != nullptr) {
    MIRConst *fieldConst = mirModule->GetMemPool()->New<MIRIntConst>(constValue, sType->GetElemType(fieldID - 1));
    MapleVector<MIRConst*> &constVec = newConst->GetConstVec();
    fieldConst->SetFieldID(fieldID);
    constVec.push_back(fieldConst);
  }
}

// This is for compiler-generated metadata 1-level struct
void MIRBuilder::AddAddrofFieldConst(const MIRStructType *structType, MIRAggConst *newConst, uint32 fieldID,
                                     const MIRSymbol *fieldSymbol) {
  if (structType != nullptr && newConst != nullptr && fieldSymbol != nullptr) {
    AddrofNode *fieldExpr = CreateExprAddrof(0, fieldSymbol, mirModule->GetMemPool());
    MIRConst *fieldConst = mirModule->GetMemPool()->New<MIRAddrofConst>(fieldExpr->GetStIdx(), fieldExpr->GetFieldID(),
                                                                        structType->GetElemType(fieldID - 1));
    MapleVector<MIRConst*> &constVec = newConst->GetConstVec();
    fieldConst->SetFieldID(fieldID);
    constVec.push_back(fieldConst);
  }
}

// This is for compiler-generated metadata 1-level struct
void MIRBuilder::AddAddroffuncFieldConst(const MIRStructType *structType, MIRAggConst *newConst, uint32 fieldID,
                                         const MIRSymbol *funcSymbol) {
  if (structType != nullptr && newConst != nullptr && funcSymbol != nullptr) {
    MIRConst *fieldConst = nullptr;
    MIRFunction *vMethod = funcSymbol->GetFunction();
    if (vMethod->IsAbstract()) {
      fieldConst = mirModule->GetMemPool()->New<MIRIntConst>(0, structType->GetElemType(fieldID - 1));
    } else {
      AddroffuncNode *addrofFuncExpr =
          CreateExprAddroffunc(funcSymbol->GetFunction()->GetPuidx(), mirModule->GetMemPool());
      fieldConst = mirModule->GetMemPool()->New<MIRAddroffuncConst>(addrofFuncExpr->GetPUIdx(),
                                                                    structType->GetElemType(fieldID - 1));
    }
    fieldConst->SetFieldID(fieldID);
    MapleVector<MIRConst*> &constVec = newConst->GetConstVec();
    constVec.push_back(fieldConst);
  }
}

// fieldID is continuously being updated during traversal;
// when the field is found, its field id is returned via fieldID
bool MIRBuilder::TraverseToNamedField(MIRStructType *structType, GStrIdx nameIdx, uint32 &fieldID) {
  TyIdx tid(0);
  return TraverseToNamedFieldWithTypeAndMatchStyle(structType, nameIdx, tid, fieldID, kMatchAnyField);
}

bool MIRBuilder::IsOfSameType(MIRType *type1, MIRType *type2) {
  ASSERT(type1 != nullptr, "type1 is null");
  ASSERT(type2 != nullptr, "type2 is null");
  if (type2->GetKind() != type1->GetKind()) {
    return false;
  }
  switch (type1->GetKind()) {
    case kTypeScalar: {
      return (type1->GetTypeIndex() == type2->GetTypeIndex());
    }
    case kTypePointer: {
      MIRPtrType *ptrType = static_cast<MIRPtrType*>(type1);
      MIRPtrType *ptrTypeIt = static_cast<MIRPtrType*>(type2);
      if (ptrType->GetPointedTyIdx() == ptrTypeIt->GetPointedTyIdx()) {
        return true;
      } else {
        return IsOfSameType(GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptrType->GetPointedTyIdx()),
                            GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptrTypeIt->GetPointedTyIdx()));
      }
    }
    case kTypeJArray: {
      MIRJarrayType *atype1 = static_cast<MIRJarrayType*>(type1);
      MIRJarrayType *atype2 = static_cast<MIRJarrayType*>(type2);
      if (atype1->GetDim() != atype2->GetDim()) {
        return false;
      }
      return IsOfSameType(atype1->GetElemType(), atype2->GetElemType());
    }
    default: {
      return type1->GetTypeIndex() == type2->GetTypeIndex();
    }
  }
}

// traverse parent first but match self first.
void MIRBuilder::TraverseToNamedFieldWithType(MIRStructType *structType, GStrIdx nameIdx, TyIdx typeIdx,
                                              uint32 &fieldID, uint32 &idx) {
  if (structType == nullptr) {
    return;
  }
  if (structType->IsIncomplete()) {
    incompleteTypeRefedSet.insert(structType->GetTypeIndex());
  }
  // process parent
  if (structType->GetKind() == kTypeClass || structType->GetKind() == kTypeClassIncomplete) {
    MIRClassType *classType = static_cast<MIRClassType*>(structType);
    MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(classType->GetParentTyIdx());
    MIRStructType *parentType = static_cast<MIRStructType*>(type);
    if (parentType != nullptr) {
      fieldID++;
      TraverseToNamedFieldWithType(parentType, nameIdx, typeIdx, fieldID, idx);
    }
  }
  for (uint32 fieldIdx = 0; fieldIdx < structType->GetFieldsSize(); fieldIdx++) {
    fieldID++;
    TyIdx fieldTyIdx = structType->GetFieldsElemt(fieldIdx).second.first;
    MIRType *fieldType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(fieldTyIdx);
    if (structType->GetFieldsElemt(fieldIdx).first == nameIdx) {
      if ((typeIdx == 0 || fieldTyIdx == typeIdx)) {
        idx = fieldID;
        continue;
      }
      // for pointer type, check their pointed type
      MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(typeIdx);
      if (IsOfSameType(type, fieldType)) {
        idx = fieldID;
      }
    }

    if (fieldType->GetKind() == kTypeStruct || fieldType->GetKind() == kTypeStructIncomplete ||
        fieldType->GetKind() == kTypeClass || fieldType->GetKind() == kTypeClassIncomplete ||
        fieldType->GetKind() == kTypeInterface || fieldType->GetKind() == kTypeInterfaceIncomplete) {
      MIRStructType *subStructType = static_cast<MIRStructType*>(fieldType);
      TraverseToNamedFieldWithType(subStructType, nameIdx, typeIdx, fieldID, idx);
    }
  }
}

// fieldID is continuously being updated during traversal;
// when the field is found, its field id is returned via fieldID
//
// typeidx: TyIdx(0) means do not check types.
// matchstyle: 0: do not match but traverse to update fieldID
//             1: match top level field only
//             2: match any field
//             4: traverse parent first
//          0xc: do not match but traverse to update fieldID, traverse parent first, found in child
bool MIRBuilder::TraverseToNamedFieldWithTypeAndMatchStyle(MIRStructType *structType, GStrIdx nameIdx, TyIdx typeIdx,
                                                           uint32 &fieldID, unsigned int matchStyle) {
  if (structType == nullptr) {
    return false;
  }
  if (structType->IsIncomplete()) {
    incompleteTypeRefedSet.insert(structType->GetTypeIndex());
  }
  if (matchStyle & kParentFirst) {
    // process parent
    if (structType->GetKind() == kTypeClass || structType->GetKind() == kTypeClassIncomplete) {
      MIRClassType *classType = static_cast<MIRClassType*>(structType);
      MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(classType->GetParentTyIdx());
      MIRStructType *parentType = static_cast<MIRStructType*>(type);
      if (parentType != nullptr) {
        fieldID++;
        if (matchStyle == (kFoundInChild | kParentFirst | kUpdateFieldID)) {
          matchStyle = kParentFirst;
          uint32 idxBackup = nameIdx.GetIdx();
          nameIdx.SetIdx(0);
          // do not match but traverse to update fieldID, traverse parent first
          TraverseToNamedFieldWithTypeAndMatchStyle(parentType, nameIdx, typeIdx, fieldID, matchStyle);
          nameIdx.SetIdx(idxBackup);
        } else if (TraverseToNamedFieldWithTypeAndMatchStyle(parentType, nameIdx, typeIdx, fieldID, matchStyle)) {
          return true;
        }
      }
    } else {
      return false;
    }
  }
  for (uint32 fieldIdx = 0; fieldIdx < structType->GetFieldsSize(); fieldIdx++) {
    fieldID++;
    TyIdx fieldTyIdx = structType->GetFieldsElemt(fieldIdx).second.first;
    MIRType *fieldType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(fieldTyIdx);
    ASSERT(fieldType != nullptr, "fieldType is null");
    if (matchStyle && structType->GetFieldsElemt(fieldIdx).first == nameIdx) {
      if ((typeIdx == 0 || fieldTyIdx == typeIdx)) {
        return true;
      }
      // for pointer type, check their pointed type
      MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(typeIdx);
      if (IsOfSameType(type, fieldType)) {
        return true;
      }
    }
    unsigned int style = matchStyle & kMatchAnyField;
    if (fieldType->GetKind() == kTypeStruct || fieldType->GetKind() == kTypeStructIncomplete ||
        fieldType->GetKind() == kTypeClass || fieldType->GetKind() == kTypeClassIncomplete ||
        fieldType->GetKind() == kTypeInterface || fieldType->GetKind() == kTypeInterfaceIncomplete) {
      MIRStructType *subStructType = static_cast<MIRStructType*>(fieldType);
      if (TraverseToNamedFieldWithTypeAndMatchStyle(subStructType, nameIdx, typeIdx, fieldID, style)) {
        return true;
      }
    }
  }
  return false;
}

FieldID MIRBuilder::GetStructFieldIDFromNameAndType(MIRType *type, const std::string &name, TyIdx idx,
                                                    unsigned int matchStyle) {
  MIRStructType *structType = static_cast<MIRStructType*>(type);
  uint32 fieldID = 0;
  GStrIdx strIdx = GetStringIndex(name);
  if (TraverseToNamedFieldWithTypeAndMatchStyle(structType, strIdx, idx, fieldID, matchStyle)) {
    return fieldID;
  }
  return 0;
}

FieldID MIRBuilder::GetStructFieldIDFromNameAndType(MIRType *type, const std::string &name, TyIdx idx) {
  return GetStructFieldIDFromNameAndType(type, name, idx, kMatchAnyField);
}

FieldID MIRBuilder::GetStructFieldIDFromNameAndTypeParentFirst(MIRType *type, const std::string &name, TyIdx idx) {
  return GetStructFieldIDFromNameAndType(type, name, idx, kParentFirst);
}

FieldID MIRBuilder::GetStructFieldIDFromNameAndTypeParentFirstFoundInChild(MIRType *type, const std::string &name,
                                                                           TyIdx idx) {
  // do not match but traverse to update fieldid, traverse parent first, found in child
  return GetStructFieldIDFromNameAndType(type, name, idx, (kFoundInChild | kParentFirst | kUpdateFieldID));
}

FieldID MIRBuilder::GetStructFieldIDFromFieldName(MIRType *type, const std::string &name) {
  return GetStructFieldIDFromNameAndType(type, name, TyIdx(0), kMatchAnyField);
}

FieldID MIRBuilder::GetStructFieldIDFromFieldNameParentFirst(MIRType *type, const std::string &name) {
  return GetStructFieldIDFromNameAndType(type, name, TyIdx(0), kParentFirst);
}

void MIRBuilder::SetStructFieldIDFromFieldName(MIRType *structtype, const std::string &name, GStrIdx newStrIdx,
                                               const MIRType *newFieldType) {
  MIRStructType *structType = static_cast<MIRStructType*>(structtype);
  CHECK_FATAL(structtype != nullptr, "structType is null");
  uint32 fieldID = 0;
  GStrIdx strIdx = GetStringIndex(name);
  while (true) {
    if (structType->GetElemStrIdx(fieldID) == strIdx) {
      if (newStrIdx != 0) {
        structType->SetElemStrIdx(fieldID, newStrIdx);
      }
      if (newFieldType) {
        structType->SetElemtTyIdx(fieldID, newFieldType->GetTypeIndex());
      }
      return;
    }
    fieldID++;
  }
}

// create a function named str
MIRFunction *MIRBuilder::GetOrCreateFunction(const std::string &str, TyIdx retTyIdx) {
  GStrIdx strIdx = GetStringIndex(str);
  MIRSymbol *funcSt = nullptr;
  if (strIdx != 0) {
    funcSt = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(strIdx);
    if (funcSt == nullptr) {
      funcSt = CreateSymbol(TyIdx(0), strIdx, kStFunc, kScText, nullptr, kScopeGlobal);
    } else {
      ASSERT(funcSt->GetSKind() == kStFunc, "runtime check error");
      return funcSt->GetFunction();
    }
  } else {
    strIdx = GetOrCreateStringIndex(str);
    funcSt = CreateSymbol(TyIdx(0), strIdx, kStFunc, kScText, nullptr, kScopeGlobal);
  }
  MIRFunction *fn = mirModule->GetMemPool()->New<MIRFunction>(mirModule, funcSt->GetStIdx());
  fn->Init();
  fn->SetPuidx(GlobalTables::GetFunctionTable().GetFuncTable().size());
  MIRFuncType *funcType = mirModule->GetMemPool()->New<MIRFuncType>();
  fn->SetMIRFuncType(funcType);
  fn->SetReturnTyIdx(retTyIdx);
  GlobalTables::GetFunctionTable().GetFuncTable().push_back(fn);
  funcSt->SetFunction(fn);
  return fn;
}

MIRFunction *MIRBuilder::GetFunctionFromSymbol(MIRSymbol *funcSymbol) const {
  if (!funcSymbol) {
    return nullptr;
  }
  ASSERT(funcSymbol->GetSKind() == kStFunc, "Symbol %s is not a function symbol", funcSymbol->GetName().c_str());
  return funcSymbol->GetFunction();
}

MIRFunction *MIRBuilder::GetFunctionFromName(const std::string &str) {
  return GetFunctionFromSymbol(
      GlobalTables::GetGsymTable().GetSymbolFromStrIdx(GlobalTables::GetStrTable().GetStrIdxFromName(str)));
}

MIRFunction *MIRBuilder::GetFunctionFromStidx(StIdx stIdx) {
  return GetFunctionFromSymbol(GlobalTables::GetGsymTable().GetSymbolFromStidx(stIdx.Idx()));
}

MIRSymbol *MIRBuilder::GetOrCreateDecl(const std::string &str, const MIRType *type, MIRFunction *func, bool isLocal,
                                       bool &created) {
  MIRSymbolTable *symbolTable = nullptr;
  if (isLocal) {
    if (func) {
      symbolTable = func->GetSymTab();
    } else {
      MIRFunction *currentFunctionInner = GetCurrentFunction();
      CHECK_FATAL(currentFunctionInner != nullptr, "null ptr check");
      symbolTable = currentFunctionInner->GetSymTab();
    }
    ASSERT(symbolTable != nullptr, "symbol_table is null in MIRBuilder::GetOrCreateDecl");
  }
  GStrIdx strIdx = GetStringIndex(str);
  if (strIdx != 0) {
    StIdx stidx =
        isLocal ? symbolTable->GetStIdxFromStrIdx(strIdx) : GlobalTables::GetGsymTable().GetStIdxFromStrIdx(strIdx);
    if (stidx.Idx() != 0) {
      created = false;
      return isLocal ? symbolTable->GetSymbolFromStIdx(stidx.Idx())
                     : GlobalTables::GetGsymTable().GetSymbolFromStidx(stidx.Idx());
    }
  }
  created = true;
  strIdx = GetOrCreateStringIndex(str);
  MIRSymbol *st =
      isLocal ? symbolTable->CreateSymbol(kScopeLocal) : GlobalTables::GetGsymTable().CreateSymbol(kScopeGlobal);
  st->SetNameStrIdx(strIdx);
  st->SetTyIdx(type->GetTypeIndex());
  if (isLocal) {
    (void)symbolTable->AddToStringSymbolMap(st);
  } else {
    (void)GlobalTables::GetGsymTable().AddToStringSymbolMap(st);
  }
  return st;
}

MIRSymbol *MIRBuilder::GetOrCreateDeclInFunc(const std::string &str, const MIRType *type, MIRFunction *func) {
  bool isCreated = false;
  MIRSymbol *st = GetOrCreateDecl(str, type, func, true, isCreated);
  if (isCreated) {
    st->SetStorageClass(kScAuto);
    st->SetSKind(kStVar);
  }
  return st;
}

MIRSymbol *MIRBuilder::GetOrCreateLocalDecl(const std::string &str, MIRType *type) {
  bool isCreated = false;
  MIRSymbol *st = GetOrCreateDecl(str, type, nullptr, true, isCreated);
  ASSERT(st != nullptr, "st is null");
  if (isCreated) {
    st->SetStorageClass(kScAuto);
    st->SetSKind(kStVar);
  }
  return st;
}

MIRSymbol *MIRBuilder::CreateLocalDecl(const std::string &str, const MIRType *type) {
  GStrIdx stridx = GetOrCreateStringIndex(str);
  MIRFunction *currentFunctionInner = GetCurrentFunction();
  CHECK_FATAL(currentFunctionInner != nullptr, "null ptr check");
  MIRSymbolTable *symbolTable = currentFunctionInner->GetSymTab();
  MIRSymbol *st = symbolTable->CreateSymbol(kScopeLocal);
  st->SetNameStrIdx(stridx);
  st->SetTyIdx(type->GetTypeIndex());
  (void)symbolTable->AddToStringSymbolMap(st);
  st->SetStorageClass(kScAuto);
  st->SetSKind(kStVar);
  return st;
}

MIRSymbol *MIRBuilder::GetGlobalDecl(const std::string &str) {
  GStrIdx strIdx = GetStringIndex(str);
  if (strIdx != 0) {
    StIdx stidx = GlobalTables::GetGsymTable().GetStIdxFromStrIdx(strIdx);
    if (stidx.FullIdx() != 0) {
      return GlobalTables::GetGsymTable().GetSymbolFromStidx(stidx.Idx());
    }
  }
  return nullptr;
}

MIRSymbol *MIRBuilder::GetLocalDecl(const std::string &str) {
  MIRFunction *currentFunctionInner = GetCurrentFunction();
  CHECK_FATAL(currentFunctionInner != nullptr, "null ptr check");
  MIRSymbolTable *symbolTable = currentFunctionInner->GetSymTab();
  GStrIdx strIdx = GetStringIndex(str);
  if (strIdx != 0) {
    StIdx stidx = symbolTable->GetStIdxFromStrIdx(strIdx);
    if (stidx.FullIdx() != 0) {
      return symbolTable->GetSymbolFromStIdx(stidx.Idx());
    }
  }
  return nullptr;
}

// search the scope hierarchy
MIRSymbol *MIRBuilder::GetDecl(const std::string &str) {
  GStrIdx stridx = GetStringIndex(str);
  MIRSymbol *sym = nullptr;
  if (stridx != 0) {
    // try to find the decl in local scope first
    if (GetCurrentFunction()) {
      sym = GetCurrentFunction()->GetSymTab()->GetSymbolFromStrIdx(stridx);
    }
    if (sym == nullptr) {
      sym = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(stridx);
    }
  }
  return sym;
}

MIRSymbol *MIRBuilder::CreateGlobalDecl(const std::string &str, const MIRType *type, MIRStorageClass sc) {
  ASSERT(type != nullptr, "type is null");
  GStrIdx strIdx = GetOrCreateStringIndex(str);
  MIRSymbol *st = GlobalTables::GetGsymTable().CreateSymbol(kScopeGlobal);
  st->SetNameStrIdx(strIdx);
  st->SetTyIdx(type->GetTypeIndex());
  (void)GlobalTables::GetGsymTable().AddToStringSymbolMap(st);
  st->SetStorageClass(sc);
  st->SetSKind(kStVar);
  return st;
}

MIRSymbol *MIRBuilder::GetOrCreateGlobalDecl(const std::string &str, const MIRType *type) {
  bool isCreated = false;
  MIRSymbol *st = GetOrCreateDecl(str, type, nullptr, false, isCreated);
  if (isCreated) {
    st->SetStorageClass(kScGlobal);
    st->SetSKind(kStVar);
  } else {
    // Existing symbol may come from anther module. We need to register it
    // in the current module so that per-module mpl file is self-sustained.
    mirModule->AddSymbol(st);
  }
  MIRConst *cst = GlobalTables::GetConstPool().GetConstFromPool(st->GetNameStrIdx());
  if (cst != nullptr) {
    st->SetKonst(cst);
  }
  return st;
}

ConstvalNode *MIRBuilder::CreateIntConst(int64 val, PrimType pty) {
  ConstvalNode *constvalNode = GetCurrentFuncCodeMp()->New<ConstvalNode>();
  MIRFunction *currentFunctionInner = GetCurrentFunction();
  ASSERT(currentFunctionInner != nullptr, "null ptr check");
  MIRIntConst *intConst =
      currentFunctionInner->GetDataMemPool()->New<MIRIntConst>(val, GlobalTables::GetTypeTable().GetPrimType(pty));
  constvalNode->SetPrimType(pty);
  constvalNode->SetConstVal(intConst);
  return constvalNode;
}

ConstvalNode *MIRBuilder::CreateFloatConst(float val) {
  ConstvalNode *constvalNode = GetCurrentFuncCodeMp()->New<ConstvalNode>();
  MIRFunction *currentFunctionInner = GetCurrentFunction();
  ASSERT(currentFunctionInner != nullptr, "null ptr check");
  MIRFloatConst *floatConst = currentFunctionInner->GetDataMemPool()->New<MIRFloatConst>(
      val, GlobalTables::GetTypeTable().GetPrimType(PTY_f32));
  constvalNode->SetPrimType(PTY_f32);
  constvalNode->SetConstVal(floatConst);
  return constvalNode;
}

ConstvalNode *MIRBuilder::CreateDoubleConst(double val) {
  ConstvalNode *constvalNode = GetCurrentFuncCodeMp()->New<ConstvalNode>();
  MIRFunction *currentFunctionInner = GetCurrentFunction();
  ASSERT(currentFunctionInner != nullptr, "null ptr check");
  MIRDoubleConst *dblConst = currentFunctionInner->GetDataMemPool()->New<MIRDoubleConst>(
      val, GlobalTables::GetTypeTable().GetPrimType(PTY_f64));
  constvalNode->SetPrimType(PTY_f64);
  constvalNode->SetConstVal(dblConst);
  return constvalNode;
}

ConstvalNode *MIRBuilder::CreateFloat128Const(const uint64 *val) {
  ConstvalNode *constvalNode = GetCurrentFuncCodeMp()->New<ConstvalNode>();
  MIRFunction *currentFunctionInner = GetCurrentFunction();
  ASSERT(currentFunctionInner != nullptr, "null ptr check");
  MIRFloat128Const *f128Const = currentFunctionInner->GetDataMemPool()->New<MIRFloat128Const>(
      val, GlobalTables::GetTypeTable().GetPrimType(PTY_f128));
  constvalNode->SetPrimType(PTY_f128);
  constvalNode->SetConstVal(f128Const);
  return constvalNode;
}

ConstvalNode *MIRBuilder::GetConstInt(MemPool *memPool, int i) {
  ConstvalNode *constvalNode = memPool->New<ConstvalNode>();
  MIRIntConst *intConst = memPool->New<MIRIntConst>(i, GlobalTables::GetTypeTable().GetInt64());
  constvalNode->SetPrimType(PTY_i32);
  constvalNode->SetConstVal(intConst);
  return constvalNode;
}

ConstvalNode *MIRBuilder::CreateAddrofConst(BaseNode *e) {
  ConstvalNode *constvalNode = GetCurrentFuncCodeMp()->New<ConstvalNode>();
  ASSERT(e->GetOpCode() == OP_addrof, "illegal op for addrof const");
  AddrofNode *aNode = static_cast<AddrofNode*>(e);
  // determine the type of 'e' and create a pointer type, accordingly
  MIRFunction *currentFunctionInner = GetCurrentFunction();
  ASSERT(currentFunctionInner != nullptr, "null ptr check");
  MIRSymbol *var = currentFunctionInner->GetLocalOrGlobalSymbol(static_cast<AddrofNode*>(e)->GetStIdx());
  TyIdx ptyIdx = var->GetTyIdx();
  MIRPtrType ptrType(ptyIdx);
  ptyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&ptrType);
  MIRType *exprty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptyIdx);
  MIRAddrofConst *addr = mirModule->GetMemPool()->New<MIRAddrofConst>(aNode->GetStIdx(), aNode->GetFieldID(), exprty);
  constvalNode->SetPrimType(PTY_ptr);
  constvalNode->SetConstVal(addr);
  return constvalNode;
}

ConstvalNode *MIRBuilder::CreateAddroffuncConst(const BaseNode *e) {
  ConstvalNode *constvalNode = GetCurrentFuncCodeMp()->New<ConstvalNode>();
  ASSERT(e->GetOpCode() == OP_addroffunc, "illegal op for addroffunc const");
  MIRFunction *f =
      GlobalTables::GetFunctionTable().GetFunctionFromPuidx(static_cast<const AddroffuncNode*>(e)->GetPUIdx());
  MIRSymbol *fname = f->GetFuncSymbol();
  TyIdx ptyIdx = fname->GetTyIdx();
  MIRPtrType ptrType(ptyIdx);
  ptyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&ptrType);
  MIRType *exprty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptyIdx);
  MIRAddroffuncConst *fadr =
      mirModule->GetMemPool()->New<MIRAddroffuncConst>(static_cast<const AddroffuncNode*>(e)->GetPUIdx(), exprty);
  constvalNode->SetPrimType(PTY_ptr);
  constvalNode->SetConstVal(fadr);
  return constvalNode;
}

ConstvalNode *MIRBuilder::CreateStrConst(const BaseNode *e) {
  ConstvalNode *constvalNode = GetCurrentFuncCodeMp()->New<ConstvalNode>();
  ASSERT(e->GetOpCode() == OP_conststr, "illegal op for conststr const");
  UStrIdx strIdx = static_cast<const ConststrNode*>(e)->GetStrIdx();
  CHECK_FATAL(PTY_u8 < GlobalTables::GetTypeTable().GetTypeTable().size(),
              "index is out of range in MIRBuilder::CreateStrConst");
  TyIdx ptyidx = GlobalTables::GetTypeTable().GetTypeFromTyIdx(TyIdx(PTY_u8))->GetTypeIndex();
  MIRPtrType ptrType(ptyidx);
  ptyidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&ptrType);
  MIRType *exprType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptyidx);
  MIRStrConst *cStr = mirModule->GetMemPool()->New<MIRStrConst>(strIdx, exprType);
  constvalNode->SetPrimType(PTY_ptr);
  constvalNode->SetConstVal(cStr);
  return constvalNode;
}

ConstvalNode *MIRBuilder::CreateStr16Const(const BaseNode *e) {
  ConstvalNode *constvalNode = GetCurrentFuncCodeMp()->New<ConstvalNode>();
  ASSERT(e->GetOpCode() == OP_conststr16, "illegal op for conststr16 const");
  U16StrIdx strIdx = static_cast<const Conststr16Node*>(e)->GetStrIdx();
  CHECK_FATAL(PTY_u16 < GlobalTables::GetTypeTable().GetTypeTable().size(),
              "index out of range in MIRBuilder::CreateStr16Const");
  TyIdx ptyIdx = GlobalTables::GetTypeTable().GetTypeFromTyIdx(TyIdx(PTY_u16))->GetTypeIndex();
  MIRPtrType ptrType(ptyIdx);
  ptyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&ptrType);
  MIRType *exprty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptyIdx);
  MIRStr16Const *cstr = mirModule->GetMemPool()->New<MIRStr16Const>(strIdx, exprty);
  constvalNode->SetPrimType(PTY_ptr);
  constvalNode->SetConstVal(cstr);
  return constvalNode;
}

MIRSymbol *MIRBuilder::GetSymbolFromEnclosingScope(StIdx stIdx) {
  if (stIdx.FullIdx() == 0) {
    return nullptr;
  }
  if (stIdx.Islocal()) {
    MIRFunction *fun = GetCurrentFunction();
    ASSERT(fun != nullptr, "null ptr check");
    MIRSymbol *st = fun->GetSymTab()->GetSymbolFromStIdx(stIdx.Idx());
    if (st != nullptr) {
      return st;
    }
  }
  return GlobalTables::GetGsymTable().GetSymbolFromStidx(stIdx.Idx());
}

MIRSymbol *MIRBuilder::GetSymbol(TyIdx tyIdx, const std::string &name, MIRSymKind mClass, MIRStorageClass sClass,
                                 MIRFunction *func, uint8 scpID, bool sameType = false) {
  GStrIdx strIdx = GetOrCreateStringIndex(name);
  return GetSymbol(tyIdx, strIdx, mClass, sClass, func, scpID, sameType);
}

// when sametype is true, it means match everything the of the symbol
MIRSymbol *MIRBuilder::GetSymbol(TyIdx tyIdx, GStrIdx strIdx, MIRSymKind mClass, MIRStorageClass sClass,
                                 MIRFunction *func, uint8 scpID, bool sameType = false) {
  if (scpID != kScopeGlobal) {
    ERR(kLncErr, "not yet implemented");
    return nullptr;
  }

  MIRSymbol *st = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(strIdx);
  if (st == nullptr || st->GetTyIdx() != tyIdx) {
    return nullptr;
  }

  if (sameType) {
    if (st->GetStorageClass() == sClass && st->GetSKind() == mClass) {
      return st;
    }
    return nullptr;
  }
  ASSERT(mClass == st->GetSKind(),
         "trying to create a new symbol that has the same name and GtyIdx. might cause problem");
  ASSERT(sClass == st->GetStorageClass(),
         "trying to create a new symbol that has the same name and tyIdx. might cause problem");
  return st;
}

MIRSymbol *MIRBuilder::GetOrCreateSymbol(TyIdx tyIdx, const std::string &name, MIRSymKind mClass,
                                         MIRStorageClass sClass, MIRFunction *func, uint8 scpID,
                                         bool sametype = false) {
  GStrIdx stridx = GetOrCreateStringIndex(name);
  return GetOrCreateSymbol(tyIdx, stridx, mClass, sClass, func, scpID, sametype);
}

MIRSymbol *MIRBuilder::GetOrCreateSymbol(TyIdx tyIdx, GStrIdx strIdx, MIRSymKind mClass, MIRStorageClass sClass,
                                         MIRFunction *func, uint8 scpID, bool sameType = false) {
  if (MIRSymbol *st = GetSymbol(tyIdx, strIdx, mClass, sClass, func, scpID, sameType)) {
    return st;
  }
  return CreateSymbol(tyIdx, strIdx, mClass, sClass, func, scpID);
}

// when func is null, create global symbol, otherwise create local symbol
MIRSymbol *MIRBuilder::CreateSymbol(TyIdx tyIdx, const std::string &name, MIRSymKind mClass, MIRStorageClass sClass,
                                    MIRFunction *func, uint8 scpID) {
  GStrIdx stridx = GetOrCreateStringIndex(name);
  return CreateSymbol(tyIdx, stridx, mClass, sClass, func, scpID);
}

// when func is null, create global symbol, otherwise create local symbol
MIRSymbol *MIRBuilder::CreateSymbol(TyIdx tyIdx, GStrIdx strIdx, MIRSymKind mClass, MIRStorageClass sClass,
                                    MIRFunction *func, uint8 scpID) {
  MIRSymbol *st = nullptr;
  if (func) {
    st = func->GetSymTab()->CreateSymbol(scpID);
  } else {
    st = GlobalTables::GetGsymTable().CreateSymbol(scpID);
  }
  CHECK_FATAL(st != nullptr, "Failed to create MIRSymbol");
  st->SetStorageClass(sClass);
  st->SetSKind(mClass);
  st->SetNameStrIdx(strIdx);
  st->SetTyIdx(tyIdx);
  if (func) {
    (void)func->GetSymTab()->AddToStringSymbolMap(st);
  } else {
    (void)GlobalTables::GetGsymTable().AddToStringSymbolMap(st);
  }
  return st;
}

MIRSymbol *MIRBuilder::CreatePregFormalSymbol(TyIdx tyIdx, PregIdx pRegIdx, MIRFunction *func) {
  MIRSymbol *st = func->GetSymTab()->CreateSymbol(kScopeLocal);
  CHECK_FATAL(st != nullptr, "Failed to create MIRSymbol");
  st->SetStorageClass(kScFormal);
  st->SetSKind(kStPreg);
  st->SetTyIdx(tyIdx);
  MIRPregTable *pRegTab = func->GetPregTab();
  st->SetPreg(pRegTab->PregFromPregIdx(pRegIdx));
  return st;
}

MIRFunction *MIRBuilder::CreateFunction(const std::string &name, const MIRType *returnType, const ArgVector &arguments,
                                        bool isVarg, bool createBody) {
  MIRSymbol *funcSymbol = GlobalTables::GetGsymTable().CreateSymbol(kScopeGlobal);
  CHECK_FATAL(funcSymbol != nullptr, "Failed to create MIRSymbol");
  GStrIdx strIdx = GetOrCreateStringIndex(name.c_str());
  funcSymbol->SetNameStrIdx(strIdx);
  if (!GlobalTables::GetGsymTable().AddToStringSymbolMap(funcSymbol)) {
    return nullptr;
  }
  funcSymbol->SetStorageClass(kScText);
  funcSymbol->SetSKind(kStFunc);
  MIRFunction *fn = mirModule->GetMemPool()->New<MIRFunction>(mirModule, funcSymbol->GetStIdx());
  fn->Init();
  fn->SetPuidx(GlobalTables::GetFunctionTable().GetFuncTable().size());
  GlobalTables::GetFunctionTable().GetFuncTable().push_back(fn);
  std::vector<TyIdx> funcVecType;
  std::vector<TypeAttrs> funcVecAttrs;
  for (size_t i = 0; i < arguments.size(); i++) {
    MIRSymbol *argSymbol = fn->GetSymTab()->CreateSymbol(kScopeLocal);
    argSymbol->SetNameStrIdx(GetOrCreateStringIndex(arguments[i].first.c_str()));
    MIRType *ty = arguments[i].second;
    argSymbol->SetTyIdx(ty->GetTypeIndex());
    argSymbol->SetStorageClass(kScFormal);
    argSymbol->SetSKind(kStVar);
    (void)fn->GetSymTab()->AddToStringSymbolMap(argSymbol);
    fn->AddFormal(argSymbol);
    funcVecType.push_back(ty->GetTypeIndex());
    funcVecAttrs.push_back(TypeAttrs());
  }
  funcSymbol->SetTyIdx(
      GlobalTables::GetTypeTable()
          .GetOrCreateFunctionType(mirModule, returnType->GetTypeIndex(), funcVecType, funcVecAttrs, isVarg)
          ->GetTypeIndex());
  MIRFuncType *funcType = dynamic_cast<MIRFuncType*>(funcSymbol->GetType());
  fn->SetMIRFuncType(funcType);
  funcSymbol->SetFunction(fn);
  if (createBody) {
    fn->NewBody();
  }
  return fn;
}

MIRFunction *MIRBuilder::CreateFunction(const StIdx stIdx, bool addToTable) {
  MIRFunction *fn = mirModule->GetMemPool()->New<MIRFunction>(mirModule, stIdx);
  fn->Init();
  fn->SetPuidx(GlobalTables::GetFunctionTable().GetFuncTable().size());
  if (addToTable) {
    GlobalTables::GetFunctionTable().GetFuncTable().push_back(fn);
  }

  MIRFuncType *funcType = mirModule->GetMemPool()->New<MIRFuncType>();
  fn->SetMIRFuncType(funcType);
  return fn;
}

SizeoftypeNode *MIRBuilder::CreateExprSizeoftype(const MIRType *type) {
  SizeoftypeNode *sizeOfTypeNode = GetCurrentFuncCodeMp()->New<SizeoftypeNode>();
  sizeOfTypeNode->SetPrimType(PTY_u32);
  sizeOfTypeNode->SetTyIdx(type->GetTypeIndex());
  return sizeOfTypeNode;
}

FieldsDistNode *MIRBuilder::CreateExprFieldsDist(const MIRType *type, FieldID field1, FieldID field2) {
  FieldsDistNode *node = GetCurrentFuncCodeMp()->New<FieldsDistNode>();
  node->SetPrimType(PTY_i32);
  node->SetTyIdx(type->GetTypeIndex());
  node->SetFiledID1(field1);
  node->SetFiledID2(field2);
  return node;
}

AddrofNode *MIRBuilder::CreateExprAddrof(FieldID fieldID, const MIRSymbol *symbol, MemPool *memPool) {
  if (memPool == nullptr) {
    memPool = GetCurrentFuncCodeMp();
  }
  AddrofNode *addrofNode = memPool->New<AddrofNode>(OP_addrof);
  addrofNode->SetPrimType(PTY_ptr);
  addrofNode->SetStIdx(symbol->GetStIdx());
  addrofNode->SetFieldID(fieldID);
  return addrofNode;
}

AddrofNode *MIRBuilder::CreateExprAddrof(FieldID fieldID, StIdx symbolStIdx, MemPool *memPool) {
  if (memPool == nullptr) {
    memPool = GetCurrentFuncCodeMp();
  }
  AddrofNode *addrofNode = memPool->New<AddrofNode>(OP_addrof);
  addrofNode->SetPrimType(PTY_ptr);
  addrofNode->SetStIdx(symbolStIdx);
  addrofNode->SetFieldID(fieldID);
  return addrofNode;
}

AddroffuncNode *MIRBuilder::CreateExprAddroffunc(PUIdx puIdx, MemPool *memPool) {
  if (memPool == nullptr) {
    memPool = GetCurrentFuncCodeMp();
  }
  AddroffuncNode *addrofFunc = memPool->New<AddroffuncNode>();
  addrofFunc->SetPrimType(PTY_ptr);
  addrofFunc->SetPUIdx(puIdx);
  return addrofFunc;
}

AddrofNode *MIRBuilder::CreateExprDread(const MIRType *type, FieldID fieldID, const MIRSymbol *symbol) {
  AddrofNode *drn = GetCurrentFuncCodeMp()->New<AddrofNode>(OP_dread);
  drn->SetStIdx(symbol->GetStIdx());
  drn->SetFieldID(fieldID);
  CHECK(type->GetTypeIndex().GetIdx() < GlobalTables::GetTypeTable().GetTypeTable().size(),
        "index out of range in MIRBuilder::CreateExprDread");
  drn->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(type->GetTypeIndex()));
  return drn;
}

RegreadNode *MIRBuilder::CreateExprRegread(PrimType pty, PregIdx regIdx) {
  RegreadNode *regRead = GetCurrentFuncCodeMp()->New<RegreadNode>();
  regRead->SetPrimType(pty);
  regRead->SetRegIdx(regIdx);
  return regRead;
}

AddrofNode *MIRBuilder::CreateExprDread(MIRType *type, MIRSymbol *symbol) {
  return CreateExprDread(type, 0, symbol);
}

AddrofNode *MIRBuilder::CreateExprDread(MIRSymbol *symbol, uint16 fieldID) {
  if (fieldID == 0) {
    return CreateExprDread(symbol);
  }
  ASSERT(false, "NYI");
  return nullptr;
}

AddrofNode *MIRBuilder::CreateExprDread(MIRSymbol *symbol) {
  return CreateExprDread(symbol->GetType(), 0, symbol);
}

AddrofNode *MIRBuilder::CreateExprDread(PregIdx pregID, PrimType pty) {
  AddrofNode *dread = GetCurrentFuncCodeMp()->New<AddrofNode>(OP_dread);
  dread->SetPrimType(pty);
  dread->GetStIdx().SetFullIdx(pregID);
  return dread;
}

IreadNode *MIRBuilder::CreateExprIread(const MIRType *returnType, const MIRType *ptrType, FieldID fieldID,
                                       BaseNode *addr) {
  IreadNode *irn = GetCurrentFuncCodeMp()->New<IreadNode>(OP_iread);
  TyIdx ptrTypeIdx = ptrType->GetTypeIndex();
  TyIdx returnTypeIdx = returnType->GetTypeIndex();
  ASSERT(returnTypeIdx.GetIdx() < GlobalTables::GetTypeTable().GetTypeTable().size(),
        "index out of range in MIRBuilder::CreateExprIread");
  irn->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(returnTypeIdx));
  irn->SetTyIdx(ptrTypeIdx);

  ASSERT(fieldID != 0 || ptrType->GetPrimType() != PTY_agg,
         "Error: Fieldid should not be 0 when trying to iread a field from type ");
  irn->SetFieldID(fieldID);
  irn->SetOpnd(addr);
  return irn;
}

IreadoffNode *MIRBuilder::CreateExprIreadoff(PrimType pty, int32 offset, BaseNode *opnd0) {
  IreadoffNode *ireadOff = GetCurrentFuncCodeMp()->New<IreadoffNode>();
  ireadOff->SetPrimType(pty);
  ireadOff->SetOffset(offset);
  ireadOff->SetOpnd(opnd0);
  return ireadOff;
}

IreadFPoffNode *MIRBuilder::CreateExprIreadFPoff(PrimType pty, int32 offset) {
  IreadFPoffNode *ireadOff = GetCurrentFuncCodeMp()->New<IreadFPoffNode>();
  ireadOff->SetPrimType(pty);
  ireadOff->SetOffset(offset);
  return ireadOff;
}

IaddrofNode *MIRBuilder::CreateExprIaddrof(const MIRType *returnType, const MIRType *ptrType, FieldID fieldID,
                                           BaseNode *addr) {
  IaddrofNode *iAddrOfNode = CreateExprIread(returnType, ptrType, fieldID, addr);
  iAddrOfNode->SetOpCode(OP_iaddrof);
  return iAddrOfNode;
}

IaddrofNode *MIRBuilder::CreateExprIaddrof(PrimType returnTypePty, TyIdx ptrTypeIdx, FieldID fieldID, BaseNode *addr) {
  IaddrofNode *iaddrofNode = GetCurrentFuncCodeMp()->New<IreadNode>(OP_iaddrof);
  iaddrofNode->SetPrimType(returnTypePty);
  iaddrofNode->SetTyIdx(ptrTypeIdx);
  iaddrofNode->SetFieldID(fieldID);
  iaddrofNode->SetOpnd(addr);
  return iaddrofNode;
}

UnaryNode *MIRBuilder::CreateExprUnary(Opcode opcode, const MIRType *type, BaseNode *opnd) {
  UnaryNode *un = GetCurrentFuncCodeMp()->New<UnaryNode>(opcode);
  un->SetPrimType(type->GetPrimType());
  un->SetOpnd(opnd);
  return un;
}

GCMallocNode *MIRBuilder::CreateExprGCMalloc(Opcode opcode, const MIRType *ptype, const MIRType *type) {
  GCMallocNode *un = GetCurrentFuncCodeMp()->New<GCMallocNode>(opcode);
  un->SetPrimType(ptype->GetPrimType());
  un->SetTyIdx(type->GetTypeIndex());
  return un;
}

JarrayMallocNode *MIRBuilder::CreateExprJarrayMalloc(Opcode opcode, const MIRType *ptype, const MIRType *type,
                                                     BaseNode *opnd) {
  JarrayMallocNode *un = GetCurrentFuncCodeMp()->New<JarrayMallocNode>(opcode);
  un->SetPrimType(ptype->GetPrimType());
  un->SetTyIdx(type->GetTypeIndex());
  un->SetOpnd(opnd);
  return un;
}

TypeCvtNode *MIRBuilder::CreateExprTypeCvt(Opcode o, const MIRType *type, const MIRType *fromType, BaseNode *opnd) {
  TypeCvtNode *un = GetCurrentFuncCodeMp()->New<TypeCvtNode>(o);
  un->SetPrimType(type->GetPrimType());
  un->SetFromType(fromType->GetPrimType());
  un->SetOpnd(static_cast<BaseNode*>(opnd));
  return un;
}

ExtractbitsNode *MIRBuilder::CreateExprExtractbits(Opcode o, const MIRType *type, uint32 bOffset, uint32 bsize,
                                                   BaseNode *opnd) {
  ExtractbitsNode *ext = GetCurrentFuncCodeMp()->New<ExtractbitsNode>(o);
  ext->SetPrimType(type->GetPrimType());
  ext->SetBitsOffset(bOffset);
  ext->SetBitsSize(bsize);
  ext->SetOpnd(static_cast<BaseNode*>(opnd));
  return ext;
}

RetypeNode *MIRBuilder::CreateExprRetype(const MIRType *type, const MIRType *fromType, BaseNode *opnd) {
  RetypeNode *un = GetCurrentFuncCodeMp()->New<RetypeNode>();
  un->SetPrimType(type->GetPrimType());
  un->SetFromType(fromType->GetPrimType());
  un->SetTyIdx(type->GetTypeIndex());
  un->SetOpnd(static_cast<BaseNode*>(opnd));
  return un;
}

BinaryNode *MIRBuilder::CreateExprBinary(Opcode opcode, const MIRType *type, BaseNode *opnd0, BaseNode *opnd1) {
  BinaryNode *bn = GetCurrentFuncCodeMp()->New<BinaryNode>(opcode);
  bn->SetPrimType(type->GetPrimType());
  bn->SetBOpnd(opnd0, 0);
  bn->SetBOpnd(opnd1, 1);
  return bn;
}

TernaryNode *MIRBuilder::CreateExprTernary(Opcode opcode, const MIRType *type, BaseNode *opnd0, BaseNode *opnd1,
                                           BaseNode *opnd2) {
  TernaryNode *tn = GetCurrentFuncCodeMp()->New<TernaryNode>(opcode);
  tn->SetPrimType(type->GetPrimType());
  tn->SetOpnd(opnd0, 0);
  tn->SetOpnd(opnd1, 1);
  tn->SetOpnd(opnd2, 2);
  return tn;
}

CompareNode *MIRBuilder::CreateExprCompare(Opcode opcode, const MIRType *type, const MIRType *opndType, BaseNode *opnd0,
                                           BaseNode *opnd1) {
  CompareNode *bn = GetCurrentFuncCodeMp()->New<CompareNode>(opcode);
  bn->SetPrimType(type->GetPrimType());
  bn->SetOpndType(opndType->GetPrimType());
  bn->SetBOpnd(opnd0, 0);
  bn->SetBOpnd(opnd1, 1);
  return bn;
}

ArrayNode *MIRBuilder::CreateExprArray(const MIRType *arrayType) {
  ArrayNode *arrayNode = GetCurrentFuncCodeMp()->New<ArrayNode>(GetCurrentFuncCodeMpAllocator());
  MIRType *addrType = GlobalTables::GetTypeTable().GetOrCreatePointerType(arrayType);
  ASSERT(addrType != nullptr, "addrType is null");
  arrayNode->SetPrimType(addrType->GetPrimType());
  arrayNode->SetTyIdx(addrType->GetTypeIndex());
  arrayNode->SetNumOpnds(0);
  return arrayNode;
}

ArrayNode *MIRBuilder::CreateExprArray(const MIRType *arrayType, BaseNode *op) {
  ArrayNode *arrayNode = CreateExprArray(arrayType);
  arrayNode->GetNopnd().push_back(op);
  arrayNode->SetNumOpnds(1);
  return arrayNode;
}

ArrayNode *MIRBuilder::CreateExprArray(const MIRType *arrayType, BaseNode *op1, BaseNode *op2) {
  ArrayNode *arrayNode = CreateExprArray(arrayType);
  arrayNode->GetNopnd().push_back(op1);
  arrayNode->GetNopnd().push_back(op2);
  arrayNode->SetNumOpnds(2);
  return arrayNode;
}

IntrinsicopNode *MIRBuilder::CreateExprIntrinsicop(MIRIntrinsicID idx, Opcode opCode, const MIRType *type,
                                                   const MapleVector<BaseNode*> &ops) {
  IntrinsicopNode *expr =
      GetCurrentFuncCodeMp()->New<IntrinsicopNode>(GetCurrentFuncCodeMpAllocator(), opCode, type->GetPrimType());
  expr->SetIntrinsic(idx);
  expr->SetNOpnd(ops);
  expr->SetNumOpnds(ops.size());
  if (opCode == OP_intrinsicopwithtype) {
    expr->SetTyIdx(type->GetTypeIndex());
  }
  return expr;
}

DassignNode *MIRBuilder::CreateStmtDassign(const MIRSymbol *symbol, FieldID fieldID, BaseNode *src) {
  DassignNode *stmt = GetCurrentFuncCodeMp()->New<DassignNode>();
  stmt->SetStIdx(symbol->GetStIdx());
  stmt->SetFieldID(fieldID);
  stmt->SetRHS(src);
  return stmt;
}

RegassignNode *MIRBuilder::CreateStmtRegassign(PrimType pty, PregIdx regIdx, BaseNode *src) {
  RegassignNode *stmt = GetCurrentFuncCodeMp()->New<RegassignNode>();
  stmt->SetPrimType(pty);
  stmt->SetRegIdx(regIdx);
  stmt->SetOpnd(src);
  return stmt;
}

DassignNode *MIRBuilder::CreateStmtDassign(StIdx sIdx, FieldID fieldID, BaseNode *src) {
  DassignNode *stmt = GetCurrentFuncCodeMp()->New<DassignNode>();
  stmt->SetStIdx(sIdx);
  stmt->SetFieldID(fieldID);
  stmt->SetRHS(src);
  return stmt;
}

IassignNode *MIRBuilder::CreateStmtIassign(const MIRType *type, FieldID fieldID, BaseNode *addr, BaseNode *src) {
  IassignNode *stmt = GetCurrentFuncCodeMp()->New<IassignNode>();
  stmt->SetTyIdx(type->GetTypeIndex());
  stmt->SetFieldID(fieldID);
  stmt->SetOpnd(addr, 0);
  stmt->SetRHS(src);
  return stmt;
}

IassignoffNode *MIRBuilder::CreateStmtIassignoff(PrimType pty, int32 offset, BaseNode *addr, BaseNode *src) {
  IassignoffNode *stmt = GetCurrentFuncCodeMp()->New<IassignoffNode>();
  stmt->SetPrimType(pty);
  stmt->offset = offset;
  stmt->SetBOpnd(addr, 0);
  stmt->SetBOpnd(src, 1);
  return stmt;
}

IassignFPoffNode *MIRBuilder::CreateStmtIassignFPoff(PrimType pty, int32 offset, BaseNode *src) {
  IassignFPoffNode *stmt = GetCurrentFuncCodeMp()->New<IassignFPoffNode>();
  stmt->SetPrimType(pty);
  stmt->SetOffset(offset);
  stmt->SetOpnd(src);
  return stmt;
}

CallNode *MIRBuilder::CreateStmtCall(PUIdx puIdx, const MapleVector<BaseNode*> &args, Opcode opCode) {
  CallNode *stmt = GetCurrentFuncCodeMp()->New<CallNode>(GetCurrentFuncCodeMpAllocator(), opCode);
  stmt->SetPUIdx(puIdx);
  stmt->SetNOpnd(args);
  stmt->SetNumOpnds(args.size());
  return stmt;
}

CallNode *MIRBuilder::CreateStmtCall(const std::string &callee, const MapleVector<BaseNode*> &args) {
  GStrIdx strIdx = GlobalTables::GetStrTable().GetStrIdxFromName(callee);
  StIdx stIdx = GlobalTables::GetGsymTable().GetStIdxFromStrIdx(strIdx);
  MIRSymbol *st = GlobalTables::GetGsymTable().GetSymbolFromStidx(stIdx.Idx());
  ASSERT(st != nullptr, "MIRSymbol st is null");
  MIRFunction *func = st->GetFunction();
  return CreateStmtCall(func->GetPuidx(), args, OP_call);
}

IcallNode *MIRBuilder::CreateStmtIcall(const MapleVector<BaseNode*> &args) {
  IcallNode *stmt = GetCurrentFuncCodeMp()->New<IcallNode>(GetCurrentFuncCodeMpAllocator(), OP_icall);
  stmt->SetNOpnd(args);
  stmt->SetNumOpnds(args.size());
  return stmt;
}

IntrinsiccallNode *MIRBuilder::CreateStmtIntrinsicCall(MIRIntrinsicID idx, const MapleVector<BaseNode*> &arguments,
                                                       TyIdx tyIdx) {
  IntrinsiccallNode *stmt = GetCurrentFuncCodeMp()->New<IntrinsiccallNode>(
      GetCurrentFuncCodeMpAllocator(), tyIdx == 0 ? OP_intrinsiccall : OP_intrinsiccallwithtype);
  stmt->SetIntrinsic(idx);
  stmt->SetTyIdx(tyIdx);
  stmt->SetNOpnd(arguments);
  stmt->SetNumOpnds(arguments.size());
  return stmt;
}

IntrinsiccallNode *MIRBuilder::CreateStmtXintrinsicCall(MIRIntrinsicID idx, const MapleVector<BaseNode*> &arguments) {
  IntrinsiccallNode *stmt =
      GetCurrentFuncCodeMp()->New<IntrinsiccallNode>(GetCurrentFuncCodeMpAllocator(), OP_xintrinsiccall);
  stmt->SetIntrinsic(idx);
  stmt->SetNOpnd(arguments);
  stmt->SetNumOpnds(arguments.size());
  return stmt;
}

CallNode *MIRBuilder::CreateStmtCallAssigned(PUIdx puIdx, const MIRSymbol *ret, Opcode op) {
  CallNode *stmt = GetCurrentFuncCodeMp()->New<CallNode>(GetCurrentFuncCodeMpAllocator(), op);
  stmt->SetPUIdx(puIdx);
  if (ret) {
    ASSERT((ret->GetStorageClass() == kScAuto || ret->GetStorageClass() == kScFormal ||
            ret->GetStorageClass() == kScExtern || ret->GetStorageClass() == kScGlobal),
           "Not Expected ret");
    stmt->GetReturnVec().push_back(CallReturnPair(ret->GetStIdx(), RegFieldPair(0, 0)));
  }
  return stmt;
}

CallNode *MIRBuilder::CreateStmtCallAssigned(PUIdx puIdx, const MapleVector<BaseNode*> &args, const MIRSymbol *ret,
                                             Opcode opcode, TyIdx tyIdx) {
  CallNode *stmt = GetCurrentFuncCodeMp()->New<CallNode>(GetCurrentFuncCodeMpAllocator(), opcode);
  stmt->SetPUIdx(puIdx);
  stmt->SetTyIdx(tyIdx);
  stmt->SetNOpnd(args);
  stmt->SetNumOpnds(args.size());
  if (ret != nullptr) {
    ASSERT((ret->GetStorageClass() == kScAuto || ret->GetStorageClass() == kScFormal ||
            ret->GetStorageClass() == kScExtern || ret->GetStorageClass() == kScGlobal),
           "Not Expected ret");
    stmt->GetReturnVec().push_back(CallReturnPair(ret->GetStIdx(), RegFieldPair(0, 0)));
  }
  return stmt;
}

CallNode *MIRBuilder::CreateStmtCallRegassigned(PUIdx puIdx, PregIdx pRegIdxt, Opcode opcode, BaseNode *arg) {
  CallNode *stmt = GetCurrentFuncCodeMp()->New<CallNode>(GetCurrentFuncCodeMpAllocator(), opcode);
  stmt->SetPUIdx(puIdx);
  stmt->GetNopnd().push_back(arg);
  stmt->SetNumOpnds(stmt->GetNopndSize());
  if (pRegIdxt > 0) {
    stmt->GetReturnVec().push_back(CallReturnPair(StIdx(), RegFieldPair(0, pRegIdxt)));
  }
  return stmt;
}

CallNode *MIRBuilder::CreateStmtCallRegassigned(PUIdx puIdx, const MapleVector<BaseNode*> &args, PregIdx pRegIdxt,
                                                Opcode opcode) {
  CallNode *stmt = GetCurrentFuncCodeMp()->New<CallNode>(GetCurrentFuncCodeMpAllocator(), opcode);
  stmt->SetPUIdx(puIdx);
  stmt->SetNOpnd(args);
  stmt->SetNumOpnds(args.size());
  if (pRegIdxt > 0) {
    stmt->GetReturnVec().push_back(CallReturnPair(StIdx(), RegFieldPair(0, pRegIdxt)));
  }
  return stmt;
}

IntrinsiccallNode *MIRBuilder::CreateStmtIntrinsicCallAssigned(MIRIntrinsicID idx, const MapleVector<BaseNode*> &args,
                                                               PregIdx retPregIdx) {
  IntrinsiccallNode *stmt =
      GetCurrentFuncCodeMp()->New<IntrinsiccallNode>(GetCurrentFuncCodeMpAllocator(), OP_intrinsiccallassigned);
  stmt->SetIntrinsic(idx);
  stmt->SetNOpnd(args);
  stmt->SetNumOpnds(args.size());
  if (retPregIdx > 0) {
    stmt->GetReturnVec().push_back(CallReturnPair(StIdx(), RegFieldPair(0, retPregIdx)));
  }
  return stmt;
}

IntrinsiccallNode *MIRBuilder::CreateStmtIntrinsicCallAssigned(MIRIntrinsicID idx, const MapleVector<BaseNode*> &args,
                                                               const MIRSymbol *ret, TyIdx tyIdx) {
  IntrinsiccallNode *stmt = GetCurrentFuncCodeMp()->New<IntrinsiccallNode>(
      GetCurrentFuncCodeMpAllocator(), tyIdx == 0 ? OP_intrinsiccallassigned : OP_intrinsiccallwithtypeassigned);
  stmt->SetIntrinsic(idx);
  stmt->SetTyIdx(tyIdx);
  stmt->SetNOpnd(args);
  stmt->SetNumOpnds(args.size());
  CallReturnVector nrets(GetCurrentFuncCodeMpAllocator()->Adapter());
  if (ret != nullptr) {
    ASSERT((ret->GetStorageClass() == kScAuto || ret->GetStorageClass() == kScFormal ||
            ret->GetStorageClass() == kScExtern || ret->GetStorageClass() == kScGlobal),
           "Not Excepted ret");
    nrets.push_back(CallReturnPair(ret->GetStIdx(), RegFieldPair(0, 0)));
  }
  stmt->SetReturnVec(nrets);
  return stmt;
}

IntrinsiccallNode *MIRBuilder::CreateStmtXintrinsicCallAssigned(MIRIntrinsicID idx, const MapleVector<BaseNode*> &args,
                                                                const MIRSymbol *ret) {
  IntrinsiccallNode *stmt =
      GetCurrentFuncCodeMp()->New<IntrinsiccallNode>(GetCurrentFuncCodeMpAllocator(), OP_xintrinsiccallassigned);
  stmt->SetIntrinsic(idx);
  stmt->SetNOpnd(args);
  stmt->SetNumOpnds(args.size());
  CallReturnVector nrets(GetCurrentFuncCodeMpAllocator()->Adapter());
  if (ret != nullptr) {
    ASSERT((ret->GetStorageClass() == kScAuto || ret->GetStorageClass() == kScFormal ||
            ret->GetStorageClass() == kScExtern || ret->GetStorageClass() == kScGlobal),
           "Not Excepted ret");
    nrets.push_back(CallReturnPair(ret->GetStIdx(), RegFieldPair(0, 0)));
  }
  stmt->SetReturnVec(nrets);
  return stmt;
}

NaryStmtNode *MIRBuilder::CreateStmtReturn(BaseNode *rVal) {
  NaryStmtNode *stmt = GetCurrentFuncCodeMp()->New<NaryStmtNode>(GetCurrentFuncCodeMpAllocator(), OP_return);
  if (rVal) {
    stmt->GetNopnd().push_back(rVal);
  }
  stmt->SetNumOpnds(stmt->GetNopndSize());
  return stmt;
}

NaryStmtNode *MIRBuilder::CreateStmtNary(Opcode op, const MapleVector<BaseNode*> &rVals) {
  NaryStmtNode *stmt = GetCurrentFuncCodeMp()->New<NaryStmtNode>(GetCurrentFuncCodeMpAllocator(), op);
  stmt->SetNOpnd(rVals);
  stmt->SetNumOpnds(stmt->GetNopndSize());
  return stmt;
}

NaryStmtNode *MIRBuilder::CreateStmtNary(Opcode op, BaseNode *rVal) {
  NaryStmtNode *stmt = GetCurrentFuncCodeMp()->New<NaryStmtNode>(GetCurrentFuncCodeMpAllocator(), op);
  if (rVal) {
    stmt->GetNopnd().push_back(rVal);
  }
  stmt->SetNumOpnds(stmt->GetNopndSize());
  return stmt;
}

UnaryStmtNode *MIRBuilder::CreateStmtUnary(Opcode op, BaseNode *rVal) {
  UnaryStmtNode *stmt = GetCurrentFuncCodeMp()->New<UnaryStmtNode>(op);
  stmt->SetOpnd(rVal);
  return stmt;
}

UnaryStmtNode *MIRBuilder::CreateStmtThrow(BaseNode *rVal) {
  return CreateStmtUnary(OP_throw, rVal);
}

IfStmtNode *MIRBuilder::CreateStmtIf(BaseNode *cond) {
  IfStmtNode *ifStmt = GetCurrentFuncCodeMp()->New<IfStmtNode>();
  ifStmt->SetOpnd(cond);
  BlockNode *thenBlock = GetCurrentFuncCodeMp()->New<BlockNode>();
  ifStmt->SetThenPart(thenBlock);
  return ifStmt;
}

IfStmtNode *MIRBuilder::CreateStmtIfThenElse(BaseNode *cond) {
  IfStmtNode *ifStmt = GetCurrentFuncCodeMp()->New<IfStmtNode>();
  ifStmt->SetOpnd(cond);
  BlockNode *thenBlock = GetCurrentFuncCodeMp()->New<BlockNode>();
  ifStmt->SetThenPart(thenBlock);
  BlockNode *elseBlock = GetCurrentFuncCodeMp()->New<BlockNode>();
  ifStmt->SetElsePart(elseBlock);
  ifStmt->SetNumOpnds(3);
  return ifStmt;
}

DoloopNode *MIRBuilder::CreateStmtDoloop(StIdx doVarStIdx, bool isPReg, BaseNode *startExp, BaseNode *contExp,
                                         BaseNode *incrExp) {
  DoloopNode *doLoopNode = GetCurrentFuncCodeMp()->New<DoloopNode>();
  doLoopNode->SetDoVarStIdx(doVarStIdx);
  doLoopNode->SetIsPreg(isPReg);
  doLoopNode->SetStartExpr(startExp);
  doLoopNode->SetContExpr(contExp);
  doLoopNode->SetIncrExpr(incrExp);
  doLoopNode->SetDoBody(GetCurrentFuncCodeMp()->New<BlockNode>());
  doLoopNode->SetNumOpnds(4);
  return doLoopNode;
}

SwitchNode *MIRBuilder::CreateStmtSwitch(BaseNode *opnd, LabelIdx defaultLabel, const CaseVector &switchTable) {
  SwitchNode *switchNode = GetCurrentFuncCodeMp()->New<SwitchNode>(GetCurrentFuncCodeMpAllocator());
  switchNode->SetSwitchOpnd(opnd);
  switchNode->SetDefaultLabel(defaultLabel);
  switchNode->SetSwitchTable(switchTable);
  switchNode->SetNumOpnds(switchTable.size());
  return switchNode;
}

GotoNode *MIRBuilder::CreateStmtGoto(Opcode o, LabelIdx labIdx) {
  GotoNode *gotoNode = GetCurrentFuncCodeMp()->New<GotoNode>(o);
  gotoNode->SetOffset(labIdx);
  return gotoNode;
}

JsTryNode *MIRBuilder::CreateStmtJsTry(Opcode o, LabelIdx cLabIdx, LabelIdx fLabIdx) {
  JsTryNode *tryNode = GetCurrentFuncCodeMp()->New<JsTryNode>();
  tryNode->SetCatchOffset(static_cast<uint16>(cLabIdx));
  tryNode->SetFinallyOffset(static_cast<uint16>(fLabIdx));
  return tryNode;
}

TryNode *MIRBuilder::CreateStmtTry(const MapleVector<LabelIdx> &cLabIdxs) {
  TryNode *tryNode = GetCurrentFuncCodeMp()->New<TryNode>(GetCurrentFuncCodeMpAllocator());
  tryNode->SetOffsets(cLabIdxs);
  return tryNode;
}

CatchNode *MIRBuilder::CreateStmtCatch(const MapleVector<TyIdx> &tyIdxVec) {
  CatchNode *catchNode = GetCurrentFuncCodeMp()->New<CatchNode>(GetCurrentFuncCodeMpAllocator());
  catchNode->SetExceptionTyIdxVec(tyIdxVec);
  return catchNode;
}

LabelIdx MIRBuilder::GetOrCreateMIRLabel(const std::string &name) {
  GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(name);
  MIRFunction *currentFunctionInner = GetCurrentFunction();
  ASSERT(currentFunctionInner != nullptr, "null ptr check");
  LabelIdx labidx = currentFunctionInner->GetLabelTab()->GetStIdxFromStrIdx(stridx);
  if (labidx == 0) {
    labidx = currentFunctionInner->GetLabelTab()->CreateLabel();
    currentFunctionInner->GetLabelTab()->SetSymbolFromStIdx(labidx, stridx);
    currentFunctionInner->GetLabelTab()->AddToStringLabelMap(labidx);
  }
  return labidx;
}

LabelIdx MIRBuilder::CreateLabIdx(MIRFunction *mirFunc) {
  LabelIdx lidx = mirFunc->GetLabelTab()->CreateLabel();
  mirFunc->GetLabelTab()->AddToStringLabelMap(lidx);
  return lidx;
}

LabelNode *MIRBuilder::CreateStmtLabel(LabelIdx labIdx) {
  LabelNode *label = GetCurrentFuncCodeMp()->New<LabelNode>();
  label->SetLabelIdx(labIdx);
  return label;
}

StmtNode *MIRBuilder::CreateStmtComment(const std::string &cmnt) {
  CommentNode *cmntNode = GetCurrentFuncCodeMp()->New<CommentNode>(GetCurrentFuncCodeMpAllocator(), cmnt);
  return cmntNode;
}

void MIRBuilder::AddStmtInCurrentFunctionBody(StmtNode *stmt) {
  MIRFunction *fun = GetCurrentFunction();
  ASSERT(fun != nullptr, "null ptr check");
  stmt->GetSrcPos().CondSetLineNum(lineNum);
  fun->GetBody()->AddStatement(stmt);
}

AddrofNode *MIRBuilder::CreateAddrof(const MIRSymbol *st, PrimType pty) {
  AddrofNode *addrofNode = GetCurrentFuncCodeMp()->New<AddrofNode>(OP_addrof);
  addrofNode->SetPrimType(pty);
  addrofNode->SetStIdx(st->GetStIdx());
  return addrofNode;
}

AddrofNode *MIRBuilder::CreateDread(const MIRSymbol *st, PrimType pty) {
  AddrofNode *dread = GetCurrentFuncCodeMp()->New<AddrofNode>(OP_dread);
  dread->SetPrimType(pty);
  dread->SetStIdx(st->GetStIdx());
  dread->SetFieldID(0);
  return dread;
}

CondGotoNode *MIRBuilder::CreateStmtCondGoto(BaseNode *cond, Opcode op, LabelIdx labIdx) {
  CondGotoNode *condGoto = GetCurrentFuncCodeMp()->New<CondGotoNode>(op == OP_brtrue ? OP_brtrue : OP_brfalse);
  condGoto->SetOffset(labIdx);
  condGoto->SetOpnd(cond);
  return condGoto;
}

MemPool *MIRBuilder::GetCurrentFuncCodeMp() {
  return mirModule->CurFuncCodeMemPool();
}

MapleAllocator *MIRBuilder::GetCurrentFuncCodeMpAllocator() {
  return mirModule->CurFuncCodeMemPoolAllocator();
}

}  // namespace maple
