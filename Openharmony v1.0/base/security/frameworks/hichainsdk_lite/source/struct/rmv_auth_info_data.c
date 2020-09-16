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

void *parse_rmv_auth_info_data(const char *payload, enum json_object_data_type data_type)
{
    struct remove_auth_data *rmv_auth_data = (struct remove_auth_data *)MALLOC(sizeof(struct remove_auth_data));
    if (rmv_auth_data == NULL) {
        return NULL;
    }
    (void)memset_s(rmv_auth_data, sizeof(*rmv_auth_data), 0, sizeof(*rmv_auth_data));
    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Rmv AuthInfo Data parse payload failed");
        goto error;
    }
    /* user_type */
    int32_t type = get_json_int(obj, FIELD_RMV_TYPE);
    if (type == -1) {
        LOGE("Parse Rmv AuthInfo Data failed, field is null in rmvType");
        goto error;
    }
    rmv_auth_data->user_type = type;
    /* rmvId */
    int32_t result = byte_convert(obj, FIELD_RMV_ID, rmv_auth_data->auth_id.auth_id,
                                  (uint32_t *)&rmv_auth_data->auth_id.length, HC_AUTH_ID_BUFF_LEN);
    if (result != HC_OK) {
        LOGE("Parse Rmv AuthInfo Data failed, field is null in rmvId");
        goto error;
    }
    free_payload(obj, data_type);
    return (void *)rmv_auth_data;
error:
    free_payload(obj, data_type);
    FREE(rmv_auth_data);
    return NULL;
}

void free_rmv_auth_info_data(void *obj)
{
    if (obj != NULL) {
        FREE(obj);
    }
}

char *make_rmv_auth_info_data(void *data)
{
    struct remove_auth_data *rmv_auth_data = data;
    /* rmvId */
    uint8_t *tmp_rmv_id_data_hex = raw_byte_to_hex_string(rmv_auth_data->auth_id.auth_id,
                                                          rmv_auth_data->auth_id.length);
    if (tmp_rmv_id_data_hex == NULL) {
        return NULL;
    }
    char *ret_str = (char *)MALLOC(RET_STR_LENGTH);
    if (ret_str == NULL) {
        FREE(tmp_rmv_id_data_hex);
        return NULL;
    }
    (void)memset_s(ret_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(ret_str, RET_STR_LENGTH, RET_STR_LENGTH - 1, "{\"%s\":%d,\"%s\":\"%s\"}", FIELD_RMV_TYPE,
        rmv_auth_data->user_type, FIELD_RMV_ID, tmp_rmv_id_data_hex) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    FREE(tmp_rmv_id_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(rmv_auth_info_data)

#endif /* _CUT_XXX_ */
