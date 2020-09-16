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

#ifndef OHOS_ACELITE_CONSOLE_LOG_IMPL_H
#define OHOS_ACELITE_CONSOLE_LOG_IMPL_H

#include "acelite_config.h"
#include "js_config.h"

#if ENABLED(CONSOLE_LOG_OUTPUT)

#include "jerryscript.h"

namespace OHOS {
namespace ACELite {
/**
 * The log level definations.
 */
enum LogLevel {
    LOG_LEVEL_FATAL,   // fatal, no console.fatal
    LOG_LEVEL_ERR,     // console.error
    LOG_LEVEL_WARN,    // console.warn
    LOG_LEVEL_INFO,    // console.info
    LOG_LEVEL_DEBUG,   // console.debug
    LOG_LEVEL_TRACE,   // console.trace
    LOG_LEVEL_NONE,    // console.log
};

/**
 * @brief: the str to print out.
 *
 * @param logLevel the log level
 * @param str the string to print out
 */
void LogString(const LogLevel logLevel, const char * const str);

/**
 * @brief: Output given string into stdout or the log file.
 *
 * @param logLevel the log level
 * @param str the string to print
 * @param length the string's length
 */
void Output(const LogLevel logLevel, const char * const str, const uint8_t length);

/**
 * @brief: Flush the output.
 */
void FlushOutput();

/**
 * @fn ConsoleModule::LogNative()
 *
 * @brief The real implementation for all console log function, same implementation with the jerry's default IO.
 *
 * @param logLevel the log level, please refer to LogNative definations
 * @param func function object
 * @param context the context of function execution
 * @param args the list of arguments
 * @param length the length of arguments list
 */
jerry_value_t LogNative(const LogLevel logLevel,
                        const jerry_value_t func,
                        const jerry_value_t context,
                        const jerry_value_t* args,
                        const jerry_length_t length);

/**
 * @brief: Print log level if needed.
 *
 * @param logLevel the log level
 */
void LogOutLevel(const LogLevel logLevel);

/**
 * @brief: Log a single character to standard output or the log buffer.
 * If log to buffer, will flush to file or stdout when '\n' or buffer is full.
 *
 * @param c the character to print
 * @param logLevel the loglevel, need to output if c is '\n'
 * @param endFlag the flag presents if this is the end of the console log, default is false
 */
void LogChar(char c, const LogLevel logLevel, bool endFlag = false);
} // namespace ACELite
} // namespace OHOS
#endif // ENABLED(CONSOLE_LOG_OUTPUT)
#endif // OHOS_ACELITE_CONSOLE_LOG_IMPL_H
