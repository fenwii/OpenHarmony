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
#ifndef MAPLE_IR_INCLUDE_GLOBAL_TABLES_H
#define MAPLE_IR_INCLUDE_GLOBAL_TABLES_H
#include <iostream>
#include <memory>
#include <functional>
#include "mempool.h"
#include "mempool_allocator.h"
#include "types_def.h"
#include "prim_types.h"
#include "mir_module.h"
#include "name_mangler.h"
#include "mir_type.h"

namespace maple {
class MIRType;
class TypeAttrs;
class FieldAttrs;
class MIRStructType;
class MIRArrayType;
using TyIdxFieldAttrPair = std::pair<TyIdx, FieldAttrs>;
using FieldPair = std::pair<GStrIdx, TyIdxFieldAttrPair>;
using FieldVector = std::vector<FieldPair>;

// to facilitate the use of unordered_map
class TyIdxHash {
 public:
  std::size_t operator()(const TyIdx &tyIdx) const {
    return std::hash<uint32>{}(tyIdx.GetIdx());
  }
};

// to facilitate the use of unordered_map
class GStrIdxHash {
 public:
  std::size_t operator()(const GStrIdx &gStrIdx) const {
    return std::hash<uint32>{}(gStrIdx.GetIdx());
  }
};

// to facilitate the use of unordered_map
class UStrIdxHash {
 public:
  std::size_t operator()(const UStrIdx &uStrIdx) const {
    return std::hash<uint32>{}(uStrIdx.GetIdx());
  }
};

class TypeTable {
 private:
  using MIRTypePtr = MIRType*;
  struct Hash {
    uint32 operator()(const MIRTypePtr &ty) const {
      return ty->GetHashIndex();
    }
  };

  struct Equal {
    uint32 operator()(const MIRTypePtr &tx, const MIRTypePtr &ty) const {
      return tx->EqualTo(*ty);
    }
  };

  std::unordered_set<MIRTypePtr, Hash, Equal> typeHashTable;

 public:
  static MIRType *voidPtrType;

 public:
  TypeTable();
  TypeTable(const TypeTable&) = delete;
  TypeTable &operator=(const TypeTable&) = delete;
  ~TypeTable();
  MIRType *CreateMirType(uint32 ti) const;
  void PutToHashTable(MIRType *mirtype);

  std::vector<MIRType*> &GetTypeTable() {
    return typeTable;
  }

  MIRType *GetTypeFromTyIdx(TyIdx tyIdx) const {
    ASSERT(tyIdx.GetIdx() < typeTable.size(), "array index out of range");
    return typeTable.at(tyIdx.GetIdx());
  }

  MIRType *GetTypeFromTyIdx(uint32 index) const {
    ASSERT(index < typeTable.size(), "array index out of range");
    return typeTable.at(index);
  }

  PrimType GetPrimTypeFromTyIdx(TyIdx tyIdx) const {
    ASSERT(tyIdx.GetIdx() < typeTable.size(), "array index out of range");
    return typeTable.at(tyIdx.GetIdx())->GetPrimType();
  }

  void SetTypeWithTyIdx(TyIdx tyIdx, MIRType *type) {
    ASSERT(tyIdx.GetIdx() < typeTable.size(), "array index out of range");
    typeTable.at(tyIdx.GetIdx()) = type;
  }

  TyIdx GetOrCreateMIRType(MIRType *ptype);

  uint32 GetTypeTableSize(void) const {
    return typeTable.size();
  }

  // Get primtive types.
  MIRType *GetPrimType(PrimType ptyp) const {
    ASSERT(ptyp < typeTable.size(), "array index out of range");
    return typeTable.at(ptyp);
  }

  MIRType *GetFloat() const {
    ASSERT(PTY_f32 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_f32);
  }

  MIRType *GetDouble() const {
    ASSERT(PTY_f64 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_f64);
  }

