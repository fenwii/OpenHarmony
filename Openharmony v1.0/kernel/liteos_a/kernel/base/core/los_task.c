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
#include "los_base_pri.h"
#include "los_priqueue_pri.h"
#include "los_sem_pri.h"
#include "los_event_pri.h"
#include "los_mux_pri.h"
#include "los_hw_pri.h"
#include "los_exc.h"
#include "los_memstat_pri.h"
#include "los_mp.h"
#include "los_spinlock.h"
#include "los_percpu_pri.h"
#include "los_process_pri.h"
#if (LOSCFG_KERNEL_TRACE == YES)
#include "los_trace.h"
#endif

#ifdef LOSCFG_KERNEL_TICKLESS
#include "los_tickless_pri.h"
#endif
#ifdef LOSCFG_KERNEL_CPUP
#include "los_cpup_pri.h"
#endif
#if (LOSCFG_BASE_CORE_SWTMR == YES)
#include "los_swtmr_pri.h"
#endif
#ifdef LOSCFG_EXC_INTERACTION
#include "los_exc_interaction_pri.h"
#endif
#if (LOSCFG_KERNEL_LITEIPC == YES)
#include "hm_liteipc.h"
#endif
#include "user_copy.h"
#include "los_vm_syscall.h"
#ifdef LOSCFG_ENABLE_OOM_LOOP_TASK
#include "los_oom.h"
#endif
#include "los_vm_map.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#if (LOSCFG_BASE_CORE_TSK_LIMIT <= 0)
#error "task maxnum cannot be zero"
#endif  /* LOSCFG_BASE_CORE_TSK_LIMIT <= 0 */

LITE_OS_SEC_BSS LosTaskCB    *g_taskCBArray;
LITE_OS_SEC_BSS LOS_DL_LIST  g_losFreeTask;
LITE_OS_SEC_BSS LOS_DL_LIST  g_taskRecyleList;
LITE_OS_SEC_BSS UINT32       g_taskMaxNum;
LITE_OS_SEC_BSS UINT32       g_taskScheduled; /* one bit for each cores */
LITE_OS_SEC_BSS EVENT_CB_S   g_resourceEvent;
/* spinlock for task module, only available on SMP mode */
LITE_OS_SEC_BSS SPIN_LOCK_INIT(g_taskSpin);

STATIC VOID OsConsoleIDSetHook(UINT32 param1,
                               UINT32 param2) __attribute__((weakref("OsSetConsoleID")));
STATIC VOID OsExcStackCheckHook(VOID) __attribute__((weakref("OsExcStackCheck")));

#define OS_CHECK_TASK_BLOCK (OS_TASK_STATUS_DELAY |    \
                             OS_TASK_STATUS_PEND |     \
                             OS_TASK_STATUS_SUSPEND)

/* temp task blocks for booting procedure */
LITE_OS_SEC_BSS STATIC LosTaskCB                g_mainTask[LOSCFG_KERNEL_CORE_NUM];

VOID* OsGetMainTask()
{
    return (g_mainTask + ArchCurrCpuid());
}

VOID OsSetMainTask()
{
    UINT32 i;
    CHAR *name = "osMain";
    errno_t ret;

    for (i = 0; i < LOSCFG_KERNEL_CORE_NUM; i++) {
        g_mainTask[i].taskStatus = OS_TASK_STATUS_UNUSED;
        g_mainTask[i].taskID = LOSCFG_BASE_CORE_TSK_LIMIT;
        g_mainTask[i].priority = OS_TASK_PRIORITY_LOWEST;
#if (LOSCFG_KERNEL_SMP_LOCKDEP == YES)
        g_mainTask[i].lockDep.lockDepth = 0;
        g_mainTask[i].lockDep.waitLock = NULL;
#endif
        ret = memcpy_s(g_mainTask[i].taskName, OS_TCB_NAME_LEN, name, strlen(name));
        if (ret != EOK) {
            g_mainTask[i].taskName[0] = '\0';
        }
        LOS_ListInit(&g_mainTask[i].lockList);
    }
}

LITE_OS_SEC_TEXT WEAK VOID OsIdleTask(VOID)
{
    while (1) {
#ifdef LOSCFG_KERNEL_TICKLESS
        if (OsTickIrqFlagGet()) {
            OsTickIrqFlagSet(0);
            OsTicklessStart();
        }
#endif
        Wfi();
    }
}

/*
 * Description : Change task priority.
 * Input       : taskCB    --- task control block
 *               priority  --- priority
 */
LITE_OS_SEC_TEXT_MINOR VOID OsTaskPriModify(LosTaskCB *taskCB, UINT16 priority)
{
    LosProcessCB *processCB = NULL;

    LOS_ASSERT(LOS_SpinHeld(&g_taskSpin));

    if (taskCB->taskStatus & OS_TASK_STATUS_READY) {
        processCB = OS_PCB_FROM_PID(taskCB->processID);
        OS_TASK_PRI_QUEUE_DEQUEUE(processCB, taskCB);
        taskCB->priority = priority;
        OS_TASK_PRI_QUEUE_ENQUEUE(processCB, taskCB);
    } else {
        taskCB->priority = priority;
    }
}

LITE_OS_SEC_TEXT STATIC INLINE VOID OsAdd2TimerList(LosTaskCB *taskCB, UINT32 timeOut)
{
    SET_SORTLIST_VALUE(&taskCB->sortList, timeOut);
    OsAdd2SortLink(&OsPercpuGet()->taskSortLink, &taskCB->sortList);
#if (LOSCFG_KERNEL_SMP == YES)
    taskCB->timerCpu = ArchCurrCpuid();
#endif
}

LITE_OS_SEC_TEXT STATIC INLINE VOID OsTimerListDelete(LosTaskCB *taskCB)
{
#if (LOSCFG_KERNEL_SMP == YES)
    SortLinkAttribute *sortLinkHeader = &g_percpu[taskCB->timerCpu].taskSortLink;
#else
    SortLinkAttribute *sortLinkHeader = &g_percpu[0].taskSortLink;
#endif
    OsDeleteSortLink(sortLinkHeader, &taskCB->sortList);
}

STATIC INLINE VOID OsInsertTCBToFreeList(LosTaskCB *taskCB)
{
    UINT32 taskID = taskCB->taskID;
    (VOID)memset_s(taskCB, sizeof(LosTaskCB), 0, sizeof(LosTaskCB));
    taskCB->taskID = taskID;
    taskCB->taskStatus = OS_TASK_STATUS_UNUSED;
    taskCB->processID = OS_INVALID_VALUE;
    LOS_ListAdd(&g_losFreeTask, &taskCB->pendList);
}

LITE_OS_SEC_TEXT_INIT VOID OsTaskJoinPostUnsafe(LosTaskCB *taskCB)
{
    LosTaskCB *resumedTask = NULL;

    if (taskCB->taskStatus & OS_TASK_FLAG_PTHREAD_JOIN) {
        if (!LOS_ListEmpty(&taskCB->joinList)) {
            resumedTask = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&(taskCB->joinList)));
            OsTaskWake(resumedTask);
        }
        taskCB->taskStatus &= ~OS_TASK_FLAG_PTHREAD_JOIN;
    }
    taskCB->taskStatus |= OS_TASK_STATUS_EXIT;
}

LITE_OS_SEC_TEXT UINT32 OsTaskJoinPendUnsafe(LosTaskCB *taskCB)
{
    LosProcessCB *processCB = OS_PCB_FROM_PID(taskCB->processID);
    if (!(processCB->processStatus & OS_PROCESS_STATUS_RUNNING)) {
        return LOS_EPERM;
    }

    if (taskCB->taskStatus & OS_TASK_STATUS_INIT) {
        return LOS_EINVAL;
    }

    if ((taskCB->taskStatus & OS_TASK_FLAG_PTHREAD_JOIN) && LOS_ListEmpty(&taskCB->joinList)) {
        return OsTaskWait(&taskCB->joinList, LOS_WAIT_FOREVER, TRUE);
    } else if (taskCB->taskStatus & OS_TASK_STATUS_EXIT) {
        return LOS_OK;
    }

    return LOS_EINVAL;
}

LITE_OS_SEC_TEXT UINT32 OsTaskSetDeatchUnsafe(LosTaskCB *taskCB)
{
    LosProcessCB *processCB = OS_PCB_FROM_PID(taskCB->processID);
    if (!(processCB->processStatus & OS_PROCESS_STATUS_RUNNING)) {
        return LOS_EPERM;
    }

    if (taskCB->taskStatus & OS_TASK_FLAG_PTHREAD_JOIN) {
        if (LOS_ListEmpty(&(taskCB->joinList))) {
            LOS_ListDelete(&(taskCB->joinList));
            taskCB->taskStatus &= ~OS_TASK_FLAG_PTHREAD_JOIN;
            taskCB->taskStatus |= OS_TASK_FLAG_DETACHED;
            return LOS_OK;
        }
        /* This error code has a special purpose and is not allowed to appear again on the interface */
        return LOS_ESRCH;
    }

    return LOS_EINVAL;
}

