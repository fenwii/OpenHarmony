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
 * @file ability_manager.h
 *
 * @brief Declares ability-related functions, including functions for starting, stopping, connecting to,
 * and disconnecting from an ability, registering a callback, and unregistering a callback.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OHOS_ABILITY_MANAGER_H
#define OHOS_ABILITY_MANAGER_H

#include "ability_connection.h"
#include "want.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Starts an ability based on the specified {@link Want} information.
 *
 * @param want Indicates the pointer to the {@link Want} structure containing information about the ability to start.
 * @return Returns <b>0</b> if this function is successfully called; returns another value otherwise.
 */
int StartAbility(const Want *want);

/**
 * @brief Stops an ability based on the specified {@link Want} information.
 *
 * This function takes effect only on Service abilities.
 *
 * @param want Indicates the pointer to the {@link Want} structure containing information about the ability to stop.
 * @return Returns <b>0</b> if this function is successfully called; returns another value otherwise.
 */
int StopAbility(const Want *want);

/**
 * @brief Connects to a Service ability based on the specified {@link Want} information.
 *
 * After the Service ability is connected, the AMS invokes the particular
 * callback and returns the ID of the Service ability.
 * The client can use this ID to communicate with the connected Service ability.
 *
 * @param want Indicates the pointer to the {@link Want} structure containing
 *             information about the Service ability to connect.
 * @param conn Indicates the callback object when the Service ability is connected.
 * @param data Indicates the pointer to the data to be passed to the callback.
 * @return Returns <b>0</b> if this function is successfully called; returns another value otherwise.
 */
int ConnectAbility(const Want *want, const IAbilityConnection *conn, void *data);

/**
 * @brief Disconnects from a Service ability.
 *
 * @param conn Indicates the callback object when the Service ability is connected.
 * @return Returns <b>0</b> if this function is successfully called; returns another value otherwise.
 */
int DisconnectAbility(const IAbilityConnection *conn);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* OHOS_ABILITY_MANAGER_H */
