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

#include "build_object.h"
#include <securec.h>
#include "log.h"
#include "auth_info.h"

struct object_map {
    int32_t modular;
    bool is_client;
    void **object;
};

struct object_relation {
    int32_t src_modular;
    int32_t dst_modular;
    bool src_is_client;
    bool dst_is_client;
};

static void **get_object(const struct object_map *map, uint32_t n, int32_t modular, bool is_client);
static bool check_mutex_object_is_null(const struct object_map *map, uint32_t n, int32_t modular, bool is_client);
static bool check_depend_object_is_not_null(const struct object_map *map, uint32_t n, int32_t modular, bool is_client);
static void *build_object_by_modular(struct hichain *hichain, int32_t modular, bool is_client, const void *params);
static bool check_param_is_valid(const struct operation_parameter *para);
int32_t build_object(struct hichain *hichain, int32_t modular, bool is_client, const void *params)
{
    const struct object_map map[] = { { PAKE_MODULAR, true, (void **)&hichain->pake_client },
                                      { PAKE_MODULAR, false, (void **)&hichain->pake_server },
                                      { STS_MODULAR, true, (void **)&hichain->sts_client },
                                      { STS_MODULAR, false, (void **)&hichain->sts_server },
                                      { ADD_MODULAR, true, (void **)&hichain->auth_info },
                                      { REMOVE_MODULAR, true, (void **)&hichain->auth_info },
                                      { SEC_CLONE_MODULAR, false, (void **)&hichain->sec_clone_server } };
    void **object = get_object(map, sizeof(map) / sizeof(map[0]), modular, is_client);
    if ((object == NULL) || (*object != NULL)) {
        DBG_OUT("No sub-objects need to be applied for");
        return HC_OK;
    }
    if (check_mutex_object_is_null(map, sizeof(map) / sizeof(map[0]), modular, is_client) == false) {
        LOGE("The mutex sub-object have been created, create %d:%d sub-object failed", modular, is_client);
        return HC_REPEATED_REFERENCE;
    }
    if (check_depend_object_is_not_null(map, sizeof(map) / sizeof(map[0]), modular, is_client) == false) {
        LOGE("The depend sub-object is not created, create %d:%d sub-object failed", modular, is_client);
        return HC_NEED_DEPEND;
    }
    *object = build_object_by_modular(hichain, modular, is_client, params);
    if (*object == NULL) {
        LOGE("Create %d:%d sub-object failed", modular, is_client);
        return HC_BUILD_OBJECT_FAILED;
    }
    DBG_OUT("Create %d:%d sub-object success", modular, is_client);
    return HC_OK;
}

static void **get_object(const struct object_map *map, uint32_t n, int32_t modular, bool is_client)
{
    for (uint32_t i = 0; i < n; i++) {
        if ((modular == map[i].modular) && (is_client == map[i].is_client)) {
            return map[i].object;
        }
    }

    return NULL;
}

typedef const struct object_relation *object_relation_ptr;

static uint32_t select_relation_map(const struct object_relation *map, uint32_t n, int32_t modular, bool is_client,
    object_relation_ptr *select_map)
{
    uint32_t count = 0;

    for (uint32_t i = 0; i < n; i++) {
        if ((modular == map[i].src_modular) && (is_client == map[i].src_is_client)) {
            select_map[count] = &map[i];
            count++;
        }
    }
    return count;
}

static bool check_mutex_object_is_null(const struct object_map *map, uint32_t n, int32_t modular, bool is_client)
{
    const struct object_relation mutex_map[] = { { PAKE_MODULAR, STS_MODULAR, true, false },
                                                 { STS_MODULAR, PAKE_MODULAR, false, true },
                                                 { PAKE_MODULAR, STS_MODULAR, true, true },
                                                 { STS_MODULAR, PAKE_MODULAR, true, true },
                                                 { PAKE_MODULAR, STS_MODULAR, false, false },
                                                 { STS_MODULAR, PAKE_MODULAR, false, false },
                                                 { PAKE_MODULAR, STS_MODULAR, false, true },
                                                 { STS_MODULAR, PAKE_MODULAR, true, false },
                                                 { STS_MODULAR, STS_MODULAR, true, false },
                                                 { STS_MODULAR, STS_MODULAR, false, true },
                                                 { ADD_MODULAR, STS_MODULAR, true, false },
                                                 { STS_MODULAR, ADD_MODULAR, false, true },
                                                 { REMOVE_MODULAR, STS_MODULAR, true, false },
                                                 { STS_MODULAR, REMOVE_MODULAR, false, true },
                                                 { PAKE_MODULAR, SEC_CLONE_MODULAR, false, false },
                                                 { SEC_CLONE_MODULAR, PAKE_MODULAR, false, false } };
    object_relation_ptr select_map[sizeof(mutex_map) / sizeof(mutex_map[0])] = {0};
    uint32_t count = select_relation_map(mutex_map, sizeof(mutex_map) / sizeof(mutex_map[0]), modular,
        is_client, select_map);
    if (count == 0) { /* no muutex sub object */
        return true;
    }
    for (uint32_t i = 0; i < n; i++) {
        if ((map[i].modular == modular) && (map[i].is_client == is_client)) { /* skip sub object that will be created */
            continue;
        }
        if (*map[i].object == NULL) { /* null sub object is correct even mutex */
            continue;
        }
        for (uint32_t j = 0; j < count; j++) {
            if ((map[i].modular == select_map[j]->dst_modular) && (map[i].is_client == select_map[j]->dst_is_client)) {
                return false; /* mutex sub object and not null */
            }
        }
    }
    return true;
}

