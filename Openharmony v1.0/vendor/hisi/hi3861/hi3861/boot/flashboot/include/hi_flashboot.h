/*
 * @file hi_flashboot.h
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

/** @defgroup iot_flashboot Flash Boot */
#ifndef _HI_FLASHBOOT_H_
#define _HI_FLASHBOOT_H_

#include <hi_types.h>
#include <hi_boot_rom.h>

/** @defgroup iot_nv NV Management APIs
* @ingroup  iot_flashboot
*/
/**
* @ingroup  iot_nv
* Maximum length of an NV item (unit: byte). CNcomment:NV项最大长度（单位：byte）。CNend
*/
#define HNV_ITEM_MAXLEN             (256 - 4)

/**
* @ingroup  iot_nv
*/
#define PRODUCT_CFG_NV_REG_NUM_MAX  20

/**
* @ingroup  iot_nv
*/
#define HI_FNV_DEFAULT_ADDR         0x8000

/**
* @ingroup  iot_nv
*/
#define HI_NV_DEFAULT_TOTAL_SIZE    0x2000

/**
* @ingroup  iot_nv
*/
#define HI_NV_DEFAULT_BLOCK_SIZE    0x1000

/**
* @ingroup  iot_nv
*
* Factory NV area user area end ID. CNcomment:工厂区NV结束ID。CNend
*/
#define HI_NV_FACTORY_USR_ID_END    0x20

/**
* @ingroup  iot_nv
*/
#define  HI_NV_FTM_FLASH_PARTIRION_TABLE_ID  0x02

/**
* @ingroup  iot_nv
* @brief Initializes NV management in the factory partition.CNcomment:工厂区NV初始化。CNend
*
* @par 描述:
*          Initializes NV management in the factory partition.CNcomment: 工厂区NV管理初始化。CNend
*
* @attention The parameters cannot be set randomly and must match the product delivery plan.
CNcomment:参数不能随意配置，需要与产品出厂规划匹配。CNend
* @param  addr [IN] type #hi_u32，Start address of the NV factory partition in the flash. The address is planned by
*                   the factory and set by the boot macro #FACTORY_NV_ADDR.
CNcomment:设置工厂区NV FLASH首地址，由出厂规划，boot宏定义FACTORY_NV_ADDR 统一设置。CNend
* @param  total_size    [IN] type #hi_u32，total size of factory NV.
CNcomment:工厂区NV的总大小。CNend
* @param  block_size    [IN] type #hi_u32，block size of factory NV.
CNcomment:工厂区NV的块大小。CNend
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_flashboot.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see hi_factory_nv_write | hi_factory_nv_read。
*/
hi_u32 hi_factory_nv_init(hi_u32 addr, hi_u32 total_size, hi_u32 block_size);

/**
* @ingroup  iot_nv
* @brief Sets the NV value in the factory partition. CNcomment:设置工厂区NV值。CNend
*
* @par 描述:
*           Sets the NV value in the factory partition.CNcomment:设置工厂区NV值。CNend
*
* @attention None
* @param  id    [IN] type #hi_u8，NV item ID, ranging from #HI_NV_FACTORY_ID_START to #HI_NV_FACTORY_USR_ID_END.
CNcomment:NV项ID，范围从#HI_NV_FACTORY_ID_START到#HI_NV_FACTORY_USR_ID_END。CNend
* @param  pdata [IN] type #hi_pvoid，NV item data.CNcomment:NV项数据。CNend
* @param  len   [IN] type #hi_u8，Length of an NV item (unit: byte). The maximum value is #HNV_ITEM_MAXLEN.
CNcomment:NV项长度（单位：byte），最大不允许超过HNV_ITEM_MAXLEN。CNend
* @param  flag   [IN] type #hi_u32，Reserve.CNcomment:保留参数。CNend
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_flashboot.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see hi_factory_nv_read。
*/
hi_u32 hi_factory_nv_write(hi_u8 id, hi_pvoid pdata, hi_u8 len, hi_u32 flag);

