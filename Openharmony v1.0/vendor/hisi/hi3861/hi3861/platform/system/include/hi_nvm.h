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

#ifndef __HI_NVM_H__
#define __HI_NVM_H__

#include <hi_types.h>

#define HNV_FILE_SIGNATURE               hi_make_identifier('H', 'N', 'V', '$')
#define FNV_FILE_SIGNATURE               hi_make_identifier('F', 'N', 'V', '#')

#define FLASH_BLOCK_SIZE  0x1000
#define HNV_NCRC_SIZE     8
#define NV_TOTAL_MAX_NUM  255
#define HNV_FAULT_TOLERANT_TIMES  3

#define HNV_MANAGE_FIXED_LEN  24

typedef struct _hi_nvm_manage_s_ {
    hi_u32  magic;
    hi_u32  crc;
    hi_u8   ver;
    hi_u8   head_len;
    hi_u16  total_num;
    hi_u32  seq;
    hi_u32  ver_magic;
    hi_u32  flash_size;
    hi_u8   keep_id_range[2]; /* Reserved upg id, size:2 bytes, byte0:upper boundary, byte1:lower boundary */
    hi_u8   reserve[2];       /* Reserved 2 bytes */
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

#endif   /* __HI_NVM_H__ */