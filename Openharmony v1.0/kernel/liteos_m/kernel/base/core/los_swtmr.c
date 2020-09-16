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
#include "los_swtmr_pri.h"
#include "los_base_pri.h"
#include "los_sys.h"
#include "los_membox_pri.h"
#include "los_memory_pri.h"
#include "los_queue_pri.h"
#include "los_task_pri.h"
#include "los_hwi.h"
#if (LOSCFG_PLATFORM_EXC == YES)
#include "los_exc.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#if (LOSCFG_BASE_CORE_SWTMR == YES)

LITE_OS_SEC_BSS UINT32          g_swtmrHandlerQueue;           /* Software Timer timeout queue ID */
LITE_OS_SEC_BSS SWTMR_CTRL_S    *g_swtmrCBArray = NULL;        /* first address in Timer memory space */
LITE_OS_SEC_BSS SWTMR_CTRL_S    *g_swtmrFreeList = NULL;       /* Free list of Softwaer Timer */
LITE_OS_SEC_BSS SWTMR_CTRL_S    *g_swtmrSortList = NULL;       /* The software timer count list */

#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
typedef struct SwtmrAlignDataStr {
    UINT32 times : 24;
    UINT32 : 5;
    UINT32 canMultiple : 1;
    UINT32 canAlign : 1;
    UINT32 isAligned : 1;
} SwtmrAlignData;
LITE_OS_SEC_BSS SwtmrAlignData      g_swtmrAlignID[LOSCFG_BASE_CORE_SWTMR_LIMIT] = {0};   /* store swtmr align */
static UINT32                       g_swtimerRousesTime = 0;  /* suspend time */
static SWTMR_CTRL_S                 *g_swtmrRouses = NULL;    /* first swtmr that can wake up */
static SWTMR_CTRL_S                 *g_swtmrRousesPrev = NULL;
#endif

#define SWTMR_MAX_RUNNING_TICKS     2


/*****************************************************************************
Function    : OsSwtmrTask
Description : Swtmr task main loop, handle time-out timer.
Input       : None
Output      : None
Return      : None
*****************************************************************************/
LITE_OS_SEC_TEXT VOID OsSwtmrTask(VOID)
{
    SwtmrHandlerItem swtmrHandle;
    UINT32 readSzie;
    UINT32 ret;
    UINT64 tick;
    readSzie = sizeof(SwtmrHandlerItem);
    for (;;) {
        ret = LOS_QueueReadCopy(g_swtmrHandlerQueue, &swtmrHandle, &readSzie, LOS_WAIT_FOREVER);
        if ((ret == LOS_OK) && (readSzie == sizeof(SwtmrHandlerItem))) {
            if (swtmrHandle.handler == NULL) {
                continue;
            }

            tick = LOS_TickCountGet();
            swtmrHandle.handler(swtmrHandle.arg);
            tick = LOS_TickCountGet() - tick;

            if (tick >= SWTMR_MAX_RUNNING_TICKS) {
                PRINT_WARN("timer_handler(%p) cost too many ms(%d)\n",
                           swtmrHandle.handler,
                           (UINT32)((tick * OS_SYS_MS_PER_SECOND) / LOSCFG_BASE_CORE_TICK_PER_SECOND));
            }
        }
    }
}

