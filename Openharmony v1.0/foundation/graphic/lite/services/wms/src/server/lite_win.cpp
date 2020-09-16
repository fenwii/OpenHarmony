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

#include "server/lite_win.h"

#include "gfx_engines.h"
#include "graphic_locker.h"
#include "graphic_log.h"
#include "securec.h"

#include "server/lite_wm.h"

namespace OHOS {
static const int16_t DEFAULT_QUEUE_SIZE = 2;

LiteWindow::LiteWindow(const LiteWinConfig& config)
    : id_(INVALID_WINDOW_ID), isShow_(false), config_(config), surface_(nullptr),
      backBuf_(nullptr), sid_({}), needUnregister_(false)
{
    pthread_mutex_init(&backBufMutex_, NULL);
    id_ = LiteWM::GetInstance()->GetUniqueWinId();
}

LiteWindow::~LiteWindow()
{
    if (needUnregister_) {
        GRAPHIC_LOGI("UnRegisteIpcCallback");
        UnRegisteIpcCallback(sid_);
    }

    if (surface_) {
        if (backBuf_) {
            surface_->CancelBuffer(backBuf_);
        }
        delete surface_;
        surface_ = nullptr;
    }

    LiteWM::GetInstance()->RecycleWinId(id_);
}

bool LiteWindow::CreateSurface()
{
    if (surface_ == nullptr) {
        surface_ = Surface::CreateSurface();
        if (surface_ == nullptr) {
            GRAPHIC_LOGE("CreateSurface failed!");
            return false;
        }
        surface_->SetWidthAndHeight(config_.rect.GetWidth(), config_.rect.GetHeight());
        surface_->SetQueueSize(DEFAULT_QUEUE_SIZE);
        surface_->SetFormat(config_.pixelFormat);
        surface_->SetUsage(BUFFER_CONSUMER_USAGE_HARDWARE);

        if (backBuf_ == nullptr) {
            backBuf_ = surface_->RequestBuffer();
        }
    }
    return true;
}

void LiteWindow::ReleaseSurface()
{
}

void LiteWindow::ResizeSurface(int16_t width, int16_t height)
{
    if (surface_ == nullptr) {
        return;
    }

    GraphicLocker lock(backBufMutex_);
    if (backBuf_ != nullptr) {
        surface_->CancelBuffer(backBuf_);
    }
    surface_->SetWidthAndHeight(width, height);
    backBuf_ = surface_->RequestBuffer();
}

void LiteWindow::Update(Rect rect)
{
    LiteWM::GetInstance()->UpdateWindow(this, rect);
}

void LiteWindow::UpdateBackBuf()
{
    GraphicLocker lock(backBufMutex_);
    if (surface_ == nullptr || backBuf_ == nullptr) {
        return;
    }

    SurfaceBuffer* acquireBuffer = surface_->AcquireBuffer();
    if (acquireBuffer != nullptr) {
        void* acquireBufVirAddr = acquireBuffer->GetVirAddr();
        void* backBufVirAddr = backBuf_->GetVirAddr();
        if (acquireBufVirAddr != nullptr && backBufVirAddr != nullptr) {
            GRAPHIC_LOGI("memcpy, backBuf size=%d, acquireBuffer size=%d",
                backBuf_->GetSize(), acquireBuffer->GetSize());
            if (memcpy_s(backBufVirAddr, backBuf_->GetSize(),
                acquireBufVirAddr, acquireBuffer->GetSize()) != EOK) {
                GRAPHIC_LOGE("memcpy_s error!");
            }
            GRAPHIC_LOGI("memcpy end");
        }
        surface_->ReleaseBuffer(acquireBuffer);
    }
}

static uint16_t ARGB8888ToArgb1555(ColorType color)
{
    union {
        struct {
            uint16_t blue : 5;
            uint16_t green : 5;
            uint16_t red : 5;
            uint16_t alpha : 1;
        };
        uint16_t full;
    } ret;
    ret.alpha = color.alpha;
    ret.red = color.red >> 3;
    ret.green = color.green >> 3;
    ret.blue = color.blue >> 3;
    return ret.full;
}

void LiteWindow::Flush(const Rect& srcRect, const LiteSurfaceData* layerData, int16_t dx, int16_t dy)
{
    GraphicLocker lock(backBufMutex_);
#if ENABLE_HARDWARE_ACCELERATION
    uintptr_t phyaddr = backBuf_->GetPhyAddr();
    if (phyaddr) {
        LiteSurfaceData srcData;
        srcData.width = surface_->GetWidth();
        srcData.height = surface_->GetHeight();
        srcData.pixelFormat = (ImagePixelFormat)surface_->GetFormat();
        srcData.stride = surface_->GetStride();
        srcData.phyAddr = (uint8_t*)phyaddr;
        GRAPHIC_LOGD("Hardware composite, width=%d, height=%d, pixelFormat=%d, stride=%d",
            srcData.width, srcData.height, srcData.pixelFormat, srcData.stride);
        if (GfxEngines::GetInstance()->GfxBlit(srcData, srcRect, *layerData, dx, dy)) {
            return;
        }
    }
#endif

    int x1 = srcRect.GetLeft();
    int y1 = srcRect.GetTop();
    int x2 = srcRect.GetRight();
    int y2 = srcRect.GetBottom();
    uint8_t* srcBuf = (uint8_t*)backBuf_->GetVirAddr();
    uint8_t* dstBuf = layerData->virAddr + dy * layerData->stride;
    GRAPHIC_LOGD("Software composite, {%d,%d,%d,%d}", x1, y1, x2, y2);

    uint32_t stride = surface_->GetStride();
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            ColorType* tmp = (ColorType*)(srcBuf + y * stride) + x;
            *((uint16_t*)dstBuf + dx + x - x1) = ARGB8888ToArgb1555(*tmp);
        }
        dstBuf += layerData->stride;
    }
}

Surface* LiteWindow::GetSurface()
{
    return surface_;
}

void LiteWindow::MoveTo(int16_t x, int16_t y)
{
    GRAPHIC_LOGI("{%d,%d}=>{%d,%d}", config_.rect.GetLeft(), config_.rect.GetTop(), x, y);
    LiteWM::GetInstance()->UpdateWindowRegion(this, config_.rect);
    config_.rect.SetPosition(x, y);
    LiteWM::GetInstance()->UpdateWindowRegion(this, config_.rect);
}

void LiteWindow::Resize(int16_t width, int16_t height)
{
    GRAPHIC_LOGI("{%d,%d}=>{%d,%d}", config_.rect.GetWidth(), config_.rect.GetHeight(), width, height);
    config_.rect.Resize(width, height);
    ResizeSurface(width, height);
}
}