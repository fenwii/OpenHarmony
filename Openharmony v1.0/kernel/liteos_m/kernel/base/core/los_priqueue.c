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
#include "los_base_pri.h"
#include "los_task_pri.h"
#include "los_memory.h"
#include "los_compiler.h"

LITE_OS_SEC_BSS LOS_DL_LIST *g_losPriorityQueueList = NULL;
static LITE_OS_SEC_BSS UINT32 g_priqueueBitmap = 0;

#define PRIQUEUE_PRIOR0_BIT (UINT32)0x80000000

UINT32 OsPriqueueInit(VOID)
{
    UINT32 priority;
    UINT32 size = OS_PRIORITY_QUEUE_PRIORITYNUM * sizeof(LOS_DL_LIST);

    g_losPriorityQueueList = (LOS_DL_LIST *)LOS_MemAlloc(m_aucSysMem0, size);
    if (g_losPriorityQueueList == NULL) {
        return LOS_NOK;
    }

    for (priority = 0; priority < OS_PRIORITY_QUEUE_PRIORITYNUM; ++priority) {
        LOS_ListInit(&g_losPriorityQueueList[priority]);
    }
    return LOS_OK;
}

VOID OsPriqueueEnqueue(LOS_DL_LIST *priqueueItem, UINT32 priority)
{
    if (LOS_ListEmpty(&g_losPriorityQueueList[priority])) {
        g_priqueueBitmap |= (PRIQUEUE_PRIOR0_BIT >> priority);
    }

    LOS_ListTailInsert(&g_losPriorityQueueList[priority], priqueueItem);
}

VOID OsPriqueueDequeue(LOS_DL_LIST *priqueueItem)
{
    LosTaskCB *runningTask = NULL;
    LOS_ListDelete(priqueueItem);

    runningTask = LOS_DL_LIST_ENTRY(priqueueItem, LosTaskCB, pendList);
    if (LOS_ListEmpty(&g_losPriorityQueueList[runningTask->priority])) {
        g_priqueueBitmap &= ~(PRIQUEUE_PRIOR0_BIT >> runningTask->priority);
    }
}

LOS_DL_LIST *OsPriqueueTop(VOID)
{
    UINT32 priority;

    if (g_priqueueBitmap != 0) {
        priority = CLZ(g_priqueueBitmap);
        return LOS_DL_LIST_FIRST(&g_losPriorityQueueList[priority]);
    }

    return (LOS_DL_LIST *)NULL;
}

UINT32 OsPriqueueSize(UINT32 priority)
{
    UINT32 itemCnt = 0;
    LOS_DL_LIST *curPQNode = (LOS_DL_LIST *)NULL;

    LOS_DL_LIST_FOR_EACH(curPQNode, &g_losPriorityQueueList[priority]) {
        ++itemCnt;
    }

    return itemCnt;
}

UINT32 OsPriqueueTotalSize(VOID)
{
    UINT32 priority;
    UINT32 totalSize = 0;

    for (priority = 0; priority < OS_PRIORITY_QUEUE_PRIORITYNUM; ++priority) {
        totalSize += OsPriqueueSize(priority);
    }

    return totalSize;
}
