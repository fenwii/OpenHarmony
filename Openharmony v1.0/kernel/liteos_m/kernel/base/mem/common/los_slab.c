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

#include <string.h>
#include <stdint.h>
#include "securec.h"
#include "los_slab_pri.h"
#include "los_heap_pri.h"

#define LOW_BITS_MASK                     31
#define NUM_BITS_IN_ONE_BYTE              32
#define NUMBITS_TO_NUMBYTES(numBits)      (((numBits) + LOW_BITS_MASK) / 8)

VOID OsAtomicBitsetInit(struct AtomicBitset *set, UINT32 numBits)
{
    set->numBits = numBits;
    // Ignore the return code when matching CSEC rule 6.6(2).
    (VOID)memset_s(set->words, NUMBITS_TO_NUMBYTES(numBits), 0, NUMBITS_TO_NUMBYTES(numBits));
    // mark all high bits so that OsAtomicBitsetFindClearAndSet() is simpler
    if (numBits & LOW_BITS_MASK) {
        set->words[numBits / NUM_BITS_IN_ONE_BYTE] =
            ((UINT32)((INT32) - 1LL)) << (numBits & LOW_BITS_MASK);
    }
}

inline UINT32 OsAtomicBitsetGetNumBits(const struct AtomicBitset *set)
{
    return set->numBits;
}

/**************************************************************************
 Function    : OsAtomicBitsetGetBit
 Description : get the specified bit in set
 Input       : set --- pointer to the bitset
               num --- the num to fetch
 Output      : None
 Return      : LOS_OK on success or error code on failure
**************************************************************************/
BOOL OsAtomicBitsetGetBit(const struct AtomicBitset *set, UINT32 num)
{
    /* any value is as good as the next */
    if (num >= set->numBits) {
        return FALSE;
    }
    return !!((set->words[num / NUM_BITS_IN_ONE_BYTE]) & (1UL << (num & LOW_BITS_MASK)));
}

/**************************************************************************
 Function    : OsAtomicBitsetClearBit
 Description : clear the specified bit in set
 Input       : set --- pointer to the bitset
               num --- the num to clear
 Output      : None
 Return      : None
**************************************************************************/
VOID OsAtomicBitsetClearBit(struct AtomicBitset *set, UINT32 num)
{
    UINT32 *wordPtr = set->words + (num / NUM_BITS_IN_ONE_BYTE);

    if (num >= set->numBits) {
        return;
    }
    (*wordPtr) &= ~(1UL << (num & LOW_BITS_MASK));
}

/* find from the high bit to high bit return the address of the first available bit */
INT32 OsAtomicBitsetFindClearAndSet(struct AtomicBitset *set)
{
    UINT32 idx;
    UINT32 numWords = (set->numBits + LOW_BITS_MASK) / NUM_BITS_IN_ONE_BYTE;
    UINT32 *wordPtr = set->words;
    UINT32 tmpWord;
    INT32 count = 0;

    for (idx = 0; idx < numWords; idx++, wordPtr++) {
        if (*wordPtr == 0xFFFFFFFF) {
            continue;
        }

        tmpWord = ~(*wordPtr);

        while (tmpWord) {
            tmpWord = tmpWord >> 1UL;
            count++;
        }

        *wordPtr |= (1UL << (count - 1));

        return (INT32)(idx * NUM_BITS_IN_ONE_BYTE + count - 1);
    }

    return -1;
}

/* change the order of the output idx of OsAtomicBitsetFindClearAndSet to order of natural numbers */
INT32 OsAtomicBitsetIdxChgToNatural(struct AtomicBitset *bitset, INT32 index)
{
    UINT32 ret;
    UINT32 bit;
    if (index < 0) {
        return index;
    }
    bit = LOW_BITS_MASK + (index & ~LOW_BITS_MASK);
    if (bit > bitset->numBits - 1) {
        bit = bitset->numBits - 1;
    }
    ret = bit - (index & LOW_BITS_MASK);
    return ret;
}

/**************************************************************************
 Function    : OsAtomicBitsetEmpty
 Description : check whether bitset is empty
 Input       : bitset --- pointer to the bitset
 Output      : None
 Return      : LOS_OK on success or error code on failure
**************************************************************************/
BOOL OsAtomicBitsetEmpty(struct AtomicBitset *bitset)
{
    UINT32 idx = 0;
    for (idx = 0; idx < (bitset->numBits / NUM_BITS_IN_ONE_BYTE);) {
        if (bitset->words[idx] != 0) {
            return FALSE;
        }
        idx++;
    }
    if (bitset->numBits & LOW_BITS_MASK) {
        if (bitset->words[idx] & ~(0xFFFFFFFF << (bitset->numBits & LOW_BITS_MASK))) {
            return FALSE;
        }
    }
    return TRUE;
}

