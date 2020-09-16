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

void *parse_auth_start_request(const char *payload, enum json_object_data_type data_type)
{
    struct sts_start_request_data *auth_start_request =
        (struct sts_start_request_data *)MALLOC(sizeof(struct sts_start_request_data));
    if (auth_start_request == NULL) {
        return NULL;
    }
    (void)memset_s(auth_start_request, sizeof(*auth_start_request), 0, sizeof(*auth_start_request));
    json_pobject obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Auth Start Request parse payload failed");
        goto error;
    }
    /* op */
    int32_t op = get_json_int(obj, FIELD_OPERATION_CODE);
    if (op == -1) {
        LOGE("Parse Auth Start Request failed, field is null in operationCode");
        goto error;
    }
    auth_start_request->operation_code = op;
    /* challenge */
    int32_t result = byte_convert(obj, FIELD_CHALLENGE, auth_start_request->challenge.challenge,
                                  &auth_start_request->challenge.length, CHALLENGE_BUFF_LENGTH);
    if (result != HC_OK) {
        LOGE("Parse Add AuthInfo Data failed, field is null in challenge");
        goto error;
    }
    /* epk */
    result = byte_convert(obj, FIELD_EPK, (uint8_t *)auth_start_request->epk.stpk,
                          &auth_start_request->epk.length, HC_ST_PUBLIC_KEY_LEN);
    if (result != HC_OK) {
        LOGE("Parse Add AuthInfo Data failed, field is null in epk");
        goto error;
    }
    /* pkgName */
    (void)string_convert(obj, FIELD_PKG_NAME, (uint8_t *)auth_start_request->package_name.name,
                         &auth_start_request->package_name.length, HC_PACKAGE_NAME_BUFF_LEN);
    /* peerAuthId */
    (void)byte_convert(obj, FIELD_PEER_AUTH_ID, (uint8_t *)auth_start_request->self_auth_id.auth_id,
                       &auth_start_request->self_auth_id.length, HC_AUTH_ID_BUFF_LEN);
    /* peerUserType */
    int peer_user_type = get_json_int(obj, FIELD_PEER_USER_TYPE);

    auth_start_request->peer_user_type = peer_user_type;
    /* version */
    json_pobject obj_ver = get_json_obj(obj, FIELD_VERSION);
    bool ret = parse_version(obj_ver, &auth_start_request->peer_version, &auth_start_request->peer_support_version);
    if (!ret) {
        LOGE("Parse Auth Start Request, field is null in version");
        goto error;
    }
    free_payload(obj, data_type);
    return (void *)auth_start_request;
error:
    free_payload(obj, data_type);
    FREE(auth_start_request);
    return NULL;
}

void free_auth_start_request(void *obj)
{
    if (obj != NULL) {
        FREE(obj);
    }
}

static char *make_requst_json_str(struct sts_start_request_data *auth_start_request,
                                  struct sts_start_request_data_hex tmp_hex)
{
    char *tmp_str = (char *)MALLOC(RET_STR_LENGTH);
    if (tmp_str == NULL) {
        return NULL;
    }
    (void)memset_s(tmp_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(tmp_str, RET_STR_LENGTH, RET_STR_LENGTH - 1,
        "{\"%s\":%d,\"%s\":%d,\"%s\":{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":%d,"
        "\"%s\":{\"%s\":\"%u.%u.%u\",\"%s\":\"%u.%u.%u\"},\"%s\":\"%s\","
        "\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%d\",\"%s\":\"%u\"}}",
        FIELD_AUTH_FORM, AUTH_FORM, FIELD_MESSAGE, AUTH_START_REQUEST, FIELD_PAYLOAD,
        FIELD_CHALLENGE, tmp_hex.tmp_cha_data_hex, FIELD_EPK, tmp_hex.tmp_epk_data_hex,
        FIELD_OPERATION_CODE, auth_start_request->operation_code,
        FIELD_VERSION, FIELD_CURRENT_VERSION, auth_start_request->peer_version.first,
        auth_start_request->peer_version.second,
        auth_start_request->peer_version.third, FIELD_MIN_VERSION,
        auth_start_request->peer_support_version.first,
        auth_start_request->peer_support_version.second,
        auth_start_request->peer_support_version.third,
        FIELD_PKG_NAME, auth_start_request->package_name.name,
        FIELD_SERVICE_TYPE, tmp_hex.tmp_type_data_hex,
        FIELD_PEER_AUTH_ID, tmp_hex.tmp_auth_id_data_hex,
        FIELD_PEER_USER_TYPE, auth_start_request->peer_user_type,
        FIELD_KEY_LENGTH, auth_start_request->key_length) < 0) {
        LOGE("String generate failed");
        FREE(tmp_str);
        tmp_str = NULL;
    }
    return tmp_str;
}

char *make_auth_start_request(void *data)
{
    struct sts_start_request_data *auth_start_request = data;
    struct sts_start_request_data_hex tmp_hex = {0, 0, 0, 0};
    /* challenge */
    tmp_hex.tmp_cha_data_hex = raw_byte_to_hex_string(auth_start_request->challenge.challenge,
                                                      auth_start_request->challenge.length);
    if (tmp_hex.tmp_cha_data_hex == NULL) {
        return NULL;
    }
    /* epk */
    tmp_hex.tmp_epk_data_hex = raw_byte_to_hex_string(auth_start_request->epk.stpk, auth_start_request->epk.length);
    if (tmp_hex.tmp_epk_data_hex == NULL) {
        FREE(tmp_hex.tmp_cha_data_hex);
        return NULL;
    }
    /* service_type */
    tmp_hex.tmp_type_data_hex = raw_byte_to_hex_string(auth_start_request->service_type.type,
                                                       auth_start_request->service_type.length);
    if (tmp_hex.tmp_type_data_hex == NULL) {
        FREE(tmp_hex.tmp_epk_data_hex);
        FREE(tmp_hex.tmp_cha_data_hex);
        return NULL;
    }
    /* peerAuthId */
    tmp_hex.tmp_auth_id_data_hex = raw_byte_to_hex_string(auth_start_request->self_auth_id.auth_id,
                                                          auth_start_request->self_auth_id.length);
    if (tmp_hex.tmp_auth_id_data_hex == NULL) {
        FREE(tmp_hex.tmp_epk_data_hex);
        FREE(tmp_hex.tmp_type_data_hex);
        FREE(tmp_hex.tmp_cha_data_hex);
        return NULL;
    }
    char *ret_str = make_requst_json_str(auth_start_request, tmp_hex);
    FREE(tmp_hex.tmp_epk_data_hex);
    FREE(tmp_hex.tmp_cha_data_hex);
    FREE(tmp_hex.tmp_type_data_hex);
    FREE(tmp_hex.tmp_auth_id_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(auth_start_request)

#endif /* _CUT_XXX_ */

