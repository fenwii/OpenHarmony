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

#ifndef OHOS_ABILITY_LIST_H
#define OHOS_ABILITY_LIST_H

#include "ability_record.h"
#include "utils_list.h"

namespace OHOS {
class AbilityList {
public:
    AbilityList() = default;
    ~AbilityList() = default;

    void Add(AbilityRecord *abilityRecord);
    AbilityRecord *Get(uint16_t token) const;
    AbilityRecord *Get(const char *bundleName) const;
    void Erase(uint16_t token);

private:
    List<AbilityRecord *> abilityList_ {};
};
} // namespace OHOS

#endif // OHOS_ABILITY_LIST_H