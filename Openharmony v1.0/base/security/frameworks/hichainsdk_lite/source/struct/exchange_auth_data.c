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
#include "parsedata.h"
#include "exchange_auth_info.h"
#include "key_agreement_version.h"

void *parse_exchange_data(const char *payload, enum json_object_data_type data_type)
{
    struct exchange_auth_data *exchange_auth_data =
        (struct exchange_auth_data *)MALLOC(sizeof(struct exchange_auth_data));
    if (exchange_auth_data == NULL) {
        return NULL;
    }
    (void)memset_s(exchange_auth_data, sizeof(*exchange_auth_data), 0, sizeof(*exchange_auth_data));
    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Exchange Data parse payload failed");
        goto error;
    }
    /* authId */
    int32_t result = byte_convert(obj, FIELD_AUTH_ID, exchange_auth_data->auth_id.auth_id,
                                  (uint32_t *)&exchange_auth_data->auth_id.length, HC_AUTH_ID_BUFF_LEN);
    if (result != HC_OK) {
        LOGE("Parse Exchange Data failed, field is null in authId");
        goto error;
    }
    /* authPk */
    result = byte_convert(obj, FIELD_AUTH_PK, exchange_auth_data->ltpk.ltpk,
                          (uint32_t *)&exchange_auth_data->ltpk.length, HC_LT_PRIVATE_KEY_LEN);
    if (result != HC_OK) {
        LOGE("Parse Exchange Data failed, field is null in authPk");
        goto error;
    }
    free_payload(obj, data_type);
    return (void *)exchange_auth_data;
error:
    free_payload(obj, data_type);
    FREE(exchange_auth_data);
    return NULL;
}

void free_exchange_data(void *obj)
{
    if (obj != NULL) {
        FREE(obj);
    }
}

char *make_exchange_data(void *data)
{
    struct exchange_auth_data *exchange_auth_data = data;
    /* authId */
    uint8_t  *tmp_auth_id_data_hex = raw_byte_to_hex_string(exchange_auth_data->auth_id.auth_id,
                                                            exchange_auth_data->auth_id.length);
    if (tmp_auth_id_data_hex == NULL) {
        return NULL;
    }
    /* authPk */
    uint8_t  *tmp_auth_pk_data_hex = raw_byte_to_hex_string(exchange_auth_data->ltpk.ltpk,
                                                            exchange_auth_data->ltpk.length);
    if (tmp_auth_pk_data_hex == NULL) {
        FREE(tmp_auth_id_data_hex);
        return NULL;
    }
    char *ret_str = (char *)MALLOC(RET_STR_LENGTH);
    if (ret_str == NULL) {
        FREE(tmp_auth_id_data_hex);
        FREE(tmp_auth_pk_data_hex);
        return NULL;
    }
    (void)memset_s(ret_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(ret_str, RET_STR_LENGTH, RET_STR_LENGTH - 1, "{\"%s\":\"%s\", \"%s\":\"%s\"}", FIELD_AUTH_ID,
        tmp_auth_id_data_hex, FIELD_AUTH_PK, tmp_auth_pk_data_hex) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    FREE(tmp_auth_id_data_hex);
    FREE(tmp_auth_pk_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(exchange_data)

#endif /* _CUT_XXX_ */
