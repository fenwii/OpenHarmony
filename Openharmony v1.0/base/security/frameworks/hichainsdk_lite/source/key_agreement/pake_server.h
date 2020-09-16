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

#ifndef __PAKE_SERVER_H__
#define __PAKE_SERVER_H__

enum pake_message_type {
    PAKE_START_MSG = 1,
    PAKE_END_MSG,
};

#include "hichain.h"
#include "base.h"

#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_))

#include "key_agreement_server.h"

#define KCF_BUFF_LENGTH             16
#define PAKE_SESSION_KEY_LENGTH     16
#define PAKE_HMAC_KEY_LENGTH        32
#define PAKE_SHARED_SECRET_LENGTH   HC_BIG_PRIME_MAX_LEN
#define PAKE_EPK_LENGTH             HC_BIG_PRIME_MAX_LEN
#if !defined(_SCANTY_MEMORY_)
#define PAKE_ESK_LENGTH             32
#else /* _SCANTY_MEMORY_ */
#define PAKE_ESK_LENGTH             28
#endif /* _SCANTY_MEMORY_ */
#define PAKE_ESK_SHORT_LENGTH       28

struct pake_hmac_key {
    uint32_t length;
    uint8_t key[PAKE_HMAC_KEY_LENGTH];
};

struct pake_session_key {
    uint32_t length;
    uint8_t key[PAKE_SESSION_KEY_LENGTH];
};

struct pake_shared_secret {
    uint32_t length;
    uint8_t shared_secret[PAKE_SHARED_SECRET_LENGTH];
};

struct epk {
    uint32_t length;
    uint8_t epk[PAKE_EPK_LENGTH];
};

struct esk {
    uint32_t length;
    uint8_t esk[PAKE_ESK_LENGTH];
};

struct pake_server {
    struct key_agreement_server server_info;
    uint32_t key_length;
    struct hc_pin pin;
    struct hc_salt salt;
    struct hc_auth_id self_id;
    struct hc_auth_id peer_id;
    struct challenge self_challenge;
    struct challenge peer_challenge;
    struct esk self_esk;
    struct pake_session_key session_key;
    struct pake_hmac_key hmac_key;
    struct hc_session_key service_key;
    enum large_prime_number_type prime_type;
};

struct kcf_key {
    uint32_t length;
    uint8_t kcf[KCF_BUFF_LENGTH];
};

struct pake_start_request_data {
    struct key_agreement_version peer_version;
    struct key_agreement_version peer_support_version;
    int32_t operation_code;
    int32_t epk_len;
};

struct pake_start_response_data {
    struct key_agreement_version self_version;
    struct key_agreement_version self_support_version;
    struct challenge challenge;
    struct hc_salt salt;
    struct epk epk;
};

struct pake_end_request_data {
    struct challenge challenge;
    struct epk epk;
    struct hmac kcf_data;
};

struct pake_end_response_data {
    struct hmac kcf_data;
};

static inline uint32_t pake_server_sn(struct pake_server *server)
{
    return server->server_info.protocol_base_info.sn;
}

int32_t send_pake_start_response(struct pake_server *pake_server, struct message *receive, struct message *send);
int32_t send_pake_end_response(struct pake_server *pake_server, struct message *receive, struct message *send);

#else /* _CUT_XXX_ */

struct pake_server {
    char rsv;
};

#endif /* _CUT_XXX_ */

struct pake_server *build_pake_server(const struct hc_pin *pin, uint32_t key_length, const struct hc_auth_id *client,
    const struct hc_auth_id *server);
void destroy_pake_server(struct pake_server *pake_server);

#endif /* __PAKE_SERVER_H__ */
