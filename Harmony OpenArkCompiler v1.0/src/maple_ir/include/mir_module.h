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
#ifndef MAPLE_IR_INCLUDE_MIR_MODULE_H
#define MAPLE_IR_INCLUDE_MIR_MODULE_H
#include "types_def.h"
#include "prim_types.h"
#include "intrinsics.h"
#include "opcodes.h"
#include "mpl_logging.h"
#include "muid.h"
#if MIR_FEATURE_FULL
#include <string>
#include <unordered_set>
#include "mempool.h"
#include "mempool_allocator.h"
#include "maple_string.h"
#endif  // MIR_FEATURE_FULL

namespace maple {
class CallInfo;
class MIRModule;
class MIRBuilder;
using MIRModulePtr = MIRModule*;
using MIRBuilderPtr = MIRBuilder*;

enum MIRFlavor {
  kFlavorUnknown,
  kFeProduced,
  kMeProduced,
  kBeLowered,
  kMmpl,
  kCmplV1,
  kCmpl  // == CMPLv2
};

enum MIRSrcLang { kSrcLangUnknown, kSrcLangC, kSrcLangJs, kSrcLangJava, kSrcLangCPlusPlus };


// blksize gives the size of the memory block in bytes; there are (blksize+3)/4
// words; 1 bit for each word, so the bit vector's length in bytes is
// ((blksize+3)/4+7)/8
static inline uint32 BlockSize2BitVectorSize(uint32 blkSize) {
  uint32 bitVectorLen = ((blkSize + 3) / 4 + 7) / 8;
  return ((bitVectorLen + 3) >> 2) << 2;  // round up to word boundary
}

#if MIR_FEATURE_FULL
class MIRType;
class MIRFunction;
class MIRSymbol;
class MIRSymbolTable;
class MIRTypeNameTable;
class MIRFloatConst;
class MIRDoubleConst;
class MIRBuilder;
class DebugInfo;
class BinaryMplt;
using MIRInfoPair = std::pair<GStrIdx, uint32>;
using MIRInfoVector = MapleVector<MIRInfoPair>;
using MIRDataPair = std::pair<GStrIdx, std::vector<uint8>>;
using MIRDataVector = MapleVector<MIRDataPair>;
constexpr int kMaxEncodedValueLen = 10;
struct EncodedValue {
  uint8 encodedValue[kMaxEncodedValueLen] = { 0 };
};

class MIRTypeNameTable {
 private:
  MapleAllocator *mAllocator;
  MapleMap<GStrIdx, TyIdx> gStrIdxToTyIdxMap;

 public:
  explicit MIRTypeNameTable(MapleAllocator *allocator)
      : mAllocator(allocator), gStrIdxToTyIdxMap(std::less<GStrIdx>(), mAllocator->Adapter()) {}

  ~MIRTypeNameTable() = default;

  MapleMap<GStrIdx, TyIdx> &GetGStrIdxToTyIdxMap() {
    return gStrIdxToTyIdxMap;
  }

  TyIdx GetTyIdxFromGStrIdx(GStrIdx idx) {
    auto it = gStrIdxToTyIdxMap.find(idx);
    if (it == gStrIdxToTyIdxMap.end()) {
      return TyIdx(0);
    }
    return it->second;
  }

  void SetGStrIdxToTyIdx(GStrIdx gStrIdx, TyIdx tyIdx) {
    gStrIdxToTyIdxMap[gStrIdx] = tyIdx;
  }

  size_t Size() const {
    return gStrIdxToTyIdxMap.size();
  }
};

class MIRModule {
 public:
  using CallSite = std::pair<CallInfo*, PUIdx>;

  MIRModule(MIRModule &p) = delete;
  MIRModule &operator=(const MIRModule &module) = delete;

  explicit MIRModule(const char *fn = "");
  ~MIRModule();

  const MemPool *GetMemPool() const {
    return memPool;
  }

  MemPool *GetMemPool() {
    return memPool;
  }

  const MapleAllocator &GetMPAllocator() const {
    return memPoolAllocator;
  }

  MapleAllocator &GetMPAllocator() {
    return memPoolAllocator;
  }

  const MapleVector<MIRFunction*> &GetFunctionList() const {
    return functionList;
  }

