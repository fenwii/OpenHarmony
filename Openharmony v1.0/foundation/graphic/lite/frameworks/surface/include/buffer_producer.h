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

#ifndef GRAPHIC_LITE_BUFFER_PRODUCER_H
#define GRAPHIC_LITE_BUFFER_PRODUCER_H

#include "buffer_queue.h"
#include "surface_buffer.h"

#include <string>

namespace OHOS {
extern "C" {
typedef enum {
    REQUEST_BUFFER = 0,
    FLUSH_BUSFFER,
    CANCEL_BUFFER,
    SET_QUEUE_SIZE,
    GET_QUEUE_SIZE,
    SET_WIDTH_AND_HEIGHT,
    GET_WIDTH,
    GET_HEIGHT,
    SET_FORMAT,
    GET_FORMAT,
    SET_STRIDE_ALIGNMENT,
    GET_STRIDE_ALIGNMENT,
    GET_STRIDE,
    SET_SIZE,
    GET_SIZE,
    SET_USAGE,
    GET_USAGE,
    MAX_REQUEST_CODE,
} SURFACE_REQUEST_CODE;
} // end extern

/**
 * @brief Surface producer abstract class. Provide request, flush, cancel and set buffer attr ability.
 *        In multi process, the producer is BufferClientProducer; In single process, it is BufferQueueProducer.
 *        Using in multi media and graphic for multi process.
 */
class BufferProducer {
public:
    /**
     * @brief Surface Buffer Producer Destructor.
     */
    virtual ~BufferProducer() {};

    /**
     * @brief Request buffer. Surface producer requests buffer.
     *        Waiting until some buffer could used.
     * @param [in] whether waiting or not.
     *        wait = 1. waiting util get surface buffer.
     *        wait = 0. No wait to get surface buffer.
     * @returns buffer poiter.
     */
    virtual SurfaceBufferImpl* RequestBuffer(uint8_t wait) = 0;

    /**
     * @brief Flush buffer for consumer acquire. When producer flush buffer, to
     *        push to dirty list, and call back to consumer that buffer is available to acquire.
     * @param [in] SurfaceBufferImpl pointer, Which buffer could acquire for consumer.
     * @returns Flush buffer succeed or not.
     *        0 is succeed; other is failed.
     */
    virtual int32_t FlushBuffer(SurfaceBufferImpl* buffer) = 0;

    /**
     * @brief Cancel buffer. Producer cancel this buffer, buffer will push to free list for request it.
     * @param [in] SurfaceBufferImpl pointer, Which buffer will push back to free list for request it.
     */
    virtual void Cancel(SurfaceBufferImpl* buffer) = 0;

    /**
     * @brief Set queue size, the surface could alloc max buffer count.
     *        Default is 1. Max count is 10.
     * @param [in] queueSize. Could allocate buffer count.
     */
    virtual void SetQueueSize(uint8_t queueSize) = 0;

    /**
     * @brief Get queue size, the surface could alloc max buffer count.
     * @returns queue size.
     */
    virtual uint8_t GetQueueSize() = 0;

    /**
     * @brief Set width and height to calculate the buffer size.
     * @param [in] width, Buffer width.
     * @param [in] height, Buffer height.
     */
    virtual void SetWidthAndHeight(uint32_t width, uint32_t height) = 0;

    /**
     * @brief Get width, buffer width to calculate the buffer size..
     * @returns width, Buffer width.
     */
    virtual uint32_t GetWidth() = 0;

    /**
     * @brief Get height, buffer height to calculate the buffer size..
     * @returns height, Buffer height.
     */
    virtual uint32_t GetHeight() = 0;

    /**
     * @brief Set format, to calculate the buffer size.
     *        Default is IMAGE_PIXEL_FORMAT_RGB565. See all formats in OHOS::ImageFormat
     * @param [in] format, Buffer format.
     */
    virtual void SetFormat(uint32_t format) = 0;

    /**
     * @brief Get format, buffer format to calculate the buffer size..
     * @returns format, Buffer format.
     */
    virtual uint32_t GetFormat() = 0;

    /**
     * @brief Set stride alignment bytes. Default alignment is 4 bytes.
     * @param [in] strideAlignment, Buffer stride alignment
     */
    virtual void SetStrideAlignment(uint32_t strideAlignment) = 0;

    /**
     * @brief Get stride alignment bytes. Default alignment is 4 bytes.
     * @returns strideAlignment, Buffer stride alignment.
     */
    virtual uint32_t GetStrideAlignment() = 0;

    /**
     * @brief Get bytes of one stride which calculate by width, format and stride alignment.
     * @returns The stride
     */
    virtual uint32_t GetStride() = 0;

    /**
     * @brief Set buffer size. Surface alloc buffer size, no need to calculate by width, height, format...
     * @param [in] The buffer size
     */
    virtual void SetSize(uint32_t size) = 0;

    /**
     * @brief Get buffer size. Surface alloc buffer size.
     *        The size is setted by SetSize() or calculated by width, height, format...
     * @returns The buffer size.
     */
    virtual uint32_t GetSize() = 0;

    /**
     * @brief Set buffer usage. Surface alloc physical or virtual memory buffer.
     *        Support usage see detail in OHOS::BUFFER_CONSUMER_USAGE.
     *        Default is BUFFER_CONSUMER_USAGE_SORTWARE, which will alloc virtual memory buffer.
     * @param [in] The buffer usage.
     */
    virtual void SetUsage(uint32_t usage) = 0;

    /**
     * @brief Get buffer usage. Surface alloc physical or virtual memory buffer.
     *        All usage sees detail in OHOS::BUFFER_CONSUMER_USAGE.
     * @returns The buffer usage.
     */
    virtual uint32_t GetUsage() = 0;

    /**
     * @brief Set user data. Construct a local map to store all the user-data.
     * @param [in] key.
     * @param [in] value.
     */
    virtual void SetUserData(const std::string& key, const std::string& value) {}

    /**
     * @brief Get user data. Get the value from local map.
     * @returns value refers to the key.
     */
    virtual std::string GetUserData(const std::string& key)
    {
        return std::string();
    }
};
} // namespace OHOS
#endif