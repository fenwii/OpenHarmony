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

#include "app_restart_task.h"

#include "ability_stack_manager.h"
#include "app_manager.h"
#include "util/abilityms_helper.h"

namespace OHOS {
AppRestartTask::AppRestartTask(AbilityMgrContext *context, const BundleInfo *bundleInfo)
    : AbilityTask(context), bundleInfo_(bundleInfo)
{
}

AbilityMsStatus AppRestartTask::Execute()
{
    PRINTD("AppRestartTask", "start");
    if (abilityMgrContext_ == nullptr || bundleInfo_ == nullptr || bundleInfo_->bundleName == nullptr) {
        return AbilityMsStatus::TaskStatus("app terminate", "invalid argument");
    }

    // Step1: Remove app record
    AppManager::GetInstance().RemoveAppRecord(bundleInfo_->bundleName);

    // Step2: Clear app MissionStack and AbilityRecord
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    stackManager.ClearAbilityStack(bundleInfo_->bundleName, *abilityMgrContext_);

    // Step3: Get top page ability
    auto topRecord = const_cast<PageAbilityRecord *>(stackManager.GetTopPageAbility(*abilityMgrContext_));
    if (topRecord == nullptr) {
        return AbilityMsStatus::NoActiveAbilityStatus("restart app", "start launcher");
    } else {
        // Step4: Active top ability
        topRecord->ActiveAbility();
    }
    return AbilityMsStatus::Ok();
}
}  // namespace OHOS
