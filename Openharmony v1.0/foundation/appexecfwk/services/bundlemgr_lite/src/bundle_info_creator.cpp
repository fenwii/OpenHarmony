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

#include "bundle_info_creator.h"

#include "ability_info_utils.h"
#include "appexecfwk_errors.h"
#include "bundle_info_utils.h"
#include "bundle_manager_service.h"
#include "bundle_res_transform.h"
#include "bundle_util.h"
#include "log.h"
#include "module_info_utils.h"
#include "securec.h"
#include "utils.h"

namespace OHOS {
uint8_t BundleInfoCreator::SaveBundleInfo(const BundleProfile &bundleProfile, BundleInfo **bundleInfo)
{
    *bundleInfo = reinterpret_cast<BundleInfo *>(AdapterMalloc(sizeof(BundleInfo)));
    if (*bundleInfo == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "malloc bundleInfo fail!");
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    if (memset_s(*bundleInfo, sizeof(BundleInfo), 0, sizeof(BundleInfo)) != EOK) {
        HILOG_ERROR(HILOG_MODULE_APP, "memset bundleInfo fail!");
        AdapterFree(*bundleInfo);
        *bundleInfo = nullptr;
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    std::string installDirPath = ManagerService::GetInstance().GetCodeDirPath();
    std::string dataDirPath = ManagerService::GetInstance().GetDataDirPath();
    if (!SetBundleInfo(bundleProfile, installDirPath, dataDirPath, *bundleInfo)) {
        BundleInfoUtils::FreeBundleInfo(*bundleInfo);
        *bundleInfo = nullptr;
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }
    return ERR_OK;
}

BundleInfo *BundleInfoCreator::CreateBundleInfo(const BundleProfile &bundleProfile, const std::string &installDirPath,
    const std::string &dataDirPath, const BundleRes &bundleRes)
{
    BundleInfo *bundleInfo = reinterpret_cast<BundleInfo *>(AdapterMalloc(sizeof(BundleInfo)));
    if (bundleInfo == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "malloc bundleInfo fail when create bundleInfo!");
        return nullptr;
    }

    int32_t ret = memset_s(bundleInfo, sizeof(BundleInfo), 0, sizeof(BundleInfo));
    if (ret != EOK) {
        HILOG_ERROR(HILOG_MODULE_APP, "memset bundleInfo fail when create bundleInfo!");
        AdapterFree(bundleInfo);
        return nullptr;
    }

    if (!SetBundleInfo(bundleProfile, installDirPath, dataDirPath, bundleInfo)) {
        HILOG_ERROR(HILOG_MODULE_APP, "set bundleInfo fail when create bundleInfo!");
        BundleInfoUtils::FreeBundleInfo(bundleInfo);
        return nullptr;
    }

    uint8_t errorCode = BundleResTransform::ConvertResInfoToBundleInfo(bundleInfo->codePath, bundleRes, bundleInfo);
    if (errorCode != ERR_OK) {
        HILOG_ERROR(HILOG_MODULE_APP, "convert resInfo to bundleInfo fail when create bundleInfo!");
        BundleInfoUtils::FreeBundleInfo(bundleInfo);
        return nullptr;
    }
    return bundleInfo;
}

bool BundleInfoCreator::SetBundleInfo(const BundleProfile &bundleProfile, const std::string &installDirPath,
    const std::string &dataDirPath, BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr || installDirPath.empty() || dataDirPath.empty()) {
        return false;
    }
    bundleInfo->isKeepAlive = bundleProfile.isKeepAlive;
    bundleInfo->isNativeApp = bundleProfile.isNativeApp;
    bundleInfo->versionCode = bundleProfile.profileVersion.versionCode;
    bundleInfo->compatibleApi = bundleProfile.profileApiVersion.minApiVersion;
    if (bundleProfile.profileApiVersion.maxApiVersion == 0) {
        bundleInfo->targetApi = bundleInfo->compatibleApi;
    } else {
        bundleInfo->targetApi = bundleProfile.profileApiVersion.maxApiVersion;
    }
    // set codePath and dataPath
    std::string codePath = installDirPath + PATH_SEPARATOR + bundleProfile.bundleName;
    std::string dataPath = dataDirPath + PATH_SEPARATOR + bundleProfile.bundleName;
    if (codePath.size() > PATH_LENGTH || dataPath.size() > PATH_LENGTH) {
        HILOG_ERROR(HILOG_MODULE_APP, "codePath or dataPath length exceed max value!");
        return false;
    }

