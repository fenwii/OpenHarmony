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

#include "pms.h"

#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <securec.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "cJSON.h"
#include "log.h"

#include "feature.h"
#include "iunknown.h"
#include "memory_adapter.h"
#include "samgr_lite.h"
#include "service.h"

#include "perm_operate.h"

#define P_DIR "/storage/app/etc/permissions/"
#define P_NAME_MAXLEN 32
#define BUFF_SIZE 1024
#define PERM_MAX 1024
#define FIELD_PERMISSION "permissions"
#define FIELD_NAME "name"
#define FIELD_DESC "desc"
#define FIELD_IS_GRANTED "isGranted"

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

// Supported permissions
static PermissionDef g_permissions[] = {
    // appfwk
    {"ohos.permission.LISTEN_BUNDLE_CHANGE",  SYSTEM_GRANT,    NOT_RESTRICTED},
    {"ohos.permission.GET_BUNDLE_INFO",       SYSTEM_GRANT,    NOT_RESTRICTED},
    {"ohos.permission.INSTALL_BUNDLE",        SYSTEM_GRANT,    NOT_RESTRICTED},
    // media
    {"ohos.permission.CAMERA",                USER_GRANT,      NOT_RESTRICTED},
    {"ohos.permission.MODIFY_AUDIO_SETTINGS", SYSTEM_GRANT,    NOT_RESTRICTED},
    {"ohos.permission.READ_MEDIA",            USER_GRANT,      NOT_RESTRICTED},
    {"ohos.permission.MICROPHONE",            USER_GRANT,      NOT_RESTRICTED},
    {"ohos.permission.WRITE_MEDIA",           USER_GRANT,      NOT_RESTRICTED},
    // soft_bus
    {"ohos.permission.DISTRIBUTED_DATASYNC",  USER_GRANT,      NOT_RESTRICTED},
    // dvkit
    {"ohos.permission.DISTRIBUTED_VIRTUALDEVICE",  USER_GRANT,    NOT_RESTRICTED},
    // might expire in the future
    {"ohos.permission.RECORD_AUDIO",          USER_GRANT,    NOT_RESTRICTED},
    {"ohos.permission.READ_MEDIA_AUDIO",      USER_GRANT,    NOT_RESTRICTED},
    {"ohos.permission.READ_MEDIA_IMAGES",     USER_GRANT,    NOT_RESTRICTED},
    {"ohos.permission.READ_MEDIA_VIDEO",      USER_GRANT,    NOT_RESTRICTED},
    {"ohos.permission.WRITE_MEDIA_AUDIO",     USER_GRANT,    NOT_RESTRICTED},
    {"ohos.permission.WRITE_MEDIA_IMAGES",    USER_GRANT,    NOT_RESTRICTED},
    {"ohos.permission.WRITE_MEDIA_VIDEO",     USER_GRANT,    NOT_RESTRICTED},
};

static unsigned int g_permissionSize = sizeof(g_permissions) / sizeof(PermissionDef);

// Permission matrix of run-time tasks
static struct TaskList g_taskList = {
    NULL
};

// don't forget free() afterwards
static char *ConcatString(const char *s1, const char *s2)
{
    unsigned int allocSize = strlen(s1) + strlen(s2) + 1;
    if (allocSize > BUFF_SIZE) {
        return NULL;
    }
    char *rst = (char *) malloc(allocSize);
    if (rst == NULL) {
        return NULL;
    }
    if (memset_s(rst, allocSize, 0x0, allocSize) != EOK) {
        free(rst);
        return NULL;
    }
    if (strcpy_s(rst, allocSize, s1) != EOK) {
        free(rst);
        return NULL;
    }
    if (strcat_s(rst, allocSize, s2) != EOK) {
        free(rst);
        return NULL;
    }
    return rst;
}

static int WriteString(const char *path, const char *string)
{
    int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        return fd;
    }
    if (write(fd, string, strlen(string)) != strlen(string)) {
        close(fd);
        unlink(path);
        return PERM_ERRORCODE_WRITEFD_FAIL;
    }
    close(fd);
    return PERM_ERRORCODE_SUCCESS;
}

