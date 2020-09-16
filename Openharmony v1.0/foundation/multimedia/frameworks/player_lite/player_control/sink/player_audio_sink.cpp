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

#include "player_audio_sink.h"
#include "player_sync.h"
#include "media_log.h"
#include <unistd.h>
#include <cmath>
#include <sys/time.h>

namespace OHOS {
namespace Media {
#define CHECK_FAILED_RETURN(value, target, ret, printfString) \
do { \
    if ((value) != (target)) { \
        MEDIA_ERR_LOG(" %s ", (printfString != nullptr) ? (printfString) : " "); \
        return (ret); \
    } \
} while (0)

#define CHECK_NULL_RETURN(value, ret, printfString) \
do { \
    if ((value) == nullptr) { \
        MEDIA_ERR_LOG(" %s ", (printfString != nullptr) ? (printfString) : " "); \
        return (ret); \
    } \
} while (0)

const int32_t HALF_FACTOR = 2;
const int32_t MAX_QUEUE_BUF_NUM = 32;
const int32_t MAX_AUDIO_ADAPTER_NUM = 2;
const int32_t RENDER_BUF_FULL = 0xa016800f;

AudioSink::AudioSink()
    : started_(false), paused_(false), eosSended_(false), rendFrameCnt_(0), lastRendFrameCnt_(0),
      pauseAfterPlay_(false), m_state(SINK_STATE_IDLE), syncHdl_(nullptr), m_playMode(RENDER_MODE_NORMAL),
      m_rendStartTime(-1), m_lastRendPts(AV_INVALID_PTS), m_lastRendSysTimeMs(-1),
      m_leftVolume_(0.0f), m_rightVolume_(0.0f), eosPts_(AV_INVALID_PTS), receivedEos(false), audioManager_(nullptr),
      audioAdapter_(nullptr), audioRender_(nullptr)
{
    ResetRendStartTime();
    frameCacheQue_.clear();
    frameReleaseQue_.clear();
    callBack_ = {};
    attr_ = {};
}

AudioSink::~AudioSink()
{
    DeInit();
}

void AudioSink::DeInit()
{
    started_ = false;
    if (frameCacheQue_.size() != 0 || frameReleaseQue_.size()) {
        MEDIA_ERR_LOG("frames should be released before DeInit!!!");
    }
    if (audioRender_ != nullptr) {
        audioAdapter_->DestroyRender(audioAdapter_, audioRender_);
    }
    if (audioManager_ != nullptr) {
        MEDIA_ERR_LOG("audioAdapter_ UnloadModule not null");
        audioManager_->UnloadAdapter(audioManager_, audioAdapter_);
    }
    frameCacheQue_.clear();
    frameReleaseQue_.clear();
}

int32_t AudioSink::Init(SinkAttr &atrr)
{
    attr_ = atrr;
    audioManager_ = GetAudioManagerFuncs();
    if (audioManager_ == nullptr) {
        return SINK_GET_DEVICE_FAILED;
    }
    int32_t ret = 0;
    int32_t size = -1;
    struct AudioAdapterDescriptor *descs = nullptr;
    audioManager_->GetAllAdapters(audioManager_, &descs, &size);
    if (size > MAX_AUDIO_ADAPTER_NUM) {
        return SINK_GET_DEVICE_FAILED;
    }
    for (int index = 0; index < size; index++) {
        struct AudioAdapterDescriptor *desc = &descs[index];
        for (int port = 0; (desc != nullptr && port < static_cast<int>(desc->portNum)); port++) {
            if (desc->ports[port].dir == PORT_OUT &&
                (audioManager_->LoadAdapter(audioManager_, desc, &audioAdapter_)) == 0) {
                (void)audioAdapter_->InitAllPorts(audioAdapter_);
                if (memcpy_s(&renderPort_, sizeof(struct AudioPort),
                    &desc->ports[port], sizeof(struct AudioPort)) != 0) {
                    MEDIA_ERR_LOG("memcpy_s failed");
                }
                break;
            }
        }
    }
    if (ret != 0 || audioAdapter_ == nullptr) {
        MEDIA_ERR_LOG("load audiodevice failed");
        return SINK_LAOD_DEVICE_FAILED;
    }

    struct AudioSampleAttributes param;
    param.sampleRate = attr_.audAttr.sampleRate;
    param.format = AUDIO_FORMAT_PCM_16_BIT;
    param.channelCount = attr_.audAttr.channel;
    param.interleaved = false;
    MEDIA_INFO_LOG(" sampleRate:%d, channelCount:%d", param.sampleRate, param.channelCount);

    struct AudioDeviceDescriptor deviceDesc;
    deviceDesc.portId = 0;
    deviceDesc.pins = PIN_OUT_SPEAKER;
    deviceDesc.desc = nullptr;
    ret = audioAdapter_->CreateRender(audioAdapter_, &deviceDesc, &param, &audioRender_);
    if (ret != 0 || audioRender_ == nullptr) {
        MEDIA_ERR_LOG("AudioDeviceCreateRender failed");
        return SINK_OPEN_STREAM_FAILED;
    }
    MEDIA_ERR_LOG("init success");
    return SINK_SUCCESS;
}

void AudioSink::ResetRendStartTime()
{
    lastRendFrameCnt_ = 0;
    m_lastRendPts = AV_INVALID_PTS;
    m_rendStartTime = AV_INVALID_PTS;
}

void AudioSink::GetStatus(AudioSinkStatus &status)
{
    status.audFrameCount = rendFrameCnt_;
}

void AudioSink::UpdateAudioPts(int64_t& timestamp, int64_t currentPts)
{
    timestamp = currentPts;
}

int32_t AudioSink::GetRenderFrame(OutputInfo &renderFrame, OutputInfo &frame)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret = SINK_QUE_EMPTY;
    if (frame.type == AUDIO_DECODER &&  frame.bufferCnt != 0) {
        frameCacheQue_.push_back(frame);
    }
    if (frameCacheQue_.size() != 0) {
        renderFrame = frameCacheQue_[0];
        ret = SINK_SUCCESS;
    }
    return ret;
}

void AudioSink::RelaseQueHeadFrame(void)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (frameCacheQue_.size() != 0) {
        OutputInfo frame = frameCacheQue_[0];
        frameCacheQue_.erase(frameCacheQue_.begin());
        frameReleaseQue_.push_back(frame);
    }
}

