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

#ifndef GRAPHIC_LITE_WINDOW_IMPL_H
#define GRAPHIC_LITE_WINDOW_IMPL_H

#include "client/iwindow.h"
#include "components/root_view.h"
#include "window/window.h"
#include "dock/screen_device.h"

namespace OHOS {
class WindowImpl : public Window {
public:
    WindowImpl();
    virtual ~WindowImpl();

    void BindRootView(RootView* rootView) override;
    void UnbindRootView() override;
    RootView* GetRootView() override;
    Rect GetRect() override;

    void Show() override;
    void Hide() override;
    void MoveTo(int16_t x, int16_t y) override;
    void Resize(int16_t width, int16_t height) override;
    void RaiseToTop() override;
    void LowerToBottom() override;

    int32_t GetWindowId() override;

    void Render();
    void Update();
    void Flush();
    bool Create(const WindowConfig& config);
    void Destory();
    void AddToDisplay();
    void RemoveFromDisplay();

private:
    void UpdateHalDisplayBuffer();

    RootView* rootView_;
    IWindow* iWindow_;
    WindowConfig config_;
    bool isShow_;
    AllocationInfo gfxAlloc_;
};
}
#endif