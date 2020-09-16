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

#include "parsedata.h"
#include <securec.h>
#include "mem_stat.h"
#include "jsonutil.h"
#include "log.h"

uint32_t parse_header(const char *data)
{
    int32_t ret = 0;
    json_handle obj = NULL;
    obj = parse_json(data);
    if (obj == NULL) {
        return -1;
    }
    ret = get_json_int(obj, FIELD_MESSAGE);
    free_json(obj);
    return ret;
}

struct pass_through_data *parse_data(const char *data)
{
    const char *payload = NULL;
    struct pass_through_data *msg_data = (struct pass_through_data *)MALLOC(sizeof(struct pass_through_data));
    if (msg_data == NULL) {
        return NULL;
    }
    json_handle obj = parse_json(data);
    if (obj == NULL) {
        LOGE("Passthrough Data parse_json failed");
        goto error;
    }
    int32_t message_code = get_json_int(obj, FIELD_MESSAGE);
    if (message_code == -1) {
        LOGE("Passthrough Data failed, field is null in message");
        goto error;
    }
    json_pobject obj_value = get_json_obj(obj, FIELD_PAYLOAD);
    payload = json_to_string(obj_value);
    if (payload == NULL) {
        LOGE("Passthrough Data failed, field is null in payload");
        goto error;
    }
    (void)memset_s(msg_data, sizeof(*msg_data), 0, sizeof(*msg_data));
    msg_data->message_code = message_code;
    int32_t len = strlen(payload);
    if (len > 0) {
        ++len; /* add terminator */
        char *tmp_data = (char *)MALLOC(len);
        if (tmp_data == NULL) {
            goto error;
        }
        (void)memset_s(tmp_data, len, 0, len);
        (void)memcpy_s(tmp_data, len, payload, len);
        msg_data->payload_data = tmp_data;
    }
    FREE((char *)payload);
    free_json(obj);
    return msg_data;
error:
    if (payload != NULL) {
        FREE((char *)payload);
    }
    free_json(obj);
    FREE(msg_data);
    return NULL;
}

void free_data(struct pass_through_data *data)
{
    if (data != NULL) {
        if (data->payload_data != NULL) {
            FREE(data->payload_data);
        }
        FREE(data);
    }
}

void *parse_payload(const char *payload, enum json_object_data_type data_type)
{
    if (data_type == JSON_STRING_DATA) {
        return parse_json(payload);
    } else if (data_type == JSON_OBJECT_DATA) {
        return (void *)payload;
    } else {
        return NULL;
    }
}

void free_payload(char *data, enum json_object_data_type data_type)
{
    if (data_type == JSON_STRING_DATA) {
        free_json(data);
    } else {
        return;
    }
}
