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

#include "osal_thread.h"
#include <pthread.h>
#include "hdf_base.h"
#include "hdf_log.h"
#include "osal_mem.h"

#define OSAL_PTHREAD_STACK_MIN 4096

#define HDF_LOG_TAG osal_thread

typedef void *(*posixEntry)(void *data);

struct ThreadWrapper {
    OsalThreadEntry threadEntry;
    void *entryPara;
    pthread_t id;
};
#ifdef _LINUX_USER_
enum {
    OSAL_PRIORITY_MIDDLE   = 50,
    OSAL_PRIORITY_HIGH     = 90,
    OSAL_PRIORITY_HIGHEST  = 99,
};
#else
enum {
    OSAL_PRIORITY_MIDDLE   = 30,
    OSAL_PRIORITY_HIGH     = 15,
    OSAL_PRIORITY_HIGHEST  = 5,
};
#endif

static void OsalThreadRemapSched(int priority, struct sched_param *param, int32_t *policy)
{
    if (priority == OSAL_THREAD_PRI_HIGHEST) {
        param->sched_priority = OSAL_PRIORITY_HIGHEST;
    } else if (priority == OSAL_THREAD_PRI_HIGH) {
        param->sched_priority = OSAL_PRIORITY_HIGH;
    } else if (priority == OSAL_THREAD_PRI_DEFAULT) {
        param->sched_priority = OSAL_PRIORITY_MIDDLE;
    } else {
        *policy = SCHED_OTHER;
    }
}

int32_t OsalThreadCreate(struct OsalThread *thread, OsalThreadEntry threadEntry, void *entryPara)
{
    struct ThreadWrapper *para = NULL;

    if (thread == NULL || threadEntry == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    thread->realThread = NULL;
    para = OsalMemAlloc(sizeof(*para));
    if (para == NULL) {
        HDF_LOGE("%s malloc fail", __func__);
        return HDF_FAILURE;
    }

    para->entryPara = entryPara;
    para->threadEntry = threadEntry;
    thread->realThread = para;

    return HDF_SUCCESS;
}

int32_t OsalThreadDestroy(struct OsalThread *thread)
{
    if (thread->realThread != NULL) {
        OsalMemFree(thread->realThread);
        thread->realThread = NULL;
    }
    return HDF_SUCCESS;
}

static int OsalCreatePthread(pthread_t *threadId, pthread_attr_t *attribute, struct ThreadWrapper *para)
{
    int resultCode = pthread_create(threadId, attribute, (posixEntry)para->threadEntry, para->entryPara);
    if (resultCode != 0) {
        HDF_LOGE("pthread_create errorno: %d", resultCode);
        return resultCode;
    }
    resultCode = pthread_detach(*threadId);
    if (resultCode != 0) {
        HDF_LOGE("pthread_detach errorno: %d", resultCode);
        return resultCode;
    }
    resultCode = pthread_attr_destroy(attribute);
    if (resultCode != 0) {
        HDF_LOGE("pthread_attr_destroy errorno: %d", resultCode);
        return resultCode;
    }
    return 0;
}

int32_t OsalThreadStart(struct OsalThread *thread, const struct OsalThreadParam *param)
{
    pthread_attr_t attribute;
    struct sched_param priorityHolder;
    int32_t policy = SCHED_FIFO;

    if (thread == NULL || thread->realThread == NULL || param == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    struct ThreadWrapper *para = (struct ThreadWrapper *)thread->realThread;

    int resultCode = pthread_attr_init(&attribute);
    if (resultCode != 0) {
        HDF_LOGE("pthread_attr_init errorno: %d", resultCode);
        goto DEAL_FAIL;
    }

    resultCode = pthread_attr_setinheritsched(&attribute, PTHREAD_EXPLICIT_SCHED);
    if (resultCode != 0) {
        HDF_LOGE("pthread_attr_setinheritsched errorno: %d", resultCode);
        goto DEAL_FAIL;
    }

    size_t stackSize = param->stackSize;
    if (stackSize > 0) {
        stackSize = (stackSize < OSAL_PTHREAD_STACK_MIN) ? OSAL_PTHREAD_STACK_MIN : stackSize;
        resultCode = pthread_attr_setstacksize(&attribute, stackSize);
        if (resultCode != 0) {
            HDF_LOGE("pthread_attr_setstacksize errorno: %d", resultCode);
            goto DEAL_FAIL;
        }
    }

    resultCode = pthread_attr_getschedparam(&attribute, &priorityHolder);
    if (resultCode != 0) {
        HDF_LOGE("pthread_attr_getschedparam errorno: %d", resultCode);
        goto DEAL_FAIL;
    }

    OsalThreadRemapSched(param->priority, &priorityHolder, &policy);

    resultCode = pthread_attr_setschedpolicy(&attribute, policy);
    if (resultCode != 0) {
        HDF_LOGE("pthread_attr_setschedpolity errorno: %d", resultCode);
        goto DEAL_FAIL;
    }

    resultCode = pthread_attr_setschedparam(&attribute, &priorityHolder);
    if (resultCode != 0) {
        HDF_LOGE("pthread_attr_setschedparam errorno: %d", resultCode);
        goto DEAL_FAIL;
    }

    resultCode = OsalCreatePthread(&para->id, &attribute, thread->realThread);
    if (resultCode != 0) {
        HDF_LOGE("pthread_attr_setschedparam errorno: %d", resultCode);
        goto DEAL_FAIL;
    }
    return HDF_SUCCESS;

DEAL_FAIL:
    (void)OsalThreadDestroy(thread);
    return HDF_FAILURE;
}

