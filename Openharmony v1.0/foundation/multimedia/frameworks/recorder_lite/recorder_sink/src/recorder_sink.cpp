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

#include "recorder_sink.h"
#include "format_interface.h"
#include "media_log.h"
#include "securec.h"

namespace OHOS {
namespace Media {
constexpr uint32_t RECORDER_PARAMS_CNT = 2;
RecorderSink::RecorderSink()
    :formatMuxerHandle_(nullptr),
     prepared_(false),
     started_(false),
     outputFormat_(OUTPUT_FORMAT_INVALID),
     outputFd_(-1),
     path_(""),
     maxFileSize_(-1),
     maxDuration_(-1)
{
    FormatInit();
    if (memset_s(&outputConfig_, sizeof(FormatOutputConfig), 0, sizeof(FormatOutputConfig)) != EOK) {
        MEDIA_ERR_LOG("memset_s failed %s ", path_.c_str());
    }
}

RecorderSink::~RecorderSink()
{
    FormatDeInit();
}

int32_t RecorderSink::CheckPrepared()
{
    if (!prepared_) {
        MEDIA_ERR_LOG("RecorderSink not prepared yet");
        return ERR_ILLEGAL_STATE;
    }
    return SUCCESS;
}

int32_t RecorderSink::CheckStarted() const
{
    if (!started_) {
        MEDIA_ERR_LOG("RecorderSink not started yet");
        return ERR_ILLEGAL_STATE;
    }
    return SUCCESS;
}

int32_t RecorderSink::SetOutputPath(const string &path)
{
    path_ = path;
    return SUCCESS;
}

int32_t RecorderSink::Prepare()
{
    if (prepared_) {
        return SUCCESS;
    }
    outputConfig_.format = outputFormat_;
    if (outputFd_ != -1) {
        outputConfig_.type = OUTPUT_TYPE_FD;
        outputConfig_.fd = outputFd_;
    } else {
        outputConfig_.type = OUTPUT_TYPE_URI;
        if (memcpy_s(outputConfig_.url, URL_LEN, path_.c_str(), path_.length()) != EOK) {
            MEDIA_ERR_LOG("memcpy_s failed %s ", path_.c_str());
            return ERR_INVALID_PARAM;
        }
    }
    int32_t ret = FormatMuxerCreate(&formatMuxerHandle_, &outputConfig_);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("FormatMuxerCreate failed 0x%x  outputFd_:%d", ret, outputFd_);
        return ret;
    }
    prepared_ = true;
    if (maxDuration_ != -1) {
        ret = FormatMuxerSetMaxFileDuration(formatMuxerHandle_, maxDuration_);
        if (ret != SUCCESS) {
            MEDIA_ERR_LOG("FormatMuxersetMaxFileDuration failed 0x%x", ret);
        }
    }
    if (maxFileSize_ != -1) {
        ret = FormatMuxerSetMaxFileSize(formatMuxerHandle_, maxFileSize_);
        if (ret != SUCCESS) {
            MEDIA_ERR_LOG("FormatMuxersetMaxFileSize failed 0x%x", ret);
        }
    }
    return SUCCESS;
}

int32_t RecorderSink::AddTrackSource(const TrackSource &trackSource, int32_t &trackId)
{
    int32_t trackIndex = FormatMuxerAddTrack(formatMuxerHandle_, &trackSource);
    if (trackIndex < 0) {
        MEDIA_ERR_LOG("FormatMuxerAddTrack failed 0x%x ", trackIndex);
        return trackIndex;
    }
    trackId = trackIndex;
    return SUCCESS;
}

int32_t RecorderSink::WriteData(int32_t trackId, FormatFrame &frameData) const
{
    if (CheckStarted() != SUCCESS) {
        return ERR_ILLEGAL_STATE;
    }
    return FormatMuxerWriteFrame(formatMuxerHandle_, &frameData);
}

int32_t RecorderSink::SetOutputFormat(OutputFormat format)
{
    outputFormat_ = format;
    return SUCCESS;
}

int32_t RecorderSink::SetOutputFile(int32_t fd)
{
    outputFd_ = fd;
    return SUCCESS;
}

int32_t RecorderSink::SetNextOutputFile(int32_t fd)
{
    if (CheckPrepared() != SUCCESS) {
        return ERR_ILLEGAL_STATE;
    }
    return FormatMuxerSetNextOutputFile(formatMuxerHandle_, fd);
}

int32_t RecorderSink::SetMaxDuration(int64_t duration)
{
    if (started_) {
        MEDIA_ERR_LOG("RecorderSink is started ,SetMaxDuration must be setted before Prepare");
        return ERR_ILLEGAL_STATE;
    }
    if (duration <= 0) {
        MEDIA_ERR_LOG("invalid  MaxDuration size:%lld", duration);
        return ERR_INVALID_PARAM;
    }
    maxDuration_ = duration;
    if (prepared_) {
        return FormatMuxerSetMaxFileDuration(formatMuxerHandle_, duration);
    }
    return SUCCESS;
}

int32_t RecorderSink::SetMaxFileSize(int64_t size)
{
    if (started_) {
        MEDIA_ERR_LOG("RecorderSink is started , SetMaxFileSize must setted before Prepare");
        return ERR_ILLEGAL_STATE;
    }
    if (size <= 0) {
        MEDIA_ERR_LOG("invalid  MaxFileSize size:%lld", size);
        return ERR_INVALID_PARAM;
    }
    maxFileSize_ = size;
    if (prepared_) {
        return FormatMuxerSetMaxFileSize(formatMuxerHandle_, size);
    }
    return SUCCESS;
}

int32_t RecorderSink::SetOrientationHint(int degrees)
{
    if (CheckPrepared() != SUCCESS) {
        return ERR_ILLEGAL_STATE;
    }
    return FormatMuxerSetOrientation(formatMuxerHandle_, degrees);
}

int32_t RecorderSink::SetLocation(int latitude, int longitude)
{
    if (CheckPrepared() != SUCCESS) {
        return ERR_ILLEGAL_STATE;
    }
    return FormatMuxerSetLocation(formatMuxerHandle_, latitude, longitude);
}

int32_t RecorderSink::SendCallbackInfo(int32_t type, int32_t extra)
{
    if (recCallBack_ == nullptr) {
        MEDIA_ERR_LOG("sink: is nullptr");
        return ERR_INVALID_PARAM;
    }
    switch (type) {
        case MUXER_INFO_MAX_DURATION_APPROACHING:
        case MUXER_INFO_MAX_FILESIZE_APPROACHING:
        case MUXER_INFO_MAX_DURATION_REACHED:
        case MUXER_INFO_MAX_FILESIZE_REACHED:
        case MUXER_INFO_NEXT_OUTPUT_FILE_STARTED:
        case MUXER_INFO_FILE_SPLIT_FINISHED:
        case MUXER_INFO_FILE_START_TIME_MS:
            recCallBack_->OnInfo(type, extra);
            return SUCCESS;
        default:
            MEDIA_ERR_LOG("pass event type %d", type);
            return ERR_INVALID_PARAM;
    }
}

int32_t RecorderSink::SendCallbackError(int32_t errorType, int32_t errorCode)
{
    MEDIA_INFO_LOG("errorType:%d", errorType);
    if (recCallBack_ == nullptr) {
        MEDIA_ERR_LOG("sink: is nullptr");
        return ERR_INVALID_PARAM;
    }
    switch (errorType) {
        case ERROR_UNKNOWN:
            MEDIA_ERR_LOG("recorder Callback error");
            recCallBack_->OnError(errorType, errorCode);
            return SUCCESS;
        default:
            MEDIA_ERR_LOG("pass event err %d", errorType);
            return ERR_INVALID_PARAM;
    }
}

int32_t SinkOnError(CALLBACK_HANDLE privateDataHandle, int32_t errorType, int32_t errorCode)
{
    RecorderSink *sink = reinterpret_cast<RecorderSink *>(privateDataHandle);
    if (sink == nullptr) {
        MEDIA_ERR_LOG("sink: is nullptr");
        return ERR_INVALID_PARAM;
    }
    return sink->SendCallbackError(errorType, errorCode);
}

int32_t SinkOnInfo(CALLBACK_HANDLE privateDataHandle, int32_t type, int32_t extra)
{
    MEDIA_INFO_LOG("type:%d", type);
    RecorderSink *sink = reinterpret_cast<RecorderSink *>(privateDataHandle);
    if (sink == nullptr) {
        MEDIA_ERR_LOG("sink: is nullptr");
        return ERR_INVALID_PARAM;
    }
    return sink->SendCallbackInfo(type, extra);
}


int32_t RecorderSink::SetRecorderCallback(const std::shared_ptr<RecorderCallback> &callback)
{
    if (started_) {
        MEDIA_ERR_LOG("RecorderSink is started , SetMaxFileSize must setted before Prepare");
        return ERR_ILLEGAL_STATE;
    }
    recCallBack_ = callback;
    sinkCallback_ = std::make_shared<FormatCallback>();
    sinkCallback_->privateDataHandle = this;
    sinkCallback_->OnError = SinkOnError;
    sinkCallback_->OnInfo = SinkOnInfo;
    return SUCCESS;
}

int32_t RecorderSink::Start()
{
    if (CheckPrepared() != SUCCESS) {
        return ERR_ILLEGAL_STATE;
    }
    if (started_) {
        return SUCCESS;
    }
    int32_t ret;
    if (recCallBack_ != nullptr &&
        sinkCallback_ != nullptr) {
        ret = FormatMuxerSetCallBack(formatMuxerHandle_, sinkCallback_.get());
        MEDIA_ERR_LOG("FormatMuxerSetCallBack :%p ret: 0x%x",
                      recCallBack_.get(), ret);
    }
    ret = FormatMuxerStart(formatMuxerHandle_);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("FormatMuxerStart failed 0x%x", ret);
        return ret;
    }
    started_ = true;
    return SUCCESS;
}

