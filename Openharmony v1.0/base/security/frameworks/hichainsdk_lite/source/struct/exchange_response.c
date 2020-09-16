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

#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) || defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))

#include <securec.h>
#include "log.h"
#include "mem_stat.h"
#include "jsonutil.h"
#include "commonutil.h"
#include "base.h"
#include "parsedata.h"
#include "exchange_auth_info.h"
#include "key_agreement_version.h"

void *parse_exchange_response(const char *payload, enum json_object_data_type data_type)
{
    exchange_response_data *exchange_response = (exchange_response_data *)MALLOC(sizeof(exchange_response_data));
    if (exchange_response == NULL) {
        return NULL;
    }
    (void)memset_s(exchange_response, sizeof(*exchange_response), 0, sizeof(*exchange_response));
    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Exchange Response parse payload failed");
        goto error;
    }
    /* authData */
    const char *ex_auth_info = get_json_string(obj, FIELD_EX_AUTH_INFO);
    if (ex_auth_info == NULL) {
        LOGE("Parse Exchange Response failed, field is null in exAuthInfo");
        goto error;
    }
    int32_t len_ex_auth_info = strlen(ex_auth_info);
    if ((len_ex_auth_info / BYTE_TO_HEX_OPER_LENGTH) > HC_AUTH_REQUEST_LEN) {
        LOGE("Parse Exchange Response failed, field length is not match in exAuthInfo");
        goto error;
    }
    exchange_response->cipher.length = len_ex_auth_info / BYTE_TO_HEX_OPER_LENGTH;
    exchange_response->cipher.size = exchange_response->cipher.length;
    exchange_response->cipher.val = (uint8_t *)MALLOC(exchange_response->cipher.size);
    if (exchange_response->cipher.val == NULL) {
        LOGE("malloc exchangeResponse cipher failed");
        goto error;
    }
    (void)memset_s(exchange_response->cipher.val, exchange_response->cipher.size, 0, exchange_response->cipher.size);
    if (hex_string_to_byte(ex_auth_info, len_ex_auth_info, exchange_response->cipher.val) != HC_OK) {
        goto error;
    }
    free_payload(obj, data_type);
    return (void *)exchange_response;
error:
    free_payload(obj, data_type);
    free_exchange_response(exchange_response);
    return NULL;
}

void free_exchange_response(void *obj)
{
    if (obj != NULL) {
        exchange_response_data *data = obj;
        if (data->cipher.val != NULL) {
            FREE(data->cipher.val);
        }
        FREE(data);
    }
}

char *make_exchange_response(void *data)
{
    exchange_response_data *exchange_response = data;
    /* authinfo */
    uint8_t *tmp_data_hex = raw_byte_to_hex_string(exchange_response->cipher.val, exchange_response->cipher.length);
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
        EXCHANGE_RESPONSE, FIELD_PAYLOAD, FIELD_EX_AUTH_INFO, tmp_data_hex) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    FREE(tmp_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(exchange_response)

#endif /* _CUT_XXX_ */