  MIRType *GetFloat128() const {
    ASSERT(PTY_f128 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_f128);
  }

  MIRType *GetUInt1() const {
    ASSERT(PTY_u1 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_u1);
  }

  MIRType *GetUInt8() const {
    ASSERT(PTY_u8 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_u8);
  }

  MIRType *GetInt8() const {
    ASSERT(PTY_i8 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_i8);
  }

  MIRType *GetUInt16() const {
    ASSERT(PTY_u16 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_u16);
  }

  MIRType *GetInt16() const {
    ASSERT(PTY_i16 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_i16);
  }

  MIRType *GetInt32() const {
    ASSERT(PTY_i32 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_i32);
  }

  MIRType *GetUInt32() const {
    ASSERT(PTY_u32 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_u32);
  }

  MIRType *GetInt64() const {
    ASSERT(PTY_i64 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_i64);
  }

  MIRType *GetUInt64() const {
    ASSERT(PTY_u64 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_u64);
  }

  MIRType *GetPtr() const {
    ASSERT(PTY_ptr < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_ptr);
  }

#ifdef USE_32BIT_REF
  MIRType *GetCompactPtr() const {
    ASSERT(PTY_u32 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_u32);
  }

#else
  MIRType *GetCompactPtr() const {
    ASSERT(PTY_u64 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_u64);
  }

#endif
  MIRType *GetRef() const {
    ASSERT(PTY_ref < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_ref);
  }

  MIRType *GetAddr32() const {
    ASSERT(PTY_a32 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_a32);
  }

  MIRType *GetAddr64() const {
    ASSERT(PTY_a64 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_a64);
  }

  MIRType *GetVoid() const {
    ASSERT(PTY_void < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_void);
  }

  MIRType *GetDynundef() const {
    ASSERT(PTY_dynundef < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_dynundef);
  }

#ifdef DYNAMICLANG
  MIRType *GetDynany() const {
    ASSERT(PTY_dynany < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_dynany);
  }

  MIRType *GetDyni32() const {
    ASSERT(PTY_dyni32 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_dyni32);
  }

  MIRType *GetDynf64() const {
    ASSERT(PTY_dynf64 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_dynf64);
  }

  MIRType *GetDynf32() const {
    ASSERT(PTY_dynf32 < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_dynf32);
  }

  MIRType *GetDynstr() const {
    ASSERT(PTY_dynstr < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_dynstr);
  }

  MIRType *GetDynobj() const {
    ASSERT(PTY_dynobj < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_dynobj);
  }

  MIRType *GetDynbool() const {
    ASSERT(PTY_dynbool < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_dynbool);
  }

#endif
  MIRType *GetUnknown() const {
    ASSERT(PTY_unknown < typeTable.size(), "array index out of range");
    return typeTable.at(PTY_unknown);
  }

  // Get or Create derived types.
  MIRType *GetOrCreatePointerType(TyIdx pointedTyIdx, PrimType pty = PTY_ptr);
  MIRType *GetOrCreatePointerType(const MIRType *pointTo, PrimType pty = PTY_ptr);
  MIRType *GetPointedTypeIfApplicable(MIRType *type) const;
  MIRType *GetVoidPtr() const {
    ASSERT(voidPtrType != nullptr, "voidPtrType should not be null");
    return voidPtrType;
  }

  MIRArrayType *GetOrCreateArrayType(const MIRType *elem, uint8 dim, const uint32 *sizeArray);
  MIRArrayType *GetOrCreateArrayType(const MIRType *elem, uint32 size);  // For one dimention array
  MIRType *GetOrCreateFarrayType(const MIRType *elem);
  MIRType *GetOrCreateJarrayType(const MIRType *elem);
  MIRType *GetOrCreateFunctionType(MIRModule *module, TyIdx, const std::vector<TyIdx> &, const std::vector<TypeAttrs> &,
                                   bool isVarg = false, bool isSimpCreate = false);
  MIRType *GetOrCreateStructType(const char *name, const FieldVector &fields, const FieldVector &prntFields,
                                 MIRModule *module) {
    return GetOrCreateStructOrUnion(name, fields, prntFields, module);
  }