/**************************************************************************
 Function    : OsSlabAllocatorNew
 Description : create a new allocator
 Input       : pool      --- pointer to the pool
               itemSz    --- alloc size
               itemAlign --- aligned size
               numItems  --- item num
 Output      : None
 Return      : the pointer to a new allocator
**************************************************************************/
OsSlabAllocator* OsSlabAllocatorNew(VOID *pool, UINT32 itemSz, UINT32 itemAlign, UINT32 numItems)
{
    OsSlabAllocator *allocator = NULL;
    UINT32 bitSetSz;
    UINT32 dataSz;
    UINT32 itemSize;

    /* calculate size */
    bitSetSz = ATOMIC_BITSET_SZ(numItems);

    bitSetSz = (bitSetSz + itemAlign - 1) & (~(itemAlign - 1));
    itemSize = (itemSz + itemAlign - 1) & (~(itemAlign - 1));
    dataSz = itemSize * numItems;

    allocator = (OsSlabAllocator*)LOS_HeapAlloc(pool, sizeof(OsSlabAllocator) + bitSetSz + dataSz);

    if (allocator != NULL) {
        allocator->itemSz = itemSize;

        allocator->bitset = (struct AtomicBitset *)(VOID *)((UINT8*)allocator + sizeof(OsSlabAllocator));
        allocator->dataChunks = ((UINT8*)allocator->bitset) + bitSetSz;
        OsAtomicBitsetInit(allocator->bitset, numItems);
    }

    return allocator;
}


/**************************************************************************
 Function    : OsSlabAllocatorDestroy
 Description : free the specified allocator
 Input       : pool      --- pointer to the pool
               allocator --- pointer to the allocator
 Output      : None
 Return      : None
**************************************************************************/
VOID OsSlabAllocatorDestroy(VOID *pool, OsSlabAllocator *allocator)
{
    (VOID)LOS_HeapFree(pool, allocator);
}

/**************************************************************************
 Function    : OsSlabAllocatorAlloc
 Description : alloc one bit from the specified allocator
 Input       : allocator --- pointer to the allocator
 Output      : None
 Return      : NULL on failure or one bit from the specified allocator
**************************************************************************/
VOID* OsSlabAllocatorAlloc(OsSlabAllocator *allocator)
{
    INT32 itemIdx = OsAtomicBitsetFindClearAndSet(allocator->bitset);
    if (itemIdx < 0) {
        return NULL;
    }

    return allocator->dataChunks + allocator->itemSz * itemIdx;
}

/**************************************************************************
 Function    : OsSlabAllocatorFree
 Description : free the specified bit in the specified allocator
 Input       : allocator --- pointer to the allocator
               ptr       --- pointer to the mem chunk to be freed
 Output      : None
 Return      : TRUE or FALSE
**************************************************************************/
BOOL OsSlabAllocatorFree(OsSlabAllocator *allocator, VOID* ptr)
{
    UINT8 *ptrTmp = (UINT8*)ptr;
    UINT32 itemOffset = ptrTmp - allocator->dataChunks;
    UINT32 itemIdx = itemOffset / allocator->itemSz;

    // check for invalid inputs
    if ((itemOffset % allocator->itemSz) || (itemIdx >= OsAtomicBitsetGetNumBits(allocator->bitset)) ||
         !(OsAtomicBitsetGetBit(allocator->bitset, itemIdx))) {
        return FALSE;
    }

    OsAtomicBitsetClearBit(allocator->bitset, itemIdx);
    return TRUE;
}

/**************************************************************************
 Function    : OsSlabAllocatorGetNth
 Description : get the specified data chunk from the allocator
 Input       : allocator --- pointer to the allocator
               idx       --- chunk num
 Output      : None
 Return      : NULL on failure or specified data chunk on success
**************************************************************************/
VOID* OsSlabAllocatorGetNth(OsSlabAllocator *allocator, UINT32 idx)
{
    if (!OsAtomicBitsetGetBit(allocator->bitset, idx)) {
        return NULL;
    }

    return allocator->dataChunks + allocator->itemSz * idx;
}