void AudioSink::RelaseQueAllFrame(void)
{
    size_t i;
    size_t queSize;
    std::lock_guard<std::mutex> lock(mutex_);
    queSize = frameCacheQue_.size();
    if (queSize > MAX_QUEUE_BUF_NUM) {
        return;
    }
    for (i = 0; i < queSize; i++) {
        frameReleaseQue_.push_back(frameCacheQue_[i]);
    }
    frameCacheQue_.clear();
}

int32_t AudioSink::DequeReleaseFrame(OutputInfo &frame)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (frameReleaseQue_.size() == 0) {
        return SINK_QUE_EMPTY;
    }
    frame = frameReleaseQue_[0];
    frameReleaseQue_.erase(frameReleaseQue_.begin());
    return SINK_SUCCESS;
}

void AudioSink::RenderRptEvent(EventCbType event)
{
    if (callBack_.onEventCallback != nullptr) {
        if (event == EVNET_AUDIO_PLAY_EOS && eosSended_) {
            return;
        }
        callBack_.onEventCallback(callBack_.priv, event, 0, 0);
        if (event == EVNET_AUDIO_PLAY_EOS) {
            eosSended_ = true;
        }
    }
}

int32_t AudioSink::WriteToAudioDevice(OutputInfo &renderFrame)
{
    int32_t ret;
    uint64_t writeLen = 0;
    if ((audioRender_ == nullptr) || (renderFrame.buffers == nullptr)) {
        RelaseQueHeadFrame();
        return HI_ERR_AVPLAY_AUDIO_REND_ERR;
    }

    ret = audioRender_->RenderFrame(audioRender_, (void*)&renderFrame, (uint64_t)renderFrame.buffers[0].length,
        &writeLen);
    if ((unsigned long)renderFrame.buffers[0].length != writeLen || ret == RENDER_BUF_FULL) {
        return SINK_RENDER_FULL;
    } else if (ret != HI_SUCCESS) {
        RelaseQueHeadFrame();
        MEDIA_ERR_LOG("RenderFrame failed ret: %x", ret);
        return HI_ERR_AVPLAY_AUDIO_REND_ERR;
    }
    RelaseQueHeadFrame();
    rendFrameCnt_++;
    return HI_SUCCESS;
}

