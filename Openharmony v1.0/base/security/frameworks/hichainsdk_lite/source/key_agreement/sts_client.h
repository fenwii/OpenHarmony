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

#ifndef __STS_CLIENT_H__
#define __STS_CLIENT_H__

#include "key_agreement_server.h"
#include <stdint.h>
#include "base.h"
#include "hichain.h"
#include "sts_server.h"
#include "parsedata.h"
#include "key_agreement_client.h"

#if !(defined(_CUT_STS_) || defined(_CUT_STS_CLIENT_))

struct sts_client {
    struct key_agreement_client client_info;
    const struct session_identity *identity;
    int32_t operation_code;
    struct stsk self_private_key;
    struct stpk self_public_key;
    struct stpk peer_public_key;
    struct hc_session_key session_key;
    struct hc_session_key service_key;
    uint32_t key_length;
    struct challenge peer_challenge;
    struct challenge my_challenge;
    struct hc_auth_id peer_id;
    struct hc_auth_id self_id;
    enum hc_user_type peer_user_type;
    struct auth_data my_auth_data;
    struct auth_data peer_auth_data;
    struct hc_salt salt;
    hc_handle hichain_handle;
};

static inline uint32_t sts_client_sn(struct sts_client *client)
{
    return client->client_info.protocol_base_info.sn;
}

int32_t send_sts_start_request(struct sts_client *sts_client, struct message *send);
int32_t send_sts_end_request(struct sts_client *sts_client, const struct message *receive, struct message *send);
int32_t receive_sts_end_response(struct sts_client *sts_client, struct message *receive);

#else /* _CUT_XXX_ */

struct sts_client {
    char rsv;
};

#endif /* _CUT_XXX_ */

struct sts_client *build_sts_client(const hc_handle hichain_handle, uint32_t key_length,
    const struct hc_auth_id *client, const struct hc_auth_id *server);
void destroy_sts_client(struct sts_client *handle);

#endif /* __STS_CLIENT_H__ */