LITE_OS_SEC_TEXT VOID OsTaskScan(VOID)
{
    SortLinkList *sortList = NULL;
    LosTaskCB *taskCB = NULL;
    BOOL needSchedule = FALSE;
    UINT16 tempStatus;
    LOS_DL_LIST *listObject = NULL;
    SortLinkAttribute *taskSortLink = NULL;

    taskSortLink = &OsPercpuGet()->taskSortLink;
    taskSortLink->cursor = (taskSortLink->cursor + 1) & OS_TSK_SORTLINK_MASK;
    listObject = taskSortLink->sortLink + taskSortLink->cursor;

    /*
     * When task is pended with timeout, the task block is on the timeout sortlink
     * (per cpu) and ipc(mutex,sem and etc.)'s block at the same time, it can be waken
     * up by either timeout or corresponding ipc it's waiting.
     *
     * Now synchronize sortlink preocedure is used, therefore the whole task scan needs
     * to be protected, preventing another core from doing sortlink deletion at same time.
     */
    LOS_SpinLock(&g_taskSpin);

    if (LOS_ListEmpty(listObject)) {
        LOS_SpinUnlock(&g_taskSpin);
        return;
    }
    sortList = LOS_DL_LIST_ENTRY(listObject->pstNext, SortLinkList, sortLinkNode);
    ROLLNUM_DEC(sortList->idxRollNum);

    while (ROLLNUM(sortList->idxRollNum) == 0) {
        LOS_ListDelete(&sortList->sortLinkNode);
        taskCB = LOS_DL_LIST_ENTRY(sortList, LosTaskCB, sortList);
        taskCB->taskStatus &= ~OS_TASK_STATUS_PEND_TIME;
        tempStatus = taskCB->taskStatus;
        if (tempStatus & OS_TASK_STATUS_PEND) {
            taskCB->taskStatus &= ~OS_TASK_STATUS_PEND;
#if (LOSCFG_KERNEL_LITEIPC == YES)
            taskCB->ipcStatus &= ~IPC_THREAD_STATUS_PEND;
#endif
            taskCB->taskStatus |= OS_TASK_STATUS_TIMEOUT;
            LOS_ListDelete(&taskCB->pendList);
            taskCB->taskSem = NULL;
            taskCB->taskMux = NULL;
        } else {
            taskCB->taskStatus &= ~OS_TASK_STATUS_DELAY;
        }

        if (!(tempStatus & OS_TASK_STATUS_SUSPEND)) {
            OS_TASK_SCHED_QUEUE_ENQUEUE(taskCB, OS_PROCESS_STATUS_PEND);
            needSchedule = TRUE;
        }

        if (LOS_ListEmpty(listObject)) {
            break;
        }

        sortList = LOS_DL_LIST_ENTRY(listObject->pstNext, SortLinkList, sortLinkNode);
    }

    LOS_SpinUnlock(&g_taskSpin);

    if (needSchedule != FALSE) {
        LOS_MpSchedule(OS_MP_CPU_ALL);
        LOS_Schedule();
    }
}

LITE_OS_SEC_TEXT_INIT UINT32 OsTaskInit(VOID)
{
    UINT32 index;
    UINT32 ret;
    UINT32 size;

    g_taskMaxNum = LOSCFG_BASE_CORE_TSK_LIMIT;
    size = (g_taskMaxNum + 1) * sizeof(LosTaskCB);
    /*
     * This memory is resident memory and is used to save the system resources
     * of task control block and will not be freed.
     */
    g_taskCBArray = (LosTaskCB *)LOS_MemAlloc(m_aucSysMem0, size);
    if (g_taskCBArray == NULL) {
        return LOS_ERRNO_TSK_NO_MEMORY;
    }
    (VOID)memset_s(g_taskCBArray, size, 0, size);

    LOS_ListInit(&g_losFreeTask);
    LOS_ListInit(&g_taskRecyleList);
    for (index = 0; index < g_taskMaxNum; index++) {
        g_taskCBArray[index].taskStatus = OS_TASK_STATUS_UNUSED;
        g_taskCBArray[index].taskID = index;
        LOS_ListTailInsert(&g_losFreeTask, &g_taskCBArray[index].pendList);
    }

    ret = OsPriQueueInit();
    if (ret != LOS_OK) {
        return LOS_ERRNO_TSK_NO_MEMORY;
    }

    /* init sortlink for each core */
    for (index = 0; index < LOSCFG_KERNEL_CORE_NUM; index++) {
        ret = OsSortLinkInit(&g_percpu[index].taskSortLink);
        if (ret != LOS_OK) {
            return LOS_ERRNO_TSK_NO_MEMORY;
        }
    }
    return LOS_OK;
}

UINT32 OsGetIdleTaskId(VOID)
{
    Percpu *perCpu = OsPercpuGet();
    return perCpu->idleTaskID;
}

LITE_OS_SEC_TEXT_INIT UINT32 OsIdleTaskCreate(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S taskInitParam;
    Percpu *perCpu = OsPercpuGet();
    UINT32 *idleTaskID = &perCpu->idleTaskID;

    (VOID)memset_s((VOID *)(&taskInitParam), sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)OsIdleTask;
    taskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE;
    taskInitParam.pcName = "Idle";
    taskInitParam.usTaskPrio = OS_TASK_PRIORITY_LOWEST;
    taskInitParam.uwResved = OS_TASK_FLAG_IDLEFLAG;
#if (LOSCFG_KERNEL_SMP == YES)
    taskInitParam.usCpuAffiMask = CPUID_TO_AFFI_MASK(ArchCurrCpuid());
#endif
    ret = LOS_TaskCreate(idleTaskID, &taskInitParam);
    OS_TCB_FROM_TID(*idleTaskID)->taskStatus |= OS_TASK_FLAG_SYSTEM_TASK;

    return ret;
}

/*
 * Description : get id of current running task.
 * Return      : task id
 */
LITE_OS_SEC_TEXT UINT32 LOS_CurTaskIDGet(VOID)
{
    LosTaskCB *runTask = OsCurrTaskGet();

    if (runTask == NULL) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }
    return runTask->taskID;
}

#if (LOSCFG_BASE_CORE_TSK_MONITOR == YES)
LITE_OS_SEC_TEXT STATIC VOID OsTaskStackCheck(LosTaskCB *oldTask, LosTaskCB *newTask)
{
    if (!OS_STACK_MAGIC_CHECK(oldTask->topOfStack)) {
        LOS_Panic("CURRENT task ID: %s:%d stack overflow!\n", oldTask->taskName, oldTask->taskID);
    }

    if (((UINTPTR)(newTask->stackPointer) <= newTask->topOfStack) ||
        ((UINTPTR)(newTask->stackPointer) > (newTask->topOfStack + newTask->stackSize))) {
        LOS_Panic("HIGHEST task ID: %s:%u SP error! StackPointer: %p TopOfStack: %p\n",
                  newTask->taskName, newTask->taskID, newTask->stackPointer, newTask->topOfStack);
    }

    if (OsExcStackCheckHook != NULL) {
        OsExcStackCheckHook();
    }
}

#endif

LITE_OS_SEC_TEXT_MINOR UINT32 OsTaskSwitchCheck(LosTaskCB *oldTask, LosTaskCB *newTask)
{
#if (LOSCFG_BASE_CORE_TSK_MONITOR == YES)
    OsTaskStackCheck(oldTask, newTask);
#endif /* LOSCFG_BASE_CORE_TSK_MONITOR == YES */

#if (LOSCFG_KERNEL_TRACE == YES)
    LOS_Trace(LOS_TRACE_SWITCH, newTask->taskID, oldTask->taskID);
#endif

    return LOS_OK;
}

LITE_OS_SEC_TEXT VOID OsTaskToExit(LosTaskCB *taskCB, UINT32 status)
{
    UINT32 intSave;
    LosProcessCB *runProcess = NULL;
    LosTaskCB *mainTask = NULL;

    SCHEDULER_LOCK(intSave);
    runProcess = OS_PCB_FROM_PID(taskCB->processID);
    mainTask = OS_TCB_FROM_TID(runProcess->threadGroupID);
    SCHEDULER_UNLOCK(intSave);
    if (mainTask == taskCB) {
        OsTaskExitGroup(status);
    }

    SCHEDULER_LOCK(intSave);
    if (runProcess->threadNumber == 1) { /* 1: The last task of the process exits */
        SCHEDULER_UNLOCK(intSave);
        (VOID)OsProcessExit(taskCB, status);
        return;
    }

    if (taskCB->taskStatus & OS_TASK_FLAG_DETACHED) {
        (VOID)OsTaskDeleteUnsafe(taskCB, status, intSave);
    }

    OsTaskJoinPostUnsafe(taskCB);
    OsSchedResched();
    SCHEDULER_UNLOCK(intSave);
    return;
}

/*
 * Description : All task entry
 * Input       : taskID     --- The ID of the task to be run
 */
LITE_OS_SEC_TEXT_INIT VOID OsTaskEntry(UINT32 taskID)
{
    LosTaskCB *taskCB = NULL;

    LOS_ASSERT(!OS_TID_CHECK_INVALID(taskID));

    /*
     * task scheduler needs to be protected throughout the whole process
     * from interrupt and other cores. release task spinlock and enable
     * interrupt in sequence at the task entry.
     */
    LOS_SpinUnlock(&g_taskSpin);
    (VOID)LOS_IntUnLock();

    taskCB = OS_TCB_FROM_TID(taskID);
    taskCB->joinRetval = taskCB->taskEntry(taskCB->args[0], taskCB->args[1],
                                           taskCB->args[2], taskCB->args[3]); /* 2 & 3: just for args array index */
    if (taskCB->taskStatus & OS_TASK_FLAG_DETACHED) {
        taskCB->joinRetval = 0;
    }

    OsTaskToExit(taskCB, 0);
}

