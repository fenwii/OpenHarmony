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

#ifndef __STS_SERVER_H__
#define __STS_SERVER_H__

#include "hichain.h"
#include "base.h"

enum sts_message_type {
    STS_START_MSG = 1,
    STS_END_MSG,
};

#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_))

#include "key_agreement_server.h"

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
#define HC_AUTH_DATA_BUFF_LEN 8192
#else
#define HC_AUTH_DATA_BUFF_LEN 256
#endif

#define STS_SESSION_KEY_LENGTH 16
#define PEER_USER_TYPE_EMPTY (-1)
#define PEER_USER_TYPE_ACCESSORY 99

#define HICHAIN_RETURN_KEY "hichain_return_key"
#define HICHAIN_AUTH_INFO  "hichain_auth_info"

struct auth_data {
    uint32_t length;
    uint8_t auth_data[HC_AUTH_DATA_BUFF_LEN];
};

struct auth_return {
    uint32_t length;
    uint8_t auth_return[HC_AUTH_DATA_BUFF_LEN];
};

struct sts_session_key {
    uint32_t length;
    uint8_t key[STS_SESSION_KEY_LENGTH];
};

struct sts_end_response_data {
    struct auth_return auth_return;
};

struct sts_start_response_data {
    struct key_agreement_version self_version;
    struct key_agreement_version self_support_version;
    struct challenge challenge;
    struct hc_salt salt;
    struct stpk epk;
    struct auth_data auth_data;
    struct hc_auth_id self_auth_id;
    enum hc_user_type peer_user_type;
};

struct sts_server {
    struct key_agreement_server server_info;
    const struct session_identity *identity;
    struct stpk self_public_key;
    struct stsk self_private_key;
    struct stpk peer_public_key;
    struct sts_session_key session_key;
    struct hc_session_key service_key;
    uint32_t key_length;
    struct challenge peer_challenge;
    struct challenge my_challenge;
    struct hc_auth_id peer_id;
    struct hc_auth_id self_id;
    enum hc_user_type peer_user_type;
    struct hc_salt salt;
    hc_handle hichain_handle;
    uint32_t start_request;
    uint32_t ack_request;
    struct sts_start_response_data start_response_data;
    struct sts_end_response_data end_response_data;
};

struct sts_start_request_data {
    struct key_agreement_version peer_version;
    struct key_agreement_version peer_support_version;
    int32_t operation_code;
    struct challenge challenge;
    struct stpk epk;
    struct hc_package_name package_name;
    struct hc_service_type service_type;
    struct hc_auth_id self_auth_id;
    enum hc_user_type peer_user_type;
    uint32_t key_length;
};

struct sts_start_request_data_hex {
    uint8_t *tmp_cha_data_hex;
    uint8_t *tmp_epk_data_hex;
    uint8_t *tmp_type_data_hex;
    uint8_t *tmp_auth_id_data_hex;
};

struct sts_start_response_data_hex {
    uint8_t *tmp_auth_data_hex;
    uint8_t *tmp_cha_data_hex;
    uint8_t *tmp_salt_data_hex;
    uint8_t *tmp_epk_data_hex;
    uint8_t *tmp_auth_id_data_hex;
};

struct sts_end_request_data {
    struct auth_data auth_data;
};

static inline uint32_t sts_server_sn(struct sts_server *server)
{
    return server->server_info.protocol_base_info.sn;
}

int32_t send_sts_start_response(struct sts_server *handle, struct message *receive, struct message *send);
int32_t send_sts_end_response(struct sts_server *handle, struct message *receive, struct message *send);

#else /* _CUT_XXX_ */

struct sts_server {
    char rsv;
};

#endif /* _CUT_XXX_ */

struct sts_server *build_sts_server(const hc_handle hichain_handle, uint32_t key_length,
    const struct hc_auth_id *client, const struct hc_auth_id *server);
void destroy_sts_server(struct sts_server *handle);

#endif /* __STS_SERVER_H__ */
