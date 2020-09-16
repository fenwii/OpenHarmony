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
#include "ace_ability.h"

#include "ability_env.h"
#include "ace_log.h"
#include "ace_mem_base.h"
#include "js_fwk_common.h"
#include "root_view.h"

namespace OHOS {
namespace ACELite {
AbilityEventHandler *AceAbility::eventHandler_ = nullptr;
AceAbility *AceAbility::topAbility_ = nullptr;

REGISTER_AA(AceAbility)

void AceAbility::OnStart(const Want &want)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "AceAbility OnStart");
    eventHandler_ = AbilityEventHandler::GetCurrentHandler();

    const char * const abilitySrcPath = GetSrcPath();
    const char * const bundleName = GetBundleName();
    HILOG_DEBUG(HILOG_MODULE_ACE, "ace ability src path = %s", abilitySrcPath);
    HILOG_DEBUG(HILOG_MODULE_ACE, "ace ability bundle name = %s", bundleName);

    char* jsBundlePath = RelocateJSSourceFilePath(abilitySrcPath, "assets/js/default/");
    HILOG_DEBUG(HILOG_MODULE_ACE, "ace ability js bundle path = %s", jsBundlePath);
    const uint16_t token = 0xff; // js ability's token is hidden by AMS
    jsAbility_.Launch(jsBundlePath, bundleName, (uint16_t)token);
    ACE_FREE(jsBundlePath);
    RootView *rootView = RootView::GetInstance();
    if (rootView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get rootView is nullptr");
        return;
    }
    SetUIContent(rootView);
    Ability::OnStart(want);
    HILOG_DEBUG(HILOG_MODULE_ACE, "AceAbility OnStart Done");
}

void AceAbility::OnInactive()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "AceAbility OnInactive");
    topAbility_ = nullptr;
    Ability::OnInactive();
    HILOG_DEBUG(HILOG_MODULE_ACE, "AceAbility OnInactive Done");
}

void AceAbility::OnActive(const Want &want)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "AceAbility OnActive");
    Ability::OnActive(want);
    jsAbility_.Show();
    topAbility_ = this;
    HILOG_DEBUG(HILOG_MODULE_ACE, "AceAbility OnActive Done");
}

void AceAbility::OnBackground()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "AceAbility OnBackground");
    Ability::OnBackground();
    jsAbility_.Hide();
    HILOG_DEBUG(HILOG_MODULE_ACE, "AceAbility OnBackground Done");
}

void AceAbility::OnStop()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "AceAbility OnStop");
    Ability::OnStop();
    jsAbility_.TransferToDestroy();
    HILOG_DEBUG(HILOG_MODULE_ACE, "AceAbility OnStop Done");
}

bool AceAbility::PostUITask(std::function<void()> task)
{
    if (eventHandler_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AceAbility PostUITask failed as eventHandler_ is null!");
        return false;
    }
    eventHandler_->PostTask(task);
    return true;
}

void AceAbility::TerminateSelf()
{
    if (topAbility_ != nullptr) {
        topAbility_->TerminateAbility();
    }
}
} // namespace ACELite
} // namespace OHOS
