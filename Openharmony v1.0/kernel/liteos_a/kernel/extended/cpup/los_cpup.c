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

#include "los_cpup_pri.h"
#include "los_process_pri.h"
#include "los_base.h"
#include "los_swtmr.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#ifdef LOSCFG_KERNEL_CPUP

LITE_OS_SEC_BSS STATIC UINT16 swtmrID;
LITE_OS_SEC_BSS STATIC UINT16 cpupInitFlg = 0;
LITE_OS_SEC_BSS OsCpupCB *g_cpup = NULL;
LITE_OS_SEC_BSS STATIC UINT16 cpupMaxNum;
LITE_OS_SEC_BSS STATIC UINT16 hisPos = 0; /* current Sampling point of historyTime */
LITE_OS_SEC_BSS STATIC UINT64 cpuHistoryTime[OS_CPUP_HISTORY_RECORD_NUM + 1];

LITE_OS_SEC_BSS STATIC UINT64 startCycles = 0;
#ifdef LOSCFG_CPUP_INCLUDE_IRQ
LITE_OS_SEC_BSS STATIC UINT64 timeInIrqPerProcessSwitch[LOSCFG_KERNEL_CORE_NUM];
LITE_OS_SEC_BSS STATIC UINT64 intTimeStart[LOSCFG_KERNEL_CORE_NUM];
#endif

#define OS_CPUP_UNUSED 0x0U
#define OS_CPUP_USED   0x1U
#define HIGH_BITS 32

#define CPUP_PRE_POS(pos) (((pos) == 0) ? (OS_CPUP_HISTORY_RECORD_NUM - 1) : ((pos) - 1))
#define CPUP_POST_POS(pos) (((pos) == (OS_CPUP_HISTORY_RECORD_NUM - 1)) ? 0 : ((pos) + 1))

LITE_OS_SEC_TEXT_INIT VOID OsCpupGuard(VOID)
{
    UINT16 prevPos;
    UINT16 loop;
    UINT32 pid;
    UINT32 intSave;
    UINT64 curCycle;

    SCHEDULER_LOCK(intSave);

    curCycle = OsGetCpuCycle();
    prevPos = hisPos;
    hisPos = CPUP_POST_POS(hisPos);
    cpuHistoryTime[prevPos] = curCycle;

    for (loop = 0; loop < cpupMaxNum; loop++) {
        g_cpup[loop].historyTime[prevPos] = g_cpup[loop].allTime;
    }

    for (loop = 0; loop < LOSCFG_KERNEL_CORE_NUM; loop++) {
        pid = OsCpuProcessIDGetUnsafe(loop);
        /* reacquire the cycle to prevent flip */
        curCycle = OsGetCpuCycle();
        g_cpup[pid].historyTime[prevPos] += curCycle - g_cpup[pid].startTime;
#ifdef LOSCFG_CPUP_INCLUDE_IRQ
        g_cpup[pid].historyTime[prevPos] -= timeInIrqPerProcessSwitch[loop];
#endif
    }

    SCHEDULER_UNLOCK(intSave);
}

LITE_OS_SEC_TEXT_INIT VOID OsCpupGuardCreator(VOID)
{
    (VOID)LOS_SwtmrCreate(LOSCFG_BASE_CORE_TICK_PER_SECOND, LOS_SWTMR_MODE_PERIOD,
                          (SWTMR_PROC_FUNC)OsCpupGuard, &swtmrID, 0);

    (VOID)LOS_SwtmrStart(swtmrID);
}

/*
 * Description: initialization of CPUP
 * Return     : LOS_OK or Error Information
 */
LITE_OS_SEC_TEXT_INIT UINT32 OsCpupInit(VOID)
{
    UINT32 size;

    cpupMaxNum = LOSCFG_BASE_CORE_PROCESS_LIMIT;
#ifdef LOSCFG_CPUP_INCLUDE_IRQ
    cpupMaxNum += OS_HWI_MAX_NUM;
#endif

    /* every process has only one record, and it won't operated at the same time */
    size = cpupMaxNum * sizeof(OsCpupCB);
    g_cpup = (OsCpupCB *)LOS_MemAlloc(m_aucSysMem0, size);
    if (g_cpup == NULL) {
        return LOS_ERRNO_CPUP_NO_MEMORY;
    }

    (VOID)memset_s(g_cpup, size, 0, size);
    cpupInitFlg = 1;
    return LOS_OK;
}

LITE_OS_SEC_TEXT VOID OsCpupSet(UINT32 id)
{
    g_cpup[id].id = id;
    g_cpup[id].status = OS_CPUP_USED;
}

