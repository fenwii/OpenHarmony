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
 * @defgroup los_slab Slab
 * @ingroup kernel
 */

#ifndef _LOS_SLAB_PRI_H
#define _LOS_SLAB_PRI_H

#include "los_base.h"
#include "los_slab.h"
#include <los_typedef.h>

typedef struct tagLosSlabStatus {
    UINT32 totalSize;
    UINT32 usedSize;
    UINT32 freeSize;
    UINT32 allocCount;
    UINT32 freeCount;
} LosSlabStatus;

typedef struct tagOsSlabBlockNode {
    UINT16 magic;
    UINT8  blkSz;
    UINT8  recordId;
} OsSlabBlockNode;

struct AtomicBitset {
    UINT32 numBits;
    UINT32 words[0];
};

typedef struct tagOsSlabAllocator {
    UINT32 itemSz;
    UINT8 *dataChunks;
    struct AtomicBitset *bitset;
} OsSlabAllocator;

typedef struct tagOsSlabMem {
    UINT32 blkSz;
    UINT32 blkCnt;
    UINT32 blkUsedCnt;
    OsSlabAllocator *alloc;
} OsSlabMem;

struct LosSlabControlHeader {
    OsSlabMem slabClass[SLAB_MEM_COUNT];
};

#define OS_SLAB_MAGIC 0xdede
#define OS_SLAB_BLOCK_HEAD_GET(ptr)                ((OsSlabBlockNode *)(VOID *)((UINT8 *)(ptr) - \
                                                      sizeof(OsSlabBlockNode)))
#define OS_SLAB_BLOCK_MAGIC_SET(slabNode)          (((OsSlabBlockNode *)(slabNode))->magic = (UINT16)OS_SLAB_MAGIC)
#define OS_SLAB_BLOCK_MAGIC_GET(slabNode)          (((OsSlabBlockNode *)(slabNode))->magic)
#define OS_SLAB_BLOCK_SIZE_SET(slabNode, size)     (((OsSlabBlockNode *)(slabNode))->blkSz = (size))
#define OS_SLAB_BLOCK_SIZE_GET(slabNode)           (((OsSlabBlockNode *)(slabNode))->blkSz)
#define OS_SLAB_BLOCK_ID_SET(slabNode, id)         (((OsSlabBlockNode *)(slabNode))->recordId = (id))
#define OS_SLAB_BLOCK_ID_GET(slabNode)             (((OsSlabBlockNode *)(slabNode))->recordId)
#define OS_ALLOC_FROM_SLAB_CHECK(slabNode)         (((OsSlabBlockNode *)(slabNode))->magic == (UINT16)OS_SLAB_MAGIC)

#define ATOMIC_BITSET_SZ(numbits)   (sizeof(struct AtomicBitset) + ((numbits) + 31) / 8)

/**
 * @ingroup  los_slab
 * @brief Initialization atomic bitset.
 *
 * @par Description:
 * This API is used to initialization atomic bitset.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  set            [IN/OUT] Type #AtomicBitset *   Atomic bitset.
 * @param  numBits        [IN] Type #UINT32   Bits number.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsSlabAllocatorDestroy
 */
VOID OsAtomicBitsetInit(struct AtomicBitset *set, UINT32 numBits);

/**
 * @ingroup  los_slab
 * @brief Get atomic bitset number.
 *
 * @par Description:
 * This API is used to get atomic bitset number.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  set            [IN] Type #AtomicBitset *   Atomic bitset.
 *
 * @retval UINT32   Atomic bitset number.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsSlabAllocatorDestroy
 */
UINT32 OsAtomicBitsetGetNumBits(const struct AtomicBitset *set);

/**
 * @ingroup  los_slab
 * @brief Get atomic bitset bit.
 *
 * @par Description:
 * This API is used to get atomic bitset bit.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  set              [IN] Type #AtomicBitset *   Atomic bitset.
 * @param  num              [IN] Type #UINT32   Bit number.
 *
 * @retval BOOL  success or failed
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsSlabAllocatorDestroy
 */
BOOL OsAtomicBitsetGetBit(const struct AtomicBitset *set, UINT32 num);

/**
 * @ingroup  los_slab
 * @brief Clear the atomic bitset bit.
 *
 * @par Description:
 * This API is used to clear the atomic bitset bit.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  set              [IN] Type #AtomicBitset *   Atomic bitset.
 * @param  num              [IN] Type #UINT32   Bit number.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsSlabAllocatorDestroy
 */
VOID OsAtomicBitsetClearBit(struct AtomicBitset *set, UINT32 num);

/**
 * @ingroup  los_slab
 * @brief Clear and set the atomic bitset bit.
 *
 * @par Description:
 * This API is used to clear and set the atomic bitset bit.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  set         [IN] Type #AtomicBitset *   Atomic bitset.
 *
 * @retval INT32   The address of the first available bit.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsSlabAllocatorDestroy
 */
