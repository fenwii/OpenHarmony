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
#ifndef MAPLE_IPA_INCLUDE_MODULE_PHASE_MANAGER_H
#define MAPLE_IPA_INCLUDE_MODULE_PHASE_MANAGER_H
#include "module_phase.h"
#include "me_phase_manager.h"

static constexpr char kDotStr[] = ".";
static constexpr char kDotMplStr[] = ".mpl";

namespace maple {
class DoKlassHierarchy : public ModulePhase {
 public:
  explicit DoKlassHierarchy(ModulePhaseID id) : ModulePhase(id) {}

  AnalysisResult *Run(MIRModule *module, ModuleResultMgr *m) override;
  std::string PhaseName() const override {
    return "classhierarchy";
  }

  virtual ~DoKlassHierarchy(){};
};

class ModulePhaseManager : public PhaseManager {
 public:
  ModulePhaseManager(MemPool *memPool, MIRModule &mod, ModuleResultMgr *mrm = nullptr)
      : PhaseManager(memPool, "modulephase"), mirModule(mod) {
    if (mrm != nullptr) {
      arModuleMgr = mrm;
    } else {
      arModuleMgr = memPool->New<ModuleResultMgr>(GetMemAllocator());
    }
    timePhases = false;
  }

  ~ModulePhaseManager() {}

  // register all module phases defined in module_phases.def
  void RegisterModulePhases();
  // Add module phases which are going to be run
  void AddModulePhases(std::vector<std::string> &phases);
  void RunModulePhases() const;
  ModuleResultMgr *GetModResultMgr() {
    return arModuleMgr;
  }

  void SetTimePhases(bool val) {
    timePhases = val;
  }

  void Run() override;
  void Emit(const char *passName);

 private:
  bool timePhases;
  MIRModule &mirModule;
  ModuleResultMgr *arModuleMgr; /* module level analysis result */
};

}  // namespace maple
#endif  // MAPLE_IPA_INCLUDE_MODULE_PHASE_MANAGER_H
