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
#include "los_queue_pri.h"
#include "los_membox_pri.h"
#include "los_memory_pri.h"
#include "los_priqueue_pri.h"
#include "los_task_pri.h"
#if (LOSCFG_PLATFORM_EXC == YES)
#include "los_exc_pri.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if (LOSCFG_BASE_IPC_QUEUE == YES)

LITE_OS_SEC_BSS LosQueueCB *g_allQueue = NULL ;
LITE_OS_SEC_BSS LOS_DL_LIST g_freeQueueList;
#if (LOSCFG_PLATFORM_EXC == YES)
LITE_OS_SEC_BSS UINT32 g_excQueueMaxNum;
#endif

/**************************************************************************
 Function    : OsQueueInit
 Description : queue initial
 Input       : None
 Output      : None
 Return      : LOS_OK on success or error code on failure
**************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsQueueInit(VOID)
{
    LosQueueCB *queueNode = NULL;
    UINT16 index;

    if (LOSCFG_BASE_IPC_QUEUE_LIMIT == 0) {
        return LOS_ERRNO_QUEUE_MAXNUM_ZERO;
    }

    g_allQueue = (LosQueueCB *)LOS_MemAlloc(m_aucSysMem0, LOSCFG_BASE_IPC_QUEUE_LIMIT * sizeof(LosQueueCB));
    if (g_allQueue == NULL) {
        return LOS_ERRNO_QUEUE_NO_MEMORY;
    }

    (VOID)memset_s(g_allQueue, LOSCFG_BASE_IPC_QUEUE_LIMIT * sizeof(LosQueueCB),
                   0, LOSCFG_BASE_IPC_QUEUE_LIMIT * sizeof(LosQueueCB));

    LOS_ListInit(&g_freeQueueList);
    for (index = 0; index < LOSCFG_BASE_IPC_QUEUE_LIMIT; index++) {
        queueNode = ((LosQueueCB *)g_allQueue) + index;
        queueNode->queueID = index;
        LOS_ListTailInsert(&g_freeQueueList, &queueNode->readWriteList[OS_QUEUE_WRITE]);
    }

#if (LOSCFG_PLATFORM_EXC == YES)
    g_excQueueMaxNum = LOSCFG_BASE_IPC_QUEUE_LIMIT;
    OsExcRegister(OS_EXC_TYPE_QUE, (EXC_INFO_SAVE_CALLBACK)LOS_QueueInfoGet, &g_excQueueMaxNum);
#endif

    return LOS_OK;
}

/*****************************************************************************
 Function    : LOS_QueueCreate
 Description : Create a queue
 Input       : queueName  --- Queue name, less than 4 characters
             : len        --- Queue lenth
             : flags      --- Queue type, FIFO or PRIO
             : maxMsgSize --- Maximum message size in byte
 Output      : queueID    --- Queue ID
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_QueueCreate(CHAR *queueName,
                                             UINT16 len,
                                             UINT32 *queueID,
                                             UINT32 flags,
                                             UINT16 maxMsgSize)
{
    LosQueueCB *queueCB = NULL;
    UINTPTR intSave;
    LOS_DL_LIST *unusedQueue = NULL;
    UINT8 *queue = NULL;
    UINT16 msgSize;

    (VOID)queueName;
    (VOID)flags;

    if (queueID == NULL) {
        return LOS_ERRNO_QUEUE_CREAT_PTR_NULL;
    }

    if (maxMsgSize > (OS_NULL_SHORT - sizeof(UINT32))) {
        return LOS_ERRNO_QUEUE_SIZE_TOO_BIG;
    }

    if ((len == 0) || (maxMsgSize == 0)) {
        return LOS_ERRNO_QUEUE_PARA_ISZERO;
    }
    msgSize = maxMsgSize + sizeof(UINT32);

    /* Memory allocation is time-consuming, to shorten the time of disable interrupt,
       move the memory allocation to here. */
    queue = (UINT8 *)LOS_MemAlloc(m_aucSysMem0, len * msgSize);
    if (queue == NULL) {
        return LOS_ERRNO_QUEUE_CREATE_NO_MEMORY;
    }

    intSave = LOS_IntLock();
    if (LOS_ListEmpty(&g_freeQueueList)) {
        LOS_IntRestore(intSave);
        (VOID)LOS_MemFree(m_aucSysMem0, queue);
        return LOS_ERRNO_QUEUE_CB_UNAVAILABLE;
    }

    unusedQueue = LOS_DL_LIST_FIRST(&(g_freeQueueList));
    LOS_ListDelete(unusedQueue);
    queueCB = (GET_QUEUE_LIST(unusedQueue));
    queueCB->queueLen = len;
    queueCB->queueSize = msgSize;
    queueCB->queue = queue;
    queueCB->queueState = OS_QUEUE_INUSED;
    queueCB->readWriteableCnt[OS_QUEUE_READ] = 0;
    queueCB->readWriteableCnt[OS_QUEUE_WRITE] = len;
    queueCB->queueHead = 0;
    queueCB->queueTail = 0;
    LOS_ListInit(&queueCB->readWriteList[OS_QUEUE_READ]);
    LOS_ListInit(&queueCB->readWriteList[OS_QUEUE_WRITE]);
    LOS_ListInit(&queueCB->memList);
    LOS_IntRestore(intSave);

    *queueID = queueCB->queueID;

    return LOS_OK;
}

