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

#include "cmsis_os.h"
#include "los_typedef.h"
#include "los_printf.h"

#include "los_event.h"
#include "los_membox.h"
#include "los_memory.h"
#include "los_hwi.h"

#include "los_mux_pri.h"
#include "los_queue_pri.h"
#include "los_sem_pri.h"
#include "los_swtmr_pri.h"
#include "los_sys_pri.h"
#include "los_task_pri.h"
#include "los_tick_pri.h"
#include "string.h"
#include "securec.h"
#include "system_config.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */
#if (CMSIS_OS_VER == 2)

/* Kernel initialization state */
static osKernelState_t g_kernelState;

extern BOOL g_taskScheduled;

#define LOS_PRIORITY_WIN 8

const osVersion_t g_stLosVersion = { 001, 001 };

#define LITEOS_VERSION_MAJOR 1
#define LITEOS_VERSION_MINOR 0
#define LITEOS_VERSION_BUILD 0

/* Kernel version and identification string definition */
#define KERNEL_VERSION            (((UINT32)LITEOS_VERSION_MAJOR * 10000000UL) | \
                                   ((UINT32)LITEOS_VERSION_MINOR *    10000UL) | \
                                   ((UINT32)LITEOS_VERSION_BUILD *        1UL))

#define KERNEL_ID "HUAWEI-LiteOS"
#define UNUSED(var) do { (void)var; } while(0)

//  ==== Kernel Management Functions ====
uint32_t osTaskStackWaterMarkGet(UINT32 taskID);


osStatus_t osKernelInitialize(void)
{
    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (g_kernelState != osKernelInactive) {
        return osError;
    }

    if (LOS_OK == LOS_KernelInit()) {
        g_kernelState = osKernelReady;
        return osOK;
    } else {
        return osError;
    }
}


osStatus_t osKernelGetInfo(osVersion_t *version, char *id_buf, uint32_t id_size)
{
    uint32_t uwRet;

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (version != NULL) {
        version->api = g_stLosVersion.api;
        version->kernel = g_stLosVersion.kernel;
    }

    if ((id_buf != NULL) && (id_size != 0U)) {
        if (id_size > sizeof(KERNEL_ID)) {
            id_size = sizeof(KERNEL_ID);
        }
        uwRet = memcpy_s(id_buf, id_size, KERNEL_ID, id_size);
        if (uwRet != EOK) {
            PRINT_ERR("%s[%d] memcpy failed, error type = %u\n", __FUNCTION__, __LINE__, uwRet);
            return osError;
        }
    }

    return osOK;
}


osKernelState_t osKernelGetState(void)
{
    if (OS_INT_ACTIVE) {
        return osKernelError;
    }

    if (!g_taskScheduled) {
        if (g_kernelState == osKernelReady) {
            return osKernelReady;
        } else {
            return osKernelInactive;
        }
    } else if (g_losTaskLock > 0) {
        return osKernelLocked;
    } else {
        return osKernelRunning;
    }
}


osStatus_t osKernelStart(void)
{
    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (g_kernelState == osKernelReady) {
        if (LOS_OK == LOS_Start()) {
            g_kernelState = osKernelRunning;
            return osOK;
        } else {
            return osError;
        }
    } else {
        return osError;
    }
}


int32_t osKernelLock(void)
{
    int32_t lock;

    if (OS_INT_ACTIVE) {
        return (int32_t)osErrorISR;
    }

    if (!g_taskScheduled) {
        return (int32_t)osError;
    }

    if (g_losTaskLock > 0) {
        lock = 1;
    } else {
        LOS_TaskLock();
        lock = 0;
    }

    return lock;
}


int32_t osKernelUnlock(void)
{
    int32_t lock;

    if (OS_INT_ACTIVE) {
        return (int32_t)osErrorISR;
    }

    if (!g_taskScheduled) {
        return (int32_t)osError;
    }

    if (g_losTaskLock > 0) {
        LOS_TaskUnlock();
        if (g_losTaskLock != 0) {
            return (int32_t)osError;
        }
        lock = 1;
    } else {
        lock = 0;
    }

    return lock;
}


int32_t osKernelRestoreLock(int32_t lock)
{
    if (OS_INT_ACTIVE) {
        return (int32_t)osErrorISR;
    }

    if (!g_taskScheduled) {
        return (int32_t)osError;
    }

    switch (lock) {
        case 0:
            LOS_TaskUnlock();
            if (g_losTaskLock != 0) {
                break;
            }
            return 0;
        case 1:
            LOS_TaskLock();
            return 1;
        default:
            break;
    }

    return (int32_t)osError;
}


