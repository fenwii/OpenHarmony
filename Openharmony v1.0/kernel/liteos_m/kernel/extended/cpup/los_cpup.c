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

#include "string.h"
#include "securec.h"
#include "los_cpup_pri.h"
#include "los_task_pri.h"
#include "los_memory_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#if (LOSCFG_BASE_CORE_CPUP == YES)

/**
 * @ingroup los_cpup
 * CPU usage-type macro: used for tasks.
 */
#define OS_THREAD_TYPE_TASK     0

/**
 * @ingroup los_cpup
 * CPU usage-type macro: used for hardware interrupts.
 */
#define OS_THREAD_TYPE_HWI      1

LITE_OS_SEC_BSS UINT16    g_cpupInitFlg = 0;
LITE_OS_SEC_BSS OsCpupCB  *g_cpup = NULL;
LITE_OS_SEC_BSS UINT64    g_lastRecordTime;
LITE_OS_SEC_BSS UINT16    g_hisPos; /* <current Sampling point of historyTime */
extern VOID LOS_GetCpuCycle(UINT32 *cntHi, UINT32 *cntLo);
#define OS_CPUP_RECORD_PERIOD   (g_sysClock)
/*****************************************************************************
Function   : OsCpupInit
Description: initialization of CPUP
Input      : None
Return     : LOS_OK or Error Information
*****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsCpupInit()
{
    UINT32 size;

    size = g_taskMaxNum * sizeof(OsCpupCB);
    g_cpup = (OsCpupCB *)LOS_MemAlloc(m_aucSysMem0, size);

    if (g_cpup == NULL) {
        return LOS_ERRNO_CPUP_NO_MEMORY;
    }

    // Ignore the return code when matching CSEC rule 6.6(3).
    (VOID)memset_s(g_cpup, size, 0, size);
    g_cpupInitFlg = 1;

    return LOS_OK;
}

/*****************************************************************************
Function   : OsGetCpuCycle
Description: get current cycles count
Input      : None
Return     : current cycles count
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT64 OsGetCpuCycle(VOID)
{
    UINT32 high = 0;
    UINT32 low = 0;
    LOS_GetCpuCycle(&high, &low);
    return (((UINT64)high << 32) + low); // 32 means bits of word
}
/*****************************************************************************
Function   : OsTskCycleStart
Description: start task to get cycles count in current task begining
Input      : None
Return     : None
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR VOID OsTskCycleStart(VOID)
{
    UINT32 taskID;

    if (g_cpupInitFlg == 0) {
        return;
    }

    taskID = g_losTask.newTask->taskID;
    g_cpup[taskID].cpupID = taskID;
    g_cpup[taskID].startTime = OsGetCpuCycle();

    return;
}
/*****************************************************************************
Function   : OsTskCycleEnd
Description: quit task and get cycle count
Input      : None
Return     : None
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR VOID OsTskCycleEnd(VOID)
{
    UINT32 taskID;
    UINT64 cpuCycle;

    if (g_cpupInitFlg == 0) {
        return;
    }

    taskID = g_losTask.runTask->taskID;

    if (g_cpup[taskID].startTime == 0) {
        return;
    }

    cpuCycle = OsGetCpuCycle();

    if (cpuCycle < g_cpup[taskID].startTime) {
        cpuCycle += g_cyclesPerTick;
    }

    g_cpup[taskID].allTime += (cpuCycle - g_cpup[taskID].startTime);
    g_cpup[taskID].startTime = 0;

    return;
}
/*****************************************************************************
Function   : OsTskCycleEndStart
Description: start task to get cycles count in current task ending
Input      : None
Return     : None
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR VOID OsTskCycleEndStart(VOID)
{
    UINT32 taskID;
    UINT64 cpuCycle;
    UINT16 loopNum;

    if (g_cpupInitFlg == 0) {
        return;
    }

    taskID = g_losTask.runTask->taskID;
    cpuCycle = OsGetCpuCycle();

    if (g_cpup[taskID].startTime != 0) {
        if (cpuCycle < g_cpup[taskID].startTime) {
            cpuCycle += g_cyclesPerTick;
        }

        g_cpup[taskID].allTime += (cpuCycle - g_cpup[taskID].startTime);
        g_cpup[taskID].startTime = 0;
    }

    taskID = g_losTask.newTask->taskID;
    g_cpup[taskID].cpupID = taskID;
    g_cpup[taskID].startTime = cpuCycle;

    if ((cpuCycle - g_lastRecordTime) > OS_CPUP_RECORD_PERIOD) {
        g_lastRecordTime = cpuCycle;

        for (loopNum = 0; loopNum < g_taskMaxNum; loopNum++) {
            g_cpup[loopNum].historyTime[g_hisPos] = g_cpup[loopNum].allTime;
        }

        if (g_hisPos == (OS_CPUP_HISTORY_RECORD_NUM - 1)) {
            g_hisPos = 0;
        } else {
            g_hisPos++;
        }
    }

    return;
}

LITE_OS_SEC_TEXT_MINOR static inline UINT16 OsGetPrePos(UINT16 curPos)
{
    return (curPos == 0) ? (OS_CPUP_HISTORY_RECORD_NUM - 1) : (curPos - 1);
}

LITE_OS_SEC_TEXT_MINOR static VOID OsGetPositions(UINT16 mode, UINT16* curPosAddr, UINT16* prePosAddr)
{
    UINT16 curPos;
    UINT16 prePos = 0;

    curPos = g_hisPos;

    if (mode == CPUP_IN_1S) {
        curPos = OsGetPrePos(curPos);
        prePos = OsGetPrePos(curPos);
    } else if (mode == CPUP_LESS_THAN_1S) {
        curPos = OsGetPrePos(curPos);
    }

    *curPosAddr = curPos;
    *prePosAddr = prePos;
}

/*****************************************************************************
Function   : LOS_SysCpuUsage
Description: get current CPU usage
Input      : None
Return     : cpupRet:current CPU usage
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_SysCpuUsage(VOID)
{
    UINT64  cpuCycleAll = 0;
    UINT32  cpupRet = 0;
    UINT16  loopNum;
    UINTPTR intSave;

    if (g_cpupInitFlg == 0) {
        return LOS_ERRNO_CPUP_NO_INIT;
    }

    // get end time of current task
    intSave = LOS_IntLock();
    OsTskCycleEnd();

    for (loopNum = 0; loopNum < g_taskMaxNum; loopNum++) {
        cpuCycleAll += g_cpup[loopNum].allTime;
    }

    if (cpuCycleAll) {
        cpupRet = LOS_CPUP_PRECISION -  (UINT32)((LOS_CPUP_PRECISION *
            g_cpup[g_idleTaskID].allTime) / cpuCycleAll);
    }

    OsTskCycleStart();
    LOS_IntRestore(intSave);

    return cpupRet;
}

/*****************************************************************************
Function   : LOS_HistorySysCpuUsage
Description: get CPU usage history
Input      : mode: mode,0 = usage in 10s,1 = usage in last 1s, else = less than 1s
Return     : cpupRet:CPU usage history
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_HistorySysCpuUsage(UINT16 mode)
{
    UINT64  cpuCycleAll = 0;
    UINT64  idleCycleAll = 0;
    UINT32  cpupRet = 0;
    UINT16  loopNum;
    UINT16  curPos;
    UINT16  prePos = 0;
    UINTPTR intSave;

    if (g_cpupInitFlg == 0) {
        return LOS_ERRNO_CPUP_NO_INIT;
    }

    // get end time of current task
    intSave = LOS_IntLock();
    OsTskCycleEnd();

    OsGetPositions(mode, &curPos, &prePos);

    for (loopNum = 0; loopNum < g_taskMaxNum; loopNum++) {
        if (mode == CPUP_IN_1S) {
            cpuCycleAll += g_cpup[loopNum].historyTime[curPos] - g_cpup[loopNum].historyTime[prePos];
        } else {
            cpuCycleAll += g_cpup[loopNum].allTime - g_cpup[loopNum].historyTime[curPos];
        }
    }

    if (mode == CPUP_IN_1S) {
        idleCycleAll += g_cpup[g_idleTaskID].historyTime[curPos] -
                           g_cpup[g_idleTaskID].historyTime[prePos];
    } else {
        idleCycleAll += g_cpup[g_idleTaskID].allTime - g_cpup[g_idleTaskID].historyTime[curPos];
    }

    if (cpuCycleAll) {
        cpupRet = (LOS_CPUP_PRECISION -  (UINT32)((LOS_CPUP_PRECISION * idleCycleAll) / cpuCycleAll));
    }

    OsTskCycleStart();
    LOS_IntRestore(intSave);

    return cpupRet;
}

/*****************************************************************************
Function   : LOS_TaskCpuUsage
Description: get CPU usage of certain task
Input      : taskID : task ID
Return     : cpupRet:CPU usage of certain task
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskCpuUsage(UINT32 taskID)
{
    UINT64  cpuCycleAll = 0;
    UINT16  loopNum;
    UINTPTR intSave;
    UINT32  cpupRet = 0;

    if (g_cpupInitFlg == 0) {
        return LOS_ERRNO_CPUP_NO_INIT;
    }
    if (OS_TSK_GET_INDEX(taskID) >= g_taskMaxNum) {
        return LOS_ERRNO_CPUP_TSK_ID_INVALID;
    }
    if (g_cpup[taskID].cpupID != taskID) {
        return LOS_ERRNO_CPUP_THREAD_NO_CREATED;
    }
    if ((g_cpup[taskID].status & OS_TASK_STATUS_UNUSED) || (g_cpup[taskID].status == 0)) {
        return LOS_ERRNO_CPUP_THREAD_NO_CREATED;
    }
    intSave = LOS_IntLock();
    OsTskCycleEnd();

    /* get total Cycle */
    for (loopNum = 0; loopNum < g_taskMaxNum; loopNum++) {
        if ((g_cpup[loopNum].status & OS_TASK_STATUS_UNUSED) || (g_cpup[loopNum].status == 0)) {
            continue;
        }
        cpuCycleAll += g_cpup[loopNum].allTime;
    }

    if (cpuCycleAll) {
        cpupRet = (UINT32)((LOS_CPUP_PRECISION * g_cpup[taskID].allTime) / cpuCycleAll);
    }

    OsTskCycleStart();
    LOS_IntRestore(intSave);

    return cpupRet;
}

