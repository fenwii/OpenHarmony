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
#include "hos_types.h"
#include "hiview_def.h"
#include "hiview_util.h"
#include "hiview_log.h"
#include "hiview_event.h"
#include "hiview_cache.h"
#include "hiview_config.h"
#include "hiview_file.h"
#include "hiview_service.h"
#include "hiview_output_event.h"

#define EVENT_PAYLOAD_MAX_SIZE   (5*16)

static HiviewCache g_faultEventCache = {
    .size = 0,
    .buffer = NULL,
};
static HiviewCache g_ueEventCache = {
    .size = 0,
    .buffer = NULL,
};
static HiviewCache g_statEventCache = {
    .size = 0,
    .buffer = NULL,
};
static HiviewFile g_faultEventFile = {
    .path = HIVIEW_FILE_PATH_FAULT_EVENT,
    .fhandle = -1,
};
static HiviewFile g_ueEventFile = {
    .path = HIVIEW_FILE_PATH_UE_EVENT,
    .fhandle = -1,
};
static HiviewFile g_statEventFile = {
    .path = HIVIEW_FILE_PATH_STAT_EVENT,
    .fhandle = -1,
};

/* Output the event to UART using plaintext. */
static void OutputEventRealtime(const Request *req);
/* Output the event to FLASH using binary. */
static void OutputEvent2Flash(const Request *req);
static void InitFaultEventOutput(void);
static void InitUeEventOutput(void);
static void InitStatEventOutput(void);
static void Output2Flash(uint8 eventType);
static void CloseEventOutputFile(uint8 type);
static void GetEventCache(uint8 type, HiviewCache **c, HiviewFile **f);

void InitCoreEventOutput(void)
{
    HiviewRegisterMsgHandle(HIVIEW_MSG_OUTPUT_EVENT_BIN_FILE, OutputEvent2Flash);
    HiviewRegisterMsgHandle(HIVIEW_MSG_OUTPUT_EVENT_FLOW, OutputEventRealtime);
}

void InitEventOutput(void)
{
    InitFaultEventOutput();
    InitUeEventOutput();
    InitStatEventOutput();
}

void ClearEventOutput(void)
{
    if (g_hiviewConfig.outputOption == OUTPUT_OPTION_BIN_FILE ||
        g_hiviewConfig.outputOption == OUTPUT_OPTION_TEXT_FILE) {
        CloseEventOutputFile(FAULT_EVENT_CACHE);
        CloseEventOutputFile(UE_EVENT_CACHE);
        CloseEventOutputFile(STAT_EVENT_CACHE);
    }
}

static void InitFaultEventOutput(void)
{
    if (InitHiviewCache(&g_faultEventCache, FAULT_EVENT_CACHE, EVENT_CACHE_SIZE) == FALSE) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "malloc[%d] fail.", FAULT_EVENT_CACHE);
    }
    if (g_hiviewConfig.outputOption == OUTPUT_OPTION_DEBUG ||
        g_hiviewConfig.outputOption == OUTPUT_OPTION_FLOW) {
        return;
    }
    if (InitHiviewFile(&g_faultEventFile, HIVIEW_FAULT_EVENT_FILE, FAULT_EVENT_FILE_SIZE) == FALSE) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "Open file[%d] failed.", HIVIEW_FAULT_EVENT_FILE);
    }
}

static void InitUeEventOutput(void)
{
    if (InitHiviewCache(&g_ueEventCache, UE_EVENT_CACHE, EVENT_CACHE_SIZE) == FALSE) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "malloc[%d] fail.", UE_EVENT_CACHE);
    }
    if (g_hiviewConfig.outputOption == OUTPUT_OPTION_DEBUG ||
        g_hiviewConfig.outputOption == OUTPUT_OPTION_FLOW) {
        return;
    }
    if (InitHiviewFile(&g_ueEventFile, HIVIEW_UE_EVENT_FILE, UE_EVENT_FILE_SIZE) == FALSE) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "Open file[%d] failed.", HIVIEW_UE_EVENT_FILE);
    }
}

