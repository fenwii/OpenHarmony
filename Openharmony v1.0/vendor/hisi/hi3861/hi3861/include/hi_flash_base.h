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

#ifndef __HI_FLASH_BASE_H__
#define __HI_FLASH_BASE_H__

#include <hi_types_base.h>

#define HI_FLASH_CMD_ADD_FUNC   0
#define HI_FLASH_CMD_GET_INFO   1  /**< IOCTL command ID for obtaining the flash information.
                                        The corresponding output parameter points to the hi_flash_info structure.
CNcomment:IOCTL获取Flash信息，对应出参指向结构体为hi_flash_info.CNend */
#define HI_FLASH_CMD_IS_BUSY    2  /**< IOCTL Obtain whether the flash memory is busy. The corresponding output
                                        parameter point type is hi_bool.
CNcomment:IOCTL获取Flash是否busy，对应出参指向类型为hi_bool CNend */

#define HI_FLASH_CHIP_ID_NUM    3
#define HI_FLASH_CAPACITY_ID    2

/**
* @ingroup  iot_flash
*
* Flash information obtaining structure, used to describe the return structure of the command ID HI_FLASH_CMD_GET_INFO.
CNcomment:Flash信息获取结构体，用于描述命令ID(HI_FLASH_CMD_GET_INFO)的返回结构体。CNend
*/
typedef struct {
    hi_char *name;                     /**< Flash name.CNcomment:Flash名字CNend  */
    hi_u8   id[HI_FLASH_CHIP_ID_NUM];  /**< Flash Id  */
    hi_u8   pad;
    hi_u32 total_size;                 /**< Flash totoal size (unit: byte).
                                          CNcomment:Flash总大小（单位：byte）CNend  */
    hi_u32 sector_size;                /**< Flash block size (unit: byte).
                                          CNcomment:Flash块大小（单位：byte）CNend */
} hi_flash_info;

#endif

