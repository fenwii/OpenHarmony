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
#include <securec.h>
#include "ohos_errno.h"
#include "utils_file.h"

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
    unsigned int valueLen = 0;
    if (UtilsFileStat(key, &valueLen) != EC_SUCCESS) {
        return EC_FAILURE;
    }
    if (valueLen >= len) {
        return EC_INVALID;
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
    fd = -1;
    value[valueLen] = '\0';
    return valueLen;
}

int SetSysParam(const char* key, const char* value)
{
    if (!IsValidKey(key) || !IsValidValue(value, MAX_VALUE_LEN)) {
        return EC_INVALID;
    }
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

boolean CheckPermission(void)
{
    return TRUE;
}
