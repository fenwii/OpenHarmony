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
#ifndef LITE_THREAD_ADAPTER_H
#define LITE_THREAD_ADAPTER_H

#include <ohos_types.h>
#include "common.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/// \details Mutex ID identifies the mutex.
typedef void *(*Runnable)(void *argv);

typedef struct ThreadAttr ThreadAttr;
struct ThreadAttr {
    const char *name;   // name of the thread
    uint32 stackSize;   // size of stack
    uint8 priority;     // initial thread priority
    uint8 reserved1;    // reserved1 (must be 0)
    uint16 reserved2;   // reserved2 (must be 0)
};

MutexId MUTEX_InitValue(void);

void MUTEX_Lock(MutexId mutex);

void MUTEX_Unlock(MutexId mutex);

void MUTEX_GlobalLock(void);

void MUTEX_GlobalUnlock(void);

ThreadId THREAD_Create(Runnable run, void *argv, const ThreadAttr *attr);

int THREAD_Total(void);

void *THREAD_GetThreadLocal(void);

void THREAD_SetThreadLocal(const void *local);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_THREAD_ADAPTER_H
