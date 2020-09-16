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

#ifndef OHOS_BUNDLE_CALLBACK_H
#define OHOS_BUNDLE_CALLBACK_H

#include <string>
#include <string.h>
#include <algorithm>
#include <unordered_map>
#include <vector>

#include "appexecfwk_errors.h"
#include "bundle_callback_utils.h"
#include "liteipc_adapter.h"
#include "nocopyable.h"

namespace OHOS {
class BundleCallback {
public:
    ~BundleCallback();
    static BundleCallback& GetInstance()
    {
        static BundleCallback instance;
        return instance;
    }

    int32_t RegisterBundleStateCallback(const BundleStateCallback &callback, const char *bundleName, void *data);
    int32_t UnregisterBundleStateCallback();
    int32_t GenerateLocalServiceId();
    int32_t TransmitServiceId(const SvcIdentity &svc, bool flag);
    BundleCallbackInfo GetCallbackInfoByName(const char *bundleName);
private:
    BundleCallback() = default;

    BundleStateCallback bundleStateCallback_ { nullptr }; // register callback for all apps
    SvcIdentity *svcIdentity_ { nullptr };
    void *innerData_ { nullptr };
    std::unordered_map<std::string, BundleCallbackInfo> callbackMap_ {};

    DISALLOW_COPY_AND_MOVE(BundleCallback);
};
} // namespace OHOS
#endif // OHOS_BUNDLE_CALLBACK_H