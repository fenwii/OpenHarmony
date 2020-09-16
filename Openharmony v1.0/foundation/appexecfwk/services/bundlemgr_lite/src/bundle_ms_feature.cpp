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

#include "bundle_ms_feature.h"

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
static BmsImpl g_bmsImpl = {
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = BundleMsFeature::Invoke,
    .QueryAbilityInfo = BundleMsFeature::QueryAbilityInfo,
    .GetBundleInfo = BundleMsFeature::GetBundleInfo,
    .GetBundleInfos = BundleMsFeature::GetBundleInfos,
    .QueryKeepAliveBundleInfos = BundleMsFeature::QueryKeepAliveBundleInfos,
    .GetBundleNameForUid = BundleMsFeature::GetBundleNameForUid,
    IPROXY_END
};

BundleInvokeType BundleMsFeature::BundleMsInvokeFuc[BMS_INNER_BEGIN] {
    QueryInnerAbilityInfo,
    GetInnerBundleInfo,
    ChangeInnerCallbackServiceId,
    GetInnerBundleNameForUid,
    HandleGetBundleInfos,
};

IUnknown *GetBmsFeatureApi(Feature *feature)
{
    g_bmsImpl.bundleMsFeature = reinterpret_cast<BundleMsFeature *>(feature);
    return GET_IUNKNOWN(g_bmsImpl);
}

static void Init()
{
    SamgrLite *sm = SAMGR_GetInstance();
    if (sm == nullptr) {
        return;
    }
    sm->RegisterFeature(BMS_SERVICE, reinterpret_cast<Feature *>(BundleMsFeature::GetInstance()));
    sm->RegisterFeatureApi(BMS_SERVICE, BMS_FEATURE,
        GetBmsFeatureApi(reinterpret_cast<Feature *>(BundleMsFeature::GetInstance())));
    HILOG_DEBUG(HILOG_MODULE_APP, "BundleMS feature start success");
}
APP_FEATURE_INIT(Init);

BundleMsFeature::BundleMsFeature() : identity_()
{
    this->Feature::GetName = BundleMsFeature::GetFeatureName;
    this->Feature::OnInitialize = BundleMsFeature::OnFeatureInitialize;
    this->Feature::OnStop = BundleMsFeature::OnFeatureStop;
    this->Feature::OnMessage = BundleMsFeature::OnFeatureMessage;
}

BundleMsFeature::~BundleMsFeature() {}

const char *BundleMsFeature::GetFeatureName(Feature *feature)
{
    (void) feature;
    return BMS_FEATURE;
}

void BundleMsFeature::OnFeatureInitialize(Feature *feature, Service *parent, Identity identity)
{
    if (feature == nullptr) {
        return;
    }
    (reinterpret_cast<BundleMsFeature *>(feature))->identity_ = identity;
    bool ret = GetInstance()->BundleServiceTaskInit();
    HILOG_DEBUG(HILOG_MODULE_APP, "BundleMS feature initialized, result is %d", ret);
}

void BundleMsFeature::OnFeatureStop(Feature *feature, Identity identity)
{
    (void) feature;
    (void) identity;
}

BOOL BundleMsFeature::OnFeatureMessage(Feature *feature, Request *request)
{
    if (feature == nullptr || request == nullptr) {
        return FALSE;
    }
    ManagerService::GetInstance().ServiceMsgProcess(request);
    return TRUE;
}

void static InnerFreeDataBuff(void *ptr)
{
    if (ptr != nullptr) {
        free(ptr);
    }
}

