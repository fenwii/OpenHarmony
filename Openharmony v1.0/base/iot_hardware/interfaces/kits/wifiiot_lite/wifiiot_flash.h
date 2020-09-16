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
 * @file wifiiot_flash.h
 *
 * @brief Declares the flash interface functions.
 *
 * These functions are used to initialize or deinitialize a flash device,
 * and read data from or write data to a flash memory. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef WIFIIOT_FLASH_H
#define WIFIIOT_FLASH_H

/**
 * @brief Reads data from a flash memory address.
 *
 * This function reads a specified length of data from a specified flash memory address.
 *
 * @param flashOffset Indicates the address of the flash memory from which data is to read.
 * @param size Indicates the length of the data to read.
 * @param ramData Indicates the pointer to the RAM for storing the read data.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 *         returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int FlashRead(const unsigned int flashOffset, const unsigned int size, unsigned char *ramData);

/**
 * @brief Writes data to a flash memory address.
 *
 * This function writes a specified length of data to a specified flash memory address.
 *
 * @param flashOffset Indicates the address of the flash memory to which data is to write.
 * @param size Indicates the length of the data to write.
 * @param ramData Indicates the pointer to the RAM for storing the data to write.
 * @param doErase Indicates whether to automatically erase and overwrite the data.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 *         returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int FlashWrite(const unsigned int flashOffset, unsigned int size,
                        const unsigned char *ramData, unsigned char doErase);

/**
 * @brief Erases data in a specified flash memory address.
 *
 * @param flashOffset Indicates the address of the flash memory data to erase.
 * @param size Indicates the length of the data to erase, in bytes. The value must be a multiple of 4000 bytes.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 *         returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int FlashErase(const unsigned int flashOffset, const unsigned int size);

/**
 * @brief Initializes the flash device.
 *
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 *         returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int FlashInit(void);

/**
 * @brief Deinitializes the flash device.
 *
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 *         returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int FlashDeinit(void);

#endif
/** @} */
