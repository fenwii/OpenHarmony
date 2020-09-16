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

#include "bundle_daemon_client.h"

#include "bundle_daemon_interface.h"
#include "bundle_log.h"
#include "hos_errno.h"
#include "iproxy_client.h"
#include "samgr_lite.h"

namespace OHOS {
namespace {
constexpr unsigned SLEEP_TIME = 200000;
}

int32_t BundleDaemonClient::BundleDaemonCallback(const IpcContext* context, void *ipcMsg, IpcIo *io, void *arg)
{
    BundleDaemonClient *client = reinterpret_cast<BundleDaemonClient *>(arg);
    if (client == nullptr) {
        if (ipcMsg != nullptr) {
            FreeBuffer(nullptr, ipcMsg);
        }
        return EC_INVALID;
    }

    client->result_ = IpcIoPopInt32(io);
    if (ipcMsg != nullptr) {
        FreeBuffer(nullptr, ipcMsg);
    }
    int value;
    sem_getvalue(&client->sem_, &value);
    if (value <= 0) {
        sem_post(&client->sem_);
    }
    return EC_SUCCESS;
}

int32_t BundleDaemonClient::DeathCallback(const IpcContext* context, void* ipcMsg, IpcIo* data, void* arg)
{
    if (ipcMsg != nullptr) {
        FreeBuffer(nullptr, ipcMsg);
    }
    pthread_t pid;
    if (pthread_create(&pid, nullptr, RegisterDeathCallback, arg) == 0) {
        return EC_SUCCESS;
    }

    BundleDaemonClient *client = reinterpret_cast<BundleDaemonClient *>(arg);
    if (client != nullptr) {
        client->result_ = EC_CANCELED;
        int value;
        sem_getvalue(&client->sem_, &value);
        if (value <= 0) {
            sem_post(&client->sem_);
        }
    }
    return EC_INVALID;
}

BundleDaemonClient::~BundleDaemonClient()
{
    if (initialized_) {
        UnRegisteIpcCallback(svcIdentity_);
        UnRegisteDeathCallback(bdsSvcIdentity_, cbid_);
        bdsClient_->Release(reinterpret_cast<IUnknown *>(bdsClient_));
        bdsClient_ = nullptr;
        sem_destroy(&sem_);
    }
}

bool BundleDaemonClient::Initialize()
{
    if (initialized_) {
        PRINTI("BundleDaemonClient", "already initialized");
        return true;
    }
    if (sem_init(&sem_, 0, 0) != 0) {
        PRINTE("BundleDaemonClient", "sem_init fail");
        return false;
    }

    while (bdsClient_ == nullptr) {
        IUnknown *iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(BDS_SERVICE);
        if (iUnknown == nullptr) {
            usleep(SLEEP_TIME);
            continue;
        }

        (void)iUnknown->QueryInterface(iUnknown, CLIENT_PROXY_VER, (void **)&bdsClient_);
    }

    // register bundle_daemon callback
    int32_t ret = RegisteIpcCallback(
        BundleDaemonClient::BundleDaemonCallback, 0, IPC_WAIT_FOREVER, &svcIdentity_, this);
    if (ret != EC_SUCCESS || RegisterCallback() != LITEIPC_OK) {
        PRINTE("BundleDaemonClient", "register bundle_daemon callback fail");
        sem_destroy(&sem_);
        return false;
    }

    // register bundle_daemon death callback
    bdsSvcIdentity_ = SAMGR_GetRemoteIdentity(BDS_SERVICE, nullptr);
    if (RegisteDeathCallback(nullptr, bdsSvcIdentity_, &BundleDaemonClient::DeathCallback, this, &cbid_) !=
        LITEIPC_OK) {
        PRINTW("BundleDaemonClient", "register bundle_daemon death callback fail");
        // Keep running if register death callback fail
    }

    initialized_ = true;
    return true;
}

void *BundleDaemonClient::RegisterDeathCallback(void *arg)
{
    BundleDaemonClient *client = reinterpret_cast<BundleDaemonClient *>(arg);
    if (client == nullptr) {
        return nullptr;
    }
    client->result_ = EC_CANCELED;
    int value;
    sem_getvalue(&client->sem_, &value);
    if (value <= 0) {
        sem_post(&client->sem_);
    }
    // Register invoke callback and death callback again
    Lock<Mutex> lock(client->mutex_);
    client->RegisterCallback();

    UnRegisteDeathCallback(client->bdsSvcIdentity_, client->cbid_);
    client->cbid_ = INVALID_INDEX;
    client->bdsSvcIdentity_.handle = INVALID_INDEX;
    client->bdsSvcIdentity_.token = INVALID_INDEX;

    client->bdsSvcIdentity_ = SAMGR_GetRemoteIdentity(BDS_SERVICE, nullptr);
    if (RegisteDeathCallback(nullptr, client->bdsSvcIdentity_, &BundleDaemonClient::DeathCallback,
        client, &client->cbid_) != LITEIPC_OK) {
        PRINTW("BundleDeamonClient", "register death callback fail");
        // Keep running if register death callback fail
    }

    return nullptr;
}

int32 BundleDaemonClient::WaitResultSync(int32 result)
{
    if (result == EC_SUCCESS) {
        sem_wait(&sem_);
        result = result_;
        result_ = EC_FAILURE;
    }
    return result;
}

int32 BundleDaemonClient::RegisterCallback()
{
    IpcIo request;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&request, data, IPC_IO_DATA_MAX, 1);
    IpcIoPushSvc(&request, &svcIdentity_);

