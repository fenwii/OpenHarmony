/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2018. All rights reserved.
 * Description: LiteOS Mem Module Implementation
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
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
 * --------------------------------------------------------------------------- */

#ifndef _LOS_MEMORY_H
#define _LOS_MEMORY_H
#include "los_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup los_memory
 * Memory information structure
 */
typedef struct {
    UINT32 usedSize;
    UINT32 freeSize;
    UINT32 totalSize;
    UINT32 allocCount;
    UINT32 freeCount;
    UINT32 mallocFailCount;
#if defined(LOSCFG_MEM_WATERLINE) && (LOSCFG_MEM_WATERLINE == YES)
    UINT32 usageWaterLine;
#endif
} LOS_MEM_STATUS;

#if (LOSCFG_MEMORY_BESTFIT == YES)

#if (LOSCFG_BASE_MEM_NODE_SIZE_CHECK == YES)
#define OS_MEM_CHECK_DEBUG
#endif

typedef VOID (*MALLOC_HOOK)(VOID);

extern MALLOC_HOOK g_mallocHook;

typedef VOID (*MEM_CHECK_ERR_FUNC)(VOID *tmpNode);

/**
 * @ingroup los_memory
 * @brief Get the pointer to the little memory pool.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get the pointer to the little memory pool.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param None.
 *
 * @retval #VOID*         return the pointer to the little memory pool.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 */
extern VOID *LOS_MemGetLmp(VOID);

/**
 * @ingroup los_memory
 * @brief Get the size of memory totally used.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get the size of memory totally used in memory pool.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * </ul>
 *
 * @param  pool           [IN] A pointer pointed to the memory pool.
 *
 * @retval #LOS_NOK        The incoming parameter pool is NULL.
 * @retval #UINT32         The size of the memory pool used.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 LOS_MemTotalUsedGet(VOID *pool);

/**
 * @ingroup los_memory
 * @brief Get the number of free memory nodes.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get the number of free memory nodes in memory pool.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * </ul>
 *
 * @param  pool           [IN] A pointer pointed to the memory pool.
 *
 * @retval #LOS_NOK        The incoming parameter pool is NULL.
 * @retval #UINT32         The number of free memory nodes.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 LOS_MemFreeBlksGet(VOID *pool);

/**
 * @ingroup los_memory
 * @brief Get the number of used memory nodes.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get the number of used memory nodes in memory pool.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * </ul>
 *
 * @param  pool           [IN] A pointer pointed to the memory pool.
 *
 * @retval #LOS_NOK        The incoming parameter pool is NULL.
 * @retval #UINT32         The number of used memory nodes.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 LOS_MemUsedBlksGet(VOID *pool);

/**
 * @ingroup los_memory
 * @brief Get the task ID of a used memory node.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get the task ID of a used memory node.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input ptr parameter must be allocated by LOS_MemAlloc or LOS_MemAllocAlign.</li>
 * <li>This interface only support obtain the task ID of a used memory node which is allocated from
 * the system memory pool (OS_SYS_MEM_ADDR) at present.</li>
 * </ul>
 *
 * @param  pool               [IN] A used memory node.
 *
 * @retval #OS_INVALID        The incoming parameter ptr is illegal.
 * @retval #UINT32            The task ID of used memory node ptr.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 LOS_MemTaskIdGet(const VOID *pool);

/**
 * @ingroup los_memory
 * @brief Get the address of last node.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get the address of last node.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * <li>The last node of memory pool is not the end node.</li>
 * </ul>
 *
 * @param  pool               [IN] A pointer pointed to the memory pool.
 *
 * @retval #LOS_NOK           The incoming parameter pool is NULL.
 * @retval #UINT32            The address of the last used node that casts to UINT32.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 LOS_MemLastUsedGet(VOID *pool);

/**
 * @ingroup los_memory
 * @brief Check the memory pool Integrity.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to check the memory pool Integrity.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * <li>LOS_MemIntegrityCheck will be called by malloc function when the macro of LOSCFG_BASE_MEM_NODE_INTEGRITY_CHECK
 * is defined in LiteOS.</li>
 * <li>LOS_MemIntegrityCheck function can be called by user anytime.</li>
 * </ul>
 *
 * @param  pool              [IN] A pointer pointed to the memory pool.
 *
 * @retval #LOS_NOK           The memory pool (pool) is impaired.
 * @retval #LOS_OK            The memory pool (pool) is integrated.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 LOS_MemIntegrityCheck(VOID *pool);

/**
 * @ingroup los_memory
 * @brief Figure the system memory pool for it's total mem used.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to figure the system memory pool for it's total mem used.</li>
 * </ul>
 *
 * @retval #UINT32   The mem used.
 * @par Dependency:
 * <ul>
 * <li>los_memory.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see None.
 */
