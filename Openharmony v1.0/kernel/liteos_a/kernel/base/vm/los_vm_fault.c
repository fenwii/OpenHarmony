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
 * @defgroup los_vm_fault vm fault definition
 * @ingroup kernel
 */
#include "los_vm_fault.h"
#include "los_vm_map.h"
#include "los_vm_dump.h"
#include "los_vm_filemap.h"
#include "los_vm_page.h"
#include "los_vm_lock.h"
#include "los_exc.h"
#include "los_oom.h"
#include "los_printf.h"
#include "los_process_pri.h"
#include "arm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

extern char __exc_table_start[];
extern char __exc_table_end[];

STATIC STATUS_T OsVmRegionRightCheck(LosVmMapRegion *region, UINT32 flags)
{
    if ((flags & VM_MAP_PF_FLAG_WRITE) == VM_MAP_PF_FLAG_WRITE) {
        if ((region->regionFlags & VM_MAP_REGION_FLAG_PERM_WRITE) != VM_MAP_REGION_FLAG_PERM_WRITE) {
            VM_ERR("write permission check failed operation flags %x, region flags %x", flags, region->regionFlags);
            return LOS_NOK;
        }
    }

    if ((flags & VM_MAP_PF_FLAG_INSTRUCTION) == VM_MAP_PF_FLAG_INSTRUCTION) {
        if ((region->regionFlags & VM_MAP_REGION_FLAG_PERM_EXECUTE) != VM_MAP_REGION_FLAG_PERM_EXECUTE) {
            VM_ERR("exec permission check failed operation flags %x, region flags %x", flags, region->regionFlags);
            return LOS_NOK;
        }
    }

    return LOS_OK;
}

STATIC VOID OsFaultTryFixup(ExcContext *frame, VADDR_T excVaddr, STATUS_T *status)
{
    INT32 tableNum = (__exc_table_end - __exc_table_start) / sizeof(LosExcTable);
    LosExcTable *excTable = (LosExcTable *)__exc_table_start;
#ifdef LOSCFG_DEBUG_VERSION
    LosVmSpace *space = NULL;
    VADDR_T vaddr;
#endif

    if ((frame->regCPSR & CPSR_MODE_MASK) != CPSR_MODE_USR) {
        for (int i = 0; i < tableNum; ++i, ++excTable) {
            if (frame->PC == (UINTPTR)excTable->excAddr) {
                frame->PC = (UINTPTR)excTable->fixAddr;
                frame->R2 = (UINTPTR)excVaddr;
                *status = LOS_OK;
                return;
            }
        }
    }

#ifdef LOSCFG_DEBUG_VERSION
    vaddr = ROUNDDOWN(excVaddr, PAGE_SIZE);
    space = LOS_SpaceGet(vaddr);
    if (space != NULL) {
        LOS_DumpMemRegion(vaddr);
    }
#endif
}

#ifdef LOSCFG_FS_VFS
STATIC STATUS_T OsDoReadFault(LosVmMapRegion *region, LosVmPgFault *vmPgFault)
{
    status_t ret;
    PADDR_T paddr;
    LosVmPage *page = NULL;
    VADDR_T vaddr = (VADDR_T)vmPgFault->vaddr;
    LosVmSpace *space = region->space;

    ret = LOS_ArchMmuQuery(&space->archMmu, vaddr, NULL, NULL);
    if (ret == LOS_OK) {
        return LOS_OK;
    }
    if (region->unTypeData.rf.vmFOps == NULL || region->unTypeData.rf.vmFOps->fault == NULL) {
        VM_ERR("region args invalid, file path: %s", region->unTypeData.rf.file->f_path);
        return LOS_ERRNO_VM_INVALID_ARGS;
    }

    (VOID)LOS_MuxAcquire(&region->unTypeData.rf.file->f_mapping->mux_lock);
    ret = region->unTypeData.rf.vmFOps->fault(region, vmPgFault);
    if (ret == LOS_OK) {
        paddr = LOS_PaddrQuery(vmPgFault->pageKVaddr);
        page = LOS_VmPageGet(paddr);
        if (page != NULL) { /* just incase of page null */
            LOS_AtomicInc(&page->refCounts);
            OsCleanPageLocked(page);
        }
        ret = LOS_ArchMmuMap(&space->archMmu, vaddr, paddr, 1,
                             region->regionFlags & (~VM_MAP_REGION_FLAG_PERM_WRITE));
        if (ret < 0) {
            VM_ERR("LOS_ArchMmuMap fial");
            OsDelMapInfo(region, vmPgFault, false);
            (VOID)LOS_MuxRelease(&region->unTypeData.rf.file->f_mapping->mux_lock);
            return LOS_ERRNO_VM_NO_MEMORY;
        }

        (VOID)LOS_MuxRelease(&region->unTypeData.rf.file->f_mapping->mux_lock);
        return LOS_OK;
    }
    (VOID)LOS_MuxRelease(&region->unTypeData.rf.file->f_mapping->mux_lock);

    return LOS_ERRNO_VM_NO_MEMORY;
}

