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

#include "ability_stack.h"

#include "ability_record.h"

namespace OHOS {
const AbilityRecord *AbilityStack::GetTopAbility()
{
    if (abilityStack_.Size() != 0) {
        return abilityStack_.Front();
    }
    return nullptr;
}

int AbilityStack::GetAllAbilities(AbilityRecord **abilityRecords)
{
    int size = abilityStack_.Size();
    if (size == 0) {
        *abilityRecords = nullptr;
        return 0;
    }

    auto ars = new AbilityRecord[size];
    *abilityRecords = ars;
    for (auto node = abilityStack_.Begin(); node != abilityStack_.End(); node = node->next_) {
        if (node->value_ == nullptr) {
            continue;
        }
        AbilityRecord::CopyAbilityRecord(*(node->value_), *ars);
        ars++;
    }

    return size;
}

void AbilityStack::PushAbility(AbilityRecord *record)
{
    if (record != nullptr) {
        abilityStack_.PushFront(record);
    }
}

void AbilityStack::PopAbility()
{
    abilityStack_.PopFront();
}
} // namespace OHOS