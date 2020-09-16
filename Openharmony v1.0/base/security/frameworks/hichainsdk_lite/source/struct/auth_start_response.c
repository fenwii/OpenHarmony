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

#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_))

#include <securec.h>
#include "log.h"
#include "mem_stat.h"
#include "jsonutil.h"
#include "commonutil.h"
#include "parsedata.h"
#include "key_agreement_version.h"
#include "add_auth_info.h"

void *parse_auth_start_response(const char *payload, enum json_object_data_type data_type)
{
    struct sts_start_response_data *auth_start_response =
        (struct sts_start_response_data *)MALLOC(sizeof(struct sts_start_response_data));
    if (auth_start_response == NULL) {
        return NULL;
    }
    (void)memset_s(auth_start_response, sizeof(*auth_start_response), 0, sizeof(*auth_start_response));
    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse AuthStart Response parse payload failed");
        goto error;
    }
    /* authData */
    int32_t result = byte_convert(obj, FIELD_AUTH_DATA, auth_start_response->auth_data.auth_data,
                                  &auth_start_response->auth_data.length, HC_AUTH_DATA_BUFF_LEN);
    if (result != HC_OK) {
        LOGE("Parse AuthStart Response failed, field is null in authData");
        goto error;
    }

    /* challenge */
    result = byte_convert(obj, FIELD_CHALLENGE, auth_start_response->challenge.challenge,
                          &auth_start_response->challenge.length, CHALLENGE_BUFF_LENGTH);
    if (result != HC_OK) {
        LOGE("Parse AuthStart Response failed, field is null in challenge");
        goto error;
    }

    /* salt */
    result = byte_convert(obj, FIELD_SALT, auth_start_response->salt.salt,
                          (uint32_t *)&auth_start_response->salt.length, HC_SALT_BUFF_LEN);
    if (result != HC_OK) {
        LOGE("Parse AuthStart Response failed, field is null in salt");
        goto error;
    }

    /* epk */
    result = byte_convert(obj, FIELD_EPK, auth_start_response->epk.stpk,
                          &auth_start_response->epk.length, HC_ST_PUBLIC_KEY_LEN);
    if (result != HC_OK) {
        LOGE("Parse AuthStart Response failed, field is null in epk");
        goto error;
    }
    /* version */
    json_pobject obj_ver = get_json_obj(obj, FIELD_VERSION);
    bool ret = parse_version(obj_ver, &auth_start_response->self_version, &auth_start_response->self_support_version);
    if (!ret) {
        LOGE("Parse AuthStart Response failed, field is null in version");
        goto error;
    }
    free_payload(obj, data_type);
    return (void *)auth_start_response;
error:
    free_payload(obj, data_type);
    FREE(auth_start_response);
    return NULL;
}

void free_auth_start_response(void *obj)
{
    if (obj != NULL) {
        FREE(obj);
    }
}

static char *make_response_json_str(struct sts_start_response_data *as_res,
                                    struct sts_start_response_data_hex tmp_hex)
{
    char *tmp_str = (char *)MALLOC(RET_STR_LENGTH);
    if (tmp_str == NULL) {
        return NULL;
    }

    (void)memset_s(tmp_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(tmp_str, RET_STR_LENGTH, RET_STR_LENGTH - 1,
        "{\"%s\":%d,\"%s\":%d,\"%s\":{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\","
        "\"%s\":{\"%s\":\"%u.%u.%u\",\"%s\":\"%u.%u.%u\"},\"%s\":\"%s\",\"%s\":\"%d\"}}",
        FIELD_AUTH_FORM, AUTH_FORM, FIELD_MESSAGE, AUTH_START_RESPONSE, FIELD_PAYLOAD, FIELD_AUTH_DATA,
        tmp_hex.tmp_auth_data_hex, FIELD_CHALLENGE, tmp_hex.tmp_cha_data_hex, FIELD_EPK,
        tmp_hex.tmp_epk_data_hex, FIELD_SALT, tmp_hex.tmp_salt_data_hex,
        FIELD_VERSION, FIELD_CURRENT_VERSION, as_res->self_version.first,
        as_res->self_version.second, as_res->self_version.third, FIELD_MIN_VERSION,
        as_res->self_support_version.first, as_res->self_support_version.second,
        as_res->self_support_version.third, FIELD_PEER_AUTH_ID, tmp_hex.tmp_auth_id_data_hex,
        FIELD_PEER_USER_TYPE, as_res->peer_user_type) < 0) {
        LOGE("String generate failed");
        FREE(tmp_str);
        tmp_str = NULL;
    }
    return tmp_str;
}

char *make_auth_start_response(void *data)
{
    struct sts_start_response_data *as_res = data;
    struct sts_start_response_data_hex tmp_hex = {0, 0, 0, 0, 0};
    /* authData */
    tmp_hex.tmp_auth_data_hex = raw_byte_to_hex_string(as_res->auth_data.auth_data, as_res->auth_data.length);
    if (tmp_hex.tmp_auth_data_hex == NULL) {
        return NULL;
    }
    /* challenge */
    tmp_hex.tmp_cha_data_hex = raw_byte_to_hex_string(as_res->challenge.challenge, as_res->challenge.length);
    if (tmp_hex.tmp_cha_data_hex == NULL) {
        FREE(tmp_hex.tmp_auth_data_hex);
        return NULL;
    }
    /* salt */
    tmp_hex.tmp_salt_data_hex = raw_byte_to_hex_string(as_res->salt.salt, as_res->salt.length);
    if (tmp_hex.tmp_salt_data_hex == NULL) {
        FREE(tmp_hex.tmp_auth_data_hex);
        FREE(tmp_hex.tmp_cha_data_hex);
        return NULL;
    }
    /* epk */
    tmp_hex.tmp_epk_data_hex = raw_byte_to_hex_string(as_res->epk.stpk, as_res->epk.length);
    if (tmp_hex.tmp_epk_data_hex == NULL) {
        FREE(tmp_hex.tmp_auth_data_hex);
        FREE(tmp_hex.tmp_cha_data_hex);
        FREE(tmp_hex.tmp_salt_data_hex);
        return NULL;
    }
    /* peerAuthId */
    tmp_hex.tmp_auth_id_data_hex = raw_byte_to_hex_string(as_res->self_auth_id.auth_id, as_res->self_auth_id.length);
    if (tmp_hex.tmp_auth_id_data_hex == NULL) {
        FREE(tmp_hex.tmp_epk_data_hex);
        FREE(tmp_hex.tmp_cha_data_hex);
        FREE(tmp_hex.tmp_salt_data_hex);
        FREE(tmp_hex.tmp_auth_data_hex);
        return NULL;
    }
    char *ret_str = make_response_json_str(as_res, tmp_hex);

    FREE(tmp_hex.tmp_auth_data_hex);
    FREE(tmp_hex.tmp_cha_data_hex);
    FREE(tmp_hex.tmp_salt_data_hex);
    FREE(tmp_hex.tmp_epk_data_hex);
    FREE(tmp_hex.tmp_auth_id_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(auth_start_response)

#endif /* _CUT_XXX_ */
