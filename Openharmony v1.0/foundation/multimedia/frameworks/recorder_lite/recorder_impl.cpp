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

#include "recorder_impl.h"
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/io.h>
#include <sys/select.h>
#include <sys/prctl.h>
#include "media_log.h"
#include "securec.h"

namespace OHOS {
namespace Media {
#define CHECK_MEMBER_PTR_RETURN(param)                                \
    do {                                                              \
        if (param == nullptr) {                                       \
            MEDIA_ERR_LOG("ptr is null"); \
            return ERR_UNKNOWN;                                       \
        }                                                             \
    } while (0)

constexpr float RECORDER_DEFAULT_SPEED = 1.0;

constexpr uint32_t RECORDER_AUDIO_THREAD_PRIORITY = 19;
constexpr uint32_t RECORDER_VIDEO_THREAD_PRIORITY = 20;

Recorder::RecorderImpl::RecorderImpl()
{
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        sourceManager_[i].videoSource = nullptr;
        sourceManager_[i].videoSourceStarted = false;
        sourceManager_[i].videoSourcePaused = false;
        sourceManager_[i].videoTrackId = -1;
        sourceManager_[i].audioSource = nullptr;
        sourceManager_[i].audioSourceStarted = false;
        sourceManager_[i].audioSourcePaused = false;
        sourceManager_[i].audioTrackId = -1;
        sourceManager_[i].videoSourceConfig = {};
        sourceManager_[i].audioSourceConfig = {};
    }
    recorderSink_ = new(std::nothrow) RecorderSink();
    if (recorderSink_ != nullptr) {
        status_= INITIALIZED;
    }
    MEDIA_INFO_LOG("ctor status_:%d", status_);
}

Recorder::RecorderImpl::~RecorderImpl()
{
    if (status_ != RELEASED) {
        (void)Release();
    }
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].videoSource != nullptr) {
            delete sourceManager_[i].videoSource;
            sourceManager_[i].videoSource = nullptr;
        }
        if (sourceManager_[i].audioSource != nullptr) {
            delete sourceManager_[i].audioSource;
            sourceManager_[i].audioSource = nullptr;
        }
    }
    if (recorderSink_ != nullptr) {
        delete recorderSink_;
        recorderSink_ = nullptr;
    }
}

int32_t Recorder::RecorderImpl::ResetConfig()
{
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        sourceManager_[i].videoSourceStarted = false;
        sourceManager_[i].videoSourcePaused = false;
        sourceManager_[i].videoTrackId = -1;
        sourceManager_[i].audioSourceStarted = false;
        sourceManager_[i].audioSourcePaused = false;
        sourceManager_[i].audioTrackId = -1;
        sourceManager_[i].videoSourceConfig = {};
        if (memset_s(&sourceManager_[i].videoSourceConfig , sizeof(RecorderVideoSourceConfig),
                     0x00, sizeof(RecorderVideoSourceConfig)) != EOK) {
            MEDIA_ERR_LOG("memset videoSourceConfig failed");
            return ERR_UNKNOWN;
        }
        if (memset_s(&sourceManager_[i].audioSourceConfig , sizeof(RecorderAudioSourceConfig),
                     0x00, sizeof(RecorderAudioSourceConfig)) != EOK) {
            MEDIA_ERR_LOG("memset videoSourceConfig failed");
            return ERR_UNKNOWN;
        }
    }
    MEDIA_INFO_LOG("ResetConfig SUCCESS");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::InitCheck()
{
    if (status_ == RELEASED) {
        MEDIA_ERR_LOG("InitCheck ILLEGAL_STATE  status:%u", status_);
        return ERR_ILLEGAL_STATE;
    }
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::GetFreeVideoSourceID(int32_t &sourceId)
{
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].videoSource == nullptr) {
            sourceId = i;
            return SUCCESS;
        }
    }
    MEDIA_ERR_LOG("could get free video sourceId");
    return ERROR;
}

int32_t Recorder::RecorderImpl::GetFreeAudioSourceID(int32_t &sourceId)
{
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].audioSource == nullptr) {
            sourceId = i;
            return SUCCESS;
        }
    }
    MEDIA_ERR_LOG("could get free Audio sourceId");
    return ERROR;
}

