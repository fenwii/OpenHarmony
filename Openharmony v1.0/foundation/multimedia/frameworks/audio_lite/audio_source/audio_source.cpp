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
#include "audio_source.h"
#include "media_log.h"
#include "securec.h"

namespace OHOS {
namespace Audio {
#define AUDIO_RETURN_VAL_IF_NULL(condition)                                            \
    do {                                                                               \
        if ((condition) == nullptr) {                                                  \
            MEDIA_ERR_LOG("" #condition " is NULL");    \
            return ERR_ILLEGAL_STATE;                                                  \
        }                                                                              \
    } while (0)

using namespace OHOS::Media;
static AudioManager *g_audioManager = nullptr;
AudioSource::AudioSource()
    : initialized_(false),
      started_(false),
      audioAdapter_(nullptr),
      audioCapture_(nullptr)
{
    if (g_audioManager == nullptr) {
        g_audioManager = GetAudioManagerFuncs();
        MEDIA_DEBUG_LOG("g_audioManager: %p", g_audioManager);
    }
    int size = 0;
    struct AudioAdapterDescriptor *descs = nullptr;
    g_audioManager->GetAllAdapters(g_audioManager, &descs, &size);
    MEDIA_DEBUG_LOG("GetAllAdapters: %d ", size);

    for (int index = 0; index < size; index++) {
        struct AudioAdapterDescriptor *desc = &descs[index];
        for (int port = 0; (desc != nullptr && port < static_cast<int>(desc->portNum)); port++) {
            if (desc->ports[port].dir == PORT_IN &&
                (g_audioManager->LoadAdapter(g_audioManager, desc, &audioAdapter_)) == 0) {
                (void)audioAdapter_->InitAllPorts(audioAdapter_);
                if (memcpy_s(&capturePort_, sizeof(struct AudioPort),
                    &desc->ports[port], sizeof(struct AudioPort)) != 0) {
                    MEDIA_WARNING_LOG("memcpy_s capturePort_ failed");
                }
                break;
            }
        }
    }
    MEDIA_DEBUG_LOG("LoadAdapter audioAdapter_:%p", audioAdapter_);
}

AudioSource::~AudioSource()
{
    MEDIA_DEBUG_LOG("audioAdapter_ :%p", audioAdapter_);
    if (audioAdapter_ != nullptr) {
        MEDIA_INFO_LOG("audioAdapter_ UnloadModule: %p", audioAdapter_);
        g_audioManager->UnloadAdapter(g_audioManager, audioAdapter_);
        audioAdapter_ = nullptr;
    }
}

int32_t AudioSource::InitCheck()
{
    if (!initialized_) {
        MEDIA_ERR_LOG("not initialized");
        return ERR_ILLEGAL_STATE;
    }
    return SUCCESS;
}

bool AudioSource::GetMinFrameCount(int32_t sampleRate, int32_t channelCount,
                                   AudioCodecFormat audioFormat, size_t &frameCount)
{
    frameCount = 0;
    return true;
}

uint64_t AudioSource::GetFrameCount()
{
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        return ret;
    }
    AUDIO_RETURN_VAL_IF_NULL(audioCapture_);
    uint64_t frameCount = 0;
    ret = audioCapture_->attr.GetFrameCount(reinterpret_cast<AudioHandle>(audioCapture_), &frameCount);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("attr GetFrameCount failed 0x%x ", ret);
        return ret;
    }
    return frameCount;
}

int32_t AudioSource::EnumDeviceBySourceType(AudioSourceType inputSource, std::vector<AudioDeviceDesc> &devices)
{
    if (inputSource != AUDIO_MIC) {
        MEDIA_ERR_LOG("AudioSource only support AUDIO_MIC");
        return ERR_INVALID_PARAM;
    }
    AUDIO_RETURN_VAL_IF_NULL(audioAdapter_);

    struct AudioPortCapability capability;
    audioAdapter_->GetPortCapability(audioAdapter_, &capturePort_, &capability);
    AudioDeviceDesc deviceDesc;
    deviceDesc.deviceId = capability.deviceId;
    deviceDesc.inputSourceType = AUDIO_MIC;
    devices.push_back(deviceDesc);
    return SUCCESS;
}

int32_t AudioSource::Initialize(const AudioSourceConfig &input)
{
    AUDIO_RETURN_VAL_IF_NULL(audioAdapter_);

    MEDIA_INFO_LOG("deviceId:0x%x input.sampleRate:%d", input.deviceId, input.sampleRate);
    int32_t ret = SUCCESS;
    struct AudioDeviceDescriptor desc;
    struct AudioSampleAttributes attrs;
    attrs.type = AUDIO_IN_MEDIA;
    attrs.sampleRate = input.sampleRate;
    attrs.format = AUDIO_FORMAT_PCM_16_BIT;
    attrs.channelCount = input.channelCount;
    attrs.interleaved = input.interleaved;
    ret = audioAdapter_->CreateCapture(audioAdapter_, &desc, &attrs, &audioCapture_);
    if (ret != SUCCESS || audioCapture_ == nullptr) {
        MEDIA_ERR_LOG("CreateCapture failed 0x%x", ret);
        return ret;
    }
    initialized_ = true;
    return SUCCESS;
}

int32_t AudioSource::SetInputDevice(uint32_t deviceId)
{
    return SUCCESS;
}

int32_t AudioSource::GetCurrentDeviceId(uint32_t &deviceId)
{
    AUDIO_RETURN_VAL_IF_NULL(audioCapture_);
    int32_t ret = audioCapture_->attr.GetCurrentChannelId(reinterpret_cast<AudioHandle>(audioCapture_), &deviceId);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("GetCurrentChannelId failed 0x%x", ret);
        return ret;
    }
    MEDIA_INFO_LOG("deviceId:0x%x", deviceId);
    return SUCCESS;
}

int32_t AudioSource::Start()
{
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        return ret;
    }

    AUDIO_RETURN_VAL_IF_NULL(audioCapture_);
    ret = audioCapture_->control.Start(reinterpret_cast<AudioHandle>(audioCapture_));
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("audioCapture_ Start failed 0x%x", ret);
        return ret;
    }
    started_ = true;
    return SUCCESS;
}

int32_t AudioSource::ReadFrame(uint8_t *buffer, size_t bufferBytes, bool isBlockingRead)
{
    if (!started_) {
        MEDIA_ERR_LOG("AudioSource not Start");
        return ERR_ILLEGAL_STATE;
    }
    return SUCCESS;
}

int32_t AudioSource::Stop()
{
    MEDIA_INFO_LOG("AudioSource::Stop");
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        return ret;
    }

    AUDIO_RETURN_VAL_IF_NULL(audioCapture_);
    ret = audioCapture_->control.Stop(reinterpret_cast<AudioHandle>(audioCapture_));
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("Stop failed 0x%x", ret);
        return ret;
    }
    ret = audioAdapter_->DestroyCapture(audioAdapter_, audioCapture_);
    audioCapture_ = nullptr;
    started_ = false;
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("Close failed 0x%x", ret);
        return ret;
    }
    return SUCCESS;
}
}  // namespace Audio
}  // namespace OHOS
