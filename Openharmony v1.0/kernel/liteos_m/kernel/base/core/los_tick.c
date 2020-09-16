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

#include "los_tick_pri.h"
#include "los_base_pri.h"
#include "los_swtmr_pri.h"
#include "los_task_pri.h"
#include "los_timeslice_pri.h"
#if (LOSCFG_KERNEL_TICKLESS == YES)
#include "los_tickless_pri.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

LITE_OS_SEC_BSS UINT64 g_ullTickCount;
LITE_OS_SEC_BSS UINT32 g_ticksPerSec;
LITE_OS_SEC_BSS UINT32 g_uwCyclePerSec;
LITE_OS_SEC_BSS UINT32 g_cyclesPerTick;
LITE_OS_SEC_BSS UINT32 g_sysClock;

#if (LOSCFG_BASE_CORE_TICK_HW_TIME == YES)
extern VOID platform_tick_handler(VOID);
#endif

#if (LOSCFG_KERNEL_TICKLESS == YES)
LITE_OS_SEC_TEXT VOID OsTickHandlerLoop(UINT32 elapseTicks)
{
    UINT32 index;

    for (index = 0; index < elapseTicks; index++) {
#if (LOSCFG_BASE_CORE_TICK_HW_TIME == YES)
        platform_tick_handler();
#endif

        g_ullTickCount++;

#if (LOSCFG_BASE_CORE_TIMESLICE == YES)
        OsTimesliceCheck();
#endif
        OsTaskScan();  // task timeout scan
#if (LOSCFG_BASE_CORE_SWTMR == YES)
        (VOID)OsSwtmrScan();
#endif
    }
}

#endif

LITE_OS_SEC_TEXT VOID OsTickHandler(VOID)
{
#if (LOSCFG_KERNEL_TICKLESS == YES)
    if (g_reloadSysTickFlag) {
        LOS_SysTickReload(g_cyclesPerTick);
        g_reloadSysTickFlag = 0;
    }
    g_tickIrqFlag = g_ticklessFlag;
#endif

#if (LOSCFG_BASE_CORE_TICK_HW_TIME == YES)
    platform_tick_handler();
#endif

    g_ullTickCount++;

#if (LOSCFG_BASE_CORE_TIMESLICE == YES)
    OsTimesliceCheck();
#endif

    OsTaskScan();  // task timeout scan

#if (LOSCFG_BASE_CORE_SWTMR == YES)
    (VOID)OsSwtmrScan();
#endif
}

UINT32 LOS_SysClockGet(VOID)
{
    return g_sysClock;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
