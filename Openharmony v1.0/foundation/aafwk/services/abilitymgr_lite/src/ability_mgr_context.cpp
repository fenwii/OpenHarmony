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

#include "ability_mgr_context.h"
#include "ability_mission_stack.h"
#include "util/abilityms_helper.h"

namespace OHOS {
AbilityMgrContext::AbilityMgrContext()
{
    launcherMissionStacks_ = new AbilityMissionStack(LAUNCHER);
    defaultMissionStacks_ = new AbilityMissionStack(DEFAULT);
    serviceConnects_ = new AbilityConnectMission();
}

AbilityMgrContext::~AbilityMgrContext()
{
    delete launcherMissionStacks_;
    launcherMissionStacks_ = nullptr;
    delete defaultMissionStacks_;
    defaultMissionStacks_ = nullptr;
    delete serviceConnects_;
    serviceConnects_ = nullptr;
    topMissionStacks_ = nullptr;
}

const AbilityMissionStack *AbilityMgrContext::GetLauncherMissionStacks() const
{
    return launcherMissionStacks_;
}

const AbilityMissionStack *AbilityMgrContext::GetDefaultMissionStacks() const
{
    return defaultMissionStacks_;
}

const AbilityMissionStack *AbilityMgrContext::GetTopMissionStacks() const
{
    return topMissionStacks_;
}

const AbilityMissionStack *AbilityMgrContext::GetTargetMissionStack(const char *bundleName) const
{
    if (AbilityMsHelper::IsLauncherAbility(bundleName)) {
        return launcherMissionStacks_;
    }
    return defaultMissionStacks_;
}

void AbilityMgrContext::SetTopMissionStacks(const AbilityMissionStack *stack)
{
    topMissionStacks_ = stack;
}

const AbilityConnectMission *AbilityMgrContext::GetServiceConnects() const
{
    return serviceConnects_;
}
}  // namespace OHOS
