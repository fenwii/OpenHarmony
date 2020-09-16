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

#ifndef HICHAIN_KEY_AGREEMENT_CLIENT_H
#define HICHAIN_KEY_AGREEMENT_CLIENT_H

#include "key_agreement.h"

typedef int32_t (*CLIENT_VIRTUAL_FUNC)(void *, void *);

struct client_virtual_func_group {
    CLIENT_VIRTUAL_FUNC build_start_request_data;
    CLIENT_VIRTUAL_FUNC parse_start_response_data;
    CLIENT_VIRTUAL_FUNC build_end_request_data;
    CLIENT_VIRTUAL_FUNC parse_end_response_data;
};

struct key_agreement_client {
    struct key_agreement_protocol protocol_base_info;
    struct client_virtual_func_group package_funcs;
};

void init_client(struct key_agreement_client *handle, struct client_virtual_func_group *funcs);
int32_t send_start_request(void *handle, void *send_data);
int32_t send_end_request(void *handle, void *receive_data, void *send_data);
int32_t receive_end_response(void *handle, void *receive_data);

#endif /* HICHAIN_KEY_AGREEMENT_CLIENT_H */