  MIRType *GetOrCreateUnionType(const char *name, const FieldVector &fields, const FieldVector &parentFields,
                                MIRModule *module) {
    return GetOrCreateStructOrUnion(name, fields, parentFields, module, false);
  }

  MIRType *GetOrCreateClassType(const char *name, MIRModule *module) {
    return GetOrCreateClassOrInterface(name, module, true);
  }

  MIRType *GetOrCreateInterfaceType(const char *name, MIRModule *module) {
    return GetOrCreateClassOrInterface(name, module, false);
  }

  void PushIntoFieldVector(FieldVector *fields, const char *name, MIRType *type);
  void AddFieldToStructType(MIRStructType *structType, const char *fieldName, MIRType *fieldType);

 private:
  std::vector<MIRType*> typeTable;

 private:
  MIRType *CreateType(MIRType *oldType);
  MIRType *GetOrCreateStructOrUnion(const char *name, const FieldVector &fields, const FieldVector &prntFields,
                                    MIRModule *module, bool forStruct = true);
  MIRType *GetOrCreateClassOrInterface(const char *name, MIRModule *module, bool forClass);
};

class StrPtrHash {
 public:
  size_t operator()(const std::string *str) const {
    return std::hash<std::string>{}(*str);
  }

  size_t operator()(const std::u16string *str) const {
    return std::hash<std::u16string>{}(*str);
  }
};

class StrPtrEqual {
 public:
  bool operator()(const std::string *str1, const std::string *str2) const {
    return *str1 == *str2;
  }

  bool operator()(const std::u16string *str1, const std::u16string *str2) const {
    return *str1 == *str2;
  }
};

// T can be std::string or std::u16string
// U can be GStrIdx, UStrIdx_t, or u16stridx_t
template <typename T, typename U>  // T can be std::string or std::u16string
class StringTable {
 public:
  StringTable &operator = (const StringTable &) = delete;
  StringTable(const StringTable &) = delete;
  StringTable() = default;

  void Init() {
    // initialize 0th entry of stringTable with an empty string
    T *ptr = new (std::nothrow) T;
    CHECK_FATAL(ptr != nullptr, "null ptr check");
    stringTable.push_back(ptr);
  }

  ~StringTable() {
    stringTableMap.clear();
    for (auto it : stringTable) {
      delete it;
    }
  }

  U GetStrIdxFromName(const T &str) const {
    auto it = stringTableMap.find(&str);
    if (it == stringTableMap.end()) {
      return U(0);
    }
    return it->second;
  }

  U GetOrCreateStrIdxFromName(const T &str) {
    U strIdx = GetStrIdxFromName(str);
    if (strIdx == 0) {
      strIdx.SetIdx(stringTable.size());
      T *newStr = new (std::nothrow) T(str);
      CHECK_FATAL(newStr != nullptr, "null ptr check");
      stringTable.push_back(newStr);
      stringTableMap[newStr] = strIdx;
    }
    return strIdx;
  }

  size_t StringTableSize(void) const {
    return stringTable.size();
  }

  const T &GetStringFromStrIdx(U strIdx) const {
    ASSERT(strIdx.GetIdx() < stringTable.size(), "array index out of range");
    return *stringTable[strIdx.GetIdx()];
  }

 private:
  std::vector<const T*> stringTable;  // index is uint32
  std::unordered_map<const T*, U, StrPtrHash, StrPtrEqual> stringTableMap;
};

class FPConstTable {
 public:
  FPConstTable &operator=(const FPConstTable &p) = delete;
  FPConstTable(const FPConstTable &p) = delete;