uint32_t osKernelGetTickCount(void)
{
    uint64_t ticks;
    UINTPTR uvIntSave;

    if (OS_INT_ACTIVE) {
#ifndef LITEOS_WIFI_IOT_VERSION
        ticks = g_ullTickCount;
#else
        ticks = g_tickCount;
#endif
    } else {
        uvIntSave = LOS_IntLock();
#ifndef LITEOS_WIFI_IOT_VERSION
        ticks = g_ullTickCount;
#else
        ticks = g_tickCount;
#endif
        LOS_IntRestore(uvIntSave);
    }

    return (uint32_t)ticks;
}

uint32_t osKernelGetTickFreq(void)
{
    uint32_t freq;

    if (OS_INT_ACTIVE) {
        freq = 0U;
    } else {
        freq = LOSCFG_BASE_CORE_TICK_PER_SECOND;
    }

    return (freq);
}

extern VOID LOS_GetCpuCycle(UINT32 *puwCntHi, UINT32 *puwCntLo);
uint32_t osKernelGetSysTimerCount(void)
{
    uint32_t countHigh = 0;
    uint32_t countLow = 0;
    if (OS_INT_ACTIVE) {
        countLow = 0U;
    } else {
        LOS_GetCpuCycle((UINT32 *)&countHigh, (UINT32 *)&countLow);
    }
    return countLow;
}


uint32_t osKernelGetSysTimerFreq(void)
{
    return OS_SYS_CLOCK;
}


//  ==== Thread Management Functions ====

osThreadId_t osThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr)
{
    UINT32 uwTid;
    UINT32 uwRet;
    LosTaskCB *pstTaskCB = NULL;
    TSK_INIT_PARAM_S stTskInitParam;

    if (OS_INT_ACTIVE) {
        return NULL;
    }

    if ((attr == NULL) || (func == NULL) || (attr->priority < osPriorityLow1) ||
        (attr->priority > osPriorityAboveNormal6)) {
        return (osThreadId_t)NULL;
    }

    (void)memset_s(&stTskInitParam, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    stTskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)func;
#ifndef LITEOS_WIFI_IOT_VERSION
    stTskInitParam.uwArg = (UINT32)argument;
#else
    stTskInitParam.auwArgs[0] = (UINT32)argument;
#endif
    stTskInitParam.uwStackSize = attr->stack_size;
    stTskInitParam.pcName = (CHAR *)attr->name;
    stTskInitParam.usTaskPrio = OS_TASK_PRIORITY_LOWEST - ((UINT16)(attr->priority) - LOS_PRIORITY_WIN); /* 0~31 */

    uwRet = LOS_TaskCreate(&uwTid, &stTskInitParam);

    if (LOS_OK != uwRet) {
        return (osThreadId_t)NULL;
    }

    pstTaskCB = OS_TCB_FROM_TID(uwTid);

    return (osThreadId_t)pstTaskCB;
}


const char *osThreadGetName(osThreadId_t thread_id)
{
    LosTaskCB *pstTaskCB = NULL;

    if (OS_INT_ACTIVE || thread_id == NULL) {
        return NULL;
    }

    pstTaskCB = (LosTaskCB *)thread_id;

    return pstTaskCB->taskName;
}


osThreadId_t osThreadGetId(void)
{
    if (OS_INT_ACTIVE) {
        return NULL;
    }

    return (osThreadId_t)(g_losTask.runTask);
}

void *osThreadGetArgument(void)
{
    if (OS_INT_ACTIVE) {
        return 0;
    }

    LosTaskCB *taskCb = (LosTaskCB *)osThreadGetId();
    if (taskCb == NULL) {
        return NULL;
    }
#ifndef LITEOS_WIFI_IOT_VERSION
    return (void *)(taskCb->arg);
#else
    return (void *)(taskCb->args[0]);
#endif
}

osThreadState_t osThreadGetState(osThreadId_t thread_id)
{
    UINT16 taskStatus;
    osThreadState_t stState;
    LosTaskCB *pstTaskCB = NULL;

    if (OS_INT_ACTIVE || thread_id == NULL) {
        return osThreadError;
    }

    pstTaskCB = (LosTaskCB *)thread_id;
    taskStatus = pstTaskCB->taskStatus;

    if (taskStatus & OS_TASK_STATUS_RUNNING) {
        stState = osThreadRunning;
    } else if (taskStatus & OS_TASK_STATUS_READY) {
        stState = osThreadReady;
    } else if (taskStatus &
        (OS_TASK_STATUS_DELAY | OS_TASK_STATUS_PEND | OS_TASK_STATUS_SUSPEND | OS_TASK_STATUS_PEND_QUEUE)) {
        stState = osThreadBlocked;
    } else if (taskStatus & OS_TASK_STATUS_UNUSED) {
        stState = osThreadInactive;
    } else {
        stState = osThreadError;
    }

    return stState;
}


uint32_t osThreadGetStackSize(osThreadId_t thread_id)
{
    LosTaskCB *pstTaskCB = NULL;

    if (OS_INT_ACTIVE || thread_id == NULL) {
        return 0U;
    }

    pstTaskCB = (LosTaskCB *)thread_id;

    return pstTaskCB->stackSize;
}


