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
#include "printing.h"
#include <iostream>
#include "mir_module.h"
#include "types_def.h"

constexpr int kIndentunit = 2;  // number of blank chars of each indentation

namespace maple {

std::string const kBlankString = "                                                                                ";

void PrintIndentation(int32 indent) {
  int64 indentAmount = static_cast<int64>(indent) * kIndentunit;
  do {
    LogInfo::MapleLogger() << kBlankString.substr(0, indentAmount);
    indentAmount -= kBlankString.length();
  } while (indentAmount > 0);
}

void PrintString(const std::string &str) {
  uint32 i = 0;
  LogInfo::MapleLogger() << " \"";
  while (i < str.length()) {
    unsigned char c = str[i++];
    // differentiate printable and non-printable charactors
    if (c >= 0x20 && c <= 0x7e) {
      // escape "
      switch (c) {
        case '"':
          LogInfo::MapleLogger() << "\\\"";
          break;
        case '\\':
          LogInfo::MapleLogger() << "\\\\";
          break;
        default:
          LogInfo::MapleLogger() << c;
          break;
      }
    } else {
      LogInfo::MapleLogger() << "\\x" << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)c << std::dec;
    }
  }
  LogInfo::MapleLogger() << "\"";
}

}  // namespace maple
