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

#include "recorder_audio_source.h"
#include "media_log.h"

namespace OHOS {
namespace Media {
const int64_t AUDIO_SOURCE_TIME_US_S = 1000000ULL;   /* us to s */
const int64_t AUDIO_SOURCE_TIME_NS_US = 1000ULL;     /* ns  to us  */

RecorderAudioSource::RecorderAudioSource()
    :audioCap_(new AudioCapturer()),
     framesize_(0),
     buffer_(nullptr),
     frameSeq_(0)
{
}

RecorderAudioSource::~RecorderAudioSource()
{
    if (buffer_) {
        delete buffer_;
        buffer_ = nullptr;
    }
}

int32_t RecorderAudioSource::Init(const RecorderAudioSourceConfig &sourceConfig)
{
    int32_t ret = 0;
    AudioCapturerInfo info;
    info.inputSource = sourceConfig.inputSource;
    info.audioFormat = sourceConfig.audioFormat;
    info.sampleRate = sourceConfig.sampleRate;
    info.channelCount = sourceConfig.channelCount;
    info.bitRate = sourceConfig.bitRate;
    info.streamType = TYPE_MEDIA;
    info.bitWidth = BIT_WIDTH_16;
    if ((ret = audioCap_->SetCapturerInfo(info)) != SUCCESS) {
        MEDIA_ERR_LOG("Can't SetCapturerInfo ret:x%x", ret);
        return ret;
    }
    uint64_t frameCnt = audioCap_->GetFrameCount();
    framesize_ = static_cast<uint32_t>(frameCnt * info.channelCount * info.bitWidth / sizeof(uint8_t));
    if (framesize_ == 0) {
        MEDIA_ERR_LOG("Can't get framesize");
        return ERR_UNKNOWN;
    }
    buffer_ = new (std::nothrow) uint8_t[framesize_];
    if (buffer_ == nullptr) {
        MEDIA_ERR_LOG("new buffer_ nullptr");
        return ERR_UNKNOWN;
    }
    MEDIA_DEBUG_LOG("framesize_ %d", framesize_);
    return SUCCESS;
}

int32_t RecorderAudioSource::Start()
{
    if (!audioCap_->Start()) {
        MEDIA_ERR_LOG("AudioCapturer Can't Start");
        return ERR_UNKNOWN;
    }
    return SUCCESS;
}

static int32_t Int64Multiple(int64_t firstNumber, int64_t secondeNumner, int64_t &result)
{
    if (secondeNumner == 0) {
        result = 0;
        return SUCCESS;
    }

    const int64_t int64Max = 0x7fffffffffffffff;
    if (firstNumber > (int64Max / secondeNumner)) {
        return ERR_INVALID_OPERATION;
    }
    result = firstNumber * secondeNumner;
    return SUCCESS;
}

int32_t RecorderAudioSource::AcquireBuffer(RecorderSourceBuffer &buffer, bool isBlocking)
{
    int32_t readLen = audioCap_->Read(buffer_, framesize_, isBlocking);
    if (readLen <= SUCCESS || readLen > static_cast<int32_t>(framesize_)) {
        MEDIA_ERR_LOG("audioCap Read failed ret:0x%x", readLen);
        return ERR_READ_BUFFER;
    }
    frameSeq_++;
    buffer.keyFrameFlag = false;
    buffer.dataAddr = buffer_;
    buffer.dataLen = readLen;
    buffer.dataSeq = frameSeq_;
    Timestamp timestamp;
    Timestamp::Timebase base = Timestamp::Timebase::MONOTONIC;
    if (!audioCap_->GetAudioTime(timestamp, base)) {
        MEDIA_ERR_LOG("AudioCapturer Can't GetAudioTime ");
        return ERR_READ_BUFFER;
    }
    int64_t timeStampSecPart = 0;
    if (Int64Multiple(static_cast<int64_t>(timestamp.time.tv_sec),
        AUDIO_SOURCE_TIME_US_S, timeStampSecPart) != 0) {
        MEDIA_ERR_LOG("multiple overflow, use default zero");
    }
    buffer.timeStamp = timeStampSecPart + timestamp.time.tv_nsec / AUDIO_SOURCE_TIME_NS_US;
    return SUCCESS;
}

int32_t RecorderAudioSource::ReleaseBuffer(RecorderSourceBuffer &buffer)
{
    return SUCCESS;
}

int32_t RecorderAudioSource::Stop()
{
    if (!audioCap_->Stop()) {
        MEDIA_ERR_LOG("AudioCapturer Can't Stop");
        return ERR_UNKNOWN;
    }
    return SUCCESS;
}

int32_t RecorderAudioSource::Pause()
{
    return SUCCESS;
}

int32_t RecorderAudioSource::Release()
{
    if (!audioCap_->Release()) {
        MEDIA_ERR_LOG("AudioCapturer Can't Release");
        return ERR_UNKNOWN;
    }
    return SUCCESS;
}
}  // namespace Media
}  // namespace OHOS
