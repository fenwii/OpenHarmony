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

#ifndef GRAPHIC_LITE_PROXY_WINDOWS_MANAGER_H
#define GRAPHIC_LITE_PROXY_WINDOWS_MANAGER_H

#include "client/iwindows_manager.h"
#include "client/isurface.h"
#include "client/lite_proxy_window.h"

namespace OHOS {
class LiteProxyWindowsManager : public IWindowsManager {
public:
    LiteProxyWindowsManager() {}
    virtual ~LiteProxyWindowsManager() {}

    int Init() override;
    IWindow* CreateWindow(const LiteWinConfig& config) override;
    void RemoveWindow(IWindow* win) override;
    void GetEventData(DeviceData* data) override;
    void Screenshot() override;
    void SetScreenshotListener(ScreenshotListener* listener) override;
};
}
#endif