LITE_OS_SEC_TEXT_INIT STATIC UINT32 OsTaskCreateParamCheck(const UINT32 *taskID,
    TSK_INIT_PARAM_S *initParam, VOID **pool)
{
    LosProcessCB *process = NULL;
    UINT32 poolSize = OS_SYS_MEM_SIZE;
    *pool = (VOID *)m_aucSysMem1;

    if (taskID == NULL) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    if (initParam == NULL) {
        return LOS_ERRNO_TSK_PTR_NULL;
    }

    process = OS_PCB_FROM_PID(initParam->processID);
    if (process->processMode > OS_USER_MODE) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    if (!OsProcessIsUserMode(process)) {
        if (initParam->pcName == NULL) {
            return LOS_ERRNO_TSK_NAME_EMPTY;
        }
    }

    if (initParam->pfnTaskEntry == NULL) {
        return LOS_ERRNO_TSK_ENTRY_NULL;
    }

    if (initParam->usTaskPrio > OS_TASK_PRIORITY_LOWEST) {
        return LOS_ERRNO_TSK_PRIOR_ERROR;
    }

#ifdef LOSCFG_EXC_INTERACTION
    if (!OsExcInteractionTaskCheck(initParam)) {
        *pool = m_aucSysMem0;
        poolSize = OS_EXC_INTERACTMEM_SIZE;
    }
#endif
    if (initParam->uwStackSize > poolSize) {
        return LOS_ERRNO_TSK_STKSZ_TOO_LARGE;
    }

    if (initParam->uwStackSize == 0) {
        initParam->uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    }
    initParam->uwStackSize = (UINT32)ALIGN(initParam->uwStackSize, LOSCFG_STACK_POINT_ALIGN_SIZE);

    if (initParam->uwStackSize < LOS_TASK_MIN_STACK_SIZE) {
        return LOS_ERRNO_TSK_STKSZ_TOO_SMALL;
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT STATIC VOID OsTaskStackAlloc(VOID **topStack, UINT32 stackSize, VOID *pool)
{
    *topStack = (VOID *)LOS_MemAllocAlign(pool, stackSize, LOSCFG_STACK_POINT_ALIGN_SIZE);
}

STATIC INLINE UINT32 OsTaskSyncCreate(LosTaskCB *taskCB)
{
#if (LOSCFG_KERNEL_SMP_TASK_SYNC == YES)
    UINT32 ret = LOS_SemCreate(0, &taskCB->syncSignal);
    if (ret != LOS_OK) {
        return LOS_ERRNO_TSK_MP_SYNC_RESOURCE;
    }
#else
    (VOID)taskCB;
#endif
    return LOS_OK;
}

STATIC INLINE VOID OsTaskSyncDestroy(UINT32 syncSignal)
{
#if (LOSCFG_KERNEL_SMP_TASK_SYNC == YES)
    (VOID)LOS_SemDelete(syncSignal);
#else
    (VOID)syncSignal;
#endif
}

LITE_OS_SEC_TEXT UINT32 OsTaskSyncWait(const LosTaskCB *taskCB)
{
#if (LOSCFG_KERNEL_SMP_TASK_SYNC == YES)
    UINT32 ret = LOS_OK;

    LOS_ASSERT(LOS_SpinHeld(&g_taskSpin));
    LOS_SpinUnlock(&g_taskSpin);
    /*
     * gc soft timer works every OS_MP_GC_PERIOD period, to prevent this timer
     * triggered right at the timeout has reached, we set the timeout as double
     * of the gc peroid.
     */
    if (LOS_SemPend(taskCB->syncSignal, OS_MP_GC_PERIOD * 2) != LOS_OK) {
        ret = LOS_ERRNO_TSK_MP_SYNC_FAILED;
    }

    LOS_SpinLock(&g_taskSpin);

    return ret;
#else
    (VOID)taskCB;
    return LOS_OK;
#endif
}

STATIC INLINE VOID OsTaskSyncWake(const LosTaskCB *taskCB)
{
#if (LOSCFG_KERNEL_SMP_TASK_SYNC == YES)
    (VOID)OsSemPostUnsafe(taskCB->syncSignal, NULL);
#else
    (VOID)taskCB;
#endif
}

STATIC VOID OsTaskKernelResourcesToFree(UINT32 syncSignal, UINTPTR topOfStack)
{
    VOID *poolTmp = (VOID *)m_aucSysMem1;

    OsTaskSyncDestroy(syncSignal);

#ifdef LOSCFG_EXC_INTERACTION
    if (topOfStack < (UINTPTR)m_aucSysMem1) {
        poolTmp = (VOID *)m_aucSysMem0;
    }
#endif
    (VOID)LOS_MemFree(poolTmp, (VOID *)topOfStack);
}

LITE_OS_SEC_TEXT VOID OsTaskCBRecyleToFree()
{
    LosTaskCB *taskCB = NULL;
    UINT32 intSave;

    SCHEDULER_LOCK(intSave);
    while (!LOS_ListEmpty(&g_taskRecyleList)) {
        taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&g_taskRecyleList));
        LOS_ListDelete(&taskCB->pendList);
        SCHEDULER_UNLOCK(intSave);

        OsTaskResourcesToFree(taskCB);

        SCHEDULER_LOCK(intSave);
    }
    SCHEDULER_UNLOCK(intSave);
}

LITE_OS_SEC_TEXT VOID OsTaskResourcesToFree(LosTaskCB *taskCB)
{
    LosProcessCB *processCB = OS_PCB_FROM_PID(taskCB->processID);
    UINT32 syncSignal = LOSCFG_BASE_IPC_SEM_LIMIT;
    UINT32 mapSize, intSave;
    UINTPTR mapBase, topOfStack;
    UINT32 ret;

    if (OsProcessIsUserMode(processCB) && (taskCB->userMapBase != 0)) {
        SCHEDULER_LOCK(intSave);
        mapBase = (UINTPTR)taskCB->userMapBase;
        mapSize = taskCB->userMapSize;
        taskCB->userMapBase = 0;
        taskCB->userArea = 0;
        SCHEDULER_UNLOCK(intSave);

        LOS_ASSERT(!(processCB->vmSpace == NULL));
        ret = OsUnMMap(processCB->vmSpace, (UINTPTR)mapBase, mapSize);
        if ((ret != LOS_OK) && (mapBase != 0) && !(processCB->processStatus & OS_PROCESS_STATUS_INIT)) {
            PRINT_ERR("process(%u) ummap user task(%u) stack failed! mapbase: 0x%x size :0x%x, error: %d\n",
                      processCB->processID, taskCB->taskID, mapBase, mapSize, ret);
        }

#if (LOSCFG_KERNEL_LITEIPC == YES)
        LiteIpcRemoveServiceHandle(taskCB);
#endif
    }

    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        topOfStack = taskCB->topOfStack;
        taskCB->topOfStack = 0;
#if (LOSCFG_KERNEL_SMP_TASK_SYNC == YES)
        syncSignal = taskCB->syncSignal;
        taskCB->syncSignal = LOSCFG_BASE_IPC_SEM_LIMIT;
#endif
        OsTaskKernelResourcesToFree(syncSignal, topOfStack);

        SCHEDULER_LOCK(intSave);
        OsInsertTCBToFreeList(taskCB);
        SCHEDULER_UNLOCK(intSave);
    }
    return;
}

LITE_OS_SEC_TEXT_INIT STATIC VOID OsTaskCBInitBase(LosTaskCB *taskCB,
                                                   const VOID *stackPtr,
                                                   const VOID *topStack,
                                                   const TSK_INIT_PARAM_S *initParam)
{
    taskCB->stackPointer = (VOID *)stackPtr;
    taskCB->args[0]      = initParam->auwArgs[0]; /* 0~3: just for args array index */
    taskCB->args[1]      = initParam->auwArgs[1];
    taskCB->args[2]      = initParam->auwArgs[2];
    taskCB->args[3]      = initParam->auwArgs[3];
    taskCB->topOfStack   = (UINTPTR)topStack;
    taskCB->stackSize    = initParam->uwStackSize;
    taskCB->priority     = initParam->usTaskPrio;
    taskCB->taskEntry    = initParam->pfnTaskEntry;
    taskCB->signal       = SIGNAL_NONE;

#if (LOSCFG_KERNEL_SMP == YES)
    taskCB->currCpu      = OS_TASK_INVALID_CPUID;
    taskCB->cpuAffiMask  = (initParam->usCpuAffiMask) ?
                            initParam->usCpuAffiMask : LOSCFG_KERNEL_CPU_MASK;
#endif
#if (LOSCFG_KERNEL_LITEIPC == YES)
    LOS_ListInit(&(taskCB->msgListHead));
    (VOID)memset_s(taskCB->accessMap, sizeof(taskCB->accessMap), 0, sizeof(taskCB->accessMap));
#endif
    taskCB->policy = (initParam->policy == LOS_SCHED_FIFO) ? LOS_SCHED_FIFO : LOS_SCHED_RR;
    taskCB->taskStatus = OS_TASK_STATUS_INIT;
    if (initParam->uwResved & OS_TASK_FLAG_DETACHED) {
        taskCB->taskStatus |= OS_TASK_FLAG_DETACHED;
    } else {
        LOS_ListInit(&taskCB->joinList);
        taskCB->taskStatus |= OS_TASK_FLAG_PTHREAD_JOIN;
    }

    taskCB->futex.index = OS_INVALID_VALUE;
    LOS_ListInit(&taskCB->lockList);
}

