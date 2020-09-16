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

#ifndef PLAYER_DEFINE_H
#define PLAYER_DEFINE_H

#include <stdint.h>
#include "securec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
#ifndef HI_SUCCESS
#define HI_SUCCESS 0
#endif

#ifndef HI_FAILURE
#define HI_FAILURE -1
#endif

typedef enum {
    ERR_AVPLAY_ILLEGAL_PARAM = 0x37,
    ERR_AVPLAY_NULL_PTR = 0x38,
    ERR_AVPLAY_NOMEM = 0x39,
    ERR_AVPLAY_INVALID_HANDLE = 0x40,
    ERR_AVPLAY_SRC_CREATE_FAILED = 0x41,
    ERR_AVPLAY_NOT_INITED = 0x42,
    ERR_AVPLAY_NOT_STARTED = 0x43,
    ERR_AVPLAY_ADEC_NOFREE = 0x44,
    ERR_AVPLAY_INVALID_OP = 0x45,
    ERR_AVPLAY_INVALID_VOHANDLE = 0x46,
    ERR_AVPLAY_THREAD_ERR = 0x47,
    ERR_AVPLAY_BUF_FULL = 0x48,
    ERR_AVPLAY_SOLOAD_FAILED = 0x49,
    ERR_AVPLAY_VIDEO_REND_ERR = 0x50,
    ERR_AVPLAY_AUDIO_REND_ERR = 0x51,
    ERR_AVPLAY_NOT_SUPPORT = 0x52,
    ERR_AVPLAY_VDEC_ERR = 0x53,
    ERR_AVPLAY_ADEC_ERR = 0x54,
    ERR_AVPLAY_SESSION_FULL = 0x55,
    ERR_AVPLAY_ADEC_REGED = 0x57,
    ERR_AVPLAY_ADEC_NOTREG = 0x58,
    ERR_AVPLAY_ADEC_DLOPEN = 0x59,
    ERR_AVPLAY_ADEC_DLSYM = 0x60,
    ERR_AVPLAY_AUDIO_REND_FULL = 0x61,
} HiAvplayErrCode;

static const int32_t HI_ERR_AVPLAY_ID = (0x80000000L + 0x61000000L);

#define HI_AVPLAY_DEF_ERR(errid) ((int32_t)((HI_ERR_AVPLAY_ID) | (errid)))

#define HI_ERR_AVPLAY_ILLEGAL_PARA      HI_AVPLAY_DEF_ERR(ERR_AVPLAY_ILLEGAL_PARAM)
#define HI_ERR_AVPLAY_NULL_PTR          HI_AVPLAY_DEF_ERR(ERR_AVPLAY_NULL_PTR)
#define HI_ERR_AVPLAY_NOMEM             HI_AVPLAY_DEF_ERR(ERR_AVPLAY_NOMEM)
#define HI_ERR_AVPLAY_INVALID_HANDLE    HI_AVPLAY_DEF_ERR(ERR_AVPLAY_INVALID_HANDLE)
#define HI_ERR_AVPLAY_SRC_CREATE_FAILED HI_AVPLAY_DEF_ERR(ERR_AVPLAY_SRC_CREATE_FAILED)
#define HI_ERR_AVPLAY_NOT_INITED        HI_AVPLAY_DEF_ERR(ERR_AVPLAY_NOT_INITED)
#define HI_ERR_AVPLAY_NOT_STARTED       HI_AVPLAY_DEF_ERR(ERR_AVPLAY_NOT_STARTED)
#define HI_ERR_AVPLAY_ADEC_NOFREE       HI_AVPLAY_DEF_ERR(ERR_AVPLAY_ADEC_NOFREE)
#define HI_ERR_AVPLAY_INVALID_OP        HI_AVPLAY_DEF_ERR(ERR_AVPLAY_INVALID_OP)
#define HI_ERR_AVPLAY_INVALID_VOHANDLE  HI_AVPLAY_DEF_ERR(ERR_AVPLAY_INVALID_VOHANDLE)
#define HI_ERR_AVPLAY_THREAD_ERR        HI_AVPLAY_DEF_ERR(ERR_AVPLAY_THREAD_ERR)
#define HI_ERR_AVPLAY_BUF_FULL          HI_AVPLAY_DEF_ERR(ERR_AVPLAY_BUF_FULL)
#define HI_ERR_AVPLAY_SOLOAD_FAILED     HI_AVPLAY_DEF_ERR(ERR_AVPLAY_SOLOAD_FAILED)
#define HI_ERR_AVPLAY_VIDEO_REND_ERR    HI_AVPLAY_DEF_ERR(ERR_AVPLAY_VIDEO_REND_ERR)
#define HI_ERR_AVPLAY_AUDIO_REND_ERR    HI_AVPLAY_DEF_ERR(ERR_AVPLAY_AUDIO_REND_ERR)
#define HI_ERR_AVPLAY_AUDIO_REND_FULL    HI_AVPLAY_DEF_ERR(ERR_AVPLAY_AUDIO_REND_FULL)
#define HI_ERR_AVPLAY_NOT_SUPPORT       HI_AVPLAY_DEF_ERR(ERR_AVPLAY_NOT_SUPPORT)
#define HI_ERR_AVPLAY_VDEC_ERR          HI_AVPLAY_DEF_ERR(ERR_AVPLAY_VDEC_ERR)
#define HI_ERR_AVPLAY_ADEC_ERR          HI_AVPLAY_DEF_ERR(ERR_AVPLAY_ADEC_ERR)
#define HI_ERR_AVPLAY_SESSION_FULL      HI_AVPLAY_DEF_ERR(ERR_AVPLAY_SESSION_FULL)
#define HI_ERR_AVPLAY_ADEC_REGED        HI_AVPLAY_DEF_ERR(ERR_AVPLAY_ADEC_REGED)
#define HI_ERR_AVPLAY_ADEC_NOTREG       HI_AVPLAY_DEF_ERR(ERR_AVPLAY_ADEC_NOTREG)
#define HI_ERR_AVPLAY_ADEC_DLOPEN       HI_AVPLAY_DEF_ERR(ERR_AVPLAY_ADEC_DLOPEN)
#define HI_ERR_AVPLAY_ADEC_DLSYM        HI_AVPLAY_DEF_ERR(ERR_AVPLAY_ADEC_DLSYM)