uint8_t BundleMsFeature::QueryInnerAbilityInfo(const uint8_t funcId, IpcIo *req, IpcIo *reply)
{
    if ((req == nullptr) || (reply == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    Want want;
    if (memset_s(&want, sizeof(Want), 0, sizeof(Want)) != EOK) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS feature memset want failed");
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }
    if (!DeserializeWant(&want, req)) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS feature deserialize failed");
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }
    AbilityInfo abilityInfo;
    if (memset_s(&abilityInfo, sizeof(AbilityInfo), 0, sizeof(AbilityInfo)) != EOK) {
        ClearWant(&want);
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS feature memset ability info failed");
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }
    uint8_t errorCode = QueryAbilityInfo(&want, &abilityInfo);
    ClearWant(&want);
    if (errorCode != OHOS_SUCCESS) {
        ClearAbilityInfo(&abilityInfo);
        return errorCode;
    }
    char *str = ConvertUtils::ConvertAbilityInfoToString(&abilityInfo);
    if (str == nullptr) {
        ClearAbilityInfo(&abilityInfo);
        return ERR_APPEXECFWK_SERIALIZATION_FAILED;
    }
    BuffPtr dataBuff = {.buffSz = strlen(str) + 1, .buff = str};
    IpcIoPushUint8(reply, static_cast<uint8_t>(OHOS_SUCCESS));
    IpcIoPushDataBuffWithFree(reply, &dataBuff, InnerFreeDataBuff);
    ClearAbilityInfo(&abilityInfo);
    return OHOS_SUCCESS;
}

