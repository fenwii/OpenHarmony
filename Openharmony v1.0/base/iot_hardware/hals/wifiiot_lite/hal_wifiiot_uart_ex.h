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
 * @file hal_wifiiot_uart_ex.h
 *
 * @brief Declares the extended UART interface functions.
 *
 * These functions are used to obtain UART attributes and check the busy status. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HAL_WIFIIOT_UART_EX_H
#define HAL_WIFIIOT_UART_EX_H

/**
 * @brief Checks whether the buffer on a UART device is empty.
 *
 * The query result will be stored in <b>empty</b>.
 *
 * @param id Indicates the UART port number.
 * @param empty Indicates the pointer to the address whether the query result is to be stored.
 * If the buffer is empty, the query result is <b>1</b>.
 * If the buffer is not empty, the query result is <b>0</b>.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalUartIsBufEmpty(HalWifiIotUartIdx id, unsigned char *empty);


/**
 * @brief Writes data to be sent to a UART device in polling mode.
 *
 *
 *
 * @param id Indicates the UART port number.
 * @param data Indicates the pointer to the start address of the data to write.
 * @param dataLen Indicates the number of bytes to write.
 * @return Returns the number of bytes written if the operation is successful;
 * returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int HalUartWriteImmediately(HalWifiIotUartIdx id, const unsigned char *data, unsigned int dataLen);

/**
 * @brief Obtains UART attributes.
 *
 * This function obtains the basic and extended attributes of a UART device.
 *
 * @param id Indicates the UART port number.
 * @param attr Indicates the pointer to the basic UART attributes.
 * @param extraAttr Indicates the pointer to the extended UART attributes.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalUartGetAttribute(HalWifiIotUartIdx id, HalWifiIotUartAttribute *attr,
                                 HalWifiIotUartExtraAttr *extraAttr);

/**
 * @brief Checks whether the buffer on a UART device is busy.
 *
 * The query result will be stored in <b>busy</b>.
 *
 * @param id Indicates the UART port number.
 * @param busy Indicates the pointer to the address whether the query result is to be stored.
 * If the buffer is busy, the query result is <b>1</b>.
 * If the buffer is not busy, the query result is <b>0</b>.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalUartIsBusy(HalWifiIotUartIdx id, unsigned char *busy);

#endif
/** @} */
