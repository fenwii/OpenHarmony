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

#ifndef __BOOT_UPG_TOOL_H__
#define __BOOT_UPG_TOOL_H__
#include "boot_upg_common.h"

#include "boot_upg_check_secure.h"

#define HI_BLOCK_SIZE 0x100

hi_u32 boot_upg_copy_flash_2_flash(hi_u32 src_addr, hi_u32 src_size, hi_u32 dst_addr, hi_u32 dst_size, hi_bool comprss);
hi_u32 boot_upg_hash_one_content(hi_u32 flash_addr, hi_u32 total_size, hi_u8 *hash, hi_u32 hash_size);
hi_u32 boot_upg_hash_more_content(HI_CONST upg_verify_param *param, hi_u8 *hash, hi_u32 hash_size);
hi_u32 boot_upg_check_before_decompress(hi_u32 addr_write, const hi_upg_section_head *seciton_head,
                                        const hi_upg_file_head *file_head);

#endif
