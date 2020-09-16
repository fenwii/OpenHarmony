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

#include "ability_mgr_feature.h"

#include "ability_connect_trans_param.h"
#include "ability_errors.h"
#include "ability_info.h"
#include "ability_message_id.h"
#include "ability_mgr_handler.h"
#include "ability_service_interface.h"
#include "adapter.h"
#include "hos_init.h"
#include "iproxy_client.h"
#include "samgr_lite.h"
#include "securec.h"
#include "util/abilityms_helper.h"
#include "utils.h"
#include "want_utils.h"

namespace OHOS {
AbilityMgrFeatureImpl g_amsImpl = {
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = AbilityMgrFeature::Invoke,
    .StartAbility = AbilityMgrFeature::StartAbility,
    .TerminateAbility = AbilityMgrFeature::TerminateAbility,
    .ConnectAbility = AbilityMgrFeature::ConnectAbility,
    .DisconnectAbility = AbilityMgrFeature::DisconnectAbility,
    .StopAbility = AbilityMgrFeature::StopAbility,
    IPROXY_END
};

InvokeFunc AbilityMgrFeature::invokeFuncList[INNER_BEGIN] {
    AbilityMgrFeature::StartAbilityInvoke,
    AbilityMgrFeature::TerminateAbilityInvoke,
    AbilityMgrFeature::AttachBundleInvoke,
    AbilityMgrFeature::ConnectAbilityInvoke,
    AbilityMgrFeature::ConnectAbilityDoneInvoke,
    AbilityMgrFeature::DisconnectAbilityInvoke,
    AbilityMgrFeature::DisconnectAbilityDoneInvoke,
    AbilityMgrFeature::AbilityTransactionDoneInvoke,
    AbilityMgrFeature::StopAbilityInvoke,
};

static void Init()
{
    SamgrLite *samgrLite = SAMGR_GetInstance();
    CHECK_NULLPTR_RETURN(samgrLite, "AbilityMgrFeature", "get samgr error");
    BOOL result = samgrLite->RegisterFeature(AMS_SERVICE, AbilityMgrFeature::GetInstance());
    if (result == FALSE) {
        PRINTE("AbilityMgrFeature", "ams register feature failure");
        return;
    }
    g_amsImpl.ams = AbilityMgrFeature::GetInstance();
    auto publicApi = GET_IUNKNOWN(g_amsImpl);
    CHECK_NULLPTR_RETURN(publicApi, "AbilityMgrFeatureLite", "publicApi is nullptr");
    BOOL apiResult = samgrLite->RegisterFeatureApi(AMS_SERVICE, AMS_FEATURE, publicApi);
    PRINTI("AbilityMgrFeature", "ams feature init %{public}s", apiResult ? "success" : "failure");
}
SYSEX_FEATURE_INIT(Init);

AbilityMgrFeature::AbilityMgrFeature() : Feature(), identity_()
{
    this->Feature::GetName = AbilityMgrFeature::GetFeatureName;
    this->Feature::OnInitialize = AbilityMgrFeature::OnFeatureInitialize;
    this->Feature::OnStop = AbilityMgrFeature::OnFeatureStop;
    this->Feature::OnMessage = AbilityMgrFeature::OnFeatureMessage;
}

int32 AbilityMgrFeature::Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    PRINTI("AbilityMgrFeature", "ams invoke called");
    if (req == nullptr) {
        return EC_INVALID;
    }
    if (funcId >= START_ABILITY && funcId < INNER_BEGIN) {
        return invokeFuncList[funcId](origin, req);
    }
    return COMMAND_ERROR;
}

const char *AbilityMgrFeature::GetFeatureName(Feature *feature)
{
    (void) feature;
    return AMS_FEATURE;
}

void AbilityMgrFeature::OnFeatureInitialize(Feature *feature, Service *parent, Identity identity)
{
    CHECK_NULLPTR_RETURN(feature, "AbilityMgrFeature", "initialize fail");
    (static_cast<AbilityMgrFeature *>(feature))->identity_ = identity;
    AbilityMgrHandler::GetInstance().Init();
}

void AbilityMgrFeature::OnFeatureStop(Feature *feature, Identity identity)
{
    (void) feature;
    (void) identity;
}

BOOL AbilityMgrFeature::OnFeatureMessage(Feature *feature, Request *request)
{
    if (feature == nullptr || request == nullptr) {
        return FALSE;
    }

    AbilityMgrHandler::GetInstance().ServiceMsgProcess(*request);
    return TRUE;
}

int32 AbilityMgrFeature::StartAbilityInvoke(const void *origin, IpcIo *req)
{
    pid_t uid = GetCallingUid(origin);
    if (uid < 0) {
        PRINTE("AbilityMgrFeature", "invalid uid argument");
        return EC_INVALID;
    }
    Want want = { nullptr, nullptr, nullptr, 0 };
    if (!DeserializeWant(&want, req)) {
        return EC_FAILURE;
    }
    int retVal = StartAbilityInner(&want, uid);
    ClearWant(&want);
    return retVal;
}

