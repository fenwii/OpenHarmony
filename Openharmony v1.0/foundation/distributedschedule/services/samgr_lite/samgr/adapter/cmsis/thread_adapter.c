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
#include "thread_adapter.h"
#include "common.h"
#include <los_task.h>
#include <cmsis_os.h>

extern void *osThreadGetArgument(void);

MutexId MUTEX_InitValue()
{
    return osMutexNew(NULL);
}

void MUTEX_Lock(MutexId mutex)
{
    if (mutex == NULL) {
        return;
    }
    osMutexAcquire(mutex, LOS_WAIT_FOREVER);
}

void MUTEX_Unlock(MutexId mutex)
{
    if (mutex == NULL) {
        return;
    }
    osMutexRelease(mutex);
}

void MUTEX_GlobalLock(void)
{
    LOS_TaskLock();
}

void MUTEX_GlobalUnlock(void)
{
    LOS_TaskUnlock();
}

ThreadId THREAD_Create(Runnable run, void *argv, const ThreadAttr *attr)
{
    osThreadAttr_t taskAttr = {attr->name, 0, NULL, 0, NULL, attr->stackSize, attr->priority, 0, 0};
    return (ThreadId)osThreadNew((osThreadFunc_t)run, argv, &taskAttr);
}

int THREAD_Total(void)
{
    return osThreadGetCount();
}

void *THREAD_GetThreadLocal(void)
{
    return osThreadGetArgument();
}

void THREAD_SetThreadLocal(const void *local)
{
    (void)local;
}