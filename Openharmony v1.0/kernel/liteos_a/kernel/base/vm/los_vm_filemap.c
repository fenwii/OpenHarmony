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
 * @defgroup los_vm_filemap vm filemap definition
 * @ingroup kernel
 */

#include "los_vm_filemap.h"
#include "los_vm_page.h"
#include "los_vm_phys.h"
#include "los_vm_common.h"
#include "los_vm_fault.h"
#include "los_process_pri.h"
#include "inode/inode.h"
#include "los_vm_lock.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

STATIC VOID OsPageCacheAdd(LosFilePage *page, struct page_mapping *mapping, VM_OFFSET_T pgoff)
{
    LosFilePage *fpage = NULL;

    LOS_DL_LIST_FOR_EACH_ENTRY(fpage, &mapping->page_list, LosFilePage, node) {
        if (fpage->pgoff > pgoff) {
            LOS_ListTailInsert(&fpage->node, &page->node);
            goto done_add;
        }
    }

    LOS_ListTailInsert(&mapping->page_list, &page->node);

    OsSetPageLRU(page->vmPage);

done_add:
    mapping->nrpages++;
}

VOID OsAddToPageacheLru(LosFilePage *page, struct page_mapping *mapping, VM_OFFSET_T pgoff)
{
    OsPageCacheAdd(page, mapping, pgoff);
    OsLruCacheAdd(page, VM_LRU_ACTIVE_FILE);
}

VOID OsPageCacheDel(LosFilePage *fpage)
{
    /* delete from file cache list */
    LOS_ListDelete(&fpage->node);
    fpage->mapping->nrpages--;

    /* unmap and remove map info */
    if (OsIsPageMapped(fpage)) {
        OsUnmapAllLocked(fpage);
    }

    LOS_PhysPageFree(fpage->vmPage);

    LOS_MemFree(m_aucSysMem0, fpage);
}

VOID OsAddMapInfo(LosFilePage *page, LosArchMmu *archMmu, VADDR_T vaddr)
{
    LosMapInfo *info = NULL;

    info = (LosMapInfo *)LOS_MemAlloc(m_aucSysMem0, sizeof(LosMapInfo));
    if (info == NULL) {
        VM_ERR("OsAddMapInfo alloc memory failed!");
        return;
    }
    info->page = page;
    info->archMmu = archMmu;
    info->vaddr = vaddr;

    LOS_ListAdd(&page->i_mmap, &info->node);
    page->n_maps++;
}

LosMapInfo *OsGetMapInfo(LosFilePage *page, LosArchMmu *archMmu, VADDR_T vaddr)
{
    LosMapInfo *info = NULL;
    LOS_DL_LIST *immap = &page->i_mmap;

    LOS_DL_LIST_FOR_EACH_ENTRY(info, immap, LosMapInfo, node) {
        if ((info->archMmu == archMmu) && (info->vaddr == vaddr) && (info->page == page)) {
            return info;
        }
    }

    return NULL;
}

VOID OsDeletePageCacheLru(LosFilePage *page)
{
    /* delete form lru list */
    OsLruCacheDel(page);
    /* delete from cache lits and free pmm if need */
    OsPageCacheDel(page);
}

STATIC LosFilePage *OsPagecacheGetPageAndFill(struct file *filp, VM_OFFSET_T pgOff, size_t *readSize, VADDR_T *kvaddr)
{
    LosFilePage *page = NULL;
    struct page_mapping *mapping = filp->f_mapping;

    page = OsFindGetEntry(mapping, pgOff);
    if (page != NULL) {
        OsSetPageLocked(page->vmPage);
        OsPageRefIncLocked(page);
        *kvaddr = (VADDR_T)(UINTPTR)OsVmPageToVaddr(page->vmPage);
        *readSize = PAGE_SIZE;
    } else {
        page = OsPageCacheAlloc(mapping, pgOff);
        if (page == NULL) {
            VM_ERR("Failed to alloc a page frame");
            return page;
        }
        OsSetPageLocked(page->vmPage);
        *kvaddr = (VADDR_T)(UINTPTR)OsVmPageToVaddr(page->vmPage);

        file_seek(filp, pgOff << PAGE_SHIFT, SEEK_SET);
        /* "ReadPage" func exists definitely in this procedure */
        *readSize = filp->f_inode->u.i_mops->readpage(filp, (char *)(UINTPTR)*kvaddr, PAGE_SIZE);
        if (*readSize == 0) {
            VM_ERR("read 0 bytes");
            OsCleanPageLocked(page->vmPage);
        }
        OsAddToPageacheLru(page, mapping, pgOff);
    }

    return page;
}