  ~FPConstTable();
  MIRFloatConst *GetOrCreateFloatConst(float);     // get the const from floatConstTable or create a new one
  MIRDoubleConst *GetOrCreateDoubleConst(double);  // get the const from doubleConstTable or create a new one

  static std::unique_ptr<FPConstTable> Create() {
    auto p = std::unique_ptr<FPConstTable>(new FPConstTable());
    p->PostInit();
    return p;
  }

 private:
  FPConstTable() : floatConstTable(), doubleConstTable(){};
  void PostInit();
  std::unordered_map<float, MIRFloatConst*> floatConstTable;     // map float const value to the table;
  std::unordered_map<double, MIRDoubleConst*> doubleConstTable;  // map double const value to the table;
  MIRFloatConst *nanFloatConst, *infFloatConst, *minusInfFloatConst, *minusZeroFloatConst;
  MIRDoubleConst *nanDoubleConst, *infDoubleConst, *minusInfDoubleConst, *minusZeroDoubleConst;
};

// STypeNameTable is only used to store class and interface types.
// Each module maintains its own MIRTypeNameTable.
class STypeNameTable {
 public:
  STypeNameTable() : gStrIdxToTyIdxMap() {}

  virtual ~STypeNameTable() {}

  std::unordered_map<GStrIdx, TyIdx, GStrIdxHash> &GetGStridxToTyidxMap() {
    return gStrIdxToTyIdxMap;
  }

  TyIdx GetTyidxFromGstrIdx(GStrIdx idx) const {
    auto it = gStrIdxToTyIdxMap.find(idx);
    if (it == gStrIdxToTyIdxMap.end()) {
      return TyIdx(0);
    }
    return it->second;
  }

  void SetGStrIdxToTyIdx(GStrIdx gStrIdx, TyIdx tyIdx) {
    gStrIdxToTyIdxMap[gStrIdx] = tyIdx;
  }

 private:
  std::unordered_map<GStrIdx, TyIdx, GStrIdxHash> gStrIdxToTyIdxMap;
};

class FunctionTable {
 public:
  FunctionTable() {
    funcTable.push_back(nullptr);
  }  // puIdx 0 is reserved

  virtual ~FunctionTable() {}

  std::vector<MIRFunction*> &GetFuncTable() {
    return funcTable;
  }

  MIRFunction *GetFunctionFromPuidx(PUIdx pidx) const {
    CHECK_FATAL(pidx < funcTable.size(), "Invalid puIdx");
    return funcTable.at(pidx);
  }

 private:
  std::vector<MIRFunction*> funcTable;  // index is PUIdx
};

class MIRSymbol;
class GSymbolTable {
 public:
  GSymbolTable();
  GSymbolTable(const GSymbolTable&) = delete;
  GSymbolTable &operator=(const GSymbolTable&) = delete;
  ~GSymbolTable();

  MIRModule *GetModule() {
    return module;
  }

  void SetModule(MIRModule *m) {
    module = m;
  }

  bool IsValidIdx(size_t idx) const {
    return idx < symbolTable.size();
  }

  MIRSymbol *GetSymbolFromStidx(uint32 idx, bool checkfirst = false) const {
    if (checkfirst && idx >= symbolTable.size()) {
      return nullptr;
    }
    ASSERT(IsValidIdx(idx), "symbol table index out of range");
    return symbolTable[idx];
  }

  void SetStrIdxStIdxMap(GStrIdx strIdx, StIdx stIdx) {
    strIdxToStIdxMap[strIdx] = stIdx;
  }

  StIdx GetStIdxFromStrIdx(GStrIdx idx) const {
    auto it = strIdxToStIdxMap.find(idx);
    if (it == strIdxToStIdxMap.end()) {
      return StIdx();
    }
    return it->second;
  }

  MIRSymbol *GetSymbolFromStrIdx(GStrIdx idx, bool checkfirst = false) const {
    return GetSymbolFromStidx(GetStIdxFromStrIdx(idx).Idx(), checkfirst);
  }