  MapleVector<MIRFunction*> &GetFunctionList() {
    return functionList;
  }

  const MIRFunction *GetFunctionList(int cnt) const {
    CHECK_FATAL(cnt < functionList.size(), "array index out of range");
    return functionList[cnt];
  }

  MIRFunction *GetFunctionList(int cnt) {
    CHECK_FATAL(cnt < functionList.size(), "array index out of range");
    return functionList[cnt];
  }

  MapleVector<MIRFunction*> &GetCompilationList() {
    return compilationList;
  }

  MapleVector<std::string> &GetImportedMplt() {
    return importedMplt;
  }

  MIRTypeNameTable *GetTypeNameTab() {
    return typeNameTab;
  }

  MapleVector<GStrIdx> &GetTypeDefOrder() {
    return typeDefOrder;
  }

  void AddClass(TyIdx t);
  void RemoveClass(TyIdx t);

  inline void SetCurFunction(MIRFunction * const f) {
    curFunction = f;
  }

  MIRSrcLang GetSrcLang() const {
    return srcLang;
  }

  MapleSet<TyIdx> &GetExternStructTypeSet() {
    return externStructTypeSet;
  }

  MapleSet<StIdx> &GetSymbolSet() {
    return symbolSet;
  }

  MapleVector<StIdx> &GetSymbolDefOrder() {
    return symbolDefOrder;
  }

  void SetSomeSymbolNeedForDecl(bool s) {
    someSymbolNeedForwDecl = s;
  }

  MIRFunction *CurFunction(void) const;
  MemPool *CurFuncCodeMemPool(void) const;
  MapleAllocator *CurFuncCodeMemPoolAllocator(void) const;
  void AddExternStructType(TyIdx tyIdx);
  void AddExternStructType(const MIRType *t);
  void AddSymbol(StIdx stIdx);
  void AddSymbol(const MIRSymbol *s);
  void AddFunction(MIRFunction *pf) {
    functionList.push_back(pf);
    compilationList.push_back(pf);
  }

  MIRFloatConst *GetOrCreateFloatConst(float);     // get the const from float_const_table_ or create a new one
  MIRDoubleConst *GetOrCreateDoubleConst(double);  // get the const from double_const_table_ or create a new one
  void InitInfo();
  void DumpInfo();
  void DumpGlobals(bool emitStructureType = true);
  void Dump(bool emitStructureType = true);
  void DumpToFile(const std::string &fileNameStr, bool emitStructureType = true);
  void DumpInlineCandidateToFile(const std::string &fileNameStr);
  const std::string &GetFileNameFromFileNum(uint32 fileNum);

  void DumpClassToFile(const char *path);
  void DumpFunctionList(bool skipBody = false);
  void DumpGlobalArraySymbol();
  void Emit(const std::string &outfileName);
  uint32 GetAndIncFloatNum() {
    return floatNum++;
  }

  MIRFunction *GetLastFunction() const {
    return functionList.back();
  }

  void SetEntryFunction(MIRFunction *f) {
    entryFunc = f;
  }

  MIRFunction *GetEntryFunction() const {
    return entryFunc;
  }

  MIRFunction *FindEntryFunction();
  uint32 GetFileinfo(GStrIdx strIdx) const;
  void OutputAsciiMpl(const char *phaseName, bool emitStructureType = true);
  void OutputFunctionListAsciiMpl(const char *phaseName);
  const std::string &GetFileName() const {
    return fileName;
  }

  std::string GetFileNameAsPostfix() const;
  void SetFileName(const std::string &name) {
    fileName = name;
  }

  bool IsJavaModule() const {
    return srcLang == kSrcLangJava;
  }

  bool IsCModule() const {
    return srcLang == kSrcLangC || srcLang == kSrcLangCPlusPlus;
  }

  inline void addSuperCall(const std::string &func) {
    superCallSet.insert(func);
  }

  inline bool findSuperCall(const std::string &func) {
    return superCallSet.find(func) != superCallSet.end();
  }

  void SetFuncInfoPrinted() const;
  size_t GetOptFuncsSize() {
    return optimizedFuncs.size();
  }

