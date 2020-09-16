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

#include "los_process_pri.h"
#include "los_task_pri.h"
#include "los_hw_pri.h"
#include "los_sem_pri.h"
#include "los_mp.h"
#include "los_exc.h"
#include "asm/page.h"
#ifdef LOSCFG_FS_VFS
#include "fs/fd_table.h"
#endif
#include "time.h"
#include "user_copy.h"
#include "los_signal.h"
#ifdef LOSCFG_KERNEL_CPUP
#include "los_cpup_pri.h"
#endif
#ifdef LOSCFG_SECURITY_VID
#include "vid_api.h"
#endif
#ifdef LOSCFG_SECURITY_CAPABILITY
#include "capability_api.h"
#endif
#include "los_swtmr_pri.h"
#include "los_vm_map.h"
#include "los_vm_phys.h"
#include "los_vm_syscall.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

LITE_OS_SEC_BSS LosProcessCB *g_runProcess[LOSCFG_KERNEL_CORE_NUM];
LITE_OS_SEC_BSS LosProcessCB *g_processCBArray = NULL;
LITE_OS_SEC_DATA_INIT STATIC LOS_DL_LIST g_freeProcess;
LITE_OS_SEC_DATA_INIT STATIC LOS_DL_LIST g_processRecyleList;
LITE_OS_SEC_BSS UINT32 g_userInitProcess = OS_INVALID_VALUE;
LITE_OS_SEC_BSS UINT32 g_kernelInitProcess = OS_INVALID_VALUE;
LITE_OS_SEC_BSS UINT32 g_kernelIdleProcess = OS_INVALID_VALUE;
LITE_OS_SEC_BSS UINT32 g_processMaxNum;
LITE_OS_SEC_BSS ProcessGroup *g_processGroup = NULL;

LITE_OS_SEC_TEXT_INIT VOID OsTaskSchedQueueDequeue(LosTaskCB *taskCB, UINT16 status)
{
    LosProcessCB *processCB = OS_PCB_FROM_PID(taskCB->processID);
    if (taskCB->taskStatus & OS_TASK_STATUS_READY) {
        OS_TASK_PRI_QUEUE_DEQUEUE(processCB, taskCB);
        taskCB->taskStatus &= ~OS_TASK_STATUS_READY;
    }

    if (processCB->threadScheduleMap != 0) {
        return;
    }

    if (processCB->processStatus & OS_PROCESS_STATUS_READY) {
        processCB->processStatus &= ~OS_PROCESS_STATUS_READY;
        OS_PROCESS_PRI_QUEUE_DEQUEUE(processCB);
    }

#if (LOSCFG_KERNEL_SMP == YES)
    if (OS_PROCESS_GET_RUNTASK_COUNT(processCB->processStatus) == 1) {
#endif
        processCB->processStatus |= status;
#if (LOSCFG_KERNEL_SMP == YES)
    }
#endif
}

STATIC INLINE VOID OsSchedTaskEnqueue(LosProcessCB *processCB, LosTaskCB *taskCB)
{
    if (((taskCB->policy == LOS_SCHED_RR) && (taskCB->timeSlice != 0)) ||
        ((taskCB->taskStatus & OS_TASK_STATUS_RUNNING) && (taskCB->policy == LOS_SCHED_FIFO))) {
        OS_TASK_PRI_QUEUE_ENQUEUE_HEAD(processCB, taskCB);
    } else {
        OS_TASK_PRI_QUEUE_ENQUEUE(processCB, taskCB);
    }
    taskCB->taskStatus |= OS_TASK_STATUS_READY;
}

LITE_OS_SEC_TEXT_INIT VOID OsTaskSchedQueueEnqueue(LosTaskCB *taskCB, UINT16 status)
{
    LosProcessCB *processCB = NULL;

    LOS_ASSERT(!(taskCB->taskStatus & OS_TASK_STATUS_READY));

    processCB = OS_PCB_FROM_PID(taskCB->processID);
    if (!(processCB->processStatus & OS_PROCESS_STATUS_READY)) {
        if (((processCB->policy == LOS_SCHED_RR) && (processCB->timeSlice != 0)) ||
            ((processCB->processStatus & OS_PROCESS_STATUS_RUNNING) && (processCB->policy == LOS_SCHED_FIFO))) {
            OS_PROCESS_PRI_QUEUE_ENQUEUE_HEAD(processCB);
        } else {
            OS_PROCESS_PRI_QUEUE_ENQUEUE(processCB);
        }
        processCB->processStatus &= ~(status | OS_PROCESS_STATUS_PEND);
        processCB->processStatus |= OS_PROCESS_STATUS_READY;
    } else {
        LOS_ASSERT(!(processCB->processStatus & OS_PROCESS_STATUS_PEND));
        LOS_ASSERT((UINTPTR)processCB->pendList.pstNext);
        if ((processCB->timeSlice == 0) && (processCB->policy == LOS_SCHED_RR)) {
            OS_PROCESS_PRI_QUEUE_DEQUEUE(processCB);
            OS_PROCESS_PRI_QUEUE_ENQUEUE(processCB);
        }
    }

    OsSchedTaskEnqueue(processCB, taskCB);
}

STATIC INLINE VOID OsInsertPCBToFreeList(LosProcessCB *processCB)
{
    UINT32 pid = processCB->processID;
    (VOID)memset_s(processCB, sizeof(LosProcessCB), 0, sizeof(LosProcessCB));
    processCB->processID = pid;
    processCB->processStatus = OS_PROCESS_FLAG_UNUSED;
    processCB->timerID = (timer_t)(UINTPTR)MAX_INVALID_TIMER_VID;
    LOS_ListTailInsert(&g_freeProcess, &processCB->pendList);
}

STATIC ProcessGroup *OsCreateProcessGroup(UINT32 pid)
{
    LosProcessCB *processCB = NULL;
    ProcessGroup *group = LOS_MemAlloc(m_aucSysMem1, sizeof(ProcessGroup));
    if (group == NULL) {
        return NULL;
    }

    group->groupID = pid;
    LOS_ListInit(&group->processList);
    LOS_ListInit(&group->exitProcessList);

    processCB = OS_PCB_FROM_PID(pid);
    LOS_ListTailInsert(&group->processList, &processCB->subordinateGroupList);
    processCB->group = group;
    processCB->processStatus |= OS_PROCESS_FLAG_GROUP_LEADER;
    if (g_processGroup != NULL) {
        LOS_ListTailInsert(&g_processGroup->groupList, &group->groupList);
    }

    return group;
}

STATIC VOID OsExitProcessGroup(LosProcessCB *processCB, ProcessGroup **group)
{
    LosProcessCB *groupProcessCB = OS_PCB_FROM_PID(processCB->group->groupID);

    LOS_ListDelete(&processCB->subordinateGroupList);
    if (LOS_ListEmpty(&processCB->group->processList) && LOS_ListEmpty(&processCB->group->exitProcessList)) {
        LOS_ListDelete(&processCB->group->groupList);
        groupProcessCB->processStatus &= ~OS_PROCESS_FLAG_GROUP_LEADER;
        *group = processCB->group;
        if (OsProcessIsUnused(groupProcessCB) && !(groupProcessCB->processStatus & OS_PROCESS_FLAG_EXIT)) {
            LOS_ListDelete(&groupProcessCB->pendList);
            OsInsertPCBToFreeList(groupProcessCB);
        }
    }

    processCB->group = NULL;
}

STATIC ProcessGroup *OsFindProcessGroup(UINT32 gid)
{
    ProcessGroup *group = NULL;
    if (g_processGroup->groupID == gid) {
        return g_processGroup;
    }

    LOS_DL_LIST_FOR_EACH_ENTRY(group, &g_processGroup->groupList, ProcessGroup, groupList) {
        if (group->groupID == gid) {
            return group;
        }
    }

    PRINT_INFO("%s is find group : %u failed!\n", __FUNCTION__, gid);
    return NULL;
}

STATIC LosProcessCB *OsFindGroupExitProcess(ProcessGroup *group, INT32 pid)
{
    LosProcessCB *childCB = NULL;

    LOS_DL_LIST_FOR_EACH_ENTRY(childCB, &(group->exitProcessList), LosProcessCB, subordinateGroupList) {
        if ((childCB->processID == pid) || (pid == OS_INVALID_VALUE)) {
            return childCB;
        }
    }

    PRINT_INFO("%s find exit process : %d failed in group : %u\n", __FUNCTION__, pid, group->groupID);
    return NULL;
}

STATIC UINT32 OsFindChildProcess(const LosProcessCB *processCB, INT32 childPid)
{
    LosProcessCB *childCB = NULL;

    if (childPid < 0) {
        goto ERR;
    }

    LOS_DL_LIST_FOR_EACH_ENTRY(childCB, &(processCB->childrenList), LosProcessCB, siblingList) {
        if (childCB->processID == childPid) {
            return LOS_OK;
        }
    }

ERR:
    PRINT_INFO("%s is find the child : %d failed in parent : %u\n", __FUNCTION__, childPid, processCB->processID);
    return LOS_NOK;
}

