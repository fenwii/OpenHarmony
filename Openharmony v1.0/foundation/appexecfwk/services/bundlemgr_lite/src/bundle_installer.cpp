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

#include "bundle_installer.h"

#include <climits>
#include <sys/stat.h>
#include <unistd.h>

#include "adapter.h"
#include "appexecfwk_errors.h"
#include "bundle_daemon_client.h"
#include "bundle_extractor.h"
#include "bundle_info_utils.h"
#include "bundle_manager_service.h"
#include "bundle_parser.h"
#include "bundle_res_transform.h"
#include "bundle_util.h"
#include "log.h"
#include "utils.h"

namespace OHOS {
const char MATCHED_ALL_STR[] = ".*";
const char DELIMITER[] = "_";
#ifdef OHOS_DEBUG
const char APPID[] = "appId";
#endif

BundleInstaller::BundleInstaller(const std::string &codeDirPath, const std::string &dataDirPath)
{
    HILOG_INFO(HILOG_MODULE_APP, "create BundleInstaller instance!");
    codeDirPath_ = codeDirPath;
    dataDirPath_ = dataDirPath;
}

BundleInstaller::~BundleInstaller()
{
    HILOG_INFO(HILOG_MODULE_APP, "destroy BundleInstaller instance!");
    codeDirPath_.clear();
    dataDirPath_.clear();
}

std::string BundleInstaller::GetCodeDirPath() const
{
    return codeDirPath_;
}

std::string BundleInstaller::GetDataDirPath() const
{
    return dataDirPath_;
}

void BundleInstaller::ModifyInstallDirByHapType(uint8_t hapType)
{
    if (hapType != THIRD_APP_FLAG) {
        dataDirPath_ = DATA_PATH;
        codeDirPath_ = INSTALL_PATH;
    } else if (ManagerService::GetInstance().IsExternalInstallMode()) {
        dataDirPath_ = EXTEANAL_DATA_PATH;
        codeDirPath_ = EXTEANAL_INSTALL_PATH;
    } else {
        dataDirPath_ = DATA_PATH;
        codeDirPath_ = INSTALL_PATH;
    }
}

uint8_t BundleInstaller::GetHapType(const char *path)
{
    uint8_t hapType = 0;
    if (BundleUtil::StartWith(path, SYSTEM_BUNDLE_PATH)) {
        hapType = SYSTEM_APP_FLAG;
    } else if (BundleUtil::StartWith(path, THIRD_SYSTEM_BUNDLE_PATH)) {
        hapType = THIRD_SYSTEM_APP_FLAG;
    } else {
        hapType = THIRD_APP_FLAG;
    }
    return hapType;
}

uint8_t BundleInstaller::Install(const char *path)
{
    if (path == nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARAM_ERROR;
    }

    if (strlen(path) > PATH_MAX) {
        return ERR_APPEXECFWK_INSTALL_FAILED_FILE_PATH_INVALID;
    }

    char realPath[PATH_MAX + 1] = { 0 };
    if (realpath(path, realPath) == nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_FILE_PATH_INVALID;
    }

    // set codeDirPath_ and dataDirPath_ according to hap path
    uint8_t hapType = GetHapType(realPath);
    ModifyInstallDirByHapType(hapType);

    InstallRecord installRecord = {
        .bundleName = nullptr, .codePath = nullptr, .appId = nullptr, .versionCode = -1, .uid = INVALID_UID,
        .gid = INVALID_GID
    };

    uint8_t errorCode = ProcessBundleInstall(realPath, installRecord, hapType);
    if (errorCode != ERR_OK) {
        ManagerService::GetInstance().RecycleUid(installRecord.bundleName);
        return errorCode;
    }

    std::string uidTmpJsonPath = std::string(JSON_PATH) + PATH_SEPARATOR + UID_GID_MAP + TMP_SUFFIX + JSON_SUFFIX;
    if (!BackUpUidAndGidInfo(installRecord, uidTmpJsonPath.c_str())) {
        HILOG_ERROR(HILOG_MODULE_APP, "backup uid and gid info fail!");
        BundleInfo *bundleInfo = ManagerService::GetInstance().QueryBundleInfo(installRecord.bundleName);
        CLEAR_INSTALL_ENV(bundleInfo);
        return ERR_APPEXECFWK_INSTALL_FAILED_UID_AND_GID_BACKUP_ERROR;
    }

    if (!RenameJsonFile(UID_GID_MAP) || !RenameJsonFile(installRecord.bundleName)) {
        HILOG_ERROR(HILOG_MODULE_APP, "rename uid_gid_map json or record json fail!");
        BundleInfo *bundleInfo = ManagerService::GetInstance().QueryBundleInfo(installRecord.bundleName);
        CLEAR_INSTALL_ENV(bundleInfo);
        return ERR_APPEXECFWK_INSTALL_FAILED_RENAME_FILE_ERROR;
    }

    // if third system bundle, it need to record bundleName in THIRD_SYSTEM_BUNDLE_JSON
    if (hapType == THIRD_SYSTEM_APP_FLAG && !CheckIsThirdSystemBundle(installRecord.bundleName)) {
        RecordThirdSystemBundle(installRecord.bundleName, THIRD_SYSTEM_BUNDLE_JSON);
    }
    return ERR_OK;
}

uint8_t BundleInstaller::ProcessBundleInstall(const std::string &path, InstallRecord &installRecord,
    uint8_t hapType)
{
    BundleInfo *bundleInfo = nullptr;
    Permissions permissions = {.permNum = 0, .permissionTrans = nullptr};
    BundleRes bundleRes = {.moduleDescriptionId = 0, .abilityRes = nullptr, .totalNumOfAbilityRes = 0};
    // check path
    uint8_t errorCode = CheckInstallFileIsValid(const_cast<char *>(path.c_str()));
    CHECK_PRO_RESULT(errorCode, bundleInfo, permissions, bundleRes.abilityRes);
#ifndef __LINUX__
    // verify signature
    SignatureInfo signatureInfo;
#ifdef OHOS_DEBUG
    if (ManagerService::GetInstance().IsSignMode()) {
        errorCode = HapSignVerify::VerifySignature(path, signatureInfo);
        CHECK_PRO_RESULT(errorCode, bundleInfo, permissions, bundleRes.abilityRes);
    }
#else
    errorCode = HapSignVerify::VerifySignature(path, signatureInfo);
    CHECK_PRO_RESULT(errorCode, bundleInfo, permissions, bundleRes.abilityRes);
#endif
#endif
    // parse config.json
    BundleParser bundleParser;
    errorCode = bundleParser.ParseHapProfile(path, permissions, bundleRes, &bundleInfo);
    CHECK_PRO_RESULT(errorCode, bundleInfo, permissions, bundleRes.abilityRes);
#ifndef __LINUX__
#ifdef OHOS_DEBUG
    // check signatureInfo
    if (ManagerService::GetInstance().IsSignMode()) {
        errorCode = CheckProvisionInfoIsValid(signatureInfo, permissions, bundleInfo->bundleName);
        CHECK_PRO_RESULT(errorCode, bundleInfo, permissions, bundleRes.abilityRes);
        // check version and signature when in update status
        size_t index = signatureInfo.appId.find_first_of(DELIMITER);
        errorCode = (index != std::string::npos) ? ERR_OK : ERR_APPEXECFWK_INSTALL_FAILED_INVALID_PROVISIONINFO;
        CHECK_PRO_RESULT(errorCode, bundleInfo, permissions, bundleRes.abilityRes);
        signatureInfo.appId = signatureInfo.appId.replace(signatureInfo.appId.begin(), signatureInfo.appId.begin() +
            index, bundleInfo->bundleName);
        bundleInfo->appId = Utils::Strdup(signatureInfo.appId.c_str());
    } else {
        bundleInfo->appId = Utils::Strdup(APPID);
    }
#else
    errorCode = CheckProvisionInfoIsValid(signatureInfo, permissions, bundleInfo->bundleName);
    CHECK_PRO_RESULT(errorCode, bundleInfo, permissions, bundleRes.abilityRes);
    // check version and signature when in update status
    size_t index = signatureInfo.appId.find_first_of(DELIMITER);
    errorCode = (index != std::string::npos) ? ERR_OK : ERR_APPEXECFWK_INSTALL_FAILED_INVALID_PROVISIONINFO;
    CHECK_PRO_RESULT(errorCode, bundleInfo, permissions, bundleRes.abilityRes);
    signatureInfo.appId = signatureInfo.appId.replace(signatureInfo.appId.begin(), signatureInfo.appId.begin() +
        index, bundleInfo->bundleName);
    bundleInfo->appId = Utils::Strdup(signatureInfo.appId.c_str());
#endif
    errorCode = (bundleInfo->appId == nullptr) ? ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR : ERR_OK;
    CHECK_PRO_RESULT(errorCode, bundleInfo, permissions, bundleRes.abilityRes);
#endif
    installRecord.bundleName = bundleInfo->bundleName;
#ifndef __LINUX__
    installRecord.appId = bundleInfo->appId;
#endif
    installRecord.versionCode = bundleInfo->versionCode;
    errorCode = CheckVersionAndSignature(installRecord.bundleName, bundleInfo);
    CHECK_PRO_RESULT(errorCode, bundleInfo, permissions, bundleRes.abilityRes);
    std::string codePath = std::string(bundleInfo->codePath) + PATH_SEPARATOR + bundleInfo->moduleInfos[0].moduleName;
    installRecord.codePath = bundleInfo->codePath;
    // unzip bundle
    std::string tmpCodePath = codePath + TMP_SUFFIX;
    errorCode = (BundleDaemonClient::GetInstance().ExtractHap(path.c_str(), tmpCodePath.c_str()) == EC_SUCCESS) ?
        ERR_OK : ERR_APPEXECFWK_INSTALL_FAILED_EXTRACT_HAP_ERROR;
    CHECK_PRO_ROLLBACK(errorCode, permissions, bundleInfo, bundleRes.abilityRes);
    // rename install path and record install infomation
    bool isUpdate = ManagerService::GetInstance().QueryBundleInfo(installRecord.bundleName) != nullptr;
    errorCode = HandleFileAndBackUpRecord(tmpCodePath.c_str(), codePath.c_str(), installRecord, isUpdate, hapType);
    CHECK_PRO_ROLLBACK(errorCode, permissions, bundleInfo, bundleRes.abilityRes);
    bundleInfo->uid = installRecord.uid;
    bundleInfo->gid = installRecord.uid;
    // store permissions
    errorCode = StorePermissions(installRecord.bundleName, permissions.permissionTrans, permissions.permNum,
        isUpdate);
    CHECK_PRO_ROLLBACK(errorCode, permissions, bundleInfo, bundleRes.abilityRes);
    // update bundle Info
    errorCode = UpdateBundleInfo(installRecord.appId, bundleRes, bundleInfo, isUpdate, hapType);
    CHECK_PRO_ROLLBACK(errorCode, permissions, bundleInfo, bundleRes.abilityRes);
    // free permissions
    AdapterFree(permissions.permissionTrans);
    AdapterFree(bundleRes.abilityRes);
    return ERR_OK;
}

#ifndef __LINUX__
uint8_t BundleInstaller::CheckProvisionInfoIsValid(const SignatureInfo &signatureInfo, const Permissions &permissions,
    const char *bundleName)
{
    if (bundleName == nullptr || signatureInfo.provisionBundleName.empty()) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    if (!MatchBundleName(bundleName, signatureInfo.provisionBundleName.c_str())) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INVALID_PROVISIONINFO;
    }

