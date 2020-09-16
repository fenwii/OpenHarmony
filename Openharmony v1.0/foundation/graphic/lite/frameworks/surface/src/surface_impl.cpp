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
#include "surface_impl.h"
#include <unistd.h>
#include "buffer_client_producer.h"
#include "buffer_common.h"
#include "buffer_manager.h"
#include "buffer_queue_consumer.h"
#include "buffer_queue_producer.h"
#include "surface_buffer_impl.h"

namespace OHOS {
SurfaceImpl::SurfaceImpl()
    : consumer_(nullptr), producer_(nullptr), IsConsumer_(true)
{
#ifndef _SURFACE_LINUX_
    sid_ = {
        .handle = 0,
        .token = 0
    };
#endif
}

#ifndef _SURFACE_LINUX_
SurfaceImpl::SurfaceImpl(const SvcIdentity& sid)
    : sid_(sid), consumer_(nullptr), producer_(nullptr), IsConsumer_(false)
{
}
#endif

SurfaceImpl::~SurfaceImpl()
{
    if (consumer_ != nullptr) {
        delete consumer_;
        consumer_ = nullptr;
    }
    if (producer_ != nullptr) {
        delete producer_;
        producer_ = nullptr;
    }
}

bool SurfaceImpl::Init()
{
    if (!BufferManager::GetInstance()->Init()) {
        GRAPHIC_LOGE("Failed init buffer manager");
        return false;
    }
    if (IsConsumer_) {
        BufferQueue* bufferQueue = new BufferQueue();
        if (bufferQueue == nullptr) {
            GRAPHIC_LOGE("Surface consumer(buffer queue) init failed.");
            return false;
        }

        if (!bufferQueue->Init()) {
            GRAPHIC_LOGE("Buffer queue init failed.");
            delete bufferQueue;
            return false;
        }

        producer_ = new BufferQueueProducer(bufferQueue);
        if (producer_ == nullptr) {
            GRAPHIC_LOGE("Surface consumer(consumer) init failed.");
            delete bufferQueue;
            return false;
        }
        consumer_ = new BufferQueueConsumer(*bufferQueue);
        if (consumer_ == nullptr) {
            GRAPHIC_LOGE("Surface consumer(consumer) init failed.");
            delete producer_;
            producer_ = nullptr;
            return false;
        }
#ifndef _SURFACE_LINUX_
    } else {
        producer_ = new BufferClientProducer(sid_);
        if (producer_ == nullptr) {
            GRAPHIC_LOGE("Surface producer init failed.");
            return false;
        }
#endif
    }
    return true;
}

void SurfaceImpl::SetWidthAndHeight(uint32_t width, uint32_t height)
{
    RETURN_IF_FAIL(producer_ != nullptr);
    RETURN_IF_FAIL(width > 0 && width <= SURFACE_MAX_WIDTH);
    RETURN_IF_FAIL(height > 0 && height <= SURFACE_MAX_HEIGHT);
    producer_->SetWidthAndHeight(width, height);
}

uint32_t SurfaceImpl::GetWidth()
{
    RETURN_VAL_IF_FAIL(producer_, 0);
    return producer_->GetWidth();
}

uint32_t SurfaceImpl::GetHeight()
{
    RETURN_VAL_IF_FAIL(producer_, 0);
    return producer_->GetHeight();
}

void SurfaceImpl::SetFormat(uint32_t format)
{
    RETURN_IF_FAIL(producer_);
    producer_->SetFormat(format);
}

uint32_t SurfaceImpl::GetFormat()
{
    RETURN_VAL_IF_FAIL(producer_, 0);
    return producer_->GetFormat();
}

void SurfaceImpl::SetStrideAlignment(uint32_t strideAlignment)
{
    RETURN_IF_FAIL(producer_);
    RETURN_IF_FAIL(strideAlignment >= SURFACE_MIN_STRIDE_ALIGNMENT && strideAlignment <= SURFACE_MAX_STRIDE_ALIGNMENT);
    producer_->SetStrideAlignment(strideAlignment);
}

uint32_t SurfaceImpl::GetStrideAlignment()
{
    RETURN_VAL_IF_FAIL(producer_, 0);
    return producer_->GetStrideAlignment();
}

uint32_t SurfaceImpl::GetStride()
{
    RETURN_VAL_IF_FAIL(producer_, 0);
    return producer_->GetStride();
}

void SurfaceImpl::SetSize(uint32_t size)
{
    RETURN_IF_FAIL(producer_);
    RETURN_IF_FAIL(size > 0 && size < SURFACE_MAX_SIZE);
    producer_->SetSize(size);
}

uint32_t SurfaceImpl::GetSize()
{
    RETURN_VAL_IF_FAIL(producer_, 0);
    return producer_->GetSize();
}

void SurfaceImpl::SetUsage(uint32_t usage)
{
    RETURN_IF_FAIL(producer_);
    RETURN_IF_FAIL(usage < BUFFER_CONSUMER_USAGE_MAX);
    producer_->SetUsage(usage);
}

uint32_t SurfaceImpl::GetUsage()
{
    uint32_t usage = producer_->GetUsage();
    return usage;
}

void SurfaceImpl::SetQueueSize(uint8_t queueSize)
{
    RETURN_IF_FAIL(producer_);
    RETURN_IF_FAIL(queueSize >= SURFACE_MIN_QUEUE_SIZE && queueSize <= SURFACE_MAX_QUEUE_SIZE);
    producer_->SetQueueSize(queueSize);
}

uint8_t SurfaceImpl::GetQueueSize()
{
    RETURN_VAL_IF_FAIL(producer_, SURFACE_ERROR_INVAILD_PARAM);
    uint8_t queueSize = producer_->GetQueueSize();
    return queueSize;
}

void SurfaceImpl::SetUserData(const std::string& key, const std::string& value)
{
    RETURN_IF_FAIL(producer_ != nullptr);
    producer_->SetUserData(key, value);
}

std::string SurfaceImpl::GetUserData(const std::string& key)
{
    RETURN_VAL_IF_FAIL(producer_ != nullptr, std::string());
    return producer_->GetUserData(key);
}

SurfaceBuffer* SurfaceImpl::RequestBuffer(uint8_t wait)
{
    RETURN_VAL_IF_FAIL(producer_, nullptr);
    return producer_->RequestBuffer(wait);
}

int32_t SurfaceImpl::FlushBuffer(SurfaceBuffer* buffer)
{
    RETURN_VAL_IF_FAIL(producer_, SURFACE_ERROR_INVAILD_PARAM);
    RETURN_VAL_IF_FAIL(buffer != nullptr, SURFACE_ERROR_INVAILD_PARAM);
    SurfaceBufferImpl* liteBuffer = reinterpret_cast<SurfaceBufferImpl*>(buffer);
    return producer_->FlushBuffer(liteBuffer);
}

SurfaceBuffer* SurfaceImpl::AcquireBuffer()
{
    RETURN_VAL_IF_FAIL(consumer_, nullptr);
    return consumer_->AcquireBuffer();
}

bool SurfaceImpl::ReleaseBuffer(SurfaceBuffer* buffer)
{
    RETURN_VAL_IF_FAIL(consumer_, false);
    SurfaceBufferImpl* liteBuffer = reinterpret_cast<SurfaceBufferImpl*>(buffer);
    return consumer_->ReleaseBuffer(*liteBuffer);
}

void SurfaceImpl::CancelBuffer(SurfaceBuffer* buffer)
{
    RETURN_IF_FAIL(producer_);
    RETURN_IF_FAIL(buffer != nullptr);
    SurfaceBufferImpl* liteBuffer = reinterpret_cast<SurfaceBufferImpl*>(buffer);
    producer_->Cancel(liteBuffer);
}

void SurfaceImpl::RegisterConsumerListener(IBufferConsumerListener& listener)
{
    RETURN_IF_FAIL(producer_);
    BufferQueueProducer* bufferQueueProducer = reinterpret_cast<BufferQueueProducer *>(producer_);
    bufferQueueProducer->RegisterConsumerListener(listener);
}

void SurfaceImpl::UnregisterConsumerListener()
{
    RETURN_IF_FAIL(producer_);
    BufferQueueProducer* bufferQueueProducer = reinterpret_cast<BufferQueueProducer *>(producer_);
    bufferQueueProducer->UnregisterConsumerListener();
}
#ifndef _SURFACE_LINUX_
void SurfaceImpl::WriteIoIpcIo(IpcIo& io)
{
    IpcIoPushSvc(&io, &sid_);
}

int32_t SurfaceImpl::DoIpcMsg(void* ipcMsg, IpcIo* io)
{
    RETURN_VAL_IF_FAIL(producer_, SURFACE_ERROR_INVAILD_PARAM);
    RETURN_VAL_IF_FAIL(ipcMsg != nullptr, SURFACE_ERROR_INVAILD_PARAM);
    RETURN_VAL_IF_FAIL(io != nullptr, SURFACE_ERROR_INVAILD_PARAM);
    BufferQueueProducer* bufferQueueProducer = reinterpret_cast<BufferQueueProducer*>(producer_);
    return bufferQueueProducer->OnIpcMsg(ipcMsg, io);
}

Surface* SurfaceImpl::GenericSurfaceByIpcIo(IpcIo& io)
{
    SvcIdentity* sid = IpcIoPopSvc(&io);
    if (sid != NULL) {
        SurfaceImpl* surface = new SurfaceImpl(*sid);
        if (surface != nullptr) {
            if (surface->Init()) {
                return surface;
            } else {
                GRAPHIC_LOGE("surface init failed");
                delete surface;
            }
        }
    }
    return nullptr;
}
#endif
} // namespace OHOS
