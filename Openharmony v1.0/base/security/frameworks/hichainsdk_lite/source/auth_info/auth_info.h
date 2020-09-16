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

#ifndef __AUTH_INFO_H__
#define __AUTH_INFO_H__

#include "hichain.h"
#include "distribution.h"

/* auth_info exchange data len */
#define HC_AUTH_REQUEST_LEN  350
#define HC_AUTH_RESPONSE_LEN 256

struct auth_info_message {
    struct uint8_buff cipher;
};

struct auth_info_cache {
    int32_t user_type;
    struct hc_auth_id auth_id;
    struct ltpk ltpk;
};

struct exchange_auth_data {
    struct hc_auth_id auth_id;
    struct ltpk ltpk;
};

typedef struct auth_info_message add_request_data;
typedef struct auth_info_message add_response_data;

typedef struct auth_info_message exchange_request_data;
typedef struct auth_info_message exchange_response_data;

typedef struct auth_info_message remove_request_data;
typedef struct auth_info_message remove_response_data;

#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_))
const struct pake_session_key *get_pake_session_key(const struct hichain *hichain);
const struct challenge *get_pake_self_challenge(const struct hichain *hichain);
const struct challenge *get_pake_peer_challenge(const struct hichain *hichain);
const struct hc_auth_id *get_pake_self_auth_id(const struct hichain *hichain);
#endif /* _CUT_XXX_ */
#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_))
const struct sts_session_key *get_sts_session_key(const struct hichain *hichain);
#endif /* _CUT_XXX_ */
int32_t encrypt_payload(const struct var_buffer *key, const struct uint8_buff *plain,
    const char *aad, struct uint8_buff *payload);
int32_t decrypt_payload(const struct var_buffer *key, const struct uint8_buff *payload,
    const char *aad, struct uint8_buff *plain);
struct auth_info_message *malloc_auth_info_msg(uint32_t size);
void free_auth_info_msg(struct auth_info_message *data);
int32_t save_auth_info(const struct hichain *hichain, int32_t pair_type, struct auth_info_cache *cache);
struct auth_info_cache *build_auth_client_info(struct hc_auth_id auth_id, int32_t user_type);
void destroy_auth_client(struct auth_info_cache *auth_info);

#endif /* __AUTH_INFO_H__ */
