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

#include "ability_slice_manager.h"

#include <ability.h>

#include "ability_slice_scheduler.h"
#include "ability_window.h"

namespace OHOS {
AbilitySliceManager::AbilitySliceManager(Ability &ability) : ability_(ability)
{
    abilitySliceScheduler_ = new AbilitySliceScheduler(*this);
}

AbilitySliceManager::~AbilitySliceManager()
{
    delete abilitySliceScheduler_;
    abilitySliceScheduler_ = nullptr;
}

void AbilitySliceManager::OnAbilityStart(const Want &want)
{
    abilitySliceScheduler_->HandleStartAbilitySlice(want);
}

void AbilitySliceManager::OnAbilityInactive()
{
    abilitySliceScheduler_->HandleInactiveAbilitySlice();
}

void AbilitySliceManager::OnAbilityActive(const Want &want)
{
    abilitySliceScheduler_->HandleActiveAbilitySlice(want);
}

void AbilitySliceManager::OnAbilityBackground()
{
    abilitySliceScheduler_->HandleMoveAbilitySliceToBackground();
}

void AbilitySliceManager::OnAbilityStop()
{
    abilitySliceScheduler_->HandleStopAbilitySlice();
}

void AbilitySliceManager::Present(const AbilitySlice &caller, AbilitySlice &target, const Want &want)
{
    abilitySliceScheduler_->AddAbilitySlice(caller, target, want);
}

void AbilitySliceManager::Terminate(AbilitySlice &slice)
{
    abilitySliceScheduler_->RemoveAbilitySlice(slice);
}

void AbilitySliceManager::SetMainRoute(const std::string &entry)
{
    abilitySliceScheduler_->SetMainRoute(entry);
}

void AbilitySliceManager::AddActionRoute(const std::string &action, const std::string &entry)
{
    abilitySliceScheduler_->AddActionRoute(action, entry);
}

void AbilitySliceManager::SetUIContent(RootView *rootView)
{
    ability_.SetUIContent(rootView);
}

int AbilitySliceManager::GetAbilityState()
{
    return ability_.GetState();
}

int AbilitySliceManager::TerminateAbility()
{
    return ability_.TerminateAbility();
}

std::string AbilitySliceManager::GetSliceStackInfo() const
{
    return abilitySliceScheduler_->GetSliceStackInfo();
}

uint64_t AbilitySliceManager::GetToken() const
{
    return ability_.token_;
}
} // namespace OHOS