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

#include "los_exc_pri.h"
#include "los_memcheck_pri.h"
#ifdef LOSCFG_LIB_LIBC
#include "string.h"
#endif
#include "securec.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define EXC_INT_STATUS_LEN              OS_NVIC_INT_ENABLE_SIZE + OS_NVIC_INT_PEND_SIZE + OS_NVIC_INT_ACT_SIZE + \
    OS_NVIC_INT_PRI_SIZE + OS_NVIC_EXCPRI_SIZE + OS_NVIC_SHCSR_SIZE + OS_NVIC_INT_CTRL_SIZE
#define TASK_ARRAY_INIT_VALUE           0xff
#define FAULT_STATUS_REG_BIT            32
#define OS_NVIC_INT_CTRL_SIZE           4
#define OS_NVIC_SHCSR_SIZE              4
#define USGFAULT                        (1 << 18)
#define BUSFAULT                        (1 << 17)
#define MEMFAULT                        (1 << 16)
#define DIV0FAULT                       (1 << 4)
#define CORE_TYPE_CORTEX_M4             2
#define HARDFAULT_IRQN                  (-13)
static VOID *g_excContent;
UINT32 g_curNestCount = 0;
ExcInfo g_excInfo;

__attribute__((noinline)) VOID LOS_Panic(const CHAR *fmt, ...)
{
    va_list ap;
    va_start(ap,fmt);
    PRINT_ERR(fmt, ap);
    va_end(ap);
    asm volatile ("swi 0");
}

UINT8 g_uwExcTbl[FAULT_STATUS_REG_BIT] = {
    0, 0, 0, 0, 0, 0, OS_EXC_UF_DIVBYZERO, OS_EXC_UF_UNALIGNED,
    0, 0, 0, 0, OS_EXC_UF_NOCP, OS_EXC_UF_INVPC, OS_EXC_UF_INVSTATE, OS_EXC_UF_UNDEFINSTR,
    0, 0, 0, OS_EXC_BF_STKERR, OS_EXC_BF_UNSTKERR, OS_EXC_BF_IMPRECISERR, OS_EXC_BF_PRECISERR, OS_EXC_BF_IBUSERR,
    0, 0, 0, OS_EXC_MF_MSTKERR, OS_EXC_MF_MUNSTKERR, 0, OS_EXC_MF_DACCVIOL, OS_EXC_MF_IACCVIOL
};
UINT32 g_excArraySize = 0;
ExcInfoArray g_excArray[OS_EXC_TYPE_MAX - 1];

UINT32 g_LR_regs = 0;
UINT32 g_PC_regs = 0;

LITE_OS_SEC_TEXT_INIT VOID OsExcInfoDisplay(ExcInfo *exc)
{
    PRINT_INFO("Phase      = 0x%x\n", exc->phase);
    PRINT_INFO("Type       = 0x%x\n", exc->type);
    PRINT_INFO("FaultAddr  = 0x%x\n", exc->faultAddr);
    PRINT_INFO("ThrdPid    = 0x%x\n", exc->thrdPid);
    PRINT_INFO("R0         = 0x%x\n", exc->context->uwR0);
    PRINT_INFO("R1         = 0x%x\n", exc->context->uwR1);
    PRINT_INFO("R2         = 0x%x\n", exc->context->uwR2);
    PRINT_INFO("R3         = 0x%x\n", exc->context->uwR3);
    PRINT_INFO("R4         = 0x%x\n", exc->context->uwR4);
    PRINT_INFO("R5         = 0x%x\n", exc->context->uwR5);
    PRINT_INFO("R6         = 0x%x\n", exc->context->uwR6);
    PRINT_INFO("R7         = 0x%x\n", exc->context->uwR7);
    PRINT_INFO("R8         = 0x%x\n", exc->context->uwR8);
    PRINT_INFO("R9         = 0x%x\n", exc->context->uwR9);
    PRINT_INFO("R10        = 0x%x\n", exc->context->uwR10);
    PRINT_INFO("R11        = 0x%x\n", exc->context->uwR11);
    PRINT_INFO("R12        = 0x%x\n", exc->context->uwR12);
    PRINT_INFO("PriMask    = 0x%x\n", exc->context->uwPriMask);
    PRINT_INFO("SP         = 0x%x\n", exc->context->uwSP);
    PRINT_INFO("LR         = 0x%x\n", exc->context->uwLR);
    PRINT_INFO("PC         = 0x%x\n", exc->context->uwPC);
    PRINT_INFO("xPSR       = 0x%x\n", exc->context->uwxPSR);

    g_LR_regs = exc->context->uwLR;
    g_PC_regs = exc->context->uwPC;
}