    if (bundleProfile.iconPath != nullptr && !BundleUtil::StartWith(bundleProfile.iconPath,
        DEFAULT_ICON_SETTING_BEGIN)) {
        std::string iconPath = codePath + PATH_SEPARATOR + bundleProfile.moduleInfo.moduleName + PATH_SEPARATOR +
            bundleProfile.iconPath;
        if (iconPath.size() > PATH_LENGTH) {
            HILOG_ERROR(HILOG_MODULE_APP, "iconPath length exceed max value!");
            return false;
        }
        if (!BundleInfoUtils::SetBundleInfoBigIconPath(bundleInfo, iconPath.c_str())) {
            HILOG_ERROR(HILOG_MODULE_APP, "set iconPath in bundleInfo fail!");
            return false;
        }
    }

    if ((bundleProfile.label != nullptr) && !BundleUtil::StartWith(bundleProfile.label, DEFAULT_LABEL_SETTING)) {
        if (!BundleInfoUtils::SetBundleInfoLabel(bundleInfo, bundleProfile.label)) {
            HILOG_ERROR(HILOG_MODULE_APP, "set label in bundleInfo fail!");
            return false;
        }
    }

    if (!BundleInfoUtils::SetBundleInfoBundleName(bundleInfo, bundleProfile.bundleName) ||
        !BundleInfoUtils::SetBundleInfoVersionName(bundleInfo, bundleProfile.profileVersion.versionName) ||
        !BundleInfoUtils::SetBundleInfoCodePath(bundleInfo, codePath.c_str()) ||
        !BundleInfoUtils::SetBundleInfoDataPath(bundleInfo, dataPath.c_str()) ||
        (bundleProfile.vendor != nullptr && !BundleInfoUtils::SetBundleInfoVendor(bundleInfo, bundleProfile.vendor)) ||
        !SetModuleInfos(bundleProfile, bundleInfo) ||
        (bundleProfile.numOfAbility != 0 && !SetAbilityInfos(bundleProfile, codePath, bundleInfo))) {
        HILOG_ERROR(HILOG_MODULE_APP, "SetBundleInfo fail!");
        return false;
    }
    return true;
}

bool BundleInfoCreator::SetModuleInfos(const BundleProfile &bundleProfile, BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr) {
        return false;
    }
    bundleInfo->moduleInfos = reinterpret_cast<ModuleInfo *>(AdapterMalloc(sizeof(ModuleInfo)));
    if (bundleInfo->moduleInfos == nullptr) {
        return false;
    }

    if (memset_s(bundleInfo->moduleInfos, sizeof(ModuleInfo), 0, sizeof(ModuleInfo)) != EOK) {
        HILOG_ERROR(HILOG_MODULE_APP, "memset ModuleInfo fail!");
        AdapterFree(bundleInfo->moduleInfos);
        bundleInfo->moduleInfos = nullptr;
        return false;
    }

    bundleInfo->numOfModule = 1;
    if (!ModuleInfoUtils::SetModuleInfoDeviceType(bundleInfo->moduleInfos,
        const_cast<char **>(bundleProfile.moduleInfo.deviceType), DEVICE_TYPE_SIZE)) {
        HILOG_ERROR(HILOG_MODULE_APP, "SetModuleInfoDeviceType fail!");
        return false;
    }
    if (!ModuleInfoUtils::SetModuleInfoMetaData(bundleInfo->moduleInfos,
        const_cast<MetaData **>(bundleProfile.moduleInfo.metaData), METADATA_SIZE)) {
        HILOG_ERROR(HILOG_MODULE_APP, "SetModuleInfoMetaData fail!");
        return false;
    }

    if (bundleProfile.moduleInfo.description != nullptr &&
        !BundleUtil::StartWith(bundleProfile.moduleInfo.description, DEFAULT_DESC_SETTING)) {
        if (!ModuleInfoUtils::SetModuleInfoDescription(bundleInfo->moduleInfos,
            bundleProfile.moduleInfo.description)) {
            HILOG_ERROR(HILOG_MODULE_APP, "SetModuleInfo description fail!");
            return false;
        }
    }
    if ((bundleProfile.moduleInfo.name != nullptr &&
        !ModuleInfoUtils::SetModuleInfoName(bundleInfo->moduleInfos, bundleProfile.moduleInfo.name)) ||
        !ModuleInfoUtils::SetModuleInfoModuleName(bundleInfo->moduleInfos, bundleProfile.moduleInfo.moduleName) ||
        !ModuleInfoUtils::SetModuleInfoModuleType(bundleInfo->moduleInfos, bundleProfile.moduleInfo.moduleType)) {
        HILOG_ERROR(HILOG_MODULE_APP, "Set name or moduleName or moduleType or description in ModuleInfo fail!");
        return false;
    }
    bundleInfo->moduleInfos->isDeliveryInstall = bundleProfile.moduleInfo.isDeliveryInstall;
    return true;
}

