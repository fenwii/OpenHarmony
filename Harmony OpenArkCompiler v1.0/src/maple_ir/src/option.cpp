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
#include "option.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include "mpl_logging.h"
#include "option_parser.h"

using namespace maple;
using namespace mapleOption;

bool Options::dumpBefore = false;
bool Options::dumpAfter = false;
std::string Options::dumpPhase = "*";
std::string Options::dumpFunc = "*";
std::string Options::skipPhase;
std::string Options::skipFrom;
std::string Options::skipAfter;
bool Options::quiet = false;
bool Options::regNativeFunc = false;
bool Options::nativeWrapper = true;  // enabled by default
bool Options::regNativeDynamicOnly = false;
std::string Options::staticBindingList;
bool Options::usePreg = false;
bool Options::mapleLinker = false;
bool Options::dumpMuidFile = false;
bool Options::emitVtableImpl = false;
#if MIR_JAVA
bool Options::skipVirtualMethod = false;
#endif
enum OptionIndex {
  kUnknown,
  kHelp,
  kDumpPhase,
  kSkipPhase,
  kSkipFrom,
  kSkipAfter,
  kDumpFunc,
  kQuiet,
  kStubJniFunc,
  kRegNativeDynamicOnly,
  kRegNativeStaticBindingList,
  kNativeWrapper,
  kDumpBefore,
  kDumpAfter,
  kSkipVirtual,
  kMapleLinker,
  kMplnkDumpMuid,
  kEmitVtableImpl,
};

const Descriptor kUsage[] = {
  { kUnknown, 0, "", "", kBuildTypeAll, kArgCheckPolicyUnknown,
    "USAGE:  mplxxx [options] *.mpl\n\n"
    "OPTIONS:" },
  { kHelp, 0, "h", "help", kBuildTypeAll, kArgCheckPolicyNone,
    "  -h, --help                        Print usage and exit" },
  { kDumpPhase, 0, "", "dump-phase", kBuildTypeAll, kArgCheckPolicyRequired,
    "  --dump-phase=PHASENAME            Enable debug trace for specified phase (can only specify once)" },
  { kSkipPhase, 0, "", "skip-phase", kBuildTypeAll, kArgCheckPolicyRequired,
    "  --skip-phase=PHASENAME            Skip the phase when adding it to phase manager" },
  { kSkipFrom, 0, "", "skip-from", kBuildTypeAll, kArgCheckPolicyRequired,
    "  --skip-from=PHASENAME             Skip all remaining phases including PHASENAME" },
  { kSkipAfter, 0, "", "skip-after", kBuildTypeAll, kArgCheckPolicyRequired,
    "  --skip-after=PHASENAME            Skip all remaining phases after PHASENAME" },
  { kDumpFunc, 0, "", "dump-func", kBuildTypeAll, kArgCheckPolicyRequired,
    "  --dump-func=FUNCNAME              Dump/trace only for functions whose names contain FUNCNAME as substring\n"
    "                                    (can only specify once)" },
  { kQuiet, 0, "", "quiet", kBuildTypeAll, kArgCheckPolicyNone,
    "  --quiet                           Disable brief trace messages with phase/function names" },
  { kStubJniFunc, 0, "", "regnativefunc", kBuildTypeAll, kArgCheckPolicyNone,
    "  --regnativefunc                   Generate native stub function to support JNI registration and calling" },
  { kNativeWrapper, 1, "", "nativewrapper", kBuildTypeAll, kArgCheckPolicyNone,
    "  --nativewrapper                   Generate native wrappers [default]" },
  { kNativeWrapper, 0, "", "no-nativewrapper", kBuildTypeAll, kArgCheckPolicyNone,
    "  --no-nativewrapper                Do not generate native wrappers" },
  { kRegNativeDynamicOnly, 0, "", "regnative-dynamic-only", kBuildTypeAll, kArgCheckPolicyNone,
    "  --regnative-dynamic-only          Only Generate dynamic register code, Report Fatal Msg if no implemented" },
  { kRegNativeStaticBindingList, 0, "", "static-binding-list", kBuildTypeAll, kArgCheckPolicyRequired,
    "  --static-bindig-list=file         Only Generate static binding function in file configure list" },
  { kDumpBefore, 0, "", "dump-before", kBuildTypeAll, kArgCheckPolicyNone,
    "  --dump-before                     Do extra IR dump before the specified phase" },
  { kDumpAfter, 0, "", "dump-after", kBuildTypeAll, kArgCheckPolicyNone,
    "  --dump-after                      Do extra IR dump after the specified phase" },
  { kMapleLinker, 0, "", "maplelinker", kBuildTypeAll, kArgCheckPolicyNone,
    "  --maplelinker                     Generate MUID symbol tables and references" },
  { kMplnkDumpMuid, 0, "", "dump-muid", kBuildTypeAll, kArgCheckPolicyNone,
    "  --dump-muid                       Dump MUID def information into a .muid file" },
  { kEmitVtableImpl, 0, "", "emitVtableImpl", kBuildTypeAll, kArgCheckPolicyNone,
    "  --emitVtableImpl                  Generate VtableImpl file" },
#if MIR_JAVA
  { kSkipVirtual, 0, "", "skipvirtual", kBuildTypeAll, kArgCheckPolicyNone, "  --skipvirtual" },
#endif
  { 0, 0, nullptr, nullptr, kBuildTypeAll, kArgCheckPolicyNone, nullptr }
};

