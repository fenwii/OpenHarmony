/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
 * Description: LiteOS memory Module Implementation
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

#ifndef _LOS_MEMBOX_H
#define _LOS_MEMBOX_H

#include "los_config.h"
#if (LOSCFG_PLATFORM_EXC == YES)
#include "los_memcheck.h"
#endif

#if (LOSCFG_MEMBOX == YES)

#define BOX_ALIGN_8                   0x80000000
/* ----------------------------------------------------------------------------
 *      Global Functions
 * --------------------------------------------------------------------------- */
/**
 * @ingroup los_membox
 * Define whether to check the address validity
 */
#if (LOSCFG_PLATFORM_EXC == YES)
#define LOS_MEMBOX_CHECK
extern UINT8 g_memMang[];
#endif

typedef struct tagMemBoxCB {
    UINT32  uwMaxBlk;
    UINT32  uwBlkCnt;
    UINT32  uwBlkSize;                  /* Memory block size                       */
}OS_MEMBOX_S;

typedef OS_MEMBOX_S *OS_MEMBOX_S_P;

#ifdef LOS_MEMBOX_CHECK
#define LOS_MEMBOX_MAGIC_SIZE    4
#else
#define LOS_MEMBOX_MAGIC_SIZE    0
#endif

/**
 * @ingroup los_membox
 * @brief Initialize a memory pool.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to initialize a memory pool.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The boxSize parameter value should match the following two conditions :</li>
 * <li>1) Be less than or equal to the Memory pool size; 2) Be greater than the size of LOS_MEMBOX_INFO.</li>
 * </ul>
 *
 * @param boxMem    [IN] Memory pool address.
 * @param boxSize   [IN] Memory pool size.
 * @param blkSize   [IN] Memory block size.
 *
 * @retval #LOS_NOK   The memory pool fails to be initialized.
 * @retval #LOS_OK    The memory pool is successfully initialized.
 * @par Dependency:
 * <ul>
 * <li>los_membox.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see None.
 */
extern UINT32 LOS_MemboxInit(VOID *boxMem, UINT32 boxSize, UINT32 blkSize);

/**
 * @ingroup los_membox
 * @brief Request a memory block.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to request a memory block.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemboxInit.</li>
 * </ul>
 *
 * @param boxMem     [IN] Memory pool address.
 *
 * @retval #VOID*      The request is accepted, and return a memory block address.
 * @retval #NULL       The request fails.
 * @par Dependency:
 * <ul>
 * <li>los_membox.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see LOS_MemboxFree
 */
extern VOID *LOS_MemboxAlloc(VOID *boxMem);

/**
 * @ingroup los_membox
 * @brief Free a memory block.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to free a memory block.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemboxInit.</li>
 * <li>The input pBox parameter must be allocated by LOS_MemboxAlloc.</li>
 * </ul>
 *
 * @param boxMem     [IN] Memory pool address.
 * @param box        [IN] Memory block address.
 *
 * @retval #LOS_NOK   This memory block fails to be freed.
 * @retval #LOS_OK    This memory block is successfully freed.
 * @par Dependency:
 * <ul>
 * <li>los_membox.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see LOS_MemboxAlloc
 */
extern UINT32 LOS_MemboxFree(const VOID *boxMem, VOID *box);

/**
 * @ingroup los_membox
 * @brief Clear a memory block.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to set the memory block value to be 0.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>The input pool parameter must be initialized via func LOS_MemboxInit.</li>
 * <li>The input pBox parameter must be allocated by LOS_MemboxAlloc.</li>
 * </ul>
 *
 * @param boxMem     [IN] Memory pool address.
 * @param box        [IN] Memory block address.
 *
 * @retval VOID
 * @par Dependency:
 * <ul>
 * <li>los_membox.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see None.
 */
extern VOID LOS_MemboxClr(const VOID *boxMem, VOID *box);


/**
 * @ingroup los_membox
 * @brief calculate membox information.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to calculate membox information.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>One parameter of this interface is a pointer, it should be a correct value, otherwise, the system may be
 * abnormal.</li>
 * </ul>
 *
 * @param  boxMem       [IN]  Type  #VOID*   Pointer to the calculate membox.
 * @param  maxBlk       [OUT] Type  #UINT32* Record membox max block.
 * @param  blkCnt       [OUT] Type  #UINT32* Record membox block count alreay allocated.
 * @param  blkSize      [OUT] Type  #UINT32* Record membox block size.
 *
 * @retval #LOS_OK        The heap status calculate success.
 * @retval #LOS_NOK       The membox  status calculate with some error.
 * @par Dependency:
 * <ul><li>los_memory.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MemAlloc | LOS_MemRealloc | LOS_MemFree
 */
extern UINT32 LOS_MemboxStatisticsGet(const VOID *boxMem, UINT32 *maxBlk, UINT32 *blkCnt, UINT32 *blkSize);
#endif
#endif
