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

#ifndef __KEY_AGREEMENT_SERVER_H__
#define __KEY_AGREEMENT_SERVER_H__

#include "key_agreement.h"

typedef int32_t (*server_virtual_func)(void *, void *);

struct server_virtual_func_group {
    server_virtual_func parse_start_request_data;
    server_virtual_func build_start_response_data;
    server_virtual_func parse_end_request_data;
    server_virtual_func build_end_response_data;
};

struct key_agreement_server {
    struct key_agreement_protocol protocol_base_info;
    struct server_virtual_func_group package_funcs;
};

void init_server(struct key_agreement_server *handle, const struct server_virtual_func_group *funcs);
int32_t send_start_response(void *handle, void *receive_data, void *send_data);
int32_t send_end_response(void *handle, void *receive_data, void *send_data);

#endif /* __KEY_AGREEMENT_SERVER_H__ */
