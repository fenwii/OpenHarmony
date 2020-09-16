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

#include "los_swtmr_pri.h"
#include "los_sortlink_pri.h"
#include "los_queue_pri.h"
#include "los_task_pri.h"
#include "los_process_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#if (LOSCFG_BASE_CORE_SWTMR == YES)
#if (LOSCFG_BASE_CORE_SWTMR_LIMIT <= 0)
#error "swtmr maxnum cannot be zero"
#endif /* LOSCFG_BASE_CORE_SWTMR_LIMIT <= 0 */

LITE_OS_SEC_BSS SWTMR_CTRL_S    *g_swtmrCBArray = NULL;     /* First address in Timer memory space */
LITE_OS_SEC_BSS UINT8           *g_swtmrHandlerPool = NULL; /* Pool of Swtmr Handler */
LITE_OS_SEC_BSS LOS_DL_LIST     g_swtmrFreeList;            /* Free list of Software Timer */

/* spinlock for swtmr module, only available on SMP mode */
LITE_OS_SEC_BSS  SPIN_LOCK_INIT(g_swtmrSpin);
#define SWTMR_LOCK(state)       LOS_SpinLockSave(&g_swtmrSpin, &(state))
#define SWTMR_UNLOCK(state)     LOS_SpinUnlockRestore(&g_swtmrSpin, (state))

LITE_OS_SEC_TEXT VOID OsSwtmrTask(VOID)
{
    SwtmrHandlerItemPtr swtmrHandlePtr = NULL;
    SwtmrHandlerItem swtmrHandle;
    UINT32 ret, swtmrHandlerQueue;

    swtmrHandlerQueue = OsPercpuGet()->swtmrHandlerQueue;
    for (;;) {
        ret = LOS_QueueRead(swtmrHandlerQueue, &swtmrHandlePtr, sizeof(CHAR *), LOS_WAIT_FOREVER);
        if ((ret == LOS_OK) && (swtmrHandlePtr != NULL)) {
            swtmrHandle.handler = swtmrHandlePtr->handler;
            swtmrHandle.arg = swtmrHandlePtr->arg;
            (VOID)LOS_MemboxFree(g_swtmrHandlerPool, swtmrHandlePtr);
            if (swtmrHandle.handler != NULL) {
                swtmrHandle.handler(swtmrHandle.arg);
            }
        }
    }
}