    if (!MatchPermissions(signatureInfo.restrictedPermissions, permissions.permissionTrans, permissions.permNum)) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INVALID_PROVISIONINFO;
    }

    if (!MatchPermissions(signatureInfo.restrictedPermissions, permissions.permissionTrans, permissions.permNum)) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INVALID_PROVISIONINFO;
    }
    return ERR_OK;
}
#endif

bool BundleInstaller::MatchBundleName(const char *bundleName, const char *matchedBundleName)
{
    if (bundleName == nullptr || matchedBundleName == nullptr) {
        return false;
    }

    if (strcmp(matchedBundleName, MATCHED_ALL_STR) == 0 || strcmp(bundleName, matchedBundleName) == 0) {
        return true;
    }

    char *pos = const_cast<char *>(matchedBundleName);
    for (uint32_t i = 0; matchedBundleName[i] != '\0' && bundleName[i] != '\0'; i++, pos++) {
        if (bundleName[i] != matchedBundleName[i]) {
            if (strcmp(pos, MATCHED_ALL_STR) == 0) {
                return true;
            }
            HILOG_WARN(HILOG_MODULE_APP, "provisionBundleName is not match the bundleName!");
            return false;
        } else if (strcmp(pos, MATCHED_ALL_STR) == 0) {
            return true;
        }
    }
    HILOG_WARN(HILOG_MODULE_APP, "provisionBundleName is not match the bundleName!");
    return false;
}

