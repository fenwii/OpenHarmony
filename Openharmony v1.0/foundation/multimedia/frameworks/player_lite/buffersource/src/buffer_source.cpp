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

#include "buffer_source.h"
#include "securec.h"
#include "media_log.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define CHK_NULL_RETURN( ptr) \
do { \
    if (ptr == nullptr) { \
        MEDIA_ERR_LOG("input param null"); \
        return -1; \
    } \
} while (0)


BufferSource::BufferSource(void)
{
    inited_ = false;

    idleBuffer_.clear();
    filledBuffer_.clear();
    if (memset_s(buffer_, sizeof(BufferInfo) * QUEUE_SIZE, 0, sizeof(BufferInfo) * QUEUE_SIZE) != 0)  {
        MEDIA_ERR_LOG("BufferSource memset_s failed");
    }
}

BufferSource::~BufferSource(void)
{
    int i;
    if (inited_ == false) {
        return;
    }
    idleBuffer_.clear();
    filledBuffer_.clear();
    for (i = 0; i < QUEUE_SIZE; i++) {
        if (buffer_[i].virAddr != nullptr) {
            free(buffer_[i].virAddr);
            buffer_[i].virAddr = nullptr;
        }
    }
    inited_ = false;
}

int BufferSource::Init(void)
{
    int i;

    for (i = 0; i < QUEUE_SIZE; i++) {
        buffer_[i].virAddr = malloc(BUFER_SIZE);
        if (buffer_[i].virAddr == nullptr) {
            MEDIA_ERR_LOG("BufferSource::Init, malloc failed\n");
            goto failed;
        }
        buffer_[i].phyAddr = 0;
        buffer_[i].fd = -1;
        buffer_[i].bufLen = BUFER_SIZE;
        buffer_[i].offset = 0;
        buffer_[i].size = BUFER_SIZE;
        buffer_[i].idx = i;

        QueBuffer buffer;
        buffer.idx = i;
        buffer.flag = 0;
        buffer.offset = 0;
        buffer.size = 0;
        buffer.timestamp = 0;
        QueIdleBuffer(&buffer);
    }
    inited_ = true;
    MEDIA_INFO_LOG("idleQue size:%d",idleBuffer_.size());
    return 0;
failed:
    for (i = 0; i < QUEUE_SIZE; i++) {
        if (buffer_[i].virAddr != nullptr) {
            free(buffer_[i].virAddr);
            buffer_[i].virAddr = nullptr;
        }
    }
    idleBuffer_.clear();
    return -1;
}

int BufferSource::GetQueSize(void)
{
    return QUEUE_SIZE;
}

int BufferSource::GetBufferInfo(int idx, BufferInfo* info)
{
    CHK_NULL_RETURN(info);
    if (idx < 0 || idx >= QUEUE_SIZE) {
        return -1;
    }
    *info = buffer_[idx];
    return 0;
}

int BufferSource::QueIdleBuffer(const QueBuffer *buffer)
{
    std::lock_guard<std::mutex> lock(idleQueMutex_);
    CHK_NULL_RETURN(buffer);
    idleBuffer_.push_back(*buffer);
    return 0;
}

int BufferSource::DequeIdleBuffer(QueBuffer* buffer, int timeOut)
{
    std::lock_guard<std::mutex> lock(idleQueMutex_);
    CHK_NULL_RETURN(buffer);
    if (idleBuffer_.empty() != 0) {
        return -1;
    }
    *buffer = idleBuffer_[0];
    idleBuffer_.erase(idleBuffer_.begin());
    return 0;
}

size_t BufferSource::GetIdleQueSize(void)
{
    size_t size;
    std::lock_guard<std::mutex> lock(idleQueMutex_);
    size = idleBuffer_.size();
    return size;
}

int BufferSource::QueFilledBuffer(const QueBuffer *buffer)
{
    std::lock_guard<std::mutex> lock(filledQueMutex_);
    CHK_NULL_RETURN(buffer);
    filledBuffer_.push_back(*buffer);
    return 0;
}

int BufferSource::DequeFilledBuffer(QueBuffer* buffer, int timeOut)
{
    std::lock_guard<std::mutex> lock(filledQueMutex_);
    CHK_NULL_RETURN(buffer);
    if (filledBuffer_.empty() != 0) {
        return -1;
    }
    *buffer = filledBuffer_[0];
    filledBuffer_.erase(filledBuffer_.begin());
    return 0;
}

size_t BufferSource::GetFilledQueSize(void)
{
    size_t size;
    std::lock_guard<std::mutex> lock(filledQueMutex_);
    size = filledBuffer_.size();
    return size;
}

int32_t BufferSource::GetFilledQueDataSize(void)
{
    uint32_t i;
    size_t size;
    int32_t len = 0;
    std::lock_guard<std::mutex> lock(filledQueMutex_);
    size = filledBuffer_.size();
    for (i = 0; i < size; i++) {
        len += filledBuffer_[i].size;
    }
    return len;
}

int BufferSource::GetFilledBuffer(size_t idx, QueBuffer* buffer)
{
    std::lock_guard<std::mutex> lock(filledQueMutex_);
    size_t queSize;
    CHK_NULL_RETURN(buffer);
    queSize = filledBuffer_.size();
    if (queSize <= idx) {
        return -1;
    }
    *buffer = filledBuffer_[idx];
    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
