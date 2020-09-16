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

#ifndef GRAPHIC_LITE_PROXY_WINDOW_H
#define GRAPHIC_LITE_PROXY_WINDOW_H

#include "client/iwindow.h"
#include "client/lite_proxy_surface.h"
#include "client/lite_win_requestor.h"
#include "server/lite_win.h"

namespace OHOS {
class LiteProxyWindow : public IWindow {
public:
    LiteProxyWindow(LiteWinRequestor* requestor);
    virtual ~LiteProxyWindow();

    int Init() override;
    void Destroy() override;
    void Show() override;
    void Hide() override;
    void Resize(int16_t width, int16_t height) override;
    void MoveTo(int16_t x, int16_t y) override;
    void RaiseToTop() override;
    void LowerToBottom() override;
    ISurface* GetSurface() override;
    int32_t GetWindowId() override;
    void Update() override;

private:
    LiteWinRequestor* winRequestor_;
    int32_t id_;
    ISurface* surface_;
};
}
#endif