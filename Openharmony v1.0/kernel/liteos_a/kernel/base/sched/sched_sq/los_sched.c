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

#include "los_base.h"
#include "los_task_pri.h"
#include "los_percpu_pri.h"
#include "los_hw_pri.h"
#include "los_arch_mmu.h"
#include "los_process_pri.h"
#ifdef LOSCFG_KERNEL_CPUP
#include "los_cpup_pri.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

STATIC VOID OsSchedSwitchProcess(LosProcessCB *runProcess, LosProcessCB *newProcess)
{
    if (runProcess == newProcess) {
        return;
    }

#if (LOSCFG_KERNEL_SMP == YES)
    runProcess->processStatus = OS_PROCESS_RUNTASK_COUNT_DEC(runProcess->processStatus);
    newProcess->processStatus = OS_PROCESS_RUNTASK_COUNT_ADD(newProcess->processStatus);

    LOS_ASSERT(!(OS_PROCESS_GET_RUNTASK_COUNT(newProcess->processStatus) > LOSCFG_KERNEL_CORE_NUM));
    if (OS_PROCESS_GET_RUNTASK_COUNT(runProcess->processStatus) == 0) {
#endif
        runProcess->processStatus &= ~OS_PROCESS_STATUS_RUNNING;
        if ((runProcess->threadNumber > 1) && !(runProcess->processStatus & OS_PROCESS_STATUS_READY)) {
            runProcess->processStatus |= OS_PROCESS_STATUS_PEND;
        }
#if (LOSCFG_KERNEL_SMP == YES)
    }
#endif
    LOS_ASSERT(!(newProcess->processStatus & OS_PROCESS_STATUS_PEND));
    newProcess->processStatus |= OS_PROCESS_STATUS_RUNNING;

    if (OsProcessIsUserMode(newProcess)) {
        LOS_ArchMmuContextSwitch(&newProcess->vmSpace->archMmu);
    }

#ifdef LOSCFG_KERNEL_CPUP
    OsProcessCycleEndStart(newProcess->processID, OS_PROCESS_GET_RUNTASK_COUNT(runProcess->processStatus) + 1);
#endif /* LOSCFG_KERNEL_CPUP */

    OsCurrProcessSet(newProcess);

    if ((newProcess->timeSlice == 0) && (newProcess->policy == LOS_SCHED_RR)) {
        newProcess->timeSlice = OS_PROCESS_SCHED_RR_INTERVAL;
    }
}

VOID OsSchedResched(VOID)
{
    LosTaskCB *runTask = NULL;
    LosTaskCB *newTask = NULL;
    LosProcessCB *runProcess = NULL;
    LosProcessCB *newProcess = NULL;

    LOS_ASSERT(LOS_SpinHeld(&g_taskSpin));

    if (!OsPreemptableInSched()) {
        return;
    }

    runTask = OsCurrTaskGet();
    newTask = OsGetTopTask();

    /* always be able to get one task */
    LOS_ASSERT(newTask != NULL);

    if (runTask == newTask) {
        return;
    }

    runTask->taskStatus &= ~OS_TASK_STATUS_RUNNING;
    newTask->taskStatus |= OS_TASK_STATUS_RUNNING;

    runProcess = OS_PCB_FROM_PID(runTask->processID);
    newProcess = OS_PCB_FROM_PID(newTask->processID);

    OsSchedSwitchProcess(runProcess, newProcess);

#if (LOSCFG_KERNEL_SMP == YES)
    /* mask new running task's owner processor */
    runTask->currCpu = OS_TASK_INVALID_CPUID;
    newTask->currCpu = ArchCurrCpuid();
#endif

    (VOID)OsTaskSwitchCheck(runTask, newTask);

#if (LOSCFG_KERNEL_SCHED_STATISTICS == YES)
    OsSchedStatistics(runTask, newTask);
#endif

    if ((newTask->timeSlice == 0) && (newTask->policy == LOS_SCHED_RR)) {
        newTask->timeSlice = LOSCFG_BASE_CORE_TIMESLICE_TIMEOUT;
    }

    OsCurrTaskSet((VOID*)newTask);

    if (OsProcessIsUserMode(newProcess)) {
        OsCurrUserTaskSet(newTask->userArea);
    }

    PRINT_TRACE("cpu%d run process name: (%s) pid: %d status: %x threadMap: %x task name: (%s) tid: %d status: %x ->\n"
                "     new process name: (%s) pid: %d status: %x threadMap: %x task name: (%s) tid: %d status: %x!\n",
                ArchCurrCpuid(),
                runProcess->processName, runProcess->processID, runProcess->processStatus,
                runProcess->threadScheduleMap, runTask->taskName,  runTask->taskID, runTask->taskStatus,
                newProcess->processName, newProcess->processID, newProcess->processStatus,
                newProcess->threadScheduleMap, newTask->taskName, newTask->taskID, newTask->taskStatus);

    /* do the task context switch */
    OsTaskSchedule(newTask, runTask);
}

VOID OsSchedPreempt(VOID)
{
    LosTaskCB *runTask = NULL;
    UINT32 intSave;

    if (!OsPreemptable()) {
        return;
    }

    SCHEDULER_LOCK(intSave);

    /* add run task back to ready queue */
    runTask = OsCurrTaskGet();
    OS_TASK_SCHED_QUEUE_ENQUEUE(runTask, 0);

    /* reschedule to new thread */
    OsSchedResched();

    SCHEDULER_UNLOCK(intSave);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
