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

/**
 * @addtogroup hilog
 * @{
 *
 * @brief Provides logging functions.
 *
 * You can use this module to log code execution and locate code exceptions if any.
 * This module collects, filters out, buffers, forwards, formats, and performs flow control on logs.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file hiview_log.h
 *
 * @brief Defines functions of the logging module.
 *
 * You can use these functions to output logs to locate code exceptions if any.
 * Ensure that only valid logs are selected for output. If excessive logs are to be output or log levels specified
 * for output are improper, flow control will be performed on logs and key logs may be filtered out.
 * To reduce the OHOS resource usage, you need to register the information about modules requiring log output
 * with the logging system before outputting logs. Logging functions for different levels (for example,
 * {@link HILOG_LV_DEBUG}) are provided for ease in selecting logs at your desired level.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HOS_LITE_HIVIEW_LOG_H
#define HOS_LITE_HIVIEW_LOG_H

#include "hos_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

extern const char * const FUN_ARG_S;
#define FUN_ARG_0 (&FUN_ARG_S[0])
#define FUN_ARG_1 (&FUN_ARG_S[1])
#define FUN_ARG_2 (&FUN_ARG_S[2])
#define FUN_ARG_3 (&FUN_ARG_S[3])
#define FUN_ARG_4 (&FUN_ARG_S[4])
#define FUN_ARG_5 (&FUN_ARG_S[5])
#define FUN_ARG_6 (&FUN_ARG_S[6])
#define FUN_ARG_I (&FUN_ARG_S[7])
#define FUN_ARG_NUM(...) ARGS_CHECK(FUN_ARG_NUM_(FUN_ARG_I, ##__VA_ARGS__, FUN_ARG_EX_()))
#define FUN_ARG_NUM_(...) FUN_ARG_EX(__VA_ARGS__)
#define FUN_ARG_EX(_0, _1, _2, _3, _4, _5, _6, N, ...) N
#define FUN_ARG_EX_() FUN_ARG_6, FUN_ARG_5, FUN_ARG_4, FUN_ARG_3, FUN_ARG_2, FUN_ARG_1, FUN_ARG_0
#define ARGS_CHECK(N) (TRUE ? N : FUN_ARG_I)

#define HILOG_LV_INVALID 0
#define HILOG_LV_DEBUG   1
#define HILOG_LV_INFO    2
#define HILOG_LV_WARN    3
#define HILOG_LV_ERROR   4
#define HILOG_LV_FATAL   5
#define HILOG_LV_MAX     6

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
    /** Atomic Ability Framework */
    HILOG_MODULE_AAFWK,
    /** Graphic */
    HILOG_MODULE_GRAPHIC,
    /** Multimedia */
    HILOG_MODULE_MEDIA,
    /** Distributed Schedule Service */
    HILOG_MODULE_DMS,
    /** Sensors */
    HILOG_MODULE_SEN,
    /** Security */
    HILOG_MODULE_SCY,
    /** XTS */
    HILOG_MODULE_XTS,
    /** Maximum number of modules */
    HILOG_MODULE_MAX
} HiLogModuleType;

/**
 * @brief Registers module information with the logging system.
 *
 * When a new module is defined, you need to use this function to register the module information with the logging
 * system. If not registered, the logs of this module will not be output. \n
 *
 * @param id Identifies the module to be registered. The module ID, which must be globally unique, is defined in
 * {@link HiLogModuleType}.
 * @param name Indicates the module name. The value must be a static string of up to 15 uppercase and lowercase letters.
 * Variables cannot be passed as module names.
 * @return Returns <b>TRUE</b> if the registration is successful; returns <b>FALSE</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
boolean HiLogRegisterModule(uint16 id, const char *name);

/**
 * @brief Obtains the name of a registered module by module ID.
 *
 * @param id Identifies the module. The module ID, which must be globally unique, is defined in {@link HiLogModuleType}.
 * @return Returns the string pointer to the module name if obtained; returns an empty string if the module ID is
 * invalid or does not exist.
 * @since 1.0
 * @version 1.0
 */
const char *HiLogGetModuleName(uint8 id);

/*
 * Interface for printing basic logs. Use the macro definition interface instead of directly using this interface.
 * @param module Module ID.
 * @param level Log Level.
 * @param nums Parameters automatically generated by macro.
 * @param fmt Format string.
 * @attention Do not use this interface directly, you should use the HILOG_XXX interface.
 */
void HiLogPrintf(uint8 module, uint8 level, const char *nums,
    const char *fmt, ...) __attribute__((format(printf, 4, 5)));

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
#ifndef HILOG_COMPILE_LEVEL
#define HILOG_COMPILE_LEVEL HILOG_LV_DEBUG
#endif