/*****************************************************************************
Function    : OsSwtmrTaskCreate
Description : Create Software Timer
Input       : None
Output      : None
Return      : LOS_OK on success or error code on failure
*****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsSwtmrTaskCreate(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S swtmrTask;

    // Ignore the return code when matching CSEC rule 6.6(4).
    (VOID)memset_s(&swtmrTask, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));

    swtmrTask.pfnTaskEntry    = (TSK_ENTRY_FUNC)OsSwtmrTask;
    swtmrTask.uwStackSize     = LOSCFG_BASE_CORE_TSK_SWTMR_STACK_SIZE;
    swtmrTask.pcName          = "Swt_Task";
    swtmrTask.usTaskPrio      = 0;
    ret = LOS_TaskCreate(&g_swtmrTaskID, &swtmrTask);
    return ret;
}

/*****************************************************************************
Function    : OsSwtmrInit
Description : Initializes Software Timer
Input       : None
Output      : None
Return      : LOS_OK on success or error code on failure
*****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 OsSwtmrInit(VOID)
{
    UINT32 size;
    UINT16 index;
    UINT32 ret;
    SWTMR_CTRL_S *swtmr = NULL;
    SWTMR_CTRL_S *temp = NULL;

#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
    // Ignore the return code when matching CSEC rule 6.6(1).
    (VOID)memset_s((VOID *)g_swtmrAlignID, sizeof(SwtmrAlignData) * LOSCFG_BASE_CORE_SWTMR_LIMIT,
                   0, sizeof(SwtmrAlignData) * LOSCFG_BASE_CORE_SWTMR_LIMIT);
#endif

    g_swtmrSortList = (SWTMR_CTRL_S *)NULL;
    size = sizeof(SWTMR_CTRL_S) * LOSCFG_BASE_CORE_SWTMR_LIMIT;
    swtmr = (SWTMR_CTRL_S *)LOS_MemAlloc(m_aucSysMem0, size);
    if (swtmr == NULL) {
        return LOS_ERRNO_SWTMR_NO_MEMORY;
    }
    // Ignore the return code when matching CSEC rule 6.6(3).
    (VOID)memset_s((VOID *)swtmr, size, 0, size);
    g_swtmrCBArray = swtmr;
    g_swtmrFreeList = swtmr;
    swtmr->usTimerID = 0;
    temp = swtmr;
    swtmr++;
    for (index = 1; index < LOSCFG_BASE_CORE_SWTMR_LIMIT; index++, swtmr++) {
        swtmr->usTimerID = index;
        temp->pstNext = swtmr;
        temp = swtmr;
    }

    ret = LOS_QueueCreate((CHAR *)NULL, OS_SWTMR_HANDLE_QUEUE_SIZE,
                          &g_swtmrHandlerQueue, 0, sizeof(SwtmrHandlerItem));
    if (ret != LOS_OK) {
        (VOID)LOS_MemFree(m_aucSysMem0, swtmr);
        return LOS_ERRNO_SWTMR_QUEUE_CREATE_FAILED;
    }

    ret = OsSwtmrTaskCreate();
    if (ret != LOS_OK) {
        (VOID)LOS_MemFree(m_aucSysMem0, swtmr);
        return LOS_ERRNO_SWTMR_TASK_CREATE_FAILED;
    }

    return LOS_OK;
}

#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
STATIC_INLINE UINT32 OsSwtmrCalcAlignCount(UINT32 interval, UINT16 timerId)
{
    SWTMR_CTRL_S *cur = g_swtmrSortList;
    UINT32 count = 0;
    if (interval == 0) {
        return interval;
    }
    while (cur != NULL) {
        count += cur->uwCount;
        if (cur->usTimerID == timerId) {
            return (interval - (cur->uwInterval - count) % interval);
        }
        cur = cur->pstNext;
    }
    return interval;
}

LITE_OS_SEC_TEXT SWTMR_CTRL_S* OsSwtmrFindAlignPos(SWTMR_CTRL_S *swtmr)
{
    SWTMR_CTRL_S *intPos = (SWTMR_CTRL_S *)NULL;
    SWTMR_CTRL_S *cur = (SWTMR_CTRL_S *)NULL;
    SWTMR_CTRL_S *minInLarge = (SWTMR_CTRL_S *)NULL;
    SWTMR_CTRL_S *maxInLitte = (SWTMR_CTRL_S *)NULL;
    UINT32 currSwtmrTimes, swtmrTimes;
    SwtmrAlignData swtmrAlgInfo, currSwtmrAlgInfo;
    UINT32 minInLargeVal = OS_NULL_INT;
    UINT32 maxInLitteval = OS_NULL_INT;

    currSwtmrAlgInfo = g_swtmrAlignID[swtmr->usTimerID % LOSCFG_BASE_CORE_SWTMR_LIMIT];
    currSwtmrTimes = currSwtmrAlgInfo.times;
    cur = g_swtmrSortList;
    while (cur != NULL) {
        swtmrAlgInfo = g_swtmrAlignID[cur->usTimerID % LOSCFG_BASE_CORE_SWTMR_LIMIT];
        if ((swtmrAlgInfo.isAligned == 0) || (swtmrAlgInfo.canAlign == 0)) { // swtmr not start
            goto CONTINUE_NEXT_NODE;
        }
        // find same interval timer, directly return
        if (cur->uwInterval == swtmr->uwInterval) {
            swtmr->uwCount = 0;
            return cur;
        }

        if ((currSwtmrAlgInfo.canMultiple != 1) || (swtmrAlgInfo.times == 0)) {
            goto CONTINUE_NEXT_NODE;
        }
        swtmrTimes = swtmrAlgInfo.times;
        if (currSwtmrTimes == 0) {
            return NULL;
        }
        if ((swtmrTimes >= currSwtmrTimes) && ((swtmrTimes % currSwtmrTimes) == 0)) {
            if (minInLargeVal > (swtmrTimes / currSwtmrTimes)) {
                minInLargeVal = swtmrTimes / currSwtmrTimes;
                minInLarge = cur;
            }
        } else if ((swtmrTimes < currSwtmrTimes) && ((currSwtmrTimes % swtmrTimes) == 0)) {
            if (maxInLitteval > (currSwtmrTimes / swtmrTimes)) {
                maxInLitteval = currSwtmrTimes / swtmrTimes;
                maxInLitte = cur;
            }
        }
    CONTINUE_NEXT_NODE:

        cur = cur->pstNext;
    }
    if (minInLarge != NULL) {
        swtmr->uwCount = OsSwtmrCalcAlignCount(swtmr->uwInterval, minInLarge->usTimerID);
    } else if (maxInLitte != NULL) {
        swtmr->uwCount = 0;
        intPos = maxInLitte;
    }
    return intPos;
}
#endif

/*****************************************************************************
Function    : OsSwtmrStart
Description : Start Software Timer
Input       : swtmr ---------- Need to start Software Timer
Output      : None
Return      : None
*****************************************************************************/
LITE_OS_SEC_TEXT VOID OsSwtmrStart(SWTMR_CTRL_S *swtmr)
{
    SWTMR_CTRL_S *prev = (SWTMR_CTRL_S *)NULL;
    SWTMR_CTRL_S *cur = (SWTMR_CTRL_S *)NULL;

    swtmr->uwCount = swtmr->uwInterval;

#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
    if ((g_swtmrAlignID[swtmr->usTimerID % LOSCFG_BASE_CORE_SWTMR_LIMIT].canAlign == 1) &&
        (g_swtmrAlignID[swtmr->usTimerID % LOSCFG_BASE_CORE_SWTMR_LIMIT].isAligned == 0)) {
        g_swtmrAlignID[swtmr->usTimerID % LOSCFG_BASE_CORE_SWTMR_LIMIT].isAligned = 1;
        prev = OsSwtmrFindAlignPos(swtmr);
    }
#endif

    if (prev == NULL) {
        cur = g_swtmrSortList;
        while (cur != NULL) {
            if (cur->uwCount > swtmr->uwCount) {
                break;
            }

            swtmr->uwCount -= cur->uwCount;
            prev = cur;
            cur = cur->pstNext;
        }
    }

    swtmr->pstNext = ((prev == NULL) ? g_swtmrSortList : prev->pstNext);
    if (swtmr->pstNext != NULL) {
        swtmr->pstNext->uwCount -= swtmr->uwCount;
    }
    (prev == NULL) ? (g_swtmrSortList = swtmr) : (prev->pstNext = swtmr);
    swtmr->ucState = OS_SWTMR_STATUS_TICKING;
}

