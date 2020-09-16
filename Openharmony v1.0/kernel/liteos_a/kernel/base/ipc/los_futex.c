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

#include "los_futex_pri.h"
#include "los_process_pri.h"
#include "los_sys_pri.h"
#include "los_sched_pri.h"
#include "los_mp.h"
#include "los_exc.h"
#include "los_mux_pri.h"
#include "user_copy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define OS_FUTEX_FROM_FUTEXLIST(ptr) LOS_DL_LIST_ENTRY(ptr, FutexNode, futexList)
#define OS_FUTEX_FROM_QUEUELIST(ptr) LOS_DL_LIST_ENTRY(ptr, FutexNode, queueList)
#define OS_FUTEX_KEY_BASE USER_ASPACE_BASE
#define OS_FUTEX_KEY_MAX (USER_ASPACE_BASE + USER_ASPACE_SIZE)

typedef struct {
    LosMux      listLock;
    LOS_DL_LIST lockList;
} FutexHash;

#define FUTEX_INDEX_MAX  128
FutexHash g_futexHash[FUTEX_INDEX_MAX];

STATIC INT32 OsFutexLock(LosMux *lock)
{
    UINT32 ret = LOS_MuxLock(lock, LOS_WAIT_FOREVER);
    if (ret != LOS_OK) {
        PRINT_ERR("Futex lock failed! ERROR: 0x%x!\n", ret);
        return LOS_EINVAL;
    }
    return LOS_OK;
}

STATIC INT32 OsFutexUnlock(LosMux *lock)
{
    UINT32 ret = LOS_MuxUnlock(lock);
    if (ret != LOS_OK) {
        PRINT_ERR("Futex unlock failed! ERROR: 0x%x!\n", ret);
        return LOS_EINVAL;
    }
    return LOS_OK;
}

UINT32 OsFutexInit(VOID)
{
    INT32 count;
    UINT32 ret;

    for (count = 0; count < FUTEX_INDEX_MAX; count++) {
        LOS_ListInit(&g_futexHash[count].lockList);
        ret = LOS_MuxInit(&(g_futexHash[count].listLock), NULL);
        if (ret) {
            return ret;
        }
    }

    return LOS_OK;
}

#ifdef LOS_FUTEX_DEBUG
STATIC VOID OsFutexShowTaskNodeAttr(const LOS_DL_LIST *futexList)
{
    FutexNode *tempNode = NULL;
    FutexNode *lastNode = NULL;
    LosTaskCB *taskCB = NULL;
    LOS_DL_LIST *queueList = NULL;

    tempNode = OS_FUTEX_FROM_FUTEXLIST(futexList);
    PRINTK("key           : 0x%x : ->", tempNode->key);

    for (queueList = &tempNode->queueList; ;) {
        lastNode = OS_FUTEX_FROM_QUEUELIST(queueList);
        if (!LOS_ListEmpty(&(lastNode->pendList))) {
            taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(lastNode->pendList)));
            PRINTK(" %d(%d) ->", taskCB->taskID, taskCB->priority);
        } else {
            taskCB = LOS_DL_LIST_ENTRY(lastNode, LosTaskCB, futex);
            PRINTK(" %d(%d) ->", taskCB->taskID, -1);
        }
        queueList = queueList->pstNext;
        if (queueList == &tempNode->queueList) {
            break;
        }
    }
    PRINTK("\n");
}

VOID OsFutexHashShow(VOID)
{
    LOS_DL_LIST *futexList = NULL;
    INT32 count;
    /* The maximum number of barrels of a hash table */
    INT32 hashNodeMax = FUTEX_INDEX_MAX;
    PRINTK("################los_futex_pri.hash ######################\n");
    for (count = 0; count < hashNodeMax; count++) {
        futexList = &(g_futexHash[count].lockList);
        if (LOS_ListEmpty(futexList)) {
            continue;
        }
        PRINTK("hash -> index : %d\n", count);
        for (futexList = futexList->pstNext;
             futexList != &(g_futexHash[count].lockList);
             futexList = futexList->pstNext) {
                OsFutexShowTaskNodeAttr(futexList);
        }
    }
}
#endif

