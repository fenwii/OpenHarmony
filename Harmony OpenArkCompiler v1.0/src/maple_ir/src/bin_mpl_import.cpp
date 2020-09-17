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
#include "bin_mpl_import.h"
#include <sstream>
#include <vector>
#include <unordered_set>
#include <limits>
#include "bin_mpl_export.h"
#include "mir_function.h"
#include "name_mangler.h"
#include "opcode_info.h"
#include "mir_pragma.h"
#include "mir_builder.h"

namespace maple {

uint8 BinaryMplImport::Read() {
  CHECK_FATAL(bufI < buf.size(), "Index out of bound in BinaryMplImport::Read()");
  return buf[bufI++];
}

/* Little endian */
int32 BinaryMplImport::ReadInt() {
  uint32 x0 = static_cast<uint32>(Read());
  uint32 x1 = static_cast<uint32>(Read());
  uint32 x2 = static_cast<uint32>(Read());
  uint32 x3 = static_cast<uint32>(Read());
  return (((((x3 << 8u) + x2) << 8u) + x1) << 8u) + x0;
}

int64 BinaryMplImport::ReadInt64() {
  // casts to avoid sign extension
  uint32 x0 = static_cast<uint32>(ReadInt());
  uint64 x1 = static_cast<uint32>(ReadInt());
  return static_cast<int64>((x1 << 32) + x0);
}

/* LEB128 */
int64 BinaryMplImport::ReadNum() {
  uint64 n = 0;
  int64 y = 0;
  uint64 b = static_cast<uint64>(Read());
  while (b >= 0x80) {
    y += ((b - 0x80) << n);
    n += 7;
    b = static_cast<uint64>(Read());
  }
  b = (b & 0x3F) - (b & 0x40);
  return y + (b << n);
}

void BinaryMplImport::ReadAsciiStr(std::string &str) {
  uint8 ch = Read();
  std::ostringstream strStream(str);
  while (ch != '\0') {
    strStream << ch;
    ch = Read();
  }
  str = strStream.str();
}

void BinaryMplImport::ReadFileAt(const std::string &name, int32 offset) {
  FILE *f = fopen(name.c_str(), "rb");
  CHECK_FATAL(f != nullptr, "Error while reading the binary file: %s", name.c_str());

  int seekRet = fseek(f, 0, SEEK_END);
  CHECK_FATAL(seekRet == 0, "call fseek failed");

  long size = ftell(f);
  size -= offset;

  CHECK_FATAL(size >= 0, "should not be negative");

  seekRet = fseek(f, offset, SEEK_SET);
  CHECK_FATAL(seekRet == 0, "call fseek failed");
  buf.resize(size);

  long result = fread(&buf[0], sizeof(uint8), size, f);
  fclose(f);
  CHECK_FATAL(result == size, "Error while reading the binary file: %s", name.c_str());
}

void BinaryMplImport::ImportConstBase(MIRConstKind &kind, MIRTypePtr &type, uint32 &fieldID) {
  kind = static_cast<MIRConstKind>(ReadNum());
  TyIdx tyidx = ImportType();
  type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyidx);
  fieldID = ReadNum();
}

