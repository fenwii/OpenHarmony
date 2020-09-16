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

#include "components/ui_surface_view.h"
#include <string>
#include "draw/draw_rect.h"
#include "draw/draw_utils.h"
#include "graphic_log.h"
#include "surface_buffer.h"

namespace OHOS {
UISurfaceView::UISurfaceView()
{
    surface_ = Surface::CreateSurface();
    if (surface_ == nullptr) {
        GRAPHIC_LOGE("UISurfaceView::UISurfaceView surface create failed\n");
        return;
    }
    surface_->SetWidthAndHeight(GetWidth(), GetHeight());
    surface_->SetQueueSize(DEFAULT_QUEUE_SIZE);
    surface_->SetFormat(IMAGE_PIXEL_FORMAT_ARGB8888);
}

UISurfaceView::~UISurfaceView()
{
    if (surface_ != nullptr) {
        delete surface_;
        surface_ = nullptr;
    }
}

void UISurfaceView::SetPosition(int16_t x, int16_t y)
{
    UIView::SetPosition(x, y);
    if (surface_ == nullptr) {
        GRAPHIC_LOGE("UISurfaceView::SetPosition surface is null\n");
        return;
    }
    x = GetRect().GetLeft();
    y = GetRect().GetTop();
    surface_->SetUserData(REGION_POSITION_X, std::to_string(x));
    surface_->SetUserData(REGION_POSITION_Y, std::to_string(y));
}

void UISurfaceView::SetPosition(int16_t x, int16_t y, int16_t width, int16_t height)
{
    UIView::SetPosition(x, y, width, height);
    if (surface_ == nullptr) {
        GRAPHIC_LOGE("UISurfaceView::SetPosition surface is null\n");
        return;
    }
    x = GetRect().GetLeft();
    y = GetRect().GetTop();
    surface_->SetUserData(REGION_POSITION_X, std::to_string(x));
    surface_->SetUserData(REGION_POSITION_Y, std::to_string(y));
    surface_->SetUserData(REGION_WIDTH, std::to_string(width));
    surface_->SetUserData(REGION_HEIGHT, std::to_string(height));
}

void UISurfaceView::Resize(int16_t width, int16_t height)
{
    UIView::Resize(width, height);
    if (surface_ == nullptr) {
        GRAPHIC_LOGE("UISurfaceView::Resize surface is null\n");
        return;
    }
    surface_->SetUserData(REGION_WIDTH, std::to_string(width));
    surface_->SetUserData(REGION_HEIGHT, std::to_string(height));
}

void UISurfaceView::SetWidth(int16_t width)
{
    UIView::SetWidth(width);
    if (surface_ == nullptr) {
        GRAPHIC_LOGE("UISurfaceView::SetWidth surface is null\n");
        return;
    }
    surface_->SetUserData(REGION_WIDTH, std::to_string(width));
}

void UISurfaceView::SetHeight(int16_t height)
{
    UIView::SetHeight(height);
    if (surface_ == nullptr) {
        GRAPHIC_LOGE("UISurfaceView::SetHeight surface is null\n");
        return;
    }
    surface_->SetUserData(REGION_HEIGHT, std::to_string(height));
}


void UISurfaceView::SetX(int16_t x)
{
    UIView::SetX(x);
    if (surface_ == nullptr) {
        GRAPHIC_LOGE("UISurfaceView::SetX surface is null\n");
        return;
    }
    x = GetRect().GetLeft();
    surface_->SetUserData(REGION_POSITION_X, std::to_string(x));
}

void UISurfaceView::SetY(int16_t y)
{
    UIView::SetY(y);
    if (surface_ == nullptr) {
        GRAPHIC_LOGE("UISurfaceView::SetY surface is null\n");
        return;
    }
    y = GetRect().GetTop();
    surface_->SetUserData(REGION_POSITION_Y, std::to_string(y));
}

void UISurfaceView::SetVisible(bool visible)
{
    GRAPHIC_LOGI("UISurfaceView::SetVisible can not set visible\n");
}

Surface* UISurfaceView::GetSurface() const
{
    return surface_;
}

bool UISurfaceView::OnPreDraw(const Rect& invalidatedArea)
{
    // need fill transpant color
    return true;
}

void UISurfaceView::OnDraw(const Rect& invalidatedArea)
{
    Draw(invalidatedArea);
}

void UISurfaceView::Draw(const Rect& invalidatedArea)
{
    SurfaceBuffer* acquireBuffer = (surface_ != nullptr) ? surface_->AcquireBuffer() : nullptr;
    if (acquireBuffer != nullptr) {
        GRAPHIC_LOGE("UISurfaceView::Draw acquireBufferVirAddr=%p \n", acquireBuffer->GetVirAddr());
        // fill with buffer
        DrawUtils::GetInstance()->DrawWithBuffer(GetRect(), invalidatedArea,
            reinterpret_cast<const ColorType*>(acquireBuffer->GetVirAddr()));
        surface_->ReleaseBuffer(acquireBuffer);
    } else {
        // fill with transpant color
        DrawUtils::GetInstance()->DrawTranspantArea(GetRect(), invalidatedArea);
    }
}
} // namespace OHOS
