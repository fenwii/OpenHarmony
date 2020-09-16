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

#ifndef OHOS_ABILITY_MGR_CONTEXT_H
#define OHOS_ABILITY_MGR_CONTEXT_H

#include "ability_mission_stack.h"
#include "ability_connect_mission.h"

namespace OHOS {
class AbilityMgrContext {
public:
    AbilityMgrContext();
    ~AbilityMgrContext();

    const AbilityMissionStack *GetLauncherMissionStacks() const;
    const AbilityMissionStack *GetDefaultMissionStacks() const;
    const AbilityMissionStack *GetTopMissionStacks() const;
    const AbilityMissionStack *GetTargetMissionStack(const char *bundleName) const;
    const AbilityConnectMission *GetServiceConnects() const;
    void SetTopMissionStacks(const AbilityMissionStack *stack);
private:
    AbilityMissionStack *launcherMissionStacks_ { nullptr };
    AbilityMissionStack *defaultMissionStacks_ { nullptr };
    AbilityConnectMission *serviceConnects_ { nullptr };
    const AbilityMissionStack *topMissionStacks_ { nullptr };
};
}  // namespace OHOS
#endif  // OHOS_ABILITY_MGR_CONTEXT_H
