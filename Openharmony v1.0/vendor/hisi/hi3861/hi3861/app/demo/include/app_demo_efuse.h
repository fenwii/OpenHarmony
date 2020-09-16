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

#ifndef __APP_DEMO_EFUSE_H__
#define __APP_DEMO_EFUSE_H__

#include <hi_types_base.h>

#include <hi_early_debug.h>
#include <hi_efuse.h>

#define EFUSE_USR_RW_SAMPLE_BUFF_MAX_LEN 2 /* The efuse customer_rsvd0 length is 64 bits.
                                              Two 32-bit space is required for storing read and write data. */

hi_u32 get_efuse_id_size_test(hi_void);
hi_void efuse_get_lock_stat(hi_void);
hi_u32 efuse_usr_read(hi_void);
hi_u32 efuse_usr_write(hi_void);
hi_u32 efuse_usr_lock(hi_void);
hi_u32 sample_usr_efuse(hi_void);
hi_u32 efuse_id_read(hi_void);
hi_u32 efuse_id_write(hi_void);
hi_u32 efuse_id_lock(hi_void);
hi_u32 sample_id_efuse(hi_void);
hi_void efuse_demo(hi_void);
#endif
