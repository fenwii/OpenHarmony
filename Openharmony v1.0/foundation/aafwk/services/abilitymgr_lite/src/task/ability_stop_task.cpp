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

#include "ability_stop_task.h"

namespace OHOS {
AbilityStopTask::AbilityStopTask(AbilityMgrContext *context, uint64_t token)
    : AbilityTask(context), token_(token)
{
}

AbilityMsStatus AbilityStopTask::Execute()
{
    PRINTD("AbilityStopTask", "start");
    if (abilityMgrContext_ == nullptr) {
        return AbilityMsStatus::TaskStatus("stop", "invalid argument");
    }
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    // Step 1: Find stop ability record.
    PageAbilityRecord *stopAbility = stackManager.FindPageAbility(*abilityMgrContext_, token_);
    if (stopAbility == nullptr) {
        return AbilityMsStatus::TaskStatus("stop", "ability record not found");
    }
    auto serviceConnects = const_cast<AbilityConnectMission *>(abilityMgrContext_->GetServiceConnects());
    if (serviceConnects == nullptr) {
        return AbilityMsStatus::TaskStatus("stop", "invalid argument");
    }
    stopAbility->SetCurrentState(STATE_INITIAL);
    if (stopAbility->GetAbilityInfo().abilityType == AbilityType::SERVICE) {
        if (stopAbility->GetConnectStatus() == ConnectStatus::STOPPED) {
            return AbilityMsStatus::TaskStatus("stop", "service has stopped");
        }
        AbilityMsStatus status = stopAbility->StopAbilityDone();
        bool existsPage = stackManager.ExistAppInStack(stopAbility->GetAbilityInfo(), *abilityMgrContext_);
        int32_t count = serviceConnects->CountServiceInApp(stopAbility->GetAbilityInfo().bundleName);
        if (!existsPage && count == 1) {
            PRINTI("AbilityStopTask", "exit app");
            status = stopAbility->ExitApp();
        }
        serviceConnects->RemoveServiceRecord(token_);
        return status;
    } else {
        // Step 2: Ability is bottom in MissionRecord
        AbilityMsStatus status = AbilityMsStatus::Ok();
        if (stopAbility->IsBottomPageAbility() &&
            serviceConnects->CountServiceInApp(stopAbility->GetAbilityInfo().bundleName) == 0) {
            // exit process
            status = stopAbility->ExitApp();
        }
        // Step 3: Delete ability from stack
        stackManager.RemovePageAbility(*stopAbility, *abilityMgrContext_);
        return status;
    }
}
}  // namespace OHOS
