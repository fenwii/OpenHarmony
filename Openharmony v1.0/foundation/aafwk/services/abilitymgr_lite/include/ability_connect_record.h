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

#ifndef OHOS_ABILITY_CONNECT_RECORD_H
#define OHOS_ABILITY_CONNECT_RECORD_H

#include "liteipc_adapter.h"
#include "samgr_lite.h"

namespace OHOS {
enum ConnectStatus {
    INIT,
    WAIT_CONNECT,
    CONNECTING,
    CONNECTED,
    DISCONNECTING,
    DISCONNECT,
    STOPPING,
    STOPPED,
};

class AbilityConnectRecord {
public:
    AbilityConnectRecord(const SvcIdentity &identity, uint64_t abilityToken)
        : connectSid_(identity), abilityToken_(abilityToken) {};

    ~AbilityConnectRecord() = default;

    void SetStatus(ConnectStatus status)
    {
        status_ = status;
    }

    ConnectStatus GetStatus() const
    {
        return status_;
    }

    const SvcIdentity &GetConnectSid() const
    {
        return connectSid_;
    }

    uint64_t GetAbilityToken() const
    {
        return abilityToken_;
    }

private:
    const SvcIdentity connectSid_;
    const uint64_t abilityToken_;
    ConnectStatus status_ = ConnectStatus::INIT;
};
} // namespace OHOS

#endif // OHOS_ABILITY_CONNECT_RECORD_H
