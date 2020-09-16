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

#ifndef __DISTRIBUTION_H__
#define __DISTRIBUTION_H__

#include <stdint.h>
#include "hichain.h"
#include "pake_client.h"
#include "pake_server.h"
#include "sts_client.h"
#include "sts_server.h"
#include "sec_clone_server.h"

enum hichain_state {
    INIT_STATE = 0,
    KEY_AGREEMENT_STATE = 1,
    OPERATION_STATE,
    OVER_STATE
};

struct hichain {
    struct session_identity identity;
    enum hc_type type;
    enum hichain_state state;
    enum hichain_state last_state;
    int32_t operation_code;
    struct pake_client *pake_client;
    struct pake_server *pake_server;
    struct sts_server *sts_server;
    struct sts_client *sts_client;
    struct sec_clone_server *sec_clone_server;
    struct auth_info_cache *auth_info;
    struct hc_call_back cb;
};

enum message_modular {
    INVALID_MODULAR = 0,
    PAKE_MODULAR = 1,
    STS_MODULAR,
    EXCHANGE_MODULAR,
    ADD_MODULAR,
    REMOVE_MODULAR,
    SEC_CLONE_MODULAR,
    INFORM_MODULAR,
};

struct header_analysis {
    int32_t modular;
    int32_t msg_type;
    bool is_request_msg;
};

struct header_analysis navigate_message(uint32_t message_code);
int32_t check_message_support(struct hichain *hichain, const struct header_analysis *nav,
    const struct message *receive);
int32_t proc_message(struct hichain *handle, struct header_analysis *nav, struct message *receive,
    struct message *send);
int32_t connect_message(struct hichain *handle, struct header_analysis *nav, struct message *send);
#endif /* __DISTRIBUTION_H__ */
