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

void *parse_pake_server_confirm(const char *payload, enum json_object_data_type data_type)
{
    struct pake_end_response_data *pake_server_confirm =
        (struct pake_end_response_data *)MALLOC(sizeof(struct pake_end_response_data));
    if (pake_server_confirm == NULL) {
        return NULL;
    }
    (void)memset_s(pake_server_confirm, sizeof(*pake_server_confirm), 0, sizeof(*pake_server_confirm));
    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Pake Server Confirm parse payload failed");
        goto error;
    }
    /* kcfData */
    int32_t result = byte_convert(obj, FIELD_KCF_DATA, pake_server_confirm->kcf_data.hmac,
                                  (uint32_t *)&pake_server_confirm->kcf_data.length, HC_HMAC_LEN);
    if (result != HC_OK) {
        LOGE("Parse Auth ACK Request Data failed, field is null in addId");
        goto error;
    }
    free_payload(obj, data_type);
    return (void *)pake_server_confirm;
error:
    free_payload(obj, data_type);
    FREE(pake_server_confirm);
    return NULL;
}

void free_pake_server_confirm(void *obj)
{
    if (obj != NULL) {
        FREE(obj);
    }
}

char *make_pake_server_confirm(void *data)
{
    struct pake_end_response_data *pake_server_confirm = data;
    /* kcfData */
    uint8_t *tmp_kcf_data_hex = raw_byte_to_hex_string(pake_server_confirm->kcf_data.hmac,
                                                       pake_server_confirm->kcf_data.length);
    if (tmp_kcf_data_hex == NULL) {
        return NULL;
    }
    char *ret_str = (char *)MALLOC(RET_STR_LENGTH);
    if (ret_str == NULL) {
        FREE(tmp_kcf_data_hex);
        return NULL;
    }
    (void)memset_s(ret_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(ret_str, RET_STR_LENGTH, RET_STR_LENGTH - 1, "{\"%s\":%d,\"%s\":{\"%s\":\"%s\"}}", FIELD_MESSAGE,
        PAKE_SERVER_CONFIRM_RESPONSE, FIELD_PAYLOAD, FIELD_KCF_DATA, tmp_kcf_data_hex) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    FREE(tmp_kcf_data_hex);
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(pake_server_confirm)

#endif /* _CUT_XXX_ */
