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

#ifndef PLAYER_SINK_MANAGER_H
#define PLAYER_SINK_MANAGER_H

#include <memory>
#include <vector>
#include "player_sink_type.h"
#include "player_define.h"
#include "player_audio_sink.h"
#include "player_video_sink.h"
#include <string>

using namespace std;

namespace OHOS {
namespace Media {
struct SyncInfo {
    int32_t syncId;
    std::shared_ptr<PlayerSync> sync;
};

struct AudioSinkInfo {
    int32_t trackId;
    AudioSinkAttr audAttr;
    std::shared_ptr<AudioSink> sink;
};

struct VideoSinkInfo {
    int32_t trackId;
    int32_t syncId;
    VideoSinkAttr vidAttr;
    std::shared_ptr<VideoSink> sink;
};

struct SinkInfo {
    SinkType sinkType;
    int32_t trackId;
    union {
        AudioSinkInfo vidSink;
        AudioSinkInfo audSink;
    } param;
};

class SinkManager {
friend VideoSink;
friend AudioSink;

public:
    SinkManager();
    ~SinkManager();
    int32_t AddNewSink(SinkAttr &attr);
    int32_t Start(void);
    int32_t Stop(void);
    int32_t Flush(void);
    int32_t Reset(void);
    int32_t Pause(void);
    int32_t Resume(void);
    int32_t SetSpeed(float speed, TplayDirect  tplayDirect);
    int32_t GetSpeed(float &speed, TplayDirect  &tplayDirect);
    int32_t RenderFrame(OutputInfo &frame);
    int32_t SetVolume(float left, float right);
    int32_t GetVolume(float &left, float &right);
    int32_t SetParam(const char *key, dataType type, void* value);
    int32_t GetParam(const char *key, dataType *type, void** value, int32_t *size);
    void SetRenderMode(RenderMode mode);
    int32_t RegisterCallBack(PlayEventCallback &callback);
    int32_t GetStatus(PlayerStreamInfo &info);
    void RenderEos(bool isAudio);
    int DequeReleaseFrame(bool audioSink, OutputInfo &frame);
    void GetRenderPosition(int64_t &position);

private:
    int32_t Tplay(float speed, TplayDirect  tplayDirect);
    int32_t TplayToNormal(void);
    void ResetRendStartTime();

    bool m_inited_;
    float m_speed_;
    TplayDirect  m_tplayDirect_;
    float m_leftVolume_;
    float m_rightVolume_;
    bool m_paused_;
    bool m_started_;
    bool pauseAfterPlay_;
    int64_t vidRendStartTime_;
    int64_t lastVidRendSysTimeMs_;
    int32_t m_audioSinkNum_;
    int32_t m_videoSinkNum_;
    std::shared_ptr<PlayerSync> sync_;
    AudioSinkInfo m_audioSinkInfo_[MAX_PIPELINE_SINK_NUM];
    VideoSinkInfo m_videoSinkInfo_[MAX_PIPELINE_SINK_NUM];
    PlayEventCallback callBack_;
    bool recieveAudioEos_;
    bool recieveVideoEos_;
};
}  // namespace Media
}  // namespace OHOS

#endif  // PLAYER_SINK_MANAGER_H