MIRConst *BinaryMplImport::ImportConst(MIRFunction *func) {
  int64 tag = ReadNum();
  if (tag == 0) {
    return nullptr;
  }

  MIRConstKind kind;
  MIRType *type = nullptr;
  uint32 fieldID;
  MemPool *memPool = (func == nullptr) ? mod.GetMemPool() : func->GetCodeMempool();

  if (tag == kBinKindConstInt) {
    ImportConstBase(kind, type, fieldID);
    return mod.GetMemPool()->New<MIRIntConst>(ReadNum(), type, fieldID);
  } else if (tag == kBinKindConstAddrof) {
    ImportConstBase(kind, type, fieldID);
    MIRSymbol *sym = InSymbol(func);
    ASSERT(sym, "null ptr check");
    FieldID fi = ReadNum();
    return memPool->New<MIRAddrofConst>(sym->GetStIdx(), fi, type);
  } else if (tag == kBinKindConstAddrofFunc) {
    ImportConstBase(kind, type, fieldID);
    PUIdx puidx = ImportFunction();
    return memPool->New<MIRAddroffuncConst>(puidx, type, fieldID);
  } else if (tag == kBinKindConstStr) {
    ImportConstBase(kind, type, fieldID);
    UStrIdx ustr = ImportUsrStr();
    return memPool->New<MIRStrConst>(ustr, type, fieldID);
  } else if (tag == kBinKindConstStr16) {
    ImportConstBase(kind, type, fieldID);
    Conststr16Node *cs;
    cs = memPool->New<Conststr16Node>();
    cs->SetPrimType(type->GetPrimType());
    int64 len = ReadNum();
    std::ostringstream ostr;
    for (int64 i = 0; i < len; i++) {
      ostr << Read();
    }
    std::u16string str16;
    NameMangler::UTF8ToUTF16(str16, ostr.str());
    cs->SetStrIdx(GlobalTables::GetU16StrTable().GetOrCreateStrIdxFromName(str16));
    return memPool->New<MIRStr16Const>(cs->GetStrIdx(), type);
  } else if (tag == kBinKindConstFloat) {
    union {
      float fvalue;
      int32 ivalue;
    } value;

    value.ivalue = ReadNum();
    return GlobalTables::GetFpConstTable().GetOrCreateFloatConst(value.fvalue);
  } else if (tag == kBinKindConstDouble) {
    union {
      double dvalue;
      int64 ivalue;
    } value;

    value.ivalue = ReadNum();
    return GlobalTables::GetFpConstTable().GetOrCreateDoubleConst(value.dvalue);
  } else if (tag == kBinKindConstAgg) {
    ImportConstBase(kind, type, fieldID);
    MIRAggConst *aggConst = mod.GetMemPool()->New<MIRAggConst>(&mod, type);
    int64 size = ReadNum();
    for (int64 i = 0; i < size; i++) {
      aggConst->GetConstVec().push_back(ImportConst(func));
    }
    return aggConst;
  } else if (tag == kBinKindConstSt) {
    ImportConstBase(kind, type, fieldID);
    MIRStConst *stConst = mod.GetMemPool()->New<MIRStConst>(&mod, type);
    int64 size = ReadNum();
    for (int64 i = 0; i < size; i++) {
      stConst->GetStVec().push_back(InSymbol(func));
    }
    size = ReadNum();
    for (int64 i = 0; i < size; i++) {
      stConst->GetStOffsetVec().push_back(ReadNum());
    }
    return stConst;
  } else {
    ASSERT(false, "Unhandled const type");
  }
  return nullptr;
}

GStrIdx BinaryMplImport::ImportStr() {
  int64 tag = ReadNum();
  if (tag == 0) {
    return GStrIdx(0);
  } else if (tag < 0) {
    CHECK_FATAL(-tag < static_cast<int64>(gStrTab.size()), "index out of range in BinaryMplt::ImportStr");
    return gStrTab[-tag];
  } else {
    ASSERT(tag == kBinString, "expecting kBinString");
    std::string str;
    ReadAsciiStr(str);
    GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(str);
    gStrTab.push_back(strIdx);
    return strIdx;
  }
}

UStrIdx BinaryMplImport::ImportUsrStr() {
  int64 tag = ReadNum();
  if (tag == 0) {
    return UStrIdx(0);
  } else if (tag < 0) {
    CHECK_FATAL(-tag < static_cast<int64>(uStrTab.size()), "index out of range in BinaryMplt::InUsrStr");
    return uStrTab[-tag];
  } else {
    ASSERT(tag == kBinUsrString, "expecting kBinUsrString");
    std::string str;
    ReadAsciiStr(str);
    UStrIdx strIdx = GlobalTables::GetUStrTable().GetOrCreateStrIdxFromName(str);
    uStrTab.push_back(strIdx);
    return strIdx;
  }
}

MIRPragmaElement *BinaryMplImport::ImportPragmaElement() {
  MIRPragmaElement *element = mod.GetMemPool()->New<MIRPragmaElement>(&mod);
  element->SetNameStrIdx(ImportStr());
  element->SetTypeStrIdx(ImportStr());
  element->SetType((PragmaValueType)ReadNum());
  if (element->GetType() == kValueString || element->GetType() == kValueType || element->GetType() == kValueField ||
      element->GetType() == kValueMethod || element->GetType() == kValueEnum) {
    element->SetI32Val(static_cast<int32>(ImportStr().GetIdx()));
  } else {
    element->SetU64Val(static_cast<uint64>(ReadInt64()));
  }
  int64 size = ReadNum();
  for (int64 i = 0; i < size; i++) {
    element->PushSubElemVec(ImportPragmaElement());
  }
  return element;
}

MIRPragma *BinaryMplImport::ImportPragma() {
  MIRPragma *p = mod.GetMemPool()->New<MIRPragma>(&mod);
  p->SetKind(static_cast<PragmaKind>(ReadNum()));
  p->SetVisibility(ReadNum());
  p->SetStrIdx(ImportStr());
  p->SetTyIdx(ImportType());
  p->SetTyIdxEx(ImportType());
  p->SetParamNum(ReadNum());
  int64 size = ReadNum();
  for (int64 i = 0; i < size; i++) {
    p->PushElementVector(ImportPragmaElement());
  }
  return p;
}

