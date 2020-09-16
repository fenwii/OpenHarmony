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

#include "gt_bundle_manager_service.h"

#include "ability_info_utils.h"
#include "ability_message_id.h"
#include "appexecfwk_errors.h"
#include "bundle_message_id.h"
#include "bundle_util.h"
#include "gt_bundle_extractor.h"
#include "gt_bundle_parser.h"
#include "gt_extractor_util.h"
#include "mc_fs.h"
#include "utils.h"
#include "want.h"

namespace OHOS {
const int8_t BUNDLE_INFO_HEADER = 31;

GtManagerService::GtManagerService()
{
    installer_ = new GtBundleInstaller();
    bundleMap_ = BundleMap::GetInstance();
}

GtManagerService::~GtManagerService()
{
    delete installer_;
    installer_ = nullptr;
}

void GtManagerService::ServiceMsgProcess(MC_MSG_S* msg)
{
    if (msg == nullptr || bundleSvcStop_) {
        return;
    }

    if (installer_ == nullptr) {
        installer_ = new GtBundleInstaller();
    }

    switch (msg->enId) {
        case BUNDLE_SERVICE_INITED: {
            ScanPackages();
            break;
        }
        case BUNDLE_UPDATED:
            /* Process update request by Install() */
        case BUNDLE_INSTALLED: {
            char *path = reinterpret_cast<char *>(msg->pMsgAllocBuf);
            char *name = strrchr(path, '/');
            if (name == nullptr) {
                break;
            }
            BundleOperationFunc cb = reinterpret_cast<BundleOperationFunc>(msg->msgValue);
            if (cb != nullptr) {
                (*cb)(PACKAGE_ADD_DOING, name + 1, ERR_OK);
                HILOG_INFO(HILOG_MODULE_AAFWK, "[BMS] begin to Install");
                uint8_t bResult = installer_->Install(path);
                if (bResult == ERR_OK) {
                    (*cb)(PACKAGE_ADD_OK, name + 1, ERR_OK);
                    HILOG_INFO(HILOG_MODULE_AAFWK, "[BMS] Install Success");
                } else {
                    (*cb)(PACKAGE_ADD_FAILED, name + 1, bResult);
                    HILOG_ERROR(HILOG_MODULE_AAFWK, "[BMS] Install failed, ret: %u", bResult);
                }
            }
            (void) unlink(path);
            break;
        }
        case BUNDLE_UNINSTALLED: {
            char *bundleName = reinterpret_cast<char *>(msg->pMsgAllocBuf);
            BundleOperationFunc cb = reinterpret_cast<BundleOperationFunc>(msg->msgValue);
            if (cb != nullptr) {
                (*cb)(PACKAGE_REMOVE_DOING, bundleName, ERR_OK);
            }
            HILOG_INFO(HILOG_MODULE_AAFWK, "[BMS] begin to Uninstall");
            uint8_t bResult = installer_->Uninstall(bundleName);
            if (cb != nullptr) {
                if (bResult == ERR_OK) {
                    (*cb)(PACKAGE_REMOVE_OK, bundleName, ERR_OK);
                    HILOG_INFO(HILOG_MODULE_AAFWK, "[BMS] Uninstall Success");
                } else {
                    (*cb)(PACKAGE_REMOVE_FAILED, bundleName, bResult);
                    HILOG_ERROR(HILOG_MODULE_AAFWK, "[BMS] Uninstall failed, ret: %u", bResult);
                }
            }
            break;
        }
        case MC_PROP_DM_FACTORY_RESET: {
            BundleFactoryReset();
            break;
        }
        default: {
            break;
        }
    }
}

void GtManagerService::InstallAllSystemBundle(uint8_t scanFlag)
{
    DIR *dir = nullptr;
    dirent *ent = nullptr;

    dir = (scanFlag == SYSTEM_APP_FLAG) ? opendir(SYSTEM_BUNDLE_PATH) : opendir(THIRD_SYSTEM_BUNDLE_PATH);
    if (dir == nullptr) {
        return;
    }

    while ((ent = readdir(dir)) != nullptr) {
        if ((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..")) == 0) {
            continue;
        }
        if (scanFlag == SYSTEM_APP_FLAG) {
            InstallSystemBundle(SYSTEM_BUNDLE_PATH, ent->d_name);
        } else {
            InstallSystemBundle(THIRD_SYSTEM_BUNDLE_PATH, ent->d_name);
        }
    }
    closedir(dir);
}

void GtManagerService::InstallSystemBundle(const char *fileDir, const char *fileName)
{
    if (installer_ == nullptr) {
        return;
    }

    char *bundlePathComp[] = {
        const_cast<char *>(fileDir), const_cast<char *>(PATH_SEPARATOR), const_cast<char *>(fileName)
    };
    char *systemAppPath = BundleUtil::Strscat(bundlePathComp, sizeof(bundlePathComp) / sizeof(char *));
    if (systemAppPath == nullptr) {
        return;
    }

    if (!BundleUtil::IsFile(systemAppPath) || !BundleUtil::EndWith(systemAppPath, INSTALL_FILE_SUFFIX)) {
        AdapterFree(systemAppPath);
        return;
    }

    installer_->Install(systemAppPath);
    AdapterFree(systemAppPath);
}

void GtManagerService::ScanPackages()
{
    if (!BundleUtil::IsDir(JSON_PATH)) {
        BundleUtil::MkDirs(JSON_PATH);
        InstallAllSystemBundle(SYSTEM_APP_FLAG);
        InstallAllSystemBundle(THIRD_SYSTEM_APP_FLAG);
        return;
    }

    // get third system bundle uninstall record
    cJSON *uninstallRecord = BundleUtil::GetJsonStream(UNINSTALL_THIRD_SYSTEM_BUNDLE_JSON);
    if (uninstallRecord == nullptr) {
        (void) unlink(UNINSTALL_THIRD_SYSTEM_BUNDLE_JSON);
    }

    // scan system apps
    ScanAppDir(SYSTEM_BUNDLE_PATH, nullptr, SYSTEM_APP_FLAG, true);
    // scan third system apps
    ScanAppDir(THIRD_SYSTEM_BUNDLE_PATH, uninstallRecord, THIRD_SYSTEM_APP_FLAG, false);
    if (uninstallRecord != nullptr) {
        cJSON_Delete(uninstallRecord);
    }
    // scan third apps
    ScanAppDir(INSTALL_PATH, nullptr, THIRD_APP_FLAG, false);
}

void GtManagerService::ScanAppDir(const char *appDir, const cJSON *uninstallRecord, uint8_t scanFlag, bool isSystemApp)
{
    dirent *ent = nullptr;
    char *bundleName = nullptr;
    int32_t versionCode = -1;

    if (appDir == nullptr) {
        return;
    }

    DIR *dir = opendir(appDir);
    if (dir == nullptr) {
        return;
    }
    while ((ent = readdir(dir)) != nullptr) {
        if ((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..")) == 0) {
            continue;
        }
        char *appPathComp[] = {const_cast<char *>(appDir), const_cast<char *>(PATH_SEPARATOR), ent->d_name};
        char *appPath = BundleUtil::Strscat(appPathComp, sizeof(appPathComp) / sizeof(char *));
        if (appPath == nullptr) {
            break;
        }

        if (scanFlag == THIRD_APP_FLAG) {
            if (!BundleUtil::IsDir(appPath)) {
                AdapterFree(appPath);
                continue;
            }
            ReloadEntireBundleInfo(appPath, ent->d_name, versionCode, isSystemApp);
            AdapterFree(appPath);
            continue;
        }
        // scan system app
        bool res = CheckSystemBundleIsValid(appPath, &bundleName, versionCode);
        if (!res) {
            AdapterFree(appPath);
            AdapterFree(bundleName);
            continue;
        }

        if (scanFlag == THIRD_SYSTEM_APP_FLAG &&
            CheckThirdSystemBundleHasUninstalled(bundleName, uninstallRecord)) {
            AdapterFree(appPath);
            AdapterFree(bundleName);
            continue;
        }

        ReloadEntireBundleInfo(appPath, bundleName, versionCode, isSystemApp);
        AdapterFree(appPath);
        AdapterFree(bundleName);
    }
    closedir(dir);
}

bool GtManagerService::CheckSystemBundleIsValid(const char *appPath, char **bundleName, int32_t &versionCode)
{
    if (appPath == nullptr || bundleName == nullptr) {
        return false;
    }

    if (!BundleUtil::IsFile(appPath) || !BundleUtil::EndWith(appPath, INSTALL_FILE_SUFFIX)) {
        return false;
    }

    if (!GtBundleParser::ParseBundleAttr(appPath, bundleName, versionCode)) {
        return false;
    }

    if (*bundleName != nullptr && strlen(*bundleName) >= MAX_BUNDLE_NAME_LEN) {
        return false;
    }
    return true;
}

void GtManagerService::ReloadEntireBundleInfo(const char *appPath, const char *bundleName, int32_t versionCode,
    bool isSystemApp)
{
    char *codePath = nullptr;
    char *appId = nullptr;
    int32_t oldVersionCode = -1;

    if (installer_ == nullptr || appPath == nullptr || bundleName == nullptr) {
        return;
    }

    if (QueryBundleInfo(bundleName) != nullptr) {
        return;
    }

    if (BundleUtil::IsFile(appPath) && !CheckBundleHasInstalled(bundleName)) {
        installer_->Install(appPath);
        return;
    }

    if (BundleUtil::EndWith(appPath, TMP_SUFFIX)) {
        BundleUtil::RemoveDir(appPath);
        return;
    }

    bool res = BundleUtil::CheckBundleJsonIsValid(bundleName, &codePath, &appId, oldVersionCode);
    AdapterFree(appId);
    if (BundleUtil::IsFile(appPath)) {
        if (!res) {
            installer_->Install(appPath);
            AdapterFree(codePath);
            return;
        }
        if (oldVersionCode < versionCode) {
            ReloadBundleInfo(codePath, isSystemApp);
            installer_->Install(appPath);
            AdapterFree(codePath);
            return;
        }
    } else {
        if (!res) {
            BundleUtil::RemoveDir(appPath);
            AdapterFree(codePath);
            return;
        }
    }
    ReloadBundleInfo(codePath, isSystemApp);
    AdapterFree(codePath);
}

void GtManagerService::ReloadBundleInfo(const char *profileDir, bool isSystemApp)
{
    if (profileDir == nullptr) {
        return;
    }
    BundleInfo *bundleInfo = GtBundleParser::ParseHapProfile(profileDir);
    if (bundleInfo != nullptr) {
        HILOG_ERROR(HILOG_MODULE_AAFWK, "[BMS] reload bundle info fail!, isSystemApp is %d", isSystemApp);
        bundleInfo->isSystemApp = isSystemApp;
        bundleMap_->Add(bundleInfo);
        return;
    }
    BundleUtil::RemoveDir(profileDir);
}

bool GtManagerService::CheckBundleHasInstalled(const char *bundleName)
{
    if (bundleName == nullptr) {
        return false;
    }
    int32_t fileNameSize = strlen(bundleName) + strlen(JSON_SUFFIX);
    char *fileName = reinterpret_cast<char *>(AdapterMalloc((fileNameSize + 1) * sizeof(char)));
    if (fileName == nullptr) {
        return false;
    }

    if (sprintf_s(fileName, fileNameSize + 1, "%s%s", bundleName, JSON_SUFFIX) < 0) {
        AdapterFree(fileName);
        return false;
    }

    dirent *ent = nullptr;
    DIR *dir = opendir(JSON_PATH);
    if (dir == nullptr) {
        AdapterFree(fileName);
        return false;
    }
    while ((ent = readdir(dir)) != nullptr) {
        if ((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..")) == 0) {
            continue;
        }
        if (strcmp(fileName, ent->d_name) == 0) {
            AdapterFree(fileName);
            closedir(dir);
            return true;
        }
    }
    AdapterFree(fileName);
    closedir(dir);
    return false;
}

bool GtManagerService::CheckThirdSystemBundleHasUninstalled(const char *bundleName, const cJSON *object)
{
    if (object == nullptr || bundleName == nullptr) {
        return false;
    }

    cJSON *array = cJSON_GetObjectItem(object, JSON_MAIN_KEY);
    if (!cJSON_IsArray(array)) {
        return false;
    }

    int32_t size = cJSON_GetArraySize(array);
    for (int32_t i = 0; i < size; i++) {
        cJSON *item = cJSON_GetArrayItem(array, i);
        if (!cJSON_IsString(item)) {
            return false;
        }
        if ((item->valuestring != nullptr) && strcmp(bundleName, item->valuestring) == 0) {
            return true;
        }
    }
    return false;
}

BundleInfo *GtManagerService::QueryBundleInfo(const char *bundleName)
{
    if (bundleName == nullptr || bundleMap_ == nullptr) {
        return nullptr;
    }
    return bundleMap_->Get(bundleName);
}

void GtManagerService::RemoveBundleInfo(const char *bundleName)
{
    if (bundleName == nullptr || bundleMap_ == nullptr) {
        return;
    }
    bundleMap_->Erase(bundleName);
}

void GtManagerService::AddBundleInfo(BundleInfo *info)
{
    if (info == nullptr || info->bundleName == nullptr || bundleMap_ == nullptr) {
        return;
    }
    bundleMap_->Add(info);
}

uint8_t GtManagerService::GetBundleInfo(const char *bundleName, int32_t flags, BundleInfo& bundleInfo)
{
    if (bundleMap_ == nullptr) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    return bundleMap_->GetBundleInfo(bundleName, flags, bundleInfo);
}

uint8_t GtManagerService::GetBundleInfos(int32_t flags, BundleInfo **bundleInfos, int32_t *len)
{
    if (bundleMap_ == nullptr) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    return bundleMap_->GetBundleInfos(flags, bundleInfos, len);
}

char *GtManagerService::GetAppIdByBundleName(const char *bundleName)
{
    if (bundleName == nullptr) {
        return nullptr;
    }
    BundleInfo bundleInfo;
    if (GetBundleInfo(bundleName, 0, bundleInfo) != ERR_OK) {
        return nullptr;
    }
    return BundleUtil::GetValueFromBundleJson(bundleName, JSON_SUB_KEY_APPID);
}

uint32_t GtManagerService::GetVersionCodeByBundlePath(const char *path, unsigned char *versionCode, uint8_t length)
{
    if (!BundleUtil::IsFile(path) || versionCode == nullptr || length == 0) {
        return 0;
    }

    char *bundleName = nullptr;
    int32_t code = -1;
    if (!GtBundleParser::ParseBundleAttr(path, &bundleName, code)) {
        AdapterFree(bundleName);
        return 0;
    }
    AdapterFree(bundleName);
    // convert number to char
    uint8_t versionCodeLen = 0;
    while (code != 0) {
        if (versionCodeLen == length - 1) {
            return 0;
        }
        versionCode[versionCodeLen++] = code % NUMBER_TEN + ZERO_ASCII_NUM;
        code /= NUMBER_TEN;
    }
    versionCode[versionCodeLen] = '\0';
    // pre-post conversion
    for (uint8_t j = 0; j < versionCodeLen / NUMBER_TWO; j++) {
        versionCode[j] = versionCode[j] + versionCode[versionCodeLen - 1 - j];
        versionCode[versionCodeLen - 1 - j] = versionCode[j] - versionCode[versionCodeLen - 1 - j];
        versionCode[j] = versionCode[j] - versionCode[versionCodeLen - 1 - j];
    }
    return versionCodeLen;
}

uint8_t GtManagerService::DumpBundleInfos(char **bundles)
{
    int32_t len = 0;
    BundleInfo *bundleInfos = nullptr;
    uint8_t retCode = bundleMap_->GetBundleInfos(0, &bundleInfos, &len);
    if (retCode != ERR_OK) {
        if (bundleInfos != nullptr) {
            ClearBundleInfos(bundleInfos, len);
            bundleInfos = nullptr;
        }
        return ERR_APPEXECFWK_DUMP_ERROR;
    }

    int32_t bundleInfoSize = 1;
    for (int32_t i = 0; i < len; i++) {
        if (bundleInfos[i].bundleName == nullptr ||
            bundleInfos[i].label == nullptr || bundleInfos[i].versionName == nullptr) {
            ClearBundleInfos(bundleInfos, len);
            bundleInfos = nullptr;
            return ERR_APPEXECFWK_DUMP_ERROR;
        }
        bundleInfoSize += strlen(bundleInfos[i].bundleName) +
            strlen(bundleInfos[i].label) + strlen(bundleInfos[i].versionName) + BUNDLE_INFO_HEADER;
    }

    *bundles = reinterpret_cast<char *>(AdapterMalloc(bundleInfoSize));
    if (*bundles == nullptr) {
        ClearBundleInfos(bundleInfos, len);
        bundleInfos = nullptr;
        return ERR_APPEXECFWK_DUMP_ERROR;
    }
    (*bundles)[0] = '\0';
    for (int32_t i = 0; i < len; i++) {
        int32_t res = sprintf_s((*bundles) + strlen(*bundles), bundleInfoSize - strlen(*bundles),
            "bundleName:%s,name:%s,versionName:%s;",
            bundleInfos[i].bundleName, bundleInfos[i].label, bundleInfos[i].versionName);
        if (res < 0) {
            AdapterFree(*bundles);
            ClearBundleInfos(bundleInfos, len);
            bundleInfos = nullptr;
            return ERR_APPEXECFWK_DUMP_ERROR;
        }
    }

    ClearBundleInfos(bundleInfos, len);
    bundleInfos = nullptr;
    return ERR_OK;
}

void GtManagerService::ClearBundleInfos(BundleInfo *bundleInfos, int32_t len)
{
    if (bundleInfos == nullptr) {
        return;
    }
    for (int32_t i = 0; i < len; i++) {
        ClearBundleInfo(&bundleInfos[i]);
    }
    AdapterFree(bundleInfos);
}

void GtManagerService::SendBundleListChangedToLauncher(BundleState state, const char *bundleName)
{
    if (bundleName == nullptr) {
        return;
    }
    char *innerBundleName = reinterpret_cast<char *>(SvrMalloc(strlen(bundleName) + 1));
    if (innerBundleName == nullptr) {
        return;
    }
    if (strncpy_s(innerBundleName, strlen(bundleName) + 1, bundleName, strlen(bundleName)) != EOK) {
        SvrFree(innerBundleName);
        return;
    }
    if (AdapterSend((MC_MSG_ID_E) BUNDLE_LIST_CHANGED, state, reinterpret_cast<void *>(innerBundleName)) != MC_TRUE) {
        SvrFree(innerBundleName);
    }
}

void GtManagerService::BundleFactoryReset()
{
    bundleSvcStop_ = true;
    // reply bundle factory reset result
    AdapterSend(MC_PROP_DM_FACTORY_RESET_DONE, (MC_U32)(MC_MAIL_ABILITY_BUNDLE_MANAGER), nullptr);
}
} // namespace OHOS

extern "C" {
void BUNDLE_ServiceTaskInit(void)
{
    (void) AdapterSend((MC_MSG_ID_E) BUNDLE_SERVICE_INITED, 0, nullptr);
}

void BUNDLE_ServiceMsgProcess(MC_MSG_S *msg)
{
    OHOS::GtManagerService::GetInstance().ServiceMsgProcess(msg);
}

uint8_t DumpBundleInfos(char **bundles)
{
    return OHOS::GtManagerService::GetInstance().DumpBundleInfos(bundles);
}

int32_t Install(const char *hapPath, BundleOperationFunc cb)
{
    if (hapPath == nullptr) {
        return -1;
    }
    char *path = reinterpret_cast<char *>(SvrMalloc(strlen(hapPath) + 1));
    if (path == nullptr) {
        return -1;
    }
    if (strncpy_s(path, strlen(hapPath) + 1, hapPath, strlen(hapPath)) != EOK) {
        SvrFree(path);
        return -1;
    }

    uint32_t value = reinterpret_cast<uint32_t>(cb);
    if (AdapterSend((MC_MSG_ID_E) BUNDLE_INSTALLED, value, reinterpret_cast<void *>(path)) != MC_TRUE) {
        SvrFree(path);
        return -1;
    }
    return 0;
}

int32_t Uninstall(const char *bundleName, BundleOperationFunc cb)
{
    if (bundleName == nullptr) {
        return -1;
    }
    char *innerBundleName = reinterpret_cast<char *>(SvrMalloc(strlen(bundleName) + 1));
    if (innerBundleName == nullptr) {
        return -1;
    }
    if (strncpy_s(innerBundleName, strlen(bundleName) + 1, bundleName, strlen(bundleName)) != EOK) {
        SvrFree(innerBundleName);
        return -1;
    }

    uint32_t value = reinterpret_cast<uint32_t>(cb);
    if (AdapterSend((MC_MSG_ID_E) BUNDLE_UNINSTALLED, value, reinterpret_cast<void *>(innerBundleName)) != MC_TRUE) {
        SvrFree(innerBundleName);
        return -1;
    }
    return 0;
}

void QueryAbilityInfo(Want want, AbilityInfo *abilityInfo)
{
    if (want.element == nullptr) {
        return;
    }
    const char *bundleName = want.element->bundleName;
    BundleInfo *bundleInfo = OHOS::GtManagerService::GetInstance().QueryBundleInfo(bundleName);
    if (bundleInfo == nullptr) {
        return;
    }
    AbilityInfo *ability = bundleInfo->abilityInfo;
    if (ability == nullptr) {
        return;
    }
    OHOS::AbilityInfoUtils::SetAbilityInfoBundleName(abilityInfo, bundleName);
    OHOS::AbilityInfoUtils::SetAbilityInfoSrcPath(abilityInfo, ability->srcPath);
}

uint8_t GetBundleInfo(const char *bundleName, int32_t flags, BundleInfo *bundleInfo)
{
    return OHOS::GtManagerService::GetInstance().GetBundleInfo(bundleName, flags, *bundleInfo);
}

uint8_t GetBundleInfos(const int32_t flags, BundleInfo **bundleInfos, int32_t *len)
{
    return OHOS::GtManagerService::GetInstance().GetBundleInfos(flags, bundleInfos, len);
}

char *GetAppIdByBundleName(const char *bundleName)
{
    return OHOS::GtManagerService::GetInstance().GetAppIdByBundleName(bundleName);
}

uint32_t GetVersionCodeByBundlePath(const char *path, unsigned char *versionCode, uint8_t length)
{
    return OHOS::GtManagerService::GetInstance().GetVersionCodeByBundlePath(path, versionCode, length);
}
}
