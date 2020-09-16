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

#include "camera_device.h"

#include <string>
#include <thread>

#include "codec_interface.h"
#include "hal_display.h"
#include "media_log.h"
#include "meta_data.h"
#include "securec.h"

using namespace OHOS;
using namespace OHOS::Media;
using namespace std;

const int32_t KEY_IS_SYNC_FRAME = 1; // "is-sync-frame"
const int32_t KEY_TIME_US = 2;       // "timeUs"

namespace OHOS {
namespace Media {
inline PicSize Convert2CodecSize(CameraPicSize size)
{
    return (PicSize)size;
}
static int32_t SetVencSource(CODEC_HANDLETYPE codecHdl, uint32_t deviceId)
{
    Param param = {.key = KEY_DEVICE_ID, .val = (void *)&deviceId, .size = sizeof(uint32_t)};
    int32_t ret = CodecSetParameter(codecHdl, &param, 1);
    if (ret != 0) {
        MEDIA_ERR_LOG("Set enc source failed.(ret=%d)", ret);
        return ret;
    }
    return MEDIA_OK;
}

static int32_t
    CameraCreateVideoEnc(FrameConfig &fc, HalVideoProcessorAttr *attr, uint32_t srcDev, CODEC_HANDLETYPE *codecHdl)
{
    const char *name = "codec.video.hardware.encoder";
    const uint32_t maxParamNum = 10;
    uint32_t paramIndex = 0;
    Param param[maxParamNum];

    CodecType domainKind = VIDEO_ENCODER;
    param[paramIndex].key = KEY_CODEC_TYPE;
    param[paramIndex].val = &domainKind;
    param[paramIndex].size = sizeof(CodecType);
    paramIndex++;

    AvCodecMime codecMime = MEDIA_MIMETYPE_VIDEO_HEVC;
    param[paramIndex].key = KEY_MIMETYPE;
    param[paramIndex].val = &codecMime;
    param[paramIndex].size = sizeof(AvCodecMime);
    paramIndex++;

    VenCodeRcMode rcMode = VENCOD_RC_CBR;
    param[paramIndex].key = KEY_VIDEO_RC_MODE;
    param[paramIndex].val = &rcMode;
    param[paramIndex].size = sizeof(VenCodeRcMode);
    paramIndex++;

    VenCodeGopMode gopMode = VENCOD_GOPMODE_NORMALP;
    param[paramIndex].key = KEY_VIDEO_GOP_MODE;
    param[paramIndex].val = &gopMode;
    param[paramIndex].size = sizeof(VenCodeGopMode);
    paramIndex++;

    Profile profile = HEVC_MAIN_PROFILE;
    param[paramIndex].key = KEY_VIDEO_PROFILE;
    param[paramIndex].val = &profile;
    param[paramIndex].size = sizeof(Profile);
    paramIndex++;

    PicSize picSize = Convert2CodecSize(attr->size);
    MEDIA_DEBUG_LOG("picSize=%d", picSize);
    param[paramIndex].key = KEY_VIDEO_PIC_SIZE;
    param[paramIndex].val = &picSize;
    param[paramIndex].size = sizeof(PicSize);
    paramIndex++;

    uint32_t frameRate = attr->fps;
    MEDIA_DEBUG_LOG("frameRate=%d", frameRate);
    param[paramIndex].key = KEY_VIDEO_FRAME_RATE;
    param[paramIndex].val = &frameRate;
    param[paramIndex].size = sizeof(uint32_t);
    paramIndex++;

    int32_t ret = CodecCreate(name, param, paramIndex, codecHdl);
    if (ret != 0) {
        MEDIA_ERR_LOG("Create video encoder failed.");
        return HAL_MEDIA_ERR;
    }

    ret = SetVencSource(*codecHdl, srcDev);
    if (ret != 0) {
        CodecDestroy(codecHdl);
        return HAL_MEDIA_ERR;
    }

    return HAL_MEDIA_OK;
}

static int32_t CameraCreateJpegEnc(uint32_t srcDev, HalVideoProcessorAttr *attr, CODEC_HANDLETYPE *codecHdl)
{
    const char *videoEncName = "codec.jpeg.hardware.encoder";
    const uint32_t maxParamNum = 5;
    Param param[maxParamNum];
    uint32_t paramIndex = 0;

    CodecType domainKind = VIDEO_ENCODER;
    param[paramIndex].key = KEY_CODEC_TYPE;
    param[paramIndex].val = &domainKind;
    param[paramIndex].size = sizeof(CodecType);
    paramIndex++;

    AvCodecMime codecMime = MEDIA_MIMETYPE_IMAGE_JPEG;
    param[paramIndex].key = KEY_MIMETYPE;
    param[paramIndex].val = &codecMime;
    param[paramIndex].size = sizeof(AvCodecMime);
    paramIndex++;

    PicSize picSize = Convert2CodecSize(attr->size);
    param[paramIndex].key = KEY_VIDEO_PIC_SIZE;
    param[paramIndex].val = &picSize;
    param[paramIndex].size = sizeof(PicSize);
    paramIndex++;

    int32_t ret = CodecCreate(videoEncName, param, paramIndex, codecHdl);
    if (ret != 0) {
        return HAL_MEDIA_ERR;
    }

    ret = SetVencSource(*codecHdl, srcDev);
    if (ret != 0) {
        MEDIA_ERR_LOG("Set video encoder source failed.");
        CodecDestroy(*codecHdl);
        return HAL_MEDIA_ERR;
    }

    return HAL_MEDIA_OK;
}

static int32_t CopyCodecOutput(void *dst, uint32_t *size, OutputInfo *buffer)
{
    char *dstBuf = reinterpret_cast<char *>(dst);
    for (uint32_t i = 0; i < buffer->bufferCnt; i++) {
        uint32_t packSize = buffer->buffers[i].length - buffer->buffers[i].offset;
        errno_t ret = memcpy_s(dstBuf, *size, buffer->buffers[i].addr + buffer->buffers[i].offset, packSize);
        if (ret != EOK) {
            return HAL_MEDIA_ERR;
        }
        *size -= packSize;
        dstBuf += packSize;
    }
    return MEDIA_OK;
}

static int32_t FindAvailProcessorIdx(Surface &surface, vector<HalVideoProcessorAttr> &attrs)
{
    CameraPicSize picSize = HalConvert2StandardSize(surface.GetWidth(), surface.GetHeight());
    for (uint32_t i = 0; i < attrs.size(); i++) {
        if (attrs[i].size == picSize) {
            return i;
        }
    }
    return -1;
}

int RecordAssistant::OnVencBufferAvailble(UINTPTR hComponent, UINTPTR dataIn, OutputInfo *buffer)
{
    CODEC_HANDLETYPE hdl = reinterpret_cast<CODEC_HANDLETYPE>(hComponent);
    RecordAssistant *assistant = reinterpret_cast<RecordAssistant *>(dataIn);
    list<Surface *> *surfaceList = nullptr;
    for (uint32_t idx = 0; idx < assistant->vencHdls_.size(); idx++) {
        if (assistant->vencHdls_[idx] == hdl) {
            surfaceList = &(assistant->vencSurfaces_[idx]);
            break;
        }
    }
    if (surfaceList == nullptr || surfaceList->empty()) {
        MEDIA_ERR_LOG("Encoder handle is illegal.");
        return -1;
    }
    int32_t ret = -1;
    for (auto &surface : *surfaceList) {
        SurfaceBuffer *surfaceBuf = surface->RequestBuffer();
        if (surfaceBuf == nullptr) {
            MEDIA_ERR_LOG("No available buffer in surface.");
            break;
        }

        uint32_t size = surface->GetSize();
        void *buf = surfaceBuf->GetVirAddr();
        if (buf == nullptr) {
            MEDIA_ERR_LOG("Invalid buffer address.");
            break;
        }
        ret = CopyCodecOutput(buf, &size, buffer);
        if (ret != HAL_MEDIA_OK) {
            MEDIA_ERR_LOG("No available buffer in surface.");
            surface->CancelBuffer(surfaceBuf);
            break;
        }
        surfaceBuf->SetInt32(KEY_IS_SYNC_FRAME, (((buffer->flag & STREAM_FLAG_KEYFRAME) == 0) ? 0 : 1));
        surfaceBuf->SetInt64(KEY_TIME_US, buffer->timeStamp);
        surfaceBuf->SetSize(surface->GetSize() - size);

        if (surface->FlushBuffer(surfaceBuf) != 0) {
            MEDIA_ERR_LOG("Flush surface failed.");
            surface->CancelBuffer(surfaceBuf);
            ret = -1;
            break;
        }
    }
    if (CodecQueueOutput(hdl, buffer, 0, -1) != 0) {
        MEDIA_ERR_LOG("Codec queue output failed.");
    }

    return ret;
}

CodecCallback RecordAssistant::recordCodecCb_ = {nullptr, nullptr, RecordAssistant::OnVencBufferAvailble};

int32_t RecordAssistant::SetFrameConfig(FrameConfig &fc,
                                        vector<HalProcessorHdl> &hdls,
                                        vector<HalVideoProcessorAttr> &attrs)
{
    fc_ = &fc;

    auto surfaceList = fc.GetSurfaces();
    if (surfaceList.size() != 1) {
        MEDIA_ERR_LOG("Only support one surface in frame config now.");
        return MEDIA_ERR;
    }
    for (auto &surface : surfaceList) {
        CODEC_HANDLETYPE codecHdl = nullptr;
        int32_t ProcessorIdx = FindAvailProcessorIdx(*surface, attrs);
        if (ProcessorIdx < 0) {
            MEDIA_ERR_LOG("No suitble procesor for recording.");
            return MEDIA_ERR;
        }
        uint32_t deviceId = HalGetProcessorDeviceId(hdls[ProcessorIdx]);
        int32_t encIdx = VideoEncIsExist(&attrs[deviceId]);
        if (encIdx >= 0) {
            vencSurfaces_[encIdx].emplace_back(surface);
            continue;
        }

        int32_t ret = CameraCreateVideoEnc(fc, &attrs[ProcessorIdx], deviceId, &codecHdl);
        if (ret != MEDIA_OK) {
            MEDIA_ERR_LOG("Cannot create suitble video encoder.");
            return MEDIA_ERR;
        }

        ret = CodecSetCallback(codecHdl, &recordCodecCb_, reinterpret_cast<UINTPTR>(this));
        if (ret != 0) {
            MEDIA_ERR_LOG("Set codec callback failed.(ret=%d)", ret);
            CodecDestroy(codecHdl);
            return MEDIA_ERR;
        }
        vencHdls_.emplace_back(codecHdl);
        list<Surface *> conList({surface});
        vencSurfaces_.emplace_back(conList);
        vencAttr_.emplace_back(&attrs[deviceId]);
    }
    state_ = LOOP_READY;
    return MEDIA_OK;
}

int32_t RecordAssistant::Start()
{
    if (state_ != LOOP_READY) {
        return MEDIA_ERR;
    }

    int32_t ret = HAL_MEDIA_OK;
    int32_t i;
    for (i = 0; static_cast<uint32_t>(i) < vencHdls_.size(); i++) {
        ret = CodecStart(vencHdls_[i]);
        if (ret != HAL_MEDIA_OK) {
            MEDIA_ERR_LOG("Video encoder start failed.");
            ret = MEDIA_ERR;
            break;
        }
    }
    if (ret == MEDIA_ERR) {
        /* rollback */
        for (; i >= 0; i--) {
            CodecStop(vencHdls_[i]);
        }
        return MEDIA_ERR;
    }
    state_ = LOOP_LOOPING;

    MEDIA_DEBUG_LOG("Start camera recording succeed.");
    return MEDIA_OK;
}

int32_t RecordAssistant::Stop()
{
    if (state_ != LOOP_LOOPING) {
        return MEDIA_ERR;
    }

    for (uint32_t i = 0; i < vencHdls_.size(); i++) {
        CodecStop(vencHdls_[i]);
        CodecDestroy(vencHdls_[i]);
    }
    vencHdls_.clear();
    vencAttr_.clear();
    vencSurfaces_.clear();

    state_ = LOOP_STOP;
    return MEDIA_OK;
}

int32_t RecordAssistant::VideoEncIsExist(HalVideoProcessorAttr *attr)
{
    for (uint32_t i = 0; i < vencAttr_.size(); i++) {
        if (vencAttr_[i] == attr) {
            return i;
        }
    }
    return -1;
}

static void GetSurfaceRect(Surface *surface, HalVideoOutputAttr *attr)
{
    attr->regionPositionX = std::stoi(surface->GetUserData("region_position_x"));
    attr->regionPositionY = std::stoi(surface->GetUserData("region_position_y"));
    attr->regionWidth = std::stoi(surface->GetUserData("region_width"));
    attr->regionHeight = std::stoi(surface->GetUserData("region_height"));
}

int32_t PreviewAssistant::SetFrameConfig(FrameConfig &fc,
                                         vector<HalProcessorHdl> &hdls,
                                         vector<HalVideoProcessorAttr> &attrs)
{
    fc_ = &fc;

    auto surfaceList = fc.GetSurfaces();
    if (surfaceList.size() != 1) {
        MEDIA_ERR_LOG("Only support one surface in frame config now.");
        return MEDIA_ERR;
    }
    auto surface = surfaceList.front();
    int32_t ProcessorIdx = FindAvailProcessorIdx(*surface, attrs);
    if (ProcessorIdx < 0) {
        MEDIA_ERR_LOG("No suitble procesor for preview.");
        return MEDIA_ERR;
    }
    uint32_t deviceId = HalGetProcessorDeviceId(hdls[ProcessorIdx]);

    HalVideoOutputAttr attr;
    GetSurfaceRect(surface, &attr);
    int32_t ret = HalCreateCameraVideoOutput(deviceId, &attr);
    if (ret != 0) {
        MEDIA_ERR_LOG("Create preview video output failed.");
        return MEDIA_ERR;
    }

    return MEDIA_OK;
}

int32_t PreviewAssistant::Start()
{
    // enable vo
    return MEDIA_OK;
}

int32_t PreviewAssistant::Stop()
{
    HalDestroyCameraVideoOutput();
    return MEDIA_OK;
}

int32_t CaptureAssistant::SetFrameConfig(FrameConfig &fc,
                                         vector<HalProcessorHdl> &hdls,
                                         vector<HalVideoProcessorAttr> &attrs)
{
    auto surfaceList = fc.GetSurfaces();
    if (surfaceList.size() != 1) {
        MEDIA_ERR_LOG("Only support one surface in frame config now.");
        return MEDIA_ERR;
    }
    if (surfaceList.empty()) {
        MEDIA_ERR_LOG("Frame config with empty surface list.");
        return MEDIA_ERR;
    }
    if (surfaceList.size() > 1) {
        MEDIA_WARNING_LOG("Capture only fullfill the first surface in frame config.");
    }
    Surface *surface = surfaceList.front();
    int32_t idx = FindAvailProcessorIdx(*surface, attrs);
    if (idx < 0) {
        MEDIA_ERR_LOG("No suitble procesor for venc.");
        return MEDIA_ERR;
    }
    uint32_t deviceId = HalGetProcessorDeviceId(hdls[idx]);
    int32_t ret = CameraCreateJpegEnc(deviceId, &attrs[idx], &vencHdl_);
    if (ret != HAL_MEDIA_OK) {
        MEDIA_ERR_LOG("Create capture venc failed.");
        return MEDIA_ERR;
    }

    capSurface_ = surface;

    state_ = LOOP_READY;
    return MEDIA_OK;
}

/* Block method, waiting for capture completed */
int32_t CaptureAssistant::Start()
{
    state_ = LOOP_LOOPING;
    int32_t ret = CodecStart(vencHdl_);
    if (ret != 0) {
        MEDIA_ERR_LOG("Start capture encoder failed.(ret=%d)", ret);
        return MEDIA_ERR;
    }
    MEDIA_DEBUG_LOG("surface = %p", capSurface_);

    SurfaceBuffer *surfaceBuf = capSurface_->RequestBuffer();
    if (surfaceBuf == nullptr) {
        MEDIA_ERR_LOG("No available buffer in surface.");
        return -1;
    }

    OutputInfo outInfo;
    ret = CodecDequeueOutput(vencHdl_, 0, nullptr, &outInfo);
    if (ret != 0) {
        capSurface_->CancelBuffer(surfaceBuf);
        MEDIA_ERR_LOG("Dequeue capture frame failed.(ret=%d)", ret);
        return MEDIA_ERR;
    }

    uint32_t size = capSurface_->GetSize();
    void *buf = surfaceBuf->GetVirAddr();
    if (buf == nullptr) {
        MEDIA_ERR_LOG("Invalid buffer address.");
        return -1;
    }
    ret = CopyCodecOutput(buf, &size, &outInfo);
    if (ret != HAL_MEDIA_OK) {
        MEDIA_ERR_LOG("No available buffer in capSurface_.");
        capSurface_->CancelBuffer(surfaceBuf);
        return -1;
    }
    surfaceBuf->SetSize(capSurface_->GetSize() - size);

    if (capSurface_->FlushBuffer(surfaceBuf) != 0) {
        MEDIA_ERR_LOG("Flush surface buffer failed.");
        capSurface_->CancelBuffer(surfaceBuf);
        return -1;
    }

    CodecQueueOutput(vencHdl_, &outInfo, 0, -1); // 0:no timeout -1:no fd
    CodecStop(vencHdl_);
    CodecDestroy(vencHdl_);

    state_ = LOOP_STOP;

    return MEDIA_OK;
}

int32_t CaptureAssistant::Stop()
{
    MEDIA_DEBUG_LOG("No support method.");
    return MEDIA_OK;
}

CameraDevice::CameraDevice() {}

CameraDevice::~CameraDevice() {}

int32_t CameraDevice::Initialize(CameraAbility &ability)
{
    /* Need to be Refactored when delete config file */
    int32_t ret = HalCreateVideoProcessor(nullptr);
    if (ret != HAL_MEDIA_OK) {
        MEDIA_ERR_LOG("Init camera device failed.(ret=%d)", ret);
        return MEDIA_ERR;
    }
    HalVideoProcessorAttr attrs[HAL_MAX_VPSS_NUM];
    HalProcessorHdl hdls[HAL_MAX_VPSS_NUM];
    int32_t size;
    list<CameraPicSize> range;
    HalCameraGetProcessorAttr(hdls, attrs, &size);
    for (int i = 0; i < size; i++) {
        prcessorAttrs_.emplace_back(attrs[i]);
        prcessorHdls_.emplace_back(hdls[i]);
        range.emplace_back(attrs[i].size);
    }
    ability.SetParameterRange(PARAM_KEY_SIZE, range);

    ret = CodecInit();
    if (ret != 0) {
        MEDIA_ERR_LOG("Codec module init failed.(ret=%d)", ret);
        return MEDIA_ERR;
    }
    MEDIA_DEBUG_LOG("Codec module init succeed.");

    captureAssistant_.state_ = LOOP_READY;
    previewAssistant_.state_ = LOOP_READY;
    recordAssistant_.state_ = LOOP_READY;
    return MEDIA_OK;
}

int32_t CameraDevice::UnInitialize()
{
    HalDestroyVideoProcessor();
    return MEDIA_OK;
}

int32_t CameraDevice::TriggerLoopingCapture(FrameConfig &fc)
{
    MEDIA_DEBUG_LOG("Camera device start looping capture.");

    DeviceAssistant *assistant = nullptr;
    int fcType = fc.GetFrameConfigType();
    switch (fcType) {
        case FRAME_CONFIG_RECORD:
            assistant = &recordAssistant_;
            break;
        case FRAME_CONFIG_PREVIEW:
            assistant = &previewAssistant_;
            break;
        case FRAME_CONFIG_CAPTURE:
            assistant = &captureAssistant_;
            break;
        default:
            break;
    }
    if (assistant == nullptr) {
        MEDIA_ERR_LOG("Invalid frame config type.(type=%d)", fcType);
        return MEDIA_ERR;
    }
    if (assistant->state_ == LOOP_IDLE || assistant->state_ == LOOP_LOOPING || assistant->state_ == LOOP_ERROR) {
        MEDIA_ERR_LOG("Device state is %d, cannot start looping capture.", assistant->state_);
        return MEDIA_ERR;
    }

    int ret = assistant->SetFrameConfig(fc, prcessorHdls_, prcessorAttrs_);
    if (ret != MEDIA_OK) {
        MEDIA_ERR_LOG("Check and set frame config failed.(ret=%d)", ret);
        return MEDIA_ERR;
    }

    ret = assistant->Start();
    if (ret != MEDIA_OK) {
        MEDIA_ERR_LOG("Start looping capture failed.(ret=%d)", ret);
        return MEDIA_ERR;
    }

    return MEDIA_OK;
}

void CameraDevice::StopLoopingCapture()
{
    previewAssistant_.Stop();
    recordAssistant_.Stop();
}

int32_t CameraDevice::TriggerSingleCapture(FrameConfig &fc)
{
    return TriggerLoopingCapture(fc);
}

int32_t CameraDevice::SetCameraConfig(CameraConfig &config)
{
    cc_ = &config;
    return MEDIA_OK;
}
} // namespace Media
} // namespace OHOS
