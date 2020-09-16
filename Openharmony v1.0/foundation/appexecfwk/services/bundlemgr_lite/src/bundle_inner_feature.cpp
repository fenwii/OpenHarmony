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

#include "bundle_inner_feature.h"

#include "ability_info_utils.h"
#include "appexecfwk_errors.h"
#include "bundle_info_utils.h"
#include "bundle_inner_interface.h"
#include "bundle_manager_service.h"
#include "bundle_message_id.h"
#include "convert_utils.h"
#include "hos_init.h"
#include "log.h"
#include "message.h"
#include "samgr_lite.h"
#include "securec.h"
#include "serializer.h"
#include "utils.h"
#include "want_utils.h"

namespace OHOS {
static BmsInnerImpl g_bmsInnerImpl = {
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = BundleInnerFeature::Invoke,
    IPROXY_END
};

BundleInvokeType BundleInnerFeature::BundleMsInvokeFuc[BMS_CMD_END - BMS_INNER_BEGIN] {
    InstallInnerBundle,
    UninstallInnerBundle,
#ifdef OHOS_DEBUG
    SetExternalInstallMode,
    SetInnerDebugMode,
    SetInnerSignMode,
#endif
};

IUnknown *GetBmsInnerFeatureApi(Feature *feature)
{
    g_bmsInnerImpl.bundleInnerFeature = reinterpret_cast<BundleInnerFeature *>(feature);
    return GET_IUNKNOWN(g_bmsInnerImpl);
}

static void Init()
{
    SamgrLite *sm = SAMGR_GetInstance();
    if (sm == nullptr) {
        return;
    }
    sm->RegisterFeature(BMS_SERVICE, reinterpret_cast<Feature *>(BundleInnerFeature::GetInstance()));
    sm->RegisterFeatureApi(BMS_SERVICE, BMS_INNER_FEATURE,
                           GetBmsInnerFeatureApi(reinterpret_cast<Feature *>(BundleInnerFeature::GetInstance())));
    HILOG_DEBUG(HILOG_MODULE_APP, "BundleMS inner feature start success");
}
APP_FEATURE_INIT(Init);

BundleInnerFeature::BundleInnerFeature() : identity_()
{
    this->Feature::GetName = BundleInnerFeature::GetFeatureName;
    this->Feature::OnInitialize = BundleInnerFeature::OnFeatureInitialize;
    this->Feature::OnStop = BundleInnerFeature::OnFeatureStop;
    this->Feature::OnMessage = BundleInnerFeature::OnFeatureMessage;
}

BundleInnerFeature::~BundleInnerFeature() {}

const char *BundleInnerFeature::GetFeatureName(Feature *feature)
{
    (void) feature;
    return BMS_INNER_FEATURE;
}

void BundleInnerFeature::OnFeatureInitialize(Feature *feature, Service *parent, Identity identity)
{
    if (feature == nullptr) {
        return;
    }
    (reinterpret_cast<BundleInnerFeature *>(feature))->identity_ = identity;
}

void BundleInnerFeature::OnFeatureStop(Feature *feature, Identity identity)
{
    (void) feature;
    (void) identity;
}

BOOL BundleInnerFeature::OnFeatureMessage(Feature *feature, Request *request)
{
    if (feature == nullptr || request == nullptr) {
        return FALSE;
    }
    ManagerService::GetInstance().ServiceMsgProcess(request);
    return TRUE;
}

uint8_t BundleInnerFeature::InstallInnerBundle(const uint8_t funcId, IpcIo *req, IpcIo *reply)
{
    if ((req == nullptr) || (reply == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }

    size_t length = 0;
    char *reqPath = reinterpret_cast<char *>(IpcIoPopString(req, &length));
    if (reqPath == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS inner feature deserialize install path failed");
        return ERR_APPEXECFWK_DESERIALIZATION_FAILED;
    }
    SvcIdentity *svc = IpcIoPopSvc(req);
    if (svc == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS inner feature deserialize serviceId failed");
        return ERR_APPEXECFWK_DESERIALIZATION_FAILED;
    }

    SvcIdentityInfo *info = reinterpret_cast<SvcIdentityInfo *>(AdapterMalloc(sizeof(SvcIdentityInfo)));
    if (info == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS inner feature malloc service info info failed");
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }
    info->path = Utils::Strdup(reqPath);
    if (info->path == nullptr) {
        AdapterFree(info);
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS inner feature malloc path failed");
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }
    info->bundleName = nullptr;
    info->svc = reinterpret_cast<SvcIdentity *>(AdapterMalloc(sizeof(SvcIdentity)));
    if (info->svc == nullptr) {
        AdapterFree(info->path);
        AdapterFree(info);
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS inner feature malloc serviceId failed");
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }
    *(info->svc) = *svc;
    Request request = {
        .msgId = BUNDLE_INSTALLED,
        .len = static_cast<int16>(sizeof(SvcIdentityInfo)),
        .data = reinterpret_cast<void *>(info),
        .msgValue = 0
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != OHOS_SUCCESS) {
        AdapterFree(info->path);
        AdapterFree(info->svc);
        AdapterFree(info);
        return ERR_APPEXECFWK_INSTALL_FAILED_SEND_REQUEST_ERROR;
    }
    return ERR_OK;
}

uint8_t BundleInnerFeature::UninstallInnerBundle(const uint8_t funcId, IpcIo *req, IpcIo *reply)
{
    if ((req == nullptr) || (reply == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    size_t length = 0;
    char *bundleName = reinterpret_cast<char *>(IpcIoPopString(req, &length));
    if (bundleName == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS inner feature deserialize bundle name failed");
        return ERR_APPEXECFWK_DESERIALIZATION_FAILED;
    }
    SvcIdentity *svc = IpcIoPopSvc(req);
    if (svc == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS inner feature deserialize serviceId failed");
        return ERR_APPEXECFWK_DESERIALIZATION_FAILED;
    }

    SvcIdentityInfo *info = reinterpret_cast<SvcIdentityInfo *>(AdapterMalloc(sizeof(SvcIdentityInfo)));
    if (info == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS inner feature malloc service info failed");
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }
    info->path = nullptr;
    info->bundleName = Utils::Strdup(bundleName);
    info->svc = reinterpret_cast<SvcIdentity *>(AdapterMalloc(sizeof(SvcIdentity)));
    if (info->svc == nullptr) {
        AdapterFree(info->bundleName);
        AdapterFree(info);
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS inner feature malloc serviceId failed");
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }
    *(info->svc) = *svc;
    Request request = {
        .msgId = BUNDLE_UNINSTALLED,
        .len = static_cast<int16>(sizeof(SvcIdentityInfo)),
        .data = reinterpret_cast<void *>(info),
        .msgValue = 0
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != OHOS_SUCCESS) {
        AdapterFree(info->bundleName);
        AdapterFree(info->svc);
        AdapterFree(info);
        return ERR_APPEXECFWK_UNINSTALL_FAILED_SEND_REQUEST_ERROR;
    }
    return ERR_OK;
}

#ifdef OHOS_DEBUG
uint8_t BundleInnerFeature::SetExternalInstallMode(const uint8_t funcId, IpcIo *req, IpcIo *reply)
{
    if ((req == nullptr) || (reply == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    uint8_t errorCode = OHOS::ManagerService::GetInstance().SetExternalInstallMode(IpcIoPopBool(req));
    if (errorCode == OHOS_SUCCESS) {
        IpcIoPushUint8(reply, static_cast<uint8_t>(OHOS_SUCCESS));
    }
    return errorCode;
}

uint8_t BundleInnerFeature::SetInnerDebugMode(const uint8_t funcId, IpcIo *req, IpcIo *reply)
{
    if ((req == nullptr) || (reply == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    uint8_t errorCode = OHOS::ManagerService::GetInstance().SetDebugMode(IpcIoPopBool(req));
    if (errorCode == OHOS_SUCCESS) {
        IpcIoPushUint8(reply, static_cast<uint8_t>(OHOS_SUCCESS));
    }
    return errorCode;
}

uint8_t BundleInnerFeature::SetInnerSignMode(const uint8_t funcId, IpcIo *req, IpcIo *reply)
{
    if ((req == nullptr) || (reply == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    uint8_t errorCode = OHOS::ManagerService::GetInstance().SetSignMode(IpcIoPopBool(req));
    if (errorCode == OHOS_SUCCESS) {
        IpcIoPushUint8(reply, static_cast<uint8_t>(OHOS_SUCCESS));
    }
    return errorCode;
}
#endif

int32 BundleInnerFeature::Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    if (req == nullptr) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    IpcIoPushUint8(reply, static_cast<uint8_t>(funcId));
    uint8_t ret = OHOS_SUCCESS;
#ifdef OHOS_DEBUG
    if ((funcId >= BMS_INNER_BEGIN) && (funcId < BMS_CMD_END)) {
#else
    if ((funcId >= BMS_INNER_BEGIN) && (funcId <= UNINSTALL)) {
#endif
        ret = BundleMsInvokeFuc[funcId - BMS_INNER_BEGIN](funcId, req, reply);
    } else {
        ret = ERR_APPEXECFWK_COMMAND_ERROR;
    }

    if (ret != OHOS_SUCCESS) {
        IpcIoPushUint8(reply, ret);
    }
    return ret;
}
} // namespace OHOS
