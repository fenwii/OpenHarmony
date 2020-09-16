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

#ifndef OHOS_ABILITY_STACK_MANAGER_H
#define OHOS_ABILITY_STACK_MANAGER_H

#include <string>

#include "ability_mission_stack.h"
#include "ability_mgr_context.h"
#include "ability_info.h"
#include "bundle_info.h"
#include "nocopyable.h"
#include "want.h"

namespace OHOS {
class AbilityStackManager : public NoCopyable {
public:
    static AbilityStackManager &GetInstance()
    {
        static AbilityStackManager instance;
        return instance;
    };
    ~AbilityStackManager() = default;

    PageAbilityRecord *GeneratePageAbility(const AbilityInfo &target,
        const Want &want, const PageAbilityRecord *topAbility, AbilityMgrContext &amsContext) const;
    PageAbilityRecord *FindPageAbility(const AbilityMgrContext &amsContext, uint64_t token) const;
    const PageAbilityRecord *FindPageAbility(const AbilityMgrContext &amsContext, const Want &want) const;
    const PageAbilityRecord *GetTopPageAbility(const AbilityMgrContext &amsContext) const;
    const PageAbilityRecord *GetPrevPageAbility(const AbilityMgrContext &amsContext,
        const PageAbilityRecord &current) const;
    void RemovePageAbility(const PageAbilityRecord &target, AbilityMgrContext &amsContext);
    bool ExistAppInStack(const AbilityInfo &target, AbilityMgrContext &amsContext) const;
    void ClearAbilityStack(const char *bundleName, AbilityMgrContext &amsContext) const;
#ifdef OHOS_DEBUG
    AbilityMsStatus DumpAllAbilityRecord(const AbilityMgrContext &amsContext) const;
#endif
    PageAbilityRecord *FindServiceAbility(const AbilityMgrContext &amsContext, uint64_t token) const;
    PageAbilityRecord *FindServiceAbility(const AbilityMgrContext &amsContext, const char *bundleName,
        const char *abilityName) const;
private:
    AbilityStackManager() = default;
};
} // namespace OHOS
#endif // OHOS_ABILITY_STACK_MANAGER_H
