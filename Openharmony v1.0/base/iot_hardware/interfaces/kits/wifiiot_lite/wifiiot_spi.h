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
 * @file wifiiot_spi.h
 *
 * @brief Declares the SPI interface functions.
 *
 * These functions are used for SPI initialization, deinitialization, and data transmission. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef WIFIIOT_SPI_H
#define WIFIIOT_SPI_H

/**
 * @brief Indicates the SPI callback, which is used in {@link SpiRegisterUsrFunc}.
 */
typedef void (*SpiIsrFunc)(void);

/**
 * @brief Enumerates SPI channel IDs.
 */
typedef enum {
    /** Channel 0 */
    WIFI_IOT_SPI_ID_0 = 0,
    /** Channel 1 */
    WIFI_IOT_SPI_ID_1,
} WifiIotSpiIdx;

/**
 * @brief Enumerates communication polarities.
 */
typedef enum {
    /** Polarity 0 */
    WIFI_IOT_SPI_CFG_CLOCK_CPOL_0,
    /** Polarity 1 */
    WIFI_IOT_SPI_CFG_CLOCK_CPOL_1,
}WifiIotSpiCfgClockCpol;

/**
 * @brief Enumerates communication phases.
 */
typedef enum {
    /** Phase 0 */
    WIFI_IOT_SPI_CFG_CLOCK_CPHA_0,
    /** Phase 1 */
    WIFI_IOT_SPI_CFG_CLOCK_CPHA_1,
} WifiIotSpiCfgClockCpha;

/**
 * @brief Enumerates communication protocols.
 */
typedef enum {
    /** Motorola protocol */
    WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA,
    /** Texas Instruments protocol */
    WIFI_IOT_SPI_CFG_FRAM_MODE_TI,
    /** Microwire protocol */
    WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE,
} WifiIotSpiCfgFramMode;

/**
 * @brief Enumerates the communication data width, that is,
 * the number of valid bits in each frame.
 *
 */
typedef enum {
    /** 4 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT = 0x3,
    /** 5 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_5BIT,
    /** 6 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_6BIT,
    /** 7 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_7BIT,
    /** 8 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_8BIT,
    /** 9 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_9BIT,
    /** 10 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT,
    /** 11 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_11BIT,
    /** 12 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_12BIT,
    /** 13 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_13BIT,
    /** 14 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_14BIT,
    /** 15 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_15BIT,
    /** 16 bits */
    WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT,
} WifiIotSpiCfgDataWidth;

/**
 * @brief Enumerates the endian mode of each frame.
 */
typedef enum {
    /** Little-endian */
    WIFI_IOT_SPI_CFG_ENDIAN_LITTLE,
    /** Big-endian */
    WIFI_IOT_SPI_CFG_ENDIAN_BIG,
} WifiIotSpiCfgEndian;

/**
 * @brief Defines data communication parameters.
 */
typedef struct {
    /** Communication polarity. For details about available values,
     * see {@link WifiIotSpiCfgClockCpol}.
     */
    unsigned int cpol : 1;
    /** Communication phase.
     * For details about available values, see {@link WifiIotSpiCfgClockCpha}.
     */
    unsigned int cpha : 1;
    /** Communication protocol.
     * For details about available values, see {@link WifiIotSpiCfgFramMode}.
     */
    unsigned int framMode : 2;
    /** Communication data width.
     * For details about available values, see {@link WifiIotSpiCfgDataWidth}.
     */
    unsigned int dataWidth : 4;
    /** Endian mode. For details about available values, see {@link WifiIotSpiCfgEndian}. */
    unsigned int endian : 1;
    /** Padding bit */
    unsigned int pad : 23;
    /** Communication frequency. The value ranges from 2460 Hz to 40 MHz. */
    unsigned int freq;
} WifiIotSpiCfgBasicInfo;

/**
 * @brief Specifies whether a device is a master or slave device.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /** Whether the device is a slave device */
    unsigned int isSlave : 1;
    /** Padding bit */
    unsigned int pad : 31;
} WifiIotSpiCfgInitParam;