STATIC LosProcessCB *OsFindExitChildProcess(const LosProcessCB *processCB, INT32 childPid)
{
    LosProcessCB *exitChild = NULL;

    LOS_DL_LIST_FOR_EACH_ENTRY(exitChild, &(processCB->exitChildList), LosProcessCB, siblingList) {
        if ((childPid == OS_INVALID_VALUE) || (exitChild->processID == childPid)) {
            return exitChild;
        }
    }

    PRINT_INFO("%s is find the exit child : %d failed in parent : %u\n", __FUNCTION__, childPid, processCB->processID);
    return NULL;
}

STATIC INLINE VOID OsWaitWakeTask(LosTaskCB *taskCB, UINT32 wakePID)
{
    taskCB->waitID = wakePID;
    OsTaskWake(taskCB);
#if (LOSCFG_KERNEL_SMP == YES)
    LOS_MpSchedule(OS_MP_CPU_ALL);
#endif
}

STATIC BOOL OsWaitWakeSpecifiedProcess(LOS_DL_LIST *head, const LosProcessCB *processCB, LOS_DL_LIST **anyList)
{
    LOS_DL_LIST *list = head;
    LosTaskCB *taskCB = NULL;
    UINT32 pid = 0;
    BOOL find = FALSE;

    while (list->pstNext != head) {
        taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(list));
        if ((taskCB->waitFlag == OS_PROCESS_WAIT_PRO) && (taskCB->waitID == processCB->processID)) {
            if (pid == 0) {
                pid = processCB->processID;
                find = TRUE;
            } else {
                pid = OS_INVALID_VALUE;
            }

            OsWaitWakeTask(taskCB, pid);
            continue;
        }

        if (taskCB->waitFlag != OS_PROCESS_WAIT_PRO) {
            *anyList = list;
            break;
        }
        list = list->pstNext;
    }

    return find;
}

STATIC VOID OsWaitCheckAndWakeParentProcess(LosProcessCB *parentCB, const LosProcessCB *processCB)
{
    LOS_DL_LIST *head = &parentCB->waitList;
    LOS_DL_LIST *list = NULL;
    LosTaskCB *taskCB = NULL;
    BOOL findSpecified = FALSE;

    if (LOS_ListEmpty(&parentCB->waitList)) {
        return;
    }

    findSpecified = OsWaitWakeSpecifiedProcess(head, processCB, &list);
    if (findSpecified == TRUE) {
        /* No thread is waiting for any child process to finish */
        if (LOS_ListEmpty(&parentCB->waitList)) {
            return;
        } else if (!LOS_ListEmpty(&parentCB->childrenList)) {
            /* Other child processes exist, and other threads that are waiting
             * for the child to finish continue to wait
             */
            return;
        }
    }

    /* Waiting threads are waiting for a specified child process to finish */
    if (list == NULL) {
        return;
    }

    /* No child processes exist and all waiting threads are awakened */
    if (findSpecified == TRUE) {
        while (list->pstNext != head) {
            taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(list));
            OsWaitWakeTask(taskCB, OS_INVALID_VALUE);
        }
        return;
    }

    while (list->pstNext != head) {
        taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(list));
        if (taskCB->waitFlag == OS_PROCESS_WAIT_GID) {
            if (taskCB->waitID != processCB->group->groupID) {
                list = list->pstNext;
                continue;
            }
        }

        if (findSpecified == FALSE) {
            OsWaitWakeTask(taskCB, processCB->processID);
            findSpecified = TRUE;
        } else {
            OsWaitWakeTask(taskCB, OS_INVALID_VALUE);
        }

        if (!LOS_ListEmpty(&parentCB->childrenList)) {
            break;
        }
    }

    return;
}

LITE_OS_SEC_TEXT VOID OsProcessResourcesToFree(LosProcessCB *processCB)
{
    if (!(processCB->processStatus & (OS_PROCESS_STATUS_INIT | OS_PROCESS_STATUS_RUNNING))) {
        PRINT_ERR("The process(%d) has no permission to release process(%d) resources!\n",
                  OsCurrProcessGet()->processID, processCB->processID);
    }

#ifdef LOSCFG_FS_VFS
    if (OsProcessIsUserMode(processCB)) {
        delete_files(processCB, processCB->files);
    }
    processCB->files = NULL;
#endif

#ifdef LOSCFG_SECURITY_CAPABILITY
    if (processCB->user != NULL) {
        (VOID)LOS_MemFree(m_aucSysMem1, processCB->user);
        processCB->user = NULL;
    }
#endif

    OsSwtmrRecycle(processCB->processID);
    processCB->timerID = (timer_t)(UINTPTR)MAX_INVALID_TIMER_VID;

#ifdef LOSCFG_SECURITY_VID
    if (processCB->timerIdMap.bitMap != NULL) {
        VidMapDestroy(processCB);
        processCB->timerIdMap.bitMap = NULL;
    }
#endif

#if (LOSCFG_KERNEL_LITEIPC == YES)
    if (OsProcessIsUserMode(processCB)) {
        LiteIpcPoolDelete(&(processCB->ipcInfo));
        (VOID)memset_s(&(processCB->ipcInfo), sizeof(ProcIpcInfo), 0, sizeof(ProcIpcInfo));
    }
#endif
}

LITE_OS_SEC_TEXT STATIC VOID OsRecycleZombiesProcess(LosProcessCB *childCB, ProcessGroup **group)
{
    OsExitProcessGroup(childCB, group);
    LOS_ListDelete(&childCB->siblingList);
    if (childCB->processStatus & OS_PROCESS_STATUS_ZOMBIES) {
        childCB->processStatus &= ~OS_PROCESS_STATUS_ZOMBIES;
        childCB->processStatus |= OS_PROCESS_FLAG_UNUSED;
    }

    LOS_ListDelete(&childCB->pendList);
    if (childCB->processStatus & OS_PROCESS_FLAG_EXIT) {
        LOS_ListHeadInsert(&g_processRecyleList, &childCB->pendList);
    } else if (childCB->processStatus & OS_PROCESS_FLAG_GROUP_LEADER) {
        LOS_ListTailInsert(&g_processRecyleList, &childCB->pendList);
    } else {
        OsInsertPCBToFreeList(childCB);
    }
}

STATIC VOID OsDealAliveChildProcess(LosProcessCB *processCB)
{
    UINT32 parentID;
    LosProcessCB *childCB = NULL;
    LosProcessCB *parentCB = NULL;
    LOS_DL_LIST *nextList = NULL;
    LOS_DL_LIST *childHead = NULL;

    if (!LOS_ListEmpty(&processCB->childrenList)) {
        childHead = processCB->childrenList.pstNext;
        LOS_ListDelete(&(processCB->childrenList));
        if (OsProcessIsUserMode(processCB)) {
            parentID = g_userInitProcess;
        } else {
            parentID = g_kernelInitProcess;
        }

        for (nextList = childHead; ;) {
            childCB = OS_PCB_FROM_SIBLIST(nextList);
            childCB->parentProcessID = parentID;
            nextList = nextList->pstNext;
            if (nextList == childHead) {
                break;
            }
        }

        parentCB = OS_PCB_FROM_PID(parentID);
        LOS_ListTailInsertList(&parentCB->childrenList, childHead);
    }

    return;
}

STATIC VOID OsChildProcessResourcesFree(const LosProcessCB *processCB)
{
    LosProcessCB *childCB = NULL;
    ProcessGroup *group = NULL;

    while (!LOS_ListEmpty(&((LosProcessCB *)processCB)->exitChildList)) {
        childCB = LOS_DL_LIST_ENTRY(processCB->exitChildList.pstNext, LosProcessCB, siblingList);
        OsRecycleZombiesProcess(childCB, &group);
        (VOID)LOS_MemFree(m_aucSysMem1, group);
    }
}

STATIC VOID OsProcessNaturalExit(LosTaskCB *runTask, UINT32 status)
{
    LosProcessCB *processCB = OS_PCB_FROM_PID(runTask->processID);
    LosProcessCB *parentCB = NULL;

    LOS_ASSERT(!(processCB->threadScheduleMap != 0));
    LOS_ASSERT(processCB->processStatus & OS_PROCESS_STATUS_RUNNING);

    OsChildProcessResourcesFree(processCB);

#ifdef LOSCFG_KERNEL_CPUP
    OsCpupClean(processCB->processID);
#endif

    /* is a child process */
    if (processCB->parentProcessID != OS_INVALID_VALUE) {
        parentCB = OS_PCB_FROM_PID(processCB->parentProcessID);
        LOS_ListDelete(&processCB->siblingList);
        if (!OsProcessExitCodeSignalIsSet(processCB)) {
            OsProcessExitCodeSet(processCB, status);
        }
        LOS_ListTailInsert(&parentCB->exitChildList, &processCB->siblingList);
        LOS_ListDelete(&processCB->subordinateGroupList);
        LOS_ListTailInsert(&processCB->group->exitProcessList, &processCB->subordinateGroupList);

        OsWaitCheckAndWakeParentProcess(parentCB, processCB);

        OsDealAliveChildProcess(processCB);

        processCB->processStatus |= OS_PROCESS_STATUS_ZOMBIES;

        (VOID)OsKill(processCB->parentProcessID, SIGCHLD, OS_KERNEL_KILL_PERMISSION);
        LOS_ListHeadInsert(&g_processRecyleList, &processCB->pendList);
        OsRunTaskToDelete(runTask);
        return;
    }

    LOS_Panic("pid : %u is the root process exit!\n", processCB->processID);
    return;
}