INT32 OsAtomicBitsetFindClearAndSet(struct AtomicBitset *set);

/**
 * @ingroup  los_slab
 * @brief Change the order of the output idx of OsAtomicBitsetFindClearAndSet to order of natural numbers.
 *
 * @par Description:
 * This API is used to change the order of the output idx of OsAtomicBitsetFindClearAndSet to order of natural numbers.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  bitset            [IN] Type #AtomicBitset *   Atomic bitset.
 * @param  index             [IN] Type #INT32   index.
 *
 * @retval INT32   Index to natural numbers.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsSlabAllocatorDestroy
 */
INT32 OsAtomicBitsetIdxChgToNatural(struct AtomicBitset *bitset, INT32 index);

/**
 * @ingroup  los_slab
 * @brief Judgment the atomic bitset is empty.
 *
 * @par Description:
 * This API is used to judgment the atomic bitset is empty.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  bitset         [IN] Type #AtomicBitset *   Atomic bitset.
 *
 * @retval BOOL   Judgment result.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsSlabAllocatorDestroy
 */
BOOL OsAtomicBitsetEmpty(struct AtomicBitset *bitset);

// thread/interrupt safe. allocations will not fail if space exists. even in interrupts.
// itemAlign over 4 will not be guaranteed since the heap does not hand out chunks with that kind of alignment
/**
 * @ingroup  los_slab
 * @brief create a new slab allocator.
 *
 * @par Description:
 * This API is used to create a new slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool       [IN] Pointer to the memory pool that contains the memory block to be allocated.
 * @param  itemSz     [IN] The size of one slab page.
 * @param  itemAlign  [IN] Type alignment, 4 byte-aligned, 8 byte-aligned, etc.
 * @param  numItems   [IN] The number of slab page.
 *
 * @retval #OS_SLAB_ALLOCATOR*        The address of slab allocator.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsSlabAllocatorDestroy
 */
OsSlabAllocator *OsSlabAllocatorNew(VOID *pool, UINT32 itemSz, UINT32 itemAlign, UINT32 numItems);

/**
 * @ingroup  los_slab
 * @brief Destroy a slab allocator.
 *
 * @par Description:
 * This API is used to Destroy a slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool          [IN] Pointer to the memory pool that contains the memory block to be allocated.
 * @param  allocator     [IN] a slab allocator.
 *
 * @retval #VOID
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsSlabAllocatorNew
 */
VOID OsSlabAllocatorDestroy(VOID *pool, OsSlabAllocator *allocator);

/**
 * @ingroup  los_slab
 * @brief Allocate a slab page form allocator.
 *
 * @par Description:
 * This API is used to allocate a slab page form allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  allocator     [IN] a slab allocator.
 *
 * @retval #VOID*        return a slab page.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsSlabAllocatorFree
 */
VOID* OsSlabAllocatorAlloc(OsSlabAllocator *allocator);

/**
 * @ingroup  los_slab
 * @brief Free a slab page.
 *
 * @par Description:
 * This API is used to free a slab page.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  allocator     [IN] a slab allocator.
 * @param  ptr           [IN] a slab page.
 *
 * @retval #FALSE        Failed to free a slab page.
 * @retval #TRUE         Succees to free a slab page.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_SlabAllocatorAlloc
 */
BOOL OsSlabAllocatorFree(OsSlabAllocator *allocator, VOID* ptr);

/**
 * @ingroup  los_slab
 * @brief Get a slab page index with judgment.
 *
 * @par Description:
 * This API is used to get a slab page index with judgment.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  allocator     [IN] a slab allocator.
 * @param  idx           [IN] index
 *
 * @retval  VOID *
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
/* -> pointer or NULL if that slot is empty may be not int-safe. YMMV */
VOID* OsSlabAllocatorGetNth(OsSlabAllocator *allocator, UINT32 idx);

