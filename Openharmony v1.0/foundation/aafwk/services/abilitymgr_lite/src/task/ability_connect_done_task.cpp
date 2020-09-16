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

#include "ability_connect_done_task.h"

namespace OHOS {
AbilityConnectDoneTask::AbilityConnectDoneTask(AbilityMgrContext *context, const SvcIdentity &serviceSid,
    uint64_t token) : AbilityTask(context), serviceSid_(serviceSid), token_(token)
{
}

AbilityMsStatus AbilityConnectDoneTask::Execute()
{
    PRINTD("AbilityConnectDoneTask", "start");
    if (abilityMgrContext_ == nullptr) {
        return AbilityMsStatus::TaskStatus("connectTaskDone", "invalid argument");
    }
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    PageAbilityRecord *service = stackManager.FindServiceAbility(*abilityMgrContext_, token_);
    if (service == nullptr) {
        return AbilityMsStatus::TaskStatus("connectTaskDone", "service ability dose not exists");
    }
    if (service->IsPerformStop()) {
        return AbilityMsStatus::TaskStatus("connectTaskDone", "service is stopping");
    }
    service->SetServiceSid(serviceSid_);
    AbilityMsStatus status = service->ConnectAbilityDone();
    service->SetConnectStatus(ConnectStatus::CONNECTED);
    return status;
}
}  // namespace OHOS
