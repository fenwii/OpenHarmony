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

#ifndef LITEPLAYER_DEFINE_H
#define LITEPLAYER_DEFINE_H
#include <pthread.h>
#include "player_define.h"
#include "media_log.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

static const char * const MOD_NAME_PLAYER = "Player";

static const uint32_t  MS_SCALE   = 1000;
static const int64_t INVALID_PTS = -1;

#ifdef __HuaweiLite__
static const uint32_t MAX_DEMUX_LIBNAME_LEN = 256;
#endif

static const uint32_t MAX_STATE_WAIT_TIMES = 50;
static const uint32_t FULL_TPLAY_FRAMERATE_LIMIT = 30;
/* DEFAULT_BITRATE: 2 * 1024 */
static const uint32_t FULL_TPLAY_BITRATE_LIMIT = 2048;
/* TPLAY_FULL_LIMIT_RESULITON: 1024 * 576 */
static const uint32_t FULL_TPLAY_RESULITON_LIMIT   = 589824;
static const uint32_t HI_RET_SKIP_PACKET   = 1;
static const uint32_t EXTRA_MBUF_LEN = 1500;

static const char * const FF_VDEC_LIB_NAME = "libffmpeg_demuxer.so";

/* default playing pos notify in ms */
static const uint32_t DELAYUS_ON_BUFFER_FULL = 5000;
static const uint32_t DELAYUS_ON_DEMUX_READ_END  = 30000;
/* MAX_REPLY_WAIT_TIME: 5000 * 1000 us */
static const uint64_t MAX_REPLY_WAIT_TIME = 5000000;

static const uint32_t TPLAY_SPEED_DECIMAL_PRECISION  = 1000;
static const uint32_t AUDIO_BITWIDTH = 16;
static const uint32_t MIN_NOTIFY_INTERVAL_MS = 50;
static const int32_t OFFSET_INCREASE_FOR_FRAME_LOST = 2;
/* video es stream buf max limit size: (200 * 1024 * 1024) */
static const uint32_t VIDEO_ESBUF_SIZE_LIMIT = 209715200;
/* audio es stream buf max limit size: (100 * 1024 * 1024) */
static const uint32_t AUDIO_ESBUF_SIZE_LIMIT = 104857600;
static const uint32_t AV_ESBUF_SIZE_MIN  = 1024;
static const uint32_t VDEC_VBBUF_CONUT_MIN  = 3;

static const uint32_t PLAYER_8K_WIDTH = 7680;
static const uint32_t PLAYER_8K_HEIGHT = 4320;
/* PLAYER_VID_BUF_SIZE_LEVEL1: (24 * 1024 * 1024) */
static const uint32_t PLAYER_VID_BUF_SIZE_LEVEL1  = 25165824;
/* PLAYER_VID_BUF_SIZE_LEVEL2: (12 * 1024 * 1024) */
static const uint32_t PLAYER_VID_BUF_SIZE_LEVEL2  = 12582912;
/* PLAYER_VID_BUF_SIZE_LEVEL3: (8 * 1024 * 1024) */
static const uint32_t PLAYER_VID_BUF_SIZE_LEVEL3 = 8388608;
/* PLAYER_VID_BUF_SIZE_LEVEL4: (4 * 1024 * 1024) */
static const uint32_t PLAYER_VID_BUF_SIZE_LEVEL4 = 4194304;

static const uint32_t PLAYER_4K_WIDTH  = 3840;
static const uint32_t PLAYER_4K_HEIGHT = 2160;
static const uint32_t PLAYER_1080P_WIDTH = 1920;
static const uint32_t PLAYER_1080P_HEIGHT = 1080;

/* PLAYER_MPF_MBUF_SIZE: (600 * 1024) */
static const uint32_t PLAYER_MPF_MBUF_SIZE = 614400;
/* PLAYER_MPF_BUF_EXTRA: (2 * 1024) */
static const uint32_t PLAYER_MPF_BUF_EXTRA = 2048;
/* PLAYER_MPF_ESBUF_MIN: (32 * 1024) */
static const uint32_t PLAYER_MPF_ESBUF_MIN = 32768;

static const int32_t AV_INVALID_PTS = -1;

static const uint32_t NO_WAIT = 0;

static const uint32_t ZERO_ARG = 0;

static const uint32_t MAX_MSG_QUEUE_SIZE = 50;

static const uint32_t MAX_MSG_QUEUE_PAYLOAD_SIZE  = 1024;

#define PLAYER_LOCK(mutex)                                                                            \
    do {                                                                                              \
        int32_t lockRet = pthread_mutex_lock(&(mutex));                                             \
        if (lockRet != 0) {                                                                         \
            MEDIA_ERR_LOG("lock failed err: %d", lockRet); \
        }                                                                                              \
    } while (0)

#define PLAYER_UNLOCK(mutex)                                                                               \
    do {                                                                                                   \
        int32_t unLockRet = pthread_mutex_unlock(&(mutex));                                              \
        if (unLockRet != 0) {                                                                           \
            MEDIA_ERR_LOG("unlock failed err: %d", unLockRet); \
        }                                                                                                  \
    } while (0)

#define LITERPLAYER_COND_SIGNAL(cond)          \
    do {                                       \
        (void)pthread_cond_signal(&(cond)); \
    } while (0)

#define PLAYER_RETURN_VAL_IF_NULL(condition, ret)                                                  \
    do {                                                                                           \
        if ((condition) == nullptr) {                                                              \
            MEDIA_ERR_LOG("" #condition " is NULL error");                                         \
            return (ret);                                                                          \
        }                                                                                          \
    } while (0)

#define PLAYER_RETURN_IF_NOT_INIT(isInited)    \
    do {                                                                              \
        if (!(isInited)) {                                              \
            MEDIA_ERR_LOG("liteplayer has not been init"); \
            return HI_ERR_LITEPLAYER_NOT_INIT;                                          \
        }                                                                             \
    } while (0)

enum PlayerTplayMode {
    PLAYER_TPLAY_FULL_PLAY,
    PLAYER_TPLAY_ONLY_I_FRAME,
    PLAYER_TPLAY_BUTT
};

enum PlayerTplaySeekOffset {
    TPLAY_SEEK_OFFSET_2X = 250,  // ms
    TPLAY_SEEK_OFFSET_4X = 250,
    TPLAY_SEEK_OFFSET_8X = 400,
    TPLAY_SEEK_OFFSET_16X = 800,
    TPLAY_SEEK_OFFSET_32X = 1600,
    TPLAY_SEEK_OFFSET_64X = 3200,
    TPLAY_SEEK_OFFSET_128X = 6400
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif  // LITEPLAYER_DEFINE_H
