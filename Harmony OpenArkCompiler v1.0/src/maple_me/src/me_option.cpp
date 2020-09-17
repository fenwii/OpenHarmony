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
#include "me_option.h"
#include <iostream>
#include <cstring>
#include "mpl_logging.h"
#include "option_parser.h"
#include "string_utils.h"

using namespace maple;
using namespace mapleOption;

std::unordered_set<std::string> MeOptions::dumpPhases = {};
bool MeOptions::dumpAfter = false;
std::string MeOptions::dumpFunc = "*";
unsigned long MeOptions::range[2] = { 0, 0 };
bool MeOptions::useRange = false;
bool MeOptions::quiet = false;
bool MeOptions::setCalleeHasSideEffect = false;
bool MeOptions::noSteensgaard = false;
bool MeOptions::noTBAA = false;
uint8 MeOptions::aliasAnalysisLevel = 3;
bool MeOptions::noDot = false;
bool MeOptions::stmtNum = false;
uint8 MeOptions::optLevel = 0;
bool MeOptions::ignoreIPA = true;
bool MeOptions::lessThrowAlias = true;
bool MeOptions::finalFieldAlias = false;
bool MeOptions::regreadAtReturn = true;

void MeOptions::SplitPhases(const char *str, std::unordered_set<std::string> &set) {
  std::string s{str};

  if (s.compare("*") == 0) {
    set.insert(s);
    return;
  }
  StringUtils::Split(s, set, ',');
}

void MeOptions::GetRange(const char *str) {
  std::string s = str;
  size_t comma = s.find_first_of(",", 0);
  if (comma != std::string::npos) {
    range[0] = std::stoul(s.substr(0, comma), nullptr);
    range[1] = std::stoul(s.substr(comma + 1, std::string::npos - (comma + 1)), nullptr);
  }
  if (range[0] > range[1]) {
    LogInfo::MapleLogger(kLlErr) << "invalid values for --range=" << range[0] << "," << range[1] << std::endl;
    ASSERT(false, "GetRange exit");
  }
}

bool MeOptions::DumpPhase(const std::string &phase) {
  if (phase == "") {
    return false;
  }
  return ((dumpPhases.find(phase) != dumpPhases.end()) || (dumpPhases.find("*") != dumpPhases.end()));
}
