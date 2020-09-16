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

#include "los_task_pri.h"
#include "string.h"
#include "securec.h"
#include "los_base_pri.h"
#include "los_memory_pri.h"
#include "los_memstat_pri.h"
#include "los_priqueue_pri.h"
#include "los_sem_pri.h"
#include "los_mux_pri.h"
#if (LOSCFG_PLATFORM_EXC == YES)
#include "los_exc_pri.h"
#endif
#if (LOSCFG_KERNEL_TICKLESS == YES)
#include "los_tickless_pri.h"
#endif
#if (LOSCFG_BASE_CORE_CPUP == YES)
#include "los_cpup_pri.h"
#endif
#include "los_hw.h"

#if (LOSCFG_KERNEL_TRACE == YES)
#include "los_trace.h"
#endif
#include "los_sleep.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup los_task
 * @brief Convinence macro for bitwise operation of task module
 */
#define EVALUATE_L(NUMBER, VALUE)  \
            ((NUMBER) = (((NUMBER) & 0xf8000000) | (VALUE)))

#define EVALUATE_H(NUMBER, VALUE)  \
            ((NUMBER) = (((NUMBER) & 0x07ffffff) | ((VALUE) << 27)))

#define UWROLLNUMSUB(NUMBER1, NUMBER2)  \
            ((NUMBER1) = (((NUMBER1) & 0xf8000000) | (UWROLLNUM(NUMBER1) - UWROLLNUM(NUMBER2))))

#define UWROLLNUMADD(NUMBER1, NUMBER2)  \
            ((NUMBER1) = (((NUMBER1) & 0xf8000000) | (UWROLLNUM(NUMBER1) + UWROLLNUM(NUMBER2))))

#define UWROLLNUM(NUMBER) ((NUMBER) & 0x07ffffff)

#define UWSORTINDEX(NUMBER) ((NUMBER) >> 27)

#define UWROLLNUMDEC(NUMBER)  \
            ((NUMBER) = ((NUMBER) - 1))


#define OS_CHECK_TASK_BLOCK                     (OS_TASK_STATUS_DELAY | \
                                                 OS_TASK_STATUS_PEND | \
                                                 OS_TASK_STATUS_SUSPEND | \
                                                 OS_TASK_STATUS_EVENT | \
                                                 OS_TASK_STATUS_PEND_QUEUE)

/**
 * @ingroup los_task
 * @brief check taks id's validation
 */
#define OS_TASK_ID_CHECK(taskID)              LOS_ASSERT_COND(OS_TSK_GET_INDEX(taskID) < g_taskMaxNum)

/**
 * @ingroup los_task
 * @brief check taks id's invalidation
 */
#define OS_CHECK_TSK_PID_NOIDLE(taskID)       (OS_TSK_GET_INDEX(taskID) >= g_taskMaxNum)

/**
 * @ingroup los_task
 * @brief the offset of task stack's top for skipping the magic word
 */
#define OS_TASK_STACK_TOP_OFFSET                4

LITE_OS_SEC_BSS  LosTaskCB                           *g_taskCBArray = NULL;
LITE_OS_SEC_BSS  LosTask                             g_losTask;
LITE_OS_SEC_BSS  UINT16                              g_losTaskLock;
LITE_OS_SEC_BSS  UINT32                              g_taskMaxNum;
LITE_OS_SEC_BSS  UINT32                              g_idleTaskID;
LITE_OS_SEC_BSS  UINT32                              g_swtmrTaskID;
LITE_OS_SEC_DATA_INIT LOS_DL_LIST                    g_losFreeTask;
LITE_OS_SEC_DATA_INIT LOS_DL_LIST                    g_taskRecyleList;
LITE_OS_SEC_BSS  TaskSortLinkAttr                    g_taskSortLink;
LITE_OS_SEC_BSS  BOOL                                g_taskScheduled = FALSE;

#if (LOSCFG_BASE_CORE_TSK_MONITOR == YES)

TSKSWITCHHOOK g_taskSwitchHook = NULL;
TSKSWITCHHOOK g_pfnUsrTskSwitchHook = NULL;
#endif /* LOSCFG_BASE_CORE_TSK_MONITOR == YES */

#if (LOSCFG_BASE_CORE_EXC_TSK_SWITCH == YES)

TaskSwitchInfo g_taskSwitchInfo;
#endif

STATIC_INLINE UINT32 OsCheckTaskIDValid(UINT32 taskID)
{
    UINT32 ret = LOS_OK;
    if (taskID == g_idleTaskID) {
        ret = LOS_ERRNO_TSK_OPERATE_IDLE;
    } else if (taskID == g_swtmrTaskID) {
        ret = LOS_ERRNO_TSK_SUSPEND_SWTMR_NOT_ALLOWED;
    } else if (OS_TSK_GET_INDEX(taskID) >= g_taskMaxNum) {
        ret = LOS_ERRNO_TSK_ID_INVALID;
    }
    return ret;
}

#if (LOSCFG_KERNEL_TICKLESS == YES)
UINT32 OsTaskNextSwitchTimeGet(VOID)
{
    LosTaskCB *taskCB = NULL;
    UINT32 taskSortLinkTick = 0;
    LOS_DL_LIST *listObject = NULL;
    UINT32 tempTicks = 0;
    UINT32 index;

    for (index = 0; index < OS_TSK_SORTLINK_LEN; index++) {
        listObject = g_taskSortLink.sortLink + ((g_taskSortLink.cursor + index) % OS_TSK_SORTLINK_LEN);
        if (listObject->pstNext != listObject) {
            taskCB = LOS_DL_LIST_ENTRY((listObject)->pstNext, LosTaskCB, timerList);
            tempTicks = (index == 0) ? OS_TSK_SORTLINK_LEN : index;
            tempTicks += (UINT32)(UWROLLNUM(taskCB->idxRollNum) * OS_TSK_SORTLINK_LEN);
            if ((taskSortLinkTick == 0) || (taskSortLinkTick > tempTicks)) {
                taskSortLinkTick = tempTicks;
            }
        }
    }

    return taskSortLinkTick;
}
#endif

