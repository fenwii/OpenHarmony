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
 * @defgroup los_vm_map vm mapping management
 * @ingroup kernel
 */

#ifndef __LOS_VM_MAP_H__
#define __LOS_VM_MAP_H__

#include "los_typedef.h"
#include "los_arch_mmu.h"
#include "los_rbtree.h"
#include "los_vm_syscall.h"
#include "los_vm_zone.h"
#include "los_vm_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef struct VmMapRange {
    VADDR_T             base;           /**< vm region base addr */
    UINT32              size;           /**< vm region size */
} LosVmMapRange;

struct VmMapRegion;
typedef struct VmMapRegion LosVmMapRegion;
struct VmFileOps;
typedef struct VmFileOps LosVmFileOps;
struct VmSpace;
typedef struct VmSpace LosVmSpace;

typedef struct VmFault {
    UINT32          flags;              /* FAULT_FLAG_xxx flags */
    unsigned long   pgoff;              /* Logical page offset based on region */
    VADDR_T         vaddr;              /* Faulting virtual address */
    VADDR_T         *pageKVaddr;        /* KVaddr of pagefault's vm page's paddr */
} LosVmPgFault;

struct VmFileOps {
    void (*open)(struct VmMapRegion *region);
    void (*close)(struct VmMapRegion *region);
    int  (*fault)(struct VmMapRegion *region, LosVmPgFault *pageFault);
    void (*remove)(struct VmMapRegion *region, LosArchMmu *archMmu, VM_OFFSET_T offset);
};

struct VmMapRegion {
    LosRbNode           rbNode;         /**< region red-black tree node */
    LosVmSpace          *space;
    LOS_DL_LIST         node;           /**< region dl list */
    LosVmMapRange       range;          /**< region address range */
    VM_OFFSET_T         pgOff;          /**< region page offset to file */
    UINT32              regionFlags;   /**< region flags: cow, user_wired */
    UINT32              shmid;          /**< shmid about shared region */
    UINT8               protectFlags;   /**< vm region protect flags: PROT_READ, PROT_WRITE, */
    UINT8               forkFlags;      /**< vm space fork flags: COPY, ZERO, */
    UINT8               regionType;     /**< vm region type: ANON, FILE, DEV */
    union {
        struct VmRegionFile {
            unsigned int fileMagic;
            struct file *file;
            const LosVmFileOps *vmFOps;
        } rf;
        struct VmRegionAnon {
            LOS_DL_LIST  node;          /**< region LosVmPage list */
        } ra;
        struct VmRegionDev {
            LOS_DL_LIST  node;          /**< region LosVmPage list */
            const LosVmFileOps *vmFOps;
        } rd;
    } unTypeData;
};

typedef struct VmSpace {
    LOS_DL_LIST         node;           /**< vm space dl list */
    LOS_DL_LIST         regions;        /**< region dl list */
    LosRbTree           regionRbTree;   /**< region red-black tree root */
    LosMux              regionMux;      /**< region list mutex lock */
    VADDR_T             base;           /**< vm space base addr */
    UINT32              size;           /**< vm space size */
    VADDR_T             heapBase;       /**< vm space heap base address */
    VADDR_T             heapNow;        /**< vm space heap base now */
    LosVmMapRegion      *heap;          /**< heap region */
    VADDR_T             mapBase;        /**< vm space mapping area base */
    UINT32              mapSize;        /**< vm space mapping area size */
    LosArchMmu          archMmu;        /**< vm mapping physical memory */
#ifdef LOSCFG_DRIVERS_TZDRIVER
    VADDR_T             codeStart;      /**< user process code area start */
    VADDR_T             codeEnd;        /**< user process code area end */
#endif
} LosVmSpace;

#define     VM_MAP_REGION_TYPE_NONE                 (0x0)
#define     VM_MAP_REGION_TYPE_ANON                 (0x1)
#define     VM_MAP_REGION_TYPE_FILE                 (0x2)
#define     VM_MAP_REGION_TYPE_DEV                  (0x4)
#define     VM_MAP_REGION_TYPE_MASK                 (0x7)

