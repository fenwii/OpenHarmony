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

#include <hi_types.h>

#define SFC_BUFFER_BASE_ADDRESS 0x400000

/** @defgroup iot_flash_partiton Partition Table APIs
* @ingroup  iot_flashboot
*/
/**
 * @ingroup iot_flash_partiton
 *
 * partition number.
 */
#define HI_FLASH_PARTITON_MAX 12

/**
 * @ingroup iot_flash_partiton
 *
 * partition ID.
 */
typedef enum {
    HI_FLASH_PARTITON_BOOT = 0,    /**< Boot partition ID.CNcomment:BOOT分区ID.CNend */
    HI_FLASH_PARTITON_FACTORY_NV,  /**< Factory NV working partition ID.CNcomment:工厂NV分区ID.CNend */
    HI_FLASH_PARTITON_NORMAL_NV,   /**< NORMAL NV partition ID.CNcomment:非工厂NV分区ID.CNend */
    HI_FLASH_PARTITON_NORMAL_NV_BACKUP,   /**< NORMAL backup NV partition ID.CNcomment:非工厂NV备份分区ID，必须和非工厂区连续.CNend */
    HI_FLASH_PARTITON_KERNEL_A,    /**< Kernel A running partition ID.CNcomment:内核A区ID.CNend */
    HI_FLASH_PARTITON_KERNEL_B,    /**< Kernel B runing partition ID.CNcomment:内核B区ID.CNend */
    HI_FLASH_PARTITON_HILINK,      /**< HILINK partition ID.CNcomment:HILINK分区ID(未使用HILINK可不需要).CNend */
    HI_FLASH_PARTITON_FILE_SYSTEM, /**< File system partition ID.CNcomment:文件系统区ID.CNend */
    HI_FLASH_PARTITON_USR_RESERVE, /**< User Reserved partition.CNcomment:用户保留区ID.CNend */
    HI_FLASH_PARTITON_HILINK_PKI,  /**< HiLink PKI partition.CNcomment: HILINK PKI证书ID(未使用HILINK可不需要). CNend */
    HI_FLASH_PARTITON_CRASH_INFO,  /**< Crash log partition.CNcomment:死机存储区ID.CNend */
    HI_FLASH_PARTITON_BOOT_BACK,   /**< Boot backup partition.CNcomment:备份boot区ID. CNend */
} hi_flash_partition_table_id;

/**
 *  @ingroup iot_flash_partiton
 *
 *  Flash partition management. CNcomment:Flash分区表项。CNend
 */
typedef struct {
    hi_u32  addr    : 24;   /* Flash partition address. The value is 16 MB. If the address is in reverse order,
                                the value is the end low address. CNcomment:Flash分区地址，限制为16MB，
                                如果为倒序，存放为结束的低地址值 CNend */
    hi_u32  id      : 7;    /* Flash partition ID. CNcomment:Flash区ID.CNend  */
    hi_u32  dir     : 1;    /* Flash area storage direction. 0:regular. 1: reversed.CNcomment:Flash区存放方向。
                                0：分区内容正序；1：倒序末地址 CNend */

    hi_u32  size    : 24;   /* Size of the parition(Unit:byte). CNcomment:Flash分区大小（单位：byte）CNend */
    hi_u32  reserve : 8;    /* Reserved. CNcomment:保留区CNend  */

    hi_u32  addition;       /* Supplementary information about the flash partition, such as the address of the Ram.
                               CNcomment:Flash分区补充信息，如Ram对应地址等 CNend */
} hi_flash_partition_info;

/**
 *  @ingroup iot_flash_partiton
 *  Flash partiton table.
 */
typedef struct {
    hi_flash_partition_info table[HI_FLASH_PARTITON_MAX]; /**< Flash分区表项描述  */
} hi_flash_partition_table;

/**
* @ingroup  iot_flash_partiton
* @brief  Initialize flash partition table. CNcomment:初始化Flash分区表。CNend
*
* @par 描述:
*           Initialize flash partition table. CNcomment:初始化Flash分区表。CNend
*
* @attention None.
* @param  None.
*
* @retval #HI_ERR_FAILURE Failure.
* @retval #HI_ERR_SUCCESS Success.
* @par 依赖:
*            @li hi_flashboot.h：Describes FlashBoot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  hi_get_partition_table。
*/
hi_u32 hi_flash_partition_init(hi_void);

/**
* @ingroup  iot_flash_partiton
* @brief  Get flash partition table. CNcomment:获取Flash分区表。CNend
*
* @par 描述:
*           Get flash partition table. CNcomment:获取Flash分区表。CNend
*
* @attention None.
* @param  None.
*
* @retval #HI_NULL Failure.
* @retval #Other Success.
* @par 依赖:
*            @li hi_flashboot.h：Describes FlashBoot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  hi_flash_partition_init。
*/
hi_flash_partition_table* hi_get_partition_table(hi_void);
