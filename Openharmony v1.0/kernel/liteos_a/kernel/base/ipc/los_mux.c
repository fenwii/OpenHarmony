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

#include "los_mux_pri.h"
#include "los_bitmap.h"
#include "los_spinlock.h"
#include "los_mp.h"
#include "los_task_pri.h"
#include "los_exc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if (LOSCFG_BASE_IPC_MUX == YES)
#define MUTEXATTR_TYPE_MASK 0x0FU

LITE_OS_SEC_TEXT UINT32 LOS_MuxAttrInit(LosMuxAttr *attr)
{
    if (attr == NULL) {
        return LOS_EINVAL;
    }

    attr->protocol    = LOS_MUX_PRIO_INHERIT;
    attr->prioceiling = OS_TASK_PRIORITY_LOWEST;
    attr->type        = LOS_MUX_DEFAULT;
    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxAttrDestroy(LosMuxAttr *attr)
{
    if (attr == NULL) {
        return LOS_EINVAL;
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxAttrGetType(const LosMuxAttr *attr, INT32 *outType)
{
    INT32 type;

    if ((attr == NULL) || (outType == NULL)) {
        return LOS_EINVAL;
    }

    type = (INT32)(attr->type & MUTEXATTR_TYPE_MASK);
    if ((type < LOS_MUX_NORMAL) || (type > LOS_MUX_ERRORCHECK)) {
        return LOS_EINVAL;
    }

    *outType = type;

    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxAttrSetType(LosMuxAttr *attr, INT32 type)
{
    if ((attr == NULL) || (type < LOS_MUX_NORMAL) || (type > LOS_MUX_ERRORCHECK)) {
        return LOS_EINVAL;
    }

    attr->type = (UINT8)((attr->type & ~MUTEXATTR_TYPE_MASK) | (UINT32)type);
    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxAttrGetProtocol(const LosMuxAttr *attr, INT32 *protocol)
{
    if ((attr != NULL) && (protocol != NULL)) {
        *protocol = attr->protocol;
    } else {
        return LOS_EINVAL;
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxAttrSetProtocol(LosMuxAttr *attr, INT32 protocol)
{
    if (attr == NULL) {
        return LOS_EINVAL;
    }

    switch (protocol) {
        case LOS_MUX_PRIO_NONE:
        case LOS_MUX_PRIO_INHERIT:
        case LOS_MUX_PRIO_PROTECT:
            attr->protocol = (UINT8)protocol;
            return LOS_OK;
        default:
            return LOS_EINVAL;
    }
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxAttrGetPrioceiling(const LosMuxAttr *attr, INT32 *prioceiling)
{
    if (attr == NULL) {
        return LOS_EINVAL;
    }

    if (prioceiling != NULL) {
        *prioceiling = attr->prioceiling;
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxAttrSetPrioceiling(LosMuxAttr *attr, INT32 prioceiling)
{
    if ((attr == NULL) ||
        (prioceiling < OS_TASK_PRIORITY_HIGHEST) ||
        (prioceiling > OS_TASK_PRIORITY_LOWEST)) {
        return LOS_EINVAL;
    }

    attr->prioceiling = (UINT8)prioceiling;

    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxSetPrioceiling(LosMux *mutex, INT32 prioceiling, INT32 *oldPrioceiling)
{
    INT32 ret;
    INT32 retLock;
    if ((mutex == NULL) ||
        (prioceiling < OS_TASK_PRIORITY_HIGHEST) ||
        (prioceiling > OS_TASK_PRIORITY_LOWEST)) {
        return LOS_EINVAL;
    }

    retLock = LOS_MuxLock(mutex, LOS_WAIT_FOREVER);
    if (retLock != LOS_OK) {
        return retLock;
    }

    if (oldPrioceiling != NULL) {
        *oldPrioceiling = mutex->attr.prioceiling;
    }

    ret = LOS_MuxAttrSetPrioceiling(&mutex->attr, prioceiling);

    retLock = LOS_MuxUnlock(mutex);
    if ((ret == LOS_OK) && (retLock != LOS_OK)) {
        return retLock;
    }

    return ret;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxGetPrioceiling(const LosMux *mutex, INT32 *prioceiling)
{
    if ((mutex != NULL) && (prioceiling != NULL) && (mutex->magic == OS_MUX_MAGIC)) {
        *prioceiling = mutex->attr.prioceiling;
        return LOS_OK;
    }

    return LOS_EINVAL;
}

LITE_OS_SEC_TEXT BOOL LOS_MuxIsValid(const LosMux *mutex)
{
    if ((mutex != NULL) && (mutex->magic == OS_MUX_MAGIC)) {
        return TRUE;
    }

    return FALSE;
}

STATIC UINT32 OsCheckMutexAttr(const LosMuxAttr *attr)
{
    if (((INT8)(attr->type) < LOS_MUX_NORMAL) || (attr->type > LOS_MUX_ERRORCHECK)) {
        return LOS_NOK;
    }
    if (((INT8)(attr->prioceiling) < OS_TASK_PRIORITY_HIGHEST) || (attr->prioceiling > OS_TASK_PRIORITY_LOWEST)) {
        return LOS_NOK;
    }
    if (((INT8)(attr->protocol) < LOS_MUX_PRIO_NONE) || (attr->protocol > LOS_MUX_PRIO_PROTECT)) {
        return LOS_NOK;
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxInit(LosMux *mutex, const LosMuxAttr *attr)
{
    UINT32 intSave;

    if (mutex == NULL) {
        return LOS_EINVAL;
    }

    if (attr == NULL) {
        (VOID)LOS_MuxAttrInit(&mutex->attr);
    } else {
        (VOID)memcpy_s(&mutex->attr, sizeof(LosMuxAttr), attr, sizeof(LosMuxAttr));
    }

    if (OsCheckMutexAttr(&mutex->attr) != LOS_OK) {
        return LOS_EINVAL;
    }

    SCHEDULER_LOCK(intSave);
    mutex->muxCount = 0;
    mutex->owner = NULL;
    LOS_ListInit(&mutex->muxList);
    mutex->magic = OS_MUX_MAGIC;
    SCHEDULER_UNLOCK(intSave);
    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxDestroy(LosMux *mutex)
{
    UINT32 intSave;

    if (mutex == NULL) {
        return LOS_EINVAL;
    }

    SCHEDULER_LOCK(intSave);
    if (mutex->magic != OS_MUX_MAGIC) {
        SCHEDULER_UNLOCK(intSave);
        return LOS_EBADF;
    }

    if (mutex->muxCount != 0) {
        SCHEDULER_UNLOCK(intSave);
        return LOS_EBUSY;
    }

    (VOID)memset_s(mutex, sizeof(LosMux), 0, sizeof(LosMux));
    SCHEDULER_UNLOCK(intSave);
    return LOS_OK;
}

STATIC VOID OsMuxBitmapSet(const LosMux *mutex, const LosTaskCB *runTask, LosTaskCB *owner)
{
    if ((owner->priority > runTask->priority) && (mutex->attr.protocol == LOS_MUX_PRIO_INHERIT)) {
        LOS_BitmapSet(&(owner->priBitMap), owner->priority);
        OsTaskPriModify(owner, runTask->priority);
    }
}

VOID OsMuxBitmapRestore(const LosMux *mutex, const LosTaskCB *taskCB, LosTaskCB *owner)
{
    UINT16 bitMapPri;

    if (mutex->attr.protocol != LOS_MUX_PRIO_INHERIT) {
        return;
    }

    if (owner->priority >= taskCB->priority) {
        bitMapPri = LOS_LowBitGet(owner->priBitMap);
        if (bitMapPri != LOS_INVALID_BIT_INDEX) {
            LOS_BitmapClr(&(owner->priBitMap), bitMapPri);
            OsTaskPriModify(owner, bitMapPri);
        }
    } else {
        if (LOS_HighBitGet(owner->priBitMap) != taskCB->priority) {
            LOS_BitmapClr(&(owner->priBitMap), taskCB->priority);
        }
    }
}

STATIC LOS_DL_LIST *OsMuxPendFindPosSub(const LosTaskCB *runTask, const LosMux *mutex)
{
    LosTaskCB *pendedTask = NULL;
    LOS_DL_LIST *node = NULL;

    LOS_DL_LIST_FOR_EACH_ENTRY(pendedTask, &(mutex->muxList), LosTaskCB, pendList) {
        if (pendedTask->priority < runTask->priority) {
            continue;
        } else if (pendedTask->priority > runTask->priority) {
            node = &pendedTask->pendList;
            break;
        } else {
            node = pendedTask->pendList.pstNext;
            break;
        }
    }

    return node;
}

STATIC LOS_DL_LIST *OsMuxPendFindPos(const LosTaskCB *runTask, LosMux *mutex)
{
    LosTaskCB *pendedTask1 = NULL;
    LosTaskCB *pendedTask2 = NULL;
    LOS_DL_LIST *node = NULL;

    if (LOS_ListEmpty(&mutex->muxList)) {
        node = &mutex->muxList;
    } else {
        pendedTask1 = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&mutex->muxList));
        pendedTask2 = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_LAST(&mutex->muxList));
        if ((pendedTask1 != NULL) && (pendedTask1->priority > runTask->priority)) {
            node = mutex->muxList.pstNext;
        } else if ((pendedTask2 != NULL) && (pendedTask2->priority <= runTask->priority)) {
            node = &mutex->muxList;
        } else {
            node = OsMuxPendFindPosSub(runTask, mutex);
        }
    }

    return node;
}

STATIC UINT32 OsMuxPendOp(LosTaskCB *runTask, LosMux *mutex, UINT32 timeout)
{
    UINT32 ret;
    LOS_DL_LIST *node = NULL;
    LosTaskCB *owner = NULL;

    if ((mutex->muxList.pstPrev == NULL) || (mutex->muxList.pstNext == NULL)) {
        /* This is for mutex macro initialization. */
        mutex->muxCount = 0;
        mutex->owner = NULL;
        LOS_ListInit(&mutex->muxList);
    }

    if (mutex->muxCount == 0) {
        mutex->muxCount++;
        mutex->owner = (VOID *)runTask;
        LOS_ListTailInsert(&runTask->lockList, &mutex->holdList);
        if ((runTask->priority > mutex->attr.prioceiling) && (mutex->attr.protocol == LOS_MUX_PRIO_PROTECT)) {
            LOS_BitmapSet(&runTask->priBitMap, runTask->priority);
            OsTaskPriModify(runTask, mutex->attr.prioceiling);
        }
        return LOS_OK;
    }

    if (((LosTaskCB *)mutex->owner == runTask) && (mutex->attr.type == LOS_MUX_RECURSIVE)) {
        mutex->muxCount++;
        return LOS_OK;
    }

    if (!timeout) {
        return LOS_EINVAL;
    }

    if (!OsPreemptableInSched()) {
        return LOS_EDEADLK;
    }

    OsMuxBitmapSet(mutex, runTask, (LosTaskCB *)mutex->owner);

    owner = (LosTaskCB *)mutex->owner;
    runTask->taskMux = (VOID *)mutex;
    node = OsMuxPendFindPos(runTask, mutex);

    ret = OsTaskWait(node, timeout, TRUE);
    if (ret == LOS_ERRNO_TSK_TIMEOUT) {
        runTask->taskMux = NULL;
        ret = LOS_ETIMEDOUT;
    }

    if (timeout != LOS_WAIT_FOREVER) {
        OsMuxBitmapRestore(mutex, runTask, owner);
    }

    return ret;
}

UINT32 OsMuxLockUnsafe(LosMux *mutex, UINT32 timeout)
{
    LosTaskCB *runTask = OsCurrTaskGet();

    if (mutex->magic != OS_MUX_MAGIC) {
        return LOS_EBADF;
    }

    if (OsCheckMutexAttr(&mutex->attr) != LOS_OK) {
        return LOS_EINVAL;
    }

    if ((mutex->attr.type == LOS_MUX_ERRORCHECK) && (mutex->muxCount != 0) && (mutex->owner == (VOID *)runTask)) {
        return LOS_EDEADLK;
    }

    return OsMuxPendOp(runTask, mutex, timeout);
}

UINT32 OsMuxTrylockUnsafe(LosMux *mutex, UINT32 timeout)
{
    LosTaskCB *runTask = OsCurrTaskGet();

    if (mutex->magic != OS_MUX_MAGIC) {
        return LOS_EBADF;
    }

    if (OsCheckMutexAttr(&mutex->attr) != LOS_OK) {
        return LOS_EINVAL;
    }

    if ((mutex->owner != NULL) && ((LosTaskCB *)mutex->owner != runTask)) {
        return LOS_EBUSY;
    }
    if ((mutex->attr.type != LOS_MUX_RECURSIVE) && (mutex->muxCount != 0)) {
        return LOS_EBUSY;
    }

    return OsMuxPendOp(runTask, mutex, timeout);
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxLock(LosMux *mutex, UINT32 timeout)
{
    LosTaskCB *runTask = NULL;
    UINT32 intSave;
    UINT32 ret;

    if (mutex == NULL) {
        return LOS_EINVAL;
    }

    if (OS_INT_ACTIVE) {
        return LOS_EINTR;
    }

    runTask = (LosTaskCB *)OsCurrTaskGet();
    /* DO NOT Call blocking API in system tasks */
    if (runTask->taskStatus & OS_TASK_FLAG_SYSTEM_TASK) {
        PRINTK("Warning: DO NOT call %s in system tasks.\n", __FUNCTION__);
        OsBackTrace();
    }

    SCHEDULER_LOCK(intSave);
    ret = OsMuxLockUnsafe(mutex, timeout);
    SCHEDULER_UNLOCK(intSave);
    return ret;
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxTrylock(LosMux *mutex)
{
    LosTaskCB *runTask = NULL;
    UINT32 intSave;
    UINT32 ret;

    if (mutex == NULL) {
        return LOS_EINVAL;
    }

    if (OS_INT_ACTIVE) {
        return LOS_EINTR;
    }

    runTask = (LosTaskCB *)OsCurrTaskGet();
    /* DO NOT Call blocking API in system tasks */
    if (runTask->taskStatus & OS_TASK_FLAG_SYSTEM_TASK) {
        PRINTK("Warning: DO NOT call %s in system tasks.\n", __FUNCTION__);
        OsBackTrace();
    }

    SCHEDULER_LOCK(intSave);
    ret = OsMuxTrylockUnsafe(mutex, 0);
    SCHEDULER_UNLOCK(intSave);
    return ret;
}

STATIC VOID OsMuxPostOpSub(LosTaskCB *taskCB, LosMux *mutex)
{
    LosTaskCB *pendedTask = NULL;
    UINT16 bitMapPri;

    if (!LOS_ListEmpty(&mutex->muxList)) {
        bitMapPri = LOS_HighBitGet(taskCB->priBitMap);
        LOS_DL_LIST_FOR_EACH_ENTRY(pendedTask, (&mutex->muxList), LosTaskCB, pendList) {
            if (bitMapPri != pendedTask->priority) {
                LOS_BitmapClr(&taskCB->priBitMap, pendedTask->priority);
            }
        }
    }
    bitMapPri = LOS_LowBitGet(taskCB->priBitMap);
    LOS_BitmapClr(&taskCB->priBitMap, bitMapPri);
    OsTaskPriModify((LosTaskCB *)mutex->owner, bitMapPri);
}

STATIC UINT32 OsMuxPostOp(LosTaskCB *taskCB, LosMux *mutex, BOOL *needSched)
{
    LosTaskCB *resumedTask = NULL;

    if (LOS_ListEmpty(&mutex->muxList)) {
        LOS_ListDelete(&mutex->holdList);
        mutex->owner = NULL;
        return LOS_OK;
    }

    resumedTask = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(mutex->muxList)));
    if (mutex->attr.protocol == LOS_MUX_PRIO_INHERIT) {
        if (resumedTask->priority > taskCB->priority) {
            if (LOS_HighBitGet(taskCB->priBitMap) != resumedTask->priority) {
                LOS_BitmapClr(&taskCB->priBitMap, resumedTask->priority);
            }
        } else if (taskCB->priBitMap != 0) {
            OsMuxPostOpSub(taskCB, mutex);
        }
    }
    mutex->muxCount = 1;
    mutex->owner = (VOID *)resumedTask;
    resumedTask->taskMux = NULL;
    LOS_ListDelete(&mutex->holdList);
    LOS_ListTailInsert(&resumedTask->lockList, &mutex->holdList);
    OsTaskWake(resumedTask);
    if (needSched != NULL) {
        *needSched = TRUE;
    }

    return LOS_OK;
}

UINT32 OsMuxUnlockUnsafe(LosTaskCB *taskCB, LosMux *mutex, BOOL *needSched)
{
    UINT16 bitMapPri;

    if (mutex->magic != OS_MUX_MAGIC) {
        return LOS_EBADF;
    }

    if (OsCheckMutexAttr(&mutex->attr) != LOS_OK) {
        return LOS_EINVAL;
    }

    if (mutex->muxCount == 0) {
        return LOS_EPERM;
    }

    if ((LosTaskCB *)mutex->owner != taskCB) {
        return LOS_EPERM;
    }

    if ((--mutex->muxCount != 0) && (mutex->attr.type == LOS_MUX_RECURSIVE)) {
        return LOS_OK;
    }

    if (mutex->attr.protocol == LOS_MUX_PRIO_PROTECT) {
        bitMapPri = LOS_HighBitGet(taskCB->priBitMap);
        if (bitMapPri != LOS_INVALID_BIT_INDEX) {
            LOS_BitmapClr(&taskCB->priBitMap, bitMapPri);
            OsTaskPriModify(taskCB, bitMapPri);
        }
    }

    /* Whether a task block the mutex lock. */
    return OsMuxPostOp(taskCB, mutex, needSched);
}

LITE_OS_SEC_TEXT UINT32 LOS_MuxUnlock(LosMux *mutex)
{
    LosTaskCB *runTask = NULL;
    BOOL needSched = FALSE;
    UINT32 intSave;
    UINT32 ret;

    if (mutex == NULL) {
        return LOS_EINVAL;
    }

    if (OS_INT_ACTIVE) {
        return LOS_EINTR;
    }

    runTask = (LosTaskCB *)OsCurrTaskGet();
    /* DO NOT Call blocking API in system tasks */
    if (runTask->taskStatus & OS_TASK_FLAG_SYSTEM_TASK) {
        PRINTK("Warning: DO NOT call %s in system tasks.\n", __FUNCTION__);
        OsBackTrace();
    }

    SCHEDULER_LOCK(intSave);
    ret = OsMuxUnlockUnsafe(runTask, mutex, &needSched);
    SCHEDULER_UNLOCK(intSave);
    if (needSched == TRUE) {
        LOS_MpSchedule(OS_MP_CPU_ALL);
        LOS_Schedule();
    }
    return ret;
}

#endif /* (LOSCFG_BASE_IPC_MUX == YES) */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
