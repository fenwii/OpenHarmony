/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef KV_STORE_COMMON_H
#define KV_STORE_COMMON_H

#include "ohos_types.h"
#include "utils_config.h"

#define MAX_KEY_LEN 32
#define MAX_VALUE_LEN 128

boolean IsValidChar(const char ch);
boolean IsValidValue(const char* value, unsigned int len);
boolean IsValidKey(const char* key);

#ifdef FEATURE_KV_CACHE
typedef struct KvItem_ {
    char* key;
    char* value;
    struct KvItem_* next;
    struct KvItem_* prev;
} KvItem;

void DeleteKVCache(const char* key);
void AddKVCache(const char* key, const char* value, boolean isNew);
int GetValueByCache(const char* key, char* value, unsigned int maxLen);
int ClearKVCacheInner(void);
#endif

#endif  // KV_STORE_COMMON_H