LITE_OS_SEC_TEXT_INIT STATIC UINT32 OsTaskCBInit(LosTaskCB *taskCB, const TSK_INIT_PARAM_S *initParam,
                                                 const VOID *stackPtr, const VOID *topStack)
{
    UINT32 intSave;
    UINT32 ret;
    UINT32 numCount;
    UINT16 mode;
    LosProcessCB *processCB = NULL;

    OsTaskCBInitBase(taskCB, stackPtr, topStack, initParam);

    SCHEDULER_LOCK(intSave);
    processCB = OS_PCB_FROM_PID(initParam->processID);
    taskCB->processID = processCB->processID;
    mode = processCB->processMode;
    LOS_ListTailInsert(&(processCB->threadSiblingList), &(taskCB->threadList));
    if (mode == OS_USER_MODE) {
        taskCB->userArea = initParam->userParam.userArea;
        taskCB->userMapBase = initParam->userParam.userMapBase;
        taskCB->userMapSize = initParam->userParam.userMapSize;
        OsUserTaskStackInit(taskCB->stackPointer, taskCB->taskEntry, initParam->userParam.userSP);
    }

    if (!processCB->threadNumber) {
        processCB->threadGroupID = taskCB->taskID;
    }
    processCB->threadNumber++;

    numCount = processCB->threadCount;
    processCB->threadCount++;
    SCHEDULER_UNLOCK(intSave);

    if (initParam->pcName == NULL) {
        (VOID)memset_s(taskCB->taskName, sizeof(CHAR) * OS_TCB_NAME_LEN, 0, sizeof(CHAR) * OS_TCB_NAME_LEN);
        (VOID)snprintf_s(taskCB->taskName, sizeof(CHAR) * OS_TCB_NAME_LEN,
                         (sizeof(CHAR) * OS_TCB_NAME_LEN) - 1, "thread%u", numCount);
        return LOS_OK;
    }

    if (mode == OS_KERNEL_MODE) {
        ret = memcpy_s(taskCB->taskName, sizeof(CHAR) * OS_TCB_NAME_LEN, initParam->pcName, strlen(initParam->pcName));
        if (ret != EOK) {
            taskCB->taskName[0] = '\0';
        }
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT LosTaskCB *OsGetFreeTaskCB(VOID)
{
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;

    SCHEDULER_LOCK(intSave);
    if (LOS_ListEmpty(&g_losFreeTask)) {
        SCHEDULER_UNLOCK(intSave);
        PRINT_ERR("No idle TCB in the system!\n");
        return NULL;
    }

    taskCB = OS_TCB_FROM_PENDLIST(LOS_DL_LIST_FIRST(&g_losFreeTask));
    LOS_ListDelete(LOS_DL_LIST_FIRST(&g_losFreeTask));
    SCHEDULER_UNLOCK(intSave);

    return taskCB;
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskCreateOnly(UINT32 *taskID, TSK_INIT_PARAM_S *initParam)
{
    UINT32 intSave, errRet;
    VOID *topStack = NULL;
    VOID *stackPtr = NULL;
    LosTaskCB *taskCB = NULL;
    VOID *pool = NULL;

    errRet = OsTaskCreateParamCheck(taskID, initParam, &pool);
    if (errRet != LOS_OK) {
        return errRet;
    }

    taskCB = OsGetFreeTaskCB();
    if (taskCB == NULL) {
        errRet = LOS_ERRNO_TSK_TCB_UNAVAILABLE;
        goto LOS_ERREND;
    }

    errRet = OsTaskSyncCreate(taskCB);
    if (errRet != LOS_OK) {
        goto LOS_ERREND_REWIND_TCB;
    }

    OsTaskStackAlloc(&topStack, initParam->uwStackSize, pool);
    if (topStack == NULL) {
        errRet = LOS_ERRNO_TSK_NO_MEMORY;
        goto LOS_ERREND_REWIND_SYNC;
    }

    stackPtr = OsTaskStackInit(taskCB->taskID, initParam->uwStackSize, topStack, TRUE);
    errRet = OsTaskCBInit(taskCB, initParam, stackPtr, topStack);
    if (errRet != LOS_OK) {
        goto LOS_ERREND_TCB_INIT;
    }
    if (OsConsoleIDSetHook != NULL) {
        OsConsoleIDSetHook(taskCB->taskID, OsCurrTaskGet()->taskID);
    }

    *taskID = taskCB->taskID;
    return LOS_OK;

LOS_ERREND_TCB_INIT:
    (VOID)LOS_MemFree(pool, topStack);
LOS_ERREND_REWIND_SYNC:
#if (LOSCFG_KERNEL_SMP_TASK_SYNC == YES)
    OsTaskSyncDestroy(taskCB->syncSignal);
#endif
LOS_ERREND_REWIND_TCB:
    SCHEDULER_LOCK(intSave);
    OsInsertTCBToFreeList(taskCB);
    SCHEDULER_UNLOCK(intSave);
LOS_ERREND:
    return errRet;
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskCreate(UINT32 *taskID, TSK_INIT_PARAM_S *initParam)
{
    UINT32 ret;
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;

    if (initParam == NULL) {
        return LOS_ERRNO_TSK_PTR_NULL;
    }

    if (OS_INT_ACTIVE) {
        return LOS_ERRNO_TSK_YIELD_IN_INT;
    }

    if (initParam->uwResved & OS_TASK_FLAG_IDLEFLAG) {
        initParam->processID = OsGetIdleProcessID();
    } else if (OsProcessIsUserMode(OsCurrProcessGet())) {
        initParam->processID = OsGetKernelInitProcessID();
    } else {
        initParam->processID = OsCurrProcessGet()->processID;
    }
    initParam->uwResved &= ~OS_TASK_FLAG_IDLEFLAG;
    initParam->uwResved &= ~OS_TASK_FLAG_PTHREAD_JOIN;
    if (initParam->uwResved & LOS_TASK_STATUS_DETACHED) {
        initParam->uwResved = OS_TASK_FLAG_DETACHED;
    }

    ret = LOS_TaskCreateOnly(taskID, initParam);
    if (ret != LOS_OK) {
        return ret;
    }
    taskCB = OS_TCB_FROM_TID(*taskID);

    SCHEDULER_LOCK(intSave);
    taskCB->taskStatus &= ~OS_TASK_STATUS_INIT;
    OS_TASK_SCHED_QUEUE_ENQUEUE(taskCB, 0);
    SCHEDULER_UNLOCK(intSave);

    /* in case created task not running on this core,
       schedule or not depends on other schedulers status. */
    LOS_MpSchedule(OS_MP_CPU_ALL);
    if (OS_SCHEDULER_ACTIVE) {
        LOS_Schedule();
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskResume(UINT32 taskID)
{
    UINT32 intSave;
    UINT16 tempStatus;
    UINT32 errRet;
    LosTaskCB *taskCB = NULL;
    BOOL needSched = FALSE;

    if (OS_TID_CHECK_INVALID(taskID)) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    SCHEDULER_LOCK(intSave);

    /* clear pending signal */
    taskCB->signal &= ~SIGNAL_SUSPEND;

    tempStatus = taskCB->taskStatus;
    if (tempStatus & OS_TASK_STATUS_UNUSED) {
        errRet = LOS_ERRNO_TSK_NOT_CREATED;
        OS_GOTO_ERREND();
    } else if (!(tempStatus & OS_TASK_STATUS_SUSPEND)) {
        errRet = LOS_ERRNO_TSK_NOT_SUSPENDED;
        OS_GOTO_ERREND();
    }

    taskCB->taskStatus &= ~OS_TASK_STATUS_SUSPEND;
    if (!(taskCB->taskStatus & OS_CHECK_TASK_BLOCK)) {
        OS_TASK_SCHED_QUEUE_ENQUEUE(taskCB, OS_PROCESS_STATUS_PEND);
        if (OS_SCHEDULER_ACTIVE) {
            needSched = TRUE;
        }
    }

    SCHEDULER_UNLOCK(intSave);

    if (needSched) {
        LOS_MpSchedule(OS_MP_CPU_ALL);
        LOS_Schedule();
    }

    return LOS_OK;

LOS_ERREND:
    SCHEDULER_UNLOCK(intSave);
    return errRet;
}

/*
 * Check if needs to do the suspend operation on the running task.
 * Return TRUE, if needs to do the suspension.
 * Rerturn FALSE, if meets following circumstances:
 * 1. Do the suspension across cores, if SMP is enabled
 * 2. Do the suspension when preemption is disabled
 * 3. Do the suspension in hard-irq
 * then LOS_TaskSuspend will directly return with 'ret' value.
 */
LITE_OS_SEC_TEXT_INIT STATIC BOOL OsTaskSuspendCheckOnRun(LosTaskCB *taskCB, UINT32 *ret)
{
    /* init default out return value */
    *ret = LOS_OK;

#if (LOSCFG_KERNEL_SMP == YES)
    /* ASYNCHRONIZED. No need to do task lock checking */
    if (taskCB->currCpu != ArchCurrCpuid()) {
        taskCB->signal = SIGNAL_SUSPEND;
        LOS_MpSchedule(taskCB->currCpu);
        return FALSE;
    }
#endif

    if (!OsPreemptableInSched()) {
        /* Suspending the current core's running task */
        *ret = LOS_ERRNO_TSK_SUSPEND_LOCKED;
        return FALSE;
    }

    if (OS_INT_ACTIVE) {
        /* suspend running task in interrupt */
        taskCB->signal = SIGNAL_SUSPEND;
        return FALSE;
    }

    return TRUE;
}

LITE_OS_SEC_TEXT STATIC UINT32 OsTaskSuspend(LosTaskCB *taskCB)
{
    UINT32 errRet;
    UINT16 tempStatus;
    LosTaskCB *runTask = NULL;

    tempStatus = taskCB->taskStatus;
    if (tempStatus & OS_TASK_STATUS_UNUSED) {
        return LOS_ERRNO_TSK_NOT_CREATED;
    }

    if (tempStatus & OS_TASK_STATUS_SUSPEND) {
        return LOS_ERRNO_TSK_ALREADY_SUSPENDED;
    }

    if ((tempStatus & OS_TASK_STATUS_RUNNING) &&
        !OsTaskSuspendCheckOnRun(taskCB, &errRet)) {
        return errRet;
    }

    if (tempStatus & OS_TASK_STATUS_READY) {
        OS_TASK_SCHED_QUEUE_DEQUEUE(taskCB, OS_PROCESS_STATUS_PEND);
    }

    taskCB->taskStatus |= OS_TASK_STATUS_SUSPEND;

    runTask = OsCurrTaskGet();
    if (taskCB == runTask) {
        OsSchedResched();
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskSuspend(UINT32 taskID)
{
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;
    UINT32 errRet;

    if (OS_TID_CHECK_INVALID(taskID)) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    if (taskCB->taskStatus & OS_TASK_FLAG_SYSTEM_TASK) {
        return LOS_ERRNO_TSK_OPERATE_SYSTEM_TASK;
    }

    SCHEDULER_LOCK(intSave);
    errRet = OsTaskSuspend(taskCB);
    SCHEDULER_UNLOCK(intSave);
    return errRet;
}

STATIC INLINE VOID OsTaskStatusUnusedSet(LosTaskCB *taskCB)
{
    taskCB->taskStatus |= OS_TASK_STATUS_UNUSED;
    taskCB->eventMask = 0;

    OS_MEM_CLEAR(taskCB->taskID);
}

STATIC INLINE VOID OsTaskReleaseHoldLock(LosProcessCB *processCB, LosTaskCB *taskCB)
{
    LosMux *mux = NULL;
    UINT32 ret;

    while (!LOS_ListEmpty(&taskCB->lockList)) {
        mux = LOS_DL_LIST_ENTRY(LOS_DL_LIST_FIRST(&taskCB->lockList), LosMux, holdList);
        ret = OsMuxUnlockUnsafe(taskCB, mux, NULL);
        if (ret != LOS_OK) {
            LOS_ListDelete(&mux->holdList);
            PRINT_ERR("mux ulock failed! : %u\n", ret);
        }
    }

    if (processCB->processMode == OS_USER_MODE) {
        OsTaskJoinPostUnsafe(taskCB);
        OsFutexNodeDeleteFromFutexHash(&taskCB->futex, TRUE, NULL, NULL);
    }

    OsTaskSyncWake(taskCB);
}

LITE_OS_SEC_TEXT VOID OsRunTaskToDelete(LosTaskCB *taskCB)
{
    LosProcessCB *processCB = OS_PCB_FROM_PID(taskCB->processID);
    OsTaskReleaseHoldLock(processCB, taskCB);
    OsTaskStatusUnusedSet(taskCB);

    LOS_ListDelete(&taskCB->threadList);
    processCB->threadNumber--;
    LOS_ListTailInsert(&g_taskRecyleList, &taskCB->pendList);
    OsEventWriteUnsafe(&g_resourceEvent, OS_RESOURCE_EVENT_FREE, FALSE, NULL);

    OsSchedResched();
    return;
}

/*
 * Check if needs to do the delete operation on the running task.
 * Return TRUE, if needs to do the deletion.
 * Rerturn FALSE, if meets following circumstances:
 * 1. Do the deletion across cores, if SMP is enabled
 * 2. Do the deletion when preemption is disabled
 * 3. Do the deletion in hard-irq
 * then LOS_TaskDelete will directly return with 'ret' value.
 */
STATIC BOOL OsRunTaskToDeleteCheckOnRun(LosTaskCB *taskCB, UINT32 *ret)
{
    /* init default out return value */
    *ret = LOS_OK;

#if (LOSCFG_KERNEL_SMP == YES)
    /* ASYNCHRONIZED. No need to do task lock checking */
    if (taskCB->currCpu != ArchCurrCpuid()) {
        /*
         * the task is running on another cpu.
         * mask the target task with "kill" signal, and trigger mp schedule
         * which might not be essential but the deletion could more in time.
         */
        taskCB->signal = SIGNAL_KILL;
        LOS_MpSchedule(taskCB->currCpu);
        *ret = OsTaskSyncWait(taskCB);
        return FALSE;
    }
#endif

    if (!OsPreemptableInSched()) {
        /* If the task is running and scheduler is locked then you can not delete it */
        *ret = LOS_ERRNO_TSK_DELETE_LOCKED;
        return FALSE;
    }

    if (OS_INT_ACTIVE) {
        /*
         * delete running task in interrupt.
         * mask "kill" signal and later deletion will be handled.
         */
        taskCB->signal = SIGNAL_KILL;
        return FALSE;
    }

    return TRUE;
}

STATIC VOID OsTaskDeleteInactive(LosProcessCB *processCB, LosTaskCB *taskCB)
{
    LosMux *mux = (LosMux *)taskCB->taskMux;

    LOS_ASSERT(!(taskCB->taskStatus & OS_TASK_STATUS_RUNNING));

    OsTaskReleaseHoldLock(processCB, taskCB);

    if (taskCB->taskStatus & OS_TASK_STATUS_READY) {
        OS_TASK_SCHED_QUEUE_DEQUEUE(taskCB, 0);
    } else if (taskCB->taskStatus & OS_TASK_STATUS_PEND) {
        LOS_ListDelete(&taskCB->pendList);
        if (LOS_MuxIsValid(mux) == TRUE) {
            OsMuxBitmapRestore(mux, taskCB, (LosTaskCB *)mux->owner);
        }
    }

    if (taskCB->taskStatus & (OS_TASK_STATUS_DELAY | OS_TASK_STATUS_PEND_TIME)) {
        OsTimerListDelete(taskCB);
    }
    OsTaskStatusUnusedSet(taskCB);

    LOS_ListDelete(&taskCB->threadList);
    processCB->threadNumber--;
    LOS_ListTailInsert(&g_taskRecyleList, &taskCB->pendList);
    return;
}

LITE_OS_SEC_TEXT UINT32 OsTaskDeleteUnsafe(LosTaskCB *taskCB, UINT32 status, UINT32 intSave)
{
    LosProcessCB *processCB = OS_PCB_FROM_PID(taskCB->processID);
    UINT32 mode = processCB->processMode;
    UINT32 errRet = LOS_OK;

    if (taskCB->taskStatus & OS_TASK_FLAG_SYSTEM_TASK) {
        errRet = LOS_ERRNO_TSK_OPERATE_SYSTEM_TASK;
        goto EXIT;
    }

    if ((taskCB->taskStatus & OS_TASK_STATUS_RUNNING) && !OsRunTaskToDeleteCheckOnRun(taskCB, &errRet)) {
        goto EXIT;
    }

    if (!(taskCB->taskStatus & OS_TASK_STATUS_RUNNING)) {
        OsTaskDeleteInactive(processCB, taskCB);
        SCHEDULER_UNLOCK(intSave);
        OsWriteResourceEvent(OS_RESOURCE_EVENT_FREE);
        return errRet;
    }

    if (mode == OS_USER_MODE) {
        SCHEDULER_UNLOCK(intSave);
        OsTaskResourcesToFree(taskCB);
        SCHEDULER_LOCK(intSave);
    }

#if (LOSCFG_KERNEL_SMP == YES)
    LOS_ASSERT(OsPercpuGet()->taskLockCnt == 1);
#else
    LOS_ASSERT(OsPercpuGet()->taskLockCnt == 0);
#endif
    OsRunTaskToDelete(taskCB);

EXIT:
    SCHEDULER_UNLOCK(intSave);
    return errRet;
}

LITE_OS_SEC_TEXT_INIT UINT32 LOS_TaskDelete(UINT32 taskID)
{
    UINT32 intSave;
    UINT32 ret;
    LosTaskCB *taskCB = NULL;
    LosProcessCB *processCB = NULL;

    if (OS_TID_CHECK_INVALID(taskID)) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    if (OS_INT_ACTIVE) {
        return LOS_ERRNO_TSK_YIELD_IN_INT;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    SCHEDULER_LOCK(intSave);
    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        ret = LOS_ERRNO_TSK_NOT_CREATED;
        OS_GOTO_ERREND();
    }

    processCB = OS_PCB_FROM_PID(taskCB->processID);
    if (processCB->threadNumber == 1) {
        if (processCB == OsCurrProcessGet()) {
            SCHEDULER_UNLOCK(intSave);
            OsProcessExit(taskCB, OS_PRO_EXIT_OK);
            return LOS_OK;
        }

        ret = LOS_ERRNO_TSK_ID_INVALID;
        OS_GOTO_ERREND();
    }

    return OsTaskDeleteUnsafe(taskCB, OS_PRO_EXIT_OK, intSave);

LOS_ERREND:
    SCHEDULER_UNLOCK(intSave);
    return ret;
}

LITE_OS_SEC_TEXT UINT32 LOS_TaskDelay(UINT32 tick)
{
    UINT32 intSave;
    LosTaskCB *runTask = NULL;

    if (OS_INT_ACTIVE) {
        PRINT_ERR("In interrupt not allow delay task!\n");
        return LOS_ERRNO_TSK_DELAY_IN_INT;
    }

    runTask = OsCurrTaskGet();
    if (runTask->taskStatus & OS_TASK_FLAG_SYSTEM_TASK) {
        OsBackTrace();
        return LOS_ERRNO_TSK_OPERATE_SYSTEM_TASK;
    }

    if (!OsPreemptable()) {
        return LOS_ERRNO_TSK_DELAY_IN_LOCK;
    }

    if (tick == 0) {
        return LOS_TaskYield();
    } else {
        SCHEDULER_LOCK(intSave);
        OS_TASK_SCHED_QUEUE_DEQUEUE(runTask, OS_PROCESS_STATUS_PEND);
        OsAdd2TimerList(runTask, tick);
        runTask->taskStatus |= OS_TASK_STATUS_DELAY;
        OsSchedResched();
        SCHEDULER_UNLOCK(intSave);
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT16 LOS_TaskPriGet(UINT32 taskID)
{
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;
    UINT16 priority;

    if (OS_TID_CHECK_INVALID(taskID)) {
        return (UINT16)OS_INVALID;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    SCHEDULER_LOCK(intSave);
    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        SCHEDULER_UNLOCK(intSave);
        return (UINT16)OS_INVALID;
    }

    priority = taskCB->priority;
    SCHEDULER_UNLOCK(intSave);
    return priority;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskPriSet(UINT32 taskID, UINT16 taskPrio)
{
    BOOL isReady = FALSE;
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;
    UINT16 tempStatus;
    LosProcessCB *processCB = NULL;

    if (taskPrio > OS_TASK_PRIORITY_LOWEST) {
        return LOS_ERRNO_TSK_PRIOR_ERROR;
    }

    if (OS_TID_CHECK_INVALID(taskID)) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    if (taskCB->taskStatus & OS_TASK_FLAG_SYSTEM_TASK) {
        return LOS_ERRNO_TSK_OPERATE_SYSTEM_TASK;
    }

    SCHEDULER_LOCK(intSave);
    tempStatus = taskCB->taskStatus;
    if (tempStatus & OS_TASK_STATUS_UNUSED) {
        SCHEDULER_UNLOCK(intSave);
        return LOS_ERRNO_TSK_NOT_CREATED;
    }

    /* delete the task and insert with right priority into ready queue */
    isReady = tempStatus & OS_TASK_STATUS_READY;
    if (isReady) {
        processCB = OS_PCB_FROM_PID(taskCB->processID);
        OS_TASK_PRI_QUEUE_DEQUEUE(processCB, taskCB);
        taskCB->priority = taskPrio;
        OS_TASK_PRI_QUEUE_ENQUEUE(processCB, taskCB);
    } else {
        taskCB->priority = taskPrio;
        if (tempStatus & OS_TASK_STATUS_RUNNING) {
            isReady = TRUE;
        }
    }

    SCHEDULER_UNLOCK(intSave);
    /* delete the task and insert with right priority into ready queue */
    if (isReady) {
        LOS_MpSchedule(OS_MP_CPU_ALL);
        LOS_Schedule();
    }
    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_CurTaskPriSet(UINT16 taskPrio)
{
    return LOS_TaskPriSet(OsCurrTaskGet()->taskID, taskPrio);
}

/*
 * Description : pend a task in list
 * Input       : list       --- wait task list
 *               taskStatus --- task status
 *               timeOut    ---  Expiry time
 * Return      : LOS_OK on success or LOS_NOK on failure
 */
UINT32 OsTaskWait(LOS_DL_LIST *list, UINT32 timeout, BOOL needSched)
{
    LosTaskCB *runTask = NULL;
    LOS_DL_LIST *pendObj = NULL;

    runTask = OsCurrTaskGet();
    OS_TASK_SCHED_QUEUE_DEQUEUE(runTask, OS_PROCESS_STATUS_PEND);
    pendObj = &runTask->pendList;
    runTask->taskStatus |= OS_TASK_STATUS_PEND;
    LOS_ListTailInsert(list, pendObj);
    if (timeout != LOS_WAIT_FOREVER) {
        runTask->taskStatus |= OS_TASK_STATUS_PEND_TIME;
        OsAdd2TimerList(runTask, timeout);
    }

    if (needSched == TRUE) {
        OsSchedResched();
        if (runTask->taskStatus & OS_TASK_STATUS_TIMEOUT) {
            runTask->taskStatus &= ~OS_TASK_STATUS_TIMEOUT;
            return LOS_ERRNO_TSK_TIMEOUT;
        }
    }
    return LOS_OK;
}

/*
 * Description : delete the task from pendlist and also add to the priqueue
 * Input       : resumedTask --- resumed task
 *               taskStatus  --- task status
 */
VOID OsTaskWake(LosTaskCB *resumedTask)
{
    LOS_ListDelete(&resumedTask->pendList);
    resumedTask->taskStatus &= ~OS_TASK_STATUS_PEND;

    if (resumedTask->taskStatus & OS_TASK_STATUS_PEND_TIME) {
        OsTimerListDelete(resumedTask);
        resumedTask->taskStatus &= ~OS_TASK_STATUS_PEND_TIME;
    }
    if (!(resumedTask->taskStatus & OS_TASK_STATUS_SUSPEND)) {
        OS_TASK_SCHED_QUEUE_ENQUEUE(resumedTask, OS_PROCESS_STATUS_PEND);
    }
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskYield(VOID)
{
    UINT32 tskCount;
    UINT32 intSave;
    LosTaskCB *runTask = NULL;
    LosProcessCB *runProcess = NULL;

    if (OS_INT_ACTIVE) {
        return LOS_ERRNO_TSK_YIELD_IN_INT;
    }

    if (!OsPreemptable()) {
        return LOS_ERRNO_TSK_YIELD_IN_LOCK;
    }

    runTask = OsCurrTaskGet();
    if (OS_TID_CHECK_INVALID(runTask->taskID)) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    SCHEDULER_LOCK(intSave);

    /* reset timeslice of yeilded task */
    runTask->timeSlice = 0;
    runProcess = OS_PCB_FROM_PID(runTask->processID);
    tskCount = OS_TASK_PRI_QUEUE_SIZE(runProcess, runTask);
    if (tskCount > 0) {
        OS_TASK_PRI_QUEUE_ENQUEUE(runProcess, runTask);
        runTask->taskStatus |= OS_TASK_STATUS_READY;
    } else {
        SCHEDULER_UNLOCK(intSave);
        return LOS_OK;
    }
    OsSchedResched();
    SCHEDULER_UNLOCK(intSave);
    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR VOID LOS_TaskLock(VOID)
{
    UINT32 intSave;
    UINT32 *losTaskLock = NULL;

    intSave = LOS_IntLock();
    losTaskLock = &OsPercpuGet()->taskLockCnt;
    (*losTaskLock)++;
    LOS_IntRestore(intSave);
}

LITE_OS_SEC_TEXT_MINOR VOID LOS_TaskUnlock(VOID)
{
    UINT32 intSave;
    UINT32 *losTaskLock = NULL;
    Percpu *percpu = NULL;

    intSave = LOS_IntLock();

    percpu = OsPercpuGet();
    losTaskLock = &OsPercpuGet()->taskLockCnt;
    if (*losTaskLock > 0) {
        (*losTaskLock)--;
        if ((*losTaskLock == 0) && (percpu->schedFlag == INT_PEND_RESCH) &&
            OS_SCHEDULER_ACTIVE) {
            percpu->schedFlag = INT_NO_RESCH;
            LOS_IntRestore(intSave);
            LOS_Schedule();
            return;
        }
    }

    LOS_IntRestore(intSave);
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskInfoGet(UINT32 taskID, TSK_INFO_S *taskInfo)
{
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;

    if (taskInfo == NULL) {
        return LOS_ERRNO_TSK_PTR_NULL;
    }

    if (OS_TID_CHECK_INVALID(taskID)) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    SCHEDULER_LOCK(intSave);
    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        SCHEDULER_UNLOCK(intSave);
        return LOS_ERRNO_TSK_NOT_CREATED;
    }

    if (!(taskCB->taskStatus & OS_TASK_STATUS_RUNNING) || OS_INT_ACTIVE) {
        taskInfo->uwSP = (UINTPTR)taskCB->stackPointer;
    } else {
        taskInfo->uwSP = ArchSPGet();
    }

    taskInfo->usTaskStatus = taskCB->taskStatus;
    taskInfo->usTaskPrio = taskCB->priority;
    taskInfo->uwStackSize = taskCB->stackSize;
    taskInfo->uwTopOfStack = taskCB->topOfStack;
    taskInfo->uwEventMask = taskCB->eventMask;
    taskInfo->taskEvent = taskCB->taskEvent;
    taskInfo->pTaskSem = taskCB->taskSem;
    taskInfo->pTaskMux = taskCB->taskMux;
    taskInfo->uwTaskID = taskID;

    if (strncpy_s(taskInfo->acName, LOS_TASK_NAMELEN, taskCB->taskName, LOS_TASK_NAMELEN - 1) != EOK) {
        PRINT_ERR("Task name copy failed!\n");
    }
    taskInfo->acName[LOS_TASK_NAMELEN - 1] = '\0';

    taskInfo->uwBottomOfStack = TRUNCATE(((UINTPTR)taskCB->topOfStack + taskCB->stackSize),
                                         OS_TASK_STACK_ADDR_ALIGN);
    taskInfo->uwCurrUsed = (UINT32)(taskInfo->uwBottomOfStack - taskInfo->uwSP);

    taskInfo->bOvf = OsStackWaterLineGet((const UINTPTR *)taskInfo->uwBottomOfStack,
                                         (const UINTPTR *)taskInfo->uwTopOfStack, &taskInfo->uwPeakUsed);
    SCHEDULER_UNLOCK(intSave);
    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT32 LOS_TaskCpuAffiSet(UINT32 taskID, UINT16 cpuAffiMask)
{
#if (LOSCFG_KERNEL_SMP == YES)
    LosTaskCB *taskCB = NULL;
    UINT32 intSave;
    BOOL needSched = FALSE;
    UINT16 currCpuMask;

    if (OS_TID_CHECK_INVALID(taskID)) {
        return LOS_ERRNO_TSK_ID_INVALID;
    }

    if (!(cpuAffiMask & LOSCFG_KERNEL_CPU_MASK)) {
        return LOS_ERRNO_TSK_CPU_AFFINITY_MASK_ERR;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    SCHEDULER_LOCK(intSave);
    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        SCHEDULER_UNLOCK(intSave);
        return LOS_ERRNO_TSK_NOT_CREATED;
    }

    taskCB->cpuAffiMask = cpuAffiMask;
    currCpuMask = CPUID_TO_AFFI_MASK(taskCB->currCpu);
    if (!(currCpuMask & cpuAffiMask)) {
        needSched = TRUE;
        taskCB->signal = SIGNAL_AFFI;
    }
    SCHEDULER_UNLOCK(intSave);

    if (needSched && OS_SCHEDULER_ACTIVE) {
        LOS_MpSchedule(currCpuMask);
        LOS_Schedule();
    }
#endif
    (VOID)taskID;
    (VOID)cpuAffiMask;
    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT16 LOS_TaskCpuAffiGet(UINT32 taskID)
{
#if (LOSCFG_KERNEL_SMP == YES)
#define INVALID_CPU_AFFI_MASK   0
    LosTaskCB *taskCB = NULL;
    UINT16 cpuAffiMask;
    UINT32 intSave;

    if (OS_TID_CHECK_INVALID(taskID)) {
        return INVALID_CPU_AFFI_MASK;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    SCHEDULER_LOCK(intSave);
    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        SCHEDULER_UNLOCK(intSave);
        return INVALID_CPU_AFFI_MASK;
    }

    cpuAffiMask = taskCB->cpuAffiMask;
    SCHEDULER_UNLOCK(intSave);

    return cpuAffiMask;
#else
    (VOID)taskID;
    return 1;
#endif
}

/*
 * Description : Process pending signals tagged by others cores
 */
LITE_OS_SEC_TEXT_MINOR UINT32 OsTaskProcSignal(VOID)
{
    Percpu *percpu = NULL;
    LosTaskCB *runTask = NULL;
    UINT32 intSave, ret;

    /*
     * private and uninterruptable, no protection needed.
     * while this task is always running when others cores see it,
     * so it keeps recieving signals while follow code excuting.
     */
    runTask = OsCurrTaskGet();
    if (runTask->signal == SIGNAL_NONE) {
        goto EXIT;
    }

    if (runTask->signal & SIGNAL_KILL) {
        /*
         * clear the signal, and do the task deletion. if the signaled task has been
         * scheduled out, then this deletion will wait until next run.
         */
        SCHEDULER_LOCK(intSave);
        runTask->signal = SIGNAL_NONE;
        ret = OsTaskDeleteUnsafe(runTask, OS_PRO_EXIT_OK, intSave);
        if (ret) {
            PRINT_ERR("Task proc signal delete task(%u) failed err:0x%x\n", runTask->taskID, ret);
        }
    } else if (runTask->signal & SIGNAL_SUSPEND) {
        runTask->signal &= ~SIGNAL_SUSPEND;

        /* suspend killed task may fail, ignore the result */
        (VOID)LOS_TaskSuspend(runTask->taskID);
#if (LOSCFG_KERNEL_SMP == YES)
    } else if (runTask->signal & SIGNAL_AFFI) {
        runTask->signal &= ~SIGNAL_AFFI;

        /* pri-queue has updated, notify the target cpu */
        LOS_MpSchedule((UINT32)runTask->cpuAffiMask);
#endif
    }

EXIT:
    /* check if needs to schedule */
    percpu = OsPercpuGet();
    if (OsPreemptable() && (percpu->schedFlag == INT_PEND_RESCH)) {
        percpu->schedFlag = INT_NO_RESCH;
        return INT_PEND_RESCH;
    }

    return INT_NO_RESCH;
}

LITE_OS_SEC_TEXT INT32 OsSetCurrTaskName(const CHAR *name)
{
    UINT32 intSave;
    UINT32 strLen;
    errno_t err;
    LosTaskCB *runTask = NULL;
    LosProcessCB *runProcess = NULL;
    const CHAR *namePtr = NULL;
    CHAR nameBuff[OS_TCB_NAME_LEN] = { 0 };

    runTask = OsCurrTaskGet();
    runProcess = OS_PCB_FROM_PID(runTask->processID);
    if (runProcess->processMode == OS_USER_MODE) {
        (VOID)LOS_ArchCopyFromUser(nameBuff, (const VOID *)name, OS_TCB_NAME_LEN);
        strLen = strnlen(nameBuff, OS_TCB_NAME_LEN);
        namePtr = nameBuff;
    } else {
        strLen = strnlen(name, OS_TCB_NAME_LEN);
        namePtr = name;
    }

    if (strLen == 0) {
        err = EINVAL;
        PRINT_ERR("set task(%u) name failed! %d\n", OsCurrTaskGet()->taskID, err);
        return err;
    } else if (strLen == OS_TCB_NAME_LEN) {
        strLen = strLen - 1;
    }

    SCHEDULER_LOCK(intSave);

    err = memcpy_s(runTask->taskName, OS_TCB_NAME_LEN, (VOID *)namePtr, strLen);
    if (err != EOK) {
        runTask->taskName[0] = '\0';
        err = EINVAL;
        goto EXIT;
    }

    runTask->taskName[strLen] = '\0';

    /* if thread is main thread, then set processName as taskName */
    if (runTask->taskID == runProcess->threadGroupID) {
        (VOID)memcpy_s(runProcess->processName, OS_PCB_NAME_LEN, (VOID *)runTask->taskName, OS_TCB_NAME_LEN);
    }

    SCHEDULER_UNLOCK(intSave);
    return LOS_OK;

EXIT:
    SCHEDULER_UNLOCK(intSave);
    return err;
}

LITE_OS_SEC_TEXT VOID OsTaskExitGroup(UINT32 status)
{
    LosProcessCB *processCB = NULL;
    LosTaskCB *taskCB = NULL;
    LOS_DL_LIST *list = NULL;
    LOS_DL_LIST *head = NULL;
    LosTaskCB *runTask[LOSCFG_KERNEL_CORE_NUM] = { 0 };
    UINT32 intSave;
#if (LOSCFG_KERNEL_SMP == YES)
    UINT16 cpu;
#endif

    SCHEDULER_LOCK(intSave);
    processCB = OsCurrProcessGet();
    if (processCB->processStatus & OS_PROCESS_FLAG_EXIT) {
        SCHEDULER_UNLOCK(intSave);
        return;
    }

    processCB->processStatus |= OS_PROCESS_FLAG_EXIT;
    runTask[ArchCurrCpuid()] = OsCurrTaskGet();
    runTask[ArchCurrCpuid()]->sig.sigprocmask = OS_INVALID_VALUE;

    list = &processCB->threadSiblingList;
    head = list;
    do {
        taskCB = LOS_DL_LIST_ENTRY(list->pstNext, LosTaskCB, threadList);
        if (!(taskCB->taskStatus & OS_TASK_STATUS_RUNNING)) {
            OsTaskDeleteInactive(processCB, taskCB);
        } else {
#if (LOSCFG_KERNEL_SMP == YES)
            if (taskCB->currCpu != ArchCurrCpuid()) {
                taskCB->signal = SIGNAL_KILL;
                runTask[taskCB->currCpu] = taskCB;
                LOS_MpSchedule(taskCB->currCpu);
            }
#endif
            list = list->pstNext;
        }
    } while (head != list->pstNext);

#if (LOSCFG_KERNEL_SMP == YES)
    for (cpu = 0; cpu < LOSCFG_KERNEL_CORE_NUM; cpu++) {
        if ((cpu == ArchCurrCpuid()) || (runTask[cpu] == NULL)) {
            continue;
        }

        (VOID)OsTaskSyncWait(runTask[cpu]);
    }
#endif
    SCHEDULER_UNLOCK(intSave);

    LOS_ASSERT(processCB->threadNumber == 1);
    return;
}

LITE_OS_SEC_TEXT VOID OsExecDestroyTaskGroup(VOID)
{
    OsTaskExitGroup(OS_PRO_EXIT_OK);
    OsTaskCBRecyleToFree();
}

LITE_OS_SEC_TEXT VOID OsProcessSuspendAllTask(VOID)
{
    LosProcessCB *process = NULL;
    LosTaskCB *taskCB = NULL;
    LosTaskCB *runTask = NULL;
    LOS_DL_LIST *list = NULL;
    LOS_DL_LIST *head = NULL;
    UINT32 intSave;
    UINT32 ret;

    SCHEDULER_LOCK(intSave);
    process = OsCurrProcessGet();
    runTask = OsCurrTaskGet();

    list = &process->threadSiblingList;
    head = list;
    do {
        taskCB = LOS_DL_LIST_ENTRY(list->pstNext, LosTaskCB, threadList);
        if (taskCB != runTask) {
            ret = OsTaskSuspend(taskCB);
            if ((ret != LOS_OK) && (ret != LOS_ERRNO_TSK_ALREADY_SUSPENDED)) {
                PRINT_ERR("process(%d) suspend all task(%u) failed! ERROR: 0x%x\n",
                          process->processID, taskCB->taskID, ret);
            }
        }
        list = list->pstNext;
    } while (head != list->pstNext);

    SCHEDULER_UNLOCK(intSave);
    return;
}

UINT32 OsUserTaskOperatePermissionsCheck(LosTaskCB *taskCB)
{
    if (taskCB == NULL) {
        return LOS_EINVAL;
    }

    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        return LOS_EINVAL;
    }

    if (OsCurrProcessGet()->processID != taskCB->processID) {
        return LOS_EPERM;
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT STATIC UINT32 OsCreateUserTaskParamCheck(UINT32 processID, TSK_INIT_PARAM_S *param)
{
    UserTaskParam *userParam = NULL;

    if (param == NULL) {
        return OS_INVALID_VALUE;
    }

    userParam = &param->userParam;
    if ((processID == OS_INVALID_VALUE) && !LOS_IsUserAddress(userParam->userArea)) {
        return OS_INVALID_VALUE;
    }

    if (!LOS_IsUserAddress((UINTPTR)param->pfnTaskEntry)) {
        return OS_INVALID_VALUE;
    }

    if ((!userParam->userMapSize) || !LOS_IsUserAddressRange(userParam->userMapBase, userParam->userMapSize)) {
        return OS_INVALID_VALUE;
    }

    if (userParam->userArea &&
        ((userParam->userSP <= userParam->userMapBase) ||
        (userParam->userSP > (userParam->userMapBase + userParam->userMapSize)))) {
        return OS_INVALID_VALUE;
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_INIT INT32 OsCreateUserTask(UINT32 processID, TSK_INIT_PARAM_S *initParam)
{
    LosProcessCB *processCB = NULL;
    UINT32 taskID;
    UINT32 ret;
    UINT32 intSave;

    ret = OsCreateUserTaskParamCheck(processID, initParam);
    if (ret != LOS_OK) {
        return ret;
    }

    initParam->uwStackSize = OS_USER_TASK_SYSCALL_SATCK_SIZE;
    initParam->usTaskPrio = OS_TASK_PRIORITY_LOWEST;
    initParam->policy = LOS_SCHED_RR;
    if (processID == OS_INVALID_VALUE) {
        SCHEDULER_LOCK(intSave);
        processCB = OsCurrProcessGet();
        initParam->processID = processCB->processID;
        initParam->consoleID = processCB->consoleID;
        SCHEDULER_UNLOCK(intSave);
    } else {
        processCB = OS_PCB_FROM_PID(processID);
        if (!(processCB->processStatus & (OS_PROCESS_STATUS_INIT | OS_PROCESS_STATUS_RUNNING))) {
            return OS_INVALID_VALUE;
        }
        initParam->processID = processID;
        initParam->consoleID = 0;
    }

    ret = LOS_TaskCreateOnly(&taskID, initParam);
    if (ret != LOS_OK) {
        return OS_INVALID_VALUE;
    }

    return taskID;
}

LITE_OS_SEC_TEXT INT32 LOS_GetTaskScheduler(INT32 taskID)
{
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;
    INT32 policy;

    if (OS_TID_CHECK_INVALID(taskID)) {
        return -LOS_EINVAL;
    }

    taskCB = OS_TCB_FROM_TID(taskID);
    SCHEDULER_LOCK(intSave);
    if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
        policy = -LOS_EINVAL;
        OS_GOTO_ERREND();
    }

    policy = taskCB->policy;

LOS_ERREND:
    SCHEDULER_UNLOCK(intSave);
    return policy;
}

LITE_OS_SEC_TEXT INT32 OsTaskSchedulerSetUnsafe(LosTaskCB *taskCB, UINT16 policy, UINT16 priority,
                                                BOOL policyFlag, UINT32 intSave)
{
    BOOL needSched = TRUE;
    if (taskCB->taskStatus & OS_TASK_STATUS_READY) {
        OS_TASK_PRI_QUEUE_DEQUEUE(OS_PCB_FROM_PID(taskCB->processID), taskCB);
    }

    if (policyFlag == TRUE) {
        if (policy == LOS_SCHED_FIFO) {
            taskCB->timeSlice = 0;
        }
        taskCB->policy = policy;
    }
    taskCB->priority = priority;

    if (taskCB->taskStatus & OS_TASK_STATUS_INIT) {
        taskCB->taskStatus &= ~OS_TASK_STATUS_INIT;
        taskCB->taskStatus |= OS_TASK_STATUS_READY;
    }

    if (taskCB->taskStatus & OS_TASK_STATUS_READY) {
        taskCB->taskStatus &= ~OS_TASK_STATUS_READY;
        OS_TASK_SCHED_QUEUE_ENQUEUE(taskCB, OS_PROCESS_STATUS_INIT);
    } else if (taskCB->taskStatus & OS_TASK_STATUS_RUNNING) {
        goto SCHEDULE;
    } else {
        needSched = FALSE;
    }

SCHEDULE:
    SCHEDULER_UNLOCK(intSave);

    LOS_MpSchedule(OS_MP_CPU_ALL);
    if (OS_SCHEDULER_ACTIVE && (needSched == TRUE)) {
        LOS_Schedule();
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT INT32 LOS_SetTaskScheduler(INT32 taskID, UINT16 policy, UINT16 priority)
{
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;

    if (OS_TID_CHECK_INVALID(taskID)) {
        return LOS_ESRCH;
    }

    if (priority > OS_TASK_PRIORITY_LOWEST) {
        return LOS_EINVAL;
    }

    if ((policy != LOS_SCHED_FIFO) && (policy != LOS_SCHED_RR)) {
        return LOS_EINVAL;
    }

    SCHEDULER_LOCK(intSave);
    taskCB = OS_TCB_FROM_TID(taskID);
    return OsTaskSchedulerSetUnsafe(taskCB, policy, priority, TRUE, intSave);
}

LITE_OS_SEC_TEXT VOID OsWriteResourceEvent(UINT32 events)
{
    (VOID)LOS_EventWrite(&g_resourceEvent, events);
}

STATIC VOID OsResourceRecoveryTask(VOID)
{
    UINT32 ret;

    while (1) {
        ret = LOS_EventRead(&g_resourceEvent, OS_RESOURCE_EVENT_MASK,
                            LOS_WAITMODE_OR | LOS_WAITMODE_CLR, LOS_WAIT_FOREVER);
        if (ret & (OS_RESOURCE_EVENT_FREE | OS_RESOURCE_EVENT_OOM)) {
            OsTaskCBRecyleToFree();

            OsProcessCBRecyleToFree();
        }

#ifdef LOSCFG_ENABLE_OOM_LOOP_TASK
        if (ret & OS_RESOURCE_EVENT_OOM) {
            (VOID)OomCheckProcess();
        }
#endif
    }
}

LITE_OS_SEC_TEXT UINT32 OsCreateResourceFreeTask(VOID)
{
    UINT32 ret;
    UINT32 taskID;
    TSK_INIT_PARAM_S taskInitParam;

    ret = LOS_EventInit((PEVENT_CB_S)&g_resourceEvent);
    if (ret != LOS_OK) {
        return LOS_NOK;
    }

    (VOID)memset_s((VOID *)(&taskInitParam), sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)OsResourceRecoveryTask;
    taskInitParam.uwStackSize = OS_TASK_RESOURCE_STATCI_SIZE;
    taskInitParam.pcName = "ResourcesTask";
    taskInitParam.usTaskPrio = OS_TASK_RESOURCE_FREE_PRIORITY;
    return LOS_TaskCreate(&taskID, &taskInitParam);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
