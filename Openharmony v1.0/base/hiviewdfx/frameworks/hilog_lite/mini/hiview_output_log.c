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

#include "hiview_output_log.h"
#include "hiview_def.h"
#include "hiview_util.h"
#include "hiview_cache.h"
#include "hiview_config.h"
#include "hiview_file.h"
#include "hiview_log.h"
#include "hiview_service.h"
#include "message.h"
#include "securec.h"
#include "hos_types.h"

#define SINGLE_FMT_MAX_LEN      8
#define FMT_CONVERT_TRMINATOR   2

static char g_logLevelInfo[HILOG_LV_MAX] = {
    'N', // "NONE"
    'D', // "DEBUG"
    'I', // "INFO"
    'W', // "WARN"
    'E', // "ERROR"
    'F'  // "FATAL"
};

static uint8 g_logCacheBuffer[LOG_STATIC_CACHE_SIZE];
static HiviewCache g_logCache = {
    .size = 0,
    .buffer = NULL,
};
static HiviewFile g_logFile = {
    .path = HIVIEW_FILE_PATH_LOG,
    .fhandle = -1,
};

/* Output the log to UART using plaintext. */
static void OutputLogRealtime(const Request *req);
/* Output the log to FLASH using text. */
static void OutputLog2TextFile(const Request *req);
/* Output the log to FLASH using binary. */
static void OutputLog2BinFile(const Request *req);
static int32 LogCommonFmt(char *outStr, int32 outStrlen, const HiLogCommon *commonContentPtr);
static int32 LogValuesFmt(char *desStrPtr, int32 desLen, const HiLogContent *logContentPtr);
static int32 LogDebugValuesFmt(char *desStrPtr, int32 desLen, const HiLogContent *logContentPtr);

void InitCoreLogOutput(void)
{
    InitHiviewStaticCache(&g_logCache, LOG_CACHE, g_logCacheBuffer, sizeof(g_logCacheBuffer));
    HiviewRegisterMsgHandle(HIVIEW_MSG_OUTPUT_LOG_TEXT_FILE, OutputLog2TextFile);
    HiviewRegisterMsgHandle(HIVIEW_MSG_OUTPUT_LOG_BIN_FILE, OutputLog2BinFile);
    HiviewRegisterMsgHandle(HIVIEW_MSG_OUTPUT_LOG_FLOW, OutputLogRealtime);
}

void InitLogOutput(void)
{
    if (g_hiviewConfig.outputOption == OUTPUT_OPTION_DEBUG ||
        g_hiviewConfig.outputOption == OUTPUT_OPTION_FLOW) {
        return;
    }
    HiviewFileType type = HIVIEW_LOG_TEXT_FILE;
    if (g_hiviewConfig.outputOption == OUTPUT_OPTION_BIN_FILE) {
        type = HIVIEW_LOG_BIN_FILE;
    }
    if (InitHiviewFile(&g_logFile, type,
        (HIVIEW_LOG_FILE_SIZE / sizeof(HiLogContent)) * sizeof(HiLogContent)) == FALSE) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "Open file[%d] failed.", HIVIEW_LOG_BIN_FILE);
    }
}

void ClearLogOutput(void)
{
    if (g_logCache.usedSize > 0) {
        if (g_hiviewConfig.outputOption == OUTPUT_OPTION_TEXT_FILE) {
            OutputLog2TextFile(NULL);
        } else if (g_hiviewConfig.outputOption == OUTPUT_OPTION_BIN_FILE) {
            OutputLog2BinFile(NULL);
        }
    }
    CloseHiviewFile(&g_logFile);
}

