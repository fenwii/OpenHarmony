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
 * @file bundle_manager.h
 *
 * @brief Declares functions used for managing application bundles and obtaining bundle information.
 *
 * You can use functions provided in this file to install, update, or uninstall an application, obtain
 * {@link AbilityInfo} and {@link BundleInfo} about an application, obtain the bundle name of an application based
 * on the application's user ID (UID), and obtain {@link BundleInfo} objects of all applications or keep-alive
 * applications in the system.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OHOS_BUNDLEMANAGER_INTERFACE_H
#define OHOS_BUNDLEMANAGER_INTERFACE_H

#include "ability_info.h"
#include "bundle_info.h"
#include "bundle_status_callback.h"
#include "install_param.h"
#include "stdint.h"
#include "want.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Called when an application is installed, updated, or uninstalled.
 *
 * This function can be registered through {@link Install} and {@link Uninstall} to receive the installation, update,
 * and uninstallation result.
 *
 * @param resultCode Indicates the status code returned for the application installation, update, or uninstallation
 *                   result. For details, see {@link AppexecfwkErrors}.
 * @param resultMessage Indicates the result message returned with the status code.
 *
 * @since 1.0
 * @version 1.0
 */
typedef void (*InstallerCallback)(const uint8_t resultCode, const void *resultMessage);

/**
 * @brief Registers a callback to monitor the installation, update, and uninstallation state changes of an application.
 *
 * @param bundleCallback Indicates the callback to be invoked when the installation, update, or uninstallation state
 *                       of the monitored application changes.
 * @param bundleName Indicates the pointer to the bundle name of the application to monitor. If this parameter is set
 *                   to <b>nullptr</b>, the installation, update, or uninstallation state of all applications will be
 *                   monitored.
 * @return Returns {@link ERR_OK} if this function is successfully called; returns another error code defined in
 *         {@link AppexecfwkErrors} otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t RegisterCallback(BundleStatusCallback *BundleStatusCallback);

/**
 * @brief Unregisters a callback previously registered for monitoring the installation, update, and uninstallation
 *        state changes of an application.
 *
 * @param bundleName Indicates the pointer to the bundle name of the application being monitored. If this parameter
 *                   is set to <b>nullptr</b>, monitoring on the installation, update, or uninstallation state of
 *                   all applications will be canceled.
 * @return Returns {@link ERR_OK} if this function is successfully called; returns another error code defined in
 *        {@link AppexecfwkErrors} otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t UnregisterCallback();

/**
 * @brief Installs or updates an application.
 *
 * @param hapPath Indicates the pointer to the path for storing the OpenHarmony Ability Package (HAP) of the application
 *                to install or update.
 * @param bundleCallback Indicates the callback to be invoked for notifying the installation or update result.
 * @return Returns <b>true</b> if this function is successfully called; returns <b>false</b> otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
bool Install(const char *hapPath, const InstallParam *installParam, InstallerCallback installerCallback);

/**
 * @brief Uninstalls an application.
 *
 * @param bundleName Indicates the pointer to the bundle name of the application to uninstall.
 * @param bundleCallback Indicates the callback to be invoked for notifying the uninstallation result.
 * @return Returns <b>true</b> if this function is successfully called; returns <b>false</b> otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
bool Uninstall(const char *bundleName, const InstallParam *installParam, InstallerCallback installerCallback);

/**
 * @brief Queries the {@link AbilityInfo} of an ability based on the information carried in the {@link Want}
 *        structure.
 * @attention Before querying an {@link AbilityInfo} object, you should first call <b>memset</b> on the
 *            constructed {@link AbilityInfo} object so that each field in it can be properly initialized
 *            for carrying the obtained information.
 * @param want Indicates the pointer to the {@link Want} structure used for querying the specified ability.
 * @param abilityInfo Indicates the pointer to the obtained {@link AbilityInfo} object.
 *
 * @return Returns {@link ERR_OK} if this function is successfully called; returns another error code defined in
 *         {@link AppexecfwkErrors} otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
uint8_t QueryAbilityInfo(const Want *want, AbilityInfo *abilityInfo);

/**
 * @brief Obtains the {@link BundleInfo} of an application based on the specified bundle name.
 *
 * @attention Before querying a {@link BundleInfo} object, you should first call <b>memset</b> on the constructed
 *            {@link BundleInfo} object so that each field in it can be properly initialized for carrying the
 *            obtained information.
 * @param bundleName Indicates the pointer to the name of the application bundle to query.
 * @param flags Specifies whether the obtained {@link BundleInfo} object can contain {@link AbilityInfo}. The value
 *              <b>1</b> indicates that it can contain {@link AbilityInfo}, and <b>0</b> indicates that it cannot.
 * @param bundleInfo Indicates the pointer to the obtained {@link BundleInfo} object.
 *
 * @return Returns {@link ERR_OK} if this function is successfully called; returns another error code defined in
 *         {@link AppexecfwkErrors} otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
uint8_t GetBundleInfo(const char *bundleName, int32_t flags, BundleInfo *bundleInfo);

/**
 * @brief Obtains the {@link BundleInfo} of all bundles in the system.
 *
 * @param flags Specifies whether each of the obtained {@link BundleInfo} objects can contain {@link AbilityInfo}.
 *               The value <b>1</b> indicates that it can contain {@link AbilityInfo}, and <b>0</b> indicates that
 *              it cannot.
 * @param bundleInfos Indicates the double pointer to the obtained {@link BundleInfo} objects.
 * @param len Indicates the pointer to the number of {@link BundleInfo} objects obtained.
 * @return Returns {@link ERR_OK} if this function is successfully called; returns another error code defined in
 *         {@link AppexecfwkErrors} otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
uint8_t GetBundleInfos(const int flags, BundleInfo **bundleInfos, int32_t *len);

/**
 * @brief Obtains the {@link BundleInfo} of all keep-alive applications in the system.
 *
 * @param bundleInfos Indicates the double pointer to the obtained {@link BundleInfo} objects.
 * @param len Indicates the pointer to the number of {@link BundleInfo} objects obtained.
 * @return Returns {@link ERR_OK} if this function is successfully called; returns another error code defined in
 *        {@link AppexecfwkErrors} otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
uint8_t QueryKeepAliveBundleInfos(BundleInfo **bundleInfos, int32_t *len);

/**
 * @brief Obtains the {@link BundleInfo} of application bundles based on the specified {@link MetaData}.
 *
 * @param metaDataKey Indicates the pointer to the metadata name in the {@link MetaData}.
 * @param bundleInfos Indicates the double pointer to the obtained {@link BundleInfo} objects.
 * @param len Indicates the pointer to the number of {@link BundleInfo} objects obtained.
 * @return Returns {@link ERR_OK} if this function is successfully called; returns another error code defined in
 *         {@link AppexecfwkErrors} otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
uint8_t GetBundleInfosByMetaData(const char *metaDataKey, BundleInfo **bundleInfos, int32_t *len);

/**
 * @brief Obtains the bundle name of an application based on the specified UID.
 *
 * @param uid Indicates the UID of the application to query.
 * @param bundleName Indicates the double pointer to the bundle name of the application.
 * @return Returns {@link ERR_OK} if this function is successfully called; returns another error code defined in
 *         {@link AppexecfwkErrors} otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
uint8_t GetBundleNameForUid(int32_t uid, char **bundleName);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* OHOS_BUNDLEMANAGER_INTERFACE_H */
/** @} */