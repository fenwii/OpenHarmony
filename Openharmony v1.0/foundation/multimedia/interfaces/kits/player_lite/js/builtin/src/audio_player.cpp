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
#include "audio_player.h"
#include <errno.h>
#include <sys/prctl.h>
#include <sys/time.h>
#include <unistd.h>
#include "js_async_work.h"
#include "media_log.h"

#define DELETE_NOT_NULL(pointer) \
    if (pointer != nullptr)      \
    {                            \
        delete pointer;          \
        pointer = nullptr;       \
    }

namespace OHOS {
namespace ACELite {
constexpr char STATUS_PLAY[] = "play";
constexpr char STATUS_PAUSE[] = "pause";
constexpr char STATUS_STOP[] = "stop";
constexpr uint16_t MAX_VOLUME = 300;
constexpr double DEFAULT_VOLUME = 1.0;
constexpr double MILLISECONDS_PER_SECOND = 1000.0;

void TriggerEventListener(const AudioEventListener *listener)
{
    if (!JsAsyncWork::DispatchAsyncWork(AsyncExecuteCallback, const_cast<AudioEventListener *>(listener))) {
        MEDIA_ERR_LOG("dispatch async work failed.");
    }
}

void AsyncExecuteCallback(void *arg)
{
    AudioEventListener *listener = static_cast<AudioEventListener *>(arg);
    if (listener == nullptr) {
        MEDIA_ERR_LOG("async execute callback failed.");
        return;
    }
    listener->OnTrigger();
}

AudioEventListener::AudioEventListener(JSIValue callback) : callback_(JSI::AcquireValue(callback)) {}

AudioEventListener::~AudioEventListener()
{
    if (!JSI::ValueIsUndefined(callback_)) {
        JSI::ReleaseValue(callback_);
    }
}

JSIValue AudioEventListener::GetCallback() const
{
    return callback_;
}

void AudioEventListener::OnTrigger() const
{
    if (JSI::ValueIsFunction(callback_)) {
        JSI::CallFunction(callback_, JSI::CreateUndefined(), nullptr, 0);
    }
}

AudioPlayerCallback::AudioPlayerCallback(AudioPlayer *audioPlayer) : PlayerCallback(), audioPlayer_(audioPlayer) {}

void *AudioPlayerCallback::PlaybackCompleteHandler(void *arg)
{
    AudioPlayer *audioPlayer_ = (AudioPlayer *)arg;
    prctl(PR_SET_NAME, "PlaybackCompleteHandler");

    if (!audioPlayer_->ResetPlayer()) {
        MEDIA_ERR_LOG("fail to reset player.");
        TriggerEventListener(audioPlayer_->GetOnErrorListener());
    }
    TriggerEventListener(audioPlayer_->GetOnEndedListener());
    return nullptr;
}

void AudioPlayerCallback::OnPlaybackComplete()
{
    MEDIA_DEBUG_LOG("fork playback complete handler thread.");
    pthread_t threadId;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int retCode = pthread_create(&threadId, &attr, AudioPlayerCallback::PlaybackCompleteHandler, audioPlayer_);
    if (retCode != 0) {
        MEDIA_ERR_LOG("fork thread failed: %d.", retCode);
        return;
    }
    MEDIA_DEBUG_LOG("fork thread success: %lu", threadId);
}

void AudioPlayerCallback::OnError(int32_t errorType, int32_t errorCode)
{
    TriggerEventListener(audioPlayer_->GetOnErrorListener());
}

void AudioPlayerCallback::OnInfo(int type, int extra)
{
    TriggerEventListener(audioPlayer_->GetOnLoadedDataListener());
}

void AudioPlayerCallback::OnVideoSizeChanged(int width, int height) {}

void AudioPlayerCallback::OnRewindToComplete()
{
    TriggerEventListener(audioPlayer_->GetOnTimeUpdateListener());
}

pthread_mutex_t AudioPlayer::lock_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t AudioPlayer::condition_ = PTHREAD_COND_INITIALIZER;

AudioPlayer *AudioPlayer::GetInstance()
{
    static AudioPlayer audioPlayer;
    return &audioPlayer;
}

AudioPlayer::AudioPlayer() : player_(nullptr),
                             onPlayListener_(nullptr),
                             onPauseListener_(nullptr),
                             onStopListener_(nullptr),
                             onLoadedDataListener_(nullptr),
                             onEndedListener_(nullptr),
                             onErrorListener_(nullptr),
                             onTimeUpdateListener_(nullptr),
                             src_(nullptr),
                             status_(const_cast<char *>(STATUS_STOP)),
                             volume_(DEFAULT_VOLUME),
                             autoPlay_(false),
                             muted_(false),
                             isRunning_(false) {}

void AudioPlayer::ForkUpdateTimeThread()
{
    MEDIA_DEBUG_LOG("fork update time thread.");
    pthread_t threadId;
    if (isRunning_) {
        return;
    }
    isRunning_ = true;
    int retCode = pthread_mutex_init(&lock_, nullptr);
    if (retCode != 0) {
        MEDIA_ERR_LOG("init mutex lock failed: %d.", retCode);
        return;
    }
    retCode = pthread_cond_init(&condition_, nullptr);
    if (retCode != 0) {
        MEDIA_ERR_LOG("init condition failed: %d.", retCode);
        (void)pthread_mutex_destroy(&lock_);
        return;
    }
    retCode = pthread_create(&threadId, nullptr, AudioPlayer::UpdateTimeHandler, this);
    if (retCode != 0) {
        MEDIA_ERR_LOG("fork thread failed: %d.", retCode);
        (void)pthread_mutex_destroy(&lock_);
        (void)pthread_cond_destroy(&condition_);
        return;
    }
    MEDIA_DEBUG_LOG("fork thread success: %lu", threadId);
}

void *AudioPlayer::UpdateTimeHandler(void *arg)
{
    prctl(PR_SET_NAME, "UpdateTimeHandler");
    if (arg == nullptr) {
        MEDIA_ERR_LOG("audio player is null.");
        return nullptr;
    }
    AudioPlayer *audioPlayer = static_cast<AudioPlayer *>(arg);

    struct timespec timeout;
    int retCode;
    while (audioPlayer->isRunning_) {
        retCode = pthread_mutex_lock(&lock_);
        if (retCode != 0) {
            MEDIA_ERR_LOG("mutex lock failed: %d", retCode);
            break;
        }
        if (!audioPlayer->IsPlaying()) {
            // waiting for playing
            (void)pthread_cond_wait(&condition_, &lock_);
        } else {
            retCode = clock_gettime(CLOCK_REALTIME, &timeout);
            if (retCode != 0) {
                MEDIA_ERR_LOG("get current time failed: %d", retCode);
                (void)pthread_mutex_unlock(&lock_);
                continue;
            }
            timeout.tv_sec += 1;
            retCode = pthread_cond_timedwait(&condition_, &lock_, &timeout);
            if (retCode == ETIMEDOUT) {
                TriggerEventListener(audioPlayer->GetOnTimeUpdateListener());
            }
        }
        retCode = pthread_mutex_unlock(&lock_);
        if (retCode != 0) {
            MEDIA_ERR_LOG("unlock faild: %d", retCode);
            break;
        }
    }
    audioPlayer->StopUpdateTimeThread();
    (void)pthread_cond_destroy(&condition_);
    (void)pthread_mutex_destroy(&lock_);
    return nullptr;
}

void AudioPlayer::StopUpdateTimeThread()
{
    isRunning_ = false;
}

bool AudioPlayer::CreatePlayer()
{
    player_ = new Media::Player();
    if (player_ == nullptr) {
        MEDIA_ERR_LOG("fail to create player");
        return false;
    }
    if (muted_) {
        player_->SetVolume(0, 0);
    } else {
        double volume = volume_ * MILLISECONDS_PER_SECOND;
        if (player_->SetVolume(volume, volume) != 0) {
            MEDIA_ERR_LOG("fail to reset volume");
        }
    }
    if (!callback_) {
        MEDIA_ERR_LOG("Create Callback");
        callback_ = std::make_shared<AudioPlayerCallback>(this);
    }
    player_->SetPlayerCallback(callback_);
    return true;
}

bool AudioPlayer::DestoryPlayer()
{
    if (player_ != nullptr) {
        if (player_->IsPlaying() && player_->Stop() != 0) {
            MEDIA_ERR_LOG("fail to stop audio.");
        }
        if (player_->Reset() != 0) {
            MEDIA_ERR_LOG("fail to reset audio player.");
        }
        if (player_->Release() != 0) {
            MEDIA_ERR_LOG("fail to release audio player.");
        }
        delete player_;
        player_ = nullptr;
    }
    ReleaseSrc();
    status_ = const_cast<char *>(STATUS_STOP);
    return true;
}

bool AudioPlayer::ResetPlayer()
{
    (void)pthread_mutex_lock(&lock_);
    bool ret = DestoryPlayer();
    if (!ret) {
        MEDIA_ERR_LOG("fail to destory player.");
    }
    ret = CreatePlayer();
    if (!ret) {
        MEDIA_ERR_LOG("fail to re-create audio.");
    }
    (void)pthread_mutex_unlock(&lock_);
    return ret;
}

void AudioPlayer::ReleaseEventListeners()
{
    DELETE_NOT_NULL(onPlayListener_);
    DELETE_NOT_NULL(onPauseListener_);
    DELETE_NOT_NULL(onStopListener_);
    DELETE_NOT_NULL(onLoadedDataListener_);
    DELETE_NOT_NULL(onEndedListener_);
    DELETE_NOT_NULL(onErrorListener_);
    DELETE_NOT_NULL(onTimeUpdateListener_);
}

void AudioPlayer::ReleaseSrc()
{
    if (src_ != nullptr) {
        ace_free(src_);
        src_ = nullptr;
    }
}

bool AudioPlayer::Play()
{
    if (player_->IsPlaying()) {
        MEDIA_DEBUG_LOG("audio is playing.");
        return true;
    }
    if (src_ == nullptr) {
        MEDIA_ERR_LOG("audio src is required.");
        return false;
    }
    if (player_->Play() != 0) {
        MEDIA_ERR_LOG("fail to play audio.");
        return false;
    }
    int retCode = pthread_cond_signal(&condition_);
    if (retCode != 0) {
        MEDIA_ERR_LOG("fail to signal condition: %d.", retCode);
    }
    status_ = const_cast<char *>(STATUS_PLAY);
    TriggerEventListener(onPlayListener_);
    return true;
}

bool AudioPlayer::Pause()
{
    if (!player_->IsPlaying()) {
        MEDIA_DEBUG_LOG("player is not playing");
        return false;
    }
    if (player_->Pause() != 0) {
        MEDIA_ERR_LOG("fail to pause audio.");
        return false;
    }
    status_ = const_cast<char *>(STATUS_PAUSE);
    TriggerEventListener(onPauseListener_);
    return true;
}

bool AudioPlayer::Stop()
{
    TriggerEventListener(onStopListener_);
    if (!DestoryPlayer()) {
        MEDIA_ERR_LOG("fail to destory player.");
    }
    if (!CreatePlayer()) {
        MEDIA_ERR_LOG("fail to re-create audio.");
        return false;
    }
    return true;
}

char *AudioPlayer::GetSrc() const
{
    return src_;
}

double AudioPlayer::GetCurrentTime() const
{
    if (status_ == STATUS_STOP) {
        return -1;
    }
    int64_t currentTime = 0;
    if (player_->GetCurrentTime(currentTime) != 0) {
        MEDIA_ERR_LOG("fail to get audio currentTime property.");
    }
    return currentTime / MILLISECONDS_PER_SECOND;
}

double AudioPlayer::GetDuration() const
{
    if (status_ == STATUS_STOP) {
        return -1;
    }

    int64_t duation = 0;
    if (player_->GetDuration(duation) != 0) {
        MEDIA_ERR_LOG("fail to get audio duaiton property.");
    }
    return duation / MILLISECONDS_PER_SECOND;
}

bool AudioPlayer::GetAutoPlay() const
{
    return autoPlay_;
}

bool AudioPlayer::IsLooping() const
{
    return player_->IsSingleLooping();
}

bool AudioPlayer::IsMuted() const
{
    return muted_;
}

const char *AudioPlayer::GetStatus() const
{
    return status_;
}

double AudioPlayer::GetVolume() const
{
    return volume_;
}

bool AudioPlayer::IsPlaying() const
{
    if (player_ == nullptr) {
        return false;
    }

    return player_->IsPlaying();
}

bool AudioPlayer::SetSrc(char *src)
{
    if (src_ != nullptr) {
        if (!DestoryPlayer()) {
            MEDIA_ERR_LOG("fail to destory player.");
        }
        if (!CreatePlayer()) {
            MEDIA_ERR_LOG("fail to re-create audio.");
        }
    }

    if (src == nullptr) {
        MEDIA_ERR_LOG("set audio src to null.");
        return true;
    }

    std::string uri(src);
    std::map<std::string, std::string> header;
    Media::Source source(uri, header);
    if (player_->SetSource(source) != 0) {
        MEDIA_ERR_LOG("fail to set audio src property.");
        return false;
    }
    src_ = src;
    if (player_->Prepare() != 0) {
        MEDIA_ERR_LOG("fail to prepare.");
        return false;
    }
    if (autoPlay_) {
        this->Play();
    }
    return true;
}

bool AudioPlayer::SetCurrentTime(double currentTime) const
{
    if (currentTime < 0) {
        MEDIA_ERR_LOG("currentTime must be larger than or equals 0.");
        return false;
    }
    int64_t position = static_cast<int64_t>(currentTime * MILLISECONDS_PER_SECOND);
    if (player_->Rewind(position, Media::PlayerSeekMode::PLAYER_SEEK_CLOSEST_SYNC) != 0) {
        MEDIA_ERR_LOG("fail to set audio currentTime property.");
        return false;
    }
    return true;
}

bool AudioPlayer::SetAutoPlay(bool autoPlay)
{
    if (autoPlay && src_ != nullptr && status_ == STATUS_STOP) {
        if (!Play()) {
            MEDIA_ERR_LOG("fail to auto play audio.");
        }
    }
    autoPlay_ = autoPlay;
    return true;
}

bool AudioPlayer::SetLoop(bool loop) const
{
    if (player_->EnableSingleLooping(loop) != 0) {
        MEDIA_ERR_LOG("1 argument is required.");
        return false;
    }
    return true;
}

bool AudioPlayer::SetVolume(double volume)
{
    if (volume < 0 || volume > 1) {
        MEDIA_ERR_LOG("invalid parameter.");
        return false;
    }
    float parsedVolume = static_cast<float>(volume * MAX_VOLUME) ;
    if (player_->SetVolume(parsedVolume, parsedVolume) != 0) {
        MEDIA_ERR_LOG("fail to set volume.");
        return false;
    }
    volume_ = volume;
    return true;
}

bool AudioPlayer::SetMuted(bool muted)
{
    double volume = muted ? 0.0 : (volume_ * MILLISECONDS_PER_SECOND);
    if (player_->SetVolume(volume, volume) != 0) {
        MEDIA_ERR_LOG("fail to set volume.");
        return false;
    }
    muted_ = muted;
    return true;
}

const AudioEventListener *AudioPlayer::GetOnPlayListener() const
{
    return onPlayListener_;
}

const AudioEventListener *AudioPlayer::GetOnPauseListener() const
{
    return onPauseListener_;
}

const AudioEventListener *AudioPlayer::GetOnStopListener() const
{
    return onStopListener_;
}

const AudioEventListener *AudioPlayer::GetOnLoadedDataListener() const
{
    return onLoadedDataListener_;
}

const AudioEventListener *AudioPlayer::GetOnEndedListener() const
{
    return onEndedListener_;
}

const AudioEventListener *AudioPlayer::GetOnErrorListener() const
{
    return onErrorListener_;
}

const AudioEventListener *AudioPlayer::GetOnTimeUpdateListener() const
{
    return onTimeUpdateListener_;
}

void AudioPlayer::SetOnPlayListener(AudioEventListener *onPlayListener)
{
    if (onPlayListener_ != nullptr) {
        delete onPlayListener_;
    }
    onPlayListener_ = onPlayListener;
}

void AudioPlayer::SetOnPauseListener(AudioEventListener *onPauseListener)
{
    if (onPauseListener_ != nullptr) {
        delete onPauseListener_;
    }
    onPauseListener_ = onPauseListener;
}

void AudioPlayer::SetOnStopListener(AudioEventListener *onStopListener)
{
    if (onStopListener_ != nullptr) {
        delete onStopListener_;
    }
    onStopListener_ = onStopListener;
}

void AudioPlayer::SetOnLoadedDataListener(AudioEventListener *onLoadedDataListener)
{
    if (onLoadedDataListener_ != nullptr) {
        delete onLoadedDataListener_;
    }
    onLoadedDataListener_ = onLoadedDataListener;
}

void AudioPlayer::SetOnEndedListener(AudioEventListener *onEndedListener)
{
    if (onEndedListener_ != nullptr) {
        delete onEndedListener_;
    }
    onEndedListener_ = onEndedListener;
}

void AudioPlayer::SetOnErrorListener(AudioEventListener *onErrorListener)
{
    if (onErrorListener_ != nullptr) {
        delete onErrorListener_;
    }
    onErrorListener_ = onErrorListener;
}

void AudioPlayer::SetOnTimeUpdateListener(AudioEventListener *onTimeUpdateListener)
{
    if (onTimeUpdateListener_ != nullptr) {
        delete onTimeUpdateListener_;
    }
    onTimeUpdateListener_ = onTimeUpdateListener;
}
} // namespace ACELite
} // namespace OHOS
