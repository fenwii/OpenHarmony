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

/* flags for initial mapping struct */
#define MMU_INITIAL_MAPPING_TEMPORARY       (0x1)
#define MMU_INITIAL_MAPPING_FLAG_UNCACHED   (0x2)
#define MMU_INITIAL_MAPPING_FLAG_DEVICE     (0x4)
#define MMU_INITIAL_MAPPING_FLAG_DYNAMIC    (0x8)
#ifndef ASSEMBLY

#ifndef __LOS_VM_BOOT_H__
#define __LOS_VM_BOOT_H__

#include "los_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define OS_KHEAP_BLOCK_SIZE                 (512 * 1024UL)

typedef struct ArchMmuInitMapping {
    PADDR_T phys;
    VADDR_T virt;
    size_t  size;
    unsigned int flags;
    const char *name;
} LosArchMmuInitMapping;

extern UINTPTR g_vmBootMemBase;
extern BOOL g_kHeapInited;

UINT32 OsVmAddrCheck(size_t tempAddr, size_t length);
VOID *OsVmBootMemAlloc(size_t len);
UINT32 OsSysMemInit(VOID);
VOID OsInitMappingStartUp(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif /* __LOS_VM_BOOT_H__ */
#endif /* ASSEMBLY */
