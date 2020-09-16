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

#include "ability_connect_mission.h"

#include <string.h>

#include "util/abilityms_log.h"

namespace OHOS {
AbilityConnectMission::~AbilityConnectMission()
{
    for (auto iterator = serviceRecords_.begin(); iterator != serviceRecords_.end(); ++iterator) {
        auto record = *iterator;
        delete record;
    }
    serviceRecords_.clear();
    PRINTD("AbilityConnectMission", "Constructor");
}

void AbilityConnectMission::PushServiceRecord(PageAbilityRecord &abilityRecord)
{
    serviceRecords_.emplace_back(&abilityRecord);
}

PageAbilityRecord *AbilityConnectMission::FindServiceRecord(uint64_t token) const
{
    for (const auto record : serviceRecords_) {
        if (record != nullptr && record->GetToken() == token) {
            return record;
        }
    }
    return nullptr;
}

PageAbilityRecord *AbilityConnectMission::FindServiceRecord(const char *bundleName, const char *abilityName) const
{
    CHECK_NULLPTR_RETURN_PTR(bundleName, "AbilityConnectMission", "invalid argument");
    CHECK_NULLPTR_RETURN_PTR(abilityName, "AbilityConnectMission", "invalid argument");
    for (const auto record : serviceRecords_) {
        if (record != nullptr) {
            const char *recordBundleName = record->GetAbilityInfo().bundleName;
            const char *recordAbilityName = record->GetAbilityInfo().name;
            if (recordBundleName == nullptr || recordAbilityName == nullptr) {
                continue;
            }
            if (strcmp(recordBundleName, bundleName) == 0 && strcmp(recordAbilityName, abilityName) == 0) {
                return record;
            }
        }
    }
    return nullptr;
}

PageAbilityRecord *AbilityConnectMission::FindServiceRecord(const SvcIdentity &connectSid, uint64_t abilityToken) const
{
    for (const auto record : serviceRecords_) {
        if (record != nullptr && record->GetConnectRecord(connectSid, abilityToken) != nullptr) {
            return record;
        }
    }
    return nullptr;
}

void AbilityConnectMission::RemoveServiceRecord(uint64_t token)
{
    for (auto iterator = serviceRecords_.begin(); iterator != serviceRecords_.end();) {
        auto record = *iterator;
        if (record != nullptr && record->GetToken() == token) {
            iterator = serviceRecords_.erase(iterator);
            delete record;
        } else {
            ++iterator;
        }
    }
}

void AbilityConnectMission::RemoveServiceRecord(const char *bundleName)
{
    CHECK_NULLPTR_RETURN(bundleName, "AbilityConnectMission", "invalid argument");
    for (auto iterator = serviceRecords_.begin(); iterator != serviceRecords_.end();) {
        auto record = *iterator;
        if (record != nullptr && record->IsSamePageAbility(bundleName)) {
            AbilityMsStatus status = record->StopAbilityDone();
            if (!status.IsOk()) {
                PRINTW("RemoveServiceRecord", "service disconnectDoneTransaction failed");
            }
            iterator = serviceRecords_.erase(iterator);
            delete record;
        } else {
            ++iterator;
        }
    }
}

int32_t AbilityConnectMission::CountServiceInApp(const char *bundleName)
{
    if (bundleName == nullptr) {
        return 0;
    }
    int32_t retVal = 0;
    for (const auto record : serviceRecords_) {
        if (record == nullptr) {
            continue;
        }
        if (record->GetAbilityInfo().bundleName != nullptr &&
            strcmp(record->GetAbilityInfo().bundleName, bundleName) == 0) {
            retVal++;
        }
    }
    return retVal;
}

#ifdef OHOS_DEBUG
AbilityMsStatus AbilityConnectMission::DumpConnectMission() const
{
    if (serviceRecords_.empty()) {
        return AbilityMsStatus::DumpStatus("");
    }
    std::string connectInfo = "ConnectMission: \n";
    AbilityMsStatus result = AbilityMsStatus::DumpStatus(connectInfo.c_str());
    for (const auto target : serviceRecords_) {
        if (target != nullptr) {
            result.DumpAppend(target->DumpAbilityRecord());
        }
    }
    return result;
}
#endif

void AbilityConnectMission::RemoveConnectRecordByPageToken(uint64_t token, const char *bundleName)
{
    CHECK_NULLPTR_RETURN(bundleName, "AbilityConnectMission", "invalid argument");
    for (auto iterator = serviceRecords_.begin(); iterator != serviceRecords_.end(); ++iterator) {
        auto record = *iterator;
        if (record != nullptr && record->GetAbilityInfo().bundleName != nullptr &&
            strcmp(record->GetAbilityInfo().bundleName, bundleName) != 0) {
            record->RemoveConnectRecordByPageToken(token);
        }
    }
}
} // namespace OHOS