void BinaryMplImport::ImportFieldPair(FieldPair &fp) {
  fp.first = ImportStr();
  fp.second.first = ImportType();
  fp.second.second.SetAttrFlag(ReadNum());
  fp.second.second.SetAlignValue(ReadNum());
  FieldAttrs fa = fp.second.second;
  if (fa.GetAttr(FLDATTR_static) && fa.GetAttr(FLDATTR_final) &&
      (fa.GetAttr(FLDATTR_public) || fa.GetAttr(FLDATTR_protected))) {
    int64 tag = ReadNum();
    if (tag == kBinInitConst) {
      GlobalTables::GetConstPool().InsertConstPool(fp.first, ImportConst(nullptr));
    }
  }
}

void BinaryMplImport::ImportMethodPair(MethodPair &memPool) {
  std::string funcName;
  ReadAsciiStr(funcName);
  TyIdx funcTyidx = ImportType();
  int64 x = ReadNum();
  ASSERT(x >= 0, "ReadNum error, x: %d", x);
  uint64 attrFlag = static_cast<uint64>(x);

  GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(funcName);
  MIRSymbol *prevFuncSt = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(stridx);
  MIRSymbol *funcSt = nullptr;
  MIRFunction *fn = nullptr;

  if (prevFuncSt != nullptr && (prevFuncSt->GetStorageClass() == kScText && prevFuncSt->GetSKind() == kStFunc)) {
    funcSt = prevFuncSt;
    fn = funcSt->GetFunction();
  } else {
    funcSt = GlobalTables::GetGsymTable().CreateSymbol(kScopeGlobal);
    funcSt->SetNameStrIdx(stridx);
    GlobalTables::GetGsymTable().AddToStringSymbolMap(funcSt);
    funcSt->SetStorageClass(kScText);
    funcSt->SetSKind(kStFunc);
    funcSt->SetTyIdx(funcTyidx);
    funcSt->SetIsImported(imported);
    methodSymbols.push_back(funcSt);

    fn = mod.GetMemPool()->New<MIRFunction>(&mod, funcSt->GetStIdx());
    fn->Init();
    fn->SetPuidx(GlobalTables::GetFunctionTable().GetFuncTable().size());
    GlobalTables::GetFunctionTable().GetFuncTable().push_back(fn);
    funcSt->SetFunction(fn);
    MIRFuncType *funcType = dynamic_cast<MIRFuncType*>(funcSt->GetType());
    fn->SetMIRFuncType(funcType);
    fn->SetFileIndex(0);
    fn->SetBaseClassFuncNames(funcSt->GetNameStrIdx());
    fn->GetFuncAttrs().SetAttrFlag(attrFlag);
  }
  memPool.first.SetFullIdx(funcSt->GetStIdx().FullIdx());
  memPool.second.first.SetIdx(funcTyidx.GetIdx());
  memPool.second.second.SetAttrFlag(attrFlag);
}

void BinaryMplImport::UpdateMethodSymbols() {
  for (auto sym : methodSymbols) {
    MIRFunction *fn = sym->GetFunction();
    ASSERT(fn != nullptr, "fn is null");
    MIRFuncType *funcType = static_cast<MIRFuncType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(sym->GetTyIdx()));
    fn->SetMIRFuncType(funcType);
    fn->SetReturnStruct(GlobalTables::GetTypeTable().GetTypeFromTyIdx(funcType->GetRetTyIdx()));
  }
}

void BinaryMplImport::ImportFieldsOfStructType(FieldVector &fields, uint32 methodSize) {
  int64 size = ReadNum();
  int64 initSize = fields.size() + methodSize;
  for (int64 i = 0; i < size; i++) {
    FieldPair fp;
    ImportFieldPair(fp);
    if (initSize == 0) {
      fields.push_back(fp);
    }
  }
}

void BinaryMplImport::ImportMethodsOfStructType(MethodVector &methods) {
  int64 size = ReadNum();
  bool isEmpty = methods.empty();
  for (int64 i = 0; i < size; i++) {
    MethodPair memPool;
    ImportMethodPair(memPool);
    if (isEmpty) {
      methods.push_back(memPool);
    }
  }
}