/* ****************************************************************************
 Function : OsExcHandleEntry
 Description : EXC模块的处理分发函数
 Input  : excType
        : faultAddr
        : pid
        : excBufAddr --- EXC寄存器信息的首地址
 Output : None
 Return : None
 **************************************************************************** */
LITE_OS_SEC_TEXT_INIT VOID OsExcHandleEntry(UINT32 excType, UINT32 faultAddr, UINT32 pid,
                                            EXC_CONTEXT_S *excBufAddr)
{
    UINT16 tmpFlag = (excType >> 16) & OS_NULL_SHORT;  // 为2在中断中，为1 faultAddr有效
    g_curNestCount++;
    g_vuwIntCount++;
    g_excInfo.nestCnt = g_curNestCount;

    g_excInfo.type = excType & OS_NULL_SHORT;
    g_excContent = (UINT32 *)g_aucTaskArray;

    if (tmpFlag & OS_EXC_FLAG_FAULTADDR_VALID) {
        g_excInfo.faultAddr = faultAddr;
    } else {
        g_excInfo.faultAddr = OS_EXC_IMPRECISE_ACCESS_ADDR;
    }

    if (g_losTask.runTask != NULL) {
        if (tmpFlag & OS_EXC_FLAG_IN_HWI) {
            g_excInfo.phase = OS_EXC_IN_HWI;
            g_excInfo.thrdPid = pid;
        } else {
            g_excInfo.phase = OS_EXC_IN_TASK;
            g_excInfo.thrdPid = g_losTask.runTask->taskID;
        }
    } else {
        g_excInfo.phase = OS_EXC_IN_INIT;
        g_excInfo.thrdPid = OS_NULL_INT;
    }

    if (excType & OS_EXC_FLAG_NO_FLOAT) {
        g_excInfo.context = (EXC_CONTEXT_S *)((CHAR *)excBufAddr - LOS_OFF_SET_OF(EXC_CONTEXT_S, uwR4));
    } else {
        g_excInfo.context = excBufAddr;
    }

    OsExcSave2DDR();

    OsExcInfoDisplay(&g_excInfo);

    LOS_Reboot();
}
static VOID OsExcSaveIntStatus()
{
    UINT32 ret;
    UINT32 failCnt = 0;
    *((UINT32 *)g_excContent) = OS_EXC_TYPE_NVIC;
    g_excContent = (UINT8 *)g_excContent + sizeof(UINT32);

    // = OS_NVIC_INT_ENABLE_SIZE + OS_NVIC_INT_PEND_SIZE + OS_NVIC_INT_ACT_SIZE + OS_NVIC_INT_PRI_SIZE + 12 + 4 + 4
    *((UINT32 *)g_excContent) = EXC_INT_STATUS_LEN;
    g_excContent = (UINT8 *)g_excContent + sizeof(UINT32);
    /* 保存中断ENABLE寄存器组 */
    ret = memcpy_s(g_excContent, MAX_EXC_MEM_SIZE, (const VOID *)OS_NVIC_SETENA_BASE, OS_NVIC_INT_ENABLE_SIZE);
    g_excContent = (UINT8 *)g_excContent + OS_NVIC_INT_ENABLE_SIZE;
    failCnt += (ret == EOK) ? 0 : 1;

    /* 保存中断PEND寄存器组 */
    ret = memcpy_s(g_excContent, MAX_EXC_MEM_SIZE, (const VOID *)OS_NVIC_SETPEND_BASE, OS_NVIC_INT_PEND_SIZE);
    g_excContent = (UINT8 *)g_excContent + OS_NVIC_INT_PEND_SIZE;
    failCnt += (ret == EOK) ? 0 : 1;

    /* 保存中断ACTIVE寄存器组 */
    ret = memcpy_s(g_excContent, MAX_EXC_MEM_SIZE, (const VOID *)OS_NVIC_INT_ACT_BASE, OS_NVIC_INT_ACT_SIZE);
    g_excContent = (UINT8 *)g_excContent + OS_NVIC_INT_ACT_SIZE;
    failCnt += (ret == EOK) ? 0 : 1;

    /* 保存中断优先级寄存器组 */
    ret = memcpy_s(g_excContent, MAX_EXC_MEM_SIZE, (const VOID *)OS_NVIC_PRI_BASE, OS_NVIC_INT_PRI_SIZE);
    g_excContent = (UINT8 *)g_excContent + OS_NVIC_INT_PRI_SIZE;
    failCnt += (ret == EOK) ? 0 : 1;

    /* 	系统异常优先级寄存器组 */
    ret = memcpy_s(g_excContent, MAX_EXC_MEM_SIZE, (const VOID *)OS_NVIC_EXCPRI_BASE, OS_NVIC_EXCPRI_SIZE);
    g_excContent = (UINT8 *)g_excContent + OS_NVIC_EXCPRI_SIZE;
    failCnt += (ret == EOK) ? 0 : 1;

    /* 保存系统Handler控制及状态寄存器SHCSR */
    ret = memcpy_s(g_excContent, MAX_EXC_MEM_SIZE, (const VOID *)OS_NVIC_SHCSR, OS_NVIC_SHCSR_SIZE);
    g_excContent = (UINT8 *)g_excContent + sizeof(UINT32);
    failCnt += (ret == EOK) ? 0 : 1;

    /* 保存中断控制及状态寄存器ICSR */
    ret = memcpy_s(g_excContent, MAX_EXC_MEM_SIZE, (const VOID *)OS_NVIC_INT_CTRL, OS_NVIC_INT_CTRL_SIZE);
    g_excContent = (UINT8 *)g_excContent + sizeof(UINT32);
    failCnt += (ret == EOK) ? 0 : 1;

    if (failCnt != 0) {
        PRINT_ERR("OsExcSaveIntStatus copy register info failed, cnt:%d\n", failCnt);
    }

    return;
}