extern UINT32 LOS_MemGetUsed(VOID);

/**
 * @ingroup los_memory
 * @brief Get the system memory pool's size.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get the system memory pool's size.</li>
 * </ul>
 *
 * @retval #UINT32   The poll size.
 * @par Dependency:
 * <ul>
 * <li>los_memory.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see None.
 */
extern UINT32 LOS_MemGetTotal(VOID);

/**
 * @ingroup los_memory
 * @brief Get the memory pool's size.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get the memory pool's size.</li>
 * </ul>
 *
 * @retval #UINT32   The memory poll size.
 * @par Dependency:
 * <ul>
 * <li>los_memory.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see None.
 */
extern UINT32 LOS_MemPoolSizeGet(const VOID *pool);

/**
 * @ingroup los_memory
 *  Define a mem size check intensity
 *
 *  Lowest mem check.
 */
#define LOS_MEM_CHECK_LEVEL_LOW     0

/**
 * @ingroup los_memory
 * Define a mem size check intensity
 *
 * Highest mem check.
 */
#define LOS_MEM_CHECK_LEVEL_HIGH    1

/**
 * @ingroup los_memory
 * Define a mem size check intensity
 *
 * disable mem check.
 */
#define LOS_MEM_CHECK_LEVEL_DISABLE 0xff

/**
 * @ingroup los_memory
 * Define a mem size check intensity
 *
 * default intensity set mem check.
 */
#define LOS_MEM_CHECK_LEVEL_DEFAULT LOS_MEM_CHECK_LEVEL_DISABLE

/**
 * @ingroup los_memory
 * @brief Check the size of memory node specified.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to check the size of memory node.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * <li>The input ptr parameter must be allocated by LOS_MemAlloc or LOS_MemAllocAlign.</li>
 * <li>The function will be called by function specified, such as memset or memcpy.</li>
 * <li>The feature can be enabled when you set the macro value of LOSCFG_BASE_MEM_NODE_SIZE_CHECK as YES.</li>
 * <li>You had better set memory check level as LOS_MEM_CHECK_LEVEL_DISABLE when copy bin file.</li>
 * </ul>
 *
 * @param  pool              [IN]  A pointer pointed to the memory pool.
 * @param  ptr               [IN]  A pointer pointed to the source node.
 * @param  totalSize         [OUT] A pointer to save total size, must point to valid memory.
 * @param  availSize         [OUT] A pointer to save available size, must point to valid memory.
 *
 * @retval #OS_ERRNO_MEMCHECK_DISABLED           Memcheck function does not open.
 * @retval #OS_ERRNO_MEMCHECK_NOT_INIT           Memcheck function does not init.
 * @retval #OS_ERRNO_MEMCHECK_PARA_NULL          The pool or ptr is NULL.
 * @retval #OS_ERRNO_MEMCHECK_OUTSIDE            The ptr address is not in the reasonable range.
 * @retval #OS_ERRNO_MEMCHECK_NO_HEAD            Can't find the control head node from ptr.
 * @retval #OS_ERRNO_MEMCHECK_WRONG_LEVEL        The memory check level is illegal.
 * @retval #LOS_OK                               Success to get total size and available
 *                                               size of the memory node (ptr).
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemCheckLevelSet | LOS_MemCheckLevelGet
 */
extern UINT32 LOS_MemNodeSizeCheck(VOID *pool, const VOID *ptr, UINT32 *totalSize, UINT32 *availSize);

