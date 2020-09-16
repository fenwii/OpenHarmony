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

#ifndef OHOS_BUNDLE_INFO_CREATOR_H
#define OHOS_BUNDLE_INFO_CREATOR_H

#include <string>

#include "bundle_common.h"
#include "bundle_info.h"

namespace OHOS {
class BundleInfoCreator {
public:
    BundleInfoCreator() = default;
    ~BundleInfoCreator() = default;

    static BundleInfo *CreateBundleInfo(const BundleProfile &bundleProfile, const std::string &installDirPath,
        const std::string &dataDirPath, const BundleRes &bundleRes);
    static uint8_t SaveBundleInfo(const BundleProfile &bundleProfile, BundleInfo **bundleInfo);
private:
    static bool SetBundleInfo(const BundleProfile &bundleProfile, const std::string &installDirPath,
        const std::string &dataDirPath, BundleInfo *bundleInfo);
    static bool SetModuleInfos(const BundleProfile &bundleProfile, BundleInfo *bundleInfo);
    static bool SetAbilityInfos(const BundleProfile &bundleProfile, const std::string &codePath,
        BundleInfo *bundleInfo);
    static bool SetAbilityInfo(const BundleProfile &bundleProfile, const std::string &codePath,
        BundleInfo *bundleInfo, uint32_t index);
}; // namespace OHOS
}
#endif  // OHOS_BUNDLE_INFO_CREATOR_H