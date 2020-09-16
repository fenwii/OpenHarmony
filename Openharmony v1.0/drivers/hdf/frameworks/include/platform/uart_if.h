/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @addtogroup UART
 * @{
 *
 * @brief Defines standard APIs of universal asynchronous receiver/transmitter (UART) capabilities.
 *
 * You can use this module to access the UART and enable the driver to operate a UART-compliant device.
 * The functions in this module help you to obtain and release the UART device handle, read and write data,
 * obtain and set the baud rate and device attributes.
 *
 * @since 1.0
 */

/**
 * @file uart_if.h
 *
 * @brief Declares standard UART APIs.
 *
 * @since 1.0
 */

#ifndef UART_IF_H
#define UART_IF_H

#include "hdf_platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Defines basic attributes of the UART port.
 *
 * You can configure the attributes via {@link UartSetAttribute}. If the parameters are not set,
 * default attributes are used.
 *
 * @attention The UART controller determines which UART attribute parameters are supported.
 *
 * @since 1.0
 */
struct UartAttribute {
    /**
     * Data Bit | Description
     * ------------| -----------------------
     * UART_ATTR_DATABIT_8 | 8 data bits
     * UART_ATTR_DATABIT_7 | 7 data bits
     * UART_ATTR_DATABIT_6 | 6 data bits
     * UART_ATTR_DATABIT_5 | 5 data bits
    */
    unsigned int dataBits : 4;
/**
 * @brief Indicates the UART word length, which is 8 data bits per frame.
 *
 * @since 1.0
 */
#define UART_ATTR_DATABIT_8 0
/**
 * @brief Indicates the UART word length, which is 7 data bits per frame.
 *
 * @since 1.0
 */
#define UART_ATTR_DATABIT_7 1
/**
 * @brief Indicates the UART word length, which is 6 data bits per frame.
 *
 * @since 1.0
 */
#define UART_ATTR_DATABIT_6 2
/**
 * @brief Indicates the UART word length, which is 5 data bits per frame.
 *
 * @since 1.0
 */
#define UART_ATTR_DATABIT_5 3
    /**
     * Parity Bit | Description
     * ------------| -----------------------
     * UART_ATTR_PARITY_NONE | No parity bit
     * UART_ATTR_PARITY_ODD | Odd parity bit
     * UART_ATTR_PARITY_EVEN | Even parity bit
     * UART_ATTR_PARITY_MARK | <b>1</b>
     * UART_ATTR_PARITY_SPACE | <b>0</b>
     */
    unsigned int parity : 4;
/**
 * @brief Indicates that the UART device has no parity bit.
 *
 * @since 1.0
 */
#define UART_ATTR_PARITY_NONE 0
/**
 * @brief Indicates that the UART device has an odd parity bit.
 *
 * @since 1.0
 */
#define UART_ATTR_PARITY_ODD 1
/**
 * @brief Indicates that the UART device has an even parity bit.
 *
 * @since 1.0
 */
#define UART_ATTR_PARITY_EVEN 2
/**
 * @brief Indicates that the parity bit is 1.
 *
 * @since 1.0
 */
#define UART_ATTR_PARITY_MARK 3
/**
* @brief Indicates that the parity bit is 0.
 *
 * @since 1.0
 */
#define UART_ATTR_PARITY_SPACE 4
    /**
     * Stop Bit | Description
     * ------------| -----------------------
     * UART_ATTR_STOPBIT_1 | 1 stop bit
     * UART_ATTR_STOPBIT_1P5 | 1.5 stop bits
     * UART_ATTR_STOPBIT_2 | 2 stop bits
     */
    unsigned int stopBits : 4;
/**
 * @brief Indicates that the UART device has 1 stop bit.
 *
 * @since 1.0
 */
#define UART_ATTR_STOPBIT_1 0
/**
 * @brief Indicates that the UART device has 1.5 stop bits.
 *
 * @since 1.0 */
#define UART_ATTR_STOPBIT_1P5 1
/**
 * @brief Indicates that the UART device has 2 stop bits.
 *
 * @since 1.0
 */
#define UART_ATTR_STOPBIT_2 2
    /**
     * RTS | Description
     * ------------| -----------------------
     * UART_ATTR_RTS_DIS | RTS disabled
     * UART_ATTR_RTS_EN | RTS enabled
     */
    unsigned int rts : 1;
/**
* @brief Indicates that Request To Send (RTS) is disabled for the UART device.
 *
 * @since 1.0
 */
#define UART_ATTR_RTS_DIS 0
/**
 * @brief Indicates that RTS is enabled for the UART device.
 *
 * @since 1.0
 */
#define UART_ATTR_RTS_EN 1
    /**
     * CTS | Description
     * ------------| -----------------------
     * UART_ATTR_CTS_DIS | CTS disabled
     * UART_ATTR_CTS_EN | CTS enabled
     */
    unsigned int cts : 1;
/**
 * @brief Indicates that Clear To Send (CTS) is disabled for the UART device.
 *
 * @since 1.0
 */
#define UART_ATTR_CTS_DIS 0
/**
 * @brief Indicates that CTS is enabled for the UART device.
 *
 * @since 1.0
 */
#define UART_ATTR_CTS_EN 1
    /**
     * Receiver FIFO | Description
     * ------------| -----------------------
     * UART_ATTR_RX_FIFO_DIS | FIFO disabled
     * UART_ATTR_RX_FIFO_EN | FIFO enabled
     */
    unsigned int fifoRxEn : 1;
/**
 * @brief Indicates that First In First Out (FIFO) is disabled for the receiving UART.
 *
 * @since 1.0
 */
#define UART_ATTR_RX_FIFO_DIS 0
/**
 * @brief Indicates that FIFO is enabled for the receiving UART.
 *
 * @since 1.0
 */
#define UART_ATTR_RX_FIFO_EN 1
    /**
     * Transmitter FIFO | Description
     * ------------| -----------------------
     * UART_ATTR_TX_FIFO_DIS | FIFO disabled
     * UART_ATTR_TX_FIFO_EN | FIFO enabled
     */
    unsigned int fifoTxEn : 1;
/**
 * @brief Indicates that FIFO is disabled for the transmitting UART.
 *
 * @since 1.0
 */
#define UART_ATTR_TX_FIFO_DIS 0
/**
 * @brief Indicates that FIFO is enabled for the transmitting UART.
 *
 * @since 1.0
 */
#define UART_ATTR_TX_FIFO_EN 1
    /** Reserved bits */
    unsigned int reserved : 16;
};

/**
 * @brief Enumerates UART transmission modes.
 *
 * @attention The UART controller determines whether an enumerated transmission mode is supported.
 *
 * @since 1.0
 */
enum UartTransMode {
    UART_MODE_RD_BLOCK = 0,  /**< Blocking mode */
    UART_MODE_RD_NONBLOCK,   /**< Non-blocking mode */
    UART_MODE_DMA_RX_EN,     /**< DMA enabled for data receiving */
    UART_MODE_DMA_RX_DIS,    /**< DMA disabled for data receiving */
    UART_MODE_DMA_TX_EN,     /**< DMA enabled for data transmitting */
    UART_MODE_DMA_TX_DIS,    /**< DMA disabled for data transmitting */
};

/**
 * @brief Obtains the UART device handle.
 *
 * Before accessing the UART device, you must call this function to obtain the UART device handle.
 *
 * @param port Indicates the UART port.
 *
 * @return Returns the pointer to the UART device handle if the handle is obtained; returns <b>NULL</b> otherwise.
 * @since 1.0
 */
struct DevHandle *UartOpen(uint32_t port);

/**
 * @brief Releases the UART device handle.
 *
 * If you no longer need to access the UART device, you should call this function to close its handle so as to
 * release unused memory resources.
 *
 * @param handle Indicates the pointer to the UART device handle, which is obtained via {@link UartOpen}.
 *
 * @since 1.0
 */
void UartClose(struct DevHandle *handle);

/**
 * @brief Reads data of a specified size from a UART device.
 *
 * @param handle Indicates the pointer to the UART device handle, which is obtained via {@link UartOpen}.
 * @param data Indicates the pointer to the buffer for receiving the data.
 * @param size Indicates the size of the data to read.
 *
 * @return Returns the size of the data that is successfully read; returns a negative number if the reading fails.
 * @since 1.0
 */
int32_t UartRead(struct DevHandle *handle, uint8_t *data, uint32_t size);

/**
 * @brief Writes data of a specified size into a UART device.
 *
 * @param handle Indicates the pointer to the UART device handle, which is obtained via {@link UartOpen}.
 * @param data Indicates the pointer to the data to write.
 * @param size Indicates the size of the data to write.
 *
 * @return Returns <b>0</b> if the data is successfully written; returns a negative number otherwise.
 * @since 1.0
 */
int32_t UartWrite(struct DevHandle *handle, uint8_t *data, uint32_t size);

/**
 * @brief Obtains the baud rate of the UART device.
 *
 * @param handle Indicates the pointer to the UART device handle, which is obtained via {@link UartOpen}.
 * @param baudRate Indicates the pointer to the obtained baud rate.
 *
 * @return Returns <b>0</b> if the baud rate is obtained; returns a negative number otherwise.
 * @since 1.0
 */
int32_t UartGetBaud(struct DevHandle *handle, uint32_t *baudRate);

/**
 * @brief Sets the baud rate for the UART device.
 *
 * @param handle Indicates the pointer to the UART device handle, which is obtained via {@link UartOpen}.
 * @param baudRate Indicates the baud rate to set.
 *
 * @return Returns <b>0</b> if the setting is successful; returns a negative number otherwise.
 * @since 1.0
 */
int32_t UartSetBaud(struct DevHandle *handle, uint32_t baudRate);

/**
 * @brief Obtains the UART attribute.
 *
 * UART attributes include data bits, stop bits, parity bit, CTS, RTS, and receiving and transmitting FIFO.
 *
 * @param handle Indicates the pointer to the UART device handle, which is obtained via {@link UartOpen}.
 * @param attribute Indicates the pointer to the obtained UART attribute.
 *
 * @return Returns <b>0</b> if the UART attribute is obtained; returns a negative number otherwise.
 * @since 1.0 */
int32_t UartGetAttribute(struct DevHandle *handle, struct UartAttribute *attribute);

/**
 * @brief Sets the UART attribute.
 *
 * UART attributes include data bits, stop bits, parity bit, CTS, RTS, and receiving and transmitting FIFO.
 *
 * @param handle Indicates the pointer to the UART device handle, which is obtained via {@link UartOpen}.
 * @param attribute Indicates the pointer to the UART attribute to set.
 *
 * @return Returns <b>0</b> if the setting is successful; returns a negative number otherwise.
 * @since 1.0
 */
int32_t UartSetAttribute(struct DevHandle *handle, struct UartAttribute *attribute);

/**
 * @brief Sets the UART transmission mode.
 *
 * @param handle Indicates the pointer to the UART device handle, which is obtained via {@link UartOpen}.
 * @param mode Indicates a transmission mode enumerated in {@linkUartTransMode}.
 *
 * @return Returns <b>0</b> if the setting is successful; returns a negative number otherwise.
 * @since 1.0
 */
int32_t UartSetTransMode(struct DevHandle *handle, enum UartTransMode mode);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* PAL_UART_IF_H */
/** @} */