bool Recorder::RecorderImpl::IsValidSourceID(int32_t sourceId)
{
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceId == static_cast<int32_t>(i) &&
            (sourceManager_[i].videoSource != nullptr ||
            sourceManager_[i].audioSource != nullptr)) {
            return true;
        }
    }
    MEDIA_ERR_LOG("IsValidSourceID sourceId:%d", sourceId);
    return false;
}

int32_t Recorder::RecorderImpl::SetVideoSource(VideoSourceType source, int32_t &sourceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (source < VIDEO_SOURCE_SURFACE_YUV || source >= VIDEO_SOURCE_BUTT) {
        MEDIA_ERR_LOG("only support  VIDEO_SOURCE_SURFACE_ES  source: %d is invalid\n", source);
        return ERR_INVALID_PARAM;
    }
    int32_t ret = GetFreeVideoSourceID(sourceId);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("GetFreeVideoSourceID  failed Ret: %d", ERR_NOFREE_CHANNEL);
        return ERR_NOFREE_CHANNEL;
    }
    sourceManager_[sourceId].videoSource = new RecorderVideoSource();
    MEDIA_INFO_LOG("Video Source :%d Set SUCCESS", source);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetVideoEncoder(int32_t sourceId, VideoCodecFormat encoder)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return ERR_INVALID_PARAM;
    }
    if (encoder != VIDEO_DEFAULT && encoder != H264 && encoder != HEVC) {
        MEDIA_ERR_LOG("input VideoCodecFormat : %d is invalid", encoder);
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].videoSourceConfig.videoFormat = encoder;
    MEDIA_INFO_LOG("Video Encoder :%d Set SUCCESS", encoder);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetVideoSize(int32_t sourceId, int32_t width, int32_t height)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return ERR_INVALID_PARAM;
    }
    if (width <= 0 || height <= 0) {
        MEDIA_ERR_LOG("input VideoSize width: %d width: %d is invalid", width, height);
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].videoSourceConfig.width = width;
    sourceManager_[sourceId].videoSourceConfig.height = height;
    MEDIA_INFO_LOG("Video Size width:%d height:%d", width, height);
    return SUCCESS;
}
int32_t Recorder::RecorderImpl::SetVideoFrameRate(int32_t sourceId, int32_t frameRate)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return ERR_INVALID_PARAM;
    }
    if (frameRate <= 0) {
        MEDIA_ERR_LOG("input frameRate %d is invalid", frameRate);
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].videoSourceConfig.frameRate = frameRate;
    MEDIA_INFO_LOG("Video frameRate:%d ", frameRate);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetVideoEncodingBitRate(int32_t sourceId, int32_t rate)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return ERR_INVALID_PARAM;
    }
    if (rate <= 0) {
        MEDIA_ERR_LOG("input rate %d is invalid", rate);
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].videoSourceConfig.bitRate = rate;
    MEDIA_INFO_LOG("Video Encoding BitRate:%d ", rate);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetCaptureRate(int32_t sourceId, double fps)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return ERR_INVALID_PARAM;
    }
    if (fps <= 0.0) {
        MEDIA_ERR_LOG("input rate %lf is invalid", fps);
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].videoSourceConfig.captureRate = fps;
    MEDIA_INFO_LOG("Video Capture Rate:%lf ", fps);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetOrientationHint(int32_t sourceId, int32_t degree)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return ERR_INVALID_PARAM;
    }
    if (degree <= 0) {
        MEDIA_ERR_LOG("input rate %d is invalid", degree);
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].videoSourceConfig.degree = degree;
    return SUCCESS;
}

std::shared_ptr<OHOS::Surface> Recorder::RecorderImpl::GetSurface(int32_t sourceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return nullptr;
    }
    return sourceManager_[sourceId].videoSource->GetSurface();
}

bool Recorder::RecorderImpl::IsValidAudioSource(AudioSourceType source)
{
    if (source <= AUDIO_SOURCE_INVALID || source > AUDIO_VOICE_PERFORMANCE) {
        MEDIA_ERR_LOG("input AudioSourceType : %d is invalid", source);
        return false;
    }
    return true;
}

