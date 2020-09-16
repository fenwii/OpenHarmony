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

#ifndef OHOS_ABILITY_SLICE_MANAGER_H
#define OHOS_ABILITY_SLICE_MANAGER_H

#include <ability.h>
#include <ability_slice.h>

namespace OHOS {
class AbilitySliceScheduler;

class AbilitySliceManager {
public:
    explicit AbilitySliceManager(Ability &ability);
    ~AbilitySliceManager();

    void OnAbilityStart(const Want &want);
    void OnAbilityInactive();
    void OnAbilityActive(const Want &want);
    void OnAbilityBackground();
    void OnAbilityStop();

    void Present(const AbilitySlice &caller, AbilitySlice &target, const Want &want);
    void Terminate(AbilitySlice &slice);

    void SetMainRoute(const std::string &entry);
    void AddActionRoute(const std::string &action, const std::string &entry);

    void SetUIContent(RootView *rootView);
    int GetAbilityState();

    int TerminateAbility();

    std::string GetSliceStackInfo() const;

    uint64_t GetToken() const;

private:
    AbilitySliceScheduler *abilitySliceScheduler_ { nullptr };
    Ability &ability_;
};
} // namespace OHOS

#endif // OHOS_ABILITY_SLICE_MANAGER_H