  void AddOptFuncs(MIRFunction *func) {
    return optimizedFuncs.push_back(func);
  }

  MapleSet<uint32> &GetRcNoNeedingLock() {
    return rcNotNeedingLock;
  }

  MapleMap<PUIdx, MapleSet<FieldID>*> &GetPuIdxFieldInitializedMap() {
    return puIdxFieldInitializedMap;
  }

  MapleSet<FieldID> *GetPUIdxFieldInitializedMapItem(PUIdx first) {
    return puIdxFieldInitializedMap[first];
  }

  std::ostream &GetOut() {
    return out;
  }

  const MIRBuilderPtr &GetMIRBuilder() const {
    return mirBuilder;
  }

  const std::string &GetEntryFuncName() const {
    return entryFuncName;
  }

  std::string &GetEntryFuncName() {
    return entryFuncName;
  }

  void SetEntryFuncName(const std::string &entryFunctionName) {
    entryFuncName = entryFunctionName;
  }

  const TyIdx &GetThrowableTyIdx() const {
    return throwableTyIdx;
  }

  void SetThrowableTyIdx(TyIdx throwableTypeIndex) {
    throwableTyIdx = throwableTypeIndex;
  }

  bool GetWithProfileInfo() {
    return withProfileInfo;
  }

  void SetWithProfileInfo(bool withProfInfo) {
    withProfileInfo = withProfInfo;
  }

  BinaryMplt *GetBinMplt() {
    return binMplt;
  }

  void SetBinMplt(BinaryMplt *binaryMplt) {
    binMplt = binaryMplt;
  }

  MIRInfoVector &GetFileInfo() {
    return fileInfo;
  }

  void SetFileInfo(MIRInfoVector fileInf) {
    fileInfo = fileInf;
  }

  MapleVector<bool> &GetFileInfoIsString() {
    return fileInfoIsString;
  }

  void SetFileInfoIsString(MapleVector<bool> fileInfoIsStr) {
    fileInfoIsString = fileInfoIsStr;
  }

  MIRDataVector &GetFileData() {
    return fileData;
  }

  MIRInfoVector &GetSrcFileInfo() {
    return srcFileInfo;
  }

  const MIRFlavor &GetFlavor() const {
    return flavor;
  }

  void SetFlavor(MIRFlavor flv) {
    flavor = flv;
  }

  void SetSrcLang(MIRSrcLang sourceLanguage) {
    srcLang = sourceLanguage;
  }

  void SetID(uint16 num) {
    id = num;
  }

  uint32 GetGlobalMemSize() {
    return globalMemSize;
  }

  void SetGlobalMemSize(uint32 globalMemberSize) {
    globalMemSize = globalMemberSize;
  }

  uint8 *GetGlobalBlockMap() {
    return globalBlkMap;
  }

  void SetGlobalBlockMap(uint8 *globalBlockMap) {
    globalBlkMap = globalBlockMap;
  }

  uint8 *GetGlobalWordsTypeTagged() {
    return globalWordsTypeTagged;
  }

  void SetGlobalWordsTypeTagged(uint8 *globalWordsTyTagged) {
    globalWordsTypeTagged = globalWordsTyTagged;
  }

  uint8 *GetGlobalWordsRefCounted() {
    return globalWordsRefCounted;
  }

  void SetGlobalWordsRefCounted(uint8 *counted) {
    globalWordsRefCounted = counted;
  }

  void SetNumFuncs(uint32 numFunc) {
    numFuncs = numFunc;
  }

  MapleVector<GStrIdx> &GetImportFiles() {
    return importFiles;
  }

  MapleVector<GStrIdx> &GetImportPaths() {
    return importPaths;
  }

  MapleSet<uint32> &GetClassList() {
    return classList;
  }

  std::map<PUIdx, std::vector<CallSite>> &GetMethod2TargetMap() {
    return method2TargetMap;
  }

  std::vector<CallSite> &GetMemFromMethod2TargetMap(const PUIdx methodPuIdx) {
    return method2TargetMap[methodPuIdx];
  }

  void SetMethod2TargetMap(const std::map<PUIdx, std::vector<CallSite>> &map) {
    method2TargetMap = map;
  }

