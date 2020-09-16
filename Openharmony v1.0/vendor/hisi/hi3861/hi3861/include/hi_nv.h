/**
 * @file hi_nv.h
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
 *
 * Description: NV items consist of the NV items in the factory partition and NV items in the normal partition.
 *              The NV items in the normal partition are classified into NV items in the reserved partition and
 *              NV items in the common partition. The values of NV items in the reserved partition won't change
 *              after OTA upgrade. \n
 * CNcomment:NV分为工厂区NV和非工厂区NV，非工厂区NV又分为保留区和普通区，保留区升级后保留NV值。CNend
 */

/** @defgroup iot_nv NV Management
 * @ingroup  system
 */
#ifndef __HI_NV_H__
#define __HI_NV_H__
#include <hi_types.h>

/**
* @ingroup  iot_nv
*
* Maximum length of an NV item (unit: byte). CNcomment:NV项最大长度（单位：byte）。CNend
*/
#define HNV_ITEM_MAXLEN (256 - 4)
#define PRODUCT_CFG_NV_REG_NUM_MAX               4

#define HI_FNV_DEFAULT_ADDR         0x8000
#define HI_NV_DEFAULT_TOTAL_SIZE    0x2000
#define HI_NV_DEFAULT_BLOCK_SIZE    0x1000

/**
* @ingroup  iot_nv
*
* Maximum number of registered hi_nv_register_change_nofity_proc functions.
CNcomment:hi_nv_register_change_nofity_proc注册函数个数最大值。CNend
*/
#define HI_NV_CHANGED_PROC_NUM  PRODUCT_CFG_NV_REG_NUM_MAX

/**
* @ingroup  iot_nv
* @brief Initialize Normal NV.CNcomment:非工厂区NV初始化。CNend
*
* @par 描述:
*           Initialize Normal NV.CNcomment:非工厂区NV初始化。CNend
*
* @attention Parameters are obtained from the partition table and cannot be set randomly.
CNcomment:参数从分区表中获取，禁止随意设置。CNend
* @param  addr          [IN] type #hi_u32，Flash address of the normal NV partition, corresponding to the flash
*                            address of the member #HI_FLASH_PARTITON_NORMAL_NV in the partition table.
CNcomment:非工厂区NV的FLASH地址，对应分区表成员#HI_FLASH_PARTITON_NORMAL_NV的FLASH地址。CNend
* @param  total_size    [IN] type #hi_u32，total size of normal NV.
CNcomment:非工厂区NV的总大小。CNend
* @param  block_size    [IN] type #hi_u32，block size of normal NV.
CNcomment:非工厂区NV的块大小。CNend
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_nv.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see hi_get_partition_table | hi_nv_read | hi_nv_write。
*/
HI_EAPI hi_u32 hi_nv_init(hi_u32 addr, hi_u32 total_size, hi_u32 block_size);

/**
* @ingroup  iot_nv
* @brief Set the normal NV value.CNcomment:设置非工厂区NV值。CNend
*
* @par 描述:
*           Set the normal NV value.CNcomment:设置非工厂区NV值。CNend
*
* @attention
*            @li Only a normal NV item can be operated.CNcomment:仅能操作非工厂区NV。CNend
*            @li This API is called only in a task and cannot be called in an interrupt.
CNcomment:仅支持任务中调用，不支持中断中调用。CNend
* @param  id      [IN] type #hi_u8，NV item ID, ranging from #HI_NV_NORMAL_ID_START to #HI_NV_NORMAL_USR_ID_END.
CNcomment:NV项ID，范围从#HI_NV_NORMAL_ID_START到#HI_NV_NORMAL_USR_ID_END。CNend
* @param  pdata   [IN] type #const hi_pvoid，NV item data.CNcomment:NV项数据。CNend
* @param  len     [IN] type #hi_u8，Length of an NV item (unit: byte). The len must be equal to the Length of
the real NV item data.CNcomment:NV项长度（单位：byte）。len必须和NV项的实际长度相等。CNend
* @param  flag   [IN] type #hi_u32，Reserve.CNcomment:保留参数。CNend
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_nv.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see hi_nv_read。
*/
HI_EAPI hi_u32 hi_nv_write(hi_u8 id, const hi_pvoid pdata, hi_u8 len, hi_u32 flag);

