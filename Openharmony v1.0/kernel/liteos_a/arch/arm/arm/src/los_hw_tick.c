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
#include "los_hwi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

LITE_OS_SEC_TEXT_INIT UINT32 OsTickInit(UINT32 systemClock, UINT32 tickPerSecond)
{
    if ((systemClock == 0) ||
        (tickPerSecond == 0) ||
        (tickPerSecond > systemClock)) {
        return LOS_ERRNO_TICK_CFG_INVALID;
    }
    HalClockInit();

    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT VOID OsTickStart(VOID)
{
    HalClockStart();
}

LITE_OS_SEC_TEXT_MINOR VOID LOS_GetCpuCycle(UINT32 *highCnt, UINT32 *lowCnt)
{
    UINT64 cycle = HalClockGetCycles();

    *highCnt = cycle >> 32; /* 32: offset 32 bits and retain high bits */
    *lowCnt = cycle & 0xFFFFFFFFU;
}

LITE_OS_SEC_TEXT_MINOR UINT64 LOS_CurrNanosec(VOID)
{
    DOUBLE nanos;

    nanos = (DOUBLE)HalClockGetCycles() * OS_SYS_NS_PER_SECOND / g_sysClock;
    return (UINT64)nanos;
}

LITE_OS_SEC_TEXT_MINOR VOID LOS_Udelay(UINT32 usecs)
{
    HalDelayUs(usecs);
}

LITE_OS_SEC_TEXT_MINOR VOID LOS_Mdelay(UINT32 msecs)
{
    HalDelayUs(msecs * 1000); /* 1000 : 1ms = 1000us */
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
