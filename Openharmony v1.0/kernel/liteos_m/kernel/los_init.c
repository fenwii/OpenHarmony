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

#include "los_sys.h"
#include "los_tick.h"
#include "los_task_pri.h"
#include "los_tick_pri.h"
#include "los_config.h"
#if (LOSCFG_KERNEL_RUNSTOP == YES)
#include "los_sr.h"
#endif

#if (LOSCFG_PLATFORM_EXC == YES)
#include "los_exc_pri.h"
#endif

#if (LOSCFG_KERNEL_TRACE == YES)
#include "los_trace.h"
#endif

#if (LOSCFG_KERNEL_CPPSUPPORT == YES)
#include "los_cppsupport.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

UINT8 *m_aucSysMem0;

#if (LOSCFG_PLATFORM_EXC == YES)
UINT8 g_aucTaskArray[MAX_EXC_MEM_SIZE];
#endif
#define FPU_ENABLE ((3UL << 20) | (3UL << 22))

VOID OsEnableFPU(VOID)
{
    *(volatile UINT32 *)0xE000ED88 |= FPU_ENABLE; /* CPACR is located at address 0xE000ED88. */
}

/*****************************************************************************
 Function    : LOS_Reboot
 Description : system exception, die in here, wait for watchdog.
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT VOID LOS_Reboot(VOID)
{
    (VOID)LOS_IntLock();
    while (1) {
    }
}
/*****************************************************************************
 Function    : OsRegister
 Description : Configuring the maximum number of tasks
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT static VOID OsRegister(VOID)
{
    g_taskMaxNum = LOSCFG_BASE_CORE_TSK_LIMIT + 1; /* Reserved 1 for IDLE */

    return;
}

/*****************************************************************************
 Function    : LOS_Start
 Description : Task start function.
 Input       : None
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_Start(VOID)
{
    UINT32 ret;
#if (LOSCFG_BASE_CORE_TICK_HW_TIME == NO)
    ret = OsTickStart();

    if (ret != LOS_OK) {
        PRINT_ERR("OsTickStart error\n");
        return ret;
    }
#else
    ret = os_timer_init();
    if (ret != LOS_OK) {
        PRINT_ERR("os_timer_init error\n");
        return ret;
    }
#endif
    LOS_StartToRun();

    return ret;
}

/*****************************************************************************
 Function    : LOS_KernelInit
 Description : System kernel initialization function, configure all system modules
 Input       : None
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT UINT32 LOS_KernelInit(VOID)
{
    UINT32 ret;

    OsRegister();

    m_aucSysMem0 = (UINT8 *)OS_SYS_MEM_ADDR;
    g_sysMemAddrEnd = ((UINT32)OS_SYS_MEM_ADDR + OS_SYS_MEM_SIZE);
    ret = OsMemSystemInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsMemSystemInit error %d\n", ret);
        return ret;
    }

#if (LOSCFG_PLATFORM_HWI == YES)
    OsHwiInit();
#endif

#if (LOSCFG_PLATFORM_EXC == YES)
    OsExcInit(MAX_EXC_MEM_SIZE);
#endif

    ret = OsTaskInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsTaskInit error\n");
        return ret;
    }

#if (LOSCFG_BASE_CORE_TSK_MONITOR == YES)
        OsTaskMonInit();
#endif

#if (LOSCFG_BASE_CORE_CPUP == YES)
    ret = OsCpupInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsCpupInit error\n");
        return ret;
    }
#endif

#if (LOSCFG_BASE_IPC_SEM == YES)
    ret = OsSemInit();
    if (ret != LOS_OK) {
        return ret;
    }
#endif

#if (LOSCFG_BASE_IPC_MUX == YES)
    ret = OsMuxInit();
    if (ret != LOS_OK) {
        return ret;
    }
#endif

#if (LOSCFG_BASE_IPC_QUEUE == YES)
    ret = OsQueueInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsQueueInit error\n");
        return ret;
    }
#endif

#if (LOSCFG_BASE_CORE_SWTMR == YES)
    ret = OsSwtmrInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsSwtmrInit error\n");
        return ret;
    }
#endif

#if (LOSCFG_BASE_CORE_TIMESLICE == YES)
    OsTimesliceInit();
#endif

    ret = OsIdleTaskCreate();
    if (ret != LOS_OK) {
        return ret;
    }

#if (LOSCFG_KERNEL_TRACE == YES)
    ret = LOS_TraceInit();
    if (ret != LOS_OK) {
        PRINT_ERR("LOS_TraceInit error\n");
        return ret;
    }
#endif

#if (LOSCFG_KERNEL_CPPSUPPORT == YES)
     extern char __init_array_start,__init_array_end;
     LOS_CppSystemInit((UINTPTR)&__init_array_start,(UINTPTR)&__init_array_end);
#endif
#ifdef LOSCFG_TEST
    ret = los_TestInit();
    if (ret != LOS_OK) {
        PRINT_ERR("los_TestInit error\n");
        return ret;
    }
#endif

    return LOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