int32_t Recorder::RecorderImpl::SetAudioSource(AudioSourceType source, int32_t &sourceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret = GetFreeAudioSourceID(sourceId);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("GetFreeAudioSourceID  failed Ret: %d", ERR_NOFREE_CHANNEL);
        return ERR_NOFREE_CHANNEL;
    }
    if (!IsValidAudioSource(source)) {
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].audioSource = new RecorderAudioSource();
    MEDIA_INFO_LOG("Audio Source :%d Set SUCCESS", source);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetAudioEncoder(int32_t sourceId, AudioCodecFormat encoder)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return ERR_INVALID_PARAM;
    }
    if (encoder >= FORMAT_BUTT || encoder <= AUDIO_DEFAULT) {
        MEDIA_ERR_LOG("input AudioCodecFormat : %d is invalid", encoder);
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].audioSourceConfig.audioFormat = encoder;
    MEDIA_INFO_LOG("Audio Encoder :%d Set", encoder);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetAudioSampleRate(int32_t sourceId, int32_t rate)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return ERR_INVALID_PARAM;
    }
    if (rate <= 0) {
        MEDIA_ERR_LOG("input AudioSampleRate %d is invalid", rate);
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].audioSourceConfig.sampleRate = rate;
    MEDIA_INFO_LOG("Audio Sample Rate :%d Set", rate);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetAudioChannels(int32_t sourceId, int32_t num)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return ERR_INVALID_PARAM;
    }
    if (num <= 0) {
        MEDIA_ERR_LOG("input AudioChannels %d is invalid", num);
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].audioSourceConfig.channelCount = num;
    MEDIA_INFO_LOG("Audio Channels :%d Set", num);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetAudioEncodingBitRate(int32_t sourceId, int32_t bitRate)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!IsValidSourceID(sourceId)) {
        MEDIA_ERR_LOG("input sourceId : %d is invalid", sourceId);
        return ERR_INVALID_PARAM;
    }
    if (bitRate <= 0) {
        MEDIA_ERR_LOG("input AudioEncodingBitRate %d is invalid", bitRate);
        return ERR_INVALID_PARAM;
    }
    sourceManager_[sourceId].audioSourceConfig.bitRate = bitRate;
    MEDIA_INFO_LOG("Audio Encoding BitRate :%d Set", bitRate);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetLocation(int32_t latitude, int32_t longitude)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("SetLocation InitCheck err");
        return ret;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    return recorderSink_->SetLocation(latitude, longitude);
}

int32_t Recorder::RecorderImpl::SetMaxDuration(int32_t duration)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("SetMaxDuration InitCheck err");
        return ret;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    MEDIA_INFO_LOG("Max Duration :%d Set", duration);
    return recorderSink_->SetMaxDuration(duration);
}

int32_t Recorder::RecorderImpl::SetOutputFormat(OutputFormatType format)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("SetOutputFormat InitCheck err");
        return ret;
    }
    MEDIA_INFO_LOG("Output Format :%d Set", format);
    OutputFormat outPutFormat;
    switch (format) {
        case FORMAT_MPEG_4:
            outPutFormat = OUTPUT_FORMAT_MPEG_4;
            break;
        case FORMAT_TS:
            outPutFormat = OUTPUT_FORMAT_TS;
            break;
        default:
            MEDIA_ERR_LOG("format: %d use default OUTPUT_FORMAT_MPEG_4", format);
            outPutFormat = OUTPUT_FORMAT_MPEG_4;
            break;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    return recorderSink_->SetOutputFormat(outPutFormat);
}

int32_t Recorder::RecorderImpl::SetOutputPath(const string &path)
{
    std::lock_guard<std::mutex> lock(mutex_);
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    if (status_ != INITIALIZED) {
        MEDIA_ERR_LOG("SetOutputPath ILLEGAL_STATE  status:%u", status_);
        return ERR_ILLEGAL_STATE;
    }
    if (path.data() == nullptr) {
        MEDIA_ERR_LOG("The path is nullptr");
        return ERR_INVALID_PARAM;
    }
    if (access(path.c_str(), F_OK) == -1) {
        MEDIA_ERR_LOG("The path :%s doesn't exisit", path.c_str());
        return ERR_INVALID_PARAM;
    }
    if (access(path.c_str(),  W_OK) == -1) {
        MEDIA_ERR_LOG("The path :%s No write permission", path.c_str());
        return ERR_INVALID_PARAM;
    }
    recorderSink_->SetOutputPath(path);
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::IsValidFileFd(int32_t fd)
{
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        MEDIA_ERR_LOG("Fail to get File Status Flags err: %d", errno);
        return ERR_INVALID_OPERATION;
    }
    // fd must be in read-write mode or write-only mode.
    uint32_t flagsCheck = static_cast<uint32_t>(flags);
    if ((flagsCheck & (O_RDWR | O_WRONLY)) == 0) {
        MEDIA_ERR_LOG("File descriptor is not in read-write mode or write-only mode fd:%d", fd);
        return ERR_INVALID_OPERATION;
    }
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetOutputFile(int32_t fd)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("SetOutputFormat InitCheck err");
        return ret;
    }
    MEDIA_INFO_LOG("Output File :%d Set", fd);
    if (IsValidFileFd(fd) != SUCCESS) {
        MEDIA_ERR_LOG("Fail to get File Status Flags from fd: %d", fd);
        return ERR_INVALID_PARAM;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    return recorderSink_->SetOutputFile(fd);
}

