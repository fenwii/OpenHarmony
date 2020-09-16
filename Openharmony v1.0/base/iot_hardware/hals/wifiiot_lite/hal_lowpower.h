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
 * @addtogroup power
 * @{
 *
 * @brief Provides device power management functions.
 *
 * This module is used to reboot the device and set low power consumption for the device. \n
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file hal_lowpower.h
 *
 * @brief Sets low power consumption for the device.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HAL_LOWPOWER_H
#define HAL_LOWPOWER_H

/**
 * @brief Enumerates low power consumption modes.
 */
typedef enum {
    /** No sleep */
    HAL_NO_SLEEP,
    /** Light sleep */
    HAL_LIGHT_SLEEP,
    /** Deep sleep */
    HAL_DEEP_SLEEP,
}HalLpcType;

/**
 * @brief Initializes low power consumption.
 *
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 *         Returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalLpcInit(void);

/**
 * @brief Sets low power consumption for the device.
 *
 * @param type Indicates the low power consumption mode to set.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 *         Returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalLpcSetType(HalLpcType type);

#endif
