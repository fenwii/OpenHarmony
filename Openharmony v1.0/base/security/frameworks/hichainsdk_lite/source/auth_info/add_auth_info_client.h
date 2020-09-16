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

#ifndef __ADD_AUTH_INFO_CLIENT_H__
#define __ADD_AUTH_INFO_CLIENT_H__

#include "add_auth_info.h"
#include "sts_client.h"

#if !(defined(_CUT_STS_) || defined(_CUT_STS_CLIENT_) || defined(_CUT_ADD_) || defined(_CUT_ADD_CLIENT_))

#define HC_ADD_AUTH_DATA_BUFF_LEN    256
#define HC_ADD_INFO_REQUEST     "hichain_add_info_request"
#define HC_ADD_INFO_RESPONSE    "hichain_add_info_response"

struct add_auth_info_client {
    struct sts_client *sts_client;
    struct auth_info_cache *auth_info;
};

#ifdef __cplusplus
extern "C" {
#endif
int32_t build_add_request_data(struct add_auth_info_client *auth_info_client, add_request_data *send);
int32_t parse_add_response_data(struct add_auth_info_client *auth_info_client, const add_response_data *receive);
int32_t receive_add_response(const struct hichain *hichain, const struct message *receive);
#ifdef __cplusplus
}
#endif

#endif /* _CUT_XXX_ */

int32_t send_add_request(const struct hichain *hichain, struct message *send);

#endif /* __ADD_AUTH_INFO_CLIENT_H__ */