int32_t Recorder::RecorderImpl::SetNextOutputFile(int32_t fd)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("SetNextOutputFile InitCheck err");
        return ret;
    }
    MEDIA_INFO_LOG("Next Output File :%d Set", fd);
    if (IsValidFileFd(fd) != SUCCESS) {
        MEDIA_ERR_LOG("Fail to get File Status Flags from fd: %d", fd);
        return ERR_INVALID_PARAM;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    return recorderSink_->SetNextOutputFile(fd);
}

int32_t Recorder::RecorderImpl::SetMaxFileSize(int64_t size)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("SetMaxFileSize InitCheck err");
        return ret;
    }
    MEDIA_INFO_LOG("Max File Size :%lld Set", size);
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    return recorderSink_->SetMaxFileSize(size);
}

int32_t Recorder::RecorderImpl::SetRecorderCallback(const std::shared_ptr<RecorderCallback> &callback)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("SetRecorderCallback InitCheck err");
        return ret;
    }
    if (callback == nullptr) {
        MEDIA_ERR_LOG("SetRecorderCallback callback is nullptr");
        return ERR_INVALID_PARAM;
    }
    MEDIA_INFO_LOG("RecorderCallback :%p Set", callback.get());
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    return recorderSink_->SetRecorderCallback(callback);
}

