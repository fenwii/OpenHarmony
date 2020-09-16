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

#include "los_vm_iomap.h"
#include "los_printf.h"
#include "los_vm_zone.h"
#include "los_vm_common.h"
#include "los_vm_map.h"
#include "los_vm_lock.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

VOID *ioremap(PADDR_T paddr, unsigned long size)
{
    if (IS_PERIPH_ADDR(paddr) && IS_PERIPH_ADDR(paddr + size)) {
        return (VOID *)(UINTPTR)IO_DEVICE_ADDR(paddr);
    }

    VM_ERR("ioremap failed invalid addr or size %p %d", paddr, size);
    return (VOID *)(UINTPTR)paddr;
}

VOID iounmap(VOID *vaddr) {}

VOID *ioremap_nocache(PADDR_T paddr, unsigned long size)
{
    if (IS_PERIPH_ADDR(paddr) && IS_PERIPH_ADDR(paddr + size)) {
        return (VOID *)(UINTPTR)IO_UNCACHED_ADDR(paddr);
    }

    if (IS_MEMORY_ADDR(paddr) && IS_MEMORY_ADDR(paddr + size)) {
        return (VOID *)(UINTPTR)MEM_UNCACHED_ADDR(paddr);
    }

    VM_ERR("ioremap_nocache failed invalid addr or size %p %d", paddr, size);
    return (VOID *)(UINTPTR)paddr;
}

VOID *ioremap_cached(PADDR_T paddr, unsigned long size)
{
    if (IS_PERIPH_ADDR(paddr) && IS_PERIPH_ADDR(paddr + size)) {
        return (VOID *)(UINTPTR)IO_CACHED_ADDR(paddr);
    }

    if (IS_MEMORY_ADDR(paddr) && IS_MEMORY_ADDR(paddr + size)) {
        return (VOID *)(UINTPTR)MEM_CACHED_ADDR(paddr);
    }

    VM_ERR("ioremap_cached failed invalid addr or size %p %d", paddr, size);
    return (VOID *)(UINTPTR)paddr;
}

int remap_pfn_range(VADDR_T vaddr, unsigned long pfn, unsigned long size, unsigned long prot)
{
    STATUS_T status = LOS_OK;
    int ret;
    LosVmMapRegion *region = NULL;
    unsigned long vpos;
    unsigned long end;
    unsigned long paddr = pfn << PAGE_SHIFT;
    LosVmSpace *space = LOS_SpaceGet(vaddr);

    if (size == 0) {
        VM_ERR("invalid map size %u", size);
        return LOS_ERRNO_VM_INVALID_ARGS;
    }
    size = ROUNDUP(size, PAGE_SIZE);

    if (!IS_PAGE_ALIGNED(vaddr) || pfn == 0) {
        VM_ERR("invalid map map vaddr %x or pfn %x", vaddr, pfn);
        return LOS_ERRNO_VM_INVALID_ARGS;
    }

    if (space == NULL) {
        VM_ERR("aspace not exists");
        return LOS_ERRNO_VM_NOT_FOUND;
    }

    (VOID)LOS_MuxAcquire(&space->regionMux);

    region = LOS_RegionFind(space, vaddr);
    if (region == NULL) {
        VM_ERR("region not exists");
        status = LOS_ERRNO_VM_NOT_FOUND;
        goto OUT;
    }
    end = vaddr + size;
    if (region->range.base + region->range.size < end) {
        VM_ERR("out of range:base=%x size=%d vaddr=%x len=%u",
               region->range.base, region->range.size, vaddr, size);
        status = LOS_ERRNO_VM_INVALID_ARGS;
        goto OUT;
    }

    /* check */
    for (vpos = vaddr; vpos < end; vpos += PAGE_SIZE) {
        status = LOS_ArchMmuQuery(&space->archMmu, (VADDR_T)vpos, NULL, NULL);
        if (status == LOS_OK) {
            VM_ERR("remap_pfn_range, address mapping already exist");
            status = LOS_ERRNO_VM_INVALID_ARGS;
            goto OUT;
        }
    }

    /* map all */
    ret = LOS_ArchMmuMap(&space->archMmu, vaddr, paddr, size >> PAGE_SHIFT, prot);
    if (ret <= 0) {
        VM_ERR("ioremap LOS_ArchMmuMap failed err = %d", ret);
        goto OUT;
    }

    status = LOS_OK;

OUT:
    (VOID)LOS_MuxRelease(&space->regionMux);
    return status;
}

VOID *LOS_DmaMemAlloc(DMA_ADDR_T *dmaAddr, size_t size, size_t align, enum DmaMemType type)
{
    VOID *kVaddr = NULL;

    if (size == 0) {
        return NULL;
    }

    if ((type != DMA_CACHE) && (type != DMA_NOCACHE)) {
        VM_ERR("The dma type = %d is not support!", type);
        return NULL;
    }

    kVaddr = LOS_KernelMallocAlign(size, align);
    if (kVaddr == NULL) {
        VM_ERR("failed, size = %u, align = %u", size, align);
        return NULL;
    }

    if (dmaAddr != NULL) {
        *dmaAddr = (DMA_ADDR_T)LOS_PaddrQuery(kVaddr);
    }

    if (type == DMA_NOCACHE) {
        kVaddr = (VOID *)VMM_TO_UNCACHED_ADDR((UINTPTR)kVaddr);
    }

    return kVaddr;
}

VOID LOS_DmaMemFree(VOID *vaddr)
{
    UINTPTR addr;

    if (vaddr == NULL) {
        return;
    }
    addr = (UINTPTR)vaddr;

    if ((addr >= UNCACHED_VMM_BASE) && (addr < UNCACHED_VMM_BASE + UNCACHED_VMM_SIZE)) {
        addr = UNCACHED_TO_VMM_ADDR(addr);
        LOS_KernelFree((VOID *)addr);
    } else if ((addr >= KERNEL_VMM_BASE) && (addr < KERNEL_VMM_BASE + KERNEL_VMM_SIZE)) {
        LOS_KernelFree((VOID *)addr);
    } else {
        VM_ERR("addr %#x not in dma area!!!", vaddr);
    }
    return;
}

DMA_ADDR_T LOS_DmaVaddrToPaddr(VOID *vaddr)
{
    status_t ret;
    paddr_t pa;
    LosVmSpace *space = LOS_GetKVmSpace();

    ret = LOS_ArchMmuQuery(&space->archMmu, (VADDR_T)(UINTPTR)vaddr, &pa, NULL);
    if (ret != LOS_OK) {
        return (DMA_ADDR_T)NULL;
    }

    return (DMA_ADDR_T)pa;
}
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
