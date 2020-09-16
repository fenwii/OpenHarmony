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
#include "los_err_pri.h"
#include "los_memory_pri.h"
#include "los_priqueue_pri.h"
#include "los_task_pri.h"
#if (LOSCFG_PLATFORM_EXC == YES)
#include "los_exc.h"
#endif
#include "los_hw.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if (LOSCFG_BASE_IPC_MUX == YES)

LITE_OS_SEC_BSS       LosMuxCB*   g_allMux = NULL;
LITE_OS_SEC_DATA_INIT LOS_DL_LIST g_unusedMuxList;

/*****************************************************************************
 Funtion      : OsMuxInit
 Description  : Initializes the mutex
 Input        : None
 Output       : None
 Return       : LOS_OK on success ,or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsMuxInit(VOID)
{
    LosMuxCB *muxNode = NULL;
    UINT32 index;

    LOS_ListInit(&g_unusedMuxList);

    if (LOSCFG_BASE_IPC_MUX_LIMIT == 0) {
        return LOS_ERRNO_MUX_MAXNUM_ZERO;
    }

    g_allMux = (LosMuxCB *)LOS_MemAlloc(m_aucSysMem0, (LOSCFG_BASE_IPC_MUX_LIMIT * sizeof(LosMuxCB)));
    if (g_allMux == NULL) {
        return LOS_ERRNO_MUX_NO_MEMORY;
    }

    for (index = 0; index < LOSCFG_BASE_IPC_MUX_LIMIT; index++) {
        muxNode = ((LosMuxCB *)g_allMux) + index;
        muxNode->muxID = index;
        muxNode->muxStat = OS_MUX_UNUSED;
        LOS_ListTailInsert(&g_unusedMuxList, &muxNode->muxList);
    }
    return LOS_OK;
}

/*****************************************************************************
 Function     : LOS_MuxCreate
 Description  : Create a mutex
 Input        : None
 Output       : muxHandle ------ Mutex operation handle
 Return       : LOS_OK on success ,or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_MuxCreate(UINT32 *muxHandle)
{
    UINT32 intSave;
    LosMuxCB *muxCreated = NULL;
    LOS_DL_LIST *unusedMux = NULL;
    UINT32 errNo;
    UINT32 errLine;

    if (muxHandle == NULL) {
        return LOS_ERRNO_MUX_PTR_NULL;
    }

    intSave = LOS_IntLock();
    if (LOS_ListEmpty(&g_unusedMuxList)) {
        LOS_IntRestore(intSave);
        OS_GOTO_ERR_HANDLER(LOS_ERRNO_MUX_ALL_BUSY);
    }

    unusedMux = LOS_DL_LIST_FIRST(&(g_unusedMuxList));
    LOS_ListDelete(unusedMux);
    muxCreated = (GET_MUX_LIST(unusedMux));
    muxCreated->muxCount = 0;
    muxCreated->muxStat = OS_MUX_USED;
    muxCreated->priority = 0;
    muxCreated->owner = (LosTaskCB *)NULL;
    LOS_ListInit(&muxCreated->muxList);
    *muxHandle = (UINT32)muxCreated->muxID;
    LOS_IntRestore(intSave);
    return LOS_OK;
ERR_HANDLER:
    OS_RETURN_ERROR_P2(errLine, errNo);
}

/*****************************************************************************
 Function     : LOS_MuxDelete
 Description  : Delete a mutex
 Input        : muxHandle ------Mutex operation handle
 Output       : None
 Return       : LOS_OK on success ,or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_MuxDelete(UINT32 muxHandle)
{
    UINT32 intSave;
    LosMuxCB *muxDeleted = NULL;
    UINT32 errNo;
    UINT32 errLine;

    if (muxHandle >= (UINT32)LOSCFG_BASE_IPC_MUX_LIMIT) {
        OS_GOTO_ERR_HANDLER(LOS_ERRNO_MUX_INVALID);
    }

    muxDeleted = GET_MUX(muxHandle);
    intSave = LOS_IntLock();
    if (muxDeleted->muxStat == OS_MUX_UNUSED) {
        LOS_IntRestore(intSave);
        OS_GOTO_ERR_HANDLER(LOS_ERRNO_MUX_INVALID);
    }

    if ((!LOS_ListEmpty(&muxDeleted->muxList)) || muxDeleted->muxCount) {
        LOS_IntRestore(intSave);
        OS_GOTO_ERR_HANDLER(LOS_ERRNO_MUX_PENDED);
    }

    LOS_ListAdd(&g_unusedMuxList, &muxDeleted->muxList);
    muxDeleted->muxStat = OS_MUX_UNUSED;

    LOS_IntRestore(intSave);

    return LOS_OK;
ERR_HANDLER:
    OS_RETURN_ERROR_P2(errLine, errNo);
}

STATIC_INLINE UINT32 OsMuxValidCheck(LosMuxCB *muxPended)
{
    if (muxPended->muxStat == OS_MUX_UNUSED) {
        return LOS_ERRNO_MUX_INVALID;
    }

    if (OS_INT_ACTIVE) {
        return LOS_ERRNO_MUX_PEND_INTERR;
    }

    if (g_losTaskLock) {
        PRINT_ERR("!!!LOS_ERRNO_MUX_PEND_IN_LOCK!!!\n");
#if (LOSCFG_PLATFORM_EXC == YES)
        OsBackTrace();
#endif
        return LOS_ERRNO_MUX_PEND_IN_LOCK;
    }

    return LOS_OK;
}

/*****************************************************************************
 Function     : LOS_MuxPend
 Description  : Specify the mutex P operation
 Input        : muxHandle ------ Mutex operation handleone
              : timeOut   ------- waiting time
 Output       : None
 Return       : LOS_OK on success ,or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_MuxPend(UINT32 muxHandle, UINT32 timeout)
{
    UINT32 intSave;
    LosMuxCB *muxPended = NULL;
    UINT32 retErr;
    LosTaskCB *runningTask = NULL;

    if (muxHandle >= (UINT32)LOSCFG_BASE_IPC_MUX_LIMIT) {
        OS_RETURN_ERROR(LOS_ERRNO_MUX_INVALID);
    }

    muxPended = GET_MUX(muxHandle);
    intSave = LOS_IntLock();
    retErr = OsMuxValidCheck(muxPended);
    if (retErr) {
        goto ERROR_MUX_PEND;
    }

    runningTask = (LosTaskCB *)g_losTask.runTask;
    if (muxPended->muxCount == 0) {
        muxPended->muxCount++;
        muxPended->owner = runningTask;
        muxPended->priority = runningTask->priority;
        LOS_IntRestore(intSave);
        return LOS_OK;
    }

    if (muxPended->owner == runningTask) {
        muxPended->muxCount++;
        LOS_IntRestore(intSave);
        return LOS_OK;
    }

    if (!timeout) {
        retErr = LOS_ERRNO_MUX_UNAVAILABLE;
        goto ERROR_MUX_PEND;
    }

    runningTask->taskMux = (VOID *)muxPended;

    if (muxPended->owner->priority > runningTask->priority) {
        OsTaskPriModify(muxPended->owner, runningTask->priority);
    }

    OsTaskWait(&muxPended->muxList, OS_TASK_STATUS_PEND, timeout);

    LOS_IntRestore(intSave);
    LOS_Schedule();

    if (runningTask->taskStatus & OS_TASK_STATUS_TIMEOUT) {
        intSave = LOS_IntLock();
        runningTask->taskStatus &= (~OS_TASK_STATUS_TIMEOUT);
        retErr = LOS_ERRNO_MUX_TIMEOUT;
        goto ERROR_MUX_PEND;
    }

    return LOS_OK;

ERROR_MUX_PEND:
    LOS_IntRestore(intSave);
    OS_RETURN_ERROR(retErr);
}

/*****************************************************************************
 Function     : LOS_MuxPost
 Description  : Specify the mutex V operation,
 Input        : muxHandle ------ Mutex operation handle
 Output       : None
 Return       : LOS_OK on success ,or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_MuxPost(UINT32 muxHandle)
{
    UINT32 intSave;
    LosMuxCB *muxPosted = GET_MUX(muxHandle);
    LosTaskCB *resumedTask = NULL;
    LosTaskCB *runningTask = NULL;

    intSave = LOS_IntLock();

    if ((muxHandle >= (UINT32)LOSCFG_BASE_IPC_MUX_LIMIT) ||
        (muxPosted->muxStat == OS_MUX_UNUSED)) {
        LOS_IntRestore(intSave);
        OS_RETURN_ERROR(LOS_ERRNO_MUX_INVALID);
    }

    runningTask = (LosTaskCB *)g_losTask.runTask;
    if ((muxPosted->muxCount == 0) || (muxPosted->owner != runningTask)) {
        LOS_IntRestore(intSave);
        OS_RETURN_ERROR(LOS_ERRNO_MUX_INVALID);
    }

    if (--(muxPosted->muxCount) != 0) {
        LOS_IntRestore(intSave);
        return LOS_OK;
    }

    if ((muxPosted->owner->priority) != muxPosted->priority) {
        OsTaskPriModify(muxPosted->owner, muxPosted->priority);
    }

    if (!LOS_ListEmpty(&muxPosted->muxList)) {
        resumedTask = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(muxPosted->muxList)));

        muxPosted->muxCount = 1;
        muxPosted->owner = resumedTask;
        muxPosted->priority = resumedTask->priority;
        resumedTask->taskMux = NULL;

        OsTaskWake(resumedTask, OS_TASK_STATUS_PEND);

        LOS_IntRestore(intSave);
        LOS_Schedule();
    } else {
        LOS_IntRestore(intSave);
    }

    return LOS_OK;
}
#endif /* (LOSCFG_BASE_IPC_MUX == YES) */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
