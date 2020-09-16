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

#include "page_ability_record.h"

#include "ability_connect_mission.h"
#include "ability_info_utils.h"
#include "ability_mission_record.h"
#include "adapter.h"
#include "app_manager.h"
#include "bundle_info_utils.h"
#include "securec.h"
#include "token_generate.h"
#include "util/abilityms_helper.h"

namespace OHOS {
PageAbilityRecord::PageAbilityRecord(const AbilityInfo &abilityInfo, const Want &want)
{
    if (want.element != nullptr) {
        SetWantElement(&want_, *(want.element));
    }
    if (want.data != nullptr) {
        SetWantData(&want_, want.data, want.dataLength);
    }
    if (want.sid != nullptr) {
        SetWantSvcIdentity(&want_, *(want.sid));
    }
    AbilityInfoUtils::CopyAbilityInfo(&abilityInfo_, abilityInfo);
    Initialize();
    PRINTD("PageAbilityRecord", "Constructor");
}

PageAbilityRecord::~PageAbilityRecord()
{
    if (appRecord_ != nullptr) {
        appRecord_->ClearPendingAbility(this);
        appRecord_ = nullptr;
    }
    ClearWant(&want_);
    ClearAbilityInfo(&abilityInfo_);
    ClearBundleInfo(&bundleInfo_);
    missionRecord_ = nullptr;
    prevPageAbility_ = nullptr;
    nextPageAbility_ = nullptr;

    for (auto iterator = connectRecords_.begin(); iterator != connectRecords_.end(); ++iterator) {
        auto record = *iterator;
        delete record;
    }
    connectRecords_.clear();
    PRINTD("AbilityRecord", "Destructor");
}

void PageAbilityRecord::Initialize()
{
    token_ = TokenGenerate::GenerateToken();
    appRecord_ = AppManager::GetInstance().GetAppRecordByBundleName(abilityInfo_.bundleName);
}

const AbilityInfo& PageAbilityRecord::GetAbilityInfo() const
{
    return abilityInfo_;
}

const BundleInfo& PageAbilityRecord::GetBundleInfo() const
{
    return bundleInfo_;
}

void PageAbilityRecord::SetBundleInfo(const BundleInfo &bundleInfo)
{
    if (memset_s(&bundleInfo_, sizeof(BundleInfo), 0, sizeof(BundleInfo)) == EOK) {
        BundleInfoUtils::CopyBundleInfo(0, &bundleInfo_, bundleInfo);
    }
}

bool PageAbilityRecord::IsSamePageAbility(const PageAbilityRecord &target) const
{
    return token_ == target.GetToken();
}

bool PageAbilityRecord::IsSamePageAbility(const Want &want) const
{
    if (want.element == nullptr || want.element->bundleName == nullptr || want.element->abilityName == nullptr) {
        return false;
    }
    if (abilityInfo_.bundleName == nullptr || abilityInfo_.name == nullptr) {
        return false;
    }
    if (strcmp(abilityInfo_.bundleName, want.element->bundleName) == 0 &&
        strcmp(abilityInfo_.name, want.element->abilityName) == 0) {
        return true;
    }
    return false;
}

bool PageAbilityRecord::IsSamePageAbility(const char *bundleName) const
{
    if (bundleName == nullptr || abilityInfo_.bundleName == nullptr) {
        return false;
    }
    return strcmp(bundleName, abilityInfo_.bundleName) == 0;
}

bool PageAbilityRecord::IsBottomPageAbility() const
{
    if (missionRecord_ != nullptr) {
        const PageAbilityRecord *bottomAbililty = missionRecord_->GetBottomPageAbility();
        if (bottomAbililty != nullptr && bottomAbililty->GetToken() == token_) {
            return true;
        }
    }
    return false;
}

ConnectStatus PageAbilityRecord::GetConnectStatus() const
{
    return connectStatus_;
}

bool PageAbilityRecord::IsPerformStop() const
{
    return connectStatus_ == ConnectStatus::STOPPING || connectStatus_ == ConnectStatus::STOPPED;
}

void PageAbilityRecord::SetConnectStatus(ConnectStatus connectStatus)
{
    connectStatus_ = connectStatus;
}

void PageAbilityRecord::SetStartDone(bool startDone)
{
    startDone_ = startDone;
}

uint64_t PageAbilityRecord::GetToken() const
{
    return token_;
}

void PageAbilityRecord::SetCurrentState(State state)
{
    currentState_ = state;
}

State PageAbilityRecord::GetCurrentState() const
{
    return currentState_;
}

void PageAbilityRecord::SetMissionRecord(AbilityMissionRecord *missionRecord)
{
    missionRecord_ = missionRecord;
}

const AbilityMissionRecord *PageAbilityRecord::GetMissionRecord() const
{
    return missionRecord_;
}

void PageAbilityRecord::SetNextPageAbility(PageAbilityRecord *next)
{
    nextPageAbility_ = next;
}

const PageAbilityRecord *PageAbilityRecord::GetNextPageAbility() const
{
    return nextPageAbility_;
}

void PageAbilityRecord::SetPrevPageAbility(PageAbilityRecord *prev)
{
    prevPageAbility_ = prev;
}

const PageAbilityRecord *PageAbilityRecord::GetPrevPageAbility() const
{
    return prevPageAbility_;
}

void PageAbilityRecord::SetConnectMission(AbilityConnectMission *connectMission)
{
    connectMission_ = connectMission;
}

const AbilityConnectMission *PageAbilityRecord::GetConnectMission() const
{
    return connectMission_;
}

void PageAbilityRecord::SetServiceSid(const SvcIdentity &serviceSid)
{
    serviceSid_ = serviceSid;
}

const SvcIdentity PageAbilityRecord::GetServiceSid() const
{
    return serviceSid_;
}

AbilityConnectRecord *PageAbilityRecord::GetConnectRecord(const SvcIdentity &serviceSid) const
{
    for (const auto record : connectRecords_) {
        if (record != nullptr && record->GetConnectSid().handle == serviceSid.handle &&
            record->GetConnectSid().token == serviceSid.token) {
            return record;
        }
    }
    return nullptr;
}

void PageAbilityRecord::pushConnectRecord(AbilityConnectRecord *connectRecord)
{
    connectRecords_.emplace_back(connectRecord);
}

void PageAbilityRecord::RemoveConnectRecord(const SvcIdentity &serviceSid)
{
    for (auto iterator = connectRecords_.begin(); iterator != connectRecords_.end(); ++iterator) {
        auto record = *iterator;
        if (record != nullptr && record->GetConnectSid().handle == serviceSid.handle &&
            record->GetConnectSid().token == serviceSid.token) {
            connectRecords_.erase(iterator);
            delete record;
            return;
        }
    }
}

bool PageAbilityRecord::IsLauncherAbility() const
{
    return AbilityMsHelper::IsLauncherAbility(abilityInfo_.bundleName);
}

AbilityMsStatus PageAbilityRecord::StartAbility()
{
    if (appRecord_ == nullptr) {
        // If process is not exist, start process.
        appRecord_ = AppManager::GetInstance().StartAppProcess(bundleInfo_);
        if (appRecord_ == nullptr) {
            return AbilityMsStatus::ProcessStatus("start app process fail");
        }
        appRecord_->SetPendingAbility(this);
        return AbilityMsStatus::Ok();
    }
    return ActiveAbility();
}

AbilityMsStatus PageAbilityRecord::StartService()
{
    if (appRecord_ == nullptr) {
        // If process is not exist, start process.
        appRecord_ = AppManager::GetInstance().StartAppProcess(bundleInfo_);
        if (appRecord_ == nullptr) {
            return AbilityMsStatus::ProcessStatus("start app process fail");
        }
        appRecord_->SetPendingAbility(this);
        return AbilityMsStatus::Ok();
    }
    return InactiveAbility();
}

AbilityMsStatus PageAbilityRecord::ActiveAbility()
{
    if (currentState_ == STATE_ACTIVE) {
        return AbilityMsStatus::LifeCycleStatus("current state is already active when active");
    }
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::AppTransanctStatus("app record not exsit");
    }
    TransactionState state = {token_, STATE_ACTIVE};
    auto status = appRecord_->AbilityTransaction(state, want_, abilityInfo_.abilityType);
    AdapterFree(want_.sid);
    return status;
}

