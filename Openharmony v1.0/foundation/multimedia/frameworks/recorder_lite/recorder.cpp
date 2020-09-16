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

#include "recorder.h"

#include "media_log.h"
#include "pms_interface.h"
#include "recorder_impl.h"
#include "securec.h"

namespace OHOS {
namespace Media {
Recorder::Recorder() : impl_(new RecorderImpl()) {}

Recorder::~Recorder() {}

int32_t Recorder::SetVideoSource(VideoSourceType source, int32_t &sourceId)
{
    return impl_->SetVideoSource(source, sourceId);
}

int32_t Recorder::SetVideoEncoder(int32_t sourceId, VideoCodecFormat encoder)
{
    return impl_->SetVideoEncoder(sourceId, encoder);
}

int32_t Recorder::SetVideoSize(int32_t sourceId, int32_t width, int32_t height)
{
    return impl_->SetVideoSize(sourceId, width, height);
}
int32_t Recorder::SetVideoFrameRate(int32_t sourceId, int32_t frameRate)
{
    return impl_->SetVideoFrameRate(sourceId, frameRate);
}

int32_t Recorder::SetVideoEncodingBitRate(int32_t sourceId, int32_t rate)
{
    return impl_->SetVideoEncodingBitRate(sourceId, rate);
}

int32_t Recorder::SetCaptureRate(int32_t sourceId, double fps)
{
    return impl_->SetCaptureRate(sourceId, fps);
}

std::shared_ptr<OHOS::Surface> Recorder::GetSurface(int32_t sourceId)
{
    return impl_->GetSurface(sourceId);
}

int32_t Recorder::SetAudioSource(AudioSourceType source, int32_t &sourceId)
{
    return impl_->SetAudioSource(source, sourceId);
}

int32_t Recorder::SetAudioEncoder(int32_t sourceId, AudioCodecFormat encoder)
{
    return impl_->SetAudioEncoder(sourceId, encoder);
}

int32_t Recorder::SetAudioSampleRate(int32_t sourceId, int32_t rate)
{
    return impl_->SetAudioSampleRate(sourceId, rate);
}

int32_t Recorder::SetAudioChannels(int32_t sourceId, int32_t num)
{
    return impl_->SetAudioChannels(sourceId, num);
}

int32_t Recorder::SetAudioEncodingBitRate(int32_t sourceId, int32_t bitRate)
{
    return impl_->SetAudioEncodingBitRate(sourceId, bitRate);
}

int32_t Recorder::SetMaxDuration(int32_t duration)
{
    return impl_->SetMaxDuration(duration);
}

int32_t Recorder::SetOutputFormat(OutputFormatType format)
{
    return impl_->SetOutputFormat(format);
}

int32_t Recorder::SetOutputPath(const string &path)
{
    return impl_->SetOutputPath(path);
}

int32_t Recorder::SetOutputFile(int32_t fd)
{
    return impl_->SetOutputFile(fd);
}

int32_t Recorder::SetNextOutputFile(int32_t fd)
{
    return impl_->SetNextOutputFile(fd);
}

int32_t Recorder::SetMaxFileSize(int64_t size)
{
    return impl_->SetMaxFileSize(size);
}

int32_t Recorder::SetRecorderCallback(const std::shared_ptr<RecorderCallback> &callback)
{
    return impl_->SetRecorderCallback(callback);
}

int32_t Recorder::Prepare()
{
    if (CheckPermission(0, "ohos.permission.MICROPHONE") != GRANTED) {
        MEDIA_WARNING_LOG("Process can not access microphone.");
        return MEDIA_PERMISSION_DENIED;
    }
    if (CheckPermission(0, "ohos.permission.WRITE_MEDIA") != GRANTED) {
        MEDIA_WARNING_LOG("Process can not write media.");
        return MEDIA_PERMISSION_DENIED;
    }
    return impl_->Prepare();
}

int32_t Recorder::Start()
{
    return impl_->Start();
}

int32_t Recorder::Pause()
{
    return impl_->Pause();
}

int32_t Recorder::Resume()
{
    return impl_->Resume();
}

int32_t Recorder::Stop(bool block)
{
    return impl_->Stop(block);
}

int32_t Recorder::Reset()
{
    return impl_->Reset();
}

int32_t Recorder::Release()
{
    return impl_->Release();
}

int32_t Recorder::SetFileSplitDuration(FileSplitType type, int64_t timestamp, uint32_t duration)
{
    return impl_->SetFileSplitDuration(type, timestamp, duration);
}

int32_t Recorder::SetParameter(int32_t sourceId, const Format &format)
{
    return impl_->SetParameter(sourceId, format);
}

} /* namespace Media */
} /* namespace OHOS */
