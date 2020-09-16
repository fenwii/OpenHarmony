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

#include "console_log_impl.h"
#if ENABLED(CONSOLE_LOG_OUTPUT)
#include "js_app_environment.h"
#ifdef FEATURE_USER_MC_LOG_PRINTF
#include "log_js.h" // mc js console log header
#endif // FEATURE_USER_MC_LOG_PRINTF
#ifdef FEATURE_ACELITE_HI_LOG_PRINTF
#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0xD003B00
#define LOG_TAG "JS-3RD-APP"
#include "hilog/log.h"
#endif // FEATURE_ACELITE_HI_LOG_PRINTF
#include <stdio.h>
#include <string.h>

namespace OHOS {
namespace ACELite {
#ifdef CONSOLE_LOG_LINE_MAX_LENGTH
const int16_t LOG_BUFFER_SIZE = CONSOLE_LOG_LINE_MAX_LENGTH;
#else
const int16_t LOG_BUFFER_SIZE = 256; // use 256 as default if it's not config
#endif // CONSOLE_LOG_LINE_MAX_LENGTH
jerry_value_t LogNative(const LogLevel logLevel,
                        const jerry_value_t func,
                        const jerry_value_t context,
                        const jerry_value_t *args,
                        const jerry_length_t argc)
{
    (void)func;    /* unused */
    (void)context; /* unused */

    // print out log level if needed
    LogOutLevel(logLevel);

    const char * const nullStr = "\\u0000";
    jerry_value_t retVal = jerry_create_undefined();

    for (jerry_length_t argIndex = 0; argIndex < argc; argIndex++) {
        jerry_value_t strVal;

        if (jerry_value_is_symbol(args[argIndex])) {
            strVal = jerry_get_symbol_descriptive_string(args[argIndex]);
        } else {
            strVal = jerry_value_to_string(args[argIndex]);
        }

        if (jerry_value_is_error(strVal)) {
            /* There is no need to free the undefined value. */
            retVal = strVal;
            break;
        }

        jerry_length_t length = jerry_get_utf8_string_length(strVal);
        jerry_length_t substrPos = 0;
        const uint16_t bufLength = LOG_BUFFER_SIZE;
        jerry_char_t substrBuf[bufLength] = {0};

        do {
            jerry_size_t substrSize =
                jerry_substring_to_utf8_char_buffer(strVal, substrPos, length, substrBuf, bufLength - 1);

            jerry_char_t *bufEndPos = substrBuf + substrSize;

            /* Update start position by the number of utf-8 characters. */
            for (jerry_char_t *bufPos = substrBuf; bufPos < bufEndPos; bufPos++) {
                /* Skip intermediate utf-8 octets. */
                if ((*bufPos & 0xc0) != 0x80) {
                    substrPos++;
                }
            }

            for (jerry_char_t *bufPos = substrBuf; bufPos < bufEndPos; bufPos++) {
                char chr = static_cast<char>(*bufPos);

                if (chr != '\0') {
                    LogChar(chr, logLevel);
                    continue;
                }

                for (jerry_size_t null_index = 0; nullStr[null_index] != '\0'; null_index++) {
                    LogChar(nullStr[null_index], logLevel);
                }
            }
        } while (substrPos < length);

        jerry_release_value(strVal);
    }
    // output end
    LogChar('\n', logLevel, true);
    FlushOutput();
    return retVal;
}

void LogOutLevel(const LogLevel logLevel)
{
    switch (logLevel) {
        case LOG_LEVEL_ERR:
            LogString(logLevel, "[Console Error] "); // console error
            break;
        case LOG_LEVEL_WARN:
            LogString(logLevel, "[Console Warn] "); // console warn
            break;
        case LOG_LEVEL_INFO:
            LogString(logLevel, "[Console Info] "); // console info
            break;
        case LOG_LEVEL_DEBUG:
            LogString(logLevel, "[Console Debug] "); // console debug
            break;
        case LOG_LEVEL_TRACE:
            LogString(logLevel, "[Console Trace] "); // console trace, this is not supported yet
            break;
        case LOG_LEVEL_NONE:
            LogString(logLevel, "[Console Debug] "); // console.log(), default apply the DEBUG level
            break;
        default: // just return for not supported log level
            break;
    }
}

/**
 * @brief: the str to print out.
 *
 * @param str the string to print out
 */
void LogString(const LogLevel logLevel, const char * const str)
{
    if (str == nullptr) {
        return;
    }
#if defined(FEATURE_ACELITE_HI_LOG_PRINTF) || defined(FEATURE_USER_MC_LOG_PRINTF)
    size_t strLength = strlen(str);
    for (size_t i = 0; i < strLength; i++) {
        LogChar(str[i], logLevel, false);
    }
#else
    Output(logLevel, str, strlen(str));
#endif
}

static char logBuffer[LOG_BUFFER_SIZE] = {0};
static uint16_t logBufferIndex = 0;

void LogChar(char c, const LogLevel logLevel, bool endFlag)
{
    logBuffer[logBufferIndex++] = c;
    if ((logBufferIndex == (LOG_BUFFER_SIZE - 1)) || (c == '\n')) {
        if ((c == '\n') && (logBufferIndex > 0)) {
            logBufferIndex--; // will trace out line seperator after print the content out
        }
        logBuffer[logBufferIndex] = '\0';
        Output(logLevel, logBuffer, logBufferIndex);
        logBufferIndex = 0;
        if (c == '\n' || !endFlag) {
            // this is the newline during the console log, need to append the loglevel prefix,
            // example: console.log("aa\nbb");
#if !defined(FEATURE_ACELITE_HI_LOG_PRINTF) && !defined(FEATURE_USER_MC_LOG_PRINTF)
            Output(logLevel, "\n", 1); // hilog will trace our the line seperator directly
#endif
            if (!endFlag) {
                LogOutLevel(logLevel);
            }
        }
    }
}

#ifdef FEATURE_ACELITE_HI_LOG_PRINTF
static void OutputToHiLog(const LogLevel logLevel, const char * const str)
{
    switch (logLevel) {
        case LOG_LEVEL_ERR:
            HILOG_ERROR(HILOG_MODULE_APP, "%{public}s", str);
            break;
        case LOG_LEVEL_WARN:
            HILOG_WARN(HILOG_MODULE_APP, "%{public}s", str);
            break;
        case LOG_LEVEL_INFO:
            HILOG_INFO(HILOG_MODULE_APP, "%{public}s", str);
            break;
        case LOG_LEVEL_DEBUG:
            HILOG_DEBUG(HILOG_MODULE_APP, "%{public}s", str);
            break;
        case LOG_LEVEL_TRACE:
            HILOG_INFO(HILOG_MODULE_APP, "%{public}s", str);
            break;
        case LOG_LEVEL_NONE:
            HILOG_DEBUG(HILOG_MODULE_APP, "%{public}s", str);
            break;
        default:
            break;
    }
}
#elif defined(FEATURE_USER_MC_LOG_PRINTF)
static void OutputToHiLog(const LogLevel logLevel, const char * const str)
{
    switch (logLevel) {
        case LOG_LEVEL_ERR:
            HILOG_ERROR_JS(str);
            break;
        case LOG_LEVEL_WARN:
            HILOG_WARN_JS(str);
            break;
        case LOG_LEVEL_INFO:
            HILOG_INFO_JS(str);
            break;
        case LOG_LEVEL_DEBUG:
            HILOG_DEBUG_JS(str);
            break;
        case LOG_LEVEL_TRACE:
            HILOG_INFO_JS(str);
            break;
        case LOG_LEVEL_NONE:
            HILOG_DEBUG_JS(str);
            break;
        default:
            break;
    }
}
#endif

void Output(const LogLevel logLevel, const char * const str, const uint8_t length)
{
    if (str == nullptr) {
        return;
    }
    (void)length;
    Debugger::GetInstance().Output(str);
#if defined(FEATURE_ACELITE_HI_LOG_PRINTF) || defined(FEATURE_USER_MC_LOG_PRINTF)
    OutputToHiLog(logLevel, str);
#endif
}

void FlushOutput()
{
    Debugger::GetInstance().FlushOutput();
}
} // namespace ACELite
} // namespace OHOS

#endif // ENABLED(CONSOLE_LOG_OUTPUT)
