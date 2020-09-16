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

#include "at_io.h"

#include <hi_stdlib.h>
#include <hi_at.h>
#include <at.h>
#include <hi_io.h>
#include <hi_gpio.h>
#include <hi_isr.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define io_dir_get(cond, id, val_addr)      \
        if ((cond) & (hi_u16)(1 << (id))) { \
            *(val_addr) = HI_GPIO_DIR_OUT;  \
        } else {                            \
            *(val_addr) = HI_GPIO_DIR_IN;   \
        }

#define IO_MAX_WORK_MODE    7

hi_u32 gpio_get_dir(hi_gpio_idx id, hi_gpio_dir *dir)
{
    if (id >= HI_GPIO_IDX_MAX || dir == HI_NULL) {
        return HI_ERR_GPIO_INVALID_PARAMETER;
    }
    hi_u32 int_val;
    hi_u16 reg_val = 0;

    int_val = hi_int_lock();
    hi_reg_read16(0x50006004, reg_val);
    io_dir_get(reg_val, (hi_u16) id, dir);
    hi_int_restore(int_val);

    return HI_ERR_SUCCESS;
}

hi_u32 at_setup_iosetmode_cmd(hi_s32 argc, const hi_char *argv[])
{
    hi_io_name io_num;
    hi_u8 io_mode;
    hi_io_pull io_pull_stat;
    hi_io_driver_strength io_power_level;
    hi_u32 ret;
    hi_s32 i;

    if (argc < 3 || argc > 4) {     /* argc 3/4 */
        return HI_ERR_FAILURE;
    }

    for (i = 0; i < argc; i++) {
        if (integer_check(argv[i]) != HI_ERR_SUCCESS) {
            return HI_ERR_FAILURE;
        }
    }

    io_num = (hi_io_name)atoi(argv[0]);
    if (io_num > HI_IO_NAME_GPIO_14) {
        return HI_ERR_FAILURE;
    }

    io_mode = (hi_u8)atoi(argv[1]);
    if (io_mode > IO_MAX_WORK_MODE) {
        return HI_ERR_FAILURE;
    }

    io_pull_stat = (hi_io_pull)atoi(argv[2]);   /* argc 2 */
    if (io_pull_stat > HI_IO_PULL_DOWN) {
        return HI_ERR_FAILURE;
    }

    if (argc == 3) {    /* argc 3 */
        io_power_level = HI_IO_DRIVER_STRENGTH_3;
    } else {
        io_power_level = (hi_io_driver_strength)atoi(argv[3]);  /* argc 3 */
    }

    ret = hi_io_set_func(io_num, io_mode);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    ret = hi_io_set_pull(io_num, io_pull_stat);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }
    ret = hi_io_set_driver_strength(io_num, io_power_level);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    AT_RESPONSE_OK;
    return HI_ERR_SUCCESS;
}