/*****************************************************************************
Function    : OsSwtmrDelete
Description : Delete Software Timer
Input       : swtmr --- Need to delete Software Timer, When using, Ensure that it can't be NULL.
Output      : None
Return      : None
*****************************************************************************/
STATIC_INLINE VOID OsSwtmrDelete(SWTMR_CTRL_S *swtmr)
{
    /* insert to free list */
    swtmr->pstNext = g_swtmrFreeList;
    g_swtmrFreeList = swtmr;
    swtmr->ucState = OS_SWTMR_STATUS_UNUSED;

#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
    (VOID)memset_s((VOID *)&g_swtmrAlignID[swtmr->usTimerID % LOSCFG_BASE_CORE_SWTMR_LIMIT],
                   sizeof(SwtmrAlignData), 0, sizeof(SwtmrAlignData));
#endif
}


LITE_OS_SEC_TEXT VOID OsSwtmrStop(const SWTMR_CTRL_S *swtmr)
{
    SWTMR_CTRL_S *prev = (SWTMR_CTRL_S *)NULL;
    SWTMR_CTRL_S *cur = (SWTMR_CTRL_S *)NULL;

    if (!g_swtmrSortList) {
        return;
    }

    cur = g_swtmrSortList;

    while (cur != swtmr) {
        prev = cur;
        cur = cur->pstNext;
    }

    if (cur->pstNext != NULL) {
        cur->pstNext->uwCount += cur->uwCount;
    }

    if (prev == NULL) {
        g_swtmrSortList = cur->pstNext;
    } else {
        prev->pstNext = cur->pstNext;
    }

    cur->pstNext = (SWTMR_CTRL_S *)NULL;
    cur->ucState = OS_SWTMR_STATUS_CREATED;

#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
    g_swtmrAlignID[swtmr->usTimerID % LOSCFG_BASE_CORE_SWTMR_LIMIT].isAligned = 0;
#endif
}

