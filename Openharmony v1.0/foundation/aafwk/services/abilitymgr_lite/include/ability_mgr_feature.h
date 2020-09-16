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

#ifndef OHOS_ABILITYMANAGERSERVICE_FEATURE_H
#define OHOS_ABILITYMANAGERSERVICE_FEATURE_H

#include "ability_mgr_handler.h"
#include "ability_service_interface.h"
#include "feature.h"
#include "iproxy_client.h"
#include "iunknown.h"
#include "nocopyable.h"

namespace OHOS {
typedef int32 (*InvokeFunc)(const void *origin, IpcIo *req);

class AbilityMgrFeature : public Feature {
public:
    static int32 StartAbility(const Want *want);
    static int32 TerminateAbility(uint64_t token);
    static int32 ConnectAbility(const Want *want, SvcIdentity *svc, uint64_t token);
    static int32 DisconnectAbility(SvcIdentity *svc, uint64_t token);
    static int32 StopAbility(const Want *want);

    static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply);

    static int32 AppDeathNotify(const IpcContext* context, void *ipcMsg, IpcIo *data, void *arg);
    static AbilityMgrFeature *GetInstance()
    {
        static AbilityMgrFeature instance;
        return &instance;
    }
    ~AbilityMgrFeature() = default;
private:
    AbilityMgrFeature();
    static int32 StartAbilityInner(const Want *want, pid_t callingUid);
    static int32 ConnectAbilityInner(const Want *want, SvcIdentity *svc, uint64_t token, pid_t callingUid);
    static int32 StopAbilityInner(const Want *want, pid_t callingUid);
    static int32 StartAbilityInvoke(const void *origin, IpcIo *req);
    static int32 TerminateAbilityInvoke(const void *origin, IpcIo *req);
    static int32 ConnectAbilityInvoke(const void *origin, IpcIo *req);
    static int32 DisconnectAbilityInvoke(const void *origin, IpcIo *req);
    static int32 StopAbilityInvoke(const void *origin, IpcIo *req);

    static int32 AbilityTransactionDoneInvoke(const void *origin, IpcIo *req);
    static int32 AttachBundleInvoke(const void *origin, IpcIo *req);
    static int32 ConnectAbilityDoneInvoke(const void *origin, IpcIo *req);
    static int32 DisconnectAbilityDoneInvoke(const void *origin, IpcIo *req);
    static int32 RestartApp(const char *bundleName);

    static const char *GetFeatureName(Feature *feature);
    static void OnFeatureInitialize(Feature *feature, Service *parent, Identity identity);
    static void OnFeatureStop(Feature *feature, Identity identity);
    static BOOL OnFeatureMessage(Feature *feature, Request *request);

private:
    Identity identity_;
    static InvokeFunc invokeFuncList[INNER_BEGIN];
    DISALLOW_COPY_AND_MOVE(AbilityMgrFeature);
};

typedef struct {
    INHERIT_IUNKNOWNENTRY(AmsInterface);
    AbilityMgrFeature *ams;
} AbilityMgrFeatureImpl;
} // namespace OHOS
#endif // OHOS_ABILITYMANAGERSERVICE_FEATURE_H
