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
#ifndef OHOS_ACELITE_JS_ROUTER_H
#define OHOS_ACELITE_JS_ROUTER_H

#include "js_page_state_machine.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class Router final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(Router);
    Router() : currentSm_(nullptr), newSm_(nullptr), hidden_(false) {}
    ~Router()
    {
        if (currentSm_ != nullptr) {
            delete currentSm_;
        }
    }
    jerry_value_t Replace(jerry_value_t object, bool async = true);
    void ReplaceSync();
    void Show();
    void Hide();

private:
    StateMachine *currentSm_; // current state machine for current shown page
    StateMachine *newSm_;     // current state machine for target showing page
    bool hidden_;             // the flag representing whether the whole app is moved to background
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_JS_ROUTER_H
