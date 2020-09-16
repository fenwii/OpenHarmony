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

#define _LOS_SLAB_MEM_C_
#include <los_printf.h>
#include <los_hwi.h>
#include <los_slab_pri.h>

VOID *OsSlabBlockHeadFill(OsSlabBlockNode *slabNode, UINT32 blkSz)
{
    OS_SLAB_BLOCK_MAGIC_SET(slabNode);
    OS_SLAB_BLOCK_SIZE_SET(slabNode, blkSz);
    OS_SLAB_BLOCK_ID_SET(slabNode, 0); // now undefine how to use ID
    return (VOID *)(slabNode + 1);
}

/*****************************************************************************
 Function    : OsSlabMemInit
 Description : To initialize the slab memory management
 Input       : None
 Output      : None
 Return      : TRUE --- initialize OK, FALSE --- initialize false
*****************************************************************************/
BOOL OsSlabMemInit(VOID *pool)
{
    struct LosSlabControlHeader *slabMemHead = OsSlabCtrlHdrGet(pool);
    UINT32 idx = 0;
    UINT32 tmp = 0;
    UINT32 blkSz = 0;
    UINT32 blkCnt = 0;

    for (idx = 0; idx < SLAB_MEM_COUNT; idx++) {
        blkSz = (SLAB_MEM_CALSS_STEP_SIZE << idx);
        blkCnt = SLAB_MEM_ALLOCATOR_SIZE / blkSz;
        slabMemHead->slabClass[idx].blkSz = blkSz;
        slabMemHead->slabClass[idx].blkCnt = blkCnt;
        slabMemHead->slabClass[idx].blkUsedCnt = 0;
        if (slabMemHead->slabClass[idx].alloc != NULL) {
            PRINT_WARN("SlabMemAllocator[%d] inited before\n", idx);
            tmp++;
        } else {
            slabMemHead->slabClass[idx].alloc =
                OsSlabAllocatorNew(pool, blkSz + sizeof(OsSlabBlockNode), (UINT32)sizeof(VOID *), blkCnt);
        }
    }

    return ((tmp == 0) ? TRUE : FALSE);
}

/*****************************************************************************
 Function    : OsSlabMemAlloc
 Description : To alloc memory block
 Input       : pool --- pointer to the memory pool
               size --- size of the  memory we want to alloc
 Output      : None
 Return      : pointer :the address of the memory we alloced
*****************************************************************************/
VOID *OsSlabMemAlloc(VOID *pool, UINT32 size)
{
    VOID *ret = NULL;
    UINTPTR intSave;
    struct LosSlabControlHeader *slabMem = OsSlabCtrlHdrGet(pool);
    OsSlabMem *slabAlloc = NULL;
    UINT32 idx;

    if (size > (SLAB_MEM_CALSS_STEP_SIZE << (SLAB_MEM_COUNT - 1))) {
        return NULL;
    }

    for (idx = 0; idx < SLAB_MEM_COUNT; idx++) {
        if (size <= slabMem->slabClass[idx].blkSz) {
            intSave = LOS_IntLock();

            if (slabMem->slabClass[idx].blkUsedCnt >= slabMem->slabClass[idx].blkCnt) {
                LOS_IntRestore(intSave);
                return NULL;
            }

            if (slabMem->slabClass[idx].alloc == NULL) {
                LOS_IntRestore(intSave);
                return NULL;
            }

            slabAlloc = &(slabMem->slabClass[idx]);
            ret = OsSlabAllocatorAlloc(slabAlloc->alloc);
            if (ret != NULL) {
                /* alloc success */
                ret = OsSlabBlockHeadFill((OsSlabBlockNode *)ret, slabMem->slabClass[idx].blkSz);
                slabMem->slabClass[idx].blkUsedCnt++;
            }

            LOS_IntRestore(intSave);
            return ret;
        }
    }

    return NULL;
}

/*****************************************************************************
 Function    : OsSlabMemFree
 Description : To free the memory block
 Input       : pool --- Pointer to the memory pool that contains the memory block to be allocated
               ptr  --- the pointer of heap memory we want to free
 Output      : None
 Return      : TRUE:success FALSE:error
*****************************************************************************/
BOOL OsSlabMemFree(VOID *pool, VOID* ptr)
{
    UINTPTR intSave;
    struct LosSlabControlHeader *slabMem = OsSlabCtrlHdrGet(pool);
    BOOL ret = FALSE;
    OsSlabMem *slabAlloc = NULL;
    UINT32 idx;
    OsSlabBlockNode *slabNode = OS_SLAB_BLOCK_HEAD_GET(ptr);

    if (!OS_ALLOC_FROM_SLAB_CHECK(slabNode)) {
        return FALSE;
    }
    for (idx = 0; idx < SLAB_MEM_COUNT; idx++) {
        if (slabMem->slabClass[idx].blkSz >= OS_SLAB_BLOCK_SIZE_GET(slabNode)) {
            intSave = LOS_IntLock();

            slabAlloc = &(slabMem->slabClass[idx]);
            if (TRUE == OsSlabAllocatorFree(slabAlloc->alloc, slabNode)) {
                ret = TRUE;
                slabMem->slabClass[idx].blkUsedCnt--;
            }

            LOS_IntRestore(intSave);
            return ret;
        }
    }
    return FALSE;
}

