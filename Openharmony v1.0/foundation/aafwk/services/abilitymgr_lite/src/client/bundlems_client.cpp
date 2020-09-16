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

#include "client/bundlems_client.h"

#include "appexecfwk_errors.h"
#include "samgr_lite.h"

namespace OHOS {
BundleMsClient::~BundleMsClient()
{
    bmsServerProxy_ = nullptr;
}

AbilityMsStatus BundleMsClient::Initialize()
{
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(BMS_SERVICE, BMS_FEATURE);
    if (iUnknown == nullptr) {
        return AbilityMsStatus::BmsQueryStatus("get bms feature api failure");
    }
    int result = iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **) &bmsServerProxy_);
    if (result != 0 || bmsServerProxy_ == nullptr) {
        return AbilityMsStatus::BmsQueryStatus("get bms interface failure");
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus BundleMsClient::QueryAbilityInfo(const Want *want, AbilityInfo *result) const
{
    if (bmsServerProxy_ == nullptr) {
        return AbilityMsStatus::BmsQueryStatus("bms server proxy is nullptr");
    }
    if (bmsServerProxy_->QueryAbilityInfo(want, result) != ERR_OK) {
        ClearAbilityInfo(result);
        return AbilityMsStatus::BmsQueryStatus("query ability info failure");
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus BundleMsClient::QueryBundleInfo(const char* bundleName, BundleInfo *bundleInfo) const
{
    if (bmsServerProxy_ == nullptr) {
        return AbilityMsStatus::BmsQueryStatus("bms service proxy is nullptr");
    }
    if (bmsServerProxy_->GetBundleInfo(bundleName, 1, bundleInfo) != ERR_OK) {
        return AbilityMsStatus::BmsQueryStatus("query bundle info failure");
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus BundleMsClient::QueryKeepAliveBundleInfos(BundleInfo **bundleInfos, int32_t *len) const
{
    if (bmsServerProxy_ == nullptr) {
        return AbilityMsStatus::BmsQueryStatus("bms service proxy is nullptr");
    }
    if (bmsServerProxy_->QueryKeepAliveBundleInfos(bundleInfos, len) != ERR_OK) {
        return AbilityMsStatus::BmsQueryStatus("query keep alive bundle info failure");
    }
    return AbilityMsStatus::Ok();
}
} // namespace OHOS
