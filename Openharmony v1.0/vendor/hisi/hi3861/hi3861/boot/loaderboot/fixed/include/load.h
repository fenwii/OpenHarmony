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

#ifndef __LOAD_H__
#define __LOAD_H__

#include <hi_boot_rom.h>

extern hi_char *g_ymodem_buf;
hi_u32 load_malloc_init(hi_void);
hi_s32 load_malloc_deinit(hi_void);
hi_u32 load_serial_ymodem(hi_u32 offset, hi_u32 *addr, hi_u32 check_sum);

#endif
