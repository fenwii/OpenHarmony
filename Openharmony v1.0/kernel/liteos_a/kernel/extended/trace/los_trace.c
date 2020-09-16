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

#include "los_trace_pri.h"
#include "securec.h"
#include "los_typedef.h"
#include "los_task_pri.h"
#include "los_memory.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#if (LOSCFG_KERNEL_TRACE == YES)
LITE_OS_SEC_BSS SPIN_LOCK_INIT(g_traceSpin);
#define TRACE_LOCK(state)       LOS_SpinLockSave(&g_traceSpin, &(state))
#define TRACE_UNLOCK(state)     LOS_SpinUnlockRestore(&g_traceSpin, (state))

STATIC SPIN_LOCK_S g_traceCpuSpin[LOSCFG_KERNEL_CORE_NUM];
#define TRACE_CPU_LOCK(state, cpuID)       LOS_SpinLockSave(&g_traceCpuSpin[(cpuID)], &(state))
#define TRACE_CPU_UNLOCK(state, cpuID)     LOS_SpinUnlockRestore(&g_traceCpuSpin[(cpuID)], (state))

STATIC TraceBuffer g_traceBuf[LOSCFG_KERNEL_CORE_NUM];
STATIC TraceHook *g_traceInfo[LOS_TRACE_TYPE_NUM];
STATIC UINT16 g_frameSize[LOS_TRACE_TYPE_NUM];

STATIC VOID OsTracePosAdj(UINT16 bufferSize)
{
    UINT32 cpu = ArchCurrCpuid();
    if ((g_traceBuf[cpu].tracePos == LOS_TRACE_BUFFER_SIZE) ||
        ((g_traceBuf[cpu].tracePos + bufferSize + LOS_TRACE_TAG_LENGTH) > LOS_TRACE_BUFFER_SIZE)) {
        /* When wrap happened, record the postion before wrap */
        g_traceBuf[cpu].traceWrapPos = g_traceBuf[cpu].tracePos;
        g_traceBuf[cpu].tracePos = 0;
    }
}

STATIC UINT16 OsTaskTrace(UINT8 *inputBuffer, UINT32 newTaskID, UINT32 oldTaskID)
{
    TaskTraceFrame *taskInfo = NULL;

    if (inputBuffer == NULL) {
        return 0;
    }

    taskInfo = (TaskTraceFrame *)inputBuffer;
    taskInfo->currentTick = LOS_TickCountGet();
    taskInfo->srcTaskId = oldTaskID;
    taskInfo->destTaskId = newTaskID;

    return sizeof(TaskTraceFrame);
}

STATIC UINT16 OsIntTrace(UINT8 *inputBuffer, UINT32 newIrqNum, UINT32 direFlag)
{
    IntTraceFrame *interruptInfo = NULL;
    UINT16 useSize = 0;

    if (inputBuffer == NULL) {
        return 0;
    }

    /* ignore tick and uart interrupts */
    if ((newIrqNum != OS_TICK_INT_NUM) && (newIrqNum != NUM_HAL_INTERRUPT_UART)) {
        useSize = sizeof(IntTraceFrame);
        interruptInfo = (IntTraceFrame *)inputBuffer;
        interruptInfo->currentTick = LOS_TickCountGet();
        interruptInfo->irqNum = newIrqNum;
        interruptInfo->irqDirection = direFlag;
    }

    return useSize;
}

UINT32 OsTraceReg(TraceType traceType, WriteHook inHook)
{
    TraceHook *traceInfo = NULL;

    if (g_traceInfo[traceType]) {
        /* The Buffer has been alocated before */
        traceInfo = g_traceInfo[traceType];
    } else {
        /* First time allocate */
        traceInfo = (TraceHook *)LOS_MemAlloc(m_aucSysMem0, sizeof(TraceHook));
        if (traceInfo == NULL) {
            return LOS_ERRNO_TRACE_NO_MEMORY;
        }

        g_traceInfo[traceType] = traceInfo;
    }

    traceInfo->type = traceType;
    traceInfo->inputHook = inHook;

    return LOS_OK;
}