int32 AbilityMgrFeature::StartAbility(const Want *want)
{
    return StartAbilityInner(want, -1);
}

int32 AbilityMgrFeature::StartAbilityInner(const Want *want, pid_t callingUid)
{
    if (want == nullptr || want->element == nullptr) {
        PRINTE("AbilityMgrFeature", "invalid argument");
        return EC_INVALID;
    }
    Want *data = new Want();
    if (memset_s(data, sizeof(Want), 0, sizeof(Want)) != EOK) {
        PRINTE("AbilityMgrFeature", "memory alloc error");
        delete data;
        return EC_NOMEMORY;
    }
    SetWantElement(data, *(want->element));
    SetWantData(data, want->data, want->dataLength);
    if (want->sid != nullptr) {
        SetWantSvcIdentity(data, *(want->sid));
    }
    Request request = {
        .msgId = AMS_START_ABILITY,
        .len = 0,
        .data = reinterpret_cast<void *>(data),
        .msgValue = static_cast<uint32>(callingUid),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityMgrFeature", "send request failure");
        ClearWant(data);
        delete data;
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityMgrFeature::TerminateAbilityInvoke(const void *origin, IpcIo *req)
{
    uint64_t token = IpcIoPopUint64(req);
    return TerminateAbility(token);
}

int32 AbilityMgrFeature::TerminateAbility(uint64_t token)
{
    uint64_t *terminateToken = new uint64_t;
    *terminateToken = token;
    Request request = {
        .msgId = AMS_TERMINATE_ABILITY,
        .len = 0,
        .data = reinterpret_cast<void *>(terminateToken),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityMgrFeature", "send request failure");
        delete terminateToken;
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityMgrFeature::AbilityTransactionDoneInvoke(const void *origin, IpcIo *req)
{
    uint64_t token = IpcIoPopUint64(req);
    int32 state = IpcIoPopInt32(req);
    TransactionState *transactionState = new TransactionState();
    transactionState->token = token;
    transactionState->state = state;
    Request request = {
        .msgId = AMS_TRANSACTION_DONE,
        .len = 0,
        .data = reinterpret_cast<void *>(transactionState),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityMgrFeature", "send request failure");
        delete transactionState;
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityMgrFeature::AttachBundleInvoke(const void *origin, IpcIo *req)
{
    pid_t callingPid = GetCallingPid(origin);
    if (callingPid < 0) {
        PRINTE("AbilityMgrFeature", "invalid pid argument");
        return EC_INVALID;
    }
    uint64_t token = IpcIoPopUint64(req);
    SvcIdentity *svcIdentity = IpcIoPopSvc(req);
    if (svcIdentity == nullptr) {
        return EC_INVALID;
    }
    auto client = new AbilityThreadClient(token, callingPid,
        *svcIdentity, &AbilityMgrFeature::AppDeathNotify);
    Request request = {
        .msgId = AMS_ATTACH_BUNDLE,
        .len = 0,
        .data = reinterpret_cast<void *>(client),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityMgrFeature", "send request failure");
        delete client;
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityMgrFeature::ConnectAbilityInvoke(const void *origin, IpcIo *req)
{
    pid_t uid = GetCallingUid(origin);
    if (uid < 0) {
        PRINTE("AbilityMgrFeature", "invalid uid argument");
        return EC_INVALID;
    }
    uint64_t token = IpcIoPopUint64(req);
    SvcIdentity* sid = IpcIoPopSvc(req);
    Want want = { nullptr, nullptr, nullptr, 0 };
    if (!DeserializeWant(&want, req)) {
        return EC_FAILURE;
    }
    int32 retVal = ConnectAbilityInner(&want, sid, token, uid);
    ClearWant(&want);
    return retVal;
}

int32 AbilityMgrFeature::ConnectAbility(const Want *want, SvcIdentity *svc, uint64_t token)
{
    return ConnectAbilityInner(want, svc, token, -1);
}

int32 AbilityMgrFeature::ConnectAbilityInner(const Want *want, SvcIdentity *svc, uint64_t token, pid_t callingUid)
{
    if (want == nullptr || want->element == nullptr || svc == nullptr) {
        return EC_INVALID;
    }
    Want *data = new Want();
    if (memset_s(data, sizeof(Want), 0, sizeof(Want)) != EOK) {
        delete data;
        PRINTE("AbilityMgrFeature", "memory alloc error");
        return EC_NOMEMORY;
    }
    SetWantElement(data, *(want->element));
    SetWantData(data, want->data, want->dataLength);
    if (want->sid != nullptr) {
        SetWantSvcIdentity(data, *(want->sid));
    }
    auto transParam = new AbilityConnectTransParam(data, *svc, token);
    transParam->SetCallingUid(callingUid);
    Request request = {
        .msgId = AMS_CONNECT_ABILITY,
        .len = 0,
        .data = reinterpret_cast<void *>(transParam),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityMgrFeature", "connect ability send request failure");
        delete transParam;
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityMgrFeature::DisconnectAbilityInvoke(const void *origin, IpcIo *req)
{
    uint64_t token = IpcIoPopUint64(req);
    SvcIdentity *sid = IpcIoPopSvc(req);
    return DisconnectAbility(sid, token);
}

int32 AbilityMgrFeature::DisconnectAbility(SvcIdentity *svc, uint64_t token)
{
    if (svc == nullptr) {
        return EC_INVALID;
    }
    auto transParam = new AbilityConnectTransParam(nullptr, *svc, token);
    Request request = {
        .msgId = AMS_DISCONNECT_ABILITY,
        .len = 0,
        .data = reinterpret_cast<void *>(transParam),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityMgrFeature", "disconnect ability send request failure");
        delete transParam;
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityMgrFeature::ConnectAbilityDoneInvoke(const void *origin, IpcIo *req)
{
    uint64_t token = IpcIoPopUint64(req);
    SvcIdentity *sid = IpcIoPopSvc(req);
    if (sid == nullptr) {
        return EC_INVALID;
    }
    auto transParam = new AbilityConnectTransParam(nullptr, *sid, token);
    Request request = {
        .msgId = AMS_CONNECT_ABILITY_DONE,
        .len = 0,
        .data = reinterpret_cast<void *>(transParam),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityMgrFeature", "connect ability done send request failure");
        delete transParam;
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityMgrFeature::DisconnectAbilityDoneInvoke(const void *origin, IpcIo *req)
{
    uint64_t *disconnectToken = new uint64_t;
    *disconnectToken = IpcIoPopUint64(req);
    Request request = {
        .msgId = AMS_DISCONNECT_ABILITY_DONE,
        .len = 0,
        .data = reinterpret_cast<void *>(disconnectToken),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityMgrFeature", "disconnect ability done send request failure");
        delete disconnectToken;
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityMgrFeature::StopAbilityInvoke(const void *origin, IpcIo *req)
{
    pid_t uid = GetCallingUid(origin);
    if (uid < 0) {
        PRINTE("AbilityMgrFeature", "invalid uid argument");
        return EC_INVALID;
    }
    Want want = { nullptr, nullptr, nullptr, 0 };
    if (!DeserializeWant(&want, req)) {
        return EC_FAILURE;
    }
    int retVal = StopAbilityInner(&want, uid);
    ClearWant(&want);
    return retVal;
}

int32 AbilityMgrFeature::StopAbility(const Want *want)
{
    return StopAbilityInner(want, -1);
}

int32 AbilityMgrFeature::StopAbilityInner(const Want *want, pid_t callingUid)
{
    if (want == nullptr || want->element == nullptr) {
        PRINTE("AbilityMgrFeature", "invalid argument");
        return EC_INVALID;
    }
    Want *data = new Want();
    if (memset_s(data, sizeof(Want), 0, sizeof(Want)) != EOK) {
        PRINTE("AbilityMgrFeature", "memory alloc error");
        delete data;
        return EC_NOMEMORY;
    }
    SetWantElement(data, *(want->element));
    SetWantData(data, want->data, want->dataLength);
    if (want->sid != nullptr) {
        SetWantSvcIdentity(data, *(want->sid));
    }
    Request request = {
        .msgId = AMS_TERMINATE_SERVICE,
        .len = 0,
        .data = reinterpret_cast<void *>(data),
        .msgValue = static_cast<uint32>(callingUid),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityMgrFeature", "send request failure");
        ClearWant(data);
        delete data;
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityMgrFeature::RestartApp(const char *bundleName)
{
    if (!AbilityMsHelper::IsLegalBundleName(bundleName)) {
        return EC_INVALID;
    }
    char *name = Utils::Strdup(bundleName);
    if (name == nullptr) {
        return EC_NOMEMORY;
    }
    Request request = {
        .msgId = AMS_RESTART_APP,
        .len = 0,
        .data = reinterpret_cast<void *>(name),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityMgrFeature", "send request failure");
        AdapterFree(name);
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityMgrFeature::AppDeathNotify(const IpcContext* context, void *ipcMsg, IpcIo *data, void *arg)
{
    PRINTE("AbilityMgrFeature", "start");
    FreeBuffer(nullptr, ipcMsg);
    AppInfo *appInfo = reinterpret_cast<AppInfo *>(arg);
    if (appInfo == nullptr) {
        return EC_INVALID;
    }
    if (!AbilityMsHelper::IsLegalBundleName(appInfo->bundleName)) {
        AdapterFree(appInfo->bundleName);
        delete appInfo;
        return EC_INVALID;
    }
    int32 ret = RestartApp(appInfo->bundleName);
    AdapterFree(appInfo->bundleName);
    delete appInfo;
    return ret;
}
} // namespace OHOS
