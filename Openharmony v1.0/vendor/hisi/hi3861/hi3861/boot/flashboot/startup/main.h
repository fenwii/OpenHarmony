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

#ifndef __MAIN_H__
#define __MAIN_H__

HI_EXTERN hi_u32 __heap_begin__;
HI_EXTERN hi_u32 __heap_end__;

#define HI_CHIP_VER_HI3861L     0x0
#define IO_CTRL_REG_BASE_ADDR   0x904   /* Base address of the I/O control register, which is used to
                                           configure the drive capability and pull-up/pull-down */
/* bit mask */
#define MSK_2_B                 0x3
#define MSK_3_B                 0x7
/* bit offset */
#define OFFSET_4_B              4
#define OFFSET_22_B             22
#define OFFSET_25_B             25
#define OFFSET_28_B             28

#endif
