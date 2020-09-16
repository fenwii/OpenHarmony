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

#include "audio_encoder.h"
#include "media_log.h"
#include "securec.h"

namespace OHOS {
namespace Audio {
using namespace OHOS::Media;

constexpr uint32_t AUDIO_READ_STREAM_TIME_OUT_MS = 1000; /* 1S */

constexpr uint32_t AUDIO_CHANNEL_MONO = 1;
constexpr uint32_t AUDIO_CHANNEL_STEREO = 2;

AudioEncoder::AudioEncoder()
    : encHandle_(nullptr),
      started_(false)
{
    for (int i = 0; i < AUDIO_ENC_PARAM_NUM; i++) {
        encAttr_[i] = {};
    }
    CodecInit();
    MEDIA_INFO_LOG("AudioEncoder ctor");
}

AudioEncoder::~AudioEncoder()
{
    if (encHandle_ != nullptr) {
        CodecDestroy(encHandle_);
        encHandle_ = nullptr;
    }
    CodecDeinit();
    MEDIA_INFO_LOG("AudioEncoder dtor");
}

static bool IsAudioCodecFormatSupported(AudioCodecFormat format)
{
    if ((format < AAC_LC) || (format > AAC_ELD)) {
        MEDIA_ERR_LOG("Invalid format: %d", format);
        return false;
    }
    return true;
}

static Profile GetProfileFromAudioCodecFormat(AudioCodecFormat format)
{
    switch (format) {
        case AAC_LC:
            return AAC_LC_PROFILE;
        case AAC_HE_V1:
            return AAC_HE_V1_PROFILE;
        case AAC_HE_V2:
            return AAC_HE_V2_PROFILE;
        case AAC_LD:
            return AAC_LD_PROFILE;
        case AAC_ELD:
            return AAC_ELD_PROFILE;
        default:
            MEDIA_ERR_LOG("Invalid format: 0x%x", format);
            return AAC_LC_PROFILE;
    }
}

static AudioSampleRate ConvertSampleRate(uint32_t sampleRate)
{
    switch (sampleRate) {
        case AUD_SAMPLE_RATE_8000:
            return AUD_SAMPLE_RATE_8000;
        case AUD_SAMPLE_RATE_11025:
            return AUD_SAMPLE_RATE_11025;
        case AUD_SAMPLE_RATE_12000:
            return AUD_SAMPLE_RATE_12000;
        case AUD_SAMPLE_RATE_16000:
            return AUD_SAMPLE_RATE_16000;
        case AUD_SAMPLE_RATE_22050:
            return AUD_SAMPLE_RATE_22050;
        case AUD_SAMPLE_RATE_24000:
            return AUD_SAMPLE_RATE_24000;
        case AUD_SAMPLE_RATE_32000:
            return AUD_SAMPLE_RATE_24000;
        case AUD_SAMPLE_RATE_44100:
            return AUD_SAMPLE_RATE_44100;
        case AUD_SAMPLE_RATE_48000:
            return AUD_SAMPLE_RATE_48000;
        case AUD_SAMPLE_RATE_64000:
            return AUD_SAMPLE_RATE_64000;
        case AUD_SAMPLE_RATE_96000:
            return AUD_SAMPLE_RATE_96000;
        default:
            MEDIA_ERR_LOG("Invalid sample_rate: %d", sampleRate);
            return AUD_SAMPLE_RATE_48000;
    }
}

static AudioSoundMode ConvertSoundMode(uint32_t channelCount)
{
    switch (channelCount) {
        case AUDIO_CHANNEL_MONO:
            return AUD_SOUND_MODE_MONO;
        case AUDIO_CHANNEL_STEREO:
            return AUD_SOUND_MODE_STEREO;
        default:
            MEDIA_ERR_LOG("Invalid soundMode: %d", channelCount);
            return AUD_SOUND_MODE_MONO;
    }
}

int32_t AudioEncoder::InitAencAttr(const AudioEncodeConfig &input)
{
    if (!IsAudioCodecFormatSupported(input.audioFormat)) {
        MEDIA_ERR_LOG("input.audioFormat :0x%x is not support", input.audioFormat);
        return ERR_INVALID_PARAM;
    }
    uint32_t paramIndex = 0;
    domainKind_ = AUDIO_ENCODER;
    encAttr_[paramIndex].key = KEY_CODEC_TYPE;
    encAttr_[paramIndex].val = &domainKind_;
    encAttr_[paramIndex].size = sizeof(CodecType);
    paramIndex++;
    codecMime_ = MEDIA_MIMETYPE_AUDIO_AAC;
    encAttr_[paramIndex].key = KEY_MIMETYPE;
    encAttr_[paramIndex].val = &codecMime_;
    encAttr_[paramIndex].size = sizeof(AvCodecMime);
    paramIndex++;
    profile_ = GetProfileFromAudioCodecFormat(input.audioFormat);
    encAttr_[paramIndex].key = KEY_AUDIO_PROFILE;
    encAttr_[paramIndex].val = &profile_;
    encAttr_[paramIndex].size = sizeof(Profile);
    paramIndex++;
    sampleRate_ = ConvertSampleRate(input.sampleRate);
    encAttr_[paramIndex].key = KEY_SAMPLE_RATE;
    encAttr_[paramIndex].val = &sampleRate_;
    encAttr_[paramIndex].size = sizeof(AudioSampleRate);
    paramIndex++;
    bitRate_ = input.bitRate;
    encAttr_[paramIndex].key = KEY_BITRATE;
    encAttr_[paramIndex].val = &bitRate_;
    encAttr_[paramIndex].size = sizeof(uint32_t);
    paramIndex++;
    soundMode_ = ConvertSoundMode(input.channelCount);
    encAttr_[paramIndex].key = KEY_SOUND_MODE;
    encAttr_[paramIndex].val = &soundMode_;
    encAttr_[paramIndex].size = sizeof(AudioSoundMode);
    paramIndex++;
    ptNumPerFrm_ = AUDIO_AUDIO_POINT_NUM;
    encAttr_[paramIndex].key = KEY_POINT_NUM_PER_FRAME;
    encAttr_[paramIndex].val = &ptNumPerFrm_;
    encAttr_[paramIndex].size = sizeof(uint32_t);
    paramIndex++;
    bufSize_ = AUDIO_FRAME_NUM_IN_BUF;
    encAttr_[paramIndex].key = KEY_BUFFERSIZE;
    encAttr_[paramIndex].val = &bufSize_;
    encAttr_[paramIndex].size = sizeof(uint32_t);
    return SUCCESS;
}

int32_t AudioEncoder::Initialize(const AudioEncodeConfig &input)
{
    int32_t ret = InitAencAttr(input);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("InitAencAttr failed:%d", ret);
        return ret;
    }
    const char *audioEncName = "codec.aac.hardware.encoder";
    ret = CodecCreate(audioEncName, encAttr_, AUDIO_ENC_PARAM_NUM, &encHandle_);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("CodecCreate failed :0x%x", ret);
        return ret;
    }
    return SUCCESS;
}

