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
#ifndef OHOS_ACELITE_ACE_ABILITY_H
#define OHOS_ACELITE_ACE_ABILITY_H

#include <string>

#include "ability.h"
#include "ability_event_handler.h"
#include "ability_loader.h"
#include "js_ability.h"

#ifdef OHOS_ACELITE_PRODUCT_WATCH
#error AceAbility only be used for L1 upper
#endif

namespace OHOS {
namespace ACELite {
class AceAbility final : public Ability {
public:
    static bool PostUITask(std::function<void()> task);
    static void TerminateSelf();

protected:
    void OnStart(const Want &want) override;
    void OnInactive() override;
    void OnActive(const Want &want) override;
    void OnBackground() override;
    void OnStop() override;

private:
    JSAbility jsAbility_;
    static AbilityEventHandler *eventHandler_;
    static AceAbility *topAbility_;
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_ACE_ABILITY_H