static INLINE LITE_OS_SEC_TEXT UINT32 OsQueueReadParameterCheck(UINT32 queueID, VOID *bufferAddr,
                                                                UINT32 *bufferSize, UINT32 timeOut)
{
    if (queueID >= LOSCFG_BASE_IPC_QUEUE_LIMIT) {
        return LOS_ERRNO_QUEUE_INVALID;
    }
    if ((bufferAddr == NULL) || (bufferSize == NULL)) {
        return LOS_ERRNO_QUEUE_READ_PTR_NULL;
    }

    if (*bufferSize == 0) {
        return LOS_ERRNO_QUEUE_READSIZE_ISZERO;
    }

    if (timeOut != LOS_NO_WAIT) {
        if (OS_INT_ACTIVE) {
            return LOS_ERRNO_QUEUE_READ_IN_INTERRUPT;
        }
    }
    return LOS_OK;
}

static INLINE LITE_OS_SEC_TEXT UINT32 OsQueueWriteParameterCheck(UINT32 queueID, VOID *bufferAddr,
                                                                 UINT32 *bufferSize, UINT32 timeOut)
{
    if (queueID >= LOSCFG_BASE_IPC_QUEUE_LIMIT) {
        return LOS_ERRNO_QUEUE_INVALID;
    }

    if (bufferAddr == NULL) {
        return LOS_ERRNO_QUEUE_WRITE_PTR_NULL;
    }

    if (*bufferSize == 0) {
        return LOS_ERRNO_QUEUE_WRITESIZE_ISZERO;
    }

    if (timeOut != LOS_NO_WAIT) {
        if (OS_INT_ACTIVE) {
            return LOS_ERRNO_QUEUE_WRITE_IN_INTERRUPT;
        }
    }
    return LOS_OK;
}

static INLINE VOID OsQueueBufferOperate(LosQueueCB *queueCB, UINT32 operateType,
                                                                VOID *bufferAddr, UINT32 *bufferSize)
{
    UINT8 *queueNode = NULL;
    UINT32 msgDataSize;
    UINT16 queuePosion;
    errno_t rc;

    /* get the queue position */
    switch (OS_QUEUE_OPERATE_GET(operateType)) {
        case OS_QUEUE_READ_HEAD:
            queuePosion = queueCB->queueHead;
            ((queueCB->queueHead + 1) == queueCB->queueLen) ? (queueCB->queueHead = 0) : (queueCB->queueHead++);
            break;

        case OS_QUEUE_WRITE_HEAD:
            (queueCB->queueHead == 0) ? (queueCB->queueHead = (queueCB->queueLen - 1)) : (--queueCB->queueHead);
            queuePosion = queueCB->queueHead;
            break;

        case OS_QUEUE_WRITE_TAIL:
            queuePosion = queueCB->queueTail;
            ((queueCB->queueTail + 1) == queueCB->queueLen) ? (queueCB->queueTail = 0) : (queueCB->queueTail++);
            break;

        default:
            PRINT_ERR("invalid queue operate type!\n");
            return;
    }

    queueNode = &(queueCB->queue[(queuePosion * (queueCB->queueSize))]);

    if (OS_QUEUE_IS_POINT(operateType)) {
        if (OS_QUEUE_IS_READ(operateType)) {
            *(UINT32 *)bufferAddr = *(UINT32 *)(VOID *)queueNode;
        } else {
            *(UINT32 *)(VOID *)queueNode = *(UINT32 *)bufferAddr;  // change to pp when calling OsQueueOperate
        }
    } else {
        if (OS_QUEUE_IS_READ(operateType)) {
            msgDataSize = *((UINT32 *)(UINTPTR)((queueNode + queueCB->queueSize) - sizeof(UINT32)));
            rc = memcpy_s((VOID *)bufferAddr, *bufferSize, (VOID *)queueNode, msgDataSize);
            if (rc != EOK) {
                PRINT_ERR("%s[%d] memcpy failed, error type = %u\n", __FUNCTION__, __LINE__, rc);
                return;
            }

            *bufferSize = msgDataSize;
        } else {
            *((UINT32 *)(UINTPTR)((queueNode + queueCB->queueSize) - sizeof(UINT32))) = *bufferSize;
            rc = memcpy_s((VOID *)queueNode, queueCB->queueSize, (VOID *)bufferAddr, *bufferSize);
            if (rc != EOK) {
                PRINT_ERR("%s[%d] memcpy failed, error type = %u\n", __FUNCTION__, __LINE__, rc);
                return;
            }
        }
    }
}