/*****************************************************************************
 Function    : OsIdleTask
 Description : Idle task.
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT WEAK VOID OsIdleTask(VOID)
{
    while (1) {
#if (LOSCFG_KERNEL_TICKLESS == YES)
        if (g_tickIrqFlag) {
            g_tickIrqFlag = 0;
            OsTicklessStart();
        }
#endif
#if (LOSCFG_KERNEL_RUNSTOP == YES)
        LOS_EnterSleep(OS_SYS_NORMAL_SLEEP);
#endif
    }
}

/*****************************************************************************
 Function    : OsTaskPriModify
 Description : Change task priority.
 Input       : taskCB    --- task control block
               priority  --- priority
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_MINOR VOID OsTaskPriModify(LosTaskCB *taskCB, UINT16 priority)
{
    if (taskCB->taskStatus & OS_TASK_STATUS_READY) {
        OsPriqueueDequeue(&taskCB->pendList);
        taskCB->taskStatus &= (~OS_TASK_STATUS_READY);
        taskCB->priority = priority;
        taskCB->taskStatus |= OS_TASK_STATUS_READY;
        OsPriqueueEnqueue(&taskCB->pendList, taskCB->priority);
    } else {
        taskCB->priority = priority;
    }
}

/*****************************************************************************
 Function    : OsTaskAdd2TimerList
 Description : Add task to sorted delay list.
 Input       : taskCB    --- task control block
               timeout   --- wait time, ticks
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT VOID OsTaskAdd2TimerList(LosTaskCB *taskCB, UINT32 timeout)
{
    LosTaskCB *taskDelay = NULL;
    LOS_DL_LIST *listObject = NULL;
    UINT32 sortIndex;
    UINT32 rollNum;

    sortIndex = timeout & OS_TSK_SORTLINK_MASK;
    rollNum = (timeout >> OS_TSK_SORTLINK_LOGLEN);
    (sortIndex > 0) ? 0 : (rollNum--);
    EVALUATE_L(taskCB->idxRollNum, rollNum);
    sortIndex = (sortIndex + g_taskSortLink.cursor);
    sortIndex = sortIndex & OS_TSK_SORTLINK_MASK;
    EVALUATE_H(taskCB->idxRollNum, sortIndex);
    listObject = g_taskSortLink.sortLink + sortIndex;
    if (listObject->pstNext == listObject) {
        LOS_ListTailInsert(listObject, &taskCB->timerList);
    } else {
        taskDelay = LOS_DL_LIST_ENTRY((listObject)->pstNext, LosTaskCB, timerList);
        do {
            if (UWROLLNUM(taskDelay->idxRollNum) <= UWROLLNUM(taskCB->idxRollNum)) {
                UWROLLNUMSUB(taskCB->idxRollNum, taskDelay->idxRollNum);
            } else {
                UWROLLNUMSUB(taskDelay->idxRollNum, taskCB->idxRollNum);
                break;
            }

            taskDelay = LOS_DL_LIST_ENTRY(taskDelay->timerList.pstNext, LosTaskCB, timerList);
        } while (&taskDelay->timerList != (listObject));

        LOS_ListTailInsert(&taskDelay->timerList, &taskCB->timerList);
    }
}


LITE_OS_SEC_TEXT VOID OsTimerListDelete(LosTaskCB *taskCB)
{
    LOS_DL_LIST  *listObject = NULL;
    LosTaskCB  *nextTask = NULL;
    UINT32 sortIndex;

    sortIndex = UWSORTINDEX(taskCB->idxRollNum);
    listObject = g_taskSortLink.sortLink + sortIndex;

    if (listObject != taskCB->timerList.pstNext) {
        nextTask = LOS_DL_LIST_ENTRY(taskCB->timerList.pstNext, LosTaskCB, timerList);
        UWROLLNUMADD(nextTask->idxRollNum, taskCB->idxRollNum);
    }

    LOS_ListDelete(&taskCB->timerList);
}

LITE_OS_SEC_TEXT VOID OsTaskScan(VOID)
{
    LosTaskCB *taskCB = NULL;
    BOOL needSchedule = FALSE;
    LOS_DL_LIST *listObject = NULL;
    UINT16 tempStatus;
    UINTPTR intSave;
    intSave = LOS_IntLock();

    g_taskSortLink.cursor = (g_taskSortLink.cursor + 1) % OS_TSK_SORTLINK_LEN;
    listObject = g_taskSortLink.sortLink + g_taskSortLink.cursor;
    if (listObject->pstNext == listObject) {
        LOS_IntRestore(intSave);
        return;
    }

    for (taskCB = LOS_DL_LIST_ENTRY((listObject)->pstNext, LosTaskCB, timerList);
         &taskCB->timerList != (listObject);) {
        tempStatus = taskCB->taskStatus;
        if (UWROLLNUM(taskCB->idxRollNum) > 0) {
            UWROLLNUMDEC(taskCB->idxRollNum);
            break;
        }

        LOS_ListDelete(&taskCB->timerList);
        if (tempStatus & OS_TASK_STATUS_PEND) {
            taskCB->taskStatus &= ~(OS_TASK_STATUS_PEND);
            LOS_ListDelete(&taskCB->pendList);
            taskCB->taskSem = NULL;
            taskCB->taskMux = NULL;
        }
        else if (tempStatus & OS_TASK_STATUS_EVENT) {
            taskCB->taskStatus &= ~(OS_TASK_STATUS_EVENT);
        }
        else if (tempStatus & OS_TASK_STATUS_PEND_QUEUE) {
            LOS_ListDelete(&taskCB->pendList);
            taskCB->taskStatus &= ~(OS_TASK_STATUS_PEND_QUEUE);
        } else {
            taskCB->taskStatus &= ~(OS_TASK_STATUS_DELAY);
        }

        if (!(tempStatus & OS_TASK_STATUS_SUSPEND)) {
            taskCB->taskStatus |= OS_TASK_STATUS_READY;
            OsPriqueueEnqueue(&taskCB->pendList, taskCB->priority);
            needSchedule = TRUE;
        }

        if (listObject->pstNext == listObject) {
            break;
        }

        taskCB = LOS_DL_LIST_ENTRY(listObject->pstNext, LosTaskCB, timerList);
    }

    LOS_IntRestore(intSave);

    if (needSchedule) {
        LOS_Schedule();
    }
}

/*****************************************************************************
 Function    : OsConvertTskStatus
 Description : Convert task status to string.
 Input       : taskStatus    --- task status
 Output      : None
 Return      : string
 *****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT8 *OsConvertTskStatus(UINT16 taskStatus)
{
    if (taskStatus & OS_TASK_STATUS_RUNNING) {
        return (UINT8 *)"Running";
    } else if (taskStatus & OS_TASK_STATUS_READY) {
        return (UINT8 *)"Ready";
    } else if (taskStatus & OS_TASK_STATUS_DELAY) {
        return (UINT8 *)"Delay";
    } else if (taskStatus & OS_TASK_STATUS_PEND) {
        if (taskStatus & OS_TASK_STATUS_TIMEOUT) {
            return (UINT8 *)"PendTimeOut";
        }

        return (UINT8 *)"Pend";
    } else if (taskStatus & OS_TASK_STATUS_SUSPEND) {
        return (UINT8 *)"Suspend";
    } else if (taskStatus & OS_TASK_STATUS_PEND_QUEUE) {
        if (taskStatus & OS_TASK_STATUS_TIMEOUT) {
            return (UINT8 *)"QueuePendTimeOut";
        }

        return (UINT8 *)"QueuePend";
    }

    return (UINT8 *)"Impossible";
}

UINT32 OsGetTaskWaterLine(UINT32 taskID)
{
    UINT32 *stackPtr = NULL;
    UINT32 peakUsed;

    if (*(UINT32 *)(UINTPTR)OS_TCB_FROM_TID(taskID)->topOfStack == OS_TASK_MAGIC_WORD) {
        stackPtr = (UINT32 *)(UINTPTR)(OS_TCB_FROM_TID(taskID)->topOfStack + OS_TASK_STACK_TOP_OFFSET);
        while ((stackPtr < (UINT32 *)(OS_TCB_FROM_TID(taskID)->stackPointer)) && (*stackPtr == OS_TASK_STACK_INIT)) {
            stackPtr += 1;
        }
        peakUsed = OS_TCB_FROM_TID(taskID)->stackSize -
            ((UINT32)(UINTPTR)stackPtr - OS_TCB_FROM_TID(taskID)->topOfStack);
    } else {
        PRINT_ERR("CURRENT task %s stack overflow!\n", OS_TCB_FROM_TID(taskID)->taskName);
        peakUsed = OS_NULL_INT;
    }
    return peakUsed;
}

#if (LOSCFG_BASE_CORE_CPUP == YES)
LITE_OS_SEC_TEXT_MINOR UINT32 OsGetAllTskCpupInfo(CPUP_INFO_S **cpuLessOneSec,
                                                  CPUP_INFO_S **cpuTenSec,
                                                  CPUP_INFO_S **cpuOneSec)
{
    if ((cpuLessOneSec == NULL) || (cpuTenSec == NULL) || (cpuOneSec == NULL)) {
        return OS_ERROR;
    }
    *cpuLessOneSec = (CPUP_INFO_S *)LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR, sizeof(CPUP_INFO_S) * g_taskMaxNum);
    if (*cpuLessOneSec == NULL) {
        PRINT_ERR("%s[%d] malloc failure!\n", __FUNCTION__, __LINE__);
        return OS_ERROR;
    }
    // Ignore the return code when matching CSEC rule 6.6(3).
    (VOID)memset_s((VOID *)(*cpuLessOneSec), sizeof(CPUP_INFO_S) * g_taskMaxNum,
                   (INT32)0, sizeof(CPUP_INFO_S) * g_taskMaxNum);

    *cpuTenSec = (CPUP_INFO_S *)LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR, sizeof(CPUP_INFO_S) * g_taskMaxNum);
    if (*cpuTenSec == NULL) {
        PRINT_ERR("%s[%d] malloc failure!\n", __FUNCTION__, __LINE__);
        (VOID)LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, *cpuLessOneSec);
        *cpuLessOneSec = NULL;
        return OS_ERROR;
    }
    // Ignore the return code when matching CSEC rule 6.6(3).
    (VOID)memset_s((VOID *)(*cpuTenSec), sizeof(CPUP_INFO_S) * g_taskMaxNum,
                   (INT32)0, sizeof(CPUP_INFO_S) * g_taskMaxNum);

    *cpuOneSec = (CPUP_INFO_S *)LOS_MemAlloc((VOID *)OS_SYS_MEM_ADDR, sizeof(CPUP_INFO_S) * g_taskMaxNum);
    if (*cpuOneSec == NULL) {
        PRINT_ERR("%s[%d] malloc failure!\n", __FUNCTION__, __LINE__);
        (VOID)LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, *cpuLessOneSec);
        (VOID)LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, *cpuTenSec);
        return OS_ERROR;
    }
    // Ignore the return code when matching CSEC rule 6.6(3).
    (VOID)memset_s((VOID *)(*cpuOneSec), sizeof(CPUP_INFO_S) * g_taskMaxNum,
                   (INT32)0, sizeof(CPUP_INFO_S) * g_taskMaxNum);

    LOS_TaskLock();
    (VOID)LOS_AllTaskCpuUsage(*cpuLessOneSec, CPUP_LESS_THAN_1S);
    (VOID)LOS_AllTaskCpuUsage(*cpuTenSec, CPUP_IN_10S);
    (VOID)LOS_AllTaskCpuUsage(*cpuOneSec, CPUP_IN_1S);
    LOS_TaskUnlock();

    return LOS_OK;
}
#endif

LITE_OS_SEC_TEXT_MINOR VOID OsPrintAllTskInfoHeader()
{
    PRINT_ERR("\r\nName                          TID    Priority   Status       "
              "StackSize    WaterLine    StackPoint  TopOfStack   EventMask  SemID");
#if (LOSCFG_BASE_CORE_CPUP == YES)
    PRINT_ERR(" CPUUSE   CPUUSE10s  CPUUSE1s  ");
#endif /* LOSCFG_BASE_CORE_CPUP */
    PRINT_ERR("\n");
    PRINT_ERR("----                          ---    --------   --------     ");
    PRINT_ERR("---------    ----------   ----------  ----------   ---------  -----");
