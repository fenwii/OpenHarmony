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

#include "ability_info_utils.h"

#include "utils.h"

namespace OHOS {
void AbilityInfoUtils::CopyAbilityInfo(AbilityInfo *des, AbilityInfo src)
{
    if (des == nullptr) {
        return;
    }

    SetAbilityInfoBundleName(des, src.bundleName);
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    des->isVisible = src.isVisible;
    des->abilityType = src.abilityType;
    des->launchMode = src.launchMode;
    SetAbilityInfoModuleName(des, src.moduleName);
    SetAbilityInfoName(des, src.name);
    SetAbilityInfoDescription(des, src.description);
    SetAbilityInfoIconPath(des, src.iconPath);
    SetAbilityInfoDeviceId(des, src.deviceId);
    SetAbilityInfoLabel(des, src.label);
#else
    SetAbilityInfoSrcPath(des, src.srcPath);
#endif
}

bool AbilityInfoUtils::SetAbilityInfoBundleName(AbilityInfo *abilityInfo, const char *bundleName)
{
    if (abilityInfo == nullptr || bundleName == nullptr) {
        return false;
    }

    AdapterFree(abilityInfo->bundleName);
    abilityInfo->bundleName = Utils::Strdup(bundleName);
    return abilityInfo->bundleName != nullptr;
}

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
bool AbilityInfoUtils::SetAbilityInfoModuleName(AbilityInfo *abilityInfo, const char *moduleName)
{
    if (abilityInfo == nullptr || moduleName == nullptr) {
        return false;
    }

    AdapterFree(abilityInfo->moduleName);
    abilityInfo->moduleName = Utils::Strdup(moduleName);
    return abilityInfo->moduleName != nullptr;
}

bool AbilityInfoUtils::SetAbilityInfoName(AbilityInfo *abilityInfo, const char *name)
{
    if (abilityInfo == nullptr || name == nullptr) {
        return false;
    }

    AdapterFree(abilityInfo->name);
    abilityInfo->name = Utils::Strdup(name);
    return abilityInfo->name != nullptr;
}

bool AbilityInfoUtils::SetAbilityInfoDescription(AbilityInfo *abilityInfo, const char *description)
{
    if (abilityInfo == nullptr || description == nullptr) {
        return false;
    }

    AdapterFree(abilityInfo->description);
    abilityInfo->description = Utils::Strdup(description);
    return abilityInfo->description != nullptr;
}

bool AbilityInfoUtils::SetAbilityInfoIconPath(AbilityInfo *abilityInfo, const char *iconPath)
{
    if (abilityInfo == nullptr || iconPath == nullptr) {
        return false;
    }

    AdapterFree(abilityInfo->iconPath);
    abilityInfo->iconPath = Utils::Strdup(iconPath);
    return abilityInfo->iconPath != nullptr;
}

bool AbilityInfoUtils::SetAbilityInfoDeviceId(AbilityInfo *abilityInfo, const char *deviceId)
{
    if (abilityInfo == nullptr || deviceId == nullptr) {
        return false;
    }

    AdapterFree(abilityInfo->deviceId);
    abilityInfo->deviceId = Utils::Strdup(deviceId);
    return abilityInfo->deviceId != nullptr;
}

bool AbilityInfoUtils::SetAbilityInfoLabel(AbilityInfo *abilityInfo, const char *label)
{
    if (abilityInfo == nullptr || label == nullptr) {
        return false;
    }

    AdapterFree(abilityInfo->label);
    abilityInfo->label = Utils::Strdup(label);
    return abilityInfo->label != nullptr;
}
#else
bool AbilityInfoUtils::SetAbilityInfoSrcPath(AbilityInfo *abilityInfo, const char *srcPath)
{
    if (abilityInfo == nullptr || srcPath == nullptr) {
        return false;
    }

    AdapterFree(abilityInfo->srcPath);
    abilityInfo->srcPath = Utils::Strdup(srcPath);
    return abilityInfo->srcPath != nullptr;
}
#endif
} // OHOS