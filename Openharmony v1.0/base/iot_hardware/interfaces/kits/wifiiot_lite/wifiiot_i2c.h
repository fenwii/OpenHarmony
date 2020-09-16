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
 * @file wifiiot_i2c.h
 *
 * @brief Declares the I2C interface functions.
 *
 * These functions are used for I2C initialization and data transmission. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef WIFIIOT_I2C_H
#define WIFIIOT_I2C_H

/**
 * @brief Defines I2C data transmission attributes.
 */
typedef struct {
    /** Pointer to the buffer storing data to send */
    unsigned char *sendBuf;
    /** Length of data to send */
    unsigned int  sendLen;
    /** Pointer to the buffer for storing data to receive */
    unsigned char *receiveBuf;
    /** Length of data received */
    unsigned int  receiveLen;
} WifiIotI2cData;

/**
 * @brief Enumerates I2C hardware indexes.
 */
typedef enum {
    /** I2C hardware index 0 */
    WIFI_IOT_I2C_IDX_0,
    /** I2C hardware index 1 */
    WIFI_IOT_I2C_IDX_1,
} WifiIotI2cIdx;

/**
 * @brief Initializes an I2C device with a specified baud rate.
 *
 *
 *
 * @param id Indicates the I2C device ID.
 * @param baudrate Indicates the I2C baud rate.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int I2cInit(WifiIotI2cIdx id, unsigned int baudrate);

/**
 * @brief Deinitializes an I2C device.
 *
 * @param id Indicates the I2C device ID.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int I2cDeinit(WifiIotI2cIdx id);

/**
 * @brief Writes data to an I2C device.
 *
 *
 *
 * @param id Indicates the I2C device ID.
 * @param deviceAddr Indicates the I2C device address.
 * @param i2cData Indicates the pointer to the data descriptor to write.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int I2cWrite(WifiIotI2cIdx id, unsigned short deviceAddr, const WifiIotI2cData *i2cData);

/**
 * @brief Reads data from an I2C device.
 *
 * The data read will be saved to the address specified by <b>i2cData</b>.
 *
 * @param id Indicates the I2C device ID.
 * @param deviceAddr Indicates the I2C device address.
 * @param i2cData Indicates the pointer to the data descriptor to read.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int I2cRead(WifiIotI2cIdx id, unsigned short deviceAddr, const WifiIotI2cData *i2cData);

#endif
/** @} */