// don't forget free() afterwards
static char *ReadString(const char *path, int *errcode)
{
    char resolvedPath[PATH_MAX + 1] = {0x0};
    if (strlen(path) > PATH_MAX || NULL == realpath(path, resolvedPath)) {
        *errcode = PERM_ERRORCODE_PATH_INVALID;
        HILOG_ERROR(HILOG_MODULE_APP, "Path error.[path:%s][len:%d][line:%d]", path, strlen(path), __LINE__);
        return NULL;
    }

    struct stat buf;
    if (stat(path, &buf)) {
        *errcode = PERM_ERRORCODE_STAT_FAIL;
        return NULL;
    }
    int readSize = buf.st_size;
    char *rst = (char *) malloc(readSize);
    if (rst == NULL) {
        *errcode = PERM_ERRORCODE_MALLOC_FAIL;
        return NULL;
    }
    errno_t err = memset_s(rst, readSize, 0x0, readSize);
    if (err != EOK) {
        free(rst);
        *errcode = PERM_ERRORCODE_MEMSET_FAIL;
        return NULL;
    }

    int fd = open(resolvedPath, O_RDONLY);
    if (fd < 0) {
        free(rst);
        *errcode = PERM_ERRORCODE_OPENFD_FAIL;
        return NULL;
    }

    if (read(fd, rst, readSize) < 0) {
        free(rst);
        close(fd);
        *errcode = PERM_ERRORCODE_READFD_FAIL;
        return NULL;
    }

    close(fd);
    return rst;
}

static char *GetPath(const char *identifier)
{
    return ConcatString(P_DIR, identifier);
}

static int GetPermissionType(const char *permission)
{
    for (int i = 0; i < g_permissionSize; i++) {
        if (strcmp(permission, g_permissions[i].name) == 0) {
            return g_permissions[i].type;
        }
    }
    return PERM_ERRORCODE_INVALID_PERMNAME;
}

static int ParsePermissions(const char *jsonStr, PermissionSaved **perms, int *permNum)
{
    cJSON *root = cJSON_Parse(jsonStr);
    if (root == NULL) {
        return PERM_ERRORCODE_JSONPARSE_FAIL;
    }
    cJSON *array = cJSON_GetObjectItem(root, FIELD_PERMISSION);
    int pSize = cJSON_GetArraySize(array);
    int allocSize = sizeof(PermissionSaved) * pSize;
    if (allocSize == 0) {
        cJSON_Delete(root);
        return PERM_ERRORCODE_SUCCESS;
    }
    *perms = (PermissionSaved *) malloc(allocSize);
    if (*perms == NULL) {
        cJSON_Delete(root);
        return PERM_ERRORCODE_MALLOC_FAIL;
    }
    for (int i = 0; i < pSize; i++) {
        cJSON *object = cJSON_GetArrayItem(array, i);
        cJSON *itemName = cJSON_GetObjectItem(object, FIELD_NAME);
        cJSON *itemDesc = cJSON_GetObjectItem(object, FIELD_DESC);
        cJSON *itemGranted = cJSON_GetObjectItem(object, FIELD_IS_GRANTED);
        if (itemName == NULL || itemDesc == NULL || itemGranted == NULL) {
            cJSON_Delete(root);
            free(*perms);
            *perms = NULL;
            return PERM_ERRORCODE_JSONPARSE_FAIL;
        }
        if (strcpy_s((*perms + i)->name, PERM_NAME_LEN, itemName->valuestring) != EOK) {
            cJSON_Delete(root);
            free(*perms);
            *perms = NULL;
            return PERM_ERRORCODE_COPY_ERROR;
        }
        if (strcpy_s((*perms + i)->desc, PERM_DESC_LEN, itemDesc->valuestring) != EOK) {
            cJSON_Delete(root);
            free(*perms);
            *perms = NULL;
            return PERM_ERRORCODE_COPY_ERROR;
        }
        (*perms + i)->granted = (enum IsGranted) itemGranted->valueint;
    }
    *permNum = pSize;
    cJSON_Delete(root);
    return PERM_ERRORCODE_SUCCESS;
}

static int WritePermissions(cJSON *root, char *path)
{
    char *jsonStr = NULL;
    jsonStr = cJSON_PrintUnformatted(root);
    if (jsonStr == NULL) {
        free(path);
        cJSON_Delete(root);
        return PERM_ERRORCODE_MALLOC_FAIL;
    }
    int ret = WriteString(path, jsonStr);
    free(jsonStr);
    free(path);
    cJSON_Delete(root);
    return ret;
}

