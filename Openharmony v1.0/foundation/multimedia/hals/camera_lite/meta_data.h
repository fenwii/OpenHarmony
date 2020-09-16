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
#ifndef OHOS_META_DATA_H
#define OHOS_META_DATA_H

#include "stdint.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

typedef struct {
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
} CameraRect;

typedef enum {
    CAM_PIC_CIF,     /* 320 * 288 */
    CAM_PIC_360P,    /* 640 * 360 */
    CAM_PIC_D1_PAL,  /* 720 * 576 */
    CAM_PIC_D1_NTSC, /* 720 * 480 */
    CAM_PIC_720P,    /* 1280 * 720 */
    CAM_PIC_1080P,   /* 1920 * 1080 */
    CAM_PIC_2560X1440,
    CAM_PIC_2592X1520,
    CAM_PIC_2592X1536,
    CAM_PIC_2592X1944,
    CAM_PIC_2688X1536,
    CAM_PIC_2716X1524,
    CAM_PIC_3840X2160,
    CAM_PIC_4096X2160,
    CAM_PIC_3000X3000,
    CAM_PIC_4000X3000,
    CAM_PIC_7680X4320,
    CAM_PIC_3840X8640,
    CAM_PIC_BUTT
} CameraPicSize;

typedef enum {
    /* Frame rate */
    CAM_FRAME_FPS,
    /* Auto exposure mode */
    CAM_AE_MODE,
    /* Auto exposure time */
    CAM_AE_EXPO_TIME,
    /* Auto exposure compensation value */
    CAM_AE_COMPENSATION,
    /* Auto exposure lock */
    CAM_AE_LOCK,
    /* Auto exposure region */
    CAM_AE_REGIONS,
    /* White balance mode */
    CAM_AWB_MODE,
    /* White balance lock */
    CAM_AWB_LOCK,
    /* White balance region */
    CAM_AWB_REGION,
    /* Video stabilization feature */
    CAM_VIDEO_STABILIZATION_NABLE,
    /* Image luminance */
    CAM_IMAGE_LUMA,
    /* Image contrast */
    CAM_IMAGE_CONTRAST,
    /* Image hue */
    CAM_IMAGE_HUE,
    /* Image saturation */
    CAM_IMAGE_SATURATION,
    /* Hot pixel correction */
    CAM_HOT_PIXEL_ENABLE,
    /* Level of hot pixel correction */
    CAM_HOT_PIXEL_LEVEL,
    /* Image denoising mode */
    CAM_IMAGE_DENOISE_MODE,
    /* Image denoising level */
    CAM_IMAGE_DENOISE_LEVEL,
} CameraFuncKey;

/**
 @brief Enumerates parameters for image rotation and mirroring.
 */
typedef enum {
    CAM_CENTER_MIRROR = 0,     /**< Central mirroring */
    CAM_HORIZONTAL_MIRROR = 1, /**< Horizontal mirroring */
    CAM_VETICALLY_MIRROR = 2,  /**< Vertical mirroring */
    CAM_ROTATION_90 = 3,       /**< 90-degree rotation */
    CAM_ROTATION_180 = 4,      /**< 180-degree rotation  */
} CameraInvertMode;

#define PARAM_KEY_SIZE 0

#define ENCODER_TYPE 0
typedef enum { CAM_ENCODE_JPEG, CAM_ENCODE_H264, CAM_ENCODE_H265, CAM_ENCODE_FORMAT_BUTT} CameraEncodeFormat;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
#endif // OHOS_META_DATA_H