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

#include "add_auth_info_client.h"
#include <securec.h>
#include "huks_adapter.h"
#include "log.h"
#include "mem_stat.h"

#if !(defined(_CUT_STS_) || defined(_CUT_STS_CLIENT_) || defined(_CUT_ADD_) || defined(_CUT_ADD_CLIENT_))

int32_t send_add_request(const struct hichain *hichain, struct message *send)
{
    struct add_auth_info_client auth_info_client;
    auth_info_client.sts_client = hichain->sts_client;
    auth_info_client.auth_info = hichain->auth_info;

    add_request_data *request_data = (add_request_data *)MALLOC(sizeof(add_request_data));
    if (request_data == NULL) {
        LOGE("Malloc add request data failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(request_data, sizeof(*request_data), 0, sizeof(*request_data));

    int32_t ret = build_add_request_data(&auth_info_client, request_data);
    if (ret != HC_OK) {
        LOGE("Build add request data failed. error code is %d", ret);
        FREE(request_data);
        return ret;
    }

    send->payload = request_data;
    send->msg_code = ADD_AUTHINFO_REQUEST;

    return HC_OK;
}

int32_t receive_add_response(const struct hichain *hichain, const struct message *receive)
{
    struct add_auth_info_client auth_info_client;
    auth_info_client.sts_client = hichain->sts_client;
    auth_info_client.auth_info = hichain->auth_info;

    int32_t ret = parse_add_response_data(&auth_info_client, (add_response_data *)receive->payload);
    if (ret != HC_OK) {
        LOGE("Parse add response data failed. error code is %d", ret);
        return ret;
    }
    return HC_OK;
}

int32_t build_add_request_data(struct add_auth_info_client *auth_info_client, add_request_data *send)
{
    struct service_id service_id = generate_service_id(auth_info_client->sts_client->identity);
    enum huks_key_alias_type alias_type = (auth_info_client->auth_info->user_type == HC_USER_TYPE_ACCESSORY) ?
                                           KEY_ALIAS_ACCESSOR_PK : KEY_ALIAS_CONTROLLER_PK;
    struct hc_key_alias alias = generate_key_alias(&service_id,
                                                   &auth_info_client->auth_info->auth_id,
                                                   alias_type);
    struct ltpk lt_public_key = { 0, {0} };
    int32_t ret = export_lt_public_key(&alias, &lt_public_key);
    if (ret != HC_OK) {
        LOGE("Generate ltpk return value is %d", ret);
        return HC_GET_LTPK_FAILED;
    }

    struct add_auth_data auth_data;
    auth_data.user_type = auth_info_client->auth_info->user_type;
    auth_data.ltpk = lt_public_key;
    auth_data.auth_id = auth_info_client->auth_info->auth_id;

    uint8_t *tmp = (uint8_t *)make_add_auth_info_data((void *)&auth_data);
    if (tmp == NULL) {
        LOGE("Make add auth info data failed");
        return HC_BUILD_SEND_DATA_FAILED;
    }

    struct uint8_buff plain = { NULL, 0, 0 };
    plain.val = tmp;
    plain.length = strlen((const char *)tmp);
    plain.size = plain.length + 1;

    struct uint8_buff payload = { NULL, 0, 0 };
    payload.val = (uint8_t *)MALLOC(HC_ADD_AUTH_DATA_BUFF_LEN);
    if (payload.val == NULL) {
        LOGE("Malloc payload val failed");
        FREE(tmp);
        return HC_MALLOC_FAILED;
    }
    payload.size = HC_ADD_AUTH_DATA_BUFF_LEN;
    payload.length = 0;

    ret = encrypt_payload((struct var_buffer *)&auth_info_client->sts_client->session_key,
                          &plain, HC_ADD_INFO_REQUEST, &payload);
    FREE(tmp);
    if (ret != HC_OK) {
        LOGE("Decrypt exchange request payload failed");
        FREE(payload.val);
        return ret;
    }

    send->cipher = payload;
    return HC_OK;
}

int32_t parse_add_response_data(struct add_auth_info_client *auth_info_client, const add_response_data *receive)
{
    struct uint8_buff plain = { NULL, 0, 0 };
    int32_t ret = decrypt_payload((struct var_buffer *)&auth_info_client->sts_client->session_key,
                                  &receive->cipher, HC_ADD_INFO_RESPONSE, &plain);
    if (ret != HC_OK) {
        FREE(plain.val);
        LOGE("Decrypt add request payload failed");
        return ret;
    }

    ret = plain.val[0];
    FREE(plain.val);
    if (ret != HC_OK) {
        LOGE("Get decrypt plain value failed, ret: %d", ret);
        return ret;
    }

    return  HC_OK;
}

#else /* _CUT_XXX_ */
int32_t send_add_request(const struct hichain *hichain, struct message *send)
{
    LOGE("Donot support sts client for add");
    (void)hichain;
    (void)send;
    return HC_UNSUPPORT;
}
#endif /* _CUT_XXX_ */
