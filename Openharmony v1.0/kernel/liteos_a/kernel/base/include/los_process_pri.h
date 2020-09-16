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

#ifndef _LOS_PROCESS_PRI_H
#define _LOS_PROCESS_PRI_H

#include "los_sortlink_pri.h"
#include "los_priqueue_pri.h"
#include "los_task_pri.h"
#include "los_sem_pri.h"
#include "los_process.h"
#include "los_vm_map.h"
#if (LOSCFG_KERNEL_LITEIPC == YES)
#include "hm_liteipc.h"
#endif
#ifdef LOSCFG_SECURITY_CAPABILITY
#include "capability_type.h"
#endif
#ifdef LOSCFG_SECURITY_VID
#include "vid_type.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define OS_PCB_NAME_LEN OS_TCB_NAME_LEN

#ifdef LOSCFG_SECURITY_CAPABILITY
#define OS_GROUPS_NUMBER_MAX 256

typedef struct {
    UINT32  userID;
    UINT32  effUserID;
    UINT32  gid;
    UINT32  effGid;
    UINT32  groupNumber;
    UINT32  groups[1];
} User;
#endif

typedef struct {
    UINT32      groupID;         /**< Process group ID is the PID of the process that created the group */
    LOS_DL_LIST processList;     /**< List of processes under this process group */
    LOS_DL_LIST exitProcessList; /**< List of closed processes (zombie processes) under this group */
    LOS_DL_LIST groupList;       /**< Process group list */
} ProcessGroup;

typedef struct ProcessCB {
    CHAR                 processName[OS_PCB_NAME_LEN]; /**< Process name */
    UINT32               processID;                    /**< process ID = leader thread ID */
    UINT16               processStatus;                /**< [15:4] process Status; [3:0] The number of threads currently
                                                            running in the process */
    UINT16               priority;                     /**< process priority */
    UINT16               policy;                       /**< process policy */
    UINT16               timeSlice;                    /**< Remaining time slice */
    UINT16               consoleID;                    /**< The console id of task belongs  */
    UINT16               processMode;                  /**< Kernel Mode:0; User Mode:1; */
    UINT32               parentProcessID;              /**< Parent process ID */
    UINT32               exitCode;                     /**< process exit status */
    LOS_DL_LIST          pendList;                     /**< Block list to which the process belongs */
    LOS_DL_LIST          childrenList;                 /**< my children process list */
    LOS_DL_LIST          exitChildList;                /**< my exit children process list */
    LOS_DL_LIST          siblingList;                  /**< linkage in my parent's children list */
    ProcessGroup         *group;                       /**< Process group to which a process belongs */
    LOS_DL_LIST          subordinateGroupList;         /**< linkage in my group list */
    UINT32               threadGroupID;                /**< Which thread group , is the main thread ID of the process */
    UINT32               threadScheduleMap;            /**< The scheduling bitmap table for the thread group of the
                                                            process */
    LOS_DL_LIST          threadSiblingList;            /**< List of threads under this process */
    LOS_DL_LIST          threadPriQueueList[OS_PRIORITY_QUEUE_NUM]; /**< The process's thread group schedules the
                                                                         priority hash table */
    volatile UINT32      threadNumber; /**< Number of threads alive under this process */
    UINT32               threadCount;  /**< Total number of threads created under this process */
    LOS_DL_LIST          waitList;     /**< The process holds the waitLits to support wait/waitpid */
#if (LOSCFG_KERNEL_SMP == YES)
    UINT32               timerCpu;     /**< CPU core number of this task is delayed or pended */
#endif
    UINTPTR              sigHandler;   /**< signal handler */
    sigset_t             sigShare;     /**< signal share bit */
#if (LOSCFG_KERNEL_LITEIPC == YES)
    ProcIpcInfo         ipcInfo;       /**< memory pool for lite ipc */
#endif
    LosVmSpace          *vmSpace;       /**< VMM space for processes */
#ifdef LOSCFG_FS_VFS
    struct files_struct *files;        /**< Files held by the process */
#endif
    timer_t             timerID;       /**< iTimer */

#ifdef LOSCFG_SECURITY_CAPABILITY
    User                *user;
    UINT32              capability;
#endif
#ifdef LOSCFG_SECURITY_VID
    TimerIdMap          timerIdMap;
#endif
#ifdef LOSCFG_DRIVERS_TZDRIVER
    struct file         *execFile;     /**< Exec bin of the process */
#endif
    mode_t umask;
} LosProcessCB;

