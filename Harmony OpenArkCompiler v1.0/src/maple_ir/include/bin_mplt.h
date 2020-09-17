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
#ifndef MAPLE_IR_INCLUDE_BIN_MPLT_H
#define MAPLE_IR_INCLUDE_BIN_MPLT_H
#include "mir_module.h"
#include "mir_nodes.h"
#include "mir_preg.h"
#include "parser_opt.h"
#include "bin_mpl_export.h"
#include "bin_mpl_import.h"

namespace maple {
class BinaryMplt {
 public:

  explicit BinaryMplt(MIRModule &md) : mirModule(md), binImport(md), binExport(md) {}

  virtual ~BinaryMplt() {}

  void Export(const std::string &suffix) {
    binExport.Export(suffix);
  }

  bool Import(const std::string &modID, bool readCG = false, bool readSE = false) {
    importFileName = modID;
    return binImport.Import(modID, readCG, readSE);
  }

  MIRModule &GetMod() {
    return mirModule;
  }

  BinaryMplImport &GetBinImport() {
    return binImport;
  }

  BinaryMplExport &GetBinExport() {
    return binExport;
  }

  std::string &GetImportFileName() {
    return importFileName;
  }

 private:
  MIRModule &mirModule;
  BinaryMplImport binImport;
  BinaryMplExport binExport;
  std::string importFileName;
};

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_BIN_MPLT_H