uint32_t osTaskStackWaterMarkGet(UINT32 taskID)
{
    UINT32 uwCount = 0;
    UINT32 *ptopOfStack;
    UINTPTR uvIntSave;
    LosTaskCB *pstTaskCB = NULL;

    if (taskID > LOSCFG_BASE_CORE_TSK_LIMIT) {
        return 0;
    }

    uvIntSave = LOS_IntLock();

    pstTaskCB = OS_TCB_FROM_TID(taskID);
    if (OS_TASK_STATUS_UNUSED & (pstTaskCB->taskStatus)) {
        LOS_IntRestore(uvIntSave);
        return 0;
    }

    // first 4 bytes is OS_TASK_MAGIC_WORD, skip
    ptopOfStack = (UINT32 *)(UINTPTR)pstTaskCB->topOfStack + 1;

    while (*ptopOfStack == (UINT32)OS_TASK_STACK_INIT) {
        ++ptopOfStack;
        ++uwCount;
    }

    uwCount *= sizeof(UINT32);

    LOS_IntRestore(uvIntSave);
    return uwCount;
}


uint32_t osThreadGetStackSpace(osThreadId_t thread_id)
{
    LosTaskCB *pstTaskCB = NULL;

    if (OS_INT_ACTIVE || thread_id == NULL) {
        return 0U;
    }

    pstTaskCB = (LosTaskCB *)thread_id;

    return osTaskStackWaterMarkGet(pstTaskCB->taskID);
}


osStatus_t osThreadSetPriority(osThreadId_t thread_id, osPriority_t priority)
{
    UINT32 uwRet;
    UINT16 usPriority;
    LosTaskCB *pstTaskCB = NULL;

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (thread_id == NULL) {
        return osErrorParameter;
    }

    if (priority < osPriorityLow1 || priority > osPriorityAboveNormal6) {
        return osErrorParameter;
    }

    pstTaskCB = (LosTaskCB *)thread_id;
    usPriority = OS_TASK_PRIORITY_LOWEST - ((UINT16)priority - LOS_PRIORITY_WIN);
    uwRet = LOS_TaskPriSet(pstTaskCB->taskID, usPriority);
    switch (uwRet) {
        case LOS_ERRNO_TSK_PRIOR_ERROR:
        case LOS_ERRNO_TSK_OPERATE_IDLE:
        case LOS_ERRNO_TSK_ID_INVALID:
            return osErrorParameter;

        case LOS_ERRNO_TSK_NOT_CREATED:
            return osErrorResource;

        default:
            return osOK;
    }
}


osPriority_t osThreadGetPriority(osThreadId_t thread_id)
{
    UINT16 usRet;
    LosTaskCB *pstTaskCB = NULL;

    if (OS_INT_ACTIVE || thread_id == NULL) {
        return osPriorityError;
    }

    pstTaskCB = (LosTaskCB *)thread_id;
    usRet = LOS_TaskPriGet(pstTaskCB->taskID);

    if (usRet == (UINT16)OS_INVALID) {
        return osPriorityError;
    }

    return (osPriority_t)(OS_TASK_PRIORITY_LOWEST - (usRet - LOS_PRIORITY_WIN));
}


osStatus_t osThreadYield(void)
{
    UINT32 uwRet;

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    uwRet = LOS_TaskYield();

    if (uwRet == LOS_OK) {
        return osOK;
    }

    return osError;
}


osStatus_t osThreadSuspend(osThreadId_t thread_id)
{
    UINT32 uwRet;
    LosTaskCB *pstTaskCB = NULL;

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (thread_id == NULL) {
        return osErrorParameter;
    }

    pstTaskCB = (LosTaskCB *)thread_id;
    uwRet = LOS_TaskSuspend(pstTaskCB->taskID);
    switch (uwRet) {
        case LOS_ERRNO_TSK_OPERATE_IDLE:
        case LOS_ERRNO_TSK_SUSPEND_SWTMR_NOT_ALLOWED:
        case LOS_ERRNO_TSK_ID_INVALID:
            return osErrorParameter;

        case LOS_ERRNO_TSK_NOT_CREATED:
        case LOS_ERRNO_TSK_ALREADY_SUSPENDED:
        case LOS_ERRNO_TSK_SUSPEND_LOCKED:
            return osErrorResource;

        default:
            return osOK;
    }
}


osStatus_t osThreadResume(osThreadId_t thread_id)
{
    UINT32 uwRet;
    LosTaskCB *pstTaskCB = NULL;

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (thread_id == NULL) {
        return osErrorParameter;
    }

    pstTaskCB = (LosTaskCB *)thread_id;
    uwRet = LOS_TaskResume(pstTaskCB->taskID);

    switch (uwRet) {
        case LOS_ERRNO_TSK_ID_INVALID:
            return osErrorParameter;

        case LOS_ERRNO_TSK_NOT_CREATED:
        case LOS_ERRNO_TSK_NOT_SUSPENDED:
            return osErrorResource;

        default:
            return osOK;
    }
}


