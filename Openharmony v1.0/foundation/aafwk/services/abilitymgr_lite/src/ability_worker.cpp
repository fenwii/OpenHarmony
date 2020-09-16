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

#include "ability_worker.h"

#include <inttypes.h>

#include "ability_activate_task.h"
#include "ability_attach_task.h"
#include "ability_background_task.h"
#include "ability_connect_done_task.h"
#include "ability_connect_task.h"
#include "ability_disconnect_done_task.h"
#include "ability_disconnect_task.h"
#include "ability_dump_task.h"
#include "ability_inactivate_task.h"
#include "ability_start_task.h"
#include "ability_stop_task.h"
#include "ability_terminate_service_task.h"
#include "ability_terminate_task.h"
#include "app_restart_task.h"
#include "app_terminate_task.h"
#include "util/abilityms_helper.h"

namespace OHOS {
AbilityWorker::AbilityWorker()
{
    abilityMgrContext_ = new AbilityMgrContext();
}

AbilityWorker::~AbilityWorker()
{
    delete abilityMgrContext_;
    abilityMgrContext_ = nullptr;
}

AbilityMsStatus AbilityWorker::StartAbility(const Want &want, const AbilityInfo &target,
    const BundleInfo &bundleInfo, pid_t callingUid)
{
    if (!AbilityMsHelper::CheckVisiblePermission(callingUid, bundleInfo.uid, target.isVisible)) {
        return AbilityMsStatus::PermissionStatus("start ability visible is false");
    }
    AbilityStartTask startTask(abilityMgrContext_, &want, &target, &bundleInfo);
    return startTask.Execute();
}

AbilityMsStatus AbilityWorker::AttachBundle(const AbilityThreadClient &client)
{
    PRINTD("AbilityWorker", "app token(%{private}" PRIu64 ")", client.GetToken());
    AbilityAttachTask attachTask(&client);
    return attachTask.Execute();
}

AbilityMsStatus AbilityWorker::TerminateAbility(uint64_t token)
{
    PRINTD("AbilityWorker", "ability token(%{private}" PRIu64 ")", token);
    AbilityTerminateTask terminateTask(abilityMgrContext_, token);
    return terminateTask.Execute();
}

AbilityMsStatus AbilityWorker::TerminateService(const AbilityInfo &target, const BundleInfo &bundleInfo,
    pid_t callingUid)
{
    if (!AbilityMsHelper::CheckVisiblePermission(callingUid, bundleInfo.uid, target.isVisible)) {
        return AbilityMsStatus::PermissionStatus("terminate service visible is false");
    }
    AbilityTerminateServiceTask terminateServiceTask(abilityMgrContext_, &target);
    return terminateServiceTask.Execute();
}

AbilityMsStatus AbilityWorker::AbilityTransaction(const TransactionState &state)
{
    PRINTD("AbilityWorker", "ability token(%{private}" PRIu64 "), state(%{public}d)", state.token, state.state);
    AbilityTask *task = nullptr;
    switch (state.state) {
        case STATE_BACKGROUND:
            task = new AbilityBackgroundTask(abilityMgrContext_, state.token);
            break;
        case STATE_INACTIVE:
            task = new AbilityInactivateTask(abilityMgrContext_, state.token);
            break;
        case STATE_ACTIVE:
            task = new AbilityActivateTask(abilityMgrContext_, state.token);
            break;
        case STATE_INITIAL:
            task = new AbilityStopTask(abilityMgrContext_, state.token);
            break;
        default:
            break;
    }
    AbilityMsStatus status = (task != nullptr) ? task->Execute() : AbilityMsStatus();
    delete task;
    return status;
}

AbilityMsStatus AbilityWorker::TerminateApp(const char *bundleName)
{
    AppTerminateTask appTerminateTask(abilityMgrContext_, bundleName);
    return appTerminateTask.Execute();
}

AbilityMsStatus AbilityWorker::RestartApp(const BundleInfo &bundleInfo)
{
    AppRestartTask restartTask(abilityMgrContext_, &bundleInfo);
    return restartTask.Execute();
}

AbilityMsStatus AbilityWorker::ConnectAbility(const AbilityConnectTransParam &connectParam,
    const AbilityInfo &target, const BundleInfo &bundleInfo)
{
    if (!AbilityMsHelper::CheckVisiblePermission(connectParam.GetCallingUid(), bundleInfo.uid, target.isVisible)) {
        return AbilityMsStatus::PermissionStatus("connect ability visibale is false");
    }
    if (abilityMgrContext_ == nullptr) {
        return AbilityMsStatus::TaskStatus("connect", "invalid argument");
    }
    auto serviceConnects = abilityMgrContext_->GetServiceConnects();
    if (serviceConnects == nullptr) {
        return AbilityMsStatus::TaskStatus("connect", "invalid argument");
    }
    if (connectParam.GetWant() == nullptr || connectParam.GetWant()->element == nullptr) {
        return AbilityMsStatus::TaskStatus("connect", "invalid argument");
    }
    char *bundleName = connectParam.GetWant()->element->bundleName;
    char *abilityName = connectParam.GetWant()->element->abilityName;
    auto abilityRecord = serviceConnects->FindServiceRecord(bundleName, abilityName);
    if (abilityRecord == nullptr) {
        PRINTD("AbilityWorker", "ability start first");
        AbilityStartTask startTask(abilityMgrContext_, connectParam.GetWant(), &target, &bundleInfo);
        startTask.SetWaitConnect(true);
        AbilityMsStatus status = startTask.Execute();
        if (!status.IsOk()) {
            return status;
        }
    } else {
        PRINTD("AbilityWorker", "ability has started");
    }
    abilityRecord = serviceConnects->FindServiceRecord(bundleName, abilityName);
    if (abilityRecord == nullptr) {
        return AbilityMsStatus::TaskStatus("connect", "generate ability record failure");
    }
    AbilityConnectTask connectTask(abilityMgrContext_, *connectParam.GetWant(),
            connectParam.GetSvcIdentity(), connectParam.GetToken());
    AbilityMsStatus status = connectTask.Execute();
    return status;
}

AbilityMsStatus AbilityWorker::DisconnectAbility(const SvcIdentity &identity, uint64_t token)
{
    AbilityDisconnectTask disconnectTask(abilityMgrContext_, identity, token);
    return disconnectTask.Execute();
}

AbilityMsStatus AbilityWorker::ConnectAbilityDone(const SvcIdentity &identity, uint64_t token)
{
    AbilityConnectDoneTask connectDoneTask(abilityMgrContext_, identity, token);
    return connectDoneTask.Execute();
}

AbilityMsStatus AbilityWorker::DisconnectAbilityDone(uint64_t token)
{
    AbilityDisconnectDoneTask connectDoneTask(abilityMgrContext_, token);
    return connectDoneTask.Execute();
}

AbilityMsStatus AbilityWorker::DumpAbility(const AbilityDumpClient &client)
{
    AbilityDumpTask dumpTask(abilityMgrContext_, &client);
    return dumpTask.Execute();
}
}  // namespace OHOS
