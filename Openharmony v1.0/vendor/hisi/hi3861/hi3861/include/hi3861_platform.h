/**
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

#ifndef __HI3861_PLATFORM_H
#define __HI3861_PLATFORM_H

#include <hi_types.h>
#include <hi3861_platform_base.h>

#ifdef HI_BOARD_FPGA
#define PKT_H_START_ADDR    (0x03100000 + 0x4000) /* 16K use for MAC data collect */
#define PKT_H_LEN           0x2000 /* PKT_H:8K MIN:7K */
#define PKT_B_START_ADDR    (0x03100000 + 0x2000 + 0x4000)
#define PKT_B_LEN           0x8000 /* PKT_B:32K MIN:32K */

#else

#define PKT_H_START_ADDR    0x02400000
#define PKT_H_LEN           0x2000 /* PKT_H:8K MIN:7K */
#define PKT_B_START_ADDR    (0x03100000)
#ifdef CONFIG_CHIP_PKT_48K
#define PKT_B_LEN           0xC000 /* PKT_B:32K */
#else
#define PKT_B_LEN           0x8000 /* PKT_B:48K */
#endif

#endif

#define HI_CHIP_ID_1131SV200    0xFF
#define HI_CHIP_VER_HI3861L     0x0
#define HI_CHIP_VER_HI3861      0x1
#define HI_CHIP_VER_HI3881      0x2

hi_void app_io_init(hi_void);
hi_void app_main(hi_void);

#endif /* __HI3861_PLATFORM_H */