STATIC UINT32 OsFutexGetTick(UINT32 absTime)
{
    UINT32 interval;

    /* the values not less than per Millisecond */
    if (absTime < OS_SYS_MS_PER_SECOND) {
        interval = OS_SYS_MS_PER_SECOND / LOSCFG_BASE_CORE_TICK_PER_SECOND;
    } else {
        interval = absTime / OS_SYS_MS_PER_SECOND;
    }

    interval = LOS_MS2Tick(interval);
    if (interval == 0) {
        interval = 1;
    }

    return interval;
}

STATIC INLINE VOID OsFutexSetKey(UINTPTR futexKey, FutexNode *node)
{
    node->key = futexKey;
    node->index = futexKey / OS_FUTEX_KEY_BASE;
    node->pid = LOS_GetCurrProcessID();
}

STATIC INLINE VOID OsFutexDeinitFutexNode(FutexNode *node)
{
    node->index = OS_INVALID_VALUE;
    node->pid = 0;
    LOS_ListDelete(&node->queueList);
}

STATIC INLINE VOID OsFutexReplaceQueueListHeadNode(FutexNode *oldHeadNode, FutexNode *newHeadNode)
{
    LOS_DL_LIST *futexList = oldHeadNode->futexList.pstPrev;
    LOS_ListDelete(&oldHeadNode->futexList);
    LOS_ListHeadInsert(futexList, &newHeadNode->futexList);
}

STATIC INLINE VOID OsFutexDeleteKeyFromFutexList(FutexNode *node)
{
    LOS_ListDelete(&node->futexList);
}

STATIC VOID OsFutexDeleteKeyNodeFromHash(FutexNode *node, BOOL isDeleteHead, FutexNode **headNode, BOOL *queueFlags)
{
    FutexNode *nextNode = NULL;

    if (node->index >= FUTEX_INDEX_MAX) {
        return;
    }

    if (LOS_ListEmpty(&node->queueList)) {
        OsFutexDeleteKeyFromFutexList(node);
        if (queueFlags != NULL) {
            *queueFlags = TRUE;
        }
        goto EXIT;
    }

    /* FutexList is not NULL, but the header node of queueList */
    if (node->futexList.pstNext != NULL) {
        if (isDeleteHead == TRUE) {
            nextNode = OS_FUTEX_FROM_QUEUELIST(LOS_DL_LIST_FIRST(&node->queueList));
            OsFutexReplaceQueueListHeadNode(node, nextNode);
            if (headNode != NULL) {
                *headNode = nextNode;
            }
        } else {
            return;
        }
    }

EXIT:
    OsFutexDeinitFutexNode(node);
    return;
}

VOID OsFutexNodeDeleteFromFutexHash(FutexNode *node, BOOL isDeleteHead, FutexNode **headNode, BOOL *queueFlags)
{
    FutexHash *hashNode = NULL;
    UINT32 index = node->key / OS_FUTEX_KEY_BASE;

    if (index >= FUTEX_INDEX_MAX) {
        return;
    }

    hashNode = &g_futexHash[index];
    if (OsMuxLockUnsafe(&hashNode->listLock, LOS_WAIT_FOREVER)) {
        return;
    }

    if (node->index != index) {
        goto EXIT;
    }

    OsFutexDeleteKeyNodeFromHash(node, isDeleteHead, headNode, queueFlags);

EXIT:
    if (OsMuxUnlockUnsafe(OsCurrTaskGet(), &hashNode->listLock, NULL)) {
        return;
    }

    return;
}

STATIC FutexNode *OsFutexDeleteAlreadyWakeTaskAndGetNext(const FutexNode *node, FutexNode **headNode, BOOL isDeleteHead)
{
    FutexNode *tempNode = (FutexNode *)node;
    FutexNode *nextNode = NULL;
    BOOL queueFlag = FALSE;

    while (LOS_ListEmpty(&(tempNode->pendList))) {     /* already weak */
        if (!LOS_ListEmpty(&(tempNode->queueList))) { /* It's not a head node */
            nextNode = OS_FUTEX_FROM_QUEUELIST(LOS_DL_LIST_FIRST(&(tempNode->queueList)));
        }

        OsFutexDeleteKeyNodeFromHash(tempNode, isDeleteHead, headNode, &queueFlag);
        if (queueFlag) {
            return NULL;
        }

        tempNode = nextNode;
    }

    return tempNode;
}