void OutputLog(const uint8 *content, uint32 len)
{
    if (content == NULL) {
        return;
    }

    /* When the init of kernel is not finished, data is cached in the cache. */
    if (g_hiviewConfig.hiviewInited == FALSE) {
        if (WriteToCache(&g_logCache, content, len) != (int32)len) {
            HILOG_INFO(HILOG_MODULE_HIVIEW, "Write log to cache failed.");
        }
        return;
    }

    char tempOutStr[LOG_FMT_MAX_LEN] = {0};
    if (g_hiviewConfig.outputOption == OUTPUT_OPTION_DEBUG) {
        if (LogContentFmt(tempOutStr, sizeof(tempOutStr), content) > 0) {
            HIVIEW_UartPrint(tempOutStr);
        }
        return;
    }

    if (WriteToCache(&g_logCache, (uint8 *)content, len) == (int32)len) {
        if (g_logCache.usedSize >= HIVIEW_FILE_BUF_SIZE) {
            switch (g_hiviewConfig.outputOption) {
                case OUTPUT_OPTION_TEXT_FILE:
                    HiviewSendMessage(HIVIEW_SERVICE, HIVIEW_MSG_OUTPUT_LOG_TEXT_FILE, 0);
                    break;
                case OUTPUT_OPTION_BIN_FILE:
                    HiviewSendMessage(HIVIEW_SERVICE, HIVIEW_MSG_OUTPUT_LOG_BIN_FILE, 0);
                    break;
                case OUTPUT_OPTION_FLOW:
                    HiviewSendMessage(HIVIEW_SERVICE, HIVIEW_MSG_OUTPUT_LOG_FLOW, 0);
                    break;
                default:
                    break;
            }
        }
    }
}

static void OutputLogRealtime(const Request *req)
{
    HiLogContent logContent;
    char tempOutStr[LOG_FMT_MAX_LEN] = {0};
    int32 len;
    (void)req;

    while (ReadFromCache(&g_logCache, (uint8 *)&(logContent.commonContent),
        sizeof(HiLogCommon)) == sizeof(HiLogCommon)) {
        if (logContent.commonContent.head != LOG_INFO_HEAD) {
            DiscardCacheData(&g_logCache);
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "Discard cache[%d] data.", LOG_CACHE);
            break;
        }
        len = logContent.commonContent.valueNumber * sizeof(uint32);
        if (len > 0 && ReadFromCache(&g_logCache, (uint8 *)&(logContent.values), len) != len) {
            continue;
        }
        len = LogContentFmt(tempOutStr, sizeof(tempOutStr), (uint8 *)&logContent);
        if (len <= 0) {
            continue;
        }
        HIVIEW_UartPrint(tempOutStr);
    }
}

static void OutputLog2TextFile(const Request *req)
{
    HiLogContent logContent;
    char tempOutStr[LOG_FMT_MAX_LEN] = {0};
    (void)req;

    if (g_logCache.usedSize < sizeof(HiLogCommon)) {
        return;
    }

    int32 len;
    while (ReadFromCache(&g_logCache, (uint8 *)&(logContent.commonContent),
        sizeof(HiLogCommon)) == sizeof(HiLogCommon)) {
        if (logContent.commonContent.head != LOG_INFO_HEAD) {
            DiscardCacheData(&g_logCache);
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "Discard cache[%d] data.", LOG_CACHE);
            break;
        }
        len = logContent.commonContent.valueNumber * sizeof(uint32);
        if (len > 0 && ReadFromCache(&g_logCache, (uint8 *)&(logContent.values), len) != len) {
            continue;
        }
        len = LogContentFmt(tempOutStr, sizeof(tempOutStr), (uint8 *)&logContent);
        if (len > 0 && WriteToFile(&g_logFile, (uint8 *)tempOutStr, len) != len) {
            g_hiviewConfig.writeFailureCount++;
        }
    }
}