/*****************************************************************************
Function   : LOS_HistoryTaskCpuUsage
Description: get CPU usage history of certain task
Input      : taskID : task ID
           : mode: mode,0 = usage in 10s,1 = usage in last 1s, else = less than 1s
Return     : cpupRet:CPU usage history of task
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_HistoryTaskCpuUsage(UINT32 taskID, UINT16 mode)
{
    UINT64  cpuCycleAll = 0;
    UINT64  cpuCycleCurTsk = 0;
    UINT16  loopNum, curPos;
    UINT16  prePos = 0;
    UINTPTR intSave;
    UINT32  cpupRet = 0;

    if (g_cpupInitFlg == 0) {
        return LOS_ERRNO_CPUP_NO_INIT;
    }
    if (OS_TSK_GET_INDEX(taskID) >= g_taskMaxNum) {
        return LOS_ERRNO_CPUP_TSK_ID_INVALID;
    }
    if (g_cpup[taskID].cpupID != taskID) {
        return LOS_ERRNO_CPUP_THREAD_NO_CREATED;
    }
    if ((g_cpup[taskID].status & OS_TASK_STATUS_UNUSED) || (g_cpup[taskID].status == 0)) {
        return LOS_ERRNO_CPUP_THREAD_NO_CREATED;
    }
    intSave = LOS_IntLock();
    OsTskCycleEnd();

    OsGetPositions(mode, &curPos, &prePos);

    /* get total Cycle in history */
    for (loopNum = 0; loopNum < g_taskMaxNum; loopNum++) {
        if ((g_cpup[loopNum].status & OS_TASK_STATUS_UNUSED) || (g_cpup[loopNum].status == 0)) {
            continue;
        }

        if (mode == CPUP_IN_1S) {
            cpuCycleAll += g_cpup[loopNum].historyTime[curPos] - g_cpup[loopNum].historyTime[prePos];
        } else {
            cpuCycleAll += g_cpup[loopNum].allTime - g_cpup[loopNum].historyTime[curPos];
        }
    }

    if (mode == CPUP_IN_1S) {
        cpuCycleCurTsk += g_cpup[taskID].historyTime[curPos] - g_cpup[taskID].historyTime[prePos];
    } else {
        cpuCycleCurTsk += g_cpup[taskID].allTime - g_cpup[taskID].historyTime[curPos];
    }
    if (cpuCycleAll) {
        cpupRet = (UINT32)((LOS_CPUP_PRECISION * cpuCycleCurTsk) / cpuCycleAll);
    }

    OsTskCycleStart();
    LOS_IntRestore(intSave);

    return cpupRet;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_AllTaskCpuUsage(CPUP_INFO_S *cpupInfo, UINT16 mode)
{
    UINT16  loopNum;
    UINT16  curPos;
    UINT16  prePos = 0;
    UINTPTR intSave;
    UINT64  cpuCycleAll = 0;
    UINT64  cpuCycleCurTsk = 0;

    if (g_cpupInitFlg == 0) {
        return  LOS_ERRNO_CPUP_NO_INIT;
    }

    if (cpupInfo == NULL) {
        return LOS_ERRNO_CPUP_TASK_PTR_NULL;
    }

    intSave = LOS_IntLock();
    OsTskCycleEnd();

    OsGetPositions(mode, &curPos, &prePos);

    for (loopNum = 0; loopNum < g_taskMaxNum; loopNum++) {
        if ((g_cpup[loopNum].status & OS_TASK_STATUS_UNUSED) ||
            (g_cpup[loopNum].status == 0)) {
            continue;
        }

        if (mode == CPUP_IN_1S) {
            cpuCycleAll += g_cpup[loopNum].historyTime[curPos] - g_cpup[loopNum].historyTime[prePos];
        } else {
            cpuCycleAll += g_cpup[loopNum].allTime - g_cpup[loopNum].historyTime[curPos];
        }
    }

    for (loopNum = 0; loopNum < g_taskMaxNum; loopNum++) {
        if ((g_cpup[loopNum].status & OS_TASK_STATUS_UNUSED) ||
            (g_cpup[loopNum].status == 0)) {
            continue;
        }

        if (mode == CPUP_IN_1S) {
            cpuCycleCurTsk += g_cpup[loopNum].historyTime[curPos] - g_cpup[loopNum].historyTime[prePos];
        } else {
            cpuCycleCurTsk += g_cpup[loopNum].allTime - g_cpup[loopNum].historyTime[curPos];
        }
        cpupInfo[loopNum].usStatus = g_cpup[loopNum].status;
        if (cpuCycleAll) {
            cpupInfo[loopNum].uwUsage = (UINT32)((LOS_CPUP_PRECISION * cpuCycleCurTsk) / cpuCycleAll);
        }

        cpuCycleCurTsk = 0;
    }

    OsTskCycleStart();
    LOS_IntRestore(intSave);

    return LOS_OK;
}

