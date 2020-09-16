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

#include "ability_attach_task.h"

#include "app_manager.h"

namespace OHOS {
AbilityAttachTask::AbilityAttachTask(const AbilityThreadClient *client)
    : client_(client)
{
}

AbilityAttachTask::~AbilityAttachTask()
{
    client_ = nullptr;
}

AbilityMsStatus AbilityAttachTask::Execute()
{
    PRINTD("AbilityAttachTask", "start");
    if (client_ == nullptr) {
        return AbilityMsStatus::TaskStatus("Attach", "invalid argument");
    }
    // step1: Get app record by token.
    auto appRecord = const_cast<AppRecord *>(AppManager::GetInstance().GetAppRecordByToken(
        client_->GetToken(), client_->GetPid()));
    if (appRecord == nullptr) {
        return AbilityMsStatus::TaskStatus("Attach", "appRecord not found");
    }
    // step2: Save ability thread client.
    AbilityMsStatus status = appRecord->SetAbilityThreadClient(*client_);
    CHECK_RESULT(status);

    // step3: Load permission
    status = appRecord->LoadPermission();
    if (!status.IsOk()) {
        AppManager::GetInstance().RemoveAppRecord(*appRecord);
        return status;
    }

    // step4: Init app
    status = appRecord->AppInitTransaction();
    CHECK_RESULT(status);

    // step5: Launch pending ability.
    return appRecord->LaunchPendingAbility();
}
}  // namespace OHOS
