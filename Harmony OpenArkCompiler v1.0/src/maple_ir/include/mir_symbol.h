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
#ifndef MAPLE_IR_INCLUDE_MIR_SYMBOL_H
#define MAPLE_IR_INCLUDE_MIR_SYMBOL_H
#include <sstream>
#include "mir_const.h"
#include "mir_preg.h"

constexpr int kScopeLocal = 2;   // the default scope level for function variables
constexpr int kScopeGlobal = 1;  // the scope level for global variables

namespace maple {
enum MIRSymKind {
  kStInvalid,
  kStVar,
  kStFunc,
  kStConst,
  kStJavaClass,
  kStJavaInterface,
  kStPreg,
};

enum MIRStorageClass : std::uint8_t {
  kScInvalid,
  kScAuto,
  kScAliased,
  kScFormal,
  kScExtern,
  kScGlobal,
  kScPstatic,  // PU-static
  kScFstatic,  // file-static
  kScText,
  kScTypeInfo,      // used for eh type st
  kScTypeInfoName,  // used for eh type st name
  kScTypeCxxAbi,    // used for eh inherited from c++ __cxxabiv1
  kScUnused
};

// to represent a single symbol
class MIRSymbol {
 public:
  union SymbolType {  // a symbol can either be a const or a function or a preg which currently used for formal
    MIRConst *konst;
    MIRFunction *mirFunc;
    MIRPreg *preg;  // the MIRSymKind must be kStPreg
  };

  // Please keep order of the fields, avoid paddings.
 private:
  TyIdx tyIdx;
  TyIdx inferredTyIdx;
  MIRStorageClass storageClass;
  MIRSymKind sKind;
  bool isTmp;
  bool needForwDecl;  // addrof of this symbol used in initialization, NOT serialized
  bool isDeleted;     // tell if it is deleted, NOT serialized
  bool instrumented;  // a local ref pointer instrumented by RC opt, NOT serialized
  bool isImported;
  StIdx stIdx;
  TypeAttrs typeAttrs;
  GStrIdx nameStrIdx;
  SymbolType value;
  static GStrIdx reflectClassNameIdx;
  static GStrIdx reflectMethodNameIdx;
  static GStrIdx reflectFieldNameIdx;

 public:
  MIRSymbol()
      : tyIdx(0),
        inferredTyIdx(kInitTyIdx),
        storageClass(kScInvalid),
        sKind(kStInvalid),
        isTmp(false),
        needForwDecl(false),
        isDeleted(false),
        instrumented(false),
        isImported(false),
        stIdx(0, 0),
        nameStrIdx(0),
        value({ nullptr }) {
  }
  MIRSymbol(uint32 idx, uint8 scp)
      : tyIdx(0),
        inferredTyIdx(kInitTyIdx),
        storageClass(kScInvalid),
        sKind(kStInvalid),
        isTmp(false),
        needForwDecl(false),
        isDeleted(false),
        instrumented(false),
        isImported(false),
        stIdx(scp, idx),
        nameStrIdx(0),
        value({ nullptr }) {
  }
  ~MIRSymbol() {}

  void SetIsTmp(bool temp) {
    isTmp = temp;
  }

  bool GetIsTmp() const {
    return isTmp;
  }

  void SetNeedForwDecl() {
    needForwDecl = true;
  }

  bool IsNeedForwDecl() const {
    return needForwDecl;
  }

  void SetInstrumented() {
    instrumented = true;
  }

  bool IsInstrumented() const {
    return instrumented;
  }

  void SetIsImported(bool imported) {
    isImported = imported;
  }

  bool GetIsImported() {
    return isImported;
  }

  void SetTyIdx(TyIdx tyIdx) {
    this->tyIdx = tyIdx;
  }

  const TyIdx GetTyIdx() const {
    return tyIdx;
  }

  void SetInferredTyIdx(TyIdx i) {
    inferredTyIdx = i;
  }

  const TyIdx &GetInferredTyIdx() const {
    return inferredTyIdx;
  }