STATIC VOID OsFutexInsertNewFutexKeyToHash(FutexNode *node)
{
    FutexNode *headNode = NULL;
    FutexNode *tailNode = NULL;
    LOS_DL_LIST *futexList = NULL;
    FutexHash *hashNode = &g_futexHash[node->index];

    if (LOS_ListEmpty(&hashNode->lockList)) {
        LOS_ListHeadInsert(&(hashNode->lockList), &(node->futexList));
        goto EXIT;
    }

    headNode = OS_FUTEX_FROM_FUTEXLIST(LOS_DL_LIST_FIRST(&(hashNode->lockList)));
    /* The small key is at the front of the queue */
    if (node->key < headNode->key) {
        LOS_ListHeadInsert(&(hashNode->lockList), &(node->futexList));
        goto EXIT;
    }

    tailNode = OS_FUTEX_FROM_FUTEXLIST(LOS_DL_LIST_LAST(&(hashNode->lockList)));
    if (node->key > tailNode->key) {
        LOS_ListTailInsert(&(hashNode->lockList), &(node->futexList));
        goto EXIT;
    }

    for (futexList = hashNode->lockList.pstNext;
         futexList != &(hashNode->lockList);
         futexList = futexList->pstNext) {
        headNode = OS_FUTEX_FROM_FUTEXLIST(futexList);
        if (node->key > headNode->key) {
            continue;
        } else if (node->key < headNode->key) {
            LOS_ListTailInsert(&(headNode->futexList), &(node->futexList));
            break;
        }

        LOS_ListTailInsert(&(headNode->futexList), &(node->futexList));
        break;
    }

EXIT:
    return;
}

STATIC INT32 OsFutexInsertFindFormBackToFront(LOS_DL_LIST *queueList, const LosTaskCB *runTask, FutexNode *node)
{
    LOS_DL_LIST *listHead = queueList;
    LOS_DL_LIST *listTail = queueList->pstPrev;
    FutexNode *tempNode = NULL;
    LosTaskCB *taskTail = NULL;

    for (; listHead != listTail; listTail = listTail->pstPrev) {
        tempNode = OS_FUTEX_FROM_QUEUELIST(listTail);
        tempNode = OsFutexDeleteAlreadyWakeTaskAndGetNext(tempNode, NULL, FALSE);
        taskTail = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(tempNode->pendList)));
        if (runTask->priority >= taskTail->priority) {
            LOS_ListHeadInsert(&(tempNode->queueList), &(node->queueList));
            return LOS_OK;
        } else if (runTask->priority < taskTail->priority) {
            if (listTail->pstPrev == listHead) {
                LOS_ListTailInsert(&(tempNode->queueList), &(node->queueList));
                return LOS_OK;
            }
        }
    }

    return LOS_NOK;
}

STATIC INT32 OsFutexInsertFindFromFrontToBack(LOS_DL_LIST *queueList, const LosTaskCB *runTask, FutexNode *node)
{
    LOS_DL_LIST *listHead = queueList;
    LOS_DL_LIST *listTail = queueList->pstPrev;
    FutexNode *tempNode = NULL;
    LosTaskCB *taskHead = NULL;

    for (; listHead != listTail; listHead = listHead->pstNext) {
        tempNode = OS_FUTEX_FROM_QUEUELIST(listHead);
        tempNode = OsFutexDeleteAlreadyWakeTaskAndGetNext(tempNode, NULL, FALSE);
        taskHead = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(tempNode->pendList)));
        /* High priority comes before low priority,
         * in the case of the same priority, after the current node
         */
        if (runTask->priority >= taskHead->priority) {
            if (listHead->pstNext == listTail) {
                LOS_ListHeadInsert(&(tempNode->queueList), &(node->queueList));
                return LOS_OK;
            }
            continue;
        } else if (runTask->priority < taskHead->priority) {
            LOS_ListTailInsert(&(tempNode->queueList), &(node->queueList));
            return LOS_OK;
        }
    }

    return LOS_NOK;
}

