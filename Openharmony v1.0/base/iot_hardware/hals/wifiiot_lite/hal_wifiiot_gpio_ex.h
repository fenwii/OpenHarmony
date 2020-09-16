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
 * @file hal_wifiiot_gpio_ex.h
 *
 * @brief Declares the extended GPIO interface functions.
 *
 * These functions are used for settings GPIO pulls and driver strength. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HAL_WIFIIOT_GPIO_EX_H
#define HAL_WIFIIOT_GPIO_EX_H

typedef enum {
    /** GPIO hardware pin 0 */
    HAL_WIFI_IOT_IO_NAME_GPIO_0,
    /** GPIO hardware pin 1 */
    HAL_WIFI_IOT_IO_NAME_GPIO_1,
    /** GPIO hardware pin 2 */
    HAL_WIFI_IOT_IO_NAME_GPIO_2,
    /** GPIO hardware pin 3 */
    HAL_WIFI_IOT_IO_NAME_GPIO_3,
    /** GPIO hardware pin 4 */
    HAL_WIFI_IOT_IO_NAME_GPIO_4,
    /** GPIO hardware pin 5 */
    HAL_WIFI_IOT_IO_NAME_GPIO_5,
    /** GPIO hardware pin 6 */
    HAL_WIFI_IOT_IO_NAME_GPIO_6,
    /** GPIO hardware pin 7 */
    HAL_WIFI_IOT_IO_NAME_GPIO_7,
    /** GPIO hardware pin 8 */
    HAL_WIFI_IOT_IO_NAME_GPIO_8,
    /** GPIO hardware pin 9 */
    HAL_WIFI_IOT_IO_NAME_GPIO_9,
    /** GPIO hardware pin 10 */
    HAL_WIFI_IOT_IO_NAME_GPIO_10,
    /** GPIO hardware pin 11 */
    HAL_WIFI_IOT_IO_NAME_GPIO_11,
    /** GPIO hardware pin 12 */
    HAL_WIFI_IOT_IO_NAME_GPIO_12,
    /** GPIO hardware pin 13 */
    HAL_WIFI_IOT_IO_NAME_GPIO_13,
    /** GPIO hardware pin 14 */
    HAL_WIFI_IOT_IO_NAME_GPIO_14,
    /** Maximum value */
    HAL_WIFI_IOT_IO_NAME_MAX,
} HalWifiIotIoName;

typedef enum {
    /** Driver strength level 0 (highest) */
    HAL_WIFI_IOT_IO_DRIVER_STRENGTH_0 = 0,
    /** Driver strength level 1 */
    HAL_WIFI_IOT_IO_DRIVER_STRENGTH_1,
    /** Driver strength level 2 */
    HAL_WIFI_IOT_IO_DRIVER_STRENGTH_2,
    /** Driver strength level 3 */
    HAL_WIFI_IOT_IO_DRIVER_STRENGTH_3,
    /** Driver strength level 4 */
    HAL_WIFI_IOT_IO_DRIVER_STRENGTH_4,
    /** Driver strength level 5 */
    HAL_WIFI_IOT_IO_DRIVER_STRENGTH_5,
    /** Driver strength level 6 */
    HAL_WIFI_IOT_IO_DRIVER_STRENGTH_6,
    /** Driver strength level 7 (lowest) */
    HAL_WIFI_IOT_IO_DRIVER_STRENGTH_7,
    /** Maximum value */
    HAL_WIFI_IOT_IO_DRIVER_STRENGTH_MAX,
} HalWifiIotIoDriverStrength;

typedef enum {
    /** No pull */
    HAL_WIFI_IOT_IO_PULL_NONE,
    /** Pull-up */
    HAL_WIFI_IOT_IO_PULL_UP,
    /** Pull-down */
    HAL_WIFI_IOT_IO_PULL_DOWN,
    /** Maximum value */
    HAL_WIFI_IOT_IO_PULL_MAX,
} HalWifiIotIoPull;

unsigned int HalIoSetPull(HalWifiIotIoName id, HalWifiIotIoPull val);

unsigned int HalIoSetFunc(HalWifiIotIoName id, unsigned char val);

unsigned int HalIoGetPull(HalWifiIotIoName id, HalWifiIotIoPull *val);

unsigned int HalIoGetFunc(HalWifiIotIoName id, unsigned char *val);

unsigned int HalIOGetDriverStrength(HalWifiIotIoName id, HalWifiIotIoDriverStrength *val);

unsigned int HalIOSetDriverStrength(HalWifiIotIoName id, HalWifiIotIoDriverStrength val);
#endif