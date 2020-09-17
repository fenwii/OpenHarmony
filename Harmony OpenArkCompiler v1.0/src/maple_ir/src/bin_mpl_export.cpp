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
#include "bin_mpl_export.h"
#include <sstream>
#include <vector>
#include "mir_function.h"
#include "name_mangler.h"
#include "opcode_info.h"
#include "mir_pragma.h"
#include "mir_builder.h"
#include "bin_mplt.h"
#include "factory.h"

namespace {

using namespace maple;

using OutputConstFactory = FunctionFactory<MIRConstKind, void, MIRConst*, BinaryMplExport*>;
using OutputTypeFactory = FunctionFactory<MIRTypeKind, void, MIRType*, BinaryMplExport*>;

void OutputConstInt(MIRConst *constVal, BinaryMplExport *mplExport) {
  mplExport->WriteNum(kBinKindConstInt);
  mplExport->OutputConstBase(constVal);
  mplExport->WriteNum(static_cast<MIRIntConst*>(constVal)->GetValue());
}

void OutputConstAddrof(MIRConst *constVal, BinaryMplExport *mplExport) {
  mplExport->WriteNum(kBinKindConstAddrof);
  mplExport->OutputConstBase(constVal);
  MIRAddrofConst *addrof = static_cast<MIRAddrofConst*>(constVal);
  mplExport->OutputSymbol(mplExport->GetMIRModule().CurFunction()->GetLocalOrGlobalSymbol(addrof->GetSymbolIndex()));
  mplExport->WriteNum(addrof->GetFieldID());
}

void OutputConstAddrofFunc(MIRConst *constVal, BinaryMplExport *mplExport) {
  mplExport->WriteNum(kBinKindConstAddrofFunc);
  mplExport->OutputConstBase(constVal);
  MIRAddroffuncConst *addrfunc = static_cast<MIRAddroffuncConst*>(constVal);
  mplExport->OutputFunction(addrfunc->GetValue());
}

void OutputConstLbl(MIRConst *constVal, BinaryMplExport *mplExport) {
  ASSERT(false, "NYI");
}

void OutputConstStr(MIRConst *constVal, BinaryMplExport *mplExport) {
  mplExport->WriteNum(kBinKindConstStr);
  mplExport->OutputConstBase(constVal);
  MIRStrConst *strc = static_cast<MIRStrConst*>(constVal);
  mplExport->OutputUsrStr(strc->GetValue());
}

void OutputConstStr16(MIRConst *constVal, BinaryMplExport *mplExport) {
  mplExport->WriteNum(kBinKindConstStr16);
  mplExport->OutputConstBase(constVal);
  MIRStr16Const *mirStr16 = static_cast<MIRStr16Const*>(constVal);
  std::u16string str16 = GlobalTables::GetU16StrTable().GetStringFromStrIdx(mirStr16->GetValue());
  std::string str;
  NameMangler::UTF16ToUTF8(str, str16);
  mplExport->WriteNum(str.length());
  for (uint64 i = 0; i < str.length(); i++) {
    mplExport->Write(static_cast<uint8>(str[i]));
  }
}

void OutputConstFloat(MIRConst *constVal, BinaryMplExport *mplExport) {
  mplExport->WriteNum(kBinKindConstFloat);
  MIRFloatConst *fconst = static_cast<MIRFloatConst*>(constVal);
  mplExport->WriteNum(fconst->GetIntValue());
}

void OutputConstDouble(MIRConst *constVal, BinaryMplExport *mplExport) {
  mplExport->WriteNum(kBinKindConstDouble);
  MIRDoubleConst *dconst = static_cast<MIRDoubleConst*>(constVal);
  mplExport->WriteNum(dconst->GetIntValue());
}

void OutputConstAgg(MIRConst *constVal, BinaryMplExport *mplExport) {
  mplExport->WriteNum(kBinKindConstAgg);
  mplExport->OutputConstBase(constVal);
  MIRAggConst *aggConst = static_cast<MIRAggConst*>(constVal);
  size_t size = aggConst->GetConstVec().size();
  mplExport->WriteNum(size);
  for (size_t i = 0; i < size; i++) {
    mplExport->OutputConst(aggConst->GetConstVecItem(i));
  }
}

void OutputConstSt(MIRConst *constVal, BinaryMplExport *mplExport) {
  mplExport->WriteNum(kBinKindConstSt);
  mplExport->OutputConstBase(constVal);
  MIRStConst *stConst = static_cast<MIRStConst*>(constVal);
  size_t size = stConst->GetStVec().size();
  mplExport->WriteNum(size);
  for (size_t i = 0; i < size; i++) {
    mplExport->OutputSymbol(stConst->GetStVecItem(i));
  }
  size = stConst->GetStOffsetVec().size();
  mplExport->WriteNum(size);
  for (size_t i = 0; i < size; i++) {
    mplExport->WriteNum(stConst->GetStOffsetVecItem(i));
  }
}

void InitOutputConstFactory() {
  RegisterFactoryFunction<OutputConstFactory>(kConstInt, OutputConstInt);
  RegisterFactoryFunction<OutputConstFactory>(kConstAddrof, OutputConstAddrof);
  RegisterFactoryFunction<OutputConstFactory>(kConstAddrofFunc, OutputConstAddrofFunc);
  RegisterFactoryFunction<OutputConstFactory>(kConstLblConst, OutputConstLbl);
  RegisterFactoryFunction<OutputConstFactory>(kConstStrConst, OutputConstStr);
  RegisterFactoryFunction<OutputConstFactory>(kConstStr16Const, OutputConstStr16);
  RegisterFactoryFunction<OutputConstFactory>(kConstFloatConst, OutputConstFloat);
  RegisterFactoryFunction<OutputConstFactory>(kConstDoubleConst, OutputConstDouble);
  RegisterFactoryFunction<OutputConstFactory>(kConstAggConst, OutputConstAgg);
  RegisterFactoryFunction<OutputConstFactory>(kConstStConst, OutputConstSt);
}

void OutputTypeScalar(MIRType *ty, BinaryMplExport *mplExport) {
  mplExport->WriteNum(kBinKindTypeScalar);
  mplExport->OutputTypeBase(ty);
}

void OutputTypePointer(MIRType *ty, BinaryMplExport *mplExport) {
  MIRPtrType *type = static_cast<MIRPtrType*>(ty);
  mplExport->WriteNum(kBinKindTypePointer);
  mplExport->OutputTypeBase(type);
  mplExport->OutputType(type->GetPointedTyIdx());
}

void OutputTypeByName(MIRType *ty, BinaryMplExport *mplExport) {
  MIRTypeByName *type = static_cast<MIRTypeByName*>(ty);
  mplExport->WriteNum(kBinKindTypeByName);
  mplExport->OutputTypeBase(type);
}

void OutputTypeFArray(MIRType *ty, BinaryMplExport *mplExport) {
  MIRFarrayType *type = static_cast<MIRFarrayType*>(ty);
  mplExport->WriteNum(kBinKindTypeFArray);
  mplExport->OutputTypeBase(type);
  mplExport->OutputType(type->GetElemTyIdx());
}

void OutputTypeJArray(MIRType *ty, BinaryMplExport *mplExport) {
  MIRJarrayType *type = static_cast<MIRJarrayType*>(ty);
  mplExport->WriteNum(kBinKindTypeJarray);
  mplExport->OutputTypeBase(type);
  mplExport->OutputType(type->GetElemTyIdx());
}

void OutputTypeArray(MIRType *ty, BinaryMplExport *mplExport) {
  MIRArrayType *type = static_cast<MIRArrayType*>(ty);
  mplExport->WriteNum(kBinKindTypeArray);
  mplExport->OutputTypeBase(type);
  mplExport->WriteNum(type->GetDim());
  for (int i = 0; i < type->GetDim(); i++) {
    mplExport->WriteNum(type->GetSizeArrayItem(i));
  }
  mplExport->OutputType(type->GetElemTyIdx());
}

void OutputTypeFunction(MIRType *ty, BinaryMplExport *mplExport) {
  MIRFuncType *type = static_cast<MIRFuncType*>(ty);
  mplExport->WriteNum(kBinKindTypeFunction);
  mplExport->OutputTypeBase(type);
  mplExport->OutputType(type->GetRetTyIdx());
  mplExport->WriteNum(type->IsVarargs());
  size_t size = type->GetParamTypeList().size();
  mplExport->WriteNum(size);
  for (size_t i = 0; i < size; i++) {
    mplExport->OutputType(type->GetParamTypeList()[i]);
  }
  size = type->GetParamAttrsList().size();
  mplExport->WriteNum(size);
  for (size_t i = 0; i < size; i++) {
    mplExport->OutputTypeAttrs(type->GetParamAttrsList()[i]);
  }
}

void OutputTypeParam(MIRType *ty, BinaryMplExport *mplExport) {
  MIRTypeParam *type = static_cast<MIRTypeParam*>(ty);
  mplExport->WriteNum(kBinKindTypeParam);
  mplExport->OutputTypeBase(type);
}

void OutputTypeInstantVector(MIRType *ty, BinaryMplExport *mplExport) {
  MIRInstantVectorType *type = static_cast<MIRInstantVectorType*>(ty);
  mplExport->WriteNum(kBinKindTypeInstantVector);
  mplExport->OutputTypeBase(type);
  mplExport->WriteNum(ty->GetKind());
  mplExport->OutputTypePairs(type);
}

void OutputTypeGenericInstant(MIRType *ty, BinaryMplExport *mplExport) {
  MIRGenericInstantType *type = static_cast<MIRGenericInstantType*>(ty);
  mplExport->WriteNum(kBinKindTypeGenericInstant);
  mplExport->OutputTypeBase(type);
  mplExport->OutputTypePairs(type);
  mplExport->OutputType(type->GetGenericTyIdx());
}

void OutputTypeBitField(MIRType *ty, BinaryMplExport *mplExport) {
  MIRBitFieldType *type = static_cast<MIRBitFieldType*>(ty);
  mplExport->WriteNum(kBinKindTypeBitField);
  mplExport->OutputTypeBase(type);
  mplExport->WriteNum(type->GetFieldSize());
}

// for Struct/StructIncomplete/Union
void OutputTypeStruct(MIRType *ty, BinaryMplExport *mplExport) {
  MIRStructType *type = static_cast<MIRStructType*>(ty);
  mplExport->WriteNum(kBinKindTypeStruct);
  mplExport->OutputTypeBase(type);
  MIRTypeKind kind = ty->GetKind();
  if (type->IsImported()) {
    CHECK_FATAL(ty->GetKind() != kTypeUnion, "must be");
    kind = kTypeStructIncomplete;
  }
  mplExport->WriteNum(kind);
  if (kind != kTypeStructIncomplete) {
    mplExport->OutputStructTypeData(type);
  }
}

void OutputTypeClass(MIRType *ty, BinaryMplExport *mplExport) {
  MIRClassType *type = static_cast<MIRClassType*>(ty);
  mplExport->WriteNum(kBinKindTypeClass);
  mplExport->OutputTypeBase(type);
  MIRTypeKind kind = ty->GetKind();
  if (type->IsImported()) {
    kind = kTypeClassIncomplete;
  }
  mplExport->WriteNum(kind);
  if (kind != kTypeClassIncomplete) {
    mplExport->OutputStructTypeData(type);
    mplExport->OutputClassTypeData(type);
  }
}

void OutputTypeInterface(MIRType *ty, BinaryMplExport *mplExport) {
  MIRInterfaceType *type = static_cast<MIRInterfaceType*>(ty);
  mplExport->WriteNum(kBinKindTypeInterface);
  mplExport->OutputTypeBase(type);
  MIRTypeKind kind = ty->GetKind();
  if (type->IsImported()) {
    kind = kTypeInterfaceIncomplete;
  }
  mplExport->WriteNum(kind);
  if (kind != kTypeInterfaceIncomplete) {
    mplExport->OutputStructTypeData(type);
    mplExport->OutputInterfaceTypeData(type);
  }
}

void OutputTypeConstString(MIRType *ty, BinaryMplExport *mplExport) {
  ASSERT(false, "Type's kind not yet implemented: %d", ty->GetKind());
}

void InitOutputTypeFactory() {
  RegisterFactoryFunction<OutputTypeFactory>(kTypeScalar, OutputTypeScalar);
  RegisterFactoryFunction<OutputTypeFactory>(kTypePointer, OutputTypePointer);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeByName, OutputTypeByName);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeFArray, OutputTypeFArray);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeJArray, OutputTypeJArray);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeArray, OutputTypeArray);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeFunction, OutputTypeFunction);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeParam, OutputTypeParam);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeInstantVector, OutputTypeInstantVector);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeGenericInstant, OutputTypeGenericInstant);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeBitField, OutputTypeBitField);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeStruct, OutputTypeStruct);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeStructIncomplete, OutputTypeStruct);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeUnion, OutputTypeStruct);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeClass, OutputTypeClass);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeClassIncomplete, OutputTypeClass);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeInterface, OutputTypeInterface);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeInterfaceIncomplete, OutputTypeInterface);
  RegisterFactoryFunction<OutputTypeFactory>(kTypeConstString, OutputTypeConstString);
}

};  // namespace