STATIC INT32 OsFutexRecycleAndFindHeadNode(FutexNode *headNode, FutexNode *node, FutexNode **firstNode)
{
    UINT32 intSave;

    SCHEDULER_LOCK(intSave);
    *firstNode = OsFutexDeleteAlreadyWakeTaskAndGetNext(headNode, NULL, TRUE);
    SCHEDULER_UNLOCK(intSave);

    /* The head node is removed and there was originally only one node under the key */
    if (*firstNode == NULL) {
        OsFutexInsertNewFutexKeyToHash(node);
        LOS_ListInit(&(node->queueList));
        return LOS_OK;
    }

    return LOS_OK;
}

STATIC INT32 OsFutexInsertTasktoPendList(FutexNode **firstNode, FutexNode *node, const LosTaskCB *run)
{
    LosTaskCB *taskHead = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&((*firstNode)->pendList)));
    LOS_DL_LIST *queueList = &((*firstNode)->queueList);
    FutexNode *tailNode = NULL;
    LosTaskCB *taskTail = NULL;

    if (run->priority < taskHead->priority) {
        /* The one with the highest priority is inserted at the top of the queue */
        LOS_ListTailInsert(queueList, &(node->queueList));
        OsFutexReplaceQueueListHeadNode(*firstNode, node);
        *firstNode = node;
        return LOS_OK;
    }

    if (LOS_ListEmpty(queueList) && (run->priority >= taskHead->priority)) {
        /* Insert the next position in the queue with equal priority */
        LOS_ListHeadInsert(queueList, &(node->queueList));
        return LOS_OK;
    }

    tailNode = OS_FUTEX_FROM_QUEUELIST(LOS_DL_LIST_LAST(queueList));
    taskTail = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(tailNode->pendList)));
    if ((run->priority >= taskTail->priority) ||
        ((run->priority - taskHead->priority) > (taskTail->priority - run->priority))) {
        return OsFutexInsertFindFormBackToFront(queueList, run, node);
    }

    return OsFutexInsertFindFromFrontToBack(queueList, run, node);
}

STATIC FutexNode *OsFindFutexNode(const FutexNode *node)
{
    FutexHash *hashNode = &g_futexHash[node->index];
    LOS_DL_LIST *futexList = &(hashNode->lockList);
    FutexNode *headNode = NULL;

    for (futexList = futexList->pstNext;
         futexList != &(hashNode->lockList);
         futexList = futexList->pstNext) {
        headNode = OS_FUTEX_FROM_FUTEXLIST(futexList);
        if ((headNode->key == node->key) && (headNode->pid == node->pid)) {
            return headNode;
        }
    }

    return NULL;
}

STATIC INT32 OsFindAndInsertToHash(FutexNode *node)
{
    FutexNode *headNode = NULL;
    FutexNode *firstNode = NULL;
    UINT32 intSave;
    INT32 ret;

    headNode = OsFindFutexNode(node);
    if (headNode == NULL) {
        OsFutexInsertNewFutexKeyToHash(node);
        LOS_ListInit(&(node->queueList));
        return LOS_OK;
    }

    ret = OsFutexRecycleAndFindHeadNode(headNode, node, &firstNode);
    if (ret != LOS_OK) {
        return ret;
    } else if (firstNode == NULL) {
        return ret;
    }

    SCHEDULER_LOCK(intSave);
    ret = OsFutexInsertTasktoPendList(&firstNode, node, OsCurrTaskGet());
    SCHEDULER_UNLOCK(intSave);

    return ret;
}

STATIC INT32 OsFutexWaitParmaCheck(const UINT32 *userVaddr, UINT32 flags, UINT32 val, UINT32 absTime)
{
    UINTPTR futexKey = (UINTPTR)userVaddr;
    UINT32 lockVal;
    INT32 ret;

    if (OS_INT_ACTIVE) {
        return LOS_EINTR;
    }

    if (flags) {
        PRINT_ERR("Futex wait parma check failed! error flags: 0x%x\n", flags);
        return LOS_EINVAL;
    }

    if ((futexKey % sizeof(INT32)) || (futexKey < OS_FUTEX_KEY_BASE) || (futexKey >= OS_FUTEX_KEY_MAX)) {
        PRINT_ERR("Futex wait parma check failed! error futex key: 0x%x\n", futexKey);
        return LOS_EINVAL;
    }

    if (!absTime) {
        PRINT_ERR("Futex wait parma check failed! error absTime: %u\n", absTime);
        return LOS_EINVAL;
    }

    ret = LOS_ArchCopyFromUser(&lockVal, userVaddr, sizeof(UINT32));
    if (ret) {
        PRINT_ERR("Futex wait parma check failed! copy from user failed!\n");
        return LOS_EINVAL;
    }

    if (lockVal != val) {
        return LOS_EBADF;
    }

    return LOS_OK;
}