/*****************************************************************************
Function    : OsSwtmrTimeoutHandle
Description : Software Timer time out handler
Input       : None
Output      : None
Return      : None
*****************************************************************************/
LITE_OS_SEC_TEXT static VOID OsSwtmrTimeoutHandle(VOID)
{
    SWTMR_CTRL_S *swtmr = g_swtmrSortList;
    SwtmrHandlerItem swtmrHandler;

    while ((swtmr != NULL) && (swtmr->uwCount == 0)) {
        g_swtmrSortList = swtmr->pstNext;
        swtmrHandler.handler = swtmr->pfnHandler;
        swtmrHandler.arg = swtmr->uwArg;
        (VOID)LOS_QueueWriteCopy(g_swtmrHandlerQueue, &swtmrHandler, sizeof(SwtmrHandlerItem), LOS_NO_WAIT);
        if (swtmr->ucMode == LOS_SWTMR_MODE_ONCE) {
            OsSwtmrDelete(swtmr);
            if (swtmr->usTimerID < (OS_SWTMR_MAX_TIMERID - LOSCFG_BASE_CORE_SWTMR_LIMIT)) {
                swtmr->usTimerID += LOSCFG_BASE_CORE_SWTMR_LIMIT;
            } else {
                swtmr->usTimerID %= LOSCFG_BASE_CORE_SWTMR_LIMIT;
            }
        } else if (swtmr->ucMode == LOS_SWTMR_MODE_PERIOD) {
            OsSwtmrStart(swtmr);
        } else if (swtmr->ucMode == LOS_SWTMR_MODE_NO_SELFDELETE) {
            swtmr->ucState = OS_SWTMR_STATUS_CREATED;
        }

        swtmr = g_swtmrSortList;
    }
}

/*****************************************************************************
Function    : OsSwtmrScan
Description : Tick interrupt interface module of Software Timer
Input       : None
Output      : None
Return      : LOS_OK on success
*****************************************************************************/
LITE_OS_SEC_TEXT UINT32 OsSwtmrScan(VOID)
{
    if (g_swtmrSortList != NULL) {
        if (--(g_swtmrSortList->uwCount) == 0) {
            OsSwtmrTimeoutHandle();
        }
    }
    return LOS_OK;
}

/*****************************************************************************
Function    : OsSwtmrGetNextTimeout
Description : Get next timeout
Input       : None
Output      : None
Return      : Count of the Timer list
*****************************************************************************/
#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
LITE_OS_SEC_TEXT UINT32 OsSwtmrGetNextTimeout(VOID)
{
    SWTMR_CTRL_S *cur = NULL;
    UINT32 tmpTime = 0;
    UINT32 sleepTime = OS_NULL_INT;

    cur = g_swtmrSortList;

    // find first timer can wakeup the system
    while (cur != NULL) {
        if (cur->ucRouses == OS_SWTMR_ROUSES_ALLOW) {
            g_swtmrRouses = cur;
            break;
        }

        tmpTime += cur->uwCount;
        g_swtmrRousesPrev = cur;
        cur = cur->pstNext;
    }

    if (cur != NULL) {
        sleepTime = cur->uwCount + tmpTime;
        g_swtimerRousesTime  = sleepTime;
    }

    return sleepTime;
}
#else
LITE_OS_SEC_TEXT UINT32 OsSwtmrGetNextTimeout(VOID)
{
    if (g_swtmrSortList == NULL) {
        return OS_NULL_INT;
    }
    return g_swtmrSortList->uwCount;
}
#endif

