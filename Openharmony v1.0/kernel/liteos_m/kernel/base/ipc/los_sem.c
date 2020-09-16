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

#include "los_sem_pri.h"
#include "los_base_pri.h"
#include "los_err_pri.h"
#include "los_memory_pri.h"
#include "los_priqueue_pri.h"
#include "los_sys_pri.h"
#include "los_task_pri.h"
#if (LOSCFG_PLATFORM_EXC == YES)
#include "los_exc.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if (LOSCFG_BASE_IPC_SEM == YES)

LITE_OS_SEC_DATA_INIT LOS_DL_LIST g_unusedSemList;
LITE_OS_SEC_BSS LosSemCB *g_allSem = NULL;

/*****************************************************************************
 Function     : OsSemInit
 Description  : Initialize the  Semaphore doubly linked list
 Input        : None
 Output       : None
 Return       : LOS_OK on success, or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsSemInit(VOID)
{
    LosSemCB *semNode = NULL;
    UINT16 index;

    LOS_ListInit(&g_unusedSemList);

    if (LOSCFG_BASE_IPC_SEM_LIMIT == 0) {
        return LOS_ERRNO_SEM_MAXNUM_ZERO;
    }

    g_allSem = (LosSemCB *)LOS_MemAlloc(m_aucSysMem0, (LOSCFG_BASE_IPC_SEM_LIMIT * sizeof(LosSemCB)));
    if (g_allSem == NULL) {
        return LOS_ERRNO_SEM_NO_MEMORY;
    }

    /* Connect all the ECBs in a doubly linked list. */
    for (index = 0; index < LOSCFG_BASE_IPC_SEM_LIMIT; index++) {
        semNode = ((LosSemCB *)g_allSem) + index;
        semNode->semID = index;
        semNode->semStat = OS_SEM_UNUSED;
        LOS_ListTailInsert(&g_unusedSemList, &semNode->semList);
    }
    return LOS_OK;
}

