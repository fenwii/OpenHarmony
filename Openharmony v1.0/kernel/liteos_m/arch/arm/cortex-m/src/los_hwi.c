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

#include "los_hwi.h"
#include "los_sr.h"

#if (LOSCFG_KERNEL_TICKLESS == YES)
#include "los_tickless_pri.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*lint -save -e40 -e522 -e533*/
__weak VOID SysTickHandler(VOID)
{
    return;
}

UINT32 g_vuwIntCount = 0;
/*lint -restore*/
#ifdef __ICCARM__
#pragma location = ".data.vector"
#elif defined(__CC_ARM) || defined(__GNUC__)
LITE_OS_SEC_VEC
#endif

HWI_PROC_FUNC g_hwiForm[OS_VECTOR_CNT] = {
    (HWI_PROC_FUNC)0,                    // [0] Top of Stack
    (HWI_PROC_FUNC)Reset_Handler,        // [1] reset
    (HWI_PROC_FUNC)OsHwiDefaultHandler,  // [2] NMI Handler
    (HWI_PROC_FUNC)OsHwiDefaultHandler,  // [3] Hard Fault Handler
    (HWI_PROC_FUNC)OsHwiDefaultHandler,  // [4] MPU Fault Handler
    (HWI_PROC_FUNC)OsHwiDefaultHandler,  // [5] Bus Fault Handler
    (HWI_PROC_FUNC)OsHwiDefaultHandler,  // [6] Usage Fault Handler
    (HWI_PROC_FUNC)0,                    // [7] Reserved
    (HWI_PROC_FUNC)0,                    // [8] Reserved
    (HWI_PROC_FUNC)0,                    // [9] Reserved
    (HWI_PROC_FUNC)0,                    // [10] Reserved
    (HWI_PROC_FUNC)OsHwiDefaultHandler,  // [11] SVCall Handler
    (HWI_PROC_FUNC)OsHwiDefaultHandler,  // [12] Debug Monitor Handler
    (HWI_PROC_FUNC)0,                    // [13] Reserved
    (HWI_PROC_FUNC)osPendSV,             // [14] PendSV Handler
    (HWI_PROC_FUNC)SysTickHandler,      // [15] SysTick Handler
};
#if (OS_HWI_WITH_ARG == YES)
HWI_SLAVE_FUNC g_hwiSlaveForm[OS_VECTOR_CNT] = {{ (HWI_PROC_FUNC)0, (HWI_ARG_T)0 }};
#else
HWI_PROC_FUNC g_hwiSlaveForm[OS_VECTOR_CNT] = {0};
#endif

/* ****************************************************************************
 Function    : OsIntNumGet
 Description : Get a interrupt number
 Input       : None
 Output      : None
 Return      : Interrupt Indexes number
 **************************************************************************** */
LITE_OS_SEC_TEXT_MINOR UINT32 OsIntNumGet(VOID)
{
    return __get_IPSR();
}

/* ****************************************************************************
 Function    : OsHwiDefaultHandler
 Description : default handler of the hardware interrupt
 Input       : None
 Output      : None
 Return      : None
 **************************************************************************** */
/*lint -e529*/
LITE_OS_SEC_TEXT_MINOR VOID OsHwiDefaultHandler(VOID)
{
    UINT32 irqNum = OsIntNumGet();
    PRINT_ERR("%s irqnum:%d\n", __FUNCTION__, irqNum);
    while (1) {}
}

/* ****************************************************************************
 Function    : OsInterrupt
 Description : Hardware interrupt entry function
 Input       : None
 Output      : None
 Return      : None
 **************************************************************************** */