UINT32 LOS_TraceInit(VOID)
{
    UINT32 ret;
    INT32 cpuID;
    UINT32 intSave;

    /* Initialize the global variable */
    (VOID)memset_s((VOID *)g_traceInfo, sizeof(g_traceInfo), 0, sizeof(g_traceInfo));
    (VOID)memset_s((VOID *)g_traceBuf, sizeof(g_traceBuf), 0, sizeof(g_traceBuf));
    (VOID)memset_s((VOID *)g_frameSize, sizeof(g_frameSize), 0, sizeof(g_frameSize));

    TRACE_LOCK(intSave);
    for (cpuID = 0; cpuID < LOSCFG_KERNEL_CORE_NUM; cpuID++) {
        LOS_SpinInit(&g_traceCpuSpin[cpuID]); /* initialize all buffer spin lock */
    }

    g_frameSize[LOS_TRACE_SWITCH] = sizeof(TaskTraceFrame);
    ret = OsTraceReg(LOS_TRACE_SWITCH, OsTaskTrace);
    if (ret != LOS_OK) {
        TRACE_UNLOCK(intSave);
        return ret;
    }

    g_frameSize[LOS_TRACE_INTERRUPT] = sizeof(IntTraceFrame);
    ret = OsTraceReg(LOS_TRACE_INTERRUPT, OsIntTrace);
    if (ret != LOS_OK) {
        TRACE_UNLOCK(intSave);
        return ret;
    }
    TRACE_UNLOCK(intSave);

    return LOS_OK;
}

UINT32 LOS_TraceUserReg(TraceType traceType, WriteHook inHook, UINT16 useSize)
{
    UINT32 intSave;
    UINT32 ret;

    if ((traceType <= LOS_TRACE_INTERRUPT) || (traceType >= LOS_TRACE_TYPE_NUM)) {
        return LOS_ERRNO_TRACE_TYPE_INVALID;
    }

    if (inHook == NULL) {
        return LOS_ERRNO_TRACE_FUNCTION_NULL;
    }

    if ((useSize == 0) || (((UINT32)useSize + LOS_TRACE_TAG_LENGTH) > LOS_TRACE_BUFFER_SIZE)) {
        return LOS_ERRNO_TRACE_MAX_SIZE_INVALID;
    }

    TRACE_LOCK(intSave);
    g_frameSize[traceType] = useSize;
    ret = OsTraceReg(traceType, inHook);
    TRACE_UNLOCK(intSave);

    return ret;
}

VOID LOS_Trace(TraceType traceType, UINT32 newID, UINT32 oldID)
{
    TraceHook *traceInfo = NULL;
    UINT32 intSave, intSaveCpu;
    UINT32 cpu;
    UINT16 useSize;

    intSaveCpu = LOS_IntLock();
    cpu = ArchCurrCpuid();

    if (traceType < LOS_TRACE_TYPE_NUM) {
        TRACE_CPU_LOCK(intSave, cpu);
        traceInfo = g_traceInfo[traceType];
        if ((traceInfo != NULL) && (traceInfo->inputHook != NULL)) {
            useSize = g_frameSize[traceType];
            OsTracePosAdj(useSize);
            useSize = traceInfo->inputHook(&g_traceBuf[cpu].dataBuf[g_traceBuf[cpu].tracePos], newID, oldID);
            if (useSize) {
                g_traceBuf[cpu].tracePos += useSize;

                /* Add tag by trace system, to avoid the user's misuse */
                *(UINTPTR *)&(g_traceBuf[cpu].dataBuf[g_traceBuf[cpu].tracePos]) = (UINTPTR)traceType;
                g_traceBuf[cpu].tracePos += LOS_TRACE_TAG_LENGTH;
            }
        }
        TRACE_CPU_UNLOCK(intSave, cpu);
    }

    LOS_IntRestore(intSaveCpu);
}

INT32 LOS_TraceFrameSizeGet(TraceType traceType)
{
    if ((traceType < LOS_TRACE_SWITCH) || (traceType >= LOS_TRACE_TYPE_NUM)) {
        return -1;
    }
    return g_frameSize[traceType];
}

UINT32 LOS_TraceBufGet(TraceBuffer *outputBuf, UINT32 cpuID)
{
    UINT32 intSave;

    if ((outputBuf == NULL) || (cpuID >= LOSCFG_KERNEL_CORE_NUM)) {
        return LOS_NOK;
    }

    TRACE_CPU_LOCK(intSave, cpuID);
    if (memcpy_s(outputBuf, sizeof(TraceBuffer), &g_traceBuf[cpuID], sizeof(TraceBuffer)) != EOK) {
        TRACE_CPU_UNLOCK(intSave, cpuID);
        return LOS_NOK;
    }
    TRACE_CPU_UNLOCK(intSave, cpuID);

    return LOS_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