STATIC INT32 OsFutexDeleteTimeoutTaskNode(FutexHash *hashNode, FutexNode *node)
{
    UINT32 intSave;
    if (OsFutexLock(&hashNode->listLock)) {
        return LOS_EINVAL;
    }

    if (node->index < FUTEX_INDEX_MAX) {
        SCHEDULER_LOCK(intSave);
        (VOID)OsFutexDeleteAlreadyWakeTaskAndGetNext(node, NULL, TRUE);
        SCHEDULER_UNLOCK(intSave);
    }

#ifdef LOS_FUTEX_DEBUG
    OsFutexHashShow();
#endif

    if (OsFutexUnlock(&hashNode->listLock)) {
        return LOS_EINVAL;
    }
    return LOS_ETIMEDOUT;
}

STATIC INT32 OsFutexInserTaskToHash(LosTaskCB **taskCB, FutexNode **node, const UINTPTR futexKey)
{
    INT32 ret;
    *taskCB = OsCurrTaskGet();
    *node = &((*taskCB)->futex);
    OsFutexSetKey(futexKey, *node);

    ret = OsFindAndInsertToHash(*node);
    if (ret) {
        return LOS_NOK;
    }

    LOS_ListInit(&((*node)->pendList));
    return LOS_OK;
}

STATIC INT32 OsFutexWaitTask(const UINT32 timeOut, const UINT32 *userVaddr)
{
    INT32 futexRet;
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;
    FutexNode *node = NULL;
    UINTPTR futexKey = (UINTPTR)userVaddr;
    UINT32 index = futexKey / OS_FUTEX_KEY_BASE;
    FutexHash *hashNode = &g_futexHash[index];

    if (OsFutexLock(&hashNode->listLock)) {
        return LOS_EINVAL;
    }

    if (OsFutexInserTaskToHash(&taskCB, &node, futexKey)) {
        goto EXIT_ERR;
    }
    SCHEDULER_LOCK(intSave);
    OsTaskWait(&(node->pendList), timeOut, FALSE);
    OsPercpuGet()->taskLockCnt++;
    LOS_SpinUnlock(&g_taskSpin);

#ifdef LOS_FUTEX_DEBUG
    OsFutexHashShow();
#endif

    futexRet = OsFutexUnlock(&hashNode->listLock);
    if (futexRet) {
        OsPercpuGet()->taskLockCnt--;
        LOS_IntRestore(intSave);
        goto EXIT_UNLOCK_ERR;
    }

    LOS_SpinLock(&g_taskSpin);
    OsPercpuGet()->taskLockCnt--;

    /*
     * it will immediately do the scheduling, so there's no need to release the
     * task spinlock. when this task's been rescheduled, it will be holding the spinlock.
     */
    OsSchedResched();

    if (taskCB->taskStatus & OS_TASK_STATUS_TIMEOUT) {
        taskCB->taskStatus &= ~OS_TASK_STATUS_TIMEOUT;
        SCHEDULER_UNLOCK(intSave);
        return OsFutexDeleteTimeoutTaskNode(hashNode, node);
    }

    SCHEDULER_UNLOCK(intSave);
    return LOS_OK;

EXIT_ERR:
    futexRet = OsFutexUnlock(&hashNode->listLock);
EXIT_UNLOCK_ERR:
    if (futexRet) {
        return futexRet;
    }
    return LOS_NOK;
}

