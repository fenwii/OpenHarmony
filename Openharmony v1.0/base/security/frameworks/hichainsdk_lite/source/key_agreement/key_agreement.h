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

#ifndef __KEY_AGREEMENT_H__
#define __KEY_AGREEMENT_H__

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

enum protocol_state {
    PROTOCOL_UNINIT = 0,
    PROTOCOL_INIT,
    START_REQUEST,  /* C->S */
    START_RESPONSE, /* S->C */
    END_REQUEST,    /* C->S */
    PROTOCOL_TIMEOUT,
    PROTOCOL_ERROR,
    PROTOCOL_FINISH
};

enum protocol_action {
    SEND_START_REQUEST = 1,
    SEND_START_RESPONSE,
    SEND_END_REQUEST,
    SEND_END_RESPONSE,
    RECEIVE_END_RESPONSE
};

#define CHALLENGE_BUFF_LENGTH 16

struct key_agreement_protocol {
    enum protocol_state state;
    enum protocol_state last_state;
    uint32_t sn;
    time_t last_time_sec;
};

/* first.second.third */
struct key_agreement_version {
    uint32_t first;
    uint32_t second;
    uint32_t third;
};

struct challenge {
    uint32_t length;
    uint8_t challenge[CHALLENGE_BUFF_LENGTH];
};

void init_protocol(struct key_agreement_protocol *handle);
void set_state(struct key_agreement_protocol *handle, enum protocol_state new_state);
void set_last_time_sec(struct key_agreement_protocol *handle);
struct key_agreement_version get_current_version(void);
bool is_peer_support_current_version(struct key_agreement_version *peer_version,
    struct key_agreement_version *peer_support_version);

#endif /* __KEY_AGREEMENT_H__ */
