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
 * @defgroup los_vm_dump virtual memory dump operation
 * @ingroup kernel
 */

#include "los_vm_dump.h"
#include "los_mmu_descriptor_v6.h"
#include "fs/fs.h"
#include "los_printf.h"
#include "los_vm_page.h"
#include "los_vm_phys.h"
#include "los_process_pri.h"
#include "los_atomic.h"
#include "los_vm_lock.h"
#include "los_memory_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define     FLAG_SIZE               4
#define     FLAG_START              2

const CHAR *OsGetRegionNameOrFilePath(LosVmMapRegion *region)
{
    struct file *filep = NULL;
    if (region == NULL) {
        return "";
#ifdef LOSCFG_FS_VFS
    } else if (LOS_IsRegionFileValid(region)) {
        filep = region->unTypeData.rf.file;
        return filep->f_path;
#endif
    } else if (region->regionFlags & VM_MAP_REGION_FLAG_HEAP) {
        return "HEAP";
    } else if (region->regionFlags & VM_MAP_REGION_FLAG_STACK) {
        return "STACK";
    } else if (region->regionFlags & VM_MAP_REGION_FLAG_TEXT) {
        return "Text";
    } else if (region->regionFlags & VM_MAP_REGION_FLAG_VDSO) {
        return "VDSO";
    } else if (region->regionFlags & VM_MAP_REGION_FLAG_MMAP) {
        return "MMAP";
    } else if (region->regionFlags & VM_MAP_REGION_FLAG_SHM) {
        return "SHM";
    } else {
        return "";
    }
    return "";
}

INT32 OsRegionOverlapCheckUnlock(LosVmSpace *space, LosVmMapRegion *region)
{
    LosVmMapRegion *regionTemp = NULL;
    LosRbNode *pstRbNode = NULL;
    LosRbNode *pstRbNodeNext = NULL;

    /* search the region list */
    RB_SCAN_SAFE(&space->regionRbTree, pstRbNode, pstRbNodeNext)
        regionTemp = (LosVmMapRegion *)pstRbNode;
        if (region->range.base == regionTemp->range.base && region->range.size == regionTemp->range.size) {
            continue;
        }
        if (((region->range.base + region->range.size) > regionTemp->range.base) &&
            (region->range.base < (regionTemp->range.base + regionTemp->range.size))) {
            VM_ERR("overlap between regions:\n"
                   "flals:%#x base:%p size:%08x space:%p\n"
                   "flags:%#x base:%p size:%08x space:%p",
                   region->regionFlags, region->range.base, region->range.size, region->space,
                   regionTemp->regionFlags, regionTemp->range.base, regionTemp->range.size, regionTemp->space);
            return -1;
        }
    RB_SCAN_SAFE_END(&space->regionRbTree, pstRbNode, pstRbNodeNext)

    return 0;
}

UINT32 OsShellCmdProcessVmUsage(LosVmSpace *space)
{
    LosVmMapRegion *region = NULL;
    LosRbNode *pstRbNode = NULL;
    LosRbNode *pstRbNodeNext = NULL;
    UINT32 used = 0;

    if (space == NULL) {
        return 0;
    }

    if (space == LOS_GetKVmSpace()) {
        OsShellCmdProcessPmUsage(space, NULL, &used);
    } else {
        RB_SCAN_SAFE(&space->regionRbTree, pstRbNode, pstRbNodeNext)
            region = (LosVmMapRegion *)pstRbNode;
            used += region->range.size;
        RB_SCAN_SAFE_END(&space->regionRbTree, pstRbNode, pstRbNodeNext)
    }

    return used;
}

