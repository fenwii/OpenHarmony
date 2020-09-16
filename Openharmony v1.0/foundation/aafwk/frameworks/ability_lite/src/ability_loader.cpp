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

#include "ability_loader.h"
#include "log.h"

namespace OHOS {
void AbilityLoader::RegisterAbility(const std::string &abilityName, const CreateAblity &createFunc)
{
    abilities_.emplace(abilityName, createFunc);
    HILOG_INFO(HILOG_MODULE_APP, "RegisterAbility %s", abilityName.c_str());
}

Ability *AbilityLoader::GetAbilityByName(const std::string &abilityName)
{
    auto it = abilities_.find(abilityName);
    if (it == abilities_.end()) {
        HILOG_ERROR(HILOG_MODULE_APP, "GetAbilityByName failed: %s", abilityName.c_str());
        return nullptr;
    } else {
        return it->second();
    }
}

#ifdef ABILITY_WINDOW_SUPPORT
void AbilityLoader::RegisterAbilitySlice(const std::string &sliceName, const CreateSlice &createFunc)
{
    slices_.emplace(sliceName, createFunc);
    HILOG_INFO(HILOG_MODULE_APP, "RegisterAbilitySlice %s", sliceName.c_str());
}

AbilitySlice *AbilityLoader::GetAbilitySliceByName(const std::string &sliceName)
{
    auto it = slices_.find(sliceName);
    if (it == slices_.end()) {
        HILOG_ERROR(HILOG_MODULE_APP, "GetAbilitySliceByName failed: %s", sliceName.c_str());
        return nullptr;
    } else {
        return it->second();
    }
}
#endif
} //  namespace OHOS