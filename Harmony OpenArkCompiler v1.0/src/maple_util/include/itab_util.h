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
#ifndef MAPLE_UTIL_INCLUDE_ITAB_UTIL_H
#define MAPLE_UTIL_INCLUDE_ITAB_UTIL_H

namespace maple {
constexpr int kHashSize = 23;
constexpr int kHeadSizeOfSecondHash = 3;
constexpr int kFlagAgInHeadOfSecondHash = 1;
constexpr unsigned int kItabSecondHashSize = 0x1fff;
constexpr int kFlagFirstHashConflict = 0;
constexpr int kFlagSecondHashConflict = 1;

constexpr int kItabFirstHashSize = kHashSize;

unsigned int DJBHash(const char *str);
unsigned int GetHashIndex(const char *name);
unsigned int GetSecondHashIndex(const char *name);


}  // namespace maple
#endif
