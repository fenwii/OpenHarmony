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

#ifndef OHOS_BUNDLE_STATUS_CALLBACK_H
#define OHOS_BUNDLE_STATUS_CALLBACK_H

/**
 * @brief Called when the installation, update, or uninstallation state of an application changes.
 *
 * This callback can be registered or unregistered through {@link RegisterCallback} or
 * {@link UnregisterCallback} to monitor the installation, update, and uninstallation state changes of
 * applications in the system.
 * @param installType Indicates the installation, update, or uninstallation state. The value <b>0</b> indicates that
 *                    the application is being installed or updated, and <b>1</b> indicates that the application is
 *                    being uninstalled.
 * @param resultCode Indicates the status code returned for the application installation, update, or uninstallation
 *                   result. For details, see {@link AppexecfwkErrors}.
 * @param resultMessage Indicates the result message returned with the status code.
 * @param bundleName Indicates the name of the bundle whose state has changed.
 *
 * @since 1.0
 * @version 1.0
 */
typedef void (*BundleStateCallback)(const uint8_t installType, const uint8_t resultCode, const void *resultMessage,
    const char *bundleName, void *data);

typedef struct {
    char *bundleName;
    void *data;
    BundleStateCallback callBack;
} BundleStatusCallback;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus
void ClearBundleStatusCallback(BundleStatusCallback *bundleStatusCallback);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus
#endif // OHOS_BUNDLE_STATUS_CALLBACK_H