static INLINE UINT32 OsQueueOperateParamCheck(const LosQueueCB *queueCB, UINT32 operateType, const UINT32 *bufferSize)
{
    if (queueCB->queueState == OS_QUEUE_UNUSED) {
        return LOS_ERRNO_QUEUE_NOT_CREATE;
    }

    if (OS_QUEUE_IS_READ(operateType) && (*bufferSize < (queueCB->queueSize - sizeof(UINT32)))) {
        return LOS_ERRNO_QUEUE_READ_SIZE_TOO_SMALL;
    } else if (OS_QUEUE_IS_WRITE(operateType) && (*bufferSize > (queueCB->queueSize - sizeof(UINT32)))) {
        return LOS_ERRNO_QUEUE_WRITE_SIZE_TOO_BIG;
    }

    return LOS_OK;
}

UINT32 OsQueueOperate(UINT32 queueID, UINT32 operateType, VOID *bufferAddr, UINT32 *bufferSize, UINT32 timeOut)
{
    LosQueueCB *queueCB = NULL;
    LosTaskCB *runTsk = NULL;
    LosTaskCB *resumedTask = NULL;
    UINT32 ret;
    UINT32 readWrite = OS_QUEUE_READ_WRITE_GET(operateType);
    UINT32 readWriteTmp = !readWrite;

    UINTPTR intSave = LOS_IntLock();

    queueCB = (LosQueueCB *)GET_QUEUE_HANDLE(queueID);
    ret = OsQueueOperateParamCheck(queueCB, operateType, bufferSize);
    if (ret != LOS_OK) {
        goto QUEUE_END;
    }

    if (queueCB->readWriteableCnt[readWrite] == 0) {
        if (timeOut == LOS_NO_WAIT) {
            ret = OS_QUEUE_IS_READ(operateType) ? LOS_ERRNO_QUEUE_ISEMPTY : LOS_ERRNO_QUEUE_ISFULL;
            goto QUEUE_END;
        }

        if (g_losTaskLock) {
            ret = LOS_ERRNO_QUEUE_PEND_IN_LOCK;
            goto QUEUE_END;
        }

        runTsk = (LosTaskCB *)g_losTask.runTask;
        OsTaskWait(&queueCB->readWriteList[readWrite], OS_TASK_STATUS_PEND_QUEUE, timeOut);
        LOS_IntRestore(intSave);
        LOS_Schedule();

        intSave = LOS_IntLock();
        if (runTsk->taskStatus & OS_TASK_STATUS_TIMEOUT) {
            runTsk->taskStatus &= (~OS_TASK_STATUS_TIMEOUT);
            ret = LOS_ERRNO_QUEUE_TIMEOUT;
            goto QUEUE_END;
        }
    } else {
        queueCB->readWriteableCnt[readWrite]--;
    }

    OsQueueBufferOperate(queueCB, operateType, bufferAddr, bufferSize);


    if (!LOS_ListEmpty(&queueCB->readWriteList[readWriteTmp])) {
        resumedTask = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&queueCB->readWriteList[readWriteTmp]));
        OsTaskWake(resumedTask, OS_TASK_STATUS_PEND_QUEUE);
        LOS_IntRestore(intSave);
        LOS_Schedule();
        return LOS_OK;
    } else {
        queueCB->readWriteableCnt[readWriteTmp]++;
    }

