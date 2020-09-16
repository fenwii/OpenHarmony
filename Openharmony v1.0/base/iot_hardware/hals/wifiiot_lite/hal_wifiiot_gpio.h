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
 * @file hal_wifiiot_gpio.h
 *
 * @brief Declares the GPIO interface functions.
 *
 * These functions are used for GPIO initialization,
 * input/output settings, and level settings. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HAL_WIFIIOT_GPIO_H
#define HAL_WIFIIOT_GPIO_H

typedef enum {
    /** GPIO0 */
    HAL_WIFI_IOT_GPIO_IDX_0,
    /** GPIO1 */
    HAL_WIFI_IOT_GPIO_IDX_1,
    /** GPIO2 */
    HAL_WIFI_IOT_GPIO_IDX_2,
    /** GPIO3 */
    HAL_WIFI_IOT_GPIO_IDX_3,
    /** GPIO4 */
    HAL_WIFI_IOT_GPIO_IDX_4,
    /** GPIO5 */
    HAL_WIFI_IOT_GPIO_IDX_5,
    /** GPIO6 */
    HAL_WIFI_IOT_GPIO_IDX_6,
    /** GPIO7 */
    HAL_WIFI_IOT_GPIO_IDX_7,
    /** GPIO8 */
    HAL_WIFI_IOT_GPIO_IDX_8,
    /** GPIO9 */
    HAL_WIFI_IOT_GPIO_IDX_9,
    /** GPIO10 */
    HAL_WIFI_IOT_GPIO_IDX_10,
    /** GPIO11 */
    HAL_WIFI_IOT_GPIO_IDX_11,
    /** GPIO12 */
    HAL_WIFI_IOT_GPIO_IDX_12,
    /** GPIO13 */
    HAL_WIFI_IOT_GPIO_IDX_13,
    /** GPIO14 */
    HAL_WIFI_IOT_GPIO_IDX_14,
    /** Maximum value */
    HAL_WIFI_IOT_GPIO_IDX_MAX,
} HalWifiIotGpioIdx;

typedef enum {
    /** Low GPIO level */
    HAL_WIFI_IOT_GPIO_VALUE0 = 0,
    /** High GPIO level */
    HAL_WIFI_IOT_GPIO_VALUE1
} HalWifiIotGpioValue;


typedef enum {
    /** Input */
    HAL_WIFI_IOT_GPIO_DIR_IN = 0,
    /** Output */
    HAL_WIFI_IOT_GPIO_DIR_OUT
} HalWifiIotGpioDir;

typedef enum {
    /** Level-sensitive interrupt */
    HAL_WIFI_IOT_INT_TYPE_LEVEL = 0,
    /** Edge-sensitive interrupt */
    HAL_WIFI_IOT_INT_TYPE_EDGE
} HalWifiIotGpioIntType;

typedef enum {
    /** Interrupt at a low level or falling edge */
    HAL_WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW = 0,
    /** Interrupt at a high level or rising edge */
    HAL_WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH
} HalWifiIotGpioIntPolarity;


typedef void (*HalGpioIsrCallbackFunc) (char *arg);

unsigned int HalGpioInit(void);

unsigned int HalGpioDeinit(void);

unsigned int HalGpioSetDir(HalWifiIotGpioIdx id, HalWifiIotGpioDir dir);

unsigned int HalGpioGetDir(HalWifiIotGpioIdx id, HalWifiIotGpioDir *dir);

unsigned int HalGpioSetOutputVal(HalWifiIotGpioIdx id, HalWifiIotGpioValue val);

unsigned int HalGpioGetOutputVal(HalWifiIotGpioIdx id, HalWifiIotGpioValue *val);

unsigned int HalGpioGetInputVal(HalWifiIotGpioIdx id, HalWifiIotGpioValue *val);

unsigned int HalGpioRegisterIsrFunc(HalWifiIotGpioIdx id, HalWifiIotGpioIntType intType,
                                    HalWifiIotGpioIntPolarity intPolarity, HalGpioIsrCallbackFunc func, char *arg);

unsigned int HalGpioUnregisterIsrFunc(HalWifiIotGpioIdx id);

unsigned int HalGpioSetIsrMask(HalWifiIotGpioIdx id, unsigned char mask);

unsigned int HalGpioSetIsrMode(HalWifiIotGpioIdx id, HalWifiIotGpioIntType intType,
                               HalWifiIotGpioIntPolarity intPolarity);

#endif
