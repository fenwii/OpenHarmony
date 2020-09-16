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

#ifndef __LOS_VM_PHYS_H__
#define __LOS_VM_PHYS_H__

#include "los_typedef.h"
#include "los_list.h"
#include "los_spinlock.h"
#include "los_vm_page.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define VM_LIST_ORDER_MAX    9
#define VM_PHYS_SEG_MAX    32

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif

#define VM_PAGE_TO_PHYS(page)    (page->physAddr)
#define VM_ORDER_TO_PAGES(order) (1 << (order))
#define VM_ORDER_TO_PHYS(order)  (1 << (PAGE_SHIFT + (order)))
#define VM_PHYS_TO_ORDER(phys)   (min(LOS_LowBitGet((phys) >> PAGE_SHIFT), VM_LIST_ORDER_MAX - 1))

struct VmFreeList {
    LOS_DL_LIST node;
    UINT32 listCnt;
};

enum OsLruList {
    VM_LRU_INACTIVE_ANON = 0,
    VM_LRU_ACTIVE_ANON,
    VM_LRU_INACTIVE_FILE,
    VM_LRU_ACTIVE_FILE,
    VM_LRU_UNEVICTABLE,
    VM_NR_LRU_LISTS
};

typedef struct VmPhysSeg {
    PADDR_T start;            /* The start of physical memory area */
    size_t size;              /* The size of physical memory area */
    LosVmPage *pageBase;      /* The first page address of this area */

    SPIN_LOCK_S freeListLock; /* The buddy list spinlock */
    struct VmFreeList freeList[VM_LIST_ORDER_MAX];  /* The free pages in the buddy list */

    SPIN_LOCK_S lruLock;
    size_t lruSize[VM_NR_LRU_LISTS];
    LOS_DL_LIST lruList[VM_NR_LRU_LISTS];
} LosVmPhysSeg;

struct VmPhysArea {
    PADDR_T start;
    size_t size;
};

extern struct VmPhysSeg g_vmPhysSeg[VM_PHYS_SEG_MAX];
extern INT32 g_vmPhysSegNum;

UINT32 OsVmPagesToOrder(size_t nPages);
struct VmPhysSeg *OsVmPhysSegGet(LosVmPage *page);
LosVmPhysSeg *OsGVmPhysSegGet(VOID);
VOID *OsVmPageToVaddr(LosVmPage *page);
VOID OsVmPhysSegAdd(VOID);
VOID OsVmPhysInit(VOID);
VOID OsVmPhysAreaSizeAdjust(size_t size);
UINT32 OsVmPhysPageNumGet(VOID);
LosVmPage *OsVmVaddrToPage(VOID *ptr);
VOID OsPhysSharePageCopy(PADDR_T oldPaddr, PADDR_T *newPaddr, LosVmPage *newPage);
VOID OsVmPhysPagesFreeContiguous(LosVmPage *page, size_t nPages);
LosVmPage *OsVmPhysToPage(paddr_t pa, UINT8 segID);

LosVmPage *LOS_PhysPageAlloc(VOID);
VOID LOS_PhysPageFree(LosVmPage *page);
size_t LOS_PhysPagesAlloc(size_t nPages, LOS_DL_LIST *list);
size_t LOS_PhysPagesFree(LOS_DL_LIST *list);
VOID *LOS_PhysPagesAllocContiguous(size_t nPages);
VOID LOS_PhysPagesFreeContiguous(VOID *ptr, size_t nPages);
VADDR_T *LOS_PaddrToKVaddr(PADDR_T paddr);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __LOS_VM_PHYS_H__ */
