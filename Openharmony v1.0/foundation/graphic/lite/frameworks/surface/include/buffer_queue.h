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

#ifndef GRAPHIC_LITE_BUFFER_QUEUE
#define GRAPHIC_LITE_BUFFER_QUEUE

#include <list>
#include <map>
#include "surface_buffer_impl.h"

namespace OHOS {
const static int8_t SURFACE_MAX_PLANE_NUM = 4;
struct PlaneInfo {
    uint32_t stride;
    uint32_t offset;
    uint32_t size;
};

enum PLANE_COUNT {
    IMAGE_PIXEL_FORMAT_PLANE_COUNT_RGB = 1,
    IMAGE_PIXEL_FORMAT_PLANE_COUNT_YUVSPXX,
    IMAGE_PIXEL_FORMAT_PLANE_COUNT_YUV4XX
};

class BufferQueue {
public:
    /**
     * @brief Surface Constructor. Store all buffers and manager all buffers state.
     */
    BufferQueue();

    /**
     * @brief BufferQueue Destructor. Free all buffers.
     */
    ~BufferQueue();

    /**
     * @brief Request buffer. BufferQueue deuque buffer, If free list has buffer, pop and return the buffer.
     *        If no buffer in free list, and attach count less than queue size, allocate new one .
     *         Surface producer requests buffer.
     * @param [in] whether waiting or not.
     *        wait = 1. waiting util free list has buffer, pop and return it.
     *        wait = 0. No wait, could return null pointer.
     * @returns buffer poiter.
     */
    SurfaceBufferImpl* RequestBuffer(uint8_t wait);

    /**
     * @brief Flush buffer to dirty list, for consumer acquire. When producer flush buffer, buffer
     *        will push to dirty list, and call back to consumer that buffer is available to acquire.
     * @param [in] SurfaceBufferImpl, Which buffer could acquire for consumer.
     * @returns Flush buffer succeed or not.
     *        0 is succeed; other is failed.
     */
    int32_t FlushBuffer(SurfaceBufferImpl& buffer);

    /**
     * @brief Acquire buffer. Consumer acquire buffer, which producer has flush and push to free list.
     * @returns buffer poiter.
     */
    SurfaceBufferImpl* AcquireBuffer();

    /**
     * @brief Release buffer. Consumer release buffer, which will push to free list for producer request it.
     * @param [in] SurfaceBufferImpl pointer, Which buffer need to release.
     * @returns Release buffer succeed or not.
     *        0 is succeed; other is failed.
     */
    bool ReleaseBuffer(const SurfaceBufferImpl& buffer);

    /**
     * @brief Cancel buffer. Producer cancel this buffer, buffer will push back to free list for request it again.
     * @param [in] SurfaceBufferImpl, Which buffer will push back to free list for request it.
     */
    int32_t CancelBuffer(const SurfaceBufferImpl& buffer);

    /**
     * @brief Whether the format is supported or not.
     * @param [in], Buffer format.
     */
    bool IsFormatSupported(uint32_t format);

    /**
     * @brief Set queue size, alloc max buffer count.
     *        Default is 1. Max count is 10.
     * @param [in] queueSize. Could alloc buffer count.
     */
    void SetQueueSize(uint8_t queueSize);

    /**
     * @brief Get queue size, alloc max buffer count.
     * @returns queue size.
     */
    uint8_t GetQueueSize();

    /**
     * @brief Set width and height to calculate the buffer size.
     * @param [in] width, Buffer width.
     * @param [in] height, Buffer height.
     */
    void SetWidthAndHeight(uint32_t width, uint32_t height);

    /**
     * @brief Get width, buffer width to calculate the buffer size..
     * @returns width, Buffer width.
     */
    int32_t GetWidth();

    /**
     * @brief Get height, buffer height to calculate the buffer size..
     * @returns height, Buffer height.
     */
    int32_t GetHeight();