/**
 * @brief Sends data in SPI slave mode.
 *
 * In SPI slave mode, this function sends data of the length
 * specified by <b>byteLen</b> in <b>writeData</b> through
 * the channel specified by <b>spiId</b> within the duration <b>timeOutMs</b>.
 *
 * @param spiId Indicates the SPI channel ID.
 * @param writeData Indicates the pointer to the data to send.
 * @param byteLen Indicates the length of the data to send.
 * @param timeOutMs Indicates the timeout interval.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiSlaveWrite(WifiIotSpiIdx spiId, char *writeData, unsigned int byteLen, unsigned int timeOutMs);

/**
 * @brief Reads data in SPI slave mode.
 *
 * In SPI slave mode, this function reads data of the length
 * specified by <b>byteLen</b> in <b>readData</b> through the channel
 * specified by <b>spiId</b> within the duration <b>timeOutMs</b>.
 *
 * @param spiId Indicates the SPI channel ID.
 * @param readData Indicates the pointer to the data to read.
 * @param byteLen Indicates the length of the data to read.
 * @param timeOutMs Indicates the timeout interval.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiSlaveRead(WifiIotSpiIdx spiId, char *readData, unsigned int byteLen, unsigned int timeOutMs);

/**
 * @brief Sends data in half-duplex SPI master mode.
 *
 * In SPI master mode, this function sends data of the length
 * specified by <b>byteLen</b> in <b>writeData</b>
 * through the channel specified by <b>spiId</b>.
 *
 * @param spiId Indicates the SPI channel ID.
 * @param writeData Indicates the pointer to the data to send.
 * @param byteLen Indicates the length of the data to send.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiHostWrite(WifiIotSpiIdx spiId, char *writeData, unsigned int byteLen);

/**
 * @brief Reads data in half-duplex SPI master mode.
 *
 * In SPI master mode, this function reads data of the length
 * specified by <b>byteLen</b> in <b>readData</b>
 * through the channel specified by <b>spiId</b>.
 *
 * @param spiId Indicates the SPI channel ID.
 * @param readData Indicates the pointer to the data to read.
 * @param byteLen Indicates the length of the data to read.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiHostRead(WifiIotSpiIdx spiId, char *readData, unsigned int byteLen);

/**
 * @brief Sends and reads data in full-duplex SPI master mode.
 *
 * In SPI master mode, this function sends data in <b>writeData</b> and
 * reads data of the length specified by <b>byteLen</b> in <b>readData</b>
 * both through the channel specified by <b>spiId</b>.
 *
 * @param spiId Indicates the SPI channel ID.
 * @param writeData Indicates the pointer to the data to send.
 * @param readData Indicates the pointer to the data to read.
 * @param byteLen Indicates the length of the data to read.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiHostWriteread(WifiIotSpiIdx spiId, char *writeData, char *readData, unsigned int byteLen);

/**
 * @brief Sets the SPI channel parameter.
 *
 *
 *
 * @param spiId Indicates the SPI channel ID.
 * @param param Indicates the pointer to the SPI parameter to set.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiSetBasicInfo(WifiIotSpiIdx spiId, const WifiIotSpiCfgBasicInfo *param);

/**
 * @brief Initializes an SPI device.
 *
 * This function initializes the device with the channel ID <b>spiId</b>,
 * device type <b>initParam</b>, and device parameter <b>param</b>.
 *
 * @param spiId Indicates the SPI channel ID.
 * @param initParam Specifies whether the device is a slave one.
 * @param param Indicates the pointer to the SPI device parameter.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiInit(WifiIotSpiIdx spiId, WifiIotSpiCfgInitParam initParam, const WifiIotSpiCfgBasicInfo *param);

/**
 * @brief Deinitializes an SPI device.
 *
 * @param spiId Indicates the SPI channel ID.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiDeinit(WifiIotSpiIdx spiId);

/**
 * @brief Sets whether to enable the interrupt request (IRQ) mode for an SPI device.
 *
 *
 *
 * @param spiId Indicates the SPI channel ID.
 * @param irqEn Specifies whether to enable IRQ.
 * The value <b>1</b> means to enable IRQ, and <b>0</b> means to disable IRQ.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiSetIrqMode(WifiIotSpiIdx spiId, unsigned char irqEn);

/**
 * @brief Sets whether to enable DMA to transfer data for an SPI device in slave mode.
 *
 *
 *
 * @param spiId Indicates the SPI channel ID.
 * @param dmaEn Specifies whether to enable DMA.
 * The value <b>1</b> means to enable DMA, and <b>0</b> means to disable DMA.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiSetDmaMode(WifiIotSpiIdx spiId, unsigned char dmaEn);

/**
 * @brief Registers the data TX preparation/recovery function.
 *
 * This function registers the functions
 * registered by <b>prepareF</b> and <b>restoreF</b> for
 * an SPI device with a channel specified by <b>spiId</b>.
 *
 * @param spiId Indicates the SPI channel ID.
 * @param prepareF Indicates the function used for data preparation.
 * @param restoreF Indicates the function used for data recovery.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiRegisterUsrFunc(WifiIotSpiIdx spiId, SpiIsrFunc prepareF, SpiIsrFunc restoreF);

/**
 * @brief Sets whether to enable loopback test for an SPI device.
 *
 *
 *
 * @param spiId Indicates the SPI channel ID.
 * @param lbEn Specifies whether to enable loopback test. The value <b>1</b>
 * means to enable loopback test, and <b>0</b> means to disable loopback test.
 * @return Returns {@link WIFI_IOT_SUCCESS} if the operation is successful;
 * returns an error code defined in {@link wifiiot_errno.h} otherwise.
 * @since 1.0
 * @version 1.0
 */
unsigned int SpiSetLoopBackMode(WifiIotSpiIdx spiId, unsigned char lbEn);

#endif
/** @} */
