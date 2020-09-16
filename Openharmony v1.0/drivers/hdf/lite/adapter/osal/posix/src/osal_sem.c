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

#include "osal_sem.h"
#include <errno.h>
#include <semaphore.h>
#include <time.h>
#include "securec.h"
#include "hdf_log.h"
#include "osal_mem.h"

const int32_t SHARE = 0;
#define HDF_LOG_TAG osal_sem
#define HDF_NANO_UNITS 1000000000

int32_t OsalSemInit(struct OsalSem *sem, uint32_t value)
{
    sem_t *semTmp = NULL;

    if (sem == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    sem->realSemaphore = NULL;

    semTmp = (sem_t *)OsalMemCalloc(sizeof(sem_t));
    if (semTmp == NULL) {
        HDF_LOGE("malloc fail");
        return HDF_ERR_MALLOC_FAIL;
    }

    if (sem_init(semTmp, SHARE, value) != 0) {
        HDF_LOGE("sem_init fail errno:%d", errno);
        OsalMemFree(semTmp);
        return HDF_FAILURE;
    }
    sem->realSemaphore = (void *)semTmp;

    return HDF_SUCCESS;
}

int32_t OsalSemWait(struct OsalSem *sem, uint32_t ms)
{
    if (sem == NULL || sem->realSemaphore == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    if (ms == HDF_WAIT_FOREVER) {
        if (sem_wait((sem_t *)sem->realSemaphore) != 0) {
            HDF_LOGE("sem_wait fail errno:%d", errno);
            return HDF_FAILURE;
        }
    } else {
        struct timespec time;
        (void)memset_s(&time, sizeof(time), 0, sizeof(time));
        clock_gettime(CLOCK_REALTIME, &time);
        time.tv_sec += ms / HDF_KILO_UNIT;
        time.tv_nsec += (ms % HDF_KILO_UNIT) * HDF_KILO_UNIT * HDF_KILO_UNIT;
        if (time.tv_nsec >= HDF_NANO_UNITS) {
            time.tv_nsec -= HDF_NANO_UNITS;
            time.tv_sec += 1;
        }
        int32_t ret = sem_timedwait((sem_t *)sem->realSemaphore, &time);
        if (ret != 0) {
            if (errno == ETIMEDOUT) {
                return HDF_ERR_TIMEOUT;
            } else {
                HDF_LOGE("%s time_out time:%d ret:%d,errno:%d", __func__, ms, ret, errno);
                return HDF_FAILURE;
            }
        }
    }

    return HDF_SUCCESS;
}

int32_t OsalSemPost(struct OsalSem *sem)
{
    if (sem == NULL || sem->realSemaphore == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    if (sem_post((sem_t *)sem->realSemaphore) != 0) {
        HDF_LOGE("sem_post fail errno:%d", errno);
        return HDF_FAILURE;
    }

    return HDF_SUCCESS;
}

int32_t OsalSemDestroy(struct OsalSem *sem)
{
    if (sem == NULL || sem->realSemaphore == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    int32_t ret = sem_destroy((sem_t *)sem->realSemaphore);
    if (ret != 0) {
        HDF_LOGE("sem_destroy fail errno:%d", errno);
        return HDF_FAILURE;
    }
    OsalMemFree(sem->realSemaphore);
    sem->realSemaphore = NULL;

    return HDF_SUCCESS;
}

