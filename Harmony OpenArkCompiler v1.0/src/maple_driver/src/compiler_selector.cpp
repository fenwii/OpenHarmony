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
#include "compiler_selector.h"
#include "mpl_logging.h"

#include <algorithm>

namespace maple {
Compiler *CompilerSelectorImpl::FindCompiler(const SupportedCompilers &compilers, const std::string name) const {
  auto compiler = compilers.find(name);
  if (compiler != compilers.end()) {
    return compiler->second;
  }
  return nullptr;
}

const ErrorCode CompilerSelectorImpl::InsertCompilerIfNeeded(std::vector<Compiler*> &selected,
                                                             const SupportedCompilers &compilers,
                                                             const std::string name) const {
  Compiler *compiler = FindCompiler(compilers, name);
  if (compiler != nullptr) {
    if (std::find(selected.cbegin(), selected.cend(), compiler) == selected.cend()) {
      selected.push_back(compiler);
    }
  } else {
    LogInfo::MapleLogger(kLlErr) << name << " not found!!!" << std::endl;
    return ErrorCode::kErrorToolNotFound;
  }
  return ErrorCode::kErrorNoError;
}

const ErrorCode CompilerSelectorImpl::Select(const SupportedCompilers &supportedCompilers, const MplOptions &mplOptions,
                                             std::vector<Compiler*> &selected) const {
  bool combPhases = false;
  int ret = ErrorCode::kErrorNoError;
  if (!mplOptions.runningExes.empty()) {
    for (auto runningExe : mplOptions.runningExes) {
      if (runningExe == kBinNameMe) {
        combPhases = true;
      } else if (runningExe == kBinNameMpl2mpl && combPhases) {
        continue;
      }
      ret = InsertCompilerIfNeeded(selected, supportedCompilers, runningExe);
      if (ret != ErrorCode::kErrorNoError) {
        return ErrorCode::kErrorToolNotFound;
      }
    }
  }
  return selected.empty() ? ErrorCode::kErrorToolNotFound : ErrorCode::kErrorNoError;
}

}  // namespace maple