static int SavePermissions(const char *identifier, const PermissionSaved *permissions, int permNum)
{
    if (identifier == NULL || permissions == NULL) {
        return PERM_ERRORCODE_INVALID_PARAMS;
    }

    cJSON *root = NULL;
    cJSON *array = NULL;
    char *path = NULL;
    root = cJSON_CreateObject();
    if (root == NULL) {
        return PERM_ERRORCODE_MALLOC_FAIL;
    }
    array = cJSON_CreateArray();
    if (array == NULL) {
        cJSON_Delete(root);
        return PERM_ERRORCODE_MALLOC_FAIL;
    }
    path = GetPath(identifier);
    if (path == NULL) {
        cJSON_Delete(array);
        cJSON_Delete(root);
        return PERM_ERRORCODE_MALLOC_FAIL;
    }
    for (int i = 0; i < permNum; i++) {
        cJSON *object = cJSON_CreateObject();
        if (object == NULL) {
            free(path);
            cJSON_Delete(array);
            cJSON_Delete(root);
            return PERM_ERRORCODE_MALLOC_FAIL;
        }
        cJSON_AddItemToObject(object, FIELD_NAME, cJSON_CreateString(permissions[i].name));
        cJSON_AddItemToObject(object, FIELD_DESC, cJSON_CreateString(permissions[i].desc));
        cJSON_AddItemToObject(object, FIELD_IS_GRANTED, cJSON_CreateBool(permissions[i].granted));
        cJSON_AddItemToArray(array, object);
    }
    cJSON_AddItemToObject(root, FIELD_PERMISSION, array);
    return WritePermissions(root, path);
}

char *QueryPermissionString(const char *identifier, int *errCode)
{
    if (identifier == NULL) {
        *errCode = PERM_ERRORCODE_INVALID_PARAMS;
        return NULL;
    }

    int ret;
    char *path = NULL;
    char *jsonStr = NULL;

    path = GetPath(identifier);
    if (path == NULL) {
        *errCode = PERM_ERRORCODE_MALLOC_FAIL;
        return NULL;
    }
    ret = access(path, F_OK);
    if (ret) {
        free(path);
        *errCode = PERM_ERRORCODE_FILE_NOT_EXIST;
        return NULL;
    }

    jsonStr = ReadString(path, errCode);
    free(path);
    if (*errCode) {
        return NULL;
    }

    return jsonStr;
}

int QueryPermission(const char *identifier, PermissionSaved **permissions, int *permNum)
{
    int errCode = 0;
    char *jsonStr = QueryPermissionString(identifier, &errCode);
    if (errCode) {
        return errCode;
    }

    int ret = ParsePermissions(jsonStr, permissions, permNum);
    free(jsonStr);
    return ret;
}

int UpdateAppPermission(const char *identifier, PermissionTrans newPerms[], int newPermNum)
{
    PermissionSaved *permissions = NULL;
    int permNum = 0;
    int ret = QueryPermission(identifier, &permissions, &permNum);
    if (ret == PERM_ERRORCODE_FILE_NOT_EXIST) {
        return SaveOrUpdatePermissions(identifier, newPerms, newPermNum, FIRST_INSTALL);
    }
    if (ret != PERM_ERRORCODE_SUCCESS) {
        return ret;
    }
    int allocSize = sizeof(PermissionSaved) * newPermNum;
    PermissionSaved *updatePerms = (PermissionSaved *) malloc(allocSize);
    if (updatePerms == NULL) {
        free(permissions);
        return PERM_ERRORCODE_MALLOC_FAIL;
    }
    for (int i = 0; i < newPermNum; i++) {
        if (strlen(newPerms[i].name) > PERM_NAME_LEN - 1 || strlen(newPerms[i].desc) > PERM_DESC_LEN - 1) {
            free(updatePerms);
            free(permissions);
            return PERM_ERRORCODE_FIELD_TOO_LONG;
        }
        if (strcpy_s((updatePerms + i)->name, PERM_NAME_LEN, newPerms[i].name) != EOK) {
            free(updatePerms);
            free(permissions);
            return PERM_ERRORCODE_COPY_ERROR;
        }
        if (strcpy_s((updatePerms + i)->desc, PERM_DESC_LEN, newPerms[i].desc) != EOK) {
            free(updatePerms);
            free(permissions);
            return PERM_ERRORCODE_COPY_ERROR;
        }
        int permType = GetPermissionType(newPerms[i].name);
        if (permType == PERM_ERRORCODE_INVALID_PERMNAME) {
            free(updatePerms);
            free(permissions);
            return PERM_ERRORCODE_INVALID_PERMNAME;
        }
        (updatePerms + i)->granted = (permType == SYSTEM_GRANT) ? GRANTED : NOT_GRANTED;
        for (int j = 0; j < permNum; j++) {
            if (strcmp(newPerms[i].name, (permissions + j)->name) == 0) {
                (updatePerms + i)->granted = permissions[j].granted;
            }
        }
    }
    int retCode = SavePermissions(identifier, updatePerms, newPermNum);
    free(updatePerms);
    free(permissions);
    return retCode;
}

