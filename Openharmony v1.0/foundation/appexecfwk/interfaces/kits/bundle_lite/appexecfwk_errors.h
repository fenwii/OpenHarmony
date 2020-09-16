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
 * @file appexecfwk_errors.h
 *
 * @brief Declares error codes returned by bundle management functions.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OHOS_APPEXECFWK_ERRORS_H
#define OHOS_APPEXECFWK_ERRORS_H

/**
 * @brief Enumerates error codes provided by the Bundle Manager Service.
 */
enum AppexecfwkErrors {
    /** The function is successfully called. */
    ERR_OK = 0,

    /** Incorrect parameter for querying {@link AbilityInfo} or {@link BundleInfo}. */
    ERR_APPEXECFWK_QUERY_PARAMETER_ERROR,

    /** No {@link AbilityInfo} or {@link BundleInfo} is found. */
    ERR_APPEXECFWK_QUERY_NO_INFOS,

    /** An error occurred when initializing {@link BundleInfo} or {@link AbilityInfo} during information query. */
    ERR_APPEXECFWK_QUERY_INFOS_INIT_ERROR,

    /** The object or pointer is null. */
    ERR_APPEXECFWK_OBJECT_NULL,

    /** Failed to install the application due to an internal logic error. */
    ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR = 10,

    /** Failed to install the application due to incorrect parameters. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARAM_ERROR,

    /** Failed to install the application because the installation file path is invalid. */
    ERR_APPEXECFWK_INSTALL_FAILED_FILE_PATH_INVALID,

    /** Failed to install the application because the installation file does not exist. */
    ERR_APPEXECFWK_INSTALL_FAILED_FILE_NOT_EXISTS,

    /** Failed to install the application because the installation file name is invalid. */
    ERR_APPEXECFWK_INSTALL_FAILED_INVALID_FILE_NAME,

    /** Failed to install the application due to incorrect file content. */
    ERR_APPEXECFWK_INSTALL_FAILED_BAD_FILE,

    /** Failed to install the application due to a file creation error. */
    ERR_APPEXECFWK_INSTALL_FAILED_CREATE_FILE_ERROR,

    /** Failed to install the application due to a file path creation error. */
    ERR_APPEXECFWK_INSTALL_FAILED_CREATE_CODE_DIR_ERROR,

    /** Failed to install the application due to a file path deletion error. */
    ERR_APPEXECFWK_INSTALL_FAILED_REMOVE_CODE_DIR_ERROR,

    /** Failed to install the application because an error occurred when creating the permission file directory. */
    ERR_APPEXECFWK_INSTALL_FAILED_CREATE_PERMISSIONS_DIR_ERROR,

    /** Failed to install the application due to a path renaming error. */
    ERR_APPEXECFWK_INSTALL_FAILED_RENAME_DIR_ERROR,
    /** Failed to install the application due to a file renaming error. */
    ERR_APPEXECFWK_INSTALL_FAILED_RENAME_FILE_ERROR,

    /** Failed to install the application due to an error occurred when removing the data path. */
    ERR_APPEXECFWK_INSTALL_FAILED_REMOVE_DATA_DIR_ERROR,

    /** Failed to install the application due to an error occurred when creating the data path. */
    ERR_APPEXECFWK_INSTALL_FAILED_CREATE_DATA_DIR_ERROR,

    /** Failed to install the application due to an error occurred when recording installation information. */
    ERR_APPEXECFWK_INSTALL_FAILED_RECORD_INFO_ERROR,

    /** Failed to install the application due to an error occurred when backing up the UID and GID. */
    ERR_APPEXECFWK_INSTALL_FAILED_UID_AND_GID_BACKUP_ERROR,

    /** Failed to install the application due to an error occurred when changing ownership of the data directory. */
    ERR_APPEXECFWK_INSTALL_FAILED_CHOWN_DATA_DIR_ERROR,

    /** Failed to install the application because an application of a later version has been installed. */
    ERR_APPEXECFWK_INSTALL_FAILED_VERSION_DOWNGRADE,

    /**
     * Failed to install the application because the number of installed applications exceeds the maximum (30). This
     * error code is available only to basic watches.
     */
    ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_BUNDLE_NUMBER,

    /** Failed to install the application due to an error occurred when storing permission information. */
    ERR_APPEXECFWK_INSTALL_FAILED_STORE_PERMISSIONS_ERROR,

    /**
     * Failed to install the application due to invalid file data. This error code is available only to basic
     * watches.
     */
    ERR_APPEXECFWK_INSTALL_FAILED_FILE_DATA_INVALID,

