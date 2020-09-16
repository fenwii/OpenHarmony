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

/**
 * @defgroup los_vm_syscall vm syscall definition
 * @ingroup kernel
 */

#ifndef __LOS_VM_SYSCALL_H__
#define __LOS_VM_SYSCALL_H__

#include "sys/shm.h"
#include "sys/mman.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

STATIC INLINE BOOL LOS_IsNamedMapping(unsigned long flags)
{
    return ((flags & MAP_ANONYMOUS) == 0);
}

STATIC INLINE BOOL LOS_IsAnonymousMapping(unsigned long flags)
{
    return ((flags & MAP_ANONYMOUS) == MAP_ANONYMOUS);
}

VADDR_T LOS_MMap(VADDR_T vaddr, size_t len, unsigned prot, unsigned long flags, int fd, unsigned long pgoff);
STATUS_T LOS_UnMMap(VADDR_T addr, size_t size);
VOID *LOS_DoBrk(VOID *addr);
int LOS_DoMprotect(VADDR_T vaddr, size_t len, unsigned long prot);
VADDR_T LOS_DoMremap(VADDR_T oldAddress, size_t oldSize, size_t newSize, int flags, VADDR_T newAddr);
VOID LOS_DumpMemRegion(VADDR_T vaddr);
INT32 ShmInit(VOID);
INT32 ShmDeinit(VOID);
INT32 ShmGet(key_t key, size_t size, INT32 shmflg);
VOID *ShmAt(INT32 shmid, const VOID *shmaddr, INT32 shmflg);
INT32 ShmCtl(INT32 shmid, INT32 cmd, struct shmid_ds *buf);
INT32 ShmDt(const VOID *shmaddr);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __LOS_VM_SYSCALL_H__ */
