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

#include <app_demo_nv.h>

/*
 * This demo simply shows how to read and write nv item.
 * nv demo must excute after hi_nv_init in app_main.
 * nv default value was defined in tools\scripts\generate_nv\xml_file\mss_nvi_db.xml
 */
hi_void nv_demo(hi_void)
{
    hi_u32 ret;
    hi_u32 err_info = 0;
    hi_nv_demo_tset_cfg cfg, cfg1;
    hi_flash_partition_table *ptable = hi_get_partition_table();
    (hi_void)memset_s(&cfg, sizeof(cfg), 0, sizeof(cfg));
    (hi_void)memset_s(&cfg1, sizeof(cfg1), 0, sizeof(cfg1));

    cfg.nv_demo_test_num0 = 0x1;

    hi_flash_deinit();
    ret = hi_flash_init();
    if (ret != HI_ERR_SUCCESS) {
        err_info |= 1 << 0x6;
        printf("flash init status:0x%x\n", err_info);
        return;
    }

    ret = hi_nv_init(ptable->table[HI_FLASH_PARTITON_NORMAL_NV].addr, HI_NV_DEFAULT_TOTAL_SIZE,
        HI_NV_DEFAULT_BLOCK_SIZE);
    if (ret != HI_ERR_SUCCESS) {
        printf("nv init fail\r\n");
        return;
    }

    /* read nv data(which nv id is 0x22) from board */
    ret = hi_nv_read(HI_NV_DEMO_RST_CFG_ID, &cfg, sizeof(cfg), 0);
    if (ret != HI_ERR_SUCCESS) {
        printf("nv read fail\r\n");
        return;
    }
    printf("nv read success, cfg.nv_demo_test_num0:%d\r\n", cfg.nv_demo_test_num0);

    cfg1.nv_demo_test_num0 = 0x3;

    /* write nv data(which nv id is 0x22) to board */
    ret = hi_nv_write(HI_NV_DEMO_RST_CFG_ID, &cfg1, sizeof(cfg1), 0);
    if (ret != HI_ERR_SUCCESS) {
        printf("nv write fail\r\n");
        return;
    }
    printf("nv write success\r\n");
    ret = hi_nv_read(HI_NV_DEMO_RST_CFG_ID, &cfg, sizeof(cfg), 0);
    if (ret != HI_ERR_SUCCESS) {
        printf("nv read fail\r\n");
        return;
    }
    printf("nv read success, cfg.nv_demo_test_num0:%d\r\n", cfg.nv_demo_test_num0);
}

hi_void factory_nv_demo(hi_void)
{
    hi_u32 ret;
    hi_u32 err_info = 0;
    hi_factory_nv_demo_tset_cfg cfg, cfg1;
    (hi_void)memset_s(&cfg, sizeof(cfg), 0, sizeof(cfg));
    (hi_void)memset_s(&cfg1, sizeof(cfg1), 0, sizeof(cfg1));

    cfg.nv_factory_demo_test_num0 = 0x1;

    hi_flash_deinit();
    ret = hi_flash_init();
    if (ret != HI_ERR_SUCCESS) {
        err_info |= 1 << 0x6;
        printf("flash init status:0x%x\n", err_info);
        return;
    }

    ret = hi_factory_nv_init(HI_FNV_DEFAULT_ADDR, HI_NV_DEFAULT_TOTAL_SIZE, HI_NV_DEFAULT_BLOCK_SIZE);
    if (ret != HI_ERR_SUCCESS) {
        printf("factory nv init fail\r\n");
        return;
    }

    /* read factory nv data(which nv id is 0x1) from board */
    ret = hi_factory_nv_read(HI_FACTORY_NV_DEMO_ID, &cfg, sizeof(cfg), 0);
    if (ret != HI_ERR_SUCCESS) {
        printf("factory nv read fail\r\n");
        return;
    }
    printf("factory nv read success, cfg.nv_demo_test_num0:%d\r\n", cfg.nv_factory_demo_test_num0);

    cfg1.nv_factory_demo_test_num0 = 0x3;

    /* write factory nv data(which nv id is 0x1) to board */
    ret = hi_factory_nv_write(HI_FACTORY_NV_DEMO_ID, &cfg1, sizeof(cfg1), 0);
    if (ret != HI_ERR_SUCCESS) {
        printf("factory nv write fail\r\n");
        return;
    }
    printf("factory nv write success\r\n");
    ret = hi_factory_nv_read(HI_FACTORY_NV_DEMO_ID, &cfg, sizeof(cfg), 0);
    if (ret != HI_ERR_SUCCESS) {
        printf("factory nv read fail\r\n");
        return;
    }
    printf("factory nv read success, cfg.nv_demo_test_num0:%d\r\n", cfg.nv_factory_demo_test_num0);
}