  void SetStIdx(StIdx stIdx) {
    this->stIdx = stIdx;
  }

  const StIdx &GetStIdx() const {
    return stIdx;
  }

  void SetSKind(MIRSymKind m) {
    sKind = m;
  }

  MIRSymKind GetSKind() const {
    return sKind;
  }

  uint32 GetScopeIdx() const {
    return stIdx.Scope();
  }

  uint32 GetStIndex() const {
    return stIdx.Idx();
  }

  bool IsLocal() const {
    return stIdx.Islocal();
  }

  bool IsGlobal() const {
    return stIdx.IsGlobal();
  }

  const TypeAttrs &GetAttrs() const {
    return typeAttrs;
  }

  TypeAttrs &GetAttrs() {
    return typeAttrs;
  }

  void SetAttrs(TypeAttrs attr) {
    typeAttrs = attr;
  }

  // AddAttrs adds more attributes instead of overrides the current one
  void AddAttrs(TypeAttrs attr) {
    typeAttrs.SetAttrFlag(typeAttrs.GetAttrFlag() | attr.GetAttrFlag());
  }

  bool GetAttr(AttrKind x) const {
    return typeAttrs.GetAttr(x);
  }

  void SetAttr(AttrKind x) {
    typeAttrs.SetAttr(x);
  }

  void ResetAttr(AttrKind x) {
    typeAttrs.ResetAttr(x);
  }

  bool IsVolatile() const {
    return typeAttrs.GetAttr(ATTR_volatile);
  }

  bool IsStatic() const {
    return typeAttrs.GetAttr(ATTR_static);
  }

  bool IsFinal() const {
    return (typeAttrs.GetAttr(ATTR_final) || typeAttrs.GetAttr(ATTR_readonly)) || IsLiteral() || IsLiteralPtr();
  }

  bool IsWeak() const {
    return typeAttrs.GetAttr(ATTR_weak);
  }

  bool IsPrivate() const {
    return typeAttrs.GetAttr(ATTR_private);
  }

  bool IsRefType() const {
    return typeAttrs.GetAttr(ATTR_localrefvar);
  }

  void SetNameStrIdx(const GStrIdx &stridx) {
    nameStrIdx = stridx;
  }

  void SetNameStrIdx(const std::string &name);

  GStrIdx GetNameStrIdx() const {
    return nameStrIdx;
  }

  MIRStorageClass GetStorageClass() const {
    return storageClass;
  }

  void SetStorageClass(MIRStorageClass cl) {
    storageClass = cl;
  }

  bool IsReadOnly() const {
    return (kScFstatic == storageClass && kStConst == sKind);
  }

  bool IsConst() const {
    return sKind == kStConst || (sKind == kStVar && value.konst != nullptr);
  }

  MIRType *GetType() const;

  const std::string &GetName() const;

  MIRConst *GetKonst() const {
    ASSERT((sKind == kStConst || sKind == kStVar), "must be const symbol");
    return value.konst;
  }

  void SetKonst(MIRConst *mirconst) {
    ASSERT((sKind == kStConst || sKind == kStVar), "must be const symbol");
    value.konst = mirconst;
  }

  void SetIsDeleted() {
    isDeleted = true;
  }

  void ResetIsDeleted() {
    isDeleted = false;
  }

  bool IsDeleted() const {
    return isDeleted;
  }

  bool IsPreg() const {
    return sKind == kStPreg;
  }

  bool IsJavaClassInterface() const {
    return sKind == kStJavaClass || sKind == kStJavaInterface;
  }

  SymbolType GetValue() const {
    return value;
  }

  void SetValue(SymbolType value) {
    this->value = value;
  }

  MIRPreg *GetPreg() {
    ASSERT(IsPreg(), "must be Preg");
    return value.preg;
  }

  const MIRPreg *GetPreg() const {
    CHECK_FATAL(IsPreg(), "must be Preg");
    return value.preg;
  }