INT32 OsFutexWait(const UINT32 *userVaddr, UINT32 flags, UINT32 val, UINT32 absTime)
{
    INT32 ret;
    UINT32 timeOut = LOS_WAIT_FOREVER;

    ret = OsFutexWaitParmaCheck(userVaddr, flags, val, absTime);
    if (ret) {
        return ret;
    }
    if (absTime != LOS_WAIT_FOREVER) {
        timeOut = OsFutexGetTick(absTime);
    }

    return OsFutexWaitTask(timeOut, userVaddr);
}

/* Check to see if the task to be awakened has timed out
 * if time out, to weak next pend task.
 */
STATIC VOID OsFutexCheckAndWakePendTask(FutexNode *headNode, const INT32 wakeNumber,
                                        FutexHash *hashNode, FutexNode **nextNode, BOOL *wakeAny)
{
    INT32 count;
    LosTaskCB *taskCB = NULL;
    FutexNode *node = headNode;
    for (count = 0; count < wakeNumber; count++) {
        /* Ensure the integrity of the head */
        *nextNode = OsFutexDeleteAlreadyWakeTaskAndGetNext(node, NULL, FALSE);
        if (*nextNode == NULL) {
            /* The last node in queuelist is invalid or the entire list is invalid */
            return;
        }
        node = *nextNode;
        taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(node->pendList)));
        OsTaskWake(taskCB);
        *wakeAny = TRUE;
        *nextNode = OS_FUTEX_FROM_QUEUELIST(LOS_DL_LIST_FIRST(&(node->queueList)));
        if (node != headNode) {
            OsFutexDeinitFutexNode(node);
        }

        if (LOS_ListEmpty(&headNode->queueList)) {
            /* Wakes up the entire linked list node */
            *nextNode = NULL;
            return;
        }

        node = *nextNode;
    }
    return;
}

STATIC INT32 OsFutexWakeTask(UINTPTR futexKey, INT32 wakeNumber, FutexNode **newHeadNode, BOOL *wakeAny)
{
    UINT32 intSave;
    FutexNode *node = NULL;
    FutexNode *headNode = NULL;
    UINT32 index = futexKey / OS_FUTEX_KEY_BASE;
    FutexHash *hashNode = &g_futexHash[index];
    FutexNode tempNode = {
        .key = futexKey,
        .index = index,
        .pid = LOS_GetCurrProcessID(),
    };

    node = OsFindFutexNode(&tempNode);
    if (node == NULL) {
        return LOS_EBADF;
    }

    headNode = node;

    SCHEDULER_LOCK(intSave);
    OsFutexCheckAndWakePendTask(headNode, wakeNumber, hashNode, newHeadNode, wakeAny);
    if ((*newHeadNode) != NULL) {
        OsFutexReplaceQueueListHeadNode(headNode, *newHeadNode);
        OsFutexDeinitFutexNode(headNode);
    } else if (headNode->index < FUTEX_INDEX_MAX) {
        OsFutexDeleteKeyFromFutexList(headNode);
        OsFutexDeinitFutexNode(headNode);
    }
    SCHEDULER_UNLOCK(intSave);

    return LOS_OK;
}

INT32 OsFutexWake(const UINT32 *userVaddr, UINT32 flags, INT32 wakeNumber)
{
    INT32 ret, futexRet;
    UINTPTR futexKey = (UINTPTR)userVaddr;
    FutexHash *hashNode = NULL;
    INT32 index = futexKey / OS_FUTEX_KEY_BASE;
    FutexNode *headNode = NULL;
    BOOL wakeAny = FALSE;

    if (!(flags & FUTEX_WAKE)) {
        PRINT_ERR("Futex wake param check failed! error flags: 0x%x\n", flags);
        return LOS_EINVAL;
    }

    if ((futexKey % sizeof(INT32)) || (futexKey < OS_FUTEX_KEY_BASE) || (futexKey >= OS_FUTEX_KEY_MAX)) {
        PRINT_ERR("Futex wake param check failed! error futex key: 0x%x\n", futexKey);
        return LOS_EINVAL;
    }

    hashNode = &g_futexHash[index];
    if (OsFutexLock(&hashNode->listLock)) {
        return LOS_EINVAL;
    }

    ret = OsFutexWakeTask(futexKey, wakeNumber, &headNode, &wakeAny);
    if (ret) {
        goto EXIT_ERR;
    }

#ifdef LOS_FUTEX_DEBUG
    OsFutexHashShow();
#endif

    futexRet = OsFutexUnlock(&hashNode->listLock);
    if (futexRet) {
        goto EXIT_UNLOCK_ERR;
    }

    if (wakeAny == TRUE) {
        LOS_MpSchedule(OS_MP_CPU_ALL);
        LOS_Schedule();
    }

    return LOS_OK;

EXIT_ERR:
    futexRet = OsFutexUnlock(&hashNode->listLock);
EXIT_UNLOCK_ERR:
    if (futexRet) {
        return futexRet;
    }
    return ret;
}

