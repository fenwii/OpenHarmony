/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __SEC_CLONE_SERVER_H__
#define __SEC_CLONE_SERVER_H__

#include "hichain.h"

enum SEC_CLONE_MESSAGE_TYPE {
    SEC_CLONE_START_MSG = 1,
    SEC_CLONE_END_MSG,
};

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))

#include "base.h"
#include "key_agreement_server.h"

struct sec_clone_server {
    struct key_agreement_server server_info;
    bool need_clean_temp_key;
    hc_handle hichain_handle;
    struct uint8_buff start_request_data;
    struct uint8_buff client_sec_data;
    struct hc_key_alias cert_key_alias;
};

int32_t send_sec_clone_start_response(struct sec_clone_server *sec_clone_server,
    const struct message *receive, struct message *send);
int32_t send_sec_clone_end_response(struct sec_clone_server *sec_clone_server,
    const struct message *receive, struct message *send);

#else

struct sec_clone_server {
    char rsv;
};

#endif

struct sec_clone_server *build_sec_clone_server(hc_handle hichain);
void destroy_sec_clone_server(struct sec_clone_server *handle);

#endif