/**
 * @ingroup  los_slab
 * @brief Get a slab page index without judgment.
 *
 * @par Description:
 * This API is used to get a slab page index without judgment.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  allocator     [IN] a slab allocator.
 * @param  idx           [IN] index
 *
 * @retval  VOID *
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
VOID* OsSlabAllocatorGetIdxP(OsSlabAllocator *allocator, UINT32 idx);

/**
 * @ingroup  los_slab
 * @brief Get the index of slab page in slab allocator.
 *
 * @par Description:
 * This API is used to get the index of slab page in slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  allocator     [IN] a slab allocator.
 * @param  ptr           [IN] a slab page.
 *
 * @retval #-1           Illegal index .
 * @retval #UINT32       Succees to get index.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
UINT32 OsSlabAllocatorGetIndex(OsSlabAllocator *allocator, VOID *ptr);

/**
 * @ingroup  los_slab
 * @brief Get the number of slab page.
 *
 * @par Description:
 * This API is used to get the number of slab page.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  allocator     [IN] a slab allocator.
 *
 * @retval #UINT32       Succees to get the number of slab page.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
UINT32 OsSlabAllocatorGetNumItems(OsSlabAllocator *allocator);

/**
 * @ingroup  los_slab
 * @brief Check the slab allocator.
 *
 * @par Description:
 * This API is used to check the slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  allocator     [IN] a slab allocator.
 *
 * @retval #FALSE        The slab allocator is already used.
 * @retval #TRUE         The slab allocator is not used.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
BOOL OsSlabAllocatorEmpty(OsSlabAllocator *allocator);

/**
 * @ingroup  los_slab
 * @brief Get the used number of slab page in slab allocator.
 *
 * @par Description:
 * This API is used to get the used number of slab page in slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  allocator      [IN] a slab allocator.
 *
 * @retval #UINT32        The used number of slab page in slab allocator.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
UINT32 OsSlabAllocatorGetUsedItemCnt(OsSlabAllocator *allocator);

/**
 * @ingroup  los_slab
 * @brief Get the info of slab allocator.
 *
 * @par Description:
 * This API is used to get the info of slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  allocator    [IN]  a slab allocator.
 * @param  itemSize     [OUT] a slab page size.
 * @param  itemCnt      [OUT] a slab page num.
 * @param  curUsage     [OUT] a used number of slab page.
 *
 * @retval #VOID
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
VOID OsSlabAllocatorGetSlabInfo(OsSlabAllocator *allocator, UINT32 *itemSize, UINT32 *itemCnt, UINT32 *curUsage);

/**
 * @ingroup  los_slab
 * @brief init slab allocator.
 *
 * @par Description:
 * This API is used to init slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool    [IN] Pointer to the memory pool that contains the memory block to be allocated.
 *
 * @retval BOOL
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern BOOL OsSlabMemInit(VOID *pool);

/**
 * @ingroup  los_slab
 * @brief alloc mem by slab allocator.
 *
 * @par Description:
 * This API is used to alloc mem by slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool     [IN] Pointer to the memory pool that contains the memory block to be allocated.
 * @param  sz       [IN] Size of mem to alloc
 *
 * @retval VOID *  The address of alloced mem or NULL.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern VOID *OsSlabMemAlloc(VOID *pool, UINT32 sz);

/**
 * @ingroup  los_slab
 * @brief free mem by slab allocator.
 *
 * @par Description:
 * This API is used to free mem by slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool     [IN] Pointer to the memory pool that contains the memory block to be allocated.
 * @param  ptr      [IN] Pointer to the memory that to be free
 *
 * @retval BOOL   success or failed
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern BOOL OsSlabMemFree(VOID *pool, VOID *ptr);

/**
 * @ingroup  los_slab
 * @brief deinit slab allocator.
 *
 * @par Description:
 * This API is used to deinit slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool    [IN] Pointer to the memory pool that contains the memory block to be allocated.
 *
 * @retval VOID
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern VOID OsSlabMemDeinit(VOID *pool);

/**
 * @ingroup  los_slab
 * @brief Check slab allocator.
 *
 * @par Description:
 * This API is used to check slab allocator.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  allocator    [IN] a slab allocator.
 * @param  ptr          [IN] Slab node.
 *
 * @retval VOID
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern BOOL OsSlabAllocatorCheck(OsSlabAllocator *allocator, VOID *ptr);

/**
 * @ingroup  los_slab
 * @brief Get SlabCtrlHdr.
 *
 * @par Description:
 * This API is used to get SlabCtrlHdr.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool    [IN] Pointer to the memory pool that contains the memory block to be allocated.
 *
 * @retval VOID
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID *OsSlabCtrlHdrGet(const VOID *pool);

/**
 * @ingroup  los_slab
 * @brief Check the slab memory.
 *
 * @par Description:
 * This API is used to check the slab memory.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool    [IN] Pointer to the memory pool that contains the memory block to be allocated.
 * @param  ptr     [IN] Slab block head.
 *
 * @retval UINT32   block size.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsSlabMemCheck(VOID *pool, VOID *ptr);

/**
 * @ingroup  los_slab
 * @brief Get the slab status.
 *
 * @par Description:
 * This API is used to get the slab status.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool         [IN] Pointer to the memory pool that contains the memory block to be allocated.
 * @param  status       [IN/OUT] Slab block status.
 *
 * @retval UINT32   Get status result.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsSlabStatisticsGet(VOID *pool, LosSlabStatus *status);

/**
 * @ingroup  los_slab
 * @brief Get the max free block size.
 *
 * @par Description:
 * This API is used to get the max free block size.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool         [IN] Pointer to the memory pool that contains the memory block to be allocated.
 *
 * @retval UINT32   Max free block size.
 * @par Dependency:
 * <ul><li>los_slab_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsSlabGetMaxFreeBlkSize(VOID *pool);

#endif

