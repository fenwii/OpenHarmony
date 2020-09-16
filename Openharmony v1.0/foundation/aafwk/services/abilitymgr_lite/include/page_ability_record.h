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

#ifndef OHOS_ABILITY_RECORD_NEW_H
#define OHOS_ABILITY_RECORD_NEW_H

#include <list>

#include "ability_connect_record.h"
#include "ability_state.h"
#include "app_record.h"
#include "serializer.h"

namespace OHOS {
class AbilityConnectMission;
class AbilityMissionRecord;
class PageAbilityRecord {
public:
    PageAbilityRecord(const AbilityInfo &abilityInfo, const Want &want);
    ~PageAbilityRecord();

    // AbilityInfo
    const AbilityInfo& GetAbilityInfo() const;
    bool IsLauncherAbility() const;
    void SetCurrentState(State state);
    State GetCurrentState() const;
    uint64_t GetToken() const;

    // Util
    bool IsSamePageAbility(const PageAbilityRecord &target) const;
    bool IsSamePageAbility(const Want &want) const;
    bool IsSamePageAbility(const char *bundleName) const;
    bool IsBottomPageAbility() const;

    // BundleInfo
    const BundleInfo& GetBundleInfo() const;
    void SetBundleInfo(const BundleInfo &bundleInfo);

    // LifeCycle
    AbilityMsStatus StartAbility();
    AbilityMsStatus ActiveAbility();
    AbilityMsStatus InactiveAbility() const;
    AbilityMsStatus ToBackgroundAbility() const;
    AbilityMsStatus StopAbility() const;
    AbilityMsStatus ExitApp();

    // MissionRecord
    void SetMissionRecord(AbilityMissionRecord *missionRecord);
    const AbilityMissionRecord *GetMissionRecord() const;

    // Getter and Setter next and prev ability
    void SetNextPageAbility(PageAbilityRecord *next);
    const PageAbilityRecord *GetNextPageAbility() const;
    void SetPrevPageAbility(PageAbilityRecord *prev);
    const PageAbilityRecord *GetPrevPageAbility() const;

    // connect service ability
    void SetConnectMission(AbilityConnectMission *connectMission);
    const AbilityConnectMission *GetConnectMission() const;
    void SetServiceSid(const SvcIdentity& serviceSid);
    const SvcIdentity GetServiceSid() const;
    ConnectStatus GetConnectStatus() const;
    void SetConnectStatus(ConnectStatus connectStatus);
    void SetStartDone(bool startDone);
    AbilityConnectRecord *GetConnectRecord(const SvcIdentity &serviceSid) const;
    void pushConnectRecord(AbilityConnectRecord *connectRecord);
    void RemoveConnectRecord(const SvcIdentity &serviceSid);
    bool IsPerformStop() const;
    AbilityConnectRecord *GetConnectRecord(const SvcIdentity &serviceSid, uint64_t abilityToken) const;

    AbilityMsStatus StartService();
    AbilityMsStatus ConnectAbility();
    AbilityMsStatus DisconnectAbility(const SvcIdentity &connectSid);
    AbilityMsStatus ConnectAbilityDone();
    AbilityMsStatus DisconnectAbilityDone();
    AbilityMsStatus ForceStopServiceAbility();
    AbilityMsStatus StopAbilityDone();
    void RemoveConnectRecordByPageToken(uint64_t token);

    // Dump
#ifdef OHOS_DEBUG
    AbilityMsStatus DumpAbilityRecord() const;
#endif
    AbilityMsStatus DumpAbilitySlice(const Want &want) const;
private:
    void Initialize();

    AbilityMissionRecord *missionRecord_ { nullptr };
    PageAbilityRecord *nextPageAbility_ { nullptr };
    PageAbilityRecord *prevPageAbility_ { nullptr };

    AppRecord *appRecord_ { nullptr };
    AbilityInfo abilityInfo_ = {};
    BundleInfo bundleInfo_ = {};
    Want want_ = {};
    State currentState_ = STATE_UNINITIALIZED;
    uint64_t token_ { 0 };

    bool startDone_ = false;
    SvcIdentity serviceSid_ = { 0, 0 };
    ConnectStatus connectStatus_ = ConnectStatus::INIT;
    bool forceStop_ = false;

    AbilityConnectMission *connectMission_  { nullptr };
    std::list<AbilityConnectRecord *> connectRecords_;
};
}
#endif // OHOS_ABILITY_RECORD_NEW_H