static int FormPermissions(const PermissionTrans permissions[], int permNum, char *path, cJSON *root, cJSON *array)
{
    for (int i = 0; i < permNum; i++) {
        if (strlen(permissions[i].name) > PERM_NAME_LEN - 1 || strlen(permissions[i].desc) > PERM_DESC_LEN - 1) {
            free(path);
            cJSON_Delete(array);
            cJSON_Delete(root);
            return PERM_ERRORCODE_FIELD_TOO_LONG;
        }
        cJSON *object = cJSON_CreateObject();
        if (object == NULL) {
            free(path);
            cJSON_Delete(array);
            cJSON_Delete(root);
            return PERM_ERRORCODE_MALLOC_FAIL;
        }
        cJSON_AddItemToObject(object, FIELD_NAME, cJSON_CreateString(permissions[i].name));
        cJSON_AddItemToObject(object, FIELD_DESC, cJSON_CreateString(permissions[i].desc));
        int permType = GetPermissionType(permissions[i].name);
        if (permType == PERM_ERRORCODE_INVALID_PERMNAME) {
            free(path);
            cJSON_Delete(object);
            cJSON_Delete(array);
            cJSON_Delete(root);
            return PERM_ERRORCODE_INVALID_PERMNAME;
        }
        cJSON_AddItemToObject(object, FIELD_IS_GRANTED, cJSON_CreateBool(permType));
        cJSON_AddItemToArray(array, object);
    }
    cJSON_AddItemToObject(root, FIELD_PERMISSION, array);
    return WritePermissions(root, path);
}

int SaveOrUpdatePermissions(const char *identifier, PermissionTrans permissions[], int permNum, enum IsUpdate isUpdate)
{
    if (identifier == NULL || permissions == NULL || (isUpdate != UPDATE && isUpdate != FIRST_INSTALL)) {
        return PERM_ERRORCODE_INVALID_PARAMS;
    }
    if (permNum > PERM_MAX) {
        return PERM_ERRORCODE_TOO_MUCH_PERM;
    }
    if (isUpdate == UPDATE) {
        return UpdateAppPermission(identifier, permissions, permNum);
    }
    cJSON *root = NULL;
    cJSON *array = NULL;
    char *path = NULL;
    root = cJSON_CreateObject();
    if (root == NULL) {
        return PERM_ERRORCODE_MALLOC_FAIL;
    }
    array = cJSON_CreateArray();
    if (array == NULL) {
        cJSON_Delete(root);
        return PERM_ERRORCODE_MALLOC_FAIL;
    }
    path = GetPath(identifier);
    if (path == NULL) {
        cJSON_Delete(array);
        cJSON_Delete(root);
        return PERM_ERRORCODE_MALLOC_FAIL;
    }
    return FormPermissions(permissions, permNum, path, root, array);
}

int DeletePermissions(const char *identifier)
{
    if (identifier == NULL) {
        return PERM_ERRORCODE_INVALID_PARAMS;
    }
    int ret;
    char *path = NULL;
    path = GetPath(identifier);
    if (path == NULL) {
        return PERM_ERRORCODE_MALLOC_FAIL;
    }

    ret = access(path, F_OK);
    if (ret != 0) {
        free(path);
        return PERM_ERRORCODE_SUCCESS;
    }

    ret = unlink(path);
    if (ret != 0) {
        free(path);
        return PERM_ERRORCODE_UNLINK_ERROR;
    }

    free(path);
    return PERM_ERRORCODE_SUCCESS;
}

int IsPermissionValid(const char *permissionName)
{
    for (int i = 0; i < g_permissionSize; i++) {
        if (strcmp(permissionName, g_permissions[i].name) == 0) {
            return PERM_ERRORCODE_SUCCESS;
        }
    }
    return PERM_ERRORCODE_INVALID_PERMNAME;
}

int IsPermissionRestricted(const char *permissionName)
{
    for (int i = 0; i < g_permissionSize; i++) {
        if (strcmp(permissionName, g_permissions[i].name) == 0) {
            return g_permissions[i].isRestricted;
        }
    }
    return PERM_ERRORCODE_INVALID_PERMNAME;
}