ssize_t OsMappingRead(struct file *filp, char *buf, size_t size)
{
    INT32 ret;
    vaddr_t kvaddr = 0;
    UINT32 intSave;
    struct stat bufStat;
    size_t readSize = 0;
    size_t readTotal = 0;
    size_t readLeft = size;
    LosFilePage *page = NULL;
    VM_OFFSET_T pos = file_seek(filp, 0, SEEK_CUR);
    VM_OFFSET_T pgOff = pos >> PAGE_SHIFT;
    INT32 offInPage = pos % PAGE_SIZE;
    struct page_mapping *mapping = filp->f_mapping;
    INT32 nPages = (ROUNDUP(pos + size, PAGE_SIZE) - ROUNDDOWN(pos, PAGE_SIZE)) >> PAGE_SHIFT;

    ret = stat(filp->f_path, &bufStat);
    if (ret != OK) {
        VM_ERR("Get file size failed. (filepath=%s)", filp->f_path);
        return 0;
    }

    if (pos >= bufStat.st_size) {
        PRINT_INFO("%s filp->f_pos >= bufStat.st_size (pos=%ld, fileSize=%ld)\n", filp->f_path, pos, bufStat.st_size);
        return 0;
    }

    LOS_SpinLockSave(&mapping->list_lock, &intSave);

    for (INT32 i = 0; (i < nPages) && readLeft; i++, pgOff++) {
        page = OsPagecacheGetPageAndFill(filp, pgOff, &readSize, &kvaddr);
        if ((page == NULL) || (readSize == 0)) {
            break;
        }
        if (readSize < PAGE_SIZE) {
            readLeft = readSize;
        }

        readSize = MIN2((PAGE_SIZE - offInPage), readLeft);

        (VOID)memcpy_s((VOID *)buf, readLeft, (char *)kvaddr + offInPage, readSize);
        buf += readSize;
        readLeft -= readSize;
        readTotal += readSize;

        offInPage = 0;

        OsCleanPageLocked(page->vmPage);
    }

    LOS_SpinUnlockRestore(&mapping->list_lock, intSave);
    file_seek(filp, pos + readTotal, SEEK_SET);

    return readTotal;
}

ssize_t OsMappingWrite(struct file *filp, const char *buf, size_t size)
{
    VADDR_T kvaddr;
    UINT32 intSave;
    INT32 writeSize = 0;
    size_t writeLeft = size;
    VM_OFFSET_T pos = file_seek(filp, 0, SEEK_CUR);
    VM_OFFSET_T pgOff = pos >> PAGE_SHIFT;
    INT32 offInPage = pos % PAGE_SIZE;
    LosFilePage *page = NULL;
    struct page_mapping *mapping = filp->f_mapping;
    INT32 nPages = (ROUNDUP(pos + size, PAGE_SIZE) - ROUNDDOWN(pos, PAGE_SIZE)) >> PAGE_SHIFT;

    LOS_SpinLockSave(&mapping->list_lock, &intSave);

    for (INT32 i = 0; i < nPages; i++, pgOff++) {
        page = OsFindGetEntry(mapping, pgOff);
        if (page) {
            kvaddr = (VADDR_T)(UINTPTR)OsVmPageToVaddr(page->vmPage);
            OsSetPageLocked(page->vmPage);
            OsPageRefIncLocked(page);
        } else {
            page = OsPageCacheAlloc(mapping, pgOff);
            if (page == NULL) {
                VM_ERR("Failed to alloc a page frame");
                break;
            }
            kvaddr = (VADDR_T)(UINTPTR)OsVmPageToVaddr(page->vmPage);
            OsAddToPageacheLru(page, mapping, pgOff);
            OsSetPageLocked(page->vmPage);
        }

        writeSize = MIN2((PAGE_SIZE - offInPage), writeLeft);

        (VOID)memcpy_s((char *)(UINTPTR)kvaddr + offInPage, writeLeft, buf, writeSize);
        buf += writeSize;
        writeLeft -= writeSize;

        OsMarkPageDirty(page, NULL, offInPage, writeSize);

        offInPage = 0;

        OsCleanPageLocked(page->vmPage);
    }

    LOS_SpinUnlockRestore(&mapping->list_lock, intSave);

    file_seek(filp, pos + size - writeLeft, SEEK_SET);
    return (size - writeLeft);
}

