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

#ifndef OHOS_BUNDLE_MANAGER_SERVICE_H
#define OHOS_BUNDLE_MANAGER_SERVICE_H

#include <map>
#include <vector>

#include "ability_service_interface.h"
#include "adapter.h"
#include "bundle_installer.h"
#include "bundle_info.h"
#include "bundle_map.h"
#include "cJSON.h"
#include "message.h"
#include "nocopyable.h"
#include "stdint.h"

namespace OHOS {
class ManagerService {
public:
    static ManagerService &GetInstance()
    {
        static ManagerService instance;
        return instance;
    }
    void ServiceMsgProcess(Request *request);
    BundleInfo *QueryBundleInfo(const char *bundleName);
    void RemoveBundleInfo(const char *bundleName);
    void AddBundleInfo(BundleInfo *info);
    uint8_t GetBundleInfo(const char *bundleName, int32_t flags, BundleInfo& bundleInfo);
    uint8_t GetBundleInfos(int32_t flags, BundleInfo **bundleInfos, int32_t *len);
    std::vector<SvcIdentity> GetServiceId() const;
    int32_t GenerateUid(const char *bundleName, int8_t bundleStyle);
    void RecycleUid(const char *bundleName);
    static bool GetAmsInterface(AmsInnerInterface **amsInterface);
    std::string GetSharedLibPath() const;
    std::string GetCodeDirPath() const;
    std::string GetDataDirPath() const;
    void SetSharedLibPath(const std::string &sharedLibPath);
    uint8_t SetExternalInstallMode(bool enable);
    bool IsExternalInstallMode() const;
    uint8_t SetDebugMode(bool enable);
    bool IsDebugMode() const;
#ifdef OHOS_DEBUG
    uint8_t SetSignMode(bool enable);
    bool IsSignMode() const;
#endif
private:
    ManagerService();
    ~ManagerService();

    void ScanPackages();
    void ScanSharedLibPath();
    void ScanAppDir(const char *appDir, const cJSON *uninstallRecord, int32_t scanFlag, bool isSystemApp);
    void InstallAllSystemBundle(int32_t scanFlag);
    void InstallSystemBundle(const char *fileDir, const char *fileName);
    void ReloadBundleInfo(const char *codePath, const char *appId, const char *bundleName, bool isSystemApp);
    void ReloadEntireBundleInfo(const char *appPath, const char *bundleName, int32_t versionCode, bool isSystemApp);
    bool CheckSystemBundleIsValid(const char *appPath, char **bundleName, int32_t &versionCode);
    bool CheckBundleHasInstalled(const char *bundleName);
    bool CheckThirdSystemBundleHasUninstalled(const char *bundleName, const cJSON *object);
    void InstallThirdBundle(const char *path, const SvcIdentity &svc);
    void AddCallbackServiceId(const SvcIdentity &svc);
    void RemoveCallbackServiceId(const SvcIdentity &svc);
    void RestoreUidAndGidMap();
    bool RecycleInnerUid(const std::string &bundleName, std::map<int, std::string> &innerMap);

    std::map<int, std::string> sysUidMap_;
    std::map<int, std::string> sysVendorUidMap_;
    std::map<int, std::string> appUidMap_;
    BundleInstaller *installer_;
    BundleMap *bundleMap_;
    std::vector<SvcIdentity> svcIdentity_;
    std::string sharedLibPath_;
    bool IsExternalInstallMode_ { false };
    bool isDebugMode_ { false };
#ifdef OHOS_DEBUG
    bool isSignMode_ { true };
#endif

    DISALLOW_COPY_AND_MOVE(ManagerService);
};
}
#endif // OHOS_BUNDLE_MANAGER_SERVICE_H
