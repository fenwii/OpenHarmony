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

#ifndef __FT_NV_H__
#define __FT_NV_H__
#include <hi_types.h>

/******************************************************************************
 NV ID[0xF00, 0xFFF]
 *****************************************************************************/
#define HI_NV_FTM_FLASH_PARTIRION_TABLE_ID   0x02
#define HI_FTM_PRODUCT_ID_RANGE_MRS          500

#define HI_NV_FTM_STARTUP_CFG_ID   0x3 /* hi_nv_ftm_startup_cfg */
#define HI_NV_FTM_FACTORY_MODE     0x9 /* hi_nv_ftm_factory_mode */
#define HI_NV_FTM_UPG_WAIT_MODE    0xA /* hi_nv_ftm_upg_wait_mode */

typedef struct {
    uintptr_t addr_start; /* boot start address */
    hi_u16 mode;          /* upgrade mode */
    hi_u8 file_type;      /* file type:boot or code+nv */
    hi_u8 refresh_nv;     /* refresh nv when the flag bit 0x55 is read */
    hi_u8 reset_cnt;      /* number of restarts in upgrade mode */
    hi_u8 cnt_max;        /* the maximum number of restarts (default value : 3) */
    hi_u16 reserved1;
    uintptr_t addr_write; /* write kernel upgrade file address */
    hi_u32 reserved2;     /* reserved */
} hi_nv_ftm_startup_cfg;

typedef struct {
    hi_u32 factory_mode;          /* 0:normal_mode;1:factory_mode */
    uintptr_t factory_addr_start; /* factory bin start address */
    hi_u32 factory_size;          /* factory bin size */
    hi_u32 factory_valid;         /* 0:invalid;1:valid */
} hi_nv_ftm_factory_mode;

typedef struct {
    hi_u32 file_addr;
    hi_u8 file_type;
    hi_u8 boot_version;
    hi_u8 is_upg_process;
    hi_u8 trans_finish_flag;
} hi_nv_ftm_upg_wait_mode;

#endif  /* __FT_NV_H__ */

