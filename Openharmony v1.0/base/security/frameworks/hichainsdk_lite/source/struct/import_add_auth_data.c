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

#include <securec.h>
#include "log.h"
#include "mem_stat.h"
#include "jsonutil.h"
#include "commonutil.h"
#include "parsedata.h"
#include "add_auth_info.h"

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
static const int32_t g_key_type_position = 1;
#endif

void *parse_import_add_auth_data(const char *payload, enum json_object_data_type data_type)
{
    struct import_auth_data *signed_auth_data =
        (struct import_auth_data *)MALLOC(sizeof(struct import_auth_data));
    if (signed_auth_data == NULL) {
        return NULL;
    }
    (void)memset_s(signed_auth_data, sizeof(*signed_auth_data), 0, sizeof(*signed_auth_data));
    json_pobject obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Import Add Auth Info Data failed");
        goto error;
    }

    /* publicKey */
    int32_t result = byte_convert(obj, FIELD_PUBLIC_KEY, signed_auth_data->ltpk.ltpk,
                                  &signed_auth_data->ltpk.length, HC_LT_PUBLIC_KEY_LEN);
    if (result != HC_OK) {
        LOGE("Parse Import Add Auth Info Data failed, field is wrong in publicKey");
        goto error;
    }

    /* ownerId */
    result = byte_convert(obj, FIELD_OWNER_ID, signed_auth_data->owner_id.auth_id,
                          &signed_auth_data->owner_id.length, HC_AUTH_ID_BUFF_LEN);
    if (result != HC_OK) {
        LOGE("Parse Import Add Auth Info Data failed, field is wrong in ownerId");
        goto error;
    }

    /* authId */
    result = byte_convert(obj, FIELD_AUTH_ID, signed_auth_data->auth_id.auth_id,
                          &signed_auth_data->auth_id.length, HC_AUTH_ID_BUFF_LEN);
    if (result != HC_OK) {
        LOGE("Parse Import Add Auth Info Data failed, field is wrong in authId");
        goto error;
    }

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    /* keyType */
    uint8_t key_type[HC_KEY_TYPE_LEN] = {0};
    uint32_t key_length;
    result = byte_convert(obj, FIELD_KEY_TYPE, key_type, &key_length, HC_KEY_TYPE_LEN);
    if (result != HC_OK) {
        LOGE("Parse Import Add Auth Info Data failed, field is wrong in keyType");
        goto error;
    }

    signed_auth_data->user_type = key_type[g_key_type_position];
#endif

    free_payload(obj, data_type);
    return (void *)signed_auth_data;
error:
    free_payload(obj, data_type);
    FREE(signed_auth_data);
    return NULL;
}

void free_import_add_auth_data(void *obj)
{
    if (obj != NULL) {
        FREE(obj);
    }
}

