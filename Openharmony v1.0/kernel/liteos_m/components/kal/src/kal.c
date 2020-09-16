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

#include "securec.h"
#include "hi_mem.h"
#include "los_task.h"
#include "los_swtmr.h"
#include "los_swtmr_pri.h"
#include "los_hwi.h"
#include "kal.h"


#ifdef __cplusplus
#define NULL 0L
#else
#ifndef NULL
#define NULL ((void *)0)
#endif
#endif
#define MS_PER_SECOND 1000

unsigned int KalThreadGetInfo(unsigned int threadId, ThreadInfo *info)
{
    unsigned int ret;
    if (info == NULL) {
        return -1;
    }
    (void)memset_s(info, sizeof(ThreadInfo), 0, sizeof(ThreadInfo));
    TSK_INFO_S *losTaskInfo = (TSK_INFO_S *)malloc(sizeof(TSK_INFO_S));
    if (losTaskInfo == NULL) {
        return -1;
    }
    (void)memset_s(losTaskInfo, sizeof(TSK_INFO_S), 0, sizeof(TSK_INFO_S));
    ret = LOS_TaskInfoGet(threadId, losTaskInfo);
    if (ret == LOS_OK) {
        info->id = losTaskInfo->uwTaskID;
        info->status = losTaskInfo->usTaskStatus;
        info->priority = losTaskInfo->usTaskPrio;
        info->taskSem = losTaskInfo->pTaskSem;
        info->taskMutex = losTaskInfo->pTaskMux;
        info->eventMask = losTaskInfo->uwEventMask;
        info->stackSize = losTaskInfo->uwStackSize;
        info->topOfStack = losTaskInfo->uwTopOfStack;
        info->bottomOfStack = losTaskInfo->uwBottomOfStack;
        info->mstatus = losTaskInfo->mstatus;
        info->mepc = losTaskInfo->mepc;
        info->tp = losTaskInfo->tp;
        info->ra = losTaskInfo->ra;
        info->sp = losTaskInfo->uwSP;
        info->currUsed = losTaskInfo->uwCurrUsed;
        info->peakUsed = losTaskInfo->uwPeakUsed;
        info->overflowFlag = losTaskInfo->bOvf;
        ret = memcpy_s(info->name, sizeof(info->name), losTaskInfo->acName, sizeof(info->name) - 1);
    }
    free(losTaskInfo);
    return ret;
}

void KalDelayUs(unsigned int us)
{
    unsigned int ticks;
    if (us == 0) {
        return;
    }
    ticks = LOS_MS2Tick(us / MS_PER_SECOND);
    (void)LOS_TaskDelay(ticks);
}

KalTimerId KalTimerCreate(KalTimerProc func, KalTimerType type, void *arg, unsigned int ticks)
{
    UINT16 swtmrId;
    UINT8 mode;
    if ((OS_INT_ACTIVE) || (NULL == func) || ((KAL_TIMER_ONCE != type) && (KAL_TIMER_PERIODIC != type))) {
        return (KalTimerId)NULL;
    }
    if (KAL_TIMER_ONCE == type) {
        mode = LOS_SWTMR_MODE_NO_SELFDELETE;
    } else {
        mode = LOS_SWTMR_MODE_PERIOD;
    }
#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
    if (LOS_OK != LOS_SwtmrCreate(ticks, mode, (SWTMR_PROC_FUNC)func, &swtmrId, (UINT32)(UINTPTR)arg,
        osTimerRousesAllow, osTimerAlignIgnore)) {
        return (KalTimerId)NULL;
    }
#else
    if (LOS_OK != LOS_SwtmrCreate(ticks, mode, (SWTMR_PROC_FUNC)func, &swtmrId, (UINT32)(UINTPTR)arg)) {
        return (KalTimerId)NULL;
    }
#endif
    return (KalTimerId)OS_SWT_FROM_SID(swtmrId);
}
KalErrCode KalTransRetCode(unsigned int ret)
{
    if (LOS_OK == ret) {
        return KAL_OK;
    } else if (LOS_ERRNO_SWTMR_ID_INVALID == ret) {
        return KAL_ERR_PARA;
    } else {
        return KAL_ERR_INNER;
    }
}
KalErrCode KalTimerStart(KalTimerId timerId)
{
    UINT32 ret;
    SWTMR_CTRL_S *swtmr = NULL;
    if (NULL == timerId) {
        return KAL_ERR_PARA;
    }
    swtmr = (SWTMR_CTRL_S *)timerId;

    ret = LOS_SwtmrStart(swtmr->usTimerID);
    return KalTransRetCode(ret);
}
// support change while not running.
KalErrCode KalTimerChange(KalTimerId timerId, unsigned int ticks)
{
    SWTMR_CTRL_S *swtmr = NULL;
    if ((0 == ticks) || (NULL == timerId)) {
        return KAL_ERR_PARA;
    }
    swtmr = (SWTMR_CTRL_S *)timerId;
    if (OS_SWTMR_STATUS_TICKING == swtmr->ucState) {
        return KAL_ERR_TIMER_STATE;
    }
    swtmr->uwInterval = ticks;
    return KAL_OK;
}
KalErrCode KalTimerStop(KalTimerId timerId)
{
    UINT32 ret;
    SWTMR_CTRL_S *swtmr = NULL;
    if (NULL == timerId) {
        return KAL_ERR_PARA;
    }
    swtmr = (SWTMR_CTRL_S *)timerId;
    ret = LOS_SwtmrStop(swtmr->usTimerID);
    return KalTransRetCode(ret);
}

KalErrCode KalTimerDelete(KalTimerId timerId)
{
    UINT32 ret;
    SWTMR_CTRL_S *swtmr = NULL;
    if (NULL == timerId) {
        return KAL_ERR_PARA;
    }
    swtmr = (SWTMR_CTRL_S *)timerId;
    ret = LOS_SwtmrDelete(swtmr->usTimerID);
    return KalTransRetCode(ret);
}
unsigned int KalTimerIsRunning(KalTimerId timerId)
{
    if ((OS_INT_ACTIVE) || (NULL == timerId)) {
        return 0;
    }
    return (OS_SWTMR_STATUS_TICKING == ((SWTMR_CTRL_S *)timerId)->ucState);
}

unsigned int KalTickToMs(unsigned int ticks)
{
    return LOS_Tick2MS(ticks);
}
unsigned int KalMsToTick(unsigned int millisec)
{
    return LOS_MS2Tick(millisec);
}

KalErrCode KalGetMemInfo(MemInfo *pmemInfo)
{
    hi_mdm_mem_info hiMemInfo;
    hi_u32 hiRet;
    if (NULL == pmemInfo) {
        return KAL_ERR_PARA;
    }
    hiRet = hi_mem_get_sys_info(&hiMemInfo);
    if (hiRet != 0) {
        return KAL_ERR_INNER;
    }
    pmemInfo->total = hiMemInfo.total;
    pmemInfo->used = hiMemInfo.used;
    pmemInfo->free = hiMemInfo.free;
    pmemInfo->freeNodeNum = hiMemInfo.free_node_num;
    pmemInfo->usedNodeNum = hiMemInfo.used_node_num;
    pmemInfo->maxFreeNodeSize = hiMemInfo.max_free_node_size;
    pmemInfo->mallocFailCount = hiMemInfo.malloc_fail_count;
    pmemInfo->peekSize = hiMemInfo.peek_size;
    pmemInfo->totalLmp = hiMemInfo.total_lmp;
    pmemInfo->usedLmp = hiMemInfo.used_lmp;
    pmemInfo->freeLmp = hiMemInfo.free_lmp;
    return KAL_OK;
}
