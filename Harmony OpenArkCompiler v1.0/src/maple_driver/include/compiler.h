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
#ifndef MAPLE_DRIVER_INCLUDE_COMPILER_H
#define MAPLE_DRIVER_INCLUDE_COMPILER_H
#include <map>
#include <unordered_set>
#include "error_code.h"
#include "mpl_options.h"
#include "me_option.h"
#include "option.h"
#include "mir_module.h"
#include "mir_parser.h"

namespace maple {
// build flag -DMAPLE_ROOT
#ifndef MAPLE_ROOT
#define MAPLE_ROOT ""
#endif

static constexpr char kBinNameJbc2mpl[] = "jbc2mpl";
static constexpr char kBinNameMe[] = "me";
static constexpr char kBinNameMpl2mpl[] = "mpl2mpl";
static constexpr char kBinNameMplcg[] = "mplcg";
static constexpr char kBinNameMapleComb[] = "maplecomb";

class Compiler {
 public:
  explicit Compiler(const std::string &name) : name(name) {}

  virtual ~Compiler() {}

  virtual ErrorCode Compile(const MplOptions &options, MIRModulePtr &theModule);
  inline const std::string &GetName() const {
    return name;
  }

  virtual const std::vector<std::string> GetBinNames() const {
    return std::vector<std::string>();
  }

  virtual void GetTmpFilesToDelete(const MplOptions &mplOptions, std::vector<std::string> &tempFiles) const {
    return;
  }

  virtual const std::unordered_set<std::string> GetFinalOutputs(const MplOptions &mplOptions) const {
    return std::unordered_set<std::string>();
  }

  virtual void PrintCommand(const MplOptions &options) const {}

 protected:
  virtual const std::string GetBinPath(const MplOptions &mplOptions) const;
  virtual const std::string GetBinName() const {
    return "";
  }

  virtual const std::string GetInputFileName(const MplOptions &options) const {
    std::string strOption = "";
    for (auto const &inputFile : options.splitsInputFiles) {
      strOption += " " + inputFile;
    }
    return strOption;
  }

  virtual const DefaultOption GetDefaultOptions(const MplOptions &options) {
    return DefaultOption();
  }

  virtual void AppendExtraOptions(std::map<std::string, MplOption> &finalOptions,
                                  std::map<std::string, std::vector<MplOption>> extraOptions) const;
  virtual const std::string AppendSpecialOption(const MplOptions &options, const std::string &optionStr) const {
    return optionStr;
  }

  virtual const std::string AppendOptimization(const MplOptions &options, const std::string &optionStr) const;
  const bool CanAppendOptimization(const std::string &optionStr) const;
  void AppendOptions(std::map<std::string, MplOption> &finalOptions, const std::string &key, const std::string &value,
                     const std::string &connectSymbol) const;

 private:
  const std::string MakeOption(const MplOptions &options);
  void AppendDefaultOptions(std::map<std::string, MplOption> &finalOptions,
                            const std::map<std::string, MplOption> &defaultOptions) const;
  void AppendUserOptions(std::map<std::string, MplOption> &finalOptions,
                         const std::vector<mapleOption::Option> userOption) const;
  const std::map<std::string, MplOption> MakeDefaultOptions(const MplOptions &options);
  const int Exe(const MplOptions &mplOptions, const std::string &options) const;
  const std::string name;
};

class Jbc2MplCompiler : public Compiler {
 public:
  explicit Jbc2MplCompiler(const std::string &name) : Compiler(name) {}

  ~Jbc2MplCompiler() {}

  const std::vector<std::string> GetBinNames() const;

 protected:
  const std::string GetBinName() const;
  const DefaultOption GetDefaultOptions(const MplOptions &options);
  void GetTmpFilesToDelete(const MplOptions &mplOptions, std::vector<std::string> &tempFiles) const;
  const std::unordered_set<std::string> GetFinalOutputs(const MplOptions &mplOptions) const;
};

class MapleCombCompiler : public Compiler {
 public:
  explicit MapleCombCompiler(const std::string &name) : Compiler(name), realRunningExe("") {}

  ~MapleCombCompiler() {}

  ErrorCode Compile(const MplOptions &options, MIRModulePtr &theModule);
  void PrintCommand(const MplOptions &options) const;
  const std::string GetInputFileName(const MplOptions &options) const;

 protected:
  const std::unordered_set<std::string> GetFinalOutputs(const MplOptions &mplOptions) const;

 private:
  MeOptions *MakeMeOptions(const MplOptions &options, MemPool *optmp);
  Options *MakeMpl2MplOptions(const MplOptions &options, MemPool *optmp);
  std::string realRunningExe;
};

class MplcgCompiler : public Compiler {
 public:
  explicit MplcgCompiler(const std::string &name) : Compiler(name) {}

  ~MplcgCompiler() {}

  const std::string GetBinName() const;
  const std::vector<std::string> GetBinNames() const;

 protected:
  const std::string GetInputFileName(const MplOptions &options) const;
  const DefaultOption GetDefaultOptions(const MplOptions &options);

};

}  // namespace maple
#endif  // MAPLE_DRIVER_INCLUDE_COMPILER_H
