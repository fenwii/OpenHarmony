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
 * @file feature.h
 *
 * @brief Defines the base class of a feature.
 *
 * This class is used to develop service features. \n
 * It provides functions for the feature lifecycle of a service. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef LITE_FEATURE_H
#define LITE_FEATURE_H

#include "message.h"
#include "service.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct Feature Feature;

/**
 * @brief Defines the base class of a feature.
 *
 * You need to implement the pointer to the feature. \n
 *
 * @since 1.0
 * @version 1.0
 */
struct Feature {
    /**
     * @brief Obtains a feature name.
     *
     * This function is implemented by developers and called by Samgr during feature registration
     * and startup. \n
     *
     * @param feature Indicates the pointer to the feature.
     * @return Returns a constant character string less than 16 bytes if the operation is
     * successful; returns <b>NULL</b> if the operation fails.
     *
     * @since 1.0
     * @version 1.0
     */
    const char *(*GetName)(Feature *feature);

    /**
     * @brief Initializes a feature.
     *
     * This function is implemented by developers. After Samgr dispatches tasks to a service, the
     * service calls this function in its own tasks. \n
     *
     * @param feature Indicates the pointer to the feature.
     * @param parent Indicates the pointer to the {@link Service} to which the feature belongs.
     * @param identity Indicates the identity of a feature dispatched by the system.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*OnInitialize)(Feature *feature, Service *parent, Identity identity);

    /**
     * @brief Stops a feature.
     *
     * This function is implemented by developers and is called by Samgr when a feature is
     * deregistered to stop running services. \n
     *
     * @param feature Indicates the pointer to the feature.
     * @param identity Indicates the {@link Identity} of the feature to be stopped.
     * @since 1.0
     * @version 1.0
     */
    void (*OnStop)(Feature *feature, Identity identity);

    /**
     * @brief Processes a feature message.
     *
     * This function is implemented by developers to process requests sent by callers through
     * IUnknown. \n
     *
     * @param feature Indicates the pointer to the feature.
     * @param request Indicates the request message.
     * @return Returns <b>TRUE</b> if the processing is successful; returns <b>FALSE</b> if
     * the processing fails.
     *
     * @since 1.0
     * @version 1.0
     */
    BOOL (*OnMessage)(Feature *feature, Request *request);
};

/**
 * @brief Inherits from the macro of the feature class.
 *
 * This macro provides the capability of inheriting the feature lifecycle. \n
 *
 */
#define INHERIT_FEATURE                                                         \
    const char *(*GetName)(Feature *feature);                                   \
    void (*OnInitialize)(Feature *feature, Service *parent, Identity identity); \
    void (*OnStop)(Feature *feature, Identity identity);                        \
    BOOL (*OnMessage)(Feature *feature, Request *request)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif // LITE_FEATURE_H
/** @} */