QUEUE_END:
    LOS_IntRestore(intSave);
    return ret;
}

LITE_OS_SEC_TEXT UINT32 LOS_QueueReadCopy(UINT32 queueID,
                                          VOID *bufferAddr,
                                          UINT32 *bufferSize,
                                          UINT32 timeOut)
{
    UINT32 ret;
    UINT32 operateType;

    ret = OsQueueReadParameterCheck(queueID, bufferAddr, bufferSize, timeOut);
    if (ret != LOS_OK) {
        return ret;
    }

    operateType = OS_QUEUE_OPERATE_TYPE(OS_QUEUE_READ, OS_QUEUE_HEAD, OS_QUEUE_NOT_POINT);
    return OsQueueOperate(queueID, operateType, bufferAddr, bufferSize, timeOut);
}

LITE_OS_SEC_TEXT UINT32 LOS_QueueWriteHeadCopy(UINT32 queueID,
                                               VOID *bufferAddr,
                                               UINT32 bufferSize,
                                               UINT32 timeOut)
{
    UINT32 ret;
    UINT32 operateType;

    ret = OsQueueWriteParameterCheck(queueID, bufferAddr, &bufferSize, timeOut);
    if (ret != LOS_OK) {
        return ret;
    }

    operateType = OS_QUEUE_OPERATE_TYPE(OS_QUEUE_WRITE, OS_QUEUE_HEAD, OS_QUEUE_NOT_POINT);
    return OsQueueOperate(queueID, operateType, bufferAddr, &bufferSize, timeOut);
}

LITE_OS_SEC_TEXT UINT32 LOS_QueueWriteCopy(UINT32 queueID,
                                           VOID *bufferAddr,
                                           UINT32 bufferSize,
                                           UINT32 timeOut)
{
    UINT32 ret;
    UINT32 operateType;

    ret = OsQueueWriteParameterCheck(queueID, bufferAddr, &bufferSize, timeOut);
    if (ret != LOS_OK) {
        return ret;
    }

    operateType = OS_QUEUE_OPERATE_TYPE(OS_QUEUE_WRITE, OS_QUEUE_TAIL, OS_QUEUE_NOT_POINT);
    return OsQueueOperate(queueID, operateType, bufferAddr, &bufferSize, timeOut);
}

LITE_OS_SEC_TEXT UINT32 LOS_QueueRead(UINT32 queueID, VOID *bufferAddr, UINT32 bufferSize, UINT32 timeOut)
{
    UINT32 ret;
    UINT32 operateType;

    ret = OsQueueReadParameterCheck(queueID, bufferAddr, &bufferSize, timeOut);
    if (ret != LOS_OK) {
        return ret;
    }

    operateType = OS_QUEUE_OPERATE_TYPE(OS_QUEUE_READ, OS_QUEUE_HEAD, OS_QUEUE_POINT);
    return OsQueueOperate(queueID, operateType, bufferAddr, &bufferSize, timeOut);
}

LITE_OS_SEC_TEXT UINT32 LOS_QueueWrite(UINT32 queueID, VOID *bufferAddr, UINT32 bufferSize, UINT32 timeOut)
{
    UINT32 ret;
    UINT32 operateType;
    UINT32 size = sizeof(UINT32 *);
    (VOID)bufferSize;

    ret = OsQueueWriteParameterCheck(queueID, bufferAddr, &size, timeOut);
    if (ret != LOS_OK) {
        return ret;
    }

    operateType = OS_QUEUE_OPERATE_TYPE(OS_QUEUE_WRITE, OS_QUEUE_TAIL, OS_QUEUE_POINT);
    return OsQueueOperate(queueID, operateType, &bufferAddr, &size, timeOut);
}

LITE_OS_SEC_TEXT UINT32 LOS_QueueWriteHead(UINT32 queueID,
                                           VOID *bufferAddr,
                                           UINT32 bufferSize,
                                           UINT32 timeOut)
{
    UINT32 size = sizeof(UINT32 *);
    (VOID)bufferSize;

    if (bufferAddr == NULL) {
        return LOS_ERRNO_QUEUE_WRITE_PTR_NULL;
    }

    return LOS_QueueWriteHeadCopy(queueID, &bufferAddr, size, timeOut);
}

