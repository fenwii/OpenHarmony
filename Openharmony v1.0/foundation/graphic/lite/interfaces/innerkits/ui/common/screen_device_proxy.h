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

#ifndef GRAPHIC_LITE_SCREEN_DEVICE_PROXY_H
#define GRAPHIC_LITE_SCREEN_DEVICE_PROXY_H

#include "dock/screen_device.h"
#include "color.h"
#include "graphic_semaphore.h"
#include "graphic_assert.h"
#include "rect.h"
#if ENABLE_WINDOW
#include "surface.h"
#endif

namespace OHOS {
/** @brief A display device proxy */
class ScreenDeviceProxy : public HeapBase {
public:
    static ScreenDeviceProxy* GetInstance()
    {
        static ScreenDeviceProxy instance;
        return &instance;
    }

    void SetDevice(ScreenDevice* device)
    {
        device_ = device;
    }

    ScreenDevice* GetDevice()
    {
        return device_;
    }

    void Flush();

    void OnFlushReady();

    void OnRenderFinish();

#if ENABLE_FRAME_BUFFER
    void SetFramebuffer(ScreenBufferType* addr, uint16_t width)
    {
        frameBufferAddr_ = addr;
        frameBufferWidth_ = width;
    }
#endif

#if ENABLE_WINDOW
    AllocationInfo& GetAllocationInfo()
    {
        return gfxAlloc_;
    }
#endif

    uint16_t GetBufferWidth() const
    {
#if ENABLE_FRAME_BUFFER
        return frameBufferWidth_;
#elif ENABLE_WINDOW
        return gfxAlloc_.stride / sizeof(ColorType);
#else
        return bufferRect_.GetWidth();
#endif
    }

    Rect& GetBufferRect()
    {
        return bufferRect_;
    }

    void SetScreenSize(uint16_t width, uint16_t height);
    uint16_t GetScreenWidth() const
    {
        return width_;
    }

    uint16_t GetScreenHeight() const
    {
        return height_;
    }

    uint32_t GetScreenArea() const
    {
        return width_ * height_;
    }

    ScreenBufferType* GetBuffer()
    {
        flush_.Wait();
#if ENABLE_FRAME_BUFFER
        int32_t offset = bufferRect_.GetTop() * frameBufferWidth_ + bufferRect_.GetLeft();
        return frameBufferAddr_ + offset;
#elif ENABLE_WINDOW
        return (ScreenBufferType*)gfxAlloc_.virAddr;
#else
        return buffer_;
#endif
    }

private:
    ScreenDeviceProxy() : device_(nullptr), flush_(false), width_(HORIZONTAL_RESOLUTION), height_(VERTICAL_RESOLUTION)
    {
#if ENABLE_FRAME_BUFFER
        frameBufferAddr_ = nullptr;
        frameBufferWidth_ = 0;
#endif
#if ENABLE_WINDOW
        gfxAlloc_ = {0};
#endif
        buffer_ = nullptr;
    }
    virtual ~ScreenDeviceProxy() {}

    ScreenDeviceProxy(const ScreenDeviceProxy&) = delete;
    ScreenDeviceProxy& operator=(const ScreenDeviceProxy&) = delete;
    ScreenDeviceProxy(ScreenDeviceProxy&&) = delete;
    ScreenDeviceProxy& operator=(ScreenDeviceProxy&&) = delete;

    ScreenDevice* device_;
    FlushSem flush_;
    uint16_t width_;
    uint16_t height_;
    ScreenBufferType* buffer_;
    Rect bufferRect_;

#if ENABLE_FRAME_BUFFER
    ScreenBufferType* frameBufferAddr_;
    uint16_t frameBufferWidth_;
#endif

#if ENABLE_WINDOW
    AllocationInfo gfxAlloc_;
#endif
};
} // namespace OHOS
#endif // GRAPHIC_LITE_SCREEN_DEVICE_PROXY_H