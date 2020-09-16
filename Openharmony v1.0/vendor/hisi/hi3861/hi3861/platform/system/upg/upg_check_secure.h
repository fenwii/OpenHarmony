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

#ifndef __UPG_CHECK_SECURE_H__
#define __UPG_CHECK_SECURE_H__

#include <upg_common.h>

#define RSA_2048_LEN  256
#define RSA_KEY_LEN   512
#define ECC_KEY_LEN   64
#define ECC_256_LEN   32
#define HI_BLOCK_SIZE 0x100

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

hi_u32 upg_check_upg_file_code(hi_u32 flash_addr, hi_upg_head *upg_head);
hi_u32 upg_check_upg_file_head(hi_upg_head *upg_head);
hi_u32 upg_check_upg_file(hi_u32 flash_addr, hi_upg_head *upg_head);
hi_u32 upg_hash_one_content(hi_u32 flash_addr, hi_u32 total_size, hi_u8 *hash, hi_u32 hash_size);
hi_u32 upg_is_secure_efuse(hi_bool *secure_flag);

#endif /* __UPG_CHECK_SECURE_H__ */

