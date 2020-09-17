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
#ifndef MAPLE_UTIL_INCLUDE_MPL_UTILS_H
#define MAPLE_UTIL_INCLUDE_MPL_UTILS_H

namespace maple {
class Utils {
 public:
  static int HexCharToDigit(char c) {
    if (c >= '0' && c <= '9') {
      return (c - '0');
    } else if (c >= 'A' && c <= 'F') {
      return (c - 'A' + 10);
    } else if (c >= 'a' && c <= 'f') {
      return (c - 'a' + 10);
    } else {
      return 0;
    }
  }
};

}  // namespace maple
#endif  // MAPLE_UTIL_INCLUDE_MPL_UTILS_H