VOID OsExcRegister(ExcInfoType type, EXC_INFO_SAVE_CALLBACK func, VOID *arg)
{
    ExcInfoArray *excInfo = NULL;
    if ((type == 0) || (type >= OS_EXC_TYPE_MAX) || (func == NULL)) {
        PRINT_ERR("OsExcRegister ERROR!\n");
        return;
    }
    excInfo = &(g_excArray[type - 1]);
    excInfo->uwType = type;
    excInfo->pFnExcInfoCb = func;
    excInfo->pArg = arg;
    excInfo->uwValid = TRUE;
}

static VOID OsExcSaveSysInfo(ExcInfoType type, EXC_INFO_SAVE_CALLBACK func, UINT32 loop, UINT32 length, UINT32 index)
{
    UINT32 ret;
    UINT32 buffer[OS_EXC_MAX_BUF_LEN];

    *((UINT32 *)g_excContent) = type;
    g_excContent = (UINT8 *)g_excContent + sizeof(UINT32);
    *((UINT32 *)g_excContent) = length * (loop - index);
    g_excContent = (UINT8 *)g_excContent + sizeof(UINT32);

    for (; index < loop; index++) {
        (VOID)memset_s(buffer, sizeof(UINT32) * OS_EXC_MAX_BUF_LEN, 0, sizeof(UINT32) * OS_EXC_MAX_BUF_LEN);
        ret = func(index, (VOID *)buffer);
        if (ret == LOS_OK) {
            if (memcpy_s(g_excContent, MAX_EXC_MEM_SIZE, (VOID *)buffer, length) != EOK) {
                PRINT_ERR("OsExcSaveSysInfo copy buffer failed\n");
                return;
            }
            g_excContent = (UINT8 *)g_excContent + length;
        } else {
            g_excContent = (UINT8 *)g_excContent + length;
        }
    }
}

static VOID OsExcSaveInfo(ExcInfoType type, EXC_INFO_SAVE_CALLBACK func, VOID *arg)
{
    UINT32 length;
    UINT32 index;
    UINT32 loop;
    UINT32 taskSwitchCount = 0;
    TaskSwitchInfo *taskSwitchInfo = NULL;

    if (arg == NULL) {
        return;
    }

    switch (type) {
        case OS_EXC_TYPE_TSK: /* save task info */
            length = sizeof(TSK_INFO_S);
            loop = *(UINT32 *)arg;
            index = 0;
            break;

        case OS_EXC_TYPE_QUE: /* save queue info */
            length = sizeof(QUEUE_INFO_S);
            loop = *(UINT32 *)arg + 1;
            index = 1;
            break;

        case OS_EXC_TYPE_NVIC:
            (VOID)func(0, 0);
            goto END;

        case OS_EXC_TYPE_TSK_SWITCH: /* save task switch info */
            // not necessary, just for macro int library
            taskSwitchInfo = arg;
            taskSwitchCount = taskSwitchInfo->cntInfo.maxCnt;
            length = sizeof(UINT32) + sizeof(CHAR) * LOS_TASK_NAMELEN;
            if (taskSwitchInfo->cntInfo.isFull) {
                index = taskSwitchInfo->idx;
                loop = index + taskSwitchCount;
            } else {
                index = 0;
                loop = taskSwitchInfo->idx;
            }
            break;

        case OS_EXC_TYPE_MEM: /* save mem info */
            length = sizeof(MEM_INFO_S);
            loop = *(UINT32 *)arg;
            index = 0;
            break;

        default:
            goto END;
    }
    OsExcSaveSysInfo(type, (EXC_INFO_SAVE_CALLBACK)func, loop, length, index);
END:
    return;
}

