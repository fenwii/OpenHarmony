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

#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_))

#include <securec.h>
#include "log.h"
#include "mem_stat.h"
#include "jsonutil.h"
#include "commonutil.h"
#include "pake_server.h"
#include "key_agreement_version.h"
#include "parsedata.h"

void *parse_pake_response(const char *payload, enum json_object_data_type data_type)
{
    struct pake_start_response_data *pake_response =
        (struct pake_start_response_data *)MALLOC(sizeof(struct pake_start_response_data));
    if (pake_response == NULL) {
        return NULL;
    }
    (void)memset_s(pake_response, sizeof(*pake_response), 0, sizeof(*pake_response));
    json_pobject obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Pake Response parse payload failed");
        goto error;
    }
    /* challenge */
    int32_t result = byte_convert(obj, FIELD_CHALLENGE, pake_response->challenge.challenge,
                                  &pake_response->challenge.length, CHALLENGE_BUFF_LENGTH);
    if (result != HC_OK) {
        LOGE("Parse Pake Response failed, field is null in challenge");
        goto error;
    }
    /* salt */
    result = byte_convert(obj, FIELD_SALT, pake_response->salt.salt,
                          (uint32_t *)&pake_response->salt.length, HC_SALT_BUFF_LEN);
    if (result != HC_OK) {
        LOGE("Parse Pake Response failed, field is null in salt");
        goto error;
    }
    /* epk */
    result = byte_convert(obj, FIELD_EPK, pake_response->epk.epk,
                          &pake_response->epk.length, PAKE_EPK_LENGTH);
    if (result != HC_OK) {
        LOGE("Parse Pake Response failed, field is null in epk");
        goto error;
    }
    /* version */
    json_pobject obj_ver = get_json_obj(obj, FIELD_VERSION);
    bool ret = parse_version(obj_ver, &pake_response->self_version, &pake_response->self_support_version);
    if (!ret) {
        LOGE("Parse Pake Response failed, field is null in version");
        goto error;
    }
    free_payload(obj, data_type);
    return (void *)pake_response;
error:
    free_payload(obj, data_type);
    FREE(pake_response);
    return NULL;
}

void free_pake_response(void *obj)
{
    if (obj != NULL) {
        FREE(obj);
    }
}

char *make_pake_response(void *data)
{
    struct pake_start_response_data *pake_response = data;
    /* challenge */
    uint8_t *tmp_cha_data_hex = raw_byte_to_hex_string(pake_response->challenge.challenge,
                                                       pake_response->challenge.length);
    if (tmp_cha_data_hex == NULL) {
        return NULL;
    }
    /* salt */
    uint8_t *tmp_salt_data_hex = raw_byte_to_hex_string(pake_response->salt.salt, pake_response->salt.length);
    if (tmp_salt_data_hex == NULL) {
        FREE(tmp_cha_data_hex);
        return NULL;
    }
    /* epk */
    uint8_t *tmp_epk_data_hex = raw_byte_to_hex_string(pake_response->epk.epk, pake_response->epk.length);
    if (tmp_epk_data_hex == NULL) {
        FREE(tmp_cha_data_hex);
        FREE(tmp_salt_data_hex);
        return NULL;
    }
    char *ret_str = (char *)MALLOC(RET_STR_LENGTH);
    if (ret_str == NULL) {
        FREE(tmp_cha_data_hex);
        FREE(tmp_salt_data_hex);
        FREE(tmp_epk_data_hex);
        return NULL;
    }
    (void)memset_s(ret_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(ret_str, RET_STR_LENGTH, RET_STR_LENGTH - 1,
        "{\"%s\":%d,\"%s\":{\"%s\":{\"%s\":\"%u.%u.%u\",\"%s\":\"%u.%u.%u\"},"
        "\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}}",
        FIELD_MESSAGE, PAKE_RESPONSE, FIELD_PAYLOAD, FIELD_VERSION, FIELD_CURRENT_VERSION,
        pake_response->self_version.first, pake_response->self_version.second,
        pake_response->self_version.third, FIELD_MIN_VERSION, pake_response->self_support_version.first,
        pake_response->self_support_version.second, pake_response->self_support_version.third,
        FIELD_CHALLENGE, (char *)tmp_cha_data_hex, FIELD_SALT, (char *)tmp_salt_data_hex, FIELD_EPK,
        (char *)tmp_epk_data_hex) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    FREE(tmp_cha_data_hex);
    FREE(tmp_salt_data_hex);
    FREE(tmp_epk_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(pake_response)

#endif /* _CUT_XXX_ */