LITE_OS_SEC_TEXT_INIT UINT32 OsProcessInit(VOID)
{
    UINT32 index;
    UINT32 size;

    g_processMaxNum = LOSCFG_BASE_CORE_PROCESS_LIMIT;
    size = g_processMaxNum * sizeof(LosProcessCB);

    g_processCBArray = (LosProcessCB *)LOS_MemAlloc(m_aucSysMem1, size);
    if (g_processCBArray == NULL) {
        return LOS_NOK;
    }
    (VOID)memset_s(g_processCBArray, size, 0, size);

    LOS_ListInit(&g_freeProcess);
    LOS_ListInit(&g_processRecyleList);

    for (index = 0; index < g_processMaxNum; index++) {
        g_processCBArray[index].processID = index;
        g_processCBArray[index].processStatus = OS_PROCESS_FLAG_UNUSED;
        LOS_ListTailInsert(&g_freeProcess, &g_processCBArray[index].pendList);
    }

    g_userInitProcess = 1; /* 1: The root process ID of the user-mode process is fixed at 1 */
    LOS_ListDelete(&g_processCBArray[g_userInitProcess].pendList);

    g_kernelInitProcess = 2; /* 2: The root process ID of the kernel-mode process is fixed at 2 */
    LOS_ListDelete(&g_processCBArray[g_kernelInitProcess].pendList);

    return LOS_OK;
}

STATIC UINT32 OsCreateIdleProcess(VOID)
{
    UINT32 ret;
    CHAR *idleName = "Idle";
    LosProcessCB *idleProcess = NULL;
    Percpu *perCpu = OsPercpuGet();
    UINT32 *idleTaskID = &perCpu->idleTaskID;

    ret = OsCreateResourceFreeTask();
    if (ret != LOS_OK) {
        return ret;
    }

    ret = LOS_Fork(CLONE_FILES, "KIdle", (TSK_ENTRY_FUNC)OsIdleTask, LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE);
    if (ret < 0) {
        return LOS_NOK;
    }
    g_kernelIdleProcess = (UINT32)ret;

    idleProcess = OS_PCB_FROM_PID(g_kernelIdleProcess);
    *idleTaskID = idleProcess->threadGroupID;
    OS_TCB_FROM_TID(*idleTaskID)->taskStatus |= OS_TASK_FLAG_SYSTEM_TASK;
#if (LOSCFG_KERNEL_SMP == YES)
    OS_TCB_FROM_TID(*idleTaskID)->cpuAffiMask = CPUID_TO_AFFI_MASK(ArchCurrCpuid());
#endif
    (VOID)memset_s(OS_TCB_FROM_TID(*idleTaskID)->taskName, OS_TCB_NAME_LEN, 0, OS_TCB_NAME_LEN);
    (VOID)memcpy_s(OS_TCB_FROM_TID(*idleTaskID)->taskName, OS_TCB_NAME_LEN, idleName, strlen(idleName));
    return LOS_OK;
}

LITE_OS_SEC_TEXT VOID OsProcessCBRecyleToFree(VOID)
{
    UINT32 intSave;
    LosVmSpace *space = NULL;
    LosProcessCB *processCB = NULL;

    SCHEDULER_LOCK(intSave);
    while (!LOS_ListEmpty(&g_processRecyleList)) {
        processCB = OS_PCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&g_processRecyleList));
        if (!(processCB->processStatus & OS_PROCESS_FLAG_EXIT)) {
            break;
        }
        SCHEDULER_UNLOCK(intSave);

        OsTaskCBRecyleToFree();

        SCHEDULER_LOCK(intSave);
        processCB->processStatus &= ~OS_PROCESS_FLAG_EXIT;
        if (OsProcessIsUserMode(processCB)) {
            space = processCB->vmSpace;
        }
        processCB->vmSpace = NULL;
        /* OS_PROCESS_FLAG_GROUP_LEADER: The lead process group cannot be recycled without destroying the PCB.
         * !OS_PROCESS_FLAG_UNUSED: Parent process does not reclaim child process resources.
         */
        LOS_ListDelete(&processCB->pendList);
        if ((processCB->processStatus & OS_PROCESS_FLAG_GROUP_LEADER) ||
            (processCB->processStatus & OS_PROCESS_STATUS_ZOMBIES)) {
            LOS_ListTailInsert(&g_processRecyleList, &processCB->pendList);
        } else {
            /* Clear the bottom 4 bits of process status */
            OsInsertPCBToFreeList(processCB);
        }
        SCHEDULER_UNLOCK(intSave);

        (VOID)LOS_VmSpaceFree(space);

        SCHEDULER_LOCK(intSave);
    }

    SCHEDULER_UNLOCK(intSave);
}

STATIC LosProcessCB *OsGetFreePCB(VOID)
{
    LosProcessCB *processCB = NULL;
    UINT32 intSave;

    SCHEDULER_LOCK(intSave);
    if (LOS_ListEmpty(&g_freeProcess)) {
        SCHEDULER_UNLOCK(intSave);
        PRINT_ERR("No idle PCB in the system!\n");
        return NULL;
    }

    processCB = OS_PCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&g_freeProcess));
    LOS_ListDelete(&processCB->pendList);
    SCHEDULER_UNLOCK(intSave);

    return processCB;
}

STATIC VOID OsDeInitPCB(LosProcessCB *processCB)
{
    UINT32 intSave;
    ProcessGroup *group = NULL;

    if (processCB == NULL) {
        return;
    }

    OsProcessResourcesToFree(processCB);

    SCHEDULER_LOCK(intSave);
    if (processCB->parentProcessID != OS_INVALID_VALUE) {
        LOS_ListDelete(&processCB->siblingList);
        processCB->parentProcessID = OS_INVALID_VALUE;
    }

    if (processCB->group != NULL) {
        OsExitProcessGroup(processCB, &group);
    }

    processCB->processStatus &= ~OS_PROCESS_STATUS_INIT;
    processCB->processStatus |= OS_PROCESS_FLAG_EXIT;
    LOS_ListHeadInsert(&g_processRecyleList, &processCB->pendList);
    SCHEDULER_UNLOCK(intSave);

    (VOID)LOS_MemFree(m_aucSysMem1, group);
    OsWriteResourceEvent(OS_RESOURCE_EVENT_FREE);
    return;
}

STATIC UINT32 OsSetProcessName(LosProcessCB *processCB, const CHAR *name)
{
    errno_t errRet;
    UINT32 len;

    if (name != NULL) {
        len = strlen(name);
        if (len >= OS_PCB_NAME_LEN) {
            len = OS_PCB_NAME_LEN - 1; /* 1: Truncate, reserving the termination operator for character turns */
        }
        errRet = memcpy_s(processCB->processName, sizeof(CHAR) * OS_PCB_NAME_LEN, name, len);
        if (errRet != EOK) {
            processCB->processName[0] = '\0';
            return LOS_NOK;
        }
        processCB->processName[len] = '\0';
        return LOS_OK;
    }

    (VOID)memset_s(processCB->processName, sizeof(CHAR) * OS_PCB_NAME_LEN, 0, sizeof(CHAR) * OS_PCB_NAME_LEN);
    switch (processCB->processMode) {
        case OS_KERNEL_MODE:
            (VOID)snprintf_s(processCB->processName, sizeof(CHAR) * OS_PCB_NAME_LEN,
                             (sizeof(CHAR) * OS_PCB_NAME_LEN) - 1, "KerProcess%u", processCB->processID);
            break;
        default:
            (VOID)snprintf_s(processCB->processName, sizeof(CHAR) * OS_PCB_NAME_LEN,
                             (sizeof(CHAR) * OS_PCB_NAME_LEN) - 1, "UserProcess%u", processCB->processID);
            break;
    }
    return LOS_OK;
}