/* numap a page when cow happend only */
STATIC LosVmPage *OsCowUnmapOrg(LosArchMmu *archMmu, LosVmMapRegion *region, LosVmPgFault *vmf)
{
    UINT32 intSave;
    LosVmPage *oldPage = NULL;
    LosMapInfo *mapInfo = NULL;
    LosFilePage *fpage = NULL;
    VADDR_T vaddr = (VADDR_T)vmf->vaddr;

    LOS_SpinLockSave(&region->unTypeData.rf.file->f_mapping->list_lock, &intSave);
    fpage = OsFindGetEntry(region->unTypeData.rf.file->f_mapping, vmf->pgoff);
    if (fpage != NULL) {
        oldPage = fpage->vmPage;
        OsSetPageLocked(oldPage);
        mapInfo = OsGetMapInfo(fpage, archMmu, vaddr);
        if (mapInfo != NULL) {
            OsUnmapPageLocked(fpage, mapInfo);
        } else {
            LOS_ArchMmuUnmap(archMmu, vaddr, 1);
        }
    } else {
        LOS_ArchMmuUnmap(archMmu, vaddr, 1);
    }
    LOS_SpinUnlockRestore(&region->unTypeData.rf.file->f_mapping->list_lock, intSave);

    return oldPage;
}
#endif

status_t OsDoCowFault(LosVmMapRegion *region, LosVmPgFault *vmPgFault)
{
    STATUS_T ret;
    VOID *kvaddr = NULL;
    PADDR_T oldPaddr = 0;
    PADDR_T newPaddr;
    LosVmPage *oldPage = NULL;
    LosVmPage *newPage = NULL;
    LosVmSpace *space = NULL;

    if ((vmPgFault == NULL) || (region == NULL) ||
        (region->unTypeData.rf.vmFOps == NULL) || (region->unTypeData.rf.vmFOps->fault == NULL)) {
        VM_ERR("region args invalid");
        return LOS_ERRNO_VM_INVALID_ARGS;
    }

    space = region->space;
    ret = LOS_ArchMmuQuery(&space->archMmu, (VADDR_T)vmPgFault->vaddr, &oldPaddr, NULL);
    if (ret == LOS_OK) {
        oldPage = OsCowUnmapOrg(&space->archMmu, region, vmPgFault);
    }

    newPage = LOS_PhysPageAlloc();
    if (newPage == NULL) {
        VM_ERR("pmm_alloc_page fail");
        ret = LOS_ERRNO_VM_NO_MEMORY;
        goto ERR_OUT;
    }

    newPaddr = VM_PAGE_TO_PHYS(newPage);
    kvaddr = OsVmPageToVaddr(newPage);

    (VOID)LOS_MuxAcquire(&region->unTypeData.rf.file->f_mapping->mux_lock);
    ret = region->unTypeData.rf.vmFOps->fault(region, vmPgFault);
    if (ret != LOS_OK) {
        VM_ERR("call region->vm_ops->fault fail");
        (VOID)LOS_MuxRelease(&region->unTypeData.rf.file->f_mapping->mux_lock);
        goto ERR_OUT;
    }

    /**
     * here we get two conditions, 1.this page hasn't mapped or mapped from pagecache,
     * we can take it as a normal file cow map. 2.this page has done file cow map,
     * we can take it as a anonymous cow map.
     */
    if ((oldPaddr == 0) || (LOS_PaddrToKVaddr(oldPaddr) == vmPgFault->pageKVaddr)) {
        (VOID)memcpy_s(kvaddr, PAGE_SIZE, vmPgFault->pageKVaddr, PAGE_SIZE);
        LOS_AtomicInc(&newPage->refCounts);
        OsCleanPageLocked(LOS_VmPageGet(LOS_PaddrQuery(vmPgFault->pageKVaddr)));
    } else {
        OsPhysSharePageCopy(oldPaddr, &newPaddr, newPage);
        /* use old page free the new one */
        if (newPaddr == oldPaddr) {
            LOS_PhysPageFree(newPage);
            newPage = NULL;
        }
    }

    ret = LOS_ArchMmuMap(&space->archMmu, (VADDR_T)vmPgFault->vaddr, newPaddr, 1, region->regionFlags);
    if (ret < 0) {
        VM_ERR("LOS_ArchMmuMap fial");
        ret =  LOS_ERRNO_VM_NO_MEMORY;
        (VOID)LOS_MuxRelease(&region->unTypeData.rf.file->f_mapping->mux_lock);
        goto ERR_OUT;
    }
    (VOID)LOS_MuxRelease(&region->unTypeData.rf.file->f_mapping->mux_lock);

    if (oldPage != NULL) {
        OsCleanPageLocked(oldPage);
    }

    return LOS_OK;

ERR_OUT:
    if (newPage != NULL) {
        LOS_PhysPageFree(newPage);
    }
    if (oldPage != NULL) {
        OsCleanPageLocked(oldPage);
    }

    return ret;
}

