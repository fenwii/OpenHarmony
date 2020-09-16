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

#ifndef PLAYER_AUDIO_SINK_H
#define PLAYER_AUDIO_SINK_H

#include <memory>
#include <vector>
#include <mutex>
#include "player_sink_type.h"
#include "player_define.h"
#include "codec_type.h"
#include "player_sync.h"
#include "audio_manager.h"

using namespace std;

namespace OHOS {
namespace Media {
class PlayerSync;
class AudioSink {
public:
    AudioSink();
    ~AudioSink();
    int32_t Init(SinkAttr &atrr);
    void DeInit(void);
    int32_t Start(void);
    int32_t Stop(void);
    int32_t Flush(void);
    int32_t Reset(void);
    int32_t Pause(void);
    int32_t Resume(void);
    int32_t SetSpeed(float speed);
    int32_t GetSpeed(float &speed);
    int32_t GetState(int32_t &state);
    int32_t RenderFrame(OutputInfo &frame);
    int32_t SetRenderMode();
    int32_t SetVolume(float left, float right);
    int32_t GetVolume(float &left, float &right);
    int32_t SetMute(bool mute);
    int32_t GetMute(bool &mute);
    void SetSync(PlayerSync *sync);
    int32_t SetParam(const char *key, dataType type, void* value);
    int32_t GetParam(const char *key, dataType type, void* value);
    int32_t RegisterCallBack(PlayEventCallback &callback);
    void GetStatus(AudioSinkStatus &status);
    void RenderEos(void);
    int DequeReleaseFrame(OutputInfo &frame);
    void GetRenderPosition(int64_t &position);

private:
    void ResetRendStartTime();
    void SendAudioEndOfStream();
    void UpdateAudioPts(int64_t& timestamp, int64_t currentPts);
    int GetRenderFrame(OutputInfo &renderFrame, OutputInfo &frame);
    void RelaseQueHeadFrame(void);
    void RelaseQueAllFrame(void);
    void RenderRptEvent(EventCbType event);
    int32_t WriteToAudioDevice(OutputInfo &renderFrame);

    bool started_;
    bool paused_;
    bool eosSended_;
    int64_t rendFrameCnt_;
    int64_t lastRendFrameCnt_;
    bool pauseAfterPlay_;
    SinkAttr attr_;
    SinkState m_state;
    PlayerSync *syncHdl_;
    RenderMode m_playMode;
    int64_t m_rendStartTime;
    int64_t m_lastRendPts;
    int64_t m_lastRendSysTimeMs;
    PlayEventCallback callBack_;
    float m_leftVolume_;
    float m_rightVolume_;
    int64_t eosPts_;
    bool receivedEos;
    std::mutex mutex_;
    std::vector<OutputInfo> frameCacheQue_;
    std::vector<OutputInfo> frameReleaseQue_;
    struct AudioManager *audioManager_;
    struct AudioAdapter *audioAdapter_;
    struct AudioRender *audioRender_;
    AudioPort renderPort_ = {};
};
}  // namespace Media
}  // namespace OHOS

#endif  // PLAYER_SINK_H
