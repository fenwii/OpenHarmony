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

#include "jsonutil.h"
#include "mem_stat.h"
#include "cJSON.h"

json_handle parse_json(const char *data)
{
    cJSON *root = NULL;

    if (data != NULL) {
        root = cJSON_Parse(data);
    }
    return (void *)root;
}

void free_json(json_handle hanlde)
{
    if (hanlde != NULL) {
        cJSON_Delete((cJSON *)hanlde);
    }
}

json_pobject get_json_obj(json_pobject parent, const char *field)
{
    return cJSON_GetObjectItem((cJSON *)parent, field);
}

int32_t get_json_int(json_pobject obj, const char *field)
{
    int32_t ret = -1;

    if (obj == NULL) {
        return ret;
    }
    if (field == NULL) {
        return ((cJSON *)obj)->valueint;
    }

    cJSON *obj_value = NULL;

    do {
        obj_value = (cJSON *)get_json_obj(obj, field);
        if (obj_value == NULL) {
            break;
        }
        if (!cJSON_IsNumber(obj_value)) {
            break;
        }
        ret = obj_value->valueint;
    } while (0);

    return ret;
}

const char *get_json_string(json_pobject obj, const char *field)
{
    if (obj == NULL) {
        return NULL;
    }
    if (field == NULL) {
        return ((cJSON *)obj)->valuestring;
    }
    cJSON *obj_value = NULL;
    const char *payload = NULL;

    do {
        obj_value = (cJSON *)get_json_obj(obj, field);
        if (obj_value == NULL) {
            break;
        }
        payload = cJSON_GetStringValue(obj_value);
        if (payload == NULL) {
            break;
        }
    } while (0);
    return payload;
}

int32_t get_json_bool(json_pobject obj, const char *field)
{
    int32_t ret = -1;

    if (obj == NULL) {
        return ret;
    }
    if (field == NULL) {
        return ((cJSON *)obj)->valueint;
    }

    cJSON *obj_value = NULL;

    do {
        obj_value = (cJSON *)get_json_obj(obj, field);
        if (obj_value == NULL) {
            break;
        }
        if (!cJSON_IsBool(obj_value)) {
            break;
        }
        if (cJSON_IsFalse(obj_value)) {
            ret = 0;
        }
        if (cJSON_IsTrue(obj_value)) {
            ret = 1;
        }
    } while (0);
    return ret;
}

int32_t get_array_size(json_pobject obj)
{
    if (cJSON_IsArray(obj)) {
        return cJSON_GetArraySize(obj);
    }
    return -1;
}

json_pobject get_array_idx(json_pobject obj, int32_t idx)
{
    if (cJSON_IsArray(obj)) {
        return cJSON_GetArrayItem(obj, idx);
    }
    return NULL;
}

json_pobject create_json_object(void)
{
    return cJSON_CreateObject();
}

void delete_json_object(json_pobject obj)
{
    if (obj != NULL) {
        cJSON_Delete((cJSON *)obj);
    }
}

void add_item_to_object(json_pobject parent, const char *field, json_pobject obj)
{
    cJSON_AddItemToObject((cJSON *)parent, field, (cJSON *)obj);
}

json_pobject add_string_to_object(json_pobject parent, const char *field, const char *value)
{
    return cJSON_AddStringToObject((cJSON *)parent, field, value);
}

json_pobject add_number_to_object(json_pobject parent, const char *field, int32_t value)
{
    return cJSON_AddNumberToObject((cJSON *)parent, field, value);
}

json_pobject add_bool_to_object(json_pobject parent, const char *field, int32_t value)
{
    if (value == 0) {
        return cJSON_AddFalseToObject((cJSON *)parent, field);
    } else {
        return cJSON_AddTrueToObject((cJSON *)parent, field);
    }
}

json_pobject add_object_to_object(json_pobject parent, const char *field)
{
    return cJSON_AddObjectToObject(parent, field);
}

char *json_to_string(json_pobject obj)
{
    if (obj != NULL) {
        char *ret = cJSON_PrintUnformatted(obj);
        return ret;
    }
    return NULL;
}

void free_json_string(char *json_str)
{
    FREE(json_str);
}

json_pobject add_array_to_object(json_pobject parent, const char *field)
{
    return cJSON_AddArrayToObject(parent, field);
}

void add_string_to_array(json_pobject objArr, const char *value)
{
    cJSON_AddItemToArray(objArr, cJSON_CreateString(value));
}

void add_number_to_array(json_pobject objArr, int32_t value)
{
    cJSON_AddItemToArray(objArr, cJSON_CreateNumber(value));
}

void add_bool_to_array(json_pobject objArr, int32_t value)
{
    cJSON_AddItemToArray(objArr, cJSON_CreateBool(value));
}

void add_obj_to_array(json_pobject objArr, json_pobject obj)
{
    cJSON_AddItemToArray(objArr, obj);
}
