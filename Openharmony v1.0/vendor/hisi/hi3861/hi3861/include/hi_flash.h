/*
 * @file hi_flash.h
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

/** @defgroup iot_flash  Flash
 *  @ingroup drivers
 */
#ifndef __HI_FLASH_H__
#define __HI_FLASH_H__

#include <hi_types.h>
#include <hi_flash_base.h>
/**
* @ingroup  iot_flash
* @brief  Reads the flash data to the specified cache. CNcomment:读出Flash数据到指定缓存区域。CNend
*
* @par 描述:
*           Reads the flash data to the specified cache. CNcomment:读出Flash数据到指定缓存区域。CNend
*
* @attention None
* @param  flash_offset      [IN] type #const hi_u32，Offset of the flash address.CNcomment:指定的Flash地址偏移。CNend
* @param  size              [IN] type #const hi_u32，Read length (unit: byte).
CNcomment:指定读取的长度（单位：byte）。CNend
* @param  ram_data          [OUT] type #hi_u8*，Destination cache address.CNcomment:目的缓存地址。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_flash.h：FLASH driver APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_u32 hi_flash_read(const hi_u32 flash_offset, const hi_u32 size, hi_u8 *ram_data);

/**
* @ingroup  iot_flash
* @brief  Writes data to the specified flash partition.CNcomment:把数据写入指定的Flash区。CNend
*
* @par 描述:
*           Writes data to the specified flash partition.CNcomment:把数据写入指定的Flash区域。CNend
*
* @attention
*           @li Restriction protection for the relative address of the flash memory.
CNcomment:Flash相对地址的限制保护。CNend
*           @li The number of flash erase times must comply with the device data sheet.
CNcomment:Flash擦写次数限制。CNend
*           @li Determine whether to erase the flash before the write based on the actual control scenario.
CNcomment:根据用户实际控制场景决定是否先擦后写。CNend
* @param  flash_offset    [IN] type #const hi_u32，Offset address for writing data to the flash memory.
CNcomment:指定写入Flash偏移地址。CNend
* @param  size            [IN] type #hi_u32，Length of the data to be written (unit: byte).
CNcomment:需要写入的长度（单位：byte）。CNend
* @param  ram_data        [IN] type #const hi_u8*，Cache address of the data to be written.
CNcomment:需要写入的数据的缓存地址。CNend
* @param  do_erase        [IN] type #hi_bool，HI_FALSE: Write data to the flash memory directly.
*                                             HI_TRUE:  Erase the sector space before write.
*                         The user data is written to the user operation space and the historical
*                         data is written back to other spaces.CNcomment:表示是否自动擦除并覆盖写入。
*                         @li HI_TRUE：本接口中先擦后写。
*                         @li HI_FALSE：用户已经擦除本接口，可直接写入。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_flash.h：FLASH driver APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_u32 hi_flash_write(const hi_u32 flash_offset, hi_u32 size, const hi_u8 *ram_data, hi_bool do_erase);

/**
* @ingroup  iot_flash
* @brief  Erases the data in the specified flash partition.CNcomment:把指定的Flash区域数据擦除。CNend
*
* @par 描述:
*           Erases the data in the specified flash partition.CNcomment:把指定的Flash区域数据擦除。CNend
*
* @attention
*           @li Restriction protection for the relative address of the flash memory.
CNcomment:Flash相对地址的限制保护。CNend
*           @li The number of flash erase times must comply with the device data sheet.
CNcomment:Flash擦写次数限制。CNend
*
* @param  flash_offset    [IN] type #const hi_u32，Address offset of the flash memory to be erased.
CNcomment:指定要擦除Flash的地址偏移。CNend
* @param  size            [IN] type #const hi_u32，Length of the data to be erased (unit: byte).
*                         The value must be a multiple of 4 KB.
CNcomment:需要擦除的长度（单位：byte），必须是4K的倍数。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_flash.h：FLASH driver APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_u32 hi_flash_erase(const hi_u32 flash_offset, const hi_u32 size);

/**
* @ingroup  iot_flash
* @brief   Initializes the flash device. CNcomment:初始化Flash设备。CNend
*
* @par 描述:
*           Initializes the flash device. CNcomment:初始化Flash设备。CNend
*
* @attention Initialize the flash module during system boot.
CNcomment:Flash模块初始化，一般在系统启动时调用。CNend
* @param  None
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_flash.h：FLASH driver APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_u32 hi_flash_init(hi_void);

/**
* @ingroup  iot_flash
* @brief  Deinitializes the flash device.CNcomment:去初始化Flash设备。CNend
*
* @par 描述:
*           Deinitializes the flash device.CNcomment:去初始化Flash设备。CNend
*
* @attention None
* @param  None
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_flash.h：FLASH driver APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_u32 hi_flash_deinit(hi_void);
/**
* @ingroup  iot_flash
* @brief  Sets or reads flash information.CNcomment:获取Flash信息。CNend
*
* @par 描述:
*          Sets or reads flash information.CNcomment:获取Flash信息。CNend
*
* @attention None
* @param  cmd             [IN]     type #hi_u16，Command ID, currently supports HI_FLASH_CMD_GET_INFO and
*                         HI_FLASHI_FLASH_CMD_IS_BUSY.
CNcomment:命令ID，当前支持HI_FLASH_CMD_GET_INFO 和 HI_FLASH_CMD_IS_BUSY。CNend
* @param  data            [IN/OUT] type #hi_void*, Information set or obtained. cmd is HI_FLASH_CMD_GET_INFO, data is
*                         a pointer of hi_flash_info struct; cmd is HI_FLASH_CMD_IS_BUSY, data is a pointer of type
*                         hi_bool.CNcomment:数据信息，cmd参数为HI_FLASH_CMD_GET_INFO，data为hi_flash_info结构指针；
*                         cmd为HI_FLASH_CMD_IS_BUSY，data为hi_bool类型指针。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_flash.h：FLASH driver APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_u32 hi_flash_ioctl(HI_IN hi_u16 cmd, HI_INOUT hi_void *data);

#endif

