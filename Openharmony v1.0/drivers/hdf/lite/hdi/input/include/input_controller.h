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
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file input_controller.h
 *
 * @brief Declares the driver interfaces for controlling the business process of input devices.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include "input_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provides interfaces for controlling the business process of input devices.
 *
 * The interfaces can be called to control the power status, enable or disable a feature, get driver chip information,
 * and control the production test.
 */
typedef struct {
    /**
     * @brief Sets the power status.
     *
     * This function is called only when the power status of the OS is changed. \n
     * The input service or the power management module can call this function to set the power status
     * for the input device when the OS is in the Resume or Suspend status, so that the driver integrated circuit (IC)
     * of the device can normally enter the specified status.
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param status Indicates the power status to set. The input service will notify the input device of entering the
     * Resume or Suspend state specified by {@link PowerStatus}.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in
     * {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetPowerStatus)(uint32_t devIndex, uint32_t status);

    /**
     * @brief Gets the power status.
     *
     * The input service or the power management module can set the power status for the input device when the OS
     * is in the Resume or Suspend status, so that the driver IC of the device can normally enter the specified status.
     * You can call this function to obtain the power status.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param status Indicates the pointer to the power status of the device. For details, see {@link PowerStatus}.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined in
     * {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetPowerStatus)(uint32_t devIndex, uint32_t *status);

    /**
     * @brief Gets the type of the input device based on the specified device index.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param deviceType Indicates the pointer to the device type. For details, see {@link InputDevType}.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined
     * in {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetDeviceType)(uint32_t devIndex, uint32_t *deviceType);

    /**
     * @brief Gets the chip information of the specified device.
     *
     * A product is usually equipped with modules and driver ICs provided by multiple vendors. An input service
     * can call this function to get the specific information if needed.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param chipInfo Indicates the pointer to the chip information.
     * @param length Indicates the length of the chip information.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined
     * in {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetChipInfo)(uint32_t devIndex, char *chipInfo, uint32_t length);

    /**
     * @brief Gets the module vendor name of the specified device.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param vendorName Indicates the pointer to the module vendor name.
     * @param length Indicates the length of the vendor name.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined
     * in {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetVendorName)(uint32_t devIndex, char *vendorName, uint32_t length);

    /**
     * @brief Gets the driver chip name of the specified device.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param chipName Indicates the pointer to the driver chip name.
     * @param length Indicates the length of the driver chip name.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined
     * in {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*GetChipName)(uint32_t devIndex, char *chipName, uint32_t length);

    /**
     * @brief Sets the gesture mode.
     *
     * The input service can use this function to enable or disable the gesture mode by setting <b>EnableBit</b>
     * of the gesture mode.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param gestureMode Indicates the gesture mode to set.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined
     * in {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*SetGestureMode)(uint32_t devIndex, uint32_t gestureMode);

    /**
     * @brief Conducts a capacitance self-test.
     *
     * The capacitance self-test items are defined by the component vendor, such as the tests on the raw data,
     * short circuit, open circuit, interference, and row/column difference.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param testType Indicates the capacitance test type. For details, see {@link CapacitanceTest}.
     * @param result Indicates the pointer to the capacitance test result. The value is <b>SUCC</b> for a successful
     * operation and is an error code for a failed operation.
     * @param length Indicates the length of the test result.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined
     * in {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*RunCapacitanceTest)(uint32_t devIndex, uint32_t testType, char *result, uint32_t length);

    /**
     * @brief Executes the extra command.
     *
     * @param devIndex Indicates the index of an input device. A maximum of 32 input devices are supported.
     * The value ranges from 0 to 31, and value <b>0</b> represents the first input device.
     * @param cmd Indicates the pointer to the extra command data packet, including the command codes and parameters.
     * For details, see {@link InputExtraCmd}.
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined
     * in {@link RetStatus} otherwise.
     * @since 1.0
     * @version 1.0
     */
    int32_t (*RunExtraCommand)(uint32_t devIndex, InputExtraCmd *cmd);
} InputController;

#ifdef __cplusplus
}
#endif
#endif
/** @} */