/**
 * @ingroup los_memory
 * @brief Set the memory check level.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to set the memory check level.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>There are three level you can set.</li>
 * <li>The legal level are LOS_MEM_CHECK_LEVEL_LOW, LOS_MEM_CHECK_LEVEL_HIGH, LOS_MEM_CHECK_LEVEL_DISABLE.</li>
 * </ul>
 *
 * @param  level                                  [IN] The level what you want to set.
 *
 * @retval #LOS_ERRNO_MEMCHECK_WRONG_LEVEL           The memory check level what you want to set is illegal.
 * @retval #LOS_OK                                  Success to set the memory check level.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemNodeSizeCheck | LOS_MemCheckLevelGet
 */
extern UINT32 LOS_MemCheckLevelSet(UINT8 level);

/**
 * @ingroup los_memory
 * @brief Get the memory check level.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get the current memory check level.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None
 *
 * @retval #UINT8           The current memory check level.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemNodeSizeCheck | LOS_MemCheckLevelSet
 */
extern UINT8 LOS_MemCheckLevelGet(VOID);

/**
 * @ingroup los_memory
 * @brief Get the memory pool information.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get the current memory pool used information.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * <li>The size of the input parameter size can not be greater than the memory pool size that
 * specified at the second input parameter of LOS_MemInit.</li>
 * <li>The size of the input parameter size must be four byte-aligned.</li>
 * </ul>
 *
 * @param  pool    [IN] Pointer to the memory pool that contains the memory block to be allocated.
 * @param  status  [OUT] Structure contains the mem info.
 *
 * @retval #LOS_NOK          .
 * @retval #LOS_OK           .

 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 */
extern UINT32 LOS_MemInfoGet(VOID *pool, LOS_MEM_STATUS *status);
#else

/**
 * @ingroup los_memory
 * @brief calculate heap max free block size.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to calculate heap max free block size.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  pool          [IN] Pointer to memory pool.
 *
 * @retval #UINT32        The  max free block size.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemAlloc | LOS_MemRealloc | LOS_MemFree
 */
extern UINT32 LOS_MemGetMaxFreeBlkSize(VOID *pool);
#endif

/**
 * @ingroup los_memory
 * @brief Initialize dynamic memory.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to initialize the dynamic memory of a doubly linked list.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The size parameter value should match the following two conditions : 1) Be less than or equal to
 * the Memory pool size; 2) Be greater than the size of OS_MEM_MIN_POOL_SIZE.</li>
 * <li>Call this API when dynamic memory needs to be initialized during the startup of Huawei LiteOS.</li>
 * <li>The parameter input must be four byte-aligned.</li>
 * <li>The init area [pool, pool + size] should not conflict with other pools.</li>
 * </ul>
 *
 * @param pool         [IN] Starting address of memory.
 * @param size         [IN] Memory size.
 *
 * @retval #LOS_NOK    The dynamic memory fails to be initialized.
 * @retval #LOS_OK     The dynamic memory is successfully initialized.
 * @par Dependency:
 * <ul>
 * <li>los_memory.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see None.
 */
extern UINT32 LOS_MemInit(VOID *pool, UINT32 size);

/**
 * @ingroup los_memory
 * @brief Allocate dynamic memory.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to allocate a memory block of which the size is specified.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * <li>The size of the input parameter size can not be greater than the memory pool size
 * that specified at the second input parameter of LOS_MemInit.</li>
 * <li>The size of the input parameter size must be four byte-aligned.</li>
 * </ul>
 *
 * @param  pool    [IN] Pointer to the memory pool that contains the memory block to be allocated.
 * @param  size    [IN] Size of the memory block to be allocated (unit: byte).
 *
 * @retval #NULL          The memory fails to be allocated.
 * @retval #VOID*         The memory is successfully allocated with the starting address of
 *                        the allocated memory block returned.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemRealloc | LOS_MemAllocAlign | LOS_MemFree
 */
extern VOID *LOS_MemAlloc(VOID *pool, UINT32 size);