int32_t RecorderSink::Stop(bool block)
{
    if (!started_) {
        MEDIA_INFO_LOG("RecorderSink is stoped or not started");
        return SUCCESS;
    }
    int32_t ret = FormatMuxerStop(formatMuxerHandle_, block);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("FormatMuxerStop failed 0x%x", ret);
        return ret;
    }
    started_ = false;
    return SUCCESS;
}

int32_t RecorderSink::Reset()
{
    int32_t ret;
    if (started_) {
        ret = Stop(false);
        if (ret != SUCCESS) {
            MEDIA_ERR_LOG("Stop failed 0x%x", ret);
            return ret;
        }
    }
    if (prepared_) {
        ret = Release();
        if (ret != SUCCESS) {
            MEDIA_ERR_LOG("Release failed 0x%x", ret);
            return ret;
        }
    }
    prepared_ = false;
    outputFormat_ = OUTPUT_FORMAT_INVALID;
    outputFd_ = -1;
    maxFileSize_ = -1;
    maxDuration_ = -1;
    return SUCCESS;
}

int32_t RecorderSink::Release()
{
    int32_t ret;
    if (started_) {
        ret = Stop(false);
        if (ret != SUCCESS) {
            MEDIA_ERR_LOG("Stop failed 0x%x", ret);
            return ret;
        }
        started_ = false;
    }
    ret = FormatMuxerDestory(formatMuxerHandle_);
    if (ret != SUCCESS) {
        MEDIA_ERR_LOG("FormatMuxerDestory failed Ret: 0x%x", ret);
        return ret;
    }
    formatMuxerHandle_ = nullptr;
    prepared_ = false;
    return SUCCESS;
}

int32_t RecorderSink::SetFileSplitDuration(ManualSplitType type, int64_t timestamp, uint32_t duration)
{
    if (CheckStarted() != SUCCESS) {
        return ERR_ILLEGAL_STATE;
    }
    return FormatMuxerSetFileSplitDuration(formatMuxerHandle_, type, timestamp, duration);
}

int32_t RecorderSink::SetParameter(int32_t trackId, const Format &format)
{
    int32_t itemNum = 0;
    ParameterItem items[RECORDER_PARAMS_CNT];
    memset_s(items, sizeof(ParameterItem) * RECORDER_PARAMS_CNT, 0x00,
             sizeof(ParameterItem) * RECORDER_PARAMS_CNT);
    int32_t value;
    if (format.GetIntValue(RCORDER_PRE_CACHE_DURATION, value)) {
        items[itemNum].key = KEY_TYPE_PRE_CACHE;
        items[itemNum].value.s32Value = value;
        items[itemNum].size = sizeof(int32_t);
        itemNum++;
    } else {
        return ERR_INVALID_PARAM;
    }
    return FormatMuxerSetParameter(formatMuxerHandle_, trackId, items, itemNum);
}
}  // namespace Media
}  // namespace OHOS