/**
* @ingroup  iot_nv
* @brief Reads the NV value in the factory partition.CNcomment:读取工厂区NV值。CNend
*
* @par 描述:
*           Reads the NV value in the factory partition.读取工厂区NV值。CNend
*
* @attention None
*
* @param  id      [IN] type #hi_u8，NV item ID, ranging from #HI_NV_NORMAL_ID_START to #HI_NV_NORMAL_USR_ID_END.
CNcomment:NV项ID，范围从#HI_NV_NORMAL_ID_START到#HI_NV_NORMAL_USR_ID_END。CNend
* @param  pdata   [IN] type #hi_pvoid，NV item data.CNcomment:NV项数据。CNend
* @param  len     [IN] type #hi_u8，Length of an NV item (unit: byte). The maximum value is HNV_ITEM_MAXLEN.
CNcomment:NV项长度（单位：byte），最大不允许超过HNV_ITEM_MAXLEN。CNend
* @param  flag    [IN] type #hi_u32，Reserve.CNcomment:保留参数。CNend
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_flashboot.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see hi_factory_nv_write。
*/
hi_u32 hi_factory_nv_read(hi_u8 id, hi_pvoid pdata, hi_u8 len, hi_u32 flag);

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
    hi_u32  addr   : 24;   /* Flash partition address. The value is 16 MB. If the address is in reverse order,
                               the value is the end low address. CNcomment:Flash分区地址，限制为16MB，
                               如果为倒序，存放为结束的低地址值 CNend */
    hi_u32  id     : 7;    /* Flash partition ID. CNcomment:Flash区ID.CNend  */
    hi_u32  dir    : 1;    /* Flash area storage direction. 0:regular. 1: reversed.CNcomment:Flash区存放方向。
                               0：分区内容正序；1：倒序末地址 CNend */

    hi_u32  size   : 24;   /* Size of the parition(Unit:byte). CNcomment:Flash分区大小（单位：byte）CNend */
    hi_u32  reserve : 8;   /* Reserved. CNcomment:保留区CNend  */

    hi_u32  addition;      /* Supplementary information about the flash partition, such as the address of the Ram.
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

/** @defgroup iot_efuse eFuse APIs
* @ingroup iot_flashboot
*/
/**
* @ingroup  iot_efuse
*
* Efuse ID.
*/
typedef enum {
    HI_EFUSE_CHIP_RW_ID = 0,
    HI_EFUSE_DIE_RW_ID = 1,
    HI_EFUSE_PMU_FUSE1_RW_ID = 2,
    HI_EFUSE_PMU_FUSE2_RW_ID = 3,
    HI_EFUSE_FLASH_ENCPY_CNT3_RW_ID = 4,
    HI_EFUSE_FLASH_ENCPY_CNT4_RW_ID = 5,
    HI_EFUSE_FLASH_ENCPY_CNT5_RW_ID = 6,
    HI_EFUSE_DSLEEP_FLAG_RW_ID = 7,
    HI_EFUSE_ROOT_PUBKEY_RW_ID = 8,
    HI_EFUSE_ROOT_KEY_WO_ID = 9,
    HI_EFUSE_CUSTOMER_RSVD0_RW_ID = 10,
    HI_EFUSE_SUBKEY_CAT_RW_ID = 11,
    HI_EFUSE_ENCRYPT_FLAG_RW_ID = 12,
    HI_EFUSE_SUBKEY_RSIM_RW_ID = 13,
    HI_EFUSE_START_TYPE_RW_ID = 14,
    HI_EFUSE_JTM_RW_ID = 15,
    HI_EFUSE_UTM0_RW_ID = 16,
    HI_EFUSE_UTM1_RW_ID = 17,
    HI_EFUSE_UTM2_RW_ID = 18,
    HI_EFUSE_SDC_RW_ID = 19,
    HI_EFUSE_RSVD0_RW_ID = 20,
    HI_EFUSE_KDF2ECC_HUK_DISABLE_RW_ID = 21,
    HI_EFUSE_SSS_CORNER_RW_ID = 22,
    HI_EFUSE_UART_HALT_INTERVAL_RW_ID = 23,
    HI_EFUSE_TSENSOR_RIM_RW_ID = 24,
    HI_EFUSE_CHIP_BK_RW_ID = 25,
    HI_EFUSE_IPV4_MAC_ADDR_RW_ID = 26,
    HI_EFUSE_IPV6_MAC_ADDR_RW_ID = 27,
    HI_EFUSE_PG2GCCKA0_TRIM0_RW_ID = 28,
    HI_EFUSE_PG2GCCKA1_TRIM0_RW_ID = 29,
    HI_EFUSE_NVRAM_PA2GA0_TRIM0_RW_ID = 30,
    HI_EFUSE_NVRAM_PA2GA1_TRIM0_RW_ID = 31,
    HI_EFUSE_PG2GCCKA0_TRIM1_RW_ID = 32,
    HI_EFUSE_PG2GCCKA1_TRIM1_RW_ID = 33,
    HI_EFUSE_NVRAM_PA2GA0_TRIM1_RW_ID = 34,
    HI_EFUSE_NVRAM_PA2GA1_TRIM1_RW_ID = 35,
    HI_EFUSE_PG2GCCKA0_TRIM2_RW_ID = 36,
    HI_EFUSE_PG2GCCKA1_TRIM2_RW_ID = 37,
    HI_EFUSE_NVRAM_PA2GA0_TRIM2_RW_ID = 38,
    HI_EFUSE_NVRAM_PA2GA1_TRIM2_RW_ID = 39,
    HI_EFUSE_TEE_BOOT_VER_RW_ID = 40,
    HI_EFUSE_TEE_KERNEL_VER_RW_ID = 41,
    HI_EFUSE_TEE_SALT_RW_ID = 42,
    HI_EFUSE_FLASH_ENCPY_CNT0_RW_ID = 43,
    HI_EFUSE_FLASH_ENCPY_CNT1_RW_ID = 44,
    HI_EFUSE_FLASH_ENCPY_CNT2_RW_ID = 45,
    HI_EFUSE_FLASH_ENCPY_CFG_RW_ID = 46,
    HI_EFUSE_FLASH_SCRAMBLE_EN_RW_ID = 47,
    HI_EFUSE_USER_FLASH_IND_RW_ID = 48,
    HI_EFUSE_RF_PDBUFFER_GCAL_RW_ID = 49,
    HI_EFUSE_CUSTOMER_RSVD1_RW_ID = 50,
    HI_EFUSE_DIE_2_RW_ID = 51,
    HI_EFUSE_SEC_BOOT_RW_ID = 52,
    HI_EFUSE_IDX_MAX,
} hi_efuse_idx;