    /** Failed to install the application due to unmatched signature used for version update. */
    ERR_APPEXECFWK_INSTALL_FAILED_INCOMPATIBLE_SIGNATURE,

    /** Failed to install the application due to unmatched provisioning information during signature verification. */
    ERR_APPEXECFWK_INSTALL_FAILED_INVALID_PROVISIONINFO,

    /** Failed to install the application due to an error occurred when processing the signature file. */
    ERR_APPEXECFWK_INSTALL_FAILED_OPERATE_SIGNED_FILE_ERROR,

    /** Failed to install the application due to an error occurred when parsing the application signature. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_APP_SIGNATURE_ERROR,

    /** Failed to install the application due to an error occurred when parsing the file signature. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_SIGNATURE_ERROR,

    /** Failed to install the application due to an internal error during signature verification. */
    ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_SIGNATURE_ERROR,

    /** Failed to install the application due to an error occurred when setting the signature verification mode. */
    ERR_APPEXECFWK_SET_DEBUG_MODE_ERROR,

    /** Failed to parse the file. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_ERROR = 40,

    /** Failed to parse the bundle name. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_BUNDLENAME_ERROR,

    /** Invalid bundle name. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_BUNDLENAME,

    /** Failed to parse the vendor information. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VENDOR_ERROR,

    /** Failed to parse the version code. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VERSIONCODE_ERROR,

    /** Failed to parse the version name. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VERSIONNAME_ERROR,

    /** Failed to parse the installation permission information. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PERMISSIONS_ERROR,

    /** Failed to parse the API version. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_API_VERSION_ERROR,

    /** Failed to parse the device configuration. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICE_CONFIG_ERROR,

    /** Failed to parse the <b>isKeepAlive</b> field of the application. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_KEEPALIVE_ERROR,

    /**
     * Failed to parse the <b>name</b> field of the application's HAP package. The HAP information is encapsulated in
     * a {@link ModuleInfo} object.
     */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULENAME_ERROR,

    /** Invalid HAP name. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_MODULENAME,

    /** Failed to parse the HAP description information. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULE_DESCRIPTION_ERROR,

    /** Failed to parse the <b>deviceType</b> field of the application's HAP package. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICETYPE_ERROR,

    /** Failed to parse the HAP information. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_ERROR,

    /** Failed to parse the <b>moduleName</b> field of the application's HAP package. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULENAME_ERROR,

    /** Invalid HAP type. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULETYPE_ERROR,

    /** Failed to parse the <b>isDeliveryInstall</b> field of the application's HAP package. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_DELIVERY_ERROR,

    /** Failed to parse the {@link MetaData} information. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_METADATA_ERROR,

    /** Failed to parse the {@link AbilityInfo}. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITIES_ERROR,

    /** Failed to parse the class name of the ability. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_NAME_ERROR,

    /** Failed to parse the template used by the ability. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_TYPE_ERROR,

    /** Failed to parse the icon path of the ability. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_ICONPATH_ERROR,

    /** Failed to parse the label of the ability. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LABEL_ERROR,

    /** Failed to parse the description of the ability. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_DESCRIPTION_ERROR,

    /** Failed to parse the startup mode of the ability. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LAUNCHTYPE_ERROR,

    /** Failed to parse the <b>isVisible</b> field of the ability. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_VISIBLE_ERROR,

    /** Invalid length of the bundle name. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_BUNDLENAME_LENGTH,

    /** The parsed application label exceeds the maximum length (255 bytes). */
    ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_LABEL_LENGTH_ERROR,

    /** The parsed application version name exceeds the maximum length (127 bytes). */
    ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_VERSIONNAME_LENGTH_ERROR,

    /** The parsed application metadata name exceeds the maximum length (255 bytes). */
    ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_METADATA_NAME_LENGTH_ERROR,

    /** The parsed application metadata value exceeds the maximum length (255 bytes). */
    ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_METADATA_VALUE_LENGTH_ERROR,

    /** The parsed application vendor name exceeds the maximum length (255 bytes). */
    ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_VENDOR_LENGTH_ERROR,

    /** The parsed HAP name exceeds the maximum length (31 bytes). */
    ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_MODULENAME_LENGTH_ERROR,

    /** The parsed ability class name exceeds the maximum length (127 bytes). */
    ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITYNAME_LENGTH_ERROR,

    /** The parsed ability description exceeds the maximum length (255 bytes). */
    ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITY_DESCRIPTION_LENGTH_ERROR,

    /** The parsed ability label exceeds the maximum length (255 bytes). */
    ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITY_LABEL_LENGTH_ERROR,

    /** Failed to initialize the extractor. */
    ERR_APPEXECFWK_INSTALL_FAILED_EXTRACTOR_NOT_INIT,

