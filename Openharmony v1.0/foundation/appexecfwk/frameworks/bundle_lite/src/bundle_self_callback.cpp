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

#include "bundle_self_callback.h"

#include "adapter.h"
#include "bundle_callback_utils.h"
#include "bundle_manager.h"
#include "iproxy_client.h"
#include "log.h"
#include "samgr_lite.h"

namespace OHOS {
BundleSelfCallback::~BundleSelfCallback()
{
    if (svcIdentity_ != nullptr) {
        (void) UnRegisteIpcCallback(*svcIdentity_);
        AdapterFree(svcIdentity_);
    }
}

int32_t InnerCallback(const char *resultMessage, uint8_t resultCode, const InstallerCallback& installerCallback)
{
    if ((resultMessage == nullptr) || (installerCallback == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    if (resultCode == ERR_OK) {
        installerCallback(resultCode, resultMessage);
    } else {
        installerCallback(resultCode, ObtainErrorMessage(resultCode).c_str());
    }
    return ERR_OK;
}

int32_t BundleSelfCallback::Callback(const IpcContext* context, void *ipcMsg, IpcIo *io, void *arg)
{
    if (ipcMsg == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleSelfCallback ipcMsg is nullptr");
        return ERR_APPEXECFWK_OBJECT_NULL;
    }

    if (io == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleSelfCallback io is nullptr");
        FreeBuffer(NULL, ipcMsg);
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    InstallerCallback installerCallback = GetInstance().GetCallback();
    if (installerCallback == nullptr) {
        FreeBuffer(NULL, ipcMsg);
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    uint32_t installType = 0;
    int32_t ret = GetCode(ipcMsg, &installType);
    if (ret != LITEIPC_OK) {
        FreeBuffer(NULL, ipcMsg);
        HILOG_ERROR(HILOG_MODULE_APP, "BundleSelfCallback Get install type failed");
        return ERR_APPEXECFWK_CALLBACK_GET_INSTALLTYPE_FAILED;
    }
    auto resultCode = static_cast<uint8_t>(IpcIoPopInt32(io));
    FreeBuffer(NULL, ipcMsg);
    if (installType == INSTALL_CALLBACK) {
        return InnerCallback(INSTALL_SUCCESS, resultCode, installerCallback);
    }
    if (installType == UNINSTALL_CALLBACK) {
        return InnerCallback(UNINSTALL_SUCCESS, resultCode, installerCallback);
    }
    HILOG_ERROR(HILOG_MODULE_APP, "BundleSelfCallback get error install type");
    return ERR_APPEXECFWK_CALLBACK_GET_ERROR_INSTALLTYPE;
}

int32 BundleSelfCallback::GenerateLocalServiceId()
{
    svcIdentity_ = reinterpret_cast<SvcIdentity *>(AdapterMalloc(sizeof(SvcIdentity)));
    if (svcIdentity_ == nullptr) {
        return ERR_APPEXECFWK_CALLBACK_GENERATE_LOCAL_SERVICEID_FAILED;
    }

    int32_t ret = RegisteIpcCallback(Callback, 0, IPC_WAIT_FOREVER, svcIdentity_, NULL);
    if ((ret != LITEIPC_OK)) {
        AdapterFree(svcIdentity_);
        svcIdentity_ = nullptr;
        return ERR_APPEXECFWK_CALLBACK_GENERATE_LOCAL_SERVICEID_FAILED;
    }
    return ERR_OK;
}

const SvcIdentity *BundleSelfCallback::RegisterBundleSelfCallback(InstallerCallback &installerCallback)
{
    if (installerCallback == nullptr) {
        return nullptr;
    }
    if (svcIdentity_ == nullptr) {
        int32 ret = GenerateLocalServiceId();
        if (ret != ERR_OK) {
            return nullptr;
        }
    }
    installerCallback_ = installerCallback;
    return svcIdentity_;
}

const InstallerCallback BundleSelfCallback::GetCallback()
{
    return installerCallback_;
}
} // namespace