/**
 * @ingroup los_memory
 * @brief Free dynamic memory.
 *
 * @par Description:
 * <li>This API is used to free specified dynamic memory that has been allocated.</li>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * <li>The input mem parameter must be allocated by LOS_MemAlloc or LOS_MemAllocAlign or LOS_MemRealloc.</li>
 * </ul>
 *
 * @param  pool  [IN] Pointer to the memory pool that contains the dynamic memory block to be freed.
 * @param  mem   [IN] Starting address of the memory block to be freed.
 *
 * @retval #LOS_NOK          The memory block fails to be freed
 * @retval #LOS_OK           The memory block is successfully freed.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemAlloc | LOS_MemRealloc | LOS_MemAllocAlign
 */
extern UINT32 LOS_MemFree(VOID *pool, const VOID *mem);

/**
 * @ingroup los_memory
 * @brief Re-allocate a memory block.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to allocate a new memory block of which the size is specified by size if the original
 * memory block size is insufficient. The new memory block will copy the data in the original memory block of
 * which the address is specified by ptr. The size of the new memory block determines the maximum size of data
 * to be copied. After the new memory block is created, the original one is freed.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * <li>The input ptr parameter must be allocated by LOS_MemAlloc.</li>
 * <li>The size of the input parameter size can not be greater than the memory pool size that specified at the
 * second input parameter of LOS_MemInit.</li>
 * <li>The size of the input parameter size must be aligned as follows: 1) if the ptr is allocated by LOS_MemAlloc,
 * it must be four byte-aligned; 2) if the ptr is allocated by LOS_MemAllocAlign, it must be aligned with the size
 * of the input parameter uwBoundary of LOS_MemAllocAlign.</li>
 * </ul>
 *
 * @param  pool      [IN] Pointer to the memory pool that contains the original and new memory blocks.
 * @param  ptr       [IN] Address of the original memory block.
 * @param  size      [IN] Size of the new memory block.
 *
 * @retval #NULL          The memory fails to be re-allocated.
 * @retval #VOID*         The memory is successfully re-allocated with the starting address of the new memory block
 *                        returned.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemAlloc | LOS_MemAllocAlign | LOS_MemFree
 */
extern VOID *LOS_MemRealloc(VOID *pool, const VOID *ptr, UINT32 size);

/**
 * @ingroup los_memory
 * @brief Allocate aligned memory.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to allocate memory blocks of specified size and of which the starting addresses are aligned
 * on a specified boundary.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemInit.</li>
 * <li>The size of the input parameter size can not be greater than the memory pool size that specified at the second
 * input parameter of LOS_MemInit.</li>
 * <li>The alignment parameter value must be a power of 2 with the minimum value being 4.</li>
 * </ul>
 *
 * @param  pool      [IN] Pointer to the memory pool that contains the memory blocks to be allocated.
 * @param  size      [IN] Size of the memory to be allocated.
 * @param  boundary  [IN] Boundary on which the memory is aligned.
 *
 * @retval #NULL          The memory fails to be allocated.
 * @retval #VOID*         The memory is successfully allocated with the starting address of the allocated memory
 *                        returned.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemAlloc | LOS_MemRealloc | LOS_MemFree
 */
extern VOID *LOS_MemAllocAlign(VOID *pool, UINT32 size, UINT32 boundary);

/**
 * @ingroup los_memory
 * @brief Enable the Intergrity check when alloc and free memory.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to enable the Intergrity check when alloc and free memory.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemNodeSizeCheck | LOS_MemCheckLevelSet
 */
extern VOID LOS_MemEnableIntegrityCheck(VOID);

/**
 * @ingroup los_memory
 * @brief Disable the intergrity check when alloc and free memory.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to disable the intergrity check when alloc and free memory.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemNodeSizeCheck | LOS_MemCheckLevelSet
 */
extern VOID LOS_MemDisableIntegrityCheck(VOID);

/**
 * @ingroup los_memory
 * @brief Set lr address saved in memory node info.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to Set lr address saved in memory node info.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param lr [IN] The lr value need to be saved in memory node info.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 */
extern VOID LOS_MemSetLr(UINT32 lr);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_MEMORY_H */