STATIC VOID OsPageCacheUnmap(LosFilePage *fpage, LosArchMmu *archMmu, VADDR_T vaddr)
{
    UINT32 intSave;
    LosMapInfo *info = NULL;

    LOS_SpinLockSave(&fpage->physSeg->lruLock, &intSave);
    info = OsGetMapInfo(fpage, archMmu, vaddr);
    if (info == NULL) {
        VM_ERR("OsPageCacheUnmap get map info fail!");
    } else {
        OsUnmapPageLocked(fpage, info);
    }
    if (!(OsIsPageMapped(fpage) && ((fpage->flags & VM_MAP_REGION_FLAG_PERM_EXECUTE) ||
        OsIsPageDirty(fpage->vmPage)))) {
        OsPageRefDecNoLock(fpage);
    }

    LOS_SpinUnlockRestore(&fpage->physSeg->lruLock, intSave);
}

VOID OsVmmFileRemove(LosVmMapRegion *region, LosArchMmu *archMmu, VM_OFFSET_T pgoff)
{
    UINT32 intSave;
    vaddr_t vaddr;
    paddr_t paddr = 0;
    struct file *file = NULL;
    struct page_mapping *mapping = NULL;
    LosFilePage *fpage = NULL;
    LosFilePage *tmpPage = NULL;
    LosVmPage *mapPage = NULL;

    if (!LOS_IsRegionFileValid(region) || (region->unTypeData.rf.file->f_mapping == NULL)) {
        return;
    }
    file = region->unTypeData.rf.file;
    mapping = file->f_mapping;
    vaddr = region->range.base + ((UINT32)(pgoff - region->pgOff) << PAGE_SHIFT);

    status_t status = LOS_ArchMmuQuery(archMmu, vaddr, &paddr, NULL);
    if (status != LOS_OK) {
        return;
    }

    mapPage = LOS_VmPageGet(paddr);

    /* is page is in cache list */
    LOS_SpinLockSave(&mapping->list_lock, &intSave);
    fpage = OsFindGetEntry(mapping, pgoff);
    /* no cache or have cache but not map(cow), free it direct */
    if ((fpage == NULL) || (fpage->vmPage != mapPage)) {
        LOS_PhysPageFree(mapPage);
        LOS_ArchMmuUnmap(archMmu, vaddr, 1);
    /* this is a page cache map! */
    } else {
        OsPageCacheUnmap(fpage, archMmu, vaddr);
        if (OsIsPageDirty(fpage->vmPage)) {
            tmpPage = OsDumpDirtyPage(fpage);
        }
    }
    LOS_SpinUnlockRestore(&mapping->list_lock, intSave);

    if (tmpPage) {
        OsDoFlushDirtyPage(tmpPage);
    }
    return;
}

VOID OsMarkPageDirty(LosFilePage *fpage, LosVmMapRegion *region, INT32 off, INT32 len)
{
    if (region != NULL) {
        OsSetPageDirty(fpage->vmPage);
        fpage->dirtyOff = off;
        fpage->dirtyEnd = len;
    } else {
        OsSetPageDirty(fpage->vmPage);
        if ((off + len) > fpage->dirtyEnd) {
            fpage->dirtyEnd = off + len;
        }

        if (off < fpage->dirtyOff) {
            fpage->dirtyOff = off;
        }
    }
}