bool BundleInstaller::MatchPermissions(const std::vector<std::string> & restrictedPermissions,
    PermissionTrans *permissionsTrans, int32_t permTransNum)
{
    if (permTransNum == 0) {
        return true;
    }

    if (permissionsTrans == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "permissionsTrans is nullptr!");
        return false;
    }

    std::vector<std::string> realRestrictedPermissions;
    for (int32_t i = 0; i < permTransNum; i++) {
        if (IsPermissionRestricted((permissionsTrans + i)->name) == 0) {
            realRestrictedPermissions.emplace_back(std::string((permissionsTrans + i)->name));
        }
    }

    if (realRestrictedPermissions.empty()) {
        HILOG_INFO(HILOG_MODULE_APP, "this app has no restricted permissions!");
        return true;
    }

    int32_t size = realRestrictedPermissions.size();
    for (int32_t i = 0; i < size; i++) {
        bool isMatched = false;
        for (const auto & restrictedPermission : restrictedPermissions) {
            if (realRestrictedPermissions[i] == restrictedPermission) {
                isMatched = true;
                break;
            }
        }
        if (!isMatched) {
            HILOG_WARN(HILOG_MODULE_APP, "provisionPermissions is not match the bundle reqPermissions!");
            return false;
        }
    }
    return true;
}