status_t OsDoSharedFault(LosVmMapRegion *region, LosVmPgFault *vmPgFault)
{
    STATUS_T ret;
    UINT32 intSave;
    PADDR_T paddr = 0;
    VADDR_T vaddr = (VADDR_T)vmPgFault->vaddr;
    LosVmSpace *space = region->space;
    LosVmPage *page = NULL;
    LosFilePage *fpage = NULL;

    if ((region->unTypeData.rf.vmFOps == NULL) || (region->unTypeData.rf.vmFOps->fault == NULL)) {
        VM_ERR("region args invalid");
        return LOS_ERRNO_VM_INVALID_ARGS;
    }

    ret = LOS_ArchMmuQuery(&space->archMmu, vmPgFault->vaddr, &paddr, NULL);
    if (ret == LOS_OK) {
        LOS_ArchMmuUnmap(&space->archMmu, vmPgFault->vaddr, 1);
        ret = LOS_ArchMmuMap(&space->archMmu, vaddr, paddr, 1, region->regionFlags);
        if (ret < 0) {
            VM_ERR("LOS_ArchMmuMap failed. ret=%d", ret);
            return LOS_ERRNO_VM_NO_MEMORY;
        }

        LOS_SpinLockSave(&region->unTypeData.rf.file->f_mapping->list_lock, &intSave);
        fpage = OsFindGetEntry(region->unTypeData.rf.file->f_mapping, vmPgFault->pgoff);
        if (fpage) {
            OsMarkPageDirty(fpage, region, 0, 0);
        }
        LOS_SpinUnlockRestore(&region->unTypeData.rf.file->f_mapping->list_lock, intSave);

        return LOS_OK;
    }

    (VOID)LOS_MuxAcquire(&region->unTypeData.rf.file->f_mapping->mux_lock);
    ret = region->unTypeData.rf.vmFOps->fault(region, vmPgFault);
    if (ret == LOS_OK) {
        paddr = LOS_PaddrQuery(vmPgFault->pageKVaddr);
        page = LOS_VmPageGet(paddr);
         /* just in case of page null */
        if (page != NULL) {
            LOS_AtomicInc(&page->refCounts);
            OsCleanPageLocked(page);
        }
        ret = LOS_ArchMmuMap(&space->archMmu, vaddr, paddr, 1, region->regionFlags);
        if (ret < 0) {
            VM_ERR("LOS_ArchMmuMap failed. ret=%d", ret);
            OsDelMapInfo(region, vmPgFault, TRUE);
            (VOID)LOS_MuxRelease(&region->unTypeData.rf.file->f_mapping->mux_lock);
            return LOS_ERRNO_VM_NO_MEMORY;
        }

        (VOID)LOS_MuxRelease(&region->unTypeData.rf.file->f_mapping->mux_lock);
        return LOS_OK;
    }
    (VOID)LOS_MuxRelease(&region->unTypeData.rf.file->f_mapping->mux_lock);
    return ret;
}

/**
 * Page read operation is a simple case, just share the pagecache(save memory)
 * and make a read permission mmapping (region->arch_mmu_flags & (~ARCH_MMU_FLAG_PERM_WRITE)).
 * However for write operation, vmflag (VM_PRIVATE|VM_SHREAD) decides COW or SHARED fault.
 * For COW fault, pagecache is copied to private anonyous pages and the changes on this page
 * won't write through to the underlying file. For SHARED fault, pagecache is mapping with
 * region->arch_mmu_flags and the changes on this page will write through to the underlying file
 */
STATIC STATUS_T OsDoFileFault(LosVmMapRegion *region, LosVmPgFault *vmPgFault, UINT32 flags)
{
    STATUS_T ret;

    if (flags & VM_MAP_PF_FLAG_WRITE) {
        if (region->regionFlags & VM_MAP_REGION_FLAG_SHARED) {
            ret = OsDoSharedFault(region, vmPgFault);
        } else {
            ret = OsDoCowFault(region, vmPgFault);
        }
    } else {
        ret = OsDoReadFault(region, vmPgFault);
    }
    return ret;
}

