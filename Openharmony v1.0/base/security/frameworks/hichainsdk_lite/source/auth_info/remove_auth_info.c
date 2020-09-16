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

#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_) || defined(_CUT_REMOVE_) || defined(_CUT_REMOVE_SERVER_))

#include "remove_auth_info.h"
#include "log.h"
#include "base.h"
#include "mem_stat.h"
#include "parsedata.h"
#include "huks_adapter.h"

#define HICHAIN_REMOVE_INFO_REQUEST  "hichain_remove_info_request"
#define HICHAIN_REMOVE_INFO_RESPONSE "hichain_remove_info_response"

static int32_t parse_remove_request_data(const struct hichain *hichain, remove_request_data *receive,
                                         struct auth_info_cache *cache);
static int32_t build_remove_response_data(const struct hichain *hichain, remove_response_data *send);
static int32_t delete_auth_info(const struct hichain *hichain, int32_t user_type, struct hc_auth_id *auth_id);
int32_t send_remove_response(const struct hichain *hichain, struct message *receive, struct message *send)
{
    remove_response_data *send_data = malloc_auth_info_msg(HC_AUTH_RESPONSE_LEN);
    if (send_data == NULL) {
        LOGE("Malloc struct remove_response_data failed");
        send->msg_code = INFORM_MESSAGE;
        return HC_MALLOC_FAILED;
    }
    struct auth_info_cache cache;
    int32_t ret = parse_remove_request_data(hichain, (remove_request_data *)receive->payload, &cache);
    if (ret != HC_OK) {
        LOGE("Parse remove request failed, error code is %d", ret);
        goto error;
    }
    ret = build_remove_response_data(hichain, send_data);
    if (ret != HC_OK) {
        LOGE("Build remove response failed, error code is %d", ret);
        goto error;
    }
    ret = delete_auth_info(hichain, cache.user_type, &cache.auth_id);
    if (ret != HC_OK) {
        LOGE("Delete ltpk failed, error code is %d", ret);
        goto error;
    }

    DBG_OUT("Send remove response success");
    send->payload = send_data;
    send->msg_code = REMOVE_AUTHINFO_RESPONSE;
    return HC_OK;

error:
    free_auth_info_msg(send_data);
    send->msg_code = INFORM_MESSAGE;
    return ret;
}

static int32_t get_field_from_request_payload(struct uint8_buff *payload, int32_t *user_type,
    struct hc_auth_id *auth_id);
static int32_t parse_remove_request_data(const struct hichain *hichain, remove_request_data *receive,
    struct auth_info_cache *cache)
{
    const struct sts_session_key *session_key = get_sts_session_key(hichain);
    if (session_key == NULL) {
        LOGE("Get sts session key failed");
        return HC_STS_OBJECT_ERROR;
    }
    struct uint8_buff plain = { 0, 0, 0 };
    int32_t ret = decrypt_payload((const struct var_buffer *)session_key, &receive->cipher,
                                  HICHAIN_REMOVE_INFO_REQUEST, &plain);
    if (ret != HC_OK) {
        LOGE("Decrypt remove request payload failed");
        return ret;
    }
    ret = get_field_from_request_payload(&plain, &cache->user_type, &cache->auth_id);
    FREE(plain.val);
    plain.val = NULL;
    if (ret != HC_OK) {
        LOGE("Get field from remove request message failed, error code is %d", ret);
        return ret;
    }

    DBG_OUT("Save ltpk success");
    return HC_OK;
}

static int32_t build_remove_response_data(const struct hichain *hichain, remove_response_data *send)
{
    uint8_t array[sizeof(int32_t)] = {0};
    struct uint8_buff plain = {
        .val = array,
        .size = sizeof(array),
        .length = sizeof(array)
    };

    const struct sts_session_key *key = get_sts_session_key(hichain);
    int32_t ret = encrypt_payload((const struct var_buffer *)key, &plain,
                                  HICHAIN_REMOVE_INFO_RESPONSE, &send->cipher);
    if (ret != HC_OK) {
        LOGE("Encrypt remove response failed, error code is %d", ret);
        return HC_ENCRYPT_FAILED;
    }

    return HC_OK;
}

static int32_t delete_auth_info(const struct hichain *hichain, int32_t user_type, struct hc_auth_id *auth_id)
{
    struct service_id service_id = generate_service_id(&hichain->identity);
    if (service_id.length == 0) {
        LOGE("Generate service id failed");
        return HC_GEN_SERVICE_ID_FAILED;
    }
    enum huks_key_alias_type alias_type = (user_type == HC_USER_TYPE_ACCESSORY) ?
                                           KEY_ALIAS_ACCESSOR_PK : KEY_ALIAS_CONTROLLER_PK;
    struct hc_key_alias alias = generate_key_alias(&service_id, auth_id, alias_type);
    if (alias.length == 0) {
        LOGE("Generate key alias failed");
        return HC_GEN_ALIAS_FAILED;
    }
    int32_t ret = check_lt_public_key_exist(&alias);
    if (ret == HC_OK) {
        ret = delete_lt_public_key(&alias);
        if (ret != HC_OK) {
            LOGE("Save ltpk failed, error code is %d", ret);
            return HC_SAVE_LTPK_FAILED;
        }
    }
    DBG_OUT("Save ltpk success");
    (void)user_type;
    return HC_OK;
}

static int32_t get_field_from_request_payload(struct uint8_buff *payload, int32_t *user_type,
    struct hc_auth_id *auth_id)
{
    struct remove_auth_data *rmv_auth_data = parse_rmv_auth_info_data((char *)payload->val, JSON_STRING_DATA);
    if (rmv_auth_data == NULL) {
        LOGE("ParseRmvAuthInfoData failed");
        return HC_DECRYPT_FAILED;
    }
    *user_type = rmv_auth_data->user_type;
    *auth_id = rmv_auth_data->auth_id;
    free_rmv_auth_info_data(rmv_auth_data);
    return HC_OK;
}

#endif /* _CUT_XXX_ */