/**
* @ingroup  iot_efuse
*
* Efuse Lock ID.
*/
typedef enum {
    HI_EFUSE_LOCK_CHIP_ID = 0,
    HI_EFUSE_LOCK_DIE_ID = 1,
    HI_EFUSE_LOCK_PMU_FUSE1_FUSE2_START_TYPE_TSENSOR_ID = 2,
    HI_EFUSE_LOCK_ROOT_PUBKEY_ID = 3,
    HI_EFUSE_LOCK_ROOT_KEY_ID = 4,
    HI_EFUSE_LOCK_CUSTOMER_RSVD0_ID = 5,
    HI_EFUSE_LOCK_SUBKEY_CAT_ID = 6,
    HI_EFUSE_LOCK_ENCRYPT_RSIM_ID = 7,
    HI_EFUSE_LOCK_JTM_ID = 8,
    HI_EFUSE_LOCK_UTM0_ID = 9,
    HI_EFUSE_LOCK_UTM1_ID = 10,
    HI_EFUSE_LOCK_UTM2_ID = 11,
    HI_EFUSE_LOCK_SDC_ID = 12,
    HI_EFUSE_LOCK_RSVD0_ID = 13,
    HI_EFUSE_LOCK_SSS_CORNER_ID = 14,
    HI_EFUSE_LOCK_UART_HALT_INTERVAL_ID = 15,
    HI_EFUSE_LOCK_CHIP_BK_ID = 16,
    HI_EFUSE_LOCK_IPV4_IPV6_MAC_ADDR_ID = 17,
    HI_EFUSE_LOCK_PG2GCCKA0_PG2GCCKA1_TRIM0_ID = 18,
    HI_EFUSE_LOCK_NVRAM_PA2GA0_PA2GA1_TRIM0_ID = 19,
    HI_EFUSE_LOCK_PG2GCCKA0_PG2GCCKA1_TRIM1_ID = 20,
    HI_EFUSE_LOCK_NVRAM_PA2GA0_PA2GA1_TRIM1_ID = 21,
    HI_EFUSE_LOCK_PG2GCCKA0_PG2GCCKA1_TRIM2_ID = 22,
    HI_EFUSE_LOCK_NVRAM_PA2GA0_PA2GA1_TRIM2_ID = 23,
    HI_EFUSE_LOCK_TEE_BOOT_VER_ID = 24,
    HI_EFUSE_LOCK_TEE_KERNEL_VER_ID = 25,
    HI_EFUSE_LOCK_TEE_SALT_ID = 26,
    HI_EFUSE_LOCK_FLASH_ENCPY_CNT0_ID = 27,
    HI_EFUSE_LOCK_FLASH_ENCPY_CNT1_ID = 28,
    HI_EFUSE_LOCK_FLASH_ENCPY_CNT2_ID = 29,
    HI_EFUSE_LOCK_FLASH_ENCPY_CFG_ID = 30,
    HI_EFUSE_LOCK_FLASH_SCRAMBLE_EN_FLASH_IND_ID = 31,
    HI_EFUSE_LOCK_RF_PDBUFFER_GCAL_ID = 32,
    HI_EFUSE_LOCK_CUSTOMER_RSVD1_ID = 33,
    HI_EFUSE_LOCK_DIE_2_ID = 34,
    HI_EFUSE_LOCK_KDF2ECC_HUK_DISABLE_ID = 35,
    HI_EFUSE_LOCK_FLASH_ENCPY_CNT3_ID = 36,
    HI_EFUSE_LOCK_FLASH_ENCPY_CNT4_ID = 37,
    HI_EFUSE_LOCK_FLASH_ENCPY_CNT5_ID = 38,
    HI_EFUSE_LOCK_SEC_BOOT_ID = 39,
    HI_EFUSE_LOCK_DSLEEP_FLAG_ID = 40,
    HI_EFUSE_LOCK_MAX,
} hi_efuse_lock_id;