/**
 * @brief Outputs debug logs.
 *
 * @param mod Identifies the module. The module ID, which must be globally unique, is defined in
 * {@link HiLogModuleType}.
 * @param fmt Indicates the formatted string of log content.
 *        <ul>
 *          <li>A maximum of six variable parameters are supported. </li>
 *          <li>The format specifier \%s is not supported. If it is used, this function will return unpredictable
 *          results. </li>
 *          <li>Each formatted log record allows for a maximum of 128 characters. If the length of a log record exceeds
 *          128 characters, the log record cannot be output. </li>
 *        </ul>
 * @since 1.0
 * @version 1.0
 */
#if HILOG_COMPILE_LEVEL <= HILOG_LV_DEBUG
#define HILOG_DEBUG(mod, fmt, ...) HiLogPrintf(mod, HILOG_LV_DEBUG, FUN_ARG_NUM(__VA_ARGS__), fmt, ##__VA_ARGS__)
#else
#define HILOG_DEBUG(mod, fmt, ...)
#endif

/**
 * @brief Outputs informational logs.
 *
 * @param mod Identifies the module. The module ID, which must be globally unique, is defined in
 * {@link HiLogModuleType}.
 * @param fmt Indicates the formatted string of log content.
 *        <ul>
 *          <li>A maximum of six variable parameters are supported. </li>
 *          <li>The format specifier \%s is not supported. If it is used, this function will return unpredictable
 *          results. </li>
 *          <li>Each formatted log record allows for a maximum of 128 characters. If the length of a log record exceeds
 *          128 characters, the log record cannot be output. </li>
 *        </ul>
 * @since 1.0
 * @version 1.0
 */
#if HILOG_COMPILE_LEVEL <= HILOG_LV_INFO
#define HILOG_INFO(mod, fmt, ...) HiLogPrintf(mod, HILOG_LV_INFO, FUN_ARG_NUM(__VA_ARGS__), fmt, ##__VA_ARGS__)
#else
#define HILOG_INFO(mod, fmt, ...)
#endif

/**
 * @brief Outputs warning logs.
 *
 * @param mod Identifies the module. The module ID, which must be globally unique, is defined in
 * {@link HiLogModuleType}.
 * @param fmt Indicates the formatted string of log content.
 *        <ul>
 *          <li>A maximum of six variable parameters are supported. </li>
 *          <li>The format specifier \%s is not supported. If it is used, this function will return unpredictable
 *          results. </li>
 *          <li>Each formatted log record allows for a maximum of 128 characters. If the length of a log record exceeds
 *          128 characters, the log record cannot be output. </li>
 *        </ul>
 * @since 1.0
 * @version 1.0
 */
#if HILOG_COMPILE_LEVEL <= HILOG_LV_WARN
#define HILOG_WARN(mod, fmt, ...) HiLogPrintf(mod, HILOG_LV_WARN, FUN_ARG_NUM(__VA_ARGS__), fmt, ##__VA_ARGS__)
#else
#define HILOG_WARN(mod, fmt, ...)
#endif

/**
 * @brief Outputs error logs.
 *
 * @param mod Identifies the module. The module ID, which must be globally unique, is defined in
 * {@link HiLogModuleType}.
 * @param fmt Indicates the formatted string of log content.
 *        <ul>
 *          <li>A maximum of six variable parameters are supported. </li>
 *          <li>The format specifier \%s is not supported. If it is used, this function will return unpredictable
 *          results. </li>
 *          <li>Each formatted log record allows for a maximum of 128 characters. If the length of a log record exceeds
 *          128 characters, the log record cannot be output. </li>
 *        </ul>
 * @since 1.0
 * @version 1.0
 */
#if HILOG_COMPILE_LEVEL <= HILOG_LV_ERROR
#define HILOG_ERROR(mod, fmt, ...) HiLogPrintf(mod, HILOG_LV_ERROR, FUN_ARG_NUM(__VA_ARGS__), fmt, ##__VA_ARGS__)
#else
#define HILOG_ERROR(mod, fmt, ...)
#endif

/**
 * @brief Outputs fatal logs.
 *
 * @param mod Identifies the module. The module ID, which must be globally unique, is defined in
 * {@link HiLogModuleType}.
 * @param fmt Indicates the formatted string of log content.
 *        <ul>
 *          <li>A maximum of six variable parameters are supported. </li>
 *          <li>The format specifier \%s is not supported. If it is used, this function will return unpredictable
 *          results. </li>
 *          <li>Each formatted log record allows for a maximum of 128 characters. If the length of a log record exceeds
 *          128 characters, the log record cannot be output. </li>
 *        </ul>
 * @since 1.0
 * @version 1.0
 */
#if HILOG_COMPILE_LEVEL <= HILOG_LV_FATAL
#define HILOG_FATAL(mod, fmt, ...) HiLogPrintf(mod, HILOG_LV_FATAL, FUN_ARG_NUM(__VA_ARGS__), fmt, ##__VA_ARGS__)
#else
#define HILOG_FATAL(mod, fmt, ...)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef HOS_LITE_HIVIEW_LOG_H */
/** @} */