/**
* @ingroup  iot_nv
* @brief Read the normal NV value.CNcomment:读取非工厂区NV值。CNend
*
* @par 描述:
*           Read the normal NV value.CNcomment:读取非工厂区NV值。CNend
*
* @attention
*            @li Only a normal NV item can be operated.CNcomment:仅能操作非工厂区NV。CNend
*            @li This API is called only in a task and cannot be called in an interrupt.
CNcomment:仅支持任务中调用，不支持中断中调用。CNend
*
* @param  id      [IN] type #hi_u8，NV item ID, ranging from #HI_NV_NORMAL_ID_START to #HI_NV_NORMAL_USR_ID_END.
CNcomment:NV项ID，范围从#HI_NV_NORMAL_ID_START到#HI_NV_NORMAL_USR_ID_END。CNend
* @param  pdata   [OUT] type #const hi_pvoid，NV item data.CNcomment:NV项数据。CNend
* @param  len     [IN] type #hi_u8，Length of an NV item (unit: byte).  The len must be equal to the Length of
the real NV item data.CNcomment:NV项长度（单位：byte）。len必须和NV项的实际长度相等。CNend
* @param  flag   [IN] type #hi_u32，Reserve.CNcomment:保留参数。CNend
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_nv.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see hi_nv_write。
*/
HI_EAPI hi_u32 hi_nv_read(hi_u8 id, const hi_pvoid pdata, hi_u8 len, hi_u32 flag);

/**
* @ingroup  iot_nv
* @brief NV item change callback function.CNcomment:NV项变更回调函数。CNend
*
* @par 描述:
*           NV item change callback function.CNcomment:NV项变更回调函数。CNend
*
* @attention This API can be called only after the SAL is initialized.
CNcomment:在SAL初始化结束后才可以调用该接口。CNend
*
* @param  id      [IN] type #hi_u8，NV item ID, ranging from #HI_NV_NORMAL_ID_START to #HI_NV_NORMAL_USR_ID_END.
CNcomment:NV项ID，范围从#HI_NV_NORMAL_ID_START到#HI_NV_NORMAL_USR_ID_END。CNend
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_nv.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see None
*/
typedef hi_u32(*hi_nvm_changed_notify_f) (hi_u8 id);

/**
* @ingroup  iot_nv
* @brief Register the normal NV item change notification function.CNcomment:非工厂区NV项变更通知函数注册。CNend
*
* @par 描述:
*           Register the normal NV item change notification function.CNcomment:非工厂区NV项变更通知函数注册。CNend
*
* @attention
*           Only the change notification function for normal NV items can be registered.
*           The maximum number of registered functions is #HI_NV_CHANGED_PROC_NUM. If the number of registered functions
*           exceeds the maximum, an error code is returned.
CNcomment:仅支持非工厂NV项注册变更通知函数处理。注册个数上限为#HI_NV_CHANGED_PROC_NUM，如超过会返回错误码。CNend
*
* @param  min_id [IN] type #hi_u8，Minimum value of an NV item ID.CNcomment:NV项ID最小值。CNend
* @param  max_id [IN] type #hi_u8，Maximum value of an NV item ID.CNcomment:NV项ID最大值。CNend
* @param  func   [IN] type #hi_nvm_changed_notify_f，Handling function for NV item changes. That is, after an NV item
*                     is changed, the NV module automatically calls the registered API.
CNcomment:NV项改变的处理函数, 即NV项变更后，NV模块会自动调用该注册的接口。CNend
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_nv.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see None
*/
HI_EAPI hi_u32 hi_nv_register_change_notify_proc(hi_u8 min_id, hi_u8 max_id, hi_nvm_changed_notify_f func);

/**
* @ingroup  iot_nv
* @brief Initialize factory NV.CNcomment:工厂区NV初始化。CNend
*
* @par 描述:
*          Initialize factory NV.CNcomment: 工厂区NV初始化。CNend
*
* @attention The parameters cannot be set randomly and must match the product delivery plan.
CNcomment:参数不能随意配置，需要与产品出厂规划匹配。CNend
* @param  addr [IN] type #hi_u32，Start address of the NV factory partition in the flash. The address is planned by
*                   the factory and set by the macro #HI_FNV_DEFAULT_ADDR.
CNcomment:设置工厂区NV FLASH首地址，由出厂规划，宏定义HI_FNV_DEFAULT_ADDR 统一设置。CNend
* @param  total_size    [IN] type #hi_u32，total size of factory NV.
CNcomment:工厂区NV的总大小。CNend
* @param  block_size    [IN] type #hi_u32，block size of factory NV.
CNcomment:工厂区NV的块大小。CNend
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_nv.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see hi_factory_nv_write | hi_factory_nv_read。
*/
HI_EAPI hi_u32 hi_factory_nv_init(hi_u32 addr, hi_u32 total_size, hi_u32 block_size);

