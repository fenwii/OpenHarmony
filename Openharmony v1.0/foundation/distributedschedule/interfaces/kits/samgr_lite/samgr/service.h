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
 * @file service.h
 *
 * @brief Provides basic types and constants of services.
 *
 * This file is mainly used for service development. \n
 * This file provides basic capabilities such as lifecycle functions of services, inherited macros,
 * and task configuration. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef LITE_SERVICE_H
#define LITE_SERVICE_H

#include "message.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct TaskConfig TaskConfig;
typedef struct Service Service;

/**
 * @brief Enumerates task types.
 *
 * These enumerations are used for configuring the task type. \n
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum TaskType {
    /** Tasks shared based on their priority by services */
    SHARED_TASK = 0,
    /** Task exclusively occupied by a service */
    SINGLE_TASK = 1,
    /** A specified task shared by multiple services */
    SPECIFIED_TASK = 2,
    /** No task for the service. Generally, this situation does not occur. */
    NO_TASK = 0xFF,
} TaskType;

/**
 * @brief Specifies the tag for the task shared by multiple services.
 *
 * These enumerations are used for specifying a multi-service sharing task. \n
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum SpecifyTag {
    /** Preset tag */
    LEVEL_HIGH = 0,
    /** Preset tag */
    LEVEL_MIDDLE = 1,
    /** Preset tag */
    LEVEL_LOW = 2,
    /** Customized tag */
    LEVEL_CUSTOM_BEGIN,
} SpecifyTag;

/**
 * @brief Enumerates task priority.
 *
 * These enumerations are used for configuring the task priority. \n
 * The valid range of the priority is (9, 39). \n
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum TaskPriority {
    /** Low-priority: (9, 15) */
    PRI_LOW = 9,
    /** Lower than the normal priority: [16, 23) */
    PRI_BELOW_NORMAL = 16,
    /** Normal priority: [24, 31). The log service is available. */
    PRI_NORMAL = 24,
    /** Higher than the normal priority: [32, 39). The communication service is available. */
    PRI_ABOVE_NORMAL = 32,
    /** Upper limit of the priority */
    PRI_BUTT = 39,
} TaskPriority;

#pragma pack(1)
/**
 * @brief Defines task configurations for a service.
 *
 * This structure defines task configurations for a service, including the task priority,
 * stack size, queue size, task type, and shared task ID. \n
 *
 */
struct TaskConfig {
    /**
     * ID of a multi-service sharing task. For details about the level definition,
     * see {@link SpecifyTag}.
     */
    int16 level;
    /** Task priority. For details about the definition of priority, see {@link TaskPriority}. */
    int16 priority;
    /** Size of a task stack */
    uint16 stackSize;
    /** Size of a task queue */
    uint16 queueSize;
    /** Task type. For details about the taskFlags definition, see {@link TaskType}. */
    uint8 taskFlags;
};
#pragma pack()

/**
 * @brief Indicates the basic type of a service.
 *
 * You need to implement the function pointers of <b>Service</b>. \n
 *
 */
struct Service {
    /**
     * @brief Obtains the name of a service.
     *
     * This function is called by Samgr during service registration and startup. You need to
     * implement this function. \n
     *
     * @param service Indicates the pointer to the service.
     * @return Returns a constant string no more than 16 bytes if the service name is obtained
     * successfully; returns <b>NULL</b> if the service name fails to be obtained.
     * @since 1.0
     * @version 1.0 */
    const char *(*GetName)(Service *service);

    /**
     * @brief Initializes the service.
     *
     * After Samgr assigns tasks to a service, the service calls the function in its own tasks.
     * You need to implement this function. \n
     *
     * @param service Indicates the pointer to the service.
     * @param identity Indicates the ID allocated by the system to the service. For details,
     * see {@link Identity}.
     * @return Returns <b>TRUE</b> if the initialization is successful; returns <b>FALSE</b>
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    BOOL (*Initialize)(Service *service, Identity identity);

    /**
     * @brief Processes service messages.
     *
     * This function is used to process requests sent by the caller through {@link IUnknown}.
     * You need to implement this function. \n
     *
     * @param service Indicates the pointer to the service.
     * @param request Indicates the pointer to the request data.
     * @return Returns <b>TRUE</b> if the message processing is successful; returns <b>FALSE</b>
     * if the processing fails.
     * @since 1.0
     * @version 1.0
     */
    BOOL (*MessageHandle)(Service *service, Request *request);

    /**
     * @brief Obtains task configurations of a service.
     *
     * This function is used to return task configurations. You need to implement this function. \n
     *
     * @param service Indicates the pointer to the service.
     * @return Returns {@link TaskConfig}.
     *
     * @since 1.0
     * @version 1.0 */
    TaskConfig (*GetTaskConfig)(Service *service);
};

/**
 * @brief Indicates the macro used to inherit the members from the <b>service</b> class.
 *
 * This macro provides the capability of inheriting the lifecycle functions of the <b>service</b>
 * class. You can use this macro to customize the service structure. \n
 */
#define INHERIT_SERVICE                                          \
    const char *(*GetName)(Service * service);                   \
    BOOL (*Initialize)(Service * service, Identity identity);    \
    BOOL (*MessageHandle)(Service * service, Request * request); \
    TaskConfig (*GetTaskConfig)(Service * service)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_SERVICE_H
/** @} */
