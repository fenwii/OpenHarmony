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
#ifndef MAPLE_DRIVER_INCLUDE_DRIVER_RUNNER_H
#define MAPLE_DRIVER_INCLUDE_DRIVER_RUNNER_H

#include <vector>
#include <string>
#include "me_option.h"
#include "interleaved_manager.h"


extern const char *kNoFile;
extern const char *kMpl2Mpl;
extern const char *kMe;

namespace maple {


class DriverRunner final {
 public:
  DriverRunner(MIRModule *theModule, const std::vector<std::string> &exeNames, Options *mpl2mplOptions,
               std::string mpl2mplInput, MeOptions *meOptions, std::string meInput, std::string actualInput,
               MemPool *optMp, bool timePhases = false,
               bool genMemPl = false)
      : theModule(theModule),
        exeNames(exeNames),
        mpl2mplOptions(mpl2mplOptions),
        mpl2mplInput(mpl2mplInput),
        meOptions(meOptions),
        meInput(meInput),
        actualInput(actualInput),
        optMp(optMp),
        timePhases(timePhases),
        genMemPl(genMemPl) {
  }

  DriverRunner(MIRModule *theModule, const std::vector<std::string> &exeNames, std::string actualInput, MemPool *optMp,
               bool timePhases = false, bool genVtableImpl = false, bool genMemPl = false)
      : DriverRunner(theModule, exeNames, nullptr, "", nullptr, "", actualInput, optMp, timePhases, genMemPl) {
  }

  ~DriverRunner() {}

  int Run();
  void ReleaseOptions();
  bool ParseInput(std::string outputFile, std::string oriBasename) const;
  void ProcessMpl2mplAndMePhases(std::string outputFile, std::string vtableImplFile) const;

  void SetMpl2mplInfo(Options *mpl2mplOptions, const std::string &mpl2mplInput) {
    this->mpl2mplOptions = mpl2mplOptions;
    this->mpl2mplInput = mpl2mplInput;
  }

  void SetMeInfo(MeOptions *meOptions, const std::string &meInput) {
    this->meOptions = meOptions;
    this->meInput = meInput;
  }


 private:
  MIRModule *theModule;
  std::vector<std::string> exeNames;
  Options *mpl2mplOptions = nullptr;
  std::string mpl2mplInput;
  MeOptions *meOptions = nullptr;
  std::string meInput;
  std::string actualInput;
  MemPool *optMp;
  bool timePhases = false;
  bool genMemPl = false;
  std::string printOutExe;

  static bool FuncOrderLessThan(const MIRFunction *left, const MIRFunction *right);

  bool IsFramework() const;
  std::string GetPostfix() const;
  void InitPhases(InterleavedManager &mgr, std::vector<std::string> &phases) const;
  void AddPhases(InterleavedManager &mgr, std::vector<std::string> &phases, const PhaseManager *phaseManager) const;
  void AddPhase(std::vector<std::string> &phases, std::string phase, const PhaseManager *phaseManager) const;

};

}  // namespace maple

#endif  // MAPLE_DRIVER_INCLUDE_DRIVER_RUNNER_H