void BinaryMplImport::ImportStructTypeData(MIRStructType *type) {
  uint32 methodSize = type->GetMethods().size();
  ImportFieldsOfStructType(type->GetFields(), methodSize);
  ImportFieldsOfStructType(type->GetStaticFields(), methodSize);
  ImportFieldsOfStructType(type->GetParentFields(), methodSize);
  ImportMethodsOfStructType(type->GetMethods());
  type->SetIsImported(imported);
}

void BinaryMplImport::ImportInterfacesOfClassType(std::vector<TyIdx> &interfaces) {
  int64 size = ReadNum();
  bool isEmpty = interfaces.empty();
  for (int64 i = 0; i < size; i++) {
    TyIdx idx = ImportType();
    if (isEmpty) {
      interfaces.push_back(idx);
    }
  }
}

void BinaryMplImport::ImportInfoIsStringOfClassType(std::vector<bool> &infoIsString) {
  int64 size = ReadNum();
  bool isEmpty = infoIsString.empty();

  for (int64 i = 0; i < size; i++) {
    bool isString = static_cast<bool>(ReadNum());

    if (isEmpty) {
      infoIsString.push_back(isString);
    }
  }
}

void BinaryMplImport::ImportInfoOfClassType(std::vector<bool> &infoIsString, std::vector<MIRInfoPair> &infos) {
  int64 size = ReadNum();
  bool isEmpty = infos.empty();
  for (int64 i = 0; i < size; i++) {
    GStrIdx idx = ImportStr();
    int64 x = (infoIsString[i]) ? ImportStr().GetIdx() : ReadNum();
    ASSERT(x >= 0 && x <= std::numeric_limits<uint32_t>::max(), "ReadNum too large, x: %d", x);
    if (isEmpty) {
      infos.push_back(MIRInfoPair(idx, static_cast<uint32>(x)));
    }
  }
}

void BinaryMplImport::ImportPragmaOfClassType(std::vector<MIRPragma*> &pragmas) {
  int64 size = ReadNum();
  bool isEmpty = pragmas.empty();
  for (int64 i = 0; i < size; i++) {
    MIRPragma *pragma = ImportPragma();
    if (isEmpty) {
      pragmas.push_back(pragma);
    }
  }
}

void BinaryMplImport::SetClassTyidxOfMethods(MIRStructType *type) {
  if (type->GetTypeIndex() != 0) {
    // set up classTyIdx for methods
    for (size_t i = 0; i < type->GetMethods().size(); i++) {
      StIdx stidx = type->GetMethodsElement(i).first;
      MIRSymbol *st = GlobalTables::GetGsymTable().GetSymbolFromStidx(stidx.Idx());
      CHECK_FATAL(st != nullptr, "st is null");
      CHECK_FATAL(st->GetSKind() == kStFunc, "unexpected st->sKind");
      st->GetFunction()->SetClassTyIdx(type->GetTypeIndex());
    }
  }
}

void BinaryMplImport::ImportClassTypeData(MIRClassType *type) {
  TyIdx tempType = ImportType();
  // Keep the parent_tyidx we first met.
  if (type->GetParentTyIdx().GetIdx() == 0) {
    type->GetParentTyIdx() = tempType;
  }
  ImportInterfacesOfClassType(type->GetInerfaceImplemented());
  ImportInfoIsStringOfClassType(type->GetInfoIsString());
  ImportInfoOfClassType(type->GetInfoIsString(), type->GetInfo());
  ImportPragmaOfClassType(type->GetPragmVec());
  SetClassTyidxOfMethods(type);
}

void BinaryMplImport::ImportInterfaceTypeData(MIRInterfaceType *type) {
  ImportInterfacesOfClassType(type->GetParentsTyIdx());
  ImportInfoIsStringOfClassType(type->GetInfoIsString());
  ImportInfoOfClassType(type->GetInfoIsString(), type->GetInfo());
  ImportPragmaOfClassType(type->GetPragmVec());
  SetClassTyidxOfMethods(type);
}

void BinaryMplImport::Reset() {
  buf.clear();
  bufI = 0;
  gStrTab.clear();
  uStrTab.clear();
  typTab.clear();
  funcTab.clear();
  symTab.clear();
  methodSymbols.clear();
  typeDefIdxMap.clear();
  definedLabels.clear();
  gStrTab.push_back(GStrIdx(0));  // Dummy
  uStrTab.push_back(UStrIdx(0));  // Dummy
  symTab.push_back(nullptr);      // Dummy
  funcTab.push_back(nullptr);     // Dummy
  for (int32 pti = 0; pti <= static_cast<int32>(PTY_agg); pti++) {
    typTab.push_back(GlobalTables::GetTypeTable().GetTypeFromTyIdx(TyIdx(pti)));
  }
}

