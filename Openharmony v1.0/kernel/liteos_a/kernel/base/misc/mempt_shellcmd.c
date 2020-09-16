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
#include "los_memory_pri.h"
#ifdef LOSCFG_MEM_RECORDINFO
#include "los_memrecord_pri.h"
#endif
#ifdef LOSCFG_SHELL_EXCINFO
#include "los_excinfo_pri.h"
#endif
#ifdef LOSCFG_SHELL
#include "shcmd.h"
#include "shell.h"
#endif
#include "los_vm_common.h"
#include "los_vm_boot.h"
#include "los_vm_map.h"
#include "los_vm_dump.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define MEM_SIZE_1K 0x400
#define MEM_SIZE_1M 0x100000
#define MEMPT_ARG_NUM_2         2

#define MEM_SIZE_TO_KB(size)    (((size) + (MEM_SIZE_1K >> 1)) / MEM_SIZE_1K)
#define MEM_SIZE_TO_MB(size)    (((size) + (MEM_SIZE_1M >> 1)) / MEM_SIZE_1M)

VOID OsDumpMemByte(size_t length, UINTPTR addr)
{
    size_t dataLen;
    UINTPTR *alignAddr = NULL;
    UINT32 count = 0;

    dataLen = ALIGN(length, sizeof(UINTPTR));
    alignAddr = (UINTPTR *)TRUNCATE(addr, sizeof(UINTPTR));
    if ((dataLen == 0) || (alignAddr == NULL)) {
        return;
    }
    while (dataLen) {
        if (IS_ALIGNED(count, sizeof(CHAR *))) {
            PRINTK("\n 0x%lx :", alignAddr);
#ifdef LOSCFG_SHELL_EXCINFO
            WriteExcInfoToBuf("\n 0x%lx :", alignAddr);
#endif
        }
#ifdef __LP64__
        PRINTK("%0+16lx ", *alignAddr);
#else
        PRINTK("%0+8lx ", *alignAddr);
#endif
#ifdef LOSCFG_SHELL_EXCINFO
#ifdef __LP64__
        WriteExcInfoToBuf("0x%0+16x ", *alignAddr);
#else
        WriteExcInfoToBuf("0x%0+8x ", *alignAddr);
#endif
#endif
        alignAddr++;
        dataLen -= sizeof(CHAR *);
        count++;
    }
    PRINTK("\n");
#ifdef LOSCFG_SHELL_EXCINFO
    WriteExcInfoToBuf("\n");
#endif

    return;
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdMemCheck(INT32 argc, const CHAR *argv[])
{
    if (argc > 0) {
        PRINTK("\nUsage: memcheck\n");
        return OS_ERROR;
    }

    if (LOS_MemIntegrityCheck(m_aucSysMem1) == LOS_OK) {
        PRINTK("system memcheck over, all passed!\n");
#ifdef LOSCFG_SHELL_EXCINFO
        WriteExcInfoToBuf("system memcheck over, all passed!\n");
#endif
    }
#ifdef LOSCFG_EXC_INTERACTION
    if (LOS_MemIntegrityCheck(m_aucSysMem0) == LOS_OK) {
        PRINTK("exc interaction memcheck over, all passed!\n");
#ifdef LOSCFG_SHELL_EXCINFO
        WriteExcInfoToBuf("exc interaction memcheck over, all passed!\n");
#endif
    }
#endif
    return 0;
}

#ifdef LOSCFG_SHELL
LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdMemRead(INT32 argc, const CHAR *argv[])
{
    size_t tempAddr;
    size_t length;
    CHAR *ptrlen = NULL;
    CHAR *ptrAddr = NULL;

    if ((argc == 0) || (argc > 2)) { /* argc is num of parameters */
        PRINTK("\nUsage: readreg [ADDRESS] [LENGTH]\n");
        return OS_ERROR;
    }

    if (argc == 1) {
        length = 0;
    } else {
        length = strtoul(argv[1], &ptrlen, 0);
        if ((ptrlen == NULL) || (*ptrlen != 0)) {
            PRINTK("readreg invalid length %s\n", argv[1]);
            return OS_ERROR;
        }
    }
    tempAddr = strtoul(argv[0], &ptrAddr, 0);
    if ((ptrAddr == NULL) || (*ptrAddr != 0)) {
        PRINTK("readreg invalid address %s\n", argv[0]);
        return OS_ERROR;
    }

    if (OsVmAddrCheck(tempAddr, length) == LOS_OK) {
        goto DONE;
    }

    PRINTK("readreg invalid address %s\n", argv[0]);
    return OS_ERROR;

DONE:
    OsDumpMemByte(length, tempAddr);

    return 0;
}

LITE_OS_SEC_TEXT_MINOR STATIC VOID OsShellCmdSectionInfo(INT32 argc, const CHAR *argv[])
{
    size_t textLen = &__text_end - &__text_start;
    size_t dataLen = &__ram_data_end - &__ram_data_start;
    size_t rodataLen = &__rodata_end - &__rodata_start;
    size_t bssLen = &__bss_end - &__bss_start;

    PRINTK("\r\n        text         data          rodata        bss\n");
    if ((argc == 1) && (strcmp(argv[0], "-k") == 0)) {
        PRINTK("Mem:    %-9lu    %-10lu    %-10lu    %-10lu\n", MEM_SIZE_TO_KB(textLen), MEM_SIZE_TO_KB(dataLen),
               MEM_SIZE_TO_KB(rodataLen), MEM_SIZE_TO_KB(bssLen));
    } else if ((argc == 1) && (strcmp(argv[0], "-m") == 0)) {
        PRINTK("Mem:    %-9lu    %-10lu    %-10lu    %-10lu\n", MEM_SIZE_TO_MB(textLen), MEM_SIZE_TO_MB(dataLen),
               MEM_SIZE_TO_MB(rodataLen), MEM_SIZE_TO_MB(bssLen));
    } else {
        PRINTK("Mem:    %-9lu    %-10lu    %-10lu    %-10lu\n", textLen, dataLen, rodataLen, bssLen);
    }
}

LITE_OS_SEC_TEXT_MINOR STATIC UINT32 OsShellCmdFreeInfo(INT32 argc, const CHAR *argv[])
{
#ifdef LOSCFG_EXC_INTERACTION
    UINT32 memUsed0 = LOS_MemTotalUsedGet(m_aucSysMem0);
    UINT32 totalMem0 = LOS_MemPoolSizeGet(m_aucSysMem0);
    UINT32 freeMem0 = totalMem0 - memUsed0;
#endif
    UINT32 memUsed = LOS_MemTotalUsedGet(m_aucSysMem1);
    UINT32 totalMem = LOS_MemPoolSizeGet(m_aucSysMem1);
    UINT32 freeMem = totalMem - memUsed;
    UINT32 usedCount, totalCount;
    UINT32 memUsedHeap = memUsed;

    OsVmPhysUsedInfoGet(&usedCount, &totalCount);
    totalMem = SYS_MEM_SIZE_DEFAULT;
    memUsed = SYS_MEM_SIZE_DEFAULT - (totalCount << PAGE_SHIFT);
    memUsed += (usedCount << PAGE_SHIFT) - freeMem;
    freeMem = totalMem - memUsed;

    if ((argc == 0) ||
        ((argc == 1) && (strcmp(argv[0], "-k") == 0)) ||
        ((argc == 1) && (strcmp(argv[0], "-m") == 0))) {
#ifdef LOSCFG_EXC_INTERACTION
        PRINTK("\r\n***** Mem:system mem      Mem1:exception interaction mem *****\n");
#endif
        PRINTK("\r\n        total        used          free          heap\n");
    }

    if ((argc == 1) && (strcmp(argv[0], "-k") == 0)) {
        PRINTK("Mem:    %-9u    %-10u    %-10u    %-10u\n", MEM_SIZE_TO_KB(totalMem), MEM_SIZE_TO_KB(memUsed),
               MEM_SIZE_TO_KB(freeMem), MEM_SIZE_TO_KB(memUsedHeap));
#ifdef LOSCFG_EXC_INTERACTION
        PRINTK("Mem1:   %-9u    %-10u    %-10u\n", MEM_SIZE_TO_KB(totalMem), MEM_SIZE_TO_KB(memUsed),
               MEM_SIZE_TO_KB(freeMem));
#endif
    } else if ((argc == 1) && (strcmp(argv[0], "-m") == 0)) {
        PRINTK("Mem:    %-9u    %-10u    %-10u    %-10u\n", MEM_SIZE_TO_MB(totalMem), MEM_SIZE_TO_MB(memUsed),
               MEM_SIZE_TO_MB(freeMem), MEM_SIZE_TO_MB(memUsedHeap));
#ifdef LOSCFG_EXC_INTERACTION
        PRINTK("Mem1:   %-9u    %-10u    %-10u\n", MEM_SIZE_TO_MB(totalMem), MEM_SIZE_TO_MB(memUsed),
               MEM_SIZE_TO_MB(freeMem));
#endif
    } else if (argc == 0) {
        PRINTK("Mem:    %-9u    %-10u    %-10u    %-10u\n", totalMem, memUsed, freeMem, memUsedHeap);
#ifdef LOSCFG_EXC_INTERACTION
        PRINTK("Mem1:   %-9u    %-10u    %-10u\n", totalMem0, memUsed0, freeMem0);
#endif
    } else {
        PRINTK("\nUsage: free or free [-k/-m]\n");
        return OS_ERROR;
    }
    return 0;
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdFree(INT32 argc, const CHAR *argv[])
{
    if (argc > 1) {
        PRINTK("\nUsage: free or free [-k/-m]\n");
        return OS_ERROR;
    }
    if (OsShellCmdFreeInfo(argc, argv) != 0) {
        return OS_ERROR;
    }
    OsShellCmdSectionInfo(argc, argv);
    return 0;
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdUname(INT32 argc, const CHAR *argv[])
{
    if (argc == 0) {
        PRINTK("%s\n", KERNEL_NAME);
        return 0;
    }

    if (argc == 1) {
        if (strcmp(argv[0], "-a") == 0) {
            PRINTK("%s %d.%d.%d.%d %s %s\n", KERNEL_NAME, KERNEL_MAJOR, KERNEL_MINOR, KERNEL_PATCH, KERNEL_ITRE,\
                __DATE__, __TIME__);
            return 0;
        } else if (strcmp(argv[0], "-s") == 0) {
            PRINTK("%s\n", KERNEL_NAME);
            return 0;
        } else if (strcmp(argv[0], "-t") == 0) {
            PRINTK("build date : %s %s\n", __DATE__, __TIME__);
            return 0;
        } else if (strcmp(argv[0], "-v") == 0) {
            PRINTK("%d.%d.%d.%d\n", KERNEL_MAJOR, KERNEL_MINOR, KERNEL_PATCH, KERNEL_ITRE);
            return 0;
        } else if (strcmp(argv[0], "--help") == 0) {
            PRINTK("-a,            print all information\n"
                   "-s,            print the kernel name\n"
                   "-t,            print the build date\n"
                   "-v,            print the kernel version\n");
            return 0;
        }
    }

    PRINTK("uname: invalid option %s\n"
           "Try 'uname --help' for more information.\n",
           argv[0]);
    return OS_ERROR;
}
#ifdef LOSCFG_MEM_LEAKCHECK
LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdMemUsed(INT32 argc, const CHAR *argv[])
{
    if (argc > 0) {
        PRINTK("\nUsage: memused\n");
        return OS_ERROR;
    }

    OsMemUsedNodeShow(m_aucSysMem1);

#ifdef LOSCFG_EXC_INTERACTION
    PRINTK("\n exc interaction memory\n");
    OsMemUsedNodeShow(m_aucSysMem0);
#endif
    return 0;
}
#endif
#ifdef LOSCFG_MEM_RECORDINFO
LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdMemRecordEnable(INT32 argc, const CHAR *argv[])
{
    OsMemRecordShowSet(1);
    return 0;
}

LITE_OS_SEC_TEXT_MINOR UINT32 OsShellCmdMemRecordDisable(INT32 argc, const CHAR *argv[])
{
    OsMemRecordShowSet(0);
    return 0;
}

SHELLCMD_ENTRY(memshowenable_shellcmd, CMD_TYPE_EX, "memshowenable", 0,
               (CmdCallBackFunc)OsShellCmdMemRecordEnable);
SHELLCMD_ENTRY(memshowdisable_shellcmd, CMD_TYPE_EX, "memshowdisable", 0,
               (CmdCallBackFunc)OsShellCmdMemRecordDisable);
#endif

#ifdef LOSCFG_MEM_LEAKCHECK
SHELLCMD_ENTRY(memused_shellcmd, CMD_TYPE_EX, "memused", 0, (CmdCallBackFunc)OsShellCmdMemUsed);
#endif

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(memcheck_shellcmd, CMD_TYPE_EX, "memcheck", 0, (CmdCallBackFunc)OsShellCmdMemCheck);
SHELLCMD_ENTRY(readreg_shellcmd, CMD_TYPE_EX, "readreg", MEMPT_ARG_NUM_2, (CmdCallBackFunc)OsShellCmdMemRead);
#endif
SHELLCMD_ENTRY(free_shellcmd, CMD_TYPE_EX, "free", XARGS, (CmdCallBackFunc)OsShellCmdFree);
SHELLCMD_ENTRY(uname_shellcmd, CMD_TYPE_EX, "uname", XARGS, (CmdCallBackFunc)OsShellCmdUname);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
