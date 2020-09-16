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

#include <app_demo_io_gpio.h>

/* gpio callback func */
hi_void gpio_isr_func(hi_void *arg)
{
    hi_unref_param(arg);
    printf("----- gpio isr success -----\r\n");
}

hi_void io_gpio_demo(hi_void)
{
    /* Take gpio 0 as an example */
    hi_u32 ret;
    hi_gpio_value gpio_val = HI_GPIO_VALUE1;

    ret = hi_gpio_init();
    if (ret != HI_ERR_SUCCESS) {
        printf("===== ERROR ===== gpio -> hi_gpio_init ret:%d\r\n", ret);
        return;
    }
    printf("----- gpio init success-----\r\n");

    ret = hi_io_set_func(HI_IO_NAME_GPIO_0, HI_IO_FUNC_GPIO_0_GPIO);
    if (ret != HI_ERR_SUCCESS) {
        printf("===== ERROR ===== gpio -> hi_io_set_func ret:%d\r\n", ret);
        return;
    }
    printf("----- io set func success-----\r\n");

    ret = hi_gpio_set_dir(HI_GPIO_IDX_0, HI_GPIO_DIR_IN);
    if (ret != HI_ERR_SUCCESS) {
        printf("===== ERROR ===== gpio -> hi_gpio_set_dir1 ret:%d\r\n", ret);
        return;
    }
    printf("----- gpio set dir success! -----\r\n");

    ret = hi_gpio_get_input_val(HI_GPIO_IDX_0, &gpio_val);
    if (ret != HI_ERR_SUCCESS) {
        printf("===== ERROR ===== gpio -> hi_gpio_get_input_val ret:%d\r\n", ret);
        return;
    }
    printf("----- gpio input val is:%d. -----\r\n", gpio_val);

    ret = hi_gpio_deinit();
    if (ret != HI_ERR_SUCCESS) {
        printf("===== ERROR ===== gpio -> hi_gpio_deinit ret:%d\r\n", ret);
        return;
    }
    printf("----- gpio deinit success-----\r\n");
}

/* gpio callback demo */
hi_void gpio_isr_demo(hi_void)
{
    hi_u32 ret;

    printf("----- gpio isr demo -----\r\n");

    (hi_void)hi_gpio_init();

    ret = hi_gpio_set_dir(HI_GPIO_IDX_0, HI_GPIO_DIR_IN);
    if (ret != HI_ERR_SUCCESS) {
        printf("===== ERROR ======gpio -> hi_gpio_set_dir1 ret:%d\r\n", ret);
        return;
    }

    ret = hi_gpio_register_isr_function(HI_GPIO_IDX_0, HI_INT_TYPE_LEVEL,
                                        HI_GPIO_EDGE_RISE_LEVEL_HIGH, gpio_isr_func, HI_NULL);
    if (ret != HI_ERR_SUCCESS) {
        printf("===== ERROR ======gpio -> hi_gpio_register_isr_function ret:%d\r\n", ret);
    }
}

hi_void app_demo_custom_io_gpio(hi_void)
{
    io_gpio_demo();
    hi_sleep(1000);  /* sleep 1000ms */
    gpio_isr_demo();
}

