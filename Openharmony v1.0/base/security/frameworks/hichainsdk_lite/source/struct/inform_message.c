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
#include "base.h"
#include "parsedata.h"
#include "key_agreement_version.h"

void *parse_inform_message(const char *payload, enum json_object_data_type data_type)
{
    struct inform_message_data *inform_msg = (struct inform_message_data *)MALLOC(sizeof(struct inform_message_data));
    if (inform_msg == NULL) {
        return NULL;
    }
    (void)memset_s(inform_msg, sizeof(*inform_msg), 0, sizeof(*inform_msg));
    json_handle obj = parse_payload(payload, data_type);
    if (obj == NULL) {
        LOGE("Parse Inform Message parse payload failed");
        goto error;
    }
    int32_t error_code = get_json_int(obj, FIELD_ERROR_CODE);
    if (error_code == -1) {
        LOGE("Parse Inform Message failed, field is null in errorCode");
        goto error;
    }
    inform_msg->error_code = error_code;
    free_payload(obj, data_type);
    return (void *)inform_msg;
error:
    free_payload(obj, data_type);
    FREE(inform_msg);
    return NULL;
}

void free_inform_message(void *obj)
{
    if (obj != NULL) {
        FREE(obj);
    }
}

char *make_inform_message(void *data)
{
    struct inform_message_data *inform_msg = data;
    char *ret_str = (char *)MALLOC(RET_STR_LENGTH);
    if (ret_str == NULL) {
        return NULL;
    }
    (void)memset_s(ret_str, RET_STR_LENGTH, 0, RET_STR_LENGTH);
    if (snprintf_s(ret_str, RET_STR_LENGTH, RET_STR_LENGTH - 1, "{\"%s\":%d, \"%s\":{\"%s\":%d}}", FIELD_MESSAGE,
        INFORM_MESSAGE, FIELD_PAYLOAD, FIELD_ERROR_CODE, inform_msg->error_code) < 0) {
        LOGE("String generate failed");
        FREE(ret_str);
        ret_str = NULL;
    }
    return ret_str;
}
