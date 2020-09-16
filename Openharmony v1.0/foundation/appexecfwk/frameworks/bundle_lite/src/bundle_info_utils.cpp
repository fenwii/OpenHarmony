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

#include "bundle_info_utils.h"

#include "ability_info_utils.h"
#include "module_info_utils.h"
#include "securec.h"

namespace OHOS {
const uint8_t GET_BUNDLE_WITH_ABILITIES = 1;

void BundleInfoUtils::FreeBundleInfos(BundleInfo *bundleInfos, uint32_t len)
{
    if (bundleInfos == nullptr) {
        return;
    }
    for (uint32_t i = 0; i < len; ++i) {
        ClearBundleInfo(bundleInfos + i);
    }
    AdapterFree(bundleInfos);
}

void BundleInfoUtils::FreeBundleInfo(BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr) {
        return;
    }
    ClearBundleInfo(bundleInfo);
    AdapterFree(bundleInfo);
}

void BundleInfoUtils::CopyBundleInfo(int32_t flags, BundleInfo *des, BundleInfo src)
{
    if (des == nullptr) {
        return;
    }

    SetBundleInfoBundleName(des, src.bundleName);
    SetBundleInfoLabel(des, src.label);
    SetBundleInfoVersionName(des, src.versionName);
    SetBundleInfoBigIconPath(des, src.bigIconPath);
    SetBundleInfoCodePath(des, src.codePath);
    SetBundleInfoDataPath(des, src.dataPath);
    SetBundleInfoVendor(des, src.vendor);
    SetBundleInfoModuleInfos(des, src.moduleInfos, src.numOfModule);
    des->isSystemApp = src.isSystemApp;
    des->versionCode = src.versionCode;
    des->compatibleApi = src.compatibleApi;
    des->targetApi = src.targetApi;
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    SetBundleInfoAppId(des, src.appId);
    SetBundleInfoSharedLibPath(des, src.sharedLibPath);
    des->isKeepAlive = src.isKeepAlive;
    des->isNativeApp = src.isNativeApp;
    des->uid = src.uid;
    des->gid = src.gid;
    if (flags == GET_BUNDLE_WITH_ABILITIES) {
        SetBundleInfoAbilityInfos(des, src.abilityInfos, src.numOfAbility);
    } else {
        des->abilityInfos = nullptr;
        des->numOfAbility = 0;
    }
#else
    SetBundleInfoSmallIconPath(des, src.smallIconPath);
    if (flags == GET_BUNDLE_WITH_ABILITIES) {
        if (src.abilityInfo != nullptr) {
            SetBundleInfoAbilityInfo(des, *(src.abilityInfo));
        }
    } else {
        des->abilityInfo = nullptr;
    }
#endif
}

bool BundleInfoUtils::SetBundleInfoBundleName(BundleInfo *bundleInfo, const char *bundleName)
{
    if (bundleInfo == nullptr || bundleName == nullptr) {
        return false;
    }

    AdapterFree(bundleInfo->bundleName);
    bundleInfo->bundleName = Utils::Strdup(bundleName);
    return bundleInfo->bundleName != nullptr;
}

bool BundleInfoUtils::SetBundleInfoVendor(BundleInfo *bundleInfo, const char *vendor)
{
    if (bundleInfo == nullptr || vendor == nullptr) {
        return false;
    }

    AdapterFree(bundleInfo->vendor);
    bundleInfo->vendor = Utils::Strdup(vendor);
    return bundleInfo->vendor != nullptr;
}

bool BundleInfoUtils::SetBundleInfoLabel(BundleInfo *bundleInfo, const char *label)
{
    if (bundleInfo == nullptr || label == nullptr) {
        return false;
    }

    AdapterFree(bundleInfo->label);
    bundleInfo->label = Utils::Strdup(label);
    return bundleInfo->label != nullptr;
}

bool BundleInfoUtils::SetBundleInfoVersionName(BundleInfo *bundleInfo, const char *versionName)
{
    if (bundleInfo == nullptr || versionName == nullptr) {
        return false;
    }

    AdapterFree(bundleInfo->versionName);
    bundleInfo->versionName = Utils::Strdup(versionName);
    return bundleInfo->versionName != nullptr;
}

bool BundleInfoUtils::SetBundleInfoBigIconPath(BundleInfo *bundleInfo, const char *bigIconPath)
{
    if (bundleInfo == nullptr || bigIconPath == nullptr) {
        return false;
    }

    AdapterFree(bundleInfo->bigIconPath);
    bundleInfo->bigIconPath = Utils::Strdup(bigIconPath);
    return bundleInfo->bigIconPath != nullptr;
}

bool BundleInfoUtils::SetBundleInfoCodePath(BundleInfo *bundleInfo, const char *codePath)
{
    if (bundleInfo == nullptr || codePath == nullptr) {
        return false;
    }

    AdapterFree(bundleInfo->codePath);
    bundleInfo->codePath = Utils::Strdup(codePath);
    return bundleInfo->codePath != nullptr;
}

bool BundleInfoUtils::SetBundleInfoDataPath(BundleInfo *bundleInfo, const char *dataPath)
{
    if (bundleInfo == nullptr || dataPath == nullptr) {
        return false;
    }

    AdapterFree(bundleInfo->dataPath);
    bundleInfo->dataPath = Utils::Strdup(dataPath);
    return bundleInfo->dataPath != nullptr;
}

