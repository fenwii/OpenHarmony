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
 * @file osal_time.h
 *
 * @brief Declares the time, sleep, and delay interfaces.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OSAL_TIME_H
#define OSAL_TIME_H

#include "hdf_base.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Defines time.
 */
typedef struct {
    uint64_t sec; /**< Second */
    uint64_t usec; /**< Microsecond */
} OsalTimespec;

/**
 * @brief Describes thread sleep, in seconds.
 *
 * When a thread invokes this function, the CPU is released and the thread enters the sleep state.
 *
 * @param sec Indicates the sleep time, in seconds.
 * @since 1.0
 * @version 1.0
 */
void OsalSleep(uint32_t sec);

/**
 * @brief Describes thread sleep, in milliseconds.
 *
 * When a thread invokes this function, the CPU is released and the thread enters the sleep state.
 *
 * @param ms Indicates the sleep time, in milliseconds.
 * @since 1.0
 * @version 1.0
 */
void OsalMSleep(uint32_t ms);

/**
 * @brief Obtains the second and microsecond time.
 *
 * @param time Indicates the pointer to the time structure {@link OsalTimespec}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to obtain time.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalGetTime(OsalTimespec *time);

/**
 * @brief Obtains time difference.
 *
 * @param start Indicates the pointer to the start time {@link OsalTimespec}.
 * @param end Indicates the pointer to the end time {@link OsalTimespec}.
 * @param diff Indicates the pointer to the time difference {@link OsalTimespec}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalDiffTime(const OsalTimespec *start, const OsalTimespec *end, OsalTimespec *diff);

/**
 * @brief Obtains the system time.
 *
 * @return Returns the system time, in milliseconds.
 * @since 1.0
 * @version 1.0
 */
uint64_t OsalGetSysTimeMs(void);

/**
 * @brief Describes thread delay, in milliseconds.
 *
 * When a thread invokes this function, the CPU is not released. This function returns after waiting for milliseconds.
 *
 * @param ms Indicates the delay time, in milliseconds.
 * @since 1.0
 * @version 1.0
 */
void OsalMDelay(uint32_t ms);

/**
 * @brief Describes thread delay, in microseconds.
 *
 * When a thread invokes this function, the CPU is not released. This function returns after waiting for microseconds.
 *
 * @param us Indicates the delay time, in microseconds.
 * @since 1.0
 * @version 1.0
 */
void OsalUDelay(uint32_t us);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_TIME_H */
/** @} */