VOID OsKProcessPmUsage(LosVmSpace *kSpace, UINT32 *actualPm)
{
    UINT32 memUsed;
    UINT32 totalMem;
    UINT32 freeMem;
    UINT32 usedCount = 0;
    UINT32 totalCount = 0;
    LosVmSpace *space = NULL;
    LOS_DL_LIST *spaceList = NULL;
    UINT32 UProcessUsed = 0;
    UINT32 pmTmp;

    if (actualPm == NULL) {
        return;
    }

    memUsed = LOS_MemTotalUsedGet(m_aucSysMem1);
    totalMem = LOS_MemPoolSizeGet(m_aucSysMem1);
    freeMem = totalMem - memUsed;

    OsVmPhysUsedInfoGet(&usedCount, &totalCount);
    /* Kernel resident memory, include default heap memory */
    memUsed = SYS_MEM_SIZE_DEFAULT - (totalCount << PAGE_SHIFT);

    spaceList = LOS_GetVmSpaceList();
    LOS_DL_LIST_FOR_EACH_ENTRY(space, spaceList, LosVmSpace, node) {
        if (space == LOS_GetKVmSpace()) {
            continue;
        }
        OsUProcessPmUsage(space, NULL, &pmTmp);
        UProcessUsed += pmTmp;
    }

    /* Kernel dynamic memory, include extended heap memory */
    memUsed += ((usedCount << PAGE_SHIFT) - UProcessUsed);
    /* Remaining heap memory */
    memUsed -= freeMem;

    *actualPm = memUsed;
}

VOID OsShellCmdProcessPmUsage(LosVmSpace *space, UINT32 *sharePm, UINT32 *actualPm)
{
    if (space == NULL) {
        return;
    }

    if ((sharePm == NULL) && (actualPm == NULL)) {
        return;
    }

    if (space == LOS_GetKVmSpace()) {
        OsKProcessPmUsage(space, actualPm);
    } else {
        OsUProcessPmUsage(space, sharePm, actualPm);
    }
}

VOID OsUProcessPmUsage(LosVmSpace *space, UINT32 *sharePm, UINT32 *actualPm)
{
    LosVmMapRegion *region = NULL;
    LosRbNode *pstRbNode = NULL;
    LosRbNode *pstRbNodeNext = NULL;
    LosVmPage *page = NULL;
    VADDR_T vaddr;
    size_t size;
    PADDR_T paddr;
    STATUS_T ret;
    INT32 shareRef;

    if (sharePm != NULL) {
        *sharePm = 0;
    }

    if (actualPm != NULL) {
        *actualPm = 0;
    }

    RB_SCAN_SAFE(&space->regionRbTree, pstRbNode, pstRbNodeNext)
        region = (LosVmMapRegion *)pstRbNode;
        vaddr = region->range.base;
        size = region->range.size;
        for (; size > 0; vaddr += PAGE_SIZE, size -= PAGE_SIZE) {
            ret = LOS_ArchMmuQuery(&space->archMmu, vaddr, &paddr, NULL);
            if (ret < 0) {
                continue;
            }
            page = LOS_VmPageGet(paddr);
            if (page == NULL) {
                continue;
            }

            shareRef = LOS_AtomicRead(&page->refCounts);
            if (shareRef > 1) {
                if (sharePm != NULL) {
                    *sharePm += PAGE_SIZE;
                }
                if (actualPm != NULL) {
                    *actualPm += PAGE_SIZE / shareRef;
                }
            } else {
                if (actualPm != NULL) {
                    *actualPm += PAGE_SIZE;
                }
            }
        }
    RB_SCAN_SAFE_END(&oldVmSpace->regionRbTree, pstRbNode, pstRbNodeNext)
}

LosProcessCB *OsGetPIDByAspace(LosVmSpace *space)
{
    UINT32 pid;
    UINT32 intSave;
    LosProcessCB *processCB = NULL;

    SCHEDULER_LOCK(intSave);
    for (pid = 0; pid < g_processMaxNum; ++pid) {
        processCB = g_processCBArray + pid;
        if (OsProcessIsUnused(processCB)) {
            continue;
        }

        if (processCB->vmSpace == space) {
            SCHEDULER_UNLOCK(intSave);
            return processCB;
        }
    }
    SCHEDULER_UNLOCK(intSave);
    return NULL;
}