#define CLONE_VM       0x00000100
#define CLONE_FS       0x00000200
#define CLONE_FILES    0x00000400
#define CLONE_SIGHAND  0x00000800
#define CLONE_PTRACE   0x00002000
#define CLONE_VFORK    0x00004000
#define CLONE_PARENT   0x00008000
#define CLONE_THREAD   0x00010000

#define OS_PCB_FROM_PID(processID) (((LosProcessCB *)g_processCBArray) + (processID))
#define OS_PCB_FROM_SIBLIST(ptr)   LOS_DL_LIST_ENTRY((ptr), LosProcessCB, siblingList)
#define OS_PCB_FROM_PENDLIST(ptr)  LOS_DL_LIST_ENTRY((ptr), LosProcessCB, pendList)

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process is created but does not participate in scheduling.
 */
#define OS_PROCESS_STATUS_INIT           0x0010U

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process is ready.
 */
#define OS_PROCESS_STATUS_READY          0x0020U

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process is running.
 */
#define OS_PROCESS_STATUS_RUNNING        0x0040U

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process is pend
 */
#define OS_PROCESS_STATUS_PEND           0x0080U

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process is run out but the resources occupied by the process are not recovered.
 */
#define OS_PROCESS_STATUS_ZOMBIES        0x100U

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The number of task currently running under the process, it only works with multiple cores.
 */
#define OS_PROCESS_RUNTASK_COUNT_MASK    0x000FU

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process status mask.
 */
#define OS_PROCESS_STATUS_MASK           0xFFF0U

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process status equal this is process control block unused,
 * coexisting with OS_PROCESS_STATUS_ZOMBIES means that the control block is not recovered.
 */
#define OS_PROCESS_FLAG_UNUSED            0x0200U

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process has been call exit, it only works with multiple cores.
 */
#define OS_PROCESS_FLAG_EXIT              0x0400U

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process is the leader of the process group.
 */
#define OS_PROCESS_FLAG_GROUP_LEADER      0x0800U

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process has performed the exec operation.
 */
#define OS_PROCESS_FLAG_ALREADY_EXEC      0x1000U

/**
 * @ingroup los_process
 * Flag that indicates the process or process control block status.
 *
 * The process is dying or already dying.
 */
#define OS_PROCESS_STATUS_INACTIVE       (OS_PROCESS_FLAG_EXIT | OS_PROCESS_STATUS_ZOMBIES)

/**
 * @ingroup los_process
 * Used to check if the process control block is unused.
 */
STATIC INLINE BOOL OsProcessIsUnused(const LosProcessCB *processCB)
{
    return ((processCB->processStatus & OS_PROCESS_FLAG_UNUSED) != 0);
}

/**
 * @ingroup los_process
 * Used to check if the process is inactive.
 */
STATIC INLINE BOOL OsProcessIsInactive(const LosProcessCB *processCB)
{
    return ((processCB->processStatus & (OS_PROCESS_FLAG_UNUSED | OS_PROCESS_STATUS_INACTIVE)) != 0);
}

/**
 * @ingroup los_process
 * Used to check if the process is dead.
 */
STATIC INLINE BOOL OsProcessIsDead(const LosProcessCB *processCB)
{
    return ((processCB->processStatus & (OS_PROCESS_FLAG_UNUSED | OS_PROCESS_STATUS_ZOMBIES)) != 0);
}

/**
 * @ingroup los_process
 * Hold the time slice process
 */
#define OS_PROCESS_SCHED_RR_INTERVAL     LOSCFG_BASE_CORE_TIMESLICE_TIMEOUT

/**
 * @ingroup los_process
 * The highest priority of a kernel mode process.
 */
#define OS_PROCESS_PRIORITY_HIGHEST      0

/**
 * @ingroup los_process
 * The lowest priority of a kernel mode process
 */
#define OS_PROCESS_PRIORITY_LOWEST       31

/**
 * @ingroup los_process
 * The highest priority of a user mode process.
 */
