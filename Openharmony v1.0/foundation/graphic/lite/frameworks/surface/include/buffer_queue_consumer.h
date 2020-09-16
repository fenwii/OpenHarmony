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

#ifndef GRAPHIC_LITE_BUFFER_QUEUE_CONSUMER_H
#define GRAPHIC_LITE_BUFFER_QUEUE_CONSUMER_H

#include "buffer_queue.h"
#include "surface_buffer.h"

namespace OHOS {
/**
 * @brief Surface producer abstract class. Provide request, flush, cancel and set buffer attr ability.
 *        In multi process, the producer is BufferClientProducer; In single process, it is BufferQueueProducer.
 *        Using in multi media and graphic for multi process.
 */
class BufferQueueConsumer {
public:
    BufferQueueConsumer(BufferQueue& bufferQueue);
    /**
     * @brief BufferQueueConsumer Destructor. Free all buffers.
     */
    ~BufferQueueConsumer();

    /**
     * @brief Acquire buffer. When producer has flush and push buffer to free list,
     *        Consumer acquire the buffer.
     * @returns buffer poiter.
     */

    SurfaceBufferImpl* AcquireBuffer();

    /**
     * @brief Release buffer. Consumer release buffer and push to free list for producer request it.
     * @param [in] SurfaceBufferImpl pointer, Which buffer need to release.
     * @returns Whether release buffer succeed or not.
     */
    bool ReleaseBuffer(const SurfaceBufferImpl& buffer);

    /**
     * @brief Set Buffer Queue to acquire and release buffer.
     * @param [in] Buffer Queue pointer, Which buffer need to release.
     */
    void SetBufferQueue(BufferQueue* bufferQueue);
private:
    BufferQueue* bufferQueue_;
};
} // end namespace

#endif