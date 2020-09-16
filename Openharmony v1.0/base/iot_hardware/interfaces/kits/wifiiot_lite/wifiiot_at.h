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
 * @file wifiiot_at.h
 *
 * @brief Declares the AT interface functions.
 *
 * These functions are used for AT initialization as well as command line registration and printing. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef WIFIIOT_AT_H
#define WIFIIOT_AT_H

typedef unsigned int (*AtCallbackFunc)(int argc, const char **argv);

/**
 * @brief Defines the AT command registration structure.
 *
 *
 *
 */
typedef struct {
    /** AT command name */
    char *atCmdName;
    /** AT command length */
    char  atCmdLen;
    /** AT test command */
    AtCallbackFunc atTestCmd;
    /** AT command query */
    AtCallbackFunc atQueryCmd;
    /** AT command setup */
    AtCallbackFunc atSetupCmd;
    /** AT command execution */
    AtCallbackFunc atExeCmd;
} AtCmdTbl;

/**
 * @brief Registers a certain number of AT commands.
 *
 *
 *
 * @param cmdTbl Indicates the command table.
 * @param cmdNum Indicates the number of AT commands in the command table.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 *         returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int AtRegisterCmd(const AtCmdTbl *cmdTbl, unsigned short cmdNum);

/**
 * @brief Registers a system AT command.
 *
 * For example, you can use this function to register the AT+RST command,
 * which is a system AT command used to reset a device.
 *
 * @since 1.0
 * @version 1.0
 */
void AtSysCmdRegister(void);

/**
 * @brief Formats data and outputs it to the AT command terminal.
 *
 * @param fmt Indicates the pointer to the control character string to format.
 * @param ... Represents a variable parameter list in the character string format.
 * @return Returns the number of bytes (excluding the end character) output to
 * the AT command terminal if the operation is successful;
 *         returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int AtPrintf(const char *fmt, ...);

/**
 * @brief Initializes an AT command task.
 *
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 *         returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int AtInit(void);

/**
 * @brief Sets whether to check the UART busy status during low-power voting.
 *
 * This function determines whether to check the UART status before the device enters the low-power mode.
 * If <b>enable</b> is set to <b>1</b> and the UART is found to be busy,
 * the device does not enter the low-power mode.
 * In other scenarios, the device enters the low-power mode.
 *
 * @param enable Specifies whether to check the UART busy status.
 *        The value <b>1</b> means to check the UART busy status,
 *        and <b>0</b> means not to check the busy status.
 * @since 1.0
 * @version 1.0
 */
void AtCheckUartBusy(unsigned char enable);

#endif
/** @} */