LITE_OS_SEC_TEXT VOID OsCpupClean(UINT32 id)
{
    (VOID)memset_s((VOID *)&g_cpup[id], sizeof(OsCpupCB), 0, sizeof(OsCpupCB));
}

LITE_OS_SEC_TEXT_INIT VOID LOS_CpupReset(VOID)
{
    UINT32 cpupIndex;
    UINT32 maxNum = cpupMaxNum;
    UINT16 loop;
    UINT64 curCycle;
    UINT32 intSave;

    if (g_cpup == NULL) {
        return;
    }

    cpupInitFlg = 0;
    intSave = LOS_IntLock();
    (VOID)LOS_SwtmrStop(swtmrID);
    curCycle = OsGetCpuCycle();

    for (loop = 0; loop < (OS_CPUP_HISTORY_RECORD_NUM + 1); loop++) {
        cpuHistoryTime[loop] = curCycle;
    }

    for (cpupIndex = 0; cpupIndex < maxNum; cpupIndex++) {
        g_cpup[cpupIndex].startTime = curCycle;
        g_cpup[cpupIndex].allTime = curCycle;
        for (loop = 0; loop < (OS_CPUP_HISTORY_RECORD_NUM + 1); loop++) {
            g_cpup[cpupIndex].historyTime[loop] = curCycle;
        }
    }

#ifdef LOSCFG_CPUP_INCLUDE_IRQ
    for (loop = 0; loop < LOSCFG_KERNEL_CORE_NUM; loop++) {
        timeInIrqPerProcessSwitch[loop] = 0;
    }
#endif

    (VOID)LOS_SwtmrStart(swtmrID);
    LOS_IntRestore(intSave);
    cpupInitFlg = 1;

    return;
}

LITE_OS_SEC_TEXT_MINOR VOID OsSetCpuCycle(UINT64 cycles)
{
    startCycles = cycles;
    return;
}

/*
 * Description: get current cycles count
 * Return     : current cycles count
 */
LITE_OS_SEC_TEXT_MINOR UINT64 OsGetCpuCycle(VOID)
{
    UINT32 high;
    UINT32 low;
    UINT64 cycles;

    LOS_GetCpuCycle(&high, &low);
    cycles = ((UINT64)high << HIGH_BITS) + low;
    if (startCycles == 0) {
        startCycles = cycles;
    }

    /*
     * The cycles should keep growing, if the checking failed,
     * it mean LOS_GetCpuCycle has the problem which should be fixed.
     */
    LOS_ASSERT(cycles >= startCycles);

    return (cycles - startCycles);
}

#ifdef LOSCFG_CPUP_INCLUDE_IRQ
STATIC VOID OsRemoveInterTimeFromPorcess(UINT32 runPID)
{
    UINT16 loop;
    UINT32 pid;

    for (loop = 0; loop < LOSCFG_KERNEL_CORE_NUM; loop++) {
        pid = OsCpuProcessIDGetUnsafe(loop);
        if (pid != runPID) {
            continue;
        }

        g_cpup[runPID].allTime -= timeInIrqPerProcessSwitch[loop];
        timeInIrqPerProcessSwitch[loop] = 0;
    }
}
#endif

/*
 * Description: start process to get cycles count in current process begining
 */
LITE_OS_SEC_TEXT_MINOR STATIC VOID OsProcessCycleStart(VOID)
{
    UINT32 pid;

    if (cpupInitFlg == 0) {
        return;
    }

    pid = LOS_GetCurrProcessID();
    g_cpup[pid].id = pid;
    g_cpup[pid].startTime = OsGetCpuCycle();

    return;
}

/*
 * Description: quit process and get cycle count
 */
LITE_OS_SEC_TEXT_MINOR STATIC VOID OsProcessCycleEnd(VOID)
{
    UINT16 runTaskCount;
    UINT32 runPID;
    UINT64 cpuCycle;
    LosProcessCB *runProcess = NULL;

    if (cpupInitFlg == 0) {
        return;
    }

    runProcess = OsCurrProcessGet();
    runPID = runProcess->processID;
    if (g_cpup[runPID].startTime == 0) {
        return;
    }

    cpuCycle = OsGetCpuCycle();
    runTaskCount = OS_PROCESS_GET_RUNTASK_COUNT(runProcess->processStatus);
    g_cpup[runPID].allTime += (cpuCycle - g_cpup[runPID].startTime) * runTaskCount;
#ifdef LOSCFG_CPUP_INCLUDE_IRQ
    OsRemoveInterTimeFromPorcess(runPID);
#endif
    g_cpup[runPID].startTime = 0;

    return;
}

