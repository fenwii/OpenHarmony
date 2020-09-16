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

#include "server/lite_wm.h"

#include "color.h"
#include "graphic_log.h"

namespace OHOS {
namespace {
#define EXPAND_RECT(x) x.GetLeft(), x.GetTop(), x.GetRight(), x.GetBottom()
const uint16_t CURSOR_WIDTH = 24;
const uint16_t CURSOR_HEIGHT = 25;
const uint8_t CURSOR_MAP[] = {
    /* Pixel format: ARGB1555 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00,
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
    0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00,
    0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
};

const uint8_t MAX_WINDOW_NUMBLE = 32;
const uint32_t WINDOW_ID_FULL_STORAGE = 0xFFFFFFFF;
}

LiteWM::LiteWM()
    : updates_({}), layerData_(nullptr), cursorInfo_({}), mousePosition_({}), deviceData_({}),
      needScreenshot(false), screenshotSurface_(nullptr), winIdStorage(0)
{
    InitMutex(stackLock_, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mouseLock_, NULL);
    pthread_mutex_init(&eventLock_, NULL);

    InputManagerService::GetInstance()->GetDistributer()->AddRawEventListener(this);
    InitMouseCursor();

    layerData_ = GetDevSurfaceData();
    if (layerData_ != nullptr) {
        if (layerData_->phyAddr == nullptr || layerData_->virAddr == nullptr) {
            GRAPHIC_LOGE("LayerInfo addr is null!");
        }
        GRAPHIC_LOGI("LayerInfo, width=%d, height=%d, stride=%d",
            layerData_->width, layerData_->height, layerData_->stride);
    } else {
        GRAPHIC_LOGE("LayerInfo is null!");
    }
}

LiteWM::~LiteWM()
{
}

void LiteWM::MainTaskHandler()
{
    if (layerData_ == nullptr || layerData_->phyAddr == nullptr || layerData_->virAddr == nullptr) {
        return;
    }

    if (needScreenshot) {
        Screenshot();
        needScreenshot = false;
    }

    if (cursorInfo_.enableCursor) {
        UpdateMouseCursor();
    }

    ProcessUpdates();
}

void LiteWM::UpdateMouseCursor()
{
    Rect& rect = cursorInfo_.rect;
    Point point = GetMousePosition();
    if (rect.GetLeft() == point.x && rect.GetTop() == point.y) {
        return;
    }
    cursorInfo_.needRedraw = true;
    AddUpdateRegion(rect);
    rect.SetPosition(point.x, point.y);
}

Surface* LiteWM::GetSurface(int32_t id)
{
    LiteWindow* window = GetWindowById(id);
    if (window != nullptr) {
        return window->GetSurface();
    }
    return nullptr;
}

void LiteWM::Show(int32_t id)
{
    GraphicLocker lock(stackLock_);
    LiteWindow* window = GetWindowById(id);
    if (window != nullptr) {
        window->SetIsShow(true);
        UpdateWindow(window, window->config_.rect);
    }
}

void LiteWM::Hide(int32_t id)
{
    GraphicLocker lock(stackLock_);
    LiteWindow* window = GetWindowById(id);
    if (window != nullptr) {
        window->SetIsShow(false);
        UpdateWindow(window, window->config_.rect);
    }
}

void LiteWM::RaiseToTop(int32_t id)
{
    GraphicLocker lock(stackLock_);
    auto node = GetWindowNodeById(id);
    if (node != nullptr) {
        node->prev_->next_ = node->next_;
        node->next_->prev_ = node->prev_;
        auto head = winList_.Begin()->prev_;
        node->next_ = head->next_;
        node->prev_ = head;
        head->next_->prev_ = node;
        head->next_ = node;

        UpdateWindow(winList_.Begin()->data_, node->data_->config_.rect);
    }
}

void LiteWM::LowerToBottom(int32_t id)
{
    GraphicLocker lock(stackLock_);
    auto node = GetWindowNodeById(id);
    if (node != nullptr) {
        node->prev_->next_ = node->next_;
        node->next_->prev_ = node->prev_;
        auto head = winList_.Begin()->prev_;
        node->prev_ = head->prev_;
        node->next_ = head;
        head->prev_->next_ = node;
        head->prev_ = node;

        UpdateWindow(winList_.Begin()->data_, node->data_->config_.rect);
    }
}

void LiteWM::MoveTo(int32_t id, int16_t x, int16_t y)
{
    GraphicLocker lock(stackLock_);
    LiteWindow* window = GetWindowById(id);
    if (window != nullptr) {
        window->MoveTo(x, y);
    }
}

void LiteWM::Resize(int32_t id, int16_t width, int16_t height)
{
    GraphicLocker lock(stackLock_);
    LiteWindow* window = GetWindowById(id);
    if (window == nullptr) {
        return;
    }
    Rect rectBefore = window->config_.rect;
    window->Resize(width, height);
    Rect rectAfter = window->config_.rect;
    Rect mask;
    if (mask.Intersect(rectBefore, rectAfter)) {
        int16_t x1 = mask.GetLeft();
        int16_t x2 = mask.GetRight();
        int16_t y1 = mask.GetTop();
        int16_t y2 = mask.GetBottom();
        if (x2 != rectBefore.GetRight()) {
            UpdateWindowRegion(window, {static_cast<int16_t>(x2 + 1), y1, rectBefore.GetRight(),
                rectBefore.GetBottom()});
        }
        if (y2 != rectBefore.GetBottom()) {
            UpdateWindowRegion(window, {x1, static_cast<int16_t>(y2 + 1), x2, rectBefore.GetBottom()});
        }
    }
}

void LiteWM::UpdateWindow(int32_t id)
{
    GRAPHIC_LOGI("UpdateWindow, id=%d", id);
    LiteWindow* window = GetWindowById(id);
    if (window != nullptr) {
        UpdateWindowRegion(window, window->config_.rect);
    }
}

LiteWindow* LiteWM::GetWindowById(int32_t id)
{
    if (id == INVALID_WINDOW_ID) {
        return nullptr;
    }

    LiteWindow* ret = nullptr;
    auto node = winList_.Begin();
    while (node != winList_.End()) {
        if (node->data_->id_ == id) {
            ret = node->data_;
            break;
        }
        node = node->next_;
    }
    return ret;
}

ListNode<LiteWindow*>* LiteWM::GetWindowNodeById(int32_t id)
{
    if (id == INVALID_WINDOW_ID) {
        return nullptr;
    }

    ListNode<LiteWindow*>* ret = nullptr;
    auto node = winList_.Begin();
    while (node != winList_.End()) {
        if (node->data_->id_ == id) {
            ret = node;
            break;
        }
        node = node->next_;
    }
    return ret;
}

void LiteWM::InitMouseCursor()
{
    GRAPHIC_LOGI("InitMouseCursor");
    cursorInfo_.rect.SetRect(0, 0, CURSOR_WIDTH - 1, CURSOR_HEIGHT - 1);
    cursorInfo_.needRedraw = false;
    cursorInfo_.enableCursor = false;
}

LiteWindow* LiteWM::CreateWindow(const LiteWinConfig& config)
{
    GraphicLocker lock(stackLock_);
    if (CheckWinIdIsAvailable() == false) {
        return nullptr;
    }
    LiteWindow* window = new LiteWindow(config);
    if (window == nullptr) {
        return nullptr;
    }
    if (!window->CreateSurface()) {
        delete window;
        return nullptr;
    }
    winList_.PushFront(window);
    return window;
}

void LiteWM::RemoveWindow(int32_t id)
{
    GraphicLocker lock(stackLock_);
    auto node = GetWindowNodeById(id);
    if (node == nullptr) {
        return;
    }
    LiteWindow* window = node->data_;
    winList_.Remove(node);
    UpdateWindow(winList_.Begin()->data_, window->config_.rect);
    delete window;
}

bool LiteWM::CheckWinIdIsAvailable()
{
    if (winIdStorage == WINDOW_ID_FULL_STORAGE) {
        GRAPHIC_LOGE("reach max window num!");
        return false;
    }
    return true;
}

int32_t LiteWM::GetUniqueWinId()
{
    static uint8_t winId = 0;
    if (CheckWinIdIsAvailable() == false) {
        return INVALID_WINDOW_ID;
    }
    while (winIdStorage & (1 << winId)) {
        winId++;
        winId %= MAX_WINDOW_NUMBLE;
    }
    winIdStorage |= (1 << winId);
    return winId;
}

void LiteWM::RecycleWinId(int32_t id)
{
    if (id == INVALID_WINDOW_ID) {
        return;
    }
    winIdStorage &= (~(1 << static_cast<uint32_t>(id)));
}

void LiteWM::InitMutex(pthread_mutex_t& mutex, int type)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, type);
    pthread_mutex_init(&mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

void LiteWM::UpdateWindow(const LiteWindow* window, const Rect& rect)
{
    GRAPHIC_LOGI("UpdateWindow, id=%d, rect={%d,%d,%d,%d}", window->id_, EXPAND_RECT(rect));
    UpdateWindowRegion(window, rect);
}

void LiteWM::UpdateWindowRegion(const LiteWindow* window, const Rect& rect)
{
    ListNode<LiteWindow *>* winNode = winList_.Tail();
    while (winNode != winList_.End()) {
        if (winNode->data_ == window) {
            CalculateUpdateRegion(winNode->prev_, EXPAND_RECT(rect));
            break;
        }
        winNode = winNode->prev_;
    }
}

void LiteWM::CalculateUpdateRegion(const ListNode<LiteWindow*>* winNode, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    Rect rect(x1, y1, x2, y2);
    if (winNode == winList_.End()) {
        AddUpdateRegion(rect);
        return;
    }
    LiteWindow* window = winNode->data_;
    if (window->isShow_ && window->config_.opacity == OPA_OPAQUE) {
        Rect& winRect = window->config_.rect;
        Rect mask;
        GRAPHIC_LOGD("winRect={%d,%d,%d,%d}, rect={%d,%d,%d,%d}", EXPAND_RECT(winRect), EXPAND_RECT(rect));
        if (mask.Intersect(winRect, rect)) {
            if (x1 != mask.GetLeft()) {
                CalculateUpdateRegion(winNode->prev_, x1, y1, mask.GetLeft() - 1, y2);
            }

            if (y1 != mask.GetTop()) {
                CalculateUpdateRegion(winNode->prev_, mask.GetLeft(), y1, x2, mask.GetTop() - 1);
            }

            if (x2 != mask.GetRight()) {
                CalculateUpdateRegion(winNode->prev_, mask.GetRight() + 1, mask.GetTop(), x2, y2);
            }

            if (y2 != mask.GetBottom()) {
                CalculateUpdateRegion(winNode->prev_, mask.GetLeft(), mask.GetBottom() + 1, mask.GetRight(), y2);
            }
            return;
        }
    }
    CalculateUpdateRegion(winNode->prev_, x1, y1, x2, y2);
}

void LiteWM::AddUpdateRegion(const Rect& rect)
{
    GraphicLocker lock(stackLock_);
    GRAPHIC_LOGD("AddUpdateRegion, rect={%d,%d,%d,%d}", EXPAND_RECT(rect));
    if (updates_.num == 0) {
        updates_.updates[updates_.num++] = rect;
        updates_.bound = rect;
    } else {
        for (int i = 0; i < updates_.num; i++) {
            Rect& updateRect = updates_.updates[i];
            if (updateRect.IsIntersect(rect) || updateRect.IsExtends(rect)) {
                updateRect.Join(updateRect, rect);
                updates_.bound.Join(updates_.bound, rect);
                return;
            }
        }
        if (updates_.num == MAX_UPDATE_SIZE) {
            updates_.bound.Join(updates_.bound, rect);
            updates_.num = 0;
            updates_.updates[updates_.num++] = updates_.bound;
        } else {
            updates_.updates[updates_.num++] = rect;
            updates_.bound.Join(updates_.bound, rect);
        }
    }
}

void LiteWM::ProcessUpdates()
{
    bool needFlush = false;
    {
        GraphicLocker lock(stackLock_);
        for (int i = 0; i < updates_.num; i++) {
            ListNode<LiteWindow *>* winNode = winList_.Begin();
            DrawRegion(winNode, EXPAND_RECT(updates_.updates[i]));

            if (cursorInfo_.enableCursor && cursorInfo_.rect.IsIntersect(updates_.updates[i])) {
                cursorInfo_.needRedraw = true;
            }
        }
        if (updates_.num != 0 || (cursorInfo_.enableCursor && cursorInfo_.needRedraw)) {
            needFlush = true;
        }
        updates_ = {};
    }

    if (cursorInfo_.enableCursor && cursorInfo_.needRedraw) {
        DrawMouseCursor();
        cursorInfo_.needRedraw = false;
    }

    if (needFlush) {
        LcdFlush();
    }
}

void LiteWM::DrawRegion(const ListNode<LiteWindow*>* winNode, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    if (winNode == winList_.End()) {
        DrawBackground(x1, y1, x2, y2);
        return;
    }

    LiteWindow* window = winNode->data_;
    if (window == nullptr) {
        return;
    }
    window->UpdateBackBuf();

    Rect rect(x1, y1, x2, y2);
    Rect& winRect = window->config_.rect;
    Rect mask;
    if (!window->isShow_ || window->config_.opacity == OPA_TRANSPARENT ||
        window->backBuf_ == nullptr || !mask.Intersect(winRect, rect)) {
        GRAPHIC_LOGI("winRect={%d,%d,%d,%d}, rect={%d,%d,%d,%d}", EXPAND_RECT(winRect), EXPAND_RECT(rect));
        DrawRegion(winNode->next_, x1, y1, x2, y2);
        return;
    }

    int x = mask.GetLeft();
    int y = mask.GetTop();

    if (window->config_.opacity != OPA_OPAQUE) {
        DrawRegion(winNode->next_, EXPAND_RECT(mask));
    }

    Rect srcRect = mask;
    srcRect.SetPosition(mask.GetLeft() - winRect.GetLeft(), mask.GetTop() - winRect.GetTop());
    GRAPHIC_LOGD("Blit, id=%d, srcRect={%d,%d,%d,%d}, x=%d, y=%d", window->id_, EXPAND_RECT(srcRect), x, y);
    window->Flush(srcRect, layerData_, x, y);
    GRAPHIC_LOGD("Blit finish");

    if (x1 != mask.GetLeft()) {
        DrawRegion(winNode->next_, x1, y1, mask.GetLeft() - 1, y2);
    }

    if (y1 != mask.GetTop()) {
        DrawRegion(winNode->next_, mask.GetLeft(), y1, x2, mask.GetTop() - 1);
    }

    if (x2 != mask.GetRight()) {
        DrawRegion(winNode->next_, mask.GetRight() + 1, mask.GetTop(), x2, y2);
    }

    if (y2 != mask.GetBottom()) {
        DrawRegion(winNode->next_, mask.GetLeft(), mask.GetBottom() + 1, mask.GetRight(), y2);
    }
}

void LiteWM::DrawBackground(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    Rect rect(0, 0, layerData_->width - 1, layerData_->height - 1);
    Rect rectBg(x1, y1, x2, y2);
    if (rect.Intersect(rect, rectBg) == false) {
        return;
    }

    x1 = rect.GetLeft();
    x2 = rect.GetRight();
    y1 = rect.GetTop();
    y2 = rect.GetBottom();

    GRAPHIC_LOGD("DrawBackground, {%d,%d,%d,%d}", x1, y1, x2, y2);
    int16_t len = (x2 - x1 + 1) * layerData_->bytePerPixel;
    for (int y = y1; y <= y2; y++) {
        uint16_t *buf1 = (uint16_t *)(layerData_->virAddr + y * layerData_->stride);
        if (memset_s(buf1 + x1, len, 0, len) != EOK) {
            GRAPHIC_LOGE("memset_s error!");
        }
    }
}

void LiteWM::DrawMouseCursor()
{
    Rect rect(0, 0, layerData_->width - 1, layerData_->height - 1);
    if (rect.Intersect(rect, cursorInfo_.rect) == false) {
        return;
    }

    int16_t x1 = rect.GetLeft();
    int16_t x2 = rect.GetRight();
    int16_t y1 = rect.GetTop();
    int16_t y2 = rect.GetBottom();

    uint16_t* buf = (uint16_t*)CURSOR_MAP;
    uint8_t* dstBuf = layerData_->virAddr + y1 * layerData_->stride;
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            if ((*buf) & 0x8000) {
                *((uint16_t*)dstBuf + x) = *(buf);
            }
            buf++;
        }
        dstBuf += layerData_->stride;
        buf += (CURSOR_WIDTH - x2 + x1 - 1);
    }
}

LiteWindow* LiteWM::FindTargetWindow(const RawEvent& event)
{
    if (winList_.IsEmpty()) {
        return nullptr;
    }

    LiteWindow* targetWindow = nullptr;
    switch (event.type) {
        case InputDevType::INDEV_TYPE_MOUSE:
        case InputDevType::INDEV_TYPE_TOUCH: {
            auto node = winList_.Begin();
            while (node != winList_.End()) {
                Point p = { event.x, event.y };
                if (!node->data_->GetConfig().rect.IsContains(p)) {
                    node = node->next_;
                    continue;
                }
                if (node->data_->GetConfig().opacity == 0) {
                    node = node->next_;
                    continue;
                }
                targetWindow = node->data_;
                break;
            }
            break;
        }
        case InputDevType::INDEV_TYPE_KEY:
        case InputDevType::INDEV_TYPE_BUTTON: {
            targetWindow = winList_.Front();
            break;
        }
        default:
            break;
    }
    return targetWindow;
}

void LiteWM::OnRawEvent(const RawEvent& rawEvent)
{
    static bool firstTime = true;
    if (layerData_ == nullptr) {
        return;
    }

    RawEvent event = rawEvent;
    if (GetLayerRotateType() == LAYER_ROTATE_90) {
        int16_t tmp = layerData_->height - event.x;
        event.x = event.y;
        event.y = tmp;
    }

    if (firstTime) {
        if (event.type == InputDevType::INDEV_TYPE_MOUSE) {
            cursorInfo_.enableCursor = true;
            cursorInfo_.needRedraw = true;
        } else {
            cursorInfo_.enableCursor = false;
        }
        firstTime = false;
    }

    if (cursorInfo_.enableCursor) {
        SetMousePosition(event.x, event.y);
    }

    LiteWindow* targetWindow = FindTargetWindow(event);
    if (targetWindow == nullptr) {
        return;
    }

    SetEventData(targetWindow, event);
}

void LiteWM::OnScreenshot(Surface* surface)
{
    needScreenshot = true;
    if (screenshotSurface_ != nullptr) {
        delete screenshotSurface_;
    }
    screenshotSurface_ = surface;
}

void LiteWM::Screenshot()
{
    if (screenshotSurface_ == nullptr) {
        return;
    }

    SurfaceBuffer* buffer = screenshotSurface_->RequestBuffer();
    if (buffer != nullptr) {
        void* virAddr = buffer->GetVirAddr();
        if (virAddr != nullptr) {
            if (memcpy_s(virAddr, buffer->GetSize(), layerData_->virAddr, buffer->GetSize()) != EOK) {
                GRAPHIC_LOGE("memcpy_s error!");
            }
        }
        screenshotSurface_->FlushBuffer(buffer);
    }
    delete screenshotSurface_;
    screenshotSurface_ = nullptr;
}
}
