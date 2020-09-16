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

#ifndef _LOS_HEAP_H
#define _LOS_HEAP_H

#include <los_typedef.h>
#include "los_base.h"
#if (LOSCFG_KERNEL_MEM_SLAB == YES)
#include "los_slab.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define IS_ALIGNED(value)                       ((((UINT32)(value)) & ((UINT32)((value) - 1))) == 0)
#define OS_MEM_ALIGN(value, align)              (((UINT32)(UINTPTR)(value) + (UINT32)((align) - 1)) & \
                                                (~(UINT32)((align) - 1)))
#define OS_MEM_ALIGN_FLAG                       0x80000000
#define OS_MEM_SET_ALIGN_FLAG(align)            ((align) = ((align) | OS_MEM_ALIGN_FLAG))
#define OS_MEM_GET_ALIGN_FLAG(align)            ((align) & OS_MEM_ALIGN_FLAG)
#define OS_MEM_GET_ALIGN_GAPSIZE(align)         ((align) & (~OS_MEM_ALIGN_FLAG))

#define RAM_HEAP_SIZE                           ((OS_SYS_MEM_SIZE) & (~7))
#define RAM_HEAP_START                          (OS_SYS_MEM_ADDR)

#ifdef CONFIG_DDR_HEAP
#define DDR_HEAP_INIT()                         LOS_HeapInit((VOID *)DDR_HEAP_START, DDR_HEAP_SIZE)
#define DDR_HEAP_ALLOC(sz)                      LOS_HeapAllocAlign((VOID *)DDR_HEAP_START, \
                                                OS_MEM_ALIGN(sz, DCACHE_LINE_SIZE), DCACHE_LINE_SIZE)
#define DDR_HEAP_FREE(p)                        LOS_HeapFree((VOID *)DDR_HEAP_START, p)
#endif

/* extra 2 blocks is for idle and extra temparary task */
#define TASK_BLOCK_NUM                          (LOSCFG_BASE_CORE_TSK_LIMIT + 2)

#if (LOSCFG_KERNEL_MEM_STATISTICS == YES)
#define TASKID_BITS                             7
/* 2 bits for used and align flag, 30 bits left */
#define SIZE_BITS                               (30 - TASKID_BITS)
#if (SIZE_BITS <= 0)
#error task id bits too big!
#endif
#if (TASK_BLOCK_NUM > ((1 << TASKID_BITS) - 1))
#error task id bits too small!
#endif
#endif

struct LOS_HEAP_NODE {
    struct LOS_HEAP_NODE* pstPrev;
#if (LOSCFG_KERNEL_MEM_STATISTICS == YES)
    UINT32 uwSize  : SIZE_BITS;
    UINT32 taskID  : TASKID_BITS;
#else
    UINT32 uwSize  : 30;
#endif
    UINT32 uwUsed  : 1;
    UINT32 uwAlign : 1;
    UINT8  ucData[0]; /*lint !e43*/
};

/**
 * @ingroup los_heap
 * @brief Initialization heap memory.
 *
 * @par Description:
 * This API is used to initialization heap memory.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param pool   [IN/OUT] A pointer pointed to the memory pool.
 * @param size   [IN] Size of heap memory.
 *
 * @retval TRUE   Initialization success.
 * @retval FALSE  Initialization failed.
 * @par Dependency:
 * <ul><li>los_heap.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern BOOL LOS_HeapInit(VOID *pool, UINT32 size);

/**
 * @ingroup los_heap
 * @brief Alloc memory block from heap memory.
 *
 * @par Description:
 * This API is used to alloc memory block from heap memory.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param pool   [IN/OUT] A pointer pointed to the memory pool.
 * @param size   [IN]     Size of heap memory.
 *
 * @retval VOID*
 * @par Dependency:
 * <ul><li>los_heap.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_HeapFree
 */
extern VOID* LOS_HeapAlloc(VOID *pool, UINT32 size);

/**
 * @ingroup los_heap
 * @brief Alloc aligned memory block from heap memory.
 *
 * @par Description:
 * This API is used to alloc aligned  memory block from heap memory.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param pool       [IN/OUT] A pointer pointed to the memory pool.
 * @param size       [IN]     Size of heap memory.
 * @param boundary   [IN]     Boundary the heap needs align
 *
 * @retval VOID*
 * @par Dependency:
 * <ul><li>los_heap.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_HeapFree
 */
extern VOID* LOS_HeapAllocAlign(VOID *pool, UINT32 size, UINT32 boundary);

/**
 * @ingroup los_heap
 * @brief Free memory block from heap memory.
 *
 * @par Description:
 * This API is used to free memory block from heap memory.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param pool   [IN/OUT] A pointer pointed to the memory pool.
 * @param ptr    [IN]     Point to be freed.
 *
 * @retval BOOL TRUE  free success  FALSE  free failed
 * @par Dependency:
 * <ul><li>los_heap.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_HeapAlloc
 */
extern BOOL LOS_HeapFree(VOID *pool, VOID* ptr);

/**
 * @ingroup los_memory
 * @brief Get the memory info from Heap.
 *
 * @par Description:
 * This API is used to get the memory info from Heap.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param None.
 *
 * @retval   UINT32  Max size of heap memory being used.
 *
 * @par Dependency:
 * <ul><li>los_heap.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
#if (LOSCFG_HEAP_MEMORY_PEAK_STATISTICS == YES)
extern UINT32 LOS_HeapGetHeapMemoryPeak(VOID);
#endif

/**
 * @ingroup los_memory
 * @brief Get the memory statistics from Heap.
 *
 * @par Description:
 * This API is used to get the memory statistics from Heap.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param None.
 *
 * @retval   None.
 *
 * @par Dependency:
 * <ul><li>los_heap.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
#if (LOSCFG_KERNEL_MEM_STATISTICS == YES)
VOID LOS_HeapDumpMemoryStats(VOID *pool);
#endif

#ifdef __cplusplus
}
#endif


#endif

