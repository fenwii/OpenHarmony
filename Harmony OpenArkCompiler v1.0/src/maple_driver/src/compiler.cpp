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
#include "compiler.h"
#include <cstdlib>
#include "file_utils.h"
#include "safe_exe.h"
#include "mpl_timer.h"

using namespace mapleOption;
namespace maple {
// build flag -DMAPLE_PRODUCT_EXECUTABLE
#ifndef MAPLE_PRODUCT_EXECUTABLE
#define MAPLE_PRODUCT_EXECUTABLE ""
#endif
const int Compiler::Exe(const MplOptions &mplOptions, const std::string &options) const {
  const std::string binPath = FileUtils::ConvertPathIfNeeded(this->GetBinPath(mplOptions) + this->GetBinName());
  return SafeExe::Exe(binPath, options);
}

const std::string Compiler::GetBinPath(const MplOptions &mplOptions) const {
  auto binPath = std::string(MAPLE_PRODUCT_EXECUTABLE);
  if (binPath.empty()) {
    binPath = mplOptions.exeFolder;
  } else {
    binPath = binPath + FileSeperator::kFileSeperatorChar;
  }
  return binPath;
}

ErrorCode Compiler::Compile(const MplOptions &options, MIRModulePtr &theModule) {
  MPLTimer timer = MPLTimer();
  LogInfo::MapleLogger() << "Starting " << this->GetName() << std::endl;
  timer.Start();
  std::string strOption = this->MakeOption(options);
  if (strOption.empty()) {
    return ErrorCode::kErrorInvalidParameter;
  }
  if (this->Exe(options, strOption) != 0) {
    return ErrorCode::kErrorCompileFail;
  }
  timer.Stop();
  LogInfo::MapleLogger() << this->GetName() + " consumed " << timer.Elapsed() << "s" << std::endl;
  return ErrorCode::kErrorNoError;
}

const std::string Compiler::MakeOption(const MplOptions &options) {
  std::map<std::string, MplOption> finalOptions;
  auto defaultOptions = this->MakeDefaultOptions(options);
  this->AppendDefaultOptions(finalOptions, defaultOptions);
  for (auto binName : this->GetBinNames()) {
    auto userOption = options.options.find(binName);
    if (userOption != options.options.end()) {
      this->AppendUserOptions(finalOptions, userOption->second);
    }
  }
  this->AppendExtraOptions(finalOptions, options.extras);
  std::string strOption = "";
  for (auto finalOption : finalOptions) {
    strOption += " " + finalOption.first + finalOption.second.connectSymbol + finalOption.second.value;
    if (options.debugFlag) {
      LogInfo::MapleLogger() << Compiler::GetName() << " options: " << finalOption.first << " "
                             << finalOption.second.value << std::endl;
    }
  }
  strOption = this->AppendOptimization(options, strOption);
  strOption = this->AppendSpecialOption(options, strOption);
  strOption += " " + this->GetInputFileName(options);
  if (options.debugFlag) {
    LogInfo::MapleLogger() << Compiler::GetName() << " input files: " << this->GetInputFileName(options) << std::endl;
  }
  strOption = FileUtils::ConvertPathIfNeeded(strOption);
  return strOption;
}

void Compiler::AppendDefaultOptions(std::map<std::string, MplOption> &finalOptions,
                                    const std::map<std::string, MplOption> &defaultOptions) const {
  for (auto defaultIt : defaultOptions) {
    finalOptions.insert(make_pair(defaultIt.first, defaultIt.second));
  }
}

void Compiler::AppendUserOptions(std::map<std::string, MplOption> &finalOptions,
                                 const std::vector<Option> userOptions) const {
  for (auto binName : this->GetBinNames()) {
    for (auto userOption : userOptions) {
      auto extra = userOption.FindExtra(binName);
      if (extra != nullptr) {
        AppendOptions(finalOptions, extra->optionKey, userOption.Args(), userOption.ConnectSymbol(binName));
      }
    }
  }
}

void Compiler::AppendExtraOptions(std::map<std::string, MplOption> &finalOptions,
                                  std::map<std::string, std::vector<MplOption>> extraOptions) const {
  auto binNames = this->GetBinNames();
  for (auto binNamesIt : binNames) {
    auto extras = extraOptions.find(binNamesIt);
    if (extras == extraOptions.end()) {
      continue;
    }
    for (auto secondExtras : extras->second) {
      AppendOptions(finalOptions, secondExtras.key, secondExtras.value, secondExtras.connectSymbol);
    }
  }
}

const std::map<std::string, MplOption> Compiler::MakeDefaultOptions(const MplOptions &options) {
  auto rawDefaultOptions = this->GetDefaultOptions(options);
  std::map<std::string, MplOption> defaultOptions;
  if (rawDefaultOptions.mplOptions != nullptr) {
    for (unsigned int i = 0; i < rawDefaultOptions.length; i++) {
      defaultOptions.insert(std::make_pair(rawDefaultOptions.mplOptions[i].key, rawDefaultOptions.mplOptions[i]));
    }
  }
  return defaultOptions;
}

void Compiler::AppendOptions(std::map<std::string, MplOption> &finalOptions, const std::string &key,
                             const std::string &value, const std::string &connectSymbol) const {
  auto finalOpt = finalOptions.find(key);
  if (finalOpt != finalOptions.end()) {
    if (finalOpt->second.isAppend) {
      finalOpt->second.value += finalOpt->second.appendSplit + value;
    } else {
      finalOpt->second.value = value;
    }
  } else {
    MplOption option;
    option.init(key, value, connectSymbol, false, "");
    finalOptions.insert(make_pair(key, option));
  }
}

const bool Compiler::CanAppendOptimization(const std::string &optionStr) const {
  // there're some issues for passing -Ox to each component, let users determine self.
  return false;
}

const std::string Compiler::AppendOptimization(const MplOptions &options, const std::string &optionStr) const {
  if (!CanAppendOptimization(optionStr)) {
    return optionStr;
  }
  return optionStr + " " + options.OptimizationLevelStr();
}

}  // namespace maple