/*****************************************************************************
 Function    : OsSlabMemDeinit
 Description :  deinitialize the slab memory ,set back to the original status
 Input       : pool --- Pointer to the memory pool
 Output      : None
 Return      : None
*****************************************************************************/
VOID OsSlabMemDeinit(VOID *pool)
{
    UINT32 idx;
    struct LosSlabControlHeader *slabMem = NULL;
    OsSlabMem *slabAlloc = NULL;
    UINT32 blkSz;
    UINT32 blkCnt;

    if (pool == NULL) {
        return ;
    }
    slabMem = OsSlabCtrlHdrGet(pool);

    for (idx = 0; idx < SLAB_MEM_COUNT; idx++) {
        blkSz = (SLAB_MEM_CALSS_STEP_SIZE << idx);
        blkCnt = SLAB_MEM_ALLOCATOR_SIZE / blkSz;
        slabMem->slabClass[idx].blkSz = blkSz;
        slabMem->slabClass[idx].blkCnt = blkCnt;
        if (slabMem->slabClass[idx].alloc != NULL) {
            slabAlloc = &(slabMem->slabClass[idx]);
            OsSlabAllocatorDestroy(pool, slabAlloc->alloc);
            slabMem->slabClass[idx].alloc = NULL;
        }
    }
    return ;
}

/**************************************************************************
 Function    : OsSlabMemCheck
 Description : check slab memory
 Input       : pool --- pointer to the memory pool
               ptr  --- pointer to the memory chunk
 Output      : None
 Return      : LOS_OK on success or error code on failure
**************************************************************************/
UINT32 OsSlabMemCheck(VOID *pool, VOID* ptr)
{
    UINTPTR intSave;
    struct LosSlabControlHeader *slabMem = OsSlabCtrlHdrGet(pool);
    UINT32 retBlkSz = (UINT32)-1;
    OsSlabMem *slabAlloc = NULL;
    UINT32 idx;
    OsSlabBlockNode *slabNode = OS_SLAB_BLOCK_HEAD_GET(ptr);

    if ((!OS_ALLOC_FROM_SLAB_CHECK(slabNode)) ||
        slabMem->slabClass[SLAB_MEM_COUNT - 1].blkSz > (OS_SLAB_BLOCK_SIZE_GET(slabNode))) {
        return retBlkSz;
    }

    intSave = LOS_IntLock();
    for (idx = 0; idx < SLAB_MEM_COUNT; idx++) {
        slabAlloc = &(slabMem->slabClass[idx]);
        if (OsSlabAllocatorCheck(slabAlloc->alloc, slabNode) == TRUE) {
            retBlkSz = slabMem->slabClass[idx].blkSz;
        }
    }
    LOS_IntRestore(intSave);

    return retBlkSz;
}

/**************************************************************************
 Function    : OsSlabStatisticsGet
 Description : collect slab statistics
 Input       : pool   --- pointer to the memory pool
 Output      : status --- memory pool statistics
 Return      : LOS_OK on success or error code on failure
**************************************************************************/
UINT32 OsSlabStatisticsGet(VOID *pool, LosSlabStatus *status)
{
    struct LosSlabControlHeader *slabMem = NULL;
    OsSlabMem *slabAlloc = NULL;
    UINT32 itemSz = 0;
    UINT32 itemCnt = 0;
    UINT32 curUsage = 0;
    UINT32 totalUsage = 0;
    UINT32 totalMem = 0;
    UINT32 totalAllocCount = 0;
    UINT32 totalFreeCount = 0;
    UINT32 idx;

    if ((status == NULL) || (pool == NULL)) {
        return LOS_NOK;
    }
    slabMem = OsSlabCtrlHdrGet(pool);

    for (idx = 0; idx < SLAB_MEM_COUNT; idx++) {
        slabAlloc = &(slabMem->slabClass[idx]);

        OsSlabAllocatorGetSlabInfo(slabAlloc->alloc, &itemSz, &itemCnt, &curUsage);
        totalUsage += (curUsage * itemSz);
        totalMem += (itemCnt * itemSz);
        totalAllocCount += slabMem->slabClass[idx].blkUsedCnt;
        totalFreeCount  += slabMem->slabClass[idx].blkCnt - slabMem->slabClass[idx].blkUsedCnt;
    }

    if (totalMem < totalUsage) {
        return LOS_NOK;
    }

    status->totalSize  = totalMem;
    status->usedSize   = totalUsage;
    status->freeSize   = status->totalSize - status->usedSize;
    status->allocCount = totalAllocCount;
    status->freeCount  = totalFreeCount;
    return LOS_OK;
}

/**************************************************************************
 Function    : OsSlabGetMaxFreeBlkSize
 Description : get max free block size
 Input       : pool --- pointer to the memory pool
 Output      : None
 Return      : max free block size
**************************************************************************/
UINT32 OsSlabGetMaxFreeBlkSize(VOID *pool)
{
    struct LosSlabControlHeader *slabMem = OsSlabCtrlHdrGet(pool);
    OsSlabMem *slabAlloc = NULL;
    UINT32 itemSz = 0;
    UINT32 itemCnt = 0;
    UINT32 curUsage = 0;
    int idx;

    for (idx = SLAB_MEM_COUNT - 1; idx >= 0; idx--) {
        slabAlloc = &(slabMem->slabClass[idx]);
        if (slabAlloc->alloc) {
            OsSlabAllocatorGetSlabInfo(slabAlloc->alloc, &itemSz, &itemCnt, &curUsage);
            if (curUsage != itemCnt) {
                return itemSz;
            }
        }
    }

    return 0;
}
