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

#ifndef _LOS_MEMORY_PRI_H
#define _LOS_MEMORY_PRI_H

#include "los_memory.h"
#include "los_spinlock.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

extern UINT32 OsMemSystemInit(UINTPTR memStart);
extern STATUS_T OsKHeapInit(size_t size);

#ifdef LOSCFG_EXC_INTERACTION
extern UINT32 OsMemExcInteractionInit(UINTPTR memStart);
#endif
extern VOID OsDumpMemByte(size_t length, UINTPTR addr);

#ifdef LOSCFG_MEM_LEAKCHECK
extern VOID OsMemUsedNodeShow(VOID *pool);
#endif

extern VOID OsMemResetEndNode(VOID *pool, UINTPTR preAddr);
extern UINT32 OsMemLargeNodeFree(const VOID *ptr);
extern BOOL OsMemIsHeapNode(const VOID *ptr);
extern UINT32 OsShellCmdMemCheck(INT32 argc, const CHAR *argv[]);

/* spinlock for mem module, only available on SMP mode */
extern SPIN_LOCK_S g_memSpin;
#define MEM_LOCK(state)       LOS_SpinLockSave(&g_memSpin, &(state))
#define MEM_UNLOCK(state)     LOS_SpinUnlockRestore(&g_memSpin, (state))

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_MEMORY_PRI_H */