bool Options::ParseOptions(int argc, char **argv, std::string &fileName) {
  bool result = true;
  OptionParser optionParser(kUsage);
  int ret = optionParser.Parse(argc, argv);
  CHECK_FATAL(ret == ErrorCode::kErrorNoError, "option parser error");
  for (auto opt : optionParser.GetOptions()) {
    switch (opt.Index()) {
      case kHelp: {
        if (opt.Args().empty()) {
          optionParser.PrintUsage();
          result = false;
        }
        break;
      }
      case kDumpBefore:
        Options::dumpBefore = true;
        break;
      case kDumpAfter:
        Options::dumpAfter = true;
        break;
      case kDumpFunc:
        Options::dumpFunc = opt.Args();
        break;
      case kDumpPhase:
        Options::dumpPhase = opt.Args();
        break;
      case kSkipPhase:
        Options::skipPhase = opt.Args();
        break;
      case kSkipFrom:
        Options::skipFrom = opt.Args();
        break;
      case kSkipAfter:
        Options::skipAfter = opt.Args();
        break;
      case kQuiet:
        Options::quiet = true;
        break;
      case kRegNativeDynamicOnly:
        Options::regNativeDynamicOnly = true;
        break;
      case kRegNativeStaticBindingList:
        Options::staticBindingList = opt.Args();
        break;
      case kStubJniFunc:
        Options::regNativeFunc = true;
        break;
      case kNativeWrapper:
        Options::nativeWrapper = opt.Type();
        break;
      case kMapleLinker:
        Options::mapleLinker = true;
        Options::dumpMuidFile = false;
        break;
      case kMplnkDumpMuid:
        Options::dumpMuidFile = true;
        break;
      case kEmitVtableImpl:
        Options::emitVtableImpl = true;
        break;
#if MIR_JAVA
      case kSkipVirtual:
        Options::skipVirtualMethod = true;
        break;
#endif
      default:
        result = false;
        ASSERT(false, "unhandled case in Options");
    }
  }

  if (result) {
    if (optionParser.GetNonOptionsCount() != 1) {
      LogInfo::MapleLogger(kLlErr) << "expecting one .mpl file as last argument, found: ";
      for (const auto &optionArg : optionParser.GetNonOptions()) {
        LogInfo::MapleLogger(kLlErr) << optionArg << " ";
      }
      LogInfo::MapleLogger(kLlErr) << std::endl;
      result = false;
    }

    if (result) {
      fileName = optionParser.GetNonOptions().front();
    }
  }
  return result;
}

void Options::DumpOptions() {
  LogInfo::MapleLogger() << "phase sequence : \t";
  if (phaseSeq.empty()) {
    LogInfo::MapleLogger() << "default phase sequence\n";
  } else {
    for (size_t i = 0; i < phaseSeq.size(); i++) {
      LogInfo::MapleLogger() << " " << phaseSeq[i].c_str();
    }
  }
  LogInfo::MapleLogger() << std::endl;
}
