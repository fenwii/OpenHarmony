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

#ifndef OHOS_ABILITY_SLICE_ROUTE_H
#define OHOS_ABILITY_SLICE_ROUTE_H

#include <map>
#include <string>

namespace OHOS {
class AbilitySliceRoute {
public:
    AbilitySliceRoute() = default;
    ~AbilitySliceRoute();

    void SetMainRoute(const std::string &entry);
    const std::string &GetMainRoute() const;
    void AddActionRoute(const std::string &action, const std::string &entry);
    std::string MatchRoute(const std::string &action);
    void Clear();

private:
    std::string mainEntry_ {};
    std::map<std::string, std::string> actionEntries_ {};
};
} // namespace OHOS

#endif // OHOS_ABILITY_SLICE_ROUTE_H
