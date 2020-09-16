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

#ifndef OHOS_ABILITYMANAGERSERVICE_INNER_FEATURE_H
#define OHOS_ABILITYMANAGERSERVICE_INNER_FEATURE_H

#include "ability_service_interface.h"
#include "ability_mgr_handler.h"
#include "feature.h"
#include "iunknown.h"
#include "iproxy_client.h"
#include "nocopyable.h"

namespace OHOS {
typedef int32 (*InvokeFunc)(const void *origin, IpcIo *req);

class AbilityInnerFeature : public Feature {
public:
    static int32 StartKeepAliveApps();
    static int32 TerminateApp(const char *bundleName);

    static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply);

    static AbilityInnerFeature *GetInstance()
    {
        static AbilityInnerFeature instance;
        return &instance;
    }
    ~AbilityInnerFeature() = default;
private:
    AbilityInnerFeature();

    static int32 TerminateAppInvoke(const void *origin, IpcIo *req);
    static int32 DumpAbilityInvoke(const void *origin, IpcIo *req);

    static const char *GetFeatureName(Feature *feature);
    static void OnFeatureInitialize(Feature *feature, Service *parent, Identity identity);
    static void OnFeatureStop(Feature *feature, Identity identity);
    static BOOL OnFeatureMessage(Feature *feature, Request *request);

private:
    Identity identity_;
    static InvokeFunc invokeFuncList[COMMAND_END - INNER_BEGIN];
    DISALLOW_COPY_AND_MOVE(AbilityInnerFeature);
};

typedef struct {
    INHERIT_IUNKNOWNENTRY(AmsInnerInterface);
    AbilityInnerFeature *ams;
} AbilityInnerFeatureImpl;
} // namespace OHOS
#endif // OHOS_ABILITYMANAGERSERVICE_INNER_FEATURE_H
