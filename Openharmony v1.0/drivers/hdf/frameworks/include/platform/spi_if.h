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
 * @addtogroup SPI
 * @{
 *
 * @brief Defines standard APIs of the Serial Peripheral Interface (SPI) capabilities.
 *
 * The SPI module abstracts the SPI capabilities of different system platforms to provide stable APIs
 * for driver development.
 * This module can create and destroy SPI device handles, read and write SPI data,
 * and obtain and set configuration parameters.
 *
 * @since 1.0
 */

/**
 * @file spi_if.h
 *
 * @brief Defines standard SPI-specific interfaces for driver development.
 *
 * A driver needs to use the SPI-specific interfaces for data writing and reading
 * before performing any operations on an SPI-compliant device.
 *
 * @since 1.0
 */

#ifndef SPI_IF_H
#define SPI_IF_H

#include "hdf_platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Indicates the SPI clock phase. The value <b>0</b> indicates that data will be sampled on the first clock edge,
 * and <b>1</b> indicates that data will be sampled on the second clock edge.
 *
 * @since 1.0
 */
#define SPI_CLK_PHASE            (1 << 0)
/**
 * @brief Indicates the SPI clock polarity. The value <b>0</b> indicates a low-level clock signal in the idle state,
 * and <b>1</b> indicates a high-level clock signal in the idle state.
 *
 * @since 1.0
 */
#define SPI_CLK_POLARITY         (1 << 1)
/**
 * @brief Indicates that a single data line is used for both input and output.
 *
 * @since 1.0
 */
#define SPI_MODE_3WIRE           (1 << 2)
/**
 * @brief Indicates the SPI loopback mode.
 *
 * @since 1.0
 */
#define SPI_MODE_LOOP            (1 << 3)
/**
 * @brief Indicates the SPI data transfer order. The value <b>0</b> indicates that data is transferred from the most
 * significant bit (MSB) to the least significant bit (LSB), and <b>1</b> indicates the opposite.
 *
 * @since 1.0
 */
#define SPI_MODE_LSBFE           (1 << 4)
/**
 * @brief Indicates that there is only one SPI device, and no chip select (CS) is required.
 *
 * @since 1.0
 */
#define SPI_MODE_NOCS            (1 << 5)
/**
 * @brief Indicates that the CS level is high when an SPI device is selected.
 *
 * @since 1.0
 */
#define SPI_MODE_CS_HIGH         (1 << 6)
/**
 * @brief Indicates that the SPI device is set to low for pausing data transfer.
 *
 * @since 1.0
 */
#define SPI_MODE_READY           (1 << 7)

/**
 * @brief Enumerates transfer modes of SPI data.
 *
 * @attention The specific SPI controller determines which variables in this structure are supported.
 *
 * @since 1.0
 */
enum SpiTransferMode {
    SPI_INTERRUPT_TRANSFER = 0, /**< Interrupt transfer mode */
    SPI_POLLING_TRANSFER,       /**< Polling transfer mode */
    SPI_DMA_TRANSFER,           /**< Direct Memory Access (DMA) transfer mode */
};

/**
 * @brief Defines the general SPI device descriptor, which can be used as the unique identifier of an SPI device.
 * When operating an SPI device, you need to specify a descriptor of the {@link SpiDevInfo} type, and obtain the
 * handle of the SPI device by calling {@link SpiOpen}.
 *
 * @since 1.0
 */
struct SpiDevInfo {
    uint32_t busNum;       /**< SPI bus number */
    uint32_t csNum;        /**< SPI device chip select (CS) */
};

/**
 * @brief Defines the custom SPI transfer message.
 *
 * @attention The specific SPI controller determines whether <b>speed</b>, <b>delayUs</b>,
 * and <b>csChange</b> are supported.
 *
 * @since 1.0
 */
struct SpiMsg {
    uint8_t *wbuf;       /**< Address of the write buffer */
    uint8_t *rbuf;       /**< Address of the read buffer */
    uint32_t len;        /**< Length of the read and write buffers. The read buffer and the write
                          * buffer have the same length.
                          */
    uint32_t speed;      /**< Current message transfer speed */
    uint16_t delayUs;    /**< Delay (in microseconds) before starting the next transfer.
                          * The value <b>0</b> indicates there is no delay between transfers.
                          */
    uint8_t csChange;    /**< Whether to switch off the CS before the next transfer when the current transfer has been
                          * completed. <b>1</b> indicates to switch off the CS; <b>0</b> indicates to switch on the CS.
                          */
};

/**
 * @brief Defines the configuration of an SPI device.
 *
 * @attention The specific SPI controller determines which variables in this structure are supported.
 *
 * @since 1.0
 */
struct SpiCfg {
    uint32_t maxSpeedHz;     /**< Maximum clock frequency */
    uint16_t mode;           /**< Input and output mode of SPI data | Description
                              * -----------------| -----------------------
                              * SPI_CLK_PHASE    | SPI clock phase.
                              * SPI_CLK_POLARITY | SPI clock polarity.
                              * SPI_MODE_3WIRE   | A single data line is used for both input and output.
                              * SPI_MODE_LOOP    | SPI loopback mode.
                              * SPI_MODE_LSBFE   | SPI data transfer order
                              * SPI_MODE_NOCS    | There is only one SPI device, and no CS is required.
                              * SPI_MODE_CS_HIGH | The CS level is high when an SPI device is selected.
                              * SPI_MODE_READY   | The SPI device is set to low for pausing data transfer.
                              */
    uint8_t transferMode;    /**< Data transfer mode, as defined in {@link SpiTransferMode}. */
    uint8_t bitsPerWord;     /**< Data transfer bit width */
};

/**
 * @brief Obtains the handle of an SPI device.
 *
 * @param info Indicates the pointer to the SPI device information.
 *
 * @return Returns the pointer to the handle of the SPI device if the operation is successful;
 * returns <b>NULL</b> otherwise.
 *
 * @since 1.0
 */
struct DevHandle *SpiOpen(const struct SpiDevInfo *info);

/**
 * @brief Releases the handle of an SPI device.
 *
 * @param handle Indicates the pointer to the SPI device handle obtained via {@link SpiOpen}.
 *
 * @since 1.0
 */
void SpiClose(struct DevHandle *handle);

/**
 * @brief Launches a custom transfer to an SPI device.
 *
 * @param handle Indicates the pointer to the SPI device handle obtained via {@link SpiOpen}.
 * @param msgs Indicates the pointer to the data to transfer.
 * @param count Indicates the length of the message structure array.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
 * @see SpiMsg
 * @since 1.0
 */
int32_t SpiTransfer(struct DevHandle *handle, struct SpiMsg *msgs, uint32_t count);

/**
 * @brief Reads data of a specified length from an SPI device.
 *
 * @param handle Indicates the pointer to the SPI device handle obtained via {@link SpiOpen}.
 * @param buf Indicates the pointer to the buffer for receiving the data.
 * @param len Indicates the length of the data to read.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
 *
 * @since 1.0
 */
int32_t SpiRead(struct DevHandle *handle, uint8_t *buf, uint32_t len);

/**
 * @brief Writes data of a specified length to an SPI device.
 *
 * @param handle Indicates the pointer to the SPI device handle obtained via {@link SpiOpen}.
 * @param buf Indicates the pointer to the data to write.
 * @param len Indicates the length of the data to write.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
 *
 * @since 1.0
 */
int32_t SpiWrite(struct DevHandle *handle, uint8_t *buf, uint32_t len);

/**
 * @brief Sets configuration parameters for an SPI device.
 *
 * @param handle Indicates the pointer to the SPI device handle obtained via {@link SpiOpen}.
 * @param cfg Indicates the pointer to the configuration parameters.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
 *
 * @since 1.0
 */
int32_t SpiSetCfg(struct DevHandle *handle, struct SpiCfg *cfg);

/**
 * @brief Obtains the configuration parameters of an SPI device.
 *
 * @param handle Indicates the pointer to the SPI device handle obtained via {@link SpiOpen}.
 * @param cfg Indicates the pointer to the configuration parameters.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value otherwise.
 *
 * @since 1.0
 */
int32_t SpiGetCfg(struct DevHandle *handle, struct SpiCfg *cfg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* SPI_IF_H */
/** @} */