hi_u32 at_setup_iogetmode_cmd(hi_s32 argc, const hi_char *argv[])
{
    hi_io_name io_num;
    hi_u8 io_mode;
    hi_io_pull io_pull_stat;
    hi_io_driver_strength io_capalibity;
    hi_u32 ret;

    if (argc != 1) {
        return HI_ERR_FAILURE;
    }

    if (integer_check(argv[0]) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    io_num = (hi_io_name)atoi(argv[0]);
    if (io_num > HI_IO_NAME_GPIO_14) {
        return HI_ERR_FAILURE;
    }

    ret = hi_io_get_func(io_num, &io_mode);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    ret = hi_io_get_pull(io_num, &io_pull_stat);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    ret = hi_io_get_driver_strength(io_num, &io_capalibity);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("+GETIOMODE:%d,%d,%d,%d\r\n", io_num, io_mode, io_pull_stat, io_capalibity);
    AT_RESPONSE_OK;
    return HI_ERR_SUCCESS;
}

hi_u32 at_setup_gpiodir_cmd(hi_s32 argc, const hi_char *argv[])
{
    hi_io_name io_num;
    hi_gpio_dir io_dir;
    hi_u8 io_mode;
    hi_u32 ret;
    hi_s32 i;

    if (argc != 2) {    /* argc 2 */
        return HI_ERR_FAILURE;
    }

    for (i = 0; i < argc; i++) {
        if (integer_check(argv[i]) != HI_ERR_SUCCESS) {
            return HI_ERR_FAILURE;
        }
    }

    io_num = (hi_io_name)atoi(argv[0]);
    if (io_num > HI_IO_NAME_GPIO_14) {
        return HI_ERR_FAILURE;
    }

    io_dir = (hi_gpio_dir)atoi(argv[1]);
    if (io_dir > HI_GPIO_DIR_OUT) {
        return HI_ERR_FAILURE;
    }

    ret = hi_io_get_func(io_num, &io_mode);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    if ((io_num < HI_IO_NAME_GPIO_13) && (io_mode != 0)) {
        return HI_ERR_FAILURE;
    } else if ((io_num >= HI_IO_NAME_GPIO_13) && (io_mode != (hi_u8)HI_IO_FUNC_GPIO_13_GPIO)) {
        return HI_ERR_FAILURE;
    }

    ret = hi_gpio_set_dir((hi_gpio_idx)io_num, io_dir);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    AT_RESPONSE_OK;
    return HI_ERR_SUCCESS;
}

hi_u32 at_setup_gpiowt_cmd(hi_s32 argc, const hi_char *argv[])
{
    hi_io_name io_num;
    hi_gpio_value io_level;
    hi_u8 io_mode;
    hi_gpio_dir io_dir;
    hi_u32 ret;
    hi_s32 i;

    if (argc != 2) {    /* argc 2 */
        return HI_ERR_FAILURE;
    }

    for (i = 0; i < argc; i++) {
        if (integer_check(argv[i]) != HI_ERR_SUCCESS) {
            return HI_ERR_FAILURE;
        }
    }

    io_num = (hi_io_name)atoi(argv[0]);
    if (io_num > HI_IO_NAME_GPIO_14) {
        return HI_ERR_FAILURE;
    }

    io_level = (hi_gpio_value)atoi(argv[1]);
    if (io_level > HI_GPIO_VALUE1) {
        return HI_ERR_FAILURE;
    }

    ret = hi_io_get_func(io_num, &io_mode);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    if ((io_num < HI_IO_NAME_GPIO_13) && (io_mode != 0)) {
        return HI_ERR_FAILURE;
    } else if ((io_num >= HI_IO_NAME_GPIO_13) && (io_mode != (hi_u8)HI_IO_FUNC_GPIO_13_GPIO)) {
        return HI_ERR_FAILURE;
    }

    ret = gpio_get_dir((hi_gpio_idx)io_num, &io_dir);
    if ((ret != HI_ERR_SUCCESS) || (io_dir != HI_GPIO_DIR_OUT)) {
        return HI_ERR_FAILURE;
    }

    ret = hi_gpio_set_ouput_val((hi_gpio_idx)io_num, io_level);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    AT_RESPONSE_OK;
    return HI_ERR_SUCCESS;
}

hi_u32 at_setup_gpiord_cmd(hi_s32 argc, const hi_char *argv[])
{
    hi_io_name io_num;
    hi_gpio_value io_level;
    hi_u8 io_mode;
    hi_gpio_dir io_dir;
    hi_u32 ret;

    if (argc != 1) {
        return HI_ERR_FAILURE;
    }

    if (integer_check(argv[0]) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    io_num = (hi_io_name)atoi(argv[0]);
    if (io_num > HI_IO_NAME_GPIO_14) {
        return HI_ERR_FAILURE;
    }

    ret = hi_io_get_func(io_num, &io_mode);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    if ((io_num < HI_IO_NAME_GPIO_13) && (io_mode != 0)) {
        return HI_ERR_FAILURE;
    } else if ((io_num >= HI_IO_NAME_GPIO_13) && (io_mode != (hi_u8)HI_IO_FUNC_GPIO_13_GPIO)) {
        return HI_ERR_FAILURE;
    }

    ret = gpio_get_dir((hi_gpio_idx)io_num, &io_dir);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    ret = hi_gpio_get_input_val((hi_gpio_idx)io_num, &io_level);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("+RDGPIO:%d,%d,%d\r\n", io_num, io_dir, io_level);
    AT_RESPONSE_OK;
    return HI_ERR_SUCCESS;
}

const at_cmd_func g_at_io_func_tbl[] = {
    {"+SETIOMODE", 10, HI_NULL, HI_NULL, (at_call_back_func)at_setup_iosetmode_cmd, HI_NULL},
    {"+GETIOMODE", 10, HI_NULL, HI_NULL, (at_call_back_func)at_setup_iogetmode_cmd, HI_NULL},
    {"+GPIODIR", 8, HI_NULL, HI_NULL, (at_call_back_func)at_setup_gpiodir_cmd, HI_NULL},
    {"+WTGPIO", 7, HI_NULL, HI_NULL, (at_call_back_func)at_setup_gpiowt_cmd, HI_NULL},
    {"+RDGPIO", 7, HI_NULL, HI_NULL, (at_call_back_func)at_setup_gpiord_cmd, HI_NULL},
};

#define AT_IO_FUNC_NUM (sizeof(g_at_io_func_tbl) / sizeof(g_at_io_func_tbl[0]))

void hi_at_io_cmd_register(void)
{
    hi_at_register_cmd(g_at_io_func_tbl, AT_IO_FUNC_NUM);
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif
