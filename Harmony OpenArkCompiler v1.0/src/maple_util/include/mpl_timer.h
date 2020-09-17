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
#ifndef MAPLE_UTIL_INCLUDE_MPL_TIMER_H
#define MAPLE_UTIL_INCLUDE_MPL_TIMER_H

#include <chrono>

namespace maple {
class MPLTimer {
 public:
  MPLTimer();
  ~MPLTimer();
  void Start();
  void Stop();
  long Elapsed();
  long ElapsedMilliseconds();
  long ElapsedMicroseconds();

 private:
  std::chrono::system_clock::time_point startTime;
  std::chrono::system_clock::time_point endTime;
};

}  // namespace maple
#endif  // MAPLE_UTIL_INCLUDE_MPL_TIMER_H
