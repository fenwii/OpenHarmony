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
 * @file osal_timer.h
 *
 * @brief Declares timer types and interfaces.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OSAL_TIMER_H
#define OSAL_TIMER_H

#include "hdf_base.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Describes a timer.
 */
typedef struct {
    void *realTimer; /**< Pointer to a timer object */
} OsalTimer;

/**
 * @brief Describes a timer execution function type.
 */
typedef void (*OsalTimerFunc)(uintptr_t arg);

/**
 * @brief Defines a timer macro.
 */
#define OSAL_DECLARE_TIMER(timer) OsalTimer timer

/**
 * @brief Creates a timer.
 *
 * @param timer Indicates the pointer to the timer {@link OsalTimer}.
 * @param interval Indicates the timer interval.
 * @param func Indicates the timer execution function {@link OsalTimerFunc}.
 * @param arg Indicates the argument passed to the timer execution function.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 * HDF_ERR_MALLOC_FAIL | Memory allocation fails.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalTimerCreate(OsalTimer *timer, uint32_t interval, OsalTimerFunc func, uintptr_t arg);

/**
 * @brief Deletes a timer.
 *
 * @param timer Indicates the pointer to the timer {@link OsalTimer}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to delete the timer.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalTimerDelete(OsalTimer *timer);

/**
 * @brief Starts a timer.
 *
 * @param timer Indicates the pointer to the timer {@link OsalTimer}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to start the timer.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalTimerStartOnce(OsalTimer *timer);

/**
 * @brief Starts a periodic timer.
 *
 * @param timer Indicates the pointer to the timer {@link OsalTimer}.
 * @param interval Indicates the timer interval, in milliseconds.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to start the timer.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalTimerStartLoop(OsalTimer *timer);

/**
 * @brief Sets the interval of a timer.
 *
 * @param timer Indicates the pointer to the timer {@link OsalTimer}.
 * @param interval Indicates the timer interval, in milliseconds.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalTimerSetTimeout(OsalTimer *timer, uint32_t interval);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_TIMER_H */
/** @} */
