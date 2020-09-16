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
#include "los_task_pri.h"
#include "los_tick_pri.h"
#include "los_typedef_pri.h"
#include "los_timeslice_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#if (LOSCFG_BASE_CORE_TIMESLICE == YES)
LITE_OS_SEC_BSS OsTaskRobin g_taskTimeSlice;

/*****************************************************************************
 Function     : OsTimesliceInit
 Description  : Initialztion Timeslice
 Input        : None
 Output       : None
 Return       : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT VOID OsTimesliceInit(VOID)
{
    g_taskTimeSlice.task = (LosTaskCB *)NULL;
    g_taskTimeSlice.tout = LOSCFG_BASE_CORE_TIMESLICE_TIMEOUT;
}

/*****************************************************************************
 Function     : OsTimesliceCheck
 Description  : check Timeslice
 Input        : None
 Output       : None
 Return       : None
 *****************************************************************************/
LITE_OS_SEC_TEXT VOID OsTimesliceCheck(VOID)
{
    if (g_taskTimeSlice.task != g_losTask.runTask) {
        g_taskTimeSlice.task = g_losTask.runTask;
        g_taskTimeSlice.time = ((UINT16)g_ullTickCount + g_taskTimeSlice.tout) - 1;
    }

    if (g_taskTimeSlice.time  == (UINT16)g_ullTickCount) {
        g_taskTimeSlice.task = (LosTaskCB *)NULL;
        if (LOS_TaskYield() != LOS_OK) {
            PRINT_INFO("%s, %d\n", __FUNCTION__, __LINE__);
        }
    }
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

