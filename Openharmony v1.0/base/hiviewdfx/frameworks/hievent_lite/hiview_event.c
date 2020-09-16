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

#include "securec.h"
#include "string.h"
#include "hos_types.h"
#include "hos_init.h"
#include "hiview_def.h"
#include "hiview_util.h"
#include "hiview_log.h"
#include "hiview_service.h"
#include "hiview_output_event.h"
#include "hiview_config.h"
#include "hiview_event.h"

#define SINGLE_VALUE_MAX_LEN   5
#define EVENT_VALUE_MAX_NUM    16
#define ENCODE_VALUE_LEN1      1
#define ENCODE_VALUE_LEN2      2
#define ENCODE_VALUE_LEN3      3
#define ENCODE_VALUE_LEN4      4
#define GET_UINT32_BYTE1(v)    (uint8)((v) & 0x000000FF)
#define GET_UINT32_BYTE2(v)    (uint8)(((v) & 0x0000FF00) >> 8)
#define GET_UINT32_BYTE3(v)    (uint8)(((v) & 0x00FF0000) >> 16)
#define GET_UINT32_BYTE4(v)    (uint8)(((v) & 0xFF000000) >> 24)

static uint8 HiEventEncode(uint8 k, uint32 v, uint8 last, uint8 *encodeOut);

static void HiEventInit(void)
{
    if (g_hiviewConfig.eventSwitch == HIVIEW_FEATURE_ON && HIEVENT_COMPILE_TYPE > HIEVENT_NONE) {
        InitCoreEventOutput();
        HiviewRegisterInitFunc(HIVIEW_CMP_TYPE_EVENT, InitEventOutput);
        HILOG_DEBUG(HILOG_MODULE_HIVIEW, "hievent init success.");
    }
}
CORE_INIT_PRI(HiEventInit, 1);

void HiEventPrintf(uint8 type, uint16 eventId, int8 key, uint32 value)
{
    if (g_hiviewConfig.eventSwitch == HIVIEW_FEATURE_OFF) {
        return;
    }
    HiEvent e = { 0 };
    uint8 encodeBuffer[SINGLE_VALUE_MAX_LEN] = {0};
    e.common.mark = EVENT_INFO_HEAD;
    e.common.eventId = eventId;
    e.common.time = (uint32)(HIVIEW_GetCurrentTime() / MS_PER_SECOND);
    e.type = type;
    if (key < 0) {
        e.common.len = 0;
        e.payload = NULL;
    } else {
        e.common.len = HiEventEncode((uint8)key, value, 1, encodeBuffer);
        e.payload = encodeBuffer;
    }

    OutputEvent((uint8 *)&e);
}

HiEvent *HiEventCreate(uint8 type, uint16 eventId, uint8 num)
{
    if (g_hiviewConfig.eventSwitch == HIVIEW_FEATURE_OFF || num <= 1 || num > EVENT_VALUE_MAX_NUM) {
        return NULL;
    }
    HiEvent *event = NULL;
    event = (HiEvent *)HIVIEW_MemAlloc(MEM_POOL_HIVIEW_ID, sizeof(HiEvent));
    if (event == NULL) {
        return NULL;
    }
    event->payload = (uint8 *)HIVIEW_MemAlloc(MEM_POOL_HIVIEW_ID, SINGLE_VALUE_MAX_LEN * num);
    if (event->payload == NULL) {
        HIVIEW_MemFree(MEM_POOL_HIVIEW_ID, (void *)event);
        return NULL;
    }
    // Number of values temporarily stored in mark.
    event->common.mark = num;
    event->common.eventId = eventId;
    event->common.time = (uint32)(HIVIEW_GetCurrentTime() / MS_PER_SECOND);
    event->common.len = 0;
    event->type = type;

    return event;
}

void HiEventPutInteger(HiEvent *event, int8 key, uint32 value)
{
    if (g_hiviewConfig.eventSwitch == HIVIEW_FEATURE_OFF || event == NULL || event->payload == NULL ||
        key < 0 || event->common.mark == 0) {
        return;
    }

    uint8 encodeLen;
    if (event->common.mark <= 1) {
        encodeLen = HiEventEncode((uint8)key, value, 1, event->payload + event->common.len);
    } else {
        encodeLen = HiEventEncode((uint8)key, value, 0, event->payload + event->common.len);
    }
    event->common.len += encodeLen;
    event->common.mark -= 1;
}

void HiEventReport(HiEvent *event)
{
    if (g_hiviewConfig.eventSwitch == HIVIEW_FEATURE_OFF || event == NULL || event->payload == NULL) {
        return;
    }

    // All data has been added.
    if (event->common.mark == 0) {
        event->common.mark = EVENT_INFO_HEAD;
        OutputEvent((uint8 *)event);
        HIVIEW_MemFree(MEM_POOL_HIVIEW_ID, event->payload);
        HIVIEW_MemFree(MEM_POOL_HIVIEW_ID, (void *)event);
    } else {
        HIVIEW_MemFree(MEM_POOL_HIVIEW_ID, event->payload);
        HIVIEW_MemFree(MEM_POOL_HIVIEW_ID, (void *)event);
    }
}

static uint8 HiEventEncode(uint8 k, uint32 v, uint8 last, uint8 *encodeOut)
{
    HiEventTag tag;

    if (encodeOut == NULL) {
        return 0;
    }
    tag.last = last;
    tag.id = k;
    if (v <= 0xFF) {
        tag.len = ENCODE_VALUE_LEN1;
    } else if (v <= 0xFFFF) {
        tag.len = ENCODE_VALUE_LEN2;
    } else if (v <= 0x00FFFFFF) {
        tag.len = ENCODE_VALUE_LEN3;
    } else {
        tag.len = ENCODE_VALUE_LEN4;
    }
    memcpy_s(encodeOut, sizeof(HiEventTag), (void *)&tag, sizeof(HiEventTag));

    switch (tag.len) {
        case ENCODE_VALUE_LEN1:
            *(encodeOut + ENCODE_VALUE_LEN1) = GET_UINT32_BYTE1(v);
            break;
        case ENCODE_VALUE_LEN2:
            *(encodeOut + ENCODE_VALUE_LEN1) = GET_UINT32_BYTE1(v);
            *(encodeOut + ENCODE_VALUE_LEN2) = GET_UINT32_BYTE2(v);
            break;
        case ENCODE_VALUE_LEN3:
            *(encodeOut + ENCODE_VALUE_LEN1) = GET_UINT32_BYTE1(v);
            *(encodeOut + ENCODE_VALUE_LEN2) = GET_UINT32_BYTE2(v);
            *(encodeOut + ENCODE_VALUE_LEN3) = GET_UINT32_BYTE3(v);
            break;
        default:
            *(encodeOut + ENCODE_VALUE_LEN1) = GET_UINT32_BYTE1(v);
            *(encodeOut + ENCODE_VALUE_LEN2) = GET_UINT32_BYTE2(v);
            *(encodeOut + ENCODE_VALUE_LEN3) = GET_UINT32_BYTE3(v);
            *(encodeOut + ENCODE_VALUE_LEN4) = GET_UINT32_BYTE4(v);
            break;
    }

    return tag.len + 1;
}