/*****************************************************************************
 Function    : OsQueueMailAlloc
 Description : Mail allocate memory
 Input       : queueID   --- QueueID
             : mailPool  --- MailPool
             : timeOut   --- TimeOut
 Output      : None
 Return      : mem:pointer if success otherwise NULL
 *****************************************************************************/
LITE_OS_SEC_TEXT VOID *OsQueueMailAlloc(UINT32 queueID, VOID *mailPool, UINT32 timeOut)
{
    VOID *mem = (VOID *)NULL;
    UINTPTR intSave;
    LosQueueCB *queueCB = (LosQueueCB *)NULL;
    LosTaskCB *runTsk = (LosTaskCB *)NULL;

    if (queueID >= LOSCFG_BASE_IPC_QUEUE_LIMIT) {
        return NULL;
    }

    if (mailPool == NULL) {
        return NULL;
    }

    if (timeOut != LOS_NO_WAIT) {
        if (OS_INT_ACTIVE) {
            return NULL;
        }
    }

    intSave = LOS_IntLock();
    queueCB = GET_QUEUE_HANDLE(queueID);
    if (queueCB->queueState == OS_QUEUE_UNUSED) {
        goto END;
    }

    mem = LOS_MemboxAlloc(mailPool);
    if (mem == NULL) {
        if (timeOut == LOS_NO_WAIT) {
            goto END;
        }

        runTsk = (LosTaskCB *)g_losTask.runTask;
        OsTaskWait(&queueCB->memList, OS_TASK_STATUS_PEND_QUEUE, timeOut);
        LOS_IntRestore(intSave);
        LOS_Schedule();

        intSave = LOS_IntLock();
        if (runTsk->taskStatus & OS_TASK_STATUS_TIMEOUT) {
            runTsk->taskStatus &= (~OS_TASK_STATUS_TIMEOUT);
            goto END;
        } else {
            /* When enters the current branch, means the current task already got a available membox,
             * so the runTsk->msg can not be NULL.
             */
            mem = runTsk->msg;
            runTsk->msg = NULL;
        }
    }

END:
    LOS_IntRestore(intSave);
    return mem;
}

