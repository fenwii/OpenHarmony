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

#ifndef OHOS_BUNDLE_RES_TRANSFORM_H
#define OHOS_BUNDLE_RES_TRANSFORM_H

#include "bundle_common.h"
#include "bundle_info.h"

#include <string>

namespace OHOS {
class BundleResTransform {
public:
    BundleResTransform() = default;
    ~BundleResTransform() = default;

    static uint8_t ConvertResInfoToBundleInfo(const std::string &path, const BundleRes &bundleRes,
        BundleInfo *bundleInfo);
private:
    static bool ConvertIconResToBundleInfo(const std::string &path, uint32_t iconId, BundleInfo *bundleInfo,
        uint32_t index);
    static bool ConvertLableResToBundleInfo(const std::string &path, uint32_t labelId, BundleInfo *bundleInfo,
        uint32_t index);
    static bool ConvertDesResIdToBundleInfo(const std::string &path, uint32_t desId, BundleInfo *bundleInfo,
        uint32_t index);
}; // namespace OHOS
}
#endif  // OHOS_BUNDLE_RES_TRANSFORM_H