#if (LOSCFG_BASE_CORE_CPUP == YES)
    PRINT_ERR("  ------- ---------  ---------");
#endif /* LOSCFG_BASE_CORE_CPUP */
    PRINT_ERR("\n");
}

/*****************************************************************************
 Function    : OsGetAllTskInfo
 Description : Get all task info.
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 OsGetAllTskInfo(VOID)
{
    LosTaskCB    *taskCB = (LosTaskCB *)NULL;
    UINT32       loopNum;
    UINT32       semID;
#if (LOSCFG_BASE_CORE_CPUP == YES)
    CPUP_INFO_S *cpuLessOneSec = (CPUP_INFO_S *)NULL;
    CPUP_INFO_S *cpuTenSec = (CPUP_INFO_S *)NULL;
    CPUP_INFO_S *cpuOneSec = (CPUP_INFO_S *)NULL;
#endif

#if (LOSCFG_BASE_CORE_CPUP == YES)
    if (OsGetAllTskCpupInfo(&cpuLessOneSec, &cpuTenSec, &cpuOneSec) != LOS_OK) {
        return OS_ERROR;
    }
#endif

    OsPrintAllTskInfoHeader();

#if (LOSCFG_EXC_HRADWARE_STACK_PROTECTION == YES)
    UINT32 flag = osStackProtDisable();
#endif

    for (loopNum = 0; loopNum < g_taskMaxNum; loopNum++) {
        taskCB = (((LosTaskCB *)g_taskCBArray) + loopNum);
        if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
            continue;
        }

        PRINT_ERR("%-30s, 0x%-5x, %-11d, %-13s, 0x%-11x, 0x%-11x, 0x%-10x, 0x%-11x, 0x%-9x",
                  taskCB->taskName, taskCB->taskID, taskCB->priority, OsConvertTskStatus(taskCB->taskStatus),
                  taskCB->stackSize, OsGetTaskWaterLine(taskCB->taskID),
                  (UINT32)(UINTPTR)taskCB->stackPointer, taskCB->topOfStack, taskCB->eventMask);

        semID = (taskCB->taskSem == NULL) ? OS_NULL_SHORT : (((LosSemCB *)taskCB->taskSem)->semID);
        PRINT_ERR("0x%-7x", semID);

#if (LOSCFG_BASE_CORE_CPUP == YES)
        PRINT_ERR("%2d.%-7d%2d.%-9d%2d.%-6d",
                  cpuLessOneSec[taskCB->taskID].uwUsage / LOS_CPUP_PRECISION_MULT,
                  cpuLessOneSec[taskCB->taskID].uwUsage % LOS_CPUP_PRECISION_MULT,
                  cpuTenSec[taskCB->taskID].uwUsage / LOS_CPUP_PRECISION_MULT,
                  cpuTenSec[taskCB->taskID].uwUsage % LOS_CPUP_PRECISION_MULT,
                  cpuOneSec[taskCB->taskID].uwUsage / LOS_CPUP_PRECISION_MULT,
                  cpuOneSec[taskCB->taskID].uwUsage % LOS_CPUP_PRECISION_MULT);
#endif /* LOSCFG_BASE_CORE_CPUP */
        PRINT_ERR("\n");
    }

#if (LOSCFG_EXC_HRADWARE_STACK_PROTECTION == YES)
    osStackProtRestore(flag);
#endif

