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
#include "time_adapter.h"
#include <ohos_errno.h>
#include <time.h>

#define MS_PER_SECOND 1000
#define NS_PER_MS 1000000

int32 WDT_Start(uint32 ms)
{
    return WDT_Reset(ms);
}

int32 WDT_Reset(uint32 ms)
{
    (void)ms;
    return EC_FAILURE;
}

int32 WDT_Stop(void)
{
    return EC_FAILURE;
}

uint64 SAMGR_GetProcessTime(void)
{
    struct timespec ts = {0, 0};
    clock_gettime(CLOCK_REALTIME, &ts);
    return ((ts.tv_sec * MS_PER_SECOND) + (ts.tv_nsec / NS_PER_MS));
}
