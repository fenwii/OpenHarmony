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

#ifndef OHOS_ACELITE_JS_CONFIG_H
#define OHOS_ACELITE_JS_CONFIG_H

#include "acelite_config.h"

/*
 * Usage:
 *     #if ENABLED(SECURE_C_FUNCTION)
 *     #if DISABLED(SECURE_C_FUNCTION)
 *     #if ENABLED(SECURE_C_FUNCTION) && DISABLED(LOG_OUTPUT)
 *     #if ENABLED(SECURE_C_FUNCTION) || ENABLED(LOG_OUTPUT)
 */
#define ENABLED(CONFIGURATION) ((CONFIGURATION) == 1)
#define DISABLED(CONFIGURATION) ((CONFIGURATION) != 1)

/**
 * Enable secure C functions on real device, and disable on PC simulator for
 * windows sdk version issue.
 *
 * Allowed values:
 *  0: Disable the secure C functions.
 *  1: Enable the secure C functions.
 *
 * Default: 1 on real device and 0 on PC simulator.
 */
#if (!defined _WIN32) && (!defined _WIN64)
#ifndef SECURE_C_FUNCTION
#define SECURE_C_FUNCTION 1 // modify here for real device case
#endif
#else
#ifndef SECURE_C_FUNCTION
#define SECURE_C_FUNCTION 0 // modify here for PC simulator case
#endif
#endif

/**
 * Enable/Disable JS framework runtime performance measurement.
 *
 * Allowed values:
 *  0: Disable the JS framework performance measurement.
 *  1: Enable the JS framework performance measurement.
 *
 * Default: 1
 */
#ifndef JS_PROFILER
#define JS_PROFILER 1
#endif

/**
 * Enable/Disable log function, uncomment to disable.
 *
 * Allowed values:
 *  0: Disable all log output.
 *  1: Enable all log output.
 *
 * Default: 0 on real device and 1 on PC simulator.
 */
#if (defined(_WIN32) || defined(_WIN64))
#define LOG_OUTPUT 1 // this controls JS FWK log out
#endif

/**
 * Enable/Disable log function, uncomment to disable.
 *
 * Allowed values:
 *  0: Disable all JS console log output.
 *  1: Enable all JS console log output.
 *
 * Default: 1
 */
#define CONSOLE_LOG_OUTPUT 1 // this controls console log out

/**
 * Enable/Disable engine debugger initialization
 *
 * Allowed values:
 *  0: Disable engine debugger initialization.
 *  1: Enable engine debugger initialization.
 *
 * Default: 0 on real device and 1 on PC simulator
 */
#if defined(_WIN32) || defined(_WIN64)
#define ENGINE_DEBUGGER 1
#else
#define ENGINE_DEBUGGER 0
#endif

/**
 * Enable/Disable the JS API for obtain ACELite version.
 *
 * Allowed values:
 *  0: Disable the JS API for obtain ACELite version.
 *  1: Enable the JS API for obtain ACELite version.
 *
 * Default: 1
 */
#ifndef ACE_LITE_VERSION_JS_API
#define ACE_LITE_VERSION_JS_API 1
#endif

/**
 * JS engine macro for engine adapter layer.
 */
#ifndef ENABLE_JERRY
#define ENABLE_JERRY 1
#endif
#endif // OHOS_ACELITE_JS_CONFIG_H