#if (LOSCFG_BASE_CORE_CPUP == YES)
    (VOID)LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, cpuLessOneSec);
    (VOID)LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, cpuTenSec);
    (VOID)LOS_MemFree((VOID *)OS_SYS_MEM_ADDR, cpuOneSec);
#endif

    return LOS_OK;
}

/*****************************************************************************
 Function    : OsTaskInit
 Description : Task init function.
 Input       : None
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsTaskInit(VOID)
{
    UINT32 size;
    UINT32 index;
    LOS_DL_LIST *listObject = NULL;
    UINT32 queueResult;

    size = (g_taskMaxNum + 1) * sizeof(LosTaskCB);
    g_taskCBArray = (LosTaskCB *)LOS_MemAlloc(m_aucSysMem0, size);
    if (g_taskCBArray == NULL) {
        return LOS_ERRNO_TSK_NO_MEMORY;
    }

    // Ignore the return code when matching CSEC rule 6.6(1).
    (VOID)memset_s(g_taskCBArray, size, 0, size);
    LOS_ListInit(&g_losFreeTask);
    LOS_ListInit(&g_taskRecyleList);
    for (index = 0; index <= LOSCFG_BASE_CORE_TSK_LIMIT; index++) {
        g_taskCBArray[index].taskStatus = OS_TASK_STATUS_UNUSED;
        g_taskCBArray[index].taskID = index;
        LOS_ListTailInsert(&g_losFreeTask, &g_taskCBArray[index].pendList);
    }

    // Ignore the return code when matching CSEC rule 6.6(4).
    (VOID)memset_s((VOID *)(&g_losTask), sizeof(g_losTask), 0, sizeof(g_losTask));
    g_losTask.runTask = &g_taskCBArray[g_taskMaxNum];
    g_losTask.runTask->taskID = index;
    g_losTask.runTask->taskStatus = (OS_TASK_STATUS_UNUSED | OS_TASK_STATUS_RUNNING);
    g_losTask.runTask->priority = OS_TASK_PRIORITY_LOWEST + 1;
    queueResult = OsPriqueueInit();
    if (queueResult == LOS_NOK) {
        (VOID)LOS_MemFree(m_aucSysMem0, g_taskCBArray);
        return LOS_ERRNO_TSK_NO_MEMORY;
    }

    size = sizeof(LOS_DL_LIST) * OS_TSK_SORTLINK_LEN;
    listObject = (LOS_DL_LIST *)LOS_MemAlloc(m_aucSysMem0, size);
    if (listObject == NULL) {
        (VOID)LOS_MemFree(m_aucSysMem0, g_taskCBArray);
        return LOS_ERRNO_TSK_NO_MEMORY;
    }

    // Ignore the return code when matching CSEC rule 6.6(3).
    (VOID)memset_s((VOID *)listObject, size, 0, size);
    g_taskSortLink.sortLink = listObject;
    g_taskSortLink.cursor = 0;
    for (index = 0; index < OS_TSK_SORTLINK_LEN; index++, listObject++) {
        LOS_ListInit(listObject);
    }

#if (LOSCFG_PLATFORM_EXC == YES)
    OsExcRegister((ExcInfoType)OS_EXC_TYPE_TSK, (EXC_INFO_SAVE_CALLBACK)LOS_TaskInfoGet, &g_taskMaxNum);
#endif
    return LOS_OK;
}


/*****************************************************************************
 Function    : OsIdleTaskCreate
 Description : Create idle task.
 Input       : None
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsIdleTaskCreate(VOID)
{
    UINT32 retVal;
    TSK_INIT_PARAM_S taskInitParam;
    // Ignore the return code when matching CSEC rule 6.6(4).
    (VOID)memset_s((VOID *)(&taskInitParam), sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)OsIdleTask;
    taskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE;
    taskInitParam.pcName = "IdleCore000";
    taskInitParam.usTaskPrio = OS_TASK_PRIORITY_LOWEST;
    retVal = LOS_TaskCreate(&g_idleTaskID, &taskInitParam);

    if (retVal != LOS_OK) {
        return retVal;
    }

    return LOS_OK;
}

/*****************************************************************************
 Function    : LOS_CurTaskIDGet
 Description : get id of current running task.
 Input       : None
 Output      : None
 Return      : task id
 *****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_CurTaskIDGet(VOID)
{
    if (g_losTask.runTask == NULL) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }
    return g_losTask.runTask->taskID;
}

/*****************************************************************************
 Function    : LOS_NextTaskIDGet
 Description : get id of next running task.
 Input       : None
 Output      : None
 Return      : task id
 *****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_NextTaskIDGet(VOID)
{
    if (g_losTask.newTask == NULL) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }
    return g_losTask.newTask->taskID;
}

/*****************************************************************************
 Function    : LOS_CurTaskNameGet
 Description : get name of current running task.
 Input       : None
 Output      : None
 Return      : task name
 *****************************************************************************/
LITE_OS_SEC_TEXT CHAR *LOS_CurTaskNameGet(VOID)
{
    CHAR *taskName = NULL;

    if (g_losTask.runTask != NULL) {
        taskName = g_losTask.runTask->taskName;
    }

    return taskName;
}

/*****************************************************************************
 Function    : OsTaskSwitchCheck
 Description : Check task switch
 Input       : Node
 Output      : None
 Return      : None
 *****************************************************************************/
#if (LOSCFG_BASE_CORE_TSK_MONITOR == YES)
LITE_OS_SEC_TEXT VOID OsTaskSwitchCheck(VOID)
{
#if (LOSCFG_EXC_HRADWARE_STACK_PROTECTION == NO)
    UINT32 endOfStack = g_losTask.newTask->topOfStack + g_losTask.newTask->stackSize;

    if ((*(UINT32 *)(UINTPTR)(g_losTask.runTask->topOfStack)) != OS_TASK_MAGIC_WORD) {
        PRINT_ERR("CURRENT task ID: %s:%d stack overflow!\n",
                  g_losTask.runTask->taskName, g_losTask.runTask->taskID);
    }
    if (((UINT32)(UINTPTR)(g_losTask.newTask->stackPointer) <= (g_losTask.newTask->topOfStack)) ||
        ((UINT32)(UINTPTR)(g_losTask.newTask->stackPointer) > endOfStack)) {
        PRINT_ERR("HIGHEST task ID: %s:%d SP error!\n",
                  g_losTask.newTask->taskName, g_losTask.newTask->taskID);
        PRINT_ERR("HIGHEST task StackPointer: 0x%x TopOfStack: 0x%x\n",
                  (UINT32)(UINTPTR)(g_losTask.newTask->stackPointer), g_losTask.newTask->topOfStack);
    }
#endif

#if (LOSCFG_BASE_CORE_EXC_TSK_SWITCH == YES)
    /* record task switch info */
    g_taskSwitchInfo.pid[g_taskSwitchInfo.idx] = (UINT16)(g_losTask.newTask->taskID);

    errno_t ret = memcpy_s(g_taskSwitchInfo.name[g_taskSwitchInfo.idx], LOS_TASK_NAMELEN,
                           g_losTask.newTask->taskName, LOS_TASK_NAMELEN);
    if (ret != EOK) {
        PRINT_ERR("exc task switch copy file name failed!\n");
    }
    g_taskSwitchInfo.name[g_taskSwitchInfo.idx][LOS_TASK_NAMELEN - 1] = '\0';

    if (++g_taskSwitchInfo.idx == OS_TASK_SWITCH_INFO_COUNT) {
        g_taskSwitchInfo.idx = 0;
        g_taskSwitchInfo.cntInfo.isFull = TRUE;
    }
#endif

    if (g_pfnUsrTskSwitchHook != NULL) {
        g_pfnUsrTskSwitchHook();
    }

#if (LOSCFG_KERNEL_TRACE == YES)
    LOS_Trace(LOS_TRACE_SWITCH, 0);
#endif

#if (LOSCFG_BASE_CORE_CPUP == YES)
    OsTskCycleEndStart();
#endif /* LOSCFG_BASE_CORE_CPUP */
}