osStatus_t osThreadTerminate(osThreadId_t thread_id)
{
    UINT32 uwRet;
    LosTaskCB *pstTaskCB = NULL;

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (thread_id == NULL) {
        return osErrorParameter;
    }

    pstTaskCB = (LosTaskCB *)thread_id;
    uwRet = LOS_TaskDelete(pstTaskCB->taskID);

    switch (uwRet) {
        case LOS_ERRNO_TSK_OPERATE_IDLE:
        case LOS_ERRNO_TSK_SUSPEND_SWTMR_NOT_ALLOWED:
        case LOS_ERRNO_TSK_ID_INVALID:
            return osErrorParameter;

        case LOS_ERRNO_TSK_NOT_CREATED:
            return osErrorResource;

        default:
            return osOK;
    }
}


uint32_t osThreadGetCount(void)
{
    uint32_t uwCount = 0;

    if (OS_INT_ACTIVE) {
        return 0U;
    }

    for (uint32_t index = 0; index <= LOSCFG_BASE_CORE_TSK_LIMIT; index++) {
        if (!((g_taskCBArray + index)->taskStatus & OS_TASK_STATUS_UNUSED)) {
            uwCount++;
        }
    }

    return uwCount;
}


//  ==== Generic Wait Functions ====
WEAK UINT32 LOS_HalDelay(UINT32 ticks)
{
    UNUSED(ticks);
    return LOS_ERRNO_TSK_DELAY_IN_INT;
}


osStatus_t osDelay(uint32_t ticks)
{
    UINT32 uwRet = 0;
    if (ticks == 0) {
        return osOK;
    }
    if (osKernelGetState() != osKernelRunning) {
        uwRet = LOS_HalDelay(ticks);
    } else {
        uwRet = LOS_TaskDelay(ticks);
    }
    if (uwRet == LOS_OK) {
        return osOK;
    } else {
        return osError;
    }
}


osStatus_t osDelayUntil(uint32_t ticks)
{
    UINT32 uwRet;
    UINT32 uwTicks;
    UINT32 tickCount = osKernelGetTickCount();

    if (ticks < tickCount) {
        return osError;
    }

    uwTicks = (UINT32)(ticks - tickCount);

    uwRet = LOS_TaskDelay(uwTicks);
    if (uwRet == LOS_OK) {
        return osOK;
    } else {
        return osError;
    }
}

//  ==== Timer Management Functions ====
#if (LOSCFG_BASE_CORE_SWTMR == YES)
#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
osTimerId_t osTimerExtNew(osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr,
    os_timer_rouses_type ucRouses, os_timer_align_type ucSensitive)
{
    UNUSED(attr);
    UINT16 usSwTmrID;
    UINT8 mode;

    if ((OS_INT_ACTIVE) || (NULL == func) || ((osTimerOnce != type) && (osTimerPeriodic != type))) {
        return (osTimerId_t)NULL;
    }

    if (osTimerOnce == type) {
        mode = LOS_SWTMR_MODE_NO_SELFDELETE;
    } else {
        mode = LOS_SWTMR_MODE_PERIOD;
    }
    if (LOS_OK != LOS_SwtmrCreate(1, mode, (SWTMR_PROC_FUNC)func, &usSwTmrID, (UINT32)(UINTPTR)argument, ucRouses, ucSensitive)) {
        return (osTimerId_t)NULL;
    }

    return (osTimerId_t)OS_SWT_FROM_SID(usSwTmrID);
}
#endif
osTimerId_t osTimerNew(osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr)
{
    UNUSED(attr);
    UINT16 usSwTmrID;
    UINT8 mode;

    if ((OS_INT_ACTIVE) || (NULL == func) || ((osTimerOnce != type) && (osTimerPeriodic != type))) {
        return (osTimerId_t)NULL;
    }

    if (osTimerOnce == type) {
        mode = LOS_SWTMR_MODE_NO_SELFDELETE;
    } else {
        mode = LOS_SWTMR_MODE_PERIOD;
    }
#if (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES)
    if (LOS_OK != LOS_SwtmrCreate(1, mode, (SWTMR_PROC_FUNC)func, &usSwTmrID, (UINT32)(UINTPTR)argument,
        osTimerRousesAllow, osTimerAlignIgnore)) {
        return (osTimerId_t)NULL;
    }
#else
    if (LOS_OK != LOS_SwtmrCreate(1, mode, (SWTMR_PROC_FUNC)func, &usSwTmrID, (UINT32)(UINTPTR)argument)) {
        return (osTimerId_t)NULL;
    }
#endif

    return (osTimerId_t)OS_SWT_FROM_SID(usSwTmrID);
}

