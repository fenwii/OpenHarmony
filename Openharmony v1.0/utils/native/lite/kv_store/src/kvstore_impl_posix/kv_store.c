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
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <securec.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "kvstore_common.h"
#include "kvstore_env.h"
#include "ohos_errno.h"
#include "ohos_types.h"
#include "utils_config.h"

#define KVSTORE_PATH       "kvstore"
#define MAX_KEY_PATH       256
#define MAX_GET_VALUE_LEN  0x7FFFFFFF
static pthread_mutex_t g_kvGlobalMutex = PTHREAD_MUTEX_INITIALIZER;
static int g_kvSum = 0;
static boolean g_getKvSum = FALSE;
static char g_dataPath[MAX_KEY_PATH + 1] = {0};

static int GetResolvedPath(const char* dataPath, const char* key, char* resolvedPath, unsigned int len)
{
    char* keyPath = (char *)malloc(MAX_KEY_PATH + 1);
    if (keyPath == NULL) {
        return EC_FAILURE;
    }
    if (sprintf_s(keyPath, MAX_KEY_PATH + 1, "%s/%s/%s", dataPath, KVSTORE_PATH, key) < 0) {
        free(keyPath);
        return EC_FAILURE;
    }
    if (realpath(keyPath, resolvedPath) != NULL) {
        free(keyPath);
        return EC_SUCCESS;
    }
    if (errno == ENOENT) {
        if (strncpy_s(resolvedPath, len, keyPath, strlen(keyPath)) == EOK) {
            free(keyPath);
            return EC_SUCCESS;
        }
    }
    free(keyPath);
    return EC_FAILURE;
}