LITE_OS_SEC_TEXT_MINOR VOID OsTaskMonInit(VOID)
{
#if (LOSCFG_BASE_CORE_EXC_TSK_SWITCH == YES)
    // Ignore the return code when matching CSEC rule 6.6(4).
    (VOID)memset_s(&g_taskSwitchInfo, sizeof(TaskSwitchInfo), 0, sizeof(TaskSwitchInfo));
    g_taskSwitchInfo.cntInfo.maxCnt = OS_TASK_SWITCH_INFO_COUNT;
#if (LOSCFG_PLATFORM_EXC == YES)
    OsExcRegister((ExcInfoType)OS_EXC_TYPE_TSK_SWITCH,
                  (EXC_INFO_SAVE_CALLBACK)LOS_TaskSwitchInfoGet,
                  &g_taskSwitchInfo);
#endif
#endif
    g_taskSwitchHook = OsTaskSwitchCheck;
    g_pfnUsrTskSwitchHook = NULL;
    return;
}
#endif

/*****************************************************************************
 Function    : OsTaskEntry
 Description : All task entry
 Input       : taskID     --- The ID of the task to be run
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT VOID OsTaskEntry(UINT32 taskID)
{
    UINT32 retVal;
    LosTaskCB *taskCB = NULL;

    OS_TASK_ID_CHECK(taskID);

    taskCB = OS_TCB_FROM_TID(taskID);

    (VOID)taskCB->taskEntry(taskCB->arg);

    retVal = LOS_TaskDelete(taskCB->taskID);
    if (retVal != LOS_OK) {
        PRINT_ERR("Delete Task[TID: %d] Failed!\n", taskCB->taskID);
    }
}

LITE_OS_SEC_TEXT_INIT STATIC_INLINE UINT32 OsTaskInitParamCheck(TSK_INIT_PARAM_S *taskInitParam)
{
    if (taskInitParam == NULL) {
        return LOS_ERRNO_TSK_PTR_NULL;
    }

    if (taskInitParam->pcName == NULL) {
        return LOS_ERRNO_TSK_NAME_EMPTY;
    }

    if (taskInitParam->pfnTaskEntry == NULL) {
        return LOS_ERRNO_TSK_ENTRY_NULL;
    }

    if ((taskInitParam->usTaskPrio) > OS_TASK_PRIORITY_LOWEST) {
        return LOS_ERRNO_TSK_PRIOR_ERROR;
    }

    if (((taskInitParam->usTaskPrio) == OS_TASK_PRIORITY_LOWEST)
        && (taskInitParam->pfnTaskEntry != OS_IDLE_TASK_ENTRY)) {
        return LOS_ERRNO_TSK_PRIOR_ERROR;
    }

    if (taskInitParam->uwStackSize > OS_SYS_MEM_SIZE) {
        return LOS_ERRNO_TSK_STKSZ_TOO_LARGE;
    }

    if (taskInitParam->uwStackSize == 0) {
        taskInitParam->uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    }
    taskInitParam->uwStackSize = ALIGN(taskInitParam->uwStackSize, OS_TASK_STACK_ADDR_ALIGN);

    if (taskInitParam->uwStackSize < LOSCFG_BASE_CORE_TSK_MIN_STACK_SIZE) {
        return LOS_ERRNO_TSK_STKSZ_TOO_SMALL;
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT UINT32 OsNewTaskInit(LosTaskCB *taskCB, TSK_INIT_PARAM_S *taskInitParam, VOID *topOfStack)
{
    VOID *stackPtr = NULL;

    stackPtr = OsTskStackInit(taskCB->taskID, taskInitParam->uwStackSize, topOfStack);
    taskCB->stackPointer    = stackPtr;
    taskCB->arg             = taskInitParam->uwArg;
    taskCB->topOfStack      = (UINT32)(UINTPTR)topOfStack;
    taskCB->stackSize       = taskInitParam->uwStackSize;
    taskCB->taskSem         = NULL;
    taskCB->taskMux         = NULL;
    taskCB->taskStatus      = OS_TASK_STATUS_SUSPEND;
    taskCB->priority        = taskInitParam->usTaskPrio;
    taskCB->taskEntry       = taskInitParam->pfnTaskEntry;
    taskCB->event.uwEventID = OS_NULL_INT;
    taskCB->eventMask       = 0;
    taskCB->taskName        = taskInitParam->pcName;
    taskCB->msg             = NULL;

    return LOS_OK;
}

/*****************************************************************************
 Function    : LOS_TaskCreateOnly
 Description : Create a task and suspend
 Input       : taskInitParam --- Task init parameters
 Output      : taskID        --- Save task ID
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskCreateOnly(UINT32 *taskID, TSK_INIT_PARAM_S *taskInitParam)
{
    UINTPTR intSave;
    VOID  *topOfStack = NULL;
    LosTaskCB *taskCB = NULL;
    UINT32 retVal;

    if (taskID == NULL) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    retVal = OsTaskInitParamCheck(taskInitParam);
    if (retVal != LOS_OK) {
        return retVal;
    }

    intSave = LOS_IntLock();
    while (!LOS_ListEmpty(&g_taskRecyleList)) {
        taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&g_taskRecyleList));
        LOS_ListDelete(LOS_DL_LIST_FIRST(&g_taskRecyleList));
        LOS_ListAdd(&g_losFreeTask, &taskCB->pendList);
        (VOID)LOS_MemFree(OS_TASK_STACK_ADDR, (VOID *)(UINTPTR)taskCB->topOfStack);
        taskCB->topOfStack = (UINT32)NULL;
    }

    if (LOS_ListEmpty(&g_losFreeTask)) {
        retVal = LOS_ERRNO_TSK_TCB_UNAVAILABLE;
        OS_GOTO_ERREND();
    }

    taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&g_losFreeTask));
    LOS_ListDelete(LOS_DL_LIST_FIRST(&g_losFreeTask));

    LOS_IntRestore(intSave);

    topOfStack = (VOID *)LOS_MemAllocAlign(OS_TASK_STACK_ADDR, taskInitParam->uwStackSize,
        LOSCFG_STACK_POINT_ALIGN_SIZE);
    if (topOfStack == NULL) {
        intSave = LOS_IntLock();
        LOS_ListAdd(&g_losFreeTask, &taskCB->pendList);
        LOS_IntRestore(intSave);
        return LOS_ERRNO_TSK_NO_MEMORY;
    }

    retVal = OsNewTaskInit(taskCB, taskInitParam, topOfStack);
    if (retVal != LOS_OK) {
        return retVal;
    }

    *taskID = taskCB->taskID;
    return retVal;
}


/*****************************************************************************
 Function    : LOS_TaskCreate
 Description : Create a task
 Input       : taskInitParam --- Task init parameters
 Output      : taskID        --- Save task ID
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskCreate(UINT32 *taskID, TSK_INIT_PARAM_S *taskInitParam)
{
    UINT32 retVal;
    UINTPTR intSave;
    LosTaskCB *taskCB = NULL;

    retVal = LOS_TaskCreateOnly(taskID, taskInitParam);
    if (retVal != LOS_OK) {
        return retVal;
    }
    taskCB = OS_TCB_FROM_TID(*taskID);

    intSave = LOS_IntLock();
    taskCB->taskStatus &= (~OS_TASK_STATUS_SUSPEND);
    taskCB->taskStatus |= OS_TASK_STATUS_READY;

#if (LOSCFG_BASE_CORE_CPUP == YES)
    g_cpup[taskCB->taskID].cpupID = taskCB->taskID;
    g_cpup[taskCB->taskID].status = taskCB->taskStatus;
#endif

    OsPriqueueEnqueue(&taskCB->pendList, taskCB->priority);
    g_losTask.newTask = LOS_DL_LIST_ENTRY(OsPriqueueTop(), LosTaskCB, pendList);

    if ((g_taskScheduled) && (g_losTaskLock == 0)) {
        if (g_losTask.runTask != g_losTask.newTask) {
            if (LOS_CHECK_SCHEDULE) {
                LOS_IntRestore(intSave);
                OsSchedule();
                return LOS_OK;
            }
        }
    }

    LOS_IntRestore(intSave);
    return LOS_OK;
}

/*****************************************************************************
 Function    : LOS_TaskResume
 Description : Resume suspend task
 Input       : taskID --- Task ID
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskResume(UINT32 taskID)
{
    UINTPTR intSave;
    LosTaskCB *taskCB = NULL;
    UINT16 tempStatus;
    UINT32 retErr = OS_ERROR;

    if (taskID > LOSCFG_BASE_CORE_TSK_LIMIT) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    intSave = LOS_IntLock();
    tempStatus = taskCB->taskStatus;

    if (tempStatus & OS_TASK_STATUS_UNUSED) {
        retErr = LOS_ERRNO_TSK_NOT_CREATED;
        OS_GOTO_ERREND();
    } else if (!(tempStatus & OS_TASK_STATUS_SUSPEND)) {
        retErr = LOS_ERRNO_TSK_NOT_SUSPENDED;
        OS_GOTO_ERREND();
    }

    taskCB->taskStatus &= (~OS_TASK_STATUS_SUSPEND);
    if (!(taskCB->taskStatus & OS_CHECK_TASK_BLOCK)) {
        taskCB->taskStatus |= OS_TASK_STATUS_READY;
        OsPriqueueEnqueue(&taskCB->pendList, taskCB->priority);
        if (g_taskScheduled) {
            LOS_IntRestore(intSave);
            LOS_Schedule();
            return LOS_OK;
        }
        g_losTask.newTask = LOS_DL_LIST_ENTRY(OsPriqueueTop(), LosTaskCB, pendList);
    }

    LOS_IntRestore(intSave);
    return LOS_OK;

LOS_ERREND:
    LOS_IntRestore(intSave);
    return retErr;
}

/*****************************************************************************
 Function    : LOS_TaskSuspend
 Description : Suspend task
 Input       : taskID --- Task ID
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskSuspend(UINT32 taskID)
{
    UINTPTR intSave;
    LosTaskCB *taskCB = NULL;
    UINT16 tempStatus;
    UINT32 retErr;

    retErr = OsCheckTaskIDValid(taskID);
    if (retErr != LOS_OK) {
        return retErr;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    intSave = LOS_IntLock();
    tempStatus = taskCB->taskStatus;
    if (tempStatus & OS_TASK_STATUS_UNUSED) {
        retErr = LOS_ERRNO_TSK_NOT_CREATED;
        OS_GOTO_ERREND();
    }

    if (tempStatus & OS_TASK_STATUS_SUSPEND) {
        retErr = LOS_ERRNO_TSK_ALREADY_SUSPENDED;
        OS_GOTO_ERREND();
    }

    if ((tempStatus & OS_TASK_STATUS_RUNNING) && (g_losTaskLock != 0)) {
        retErr = LOS_ERRNO_TSK_SUSPEND_LOCKED;
        OS_GOTO_ERREND();
    }

    if (tempStatus & OS_TASK_STATUS_READY) {
        OsPriqueueDequeue(&taskCB->pendList);
        taskCB->taskStatus &= (~OS_TASK_STATUS_READY);
    }

    taskCB->taskStatus |= OS_TASK_STATUS_SUSPEND;
    if (taskID == g_losTask.runTask->taskID) {
        LOS_IntRestore(intSave);
        LOS_Schedule();
        return LOS_OK;
    }

    LOS_IntRestore(intSave);
    return LOS_OK;

LOS_ERREND:
    LOS_IntRestore(intSave);
    return retErr;
}

LITE_OS_SEC_TEXT_INIT STATIC_INLINE VOID OsRunningTaskDelete(UINT32 taskID, LosTaskCB *taskCB)
{
    LOS_ListTailInsert(&g_taskRecyleList, &taskCB->pendList);
    g_losTask.runTask = &g_taskCBArray[g_taskMaxNum];
    g_losTask.runTask->taskID = taskID;
    g_losTask.runTask->taskStatus = taskCB->taskStatus;
    g_losTask.runTask->topOfStack = taskCB->topOfStack;
    g_losTask.runTask->taskName = taskCB->taskName;
}
/*****************************************************************************
 Function    : LOS_TaskDelete
 Description : Delete a task
 Input       : taskID --- Task ID
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskDelete(UINT32 taskID)
{
    UINTPTR intSave;
    LosTaskCB *taskCB = OS_TCB_FROM_TID(taskID);

    UINT32 ret = OsCheckTaskIDValid(taskID);
    if (ret != LOS_OK) {
        return ret;
    }

    intSave = LOS_IntLock();

    if ((taskCB->taskStatus) & OS_TASK_STATUS_UNUSED) {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_TSK_NOT_CREATED;
    }

    /* If the task is running and scheduler is locked then you can not delete it */
    if (((taskCB->taskStatus) & OS_TASK_STATUS_RUNNING) && (g_losTaskLock != 0)) {
        PRINT_INFO("In case of task lock, task deletion is not recommended\n");
        g_losTaskLock = 0;
    }

    if ((taskCB->taskStatus) & OS_TASK_STATUS_READY) {
        OsPriqueueDequeue(&taskCB->pendList);
        taskCB->taskStatus &= (~OS_TASK_STATUS_READY);
    } else if (((taskCB->taskStatus) & (OS_TASK_STATUS_PEND | OS_TASK_STATUS_PEND_QUEUE))) {
        LOS_ListDelete(&taskCB->pendList);
    }

    if ((taskCB->taskStatus) & (OS_TASK_STATUS_DELAY | OS_TASK_STATUS_TIMEOUT)) {
        OsTimerListDelete(taskCB);
    }

    taskCB->taskStatus &= (~(OS_TASK_STATUS_SUSPEND));
    taskCB->taskStatus |= OS_TASK_STATUS_UNUSED;
    taskCB->event.uwEventID = OS_NULL_INT;
    taskCB->eventMask = 0;
