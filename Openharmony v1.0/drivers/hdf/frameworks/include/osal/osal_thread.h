/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @addtogroup OSAL
 * @{
 *
 * @brief Defines the structures and interfaces for the Operating System Abstraction Layer (OSAL) module.
 *
 * The OSAL module harmonizes OS interface differences and provides unified OS interfaces externally,
 * including the memory management, thread, mutex, spinlock, semaphore, timer, file, interrupt, time,
 * atomic, firmware, and I/O operation modules.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file osal_thread.h
 *
 * @brief Declares thread types and interfaces.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OSAL_THREAD_H
#define OSAL_THREAD_H

#include "hdf_base.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Enumerates thread priorities.
 */
typedef enum {
    OSAL_THREAD_PRI_LOW, /**< Low priority */
    OSAL_THREAD_PRI_DEFAULT, /**< Default priority */
    OSAL_THREAD_PRI_HIGH, /**< High priority */
    OSAL_THREAD_PRI_HIGHEST /**< Highest priority */
} OSAL_THREAD_PRIORITY;

/**
 * @brief Describes thread parameters.
 */
struct OsalThreadParam {
    char *name; /**< Thread name */
    size_t stackSize; /**< Stack size of a thread */
    OSAL_THREAD_PRIORITY priority; /**< Thread priority */
};

/**
 * @brief Defines a thread callback function type.
 */
typedef int (*OsalThreadEntry)(void *);

/**
 * @brief Describes a thread.
 */
struct OsalThread {
    int32_t status; /**< Thread running status */
    void *realThread; /**< Pointer to a created thread object */
};

/**
 * @brief Defines a thread macro.
 */
#define OSAL_DECLARE_THREAD(thread) struct OsalThread thread

/**
 * @brief Creates a thread.
 *
 * @param thread Indicates the pointer to the thread {@link OsalThread}.
 * @param threadEntry Indicates the thread callback function {@link OsalThreadEntry}.
 * @param entryPara Indicates the pointer to the parameter passed to the thread callback function.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 * HDF_ERR_MALLOC_FAIL | Memory allocation fails.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalThreadCreate(struct OsalThread *thread, OsalThreadEntry threadEntry, void *entryPara);
/**
 * @brief Starts a thread.
 *
 * @param thread Indicates the pointer to the thread {@link OsalThread}.
 * @param param Indicates the pointer to the parameter used to start a thread. For details, see {@link OsalThreadParam}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to start the thread.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalThreadStart(struct OsalThread *thread, const struct OsalThreadParam *param);

/**
 * @brief Destroys a thread.
 *
 * @param thread Indicates the pointer to the thread {@link OsalThread}.
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to destroy the thread.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalThreadDestroy(struct OsalThread *thread);

/**
 * @brief Suspends a thread.
 *
 * @param thread Indicates the pointer to the thread {@link OsalThread}.
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to suspend the thread.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalThreadSuspend(struct OsalThread *thread);

/**
 * @brief Resumes a thread.
 *
 * @param thread Indicates the pointer to the thread {@link OsalThread}.
  * @since 1.0
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to resume the thread.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @version 1.0
 */
int32_t OsalThreadResume(struct OsalThread *thread);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_THREAD_H */
/** @} */
