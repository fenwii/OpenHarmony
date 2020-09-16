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

#ifndef __BOOT_UPG_START_UP_H
#define __BOOT_UPG_START_UP_H

#include <boot_upg_common.h>

#define ENV_REFRESH_NV 0x55

#define HI_UPG_MODE_NORMAL  0 /* normal mode */
#define HI_UPG_MODE_UPGRADE 1 /* upgrade mode */
#define UPG_MAX_BACKUP_CNT  3

#define HI_NV_FTM_STARTUP_CFG_ID 0x3
#define HI_NV_FTM_FACTORY_MODE 0x9

typedef struct {
    uintptr_t addr_start; /* boot start address */
    hi_u16 mode;          /* upgrade mode */
    hi_u8 file_type;      /* file type:boot or code+nv */
    hi_u8 refresh_nv;     /* refresh nv when the flag bit 0x55 is read */
    hi_u8 reset_cnt;      /* number of restarts in upgrade mode */
    hi_u8 cnt_max;        /* the maximum number of restarts (default value : 3) */
    hi_u16 reserved1;
    uintptr_t addr_write; /* write kernel upgrade file address */
    hi_u32 reserved2; /* 2: reserved bytes */
} hi_nv_ftm_startup_cfg;

typedef struct {
    hi_u32 factory_mode;          /* 0:normal_mode;1:factory_mode */
    uintptr_t factory_addr_start; /* factory bin start address */
    hi_u32 factory_size;          /* factory bin size */
    hi_u32 factory_valid;         /* 0:invalid;1:valid */
}hi_nv_ftm_factory_mode;

hi_u32 boot_upg_save_cfg_to_nv(hi_void);
hi_void boot_upg_load_cfg_from_nv(hi_void);
hi_nv_ftm_startup_cfg *boot_upg_get_cfg(hi_void);

#endif /* __BOOT_UPG_START_UP_H */