#if (LOSCFG_BASE_CORE_CPUP == YES)
    // Ignore the return code when matching CSEC rule 6.6(4).
    (VOID)memset_s((VOID *)&g_cpup[taskCB->taskID], sizeof(OsCpupCB), 0, sizeof(OsCpupCB));
#endif
    g_losTask.newTask = LOS_DL_LIST_ENTRY(OsPriqueueTop(), LosTaskCB, pendList);
    if (taskCB->taskStatus & OS_TASK_STATUS_RUNNING) {
        OsRunningTaskDelete(taskID, taskCB);
        taskCB->taskStatus = OS_TASK_STATUS_UNUSED;
        LOS_IntRestore(intSave);
        OsSchedule();
        return LOS_OK;
    } else {
        taskCB->taskStatus = OS_TASK_STATUS_UNUSED;
        LOS_ListAdd(&g_losFreeTask, &taskCB->pendList);
        (VOID)LOS_MemFree(OS_TASK_STACK_ADDR, (VOID *)(UINTPTR)taskCB->topOfStack);
        taskCB->topOfStack = (UINT32)NULL;
    }

    LOS_IntRestore(intSave);
    return LOS_OK;
}

/*****************************************************************************
 Function    : LOS_TaskDelay
 Description : delay the current task
 Input       : tick    --- time
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_TaskDelay(UINT32 tick)
{
    UINTPTR intSave;

    if (OS_INT_ACTIVE) {
        return LOS_ERRNO_TSK_DELAY_IN_INT;
    }

    if (g_losTaskLock != 0) {
        return LOS_ERRNO_TSK_DELAY_IN_LOCK;
    }

    if (tick == 0) {
        return LOS_TaskYield();
    } else {
        intSave = LOS_IntLock();
        OsPriqueueDequeue(&(g_losTask.runTask->pendList));
        g_losTask.runTask->taskStatus &= (~OS_TASK_STATUS_READY);
        OsTaskAdd2TimerList((LosTaskCB *)g_losTask.runTask, tick);
        g_losTask.runTask->taskStatus |= OS_TASK_STATUS_DELAY;
        LOS_IntRestore(intSave);
        LOS_Schedule();
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT16 LOS_TaskPriGet(UINT32 taskID)
{
    UINTPTR intSave;
    LosTaskCB *taskCB = NULL;
    UINT16 priority;

    if (OS_CHECK_TSK_PID_NOIDLE(taskID)) {
        return (UINT16)OS_INVALID;
    }

    taskCB = OS_TCB_FROM_TID(taskID);

    intSave = LOS_IntLock();

    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        LOS_IntRestore(intSave);
        return (UINT16)OS_INVALID;
    }

    priority = taskCB->priority;
    LOS_IntRestore(intSave);
    return priority;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskPriSet(UINT32 taskID, UINT16 taskPrio)
{
    BOOL isReady = FALSE;
    UINTPTR intSave;
    LosTaskCB *taskCB = NULL;
    UINT16 tempStatus;

    if (taskPrio > OS_TASK_PRIORITY_LOWEST) {
        return LOS_ERRNO_TSK_PRIOR_ERROR;
    }

    if (taskID == g_idleTaskID) {
        return LOS_ERRNO_TSK_OPERATE_IDLE;
    }

    if (taskID == g_swtmrTaskID) {
        return LOS_ERRNO_TSK_OPERATE_SWTMR;
    }

    if (OS_CHECK_TSK_PID_NOIDLE(taskID)) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    intSave = LOS_IntLock();
    tempStatus = taskCB->taskStatus;
    if (tempStatus & OS_TASK_STATUS_UNUSED) {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_TSK_NOT_CREATED;
    }
    /* delete the task and insert with right priority into ready queue */
    isReady = (tempStatus & OS_TASK_STATUS_READY);
    if (isReady) {
        OsPriqueueDequeue(&taskCB->pendList);
        taskCB->taskStatus &= (~OS_TASK_STATUS_READY);
        taskCB->priority = taskPrio;
        taskCB->taskStatus |= OS_TASK_STATUS_READY;
        OsPriqueueEnqueue(&taskCB->pendList, taskCB->priority);
    } else {
        taskCB->priority = taskPrio;
    }

    LOS_IntRestore(intSave);
    /* delete the task and insert with right priority into ready queue */
    if (isReady) {
        LOS_Schedule();
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_CurTaskPriSet(UINT16 taskPrio)
{
    UINT32 retVal;
    retVal = LOS_TaskPriSet(g_losTask.runTask->taskID, taskPrio);
    return retVal;
}

/**************************************************************************
 Function    : OsTaskWait
 Description : pend the running task in a list
 Input       : pendingList   -- The pending list
               taskStatus    -- The status need to be converted to
               timeout       -- Expiry time
 Output      : None
 Return      : None
**************************************************************************/
VOID OsTaskWait(LOS_DL_LIST *pendingList, UINT32 taskStatus, UINT32 timeout)
{
    LosTaskCB *runTask = NULL;
    LOS_DL_LIST *pendObj = NULL;

    runTask = g_losTask.runTask;
    OsPriqueueDequeue(&runTask->pendList);
    runTask->taskStatus &= (~OS_TASK_STATUS_READY);
    pendObj = &runTask->pendList;
    runTask->taskStatus |= taskStatus;
    LOS_ListTailInsert(pendingList, pendObj);
    if (timeout != LOS_WAIT_FOREVER) {
        runTask->taskStatus |= OS_TASK_STATUS_TIMEOUT;
        OsTaskAdd2TimerList((LosTaskCB *)runTask, timeout);
    }
}

/**************************************************************************
 Function    : OsTaskWake
 Description : delete the task from pendlist and also add to the priqueue
 Input       : resumedTask    --  resumed task
             : taskStatus     --  the status to be unset
 Output      : resumedTask    --  resumed task
 Return      : None
**************************************************************************/
VOID OsTaskWake(LosTaskCB *resumedTask, UINT32 taskStatus)
{
    LOS_ListDelete(&resumedTask->pendList);
    resumedTask->taskStatus &= (~taskStatus);
    if (resumedTask->taskStatus & OS_TASK_STATUS_TIMEOUT) {
        OsTimerListDelete(resumedTask);
        resumedTask->taskStatus &= (~OS_TASK_STATUS_TIMEOUT);
    }
    if (!(resumedTask->taskStatus & OS_TASK_STATUS_SUSPEND)) {
        resumedTask->taskStatus |= OS_TASK_STATUS_READY;
        OsPriqueueEnqueue(&resumedTask->pendList, resumedTask->priority);
    }
}

/*****************************************************************************
 Function    : LOS_TaskYield
 Description : Adjust the procedure order of specified task
 Input       : None
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskYield(VOID)
{
    UINT32 taskCount;
    UINTPTR intSave;

    if (g_losTask.runTask->taskID >= g_taskMaxNum) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    if (!(g_losTask.runTask->taskStatus & OS_TASK_STATUS_READY)) {
        return LOS_OK;
    }

    intSave = LOS_IntLock();
    taskCount = OsPriqueueSize(g_losTask.runTask->priority);
    if (taskCount > 1) {
        LOS_ListDelete(&(g_losTask.runTask->pendList));
        g_losTask.runTask->taskStatus |= OS_TASK_STATUS_READY;
        OsPriqueueEnqueue(&(g_losTask.runTask->pendList), g_losTask.runTask->priority);
    } else {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_TSK_YIELD_NOT_ENOUGH_TASK;
    }

    LOS_IntRestore(intSave);
    LOS_Schedule();
    return LOS_OK;
}

/*****************************************************************************
 Function    : LOS_TaskLock
 Description : Task lock
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_MINOR VOID LOS_TaskLock(VOID)
{
    UINTPTR intSave;

    intSave = LOS_IntLock();
    g_losTaskLock++;
    LOS_IntRestore(intSave);
}

/*****************************************************************************
 Function    : LOS_TaskUnlock
 Description : Task unlock
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_MINOR VOID LOS_TaskUnlock(VOID)
{
    UINTPTR intSave;

    intSave = LOS_IntLock();
    if (g_losTaskLock > 0) {
        g_losTaskLock--;
        if (g_losTaskLock == 0) {
            LOS_IntRestore(intSave);
            LOS_Schedule();
            return;
        }
    }

    LOS_IntRestore(intSave);
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskInfoGet(UINT32 taskID, TSK_INFO_S *taskInfo)
{
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;
#if (LOSCFG_EXC_HRADWARE_STACK_PROTECTION == YES)
    UINT32 flag;
#endif

    if (taskInfo == NULL) {
        return LOS_ERRNO_TSK_PTR_NULL;
    }

    if (OS_CHECK_TSK_PID_NOIDLE(taskID)) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    intSave = LOS_IntLock();

    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_TSK_NOT_CREATED;
    }

    taskInfo->uwSP = (UINT32)(UINTPTR)taskCB->stackPointer;
    taskInfo->usTaskStatus = taskCB->taskStatus;
    taskInfo->usTaskPrio = taskCB->priority;
    taskInfo->uwStackSize = taskCB->stackSize;
    taskInfo->uwTopOfStack = taskCB->topOfStack;
    taskInfo->uwEvent = taskCB->event;
    taskInfo->uwEventMask = taskCB->eventMask;
    taskInfo->uwSemID = (taskCB->taskSem != NULL) ? ((LosSemCB *)(taskCB->taskSem))->semID :
                        LOSCFG_BASE_IPC_SEM_LIMIT;
    taskInfo->uwMuxID = (taskCB->taskMux != NULL) ? ((LosMuxCB *)(taskCB->taskMux))->muxID :
                        LOSCFG_BASE_IPC_MUX_LIMIT;
    taskInfo->pTaskSem = taskCB->taskSem;
    taskInfo->pTaskMux = taskCB->taskMux;
    taskInfo->uwTaskID = taskID;
    // Ignore the return code when matching CSEC rule 6.6(4).
    (VOID)strncpy_s(taskInfo->acName, LOS_TASK_NAMELEN, taskCB->taskName, LOS_TASK_NAMELEN - 1);
    taskInfo->acName[LOS_TASK_NAMELEN - 1] = '\0';

    taskInfo->uwBottomOfStack = TRUNCATE(((UINT32)(taskCB->topOfStack) + (taskCB->stackSize)),
                                         OS_TASK_STACK_ADDR_ALIGN);
    taskInfo->uwCurrUsed = taskInfo->uwBottomOfStack - taskInfo->uwSP;

#if (LOSCFG_EXC_HRADWARE_STACK_PROTECTION == YES)
    flag = osStackProtDisable();
#endif

    taskInfo->uwPeakUsed = OsGetTaskWaterLine(taskID);
    taskInfo->bOvf = (taskInfo->uwPeakUsed == OS_NULL_INT) ? TRUE : FALSE;

#if (LOSCFG_EXC_HRADWARE_STACK_PROTECTION == YES)
    osStackProtRestore(flag);
#endif

    LOS_IntRestore(intSave);

    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskStatusGet(UINT32 taskID, UINT32 *taskStatus)
{
    UINT32    intSave;
    LosTaskCB *taskCB = NULL;

    if (taskStatus == NULL) {
        return LOS_ERRNO_TSK_PTR_NULL;
    }

    if (OS_CHECK_TSK_PID_NOIDLE(taskID)) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    intSave = LOS_IntLock();

    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_TSK_NOT_CREATED;
    }

    *taskStatus = taskCB->taskStatus;

    LOS_IntRestore(intSave);

    return LOS_OK;
}

#if (LOSCFG_BASE_CORE_EXC_TSK_SWITCH == YES)
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskSwitchInfoGet(UINT32 index, UINT32 *taskSwitchInfo)
{
    UINTPTR intSave;
    UINT32 curIndex;

    curIndex = index;
    if (curIndex >= OS_TASK_SWITCH_INFO_COUNT) {
        curIndex %= OS_TASK_SWITCH_INFO_COUNT;
    }

    if (taskSwitchInfo == NULL) {
        return LOS_ERRNO_TSK_PTR_NULL;
    }

    intSave = LOS_IntLock();

    (*taskSwitchInfo) = g_taskSwitchInfo.pid[curIndex];

    if (memcpy_s((VOID *)(taskSwitchInfo + 1), LOS_TASK_NAMELEN,
                 g_taskSwitchInfo.name[curIndex], LOS_TASK_NAMELEN) != EOK) {
        PRINT_ERR("LOS_TaskSwitchInfoGet copy task name failed\n");
    }

    LOS_IntRestore(intSave);
    return LOS_OK;
}
#endif

/*****************************************************************************
Function    : LOS_TaskInfoMonitor
Description : Get all task info
Input       : None
Return      : LOS_OK on success ,or OS_ERROR on failure
*****************************************************************************/
LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskInfoMonitor(VOID)
{
    UINT32 retVal;

    retVal = OsGetAllTskInfo();

    return retVal;
}

/*****************************************************************************
 Function    : LOS_TaskIsRunning
 Description : Check if LiteOS has been started.
 Input       : VOID
 Output      : VOID
 Return      : TRUE means LiteOS was started, FALSE means not.
 *****************************************************************************/
LITE_OS_SEC_TEXT_MINOR BOOL LOS_TaskIsRunning(VOID)
{
    return g_taskScheduled;
}

/*****************************************************************************
 Function    : LOS_NewTaskIDGet
 Description : get id of current new task.
 Input       : None
 Output      : None
 Return      : task id
 *****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_NewTaskIDGet(VOID)
{
    if (g_losTask.newTask == NULL) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }
    return g_losTask.newTask->taskID;
}

/*****************************************************************************
 Function    : LOS_TaskNameGet
 Description : get Name of current new task.
 Input       : taskID -----task id
 Output      : None
 Return      : task name
 *****************************************************************************/
LITE_OS_SEC_TEXT CHAR* LOS_TaskNameGet(UINT32 taskID)
{
    UINT32    intSave;
    LosTaskCB *taskCB = NULL;

    if (OS_CHECK_TSK_PID_NOIDLE(taskID)) {
        return NULL;
    }

    taskCB = OS_TCB_FROM_TID(taskID);

    intSave = LOS_IntLock();
    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        LOS_IntRestore(intSave);
        return NULL;
    }
    LOS_IntRestore(intSave);

    return taskCB->taskName;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
