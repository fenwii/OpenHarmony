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
#ifndef LITE_TIME_ADAPTER_H
#define LITE_TIME_ADAPTER_H

#include <ohos_types.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

int32 WDT_Start(uint32 ms);

int32 WDT_Reset(uint32 ms);

int32 WDT_Stop(void);

uint64 SAMGR_GetProcessTime(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_TIME_ADAPTER_H
