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


using namespace maple;

static MplOption kDefaultOptions[] = {};

const DefaultOption MplcgCompiler::GetDefaultOptions(const MplOptions &options) {
  DefaultOption defaultOptions;
  if (options.optimizationLevel == kO0 && options.setDefaultLevel) {
    defaultOptions.mplOptions = kMplcgDefaultOptionsO0;
    defaultOptions.length = sizeof(kMplcgDefaultOptionsO0) / sizeof(MplOption);
  }
  else {
    defaultOptions.mplOptions = kDefaultOptions;
    defaultOptions.length = sizeof(kDefaultOptions) / sizeof(MplOption);
  }
  return defaultOptions;
}

const std::string MplcgCompiler::GetBinName() const {
  return kBinNameMplcg;
}

const std::vector<std::string> MplcgCompiler::GetBinNames() const {
  auto binNames = std::vector<std::string>();
  binNames.push_back(kBinNameMplcg);
  return binNames;
}

const std::string MplcgCompiler::GetInputFileName(const MplOptions &options) const {
  std::string::size_type idx = options.outputName.find(".VtableImpl");
  std::string outputName = options.outputName;
  if (idx != std::string::npos) {
    outputName = options.outputName.substr(0, idx);
  }
  return options.outputFolder + outputName + ".VtableImpl.mpl";
}