osStatus_t osTimerStart(osTimerId_t timer_id, uint32_t ticks)
{
    UINT32 uwRet;
    SWTMR_CTRL_S *pstSwtmr;

    if ((0 == ticks) || (NULL == timer_id)) {
        return osErrorParameter;
    }

    pstSwtmr = (SWTMR_CTRL_S *)timer_id;
    pstSwtmr->uwInterval = ticks;
    uwRet = LOS_SwtmrStart(pstSwtmr->usTimerID);
    if (LOS_OK == uwRet) {
        return osOK;
    } else if (LOS_ERRNO_SWTMR_ID_INVALID == uwRet) {
        return osErrorParameter;
    } else {
        return osErrorResource;
    }
}


const char *osTimerGetName(osTimerId_t timer_id)
{
    UNUSED(timer_id);
    return (const char *)NULL;
}


osStatus_t osTimerStop(osTimerId_t timer_id)
{
    UINT32 uwRet;
    SWTMR_CTRL_S *pstSwtmr = (SWTMR_CTRL_S *)timer_id;

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (NULL == pstSwtmr) {
        return osErrorParameter;
    }

    uwRet = LOS_SwtmrStop(pstSwtmr->usTimerID);
    if (LOS_OK == uwRet) {
        return osOK;
    } else if (LOS_ERRNO_SWTMR_ID_INVALID == uwRet) {
        return osErrorParameter;
    } else {
        return osErrorResource;
    }
}


uint32_t osTimerIsRunning(osTimerId_t timer_id)
{
    if ((OS_INT_ACTIVE) || (NULL == timer_id)) {
        return 0;
    }

    return (OS_SWTMR_STATUS_TICKING == ((SWTMR_CTRL_S *)timer_id)->ucState);
}


osStatus_t osTimerDelete(osTimerId_t timer_id)
{
    UINT32 uwRet;
    SWTMR_CTRL_S *pstSwtmr = (SWTMR_CTRL_S *)timer_id;

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (NULL == pstSwtmr) {
        return osErrorParameter;
    }

    uwRet = LOS_SwtmrDelete(pstSwtmr->usTimerID);
    if (LOS_OK == uwRet) {
        return osOK;
    } else if (LOS_ERRNO_SWTMR_ID_INVALID == uwRet) {
        return osErrorParameter;
    } else {
        return osErrorResource;
    }
}
#endif

osEventFlagsId_t osEventFlagsNew(const osEventFlagsAttr_t *attr)
{
    PEVENT_CB_S pstEventCB;
    UINT32 uwRet;

    UNUSED(attr);

    if (OS_INT_ACTIVE) {
        return (osEventFlagsId_t)NULL;
    }

    pstEventCB = (PEVENT_CB_S)LOS_MemAlloc(m_aucSysMem0, sizeof(EVENT_CB_S));
    if (pstEventCB == NULL) {
        return (osEventFlagsId_t)NULL;
    }

    uwRet = LOS_EventInit(pstEventCB);
    if (uwRet == LOS_ERRNO_EVENT_PTR_NULL) {
        return (osEventFlagsId_t)NULL;
    } else {
        return (osEventFlagsId_t)pstEventCB;
    }
}


const char *osEventFlagsGetName(osEventFlagsId_t ef_id)
{
    UNUSED(ef_id);

    if (OS_INT_ACTIVE) {
        return (const char *)NULL;
    }

    return (const char *)NULL;
}


uint32_t osEventFlagsSet(osEventFlagsId_t ef_id, uint32_t flags)
{
    PEVENT_CB_S pstEventCB = (PEVENT_CB_S)ef_id;
    UINT32 uwRet;
    uint32_t rflags;
    if (pstEventCB == NULL) {
        return osFlagsErrorParameter;
    }
    uwRet = LOS_EventWrite(pstEventCB, (UINT32)flags);
    if (uwRet != LOS_OK) {
        return (uint32_t)osFlagsErrorParameter;
    } else {
        rflags = pstEventCB->uwEventID;
        return rflags;
    }
}


uint32_t osEventFlagsClear(osEventFlagsId_t ef_id, uint32_t flags)
{
    PEVENT_CB_S pstEventCB = (PEVENT_CB_S)ef_id;
    UINTPTR uwIntSave;
    uint32_t rflags;
    UINT32 uwRet;

    if (pstEventCB == NULL) {
        return (uint32_t)osFlagsErrorParameter;
    }

    uwIntSave = LOS_IntLock();
    rflags = pstEventCB->uwEventID;

    uwRet = LOS_EventClear(pstEventCB, ~flags);
    LOS_IntRestore(uwIntSave);
    if (uwRet != LOS_OK) {
        return (uint32_t)osFlagsErrorParameter;
    } else {
        return rflags;
    }
}


