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

#ifndef PLAYER_SINK_TYPE_H
#define PLAYER_SINK_TYPE_H

#include <memory>
#include <vector>
#include "player_define.h"
#include "surface.h"

using namespace std;

namespace OHOS {
namespace Media {
#define AV_INVALID_PTS -1
#define MS_SCALE   1000
#define ENABLE_RENDER "enable-render"
#define MAX_PIPELINE_SINK_NUM  2

typedef enum {
    SINK_STATE_IDLE,
    SINK_STATE_INITED,
    SINK_STATE_PREPARED,
    SINK_STATE_STARTED, /* normal play and tplay */
    SINK_STATE_PAUSE,
    SINK_STATE_STOP,
    SINK_STATE_COMPLETE,  /* recieve eos */ 
    SINK_STATE_ERROR
} SinkState;

typedef enum  {
    SINK_TYPE_AUDIO,
    SINK_TYPE_VIDEO,
    SINK_TYPE_BUT,
} SinkType;

typedef enum {
    DATA_TYPE_U8,
    DATA_TYPE_S8,
    DATA_TYPE_U16,
    DATA_TYPE_S16,
    DATA_TYPE_U32,
    DATA_TYPE_S32,
    DATA_TYPE_U64,
    DATA_TYPE_S64,
    DATA_TYPE_FLOAT,
    DATA_TYPE_DOUBLE,
    DATA_TYPE_STRING,
} dataType;

typedef struct {
    int32_t format;
    uint32_t sampleFmt;
    uint32_t sampleRate;
    uint32_t channel;
    float volume;
} AudioSinkAttr;

typedef struct {
    int32_t width;
    int32_t height;
    float frameRate;
    int32_t format;
    Surface *surface;
} VideoSinkAttr;

typedef struct {
    SinkType sinkType;
    int32_t trackId;
    union {
        VideoSinkAttr vidAttr;
        AudioSinkAttr audAttr;
    };
} SinkAttr;

typedef struct {
    uint64_t audFrameCount;
} AudioSinkStatus;

typedef struct {
    uint64_t vidFrameCount;
    uint32_t decWidth;
    uint32_t decHeight;
    uint32_t fpsInteger;
    uint32_t fpsDecimal;
} VideoSinkStatus;

typedef enum {
    SINK_SUCCESS = 0,
    SINK_GET_DEVICE_FAILED,
    SINK_LAOD_DEVICE_FAILED,
    SINK_OPEN_STREAM_FAILED,
    SINK_INIT_FAILED,
    SINK_RENDER_FULL,
    SINK_RENDER_DELAY,
    SINK_RENDER_ERROR,
    SINK_QUE_EMPTY,
    SINK_RENDER_EOS,
} SinkRetCode;
}  // namespace Media
}  // namespace OHOS

#endif  // PLAYER_SINK_H