static bool check_depend_object_is_not_null(const struct object_map *map, uint32_t n, int32_t modular, bool is_client)
{
    const struct object_relation depend_map[] = { { ADD_MODULAR, STS_MODULAR, true, true },
                                                  { REMOVE_MODULAR, STS_MODULAR, true, true },
                                                  { SEC_CLONE_MODULAR, STS_MODULAR, false, false } };
    object_relation_ptr select_map[sizeof(depend_map) / sizeof(depend_map[0])] = {0};
    uint32_t count = select_relation_map(depend_map, sizeof(depend_map) / sizeof(depend_map[0]),
                                         modular, is_client, select_map);
    if (count == 0) { /* no dependent sub object */
        return true;
    }
    for (uint32_t i = 0; i < n; i++) {
        if ((map[i].modular == modular) && (map[i].is_client == is_client)) { /* skip sub object that will be created */
            continue;
        }
        if (*map[i].object != NULL) { /* null sub object is correct even dependent */
            continue;
        }
        for (uint32_t j = 0; j < count; j++) {
            if ((map[i].modular == select_map[j]->dst_modular) && (map[i].is_client == select_map[j]->dst_is_client)) {
                return false; /* depentend sub object and not null */
            }
        }
    }
    return true;
}

typedef void *(*build_sub_object)(struct hichain *hichain, const void *params);
struct build_sub_object_map {
    int32_t modular;
    bool is_client;
    build_sub_object build_func;
};

static void *build_pake_client_object(struct hichain *hichain, const void *params);
static void *build_pake_server_object(struct hichain *hichain, const void *params);
static void *build_sts_client_object(struct hichain *hichain, const void *params);
static void *build_sts_server_object(struct hichain *hichain, const void *params);
static void *build_auth_info_client_object(struct hichain *hichain, const void *params);
static void *build_sec_clone_server_object(struct hichain *hichain, const void *params);
static void *build_object_by_modular(struct hichain *hichain, int32_t modular, bool is_client, const void *params)
{
    const struct build_sub_object_map map[] = { { PAKE_MODULAR, true, build_pake_client_object },
                                                { PAKE_MODULAR, false, build_pake_server_object },
                                                { STS_MODULAR, true, build_sts_client_object },
                                                { STS_MODULAR, false, build_sts_server_object },
                                                { ADD_MODULAR, true, build_auth_info_client_object },
                                                { REMOVE_MODULAR, true, build_auth_info_client_object },
                                                { SEC_CLONE_MODULAR, false, build_sec_clone_server_object } };
    for (uint32_t i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
        if ((map[i].modular == modular) && (map[i].is_client == is_client)) {
            return map[i].build_func(hichain, params);
        }
    }
    return NULL;
}

static void *build_pake_client_object(struct hichain *hichain, const void *params)
{
    (void)params;
    struct hc_pin pin = { 0, {0} };
    struct operation_parameter para;

    (void)memset_s(&para, sizeof(para), 0, sizeof(para));
    hichain->cb.get_protocol_params(&hichain->identity, hichain->operation_code, &pin, &para);
    if (check_param_is_valid(&para) == false) {
        LOGE("Param invalid");
        return NULL;
    }
    if (pin.length > HC_PIN_BUFF_LEN) {
        LOGE("PIN invalid");
        return NULL;
    }
    return build_pake_client(&hichain->identity, &pin, para.key_length, &para.self_auth_id, &para.peer_auth_id);
}

static void *build_pake_server_object(struct hichain *hichain, const void *params)
{
    (void)params;
    struct hc_pin pin = { 0, {0} };
    struct operation_parameter para;

    (void)memset_s(&para, sizeof(para), 0, sizeof(para));
    hichain->cb.get_protocol_params(&hichain->identity, hichain->operation_code, &pin, &para);
    if (check_param_is_valid(&para) == false) {
        LOGE("Param invalid");
        return NULL;
    }
    if (pin.length > HC_PIN_BUFF_LEN) {
        LOGE("PIN invalid");
        return NULL;
    }
    return build_pake_server(&pin, para.key_length, &para.peer_auth_id, &para.self_auth_id);
}

static void *build_sts_client_object(struct hichain *hichain, const void *params)
{
    struct operation_parameter *para = (struct operation_parameter *)params;

    return build_sts_client(hichain, para->key_length, &para->self_auth_id,
                            &para->peer_auth_id);
}

static void *build_sts_server_object(struct hichain *hichain, const void *params)
{
    (void)params;
    struct hc_pin pin = { 0, {0} };
    struct operation_parameter para;

    (void)memset_s(&para, sizeof(para), 0, sizeof(para));
    hichain->cb.get_protocol_params(&hichain->identity, hichain->operation_code, &pin, &para);
    if (check_param_is_valid(&para) == false) {
        LOGE("Protocol param invalid");
        return NULL;
    }
    return build_sts_server(hichain, para.key_length, &para.peer_auth_id, &para.self_auth_id);
}

static void *build_auth_info_client_object(struct hichain *hichain, const void *params)
{
    struct auth_info_cache *para = (struct auth_info_cache *)params;

    hichain->auth_info = build_auth_client_info(para->auth_id, para->user_type);

    return hichain->auth_info;
}

static void *build_sec_clone_server_object(struct hichain *hichain, const void *params)
{
    (void)params;
    return build_sec_clone_server(hichain);
}

static bool check_param_is_valid(const struct operation_parameter *para)
{
    check_ptr_return_val(para, false);
    if (para->self_auth_id.length > HC_AUTH_ID_BUFF_LEN) {
        LOGE("Self auth id length error");
        return false;
    }
    if (para->peer_auth_id.length > HC_AUTH_ID_BUFF_LEN) {
        LOGE("Peer auth id length error");
        return false;
    }
    if (para->key_length > HC_SESSION_KEY_LEN) {
        LOGE("Key length error");
        return false;
    }
    return true;
}
