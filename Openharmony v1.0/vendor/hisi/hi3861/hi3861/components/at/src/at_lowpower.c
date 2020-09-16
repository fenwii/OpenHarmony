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

#include "at_lowpower.h"

#ifndef CONFIG_FACTORY_TEST_MODE
#include "lwip/ip_addr.h"
#endif
#include "hi_at.h"
#include "hi_gpio.h"
#include "hi_io.h"
#include "hi_lowpower.h"
#include "hi_stdlib.h"
#include "hi_time.h"
#include "hi_types_base.h"
#include "hi_watchdog.h"
#include "hi_wifi_api.h"

#include "at.h"
#include "at_io.h"

#define MILLISECOND_PER_TICK     10
#define GPIO3_WAKE_UP_SOURCE     3
#define GPIO5_WAKE_UP_SOURCE     5
#define GPIO7_WAKE_UP_SOURCE     7
#define GPIO14_WAKE_UP_SOURCE    14
#define ALL_GPIO_WAKE_UP_SOURCE  0

#define IO0_GPIO_MODE            0
#define IO1_GPIO_MODE            0
#define IO2_GPIO_MODE            0
#define IO3_GPIO_MODE            0
#define IO4_GPIO_MODE            0
#define IO5_GPIO_MODE            0
#define IO6_GPIO_MODE            0
#define IO7_GPIO_MODE            0
#define IO8_GPIO_MODE            0
#define IO9_GPIO_MODE            0
#define IO10_GPIO_MODE           0
#define IO11_GPIO_MODE           0
#define IO12_GPIO_MODE           0
#define IO13_GPIO_MODE           4
#define IO14_GPIO_MODE           4

hi_u8 g_io_gpio_mode[] = {
    IO0_GPIO_MODE,
    IO1_GPIO_MODE,
    IO2_GPIO_MODE,
    IO3_GPIO_MODE,
    IO4_GPIO_MODE,
    IO5_GPIO_MODE,
    IO6_GPIO_MODE,
    IO7_GPIO_MODE,
    IO8_GPIO_MODE,
    IO9_GPIO_MODE,
    IO10_GPIO_MODE,
    IO11_GPIO_MODE,
    IO12_GPIO_MODE,
    IO13_GPIO_MODE,
    IO14_GPIO_MODE,
};