static int GetValueByFile(const char* dataPath, const char* key, char* value, unsigned int len)
{
    char* keyPath = (char *)malloc(PATH_MAX + 1);
    if (keyPath == NULL) {
        return EC_FAILURE;
    }
    if (GetResolvedPath(dataPath, key, keyPath, PATH_MAX + 1) != EC_SUCCESS) {
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
        return EC_FAILURE;
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

static int SetValueToFile(const char* dataPath, const char* key, const char* value)
{
    char* keyPath = (char *)malloc(PATH_MAX + 1);
    if (keyPath == NULL) {
        return EC_FAILURE;
    }
    if (GetResolvedPath(dataPath, key, keyPath, PATH_MAX + 1) != EC_SUCCESS) {
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

static int DeleteValueFromFile(const char* dataPath, const char* key)
{
    char* keyPath = (char *)malloc(MAX_KEY_PATH + 1);
    if (keyPath == NULL) {
        return EC_FAILURE;
    }
    if (sprintf_s(keyPath, MAX_KEY_PATH + 1, "%s/%s/%s", dataPath, KVSTORE_PATH, key) < 0) {
        free(keyPath);
        return EC_FAILURE;
    }
    int ret = unlink(keyPath);
    free(keyPath);
    return ret;
}

static int InitKv(const char* dataPath)
{
    if (dataPath == NULL) {
        return EC_FAILURE;
    }
    char* kvPath = (char *)malloc(MAX_KEY_PATH + 1);
    if (kvPath == NULL) {
        return EC_FAILURE;
    }
    if (sprintf_s(kvPath, MAX_KEY_PATH + 1, "%s/%s", dataPath, KVSTORE_PATH) < 0) {
        free(kvPath);
        return EC_FAILURE;
    }
    if (access(kvPath, F_OK) == F_OK) {
        free(kvPath);
        return EC_SUCCESS;
    }
    if (mkdir(kvPath, S_IRUSR | S_IWUSR | S_IXUSR) != F_OK) {
        free(kvPath);
        return EC_FAILURE;
    }
    free(kvPath);
    return EC_SUCCESS;
}

static int GetCurrentItem(const char* dataPath)
{
    char kvPath[MAX_KEY_PATH + 1] = {0};
    if (sprintf_s(kvPath, MAX_KEY_PATH + 1, "%s/%s", dataPath, KVSTORE_PATH) < 0) {
        return EC_FAILURE;
    }
    DIR *fileDir = opendir(kvPath);
    if (fileDir == NULL) {
        return EC_FAILURE;
    }
    struct dirent *dir = readdir(fileDir);
    int sum = 0;
    while (dir != NULL) {
        char fullPath[MAX_KEY_PATH + 1] = {0};
        struct stat info = {0};
        if (sprintf_s(fullPath, MAX_KEY_PATH + 1, "%s/%s", kvPath, dir->d_name) < 0) {
            closedir(fileDir);
            return EC_FAILURE;
        }
        if (stat(fullPath, &info) != 0) {
            closedir(fileDir);
            return EC_FAILURE;
        }
        if (S_ISREG(info.st_mode)) {
            sum++;
        }
        dir = readdir(fileDir);
    }
    closedir(fileDir);
    return sum;
}

static boolean NewItem(const char* dataPath, const char* key)
{
    char* keyPath = (char *)malloc(MAX_KEY_PATH + 1);
    if (keyPath == NULL) {
        return FALSE;
    }
    if (sprintf_s(keyPath, MAX_KEY_PATH + 1, "%s/%s/%s", dataPath, KVSTORE_PATH, key) < 0) {
        free(keyPath);
        return FALSE;
    }
    if (access(keyPath, F_OK) == F_OK) {
        free(keyPath);
        return FALSE;
    }
    free(keyPath);
    return TRUE;
}

int UtilsGetValue(const char* key, char* value, unsigned int len)
{
    if (!IsValidKey(key) || (value == NULL) || (len > MAX_GET_VALUE_LEN)) {
        return EC_INVALID;
    }
    pthread_mutex_lock(&g_kvGlobalMutex);
    const char* dataPath = g_dataPath;
    if (dataPath == NULL) {
        pthread_mutex_unlock(&g_kvGlobalMutex);
        return EC_FAILURE;
    }
#ifdef FEATURE_KV_CACHE
    if (GetValueByCache(key, value, len) == EC_SUCCESS) {
        pthread_mutex_unlock(&g_kvGlobalMutex);
        return EC_SUCCESS;
    }
#endif
    int ret = GetValueByFile(dataPath, key, value, len);
    if (ret < 0) {
        pthread_mutex_unlock(&g_kvGlobalMutex);
        return EC_FAILURE;
    }
#ifdef FEATURE_KV_CACHE
    AddKVCache(key, value, FALSE);
#endif
    pthread_mutex_unlock(&g_kvGlobalMutex);
    return ret;
}

int UtilsSetValue(const char* key, const char* value)
{
    if (!IsValidKey(key) || !IsValidValue(value, MAX_VALUE_LEN)) {
        return EC_INVALID;
    }
    pthread_mutex_lock(&g_kvGlobalMutex);
    const char* dataPath = g_dataPath;
    int ret = InitKv(dataPath);
    if (ret != EC_SUCCESS) {
        g_getKvSum = FALSE;
        pthread_mutex_unlock(&g_kvGlobalMutex);
        return EC_FAILURE;
    }
    if (!g_getKvSum) {
        g_kvSum = GetCurrentItem(dataPath);
        if (g_kvSum < 0) {
            pthread_mutex_unlock(&g_kvGlobalMutex);
            return EC_FAILURE;
        }
        g_getKvSum = TRUE;
    }
    boolean newItem = NewItem(dataPath, key);
    if ((g_kvSum >= MAX_KV_SUM) && newItem) {
        pthread_mutex_unlock(&g_kvGlobalMutex);
        return EC_FAILURE;
    }
    ret = SetValueToFile(dataPath, key, value);
    if (ret == EC_SUCCESS) {
#ifdef FEATURE_KV_CACHE
        AddKVCache(key, value, TRUE);
#endif
        if (newItem) {
            g_kvSum++;
        }
    }
    pthread_mutex_unlock(&g_kvGlobalMutex);
    return ret;
}

int UtilsDeleteValue(const char* key)
{
    if (!IsValidKey(key)) {
        return EC_INVALID;
    }
    pthread_mutex_lock(&g_kvGlobalMutex);
    const char* dataPath = g_dataPath;
    if (dataPath == NULL) {
        pthread_mutex_unlock(&g_kvGlobalMutex);
        return EC_FAILURE;
    }
#ifdef FEATURE_KV_CACHE
    DeleteKVCache(key);
#endif
    int ret = DeleteValueFromFile(dataPath, key);
    if (ret == EC_SUCCESS) {
        g_kvSum--;
    }
    pthread_mutex_unlock(&g_kvGlobalMutex);
    return ret;
}

#ifdef FEATURE_KV_CACHE
int ClearKVCache(void)
{
    int ret;
    pthread_mutex_lock(&g_kvGlobalMutex);
    ret = ClearKVCacheInner();
    pthread_mutex_unlock(&g_kvGlobalMutex);
    return ret;
}
#endif

int UtilsSetEnv(const char* path)
{
    if (path == NULL) {
        return EC_FAILURE;
    }
    pthread_mutex_lock(&g_kvGlobalMutex);
    if (strcpy_s(g_dataPath, MAX_KEY_PATH + 1, path) != EOK) {
        pthread_mutex_unlock(&g_kvGlobalMutex);
        return EC_FAILURE;
    }
    pthread_mutex_unlock(&g_kvGlobalMutex);
    return EC_SUCCESS;
}