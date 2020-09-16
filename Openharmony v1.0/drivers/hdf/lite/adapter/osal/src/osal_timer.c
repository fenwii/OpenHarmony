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

#include "osal_timer.h"
#include "los_hwi.h"
#include "los_swtmr.h"
#include "los_swtmr_pri.h"
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG osal_timer

struct OsalLitetimer {
    uintptr_t arg;
    uint16_t timerID;
    OsalTimerFunc func;
    uint32_t interval;
};

int32_t OsalTimerCreate(OsalTimer *timer, uint32_t interval, OsalTimerFunc func, uintptr_t arg)
{
    struct OsalLitetimer *liteTimer = NULL;

    if (func == NULL || timer == NULL || interval == 0) {
        HDF_LOGE("%s invalid para", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    timer->realTimer = NULL;

    liteTimer = (struct OsalLitetimer *)OsalMemCalloc(sizeof(*liteTimer));
    if (liteTimer == NULL) {
        HDF_LOGE("%s malloc fail", __func__);
        return HDF_ERR_MALLOC_FAIL;
    }
    liteTimer->timerID = MAX_INVALID_TIMER_VID;
    liteTimer->arg = arg;
    liteTimer->func = func;
    liteTimer->interval = interval;
    timer->realTimer = (void *)liteTimer;

    return HDF_SUCCESS;
}

static int32_t OsalStartTimer(OsalTimer *timer, UINT8 mode)
{
    uint32_t ret;
    uint32_t intSave;
    uint32_t interval;
    uint16_t timerID = 0;
    struct OsalLitetimer *liteTimer = NULL;

    if (timer == NULL || timer->realTimer == NULL) {
        HDF_LOGE("%s invalid para %d", __func__, __LINE__);
        return HDF_ERR_INVALID_PARAM;
    }

    liteTimer = (struct OsalLitetimer *)timer->realTimer;
    if (liteTimer->interval == 0 || liteTimer->func == NULL) {
        HDF_LOGE("%s invalid para %d", __func__, __LINE__);
        return HDF_ERR_INVALID_PARAM;
    }

    interval = liteTimer->interval;
    intSave = LOS_IntLock();
    ret = LOS_SwtmrCreate(LOS_MS2Tick(interval), mode, (SWTMR_PROC_FUNC)liteTimer->func, &timerID, liteTimer->arg);
    if (ret != LOS_OK) {
        LOS_IntRestore(intSave);
        HDF_LOGE("%s LOS_SwtmrCreate fail %d", __func__, ret);
        return HDF_FAILURE;
    }

    ret = LOS_SwtmrStart(timerID);
    if (ret != LOS_OK) {
        LOS_SwtmrDelete(timerID);
        LOS_IntRestore(intSave);
        HDF_LOGE("%s LOS_SwtmrStart fail %d", __func__, ret);
        return HDF_FAILURE;
    }
    LOS_IntRestore(intSave);

    liteTimer->timerID = timerID;
    return HDF_SUCCESS;
}
int32_t OsalTimerStartLoop(OsalTimer *timer)
{
    return OsalStartTimer(timer, LOS_SWTMR_MODE_PERIOD);
}

int32_t OsalTimerStartOnce(OsalTimer *timer)
{
    return OsalStartTimer(timer, LOS_SWTMR_MODE_ONCE);
}

int32_t OsalTimerSetTimeout(OsalTimer *timer, uint32_t interval)
{
    struct OsalLitetimer *liteTimer = NULL;
    uint32_t intSave;
    uint32_t ret;

    if (timer == NULL || timer->realTimer == NULL || interval == 0) {
        HDF_LOGE("%s invalid para", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    liteTimer = (struct OsalLitetimer *)timer->realTimer;
    if (liteTimer->timerID == MAX_INVALID_TIMER_VID) {
        HDF_LOGE("%s timer id invalid %d", __func__, liteTimer->timerID);
        return HDF_FAILURE;
    }

    if (liteTimer->interval == interval) {
        return HDF_SUCCESS;
    }

    liteTimer->interval = interval;

    intSave = LOS_IntLock();
    ret = LOS_SwtmrDelete(liteTimer->timerID);
    if (ret != LOS_OK) {
        LOS_IntRestore(intSave);
        HDF_LOGE("%s LOS_SwtmrDelete fail %d", __func__, ret);
        return HDF_FAILURE;
    }
    LOS_IntRestore(intSave);

    return OsalTimerStartLoop(timer);
}

int32_t OsalTimerDelete(OsalTimer *timer)
{
    uint32_t intSave;
    uint32_t ret;
    struct OsalLitetimer *liteTimer = NULL;

    if (timer == NULL || timer->realTimer == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    liteTimer = (struct OsalLitetimer *)timer->realTimer;
    if (liteTimer->timerID == MAX_INVALID_TIMER_VID) {
        HDF_LOGE("%s timer id invalid %d", __func__, liteTimer->timerID);
        return HDF_FAILURE;
    }
    intSave = LOS_IntLock();
    ret = LOS_SwtmrDelete(liteTimer->timerID);
    if (ret == LOS_OK) {
        LOS_IntRestore(intSave);
        OsalMemFree(timer->realTimer);
        timer->realTimer = NULL;
        return HDF_SUCCESS;
    } else {
        LOS_IntRestore(intSave);
        HDF_LOGE("%s LOS_SwtmrDelete fail %d", __func__, ret);
        return HDF_FAILURE;
    }
}

