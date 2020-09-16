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

#include "client/lite_proxy_surface.h"
#include "graphic_log.h"

namespace OHOS {
LiteProxySurface::LiteProxySurface(Surface* surface, LiteWinRequestor* par)
    : buffer_(nullptr), surface_(surface)
{
}

LiteProxySurface::~LiteProxySurface()
{
}

void LiteProxySurface::Lock(void** buf, void** phyMem, uint32_t* strideLen)
{
    GRAPHIC_LOGI("Lock");
    if (surface_ == nullptr) {
        return;
    }

    if (buffer_ == nullptr) {
        buffer_ = surface_->RequestBuffer();
        if (buffer_ == nullptr) {
            GRAPHIC_LOGE("buffer_ is null!");
            *buf = nullptr;
            *phyMem = nullptr;
            *strideLen = 0;
            return;
        }
    }
    *buf = buffer_->GetVirAddr();
    uintptr_t phyAddr = buffer_->GetPhyAddr();
    *phyMem = (void*)phyAddr;
    *strideLen = surface_->GetStride();
    GRAPHIC_LOGI("strideLen=%d", *strideLen);
}

void LiteProxySurface::Unlock()
{
    if (surface_ == nullptr || buffer_ == nullptr) {
        return;
    }

    GRAPHIC_LOGI("Unlock");
    surface_->FlushBuffer(buffer_);
    buffer_ = nullptr;
}
}