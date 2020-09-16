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

#ifndef GRAPHIC_LITE_BUFFER_SLAVE_PRODUCER_H
#define GRAPHIC_LITE_BUFFER_SLAVE_PRODUCER_H

#include "buffer_producer.h"
#include "surface_buffer.h"
#include "buffer_queue.h"
#ifndef _SURFACE_LINUX_
#include "serializer.h"
#include "liteipc_adapter.h"
#endif
namespace OHOS {
#ifndef _SURFACE_LINUX_
/**
 * @brief Surface producer client class in multi process. Surface Client invoke these method to send ipc
 *        request to BufferQueueProducer for request buffer, flush buffer, cancel buffer and set buffer attr.
 */
class BufferClientProducer : public BufferProducer {
public:
    /**
     * @brief Surface Buffer Client Producer Constructor.
     * @param [in] SvcIdentity sid, Surface consumer sid, for sending ipc request.
     */
    BufferClientProducer(const SvcIdentity& sid);

    /**
     * @brief Surface Buffer Client Producer Destructor.
     */
    ~BufferClientProducer();

    /**
     * @brief Request buffer. Surface client producer sends ipc message(code=REQUEST_BUFFER) to requests buffer.
     *        BufferQueueProducer does the request and return Buffer handle, then map the handle with virtual address
     *        to write data.
     * @param [in] whether waiting or not.
     *        wait = 1. waiting util get surface buffer.
     *        wait = 0. No wait to get surface buffer.
     * @returns buffer poiter.
     */
    SurfaceBufferImpl* RequestBuffer(uint8_t wait) override;

    /**
     * @brief Flush buffer for consumer acquire. Client producer sends request(code=FLUSH_BUSFFER) to flush buffer,
     *        BufferQueueProducer push buffer to dirty list, and call back to consumer that buffer is available to
     *        acquire.
     * @param [in] SurfaceBufferImpl pointer, Which buffer could acquire for consumer.
     * @returns Flush buffer succeed or not.
     *        0 is succeed; other is failed.
     */
    int32_t FlushBuffer(SurfaceBufferImpl* buffer) override;

    /**
     * @brief Cancel buffer. Client Producer sends request(CANCEL_BUFFER) to cancel this buffer.
     *        BufferQueueProducer push push buffer to free list for request it again.
     * @param [in] SurfaceBufferImpl pointer, push it back to free list for request it.
     */
    void Cancel(SurfaceBufferImpl* buffer) override;

    /**
     * @brief Set queue size. Client Producer sends request(SET_QUEUE_SIZE) to set max buffer count.
     * @param [in] queueSize. Could allocate buffer count.
     */
    void SetQueueSize(uint8_t queueSize) override;

    /**
     * @brief Get queue size. Client Producer sends request(GET_QUEUE_SIZE) to get max buffer count.
     * @returns queue size.
     */
    uint8_t GetQueueSize() override;

    /**
     * @brief Client Producer sends request(SET_WIDTH_AND_HEIGHT) to set width and height to calculate the buffer size.
     * @param [in] width, Buffer width.
     * @param [in] height, Buffer height.
     */
    void SetWidthAndHeight(uint32_t width, uint32_t height) override;

    /**
     * @brief Client Producer sends request(GET_WIDTH) to get width, buffer width to calculate the buffer size..
     * @returns width, Buffer width.
     */
    uint32_t GetWidth() override;

    /**
     * @brief Client Producer sends request(GET_HEIGHT) to get height, buffer height to calculate the buffer size..
     * @returns height, Buffer height.
     */
    uint32_t GetHeight() override;

    /**
     * @brief Client Producer sends request(SET_FORMAT) to set format, to calculate the buffer size.
     *        Default is IMAGE_PIXEL_FORMAT_RGB565. See all formats in OHOS::ImageFormat
     * @param [in] format, Buffer format.
     */
    void SetFormat(uint32_t format) override;

    /**
     * @brief Client Producer sends request(GET_FORMAT) to get format, buffer format to calculate the buffer size..
     * @returns format, Buffer format.
     */
    uint32_t GetFormat() override;

    /**
     * @brief Client Producer sends request(SET_STRIDE_ALIGNMENT) to set stride alignment bytes.
     *        Default alignment is 4 bytes.
     * @param [in] strideAlignment, Buffer stride alignment
     */
    void SetStrideAlignment(uint32_t strideAlignment) override;

    /**
     * @brief Client Producer sends request(GET_STRIDE_ALIGNMENT) to get stride alignment bytes.
     *        Default alignment is 4 bytes.
     * @returns strideAlignment, Buffer stride alignment.
     */
    uint32_t GetStrideAlignment() override;

    /**
     * @brief Client Producer sends request(GET_STRIDE) to get bytes of one stride which calculate by width,
     *        format and stride alignment.
     * @returns The stride
     */
    uint32_t GetStride() override;

    /**
     * @brief Client Producer sends request(SET_SIZE) to set buffer size. Surface alloc buffer size, no need
     *        to calculate by width, height, format...
     * @param [in] The buffer size
     */
    void SetSize(uint32_t size) override;

    /**
     * @brief Client Producer sends request(GET_SIZE) to get buffer size. Surface alloc buffer size.
     *        The size is setted by SetSize() or calculated by width, height, format...
     * @returns The buffer size.
     */
    uint32_t GetSize() override;

    /**
     * @brief Client Producer sends request(SET_USAGE) to set buffer usage. Surface alloc physical or
     *        virtual memory buffer. Support usage see detail in OHOS::BUFFER_CONSUMER_USAGE.
     *        Default is BUFFER_CONSUMER_USAGE_SORTWARE, which will alloc virtual memory buffer.
     * @param [in] The buffer usage.
     */
    void SetUsage(uint32_t usage) override;

    /**
     * @brief Client Producer sends request(GET_USAGE) to get buffer usage. Surface alloc physical or
     *        virtual memory buffer. All usage sees detail in OHOS::BUFFER_CONSUMER_USAGE.
     * @returns The buffer usage.
     */
    uint32_t GetUsage() override;
private:
    uint32_t GetAttr(uint32_t code);
    void SetAttr(uint32_t code, uint32_t value);
    SvcIdentity sid_;
};
#endif
} // end namespace

#endif