/*****************************************************************************
 Function    : OsQueueMailFree
 Description : Mail free memory
 Input       : queueID   --- QueueID
             : mailPool  --- MailPool
             : mailMem   --- MailMem
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT UINT32 OsQueueMailFree(UINT32 queueID, VOID *mailPool, VOID *mailMem)
{
    VOID *mem = (VOID *)NULL;
    UINTPTR intSave;
    LosQueueCB *queueCB = (LosQueueCB *)NULL;
    LosTaskCB *resumedTask = (LosTaskCB *)NULL;

    if (queueID >= LOSCFG_BASE_IPC_QUEUE_LIMIT) {
        return LOS_ERRNO_QUEUE_MAIL_HANDLE_INVALID;
    }

    if (mailPool == NULL) {
        return LOS_ERRNO_QUEUE_MAIL_PTR_INVALID;
    }

    intSave = LOS_IntLock();

    if (LOS_MemboxFree(mailPool, mailMem)) {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_QUEUE_MAIL_FREE_ERROR;
    }

    queueCB = GET_QUEUE_HANDLE(queueID);
    if (queueCB->queueState == OS_QUEUE_UNUSED) {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_QUEUE_NOT_CREATE;
    }

    if (!LOS_ListEmpty(&queueCB->memList)) {
        resumedTask = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&queueCB->memList));
        OsTaskWake(resumedTask, OS_TASK_STATUS_PEND_QUEUE);
        mem = LOS_MemboxAlloc(mailPool);
        if (mem == NULL) {
            LOS_IntRestore(intSave);
            return LOS_ERRNO_QUEUE_NO_MEMORY;
        }
        resumedTask->msg = mem;
        LOS_IntRestore(intSave);
        LOS_Schedule();
    } else {
        LOS_IntRestore(intSave);
    }
    return LOS_OK;
}

/*****************************************************************************
 Function    : LOS_QueueDelete
 Description : Delete a queue
 Input       : queueID   --- QueueID
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_QueueDelete(UINT32 queueID)
{
    LosQueueCB *queueCB = NULL;
    UINT8 *queue = NULL;
    UINTPTR intSave;
    UINT32 ret;

    if (queueID >= LOSCFG_BASE_IPC_QUEUE_LIMIT) {
        return LOS_ERRNO_QUEUE_NOT_FOUND;
    }

    intSave = LOS_IntLock();
    queueCB = (LosQueueCB *)GET_QUEUE_HANDLE(queueID);
    if (queueCB->queueState == OS_QUEUE_UNUSED) {
        ret = LOS_ERRNO_QUEUE_NOT_CREATE;
        goto QUEUE_END;
    }

    if (!LOS_ListEmpty(&queueCB->readWriteList[OS_QUEUE_READ])) {
        ret = LOS_ERRNO_QUEUE_IN_TSKUSE;
        goto QUEUE_END;
    }

    if (!LOS_ListEmpty(&queueCB->readWriteList[OS_QUEUE_WRITE])) {
        ret = LOS_ERRNO_QUEUE_IN_TSKUSE;
        goto QUEUE_END;
    }

    if (!LOS_ListEmpty(&queueCB->memList)) {
        ret = LOS_ERRNO_QUEUE_IN_TSKUSE;
        goto QUEUE_END;
    }

    if ((queueCB->readWriteableCnt[OS_QUEUE_WRITE] + queueCB->readWriteableCnt[OS_QUEUE_READ]) !=
        queueCB->queueLen) {
        ret = LOS_ERRNO_QUEUE_IN_TSKWRITE;
        goto QUEUE_END;
    }

    queue = queueCB->queue;
    queueCB->queue = (UINT8 *)NULL;
    queueCB->queueState = OS_QUEUE_UNUSED;
    LOS_ListAdd(&g_freeQueueList, &queueCB->readWriteList[OS_QUEUE_WRITE]);
    LOS_IntRestore(intSave);

    ret = LOS_MemFree(m_aucSysMem0, (VOID *)queue);
    return ret;

QUEUE_END:
    LOS_IntRestore(intSave);
    return ret;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_QueueInfoGet(UINT32 queueID, QUEUE_INFO_S *queueInfo)
{
    UINTPTR intSave;
    UINT32 ret = LOS_OK;
    LosQueueCB *queueCB = NULL;
    LosTaskCB *tskCB = NULL;

    if (queueInfo == NULL) {
        return LOS_ERRNO_QUEUE_PTR_NULL;
    }

    if (queueID >= LOSCFG_BASE_IPC_QUEUE_LIMIT) {
        return LOS_ERRNO_QUEUE_INVALID;
    }

    (VOID)memset_s((VOID *)queueInfo, sizeof(QUEUE_INFO_S), 0, sizeof(QUEUE_INFO_S));
    intSave = LOS_IntLock();

    queueCB = (LosQueueCB *)GET_QUEUE_HANDLE(queueID);

    if (queueCB->queueState == OS_QUEUE_UNUSED) {
        ret = LOS_ERRNO_QUEUE_NOT_CREATE;
        goto QUEUE_END;
    }

    queueInfo->queueID = queueID;
    queueInfo->queueLen = queueCB->queueLen;
    queueInfo->queueSize = queueCB->queueSize;
    queueInfo->queueHead = queueCB->queueHead;
    queueInfo->queueTail = queueCB->queueTail;
    queueInfo->readableCnt = queueCB->readWriteableCnt[OS_QUEUE_READ];
    queueInfo->writableCnt = queueCB->readWriteableCnt[OS_QUEUE_WRITE];

    LOS_DL_LIST_FOR_EACH_ENTRY(tskCB, &queueCB->readWriteList[OS_QUEUE_READ], LosTaskCB, pendList) {
        queueInfo->waitReadTask |= (1 << tskCB->taskID);
    }

    LOS_DL_LIST_FOR_EACH_ENTRY(tskCB, &queueCB->readWriteList[OS_QUEUE_WRITE], LosTaskCB, pendList) {
        queueInfo->waitWriteTask |= (1 << tskCB->taskID);
    }

    LOS_DL_LIST_FOR_EACH_ENTRY(tskCB, &queueCB->memList, LosTaskCB, pendList) {
        queueInfo->waitMemTask |= (1 << tskCB->taskID);
    }

QUEUE_END:
    LOS_IntRestore(intSave);
    return ret;
}

#endif /* (LOSCFG_BASE_IPC_QUEUE == YES) */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
