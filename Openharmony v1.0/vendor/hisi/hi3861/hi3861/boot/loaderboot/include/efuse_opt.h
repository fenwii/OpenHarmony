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

#ifndef __EFUSE_OPT_H__
#define __EFUSE_OPT_H__
#include <hi_boot_rom.h>

#define EFUSE_MAX_INDEX_SIZE    32
#define EFUSE_BIT_NUM           2048
#define SIZE_32_BITS            32
#define SIZE_64_BITS            64
#define SHIFT_5_BITS            5
#define SHA_256_LENGTH          32
#define EFUSE_CFG_MAX_LEN       1320
#define EFUSE_CFG_MIN_LEN       48
#define U32_PER_LINE            4
#define EFUSE_READ_MAX_BITS     256

typedef struct {
    hi_u8 hash[SHA_256_LENGTH];     /* hash of configuration file. */
    hi_u8 stru_ver;     /* default 0. */
    hi_u8 stru_size;    /* sizeof(struct otp_config_header). */
    hi_u16 number;      /* Item number to be burn. */
    hi_u32 file_size;   /* Configuration file size. */
    hi_u32 reserved[2]; /* Reserved 2 u32. */
    hi_u8 data[0];      /* Item: size = file_size - stru_size. */
} efuse_config_header;

typedef struct {
    hi_u8 stru_ver;     /* default 0. */
    hi_u8 stru_size;    /* sizeof(struct otp_config_item) */
    hi_u16 start_bit;   /* Start bit of OTP */
    hi_u16 bit_width;   /* Bit width */
    hi_u16 value_len;   /* Length of value Byte(s), 4-byte-aligned. */
    hi_u8 value[0];     /* Item, offset: stru_size. */
} efuse_config_item;

hi_u32 efuse_burn(uintptr_t file_addr, hi_u32 file_len);
hi_u32 efuse_read(hi_u16 start_bit, hi_u16 size);
hi_u8 get_writeable_encpt_cnt(hi_void);

#endif
