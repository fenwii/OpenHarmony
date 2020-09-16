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
#include <pthread.h>
#include <unistd.h>
#include "common.h"
#include "memory_adapter.h"
#define PRI_BUTT 39
#define MIN_STACK_SIZE 0x8000
static int g_threadCount = 0;
static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_key_t g_localKey = 0;

MutexId MUTEX_InitValue()
{
    pthread_mutex_t *mutex = SAMGR_Malloc(sizeof(pthread_mutex_t));
    if (mutex == NULL) {
        return NULL;
    }
    (void)pthread_mutex_init(mutex, NULL);
    return (MutexId)mutex;
}

void MUTEX_Lock(MutexId mutex)
{
    if (mutex == NULL) {
        return;
    }
    pthread_mutex_lock((pthread_mutex_t *)mutex);
}

void MUTEX_Unlock(MutexId mutex)
{
    if (mutex == NULL) {
        return;
    }
    pthread_mutex_unlock((pthread_mutex_t *)mutex);
}

void MUTEX_GlobalLock(void)
{
    pthread_mutex_lock(&g_mutex);
}

void MUTEX_GlobalUnlock(void)
{
    pthread_mutex_unlock(&g_mutex);
}

ThreadId THREAD_Create(Runnable run, void *argv, const ThreadAttr *attr)
{
    pthread_attr_t threadAttr;
    pthread_attr_init(&threadAttr);
    pthread_attr_setstacksize(&threadAttr, (attr->stackSize | MIN_STACK_SIZE));
    pthread_attr_setinheritsched(&threadAttr, PTHREAD_EXPLICIT_SCHED);
#ifdef SAMGR_LINUX_ADAPTER
    struct sched_param sched = {attr->priority};
#else
    struct sched_param sched = {PRI_BUTT - attr->priority};
#endif
    pthread_attr_setschedpolicy(&threadAttr, SCHED_RR);
    pthread_attr_setschedparam(&threadAttr, &sched);
    pthread_key_create(&g_localKey, NULL);
    pthread_t threadId = 0;
    int errno = pthread_create(&threadId, &threadAttr, run, argv);
    if (errno != 0) {
        return NULL;
    }

    MUTEX_GlobalLock();
    g_threadCount++;
    MUTEX_GlobalUnlock();
    return (ThreadId)threadId;
}

int THREAD_Total(void)
{
    return g_threadCount;
}

void *THREAD_GetThreadLocal(void)
{
    return pthread_getspecific(g_localKey);
}

void THREAD_SetThreadLocal(const void *local)
{
    pthread_setspecific(g_localKey, local);
}
