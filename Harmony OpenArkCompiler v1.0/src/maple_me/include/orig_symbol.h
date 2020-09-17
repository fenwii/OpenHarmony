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
#ifndef MAPLE_ME_INCLUDE_ORIG_SYMBOL_H
#define MAPLE_ME_INCLUDE_ORIG_SYMBOL_H
#include "mir_module.h"
#include "mir_symbol.h"
#include "mir_preg.h"
#include "mir_function.h"
#include "bb.h"

// This file defines the data structure OriginalSt that represents a program
// symbol occurring in the code of the program being optimized.

namespace maple {
constexpr int kInitVersion = 0;
class VarMeExpr;
class OriginalSt {
 public:
  OriginalSt(OStIdx index, MapleAllocator *alloc, bool local, bool isFormal, FieldID fieldIDPara)
      : ostType(kUnkonwnOst),
        index(index),
        versionsIndex(alloc->Adapter()),
        zeroVersionIndex(0),
        tyIdx(0),
        fieldID(fieldIDPara),
        indirectLev(0),
        isLocal(local),
        isFormal(isFormal),
        addressTaken(false),
        isFinal(false),
        isPrivate(false),
        ignoreRC(false),
        epreLocalRefVar(false),
        symOrPreg(),
        puIdx(0) {}

  OriginalSt(uint32 index, PregIdx rIdx, PUIdx pIdx, MapleAllocator *alloc)
      : OriginalSt(OStIdx(index), alloc, true, false, 0) {
    ostType = kPregOst;
    symOrPreg.pregIdx = rIdx;
    puIdx = pIdx;
  }

  OriginalSt(uint32 index, MIRSymbol *mirSt, PUIdx pIdx, FieldID fieldIDPara, MapleAllocator *alloc)
      : OriginalSt(OStIdx(index), alloc, mirSt->IsLocal(), mirSt->GetStorageClass() == kScFormal, fieldIDPara) {
    ostType = kSymbolOst;
    symOrPreg.mirSt = mirSt;
    puIdx = pIdx;
    ignoreRC = mirSt->IgnoreRC();
  }

  void Dump() const;
  PregIdx GetPregIdx() const {
    ASSERT(ostType == kPregOst, "OriginalSt must be PregOst");
    return symOrPreg.pregIdx;
  }

  MIRPreg *GetMIRPreg() const {
    ASSERT(ostType == kPregOst, "OriginalSt must be PregOst");
    return GlobalTables::GetGsymTable().GetModule()->CurFunction()->GetPregTab()->PregFromPregIdx(symOrPreg.pregIdx);
  }

  MIRSymbol *GetMIRSymbol() const {
    ASSERT(ostType == kSymbolOst, "OriginalSt must be SymbolOst");
    return symOrPreg.mirSt;
  }

  bool HasAttr(AttrKind x) const {
    if (ostType == kSymbolOst) {
      TypeAttrs typeAttr = symOrPreg.mirSt->GetAttrs();
      if (typeAttr.GetAttr(x)) {
        return true;
      }
    }
    return false;
  }

  bool IsLocal() const {
    return isLocal;
  }

  bool IsFormal() const {
    return isFormal;
  }

  void SetIsFormal(bool isFormalPara = true) {
    this->isFormal = isFormalPara;
  }

  bool IsFinal() const {
    return isFinal;
  }

  void SetIsFinal(bool isFinalPara = true) {
    this->isFinal = isFinalPara;
  }

  bool IsPrivate() const {
    return isPrivate;
  }

  void SetIsPrivate(bool isPrivatePara = true) {
    this->isPrivate = isPrivatePara;
  }

  bool IsVolatile() const {
    return (ostType == kSymbolOst) ? symOrPreg.mirSt->IsVolatile() : false;
  }

  bool IsVrNeeded() const {
    return (ostType == kSymbolOst) ? symOrPreg.mirSt->GetIsTmp() : false;
  }

  bool Equal(const OriginalSt *ost) const;

  bool IsRealSymbol() const {
    return (ostType == kSymbolOst || ostType == kPregOst);
  }

  bool IsSymbolOst() const {
    return (ostType == kSymbolOst);
  }

  bool IsPregOst() const {
    return (ostType == kPregOst);
  }

  int8 GetIndirectLev() const {
    return indirectLev;
  }

  void SetIndirectLev(int8 idl) {
    this->indirectLev = idl;
  }

  ~OriginalSt(){};

  OStIdx GetIndex() const {
    return index;
  }

  size_t GetVersionIndex(size_t version) const {
    ASSERT(version < versionsIndex.size(), "version out of range");
    return versionsIndex.at(version);
  }

  MapleVector<size_t> &GetVersionsIndex() {
    return versionsIndex;
  }

  size_t GetZeroVersionIndex() const {
    return zeroVersionIndex;
  }

