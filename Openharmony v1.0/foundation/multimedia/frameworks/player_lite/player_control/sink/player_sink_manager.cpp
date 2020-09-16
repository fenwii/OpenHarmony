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

#include "player_sink_manager.h"
#include <sys/time.h>
#include "media_log.h"

namespace OHOS {
namespace Media {
#define SS2US  1000000
#define US2NS  1000
#define US2MS  1000

int64_t GetCurTimeUs()
{
    struct timespec ts = { 0, 0 };
    (void)clock_gettime(CLOCK_MONOTONIC, &ts);
    return (((int64_t)ts.tv_sec) * SS2US) + (((int64_t)ts.tv_nsec) / US2NS);
}

static int64_t GetCurTimeMs()
{
    int64_t curTimeUs = GetCurTimeUs();
    return (curTimeUs / US2MS);
}

SinkManager::SinkManager()
    : m_inited_(false), m_speed_(1.0f), m_tplayDirect_(TPLAY_DIRECT_BUTT),
      m_leftVolume_(0.0f), m_rightVolume_(0.0f), m_paused_(false), m_started_(false),
      pauseAfterPlay_(false), vidRendStartTime_(-1), lastVidRendSysTimeMs_(-1), m_audioSinkNum_(0),
      m_videoSinkNum_(0), sync_(nullptr), recieveAudioEos_(false), recieveVideoEos_(false)
{
    callBack_ = {};
    m_audioSinkInfo_[0] = {};
    m_audioSinkInfo_[1] = {};
    m_videoSinkInfo_[0] = {};
    m_videoSinkInfo_[1] = {};
}

SinkManager::~SinkManager()
{
}

int32_t SinkManager::AddNewSink(SinkAttr &attr)
{
    if (sync_ == nullptr) {
        sync_ = std::make_shared<PlayerSync>();
    }
    if (sync_ == nullptr) {
        MEDIA_ERR_LOG("make_shared failed.");
        return -1;
    }
    sync_->Init();
    if (attr.sinkType == SINK_TYPE_AUDIO) {
        if (m_audioSinkNum_ >= MAX_PIPELINE_SINK_NUM) {
            return -1;
        }
        m_audioSinkInfo_[m_audioSinkNum_].trackId = attr.trackId;
        m_audioSinkInfo_[m_audioSinkNum_].audAttr = attr.audAttr;
        m_audioSinkInfo_[m_audioSinkNum_].sink = std::make_shared<AudioSink>();
        m_audioSinkInfo_[m_audioSinkNum_].sink->Init(attr);
        m_audioSinkInfo_[m_audioSinkNum_].sink->SetSync(sync_.get());
        m_audioSinkNum_++;
    } else if (attr.sinkType == SINK_TYPE_VIDEO) {
        if (m_videoSinkNum_ >= MAX_PIPELINE_SINK_NUM) {
            return -1;
        }
        m_videoSinkInfo_[m_videoSinkNum_].trackId = attr.trackId;
        m_videoSinkInfo_[m_videoSinkNum_].vidAttr = attr.vidAttr;
        m_videoSinkInfo_[m_videoSinkNum_].sink = std::make_shared<VideoSink>();
        m_videoSinkInfo_[m_videoSinkNum_].sink->Init(attr);
        m_videoSinkInfo_[m_videoSinkNum_].sink->SetSync(sync_.get());
        m_videoSinkNum_++;
    }
    return 0;
}


int32_t SinkManager::Start(void)
{
    int32_t i;

    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_videoSinkInfo_[i].sink != nullptr) {
            m_videoSinkInfo_[i].sink->Start();
        }
    }

    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_audioSinkInfo_[i].sink != nullptr) {
            m_audioSinkInfo_[i].sink->Start();
        }
    }
    if (sync_ != nullptr) {
        sync_->Start(SYNC_CHN_VID);
        sync_->Start(SYNC_CHN_AUD);
    }
    m_started_ = true;
    return HI_SUCCESS;
}

int32_t SinkManager::Flush(void)
{
    int32_t i;
    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_videoSinkInfo_[i].sink != nullptr) {
            m_videoSinkInfo_[i].sink->Flush();
        }
    }

    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_audioSinkInfo_[i].sink != nullptr) {
            m_audioSinkInfo_[i].sink->Flush();
        }
    }
    return 0;
}

int32_t SinkManager::Reset(void)
{
    int32_t i;
    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_videoSinkInfo_[i].sink != nullptr) {
            m_videoSinkInfo_[i].sink->Reset();
        }
    }

    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_audioSinkInfo_[i].sink != nullptr) {
            m_audioSinkInfo_[i].sink->Reset();
        }
    }
    return 0;
}

