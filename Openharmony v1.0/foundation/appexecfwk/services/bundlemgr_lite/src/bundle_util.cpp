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

#include "bundle_util.h"

#include <new>

#include "appexecfwk_errors.h"
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
#include <climits>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "bundle_daemon_client.h"
#else
#include <limits.h>
#include "mc_fs.h"
#endif
#include "utils.h"

namespace OHOS {
const char DIGITSTR[] = "0123456789";
/*
 * path should not include ".." or "./" or ".\0"
 */
bool BundleUtil::CheckRealPath(const char *path)
{
    if (path == nullptr || strlen(path) > PATH_LENGTH) {
        return false;
    }
    char *next = const_cast<char *>(path);
    for (; *next != '\0'; next++) {
        if (*next != '.') {
            continue;
        }
        next++;
        if (*next == '\0' || *next == '.' || *next == '/') {
            return false;
        }
    }
    return true;
}

bool BundleUtil::IsFile(const char *path)
{
    if (!CheckRealPath(path)) {
        return false;
    }

    struct stat buf = { 0 };
    int32_t ret = stat(path, &buf);
    if (ret != 0) {
        return false;
    }

    int32_t fp = open(path, O_RDONLY, S_IREAD | S_IWRITE);
    if (fp >= 0) {
        close(fp);
        return true;
    }
    return false;
}

bool BundleUtil::IsDir(const char *path)
{
    if (path == nullptr) {
        return false;
    }

    struct stat buf = { 0 };
    int32_t ret = stat(path, &buf);
    if (ret != 0) {
        return false;
    }
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    if ((buf.st_mode & S_IFDIR) == S_IFDIR) {
        return true;
    }
#else
    if ((buf.attr & AM_DIR) == AM_DIR) {
        return true;
    }
#endif
    return false;
}

bool BundleUtil::EndWith(const char *str, const char *subStr)
{
    if (str == nullptr || subStr == nullptr) {
        return false;
    }

    int32_t strLen = strlen(str);
    int32_t subStrLen = strlen(subStr);
    if (strLen == 0 || subStrLen == 0 || strLen < subStrLen) {
        return false;
    }

    while (subStrLen >= 1) {
        if (str[strLen - 1] != subStr[subStrLen - 1]) {
            return false;
        }
        strLen--;
        subStrLen--;
    }
    return true;
}

bool BundleUtil::StartWith(const char *str, const char *subStr)
{
    if (str == nullptr || subStr == nullptr) {
        return false;
    }

    int32_t strLen = strlen(str);
    int32_t subStrLen = strlen(subStr);
    if (strLen == 0 || subStrLen == 0 || strLen < subStrLen) {
        return false;
    }

    int32_t index = 0;
    while (index < subStrLen) {
        if (str[index] != subStr[index]) {
            return false;
        }
        index++;
    }
    return true;
}

bool BundleUtil::IsDigitStr(const char *str)
{
    if (str == nullptr) {
        return false;
    }
    return strspn(str, DIGITSTR) == strlen(str);
}

uint32_t BundleUtil::GetFileSize(const char *filePath)
{
    if (!CheckRealPath(filePath)) {
        return 0;
    }

    struct stat fileInfo;
    int32_t ret = stat(filePath, &fileInfo);
    if (ret != 0) {
        return 0;
    }
    return fileInfo.st_size;
}

void BundleUtil::DeleteJsonFile(const char *bundleName)
{
    if (bundleName == nullptr) {
        return;
    }
    char *bundleTmpJsonPathComp[] = {
        const_cast<char *>(JSON_PATH), const_cast<char *>(PATH_SEPARATOR),
        const_cast<char *>(bundleName), const_cast<char *>(TMP_SUFFIX), const_cast<char *>(JSON_SUFFIX)
    };

    char *bundleTmpJsonPath = Strscat(bundleTmpJsonPathComp, sizeof(bundleTmpJsonPathComp) / sizeof(char *));
    if (bundleTmpJsonPath == nullptr) {
        return;
    }

    if (IsFile(bundleTmpJsonPath)) {
        BundleDaemonClient::GetInstance().RemoveFile(bundleTmpJsonPath);
        AdapterFree(bundleTmpJsonPath);
        return;
    }
    AdapterFree(bundleTmpJsonPath);

    char *bundleJsonPathComp[] = {
        const_cast<char *>(JSON_PATH), const_cast<char *>(PATH_SEPARATOR),
        const_cast<char *>(bundleName), const_cast<char *>(JSON_SUFFIX)
    };
    char *bundleJsonPath = Strscat(bundleJsonPathComp, sizeof(bundleJsonPathComp) / sizeof(char *));
    if (bundleJsonPath == nullptr) {
        return;
    }
    if (IsFile(bundleJsonPath)) {
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
        BundleDaemonClient::GetInstance().RemoveFile(bundleJsonPath);
#else
        (void)unlink(bundleJsonPath);
#endif
    }
    AdapterFree(bundleJsonPath);
}

char *BundleUtil::Strscat(char *str[], uint32_t len)
{
    int32_t strSize = 0;
    for (uint32_t i = 0; i < len; i++) {
        if (str[i] == nullptr) {
            return nullptr;
        }
        strSize += strlen(str[i]);
    }

    char *outStr = reinterpret_cast<char *>(AdapterMalloc((strSize + 1) * sizeof(char)));
    if (outStr == nullptr) {
        return nullptr;
    }

    if (strncpy_s(outStr, strSize + 1, str[0], strlen(str[0])) != EOK) {
        AdapterFree(outStr);
        return nullptr;
    }

    for (uint32_t i = 1; i < len; i++) {
        errno_t err = strncat_s(outStr, strSize + 1, str[i], strlen(str[i]));
        if (err != EOK) {
            AdapterFree(outStr);
            return nullptr;
        }
    }
    return outStr;
}

cJSON *BundleUtil::GetJsonStream(const char *path)
{
    struct stat fileInfo;
    int32_t size = 0;

    if (stat(path, &fileInfo) != 0 || (size = fileInfo.st_size) <= 0) {
        return nullptr;
    }

    if (size * sizeof(char) > INT_MAX) {
        return nullptr;
    }

    if (!CheckRealPath(path)) {
        return nullptr;
    }

    int32_t fp = open(path, O_RDONLY, S_IREAD | S_IWRITE);
    if (fp < 0) {
        return nullptr;
    }

    char *json = reinterpret_cast<char *>(AdapterMalloc(size * sizeof(char)));
    if (json == nullptr) {
        close(fp);
        return nullptr;
    }
    if (read(fp, json, size * sizeof(char)) != static_cast<int32_t>(size * sizeof(char))) {
        AdapterFree(json);
        close(fp);
        return nullptr;
    }
    close(fp);

    cJSON *root = cJSON_Parse(json);
    AdapterFree(json);
    json = nullptr;
    return root;
}

bool BundleUtil::CheckBundleJsonIsValid(const char *bundleName, char **codePath, char **appId, int32_t &versionCode)
{
    *codePath = GetValueFromBundleJson(bundleName, JSON_SUB_KEY_CODEPATH);
    if (*codePath == nullptr || !IsDir(*codePath) || !EndWith(*codePath, bundleName)) {
        return false;
    }

    *appId = GetValueFromBundleJson(bundleName, JSON_SUB_KEY_APPID);
    if (*appId == nullptr) {
        return false;
    }

    versionCode = GetValueFromBundleJson(bundleName, JSON_SUB_KEY_VERSIONCODE, -1);
    if (versionCode == -1) {
        return false;
    }
    return true;
}

char *BundleUtil::GetValueFromBundleJson(const char *bundleName, const char *key)
{
    char *bundleJsonPathComp[] = {
        const_cast<char *>(JSON_PATH), const_cast<char *>(PATH_SEPARATOR),
        const_cast<char *>(bundleName), const_cast<char *>(JSON_SUFFIX)
    };
    char *bundleJsonPath = Strscat(bundleJsonPathComp, sizeof(bundleJsonPathComp) / sizeof(char *));
    if (bundleJsonPath == nullptr) {
        return nullptr;
    }

    cJSON *object = GetJsonStream(bundleJsonPath);
    if (object == nullptr) {
        AdapterFree(bundleJsonPath);
        return nullptr;
    }
    AdapterFree(bundleJsonPath);

    cJSON *item = cJSON_GetObjectItem(object, key);
    if (!cJSON_IsString(item)) {
        cJSON_Delete(object);
        return nullptr;
    }

    char *value = Utils::Strdup(item->valuestring);
    cJSON_Delete(object);
    return value;
}

int32_t BundleUtil::GetValueFromBundleJson(const char *bundleName, const char *key, int32_t defaultValue)
{
    char *bundleJsonPathComp[] = {
        const_cast<char *>(JSON_PATH), const_cast<char *>(PATH_SEPARATOR),
        const_cast<char *>(bundleName), const_cast<char *>(JSON_SUFFIX)
    };
    char *bundleJsonPath = Strscat(bundleJsonPathComp, sizeof(bundleJsonPathComp) / sizeof(char *));
    if (bundleJsonPath == nullptr) {
        return defaultValue;
    }

    cJSON *object = GetJsonStream(bundleJsonPath);
    if (object == nullptr) {
        AdapterFree(bundleJsonPath);
        return defaultValue;
    }
    AdapterFree(bundleJsonPath);

    cJSON *item = cJSON_GetObjectItem(object, key);
    if (!cJSON_IsNumber(item)) {
        cJSON_Delete(object);
        return defaultValue;
    }

    int32_t value = item->valueint;
    cJSON_Delete(object);
    return value;
}

cJSON *BundleUtil::ConvertInstallRecordToJson(const InstallRecord &installRecord)
{
    cJSON *root = cJSON_CreateObject();
    if (root == nullptr) {
        return nullptr;
    }

    if ((cJSON_AddStringToObject(root, JSON_SUB_KEY_PACKAGE, installRecord.bundleName) == nullptr) ||
#ifndef __LINUX__
        (cJSON_AddStringToObject(root, JSON_SUB_KEY_APPID, installRecord.appId) == nullptr) ||
#endif
        (cJSON_AddNumberToObject(root, JSON_SUB_KEY_VERSIONCODE, installRecord.versionCode) == nullptr) ||
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
        (cJSON_AddNumberToObject(root, JSON_SUB_KEY_UID, installRecord.uid) == nullptr) ||
        (cJSON_AddNumberToObject(root, JSON_SUB_KEY_GID, installRecord.gid) == nullptr) ||
#endif
        (cJSON_AddStringToObject(root, JSON_SUB_KEY_CODEPATH, installRecord.codePath) == nullptr)) {
        cJSON_Delete(root);
        return nullptr;
    }
    return root;
}

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
cJSON *BundleUtil::ObtainUidAndGidJson(bool flag)
{
    std::string uidJsonPath = std::string(JSON_PATH) + PATH_SEPARATOR + UID_GID_MAP + JSON_SUFFIX;
    cJSON *object = BundleUtil::GetJsonStream(uidJsonPath.c_str());
    if ((object != nullptr) || (!flag)) {
        return object;
    }

    object = cJSON_CreateObject();
    if (object == nullptr) {
        return nullptr;
    }
    cJSON *size = cJSON_CreateNumber(0);
    if (size == nullptr) {
        cJSON_Delete(object);
        return nullptr;
    }
    if (!cJSON_AddItemToObject(object, PROFILE_KEY_UID_SIZE, size)) {
        cJSON_Delete(size);
        cJSON_Delete(object);
        return nullptr;
    }
    cJSON *uids = cJSON_AddArrayToObject(object, PROFILE_KEY_UID_AND_GID);
    if (uids == nullptr) {
        cJSON_Delete(object);
        return nullptr;
    }
    return object;
}

bool BundleUtil::AddUidAndGidInfo(const InstallRecord &installRecord, cJSON *size, cJSON *uids)
{
    if ((size == nullptr) || (uids == nullptr)) {
        return false;
    }
    cJSON_SetNumberValue(size, size->valueint + 1);
    cJSON *uid = cJSON_CreateObject();
    if (uid == nullptr) {
        return false;
    }
    if ((cJSON_AddStringToObject(uid, JSON_SUB_KEY_PACKAGE, installRecord.bundleName) == nullptr) ||
        (cJSON_AddNumberToObject(uid, JSON_SUB_KEY_UID, installRecord.uid) == nullptr) ||
        (cJSON_AddNumberToObject(uid, JSON_SUB_KEY_GID, installRecord.gid) == nullptr)) {
        cJSON_Delete(uid);
        return false;
    }
    if (!cJSON_AddItemToArray(uids, uid)) {
        cJSON_Delete(uid);
        return false;
    }
    return true;
}

cJSON *BundleUtil::ConvertUidAndGidToJson(const InstallRecord &installRecord)
{
    if (installRecord.bundleName == nullptr) {
        return nullptr;
    }

    cJSON *object = ObtainUidAndGidJson(true);
    if (object == nullptr) {
        return nullptr;
    }

    cJSON *size = cJSON_GetObjectItemCaseSensitive(object, PROFILE_KEY_UID_SIZE);
    if (!cJSON_IsNumber(size)) {
        cJSON_Delete(object);
        return nullptr;
    }
    cJSON *uids = cJSON_GetObjectItemCaseSensitive(object, PROFILE_KEY_UID_AND_GID);
    if (!cJSON_IsArray(uids)) {
        cJSON_Delete(object);
        return nullptr;
    }

    cJSON *item = nullptr;
    cJSON_ArrayForEach(item, uids) {
        cJSON *innerBundleName = cJSON_GetObjectItemCaseSensitive(item, JSON_SUB_KEY_PACKAGE);
        if ((cJSON_IsString(innerBundleName)) && (innerBundleName->valuestring != nullptr)) {
            if (strcmp(innerBundleName->valuestring, installRecord.bundleName) == 0) {
                return object;
            }
        }
    }

    if (!AddUidAndGidInfo(installRecord, size, uids)) {
        cJSON_Delete(object);
        return nullptr;
    }

    return object;
}

bool BundleUtil::DeleteInnerUidInfoFromUidArray(const char *bundleName, cJSON *size, cJSON *uids)
{
    if ((size == nullptr) || (uids == nullptr) || (bundleName == nullptr)) {
        return false;
    }
    cJSON *uid = nullptr;
    int32_t index = -1;
    bool isFound = false;
    cJSON_ArrayForEach(uid, uids) {
        index++;
        cJSON *innerBundleName = cJSON_GetObjectItemCaseSensitive(uid, JSON_SUB_KEY_PACKAGE);
        if ((cJSON_IsString(innerBundleName)) && (innerBundleName->valuestring != nullptr)) {
            if (strcmp(innerBundleName->valuestring, bundleName) == 0) {
                isFound = true;
                break;
            }
        }
    }
    if (isFound) {
        cJSON_DeleteItemFromArray(uids, index);
        cJSON_SetNumberValue(size, size->valueint - 1);
    }
    return true;
}

bool BundleUtil::DeleteUidInfoFromJson(const char *bundleName)
{
    cJSON *object = ObtainUidAndGidJson(false);
    if (object == nullptr) {
        return false;
    }

    cJSON *size = cJSON_GetObjectItemCaseSensitive(object, PROFILE_KEY_UID_SIZE);
    if (!cJSON_IsNumber(size)) {
        cJSON_Delete(object);
        return false;
    }
    cJSON *uids = cJSON_GetObjectItemCaseSensitive(object, PROFILE_KEY_UID_AND_GID);
    if (!cJSON_IsArray(uids)) {
        cJSON_Delete(object);
        return false;
    }
    if (!DeleteInnerUidInfoFromUidArray(bundleName, size, uids)) {
        cJSON_Delete(object);
        return false;
    }

    std::string uidJsonPath = std::string(JSON_PATH) + PATH_SEPARATOR + UID_GID_MAP + JSON_SUFFIX;
    if (size->valueint == 0) {
        BundleDaemonClient::GetInstance().RemoveFile(uidJsonPath.c_str());
    } else {
        char *out = cJSON_Print(object);
        if (out == nullptr) {
            cJSON_Delete(object);
            return false;
        }
        BundleDaemonClient::GetInstance().StoreContentToFile(uidJsonPath.c_str(), out, strlen(out) + 1);
        cJSON_free(out);
    }

    cJSON_Delete(object);
    return true;
}
#else
bool BundleUtil::MkDirs(const char *dir)
{
    if (IsDir(dir)) {
        return true;
    }
    if (strlen(dir) > PATH_LENGTH) {
        return false;
    }
    int32_t len = strlen(dir);
    char *rootDir = nullptr;
    bool isRootDirExists = true;
    for (int32_t i = 1; i < len; i++) {
        if (dir[i] != '/') {
            continue;
        }
        rootDir = GetRootDir(dir, i);
        if (rootDir == nullptr) {
            return false;
        }
        if (isRootDirExists) {
            if (IsDir(rootDir)) {
                AdapterFree(rootDir);
                continue;
            }
            isRootDirExists = false;
        }
        if (mkdir(rootDir, S_IREAD | S_IWRITE) < 0) {
            AdapterFree(rootDir);
            return false;
        }
        AdapterFree(rootDir);
    }
    return (mkdir(dir, S_IREAD | S_IWRITE) < 0) ? false : true;
}

bool BundleUtil::RemoveDir(const char *path)
{
    if (!IsDir(path)) {
        (void) unlink(path);
        return true;
    }

    List<char *>* list = new (std::nothrow)List<char *>();
    if (list == nullptr) {
        return false;
    }
    list->PushFront(Utils::Strdup(path));
    while (!list->IsEmpty()) {
        char *curPath = list->Front();
        if (curPath == nullptr) {
            break;
        }
        if (CheckDirIsEmpty(curPath, list)) {
            list->PopFront();
            if (rmdir(curPath) < 0) {
                AdapterFree(curPath);
                break;
            }
            AdapterFree(curPath);
        }
    }
    for (auto node = list->Begin(); node != list->End(); node = node->next_) {
        AdapterFree(node->value_);
    }
    if (!list->IsEmpty()) {
        delete list;
        return false;
    }

    delete list;
    return true;
}

bool BundleUtil::RenameDir(const char *oldDir, const char *newDir)
{
    if (oldDir == nullptr || newDir == nullptr) {
        return false;
    }

    if (IsDir(newDir) && !RemoveDir(newDir)) {
        return false;
    }

    if (frename(oldDir, newDir) != 0) {
        return false;
    }
    return true;
}

bool BundleUtil::RenameFile(const char *oldFile, const char *newFile)
{
    if (oldFile == nullptr || newFile == nullptr) {
        return false;
    }

    if (IsFile(newFile) && unlink(newFile) < 0) {
        return false;
    }

    if (frename(oldFile, newFile) != 0) {
        return false;
    }
    return true;
}

char *BundleUtil::GetRootDir(const char *dir, int32_t index)
{
    char *rootDir = reinterpret_cast<char *>(AdapterMalloc((index + 1) * sizeof(char)));
    if (rootDir == nullptr) {
        return nullptr;
    }
    errno_t err = strncpy_s(rootDir, index + 1, dir, index);
    if (err != EOK) {
        AdapterFree(rootDir);
        return nullptr;
    }
    return rootDir;
}

bool BundleUtil::CheckDirIsEmpty(const char *dirPath, List<char *>* list)
{
    DIR *dir = nullptr;
    if ((dir = opendir(dirPath)) == nullptr) {
        return false;
    }
    bool isEmptyDir = true;
    dirent *dp = nullptr;
    while ((dp = readdir(dir)) != nullptr) {
        if ((strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..")) == 0) {
            continue;
        }

        int32_t pathSize = strlen(dirPath) + strlen(dp->d_name) + strlen(PATH_SEPARATOR);
        char *filePath = reinterpret_cast<char *>(AdapterMalloc((pathSize + 1) * sizeof(char)));
        if (filePath == nullptr ||
            sprintf_s(filePath, pathSize + 1, "%s%s%s", dirPath, PATH_SEPARATOR, dp->d_name) < 0) {
            AdapterFree(filePath);
            continue;
        }

        if (IsDir(filePath)) {
            list->PushFront(filePath);
            isEmptyDir = false;
        } else {
            (void) unlink(filePath);
            AdapterFree(filePath);
        }
    }
    closedir(dir);
    return isEmptyDir;
}

bool BundleUtil::StoreJsonContentToFile(const char *packageJson, const cJSON *object)
{
    if (object == nullptr) {
        return false;
    }

    char *out = cJSON_Print(object);
    if (out == nullptr) {
        return false;
    }

    if (!CheckRealPath(packageJson)) {
        free(out);
        return false;
    }

    if (IsFile(packageJson) && unlink(packageJson) < 0) {
        free(out);
        return false;
    }

    int32_t fp = open(packageJson, O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
    if (fp < 0) {
        free(out);
        return false;
    }

    if (write(fp, out, strlen(out)) != strlen(out)) {
        free(out);
        close(fp);
        return false;
    }

    free(out);
    close(fp);
    return true;
}

void BundleUtil::FreeStrArrayMemory(char **pointer, uint32_t len)
{
    if (len != 0 && pointer != nullptr) {
        for (uint32_t i = 0; i < len; i++) {
            AdapterFree(*(pointer + i));
        }
        AdapterFree(pointer);
    }
}
#endif
} // namespace OHOS