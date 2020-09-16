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

#ifndef AUDIO_SOURCE_H_
#define AUDIO_SOURCE_H_

#include <cstddef>
#include <cstdint>
#include <time.h>
#include <memory>
#include <vector>

#include "media_errors.h"
#include "media_info.h"
#include "format.h"
#include "audio_manager.h"

namespace OHOS {
namespace Audio {
struct AudioSourceConfig {
    /**
     * 根据EnumDeviceBySourceType 枚举到的设备，选择设置当前audio source 要使用的设备.
     */
    uint32_t deviceId;
    AudioCodecFormat audioFormat;
    int32_t sampleRate = 0;
    int32_t channelCount = 0;
    bool interleaved;
    AudioBitWidth bitWidth = BIT_WIDTH_16;
    AudioStreamType streamUsage;
};

class AudioSource {
public:
    AudioSource();
    ~AudioSource();

    /**
     * 根据输入源类型枚举当前支持的设备，包括设备名和设备ID.
     */
    int32_t EnumDeviceBySourceType(AudioSourceType inputSource, std::vector<AudioDeviceDesc> &devices);

     /**
     * Obtains the minimum frame count (in BytesPerSample) required in the specified conditions.
     *
     * @param sampleRate Indicates the sampling rate (Hz).
     * @param channelCount Indicates the audio channel count.
     * @param audioFormat Indicates the audio data format.
     * @param frameCount the minimum frame count (in BytesPerSample).
     * @return Returns {@code true} if success; returns {@code false} otherwise.
     */
    static bool GetMinFrameCount(int32_t sampleRate, int32_t channelCount,
                                 AudioCodecFormat audioFormat, size_t &frameCount);

    /**
     * Obtains the frame count (in BytesPerSample) required in the current conditions.
     *
     * @return Returns the frame count (in BytesPerSample); returns {@code -1} if an exception occurs.
     */
    uint64_t GetFrameCount();

    /**
     * 根据AudioSourceConfig 初始化当前source.
     */
    int32_t Initialize(const AudioSourceConfig &input);

    /**
    * 设置设备ID，需要切换设备时调用.
    */
    int32_t SetInputDevice(uint32_t deviceId);

    /**
     * 获取当前的设备ID.
     */
    int32_t GetCurrentDeviceId(uint32_t &deviceId);

    /**
    * 启动源.
    */
    int32_t Start();

    /**
    * 读取源数据，返回实际读取大小.
    */
    int32_t ReadFrame(uint8_t *buffer, size_t bufferBytes, bool isBlockingRead);

    /**
    * 停止源.
    */
    int32_t Stop();

private:
    int32_t InitCheck();

private:
    bool initialized_;
    bool started_;
    AudioAdapter *audioAdapter_;
    AudioCapture *audioCapture_;
    AudioPort capturePort_ = {};
};
}  // namespace Audio
}  // namespace OHOS
#endif  // AUDIO_SOURCE_H_