/*****************************************************************************
Function    : OsSwtimerInsert
Description : Insert a list of swtmr
Input       : **head, *swtmr
Output      : **head, *swtmr
Return      : None
*****************************************************************************/
#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
VOID OsSwtimerInsert(SWTMR_CTRL_S **head, SWTMR_CTRL_S *swtmr)
{
    SWTMR_CTRL_S *prev = NULL;
    SWTMR_CTRL_S *nextTmp = swtmr->pstNext;
    SWTMR_CTRL_S *cur = *head;

    while (swtmr != NULL) {
        while (cur != NULL) {
            if (cur->uwCount > swtmr->uwCount) {
                break;
            }

            swtmr->uwCount -= cur->uwCount;
            prev = cur;
            cur = cur->pstNext;
        }
        swtmr->pstNext = cur;

        if (cur != NULL) {
            cur->uwCount -= swtmr->uwCount;
        }
        if (prev == NULL) {
            *head = swtmr;
        } else {
            prev->pstNext = swtmr;
        }

        prev = swtmr;
        swtmr = nextTmp;
        nextTmp = nextTmp->pstNext;
    }

    return;
}
#endif
/*****************************************************************************
Function    : OsSwtmrAdjust
Description : Adjust Software Timer list
Input       : sleepTime
Output      : None
Return      : None
*****************************************************************************/
#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
LITE_OS_SEC_TEXT VOID OsSwtmrAdjust(UINT32 sleepTime)
{
    SWTMR_CTRL_S  *cur = NULL;

    if (g_swtmrRouses == NULL) {
        return;
    }

    if (sleepTime > g_swtimerRousesTime) {
        sleepTime = g_swtimerRousesTime;
    }

    if (sleepTime <= g_swtmrRouses->uwCount) {
        g_swtmrRouses->uwCount -= sleepTime;
    } else {
        g_swtmrRouses->uwCount = g_swtimerRousesTime - sleepTime;

        if (g_swtmrRousesPrev != NULL) {
            g_swtmrRousesPrev->pstNext = NULL;
            cur = g_swtmrSortList;
            OsSwtimerInsert(&g_swtmrRouses, cur);
            g_swtmrSortList = g_swtmrRouses;
        }
    }
    if (g_swtmrSortList->uwCount == 0) {
        OsSwtmrTimeoutHandle();
    }

    g_swtmrRouses = NULL;
    g_swtmrRousesPrev = NULL;
}
#else
LITE_OS_SEC_TEXT VOID OsSwtmrAdjust(UINT32 sleepTime)
{
    UINT32 tmpSleepTime = sleepTime;

    if (g_swtmrSortList == NULL) {
        return;
    }

    if (tmpSleepTime > g_swtmrSortList->uwCount) {
        tmpSleepTime = g_swtmrSortList->uwCount;
    }

    g_swtmrSortList->uwCount -= tmpSleepTime;

    if (g_swtmrSortList->uwCount == 0) {
        OsSwtmrTimeoutHandle();
    }
}
#endif

LITE_OS_SEC_TEXT UINT32 OsSwtmrTimeGet(const SWTMR_CTRL_S *swtmr)
{
    SWTMR_CTRL_S *cur = (SWTMR_CTRL_S *)NULL;
    UINT32 tick = 0;

    cur = g_swtmrSortList;
    while (1) {
        if (cur == NULL) {
            break;
        }
        tick += cur->uwCount;
        if (cur == swtmr) {
            break;
        }

        cur = cur->pstNext;
    }

    return tick;
}

