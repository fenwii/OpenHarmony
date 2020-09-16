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
#include "audio_module.h"
#include "media_log.h"

namespace OHOS {
namespace ACELite {
constexpr char PROP_SUCCESS[] = "success";
constexpr char PROP_COMPLETE[] = "complete";

void AudioModule::OnTerminate()
{
    AudioPlayer *audioPlayer = AudioPlayer::GetInstance();
    if (audioPlayer == nullptr) {
        MEDIA_ERR_LOG("audio player is null");
        return;
    }
    audioPlayer->DestoryPlayer();
    audioPlayer->ReleaseEventListeners();
    audioPlayer->StopUpdateTimeThread();
}

void AudioModule::DefineProperty(JSIValue target,
                                 const char *propName,
                                 JSIFunctionHandler getter,
                                 JSIFunctionHandler setter)
{
    JSPropertyDescriptor descriptor;
    descriptor.getter = getter;
    descriptor.setter = setter;
    JSI::DefineNamedProperty(target, propName, descriptor);
}

JSIValue AudioModule::Play(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->Play());
}

JSIValue AudioModule::Pause(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->Pause());
}

JSIValue AudioModule::Stop(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->Stop());
}

JSIValue AudioModule::GetPlayState(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
     if (argsSize < 1) {
        MEDIA_ERR_LOG("1 argument is required.");
        return JSI::CreateBoolean(false);
    }

    JSIValue options = args[0];
    if (!JSI::ValueIsObject(options)) {
        MEDIA_ERR_LOG("invalid parameter.");
        return JSI::CreateBoolean(false);
    }

    JSIValue successCallback = JSI::GetNamedProperty(options, PROP_SUCCESS);
    if (!JSI::ValueIsUndefined(successCallback)) {
        AudioPlayer *audioPlayer = AudioPlayer::GetInstance();
        JSIValue data = JSI::CreateObject();
        JSI::SetStringProperty(data, "status", audioPlayer->GetStatus());
        JSI::SetStringProperty(data, "src", audioPlayer->GetSrc());
        JSI::SetNumberProperty(data, "currentTime", audioPlayer->GetCurrentTime());
        JSI::SetBooleanProperty(data, "autoplay", audioPlayer->GetAutoPlay());
        JSI::SetBooleanProperty(data, "loop", audioPlayer->IsLooping());
        JSI::SetNumberProperty(data, "volume", audioPlayer->GetVolume());
        JSI::SetBooleanProperty(data, "muted", audioPlayer->IsMuted());
        JSIValue params[1] = { data };
        JSI::CallFunction(successCallback, thisVal, params, 1);
        JSI::ReleaseValue(successCallback);
    }

    JSIValue completeCallback = JSI::GetNamedProperty(options, PROP_COMPLETE);
    if (!JSI::ValueIsUndefined(completeCallback)) {
        JSI::CallFunction(completeCallback, thisVal, nullptr, 0);
        JSI::ReleaseValue(completeCallback);
    }

    return JSI::CreateUndefined();
}

JSIValue AudioModule::SrcGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    char *src = AudioPlayer::GetInstance()->GetSrc();
    return (src == nullptr) ? JSI::CreateUndefined() : JSI::CreateString(src);
}

JSIValue AudioModule::SrcSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    if (argsSize < 1) {
        MEDIA_ERR_LOG("1 argument is required.");
        return JSI::CreateBoolean(false);
    }
    char *src = JSI::ValueToString(args[0]);
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->SetSrc(src));
}

JSIValue AudioModule::CurrentTimeGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return JSI::CreateNumber(AudioPlayer::GetInstance()->GetCurrentTime());
}

JSIValue AudioModule::CurrentTimeSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    if (argsSize < 1) {
        MEDIA_ERR_LOG("1 argument is required.");
        return JSI::CreateBoolean(false);
    }

    int64_t currentTime = static_cast<int64_t>(JSI::ValueToNumber(args[0]));
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->SetCurrentTime(currentTime));
}

JSIValue AudioModule::DurationGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    int64_t duation = AudioPlayer::GetInstance()->GetDuration();
    return duation == -1 ? JSI::CreateNumberNaN() : JSI::CreateNumber(static_cast<double>(duation));
}

