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

#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <pthread.h>
#include "jsi.h"
#include "player.h"

namespace OHOS {
namespace ACELite {
class AudioPlayer;

class AudioEventListener {
public:
    AudioEventListener() = default;

    explicit AudioEventListener(JSIValue callback);

    ~AudioEventListener();

    JSIValue GetCallback() const;

    void OnTrigger() const;

private:
    JSIValue callback_;
};

void TriggerEventListener(const AudioEventListener *listener);
void AsyncExecuteCallback(void *arg);

class AudioPlayerCallback : public Media::PlayerCallback {
public:
    AudioPlayerCallback() = delete;

    explicit AudioPlayerCallback(AudioPlayer *audioPlayer);

    virtual ~AudioPlayerCallback() = default;

    void OnPlaybackComplete() override;

    void OnError(int32_t errorType, int32_t errorCode) override;

    void OnInfo(int type, int extra) override;

    void OnVideoSizeChanged(int width, int height) override;

    void OnRewindToComplete() override;

private:
    static void *PlaybackCompleteHandler(void *arg);

    AudioPlayer *audioPlayer_;
};

class AudioPlayer {
public:
    static AudioPlayer *GetInstance();

    void ForkUpdateTimeThread();

    void StopUpdateTimeThread();

    bool CreatePlayer();

    bool DestoryPlayer();

    bool ResetPlayer();

    void ReleaseEventListeners();

    void ReleaseSrc();

    bool Play();

    bool Pause();

    bool Stop();

    char *GetSrc() const;

    double GetCurrentTime() const;

    double GetDuration() const;

    bool GetAutoPlay() const;

    bool IsLooping() const;

    bool IsMuted() const;

    const char *GetStatus() const;

    double GetVolume() const;

    bool IsPlaying() const;

    bool SetSrc(char *src);

    bool SetCurrentTime(double currentTime) const;

    bool SetAutoPlay(bool autoPlay);

    bool SetLoop(bool loop) const;

    bool SetVolume(double volume);

    bool SetMuted(bool muted);

    const AudioEventListener *GetOnPlayListener() const;

    const AudioEventListener *GetOnPauseListener() const;

    const AudioEventListener *GetOnStopListener() const;

    const AudioEventListener *GetOnLoadedDataListener() const;

    const AudioEventListener *GetOnEndedListener() const;

    const AudioEventListener *GetOnErrorListener() const;

    const AudioEventListener *GetOnTimeUpdateListener() const;

    void SetOnPlayListener(AudioEventListener *onPlayListener);

    void SetOnPauseListener(AudioEventListener *onPauseListener);

    void SetOnStopListener(AudioEventListener *onStopListener);

    void SetOnLoadedDataListener(AudioEventListener *onLoadedDataListener);

    void SetOnEndedListener(AudioEventListener *onEndedListener);

    void SetOnErrorListener(AudioEventListener *onErrorListener);

    void SetOnTimeUpdateListener(AudioEventListener *onTimeUpdateListener);

private:
    AudioPlayer();

    ~AudioPlayer() = default;

    static pthread_mutex_t lock_;
    static pthread_cond_t condition_;
    static void *UpdateTimeHandler(void *arg);

    Media::Player *player_;
    std::shared_ptr<AudioPlayerCallback> callback_;
    AudioEventListener *onPlayListener_;
    AudioEventListener *onPauseListener_;
    AudioEventListener *onStopListener_;
    AudioEventListener *onLoadedDataListener_;
    AudioEventListener *onEndedListener_;
    AudioEventListener *onErrorListener_;
    AudioEventListener *onTimeUpdateListener_;
    char *src_;
    char *status_;
    double volume_;
    bool autoPlay_;
    bool muted_;
    bool isRunning_;
};
} // namespace ACELite
} // namespace OHOS
#endif // AUDIO_PLAYER_H