/**************************************************************************
 Function    : OsSlabAllocatorGetIdxP
 Description : get the specified dataChunk from the specified allocator
 Input       : allocator --- pointer to the allocator
               idx       --- chunk num
 Output      : None
 Return      : the specified data Chunk from the specified allocator
**************************************************************************/
VOID* OsSlabAllocatorGetIdxP(OsSlabAllocator *allocator, UINT32 idx)
{
    return allocator->dataChunks + allocator->itemSz * idx;
}

/**************************************************************************
 Function    : OsSlabAllocatorGetIndex
 Description : get item index from the specified allocator
 Input       : allocator --- pointer to the allocator
               ptr       --- pointer to the mem chunk to get index
 Output      : None
 Return      : the item index from the specified allocator
**************************************************************************/
UINT32 OsSlabAllocatorGetIndex(OsSlabAllocator *allocator, VOID* ptr)
{
    UINT8 *ptrTmp = (UINT8*)ptr;
    UINT32 itemOffset = ptrTmp - allocator->dataChunks;
    UINT32 itemIdx = itemOffset / allocator->itemSz;

    if ((itemOffset % allocator->itemSz) ||
        (itemIdx >= OsAtomicBitsetGetNumBits(allocator->bitset)) ||
        !(OsAtomicBitsetGetBit(allocator->bitset, itemIdx))) {
        return (UINT32)(-1);
    }

    return itemIdx;
}

/**************************************************************************
 Function    : OsSlabAllocatorGetNumItems
 Description : get num bits of the specified allocator
 Input       : allocator --- pointer to the allocator
 Output      : None
 Return      : LOS_OK on success or error code on failure
**************************************************************************/
UINT32 OsSlabAllocatorGetNumItems(OsSlabAllocator *allocator)
{
    return OsAtomicBitsetGetNumBits(allocator->bitset);
}

/**************************************************************************
 Function    : OsSlabAllocatorEmpty
 Description : check whether the allocator is empty
 Input       : allocator --- pointer to the allocator
 Output      : None
 Return      : LOS_OK on success or error code on failure
**************************************************************************/
BOOL OsSlabAllocatorEmpty(OsSlabAllocator *allocator)
{
    return OsAtomicBitsetEmpty(allocator->bitset);
}

/**************************************************************************
 Function    : OsSlabAllocatorGetUsedItemCnt
 Description : get used num of the specified allocator
 Input       : allocator --- pointer to the allocator
 Output      : None
 Return      : used num of the specifiedd allocator
**************************************************************************/
UINT32 OsSlabAllocatorGetUsedItemCnt(OsSlabAllocator *allocator)
{
    UINT32 used;
    UINT32 idx;
    struct AtomicBitset *bitset = allocator->bitset;
    for (used = 0, idx = 0; idx < bitset->numBits; idx++) {
        if (OsAtomicBitsetGetBit(bitset, idx)) {
            used++;
        }
    }
    return used;
}

/**************************************************************************
 Function    : OsSlabAllocatorGetSlabInfo
 Description : get slab info from the specified allocator
 Input       : allocator --- pointer to the allocator
 Output      : pitemSz   --- item size
               itemCnt   --- item count
               curUsage  --- current usage
 Return      : None
**************************************************************************/
VOID OsSlabAllocatorGetSlabInfo(OsSlabAllocator *allocator, UINT32 *pitemSz, UINT32 *itemCnt, UINT32 *curUsage)
{
    *pitemSz = allocator->itemSz;
    *itemCnt = OsAtomicBitsetGetNumBits(allocator->bitset);
    *curUsage = OsSlabAllocatorGetUsedItemCnt(allocator);
}

/**************************************************************************
 Function    : OsSlabAllocatorCheck
 Description : check whether ptr is in allocator
 Input       : allocator --- pointer to the allocator
               ptr       --- pointer to the mem chunk to check
 Output      : None
 Return      : TRUE or FALSE
**************************************************************************/
BOOL OsSlabAllocatorCheck(OsSlabAllocator *allocator, VOID* ptr)
{
    UINT8 *ptrTmp = (UINT8*)ptr;
    UINT32 itemOffset = ptrTmp - allocator->dataChunks;
    UINT32 itemIdx = itemOffset / allocator->itemSz;

    // check for invalid inputs
    if ((itemOffset % allocator->itemSz) || (itemIdx >= OsAtomicBitsetGetNumBits(allocator->bitset)) ||
        !(OsAtomicBitsetGetBit(allocator->bitset, itemIdx))) {
        return FALSE;
    }

    return TRUE;
}