/*****************************************************************************
Function   : LOS_CpupUsageMonitor
Description: Get CPU usage history of certain task.
Input      : type: cpup type, SYS_CPU_USAGE and TASK_CPU_USAGE
           : taskID: task ID, Only in SYS_CPU_USAGE type, taskID is invalid
           : mode: mode, CPUP_IN_10S = usage in 10s, CPUP_IN_1S = usage in last 1s, CPUP_LESS_THAN_1S = less than 1s
Return     : LOS_OK on success, or OS_ERROR on failure
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_CpupUsageMonitor(CPUP_TYPE_E type, CPUP_MODE_E mode, UINT32 taskID)
{
    UINT32 ret;
    LosTaskCB *taskCB = NULL;

    switch (type) {
        case SYS_CPU_USAGE:
            if (mode == CPUP_IN_10S) {
                PRINTK("\nSysCpuUsage in 10s: ");
            } else if (mode == CPUP_IN_1S) {
                PRINTK("\nSysCpuUsage in 1s: ");
            } else {
                PRINTK("\nSysCpuUsage in <1s: ");
            }
            ret = LOS_HistorySysCpuUsage(mode);
            PRINTK("%d.%d", ret / LOS_CPUP_PRECISION_MULT, ret % LOS_CPUP_PRECISION_MULT);
            break;

        case TASK_CPU_USAGE:
            if (taskID > LOSCFG_BASE_CORE_TSK_LIMIT) {
                PRINT_ERR("\nThe taskid is invalid.\n");
                return OS_ERROR;
            }
            taskCB = OS_TCB_FROM_TID(taskID);
            if ((taskCB->taskStatus & OS_TASK_STATUS_UNUSED)) {
                PRINT_ERR("\nThe taskid is invalid.\n");
                return OS_ERROR;
            }
            if (mode == CPUP_IN_10S) {
                PRINTK("\nCPUusage of taskID %d in 10s: ", taskID);
            } else if (mode == CPUP_IN_1S) {
                PRINTK("\nCPUusage of taskID %d in 1s: ", taskID);
            } else {
                PRINTK("\nCPUusage of taskID %d in <1s: ", taskID);
            }
            ret = LOS_HistoryTaskCpuUsage(taskID, mode);
            PRINTK("%u.%u", ret / LOS_CPUP_PRECISION_MULT, ret % LOS_CPUP_PRECISION_MULT);
            break;

        default:
            PRINT_ERR("\nThe type is invalid.\n");
            return OS_ERROR;
    }

    return LOS_OK;
}

#endif /* LOSCFG_BASE_CORE_CPUP */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
