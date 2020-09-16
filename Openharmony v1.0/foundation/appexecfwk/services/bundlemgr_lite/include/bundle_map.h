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

#ifndef OHOS_BUNDLE_MAP_H
#define OHOS_BUNDLE_MAP_H

#include "bundle_info.h"
#include "nocopyable.h"
#include "stdint.h"
#include "utils_list.h"

namespace OHOS {
class BundleMap {
public:
    static BundleMap *GetInstance()
    {
        static BundleMap instance;
        return &instance;
    }
    ~BundleMap();

    void Add(BundleInfo *bundleInfo);
    BundleInfo *Get(const char *bundleName) const;
    uint8_t GetBundleInfos(int32_t flags, BundleInfo **bundleInfos, int32_t *len) const;
    uint8_t GetBundleInfo(const char *bundleName, int32_t flags, BundleInfo &bundleInfo) const;
    void Erase(const char *bundleName);
    void EraseAll();

private:
    BundleMap();
    void GetCopyBundleInfo(uint32_t flags, const BundleInfo *bundleInfo, BundleInfo &newBundleInfo) const;
    List<BundleInfo *> *bundleInfos_;

    DISALLOW_COPY_AND_MOVE(BundleMap);
};
} // namespace OHOS
#endif  // OHOS_BUNDLE_MAP_H