/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup PMS
 * @{
 *
 * @brief Manages permissions.
 *
 * This module provides interfaces for managing permissions of third-party applications.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file pms_interface.h
 *
 * @brief Declares interfaces for managing permissions.
 *
 * The interfaces can be used to authenticate native APIs, query, grant, and revoke permissions,
 * and grant runtime permissions.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_PERMISSIONMANAGESERVICE_INTERFACE_H
#define OHOS_PERMISSIONMANAGESERVICE_INTERFACE_H

#include "pms_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Checks whether the caller (generally a third-party application) has a specified permission
 * of a system service API.
 *
 * @param taskId Indicates the process ID of the caller. The range is [0, INT_MAX].
 * @param permissionName Indicates the pointer to the permission name. For details, see the developer
 * documentation.
 * @return Returns <b>1</b> if the caller has the permission; returns <b>0</b> otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
int CheckPermission(int taskID, const char *permissionName);

/**
 * @brief Queries all permissions requested by the application and checks whether these permissions are granted.
 *
 * @param identifier Indicates the pointer to the application bundle name.
 * @param permissions Indicates the double pointer to the array of permissions. You need to pass the
 * {@link PermissionSaved} pointer and release it after finishing using it.
 * @param permNum Indicates the pointer to the number of permissions in the array, which is an integer.
 * @return Returns <b>0</b> if the operation is successful; returns an error code defined in
 * {@link PmsErrorCode} otherwise.
 *
 * @since 1.0
 * @version 1.0
 *
 */
int QueryPermission(const char *identifier, PermissionSaved **permissions, int *permNum);

/**
 * @brief Grants a specified permission to the application.
 *
 * @param identifier Indicates the pointer to the application bundle name.
 * @param permName Indicates the pointer to the permission name. For details, see the developer documentation.
 * @return Returns <b>0</b> if the permission is successfully granted; returns an error code defined in
 * {@link PmsErrorCode} otherwise.
 *
 * @since 1.0
 * @version 1.0
 *
 */
int GrantPermission(const char *identifier, const char *permName);

/**
 * @brief Revokes a specified permission from the application.
 *
 * @param identifier Indicates the pointer to the application bundle name.
 * @param permName Indicates the pointer to the permission name. For details, see the developer documentation.
 * @return Returns <b>0</b> if the permission is successfully revoked; returns an error code defined in
 * {@link PmsErrorCode} otherwise.
 *
 * @since 1.0
 * @version 1.0
 *
 */
int RevokePermission(const char *identifier, const char *permName);

/**
 * @brief Grants a specified runtime permission to an application.
 *
 * This function applies to sensitive permissions that can be granted to the application only when the
 * application is running.
 *
 * @param taskId Indicates the process ID of the application. The range is [0, INT_MAX].
 * @param permissionName Indicates the pointer to the permission name. For details, see the developer documentation.
 * @return Returns <b>0</b> if the permission is successfully granted; returns an error code defined in
 * {@link PmsErrorCode} otherwise.
 *
 * @since 1.0
 * @version 1.0
 *
 */
int GrantRuntimePermission(int taskID, const char *permissionName);

/**
 * @brief Requests a specified permission.
 *
 * @param taskId Indicates the process ID of the application. The range is [0, INT_MAX].
 * @param permissionName Indicates the pointer to the permission name. For details, see the developer
 * documentation.
 * @return Returns <b>0</b> if the operation is successful; returns an error code defined in {@link PmsErrorCode}
 * otherwise.
 *
 * @since 1.0
 * @version 1.0
 *
 */
int RequestPermission(int taskID, const char *permissionName);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // OHOS_PERMISSIONMANAGESERVICE_INTERFACE_H