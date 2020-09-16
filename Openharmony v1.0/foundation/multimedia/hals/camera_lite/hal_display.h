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

#ifndef COMMON_PLATFORM_VO_H
#define COMMON_PLATFORM_VO_H

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

typedef int32_t HalVideoOutputHdl;

typedef struct {
    int32_t regionPositionX;
    int32_t regionPositionY;
    int32_t regionWidth;
    int32_t regionHeight;
    uint32_t priority;
} HalVideoOutputAttr;

int32_t HalCreateVideoOutput(HalVideoOutputHdl *handle, HalVideoOutputAttr attr);

int32_t HalConfigVideoOutput(HalVideoOutputHdl handle, HalVideoOutputAttr attr);

int32_t HalGetVideoOutputConfig(HalVideoOutputHdl handle, HalVideoOutputAttr *attr);

int32_t HalDestroyVideoOutput(HalVideoOutputHdl handle);

int32_t HalStartVideoOutput(HalVideoOutputHdl handle);

int32_t HalStopVideoOutput(HalVideoOutputHdl handle);

int32_t HalWriteVo(HalVideoOutputHdl handle, const void *buffer);

int32_t HalPlayerVoInit(HalVideoOutputHdl *handle);

int32_t HalPlayerSysInit(void);

void HalPlayerVoDeinit(HalVideoOutputHdl handle);

int32_t HalCreateCameraVideoOutput(uint32_t deviceId, HalVideoOutputAttr *attr);

int32_t HalDestroyCameraVideoOutput();
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif  /* End of #ifndef COMMON_PLATFORM_VO_H */
