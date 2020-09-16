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

#include "ability_slice_route.h"

namespace OHOS {
AbilitySliceRoute::~AbilitySliceRoute()
{
    Clear();
}

void AbilitySliceRoute::SetMainRoute(const std::string &entry)
{
    if (entry.empty()) {
        return;
    }

    mainEntry_ = entry;
}

const std::string &AbilitySliceRoute::GetMainRoute() const
{
    return mainEntry_;
}

void AbilitySliceRoute::AddActionRoute(const std::string &action, const std::string &entry)
{
    if (action.empty() || entry.empty()) {
        return;
    }

    actionEntries_[action] = entry;
}

std::string AbilitySliceRoute::MatchRoute(const std::string &action)
{
    auto iter = actionEntries_.find(action);
    if (iter != actionEntries_.end()) {
        return iter->second;
    }

    return "";
}

void AbilitySliceRoute::Clear()
{
    mainEntry_.clear();
    actionEntries_.clear();
}
} // namespace OHOS