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

#include "kvstore_common.h"
#include <ctype.h>
#include <securec.h>
#include <stdlib.h>
#include "ohos_errno.h"

#ifdef FEATURE_KV_CACHE
static KvItem* g_itemHeader = NULL;
static KvItem* g_itemTail = NULL;
static int g_sum = 0;
#endif

boolean IsValidChar(const char ch)
{
    if (islower(ch) || isdigit(ch) || (ch == '_') || (ch == '.')) {
        return TRUE;
    }
    return FALSE;
}

boolean IsValidValue(const char* value, unsigned int len)
{
    if ((value == NULL) || !strlen(value) || (strlen(value) >= len)) {
        return FALSE;
    }
    return TRUE;
}

boolean IsValidKey(const char* key)
{
    if (!IsValidValue(key, MAX_KEY_LEN)) {
        return FALSE;
    }
    int keyLen = strlen(key);
    for (int i = 0; i < keyLen; i++) {
        if (!IsValidChar(key[i])) {
            return FALSE;
        }
    }
    return TRUE;
}

#ifdef FEATURE_KV_CACHE
static void FreeItem(KvItem* item)
{
    if (item == NULL) {
        return;
    }
    if (item->key != NULL) {
        free(item->key);
        item->key = NULL;
    }
    if (item->value != NULL) {
        free(item->value);
        item->value = NULL;
    }
    free(item);
    item = NULL;
}

void DeleteKVCache(const char* key)
{
    if (g_itemHeader == NULL) {
        return;
    }
    KvItem* item = g_itemHeader;
    while (strcmp(key, item->key) != 0) {
        item = item->next;
        if (item == NULL) {
            return;
        }
    }
    g_sum--;
    if (g_sum == 0) {
        g_itemHeader = NULL;
        g_itemTail = NULL;
    } else if (item == g_itemHeader) {
        g_itemHeader = item->next;
        g_itemHeader->prev = NULL;
    } else if (item == g_itemTail) {
        g_itemTail = item->prev;
        g_itemTail->next = NULL;
    } else {
        item->prev->next = item->next;
        item->next->prev = item->prev;
    }
    FreeItem(item);
}

void AddKVCache(const char* key, const char* value, boolean isNew)
{
    if (isNew) {
        DeleteKVCache(key);
    }
    KvItem* item = (KvItem *)malloc(sizeof(KvItem));
    if (item == NULL) {
        return;
    }
    item->key = (char *)malloc(strlen(key) + 1);
    item->value = (char *)malloc(strlen(value) + 1);
    if ((item->key == NULL) || (item->value == NULL)) {
        FreeItem(item);
        return;
    }
    if ((strcpy_s(item->key, strlen(key) + 1, key) != EOK) ||
        (strcpy_s(item->value, strlen(value) + 1, value) != EOK)) {
        FreeItem(item);
        return;
    }
    item->prev = NULL;
    item->next = NULL;
    if (g_itemHeader == NULL) {
        g_itemHeader = item;
        g_itemTail = item;
        g_sum++;
        return;
    }
    item->next = g_itemHeader;
    g_itemHeader->prev = item;
    g_itemHeader = item;
    g_sum++;
    while (g_sum > MAX_CACHE_SIZE) {
        KvItem* needDel = g_itemTail;
        g_itemTail = g_itemTail->prev;
        FreeItem(needDel);
        g_itemTail->next = NULL;
        g_sum--;
    }
}

int GetValueByCache(const char* key, char* value, unsigned int maxLen)
{
    if (g_itemHeader == NULL) {
        return EC_FAILURE;
    }
    KvItem* item = g_itemHeader;
    while (strcmp(key, item->key) != 0) {
        item = item->next;
        if (item == NULL) {
            return EC_FAILURE;
        }
    }
    if ((maxLen <= strlen(item->value)) || (strcpy_s(value, maxLen, item->value) != EOK)) {
        return EC_FAILURE;
    }
    return EC_SUCCESS;
}

int ClearKVCacheInner(void)
{
    if (g_itemHeader == NULL) {
        return EC_SUCCESS;
    }
    KvItem* item = g_itemHeader;
    while (item != NULL) {
        KvItem* temp = item;
        item = item->next;
        FreeItem(temp);
        g_sum--;
    }
    g_itemHeader = NULL;
    g_itemTail = NULL;
    if (g_sum != 0) {
        return EC_FAILURE;
    }
    return EC_SUCCESS;
}
#endif