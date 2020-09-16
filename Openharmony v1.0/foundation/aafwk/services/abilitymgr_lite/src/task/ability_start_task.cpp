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

#include "ability_start_task.h"

#include "ability_stack_manager.h"

namespace OHOS {
AbilityStartTask::AbilityStartTask(AbilityMgrContext *context, const Want *want,
    const AbilityInfo *target, const BundleInfo *bundleInfo)
    : AbilityTask(context), want_(want), target_(target), bundleInfo_(bundleInfo)
{
}

AbilityStartTask::~AbilityStartTask()
{
    want_ = nullptr;
    target_ = nullptr;
    bundleInfo_ = nullptr;
}

void AbilityStartTask::SetWaitConnect(bool waitConnect)
{
    waitConnect_ = waitConnect;
}

AbilityMsStatus AbilityStartTask::Execute()
{
    PRINTD("AbilityStartTask", "start");
    if (abilityMgrContext_ == nullptr || want_ == nullptr ||
        target_ == nullptr || bundleInfo_ == nullptr) {
        return AbilityMsStatus::TaskStatus("start", "invalid argument");
    }
    if (target_->abilityType == AbilityType::SERVICE) {
        return StartService();
    }
    AbilityStackManager &stackManager = AbilityStackManager::GetInstance();
    // Step1: Get current top ability record.
    PageAbilityRecord *topAbility = const_cast<PageAbilityRecord *>(
        stackManager.GetTopPageAbility(*abilityMgrContext_));
    // Step2: Generate target ability record.
    PageAbilityRecord *targetAbility = stackManager.GeneratePageAbility(
        *target_, *want_, topAbility, *abilityMgrContext_);
    if (targetAbility == nullptr) {
        return AbilityMsStatus::TaskStatus("start", "generate ability record failure");
    }
    targetAbility->SetBundleInfo(*bundleInfo_);
    if (topAbility != nullptr) {
        // step3：If topAbility is not nullptr, inactive top ability.
        PRINTD("AbilityStartTask", "topAbility is not nullptr, first inactive");
        topAbility->SetNextPageAbility(targetAbility);
        targetAbility->SetPrevPageAbility(topAbility);
        AbilityMsStatus status = topAbility->InactiveAbility();
        if (!status.IsOk()) {
            topAbility->SetNextPageAbility(nullptr);
            stackManager.RemovePageAbility(*targetAbility, *abilityMgrContext_);
        }
        return status;
    }
    // step4: Start ability.
    PRINTD("AbilityStartTask", "topAbility is nullptr or not active");
    AbilityMsStatus status = targetAbility->StartAbility();
    if (status.IsProcessError() || status.IsTransactError()) {
        // Clean page ability record if failure
        if (topAbility != nullptr) {
            topAbility->SetNextPageAbility(nullptr);
        }
        stackManager.RemovePageAbility(*targetAbility, *abilityMgrContext_);
    }
    return status;
}

AbilityMsStatus AbilityStartTask::StartService()
{
    PRINTD("AbilityStartTask", "start service");
    auto connectMission = const_cast<AbilityConnectMission *>(abilityMgrContext_->GetServiceConnects());
    if (connectMission == nullptr) {
        return AbilityMsStatus::TaskStatus("start", "invalid argument");
    }
    auto service = connectMission->FindServiceRecord(target_->bundleName, target_->name);
    if (service != nullptr) {
        return AbilityMsStatus::TaskStatus("start", "service ability exists");
    }
    auto targetAbility = new PageAbilityRecord(*target_, *want_);
    targetAbility->SetBundleInfo(*bundleInfo_);
    if (waitConnect_) {
        targetAbility->SetStartDone(false);
        targetAbility->SetConnectStatus(ConnectStatus::WAIT_CONNECT);
    } else {
        targetAbility->SetStartDone(true);
    }
    connectMission->PushServiceRecord(*targetAbility);
    targetAbility->SetConnectMission(connectMission);
    AbilityMsStatus status = targetAbility->StartService();
    if (status.IsProcessError() || status.IsTransactError()) {
        // Clean service ability record if failure
        connectMission->RemoveServiceRecord(targetAbility->GetToken());
    }
    return status;
}
}  // namespace OHOS
