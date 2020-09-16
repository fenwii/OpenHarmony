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
 * @file wifiiot_gpio.h
 *
 * @brief Declares the GPIO interface functions.
 *
 * These functions are used for GPIO initialization,
 * input/output settings, and level settings. \n
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef WIFIIOT_GPIO_H
#define WIFIIOT_GPIO_H

/**
 * @brief Enumerates GPIO pin IDs.
 */
typedef enum {
    /** GPIO0 */
    WIFI_IOT_GPIO_IDX_0,
    /** GPIO1 */
    WIFI_IOT_GPIO_IDX_1,
    /** GPIO2 */
    WIFI_IOT_GPIO_IDX_2,
    /** GPIO3 */
    WIFI_IOT_GPIO_IDX_3,
    /** GPIO4 */
    WIFI_IOT_GPIO_IDX_4,
    /** GPIO5 */
    WIFI_IOT_GPIO_IDX_5,
    /** GPIO6 */
    WIFI_IOT_GPIO_IDX_6,
    /** GPIO7 */
    WIFI_IOT_GPIO_IDX_7,
    /** GPIO8 */
    WIFI_IOT_GPIO_IDX_8,
    /** GPIO9 */
    WIFI_IOT_GPIO_IDX_9,
    /** GPIO10 */
    WIFI_IOT_GPIO_IDX_10,
    /** GPIO11 */
    WIFI_IOT_GPIO_IDX_11,
    /** GPIO12 */
    WIFI_IOT_GPIO_IDX_12,
    /** GPIO13 */
    WIFI_IOT_GPIO_IDX_13,
    /** GPIO14 */
    WIFI_IOT_GPIO_IDX_14,
    /** Maximum value */
    WIFI_IOT_GPIO_IDX_MAX,
} WifiIotGpioIdx;


/**
 * @brief Enumerates GPIO level values.
 */
typedef enum {
    /** Low GPIO level */
    WIFI_IOT_GPIO_VALUE0 = 0,
    /** High GPIO level */
    WIFI_IOT_GPIO_VALUE1
} WifiIotGpioValue;

/**
 * @brief Enumerates GPIO directions.
 */
typedef enum {
    /** Input */
    WIFI_IOT_GPIO_DIR_IN = 0,
    /** Output */
    WIFI_IOT_GPIO_DIR_OUT
} WifiIotGpioDir;

/**
 * @brief Enumerates GPIO interrupt trigger modes.
 */
typedef enum {
    /** Level-sensitive interrupt */
    WIFI_IOT_INT_TYPE_LEVEL = 0,
    /** Edge-sensitive interrupt */
    WIFI_IOT_INT_TYPE_EDGE
} WifiIotGpioIntType;

/**
 * @brief Enumerates I/O interrupt polarities.
 */
typedef enum {
    /** Interrupt at a low level or falling edge */
    WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW = 0,
    /** Interrupt at a high level or rising edge */
    WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH
} WifiIotGpioIntPolarity;

/**
 * @brief Indicates the GPIO interrupt callback.
 *
 */
typedef void (*GpioIsrCallbackFunc) (char *arg);

/**
 * @brief Initializes the GPIO device.
 *
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioInit(void);

/**
 * @brief Deinitializes the GPIO device.
 *
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioDeinit(void);

/**
 * @brief Sets the direction for a GPIO pin.
 *
 * @param id Indicates the GPIO pin ID.
 * @param dir Indicates the GPIO input/output direction.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioSetDir(WifiIotGpioIdx id, WifiIotGpioDir dir);

/**
 * @brief Obtains the direction for a GPIO pin.
 *
 * @param id Indicates the GPIO pin ID.
 * @param dir Indicates the pointer to the GPIO input/output direction.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioGetDir(WifiIotGpioIdx id, WifiIotGpioDir *dir);

/**
 * @brief Sets the output level value for a GPIO pin.
 *
 * @param id Indicates the GPIO pin ID.
 * @param val Indicates the output level value.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioSetOutputVal(WifiIotGpioIdx id, WifiIotGpioValue val);

/**
 * @brief Obtains the output level value of a GPIO pin.
 *
 * @param id Indicates the GPIO pin ID.
 * @param val Indicates the pointer to the output level value.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioGetOutputVal(WifiIotGpioIdx id, WifiIotGpioValue *val);

/**
 * @brief Obtains the input level value of a GPIO pin.
 *
 * @param id Indicates the GPIO pin ID.
 * @param val Indicates the pointer to the input level value.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioGetInputVal(WifiIotGpioIdx id, WifiIotGpioValue *val);

/**
 * @brief Enables the interrupt function for a GPIO pin.
 *
 * This function can be used to set the interrupt type, interrupt polarity,
 * and interrupt callback for a GPIO pin.
 *
 * @param id Indicates the GPIO pin ID.
 * @param intType Indicates the interrupt type.
 * @param intPolarity Indicates the interrupt polarity.
 * @param func Indicates the interrupt callback function.
 * @param arg Indicates the pointer to the argument used in the interrupt callback function.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioRegisterIsrFunc(WifiIotGpioIdx id, WifiIotGpioIntType intType, WifiIotGpioIntPolarity intPolarity,
                                 GpioIsrCallbackFunc func, char *arg);

/**
 * @brief Disables the interrupt function for a GPIO pin.
 *
 * @param id Indicates the GPIO pin ID.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioUnregisterIsrFunc(WifiIotGpioIdx id);

/**
 * @brief Masks the interrupt function for a GPIO pin.
 *
 * @param id Indicates the GPIO pin ID.
 * @param mask Indicates whether the interrupt function is masked.
 * The value <b>1</b> means to mask the interrupt function,
 * and <b>0</b> means not to mask the interrupt function.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioSetIsrMask(WifiIotGpioIdx id, unsigned char mask);

/**
 * @brief Sets the interrupt trigger mode of a GPIO pin.
 *
 * This function configures a GPIO pin based on the interrupt type and interrupt polarity.
 *
 * @param id Indicates the GPIO pin ID.
 * @param intType Indicates the interrupt type.
 * @param intPolarity Indicates the interrupt polarity.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int GpioSetIsrMode(WifiIotGpioIdx id, WifiIotGpioIntType intType, WifiIotGpioIntPolarity intPolarity);

#endif
/** @} */
