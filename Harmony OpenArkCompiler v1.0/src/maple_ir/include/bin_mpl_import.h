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
#ifndef MAPLE_IR_INCLUDE_BIN_MPL_IMPORT_H
#define MAPLE_IR_INCLUDE_BIN_MPL_IMPORT_H
#include "mir_module.h"
#include "mir_nodes.h"
#include "mir_preg.h"
#include "parser_opt.h"
#include "mir_builder.h"

namespace maple {
class BinaryMplImport {
  using CallSite = std::pair<CallInfo*, PUIdx>;

 public:
  BinaryMplImport &operator = (const BinaryMplImport &) = delete;
  BinaryMplImport(const BinaryMplImport &) = delete;
  explicit BinaryMplImport(MIRModule &md) : mod(md), mirBuilder(&md) {
    imported = true;
    bufI = 0;
  }

  virtual ~BinaryMplImport() {
    for (MIRStructType *structPtr : tmpStruct) {
      delete structPtr;
    }
    for (MIRClassType *classPtr : tmpClass) {
      delete classPtr;
    }
    for (MIRInterfaceType *interfacePtr : tmpInterface) {
      delete interfacePtr;
    }
  }

  uint64 GetBufI() {
    return bufI;
  }

  void SetBufI(uint64 bufIVal) {
    bufI = bufIVal;
  }

  bool IsBufEmpty() {
    return buf.empty();
  }

  size_t GetBufSize() {
    return buf.size();
  }

  int32 GetContent(int64 key) {
    return content[key];
  }

  void SetImported(bool importedVal) {
    imported = importedVal;
  }

  bool Import(const std::string &modid, bool readSymbols = false, bool readSe = false);
  void ReadContentField();
  void ReadStrField();
  void ReadTypeField();
  void Jump2NextField();
  void Reset();
  MIRSymbol *GetOrCreateSymbol(const TyIdx &tyIdx, const GStrIdx &strIdx, MIRSymKind mclass, MIRStorageClass sclass,
                               MIRFunction *func, uint8 scpID);
  MIRType *InsertInTypeTables(MIRType *ptype);
  void InsertInHashTable(MIRType *ptype);
  void SetupEHRootType();
  void UpdateMethodSymbols();
  void ImportConstBase(MIRConstKind &kind, MIRTypePtr &type, uint32 &fieldID);
  MIRConst *ImportConst(MIRFunction *func);
  GStrIdx ImportStr();
  UStrIdx ImportUsrStr();
  MIRType *CreateMirType(MIRTypeKind kind, GStrIdx strIdx, int64 tag) const;
  MIRGenericInstantType *CreateMirGenericInstantType(GStrIdx strIdx) const;
  MIRBitFieldType *CreateBitFieldType(uint8 fieldsize, PrimType pt, GStrIdx strIdx) const;
  void completeAggInfo(TyIdx tyIdx);
  TyIdx ImportType(bool forPointedType = false);
  void ImportTypeBase(PrimType &primType, GStrIdx &strIdx, bool &nameIsLocal);
  void InSymTypeTable();
  void ImportTypePairs(std::vector<TypePair> &tpairs);
  TypeAttrs ImportTypeAttrs();
  MIRPragmaElement *ImportPragmaElement();
  MIRPragma *ImportPragma();
  void ImportFieldPair(FieldPair &fp);
  void ImportMethodPair(MethodPair &memPool);
  void ImportMethodsOfStructType(MethodVector &methods);
  void ImportStructTypeData(MIRStructType *type);
  void ImportInterfacesOfClassType(std::vector<TyIdx> &interfaces);
  void ImportInfoIsStringOfClassType(std::vector<bool> &infoIsString);
  void ImportInfoOfClassType(std::vector<bool> &infoIsString, std::vector<MIRInfoPair> &infos);
  void ImportPragmaOfClassType(std::vector<MIRPragma*> &pragmas);
  void SetClassTyidxOfMethods(MIRStructType *type);
  void ImportClassTypeData(MIRClassType *type);
  void ImportInterfaceTypeData(MIRInterfaceType *type);
  PUIdx ImportFunction();
  MIRSymbol *InSymbol(MIRFunction *func);
  void InWord(int64 targetTag, uint8 **typeTagged, uint16 frameSize);
  void ReadFileAt(const std::string &modid, int32 offset);
  uint8 Read();
  int32 ReadInt();
  int64 ReadInt64();
  void ReadAsciiStr(std::string &str);
  int64 ReadNum();
  int32 GetIPAFileIndex(std::string &name);

 private:
  uint64 bufI;
  std::vector<uint8> buf;
  std::map<int64, int32> content;
  bool imported;  // used only by irbuild to convert to ascii
  MIRModule &mod;
  MIRBuilder mirBuilder;
  std::vector<GStrIdx> gStrTab;
  std::vector<UStrIdx> uStrTab;
  std::vector<MIRStructType*> tmpStruct;
  std::vector<MIRClassType*> tmpClass;
  std::vector<MIRInterfaceType*> tmpInterface;
  std::vector<MIRType*> typTab;
  std::vector<MIRFunction*> funcTab;
  std::vector<MIRSymbol*> symTab;
  std::vector<MIRSymbol*> methodSymbols;
  std::map<TyIdx, TyIdx> typeDefIdxMap;  // map previous declared tyIdx
  std::vector<bool> definedLabels;
  std::string importFileName;

  void SkipTotalSize();
  void ImportFieldsOfStructType(FieldVector &fields, uint32 methodSize);
};

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_BIN_MPL_IMPORT_H
