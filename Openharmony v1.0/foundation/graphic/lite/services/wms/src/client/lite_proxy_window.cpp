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

#include "client/lite_proxy_window.h"
#include "graphic_log.h"
#include "surface.h"

namespace OHOS {
LiteProxyWindow::LiteProxyWindow(LiteWinRequestor* requestor)
    : winRequestor_(requestor), id_(INVALID_WINDOW_ID), surface_(nullptr)
{
}

LiteProxyWindow::~LiteProxyWindow()
{
    if (winRequestor_) {
        delete winRequestor_;
        winRequestor_ = nullptr;
    }

    if (surface_) {
        delete surface_;
        surface_ = nullptr;
    }
}

int LiteProxyWindow::Init()
{
    return 0;
}

void LiteProxyWindow::Destroy()
{
}

void LiteProxyWindow::Show()
{
    if (winRequestor_ != nullptr) {
        winRequestor_->Show();
    }
}

void LiteProxyWindow::Hide()
{
    if (winRequestor_ != nullptr) {
        winRequestor_->Hide();
    }
}

void LiteProxyWindow::Resize(int16_t width, int16_t height)
{
    if (winRequestor_ != nullptr) {
        winRequestor_->Resize(width, height);
    }
}

void LiteProxyWindow::MoveTo(int16_t x, int16_t y)
{
    if (winRequestor_ != nullptr) {
        winRequestor_->MoveTo(x, y);
    }
}

void LiteProxyWindow::RaiseToTop()
{
    if (winRequestor_ != nullptr) {
        winRequestor_->RaiseToTop();
    }
}

void LiteProxyWindow::LowerToBottom()
{
    if (winRequestor_ != nullptr) {
        winRequestor_->LowerToBottom();
    }
}

ISurface* LiteProxyWindow::GetSurface()
{
    if (surface_ == nullptr) {
        Surface* surface = winRequestor_->GetSurface();
        if (surface == nullptr) {
            return nullptr;
        }
        surface_ = new LiteProxySurface(surface, winRequestor_);
    }
    return surface_;
}

int32_t LiteProxyWindow::GetWindowId()
{
    if (id_ != INVALID_WINDOW_ID) {
        return id_;
    }

    if (winRequestor_) {
        id_ = winRequestor_->GetWindowId();
        return id_;
    }
    return INVALID_WINDOW_ID;
}

void LiteProxyWindow::Update()
{
    if (winRequestor_ != nullptr) {
        winRequestor_->Update();
    }
}
}