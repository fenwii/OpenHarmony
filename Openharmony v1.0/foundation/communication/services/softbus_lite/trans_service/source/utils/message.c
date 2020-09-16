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
#include "message.h"

#include <stdio.h>

int GetJsonInt(const cJSON *root, const char *name, int *result)
{
    if (root == NULL || name == NULL || result == NULL) {
        return -1;
    }

    cJSON *item = cJSON_GetObjectItem(root, name);
    if ((item == NULL) || (!cJSON_IsNumber(item))) {
        return -1;
    }
    *result = item->valueint;
    return 0;
}

char* GetJsonString(const cJSON *root, const char *name)
{
    if (root == NULL || name == NULL) {
        return NULL;
    }

    cJSON *item = cJSON_GetObjectItem(root, name);
    if ((item == NULL) || (!cJSON_IsString(item))) {
        return NULL;
    }
    return item->valuestring;
}