/*****************************************************************************
Function    : LOS_SwtmrCreate
Description : Create software timer
Input       : interval
              mode
              handler
              arg
Output      : swtmrId
Return      : LOS_OK on success or error code on failure
*****************************************************************************/
#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
LITE_OS_SEC_TEXT_INIT UINT32 LOS_SwtmrCreate(UINT32 interval,
                                             UINT8 mode,
                                             SWTMR_PROC_FUNC handler,
                                             UINT16 *swtmrId,
                                             UINT32 arg,
                                             UINT8 rouses,
                                             UINT8 sensitive)
#else
LITE_OS_SEC_TEXT_INIT UINT32 LOS_SwtmrCreate(UINT32 interval,
                                             UINT8 mode,
                                             SWTMR_PROC_FUNC handler,
                                             UINT16 *swtmrId,
                                             UINT32 arg)
#endif
{
    SWTMR_CTRL_S  *swtmr = NULL;
    UINTPTR  intSave;

    if (interval == 0) {
        return LOS_ERRNO_SWTMR_INTERVAL_NOT_SUITED;
    }

    if ((mode != LOS_SWTMR_MODE_ONCE) &&
        (mode != LOS_SWTMR_MODE_PERIOD) &&
        (mode != LOS_SWTMR_MODE_NO_SELFDELETE)) {
        return LOS_ERRNO_SWTMR_MODE_INVALID;
    }

    if (handler == NULL) {
        return LOS_ERRNO_SWTMR_PTR_NULL;
    }

    if (swtmrId == NULL) {
        return LOS_ERRNO_SWTMR_RET_PTR_NULL;
    }

#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
    if ((rouses != OS_SWTMR_ROUSES_IGNORE) && (rouses != OS_SWTMR_ROUSES_ALLOW)) {
        return OS_ERRNO_SWTMR_ROUSES_INVALID;
    }

    if ((sensitive != OS_SWTMR_ALIGN_INSENSITIVE) && (sensitive != OS_SWTMR_ALIGN_SENSITIVE)) {
        return OS_ERRNO_SWTMR_ALIGN_INVALID;
    }
#endif

    intSave = LOS_IntLock();
    if (g_swtmrFreeList == NULL) {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_SWTMR_MAXSIZE;
    }

    swtmr = g_swtmrFreeList;
    g_swtmrFreeList = swtmr->pstNext;
    LOS_IntRestore(intSave);
    swtmr->pfnHandler    = handler;
    swtmr->ucMode        = mode;
    swtmr->uwInterval    = interval;
    swtmr->pstNext       = (SWTMR_CTRL_S *)NULL;
    swtmr->uwCount       = 0;
    swtmr->uwArg         = arg;
#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
    swtmr->ucRouses      = rouses;
    swtmr->ucSensitive   = sensitive;
#endif
    swtmr->ucState       = OS_SWTMR_STATUS_CREATED;
    *swtmrId = swtmr->usTimerID;

    return LOS_OK;
}

/*****************************************************************************
Function    : LOS_SwtmrStart
Description : Start software timer
Input       : swtmrId ------- Software timer ID
Output      : None
Return      : LOS_OK on success or error code on failure
*****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_SwtmrStart(UINT16 swtmrId)
{
    SWTMR_CTRL_S *swtmr = NULL;
    UINTPTR intSave;
#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
    UINT32 times;
    UINT32 swtmrAlignIdIndex = 0;
#endif
    UINT32 ret = LOS_OK;
    UINT16 swtmrCbId;

    if (swtmrId >= OS_SWTMR_MAX_TIMERID) {
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }
    intSave = LOS_IntLock();
    swtmrCbId = swtmrId % LOSCFG_BASE_CORE_SWTMR_LIMIT;
    swtmr = g_swtmrCBArray + swtmrCbId;
    if (swtmr->usTimerID != swtmrId) {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }

#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
    if ((swtmr->ucSensitive == OS_SWTMR_ALIGN_INSENSITIVE) && (swtmr->ucMode == LOS_SWTMR_MODE_PERIOD)) {
        swtmrAlignIdIndex = swtmr->usTimerID % LOSCFG_BASE_CORE_SWTMR_LIMIT;
        g_swtmrAlignID[swtmrAlignIdIndex].canAlign = 1;
        if ((swtmr->uwInterval % LOS_COMMON_DIVISOR) == 0) {
            g_swtmrAlignID[swtmrAlignIdIndex].canMultiple = 1;
            times = swtmr->uwInterval / (LOS_COMMON_DIVISOR);
            g_swtmrAlignID[swtmrAlignIdIndex].times = times;
        }
    }
#endif

    switch (swtmr->ucState) {
        case OS_SWTMR_STATUS_UNUSED:
            ret = LOS_ERRNO_SWTMR_NOT_CREATED;
            break;
        case OS_SWTMR_STATUS_TICKING:
            OsSwtmrStop(swtmr);
            /* fall through */
        case OS_SWTMR_STATUS_CREATED:
            OsSwtmrStart(swtmr);
            break;
        default:
            ret = LOS_ERRNO_SWTMR_STATUS_INVALID;
            break;
    }

    LOS_IntRestore(intSave);
    return ret;
}

