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
#include "mpl_options.h"
#include <string>
#include <vector>
#include <algorithm>
#include "compiler_factory.h"
#include "file_utils.h"
#include "mpl_logging.h"
#include "option_parser.h"
#include "string_utils.h"
#include "usages.h"
#include "default_options.h"
#include "version.h"

using namespace mapleOption;

namespace maple {
const std::string kMapleDriverVersion = "mapledriver " + std::to_string(Version::kMajorMplVersion) + "." +
                                        std::to_string(Version::kMinorCompilerVersion) + " 20190712";
int MplOptions::Parse(int argc, char **argv) {
  this->optionParser = new OptionParser(USAGES);
  exeFolder = FileUtils::GetFileFolder(*argv);
  int ret = optionParser->Parse(argc, argv);
  bool isOptLevelO0 = false;
  bool isOptLevelO2 = false;
  if (ret != ErrorCode::kErrorNoError) {
    return ErrorCode::kErrorInvalidParameter;
  }
  // We should recognize O0, O2 and run options firstly to decide the real options
  for (auto opt : optionParser->GetOptions()) {
    switch (opt.Index()) {
      case kOptimization0:
        isOptLevelO0 = true;
        isOptLevelO2 = false;
        break;
      case kRun:
        this->UpdateRunningExe(opt.Args());
        break;
      default:
        break;
    }
  }
  // Set Default options as O0
  if (runningExes.size() == 0 && isOptLevelO0 == false && isOptLevelO2 == false) {
    isOptLevelO0 = true;
    isOptLevelO2 = false;
  }
  // Set O0 options
  if (isOptLevelO0 == true) {
    this->UpdateOptLevel(kO0);
    this->setDefaultLevel = true;
    this->UpdateRunningExe("jbc2mpl");
    ret = AppendDefaultOptions(kBinNameMe, kMeDefaultOptionsO0, sizeof(kMeDefaultOptionsO0) / sizeof(MplOption));
    if (ret != ErrorCode::kErrorNoError) {
      return ret;
    }
    ret = AppendDefaultOptions(kBinNameMpl2mpl, kMpl2MplDefaultOptionsO0,
                               sizeof(kMpl2MplDefaultOptionsO0) / sizeof(MplOption));
    if (ret != ErrorCode::kErrorNoError) {
      return ret;
    }
    this->UpdateRunningExe("mplcg");
  }
  for (auto opt : optionParser->GetOptions()) {
    switch (opt.Index()) {
      case kHelp: {
        optionParser->PrintUsage("all");
        return ErrorCode::kErrorExitHelp;
      }
      case kVersion: {
        INFO(kLncInfo, kMapleDriverVersion);
        return ErrorCode::kErrorExitHelp;
      }
      case kMeHelp:
        optionParser->PrintUsage("me");
        return ErrorCode::kErrorExitHelp;
      case kMpl2MplHelp:
        optionParser->PrintUsage("mpl2mpl");
        return ErrorCode::kErrorExitHelp;
      case kInFile: {
        if (!Init(opt.Args())) {
          return ErrorCode::kErrorInitFail;
        } else {
          // Check whether the file was readable
          ret = CheckFileExits();
          if (ret != ErrorCode::kErrorNoError) {
            return ret;
          }
        }
        break;
      }
      case kCombTimePhases:
        this->timePhases = true;
        this->printCommandStr += " -time-phases";
        break;
      case kGenMeMpl:
        this->genMemPl = true;
        this->printCommandStr += " --genmempl";
        break;
      case kGenVtableImpl:
        this->genVtableImpl = true;
        this->printCommandStr += " --genVtableImpl";
        break;
      case kSaveTemps:
        this->isSaveTmps = true;
        StringUtils::Split(opt.Args(), this->saveFiles, ',');
        this->printCommandStr += " --save-temps";
        break;
      case kOption:
        if (this->UpdateExtraOptionOpt(opt.Args()) != ErrorCode::kErrorNoError) {
          return ErrorCode::kErrorInvalidParameter;
        }
        break;
      case kInMplt:
        break;
      case kAllDebug:
        this->debugFlag = true;
        break;
      default:
        // I do not care
        break;
    }
    this->AddOption(opt);
  }
  // Get input fileName
  if (optionParser->GetNonOptionsCount() > 0) {
    std::string optionString;
    const std::vector<std::string> inputs = optionParser->GetNonOptions();
    for (unsigned int i = 0; i < inputs.size(); i++) {
      if (i == 0) {
        optionString = inputs[i];
      } else {
        optionString = optionString + "," + inputs[i];
      }
    }
    if (!Init(optionString)) {
      ret = ErrorCode::kErrorInitFail;
    } else {
      // Check whether the file was readable
      ret = CheckFileExits();
    }
  }
  // Set Default options as O0
  if (runningExes.size() == 0) {
    this->UpdateOptLevel(kO0);
    this->setDefaultLevel = true;
    this->UpdateRunningExe("dex2mpl");
    AppendDefaultOptions(kBinNameMe, kMeDefaultOptionsO0,
                         sizeof(kMeDefaultOptionsO0) / sizeof(MplOption));
    AppendDefaultOptions(kBinNameMpl2mpl, kMpl2MplDefaultOptionsO0,
                         sizeof(kMpl2MplDefaultOptionsO0) / sizeof(MplOption));
    this->UpdateRunningExe("mplcg");
  }
  return ret;
}

ErrorCode MplOptions::CheckFileExits() {
  ErrorCode ret = ErrorCode::kErrorNoError;
  for (auto fileName : splitsInputFiles) {
    std::ifstream infile;
    infile.open(fileName);
    if (infile.fail()) {
      LogInfo::MapleLogger(kLlErr) << "Cannot open input file " << fileName << std::endl;
      ret = ErrorCode::kErrorFileNotFound;
      return ret;
    }
  }
  return ret;
}

void MplOptions::AddOption(const mapleOption::Option &option) {
  if (option.HasExtra()) {
    for (auto extra : option.GetExtras()) {
      options.Insert(extra.exeName, option);
    }
  }
}

bool MplOptions::Init(const std::string &inputFile) {
  if (StringUtils::Trim(inputFile).empty()) {
    return false;
  }
  this->inputFiles = inputFile;
  StringUtils::Split(inputFile, this->splitsInputFiles, ',');
  std::string firstInputFile = splitsInputFiles[0];
  this->inputFolder = FileUtils::GetFileFolder(firstInputFile);
  this->outputFolder = this->inputFolder;
  this->outputName = FileUtils::GetFileName(firstInputFile, false);
  std::string extensionName = FileUtils::GetFileExtension(firstInputFile);
  if (extensionName == "class") {
    this->inputFileType = InputFileType::kClass;
  }
  else if (extensionName == "jar") {
    this->inputFileType = InputFileType::kJar;
  } else if (extensionName == "mpl") {
    if (firstInputFile.find("VtableImpl") == std::string::npos) {
      this->inputFileType = InputFileType::kMpl;
    } else {
      this->inputFileType = InputFileType::kVtableImplMpl;
    }
  } else if (extensionName == "s") {
    this->inputFileType = InputFileType::kS;
  } else {
    return false;
  }
  return true;
}

const std::string MplOptions::OptimizationLevelStr() const {
  switch (this->optimizationLevel) {
    case OptimizationLevel::kO0: {
      return "-O0";
    }
    case OptimizationLevel::kO1: {
      return "-O1";
    }
    case OptimizationLevel::kO2: {
      return "-O2";
    }
  }
}

void MplOptions::UpdateOptLevel(OptimizationLevel level) {
  this->optimizationLevel = level;
}

ErrorCode MplOptions::AppendDefaultOptions(const std::string &exeName, MplOption *mplOptions, unsigned int length) {
  bool ret = true;
  auto &exeOption = exeOptions[exeName];
  for (unsigned int i = 0; i < length; i++) {
    ret = optionParser->SetOption(mplOptions[i].key, mplOptions[i].value, exeName, exeOption);
    if (!ret) {
      return ErrorCode::kErrorInvalidParameter;
    }
  }
  auto iter = std::find(this->runningExes.begin(), this->runningExes.end(), exeName.c_str());
  if (iter == this->runningExes.end()) {
    this->runningExes.push_back(exeName);
  }
  return ErrorCode::kErrorNoError;
}

ErrorCode MplOptions::UpdateExtraOptionOpt(const std::string &args) {
  std::vector<std::string> temp;
  StringUtils::Split(args, temp, ':');
  if (temp.size() != extras.size() && temp.size() != runningExes.size()) {
    // parameter not match ignore
    LogInfo::MapleLogger(kLlErr) << "The --run and --option are not matched, please check them.(Too many ':'?)"
                                 << std::endl;
    return ErrorCode::kErrorInvalidParameter;
  }
  auto settingExe = runningExes.begin();
  for (const auto &tempIt : temp) {
    bool ret = true;

    std::vector<std::string> tmpArgs;
    // Split options with ' '
    StringUtils::Split(tempIt, tmpArgs, ' ');
    auto &exeOption = exeOptions[*settingExe];
    // For compiler bins called by system()
    auto &extraOption = extras[*settingExe];
    for (const auto &argsIt : tmpArgs) {
      MplOption mplOption;
      // If "=" is not in the string, indicates that it is an option without value
      if (argsIt.find("=") == std::string::npos) {
        if (!argsIt.empty()) {
          // Set key only
          mplOption.init(argsIt, "", " ", false, "");
          ret &= optionParser->SetOption(argsIt, "", *settingExe, exeOption);
        } else {
          continue;
        }
      } else {
        // If "=" is in the string, indicates that it is an option with value
        std::vector<std::string> arg;
        StringUtils::Split(argsIt, arg, '=');
        if (arg.size() > 1) {
          // Set key and value
          mplOption.init(arg.at(0), arg.at(1), "=", false, "");
          ret &= optionParser->SetOption(arg.at(0), arg.at(1), *settingExe, exeOption);
        } else {
          WARN(kLncWarn, "warning no args after \'=\' for " + arg.at(0));
          continue;
        }
      }
      extraOption.push_back(mplOption);
    }
    if (!ret) {
      return ErrorCode::kErrorInvalidParameter;
    }
    settingExe++;
  }
  return ErrorCode::kErrorNoError;
}

void MplOptions::UpdateRunningExe(const std::string &args) {
  std::vector<std::string> results;
  StringUtils::Split(args, results, ':');
  for (unsigned int i = 0; i < results.size(); i++) {
    auto iter = std::find(this->runningExes.begin(), this->runningExes.end(), results[i].c_str());
    if (iter == this->runningExes.end()) {
      this->runningExes.push_back(results[i]);
    }
  }
}

}  // namespace maple
