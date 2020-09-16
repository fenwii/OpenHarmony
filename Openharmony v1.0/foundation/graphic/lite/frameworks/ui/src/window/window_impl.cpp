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

#include "window/window_impl.h"
#include "client/iwindows_manager.h"
#include "common/screen_device_proxy.h"
#include "core/measure_manager.h"
#include "core/render_manager.h"
#include "graphic_log.h"

namespace OHOS {
WindowImpl::WindowImpl()
    : rootView_(nullptr), iWindow_(nullptr), isShow_(false), gfxAlloc_({})
{}

WindowImpl::~WindowImpl()
{
}


bool WindowImpl::Create(const WindowConfig& config)
{
    GRAPHIC_LOGI("Create");
    if (iWindow_ == nullptr) {
        config_ = config;
        LiteWinConfig liteConfig;
        liteConfig.rect = config.rect;
        liteConfig.pixelFormat = IMAGE_PIXEL_FORMAT_ARGB8888;
        liteConfig.opacity = OPA_OPAQUE;
        iWindow_ = IWindowsManager::GetInstance()->CreateWindow(liteConfig);
        if (iWindow_ == nullptr) {
            return false;
        }
    }
    return true;
}

void WindowImpl::Destory()
{
    Flush();
    if (iWindow_ != nullptr) {
        IWindowsManager::GetInstance()->RemoveWindow(iWindow_);
        iWindow_ = nullptr;
    }
}

void WindowImpl::AddToDisplay()
{
    GRAPHIC_LOGI("AddToDisplay");
    RenderManager::GetInstance().AddToDisplay(this);
}

void WindowImpl::RemoveFromDisplay()
{
    GRAPHIC_LOGI("RemoveFromDisplay");
    RenderManager::GetInstance().RemoveFromDisplay(this);
}

void WindowImpl::BindRootView(RootView* rootView)
{
    if (rootView == nullptr) {
        return;
    }
    UnbindRootView();
    GRAPHIC_LOGI("BindRootView");
    rootView_ = rootView;
    rootView_->boundWindow_ = this;
}

void WindowImpl::UnbindRootView()
{
    GRAPHIC_LOGI("UnbindRootView");
    if (rootView_ != nullptr) {
        rootView_->boundWindow_ = nullptr;
        rootView_ = nullptr;
    }
}

RootView* WindowImpl::GetRootView()
{
    return rootView_;
}

Rect WindowImpl::GetRect()
{
    return config_.rect;
}

void WindowImpl::Show()
{
    if (iWindow_ == nullptr) {
        return;
    }

    if (!isShow_) {
        isShow_ = true;
        MeasureManager::GetInstance().ReMeasureRect();
        Render();
        iWindow_->Show();
    }
}

void WindowImpl::Hide()
{
    if (iWindow_ == nullptr) {
        return;
    }

    if (isShow_) {
        isShow_ = false;
        iWindow_->Hide();
    }
}

void WindowImpl::MoveTo(int16_t x, int16_t y)
{
    GRAPHIC_LOGI("MoveTo");
    config_.rect.SetPosition(x, y);
    if (iWindow_ != nullptr) {
        iWindow_->MoveTo(x, y);
    }
}

void WindowImpl::Resize(int16_t width, int16_t height)
{
    GRAPHIC_LOGI("Resize");
    if (width == config_.rect.GetWidth() && height == config_.rect.GetHeight()) {
        return;
    }

    config_.rect.Resize(width, height);
    Flush();
    if (iWindow_ != nullptr) {
        iWindow_->Resize(width, height);
    }

    if (rootView_ != nullptr) {
        rootView_->Invalidate();
    }
}

void WindowImpl::RaiseToTop()
{
    GRAPHIC_LOGI("RaiseToTop");
    if (iWindow_ != nullptr) {
        iWindow_->RaiseToTop();
    }
}

void WindowImpl::LowerToBottom()
{
    GRAPHIC_LOGI("LowerToBottom");
    if (iWindow_ != nullptr) {
        iWindow_->LowerToBottom();
    }
}

void WindowImpl::Render()
{
    UpdateHalDisplayBuffer();
    if (gfxAlloc_.virAddr == nullptr) {
        GRAPHIC_LOGE("window buffer is null, windId=%d", GetWindowId());
        return;
    }

    if (rootView_ != nullptr) {
        rootView_->Render();
    }
}

void WindowImpl::Update()
{
    if (iWindow_ == nullptr) {
        return;
    }
    iWindow_->Update();
}

int32_t WindowImpl::GetWindowId()
{
    if (iWindow_ != nullptr) {
        return iWindow_->GetWindowId();
    } else {
        GRAPHIC_LOGE("iwindow is null!");
        return INVALID_WINDOW_ID;
    }
}

void WindowImpl::Flush()
{
    GRAPHIC_LOGI("Flush");
    if (iWindow_ == nullptr) {
        return;
    }
    ISurface *surface = iWindow_->GetSurface();
    if (surface != nullptr) {
        surface->Unlock();
        gfxAlloc_ = {};
    }
}

void WindowImpl::UpdateHalDisplayBuffer()
{
    if (gfxAlloc_.virAddr == nullptr && iWindow_ != nullptr) {
        ISurface* surface = iWindow_->GetSurface();
        if (surface == nullptr) {
            return;
        }
        surface->Lock((void**)&gfxAlloc_.virAddr, (void**)&gfxAlloc_.phyAddr, &gfxAlloc_.stride);
    }
    AllocationInfo& gfxAlloc = ScreenDeviceProxy::GetInstance()->GetAllocationInfo();
    gfxAlloc.phyAddr = gfxAlloc_.phyAddr;
    gfxAlloc.virAddr = gfxAlloc_.virAddr;
    gfxAlloc.stride = gfxAlloc_.stride;
    gfxAlloc.width = config_.rect.GetWidth();
    gfxAlloc.height = config_.rect.GetHeight();
    gfxAlloc.pixelFormat = IMAGE_PIXEL_FORMAT_ARGB8888;
}
}