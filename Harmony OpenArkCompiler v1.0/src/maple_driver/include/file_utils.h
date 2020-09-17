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
#ifndef MAPLE_DRIVER_INCLUDE_FILE_UTILS_H
#define MAPLE_DRIVER_INCLUDE_FILE_UTILS_H
#include <string>

namespace FileSeperator {
const static char kFileSeperatorLinuxStyleChar = '/';
const static char kFileSeperatorWindowsStyleChar = '\\';
const static char kFileSeperatorChar = kFileSeperatorLinuxStyleChar;
const static std::string kFileSeperatorLinuxStyleStr = std::string(1, kFileSeperatorLinuxStyleChar);
const static std::string kFileSeperatorWindowsStyleStr = std::string(1, kFileSeperatorWindowsStyleChar);
const static std::string kFileSeperatorStr = kFileSeperatorLinuxStyleStr;
}  // namespace FileSeperator

namespace maple {
class FileUtils {
 public:
  const static std::string GetFileName(const std::string &filePath, const bool isWithExtension);
  const static std::string GetFileExtension(const std::string &filePath);
  const static std::string GetFileFolder(const std::string &filePath);
  const static std::string ConvertPathIfNeeded(const std::string &src);
  const static int Remove(const std::string &filePath);
  const static std::string AppendMapleRootIfNeeded(bool needRootPath, const std::string &path,
                                                   const std::string &defaultRoot =
                                                   ("." + FileSeperator::kFileSeperatorStr));
};

}  // namespace maple
#endif  // MAPLE_DRIVER_INCLUDE_FILE_UTILS_H