uint8_t BundleInstaller::HandleFileAndBackUpRecord(const char *tmpPath, const char *realPath, InstallRecord &record,
    bool isUpdate, uint8_t hapType)
{
    // get ams interface
    AmsInnerInterface *amsInterface = nullptr;
    if (tmpPath == nullptr || realPath == nullptr ||
        !ManagerService::GetAmsInterface(&amsInterface) || amsInterface == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "get ams interface fail when install!");
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }
    // kill app process
    amsInterface->TerminateApp(record.bundleName);

    if (BundleDaemonClient::GetInstance().RenameFile(tmpPath, realPath) != EC_SUCCESS) {
        ManagerService::GetInstance().RemoveBundleInfo(record.bundleName);
        return ERR_APPEXECFWK_INSTALL_FAILED_RENAME_DIR_ERROR;
    }

    if (!isUpdate) {
        // distribute uid for installing application
        record.uid = ManagerService::GetInstance().GenerateUid(record.bundleName, hapType);
        record.gid = record.uid;
        bool isChown = false;
        if ((record.uid != INVALID_UID) && (record.gid != INVALID_GID)) {
            isChown = true;
        }

        std::string dataPath = dataDirPath_ + PATH_SEPARATOR + record.bundleName;
        if (BundleDaemonClient::GetInstance().CreateDataDirectory(
            dataPath.c_str(), record.uid, record.gid, isChown) != EC_SUCCESS) {
            HILOG_ERROR(HILOG_MODULE_APP, "Create data directory fail");
            return ERR_APPEXECFWK_INSTALL_FAILED_CREATE_DATA_DIR_ERROR;
        }
    } else {
        BundleInfo *bundleInfo = ManagerService::GetInstance().QueryBundleInfo(record.bundleName);
        if (bundleInfo == nullptr) {
            return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
        }
        record.uid = bundleInfo->uid;
        record.gid = bundleInfo->gid;
    }
    std::string bundleTmpJsonPath = std::string(JSON_PATH) + PATH_SEPARATOR + record.bundleName + TMP_SUFFIX +
        JSON_SUFFIX;
    if (!BackUpInstallRecord(record, bundleTmpJsonPath.c_str())) {
        ManagerService::GetInstance().RemoveBundleInfo(record.bundleName);
        return ERR_APPEXECFWK_INSTALL_FAILED_RECORD_INFO_ERROR;
    }
    return ERR_OK;
}

