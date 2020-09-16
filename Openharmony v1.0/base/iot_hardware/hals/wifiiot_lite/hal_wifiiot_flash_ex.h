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
 * @file hal_wifiiot_flash_ex.h
 *
 * @brief Declares the extended flash interface functions
 * for obtaining flash information.
 *
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HAL_WIFIIOT_FLASH_EX_H
#define HAL_WIFIIOT_FLASH_EX_H

/**
 * @brief Obtains flash information based on a specific command.
 *
 *
 *
 * @param cmd Indicates the command ID.
 * The value <b>0</b> indicates an attempt to obtain flash partition information,
 * and <b>1</b> indicates an attempt to obtain the flash busy status.
 * @param data Indicates the pointer to the memory
 * where the obtained information will be saved.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the flash information is obtained;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalFlashIoctl(unsigned short cmd, char *data);

#endif
/** @} */
