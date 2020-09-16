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

#ifndef OHOS_GT_BUNDLE_MANAGER_SERVICE_H
#define OHOS_GT_BUNDLE_MANAGER_SERVICE_H

#include "adapter.h"
#include "bundle_info.h"
#include "bundle_map.h"
#include "cJSON.h"
#include "gt_bundle_installer.h"
#include "stdint.h"

namespace OHOS {
class GtManagerService {
public:
    static GtManagerService &GetInstance()
    {
        static GtManagerService instance;
        return instance;
    }
    void ServiceMsgProcess(MC_MSG_S *msg);
    void SendBundleListChangedToLauncher(BundleState state, const char *bundleName);
    BundleInfo *QueryBundleInfo(const char *bundleName);
    void RemoveBundleInfo(const char *bundleName);
    void AddBundleInfo(BundleInfo *info);
    uint8_t GetBundleInfo(const char *bundleName, int32_t flags, BundleInfo& bundleInfo);
    uint8_t GetBundleInfos(int32_t flags, BundleInfo **bundleInfos, int32_t *len);
    char *GetAppIdByBundleName(const char *bundleName);
    uint32_t GetVersionCodeByBundlePath(const char *path, unsigned char *versionCode, uint8_t length);
    uint8_t DumpBundleInfos(char **bundles);

private:
    GtManagerService();
    ~GtManagerService();
    void ScanPackages();
    void ScanAppDir(const char *appDir, const cJSON *uninstallRecord, uint8_t scanFlag, bool isSystemApp);
    void InstallAllSystemBundle(uint8_t scanFlag);
    void InstallSystemBundle(const char *fileDir, const char *fileName);
    void ReloadBundleInfo(const char *profileDir, bool isSystemApp);
    void ReloadEntireBundleInfo(const char *appPath, const char *bundleName, int32_t versionCode, bool isSystemApp);
    bool CheckSystemBundleIsValid(const char *appPath, char **bundleName, int32_t &versionCode);
    bool CheckBundleHasInstalled(const char *bundleName);
    bool CheckThirdSystemBundleHasUninstalled(const char *bundleName, const cJSON *object);
    void BundleFactoryReset();
    void ClearBundleInfos(BundleInfo *bundleInfos, int32_t len);

    GtBundleInstaller *installer_;
    bool bundleSvcStop_ { false };
    BundleMap *bundleMap_;
};
}
#endif // OHOS_GT_BUNDLE_MANAGER_SERVICE_H
