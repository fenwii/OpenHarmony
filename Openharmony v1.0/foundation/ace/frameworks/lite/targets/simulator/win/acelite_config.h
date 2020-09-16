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
 *                 config for win simulator
 * ================================================================================================
 */
#define OHOS_ACELITE_SIMULATOR_WIN // NOTE: DO NOT use this macro directly

#define JSFWK_TEST

/**
 * The macro is used to distingush the real device and simulator.
 */
#define TARGET_SIMULATOR

/**
 * Compile all test entry for hmf
 */
#ifdef FEATURE_TEST_IMPLEMENTATION
#error "must keep the global configuration unique"
#else
#define FEATURE_TEST_IMPLEMENTATION
#endif

/**
 * enable FeatureAbility API
 */
#define FEATURE_FEATURE_ABILITY_MODULE

/**
 * support device API for JS
 */
#define FEATURE_MODULE_DEVICE

/**
 * support geo location API for JS
 */
#define FEATURE_MODULE_GEO

/**
 * support sensor API for JS
 */
#define FEATURE_MODULE_SENSOR
/**
 * timer module
 */
#define FEATURE_TIMER_MODULE

/**
 * support storage API for JS
 */
#define FEATURE_MODULE_STORAGE

/**
 * localization module
 */
#define FEATURE_LOCALIZATION_MODULE

/**
 * support config for product JS modules
 */
#define FEATURE_PRODUCT_MODULE

/**
 * module require test
 */
#ifdef ENABLE_MODULE_REQUIRE_TEST
#error "must keep the global configuration unique"
#else
#define ENABLE_MODULE_REQUIRE_TEST
#endif

/**
 * define the max length of user's console log
 */
#ifndef CONSOLE_LOG_LINE_MAX_LENGTH
#define CONSOLE_LOG_LINE_MAX_LENGTH (96)
#endif

/**
 * enable Canvas component Feature API on simulator
 */
#define FEATURE_COMPONENT_CANVAS

#define PROFILER_ENABLE_FLAG_FILE "..\\profiler_enable"

#endif // OHOS_ACELITE_CONFIG_H