STATIC UINT32 GetDirtySize(LosFilePage *fpage, struct file *file)
{
    UINT32 fileSize;
    UINT32 dirtyBegin;
    UINT32 dirtyEnd;
    struct stat buf_stat;

    if (stat(file->f_path, &buf_stat) != OK) {
        VM_ERR("FlushDirtyPage get file size failed. (filepath=%s)", file->f_path);
        return 0;
    }

    fileSize = buf_stat.st_size;
    dirtyBegin = ((UINT32)fpage->pgoff << PAGE_SHIFT);
    dirtyEnd = dirtyBegin + PAGE_SIZE;

    if (dirtyBegin >= fileSize) {
        return 0;
    }

    if (dirtyEnd >= fileSize) {
        return fileSize - dirtyBegin;
    }

    return PAGE_SIZE;
}

STATIC INT32 OsFlushDirtyPage(LosFilePage *fpage)
{
    UINT32 ret;
    size_t len;
    char *buff = NULL;
    VM_OFFSET_T oldPos;
    struct file *file = fpage->mapping->host;
    if ((file == NULL) || (file->f_inode == NULL)) {
        VM_ERR("page cache file error");
        return LOS_NOK;
    }

    oldPos = file_seek(file, 0, SEEK_CUR);
    buff = (char *)OsVmPageToVaddr(fpage->vmPage);
    file_seek(file, (((UINT32)fpage->pgoff << PAGE_SHIFT) + fpage->dirtyOff), SEEK_SET);
    len = fpage->dirtyEnd - fpage->dirtyOff;
    len = (len == 0) ? GetDirtySize(fpage, file) : len;
    if (len == 0) {
        OsCleanPageDirty(fpage->vmPage);
        (VOID)file_seek(file, oldPos, SEEK_SET);
        return LOS_OK;
    }

    if (file->f_inode && file->f_inode->u.i_mops->writepage) {
        ret = file->f_inode->u.i_mops->writepage(file, (buff + fpage->dirtyOff), len);
    } else {
        ret = file_write(file, (VOID *)buff, len);
    }
    if (ret <= 0) {
        VM_ERR("WritePage error ret %d", ret);
    }
    ret = (ret <= 0) ? LOS_NOK : LOS_OK;
    OsCleanPageDirty(fpage->vmPage);
    (VOID)file_seek(file, oldPos, SEEK_SET);

    return ret;
}

LosFilePage *OsDumpDirtyPage(LosFilePage *oldFPage)
{
    LosFilePage *newFPage = NULL;

    newFPage = (LosFilePage *)LOS_MemAlloc(m_aucSysMem0, sizeof(LosFilePage));
    if (newFPage == NULL) {
        VM_ERR("Failed to allocate for temp page!");
        return NULL;
    }

    OsCleanPageDirty(oldFPage->vmPage);
    LOS_AtomicInc(&oldFPage->vmPage->refCounts);
    /* no map page cache */
    if (LOS_AtomicRead(&oldFPage->vmPage->refCounts) == 1) {
        LOS_AtomicInc(&oldFPage->vmPage->refCounts);
    }
    (VOID)memcpy_s(newFPage, sizeof(LosFilePage), oldFPage, sizeof(LosFilePage));

    return newFPage;
}

VOID OsDoFlushDirtyPage(LosFilePage *fpage)
{
    if (fpage == NULL) {
        return;
    }
    (VOID)OsFlushDirtyPage(fpage);
    LOS_PhysPageFree(fpage->vmPage);
    LOS_MemFree(m_aucSysMem0, fpage);
}

STATIC VOID OsReleaseFpage(struct page_mapping *mapping, LosFilePage *fpage)
{
    UINT32 intSave;
    UINT32 lruSave;
    SPIN_LOCK_S *lruLock = &fpage->physSeg->lruLock;
    LOS_SpinLockSave(&mapping->list_lock, &intSave);
    LOS_SpinLockSave(lruLock, &lruSave);
    OsCleanPageLocked(fpage->vmPage);
    OsDeletePageCacheLru(fpage);
    LOS_SpinUnlockRestore(lruLock, lruSave);
    LOS_SpinUnlockRestore(&mapping->list_lock, intSave);
}

