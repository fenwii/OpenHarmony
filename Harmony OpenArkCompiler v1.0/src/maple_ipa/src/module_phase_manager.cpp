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
#include "module_phase_manager.h"
#include "class_hierarchy.h"
#include "class_init.h"
#include "option.h"
#if MIR_JAVA
#include "native_stub_func.h"
#include "vtable_analysis.h"
#include "reflection_analysis.h"
#include "vtable_impl.h"
#include "java_intrn_lowering.h"
#include "java_eh_lower.h"
#include "native_stub_func.h"
#include "muid_replacement.h"
#include "gen_check_cast.h"
#endif
#include "bin_mpl_export.h"
#include "mpl_timer.h"

namespace maple {
// Manage the phases of middle and implement some maplecomb-options such as
// skipAfter, skipFrom, quiet.
AnalysisResult *DoKlassHierarchy::Run(MIRModule *module, ModuleResultMgr *m) {
  MemPool *memPool = mempoolctrler.NewMemPool("classhierarchy mempool");
  KlassHierarchy *kh = memPool->New<KlassHierarchy>(module, memPool);
  KlassHierarchy::traceFlag = TRACE_PHASE;
  kh->BuildHierarchy();
#if MIR_JAVA
  if (!Options::skipVirtualMethod)
#endif
    kh->CountVirtualMethods();
  if (KlassHierarchy::traceFlag) {
    kh->Dump();
  }
  m->AddResult(GetPhaseID(), module, kh);
  return kh;
}

void ModulePhaseManager::RegisterModulePhases() {
#define MODAPHASE(id, modphase)                                                    \
  do {                                                                             \
    MemPool *memPool = GetMemPool();                                               \
    ModulePhase *phase = new (memPool->Malloc(sizeof(modphase(id)))) modphase(id); \
    CHECK_FATAL(phase != nullptr, "null ptr check ");                              \
    RegisterPhase(id, phase);                                                      \
    arModuleMgr->AddAnalysisPhase(id, phase);                                      \
  } while (0);
#define MODTPHASE(id, modphase)                                                    \
  do {                                                                             \
    MemPool *memPool = GetMemPool();                                               \
    ModulePhase *phase = new (memPool->Malloc(sizeof(modphase(id)))) modphase(id); \
    CHECK_FATAL(phase != nullptr, "null ptr check ");                              \
    RegisterPhase(id, phase);                                                      \
  } while (0);
#include "module_phases.def"
#undef MODAPHASE
#undef MODTPHASE
}

void ModulePhaseManager::AddModulePhases(std::vector<std::string> &phases) {
  for (std::string const &phase : phases) {
    AddPhase(phase.c_str());
  }
}

void ModulePhaseManager::RunModulePhases() const {}

void ModulePhaseManager::Run() {
  int phaseIndex = 0;
  for (auto it = PhaseSequenceBegin(); it != PhaseSequenceEnd(); it++, ++phaseIndex) {
    PhaseID id = GetPhaseId(it);
    ModulePhase *p = static_cast<ModulePhase*>(GetPhase(id));
    MIR_ASSERT(p);
    // if we need to skip after certain pass
    if (Options::skipFrom.compare(p->PhaseName()) == 0) {
      break;
    }
    if (!Options::quiet) {
      LogInfo::MapleLogger() << "---Run Module Phase [ " << p->PhaseName() << " ]---\n";
    }
    MPLTimer timer;
    if (timePhases) {
      timer.Start();
    }
    p->Run(&mirModule, arModuleMgr);
    if (timePhases) {
      timer.Stop();
      phaseTimers[phaseIndex] += timer.ElapsedMicroseconds();
    }
    if (Options::skipAfter.compare(p->PhaseName()) == 0) {
      break;
    }
  }
}

void ModulePhaseManager::Emit(const char *passName) {
  // Form output file name.
  std::string outFileName;
  std::string moduleFileName = mirModule.GetFileName();
  std::string::size_type lastDot = moduleFileName.find_last_of(kDotStr);
  if (lastDot == std::string::npos) {
    outFileName = moduleFileName + kDotStr;
  } else {
    outFileName = moduleFileName.substr(0, lastDot) + kDotStr;
  }
  outFileName = outFileName.append(passName);
  outFileName = outFileName.append(kDotMplStr);
  mirModule.DumpToFile(outFileName);
}

}  // namespace maple
