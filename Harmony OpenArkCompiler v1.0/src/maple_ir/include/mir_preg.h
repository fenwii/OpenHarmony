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
#ifndef MAPLE_IR_INCLUDE_MIR_PREG_H
#define MAPLE_IR_INCLUDE_MIR_PREG_H
#if MIR_FEATURE_FULL
#include "mir_module.h"
#include "global_tables.h"
#endif  // MIR_FEATURE_FULL

namespace maple {
// these special registers are encoded by negating the enumeration
enum SpecialReg : signed int {
  kSregSp = 1,
  kSregFp = 2,
  kSregGp = 3,
  kSregThrownval = 4,
  kSregMethodhdl = 5,
  kSregRetval0 = 6,
  kSregLast = 7,
};
#if MIR_FEATURE_FULL
class MIRPreg {
 public:
  explicit MIRPreg(uint32 n = 0) : primType(kPtyInvalid), isRef(false), needRC(false), pregNo(n), mirType(nullptr) {}

  MIRPreg(uint32 n, MIRType *mType) : MIRPreg(n) {
    mirType = mType;
  }

  ~MIRPreg(){};
  void SetNeedRC(bool needRC = true) {
    this->needRC = needRC;
  }

  bool NeedRC() const {
    return needRC;
  }

  bool IsRef() const {
    return isRef;
  }

  void SetIsRef(bool isRef) {
    this->isRef = isRef;
  }

  PrimType GetPrimType() const {
    return primType;
  }

  void SetPrimType(PrimType pty) {
    primType = pty;
  }

  int32 GetPregNo() const {
    return pregNo;
  }

  void SetPregNo(int32 pregNo) {
    this->pregNo = pregNo;
  }

  MIRType *GetMIRType() const {
    return mirType;
  }

  void SetMIRType(MIRType *mirType) {
    this->mirType = mirType;
  }

 private:
  PrimType primType;
  bool isRef;
  bool needRC;
  int32 pregNo;  // the number in maple IR after the %
  MIRType *mirType;
};

class MIRPregTable {
 public:
  static constexpr uint32 kMaxUserPregIndex = 10000;
  MIRPregTable(MIRModule *mod, MapleAllocator *allocator)
      : pregIndex(kMaxUserPregIndex),
        pregNoToPregIdxMap(std::less<uint32>(), allocator->Adapter()),
        pregTable(allocator->Adapter()),
        module(mod),
        mAllocator(allocator) {
    pregTable.push_back(static_cast<MIRPreg*>(nullptr));
    specPregTable[0].SetPregNo(0);
    specPregTable[kSregSp].SetPregNo(-kSregSp);
    specPregTable[kSregFp].SetPregNo(-kSregFp);
    specPregTable[kSregGp].SetPregNo(-kSregGp);
    specPregTable[kSregThrownval].SetPregNo(-kSregThrownval);
    specPregTable[kSregMethodhdl].SetPregNo(-kSregMethodhdl);
    specPregTable[kSregRetval0].SetPregNo(-kSregRetval0);
    for (uint32 i = 0; i < kSregLast; i++) {
      specPregTable[i].SetPrimType(PTY_unknown);
    }
  }

  ~MIRPregTable();

  PregIdx CreatePreg(PrimType primType) {
    uint32 index = pregIndex++;
    MIRPreg *preg = mAllocator->GetMemPool()->New<MIRPreg>(index);
    preg->SetPrimType(primType);
    PregIdx idx = pregTable.size();
    ASSERT(idx < 0xffff, "will has problem if over 16 bits");
    pregTable.push_back(preg);
    pregNoToPregIdxMap[index] = idx;
    pregTable[idx]->SetMIRType(GlobalTables::GetTypeTable().GetPrimType(primType));
    return idx;
  }

  PregIdx CreateRefPreg(MIRType *mirType) {
    ASSERT(mirType->GetPrimType() == PTY_ref || mirType->GetPrimType() == PTY_ptr, "ref or ptr type");
    PregIdx idx = CreatePreg(mirType->GetPrimType());
    pregTable[idx]->SetMIRType(mirType);
    return idx;
  }

  PregIdx CreateRefPreg(MIRPreg *mirPreg) {
    uint32 index = pregIndex++;
    MIRPreg *preg = mAllocator->GetMemPool()->New<MIRPreg>(index, mirPreg->GetMIRType());
    preg->SetPrimType(mirPreg->GetPrimType());
    preg->SetMIRType(mirPreg->GetMIRType());
    preg->SetNeedRC(mirPreg->NeedRC());
    PregIdx idx = pregTable.size();
    ASSERT(idx < 0xffff, "will has problem if over 16 bits");
    pregTable.push_back(preg);
    pregNoToPregIdxMap[index] = idx;
    return idx;
  }

  MIRPreg *PregFromPregIdx(PregIdx pregIdx) {
    // pregIdx < 0 denotes special register
    return (pregIdx < 0) ? &specPregTable[-pregIdx] : pregTable.at(pregIdx);
  }

  PregIdx GetPregIdxFromPregno(uint32 pregNo) {
    auto it = pregNoToPregIdxMap.find(pregNo);
    return (it == pregNoToPregIdxMap.end()) ? PregIdx(0) : it->second;
  }

  void DumpRef(int32);
  size_t Size(void) const {
    return pregTable.size();
  }

  void AddPreg(MIRPreg *preg) {
    PregIdx idx = pregTable.size();
    pregTable.push_back(preg);
    ASSERT(pregNoToPregIdxMap.find(preg->GetPregNo()) == pregNoToPregIdxMap.end(), "The same pregno is already taken");
    pregNoToPregIdxMap[preg->GetPregNo()] = idx;
  }

  MapleVector<MIRPreg*> &GetPregTable() {
    return pregTable;
  }

  MIRPreg *GetPregTableItem(uint32 index) {
    CHECK_FATAL(index < pregTable.size(), "array index out of range");
    return pregTable[index];
  }

  void SetPregNoToPregIdxMapItem(uint32 key, PregIdx value) {
    pregNoToPregIdxMap[key] = value;
  }

  uint32 GetIndex() const {
    return pregIndex;
  }

  void SetIndex(uint32 index) {
    pregIndex = index;
  }

 private:
  uint32 pregIndex;                              // user(maple_ir)'s preg must less than this value
  MapleMap<uint32, PregIdx> pregNoToPregIdxMap;  // for quick lookup based on pregno
  MapleVector<MIRPreg*> pregTable;
  MIRPreg specPregTable[kSregLast];  // for the MIRPreg nodes corresponding to special registers
  MIRModule *module;
  MapleAllocator *mAllocator;
};

#endif  // MIR_FEATURE_FULL
}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_MIR_PREG_H
