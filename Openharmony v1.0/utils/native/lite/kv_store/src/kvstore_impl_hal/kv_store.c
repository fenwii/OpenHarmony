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

#include "kv_store.h"
#include <ctype.h>
#include <securec.h>
#include <stdlib.h>
#include "kvstore_common.h"
#include "ohos_errno.h"
#include "ohos_types.h"
#include "utils_config.h"
#include "utils_file.h"

#define MAX_GET_VALUE_LEN  0x7FFFFFFF
#define KV_SUM_FILE        "KV_FILE_SUM"
#define KV_SUM_INDEX       4

static int GetValueByFile(const char* key, char* value, unsigned int len)
{
    unsigned int valueLen = 0;
    if (UtilsFileStat(key, &valueLen) != EC_SUCCESS) {
        return EC_FAILURE;
    }
    if (valueLen >= len) {
        return EC_FAILURE;
    }
    int fd = UtilsFileOpen(key, O_RDONLY_FS, 0);
    if (fd < 0) {
        return EC_FAILURE;
    }
    if (UtilsFileRead(fd, value, valueLen) < 0) {
        UtilsFileClose(fd);
        return EC_FAILURE;
    }
    UtilsFileClose(fd);
    value[valueLen] = '\0';
    return valueLen;
}

static int SetValueToFile(const char* key, const char* value)
{
    int fd = UtilsFileOpen(key, O_RDWR_FS | O_CREAT_FS | O_TRUNC_FS, 0);
    if (fd < 0) {
        return EC_FAILURE;
    }
    if (UtilsFileWrite(fd, value, strlen(value)) < 0) {
        UtilsFileClose(fd);
        return EC_FAILURE;
    }
    UtilsFileClose(fd);
    return EC_SUCCESS;
}

static int GetCurrentItem(void)
{
    int fd = UtilsFileOpen(KV_SUM_FILE, O_RDWR_FS, 0);
    if (fd < 0) {
        return 0;
    }
    char value[KV_SUM_INDEX] = {0};
    if (UtilsFileRead(fd, value, KV_SUM_INDEX) < 0) {
        UtilsFileClose(fd);
        return 0;
    }
    UtilsFileClose(fd);
    int sum = atoi(value);
    return sum;
}

static int SetCurrentItem(const int num)
{
    char value[KV_SUM_INDEX] = {0};
    if (sprintf_s(value, KV_SUM_INDEX, "%d", num) < 0) {
        return EC_FAILURE;
    }
    int fd = UtilsFileOpen(KV_SUM_FILE, O_RDWR_FS | O_CREAT_FS, 0);
    if (fd < 0) {
        return EC_FAILURE;
    }
    if (UtilsFileWrite(fd, value, KV_SUM_INDEX) < 0) {
        UtilsFileClose(fd);
        return EC_FAILURE;
    }
    UtilsFileClose(fd);
    return EC_SUCCESS;
}

static boolean NewItem(const char* key)
{
    int fd = UtilsFileOpen(key, O_RDONLY_FS, 0);
    if (fd < 0) {
        return TRUE;
    }
    UtilsFileClose(fd);
    return FALSE;
}

int UtilsGetValue(const char* key, char* value, unsigned int len)
{
    if (!IsValidKey(key) || (value == NULL) || (len > MAX_GET_VALUE_LEN)) {
        return EC_INVALID;
    }
#ifdef FEATURE_KV_CACHE
    if (GetValueByCache(key, value, len) == EC_SUCCESS) {
        return EC_SUCCESS;
    }
#endif
    int ret = GetValueByFile(key, value, len);
    if (ret < 0) {
        return EC_FAILURE;
    }
#ifdef FEATURE_KV_CACHE
    AddKVCache(key, value, FALSE);
#endif
    return ret;
}

int UtilsSetValue(const char* key, const char* value)
{
    if (!IsValidKey(key) || !IsValidValue(value, MAX_VALUE_LEN)) {
        return EC_INVALID;
    }
    int currentNum = GetCurrentItem();
    boolean newItem = NewItem(key);
    if ((currentNum >= MAX_KV_SUM) && newItem) {
        return EC_FAILURE;
    }
    int ret = SetValueToFile(key, value);
    if (ret == EC_SUCCESS) {
#ifdef FEATURE_KV_CACHE
        AddKVCache(key, value, TRUE);
#endif
        if (newItem) {
            currentNum++;
        }
    }
    ret = SetCurrentItem(currentNum);
    return ret;
}

int UtilsDeleteValue(const char* key)
{
    if (!IsValidKey(key)) {
        return EC_INVALID;
    }
#ifdef FEATURE_KV_CACHE
    DeleteKVCache(key);
#endif
    int ret = UtilsFileDelete(key);
    int currentNum = GetCurrentItem();
    if (ret == EC_SUCCESS) {
        currentNum--;
        ret = SetCurrentItem(currentNum);
    }
    return ret;
}

#ifdef FEATURE_KV_CACHE
int ClearKVCache(void)
{
    return ClearKVCacheInner();
}
#endif