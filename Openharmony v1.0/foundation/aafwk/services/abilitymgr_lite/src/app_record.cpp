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

#include "app_record.h"

#include "adapter.h"
#include "bundle_info_utils.h"
#include "page_ability_record.h"
#include "pms.h"
#include "securec.h"
#include "utils.h"

namespace OHOS {
AppRecord::AppRecord(const BundleInfo &bundleInfo, uint64_t identityId)
    : identityId_(identityId)
{
    BundleInfoUtils::CopyBundleInfo(0, &bundleInfo_, bundleInfo);
}

AppRecord::~AppRecord()
{
    ClearBundleInfo(&bundleInfo_);
    delete abilityThreadClient_;
}

void AppRecord::SetPid(const pid_t pid)
{
    pid_ = pid;
}

pid_t AppRecord::GetPid() const
{
    return pid_;
}

uint64_t AppRecord::GetIdentityId() const
{
    return identityId_;
}

const BundleInfo &AppRecord::GetBundleInfo() const
{
    return bundleInfo_;
}

AbilityMsStatus AppRecord::LoadPermission() const
{
    int ret = LoadPermissions(bundleInfo_.bundleName, pid_);
    if (ret != PERM_ERRORCODE_SUCCESS) {
        AppExitTransaction();
        std::string errorMsg = "load application permission ret = " + std::to_string(ret);
        return AbilityMsStatus::PermissionStatus(errorMsg.c_str());
    }
    return AbilityMsStatus::Ok();
}

void AppRecord::UnloadPermission() const
{
    UnLoadPermissions(pid_);
}

AbilityMsStatus AppRecord::SetAbilityThreadClient(const AbilityThreadClient &client)
{
    abilityThreadClient_ = new AbilityThreadClient(client);
    return abilityThreadClient_->Initialize(bundleInfo_.bundleName);
}

AbilityMsStatus AppRecord::AbilityTransaction(const TransactionState &state,
    const Want &want, AbilityType abilityType) const
{
    if (abilityThreadClient_ != nullptr) {
        return abilityThreadClient_->AbilityTransaction(state, want, abilityType);
    }
    return AbilityMsStatus::AppTransanctStatus("life cycle ability thread client not exsit");
}

AbilityMsStatus AppRecord::AppInitTransaction() const
{
    if (abilityThreadClient_ != nullptr) {
        return abilityThreadClient_->AppInitTransaction(bundleInfo_);
    }
    return AbilityMsStatus::AppTransanctStatus("app init ability thread client not exsit");
}

AbilityMsStatus AppRecord::AppExitTransaction() const
{
    if (abilityThreadClient_ != nullptr) {
        return abilityThreadClient_->AppExitTransaction();
    }
    return AbilityMsStatus::AppTransanctStatus("app exit ability thread client not exsit");
}

AbilityMsStatus AppRecord::DumpAbilityTransaction(const Want &want, uint64_t token) const
{
    if (abilityThreadClient_ != nullptr) {
        return abilityThreadClient_->DumpAbilityTransaction(want, token);
    }
    return AbilityMsStatus::AppTransanctStatus("dump ability ability thread client not exsit");
}

void AppRecord::SetPendingAbility(PageAbilityRecord *abilityRecord)
{
    pendingAbilityRecord_ = abilityRecord;
}

AbilityMsStatus AppRecord::LaunchPendingAbility()
{
    if (pendingAbilityRecord_ != nullptr) {
        AbilityMsStatus status;
        if (pendingAbilityRecord_->GetAbilityInfo().abilityType == AbilityType::SERVICE) {
            status = pendingAbilityRecord_->InactiveAbility();
        } else {
            status = pendingAbilityRecord_->ActiveAbility();
        }
        // MissionRecord release AbilityRecord
        pendingAbilityRecord_ = nullptr;
        return status;
    }
    return AbilityMsStatus::LifeCycleStatus("pending ability not exsit");
}

AbilityMsStatus AppRecord::ConnectTransaction(const Want &want, uint64_t token) const
{
    if (abilityThreadClient_ != nullptr) {
        return abilityThreadClient_->ConnectAbility(want, token);
    }
    return AbilityMsStatus::TaskStatus("connectAbility", "app exit ability thread client not exsit");
}

AbilityMsStatus AppRecord::DisconnectTransaction(const Want &want, uint64_t token) const
{
    if (abilityThreadClient_ != nullptr) {
        return abilityThreadClient_->DisconnectAbility(want, token);
    }
    return AbilityMsStatus::TaskStatus("disconnectAbility", "app exit ability thread client not exsit");
}

AbilityMsStatus AppRecord::ConnectDoneTransaction(const Want &want, const SvcIdentity &serviceSid,
    const SvcIdentity &connectSid) const
{
    if (abilityThreadClient_ != nullptr) {
        return abilityThreadClient_->ConnectAbilityDone(want, serviceSid, connectSid);
    }
    return AbilityMsStatus::TaskStatus("connectAbilityDone", "app exit ability thread client not exsit");
}

AbilityMsStatus AppRecord::DisconnectDoneTransaction(const Want &want, const SvcIdentity &connectSid) const
{
    if (abilityThreadClient_ != nullptr) {
        return abilityThreadClient_->DisconnectAbilityDone(want, connectSid);
    }
    return AbilityMsStatus::TaskStatus("disconnectAbilityDone", "app exit ability thread client not exsit");
}

void AppRecord::ClearPendingAbility(PageAbilityRecord *abilityRecord)
{
    if (pendingAbilityRecord_ != nullptr && pendingAbilityRecord_ == abilityRecord) {
        pendingAbilityRecord_ = nullptr;
    }
}
}  // namespace OHOS
