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

#ifndef GRAPHIC_LITE_SCREEN_DEVICE_H
#define GRAPHIC_LITE_SCREEN_DEVICE_H

#include "color.h"
#include "graphic_semaphore.h"
#include "graphic_assert.h"
#include "rect.h"
#if ENABLE_WINDOW
#include "surface.h"
#endif

namespace OHOS {
#if COLOR_DEPTH == 16
typedef Color16 ScreenBufferType;
#elif COLOR_DEPTH == 32 && ENABLE_BUFFER_RGBA == 0
typedef Color24 ScreenBufferType;
#elif COLOR_DEPTH == 32 && ENABLE_BUFFER_RGBA == 1
typedef Color32 ScreenBufferType;
#else
#error "Invalid COLOR_DEPTH, Set it to 16 or 32!"
#endif

#if ENABLE_WINDOW
struct AllocationInfo {
    uint8_t* virAddr;
    uint8_t* phyAddr;
    uint16_t width;
    uint16_t height;
    uint32_t stride;
    ImagePixelFormat pixelFormat;
};
#endif

/** @brief A semaphore for display buffer flushing. */
class FlushSem : public HeapBase {
public:
    /**
     * Constructor
     *
     * @param [in] isFlushing (Optional) True if is flushing, false if not.
     */
    FlushSem(bool isFlushing = false) : isFlushing_(isFlushing) {}

    /**
     * @brief Destructor
     */
    virtual ~FlushSem() {}

    /** Notifies the buffer is flushing end */
    void Notify()
    {
        isFlushing_ = false;
        sem_.notify();
    }

    /** Waits the buffer is flushing */
    void Wait()
    {
        while (isFlushing_) {
            sem_.wait();
        }
    }

    /** set the flag as flashing */
    void Flushing()
    {
        isFlushing_ = true;
    }

private:
    Semaphore sem_;
    bool isFlushing_;
};

/** @brief A display device. */
class ScreenDevice : public HeapBase {
public:
    /**
     * @brief Constructor
     */
    ScreenDevice() : DMA2DBlendState_(false), DMA2DFillState_(false) {}

    /**
     * @brief Destructor
     */
    virtual ~ScreenDevice() {}

    virtual void Flush(int16_t x1, int16_t y1, int16_t x2, int16_t y2, const ScreenBufferType* colorBuffer) {}

    virtual void Fill(int16_t x1, int16_t y1, int16_t x2, int16_t y2, const ColorType& color) {}

    void SetDMA2DBlendState(bool state)
    {
        DMA2DBlendState_ = state;
    }

    bool GetDMA2DBlendState() const
    {
        return DMA2DBlendState_;
    }

    virtual void DMA2DBlend(const uint8_t* src,
                            uint32_t destOffset,
                            uint32_t srcOffset,
                            uint32_t srcColorMode,
                            uint32_t destColorMode,
                            uint32_t width,
                            uint32_t height,
                            OpacityType opa,
                            uint32_t color,
                            uint8_t* dest) const
    {
    }

    void SetDMA2DFillState(bool state)
    {
        DMA2DFillState_ = state;
    }

    bool GetDMA2DFillState() const
    {
        return DMA2DFillState_;
    }

    virtual void DMA2DFill(uint32_t color,
                           uint32_t destOffset,
                           uint32_t destColorMode,
                           uint32_t width,
                           uint32_t height,
                           OpacityType opa,
                           uint8_t* dest) const
    {
    }

    virtual void SnapShot(uint32_t len, bool justCopy, uint8_t* dest) {}

    virtual void RenderFinish() {}

protected:
    bool DMA2DBlendState_;
    bool DMA2DFillState_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_SCREEN_DEVICE_H