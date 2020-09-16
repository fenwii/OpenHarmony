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

#ifndef __BOOT_UPG_CHECK_H__
#define __BOOT_UPG_CHECK_H__

#include <boot_upg_common.h>

#define PRODUCT_UPG_FILE_IMAGE_ID 0x3C78961E
#define KERELN_VER_MAX          48
#define KERNEL_VER_LEN          6
hi_u32 boot_upg_get_common_head(hi_u32 addr, hi_upg_common_head *head);
hi_u32 boot_upg_get_section_head(hi_u32 addr, hi_upg_section_head *section_head);
hi_u32 boot_upg_check_common_head(const hi_upg_common_head *head);
hi_u32 boot_upg_check_file(hi_u32 flash_addr);
hi_void boot_get_start_addr_offset(hi_u32 addr, hi_u32 *offset);
hi_u32 boot_upg_check_code_ver(hi_u8 ver);

#endif