uint8_t BundleInstaller::UpdateBundleInfo(const char *appId, const BundleRes &bundleRes, BundleInfo *bundleInfo,
    bool isUpdate, uint8_t hapType)
{
#ifndef __LINUX__
    if ((appId == nullptr) || (bundleInfo == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
#else
    if (bundleInfo == nullptr) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
#endif
    uint8_t errorCode = BundleResTransform::ConvertResInfoToBundleInfo(bundleInfo->codePath, bundleRes, bundleInfo);
    if (errorCode != ERR_OK) {
        return errorCode;
    }
    if (!isUpdate) {
        bundleInfo->isSystemApp = (hapType == SYSTEM_APP_FLAG);
    } else {
        BundleInfo *oldBundleInfo = ManagerService::GetInstance().QueryBundleInfo(bundleInfo->bundleName);
        if (oldBundleInfo == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "query bundleInfo which is exists fail!");
            return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
        }
        bundleInfo->isSystemApp = oldBundleInfo->isSystemApp;
        ManagerService::GetInstance().RemoveBundleInfo(bundleInfo->bundleName);
    }
    BundleInfoUtils::SetBundleInfoSharedLibPath(bundleInfo, ManagerService::GetInstance().GetSharedLibPath().c_str());
#ifndef __LINUX__
    bundleInfo->appId = Utils::Strdup(appId);
    if (bundleInfo->appId == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "add appId to bundleInfo fail!");
        ManagerService::GetInstance().RemoveBundleInfo(bundleInfo->bundleName);
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }
#endif
    ManagerService::GetInstance().AddBundleInfo(bundleInfo);
    return ERR_OK;
}

uint8_t BundleInstaller::Uninstall(const char *bundleName)
{
    if (bundleName == nullptr) {
        return ERR_APPEXECFWK_UNINSTALL_FAILED_PARAM_ERROR;
    }
    BundleInfo *bundleInfo = ManagerService::GetInstance().QueryBundleInfo(bundleName);
    if (bundleInfo == nullptr) {
        return ERR_APPEXECFWK_UNINSTALL_FAILED_BUNDLE_NOT_EXISTS;
    }

    if (bundleInfo->isSystemApp) {
        return ERR_APPEXECFWK_UNINSTALL_FAILED_BUNDLE_NOT_UNINSTALLABLE;
    }

    // get ams interface
    AmsInnerInterface *amsInterface = nullptr;
    if (!ManagerService::GetAmsInterface(&amsInterface) || amsInterface == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "get ams interface fail when uninstall!");
        return ERR_APPEXECFWK_UNINSTALL_FAILED_INTERNAL_ERROR;
    }
    // kill app process
    amsInterface->TerminateApp(bundleName);

    if (BundleDaemonClient::GetInstance().RemoveInstallDirectory(
        bundleInfo->codePath, bundleInfo->dataPath) != EC_SUCCESS) {
        ManagerService::GetInstance().RemoveBundleInfo(bundleName);
        return ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_DIRS_ERROR;
    }

    ManagerService::GetInstance().RemoveBundleInfo(bundleName);

    if (DeletePermissions(const_cast<char *>(bundleName)) < 0) {
        return ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_PERMISSIONS_ERROR;
    }

    // delete uid and gid info
    if (!BundleUtil::DeleteUidInfoFromJson(bundleName)) {
        return ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_UID_INFO_ERROR;
    }

    std::string bundleJsonPath = std::string(JSON_PATH) + PATH_SEPARATOR + bundleName + JSON_SUFFIX;
    if (BundleDaemonClient::GetInstance().RemoveFile(bundleJsonPath.c_str()) != EC_SUCCESS) {
        return ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_RECORD_INFO_ERROR;
    }

    if (CheckIsThirdSystemBundle(bundleName)) {
        RecordThirdSystemBundle(bundleName, UNINSTALL_THIRD_SYSTEM_BUNDLE_JSON);
    }
    return ERR_OK;
}

bool BundleInstaller::BackUpUidAndGidInfo(const InstallRecord &record, const char *jsonPath)
{
    if (jsonPath == nullptr) {
        return false;
    }
    cJSON *object = BundleUtil::ConvertUidAndGidToJson(record);
    if (object == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "BackUpUidAndGidInfo fail, object is null!");
        return false;
    }

    char *buffer = cJSON_Print(object);
    cJSON_Delete(object);
    if (buffer == nullptr) {
        return false;
    }
    if (BundleDaemonClient::GetInstance().StoreContentToFile(jsonPath, buffer, strlen(buffer) + 1) != EC_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_APP, "BackUpUidAndGidInfo fail, beacuse store JsonContent fail!");
        cJSON_free(buffer);
        return false;
    }
    cJSON_free(buffer);
    return true;
}

