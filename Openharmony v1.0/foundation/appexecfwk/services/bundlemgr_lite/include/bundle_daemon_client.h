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

#ifndef OHOS_BUNLDE_DAEMON_CLIENT_H
#define OHOS_BUNLDE_DAEMON_CLIENT_H

#include <semaphore.h>

#include "hos_errno.h"
#include "iproxy_client.h"
#include "liteipc_adapter.h"
#include "mutex_lock.h"
#include "nocopyable.h"

namespace OHOS {
class BundleDaemonClient : public NoCopyable {
public:
    static BundleDaemonClient &GetInstance()
    {
        static BundleDaemonClient instance;
        return instance;
    }
    bool Initialize();
    int32 ExtractHap(const char *hapFile, const char *codePath);
    int32 RenameFile(const char *oldFile, const char *newFile);
    int32 CreatePermissionDir();
    int32 CreateDataDirectory(const char *dataPath, int32_t uid, int32_t gid, bool isChown);
    int32 StoreContentToFile(const char *file, const void *buffer, uint32_t size);
    int32 RemoveFile(const char *file);
    int32 RemoveInstallDirectory(const char *codePath, const char *dataPath);
    static int32_t BundleDaemonCallback(const IpcContext* context, void *ipcMsg, IpcIo *io, void *arg);
    static int32_t DeathCallback(const IpcContext* context, void* ipcMsg, IpcIo* data, void* arg);
private:
    BundleDaemonClient() = default;
    ~BundleDaemonClient();

    IClientProxy *bdsClient_ { nullptr };
    SvcIdentity svcIdentity_ {};
    SvcIdentity bdsSvcIdentity_ {};
    uint32_t cbid_ = INVALID_INDEX;
    sem_t sem_;
    Mutex mutex_;
    int32 result_ = EC_FAILURE;
    bool initialized_ = false;

    static void *RegisterDeathCallback(void *);
    int32 RegisterCallback();
    int32 WaitResultSync(int32 result);
};
} // namespace OHOS
#endif // OHOS_BUNLDE_DAEMON_CLIENT_H