TypeAttrs BinaryMplImport::ImportTypeAttrs() {
  TypeAttrs ta;
  ta.SetAttrFlag(ReadNum());
  ta.SetAlignValue(ReadNum());
  return ta;
}

void BinaryMplImport::ImportTypePairs(std::vector<TypePair> &tpairs) {
  int64 size = ReadNum();
  for (int64 i = 0; i < size; i++) {
    TyIdx t0 = ImportType();
    TyIdx t1 = ImportType();
    TypePair tp(t0, t1);
    tpairs.push_back(tp);
  }
}

void BinaryMplImport::completeAggInfo(TyIdx tyIdx) {
  MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  CHECK_FATAL(type != nullptr, "MIRType is null");
  if (type->GetKind() == kTypeInterface) {
    MIRInterfaceType *interfaceType = static_cast<MIRInterfaceType*>(type);
    ImportStructTypeData(interfaceType);
    ImportInterfaceTypeData(interfaceType);
  } else if (type->GetKind() == kTypeClass) {
    MIRClassType *classType = static_cast<MIRClassType*>(type);
    ImportStructTypeData(classType);
    ImportClassTypeData(classType);
  } else if (type->GetKind() == kTypeStruct) {
    MIRStructType *structType = static_cast<MIRStructType*>(type);
    ImportStructTypeData(structType);
  } else {
    ERR(kLncErr, "in BinaryMplImport::completeAggInfo, MIRType error");
  }
}

