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
#include "pake_server.h"
#include "key_agreement_version.h"
#include "parsedata.h"

void *parse_pake_request(const char *payload, enum json_object_data_type data_type)
{
    struct pake_start_request_data *pake_request =
        (struct pake_start_request_data *)MALLOC(sizeof(struct pake_start_request_data));
    if (pake_request == NULL) {
        return NULL;
    }
    (void)memset_s(pake_request, sizeof(*pake_request), 0, sizeof(*pake_request));
    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Pake Request parse payload failed");
        goto error;
    }
    /* op */
    int32_t op = get_json_int(obj, FIELD_OPERATION_CODE);
    if (op == -1) {
        LOGE("Parse Pake Request failed, field is null in operationCode");
        goto error;
    }
    pake_request->operation_code = op;
    /* version */
    json_pobject obj_ver = get_json_obj(obj, FIELD_VERSION);
    bool ret = parse_version(obj_ver, &pake_request->peer_version, &pake_request->peer_support_version);
    if (!ret) {
        LOGE("Parse Pake Request failed, field is null in version");
        goto error;
    }

    /* support 256 mod */
    int32_t support_256_mod = get_json_bool(obj, FIELD_SUPPORT_256_MOD);
    if (support_256_mod == 1) {
        pake_request->epk_len = HC_BIG_PRIME_MAX_LEN;
    } else {
        pake_request->epk_len = HC_BIG_PRIME_MAX_LEN_384;
    }

    free_payload(obj, data_type);
    return (void *)pake_request;
error:
    free_payload(obj, data_type);
    FREE(pake_request);
    return NULL;
}

void free_pake_request(void *obj)
{
    if (obj != NULL) {
        FREE(obj);
    }
}

char *make_pake_request(void *data)
{
    struct pake_start_request_data *pake_request = data;
    char *ret_str = (char *)MALLOC(RET_STR_LENGTH);
    if (ret_str == NULL) {
        return NULL;
    }
    (void)memset_s(ret_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(ret_str, RET_STR_LENGTH, RET_STR_LENGTH - 1,
        "{\"%s\":%d,\"%s\":{\"%s\":{\"%s\":\"%u.%u.%u\",\"%s\":\"%u.%u.%u\"},\"%s\":true,\"%s\":%d}}",
        FIELD_MESSAGE, PAKE_REQUEST, FIELD_PAYLOAD, FIELD_VERSION, FIELD_CURRENT_VERSION,
        pake_request->peer_version.first, pake_request->peer_version.second,
        pake_request->peer_version.third, FIELD_MIN_VERSION,
        pake_request->peer_support_version.first, pake_request->peer_support_version.second,
        pake_request->peer_support_version.third, FIELD_SUPPORT_256_MOD,
        FIELD_OPERATION_CODE, pake_request->operation_code) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    return ret_str;
}

#else /* _CUT_XXX_ */

#include "parsedata.h"
DEFINE_EMPTY_STRUCT_FUNC(pake_request)

#endif /* _CUT_XXX_ */
