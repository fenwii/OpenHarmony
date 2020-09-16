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
 * @file want.h
 *
 * @brief Declares the structure that provides abstract description of the operation to be performed, including the
 *        ability information and the carried data, and functions for setting data in the structure.
 *
 * You can use functions provided in this file to specify information about the ability to start.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OHOS_WANT_H
#define OHOS_WANT_H

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
#include <serializer.h>
#else
#include <stdint.h>
#endif

#include "element_name.h"

/**
 * @brief Defines the abstract description of an operation, including information about the ability and the extra data
 *        to carry.
 */
typedef struct {
    /**
     * Pointer to the ability information, including the device ID, bundle name, and class name.
     */
    ElementName *element;
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    /**
     * Pointer to the ID of the server that listens for ability startup. After the ability is started, the callback
     * function corresponding to the server will be invoked.
     */
    SvcIdentity *sid;
#endif
    /**
     * Pointer to the carried data
     */
    void *data;

    /**
     * Data length
     */
    uint16_t dataLength;
} Want;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus

/**
 * @brief Clears the memory of a specified <b>Want</b> object.
 *
 * After calling functions such as {@link SetWantElement}, you should call this function to clear the memory.
 *
 * @param want Indicates the pointer to the <b>Want</b> object whose memory is to be released.
 */
void ClearWant(Want *want);

/**
 * @brief Sets the <b>element</b> variable for a specified <b>Want</b> object.
 *
 * To start a specified ability, you should call this function to set the {@link ElementName} required for starting
 * the ability.
 *
 * @param want Indicates the pointer to the <b>Want</b> object to set.
 * @param element Indicates the {@link ElementName} containing information required for starting the ability.
 *
 * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
 */
bool SetWantElement(Want *want, ElementName element);

/**
 * @brief Sets data to carry in a specified <b>Want</b> object for starting a particular ability.
 *
 * @param want Indicates the pointer to the <b>Want</b> object to set.
 * @param data Indicates the pointer to the data to set.
 * @param dataLength Indicates the data length to set. The length must be the same as that of the data specified in
 *        <b>data</b>.
 *
 * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
 */
bool SetWantData(Want *want, const void *data, uint16_t dataLength);

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER

/**
 * @brief Sets the <b>sid</b> member variable for a specified <b>Want</b> object.
 *
 * When starting an ability, you should call this function to set an {@link SvcIdentity} object if a callback needs
 * to be invoked after the ability is started successfully.
 *
 * @param want Indicates the pointer to the <b>Want</b> object to set.
 * @param sid Indicates the {@link SvcIdentity} object to set.
 *
 * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
 */
bool SetWantSvcIdentity(Want *want, SvcIdentity sid);

/**
 * @brief Converts a specified <b>Want</b> object into a character string.
 *
 * @param want Indicates the <b>Want</b> object to convert.
 *
 * @return Returns the converted character string if the operation is successful; returns <b>nullptr</b> otherwise.
 */
const char *WantToUri(Want want);

/**
 * @brief Converts a specified character string into a <b>Want</b> object.
 *
 * @param uri Indicates the pointer to the character string to convert.
 *
 * @return Returns the pointer to the converted <b>Want</b> object if the operation is successful; returns
 *         <b>nullptr</b> otherwise.
 */
Want *WantParseUri(const char *uri);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus

#endif // OHOS_WANT_H
/** @} */