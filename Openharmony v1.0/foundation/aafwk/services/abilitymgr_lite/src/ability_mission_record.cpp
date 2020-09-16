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

#include "ability_mission_record.h"

#include "adapter.h"
#include "util/abilityms_log.h"
#include "utils.h"

namespace OHOS {
AbilityMissionRecord::AbilityMissionRecord(AbilityMissionStack* missionStack, const char *bundleName)
    : abilityMissionStack_(missionStack)
{
    if (bundleName != nullptr) {
        bundleName_ = Utils::Strdup(bundleName);
    }
    PRINTD("AbilityMissionRecord", "Constuctor");
}

AbilityMissionRecord::~AbilityMissionRecord()
{
    abilityMissionStack_ = nullptr;
    ClearPageAbility();
    AdapterFree(bundleName_);
    PRINTD("AbilityMissionRecord", "Destuctor");
}

bool AbilityMissionRecord::IsEmpty() const
{
    return pageAbilityRecords_.empty();
}

bool AbilityMissionRecord::IsSameMissionRecord(const char *bundleName) const
{
    if (bundleName == nullptr || bundleName_ == nullptr) {
        return false;
    }
    if (strcmp(bundleName, bundleName_) == 0) {
        return true;
    }
    return false;
}

void AbilityMissionRecord::SetMissionStack(AbilityMissionStack *missionStack)
{
    abilityMissionStack_ = missionStack;
}

const AbilityMissionStack *AbilityMissionRecord::GetMissionStack() const
{
    return abilityMissionStack_;
}

const PageAbilityRecord *AbilityMissionRecord::GetTopPageAbility() const
{
    return pageAbilityRecords_.back();
}

const PageAbilityRecord *AbilityMissionRecord::GetBottomPageAbility() const
{
    return pageAbilityRecords_.front();
}

PageAbilityRecord *AbilityMissionRecord::FindPageAbility(uint64_t token) const
{
    for (auto iterator = pageAbilityRecords_.begin(); iterator != pageAbilityRecords_.end(); ++iterator) {
        PageAbilityRecord *record = *iterator;
        if (record != nullptr && record->GetToken() == token) {
            return record;
        }
    }
    return nullptr;
}

PageAbilityRecord *AbilityMissionRecord::FindPageAbility(const Want &want) const
{
    for (auto iterator = pageAbilityRecords_.begin(); iterator != pageAbilityRecords_.end(); ++iterator) {
        PageAbilityRecord *record = *iterator;
        if (record != nullptr && record->IsSamePageAbility(want)) {
            return record;
        }
    }
    return nullptr;
}

PageAbilityRecord *AbilityMissionRecord::GetPrevPageAbility(const PageAbilityRecord &current) const
{
    for (auto iterator = pageAbilityRecords_.begin(); iterator != pageAbilityRecords_.end(); ++iterator) {
        PageAbilityRecord *record = *iterator;
        if (record != nullptr && record->IsSamePageAbility(current)) {
            if (iterator == pageAbilityRecords_.begin()) {
                return nullptr;
            }
            return *(--iterator);
        }
    }
    return nullptr;
}

void AbilityMissionRecord::PushPageAbility(PageAbilityRecord &abilityRecord)
{
    abilityRecord.SetMissionRecord(this);
    pageAbilityRecords_.emplace_back(&abilityRecord);
}

void AbilityMissionRecord::RemovePageAbility(const PageAbilityRecord &target)
{
    auto iterator = pageAbilityRecords_.begin();
    while (iterator != pageAbilityRecords_.end()) {
        PageAbilityRecord *oldRecord = *iterator;
        if (oldRecord != nullptr && oldRecord->IsSamePageAbility(target)) {
            break;
        }
        ++iterator;
    }

    // remove from current to top of stack
    while (iterator != pageAbilityRecords_.end()) {
        PageAbilityRecord* oldRecord = *iterator;
        iterator = pageAbilityRecords_.erase(iterator);
        delete oldRecord;
    }
}

void AbilityMissionRecord::ClearPageAbility()
{
    for (auto iterator = pageAbilityRecords_.begin(); iterator != pageAbilityRecords_.end();) {
        PageAbilityRecord *abilityRecord = *iterator;
        iterator = pageAbilityRecords_.erase(iterator);
        delete abilityRecord;
    }
}

void AbilityMissionRecord::ClearPageAbility(AbilityConnectMission *connectMission)
{
    for (auto iterator = pageAbilityRecords_.begin(); iterator != pageAbilityRecords_.end();) {
        PageAbilityRecord *abilityRecord = *iterator;
        iterator = pageAbilityRecords_.erase(iterator);
        if (connectMission != nullptr) {
            connectMission->RemoveConnectRecordByPageToken(abilityRecord->GetToken(), bundleName_);
        }
        delete abilityRecord;
    }
}

void AbilityMissionRecord::SetPrevMissionRecord(const AbilityMissionRecord *missionRecord)
{
    prevMissionRecord_ = missionRecord;
}

const AbilityMissionRecord *AbilityMissionRecord::GetPrevMissionRecord() const
{
    return prevMissionRecord_;
}

#ifdef OHOS_DEBUG
AbilityMsStatus AbilityMissionRecord::DumpMissionRecord() const
{
    std::string missionInfo = "    MissionRecord: ";
    if (bundleName_ != nullptr) {
        missionInfo.append(bundleName_);
    }
    missionInfo.append("\n");
    AbilityMsStatus result = AbilityMsStatus::DumpStatus(missionInfo.c_str());
    for (auto iterator = pageAbilityRecords_.rbegin(); iterator != pageAbilityRecords_.rend(); ++iterator) {
        PageAbilityRecord *target = *iterator;
        if (target != nullptr) {
            result.DumpAppend(target->DumpAbilityRecord());
        }
    }
    return result;
}
#endif
}  // namespace OHOS
