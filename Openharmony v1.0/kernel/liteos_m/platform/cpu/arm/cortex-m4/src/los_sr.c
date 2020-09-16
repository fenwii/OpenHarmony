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

#include <los_builddef.h>
#include "los_sr.h"
#include "los_task.inc"
#include "los_exc.h"
#include "securec.h"
#include <los_builddef.h>
#include "los_tick.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

UINT32 uwGetSleepTick = 0;
#define OS_SYSTICK_CONTROL_REG    0xE000E010
#if(LOSCFG_BASE_CORE_TIMESLICE == YES)
extern OS_TASK_ROBIN_S g_stTaskTimeSlice;
#endif

extern TSK_SORTLINK_ATTRIBUTE_S g_stTskSortLink;

extern void set_mcu_status(UINT8 status);

UINT32  g_auwSaveSRContext[30];
UINT32  g_auwSaveAR[3];

UINT32  g_uwSrStateFlag = SENSORHUB_COLDBOOT;
#if (OS_SR_WAKEUP_INFO == YES)
OS_WAKEUP_INFO g_astWakeupInfo;
#endif

VOID osSetBasePri(UINT32 value)
{

}
void osTickLock(void)
{
#if (LOSCFG_BASE_CORE_TICK_HW_TIME == NO)
    *(volatile UINT32 *)OS_SYSTICK_CONTROL_REG = 0x5;
#else

#endif
}

void osTickUnlock(void)
{
#if (LOSCFG_BASE_CORE_TICK_HW_TIME == NO)
    *(volatile UINT32 *)OS_SYSTICK_CONTROL_REG = 0x7;
#else

#endif
}

UINT32  osDelayTskSuspend()
{
    LOS_TASK_CB *pstTaskCB = NULL;
    UINT64 delta = (UINT64)-1;
    UINT16 usCursor = (UINT16)-1;
    LOS_DL_LIST *pstListObject = NULL;
    UINT32 min = 0x07ffffff;
    UINT32 min_record = (UINT32)-1;
    UINT32 i;

    usCursor = (g_stTskSortLink.usCursor + 1) % OS_TSK_SORTLINK_LEN;

    for(i = 0; i < OS_TSK_SORTLINK_LEN; i++)
    {
        pstListObject = g_stTskSortLink.pstSortLink + (usCursor + i) % OS_TSK_SORTLINK_LEN;
        if(pstListObject->pstNext != pstListObject)
        {
            pstTaskCB = LOS_DL_LIST_ENTRY((pstListObject)->pstNext, LOS_TASK_CB, stTimerList);/*lint  !e413*/
            if(UWROLLNUM(pstTaskCB->uwIdxRollNum) < min)
            {
                min = UWROLLNUM(pstTaskCB->uwIdxRollNum);
                min_record = (usCursor + i) % OS_TSK_SORTLINK_LEN;
            }
        }
    }

    if(min == 0x07ffffff)
    {
        return 0xFFFFFFFF;
    }
    else
    {
        pstTaskCB = LOS_DL_LIST_ENTRY(((LOS_DL_LIST *)(g_stTskSortLink.pstSortLink + min_record))->pstNext, LOS_TASK_CB, stTimerList);/*lint  !e413*/

        if(min_record >= usCursor)
        {
            delta = (UINT64)((min_record-(UINT32)usCursor) + UWROLLNUM(pstTaskCB->uwIdxRollNum) * OS_TSK_SORTLINK_LEN + 1);
        }
        else
        {
            delta = (UINT64)((OS_TSK_SORTLINK_LEN - (UINT32)usCursor) + min_record + UWROLLNUM(pstTaskCB->uwIdxRollNum) * OS_TSK_SORTLINK_LEN +1);
        }
    }

    if (delta & (((UINT64)-1) << 32)) /* lint !e648 */
    {
        return 0xFFFFFFFF;
    }

    return (UINT32)delta;
}

VOID osDelayTskResume(UINT32 sleep_time)
{
    int i;

#if(LOSCFG_BASE_CORE_TIMESLICE == YES)
    g_stTaskTimeSlice.pstTask = (LOS_TASK_CB *)NULL;
#endif

    g_ullTickCount += sleep_time;
    if(sleep_time == 0)
        return;

    if(sleep_time > uwGetSleepTick)
    {
        sleep_time = uwGetSleepTick;
    }

    for(i = sleep_time; i > 0; i--)
    {
        osTaskScan();
    }
}

#if (LOSCFG_BASE_CORE_SWTMR == YES)
UINT32 osSwtimerSuspend()
{
    return osSwTmrGetNextTimeout();
}
#endif
VOID osSwtimerResume(UINT32 sleep_time)
{
    osSwTmrAdjust(sleep_time);
}

 UINT32 osGetSleepTime()
{
    UINT32 task = 0xFFFFFFFF;
    UINT32 timer = 0xFFFFFFFF;

    task = osDelayTskSuspend();
    #if (LOSCFG_BASE_CORE_SWTMR == YES)
    timer = osSwtimerSuspend();
    #endif
    PRINT_DEBUG("Ta:%d,Ti=%d\n",task,timer);

    return task < timer ? task : timer;
}


VOID LOS_SystemWakeup();

extern MC_BOOL MC_SYS_CheckSuspendCondition(MC_VOID);
extern int sys_suspend(void);
VOID LOS_SrIdleTaskProcess()
{
    __disable_irq();
    osTickLock();
    uwGetSleepTick = osGetSleepTime();

    if (uwGetSleepTick > 10)
    {
        if(!sys_suspend() || (FALSE == MC_SYS_CheckSuspendCondition()))
        {
            osTickUnlock();
            __enable_irq();
            return;
        }
        g_uwSrStateFlag = SENSORHUB_SLEEP;
        if(g_uwSrStateFlag == SENSORHUB_SLEEP) // if any irq before or after __enable_irq, that is befor this condition
        {
#ifdef CHIP_APOLLO
            enterSleepMode(uwGetSleepTick);
            __enable_irq();
#else
            enterStopMode(uwGetSleepTick);
            osTickUnlock();
            __enable_irq();
#endif
        }
        else
        {
            osTickUnlock();
            __enable_irq();
        }
    }
    else
    {
        osTickUnlock();
        __enable_irq();
    }
}

/*****************************************************************************
 Function     : LOS_SystemWakeup
 Description  : System Wakeup function
 Input        : uwHwiIndex  --- Make sure it comes from a valid interrupt number.
 Output       : None
 Return       : None
 *****************************************************************************/
VOID LOS_SystemWakeup(UINT32 uwHwiIndex)
{
    UINT32 uwWakeupTick = 0;
    osTickLock();
    uwWakeupTick = getSleepTime();
    if(uwWakeupTick > uwGetSleepTick)
    {
        uwWakeupTick = uwGetSleepTick;
    }
    // modify delay task list
    osDelayTskResume(uwWakeupTick);
    // modify timer list
    #if (LOSCFG_BASE_CORE_SWTMR == YES)
    osSwtimerResume(uwWakeupTick);
    #endif
    #if (OS_SR_WAKEUP_INFO == YES)
    g_astWakeupInfo.uwSleepTimeTotal += uwWakeupTick;
    g_astWakeupInfo.auwPID[g_astWakeupInfo.ucIdx] = uwHwiIndex;
    if (++g_astWakeupInfo.ucIdx == OS_WAKEUP_INFO_COUNT)
    {
        g_astWakeupInfo.ucIdx = 0;
        g_astWakeupInfo.ucIsFull = 1;
    }
    #endif
    osTickUnlock();
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
