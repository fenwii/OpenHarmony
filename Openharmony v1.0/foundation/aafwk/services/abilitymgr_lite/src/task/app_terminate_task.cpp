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

#include "app_terminate_task.h"

#include "ability_stack_manager.h"
#include "app_manager.h"

namespace OHOS {
AppTerminateTask::AppTerminateTask(AbilityMgrContext *context, const char *bundleName)
    : AbilityTask(context), bundleName_(bundleName)
{
}

AbilityMsStatus AppTerminateTask::Execute()
{
    PRINTD("AppTerminateTask", "start");
    if (abilityMgrContext_ == nullptr || bundleName_ == nullptr) {
        return AbilityMsStatus::TaskStatus("app terminate", "invalid argument");
    }

    // Step1: Stop process
    AbilityMsStatus status = AppManager::GetInstance().TerminateAppProcess(bundleName_);
    CHECK_RESULT(status);

    // Step2: Clear app MissionStack and AbilityRecord
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    stackManager.ClearAbilityStack(bundleName_, *abilityMgrContext_);

    // Step3: Active top ability
    auto topRecord = const_cast<PageAbilityRecord *>(stackManager.GetTopPageAbility(*abilityMgrContext_));
    if (topRecord != nullptr) {
        topRecord->ActiveAbility();
    }
    return AbilityMsStatus::Ok();
}
}  // namespace OHOS