/**
* @ingroup  iot_efuse
* @brief Reads the eFUSE.CNcomment:EFUSE读取数据。CNend
*
* @par 描述:
*           Reads the eFUSE.CNcomment:从EFUSE中读取数据。CNend
*
* @attention Ensure that the value of (data_len*8) is not less than efuse_id and the length of the efuse field is 8bit
*            aligned.CNcomment:需保证(data_len*8)不小于efuse_id对应efuse字段的长度向上8bit对齐。CNend
*
* @param  efuse_id [IN]  type #hi_efuse_idx，EFUSE ID
* @param  data     [OUT] type #hi_u8*，Address for saving the read data.CNcomment:读到的数据放到该地址。CNend
* @param  data_len [IN]  type #hi_u8 Space allocated to data, in bytes.CNcomment:给data分配的空间，单位byte。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*            @li hi_boot_rom.h：Describes the encryption and decryption APIs.
CNcomment:文件用于描述efuse字段操作相关接口。CNend
* @see  hi_efuse_write。
*/
hi_u32 hi_efuse_read(hi_efuse_idx efuse_id, hi_u8 *data, hi_u8 data_len);

/**
* @ingroup  iot_efuse
* @brief Writes the eFUSE.CNcomment:写数据到EFUSE。CNend
*
* @par 描述:
*           Writes the eFUSE.CNcomment:写数据到EFUSE。CNend
*
* @attention None
* @param  efuse_id  [IN] type #hi_efuse_idx，EFUSE ID
* @param  data      [IN] type #const hi_u8*，Data to be written to the eFUSE.CNcomment:写该数据到EFUSE中。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*            @li hi_boot_rom.h：Describes the encryption and decryption APIs.
CNcomment:文件用于描述efuse字段操作相关接口。CNend
* @see  hi_efuse_read。
*/
hi_u32 hi_efuse_write(hi_efuse_idx efuse_id, const hi_u8 *data);

