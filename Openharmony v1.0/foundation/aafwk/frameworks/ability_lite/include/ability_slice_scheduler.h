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

#ifndef OHOS_ABILITY_SLICE_SCHEDULER_H
#define OHOS_ABILITY_SLICE_SCHEDULER_H

#include <want.h>

#include "ability_slice_manager.h"
#include "ability_slice_route.h"
#include "ability_slice_stack.h"

namespace OHOS {
class AbilitySliceScheduler {
public:
    explicit AbilitySliceScheduler(AbilitySliceManager &abilitySliceManager);
    ~AbilitySliceScheduler();

    void HandleStartAbilitySlice(const Want &want);
    void HandleInactiveAbilitySlice();
    void HandleActiveAbilitySlice(const Want &want);
    void HandleMoveAbilitySliceToBackground();
    void HandleStopAbilitySlice();

    void AddAbilitySlice(const AbilitySlice &caller, AbilitySlice &target, const Want &want);
    void RemoveAbilitySlice(AbilitySlice &slice);

    void SetMainRoute(const std::string &entry);
    void AddActionRoute(const std::string &action, const std::string &entry);

    const std::string GetSliceStackInfo() const;
private:
    AbilitySlice *GetTargetAbilitySlice() const;
    bool CheckLegalForAdd(const AbilitySlice &caller, AbilitySlice &target, const Want &want);
    bool CheckLegalForRemove(const AbilitySlice &slice);

    AbilitySliceRoute *abilitySliceRoute_ { nullptr };
    AbilitySliceStack *abilitySliceStack_ { nullptr };
    AbilitySlice *topAbilitySlice_ { nullptr };
    AbilitySliceManager &abilitySliceManager_;
};
} // namespace OHOS

#endif // OHOS_ABILITY_SLICE_SCHEDULER_H

