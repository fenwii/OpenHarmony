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

#ifndef OHOS_ABILITY_WORKER_H
#define OHOS_ABILITY_WORKER_H

#include "ability_connect_trans_param.h"
#include "ability_mgr_context.h"
#include "client/ability_thread_client.h"
#include "client/ability_dump_client.h"

namespace OHOS {
class AbilityWorker {
public:
    AbilityWorker();
    ~AbilityWorker();

    AbilityMsStatus StartAbility(const Want &want, const AbilityInfo &target, const BundleInfo &bundleInfo, pid_t uid);
    AbilityMsStatus AttachBundle(const AbilityThreadClient &client);
    AbilityMsStatus TerminateAbility(uint64_t token);
    AbilityMsStatus AbilityTransaction(const TransactionState &state);
    AbilityMsStatus TerminateApp(const char *bundleName);
    AbilityMsStatus RestartApp(const BundleInfo &bundleInfo);
    AbilityMsStatus DumpAbility(const AbilityDumpClient &client);

    AbilityMsStatus TerminateService(const AbilityInfo &target, const BundleInfo &bundleInfo, pid_t callingUid);
    AbilityMsStatus ConnectAbility(const AbilityConnectTransParam &connectParam, const AbilityInfo &target,
            const BundleInfo &bundleInfo);
    AbilityMsStatus DisconnectAbility(const SvcIdentity &identity, uint64_t token);
    AbilityMsStatus ConnectAbilityDone(const SvcIdentity &identity, uint64_t token);
    AbilityMsStatus DisconnectAbilityDone(uint64_t token);

private:
    AbilityMgrContext *abilityMgrContext_ { nullptr };
};
}  // namespace OHOS
#endif  // OHOS_ABILITY_WORKER_H
