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

#ifndef __AT_WIFI_H__
#define __AT_WIFI_H__

#include "hi_types.h"
#include "hi_wifi_api.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define RECONN_PERIOD_MAX 65535
#define RECONN_PERIOD_MIN 1
#define RECONN_COUNT_MAX 65535
#define RECONN_COUNT_MIN 1
#define RECONN_TIMEOUT_MIN 2
#define HI_WIFI_AP_KEY_LEN_MAX 64
#define HI_WIFI_AP_KEY_LEN_MIN 8
#define HI_WIFI_MS_KEY_LEN_MAX 63
#define HI_WIFI_MS_KEY_LEN_MIN 8

void hi_at_sta_cmd_register(void);
hi_void hi_at_sta_factory_test_cmd_register(hi_void);
void hi_at_softap_cmd_register(void);
void hi_at_mesh_cmd_register(void);

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of app_sta.h */
