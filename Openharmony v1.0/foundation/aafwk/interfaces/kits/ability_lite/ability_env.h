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
 * @file ability_env.h
 *
 * @brief Declares functions for obtaining information about the runtime environment of the application to which the
 *        ability belongs, including the bundle name, source code path, and data path.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OHOS_ABILITY_ENV_H
#define OHOS_ABILITY_ENV_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Obtains the bundle name of the application to which this ability belongs.
 *
 * @return Returns the pointer to the bundle name if the operation is successful; returns a null pointer otherwise.
 */
const char *GetBundleName();

/**
 * @brief Obtains the source code path of this ability.
 *
 * @return Returns the pointer to the source code path of this ability.
 */
const char *GetSrcPath();

/**
 * @brief Obtains the data path of this ability.
 *
 * @return Returns the pointer to the data path of this ability.
 */
const char *GetDataPath();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif // OHOS_ABILITY_ENV_H