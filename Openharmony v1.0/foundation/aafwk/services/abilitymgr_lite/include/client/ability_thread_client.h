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

#ifndef OHOS_ABILITY_THREAD_CLIENT_H
#define OHOS_ABILITY_THREAD_CLIENT_H

#include "bundle_info.h"
#include "liteipc_adapter.h"
#include "util/abilityms_status.h"
#include "want.h"

namespace OHOS {
typedef struct {
    uint64_t token;
    int32_t state;
} TransactionState;

typedef struct {
    char *bundleName;
} AppInfo;

class AbilityRecord;
class AbilityThreadClient {
public:
    AbilityThreadClient(uint64_t token, pid_t callingPid, const SvcIdentity &svcIdentity, IpcMsgHandler handler);
    AbilityThreadClient(const AbilityThreadClient &client);
    ~AbilityThreadClient() = default;

    AbilityMsStatus Initialize(const char *bundleName);
    uint64_t GetToken() const;
    pid_t GetPid() const;
    const SvcIdentity &GetSvcIdentity() const;
    AbilityMsStatus AbilityTransaction(const TransactionState &state, const Want &want, AbilityType abilityType) const;
    AbilityMsStatus AppInitTransaction(const BundleInfo &bundleInfo);
    AbilityMsStatus AppExitTransaction();
    AbilityMsStatus ConnectAbility(const Want &want, uint64_t token) const;
    AbilityMsStatus DisconnectAbility(const Want &want, uint64_t token) const;
    AbilityMsStatus ConnectAbilityDone(const Want &want, const SvcIdentity &serviceSid,
        const SvcIdentity &connectSid) const;
    AbilityMsStatus DisconnectAbilityDone(const Want &want, const SvcIdentity &connectSid) const;
    AbilityMsStatus DumpAbilityTransaction(const Want &want, uint64_t token);
private:
    uint64_t token_ = -1;
    pid_t pid_ = -1;
    uint32_t cbid_ = -1;
    const SvcIdentity svcIdentity_;
    const IpcMsgHandler deathHandler_;
    static const int MAX_OBJECTS = 2;
};
} // namespace OHOS
#endif // OHOS_ABILITY_THREAD_CLIENT_H