STATIC UINT32 OsInitPCB(LosProcessCB *processCB, UINT32 mode, UINT16 priority, UINT16 policy, const CHAR *name)
{
    UINT32 count;
    LosVmSpace *space = NULL;
    LosVmPage *vmPage = NULL;
    status_t status;
    BOOL retVal = FALSE;

    processCB->processMode = mode;
    processCB->processStatus = OS_PROCESS_STATUS_INIT;
    processCB->parentProcessID = OS_INVALID_VALUE;
    processCB->threadGroupID = OS_INVALID_VALUE;
    processCB->priority = priority;
    processCB->policy = policy;
    processCB->umask = OS_PROCESS_DEFAULT_UMASK;
    processCB->timerID = (timer_t)(UINTPTR)MAX_INVALID_TIMER_VID;

    LOS_ListInit(&processCB->threadSiblingList);
    LOS_ListInit(&processCB->childrenList);
    LOS_ListInit(&processCB->exitChildList);
    LOS_ListInit(&(processCB->waitList));

    for (count = 0; count < OS_PRIORITY_QUEUE_NUM; ++count) {
        LOS_ListInit(&processCB->threadPriQueueList[count]);
    }

    if (OsProcessIsUserMode(processCB)) {
        space = LOS_MemAlloc(m_aucSysMem0, sizeof(LosVmSpace));
        if (space == NULL) {
            PRINT_ERR("%s %d, alloc space failed\n", __FUNCTION__, __LINE__);
            return LOS_ENOMEM;
        }
        VADDR_T *ttb = LOS_PhysPagesAllocContiguous(1);
        if (ttb == NULL) {
            PRINT_ERR("%s %d, alloc ttb or space failed\n", __FUNCTION__, __LINE__);
            (VOID)LOS_MemFree(m_aucSysMem0, space);
            return LOS_ENOMEM;
        }
        (VOID)memset_s(ttb, PAGE_SIZE, 0, PAGE_SIZE);
        retVal = OsUserVmSpaceInit(space, ttb);
        vmPage = OsVmVaddrToPage(ttb);
        if ((retVal == FALSE) || (vmPage == NULL)) {
            PRINT_ERR("create space failed! ret: %d, vmPage: %#x\n", retVal, vmPage);
            processCB->processStatus = OS_PROCESS_FLAG_UNUSED;
            (VOID)LOS_MemFree(m_aucSysMem0, space);
            LOS_PhysPagesFreeContiguous(ttb, 1);
            return LOS_EAGAIN;
        }
        processCB->vmSpace = space;
        LOS_ListAdd(&processCB->vmSpace->archMmu.ptList, &(vmPage->node));
    } else {
        processCB->vmSpace = LOS_GetKVmSpace();
    }

#ifdef LOSCFG_SECURITY_VID
    status = VidMapListInit(processCB);
    if (status != LOS_OK) {
        PRINT_ERR("VidMapListInit failed!\n");
        return LOS_ENOMEM;
    }
#endif
#ifdef LOSCFG_SECURITY_CAPABILITY
    OsInitCapability(processCB);
#endif

    if (OsSetProcessName(processCB, name) != LOS_OK) {
        return LOS_ENOMEM;
    }

    return LOS_OK;
}

#ifdef LOSCFG_SECURITY_CAPABILITY
STATIC User *OsCreateUser(UINT32 userID, UINT32 gid, UINT32 size)
{
    User *user = LOS_MemAlloc(m_aucSysMem1, sizeof(User) + (size - 1) * sizeof(UINT32));
    if (user == NULL) {
        return NULL;
    }

    user->userID = userID;
    user->effUserID = userID;
    user->gid = gid;
    user->effGid = gid;
    user->groupNumber = size;
    user->groups[0] = gid;
    return user;
}

LITE_OS_SEC_TEXT BOOL LOS_CheckInGroups(UINT32 gid)
{
    UINT32 intSave;
    UINT32 count;
    User *user = NULL;

    SCHEDULER_LOCK(intSave);
    user = OsCurrUserGet();
    for (count = 0; count < user->groupNumber; count++) {
        if (user->groups[count] == gid) {
            SCHEDULER_UNLOCK(intSave);
            return TRUE;
        }
    }

    SCHEDULER_UNLOCK(intSave);
    return FALSE;
}
#endif

LITE_OS_SEC_TEXT INT32 LOS_GetUserID(VOID)
{
#ifdef LOSCFG_SECURITY_CAPABILITY
    UINT32 intSave;
    INT32 uid;

    SCHEDULER_LOCK(intSave);
    uid = (INT32)OsCurrUserGet()->userID;
    SCHEDULER_UNLOCK(intSave);
    return uid;
#else
    return 0;
#endif
}

LITE_OS_SEC_TEXT INT32 LOS_GetGroupID(VOID)
{
#ifdef LOSCFG_SECURITY_CAPABILITY
    UINT32 intSave;
    INT32 gid;

    SCHEDULER_LOCK(intSave);
    gid = (INT32)OsCurrUserGet()->gid;
    SCHEDULER_UNLOCK(intSave);

    return gid;
#else
    return 0;
#endif
}

STATIC UINT32 OsProcessCreateInit(LosProcessCB *processCB, UINT32 flags, const CHAR *name, UINT16 priority)
{
    ProcessGroup *group = NULL;
    UINT32 ret = OsInitPCB(processCB, flags, priority, LOS_SCHED_RR, name);
    if (ret != LOS_OK) {
        goto EXIT;
    }

#if (LOSCFG_KERNEL_LITEIPC == YES)
    if (OsProcessIsUserMode(processCB)) {
        ret = LiteIpcPoolInit(&(processCB->ipcInfo));
        if (ret != LOS_OK) {
            ret = LOS_ENOMEM;
            PRINT_ERR("LiteIpcPoolInit failed!\n");
            goto EXIT;
        }
    }
#endif

#ifdef LOSCFG_FS_VFS
    processCB->files = alloc_files();
    if (processCB->files == NULL) {
        ret = LOS_ENOMEM;
        goto EXIT;
    }
#endif

    group = OsCreateProcessGroup(processCB->processID);
    if (group == NULL) {
        ret = LOS_ENOMEM;
        goto EXIT;
    }

#ifdef LOSCFG_SECURITY_CAPABILITY
    processCB->user = OsCreateUser(0, 0, 1);
    if (processCB->user == NULL) {
        ret = LOS_ENOMEM;
        goto EXIT;
    }
#endif

#ifdef LOSCFG_KERNEL_CPUP
    OsCpupSet(processCB->processID);
#endif

    return LOS_OK;

EXIT:
    OsDeInitPCB(processCB);
    return ret;
}

LITE_OS_SEC_TEXT_INIT UINT32 OsKernelInitProcess(VOID)
{
    LosProcessCB *processCB = NULL;
    UINT32 ret;

    ret = OsProcessInit();
    if (ret != LOS_OK) {
        return ret;
    }

    processCB = OS_PCB_FROM_PID(g_kernelInitProcess);
    ret = OsProcessCreateInit(processCB, OS_KERNEL_MODE, "KProcess", 0);
    if (ret != LOS_OK) {
        return ret;
    }

    processCB->processStatus &= ~OS_PROCESS_STATUS_INIT;
    g_processGroup = processCB->group;
    LOS_ListInit(&g_processGroup->groupList);
    OsCurrProcessSet(processCB);

    return OsCreateIdleProcess();
}

LITE_OS_SEC_TEXT UINT32 LOS_ProcessYield(VOID)
{
    UINT32 count;
    UINT32 intSave;
    LosProcessCB *runProcessCB = NULL;

    if (OS_INT_ACTIVE) {
        return LOS_ERRNO_TSK_YIELD_IN_INT;
    }

    if (!OsPreemptable()) {
        return LOS_ERRNO_TSK_YIELD_IN_LOCK;
    }

    SCHEDULER_LOCK(intSave);
    runProcessCB = OsCurrProcessGet();

    /* reset timeslice of yeilded task */
    runProcessCB->timeSlice = 0;

    count = OS_PROCESS_PRI_QUEUE_SIZE(runProcessCB);
    if (count > 0) {
        if (runProcessCB->processStatus & OS_PROCESS_STATUS_READY) {
            OS_PROCESS_PRI_QUEUE_DEQUEUE(runProcessCB);
        }
        OS_PROCESS_PRI_QUEUE_ENQUEUE(runProcessCB);
        runProcessCB->processStatus |= OS_PROCESS_STATUS_READY;
        OsSchedTaskEnqueue(runProcessCB, OsCurrTaskGet());
    } else {
        SCHEDULER_UNLOCK(intSave);
        return LOS_OK;
    }

    OsSchedResched();
    SCHEDULER_UNLOCK(intSave);
    return LOS_OK;
}

STATIC INLINE INT32 OsProcessSchedlerParamCheck(INT32 which, INT32 pid, UINT16 prio, UINT16 policy)
{
    if (OS_PID_CHECK_INVALID(pid)) {
        return LOS_EINVAL;
    }

    if (which != LOS_PRIO_PROCESS) {
        return LOS_EOPNOTSUPP;
    }

    if (prio > OS_PROCESS_PRIORITY_LOWEST) {
        return LOS_EINVAL;
    }

    if ((policy != LOS_SCHED_FIFO) && (policy != LOS_SCHED_RR)) {
        return LOS_EOPNOTSUPP;
    }

    return LOS_OK;
}

#ifdef LOSCFG_SECURITY_CAPABILITY
STATIC BOOL OsProcessCapPermitCheck(const LosProcessCB *processCB, UINT16 prio)
{
    LosProcessCB *runProcess = OsCurrProcessGet();

    /* always trust kernel process */
    if (!OsProcessIsUserMode(runProcess)) {
        return TRUE;
    }

    /* user mode process can reduce the priority of itself */
    if ((runProcess->processID == processCB->processID) && (prio > processCB->priority)) {
        return TRUE;
    }

    /* user mode process with privilege of CAP_SCHED_SETPRIORITY can change the priority */
    if (IsCapPermit(CAP_SCHED_SETPRIORITY)) {
        return TRUE;
    }
    return FALSE;
}
#endif

