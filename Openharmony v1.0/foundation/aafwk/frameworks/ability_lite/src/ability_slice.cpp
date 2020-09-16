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

#include "ability_slice.h"

#include <ability_state.h>
#include <log.h>

#include "ability_loader.h"
#include "ability_slice_manager.h"

namespace OHOS {
void AbilitySlice::Init(AbilitySliceManager &abilitySliceManager)
{
    HILOG_INFO(HILOG_MODULE_APP, "AbilitySlice Init");
    abilitySliceManager_ = &abilitySliceManager;
    sliceState_ = STATE_INITIAL;
    AbilityContext::token_ = abilitySliceManager.GetToken();
}

void AbilitySlice::Present(AbilitySlice &abilitySlice, const Want &want)
{
    if (abilitySliceManager_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "AbilitySlice Present failed");
        return;
    }
    abilitySliceManager_->Present(*this, abilitySlice, want);
}

void AbilitySlice::Terminate()
{
    if (abilitySliceManager_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "AbilitySlice Terminate failed");
        return;
    }
    abilitySliceManager_->Terminate(*this);
}

void AbilitySlice::SetUIContent(RootView *rootView)
{
    if (abilitySliceManager_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "AbilitySlice SetUIContent failed");
        return;
    }
    curRootView_ = rootView;
    abilitySliceManager_->SetUIContent(rootView);
}

void AbilitySlice::OnStart(const Want &want)
{
    HILOG_INFO(HILOG_MODULE_APP, "AbilitySlice OnStart");
    sliceState_ = STATE_INACTIVE;
}

void AbilitySlice::OnInactive()
{
    HILOG_INFO(HILOG_MODULE_APP, "AbilitySlice OnInactive");
    sliceState_ = STATE_INACTIVE;
}

void AbilitySlice::OnActive(const Want &want)
{
    HILOG_INFO(HILOG_MODULE_APP, "AbilitySlice OnActive");
    if ((sliceState_ == STATE_BACKGROUND) && (curRootView_ != nullptr)) {
        SetUIContent(curRootView_);
    }
    sliceState_ = STATE_ACTIVE;
}

void AbilitySlice::OnBackground()
{
    HILOG_INFO(HILOG_MODULE_APP, "AbilitySlice OnBackground");
    sliceState_ = STATE_BACKGROUND;
}

void AbilitySlice::OnStop()
{
    HILOG_INFO(HILOG_MODULE_APP, "AbilitySlice OnStop");
    sliceState_ = STATE_INITIAL;
}

int AbilitySlice::GetState() const
{
    return sliceState_;
}
} // namespace OHOS
