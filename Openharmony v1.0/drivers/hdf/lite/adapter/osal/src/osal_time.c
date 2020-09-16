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

#include "osal_time.h"
#include <sys/time.h>
#include <time.h>
#include "los_sys.h"
#include "los_task.h"
#include "hdf_log.h"

#define HDF_LOG_TAG osal_time
#define TM_SINCE_YEAR 1900

int32_t OsalGetTime(OsalTimespec *time)
{
    uint64_t ms;

    if (time == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    ms = LOS_TickCountGet() * (HDF_KILO_UNIT / LOSCFG_BASE_CORE_TICK_PER_SECOND);

    time->sec = ms / HDF_KILO_UNIT;
    time->usec = (ms % HDF_KILO_UNIT) * HDF_KILO_UNIT;

    return HDF_SUCCESS;
}

int32_t OsalDiffTime(const OsalTimespec *start, const OsalTimespec *end, OsalTimespec *diff)
{
    uint32_t usec = 0;
    uint32_t sec = 0;

    if (start == NULL || end == NULL || diff == NULL) {
        HDF_LOGE("%s invalid para", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    if (start->sec > end->sec) {
        HDF_LOGE("%s start time later then end time", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    if (end->usec < start->usec) {
        usec = (HDF_KILO_UNIT * HDF_KILO_UNIT);
        sec = 1;
    }
    diff->usec = usec + end->usec - start->usec;
    diff->sec = end->sec - start->sec - sec;

    return HDF_SUCCESS;
}

uint64_t OsalGetSysTimeMs(void)
{
    return LOS_TickCountGet() * (HDF_KILO_UNIT / LOSCFG_BASE_CORE_TICK_PER_SECOND);
}

void OsalSleep(uint32_t sec)
{
    LOS_Msleep(sec * HDF_KILO_UNIT);
}

void OsalMSleep(uint32_t ms)
{
    LOS_Msleep(ms);
}

void OsalUDelay(uint32_t us)
{
    LOS_Udelay(us);
}

void OsalMDelay(uint32_t ms)
{
    LOS_Mdelay(ms);
}

