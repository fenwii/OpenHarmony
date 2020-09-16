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

#include "ability_dump_task.h"

namespace OHOS {
AbilityDumpTask::AbilityDumpTask(AbilityMgrContext *context, const AbilityDumpClient *client)
    : AbilityTask(context), client_(client)
{
}

AbilityMsStatus AbilityDumpTask::Execute()
{
    PRINTD("AbilityDumpTask", "start");
    if (abilityMgrContext_ == nullptr || client_ == nullptr) {
        return AbilityMsStatus::TaskStatus("dump", "invalid argument");
    }
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    if (client_->GetWant().element != nullptr) {
        // If query target ability
        const PageAbilityRecord *targetAbility =
            stackManager.FindPageAbility(*abilityMgrContext_, client_->GetWant());
        if (targetAbility == nullptr) {
            return client_->AbilityDumpTransaction("Ability not found\n");
        }
        return targetAbility->DumpAbilitySlice(client_->GetWant());
    } else {
        // Query all ability
#ifdef OHOS_DEBUG
        AbilityMsStatus status = stackManager.DumpAllAbilityRecord(*abilityMgrContext_);
        return client_->AbilityDumpTransaction(status.Dump());
#else
        return client_->AbilityDumpTransaction("Dump is not available in release\n");
#endif
    }
}
}  // namespace OHOS