bool BundleInfoCreator::SetAbilityInfos(const BundleProfile &bundleProfile, const std::string &codePath,
    BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr || bundleProfile.numOfAbility == 0) {
        return false;
    }
    bundleInfo->numOfAbility = bundleProfile.numOfAbility;
    bundleInfo->abilityInfos = reinterpret_cast<AbilityInfo *>(AdapterMalloc(sizeof(AbilityInfo) *
        bundleInfo->numOfAbility));
    if (bundleInfo->abilityInfos == nullptr) {
        return false;
    }
    int32_t ret = memset_s(bundleInfo->abilityInfos, sizeof(AbilityInfo) * bundleInfo->numOfAbility, 0,
        sizeof(AbilityInfo) * bundleInfo->numOfAbility);
    if (ret != EOK) {
        HILOG_ERROR(HILOG_MODULE_APP, "memset AbilityInfo fail!");
        return false;
    }

    for (int32_t i = 0; i < bundleInfo->numOfAbility; i++) {
        if (!SetAbilityInfo(bundleProfile, codePath, bundleInfo, i)) {
            return false;
        }
    }
    return true;
}

bool BundleInfoCreator::SetAbilityInfo(const BundleProfile &bundleProfile, const std::string &codePath,
    BundleInfo *bundleInfo, uint32_t index)
{
    if (bundleInfo == nullptr) {
        return false;
    }

    AbilityInfo *abilityInfo = bundleInfo->abilityInfos + index;
    if (abilityInfo == nullptr) {
        return false;
    }

    if (bundleProfile.abilityInfos[index].iconPath != nullptr &&
        !BundleUtil::StartWith(bundleProfile.abilityInfos[index].iconPath, DEFAULT_ICON_SETTING_BEGIN)) {
        std::string iconPath = codePath + PATH_SEPARATOR + bundleProfile.moduleInfo.moduleName + PATH_SEPARATOR +
            bundleProfile.abilityInfos[index].iconPath;
        if (iconPath.size() > PATH_LENGTH) {
            HILOG_ERROR(HILOG_MODULE_APP, "ability iconPath length exceed max value!");
            return false;
        }
        if (!AbilityInfoUtils::SetAbilityInfoIconPath(abilityInfo, iconPath.c_str())) {
            HILOG_ERROR(HILOG_MODULE_APP, "Set iconPath in AbilityInfos fail!");
            return false;
        }
    }

    if (bundleProfile.abilityInfos[index].description != nullptr &&
        !BundleUtil::StartWith(bundleProfile.abilityInfos[index].description, DEFAULT_DESC_SETTING)) {
        if (!AbilityInfoUtils::SetAbilityInfoDescription(abilityInfo, bundleProfile.abilityInfos[index].description)) {
            HILOG_ERROR(HILOG_MODULE_APP, "Set description in AbilityInfos fail!");
            return false;
        }
    }

    if (bundleProfile.abilityInfos[index].label != nullptr &&
        !BundleUtil::StartWith(bundleProfile.abilityInfos[index].label, DEFAULT_LABEL_SETTING)) {
        if (!AbilityInfoUtils::SetAbilityInfoLabel(abilityInfo, bundleProfile.abilityInfos[index].label)) {
            HILOG_ERROR(HILOG_MODULE_APP, "Set label in AbilityInfos fail!");
            return false;
        }
    }

    abilityInfo->isVisible = bundleProfile.abilityInfos[index].isVisible;
    abilityInfo->abilityType = bundleProfile.abilityInfos[index].abilityType;
    abilityInfo->launchMode = bundleProfile.abilityInfos[index].launchMode;
    if (!AbilityInfoUtils::SetAbilityInfoBundleName(abilityInfo, bundleProfile.bundleName) ||
        !AbilityInfoUtils::SetAbilityInfoModuleName(abilityInfo, bundleProfile.moduleInfo.moduleName) ||
        !AbilityInfoUtils::SetAbilityInfoName(abilityInfo, bundleProfile.abilityInfos[index].name)) {
        HILOG_ERROR(HILOG_MODULE_APP, "Set other value in AbilityInfos fail!");
        return false;
    }
    return true;
}
} // namespace OHOS