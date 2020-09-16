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

#include "common/screen_device_proxy.h"
#include "graphic_log.h"
#include "securec.h"

namespace OHOS {
#if ENABLE_FRAME_BUFFER
void ScreenDeviceProxy::Flush() {}
#else
void ScreenDeviceProxy::Flush()
{
    flush_.Flushing();

    if (device_ != nullptr) {
#if ENABLE_WINDOW
        device_->Flush(bufferRect_.GetLeft(), bufferRect_.GetTop(), bufferRect_.GetRight(), bufferRect_.GetBottom(),
            (ScreenBufferType*)gfxAlloc_.virAddr);
#else
        device_->Flush(bufferRect_.GetLeft(), bufferRect_.GetTop(), bufferRect_.GetRight(), bufferRect_.GetBottom(),
            buffer_);
#endif
    }
}
#endif

void ScreenDeviceProxy::OnFlushReady()
{
    flush_.Notify();
}

void ScreenDeviceProxy::OnRenderFinish()
{
    if (device_ != nullptr) {
        device_->RenderFinish();
    }
}

void ScreenDeviceProxy::SetScreenSize(uint16_t width, uint16_t height)
{
    if (width == 0 || height == 0) {
        GRAPHIC_LOGE("screen size can not be zero.");
        ASSERT(0);
        return;
    }
    width_ = width;
    height_ = height;
#if !ENABLE_WINDOW
    if (buffer_ != nullptr) {
        UIFree(buffer_);
    }
    uint32_t bufSize = width * height * sizeof(ScreenBufferType);
    buffer_ = static_cast<ScreenBufferType*>(UIMalloc(bufSize));
    if (buffer_ == nullptr) {
        GRAPHIC_LOGE("screen buffer malloc failed.");
        ASSERT(0);
    }
    if (memset_s(buffer_, bufSize, 0, bufSize) != EOK) {
        GRAPHIC_LOGE("screen buffer memset failed.");
        UIFree(reinterpret_cast<void*>(buffer_));
        buffer_ = nullptr;
        ASSERT(0);
    }
#endif
}
} // namespace OHOS