UINT32 OsCountRegionPages(LosVmSpace *space, LosVmMapRegion *region, UINT32 *pssPages)
{
    UINT32 regionPages = 0;
    PADDR_T paddr;
    VADDR_T vaddr;
    UINT32 ref;
    STATUS_T status;
    float pss = 0;
    LosVmPage *page = NULL;

    for (vaddr = region->range.base; vaddr < region->range.base + region->range.size; vaddr = vaddr + PAGE_SIZE) {
        status = LOS_ArchMmuQuery(&space->archMmu, vaddr, &paddr, NULL);
        if (status == LOS_OK) {
            regionPages++;
            if (pssPages == NULL) {
                continue;
            }
            page = LOS_VmPageGet(paddr);
            if (page != NULL) {
                ref = LOS_AtomicRead(&page->refCounts);
                pss += ((ref > 0) ? (1.0 / ref) : 1);
            } else {
                pss += 1;
            }
        }
    }

    if (pssPages != NULL) {
        *pssPages = (UINT32)(pss + 0.5);
    }

    return regionPages;
}

UINT32 OsCountAspacePages(LosVmSpace *space)
{
    UINT32 spacePages = 0;
    LosVmMapRegion *region = NULL;
    LosRbNode *pstRbNode = NULL;
    LosRbNode *pstRbNodeNext = NULL;

    RB_SCAN_SAFE(&space->regionRbTree, pstRbNode, pstRbNodeNext)
        region = (LosVmMapRegion *)pstRbNode;
        spacePages += OsCountRegionPages(space, region, NULL);
    RB_SCAN_SAFE_END(&space->regionRbTree, pstRbNode, pstRbNodeNext)
    return spacePages;
}

CHAR *OsArchFlagsToStr(const UINT32 archFlags)
{
    UINT32 index;
    UINT32 cacheFlags = archFlags & VM_MAP_REGION_FLAG_CACHE_MASK;
    UINT32 flagSize = FLAG_SIZE * BITMAP_BITS_PER_WORD * sizeof(CHAR);
    CHAR *archMmuFlagsStr = (CHAR *)LOS_MemAlloc(m_aucSysMem0, flagSize);
    if (archMmuFlagsStr == NULL) {
        return NULL;
    }
    (VOID)memset_s(archMmuFlagsStr, flagSize, 0, flagSize);
    switch (cacheFlags) {
        case 0UL:
            strcat_s(archMmuFlagsStr, flagSize, " CH\0");
            break;
        case 1UL:
            strcat_s(archMmuFlagsStr, flagSize, " UC\0");
            break;
        case 2UL:
            strcat_s(archMmuFlagsStr, flagSize, " UD\0");
            break;
        case 3UL:
            strcat_s(archMmuFlagsStr, flagSize, " WC\0");
            break;
        default:
            break;
    }

    static const CHAR FLAGS[BITMAP_BITS_PER_WORD][FLAG_SIZE] = {
        [0 ... (__builtin_ffsl(VM_MAP_REGION_FLAG_PERM_USER) - 2)] = "???\0",
        [__builtin_ffsl(VM_MAP_REGION_FLAG_PERM_USER) - 1] = " US\0",
        [__builtin_ffsl(VM_MAP_REGION_FLAG_PERM_READ) - 1] = " RD\0",
        [__builtin_ffsl(VM_MAP_REGION_FLAG_PERM_WRITE) - 1] = " WR\0",
        [__builtin_ffsl(VM_MAP_REGION_FLAG_PERM_EXECUTE) - 1] = " EX\0",
        [__builtin_ffsl(VM_MAP_REGION_FLAG_NS) - 1] = " NS\0",
        [__builtin_ffsl(VM_MAP_REGION_FLAG_INVALID) - 1] = " IN\0",
        [__builtin_ffsl(VM_MAP_REGION_FLAG_INVALID) ... (BITMAP_BITS_PER_WORD - 1)] = "???\0",
    };

    for (index = FLAG_START; index < BITMAP_BITS_PER_WORD; index++) {
        if (FLAGS[index][0] == '?') {
            continue;
        }

        if (archFlags & (1UL << index)) {
            UINT32 status = strcat_s(archMmuFlagsStr, flagSize, FLAGS[index]);
            if (status != 0) {
                PRINTK("error\n");
            }
        }
    }

    return archMmuFlagsStr;
}