static void InitStatEventOutput(void)
{
    if (InitHiviewCache(&g_statEventCache, STAT_EVENT_CACHE, EVENT_CACHE_SIZE) == FALSE) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "malloc[%d] fail.", STAT_EVENT_CACHE);
    }
    if (g_hiviewConfig.outputOption == OUTPUT_OPTION_DEBUG ||
        g_hiviewConfig.outputOption == OUTPUT_OPTION_FLOW) {
        return;
    }
    if (InitHiviewFile(&g_statEventFile, HIVIEW_STAT_EVENT_FILE, STAT_EVENT_FILE_SIZE) == FALSE) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "Open file[%d] failed.", HIVIEW_STAT_EVENT_FILE);
    }
}

static void CloseEventOutputFile(uint8 type)
{
    HiviewCache *c = NULL;
    HiviewFile *f = NULL;
    GetEventCache(type, &c, &f);
    if (c != NULL && c->usedSize > 0) {
        Output2Flash(type);
    }
    CloseHiviewFile(f);
}

void OutputEvent(const uint8 *data)
{
    if (data == NULL) {
        return;
    }

    HiEvent *event = (HiEvent *)data;
    HiviewCache *c = NULL;
    HiviewFile *f = NULL;
    GetEventCache(event->type, &c, &f);
    if (WriteToCache(c, (uint8 *)&(event->common), sizeof(HiEventCommon)) == sizeof(HiEventCommon)) {
        WriteToCache(c, event->payload, event->common.len);
        if (c != NULL && c->usedSize >= HIVIEW_FILE_BUF_SIZE) {
            switch (g_hiviewConfig.outputOption) {
                /* Event do not support the text format */
                case OUTPUT_OPTION_TEXT_FILE:
                case OUTPUT_OPTION_BIN_FILE:
                    HiviewSendMessage(HIVIEW_SERVICE, HIVIEW_MSG_OUTPUT_EVENT_BIN_FILE, event->type);
                    break;
                case OUTPUT_OPTION_FLOW:
                    HiviewSendMessage(HIVIEW_SERVICE, HIVIEW_MSG_OUTPUT_EVENT_FLOW, event->type);
                    break;
                default:
                    break;
            }
        }
    }
}

static void OutputEventRealtime(const Request *req)
{
    HiviewCache *c = NULL;
    HiviewFile *f = NULL;
    uint16 payloadLen;
    HiEvent event;
    uint8 payload[EVENT_PAYLOAD_MAX_SIZE];
    char tmpBuffer[LOG_FMT_MAX_LEN] = {0};

    event.type = (uint8)req->msgValue;
    GetEventCache(event.type, &c, &f);
    while (ReadFromCache(c, (uint8 *)&(event.common), sizeof(HiEventCommon)) == sizeof(HiEventCommon)) {
        if (event.common.mark != EVENT_INFO_HEAD) {
            DiscardCacheData(c);
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "Discard cache[%d] data.", c->type);
            break;
        }
        payloadLen = event.common.len;
        if (payloadLen > sizeof(payload)) {
            payloadLen = sizeof(payload);
        }
        if (payloadLen > 0 && ReadFromCache(c, payload, payloadLen) != payloadLen) {
            break;
        }
        if (payloadLen > 0) {
            event.payload = payload;
        } else {
            event.payload = NULL;
        }
        EventContentFmt(tmpBuffer, LOG_FMT_MAX_LEN, (uint8 *)&event);
        HIVIEW_UartPrint(tmpBuffer);
    }
}

static void OutputEvent2Flash(const Request *req)
{
    Output2Flash((uint8)req->msgValue);
}

