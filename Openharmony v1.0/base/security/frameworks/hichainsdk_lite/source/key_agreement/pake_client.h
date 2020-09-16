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

#ifndef __PAKE_CLIENT_H__
#define __PAKE_CLIENT_H__

#include "hichain.h"
#include "base.h"

#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_CLIENT_))

#include "pake_server.h"
#include "key_agreement_client.h"

struct pake_client {
    struct key_agreement_client client_info;
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
    struct epk self_epk;
    struct epk peer_epk;
    struct pake_shared_secret shared_secret;
    struct hmac kcf_data;
    const struct session_identity *identity;
    int32_t operation_code;
};

static inline uint32_t pake_client_sn(struct pake_client *client)
{
    return client->client_info.protocol_base_info.sn;
}

int32_t send_pake_start_request(struct pake_client *pake_client, struct message *send);
int32_t send_pake_end_request(struct pake_client *pake_client, const struct message *receive, struct message *send);
int32_t receive_pake_end_response(struct pake_client *pake_client, struct message *receive);

#else /* _CUT_XXX_ */

struct pake_client {
    char rsv;
};

#endif /* _CUT_XXX_ */

struct pake_client *build_pake_client(const struct session_identity *identity, const struct hc_pin *pin,
    uint32_t key_length, const struct hc_auth_id *client, const struct hc_auth_id *server);
void destroy_pake_client(struct pake_client *pake_client);

#endif /* __PAKE_CLIENT_H__ */