/*
 * Description: start process to get cycles count in current process ending
 */
LITE_OS_SEC_TEXT_MINOR VOID OsProcessCycleEndStart(UINT32 newID, UINT16 runTaskCount)
{
    UINT32 runPID;
    UINT64 cpuCycle;
    OsCpupCB *cpup = NULL;

    if (cpupInitFlg == 0) {
        return;
    }

    LOS_ASSERT(runTaskCount != 0);

    cpuCycle = OsGetCpuCycle();
    runPID = LOS_GetCurrProcessID();
    cpup = &g_cpup[runPID];
    if (cpup->startTime != 0) {
        cpup->allTime += (cpuCycle - cpup->startTime) * runTaskCount;
        cpup->startTime = cpuCycle;
#ifdef LOSCFG_CPUP_INCLUDE_IRQ
        OsRemoveInterTimeFromPorcess(runPID);
#endif
    }

    cpup = &g_cpup[newID];
    cpup->id = newID;
    cpup->startTime = cpuCycle;

    return;
}

LITE_OS_SEC_TEXT_MINOR STATIC VOID OsCpupGetPos(UINT16 mode, UINT16 *curPosPointer, UINT16 *prePosPointer)
{
    UINT16 curPos;
    UINT16 tmpPos;
    UINT16 prePos;

    tmpPos = hisPos;
    curPos = CPUP_PRE_POS(tmpPos);

    /*
     * The current postion has nothing to do with the CPUP modes,
     * however, the previous postion differs.
     */
    switch (mode) {
        case CPUP_LAST_ONE_SECONDS:
            prePos = CPUP_PRE_POS(curPos);
            break;
        case CPUP_LAST_TEN_SECONDS:
            prePos = tmpPos;
            break;
        case CPUP_ALL_TIME:
            /* fall-through */
        default:
            prePos = OS_CPUP_HISTORY_RECORD_NUM;
            break;
    }

    *curPosPointer = curPos;
    *prePosPointer = prePos;

    return;
}