#define OS_USER_PROCESS_PRIORITY_HIGHEST 10

/**
 * @ingroup los_process
 * The lowest priority of a user mode process
 */
#define OS_USER_PROCESS_PRIORITY_LOWEST  OS_PROCESS_PRIORITY_LOWEST

/**
 * @ingroup los_process
 * User state root process default priority
 */
#define OS_PROCESS_USERINIT_PRIORITY     28

#define OS_GET_PROCESS_STATUS(status) ((UINT16)((UINT16)(status) & OS_PROCESS_STATUS_MASK))
#define OS_PROCESS_GET_RUNTASK_COUNT(status) ((UINT16)(((UINT16)(status)) & OS_PROCESS_RUNTASK_COUNT_MASK))
#define OS_PROCESS_RUNTASK_COUNT_ADD(status) ((UINT16)(((UINT16)(status)) & OS_PROCESS_STATUS_MASK) | \
        ((OS_PROCESS_GET_RUNTASK_COUNT(status) + 1) & OS_PROCESS_RUNTASK_COUNT_MASK))
#define OS_PROCESS_RUNTASK_COUNT_DEC(status) ((UINT16)(((UINT16)(status)) & OS_PROCESS_STATUS_MASK) | \
        ((OS_PROCESS_GET_RUNTASK_COUNT(status) - 1) & OS_PROCESS_RUNTASK_COUNT_MASK))

#define OS_TASK_DEFAULT_STACK_SIZE      0x2000
#define OS_USER_TASK_SYSCALL_SATCK_SIZE 0x3000
#define OS_USER_TASK_STACK_SIZE         0x100000

#define OS_KERNEL_MODE 0x0U
#define OS_USER_MODE   0x1U
STATIC INLINE BOOL OsProcessIsUserMode(const LosProcessCB *processCB)
{
    return (processCB->processMode == OS_USER_MODE);
}

#define LOS_SCHED_NORMAL  0U
#define LOS_SCHED_FIFO    1U
#define LOS_SCHED_RR      2U

#define LOS_PRIO_PROCESS  0U
#define LOS_PRIO_PGRP     1U
#define LOS_PRIO_USER     2U

#define OS_KERNEL_PROCESS_GROUP         2U
#define OS_USER_PRIVILEGE_PROCESS_GROUP 1U

/*
 * Process exit code
 * 31    15           8           7        0
 * |     | exit code  | core dump | signal |
 */
#define OS_PRO_EXIT_OK 0

STATIC INLINE VOID OsProcessExitCodeCoreDumpSet(LosProcessCB *processCB)
{
    processCB->exitCode |= 0x80U;
}

STATIC INLINE VOID OsProcessExitCodeSignalSet(LosProcessCB *processCB, UINT32 signal)
{
    processCB->exitCode |= signal & 0x7FU;
}

STATIC INLINE VOID OsProcessExitCodeSignalClear(LosProcessCB *processCB)
{
    processCB->exitCode &= (~0x7FU);
}

STATIC INLINE BOOL OsProcessExitCodeSignalIsSet(LosProcessCB *processCB)
{
    return (processCB->exitCode) & 0x7FU;
}

STATIC INLINE VOID OsProcessExitCodeSet(LosProcessCB *processCB, UINT32 code)
{
    processCB->exitCode |= ((code & 0x000000FFU) << 8U) & 0x0000FF00U; /* 8: Move 8 bits to the left, exitCode */
}

extern LosProcessCB *g_processCBArray;
extern LosProcessCB *g_runProcess[LOSCFG_KERNEL_CORE_NUM];
extern UINT32 g_processMaxNum;

#define OS_PID_CHECK_INVALID(pid) (((UINT32)(pid)) >= g_processMaxNum)

STATIC INLINE BOOL OsProcessIDUserCheckInvalid(UINT32 pid)
{
    return ((pid >= g_processMaxNum) || (pid == 0));
}

STATIC INLINE LosProcessCB *OsCurrProcessGet(VOID)
{
    UINT32 intSave;
    LosProcessCB *runProcess = NULL;

    intSave = LOS_IntLock();
    runProcess = g_runProcess[ArchCurrCpuid()];
    LOS_IntRestore(intSave);
    return runProcess;
}

