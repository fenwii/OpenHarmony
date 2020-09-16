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

#include <hi_loaderboot_flash.h>
#include <hi_boot_err.h>
#include "burn_file.h"

hi_u32 loaderboot_get_section_head(hi_u32 addr, hi_upg_section_head *section_head)
{
    hi_upg_common_head head = { 0 };
    hi_u32 ret;

    if (section_head == HI_NULL) {
        return HI_ERR_UPG_NULL_POINTER;
    }
    ret = hi_flash_read(addr, sizeof(hi_upg_common_head), (hi_u8 *)(&head));
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[bootupg get section head]flash read ret:", ret);
        return ret;
    }
    ret = hi_flash_read(addr + head.section_offset, sizeof(hi_upg_section_head), (hi_u8 *)section_head);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[bootupg get section head]flash read ret:", ret);
        return ret;
    }

    return ret;
}

hi_void loaderboot_get_start_addr_offset(hi_u32 addr, hi_u32 *offset)
{
    hi_upg_section_head section_head = { 0 };
    hi_u32 ret = loaderboot_get_section_head(addr, &section_head);
    if (ret == HI_ERR_SUCCESS) {
        *offset = addr + section_head.section0_offset;
    } else {
        boot_msg1("[boot get start addr offset]fail.", ret);
        *offset = addr;
    }
}