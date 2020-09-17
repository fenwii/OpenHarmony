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
#include "compiler_factory.h"
#include <regex>
#include "file_utils.h"
#include "string_utils.h"
#include "mpl_logging.h"

using namespace maple;
#define ADD_COMPILER(NAME, CLASSNAME)        \
  do {                                       \
    Insert((NAME), new (CLASSNAME)((NAME))); \
  } while (0);
CompilerFactory &CompilerFactory::GetInstance() {
  static CompilerFactory instance;
  return instance;
}

CompilerFactory::CompilerFactory() : theModule(nullptr) {
#include "supported_compilers.def"
  compilerSelector = new CompilerSelectorImpl();
}

CompilerFactory::~CompilerFactory() {
  auto it = supportedCompilers.begin();
  while (it != supportedCompilers.end()) {
    if (it->second != nullptr) {
      delete it->second;
      it->second = nullptr;
    }
    it++;
  }
  supportedCompilers.clear();
  if (compilerSelector != nullptr) {
    delete compilerSelector;
    compilerSelector = nullptr;
  }
  if (theModule != nullptr) {
    delete theModule;
    theModule = nullptr;
  }
}

void CompilerFactory::Insert(const std::string &name, Compiler *value) {
  supportedCompilers.insert(make_pair(name, value));
}

ErrorCode CompilerFactory::DeleteTmpFiles(const MplOptions &mplOptions, const std::vector<std::string> &tempFiles,
                                          const std::unordered_set<std::string> &finalOutputs) const {
  int ret = 0;
  for (auto tmpFile : tempFiles) {
    bool isSave = false;
    for (auto saveFile : mplOptions.saveFiles) {
      if (!saveFile.empty() && std::regex_match(tmpFile, std::regex(StringUtils::Replace(saveFile, "*", ".*?")))) {
        isSave = true;
        break;
      }
    }
    if (!isSave && mplOptions.inputFiles.find(tmpFile) == std::string::npos &&  // not input
        (finalOutputs.find(tmpFile) == finalOutputs.end())) {                   // not output
      ret = FileUtils::Remove(tmpFile);
    }
  }
  return ret == 0 ? ErrorCode::kErrorNoError : ErrorCode::kErrorFileNotFound;
}

ErrorCode CompilerFactory::Compile(const MplOptions &mplOptions) {
  auto compilers = std::vector<Compiler*>();
  auto ret = compilerSelector->Select(supportedCompilers, mplOptions, compilers);
  if (ret == ErrorCode::kErrorNoError) {
    for (auto compiler : compilers) {
      ret = compiler->Compile(mplOptions, this->theModule);
      if (ret != ErrorCode::kErrorNoError) {
        return ret;
      }
    }
  } else {
    return ret;
  }
  if (!mplOptions.isSaveTmps || !mplOptions.saveFiles.empty()) {
    auto tmpFiles = std::vector<std::string>();
    for (auto compiler : compilers) {
      compiler->GetTmpFilesToDelete(mplOptions, tmpFiles);
    }
    ret = DeleteTmpFiles(mplOptions, tmpFiles, compilers.at(compilers.size() - 1)->GetFinalOutputs(mplOptions));
  }
  return ret;
}
