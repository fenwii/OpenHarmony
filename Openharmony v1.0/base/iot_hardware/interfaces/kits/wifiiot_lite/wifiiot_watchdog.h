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
 * @file wifiiot_watchdog.h
 *
 * @brief Declares the watchdog interface functions.
 *
 * These functions are used to enable, disable, and feed the watchdog. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef WIFIIOT_WATCHDOG_H
#define WIFIIOT_WATCHDOG_H

/**
 * @brief Enables the watchdog.
 *
 * @since 1.0
 * @version 1.0
 */
void WatchDogEnable(void);

/**
 * @brief Feeds the watchdog.
 *
 * @since 1.0
 * @version 1.0
 */
void WatchDogKick(void);

/**
 * @brief Disables the watchdog.
 *
 * @since 1.0
 * @version 1.0
 */
void WatchDogDisable(void);

#endif
/** @} */
