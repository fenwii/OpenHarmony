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
 * @file ability_connection.h
 * @brief Declares callbacks to be invoked when a remote Service ability is connected or disconnected.
 *
 * You must override the callbacks provided in {@link IAbilityConnection} to implement your processing logic for
 * Service connection and disconnection.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_ABILITY_CONNECTION_H
#define OHOS_ABILITY_CONNECTION_H

#include "element_name.h"
#include "liteipc_adapter.h"

typedef struct IAbilityConnection IAbilityConnection;

/**
* @brief Provides callbacks to be invoked when a remote Service ability is connected or disconnected.
*/
struct IAbilityConnection {
    /**
     * @brief Called when a client is connected to a Service ability.
     *
     * This callback is invoked to receive the connection result after a client is connected to a Service ability.
     *
     * @param elementName Indicates the pointer to the information about the connected Service ability.
     * @param serviceSid Indicates the pointer to the remote proxy object of the Service ability.
     * @param resultCode Indicates the connection result code. The value <b>0</b> indicates a successful connection,
     *                   and any other value indicates a connection failure.
     * @param data Indicates the pointer to the data stored during the connection.
     */
    void (*OnAbilityConnectDone)(ElementName *elementName, SvcIdentity *serviceSid, int resultCode, void *data);

    /**
     * @brief Called after all connections to a Service ability are disconnected.
     *
     * This callback is invoked to receive the disconnection result after the connected Service ability crashes or is
     * killed. If the Service ability exits unexpectedly, all its connections are disconnected, and each ability
     * previously connected to it will call
     * {@link OnAbilityDisconnectDone(ElementName *elementName, int resultCode, void *data)}.
     *
     * @param elementName Indicates the pointer to the information about the disconnected Service ability.
     * @param resultCode Indicates the disconnection result code. The value <b>0</b> indicates a successful
     *                   disconnection, and any other value indicates a disconnection failure.
     * @param data Indicates the pointer to the data stored during the connection.
     */
    void (*OnAbilityDisconnectDone)(ElementName *elementName, int resultCode, void *data);
};
#endif // OHOS_ABILITY_CONNECTION_H