static void OutputLog2BinFile(const Request *req)
{
    HiLogCommon *pCommonContent = NULL;
    uint16 len = 0;
    uint16 valueLen;
    uint8 *tmpBuffer = NULL;
    uint16 outputSize = g_logCache.usedSize;
    (void)req;

    if (outputSize < sizeof(HiLogCommon)) {
        return;
    }
    tmpBuffer = (uint8 *)HIVIEW_MemAlloc(MEM_POOL_HIVIEW_ID, outputSize);
    if (tmpBuffer == NULL) {
        return;
    }
    while (g_logCache.usedSize >= sizeof(HiLogCommon) && outputSize > (len + sizeof(HiLogCommon))) {
        if (ReadFromCache(&g_logCache, tmpBuffer + len, sizeof(HiLogCommon)) != sizeof(HiLogCommon)) {
            continue;
        }
        pCommonContent = (HiLogCommon *)(tmpBuffer + len);
        len += sizeof(HiLogCommon);
        if (pCommonContent->head != LOG_INFO_HEAD) {
            DiscardCacheData(&g_logCache);
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "Discard cache[%d] data.", LOG_CACHE);
            break;
        }
        valueLen = pCommonContent->valueNumber * sizeof(uint32);
        if (valueLen > 0) {
            if (ReadFromCache(&g_logCache, tmpBuffer + len, valueLen) != valueLen) {
                continue;
            }
            len += valueLen;
        }
    }
    if (len > 0 && WriteToFile(&g_logFile, tmpBuffer, len) != len) {
        g_hiviewConfig.writeFailureCount++;
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "Failed to write log data.");
    }
    HIVIEW_MemFree(MEM_POOL_HIVIEW_ID, tmpBuffer);
}

uint32 GetLogFileSize(void)
{
    return GetFileUsedSize(&g_logFile);
}

uint32 ReadLogFile(uint8 *buf, uint32 len)
{
    if (buf == NULL) {
        return 0;
    }
    uint32 usedSize = GetFileUsedSize(&g_logFile);
    if (usedSize < len) {
        len = usedSize;
    }
    if (ReadFromFile(&g_logFile, buf, len) != (int32)len) {
        return 0;
    }

    return len;
}