STATUS_T OsVmPageFaultHandler(VADDR_T vaddr, UINT32 flags, ExcContext *frame)
{
    LosVmSpace *space = LOS_SpaceGet(vaddr);
    LosVmMapRegion *region = NULL;
    STATUS_T status;
    PADDR_T oldPaddr;
    PADDR_T newPaddr;
    VADDR_T excVaddr = vaddr;
    LosVmPage *newPage = NULL;
    LosVmPgFault vmPgFault = { 0 };

    if (space == NULL) {
        VM_ERR("vm space not exists, vaddr: %#x", vaddr);
        status = LOS_ERRNO_VM_NOT_FOUND;
        OsFaultTryFixup(frame, excVaddr, &status);
        return status;
    }

    if (((flags & VM_MAP_PF_FLAG_USER) != 0) && (!LOS_IsUserAddress(vaddr))) {
        VM_ERR("user space not allowed to access invalid address: %#x", vaddr);
        return LOS_ERRNO_VM_ACCESS_DENIED;
    }

    (VOID)LOS_MuxAcquire(&space->regionMux);
    region = LOS_RegionFind(space, vaddr);
    if (region == NULL) {
        VM_ERR("region not exists, vaddr: %#x", vaddr);
        status = LOS_ERRNO_VM_NOT_FOUND;
        goto CHECK_FAILED;
    }

    status = OsVmRegionRightCheck(region, flags);
    if (status != LOS_OK) {
        status = LOS_ERRNO_VM_ACCESS_DENIED;
        goto CHECK_FAILED;
    }

    if (OomCheckProcess()) {
        /*
         * under low memory, when user process request memory allocation
         * it will fail, and result is LOS_NOK and current user process
         * will be deleted. memory usage detail will be printed.
         */
        status = LOS_ERRNO_VM_NO_MEMORY;
        goto CHECK_FAILED;
    }

    vaddr = ROUNDDOWN(vaddr, PAGE_SIZE);
#ifdef LOSCFG_FS_VFS
    if (LOS_IsRegionFileValid(region)) {
        if (region->unTypeData.rf.file->f_mapping == NULL) {
            goto  CHECK_FAILED;
        }
        vmPgFault.vaddr = vaddr;
        vmPgFault.pgoff = ((vaddr - region->range.base) >> PAGE_SHIFT) + region->pgOff;
        vmPgFault.flags = flags;
        vmPgFault.pageKVaddr = NULL;

        status = OsDoFileFault(region, &vmPgFault, flags);
        if (status) {
            VM_ERR("vm fault error, status=%d", status);
            goto CHECK_FAILED;
        }
        goto DONE;
    }
#endif

    newPage = LOS_PhysPageAlloc();
    if (newPage == NULL) {
        status = LOS_ERRNO_VM_NO_MEMORY;
        goto CHECK_FAILED;
    }

    newPaddr = VM_PAGE_TO_PHYS(newPage);
    (VOID)memset_s(OsVmPageToVaddr(newPage), PAGE_SIZE, 0, PAGE_SIZE);
    status = LOS_ArchMmuQuery(&space->archMmu, vaddr, &oldPaddr, NULL);
    if (status >= 0) {
        LOS_ArchMmuUnmap(&space->archMmu, vaddr, 1);
        OsPhysSharePageCopy(oldPaddr, &newPaddr, newPage);
        /* use old page free the new one */
        if (newPaddr == oldPaddr) {
            LOS_PhysPageFree(newPage);
            newPage = NULL;
        }

        /* map all of the pages */
        status = LOS_ArchMmuMap(&space->archMmu, vaddr, newPaddr, 1, region->regionFlags);
        if (status < 0) {
            VM_ERR("failed to map replacement page, status:%d", status);
            status = LOS_ERRNO_VM_MAP_FAILED;
            goto VMM_MAP_FAILED;
        }

        status = LOS_OK;
        goto DONE;
    } else {
        /* map all of the pages */
        LOS_AtomicInc(&newPage->refCounts);
        status = LOS_ArchMmuMap(&space->archMmu, vaddr, newPaddr, 1, region->regionFlags);
        if (status < 0) {
            VM_ERR("failed to map page, status:%d", status);
            status = LOS_ERRNO_VM_MAP_FAILED;
            goto VMM_MAP_FAILED;
        }
    }

    status = LOS_OK;
    goto DONE;
VMM_MAP_FAILED:
    if (newPage != NULL) {
        LOS_PhysPageFree(newPage);
    }
CHECK_FAILED:
    OsFaultTryFixup(frame, excVaddr, &status);
DONE:
    (VOID)LOS_MuxRelease(&space->regionMux);
    return status;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
