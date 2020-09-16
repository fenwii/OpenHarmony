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

#include "ability_manager.h"

#include <log.h>

#include "ability_service_interface.h"
#include "ability_service_manager.h"
#include "abilityms_client.h"

extern "C" {
const int DEFAULT_TOKEN = 1;
int StartAbility(const Want *want)
{
    if (want == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "want is null, StartAbility failed");
        return -1;
    }

    OHOS::AbilityMsClient::GetInstance().Initialize();
    return OHOS::AbilityMsClient::GetInstance().ScheduleAms(want, 0, nullptr, START_ABILITY);
}

int StopAbility(const Want *want)
{
    if (want == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "want is null, StopAbility failed");
        return -1;
    }
    OHOS::AbilityMsClient::GetInstance().Initialize();
    return OHOS::AbilityMsClient::GetInstance().ScheduleAms(want, 0, nullptr, TERMINATE_SERVICE);
}

int ConnectAbility(const Want *want, const IAbilityConnection *conn, void *data)
{
    if (want == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "want is null, ConnectAbility failed");
        return -1;
    }
    if (conn == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "conn is null, ConnectAbility failed");
        return -1;
    }

    return OHOS::AbilityServiceManager::GetInstance().ConnectAbility(*want, *conn, DEFAULT_TOKEN, data);
}

int DisconnectAbility(const IAbilityConnection *conn)
{
    if (conn == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "conn is null, DisconnectAbility failed");
        return LITEIPC_EINVAL;
    }
    return OHOS::AbilityServiceManager::GetInstance().DisconnectAbility(*conn, DEFAULT_TOKEN);
}
}
