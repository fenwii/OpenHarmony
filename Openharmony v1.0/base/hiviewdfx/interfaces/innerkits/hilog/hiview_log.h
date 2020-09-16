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

#ifndef HOS_LITE_HIVIEW_LOG_H
#define HOS_LITE_HIVIEW_LOG_H
/**
 * @addtogroup HiLog
 * @{
 *
 * @brief Provides logging functions.
 *
 * For example, you can use these functions to output logs of the specified log type, service domain, log tag,
 * and log level.
 *
 * @since 1.1
 * @version 1.0
 */

/**
 * @file hilog/log.h
 *
 * @brief Defines the logging functions of the HiLog module.
 *
 * Before outputting logs, you must define the service domain, and log tag, use the function with
 * the specified log type and level, and specify the privacy identifier.\n
 * <ul><li>Service domain: used to identify the subsystem and module of a service. Its value is a hexadecimal
 * integer ranging from 0x0 to 0xFFFFF. The recommended format is 0xAAABB, where AAA indicates the subsystem
 * and BB indicates the module.</li> \n
 * <li>Log tag: a string used to identify the class, file, or service behavior.</li> \n
 * <li>Log level: <b>DEBUG</b>, <b>INFO</b>, <b>WARN</b>, <b>ERROR</b>, and <b>FATAL</b></li> \n
 * <li>Parameter format: a printf format string that starts with a % character, including format specifiers
 * and variable parameters.</li> \n
 * <li>Privacy identifier: {public} or {private} added between the % character and the format specifier in
 * each parameter. Note that each parameter has a privacy identifier. If no privacy identifier is added,
 * the parameter is considered to be <b>private</b>.</li></ul> \n
 *
 * Sample code:\n
 * Defining the service domain and log tag:\n
 * #define LOG_DOMAIN MY_SUBSYSTEM_MODULE // MY_SUBSYSTEM_MODULE=0x00201, where 002 indicates the subsystem and
 * 01 indicates the module.\n
 *     #define LOG_TAG "MY_TAG"\n
 * Outputting logs:\n
 *     HILOG_WARN({@link LOG_APP}, "Failed to visit %{private}s, reason:%{public}d.", url, errno);\n
 * Output result:\n
 *     05-06 15:01:06.870 1051 1051 W 00201/MY_TAG: Failed to visit <private>, reason:503.\n
 *
 * @since 1.1
 * @version 1.0
 */

#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates logging module types.
 *
 * The module type must be globally unique. A maximum of 64 module types can be defined.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    /** DFX */
    HILOG_MODULE_HIVIEW = 0,
    /** System Ability Manager */
    HILOG_MODULE_SAMGR,
    /** Update */
    HILOG_MODULE_UPDATE,
    /** Ability Cross-platform Environment */
    HILOG_MODULE_ACE,
    /** Third-party applications */
    HILOG_MODULE_APP,
    /** Maximum number of modules */
    HILOG_MODULE_MAX
} HiLogModuleType;

/**
 * @brief Defines the service domain for a log file.
 *
 * The service domain is used to identify the subsystem and module of a service. Its value is a hexadecimal integer
 * ranging from 0x0 to 0xFFFFF. If the value is beyond the range, its significant bits are automatically truncated. \n
 * The recommended format is 0xAAABB, where AAA indicates the subsystem and BB indicates the module. \n
 *
 * @since 1.1
 * @version 1.0
 */
#ifndef LOG_DOMAIN
#define LOG_DOMAIN 0
#endif

/**
 * @brief Defines a string constant used to identify the class, file, or service behavior.
 *
 * @since 1.1
 * @version 1.0
 */
#ifndef LOG_TAG
#define LOG_TAG NULL
#endif

#define DOMAIN_LENGTH 5
#define DOMAIN_FILTER 0x000FFFFF

/**
 * @brief Enumerates log types.
 *
 * Currently, <b>LOG_APP</b> is available. \n
 *
 * @since 1.1
 * @version 1.0
 */
typedef enum {
    LOG_TYPE_MIN = 0,
    // Log to kmsg, only used by init phase.
    LOG_INIT = 1,
    // Used by core service, framework.
    LOG_CORE = 3,
    LOG_TYPE_MAX
} LogType;

/**
 * @brief Enumerates log levels.
 *
 * You are advised to select log levels based on their respective usage scenarios:\n
 * <ul><li><b>DEBUG</b>: used for debugging and disabled from commercial releases</li> \n
 * <li><b>INFO</b>: used for logging important system running status and steps in key processes</li> \n
 * <li><b>WARN</b>: used for logging unexpected exceptions that have little impact on user experience and can
 * automatically recover. Logs at this level are generally output when such exceptions are detected and
 * captured.</li> \n
 * <li><b>ERROR</b>: used for logging malfunction that affects user experience and cannot automatically
 * recover</li>\n
 * <li><b>FATAL</b>: used for logging major exceptions that have severely affected user experience and should
 * not occur.</li></ul> \n
 *
 * @since 1.1
 * @version 1.0
 */
typedef enum {
    /** Debug level to be used by {@link HILOG_DEBUG} */
    LOG_DEBUG = 3,
    /** Informational level to be used by {@link HILOG_INFO} */
    LOG_INFO = 4,
    /** Warning level to be used by {@link HILOG_WARN} */
    LOG_WARN = 5,
    /** Error level to be used by {@link HILOG_ERROR} */
    LOG_ERROR = 6,
    /** Fatal level to be used by {@link HILOG_FATAL} */
    LOG_FATAL = 7,
} LogLevel;

