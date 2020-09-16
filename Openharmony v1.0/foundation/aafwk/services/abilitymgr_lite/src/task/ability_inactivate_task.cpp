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

#include "ability_inactivate_task.h"

namespace OHOS {
AbilityInactivateTask::AbilityInactivateTask(AbilityMgrContext *context, uint64_t token)
    : AbilityTask(context), token_(token)
{
}

AbilityMsStatus AbilityInactivateTask::Execute()
{
    PRINTD("AbilityInactivateTask", "start");
    if (abilityMgrContext_ == nullptr) {
        return AbilityMsStatus::TaskStatus("inactivate", "invalid argument");
    }
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    PageAbilityRecord *inactiveAbility = stackManager.FindPageAbility(*abilityMgrContext_, token_);
    if (inactiveAbility == nullptr) {
        return AbilityMsStatus::TaskStatus("inactivate", "ability record not found");
    }
    inactiveAbility->SetCurrentState(STATE_INACTIVE);
    PageAbilityRecord *nextAbility = const_cast<PageAbilityRecord *>(inactiveAbility->GetNextPageAbility());
    AbilityMsStatus status = AbilityMsStatus::Ok();
    if (inactiveAbility->GetAbilityInfo().abilityType == AbilityType::SERVICE) {
        if (inactiveAbility->GetConnectStatus() == ConnectStatus::WAIT_CONNECT) {
            PRINTD("AbilityInactivateTask", "perform connect");
            inactiveAbility->SetConnectStatus(ConnectStatus::CONNECTING);
            return inactiveAbility->ConnectAbility();
        }
        return status;
    }
    if (nextAbility != nullptr) {
        status = nextAbility->StartAbility();
        inactiveAbility->SetNextPageAbility(nullptr);
        PRINTD("AbilityInactivateTask", "next ability is not nullptr, active");
    } else {
        PageAbilityRecord *prevAbility = const_cast<PageAbilityRecord *>(
                stackManager.GetPrevPageAbility(*abilityMgrContext_, *inactiveAbility));
        if (prevAbility != nullptr) {
            status = prevAbility->ActiveAbility();
            prevAbility->SetNextPageAbility(inactiveAbility);
            PRINTD("AbilityInactivateTask", "prev ability is not nullptr, active");
        } else {
            inactiveAbility->StopAbility();
            status = AbilityMsStatus::NoActiveAbilityStatus("inactivate", "start launcher");
        }
    }
    return status;
}
}  // namespace OHOS
