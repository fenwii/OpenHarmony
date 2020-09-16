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
 * @addtogroup MultiMedia_Player
 * @{
 *
 * @brief Defines the <b>Player</b> class and provides functions related to media playback.
 *
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file player.h
 *
 * @brief Declares the <b>Player</b> class, which is used to implement player-related operations.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "source.h"
#include "format.h"
#include <memory>
#include <vector>
#include "surface.h"

namespace OHOS {
namespace Media {
/**
 * @brief Enumerates player seek modes. You can move the current playback position of the media to a given time
 * position using the specified mode.
 *
 * @since 1.0
 * @version 1.0
 */
enum PlayerSeekMode : int32_t {
    /** Moves the media position to the latest synchronization frame located before the given time position. */
    PLAYER_SEEK_PREVIOUS_SYNC = 0,
    /** Moves the media position to the latest synchronization frame located after the given time position. */
    PLAYER_SEEK_NEXT_SYNC,
    /** Moves the media position to the latest synchronization frame located before or after the given time position. */
    PLAYER_SEEK_CLOSEST_SYNC,
    /** Moves the media position to the latest frame located before or after the given time position. */
    PLAYER_SEEK_CLOSEST,
    /** Moves the media position to a given frame index. */
    PLAYER_SEEK_FRAME_INDEX,
};

/**
 * @brief Enumerates player states.
 *
 * @since 1.0
 * @version 1.0
 */
enum PlayerStates : uint32_t {
    /** Error */
    PLAYER_STATE_ERROR = 0,
    /** Idle */
    PLAYER_IDLE = 1 << 0,
    /** Initialized */
    PLAYER_INITIALIZED = 1 << 1,
    /** Preparing */
    PLAYER_PREPARING = 1 << 2,
    /** Prepared */
    PLAYER_PREPARED = 1 << 3,
    /** Playback started */
    PLAYER_STARTED = 1 << 4,
    /** Playback paused */
    PLAYER_PAUSED = 1 << 5,
    /** Playback stopped */
    PLAYER_STOPPED = 1 << 6,
    /** Playback completed */
    PLAYER_PLAYBACK_COMPLETE = 1 << 7
};

/**
 * @brief Provides listeners for events and exception notifications that occur during media playback.
 *
 * @since 1.0
 * @version 1.0
 */
class PlayerCallback {
public:
    enum PlayerInfoType : int32_t {
        /** Pushed the first video frame for rendering */
        PLAYER_INFO_RENDER_START = 0,
    };

    enum PlayerErrorType : int32_t {
        PLAYER_ERROR_UNKNOWN = 0,
    };

    PlayerCallback() = default;
    ~PlayerCallback() = default;

    /**
    * @brief Called when the playback is complete.
    *
    * @since 1.0
    * @version 1.0
    */
    virtual void OnPlaybackComplete() = 0;

    /**
    * @brief Called when a playback error occurs.
    *
    * @param errorType Indicates the error type. For details, see {@link PlayerErrorType}.
    * @param errorCode Indicates the error code.
    * @since 1.0
    * @version 1.0
    */
    virtual void OnError(int32_t errorType, int32_t errorCode) = 0;

    /**
    * @brief Called when playback information is received.
    *
    * @param type Indicates the information type. For details, see {@link PlayerInfoType}.
    * @param extra Indicates the information code.
    * @since 1.0
    * @version 1.0
    */
    virtual void OnInfo(int type, int extra) = 0;

    /**
    * @brief Called when the video image size changes.
    *
    * @param width Indicates the video width.
    * @param height Indicates the video height.
    * @since 1.0
    * @version 1.0
    */
    virtual void OnVideoSizeChanged(int width, int height) = 0;

    /**
    * @brief Called when the rewind is complete.
    *
    * @since 1.0
    * @version 1.0
    */
    virtual void OnRewindToComplete() = 0;
    };

    /**
    * @brief Provides functions for playing online movies, offline movies, and streams, for example, playing local
    * movies and advanced audio coding (AAC) streams.
    *
    * @since 1.0
    * @version 1.0
    */
class Player {
public:
    Player();
    ~Player();

    /**
     * @brief Sets the playback source for the player. The corresponding source can be the file descriptor (FD) of the
     * local file, local file URI, network URI, or media stream.
     *
     * @param source Indicates the playback source. Currently, only local file URIs and media streams are supported.
     * For details, see {@link Source}.
     * @return Returns <b>0</b> if the setting is successful; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t SetSource(const Source &source);

    /**
     * @brief Prepares the playback environment and buffers media data.
     *
     * This function must be called after {@link SetSource}.
     *
     * @return Returns <b>0</b> if the playback environment is prepared and media data is buffered;
     * returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t Prepare();

    /**
     * @brief Starts or resumes playback.
     *
     * This function must be called after {@link Prepare}. If the player state is <b>Prepared</b>, this function is
     * called to start playback. If the player state is <b>Playback paused</b>, this function is called to resume
     * playback. If the media is playing in an abnormal speed, this function is called to restore the playback speed
     * to normal.
     *
     * @return Returns <b>0</b> if the playback starts or resumes; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t Play();

    /**
     * @brief Checks whether the player is playing.
     *
     * @return Returns <b>true</b> if the player is playing; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsPlaying();

    /**
     * @brief Pauses playback.
     *
     * @return Returns <b>0</b> if the playback is paused; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t Pause();

    /**
     * @brief Stops playback.
     *
     * @return Returns <b>0</b> if the playback is stopped; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t Stop();

    /**
     * @brief Changes the playback position.
     *
     * This function can be used during playback or pause.
     *
     * @param mSeconds Indicates the target playback position, accurate to second.
     * @param mode Indicates the player seek mode. For details, see {@link PlayerSeekMode}.
     * @return Returns <b>0</b> if the playback position is changed; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
    */
    int32_t Rewind(int64_t mSeconds, int32_t mode);

    /**
     * @brief Sets the volume of the player.
     *
     * This function can be used during playback or pause. The value <b>0</b> indicates no sound, and <b>100</b>
     * indicates the original volume. If no audio device is started or no audio stream exists, the value <b>-1</b>
     * is returned.
     *
     * @param leftVolume Indicates the target volume of the left audio channel to set, ranging from 0 to 300.
     * @param rightVolume Indicates the target volume of the right audio channel to set, ranging from 0 to 300.
     * @return Returns <b>0</b> if the setting is successful; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t SetVolume(float leftVolume, float rightVolume);

    /**
     * @brief Sets a surface for video playback.
     *
     * @param surface Indicates the surface to set. For details, see {@link Surface}.
     * @return Returns <b>0</b> if the setting is successful; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t SetVideoSurface(Surface *surface);

    /**
     * @brief Sets loop playback.
     *
     * @param loop Specifies whether to enable loop playback. The value <b>true</b> means to enable loop playback,
     * and <b>false</b> means to disable loop playback.
     * @return Returns <b>0</b> if the setting is successful; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t EnableSingleLooping(bool loop);

    /**
     * @brief Checks whether the player is looping.
     *
     * @return Returns <b>true</b> if the player is looping; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsSingleLooping();

    /**
     * @brief Obtains the playback position, accurate to millisecond.
     *
     * @param time Indicates the playback position.
     * @return Returns <b>0</b> if the playback position is obtained; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t GetCurrentTime(int64_t &time) const;

    /**
     * @brief Obtains the total duration of media files, in milliseconds.
     *
     * @param duration Indicates the total duration of media files.
     * @return Returns <b>0</b> if the total duration is obtained; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t GetDuration(int64_t &duration) const;

    /**
     * @brief Obtains the width of the video.
     *
     * @param videoWidth Indicates the video width.
     * @return Returns <b>0</b> if the video width is obtained; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t GetVideoWidth(int32_t &videoWidth);

    /**
     * @brief Obtains the height of the video.
     *
     * @param videoHeight Indicates the video height.
     * @return Returns <b>0</b> if the video height is obtained; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t GetVideoHeight(int32_t &videoHeight);

    /**
     * @brief Restores the player to the initial state.
     *
     * @return Returns <b>0</b> if the player is restored; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t Reset();

    /**
     * @brief Releases player resources.
     *
     * @return Returns <b>0</b> if player resources are released; returns <b>-1</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t Release();

    /**
     * @brief Registers a listener to receive events and exception notifications from the player.
     *
     * @param cb Indicates the listener to register. For details, see {@link PlayerCallback}.
     * @since 1.0
     * @version 1.0
     */
    void SetPlayerCallback(const std::shared_ptr<PlayerCallback> &cb);

private:
    class PlayerImpl;
    std::unique_ptr<PlayerImpl> impl_;
};
}  // namespace Media
}  // namespace OHOS
#endif  // PLAYER_H
