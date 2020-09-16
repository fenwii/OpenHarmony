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
 * @addtogroup Samgr
 * @{
 *
 * @brief Manages system capabilities.
 *
 * This module provides the development framework base of the service-oriented architecture (SOA).
 * You can develop your own abilities based on the Samgr development framework. \n
 * This module provides basic models of services, features, and functions, and registration and
 * discovery capabilities. \n
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file samgr_lite.h
 *
 * @brief Manages system capabilities.
 *
 * This is used when services, features, and functions are registered with and discovered by Samgr. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef LITE_SAMGR_H
#define LITE_SAMGR_H

#include "common.h"
#include "iunknown.h"
#include "service.h"
#include "feature.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Starts a bootstrap service, which is used by samgr and implemented by system service
 * developers.
 */
#define BOOTSTRAP_SERVICE "Bootstrap"

/**
 * @brief Enumerates the IDs of the message to be processed for starting the bootstrap service.
 *
 * This function is implemented by developers of the system service. \n
 * Messages sent to the bootstrap service when Samgr is started. \n
 *
 */
typedef enum BootMessage {
    /** Message indicating that the core system service is initialized */
    BOOT_SYS_COMPLETED,
    /** Message indicating that the system and application-layer services are initialized */
    BOOT_APP_COMPLETED,
    /** Message indicating service registration during running */
    BOOT_REG_SERVICE,
    /** Maximum number of message IDs */
    BOOTSTRAP_BUTT
} BootMessage;

/**
 * @brief Represents the system ability management class.
 *
 * This class is used for registering and discovering services, features, and functions. \n
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct SamgrLite {
    /**
     * @brief Registers a service.
     *
     * You need to call this function in the startup entry of each service. \n
     * {@link Service} and {@link Service} structure members to be registered cannot be empty. \n
     *
     * @param service Indicates the service to be registered.
     * @return Returns <b>TRUE</b> if the registration is successful; returns <b>FALSE</b>
     * if the registration fails.
     * @since 1.0
     * @version 1.0
     */
    BOOL (*RegisterService)(Service *service);

    /**
     * @brief Unregisters a service.
     *
     * You need to call this function when the service is no longer required. \n
     *
     * @param name Indicates the name of the service to be unregistered.
     * @attention Before unregistering the service, you must unregister its features and functions.
     * @return Returns the unregistered service object if the unregistration is successful.
     * The memory is released by the caller. Returns <b>NULL</b> if the unregistration fails.
     * @since 1.0
     * @version 1.0
     */
    Service *(*UnregisterService)(const char *name);

    /**
     * @brief Registers a feature.
     *
     * You need to call this function in the startup entry of each feature. \n
     * {@link Feature} and {@link Feature} structure members to be registered cannot be empty. \n
     *
     * @param feature Indicates the feature to be registered.
     * @return Returns <b>TRUE</b> if the registration is successful; returns <b>FALSE</b>
     * if the registration fails.
     * @since 1.0
     * @version 1.0
     */
    BOOL (*RegisterFeature)(const char *serviceName, Feature *feature);

    /**
     * @brief Unregisters a feature.
     *
     * You need to call this function when the feature is no longer required. \n
     *
     * @param serviceName Indicates the name of the service whose feature will be unregistered.
     * @param featureName Indicates the name of the feature to be unregistered.
     * @attention Before unregistering the feature, you must unregister its functions. Otherwise,
     * the unregistration fails.
     * @return Returns the unregistered feature object if the unregistration is successful.
     * The memory is released by the caller. Returns <b>NULL</b> if the unregistration fails.
     * @since 1.0
     * @version 1.0
     */
    Feature *(*UnregisterFeature)(const char *serviceName, const char *featureName);

    /**
     * @brief Registers the API for the default feature of a service.
     *
     * You need to call this function after the service is registered. \n
     * The pointers to the {@link IUnknown} and {@link IUnknown} members to be registered
     * cannot be empty. \n
     *
     * @param service Indicates the name of the service whose default feature's API will be
     * registered.
     * @param publicApi Indicates the API to be registered.
     * @return Returns <b>TRUE</b> if the registration is successful; returns <b>FALSE</b>
     * if the registration fails.
     * @since 1.0
     * @version 1.0
     */
    BOOL (*RegisterDefaultFeatureApi)(const char *service, IUnknown *publicApi);

    /**
     * @brief Unregisters the API from the default feature of a service.
     *
     * You need to call this function to unregister {@link IUnknown} if the service to which
     * the default feature belongs is no longer required. \n
     *
     * @param service Indicates the name of the service whose default feature's API will be
     * unregistered.
     * @return Returns the unregistered function object if the unregistration is successful.
     * The memory is released by the caller. Returns <b>NULL</b> if the unregistration fails.
     * @since 1.0
     * @version 1.0
     */
    IUnknown *(*UnregisterDefaultFeatureApi)(const char *service);

    /**
     * @brief Registers the API for a feature.
     *
     * You can call this function only if the feature has been registered. \n
     * The pointers to the {@link IUnknown} and {@link IUnknown} members to be registered cannot
     * be empty. \n
     *
     * @param service Indicates the name of the service whose API will be registered.
     * @param feature Indicates the name of the feature whose API will be registered.
     * @param publicApi Indicates the API to be registered.
     * @return Returns <b>TRUE</b> if the registration is successful; returns <b>FALSE</b>
     * if the registration fails.
     * @since 1.0
     * @version 1.0
     */
    BOOL (*RegisterFeatureApi)(const char *service, const char *feature, IUnknown *publicApi);

    /**
     * @brief Unregisters the API from a feature.
     *
     * You must call this function before unregistering the feature no longer required. \n
     *
     * @param service Indicates the name of the service whose API will be unregistered.
     * @param feature Indicates the name of the feature whose API will be unregistered.
     * @return Returns the unregistered function object if the unregistration is successful.
     * The memory is released by the caller. Returns <b>NULL</b> if the unregistration fails.
     * @since 1.0
     * @version 1.0
     */
    IUnknown *(*UnregisterFeatureApi)(const char *service, const char *feature);

    /**
     * @brief Obtains the API specific to the default feature.
     *
     * You need to call this function before using the system capabilities of the service involved. \n
     *
     *
     * @param service Indicates the name of the service to which the default feature belongs.
     * @return Returns the <b>IUnknown *</b> object that can be called if the operation is
     * successful; returns <b>NULL</b> if the operation fails.
     * @since 1.0
     * @version 1.0
     */
    IUnknown *(*GetDefaultFeatureApi)(const char *service);

    /**
     * @brief Obtains the API specific to the feature.
     *
     * You need to call this function before using the system capabilities of the service involved. \n
     *
     *
     * @param service Indicates the name of the service to which the feature belongs.
     * @param feature Indicates the name of the feature whose API will be obtained.
     * @return Returns the <b>IUnknown *</b> object that can be called if the operation is
     * successful; returns <b>NULL</b> if the operation fails.
     * @since 1.0
     * @version 1.0
     */
    IUnknown *(*GetFeatureApi)(const char *serviceName, const char *feature);
} SamgrLite;

/**
 * @brief Obtains the singleton Samgr instance.
 *
 * You need to call this function before using the Samgr capabilities. \n
 *
 * @return Returns the pointer to the singleton instance {@link SamgrLite}.
 * @since 1.0
 * @version 1.0
 */
SamgrLite *SAMGR_GetInstance(void);

/**
 * @brief Starts system services and features.
 *
 * This function is called in the <b>main</b> function to start all services when an independent
 * process is developed. \n
 * This function is called after the dynamic library (containing system services and features) is
 * loaded during system running. \n
 *
 * @attention This function cannot be called frequently. Otherwise, problems such as repeated
 * service startup may occur. It is recommended that this function be called once in the
 * <b>main</b> function or after the dynamic library is loaded.
 * @since 1.0
 * @version 1.0
 */
void SAMGR_Bootstrap(void);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif // LITE_SAMGR_H
/** @} */
