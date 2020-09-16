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

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))

#include <string.h>
#include <securec.h>
#include "jsonutil.h"
#include "commonutil.h"
#include "exchange_auth_info.h"
#include "log.h"
#include "key_agreement_version.h"

static void free_single_buff(void *obj)
{
    if (obj != NULL) {
        struct uint8_buff *data = (struct uint8_buff *)obj;
        if (data->val) {
            FREE(data->val);
            data->val = NULL;
        }
        FREE(data);
    }
}

static void *get_single_json_from_buff(const char *payload, const char *name, enum json_object_data_type data_type)
{
    struct uint8_buff *request_data = (struct uint8_buff *)MALLOC(sizeof(struct uint8_buff));
    if (request_data == NULL) {
        LOGE("MALLOC failed");
        return NULL;
    }

    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        goto error;
    }
    /* authData */
    const char *client_chall = get_json_string(obj, name);
    if (client_chall == NULL) {
        goto error;
    }

    int32_t json_data_len = strlen(client_chall);
    if ((json_data_len / BYTE_TO_HEX_OPER_LENGTH) > HC_AUTH_DATA_BUFF_LEN) { /* hex to byte length */
        goto error;
    }
    request_data->size = json_data_len / BYTE_TO_HEX_OPER_LENGTH; /* hex to byte length */
    request_data->length = json_data_len / BYTE_TO_HEX_OPER_LENGTH; /* hex to byte length */
    request_data->val = (uint8_t *)MALLOC(request_data->size);
    if (request_data->val == NULL) {
        goto error;
    }
    if (hex_string_to_byte(client_chall, json_data_len, request_data->val) != HC_OK) {
        goto error;
    }
    free_payload(obj, data_type);
    return (void *)request_data;

error:
    free_payload(obj, data_type);
    free_single_buff(request_data);
    return NULL;
}

static char *make_single_json_data(void *data, const char *name, int32_t msg_code)
{
    struct uint8_buff *src_data = data;
    uint8_t *tmp_data_hex = raw_byte_to_hex_string(src_data->val, src_data->length);
    if (tmp_data_hex == NULL) {
        return NULL;
    }

    char *ret_str = (char *)MALLOC(RET_STR_LENGTH);
    if (ret_str == NULL) {
        FREE(tmp_data_hex);
        return NULL;
    }

    (void)memset_s(ret_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(ret_str, RET_STR_LENGTH, RET_STR_LENGTH - 1, "{\"%s\":%d,\"%s\":{\"%s\":\"%s\"}}", FIELD_MESSAGE,
        msg_code, FIELD_PAYLOAD, name, tmp_data_hex) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    FREE(tmp_data_hex);
    return ret_str;
}

static char *make_single_json_data_srv_proof(void *data, const char *name, int32_t msg_code)
{
    struct uint8_buff *src_data = data;
    char *ret_str = (char *)MALLOC(RET_STR_LENGTH);
    if (ret_str == NULL) {
        return NULL;
    }
    (void)memset_s(ret_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(ret_str, RET_STR_LENGTH, RET_STR_LENGTH - 1, "{\"%s\":%d,\"%s\":{\"%s\":%s}}", FIELD_MESSAGE,
        msg_code, FIELD_PAYLOAD, name, src_data->val) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }

    return ret_str;
}

void *sec_clone_parse_client_request(const char *payload, enum json_object_data_type data_type)
{
    return get_single_json_from_buff(payload, "clientChallenge", data_type);
}

void sec_clone_free_client_request(void *obj)
{
    free_single_buff(obj);
}

char *sec_clone_make_srv_proof(void *data)
{
    return make_single_json_data_srv_proof(data, "serverProof", SEC_CLONE_START_RESPONSE);
}

void *sec_clone_parse_client_ack(const char *payload, enum json_object_data_type data_type)
{
    return get_single_json_from_buff(payload, "SecData", data_type);
}

void sec_clone_free_client_ack(void *obj)
{
    free_single_buff(obj);
}

char *sec_clone_make_clone_ret(void *data)
{
    return make_single_json_data(data, "cloneReturn", SEC_CLONE_ACK_RESPONSE);
}

void *sec_clone_parse_start_resp(const char *payload, enum json_object_data_type data_type)
{
    return get_single_json_from_buff(payload, "serverProof", data_type);
}

void *sec_clone_parse_ack_resp(const char *payload, enum json_object_data_type data_type)
{
    return get_single_json_from_buff(payload, "cloneReturn", data_type);
}
#else

#define DEFINE_SEC_CLONE_EMPTY_STRUCT_FUNC(name) \
    void *sec_clone_parse_##name(const char *payload, enum json_object_data_type data_type) \
    { \
        (void)payload; \
        (void)data_type; \
        return NULL; \
    } \
    void sec_clone_free_##name(void *obj) \
    { \
        (void)obj; \
    } \
    char *sec_clone_make_##name(void *data) \
    { \
        (void)data; \
        return "Current devices do not support this feature."; \
    }

#include "parsedata.h"
DEFINE_SEC_CLONE_EMPTY_STRUCT_FUNC(client_request)
DEFINE_SEC_CLONE_EMPTY_STRUCT_FUNC(srv_proof)
DEFINE_SEC_CLONE_EMPTY_STRUCT_FUNC(client_ack)
DEFINE_SEC_CLONE_EMPTY_STRUCT_FUNC(clone_ret)
DEFINE_SEC_CLONE_EMPTY_STRUCT_FUNC(start_resp)
DEFINE_SEC_CLONE_EMPTY_STRUCT_FUNC(ack_resp)

#endif