VOID OsDelMapInfo(LosVmMapRegion *region, LosVmPgFault *vmf, BOOL cleanDirty)
{
    UINT32 intSave;
    LosMapInfo *info = NULL;
    LosFilePage *fpage = NULL;

    if (!LOS_IsRegionFileValid(region) || (region->unTypeData.rf.file->f_mapping == NULL) || (vmf == NULL)) {
        return;
    }

    LOS_SpinLockSave(&region->unTypeData.rf.file->f_mapping->list_lock, &intSave);
    fpage = OsFindGetEntry(region->unTypeData.rf.file->f_mapping, vmf->pgoff);
    if (fpage == NULL) {
        LOS_SpinUnlockRestore(&region->unTypeData.rf.file->f_mapping->list_lock, intSave);
        return;
    }

    if (cleanDirty) {
        OsCleanPageDirty(fpage->vmPage);
    }
    info = OsGetMapInfo(fpage, &region->space->archMmu, (vaddr_t)vmf->vaddr);
    if (info != NULL) {
        fpage->n_maps--;
        LOS_ListDelete(&info->node);
        LOS_AtomicDec(&fpage->vmPage->refCounts);
        LOS_MemFree(m_aucSysMem0, info);
    }
    LOS_SpinUnlockRestore(&region->unTypeData.rf.file->f_mapping->list_lock, intSave);
}

INT32 OsVmmFileFault(LosVmMapRegion *region, LosVmPgFault *vmf)
{
    INT32 ret;
    VM_OFFSET_T oldPos;
    VOID *kvaddr = NULL;

    UINT32 intSave;
    bool newCache = false;
    struct file *file = NULL;
    struct page_mapping *mapping = NULL;
    LosFilePage *fpage = NULL;

    if (!LOS_IsRegionFileValid(region) || (region->unTypeData.rf.file->f_mapping == NULL) || (vmf == NULL)) {
        VM_ERR("Input param is NULL");
        return LOS_NOK;
    }
    file = region->unTypeData.rf.file;
    mapping = file->f_mapping;

    /* get or create a new cache node */
    LOS_SpinLockSave(&mapping->list_lock, &intSave);
    fpage = OsFindGetEntry(mapping, vmf->pgoff);
    if (fpage != NULL) {
        OsPageRefIncLocked(fpage);
    } else {
        fpage = OsPageCacheAlloc(mapping, vmf->pgoff);
        if (fpage == NULL) {
            VM_ERR("Failed to alloc a page frame");
            LOS_SpinUnlockRestore(&mapping->list_lock, intSave);
            return LOS_NOK;
        }
        newCache = true;
    }
    OsSetPageLocked(fpage->vmPage);
    LOS_SpinUnlockRestore(&mapping->list_lock, intSave);
    kvaddr = OsVmPageToVaddr(fpage->vmPage);

    /* read file to new page cache */
    if (newCache) {
        oldPos = file_seek(file, 0, SEEK_CUR);
        file_seek(file, fpage->pgoff << PAGE_SHIFT, SEEK_SET);
        if (file->f_inode && file->f_inode->u.i_mops->readpage) {
            ret = file->f_inode->u.i_mops->readpage(file, (char *)kvaddr, PAGE_SIZE);
        } else {
            ret = file_read(file, kvaddr, PAGE_SIZE);
        }
        file_seek(file, oldPos, SEEK_SET);
        if (ret == 0) {
            VM_ERR("Failed to read from file!");
            OsReleaseFpage(mapping, fpage);
            return LOS_NOK;
        }
        LOS_SpinLockSave(&mapping->list_lock, &intSave);
        OsAddToPageacheLru(fpage, mapping, vmf->pgoff);
        LOS_SpinUnlockRestore(&mapping->list_lock, intSave);
    }

    LOS_SpinLockSave(&mapping->list_lock, &intSave);
    /* cow fault case no need to save mapinfo */
    if (!((vmf->flags & VM_MAP_PF_FLAG_WRITE) && !(region->regionFlags & VM_MAP_REGION_FLAG_SHARED))) {
        OsAddMapInfo(fpage, &region->space->archMmu, (vaddr_t)vmf->vaddr);
        fpage->flags = region->regionFlags;
    }

    /* share page fault, mark the page dirty */
    if ((vmf->flags & VM_MAP_PF_FLAG_WRITE) && (region->regionFlags & VM_MAP_REGION_FLAG_SHARED)) {
        OsMarkPageDirty(fpage, region, 0, 0);
    }

    vmf->pageKVaddr = kvaddr;
    LOS_SpinUnlockRestore(&mapping->list_lock, intSave);
    return LOS_OK;
}

