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

#include "util/abilityms_helper.h"

#include <cstring>

namespace OHOS {
const char * const LAUNCHER_BUNDLE_NAME = "com.huawei.launcher";
const char * const LAUNCHER_ABILITY_NAME = "MainAbility";
const char * const ACE_ABILITY_NAME = "AceAbility";
const int MAX_BUNDLE_NAME_SIZE = 128;

bool AbilityMsHelper::IsLauncherAbility(const char *bundleName)
{
    if (bundleName == nullptr) {
        PRINTW("AbilityMsHelper", "bundleName is null");
        return false;
    }
    return strcmp(LAUNCHER_BUNDLE_NAME, bundleName) == 0;
}

bool AbilityMsHelper::IsAceAbility(const char *abilityName)
{
    if (abilityName == nullptr) {
        PRINTW("AbilityMsHelper", "abilityName is null");
        return false;
    }
    return strcmp(ACE_ABILITY_NAME, abilityName) == 0;
}

AbilityMsStatus AbilityMsHelper::SetLauncherWant(Want &want)
{
    ElementName elementName = {};
    SetElementAbilityName(&elementName, LAUNCHER_ABILITY_NAME);
    SetElementBundleName(&elementName, LAUNCHER_BUNDLE_NAME);

    SetWantElement(&want, elementName);
    ClearElement(&elementName);
    return AbilityMsStatus::Ok();
}

AbilityMsStatus AbilityMsHelper::SetKeepAliveWant(const BundleInfo &bundleInfo, Want &want)
{
    if (bundleInfo.numOfAbility <= 0) {
        return AbilityMsStatus::HelpStatus("no ability exist");
    }
    ElementName elementName = {};
    if (bundleInfo.abilityInfos[0].name == nullptr) {
        return AbilityMsStatus::HelpStatus("abilityName is null");
    }
    if (bundleInfo.bundleName == nullptr) {
        return AbilityMsStatus::HelpStatus("bundleName is null");
    }
    SetElementAbilityName(&elementName, bundleInfo.abilityInfos[0].name);
    SetElementBundleName(&elementName, bundleInfo.bundleName);

    SetWantElement(&want, elementName);
    ClearElement(&elementName);
    return AbilityMsStatus::Ok();
}

#ifdef OHOS_DEBUG
std::string AbilityMsHelper::AbilityStateToString(State state)
{
    std::string result;
    switch (state) {
        case STATE_UNINITIALIZED:
            result = "uninitialized";
            break;
        case STATE_INITIAL:
            result = "initial";
            break;
        case STATE_INACTIVE:
            result = "inactive";
            break;
        case STATE_ACTIVE:
            result = "active";
            break;
        case STATE_BACKGROUND:
            result = "background";
            break;
        default:
            break;
    }
    return result;
}
#endif

bool AbilityMsHelper::IsLegalBundleName(const char *bundleName)
{
    if (bundleName == nullptr) {
        return false;
    }
    int len = strlen(bundleName);
    if (len <= 0 || len > MAX_BUNDLE_NAME_SIZE) {
        return false;
    }
    return true;
}

bool AbilityMsHelper::CheckVisiblePermission(pid_t callingUid, pid_t targetUid, bool isVisible)
{
    if (callingUid == SYSTEM_UID) {
        return true;
    }
    if (isVisible || callingUid == targetUid) {
        return true;
    }
    return false;
}
}
