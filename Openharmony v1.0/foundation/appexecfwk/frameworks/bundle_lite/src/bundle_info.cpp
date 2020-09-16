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

#include "bundle_info.h"

#include "bundle_info_utils.h"
#include "securec.h"
#include "utils.h"

void ClearBundleInfo(BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr) {
        return;
    }
    AdapterFree(bundleInfo->bundleName);
    AdapterFree(bundleInfo->versionName);
    AdapterFree(bundleInfo->label);
    AdapterFree(bundleInfo->bigIconPath);
    AdapterFree(bundleInfo->codePath);
    AdapterFree(bundleInfo->dataPath);
    AdapterFree(bundleInfo->vendor);
    OHOS::BundleInfoUtils::ClearModuleInfos(bundleInfo->moduleInfos, bundleInfo->numOfModule);
    AdapterFree(bundleInfo->moduleInfos);
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    AdapterFree(bundleInfo->appId);
    AdapterFree(bundleInfo->sharedLibPath);
    OHOS::BundleInfoUtils::ClearAbilityInfos(bundleInfo->abilityInfos, bundleInfo->numOfAbility);
    AdapterFree(bundleInfo->abilityInfos);
#else
    AdapterFree(bundleInfo->smallIconPath);
    ClearAbilityInfo(bundleInfo->abilityInfo);
    AdapterFree(bundleInfo->abilityInfo);
#endif
}
