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

#include <boot_upg_start_up.h>
#include "boot_start.h"

hi_nv_ftm_startup_cfg g_startup_cfg;

hi_void boot_upg_set_default_cfg(hi_void)
{
    hi_nv_ftm_startup_cfg *cfg = boot_upg_get_cfg();
    hi_flash_partition_table *partition = hi_get_partition_table();
    uintptr_t kernel_a_addr = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
    hi_u32 cs = (uintptr_t)cfg ^ sizeof(hi_nv_ftm_startup_cfg) ^ 0 ^ sizeof(hi_nv_ftm_startup_cfg);
    if (memset_s(cfg, sizeof(hi_nv_ftm_startup_cfg), 0, sizeof(hi_nv_ftm_startup_cfg), cs) != EOK) {
        return;
    }
    cfg->addr_start = kernel_a_addr;
    cfg->cnt_max = UPG_MAX_BACKUP_CNT;
}

hi_u32 boot_upg_save_cfg_to_nv(hi_void)
{
    hi_nv_ftm_startup_cfg *cfg = boot_upg_get_cfg();
    hi_u32 ret = hi_factory_nv_write(HI_NV_FTM_STARTUP_CFG_ID, cfg, sizeof(hi_nv_ftm_startup_cfg), 0);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    return ret;
}

hi_u32 boot_upg_check_start_addr(hi_u32 addr)
{
    hi_flash_partition_table *partition = hi_get_partition_table();
    uintptr_t kernel_a_addr = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
#if defined(CONFIG_COMPRESSION_OTA_SUPPORT)
    if (addr != kernel_a_addr) {
        return HI_ERR_FAILURE;
    }
#else
    uintptr_t kernel_b_addr = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr;
    if ((addr != kernel_a_addr) && (addr != kernel_b_addr)) {
        return HI_ERR_FAILURE;
    }
#endif
    return HI_ERR_SUCCESS;
}

hi_void boot_upg_load_cfg_from_nv(hi_void)
{
    hi_bool set_default_nv_flag = HI_FALSE;
    hi_u32 cs;
    hi_nv_ftm_startup_cfg nv_cfg = { 0 };
    hi_nv_ftm_startup_cfg *cfg = boot_upg_get_cfg();
    hi_u32 ret = hi_factory_nv_read(HI_NV_FTM_STARTUP_CFG_ID, &nv_cfg, sizeof(hi_nv_ftm_startup_cfg), 0);
    if (ret != HI_ERR_SUCCESS) {
        set_default_nv_flag = HI_TRUE;
    } else {
        ret = boot_upg_check_start_addr(nv_cfg.addr_start);
        if (ret != HI_ERR_SUCCESS) {
            set_default_nv_flag = HI_TRUE;
            boot_msg1("[bootupg load cfg]check addr start fail", nv_cfg.addr_start);
        } else {
            cs = (uintptr_t)cfg ^ sizeof(hi_nv_ftm_startup_cfg) ^ ((uintptr_t)&nv_cfg) ^ sizeof(hi_nv_ftm_startup_cfg);
            if (memcpy_s(cfg, sizeof(hi_nv_ftm_startup_cfg), &nv_cfg, sizeof(hi_nv_ftm_startup_cfg), cs) != EOK) {
                set_default_nv_flag = HI_TRUE;
            }
        }
    }

    if (set_default_nv_flag == HI_TRUE) {
        boot_upg_set_default_cfg();
        boot_upg_save_cfg_to_nv();
    }

    /* judge factory test mode */
#ifdef CONFIG_FACTORY_TEST_SUPPORT
    hi_nv_ftm_factory_mode factory_mode_cfg = {0};
    ret = hi_factory_nv_read(HI_NV_FTM_FACTORY_MODE, &factory_mode_cfg, sizeof(hi_nv_ftm_factory_mode), 0);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg0("read ftm fail");
    } else {
        if (factory_mode_cfg.factory_mode == 0x1) {
            boot_msg0("set ftm addr");
            cfg->addr_start = factory_mode_cfg.factory_addr_start; /* 0x0: factory mode, start addr example:0x14D000. */
        }
    }
#endif

    boot_upg_init_verify_addr(cfg);
}

hi_nv_ftm_startup_cfg *boot_upg_get_cfg(hi_void)
{
    return &g_startup_cfg;
}
