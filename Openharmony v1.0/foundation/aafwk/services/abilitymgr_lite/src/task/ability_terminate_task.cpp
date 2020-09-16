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

#include "ability_terminate_task.h"

#include "ability_stack_manager.h"

namespace OHOS {
AbilityTerminateTask::AbilityTerminateTask(AbilityMgrContext *context, uint64_t token)
    : AbilityTask(context), token_(token)
{
}

AbilityMsStatus AbilityTerminateTask::Execute()
{
    PRINTD("AbilityTerminateTask", "start");
    if (abilityMgrContext_ == nullptr) {
        return AbilityMsStatus::TaskStatus("ability terminate", "invalid argument");
    }
    // Step1: Get ability record from stack
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    PageAbilityRecord *terminateAbility = stackManager.FindPageAbility(*abilityMgrContext_, token_);
    if (terminateAbility == nullptr) {
        return AbilityMsStatus::TaskStatus("ability terminate", "ability record not find");
    }
    if (terminateAbility->GetAbilityInfo().abilityType == AbilityType::SERVICE) {
        return terminateAbility->ForceStopServiceAbility();
    } else {
        // Step2: Inactive ability record
        return terminateAbility->InactiveAbility();
    }
}
}  // namespace OHOS
