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

#ifndef GRAPHIC_LITE_LITE_WM_H
#define GRAPHIC_LITE_LITE_WM_H

#include <pthread.h>

#include "surface.h"

#include "geometry2d.h"
#include "graphic_locker.h"
#include "hi_fbdev.h"
#include "input_manager_service.h"
#include "list.h"

#include "server/lite_win.h"

namespace OHOS {
constexpr uint8_t MAX_UPDATE_SIZE = 8;
struct UpdateRegions {
    int num;
    Rect updates[MAX_UPDATE_SIZE];
    Rect bound;
};

struct CursorInfo {
    Rect rect;
    bool needRedraw;
    bool enableCursor;
};

class LiteWM : public InputEventDistributer::RawEventListener {
public:
    static LiteWM* GetInstance()
    {
        static LiteWM liteWm;
        return &liteWm;
    }

    void MainTaskHandler();

    void InitMouseCursor();
    void UpdateMouseCursor();
    void DrawMouseCursor();

    bool CheckWinIdIsAvailable();
    int32_t GetUniqueWinId();
    void RecycleWinId(int32_t id);

    Surface* GetSurface(int32_t id);
    void Show(int32_t id);
    void Hide(int32_t id);
    void RaiseToTop(int32_t id);
    void LowerToBottom(int32_t id);
    void MoveTo(int32_t id, int16_t x, int16_t y);
    void Resize(int32_t id, int16_t width, int16_t height);
    void UpdateWindow(int32_t id);

    void UpdateWindow(const LiteWindow* window, const Rect& rect);
    void UpdateWindowRegion(const LiteWindow* window, const Rect& rect);
    void CalculateUpdateRegion(const ListNode<LiteWindow*>* winNode, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void ProcessUpdates();
    void DrawRegion(const ListNode<LiteWindow *>* winNode, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void DrawBackground(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void AddUpdateRegion(const Rect& rect);

    LiteWindow* CreateWindow(const LiteWinConfig& config);
    void RemoveWindow(int32_t id);
    LiteWindow* GetWindowById(int32_t id);
    ListNode<LiteWindow*>* GetWindowNodeById(int32_t id);
    LiteWindow* FindTargetWindow(const RawEvent& event);

    void OnRawEvent(const RawEvent& rawEvent) override;

    void Screenshot();
    void OnScreenshot(Surface* surface);

    Point GetMousePosition()
    {
        GraphicLocker lock(mouseLock_);
        return mousePosition_;
    }

    void SetMousePosition(int16_t x, int16_t y)
    {
        x = (x < 0) ? 0 : (x > layerData_->width - 1) ? (layerData_->width - 1) : x;
        y = (y < 0) ? 0 : (y > layerData_->height - 1) ? (layerData_->height - 1) : y;

        GraphicLocker lock(mouseLock_);
        mousePosition_.x = x;
        mousePosition_.y = y;
    }

    void GetEventData(DeviceData* data)
    {
        GraphicLocker lock(eventLock_);
        *data = deviceData_;
    }

    void SetEventData(const LiteWindow* window, const RawEvent& event)
    {
        GraphicLocker lock(eventLock_);
        deviceData_.point.x = event.x;
        deviceData_.point.y = event.y;
        deviceData_.state = event.state;
        deviceData_.winId = window->GetWindowId();
    }

private:
    LiteWM();
    virtual ~LiteWM();
    void InitMutex(pthread_mutex_t& mutex, int type);

    List<LiteWindow*> winList_;
    UpdateRegions updates_;
    LiteSurfaceData* layerData_;
    CursorInfo cursorInfo_;
    Point mousePosition_;

    pthread_mutex_t stackLock_;
    pthread_mutex_t mouseLock_;
    pthread_mutex_t eventLock_;

    DeviceData deviceData_;

    bool needScreenshot;
    Surface* screenshotSurface_;

    // Store window ID by bit
    uint32_t winIdStorage;
};
}
#endif

