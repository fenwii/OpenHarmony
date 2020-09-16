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
 * @file input_manager.h
 *
 * @brief Declares the driver interfaces for managing input devices.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "input_controller.h"
#include "input_reporter.h"
#include "input_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provides interfaces for managing input devices.
 *
 * The interfaces can be used to perform basic operations on the input devices, such as opening and closing the device
 * files and querying information about the input device.
 */
typedef struct {
    /**
     * @brief Opens a specified input device file.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in
     * {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*OpenInputDevice)(uint32_t devIndex);

    /**
     * @brief Closes a specified input device file.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in
     * {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*CloseInputDevice)(uint32_t devIndex);

    /**
     * @brief Gets information about a specified input device.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param devInfo Indicates the double pointer to information about the specified device.
     * For details, see {@link DeviceInfo}.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in
     * {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetInputDevice)(uint32_t devIndex, DeviceInfo **devInfo);

    /**
     * @brief Gets information about all input devices in the device list.
     *
     * @param devNum Indicates the pointer to the total number of input devices which have been registered.
     * @param devList Indicates the double pointer to information about all devices in the device list.
     * For details, see {@link DeviceInfo}.
     * @param size Indicates the number of elements in the <b>devList</b> array.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined
     * in {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetInputDeviceList)(uint32_t *devNum, DeviceInfo **devList, uint32_t size);
} InputManager;

/**
 * @brief Defines interfaces for providing driver capabilities of input devices.
 */
typedef struct {
    InputManager *iInputManager;          /**< Device management interface for input devices */
    InputController *iInputController;    /**< Service control interface for input devices */
    InputReporter *iInputReporter;        /**< Data reporting interface for input devices */
} IInputInterface;

/**
 * @brief Gets all interfaces for performing operations on input devices.
 *
 * You can call this function after the input service is started.
 *
 * @param interface Indicates the double pointer to the interface for performing operations on input devices.
 * @return Returns <b>0</b> if the operation is successful; returns an error code defined in
 * {@link RetStatus} otherwise.
 * @since 1.0
 * @version 1.0
 */
int GetInputInterface(IInputInterface **interface);

#ifdef __cplusplus
}
#endif
#endif
/** @} */