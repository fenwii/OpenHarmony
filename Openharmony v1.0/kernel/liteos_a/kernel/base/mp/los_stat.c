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

#include "los_task_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#if (LOSCFG_KERNEL_SCHED_STATISTICS == YES)
#define HIGHTASKPRI           16
#define NS_PER_MS             1000000
#define DECIMAL_TO_PERCENTAGE 100

typedef struct {
    UINT64      idleRuntime;
    UINT64      idleStarttime;
    UINT64      highTaskRuntime;
    UINT64      highTaskStarttime;
    UINT64      spinWaitRuntime;
    UINT64      sumPriority;
    UINT32      prioritySwitch;
    UINT32      highTaskSwitch;
    UINT32      contexSwitch;
    UINT32      hwiNum;
    UINT32      ipiIrqNum;
} MpStatPercpu;

STATIC BOOL g_mpStaticStartFlag = FALSE;
STATIC UINT64 g_mpStaticStartTime;
STATIC MpStatPercpu g_mpStatPercpu[LOSCFG_KERNEL_SMP_CORE_NUM] = {0};

STATIC VOID OsMpSchedStatistics(LosTaskCB *runTask, LosTaskCB *newTask)
{
    UINT32 cpuid;
    UINT32 idleTaskID;
    UINT64 now, runtime;

    if (g_mpStaticStartFlag != TRUE) {
        return;
    }

    cpuid = ArchCurrCpuid();
    idleTaskID = OsGetIdleTaskId();
    now = LOS_CurrNanosec();

    g_mpStatPercpu[cpuid].contexSwitch++;

    if ((runTask->taskID != idleTaskID) && (newTask->taskID == idleTaskID)) {
        g_mpStatPercpu[cpuid].idleStarttime = now;
    }

    if ((runTask->taskID == idleTaskID) && (newTask->taskID != idleTaskID)) {
        runtime = now - g_mpStatPercpu[cpuid].idleStarttime;
        g_mpStatPercpu[cpuid].idleRuntime += runtime;
        g_mpStatPercpu[cpuid].idleStarttime = 0;
    }

    if ((runTask->priority >= HIGHTASKPRI) && (newTask->priority < HIGHTASKPRI)) {
        g_mpStatPercpu[cpuid].highTaskStarttime = now;
    }

    if ((runTask->priority < HIGHTASKPRI) && (newTask->priority >= HIGHTASKPRI)) {
        runtime = now - g_mpStatPercpu[cpuid].highTaskStarttime;
        g_mpStatPercpu[cpuid].highTaskRuntime += runtime;
        g_mpStatPercpu[cpuid].highTaskStarttime = 0;
    }

    if (newTask->priority < HIGHTASKPRI) {
        g_mpStatPercpu[cpuid].highTaskSwitch++;
    }

    if (newTask->taskID != idleTaskID) {
        g_mpStatPercpu[cpuid].sumPriority += newTask->priority;
        g_mpStatPercpu[cpuid].prioritySwitch++;
    }

    return;
}

LITE_OS_SEC_TEXT_MINOR VOID OsSchedStatistics(LosTaskCB *runTask, LosTaskCB *newTask)
{
    UINT64 runtime;
    UINT32 cpuid = ArchCurrCpuid();
    UINT64 now = LOS_CurrNanosec();

    SchedStat *schedRun = &runTask->schedStat;
    SchedStat *schedNew = &newTask->schedStat;
    SchedPercpu *cpuRun = &schedRun->schedPercpu[cpuid];
    SchedPercpu *cpuNew = &schedNew->schedPercpu[cpuid];

    /* calculate one chance of running time */
    runtime = now - schedRun->startRuntime;

    /* add running timer to running task statistics */
    cpuRun->runtime += runtime;
    schedRun->allRuntime += runtime;

    /* add context switch counters and schedule start time */
    cpuNew->contexSwitch++;
    schedNew->allContextSwitch++;
    schedNew->startRuntime = now;
    OsMpSchedStatistics(runTask, newTask);
}

LITE_OS_SEC_TEXT_MINOR VOID OsSpinWaitStatistics(UINT64 spinWaitRuntime)
{
    UINT32 cpuid = ArchCurrCpuid();
    g_mpStatPercpu[cpuid].spinWaitRuntime += spinWaitRuntime;
    return;
}