AbilityMsStatus PageAbilityRecord::InactiveAbility() const
{
    if (currentState_ != STATE_ACTIVE && abilityInfo_.abilityType != AbilityType::SERVICE) {
        return AbilityMsStatus::LifeCycleStatus("current state is not active when inactive");
    }
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::AppTransanctStatus("app record not exsit");
    }
    TransactionState state = {token_, STATE_INACTIVE};
    return appRecord_->AbilityTransaction(state, want_, abilityInfo_.abilityType);
}

AbilityMsStatus PageAbilityRecord::ToBackgroundAbility() const
{
    if (currentState_ != STATE_INACTIVE) {
        return AbilityMsStatus::LifeCycleStatus("current state is not inactive when background");
    }
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::AppTransanctStatus("app record not exsit");
    }
    TransactionState state = {token_, STATE_BACKGROUND};
    return appRecord_->AbilityTransaction(state, want_, abilityInfo_.abilityType);
}

AbilityMsStatus PageAbilityRecord::StopAbility() const
{
    if (currentState_ != STATE_INACTIVE) {
        return AbilityMsStatus::LifeCycleStatus("current state is not inactive when stop");
    }
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::AppTransanctStatus("app record not exsit");
    }
    TransactionState state = {token_, STATE_INITIAL};
    return appRecord_->AbilityTransaction(state, want_, abilityInfo_.abilityType);
}

