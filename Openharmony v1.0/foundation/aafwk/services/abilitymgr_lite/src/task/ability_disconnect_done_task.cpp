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

#include "ability_disconnect_done_task.h"

namespace OHOS {
AbilityDisconnectDoneTask::AbilityDisconnectDoneTask(AbilityMgrContext *context, uint64_t token)
    : AbilityTask(context), token_(token)
{
}

AbilityMsStatus AbilityDisconnectDoneTask::Execute()
{
    PRINTD("AbilityDisconnectDoneTask", "start");
    if (abilityMgrContext_ == nullptr) {
        return AbilityMsStatus::TaskStatus("disconnectTaskDone", "invalid argument");
    }
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    PageAbilityRecord *service = stackManager.FindServiceAbility(*abilityMgrContext_, token_);
    if (service == nullptr) {
        return AbilityMsStatus::TaskStatus("disconnectTaskDone", "service ability does not exists");
    }
    if (service->IsPerformStop()) {
        return AbilityMsStatus::TaskStatus("disconnectTaskDone", "service is stopping");
    }
    return service->DisconnectAbilityDone();
}
}  // namespace OHOS