TyIdx BinaryMplImport::ImportType(bool forPointedType) {
  PrimType primType = (PrimType)0;
  GStrIdx strIdx(0);
  int64 tag = ReadNum();
  static MIRType *typeNeedsComplete = nullptr;
  static int ptrLev = 0;
  if (tag == 0) {
    return TyIdx(0);
  } else if (tag < 0) {
    ASSERT(static_cast<size_t>(-tag) < typTab.size(), "index out of bounds");
    return typTab.at(-tag)->GetTypeIndex();
  }
  bool nameIsLocal = false;
  ImportTypeBase(primType, strIdx, nameIsLocal);
  if (tag == kBinKindTypeScalar) {
    return TyIdx(primType);
  } else if (tag == kBinKindTypePointer) {
    MIRPtrType type(primType, strIdx);
    type.SetNameIsLocal(nameIsLocal);
    size_t idx = typTab.size();
    typTab.push_back(nullptr);
    ++ptrLev;
    type.SetPointedTyIdx(ImportType(true));
    --ptrLev;
    MIRType *origType = InsertInTypeTables(&type);
    typTab[idx] = origType;
    if (typeNeedsComplete != nullptr && ptrLev == 0) {
      TyIdx tyIdxNeedsComplete = typeNeedsComplete->GetTypeIndex();
      typeNeedsComplete = nullptr;
      completeAggInfo(tyIdxNeedsComplete);
    }
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeByName) {
    MIRTypeByName type(strIdx);
    type.SetNameIsLocal(nameIsLocal);
    MIRType *origType = InsertInTypeTables(&type);
    typTab.push_back(origType);
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeFArray) {
    MIRFarrayType type(strIdx);
    type.SetNameIsLocal(nameIsLocal);
    size_t idx = typTab.size();
    typTab.push_back(nullptr);
    type.SetElemtTyIdx(ImportType(forPointedType));
    MIRType *origType = InsertInTypeTables(&type);
    typTab[idx] = origType;
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeJarray) {
    MIRJarrayType type(strIdx);
    type.SetNameIsLocal(nameIsLocal);
    size_t idx = typTab.size();
    typTab.push_back(nullptr);
    type.SetElemtTyIdx(ImportType(forPointedType));
    MIRType *origType = InsertInTypeTables(&type);
    typTab[idx] = origType;
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeArray) {
    MIRArrayType type(strIdx);
    type.SetNameIsLocal(nameIsLocal);
    type.SetDim(ReadNum());
    CHECK_FATAL(type.GetDim() < kMaxArrayDim, "array index out of range");
    for (uint16 i = 0; i < type.GetDim(); i++) {
      type.SetSizeArrayItem(i, ReadNum());
    }
    size_t idx = typTab.size();
    typTab.push_back(nullptr);
    type.SetElemtTyIdx(ImportType(forPointedType));
    MIRType *origType = InsertInTypeTables(&type);
    typTab[idx] = origType;
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeFunction) {
    MIRFuncType type(strIdx);
    type.SetNameIsLocal(nameIsLocal);
    size_t idx = typTab.size();
    typTab.push_back(nullptr);
    type.SetRetTyIdx(ImportType());
    type.SetVarArgs(ReadNum());
    int64 size = ReadNum();
    for (int64 i = 0; i < size; i++) {
      type.GetParamTypeList().push_back(ImportType());
    }
    size = ReadNum();
    for (int64 i = 0; i < size; i++) {
      type.GetParamAttrsList().push_back(ImportTypeAttrs());
    }
    MIRType *origType = InsertInTypeTables(&type);
    typTab[idx] = origType;
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeParam) {
    MIRTypeParam type(strIdx);
    type.SetNameIsLocal(nameIsLocal);
    MIRType *origType = InsertInTypeTables(&type);
    typTab.push_back(origType);
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeInstantVector) {
    MIRTypeKind kind = (MIRTypeKind)ReadNum();
    MIRInstantVectorType type(kind, strIdx);
    type.SetNameIsLocal(nameIsLocal);
    MIRInstantVectorType *origType = static_cast<MIRInstantVectorType*>(InsertInTypeTables(&type));
    typTab.push_back(origType);
    ImportTypePairs(origType->GetInstantVec());
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeGenericInstant) {
    MIRGenericInstantType type(strIdx);
    type.SetNameIsLocal(nameIsLocal);
    MIRGenericInstantType *origType = static_cast<MIRGenericInstantType*>(InsertInTypeTables(&type));
    typTab.push_back(origType);
    ImportTypePairs(origType->GetInstantVec());
    origType->SetGenericTyIdx(ImportType());
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeBitField) {
    uint8 fieldSize = ReadNum();
    MIRBitFieldType type(fieldSize, primType, strIdx);
    type.SetNameIsLocal(nameIsLocal);
    MIRType *origType = InsertInTypeTables(&type);
    typTab.push_back(origType);
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeStruct) {
    MIRTypeKind kind = (MIRTypeKind)ReadNum();
    MIRStructType type(kind, strIdx);
    type.SetNameIsLocal(nameIsLocal);
    MIRStructType *origType = static_cast<MIRStructType*>(InsertInTypeTables(&type));
    typTab.push_back(origType);
    if (kind != kTypeStructIncomplete) {
      if (forPointedType) {
        typeNeedsComplete = origType;
      } else {
        ImportStructTypeData(origType);
      }
    }
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeClass) {
    MIRTypeKind kind = (MIRTypeKind)ReadNum();
    MIRClassType type(kind, strIdx);
    type.SetNameIsLocal(nameIsLocal);
    MIRClassType *origType = static_cast<MIRClassType*>(InsertInTypeTables(&type));
    typTab.push_back(origType);
    if (kind != kTypeClassIncomplete) {
      if (forPointedType) {
        typeNeedsComplete = origType;
      } else {
        ImportStructTypeData(origType);
        ImportClassTypeData(origType);
      }
    }
    return origType->GetTypeIndex();
  } else if (tag == kBinKindTypeInterface) {
    MIRTypeKind kind = (MIRTypeKind)ReadNum();
    MIRInterfaceType type(kind, strIdx);
    type.SetNameIsLocal(nameIsLocal);
    MIRInterfaceType *origType = static_cast<MIRInterfaceType*>(InsertInTypeTables(&type));
    typTab.push_back(origType);
    if (kind != kTypeInterfaceIncomplete) {
      if (forPointedType) {
        typeNeedsComplete = origType;
      } else {
        ImportStructTypeData(origType);
        ImportInterfaceTypeData(origType);
      }
    }
    return origType->GetTypeIndex();
  } else {
    ASSERT(false, "Unexpected binary kind");
  }
  return TyIdx(0);
}

void BinaryMplImport::ImportTypeBase(PrimType &primType, GStrIdx &strIdx, bool &nameIsLocal) {
  primType = (PrimType)ReadNum();
  strIdx = ImportStr();
  nameIsLocal = ReadNum();
}

inline static bool IsIncomplete(const MIRType *type) {
  ASSERT(type != nullptr, "MIRType is null");
  return (type->GetKind() == kTypeInterfaceIncomplete || type->GetKind() == kTypeClassIncomplete ||
          type->GetKind() == kTypeStructIncomplete);
}

inline static bool IsObject(const MIRType *type) {
  ASSERT(type != nullptr, "MIRType is null");
  return (type->GetKind() == kTypeClass || type->GetKind() == kTypeClassIncomplete ||
          type->GetKind() == kTypeInterface || type->GetKind() == kTypeInterfaceIncomplete);
}

