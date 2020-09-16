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
 *                 config for wearable
 * ================================================================================================
 */
/**
 * the flag indicating watch product
 */
#define OHOS_ACELITE_PRODUCT_WATCH

/**
 * support terminate() API from JS
 */
#define FEATURE_TERMINATE_ABILITY

/**
 * support storage and file API for JS
 */
#define FEATURE_MODULE_STORAGE

/**
 * enable FeatureAbility API
 */
#define FEATURE_FEATURE_ABILITY_MODULE

/**
 * enable timer JS API
 */
#define FEATURE_TIMER_MODULE

/**
 * enable localization feature
 */
#define FEATURE_LOCALIZATION_MODULE

/**
 * support sensor API for JS
 */
#define FEATURE_MODULE_SENSOR

/**
 * support device API for JS
 */
#define FEATURE_MODULE_DEVICE

/**
 * support geo location API for JS
 */
#define FEATURE_MODULE_GEO

/**
 * support mc ace log module trace
 */
#define FEATURE_ACELITE_MC_LOG_PRINTF

/**
 * support mc ace event and error code print
 */
#define FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT

/**
 * support mc console log
 */
#define FEATURE_USER_MC_LOG_PRINTF

/**
 * support config for product JS modules
 */
#define FEATURE_PRODUCT_MODULE

/**
 * support config for private JS modules
 */
#define FEATURE_PRIVATE_MODULE

/**
 * support using memory pool from product side
 */
#define FEATURE_ACELITE_PRODUCT_MEMORY_POOL

/**
 * define the max length of user's console log
 */
#ifndef CONSOLE_LOG_LINE_MAX_LENGTH
#define CONSOLE_LOG_LINE_MAX_LENGTH (96)
#endif

/**
 * support mc ace dfx module
 */
#define FEATURE_ACELITE_DFX_MODULE

#define FEATURE_ACELITE_MC_DFX_MODULE

/**
 * support fatal error handling on device which not support process
 */
#ifndef FEATURE_FATAL_ERROR_HANDLING
#define FEATURE_FATAL_ERROR_HANDLING
#endif

/**
 * support js profiler
 */
#define FEATURE_ACELITE_MC_JS_PROFILER

#define DEFAULT_PROFILER_MSG_PATH "user/log/"

#define PROFILER_ENABLE_FLAG_FILE "user/data/profiler_enable"

#define RUNTIME_MODE_FILE_PATH "user/data/jsparser_enable"

#endif // OHOS_ACELITE_CONFIG_H
