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

#include <hi_flashboot.h>

#define PRODUCT_CFG_DEFAULT_BOOT_ADDR              0x0
#define PRODUCT_CFG_DEFAULT_FNV_ADDR               0x8000
#define PRODUCT_CFG_DEFAULT_NORMAL_NV_ADDR         0xA000
#define PRODUCT_CFG_DEFAULT_NORMAL_NV_BACKUP_ADDR  0xC000
#define PRODUCT_CFG_DEFAULT_KERNEL_A_ADDR          0xD000
#define PRODUCT_CFG_DEFAULT_KERNEL_B_ADDR          0xF1000
#define PRODUCT_CFG_DEFAULT_HILINK_ADDR            0x1E3000
#define PRODUCT_CFG_DEFAULT_FILE_SYSTEM_ADDR       0x1E5000
#define PRODUCT_CFG_DEFAULT_USER_RESERVE_ADDR      0x1F0000
#define PRODUCT_CFG_DEFAULT_HILINK_PKI_ADDR        0x1F5000
#define PRODUCT_CFG_DEFAULT_CRASH_INFO_ADDR        0x1F7000
#define PRODUCT_CFG_DEFAULT_BOOT_BACK_ADDR         0x1F8000

#define PRODUCT_CFG_DEFAULT_BOOT_SIZE                0x8000   /* 32K */
#define PRODUCT_CFG_DEFAULT_FNV_SIZE                 0x2000   /* 8K */
#define PRODUCT_CFG_DEFAULT_NORMAL_NV_SIZE           0x2000   /* 8K */
#define PRODUCT_CFG_DEFAULT_NORMAL_NV_BACKUP_SIZE    0x1000   /* 4K */
#define PRODUCT_CFG_DEFAULT_KERNEL_A_SIZE            0xE4000  /* 912K */
#define PRODUCT_CFG_DEFAULT_KERNEL_B_SIZE            0xF2000  /* 968K */
#define PRODUCT_CFG_DEFAULT_HILINK_SIZE              0x2000   /* 8K */
#define PRODUCT_CFG_DEFAULT_FILE_SYSTEM_SIZE         0xB000   /* 44K */
#define PRODUCT_CFG_DEFAULT_USER_RESERVE_SIZE        0x5000   /* 20K */
#define PRODUCT_CFG_DEFAULT_HILINK_PKI_SIZE          0x2000   /* 8K */
#define PRODUCT_CFG_DEFAULT_CRASH_INFO_SIZE          0x1000   /* 4K */
#define PRODUCT_CFG_DEFAULT_BOOT_BACK_SIZE           0x8000   /* 32K */

static hi_flash_partition_table g_partition_table;

hi_flash_partition_table* hi_get_partition_table(hi_void)
{
    return &g_partition_table;
}


/* Initializes the flash partition table. */
hi_u32 hi_flash_partition_init(hi_void)
{
    hi_flash_partition_table* table = hi_get_partition_table();

#ifndef CONFIG_QUICK_SEND_MODE
    hi_u32 ret = hi_factory_nv_read(HI_NV_FTM_FLASH_PARTIRION_TABLE_ID, table, sizeof(hi_flash_partition_table), 0);
#else
    hi_u32 ret = HI_ERR_FAILURE;
#endif
    if (ret != HI_ERR_SUCCESS) { /* read nv fail, set flash partition table default value */
        table->table[HI_FLASH_PARTITON_BOOT].addr = PRODUCT_CFG_DEFAULT_BOOT_ADDR;
        table->table[HI_FLASH_PARTITON_BOOT].size = PRODUCT_CFG_DEFAULT_BOOT_SIZE;
        table->table[HI_FLASH_PARTITON_FACTORY_NV].addr = PRODUCT_CFG_DEFAULT_FNV_ADDR;
        table->table[HI_FLASH_PARTITON_FACTORY_NV].size = PRODUCT_CFG_DEFAULT_FNV_SIZE;
        table->table[HI_FLASH_PARTITON_NORMAL_NV].addr = PRODUCT_CFG_DEFAULT_NORMAL_NV_ADDR;
        table->table[HI_FLASH_PARTITON_NORMAL_NV].size = PRODUCT_CFG_DEFAULT_NORMAL_NV_SIZE;
        table->table[HI_FLASH_PARTITON_NORMAL_NV_BACKUP].addr = PRODUCT_CFG_DEFAULT_NORMAL_NV_BACKUP_ADDR;
        table->table[HI_FLASH_PARTITON_NORMAL_NV_BACKUP].size = PRODUCT_CFG_DEFAULT_NORMAL_NV_BACKUP_SIZE;
        table->table[HI_FLASH_PARTITON_KERNEL_A].addr = PRODUCT_CFG_DEFAULT_KERNEL_A_ADDR;
        table->table[HI_FLASH_PARTITON_KERNEL_A].size = PRODUCT_CFG_DEFAULT_KERNEL_A_SIZE;
        table->table[HI_FLASH_PARTITON_KERNEL_B].addr = PRODUCT_CFG_DEFAULT_KERNEL_B_ADDR;
        table->table[HI_FLASH_PARTITON_KERNEL_B].size = PRODUCT_CFG_DEFAULT_KERNEL_B_SIZE;
        table->table[HI_FLASH_PARTITON_HILINK].addr = PRODUCT_CFG_DEFAULT_HILINK_ADDR;
        table->table[HI_FLASH_PARTITON_HILINK].size = PRODUCT_CFG_DEFAULT_HILINK_SIZE;
        table->table[HI_FLASH_PARTITON_FILE_SYSTEM].addr = PRODUCT_CFG_DEFAULT_FILE_SYSTEM_ADDR;
        table->table[HI_FLASH_PARTITON_FILE_SYSTEM].size = PRODUCT_CFG_DEFAULT_FILE_SYSTEM_SIZE;
        table->table[HI_FLASH_PARTITON_USR_RESERVE].addr = PRODUCT_CFG_DEFAULT_USER_RESERVE_ADDR;
        table->table[HI_FLASH_PARTITON_USR_RESERVE].size = PRODUCT_CFG_DEFAULT_USER_RESERVE_SIZE;
        table->table[HI_FLASH_PARTITON_HILINK_PKI].addr = PRODUCT_CFG_DEFAULT_HILINK_PKI_ADDR;
        table->table[HI_FLASH_PARTITON_HILINK_PKI].size = PRODUCT_CFG_DEFAULT_HILINK_PKI_SIZE;
        table->table[HI_FLASH_PARTITON_CRASH_INFO].addr = PRODUCT_CFG_DEFAULT_CRASH_INFO_ADDR;
        table->table[HI_FLASH_PARTITON_CRASH_INFO].size = PRODUCT_CFG_DEFAULT_CRASH_INFO_SIZE;
        table->table[HI_FLASH_PARTITON_BOOT_BACK].addr = PRODUCT_CFG_DEFAULT_BOOT_BACK_ADDR;
        table->table[HI_FLASH_PARTITON_BOOT_BACK].size = PRODUCT_CFG_DEFAULT_BOOT_BACK_SIZE;
    }
#ifdef CONFIG_QUICK_SEND_MODE
    ret = HI_ERR_SUCCESS;
#endif

    return ret;
}