VOID OsFileCacheFlush(struct page_mapping *mapping)
{
    UINT32 intSave;
    UINT32 lruLock;
    LOS_DL_LIST_HEAD(dirtyList);
    LosFilePage *ftemp = NULL;
    LosFilePage *fpage = NULL;

    if (mapping == NULL) {
        return;
    }
    LOS_SpinLockSave(&mapping->list_lock, &intSave);
    LOS_DL_LIST_FOR_EACH_ENTRY(fpage, &mapping->page_list, LosFilePage, node) {
        LOS_SpinLockSave(&fpage->physSeg->lruLock, &lruLock);
        if (OsIsPageDirty(fpage->vmPage)) {
            ftemp = OsDumpDirtyPage(fpage);
            if (ftemp != NULL) {
                LOS_ListTailInsert(&dirtyList, &ftemp->node);
            }
        }
        LOS_SpinUnlockRestore(&fpage->physSeg->lruLock, lruLock);
    }
    LOS_SpinUnlockRestore(&mapping->list_lock, intSave);

    LOS_DL_LIST_FOR_EACH_ENTRY_SAFE(fpage, ftemp, &dirtyList, LosFilePage, node) {
        OsDoFlushDirtyPage(fpage);
    }
}

VOID OsFileCacheRemove(struct page_mapping *mapping)
{
    UINT32 intSave;
    UINT32 lruSave;
    SPIN_LOCK_S *lruLock = NULL;
    LOS_DL_LIST_HEAD(dirtyList);
    LosFilePage *ftemp = NULL;
    LosFilePage *fpage = NULL;
    LosFilePage *fnext = NULL;

    LOS_SpinLockSave(&mapping->list_lock, &intSave);
    LOS_DL_LIST_FOR_EACH_ENTRY_SAFE(fpage, fnext, &mapping->page_list, LosFilePage, node) {
        lruLock = &fpage->physSeg->lruLock;
        LOS_SpinLockSave(lruLock, &lruSave);
        if (OsIsPageDirty(fpage->vmPage)) {
            ftemp = OsDumpDirtyPage(fpage);
            if (ftemp != NULL) {
                LOS_ListTailInsert(&dirtyList, &ftemp->node);
            }
        }

        OsDeletePageCacheLru(fpage);
        LOS_SpinUnlockRestore(lruLock, lruSave);
    }
    LOS_SpinUnlockRestore(&mapping->list_lock, intSave);

    LOS_DL_LIST_FOR_EACH_ENTRY_SAFE(fpage, fnext, &dirtyList, LosFilePage, node) {
        OsDoFlushDirtyPage(fpage);
    }
}

LosVmFileOps g_commVmOps = {
    .open = NULL,
    .close = NULL,
    .fault = OsVmmFileFault,
    .remove = OsVmmFileRemove,
};

INT32 OsVfsFileMmap(struct file *filep, LosVmMapRegion *region)
{
    region->unTypeData.rf.vmFOps = &g_commVmOps;
    region->unTypeData.rf.file = filep;
    region->unTypeData.rf.fileMagic = filep->f_magicnum;
    return ENOERR;
}

