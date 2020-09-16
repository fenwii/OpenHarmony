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

#include "param_adaptor.h"
#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <securec.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ohos_errno.h"

#define DATA_PATH          "/storage/data/system/param/"
#define MAX_KEY_PATH       128
#define SYS_UID_INDEX      1000

static boolean IsValidChar(const char ch)
{
    if (islower(ch) || isdigit(ch) || (ch == '_') || (ch == '.')) {
        return TRUE;
    }
    return FALSE;
}

static boolean IsValidValue(const char* value, unsigned int len)
{
    if ((value == NULL) || !strlen(value) || (strlen(value) >= len)) {
        return FALSE;
    }
    return TRUE;
}

static boolean IsValidKey(const char* key)
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

int GetSysParam(const char* key, char* value, unsigned int len)
{
    if (!IsValidKey(key) || (value == NULL) || (len > MAX_GET_VALUE_LEN)) {
        return EC_INVALID;
    }
    char* keyPath = (char *)malloc(MAX_KEY_PATH + 1);
    if (keyPath == NULL) {
        return EC_FAILURE;
    }
    if (sprintf_s(keyPath, MAX_KEY_PATH + 1, "%s%s", DATA_PATH, key) < 0) {
        free(keyPath);
        return EC_FAILURE;
    }
    struct stat info = {0};
    if (stat(keyPath, &info) != F_OK) {
        free(keyPath);
        return EC_FAILURE;
    }
    if (info.st_size >= len) {
        free(keyPath);
        return EC_INVALID;
    }
    int fd = open(keyPath, O_RDONLY, S_IRUSR);
    free(keyPath);
    keyPath = NULL;
    if (fd < 0) {
        return EC_FAILURE;
    }
    if (read(fd, value, info.st_size) < 0) {
        close(fd);
        return EC_FAILURE;
    }
    close(fd);
    fd = -1;
    value[info.st_size] = '\0';
    return info.st_size;
}

int SetSysParam(const char* key, const char* value)
{
    if (!IsValidKey(key) || !IsValidValue(value, MAX_VALUE_LEN)) {
        return EC_INVALID;
    }
    char* keyPath = (char *)malloc(MAX_KEY_PATH + 1);
    if (keyPath == NULL) {
        return EC_FAILURE;
    }
    if (sprintf_s(keyPath, MAX_KEY_PATH + 1, "%s%s", DATA_PATH, key) < 0) {
        free(keyPath);
        return EC_FAILURE;
    }
    int fd = open(keyPath, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    free(keyPath);
    keyPath = NULL;
    if (fd < 0) {
        return EC_FAILURE;
    }
    if (write(fd, value, strlen(value)) < 0) {
        close(fd);
        return EC_FAILURE;
    }
    close(fd);
    return EC_SUCCESS;
}

boolean CheckPermission(void)
{
    uid_t uid = getuid();
    if (uid <= SYS_UID_INDEX) {
        return TRUE;
    }
    return FALSE;
}
