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

#include "buffer_queue.h"

#include <list>
#include <string>

#include "buffer_common.h"
#include "buffer_manager.h"

namespace OHOS {
const int32_t BITS_PER_BYTE = 8;
const int32_t BUFFER_STRIDE_ALIGNMENT_DEFAULT = 4;
const uint8_t BUFFER_QUEUE_SIZE_DEFAULT = 1;
const uint8_t BUFFER_QUEUE_SIZE_MAX = 10;
const int32_t BUFFER_CONSUMER_USAGE_DEFAULT = BUFFER_CONSUMER_USAGE_SORTWARE;
const uint8_t USER_DATA_COUNT = 100;

BufferQueue::BufferQueue()
    : width_(0),
      height_(0),
      format_(IMAGE_PIXEL_FORMAT_RGB565),
      stride_(0),
      usage_(BUFFER_CONSUMER_USAGE_DEFAULT),
      size_(0),
      queueSize_(BUFFER_QUEUE_SIZE_DEFAULT),
      strideAlignment_(BUFFER_STRIDE_ALIGNMENT_DEFAULT),
      attachCount_(0)
{
}

BufferQueue::~BufferQueue()
{
    pthread_mutex_lock(&lock_);
    freeList_.clear();
    dirtyList_.clear();
    std::list<SurfaceBufferImpl *>::iterator iterBuffer;
    for (iterBuffer = allBuffers_.begin(); iterBuffer != allBuffers_.end(); ++iterBuffer) {
        SurfaceBufferImpl* tmpBuffer = *iterBuffer;
        BufferManager* bufferManager = BufferManager::GetInstance();
        if (bufferManager == nullptr) {
            continue;
        }
        bufferManager->FreeBuffer(tmpBuffer);
    }
    allBuffers_.clear();
    pthread_mutex_unlock(&lock_);
    pthread_cond_destroy(&freeCond_);
    pthread_mutex_destroy(&lock_);
}

bool BufferQueue::Init()
{
    if (pthread_mutex_init(&lock_, NULL)) {
        GRAPHIC_LOGE("Failed init mutex");
        return false;
    }
    if (pthread_cond_init(&freeCond_, NULL)) {
        GRAPHIC_LOGE("Failed init cond");
        pthread_mutex_destroy(&lock_);
        return false;
    }
    return true;
}

void BufferQueue::InitParam()
{
    UpdatePlaneInfo();
}

void BufferQueue::UpdatePlaneInfo()
{
    if (!IsFormatSupported(format_)) {
        GRAPHIC_LOGW("The format(%{public}u) is not suppored", format);
        return;
    }
    uint8_t planeCount = GetPlaneCount(format_);
    uint32_t size = 0;
    uint32_t offset = 0;
    uint32_t stride = 0;
    size_ = 0;
    for (uint8_t i = 0; i < planeCount; i++) {
        QueryEachPlaneInfo(i, size, offset, stride);
        planes_[i].size = size;
        planes_[i].offset = offset;
        planes_[i].stride = stride;
        size_ += size;
    }
    stride_ = planes_[0].stride;
}

uint8_t BufferQueue::GetPlaneCount(uint32_t format)
{
    uint8_t count = 0;
    switch (format) {
        case IMAGE_PIXEL_FORMAT_ARGB8888:
        case IMAGE_PIXEL_FORMAT_RGB888:
        case IMAGE_PIXEL_FORMAT_RGB565:
        case IMAGE_PIXEL_FORMAT_ARGB1555:
        case IMAGE_PIXEL_FORMAT_AYUV:
        case IMAGE_PIXEL_FORMAT_UYVY:
        case IMAGE_PIXEL_FORMAT_VYUY:
        case IMAGE_PIXEL_FORMAT_YUYV:
        case IMAGE_PIXEL_FORMAT_YVYU:
            count = IMAGE_PIXEL_FORMAT_PLANE_COUNT_RGB;
            break;
        case IMAGE_PIXEL_FORMAT_NV12:
        case IMAGE_PIXEL_FORMAT_NV21:
        case IMAGE_PIXEL_FORMAT_NV16:
        case IMAGE_PIXEL_FORMAT_NV61:
            count = IMAGE_PIXEL_FORMAT_PLANE_COUNT_YUVSPXX;
            break;
        case IMAGE_PIXEL_FORMAT_YUV410:
        case IMAGE_PIXEL_FORMAT_YUV411:
        case IMAGE_PIXEL_FORMAT_YUV420:
        case IMAGE_PIXEL_FORMAT_YUV422:
        case IMAGE_PIXEL_FORMAT_YUV444:
        case IMAGE_PIXEL_FORMAT_YVU410:
        case IMAGE_PIXEL_FORMAT_YVU411:
        case IMAGE_PIXEL_FORMAT_YVU420:
        case IMAGE_PIXEL_FORMAT_YVU422:
        case IMAGE_PIXEL_FORMAT_YVU444:
            count = IMAGE_PIXEL_FORMAT_PLANE_COUNT_YUV4XX;
            break;
        default:
            GRAPHIC_LOGI("The format is not supported.");
            break;
    }
    return count;
}

bool BufferQueue::IsFormatSupported(uint32_t format)
{
    bool isSupported = false;
    switch (format) {
        case IMAGE_PIXEL_FORMAT_RGB565:
        case IMAGE_PIXEL_FORMAT_RGB888:
        case IMAGE_PIXEL_FORMAT_ARGB1555:
        case IMAGE_PIXEL_FORMAT_ARGB8888:
        case IMAGE_PIXEL_FORMAT_NV21:
            isSupported = true;
            break;
        default:
            break;
    }
    return isSupported;
}

uint32_t BufferQueue::Align(uint32_t value, uint32_t alignment)
{
    return ((value + alignment - 1) / alignment) * alignment;
}

void BufferQueue::QueryEachPlaneInfo(uint32_t planeIndex, uint32_t& size, uint32_t& offset, uint32_t& stride)
{
    int32_t bitPerPixel;
    int32_t tmpOffset = 0;
    int32_t tmpStride = 0;
    int32_t tmpSize = 0;
    switch (format_) {
        case IMAGE_PIXEL_FORMAT_RGB565:
        case IMAGE_PIXEL_FORMAT_ARGB1555:
            bitPerPixel = 16; // 16 bits/Pixel these pixel formats.
            tmpOffset = 0;
            tmpStride = Align(width_ * bitPerPixel / BITS_PER_BYTE, strideAlignment_);
            tmpSize = tmpStride * height_;
            break;
        case IMAGE_PIXEL_FORMAT_RGB888:
            bitPerPixel = 24; // 24 bits/Pixel these pixel formats.
            tmpOffset = 0;
            tmpStride = Align(width_ * bitPerPixel / BITS_PER_BYTE, strideAlignment_);
            tmpSize = tmpStride * height_;
            break;
        case IMAGE_PIXEL_FORMAT_ARGB8888:
            bitPerPixel = 32; // 32 bits/Pixel these pixel formats.
            tmpOffset = 0;
            tmpStride = Align(width_ * bitPerPixel / BITS_PER_BYTE, strideAlignment_);
            tmpSize = tmpStride * height_;
            break;
        case IMAGE_PIXEL_FORMAT_NV12:
        case IMAGE_PIXEL_FORMAT_NV21:
            bitPerPixel = 12; // 12 bits/Pixel these pixel formats.
            tmpOffset = 0;
            tmpStride = Align(width_ * bitPerPixel / BITS_PER_BYTE, strideAlignment_);
            tmpSize = tmpStride * height_;
            if (planeIndex == 0) {
                break;
            }
            tmpOffset = tmpSize;
            tmpSize = tmpStride * (height_ / 2); // NV12 and NV21 format second plane size need to divide by 2.
            break;
        default:
            break;
    }
    offset = tmpOffset;
    stride = tmpStride;
    size = tmpSize;
}

void BufferQueue::NeedAttach()
{
    if (queueSize_ == attachCount_) {
        GRAPHIC_LOGI("has alloced %d buffer, could not alloc more.", allBuffers_.size());
        return;
    }
    if (size_ == 0 && isValidAttr(width_, height_, format_, strideAlignment_) != SURFACE_ERROR_OK) {
        GRAPHIC_LOGI("Invalid Attr.");
        return;
    }
    if (size_ == 0) {
        InitParam();
    }
    BufferManager* bufferManager = BufferManager::GetInstance();
    RETURN_IF_FAIL(bufferManager);
    SurfaceBufferImpl *buffer = bufferManager->AllocBuffer(size_, usage_);
    if (buffer == nullptr) {
        GRAPHIC_LOGI("BufferManager alloc memory failed ");
        return;
    }
    attachCount_++;
    freeList_.push_back(buffer);
    allBuffers_.push_back(buffer);
}

bool BufferQueue::CanRequest(uint8_t wait)
{
    bool res = true;
    if (!freeList_.empty()) {
        res = true;
        goto ERROR;
    }
    if (attachCount_ < queueSize_) {
        NeedAttach();
        res = true;
        if (freeList_.empty()) {
            GRAPHIC_LOGI("no buffer in freeQueue for dequeue.");
            res = false;
        }
        goto ERROR;
    }
    if (wait) {
        pthread_cond_wait(&freeCond_, &lock_);
        res = true;
    }
ERROR:
    return res;
}

SurfaceBufferImpl* BufferQueue::RequestBuffer(uint8_t wait)
{
    SurfaceBufferImpl *buffer = nullptr;
    pthread_mutex_lock(&lock_);
    if (!CanRequest(wait)) {
        GRAPHIC_LOGI("No buffer can request now.");
        goto ERROR;
    }
    buffer = freeList_.front();
    if (buffer == nullptr) {
        GRAPHIC_LOGI("freeQueue pop buffer failed.");
        goto ERROR;
    }
    freeList_.pop_front();
    buffer->SetState(BUFFER_STATE_REQUEST);
ERROR:
    pthread_mutex_unlock(&lock_);
    return buffer;
}

SurfaceBufferImpl* BufferQueue::GetBuffer(const SurfaceBufferImpl& buffer)
{
    std::list<SurfaceBufferImpl *>::iterator iterBuffer;
    for (iterBuffer = allBuffers_.begin(); iterBuffer != allBuffers_.end(); ++iterBuffer) {
        SurfaceBufferImpl *tmpBuffer = *iterBuffer;
        if (tmpBuffer->equals(buffer)) {
            return tmpBuffer;
        }
    }
    return nullptr;
}

int32_t BufferQueue::FlushBuffer(SurfaceBufferImpl& buffer)
{
    pthread_mutex_lock(&lock_);
    SurfaceBufferImpl *tmpBuffer = GetBuffer(buffer);
    if (tmpBuffer == nullptr || tmpBuffer->GetState() != BUFFER_STATE_REQUEST) {
        GRAPHIC_LOGI("Buffer is not existed or state invailed.");
        pthread_mutex_unlock(&lock_);
        return SURFACE_ERROR_BUFFER_NOT_EXISTED;
    }
    dirtyList_.push_back(tmpBuffer);
    if (&buffer != tmpBuffer) {
        tmpBuffer->CopyExtraData(buffer);
    }
    tmpBuffer->SetState(BUFFER_STATE_FLUSH);
    pthread_mutex_unlock(&lock_);
    return 0;
}

SurfaceBufferImpl* BufferQueue::AcquireBuffer()
{
    pthread_mutex_lock(&lock_);
    if (dirtyList_.empty()) {
        pthread_mutex_unlock(&lock_);
        GRAPHIC_LOGD("dirty queue is empty.");
        return nullptr;
    }
    SurfaceBufferImpl *buffer = dirtyList_.front();
    if (buffer == nullptr) {
        pthread_mutex_unlock(&lock_);
        GRAPHIC_LOGW("dirty queue pop buffer failed.");
        return nullptr;
    }
    buffer->SetState(BUFFER_STATE_ACQUIRE);
    dirtyList_.pop_front();
    pthread_mutex_unlock(&lock_);
    return buffer;
}
void BufferQueue::Detach(SurfaceBufferImpl *buffer)
{
    if (buffer == nullptr) {
        GRAPHIC_LOGW("Detach buffer failed, buffer is null.");
        return;
    }
    freeList_.remove(buffer);
    dirtyList_.remove(buffer);
    allBuffers_.remove(buffer);
    BufferManager* bufferManager = BufferManager::GetInstance();
    if (bufferManager != nullptr) {
        bufferManager->FreeBuffer(buffer);
    }
}

bool BufferQueue::ReleaseBuffer(const SurfaceBufferImpl& buffer)
{
    return ReleaseBuffer(buffer, BUFFER_STATE_ACQUIRE) == SURFACE_ERROR_OK;
}

int32_t BufferQueue::CancelBuffer(const SurfaceBufferImpl& buffer)
{
    return ReleaseBuffer(buffer, BUFFER_STATE_REQUEST);
}

int32_t BufferQueue::ReleaseBuffer(const SurfaceBufferImpl& buffer, BufferState state)
{
    int32_t ret = 0;
    pthread_mutex_lock(&lock_);
    SurfaceBufferImpl *tmpBuffer = GetBuffer(buffer);
    if (tmpBuffer == nullptr || tmpBuffer->GetState() != state) {
        GRAPHIC_LOGI("Buffer is not existed or state invailed.");
        ret = SURFACE_ERROR_BUFFER_NOT_EXISTED;
        goto ERROR;
    }

    if (tmpBuffer->GetDeletePending() == 1) {
        GRAPHIC_LOGI("Release the buffer which state is deletePending.");
        Detach(tmpBuffer);
        ret = SURFACE_ERROR_OK;
        goto ERROR;
    }

    if (allBuffers_.size() > queueSize_) {
        GRAPHIC_LOGI("Release the buffer: alloc buffer count is more than max queue count.");
        attachCount_--;
        Detach(tmpBuffer);
        ret = SURFACE_ERROR_OK;
        goto ERROR;
    }

    freeList_.push_back(tmpBuffer);
    tmpBuffer->SetState(BUFFER_STATE_RELEASE);
    tmpBuffer->ClearExtraData();
ERROR:
    pthread_mutex_unlock(&lock_);
    pthread_cond_signal(&freeCond_);
    return ret;
}

int32_t BufferQueue::isValidAttr(uint32_t width, uint32_t height, uint32_t format, uint32_t strideAlignment)
{
    if (width == 0 || height == 0 || strideAlignment <= 0
        || format == IMAGE_PIXEL_FORMAT_NONE || !IsFormatSupported(format)) {
        return SURFACE_ERROR_INVAILD_PARAM;
    }
    return SURFACE_ERROR_OK;
}

int32_t BufferQueue::Reset(uint32_t size)
{
    if (size == 0) {
        if (isValidAttr(width_, height_, format_, strideAlignment_) != SURFACE_ERROR_OK) {
            GRAPHIC_LOGI("Invalid Attr.");
            return SURFACE_ERROR_INVAILD_PARAM;
        } else {
            InitParam();
        }
    }
    std::list<SurfaceBufferImpl *>::iterator iterBuffer = freeList_.begin();
    while (iterBuffer != freeList_.end()) {
        SurfaceBufferImpl *tmpBuffer = *iterBuffer;
        dirtyList_.remove(tmpBuffer);
        allBuffers_.remove(tmpBuffer);
        BufferManager* bufferManager = BufferManager::GetInstance();
        if (bufferManager == nullptr) {
             ++iterBuffer;
            continue;
        }
        bufferManager->FreeBuffer(tmpBuffer);
        iterBuffer = freeList_.erase(iterBuffer);
    }
    for (iterBuffer = allBuffers_.begin(); iterBuffer != allBuffers_.end(); ++iterBuffer) {
        SurfaceBufferImpl *tmpBuffer = *iterBuffer;
        tmpBuffer->SetDeletePending(1);
    }
    attachCount_ = 0;
    return 0;
}

void BufferQueue::SetQueueSize(uint8_t queueSize)
{
    if (queueSize > BUFFER_QUEUE_SIZE_MAX || queueSize == queueSize_) {
        GRAPHIC_LOGI("The queue count(%u) is invaild", queueSize);
        return;
    }
    pthread_mutex_lock(&lock_);
    if (queueSize_ > queueSize) {
        uint8_t needDelete = queueSize_ - queueSize;
        std::list<SurfaceBufferImpl *>::iterator iterBuffer = freeList_.begin();
        while (iterBuffer != freeList_.end()) {
            SurfaceBufferImpl *tmpBuffer = *iterBuffer;
            dirtyList_.remove(tmpBuffer);
            allBuffers_.remove(tmpBuffer);
            BufferManager* bufferManager = BufferManager::GetInstance();
            if (bufferManager == nullptr) {
                ++iterBuffer;
                continue;
            }
            bufferManager->FreeBuffer(tmpBuffer);
            iterBuffer = freeList_.erase(iterBuffer);
            needDelete--;
            attachCount_--;
            if (needDelete == 0) {
                break;
            }
        }
        queueSize_ = queueSize;
        pthread_mutex_unlock(&lock_);
    } else if (queueSize_ < queueSize) {
        queueSize_ = queueSize;
        pthread_mutex_unlock(&lock_);
        pthread_cond_signal(&freeCond_);
    }
}

uint8_t BufferQueue::GetQueueSize()
{
    return queueSize_;
}

void BufferQueue::SetWidthAndHeight(uint32_t width, uint32_t height)
{
    pthread_mutex_lock(&lock_);
    width_ = width;
    height_ = height;
    Reset();
    pthread_mutex_unlock(&lock_);
    pthread_cond_signal(&freeCond_);
}

int32_t BufferQueue::GetWidth()
{
    return width_;
}

int32_t BufferQueue::GetHeight()
{
    return height_;
}

void BufferQueue::SetSize(uint32_t size)
{
    pthread_mutex_lock(&lock_);
    size_ = size;
    Reset(size);
    pthread_mutex_unlock(&lock_);
    pthread_cond_signal(&freeCond_);
}

int32_t BufferQueue::GetSize()
{
    return size_;
}

void BufferQueue::SetUserData(const std::string& key, const std::string& value)
{
    if (usrDataMap_.size() > USER_DATA_COUNT) {
        return;
    }
    usrDataMap_[key] = value;
}

std::string BufferQueue::GetUserData(const std::string& key)
{
    auto p = usrDataMap_.find(key);
    if (p != usrDataMap_.end()) {
        return p->second;
    }
    return std::string();
}

void BufferQueue::SetFormat(uint32_t format)
{
    if (format == IMAGE_PIXEL_FORMAT_NONE || !IsFormatSupported(format)) {
        GRAPHIC_LOGI("Format is invailed or not supported %u", format);
        return;
    }
    pthread_mutex_lock(&lock_);
    format_ = format;
    Reset();
    pthread_mutex_unlock(&lock_);
    pthread_cond_signal(&freeCond_);
}

int32_t BufferQueue::GetFormat()
{
    return format_;
}

void BufferQueue::SetStrideAlignment(uint32_t stride)
{
    pthread_mutex_lock(&lock_);
    strideAlignment_ = stride;
    Reset();
    pthread_mutex_unlock(&lock_);
    pthread_cond_signal(&freeCond_);
}

int32_t BufferQueue::GetStrideAlignment()
{
    return strideAlignment_;
}

int32_t BufferQueue::GetStride()
{
    return stride_;
}

void BufferQueue::SetUsage(uint32_t usage)
{
    pthread_mutex_lock(&lock_);
    usage_ = usage;
    Reset();
    pthread_mutex_unlock(&lock_);
    pthread_cond_signal(&freeCond_);
}

int32_t BufferQueue::GetUsage()
{
    return usage_;
}
} // end namespace
