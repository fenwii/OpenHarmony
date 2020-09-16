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

#include "remove_auth_info_client.h"
#include <string.h>
#include <stdlib.h>
#include <securec.h>
#include "log.h"
#include "base.h"
#include "mem_stat.h"
#include "remove_auth_info.h"
#include "huks_adapter.h"

#if !(defined(_CUT_STS_) || defined(_CUT_STS_CLIENT_) || defined(_CUT_REMOVE_) || defined(_CUT_REMOVE_CLIENT_))

int32_t build_remove_request_data(struct remove_auth_info_client *auth_info_client, remove_request_data *send);
int32_t send_remove_request(const struct hichain *hichain, struct message *send)
{
    struct remove_auth_info_client auth_info_client;

    auth_info_client.sts_client = hichain->sts_client;
    auth_info_client.auth_info = hichain->auth_info;

    remove_request_data *request_data = (remove_request_data *)MALLOC(sizeof(remove_request_data));
    if (request_data == NULL) {
        LOGE("Malloc request_data failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(request_data, sizeof(*request_data), 0, sizeof(*request_data));

    int32_t ret = build_remove_request_data(&auth_info_client, request_data);
    if (ret != HC_OK) {
        LOGE("Build remove request data failed, error code is %d", ret);
        FREE(request_data);
        return ret;
    }
    send->payload = request_data;
    send->msg_code = REMOVE_AUTHINFO_REQUEST;

    return HC_OK;
}

int32_t parse_remove_response_data(struct remove_auth_info_client *auth_info_client, remove_response_data *receive);
int32_t receive_remove_response(const struct hichain *hichain, const struct message *receive)
{
    struct remove_auth_info_client auth_info_client;
    auth_info_client.sts_client = hichain->sts_client;
    auth_info_client.auth_info = hichain->auth_info;

    int32_t ret = parse_remove_response_data(&auth_info_client, (remove_response_data *)receive->payload);
    if (ret != HC_OK) {
        LOGE("Parse remove response data failed, error code is %d", ret);
        return ret;
    }

    return HC_OK;
}

int32_t build_remove_request_data(struct remove_auth_info_client *auth_info_client, remove_request_data *send)
{
    struct ltpk ltpk;
    struct remove_auth_data authData;
    struct uint8_buff payload = { NULL, 0, 0 };
    struct uint8_buff plain = { NULL, 0, 0 };

    struct service_id service_id = generate_service_id(auth_info_client->sts_client->identity);
    enum huks_key_alias_type alias_type = (auth_info_client->auth_info->user_type == HC_USER_TYPE_ACCESSORY) ?
                                           KEY_ALIAS_ACCESSOR_PK : KEY_ALIAS_CONTROLLER_PK;
    struct hc_key_alias alias = generate_key_alias(&service_id,
                                                   &auth_info_client->auth_info->auth_id,
                                                   alias_type);

    int32_t ret = export_lt_public_key(&alias, &ltpk);
    if (ret != HC_OK) {
        LOGE("Generate ltpk return value is %d", ret);
        return HC_GET_LTPK_FAILED;
    }

    authData.user_type = HC_USER_TYPE_ACCESSORY;
    authData.auth_id = auth_info_client->auth_info->auth_id;
    uint8_t *tmp = (uint8_t *)make_rmv_auth_info_data((void *)&authData);
    if (tmp == NULL) {
        LOGE("Make remove auth info data failed");
        return HC_BUILD_SEND_DATA_FAILED;
    }
    plain.val = tmp;
    plain.length = strlen((const char *)tmp);
    plain.size = plain.length + 1;
    payload.val = (uint8_t *)MALLOC(HC_RM_AUTH_DATA_BUFF_LEN);
    if (payload.val == NULL) {
        LOGE("Malloc payload, val failed");
        FREE(tmp);
        return HC_MALLOC_FAILED;
    }
    payload.size = HC_RM_AUTH_DATA_BUFF_LEN;
    payload.length = 0;

    ret = encrypt_payload((struct var_buffer *)&auth_info_client->sts_client->session_key,
                          &plain, "hichain_remove_info_request", &payload);
    FREE(tmp);
    if (ret != HC_OK) {
        LOGE("Decrypt exchange request payload failed");
        FREE(payload.val);
        return ret;
    }
    send->cipher = payload;

    return HC_OK;
}

int32_t parse_remove_response_data(struct remove_auth_info_client *auth_info_client, remove_response_data *receive)
{
    struct uint8_buff plain = { 0, 0, 0 };
    int32_t ret = decrypt_payload((struct var_buffer *)&auth_info_client->sts_client->session_key,
                                  &receive->cipher, "hichain_remove_info_response", &plain);
    if (ret != HC_OK) {
        FREE(plain.val);
        LOGE("Decrypt rm request payload failed");
        return ret;
    }

    ret = plain.val[0];
    FREE(plain.val);
    if (ret != HC_OK) {
        LOGE("RemoveAuthStartRequest failed, ret: %d", ret);
        return ret;
    }

    return  HC_OK;
}

#else /* _CUT_XXX_ */
int32_t send_remove_request(const struct hichain *hichain, struct message *send)
{
    LOGE("Donot support sts client for remove");
    (void)hichain;
    (void)send;
    return HC_UNSUPPORT;
}
#endif /* _CUT_XXX_ */