  void SetPreg(MIRPreg *preg) {
    CHECK_FATAL(IsPreg(), "must be Preg");
    value.preg = preg;
  }

  void SetLocalRefVar() {
    SetAttr(ATTR_localrefvar);
  }

  void ResetLocalRefVar() {
    ResetAttr(ATTR_localrefvar);
  }

  MIRFunction *GetFunction() const {
    ASSERT(sKind == kStFunc, "must be function symbol");
    return value.mirFunc;
  }

  void SetFunction(MIRFunction *func) {
    ASSERT(sKind == kStFunc, "must be function symbol");
    value.mirFunc = func;
  }

  bool IsEhIndex() const {
    return GetName().compare("__eh_index__") == 0;
  }

  bool HasAddrOfValues();
  bool IsLiteral() const;
  bool IsLiteralPtr() const;
  bool PointsToConstString() const;
  bool IsConstString() const;
  bool IsClassInitBridge();
  bool IsReflectionStrTab() const;
  bool IsReflectionHashTabBucket() const;
  bool IsReflectionInfo();
  bool IsReflectionFieldsInfo() const;
  bool IsReflectionFieldsInfoCompact() const;
  bool IsReflectionSuperclassInfo();
  bool IsReflectionClassInfo();
  bool IsReflectionArrayClassInfo() const;
  bool IsReflectionClassInfoPtr() const;
  bool IsReflectionClassInfoRO();
  bool IsITabConflictInfo();
  bool IsVTabInfo();
  bool IsITabInfo();
  bool IsReflectionPrimitiveClassInfo();
  bool IsReflectionMethodsInfo() const;
  bool IsReflectionMethodsInfoCompact() const;
  bool IsRegJNITab() const;
  bool IsRegJNIFuncTab() const;
  bool IsMuidTab() const;
  bool IsCodeLayoutInfo() const;
  std::string GetMuidTabName();
  bool IsMuidFuncDefTab() const;
  bool IsMuidFuncDefOrigTab() const;
  bool IsMuidFuncInfTab() const;
  bool IsMuidFuncUndefTab() const;
  bool IsMuidDataDefTab() const;
  bool IsMuidDataDefOrigTab() const;
  bool IsMuidDataUndefTab() const;
  bool IsMuidFuncDefMuidTab() const;
  bool IsMuidFuncUndefMuidTab() const;
  bool IsMuidDataDefMuidTab() const;
  bool IsMuidDataUndefMuidTab() const;
  bool IsMuidRangeTab() const;
  bool IsGctibSym();
  bool IsPrimordialObject();
  bool IgnoreRC();
  void Dump(bool isLocal, int32 indent, bool suppressinit = false) const;
  void DumpAsLiteralVar(int32 indent);
  bool operator==(const MIRSymbol &msym) const {
    return nameStrIdx == msym.nameStrIdx;
  }

  bool operator!=(const MIRSymbol &msym) const {
    return nameStrIdx != msym.nameStrIdx;
  }

  bool operator<(const MIRSymbol &msym) const {
    return nameStrIdx < msym.nameStrIdx;
  }
};

class MIRSymbolTable {
 public:
  explicit MIRSymbolTable(MapleAllocator *allocator)
      : mAllocator(allocator), strIdxToStIdxMap(mAllocator->Adapter()), symbolTable(mAllocator->Adapter()) {
    symbolTable.push_back(static_cast<MIRSymbol*>(nullptr));
  }

  ~MIRSymbolTable() {}

  bool IsValidIdx(uint32 idx) const {
    return idx < symbolTable.size();
  }

  MIRSymbol *GetSymbolFromStIdx(uint32 idx, bool checkFirst = false) const {
    if (checkFirst && idx >= symbolTable.size()) {
      return nullptr;
    }
    CHECK_FATAL(IsValidIdx(idx), "symbol table index out of range");
    return symbolTable[idx];
  }

  MIRSymbol *CreateSymbol(uint8 scopeID) {
    MIRSymbol *st = mAllocator->GetMemPool()->New<MIRSymbol>(symbolTable.size(), scopeID);
    symbolTable.push_back(st);
    return st;
  }

