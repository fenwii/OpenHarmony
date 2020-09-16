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

#ifndef __VM_ZONE_H__
#define __VM_ZONE_H__

#include "board.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define DEFINE_(X)  X##U
#define DEFINE(X)   DEFINE_(X)

#define KERNEL_VMM_BASE         DEFINE(KERNEL_VADDR_BASE)
#define KERNEL_VMM_SIZE         DEFINE(KERNEL_VADDR_SIZE)

#define KERNEL_ASPACE_BASE      KERNEL_VMM_BASE
#define KERNEL_ASPACE_SIZE      KERNEL_VMM_SIZE

/* Uncached vmm aspace */
#define UNCACHED_VMM_BASE       (KERNEL_VMM_BASE + KERNEL_VMM_SIZE)
#define UNCACHED_VMM_SIZE       DDR_MEM_SIZE

#define VMALLOC_START           (UNCACHED_VMM_BASE + UNCACHED_VMM_SIZE)
#define VMALLOC_SIZE            0x08000000

#define PERIPH_DEVICE_BASE      (VMALLOC_START + VMALLOC_SIZE)
#define PERIPH_DEVICE_SIZE      PERIPH_PMM_SIZE
#define PERIPH_CACHED_BASE      (PERIPH_DEVICE_BASE + PERIPH_DEVICE_SIZE)
#define PERIPH_CACHED_SIZE      PERIPH_PMM_SIZE
#define PERIPH_UNCACHED_BASE    (PERIPH_CACHED_BASE + PERIPH_CACHED_SIZE)
#define PERIPH_UNCACHED_SIZE    PERIPH_PMM_SIZE

#define IO_DEVICE_ADDR(paddr)        (paddr - PERIPH_PMM_BASE + PERIPH_DEVICE_BASE)
#define IO_CACHED_ADDR(paddr)        (paddr - PERIPH_PMM_BASE + PERIPH_CACHED_BASE)
#define IO_UNCACHED_ADDR(paddr)      (paddr - PERIPH_PMM_BASE + PERIPH_UNCACHED_BASE)

#define MEM_CACHED_ADDR(paddr)       (paddr - DDR_MEM_ADDR + KERNEL_VMM_BASE)
#define MEM_UNCACHED_ADDR(paddr)     (paddr - DDR_MEM_ADDR + UNCACHED_VMM_BASE)

#define VMM_TO_UNCACHED_ADDR(vaddr)  (vaddr - KERNEL_VMM_BASE + UNCACHED_VMM_BASE)
#define UNCACHED_TO_VMM_ADDR(vaddr)  (vaddr - UNCACHED_VMM_BASE + KERNEL_VMM_BASE)

#define VMM_TO_DMA_ADDR(vaddr)  (vaddr - KERNEL_VMM_BASE + SYS_MEM_BASE)
#define DMA_TO_VMM_ADDR(vaddr)  (vaddr - SYS_MEM_BASE + KERNEL_VMM_BASE)

#if (PERIPH_UNCACHED_BASE >= (0xFFFFFFFFU - PERIPH_UNCACHED_SIZE))
#error "Kernel virtual memory space has overflowed!"
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
