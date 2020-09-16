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
 * @addtogroup wifiiot
 * @{
 *
 * @brief Provides dedicated device operation interfaces on the Wi-Fi module,
 * including ADC, AT, flash, GPIO, I2C, I2S, partition, PWM, SDIO, UART, and watchdog.
 *
 *
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file hal_wifiiot_i2c_ex.h
 *
 * @brief Declares the extended I2C interface functions.
 *
 * These functions are used for I2C baud rate setting and device exception callback. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HAL_WIFIIOT_I2C_EX_H
#define HAL_WIFIIOT_I2C_EX_H

#include "hal_wifiiot_i2c.h"

/**
 * @brief Indicates the callback invoked when a device exception occurs.
 *
 */
typedef void (*HalI2CResetFunc)(void);
/**
 * @brief Indicates the callback invoked for device preparation.
 *
 */
typedef void (*HalI2cPrepareFunc)(void);
/**
 * @brief Indicates the callback invoked for device recovery.
 *
 */
typedef void (*HalI2cRestoreFunc)(void);

/**
 * @brief Defines I2C callbacks.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /** Callback invoked upon an I2C device exception */
    HalI2CResetFunc   resetFunc;
    /** Callback invoked for data preparation */
    HalI2cPrepareFunc prepareFunc;
    /** Callback invoked for data recovery */
    HalI2cRestoreFunc restoreFunc;
} HalWifiIotI2cFunc;

/**
 * @brief Sends data to and receives data responses from an I2C device.
 *
 *
 *
 * @param id Indicates the I2C device ID.
 * @param deviceAddr Indicates the I2C device address.
 * @param i2cData Indicates the pointer to the device descriptor of the data to receive.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalI2cWriteread(HalWifiIotI2cIdx id, unsigned short deviceAddr, const HalWifiIotI2cData *i2cData);

/**
 * @brief Registers an I2C callback.
 *
 * @param id Indicates the I2C device ID.
 * @param pfn Indicates the type of the callback to register.
 *
 * @since 1.0
 * @version 1.0
 */
void HalI2cRegisterResetBusFunc(HalWifiIotI2cIdx id, HalWifiIotI2cFunc pfn);

/**
 * @brief Sets the baud rate for an I2C device.
 *
 *
 *
 * @param id Indicates the I2C device ID.
 * @param baudrate Indicates the I2C baud rate to set.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalI2cSetBaudrate(HalWifiIotI2cIdx id, unsigned int baudrate);

#endif
/** @} */