int LoadPermissions(const char *identifier, int taskID)
{
    pthread_mutex_lock(&g_mutex);
    TNode *task = GetTask(&g_taskList, taskID);
    pthread_mutex_unlock(&g_mutex);
    if (task != NULL) {
        return PERM_ERRORCODE_SUCCESS;
    }
    PermissionSaved *permissions = NULL;
    int permNum = 0;
    int ret = QueryPermission(identifier, &permissions, &permNum);
    if (ret == PERM_ERRORCODE_FILE_NOT_EXIST) {
        HILOG_INFO(HILOG_MODULE_APP, "Perm file not exists[pkgName: %s]", identifier);
        return PERM_ERRORCODE_SUCCESS;
    }
    if (ret != PERM_ERRORCODE_SUCCESS) {
        return ret;
    }

    TNode *node = (TNode *) malloc(sizeof(TNode));
    if (node == NULL) {
        free(permissions);
        return PERM_ERRORCODE_MALLOC_FAIL;
    }
    node->taskID = taskID;
    if (strcpy_s(node->pkgName, PKG_NAME_LEN, identifier) != EOK) {
        free(permissions);
        free(node);
        return PERM_ERRORCODE_COPY_ERROR;
    }
    node->permList = permissions;
    node->permNum = permNum;
    node->next = NULL;

    pthread_mutex_lock(&g_mutex);
    AddTask(&g_taskList, node);
    pthread_mutex_unlock(&g_mutex);

    return PERM_ERRORCODE_SUCCESS;
}

int UnLoadPermissions(int taskID)
{
    pthread_mutex_lock(&g_mutex);
    DeleteTask(&g_taskList, taskID);
    pthread_mutex_unlock(&g_mutex);
    return PERM_ERRORCODE_SUCCESS;
}

int CheckPermissionStat(int taskID, const char *permissionName)
{
    if (taskID < 0 || permissionName == NULL) {
        return PERM_ERRORCODE_INVALID_PARAMS;
    }
    pthread_mutex_lock(&g_mutex);
    int ret = PermissionExists(&g_taskList, taskID, permissionName);
    pthread_mutex_unlock(&g_mutex);
    return ret;
}

int GrantPermission(const char *identifier, const char *permName)
{
    PermissionSaved *permissions = NULL;
    int permNum = 0;
    int ret = QueryPermission(identifier, &permissions, &permNum);
    if (ret != PERM_ERRORCODE_SUCCESS) {
        return ret;
    }
    for (int i = 0; i < permNum; i++) {
        if (strcmp((permissions + i)->name, permName) == 0) {
            (permissions + i)->granted = GRANTED;
            break;
        }
    }
    int retCode = SavePermissions(identifier, permissions, permNum);
    free(permissions);
    return retCode;
}

int RevokePermission(const char *identifier, const char *permName)
{
    PermissionSaved *permissions = NULL;
    int permNum = 0;
    int ret = QueryPermission(identifier, &permissions, &permNum);
    if (ret != PERM_ERRORCODE_SUCCESS) {
        return ret;
    }
    for (int i = 0; i < permNum; i++) {
        if (strcmp((permissions + i)->name, permName) == 0) {
            (permissions + i)->granted = NOT_GRANTED;
            break;
        }
    }
    int retCode = SavePermissions(identifier, permissions, permNum);
    free(permissions);
    return retCode;
}

int GrantRuntimePermission(int taskID, const char *permissionName)
{
    pthread_mutex_lock(&g_mutex);
    TNode *node = GetTask(&g_taskList, taskID);
    pthread_mutex_unlock(&g_mutex);
    if (node == NULL) {
        return PERM_ERRORCODE_TASKID_NOT_EXIST;
    }

    pthread_mutex_lock(&g_mutex);
    int ret = ModifyPermission(&g_taskList, taskID, permissionName, GRANTED);
    pthread_mutex_unlock(&g_mutex);
    if (ret < 0) {
        return PERM_ERRORCODE_PERM_NOT_EXIST;
    }

    return GrantPermission(node->pkgName, permissionName);
}

int RequestPermission(int taskID, const char *permissionName)
{
    HILOG_INFO(HILOG_MODULE_APP, "Requset permission[taskID: %d][permName: %s]", taskID, permissionName);

    pthread_mutex_lock(&g_mutex);
    TNode *node = GetTask(&g_taskList, taskID);
    pthread_mutex_unlock(&g_mutex);
    if (node == NULL) {
        return PERM_ERRORCODE_TASKID_NOT_EXIST;
    }

    // Requesting users to grant permissions hasn't been implemented.
    return PERM_ERRORCODE_SUCCESS;
}
