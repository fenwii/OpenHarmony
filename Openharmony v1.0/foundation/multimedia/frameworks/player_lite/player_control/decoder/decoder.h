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

#ifndef DECODER_H
#define DECODER_H
#include <string>
#include "codec_type.h"

namespace OHOS {
namespace Media {
const int CODEC_SUCCESS = 0;
const int CODEC_FAILURE = -1;

typedef struct {
    AvCodecMime mime;
    uint32_t maxWidth;
    uint32_t maxHeight;
    uint32_t bufSize;
    uint32_t frameBufCnt; // todo buffer 个数应当不是由上面来定的
    void *priv;
} VdecAttr;

typedef struct {
    AvCodecMime mime;
    int32_t bufSize;
    void *priv;
} AdecAttr;

typedef struct {
    union {
        AdecAttr adecAttr;
        VdecAttr vdecAttr;
    };
    CodecType type;
} AvAttribute;

class Decoder {
public:
    Decoder();

    virtual ~Decoder();

    static int32_t GetCapbilityByMime(AvCodecMime mime, CodecType type, uint32_t flags, Capbility &cap);

    int32_t CreateHandle(const std::string &name, AvAttribute &attr);

    int32_t DestroyHandle();

    int32_t SetPortBufferMode(DirectionType type, BufferMode mode);

    int32_t SetMetadata(const Param *params, int paramCnt);

    int32_t GetMetadata(Param *param, int paramCnt);

    int32_t StartDec();

    int32_t StopDec();

    int32_t FlushDec();

    int32_t QueueInputBuffer(InputInfo &inputData, uint32_t timeoutMs);

    int32_t DequeInputBuffer(InputInfo &inputData, uint32_t timeoutMs);

    int32_t QueueOutputBuffer(OutputInfo &outInfo, uint32_t timeoutMs);

    int32_t DequeueOutputBuffer(OutputInfo &outInfo, uint32_t timeoutMs);

    int32_t SetCallback(CodecCallback &cb, UINTPTR instance);

private:
    CODEC_HANDLETYPE codecHandle_;
};
}
}
#endif