    /**
     * @brief Set format, to calculate the buffer size.
     *        Default is IMAGE_PIXEL_FORMAT_RGB565. See all formats in OHOS::ImageFormat
     * @param [in] format, Buffer format.
     */
    void SetFormat(uint32_t format);

    /**
     * @brief Get format, buffer format to calculate the buffer size..
     * @returns format, Buffer format.
     */
    int32_t GetFormat();

    /**
     * @brief Set stride alignment bytes. Default alignment is 4 bytes.
     * @param [in] strideAlignment, Buffer stride alignment
     */
    void SetStrideAlignment(uint32_t stride);

    /**
     * @brief Get stride alignment bytes. Default alignment is 4 bytes.
     * @returns strideAlignment, Buffer stride alignment.
     */
    int32_t GetStrideAlignment();

    /**
     * @brief Get bytes of one stride which calculate by width, format and stride alignment.
     * @returns The stride
     */
    int32_t GetStride();

    /**
     * @brief Set buffer size. Alloc buffer size, no need to calculate by width, height, format...
     * @param [in] The buffer size
     */
    void SetSize(uint32_t size);

    /**
     * @brief Get buffer size. Alloc buffer size.
     *        The size is setted by SetSize() or calculated by width, height, format...
     * @returns The buffer size.
     */
    int32_t GetSize();

    /**
     * @brief Set buffer usage. Surface alloc physical or virtual memory buffer.
     *        Support usage see detail in OHOS::BUFFER_CONSUMER_USAGE.
     *        Default is BUFFER_CONSUMER_USAGE_SORTWARE, which will alloc virtual memory buffer.
     * @param [in] The buffer usage.
     */
    void SetUsage(uint32_t usage);

    /**
     * @brief Get buffer usage. Surface alloc physical or virtual memory buffer.
     *        All usage sees detail in OHOS::BUFFER_CONSUMER_USAGE.
     * @returns The buffer usage.
     */
    int32_t GetUsage();

    /**
     * @brief Set user data. Construct a local map to store all the user-data.
     * @param [in] key.
     * @param [in] value.
     */
    void SetUserData(const std::string& key, const std::string& value);

    /**
     * @brief Get user data. Get the value from local map.
     * @returns value refers to the key.
     */
    std::string GetUserData(const std::string& key);

    /**
     * @brief Buffer queue init succeed or not.
     * @returns Whether init or not.
     */
    bool Init();
private:
    bool CanRequest(uint8_t wait);
    void InitParam();
    int32_t isValidAttr(uint32_t width, uint32_t height, uint32_t format, uint32_t strideAlignment);
    uint8_t GetPlaneCount(uint32_t format);
    uint32_t Align(uint32_t value, uint32_t alignment);
    void QueryEachPlaneInfo(uint32_t planeIndex, uint32_t& size, uint32_t& offset, uint32_t& stride);
    void UpdatePlaneInfo();
    int32_t Reset(uint32_t size = 0);
    void NeedAttach();
    void Detach(SurfaceBufferImpl* buffer);
    SurfaceBufferImpl* GetBuffer(const SurfaceBufferImpl& buffer);
    int32_t ReleaseBuffer(const SurfaceBufferImpl& buffer, BufferState state);
    uint32_t width_;
    uint32_t height_;
    uint32_t format_;
    uint32_t stride_;
    uint32_t usage_;
    uint32_t size_;
    uint8_t queueSize_;
    uint32_t strideAlignment_;
    uint8_t attachCount_;
    PlaneInfo planes_[SURFACE_MAX_PLANE_NUM];
    std::list<SurfaceBufferImpl *> freeList_;
    std::list<SurfaceBufferImpl *> dirtyList_;
    std::list<SurfaceBufferImpl *> allBuffers_;
    pthread_mutex_t lock_;
    pthread_cond_t freeCond_;
    std::map<std::string, std::string> usrDataMap_;
};
} // end namespace
#endif