  size_t GetSymbolTableSize() const {
    return symbolTable.size();
  }

  MIRSymbol *GetSymbol(uint32 idx) const {
    ASSERT(idx < symbolTable.size(), "array index out of range");
    return symbolTable.at(idx);
  }

  MIRSymbol *CreateSymbol(uint8 scopeID);
  bool AddToStringSymbolMap(const MIRSymbol *st);
  bool RemoveFromStringSymbolMap(const MIRSymbol *st);
  void Dump(bool islocal, int32 indent = 0) const;

 private:
  MIRModule *module;

 private:
  // hash table mapping string index to st index
  std::unordered_map<GStrIdx, StIdx, GStrIdxHash> strIdxToStIdxMap;
  std::vector<MIRSymbol*> symbolTable;  // map symbol idx to symbol node
};

class MIRConst;
class ConstPool {
 public:
  std::unordered_map<std::u16string, MIRSymbol*> &GetConstU16StringPool() {
    return constU16StringPool;
  }

  void InsertConstPool(GStrIdx strIdx, MIRConst *cst) {
    constMap.insert(std::pair<GStrIdx, MIRConst*>(strIdx, cst));
  }

  MIRConst *GetConstFromPool(GStrIdx strIdx) {
    return constMap[strIdx];
  }

  void PutLiteralNameAsImported(GStrIdx gIdx) {
    importedLiteralNames.insert(gIdx);
  }

  bool LookUpLiteralNameFromImported(GStrIdx gIdx) {
    return importedLiteralNames.find(gIdx) != importedLiteralNames.end();
  }

 protected:
  std::unordered_map<GStrIdx, MIRConst*, GStrIdxHash> constMap;
  std::set<GStrIdx> importedLiteralNames;

 private:
  std::unordered_map<std::u16string, MIRSymbol*> constU16StringPool;
};

class GlobalTables {
 public:
  static GlobalTables &GetGlobalTables();

  static StringTable<std::string, GStrIdx> &GetStrTable() {
    return globalTables.gStringTable;
  }

  static StringTable<std::string, UStrIdx> &GetUStrTable() {
    return globalTables.uStrTable;
  }

  static StringTable<std::u16string, U16StrIdx> &GetU16StrTable() {
    return globalTables.u16StringTable;
  }

  static TypeTable &GetTypeTable() {
    return globalTables.typeTable;
  }

  static FPConstTable &GetFpConstTable() {
    return *(globalTables.fpConstTablePtr);
  }

  static STypeNameTable &GetTypeNameTable() {
    return globalTables.typeNameTable;
  }

  static FunctionTable &GetFunctionTable() {
    return globalTables.functionTable;
  }

  static GSymbolTable &GetGsymTable() {
    return globalTables.gSymbolTable;
  }

  static ConstPool &GetConstPool() {
    return globalTables.constPool;
  }

  GlobalTables(const GlobalTables &globalTables) = delete;
  GlobalTables(const GlobalTables &&globalTables) = delete;
  GlobalTables &operator=(const GlobalTables &globalTables) = delete;
  GlobalTables &operator=(const GlobalTables &&globalTables) = delete;

 private:
  TypeTable typeTable;
  STypeNameTable typeNameTable;
  FunctionTable functionTable;
  GSymbolTable gSymbolTable;
  ConstPool constPool;
  std::unique_ptr<FPConstTable> fpConstTablePtr;
  StringTable<std::string, GStrIdx> gStringTable;
  StringTable<std::string, UStrIdx> uStrTable;
  StringTable<std::u16string, U16StrIdx> u16StringTable;
  static GlobalTables globalTables;
  virtual ~GlobalTables() = default;
  GlobalTables() : fpConstTablePtr(FPConstTable::Create()) {
    gStringTable.Init();
    uStrTable.Init();
    u16StringTable.Init();
  }
};

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_GLOBAL_TABLES_H
