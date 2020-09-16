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

#include "hap_sign_verify.h"

#include "appexecfwk_errors.h"
#include "bundle_manager_service.h"
#include "log.h"

namespace OHOS {
uint8_t HapSignVerify::VerifySignature(const std::string &hapFilepath, SignatureInfo &signatureInfo)
{
    bool mode = ManagerService::GetInstance().IsDebugMode();
    HILOG_INFO(HILOG_MODULE_APP, "current mode is %d!", mode);
    VerifyResult verifyResult;
    // verify signature
    int32_t ret = APPVERI_AppVerify(hapFilepath.c_str(), &verifyResult);
    uint8_t errorCode = SwitchErrorCode(ret);
    if (errorCode != ERR_OK) {
        return errorCode;
    }

    signatureInfo.appId = verifyResult.profile.appid;
    signatureInfo.provisionBundleName = verifyResult.profile.bundleInfo.bundleName;
    int32_t restricNum = verifyResult.profile.permission.restricNum;
    for (int32_t i = 0; i < restricNum; i++) {
        signatureInfo.restrictedPermissions.emplace_back((verifyResult.profile.permission.restricPermission)[i]);
    }
    APPVERI_FreeVerifyRst(&verifyResult);
    return ERR_OK;
}

uint8_t HapSignVerify::SwitchErrorCode(int32_t errorCode)
{
    uint32_t errCode = static_cast<uint32_t>(errorCode);
    if (errCode >= V_ERR_GET_CERT_INFO && errCode <= V_ERR_GET_CERT_TYPE) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_APP_SIGNATURE_ERROR;
    } else if (errCode >= V_ERR_GET_PROFILE_DATA && errCode <= V_ERR_INVALID_DEVID) {
        return ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_SIGNATURE_ERROR;
    } else if (errCode >= V_ERR_FILE_OPEN && errCode <= V_ERR_FILE_LENGTH) {
        return ERR_APPEXECFWK_INSTALL_FAILED_OPERATE_SIGNED_FILE_ERROR;
    } else if ((errCode >= V_ERR_MEMSET && errCode <= V_ERR_MALLOC) || errCode == V_ERR) {
        return ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_SIGNATURE_ERROR;
    } else {
        return ERR_OK;
    }
}
} // namespace OHOS