int32_t Recorder::RecorderImpl::PrepareAudioSource()
{
    int32_t ret = 0;
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].audioSource != nullptr) {
            ret = sourceManager_[i].audioSource->Init(sourceManager_[i].audioSourceConfig);
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("audioSource Init failed Ret: 0x%x", ret);
                return ret;
            }
            TrackSource trackSource;
            ret = GetAudioTrackSource(sourceManager_[i].audioSourceConfig, trackSource);
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("GetAudioTrackSource  failed Ret: 0x%x", ret);
                return ret;
            }
            int32_t trackId;
            CHECK_MEMBER_PTR_RETURN(recorderSink_);
            ret = recorderSink_->AddTrackSource(trackSource, trackId);
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("AddTrackSource  failed Ret: 0x%x", ret);
                return ret;
            }
            sourceManager_[i].audioTrackId = trackId;
            MEDIA_INFO_LOG("recorderSink_ AddTrackSource .audioTrackId :0x%x",
                           sourceManager_[i].audioTrackId);
        }
    }
    MEDIA_INFO_LOG("Prepare AudioSource SUCCESS");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::PrepareVideoSource()
{
    int32_t ret = 0;
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].videoSource != nullptr) {
            TrackSource trackSource;
            ret = GetVideoTrackSource(sourceManager_[i].videoSourceConfig, trackSource);
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("GetVideoTrackSource  failed Ret: 0x%x", ret);
                return ret;
            }
            int32_t trackId;
            CHECK_MEMBER_PTR_RETURN(recorderSink_);
            ret = recorderSink_->AddTrackSource(trackSource, trackId);
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("AddTrackSource  failed Ret: 0x%x", ret);
                return ret;
            }
            sourceManager_[i].videoTrackId = trackId;
            MEDIA_INFO_LOG("recorderSink_ AddTrackSource videoTrackId :0x%x",
                           sourceManager_[i].videoTrackId);
        }
    }
    MEDIA_INFO_LOG("Prepare VideoSource SUCCESS");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::GetVideoTrackSource(const RecorderVideoSourceConfig &videoSourceConfig,
                                                    TrackSource &trackSource)
{
    trackSource.trackSourceType = TRACK_SOURCE_TYPE_VIDEO;
    switch (videoSourceConfig.videoFormat) {
        case H264:
            trackSource.trackSourceInfo.videoInfo.codecType = CODEC_H264;
            break;
        case HEVC:
            trackSource.trackSourceInfo.videoInfo.codecType = CODEC_H265;
            break;
        default:
            MEDIA_ERR_LOG("unsupport videoFormat format: %d", videoSourceConfig.videoFormat);
            return ERR_INVALID_PARAM;
    }
    if (videoSourceConfig.width <= 0 || videoSourceConfig.height <= 0 ||
        videoSourceConfig.bitRate <= 0 || videoSourceConfig.frameRate <= 0) {
        MEDIA_ERR_LOG("VideoTrackSource not prepared");
        return ERR_INVALID_PARAM;
    }
    trackSource.trackSourceInfo.videoInfo.width = videoSourceConfig.width;
    trackSource.trackSourceInfo.videoInfo.height = videoSourceConfig.height;
    trackSource.trackSourceInfo.videoInfo.bitRate = videoSourceConfig.bitRate;
    trackSource.trackSourceInfo.videoInfo.frameRate = videoSourceConfig.frameRate;
    trackSource.trackSourceInfo.videoInfo.keyFrameInterval = videoSourceConfig.frameRate;
    trackSource.trackSourceInfo.videoInfo.speed = RECORDER_DEFAULT_SPEED;
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::GetAudioTrackSource(const RecorderAudioSourceConfig &audioSourceConfig,
                                                    TrackSource &trackSource)
{
    trackSource.trackSourceType = TRACK_SOURCE_TYPE_AUDIO;
    switch (audioSourceConfig.audioFormat) {
        case AAC_LC:
        case AAC_HE_V1:
        case AAC_HE_V2:
        case AAC_LD:
        case AAC_ELD:
            trackSource.trackSourceInfo.audioInfo.codecType = CODEC_AAC;
            break;
        default:
            MEDIA_ERR_LOG("unsupport audiFormat format: %d", audioSourceConfig.audioFormat);
            return ERR_INVALID_PARAM;
    }
    trackSource.trackSourceInfo.audioInfo.sampleRate = audioSourceConfig.sampleRate;
    trackSource.trackSourceInfo.audioInfo.channelCount = audioSourceConfig.channelCount;
    switch (audioSourceConfig.bitWidth) {
        case BIT_WIDTH_8:
         trackSource.trackSourceInfo.audioInfo.sampleBitWidth = AUDIO_SAMPLE_FMT_S8;
            break;
        case BIT_WIDTH_16:
         trackSource.trackSourceInfo.audioInfo.sampleBitWidth = AUDIO_SAMPLE_FMT_S16;
            break;
        case BIT_WIDTH_24:
            trackSource.trackSourceInfo.audioInfo.sampleBitWidth = AUDIO_SAMPLE_FMT_S24;
            break;
        default:
            MEDIA_ERR_LOG("unsupport sampleBitWidth: %d", audioSourceConfig.bitWidth);
            return ERR_INVALID_PARAM;
    }
    trackSource.trackSourceInfo.audioInfo.samplesPerFrame = 1024;
    trackSource.trackSourceInfo.audioInfo.avgBytesPerSec = audioSourceConfig.bitRate;
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::PrepareRecorderSink()
{
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("PrepareRecorderSink InitCheck err");
        return ret;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    return recorderSink_->Prepare();
}

int32_t Recorder::RecorderImpl::Prepare()
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret = PrepareRecorderSink();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("PrepareRecorderSink  failed Ret: %d", ret);
        return ret;
    }
    ret = PrepareVideoSource();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("PrepareVideoSource  failed Ret: %d", ret);
        return ret;
    }
    ret = PrepareAudioSource();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("PrepareAudioSource  failed Ret: %d", ret);
        return ret;
    }
    status_ = PREPPARED;
    MEDIA_INFO_LOG("Prepare SUCCESS");
    return SUCCESS;
}

