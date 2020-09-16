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
 * @addtogroup BundleManager
 * @{
 *
 * @brief Provides structures and functions for managing application bundles and obtaining application information.
 *
 * You can use functions provided by this module to install, update, or uninstall an application, obtain
 * {@link AbilityInfo} and {@link BundleInfo} about an application, and obtain the bundle name of an application
 * based on the application's user ID (UID).
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file element_name.h
 *
 * @brief Declares the structure that defines the required information for querying {@link AbilityInfo}, including
 *        the device ID, bundle name, and class name, and functions for setting such information.
 *
 * You can use functions provided in this file to specify the information for querying {@link AbilityInfo}.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_ELEMENT_NAME_H
#define OHOS_ELEMENT_NAME_H

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
#include <serializer.h>
#endif
#include <stdbool.h>

/**
 * @brief Defines the ability information.
 */
typedef struct {
    /**
     * Pointer to the ID of the device running the application
     */
    char *deviceId;

    /**
     * Pointer to the bundle name of the application
     */
    char *bundleName;

    /**
     * Pointer to the class name of the ability
     */
    char *abilityName;
} ElementName;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus
/**
 * @brief Clears the internal data of a specified <b>ElementName</b>.
 *
 * After {@link AbilityInfo} is queried, clear the internal data of an <b>ElementName</b> if it is no longer required.
 * @param element Indicates the pointer to the <b>ElementName</b> to clear.
 */
void ClearElement(ElementName *element);

/**
 * @brief Sets the device ID used to query {@link AbilityInfo}.
 *
 * @param element Indicates the pointer to the <b>ElementName</b> to set.
 * @param deviceId Indicates the pointer to the device ID to set.
 *
 * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
 */
bool SetElementDeviceID(ElementName *element, const char *deviceId);

/**
 * @brief Sets the bundle name used to query {@link AbilityInfo}.
 *
 * @param element Indicates the pointer to the <b>ElementName</b> to set.
 * @param bundleName Indicates the pointer to the bundle name to set.
 *
 * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
 */
bool SetElementBundleName(ElementName *element, const char *bundleName);

/**
 * @brief Sets the class name of the ability used to query {@link AbilityInfo}.
 *
 * @param element Indicates the pointer to the <b>ElementName</b> to set.
 * @param abilityName Indicates the pointer to the class name to set.
 *
 * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
 */
bool SetElementAbilityName(ElementName *element, const char *abilityName);

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
bool SerializeElement(IpcIo *io, const ElementName *element);
bool DeserializeElement(ElementName *element, IpcIo *io);
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus

#endif // OHOS_ELEMENT_NAME_H
/** @} */
