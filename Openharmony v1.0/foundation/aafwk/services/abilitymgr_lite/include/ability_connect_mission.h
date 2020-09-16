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

#ifndef OHOS_ABILITY_CONNECT_MISSION_H
#define OHOS_ABILITY_CONNECT_MISSION_H

#include <list>

#include "page_ability_record.h"

namespace OHOS {
class AbilityConnectMission {
public:
    AbilityConnectMission() = default;
    ~AbilityConnectMission();

    void PushServiceRecord(PageAbilityRecord &abilityRecord);
    PageAbilityRecord *FindServiceRecord(uint64_t token) const;
    PageAbilityRecord *FindServiceRecord(const char *bundleName, const char *abilityName) const;
    PageAbilityRecord *FindServiceRecord(const SvcIdentity &connectSid, uint64_t abilityToken) const;
    void RemoveServiceRecord(uint64_t token);
    void RemoveServiceRecord(const char *bundleName);
    int32_t CountServiceInApp(const char *bundleName);
#ifdef OHOS_DEBUG
    AbilityMsStatus DumpConnectMission() const;
#endif
    void RemoveConnectRecordByPageToken(uint64_t token, const char *bundleName);

private:
    std::list<PageAbilityRecord *> serviceRecords_;
};
} // namespace OHOS

#endif // OHOS_ABILITY_CONNECT_MISSION_H
