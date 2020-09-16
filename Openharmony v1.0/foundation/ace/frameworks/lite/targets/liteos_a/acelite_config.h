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
 *                 liteos_a config for hmf
 * ================================================================================================
 */
#define OHOS_ACELITE_LITEOS_A // NOTE: DO NOT use this macro directly

/**
 * Compile all test entry for hmf
 */
#ifdef FEATURE_TEST_IMPLEMENTATION
#error "must keep the global configuration unique"
#else
#define FEATURE_TEST_IMPLEMENTATION
#endif

/**
 * use hi log interface to trace out
 */
#ifdef FEATURE_ACELITE_HI_LOG_PRINTF
#error "must keep the global configuration unique"
#else
#define FEATURE_ACELITE_HI_LOG_PRINTF
#endif

/**
 * append no blank color to rootview for easy using, delete this after the mouse showing is optimized
 */
#ifdef FEATURE_ROOTVIEW_CUSTOM_BACKGROUND_COLOR
#error "must keep the global configuration unique"
#else
#define FEATURE_ROOTVIEW_CUSTOM_BACKGROUND_COLOR
#endif

/**
 * js profiler switch
 */
#ifdef FEATURE_ACELITE_JS_PROFILER
#error "must keep the global configuration unique"
#else
#define FEATURE_ACELITE_JS_PROFILER
#endif

/**
 * support audio API for JS
 */
#define FEATURE_MODULE_AUDIO

/**
 * switch for cipher module
 */
#define ENABLE_MODULE_CIPHER

/**
 * support storage and file API for JS
 */
#define FEATURE_MODULE_STORAGE

/**
 * support device API for JS
 */
#define FEATURE_MODULE_DEVICE

/**
 * timer module
 */
#define FEATURE_TIMER_MODULE

/**
 * support lite ace dfx module
 */
#define FEATURE_ACELITE_DFX_MODULE

#define FEATURE_ACELITE_LITE_DFX_MODULE

/**
 * enable Canvas component Feature API on ipcamera real devices
 */
#define FEATURE_COMPONENT_CANVAS

#ifdef FEATURE_COMPONENT_CAMERA
#error "must keep the global configuration unique"
#else
#define FEATURE_COMPONENT_CAMERA
#endif

#ifdef FEATURE_COMPONENT_VIDEO
#error "must keep the global configuration unique"
#else
#define FEATURE_COMPONENT_VIDEO
#endif

#define FEATURE_UPDATE_VIDEO_PROGRESS_ASYNC

#define DEFAULT_PROFILER_MSG_PATH "/storage/user/data/"

#define PROFILER_ENABLE_FLAG_FILE "/storage/user/data/profiler_enable"

#define RUNTIME_MODE_FILE_PATH "/storage/user/data/jsparser_enable"

#endif // OHOS_ACELITE_CONFIG_H
