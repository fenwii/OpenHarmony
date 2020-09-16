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

#include "ability_activate_task.h"

namespace OHOS {
AbilityActivateTask::AbilityActivateTask(AbilityMgrContext *context, uint64_t token)
    : AbilityTask(context), token_(token)
{
}

AbilityMsStatus AbilityActivateTask::Execute()
{
    PRINTD("AbilityActivateTask", "start");
    if (abilityMgrContext_ == nullptr) {
        return AbilityMsStatus::TaskStatus("activate", "invalid argument");
    }
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    PageAbilityRecord *activeAbility = stackManager.FindPageAbility(*abilityMgrContext_, token_);
    if (activeAbility == nullptr) {
        return AbilityMsStatus::TaskStatus("activate", "ability record not found");
    }
    activeAbility->SetCurrentState(STATE_ACTIVE);
    auto prevAbility = const_cast<PageAbilityRecord *>(activeAbility->GetPrevPageAbility());
    AbilityMsStatus status = AbilityMsStatus::Ok();
    if (activeAbility->GetAbilityInfo().abilityType == AbilityType::SERVICE) {
        return status;
    }
    if (prevAbility != nullptr) {
        status = prevAbility->ToBackgroundAbility();
        activeAbility->SetPrevPageAbility(nullptr);
        PRINTD("AbilityActivateTask", "prev ability is not nullptr, to background");
    } else {
        auto nextAbility = const_cast<PageAbilityRecord *>(activeAbility->GetNextPageAbility());
        if (nextAbility != nullptr) {
            status = nextAbility->StopAbility();
            activeAbility->SetNextPageAbility(nullptr);
            PRINTD("AbilityActivateTask", "next ability is not nullptr, to stop");
        }
    }
    return status;
}
}  // namespace OHOS
