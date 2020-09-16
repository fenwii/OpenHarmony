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

#ifndef GRAPHIC_LITE_BUFFER_QUEUEU_PRODUCER_H
#define GRAPHIC_LITE_BUFFER_QUEUEU_PRODUCER_H

#include "buffer_producer.h"
#include "buffer_queue.h"
#include "ibuffer_consumer_listener.h"
#include "surface_buffer.h"

namespace OHOS {
/**
 * @brief Surface producer class. In multi process, deal with surface client producer ipc request;
 *        In single process, BufferQueueProducer is producer to request buffer, flush buffer,
 *        cancel buffer and set buffer attr.
 */
class BufferQueueProducer : public BufferProducer {
public:
    /**
     * @brief Surface Buffer Client Producer Constructor.
     * @param [in] BufferQueue bufferQueue, to request buffer, flush buffer,
    *              cancel buffer and set buffer attr.
     */
    BufferQueueProducer(BufferQueue* bufferQueue);

    /**
     * @brief Surface Buffer Producer Destructor.
     */
    ~BufferQueueProducer();

    /**
     * @brief Request buffer. Surface producer requests buffer.
     *        Waiting until some buffer could used.
     * @param [in] whether waiting or not.
     *        wait = 1. waiting util get surface buffer.
     *        wait = 0. No wait to get surface buffer.
     * @returns buffer poiter.
     */
    SurfaceBufferImpl* RequestBuffer(uint8_t wait) override;

    /**
     * @brief Flush buffer for consumer acquire. When producer flush buffer, to
     *        push to dirty list, and call back to consumer that buffer is available to acquire.
     * @param [in] SurfaceBufferImpl pointer, Which buffer could acquire for consumer.
     * @returns Flush buffer succeed or not.
     *        0 is succeed; other is failed.
     */
    int32_t FlushBuffer(SurfaceBufferImpl* buffer) override;

    /**
     * @brief Enqueue buffer for consumer acquire and notice consumer to acquire it.
     * @param [in] SurfaceBufferImpl, Which buffer could acquire for consumer.
     * @returns Enqueue buffer succeed or not.
     *        0 is succeed; other is failed.
     */
    int32_t EnqueueBuffer(SurfaceBufferImpl& buffer);

    /**
     * @brief Cancel buffer. Producer cancel this buffer, buffer will push to free list for request it.
     * @param [in] SurfaceBufferImpl pointer, push it back to free list for request it.
     */
    void Cancel(SurfaceBufferImpl* buffer) override;

    /**
     * @brief Set queue size, the surface could alloc max buffer count.
     *        Default is 1. Max count is 10.
     * @param [in] queueSize. Could allocate buffer count.
     */
    void SetQueueSize(uint8_t queueSize) override;

    /**
     * @brief Get queue size, the surface could alloc max buffer count.
     * @returns queue size.
     */
    uint8_t GetQueueSize() override;

    /**
     * @brief Set width and height to calculate the buffer size.
     * @param [in] width, Buffer width.
     * @param [in] height, Buffer height.
     */
    void SetWidthAndHeight(uint32_t width, uint32_t height) override;

    /**
     * @brief Get width, buffer width to calculate the buffer size..
     * @returns width, Buffer width.
     */
    uint32_t GetWidth() override;

    /**
     * @brief Get height, buffer height to calculate the buffer size..
     * @returns height, Buffer height.
     */
    uint32_t GetHeight() override;

    /**
     * @brief Set format, to calculate the buffer size.
     *        Default is IMAGE_PIXEL_FORMAT_RGB565. See all formats in OHOS::ImageFormat
     * @param [in] format, Buffer format.
     */
    void SetFormat(uint32_t format) override;

    /**
     * @brief Get format, buffer format to calculate the buffer size..
     * @returns format, Buffer format.
     */
    uint32_t GetFormat() override;

    /**
     * @brief Set stride alignment bytes. Default alignment is 4 bytes.
     * @param [in] strideAlignment, Buffer stride alignment
     */
    void SetStrideAlignment(uint32_t strideAlignment) override;

    /**
     * @brief Get stride alignment bytes. Default alignment is 4 bytes.
     * @returns strideAlignment, Buffer stride alignment.
     */
    uint32_t GetStrideAlignment() override;

    /**
     * @brief Get bytes of one stride which calculate by width, format and stride alignment.
     * @returns The stride
     */
    uint32_t GetStride() override;

    /**
     * @brief Set buffer size. Surface alloc buffer size, no need to calculate by width, height, format...
     * @param [in] The buffer size
     */
    void SetSize(uint32_t size) override;

    /**
     * @brief Get buffer size. Surface alloc buffer size.
     *        The size is setted by SetSize() or calculated by width, height, format...
     * @returns The buffer size.
     */
    uint32_t GetSize() override;

    /**
     * @brief Set buffer usage. Surface alloc physical or virtual memory buffer.
     *        Support usage see detail in OHOS::BUFFER_CONSUMER_USAGE.
     *        Default is BUFFER_CONSUMER_USAGE_SORTWARE, which will alloc virtual memory buffer.
     * @param [in] The buffer usage.
     */
    void SetUsage(uint32_t usage) override;

    /**
     * @brief Get buffer usage. Surface alloc physical or virtual memory buffer.
     *        All usage sees detail in OHOS::BUFFER_CONSUMER_USAGE.
     * @returns The buffer usage.
     */
    uint32_t GetUsage() override;

    /**
     * @brief Set user data. Construct a local map to store all the user-data.
     * @param [in] key.
     * @param [in] value.
     */
    void SetUserData(const std::string& key, const std::string& value) override;

    /**
     * @brief Get user data. Get the value from local map.
     * @returns value refers to the key.
     */
    std::string GetUserData(const std::string& key) override;

    /**
     * @brief Register consumer listener, when some buffer is available for acquired.
     *        One producer only has one consumer listener.
     * @param [in], IBufferConsumerListener listener.
     */
    void RegisterConsumerListener(IBufferConsumerListener& listener);

    /**
     * @brief Unregister consumer listener, remove the consumer listener.
     *        One producer only has one consumer listener, So when invoking this method,
     *        there will have no listener.
     */
    void UnregisterConsumerListener();
#ifndef _SURFACE_LINUX_
    /**
     * @brief Deal with the ipc msg from BufferClientProducer.
     * @param [in] ipcMsg, ipc msg, constains request code...
     * @param [in] IpcIo pointer, ipc msg object, constains request attr...
     * @returns 0 is succeed; other is failed.
     */
    int32_t OnIpcMsg(void *ipcMsg, IpcIo *io);
#endif
private:
    BufferQueue* bufferQueue_;
    IBufferConsumerListener* consumerListener_;
};
} // end namespace
#endif
