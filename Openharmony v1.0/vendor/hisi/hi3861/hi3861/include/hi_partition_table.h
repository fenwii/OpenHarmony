/**
 * @file hi_partition_table.h
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

/** @defgroup iot_flash_partiton FLASH Partition Management
 *  @ingroup system
 */
#ifndef __HI_PARTITION_TABLE_H__
#define __HI_PARTITION_TABLE_H__
#include <hi_types.h>

#define HI_FLASH_PARTITON_MAX 12
/**
 * @ingroup iot_flash_partiton
 *
 * Partition entry ID. CNcomment:分区项ID。CNend
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
    hi_u32  addr    : 24;   /**< Flash partition address.The value is 16 MB.If the address is in reverse order,
                               the value is the end low address.CNcomment:Flash分区地址，限制为16MB，
                               如果为倒序，存放为结束的低地址值 CNend */
    hi_u32  id      : 7;    /**< Flash partition ID.CNcomment:Flash区ID.CNend  */
    hi_u32  dir     : 1;    /**< Flash area storage direction.0:regular.1: reversed.CNcomment:Flash区存放方向。
                               0：分区内容正序；1：倒序末地址 CNend */

    hi_u32  size    : 24;   /**< Size of the parition(Unit:byte).CNcomment:Flash分区大小（单位：byte）CNend */
    hi_u32  reserve : 8;    /**< Reserved. CNcomment:保留区CNend  */

    hi_u32  addition;      /**< Supplementary information about the flash partition, such as the address of the
                               Ram.CNcomment:Flash分区补充信息，如Ram对应地址等 CNend */
} hi_flash_partition_info;


/**
 *  @ingroup iot_flash_partiton
 *
 *  Flash partition table. CNcomment:Flash分区表。CNend
 */
typedef struct {
    hi_flash_partition_info table[HI_FLASH_PARTITON_MAX];  /**< Flash partition entry information.CNcomment:
                                                               Flash分区表项描述 CNend */
} hi_flash_partition_table;

/**
* @ingroup  iot_flash_partiton
* @brief  Obtains the flash partition table. CNcomment:获取Flash分区表。CNend
*
* @par 描述:
*           Obtains the flash partition table. CNcomment:获取Flash分区表。CNend
*
* @attention None
* @param None
*
* @retval #hi_flash_partition_table  Pointer to partition table information. CNcomment:分区表指针。CNend
* @par 依赖:
*            @li hi_partition_table.h：Describes flash partition APIs.
CNcomment:文件用于描述Flash分区相关接口。CNend
* @see  None
*/
hi_flash_partition_table *hi_get_partition_table(hi_void);

/**
* @ingroup  iot_flash_partiton
* @brief  Initializes the flash partition table. CNcomment:Flash分区表初始化。CNend
*
* @par 描述:
*           Initializes the flash partition table. CNcomment:Flash分区表初始化。CNend
*
* @attention None
* @param   None
*
* @retval #0      Success
* @retval #Other  Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_partition_table.h：Describes flash partition APIs.
CNcomment:文件用于描述Flash分区相关接口。CNend
* @see  None
*/
hi_u32 hi_flash_partition_init(hi_void);

/**
* @ingroup  iot_flash_partiton
* @brief  Get HiLink partition table'addr and size. CNcomment:获取HiLink分区地址和大小。CNend
*
* @par 描述:
*           Get HiLink partition table'addr and size. CNcomment:获取HiLink分区地址和大小。CNend
*
* @attention Call after hi_flash_partition_init. CNcomment:在hi_flash_partition_init之后调用。CNend
* @param  addr    [OUT] type #hi_u32*, Address of HiLink partition.CNcomment:HiLink分区地址。CNend
* @param  size     [OUT] type #hi_u32*, Size of HiLink partitioin, in bytes.CNcomment:HiLink分区大小，单位byte。CNend
*
* @retval #0      Success
* @retval #Other  Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_partition_table.h：Describes flash partition APIs.
CNcomment:文件用于描述Flash分区相关接口。CNend
* @see  None
*/
hi_u32 hi_get_hilink_partition_table(hi_u32 *addr, hi_u32 *size);

/**
* @ingroup  iot_flash_partiton
* @brief  Get HiLink PKI partition table'addr and size. CNcomment:获取HiLink PKI 分区地址和大小。CNend
*
* @par 描述:
*           Get HiLink PKI partition table'addr and size. CNcomment:获取HiLink PKI 分区地址和大小。CNend
*
* @attention Call after hi_flash_partition_init. CNcomment:在hi_flash_partition_init之后调用。CNend
* @param  addr    [OUT] type #hi_u32*, Address of HiLink PKI partition.CNcomment:HiLink PKI分区地址。CNend
* @param  size     [OUT] type #hi_u32*, Size of HiLink PKI partitioin, in bytes.CNcomment:HiLink PKI分区大小，单位byte。CNend
*
* @retval #0      Success
* @retval #Other  Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_partition_table.h：Describes flash partition APIs.
CNcomment:文件用于描述Flash分区相关接口。CNend
* @see  None
*/
hi_u32 hi_get_hilink_pki_partition_table(hi_u32 *addr, hi_u32 *size);


