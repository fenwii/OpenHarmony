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

#define TEST_KERNEL_FLASH
#ifdef TEST_KERNEL_FLASH
#include <app_demo_flash.h>

hi_u32 g_test_flash_tb = 0;
hi_u32 g_tf_test_time = 60;
hi_u32 g_tf_test_mode = 0;

hi_u8 g_tf_pdata[TEST_SIZE];
hi_u8 g_tf_pdata_back[TEST_SIZE];

#define CODE_IN_FLASH
#ifdef CODE_IN_FLASH
hi_void *test_flash_body2(hi_void* param)
#else
BSP_RAM_TEXT_SECTION hi_void *test_flash_body2(hi_void* param)
#endif
{
    hi_u32 ret;
    hi_u32 tick[2]; /* 2 */
    hi_unref_param(param);
    hi_watchdog_disable();
    tick[0] = hi_get_tick();
    for (;;) {
        if (g_tf_test_mode == 2) { /* 2 */
            for (int i = 0; i < TEST_SIZE; i++) {
                g_tf_pdata_back[i] = (hi_u8)(*(hi_u16*)(0x401000 + i * 2)); /* flash addr:0x401000 2 */
            }
        } else {
            ret = hi_flash_erase(TEST_FLASH_OFFSET, TEST_SIZE);
            if (ret != HI_ERR_SUCCESS) {
                printf("erase fail:%x\n", ret);
            }
            ret = hi_flash_write(TEST_FLASH_OFFSET, TEST_SIZE, g_tf_pdata, HI_TRUE);
            if (ret != HI_ERR_SUCCESS) {
                printf("write fail:%x\n", ret);
            }
            memset_s(g_tf_pdata_back, TEST_SIZE, 0x0, TEST_SIZE);
            ret = hi_flash_read(TEST_FLASH_OFFSET, TEST_SIZE, g_tf_pdata_back);
            if (ret != HI_ERR_SUCCESS) {
                printf("read fail:%x\n", ret);
            }
        }
        if (memcmp(g_tf_pdata, g_tf_pdata_back, TEST_SIZE)) {
            printf("hi_flash_read fail !\r\n");
            break;
        }
        tick[1] = hi_get_tick();
        if ((tick[1] - tick[0]) >= (g_tf_test_time * 100)) { /* 100 */
            printf("test over\r\n");
            break;
        }
    }
    return HI_NULL;
}

hi_void cmd_test_flash(hi_u32 test_time, hi_u32 test_mode)
{
    hi_task_attr attr;
    hi_u32 ret;
    hi_u32 i;
    g_tf_test_time = test_time;
    g_tf_test_mode = test_mode;
    printf("test mode %d ,test %d s,wait ..\r\n", g_tf_test_mode, g_tf_test_time);
    if (g_tf_test_mode == 0) {
        for (i = 0; i < TEST_SIZE; i++) {
            g_tf_pdata[i] = (hi_u8)i;
        }
    } else if (g_tf_test_mode == 1) {
        memset_s(g_tf_pdata, TEST_SIZE, 0xF0, TEST_SIZE);
        printf("test F0\r\n");
    } else if (g_tf_test_mode == 2) { /* 2 */
        printf("test task in flash\r\n");
    }
    ret = hi_flash_write(TEST_FLASH_OFFSET, TEST_SIZE, g_tf_pdata, HI_TRUE);
    if (ret != HI_ERR_SUCCESS) {
        return;
    }
    ret = hi_flash_read(TEST_FLASH_OFFSET, TEST_SIZE, g_tf_pdata_back);
    if (ret != HI_ERR_SUCCESS) {
        return;
    }
    if (memcmp(g_tf_pdata, g_tf_pdata_back, TEST_SIZE)) {
        printf("write or read fail !\r\n");
        printf("testdata addr:0x%x\r\n", (hi_u32)g_tf_pdata_back);
        return;
    }
    printf("testdata addr:0x%x\r\n", (hi_u32)g_tf_pdata_back);
    attr.stack_size = 0x800; /* 800 */
    attr.task_name = (hi_char*) "test_flash";
    attr.task_prio = 28; /* 28 */
    hi_task_create(&g_test_flash_tb, &attr, test_flash_body2, 0);
}

#endif