bool BundleInfoUtils::SetBundleInfoModuleInfos(BundleInfo *bundleInfo, const ModuleInfo *moduleInfos,
    uint32_t numOfModule)
{
    if (numOfModule == 0) {
        return true;
    }

    if (moduleInfos == nullptr || bundleInfo == nullptr) {
        return false;
    }

    bundleInfo->numOfModule = numOfModule;
    bundleInfo->moduleInfos = reinterpret_cast<ModuleInfo *>(AdapterMalloc(sizeof(ModuleInfo) * numOfModule));
    if (bundleInfo->moduleInfos == nullptr) {
        return false;
    }

    int32_t ret = memset_s(bundleInfo->moduleInfos, sizeof(ModuleInfo) * numOfModule, 0,
        sizeof(ModuleInfo) * numOfModule);
    if (ret != EOK) {
        AdapterFree(bundleInfo->moduleInfos);
        return false;
    }

    for (uint32_t i = 0; i < numOfModule; i++) {
        ModuleInfoUtils::CopyModuleInfo(bundleInfo->moduleInfos + i, moduleInfos[i]);
    }
    return true;
}

void BundleInfoUtils::ClearModuleInfos(ModuleInfo *moduleInfos, uint32_t numOfModule)
{
    if (moduleInfos == nullptr || numOfModule == 0) {
        return;
    }

    for (uint32_t i = 0; i < numOfModule; i++) {
        ClearModuleInfo(moduleInfos + i);
    }
}

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
bool BundleInfoUtils::SetBundleInfoAppId(BundleInfo *bundleInfo, const char *appId)
{
    if (bundleInfo == nullptr || appId == nullptr) {
        return false;
    }

    AdapterFree(bundleInfo->appId);
    bundleInfo->appId = Utils::Strdup(appId);
    return bundleInfo->appId != nullptr;
}

bool BundleInfoUtils::SetBundleInfoSharedLibPath(BundleInfo *bundleInfo, const char *sharedLibPath)
{
    if (bundleInfo == nullptr || sharedLibPath == nullptr) {
        return false;
    }

    AdapterFree(bundleInfo->sharedLibPath);
    bundleInfo->sharedLibPath = Utils::Strdup(sharedLibPath);
    return bundleInfo->sharedLibPath != nullptr;
}

bool BundleInfoUtils::SetBundleInfoAbilityInfos(BundleInfo *bundleInfo, const AbilityInfo *abilityInfos,
    uint32_t numOfAbility)
{
    if (numOfAbility == 0) {
        return true;
    }

    if (abilityInfos == nullptr || bundleInfo == nullptr) {
        return false;
    }

    bundleInfo->numOfAbility = numOfAbility;
    bundleInfo->abilityInfos = reinterpret_cast<AbilityInfo *>(AdapterMalloc(sizeof(AbilityInfo) * numOfAbility));
    if (bundleInfo->abilityInfos == nullptr) {
        return false;
    }
    int32_t ret = memset_s(bundleInfo->abilityInfos, sizeof(AbilityInfo) * numOfAbility, 0,
        sizeof(AbilityInfo) * numOfAbility);
    if (ret != EOK) {
        AdapterFree(bundleInfo->abilityInfos);
        return false;
    }

    for (uint32_t i = 0; i < numOfAbility; i++) {
        AbilityInfoUtils::CopyAbilityInfo(bundleInfo->abilityInfos + i, abilityInfos[i]);
    }
    return true;
}

void BundleInfoUtils::ClearAbilityInfos(AbilityInfo *abilityInfos, uint32_t numOfAbility)
{
    if (abilityInfos == nullptr || numOfAbility == 0) {
        return;
    }

    for (uint32_t i = 0; i < numOfAbility; i++) {
        ClearAbilityInfo(abilityInfos + i);
    }
}
#else
bool BundleInfoUtils::SetBundleInfoSmallIconPath(BundleInfo *bundleInfo, const char *smallIconPath)
{
    if (bundleInfo == nullptr || smallIconPath == nullptr) {
        return false;
    }

    AdapterFree(bundleInfo->smallIconPath);
    bundleInfo->smallIconPath = Utils::Strdup(smallIconPath);
    return bundleInfo->smallIconPath != nullptr;
}

bool BundleInfoUtils::SetBundleInfoAbilityInfo(BundleInfo *bundleInfo, AbilityInfo abilityInfo)
{
    if (bundleInfo == nullptr) {
        return false;
    }

    ClearAbilityInfo(bundleInfo->abilityInfo);
    AdapterFree(bundleInfo->abilityInfo);
    bundleInfo->abilityInfo = reinterpret_cast<AbilityInfo *>(AdapterMalloc(sizeof(AbilityInfo)));
    if (bundleInfo->abilityInfo == nullptr ||
        memset_s(bundleInfo->abilityInfo, sizeof(AbilityInfo), 0, sizeof(AbilityInfo)) != EOK) {
        AdapterFree(bundleInfo->abilityInfo);
        return false;
    }

    AbilityInfoUtils::CopyAbilityInfo(bundleInfo->abilityInfo, abilityInfo);
    return true;
}
#endif
} // OHOS