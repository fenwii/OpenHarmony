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
#include "interleaved_manager.h"
#include <string>
#include <vector>
#include <iomanip>

#include "module_phase.h"
#include "mir_function.h"
#include "mir_module.h"
#include "me_function.h"
#include "me_option.h"
#include "mempool.h"
#include "phase_manager.h"

using namespace maple;

void InterleavedManager::AddPhases(std::vector<std::string> &phases, bool isModulePhase, bool timePhases, bool genMpl) {
  ModuleResultMgr *mrm = nullptr;
  if (!phaseManagers.empty()) {
    // ModuleResult such class hierarchy need to be carried on
    ModulePhaseManager *mpm = dynamic_cast<ModulePhaseManager*>(phaseManagers[phaseManagers.size() - 1]);
    MeFuncPhaseManager *mepm = dynamic_cast<MeFuncPhaseManager*>(phaseManagers[phaseManagers.size() - 1]);
    if (mpm != nullptr) {
      mrm = mpm->GetModResultMgr();
    } else if (mepm != nullptr) {
      mrm = mepm->GetModResultMgr();
    }
  }

  if (isModulePhase) {
    ModulePhaseManager *mpm = GetMempool()->New<ModulePhaseManager>(GetMempool(), mirModule, mrm);
    mpm->RegisterModulePhases();
    mpm->AddModulePhases(phases);
    if (timePhases) {
      mpm->SetTimePhases(true);
    }
    phaseManagers.push_back(mpm);
  } else {  // MeFuncPhase
    MeFuncPhaseManager *fpm = GetMempool()->New<MeFuncPhaseManager>(GetMempool(), mirModule, mrm);
    fpm->RegisterFuncPhases();
    if (genMpl) {
      fpm->SetGenMempool(true);
    }
    if (timePhases) {
      fpm->SetTimePhases(true);
    }
    fpm->AddPhasesNoDefault(phases);
    phaseManagers.push_back(fpm);
  }
}

void InterleavedManager::Run() {
  for (PhaseManager * const &pm : phaseManagers) {
    if (pm == nullptr) {
      continue;
    }
    if (dynamic_cast<MeFuncPhaseManager*>(pm)) {
      MeFuncPhaseManager *fpm = static_cast<MeFuncPhaseManager*>(pm);
      unsigned long rangeNum = 0;
      MapleVector<MIRFunction*> *compList;
      if (!mirModule.GetCompilationList().empty()) {
        if ((mirModule.GetCompilationList().size() != mirModule.GetFunctionList().size() &&
             mirModule.GetCompilationList().size() !=
                 mirModule.GetFunctionList().size() - mirModule.GetOptFuncsSize())) {
          ASSERT(false, "should be equal");
        }
        compList = &mirModule.GetCompilationList();
      } else {
        compList = &mirModule.GetFunctionList();
      }
      for (MIRFunction *func : *compList) {
        if (MeOptions::useRange && (rangeNum < MeOptions::range[0] || rangeNum > MeOptions::range[1])) {
          rangeNum++;
          continue;
        }
        if (func->GetBody() == nullptr) {
          rangeNum++;
          continue;
        }
        if (fpm->GetPhaseSequence()->empty()) {
          continue;
        }
        mirModule.SetCurFunction(func);
        // lower, create BB and build cfg
        fpm->Run(func, rangeNum, meInput);
        rangeNum++;
      }
      if (fpm->GetGenMempool()) {
        mirModule.Emit("comb.me.mpl");
      }
    } else {
      pm->Run();
    }
  }
}

void InterleavedManager::DumpTimers() {
  std::ios_base::fmtflags f(LogInfo::MapleLogger().flags());
  std::vector<std::pair<std::string, time_t>> timeVec;
  long total = 0;
  LogInfo::MapleLogger() << "=================== TIMEPHASES =================\n";
  for (auto manager : phaseManagers) {
    long temp = manager->DumpTimers();
    total += temp;
    timeVec.push_back(std::pair<std::string, time_t>(manager->GetMgrName(), temp));
    LogInfo::MapleLogger() << "================================================\n";
  }
  LogInfo::MapleLogger() << "==================== SUMMARY ===================\n";
  CHECK_FATAL(total != 0, "calculation check");
  for (const auto &lapse : timeVec) {
    LogInfo::MapleLogger() << std::left << std::setw(25) << lapse.first << std::setw(10) << std::right << std::fixed
                           << std::setprecision(2) << (100.0 * lapse.second / total) << "%" << std::setw(10)
                           << (lapse.second / 1000) << "ms" << std::endl;
  }
  LogInfo::MapleLogger() << "================================================\n";
  LogInfo::MapleLogger().flags(f);
}

void InterleavedManager::InitSupportPhaseManagers() {
  ASSERT(supportPhaseManagers.empty(), "Phase managers already initialized");

  ModuleResultMgr *mrm = nullptr;

  ModulePhaseManager *mpm = GetMempool()->New<ModulePhaseManager>(GetMempool(), mirModule, mrm);
  mpm->RegisterModulePhases();
  supportPhaseManagers.push_back(mpm);

  mrm = mpm->GetModResultMgr();

  MeFuncPhaseManager *fpm = GetMempool()->New<MeFuncPhaseManager>(GetMempool(), mirModule, mrm);
  fpm->RegisterFuncPhases();
  supportPhaseManagers.push_back(fpm);
}

const PhaseManager *InterleavedManager::GetSupportPhaseManager(const std::string &phase) {
  if (supportPhaseManagers.empty()) {
    InitSupportPhaseManagers();
  }

  for (auto pm : supportPhaseManagers) {
    if (pm->ExistPhase(phase)) {
      return pm;
    }
  }

  return nullptr;
}
