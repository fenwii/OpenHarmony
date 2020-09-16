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

#ifndef __YMODEM_H__
#define __YMODEM_H__

#include <hi_types.h>
#define LOADER_RAM_TEXT       __attribute__ ((section(".ram.text")))

hi_u32  ymodem_open(hi_void);
hi_void ymodem_close(hi_void);
hi_u32  ymodem_read(hi_char* buf, hi_u32 size, hi_u32 cs);
hi_u32  ymodem_get_length(hi_void);
hi_u32 loader_ymodem_open(hi_void);

#endif

