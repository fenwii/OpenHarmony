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

#include "audio_capturer.h"
#include "audio_capturer_impl.h"

namespace OHOS {
namespace Audio {

AudioCapturer::AudioCapturer()
    : impl_(new AudioCapturerImpl())
{
}

AudioCapturer::~AudioCapturer()
{
}

bool AudioCapturer::GetMinFrameCount(int32_t sampleRate, int32_t channelCount, AudioCodecFormat audioFormat, size_t &frameCount)
{
    return AudioCapturerImpl::GetMinFrameCount(sampleRate, channelCount, audioFormat, frameCount);
}

uint64_t AudioCapturer::GetFrameCount()
{
    return impl_->GetFrameCount();
}

State AudioCapturer::GetStatus()
{
    return impl_->GetStatus();
}

bool AudioCapturer::GetAudioTime(Timestamp &timestamp, Timestamp::Timebase base)
{
    return impl_->GetTimestamp(timestamp, base);
}

int32_t AudioCapturer::SetCapturerInfo(const AudioCapturerInfo info)
{
    return impl_->SetCapturerInfo(info);
}

int32_t AudioCapturer::GetCapturerInfo(AudioCapturerInfo &info)
{
    return impl_->GetCapturerInfo(info);
}

bool AudioCapturer::Start()
{
    return impl_->Record();
}

bool AudioCapturer::Stop()
{
    return impl_->Stop();
}

bool AudioCapturer::Release()
{
    return impl_->Release();
}

int32_t AudioCapturer::Read(uint8_t *buffer, size_t userSize, bool isBlockingRead)
{
    return impl_->Read(buffer, userSize, isBlockingRead);
}

}  // namespace Audio
}  // namespace OHOS