    /** Failed to extract hap. */
    ERR_APPEXECFWK_INSTALL_FAILED_EXTRACT_HAP_ERROR,

    /** Failed to parse the JavaScript path. This error code is available only to basic watches. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_JS_DIR_ERROR,

    /** The resource index does not exist. */
    ERR_APPEXECFWK_INSTALL_FAILED_RESOURCE_INDEX_NOT_EXISTS,

    /** Failed to parse the label resource. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_LABEL_RES_ERROR,

    /** Failed to parse the icon resource. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ICON_RES_ERROR,

    /** Failed to parse the description resource. */
    ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DESCRIPTION_RES_ERROR,

    /** Failed to install the application due to a request sending error. */
    ERR_APPEXECFWK_INSTALL_FAILED_SEND_REQUEST_ERROR,

    /** Failed to uninstall the application due to an internal error. */
    ERR_APPEXECFWK_UNINSTALL_FAILED_INTERNAL_ERROR = 90,

    /** Failed to uninstall the application due to incorrect input parameters. */
    ERR_APPEXECFWK_UNINSTALL_FAILED_PARAM_ERROR,

    /** Failed to uninstall the application because it does not exist. */
    ERR_APPEXECFWK_UNINSTALL_FAILED_BUNDLE_NOT_EXISTS,

    /** Failed to uninstall the application due to an error occurred when deleting the path. */
    ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_DIRS_ERROR,

    /** Failed to uninstall the application due to an error occurred when deleting the installation record. */
    ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_RECORD_INFO_ERROR,

    /** Failed to uninstall the application due to an error occurred when deleting the permission information. */
    ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_PERMISSIONS_ERROR,

    /** Failed to uninstall the application because the application cannot be uninstalled. */
    ERR_APPEXECFWK_UNINSTALL_FAILED_BUNDLE_NOT_UNINSTALLABLE,

    /** Failed to uninstall the application due to an error occurred when deleting the UID information. */
    ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_UID_INFO_ERROR,

    /** Failed to uninstall the application due to a request sending error. */
    ERR_APPEXECFWK_UNINSTALL_FAILED_SEND_REQUEST_ERROR,

    /** Incorrect dump information. */
    ERR_APPEXECFWK_DUMP_ERROR = 100,

    /** Incorrect command. */
    ERR_APPEXECFWK_COMMAND_ERROR,

    /** Failed to register the callback. */
    ERR_APPEXECFWK_CALLBACK_REGISTER_FAILED,

    /** Failed to unregister the callback. */
    ERR_APPEXECFWK_CALLBACK_UNREGISTER_FAILED,

    /** Failed to generate a service ID for the current process. */
    ERR_APPEXECFWK_CALLBACK_GENERATE_LOCAL_SERVICEID_FAILED,

    /** Failed to transmit the service ID of the current process. */
    ERR_APPEXECFWK_CALLBACK_SERVICEID_TRANSMITTED_FAILED,

    /** The callback is never registered. */
    ERR_APPEXECFWK_CALLBACK_NEVER_REGISTERED,

    /** Failed to obtain the bundle names of all applications in the system. */
    ERR_APPEXECFWK_CALLBACK_OBTAIN_ALL_BUNDLE_FAILED,

    /** The required callback is unavailable. */
    ERR_APPEXECFWK_CALLBACK_NULL_CORRESPONDING_CALLBACK,

    /** Failed to obtain the installation type (installation or uninstallation). */
    ERR_APPEXECFWK_CALLBACK_GET_INSTALLTYPE_FAILED,

    /** Incorrect installation type. */
    ERR_APPEXECFWK_CALLBACK_GET_ERROR_INSTALLTYPE,

    /** Serialization failed. */
    ERR_APPEXECFWK_SERIALIZATION_FAILED,

    /** Deserialization failed. */
    ERR_APPEXECFWK_DESERIALIZATION_FAILED,

    /** Internal system error. */
    ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR,

    /** No bundle name associated with the UID is found. */
    ERR_APPEXECFWK_NO_BUNDLENAME_FOR_UID,

    /** The {@link IpcIo} structure is unavailable. */
    ERR_APPEXECFWK_IPCIO_UNAVAILABLED,

    /** An error occurred when calling the <b>invoke</b> function of the Bundle Manager Service. */
    ERR_APPEXECFWK_INVOKE_ERROR,

    /** The server that invokes the Bundle Manager Service does not have required permission. */
    ERR_APPEXECFWK_PERMISSION_DENIED,
};
#endif  // OHOS_APPEXECFWK_ERRORS_H
/** @} */