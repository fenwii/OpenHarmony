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

#include "window/window.h"

#include "window/window_impl.h"

namespace OHOS {
Window* Window::CreateWindow(const WindowConfig& config)
{
    WindowImpl* window = new WindowImpl;
    if (window != nullptr) {
        if (window->Create(config) == false) {
            delete window;
            return nullptr;
        }
        window->AddToDisplay();
    }
    return window;
}

void Window::DestoryWindow(Window* window)
{
    if (window != nullptr) {
        WindowImpl* windowImpl = reinterpret_cast<WindowImpl*>(window);
        windowImpl->RemoveFromDisplay();
        windowImpl->UnbindRootView();
        windowImpl->Destory();
        delete windowImpl;
    }
}
}