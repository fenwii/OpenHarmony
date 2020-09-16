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

#include "decoder.h"
#include <stdio.h>
#include "securec.h"
extern "C"
{
#include "codec_interface.h"
}

namespace OHOS {
namespace Media {
const int PARAM_MAX_NUM = 30;
Decoder::Decoder()
    : codecHandle_(nullptr)
{
}

Decoder::~Decoder()
{
}

int32_t Decoder::GetCapbilityByMime(AvCodecMime mime, CodecType type, uint32_t flags, Capbility &cap)
{
    int32_t ret = CodecGetCapbility(mime, type, flags, &cap);
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS;
}

static bool ConvertAdecAttributToParams(AvAttribute &attr, Param *param,
                                        int maxLen, int &actualLen)
{
    int32_t index = 0;
    param[index].key = KEY_MIMETYPE;
    param[index].val = (void*)&(attr.adecAttr.mime);
    param[index].size = sizeof(attr.adecAttr.mime);
    index++;
    param[index].key = KEY_BUFFERSIZE;
    param[index].val = (void*)&(attr.adecAttr.bufSize);
    param[index].size = sizeof(attr.adecAttr.bufSize);
    index++;
    param[index].key = KEY_CODEC_TYPE;
    param[index].val = (void*)&(attr.type);
    param[index].size = sizeof(attr.type);
    index++;
    if (attr.adecAttr.priv) {
        param[index].key = KEY_CHANNEL_COUNT;
        param[index].val = attr.adecAttr.priv;
        param[index].size = sizeof(uint32_t);
        index++;
    }
    actualLen = index;
    if (actualLen > maxLen) {
        printf("anylsis adec param too much\n");
        return false;
    }
    return true;
}

static bool ConvertVdecAttributToParams(AvAttribute &attr, Param *param,
                                        int maxLen, int &actualLen)
{
    int index = 0;
    param[index].key = KEY_MIMETYPE;
    param[index].val = (void*)&(attr.vdecAttr.mime);
    param[index].size = sizeof(attr.vdecAttr.mime);
    index++;
    param[index].key = KEY_WIDTH;
    param[index].val = (void*)&(attr.vdecAttr.maxWidth);
    param[index].size = sizeof(attr.vdecAttr.maxWidth);
    index++;
    param[index].key = KEY_HEIGHT;
    param[index].val = (void*)&(attr.vdecAttr.maxHeight);
    param[index].size = sizeof(attr.vdecAttr.maxHeight);
    index++;
    param[index].key = KEY_BUFFERSIZE;
    param[index].val = (void*)&(attr.vdecAttr.bufSize);
    param[index].size = sizeof(attr.vdecAttr.bufSize);
    index++;
    param[index].key = KEY_CODEC_TYPE;
    param[index].val = (void*)&(attr.type);
    param[index].size = sizeof(attr.type);
    index++;
    actualLen = index;
    if (actualLen > maxLen) {
        printf("anylsis vdec param too much\n");
        return false;
    }
    return true;
}

static bool ConvertAttributeToParams(AvAttribute &attr, Param *param,
                                           int maxLen, int &actualLen)
{
    if (param == nullptr) {
        printf("[%s] param NULL \n", __FUNCTION__);
        return false;
    }

    bool ret = false;
    switch (attr.type) {
        case AUDIO_DECODER: {
            ret = ConvertAdecAttributToParams(attr, param, maxLen, actualLen);
            break;
        }
        case VIDEO_DECODER: {
            ret = ConvertVdecAttributToParams(attr, param, maxLen, actualLen);
            break;
        }
        default: {
            printf("not support this type:%d\n", attr.type);
            ret = false;
        }
    }
    return ret;
}

int32_t Decoder::CreateHandle(const std::string &name, AvAttribute &attr)
{
    int actualLen = 0;
    Param param[PARAM_MAX_NUM];
    printf("attr,type:%d\n", attr.type);
    memset_s(param, PARAM_MAX_NUM * sizeof(Param), 0x00, PARAM_MAX_NUM * sizeof(Param));
    if (ConvertAttributeToParams(attr, param, PARAM_MAX_NUM, actualLen) == false) {
        printf("convert fail\n");
    }

    int32_t ret = CodecCreate(name.c_str(), param, actualLen, &codecHandle_);
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS;
}

int32_t Decoder::DestroyHandle()
{
    int32_t ret = CodecDestroy(codecHandle_);
    codecHandle_ = nullptr;
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS;
}

int32_t Decoder::SetPortBufferMode(DirectionType type, BufferMode mode)
{
    int32_t ret = CodecSetPortMode(codecHandle_, type, mode);
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS;
}

int32_t Decoder::SetMetadata(const Param *params, int paramCnt)
{
    int32_t ret = CodecSetParameter(codecHandle_, params, paramCnt);
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS;
}

int32_t Decoder::GetMetadata(Param *params, int paramCnt)
{
    int32_t ret = CodecGetParameter(codecHandle_, params, paramCnt);
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS;
}

int32_t Decoder::StartDec()
{
    int32_t ret = CodecStart(codecHandle_);
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS;
}

int32_t Decoder::StopDec()
{
    int32_t ret = CodecStop(codecHandle_);
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS; 
}

int32_t Decoder::FlushDec()
{
    int32_t ret = CodecFlush(codecHandle_, ALL_TYPE);
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS;  
}

int32_t Decoder::QueueInputBuffer(InputInfo &inputData, uint32_t timeoutMs)
{
    int32_t ret = CodecQueueInput(codecHandle_, &inputData, timeoutMs);
    return ret;
}

int32_t Decoder::DequeInputBuffer(InputInfo &inputData, uint32_t timeoutMs)
{
    int32_t ret = CodecDequeInput(codecHandle_, timeoutMs, &inputData);
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS;
}

int32_t Decoder::QueueOutputBuffer(OutputInfo &outInfo, uint32_t timeoutMs)
{
    int32_t ret = CodecQueueOutput(codecHandle_, &outInfo, timeoutMs, -1);
    if (ret != CODEC_SUCCESS) {
        return CODEC_FAILURE;
    }
    return CODEC_SUCCESS;
}

int32_t Decoder::DequeueOutputBuffer(OutputInfo &outInfo, uint32_t timeoutMs)
{
    int32_t ret = CodecDequeueOutput(codecHandle_, timeoutMs, nullptr, &outInfo);
    return ret;
}

int32_t Decoder::SetCallback(CodecCallback &cb, UINTPTR instance)
{
    int32_t ret = CodecSetCallback(codecHandle_, &cb, instance);
    return ret;
}
}
}
