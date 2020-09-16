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
#ifdef LOSCFG_SHELL
#include "stdlib.h"
#include "los_cpup_pri.h"
#include "los_process_pri.h"
#include "shcmd.h"
#include "shell.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

VOID OsCmdCpupOperateOneParam(UINT32 mode)
{
    UINT32 ret;

    if (mode == CPUP_LAST_TEN_SECONDS) {
        PRINTK("\nSysCpuUsage in 10s: ");
    } else if (mode == CPUP_LAST_ONE_SECONDS) {
        PRINTK("\nSysCpuUsage in 1s: ");
    } else {
        PRINTK("\nSysCpuUsage in all time: ");
    }
    ret = LOS_HistorySysCpuUsage(mode);
    PRINTK("%u.%u\n", ret / LOS_CPUP_PRECISION_MULT, ret % LOS_CPUP_PRECISION_MULT);
}

VOID OsCmdCpupOperateTwoParam(UINT32 mode, UINT32 pid)
{
    UINT32 ret;

    if (mode == CPUP_LAST_TEN_SECONDS) {
        PRINTK("\npid %u CpuUsage in 10s: ", pid);
    } else if (mode == CPUP_LAST_ONE_SECONDS) {
        PRINTK("\npid %u CpuUsage in 1s: ", pid);
    } else {
        PRINTK("\npid %u CpuUsage in all time: ", pid);
    }
    ret = LOS_HistoryProcessCpuUsage(pid, mode);
    PRINTK("%u.%u\n", ret / LOS_CPUP_PRECISION_MULT, ret % LOS_CPUP_PRECISION_MULT);
}

LITE_OS_SEC_TEXT STATIC VOID OsCpupCmdHelp(VOID)
{
    PRINTK("usage:\n");
    PRINTK("      cpup\n"
           "      cpup [MODE]\n"
           "      cpup [MODE] [PID] \n");
    PRINTK("\r\nMode parameter description:\n"
           "  0       SysCpuUsage in 10s\n"
           "  1       SysCpuUsage in 1s\n"
           "  others  SysCpuUsage in all time\n");
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdCpup(INT32 argc, const CHAR **argv)
{
    size_t mode, pid;
    CHAR *bufMode = NULL;
    CHAR *bufID = NULL;
    UINT32 ret;

    if (argc == 0) {
        ret = LOS_HistorySysCpuUsage(CPUP_LAST_TEN_SECONDS);
        PRINTK("\nSysCpuUsage in 10s: %u.%u\n", ret / LOS_CPUP_PRECISION_MULT, ret % LOS_CPUP_PRECISION_MULT);
        return LOS_OK;
    }

    if (!strcmp(argv[0], "-h") || !strcmp(argv[0], "--help")) {
        OsCpupCmdHelp();
        return LOS_OK;
    }

    mode = strtoul(argv[0], &bufMode, 0);
    if ((bufMode == NULL) || (*bufMode != 0)) {
        PRINTK("\nUnknown mode: %s\n", argv[0]);
        OsCpupCmdHelp();
        return LOS_OK;
    }

    if (mode > CPUP_ALL_TIME) {
        mode = CPUP_ALL_TIME;
    }

    if (argc == 1) {
        OsCmdCpupOperateOneParam(mode);
        return LOS_OK;
    }

    pid = strtoul(argv[1], &bufID, 0);
    if (OsProcessIDUserCheckInvalid(pid) || (*bufID != 0)) {
        PRINTK("\nUnknown pid: %s\n", argv[1]);
        return LOS_OK;
    }

    if (OsProcessIsDead(OS_PCB_FROM_PID(pid))) {
        PRINTK("\nUnknown pid: %u\n", pid);
        return LOS_OK;
    }

    /* when the parameters number is two */
    if (argc == 2) {
        OsCmdCpupOperateTwoParam(mode, pid);
        return LOS_OK;
    }

    OsCpupCmdHelp();
    return LOS_OK;
}

SHELLCMD_ENTRY(cpup_shellcmd, CMD_TYPE_EX, "cpup", XARGS, (CmdCallBackFunc)OsShellCmdCpup);
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif /* LOSCFG_SHELL */
