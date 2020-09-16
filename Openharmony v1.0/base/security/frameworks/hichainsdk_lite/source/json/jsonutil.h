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

#ifndef __JSONUTIL_H__
#define __JSONUTIL_H__

#include <stdint.h>

typedef void *json_handle;
typedef void *json_pobject;

json_handle parse_json(const char *data);
void free_json(json_handle hanlde);

json_pobject get_json_obj(json_pobject parent, const char *field);
int32_t get_json_int(json_pobject obj, const char *field);
const char *get_json_string(json_pobject obj, const char *field);
int32_t get_json_bool(json_pobject obj, const char *field);
int32_t get_array_size(json_pobject obj);
json_pobject get_array_idx(json_pobject obj, int32_t idx);

json_pobject create_json_object(void);
void delete_json_object(json_pobject obj);
void add_item_to_object(json_pobject parent, const char *field, json_pobject obj);
json_pobject add_string_to_object(json_pobject parent, const char *field, const char *value);
json_pobject add_number_to_object(json_pobject parent, const char *field, int32_t value);
json_pobject add_bool_to_object(json_pobject parent, const char *field, int32_t value);
json_pobject add_object_to_object(json_pobject parent, const char *field);

char *json_to_string(json_pobject obj);
void free_json_string(char *json_str);

json_pobject add_array_to_object(json_pobject parent, const char *field);
void add_string_to_array(json_pobject objArr, const char *value);
void add_number_to_array(json_pobject objArr, int32_t value);
void add_bool_to_array(json_pobject objArr, int32_t value);
void add_obj_to_array(json_pobject objArr, json_pobject obj);

#endif /* __JSONUTIL_H__ */