/*****************************************************************************
 Function     : OsSemCreate
 Description  : create the  Semaphore
 Input        : count      --- Semaphore count
              : maxCount   --- Max semaphore count for check
 Output       : semHandle  --- Index of semaphore
 Return       : LOS_OK on success, or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsSemCreate(UINT16 count, UINT16 maxCount, UINT32 *semHandle)
{
    UINT32 intSave;
    LosSemCB *semCreated = NULL;
    LOS_DL_LIST *unusedSem = NULL;
    UINT32 errNo;
    UINT32 errLine;

    if (semHandle == NULL) {
        return LOS_ERRNO_SEM_PTR_NULL;
    }

    if (count > maxCount) {
        OS_GOTO_ERR_HANDLER(LOS_ERRNO_SEM_OVERFLOW);
    }

    intSave = LOS_IntLock();

    if (LOS_ListEmpty(&g_unusedSemList)) {
        LOS_IntRestore(intSave);
        OS_GOTO_ERR_HANDLER(LOS_ERRNO_SEM_ALL_BUSY);
    }

    unusedSem = LOS_DL_LIST_FIRST(&(g_unusedSemList));
    LOS_ListDelete(unusedSem);
    semCreated = (GET_SEM_LIST(unusedSem));
    semCreated->semCount = count;
    semCreated->semStat = OS_SEM_USED;
    semCreated->maxSemCount = maxCount;
    LOS_ListInit(&semCreated->semList);
    *semHandle = (UINT32)semCreated->semID;
    LOS_IntRestore(intSave);
    return LOS_OK;

ERR_HANDLER:
    OS_RETURN_ERROR_P2(errLine, errNo);
}

/*****************************************************************************
 Function     : LOS_SemCreate
 Description  : Create a semaphore
 Input        : count--------- semaphore count
 Output       : semHandle-----Index of semaphore
 Return       : LOS_OK on success, or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_SemCreate(UINT16 count, UINT32 *semHandle)
{
    return OsSemCreate(count, OS_SEM_COUNTING_MAX_COUNT, semHandle);
}

/*****************************************************************************
 Function     : LOS_BinarySemCreate
 Description  : Create a binary semaphore
 Input        : count--------- semaphore count
 Output       : semHandle-----Index of semaphore
 Return       : LOS_OK on success, or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_BinarySemCreate(UINT16 count, UINT32 *semHandle)
{
    return OsSemCreate(count, OS_SEM_BINARY_MAX_COUNT, semHandle);
}

/*****************************************************************************
 Function     : LOS_SemDelete
 Description  : Delete a semaphore
 Input        : semHandle--------- semaphore operation handle
 Output       : None
 Return       : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_SemDelete(UINT32 semHandle)
{
    UINT32 intSave;
    LosSemCB *semDeleted = NULL;
    UINT32 errNo;
    UINT32 errLine;

    if (semHandle >= (UINT32)LOSCFG_BASE_IPC_SEM_LIMIT) {
        OS_GOTO_ERR_HANDLER(LOS_ERRNO_SEM_INVALID);
    }

    semDeleted = GET_SEM(semHandle);
    intSave = LOS_IntLock();
    if (semDeleted->semStat == OS_SEM_UNUSED) {
        LOS_IntRestore(intSave);
        OS_GOTO_ERR_HANDLER(LOS_ERRNO_SEM_INVALID);
    }

    if (!LOS_ListEmpty(&semDeleted->semList)) {
        LOS_IntRestore(intSave);
        OS_GOTO_ERR_HANDLER(LOS_ERRNO_SEM_PENDED);
    }

    LOS_ListAdd(&g_unusedSemList, &semDeleted->semList);
    semDeleted->semStat = OS_SEM_UNUSED;
    LOS_IntRestore(intSave);
    return LOS_OK;
ERR_HANDLER:
    OS_RETURN_ERROR_P2(errLine, errNo);
}

STATIC_INLINE UINT32 OsSemValidCheck(LosSemCB *semPended)
{
    if (semPended->semStat == OS_SEM_UNUSED) {
        return LOS_ERRNO_SEM_INVALID;
    }

    if (OS_INT_ACTIVE) {
        PRINT_ERR("!!!LOS_ERRNO_SEM_PEND_INTERR!!!\n");
#if (LOSCFG_PLATFORM_EXC == YES)
        OsBackTrace();
#endif
        return LOS_ERRNO_SEM_PEND_INTERR;
    }

    if (g_losTaskLock) {
        PRINT_ERR("!!!LOS_ERRNO_SEM_PEND_IN_LOCK!!!\n");
#if (LOSCFG_PLATFORM_EXC == YES)
        OsBackTrace();
#endif
        return LOS_ERRNO_SEM_PEND_IN_LOCK;
    }

    return LOS_OK;
}

/*****************************************************************************
 Function     : LOS_SemPend
 Description  : Specified semaphore P operation
 Input        : semHandle --------- semaphore operation handle
              : timeout   --------- waitting time
 Output       : None
 Return       : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_SemPend(UINT32 semHandle, UINT32 timeout)
{
    UINT32 intSave;
    LosSemCB *semPended = NULL;
    UINT32 retErr;
    LosTaskCB *runningTask = NULL;

    if (semHandle >= (UINT32)LOSCFG_BASE_IPC_SEM_LIMIT) {
        OS_RETURN_ERROR(LOS_ERRNO_SEM_INVALID);
    }

    semPended = GET_SEM(semHandle);
    intSave = LOS_IntLock();

    retErr = OsSemValidCheck(semPended);
    if (retErr) {
        goto ERROR_SEM_PEND;
    }

    if (semPended->semCount > 0) {
        semPended->semCount--;
        LOS_IntRestore(intSave);
        return LOS_OK;
    }

    if (!timeout) {
        retErr = LOS_ERRNO_SEM_UNAVAILABLE;
        goto ERROR_SEM_PEND;
    }

    runningTask = (LosTaskCB *)g_losTask.runTask;
    runningTask->taskSem = (VOID *)semPended;
    OsTaskWait(&semPended->semList, OS_TASK_STATUS_PEND, timeout);
    LOS_IntRestore(intSave);
    LOS_Schedule();

    if (runningTask->taskStatus & OS_TASK_STATUS_TIMEOUT) {
        intSave = LOS_IntLock();
        runningTask->taskStatus &= (~OS_TASK_STATUS_TIMEOUT);
        retErr = LOS_ERRNO_SEM_TIMEOUT;
        goto ERROR_SEM_PEND;
    }

    return LOS_OK;

ERROR_SEM_PEND:
    LOS_IntRestore(intSave);
    OS_RETURN_ERROR(retErr);
}

/*****************************************************************************
 Function     : LOS_SemPost
 Description  : Specified semaphore V operation
 Input        : semHandle--------- semaphore operation handle
 Output       : None
 Return       : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_SemPost(UINT32 semHandle)
{
    UINT32 intSave;
    LosSemCB *semPosted = GET_SEM(semHandle);
    LosTaskCB *resumedTask = NULL;

    if (semHandle >= LOSCFG_BASE_IPC_SEM_LIMIT) {
        return LOS_ERRNO_SEM_INVALID;
    }

    intSave = LOS_IntLock();

    if (semPosted->semStat == OS_SEM_UNUSED) {
        LOS_IntRestore(intSave);
        OS_RETURN_ERROR(LOS_ERRNO_SEM_INVALID);
    }

    if (semPosted->maxSemCount == semPosted->semCount) {
        LOS_IntRestore(intSave);
        OS_RETURN_ERROR(LOS_ERRNO_SEM_OVERFLOW);
    }
    if (!LOS_ListEmpty(&semPosted->semList)) {
        resumedTask = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(semPosted->semList)));
        resumedTask->taskSem = NULL;
        OsTaskWake(resumedTask, OS_TASK_STATUS_PEND);

        LOS_IntRestore(intSave);
        LOS_Schedule();
    } else {
        semPosted->semCount++;
        LOS_IntRestore(intSave);
    }

    return LOS_OK;
}

#endif /* (LOSCFG_BASE_IPC_SEM == YES) */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