void AudioSourceProcess(const SourceManager *audioSourceManager, const RecorderSink *recorderSink)
{
    MEDIA_INFO_LOG("audioSourceManager:%p", audioSourceManager);
    if (audioSourceManager == nullptr || recorderSink == nullptr) {
        return;
    }
    if (audioSourceManager->audioSource == nullptr) {
        MEDIA_ERR_LOG("audioSource is nullptr");
        return;
    }
    prctl(PR_SET_NAME, "AudioSourceProcess", 0, 0, 0);
    struct sched_param param = {};
    pthread_attr_t attr;
    pthread_attr_getschedparam(&attr, &param);
    param.sched_priority = RECORDER_AUDIO_THREAD_PRIORITY;
    pthread_setschedparam(pthread_self(), SCHED_RR, &param);
    MEDIA_INFO_LOG("AudioSourceProcess sched_priority:%d", param.sched_priority);
    while (audioSourceManager->audioSourceStarted) {
        RecorderSourceBuffer buffer;
        int32_t ret = audioSourceManager->audioSource->AcquireBuffer(buffer, false);
        if (ret != SUCCESS) {
            MEDIA_ERR_LOG("audioSource Read failed ret:0x%x", ret);
            continue;
        }
        if (!audioSourceManager->audioSourcePaused) {
            FormatFrame frameData;
            frameData.frameType = FRAME_TYPE_AUDIO;
            frameData.trackId = audioSourceManager->audioTrackId;
            frameData.isKeyFrame = false;
            frameData.timestampUs = buffer.timeStamp;
            frameData.data = buffer.dataAddr;
            frameData.len = buffer.dataLen;
            ret = recorderSink->WriteData(audioSourceManager->audioTrackId, frameData);
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("Audio WriteData failed 0x%x", ret);
            }
        }
        audioSourceManager->audioSource->ReleaseBuffer(buffer);
    }
    MEDIA_INFO_LOG("audioSourceManager:%p  over", audioSourceManager);
}

int32_t Recorder::RecorderImpl::StartAudioSource()
{
    int32_t ret = 0;
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].audioSource != nullptr) {
            ret = sourceManager_[i].audioSource->Start();
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("audioSource Start  failed Ret: 0x%x", ret);
                return ret;
            }
            sourceManager_[i].audioSourceStarted = true;
            sourceManager_[i].audioProcessThread = std::thread(AudioSourceProcess, &sourceManager_[i], recorderSink_);
        }
    }
    MEDIA_INFO_LOG("Start Audio Source SUCCESS");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::StopAudioSource()
{
    int32_t ret = 0;
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].audioSource != nullptr) {
            MEDIA_DEBUG_LOG("audioSource->Stop");
            sourceManager_[i].audioSourceStarted = false;
            ret = sourceManager_[i].audioSource->Stop();
            MEDIA_DEBUG_LOG("audioSource->Stop out");
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("audioSource Stop  failed Ret: 0x%x", ret);
                return ret;
            }
            MEDIA_DEBUG_LOG("audioProcessThread.join");
            sourceManager_[i].audioProcessThread.join();
            MEDIA_DEBUG_LOG("audioProcessThread.join out");
        }
    }
    MEDIA_INFO_LOG("Stop Audio Source SUCCESS");
    return SUCCESS;
}

void VideoSourceProcess(const SourceManager *videoSourceManager, const RecorderSink *recorderSink)
{
    MEDIA_INFO_LOG("videoSourceManager:%p", videoSourceManager);
    if (videoSourceManager == nullptr) {
        return;
    }
    if (videoSourceManager->videoSource == nullptr || recorderSink == nullptr) {
        MEDIA_ERR_LOG("videoSource recorderSink is nullptr");
        return;
    }
    prctl(PR_SET_NAME, "VideoSourceProcess", 0, 0, 0);
    struct sched_param param = {};
    pthread_attr_t attr;
    pthread_attr_getschedparam(&attr, &param);
    param.sched_priority = RECORDER_VIDEO_THREAD_PRIORITY;
    pthread_setschedparam(pthread_self(), SCHED_RR, &param);
    MEDIA_INFO_LOG("VideoSourceProcess sched_priority:%d", param.sched_priority);
    while (videoSourceManager->videoSourceStarted) {
        RecorderSourceBuffer buffer;
        int32_t ret = videoSourceManager->videoSource->AcquireBuffer(buffer, true);
        if (ret != SUCCESS) {
            MEDIA_ERR_LOG("videoSource AcquireBuffer failed ret:0x%x", ret);
            continue;
        }
        if (!videoSourceManager->videoSourcePaused) {
            FormatFrame frameData;
            frameData.frameType = FRAME_TYPE_VIDEO;
            frameData.trackId = videoSourceManager->videoTrackId;
            frameData.isKeyFrame = buffer.keyFrameFlag;
            frameData.timestampUs = buffer.timeStamp;
            frameData.data = buffer.dataAddr;
            frameData.len = buffer.dataLen;
            ret = recorderSink->WriteData(videoSourceManager->videoTrackId, frameData);
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("video WriteData failed 0x%x", ret);
            }
        }
        videoSourceManager->videoSource->ReleaseBuffer(buffer);
    }
    MEDIA_INFO_LOG("videoSourceManager:%p over", videoSourceManager);
}


