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
#ifndef MAPLE_IR_INCLUDE_BIN_MIR_FILE_H
#define MAPLE_IR_INCLUDE_BIN_MIR_FILE_H
#include <string>
#include "types_def.h"

namespace maple {
const std::string kBinMirFileID = "HWCMPL";  // for magic in file header
constexpr int kVersionMajor = 0;             // experimental version
constexpr int kVersionMinor = 1;

enum BinMirFileType {
  kMjsvmFileTypeCmplV1,
  kMjsvmFileTypeCmpl,  // kCmpl v2 is the release version of
  kMjsvmFileTypeUnknown
};

#define MAKE_VERSION_NUM(major, minor) ((uint8)(((major & 0xF) << 4) | (minor & 0xF)))
// file header for binary format kMmpl, 8B in total
// Note the header is different with the specification
struct BinMIRFileHeader {
  char magic[7];         // “HWCMPL”, or "HWLOS_"
  maple::uint8 segNum;   // number of segments (e.g. one raw IR file is a segment unit)
  maple::uint8 type;     // enum of type of VM file (e.g. MapleIR, TE)
  maple::uint8 version;  // version of IR format (should be major.minor)
};

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_BIN_MIR_FILE_H
