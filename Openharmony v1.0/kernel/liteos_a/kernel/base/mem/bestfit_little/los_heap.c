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

#include "string.h"
#include "securec.h"
#include "los_hwi.h"
#include "los_typedef.h"
#include "los_heap_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

static UINT32 g_memAllocCount = 0;
static UINT32 g_memFreeCount = 0;

#if (LOSCFG_HEAP_MEMORY_PEAK_STATISTICS == YES)
static UINT32 g_memCurHeapUsed = 0;
static UINT32 g_memMaxHeapUsed = 0;
#endif

#define HEAP_CAST(t, exp) ((t)(exp))
#define HEAP_ALIGN 4
#define HEAP_TAIL_NODE_SIZE_THRESHOLD   1024

/*
 * Description : look up the next memory node according to one memory node in the memory block list.
 * Input       : struct LosHeapManager *heapMan --- Pointer to the manager,to distinguish heap
 *               struct LosHeapNode *node --- Size of memory in bytes to allocate
 * Return      : Pointer to next memory node
 */
struct LosHeapNode* OsHeapPrvGetNext(struct LosHeapManager *heapMan, struct LosHeapNode *node)
{
    return (heapMan->tail == node) ? NULL : (struct LosHeapNode *)(UINTPTR)(node->data + node->size);
}

/*
 * Description : To initialize the heap memory and get the begin address and size of heap memory,
 *               then initialize LosHeapManager.
 * Input       : VOID *pool  --- begin address of the heap memory pool
 *               UITN32 size --- size of the heap memory pool
 * Return      : 1:success 0:error
 */
BOOL OsHeapInit(VOID *pool, UINT32 size)
{
    struct LosHeapNode *node = NULL;
    struct LosHeapManager *heapMan = HEAP_CAST(struct LosHeapManager *, pool);

    if ((heapMan == NULL) || (size <= (sizeof(struct LosHeapNode) + sizeof(struct LosHeapManager)))) {
        return FALSE;
    }

    // Ignore the return code when matching CSEC rule 6.6(2).
    (VOID)memset_s(pool, size, 0, size);

    heapMan->size = size;

    node = heapMan->head = (struct LosHeapNode *)((UINT8*)pool + sizeof(struct LosHeapManager));

    heapMan->tail = node;

    node->used = 0;
    node->prev = NULL;
    node->size = size - sizeof(struct LosHeapNode) - sizeof(struct LosHeapManager);

    return TRUE;
}

/*
 * Description : update used size
 * Input       : size --- alloc memory size
 *               ret --- memory chunk
 */
VOID OsHeapUpdateUsedSize(UINT32 size, VOID *ret)
{
#if (LOSCFG_HEAP_MEMORY_PEAK_STATISTICS == YES)
    g_memCurHeapUsed += (size + sizeof(struct LosHeapNode));
    if (g_memCurHeapUsed > g_memMaxHeapUsed) {
        g_memMaxHeapUsed = g_memCurHeapUsed;
    }
#endif

    if (ret != NULL) {
        g_memAllocCount++;
    }
}

/*
 * Description : To alloc memory block from the heap memory poll
 * Input       : VOID *pool --- Pointer to the manager,to distinguish heap
 *               UINT32 size --- size of the heap memory pool
 * Return      : NULL:error, other value:the address of the memory we alloced
 */
VOID* OsHeapAlloc(VOID *pool, UINT32 size)
{
    struct LosHeapNode *node = NULL;
    struct LosHeapNode *next = NULL;
    struct LosHeapNode *best = NULL;
    VOID *ret = NULL;
    UINT32 alignSize = ALIGNE(size);

    struct LosHeapManager *heapMan = HEAP_CAST(struct LosHeapManager *, pool);
    if (heapMan == NULL) {
        return NULL;
    }

    node = heapMan->tail;
    while (node != NULL) {
        if ((node->used == 0) && (node->size >= alignSize) &&
            ((best == NULL) || (best->size > node->size))) {
            best = node;
            if (best->size == alignSize) {
                goto SIZE_MATCH;
            }
        }
        node = node->prev;
    }

    /* alloc failed */
    if (best == NULL) {
        PRINT_ERR("there's not enough whole to alloc %x Bytes!\n", alignSize);
        goto OUT;
    }

    if ((best->size - alignSize) > sizeof(struct LosHeapNode)) {
        /* hole divide into 2 */
        node = (struct LosHeapNode*)(UINTPTR)(best->data + alignSize);

        node->used = 0;
        node->size = best->size - alignSize - sizeof(struct LosHeapNode);
        node->prev = best;

        if (best != heapMan->tail) {
            next = OsHeapPrvGetNext(heapMan, node);
            if (next != NULL) {
                next->prev = node;
            }
        } else {
            heapMan->tail = node;
        }

        best->size = alignSize;
    }

SIZE_MATCH:
    best->align = 0;
    best->used = 1;
    ret = best->data;

    OsHeapUpdateUsedSize(alignSize, ret);
OUT:

    return ret;
}