/* the high 8 bits(24~31) should reserved, shm will use it */
#define     VM_MAP_REGION_FLAG_CACHED               (0<<0)
#define     VM_MAP_REGION_FLAG_UNCACHED             (1<<0)
#define     VM_MAP_REGION_FLAG_UNCACHED_DEVICE      (2<<0) /* only exists on some arches, otherwise UNCACHED */
#define     VM_MAP_REGION_FLAG_WRITE_COMBINING      (3<<0) /* only exists on some arches, otherwise UNCACHED */
#define     VM_MAP_REGION_FLAG_CACHE_MASK           (3<<0)
#define     VM_MAP_REGION_FLAG_PERM_USER            (1<<2)
#define     VM_MAP_REGION_FLAG_PERM_READ            (1<<3)
#define     VM_MAP_REGION_FLAG_PERM_WRITE           (1<<4)
#define     VM_MAP_REGION_FLAG_PERM_EXECUTE         (1<<5)
#define     VM_MAP_REGION_FLAG_PROT_MASK            (0xF<<2)
#define     VM_MAP_REGION_FLAG_NS                   (1<<6) /* NON-SECURE */
#define     VM_MAP_REGION_FLAG_SHARED               (1<<7)
#define     VM_MAP_REGION_FLAG_PRIVATE              (1<<8)
#define     VM_MAP_REGION_FLAG_FLAG_MASK            (3<<7)
#define     VM_MAP_REGION_FLAG_STACK                (1<<9)
#define     VM_MAP_REGION_FLAG_HEAP                 (1<<10)
#define     VM_MAP_REGION_FLAG_DATA                 (1<<11)
#define     VM_MAP_REGION_FLAG_TEXT                 (1<<12)
#define     VM_MAP_REGION_FLAG_BSS                  (1<<13)
#define     VM_MAP_REGION_FLAG_VDSO                 (1<<14)
#define     VM_MAP_REGION_FLAG_MMAP                 (1<<15)
#define     VM_MAP_REGION_FLAG_SHM                  (1<<16)
#define     VM_MAP_REGION_FLAG_INVALID              (1<<17) /* indicates that flags are not specified */

STATIC INLINE UINT32 OsCvtProtFlagsToRegionFlags(unsigned long prot, unsigned long flags)
{
    UINT32 regionFlags = 0;

    regionFlags |= VM_MAP_REGION_FLAG_PERM_USER;
    regionFlags |= (prot & PROT_READ) ? VM_MAP_REGION_FLAG_PERM_READ : 0;
    regionFlags |= (prot & PROT_WRITE) ? VM_MAP_REGION_FLAG_PERM_WRITE : 0;
    regionFlags |= (prot & PROT_EXEC) ? VM_MAP_REGION_FLAG_PERM_EXECUTE : 0;
    regionFlags |= (flags & MAP_SHARED) ? VM_MAP_REGION_FLAG_SHARED : 0;
    regionFlags |= (flags & MAP_PRIVATE) ? VM_MAP_REGION_FLAG_PRIVATE : 0;

    return regionFlags;
}

STATIC INLINE BOOL LOS_IsKernelAddress(VADDR_T vaddr)
{
    return ((vaddr >= (VADDR_T)KERNEL_ASPACE_BASE) &&
            (vaddr <= ((VADDR_T)KERNEL_ASPACE_BASE + ((VADDR_T)KERNEL_ASPACE_SIZE - 1))));
}

STATIC INLINE BOOL LOS_IsKernelAddressRange(VADDR_T vaddr, size_t len)
{
    return (vaddr + len > vaddr) && LOS_IsKernelAddress(vaddr) && (LOS_IsKernelAddress(vaddr + len - 1));
}

STATIC INLINE VADDR_T LOS_RegionEndAddr(LosVmMapRegion *region)
{
    return (region->range.base + region->range.size - 1);
}

STATIC INLINE size_t LOS_RegionSize(VADDR_T start, VADDR_T end)
{
    return (end - start + 1);
}

STATIC INLINE BOOL LOS_IsRegionTypeFile(LosVmMapRegion* region)
{
    return region->regionType == VM_MAP_REGION_TYPE_FILE;
}

STATIC INLINE BOOL LOS_IsRegionPermUserReadOnly(LosVmMapRegion* region)
{
    return ((region->regionFlags & VM_MAP_REGION_FLAG_PROT_MASK) ==
            (VM_MAP_REGION_FLAG_PERM_USER | VM_MAP_REGION_FLAG_PERM_READ));
}

STATIC INLINE BOOL LOS_IsRegionFlagPrivateOnly(LosVmMapRegion* region)
{
    return ((region->regionFlags & VM_MAP_REGION_FLAG_FLAG_MASK) == VM_MAP_REGION_FLAG_PRIVATE);
}

STATIC INLINE VOID LOS_SetRegionTypeFile(LosVmMapRegion* region)
{
    region->regionType = VM_MAP_REGION_TYPE_FILE;
}

STATIC INLINE BOOL LOS_IsRegionTypeDev(LosVmMapRegion* region)
{
    return region->regionType == VM_MAP_REGION_TYPE_DEV;
}

STATIC INLINE VOID LOS_SetRegionTypeDev(LosVmMapRegion* region)
{
    region->regionType = VM_MAP_REGION_TYPE_DEV;
}

STATIC INLINE BOOL LOS_IsRegionTypeAnon(LosVmMapRegion* region)
{
    return region->regionType == VM_MAP_REGION_TYPE_ANON;
}

STATIC INLINE VOID LOS_SetRegionTypeAnon(LosVmMapRegion* region)
{
    region->regionType = VM_MAP_REGION_TYPE_ANON;
}