/**
* @ingroup  iot_efuse
* @brief Locks an area in the eFUSE. After the lock takes effect upon reboot, the area cannot be written.
CNcomment:加锁EFUSE中的某个区域，加锁后重启单板生效，该区域无法再写入。CNend
*
* @par 描述:
*           Locks an area in the eFUSE. After the lock takes effect upon reboot, the area cannot be written.
CNcomment:加锁EFUSE中的某个区域，加锁后重启单板生效，该区域无法再写入。CNend
*
* @attention None
* @param  lock_id  [IN] type #hi_efuse_lock_id，eFUSE ID to be locked.CNcomment:待加锁的EFUSE ID项。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*            @li hi_boot_rom.h：Describes the encryption and decryption APIs.
CNcomment:文件用于描述efuse字段操作相关接口。CNend
* @see  hi_efuse_write。
*/
hi_u32 hi_efuse_lock(hi_efuse_lock_id efuse_lock_id);

/**
* @ingroup  iot_efuse
* @brief Obtains the lock status of the eFUSE and queries which areas are locked.
CNcomment:获取EFUSE的锁状态，查询哪些区域已锁定。CNend
*
* @par 描述:
*           Obtains the lock status of the eFUSE and queries which areas are locked.
CNcomment:获取EFUSE的锁状态，查询哪些区域已锁定。CNend
*
* @attention None
* @param  lock_stat   [OUT] type #hi_u64*，Lock status of the eFUSE.CNcomment:获取EFUSE的锁状态。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*            @li hi_boot_rom.h：Describes the encryption and decryption APIs.
CNcomment:文件用于描述efuse字段操作相关接口。CNend
* @see  hi_efuse_write。
*/
hi_u32 hi_efuse_get_lockstat(hi_u64 *lock_stat);

/**
* @ingroup  iot_efuse
* @brief Reads the user eFUSE.CNcomment:EFUSE用户读取数据。CNend
*
* @par 描述:
*            Reads a reserved area in the eFUSE.CNcomment:用户从EFUSE中读取数据。CNend
*
* @attention None
* @param  start_bit  [IN]  type #hi_u16，Start bit. The address must be 8-bit aligned.
CNcomment:起始bit位，该地址必须8bit对齐。CNend
* @param  size       [IN]  type #hi_u16，Number of bits to be read. If the input is not 8-bit aligned,
* the function performs 8-bit alignment internally. The user needs to process the read data before using it.
CNcomment:待读取的bit位数，如果输入不是8bit对齐则函数内部会处理为8bit对齐，用户读取数据后需处理后使用。CNend
* @param  key_data  [OUT]  type #hi_u8*，Address for saving the read data.
CNcomment:读到的数据放到该地址。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*            @li hi_boot_rom.h：Describes the encryption and decryption APIs.
CNcomment:文件用于描述efuse字段操作相关接口。CNend
* @see  hi_efuse_usr_write。
*/
hi_u32 hi_efuse_usr_read(hi_u16 start_bit, hi_u16 size, hi_u8 *key_data);

/**
* @ingroup  iot_efuse
* @brief Writes data to reserved area of the eFUSE.CNcomment:EFUSE用户区写入数据。CNend
*
* @par 描述:
*           Writes data to reserved area of the eFUSE.CNcomment:用户往EFUSE写入数据。CNend
*
* @attention Generally, this API is used to write a reserved area. To write other pre-allocated areas,
*            should check the design spec to avoid conflict.CNcomment:支持用户写入任意地址数据，
建议用户使用用户预留区，其他区域的写入需要结合方案文档评估是否有冲突。CNend
*
* @param  start_bit  [IN] type  #hi_u16，Start bit.CNcomment:起始bit位。CNend
* @param  size       [IN] type  #hi_u16，Number of bits to be written. 1-to-256-bit write is supported.
CNcomment:待写入bit数，支持单bit写入，最大值为256bit数。CNend
* @param  key_data  [IN]  type  #const hi_u8*，Address for the data to be written. The maximum length is 32 bytes.
CNcomment:待写入的数据放到该地址，最长为32byte。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
* @par 依赖:
*            @li hi_boot_rom.h：Describes the encryption and decryption APIs.
CNcomment:文件用于描述efuse字段操作相关接口。CNend
* @see  hi_efuse_usr_read。
*/
hi_u32 hi_efuse_usr_write(hi_u16 start_bit, hi_u16 size, const hi_u8 *key_data);

