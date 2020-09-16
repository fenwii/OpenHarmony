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

#ifndef OHOS_BUNDLE_MS_FEATURE_H
#define OHOS_BUNDLE_MS_FEATURE_H

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

class BundleMsFeature : private Feature {
public:
    static BundleMsFeature *GetInstance()
    {
        static BundleMsFeature instance;
        return &instance;
    }
    ~BundleMsFeature();
    static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply);
    static uint8_t QueryAbilityInfo(const Want *want, AbilityInfo *abilityInfo);
    static uint8_t GetBundleInfo(const char *bundleName, int32_t flags, BundleInfo *bundleInfo);
    static uint8_t GetBundleInfos(int flags, BundleInfo **bundleInfos, int32_t *len);
    static uint8_t QueryKeepAliveBundleInfos(BundleInfo **bundleInfos, int32_t *len);
    static uint8_t GetBundleInfosByMetaData(const char *metaDataKey, BundleInfo **bundleInfos, int32_t *len);
    static uint8_t GetBundleNameForUid(int32_t uid, char **bundleName);

private:
    BundleMsFeature();
    static const char *GetFeatureName(Feature *feature);
    static void OnFeatureInitialize(Feature *feature, Service *parent, Identity identity);
    static void OnFeatureStop(Feature *feature, Identity identity);
    static BOOL OnFeatureMessage(Feature *feature, Request *request);

    bool BundleServiceTaskInit();
    static uint8_t HandleGetBundleInfos(const uint8_t funcId, IpcIo *req, IpcIo *reply);
    static uint8_t QueryInnerAbilityInfo(const uint8_t funcId, IpcIo *req, IpcIo *reply);
    static uint8_t GetInnerBundleInfo(const uint8_t funcId, IpcIo *req, IpcIo *reply);
    static uint8_t GetInnerBundleNameForUid(const uint8_t funcId, IpcIo *req, IpcIo *reply);
    static uint8_t ChangeInnerCallbackServiceId(const uint8_t funcId, IpcIo *req, IpcIo *reply);

    Identity identity_;
    static BundleInvokeType BundleMsInvokeFuc[BMS_INNER_BEGIN];

    DISALLOW_COPY_AND_MOVE(BundleMsFeature);
};

typedef struct {
    INHERIT_IUNKNOWNENTRY(BmsServerProxy);
    BundleMsFeature *bundleMsFeature;
} BmsImpl;

IUnknown *GetBmsFeatureApi(Feature *feature);
} // namespace OHOS
#endif // OHOS_BUNDLE_MS_FEATURE_H