LITE_OS_SEC_TEXT_MINOR VOID OsHwiStatistics(size_t intNum)
{
    UINT32 cpuid = ArchCurrCpuid();

    if ((g_mpStaticStartFlag != TRUE) || (intNum == OS_TICK_INT_NUM)) {
        return;
    }

    g_mpStatPercpu[cpuid].hwiNum++;
    /* 16: 0~15 is ipi interrupts */
    if (intNum < 16) {
        g_mpStatPercpu[cpuid].ipiIrqNum++;
    }

    return;
}

LITE_OS_SEC_TEXT_MINOR VOID OsShellCmdDumpSched(VOID)
{
    LosTaskCB *taskCB = NULL;
    UINT32 loop;
    UINT32 cpuid;
    UINT32 affinity;

    PRINTK("\n");
    PRINTK("Task                          TID              Total Time     Total CST     "
           "CPU                   Time           CST\n");
    PRINTK("----                          ---      ------------------    ----------    -"
           "---     ------------------    ----------\n");

    for (loop = 0; loop < g_taskMaxNum; loop++) {
        taskCB = (((LosTaskCB *)g_taskCBArray) + loop);
        if (OsTaskIsUnused(taskCB)) {
            continue;
        }

        affinity = (UINT32)taskCB->cpuAffiMask;

        PRINTK("%-30s0x%-6x%+16lf ms  %10d\n", taskCB->taskName, taskCB->taskID,
               (DOUBLE)(taskCB->schedStat.allRuntime) / NS_PER_MS,
               taskCB->schedStat.allContextSwitch);

        for (cpuid = 0; cpuid < LOSCFG_KERNEL_CORE_NUM; cpuid++) {
            if (!((1U << cpuid) & affinity)) {
                continue;
            }

            PRINTK("                                                                           "
                   "CPU%d    %+16lf ms  %12d\n", cpuid,
                   (DOUBLE)(taskCB->schedStat.schedPercpu[cpuid].runtime) / NS_PER_MS,
                   taskCB->schedStat.schedPercpu[cpuid].contexSwitch);
        }
    }

    PRINTK("\n");
}

LITE_OS_SEC_TEXT_MINOR VOID OsShellMpStaticStart(VOID)
{
    LosTaskCB *taskCB = NULL;
    UINT32 loop;
    UINT32 cpuid = 0;
    UINT32 intSave;

    SCHEDULER_LOCK(intSave);

    if (g_mpStaticStartFlag) {
        PRINT_WARN("mp static has started\n");
        SCHEDULER_UNLOCK(intSave);
        return;
    }

    g_mpStaticStartTime = LOS_CurrNanosec();

    for (loop = 0; loop < g_taskMaxNum; loop++) {
        taskCB = (((LosTaskCB *)g_taskCBArray) + loop);
        if (taskCB->taskStatus & OS_TASK_STATUS_RUNNING) {
#if (LOSCFG_KERNEL_SMP == YES)
            cpuid = taskCB->currCpu;
#endif
            if ((UINT32)(OS_TASK_INVALID_CPUID) == cpuid) {
                continue;
            }
            if (!strcmp(taskCB->taskName, "Idle")) {
                g_mpStatPercpu[cpuid].idleStarttime = g_mpStaticStartTime;
            }
            if (taskCB->priority < HIGHTASKPRI) {
                g_mpStatPercpu[cpuid].highTaskStarttime = g_mpStaticStartTime;
                g_mpStatPercpu[cpuid].highTaskSwitch++;
            }
            if (strcmp(taskCB->taskName, "Idle")) {
                g_mpStatPercpu[cpuid].sumPriority += taskCB->priority;
                g_mpStatPercpu[cpuid].prioritySwitch++;
            }
        }
    }
    g_mpStaticStartFlag = TRUE;
    SCHEDULER_UNLOCK(intSave);

    PRINTK("mp static start\n");

    return;
}

