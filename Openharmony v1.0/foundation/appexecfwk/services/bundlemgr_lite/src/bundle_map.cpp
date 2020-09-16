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

#include "bundle_map.h"

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
#include <pthread.h>
#else
#include "cmsis_os2.h"
#endif
#include "adapter.h"
#include "appexecfwk_errors.h"
#include "bundle_info_utils.h"
#include "utils.h"

namespace OHOS {
const int32_t GET_BUNDLE_WITH_ABILITIES = 1;
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
static pthread_mutex_t g_bundleListMutex = PTHREAD_MUTEX_INITIALIZER;
#else
const int32_t BUNDLELIST_MUTEX_TIMEOUT = 2000;
static osMutexId_t g_bundleListMutex;
#endif

BundleMap::BundleMap()
{
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    pthread_mutex_init(&g_bundleListMutex, nullptr);
#else
    g_bundleListMutex = osMutexNew(reinterpret_cast<osMutexAttr_t *>(NULL));
#endif
    bundleInfos_ = new List<BundleInfo *>();
}

BundleMap::~BundleMap()
{
    MutexDelete(&g_bundleListMutex);
    delete bundleInfos_;
    bundleInfos_ = nullptr;
}

void BundleMap::Add(BundleInfo *bundleInfo)
{
    if (bundleInfo == nullptr) {
        return;
    }

    if (Get(bundleInfo->bundleName) == nullptr) {
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
        MutexAcquire(&g_bundleListMutex, 0);
#else
        MutexAcquire(&g_bundleListMutex, BUNDLELIST_MUTEX_TIMEOUT);
#endif
        bundleInfos_->PushFront(bundleInfo);
        MutexRelease(&g_bundleListMutex);
    }
}

BundleInfo *BundleMap::Get(const char *bundleName) const
{
    if (bundleName == nullptr) {
        return nullptr;
    }

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    MutexAcquire(&g_bundleListMutex, 0);
#else
    MutexAcquire(&g_bundleListMutex, BUNDLELIST_MUTEX_TIMEOUT);
#endif
    for (auto node = bundleInfos_->Begin(); node != bundleInfos_->End(); node = node->next_) {
        BundleInfo *info = node->value_;
        if (info != nullptr && info->bundleName != nullptr && strcmp(info->bundleName, bundleName) == 0) {
            MutexRelease(&g_bundleListMutex);
            return info;
        }
    }
    MutexRelease(&g_bundleListMutex);
    return nullptr;
}

void BundleMap::GetCopyBundleInfo(uint32_t flags, const BundleInfo *bundleInfo, BundleInfo &newBundleInfo) const
{
    if (bundleInfo == nullptr) {
        return;
    }
    newBundleInfo.isSystemApp = bundleInfo->isSystemApp;
    newBundleInfo.versionCode = bundleInfo->versionCode;
    newBundleInfo.bundleName = bundleInfo->bundleName;
    newBundleInfo.label = bundleInfo->label;
    newBundleInfo.versionName = bundleInfo->versionName;
    newBundleInfo.codePath = bundleInfo->codePath;
    newBundleInfo.dataPath = bundleInfo->dataPath;
    newBundleInfo.compatibleApi = bundleInfo->compatibleApi;
    newBundleInfo.targetApi = bundleInfo->targetApi;
    newBundleInfo.vendor = bundleInfo->vendor;
    newBundleInfo.bigIconPath = bundleInfo->bigIconPath;
    newBundleInfo.moduleInfos = bundleInfo->moduleInfos;
    newBundleInfo.numOfModule = bundleInfo->numOfModule;
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    newBundleInfo.appId = bundleInfo->appId;
    newBundleInfo.sharedLibPath = bundleInfo->sharedLibPath;
    newBundleInfo.isKeepAlive = bundleInfo->isKeepAlive;
    newBundleInfo.isNativeApp = bundleInfo->isNativeApp;
    newBundleInfo.uid = bundleInfo->uid;
    newBundleInfo.gid = bundleInfo->gid;
    if (flags == GET_BUNDLE_WITH_ABILITIES) {
        newBundleInfo.abilityInfos = bundleInfo->abilityInfos;
        newBundleInfo.numOfAbility = bundleInfo->numOfAbility;
    } else {
        newBundleInfo.abilityInfos = nullptr;
        newBundleInfo.numOfAbility = 0;
    }
#else
    newBundleInfo.smallIconPath = bundleInfo->smallIconPath;
    if (flags == GET_BUNDLE_WITH_ABILITIES) {
        newBundleInfo.abilityInfo = bundleInfo->abilityInfo;
    } else {
        newBundleInfo.abilityInfo = nullptr;
    }
#endif
}

uint8_t BundleMap::GetBundleInfos(int32_t flags, BundleInfo **bundleInfos, int32_t *len) const
{
    if (bundleInfos == nullptr) {
        return ERR_APPEXECFWK_QUERY_PARAMETER_ERROR;
    }
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    MutexAcquire(&g_bundleListMutex, 0);
#else
    MutexAcquire(&g_bundleListMutex, BUNDLELIST_MUTEX_TIMEOUT);
#endif
    if (bundleInfos_->IsEmpty()) {
        MutexRelease(&g_bundleListMutex);
        return ERR_APPEXECFWK_QUERY_NO_INFOS;
    }

    BundleInfo *infos = reinterpret_cast<BundleInfo *>(AdapterMalloc(sizeof(BundleInfo) * bundleInfos_->Size()));
    if (infos == nullptr || memset_s(infos, sizeof(BundleInfo) * bundleInfos_->Size(), 0,
        sizeof(BundleInfo) * bundleInfos_->Size()) != EOK) {
        AdapterFree(infos);
        MutexRelease(&g_bundleListMutex);
        return ERR_APPEXECFWK_QUERY_INFOS_INIT_ERROR;
    }
    *bundleInfos = infos;

    for (auto node = bundleInfos_->Begin(); node != bundleInfos_->End(); node = node->next_) {
        BundleInfoUtils::CopyBundleInfo(flags, infos++, *(node->value_));
    }

    *len = bundleInfos_->Size();
    MutexRelease(&g_bundleListMutex);
    return ERR_OK;
}

uint8_t BundleMap::GetBundleInfo(const char *bundleName, int32_t flags, BundleInfo &bundleInfo) const
{
    if (bundleName == nullptr) {
        return ERR_APPEXECFWK_QUERY_PARAMETER_ERROR;
    }

    BundleInfo *specialBundleInfo = Get(bundleName);
    if (specialBundleInfo == nullptr) {
        return ERR_APPEXECFWK_QUERY_NO_INFOS;
    }

    GetCopyBundleInfo(flags, specialBundleInfo, bundleInfo);
    return ERR_OK;
}

void BundleMap::Erase(const char *bundleName)
{
    if (bundleName == nullptr) {
        return;
    }
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    MutexAcquire(&g_bundleListMutex, 0);
#else
    MutexAcquire(&g_bundleListMutex, BUNDLELIST_MUTEX_TIMEOUT);
#endif
    for (auto node = bundleInfos_->Begin(); node != bundleInfos_->End(); node = node->next_) {
        BundleInfo *info = node->value_;
        if (info->bundleName != nullptr && strcmp(info->bundleName, bundleName) == 0) {
            ClearBundleInfo(info);
            AdapterFree(info);
            bundleInfos_->Remove(node);
            MutexRelease(&g_bundleListMutex);
            return;
        }
    }
    MutexRelease(&g_bundleListMutex);
}

void BundleMap::EraseAll()
{
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    MutexAcquire(&g_bundleListMutex, 0);
#else
    MutexAcquire(&g_bundleListMutex, BUNDLELIST_MUTEX_TIMEOUT);
#endif
    for (auto node = bundleInfos_->Begin(); node != bundleInfos_->End(); node = node->next_) {
        ClearBundleInfo(node->value_);
        AdapterFree(node->value_);
    }
    bundleInfos_->RemoveAll();
    MutexRelease(&g_bundleListMutex);
}
}  // namespace OHOS
