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
 * @addtogroup AbilityKit
 * @{
 *
 * @brief Provides ability-related functions, including ability lifecycle callbacks and functions for connecting to or
 *        disconnecting from Particle Abilities.
 *
 * Abilities are classified into Feature Abilities and Particle Abilities. Feature Abilities support the Page template,
 * and Particle Abilities support the Service template. An ability using the Page template is called a Page ability for
 * short and that using the Service template is called a Service ability.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ability_errors.h
 *
 * @brief Declares error codes returned by ability management functions.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_ABILITY_ERRORS_H
#define OHOS_ABILITY_ERRORS_H

/**
* @brief Declares error codes returned by ability management functions.
*/
enum {
    /** The function is successfully called. */
    ERR_OK = 0,

    /** The parameter is null. */
    PARAM_NULL_ERROR,

    /** Memory allocation error. */
    MEMORY_MALLOC_ERROR,

    /** An error occurred during the execution of the <b>Dump</b> function. */
    DUMP_ABILITIES_ERROR,

    /** IPC request error. */
    IPC_REQUEST_ERROR,

    /** Serialization error. */
    SERIALIZE_ERROR,

    /** Command error. */
    COMMAND_ERROR = 0x7fff,
};
#endif  // OHOS_ABILITY_ERRORS_H