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

#ifndef HI_DEMUXER_H
#define HI_DEMUXER_H

#include "format_type.h"

/** \addtogroup     PLAYER */
/** @{ */ /** <!-- [PLAYER] */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define HI_DEMUXER_NAME_LEN           20
#define HI_DEMUXER_SUPPORT_NAMES_LEN  56
#define HI_DEMUXER_RESOLUTION_CNT     5
#define HI_DEMUXER_NO_MEDIA_STREAM    (-1)

#define HI_DEMUXER_EMTRY_NAME "g_stFormatEntry"

#define HI_DEMUXER_SEEK_FORWARD   1
#define HI_DEMUXER_SEEK_BACKWARD  2

#define HI_RET_FILE_EOF  2
#define HI_RET_NODATA  3

struct FormatMediaAttr {
    int32_t s32VidStreamId; /**< Video stream ID. */
    int32_t s32AudStreamId; /**< Audio stream ID. */
};

typedef enum hiFORMAT_VIDEO_TYPE_E {
    HI_FORMAT_VIDEO_TYPE_H264,
    HI_FORMAT_VIDEO_TYPE_H265,
    HI_FORMAT_VIDEO_TYPE_JPEG,
    HI_FORMAT_VIDEO_TYPE_BUTT
} HI_FORMAT_VIDEO_TYPE_E;

typedef enum hiFORMAT_AUDIO_TYPE_E {
    HI_FORMAT_AUDIO_TYPE_AAC,
    HI_FORMAT_AUDIO_TYPE_PCM,
    HI_FORMAT_AUDIO_TYPE_G711A,
    HI_FORMAT_AUDIO_TYPE_G711U,
    HI_FORMAT_AUDIO_TYPE_MP3,
    HI_FORMAT_AUDIO_TYPE_BUTT
} HI_FORMAT_AUDIO_TYPE_E;

typedef struct {
    int32_t s32VideoStreamIndex; /**< the index of the video stream */
    uint32_t u32Width;            /**< The height of the media file's resolution */
    uint32_t u32Height;           /**< The width of the media file's resolution */
    CodecFormat enVideoType;
} StreamResolution;

typedef struct {
    int64_t s64FileSize;  /**< File size, in the unit of byte. */
    int64_t s64StartTime; /* the media file begin time */
    int64_t s64Duration;  /**< Total duration of a file, in the unit of ms. */
    StreamResolution stSteamResolution[HI_DEMUXER_RESOLUTION_CNT];
    int32_t s32UsedVideoStreamIndex; /* <default used video index> */
    float fFrameRate;            /**< the frame rate of the stream */
    uint32_t u32Bitrate;              /**< File bit rate, in the unit of bit/s. */
    uint32_t u32AudioChannelCnt;
    uint32_t u32SampleRate;           /**< the sample rate of the audio stream */
    int32_t s32UsedAudioStreamIndex; /**< the index of the audio stream. one file may have many audio streams */
    uint32_t u32Width;            /**< The height of the media file's resolution */
    uint32_t u32Height;           /**< The width of the media file's resolution */
    CodecFormat enVideoType;
    CodecFormat enAudioType;
} FormatFileInfo;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
