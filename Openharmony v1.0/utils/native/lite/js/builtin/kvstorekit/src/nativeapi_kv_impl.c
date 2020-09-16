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

#include "nativeapi_kv_impl.h"
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <securec.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "nativeapi_config.h"

static char g_kvFolder[FILE_NAME_MAX_LEN + 1] = {0};

static bool IsValidValue(const char *value)
{
    if ((value == NULL) || !strlen(value) || (strlen(value) > VALUE_MAX_LEN)) {
        return false;
    }
    return true;
}

static int GetKvFolder(const char* dataPath)
{
    if (dataPath == NULL) {
        return ERROR_CODE_PARAM;
    }
    if (memset_s(g_kvFolder, sizeof(g_kvFolder), 0x0, sizeof(g_kvFolder)) != EOK) {
        return ERROR_CODE_GENERAL;
    }
    if (sprintf_s(g_kvFolder, sizeof(g_kvFolder), "%s/%s", dataPath, DEFAULT_FOLDER_PATH) < 0) {
        return ERROR_CODE_GENERAL;
    }
    return NATIVE_SUCCESS;
}

static int GetRealPath(const char* originPath, char* trustPath, size_t tPathLen)
{
    if (realpath(originPath, trustPath) != NULL) {
        return NATIVE_SUCCESS;
    }
    if (errno == ENOENT) {
        if (strncpy_s(trustPath, tPathLen, originPath, strlen(originPath)) == EOK) {
            return NATIVE_SUCCESS;
        }
    }
    return ERROR_CODE_GENERAL;
}

int InitKv(const char* dataPath)
{
    int ret = GetKvFolder(dataPath);
    if (ret != NATIVE_SUCCESS) {
        return ret;
    }
    if (access(g_kvFolder, F_OK) == F_OK) {
        return NATIVE_SUCCESS;
    }
    if (mkdir(g_kvFolder, S_IRUSR | S_IWUSR | S_IXUSR) != 0) {
        return ERROR_CODE_GENERAL;
    }
    return NATIVE_SUCCESS;
}

int GetValue(const char* key, char* value)
{
    if ((key == NULL) || (value == NULL)) {
        return ERROR_CODE_PARAM;
    }
    char* resolvePath = (char *)malloc(PATH_MAX);
    if (resolvePath == NULL) {
        return ERROR_CODE_GENERAL;
    }
    if (GetRealPath(key, resolvePath, PATH_MAX) != NATIVE_SUCCESS) {
        free(resolvePath);
        return ERROR_CODE_GENERAL;
    }
    int fileHandle = open(resolvePath, O_RDONLY, S_IRUSR);
    free(resolvePath);
    resolvePath = NULL;
    if (fileHandle < 0) {
        return (-errno);
    }
    int readLen = read(fileHandle, value, VALUE_MAX_LEN);
    close(fileHandle);
    fileHandle = -1;
    if (readLen < 0) {
        return ERROR_CODE_IO;
    }
    value[readLen] = '\0';
    return NATIVE_SUCCESS;
}

int SetValue(const char* key, const char* value)
{
    if ((key == NULL) || (!IsValidValue(value))) {
        return ERROR_CODE_PARAM;
    }
    char* resolvePath = (char *)malloc(PATH_MAX);
    if (resolvePath == NULL) {
        return ERROR_CODE_GENERAL;
    }
    if (GetRealPath(key, resolvePath, PATH_MAX) != NATIVE_SUCCESS) {
        free(resolvePath);
        return ERROR_CODE_GENERAL;
    }
    int fd = open(resolvePath, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    free(resolvePath);
    resolvePath = NULL;
    if (fd < 0) {
        return (-errno);
    }
    if (write(fd, value, strlen(value)) < 0) {
        close(fd);
        return ERROR_CODE_IO;
    }
    close(fd);
    return NATIVE_SUCCESS;
}

int DeleteValue(const char* key)
{
    if (key == NULL) {
        return ERROR_CODE_PARAM;
    }
    int ret = unlink(key);
    if (ret != NATIVE_SUCCESS) {
        return (-errno);
    }
    return NATIVE_SUCCESS;
}

int ClearKVStore(const char* dataPath)
{
    int ret = GetKvFolder(dataPath);
    if (ret != NATIVE_SUCCESS) {
        return ret;
    }
    ret = ERROR_CODE_GENERAL;
    DIR *fileDir = opendir(g_kvFolder);
    if (fileDir == NULL) {
        return ret;
    }
    struct dirent *dir = readdir(fileDir);
    char* fullPath = (char *)malloc(FILE_NAME_MAX_LEN + 1);
    if (fullPath == NULL) {
        goto EXIT;
    }
    while (dir != NULL) {
        if (memset_s(fullPath, FILE_NAME_MAX_LEN + 1, 0x0, FILE_NAME_MAX_LEN + 1) != EOK) {
            goto EXIT;
        }
        if (sprintf_s(fullPath, FILE_NAME_MAX_LEN + 1, "%s/%s", g_kvFolder, dir->d_name) < 0) {
            goto EXIT;
        }
        if (unlink(fullPath) != 0) {
            goto EXIT;
        }
        dir = readdir(fileDir);
    }
    ret = NATIVE_SUCCESS;
EXIT:
    free(fullPath);
    closedir(fileDir);
    return ret;
}