#define MAX_AUD_DECODER_PATH_LEN  256
static const uint32_t MAX_AVPLAY_SESSION_NUM   = 3;

typedef enum {
    MEDIA_TYPE_VIDEO,
    MEDIA_TYPE_VIDEO_AUDIO,
    MEDIA_TYPE_IMAGE,
    MEDIA_TYPE_AUDIO,
    MEDIA_TYPE_BUTT
} MediaType;

typedef enum {
    DATA_VIDEO,
    DATA_AUDIO,
    DATA_SUB,
    DATA_BUTT
} DataType;

enum EventCbType {
    EVNET_ON_STATE_CHANGE,
    EVNET_FIRST_VIDEO_REND,
    EVNET_VIDEO_PTS_ERRGAP,
    EVNET_AUDIO_PTS_ERRGAP,
    EVNET_VIDEO_RUNNING_ERR,
    EVNET_AUDIO_RUNNING_ERR,
    EVNET_VIDEO_PLAY_EOS,
    EVNET_VIDEO_PLAY_SOS,
    EVNET_AUDIO_PLAY_EOS,
    EVNET_ON_JPEG_FRAME_RENDED,
    EVNET_FRAME_CONTINUE_LOST,
    EVNET_BUTT
};

typedef enum {
    AVPLAY_ATTR_TYPE_STREAM, /* HiAvplayStreamAttr */
    AVPLAY_ATTR_TYPE_VDEC,   /* HiAvplayVdecAttr */
    AVPLAY_ATTR_TYPE_ADEC,   /* HiAvplayAdecAttr */
    AVPLAY_ATTR_TYPE_SYNC,   /* HiAvplaySyncAttr */
    AVPLAY_ATTR_TYPE_BUTT
} HiAvplayAttrType;

typedef enum {
    AVPLAY_CHN_TYPE_VID,
    AVPLAY_CHN_TYPE_AUD,
    AVPLAY_CHN_TYPE_BUTT
} HiAvplayChnType;

typedef enum {
    AVPLAY_SYNC_REF_VID,
    AVPLAY_SYNC_REF_AUD,
    AVPLAY_SYNC_REF_NONE,
    AVPLAY_SYNC_REF_BUTT
} HiAvplaySyncRefType;

enum TplayDirect {
    TPLAY_DIRECT_FORWARD,
    TPLAY_DIRECT_BACKWARD,
    TPLAY_DIRECT_BUTT
};

enum PlayerStatus {
    PLAY_STATUS_IDLE = 0,
    PLAY_STATUS_INIT,
    PLAY_STATUS_PREPARED,
    PLAY_STATUS_PLAY,
    PLAY_STATUS_TPLAY,
    PLAY_STATUS_PAUSE,
    PLAY_STATUS_ERR,
    PLAY_STATUS_BUTT
};

typedef enum {
    RENDER_MODE_NORMAL = 0,
    RENDER_MODE_PAUSE_AFTER_PLAY, /* pause after play the first frame */
    RENDER_MODE_BUTT
} RenderMode;

