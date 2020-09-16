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
 * @file hal_wifiiot_uart.h
 *
 * @brief Declares the UART interface functions.
 *
 * These functions are used for UART initialization,
 * data input/output, and data flow control. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef HAL_WIFIIOT_UART_H
#define HAL_WIFIIOT_UART_H

typedef void (*HalUartRecvCallback)(char *);
/**
 * @brief Enumerates the UART serial number.
 */
typedef enum {
    /** Physical port 0 */
    HAL_WIFI_IOT_UART_IDX_0,
    /** Physical port 1 */
    HAL_WIFI_IOT_UART_IDX_1,
    /** Physical port 2 */
    HAL_WIFI_IOT_UART_IDX_2,
    /** Maximum value */
    HAL_WIFI_IOT_UART_IDX_MAX
}HalWifiIotUartIdx;

/**
 * @brief Enumerates the number of UART data bits.
 */
typedef enum {
    /** 5 data bits */
    HAL_WIFI_IOT_UART_DATA_BIT_5 = 5,
    /** 6 data bits */
    HAL_WIFI_IOT_UART_DATA_BIT_6,
    /** 7 data bits */
    HAL_WIFI_IOT_UART_DATA_BIT_7,
    /** 8 data bits */
    HAL_WIFI_IOT_UART_DATA_BIT_8,
} HalWifiIotUartIdxDataBit;

/**
 * @brief Enumerates the number of UART stop bits.
 */
typedef enum {
    /** 1 stop bit */
    HAL_WIFI_IOT_UART_STOP_BIT_1 = 1,
    /** 2 stop bit */
    HAL_WIFI_IOT_UART_STOP_BIT_2 = 2,
} HalWifiIotUartStopBit;

/**
 * @brief Enumerates the UART parity bit.
 */
typedef enum {
    /** No parity */
    HAL_WIFI_IOT_UART_PARITY_NONE = 0,
    /** Odd parity */
    HAL_WIFI_IOT_UART_PARITY_ODD = 1,
    /** Even parity */
    HAL_WIFI_IOT_UART_PARITY_EVEN = 2,
} HalWifiIotUartParity;

/**
 * @brief Enumerates UART FIFO interrupt thresholds.
 */
typedef enum {
    /** FIFO = 1/8 full */
    HAL_WIFI_IOT_FIFO_LINE_ONE_EIGHT = 1,
    /** FIFO = 1/4 full */
    HAL_WIFI_IOT_FIFO_LINE_ONE_QUARTER,
    /** FIFO = 1/2 full */
    HAL_WIFI_IOT_FIFO_LINE_HALF,
    /** FIFO = 3/4 full */
    HAL_WIFI_IOT_FIFO_LINE_THREE_QUARTERS,
    /** FIFO = 7/8 full */
    HAL_WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS,
} HalWifiIotUartFifoLine;

/**
 * @brief Enumerates UART block states.
 */
typedef enum {
    /** Block disabled */
    HAL_WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK = 1,
    /** Block enabled */
    HAL_WIFI_IOT_UART_BLOCK_STATE_BLOCK,
} HalWifiIotUartBlockState;

/**
 * @brief Enumerates UART DMA states.
 */
typedef enum {
    /** DMA disabled */
    HAL_WIFI_IOT_UART_NONE_DMA = 1,
    /** DMA enabled */
    HAL_WIFI_IOT_UART_USE_DMA,
} HalWifiIotUartDmaState;

/**
 * @brief Enumerates hardware flow control modes.
 */
typedef enum {
    /** Hardware flow control disabled */
    HAL_WIFI_IOT_FLOW_CTRL_NONE,
    /** RTS and CTS hardware flow control enabled */
    HAL_WIFI_IOT_FLOW_CTRL_RTS_CTS,
    /** RTS hardware flow control enabled */
    HAL_WIFI_IOT_FLOW_CTRL_RTS_ONLY,
    /** RTS hardware flow control enabled */
    HAL_WIFI_IOT_FLOW_CTRL_CTS_ONLY,
} HalWifiIotFlowCtrl;

/**
 * @brief Defines the basic attributes of a UART device.
 */
typedef struct {
    /** Baud rate */
    unsigned int baudRate;
    /** Data bits.
     * The value range is specified in {@link WifiIotUartIdxDataBit}.
     */
    unsigned char  dataBits;
    /** Stop bits.
     * The value range is specified in {@link WifiIotUartStopBit}.
     */
    unsigned char  stopBits;
    /** Parity bit. The value range is specified in {@link WifiIotUartParity}. */
    unsigned char  parity;
    /** Padding bit */
    unsigned char  pad;
} HalWifiIotUartAttribute;

/**
 * @brief Defines the extended attributes of a UART device.
 */
typedef struct {
    /** Tx FIFO interrupt threshold */
    HalWifiIotUartFifoLine txFifoLine;
    /** Rx FIFO interrupt threshold */
    HalWifiIotUartFifoLine rxFifoLine;
    /** FIFO interrupt threshold for flow control */
    HalWifiIotUartFifoLine flowFifoLine;
    /** Tx block state */
    HalWifiIotUartBlockState txBlock;
    /** Rx block state */
    HalWifiIotUartBlockState rxBlock;
    /** Tx buffer size */
    unsigned short  txBufSize;
    /** Rx buffer size */
    unsigned short  rxBufSize;
    /** Whether DMA is used to send data */
    HalWifiIotUartDmaState txUseDma;
    /** Whether DMA is used to receive data */
    HalWifiIotUartDmaState rxUseDma;
} HalWifiIotUartExtraAttr;

/**
 * @brief Configures a UART device.
 *
 * This function configures a UART device
 * with the port number specified by <b>id</b> based on the basic and extended attributes.
 *
 * @param id Indicates the UART port number.
 * @param param Indicates the pointer to the basic UART attributes.
 * @param extraAttr Indicates the pointer to the extended UART attributes.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalUartInit(HalWifiIotUartIdx id, const HalWifiIotUartAttribute *param,
                         const HalWifiIotUartExtraAttr *extraAttr);

/**
 * @brief Reads data from a UART device.
 *
 * This function reads a specified length of data from a UART device
 * with the port number specified by <b>id</b>.
 *
 * @param id Indicates the UART port number.
 * @param data Indicates the pointer to the start address of the data to read.
 * @param dataLen Indicates the number of bytes to read.
 * @return Returns the number of bytes read if the operation is successful;
 * returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int HalUartRead(HalWifiIotUartIdx id, unsigned char *data, unsigned int dataLen);

/**
 * @brief Writes data to a UART device.
 *
 * This function writes a specified length of data to a UART device
 * with the port number specified by <b>id</b>.
 *
 * @param id Indicates the UART port number.
 * @param data Indicates the pointer to the start address of the data to write.
 * @param dataLen Indicates the number of bytes to write.
 * @return Returns the number of bytes written if the operation is successful;
 * returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int HalUartWrite(HalWifiIotUartIdx id, const unsigned char *data, unsigned int dataLen);

/**
 * @brief Deinitializes a UART device.
 *
 * @param id Indicates the UART port number.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalUartDeinit(HalWifiIotUartIdx id);

/**
 * @brief Sets UART hardware flow control.
 *
 * This function configures flow control for a UART device
 * with the port number specified by <b>id</b>.
 *
 * @param id Indicates the UART port number.
 * @param flowCtrl Indicates the parameter used for hardware flow control.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int HalUartSetFlowCtrl(HalWifiIotUartIdx id, HalWifiIotFlowCtrl flowCtrl);

#endif
/** @} */
