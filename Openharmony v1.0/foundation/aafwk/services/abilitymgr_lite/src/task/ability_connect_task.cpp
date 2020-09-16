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

#include "ability_connect_task.h"

#include "ability_connect_record.h"
#include "utils.h"

namespace OHOS {
AbilityConnectTask::AbilityConnectTask(AbilityMgrContext *context, const Want &want, const SvcIdentity& identity,
    uint64_t token) : AbilityTask(context), want_(want), connectSid_(identity), token_(token)
{
}

AbilityMsStatus AbilityConnectTask::Execute()
{
    PRINTD("AbilityConnectTask", "start");
    if (abilityMgrContext_ == nullptr || want_.element == nullptr) {
        return AbilityMsStatus::TaskStatus("connectTask", "invalid argument");
    }
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    PageAbilityRecord *service = stackManager.FindServiceAbility(*abilityMgrContext_,
        want_.element->bundleName, want_.element->abilityName);
    if (service == nullptr) {
        return AbilityMsStatus::TaskStatus("connectTask", "service ability does not exists");
    }
    if (service->IsPerformStop()) {
        return AbilityMsStatus::TaskStatus("connectTask", "service has stopped");
    }
    return PerformConnectTask(service);
}

AbilityMsStatus AbilityConnectTask::PerformConnectTask(PageAbilityRecord *service)
{
    ConnectStatus serviceConnectStatus = service->GetConnectStatus();
    if (serviceConnectStatus == ConnectStatus::DISCONNECTING || serviceConnectStatus == ConnectStatus::DISCONNECT ||
        serviceConnectStatus == ConnectStatus::STOPPING || serviceConnectStatus == ConnectStatus::STOPPED) {
        PRINTW("AbilityConnectTask", "service status has disconnected");
        return AbilityMsStatus::TaskStatus("AbilityConnectTask", "service status has disconnected");
    }
    auto connectRecord = service->GetConnectRecord(connectSid_);
    if (connectRecord == nullptr) {
        connectRecord = new AbilityConnectRecord(connectSid_, token_);
        connectRecord->SetStatus(ConnectStatus::CONNECTING);
        service->pushConnectRecord(connectRecord);
    }
    AbilityMsStatus abilityMsStatus = AbilityMsStatus::Ok();
    switch (serviceConnectStatus) {
        case ConnectStatus::INIT: {
            if (service->GetCurrentState() == STATE_UNINITIALIZED) {
                PRINTI("AbilityConnectTask", "service status is initializing, waiting connecting");
                service->SetConnectStatus(ConnectStatus::WAIT_CONNECT);
            } else {
                PRINTI("AbilityConnectTask", "service status is init, connection is connecting");
                service->SetConnectStatus(ConnectStatus::CONNECTING);
                abilityMsStatus = service->ConnectAbility();
            }
            break;
        }
        case ConnectStatus::CONNECTED:
        {
            if (connectRecord->GetStatus() == ConnectStatus::CONNECTING) {
                PRINTI("AbilityConnectTask", "service status has connected, connection is connecting");
                abilityMsStatus = service->ConnectAbilityDone();
            } else {
                PRINTI("AbilityConnectTask", "connection has connected");
            }
            break;
        }
        default:
            break;
    }
    return abilityMsStatus;
}
}  // namespace OHOS
