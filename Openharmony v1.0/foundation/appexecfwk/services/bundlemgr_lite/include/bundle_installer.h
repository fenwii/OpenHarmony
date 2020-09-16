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

#ifndef OHOS_BUNDLE_INSTALLER_H
#define OHOS_BUNDLE_INSTALLER_H

#include "bundle_common.h"
#include "bundle_info.h"
#include "bundle_info_utils.h"
#ifndef __LINUX__
#include "hap_sign_verify.h"
#endif
#include "stdint.h"

#include <string>
#include <vector>

namespace OHOS {
class BundleInstaller {
public:
    BundleInstaller(const std::string &codeDirPath, const std::string &dataDirPath);
    ~BundleInstaller();

    uint8_t Install(const char *path);
    uint8_t Uninstall(const char *bundleName);
    std::string GetCodeDirPath() const;
    std::string GetDataDirPath() const;
private:
    uint8_t ProcessBundleInstall(const std::string &path, InstallRecord &installRecord, uint8_t hapType);
    uint8_t HandleFileAndBackUpRecord(const char *tmpPath, const char *realPath, InstallRecord &record,
        bool isUpdate, uint8_t hapType);
    uint8_t UpdateBundleInfo(const char *appId, const BundleRes &bundleRes, BundleInfo *bundleInfo, bool isUpdate,
        uint8_t hapType);
#ifndef __LINUX__
    uint8_t CheckProvisionInfoIsValid(const SignatureInfo &signatureInfo, const Permissions &permissions,
        const char *bundleName);
#endif
    bool MatchPermissions(const std::vector<std::string> & restrictedPermissions,
        PermissionTrans *permissionsTrans, int32_t permTransNum);
    bool MatchBundleName(const char *bundleName, const char *matchedBundleName);
    uint8_t CheckInstallFileIsValid(const char *path);
    void RecordThirdSystemBundle(const char *bundleName, const char *path);
    uint8_t StorePermissions(const char *bundleName, PermissionTrans *permissions, int32_t permNum, bool isUpdate);
    uint8_t CheckVersionAndSignature(const char *bundleName, BundleInfo *bundleInfo);
    bool RenameJsonFile(const char *fileName);
    bool CheckIsThirdSystemBundle(const char *bundleName);
    bool BackUpInstallRecord(const InstallRecord &record, const char *jsonPath);
    void InitThirdSystemBundleRecord(const char *bundleName, const char *path);
    bool BackUpUidAndGidInfo(const InstallRecord &record, const char *jsonPath);
    void ModifyInstallDirByHapType(uint8_t hapType);
    uint8_t GetHapType(const char *path);

    std::string codeDirPath_;
    std::string dataDirPath_;
};

#define CHECK_PRO_RESULT(errcode, bundleInfo, permissions, abilityRes)       \
    do {                                                                     \
        if (errcode != ERR_OK) {                                             \
            ClearBundleInfo(bundleInfo);                                     \
            AdapterFree(bundleInfo);                                         \
            AdapterFree(permissions.permissionTrans);                        \
            AdapterFree(abilityRes);                                         \
            return errcode;                                                  \
        }                                                                    \
    } while (0)

#define CLEAR_INSTALL_ENV(bundleInfo)                                        \
    do {                                                                     \
        if (bundleInfo != nullptr) {                                         \
            BundleDaemonClient::GetInstance().RemoveInstallDirectory(        \
                bundleInfo->codePath, bundleInfo->dataPath);                 \
            BundleInfoUtils::FreeBundleInfo(bundleInfo);                     \
        }                                                                    \
    } while (0)

#define CHECK_PRO_ROLLBACK(errcode, permissions, bundleInfo, abilityRes)     \
    do {                                                                     \
        if (errcode != ERR_OK && bundleInfo != nullptr) {                    \
            BundleUtil::DeleteJsonFile(bundleInfo->bundleName);              \
            CLEAR_INSTALL_ENV(bundleInfo);                                   \
            AdapterFree(permissions.permissionTrans);                        \
            AdapterFree(abilityRes);                                         \
            return errcode;                                                  \
        }                                                                    \
    } while (0)
} // namespace OHOS
#endif // OHOS_BUNDLE_INSTALLER_H
