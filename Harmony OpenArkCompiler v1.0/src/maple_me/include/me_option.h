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
#ifndef MAPLE_ME_INCLUDE_ME_OPTION_H
#define MAPLE_ME_INCLUDE_ME_OPTION_H
#include <vector>
#include "mempool.h"
#include "mempool_allocator.h"
#include "types_def.h"

namespace maple {
class MeOptions {
 public:
  explicit MeOptions(MemPool *memPool) : optionAlloc(memPool) {}

  void ParseOptions(int argc, char **argv, std::string &fileName);
  ~MeOptions() {}

  void DumpUsage();
  static bool DumpPhase(const std::string &phase);
  static std::unordered_set<std::string> dumpPhases;
  static bool dumpAfter;
  static unsigned long range[2];
  static bool useRange;
  static std::string dumpFunc;
  static bool quiet;
  static bool setCalleeHasSideEffect;
  static bool noSteensgaard;
  static bool noTBAA;
  static uint8 aliasAnalysisLevel;
  static bool noDot;
  static bool stmtNum;
  static uint8 optLevel;
  static bool ignoreIPA;
  static bool lessThrowAlias;
  static bool finalFieldAlias;
  static bool regreadAtReturn;
  void SplitPhases(const char *str, std::unordered_set<std::string> &set);
  void GetRange(const char *str);

  std::unordered_set<std::string> &GetSkipPhases() {
    return skipPhases;
  }

 private:
  std::unordered_set<std::string> skipPhases;
  MapleAllocator optionAlloc;
};

#ifndef DEBUGFUNC
#define DEBUGFUNC(f)                                                         \
  (MeOptions::dumpPhases.find(PhaseName()) != MeOptions::dumpPhases.end() && \
   (MeOptions::dumpFunc.compare("*") == 0 || f->GetName().find(MeOptions::dumpFunc.c_str()) != std::string::npos))
#endif

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ME_OPTION_H