MIRType *BinaryMplImport::InsertInTypeTables(MIRType *type) {
  ASSERT(type != nullptr, "null ptr check");
  TyIdx prevTyIdx = mod.GetTypeNameTab()->GetTyIdxFromGStrIdx(type->GetNameStrIdx());
  if (prevTyIdx != 0 && !type->IsNameIsLocal()) {
    MIRType *prevType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(prevTyIdx);
    if ((IsIncomplete(prevType) && IsIncomplete(type)) || (!IsIncomplete(prevType) && !IsIncomplete(type)) ||
        (!IsIncomplete(prevType) && IsIncomplete(type))) {
      ASSERT(IsObject(prevType) && IsObject(type), "impossible");
      type = prevType->CopyMIRTypeNode();
      if (type->GetKind() == kTypeStruct || type->GetKind() == kTypeStructIncomplete) {
        tmpStruct.push_back(static_cast<MIRStructType*>(type));
      } else if (type->GetKind() == kTypeClass || type->GetKind() == kTypeClassIncomplete) {
        tmpClass.push_back(static_cast<MIRClassType*>(type));
      } else if (type->GetKind() == kTypeInterface || type->GetKind() == kTypeInterfaceIncomplete) {
        tmpInterface.push_back(static_cast<MIRInterfaceType*>(type));
      }
    } else {
      ASSERT(IsObject(prevType) && IsObject(type), "impossible");
      // New definition wins
      type->GetTypeIndex() = prevTyIdx;
      ASSERT(GlobalTables::GetTypeTable().GetTypeTable().empty() == false, "container check");
      GlobalTables::GetTypeTable().SetTypeWithTyIdx(prevTyIdx, type->CopyMIRTypeNode());
      type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(prevTyIdx);
      if (!IsIncomplete(type)) {
        GlobalTables::GetTypeNameTable().SetGStrIdxToTyIdx(type->GetNameStrIdx(), type->GetTypeIndex());
      }
    }
  } else {
    // New type, no previous definition or anonymous type
    TyIdx tyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(type);
    type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
    if (tyIdx.GetIdx() + 1 == GlobalTables::GetTypeTable().GetTypeTable().size() && !type->IsNameIsLocal()) {
      GStrIdx stridx = type->GetNameStrIdx();
      if (IsObject(type)) {
        mod.GetTypeNameTab()->SetGStrIdxToTyIdx(stridx, tyIdx);
        mod.AddClass(tyIdx);
        mod.GetTypeDefOrder().push_back(stridx);
        if (!IsIncomplete(type)) {
          GlobalTables::GetTypeNameTable().SetGStrIdxToTyIdx(stridx, tyIdx);
        }
      } else if (type->GetKind() == kTypeByName) {
        mod.GetTypeNameTab()->SetGStrIdxToTyIdx(stridx, tyIdx);
      }
    }
  }
  return type;
}

void BinaryMplImport::SetupEHRootType() {
  // setup eh root type with most recent Ljava_2Flang_2FObject_3B
  GStrIdx gStrIdx = GlobalTables::GetStrTable().GetStrIdxFromName(NameMangler::kJavaLangObjectStr);
  if (gStrIdx == 0) {
    return;
  }

  TyIdx tyIdx = GlobalTables::GetTypeNameTable().GetTyidxFromGstrIdx(gStrIdx);
  if (tyIdx != 0) {
    mod.SetThrowableTyIdx(tyIdx);
  }
}

MIRSymbol *BinaryMplImport::GetOrCreateSymbol(const TyIdx &tyIdx, const GStrIdx &strIdx, MIRSymKind mclass,
                                              MIRStorageClass sclass, MIRFunction *func, uint8 scpID) {
  MIRSymbol *st = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(strIdx);
  if (st != nullptr && st->GetStorageClass() == sclass && st->GetSKind() == mclass && scpID == kScopeGlobal) {
    return st;
  }
  return mirBuilder.CreateSymbol(tyIdx, strIdx, mclass, sclass, func, scpID);
}