VOID OsDumpRegion2(LosVmSpace *space, LosVmMapRegion *region)
{
    UINT32 pssPages = 0;
    UINT32 regionPages;

    regionPages = OsCountRegionPages(space, region, &pssPages);
    CHAR *flagsStr = OsArchFlagsToStr(region->regionFlags);
    if (flagsStr == NULL) {
        return;
    }
    PRINTK("\t %#010x  %-32.32s %#010x %#010x %-15.15s %4d    %4d\n",
        region, OsGetRegionNameOrFilePath(region), region->range.base,
        region->range.size, flagsStr, regionPages, pssPages);
    (VOID)LOS_MemFree(m_aucSysMem0, flagsStr);
}

VOID OsDumpAspace(LosVmSpace *space)
{
    LosVmMapRegion *region = NULL;
    LosRbNode *pstRbNode = NULL;
    LosRbNode *pstRbNodeNext = NULL;
    UINT32 spacePages;
    LosProcessCB *pcb = OsGetPIDByAspace(space);

    if (pcb == NULL) {
        return;
    }

    spacePages = OsCountAspacePages(space);
    PRINTK("\r\n PID    aspace     name       base       size     pages \n");
    PRINTK(" ----   ------     ----       ----       -----     ----\n");
    PRINTK(" %-4d %#010x %-10.10s %#010x %#010x     %d\n", pcb->processID, space, pcb->processName,
        space->base, space->size, spacePages);
    PRINTK("\r\n\t region      name                base       size       mmu_flags      pages   pg/ref\n");
    PRINTK("\t ------      ----                ----       ----       ---------      -----   -----\n");
    RB_SCAN_SAFE(&space->regionRbTree, pstRbNode, pstRbNodeNext)
        region = (LosVmMapRegion *)pstRbNode;
        if (region != NULL) {
            OsDumpRegion2(space, region);
            (VOID)OsRegionOverlapCheck(space, region);
        } else {
            PRINTK("region is NULL\n");
        }
    RB_SCAN_SAFE_END(&space->regionRbTree, pstRbNode, pstRbNodeNext)
    return;
}

VOID OsDumpAllAspace(VOID)
{
    LosVmSpace *space = NULL;
    LOS_DL_LIST *aspaceList = LOS_GetVmSpaceList();
    LOS_DL_LIST_FOR_EACH_ENTRY(space, aspaceList, LosVmSpace, node) {
        (VOID)LOS_MuxAcquire(&space->regionMux);
        OsDumpAspace(space);
        (VOID)LOS_MuxRelease(&space->regionMux);
    }
    return;
}

STATUS_T OsRegionOverlapCheck(LosVmSpace *space, LosVmMapRegion *region)
{
    int ret;

    if (space == NULL || region == NULL) {
        return -1;
    }

    (VOID)LOS_MuxAcquire(&space->regionMux);
    ret = OsRegionOverlapCheckUnlock(space, region);
    (VOID)LOS_MuxRelease(&space->regionMux);
    return ret;
}