  void SetZeroVersionIndex(size_t zeroVersionIndexParam) {
    zeroVersionIndex = zeroVersionIndexParam;
  }

  TyIdx GetTyIdx() const {
    return tyIdx;
  }

  void SetTyIdx(TyIdx tyIdxPara) {
    tyIdx = tyIdxPara;
  }

  FieldID GetFieldID() const {
    return fieldID;
  }

  void SetFieldID(FieldID fieldIDPara) {
    fieldID = fieldIDPara;
  }

  bool IsIgnoreRC() {
    return ignoreRC;
  }

  bool IsAddressTaken() {
    return addressTaken;
  }

  bool IsEPreLocalRefVar() {
    return epreLocalRefVar;
  }

  void SetEPreLocalRefVar(bool epreLocalrefvarPara = true) {
    epreLocalRefVar = epreLocalrefvarPara;
  }

  PUIdx GetPuIdx() {
    return puIdx;
  }

  PUIdx GetPuIdx() const {
    return puIdx;
  }

 private:
  enum OSTType { kUnkonwnOst, kSymbolOst, kPregOst } ostType;

  OStIdx index;                       // index number in originalStVector
  MapleVector<size_t> versionsIndex;  // the i-th element refers the index of versionst in versionst table
  size_t zeroVersionIndex;            // same as versionsIndex[0]
  TyIdx tyIdx;                        // type of this symbol at this level; 0 for unknown
  FieldID fieldID;                    // at each level of indirection
  int8 indirectLev;                   // level of indirection; -1 for address, 0 for itself
  bool isLocal;                       // get from defined stmt or use expr
  bool isFormal;  // it's from the formal parameters so the type must be kSymbolOst or kPregOst after rename2preg
  bool addressTaken;
  bool isFinal;          // if the field has final attribute, only when fieldID != 0
  bool isPrivate;        // if the field has private attribute, only when fieldID != 0
  bool ignoreRC;         // base on MIRSymbol's IgnoreRC()
  bool epreLocalRefVar;  // is a localrefvar temp created by epre phase
  union {
    PregIdx pregIdx;
    MIRSymbol *mirSt;
  } symOrPreg;

  PUIdx puIdx;
};

// This Table is for original symobols only. There is no SSA info attached and SSA is built based on this table.
class OriginalStTable {
 public:
  OriginalStTable(MemPool *memPool, MIRModule *mod);
  ~OriginalStTable() {}

  OriginalSt *FindOrCreateSymbolOriginalSt(MIRSymbol *mirSt, PUIdx puIdx, FieldID fld);
  OriginalSt *FindOrCreatePregOriginalSt(PregIdx pregIdx, PUIdx puIdx);
  OriginalSt *CreateSymbolOriginalSt(MIRSymbol *mirSt, PUIdx pidx, FieldID fld);
  OriginalSt *CreatePregOriginalSt(PregIdx pregIdx, PUIdx puIdx);
  OriginalSt *FindSymbolOriginalSt(MIRSymbol *mirSt);
  OriginalSt *GetOriginalStFromID(OStIdx id, bool checkfirst = false) {
    if (checkfirst && id.idx >= originalStVector.size()) {
      return nullptr;
    }
    ASSERT(id.idx < originalStVector.size(), "symbol table index out of range");
    return originalStVector[id.idx];
  }

  size_t Size() const {
    return originalStVector.size();
  }

  MIRSymbol *GetMIRSymbolFromOriginalSt(const OriginalSt *ost) const {
    ASSERT(ost->IsRealSymbol(), "runtime check error");
    return ost->GetMIRSymbol();
  }

  MIRSymbol *GetMIRSymbolFromID(OStIdx id) {
    return GetMIRSymbolFromOriginalSt(GetOriginalStFromID(id, false));
  }

  MapleAllocator &GetAlloc() {
    return alloc;
  }

  MapleVector<OriginalSt*> &GetOriginalStVector() {
    return originalStVector;
  }

  void Dump();

 private:
  MapleAllocator alloc;
  MIRModule *mirModule;
  MapleVector<OriginalSt*> originalStVector;  // the vector that map a OriginalSt's index to its pointer
  MapleUnorderedMap<MIRSymbol*, OStIdx>
      mirSt2Ost;  // mir symbol to original table, this only exists for no-original variables.
  MapleUnorderedMap<PregIdx, OStIdx> preg2Ost;
  MapleMap<TyIdx, OStIdx>
      pType2Ost;  // mir type to virtual variables in original table. this only exists for no-original variables.
  MapleMap<std::pair<BaseNode*, uint32>, OStIdx>
      malloc2Ost;  // malloc info to virtual variables in original table. this only exists for no-original variables.
  MapleMap<uint32, OStIdx> thisField2Ost;  // field of this_memory to virtual variables in original table.
  OStIdx virtuaLostUnkownMem;
  OStIdx virtuaLostConstMem;
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ORIG_SYMBOL_H