#define HILOG_LEVEL_MAX (LOG_FATAL + 1)
/**
 * @brief Outputs logs.
 *
 * You can use this function to output logs based on the specified log type, log level, service domain, log tag,
 * and variable parameters determined by the format specifier and privacy identifier in the printf format.
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param level Indicates the log level, which can be <b>LOG_DEBUG</b>, <b>LOG_INFO</b>, <b>LOG_WARN</b>,
 * <b>LOG_ERROR</b>, and <b>LOG_FATAL</b>.
 * @param domain Indicates the service domain of logs. Its value is a hexadecimal integer ranging from 0x0 to 0xFFFFF.
 * The recommended format is 0xAAABB, where AAA indicates the subsystem and BB indicates the module.
 * @param tag Indicates the log tag, which is a string used to identify the class, file, or service behavior.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the privacy
 * identifier. Specifically, {public} or {private} is added between the % character and the format specifier
 * in each parameter. \n
 * @param... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @return Returns <b>0</b> or a larger value if the operation is successful; returns a value smaller
 * than <b>0</b> otherwise.
 * @since 1.1
 * @version 1.0
 */
#ifdef LOSCFG_BASE_CORE_HILOG
int HiLogPrint(LogType type, LogLevel level, unsigned int domain, const char* tag, const char* fmt, ...)
    __attribute__((format(printf, 5, 6)));
#else
int HiLogPrint(LogType type, LogLevel level, unsigned int domain, const char* tag, const char* fmt, ...)
    __attribute__((format(os_log, 5, 6)));
#endif
/**
 * @brief Defines the pre-compiled macro for log levels.
 *
 * By default, logs at all levels are output in the compilation phase. You can set this pre-compiled macro to a specific
 * log level so that logs at levels lower than that level wil be shielded.
 * For example, if you want to shield logs lower than the ERROR level, set this macro to <b>HILOG_LV_ERROR</b>.
 * In this way, only functions for outputting ERROR- and FATAL-level logs are retained during compilation.
 * If you set this macro to <b>HILOG_LV_MAX</b>, functions for outputting logs at all levels will be disabled.
 *
 * @since 1.0
 * @version 1.0
 */

int HiLogPrintArgs(LogType bufID, LogLevel prio,
    unsigned int domain, const char* tag, const char* fmt, va_list ap);

/**
 * @brief Outputs debug logs. This is a function-like macro.
 *
 * Before calling this function, define the log service domain and log tag. Generally, you need to define them at
 * the beginning of the source file. \n
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the
 * privacy identifier. Specifically, {public} or {private} is added between the % character and the format specifier
 * in each parameter. \n
 * @param... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @return Returns <b>0</b> or a larger value if the operation is successful; returns a value smaller than <b>0</b>
 * otherwise.
 * @see HiLogPrint
 * @since 1.1
 * @version 1.0
 */
#define HILOG_DEBUG(type, ...) ((void)HiLogPrint(LOG_CORE, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief Outputs informational logs. This is a function-like macro.
 *
 * Before calling this function, define the log service domain and log tag. Generally, you need to define them
 * at the beginning of the source file. \n
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the privacy
 * identifier. Specifically, {public} or {private} is added between the % character and the format specifier in
 * each parameter. \n
 * @param... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @return Returns <b>0</b> or a larger value if the operation is successful; returns a value smaller than
 * <b>0</b> otherwise.
 * @see HiLogPrint
 * @since 1.1
 * @version 1.0
 */
#define HILOG_INFO(type, ...) ((void)HiLogPrint(LOG_CORE, LOG_INFO, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief Outputs warning logs. This is a function-like macro.
 *
 * Before calling this function, define the log service domain and log tag. Generally, you need to define them
 * at the beginning of the source file. \n
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the
 * privacy identifier. Specifically, {public} or {private} is added between the % character and the format specifier
 * in each parameter. \n
 * @param... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @return Returns <b>0</b> or a larger value if the operation is successful; returns a value smaller than
 * <b>0</b> otherwise.
 * @see HiLogPrint
 * @since 1.1
 * @version 1.0
 */
#define HILOG_WARN(type, ...) ((void)HiLogPrint(LOG_CORE, LOG_WARN, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief Outputs error logs. This is a function-like macro.
 *
 * Before calling this function, define the log service domain and log tag. Generally, you need to define
 * them at the beginning of the source file. \n
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the privacy
 * identifier. Specifically, {public} or {private} is added between the % character and the format specifier in each
 * parameter. \n
 * @param... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @return Returns <b>0</b> or a larger value if the operation is successful; returns a value smaller than
 * <b>0</b> otherwise.
 * @see HiLogPrint
 * @since 1.1
 * @version 1.0
 */
#define HILOG_ERROR(type, ...) ((void)HiLogPrint(LOG_CORE, LOG_ERROR, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief Outputs fatal logs. This is a function-like macro.
 *
 * Before calling this function, define the log service domain and log tag. Generally, you need to define them at
 * the beginning of the source file. \n
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the privacy
 * identifier. Specifically, {public} or {private} is added between the % character and the format specifier in
 * each parameter. \n
 * @param... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @return Returns <b>0</b> or a larger value if the operation is successful; returns a value smaller than
 * <b>0</b> otherwise.
 * @see HiLogPrint
 * @since 1.1
 * @version 1.0
 */
#define HILOG_FATAL(type, ...) ((void)HiLogPrint(LOG_CORE, LOG_FATAL, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

#define HILOG_DRIVER "/dev/hilog"
#define NANOSEC_PER_MIRCOSEC 1000000
struct HiLogEntry {
    unsigned int len;
    unsigned int hdrSize;
    unsigned int pid : 16;
    unsigned int taskId : 16;
    unsigned int sec;
    unsigned int nsec;
    unsigned int reserved;
    char msg[0];
};

#ifdef __cplusplus
}
#endif
/** @} */
#endif  // HOS_LITE_HIVIEW_LOG_H
