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

#ifndef __BOOT_UPG_CHECK_SECURE_H__
#define __BOOT_UPG_CHECK_SECURE_H__

#include <boot_upg_common.h>

#define RSA_2048_LEN  256
#define RSA_KEY_LEN   512
#define ECC_KEY_LEN   64
#define ECC_256_LEN   32

#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
#define FLASH_ADDR_NUM 3
#define TOTAL_SIZE_NUM 3
#define FLASH_FLAG_NUM 3
#else
#define FLASH_ADDR_NUM 2
#define TOTAL_SIZE_NUM 2
#define FLASH_FLAG_NUM 2
#endif

#define UPG_SEC_BOOT_FLAG 0x42

extern hi_u32 __data_start;
extern hi_u32 __data_load;

typedef enum {
    HI_MODE_PKCS_V15 = 0x00,
    HI_MODE_PKCS_PSS = 0x01,
    HI_MODE_ECC = 0x10,
} hi_padding_mode;

typedef struct {
    uintptr_t flash_addr[FLASH_ADDR_NUM];
    uintptr_t total_size[TOTAL_SIZE_NUM];
    hi_u32 buffer_count;
    hi_bool flash_flag[FLASH_FLAG_NUM];
    hi_u16 pad;
    hi_u8 *key_n;
    hi_u8 *key_e;
    hi_u8 *sign;
    hi_u32 key_len;
    hi_padding_mode pad_mode;
} upg_verify_param;

hi_bool boot_upg_is_secure_efuse(hi_void);
hi_u32 boot_upg_check_secure_info(hi_u32 flash_addr, hi_upg_head *upg_head);
hi_u32 boot_upg_check_unsecure_info(hi_u32 flash_addr, hi_upg_head *upg_head);
hi_void boot_upg_save_key_pos(hi_void);
hi_u32 boot_upg_secure_verify_head(hi_upg_head *upg_head);
hi_u32 boot_upg_unsecure_verify_head(hi_upg_head *upg_head);

#endif

