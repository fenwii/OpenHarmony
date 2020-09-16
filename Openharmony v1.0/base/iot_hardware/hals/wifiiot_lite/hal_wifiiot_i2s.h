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
 * @file hal_wifiiot_i2s.h
 *
 * @brief Declares the I2S interface functions.
 *
 * These functions are used for I2S initialization and data transmission. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HAL_WIFIIOT_I2S_H
#define HAL_WIFIIOT_I2S_H

/**
 * @brief Enumerates I2S sampling rates.
 */
typedef enum {
    /** 8K sampling rate */
    HAL_WIFI_IOT_I2S_SAMPLE_RATE_8K = 8,
    /** 16K sampling rate */
    HAL_WIFI_IOT_I2S_SAMPLE_RATE_16K = 16,
    /** 32K sampling rate */
    HAL_WIFI_IOT_I2S_SAMPLE_RATE_32K = 32,
    /** 48K sampling rate */
    HAL_WIFI_IOT_I2S_SAMPLE_RATE_48K = 48,
} HalWifiIotI2sSampleRate;

/**
 * @brief Enumerates I2S resolution.
 */
typedef enum {
    /** 16-bit resolution */
    HAL_WIFI_IOT_I2S_RESOLUTION_16BIT = 16,
    /** 24-bit resolution */
    HAL_WIFI_IOT_I2S_RESOLUTION_24BIT = 24,
} HalWifiIotI2sResolution;

/**
 * @brief Defines I2S attributes.
 */
typedef struct {
    /** Sampling rate */
    HalWifiIotI2sSampleRate sampleRate;
    /** Resolution */
    HalWifiIotI2sResolution resolution;
} HalWifiIotI2sAttribute;

/**
 * @brief Initializes the I2S device.
 *
 *
 *
 * @param i2sAttribute Indicates the pointer to the I2S configuration parameter.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalI2sInit(const HalWifiIotI2sAttribute *i2sAttribute);

/**
 * @brief Deinitializes the I2S device.
 *
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalI2sDeinit(void);

/**
 * @brief Writes data to the I2S device.
 *
 * This function writes data with the length specified by <b>wrLen</b> to
 * an I2S device within the duration specified by <b>timeOutMs</b>.
 *
 * @param wrData Indicates the pointer to the data to write.
 * @param wrLen Indicates the length of the data to write.
 * @param timeOutMs Indicates the timeout interval.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalI2sWrite(unsigned char *wrData, unsigned int wrLen, unsigned int timeOutMs);

/**
 * @brief Reads data from the I2S device.
 *
 * This function reads data with the length specified by <b>rdLen</b>
 * from an I2S device within the duration specified by <b>timeOutMs</b>.
 *
 * @param rdData Indicates the pointer to the data to read.
 * @param rdLen Indicates the length of the data to read.
 * @param timeOutMs Indicates the timeout interval.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalI2sRead(unsigned char *rdData, unsigned int rdLen, unsigned int timeOutMs);

#endif
/** @} */
