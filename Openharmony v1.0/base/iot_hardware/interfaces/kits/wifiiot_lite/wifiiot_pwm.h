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
 * @file wifiiot_pwm.h
 *
 * @brief Declares the PWM interface functions.
 *
 * These functions are used for PWM initialization, deinitialization, and signal output. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef WIFIIOT_PWM_H
#define WIFIIOT_PWM_H

/**
 * @brief Enumerates PWM clock sources.
 */
typedef enum {
    /** 160 MHz working clock */
    WIFI_IOT_PWM_CLK_160M,
    /** 24 MHz or 40 MHz external crystal */
    WIFI_IOT_PWM_CLK_XTAL,
    /** Maximum value */
    WIFI_IOT_PWM_CLK_MAX
} WifiIotPwmClkSource;

/**
 * @brief Enumerates PWM ports.
 */
typedef enum {
    /** PWM0 */
    WIFI_IOT_PWM_PORT_PWM0 = 0,
    /** PWM1 */
    WIFI_IOT_PWM_PORT_PWM1 = 1,
    /** PWM2 */
    WIFI_IOT_PWM_PORT_PWM2 = 2,
    /** PWM3 */
    WIFI_IOT_PWM_PORT_PWM3 = 3,
    /** PWM4 */
    WIFI_IOT_PWM_PORT_PWM4 = 4,
    /** PWM5 */
    WIFI_IOT_PWM_PORT_PWM5 = 5,
    /** Maximum value */
    WIFI_IOT_PWM_PORT_MAX
} WifiIotPwmPort;

/**
 * @brief Initializes a PWM device.
 *
 * @param port Indicates the PWM port number.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int PwmInit(WifiIotPwmPort port);

/**
 * @brief Deinitializes a PWM device.
 *
 * @param port Indicates the PWM port number.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * eturns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int PwmDeinit(WifiIotPwmPort port);

/**
 * @brief Outputs PWM signals based on the input parameters.
 *
 * This function outputs PWM signals from a specified port based on
 * the configured frequency division multiple and duty cycle.
 *
 * @param port Indicates the PWM port number.
 * @param duty Indicates the PWM duty cycle.
 * @param freq Indicates the frequency-division multiple.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int PwmStart(WifiIotPwmPort port, unsigned short duty, unsigned short freq);

/**
 * @brief Stops the PWM signal output.
 *
 * @param port Indicates the PWM port number.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int PwmStop(WifiIotPwmPort port);

#endif
/** @} */