typedef struct {
    uint32_t reserved;
} HiAvplayResetOpt;

typedef struct {
    uint32_t reserved;
} HiAvplayPauseOpt;

typedef struct {
    uint32_t reserved;
} HiAvplayResumeOpt;

typedef struct {
    uint32_t reserved;
} HiAvplayStartOpt;

typedef struct {
    uint32_t reserved;
} HiAvplayStopOpt;

typedef struct {
    void *data;
    uint32_t dataLen;
    int64_t pts;
    int64_t dts;
} HiAvplayStreamDataInfo;

typedef struct {
    int32_t type;
    uint32_t maxWidth;
    uint32_t maxHeight;
    uint32_t frameBufCnt;
    uint32_t errRecover;
} HiAvplayVdecAttr;

typedef struct {
    int32_t type;
    uint32_t sampleRate;
    uint32_t channel;
    uint32_t bitWidth; /* bits */
} HiAvplayAdecAttr;

typedef struct {
    /* Plus time range during video synchronization */
    uint32_t vidPlusTime;
    /* Negative time range during video synchronization */
    uint32_t vidNegativeTime;
} HiAvplaySyncRegion;

typedef struct {
    RenderMode playMode;
    uint32_t videoBufSize;
    uint32_t audioBufSize;
} HiAvplayStreamAttr;

struct PlaySyncAttr {
    HiAvplaySyncRefType refType;
    HiAvplaySyncRegion syncStartRegion;
    HiAvplaySyncRegion syncStopRegion;
    bool isQuickOutput;
};

typedef struct {
    union {
        HiAvplayStreamAttr streamAttr;
        HiAvplayVdecAttr vdecAttr;
        HiAvplayAdecAttr adecAttr;
        PlaySyncAttr syncAttr;
    };
} HiAvplayAttrOpt;

struct PlayVideoStreamInfo {
    uint32_t decWidth;
    uint32_t decHeight;
    uint32_t fpsInteger;
    uint32_t fpsDecimal;
    uint32_t freeEsBufSize;
    uint32_t esBufSize;
};

struct PlayAudioStreamInfo {
    uint32_t sampleRate;
    uint32_t channel; /* only support 1-2 */
    uint32_t bitwith;
    uint32_t freeEsBufSize;
    uint32_t esBufSize;
};

struct PlaySyncStatus {
    int64_t firstVidPts;
    int64_t lastVidPts;
    int64_t firstAudPts;
    int64_t lastAudPts;
    int64_t localTime;
    int64_t diffTime;
};

typedef enum {
    DECODER_STATUS_IDLE = 0,
    DECODER_STATUS_PLAY,
    DECODER_STATUS_TPLAY,
    DECODER_STATUS_PAUSE,
    DECODER_STATUS_ERR,
    DECODER_STATUS_BUTT
} DecoderStatus;

struct PlayStatusInfo {
    DecoderStatus vidStatus;
    DecoderStatus audStatus;
    PlaySyncStatus syncStatus;
    uint64_t vidFrameCount;
    uint64_t audFrameCount;
    uint64_t nonDecVidCnt;
};

struct PlayerStreamInfo {
    PlayVideoStreamInfo videoInfo;
    PlayAudioStreamInfo audioInfo;
    PlayStatusInfo avStatus;
};

struct TplayAttr {
    TplayDirect direction;
    float speed;
};

struct VolumeAttr {
    float leftVolume;
    float rightVolume;
};

enum PlaySpeed {
    PLAY_SPEED_BASE = 1,
    PLAY_SPEED_2X_FAST = 2,     /* 2 x speed fast */
    PLAY_SPEED_4X_FAST = 4,     /* 4 x speed fast */
    PLAY_SPEED_8X_FAST = 8,     /* 8 x speed fast */
    PLAY_SPEED_16X_FAST = 16,   /* 16 x speed fast */
    PLAY_SPEED_32X_FAST = 32,   /* 32 x speed fast */
    PLAY_SPEED_64X_FAST = 64,   /* 64 x speed fast */
    PLAY_SPEED_128X_FAST = 128, /* 128 x speed fast */
    PLAY_SPEED_BUTT             /* Invalid speed value */
};

typedef int32_t (*OnEventCallback)(void* priv, EventCbType event, int32_t ext1, int32_t ext2);

typedef int32_t (*OnStateChangeCallback)(void* priv, PlayerStatus status);

typedef struct {
    OnEventCallback onEventCallback;
    OnStateChangeCallback onStatusChange;
    void* priv;
} PlayEventCallback;

/* Defines the attributes when an Avplay is step. */
typedef struct {
    uint32_t reserved;
} HiAvplayStepOpt;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* PLAYER_DEFINE_H */
