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
#ifndef MAPLE_UTIL_INCLUDE_FILE_LAYOUT_H
#define MAPLE_UTIL_INCLUDE_FILE_LAYOUT_H
#include <iostream>

namespace maple {
// file-layout is shared between maple compiler and runtime, thus not in namespace maplert
enum LayoutType : uint8_t {
  kLayoutBootHot,
  kLayoutBothHot,
  kLayoutRunHot,
  kLayoutStartupOnly,
  kLayoutUsedOnce,
  kLayoutExecuted, // method excuted in some condition
  kLayoutUnused,
  kLayoutTypeCount
};

// this used for c string layout
static uint8_t kCStringShift = 1;
std::string GetLayoutTypeString(uint32_t type);

} // namespace maple
#endif