LITE_OS_SEC_TEXT_MINOR VOID OsMpStaticShow(UINT64 mpStaticPastTime)
{
    UINT32 cpuid;
    PRINTK("\n");
    PRINTK("Passed Time: %+16lf ms\n", (DOUBLE)mpStaticPastTime / NS_PER_MS);
    PRINTK("--------------------------------\n");
    PRINTK("CPU       Idle(%%)      schedule    noTick Hwi        MP Hwi    MP Loss(%%)       "
           "avg PRI      HiTSK(%%)     HiTSK SCH    HiTSK P(ms)\n");
    PRINTK("----    ---------    ----------    ----------    ----------    ----------    "
           "----------    ----------    ----------    ----------\n");

    for (cpuid = 0; cpuid < LOSCFG_KERNEL_CORE_NUM; cpuid++) {
        PRINTK("CPU%d   %+10lf%14d%14d%14d   %+11lf   %+11lf   %+11lf%14d   %+11lf\n", cpuid,
               ((DOUBLE)(g_mpStatPercpu[cpuid].idleRuntime) / mpStaticPastTime) * DECIMAL_TO_PERCENTAGE,
               g_mpStatPercpu[cpuid].contexSwitch,
               g_mpStatPercpu[cpuid].hwiNum,
               g_mpStatPercpu[cpuid].ipiIrqNum,
               ((DOUBLE)(g_mpStatPercpu[cpuid].spinWaitRuntime) / mpStaticPastTime) * DECIMAL_TO_PERCENTAGE,
               (g_mpStatPercpu[cpuid].prioritySwitch == 0) ? OS_TASK_PRIORITY_LOWEST :
               ((DOUBLE)(g_mpStatPercpu[cpuid].sumPriority) / (g_mpStatPercpu[cpuid].prioritySwitch)),
               ((DOUBLE)(g_mpStatPercpu[cpuid].highTaskRuntime) / mpStaticPastTime) * DECIMAL_TO_PERCENTAGE,
               g_mpStatPercpu[cpuid].highTaskSwitch,
               (g_mpStatPercpu[cpuid].highTaskSwitch == 0) ? 0 :
               ((DOUBLE)(g_mpStatPercpu[cpuid].highTaskRuntime) / (g_mpStatPercpu[cpuid].highTaskSwitch)) / NS_PER_MS);
    }

    PRINTK("\n");
}

LITE_OS_SEC_TEXT_MINOR VOID OsShellMpStaticStop(VOID)
{
    LosTaskCB *taskCB = NULL;
    UINT32 loop;
    UINT32 cpuid = 0;
    UINT64 mpStaticStopTime;
    UINT64 mpStaticPastTime;
    UINT64 runtime;
    UINT32 intSave;

    SCHEDULER_LOCK(intSave);

    if (g_mpStaticStartFlag != TRUE) {
        PRINT_WARN("Please set mp static start\n");
        SCHEDULER_UNLOCK(intSave);
        return;
    }

    g_mpStaticStartFlag = FALSE;
    mpStaticStopTime = LOS_CurrNanosec();
    mpStaticPastTime = mpStaticStopTime - g_mpStaticStartTime;

    for (loop = 0; loop < g_taskMaxNum; loop++) {
        taskCB = (((LosTaskCB *)g_taskCBArray) + loop);
        if (taskCB->taskStatus & OS_TASK_STATUS_RUNNING) {
#if (LOSCFG_KERNEL_SMP == YES)
            cpuid = taskCB->currCpu;
#endif
            if (cpuid == (UINT32)(OS_TASK_INVALID_CPUID)) {
                continue;
            }
            if (!strcmp(taskCB->taskName, "Idle")) {
                runtime = mpStaticStopTime - g_mpStatPercpu[cpuid].idleStarttime;
                g_mpStatPercpu[cpuid].idleRuntime += runtime;
                g_mpStatPercpu[cpuid].idleStarttime = 0;
            }
            if (taskCB->priority < HIGHTASKPRI) {
                runtime = mpStaticStopTime - g_mpStatPercpu[cpuid].highTaskStarttime;
                g_mpStatPercpu[cpuid].highTaskRuntime += runtime;
                g_mpStatPercpu[cpuid].highTaskStarttime = 0;
            }
        }
    }
    SCHEDULER_UNLOCK(intSave);
    OsMpStaticShow(mpStaticPastTime);

    (VOID)memset_s(g_mpStatPercpu, sizeof(g_mpStatPercpu), 0, sizeof(g_mpStatPercpu));
    g_mpStaticStartTime = 0;
    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
