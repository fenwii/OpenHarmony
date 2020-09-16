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

void *parse_add_auth_info_data(const char *payload, enum json_object_data_type data_type)
{
    struct add_auth_data *add_auth_data = (struct add_auth_data *)MALLOC(sizeof(struct add_auth_data));
    if (add_auth_data == NULL) {
        return NULL;
    }
    (void)memset_s(add_auth_data, sizeof(*add_auth_data), 0, sizeof(*add_auth_data));
    json_pobject obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Add AuthInfo Data parse payload failed");
        goto error;
    }
    /* user_type */
    int32_t type = get_json_int(obj, FIELD_ADD_TYPE);
    if (type == -1) {
        LOGE("Parse Add AuthInfo Data failed, field in addType");
        goto error;
    }
    add_auth_data->user_type = type;
    /* addId */
    int32_t result = byte_convert(obj, FIELD_ADD_ID, add_auth_data->auth_id.auth_id,
                                  (uint32_t *)&add_auth_data->auth_id.length, HC_AUTH_ID_BUFF_LEN);
    if (result != HC_OK) {
        LOGE("Parse Add AuthInfo Data failed, field is wrong in addId");
        goto error;
    }
    /* addKey */
    result = byte_convert(obj, FIELD_ADD_KEY, add_auth_data->ltpk.ltpk,
                          &add_auth_data->ltpk.length, HC_LT_PUBLIC_KEY_LEN);
    if (result != HC_OK) {
        LOGE("Parse Add AuthInfo Data failed, field is wrong in addKey");
        goto error;
    }
    /* Permission */
    int32_t permission = get_json_bool(obj, FIELD_PERMISSION);
    if (permission == -1) {
        LOGE("Parse Add AuthInfo Data failed, field is null in Permission");
        goto error;
    }
    add_auth_data->permission = permission;
    free_payload(obj, data_type);
    return (void *)add_auth_data;
error:
    free_payload(obj, data_type);
    FREE(add_auth_data);
    return NULL;
}

void free_add_auth_info_data(void *obj)
{
    if (obj != NULL) {
        FREE(obj);
    }
}

char *make_add_auth_info_data(void *data)
{
    struct add_auth_data *add_auth_data = data;
    /* addId */
    uint8_t *tmp_add_id_data_hex = raw_byte_to_hex_string(add_auth_data->auth_id.auth_id,
                                                          add_auth_data->auth_id.length);
    if (tmp_add_id_data_hex == NULL) {
        return NULL;
    }
    /* addKey */
    uint8_t *tmp_add_key_data_hex = raw_byte_to_hex_string(add_auth_data->ltpk.ltpk, add_auth_data->ltpk.length);
    if (tmp_add_key_data_hex == NULL) {
        FREE(tmp_add_id_data_hex);
        return NULL;
    }
    char *ret_str = (char *)MALLOC(RET_STR_LENGTH);
    if (ret_str == NULL) {
        FREE(tmp_add_id_data_hex);
        FREE(tmp_add_key_data_hex);
        return NULL;
    }
    (void)memset_s(ret_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(ret_str, RET_STR_LENGTH, RET_STR_LENGTH - 1,
        "{\"%s\":%d,\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":%s}", FIELD_ADD_TYPE, add_auth_data->user_type,
        FIELD_ADD_ID, tmp_add_id_data_hex, FIELD_ADD_KEY, tmp_add_key_data_hex, FIELD_PERMISSION,
        add_auth_data->permission ? "true" : "false") < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    FREE(tmp_add_id_data_hex);
    FREE(tmp_add_key_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(add_auth_info_data)

#endif /* _CUT_XXX_ */
