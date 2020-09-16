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

#ifndef GRAPHIC_LITE_IWINDOWS_MANAGER_H
#define GRAPHIC_LITE_IWINDOWS_MANAGER_H

#include "client/iwindow.h"
#include "geometry2d.h"
#include "input_event_info.h"
#include "list.h"

namespace OHOS {
/**
 * @brief The IWindowsManager class is an abstract definition of windows manager.
 *        Provides a series of client/interfaces for window management, event processing, etc.
 */
class IWindowsManager {
public:
    class ScreenshotListener {
    public:
        virtual void OnScreenshotEnd(uint8_t* virAddr, uint32_t size) = 0;
    };

    IWindowsManager() {}

    virtual ~IWindowsManager() {}

    /**
     * @brief Get the IWindowsManager's singleton.
     * @return IWindowsManager's singleton
     */
    static IWindowsManager* GetInstance();

    /**
     * @brief Do some initialization after creating the windows manager object.
     * @return The result of initialize.
     */
    virtual int Init() = 0;

    virtual IWindow* CreateWindow(const LiteWinConfig& config) = 0;

    virtual void RemoveWindow(IWindow* win) = 0;

    virtual void GetEventData(DeviceData* data) = 0;

    virtual void Screenshot() = 0;

    virtual void SetScreenshotListener(ScreenshotListener* listener) = 0;
};
}
#endif // GRAPHIC_LITE_IWINDOWS_MANAGER_H
