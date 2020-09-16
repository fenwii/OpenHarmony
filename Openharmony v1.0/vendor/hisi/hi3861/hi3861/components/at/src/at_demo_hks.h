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

#ifndef __APP_HKS_H__
#define __APP_HKS_H__

#include "hi_wifi_api.h"

hi_u32 app_hks_generate_conn_key(void);
hi_u32 app_hks_encrypt_conn_para(hi_wifi_assoc_request *req);
hi_u32 app_hks_decrypt_conn_param(hi_wifi_assoc_request *req);

hi_u32 app_hks_generate_cert_key(void);
hi_u32 app_hks_encrypt_cert(hi_void);
hi_u32 app_hks_decrypt_cert(hi_u32 *plain_size, hi_u8 *plain_data);

#endif

