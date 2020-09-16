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

#ifndef RECORDER_SOURCE_H
#define RECORDER_SOURCE_H
#include <memory>
#include <map>
#include <string>
#include "format.h"
#include "media_info.h"

namespace OHOS {
namespace Media {
/**
 * Indicates the recorder source type
 */
enum RecorderSourceType {
    /** input camera */
    RECORDER_SOURCE_CAMERA = 0,
    /** input surface */
    RECORDER_SOURCE_SURFACE,
    /** such as aac */
    RECORDER_SOURCE_AUDIO,
    /** image data */
    RECORDER_SOURCE_IMAGE_DATA,
    RECORDER_SOURCE_INVALID,
};

/**
 * Provides audio capture information, include input source, audio codec format , the sampling rate (Hz)
 * the sampling rate (Hz), the audio channel count, audio bit width.
 *
 */
struct RecorderVideoSourceConfig {
    VideoCodecFormat videoFormat = HEVC;
    int32_t width = 0;
    int32_t height = 0;
    int32_t frameRate = 0;
    int32_t bitRate = 0;
    double captureRate = 0.0;
    int32_t degree = 0;
};

/**
 * Provides audio capture information, include input source, audio codec format , the sampling rate (Hz)
 * the sampling rate (Hz), the audio channel count, audio bit width.
 *
 */
struct RecorderAudioSourceConfig {
    AudioSourceType inputSource = AUDIO_MIC;
    AudioCodecFormat audioFormat = AUDIO_DEFAULT;
    int32_t sampleRate = 0;
    int32_t channelCount = 0;
    int32_t bitRate = 0;
    AudioStreamType streamType = TYPE_MEDIA;
    AudioBitWidth bitWidth = BIT_WIDTH_16;
};

struct RecorderSourceBuffer {
    bool keyFrameFlag;
    int64_t timeStamp;
    uint64_t dataSeq;
    size_t dataLen;
    uint8_t *dataAddr;
};

class RecorderSource {
public:
    /**
     * A constructor used to create a {@code RecorderSource} instance based on a file descriptor.
     */
    RecorderSource()
    {
        sourceType_ = RECORDER_SOURCE_INVALID;
    };

    ~RecorderSource(){};

    /**
     * get the source-type of the the source.
     *
     * @return returns the source type, see {@link RecorderSourceType}.
     */
    RecorderSourceType GetSourceType() const
    {
        return sourceType_;
    }
    virtual int32_t Start() = 0;

    virtual int32_t AcquireBuffer(RecorderSourceBuffer &buffer, bool isBlocking) = 0;

    virtual int32_t ReleaseBuffer(RecorderSourceBuffer &buffer) = 0;

    virtual int32_t Stop() = 0;

    virtual int32_t Pause() = 0;

    virtual int32_t Release() = 0;

private:
    RecorderSourceType sourceType_;
};
}  // namespace Media
}  // namespace OHOS

#endif  // RECORDER_SOURCE_H