static VOID OsExcSave2DDR(VOID)
{
    UINT32 index = 0;
    UINT32 ret;
    UINT32 failCnt = 0;

    ret = memset_s(g_aucTaskArray, MAX_EXC_MEM_SIZE, TASK_ARRAY_INIT_VALUE, g_excArraySize);
    if (ret != EOK) {
        PRINT_ERR("memset failed\n");
        return;
    }

    /* define core type */
    *((UINT32 *)g_excContent) = CORE_TYPE_CORTEX_M4;  // 1 is cortex-M3, 2 is cortex-M4
    g_excContent = (UINT8 *)g_excContent + sizeof(UINT32);

    /* save exception info */
    *((UINT32 *)g_excContent) = OS_EXC_TYPE_CONTEXT;
    g_excContent = (UINT8 *)g_excContent + sizeof(UINT32);
    *((UINT32 *)g_excContent) = sizeof(ExcInfo) - sizeof(UINT32) + sizeof(EXC_CONTEXT_S);

    g_excContent = (UINT8 *)g_excContent + sizeof(UINT32);
    ret = memcpy_s((VOID *)g_excContent, MAX_EXC_MEM_SIZE, (VOID *)&g_excInfo, sizeof(ExcInfo) - sizeof(UINT32));
    g_excContent = (UINT8 *)g_excContent + sizeof(ExcInfo) - sizeof(UINT32);
    failCnt += (ret == EOK) ? 0 : 1;

    ret = memcpy_s((VOID *)g_excContent, MAX_EXC_MEM_SIZE, g_excInfo.context, sizeof(EXC_CONTEXT_S));
    g_excContent = (UINT8 *)g_excContent + sizeof(EXC_CONTEXT_S);
    failCnt += (ret == EOK) ? 0 : 1;

    if (failCnt != 0) {
        PRINT_ERR("OsExcSave2DDR copy exc info failed, cnt:%d\n", failCnt);
    }

    for (index = 0; index < (OS_EXC_TYPE_MAX - 1); index++) {
        if (g_excArray[index].uwValid == FALSE) {
            continue;
        }
        OsExcSaveInfo(g_excArray[index].uwType, g_excArray[index].pFnExcInfoCb, g_excArray[index].pArg);
    }
    *((UINT32 *)g_excContent) = OS_EXC_TYPE_MAX;
    g_excContent = (UINT8 *)g_excContent + sizeof(UINT32);
    return;
}

LITE_OS_SEC_TEXT_INIT VOID OsExcInit(UINT32 arraySize)
{
    g_hwiForm[HARDFAULT_IRQN + OS_SYS_VECTOR_CNT] = OsExcHardFault;
    g_hwiForm[NonMaskableInt_IRQn + OS_SYS_VECTOR_CNT] = OsExcNMI;
    g_hwiForm[MemoryManagement_IRQn + OS_SYS_VECTOR_CNT] = OsExcMemFault;
    g_hwiForm[BusFault_IRQn + OS_SYS_VECTOR_CNT] = OsExcBusFault;
    g_hwiForm[UsageFault_IRQn + OS_SYS_VECTOR_CNT] = OsExcUsageFault;
    g_hwiForm[SVCall_IRQn + OS_SYS_VECTOR_CNT] = OsExcSvcCall;
    /* Enable USGFAULT, BUSFAULT, MEMFAULT */
    *(volatile UINT32 *)OS_NVIC_SHCSR |= (USGFAULT | BUSFAULT | MEMFAULT);
    /* Enable DIV 0 and unaligned exception */  // 因为文件系统存在非对齐操作，故此异常暂不接管

    *(volatile UINT32 *)OS_NVIC_CCR |= DIV0FAULT;
    g_excArraySize = arraySize;

    OsExcRegister(OS_EXC_TYPE_NVIC, (EXC_INFO_SAVE_CALLBACK)OsExcSaveIntStatus, NULL);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
