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

#include "nativeapi_timer_task.h"
#include <stdio.h>
#include "kal.h"
#include "ohos_errno.h"

int InitTimerTask()
{
    return EC_SUCCESS;
}

int StartTimerTask(bool isPeriodic, const unsigned int delay, void* userCallback,
    void* userContext, timerHandle_t *timerHandle)
{
    if (userCallback == NULL) {
        return EC_FAILURE;
    }
    KalTimerType timerType;
    if (isPeriodic) {
        timerType = KAL_TIMER_PERIODIC;
    } else {
        timerType = KAL_TIMER_ONCE;
    }
    KalTimerId timerId = KalTimerCreate((KalTimerProc)userCallback, timerType, userContext, delay);
    if (timerId == NULL) {
        return EC_FAILURE;
    }
    int ret = KalTimerStart(timerId);
    if (ret != KAL_OK) {
        StopTimerTask(timerId);
        return EC_FAILURE;
    }
    *timerHandle = timerId;
    return EC_SUCCESS;
}

int StopTimerTask(const timerHandle_t timerHandle)
{
    if (timerHandle == NULL) {
        return EC_FAILURE;
    }
    int ret = KalTimerDelete((KalTimerId)timerHandle);
    return ret;
}