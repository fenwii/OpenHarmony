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
 * @file osal_sem.h
 *
 * @brief Declares semaphore structures and interfaces.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OSAL_SEM_H
#define OSAL_SEM_H

#include "hdf_base.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Describes a semaphore.
 */
struct OsalSem {
    void *realSemaphore; /**< Pointer to a semaphore to operate */
};

/**
 * @brief Defines a semaphore.
 */
#define OSAL_DECLARE_SEMAPHORE(sem) struct OsalSem sem

/**
 * @brief Initializes a semaphore.
 *
 * @param sem Indicates the pointer to the semaphore {@link OsalSem}.
 * @param value Indicates the initial value of the semaphore.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to initialize the semaphore.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalSemInit(struct OsalSem *sem, uint32_t value);

/**
 * @brief Waits for a semaphore.
 *
 * @param sem Indicates the pointer to the semaphore {@link OsalSem}.
 * @param ms Indicates the timeout interval.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to wait for the semaphore.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 * HDF_ERR_TIMEOUT | Timeout occurs.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalSemWait(struct OsalSem *sem, uint32_t ms);

/**
 * @brief Releases a semaphore.
 *
 * @param sem Indicates the pointer to the semaphore {@link OsalSem}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to release the semaphore.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalSemPost(struct OsalSem *sem);

/**
 * @brief Destroys a semaphore.
 *
 * @param sem Indicates the pointer to the semaphore {@link OsalSem}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to destroy the semaphore.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalSemDestroy(struct OsalSem *sem);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_SEM_H */
/** @} */
