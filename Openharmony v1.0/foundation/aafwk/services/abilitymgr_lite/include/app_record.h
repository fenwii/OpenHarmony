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

#ifndef OHOS_APP_RECORD_H
#define OHOS_APP_RECORD_H

#include "bundle_info.h"
#include "client/ability_thread_client.h"

namespace OHOS {
class PageAbilityRecord;
class AppRecord {
public:
    AppRecord(const BundleInfo& bundleInfo, uint64_t identityId);
    ~AppRecord();

    void SetPid(pid_t pid);
    pid_t GetPid() const;
    uint64_t GetIdentityId() const;
    const BundleInfo &GetBundleInfo() const;

    AbilityMsStatus LoadPermission() const;
    void UnloadPermission() const;
    AbilityMsStatus SetAbilityThreadClient(const AbilityThreadClient &client);
    AbilityMsStatus AbilityTransaction(const TransactionState &state,
        const Want &want, AbilityType abilityType) const;
    AbilityMsStatus AppInitTransaction() const;
    AbilityMsStatus AppExitTransaction() const;
    AbilityMsStatus DumpAbilityTransaction(const Want &want, uint64_t token) const;
    void SetPendingAbility(PageAbilityRecord *abilityRecord);
    AbilityMsStatus LaunchPendingAbility();

    AbilityMsStatus ConnectTransaction(const Want &want, uint64_t token) const;
    AbilityMsStatus DisconnectTransaction(const Want &want, uint64_t token) const;
    AbilityMsStatus ConnectDoneTransaction(const Want &want, const SvcIdentity &serviceSid,
        const SvcIdentity &connectSid) const;
    AbilityMsStatus DisconnectDoneTransaction(const Want &want, const SvcIdentity &connectSid) const;
    void ClearPendingAbility(PageAbilityRecord *abilityRecord);
private:
    pid_t pid_ { 0 };
    uint64_t identityId_ { 0 };
    BundleInfo bundleInfo_ {};
    AbilityThreadClient *abilityThreadClient_ { nullptr };
    PageAbilityRecord *pendingAbilityRecord_ { nullptr };
};
}  // namespace OHOS
#endif  // OHOS_APP_RECORD_H
