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

#ifndef OHOS_BUNDLE_UTIL_H
#define OHOS_BUNDLE_UTIL_H

#include "bundle_common.h"
#include "bundle_info.h"
#include "utils_list.h"
#include "stdint.h"
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
#include <string>
#include <vector>
#endif
#include "cJSON.h"

namespace OHOS {
class BundleUtil {
public:
    static bool CheckRealPath(const char *path);
    static bool IsFile(const char *path);
    static bool IsDir(const char *path);
    static bool EndWith(const char *str, const char *subStr);
    static bool StartWith(const char *str, const char *subStr);
    static cJSON *GetJsonStream(const char *path);
    static uint32_t GetFileSize(const char *filePath);
    static cJSON *ConvertInstallRecordToJson(const InstallRecord &installRecord);
    static char *GetValueFromBundleJson(const char *bundleName, const char *key);
    static int32_t GetValueFromBundleJson(const char *bundleName, const char *key, int32_t defaultValue);
    static bool IsDigitStr(const char *str);
    static void DeleteJsonFile(const char *bundleName);
    static bool CheckBundleJsonIsValid(const char *bundleName, char **codePath, char **appId, int32_t &versionCode);
    static char *Strscat(char *str[], uint32_t len);
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    static cJSON *ConvertUidAndGidToJson(const InstallRecord &installRecord);
    static bool DeleteUidInfoFromJson(const char *bundleName);
#else
    static bool MkDirs(const char *dir);
    static bool RemoveDir(const char *dir);
    static bool RenameDir(const char *oldDir, const char *newDir);
    static bool RenameFile(const char *oldFile, const char *newFile);
    static bool StoreJsonContentToFile(const char *packageJson, const cJSON *object);
    static void FreeStrArrayMemory(char **pointer, uint32_t len);
#endif
private:
    BundleUtil() = default;
    ~BundleUtil() = default;

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    static cJSON *ObtainUidAndGidJson(bool flag);
    static bool AddUidAndGidInfo(const InstallRecord &installRecord, cJSON *size, cJSON *uids);
    static bool DeleteInnerUidInfoFromUidArray(const char *bundleName, cJSON *size, cJSON *uids);
#else
    static char *GetRootDir(const char *dir, int32_t index);
    static bool CheckDirIsEmpty(const char *dir, List<char *>* list);
#endif
}; // namespace OHOS
}
#endif // OHOS_BUNDLE_UTIL_H
