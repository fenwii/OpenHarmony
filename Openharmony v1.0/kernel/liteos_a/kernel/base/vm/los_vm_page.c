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

#include "los_vm_page.h"
#include "los_vm_common.h"
#include "los_vm_phys.h"
#include "los_vm_boot.h"
#include "los_vm_filemap.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

LosVmPage *g_vmPageArray = NULL;
size_t g_vmPageArraySize;

STATIC VOID OsVmPageInit(LosVmPage *page, paddr_t pa, UINT8 segID)
{
    LOS_ListInit(&page->node);
    page->flags = FILE_PAGE_FREE;
    LOS_AtomicSet(&page->refCounts, 0);
    page->physAddr = pa;
    page->segID = segID;
    page->order = VM_LIST_ORDER_MAX;
}

STATIC INLINE VOID OsVmPageOrderListInit(LosVmPage *page, size_t nPages)
{
    OsVmPhysPagesFreeContiguous(page, nPages);
}

VOID OsVmPageStartup(VOID)
{
    struct VmPhysSeg *seg = NULL;
    LosVmPage *page = NULL;
    paddr_t pa;
    UINT32 nPage;
    INT32 segID;

    OsVmPhysAreaSizeAdjust(ROUNDUP((g_vmBootMemBase - KERNEL_ASPACE_BASE), PAGE_SIZE));

    nPage = OsVmPhysPageNumGet();
    g_vmPageArraySize = nPage * sizeof(LosVmPage);
    g_vmPageArray = (LosVmPage *)OsVmBootMemAlloc(g_vmPageArraySize);

    OsVmPhysAreaSizeAdjust(ROUNDUP(g_vmPageArraySize, PAGE_SIZE));

    OsVmPhysSegAdd();
    OsVmPhysInit();

    for (segID = 0; segID < g_vmPhysSegNum; segID++) {
        seg = &g_vmPhysSeg[segID];
        nPage = seg->size >> PAGE_SHIFT;
        for (page = seg->pageBase, pa = seg->start; page <= seg->pageBase + nPage;
             page++, pa += PAGE_SIZE) {
            OsVmPageInit(page, pa, segID);
        }
        OsVmPageOrderListInit(seg->pageBase, nPage);
    }
}

LosVmPage *LOS_VmPageGet(PADDR_T paddr)
{
    INT32 segID;
    LosVmPage *page = NULL;

    for (segID = 0; segID < g_vmPhysSegNum; segID++) {
        page = OsVmPhysToPage(paddr, segID);
        if (page != NULL) {
            break;
        }
    }

    return page;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
