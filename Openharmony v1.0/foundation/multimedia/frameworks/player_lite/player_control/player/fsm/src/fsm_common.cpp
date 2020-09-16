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

#include "fsm_common.h"

#include <ctime>
#include <cstdio>
#include <climits>
#include <unistd.h>

const uint32_t SEC2USEC = 1000000;
const uint16_t USEC2NSEC = 1000;
const uint32_t SEC2NSEC = 1000000000;

uint64_t FsmGetCurTimeUs()
{
    struct timespec ts = { 0, 0 };

    (void)clock_gettime(CLOCK_MONOTONIC, &ts);

    uint64_t curT = (((uint64_t)ts.tv_sec) * SEC2USEC) + (((uint64_t)ts.tv_nsec) / USEC2NSEC);

    return (uint64_t)curT;
}

void FsmCondInitRelative(pthread_cond_t &cond)
{
#if (!defined(__HuaweiLite__) && !defined(__OHOS__))
    pthread_condattr_t condAttr;
    (void)pthread_condattr_init(&condAttr);

    (void)pthread_condattr_setclock(&condAttr, CLOCK_MONOTONIC);
    (void)pthread_cond_init(&cond, &condAttr);
#else
    (void)pthread_cond_init(&cond, nullptr);
#endif
}

int32_t FsmCondTimewait(pthread_cond_t &cond, pthread_mutex_t &mutex, uint32_t delayUs)
{
    struct timespec ts = { 0, 0 };

#if (!defined(__HuaweiLite__) && !defined(__OHOS__))
    (void)clock_gettime(CLOCK_MONOTONIC, &ts);
#else
    ts.tv_sec = 0;
    ts.tv_nsec = 0;
#endif
    if (delayUs >= UINT_MAX / USEC2NSEC) {
        return HI_FAILURE;
    }
    uint64_t delayNs = delayUs * USEC2NSEC;
    ts.tv_sec += (delayNs / SEC2NSEC);
    delayNs = delayNs % SEC2NSEC;

    if (ts.tv_nsec + delayNs > SEC2NSEC) {
        ts.tv_sec++;
        ts.tv_nsec = (ts.tv_nsec + delayNs) - SEC2NSEC;
    } else {
        ts.tv_nsec += delayNs;
    }

    return pthread_cond_timedwait(&cond, &mutex, &ts);
}
