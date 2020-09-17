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
#ifndef MAPLE_PHASE_INCLUDE_PHASE_H
#define MAPLE_PHASE_INCLUDE_PHASE_H
#include <map>
#include <string>
#include <iostream>
#include "mempool.h"
#include "maple_string.h"
#include "mempool_allocator.h"
#include "option.h"

using PhaseID = int;

namespace maple {
/* base class of analysisPhase's result */
class AnalysisResult {
 public:
  explicit AnalysisResult(MemPool *memPoolParam) {
    ASSERT(memPoolParam != nullptr, "memPoolParam is null in AnalysisResult::AnalysisResult");
    memPool = memPoolParam;
  }

  MemPool *GetMempool() {
    return memPool;
  }

  void EraseMemPool() {
    mempoolctrler.DeleteMemPool(memPool);
  }

  virtual ~AnalysisResult() {}

 private:
  MemPool *memPool;
};

class Phase {
 public:
  Phase() {}

  virtual std::string PhaseName() const {
    ASSERT(false, "The base Phase::PhaseName should not be called");
    return "";
  }

  // obtain a new mempool by invoke this function
  MemPool *NewMemPool() {
    std::string phaseName = PhaseName();
    ASSERT(!phaseName.empty(), "PhaseName should not be empty");
    memPoolCount++;
    std::string memPoolName = phaseName + " MemPool " + std::to_string(memPoolCount);
    MemPool *memPool = mempoolctrler.NewMemPool(memPoolName.c_str());
    memPools.push_back(memPool);
    return memPool;
  }

  // release all mempool use in this phase except exclusion
  void ReleaseMemPool(const MemPool *exclusion) {
    for (MemPool *memPool : memPools) {
      if (memPool == exclusion) {
        continue;
      }
      mempoolctrler.DeleteMemPool(memPool);
      memPool = nullptr;
    }
    memPools.clear();
    memPools.shrink_to_fit();
  }

  virtual ~Phase(){};

 private:
  uint memPoolCount = 0;
  std::vector<MemPool*> memPools;
};

template <typename UnitIR, typename PhaseIDT, typename PhaseT>
class AnalysisResultManager {
 public:
  explicit AnalysisResultManager(MapleAllocator *alloc)
      : analysisResults(std::less<analysisResultKey>(), alloc->Adapter()),
        analysisPhases(std::less<PhaseIDT>(), alloc->Adapter()) {
    allocator = alloc;
  }

  virtual ~AnalysisResultManager() {
    InvalidAllResults();
    /* global variable mirModule which use same mempool control is not delete yet */
  }

  /* analysis result use global mempool and allocator */
  AnalysisResult *GetAnalysisResult(PhaseIDT id, UnitIR *ir) {
    ASSERT(ir != nullptr, "ir is null in AnalysisResultManager::GetAnalysisResult");
    std::pair<PhaseIDT, UnitIR*> key = std::make_pair(id, ir);
    if (analysisResults.find(key) != analysisResults.end()) {
      return analysisResults[key];
    }

    PhaseT *anaPhase = GetAnalysisPhase(id);
    ASSERT(anaPhase != nullptr, "anaphse is null in AnalysisResultManager::GetAnalysisResult");
    if (std::string(anaPhase->PhaseName()) != Options::skipPhase) {
      AnalysisResult *result = anaPhase->Run(ir, this);
      // allow invoke phases whose return value is nullptr using GetAnalysisResult
      if (result == nullptr) {
        anaPhase->ReleaseMemPool(nullptr);
        return nullptr;
      }
      anaPhase->ReleaseMemPool(result->GetMempool());
      analysisResults[key] = result; /* add r to analysisResults */
      return result;
    } else {
      return nullptr;
    }
  }

  void AddResult(PhaseIDT id, UnitIR *ir, AnalysisResult *ar) {
    ASSERT(ar != nullptr, "ar is null in AnalysisResultManager::AddResult");
    std::pair<PhaseIDT, UnitIR*> key = std::make_pair(id, ir);
    if (analysisResults.find(key) != analysisResults.end()) {
      InvalidAnalysisResult(id, ir);
    }
    analysisResults.insert(std::make_pair(key, ar));
  }

  void InvalidAnalysisResult(PhaseIDT id, UnitIR *ir) {
    std::pair<PhaseIDT, UnitIR*> key = std::make_pair(id, ir);
    auto it = analysisResults.find(key);
    if (it != analysisResults.end()) {
      AnalysisResult *r = analysisResults[key];
      r->EraseMemPool();
      analysisResults.erase(it);
    }
  }

  void InvalidIRbaseAnalysisResult(UnitIR *ir) {
    PhaseIDT id;
    for (auto it = analysisPhases.begin(); it != analysisPhases.end(); it++) {
      id = it->first;
      InvalidAnalysisResult(id, ir);
    }
  }

  void InvalidAllResults() {
    for (auto it = analysisResults.begin(); it != analysisResults.end(); it++) {
      AnalysisResult *r = it->second;
      ASSERT(r != nullptr, "r is null in AnalysisResultManager::InvalidAllResults");
      r->EraseMemPool();
    }
    analysisResults.clear();
  }

  void AddAnalysisPhase(PhaseIDT id, PhaseT *p) {
    ASSERT(p != nullptr, "p is null in AnalysisResultManager::AddAnalysisPhase");
    analysisPhases[id] = p;
  }

  PhaseT *GetAnalysisPhase(PhaseIDT id) {
    if (analysisPhases.find(id) != analysisPhases.end()) {
      return analysisPhases[id];
    } else {
      ASSERT(false, "Invalid analysis phase");
      return nullptr;
    }
  }

  void ClearAnalysisPhase() {
    analysisPhases.clear();
  }

 private:
  MapleAllocator *allocator; /* allocator used in local field */
  using analysisResultKey = std::pair<PhaseIDT, UnitIR*>;
  MapleMap<analysisResultKey, AnalysisResult*> analysisResults;
  MapleMap<PhaseIDT, PhaseT*> analysisPhases;
};

}  // namespace maple
#endif  // MAPLE_PHASE_INCLUDE_PHASE_H
