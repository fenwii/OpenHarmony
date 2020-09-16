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
#ifndef OHOS_CAMERA_HAL_H
#define OHOS_CAMERA_HAL_H

#include "stdbool.h"
#include "stdint.h"

#include "meta_data.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define HAL_MEDIA_OK 0
#define HAL_MEDIA_ERR 1

CameraPicSize HalConvert2StandardSize(int32_t width, int32_t height);
int32_t HalConvertFromStandardCameraPicSize(CameraPicSize size, int32_t *width, int32_t *height);

typedef int32_t HalProcessorHdl;
#define HAL_INVALID_PROCESSOR (-1)
#define HAL_MAX_VPSS_NUM 10
/* necessary and significant attr */
typedef struct {
    CameraPicSize size;
    uint32_t fps;
} HalVideoProcessorAttr;

HalProcessorHdl HalCreateVideoProcessor(HalVideoProcessorAttr *attr);
void HalCameraGetProcessorAttr(HalProcessorHdl hdls[HAL_MAX_VPSS_NUM], HalVideoProcessorAttr attrs[HAL_MAX_VPSS_NUM],
                               int32_t *size);
uint32_t HalGetProcessorDeviceId(HalProcessorHdl hdl);
void HalDestroyVideoProcessor();

/* camera */
int32_t HalMediaInitialize();
int32_t HalCameraInitialize();
void HalCameraUnInitialize();
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
#endif // OHOS_CAMERA_HAL_H