uint32_t osEventFlagsGet(osEventFlagsId_t ef_id)
{
    PEVENT_CB_S pstEventCB = (PEVENT_CB_S)ef_id;
    UINTPTR uwIntSave;
    uint32_t rflags;

    if (pstEventCB == NULL) {
        return (uint32_t)osFlagsErrorParameter;
    }

    uwIntSave = LOS_IntLock();
    rflags = pstEventCB->uwEventID;
    LOS_IntRestore(uwIntSave);

    return rflags;
}

uint32_t osEventFlagsWait(osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout)
{
    PEVENT_CB_S pstEventCB = (PEVENT_CB_S)ef_id;
    UINT32 uwMode = 0;
    UINT32 uwRet;
    uint32_t rflags;

    if (options > (osFlagsWaitAny | osFlagsWaitAll | osFlagsNoClear)) {
        return (uint32_t)osFlagsErrorParameter;
    }

    if ((options & osFlagsWaitAll) == osFlagsWaitAll) {
        uwMode |= LOS_WAITMODE_AND;
    } else {
        uwMode |= LOS_WAITMODE_OR;
    }

    if ((options & osFlagsNoClear) == osFlagsNoClear) {
        uwMode &= ~LOS_WAITMODE_CLR;
    } else {
        uwMode |= LOS_WAITMODE_CLR;
    }

    uwRet = LOS_EventRead(pstEventCB, (UINT32)flags, uwMode, (UINT32)timeout);
    switch (uwRet) {
        case LOS_ERRNO_EVENT_PTR_NULL:
        case LOS_ERRNO_EVENT_EVENTMASK_INVALID:
        case LOS_ERRNO_EVENT_SETBIT_INVALID:
            return (uint32_t)osFlagsErrorParameter;

        case LOS_ERRNO_EVENT_READ_IN_INTERRUPT:
        case LOS_ERRNO_EVENT_FLAGS_INVALID:
        case LOS_ERRNO_EVENT_READ_IN_LOCK:
            return (uint32_t)osFlagsErrorResource;

        case LOS_ERRNO_EVENT_READ_TIMEOUT:
            return (uint32_t)osFlagsErrorTimeout;

        default:
            rflags = (uint32_t)uwRet;
            return rflags;
    }
}

osStatus_t osEventFlagsDelete(osEventFlagsId_t ef_id)
{
    PEVENT_CB_S pstEventCB = (PEVENT_CB_S)ef_id;
    UINTPTR uwIntSave;
    osStatus_t uwRet;

    uwIntSave = LOS_IntLock();
    if (LOS_EventDestroy(pstEventCB) == LOS_OK) {
        uwRet = osOK;
    } else {
        uwRet = osErrorParameter;
    }
    LOS_IntRestore(uwIntSave);

    if (LOS_MemFree(m_aucSysMem0, (void *)pstEventCB) == LOS_OK) {
        uwRet = osOK;
    } else {
        uwRet = osErrorParameter;
    }

    return uwRet;
}

//  ==== Mutex Management Functions ====
#if (LOSCFG_BASE_IPC_MUX == YES)
osMutexId_t osMutexNew(const osMutexAttr_t *attr)
{
    UINT32 uwRet;
    UINT32 uwMuxId;

    UNUSED(attr);

    if (OS_INT_ACTIVE) {
        return NULL;
    }

    uwRet = LOS_MuxCreate(&uwMuxId);
    if (uwRet == LOS_OK) {
        return (osMutexId_t)(GET_MUX(uwMuxId));
    } else {
        return (osMutexId_t)NULL;
    }
}


osStatus_t osMutexAcquire(osMutexId_t mutex_id, uint32_t timeout)
{
    UINT32 uwRet;

    if (mutex_id == NULL) {
        return osErrorParameter;
    }

    if (OS_INT_ACTIVE && (timeout != LOS_NO_WAIT)) {
        timeout = 0;
    }

    uwRet = LOS_MuxPend(((LosMuxCB *)mutex_id)->muxID, timeout);
    if (uwRet == LOS_OK) {
        return osOK;
    } else if (uwRet == LOS_ERRNO_MUX_TIMEOUT) {
        return osErrorTimeout;
    } else if (uwRet == LOS_ERRNO_MUX_INVALID) {
        return osErrorParameter;
    } else {
        return osErrorResource;
    }
}


osStatus_t osMutexRelease(osMutexId_t mutex_id)
{
    UINT32 uwRet;

    if (mutex_id == NULL) {
        return osErrorParameter;
    }

    uwRet = LOS_MuxPost(((LosMuxCB *)mutex_id)->muxID);
    if (uwRet == LOS_OK) {
        return osOK;
    } else {
        return osErrorResource;
    }
}


