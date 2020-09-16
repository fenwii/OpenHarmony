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

#ifndef OHOS_BUNDLEMS_CLIENT_H
#define OHOS_BUNDLEMS_CLIENT_H

#include "bundle_inner_interface.h"
#include "util/abilityms_status.h"

namespace OHOS {
class BundleMsClient {
public:
    BundleMsClient() = default;
    ~BundleMsClient();
    AbilityMsStatus Initialize();

    AbilityMsStatus QueryAbilityInfo(const Want *want, AbilityInfo *result) const;
    AbilityMsStatus QueryBundleInfo(const char* bundleName, BundleInfo *bundleInfo) const;
    AbilityMsStatus QueryKeepAliveBundleInfos(BundleInfo **bundleInfos, int32_t *len) const;

private:
    BmsServerProxy *bmsServerProxy_ { nullptr };
};
}
#endif // OHOS_BUNDLEMS_CLIENT_H
