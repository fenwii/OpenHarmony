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

#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "los_printf.h"
#include "string.h"
#include "securec.h"
#ifdef LOSCFG_SHELL
#include "shcmd.h"
#include "shell.h"
#endif
#include "los_oom.h"
#include "los_vm_dump.h"
#include "los_process_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define ARGC_2             2
#define ARGC_1             1
#define ARGC_0             0
#define VMM_CMD            "vmm"
#define OOM_CMD            "oom"
#define VMM_PMM_CMD        "v2p"

LITE_OS_SEC_TEXT_MINOR VOID OsDumpKernelAspace(VOID)
{
    LosVmSpace *kAspace = LOS_GetKVmSpace();
    if (kAspace != NULL)  {
        OsDumpAspace(kAspace);
    } else {
        VM_ERR("kernel aspace is NULL");
    }
    return;
}

LITE_OS_SEC_TEXT_MINOR INT32 OsPid(const CHAR *str)
{
    UINT32 len = strlen(str);
    if (len <= 2) { // pid range is 0~63, max pid string length is 2
        for (UINT32 i = 0; i < len; i++) {
            if (isdigit(str[i]) == 0) {
                return -1;
            }
        }
        return atoi(str);
    }
    return -1;
}

LITE_OS_SEC_TEXT_MINOR VOID OsPrintUsage(VOID)
{
    PRINTK("-a,            print all vm address space information\n"
           "-k,            print the kernel vm address space information\n"
           "pid(0~63),     print process[pid] vm address space information\n"
           "-h | --help,   print vmm command usage\n");
}