/** @defgroup iot_flash Flash Driver APIs
* @ingroup  iot_flashboot
*/
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
*            @li hi_flashboot.h：FLASH driver APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_u32 hi_flash_init(hi_void);

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
* @param  flash_offset    [IN] type #hi_u32，Address offset of the flash memory to be erased.
CNcomment:指定要擦除Flash的地址偏移。CNend
* @param  size            [IN] type #hi_u32，Length of the data to be erased (unit: byte).
*                         The value must be a multiple of 4 KB.
CNcomment:需要擦除的长度（单位：byte），必须是4K的倍数。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_flashboot.h：FLASH driver APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_u32 hi_flash_erase(const hi_u32 flash_addr, hi_u32 flash_erase_size);

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
* @param  flash_offset    [IN] type #hi_u32，Offset address for writing data to the flash memory.
CNcomment:指定写入Flash偏移地址。CNend
* @param  size            [IN] type #hi_u32，Length of the data to be written (unit: byte).
CNcomment:需要写入的长度（单位：byte）。CNend
* @param  ram_data        [IN] type #hi_u8*，Cache address of the data to be written.
CNcomment:需要写入的数据的缓存地址。CNend
* @param  do_erase        [IN] type #hi_bool，HI_FALSE: Write data to the flash memory directly.
*                         HI_TRUE: Erase the sector space before write. The user data is written
*                         to the user operation space and the historical data is written back to other spaces.
CNcomment:表示是否自动擦除并覆盖写入。HI_TRUE：本接口中先擦后写。HI_FALSE：用户已经擦除本接口，可直接写入。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_flashboot.h：FLASH driver APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_u32 hi_flash_write(hi_u32 flash_addr, hi_u32 flash_write_size, const hi_u8 *p_flash_write_data, hi_bool do_erase);

/**
* @ingroup  iot_flash
* @brief  Reads the flash data to the specified cache. CNcomment:读出Flash数据到指定缓存区域。CNend
*
* @par 描述:
*           Reads the flash data to the specified cache. CNcomment:读出Flash数据到指定缓存区域。CNend
*
* @attention None
* @param  flash_offset      [IN] type #hi_u32，Offset of the flash address.CNcomment:指定的Flash地址偏移。CNend
* @param  size              [IN] type #hi_u32，Read length (unit: byte).
CNcomment:指定读取的长度（单位：byte）。CNend
* @param  ram_data          [IN] type #hi_u8*，Destination cache address.CNcomment:目的缓存地址。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_flashboot.h：FLASH driver APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_u32 hi_flash_read(hi_u32 flash_addr, hi_u32 flash_read_size, hi_u8 *p_flash_read_data);

/** @defgroup iot_crc32 CRC32 APIs
* @ingroup iot_flashboot
*/
/**
* @ingroup  iot_crc32
* @brief  Generates a 32-bit CRC value.CNcomment:生成32位CRC校验值。CNend
*
* @par 描述:
*           Generates a 32-bit CRC value.CNcomment:生成32位CRC校验值。CNend
*
* @attention None
* @param  crc               [IN] type #hi_u32，The CRC initial value.CNcomment:CRC初始值。CNend
* @param  p                 [IN] type #const hi_u8*，Pointer to the buffer to be verified.
CNcomment:被校验Buffer指针。CNend
* @param  len               [IN] type #hi_u32，Length of the buffer to be verified (unit: Byte).
CNcomment:被校验Buffer长度（单位：byte）。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
*
* @par 依赖:
*            @li hi_flashboot.h：Describes CRC APIs.CNcomment:文件包含CRC校验接口。CNend
* @see  None
*/
hi_u32  hi_crc32 (hi_u32 crc, const hi_u8 *p, hi_u32 len);

#endif