osThreadId_t osMutexGetOwner(osMutexId_t mutex_id)
{
    UINT32 uwIntSave;
    LosTaskCB *pstTaskCB;

    if (OS_INT_ACTIVE) {
        return NULL;
    }

    if (mutex_id == NULL) {
        return NULL;
    }

    uwIntSave = LOS_IntLock();
    pstTaskCB = ((LosMuxCB *)mutex_id)->owner;
    LOS_IntRestore(uwIntSave);

    return (osThreadId_t)pstTaskCB;
}


osStatus_t osMutexDelete(osMutexId_t mutex_id)
{
    UINT32 uwRet;

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (mutex_id == NULL) {
        return osErrorParameter;
    }

    uwRet = LOS_MuxDelete(((LosMuxCB *)mutex_id)->muxID);
    if (uwRet == LOS_OK) {
        return osOK;
    } else if (uwRet == LOS_ERRNO_MUX_INVALID) {
        return osErrorParameter;
    } else {
        return osErrorResource;
    }
}
#endif

//  ==== Semaphore Management Functions ====
#if (LOSCFG_BASE_IPC_SEM == YES)

osSemaphoreId_t osSemaphoreNew(uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr)
{
    UINT32 uwRet;
    UINT32 uwSemId;

    UNUSED(attr);

    if (OS_INT_ACTIVE) {
        return (osSemaphoreId_t)NULL;
    }

    if (1 == max_count) {
        uwRet = LOS_BinarySemCreate((UINT16)initial_count, &uwSemId);
    } else {
        uwRet = LOS_SemCreate((UINT16)initial_count, &uwSemId);
    }

    if (uwRet == LOS_OK) {
        return (osSemaphoreId_t)(GET_SEM(uwSemId));
    } else {
        return (osSemaphoreId_t)NULL;
    }
}


osStatus_t osSemaphoreAcquire(osSemaphoreId_t semaphore_id, uint32_t timeout)
{
    UINT32 uwRet;

    if (semaphore_id == NULL) {
        return osErrorParameter;
    }

    if (OS_INT_ACTIVE && (timeout != LOS_NO_WAIT)) {
        return osErrorISR;
    }

    uwRet = LOS_SemPend(((LosSemCB *)semaphore_id)->semID, timeout);
    if (uwRet == LOS_OK) {
        return osOK;
    } else if (uwRet == LOS_ERRNO_SEM_TIMEOUT) {
        return osErrorTimeout;
    } else if (uwRet == LOS_ERRNO_SEM_INVALID) {
        return osErrorParameter;
    } else if (uwRet == LOS_ERRNO_SEM_PEND_INTERR) {
        return osErrorISR;
    } else {
        return osErrorResource;
    }
}


osStatus_t osSemaphoreRelease(osSemaphoreId_t semaphore_id)
{
    UINT32 uwRet;

    if (semaphore_id == NULL) {
        return osErrorParameter;
    }

    uwRet = LOS_SemPost(((LosSemCB *)semaphore_id)->semID);
    if (uwRet == LOS_OK) {
        return osOK;
    } else if (uwRet == LOS_ERRNO_SEM_INVALID) {
        return osErrorParameter;
    } else {
        return osErrorResource;
    }
}


uint32_t osSemaphoreGetCount(osSemaphoreId_t semaphore_id)
{
    UINT32 uwIntSave;
    UINT32 uwCount;

    if (OS_INT_ACTIVE) {
        return 0;
    }

    if (semaphore_id == NULL) {
        return 0;
    }

    uwIntSave = LOS_IntLock();
    uwCount = ((LosSemCB *)semaphore_id)->semCount;
    LOS_IntRestore(uwIntSave);

    return uwCount;
}


osStatus_t osSemaphoreDelete(osSemaphoreId_t semaphore_id)
{
    UINT32 uwRet;

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    if (semaphore_id == NULL) {
        return osErrorParameter;
    }

    uwRet = LOS_SemDelete(((LosSemCB *)semaphore_id)->semID);
    if (uwRet == LOS_OK) {
        return osOK;
    } else if (uwRet == LOS_ERRNO_SEM_INVALID) {
        return osErrorParameter;
    } else {
        return osErrorResource;
    }
}
#endif


//  ==== Message Queue Management Functions ====
#if (LOSCFG_BASE_IPC_QUEUE == YES)
osMessageQueueId_t osMessageQueueNew(uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr)
{
    UINT32 uwQueueID;
    UINT32 uwRet;
    UNUSED(attr);
    osMessageQueueId_t handle;

    if (0 == msg_count || 0 == msg_size || OS_INT_ACTIVE) {
        return (osMessageQueueId_t)NULL;
    }

    uwRet = LOS_QueueCreate((char *)NULL, (UINT16)msg_count, &uwQueueID, 0, (UINT16)msg_size);
    if (uwRet == LOS_OK) {
        handle = (osMessageQueueId_t)(GET_QUEUE_HANDLE(uwQueueID));
    } else {
        handle = (osMessageQueueId_t)NULL;
    }

    return handle;
}