LITE_OS_SEC_TEXT_MINOR STATIC INLINE UINT32 OsCpuUsageParaCheck(UINT32 pid)
{
    if (cpupInitFlg == 0) {
        return LOS_ERRNO_CPUP_NO_INIT;
    }

    if (OS_PID_CHECK_INVALID(pid)) {
        return LOS_ERRNO_CPUP_PID_INVALID;
    }

    /* weather the process is created */
    if (g_cpup[pid].id != pid) {
        return LOS_ERRNO_CPUP_PROCESS_NO_CREATED;
    }

    if (g_cpup[pid].status == OS_CPUP_UNUSED) {
        return LOS_ERRNO_CPUP_PROCESS_NO_CREATED;
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 OsHistorySysCpuUsageUnsafe(UINT16 mode)
{
    UINT64 cpuCycleAll;
    UINT64 idleCycleAll;
    UINT32 cpup = 0;
    UINT16 pos;
    UINT16 prePos;
    UINT32 idlePID;

    if (cpupInitFlg == 0) {
        return LOS_ERRNO_CPUP_NO_INIT;
    }

    OsProcessCycleEnd();

    OsCpupGetPos(mode, &pos, &prePos);
    cpuCycleAll = cpuHistoryTime[pos] - cpuHistoryTime[prePos];

    idlePID = OsGetIdleProcessID();
    idleCycleAll = g_cpup[idlePID].historyTime[pos] - g_cpup[idlePID].historyTime[prePos];

    if (cpuCycleAll) {
        cpup = (LOS_CPUP_PRECISION - (UINT32)((LOS_CPUP_SINGLE_CORE_PRECISION * idleCycleAll) / cpuCycleAll));
    }

    OsProcessCycleStart();
    return cpup;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_HistorySysCpuUsage(UINT16 mode)
{
    UINT32 cpup;
    UINT32 intSave;

    /* get end time of current process */
    SCHEDULER_LOCK(intSave);
    cpup = OsHistorySysCpuUsageUnsafe(mode);
    SCHEDULER_UNLOCK(intSave);
    return cpup;
}

LITE_OS_SEC_TEXT UINT32 OsHistoryProcessCpuUsageUnsafe(UINT32 pid, UINT16 mode)
{
    UINT64 cpuCycleAll;
    UINT64 cpuCycleCurProcess;
    UINT16 pos;
    UINT16 prePos;
    UINT32 cpup = 0;
    UINT32 ret;
    OsCpupCB *processCpup = &g_cpup[pid];

    ret = OsCpuUsageParaCheck(pid);
    if (ret != LOS_OK) {
        return ret;
    }

    OsProcessCycleEnd();

    OsCpupGetPos(mode, &pos, &prePos);
    cpuCycleAll = cpuHistoryTime[pos] - cpuHistoryTime[prePos];
    cpuCycleCurProcess = processCpup->historyTime[pos] - processCpup->historyTime[prePos];
    if (cpuCycleAll) {
        cpup = (UINT32)((LOS_CPUP_SINGLE_CORE_PRECISION * cpuCycleCurProcess) / cpuCycleAll);
    }

    OsProcessCycleStart();

    return cpup;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_HistoryProcessCpuUsage(UINT32 pid, UINT16 mode)
{
    UINT32 cpup;
    UINT32 intSave;

    SCHEDULER_LOCK(intSave);
    cpup = OsHistoryProcessCpuUsageUnsafe(pid, mode);
    SCHEDULER_UNLOCK(intSave);

    return cpup;
}

LITE_OS_SEC_TEXT UINT32 OsAllCpuUsageUnsafe(UINT16 maxNum, CPUP_INFO_S *cpupInfo, UINT16 mode, UINT16 flag)
{
    UINT16 loop;
    UINT16 index;
    UINT16 pos;
    UINT16 prePos;
    UINT64 cpuCycleAll;
    UINT64 cpuCycleCurProcess;
    UINT16 numTmpMax = maxNum;
    UINT16 numTmpMin = 0;
    UINT16 numMax = g_processMaxNum;

    if (cpupInitFlg == 0) {
        return  LOS_ERRNO_CPUP_NO_INIT;
    }

    if (cpupInfo == NULL) {
        return LOS_ERRNO_CPUP_PROCESS_PTR_NULL;
    }

    if (maxNum == 0) {
        return  LOS_ERRNO_CPUP_MAXNUM_INVALID;
    }

#ifdef LOSCFG_CPUP_INCLUDE_IRQ
    if (flag == 0) {
        numTmpMax += g_processMaxNum;
        numTmpMin += g_processMaxNum;
        numMax = cpupMaxNum;
    }
#endif

    if (numTmpMax > numMax) {
        numTmpMax = numMax;
    }

    OsProcessCycleEnd();

    OsCpupGetPos(mode, &pos, &prePos);
    cpuCycleAll = cpuHistoryTime[pos] - cpuHistoryTime[prePos];

    for (loop = numTmpMin; loop < numTmpMax; loop++) {
        if (g_cpup[loop].status == OS_CPUP_UNUSED) {
            continue;
        }

        index = loop - numTmpMin;
        cpuCycleCurProcess = g_cpup[loop].historyTime[pos] - g_cpup[loop].historyTime[prePos];
        cpupInfo[index].usStatus = g_cpup[loop].status;

        if (cpuCycleAll) {
            cpupInfo[index].uwUsage = (UINT32)((LOS_CPUP_SINGLE_CORE_PRECISION * cpuCycleCurProcess) / cpuCycleAll);
        }
    }

    OsProcessCycleStart();
    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_AllCpuUsage(UINT16 maxNum, CPUP_INFO_S *cpupInfo, UINT16 mode, UINT16 flag)
{
    UINT32 intSave;
    UINT32 ret;

    SCHEDULER_LOCK(intSave);
    ret = OsAllCpuUsageUnsafe(maxNum, cpupInfo, mode, flag);
    SCHEDULER_UNLOCK(intSave);

    return ret;
}

#ifdef LOSCFG_CPUP_INCLUDE_IRQ
LITE_OS_SEC_TEXT_MINOR VOID OsCpupIrqStart(VOID)
{
    UINT32 high;
    UINT32 low;

    LOS_GetCpuCycle(&high, &low);
    intTimeStart[ArchCurrCpuid()] = ((UINT64)high << HIGH_BITS) + low;
    return;
}

LITE_OS_SEC_TEXT_MINOR VOID OsCpupIrqEnd(UINT32 intNum)
{
    UINT32 high;
    UINT32 low;
    UINT64 intTimeEnd;
    UINT32 cpuID = ArchCurrCpuid();

    LOS_GetCpuCycle(&high, &low);
    intTimeEnd = ((UINT64)high << HIGH_BITS) + low;

    g_cpup[g_processMaxNum + intNum].id = intNum;
    g_cpup[g_processMaxNum + intNum].status = OS_CPUP_USED;
    timeInIrqPerProcessSwitch[cpuID] += (intTimeEnd - intTimeStart[cpuID]);
    g_cpup[g_processMaxNum + intNum].allTime += (intTimeEnd - intTimeStart[cpuID]);

    return;
}
#endif

#endif /* LOSCFG_KERNEL_CPUP */
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
