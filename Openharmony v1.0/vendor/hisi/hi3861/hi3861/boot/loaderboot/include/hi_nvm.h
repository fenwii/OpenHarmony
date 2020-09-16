/**
 * @file hi_nvm.h
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

#ifndef __HI_NVM_H__
#define __HI_NVM_H__

#include <hi_types.h>
#include <hi_boot_rom.h>

#define hi_make_identifier(a, b, c, d)      hi_makeu32(hi_makeu16(a, b), hi_makeu16(c, d))
#define HNV_FILE_SIGNATURE               hi_make_identifier('H', 'N', 'V', '$')
#define FNV_FILE_SIGNATURE               hi_make_identifier('F', 'N', 'V', '#')

#define FACTORY_NV_SIZE   0x2000
#define FLASH_BLOCK_SIZE  0x1000
#define HNV_NCRC_SIZE     8
#define NV_TOTAL_MAX_NUM  255
#define HNV_FAULT_TOLERANT_TIMES  3

#define HNV_MANAGE_FIXED_LEN  24

/* The NV structure in the factory area must be the same as that in the kernel and
   cannot be modified after being fixed. */
typedef struct _hi_nvm_manage_s_ {
    hi_u32  magic;
    hi_u32  crc;
    hi_u8   ver;
    hi_u8   head_len;
    hi_u16  total_num;
    hi_u32  seq;
    hi_u32  ver_magic;
    hi_u32  flash_size;
    hi_u8   keep_id_range[2];  /* Reserved upg id, size:2 bytes, byte0:upper boundary, byte1:lower boundary */
    hi_u8   reserve[2];        /* Reserved 2 bytes */
    hi_u8   nv_item_data[0];
} hi_nv_manage;

typedef struct hi_nv_item_index_s_ {
    hi_u8 nv_id;
    hi_u8 nv_len;
    hi_u16 nv_offset;
} hi_nv_item_index;

typedef struct _hi_nv_ctrl_s_ {
    hi_u32 base_addr;
    hi_u32 block_size;
    hi_u32 total_block_size;
    hi_u32 current_addr;
    hi_u32 seq;
    hi_u32 sem_handle;

    hi_u8 init_flag;
    hi_u8 reserve;
    hi_u16 total_num;
    hi_u32 ver_magic;
    hi_nv_item_index* index;
} hi_nv_ctrl;

typedef enum _hi_nv_type_e_ {
    HI_TYPE_NV = 0,
    HI_TYPE_FACTORY_NV,
    HI_TYPE_TEMP,
    HI_TYPE_NV_MAX,
} hi_nv_type;

hi_u32 hi_nv_flush_keep_ids(hi_u8* addr, hi_u32 len);
hi_u32 hi_nv_block_write(hi_u8* nv_file, hi_u32 len, hi_u32 flag);

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
*
* @retval #0            Success.
* @retval #Other        Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_flashboot.h：Describes NV APIs.CNcomment:文件用于描述NV相关接口。CNend
* @see hi_factory_nv_write。
*/
hi_u32 hi_factory_nv_read(hi_u8 id, hi_pvoid pdata, hi_u8 len, hi_u32 flag);

/** @defgroup iot_crc32 CRC32 APIs
* @ingroup iot_flashboot
*/
/**
* @ingroup  iot_crc32
* @brief  Generates a 16-bit CRC value.CNcomment:生成16位CRC校验值。CNend
*
* @par 描述:
*           Generates a 16-bit CRC value.CNcomment:生成16位CRC校验值。CNend
*
* @attention None
* @param  crc               [IN] type #hi_u16，The CRC initial value.CNcomment:CRC初始值。CNend
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

#endif   /* __HI_NVM_H__ */