LITE_OS_SEC_TEXT INT32 OsSetProcessScheduler(INT32 which, INT32 pid, UINT16 prio, UINT16 policy, BOOL policyFlag)
{
    LosProcessCB *processCB = NULL;
    UINT32 intSave;
    INT32 ret;

    ret = OsProcessSchedlerParamCheck(which, pid, prio, policy);
    if (ret != LOS_OK) {
        return -ret;
    }

    SCHEDULER_LOCK(intSave);
    processCB = OS_PCB_FROM_PID(pid);
    if (OsProcessIsInactive(processCB)) {
        ret = LOS_ESRCH;
        goto EXIT;
    }

#ifdef LOSCFG_SECURITY_CAPABILITY
    if (!OsProcessCapPermitCheck(processCB, prio)) {
        ret = LOS_EPERM;
        goto EXIT;
    }
#endif

    if (policyFlag == TRUE) {
        if (policy == LOS_SCHED_FIFO) {
            processCB->timeSlice = 0;
        }
        processCB->policy = policy;
    }

    if (processCB->processStatus & OS_PROCESS_STATUS_READY) {
        OS_PROCESS_PRI_QUEUE_DEQUEUE(processCB);
        processCB->priority = prio;
        OS_PROCESS_PRI_QUEUE_ENQUEUE(processCB);
    } else {
        processCB->priority = prio;
        if (!(processCB->processStatus & OS_PROCESS_STATUS_RUNNING)) {
            ret = LOS_OK;
            goto EXIT;
        }
    }

    SCHEDULER_UNLOCK(intSave);

    LOS_MpSchedule(OS_MP_CPU_ALL);
    if (OS_SCHEDULER_ACTIVE) {
        LOS_Schedule();
    }
    return LOS_OK;

EXIT:
    SCHEDULER_UNLOCK(intSave);
    return -ret;
}

LITE_OS_SEC_TEXT INT32 LOS_SetProcessScheduler(INT32 pid, UINT16 policy, UINT16 prio)
{
    return OsSetProcessScheduler(LOS_PRIO_PROCESS, pid, prio, policy, TRUE);
}

LITE_OS_SEC_TEXT INT32 LOS_GetProcessScheduler(INT32 pid)
{
    LosProcessCB *processCB = NULL;
    UINT32 intSave;
    INT32 policy;

    if (OS_PID_CHECK_INVALID(pid)) {
        return -LOS_EINVAL;
    }

    SCHEDULER_LOCK(intSave);
    processCB = OS_PCB_FROM_PID(pid);
    if (OsProcessIsUnused(processCB)) {
        policy = -LOS_ESRCH;
        goto OUT;
    }

    policy = processCB->policy;

OUT:
    SCHEDULER_UNLOCK(intSave);
    return policy;
}

LITE_OS_SEC_TEXT INT32 LOS_SetProcessPriority(INT32 pid, UINT16 prio)
{
    return OsSetProcessScheduler(LOS_PRIO_PROCESS, pid, prio, LOS_SCHED_RR, FALSE);
}

LITE_OS_SEC_TEXT INT32 OsGetProcessPriority(INT32 which, INT32 pid)
{
    LosProcessCB *processCB = NULL;
    INT32 prio;
    UINT32 intSave;
    (VOID)which;

    if (OS_PID_CHECK_INVALID(pid)) {
        return -LOS_EINVAL;
    }

    if (which != LOS_PRIO_PROCESS) {
        return -LOS_EOPNOTSUPP;
    }

    SCHEDULER_LOCK(intSave);
    processCB = OS_PCB_FROM_PID(pid);
    if (OsProcessIsUnused(processCB)) {
        prio = -LOS_ESRCH;
        goto OUT;
    }

    prio = (INT32)processCB->priority;

OUT:
    SCHEDULER_UNLOCK(intSave);
    return prio;
}

LITE_OS_SEC_TEXT INT32 LOS_GetProcessPriority(INT32 pid)
{
    return OsGetProcessPriority(LOS_PRIO_PROCESS, pid);
}

LITE_OS_SEC_TEXT VOID OsWaitSignalToWakeProcess(LosProcessCB *processCB)
{
    LosTaskCB *taskCB = NULL;

    if (processCB == NULL) {
        return;
    }

    /* only suspend process can continue */
    if (!(processCB->processStatus & OS_PROCESS_STATUS_PEND)) {
        return;
    }

    if (!LOS_ListEmpty(&processCB->waitList)) {
        taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&processCB->waitList));
        OsWaitWakeTask(taskCB, OS_INVALID_VALUE);
    }

    return;
}

STATIC VOID OsWaitInsertWaitListInOrder(LosTaskCB *runTask, LosProcessCB *processCB)
{
    LOS_DL_LIST *head = &processCB->waitList;
    LOS_DL_LIST *list = head;
    LosTaskCB *taskCB = NULL;

    (VOID)OsTaskWait(&processCB->waitList, LOS_WAIT_FOREVER, FALSE);
    LOS_ListDelete(&runTask->pendList);
    if (runTask->waitFlag == OS_PROCESS_WAIT_PRO) {
        LOS_ListHeadInsert(&processCB->waitList, &runTask->pendList);
        return;
    } else if (runTask->waitFlag == OS_PROCESS_WAIT_GID) {
        while (list->pstNext != head) {
            taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(list));
            if (taskCB->waitFlag == OS_PROCESS_WAIT_PRO) {
                list = list->pstNext;
                continue;
            }
            break;
        }
        LOS_ListHeadInsert(list, &runTask->pendList);
        return;
    }

    while (list->pstNext != head) {
        taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(list));
        if (taskCB->waitFlag != OS_PROCESS_WAIT_ANY) {
            list = list->pstNext;
            continue;
        }
        break;
    }

    LOS_ListHeadInsert(list, &runTask->pendList);
    return;
}

STATIC UINT32 OsWaitSetFlag(const LosProcessCB *processCB, INT32 pid, LosProcessCB **child)
{
    LosProcessCB *childCB = NULL;
    ProcessGroup *group = NULL;
    LosTaskCB *runTask = OsCurrTaskGet();
    UINT32 ret;

    if (pid > 0) {
        /* Wait for the child process whose process number is pid. */
        childCB = OsFindExitChildProcess(processCB, pid);
        if (childCB != NULL) {
            goto WAIT_BACK;
        }

        ret = OsFindChildProcess(processCB, pid);
        if (ret != LOS_OK) {
            return LOS_ECHILD;
        }
        runTask->waitFlag = OS_PROCESS_WAIT_PRO;
        runTask->waitID = pid;
    } else if (pid == 0) {
        /* Wait for any child process in the same process group */
        childCB = OsFindGroupExitProcess(processCB->group, OS_INVALID_VALUE);
        if (childCB != NULL) {
            goto WAIT_BACK;
        }
        runTask->waitID = processCB->group->groupID;
        runTask->waitFlag = OS_PROCESS_WAIT_GID;
    } else if (pid == -1) {
        /* Wait for any child process */
        childCB = OsFindExitChildProcess(processCB, OS_INVALID_VALUE);
        if (childCB != NULL) {
            goto WAIT_BACK;
        }
        runTask->waitID = pid;
        runTask->waitFlag = OS_PROCESS_WAIT_ANY;
    } else { /* pid < -1 */
        /* Wait for any child process whose group number is the pid absolute value. */
        group = OsFindProcessGroup(-pid);
        if (group == NULL) {
            return LOS_ECHILD;
        }

        childCB = OsFindGroupExitProcess(group, OS_INVALID_VALUE);
        if (childCB != NULL) {
            goto WAIT_BACK;
        }

        runTask->waitID = -pid;
        runTask->waitFlag = OS_PROCESS_WAIT_GID;
    }

WAIT_BACK:
    *child = childCB;
    return LOS_OK;
}

STATIC INT32 OsWaitRecycleChildPorcess(const LosProcessCB *childCB, UINT32 intSave, INT32 *status)
{
    ProcessGroup *group = NULL;
    UINT32 pid = childCB->processID;
    UINT16 mode = childCB->processMode;
    INT32 exitCode = childCB->exitCode;

    OsRecycleZombiesProcess((LosProcessCB *)childCB, &group);
    SCHEDULER_UNLOCK(intSave);

    if (status != NULL) {
        if (mode == OS_USER_MODE) {
            (VOID)LOS_ArchCopyToUser((VOID *)status, (const VOID *)(&(exitCode)), sizeof(INT32));
        } else {
            *status = exitCode;
        }
    }

    (VOID)LOS_MemFree(m_aucSysMem1, group);
    return pid;
}

STATIC INT32 OsWaitChildProcessCheck(LosProcessCB *processCB, INT32 pid, LosProcessCB **childCB)
{
    if (LOS_ListEmpty(&(processCB->childrenList)) && LOS_ListEmpty(&(processCB->exitChildList))) {
        return LOS_ECHILD;
    }

    return OsWaitSetFlag(processCB, pid, childCB);
}

