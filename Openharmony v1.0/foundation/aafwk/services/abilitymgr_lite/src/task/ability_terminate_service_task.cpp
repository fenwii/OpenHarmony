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

#include "ability_terminate_service_task.h"

#include "ability_stack_manager.h"

namespace OHOS {
AbilityTerminateServiceTask::AbilityTerminateServiceTask(AbilityMgrContext *context, const AbilityInfo *target)
    : AbilityTask(context), target_(target)
{
}

AbilityTerminateServiceTask::~AbilityTerminateServiceTask()
{
    target_ = nullptr;
}

AbilityMsStatus AbilityTerminateServiceTask::Execute()
{
    PRINTD("AbilityTerminateServiceTask", "start");
    if (abilityMgrContext_ == nullptr || target_ == nullptr) {
        return AbilityMsStatus::TaskStatus("terminateService", "invalid argument");
    }
    auto serviceConnects = abilityMgrContext_->GetServiceConnects();
    if (serviceConnects == nullptr) {
        return AbilityMsStatus::TaskStatus("terminateService", "invalid argument");
    }
    auto service = serviceConnects->FindServiceRecord(target_->bundleName, target_->name);
    if (service == nullptr) {
        return AbilityMsStatus::TaskStatus("terminateService", "service does not exists");
    }
    if (service->GetCurrentState() == STATE_UNINITIALIZED) {
        uint64_t token = service->GetToken();
        const_cast<AbilityConnectMission *>(serviceConnects)->RemoveServiceRecord(token);
        return AbilityMsStatus::Ok();
    }
    return service->ForceStopServiceAbility();
}
}  // namespace OHOS
