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

void *parse_rmv_auth_info_request(const char *payload, enum json_object_data_type data_type)
{
    remove_request_data *rmv_auth_info_request = (remove_request_data *)MALLOC(sizeof(remove_request_data));
    if (rmv_auth_info_request == NULL) {
        return NULL;
    }
    (void)memset_s(rmv_auth_info_request, sizeof(*rmv_auth_info_request), 0, sizeof(*rmv_auth_info_request));
    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Rmv AuthInfo Request parse payload failed");
        goto error;
    }
    /* authData */
    const char *add_return = get_json_string(obj, FIELD_RMV_AUTH_INFO);
    if (add_return == NULL) {
        LOGE("Parse Rmv AuthInfo Request failed, field is null in rmvAuthInfo");
        goto error;
    }
    int32_t len_rmv_return = strlen(add_return);
    if ((len_rmv_return / BYTE_TO_HEX_OPER_LENGTH) > HC_AUTH_DATA_BUFF_LEN) {
        LOGE("Parse Rmv AuthInfo Request failed, field length is not match in rmvAuthInfo");
        goto error;
    }
    rmv_auth_info_request->cipher.length = len_rmv_return / BYTE_TO_HEX_OPER_LENGTH;
    rmv_auth_info_request->cipher.size = rmv_auth_info_request->cipher.length;
    rmv_auth_info_request->cipher.val = (uint8_t *)MALLOC(rmv_auth_info_request->cipher.size);
    if (rmv_auth_info_request->cipher.val == NULL) {
        LOGE("Malloc Rmv AuthInfo Request Cipher failed");
        goto error;
    }
    (void)memset_s(rmv_auth_info_request->cipher.val, rmv_auth_info_request->cipher.size,
                   0, rmv_auth_info_request->cipher.size);
    if (hex_string_to_byte(add_return, len_rmv_return, rmv_auth_info_request->cipher.val) != HC_OK)
        goto error;
    free_payload(obj, data_type);
    return (void *)rmv_auth_info_request;
error:
    free_payload(obj, data_type);
    free_rmv_auth_info_request(rmv_auth_info_request);
    return NULL;
}

void free_rmv_auth_info_request(void *obj)
{
    if (obj != NULL) {
        remove_request_data *data = (remove_request_data *)obj;
        if (data->cipher.val != NULL) {
            FREE(data->cipher.val);
        }
        FREE(data);
    }
}

char *make_rmv_auth_info_request(void *data)
{
    remove_request_data *rmv_auth_info_request = data;
    /* authinfo */
    uint8_t *tmp_data_hex = raw_byte_to_hex_string(rmv_auth_info_request->cipher.val,
                                                   rmv_auth_info_request->cipher.length);
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
        REMOVE_AUTHINFO_REQUEST, FIELD_PAYLOAD, FIELD_RMV_AUTH_INFO, tmp_data_hex) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    FREE(tmp_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(rmv_auth_info_request)

#endif /* _CUT_XXX_ */