/*****************************************************************************
Function    : LOS_SwtmrStop
Description : Stop software timer
Input       : swtmrId ------- Software timer ID
Output      : None
Return      : LOS_OK on success or error code on failure
*****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_SwtmrStop(UINT16 swtmrId)
{
    SWTMR_CTRL_S *swtmr = NULL;
    UINTPTR intSave;
    UINT16 swtmrCbId;
    UINT32 ret = LOS_OK;

    if (swtmrId >= OS_SWTMR_MAX_TIMERID) {
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }
    intSave = LOS_IntLock();
    swtmrCbId = swtmrId % LOSCFG_BASE_CORE_SWTMR_LIMIT;
    swtmr = g_swtmrCBArray + swtmrCbId;
    if (swtmr->usTimerID != swtmrId) {
        LOS_IntRestore(intSave);
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

    LOS_IntRestore(intSave);
    return ret;
}

LITE_OS_SEC_TEXT UINT32 LOS_SwtmrTimeGet(UINT16 swtmrId, UINT32 *tick)
{
    SWTMR_CTRL_S *swtmr = NULL;
    UINTPTR intSave;
    UINT32 ret = LOS_OK;
    UINT16 swtmrCbId;

    if (swtmrId >= OS_SWTMR_MAX_TIMERID) {
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }

    if (tick == NULL) {
        return LOS_ERRNO_SWTMR_TICK_PTR_NULL;
    }

    intSave = LOS_IntLock();
    swtmrCbId = swtmrId % LOSCFG_BASE_CORE_SWTMR_LIMIT;
    swtmr = g_swtmrCBArray + swtmrCbId;

    if (swtmr->usTimerID != swtmrId) {
        LOS_IntRestore(intSave);
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
    LOS_IntRestore(intSave);
    return ret;
}

/*****************************************************************************
Function    : LOS_SwtmrDelete
Description : Delete software timer
Input       : swtmrId ------- Software timer ID
Output      : None
Return      : LOS_OK on success or error code on failure
*****************************************************************************/
LITE_OS_SEC_TEXT UINT32 LOS_SwtmrDelete(UINT16 swtmrId)
{
    SWTMR_CTRL_S *swtmr = NULL;
    UINTPTR intSave;
    UINT32 ret = LOS_OK;
    UINT16 swtmrCbId;

    if (swtmrId >= OS_SWTMR_MAX_TIMERID) {
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }
    intSave = LOS_IntLock();
    swtmrCbId = swtmrId % LOSCFG_BASE_CORE_SWTMR_LIMIT;
    swtmr = g_swtmrCBArray + swtmrCbId;
    if (swtmr->usTimerID != swtmrId) {
        LOS_IntRestore(intSave);
        return LOS_ERRNO_SWTMR_ID_INVALID;
    }

    switch (swtmr->ucState) {
        case OS_SWTMR_STATUS_UNUSED:
            ret = LOS_ERRNO_SWTMR_NOT_CREATED;
            break;
        case OS_SWTMR_STATUS_TICKING:
            OsSwtmrStop(swtmr);
            /* fall through */
        case OS_SWTMR_STATUS_CREATED:
            OsSwtmrDelete(swtmr);
            break;
        default:
            ret = LOS_ERRNO_SWTMR_STATUS_INVALID;
            break;
    }

    LOS_IntRestore(intSave);
    return ret;
}

#endif /* (LOSCFG_BASE_CORE_SWTMR == YES) */


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
