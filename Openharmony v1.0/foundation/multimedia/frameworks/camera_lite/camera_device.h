/*
 * Copyright(c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http ://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_CAMERA_DEVICE_H
#define OHOS_CAMERA_DEVICE_H

#include <cstdbool>
#include <thread>
#include <vector>

#include "camera_ability.h"
#include "camera_config.h"
#include "codec_type.h"
#include "frame_config.h"
#include "hal_media.h"
#include "surface.h"

using namespace std;
namespace OHOS {
namespace Media {
enum LoopState {
    LOOP_IDLE,
    LOOP_READY,
    LOOP_LOOPING,
    LOOP_STOP,
    LOOP_ERROR,
};

class DeviceAssistant {
public:
    std::thread *thrd_ = nullptr;
    LoopState state_ = LOOP_IDLE;
    FrameConfig *fc_ = nullptr;

    virtual int32_t
        SetFrameConfig(FrameConfig &fc, std::vector<HalProcessorHdl> &hdls, std::vector<HalVideoProcessorAttr> &attrs)
    {
        return -1;
    }
    virtual int32_t Start()
    {
        return -1;
    }
    virtual int32_t Stop()
    {
        return -1;
    }
};

class RecordAssistant : public DeviceAssistant {
public:
    int32_t SetFrameConfig(FrameConfig &fc,
                           std::vector<HalProcessorHdl> &hdls,
                           std::vector<HalVideoProcessorAttr> &attrs) override;
    int32_t Start() override;
    int32_t Stop() override;

    vector<CODEC_HANDLETYPE> vencHdls_;
    vector<list<Surface *>> vencSurfaces_;
    vector<HalVideoProcessorAttr *> vencAttr_;
    int32_t VideoEncIsExist(HalVideoProcessorAttr *attr);
    static int OnVencBufferAvailble(UINTPTR hComponent, UINTPTR dataIn, OutputInfo *buffer);
    static CodecCallback recordCodecCb_;
};

class PreviewAssistant : public DeviceAssistant {
public:
    int32_t SetFrameConfig(FrameConfig &fc,
                           std::vector<HalProcessorHdl> &hdls,
                           std::vector<HalVideoProcessorAttr> &attrs) override;
    int32_t Start() override;
    virtual int32_t Stop() override;
};

class CaptureAssistant : public DeviceAssistant {
    int32_t SetFrameConfig(FrameConfig &fc,
                           std::vector<HalProcessorHdl> &hdls,
                           std::vector<HalVideoProcessorAttr> &attrs) override;
    int32_t Start() override;
    virtual int32_t Stop() override;
    CODEC_HANDLETYPE vencHdl_ = nullptr;
    Surface *capSurface_ = nullptr;
};

class CameraDevice {
public:
    CameraDevice();
    virtual ~CameraDevice();

    int32_t Initialize(CameraAbility &ability);
    int32_t UnInitialize();
    int32_t SetCameraConfig(CameraConfig &cc);

    int32_t TriggerLoopingCapture(FrameConfig &fc);
    void StopLoopingCapture();

    int32_t TriggerSingleCapture(FrameConfig &fc);

private:
    CameraConfig *cc_ = nullptr;
    std::vector<HalProcessorHdl> prcessorHdls_;
    std::vector<HalVideoProcessorAttr> prcessorAttrs_;
    RecordAssistant recordAssistant_;
    PreviewAssistant previewAssistant_;
    CaptureAssistant captureAssistant_;
};
} // namespace Media
} // namespace OHOS
#endif // OHOS_CAMERA_DEVICE_H