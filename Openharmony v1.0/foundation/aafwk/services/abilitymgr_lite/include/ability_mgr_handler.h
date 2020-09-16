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

#ifndef OHOS_ABILITY_MANAGER_SERVICE_IMPL_H
#define OHOS_ABILITY_MANAGER_SERVICE_IMPL_H

#include "ability_connect_trans_param.h"
#include "ability_worker.h"
#include "client/ability_dump_client.h"
#include "client/bundlems_client.h"
#include "message.h"
#include "nocopyable.h"

namespace OHOS {
class AbilityMgrHandler : public NoCopyable {
public:
    static AbilityMgrHandler &GetInstance()
    {
        static AbilityMgrHandler instance;
        return instance;
    }
    ~AbilityMgrHandler() = default;
    void Init();
    void ServiceMsgProcess(const Request& request);
private:
    AbilityMgrHandler() = default;
    void OnServiceInited();
    void StartKeepAliveApps();
    void StartKeepAliveApp(const BundleInfo &bundleInfo);
    void StartLauncher();
    int StartAbility(const Want *want, pid_t callingUid);
    void AttachBundle(AbilityThreadClient *client);
    void TerminateAbility(const uint64_t *token);
    void AbilityTransaction(TransactionState *state);
    void TerminateApp(const char *bundleName);
    void RestartApp(const char *bundleName);

    int ConnectAbility(AbilityConnectTransParam *transParam);
    void DisconnectAbility(AbilityConnectTransParam *transParam);
    void ConnectAbilityDone(AbilityConnectTransParam *transParam);
    void DisconnectAbilityDone(const uint64_t *token);
    void TerminateService(Want *want, pid_t callingUid);
    void StartAbilityCallback(const Want *want, int code);
    void DumpAbility(const AbilityDumpClient *client);
    void ConnectAbilityCallback(AbilityConnectTransParam *transParam, int code);

    AbilityWorker abilityWorker_;
    BundleMsClient bundleMsClient_;
};
} // namespace OHOS
#endif // OHOS_ABILITY_MANAGER_SERVICE_IMPL_H
