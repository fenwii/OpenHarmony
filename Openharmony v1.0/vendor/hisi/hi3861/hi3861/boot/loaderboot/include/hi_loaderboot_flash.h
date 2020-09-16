/*
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

#ifndef __HI_LOADERBOOT_FLASH_H__
#define __HI_LOADERBOOT_FLASH_H__
#include "hi_boot_rom.h"

/**
* @ingroup  hct_boot_flash
* @brief   Flash初始化
*
* @par 描述:
* 初始化Flash模块。
* @attention
* @retval #0      success.
* @retval #非0    failed.详见hi_errno.h
*
* @par Dependency:
* <ul><li>hi_loaderboot_flash.h: 该接口声明所在的头文件.</li></ul>
* @see
*/
hi_u32 hi_flash_init(hi_void);

/**
* @ingroup  hct_boot_flash
* @brief  flash数据删除
*
* @par 描述:
* 删除flash上的数据内容。
* @attention
*
* @param  flash_addr [IN] 类型 #hi_u32  待删除Flash的起始地址
* @param  flash_erase_size [IN] 类型 #hi_u32   待删除的Flash内容长度
*
* @retval #0      success.
* @retval #非0     failed.详见hi_errno.h
*
* @par Dependency:
* <ul><li>hi_loaderboot_flash.h: 该接口声明所在的头文件.</li></ul>
* @see  hi_flash_write|hi_flash_read
*/
hi_u32 hi_flash_erase(const hi_u32 flash_addr, hi_u32 flash_erase_size);

/**
* @ingroup  hct_boot_flash
* @brief  flash数据写入
*
* @par 描述:
* 向flash上的写入数据内容。
* @attention
* @li 只有在flash初始化时，配置flash回读比较空间才可以使用do_erase为HI_TRUE的选项。具体配置方法参考kernel下hi_flash_init实现。
*
* @param  flash_addr [IN] 类型 #hi_u32  Flash的起始地址
* @param  flash_write_size [IN] 类型 #hi_u32   待写入Flash的数据长度
* @param  flash_write_data [IN] 类型 #hi_u8*   待写入Flash的数据内容
* @param  do_erase [IN] 类型 #hi_bool  HI_FALSE:直接写FLASH HI_TRUE:写之前擦除操作区域对应的sector空间，用户操作空间写用户数据其它空间回写历史数据。
*
* @retval #0      success.
* @retval #非0     failed.详见hi_errno.h
*
* @par Dependency:
* <ul><li>hi_loaderboot_flash.h: 该接口声明所在的头文件.</li></ul>
* @see  hi_flash_erase|hi_flash_read
*/
hi_u32 hi_flash_write(hi_u32 flash_addr, hi_u32 flash_write_size, const hi_u8 *flash_write_data, hi_bool do_erase);

/**
* @ingroup  hct_boot_flash
* @brief  flash数据读取
*
* @par 描述:
* 从flash上的读取数据内容。
* @attention
*
* @param  flash_addr [IN] 类型 #hi_u32  Flash的起始地址
* @param  flash_read_size [IN] 类型 #hi_u32   待读取的数据长度
* @param  flash_read_data [OUT] 类型 #hi_u8*   数据内容缓冲区，用于存放从Flash中读取到的数据
*
* @retval #0      success.
* @retval #非0     failed.详见hi_errno.h
*
* @par Dependency:
* <ul><li>hi_loaderboot_flash.h: 该接口声明所在的头文件.</li></ul>
* @see  hi_flash_write|hi_flash_erase
*/
hi_u32 hi_flash_read(hi_u32 flash_addr, hi_u32 flash_read_size, hi_u8 *flash_read_data);
#endif

