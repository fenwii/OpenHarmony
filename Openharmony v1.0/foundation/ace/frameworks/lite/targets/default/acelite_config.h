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

#ifndef OHOS_ACELITE_CONFIG_H
#define OHOS_ACELITE_CONFIG_H

/**
 * ================================================================================================
 *                 the default config for hmf
 * ================================================================================================
 */
#define OHOS_ACELITE_HMF // NOTE: DO NOT use this macro directly

/**
 * Compile all test entry for hmf
 */
#ifdef FEATURE_TEST_IMPLEMENTATION
#error "must keep the global configuration unique"
#else
#define FEATURE_TEST_IMPLEMENTATION
#endif

/**
 * support hi log module trace
 */
#ifdef FEATURE_ACELITE_HI_LOG_PRINTF
#error "must keep the global configuration unique"
#else
#define FEATURE_ACELITE_HI_LOG_PRINTF
#endif

/**
 * support memory pool module
 */
#ifdef FEATURE_ACELITE_MEMORY_POOL
#error "must keep the global configuration unique"
#else
#define FEATURE_ACELITE_MEMORY_POOL
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                              //
//                            Component support configurations                                  //
//                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * analog clock component
 */
#ifdef FEATURE_COMPONENT_ANALOG_CLOCK
#error "must keep the global configuration unique"
#else
#define FEATURE_COMPONENT_ANALOG_CLOCK
#endif

/**
 * tabs component
 */
#ifdef FEATURE_COMPONENT_TABS
#error "must keep the global configuration unique"
#else
#define FEATURE_COMPONENT_TABS
#endif

/**
 * define the max length of user's console log
 */
#ifndef CONSOLE_LOG_LINE_MAX_LENGTH
#define CONSOLE_LOG_LINE_MAX_LENGTH (256)
#endif

#define DEFAULT_PROFILER_MSG_PATH "user/log/"

#define PROFILER_ENABLE_FLAG_FILE "user/data/profiler_enable"

#define RUNTIME_MODE_FILE_PATH "user/data/jsparser_enable"

#endif // OHOS_ACELITE_CONFIG_H
