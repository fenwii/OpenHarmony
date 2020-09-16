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
 * @file bundle_info.h
 *
 * @brief Declares structures and functions for managing application bundle information.
 *
 * You can use the function provided in this file to clear bundle information.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OHOS_BUNDLE_INFO_H
#define OHOS_BUNDLE_INFO_H

#include "ability_info.h"
#include "module_info.h"
#include "stdint.h"

/**
 * @brief Defines the bundle information.
 */
typedef struct {
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    /** Whether the application is kept alive */
    bool isKeepAlive;

    /**
     * Whether the application is a local application. A local application refers to an application developed using
     * C++ in the system. The value <b>true</b> indicates a local application, and <b>false</b> indicates a non-local
     * application.
     */
    bool isNativeApp;

    /** UID allocated during application installation */
    int32_t uid;

    /** Application group ID allocated during application installation */
    int32_t gid;
#endif
    /**
     * Whether the application is a system application. System applications cannot be uninstalled. The value
     * <b>true</b> indicates a system application, and <b>false</b> indicates a non-system application.
     */
    bool isSystemApp;

    /** Pointer to the minimum API version required for running the application */
    int32_t compatibleApi;

    /** Pointer to the target API version for running the application */
    int32_t targetApi;

    /** Version code of the application, which is the internal version number */
    int32_t versionCode;

    /** Pointer to the version name visible to users */
    char *versionName;

    /** Pointer to the bundle name of the application */
    char *bundleName;

    /** Pointer to the application name visible to users */
    char *label;

    /** Pointer to the big icon of the application */
    char *bigIconPath;

    /**
     * Pointer to the installation path of the application, which is in the <b>/app/run/<i>bundle name</i></b>
     * format
     */
    char *codePath;

    /** Pointer to the path for storing data files of the application. The data path is <b>/app/data</b>. */
    char *dataPath;

    /** Pointer to the vendor name of the application */
    char *vendor;

    /**
     * Pointer to the HAP package information about the application. The HAP information is encapsulated in
     * {@link ModuleInfo} objects.
     */
    ModuleInfo *moduleInfos;

    /** Number of {@link ModuleInfo} objects included in the application */
    int32_t numOfModule;
#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
    /** Pointer to the shared library path */
    char *sharedLibPath;

    /**
     * Application ID, which uniquely identifies an application. It is a combination of the bundle name and
     * signature of the application.
     */
    char *appId;

    /**
     * Pointer to the ability information about the application. The ability information is encapsulated in
     * {@link AbilityInfo} objects.
     */
    AbilityInfo *abilityInfos;

    /** Number of {@link AbilityInfo} objects in the application */
    int32_t numOfAbility;
#else
    /**
     * Pointer to the path for storing the small icon of the application. This field is available only to basic
     * watches.
     */
    char *smallIconPath;

    /** Pointer to the ability information about the application. This field is available only to basic watches. */
    AbilityInfo *abilityInfo;
#endif
} BundleInfo;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus
/**
 * @brief Clears a {@link BundleInfo} object.
 *
 * This function clears and releases the memory occupied by the fields of the pointer type included in the specified
 * {@link BundleInfo} object.
 * @param bundleInfo Indicates the pointer to the {@link BundleInfo} object to clear.
 *
 * @since 1.0
 * @version 1.0
 */
void ClearBundleInfo(BundleInfo *bundleInfo);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus

#endif // OHOS_BUNDLE_INFO_H
/** @} */