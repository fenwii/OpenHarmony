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

#include "bundle_daemon.h"

#include "bundle_daemon_log.h"
#include "hos_init.h"
#include "hos_errno.h"
#include "liteipc_adapter.h"
#include "samgr_lite.h"
#include "serializer.h"

namespace OHOS {
namespace {
constexpr int STACK_SIZE = 0x800;
constexpr int QUEUE_SIZE = 20;
constexpr pid_t BMS_UID = 7;
}
constexpr InvokeFunc BundleDaemon::invokeFuncs[];

static BundleDaemonFeature g_defaultApi = {
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = BundleDaemon::Invoke,
    IPROXY_END,
};

static void Init()
{
    SamgrLite *samgrLite = SAMGR_GetInstance();
    if (samgrLite == nullptr) {
        PRINTE("BundleDaemon", "get samgr is nullptr");
        return;
    }
    BOOL result = samgrLite->RegisterService(&BundleDaemon::GetInstance());
    if (!result) {
        PRINTE("BundleDaemon", "register bundle_daemon service fail");
        return;
    }
    result = samgrLite->RegisterDefaultFeatureApi(BDS_SERVICE, GET_IUNKNOWN(g_defaultApi));
    PRINTE("BundleDaemon", "register default feature api %{public}s", result ? "success" : "fail");
}
SYSEX_SERVICE_INIT(Init);

BundleDaemon::BundleDaemon()
{
    this->Service::GetName = BundleDaemon::GetServiceName;
    this->Service::Initialize = BundleDaemon::ServiceInitialize;
    this->Service::MessageHandle = BundleDaemon::ServiceMessageHandle;
    this->Service::GetTaskConfig = BundleDaemon::GetServiceTaskConfig;
}


BundleDaemon::~BundleDaemon()
{
    delete bundleMsClient_;
}

const char *BundleDaemon::GetServiceName(Service *service)
{
    (void)service;
    return BDS_SERVICE;
}

BOOL BundleDaemon::ServiceInitialize(Service *service, Identity identity)
{
    if (service == nullptr) {
        return FALSE;
    }
    BundleDaemon *bundleDaemon = static_cast<BundleDaemon *>(service);
    bundleDaemon->identity_ = identity;
    return TRUE;
}

TaskConfig BundleDaemon::GetServiceTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, STACK_SIZE, QUEUE_SIZE, SINGLE_TASK};
    return config;
}

BOOL BundleDaemon::ServiceMessageHandle(Service *service, Request *request)
{
    if (request == nullptr) {
        return FALSE;
    }
    return TRUE;
}

int32 BundleDaemon::Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    PRINTI("BundleDaemon", "bundle_daemon invoke start %{public}d", funcId);
    if (origin == nullptr || req == nullptr) {
        PRINTE("BundleDaemon", "invalid param");
        return EC_INVALID;
    }
    // check permission
    pid_t uid = GetCallingUid(origin);
    if (uid != BMS_UID) {
        PRINTE("BundleDaemon", "permission denied");
        return EC_PERMISSION;
    }
    if (funcId == REGISTER_CALLBACK) {
        return RegisterCallbackInvoke(req);
    }
    if (BundleDaemon::GetInstance().bundleMsClient_ == nullptr) {
        PRINTE("BundleDaemon", "bundleMsClient is nullptr");
        return EC_NOINIT;
    }
    int32 ret = EC_COMMU;
    if (funcId >= EXTRACT_HAP && funcId < BDS_CMD_END) {
        ret = (BundleDaemon::invokeFuncs[funcId])(req);
    }
    return BundleDaemon::GetInstance().bundleMsClient_->SendReply(ret);
}

int32 BundleDaemon::RegisterCallbackInvoke(IpcIo *req)
{
    SvcIdentity *svcIdentity = IpcIoPopSvc(req);
    if (svcIdentity == nullptr) {
        return EC_INVALID;
    }
    BundleDaemon::GetInstance().bundleMsClient_ = new BundleMsClient(*svcIdentity);
    return BundleDaemon::GetInstance().bundleMsClient_->SendReply(EC_SUCCESS);
}

int32 BundleDaemon::ExtractHapInvoke(IpcIo *req)
{
    size_t len = 0;
    const char *hapPath = reinterpret_cast<char *>(IpcIoPopString(req, &len));
    if (hapPath == nullptr || len == 0) {
        return EC_INVALID;
    }
    const char *codePath = reinterpret_cast<char *>(IpcIoPopString(req, &len));
    if (codePath == nullptr || len == 0) {
        return EC_INVALID;
    }
    return BundleDaemon::GetInstance().handler_.ExtractHap(hapPath, codePath);
}

int32 BundleDaemon::RenameFileInvoke(IpcIo *req)
{
    size_t len = 0;
    const char *oldFile = reinterpret_cast<char *>(IpcIoPopString(req, &len));
    if (oldFile == nullptr || len == 0) {
        return EC_INVALID;
    }
    const char *newFile = reinterpret_cast<char *>(IpcIoPopString(req, &len));
    if (newFile == nullptr || len == 0) {
        return EC_INVALID;
    }
    return BundleDaemon::GetInstance().handler_.RenameFile(oldFile, newFile);
}

int32 BundleDaemon::CreatePermissionInvoke(IpcIo *req)
{
    return BundleDaemon::GetInstance().handler_.CreatePermissionDir();
}

int32 BundleDaemon::CreateDataDirectoryInvoke(IpcIo *req)
{
    size_t len = 0;
    const char *dataPath = reinterpret_cast<char *>(IpcIoPopString(req, &len));
    if (dataPath == nullptr || len == 0) {
        return EC_INVALID;
    }
    int32_t uid = IpcIoPopInt32(req);
    int32_t gid = IpcIoPopInt32(req);
    bool isChown = IpcIoPopBool(req);

    return BundleDaemon::GetInstance().handler_.CreateDataDirectory(dataPath, uid, gid, isChown);
}

int32 BundleDaemon::StoreContentToFileInvoke(IpcIo *req)
{
    size_t len = 0;
    const char *path = reinterpret_cast<char *>(IpcIoPopString(req, &len));
    if (path == nullptr || len == 0) {
        return EC_INVALID;
    }
    BuffPtr *buffPtr = IpcIoPopDataBuff(req);
    if (buffPtr == nullptr || buffPtr->buffSz == 0) {
        return EC_INVALID;
    }
    char *buff = reinterpret_cast<char *>(buffPtr->buff);
    if (buff == nullptr) {
        return EC_INVALID;
    }

    int32 ret = BundleDaemon::GetInstance().handler_.StoreContentToFile(path, buff, buffPtr->buffSz);
    FreeBuffer(nullptr, buffPtr->buff);
    return ret;
}

int32 BundleDaemon::RemoveFileInvoke(IpcIo *req)
{
    size_t len = 0;
    const char *path = reinterpret_cast<char *>(IpcIoPopString(req, &len));
    if (path == nullptr || len == 0) {
        return EC_INVALID;
    }
    return BundleDaemon::GetInstance().handler_.RemoveFile(path);
}

int32 BundleDaemon::RemoveInstallDirectoryInvoke(IpcIo *req)
{
    size_t len = 0;
    const char *codePath = reinterpret_cast<char *>(IpcIoPopString(req, &len));
    if (codePath == nullptr || len == 0) {
        return EC_INVALID;
    }
    const char *dataPath = reinterpret_cast<char *>(IpcIoPopString(req, &len));
    if (dataPath == nullptr || len == 0) {
        return EC_INVALID;
    }
    return BundleDaemon::GetInstance().handler_.RemoveInstallDirectory(codePath, dataPath);
}
} // OHOS
