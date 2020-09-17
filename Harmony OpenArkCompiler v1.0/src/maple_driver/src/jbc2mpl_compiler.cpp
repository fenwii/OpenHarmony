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
#include <cstdlib>
#include "compiler.h"
#include "default_options.h"

namespace maple {
static MplOption kDefaultOptions[] = {};
const std::string Jbc2MplCompiler::GetBinName() const {
  return kBinNameJbc2mpl;
}

const std::vector<std::string> Jbc2MplCompiler::GetBinNames() const {
  auto binNames = std::vector<std::string>();
  binNames.push_back(kBinNameJbc2mpl);
  return binNames;
}

const DefaultOption Jbc2MplCompiler::GetDefaultOptions(const MplOptions &options) {
  DefaultOption defaultOptions;
  if (options.optimizationLevel == kO0 && options.setDefaultLevel) {
    defaultOptions.mplOptions = kJbc2mplDefaultOptionsO0;
    defaultOptions.length = sizeof(kJbc2mplDefaultOptionsO0) / sizeof(MplOption);
  } else {
    defaultOptions.mplOptions = kDefaultOptions;
    defaultOptions.length = sizeof(kDefaultOptions) / sizeof(MplOption);
  }
  return defaultOptions;
}

void Jbc2MplCompiler::GetTmpFilesToDelete(const MplOptions &mplOptions, std::vector<std::string> &tempFiles) const {
  tempFiles.push_back(mplOptions.outputFolder + mplOptions.outputName + ".mpl");
}

const std::unordered_set<std::string> Jbc2MplCompiler::GetFinalOutputs(const MplOptions &mplOptions) const {
  auto finalOutputs = std::unordered_set<std::string>();
  finalOutputs.insert(mplOptions.outputFolder + mplOptions.outputName + ".mpl");
  return finalOutputs;
}

}  // namespace maple
