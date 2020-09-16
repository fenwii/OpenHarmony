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
 * @file hal_wifiiot_kal.h
 *
 * @brief Declares the KAL interface functions.
 *
 * These functions are used to register the idle task and CPU tick callbacks. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HAL_WIFIIOT_KAL_H
#define HAL_WIFIIOT_KAL_H

/**
 * @brief Indicates the idle task and CPU tick callbacks.
 *
 */
typedef void (*HalTickIdleKalCallback)(void);

/**
 * @brief Registers the CPU tick callback.
 *
 * @param cb Indicates the CPU tick callback to register.
 * @since 1.0
 * @version 1.0
 */
void HalKalTickRegisterCallback(HalTickIdleKalCallback cb);

/**
 * @brief Registers the idle task callback.
 *
 * @param cb Indicates the idle task callback to register.
 * @since 1.0
 * @version 1.0
 */
void HalKalThreadRegisterIdleCallback(HalTickIdleKalCallback cb);

#endif
/** @} */
