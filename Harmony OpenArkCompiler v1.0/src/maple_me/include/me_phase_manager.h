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
#ifndef MAPLE_ME_INCLUDE_ME_PHASE_MANAGER_H
#define MAPLE_ME_INCLUDE_ME_PHASE_MANAGER_H
#include <vector>
#include <string>
#include "mempool.h"
#include "mempool_allocator.h"
#include "phase_manager.h"
#include "mir_module.h"
#include "me_phase.h"

namespace maple {
enum MePhaseType { kMePhaseInvalid, kMePhaseMainopt, kMePhaseLno };

/* driver of Me */
class MeFuncPhaseManager : public PhaseManager {
 public:
  MeFuncPhaseManager(MemPool *memPool, MIRModule &mod, ModuleResultMgr *mrm = nullptr)
      : PhaseManager(memPool, "mephase"),
        arFuncManager(GetMemAllocator()),
        mirModule(mod),
        modResMgr(mrm),
        mePhaseType(kMePhaseInvalid),
        genMempool(false),
        timePhases(false) {}

  ~MeFuncPhaseManager() {
    arFuncManager.InvalidAllResults();
  }

  void RunFuncPhase(MeFunction *func, MeFuncPhase *phase);
  void RegisterFuncPhases();
  void AddPhases(std::unordered_set<std::string> &skipPhases);
  void AddPhasesNoDefault(std::vector<std::string> &phases);
  void SetMePhase(MePhaseType mephase) {
    mePhaseType = mephase;
  }

  void SetModResMgr(ModuleResultMgr *mrm) {
    modResMgr = mrm;
  }

  void Run(MIRFunction *mirfunc, uint64 rangenum, const std::string &meinput);
  void Run() override {}

  MeFuncResultMgr *GetAnalysisResultManager(void) {
    return &arFuncManager;
  }

  ModuleResultMgr *GetModResultMgr() {
    return modResMgr;
  }

  bool FuncFilter(const std::string &filter, const std::string &name);

  bool GetGenMempool() {
    return genMempool;
  }

  void SetGenMempool(bool pl) {
    genMempool = pl;
  }

  void SetTimePhases(bool phs) {
    timePhases = phs;
  }

 private:
  /* analysis phase result manager */
  MeFuncResultMgr arFuncManager;
  MIRModule &mirModule;
  ModuleResultMgr *modResMgr;
  MePhaseType mePhaseType;
  bool genMempool;
  bool timePhases;
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ME_PHASE_MANAGER_H
