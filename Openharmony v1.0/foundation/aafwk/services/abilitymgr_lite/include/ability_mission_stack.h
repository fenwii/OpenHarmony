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

#ifndef OHOS_ABILITY_MISSION_STACK_H
#define OHOS_ABILITY_MISSION_STACK_H

#include <list>

#include "ability_connect_mission.h"
#include "ability_mission_record.h"

namespace OHOS {
typedef enum {
    LAUNCHER,
    DEFAULT,
} StackType;
class AbilityMissionStack {
public:
    explicit AbilityMissionStack(StackType type);
    ~AbilityMissionStack();
    StackType GetStackType() const;
    // MissionRecord
    void PushTopMissionRecord(AbilityMissionRecord &missionRecord);
    void MoveMissionRecordToTop(AbilityMissionRecord &missionRecord);
    AbilityMissionRecord *GetTargetMissionRecord(const char *bundleName) const;
    const AbilityMissionRecord *GetTopMissionRecord() const;
    void RemoveMissionRecord(AbilityMissionRecord &missionRecord);
    void RemoveMissionRecord(AbilityConnectMission *connectMission, const char *bundleName);
    bool IsTopMissionRecord(const char *bundleName) const;
    // PageAbilityRecord
    PageAbilityRecord *FindPageAbility(uint64_t token) const;
    PageAbilityRecord *FindPageAbility(const Want &want) const;
    const PageAbilityRecord *GetTopPageAbility() const;
#ifdef OHOS_DEBUG
    AbilityMsStatus DumpMissionStack() const;
#endif
private:
    std::list<AbilityMissionRecord *> missionRecords_;
    StackType stackType_;
};
}  // namespace OHOS
#endif  // OHOS_ABILITY_MISSION_STACK_H