int32 LogContentFmt(char *outStr, int32 outStrLen, const uint8 *pLogContent)
{
    int32 len;
    HiLogContent *logContentPtr = (HiLogContent *)pLogContent;

    len = LogCommonFmt(outStr, outStrLen, &(logContentPtr->commonContent));
    if (len >= 0) {
        if (g_hiviewConfig.outputOption == OUTPUT_OPTION_DEBUG) {
            len += LogDebugValuesFmt(outStr + len, outStrLen - len, logContentPtr);
        } else {
            len += LogValuesFmt(outStr + len, outStrLen - len, logContentPtr);
        }
    }

    if (len < 0) {
        return len;
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

static int32 LogCommonFmt(char *outStr, int32 outStrLen, const HiLogCommon *commonContentPtr)
{
    int32 ret;
    uint32 time, day, hour, mte, sec;

    time = commonContentPtr->time;
    day = time / SECONDS_PER_DAY;
    hour = time % SECONDS_PER_DAY / SECONDS_PER_HOUR;
    mte = time % SECONDS_PER_HOUR / SECONDS_PER_MINUTE;
    sec = time % SECONDS_PER_MINUTE;
    ret = snprintf_s(outStr, outStrLen, outStrLen - 1, "%02d %02d:%02d:%02d 0 %d %c %d/%s: ",
        day, hour, mte, sec, commonContentPtr->task, g_logLevelInfo[commonContentPtr->level],
        commonContentPtr->module, HiLogGetModuleName(commonContentPtr->module));

    return ret;
}

static int32 LogValuesFmt(char *desStrPtr, int32 desLen, const HiLogContent *logContentPtr)
{
    int32 i;
    int32 outLen = 0;
    int32 len;
    char fmtStr[SINGLE_FMT_MAX_LEN];
    uint32 valNum = logContentPtr->commonContent.valueNumber;
    const char *fmt = logContentPtr->commonContent.fmt;
    uint32 valueIndex = 0;
    for (i = 0; fmt[i] != 0 && outLen < desLen;) {
        if (fmt[i] != '%') {
            desStrPtr[outLen++] = fmt[i++];
            continue;
        }
        if (fmt[i + 1] == '%') {
            desStrPtr[outLen++] = fmt[i++];
            desStrPtr[outLen++] = fmt[i++];
            continue;
        }
        fmtStr[0] = fmt[i++];
        uint32 t = 1;
        while (fmt[i] != 0 && t < sizeof(fmtStr) - 1) {
            /* %s %ms %-ms %m.ns %-m.ns convert to %p */
            if ((fmt[i] == 's' || fmt[i] == 'S') &&
                (fmt[i - 1] == '%' || (fmt[i - 1] >= '0' && fmt[i - 1] <= '9'))) {
                fmtStr[1] = 'p';
                fmtStr[FMT_CONVERT_TRMINATOR] = 0;
                i++;
                break;
            }
            if ((fmt[i] >= 'a' && fmt[i] <= 'z') || (fmt[i] >= 'A' && fmt[i] <= 'Z')) {
                fmtStr[t++] = fmt[i++];
                fmtStr[t] = 0;
                break;
            }
            fmtStr[t++] = fmt[i++];
        }
        if (valueIndex < valNum) {
            len = snprintf_s(&desStrPtr[outLen], desLen - outLen, desLen - outLen - 1,
                fmtStr, logContentPtr->values[valueIndex]);
            if (len < 0) {
                break;
            }
            outLen += len;
            valueIndex++;
        }
    }

    return outLen;
}

static int32 LogDebugValuesFmt(char *desStrPtr, int32 desLen, const HiLogContent *logContentPtr)
{
    int32 ret = 0;
    switch (logContentPtr->commonContent.valueNumber) {
        case LOG_MULTI_PARA_0:
            ret = strncpy_s(desStrPtr, desLen, logContentPtr->commonContent.fmt, desLen - 1);
            break;
        case LOG_MULTI_PARA_1:
            ret = snprintf_s(desStrPtr, desLen, desLen - 1, logContentPtr->commonContent.fmt,
                logContentPtr->values[0]);
            break;
        case LOG_MULTI_PARA_2:
            ret = snprintf_s(desStrPtr, desLen, desLen - 1, logContentPtr->commonContent.fmt,
                logContentPtr->values[0], logContentPtr->values[1]);
            break;
        case LOG_MULTI_PARA_3:
            ret = snprintf_s(desStrPtr, desLen, desLen - 1, logContentPtr->commonContent.fmt,
                logContentPtr->values[0], logContentPtr->values[1], logContentPtr->values[LOG_MULTI_PARA_2]);
            break;
        case LOG_MULTI_PARA_4:
            ret = snprintf_s(desStrPtr, desLen, desLen - 1, logContentPtr->commonContent.fmt,
                logContentPtr->values[0], logContentPtr->values[1], logContentPtr->values[LOG_MULTI_PARA_2],
                logContentPtr->values[LOG_MULTI_PARA_3]);
            break;
        case LOG_MULTI_PARA_5:
            ret = snprintf_s(desStrPtr, desLen, desLen - 1, logContentPtr->commonContent.fmt,
                logContentPtr->values[0], logContentPtr->values[1], logContentPtr->values[LOG_MULTI_PARA_2],
                logContentPtr->values[LOG_MULTI_PARA_3], logContentPtr->values[LOG_MULTI_PARA_4]);
            break;
        case LOG_MULTI_PARA_MAX:
            ret = snprintf_s(desStrPtr, desLen, desLen - 1, logContentPtr->commonContent.fmt,
                logContentPtr->values[0], logContentPtr->values[1], logContentPtr->values[LOG_MULTI_PARA_2],
                logContentPtr->values[LOG_MULTI_PARA_3], logContentPtr->values[LOG_MULTI_PARA_4],
                logContentPtr->values[LOG_MULTI_PARA_5]);
            break;
        default:
            break;
    }

    if (ret < 0) {
        ret = 0;
    }
    return ret;
}