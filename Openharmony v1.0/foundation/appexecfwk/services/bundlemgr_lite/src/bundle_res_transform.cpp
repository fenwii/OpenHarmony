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

#include "bundle_res_transform.h"

#include "ability_info_utils.h"
#include "appexecfwk_errors.h"
#include "bundle_info_utils.h"
#include "bundle_util.h"
#include "global.h"
#include "log.h"
#include "module_info_utils.h"

namespace OHOS {
uint8_t BundleResTransform::ConvertResInfoToBundleInfo(const std::string &path, const BundleRes &bundleRes,
    BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
    }

    if (bundleRes.totalNumOfAbilityRes == 0 || bundleInfo->isNativeApp) {
        return ERR_OK;
    }

    char *des = nullptr;
    std::string resPath = path + PATH_SEPARATOR + bundleInfo->moduleInfos[0].moduleName + ASSETS +
        bundleInfo->moduleInfos[0].moduleName + PATH_SEPARATOR + RESOURCES_INDEX;
    if (bundleRes.moduleDescriptionId > 0) {
        if (!BundleUtil::IsFile(resPath.c_str())) {
            HILOG_ERROR(HILOG_MODULE_APP, "resource index is not exists!");
            return ERR_APPEXECFWK_INSTALL_FAILED_RESOURCE_INDEX_NOT_EXISTS;
        }
        if (GLOBAL_GetValueById(bundleRes.moduleDescriptionId, resPath.c_str(), &des) < 0) {
            HILOG_ERROR(HILOG_MODULE_APP, "get moduleInfo description resId fail!");
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DESCRIPTION_RES_ERROR;
        }
        if (!ModuleInfoUtils::SetModuleInfoDescription(bundleInfo->moduleInfos, des)) {
            AdapterFree(des);
            HILOG_ERROR(HILOG_MODULE_APP, "set moduleInfo description resId fail!");
            return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR;
        }
        AdapterFree(des);
    }

    for (uint32_t i = 0; i < bundleRes.totalNumOfAbilityRes; i++) {
        if (bundleRes.abilityRes[i].iconId > 0 &&
            !ConvertIconResToBundleInfo(resPath, bundleRes.abilityRes[i].iconId, bundleInfo, i)) {
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ICON_RES_ERROR;
        }
        if (bundleRes.abilityRes[i].labelId > 0 &&
            !ConvertLableResToBundleInfo(resPath, bundleRes.abilityRes[i].labelId, bundleInfo, i)) {
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_LABEL_RES_ERROR;
        }
        if (bundleRes.abilityRes[i].descriptionId > 0 &&
            !ConvertDesResIdToBundleInfo(resPath, bundleRes.abilityRes[i].descriptionId, bundleInfo, i)) {
            return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DESCRIPTION_RES_ERROR;
        }
    }
    return ERR_OK;
}

bool BundleResTransform::ConvertIconResToBundleInfo(const std::string &path, uint32_t iconId, BundleInfo *bundleInfo,
    uint32_t index)
{
    if (path.empty() || bundleInfo == nullptr) {
        return false;
    }
    if (!BundleUtil::IsFile(path.c_str())) {
        return false;
    }

    char *relativeIconPath = nullptr;
    if (GLOBAL_GetValueById(iconId, path.c_str(), &relativeIconPath) != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "get icon resId fail!");
        return false;
    }

    std::string iconPath = std::string(bundleInfo->codePath) + PATH_SEPARATOR + bundleInfo->moduleInfos[0].moduleName +
        ASSETS + relativeIconPath;
    if (!BundleUtil::IsFile(iconPath.c_str())) {
        HILOG_ERROR(HILOG_MODULE_APP, "icon is not exists!");
        AdapterFree(relativeIconPath);
        return false;
    }

    if (index == 0) {
        if (!BundleInfoUtils::SetBundleInfoBigIconPath(bundleInfo, iconPath.c_str())) {
            HILOG_ERROR(HILOG_MODULE_APP, "set icon resId in bundleInfo fail!");
            AdapterFree(relativeIconPath);
            return false;
        }
    }
    if (!AbilityInfoUtils::SetAbilityInfoIconPath(bundleInfo->abilityInfos + index, iconPath.c_str())) {
        HILOG_ERROR(HILOG_MODULE_APP, "set icon resId in abilityInfo fail!");
        AdapterFree(relativeIconPath);
        return false;
    }
    AdapterFree(relativeIconPath);
    return true;
}

bool BundleResTransform::ConvertLableResToBundleInfo(const std::string &path, uint32_t labelId, BundleInfo *bundleInfo,
    uint32_t index)
{
    if (path.empty() || bundleInfo == nullptr) {
        return false;
    }
    if (!BundleUtil::IsFile(path.c_str())) {
        return false;
    }

    char *label = nullptr;
    if (GLOBAL_GetValueById(labelId, path.c_str(), &label) != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "get laebl resId fail!");
        return false;
    }

    if (index == 0) {
        if (!BundleInfoUtils::SetBundleInfoLabel(bundleInfo, label)) {
            HILOG_ERROR(HILOG_MODULE_APP, "set label resId in bundleInfo fail!");
            AdapterFree(label);
            return false;
        }
    }
    if (!AbilityInfoUtils::SetAbilityInfoLabel(bundleInfo->abilityInfos + index, label)) {
        HILOG_ERROR(HILOG_MODULE_APP, "set label resId in abilityInfo fail!");
        AdapterFree(label);
        return false;
    }
    AdapterFree(label);
    return true;
}

bool BundleResTransform::ConvertDesResIdToBundleInfo(const std::string &path, uint32_t desId, BundleInfo *bundleInfo,
    uint32_t index)
{
    if (path.empty() || bundleInfo == nullptr) {
        return false;
    }
    if (!BundleUtil::IsFile(path.c_str())) {
        return false;
    }

    char *description = nullptr;
    if (GLOBAL_GetValueById(desId, path.c_str(), &description) != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "get description resId fail!");
        return false;
    }

    if (!AbilityInfoUtils::SetAbilityInfoDescription(bundleInfo->abilityInfos + index, description)) {
        HILOG_ERROR(HILOG_MODULE_APP, "set description resId in abilityInfo fail!");
        AdapterFree(description);
    }
    AdapterFree(description);
    return true;
}
} // namespace OHOS