void SinkManager::ResetRendStartTime()
{
    vidRendStartTime_ = AV_INVALID_PTS;
}

int32_t SinkManager::Pause()
{
    MEDIA_INFO_LOG("process in");
    if (m_paused_ == true) {
        MEDIA_ERR_LOG("avRender already paused");
        return HI_SUCCESS;
    }
    if (m_started_ == false) {
        MEDIA_ERR_LOG("not in running");
        return -1;
    }
    for (int32_t i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_audioSinkInfo_[i].sink != nullptr) {
            m_audioSinkInfo_[i].sink->Pause();
        }
    }
    if (sync_ != nullptr) {
        sync_->Reset(SYNC_CHN_VID);
        sync_->Reset(SYNC_CHN_AUD);
    }
    ResetRendStartTime();
    m_paused_ = true;
    return 0;
}

int32_t SinkManager::Resume()
{
    MEDIA_INFO_LOG("process in");
    if (sync_ != nullptr) {
        sync_->Resume();
    }
    for (int32_t i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_audioSinkInfo_[i].sink != nullptr) {
            m_audioSinkInfo_[i].sink->Resume();
        }
    }
    pauseAfterPlay_ = false;
    if (m_paused_ == false) {
        MEDIA_ERR_LOG("avRender not in pause");
        return HI_FAILURE;
    }
    vidRendStartTime_ = GetCurTimeMs();
    lastVidRendSysTimeMs_ = GetCurTimeMs();
#if (defined __HI3516CV300__)
    m_lastAudRendSysTimeMs = 0;
#endif
    m_paused_ = false;

    return 0;
}

int32_t SinkManager::TplayToNormal(void)
{
    int32_t ret;

    ret = Pause();
    if (ret != 0) {
        MEDIA_ERR_LOG("m_render pause  failed Ret: %d", ret);
        return ret;
    }
    ret = sync_->Resume();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("m_syncHdl Resume  failed Ret: %d", ret);
        return ret;
    }

    ret = sync_->Reset(SYNC_CHN_VID);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("m_syncHdl  Reset vid Ret: %d", ret);
        return ret;
    }
    ret = sync_->Reset(SYNC_CHN_AUD);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("m_syncHdl  Reset aud Ret: %d", ret);
        return ret;
    }
    ret = Resume();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("m_render resume  failed Ret: %d", ret);
        return ret;
    }
    m_speed_ = 1.0;
    m_tplayDirect_ = TPLAY_DIRECT_BUTT;
    return 0;
}

int32_t SinkManager::Tplay(float speed, TplayDirect  tplayDirect)
{
    int32_t ret;

    ret = Pause();
    if (ret != 0) {
        MEDIA_ERR_LOG("m_render pause  failed Ret: %d", ret);
        return ret;
    }
    ret = sync_->SetSpeed(speed, tplayDirect);
    if (ret != 0) {
        MEDIA_ERR_LOG("m_syncHdl  TPlay Ret: %d", ret);
        return ret;
    }
    ret = Resume();
    if (ret != 0) {
        MEDIA_ERR_LOG("m_render resume  failed Ret: %d", ret);
        return ret;
    }
    m_speed_ = speed;
    m_tplayDirect_ = tplayDirect;
    return 0;
}

int32_t SinkManager::SetSpeed(float speed, TplayDirect  tplayDirect)
{
    if (m_speed_ == speed) {
        return 0;
    }
    if (speed == 1) { /* tplay ---> normal */
        TplayToNormal();
    } else { /* tplay / ormal ---> tplay */
        Tplay(speed, tplayDirect);
    }
    return 0;
}

int32_t SinkManager::GetSpeed(float &speed, TplayDirect  &tplayDirect)
{
    speed = m_speed_;
    tplayDirect = m_tplayDirect_;
    return 0;
}

int32_t SinkManager::RenderFrame(OutputInfo &frame)
{
    int ret;
    if (frame.type == AUDIO_DECODER) {
        ret = m_audioSinkInfo_[0].sink->RenderFrame(frame);
    } else if (frame.type == VIDEO_DECODER) {
        ret = m_videoSinkInfo_[0].sink->RenderFrame(frame);
    } else {
        MEDIA_ERR_LOG("RenderFrame not support frame type: %d", frame.type);
        ret = -1;
    }
    return ret;
}

void SinkManager::SetRenderMode(RenderMode mode)
{
    if (m_videoSinkInfo_[0].sink != nullptr) {
        m_videoSinkInfo_[0].sink->SetRenderMode(mode);
    }
}

int32_t SinkManager::SetVolume(float left, float right)
{
    int i;

    m_leftVolume_ = left;
    m_rightVolume_ = right;
    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_audioSinkInfo_[i].sink != nullptr) {
            m_audioSinkInfo_[i].sink->SetVolume(left, right);
        }
    }
    return HI_SUCCESS;
}