uint8_t BundleInstaller::CheckInstallFileIsValid(const char *path)
{
    if (path == nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARAM_ERROR;
    }

    if (!BundleUtil::EndWith(path, INSTALL_FILE_SUFFIX)) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INVALID_FILE_NAME;
    }

    if (!BundleUtil::IsFile(path)) {
        return ERR_APPEXECFWK_INSTALL_FAILED_FILE_NOT_EXISTS;
    }

    if (BundleUtil::GetFileSize(path) == 0) {
        return ERR_APPEXECFWK_INSTALL_FAILED_BAD_FILE;
    }
    return ERR_OK;
}

bool BundleInstaller::CheckIsThirdSystemBundle(const char *bundleName)
{
    if (bundleName == nullptr) {
        return false;
    }

    cJSON *root = BundleUtil::GetJsonStream(THIRD_SYSTEM_BUNDLE_JSON);
    if (root == nullptr) {
        return false;
    }

    cJSON *son = cJSON_GetObjectItem(root, JSON_MAIN_KEY);
    if (!cJSON_IsArray(son)) {
        BundleDaemonClient::GetInstance().RemoveFile(THIRD_SYSTEM_BUNDLE_JSON);
        cJSON_Delete(root);
        return false;
    }

    cJSON *item = nullptr;
    cJSON_ArrayForEach(item, son) {
        if (!cJSON_IsString(item)) {
            cJSON_Delete(root);
            return false;
        }
        if (item->valuestring != nullptr && strcmp(bundleName, item->valuestring) == 0) {
            cJSON_Delete(root);
            return true;
        }
    }
    cJSON_Delete(root);
    return false;
}

void BundleInstaller::RecordThirdSystemBundle(const char *bundleName, const char *path)
{
    if ((bundleName == nullptr) || (path == nullptr)) {
        return;
    }

    if (!BundleUtil::IsFile(path)) {
        InitThirdSystemBundleRecord(bundleName, path);
        return;
    }
    cJSON *root = BundleUtil::GetJsonStream(path);
    if (root == nullptr) {
        return;
    }

    cJSON *son = cJSON_GetObjectItem(root, JSON_MAIN_KEY);
    if (!cJSON_IsArray(son)) {
        BundleDaemonClient::GetInstance().RemoveFile(path);
        cJSON_Delete(root);
        InitThirdSystemBundleRecord(bundleName, path);
        return;
    }

    cJSON *str = cJSON_CreateString(bundleName);
    if (str == nullptr) {
        cJSON_Delete(root);
        return;
    }

    if (!cJSON_AddItemToArray(son, str)) {
        cJSON_Delete(str);
        cJSON_Delete(root);
        return;
    }

    char *buffer = cJSON_Print(root);
    cJSON_Delete(root);
    if (buffer == nullptr) {
        return;
    }

    if (BundleDaemonClient::GetInstance().StoreContentToFile(path, buffer, strlen(buffer) + 1) != EC_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_APP, "record third system bundle install info fail!");
    }
    cJSON_free(buffer);
}

void BundleInstaller::InitThirdSystemBundleRecord(const char *bundleName, const char *path)
{
    if (bundleName == nullptr || path == nullptr) {
        return;
    }

    cJSON *root = cJSON_CreateObject();
    if (root == nullptr) {
        return;
    }

    cJSON *son = cJSON_CreateArray();
    if (son == nullptr) {
        cJSON_Delete(root);
        return;
    }

    if (!cJSON_AddItemToObject(root, JSON_MAIN_KEY, son)) {
        cJSON_Delete(son);
        cJSON_Delete(root);
        return;
    }

    cJSON *str = cJSON_CreateString(bundleName);
    if (str == nullptr) {
        cJSON_Delete(root);
        return;
    }

    if (!cJSON_AddItemToArray(son, str)) {
        cJSON_Delete(str);
        cJSON_Delete(root);
        return;
    }

    char *buffer = cJSON_Print(root);
    cJSON_Delete(root);
    if (buffer == nullptr) {
        return;
    }

    if (BundleDaemonClient::GetInstance().StoreContentToFile(path, buffer, strlen(buffer) + 1) != EC_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_APP, "init Third System Bundle Record fail!");
    }
    cJSON_free(buffer);
}

