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

#include "osal_mutex.h"
#include "los_mux.h"
#include "los_sys.h"
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG osal_mutex

int32_t OsalMutexInit(struct OsalMutex *mutex)
{
    uint32_t ret;
    LosMux *mux = NULL;

    if (mutex == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    mux = (LosMux *)OsalMemCalloc(sizeof(LosMux));
    if (mux == NULL) {
        HDF_LOGE("%s malloc fail", __func__);
        mutex->realMutex = NULL;
        return HDF_ERR_MALLOC_FAIL;
    }
    ret = LOS_MuxInit(mux, NULL);
    if (ret == LOS_OK) {
        mutex->realMutex = (void *)mux;
    } else {
        mutex->realMutex = NULL;
        OsalMemFree(mux);
        HDF_LOGE("%s create fail %d %d", __func__, ret, __LINE__);
        return HDF_FAILURE;
    }

    return HDF_SUCCESS;
}

int32_t OsalMutexDestroy(struct OsalMutex *mutex)
{
    uint32_t ret;

    if (mutex == NULL || mutex->realMutex == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = LOS_MuxDestroy((LosMux *)mutex->realMutex);
    if (ret != LOS_OK) {
        HDF_LOGE("%s fail %d %d", __func__, ret, __LINE__);
        return HDF_FAILURE;
    }

    OsalMemFree(mutex->realMutex);
    mutex->realMutex = NULL;
    return HDF_SUCCESS;
}

int32_t OsalMutexLock(struct OsalMutex *mutex)
{
    uint32_t ret;

    if (mutex == NULL || mutex->realMutex == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = LOS_MuxLock((LosMux *)mutex->realMutex, LOS_MS2Tick(HDF_WAIT_FOREVER));
    if (ret != LOS_OK) {
        HDF_LOGE("%s fail %d %d", __func__, ret, __LINE__);
        return HDF_FAILURE;
    }

    return HDF_SUCCESS;
}

int32_t OsalMutexTimedLock(struct OsalMutex *mutex, uint32_t ms)
{
    uint32_t ret;

    if (mutex == NULL || mutex->realMutex == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = LOS_MuxLock((LosMux *)mutex->realMutex, LOS_MS2Tick(ms));
    if (ret != LOS_OK) {
        if (ret == LOS_ETIMEDOUT) {
            return HDF_ERR_TIMEOUT;
        }
        HDF_LOGE("%s fail %d %d", __func__, ret, __LINE__);
        return HDF_FAILURE;
    }

    return HDF_SUCCESS;
}

int32_t OsalMutexUnlock(struct OsalMutex *mutex)
{
    uint32_t ret;

    if (mutex == NULL || mutex->realMutex == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = LOS_MuxUnlock((LosMux *)mutex->realMutex);
    if (ret != LOS_OK) {
        HDF_LOGE("%s fail %d %d", __func__, ret, __LINE__);
        return HDF_FAILURE;
    }

    return HDF_SUCCESS;
}

