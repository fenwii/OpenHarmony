/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TIMER_CLOCK_ID
#define TIMER_CLOCK_ID

#include <gtest/gtest.h>

// defined in musl/include/time.h
static const char* ALL_CLOCKS[CLOCK_TAI + 1] = {
    "CLOCK_REALTIME",
    "CLOCK_MONOTONIC",
    "CLOCK_PROCESS_CPUTIME_ID",
    "CLOCK_THREAD_CPUTIME_ID",
    "CLOCK_MONOTONIC_RAW",
    "CLOCK_REALTIME_COARSE",
    "CLOCK_MONOTONIC_COARSE",
    "CLOCK_BOOTTIME",
    "CLOCK_REALTIME_ALARM",
    "CLOCK_BOOTTIME_ALARM",
    "CLOCK_SGI_CYCLE",
    "CLOCK_TAI",
};

static const auto ALL_CLOCK_IDS = testing::Values(CLOCK_REALTIME, CLOCK_MONOTONIC, CLOCK_PROCESS_CPUTIME_ID,
    CLOCK_THREAD_CPUTIME_ID, CLOCK_MONOTONIC_RAW, CLOCK_REALTIME_COARSE, CLOCK_MONOTONIC_COARSE, 
    CLOCK_BOOTTIME, CLOCK_REALTIME_ALARM, CLOCK_BOOTTIME_ALARM, CLOCK_SGI_CYCLE, CLOCK_TAI);

static const auto ALL_SUPPORTED_IDS = testing::Values(CLOCK_MONOTONIC, CLOCK_REALTIME,
    CLOCK_MONOTONIC_COARSE, CLOCK_REALTIME_COARSE, CLOCK_MONOTONIC_RAW);

class AllClockIDTest : public testing::TestWithParam<int> {
};
class SupportedClockIDTest : public testing::TestWithParam<int> {
};

#endif