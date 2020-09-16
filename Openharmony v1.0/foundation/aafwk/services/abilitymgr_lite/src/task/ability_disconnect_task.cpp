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

#include "ability_disconnect_task.h"

namespace OHOS {
AbilityDisconnectTask::AbilityDisconnectTask(AbilityMgrContext *context, const SvcIdentity &identity,
    uint64_t token) : AbilityTask(context), identity_(identity), token_(token)
{
}

AbilityMsStatus AbilityDisconnectTask::Execute()
{
    PRINTD("AbilityDisconnectTask", "start");
    if (abilityMgrContext_ == nullptr) {
        return AbilityMsStatus::TaskStatus("disconnectTask", "invalid argument");
    }
    auto serviceConnects = abilityMgrContext_->GetServiceConnects();
    if (serviceConnects == nullptr) {
        return AbilityMsStatus::TaskStatus("disconnectTask", "invalid argument");
    }
    auto service = serviceConnects->FindServiceRecord(identity_, token_);
    if (service == nullptr) {
        return AbilityMsStatus::TaskStatus("disconnectTask", "service is not exists");
    }
    return service->DisconnectAbility(identity_);
}
}  // namespace OHOS
