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
#include "los_hwi.h"
#include "los_sem.h"
#include "los_typedef.h"
#include "hdf_log.h"

#define HDF_LOG_TAG osal_sem
#define HDF_INVALID_SEM_ID UINT32_MAX

int32_t OsalSemInit(struct OsalSem *sem, uint32_t value)
{
    uint32_t semId;
    uint32_t ret;

    if (sem == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = LOS_SemCreate((uint16_t)value, &semId);
    if (ret == LOS_OK) {
        sem->realSemaphore = (void *)(uintptr_t)semId;
        return HDF_SUCCESS;
    } else {
        sem->realSemaphore = (void *)(uintptr_t)HDF_INVALID_SEM_ID;
        HDF_LOGE("%s create fail %d", __func__, ret);
        return HDF_FAILURE;
    }
}

int32_t OsalSemWait(struct OsalSem *sem, uint32_t ms)
{
    uint32_t ret;

    if (sem == NULL || sem->realSemaphore == (void *)(uintptr_t)HDF_INVALID_SEM_ID) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = LOS_SemPend((uint32_t)(uintptr_t)sem->realSemaphore, LOS_MS2Tick(ms));
    if (ret == LOS_OK) {
        return HDF_SUCCESS;
    } else {
        if (ret == LOS_ERRNO_SEM_TIMEOUT) {
            return HDF_ERR_TIMEOUT;
        }
        HDF_LOGE("%s LOS_SemPend fail %d", __func__, ret);
        return HDF_FAILURE;
    }
}

int32_t OsalSemPost(struct OsalSem *sem)
{
    uint32_t ret;

    if (sem == NULL || sem->realSemaphore == (void *)(uintptr_t)HDF_INVALID_SEM_ID) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = LOS_SemPost((uint32_t)(uintptr_t)sem->realSemaphore);
    if (ret == LOS_OK) {
        return HDF_SUCCESS;
    } else {
        HDF_LOGE("%s LOS_SemPost fail %d", __func__, ret);
        return HDF_FAILURE;
    }
}

int32_t OsalSemDestroy(struct OsalSem *sem)
{
    uint32_t ret;

    if (sem == NULL || sem->realSemaphore == (void *)(uintptr_t)HDF_INVALID_SEM_ID) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = LOS_SemDelete((uint32_t)(uintptr_t)sem->realSemaphore);
    if (ret != LOS_OK) {
        HDF_LOGE("%s LOS_SemDelete fail %d", __func__, ret);
        return HDF_FAILURE;
    }
    sem->realSemaphore = (void *)(uintptr_t)HDF_INVALID_SEM_ID;
    return HDF_SUCCESS;
}

