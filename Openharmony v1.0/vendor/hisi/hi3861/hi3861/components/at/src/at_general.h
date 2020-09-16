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

#ifndef __AT_GENERAL_H__
#define __AT_GENERAL_H__

#include "hi_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define DEFAULT_IFNAME_LOCALHOST    "lo"
#define DEFAULT_IFNAME_AP           "ap0"
#define DEFAULT_IFNAME_STA          "wlan0"
#define DEFAULT_IFNAME_MESH         "mesh0"

hi_void hi_at_general_cmd_register(hi_void);
hi_void hi_at_general_factory_test_cmd_register(hi_void);
hi_u32 at_wifi_ifconfig(hi_s32 argc, const hi_char **argv);
hi_u32 osShellDhcps(hi_s32 argc, const hi_char **argv);
hi_u32 at_lwip_ifconfig(hi_s32 argc, const hi_char **argv);
hi_void at_send_serial_data(hi_char *serial_data);

extern hi_u32 get_rf_cmu_pll_param(hi_s16 *high_temp, hi_s16 *low_temp, hi_s16 *compesation);

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif
