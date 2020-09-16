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
 * @defgroup los_heap Heap
 * @ingroup kernel
 */

#ifndef _LOS_HEAP_PRI_H
#define _LOS_HEAP_PRI_H

#include "los_heap.h"
#include "los_slab_pri.h"
#include "los_memstat_pri.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagLosHeapStatus {
    UINT32 totalSize;
    UINT32 usedSize;
    UINT32 freeSize;
    UINT32 allocCount;
    UINT32 freeCount;
} LosHeapStatus;

struct LosHeapManager {
    struct LOS_HEAP_NODE *head;
    struct LOS_HEAP_NODE *tail;
    UINT32 size;
#if (LOSCFG_MEM_MUL_POOL == YES)
    VOID *nextPool;
#endif
#if (LOSCFG_KERNEL_MEM_SLAB == YES)
    struct LosSlabControlHeader slabCtrlHdr;
#endif
#if (LOSCFG_KERNEL_MEM_STATISTICS == YES)
    TaskMemUsedInfo memStats[LOSCFG_BASE_CORE_TSK_LIMIT + 2];
#endif
};

/**
 * @ingroup los_heap
 * @brief Look up the next memory node according to one memory node in the memory block list.
 *
 * @par Description:
 * This API is used to look up the next memory node according to one memory node in the memory block list.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param heapMan   [IN]    Type #LosHeapManager *  Pointer to the manager,to distinguish heap.
 * @param node      [IN]    Type #LOS_HEAP_NODE *   Size of memory in bytes to allocate.
 *
 * @retval   LOS_HEAP_NODE * Pointer to next memory node.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern struct LOS_HEAP_NODE* OsHeapPrvGetNext(struct LosHeapManager *heapMan, struct LOS_HEAP_NODE* node);

/**
 * @ingroup los_heap
 * @brief Obtain the heap information.
 *
 * @par Description:
 * This API is used to obtain the heap information.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param pool  [IN]    Type #VOID *  A pointer pointed to the heap memory pool.
 *
 * @retval       None.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID OsAlarmHeapInfo(VOID *pool);

/**
 * @ingroup los_heap
 * @brief Obtain the heap status.
 *
 * @par Description:
 * This API is used to obtain the heap status.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param pool      [IN]    Type #VOID *  A pointer pointed to the heap memory pool.
 * @param status    [OUT]   Type #LosHeapStatus *  Heap status.
 *
 * @retval   UINT32  Get status result.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsHeapStatisticsGet(VOID *pool, LosHeapStatus *status);

/**
 * @ingroup los_heap
 * @brief Get the max free block size.
 *
 * @par Description:
 * This API is used to Get the max free block size.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param pool   [IN]    Type #VOID *  A pointer pointed to the heap memory pool.
 *
 * @retval   UINT32  Max free block size.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsHeapGetMaxFreeBlkSize(VOID *pool);

#ifdef __cplusplus
}
#endif


#endif

