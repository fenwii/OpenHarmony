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

#include "ability_info.h"

#include "utils.h"

void ClearAbilityInfo(AbilityInfo *abilityInfo)
{
    if (abilityInfo == nullptr) {
        return;
    }
    AdapterFree(abilityInfo->bundleName);
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    AdapterFree(abilityInfo->moduleName);
    AdapterFree(abilityInfo->name);
    AdapterFree(abilityInfo->description);
    AdapterFree(abilityInfo->iconPath);
    AdapterFree(abilityInfo->deviceId);
    AdapterFree(abilityInfo->label);
#else
    AdapterFree(abilityInfo->srcPath);
#endif
}