STATIC UINT32 OsWaitOptionsCheck(UINT32 options)
{
    UINT32 flag = LOS_WAIT_WNOHANG | LOS_WAIT_WUNTRACED | LOS_WAIT_WCONTINUED;

    flag = ~flag & options;
    if (flag != 0) {
        return LOS_EINVAL;
    }

    if ((options & (LOS_WAIT_WCONTINUED | LOS_WAIT_WUNTRACED)) != 0) {
        return LOS_EOPNOTSUPP;
    }

    if (OS_INT_ACTIVE) {
        return LOS_EINTR;
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT INT32 LOS_Wait(INT32 pid, USER INT32 *status, UINT32 options, VOID *rusage)
{
    (VOID)rusage;
    UINT32 ret;
    UINT32 intSave;
    LosProcessCB *childCB = NULL;
    LosProcessCB *processCB = NULL;
    LosTaskCB *runTask = NULL;

    ret = OsWaitOptionsCheck(options);
    if (ret != LOS_OK) {
        return -ret;
    }

    SCHEDULER_LOCK(intSave);
    processCB = OsCurrProcessGet();
    runTask = OsCurrTaskGet();

    ret = OsWaitChildProcessCheck(processCB, pid, &childCB);
    if (ret != LOS_OK) {
        pid = -ret;
        goto ERROR;
    }

    if (childCB != NULL) {
        return OsWaitRecycleChildPorcess(childCB, intSave, status);
    }

    if ((options & LOS_WAIT_WNOHANG) != 0) {
        runTask->waitFlag = 0;
        pid = 0;
        goto ERROR;
    }

    OsWaitInsertWaitListInOrder(runTask, processCB);

    OsSchedResched();

    runTask->waitFlag = 0;
    if (runTask->waitID == OS_INVALID_VALUE) {
        pid = -LOS_ECHILD;
        goto ERROR;
    }

    childCB = OS_PCB_FROM_PID(runTask->waitID);
    if (!(childCB->processStatus & OS_PROCESS_STATUS_ZOMBIES)) {
        pid = -LOS_ESRCH;
        goto ERROR;
    }

    return OsWaitRecycleChildPorcess(childCB, intSave, status);

ERROR:
    SCHEDULER_UNLOCK(intSave);
    return pid;
}

STATIC UINT32 OsSetProcessGroupCheck(const LosProcessCB *processCB, UINT32 gid)
{
    LosProcessCB *runProcessCB = OsCurrProcessGet();
    LosProcessCB *groupProcessCB = OS_PCB_FROM_PID(gid);

    if (OsProcessIsInactive(processCB)) {
        return LOS_ESRCH;
    }

    if (!OsProcessIsUserMode(processCB) || !OsProcessIsUserMode(groupProcessCB)) {
        return LOS_EPERM;
    }

    if (runProcessCB->processID == processCB->parentProcessID) {
        if (processCB->processStatus & OS_PROCESS_FLAG_ALREADY_EXEC) {
            return LOS_EACCES;
        }
    } else if (processCB->processID != runProcessCB->processID) {
        return LOS_ESRCH;
    }

    /* Add the process to another existing process group */
    if (processCB->processID != gid) {
        if (!(groupProcessCB->processStatus & OS_PROCESS_FLAG_GROUP_LEADER)) {
            return LOS_EPERM;
        }

        if ((groupProcessCB->parentProcessID != processCB->parentProcessID) && (gid != processCB->parentProcessID)) {
            return LOS_EPERM;
        }
    }

    return LOS_OK;
}

STATIC UINT32 OsSetProcessGroupIDUnsafe(UINT32 pid, UINT32 gid, ProcessGroup **group)
{
    ProcessGroup *oldGroup = NULL;
    ProcessGroup *newGroup = NULL;
    LosProcessCB *processCB = OS_PCB_FROM_PID(pid);
    INT32 ret = OsSetProcessGroupCheck(processCB, gid);
    if (ret != LOS_OK) {
        return ret;
    }

    if (processCB->group->groupID == gid) {
        return LOS_OK;
    }

    oldGroup = processCB->group;
    OsExitProcessGroup(processCB, group);

    newGroup = OsFindProcessGroup(gid);
    if (newGroup != NULL) {
        LOS_ListTailInsert(&newGroup->processList, &processCB->subordinateGroupList);
        processCB->group = newGroup;
        return LOS_OK;
    }

    newGroup = OsCreateProcessGroup(gid);
    if (newGroup == NULL) {
        LOS_ListTailInsert(&oldGroup->processList, &processCB->subordinateGroupList);
        processCB->group = oldGroup;
        if (*group != NULL) {
            LOS_ListTailInsert(&g_processGroup->groupList, &oldGroup->groupList);
            processCB = OS_PCB_FROM_PID(oldGroup->groupID);
            processCB->processStatus |= OS_PROCESS_FLAG_GROUP_LEADER;
            *group = NULL;
        }
        return LOS_EPERM;
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT INT32 OsSetProcessGroupID(UINT32 pid, UINT32 gid)
{
    ProcessGroup *group = NULL;
    UINT32 ret;
    UINT32 intSave;

    if ((OS_PID_CHECK_INVALID(pid)) || (OS_PID_CHECK_INVALID(gid))) {
        return -LOS_EINVAL;
    }

    SCHEDULER_LOCK(intSave);
    ret = OsSetProcessGroupIDUnsafe(pid, gid, &group);
    SCHEDULER_UNLOCK(intSave);
    (VOID)LOS_MemFree(m_aucSysMem1, group);
    return -ret;
}

LITE_OS_SEC_TEXT INT32 OsSetCurrProcessGroupID(UINT32 gid)
{
    return OsSetProcessGroupID(OsCurrProcessGet()->processID, gid);
}

LITE_OS_SEC_TEXT INT32 LOS_GetProcessGroupID(UINT32 pid)
{
    INT32 gid;
    UINT32 intSave;
    LosProcessCB *processCB = NULL;

    if (OS_PID_CHECK_INVALID(pid)) {
        return -LOS_EINVAL;
    }

    SCHEDULER_LOCK(intSave);
    processCB = OS_PCB_FROM_PID(pid);
    if (OsProcessIsUnused(processCB)) {
        gid = -LOS_ESRCH;
        goto EXIT;
    }

    gid = processCB->group->groupID;

EXIT:
    SCHEDULER_UNLOCK(intSave);
    return gid;
}

LITE_OS_SEC_TEXT INT32 LOS_GetCurrProcessGroupID(VOID)
{
    return LOS_GetProcessGroupID(OsCurrProcessGet()->processID);
}

STATIC VOID *OsUserInitStackAlloc(UINT32 processID, UINT32 *size)
{
    LosVmMapRegion *region = NULL;
    LosProcessCB *processCB = OS_PCB_FROM_PID(processID);
    UINT32 stackSize = ALIGN(OS_USER_TASK_STACK_SIZE, PAGE_SIZE);

    region = LOS_RegionAlloc(processCB->vmSpace, 0, stackSize,
                             VM_MAP_REGION_FLAG_PERM_USER | VM_MAP_REGION_FLAG_PERM_READ |
                             VM_MAP_REGION_FLAG_PERM_WRITE, 0);
    if (region == NULL) {
        return NULL;
    }

    LOS_SetRegionTypeAnon(region);
    region->regionFlags |= VM_MAP_REGION_FLAG_STACK;

    *size = stackSize;

    return (VOID *)(UINTPTR)region->range.base;
}

LITE_OS_SEC_TEXT UINT32 OsExecRecycleAndInit(LosProcessCB *processCB, const CHAR *name,
                                             LosVmSpace *oldSpace, UINTPTR oldFiles)
{
    UINT32 ret;
    errno_t errRet;
    const CHAR *processName = NULL;

    if ((processCB == NULL) || (name == NULL)) {
        return LOS_NOK;
    }

    processName = strrchr(name, '/');
    processName = (processName == NULL) ? name : (processName + 1); /* 1: Do not include '/' */

    ret = OsSetProcessName(processCB, processName);
    if (ret != LOS_OK) {
        return ret;
    }
    errRet = memcpy_s(OsCurrTaskGet()->taskName, OS_TCB_NAME_LEN, processCB->processName, OS_PCB_NAME_LEN);
    if (errRet != EOK) {
        OsCurrTaskGet()->taskName[0] = '\0';
        return LOS_NOK;
    }

#if (LOSCFG_KERNEL_LITEIPC == YES)
    ret = LiteIpcPoolInit(&(processCB->ipcInfo));
    if (ret != LOS_OK) {
        PRINT_ERR("LiteIpcPoolInit failed!\n");
        return LOS_NOK;
    }
#endif

    processCB->sigHandler = 0;
    OsCurrTaskGet()->sig.sigprocmask = 0;

#ifdef LOSCFG_FS_VFS
    delete_files(OsCurrProcessGet(), (struct files_struct *)oldFiles);
#endif

    OsSwtmrRecycle(processCB->processID);
    processCB->timerID = (timer_t)(UINTPTR)MAX_INVALID_TIMER_VID;

#ifdef LOSCFG_SECURITY_VID
    VidMapDestroy(processCB);
    ret = VidMapListInit(processCB);
    if (ret != LOS_OK) {
        PRINT_ERR("VidMapListInit failed!\n");
        return LOS_NOK;
    }
#endif

    processCB->processStatus &= ~OS_PROCESS_FLAG_EXIT;
    processCB->processStatus |= OS_PROCESS_FLAG_ALREADY_EXEC;

    LOS_VmSpaceFree(oldSpace);
    return LOS_OK;
}

LITE_OS_SEC_TEXT UINT32 OsExecStart(const TSK_ENTRY_FUNC entry, UINTPTR sp, UINTPTR mapBase, UINT32 mapSize)
{
    LosProcessCB *processCB = NULL;
    LosTaskCB *taskCB = NULL;
    TaskContext *taskContext = NULL;
    UINT32 intSave;

    if (entry == NULL) {
        return LOS_NOK;
    }

    if ((sp == 0) || (LOS_Align(sp, LOSCFG_STACK_POINT_ALIGN_SIZE) != sp)) {
        return LOS_NOK;
    }

    if ((mapBase == 0) || (mapSize == 0) || (sp <= mapBase) || (sp > (mapBase + mapSize))) {
        return LOS_NOK;
    }

    SCHEDULER_LOCK(intSave);
    processCB = OsCurrProcessGet();
    taskCB = OsCurrTaskGet();

    processCB->threadGroupID = taskCB->taskID;
    taskCB->userMapBase = mapBase;
    taskCB->userMapSize = mapSize;
    taskCB->taskEntry = (TSK_ENTRY_FUNC)entry;

    taskContext = (TaskContext *)OsTaskStackInit(taskCB->taskID, taskCB->stackSize, (VOID *)taskCB->topOfStack, FALSE);
    OsUserTaskStackInit(taskContext, taskCB->taskEntry, sp);
    SCHEDULER_UNLOCK(intSave);
    return LOS_OK;
}

STATIC UINT32 OsUserInitProcessStart(UINT32 processID, TSK_INIT_PARAM_S *param)
{
    UINT32 intSave;
    INT32 taskID;
    INT32 ret;

    taskID = OsCreateUserTask(processID, param);
    if (taskID < 0) {
        return LOS_NOK;
    }

    ret = LOS_SetTaskScheduler(taskID, LOS_SCHED_RR, OS_TASK_PRIORITY_LOWEST);
    if (ret < 0) {
        PRINT_ERR("User init process set scheduler failed! ERROR:%d \n", ret);
        SCHEDULER_LOCK(intSave);
        (VOID)OsTaskDeleteUnsafe(OS_TCB_FROM_TID(taskID), OS_PRO_EXIT_OK, intSave);
        return -ret;
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT UINT32 OsUserInitProcess(VOID)
{
    INT32 ret;
    UINT32 size;
    TSK_INIT_PARAM_S param = { 0 };
    VOID *stack = NULL;
    VOID *userText = NULL;
    CHAR *userInitTextStart = (CHAR *)&__user_init_entry;
    CHAR *userInitBssStart = (CHAR *)&__user_init_bss;
    CHAR *userInitEnd = (CHAR *)&__user_init_end;
    UINT32 initBssSize = userInitEnd - userInitBssStart;
    UINT32 initSize = userInitEnd - userInitTextStart;

    LosProcessCB *processCB = OS_PCB_FROM_PID(g_userInitProcess);
    ret = OsProcessCreateInit(processCB, OS_USER_MODE, "Init", OS_PROCESS_USERINIT_PRIORITY);
    if (ret != LOS_OK) {
        return ret;
    }

    userText = LOS_PhysPagesAllocContiguous(initSize >> PAGE_SHIFT);
    if (userText == NULL) {
        ret = LOS_NOK;
        goto ERROR;
    }

    (VOID)memcpy_s(userText, initSize, (VOID *)&__user_init_load_addr, initSize);
    ret = LOS_VaddrToPaddrMmap(processCB->vmSpace, (VADDR_T)(UINTPTR)userInitTextStart, LOS_PaddrQuery(userText),
                               initSize, VM_MAP_REGION_FLAG_PERM_READ | VM_MAP_REGION_FLAG_PERM_WRITE |
                               VM_MAP_REGION_FLAG_PERM_EXECUTE | VM_MAP_REGION_FLAG_PERM_USER);
    if (ret < 0) {
        goto ERROR;
    }

    (VOID)memset_s((VOID *)((UINTPTR)userText + userInitBssStart - userInitTextStart), initBssSize, 0, initBssSize);

    stack = OsUserInitStackAlloc(g_userInitProcess, &size);
    if (stack == NULL) {
        PRINTK("user init process malloc user stack failed!\n");
        ret = LOS_NOK;
        goto ERROR;
    }

    param.pfnTaskEntry = (TSK_ENTRY_FUNC)userInitTextStart;
    param.userParam.userSP = (UINTPTR)stack + size;
    param.userParam.userMapBase = (UINTPTR)stack;
    param.userParam.userMapSize = size;
    param.uwResved = OS_TASK_FLAG_PTHREAD_JOIN;
    ret = OsUserInitProcessStart(g_userInitProcess, &param);
    if (ret != LOS_OK) {
        (VOID)OsUnMMap(processCB->vmSpace, param.userParam.userMapBase, param.userParam.userMapSize);
        goto ERROR;
    }

    return LOS_OK;

ERROR:
    (VOID)LOS_PhysPagesFreeContiguous(userText, initSize >> PAGE_SHIFT);
    OsDeInitPCB(processCB);
    return ret;
}

STATIC UINT32 OsCopyUser(LosProcessCB *childCB, LosProcessCB *parentCB)
{
#ifdef LOSCFG_SECURITY_CAPABILITY
    UINT32 size = sizeof(User) + sizeof(UINT32) * (parentCB->user->groupNumber - 1);
    childCB->user = LOS_MemAlloc(m_aucSysMem1, size);
    if (childCB->user == NULL) {
        return LOS_ENOMEM;
    }

    (VOID)memcpy_s(childCB->user, size, parentCB->user, size);
#endif
    return LOS_OK;
}

STATIC VOID OsInitCopyTaskParam(LosProcessCB *childProcessCB, const CHAR *name, UINTPTR entry, UINT32 size,
                                TSK_INIT_PARAM_S *childPara)
{
    LosTaskCB *mainThread = NULL;
    UINT32 intSave;

    SCHEDULER_LOCK(intSave);
    mainThread = OsCurrTaskGet();

    if (OsProcessIsUserMode(childProcessCB)) {
        childPara->pfnTaskEntry = mainThread->taskEntry;
        childPara->uwStackSize = mainThread->stackSize;
        childPara->userParam.userArea = mainThread->userArea;
        childPara->userParam.userMapBase = mainThread->userMapBase;
        childPara->userParam.userMapSize = mainThread->userMapSize;
    } else {
        childPara->pfnTaskEntry = (TSK_ENTRY_FUNC)entry;
        childPara->uwStackSize = size;
    }
    childPara->pcName = (CHAR *)name;
    childPara->policy = mainThread->policy;
    childPara->usTaskPrio = mainThread->priority;
    childPara->processID = childProcessCB->processID;
    if (mainThread->taskStatus & OS_TASK_FLAG_PTHREAD_JOIN) {
        childPara->uwResved = OS_TASK_FLAG_PTHREAD_JOIN;
    } else if (mainThread->taskStatus & OS_TASK_FLAG_DETACHED) {
        childPara->uwResved = OS_TASK_FLAG_DETACHED;
    }

    SCHEDULER_UNLOCK(intSave);
}

STATIC UINT32 OsCopyTask(UINT32 flags, LosProcessCB *childProcessCB, const CHAR *name, UINTPTR entry, UINT32 size)
{
    LosTaskCB *childTaskCB = NULL;
    TSK_INIT_PARAM_S childPara = { 0 };
    UINT32 ret;
    UINT32 intSave;
    UINT32 taskID;

    OsInitCopyTaskParam(childProcessCB, name, entry, size, &childPara);

    ret = LOS_TaskCreateOnly(&taskID, &childPara);
    if (ret != LOS_OK) {
        if (ret == LOS_ERRNO_TSK_TCB_UNAVAILABLE) {
            return LOS_EAGAIN;
        }
        return LOS_ENOMEM;
    }

    childTaskCB = OS_TCB_FROM_TID(taskID);
    childTaskCB->taskStatus = OsCurrTaskGet()->taskStatus;
    if (childTaskCB->taskStatus & OS_TASK_STATUS_RUNNING) {
        childTaskCB->taskStatus &= ~OS_TASK_STATUS_RUNNING;
    } else {
        if (OS_SCHEDULER_ACTIVE) {
            LOS_Panic("Clone thread status not running error status: 0x%x\n", childTaskCB->taskStatus);
        }
        childTaskCB->taskStatus &= ~OS_TASK_STATUS_UNUSED;
        childProcessCB->priority = OS_PROCESS_PRIORITY_LOWEST;
    }

    if (OsProcessIsUserMode(childProcessCB)) {
        SCHEDULER_LOCK(intSave);
        OsUserCloneParentStack(childTaskCB, OsCurrTaskGet());
        SCHEDULER_UNLOCK(intSave);
    }
    OS_TASK_PRI_QUEUE_ENQUEUE(childProcessCB, childTaskCB);
    childTaskCB->taskStatus |= OS_TASK_STATUS_READY;
    return LOS_OK;
}

STATIC UINT32 OsCopyParent(UINT32 flags, LosProcessCB *childProcessCB, LosProcessCB *runProcessCB)
{
    UINT32 ret;
    UINT32 intSave;
    LosProcessCB *parentProcessCB = NULL;

    SCHEDULER_LOCK(intSave);
    childProcessCB->priority = runProcessCB->priority;
    childProcessCB->policy = runProcessCB->policy;

    if (flags & CLONE_PARENT) {
        parentProcessCB = OS_PCB_FROM_PID(runProcessCB->parentProcessID);
        childProcessCB->parentProcessID = parentProcessCB->processID;
        LOS_ListTailInsert(&parentProcessCB->childrenList, &childProcessCB->siblingList);
        childProcessCB->group = parentProcessCB->group;
        LOS_ListTailInsert(&parentProcessCB->group->processList, &childProcessCB->subordinateGroupList);
        ret = OsCopyUser(childProcessCB, parentProcessCB);
    } else {
        childProcessCB->parentProcessID = runProcessCB->processID;
        LOS_ListTailInsert(&runProcessCB->childrenList, &childProcessCB->siblingList);
        childProcessCB->group = runProcessCB->group;
        LOS_ListTailInsert(&runProcessCB->group->processList, &childProcessCB->subordinateGroupList);
        ret = OsCopyUser(childProcessCB, runProcessCB);
    }
    SCHEDULER_UNLOCK(intSave);
    return ret;
}

STATIC UINT32 OsCopyMM(UINT32 flags, LosProcessCB *childProcessCB, LosProcessCB *runProcessCB)
{
    status_t status;
    UINT32 intSave;

    if (!OsProcessIsUserMode(childProcessCB)) {
        return LOS_OK;
    }

    if (flags & CLONE_VM) {
        SCHEDULER_LOCK(intSave);
        childProcessCB->vmSpace->archMmu.virtTtb = runProcessCB->vmSpace->archMmu.virtTtb;
        childProcessCB->vmSpace->archMmu.physTtb = runProcessCB->vmSpace->archMmu.physTtb;
        SCHEDULER_UNLOCK(intSave);
        return LOS_OK;
    }

    status = LOS_VmSpaceClone(runProcessCB->vmSpace, childProcessCB->vmSpace);
    if (status != LOS_OK) {
        return LOS_ENOMEM;
    }
    return LOS_OK;
}

STATIC UINT32 OsCopyFile(UINT32 flags, LosProcessCB *childProcessCB, LosProcessCB *runProcessCB)
{
#ifdef LOSCFG_FS_VFS
    if (flags & CLONE_FILES) {
        childProcessCB->files = runProcessCB->files;
    } else {
        childProcessCB->files = dup_fd(runProcessCB->files);
    }
    if (childProcessCB->files == NULL) {
        return LOS_ENOMEM;
    }
#endif

    childProcessCB->consoleID = runProcessCB->consoleID;
    childProcessCB->umask = runProcessCB->umask;
    return LOS_OK;
}

STATIC UINT32 OsForkInitPCB(UINT32 flags, LosProcessCB *child, const CHAR *name, UINTPTR sp, UINT32 size)
{
    UINT32 ret;
    LosProcessCB *run = OsCurrProcessGet();

    ret = OsInitPCB(child, run->processMode, OS_PROCESS_PRIORITY_LOWEST, LOS_SCHED_RR, name);
    if (ret != LOS_OK) {
        return ret;
    }

    ret = OsCopyParent(flags, child, run);
    if (ret != LOS_OK) {
        return ret;
    }

    return OsCopyTask(flags, child, name, sp, size);
}

STATIC UINT32 OsChildSetProcessGroupAndSched(LosProcessCB *child, LosProcessCB *run)
{
    UINT32 intSave;
    UINT32 ret;
    ProcessGroup *group = NULL;

    SCHEDULER_LOCK(intSave);
    if (run->group->groupID == OS_USER_PRIVILEGE_PROCESS_GROUP) {
        ret = OsSetProcessGroupIDUnsafe(child->processID, child->processID, &group);
        if (ret != LOS_OK) {
            SCHEDULER_UNLOCK(intSave);
            return LOS_ENOMEM;
        }
    }

    OS_PROCESS_PRI_QUEUE_ENQUEUE(child);
    child->processStatus &= ~OS_PROCESS_STATUS_INIT;
    child->processStatus |= OS_PROCESS_STATUS_READY;

#ifdef LOSCFG_KERNEL_CPUP
    OsCpupSet(child->processID);
#endif
    SCHEDULER_UNLOCK(intSave);

    (VOID)LOS_MemFree(m_aucSysMem1, group);
    return LOS_OK;
}

STATIC INT32 OsCopyProcessResources(UINT32 flags, LosProcessCB *child, LosProcessCB *run)
{
    UINT32 ret;

    ret = OsCopyMM(flags, child, run);
    if (ret != LOS_OK) {
        return ret;
    }

    ret = OsCopyFile(flags, child, run);
    if (ret != LOS_OK) {
        return ret;
    }

#if (LOSCFG_KERNEL_LITEIPC == YES)
    if (OsProcessIsUserMode(child)) {
        ret = LiteIpcPoolReInit(&child->ipcInfo, (const ProcIpcInfo *)(&run->ipcInfo));
        if (ret != LOS_OK) {
            return LOS_ENOMEM;
        }
    }
#endif

#ifdef LOSCFG_SECURITY_CAPABILITY
    OsCopyCapability(run, child);
#endif

    return LOS_OK;
}

STATIC INT32 OsCopyProcess(UINT32 flags, const CHAR *name, UINTPTR sp, UINT32 size)
{
    UINT32 intSave, ret, processID;
    LosProcessCB *run = OsCurrProcessGet();

    LosProcessCB *child = OsGetFreePCB();
    if (child == NULL) {
        return -LOS_EAGAIN;
    }
    processID = child->processID;

    ret = OsForkInitPCB(flags, child, name, sp, size);
    if (ret != LOS_OK) {
        goto ERROR_INIT;
    }

    ret = OsCopyProcessResources(flags, child, run);
    if (ret != LOS_OK) {
        goto ERROR_TASK;
    }

    ret = OsChildSetProcessGroupAndSched(child, run);
    if (ret != LOS_OK) {
        goto ERROR_TASK;
    }

    LOS_MpSchedule(OS_MP_CPU_ALL);
    if (OS_SCHEDULER_ACTIVE) {
        LOS_Schedule();
    }

    return processID;

ERROR_TASK:
    SCHEDULER_LOCK(intSave);
    (VOID)OsTaskDeleteUnsafe(OS_TCB_FROM_TID(child->threadGroupID), OS_PRO_EXIT_OK, intSave);
ERROR_INIT:
    OsDeInitPCB(child);
    return -ret;
}

LITE_OS_SEC_TEXT INT32 OsClone(UINT32 flags, UINTPTR sp, UINT32 size)
{
    UINT32 cloneFlag = CLONE_PARENT | CLONE_THREAD | CLONE_VFORK | CLONE_VM;

    if (flags & (~cloneFlag)) {
        PRINT_WARN("Clone dont support some flags!\n");
    }

    return OsCopyProcess(cloneFlag & flags, NULL, sp, size);
}

LITE_OS_SEC_TEXT INT32 LOS_Fork(UINT32 flags, const CHAR *name, const TSK_ENTRY_FUNC entry, UINT32 stackSize)
{
    UINT32 cloneFlag = CLONE_PARENT | CLONE_THREAD | CLONE_VFORK | CLONE_FILES;

    if (flags & (~cloneFlag)) {
        PRINT_WARN("Clone dont support some flags!\n");
    }

    flags |= CLONE_FILES;
    return OsCopyProcess(cloneFlag & flags, name, (UINTPTR)entry, stackSize);
}

LITE_OS_SEC_TEXT UINT32 LOS_GetCurrProcessID(VOID)
{
    return OsCurrProcessGet()->processID;
}

LITE_OS_SEC_TEXT VOID OsProcessExit(LosTaskCB *runTask, INT32 status)
{
    UINT32 intSave;
    LOS_ASSERT(runTask == OsCurrTaskGet());

    OsTaskResourcesToFree(runTask);
    OsProcessResourcesToFree(OsCurrProcessGet());

    SCHEDULER_LOCK(intSave);
    OsProcessNaturalExit(runTask, status);
    SCHEDULER_UNLOCK(intSave);
}

LITE_OS_SEC_TEXT VOID LOS_Exit(INT32 status)
{
    OsTaskExitGroup((UINT32)status);
    OsProcessExit(OsCurrTaskGet(), (UINT32)status);
}

LITE_OS_SEC_TEXT UINT32 OsGetUserInitProcessID(VOID)
{
    return g_userInitProcess;
}

LITE_OS_SEC_TEXT UINT32 OsGetIdleProcessID(VOID)
{
    return g_kernelIdleProcess;
}

LITE_OS_SEC_TEXT UINT32 OsGetKernelInitProcessID(VOID)
{
    return g_kernelInitProcess;
}

LITE_OS_SEC_TEXT VOID OsSetSigHandler(UINTPTR addr)
{
    OsCurrProcessGet()->sigHandler = addr;
}

LITE_OS_SEC_TEXT UINTPTR OsGetSigHandler(VOID)
{
    return OsCurrProcessGet()->sigHandler;
}
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif
