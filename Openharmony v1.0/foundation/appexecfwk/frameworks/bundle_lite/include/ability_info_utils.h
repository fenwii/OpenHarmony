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

#ifndef OHOS_ABILITYINFO_UTILS_H
#define OHOS_ABILITYINFO_UTILS_H

#include "ability_info.h"

namespace OHOS {
struct AbilityInfoUtils {
    static void CopyAbilityInfo(AbilityInfo *des, AbilityInfo src);
    static bool SetAbilityInfoBundleName(AbilityInfo *abilityInfo, const char *bundleName);
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    static bool SetAbilityInfoModuleName(AbilityInfo *abilityInfo, const char *moduleName);
    static bool SetAbilityInfoName(AbilityInfo *abilityInfo, const char *name);
    static bool SetAbilityInfoDescription(AbilityInfo *abilityInfo, const char *description);
    static bool SetAbilityInfoIconPath(AbilityInfo *abilityInfo, const char *iconPath);
    static bool SetAbilityInfoDeviceId(AbilityInfo *abilityInfo, const char *deviceId);
    static bool SetAbilityInfoLabel(AbilityInfo *abilityInfo, const char *label);
#else
    static bool SetAbilityInfoSrcPath(AbilityInfo *abilityInfo, const char *srcPath);
#endif
private:
    AbilityInfoUtils() = default;
    ~AbilityInfoUtils() = default;
}; // AbilityInfoUtils
} // OHOS
#endif // OHOS_ABILITYINFO_UTILS_H