osStatus_t osMessageQueuePut(osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)
{
    UNUSED(msg_prio);
    UINT32 uwRet;
    UINT32 uwBufferSize;
    LosQueueCB *pstQueue = (LosQueueCB *)mq_id;

    if (pstQueue == NULL || msg_ptr == NULL || ((OS_INT_ACTIVE) && (0 != timeout))) {
        return osErrorParameter;
    }
    if (pstQueue->queueSize < sizeof(UINT32)) {
        return osErrorParameter;
    }
    uwBufferSize = (UINT32)(pstQueue->queueSize - sizeof(UINT32));
    uwRet = LOS_QueueWriteCopy((UINT32)pstQueue->queueID, (void *)msg_ptr, uwBufferSize, timeout);
    if (uwRet == LOS_OK) {
        return osOK;
    } else if (uwRet == LOS_ERRNO_QUEUE_INVALID || uwRet == LOS_ERRNO_QUEUE_NOT_CREATE) {
        return osErrorParameter;
    } else if (uwRet == LOS_ERRNO_QUEUE_TIMEOUT) {
        return osErrorTimeout;
    } else {
        return osErrorResource;
    }
}


osStatus_t osMessageQueueGet(osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
{
    UNUSED(msg_prio);
    UINT32 uwRet;
    UINT32 uwBufferSize;
    LosQueueCB *pstQueue = (LosQueueCB *)mq_id;

    if (pstQueue == NULL || msg_ptr == NULL || ((OS_INT_ACTIVE) && (0 != timeout))) {
        return osErrorParameter;
    }

    uwBufferSize = (UINT32)(pstQueue->queueSize - sizeof(UINT32));
    uwRet = LOS_QueueReadCopy((UINT32)pstQueue->queueID, msg_ptr, &uwBufferSize, timeout);
    if (uwRet == LOS_OK) {
        return osOK;
    } else if (uwRet == LOS_ERRNO_QUEUE_INVALID || uwRet == LOS_ERRNO_QUEUE_NOT_CREATE) {
        return osErrorParameter;
    } else if (uwRet == LOS_ERRNO_QUEUE_TIMEOUT) {
        return osErrorTimeout;
    } else {
        return osErrorResource;
    }
}

uint32_t osMessageQueueGetCapacity(osMessageQueueId_t mq_id)
{
    uint32_t capacity;
    LosQueueCB *pstQueue = (LosQueueCB *)mq_id;

    if (pstQueue == NULL) {
        capacity = 0U;
    } else {
        capacity = pstQueue->queueLen;
    }

    return (capacity);
}

uint32_t osMessageQueueGetMsgSize(osMessageQueueId_t mq_id)
{
    uint32_t size;
    LosQueueCB *pstQueue = (LosQueueCB *)mq_id;

    if (pstQueue == NULL) {
        size = 0U;
    } else {
        size = pstQueue->queueSize - sizeof(UINT32);
    }

    return (size);
}


uint32_t osMessageQueueGetCount(osMessageQueueId_t mq_id)
{
    uint32_t count;
    UINTPTR uwIntSave;
    LosQueueCB *pstQueue = (LosQueueCB *)mq_id;

    if (pstQueue == NULL) {
        count = 0U;
    } else {
        uwIntSave = LOS_IntLock();
        count = (uint32_t)(pstQueue->readWriteableCnt[OS_QUEUE_READ]);
        LOS_IntRestore(uwIntSave);
    }
    return count;
}


uint32_t osMessageQueueGetSpace(osMessageQueueId_t mq_id)
{
    uint32_t space;
    UINTPTR uwIntSave;
    LosQueueCB *pstQueue = (LosQueueCB *)mq_id;

    if (pstQueue == NULL) {
        space = 0U;
    } else {
        uwIntSave = LOS_IntLock();
        space = (uint32_t)pstQueue->readWriteableCnt[OS_QUEUE_WRITE];
        LOS_IntRestore(uwIntSave);
    }
    return space;
}

osStatus_t osMessageQueueDelete(osMessageQueueId_t mq_id)
{
    LosQueueCB *pstQueue = (LosQueueCB *)mq_id;
    UINT32 uwRet;

    if (pstQueue == NULL) {
        return osErrorParameter;
    }

    if (OS_INT_ACTIVE) {
        return osErrorISR;
    }

    uwRet = LOS_QueueDelete((UINT32)pstQueue->queueID);
    if (uwRet == LOS_OK) {
        return osOK;
    } else if (uwRet == LOS_ERRNO_QUEUE_NOT_FOUND || uwRet == LOS_ERRNO_QUEUE_NOT_CREATE) {
        return osErrorParameter;
    } else {
        return osErrorResource;
    }
}
void osThreadExit(void)
{
    return;
}
#endif

#endif // (CMSIS_OS_VER == 2)
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
