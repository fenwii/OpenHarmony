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

#include "ability_inner_feature.h"

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
AbilityInnerFeatureImpl g_amsInnerImpl = {
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = AbilityInnerFeature::Invoke,
    .StartKeepAliveApps = AbilityInnerFeature::StartKeepAliveApps,
    .TerminateApp = AbilityInnerFeature::TerminateApp,
    IPROXY_END
};

InvokeFunc AbilityInnerFeature::invokeFuncList[COMMAND_END - INNER_BEGIN] {
    AbilityInnerFeature::TerminateAppInvoke,
    AbilityInnerFeature::DumpAbilityInvoke,
};

static void Init()
{
    SamgrLite *samgrLite = SAMGR_GetInstance();
    CHECK_NULLPTR_RETURN(samgrLite, "AbilityInnerFeature", "get samgr error");
    BOOL result = samgrLite->RegisterFeature(AMS_SERVICE, AbilityInnerFeature::GetInstance());
    if (result == FALSE) {
        PRINTE("AbilityInnerFeature", "ams register feature failure");
        return;
    }
    g_amsInnerImpl.ams = AbilityInnerFeature::GetInstance();
    auto publicApi = GET_IUNKNOWN(g_amsInnerImpl);
    CHECK_NULLPTR_RETURN(publicApi, "AbilityMgrFeatureLite", "publicApi is nullptr");
    BOOL apiResult = samgrLite->RegisterFeatureApi(AMS_SERVICE, AMS_INNER_FEATURE, publicApi);
    PRINTI("AbilityInnerFeature", "ams inner feature init %{public}s", apiResult ? "success" : "failure");
}
SYSEX_FEATURE_INIT(Init);

AbilityInnerFeature::AbilityInnerFeature() : Feature(), identity_()
{
    this->Feature::GetName = AbilityInnerFeature::GetFeatureName;
    this->Feature::OnInitialize = AbilityInnerFeature::OnFeatureInitialize;
    this->Feature::OnStop = AbilityInnerFeature::OnFeatureStop;
    this->Feature::OnMessage = AbilityInnerFeature::OnFeatureMessage;
}

int32 AbilityInnerFeature::Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    PRINTI("AbilityInnerFeature", "ams invoke called");
    if (req == nullptr) {
        return EC_INVALID;
    }
    if (funcId >= INNER_BEGIN && funcId < COMMAND_END) {
        return invokeFuncList[funcId - INNER_BEGIN](origin, req);
    }
    return COMMAND_ERROR;
}

const char *AbilityInnerFeature::GetFeatureName(Feature *feature)
{
    (void) feature;
    return AMS_INNER_FEATURE;
}

void AbilityInnerFeature::OnFeatureInitialize(Feature *feature, Service *parent, Identity identity)
{
    CHECK_NULLPTR_RETURN(feature, "AbilityInnerFeature", "initialize fail");
    (static_cast<AbilityInnerFeature *>(feature))->identity_ = identity;
}

void AbilityInnerFeature::OnFeatureStop(Feature *feature, Identity identity)
{
    (void) feature;
    (void) identity;
}

BOOL AbilityInnerFeature::OnFeatureMessage(Feature *feature, Request *request)
{
    if (feature == nullptr || request == nullptr) {
        return FALSE;
    }

    AbilityMgrHandler::GetInstance().ServiceMsgProcess(*request);
    return TRUE;
}

int32 AbilityInnerFeature::TerminateAppInvoke(const void *origin, IpcIo *req)
{
    size_t len = 0;
    char *bundleName = reinterpret_cast<char *>(IpcIoPopString(req, &len));
    if (bundleName == nullptr || len == 0) {
        PRINTE("AbilityInnerFeature", "bundleName is null");
        return EC_INVALID;
    }
    return TerminateApp(bundleName);
}

int32 AbilityInnerFeature::StartKeepAliveApps()
{
    Request request = {
        .msgId = AMS_SERVICE_INITED,
    };
    return SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
}

int32 AbilityInnerFeature::TerminateApp(const char *bundleName)
{
    if (!AbilityMsHelper::IsLegalBundleName(bundleName)) {
        return EC_INVALID;
    }

    char *name = Utils::Strdup(bundleName);
    if (name == nullptr) {
        return EC_NOMEMORY;
    }
    Request request = {
        .msgId = AMS_TERMINATE_APP,
        .len = 0,
        .data = reinterpret_cast<void *>(name),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityInnerFeature", "send request failure");
        AdapterFree(name);
        return EC_COMMU;
    }
    return EC_SUCCESS;
}

int32 AbilityInnerFeature::DumpAbilityInvoke(const void *origin, IpcIo *req)
{
    Want want = { nullptr, nullptr, nullptr, 0 };
    if (!DeserializeWant(&want, req) || (want.sid == nullptr)) {
        ClearWant(&want);
        return EC_FAILURE;
    }

    auto client = new AbilityDumpClient(want);
    ClearWant(&want);
    Request request = {
        .msgId = AMS_DUMP_ABILITY,
        .len = 0,
        .data = reinterpret_cast<void *>(client),
    };
    int32 propRet = SAMGR_SendRequest(&(GetInstance()->identity_), &request, nullptr);
    if (propRet != EC_SUCCESS) {
        PRINTE("AbilityInnerFeature", "send request failure");
        delete client;
        return EC_COMMU;
    }
    return EC_SUCCESS;
}
} // namespace OHOS
