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

#ifndef OHOS_BUNDLEINFO_UTILS_H
#define OHOS_BUNDLEINFO_UTILS_H

#include "bundle_info.h"

namespace OHOS {
struct BundleInfoUtils {
    static void CopyBundleInfo(int32_t flags, BundleInfo *des, BundleInfo src);
    static bool SetBundleInfoBundleName(BundleInfo *bundleInfo, const char *bundleName);
    static bool SetBundleInfoVendor(BundleInfo *bundleInfo, const char *vendor);
    static bool SetBundleInfoLabel(BundleInfo *bundleInfo, const char *label);
    static bool SetBundleInfoVersionName(BundleInfo *bundleInfo, const char *versionName);
    static bool SetBundleInfoBigIconPath(BundleInfo *bundleInfo, const char *bigIconPath);
    static bool SetBundleInfoCodePath(BundleInfo *bundleInfo, const char *codePath);
    static bool SetBundleInfoDataPath(BundleInfo *bundleInfo, const char *dataPath);
    static bool SetBundleInfoModuleInfos(BundleInfo *bundleInfo, const ModuleInfo *moduleInfos, uint32_t numOfModule);
    static void ClearModuleInfos(ModuleInfo *moduleInfos, uint32_t numOfModule);
    static void FreeBundleInfos(BundleInfo *bundleInfos, uint32_t len);
    static void FreeBundleInfo(BundleInfo *bundleInfo);
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    static bool SetBundleInfoAppId(BundleInfo *bundleInfo, const char *appId);
    static bool SetBundleInfoSharedLibPath(BundleInfo *bundleInfo, const char *sharedLibPath);
    static bool SetBundleInfoAbilityInfos(BundleInfo *bundleInfo, const AbilityInfo *abilityInfos,
        uint32_t numOfAbility);
    static void ClearAbilityInfos(AbilityInfo *abilityInfos, uint32_t numOfAbility);
#else
    static bool SetBundleInfoSmallIconPath(BundleInfo *bundleInfo, const char *smallIconPath);
    static bool SetBundleInfoAbilityInfo(BundleInfo *bundleInfo, AbilityInfo abilityInfo);
#endif
private:
    BundleInfoUtils() = default;
    ~BundleInfoUtils() = default;
}; // BundleInfoUtils
} // OHOS
#endif // OHOS_BUNDLEINFO_UTILS_H