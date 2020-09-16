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

#ifndef _LOS_LOAD_ELF_H
#define _LOS_LOAD_ELF_H

#include "los_ld_elf_pri.h"
#include "los_elf_auxvec_pri.h"
#include "los_process_pri.h"
#include "los_memory.h"
#include "los_strncpy_from_user.h"
#include "los_strnlen_user.h"
#include "los_user_put.h"
#include "los_user_get.h"
#include "user_copy.h"
#include "sys/stat.h"
#ifdef LOSCFG_DRIVERS_TZDRIVER
#include "fs/file.h"
#endif
#include "fs/fs.h"
#include "unistd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define INTERP_FULL_PATH                    "/lib/libc.so"
#define INVALID_FD                          (-1)
#define STRINGS_COUNT_MAX                   256
#define ELF_PHDR_NUM_MAX                    128
#define FILE_LENGTH_MAX                     0x1000000
#define MEM_SIZE_MAX                        0x1000000

#ifndef FILE_PATH_MAX
#define FILE_PATH_MAX                       PATH_MAX
#endif
#ifndef FILE_PATH_MIN
#define FILE_PATH_MIN                       2
#endif

#define USER_STACK_SIZE                     0x100000
#define USER_PARAM_BYTE_MAX                 0x1000
#define USER_STACK_TOP_MAX                  USER_ASPACE_TOP_MAX

#define EXEC_MMAP_BASE                      0x02000000

#ifdef LOSCFG_ASLR
#define RANDOM_MASK                         ((((USER_ASPACE_TOP_MAX + GB - 1) & (-GB)) >> 3) - 1)
#endif

#define STACK_ALIGN_SIZE                    0x10

/* The permissions on sections in the program header. */
#define PF_R                                0x4
#define PF_W                                0x2
#define PF_X                                0x1

typedef struct {
    const CHAR   *fileName;
    CHAR         *execName;
    INT32        argc;
    INT32        envc;
    CHAR *const  *argv;
    CHAR *const  *envp;
    UINTPTR      stackTop;
    UINTPTR      stackTopMax;
    UINTPTR      stackBase;
    UINTPTR      stackParamBase;
    UINT32       stackSize;
    INT32        stackProt;
    UINTPTR      loadAddr;
    UINTPTR      elfEntry;
    LD_ELF_EHDR  elfEhdr;
    LD_ELF_PHDR  *elfPhdr;
    UINT32       execFileLen;
    INT32        execFD;
    LD_ELF_EHDR  interpELFEhdr;
    LD_ELF_PHDR  *interpELFPhdr;
    UINT32       interpFileLen;
    INT32        interpFD;
    UINTPTR      topOfMem;
    UINTPTR      oldFiles;
    LosVmSpace   *newSpace;
    LosVmSpace   *oldSpace;
#ifdef LOSCFG_ASLR
    INT32        randomDevFD;
#endif
} ELFLoadInfo;

STATIC INLINE BOOL OsIsBadUserAddress(VADDR_T vaddr)
{
    return (vaddr >= USER_STACK_TOP_MAX);
}

extern INT32 OsLoadELFFile(ELFLoadInfo *loadInfo);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_ELF_LIB_H */
