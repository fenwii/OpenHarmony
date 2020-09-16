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

#include "los_config.h"
#include "los_task_pri.h"
#include "los_swtmr_pri.h"
#include "los_printf.h"
#include "los_atomic.h"
#include "gic_common.h"
#include "uart.h"
#include "los_process_pri.h"
#include "los_arch_mmu.h"

#if (LOSCFG_KERNEL_SMP == YES)
STATIC Atomic g_ncpu = 1;
#endif

LITE_OS_SEC_TEXT_INIT VOID OsSystemInfo(VOID)
{
#ifdef LOSCFG_DEBUG_VERSION
    const CHAR *buildType = "debug";
#else
    const CHAR *buildType = "release";
#endif /* LOSCFG_DEBUG_VERSION */

    PRINT_RELEASE("\n******************Welcome******************\n\n"
            "Processor   : %s"
#if (LOSCFG_KERNEL_SMP == YES)
            " * %d\n"
            "Run Mode    : SMP\n"
#else
            "\n"
            "Run Mode    : UP\n"
#endif
            "GIC Rev     : %s\n"
            "build time  : %s %s\n"
            "Kernel      : %s %d.%d.%d.%d/%s\n"
            "\n*******************************************\n",
            LOS_CpuInfo(),
#if (LOSCFG_KERNEL_SMP == YES)
            LOSCFG_KERNEL_SMP_CORE_NUM,
#endif
            HalIrqVersion(), __DATE__, __TIME__,\
            KERNEL_NAME, KERNEL_MAJOR, KERNEL_MINOR, KERNEL_PATCH, KERNEL_ITRE, buildType);
}

LITE_OS_SEC_TEXT_INIT VOID secondary_cpu_start(VOID)
{
#if (LOSCFG_KERNEL_SMP == YES)
    UINT32 cpuid = ArchCurrCpuid();

    OsArchMmuInitPerCPU();

    OsCurrTaskSet(OsGetMainTask());

    /* increase cpu counter */
    LOS_AtomicInc(&g_ncpu);

    /* store each core's hwid */
    CPU_MAP_SET(cpuid, OsHwIDGet());
    HalIrqInitPercpu();

    OsCurrProcessSet(OS_PCB_FROM_PID(OsGetKernelInitProcessID()));
    OsSwtmrInit();
    OsIdleTaskCreate();
    OsStart();
    while (1) {
        __asm volatile("wfi");
    }
#endif
}

#if (LOSCFG_KERNEL_SMP == YES)
#ifdef LOSCFG_TEE_ENABLE
#define TSP_CPU_ON  0xb2000011UL
STATIC INT32 raw_smc_send(UINT32 cmd)
{
    register UINT32 smc_id asm("r0") = cmd;
    do {
        asm volatile (
                "mov r0, %[a0]\n"
                "smc #0\n"
                : [a0] "+r"(smc_id)
                );
    } while (0);

    return (INT32)smc_id;
}

STATIC VOID trigger_secondary_cpu(VOID)
{
    (VOID)raw_smc_send(TSP_CPU_ON);
}

LITE_OS_SEC_TEXT_INIT VOID release_secondary_cores(VOID)
{
    trigger_secondary_cpu();
    /* wait until all APs are ready */
    while (LOS_AtomicRead(&g_ncpu) < LOSCFG_KERNEL_CORE_NUM) {
        asm volatile("wfe");
    }
}
#else
#define CLEAR_RESET_REG_STATUS(regval) (regval) &= ~(1U << 2)
LITE_OS_SEC_TEXT_INIT VOID release_secondary_cores(VOID)
{
    UINT32 regval;

    /* clear the slave cpu reset */
    READ_UINT32(regval, PERI_CRG30_BASE);
    CLEAR_RESET_REG_STATUS(regval);
    WRITE_UINT32(regval, PERI_CRG30_BASE);

    /* wait until all APs are ready */
    while (LOS_AtomicRead(&g_ncpu) < LOSCFG_KERNEL_CORE_NUM) {
        asm volatile("wfe");
    }
}
#endif /* LOSCFG_TEE_ENABLE */
#endif /* LOSCFG_KERNEL_SMP */

LITE_OS_SEC_TEXT_INIT INT32 main(VOID)
{
    UINT32 uwRet = LOS_OK;

    OsSetMainTask();
    OsCurrTaskSet(OsGetMainTask());

    /* set smp system counter freq */
#if (LOSCFG_KERNEL_SMP == YES)
#ifndef LOSCFG_TEE_ENABLE
    HalClockFreqWrite(OS_SYS_CLOCK);
#endif
#endif

    /* system and chip info */
    OsSystemInfo();

    PRINT_RELEASE("\nmain core booting up...\n");

    uwRet = OsMain();
    if (uwRet != LOS_OK) {
        return LOS_NOK;
    }

#if (LOSCFG_KERNEL_SMP == YES)
    PRINT_RELEASE("releasing %u secondary cores\n", LOSCFG_KERNEL_SMP_CORE_NUM - 1);
    release_secondary_cores();
#endif

    CPU_MAP_SET(0, OsHwIDGet());

    OsStart();

    while (1) {
        __asm volatile("wfi");
    }
}
