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

#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_) || defined(_CUT_ADD_) || defined(_CUT_ADD_SERVER_))

#include <securec.h>
#include "log.h"
#include "mem_stat.h"
#include "jsonutil.h"
#include "commonutil.h"
#include "parsedata.h"
#include "add_auth_info.h"
#include "key_agreement_version.h"

void *parse_add_auth_info_response(const char *payload, enum json_object_data_type data_type)
{
    add_response_data *add_auth_info_response = (add_response_data *)MALLOC(sizeof(add_response_data));
    if (add_auth_info_response == NULL) {
        return NULL;
    }
    (void)memset_s(add_auth_info_response, sizeof(*add_auth_info_response), 0, sizeof(*add_auth_info_response));
    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Add AuthInfo Response parse payload failed");
        goto error;
    }

    const char *add_return = get_json_string(obj, FIELD_ADD_RETURN); /* authData */
    if (add_return == NULL) {
        LOGE("Parse Add AuthInfo Response failed, field is null in addId");
        goto error;
    }
    int32_t len_add_return = strlen(add_return);
    if ((len_add_return / BYTE_TO_HEX_OPER_LENGTH) > HC_AUTH_DATA_BUFF_LEN) {
        LOGE("Parse Add AuthInfo Data Response, field length is not match in addId");
        goto error;
    }
    add_auth_info_response->cipher.length = len_add_return / BYTE_TO_HEX_OPER_LENGTH;
    add_auth_info_response->cipher.size = add_auth_info_response->cipher.length;
    add_auth_info_response->cipher.val = (uint8_t *)MALLOC(add_auth_info_response->cipher.size);
    if (add_auth_info_response->cipher.val == NULL) {
        LOGE("Add AuthInfo Data Response cipher val malloc fail");
        goto error;
    }
    (void)memset_s(add_auth_info_response->cipher.val, add_auth_info_response->cipher.size,
                   0, add_auth_info_response->cipher.size);
    if (hex_string_to_byte(add_return, len_add_return, add_auth_info_response->cipher.val) != HC_OK)
        goto error;
    free_payload(obj, data_type);
    return (void *)add_auth_info_response;
error:
    free_payload(obj, data_type);
    free_add_auth_info_response(add_auth_info_response);
    return NULL;
}

void free_add_auth_info_response(void *obj)
{
    if (obj != NULL) {
        add_response_data *data = obj;
        if (data->cipher.val != NULL) {
            FREE(data->cipher.val);
        }
        FREE(data);
    }
}

char *make_add_auth_info_response(void *data)
{
    add_response_data *add_auth_info_response = data;
    /* authdata */
    uint8_t *tmp_data_hex = raw_byte_to_hex_string(add_auth_info_response->cipher.val,
                                                   add_auth_info_response->cipher.length);
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
        ADD_AUTHINFO_RESPONSE, FIELD_PAYLOAD, FIELD_ADD_RETURN, tmp_data_hex) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    FREE(tmp_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(add_auth_info_response)

#endif /* _CUT_XXX_ */