bool BundleInstaller::BackUpInstallRecord(const InstallRecord &record, const char *jsonPath)
{
    if (jsonPath == nullptr) {
        return false;
    }
    cJSON *object = BundleUtil::ConvertInstallRecordToJson(record);
    if (object == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "BackUpInstallRecord fail, beacuse convertInstallRecordToJson object is null!");
        return false;
    }

    char *buffer = cJSON_Print(object);
    cJSON_Delete(object);
    if (buffer == nullptr) {
        return false;
    }
    if (BundleDaemonClient::GetInstance().StoreContentToFile(jsonPath, buffer, strlen(buffer) + 1) != EC_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_APP, "BackUpInstallRecord fail, beacuse store Json Content fail!");
        cJSON_free(buffer);
        return false;
    }
    cJSON_free(buffer);
    return true;
}

uint8_t BundleInstaller::StorePermissions(const char *bundleName, PermissionTrans *permissions, int32_t permNum,
    bool isUpdate)
{
    if (permNum == 0) {
        return ERR_OK;
    }

    if (bundleName == nullptr || permissions == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "Store permission fail when param is nullptr!");
        ManagerService::GetInstance().RemoveBundleInfo(bundleName);
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    if (BundleDaemonClient::GetInstance().CreatePermissionDir() != EC_SUCCESS) {
        ManagerService::GetInstance().RemoveBundleInfo(bundleName);
        return ERR_APPEXECFWK_INSTALL_FAILED_CREATE_PERMISSIONS_DIR_ERROR;
    }

    if (SaveOrUpdatePermissions(const_cast<char *>(bundleName), permissions, permNum,
        static_cast<IsUpdate>(isUpdate)) != 0) {
        ManagerService::GetInstance().RemoveBundleInfo(bundleName);
        return ERR_APPEXECFWK_INSTALL_FAILED_STORE_PERMISSIONS_ERROR;
    }
    return ERR_OK;
}

uint8_t BundleInstaller::CheckVersionAndSignature(const char *bundleName, BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr || bundleName == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "CheckVersionAndSignature fail beacuse param is nullptr!");
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }
    BundleInfo *oldBundleInfo = ManagerService::GetInstance().QueryBundleInfo(bundleName);
    if (oldBundleInfo != nullptr) {
        if (oldBundleInfo->versionCode > bundleInfo->versionCode) {
            return ERR_APPEXECFWK_INSTALL_FAILED_VERSION_DOWNGRADE;
        }
#ifndef __LINUX__
        if (oldBundleInfo->appId == nullptr || bundleInfo->appId == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "appid from bundleInfo is nullptr!");
            return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
        }
        if (strcmp(oldBundleInfo->appId, bundleInfo->appId) != 0) {
            return ERR_APPEXECFWK_INSTALL_FAILED_INCOMPATIBLE_SIGNATURE;
        }
#endif
        // in this situation, it need to change codePath and dataPath
        if (!BundleInfoUtils::SetBundleInfoCodePath(bundleInfo, oldBundleInfo->codePath) ||
            !BundleInfoUtils::SetBundleInfoDataPath(bundleInfo, oldBundleInfo->dataPath)) {
            HILOG_ERROR(HILOG_MODULE_APP, "when in update situation, it change codePath or dataPath fail!");
            return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
        }
    }
    return ERR_OK;
}

bool BundleInstaller::RenameJsonFile(const char *fileName)
{
    if (fileName == nullptr) {
        return false;
    }

    std::string tmpJsonPath = std::string(JSON_PATH) + PATH_SEPARATOR + fileName + TMP_SUFFIX + JSON_SUFFIX;
    std::string jsonPath = std::string(JSON_PATH) + PATH_SEPARATOR + fileName + JSON_SUFFIX;
    if (BundleDaemonClient::GetInstance().RenameFile(tmpJsonPath.c_str(), jsonPath.c_str()) != EC_SUCCESS) {
        return false;
    }
    return true;
}
} // namespace OHOS
