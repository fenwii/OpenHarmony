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

#include "los_mp.h"
#include "los_task_pri.h"
#include "los_percpu_pri.h"
#include "los_sched_pri.h"
#include "los_swtmr.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if (LOSCFG_KERNEL_SMP == YES)

VOID LOS_MpSchedule(UINT32 target)
{
    UINT32 cpuid = ArchCurrCpuid();
    target &= ~(1U << cpuid);
    HalIrqSendIpi(target, LOS_MP_IPI_SCHEDULE);
}

VOID OsMpWakeHandler(VOID)
{
    /* generic wakeup ipi, do nothing */
}

VOID OsMpScheduleHandler(VOID)
{
    /*
     * set schedule flag to differ from wake function,
     * so that the scheduler can be triggered at the end of irq.
     */
    OsPercpuGet()->schedFlag = INT_PEND_RESCH;
}

VOID OsMpHaltHandler(VOID)
{
    (VOID)LOS_IntLock();
    OsPercpuGet()->excFlag = CPU_HALT;

    while (1) {}
}

VOID OsMpCollectTasks(VOID)
{
    LosTaskCB *taskCB = NULL;
    UINT32 taskID = 0;
    UINT32 ret;

    /* recursive checking all the available task */
    for (; taskID <= g_taskMaxNum; taskID++) {
        taskCB = &g_taskCBArray[taskID];

        if (OsTaskIsUnused(taskCB) || OsTaskIsRunning(taskCB)) {
            continue;
        }

        /*
         * though task status is not atomic, this check may success but not accomplish
         * the deletion; this deletion will be handled until the next run.
         */
        if (taskCB->signal & SIGNAL_KILL) {
            ret = LOS_TaskDelete(taskID);
            if (ret != LOS_OK) {
                PRINT_WARN("GC collect task failed err:0x%x\n", ret);
            }
        }
    }
}

UINT32 OsMpInit(VOID)
{
    UINT16 swtmrId;

    (VOID)LOS_SwtmrCreate(OS_MP_GC_PERIOD, LOS_SWTMR_MODE_PERIOD,
                          (SWTMR_PROC_FUNC)OsMpCollectTasks, &swtmrId, 0);
    (VOID)LOS_SwtmrStart(swtmrId);

    return LOS_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