STATIC INLINE BOOL LOS_IsUserAddress(VADDR_T vaddr)
{
    return ((vaddr >= USER_ASPACE_BASE) &&
            (vaddr <= (USER_ASPACE_BASE + (USER_ASPACE_SIZE - 1))));
}

STATIC INLINE BOOL LOS_IsUserAddressRange(VADDR_T vaddr, size_t len)
{
    return (vaddr + len > vaddr) && LOS_IsUserAddress(vaddr) && (LOS_IsUserAddress(vaddr + len - 1));
}


STATIC INLINE BOOL LOS_IsVmallocAddress(VADDR_T vaddr)
{
    return ((vaddr >= VMALLOC_START) &&
            (vaddr <= (VMALLOC_START + (VMALLOC_SIZE - 1))));
}

STATIC INLINE BOOL OsIsVmRegionEmpty(LosVmSpace *vmSpace)
{
    if (vmSpace->regionRbTree.ulNodes == 0) {
        return TRUE;
    }
    return FALSE;
}

LosVmSpace *LOS_GetKVmSpace(VOID);
LOS_DL_LIST *LOS_GetVmSpaceList(VOID);
LosVmSpace *LOS_GetVmallocSpace(VOID);
VOID OsInitMappingStartUp(VOID);
VOID OsKSpaceInit(VOID);
BOOL LOS_IsRangeInSpace(const LosVmSpace *space, VADDR_T vaddr, size_t size);
STATUS_T LOS_VmSpaceReserve(LosVmSpace *space, size_t size, VADDR_T vaddr);
LosVmSpace *LOS_GetKVmSpace(VOID);
INT32 OsUserHeapFree(LosVmSpace *vmSpace, VADDR_T addr, size_t len);
VADDR_T OsAllocRange(LosVmSpace *vmSpace, size_t len);
VADDR_T OsAllocSpecificRange(LosVmSpace *vmSpace, VADDR_T vaddr, size_t len);
LosVmMapRegion *OsCreateRegion(VADDR_T vaddr, size_t len, UINT32 regionFlags, unsigned long offset);
BOOL OsInsertRegion(LosRbTree *regionRbTree, LosVmMapRegion *region);
LosVmSpace *LOS_SpaceGet(VADDR_T vaddr);
BOOL LOS_IsRegionFileValid(LosVmMapRegion *region);
LosVmMapRegion *LOS_RegionRangeFind(LosVmSpace *vmSpace, VADDR_T addr, size_t len);
LosVmMapRegion *LOS_RegionFind(LosVmSpace *vmSpace, VADDR_T addr);
PADDR_T LOS_PaddrQuery(VOID *vaddr);
LosVmMapRegion *LOS_RegionAlloc(LosVmSpace *vmSpace, VADDR_T vaddr, size_t len, UINT32 regionFlags, VM_OFFSET_T pgoff);
STATUS_T OsRegionsRemove(LosVmSpace *space, VADDR_T vaddr, size_t size);
STATUS_T OsVmRegionAdjust(LosVmSpace *space, VADDR_T vaddr, size_t size);
LosVmMapRegion *OsVmRegionDup(LosVmSpace *space, LosVmMapRegion *oldRegion, VADDR_T vaddr, size_t size);
STATUS_T OsIsRegionCanExpand(LosVmSpace *space, LosVmMapRegion *region, size_t size);
STATUS_T LOS_RegionFree(LosVmSpace *space, LosVmMapRegion *region);
STATUS_T LOS_VmSpaceFree(LosVmSpace *space);
STATUS_T LOS_VaddrToPaddrMmap(LosVmSpace *space, VADDR_T vaddr, PADDR_T paddr, size_t len, UINT32 flags);
BOOL OsUserVmSpaceInit(LosVmSpace *vmSpace, VADDR_T *virtTtb);
STATUS_T LOS_VmSpaceClone(LosVmSpace *oldVmSpace, LosVmSpace *newVmSpace);
STATUS_T LOS_UserSpaceVmAlloc(LosVmSpace *space, size_t size, VOID **ptr, UINT8 align_log2, UINT32 regionFlags);
LosMux *OsGVmSpaceMuxGet(VOID);
STATUS_T OsUnMMap(LosVmSpace *space, VADDR_T addr, size_t size);
/**
 * thread safety
 * it is used to malloc continuous virtual memory, no sure for continuous physical memory.
 */
VOID *LOS_VMalloc(size_t size);
VOID LOS_VFree(const VOID *addr);

/**
 * thread safety
 * these is used to malloc or free kernel memory.
 * when the size is large and close to multiples of pages,
 * will alloc pmm pages, otherwise alloc bestfit memory.
 */
VOID *LOS_KernelMalloc(UINT32 size);
VOID *LOS_KernelMallocAlign(UINT32 size, UINT32 boundary);
VOID *LOS_KernelRealloc(VOID *ptr, UINT32 size);
VOID LOS_KernelFree(VOID *ptr);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __LOS_VM_MAP_H__ */

