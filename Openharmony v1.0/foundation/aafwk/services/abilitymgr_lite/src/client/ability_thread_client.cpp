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

#include "client/ability_thread_client.h"

#include <inttypes.h>

#include "ability_kit_command.h"
#include "adapter.h"
#include "app_manager.h"
#include "app_record.h"
#include "client/bundlems_client.h"
#include "element_name_utils.h"
#include "liteipc_adapter.h"
#include "securec.h"
#include "serializer.h"
#include "util/abilityms_helper.h"
#include "utils.h"
#include "want_utils.h"

namespace OHOS {
const int MAX_MODULE_SIZE = 16;
AbilityThreadClient::AbilityThreadClient(uint64_t token, pid_t pid, const SvcIdentity &svcIdentity,
    IpcMsgHandler handler) : token_(token), pid_(pid), svcIdentity_(svcIdentity), deathHandler_(handler)
{
}

AbilityThreadClient::AbilityThreadClient(const AbilityThreadClient &client)
    : token_(client.token_), pid_(client.pid_), svcIdentity_(client.svcIdentity_), deathHandler_(client.deathHandler_)
{
}

AbilityMsStatus AbilityThreadClient::Initialize(const char *bundleName)
{
    if (bundleName == nullptr) {
        return AbilityMsStatus::AppTransanctStatus("bundleName is null");
    }
    AppInfo *appInfo = new AppInfo();
    appInfo->bundleName = Utils::Strdup(bundleName);
    if (appInfo->bundleName == nullptr) {
        delete appInfo;
        return AbilityMsStatus::AppTransanctStatus("memory alloc fail");
    }
    if (RegisteDeathCallback(nullptr, svcIdentity_, deathHandler_, appInfo, &cbid_) != LITEIPC_OK) {
        AdapterFree(appInfo->bundleName);
        delete appInfo;
        return AbilityMsStatus::AppTransanctStatus("register death callback ipc error");
    }
    PRINTD("AbilityThreadClient", "token(%{private}" PRIu64 ") bundleName(%{public}s) success",
        token_, appInfo->bundleName);
    return AbilityMsStatus::Ok();
}

uint64_t AbilityThreadClient::GetToken() const
{
    return token_;
}

pid_t AbilityThreadClient::GetPid() const
{
    return pid_;
}

const SvcIdentity& AbilityThreadClient::GetSvcIdentity() const
{
    return svcIdentity_;
}

AbilityMsStatus AbilityThreadClient::AbilityTransaction(const TransactionState &state,
    const Want &want, AbilityType abilityType) const
{
    PRINTD("AbilityThreadClient", "start");
    IpcIo req;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&req, data, IPC_IO_DATA_MAX, MAX_OBJECTS);
    IpcIoPushInt32(&req, state.state);
    IpcIoPushUint64(&req, state.token);
    IpcIoPushInt32(&req, abilityType);
    if (!SerializeWant(&req, &want)) {
        return AbilityMsStatus::AppTransanctStatus("SerializeWant failed");
    }
    int32_t ret = Transact(nullptr, svcIdentity_, SCHEDULER_ABILITY_LIFECYCLE, &req,
        nullptr, LITEIPC_FLAG_ONEWAY, nullptr);
    if (ret != LITEIPC_OK) {
        return AbilityMsStatus::AppTransanctStatus("lifecycle ipc error");
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus AbilityThreadClient::AppInitTransaction(const BundleInfo &bundleInfo)
{
    PRINTD("AbilityThreadClient", "start");
    if (bundleInfo.bundleName == nullptr || bundleInfo.codePath == nullptr ||
        bundleInfo.numOfModule > MAX_MODULE_SIZE) {
        return AbilityMsStatus::AppTransanctStatus("app init invalid argument");
    }
    IpcIo req;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&req, data, IPC_IO_DATA_MAX, 0);
    IpcIoPushString(&req, bundleInfo.bundleName);
    IpcIoPushString(&req, bundleInfo.codePath);
    IpcIoPushString(&req, bundleInfo.dataPath);
    IpcIoPushBool(&req, bundleInfo.isNativeApp);
    // transact moduleName
    IpcIoPushInt32(&req, bundleInfo.numOfModule);
    for (int i = 0; i < bundleInfo.numOfModule; i++) {
        if (bundleInfo.moduleInfos[i].moduleName != nullptr) {
            IpcIoPushString(&req, bundleInfo.moduleInfos[i].moduleName);
        }
    }
    uintptr_t ptr;
    if (Transact(nullptr, svcIdentity_, SCHEDULER_APP_INIT, &req,
        nullptr, LITEIPC_FLAG_DEFAULT, &ptr) != LITEIPC_OK) {
        return  AbilityMsStatus::AppTransanctStatus("app init ipc error");
    }
    FreeBuffer(nullptr, reinterpret_cast<void *>(ptr));
    return AbilityMsStatus::Ok();
}

AbilityMsStatus AbilityThreadClient::AppExitTransaction()
{
    PRINTD("AbilityThreadClient", "start");
    if (Transact(nullptr, svcIdentity_, SCHEDULER_APP_EXIT, nullptr,
        nullptr, LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        return AbilityMsStatus::AppTransanctStatus("app exit ipc error");
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus AbilityThreadClient::ConnectAbility(const Want &want, uint64_t token) const
{
    PRINTD("AbilityThreadClient", "connect");
    IpcIo req;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&req, data, IPC_IO_DATA_MAX, MAX_OBJECTS);
    IpcIoPushUint64(&req, token);
    if (!SerializeWant(&req, &want)) {
        return AbilityMsStatus::TaskStatus("connectAbility", "SerializeWant failed");
    }
    if (Transact(nullptr, svcIdentity_, SCHEDULER_ABILITY_CONNECT, &req,
        nullptr, LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        return AbilityMsStatus::TaskStatus("connectAbility", "connectAbility exit ipc error");
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus AbilityThreadClient::DisconnectAbility(const Want &want, uint64_t token) const
{
    PRINTD("AbilityThreadClient", "disconnect");
    IpcIo req;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&req, data, IPC_IO_DATA_MAX, MAX_OBJECTS);
    IpcIoPushUint64(&req, token);
    if (!SerializeWant(&req, &want)) {
        return AbilityMsStatus::TaskStatus("disconnectAbility", "SerializeWant failed");
    }
    if (Transact(nullptr, svcIdentity_, SCHEDULER_ABILITY_DISCONNECT, &req, nullptr,
        LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        return AbilityMsStatus::TaskStatus("disconnectAbility", "disconnectAbility exit ipc error");
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus AbilityThreadClient::ConnectAbilityDone(const Want &want, const SvcIdentity &serviceSid,
    const SvcIdentity &connectSid) const
{
    PRINTD("AbilityThreadClient", "connectDone");
    IpcIo req;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&req, data, IPC_IO_DATA_MAX, 1);
    IpcIoPushSvc(&req, &serviceSid);
    if (!SerializeElement(&req, want.element)) {
        return AbilityMsStatus::TaskStatus("connectAbilityDone", "SerializeElement failed");
    }

    if (Transact(nullptr, connectSid, SCHEDULER_ABILITY_CONNECT, &req, nullptr,
        LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        return AbilityMsStatus::TaskStatus("connectAbilityDone", "connectAbilityDone ipc error");
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus AbilityThreadClient::DisconnectAbilityDone(const Want &want, const SvcIdentity &connectSid) const
{
    PRINTD("AbilityThreadClient", "disconnectDone");
    IpcIo req;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&req, data, IPC_IO_DATA_MAX, 0);
    if (!SerializeElement(&req, want.element)) {
        return AbilityMsStatus::TaskStatus("DisconnectAbilityDone", "SerializeElement failed");
    }

    if (Transact(nullptr, connectSid, SCHEDULER_ABILITY_DISCONNECT, &req,
        nullptr, LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        return AbilityMsStatus::TaskStatus("disconnectAbilityDone", "disconnectAbilityDone ipc error");
    }
    return AbilityMsStatus::Ok();
}

AbilityMsStatus AbilityThreadClient::DumpAbilityTransaction(const Want &want, uint64_t token)
{
    PRINTD("AbilityThreadClient", "start");
    IpcIo req;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&req, data, IPC_IO_DATA_MAX, MAX_OBJECTS);
    if (!SerializeWant(&req, &want)) {
        return AbilityMsStatus::TaskStatus("dumpAbility", "SerializeWant failed");
    }
    IpcIoPushUint64(&req, token);
    if (Transact(nullptr, svcIdentity_, SCHEDULER_DUMP_ABILITY, &req,
        nullptr, LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        return AbilityMsStatus::AppTransanctStatus("dump ability ipc error");
    }
    return AbilityMsStatus::Ok();
}
}