LITE_OS_SEC_TEXT_INIT UINT32 OsSwtmrTaskCreate(VOID)
{
    UINT32 ret, swtmrTaskID;
    TSK_INIT_PARAM_S swtmrTask;
    UINT32 cpuid = ArchCurrCpuid();

    (VOID)memset_s(&swtmrTask, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    swtmrTask.pfnTaskEntry = (TSK_ENTRY_FUNC)OsSwtmrTask;
    swtmrTask.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    swtmrTask.pcName = "Swt_Task";
    swtmrTask.usTaskPrio = 0;
    swtmrTask.uwResved = LOS_TASK_STATUS_DETACHED;
#if (LOSCFG_KERNEL_SMP == YES)
    swtmrTask.usCpuAffiMask   = CPUID_TO_AFFI_MASK(cpuid);
#endif
    ret = LOS_TaskCreate(&swtmrTaskID, &swtmrTask);
    if (ret == LOS_OK) {
        g_percpu[cpuid].swtmrTaskID = swtmrTaskID;
        OS_TCB_FROM_TID(swtmrTaskID)->taskStatus |= OS_TASK_FLAG_SYSTEM_TASK;
    }

    return ret;
}

LITE_OS_SEC_TEXT_INIT VOID OsSwtmrRecycle(UINT32 processID)
{
    for (UINT16 index = 0; index < LOSCFG_BASE_CORE_SWTMR_LIMIT; index++) {
        if (g_swtmrCBArray[index].uwOwnerPid == processID) {
            LOS_SwtmrDelete(index);
        }
    }
}

LITE_OS_SEC_TEXT_INIT UINT32 OsSwtmrInit(VOID)
{
    UINT32 size;
    UINT16 index;
    UINT32 ret;
    SWTMR_CTRL_S *swtmr = NULL;
    UINT32 swtmrHandlePoolSize;
    UINT32 cpuid = ArchCurrCpuid();
    if (cpuid == 0) {
        size = sizeof(SWTMR_CTRL_S) * LOSCFG_BASE_CORE_SWTMR_LIMIT;
        swtmr = (SWTMR_CTRL_S *)LOS_MemAlloc(m_aucSysMem0, size); /* system resident resource */
        if (swtmr == NULL) {
            return LOS_ERRNO_SWTMR_NO_MEMORY;
        }

        (VOID)memset_s(swtmr, size, 0, size);
        g_swtmrCBArray = swtmr;
        LOS_ListInit(&g_swtmrFreeList);
        for (index = 0; index < LOSCFG_BASE_CORE_SWTMR_LIMIT; index++, swtmr++) {
            swtmr->usTimerID = index;
            LOS_ListTailInsert(&g_swtmrFreeList, &swtmr->stSortList.sortLinkNode);
        }

        swtmrHandlePoolSize = LOS_MEMBOX_SIZE(sizeof(SwtmrHandlerItem), OS_SWTMR_HANDLE_QUEUE_SIZE);

        g_swtmrHandlerPool = (UINT8 *)LOS_MemAlloc(m_aucSysMem1, swtmrHandlePoolSize); /* system resident resource */
        if (g_swtmrHandlerPool == NULL) {
            return LOS_ERRNO_SWTMR_NO_MEMORY;
        }

        ret = LOS_MemboxInit(g_swtmrHandlerPool, swtmrHandlePoolSize, sizeof(SwtmrHandlerItem));
        if (ret != LOS_OK) {
            return LOS_ERRNO_SWTMR_HANDLER_POOL_NO_MEM;
        }
    }

    ret = LOS_QueueCreate(NULL, OS_SWTMR_HANDLE_QUEUE_SIZE, &g_percpu[cpuid].swtmrHandlerQueue, 0, sizeof(CHAR *));
    if (ret != LOS_OK) {
        return LOS_ERRNO_SWTMR_QUEUE_CREATE_FAILED;
    }

    ret = OsSwtmrTaskCreate();
    if (ret != LOS_OK) {
        return LOS_ERRNO_SWTMR_TASK_CREATE_FAILED;
    }

    ret = OsSortLinkInit(&g_percpu[cpuid].swtmrSortLink);
    if (ret != LOS_OK) {
        return LOS_ERRNO_SWTMR_SORTLINK_CREATE_FAILED;
    }

    return LOS_OK;
}

/*
 * Description: Start Software Timer
 * Input      : swtmr --- Need to start software timer
 */
LITE_OS_SEC_TEXT VOID OsSwtmrStart(SWTMR_CTRL_S *swtmr)
{
    if ((swtmr->ucOverrun == 0) && ((swtmr->ucMode == LOS_SWTMR_MODE_ONCE) ||
        (swtmr->ucMode == LOS_SWTMR_MODE_OPP) ||
        (swtmr->ucMode == LOS_SWTMR_MODE_NO_SELFDELETE))) {
        SET_SORTLIST_VALUE(&(swtmr->stSortList), swtmr->uwExpiry);
    } else {
        SET_SORTLIST_VALUE(&(swtmr->stSortList), swtmr->uwInterval);
    }

    OsAdd2SortLink(&OsPercpuGet()->swtmrSortLink, &swtmr->stSortList);

    swtmr->ucState = OS_SWTMR_STATUS_TICKING;

#if (LOSCFG_KERNEL_SMP == YES)
    swtmr->uwCpuid = ArchCurrCpuid();
#endif

    return;
}

/*
 * Description: Delete Software Timer
 * Input      : swtmr --- Need to delete software timer, When using, Ensure that it can't be NULL.
 */
STATIC INLINE VOID OsSwtmrDelete(SWTMR_CTRL_S *swtmr)
{
    /* insert to free list */
    LOS_ListTailInsert(&g_swtmrFreeList, &swtmr->stSortList.sortLinkNode);
    swtmr->ucState = OS_SWTMR_STATUS_UNUSED;
    swtmr->uwOwnerPid = 0;
}

/*
 * Description: Tick interrupt interface module of software timer
 * Return     : LOS_OK on success or error code on failure
 */
LITE_OS_SEC_TEXT VOID OsSwtmrScan(VOID)
{
    SortLinkList *sortList = NULL;
    SWTMR_CTRL_S *swtmr = NULL;
    SwtmrHandlerItemPtr swtmrHandler = NULL;
    LOS_DL_LIST *listObject = NULL;
    SortLinkAttribute* swtmrSortLink = &OsPercpuGet()->swtmrSortLink;

    swtmrSortLink->cursor = (swtmrSortLink->cursor + 1) & OS_TSK_SORTLINK_MASK;
    listObject = swtmrSortLink->sortLink + swtmrSortLink->cursor;

    /*
     * it needs to be carefully coped with, since the swtmr is in specific sortlink
     * while other cores still has the chance to process it, like stop the timer.
     */
    LOS_SpinLock(&g_swtmrSpin);

    if (LOS_ListEmpty(listObject)) {
        LOS_SpinUnlock(&g_swtmrSpin);
        return;
    }
    sortList = LOS_DL_LIST_ENTRY(listObject->pstNext, SortLinkList, sortLinkNode);
    ROLLNUM_DEC(sortList->idxRollNum);

    while (ROLLNUM(sortList->idxRollNum) == 0) {
        sortList = LOS_DL_LIST_ENTRY(listObject->pstNext, SortLinkList, sortLinkNode);
        LOS_ListDelete(&sortList->sortLinkNode);
        swtmr = LOS_DL_LIST_ENTRY(sortList, SWTMR_CTRL_S, stSortList);

        swtmrHandler = (SwtmrHandlerItemPtr)LOS_MemboxAlloc(g_swtmrHandlerPool);
        if (swtmrHandler != NULL) {
            swtmrHandler->handler = swtmr->pfnHandler;
            swtmrHandler->arg = swtmr->uwArg;

            if (LOS_QueueWrite(OsPercpuGet()->swtmrHandlerQueue, swtmrHandler, sizeof(CHAR *), LOS_NO_WAIT)) {
                (VOID)LOS_MemboxFree(g_swtmrHandlerPool, swtmrHandler);
            }
        }

        if (swtmr->ucMode == LOS_SWTMR_MODE_ONCE) {
            OsSwtmrDelete(swtmr);

            if (swtmr->usTimerID < (OS_SWTMR_MAX_TIMERID - LOSCFG_BASE_CORE_SWTMR_LIMIT)) {
                swtmr->usTimerID += LOSCFG_BASE_CORE_SWTMR_LIMIT;
            } else {
                swtmr->usTimerID %= LOSCFG_BASE_CORE_SWTMR_LIMIT;
            }
        } else if (swtmr->ucMode == LOS_SWTMR_MODE_NO_SELFDELETE) {
            swtmr->ucState = OS_SWTMR_STATUS_CREATED;
        } else {
            swtmr->ucOverrun++;
            OsSwtmrStart(swtmr);
        }

        if (LOS_ListEmpty(listObject)) {
            break;
        }

        sortList = LOS_DL_LIST_ENTRY(listObject->pstNext, SortLinkList, sortLinkNode);
    }

    LOS_SpinUnlock(&g_swtmrSpin);
}

/*
 * Description: Get next timeout
 * Return     : Count of the Timer list
 */
LITE_OS_SEC_TEXT UINT32 OsSwtmrGetNextTimeout(VOID)
{
    return OsSortLinkGetNextExpireTime(&OsPercpuGet()->swtmrSortLink);
}

/*
 * Description: Stop of Software Timer interface
 * Input      : swtmr --- the software timer contrl handler
 */
LITE_OS_SEC_TEXT STATIC VOID OsSwtmrStop(SWTMR_CTRL_S *swtmr)
{
    SortLinkAttribute *sortLinkHeader = NULL;

#if (LOSCFG_KERNEL_SMP == YES)
    /*
     * the timer is running on the specific processor,
     * we need delete the timer from that processor's sortlink.
     */
    sortLinkHeader = &g_percpu[swtmr->uwCpuid].swtmrSortLink;
#else
    sortLinkHeader = &g_percpu[0].swtmrSortLink;
#endif
    OsDeleteSortLink(sortLinkHeader, &swtmr->stSortList);

    swtmr->ucState = OS_SWTMR_STATUS_CREATED;
    swtmr->ucOverrun = 0;
}

/*
 * Description: Get next software timer expiretime
 * Input      : swtmr --- the software timer contrl handler
 */
LITE_OS_SEC_TEXT STATIC UINT32 OsSwtmrTimeGet(const SWTMR_CTRL_S *swtmr)
{
    SortLinkAttribute *sortLinkHeader = NULL;

#if (LOSCFG_KERNEL_SMP == YES)
    /*
     * the timer is running on the specific processor,
     * we need search the timer from that processor's sortlink.
     */
    sortLinkHeader = &g_percpu[swtmr->uwCpuid].swtmrSortLink;
#else
    sortLinkHeader = &g_percpu[0].swtmrSortLink;
#endif

    return OsSortLinkGetTargetExpireTime(sortLinkHeader, &swtmr->stSortList);
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_SwtmrCreate(UINT32 interval,
                                             UINT8 mode,
                                             SWTMR_PROC_FUNC handler,
                                             UINT16 *swtmrID,
                                             UINTPTR arg)
{
    SWTMR_CTRL_S *swtmr = NULL;
    UINT32 intSave;
    SortLinkList *sortList = NULL;

    if (interval == 0) {
        return LOS_ERRNO_SWTMR_INTERVAL_NOT_SUITED;
    }

    if ((mode != LOS_SWTMR_MODE_ONCE) && (mode != LOS_SWTMR_MODE_PERIOD) &&
        (mode != LOS_SWTMR_MODE_NO_SELFDELETE)) {
        return LOS_ERRNO_SWTMR_MODE_INVALID;
    }

    if (handler == NULL) {
        return LOS_ERRNO_SWTMR_PTR_NULL;
    }

    if (swtmrID == NULL) {
        return LOS_ERRNO_SWTMR_RET_PTR_NULL;
    }

    SWTMR_LOCK(intSave);
    if (LOS_ListEmpty(&g_swtmrFreeList)) {
        SWTMR_UNLOCK(intSave);
        return LOS_ERRNO_SWTMR_MAXSIZE;
    }

    sortList = LOS_DL_LIST_ENTRY(g_swtmrFreeList.pstNext, SortLinkList, sortLinkNode);
    swtmr = LOS_DL_LIST_ENTRY(sortList, SWTMR_CTRL_S, stSortList);
    LOS_ListDelete(LOS_DL_LIST_FIRST(&g_swtmrFreeList));
    SWTMR_UNLOCK(intSave);

    swtmr->uwOwnerPid = OsCurrProcessGet()->processID;
    swtmr->pfnHandler = handler;
    swtmr->ucMode = mode;
    swtmr->ucOverrun = 0;
    swtmr->uwInterval = interval;
    swtmr->uwExpiry = interval;
    swtmr->uwArg = arg;
    swtmr->ucState = OS_SWTMR_STATUS_CREATED;
    SET_SORTLIST_VALUE(&(swtmr->stSortList), 0);
    *swtmrID = swtmr->usTimerID;

    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 LOS_SwtmrStart(UINT16 swtmrID)
{
    SWTMR_CTRL_S *swtmr = NULL;
    UINT32 intSave;
    UINT32 ret = LOS_OK;
    UINT16 swtmrCBID;

    if (swtmrID >= OS_SWTMR_MAX_TIMERID) {
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }

    SWTMR_LOCK(intSave);
    swtmrCBID = swtmrID % LOSCFG_BASE_CORE_SWTMR_LIMIT;
    swtmr = g_swtmrCBArray + swtmrCBID;

    if (swtmr->usTimerID != swtmrID) {
        SWTMR_UNLOCK(intSave);
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }

    switch (swtmr->ucState) {
        case OS_SWTMR_STATUS_UNUSED:
            ret = LOS_ERRNO_SWTMR_NOT_CREATED;
            break;
        /*
         * If the status of swtmr is timing, it should stop the swtmr first,
         * then start the swtmr again.
         */
        case OS_SWTMR_STATUS_TICKING:
            OsSwtmrStop(swtmr);
            /* fall-through */
        case OS_SWTMR_STATUS_CREATED:
            OsSwtmrStart(swtmr);
            break;
        default:
            ret = LOS_ERRNO_SWTMR_STATUS_INVALID;
            break;
    }

    SWTMR_UNLOCK(intSave);
    return ret;
}

LITE_OS_SEC_TEXT UINT32 LOS_SwtmrStop(UINT16 swtmrID)
{
    SWTMR_CTRL_S *swtmr = NULL;
    UINT32 intSave;
    UINT32 ret = LOS_OK;
    UINT16 swtmrCBID;

    if (swtmrID >= OS_SWTMR_MAX_TIMERID) {
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }

    SWTMR_LOCK(intSave);
    swtmrCBID = swtmrID % LOSCFG_BASE_CORE_SWTMR_LIMIT;
    swtmr = g_swtmrCBArray + swtmrCBID;

    if (swtmr->usTimerID != swtmrID) {
        SWTMR_UNLOCK(intSave);
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }

    switch (swtmr->ucState) {
        case OS_SWTMR_STATUS_UNUSED:
            ret = LOS_ERRNO_SWTMR_NOT_CREATED;
            break;
        case OS_SWTMR_STATUS_CREATED:
            ret = LOS_ERRNO_SWTMR_NOT_STARTED;
            break;
        case OS_SWTMR_STATUS_TICKING:
            OsSwtmrStop(swtmr);
            break;
        default:
            ret = LOS_ERRNO_SWTMR_STATUS_INVALID;
            break;
    }

    SWTMR_UNLOCK(intSave);
    return ret;
}

LITE_OS_SEC_TEXT UINT32 LOS_SwtmrTimeGet(UINT16 swtmrID, UINT32 *tick)
{
    SWTMR_CTRL_S *swtmr = NULL;
    UINT32 intSave;
    UINT32 ret = LOS_OK;
    UINT16 swtmrCBID;

    if (swtmrID >= OS_SWTMR_MAX_TIMERID) {
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }

    if (tick == NULL) {
        return LOS_ERRNO_SWTMR_TICK_PTR_NULL;
    }

    SWTMR_LOCK(intSave);
    swtmrCBID = swtmrID % LOSCFG_BASE_CORE_SWTMR_LIMIT;
    swtmr = g_swtmrCBArray + swtmrCBID;

    if (swtmr->usTimerID != swtmrID) {
        SWTMR_UNLOCK(intSave);
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }
    switch (swtmr->ucState) {
        case OS_SWTMR_STATUS_UNUSED:
            ret = LOS_ERRNO_SWTMR_NOT_CREATED;
            break;
        case OS_SWTMR_STATUS_CREATED:
            ret = LOS_ERRNO_SWTMR_NOT_STARTED;
            break;
        case OS_SWTMR_STATUS_TICKING:
            *tick = OsSwtmrTimeGet(swtmr);
            break;
        default:
            ret = LOS_ERRNO_SWTMR_STATUS_INVALID;
            break;
    }
    SWTMR_UNLOCK(intSave);
    return ret;
}

LITE_OS_SEC_TEXT UINT32 LOS_SwtmrDelete(UINT16 swtmrID)
{
    SWTMR_CTRL_S *swtmr = NULL;
    UINT32 intSave;
    UINT32 ret = LOS_OK;
    UINT16 swtmrCBID;

    if (swtmrID >= OS_SWTMR_MAX_TIMERID) {
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }

    SWTMR_LOCK(intSave);
    swtmrCBID = swtmrID % LOSCFG_BASE_CORE_SWTMR_LIMIT;
    swtmr = g_swtmrCBArray + swtmrCBID;

    if (swtmr->usTimerID != swtmrID) {
        SWTMR_UNLOCK(intSave);
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }

    switch (swtmr->ucState) {
        case OS_SWTMR_STATUS_UNUSED:
            ret = LOS_ERRNO_SWTMR_NOT_CREATED;
            break;
        case OS_SWTMR_STATUS_TICKING:
            OsSwtmrStop(swtmr);
            /* fall-through */
        case OS_SWTMR_STATUS_CREATED:
            OsSwtmrDelete(swtmr);
            break;
        default:
            ret = LOS_ERRNO_SWTMR_STATUS_INVALID;
            break;
    }

    SWTMR_UNLOCK(intSave);
    return ret;
}

#endif /* (LOSCFG_BASE_CORE_SWTMR == YES) */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