LITE_OS_SEC_TEXT VOID OsInterrupt(VOID)
{
    UINT32 hwiIndex;
    UINT32 intSave;

#if (LOSCFG_KERNEL_RUNSTOP == YES)
    SCB->SCR &= (UINT32) ~((UINT32)SCB_SCR_SLEEPDEEP_Msk);
#endif

    intSave = LOS_IntLock();

    g_vuwIntCount++;

    LOS_IntRestore(intSave);

    hwiIndex = OsIntNumGet();
#if (LOSCFG_KERNEL_TICKLESS == YES)
    osUpdateKernelTickCount(hwiIndex);
#endif

#if (OS_HWI_WITH_ARG == YES)
    if (g_hwiSlaveForm[hwiIndex].pfnHandler != 0) {
        g_hwiSlaveForm[hwiIndex].pfnHandler((VOID *)g_hwiSlaveForm[hwiIndex].pParm);
    }
#else
    if (g_hwiSlaveForm[hwiIndex] != 0) {
        g_hwiSlaveForm[hwiIndex]();
    }
#endif
    intSave = LOS_IntLock();
    g_vuwIntCount--;
    LOS_IntRestore(intSave);
}

/* ****************************************************************************
 Function    : OsHwiInit
 Description : initialization of the hardware interrupt
 Input       : None
 Output      : None
 Return      : None
 **************************************************************************** */
LITE_OS_SEC_TEXT_INIT VOID OsHwiInit()
{
    UINT32 index;

    for (index = OS_SYS_VECTOR_CNT; index < OS_VECTOR_CNT; index++) {
        g_hwiForm[index] = (HWI_PROC_FUNC)OsHwiDefaultHandler;
    }

    /* Interrupt vector table location */
    SCB->VTOR = (UINT32)(UINTPTR)g_hwiForm;
#if (__CORTEX_M >= 0x03U) /* only for Cortex-M3 and above */
    NVIC_SetPriorityGrouping(OS_NVIC_AIRCR_PRIGROUP);
#endif

    return;
}
/* ****************************************************************************
 Function    : LOS_HwiCreate
 Description : create hardware interrupt
 Input       : hwiNum   --- hwi num to create
               hwiPrio  --- priority of the hwi
               mode     --- unused
               handler --- hwi handler
               arg      --- param of the hwi handler
 Output      : None
 Return      : LOS_OK on success or error code on failure
 **************************************************************************** */
LITE_OS_SEC_TEXT_INIT UINT32 LOS_HwiCreate(HWI_HANDLE_T hwiNum,
                                           HWI_PRIOR_T hwiPrio,
                                           HWI_MODE_T mode,
                                           HWI_PROC_FUNC handler,
                                           HWI_ARG_T arg)
{
    UINTPTR intSave;

    if (handler == NULL) {
        return OS_ERRNO_HWI_PROC_FUNC_NULL;
    }

    if (hwiNum >= OS_HWI_MAX_NUM) {
        return OS_ERRNO_HWI_NUM_INVALID;
    }

    if (g_hwiForm[hwiNum + OS_SYS_VECTOR_CNT] != (HWI_PROC_FUNC)OsHwiDefaultHandler) {
        return OS_ERRNO_HWI_ALREADY_CREATED;
    }

    if (hwiPrio > OS_HWI_PRIO_LOWEST) {
        return OS_ERRNO_HWI_PRIO_INVALID;
    }

    intSave = LOS_IntLock();
#if (OS_HWI_WITH_ARG == YES)
    OsSetVector(hwiNum, handler, arg);
#else
    OsSetVector(hwiNum, handler);
#endif
    NVIC_EnableIRQ((IRQn_Type)hwiNum);
    NVIC_SetPriority((IRQn_Type)hwiNum, hwiPrio);

    LOS_IntRestore(intSave);

    return LOS_OK;
}

/* ****************************************************************************
 Function    : LOS_HwiDelete
 Description : Delete hardware interrupt
 Input       : hwiNum   --- hwi num to delete
 Output      : None
 Return      : LOS_OK on success or error code on failure
 **************************************************************************** */
LITE_OS_SEC_TEXT_INIT UINT32 LOS_HwiDelete(HWI_HANDLE_T hwiNum)
{
    UINT32 intSave;

    if (hwiNum >= OS_HWI_MAX_NUM) {
        return OS_ERRNO_HWI_NUM_INVALID;
    }

    NVIC_DisableIRQ((IRQn_Type)hwiNum);

    intSave = LOS_IntLock();

    g_hwiForm[hwiNum + OS_SYS_VECTOR_CNT] = (HWI_PROC_FUNC)OsHwiDefaultHandler;

    LOS_IntRestore(intSave);

    return LOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


