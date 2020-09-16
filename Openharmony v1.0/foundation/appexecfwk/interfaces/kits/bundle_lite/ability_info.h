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
 * {@link AbilityInfo} and {@link BundleInfo} about an application, and obtain the bundle name of an application based
 * on the application's user ID (UID).
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ability_info.h
 *
 * @brief Declares structures and functions for managing ability information.
 *
 * You can use the function provided in this file to clear ability information.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_ABILITY_INFO_H
#define OHOS_ABILITY_INFO_H

#include <stdbool.h>

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
/**
* @brief Enumerates types of templates used by an ability.
*/
typedef enum {
    /** Unknown */
    UNKNOWN = 0,

    /** Page */
    PAGE,

    /** Service */
    SERVICE
} AbilityType;

/**
 * @brief Enumerates startup modes of an ability.
 */
typedef enum {
    /** Singleton mode, allowing only one instance */
    SINGLETON = 0,

    /** Standard mode, allowing multiple instances */
    STANDARD
} LaunchMode;
#endif

/**
 * @brief Defines the ability information.
 */
typedef struct {
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    /** Whether the ability is visible */
    bool isVisible;

    /** Template used by the ability */
    AbilityType abilityType;

    /** Startup mode of the ability */
    LaunchMode launchMode;

    /**
     * Pointer to the name of the HAP package to which the ability belongs. The HAP information is encapsulated in a
     * {@link ModuleInfo} object.
     */
    char *moduleName;

    /** Pointer to the class name of the ability */
    char *name;

    /** Pointer to the description of the ability */
    char *description;

    /** Pointer to the icon path of the ability */
    char *iconPath;

    /** Pointer to the device ID */
    char *deviceId;

    /** Pointer to the ability name visible to users */
    char *label;
#else
    /** Pointer to the source code path. This field is available only to basic watches. */
    char *srcPath;
#endif
    /** Pointer to the application bundle name */
    char *bundleName;
} AbilityInfo;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus
/**
 * @brief Clears an {@link AbilityInfo} object.
 *
 * This function clears and releases the memory occupied by the fields of the pointer type included in the specified
 * {@link AbilityInfo} object.
 * @param abilityInfo Indicates the pointer to the {@link AbilityInfo} object to clear.
 *
 * @since 1.0
 * @version 1.0
 */
void ClearAbilityInfo(AbilityInfo *abilityInfo);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus

#endif  // OHOS_ABILITY_INFO_H
/** @} */