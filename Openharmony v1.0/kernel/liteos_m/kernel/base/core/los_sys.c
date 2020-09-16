/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "los_sys_pri.h"
#include "los_tick_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*****************************************************************************
Function    : LOS_TickCountGet
Description : get current tick
Input       : None
Output      : None
Return      : current tick
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT64 LOS_TickCountGet(VOID)
{
    return g_ullTickCount;
}

/*****************************************************************************
Function    : LOS_CyclePerTickGet
Description : Get System cycle number corresponding to each tick
Input       : None
Output      : None
Return      : cycle number corresponding to each tick
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_CyclePerTickGet(VOID)
{
    return g_cyclesPerTick;
}

/*****************************************************************************
Function    : LOS_MS2Tick
Description : milliseconds convert to Tick
Input       : millisec ---------- milliseconds
Output      : None
Return      : Tick
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MS2Tick(UINT32 millisec)
{
    if (millisec == OS_NULL_INT) {
        return OS_NULL_INT;
    }

    return ((UINT64)millisec * LOSCFG_BASE_CORE_TICK_PER_SECOND) / OS_SYS_MS_PER_SECOND;
}

/*****************************************************************************
Function    : LOS_Tick2MS
Description : Tick convert to milliseconds
Input       : ticks ---------- ticks
Output      : None
Return      : milliseconds
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_Tick2MS(UINT32 ticks)
{
    return ((UINT64)ticks * OS_SYS_MS_PER_SECOND) / LOSCFG_BASE_CORE_TICK_PER_SECOND;
}

/*****************************************************************************
Function    : OsCpuTick2MS
Description : cycle convert to milliseconds
Input       : cpuTick ---------- cycle
Output      : msHi    ---------- High 32 milliseconds
              msLo    ---------- Low 32 milliseconds
Return      : LOS_OK on success ,or error code on failure
*****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsCpuTick2MS(CpuTick *cpuTick, UINT32 *msHi, UINT32 *msLo)
{
    UINT64 tmpCpuTick;
    DOUBLE temp;

    if ((cpuTick == NULL) || (msHi == NULL) || (msLo == NULL)) {
        return LOS_ERRNO_SYS_PTR_NULL;
    }

    if (g_sysClock == 0) {
        return LOS_ERRNO_SYS_CLOCK_INVALID;
    }
    tmpCpuTick = ((UINT64)cpuTick->cntHi << OS_SYS_MV_32_BIT) | cpuTick->cntLo;
    temp = tmpCpuTick / ((DOUBLE)g_sysClock / OS_SYS_MS_PER_SECOND);

    tmpCpuTick = (UINT64)temp;

    *msLo = (UINT32)tmpCpuTick;
    *msHi = (UINT32)(tmpCpuTick >> OS_SYS_MV_32_BIT);

    return LOS_OK;
}

/*****************************************************************************
Function    : OsCpuTick2US
Description : cycle convert to Microsecond
Input       : cpuTick ---------- cycle
Output      : usHi    ---------- High 32 Microsecond
              usLo    ---------- Low 32 Microsecond
Return      : LOS_OK on success ,or error code on failure
*****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsCpuTick2US(CpuTick *cpuTick, UINT32 *usHi, UINT32 *usLo)
{
    UINT64 tmpCpuTick;
    DOUBLE temp;

    if ((cpuTick == NULL) || (usHi == NULL) || (usLo == NULL)) {
        return LOS_ERRNO_SYS_PTR_NULL;
    }

    if (g_sysClock == 0) {
        return LOS_ERRNO_SYS_CLOCK_INVALID;
    }
    tmpCpuTick = ((UINT64)cpuTick->cntHi << OS_SYS_MV_32_BIT) | cpuTick->cntLo;
    temp = tmpCpuTick / ((DOUBLE)g_sysClock / OS_SYS_US_PER_SECOND);

    tmpCpuTick = (UINT64)temp;

    *usLo = (UINT32)tmpCpuTick;
    *usHi = (UINT32)(tmpCpuTick >> OS_SYS_MV_32_BIT);

    return LOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
