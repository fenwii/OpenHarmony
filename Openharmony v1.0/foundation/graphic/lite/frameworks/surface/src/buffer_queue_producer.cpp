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

#include "buffer_queue_producer.h"

#include "buffer_common.h"
#include "buffer_manager.h"
#include "buffer_queue.h"
#include "surface_buffer_impl.h"

namespace OHOS {
const int32_t DEFAULT_IPC_SIZE = 100;

#ifndef _SURFACE_LINUX_
extern "C" {
typedef int32_t (*IpcMsgHandle)(BufferQueueProducer* product, void *ipcMsg, IpcIo *io);
};

static int32_t OnRequestBuffer(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    uint8_t isWaiting = IpcIoPopUint8(io);
    SurfaceBufferImpl* buffer = product->RequestBuffer(isWaiting);
    IpcIo reply;
    uint8_t tmpData[DEFAULT_IPC_SIZE];
    IpcIoInit(&reply, tmpData, DEFAULT_IPC_SIZE, 1);
    uint32_t ret = -1;
    if (buffer == nullptr) {
        GRAPHIC_LOGW("get buffer failed");
        IpcIoPushInt32(&reply, -1);
        ret = -1;
    } else {
        IpcIoPushInt32(&reply, 0);
        buffer->WriteToIpcIo(reply);
        ret = 0;
    }
    SendReply(nullptr, ipcMsg, &reply);
    return ret;
}

static int32_t OnFlushBuffer(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    IpcIo reply;
    uint8_t tmpData[DEFAULT_IPC_SIZE];
    IpcIoInit(&reply, tmpData, DEFAULT_IPC_SIZE, 1);
    SurfaceBufferImpl buffer;
    buffer.ReadFromIpcIo(*io);
    IpcIoPushInt32(&reply, product->EnqueueBuffer(buffer));
    SendReply(nullptr, ipcMsg, &reply);
    return 0;
}

static int32_t OnCancelBuffer(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    SurfaceBufferImpl buffer;
    buffer.ReadFromIpcIo(*io);
    product->Cancel(&buffer);
    IpcIo reply;
    uint8_t tmpData[DEFAULT_IPC_SIZE];
    IpcIoInit(&reply, tmpData, DEFAULT_IPC_SIZE, 1);
    IpcIoPushInt32(&reply, 0);
    SendReply(nullptr, ipcMsg, &reply);
    return 0;
}

static int32_t OnGetAttr(uint32_t attr, void *ipcMsg, IpcIo *io)
{
    IpcIo reply;
    uint8_t tmpData[DEFAULT_IPC_SIZE];
    IpcIoInit(&reply, tmpData, DEFAULT_IPC_SIZE, 1);
    IpcIoPushInt32(&reply, 0);
    IpcIoPushUint32(&reply, attr);
    SendReply(nullptr, ipcMsg, &reply);
    return 0;
}

static int32_t OnSendReply(void *ipcMsg, IpcIo *io)
{
    IpcIo reply;
    uint8_t tmpData[DEFAULT_IPC_SIZE];
    IpcIoInit(&reply, tmpData, DEFAULT_IPC_SIZE, 1);
    IpcIoPushInt32(&reply, 0);
    SendReply(nullptr, ipcMsg, &reply);
    return 0;
}

static int32_t OnSetQueueSize(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    uint32_t queueSize = IpcIoPopUint32(io);
    product->SetQueueSize(queueSize);
    return OnSendReply(ipcMsg, io);
}

static int32_t OnGetQueueSize(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    return OnGetAttr(product->GetQueueSize(), ipcMsg, io);
}

static int32_t OnSetWidthAndHeight(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    uint32_t width = IpcIoPopUint32(io);
    uint32_t height = IpcIoPopUint32(io);
    product->SetWidthAndHeight(width, height);
    return OnSendReply(ipcMsg, io);
}

static int32_t OnGetWidth(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    return OnGetAttr(product->GetWidth(), ipcMsg, io);
}

static int32_t OnGetHeight(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    return OnGetAttr(product->GetHeight(), ipcMsg, io);
}

static int32_t OnSetFormat(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    uint32_t format = IpcIoPopUint32(io);
    product->SetFormat(format);
    return OnSendReply(ipcMsg, io);
}

static int32_t OnGetFormat(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    return OnGetAttr(product->GetFormat(), ipcMsg, io);
}

static int32_t OnSetStrideAlignment(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    uint32_t strideAlignment = IpcIoPopUint32(io);
    product->SetStrideAlignment(strideAlignment);
    return OnSendReply(ipcMsg, io);
}

static int32_t GetStrideAlignment(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    return OnGetAttr(product->GetStrideAlignment(), ipcMsg, io);
}

static int32_t OnGetStride(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    return OnGetAttr(product->GetStride(), ipcMsg, io);
}

static int32_t OnSetSize(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    uint32_t size = IpcIoPopUint32(io);
    product->SetSize(size);
    return OnSendReply(ipcMsg, io);
}

static int32_t OnGetSize(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    return OnGetAttr(product->GetSize(), ipcMsg, io);
}

static int32_t OnSetUsage(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    uint32_t usage = IpcIoPopUint32(io);
    product->SetUsage(usage);
    return OnSendReply(ipcMsg, io);
}

static int32_t OnGetUsage(BufferQueueProducer* product, void *ipcMsg, IpcIo *io)
{
    return OnGetAttr(product->GetUsage(), ipcMsg, io);
}

static IpcMsgHandle g_ipcMsgHandleList[] = {
    OnRequestBuffer,      // REQUEST_BUFFER
    OnFlushBuffer,        // FLUSH_BUSFFER
    OnCancelBuffer,       // CANCEL_BUFFER
    OnSetQueueSize,       // SET_QUEUE_SIZE
    OnGetQueueSize,       // GET_QUEUE_SIZE
    OnSetWidthAndHeight,  // SET_WIDTH_AND_HEIGHT
    OnGetWidth,           // GET_WIDTH
    OnGetHeight,          // GET_HEIGHT
    OnSetFormat,          // SET_FORMAT
    OnGetFormat,          // GET_FORMAT
    OnSetStrideAlignment, // SET_STRIDE_ALIGNMENT
    GetStrideAlignment,   // GET_STRIDE_ALIGNMENT
    OnGetStride,          // GET_STRIDE
    OnSetSize,            // SET_SIZE
    OnGetSize,            // GET_SIZE
    OnSetUsage,           // SET_USAGE
    OnGetUsage,           // GET_USAGE
};
#endif

BufferQueueProducer::BufferQueueProducer(BufferQueue* bufferQueue)
    : bufferQueue_(bufferQueue),
      consumerListener_(nullptr)
{
}
BufferQueueProducer::~BufferQueueProducer()
{
    if (consumerListener_ != nullptr) {
        consumerListener_ = nullptr;
    }
    if (bufferQueue_ != nullptr) {
        delete bufferQueue_;
        bufferQueue_ = nullptr;
    }
}

SurfaceBufferImpl* BufferQueueProducer::RequestBuffer(uint8_t wait)
{
    RETURN_VAL_IF_FAIL(bufferQueue_, nullptr);
    SurfaceBufferImpl* buffer = bufferQueue_->RequestBuffer(wait);
    return buffer;
}

int32_t BufferQueueProducer::EnqueueBuffer(SurfaceBufferImpl& buffer)
{
    RETURN_VAL_IF_FAIL(bufferQueue_, SURFACE_ERROR_INVAILD_PARAM);
    int32_t ret = bufferQueue_->FlushBuffer(buffer);
    if (ret == 0) {
        if (consumerListener_ != nullptr) {
            consumerListener_->OnBufferAvailable();
        }
    }
    return ret;
}

int32_t BufferQueueProducer::FlushBuffer(SurfaceBufferImpl* buffer)
{
    RETURN_VAL_IF_FAIL(bufferQueue_, SURFACE_ERROR_INVAILD_PARAM);
    BufferManager* manager = BufferManager::GetInstance();
    RETURN_VAL_IF_FAIL(manager, SURFACE_ERROR_NOT_READY);
    if (buffer->GetUsage() == BUFFER_CONSUMER_USAGE_HARDWARE_CONSUMER_CACHE) {
        int32_t ret = manager->FlushCache(*buffer);
        if (ret != 0) {
            GRAPHIC_LOGW("Flush buffer failed, ret=%d", ret);
            return ret;
        }
    }
    return EnqueueBuffer(*buffer);
}

void BufferQueueProducer::Cancel(SurfaceBufferImpl* buffer)
{
    RETURN_IF_FAIL(bufferQueue_);
    bufferQueue_->CancelBuffer(*buffer);
}

void BufferQueueProducer::SetQueueSize(uint8_t queueSize)
{
    RETURN_IF_FAIL(bufferQueue_);
    bufferQueue_->SetQueueSize(queueSize);
}

uint8_t BufferQueueProducer::GetQueueSize()
{
    RETURN_VAL_IF_FAIL(bufferQueue_, 0);
    return bufferQueue_->GetQueueSize();
}

void BufferQueueProducer::SetWidthAndHeight(uint32_t width, uint32_t height)
{
    RETURN_IF_FAIL(bufferQueue_);
    bufferQueue_->SetWidthAndHeight(width, height);
}

uint32_t BufferQueueProducer::GetWidth()
{
    RETURN_VAL_IF_FAIL(bufferQueue_, 0);
    return bufferQueue_->GetWidth();
}

uint32_t BufferQueueProducer::GetHeight()
{
    RETURN_VAL_IF_FAIL(bufferQueue_, 0);
    return bufferQueue_->GetHeight();
}

void BufferQueueProducer::SetFormat(uint32_t format)
{
    RETURN_IF_FAIL(bufferQueue_);
    bufferQueue_->SetFormat(format);
}

uint32_t BufferQueueProducer::GetFormat()
{
    RETURN_VAL_IF_FAIL(bufferQueue_, 0);
    return bufferQueue_->GetFormat();
}

void BufferQueueProducer::SetStrideAlignment(uint32_t stride)
{
    RETURN_IF_FAIL(bufferQueue_);
    bufferQueue_->SetStrideAlignment(stride);
}

uint32_t BufferQueueProducer::GetStrideAlignment()
{
    RETURN_VAL_IF_FAIL(bufferQueue_, 0);
    return bufferQueue_->GetStrideAlignment();
}

uint32_t BufferQueueProducer::GetStride()
{
    RETURN_VAL_IF_FAIL(bufferQueue_, 0);
    return bufferQueue_->GetStride();
}

void BufferQueueProducer::SetSize(uint32_t size)
{
    RETURN_IF_FAIL(bufferQueue_);
    bufferQueue_->SetSize(size);
}

uint32_t BufferQueueProducer::GetSize()
{
    RETURN_VAL_IF_FAIL(bufferQueue_, 0);
    return bufferQueue_->GetSize();
}

void BufferQueueProducer::SetUsage(uint32_t usage)
{
    RETURN_IF_FAIL(bufferQueue_);
    bufferQueue_->SetUsage(usage);
}

uint32_t BufferQueueProducer::GetUsage()
{
    RETURN_VAL_IF_FAIL(bufferQueue_, 0);
    return bufferQueue_->GetUsage();
}

void BufferQueueProducer::RegisterConsumerListener(IBufferConsumerListener& listener)
{
    consumerListener_ = &listener;
}

void BufferQueueProducer::UnregisterConsumerListener()
{
    consumerListener_ = nullptr;
}

#ifndef _SURFACE_LINUX_
int32_t BufferQueueProducer::OnIpcMsg(void *ipcMsg, IpcIo *io)
{
    if (ipcMsg == NULL || io == NULL) {
        GRAPHIC_LOGW("Invalid parameter, null pointer");
        return SURFACE_ERROR_INVAILD_PARAM;
    }
    uint32_t code;
    (void)GetCode(ipcMsg, &code);
    if (code >= MAX_REQUEST_CODE) {
        GRAPHIC_LOGW("Resquest code(%u) does not support.", code);
        FreeBuffer(nullptr, ipcMsg);
        return SURFACE_ERROR_INVAILD_REQUEST;
    }
    return g_ipcMsgHandleList[code](this, ipcMsg, io);
}
#endif

void BufferQueueProducer::SetUserData(const std::string& key, const std::string& value)
{
    bufferQueue_->SetUserData(key, value);
}

std::string BufferQueueProducer::GetUserData(const std::string& key)
{
    return bufferQueue_->GetUserData(key);
}
} // end namespace
