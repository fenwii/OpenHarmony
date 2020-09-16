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

#ifndef AUDIO_MODULE_H
#define AUDIO_MODULE_H

#include "audio_player.h"

namespace OHOS {
namespace ACELite {
class AudioModule final : public MemoryHeap {
public:
    /**
     * constructor
     */
    AudioModule() = default;

    /**
     * desconstructor
     */
    ~AudioModule() = default;

    /**
     * Set volume, 0.0 means the no silcence, 1.0 means the original volume.
     *
     * @param volume Indicates the target volume to set, which ranges from 0.0 to 1.0
     * @return Returns {@code true} if setting is successful; returns {@code false} otherwise.
     */
    static bool SetVolume(float volume);

    /**
     * Call when the app is terminated
     */
    static void OnTerminate();

    /**
     * define property
     */
    static void
        DefineProperty(JSIValue target, const char *propName, JSIFunctionHandler getter, JSIFunctionHandler setter);

    /**
     * the play method of audio
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue Play(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the pause method of audio
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue Pause(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the stop method of audio
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue Stop(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getPlayState method of audio
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue GetPlayState(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio src property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue SrcGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio src property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue SrcSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio currentTime property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue CurrentTimeGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio currentTime property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue CurrentTimeSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio duration property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue DurationGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio duration property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue DurationSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio autoplay property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue AutoPlayGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio autoplay property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue AutoPlaySetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio loop property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue LoopGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio loop property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue LoopSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio volume property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue VolumeGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio volume property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue VolumeSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio muted property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue MutedGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio muted property
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue MutedSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio onplay event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnPlayGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio onplay event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnPlaySetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio onpause event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnPauseGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio onpause event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnPauseSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio onstop event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnStopGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio onstop event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnStopSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio onloadeddata event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnLoadedDataGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio onloadeddata event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnLoadedDataSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio onerror event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnEndedGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio onerror event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnEndedSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio onerror event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnErrorGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio onerror event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnErrorSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the getter of audio ontimeupdate event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnTimeUpdateGetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

    /**
     * the setter of audio ontimeupdate event
     *
     * @param thisVal Indicates function execute context
     * @param args Indicates the function arguments
     * @param argsSize Indicates the size of function arguments
     */
    static JSIValue OnTimeUpdateSetter(const JSIValue thisVal, const JSIValue *args, uint8_t argsSize);

private:
    static JSIValue GetEventCallback(const AudioEventListener *listener);

    static AudioEventListener *CreateAudioEventListener(const JSIValue *args, uint8_t argsSize);
};

void InitAudioModule(JSIValue exports);
} // namespace ACELite
} // namespace OHOS
#endif // AUDIO_MODULE_H