VOID OsDumpPte(VADDR_T vaddr)
{
    UINT32 l1Index = vaddr >> MMU_DESCRIPTOR_L1_SMALL_SHIFT;
    LosVmSpace *space = LOS_SpaceGet(vaddr);
    UINT32 ttEntry;
    LosVmPage *page = NULL;
    PTE_T *l2Table = NULL;
    UINT32 l2Index;

    if (space == NULL) {
        return;
    }

    ttEntry = space->archMmu.virtTtb[l1Index];
    if (ttEntry) {
        l2Table = LOS_PaddrToKVaddr(MMU_DESCRIPTOR_L1_PAGE_TABLE_ADDR(ttEntry));
        l2Index = (vaddr % MMU_DESCRIPTOR_L1_SMALL_SIZE) >> PAGE_SHIFT;
        if (l2Table == NULL) {
            goto ERR;
        }
        page = LOS_VmPageGet(l2Table[l2Index] & ~(PAGE_SIZE - 1));
        if (page == NULL) {
            goto ERR;
        }
        PRINTK("vaddr %p, l1Index %d, ttEntry %p, l2Table %p, l2Index %d, pfn %p count %d\n",
               vaddr, l1Index, ttEntry, l2Table, l2Index, l2Table[l2Index], LOS_AtomicRead(&page->refCounts));
    } else {
        PRINTK("vaddr %p, l1Index %d, ttEntry %p\n", vaddr, l1Index, ttEntry);
    }
    return;
ERR:
    PRINTK("%s, error vaddr: %#x, l2Table: %#x, l2Index: %#x\n", __FUNCTION__, vaddr, l2Table, l2Index);
}

UINT32 OsVmPhySegPagesGet(LosVmPhysSeg *seg)
{
    UINT32 intSave;
    UINT32 flindex;
    UINT32 segFreePages = 0;

    LOS_SpinLockSave(&seg->freeListLock, &intSave);
    for (flindex = 0; flindex < VM_LIST_ORDER_MAX; flindex++) {
        segFreePages += ((1 << flindex) * seg->freeList[flindex].listCnt);
    }
    LOS_SpinUnlockRestore(&seg->freeListLock, intSave);

    return segFreePages;
}

VOID OsVmPhysDump(VOID)
{
    LosVmPhysSeg *seg = NULL;
    UINT32 segFreePages;
    UINT32 totalFreePages = 0;
    UINT32 totalPages = 0;
    UINT32 segIndex;

    for (segIndex = 0; segIndex < g_vmPhysSegNum; segIndex++) {
        seg = &g_vmPhysSeg[segIndex];
        if (seg->size > 0) {
            segFreePages = OsVmPhySegPagesGet(seg);
#ifdef LOSCFG_SHELL_CMD_DEBUG
            PRINTK("\r\n phys_seg      base         size        free_pages    \n");
            PRINTK(" --------      -------      ----------  ---------  \n");
#endif
            PRINTK(" %08p    %08p   0x%08x   %8u  \n", seg, seg->start, seg->size, segFreePages);
            totalFreePages += segFreePages;
            totalPages += (seg->size >> PAGE_SHIFT);

            PRINTK("active   anon   %d\n", seg->lruSize[VM_LRU_ACTIVE_ANON]);
            PRINTK("inactive anon   %d\n", seg->lruSize[VM_LRU_INACTIVE_ANON]);
            PRINTK("active   file   %d\n", seg->lruSize[VM_LRU_ACTIVE_FILE]);
            PRINTK("inactice file   %d\n", seg->lruSize[VM_LRU_INACTIVE_FILE]);
        }
    }
    PRINTK("\n\rpmm pages: total = %u, used = %u, free = %u\n",
           totalPages, (totalPages - totalFreePages), totalFreePages);
}

VOID OsVmPhysUsedInfoGet(UINT32 *usedCount, UINT32 *totalCount)
{
    UINT32 index;
    UINT32 segFreePages;
    LosVmPhysSeg *physSeg = NULL;

    if (usedCount == NULL || totalCount == NULL) {
        return;
    }
    *usedCount = 0;
    *totalCount = 0;

    for (index = 0; index < g_vmPhysSegNum; index++) {
        physSeg = &g_vmPhysSeg[index];
        if (physSeg->size > 0) {
            *totalCount += physSeg->size >> PAGE_SHIFT;
            segFreePages = OsVmPhySegPagesGet(physSeg);
            *usedCount += (*totalCount - segFreePages);
        }
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
