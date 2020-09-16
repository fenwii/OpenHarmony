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

#include "ability_slice_scheduler.h"

#include <ability_state.h>
#include <log.h>

#include "ability_loader.h"
#include "ability_slice_manager.h"

namespace OHOS {
AbilitySliceScheduler::AbilitySliceScheduler(AbilitySliceManager &abilitySliceManager)
    : abilitySliceManager_(abilitySliceManager)
{
    abilitySliceRoute_ = new AbilitySliceRoute();
    abilitySliceStack_ = new AbilitySliceStack();
}

AbilitySliceScheduler::~AbilitySliceScheduler()
{
    delete abilitySliceRoute_;
    abilitySliceRoute_ = nullptr;
    delete abilitySliceStack_;
    abilitySliceStack_ = nullptr;
}

void AbilitySliceScheduler::HandleStartAbilitySlice(const Want &want)
{
    if (topAbilitySlice_ == nullptr) {
        topAbilitySlice_ = GetTargetAbilitySlice();
        if (topAbilitySlice_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "Cannot get slice [%{public}s]", abilitySliceRoute_->GetMainRoute().c_str());
            return;
        }
    }
    topAbilitySlice_->Init(abilitySliceManager_);

    topAbilitySlice_->OnStart(want);
}

void AbilitySliceScheduler::HandleInactiveAbilitySlice()
{
    if (topAbilitySlice_ == nullptr) {
        return;
    }

    topAbilitySlice_->OnInactive();
}

void AbilitySliceScheduler::HandleActiveAbilitySlice(const Want &want)
{
    if (topAbilitySlice_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "top ability slice is null, active slice error");
        return;
    }

    // add want when implicit match, not support jump by want temporary.

    topAbilitySlice_->OnActive(want);
}

void AbilitySliceScheduler::HandleMoveAbilitySliceToBackground()
{
    if (topAbilitySlice_ == nullptr) {
        return;
    }

    topAbilitySlice_->OnBackground();
}

void AbilitySliceScheduler::HandleStopAbilitySlice()
{
    if (topAbilitySlice_ == nullptr) {
        return;
    }

    topAbilitySlice_->OnStop();
    while (!abilitySliceStack_->IsEmpty()) {
        auto abilitySlice = abilitySliceStack_->Pop();
        if (abilitySlice != nullptr) {
            abilitySlice->OnStop();
        }
    }
    delete topAbilitySlice_;
    topAbilitySlice_ = nullptr;
}

void AbilitySliceScheduler::AddAbilitySlice(const AbilitySlice &caller, AbilitySlice &target, const Want &want)
{
    // Check if this jump is legal.
    if (!CheckLegalForAdd(caller, target, want)) {
        HILOG_WARN(HILOG_MODULE_APP, "Cannot jump to target AbilitySlice");
        return;
    }

    // Scheduler top slice to inactive.
    if (topAbilitySlice_->GetState() == STATE_ACTIVE) {
        topAbilitySlice_->OnInactive();
    }

    // Scheduler target slice to Active.
    if (target.GetState() == STATE_UNINITIALIZED) {
        target.Init(abilitySliceManager_);
    }
    if (target.GetState() == STATE_INITIAL) {
        target.OnStart(want);
    }
    target.OnActive(want);

    // Scheduler top slice to background.
    if (topAbilitySlice_->GetState() == STATE_INACTIVE) {
        topAbilitySlice_->OnBackground();
    }

    // Update the topAbilitySlice and stack.
    abilitySliceStack_->Push(topAbilitySlice_);
    topAbilitySlice_ = &target;
}

void AbilitySliceScheduler::RemoveAbilitySlice(AbilitySlice &slice)
{
    // Check if this slice is legal.
    if (!CheckLegalForRemove(slice)) {
        HILOG_WARN(HILOG_MODULE_APP, "Cannot terminate target AbilitySlice");
        return;
    }

    if (&slice == topAbilitySlice_) {
        // Scheduler the slice need to exit to inactive.
        topAbilitySlice_->OnInactive();

        Want want { nullptr, nullptr, nullptr, 0 };
        // Scheduler the top slice in the stack to Active.
        auto next = abilitySliceStack_->Pop();
        if (next == nullptr) {
            topAbilitySlice_->OnActive(want);
            return;
        }
        next->OnActive(want);

        // Scheduler the slice need to exit(State:initial).
        topAbilitySlice_->OnBackground();
        topAbilitySlice_->OnStop();

        // Update the topAbilitySLice and stack.
        topAbilitySlice_ = next;
    } else {
        // Scheduler the background slice to stop
        slice.OnStop();
        abilitySliceStack_->Remove(&slice);
    }
}

void AbilitySliceScheduler::SetMainRoute(const std::string &entry)
{
    abilitySliceRoute_->SetMainRoute(entry);
}

void AbilitySliceScheduler::AddActionRoute(const std::string &action, const std::string &entry)
{
    abilitySliceRoute_->AddActionRoute(action, entry);
}

AbilitySlice *AbilitySliceScheduler::GetTargetAbilitySlice() const
{
    std::string mainEntry = abilitySliceRoute_->GetMainRoute();

    return AbilityLoader::GetInstance().GetAbilitySliceByName(mainEntry);
}

bool AbilitySliceScheduler::CheckLegalForAdd(const AbilitySlice &caller, AbilitySlice &target, const Want &want)
{
    if (topAbilitySlice_ == nullptr) {
        return false;
    }
    if (abilitySliceManager_.GetAbilityState() != STATE_ACTIVE) {
        return false;
    }
    if (caller.GetState() <= STATE_INITIAL) {
        return false;
    }
    if (target.GetState() == STATE_ACTIVE) {
        return false;
    }
    if (&target == topAbilitySlice_) {
        return false;
    }

    return true;
}

bool AbilitySliceScheduler::CheckLegalForRemove(const AbilitySlice &slice)
{
    if (topAbilitySlice_ == nullptr) {
        return false;
    }
    if (abilitySliceManager_.GetAbilityState() != STATE_ACTIVE) {
        return false;
    }
    if ((!abilitySliceStack_->Exist(&slice)) && (&slice != topAbilitySlice_)) {
        return false;
    }
    if (slice.GetState() <= STATE_INITIAL) {
        return false;
    }
    if (abilitySliceStack_->IsEmpty()) {
        abilitySliceManager_.TerminateAbility();
        return false;
    }

    return true;
}

const std::string AbilitySliceScheduler::GetSliceStackInfo() const
{
    if (topAbilitySlice_ == nullptr) {
        return "    none";
    }
    std::string buff;
    buff += "    [" + std::string(typeid(*topAbilitySlice_).name()) +
        "] State: [" + std::to_string(topAbilitySlice_->GetState()) + "]\n";
    auto slices = abilitySliceStack_->GetAllSlices();
    for (auto slice : slices) {
        buff += "    [" + std::string(typeid(*slice).name()) + "] State: [" + std::to_string(slice->GetState()) + "]\n";
    }
    return buff;
}
} // namespace OHOS