int32_t AudioEncoder::BindSource(uint32_t deviceId)
{
    int32_t ret = SUCCESS;
    Param params[1];
    memset_s(params, sizeof(params), 0x00, sizeof(params));
    params[0].key = KEY_DEVICE_ID;
    params[0].val = reinterpret_cast<void *>(&deviceId);
    params[0].size = sizeof(uint32_t);
    ret = CodecSetParameter(encHandle_, params, sizeof(params) / sizeof(params[0]));
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("CodecSetDevice :0x%x", ret);
        return ret;
    }
    return SUCCESS;
}

int32_t AudioEncoder::GetMute(bool &muted)
{
    return ERR_UNKNOWN;
}

int32_t AudioEncoder::SetMute(bool muted)
{
    return ERR_UNKNOWN;
}

int32_t AudioEncoder::Start()
{
    int32_t ret = SUCCESS;
    ret = CodecStart(encHandle_);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("CodecStart failed:0x%x", ret);
        return ret;
    }
    started_ = true;
    return ret;
}

int32_t AudioEncoder::ReadStream(AudioStream &stream, bool isBlockingRead)
{
    if (!started_) {
        MEDIA_ERR_LOG("Codec not Started");
        return ERR_INVALID_READ;
    }
    if (stream.buffer == nullptr || stream.bufferLen == 0) {
        MEDIA_ERR_LOG("stream.buffer is  nullptr");
        return ERR_INVALID_READ;
    }
    uint32_t timeoutMs;
    if (isBlockingRead) {
        timeoutMs = AUDIO_READ_STREAM_TIME_OUT_MS;
    } else {
        timeoutMs = 0;
    }
    OutputInfo outInfo;
    CodecBufferInfo outBuf;
    outInfo.bufferCnt = 1;
    outInfo.buffers = &outBuf;
    int32_t ret = CodecDequeueOutput(encHandle_, timeoutMs, nullptr, &outInfo);
    if (ret != SUCCESS && outInfo.buffers[0].addr == nullptr) {
        MEDIA_ERR_LOG("CodecDequeueOutput failed:0x%x", ret);
        return ERR_INVALID_READ;
    }
    int32_t readLen = 0;
    errno_t retCopy = memcpy_s(stream.buffer, stream.bufferLen, outInfo.buffers[0].addr,
                               outInfo.buffers[0].length);
    if (retCopy != EOK) {
        MEDIA_ERR_LOG("memcpy_s encData.encodedData %p timeStamp:%lld failed :0x%x",
                      outInfo.buffers[0].addr, outInfo.timeStamp, retCopy);
        return ERR_INVALID_OPERATION;
    } else {
        readLen = outInfo.buffers[0].length;
    }
    stream.timeStamp = outInfo.timeStamp;
    (void)CodecQueueOutput(encHandle_, &outInfo, timeoutMs, -1);
    return readLen;
}

int32_t AudioEncoder::Stop()
{
    MEDIA_DEBUG_LOG("AudioEncoder::Stop");
    if (!started_) {
        MEDIA_ERR_LOG("Codec not Start");
    }
    return CodecStop(encHandle_);
}
}  // namespace Audio
}  // namespace OHOS
