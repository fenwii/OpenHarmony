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

#ifndef HOS_LITE_HIVIEW_SERVICE_H
#define HOS_LITE_HIVIEW_SERVICE_H

#include <service.h>
#include <iunknown.h>
#include "hos_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

typedef enum {
    HIVIEW_CMP_TYPE_DUMP = 0,
    HIVIEW_CMP_TYPE_LOG,
    HIVIEW_CMP_TYPE_LOG_LIMIT,
    HIVIEW_CMP_TYPE_EVENT,
    HIVIEW_CMP_TYPE_MAX
} HiviewComponentType;

typedef enum {
    HIVIEW_MSG_OUTPUT_LOG_FLOW = 0,
    HIVIEW_MSG_OUTPUT_LOG_TEXT_FILE,
    HIVIEW_MSG_OUTPUT_LOG_BIN_FILE,
    HIVIEW_MSG_OUTPUT_EVENT_FLOW,
    HIVIEW_MSG_OUTPUT_EVENT_BIN_FILE,
    HIVIEW_MSG_MAX
} HiviewInnerMessage;

typedef struct {
    INHERIT_IUNKNOWN;
    void (*Output)(IUnknown *iUnknown, int16 msgId, uint16 type);
} HiviewInterface;

typedef struct {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(HiviewInterface);
    Identity identity;
} HiviewService;

typedef void (* HiviewInitFunc)(void);
typedef void (* HiviewMsgHandle)(const Request *request);

void HiviewRegisterInitFunc(HiviewComponentType type, HiviewInitFunc func);
void HiviewRegisterMsgHandle(HiviewInnerMessage type, HiviewMsgHandle func);
void HiviewSendMessage(const char *srvName, int16 msgId, uint16 msgValue);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef HOS_LITE_HIVIEW_SERVICE_H */