uint8_t BundleMsFeature::GetInnerBundleInfo(const uint8_t funcId, IpcIo *req, IpcIo *reply)
{
    if ((req == nullptr) || (reply == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    size_t size = 0;
    char *bundleName = reinterpret_cast<char *>(IpcIoPopString(req, &size));
    if (bundleName == nullptr) {
        return ERR_APPEXECFWK_DESERIALIZATION_FAILED;
    }
    BundleInfo bundleInfo;
    if (memset_s(&bundleInfo, sizeof(BundleInfo), 0, sizeof(BundleInfo)) != EOK) {
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }
    uint8_t errorCode = GetBundleInfo(bundleName, IpcIoPopInt32(req), &bundleInfo);
    if (errorCode != OHOS_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_APP, "BundleMS GET_BUNDLE_INFO errorcode: %{public}d\n", errorCode);
        return errorCode;
    }
    char *str = ConvertUtils::ConvertBundleInfoToString(&bundleInfo);
    if (str == nullptr) {
        return ERR_APPEXECFWK_SERIALIZATION_FAILED;
    }
    BuffPtr dataBuff = {.buffSz = strlen(str) + 1, .buff = str};
    IpcIoPushUint8(reply, OHOS_SUCCESS);
    IpcIoPushDataBuffWithFree(reply, &dataBuff, InnerFreeDataBuff);
    return OHOS_SUCCESS;
}

uint8_t BundleMsFeature::HandleGetBundleInfos(const uint8_t funcId, IpcIo *req, IpcIo *reply)
{
    if ((req == nullptr) || (reply == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    BundleInfo *bundleInfos = nullptr;
    char *metaDataKey = nullptr;
    int32_t lengthOfBundleInfo = 0;
    uint8_t errorCode = 0;
    size_t length = 0;
    if (funcId == GET_BUNDLE_INFOS) {
        errorCode = GetBundleInfos(IpcIoPopInt32(req), &bundleInfos, &lengthOfBundleInfo);
    } else if (funcId == QUERY_KEEPALIVE_BUNDLE_INFOS) {
        errorCode = QueryKeepAliveBundleInfos(&bundleInfos, &lengthOfBundleInfo);
    } else if (funcId == GET_BUNDLE_INFOS_BY_METADATA) {
        metaDataKey = reinterpret_cast<char *>(IpcIoPopString(req, &length));
        if (metaDataKey == nullptr) {
            return ERR_APPEXECFWK_DESERIALIZATION_FAILED;
        }
        errorCode = GetBundleInfosByMetaData(metaDataKey, &bundleInfos, &lengthOfBundleInfo);
    } else {
        return ERR_APPEXECFWK_COMMAND_ERROR;
    }
    if (errorCode != OHOS_SUCCESS) {
        BundleInfoUtils::FreeBundleInfos(bundleInfos, lengthOfBundleInfo);
        return errorCode;
    }
    char *strs = ConvertUtils::ConvertBundleInfosToString(&bundleInfos, lengthOfBundleInfo);
    if (strs == nullptr) {
        BundleInfoUtils::FreeBundleInfos(bundleInfos, lengthOfBundleInfo);
        return ERR_APPEXECFWK_SERIALIZATION_FAILED;
    }
    BuffPtr dataBuff = {.buffSz = strlen(strs) + 1, .buff = strs};
    IpcIoPushUint8(reply, static_cast<uint8_t>(OHOS_SUCCESS));
    IpcIoPushInt32(reply, lengthOfBundleInfo);
    IpcIoPushDataBuffWithFree(reply, &dataBuff, InnerFreeDataBuff);
    BundleInfoUtils::FreeBundleInfos(bundleInfos, lengthOfBundleInfo);
    return OHOS_SUCCESS;
}

uint8_t BundleMsFeature::GetInnerBundleNameForUid(const uint8_t funcId, IpcIo *req, IpcIo *reply)
{
    if ((req == nullptr) || (reply == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    char *bundleName = nullptr;
    uint8_t errorCode = GetBundleNameForUid(IpcIoPopInt32(req), &bundleName);
    if (errorCode != OHOS_SUCCESS) {
        AdapterFree(bundleName);
        return errorCode;
    }
    IpcIoPushUint8(reply, static_cast<uint8_t>(OHOS_SUCCESS));
    IpcIoPushString(reply, bundleName);
    AdapterFree(bundleName);
    return errorCode;
}

uint8_t BundleMsFeature::ChangeInnerCallbackServiceId(const uint8_t funcId, IpcIo *req, IpcIo *reply)
{
    if ((req == nullptr) || (reply == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    bool flag = IpcIoPopBool(req);
    SvcIdentity *svc = IpcIoPopSvc(req);
    if (svc == nullptr) {
        return ERR_APPEXECFWK_DESERIALIZATION_FAILED;
    }

    auto svcIdentity = reinterpret_cast<SvcIdentity *>(AdapterMalloc(sizeof(SvcIdentity)));
    if (svcIdentity == nullptr) {
        return ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR;
    }
    *svcIdentity = *svc;
    Request request = {
        .msgId = BUNDLE_CHANGE_CALLBACK,
        .len = static_cast<int16>(sizeof(SvcIdentity)),
        .data = reinterpret_cast<void *>(svcIdentity),
        .msgValue = static_cast<uint32>(flag ? 1 : 0)
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != OHOS_SUCCESS) {
        AdapterFree(svcIdentity);
        return ERR_APPEXECFWK_UNINSTALL_FAILED_SEND_REQUEST_ERROR;
    }
    return ERR_OK;
}

int32 BundleMsFeature::Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    if (req == nullptr) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    IpcIoPushUint8(reply, static_cast<uint8_t>(funcId));
    uint8_t ret = OHOS_SUCCESS;
    if (funcId >= GET_BUNDLE_INFOS && funcId <= GET_BUNDLE_INFOS_BY_METADATA) {
        ret = BundleMsInvokeFuc[GET_BUNDLE_INFOS](funcId, req, reply);
    } else if (funcId >= QUERY_ABILITY_INFO && funcId <= GET_BUNDLENAME_FOR_UID) {
        ret = BundleMsInvokeFuc[funcId](funcId, req, reply);
    } else {
        ret = ERR_APPEXECFWK_COMMAND_ERROR;
    }

    if (ret != OHOS_SUCCESS) {
        IpcIoPushUint8(reply, ret);
    }
    return ret;
}

bool BundleMsFeature::BundleServiceTaskInit()
{
    Request request = {
        .msgId = BUNDLE_SERVICE_INITED,
        .len = 0,
        .data = nullptr,
        .msgValue = 0
    };
    int32 propRet = SAMGR_SendRequest(&identity_, &request, nullptr);
    if (propRet != OHOS_SUCCESS) {
        return false;
    }
    return true;
}

uint8_t BundleMsFeature::QueryAbilityInfo(const Want *want, AbilityInfo *abilityInfo)
{
    if ((abilityInfo == nullptr) || (want == nullptr) || (want->element == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }

    BundleInfo *bundleInfo = OHOS::ManagerService::GetInstance().QueryBundleInfo(want->element->bundleName);
    if (bundleInfo == nullptr) {
        return ERR_APPEXECFWK_QUERY_NO_INFOS;
    }

    if ((bundleInfo->abilityInfos == nullptr) || (bundleInfo->numOfAbility == 0)) {
        return ERR_APPEXECFWK_QUERY_NO_INFOS;
    }

    for (int32_t i = 0; i < bundleInfo->numOfAbility; ++i) {
        if ((want->element->abilityName != nullptr) && ((bundleInfo->abilityInfos)[i].name != nullptr) &&
            (strcmp(want->element->abilityName, (bundleInfo->abilityInfos)[i].name) == 0)) {
            OHOS::AbilityInfoUtils::CopyAbilityInfo(abilityInfo, bundleInfo->abilityInfos[i]);
            return OHOS_SUCCESS;
        }
    }
    return ERR_APPEXECFWK_QUERY_NO_INFOS;
}

uint8_t BundleMsFeature::GetBundleInfo(const char *bundleName, int32_t flags, BundleInfo *bundleInfo)
{
    return OHOS::ManagerService::GetInstance().GetBundleInfo(bundleName, flags, *bundleInfo);
}

uint8_t BundleMsFeature::GetBundleInfos(const int flags, BundleInfo **bundleInfos, int32_t *len)
{
    return OHOS::ManagerService::GetInstance().GetBundleInfos(flags, bundleInfos, len);
}

uint8_t BundleMsFeature::QueryKeepAliveBundleInfos(BundleInfo **bundleInfos, int32_t *len)
{
    if ((bundleInfos == nullptr) || (len == nullptr)) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    BundleInfo *allBundleInfos = nullptr;
    int32_t numOfAllBundleInfos = 0;
    uint8_t errorCode = GetBundleInfos(1, &allBundleInfos, &numOfAllBundleInfos);
    if (errorCode != OHOS_SUCCESS) {
        return errorCode;
    }
    *len = 0;
    for (int32_t i = 0; i < numOfAllBundleInfos; i++) {
        if (allBundleInfos[i].isKeepAlive && allBundleInfos[i].isSystemApp) {
            (*len)++;
        }
    }

    if (*len == 0) {
        BundleInfoUtils::FreeBundleInfos(allBundleInfos, numOfAllBundleInfos);
        return ERR_APPEXECFWK_QUERY_NO_INFOS;
    }
    *bundleInfos = reinterpret_cast<BundleInfo *>(AdapterMalloc(sizeof(BundleInfo) * (*len)));
    if (*bundleInfos == nullptr || memset_s(*bundleInfos, sizeof(BundleInfo) * (*len), 0,
        sizeof(BundleInfo) * (*len)) != EOK) {
        BundleInfoUtils::FreeBundleInfos(allBundleInfos, numOfAllBundleInfos);
        return ERR_APPEXECFWK_QUERY_INFOS_INIT_ERROR;
    }

    int32_t count = 0;
    for (int32_t i = 0; i < numOfAllBundleInfos && count < *len; i++) {
        if (allBundleInfos[i].isKeepAlive && allBundleInfos[i].isSystemApp) {
            OHOS::BundleInfoUtils::CopyBundleInfo(1, *bundleInfos + count, allBundleInfos[i]);
            count++;
        }
    }
    BundleInfoUtils::FreeBundleInfos(allBundleInfos, numOfAllBundleInfos);
    return OHOS_SUCCESS;
}

static bool CheckBundleInfoWithSpecialMetaData(const BundleInfo &bundleInfo, const char *metaDataKey)
{
    if (metaDataKey == nullptr) {
        return false;
    }

    for (int32_t i = 0; i < bundleInfo.numOfModule; i++) {
        for (int32_t j = 0; j < METADATA_SIZE; j++) {
            if ((bundleInfo.moduleInfos[i].metaData[j] != nullptr) &&
                (bundleInfo.moduleInfos[i].metaData[j]->name != nullptr) &&
                strcmp(metaDataKey, bundleInfo.moduleInfos[i].metaData[j]->name) == 0) {
                return true;
            }
        }
    }
    return false;
}

uint8_t BundleMsFeature::GetBundleInfosByMetaData(const char *metaDataKey, BundleInfo **bundleInfos, int32_t *len)
{
    if (metaDataKey == nullptr || bundleInfos == nullptr) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }

    BundleInfo *allBundleInfos = nullptr;
    int32_t numOfAllBundleInfos = 0;
    uint8_t errorCode = GetBundleInfos(1, &allBundleInfos, &numOfAllBundleInfos);
    if (errorCode != OHOS_SUCCESS) {
        return errorCode;
    }
    *len = 0;
    for (int32_t i = 0; i < numOfAllBundleInfos; i++) {
        if (CheckBundleInfoWithSpecialMetaData(allBundleInfos[i], metaDataKey)) {
            (*len)++;
        }
    }

    if (*len == 0) {
        BundleInfoUtils::FreeBundleInfos(allBundleInfos, numOfAllBundleInfos);
        return ERR_APPEXECFWK_QUERY_NO_INFOS;
    }

    *bundleInfos = reinterpret_cast<BundleInfo *>(AdapterMalloc(sizeof(BundleInfo) * (*len)));
    if (*bundleInfos == nullptr || memset_s(*bundleInfos, sizeof(BundleInfo) * (*len), 0,
        sizeof(BundleInfo) * (*len)) != EOK) {
        BundleInfoUtils::FreeBundleInfos(allBundleInfos, numOfAllBundleInfos);
        return ERR_APPEXECFWK_QUERY_INFOS_INIT_ERROR;
    }

    int32_t count = 0;
    for (int32_t i = 0; i < numOfAllBundleInfos && count < *len; i++) {
        if (CheckBundleInfoWithSpecialMetaData(allBundleInfos[i], metaDataKey)) {
            BundleInfoUtils::CopyBundleInfo(1, *bundleInfos + count, allBundleInfos[i]);
            count++;
        }
    }
    BundleInfoUtils::FreeBundleInfos(allBundleInfos, numOfAllBundleInfos);
    return OHOS_SUCCESS;
}

uint8_t BundleMsFeature::GetBundleNameForUid(int32_t uid, char **bundleName)
{
    if (bundleName == nullptr) {
        return ERR_APPEXECFWK_OBJECT_NULL;
    }
    BundleInfo *infos = nullptr;
    int32_t numOfInfos = 0;
    uint8_t errorCode = GetBundleInfos(0, &infos, &numOfInfos);
    if (errorCode != OHOS_SUCCESS) {
        BundleInfoUtils::FreeBundleInfos(infos, numOfInfos);
        return errorCode;
    }

    for (int i = 0; i < numOfInfos; ++i) {
        if (infos[i].uid == uid) {
            *bundleName = Utils::Strdup(infos[i].bundleName);
            break;
        }
    }
    BundleInfoUtils::FreeBundleInfos(infos, numOfInfos);
    if (*bundleName == nullptr) {
        return ERR_APPEXECFWK_NO_BUNDLENAME_FOR_UID;
    }
    return OHOS_SUCCESS;
}
} // namespace OHOS