static void Output2Flash(uint8 eventType)
{
    HiviewCache *c = NULL;
    HiviewFile *f = NULL;
    uint8 *tmpBuffer = NULL;
    HiEventCommon *pEventCommon = NULL;
    uint16 len = 0;
    uint16 payloadLen;
    uint16 outputSize;

    GetEventCache((uint8)eventType, &c, &f);
    if (c == NULL) {
        return;
    }
    outputSize = c->usedSize;
    if (outputSize < sizeof(HiEventCommon)) {
        return;
    }
    tmpBuffer = (uint8 *)HIVIEW_MemAlloc(MEM_POOL_HIVIEW_ID, outputSize);
    if (tmpBuffer == NULL) {
        return;
    }
    while (c->usedSize >= sizeof(HiEventCommon) && outputSize > (len + sizeof(HiEventCommon))) {
        if (ReadFromCache(c, tmpBuffer + len, sizeof(HiEventCommon)) != sizeof(HiEventCommon)) {
            continue;
        }
        pEventCommon = (HiEventCommon *)(tmpBuffer + len);
        len += sizeof(HiEventCommon);
        if (pEventCommon->mark != EVENT_INFO_HEAD) {
            DiscardCacheData(c);
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "Discard cache[%d] data.", c->type);
            break;
        }
        payloadLen = pEventCommon->len;
        if (payloadLen > 0) {
            if (ReadFromCache(c, tmpBuffer + len, payloadLen) != payloadLen) {
                continue;
            }
            len += payloadLen;
        }
    }
    if (len > 0 && WriteToFile(f, tmpBuffer, len) != len) {
        g_hiviewConfig.writeFailureCount++;
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "Failed to write event data.");
    }
    HIVIEW_MemFree(MEM_POOL_HIVIEW_ID, tmpBuffer);
}

uint32 GetEventFileSize(uint8 eventType)
{
    HiviewCache *c = NULL;
    HiviewFile *f = NULL;

    GetEventCache(eventType, &c, &f);
    return GetFileUsedSize(f);
}

uint32 ReadEventFile(uint8 eventType, uint8 *buf, uint32 len)
{
    HiviewCache *c = NULL;
    HiviewFile *f = NULL;
    uint32 usedSize;

    if (buf == NULL) {
        return 0;
    }
    GetEventCache(eventType, &c, &f);
    usedSize = GetFileUsedSize(f);
    if (usedSize < len) {
        len = usedSize;
    }
    if (ReadFromFile(f, buf, len) != (int32)len) {
        return 0;
    }

    return len;
}

int32 EventContentFmt(char *outStr, int32 outStrLen, const uint8 *pEvent)
{
    int32 len;
    uint32 time, hour, mte, sec;
    HiEvent *event = (HiEvent *)pEvent;

    time = event->common.time;
    hour = time % SECONDS_PER_DAY / SECONDS_PER_HOUR;
    mte = time % SECONDS_PER_HOUR / SECONDS_PER_MINUTE;
    sec = time % SECONDS_PER_MINUTE;
    if (event->payload == NULL) {
        len = snprintf_s(outStr, outStrLen, outStrLen - 1,
            "EVENT: time=%02d:%02d:%02d id=%d type=%d data=null",
            hour, mte, sec, event->common.eventId, event->type);
    } else {
        len = snprintf_s(outStr, outStrLen, outStrLen - 1,
            "EVENT: time=%02d:%02d:%02d id=%d type=%d data=%p",
            hour, mte, sec, event->common.eventId, event->type, event->payload);
    }

    if (len < 0) {
        return -1;
    }

    if (len >= outStrLen - 1) {
        outStr[outStrLen - TAIL_LINE_BREAK] = '\n';
        outStr[outStrLen - 1] = '\0';
    } else {
        outStr[len++] = '\n';
        outStr[len++] = '\0';
    }

    return len;
}

static void GetEventCache(uint8 type, HiviewCache **c, HiviewFile **f)
{
    switch (type) {
        case HIEVENT_FAULT:
            *c = &g_faultEventCache;
            *f = &g_faultEventFile;
            break;
        case HIEVENT_UE:
            *c = &g_ueEventCache;
            *f = &g_ueEventFile;
            break;
        case HIEVENT_STAT:
            *c = &g_statEventCache;
            *f = &g_statEventFile;
            break;
        default:
            break;
    }
}
