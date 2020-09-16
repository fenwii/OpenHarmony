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

#include <securec.h>
#include "log.h"
#include "mem_stat.h"
#include "jsonutil.h"
#include "commonutil.h"
#include "parsedata.h"
#include "remove_auth_info.h"
#include "key_agreement_version.h"

void *parse_rmv_auth_info_response(const char *payload, enum json_object_data_type data_type)
{
    remove_response_data *rmv_auth_info_response = (remove_response_data *)MALLOC(sizeof(remove_response_data));
    if (rmv_auth_info_response == NULL) {
        return NULL;
    }
    (void)memset_s(rmv_auth_info_response, sizeof(*rmv_auth_info_response), 0, sizeof(*rmv_auth_info_response));
    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Rmv AuthInfo Response parse payload failed");
        goto error;
    }
    /* authData */
    const char *rmv_return = get_json_string(obj, FIELD_RMV_RETURN);
    if (rmv_return == NULL) {
        LOGE("Parse Rmv AuthInfo Response failed, field is null in rmvReturn");
        goto error;
    }
    int32_t len_rmv_return = strlen(rmv_return);
    if ((len_rmv_return / BYTE_TO_HEX_OPER_LENGTH) > HC_AUTH_DATA_BUFF_LEN) {
        LOGE("Parse Rmv AuthInfo Response failed, field length is not match in rmvReturn");
        goto error;
    }
    rmv_auth_info_response->cipher.length = len_rmv_return / BYTE_TO_HEX_OPER_LENGTH;
    rmv_auth_info_response->cipher.size = rmv_auth_info_response->cipher.length;
    rmv_auth_info_response->cipher.val = (uint8_t *)MALLOC(rmv_auth_info_response->cipher.size);
    if (rmv_auth_info_response->cipher.val == NULL) {
        LOGE("malloc rmvAuthInfoResponse cipher failed");
        goto error;
    }
    (void)memset_s(rmv_auth_info_response->cipher.val, rmv_auth_info_response->cipher.size,
                   0, rmv_auth_info_response->cipher.size);
    if (hex_string_to_byte(rmv_return, len_rmv_return, rmv_auth_info_response->cipher.val) != HC_OK) {
        goto error;
    }
    free_payload(obj, data_type);
    return (void *)rmv_auth_info_response;
error:
    free_payload(obj, data_type);
    free_rmv_auth_info_response(rmv_auth_info_response);
    return NULL;
}

void free_rmv_auth_info_response(void *obj)
{
    if (obj != NULL) {
        remove_response_data *data = obj;
        if (data->cipher.val != NULL) {
            FREE(data->cipher.val);
        }
        FREE(data);
    }
}

char *make_rmv_auth_info_response(void *data)
{
    remove_response_data *rmv_auth_info_response_data = data;
    /* authinfo */
    uint8_t *tmp_data_hex = raw_byte_to_hex_string(rmv_auth_info_response_data->cipher.val,
                                                   rmv_auth_info_response_data->cipher.length);
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
        REMOVE_AUTHINFO_RESPONSE, FIELD_PAYLOAD, FIELD_RMV_RETURN, tmp_data_hex) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    FREE(tmp_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(rmv_auth_info_response)

#endif /* _CUT_XXX_ */
