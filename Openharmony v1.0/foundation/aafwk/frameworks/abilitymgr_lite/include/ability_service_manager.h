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

#ifndef OHOS_ABILITY_SERVICE_MANAGER_H
#define OHOS_ABILITY_SERVICE_MANAGER_H

#include "ability_connection.h"

#include <list>
#include <mutex>

#include "nocopyable.h"
#include "want.h"

namespace OHOS {
typedef struct {
    const IAbilityConnection *conn;
    void *storeArg;
    SvcIdentity *sid;
} StoreArgs;

class AbilityServiceManager {
public:
    static AbilityServiceManager &GetInstance()
    {
        static AbilityServiceManager instance;
        return instance;
    }
    ~AbilityServiceManager();
    int ConnectAbility(const Want &want, const IAbilityConnection &conn, uint64_t token, void *storeArg);
    int DisconnectAbility(const IAbilityConnection &conn, uint64_t token);

private:
    AbilityServiceManager() = default;
    StoreArgs *AddStoreArgs(const IAbilityConnection &conn, void *storeArg);
    StoreArgs *GetStoreArgs(const IAbilityConnection &conn) const;
    StoreArgs *RemoveStoreArgs(const IAbilityConnection *conn, StoreArgs *storeArgs);
    static int32_t ConnectAbilityCallBack(const IpcContext* context, void *ipcMsg, IpcIo *data, void *arg);
    static void ClearStore(StoreArgs *storeArgs);
    std::list<StoreArgs *> storeList_;
    std::mutex mutex_;

    DISALLOW_COPY_AND_MOVE(AbilityServiceManager);
};
} // namespace OHOS

#endif // OHOS_ABILITY_SERVICE_MANAGER_H