STATIC INT32 OsFutexRequeueInsertNewKey(UINTPTR newFutexKey, INT32 newIndex, FutexNode *oldHeadNode)
{
    INT32 ret;
    UINT32 intSave;
    LosTaskCB *task = NULL;
    FutexNode *nextNode = NULL;
    FutexNode newTempNode = {
        .key = newFutexKey,
        .index = newIndex,
        .pid = LOS_GetCurrProcessID(),
    };
    LOS_DL_LIST *queueList = &oldHeadNode->queueList;
    FutexNode *newHeadNode = OsFindFutexNode(&newTempNode);
    if (newHeadNode == NULL) {
        OsFutexInsertNewFutexKeyToHash(oldHeadNode);
        return LOS_OK;
    }

    do {
        nextNode = OS_FUTEX_FROM_QUEUELIST(queueList);
        SCHEDULER_LOCK(intSave);
        if (LOS_ListEmpty(&nextNode->pendList)) {
            queueList = queueList->pstNext;
            OsFutexDeinitFutexNode(nextNode);
            SCHEDULER_UNLOCK(intSave);
            if (queueList->pstNext != NULL) {
                continue;
            } else {
                return LOS_OK;
            }
        }

        task = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(nextNode->pendList)));
        queueList = queueList->pstNext;
        LOS_ListDelete(&nextNode->queueList);
        ret = OsFutexInsertTasktoPendList(&newHeadNode, nextNode, task);
        SCHEDULER_UNLOCK(intSave);
        if (ret != LOS_OK) {
            PRINT_ERR("Futex requeue insert new key failed!\n");
        }
    } while (queueList->pstNext != NULL);

    return LOS_OK;
}

STATIC VOID OsFutexRequeueSplitTwoLists(FutexHash *oldHashNode, FutexNode *oldHeadNode, UINTPTR futexKey, INT32 count)
{
    LOS_DL_LIST *queueList = &oldHeadNode->queueList;
    FutexNode *tailNode = OS_FUTEX_FROM_QUEUELIST(LOS_DL_LIST_LAST(queueList));
    INT32 newIndex = futexKey / OS_FUTEX_KEY_BASE;
    FutexNode *nextNode = NULL;
    FutexNode *newHeadNode = NULL;
    LOS_DL_LIST *futexList = NULL;
    BOOL IsAll = FALSE;
    INT32 i;

    for (i = 0; i < count; i++) {
        nextNode = OS_FUTEX_FROM_QUEUELIST(queueList);
        nextNode->key = futexKey;
        nextNode->index = newIndex;
        if (queueList->pstNext == &oldHeadNode->queueList) {
            IsAll = TRUE;
            break;
        }

        queueList = queueList->pstNext;
    }

    futexList = oldHeadNode->futexList.pstPrev;
    LOS_ListDelete(&oldHeadNode->futexList);
    if (IsAll == TRUE) {
        return;
    }

    newHeadNode = OS_FUTEX_FROM_QUEUELIST(queueList);
    LOS_ListHeadInsert(futexList, &newHeadNode->futexList);
    oldHeadNode->queueList.pstPrev = &nextNode->queueList;
    nextNode->queueList.pstNext = &oldHeadNode->queueList;
    newHeadNode->queueList.pstPrev = &tailNode->queueList;
    tailNode->queueList.pstNext = &newHeadNode->queueList;
    return;
}

