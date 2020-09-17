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
#include "mir_symbol.h"
#include <algorithm>
#include <unordered_set>
#include "mir_function.h"
#include "class_init.h"
#include "vtable_analysis.h"
#include "reflection_analysis.h"
#include "printing.h"
#include "native_stub_func.h"
#include "literal_str_name.h"

using namespace NameMangler;

namespace maple {

void MIRSymbol::SetNameStrIdx(const std::string &name) {
  nameStrIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(name);
}

bool MIRSymbol::HasAddrOfValues() {
  return (GetName().find(VTAB_PREFIX_STR) == 0 || GetName().find(ITAB_PREFIX_STR) == 0 ||
          GetName().find(kVtabOffsetTabStr) == 0 || IsClassInitBridge() || IsReflectionInfo() ||
          IsReflectionHashTabBucket() || IsReflectionStrTab() || IsITabConflictInfo() || IsRegJNITab() ||
          IsRegJNIFuncTab() || IsLiteral());
}

bool MIRSymbol::IsLiteral() const {
  return (GetName().find(kConstString) == 0);
}

bool MIRSymbol::IsLiteralPtr() const {
  return (GetName().find(kConstStringPtr) == 0);
}

MIRType *MIRSymbol::GetType() const {
  return GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
}

const std::string &MIRSymbol::GetName() const {
  return GlobalTables::GetStrTable().GetStringFromStrIdx(nameStrIdx);
}

bool MIRSymbol::PointsToConstString() const {
  MIRType *origType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  if (origType->GetKind() == kTypePointer) {
    return static_cast<MIRPtrType*>(origType)->PointsToConstString();
  }
  return false;
}

bool MIRSymbol::IsConstString() const {
  return typeAttrs.GetAttr(ATTR_static) && typeAttrs.GetAttr(ATTR_final) && PointsToConstString();
}

bool MIRSymbol::IsReflectionStrTab() const {
  return ((GetName().find(kReflectionStrtabPrefixStr) == 0) ||
          (GetName().find(kReflectionStartHotStrtabPrefixStr) == 0) ||
          (GetName().find(kReflectionBothHotStrTabPrefixStr) == 0) ||
          (GetName().find(kReflectionRunHotStrtabPrefixStr) == 0) ||
          (GetName().find(kReflectionNoEmitStrtabPrefixStr) == 0));
}

bool MIRSymbol::IsRegJNITab() const {
  return (GetName().find(kRegJNITabPrefixStr) == 0);
}

bool MIRSymbol::IsRegJNIFuncTab() const {
  return (GetName().find(kRegJNIFuncTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidTab() const {
  return (GetName().find(kMuidPrefixStr) == 0);
}

bool MIRSymbol::IsCodeLayoutInfo() const {
  return (GetName().find(kFunctionLayoutStr) == 0);
}

std::string MIRSymbol::GetMuidTabName() {
  if (!IsMuidTab()) {
    return "";
  }
  size_t idx = GetName().find(kFileNameSplitterStr);
  return ((idx != std::string::npos) ? GetName().substr(0, idx) : "");
}

bool MIRSymbol::IsMuidFuncDefTab() const {
  return (GetName().find(kMuidFuncDefTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidFuncDefOrigTab() const {
  return (GetName().find(kMuidFuncDefOrigTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidFuncInfTab() const {
  return (GetName().find(kMuidFuncInfTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidFuncUndefTab() const {
  return (GetName().find(kMuidFuncUndefTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidDataDefTab() const {
  return (GetName().find(kMuidDataDefTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidDataDefOrigTab() const {
  return (GetName().find(kMuidDataDefOrigTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidDataUndefTab() const {
  return (GetName().find(kMuidDataUndefTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidFuncDefMuidTab() const {
  return (GetName().find(kMuidFuncDefMuidTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidFuncUndefMuidTab() const {
  return (GetName().find(kMuidFuncUndefMuidTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidDataDefMuidTab() const {
  return (GetName().find(kMuidDataDefMuidTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidDataUndefMuidTab() const {
  return (GetName().find(kMuidDataUndefMuidTabPrefixStr) == 0);
}

bool MIRSymbol::IsMuidRangeTab() const {
  return (GetName().find(kMuidRangeTabPrefixStr) == 0);
}

bool MIRSymbol::IsClassInitBridge() {
  return (GetName().find(CLASS_INIT_BRIDGE_PREFIX_STR) == 0);
}

bool MIRSymbol::IsReflectionHashTabBucket() const {
  return (GetName().compare(0, strlen(kMuidClassMetadataBucketPrefixStr), kMuidClassMetadataBucketPrefixStr) == 0);
}

bool MIRSymbol::IsReflectionInfo() {
  return (IsReflectionClassInfo() || IsReflectionClassInfoRO() || IsReflectionFieldsInfo() ||
          IsReflectionFieldsInfoCompact() || IsReflectionMethodsInfo() || IsReflectionPrimitiveClassInfo() ||
          IsReflectionSuperclassInfo() || IsReflectionMethodsInfoCompact());
}

bool MIRSymbol::IsReflectionFieldsInfo() const {
  return (GetName().find(kFieldsInfoPrefixStr) == 0);
}

bool MIRSymbol::IsReflectionFieldsInfoCompact() const {
  return (GetName().find(kFieldsInfoCompactPrefixStr) == 0);
}

bool MIRSymbol::IsReflectionSuperclassInfo() {
  return (GetName().find(SUPERCLASSINFO_PREFIX_STR) == 0);
}

bool MIRSymbol::IsReflectionClassInfo() {
  return (GetName().find(CLASSINFO_PREFIX_STR) == 0);
}

bool MIRSymbol::IsReflectionArrayClassInfo() const {
  return (GetName().find(kArrayClassInfoPrefixStr) == 0);
}

bool MIRSymbol::IsReflectionClassInfoPtr() const {
  return (GetName().find(kClassINfoPtrPrefixStr) == 0);
}

bool MIRSymbol::IsReflectionClassInfoRO() {
  return (GetName().find(CLASSINFO_RO_PREFIX_STR) == 0);
}

bool MIRSymbol::IsITabConflictInfo() {
  return (GetName().find(ITAB_CONFLICT_PREFIX_STR) == 0);
}

bool MIRSymbol::IsVTabInfo() {
  return (GetName().find(VTAB_PREFIX_STR) == 0);
}

bool MIRSymbol::IsITabInfo() {
  return (GetName().find(ITAB_PREFIX_STR) == 0);
}

bool MIRSymbol::IsReflectionPrimitiveClassInfo() {
  return (GetName().find(PRIMITIVECLASSINFO_PREFIX_STR) == 0);
}

bool MIRSymbol::IsReflectionMethodsInfo() const {
  return (GetName().find(kMethodsInfoPrefixStr) == 0);
}

bool MIRSymbol::IsReflectionMethodsInfoCompact() const {
  return (GetName().find(kMethodsInfoCompactPrefixStr) == 0);
}

bool MIRSymbol::IsPrimordialObject() {
  return IsReflectionClassInfo() || IsReflectionPrimitiveClassInfo();
}

bool MIRSymbol::IsGctibSym() {
  return (GetName().find(GCTIB_PREFIX_STR) == 0);
}

// [Note]
// Some symbols are ignored by reference counting as they represent objects not managed by us. These include
// string-based exact comparison for "current_vptr", "vtabptr", "itabptr", "funcptr", "env_ptr", "retvar_stubfunc".
GStrIdx MIRSymbol::reflectClassNameIdx;
GStrIdx MIRSymbol::reflectMethodNameIdx;
GStrIdx MIRSymbol::reflectFieldNameIdx;
bool MIRSymbol::IgnoreRC() {
  if (isDeleted || GetAttr(ATTR_rcunowned)) {
    return true;
  }
  const std::string &name = GetName();
  // ignore %current_vptr, %vtabptr, %itabptr, %funcptr, %env_ptr
  if (name == "current_vptr" || name == "vtabptr" || name == "itabptr" || name == "funcptr" || name == "env_ptr" ||
      name == "retvar_stubfunc" || name == "_dummy_stub_object_retval") {
    return true;
  }
  if (IsReflectionInfo() || IsRegJNITab() || IsRegJNIFuncTab()) {
    return true;
  }
  MIRType *type = GetType();
  // only consider reference
  if (type == nullptr || type->GetPrimType() != PTY_ref) {
    return true;
  }
  if ((type->GetKind() == kTypeScalar) && (name != "__mapleRC__")) {
    return true;
  }
  // ignore ptr to types Ljava_2Flang_2FClass_3B,
  // Ljava_2Flang_2Freflect_2FMethod_3B
  MIRPtrType *ptype = static_cast<MIRPtrType*>(type);
  GStrIdx strIdx = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptype->GetPointedTyIdx())->GetNameStrIdx();
  if (reflectClassNameIdx == 0) {
    reflectClassNameIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(
        NameMangler::GetInternalNameLiteral("Ljava_2Flang_2FClass_3B"));
  }
  return strIdx == reflectClassNameIdx;
}

void MIRSymbol::Dump(bool isLocal, int32 indent, bool suppressinit) const {
  if (GetStorageClass() == kScUnused) {
    return;
  }
  if (GetStorageClass() == kScFormal) {
    return;
  }
  // no need for symbols of extern functions, only need declarations
  if (GetStorageClass() == kScExtern && sKind == kStFunc) {
    return;
  }
  if (GetTyIdx().GetIdx() >= GlobalTables::GetTypeTable().GetTypeTable().size()) {
    FATAL(kLncFatal, "valid maple_ir with illegal type");
  }
  if (GetStorageClass() == kScText && GetFunction() != nullptr) {
    // without body
    GetFunction()->Dump(true);
    return;
  }
  const char *ids = isLocal ? "%" : "$";
  PrintIndentation(indent);
  if (sKind == kStJavaClass) {
    LogInfo::MapleLogger() << "javaclass ";
  } else if (sKind == kStJavaInterface) {
    LogInfo::MapleLogger() << "javainterface ";
  } else if (isTmp) {
    LogInfo::MapleLogger() << "tempvar ";
  } else {
    LogInfo::MapleLogger() << "var ";
  }
  LogInfo::MapleLogger() << ids << GetName() << " ";
  if (GetStorageClass() == kScFstatic) {
    LogInfo::MapleLogger() << "fstatic ";
  } else if (GetStorageClass() == kScPstatic) {
    LogInfo::MapleLogger() << "pstatic ";
  } else if (GetStorageClass() == kScExtern) {
    LogInfo::MapleLogger() << "extern ";
  }
  if (GetTyIdx() != 0) {
    GlobalTables::GetTypeTable().GetTypeFromTyIdx(GetTyIdx())->Dump(indent + 1);
  }
  typeAttrs.DumpAttributes();
  if (sKind == kStJavaClass || sKind == kStJavaInterface || GetStorageClass() == kScTypeInfoName ||
      GetStorageClass() == kScTypeInfo || GetStorageClass() == kScTypeCxxAbi) {
    LogInfo::MapleLogger() << std::endl;
    return;
  }
  if (IsConst() && !suppressinit && !(IsLiteral() && GetStorageClass() == kScExtern)) {
    LogInfo::MapleLogger() << " = ";
    GetKonst()->Dump();
  }
  LogInfo::MapleLogger() << std::endl;
}

void MIRSymbol::DumpAsLiteralVar(int32 indent) {
  if (IsLiteral()) {
    LogInfo::MapleLogger() << GetName();
  }
}

void MIRSymbolTable::Dump(bool isLocal, int32 indent, bool printDeleted) const {
  size_t size = symbolTable.size();
  for (size_t i = 0; i < size; i++) {
    MIRSymbol *symbol = symbolTable[i];
    if (symbol == nullptr) {
      continue;
    }
    if (!printDeleted && symbol->IsDeleted()) {
      continue;
    }
    symbol->Dump(isLocal, indent);
  }
}

LabelIdx MIRLabelTable::CreateLabelWithPrefix(char c) {
  LabelIdx labidx = labelTable.size();
  std::ostringstream labelNameStream;
  labelNameStream << "@" << c << labidx;
  std::string lname = labelNameStream.str();
  GStrIdx nameIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lname);
  labelTable.push_back(nameIdx);
  strIdxToLabIdxMap[nameIdx] = labidx;
  return labidx;
}

const std::string &MIRLabelTable::GetName(LabelIdx labelIdx) const {
  CHECK_FATAL(labelIdx < labelTable.size(), "index out of range in MIRLabelTable::GetName");
  return GlobalTables::GetStrTable().GetStringFromStrIdx(labelTable[labelIdx]);
}

bool MIRLabelTable::AddToStringLabelMap(LabelIdx lidx) {
  CHECK_FATAL(lidx < labelTable.size(), "index out of range in MIRLabelTable::AddToStringLabelMap");
  if (labelTable[lidx] == 0) {
    // generate a label name based on lab_idx
    std::ostringstream labelNameStream;
    labelNameStream << "@" << lidx;
    std::string lname;
    lname = labelNameStream.str();
    labelTable[lidx] = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lname);
  }
  GStrIdx strIdx = labelTable[lidx];
  strIdxToLabIdxMap[strIdx] = lidx;
  return true;
}

void MIRPregTable::DumpRef(int32 indent) {
  MapleVector<MIRPreg*> &pRegTable = pregTable;
  for (size_t i = 1; i < pRegTable.size(); i++) {
    MIRPreg *mirPReg = pRegTable[i];
    if (mirPReg->GetPrimType() != PTY_ref) {
      continue;
    }
    if (mirPReg->GetMIRType() == nullptr) {
      continue;
    }
    PrintIndentation(indent);
    LogInfo::MapleLogger() << "reg ";
    LogInfo::MapleLogger() << "%" << mirPReg->GetPregNo();
    LogInfo::MapleLogger() << " ";
    mirPReg->GetMIRType()->Dump(0);
    LogInfo::MapleLogger() << " " << (mirPReg->NeedRC() ? 1 : 0);
    LogInfo::MapleLogger() << "\n";
  }
}

}  // namespace maple
