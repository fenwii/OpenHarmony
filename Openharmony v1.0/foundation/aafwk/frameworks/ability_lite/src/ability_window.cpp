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

#include "ability_window.h"

#include "log.h"

namespace OHOS {
void AbilityWindow::SetRootView(RootView *rootView, int16_t x, int16_t y)
{
    if (rootView == nullptr) {
        return;
    }

    if (window_ == nullptr) {
        WindowConfig config = {};
        config.rect = rootView->GetRect();
        config.rect.SetPosition(x, y);
        window_ = Window::CreateWindow(config);
        if (window_ == nullptr) {
            return;
        }
    } else {
        Rect rect = rootView->GetRect();
        window_->Resize(rect.GetWidth(), rect.GetHeight());
        window_->MoveTo(x, y);
    }

    window_->UnbindRootView();
    window_->BindRootView(rootView);
    rootView->Invalidate();

    isWindowAttached = true;
}

void AbilityWindow::EnsureLatestUIAttached() const
{
    if (!isWindowAttached || (window_ == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_APP, "Should SetUIContent before slice active");
        exit(-1);
    }
}

void AbilityWindow::OnPostAbilityStart()
{
    EnsureLatestUIAttached();

    window_->Show();
}

void AbilityWindow::OnPostAbilityActive()
{
    EnsureLatestUIAttached();

    window_->RaiseToTop();
    window_->Show();
}

void AbilityWindow::OnPostAbilityBackground()
{
    EnsureLatestUIAttached();

    window_->Hide();
}

void AbilityWindow::OnPostAbilityStop()
{
    EnsureLatestUIAttached();

    window_->UnbindRootView();
    Window::DestoryWindow(window_);
    window_ = nullptr;
}
} // namespace OHOS
