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

#include "hal_tick.h"

#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#elif defined __linux__ || defined __LITEOS__
#include <ctime>
#else
#include "los_swtmr.h"
#endif

namespace OHOS {
uint32_t HALTick::GetTime()
{
#ifdef _WIN32
    return GetTickCount();
#elif defined __linux__ || defined __LITEOS__
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_sec * SEC_TO_MILLISEC + time.tv_nsec / MILLISEC_TO_NANOSEC;
#else
    return LOS_TickCountGet();
#endif
}

uint32_t HALTick::GetElapseTime(uint32_t startTime)
{
    uint32_t currentTime = GetTime();
    uint32_t elapseTime;

    if (currentTime > startTime) {
        elapseTime = currentTime - startTime;
    } else {
        elapseTime = (UINT32_MAX - startTime) + currentTime + 1;
    }

    return elapseTime;
}
} // namespace OHOS