int32_t Recorder::RecorderImpl::StartVideoSource()
{
    int32_t ret = 0;
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].videoSource != nullptr) {
            ret = sourceManager_[i].videoSource->Start();
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("videoSource->Start  failed Ret: 0x%x", ret);
                return ret;
            }
            sourceManager_[i].videoSourceStarted = true;
            sourceManager_[i].videoProcessThread = std::thread(VideoSourceProcess, &sourceManager_[i], recorderSink_);
        }
    }
    MEDIA_INFO_LOG("Start Video Source SUCCESS");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::StopVideoSource()
{
    int32_t ret = 0;
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].videoSource != nullptr) {
            sourceManager_[i].videoSourceStarted = false;
            ret = sourceManager_[i].videoSource->Stop();
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("videoSource->Start  failed Ret: 0x%x", ret);
                return ret;
            }
            MEDIA_DEBUG_LOG("videoProcessThread.join");
            sourceManager_[i].videoProcessThread.join();
            MEDIA_DEBUG_LOG("videoProcessThread.join over");
        }
    }
    MEDIA_INFO_LOG("Stop Video Source SUCCESS");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::Start()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (status_ != PREPPARED &&
        status_ != PAUSED &&
        status_ != STOPPED) {
        MEDIA_ERR_LOG("Start ILLEGAL_STATE  status:%u", status_);
        return ERR_ILLEGAL_STATE;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    int32_t ret = recorderSink_->Start();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("recorderSink_  Start failed Ret: %d", ret);
        return ret;
    }
    ret = StartVideoSource();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("StartVideoSource  Start failed Ret: %d", ret);
        return ret;
    }
    ret = StartAudioSource();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("StartAudioSource  Start failed Ret: %d", ret);
        return ret;
    }
    MEDIA_INFO_LOG("Start Recorder SUCCESS");
    status_ = RECORDING;
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::PauseAudioSource()
{
    int32_t ret = 0;
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].audioSource != nullptr) {
            ret = sourceManager_[i].audioSource->Pause();
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("audioSource Pause  failed Ret: 0x%x", ret);
                return ret;
            }
            sourceManager_[i].audioSourcePaused = true;
        }
    }
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::PauseVideoSource()
{
    int32_t ret = 0;
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].videoSource != nullptr) {
            ret = sourceManager_[i].videoSource->Pause();
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("videoSource->Pause  failed Ret: 0x%x", ret);
                return ret;
            }
            sourceManager_[i].videoSourcePaused = true;
        }
    }
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::ResumeAudioSource()
{
    int32_t ret = 0;
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].audioSource != nullptr) {
            ret = sourceManager_[i].audioSource->Start();
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("audioSource Pause  failed Ret: 0x%x", ret);
                return ret;
            }
            sourceManager_[i].audioSourcePaused = false;
        }
    }
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::ResumeVideoSource()
{
    int32_t ret = 0;
    for (uint32_t i = 0; i < RECORDER_SOURCE_MAX_CNT; i++) {
        if (sourceManager_[i].videoSource != nullptr) {
            ret = sourceManager_[i].videoSource->Start();
            if (ret != SUCCESS) {
                MEDIA_ERR_LOG("videoSource->Start  failed Ret: 0x%x", ret);
                return ret;
            }
            sourceManager_[i].videoSourcePaused = false;
        }
    }
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::Pause()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (status_ != RECORDING) {
        MEDIA_ERR_LOG("Pause ILLEGAL_STATE  status:%u", status_);
        return ERR_ILLEGAL_STATE;
    }
    int32_t ret = PauseVideoSource();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("StopVideoSource  Pause failed Ret: %d", ret);
        return ret;
    }
    ret = PauseAudioSource();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("StopAudioSource  Pause failed Ret: %d", ret);
        return ret;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    ret = recorderSink_->Stop(false);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("recorderSink_ Stop ! ret: 0x%x", ret);
        return ret;
    }
    status_ = PAUSED;
    MEDIA_INFO_LOG("Pause Recorder SUCCESS");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::Resume()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (status_ != PAUSED) {
        MEDIA_ERR_LOG("Resume ILLEGAL_STATE  status:%u", status_);
        return ERR_ILLEGAL_STATE;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    int32_t ret = recorderSink_->Start();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("recorderSink_ Start ! ret: 0x%x", ret);
        return ret;
    }
    ret = ResumeVideoSource();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("VideoSource  Pause failed Ret: %d", ret);
        return ret;
    }
    ret = ResumeAudioSource();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("pAudioSource  Resume failed Ret: %d", ret);
        return ret;
    }
    status_ = RECORDING;
    MEDIA_INFO_LOG("Resume Recorder SUCCESS");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::Stop(bool block)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (status_ != RECORDING &&
        status_ != PAUSED) {
        MEDIA_ERR_LOG(" Stop ILLEGAL_STATE  status:%u", status_);
        return ERR_ILLEGAL_STATE;
    }
    int32_t ret = StopVideoSource();
    MEDIA_DEBUG_LOG("StopVideoSource");
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("StopVideoSource  Start failed Ret: %d", ret);
        return ret;
    }
    MEDIA_DEBUG_LOG("StopAudioSource");
    ret = StopAudioSource();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("StopAudioSource  Start failed Ret: %d", ret);
        return ret;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    ret = recorderSink_->Stop(block);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("recorderSink_ Stop ! ret: 0x%x", ret);
        return ret;
    }
    status_ = STOPPED;
    MEDIA_INFO_LOG("Stop Recorder SUCCESS");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::Reset()
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("Reset InitCheck err");
        return ret;
    }
    if (status_ == RECORDING ||
        status_ == PAUSED) {
        if ((ret = Stop(false)) != SUCCESS) {
            MEDIA_ERR_LOG("Reset Stop err");
            return ret;
        }
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    ret = recorderSink_->Reset();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG(" Reset err:0x%x", ret);
        return ret;
    }
    ret = ResetConfig();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG(" ResetConfig err:0x%x", ret);
        return ret;
    }
    status_ = RESETED;
    MEDIA_INFO_LOG("Reset Recorder SUCCESS");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::Release()
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("Release InitCheck err");
        return ret;
    }
    if (status_ == RECORDING ||
        status_ == PAUSED) {
        if ((ret = Stop(false)) != SUCCESS) {
            MEDIA_ERR_LOG("Release Stop err");
            return ret;
        }
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    ret = recorderSink_->Release();
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("recorderSink_  Release failed Ret: %d", ret);
        return ret;
    }
    status_ = RELEASED;
    MEDIA_INFO_LOG("Recorder Released");
    return SUCCESS;
}