hi_u32 ms_to_systick(hi_u32 ms, hi_bool include0)
{
    hi_u32 tick;

    /* >10ms Align Down */
    if (ms > MILLISECOND_PER_TICK) {
        tick = ms / MILLISECOND_PER_TICK;    /* convert from ms to ticks */
    } else {
        if ((include0 == HI_TRUE) && (ms == 0)) {
            tick = 0;
        } else {
            tick = 1;
        }
    }

    return tick;
}
#ifndef CONFIG_FACTORY_TEST_MODE
hi_u32 at_setup_sleep(hi_s32 argc, hi_char *argv[])
{
    hi_u8 sleep_mode;

    if (argc != 1 || argv == HI_NULL) { /* just support sleep mode param */
        return HI_ERR_FAILURE;
    }

    if ((at_param_null_check(argc, (const hi_char **)argv) != HI_ERR_SUCCESS) ||
        (integer_check(argv[0]) != HI_ERR_SUCCESS)) {
        return HI_ERR_FAILURE;
    }

    sleep_mode = (hi_u8)atoi(argv[0]);
    if (sleep_mode > 2) { /* 0:wake up; 1:light sleep; 2:deep sleep */
        return HI_ERR_FAILURE;
    }

    hi_lpc_set_type((hi_lpc_type)sleep_mode);

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_void wake_gpio_callback(hi_void *arg)
{
    /*  Add processing code based on service scenarios. */
    hi_unref_param(arg);
    /* To prevent the watchdog from being triggered by frequent reporting of GPIO interrupts
       in some abnormal scenarios,the watchdog is reset. */
    hi_watchdog_feed();
    hi_at_printf("+WKGPIO: GPIO INT TRIGGER!\r\n");
}

hi_u32 check_io_status(hi_gpio_idx io_num)
{
    hi_u8 io_current_func = 0;
    hi_gpio_dir gpio_dir = HI_GPIO_DIR_IN;

    hi_io_get_func((hi_io_name)io_num, &io_current_func);
    if (io_num < HI_GPIO_IDX_13) {
        if (io_current_func != 0) {
            return HI_ERR_FAILURE;
        }
    } else {
        if ((io_current_func != 0) && (io_current_func != IO13_GPIO_MODE)) {
            return HI_ERR_FAILURE;
        }
    }

    gpio_get_dir(io_num, &gpio_dir);
    if (gpio_dir == HI_GPIO_DIR_OUT) {
        return HI_ERR_FAILURE;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 wake_gpio_init(hi_gpio_idx io_num)
{
    hi_u32 ret;
    ret = hi_io_set_func((hi_io_name)io_num, g_io_gpio_mode[io_num]);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = hi_gpio_init();
    if ((ret != HI_ERR_SUCCESS) && (ret != HI_ERR_GPIO_REPEAT_INIT)) {
        return ret;
    }

    ret = hi_gpio_set_dir(io_num, HI_GPIO_DIR_IN);
    if (ret != HI_ERR_SUCCESS) {
        hi_gpio_deinit();
        return ret;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 at_setup_wake_gpio(hi_s32 argc, hi_char *argv[])
{
    hi_u32 ret;
    hi_s32 i;
    hi_gpio_idx io_num;
    hi_gpio_int_type int_type;
    hi_gpio_int_polarity int_level;

    if (argc != 3 || argv == HI_NULL) { /* 3 param: io_num, int_type, int_level */
        return HI_ERR_FAILURE;
    }

    ret = at_param_null_check(argc, (const hi_char **)argv);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    for (i = 0; i < argc; i++) {
        if (integer_check(argv[i]) != HI_ERR_SUCCESS) {
            return HI_ERR_FAILURE;
        }
    }

    io_num = (hi_gpio_idx)atoi(argv[0]);
    if (io_num > HI_GPIO_IDX_14) {
        return HI_ERR_FAILURE;
    }

    int_type = (hi_gpio_int_type)atoi(argv[1]);
    if (int_type > HI_INT_TYPE_EDGE) {
        return HI_ERR_FAILURE;
    }

    int_level = (hi_gpio_int_polarity)atoi(argv[2]); /* 2: int_level */
    if (int_level > HI_GPIO_EDGE_RISE_LEVEL_HIGH) {
        return HI_ERR_FAILURE;
    }

    ret = check_io_status(io_num);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = wake_gpio_init(io_num);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = hi_gpio_register_isr_function(io_num, int_type, int_level, wake_gpio_callback, HI_NULL);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = hi_lpc_config_dsleep_wakeup_io(io_num, HI_TRUE);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 at_setup_ultra_dsleep(hi_s32 argc, hi_char *argv[])
{
    hi_udsleep_src wake_gpio;
    hi_s32 i;
    hi_u32 ret;
    hi_u8 wake_param;

    if (argc != 1 || argv[0] == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    ret = at_param_null_check(argc, (const hi_char **)argv);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    for (i = 0; i < argc; i++) {
        if (integer_check(argv[i]) != HI_ERR_SUCCESS) {
            return HI_ERR_FAILURE;
        }
    }

    wake_param = (hi_u8)atoi(argv[0]);
    switch (wake_param) {
        case ALL_GPIO_WAKE_UP_SOURCE:
            wake_gpio = HI_UDS_GPIO3 | HI_UDS_GPIO5
                      | HI_UDS_GPIO7 | HI_UDS_GPIO14;
            break;
        case GPIO3_WAKE_UP_SOURCE:
            wake_gpio = HI_UDS_GPIO3;
            break;
        case GPIO5_WAKE_UP_SOURCE:
            wake_gpio = HI_UDS_GPIO5;
            break;
        case GPIO7_WAKE_UP_SOURCE:
            wake_gpio = HI_UDS_GPIO7;
            break;
        case GPIO14_WAKE_UP_SOURCE:
            wake_gpio = HI_UDS_GPIO14;
            break;
        default:
            return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    hi_udelay(3000); /* 3000:delay 3ms */
    hi_lpc_enable_udsleep(wake_gpio);

    return HI_ERR_SUCCESS;
}

hi_u32 arp_offload_parse_ipv4_check(char *ip_str, unsigned int *ip_result)
{
    char           *ip_str_cpy = ip_str;
    const char      delim = '.';
    unsigned char   count = 0;
    char           *str_value = NULL;
    hi_u32          value;
    char           *pos = NULL;

    if (strlen(ip_str) > 15) {  /* 15 */
        return HI_ERR_FAILURE;
    }

    pos = strchr(ip_str_cpy, delim);
    while (pos != NULL && pos < (ip_str + 15)) {    /* 15 */
        *pos = '\0';
        str_value = ip_str_cpy;
        ip_str_cpy = pos + 1;
        if ((strlen(str_value) < 1 || strlen(str_value) > 3) || /* 3 */
            (integer_check(str_value) != HI_ERR_SUCCESS)) {
            return HI_ERR_FAILURE;
        }
        value = (hi_u32)atoi(str_value);
        value <<= count * 8;    /* 8 */
        count++;
        *ip_result += value;
        pos = strchr(ip_str_cpy, delim);
    }
    if (count != 3) {   /* 3 */
        return HI_ERR_FAILURE;
    }

    if ((strlen(ip_str_cpy) < 1 || strlen(ip_str_cpy) > 3) ||   /* 3 */
        (integer_check(ip_str_cpy) != HI_ERR_SUCCESS)) {
        return HI_ERR_FAILURE;
    }
    value = (hi_u32)atoi(ip_str_cpy);
    value <<= 3 * 8;    /* 3*8 */
    *ip_result += value;

    return HI_ERR_SUCCESS;
}


hi_u32 at_set_arpoffload(hi_s32 argc, const hi_char **argv)
{
    const char    *ifname = "wlan0";
    unsigned char  enable;
    unsigned int   ip_addr = 0;

    if ((argc < 1) || (argc > 2) || (argv == NULL)) {   /* 1/2 */
        return HI_ERR_FAILURE;
    }

    if ((at_param_null_check(argc, argv) == HI_ERR_FAILURE) || (integer_check(argv[0]) != HI_ERR_SUCCESS)) {
        return HI_ERR_FAILURE;
    }

    enable = (unsigned char)atoi(argv[0]);
    if (argc == 1) {
        if (enable != 0) {
            return HI_ERR_FAILURE;
        }
    } else {
        if (enable != 1) {
            return HI_ERR_FAILURE;
        }

        if (arp_offload_parse_ipv4_check((char *)argv[1], &ip_addr) != HI_ERR_SUCCESS) {
            return HI_ERR_FAILURE;
        }
    }

    if (hi_wifi_arp_offload_setting(ifname, enable, ip_addr) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 at_set_powersave(hi_s32 argc, const hi_char **argv)
{
    unsigned char  ps_switch;
    int   ret;
    unsigned int   wifi_sleep_time = 0;

    if ((argc < 1) || (argc > 2) || (argv == NULL)) {   /* 1/2 */
        return HI_ERR_FAILURE;
    }

    if ((at_param_null_check(argc, (const hi_char **)argv) != HI_ERR_SUCCESS) ||
        (integer_check(argv[0]) != HI_ERR_SUCCESS)) {
        return HI_ERR_FAILURE;
    }

    ps_switch = (unsigned char)atoi(argv[0]);
    if (argc == 1) {
        if ((ps_switch != 0) && (ps_switch != 1)) {
            return HI_ERR_FAILURE;
        }
    } else { /* 2 parameters */
        if (ps_switch != 1) {
            return HI_ERR_FAILURE;
        }

        if (integer_check(argv[1]) != HI_ERR_SUCCESS) {
            return HI_ERR_FAILURE;
        }
        wifi_sleep_time = (unsigned int)atoi(argv[1]);
        if ((wifi_sleep_time < 33) || (wifi_sleep_time > 4000)) {   /* 33/4000 */
            return HI_ERR_FAILURE;
        }
    }

    ret = (hi_u32)hi_wifi_set_pm_switch(ps_switch, wifi_sleep_time);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 at_set_ndoffload(hi_s32 argc, const hi_char **argv)
{
    const char *ifname = "wlan0";
    unsigned char enable;
    ip6_addr_t ip6_addr = { 0 };

    if ((argc < 1) || (argc > 2) || (argv == NULL)) {   /* 1/2 */
        return HI_ERR_FAILURE;
    }

    if ((at_param_null_check(argc, argv) == HI_ERR_FAILURE) || (integer_check(argv[0]) != HI_ERR_SUCCESS)) {
        return HI_ERR_FAILURE;
    }

    enable = (unsigned char)atoi(argv[0]);
    if (argc == 1) {
        if (enable != 0) {
            return HI_ERR_FAILURE;
        }
    } else {
        if (enable != 1) {
            return HI_ERR_FAILURE;
        }

        if (ip6addr_aton((char *)argv[1], &ip6_addr) != 1) {
            return HI_ERR_FAILURE;
        }
    }

    if (hi_wifi_nd_offload_setting(ifname, enable, (unsigned char *)&ip6_addr) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    hi_at_printf("OK\r\n");
    return HI_ERR_SUCCESS;
}
#endif

const at_cmd_func g_at_lowpower_func_tbl[] = {
#ifndef CONFIG_FACTORY_TEST_MODE
    {"+SLP", 4, HI_NULL, HI_NULL, (at_call_back_func)at_setup_sleep, HI_NULL},
    {"+WKGPIO", 7, HI_NULL, HI_NULL, (at_call_back_func)at_setup_wake_gpio, HI_NULL},
    {"+USLP", 5, HI_NULL, HI_NULL, (at_call_back_func)at_setup_ultra_dsleep, HI_NULL},
    {"+ARP", 4, HI_NULL, HI_NULL, (at_call_back_func)at_set_arpoffload, HI_NULL},
    {"+PS", 3, HI_NULL, HI_NULL, (at_call_back_func)at_set_powersave, HI_NULL},
    {"+ND", 3, HI_NULL, HI_NULL, (at_call_back_func)at_set_ndoffload, HI_NULL},
#endif
};

#define AT_LOWPOWER_FUNC_NUM (sizeof(g_at_lowpower_func_tbl) / sizeof(g_at_lowpower_func_tbl[0]))

hi_void hi_at_lowpower_cmd_register(hi_void)
{
    hi_at_register_cmd(g_at_lowpower_func_tbl, AT_LOWPOWER_FUNC_NUM);
}