JSIValue AudioModule::DurationSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return JSI::CreateError(JsiErrorType::JSI_ERROR_COMMON, "duration is readonly.");
}

JSIValue AudioModule::AutoPlayGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->GetAutoPlay());
}

JSIValue AudioModule::AutoPlaySetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    if (argsSize < 1) {
        MEDIA_ERR_LOG("1 argument is required.");
        return JSI::CreateBoolean(false);
    }
    bool autoPlay = JSI::ValueToBoolean(args[0]);
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->SetAutoPlay(autoPlay));
}

JSIValue AudioModule::LoopGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->IsLooping());
}

JSIValue AudioModule::LoopSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    if (argsSize < 1) {
        MEDIA_ERR_LOG("1 argument is required.");
        return JSI::CreateBoolean(false);
    }

    bool loop = JSI::ValueToBoolean(args[0]);
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->SetLoop(loop));
}

JSIValue AudioModule::VolumeGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return JSI::CreateNumber(AudioPlayer::GetInstance()->GetVolume());
}

JSIValue AudioModule::VolumeSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    if (argsSize < 1) {
        MEDIA_ERR_LOG("1 argument is required.");
        return JSI::CreateBoolean(false);
    }
    float volume = static_cast<float>(JSI::ValueToNumber(args[0]));
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->SetVolume(volume));
}

JSIValue AudioModule::MutedGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->IsMuted());
}

JSIValue AudioModule::MutedSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    if (argsSize < 1) {
        MEDIA_ERR_LOG("1 argument is required.");
        return JSI::CreateBoolean(false);
    }
    bool muted = JSI::ValueToBoolean(args[0]);
    return JSI::CreateBoolean(AudioPlayer::GetInstance()->SetMuted(muted));
}

JSIValue AudioModule::OnPlayGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return GetEventCallback(AudioPlayer::GetInstance()->GetOnPlayListener());
}

JSIValue AudioModule::OnPlaySetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    AudioEventListener *listener = CreateAudioEventListener(args, argsSize);
    if (listener == nullptr) {
        return JSI::CreateBoolean(false);
    }
    AudioPlayer::GetInstance()->SetOnPlayListener(listener);
    return JSI::CreateBoolean(true);
}

JSIValue AudioModule::OnPauseGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return GetEventCallback(AudioPlayer::GetInstance()->GetOnPauseListener());
}

JSIValue AudioModule::OnPauseSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    AudioEventListener *listener = CreateAudioEventListener(args, argsSize);
    if (listener == nullptr) {
        return JSI::CreateBoolean(false);
    }
    AudioPlayer::GetInstance()->SetOnPauseListener(listener);
    return JSI::CreateBoolean(true);
}

JSIValue AudioModule::OnStopGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return GetEventCallback(AudioPlayer::GetInstance()->GetOnStopListener());
}

JSIValue AudioModule::OnStopSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    AudioEventListener *listener = CreateAudioEventListener(args, argsSize);
    if (listener == nullptr) {
        return JSI::CreateBoolean(false);
    }
    AudioPlayer::GetInstance()->SetOnStopListener(listener);
    return JSI::CreateBoolean(true);
}

JSIValue AudioModule::OnLoadedDataGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return GetEventCallback(AudioPlayer::GetInstance()->GetOnLoadedDataListener());
}

JSIValue AudioModule::OnLoadedDataSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    AudioEventListener *listener = CreateAudioEventListener(args, argsSize);
    if (listener == nullptr) {
        return JSI::CreateBoolean(false);
    }
    AudioPlayer::GetInstance()->SetOnLoadedDataListener(listener);
    return JSI::CreateBoolean(true);
}

JSIValue AudioModule::OnEndedGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return GetEventCallback(AudioPlayer::GetInstance()->GetOnEndedListener());
}

JSIValue AudioModule::OnEndedSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    AudioEventListener *listener = CreateAudioEventListener(args, argsSize);
    if (listener == nullptr) {
        return JSI::CreateBoolean(false);
    }
    AudioPlayer::GetInstance()->SetOnEndedListener(listener);
    return JSI::CreateBoolean(true);
}

JSIValue AudioModule::OnErrorGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return GetEventCallback(AudioPlayer::GetInstance()->GetOnErrorListener());
}

