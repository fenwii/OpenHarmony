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
 * @addtogroup Input
 * @{
 *
 * @brief Provides driver interfaces for the input service.
 *
 * These driver interfaces can be used to open and close input device files, get input events, query device information,
 * register callback functions, and control the feature status.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file input_reporter.h
 *
 * @brief Declares the driver interfaces for reporting data of input devices.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef INPUT_REPORTER_H
#define INPUT_REPORTER_H

#include "input_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provides interfaces for reporting event data of input devices.
 *
 * The interfaces include the callback for reporting the input event data and the functions for obtaining the data
 * in polling mode.
 */
typedef struct {
    /**
     * @brief Registers a callback for reporting subscribed data of specified input devices.
     *
     * After this callback is successfully registered, the driver can report the input event data to the input
     * service through this callback.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param callback Indicates the pointer to the callback to register.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in
     * {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*RegisterReportCallback)(uint32_t devIndex, InputReportEventCb *callback);

    /**
     * @brief Unregisters the callback for reporting subscribed data of specified input devices.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in
     * {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*UnregisterReportCallback)(uint32_t devIndex);

    /**
     * @brief Gets the input event data.
     *
     * This function enables the input service to proactively obtain the input event data in polling mode.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param eventData Indicates the pointer to the input event data reported by the input driver.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in
     * {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetInputEvent)(uint32_t devIndex, InputEventData *eventData);
} InputReporter;

#ifdef __cplusplus
}
#endif
#endif
/** @} */