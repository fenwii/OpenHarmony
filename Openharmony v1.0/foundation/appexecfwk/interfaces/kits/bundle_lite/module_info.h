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
 * @file module_info.h
 *
 * @brief Declares structures and functions for managing HAP package information.
 *
 * The HAP package is used to deploy {@link Ability} instances. It is a module package consisting of the code,
 * resources, third-party libraries, and an application configuration file. You can use the function provided in this
 * file to clear HAP information.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OHOS_BUNDLE_MODULE_INFO_H
#define OHOS_BUNDLE_MODULE_INFO_H

#include <stdbool.h>
#include "stdint.h"

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
#define DEVICE_TYPE_SIZE 16
#endif
#define METADATA_SIZE 16

/**
 * @brief Defines the metadata information in a {@link ModuleInfo} object.
 */
typedef struct {
    /** Pointer to the metadata name */
    char *name;

    /** Pointer to the metadata value */
    char *value;

    /** Extra data. You can customize this field as required. */
    char *extra;
} MetaData;

/**
 * @brief Defines the HAP information.
 */
typedef struct {
    /** Pointer to the HAP package name */
    char *moduleName;
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER

    /** Pointer to the description of the HAP package */
    char *description;

    /** Pointer to the class name of the HAP package */
    char *name;

    /** Type of the HAP package, either <b>Entry.hap</b> or <b>Feature.hap</b> */
    char *moduleType;

    /** Whether the HAP package is installed while the user is installing the application */
    bool isDeliveryInstall;

    /** 
     * Pointer to the types of devices that can run the application. The maximum size of the device type array is
     * {@link DEVICE_TYPE_SIZE}.
     */
    char *deviceType[DEVICE_TYPE_SIZE];
#endif

    /** Pointer to the metadata array whose maximum size is {@link METADATA_SIZE} */
    MetaData *metaData[METADATA_SIZE];
} ModuleInfo;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus
/**
 * @brief Clears a {@link ModuleInfo} object.
 *
 * This function clears and releases the memory occupied by the fields of the pointer type included in the specified
 * {@link ModuleInfo} object.
 * @param moduleInfo Indicates the pointer to the {@link ModuleInfo} object to clear.
 *
 * @since 1.0
 * @version 1.0
 */
void ClearModuleInfo(ModuleInfo *moduleInfo);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus

#endif // OHOS_BUNDLE_MODULE_INFO_H
/** @} */