int32_t AudioSink::RenderFrame(OutputInfo &frame)
{
    SyncRet syncRet = SYNC_RET_PLAY;
    int64_t crtPlayPts = 0;
    uint64_t frameCnt;
    OutputInfo renderFrame = {};
    struct AudioTimeStamp timestamp;
    CHECK_FAILED_RETURN(started_, true, SINK_RENDER_ERROR, "not started");
    CHECK_FAILED_RETURN(paused_, false, SINK_RENDER_ERROR, "paused");
    CHECK_NULL_RETURN(audioRender_, -1, "audio dev not inited");
    if (GetRenderFrame(renderFrame, frame) != SINK_SUCCESS) {
        if (receivedEos) {
            RenderRptEvent(EVNET_AUDIO_PLAY_EOS);
            return SINK_RENDER_EOS;
        }
        return SINK_QUE_EMPTY;
    }
    if (pauseAfterPlay_) {
        return SINK_SUCCESS;
    }
    int32_t ret = audioRender_->GetRenderPosition(audioRender_, &frameCnt, &timestamp);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("GetRenderPosition failed,ret=0x%x", ret);
        return SINK_RENDER_ERROR;
    }
    UpdateAudioPts(crtPlayPts, renderFrame.timeStamp);
    ret = (syncHdl_ != nullptr) ? syncHdl_->ProcAudFrame(crtPlayPts, syncRet) : HI_SUCCESS;
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("AVPLAY_SYNC_Proc_VidFrame pts: %lld failed", renderFrame.timeStamp);
        return SINK_RENDER_ERROR;
    }
    m_lastRendPts = renderFrame.timeStamp;
    if (syncRet == SYNC_RET_PLAY) {
        ret = WriteToAudioDevice(renderFrame);
    } else if (syncRet == SYNC_RET_DROP) {
        RelaseQueHeadFrame();
        ret = SINK_SUCCESS;
    } else if (syncRet == SYNC_RET_REPEAT) {
        ret = SINK_RENDER_DELAY;
    } else {
        MEDIA_ERR_LOG("aud invalid sync ret: %d", syncRet);
        RelaseQueHeadFrame();
        ret =  SINK_RENDER_ERROR;
    }
    return ret;
}

void AudioSink::RenderEos(void)
{
    receivedEos = true;
    eosPts_ = m_lastRendPts;
}

int32_t AudioSink::Start(void)
{
    if (!started_ && audioRender_ != nullptr) {
        audioRender_->control.Start((AudioHandle)audioRender_);
        started_ = true;
    }
    return SINK_SUCCESS;
}

int32_t AudioSink::SetVolume(float left, float right)
{
    float volume;
    CHECK_FAILED_RETURN(started_, true, -1, "not started");
    if (audioRender_ == nullptr) {
        MEDIA_ERR_LOG("AudioSink::SetVolume failed audioRender_ null");
        return -1;
    }

    m_leftVolume_ = left;
    m_rightVolume_ = right;
    if ((m_leftVolume_ == 0) && (m_rightVolume_ != 0)) {
        volume = m_rightVolume_;
    } else if ((m_leftVolume_ != 0) && (m_rightVolume_ == 0)) {
        volume = m_leftVolume_;
    } else {
        volume = (m_leftVolume_ + m_rightVolume_) / HALF_FACTOR;
    }
    audioRender_->volume.SetVolume(reinterpret_cast<AudioHandle>(audioRender_), volume);
    return SINK_SUCCESS;
}

int32_t AudioSink::GetVolume(float &left, float &right)
{
    left = m_leftVolume_;
    right = m_rightVolume_;
    return SINK_SUCCESS;
}

int32_t AudioSink::Stop(void)
{
    if (started_ && audioRender_ != nullptr) {
        audioRender_->control.Stop(reinterpret_cast<AudioHandle>(audioRender_));
    }
    RelaseQueAllFrame();
    rendFrameCnt_ = 0;
    started_ = false;
    paused_ = false;
    eosSended_ = false;
    return SINK_SUCCESS;
}

int32_t AudioSink::Pause(void)
{
    ResetRendStartTime();
    if (started_ && audioRender_ != nullptr) {
        audioRender_->control.Pause(reinterpret_cast<AudioHandle>(audioRender_));
    }
    paused_ = true;
    return SINK_SUCCESS;
}

int32_t AudioSink::Resume(void)
{
    CHECK_FAILED_RETURN(paused_, true, -1, "not paused");
    CHECK_NULL_RETURN(audioRender_, -1, "audioRender_ is null");
    audioRender_->control.Resume(reinterpret_cast<AudioHandle>(audioRender_));
    paused_ = false;
    return SINK_SUCCESS;
}

int32_t AudioSink::Reset(void)
{
    RelaseQueAllFrame();
    if (started_ && audioRender_ != nullptr) {
        audioRender_->control.Flush(reinterpret_cast<AudioHandle>(audioRender_));
    }
    ResetRendStartTime();
    return SINK_SUCCESS;
}

int32_t AudioSink::RegisterCallBack(PlayEventCallback &callback)
{
    callBack_ = callback;
    return SINK_SUCCESS;
}

void AudioSink::SetSync(PlayerSync *sync)
{
    syncHdl_ = sync;
}

int32_t AudioSink::Flush(void)
{
    if (started_ && audioRender_ != nullptr) {
        audioRender_->control.Flush(reinterpret_cast<AudioHandle>(audioRender_));
    }
    return 0;
}

void AudioSink::GetRenderPosition(int64_t &position)
{
    position = m_lastRendPts;
}
}
}
