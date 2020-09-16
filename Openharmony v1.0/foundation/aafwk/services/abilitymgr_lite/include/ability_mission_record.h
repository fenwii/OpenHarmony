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

#ifndef OHOS_ABILITY_MISSION_RECORD_H
#define OHOS_ABILITY_MISSION_RECORD_H

#include <list>

#include "ability_connect_mission.h"
#include "page_ability_record.h"

namespace OHOS {
class AbilityMissionStack;
class AbilityMissionRecord {
public:
    AbilityMissionRecord(AbilityMissionStack *missionStack, const char *bundleName);
    ~AbilityMissionRecord();
    bool IsEmpty() const;
    bool IsSameMissionRecord(const char *bundleName) const;
    void SetMissionStack(AbilityMissionStack *missionStack);
    const AbilityMissionStack *GetMissionStack() const;
    const PageAbilityRecord *GetTopPageAbility() const;
    const PageAbilityRecord *GetBottomPageAbility() const;
    PageAbilityRecord *FindPageAbility(uint64_t token) const;
    PageAbilityRecord *FindPageAbility(const Want &want) const;
    PageAbilityRecord *GetPrevPageAbility(const PageAbilityRecord &current) const;
    void PushPageAbility(PageAbilityRecord &abilityRecord);
    void RemovePageAbility(const PageAbilityRecord &target);
    void ClearPageAbility();
    void ClearPageAbility(AbilityConnectMission *connectMission);
    void SetPrevMissionRecord(const AbilityMissionRecord *missionRecord);
    const AbilityMissionRecord *GetPrevMissionRecord() const;
#ifdef OHOS_DEBUG
    AbilityMsStatus DumpMissionRecord() const;
#endif
private:
    AbilityMissionStack *abilityMissionStack_ { nullptr };
    std::list<PageAbilityRecord *> pageAbilityRecords_;
    const AbilityMissionRecord *prevMissionRecord_ { nullptr };
    const char *bundleName_ { nullptr };
};
} // namespace OHOS
#endif // OHOS_ABILITY_MISSION_RECORD_H
