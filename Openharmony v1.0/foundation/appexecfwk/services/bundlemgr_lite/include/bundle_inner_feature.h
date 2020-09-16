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

#ifndef OHOS_BUNDLE_INNER_FEATURE_H
#define OHOS_BUNDLE_INNER_FEATURE_H

#include "ability_info.h"
#include "bundle_inner_interface.h"
#include "bundle_manager.h"
#include "feature.h"
#include "iproxy_server.h"
#include "iunknown.h"
#include "nocopyable.h"
#include "ohos_types.h"
#include "want.h"

namespace OHOS {
typedef uint8_t (*BundleInvokeType)(const uint8_t funcId, IpcIo *req, IpcIo *reply);

class BundleInnerFeature : private Feature {
public:
    static BundleInnerFeature *GetInstance()
    {
        static BundleInnerFeature instance;
        return &instance;
    }
    ~BundleInnerFeature();
    static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply);

private:
    BundleInnerFeature();
    static const char *GetFeatureName(Feature *feature);
    static void OnFeatureInitialize(Feature *feature, Service *parent, Identity identity);
    static void OnFeatureStop(Feature *feature, Identity identity);
    static BOOL OnFeatureMessage(Feature *feature, Request *request);

    static uint8_t InstallInnerBundle(const uint8_t funcId, IpcIo *req, IpcIo *reply);
    static uint8_t UninstallInnerBundle(const uint8_t funcId, IpcIo *req, IpcIo *reply);
#ifdef OHOS_DEBUG
    static uint8_t SetExternalInstallMode(const uint8_t funcId, IpcIo *req, IpcIo *reply);
    static uint8_t SetInnerDebugMode(const uint8_t funcId, IpcIo *req, IpcIo *reply);
    static uint8_t SetInnerSignMode(const uint8_t funcId, IpcIo *req, IpcIo *reply);
#endif

    Identity identity_;
    static BundleInvokeType BundleMsInvokeFuc[BMS_CMD_END - BMS_INNER_BEGIN];

    DISALLOW_COPY_AND_MOVE(BundleInnerFeature);
};

struct SvcIdentityInfo {
    char *path;
    char *bundleName;
    SvcIdentity *svc;
};

typedef struct {
    INHERIT_IUNKNOWNENTRY(BmsInnerServerProxy);
    BundleInnerFeature *bundleInnerFeature;
} BmsInnerImpl;

IUnknown *GetBmsInnerFeatureApi(Feature *feature);
} // namespace OHOS
#endif // OHOS_BUNDLE_INNER_FEATURE_H
