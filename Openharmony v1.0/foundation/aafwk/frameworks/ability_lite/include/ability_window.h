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

#ifndef OHOS_ABILITY_WINDOW_H
#define OHOS_ABILITY_WINDOW_H

#include <window/window.h>

#include "nocopyable.h"

namespace OHOS {
class AbilityWindow : public NoCopyable {
public:
    AbilityWindow() = default;
    ~AbilityWindow() override = default;

    void SetRootView(RootView *rootView, int16_t x = 0, int16_t y = 0);

    void OnPostAbilityStart();
    void OnPostAbilityActive();
    void OnPostAbilityBackground();
    void OnPostAbilityStop();
private:
    void EnsureLatestUIAttached() const;

    Window *window_ { nullptr };
    bool isWindowAttached { false };
};
} // namespace OHOS

#endif // OHOS_ABILITY_WINDOW_H