namespace maple {

int BinaryMplExport::typeMarkOffset = 0;

BinaryMplExport::BinaryMplExport(MIRModule &md) : mod(md) {
  bufI = 0;
  Init();
  InitOutputConstFactory();
  InitOutputTypeFactory();
}

uint8 BinaryMplExport::Read() {
  CHECK_FATAL(bufI < buf.size(), "Index out of bound in BinaryMplImport::Read()");
  return buf[bufI++];
}

/* Little endian */
int32 BinaryMplExport::ReadInt() {
  uint32 x0 = static_cast<uint32>(Read());
  uint32 x1 = static_cast<uint32>(Read());
  uint32 x2 = static_cast<uint32>(Read());
  uint32 x3 = static_cast<uint32>(Read());
  int32 x = static_cast<int32>((((((x3 << 8) + x2) << 8) + x1) << 8) + x0);
  return x;
}

void BinaryMplExport::Write(uint8 b) {
  buf.push_back(b);
}

/* Little endian */
void BinaryMplExport::WriteInt(int32 x) {
  Write(static_cast<uint8>(static_cast<uint32>(x) & 0xFF));
  Write(static_cast<uint8>((static_cast<uint32>(x) >> 8) & 0xFF));
  Write(static_cast<uint8>((static_cast<uint32>(x) >> 16) & 0xFF));
  Write(static_cast<uint8>((static_cast<uint32>(x) >> 24) & 0xFF));
}

void BinaryMplExport::ExpandFourBuffSize() {
  WriteInt(0);
}

void BinaryMplExport::Fixup(size_t i, int32 x) {
  buf[i] = static_cast<uint8>(static_cast<uint32>(x) & 0xFF);
  buf[i + 1] = static_cast<uint8>((static_cast<uint32>(x) >> 8) & 0xFF);
  buf[i + 2] = static_cast<uint8>((static_cast<uint32>(x) >> 16) & 0xFF);
  buf[i + 3] = static_cast<uint8>((static_cast<uint32>(x) >> 24) & 0xFF);
}

void BinaryMplExport::WriteInt64(int64 x) {
  WriteInt(static_cast<int32>(static_cast<uint64>(x) & 0xFFFFFFFF));
  WriteInt(static_cast<int32>((static_cast<uint64>(x) >> 32) & 0xFFFFFFFF));
}

/* LEB128 */
void BinaryMplExport::WriteNum(int64 x) {
  while (x < -0x40 || x >= 0x40) {
    Write(static_cast<uint8>((static_cast<uint64>(x) & 0x7F) + 0x80));
    x = x >> 7;
  }
  Write((uint8)(static_cast<uint64>(x) & 0x7F));
}

void BinaryMplExport::WriteAsciiStr(const std::string &str) {
  for (size_t i = 0; i < str.size(); i++) {
    Write(static_cast<uint8>(str[i]));
  }
  Write(0);
}

void BinaryMplExport::DumpBuf(const std::string &name) {
  FILE *f = fopen(name.c_str(), "wb");
  if (f == nullptr) {
    LogInfo::MapleLogger(kLlErr) << "Error while creating the binary file: " << name << std::endl;
    FATAL(kLncFatal, "Error while creating the binary file: %s\n", name.c_str());
  }
  size_t size = buf.size();
  size_t k = fwrite(&buf[0], sizeof(uint8), size, f);
  fclose(f);
  if (k != size) {
    LogInfo::MapleLogger(kLlErr) << "Error while writing the binary file: " << name << std::endl;
  }
}

void BinaryMplExport::OutputConstBase(const MIRConst *constVal) {
  WriteNum(constVal->GetKind());
  OutputType(constVal->GetType()->GetTypeIndex());
  WriteNum(constVal->GetFieldId());
}

void BinaryMplExport::OutputConst(MIRConst *constVal) {
  if (constVal == nullptr) {
    WriteNum(0);
  } else {
    auto func = CreateProductFunction<OutputConstFactory>(constVal->GetKind());
    if (func != nullptr) {
      func(constVal, this);
    }
  }
}

void BinaryMplExport::OutputStr(const GStrIdx &gstr) {
  if (gstr == 0) {
    WriteNum(0);
    return;
  }

  auto it = gStrMark.find(gstr);
  if (it != gStrMark.end()) {
    WriteNum(-(it->second));
    return;
  }

  size_t mark = gStrMark.size();
  gStrMark[gstr] = mark;
  WriteNum(kBinString);
  ASSERT(GlobalTables::GetStrTable().StringTableSize() != 0, "container check");
  WriteAsciiStr(GlobalTables::GetStrTable().GetStringFromStrIdx(gstr));
}

void BinaryMplExport::OutputUsrStr(UStrIdx ustr) {
  if (ustr == 0) {
    WriteNum(0);
    return;
  }

  auto it = uStrMark.find(ustr);
  if (it != uStrMark.end()) {
    WriteNum(-(it->second));
    return;
  }

  size_t mark = uStrMark.size();
  uStrMark[ustr] = mark;
  WriteNum(kBinUsrString);
  WriteAsciiStr(GlobalTables::GetUStrTable().GetStringFromStrIdx(ustr));
}

void BinaryMplExport::OutputPragmaElement(const MIRPragmaElement *e) {
  ASSERT(e != nullptr, "MIRPragmaElement is null.");
  OutputStr(e->GetNameStrIdx());
  OutputStr(e->GetTypeStrIdx());
  WriteNum(e->GetType());

  if (e->GetType() == kValueString || e->GetType() == kValueType || e->GetType() == kValueField ||
      e->GetType() == kValueMethod || e->GetType() == kValueEnum) {
    OutputStr(GStrIdx(e->GetI32Val()));
  } else {
    WriteInt64(e->GetU64Val());
  }
  size_t size = e->GetSubElemVec().size();
  WriteNum(size);
  for (size_t i = 0; i < size; i++) {
    OutputPragmaElement(e->GetSubElement(i));
  }
}

void BinaryMplExport::OutputPragma(const MIRPragma *p) {
  ASSERT(p != nullptr, "MIRPragma is null.");
  WriteNum(p->GetKind());
  WriteNum(p->GetVisibility());
  OutputStr(p->GetStrIdx());
  OutputType(p->GetTyIdx());
  OutputType(p->GetTyIdxEx());
  WriteNum(p->GetParamNum());
  size_t size = p->GetElementVector().size();
  WriteNum(size);
  for (size_t i = 0; i < size; i++) {
    OutputPragmaElement(p->GetNthElement(i));
  }
}

void BinaryMplExport::OutputTypeBase(const MIRType *type) {
  ASSERT(type != nullptr, "MIRType is null.");
  WriteNum(type->GetPrimType());
  OutputStr(type->GetNameStrIdx());
  WriteNum(type->IsNameIsLocal());
}

void BinaryMplExport::OutputFieldPair(const FieldPair &fp) {
  OutputStr(fp.first);          // GStrIdx
  OutputType(fp.second.first);  // TyIdx
  FieldAttrs fa = fp.second.second;
  WriteNum(fa.GetAttrFlag());
  WriteNum(fa.GetAlignValue());
  if (fa.GetAttr(FLDATTR_static) && fa.GetAttr(FLDATTR_final) &&
      (fa.GetAttr(FLDATTR_public) || fa.GetAttr(FLDATTR_protected))) {
    const char *fieldName = (GlobalTables::GetStrTable().GetStringFromStrIdx(fp.first)).c_str();
    MIRSymbol *fieldVar = mod.GetMIRBuilder()->GetGlobalDecl(fieldName);
    if (fieldVar != nullptr && dynamic_cast<MIRStr16Const*>(fieldVar->GetKonst())) {
      WriteNum(kBinInitConst);
      OutputConst(fieldVar->GetKonst());
    } else {
      WriteNum(0);
    }
  }
}

void BinaryMplExport::OutputMethodPair(const MethodPair &memPool) {
  // use GStrIdx instead, StIdx will be created by ImportMethodPair
  MIRSymbol *funcSt = GlobalTables::GetGsymTable().GetSymbolFromStidx(memPool.first.Idx());
  CHECK_FATAL(funcSt != nullptr, "can't get symbol! Check it!");
  WriteAsciiStr(GlobalTables::GetStrTable().GetStringFromStrIdx(funcSt->GetNameStrIdx()));
  OutputType(memPool.second.first);               // TyIdx
  WriteNum(memPool.second.second.GetAttrFlag());  // FuncAttrs
}

void BinaryMplExport::OutputFieldsOfStruct(const FieldVector &fields) {
  WriteNum(fields.size());
  for (const FieldPair &fp : fields) {
    OutputFieldPair(fp);
  }
}

void BinaryMplExport::OutputMethodsOfStruct(const MethodVector &methods) {
  WriteNum(methods.size());
  for (const MethodPair &memPool : methods) {
    OutputMethodPair(memPool);
  }
}

void BinaryMplExport::OutputStructTypeData(MIRStructType *type) {
  ASSERT(type != nullptr, "MIRStructType is null.");
  OutputFieldsOfStruct(type->GetFields());
  OutputFieldsOfStruct(type->GetStaticFields());
  OutputFieldsOfStruct(type->GetParentFields());
  OutputMethodsOfStruct(type->GetMethods());
}

void BinaryMplExport::OutputImplementedInterfaces(const std::vector<TyIdx> &interfaces) {
  WriteNum(interfaces.size());
  for (const TyIdx &tyIdx : interfaces) {
    OutputType(tyIdx);
  }
}

void BinaryMplExport::OutputInfoIsString(const std::vector<bool> &infoIsString) {
  WriteNum(infoIsString.size());
  for (bool isString : infoIsString) {
    WriteNum(static_cast<int64>(isString));
  }
}

void BinaryMplExport::OutputInfo(const std::vector<MIRInfoPair> &info, const std::vector<bool> &infoIsString) {
  size_t size = info.size();
  WriteNum(size);
  for (size_t i = 0; i < size; i++) {
    OutputStr(info[i].first);  // GStrIdx
    if (infoIsString[i]) {
      OutputStr(GStrIdx(info[i].second));
    } else {
      WriteNum(info[i].second);
    }
  }
}

void BinaryMplExport::OutputPragmaVec(const std::vector<MIRPragma*> &pragmaVec) {
  WriteNum(pragmaVec.size());
  for (MIRPragma *pragma : pragmaVec) {
    OutputPragma(pragma);
  }
}

void BinaryMplExport::OutputClassTypeData(MIRClassType *type) {
  ASSERT(type != nullptr, "MIRClassType is null.");
  OutputType(type->GetParentTyIdx());
  OutputImplementedInterfaces(type->GetInerfaceImplemented());
  OutputInfoIsString(type->GetInfoIsString());
  OutputInfo(type->GetInfo(), type->GetInfoIsString());
  OutputPragmaVec(type->GetPragmVec());
}

void BinaryMplExport::OutputInterfaceTypeData(MIRInterfaceType *type) {
  ASSERT(type != nullptr, "MIRInterfaceType is null.");
  OutputImplementedInterfaces(type->GetParentsTyIdx());
  OutputInfoIsString(type->GetInfoIsString());
  OutputInfo(type->GetInfo(), type->GetInfoIsString());
  OutputPragmaVec(type->GetPragmVec());
}

void BinaryMplExport::Init() {
  gStrMark[GStrIdx(0)] = 0;
  uStrMark[UStrIdx(0)] = 0;
  symMark[nullptr] = 0;
  funcMark[nullptr] = 0;
  for (int32 pti = 0; pti <= static_cast<int32>(PTY_agg); pti++) {
    typMark[GlobalTables::GetTypeTable().GetTypeFromTyIdx(TyIdx(pti))] = pti;
  }
}

void BinaryMplExport::OutputSymbol(MIRSymbol *sym) {
  if (sym == nullptr) {
    WriteNum(0);
    return;
  }

  auto it = symMark.find(sym);
  if (it != symMark.end()) {
    WriteNum(-(it->second));
    return;
  }

  if (sym->GetSKind() != kStFunc) {
    ASSERT(false, "should not be used");
  }

  WriteNum(kBinSymbol);
  WriteNum(sym->GetScopeIdx());
  OutputStr(sym->GetNameStrIdx());
  WriteNum(sym->GetSKind());
  WriteNum(sym->GetStorageClass());
  size_t mark = symMark.size();
  symMark[sym] = mark;
  OutputTypeAttrs(sym->GetAttrs());
  WriteNum(sym->GetIsTmp() ? 1 : 0);
  OutputFunction(sym->GetFunction()->GetPuidx());
  OutputType(sym->GetTyIdx());
}

void BinaryMplExport::OutputFunction(PUIdx puIdx) {
  if (puIdx == 0) {
    WriteNum(0);
    return;
  }
  MIRFunction *func = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(puIdx);
  ASSERT(func != nullptr, "Cannot get MIRFunction.");
  size_t mark = funcMark.size();
  funcMark[func] = mark;
  MIRFunction *savedFunc = mod.CurFunction();
  mod.SetCurFunction(func);

  WriteNum(kBinFunction);
  MIRSymbol *funcSt = GlobalTables::GetGsymTable().GetSymbolFromStidx(func->GetStIdx().Idx());
  CHECK_FATAL(funcSt != nullptr, "can't get symbol! Check it!");
  OutputSymbol(funcSt);
  OutputType(func->GetReturnTyIdx());
  WriteNum(func->GetFuncAttrs().GetAttrFlag());
  WriteNum(func->GetFlag());
  OutputType(func->GetClassTyIdx());
  mod.SetCurFunction(savedFunc);
}

void BinaryMplExport::WriteStrField(uint64 contentIdx) {
  Fixup(contentIdx, buf.size());
  WriteNum(kBinStrStart);
  size_t totalSizeIdx = buf.size();
  ExpandFourBuffSize();  // total size of this field to ~BIN_STR_START
  size_t outStrSizeIdx = buf.size();
  ExpandFourBuffSize();  // size of OutputStr

  int32 size = 0;
  for (const auto &entity : GlobalTables::GetConstPool().GetConstU16StringPool()) {
    MIRSymbol *sym = entity.second;
    if (sym->IsLiteral()) {
      OutputStr(sym->GetNameStrIdx());
      size++;
    }
  }
  Fixup(totalSizeIdx, buf.size() - totalSizeIdx);
  Fixup(outStrSizeIdx, size);
  WriteNum(~kBinStrStart);
}

void BinaryMplExport::WriteTypeField(uint64 contentIdx) {
  Fixup(contentIdx, buf.size());
  WriteNum(kBinTypeStart);
  size_t totalSizeIdx = buf.size();
  ExpandFourBuffSize();  // total size of this field to ~BIN_TYPE_START
  size_t outTypeSizeIdx = buf.size();
  ExpandFourBuffSize();  // size of OutputType
  int32 size = 0;
  for (uint32 tyIdx : mod.GetClassList()) {
    TyIdx curTyidx(tyIdx);
    MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(curTyidx);
    CHECK_FATAL(type != nullptr, "can't get type, check it!");
    if (type->GetKind() == kTypeClass || type->GetKind() == kTypeInterface) {
      MIRStructType *structType = static_cast<MIRStructType*>(type);
      // skip imported class/interface and incomplete types
      if (!structType->IsImported() && !structType->IsIncomplete()) {
        OutputType(curTyidx);
        size++;
      }
    }
  }
  Fixup(totalSizeIdx, buf.size() - totalSizeIdx);
  Fixup(outTypeSizeIdx, size);
  WriteNum(~kBinTypeStart);
}


void BinaryMplExport::WriteContentField(int fieldNum, uint64 *fieldStartP) {
  ASSERT(fieldStartP != nullptr, "fieldStartP is null.");
  WriteNum(kBinContentStart);
  size_t totalSizeIdx = buf.size();
  ExpandFourBuffSize();  // total size of this field to ~BIN_SYM_START

  WriteInt(fieldNum);  // size of Content item

  WriteNum(kBinStrStart);
  fieldStartP[0] = buf.size();
  ExpandFourBuffSize();

  WriteNum(kBinTypeStart);
  fieldStartP[1] = buf.size();
  ExpandFourBuffSize();

  WriteNum(kBinCgStart);
  fieldStartP[2] = buf.size();
  ExpandFourBuffSize();

  Fixup(totalSizeIdx, buf.size() - totalSizeIdx);
  WriteNum(~kBinContentStart);
}

void BinaryMplExport::Export(const std::string &fname) {
  constexpr int kFieldNum = 3;
  uint64 fieldStartPoint[kFieldNum];
  WriteInt(kMpltMagicNumber);
  WriteContentField(kFieldNum, fieldStartPoint);
  WriteStrField(fieldStartPoint[0]);
  WriteTypeField(fieldStartPoint[1]);
  WriteNum(kBinFinish);
  importFileName = fname;
  DumpBuf(fname);
}

void BinaryMplExport::AppendAt(const std::string &name, int32 offset) {
  FILE *f = fopen(name.c_str(), "r+b");
  if (f == nullptr) {
    LogInfo::MapleLogger(kLlErr) << "Error while opening the binary file: " << name << std::endl;
    FATAL(kLncFatal, "Error while creating the binary file: %s\n", name.c_str());
  }
  int seekRet = fseek(f, (long int)offset, SEEK_SET);
  CHECK_FATAL(seekRet == 0, "call fseek failed");
  size_t size = buf.size();
  size_t k = fwrite(&buf[0], sizeof(uint8), size, f);
  fclose(f);
  if (k != size) {
    LogInfo::MapleLogger(kLlErr) << "Error while writing the binary file: " << name << std::endl;
  }
}

void BinaryMplExport::OutputTypePairs(MIRInstantVectorType *type) {
  size_t size = type->GetInstantVec().size();
  WriteNum(size);
  for (TypePair &tpair : type->GetInstantVec()) {
    OutputType(tpair.first);
    OutputType(tpair.second);
  }
}

void BinaryMplExport::OutputTypeAttrs(const TypeAttrs &ta) {
  WriteNum(ta.GetAttrFlag());
  WriteNum(ta.GetAlignValue());
}

void BinaryMplExport::OutputType(const TyIdx &tyIdx) {
  MIRType *ty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  if (tyIdx == 0) {
    WriteNum(0);
    return;
  }
  CHECK_FATAL(ty != nullptr, "if get's nulltype, should have been returned!");
  auto it = typMark.find(ty);
  if (it != typMark.end()) {
    if (ty->GetKind() != kTypeFunction) {
      WriteNum(-(it->second));
      return;
    }
    ++BinaryMplExport::typeMarkOffset;
  } else {
    int64 mark = typMark.size() + BinaryMplExport::typeMarkOffset;
    typMark[ty] = mark;
  }

  auto func = CreateProductFunction<OutputTypeFactory>(ty->GetKind());
  if (func != nullptr) {
    func(ty, this);
  } else {
    ASSERT(false, "Type's kind not yet implemented: %d", ty->GetKind());
  }
}


}  // namespace maple