JSIValue AudioModule::OnErrorSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    AudioEventListener *listener = CreateAudioEventListener(args, argsSize);
    if (listener == nullptr) {
        return JSI::CreateBoolean(false);
    }
    AudioPlayer::GetInstance()->SetOnErrorListener(listener);
    return JSI::CreateBoolean(true);
}

JSIValue AudioModule::OnTimeUpdateGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    return GetEventCallback(AudioPlayer::GetInstance()->GetOnTimeUpdateListener());
}

JSIValue AudioModule::OnTimeUpdateSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize)
{
    AudioEventListener *listener = CreateAudioEventListener(args, argsSize);
    if (listener == nullptr) {
        return JSI::CreateBoolean(false);
    }
    AudioPlayer::GetInstance()->SetOnTimeUpdateListener(listener);
    return JSI::CreateBoolean(true);
}

JSIValue AudioModule::GetEventCallback(const AudioEventListener *listener)
{
    return (listener == nullptr) ? JSI::CreateUndefined() : listener->GetCallback();
}

AudioEventListener *AudioModule::CreateAudioEventListener(const JSIValue *args, uint8_t argsSize)
{
    if (argsSize < 1) {
        MEDIA_ERR_LOG("1 argument is required.");
        return nullptr;
    }

    JSIValue callback = args[0];
    if (!JSI::ValueIsFunction(callback)) {
        MEDIA_ERR_LOG("a function is required.");
        return nullptr;
    }

    AudioEventListener *listener = new AudioEventListener(callback);
    if (listener == nullptr) {
        MEDIA_ERR_LOG("out of memory.");
    }

    return listener;
}

void InitAudioModule(JSIValue exports)
{
    AudioPlayer::GetInstance()->CreatePlayer();
    AudioPlayer::GetInstance()->ForkUpdateTimeThread();

    JSI::SetOnTerminate(exports, AudioModule::OnTerminate);
    JSI::SetModuleAPI(exports, "play", AudioModule::Play);
    JSI::SetModuleAPI(exports, "pause", AudioModule::Pause);
    JSI::SetModuleAPI(exports, "stop", AudioModule::Stop);
    JSI::SetModuleAPI(exports, "getPlayState", AudioModule::GetPlayState);

    AudioModule::DefineProperty(exports, "src", AudioModule::SrcGetter, AudioModule::SrcSetter);
    AudioModule::DefineProperty(exports, "currentTime", AudioModule::CurrentTimeGetter, AudioModule::CurrentTimeSetter);
    AudioModule::DefineProperty(exports, "duration", AudioModule::DurationGetter, AudioModule::DurationSetter);
    AudioModule::DefineProperty(exports, "autoplay", AudioModule::AutoPlayGetter, AudioModule::AutoPlaySetter);
    AudioModule::DefineProperty(exports, "loop", AudioModule::LoopGetter, AudioModule::LoopSetter);
    AudioModule::DefineProperty(exports, "volume", AudioModule::VolumeGetter, AudioModule::VolumeSetter);
    AudioModule::DefineProperty(exports, "muted", AudioModule::MutedGetter, AudioModule::MutedSetter);

    AudioModule::DefineProperty(exports, "onplay", AudioModule::OnPlayGetter, AudioModule::OnPlaySetter);
    AudioModule::DefineProperty(exports, "onpause", AudioModule::OnPauseGetter, AudioModule::OnPauseSetter);
    AudioModule::DefineProperty(exports, "onstop", AudioModule::OnStopGetter, AudioModule::OnStopSetter);
    AudioModule::DefineProperty(exports, "onloadeddata", AudioModule::OnLoadedDataGetter,
                                AudioModule::OnLoadedDataSetter);
    AudioModule::DefineProperty(exports, "onended", AudioModule::OnEndedGetter, AudioModule::OnEndedSetter);
    AudioModule::DefineProperty(exports, "onerror", AudioModule::OnErrorGetter, AudioModule::OnErrorSetter);
    AudioModule::DefineProperty(exports, "ontimeupdate", AudioModule::OnTimeUpdateGetter,
                                AudioModule::OnTimeUpdateSetter);
}
} // namespace ACELite
} // namespace OHOS