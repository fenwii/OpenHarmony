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

#ifndef OHOS_ABILITY_CONNECT_TRANS_PARAM_H
#define OHOS_ABILITY_CONNECT_TRANS_PARAM_H

#include <sched.h>
#include <stdlib.h>

#include "liteipc_adapter.h"
#include "want.h"

namespace OHOS {
class AbilityConnectTransParam {
public:
    AbilityConnectTransParam(Want *want, const SvcIdentity &identity, uint64_t abilityToken)
        : want_(want), identity_(identity), abilityToken_(abilityToken) {};

    AbilityConnectTransParam() = delete;
    ~AbilityConnectTransParam()
    {
        ClearWant(want_);
        delete want_;
    };

    const SvcIdentity &GetSvcIdentity() const
    {
        return identity_;
    }

    const Want *GetWant() const
    {
        return want_;
    }

    uint64_t GetToken() const
    {
        return abilityToken_;
    }

    void SetCallingUid(pid_t callingUid)
    {
        callingUid_ = callingUid;
    }

    pid_t GetCallingUid() const
    {
        return callingUid_;
    }

private:
    Want *want_ = { nullptr };
    SvcIdentity identity_;
    uint64_t abilityToken_ = 0;
    pid_t callingUid_ = -1;
};
} // namespace OHOS

#endif // OHOS_ABILITY_CONNECT_TRANS_PARAM_H