  void AddMemToMethod2TargetMap(const PUIdx idx, const std::vector<CallSite> &callSite) {
    method2TargetMap[idx] = callSite;
  }

  std::map<PUIdx, std::unordered_set<uint64>> &GetMethod2TargetHash() {
    return method2TargetHash;
  }

  std::unordered_set<uint64> &GetValueFromMethod2TargetHash(const PUIdx idx) {
    return method2TargetHash[idx];
  }

  void SetMethod2TargetHash(const std::map<PUIdx, std::unordered_set<uint64>> &map) {
    method2TargetHash = map;
  }

  void AddValueToMethod2TargetHash(const PUIdx idx, const std::unordered_set<uint64> &value) {
    method2TargetHash[idx] = value;
  }

 private:
  MemPool *memPool;
  MapleAllocator memPoolAllocator;
  MapleVector<MIRFunction*> functionList;  // function table in the order of the appearance of function bodies; it
  // excludes prototype-only functions
  MapleVector<MIRFunction*> compilationList;  // functions in the order of to be compiled.
  MapleVector<std::string> importedMplt;
  MIRTypeNameTable *typeNameTab;
  MapleVector<GStrIdx> typeDefOrder;

  MapleSet<TyIdx> externStructTypeSet;
  MapleSet<StIdx> symbolSet;
  MapleVector<StIdx> symbolDefOrder;
  bool someSymbolNeedForwDecl;  // some symbols' addressses used in initialization

  std::ostream &out;
  MIRBuilder *mirBuilder;
  std::string entryFuncName;  // name of the entry function
  std::string fileName;
  TyIdx throwableTyIdx;  // a special type that is the base of java exception type. only used for java
  bool withProfileInfo;
  // for cg in mplt
  BinaryMplt *binMplt;
  MIRInfoVector fileInfo;              // store info provided under fileInfo keyword
  MapleVector<bool> fileInfoIsString;  // tells if an entry has string value
  MIRDataVector fileData;
  MIRInfoVector srcFileInfo;  // store info provided under srcFileInfo keyword
  MIRFlavor flavor;
  MIRSrcLang srcLang;  // the source language
  uint16 id;
  uint32 globalMemSize;  // size of storage space for all global variables
  uint8 *globalBlkMap;   // the memory map of the block containing all the
  // globals, for specifying static initializations
  uint8 *globalWordsTypeTagged;  // bit vector where the Nth bit tells whether
  // the Nth word in globalBlkMap has typetag;
  // if yes, the typetag is the N+1th word; the
  // bitvector's size is given by
  // BlockSize2BitvectorSize(globalMemSize)
  uint8 *globalWordsRefCounted;  // bit vector where the Nth bit tells whether
  // the Nth word points to a reference-counted
  // dynamic memory block; the bitvector's size
  // is given by BlockSize2BitvectorSize(globalMemSize)
  uint32 numFuncs;  // because puIdx 0 is reserved, numFuncs is also the highest puIdx
  MapleVector<GStrIdx> importFiles;
  MapleVector<GStrIdx> importPaths;
  MapleSet<uint32> classList;

  std::map<PUIdx, std::vector<CallSite>> method2TargetMap;
  std::map<PUIdx, std::unordered_set<uint64>> method2TargetHash;

  MIRFunction *entryFunc;
  uint32 floatNum;
  MIRFunction *curFunction;
  MapleVector<MIRFunction*> optimizedFuncs;
  // Add the field for decouple optimization
  std::unordered_set<std::string> superCallSet;
  MapleSet<uint32> rcNotNeedingLock;  // set of stmtID's which does incref/decref to an object not escaping
  // record all the fields that are initialized in the constructor. module scope,
  // if puIdx doesn't appear in this map, it writes to all field id
  // if puIdx appears in the map, but it's corresponding MapleSet is nullptr, it writes nothing fieldID
  // if puIdx appears in the map, and the value of first corresponding MapleSet is 0, the puIdx appears in this module
  // and writes to all field id otherwise, it writes the field ids in MapleSet
  MapleMap<PUIdx, MapleSet<FieldID>*> puIdxFieldInitializedMap;
};

#endif  // MIR_FEATURE_FULL
}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_MIR_MODULE_H
