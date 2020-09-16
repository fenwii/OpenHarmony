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

#ifndef RECORDER_VIDEO_SOURCE_H
#define RECORDER_VIDEO_SOURCE_H
#include "recorder_source.h"
#include <memory>
#include <map>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include "format.h"
#include "media_errors.h"
#include "media_info.h"
#include "surface.h"

namespace OHOS {
namespace Media {
using OHOS::Surface;
using OHOS::SurfaceBuffer;
using OHOS::IBufferConsumerListener;
class RecorderVideoSource : public RecorderSource, IBufferConsumerListener {
public:
    /**
     * A constructor used to create a {@code RecorderSource} instance based on a file descriptor.
     *
     * @param fd Indicates the file descriptor.
     * @note Not support to play with fd-source currently
     */
    RecorderVideoSource();
    virtual ~RecorderVideoSource();

    std::shared_ptr<OHOS::Surface> GetSurface();

    /**
     * get the offset of the local file, , if source type is SOURCE_TYPE_FD, see {@link RecorderSourceType}
     *
     * @return returns the   of the first byte would been read.
     */
    virtual int32_t Start() override;
    /**
     * get the length of the local file, if source type is SOURCE_TYPE_FD, see {@link RecorderSourceType}.
     *
     * @return returns the file length
     */
    virtual int32_t AcquireBuffer(RecorderSourceBuffer &buffer, bool isBlocking) override;
    /**
     * get the the media source URI, if source type is SOURCE_TYPE_URI, see {@link RecorderSourceType}.
     *
     * @return returns the media source URI
     */
    virtual int32_t ReleaseBuffer(RecorderSourceBuffer &buffer) override;
    /**
     * get the the media source header, if source type is SOURCE_TYPE_URI, see {@link RecorderSourceType}.
     *
     * @return returns the media source header
     */
    virtual int32_t Stop() override;
    /**
     * get the the media source Stream. we call it when the source type is SOURCE_TYPE_STREAM.
     * see {@link RecorderSourceType}
     * {@link OHOS::Media::SOURCE_TYPE_STREAM}
     *
     * @return returns the media source Stream, see {@link StreamSource}
     */
    virtual int32_t Pause() override;
    /**
     * get the the media source stream format.
     *
     * @return returns the media source format, see {@link Format}
     */
    virtual int32_t Release() override;

    void OnBufferAvailable() override;
private:
    std::shared_ptr<Surface> surface_;
    std::mutex lock_;
    std::condition_variable frameAvailableCondition_;
    int32_t frameAvailableCount_;
    std::vector<SurfaceBuffer*> acquiredBuffers;
    SurfaceBuffer *acquireBuffer_;
    bool  started_;
};
}  // namespace Media
}  // namespace OHOS

#endif  // RECORDER_VIDEO_SOURCE_H
