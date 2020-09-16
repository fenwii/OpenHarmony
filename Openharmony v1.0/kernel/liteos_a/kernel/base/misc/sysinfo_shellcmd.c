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
#include "los_swtmr.h"
#include "los_sem_pri.h"
#include "los_queue_pri.h"
#include "los_swtmr_pri.h"

#ifdef LOSCFG_SHELL
#include "shcmd.h"
#include "shell.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define SYSINFO_ENABLED(x) (((x) == YES) ? "YES" : "NO")
UINT32 OsShellCmdTaskCntGet(VOID)
{
    UINT32 loop;
    UINT32 taskCnt = 0;
    UINT32 intSave;
    LosTaskCB *taskCB = NULL;

    intSave = LOS_IntLock();
    for (loop = 0; loop < g_taskMaxNum; loop++) {
        taskCB = (LosTaskCB *)g_taskCBArray + loop;
        if (OsTaskIsUnused(taskCB)) {
            continue;
        }
        taskCnt++;
    }
    LOS_IntRestore(intSave);
    return taskCnt;
}

UINT32 OsShellCmdSemCntGet(VOID)
{
    UINT32 loop;
    UINT32 semCnt = 0;
    UINT32 intSave;
    LosSemCB *semNode = NULL;

    intSave = LOS_IntLock();
    for (loop = 0; loop < LOSCFG_BASE_IPC_SEM_LIMIT; loop++) {
        semNode = GET_SEM(loop);
        if (semNode->semStat == OS_SEM_USED) {
            semCnt++;
        }
    }
    LOS_IntRestore(intSave);
    return semCnt;
}

UINT32 OsShellCmdQueueCntGet(VOID)
{
    UINT32 loop;
    UINT32 queueCnt = 0;
    UINT32 intSave;
    LosQueueCB *queueCB = NULL;

    intSave = LOS_IntLock();
    queueCB = g_allQueue;
    for (loop = 0; loop < LOSCFG_BASE_IPC_QUEUE_LIMIT; loop++, queueCB++) {
        if (queueCB->queueState == OS_QUEUE_INUSED) {
            queueCnt++;
        }
    }
    LOS_IntRestore(intSave);
    return queueCnt;
}

UINT32 OsShellCmdSwtmrCntGet(VOID)
{
    UINT32 loop;
    UINT32 swtmrCnt = 0;
    UINT32 intSave;
    SWTMR_CTRL_S *swtmrCB = NULL;

    intSave = LOS_IntLock();
    swtmrCB = g_swtmrCBArray;
    for (loop = 0; loop < LOSCFG_BASE_CORE_SWTMR_LIMIT; loop++, swtmrCB++) {
        if (swtmrCB->ucState != OS_SWTMR_STATUS_UNUSED) {
            swtmrCnt++;
        }
    }
    LOS_IntRestore(intSave);
    return swtmrCnt;
}

LITE_OS_SEC_TEXT_MINOR VOID OsShellCmdSystemInfoGet(VOID)
{
    UINT8 isTaskEnable  = YES;
    UINT8 isSemEnable   = LOSCFG_BASE_IPC_SEM;
    UINT8 isQueueEnable = LOSCFG_BASE_IPC_QUEUE;
    UINT8 isSwtmrEnable = LOSCFG_BASE_CORE_SWTMR;

    PRINTK("\n   Module    Used      Total     Enabled\n");
    PRINTK("--------------------------------------------\n");
    PRINTK("   Task      %-10u%-10d%s\n",
           OsShellCmdTaskCntGet(),
           LOSCFG_BASE_CORE_TSK_LIMIT,
           SYSINFO_ENABLED(isTaskEnable));
    PRINTK("   Sem       %-10u%-10d%s\n",
           OsShellCmdSemCntGet(),
           LOSCFG_BASE_IPC_SEM_LIMIT,
           SYSINFO_ENABLED(isSemEnable));
    PRINTK("   Queue     %-10u%-10d%s\n",
           OsShellCmdQueueCntGet(),
           LOSCFG_BASE_IPC_QUEUE_LIMIT,
           SYSINFO_ENABLED(isQueueEnable));
    PRINTK("   SwTmr     %-10u%-10d%s\n",
           OsShellCmdSwtmrCntGet(),
           LOSCFG_BASE_CORE_SWTMR_LIMIT,
           SYSINFO_ENABLED(isSwtmrEnable));
}

INT32 OsShellCmdSystemInfo(INT32 argc, const CHAR **argv)
{
    if (argc == 0) {
        OsShellCmdSystemInfoGet();
        return 0;
    }
    PRINTK("systeminfo: invalid option %s\n"
           "Systeminfo has NO ARGS.\n",
           argv[0]);
    return -1;
}

#ifdef LOSCFG_SHELL
SHELLCMD_ENTRY(systeminfo_shellcmd, CMD_TYPE_EX, "systeminfo", 1, (CmdCallBackFunc)OsShellCmdSystemInfo);
#endif /* LOSCFG_SHELL */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