LITE_OS_SEC_TEXT_MINOR VOID OsDoDumpVm(pid_t pid)
{
    LosProcessCB *processCB = NULL;

    if (OsProcessIDUserCheckInvalid(pid)) {
        PRINTK("\tThe process [%d] not valid\n", pid);
        return;
    }

    processCB = OS_PCB_FROM_PID(pid);
    if (!OsProcessIsUnused(processCB) && (processCB->vmSpace != NULL)) {
        OsDumpAspace(processCB->vmSpace);
    } else {
        PRINTK("\tThe process [%d] not active\n", pid);
    }
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdDumpVm(INT32 argc, const CHAR *argv[])
{
    if (argc == 0) {
        OsDumpAllAspace();
    } else if (argc == 1) {
        pid_t pid = OsPid(argv[0]);
        if (strcmp(argv[0], "-a") == 0) {
            OsDumpAllAspace();
        } else if (strcmp(argv[0], "-k") == 0) {
            OsDumpKernelAspace();
        } else if (pid >= 0) {
            OsDoDumpVm(pid);
        } else if (strcmp(argv[0], "-h") == 0 || strcmp(argv[0], "--help") == 0) {
            OsPrintUsage();
        } else {
            PRINTK("%s: invalid option: %s\n", VMM_CMD, argv[0]);
            OsPrintUsage();
        }
    } else {
        OsPrintUsage();
    }

    return OS_ERROR;
}

LITE_OS_SEC_TEXT_MINOR VOID V2PPrintUsage(VOID)
{
    PRINTK("pid vaddr(0x1000000~0x3e000000),     print physical address of virtual address\n"
           "-h | --help,                     print v2p command usage\n");
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdV2P(INT32 argc, const CHAR *argv[])
{
    UINT32 vaddr;
    PADDR_T paddr;
    CHAR *endPtr = NULL;

    if (argc == 0) {
        V2PPrintUsage();
    } else if (argc == 1) {
        if (strcmp(argv[0], "-h") == 0 || strcmp(argv[0], "--help") == 0) {
            V2PPrintUsage();
        }
    } else if (argc == 2) {
        pid_t pid = OsPid(argv[0]);
        vaddr = strtoul((CHAR *)argv[1], &endPtr, 0);
        if ((endPtr == NULL) || (*endPtr != 0)) {
            PRINTK("vaddr %s invalid. should be in range(0x1000000~0x3e000000) \n", argv[1]);
            return OS_ERROR;
        } else {
            if (pid >= 0) {
                if (pid < g_taskMaxNum) {
                    LosProcessCB *processCB = OS_PCB_FROM_PID(pid);
                    if (!OsProcessIsUnused(processCB)) {
                        paddr = 0;
                        LOS_ArchMmuQuery(&processCB->vmSpace->archMmu, (VADDR_T)vaddr, &paddr, 0);
                        if (paddr == 0) {
                            PRINTK("vaddr %#x is not in range or mapped\n", vaddr);
                        } else {
                            PRINTK("vaddr %#x is paddr %#x\n", vaddr, paddr);
                        }
                    } else {
                        PRINTK("\tThe process [%d] not active\n", pid);
                    }
                } else {
                    PRINTK("\tThe process [%d] not valid\n", pid);
                }
            } else {
                PRINTK("%s: invalid option: %s %s\n", VMM_PMM_CMD, argv[0], argv[1]);
            }
        }
    }

    return LOS_OK;
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdDumpPmm(VOID)
{
    OsVmPhysDump();

    return OS_ERROR;
}

LITE_OS_SEC_TEXT_MINOR VOID OomPrintUsage(VOID)
{
    PRINTK("\t-i [interval],     set oom check interval (ms)\n"
           "\t-m [mem byte],     set oom low memory threshold (Byte)\n"
           "\t-r [mem byte],     set page cache reclaim memory threshold (Byte)\n"
           "\t-h | --help,       print vmm command usage\n");
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdOom(INT32 argc, const CHAR *argv[])
{
    UINT32 lowMemThreshold;
    UINT32 reclaimMemThreshold;
    UINT32 checkInterval;
    CHAR *endPtr = NULL;

    if (argc == ARGC_0) {
        OomInfodump();
    } else if (argc == ARGC_1) {
        if (strcmp(argv[0], "-h") != 0 && strcmp(argv[0], "--help") != 0) {
            PRINTK("%s: invalid option: %s\n", OOM_CMD, argv[0]);
        }
        OomPrintUsage();
    } else if (argc == ARGC_2) {
        if (strcmp(argv[0], "-m") == 0) {
            lowMemThreshold = strtoul((CHAR *)argv[1], &endPtr, 0);
            if ((endPtr == NULL) || (*endPtr != 0)) {
                PRINTK("[oom] low mem threshold %s(byte) invalid.\n", argv[1]);
                return OS_ERROR;
            } else {
                OomSetLowMemThreashold(lowMemThreshold);
            }
        } else if (strcmp(argv[0], "-i") == 0) {
            checkInterval = strtoul((CHAR *)argv[1], &endPtr, 0);
            if ((endPtr == NULL) || (*endPtr != 0)) {
                PRINTK("[oom] check interval %s(us) invalid.\n", argv[1]);
                return OS_ERROR;
            } else {
                OomSetCheckInterval(checkInterval);
            }
        } else if (strcmp(argv[0], "-r") == 0) {
            reclaimMemThreshold = strtoul((CHAR *)argv[1], &endPtr, 0);
            if ((endPtr == NULL) || (*endPtr != 0)) {
                PRINTK("[oom] reclaim mem threshold %s(byte) invalid.\n", argv[1]);
                return OS_ERROR;
            } else {
                OomSetReclaimMemThreashold(reclaimMemThreshold);
            }
        } else {
            PRINTK("%s: invalid option: %s %s\n", OOM_CMD, argv[0], argv[1]);
            OomPrintUsage();
        }
    } else {
        PRINTK("%s: invalid option\n", OOM_CMD);
        OomPrintUsage();
    }

    return OS_ERROR;
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(oom_shellcmd, CMD_TYPE_SHOW, OOM_CMD, 2, (CmdCallBackFunc)OsShellCmdOom);
SHELLCMD_ENTRY(vm_shellcmd, CMD_TYPE_SHOW, VMM_CMD, 1, (CmdCallBackFunc)OsShellCmdDumpVm);
SHELLCMD_ENTRY(v2p_shellcmd, CMD_TYPE_SHOW, VMM_PMM_CMD, 1, (CmdCallBackFunc)OsShellCmdV2P);
#endif

#ifdef LOSCFG_SHELL
SHELLCMD_ENTRY(pmm_shellcmd, CMD_TYPE_SHOW, "pmm", 0, (CmdCallBackFunc)OsShellCmdDumpPmm);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
