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
#include "player_demux.h"
#include <memory>
#include "format_type.h"
#include "media_log.h"
extern "C"
{
#include "format_interface.h"
}

using namespace std;

namespace OHOS {
namespace Media {
#define READ_FRAME_TIMEOUT 20

#define CHECK_NULL_RETURN(value, printfString) \
do { \
    if (value == nullptr) { \
        MEDIA_ERR_LOG(" %s ", printfString ? printfString : " "); \
        return -1; \
    } \
} while (0)

#define CHECK_FAILED_RETURN(value, target, ret, printfString) \
do { \
    if (value != target) { \
        MEDIA_ERR_LOG(" %s ", printfString ? printfString : " "); \
        return ret; \
    } \
} while (0)

PlayerDemuxer::PlayerDemuxer()
    : m_inited_(false),
      m_prepared_(false),
      m_started_(false),
      m_demuxer_(nullptr),
      m_sourceType_(SOURCE_TYPE_BUT),
      m_fd_(-1)
{
    m_stream_ = {};
    m_formatListener_ = {};
    m_callBack_ = {};
}

PlayerDemuxer::~PlayerDemuxer()
{
    if (m_demuxer_ != nullptr) {
        FormatDemuxerDestory(m_demuxer_);
        m_demuxer_ = nullptr;
    }
}

int32_t PlayerDemuxer::Init(void)
{
    m_formatListener_.OnError = ErrorEventPro;
    m_formatListener_.OnInfo = InfoEventPro;
    m_inited_ = true;
    return 0;
}

int32_t PlayerDemuxer::ErrorEventPro(void *handle, int32_t errorType, int32_t errorCode)
{
    return 0;
}

int32_t PlayerDemuxer::InfoEventPro(void *handle, int32_t type, int32_t extra)
{
    return 0;
}

int32_t PlayerDemuxer::GetFormatDemuxer(void)
{
    int ret;
    FormatSource source;

    source.type = m_sourceType_;
    if (m_sourceType_ == SOURCE_TYPE_FD) {
        source.fd = m_fd_;
    } else if (m_sourceType_ == SOURCE_TYPE_URI) {
        if (strncpy_s(source.url, URL_LEN, m_filePath_.c_str(), m_filePath_.size()) != 0) {
            return -1;
        }
    } else {
        source.stream = &m_stream_;
    }
    ret = FormatDemuxerCreate(&source, &m_demuxer_);
    if (ret != 0 || m_demuxer_ == nullptr) {
        MEDIA_ERR_LOG("FormatDemuxerCreate failed\n");
        return -1;
    }
    return 0;
}

int32_t PlayerDemuxer::SetSource(int fd)
{
    CHECK_FAILED_RETURN(m_inited_, true, -1, "not inited");
    m_fd_ = fd;
    m_sourceType_ = SOURCE_TYPE_FD;
    CHECK_FAILED_RETURN(GetFormatDemuxer(), 0, -1, " ");
    return 0;
}

int32_t PlayerDemuxer::SetSource(const char *url)
{
    CHECK_FAILED_RETURN(m_inited_, true, -1, "not inited");
    m_filePath_ = std::string(url);
    m_sourceType_ = SOURCE_TYPE_URI;
    CHECK_FAILED_RETURN(GetFormatDemuxer(), 0, -1, " ");
    return 0;
}

int32_t PlayerDemuxer::SetSource(BufferStream &stream)
{
    CHECK_FAILED_RETURN(m_inited_, true, -1, "not inited");
    m_stream_ = stream;
    m_sourceType_ = SOURCE_TYPE_STREAM;
    CHECK_FAILED_RETURN(GetFormatDemuxer(), 0, -1, " ");
    return 0;
}

int32_t PlayerDemuxer::SetCallBack(PlayEventCallback &callBack)
{
    CHECK_FAILED_RETURN(m_inited_, true, -1, "not inited");
    m_callBack_ = callBack;
    return 0;
}

int32_t PlayerDemuxer::Prepare(void)
{
    CHECK_FAILED_RETURN(m_inited_, true, -1, "not inited");
    CHECK_FAILED_RETURN(FormatDemuxerSetCallBack(m_demuxer_, &m_formatListener_), 0, -1, "");
    CHECK_FAILED_RETURN(FormatDemuxerPrepare(m_demuxer_), 0, -1, "");
    m_prepared_ = true;
    return 0;
}

int32_t PlayerDemuxer::GetFileInfo(FormatFileInfo &fileInfo)
{
    uint32_t i;
    FileInfo info;
    int programId = -1;
    int trackId[2] = {-1, -1};
    int trackNum = 2;
    ProgramInfo *programInfo = nullptr;
    CHECK_FAILED_RETURN(m_prepared_, true, -1, "not prepared");
    CHECK_FAILED_RETURN(FormatDemuxerGetFileInfo(m_demuxer_, &info), 0, -1, "");
    CHECK_FAILED_RETURN(FormatDemuxerGetSelectedTrack(m_demuxer_, &programId, trackId, &trackNum), 0, -1, "");

    if (programId == -1 || trackNum == 0 || trackId[0] == -1) {
        MEDIA_ERR_LOG("FormatDemuxerGetSelectedTrack failed");
        return -1;
    }

    fileInfo.s64FileSize = -1;
    fileInfo.s64StartTime = 0;
    fileInfo.u32Bitrate = info.bitrate;
    if (info.programNum == 1) {
        programInfo = &info.programInfo[0];
    } else {
        for (i = 0; i < info.programNum; i++) {
            if (info.programInfo[i].programId == programId) {
                programInfo = &info.programInfo[i];
            }
        }
    }
    if (programInfo == nullptr) {
        MEDIA_ERR_LOG("can not find the program");
        return -1;
    }
    fileInfo.s64Duration = programInfo->durationMs;
    fileInfo.s32UsedVideoStreamIndex = -1;
    fileInfo.s32UsedAudioStreamIndex = -1;
    for (i = 0; i < programInfo->trackNum; i++) {
        if (programInfo->track[i].trackId == trackId[0] || programInfo->track[i].trackId == trackId[1]) {
            if (programInfo->track[i].trackType == TRACK_TYPE_VIDEO) {
                fileInfo.s32UsedVideoStreamIndex = programInfo->track[i].trackId;
                fileInfo.u32Width = programInfo->track[i].vidTrack.width;
                fileInfo.u32Height = programInfo->track[i].vidTrack.height;
                fileInfo.enVideoType = programInfo->track[i].vidTrack.format;
            } else if (programInfo->track[i].trackType == TRACK_TYPE_AUDIO) {
                fileInfo.s32UsedAudioStreamIndex = programInfo->track[i].trackId;
                fileInfo.u32AudioChannelCnt = programInfo->track[i].audTrack.channels;
                fileInfo.u32SampleRate = programInfo->track[i].audTrack.sampleRate;
                fileInfo.enAudioType = programInfo->track[i].audTrack.format;
            }
        }
    }
    int index = 0;
    uint32_t j;
    for (i = 0; i < info.programNum; i++) {
        programInfo = &info.programInfo[i];
        for (j = 0; i < programInfo->trackNum; i++) {
            if (programInfo->track[j].trackType == TRACK_TYPE_VIDEO) {
                fileInfo.stSteamResolution[index].s32VideoStreamIndex = programInfo->track[j].trackId;
                fileInfo.stSteamResolution[index].u32Width = programInfo->track[j].vidTrack.width;
                fileInfo.stSteamResolution[index].u32Height = programInfo->track[j].vidTrack.height;
                fileInfo.stSteamResolution[index].enVideoType = programInfo->track[j].vidTrack.format;
                index++;
            }
        }
    }
    return 0;
}

int32_t PlayerDemuxer::SelectTrack(int32_t programId, int32_t trackId)
{
    CHECK_FAILED_RETURN(m_prepared_, true, -1, "not prepared");
    return FormatDemuxerSelectTrack(m_demuxer_, programId, trackId);
}

int32_t PlayerDemuxer::UnselectTrack(int32_t programId, int32_t trackId)
{
    CHECK_FAILED_RETURN(m_prepared_, true, -1, "not prepared");
    return FormatDemuxerUnselectTrack(m_demuxer_, programId, trackId);
}

int32_t PlayerDemuxer::GetSelectedTrack(int32_t &programId, int32_t trackId[], int32_t &nums)
{
    CHECK_FAILED_RETURN(m_prepared_, true, -1, "not prepared");
    return FormatDemuxerGetSelectedTrack(m_demuxer_, &programId, trackId, &nums);
}

int32_t PlayerDemuxer::Start()
{
    CHECK_FAILED_RETURN(m_prepared_, true, -1, "not prepared");
    CHECK_FAILED_RETURN(FormatDemuxerStart(m_demuxer_), 0, -1, "");
    m_started_ = true;
    return 0;
}

int32_t PlayerDemuxer::ReadFrame(FormatFrame &frame)
{
    CHECK_FAILED_RETURN(m_started_, true, -1, "not started");
    return FormatDemuxerReadFrame(m_demuxer_, &frame, READ_FRAME_TIMEOUT);
}

int32_t PlayerDemuxer::FreeFame(FormatFrame &frame)
{
    CHECK_FAILED_RETURN(m_started_, true, -1, "not started");
    return FormatDemuxerFreeFrame(m_demuxer_, &frame);
}

int32_t PlayerDemuxer::Seek(int32_t streamIndex, int64_t timeStampUs, FormatSeekMode mode)
{
    CHECK_FAILED_RETURN(m_started_, true, -1, "not started");
    return FormatDemuxerSeek(m_demuxer_, streamIndex, timeStampUs, mode);
}

int32_t PlayerDemuxer::Stop()
{
    if (m_demuxer_ == nullptr) {
        return 0;
    }
    return FormatDemuxerStop(m_demuxer_);
}

int32_t PlayerDemuxer::SetParam(int32_t trackId, const ParameterItem *metaData, int32_t metaDataCnt)
{
    CHECK_FAILED_RETURN(m_inited_, true, -1, "not inited");
    return FormatDemuxerSetParameter(m_demuxer_, trackId, metaData, metaDataCnt);
}

int32_t PlayerDemuxer::GetParam(int32_t trackId, ParameterItem &metaData)
{
    CHECK_FAILED_RETURN(m_inited_, true, -1, "not inited");
    return FormatDemuxerGetParameter(m_demuxer_, trackId, &metaData);
}
}  // namespace Media
}  // namespace OHOS
