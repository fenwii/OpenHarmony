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

#include "ability_mission_stack.h"

#include "util/abilityms_log.h"

namespace OHOS {
AbilityMissionStack::AbilityMissionStack(StackType type)
    : stackType_(type)
{
}

AbilityMissionStack::~AbilityMissionStack()
{
    for (auto iterator = missionRecords_.begin(); iterator != missionRecords_.end();) {
        AbilityMissionRecord *missionRecord = *iterator;
        iterator = missionRecords_.erase(iterator);
        delete missionRecord;
    }
}

StackType AbilityMissionStack::GetStackType() const
{
    return stackType_;
}

void AbilityMissionStack::PushTopMissionRecord(AbilityMissionRecord &missionRecord)
{
    missionRecord.SetMissionStack(this);
    missionRecords_.emplace_back(&missionRecord);
}

void AbilityMissionStack::MoveMissionRecordToTop(AbilityMissionRecord &missionRecord)
{
    if (missionRecords_.back() != &missionRecord) {
        missionRecords_.remove(&missionRecord);
        missionRecords_.emplace_back(&missionRecord);
    }
}

void AbilityMissionStack::RemoveMissionRecord(AbilityMissionRecord &missionRecord)
{
    missionRecords_.remove(&missionRecord);
    // clear prev mission record
    for (const auto currentMission : missionRecords_) {
        if (currentMission != nullptr && currentMission->GetPrevMissionRecord() == &missionRecord) {
            currentMission->SetPrevMissionRecord(nullptr);
        }
    }
}

void AbilityMissionStack::RemoveMissionRecord(AbilityConnectMission *connectMission, const char *bundleName)
{
    AbilityMissionRecord *missionRecord = GetTargetMissionRecord(bundleName);
    CHECK_NULLPTR_RETURN(missionRecord, "AbilityMissionStack", "missionRecord is null");
    missionRecord->ClearPageAbility(connectMission);
    RemoveMissionRecord(*missionRecord);
    delete missionRecord;
}

bool AbilityMissionStack::IsTopMissionRecord(const char *bundleName) const
{
    if (bundleName == nullptr) {
        return false;
    }
    AbilityMissionRecord *topMissionRecord = missionRecords_.back();
    if (topMissionRecord != nullptr) {
        return topMissionRecord->IsSameMissionRecord(bundleName);
    }
    return false;
}

AbilityMissionRecord *AbilityMissionStack::GetTargetMissionRecord(const char *bundleName) const
{
    CHECK_NULLPTR_RETURN_PTR(bundleName, "AbilityMissionStack", "invalid argument");
    for (const auto missionRecord : missionRecords_) {
        if (missionRecord != nullptr && missionRecord->IsSameMissionRecord(bundleName)) {
            return missionRecord;
        }
    }
    return nullptr;
}

const AbilityMissionRecord *AbilityMissionStack::GetTopMissionRecord() const
{
    return missionRecords_.back();
}

PageAbilityRecord *AbilityMissionStack::FindPageAbility(uint64_t token) const
{
    for (const auto missionRecord : missionRecords_) {
        if (missionRecord == nullptr) {
            continue;
        }
        PageAbilityRecord *record = missionRecord->FindPageAbility(token);
        if (record != nullptr) {
            return record;
        }
    }
    return nullptr;
}

PageAbilityRecord *AbilityMissionStack::FindPageAbility(const Want &want) const
{
    CHECK_NULLPTR_RETURN_PTR(want.element, "AbilityMissionStack", "invalid argument");
    AbilityMissionRecord *missionRecord = GetTargetMissionRecord(want.element->bundleName);
    if (missionRecord != nullptr) {
        return missionRecord->FindPageAbility(want);
    }
    return nullptr;
}

const PageAbilityRecord *AbilityMissionStack::GetTopPageAbility() const
{
    if (!missionRecords_.empty()) {
        return missionRecords_.back()->GetTopPageAbility();
    }
    return nullptr;
}

#ifdef OHOS_DEBUG
AbilityMsStatus AbilityMissionStack::DumpMissionStack() const
{
    if (missionRecords_.size() <= 0) {
        return AbilityMsStatus::DumpStatus("");
    }
    std::string stackType = (stackType_ == LAUNCHER) ? "launcher\n" : "default\n";
    std::string stackInfo = "MissionStack Type: " + stackType;
    AbilityMsStatus result = AbilityMsStatus::DumpStatus(stackInfo.c_str());
    for (const auto missionRecord : missionRecords_) {
        if (missionRecord != nullptr) {
            result.DumpAppend(missionRecord->DumpMissionRecord());
        }
    }
    return result;
}
#endif
}  // namespace OHOS
