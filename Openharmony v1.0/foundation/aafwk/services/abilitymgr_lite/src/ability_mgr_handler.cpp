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

#include "ability_mgr_handler.h"

#include "ability_kit_command.h"
#include "ability_message_id.h"
#include "adapter.h"
#include "app_manager.h"
#include "bundle_info.h"
#include "bundle_manager.h"
#ifdef ABILITY_WINDOW_SUPPORT
#include "client/wms_client.h"
#endif
#include "element_name_utils.h"
#include "iproxy_client.h"
#include "util/abilityms_helper.h"

namespace OHOS {
void AbilityMgrHandler::Init()
{
    AbilityMsStatus status = bundleMsClient_.Initialize();
    CHECK_RESULT_LOG(status);
}

void AbilityMgrHandler::ServiceMsgProcess(const Request &request)
{
    switch (request.msgId) {
        case AMS_SERVICE_INITED: {
            OnServiceInited();
            break;
        }
        case AMS_START_ABILITY: {
            Want *want = reinterpret_cast<Want *>(request.data);
            pid_t uid = request.msgValue;
            int ret = StartAbility(want, uid);
            StartAbilityCallback(want, ret);
            ClearWant(want);
            delete want;
            break;
        }
        case AMS_TERMINATE_ABILITY: {
            TerminateAbility(reinterpret_cast<uint64_t *>(request.data));
            break;
        }
        case AMS_ATTACH_BUNDLE: {
            AttachBundle(reinterpret_cast<AbilityThreadClient *>(request.data));
            break;
        }
        case AMS_TRANSACTION_DONE: {
            AbilityTransaction(reinterpret_cast<TransactionState *>(request.data));
            break;
        }
        case AMS_CONNECT_ABILITY: {
            auto transParam = reinterpret_cast<AbilityConnectTransParam *>(request.data);
            int ret = ConnectAbility(transParam);
            ConnectAbilityCallback(transParam, ret);
            delete transParam;
            break;
        }
        case AMS_CONNECT_ABILITY_DONE: {
            auto transParam = reinterpret_cast<AbilityConnectTransParam *>(request.data);
            ConnectAbilityDone(transParam);
            delete transParam;
            break;
        }
        case AMS_DISCONNECT_ABILITY: {
            auto transParam = reinterpret_cast<AbilityConnectTransParam *>(request.data);
            DisconnectAbility(transParam);
            delete transParam;
            break;
        }
        case AMS_DISCONNECT_ABILITY_DONE: {
            DisconnectAbilityDone(reinterpret_cast<uint64_t *>(request.data));
            break;
        }
        case AMS_TERMINATE_SERVICE: {
            Want *want = reinterpret_cast<Want *>(request.data);
            pid_t uid = request.msgValue;
            TerminateService(want, uid);
            ClearWant(want);
            delete want;
            break;
        }
        case AMS_TERMINATE_APP: {
            char *bundleName = reinterpret_cast<char *>(request.data);
            TerminateApp(bundleName);
            AdapterFree(bundleName);
            break;
        }
        case AMS_DUMP_ABILITY: {
            DumpAbility(reinterpret_cast<AbilityDumpClient *>(request.data));
            break;
        }
        case AMS_RESTART_APP: {
            char *bundleName = reinterpret_cast<char *>(request.data);
            RestartApp(bundleName);
            AdapterFree(bundleName);
            break;
        }
        default: {
            PRINTI("AbilityMgrHandler", "unknown msgId");
            break;
        }
    }
}

void AbilityMgrHandler::OnServiceInited()
{
    PRINTD("AbilityMgrHandler", "start");
    StartKeepAliveApps();
}

void AbilityMgrHandler::StartKeepAliveApps()
{
    int32_t len = 0;
    BundleInfo *bundleInfos = nullptr;
    AbilityMsStatus status = bundleMsClient_.QueryKeepAliveBundleInfos(&bundleInfos, &len);
    CHECK_RESULT_LOG(status);
    CHECK_NULLPTR_RETURN(bundleInfos, "AbilityMgrHandler", "bundleInfos is nullptr");
#ifdef ABILITY_WINDOW_SUPPORT
    if (len > 0) {
        // Start keep-alive apps until wms is ready.
        WMSClient::WaitUntilWmsReady();
    }
#endif
    for (int32_t i = 0; i < len; ++i) {
        if (AbilityMsHelper::IsLauncherAbility(bundleInfos[i].bundleName)) {
#ifdef ABILITY_WINDOW_SUPPORT
            StartLauncher();
#endif
        } else {
            StartKeepAliveApp(bundleInfos[i]);
        }
    }
    for (int32_t i = 0; i < len; ++i) {
        ClearBundleInfo(&(bundleInfos[i]));
    }
    AdapterFree(bundleInfos);
}

void AbilityMgrHandler::StartKeepAliveApp(const BundleInfo &bundleInfo)
{
    PRINTD("AbilityMgrHandler", "start");
    Want want = {};
    AbilityMsStatus status = AbilityMsHelper::SetKeepAliveWant(bundleInfo, want);
    CHECK_RESULT_LOG(status);
    StartAbility(&want, AbilityMsHelper::SYSTEM_UID);
    ClearWant(&want);
}

void AbilityMgrHandler::StartLauncher()
{
    PRINTD("AbilityMgrHandler", "start");
    // Create Launcher Want,
    Want want = {};
    AbilityMsStatus status = AbilityMsHelper::SetLauncherWant(want);
    CHECK_RESULT_LOG(status);

    StartAbility(&want, AbilityMsHelper::SYSTEM_UID);
    ClearWant(&want);
}

int AbilityMgrHandler::StartAbility(const Want *want, pid_t callingUid)
{
    PRINTD("AbilityMgrHandler", "start");
    CHECK_NULLPTR_RETURN_CODE(want, "AbilityMgrHandler", "invalid argument", EC_FAILURE);
    CHECK_NULLPTR_RETURN_CODE(want->element, "AbilityMgrHandler", "invalid argument", EC_FAILURE);

    // Qurey BundleInfo note: bundleInfo not need clear
    BundleInfo bundleInfo = {};
    AbilityMsStatus status = bundleMsClient_.QueryBundleInfo(want->element->bundleName, &bundleInfo);
    CHECK_RESULT_LOG_CODE(status, EC_INVALID);

    // Query AbilityInfo
    AbilityInfo target = {};
    status = bundleMsClient_.QueryAbilityInfo(want, &target);
    CHECK_RESULT_LOG_CODE(status, EC_INVALID);

    status = abilityWorker_.StartAbility(*want, target, bundleInfo, callingUid);
    ClearAbilityInfo(&target);
    CHECK_RESULT_LOG_CODE(status, EC_COMMU);

    return EC_SUCCESS;
}

void AbilityMgrHandler::AttachBundle(AbilityThreadClient *client)
{
    PRINTD("AbilityMgrHandler", "start");
    CHECK_NULLPTR_RETURN(client, "AbilityMgrHandler", "invalid augument");
    AbilityMsStatus status = abilityWorker_.AttachBundle(*client);
    delete client;
    CHECK_RESULT_LOG(status);
}

void AbilityMgrHandler::TerminateAbility(const uint64_t *token)
{
    PRINTD("AbilityMgrHandler", "start");
    CHECK_NULLPTR_RETURN(token, "AbilityMgrHandler", "invalid argument");
    AbilityMsStatus status = abilityWorker_.TerminateAbility(*token);
    delete token;
    CHECK_RESULT_LOG(status);
}

void AbilityMgrHandler::AbilityTransaction(TransactionState *state)
{
    PRINTD("AbilityMgrHandler", "start");
    CHECK_NULLPTR_RETURN(state, "AbilityMgrHandler", "invalid argument");
    AbilityMsStatus status = abilityWorker_.AbilityTransaction(*state);
    delete state;
    if (status.IsNoActiveAbility()) {
        status.LogStatus();
        StartLauncher();
    } else {
        CHECK_RESULT_LOG(status);
    }
}

void AbilityMgrHandler::TerminateApp(const char *bundleName)
{
    PRINTD("AbilityMgrHandler", "start");
    CHECK_NULLPTR_RETURN(bundleName, "AbilityMgrHandler", "invalid argument");
    AbilityMsStatus status = abilityWorker_.TerminateApp(bundleName);
    CHECK_RESULT_LOG(status);
}

void AbilityMgrHandler::RestartApp(const char *bundleName)
{
    PRINTD("AbilityMgrHandler", "start %{public}s", bundleName);
    CHECK_NULLPTR_RETURN(bundleName, "AbilityMgrHandler", "invalid argument");
    // Qurey BundleInfo
    BundleInfo bundleInfo = {};
    AbilityMsStatus status = bundleMsClient_.QueryBundleInfo(bundleName, &bundleInfo);
    if (!status.IsOk()) {
        status.LogStatus();
        return;
    }
    status = abilityWorker_.RestartApp(bundleInfo);
    if (status.IsNoActiveAbility()) {
        status.LogStatus();
        StartLauncher();
    }
    if (!AbilityMsHelper::IsLauncherAbility(bundleInfo.bundleName) && bundleInfo.isSystemApp
        && bundleInfo.isKeepAlive) {
        StartKeepAliveApp(bundleInfo);
    }
    CHECK_RESULT_LOG(status);
}

int AbilityMgrHandler::ConnectAbility(AbilityConnectTransParam *transParam)
{
    PRINTD("AbilityMgrHandler", "connect");
    CHECK_NULLPTR_RETURN_CODE(transParam, "AbilityMgrHandler", "invalid argument", EC_FAILURE);
    const Want *want = transParam->GetWant();
    CHECK_NULLPTR_RETURN_CODE(want, "AbilityMgrHandler", "invalid argument", EC_FAILURE);
    CHECK_NULLPTR_RETURN_CODE(want->element, "AbilityMgrHandler", "invalid argument", EC_FAILURE);
    // Qurey BundleInfo note: bundleInfo not need clear
    BundleInfo bundleInfo = {};
    AbilityMsStatus status = bundleMsClient_.QueryBundleInfo(want->element->bundleName, &bundleInfo);
    CHECK_RESULT_LOG_CODE(status, EC_INVALID);

    // Query AbilityInfo
    AbilityInfo target = {};
    status = bundleMsClient_.QueryAbilityInfo(want, &target);
    CHECK_RESULT_LOG_CODE(status, EC_INVALID);

    status = abilityWorker_.ConnectAbility(*transParam, target, bundleInfo);
    ClearAbilityInfo(&target);
    CHECK_RESULT_LOG_CODE(status, EC_COMMU);
    return EC_SUCCESS;
}

void AbilityMgrHandler::DisconnectAbility(AbilityConnectTransParam *transParam)
{
    PRINTD("AbilityMgrHandler", "disconnect");
    CHECK_NULLPTR_RETURN(transParam, "AbilityMgrHandler", "invalid argument");
    const SvcIdentity sid = transParam->GetSvcIdentity();
    uint64_t token = transParam->GetToken();
    AbilityMsStatus status = abilityWorker_.DisconnectAbility(sid, token);
    CHECK_RESULT_LOG(status);
}

void AbilityMgrHandler::ConnectAbilityDone(AbilityConnectTransParam *transParam)
{
    PRINTD("AbilityMgrHandler", "connectDone");
    CHECK_NULLPTR_RETURN(transParam, "AbilityMgrHandler", "invalid argument");
    const SvcIdentity sid = transParam->GetSvcIdentity();
    uint64_t token = transParam->GetToken();
    AbilityMsStatus status = abilityWorker_.ConnectAbilityDone(sid, token);
    CHECK_RESULT_LOG(status);
}

void AbilityMgrHandler::DisconnectAbilityDone(const uint64_t *token)
{
    PRINTD("AbilityMgrHandler", "disconnectDone");
    CHECK_NULLPTR_RETURN(token, "AbilityMgrHandler", "invalid argument: token");
    AbilityMsStatus status = abilityWorker_.DisconnectAbilityDone(*token);
    delete token;
    CHECK_RESULT_LOG(status);
}

void AbilityMgrHandler::TerminateService(Want *want, pid_t callingUid)
{
    PRINTD("AbilityMgrHandler", "terminateService");
    CHECK_NULLPTR_RETURN(want, "AbilityMgrHandler", "invalid argument");
    CHECK_NULLPTR_RETURN(want->element, "AbilityMgrHandler", "invalid argument");

    // Qurey BundleInfo note: bundleInfo not need clear
    BundleInfo bundleInfo = {};
    AbilityMsStatus status = bundleMsClient_.QueryBundleInfo(want->element->bundleName, &bundleInfo);
    CHECK_RESULT_LOG(status);

    // Query AbilityInfo
    AbilityInfo target = {};
    status = bundleMsClient_.QueryAbilityInfo(want, &target);
    CHECK_RESULT_LOG(status);
    status = abilityWorker_.TerminateService(target, bundleInfo, callingUid);
    ClearAbilityInfo(&target);
    CHECK_RESULT_LOG(status);
}

void AbilityMgrHandler::StartAbilityCallback(const Want *want, int code)
{
    if ((want == nullptr) || (want->sid == nullptr) || (code == EC_SUCCESS)) {
        return;
    }
    PRINTI("AbilityMgrHandler", "start ability failed callback");
    IpcIo io;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&io, data, IPC_IO_DATA_MAX, 0);
    if (!SerializeElement(&io, want->element)) {
        return;
    }
    IpcIoPushInt32(&io, code);
    if (Transact(nullptr, *(want->sid), SCHEDULER_APP_INIT, &io, nullptr, LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        PRINTE("AbilityMgrHandler", "start ability callback failed, ipc error");
    }
}

void AbilityMgrHandler::DumpAbility(const AbilityDumpClient *client)
{
    PRINTD("AbilityMgrHandler", "start");
    CHECK_NULLPTR_RETURN(client, "AbilityMgrHandler", "invalid argument");
    AbilityMsStatus status = abilityWorker_.DumpAbility(*client);
    delete client;
    CHECK_RESULT_LOG(status);
}

void AbilityMgrHandler::ConnectAbilityCallback(AbilityConnectTransParam *transParam, int code)
{
    if (transParam == nullptr || code == EC_SUCCESS) {
        return;
    }
    PRINTI("AbilityMgrHandler", "connect ability failed");
    if (Transact(nullptr, transParam->GetSvcIdentity(), SCHEDULER_ABILITY_CONNECT_FAIL, nullptr, nullptr,
        LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        PRINTE("AbilityMgrHandler", "connect ability callback failed, ipc error");
    }
}
}  // namespace OHOS
