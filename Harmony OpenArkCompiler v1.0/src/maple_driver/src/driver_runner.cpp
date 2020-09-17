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
#include "driver_runner.h"
#include <iostream>
#include <typeinfo>
#include <sys/stat.h>
#include "mpl_timer.h"
#include "mir_function.h"
#include "mir_parser.h"

const char *kNoFile = "nofile";
const char *kMpl2Mpl = "mpl2mpl";
const char *kMe = "me";

#define JAVALANG (theModule->IsJavaModule())

#define CHECK_MODULE(errorCode...)                                              \
  do {                                                                          \
    if (theModule == nullptr) {                                                 \
      LogInfo::MapleLogger() << "Fatal error: the module is null" << std::endl; \
      return errorCode;                                                         \
    }                                                                           \
  } while (0)

#define RELEASE(pointer)      \
  do {                        \
    if (pointer != nullptr) { \
      delete pointer;         \
      pointer = nullptr;      \
    }                         \
  } while (0)

#define ADD_PHASE(name, condition)       \
  if ((condition)) {                     \
    phases.push_back(std::string(name)); \
  }

#define ADD_EXTRA_PHASE(name, timephases, timeStart)                                                    \
  if (timephases) {                                                                                     \
    auto duration = std::chrono::system_clock::now() - timeStart;                                       \
    extraPhasesTime.push_back(std::chrono::duration_cast<std::chrono::microseconds>(duration).count()); \
    extraPhasesName.push_back(name);                                                                    \
  }

namespace maple {

int DriverRunner::Run() {
  CHECK_MODULE(1);

  if (exeNames.empty()) {
    LogInfo::MapleLogger() << "Fatal error: no exe specified" << std::endl;
    return 1;
  }

  int ret = 0;
  printOutExe = exeNames[exeNames.size() - 1];

  // Prepare output file
  std::string::size_type lastdot = actualInput.find_last_of(".");
  std::string baseName = lastdot == std::string::npos ? actualInput : actualInput.substr(0, lastdot);
  std::string originBaseName = baseName;
  std::string outputFile = baseName.append(GetPostfix());

  bool parsed = ParseInput(outputFile, originBaseName);

  if (parsed) {
    if (mpl2mplOptions || meOptions) {
      std::string vtableImplFile = originBaseName;
      vtableImplFile.append(".VtableImpl.mpl");
      originBaseName.append(".VtableImpl");
      ProcessMpl2mplAndMePhases(outputFile, vtableImplFile);
    }

  } else {
    ret = 1;
  }

  return ret;
}

void DriverRunner::ReleaseOptions() {
  RELEASE(mpl2mplOptions);
  RELEASE(meOptions);
}

bool DriverRunner::FuncOrderLessThan(const MIRFunction *left, const MIRFunction *right) {
  return left->GetLayoutType() < right->GetLayoutType();
}

bool DriverRunner::IsFramework() const {
  return false;
}

std::string DriverRunner::GetPostfix() const {
  std::string postFix;

  if (printOutExe == kMe) {
    postFix = ".me.mpl";
  } else if (printOutExe == kMpl2Mpl) {
    postFix = ".VtableImpl.mpl";
  } else {
  }

  return postFix;
}

bool DriverRunner::ParseInput(std::string outputFile, std::string originBaseName) const {
  CHECK_MODULE(1);

  LogInfo::MapleLogger() << "Starting parse input" << std::endl;
  MPLTimer timer;
  timer.Start();

  MIRParser parser(*theModule);
  bool parsed = parser.ParseMIR(0, 0, false, true);
  if (!parsed) {
    parser.EmitError(outputFile);
  }
  timer.Stop();
  LogInfo::MapleLogger() << "Parse consumed " << timer.Elapsed() << "s" << std::endl;

  return parsed;
}

void DriverRunner::ProcessMpl2mplAndMePhases(std::string outputFile, std::string vtableImplFile) const {
  CHECK_MODULE();

  if (mpl2mplOptions || meOptions) {
    LogInfo::MapleLogger() << "Processing mpl2mpl&mplme" << std::endl;
    MPLTimer timer;
    timer.Start();

    InterleavedManager mgr(optMp, theModule, meInput, timePhases);
    std::vector<std::string> phases;
#include "phases.def"
    InitPhases(mgr, phases);
    mgr.Run();

    theModule->Emit(vtableImplFile);

    timer.Stop();
    LogInfo::MapleLogger() << "Mpl2mpl&mplme consumed " << timer.Elapsed() << "s" << std::endl;
  }
}

void DriverRunner::InitPhases(InterleavedManager &mgr, std::vector<std::string> &phases) const {
  if (phases.empty()) {
    return;
  }

  const PhaseManager *curManager = nullptr;
  std::vector<std::string> curPhases;

  for (std::string phase : phases) {
    auto temp = mgr.GetSupportPhaseManager(phase);

    if (temp != nullptr) {
      if (temp != curManager) {
        AddPhases(mgr, curPhases, curManager);
        curManager = temp;
        curPhases.clear();
      }

      AddPhase(curPhases, phase, curManager);
    }
  }

  AddPhases(mgr, curPhases, curManager);
}

void DriverRunner::AddPhases(InterleavedManager &mgr, std::vector<std::string> &phases,
                             const PhaseManager *phaseManager) const {
  if (phaseManager == nullptr) {
    return;
  }

  if (typeid(*phaseManager) == typeid(ModulePhaseManager)) {
    mgr.AddPhases(phases, true, timePhases);
  } else if (typeid(*phaseManager) == typeid(MeFuncPhaseManager)) {
    mgr.AddPhases(phases, false, timePhases, genMemPl);
  } else {
    CHECK_FATAL(false, "Should not reach here, phases should be handled");
  }
}

void DriverRunner::AddPhase(std::vector<std::string> &phases, std::string phase,
                            const PhaseManager *phaseManager) const {
  CHECK_FATAL(phaseManager != nullptr, "Invalid phase manager");

  if (typeid(*phaseManager) == typeid(ModulePhaseManager)) {
    if (mpl2mplOptions && Options::skipPhase.compare(phase) != 0) {
      phases.push_back(phase);
    }
  } else if (typeid(*phaseManager) == typeid(MeFuncPhaseManager)) {
    if (meOptions && meOptions->GetSkipPhases().find(phase) == meOptions->GetSkipPhases().end()) {
      phases.push_back(phase);
    }
  } else {
    CHECK_FATAL(false, "Should not reach here, phase should be handled");
  }
}


}  // namespace maple