STATIC FutexNode *OsFutexRequeueRemoveOldKeyAndGetHead(UINTPTR oldFutexKey, INT32 wakeNumber,
                                                       UINTPTR newFutexKey, INT32 requeueCount, BOOL *wakeAny)
{
    INT32 ret;
    FutexNode *oldHeadNode = NULL;
    INT32 oldIndex = oldFutexKey / OS_FUTEX_KEY_BASE;
    FutexHash *oldHashNode = &g_futexHash[oldIndex];
    FutexNode oldTempNode = {
        .key = oldFutexKey,
        .index = oldIndex,
        .pid = LOS_GetCurrProcessID(),
    };

    if (wakeNumber > 0) {
        ret = OsFutexWakeTask(oldFutexKey, wakeNumber, &oldHeadNode, wakeAny);
        if ((ret != LOS_OK) || (oldHeadNode == NULL)) {
            return NULL;
        }
    }

    if (requeueCount <= 0) {
        return NULL;
    }

    if (oldHeadNode == NULL) {
        oldHeadNode = OsFindFutexNode(&oldTempNode);
        if (oldHeadNode == NULL) {
            return NULL;
        }
    }

    OsFutexRequeueSplitTwoLists(oldHashNode, oldHeadNode, newFutexKey, requeueCount);

    return oldHeadNode;
}

STATIC INT32 OsFutexRequeueParamCheck(UINTPTR oldFutexKey, UINTPTR newFutexKey)
{
    if (oldFutexKey == newFutexKey) {
        return LOS_EINVAL;
    }

    if ((oldFutexKey % sizeof(INT32)) || (oldFutexKey < OS_FUTEX_KEY_BASE) || (oldFutexKey >= OS_FUTEX_KEY_MAX)) {
        PRINT_ERR("Futex requeue param check failed! error old futex key: 0x%x\n", oldFutexKey);
        return LOS_EINVAL;
    }

    if ((newFutexKey % sizeof(INT32)) || (newFutexKey < OS_FUTEX_KEY_BASE) || (newFutexKey >= OS_FUTEX_KEY_MAX)) {
        PRINT_ERR("Futex requeue param check failed! error new futex key: 0x%x\n", newFutexKey);
        return LOS_EINVAL;
    }

    return LOS_OK;
}

INT32 OsFutexRequeue(const UINT32 *userVaddr, UINT32 flags, INT32 wakeNumber, INT32 count, const UINT32 *newUserVaddr)
{
    INT32 ret;
    UINTPTR oldFutexKey = (UINTPTR)userVaddr;
    UINTPTR newFutexKey = (UINTPTR)newUserVaddr;
    INT32 oldIndex = oldFutexKey / OS_FUTEX_KEY_BASE;
    INT32 newIndex = newFutexKey / OS_FUTEX_KEY_BASE;
    FutexHash *oldHashNode = NULL;
    FutexHash *newHashNode = NULL;
    FutexNode *oldHeadNode = NULL;
    BOOL wakeAny = FALSE;

    if (OsFutexRequeueParamCheck(oldFutexKey, newFutexKey)) {
        return LOS_EINVAL;
    }

    oldHashNode = &g_futexHash[oldIndex];
    if (OsFutexLock(&oldHashNode->listLock)) {
        return LOS_EINVAL;
    }

    oldHeadNode = OsFutexRequeueRemoveOldKeyAndGetHead(oldFutexKey, wakeNumber, newFutexKey, count, &wakeAny);
    if (oldHeadNode == NULL) {
        (VOID)OsFutexUnlock(&oldHashNode->listLock);
        if (wakeAny == TRUE) {
            ret = LOS_OK;
            goto EXIT;
        }
        return LOS_EBADF;
    }

    newHashNode = &g_futexHash[newIndex];
    if (oldIndex != newIndex) {
        if (OsFutexUnlock(&oldHashNode->listLock)) {
            return LOS_EINVAL;
        }

        if (OsFutexLock(&newHashNode->listLock)) {
            return LOS_EINVAL;
        }
    }

    ret = OsFutexRequeueInsertNewKey(newFutexKey, newIndex, oldHeadNode);

    if (OsFutexUnlock(&newHashNode->listLock)) {
        return LOS_EINVAL;
    }

EXIT:
    if (wakeAny == TRUE) {
        LOS_MpSchedule(OS_MP_CPU_ALL);
        LOS_Schedule();
    }

    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
