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

#include "ability_background_task.h"

namespace OHOS {
AbilityBackgroundTask::AbilityBackgroundTask(AbilityMgrContext *context, uint64_t token)
    : AbilityTask(context), token_(token)
{
}

AbilityMsStatus AbilityBackgroundTask::Execute()
{
    PRINTD("AbilityBackgroundTask", "start");
    if (abilityMgrContext_ == nullptr) {
        return AbilityMsStatus::TaskStatus("background", "invalid argument");
    }
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    PageAbilityRecord *backgroundAbility = stackManager.FindPageAbility(*abilityMgrContext_, token_);
    if (backgroundAbility == nullptr) {
        return AbilityMsStatus::TaskStatus("background", "ability record not find");
    }
    backgroundAbility->SetCurrentState(STATE_BACKGROUND);
    return AbilityMsStatus::Ok();
}
}  // namespace OHOS
