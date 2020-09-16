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

#include "los_priqueue_pri.h"
#include "los_task_pri.h"
#include "los_memory.h"
#include "los_toolchain.h"
#include "los_spinlock.h"
#include "los_process_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define PRIQUEUE_PRIOR0_BIT   0x80000000U

LITE_OS_SEC_BSS LOS_DL_LIST *g_priQueueList = NULL;
LITE_OS_SEC_BSS UINT32 g_priQueueBitmap;

UINT32 OsPriQueueInit(VOID)
{
    UINT32 priority;

    /* system resident resource */
    g_priQueueList = (LOS_DL_LIST *)LOS_MemAlloc(m_aucSysMem0, (OS_PRIORITY_QUEUE_NUM * sizeof(LOS_DL_LIST)));
    if (g_priQueueList == NULL) {
        return LOS_NOK;
    }

    for (priority = 0; priority < OS_PRIORITY_QUEUE_NUM; ++priority) {
        LOS_ListInit(&g_priQueueList[priority]);
    }
    return LOS_OK;
}

LOS_DL_LIST *OsPriQueueTop(LOS_DL_LIST *priQueueList, UINT32 *bitMap)
{
    UINT32 priority;

    if (*bitMap != 0) {
        priority = CLZ(*bitMap);
        return LOS_DL_LIST_FIRST(&priQueueList[priority]);
    }

    return NULL;
}

VOID OsPriQueueEnqueueHead(LOS_DL_LIST *priQueueList, UINT32 *bitMap, LOS_DL_LIST *priqueueItem, UINT32 priority)
{
    /*
     * Task control blocks are inited as zero. And when task is deleted,
     * and at the same time would be deleted from priority queue or
     * other lists, task pend node will restored as zero.
     */
    LOS_ASSERT(priqueueItem->pstNext == NULL);

    if (LOS_ListEmpty(&priQueueList[priority])) {
        *bitMap |= PRIQUEUE_PRIOR0_BIT >> priority;
    }

    LOS_ListHeadInsert(&priQueueList[priority], priqueueItem);
}

VOID OsPriQueueEnqueue(LOS_DL_LIST *priQueueList, UINT32 *bitMap, LOS_DL_LIST *priqueueItem, UINT32 priority)
{
    /*
     * Task control blocks are inited as zero. And when task is deleted,
     * and at the same time would be deleted from priority queue or
     * other lists, task pend node will restored as zero.
     */
    LOS_ASSERT(priqueueItem->pstNext == NULL);

    if (LOS_ListEmpty(&priQueueList[priority])) {
        *bitMap |= PRIQUEUE_PRIOR0_BIT >> priority;
    }

    LOS_ListTailInsert(&priQueueList[priority], priqueueItem);
}

VOID OsPriQueueDequeue(LOS_DL_LIST *priQueueList, UINT32 *bitMap, LOS_DL_LIST *priqueueItem)
{
    LosTaskCB *task = NULL;
    LOS_ListDelete(priqueueItem);

    task = LOS_DL_LIST_ENTRY(priqueueItem, LosTaskCB, pendList);
    if (LOS_ListEmpty(&priQueueList[task->priority])) {
        *bitMap &= ~(PRIQUEUE_PRIOR0_BIT >> task->priority);
    }
}

VOID OsPriQueueProcessDequeue(LOS_DL_LIST *priqueueItem)
{
    LosProcessCB *runProcess = NULL;
    LOS_ListDelete(priqueueItem);

    runProcess = LOS_DL_LIST_ENTRY(priqueueItem, LosProcessCB, pendList);
    if (LOS_ListEmpty(&g_priQueueList[runProcess->priority])) {
        g_priQueueBitmap &= ~(PRIQUEUE_PRIOR0_BIT >> runProcess->priority);
    }
}

UINT32 OsPriQueueProcessSize(LOS_DL_LIST *priQueueList, UINT32 priority)
{
    UINT32 itemCnt = 0;
    LOS_DL_LIST *curNode = NULL;

    LOS_ASSERT(OsIntLocked());
    LOS_ASSERT(LOS_SpinHeld(&g_taskSpin));

    LOS_DL_LIST_FOR_EACH(curNode, &priQueueList[priority]) {
        ++itemCnt;
    }

    return itemCnt;
}

UINT32 OsPriQueueSize(LOS_DL_LIST *priQueueList, UINT32 priority)
{
    UINT32 itemCnt = 0;
    LOS_DL_LIST *curNode = NULL;
#if (LOSCFG_KERNEL_SMP == YES)
    LosTaskCB *task = NULL;
    UINT32 cpuID = ArchCurrCpuid();
#endif

    LOS_ASSERT(OsIntLocked());
    LOS_ASSERT(LOS_SpinHeld(&g_taskSpin));

    LOS_DL_LIST_FOR_EACH(curNode, &priQueueList[priority]) {
#if (LOSCFG_KERNEL_SMP == YES)
        task = OS_TCB_FROM_PENDLIST(curNode);
        if (!(task->cpuAffiMask & (1U << cpuID))) {
            continue;
        }
#endif
        ++itemCnt;
    }

    return itemCnt;
}


LOS_DL_LIST *OsTaskPriQueueTop(VOID)
{
    LosProcessCB *processCB = LOS_DL_LIST_ENTRY(OsPriQueueTop(g_priQueueList, &g_priQueueBitmap),
                                                LosProcessCB,
                                                pendList);
    return OsPriQueueTop(processCB->threadPriQueueList, &processCB->threadScheduleMap);
}

STATIC INLINE VOID OsDequeEmptySchedMap(LosProcessCB *processCB)
{
    if (processCB->threadScheduleMap == 0) {
        processCB->processStatus &= ~OS_PROCESS_STATUS_READY;
        OsPriQueueProcessDequeue(&processCB->pendList);
    }
}

LITE_OS_SEC_TEXT_MINOR LosTaskCB *OsGetTopTask(VOID)
{
    UINT32 priority, processPriority;
    UINT32 bitmap;
    UINT32 processBitmap;
    LosTaskCB *newTask = NULL;
#if (LOSCFG_KERNEL_SMP == YES)
    UINT32 cpuid = ArchCurrCpuid();
#endif
    LosProcessCB *processCB = NULL;
    processBitmap = g_priQueueBitmap;
    while (processBitmap) {
        processPriority = CLZ(processBitmap);
        LOS_DL_LIST_FOR_EACH_ENTRY(processCB, &g_priQueueList[processPriority], LosProcessCB, pendList) {
            bitmap = processCB->threadScheduleMap;
            while (bitmap) {
                priority = CLZ(bitmap);
                LOS_DL_LIST_FOR_EACH_ENTRY(newTask, &processCB->threadPriQueueList[priority], LosTaskCB, pendList) {
#if (LOSCFG_KERNEL_SMP == YES)
                    if (newTask->cpuAffiMask & (1U << cpuid)) {
#endif
                        newTask->taskStatus &= ~OS_TASK_STATUS_READY;
                        OsPriQueueDequeue(processCB->threadPriQueueList,
                                          &processCB->threadScheduleMap,
                                          &newTask->pendList);
                        OsDequeEmptySchedMap(processCB);
                        goto OUT;
#if (LOSCFG_KERNEL_SMP == YES)
                    }
#endif
                }
                bitmap &= ~(1U << (OS_PRIORITY_QUEUE_NUM - priority - 1));
            }
        }
        processBitmap &= ~(1U << (OS_PRIORITY_QUEUE_NUM - processPriority - 1));
    }

OUT:
    return newTask;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