/*
 * Description : To alloc memory block from the heap memory poll with
 * Input       : VOID *pool   --- Pointer to the manager,to distinguish heap
 *               UINT32 size   --- size of the heap memory pool
 *               UINT32 boundary --- boundary the heap needs align
 * Return      : NULL:error, other value:the address of the memory we alloced
 */
VOID* OsHeapAllocAlign(VOID *pool, UINT32 size, UINT32 boundary)
{
    UINT32 useSize;
    UINT32 gapSize;
    VOID *ret = NULL;
    VOID *alignedPtr = NULL;

    if ((pool == NULL) || (size == 0) || (boundary < sizeof(VOID *)) || !IS_ALIGNED(boundary, boundary)) {
        return NULL;
    }

    /* worst case is that the node happen to be 4 bytes ahead of the boundary */
    useSize = (size + boundary) - sizeof(VOID*);
    if (useSize < size) {
        return NULL;
    }

    ret = OsHeapAlloc(pool, useSize);
    if (ret != NULL) {
        alignedPtr = (VOID *)(UINTPTR)OS_MEM_ALIGN(ret, boundary);
        if (ret == alignedPtr) {
            goto OUT;
        }

        gapSize = (UINTPTR)alignedPtr - (UINTPTR)ret;
        OS_MEM_SET_ALIGN_FLAG(gapSize);
        *((UINT32 *)((UINTPTR)alignedPtr - (sizeof(UINTPTR) / sizeof(UINT8)))) = gapSize;

        ret = alignedPtr;
    }
OUT:
    return ret;
}

STATIC VOID OsDoHeapFree(struct LosHeapManager *heapMan, struct LosHeapNode *curNode)
{
    struct LosHeapNode *node = curNode;
    struct LosHeapNode *next = NULL;
    /* set to unused status */
    node->used = 0;

#if (LOSCFG_HEAP_MEMORY_PEAK_STATISTICS == YES)
    if (g_memCurHeapUsed >= (node->size + sizeof(struct LosHeapNode))) {
        g_memCurHeapUsed -= (node->size + sizeof(struct LosHeapNode));
    }
#endif

    /* unused region before and after combination */
    while (node->prev && !node->prev->used) {
        node = node->prev;
    }

    next = OsHeapPrvGetNext(heapMan, node);
    while (next != NULL) {
        if (next->used) {
            next->prev = node;
            break;
        }
        node->size += sizeof(struct LosHeapNode) + next->size;
        if (heapMan->tail == next) {
            heapMan->tail = node;
        }
        next = OsHeapPrvGetNext(heapMan, node);
    }
}

/*
 * Description : To free the  memory block from  heap memory poll
 * Input       : VOID* pool --- Pointer to the manager,to distinguish heap
 *               VOID* ptr --- the pointer of heap memory we want to free
 * Return      : 1:success 0:error
 */
