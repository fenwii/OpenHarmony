/**
 * @file hi_men.h
 *
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @defgroup iot_mem  Memory
 * @ingroup osa
 */

#ifndef __HI_MEM_H__
#define __HI_MEM_H__
#include <hi_types_base.h>

/**
 * @ingroup iot_mem
 * Overall memory information.CNcomment:整体内存信息。CNend
 */
typedef struct {
    hi_u32 total;                /**< Total space of the memory pool (unit: byte).
                                    CNcomment:内存池总大小（单位：byte）CNend */
    hi_u32 used;                 /**< Used space of the memory pool (unit: byte).
                                    CNcomment:内存池已经使用大小（单位：byte）CNend */
    hi_u32 free;                 /**< Free space of the memory pool (unit: byte).
                                    CNcomment:内存池剩余空间（单位：byte）CNend */
    hi_u32 free_node_num;        /**< Number of free nodes in the memory pool.
                                    CNcomment:内存池剩余空间节点个数 CNend */
    hi_u32 used_node_num;        /**< Number of used nodes in the memory pool.
                                    CNcomment:内存池已经使用的节点个数 CNend */
    hi_u32 max_free_node_size;   /**< Maximum size of the node in the free space of the memory pool (unit: byte).
                                    CNcomment:内存池剩余空间节点中最大节点的大小（单位：byte）CNend */
    hi_u32 malloc_fail_count;    /**< Number of memory application failures.CNcomment:内存申请失败计数 CNend */
    hi_u32 peek_size;            /**< Peak memory usage of the memory pool.CNcomment:内存池使用峰值CNend */
    hi_u32 total_lmp;            /**< Total space of the little memory pool (unit: byte).
                                    CNcomment:小内存池总大小（单位：byte）CNend */
    hi_u32 used_lmp;             /**< Used space of the little memory pool (unit: byte).
                                    CNcomment:小内存池已经使用大小（单位：byte）CNend */
    hi_u32 free_lmp;             /**< Free space of the little memory pool (unit: byte).
                                    CNcomment:小内存池剩余空间（单位：byte）CNend */
} hi_mdm_mem_info;

typedef struct {
    hi_u32 pool_addr;
    hi_u32 pool_size;
    hi_u32 fail_count;
    hi_u32 peek_size;
    hi_u32 cur_use_size;
} hi_mem_pool_crash_info;

/**
* @ingroup  iot_mem
* @brief  Dynamically applies for memory.CNcomment:动态申请内存。CNend
*
* @par 描述:
*           Dynamically applies for memory.CNcomment:动态申请内存。CNend
*
* @attention None
* @param  mod_id  [IN] type #hi_u32，ID of the called module.CNcomment:调用模块ID。CNend
* @param  size    [IN] type #hi_u32，Requested memory size (unit: byte)
CNcomment:申请内存大小（单位：byte）。CNend
*
* @retval #>0 Success
* @retval #HI_NULL   Failure. The memory is insufficient.
* @par 依赖:
*            @li hi_mem.h：Describes memory APIs.CNcomment:文件用于描述内存相关接口。CNend
* @see  hi_free。
*/
hi_pvoid hi_malloc(hi_u32 mod_id, hi_u32 size);

/**
* @ingroup  iot_mem
* @brief  Releases the memory that is dynamically applied for.CNcomment:释放动态申请的内存。CNend
*
* @par 描述:
*          Releases the memory that is dynamically applied for.CNcomment:释放动态申请的内存。CNend
*
* @attention None
* @param  mod_id  [IN] type #hi_u32，ID of the called module.CNcomment:调用模块ID。CNend
* @param  addr    [IN] type #hi_pvoid，Start address of the requested memory. The validity of the address is ensured
*                 by the caller.CNcomment:所申请内存的首地址，地址合法性由调用者保证。CNend
*
* @retval None
* @par 依赖:
*            @li hi_mem.h：Describes memory APIs.CNcomment:文件用于描述内存相关接口。CNend
* @see  hi_malloc。
*/
hi_void hi_free(hi_u32 mod_id, const hi_pvoid addr);

/**
* @ingroup  iot_mem
* @brief  Obtains the memory information.CNcomment:获取内存信息。CNend
*
* @par 描述:
*           Obtains the memory information.CNcomment:获取内存信息。CNend
*
* @attention None
* @param  mem_inf [OUT] type #hi_mdm_mem_info*，Overall memory information.CNcomment:整体内存信息。CNend
*
* @retval #0      Success.
* @retval #Other  Failure, for details, see hi_errno.h
* @par 依赖:
*            @li hi_mem.h：Describes memory APIs.CNcomment:文件用于描述内存相关接口。CNend
* @see  None
*/
hi_u32 hi_mem_get_sys_info(HI_OUT hi_mdm_mem_info *mem_inf);

/**
* @ingroup  iot_mem
* @brief  Obtains memory information, used in a crash process.
CNcomment:获取内存信息，死机流程中使用。CNend
*
* @par 描述:
*           Obtains memory information, used in a crash process. When the board is reset due to a memory exception,
*           if hi_mem_get_sys_info is used to obtain memory information, another exception may occur. In this case,
*           use hi_mem_get_sys_info_crash instead.CNcomment:获取内存信息，死机流程中使用。当内存异常导致单板复位时，
如果通过hi_mem_get_sys_info获取内存信息可能再次产生异常，此时应该使用hi_mem_get_sys_info_crash。CNend
*
* @attention None
*
* @retval #hi_mem_pool_crash_info   Memory information.CNcomment:内存信息。CNend
*
* @par 依赖:
*            @li hi_mem.h：Describes memory APIs.CNcomment:文件用于描述内存相关接口。CNend
* @see  None
*/
HI_CONST hi_mem_pool_crash_info *hi_mem_get_sys_info_crash(hi_void);

#endif
