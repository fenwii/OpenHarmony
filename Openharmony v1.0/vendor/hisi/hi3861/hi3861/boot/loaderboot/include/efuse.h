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

#ifndef __EFUSE_H__
#define __EFUSE_H__
#include "efuse_drv.h"

#define EIGHT_BITS        8
#define THREE_BITS_OFFSET 3
#define SIZE_8_BITS       8
#define SIZE_16_BITS      16
#define SIZE_24_BITS      24
#define SIZE_32_BITS      32
#define SIZE_64_BITS      64
#define SIZE_72_BITS      72
#define DATA_LENGTH       4

hi_u32 efuse_bits_read(hi_u16 start_bit, hi_u16 size, hi_u8 *data, hi_u32 data_len);
hi_u32 efuse_bits_write(hi_u16 start_bit, hi_u16 size, const hi_u8 *key_data);

#endif /* __EFUSE_H__ */

