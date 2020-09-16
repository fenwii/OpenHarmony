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

#include "ability_context.h"

#include "ability_service_interface.h"
#include "ability_service_manager.h"
#include "abilityms_client.h"

namespace OHOS {
int AbilityContext::StartAbility(const Want &want)
{
    return AbilityMsClient::GetInstance().ScheduleAms(&want, 0, nullptr, START_ABILITY);
}

int AbilityContext::TerminateAbility()
{
    return AbilityMsClient::GetInstance().ScheduleAms(nullptr, token_, nullptr, TERMINATE_ABILITY);
}

int AbilityContext::StopAbility(const Want &want)
{
    return AbilityMsClient::GetInstance().ScheduleAms(&want, 0, nullptr, TERMINATE_SERVICE);
}

int AbilityContext::ConnectAbility(const Want &want, const IAbilityConnection &conn, void *storeArg)
{
    return AbilityServiceManager::GetInstance().ConnectAbility(want, conn, token_, storeArg);
}

int AbilityContext::DisconnectAbility(const IAbilityConnection &conn)
{
    return AbilityServiceManager::GetInstance().DisconnectAbility(conn, token_);
}
} //  namespace OHOS