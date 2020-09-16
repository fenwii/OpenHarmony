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

/**
 * @addtogroup MultiMedia_AudioCapturer
 * @{
 *
 * @brief Declares APIs in the <b>AudioCapturer</b> class for audio capture.
 *
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file audio_capturer.h
 *
 * @brief Provides the <b>AudioCapturer</b> class to implement operations related to audio capture.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AUDIO_CAPTURER_H
#define AUDIO_CAPTURER_H

#include <cstddef>
#include <cstdint>
#include <time.h>
#include <memory>

#include "media_errors.h"
#include "media_info.h"

namespace OHOS {
namespace Audio {
/**
 * @brief Defines information about audio capture parameters, including the input source, audio codec format,sampling
 * rate (Hz), number of audio channels, bit rate, and bit width.
 *
 * @since 1.0
 * @version 1.0
 */
struct AudioCapturerInfo {
    /** Audio source type */
    AudioSourceType inputSource = AUDIO_MIC;
    /** Audio codec format */
    AudioCodecFormat audioFormat = AUDIO_DEFAULT;
    /** Sampling rate */
    int32_t sampleRate = 0;
    /** Number of audio channels */
    int32_t channelCount = 0;
    /** Bit rate */
    int32_t bitRate = 0;
    /** Audio stream type */
    AudioStreamType streamType = TYPE_MEDIA;
    /** Bit width */
    AudioBitWidth bitWidth = BIT_WIDTH_16;
};

/**
 * @brief Represents timestamp information, including the frame position information and high-resolution time source.
 *
 * @since 1.0
 * @version 1.0
 */
class Timestamp {
public:
    Timestamp() : framePosition(0)
    {
        time.tv_sec = 0;
        time.tv_nsec = 0;
    }
    ~Timestamp() = default;
    uint32_t framePosition;
    struct timespec time;

    /**
     * @brief Enumerates the time base of this <b>Timestamp</b>. Different timing methods are supported.
     *
     */
    enum class Timebase : int32_t {
        /** Monotonically increasing time, excluding the system sleep time */
        MONOTONIC = 0,
        /** Monotonically increasing time, including the system sleep time */
        BOOTTIME = 1
        };
};

/**
 * @brief Enumerates the recording states of the current device.
 *
 * @since 1.0
 * @version 1.0
 */
enum State : uint32_t {
    /** Prepared */
    PREPPARED,
    /** Recording */
    RECORDING,
    /** Stopped */
    STOPPED,
    /** Released */
    RELEASED
};

/**
 * @brief Provides functions for applications to implement audio capturing.
 *
 * @since 1.0
 * @version 1.0
 */
class AudioCapturer {
public:
    AudioCapturer();
    virtual ~AudioCapturer();

    /**
     * @brief Obtains the minimum number of frames required in a specified condition, in bytes per sample.
     *
     * @param sampleRate Indicates the audio sampling rate, in Hz.
     * @param channelCount Indicates the number of audio recording channels.
     * @param audioFormat Indicates the audio data format.
     * @param frameCount Indicates the minimum number of frames, in bytes per sample.
     * @return Returns <b>true</b> if the minimum number of frames is successfully obtained; returns <b>false</b>
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    static bool GetMinFrameCount(int32_t sampleRate, int32_t channelCount, AudioCodecFormat audioFormat,
                                size_t &frameCount);

    /**
     * @brief Obtains the number of frames required in the current condition, in bytes per sample.
     *
     * @return Returns the number of frames (in bytes per sample) if the operation is successful; returns <b>-1</b>
     * if an exception occurs.
     * @since 1.0
     * @version 1.0
     */
    uint64_t GetFrameCount();

    /**
     * @brief Sets audio capture parameters.
     *
     * @param info Indicates information about audio capture parameters to set. For details, see
     * {@link AudioCapturerInfo}.
     * @return Returns {@link SUCCESS} if the setting is successful; returns an error code defined
     * in {@link media_errors.h} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t SetCapturerInfo(const AudioCapturerInfo info);

    /**
     * @brief Obtains audio capture parameters.
     *
     * This function can be called after {@link SetCapturerInfo} is successful.
     *
     * @param info Indicates information about audio capture parameters. For details, see {@link AudioCapturerInfo}.
     * @return Returns {@link SUCCESS} if the parameter information is successfully obtained; returns an error code
     * defined in {@link media_errors.h} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t GetCapturerInfo(AudioCapturerInfo &info);

    /**
     * @brief Starts audio recording.
     *
     * @return Returns <b>true</b> if the recording is successfully started; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool Start();

    /**
     * @brief Reads audio data.
     *
     * @param buffer Indicates the pointer to the buffer into which the audio data is to be written.
     * @param userSize Indicates the size of the buffer into which the audio data is to be written, in bytes.
     * <b>userSize >= frameCount * channelCount * BytesPerSample</b> must evaluate to <b>true</b>. You can call
     * {@link GetFrameCount} to obtain the <b>frameCount</b> value.
     * @param isBlockingRead Specifies whether data reading will be blocked.
     * @return Returns the size of the audio data read from the device. The value ranges from <b>0</b> to
     * <b>userSize</b>. If the reading fails, one of the following error codes is returned:
     * <b>ERR_INVALID_PARAM</b>: The input parameter is incorrect.
     * <b>ERR_ILLEGAL_STATE</b>: The <b>AudioCapturer</b> instance is not initialized.
     * <b>ERR_SOURCE_NOT_SET</b>: The state of hardware device instance is abnormal.
     * @since 1.0
     * @version 1.0
     */
    int32_t Read(uint8_t *buffer, size_t userSize, bool isBlockingRead);

    /**
     * @brief Obtains the audio capture state.
     *
     * @return Returns the audio capture state defined in {@link State}.
     * @since 1.0
     * @version 1.0
     */
    State GetStatus();

    /**
     * @brief Obtains the timestamp.
     *
     * @param timestamp Indicates a {@link Timestamp} instance reference provided by the caller.
     * @param base Indicates the time base, which can be {@link Timestamp.Timebase#BOOTTIME Timestamp.Timebase.BOOTTIME}
     * or {@link Timestamp.Timebase#MONOTONIC Timestamp.Timebase.MONOTONIC}.
     * @return Returns <b>true</b> if the timestamp is successfully obtained; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool GetAudioTime(Timestamp &timestamp, Timestamp::Timebase base);

    /**
     * @brief Stops audio recording.
     *
     * @return Returns <b>true</b> if the recording is successfully stopped; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool Stop();

    /**
     * @brief Releases a local <b>AudioCapturer</b> object.
     *
     * @return Returns <b>true</b> if the object is successfully released; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool Release();

private:
    class AudioCapturerImpl;
    std::unique_ptr<AudioCapturerImpl> impl_;
};
}  // namespace Audio
}  // namespace OHOS
#endif  // AUDIO_CAPTURER_H