STATUS_T OsNamedMMap(struct file *filep, LosVmMapRegion *region)
{
    struct inode *inodePtr = NULL;
    if (filep == NULL) {
        return LOS_ERRNO_VM_MAP_FAILED;
    }
    inodePtr = filep->f_inode;
    if (inodePtr == NULL) {
        return LOS_ERRNO_VM_MAP_FAILED;
    }
    if (INODE_IS_MOUNTPT(inodePtr)) {
        if (inodePtr->u.i_mops->mmap) {
            LOS_SetRegionTypeFile(region);
            return inodePtr->u.i_mops->mmap(filep, region);
        } else {
            VM_ERR("file mmap not support");
            return LOS_ERRNO_VM_MAP_FAILED;
        }
    } else if (INODE_IS_DRIVER(inodePtr)) {
        if (inodePtr->u.i_ops->mmap) {
            LOS_SetRegionTypeDev(region);
            return inodePtr->u.i_ops->mmap(filep, region);
        } else {
            VM_ERR("dev mmap not support");
            return LOS_ERRNO_VM_MAP_FAILED;
        }
    } else {
        VM_ERR("mmap file type unknown");
        return LOS_ERRNO_VM_MAP_FAILED;
    }
}

LosFilePage *OsFindGetEntry(struct page_mapping *mapping, VM_OFFSET_T pgoff)
{
    LosFilePage *fpage = NULL;

    LOS_DL_LIST_FOR_EACH_ENTRY(fpage, &mapping->page_list, LosFilePage, node) {
        if (fpage->pgoff == pgoff) {
            return fpage;
        }

        if (fpage->pgoff > pgoff) {
            break;
        }
    }

    return NULL;
}

/* need mutex & change memory to dma zone. */
LosFilePage *OsPageCacheAlloc(struct page_mapping *mapping, VM_OFFSET_T pgoff)
{
    VOID *kvaddr = NULL;
    LosVmPhysSeg *physSeg = NULL;
    LosVmPage *vmPage = NULL;
    LosFilePage *fpage = NULL;

    vmPage = LOS_PhysPageAlloc();
    if (vmPage == NULL) {
        VM_ERR("alloc vm page failed");
        return NULL;
    }
    physSeg = OsVmPhysSegGet(vmPage);
    kvaddr = OsVmPageToVaddr(vmPage);
    if ((physSeg == NULL) || (kvaddr == NULL)) {
        LOS_PhysPageFree(vmPage);
        VM_ERR("alloc vm page failed!");
        return NULL;
    }

    fpage = (LosFilePage *)LOS_MemAlloc(m_aucSysMem0, sizeof(LosFilePage));
    if (fpage == NULL) {
        LOS_PhysPageFree(vmPage);
        VM_ERR("Failed to allocate for page!");
        return NULL;
    }

    (VOID)memset_s((VOID *)fpage, sizeof(LosFilePage), 0, sizeof(LosFilePage));

    LOS_ListInit(&fpage->i_mmap);
    LOS_ListInit(&fpage->node);
    LOS_ListInit(&fpage->lru);
    fpage->n_maps = 0;
    fpage->dirtyOff = PAGE_SIZE;
    fpage->dirtyEnd = 0;
    fpage->physSeg = physSeg;
    fpage->vmPage = vmPage;
    fpage->mapping = mapping;
    fpage->pgoff = pgoff;
    (VOID)memset_s(kvaddr, PAGE_SIZE, 0, PAGE_SIZE);

    return fpage;
}

#ifdef LOSCFG_FS_VFS
VOID OsVmmFileRegionFree(struct file *filep, LosProcessCB *processCB)
{
    int ret;
    LosVmSpace *space = NULL;
    LosVmMapRegion *region = NULL;
    LosRbNode *pstRbNode = NULL;
    LosRbNode *pstRbNodeTmp = NULL;

    if (processCB == NULL) {
        processCB = OsCurrProcessGet();
    }

    space = processCB->vmSpace;
    if (space != NULL) {
        /* free the regions associated with filep */
        RB_SCAN_SAFE(&space->regionRbTree, pstRbNode, pstRbNodeTmp)
            region = (LosVmMapRegion *)pstRbNode;
            if (LOS_IsRegionFileValid(region)) {
                if (region->unTypeData.rf.file != filep) {
                    continue;
                }
                ret = LOS_RegionFree(space, region);
                if (ret != LOS_OK) {
                    VM_ERR("free region error, space %p, region %p", space, region);
                }
            }
        RB_SCAN_SAFE_END(&space->regionRbTree, pstRbNode, pstRbNodeTmp)
    }
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