STATIC INLINE VOID OsCurrProcessSet(const LosProcessCB *process)
{
    g_runProcess[ArchCurrCpuid()] = (LosProcessCB *)process;
}

STATIC INLINE UINT32 OsCpuProcessIDGetUnsafe(UINT16 cpuID)
{
    LosProcessCB *runProcess = g_runProcess[cpuID];
    return runProcess->processID;
}

STATIC INLINE UINT32 OsCpuProcessIDGet(UINT16 cpuID)
{
    UINT32 pid;
    UINT32 intSave;

    SCHEDULER_LOCK(intSave);
    pid = OsCpuProcessIDGetUnsafe(cpuID);
    SCHEDULER_UNLOCK(intSave);

    return pid;
}

#ifdef LOSCFG_SECURITY_CAPABILITY
STATIC INLINE User *OsCurrUserGet(VOID)
{
    User *user = NULL;
    UINT32 intSave;

    intSave = LOS_IntLock();
    user = OsCurrProcessGet()->user;
    LOS_IntRestore(intSave);
    return user;
}
#endif

/*
 * return immediately if no child has exited.
 */
#define LOS_WAIT_WNOHANG   (1 << 0U)

/*
 * return if a child has stopped (but not traced via ptrace(2)).
 * Status for traced children which have stopped is provided even
 * if this option is not specified.
 */
#define LOS_WAIT_WUNTRACED (1 << 1U)

/*
 * return if a stopped child has been resumed by delivery of SIGCONT.
 * (For Linux-only options, see below.)
 */
#define LOS_WAIT_WCONTINUED (1 << 3U)

/*
 * Indicates that you are already in a wait state
 */
#define OS_PROCESS_WAIT     (1 << 15U)

/*
 * Wait for any child process to finish
 */
#define OS_PROCESS_WAIT_ANY (1 << 0U)

/*
 * Wait for the child process specified by the pid to finish
 */
#define OS_PROCESS_WAIT_PRO (1 << 1U)

/*
 * Waits for any child process in the specified process group to finish.
 */
#define OS_PROCESS_WAIT_GID (1 << 2U)

#define OS_PROCESS_INFO_ALL 1
#define OS_PROCESS_DEFAULT_UMASK 0022

extern UINTPTR __user_init_entry;
extern UINTPTR __user_init_bss;
extern UINTPTR __user_init_end;
extern UINTPTR __user_init_load_addr;
extern UINT32 OsKernelInitProcess(VOID);
extern VOID OsProcessCBRecyleToFree(VOID);
extern VOID OsProcessResourcesToFree(LosProcessCB *processCB);
extern VOID OsProcessExit(LosTaskCB *runTask, INT32 status);
extern UINT32 OsUserInitProcess(VOID);
extern VOID OsTaskSchedQueueDequeue(LosTaskCB *taskCB, UINT16 status);
extern VOID OsTaskSchedQueueEnqueue(LosTaskCB *taskCB, UINT16 status);
extern INT32 OsClone(UINT32 flags, UINTPTR sp, UINT32 size);
extern VOID OsWaitSignalToWakeProcess(LosProcessCB *processCB);
extern UINT32 OsExecRecycleAndInit(LosProcessCB *processCB, const CHAR *name,
                                   LosVmSpace *oldAspace, UINTPTR oldFiles);
extern UINT32 OsExecStart(const TSK_ENTRY_FUNC entry, UINTPTR sp, UINTPTR mapBase, UINT32 mapSize);
extern INT32 OsSetProcessScheduler(INT32 which, INT32 pid, UINT16 prio, UINT16 policy, BOOL policyFlag);
extern INT32 OsGetProcessPriority(INT32 which, INT32 pid);
extern VOID *OsUserStackAlloc(UINT32 processID, UINT32 *size);
extern UINT32 OsGetUserInitProcessID(VOID);
extern UINT32 OsGetIdleProcessID(VOID);
extern INT32 OsSetProcessGroupID(UINT32 pid, UINT32 gid);
extern INT32 OsSetCurrProcessGroupID(UINT32 gid);
extern UINT32 OsGetKernelInitProcessID(VOID);
extern VOID OsSetSigHandler(UINTPTR addr);
extern UINTPTR OsGetSigHandler(VOID);
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