/**
* @ingroup  iot_flash_partiton
* @brief  Get Crash info partition table'addr and size. CNcomment:获取死机信息分区地址和大小。CNend
*
* @par 描述:
*           Get Crash info partition table'addr and size. CNcomment:获取死机信息分区地址和大小。CNend
*
* @attention Call after hi_flash_partition_init. CNcomment:在hi_flash_partition_init之后调用。CNend
* @param  addr    [OUT] type #hi_u32*, Address of Crash info partition.CNcomment:死机信息分区地址。CNend
* @param  size     [OUT] type #hi_u32*, Size of Crash info partitioin, in bytes.CNcomment:死机信息分区大小，单位byte。CNend
*
* @retval #0      Success
* @retval #Other  Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_partition_table.h：Describes flash partition APIs.
CNcomment:文件用于描述Flash分区相关接口。CNend
* @see  None
*/
hi_u32 hi_get_crash_partition_table(hi_u32 *addr, hi_u32 *size);

/**
* @ingroup  iot_flash_partiton
* @brief  Get File system partition table'addr and size. CNcomment:获取文件系统分区地址和大小。CNend
*
* @par 描述:
*           Get File system partition table'addr and size. CNcomment:获取文件系统分区地址和大小。CNend
*
* @attention Call after hi_flash_partition_init. CNcomment:在hi_flash_partition_init之后调用。CNend
* @param  addr    [OUT] type #hi_u32*, Address of File system partition.CNcomment:文件系统分区地址。CNend
* @param  size     [OUT] type #hi_u32*, Size of HiLink partitioin, in bytes.CNcomment:文件系统分区大小，单位byte。CNend
*
* @retval #0      Success
* @retval #Other  Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_partition_table.h：Describes flash partition APIs.
CNcomment:文件用于描述Flash分区相关接口。CNend
* @see  None
*/
hi_u32 hi_get_fs_partition_table(hi_u32 *addr, hi_u32 *size);

/**
* @ingroup  iot_flash_partiton
* @brief  Get Normal NV partition table'addr and size. CNcomment:获取非工厂区分区地址和大小。CNend
*
* @par 描述:
*           Get Normal NV partition table'addr and size. CNcomment:获取非工厂区分区地址和大小。CNend
*
* @attention Call after hi_flash_partition_init. CNcomment:在hi_flash_partition_init之后调用。CNend
* @param  addr    [OUT] type #hi_u32*, Address of Normal NV partition.CNcomment:非工厂区分区地址。CNend
* @param  size     [OUT] type #hi_u32*, Size of Normal NV partitioin, in bytes.CNcomment:非工厂区分区大小，单位byte。CNend
*
* @retval #0      Success
* @retval #Other  Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_partition_table.h：Describes flash partition APIs.
CNcomment:文件用于描述Flash分区相关接口。CNend
* @see  None
*/
hi_u32 hi_get_normal_nv_partition_table(hi_u32 *addr, hi_u32 *size);

/**
* @ingroup  iot_flash_partiton
* @brief  Get Normal NV backup partition table'addr and size. CNcomment:获取非工厂备份区分区地址和大小。CNend
*
* @par 描述:
*           Get Normal NV backup partition table'addr and size. CNcomment:获取非工厂备份区分区地址和大小。CNend
*
* @attention Call after hi_flash_partition_init. CNcomment:在hi_flash_partition_init之后调用。CNend
* @param  addr    [OUT] type #hi_u32*, Address of Normal NV backup partition.CNcomment:非工厂备份区分区地址。CNend
* @param  size     [OUT] type #hi_u32*, Size of Normal NV backup partitioin, in bytes.CNcomment:非工厂备份区分区大小，单位byte。CNend
*
* @retval #0      Success
* @retval #Other  Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_partition_table.h：Describes flash partition APIs.
CNcomment:文件用于描述Flash分区相关接口。CNend
* @see  None
*/
hi_u32 hi_get_normal_nv_backup_partition_table(hi_u32 *addr, hi_u32 *size);

/**
* @ingroup  iot_flash_partiton
* @brief  Get User's reserved NV partition table'addr and size. CNcomment:获取用户保留区分区地址和大小。CNend
*
* @par 描述:
*           Get User's reserved NV partition table'addr and size. CNcomment:获取用户保留区分区地址和大小。CNend
*
* @attention Call after hi_flash_partition_init. CNcomment:在hi_flash_partition_init之后调用。CNend
* @param  addr    [OUT] type #hi_u32*, Address of user partition.CNcomment:用户保留区分区地址。CNend
* @param  size     [OUT] type #hi_u32*, Size of user partitioin, in bytes.CNcomment:用户保留区分区大小，单位byte。CNend
*
* @retval #0      Success
* @retval #Other  Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_partition_table.h：Describes flash partition APIs.
CNcomment:文件用于描述Flash分区相关接口。CNend
* @see  None
*/
hi_u32 hi_get_usr_partition_table(hi_u32 *addr, hi_u32 *size);

/**
* @ingroup  iot_flash_partiton
* @brief  Get Factory bin'addr and size. CNcomment:获取产测BIN 地址和大小。CNend
*
* @par 描述:
*           Get Factory bin'addr and size.. CNcomment:获取产测BIN 地址和大小。CNend
*
* @attention Call after hi_flash_partition_init. CNcomment:在hi_flash_partition_init之后调用。CNend
* @param  addr    [OUT] type #hi_u32*, Address of factory bin.CNcomment:产测BIN 地址。CNend
* @param  size     [OUT] type #hi_u32*, Size of factory bin, in bytes.CNcomment:产测bin 大小，单位byte。CNend
*
* @retval #0      Success
* @retval #Other  Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_partition_table.h：Describes flash partition APIs.
CNcomment:文件用于描述Flash分区相关接口。CNend
* @see  None
*/
hi_u32 hi_get_factory_bin_partition_table(hi_u32 *addr, hi_u32 *size);

#endif