  // add sym from other symbol table, happens in inline
  bool AddStOutside(MIRSymbol *sym) {
    sym->SetStIdx(StIdx(sym->GetScopeIdx(), symbolTable.size()));
    symbolTable.push_back(sym);
    return AddToStringSymbolMap(sym);
  }

  bool AddToStringSymbolMap(const MIRSymbol *st) {
    GStrIdx strIdx = st->GetNameStrIdx();
    if (strIdxToStIdxMap[strIdx].FullIdx() != 0) {
      return false;
    }
    strIdxToStIdxMap[strIdx] = st->GetStIdx();
    return true;
  }

  StIdx GetStIdxFromStrIdx(GStrIdx idx) const {
    auto it = strIdxToStIdxMap.find(idx);
    if (it == strIdxToStIdxMap.end()) {
      return StIdx();
    }
    return it->second;
  }

  MIRSymbol *GetSymbolFromStrIdx(GStrIdx idx, bool checkFirst = false) const {
    return GetSymbolFromStIdx(GetStIdxFromStrIdx(idx).Idx(), checkFirst);
  }

  void Dump(bool isLocal, int32 indent = 0, bool printDeleted = false) const;
  size_t GetSymbolTableSize() const {
    return symbolTable.size();
  }

  void Clear() {
    symbolTable.clear();
  }

 private:
  MapleAllocator *mAllocator;
  // hash table mapping string index to st index
  MapleMap<GStrIdx, StIdx> strIdxToStIdxMap;
  // map symbol idx to symbol node
  MapleVector<MIRSymbol*> symbolTable;
};

class MIRLabelTable {
 public:
  explicit MIRLabelTable(MapleAllocator *allocator)
      : mAllocator(allocator),
        strIdxToLabIdxMap(std::less<GStrIdx>(), mAllocator->Adapter()),
        labelTable(mAllocator->Adapter()) {
    labelTable.push_back(GStrIdx(kDummyLabel));  // push dummy label index 0
  }

  ~MIRLabelTable() {}

  LabelIdx CreateLabel() {
    LabelIdx labelIdx = labelTable.size();
    labelTable.push_back(GStrIdx(0));  // insert dummy global string index for anonymous label
    return labelIdx;
  }

  LabelIdx CreateLabelWithPrefix(char c);

  LabelIdx AddLabel(GStrIdx nameIdx) {
    LabelIdx labelIdx = labelTable.size();
    labelTable.push_back(nameIdx);
    strIdxToLabIdxMap[nameIdx] = labelIdx;
    return labelIdx;
  }

  LabelIdx GetStIdxFromStrIdx(GStrIdx idx) const {
    auto it = strIdxToLabIdxMap.find(idx);
    if (it == strIdxToLabIdxMap.end()) {
      return LabelIdx();
    }
    return it->second;
  }

  bool AddToStringLabelMap(LabelIdx lidx);
  size_t GetLabelTableSize() const {
    return labelTable.size();
  }

  const std::string &GetName(LabelIdx labelIdx) const;

  size_t Size() const {
    return labelTable.size();
  }

  static uint32 GetDummyLabel() {
    return kDummyLabel;
  }

  GStrIdx GetSymbolFromStIdx(LabelIdx idx) const {
    CHECK_FATAL(idx < labelTable.size(), "label table index out of range");
    return labelTable[idx];
  }

  void SetSymbolFromStIdx(LabelIdx idx, GStrIdx strIdx) {
    CHECK_FATAL(idx < labelTable.size(), "label table index out of range");
    labelTable[idx] = strIdx;
  }

 private:
  static constexpr uint32 kDummyLabel = 0;
  MapleAllocator *mAllocator;
  MapleMap<GStrIdx, LabelIdx> strIdxToLabIdxMap;
  MapleVector<GStrIdx> labelTable;  // map label idx to label name
};

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_MIR_SYMBOL_H
