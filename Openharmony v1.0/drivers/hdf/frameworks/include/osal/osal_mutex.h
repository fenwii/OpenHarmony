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
 * @file osal_mutex.h
 *
 * @brief Declares mutex types and interfaces.
 *
 * This file provides interfaces for initializing and destroying a mutex, locking a mutex,
 * locking a mutex upon timeout, and unlocking a mutex. The mutex must be destroyed after being used.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OSAL_MUTEX_H
#define OSAL_MUTEX_H

#include "hdf_base.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Describes a mutex.
 */
struct OsalMutex {
    void *realMutex; /**< Pointer to a mutex object to operate */
};

/**
 * @brief Defines a mutex.
 */
#define OSAL_DECLARE_MUTEX(mutex) struct OsalMutex mutex

/**
 * @brief Initializes a mutex.
 *
 * @param mutex Indicates the pointer to the mutex {@link OsalMutex}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to initialize the mutex.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalMutexInit(struct OsalMutex *mutex);

/**
 * @brief Destroys a mutex.
 *
 * @param mutex Indicates the pointer to the mutex {@link OsalMutex}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to destroy the mutex.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalMutexDestroy(struct OsalMutex *mutex);

/**
 * @brief Locks a mutex.
 *
 * @param mutex Indicates the pointer to the mutex {@link OsalMutex}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to lock the mutex.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalMutexLock(struct OsalMutex *mutex);

/**
 * @brief Locks a mutex with a specified timeout duration.
 *
 * @param mutex Indicates the pointer to the mutex {@link OsalMutex}.
 * @param ms Indicates the timeout duration, in milliseconds.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to lock the mutex.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 * HDF_ERR_TIMEOUT | Timeout occurs.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalMutexTimedLock(struct OsalMutex *mutex, uint32_t ms);

/**
 * @brief Unlocks a mutex.
 *
 * @param mutex Indicates the pointer to the mutex {@link OsalMutex}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to unlock the mutex.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalMutexUnlock(struct OsalMutex *mutex);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_MUTEX_H */
/** @} */