    while (bdsClient_->Invoke(bdsClient_, REGISTER_CALLBACK, &request, nullptr, nullptr) != EC_SUCCESS) {
        PRINTI("BundleDaemonClient", "register bundle_daemon callback fail");
        usleep(SLEEP_TIME);
    }
    return WaitResultSync(EC_SUCCESS);
}

int32 BundleDaemonClient::ExtractHap(const char *hapFile, const char *codePath)
{
    if (!initialized_) {
        return EC_NOINIT;
    }
    if (hapFile == nullptr || codePath == nullptr) {
        PRINTE("BundleDaemonClient", "invalid params: hapFile or codePath is nullptr");
        return EC_INVALID;
    }
    IpcIo request;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&request, data, IPC_IO_DATA_MAX, 0);
    IpcIoPushString(&request, hapFile);
    IpcIoPushString(&request, codePath);

    Lock<Mutex> lock(mutex_);
    return WaitResultSync(bdsClient_->Invoke(bdsClient_, EXTRACT_HAP, &request, nullptr, nullptr));
}

int32 BundleDaemonClient::RenameFile(const char *oldFile, const char *newFile)
{
    if (!initialized_) {
        return EC_NOINIT;
    }
    if (oldFile == nullptr || newFile == nullptr) {
        PRINTE("BundleDaemonClient", "invalid params: oldDir or newDir is nullptr");
        return EC_INVALID;
    }
    IpcIo request;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&request, data, IPC_IO_DATA_MAX, 0);
    IpcIoPushString(&request, oldFile);
    IpcIoPushString(&request, newFile);

    Lock<Mutex> lock(mutex_);
    return WaitResultSync(bdsClient_->Invoke(bdsClient_, RENAME_DIR, &request, nullptr, nullptr));
}

int32 BundleDaemonClient::CreatePermissionDir()
{
    if (!initialized_) {
        return EC_NOINIT;
    }
    Lock<Mutex> lock(mutex_);
    return WaitResultSync(bdsClient_->Invoke(bdsClient_, CREATE_PERMISSION_DIR, nullptr, nullptr, nullptr));
}

int32 BundleDaemonClient::CreateDataDirectory(const char *dataPath, int32_t uid, int32_t gid, bool isChown)
{
    if (!initialized_) {
        return EC_NOINIT;
    }
    if (dataPath == nullptr) {
        PRINTE("BundleDaemonClient", "invalid params: bundleName is nullptr");
        return EC_INVALID;
    }
    IpcIo request;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&request, data, IPC_IO_DATA_MAX, 0);
    IpcIoPushString(&request, dataPath);
    IpcIoPushInt32(&request, uid);
    IpcIoPushInt32(&request, gid);
    IpcIoPushBool(&request, isChown);

    Lock<Mutex> lock(mutex_);
    return WaitResultSync(bdsClient_->Invoke(bdsClient_, CREATE_DATA_DIRECTORY, &request, nullptr, nullptr));
}

int32 BundleDaemonClient::StoreContentToFile(const char *file, const void *buffer, uint32_t size)
{
    if (!initialized_) {
        return EC_NOINIT;
    }
    if (file == nullptr || buffer == nullptr || size == 0) {
        PRINTE("BundleDaemonClient", "invalid params");
        return EC_INVALID;
    }
    IpcIo request;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&request, data, IPC_IO_DATA_MAX, 1);
    IpcIoPushString(&request, file);
    BuffPtr dataBuff = {
        .buffSz = size, // include \0
        .buff = const_cast<void *>(buffer),
    };
    IpcIoPushDataBuff(&request, &dataBuff);

    Lock<Mutex> lock(mutex_);
    return WaitResultSync(bdsClient_->Invoke(bdsClient_, STORE_CONTENT_TO_FILE, &request, nullptr, nullptr));
}

int32 BundleDaemonClient::RemoveFile(const char *file)
{
    if (!initialized_) {
        return EC_NOINIT;
    }
    if (file == nullptr) {
        PRINTE("BundleDaemonClient", "invalid params");
        return EC_INVALID;
    }
    IpcIo request;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&request, data, IPC_IO_DATA_MAX, 0);
    IpcIoPushString(&request, file);

    Lock<Mutex> lock(mutex_);
    return WaitResultSync(bdsClient_->Invoke(bdsClient_, REMOVE_FILE, &request, nullptr, nullptr));
}

int32 BundleDaemonClient::RemoveInstallDirectory(const char *codePath, const char *dataPath)
{
    if (!initialized_) {
        return EC_NOINIT;
    }
    if (codePath == nullptr || dataPath == nullptr) {
        PRINTE("BundleDaemonClient", "invalid params: bundleName is nullptr");
        return EC_INVALID;
    }
    IpcIo request;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&request, data, IPC_IO_DATA_MAX, 0);
    IpcIoPushString(&request, codePath);
    IpcIoPushString(&request, dataPath);

    Lock<Mutex> lock(mutex_);
    return WaitResultSync(bdsClient_->Invoke(bdsClient_, REMOVE_INSTALL_DIRECTORY, &request, nullptr, nullptr));
}
} // OHOS