AbilityMsStatus PageAbilityRecord::ExitApp()
{
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::AppTransanctStatus("app record not exsit");
    }
    AbilityMsStatus status = appRecord_->AppExitTransaction();
    if (status.IsOk()) {
        AppManager::GetInstance().RemoveAppRecord(*appRecord_);
        appRecord_ = nullptr;
    }
    return status;
}

AbilityMsStatus PageAbilityRecord::ConnectAbility()
{
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::TaskStatus("connectAbility, ", "app record not exsit");
    }
    return appRecord_->ConnectTransaction(want_, token_);
}

AbilityMsStatus PageAbilityRecord::DisconnectAbility(const SvcIdentity &connectSid)
{
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::TaskStatus("disconnectAbility, ", "app record not exsit");
    }
    RemoveConnectRecord(connectSid);

    if (connectStatus_ == ConnectStatus::DISCONNECT || connectStatus_ == ConnectStatus::DISCONNECTING) {
        PRINTW("disconnectAbility", "service is disconnecting");
        return AbilityMsStatus::Ok();
    }
    if (IsPerformStop()) {
        PRINTW("disconnectAbility", "service is stopping");
        return AbilityMsStatus::Ok();
    }
    if (connectRecords_.empty()) {
        SetConnectStatus(ConnectStatus::DISCONNECTING);
        return appRecord_->DisconnectTransaction(want_, token_);
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus PageAbilityRecord::ConnectAbilityDone()
{
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::TaskStatus("connectAbilityDone, ", "app record not exsit");
    }
    for (auto record : connectRecords_) {
        if (record != nullptr && record->GetStatus() == ConnectStatus::CONNECTING) {
            record->SetStatus(ConnectStatus::CONNECTED);
            appRecord_->ConnectDoneTransaction(want_, serviceSid_, record->GetConnectSid());
        }
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus PageAbilityRecord::DisconnectAbilityDone()
{
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::TaskStatus("disconnectAbilityDone, ", "app record not exsit");
    }
    if (startDone_) {
        SetConnectStatus(ConnectStatus::INIT);
    } else {
        SetConnectStatus(ConnectStatus::DISCONNECT);
    }
    if ((connectRecords_.empty() && !startDone_) || forceStop_) {
        SetConnectStatus(ConnectStatus::STOPPING);
        TransactionState state = {token_, STATE_INITIAL};
        return appRecord_->AbilityTransaction(state, want_, abilityInfo_.abilityType);
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus PageAbilityRecord::ForceStopServiceAbility()
{
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::TaskStatus("terminateService, ", "app record not exsit");
    }
    forceStop_ = true;
    if (IsPerformStop()) {
        return AbilityMsStatus::TaskStatus("terminateService", "service is stopping");
    }
    if (connectStatus_ == ConnectStatus::DISCONNECTING) {
        return AbilityMsStatus::TaskStatus("terminateService", "service is disconnecting");
    }
    if (connectStatus_ == ConnectStatus::DISCONNECT || connectRecords_.empty()) {
        SetConnectStatus(ConnectStatus::STOPPING);
        TransactionState state = {token_, STATE_INITIAL};
        return appRecord_->AbilityTransaction(state, want_, abilityInfo_.abilityType);
    } else {
        SetConnectStatus(ConnectStatus::DISCONNECTING);
        return appRecord_->DisconnectTransaction(want_, token_);
    }
}

AbilityMsStatus PageAbilityRecord::StopAbilityDone()
{
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::TaskStatus("disconnectAbilityDone, ", "app record not exsit");
    }
    SetConnectStatus(ConnectStatus::STOPPED);
    for (const auto record : connectRecords_) {
        if (record != nullptr) {
            appRecord_->DisconnectDoneTransaction(want_, record->GetConnectSid());
        }
    }
    return AbilityMsStatus::Ok();
}

#ifdef OHOS_DEBUG
AbilityMsStatus PageAbilityRecord::DumpAbilityRecord() const
{
    std::string launcherMode = (abilityInfo_.launchMode == STANDARD) ? "standard" : "singleton";
    std::string result = "\tAbilityRecord:" + std::to_string(token_) + "\n"
        "\t    stat:" + AbilityMsHelper::AbilityStateToString(currentState_) + " launchMode:" + launcherMode + "\n"
        "\t    bundleName:" + abilityInfo_.bundleName + " abilityName:" + abilityInfo_.name + "\n"
        "\t    codePath:" + bundleInfo_.codePath + " dataPath:" + bundleInfo_.dataPath + "\n";
    return AbilityMsStatus::DumpStatus(result.c_str());
}
#endif

AbilityMsStatus PageAbilityRecord::DumpAbilitySlice(const Want &want) const
{
    if (appRecord_ == nullptr) {
        return AbilityMsStatus::TaskStatus("DumpAbility, ", "app record not exsit");
    }
    return appRecord_->DumpAbilityTransaction(want, token_);
}

void PageAbilityRecord::RemoveConnectRecordByPageToken(uint64_t token)
{
    if (connectRecords_.empty()) {
        return;
    }
    for (auto iterator = connectRecords_.begin(); iterator != connectRecords_.end();) {
        auto record = *iterator;
        if (record != nullptr && record->GetAbilityToken() == token) {
            iterator = connectRecords_.erase(iterator);
            delete record;
        } else {
            ++iterator;
        }
    }
    if (connectRecords_.empty() && !startDone_) {
        StopAbility();
    }
}

AbilityConnectRecord *PageAbilityRecord::GetConnectRecord(const SvcIdentity &serviceSid, uint64_t abilityToken) const
{
    for (const auto record : connectRecords_) {
        if (record != nullptr && record->GetConnectSid().handle == serviceSid.handle &&
            record->GetConnectSid().token == serviceSid.token && record->GetAbilityToken() == abilityToken) {
            return record;
        }
    }
    return nullptr;
}
}