MIRSymbol *BinaryMplImport::InSymbol(MIRFunction *func) {
  int64 tag = ReadNum();
  if (tag == 0) {
    return nullptr;
  } else if (tag < 0) {
    ASSERT(static_cast<size_t>(-tag) < symTab.size(), "index out of bounds");
    return symTab.at(-tag);
  } else {
    ASSERT(tag == kBinSymbol, "expecting kBinSymbol");
    int64 scope = ReadNum();
    GStrIdx stridx = ImportStr();
    MIRSymKind skind = static_cast<MIRSymKind>(ReadNum());
    MIRStorageClass sclass = static_cast<MIRStorageClass>(ReadNum());
    TyIdx tyTmp(0);
    MIRSymbol *sym = GetOrCreateSymbol(tyTmp, stridx, skind, sclass, func, scope);
    symTab.push_back(sym);
    sym->SetAttrs(ImportTypeAttrs());
    sym->SetIsTmp(ReadNum() != 0);

    sym->SetIsImported(imported);
    if (skind == kStPreg) {
      ASSERT(false, "outing kStPreg");
    } else if (skind == kStConst || skind == kStVar) {
      ASSERT(false, "outing kStConst or kStVar");
    } else if (skind == kStFunc) {
      PUIdx puidx = ImportFunction();
      TyIdx tyidx = ImportType();
      sym->SetTyIdx(tyidx);
      sym->SetFunction(GlobalTables::GetFunctionTable().GetFunctionFromPuidx(puidx));
    }
    return sym;
  }
}

PUIdx BinaryMplImport::ImportFunction() {
  int64 tag = ReadNum();
  if (tag == 0) {
    return 0;
  } else if (tag < 0) {
    ASSERT(static_cast<size_t>(-tag) < funcTab.size(), "index out of bounds");
    return funcTab.at(-tag)->GetPuidx();
  }
  ASSERT(tag == kBinFunction, "expecting kBinFunction");
  MIRSymbol *funcSt = InSymbol(nullptr);
  ASSERT(funcSt, "null ptr check");
  MIRFunction *func = nullptr;
  if (funcSt->GetFunction() == nullptr) {
    maple::MIRBuilder builder(&mod);
    func = builder.CreateFunction(funcSt->GetStIdx());
    funcTab.push_back(func);
  } else {
    func = funcSt->GetFunction();
    funcTab.push_back(func);
  }
  funcSt->SetFunction(func);
  if (mod.IsJavaModule()) {
    func->SetBaseClassFuncNames(funcSt->GetNameStrIdx());
  }
  TyIdx retType = ImportType();
  func->SetReturnTyIdx(retType);

  func->GetStIdx() = funcSt->GetStIdx();
  func->GetFuncAttrs().SetAttrFlag(ReadNum());
  func->SetFlag(ReadNum());
  func->SetClassTyIdx(ImportType());
  return func->GetPuidx();
}

inline void BinaryMplImport::SkipTotalSize() {
  ReadInt();
}

void BinaryMplImport::ReadStrField() {
  SkipTotalSize();

  int32 size = ReadInt();
  for (int64 i = 0; i < size; i++) {
    GStrIdx stridx = ImportStr();
    GlobalTables::GetConstPool().PutLiteralNameAsImported(stridx);
  }
  ASSERT(ReadNum() == ~kBinStrStart, "pattern mismatch in Read STR");
}

void BinaryMplImport::ReadTypeField() {
  SkipTotalSize();

  int32 size = ReadInt();
  for (int64 i = 0; i < size; i++) {
    ImportType();
  }
  ASSERT(ReadNum() == ~kBinTypeStart, "pattern mismatch in Read TYPE");
}

void BinaryMplImport::ReadContentField() {
  SkipTotalSize();

  int32 size = ReadInt();
  int64 item;
  int32 offset;
  for (int32 i = 0; i < size; i++) {
    item = ReadNum();
    offset = ReadInt();
    content[item] = offset;
  }
  ASSERT(ReadNum() == ~kBinContentStart, "pattern mismatch in Read CONTENT");
}

void BinaryMplImport::Jump2NextField() {
  uint32 totalSize = ReadInt();
  bufI += (totalSize - sizeof(uint32));
  ReadNum();  /// skip end tag for this field
}

bool BinaryMplImport::Import(const std::string &fname, bool readSymbols, bool readSe) {
  Reset();
  ReadFileAt(fname, 0);
  int32 magic = ReadInt();
  if (kMpltMagicNumber != magic) {  // not a binary mplt file
    buf.clear();
    return false;
  }
  int64 fieldID = ReadNum();
  while (fieldID != kBinFinish) {
    switch (fieldID) {
      case kBinContentStart: {
        ReadContentField();
        break;
      }
      case kBinStrStart: {
        ReadStrField();
        break;
      }
      case kBinTypeStart: {
        ReadTypeField();
        break;
      }
      case kBinCgStart: {
        Jump2NextField();
        break;
      }
      default:
        ASSERT(false, "should not run here");
    }
    fieldID = ReadNum();
  }
  UpdateMethodSymbols();
  SetupEHRootType();
  return true;
}

}  // namespace maple