/**
* @ingroup  iot_nv
* @brief Set the NV value in the factory partition. CNcomment:设置工厂区NV值。CNend
*
* @par 描述:
*           Set the NV value in the factory partition.CNcomment:设置工厂区NV值。CNend
*
* @attention None
* @param  id    [IN] type #hi_u8，NV item ID, ranging from #HI_NV_FACTORY_ID_START to #HI_NV_FACTORY_USR_ID_END.
CNcomment:NV项ID，范围从#HI_NV_FACTORY_ID_START到#HI_NV_FACTORY_USR_ID_END。CNend
* @param  pdata [IN] type #hi_pvoid，NV item data.CNcomment:NV项数据。CNend
* @param  len   [IN] type #hi_u8，Length of an NV item (unit: byte). The len must be equal to the Length of
the real NV item data.CNcomment:NV项长度（单位：byte）。len必须和NV项的实际长度相等。CNend
* @param  flag   [IN] type #hi_u32，Reserve.CNcomment:保留参数。CNend
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_nv.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see hi_factory_nv_read。
*/
HI_EAPI hi_u32 hi_factory_nv_write(hi_u8 id, hi_pvoid pdata, hi_u8 len, hi_u32 flag);

/**
* @ingroup  iot_nv
* @brief Read the NV value in the factory partition.CNcomment:读取工厂区NV值。CNend
*
* @par 描述:
*           Read the NV value in the factory partition.CNcomment:读取工厂区NV值。CNend
*
* @attention None
*
* @param  id      [IN] type #hi_u8，NV item ID, ranging from #HI_NV_NORMAL_ID_START to #HI_NV_NORMAL_USR_ID_END.
CNcomment:NV项ID，范围从#HI_NV_NORMAL_ID_START到#HI_NV_NORMAL_USR_ID_END。CNend
* @param  pdata   [OUT] type #hi_pvoid，NV item data.CNcomment:NV项数据。CNend
* @param  len     [IN] type #hi_u8，Length of an NV item (unit: byte). The len must be equal to the Length of
the real NV item data.CNcomment:NV项长度（单位：byte）。len必须和NV项的实际长度相等。CNend
* @param  flag    [IN] type #hi_u32，Reserve.CNcomment:保留参数。CNend
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_nv.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see hi_factory_nv_write。
*/
HI_EAPI hi_u32 hi_factory_nv_read(hi_u8 id, hi_pvoid pdata, hi_u8 len, hi_u32 flag);

/**
* @ingroup  iot_nv
* @brief refresh backup nv, always used after finish factory test.
CNcomment:更新原始备份区NV，常用于产测完成后。CNend
*
* @par 描述:
*           refresh backup nv, always used after finish factory test.
CNcomment:更新原始备份区NV，常用于产测完成后。CNend
*
* @attention should refresh backup nv if factory test modified nv.
CNcomment: 如果产测有修改NV参数，应该在产测完成后同步刷新备份区NV。CNend
*
* @param  None
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_nv.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
*/
HI_EAPI hi_u32 hi_nv_refresh_backup(hi_void);

/**
* @ingroup  iot_nv
* @brief restore nv by oringinal backup nv.
CNcomment: 使用原始备份NV 覆盖当前NV，常用于恢复出厂设置。CNend
*
* @par 描述:
*           restore nv by oringinal backup nv.
CNcomment:使用原始备份NV 覆盖当前NV，常用于恢复出厂设置。CNend
*
* @attention should reset system after restore nv. only restore normal nv, not include factory nv.
CNcomment: 使用备份NV 覆盖原始NV后，须重启系统。
仅覆盖工作区NV，不包括工厂区NV。CNend
*
* @param  None
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_nv.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
*/
HI_EAPI hi_u32 hi_nv_restore_by_backup(hi_void);

#endif
