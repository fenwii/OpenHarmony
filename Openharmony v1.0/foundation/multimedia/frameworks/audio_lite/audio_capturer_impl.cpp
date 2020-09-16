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
#include "audio_capturer_impl.h"
#include <sys/select.h>
/* include */
#include "audio_source.h"
#include "audio_encoder.h"
#include "media_log.h"

namespace OHOS {
namespace Audio {

using namespace OHOS::Media;

const unsigned long long TIME_CONVERSION_US_S = 1000000ULL;  /* ¦Ìs to s */
const unsigned long long TIME_CONVERSION_NS_US = 1000ULL;  /* ns  to ¦Ìs  */


AudioCapturer::AudioCapturerImpl::AudioCapturerImpl()
    :audioSource_(new AudioSource()),
     audioEncoder_(new AudioEncoder())
{
    MEDIA_DEBUG_LOG("ctor");
}

AudioCapturer::AudioCapturerImpl::~AudioCapturerImpl()
{
    Release();
}

bool AudioCapturer::AudioCapturerImpl::GetMinFrameCount(int32_t sampleRate, int32_t channelCount, AudioCodecFormat audioFormat, size_t &frameCount)
{
    return AudioSource::GetMinFrameCount(sampleRate, channelCount, audioFormat, frameCount);;
}

uint64_t AudioCapturer::AudioCapturerImpl::GetFrameCount()
{
    return audioSource_->GetFrameCount();
}

State AudioCapturer::AudioCapturer::AudioCapturerImpl::GetStatus()
{
    return status;
}

bool AudioCapturer::AudioCapturerImpl::GetTimestamp(Timestamp &timestamp, Timestamp::Timebase base)
{
    timestamp = timestamp_;
    return true;
}

int32_t AudioCapturer::AudioCapturerImpl::SetCapturerInfo(const AudioCapturerInfo info)
{
    int32_t ret = SUCCESS;
    std::vector<AudioDeviceDesc> devices;
    ret = audioSource_->EnumDeviceBySourceType(info.inputSource, devices);
    if (ret != SUCCESS || devices.empty()) {
        MEDIA_ERR_LOG("EnumDeviceBySourceType failed  inputSource:%d", info.inputSource);
        return ret;
    }
    MEDIA_INFO_LOG("info.sampleRate %d", info.sampleRate);
    AudioSourceConfig sourceConfig;
    sourceConfig.deviceId = devices[0].deviceId;
    sourceConfig.audioFormat = info.audioFormat;
    sourceConfig.sampleRate = info.sampleRate;
    sourceConfig.channelCount = info.channelCount;
    sourceConfig.interleaved = false;
    sourceConfig.bitWidth = info.bitWidth;
    sourceConfig.streamUsage = TYPE_DEFAULT;
    ret = audioSource_->Initialize(sourceConfig);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("Initialize failed  inputSource:%d", info.inputSource);
        return ret;
    }
    AudioEncodeConfig encodeConfig;
    encodeConfig.audioFormat = info.audioFormat;
    encodeConfig.bitRate = info.bitRate;
    encodeConfig.sampleRate = info.sampleRate;
    encodeConfig.channelCount = info.channelCount;
    encodeConfig.bitWidth = info.bitWidth;
    MEDIA_INFO_LOG("audioEncoder_ info.bitRate %d ", info.bitRate);
    ret = audioEncoder_->Initialize(encodeConfig);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("Initialize failed  inputSource:%d", info.inputSource);
        return ret;
    }
    info_ = info;
    status = PREPPARED;
    MEDIA_INFO_LOG("Set Capturer Info SUCCESS");
    return SUCCESS;
}


int32_t AudioCapturer::AudioCapturerImpl::GetCapturerInfo(AudioCapturerInfo &info)
{
    info = info_;
    return SUCCESS;
}

bool AudioCapturer::AudioCapturerImpl::Record()
{
    if (status != PREPPARED &&
        status != STOPPED) {
        MEDIA_ERR_LOG("Record ILLEGAL_STATE  status:%u", status);
        return ERR_ILLEGAL_STATE;
    }
    int32_t ret = audioSource_->Start();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("audioSource_ Start failed:0x%x", ret);
        return false;
    }
    uint32_t deviceId = 0;
    ret = audioSource_->GetCurrentDeviceId(deviceId);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("audioSource_ GetCurrentDevice failed:0x%x", ret);
        return false;
    }
    inputDeviceId_ = deviceId;
    ret = audioEncoder_->BindSource(deviceId);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("audioEncoder_ BindSource failed:0x%x", ret);
        return false;
    }
    ret = audioEncoder_->Start();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("audioEncoder_ Start failed:0x%x", ret);
        return false;
    }
    status = RECORDING;
    MEDIA_INFO_LOG("Start Audio Capturer SUCCESS");
    return true;
}

int32_t AudioCapturer::AudioCapturerImpl::Read(uint8_t *buffer, size_t userSize, bool isBlockingRead)
{
    if (buffer == NULL || userSize == 0) {
        MEDIA_ERR_LOG("Invalid buffer %p userSize:%u", buffer, userSize);
        return ERR_INVALID_READ;
    }
    if (status != RECORDING) {
        MEDIA_ERR_LOG("ILLEGAL_STATE  status:%u", status);
        return ERR_INVALID_READ;
    }
    AudioStream stream;
    stream.buffer = buffer;
    stream.bufferLen = userSize;
    int32_t readLen = audioEncoder_->ReadStream(stream, isBlockingRead);
    if (readLen == ERR_INVALID_READ) {
        MEDIA_ERR_LOG("audioEncoder_ ReadStream fail,ret:0x%x", readLen);
        return ERR_INVALID_READ;
    }
    timestamp_.time.tv_sec = static_cast<time_t>(stream.timeStamp / TIME_CONVERSION_US_S); // us - s
    timestamp_.time.tv_nsec = static_cast<time_t>((stream.timeStamp - timestamp_.time.tv_sec * TIME_CONVERSION_US_S) *
                               TIME_CONVERSION_NS_US);
    return readLen;
}

bool AudioCapturer::AudioCapturerImpl::Stop()
{
    if (status != RECORDING) {
        MEDIA_ERR_LOG("ILLEGAL_STATE  status:%u", status);
        return ERR_ILLEGAL_STATE;
    }
    MEDIA_INFO_LOG("audioEncoder Stop");
    int32_t ret = audioEncoder_->Stop();
    if (ret != SUCCESS) {
        MEDIA_DEBUG_LOG("audioEncoder_ stop fail,ret:0x%x", ret);
        return false;
    }
    MEDIA_INFO_LOG("audioSource Stop");
    ret = audioSource_->Stop();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("audioSource_ stop fail,ret:0x%x", ret);
        return false;
    }
    MEDIA_INFO_LOG("Stop Audio Capturer SUCCESS");
    status = STOPPED;
    return true;
}

bool AudioCapturer::AudioCapturerImpl::Release()
{
    if (status == RELEASED) {
        MEDIA_ERR_LOG("ILLEGAL_STATE status:%u", status);
        return false;
    }
    if (status == RECORDING && Stop()) {
        MEDIA_ERR_LOG("Stop  failed: %u", status);
        return false;
    }
    status = RELEASED;
    MEDIA_INFO_LOG("Release Audio Capturer SUCCESS");
    return true;
}
}  // namespace Audio
}  // namespace OHOS