int32_t SinkManager::GetVolume(float &left, float &right)
{
    left = m_leftVolume_;
    right = m_rightVolume_;
    return 0;
}


int32_t SinkManager::Stop(void)
{
    int32_t i;

    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_audioSinkInfo_[i].sink != nullptr) {
            m_audioSinkInfo_[i].sink->Stop();
        }
    }
    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_videoSinkInfo_[i].sink != nullptr) {
            m_videoSinkInfo_[i].sink->Stop();
        }
    }
    if (sync_ != nullptr) {
        sync_->Stop(SYNC_CHN_VID);
        sync_->Stop(SYNC_CHN_AUD);
    }
    m_started_ = false;
    return 0;
}

int32_t SinkManager::RegisterCallBack(PlayEventCallback &callback)
{
    int32_t i;
    callBack_ = callback;
    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_audioSinkInfo_[i].sink != nullptr) {
            m_audioSinkInfo_[i].sink->RegisterCallBack(callback);
        }
    }
    for (i = 0; i < MAX_PIPELINE_SINK_NUM; i++) {
        if (m_videoSinkInfo_[i].sink != nullptr) {
            m_videoSinkInfo_[i].sink->RegisterCallBack(callback);
        }
    }
    return 0;
}

int32_t SinkManager::GetStatus(PlayerStreamInfo &streamInfo)
{
    if (m_audioSinkInfo_[0].sink != nullptr) {
        AudioSinkStatus audioStatus;
        m_audioSinkInfo_[0].sink->GetStatus(audioStatus);
        streamInfo.avStatus.audFrameCount = audioStatus.audFrameCount;
    }
    if (m_videoSinkInfo_[0].sink != nullptr) {
        VideoSinkStatus videoStatus;
        m_videoSinkInfo_[0].sink->GetStatus(videoStatus);
        streamInfo.avStatus.vidFrameCount = videoStatus.vidFrameCount;
        streamInfo.videoInfo.decHeight = videoStatus.decHeight;
        streamInfo.videoInfo.decWidth = videoStatus.decWidth;
        streamInfo.videoInfo.fpsDecimal = videoStatus.fpsDecimal;
        streamInfo.videoInfo.fpsInteger = videoStatus.fpsInteger;
    }

    streamInfo.avStatus.syncStatus.lastAudPts = AV_INVALID_PTS;
    streamInfo.avStatus.syncStatus.lastVidPts = AV_INVALID_PTS;
    if (sync_ != nullptr) {
        sync_->GetStatus(streamInfo.avStatus.syncStatus);
    }
    return 0;
}

int32_t SinkManager::SetParam(const char *key, dataType type, void* value)
{
    return 0;
}

int32_t SinkManager::GetParam(const char *key, dataType *type, void** value, int32_t *size)
{
    return 0;
}

void SinkManager::RenderEos(bool isAudio)
{
    if (m_audioSinkInfo_[0].sink != nullptr && isAudio == true) {
        m_audioSinkInfo_[0].sink->RenderEos();
        recieveAudioEos_ = true;
    }
    if (m_videoSinkInfo_[0].sink != nullptr && isAudio == false) {
        m_videoSinkInfo_[0].sink->RenderEos();
        recieveVideoEos_ = true;
    }
}

int32_t SinkManager::DequeReleaseFrame(bool audioSink, OutputInfo &frame)
{
    if (m_audioSinkInfo_[0].sink != nullptr && audioSink == true) {
        return m_audioSinkInfo_[0].sink->DequeReleaseFrame(frame);
    }
    if (m_videoSinkInfo_[0].sink != nullptr && audioSink == false) {
        return m_videoSinkInfo_[0].sink->DequeReleaseFrame(frame);
    }
    return -1;
}

void SinkManager::GetRenderPosition(int64_t &position)
{
    if (m_audioSinkInfo_[0].sink != nullptr && (recieveAudioEos_ != true || m_videoSinkInfo_[0].sink == nullptr)) {
        m_audioSinkInfo_[0].sink->GetRenderPosition(position);
    } else if (m_videoSinkInfo_[0].sink != nullptr && (recieveVideoEos_ != true || m_audioSinkInfo_[0].sink == nullptr)) {
        m_videoSinkInfo_[0].sink->GetRenderPosition(position);
    } else if (recieveVideoEos_ == true && recieveAudioEos_ == true) {
        int64_t audioPos;
        int64_t videoPos;
        m_audioSinkInfo_[0].sink->GetRenderPosition(audioPos);
        m_videoSinkInfo_[0].sink->GetRenderPosition(videoPos);
        position = (audioPos >= videoPos) ? audioPos : videoPos;
    }
}
}
}