int32_t Recorder::RecorderImpl::SetFileSplitDuration(FileSplitType type, int64_t timestamp, uint32_t duration)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (status_ != RECORDING) {
        MEDIA_ERR_LOG(" SetFileSplitDuration ILLEGAL_STATE  status:%u", status_);
        return ERR_ILLEGAL_STATE;
    }
    MEDIA_INFO_LOG("Set File Split Duration type:%d", type);
    ManualSplitType manualSplitType;
    switch (type) {
        case FILE_SPLIT_POST:
            manualSplitType = MANUAL_SPLIT_POST;
            break;
        case FILE_SPLIT_PRE:
            manualSplitType = MANUAL_SPLIT_PRE;
            break;
        case FILE_SPLIT_NORMAL:
            manualSplitType = MANUAL_SPLIT_NORMAL;
            break;
        default:
            MEDIA_ERR_LOG("unsupport FileSplitType type: %d", type);
            return ERR_INVALID_PARAM;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    return recorderSink_->SetFileSplitDuration(manualSplitType, timestamp, duration);
}

int32_t Recorder::RecorderImpl::SetParameter(int32_t sourceId, const Format &format)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int32_t ret;
    if ((ret = InitCheck()) != SUCCESS) {
        MEDIA_ERR_LOG("SetParameter InitCheck err");
        return ret;
    }
    CHECK_MEMBER_PTR_RETURN(recorderSink_);
    return recorderSink_->SetParameter(sourceId, format);
}
}  // namespace Media
}  // namespace OHOS

