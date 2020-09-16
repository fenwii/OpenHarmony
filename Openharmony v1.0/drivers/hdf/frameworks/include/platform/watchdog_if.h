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
 * @addtogroup WATCHDOG
 * @{
 *
 * @brief Provides watchdog APIs, such as setting the watchdog timeout duration and feeding a watchdog (resetting
 * a watchdog timer).
 *
 * If an error occurs in the main program of the system, for example, if the program crashes or the watchdog timer
 * is not reset in time, the watchdog timer generates a reset signal, and the system restores from the suspending
 * state to the normal state.
 *
 * @since 1.0
 */

/**
 * @file watchdog_if.h
 *
 * @brief Declares standard watchdog APIs.
 *
 * @since 1.0
 */

#ifndef WATCHDOG_IF_H
#define WATCHDOG_IF_H

#include "hdf_platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Enumerates watchdog statuses.
 *
 * To obtain the watchdog status, call the {@link WatchdogGetStatus} function.
 *
 * @since 1.0
 */
enum WatchdogStatus {
    WATCHDOG_STOP,  /**< Stopped */
    WATCHDOG_START, /**< Started */
};

/**
 * @brief Opens a watchdog.
 *
 * Before operating a watchdog, you must call this function to open it and obtain its device handle.
 *
 * @param wdtId Indicates the watchdog ID.
 *
 * @return Returns the pointer to the device handle of the watch dog if the operation is successful;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
struct DevHandle *WatchdogOpen(int16_t wdtId);

 /**
 * @brief Closes a watchdog.
 *
 * If you no longer need a watchdog, call this function to close it and release its device handle to prevent
 * unnecessary use of memory resources.
 *
 * @param handle Indicates the pointer to the watchdog device handle.
 *
 * @since 1.0
 */
void WatchdogClose(struct DevHandle *handle);

/**
 * @brief Obtains the watchdog status.
 *
 * For the available watchdog statuses, see {@link WatchdogStatus}.
 *
 * @param handle Indicates the pointer to the watchdog handle, which is obtained via {@link WatchdogOpen}.
 * @param status Indicates the pointer to the watchdog status.
 *
 * @return Returns <b>0</b> if the watchdog status is obtained; returns a negative value otherwise.
 *
 * @since 1.0
 */
int32_t WatchdogGetStatus(struct DevHandle *handle, int32_t *status);

/**
 * @brief Starts a watchdog.
 *
 * This function starts the watchdog timer. You must feed the watchdog periodically; otherwise, the watchdog hardware
 * will reset the system upon a timeout.
 *
 * @param handle Indicates the pointer to the watchdog handle, which is obtained via {@link WatchdogOpen}.
 *
 * @return Returns <b>0</b> if the watchdog is successfully started; returns a negative value otherwise.
 * @attention If the watchdog timer has started before this function is called, calling this function will succeed;
 * however, the watchdog hardware determines whether to reset the timer.
 *
 * @since 1.0
 */
int32_t WatchdogStart(struct DevHandle *handle);

/**
 * @brief Stops a watchdog.
 *
 * If the watchdog has stopped before this function is called, calling this function will succeed.
 *
 * @param handle Indicates the pointer to the watchdog handle, which is obtained via {@link WatchdogOpen}.
 *
 * @return Returns <b>0</b> if the watchdog is successfully stopped; returns a negative value otherwise.
 * @since 1.0
 */
int32_t WatchdogStop(struct DevHandle *handle);

/**
 * @brief Sets the watchdog timeout duration.
 *
 * @param handle Indicates the pointer to the watchdog handle, which is obtained via {@link WatchdogOpen}.
 * @param seconds Indicates the timeout duration, in seconds.
 *
 * @return Returns <b>0</b> if the setting is successful; returns a negative value otherwise.
 * @since 1.0
 */
int32_t WatchdogSetTimeout(struct DevHandle *handle, uint32_t seconds);

/**
 * @brief Obtains the watchdog timeout duration.
 *
 * @param handle Indicates the pointer to the watchdog handle, which is obtained via {@link WatchdogOpen}.
 * @param seconds Indicates the pointer to the timeout duration, in seconds.
 *
 * @return Returns <b>0</b> if the watchdog timeout duration is obtained; returns a negative value otherwise.
 * @since 1.0
 */
int32_t WatchdogGetTimeout(struct DevHandle *handle, uint32_t *seconds);

/**
 * @brief Feeds a watchdog, that is, resets a watchdog timer.
 *
 * After a watchdog is started, you must feed it to reset the watchdog timer periodically.
 * If you do not do so, the watchdog hardware will reset the system upon a timeout.
 *
 * @param handle Indicates the pointer to the watchdog handle, which is obtained via {@link WatchdogOpen}.
 *
 * @return Returns <b>0</b> if the watchdog is fed; returns a negative value otherwise.
 * @since 1.0
 */
int32_t WatchdogFeed(struct DevHandle *handle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* WATCHDOG_IF_H */
/** @} */