BOOL OsHeapFree(VOID *pool, VOID *ptr)
{
    struct LosHeapNode *node = NULL;

    UINT32 gapSize;
    BOOL ret = TRUE;

    struct LosHeapManager *heapMan = HEAP_CAST(struct LosHeapManager *, pool);
    if ((heapMan == NULL) || (ptr == NULL)) {
        return LOS_NOK;
    }

    /* find the real ptr through gap size */
    gapSize = *((UINT32 *)((UINTPTR)ptr - (sizeof(UINTPTR) / sizeof(UINT8))));
    if (OS_MEM_GET_ALIGN_FLAG(gapSize)) {
        gapSize = OS_MEM_GET_ALIGN_GAPSIZE(gapSize);
        ptr = (VOID *)((UINTPTR)ptr - gapSize);
    }

    if (((UINTPTR)ptr < (UINTPTR)heapMan->head) ||
        ((UINTPTR)ptr > ((UINTPTR)heapMan->tail + sizeof(struct LosHeapNode)))) {
        PRINT_ERR("0x%x out of range!\n", (UINTPTR)ptr);
        return FALSE;
    }

    node = ((struct LosHeapNode *)ptr) - 1;
    /* check if the address is a node of the heap memory list */
    if ((node->used == 0) || (!((UINTPTR)node == (UINTPTR)heapMan->head) &&
        (((UINTPTR)node->prev < (UINTPTR)heapMan->head) ||
        ((UINTPTR)node->prev > ((UINTPTR)heapMan->tail + sizeof(struct LosHeapNode))) ||
        ((UINTPTR)OsHeapPrvGetNext(heapMan, node->prev) != (UINTPTR)node)))) {
        ret = FALSE;
        goto OUT;
    }

    OsDoHeapFree(heapMan, node);

OUT:
    if (ret == TRUE) {
        g_memFreeCount++;
    }

    return ret;
}

/*
 * Description : print heap information
 * Input       : pool --- Pointer to the manager, to distinguish heap
 */
VOID OsAlarmHeapInfo(VOID *pool)
{
    struct LosHeapManager *heapMan = HEAP_CAST(struct LosHeapManager *, pool);
    LosHeapStatus status = {0};
    (VOID)heapMan;

    if (OsHeapStatisticsGet(pool, &status) == LOS_NOK) {
        return;
    }

    PRINT_INFO("pool addr    pool size    used size    free size    max free    alloc Count    free Count\n");
    PRINT_INFO("0x%-8x   0x%-8x   0x%-8x    0x%-8x   0x%-8x   0x%-8x     0x%-8x\n",
               pool, heapMan->size, status.totalUsedSize, status.totalFreeSize, status.maxFreeNodeSize,
               status.usedNodeNum, status.freeNodeNum);
}

/*
 * Description : collect heap statistics
 * Input       : pool --- Pointer to the manager, to distinguish heap
 * Output      : status --- heap statistics
 * Return      : LOS_OK on success or error code on failure
 */
UINT32 OsHeapStatisticsGet(VOID *pool, LosHeapStatus *status)
{
    UINT32 heapUsed = 0;
    UINT32 maxFreeNodeSize = 0;
    UINT32 freeNodeNum = 0;
    UINT32 usedNodeNum = 0;

    struct LosHeapNode *node = NULL;
    struct LosHeapManager *ramHeap = HEAP_CAST(struct LosHeapManager *, pool);

    if (ramHeap == NULL) {
        return LOS_NOK;
    }

    if (status == NULL) {
        return LOS_NOK;
    }

    /* heap mannager header use heap space */
    heapUsed += sizeof(struct LosHeapManager);

    node = ramHeap->tail;
    while (node != NULL) {
        if (node->used) {
            heapUsed += (node->size + sizeof(struct LosHeapNode));
            usedNodeNum++;
        } else {
            if (node->size > maxFreeNodeSize) {
                maxFreeNodeSize = node->size;
            }
            freeNodeNum++;
        }
        node = node->prev;
    }

    if (ramHeap->size < heapUsed) {
        return LOS_NOK;
    }

    status->totalUsedSize = heapUsed;
    status->maxFreeNodeSize = maxFreeNodeSize;
    status->totalFreeSize = ramHeap->size - status->totalUsedSize;
    status->usedNodeNum = usedNodeNum;
    status->freeNodeNum = freeNodeNum;

    return LOS_OK;
}

#if (LOSCFG_HEAP_MEMORY_PEAK_STATISTICS == YES)
UINT32 LOS_HeapGetHeapMemoryPeak(VOID)
{
    return g_memMaxHeapUsed;
}
#endif

/*
 * Description : get max free block size
 * Input       : pool --- Pointer to the manager, to distinguish heap
 * Return      : max free block size
 */
UINT32 OsHeapGetMaxFreeBlkSize(VOID *pool)
{
    UINT32 size = 0;
    UINT32 temp;
    struct LosHeapNode *node = NULL;
    struct LosHeapManager *ramHeap = HEAP_CAST(struct LosHeapManager *, pool);

    if (ramHeap == NULL) {
        return LOS_NOK;
    }

    node = ramHeap->tail;
    while (node != NULL) {
        if (!(node->used)) {
            temp = node->size;
            if (temp > size) {
                size = temp;
            }
        }
        node = node->prev;
    }
    return size;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
