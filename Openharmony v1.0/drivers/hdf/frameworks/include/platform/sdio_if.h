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
 * @addtogroup SDIO
 * @{
 *
 * @brief Declares standard APIs of basic secure digital input and output (SDIO) capabilities.
 *
 * You can use this module to access the SDIO and enable the driver to operate an SDIO-compliant device.
 * These capabilities include reading and writing data based on SDIO, setting the block size,
 * applying for and releasing interrupts, enabling and disabling devices, and occupying and releasing the bus.
 *
 * @since 1.0
 */

 /**
  * @file sdio_if.h
  *
  * @brief Declares the standard SDIO APIs.
  *
  * @since 1.0
  */

#ifndef SDIO_IF_H
#define SDIO_IF_H

#include "hdf_platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Enumerates SDIO common information types.
 *
 * When obtaining SDIO common information by calling {@link SdioGetCommonInfo} or setting the information
 * by calling {@link SdioSetCommonInfo}, you need to pass the information type.
 */
typedef enum {
    SDIO_FUNC_INFO = 0,   /**< Functionality information */
    SDIO_OTHER_INFO,      /**< Other information */
} SdioCommonInfoType;

/**
 * @brief Defines the SDIO capabilities.
 *
 * You can obtain and set the SDIO capabilities by calling {@link SdioGetCommonInfo} and {@link SdioSetCommonInfo}
 * with {@link SdioCommonInfo} and {@link SdioCommonInfoType} passed.
 */
typedef struct {
    uint32_t maxBlockNum;    /**< Maximum number of blocks in a request */
    uint32_t maxBlockSize;   /**< Maximum number of bytes in a block.
                              * The value ranges from <b>1</b> to <b>2048</b>.
                              */
    uint32_t maxRequestSize; /**< Maximum number of bytes in a request.
                              * The value ranges from <b>1</b> to <b>2048</b>.
                              */
    uint32_t enTimeout;      /**< Maximum timeout duration, in milliseconds.
                              * The value cannot exceed <b>1</b> second.
                              */
    uint32_t funcNum;        /**< Functionality number, ranging from <b>1</b> to <b>7</b>. */
    uint32_t irqCap;         /**< IRQ capabilities */
    void *data;              /**< Private data */
} SdioFuncInfo;

/**
 * @brief Defines SDIO common information.
 *
 * You can obtain and set common SDIO information by calling {@link SdioGetCommonInfo} and {@link SdioSetCommonInfo}
 * with {@link SdioCommonInfo} and {@link SdioCommonInfoType} passed.
 */
typedef union {
    SdioFuncInfo funcInfo;   /**< Functionality information */
} SdioCommonInfo;

/**
 * @brief Defines the function type of an SDIO IRQ.
 *
 * This function is registered when you call {@link SdioClaimIrq} to request the SDIO IRQ.
 *
 * @param data Indicates the private data passed to this IRQ (The data is specified when the IRQ is registered).
 *
 * @since 1.0
 */
typedef void SdioIrqHandler(void *);

/**
 * @brief Opens an SDIO controller with a specified bus number.
 *
 * Before using the SDIO interface, you can obtain the device handle of the SDIO controller
 * by calling {@link SdioOpen}. This function is used in pair with {@link SdioClose}.
 *
 * @param busNum Indicates the bus number.
 *
 * @return Returns the device handle {@link DevHandle} of the SDIO controller if the operation is successful;
 * returns <b>NULL</b> otherwise.
 * @since 1.0
 */
struct DevHandle *SdioOpen(int16_t busNum);

/**
 * @brief Closes an SDIO controller.
 *
 * After the SDIO interface is used, you can close the SDIO controller by calling {@link SdioClose}.
 * This function is used in pair with {@link SdioOpen}.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller.
 *
 * @since 1.0
 */
void SdioClose(struct DevHandle *handle);

/**
 * @brief Incrementally reads a given length of data from the specified SDIO address.
 *
 * If the length of the data to read is greater than the size of a block, the data is read by block,
 * and the remaining data that is smaller than one block is read by byte. Otherwise, data is read by byte.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 * @param data Indicates the pointer to the data to read.
 * @param addr Indicates the start address of the data to read.
 * @param size Indicates the length of the data to read.
 * @param timeOut Indicates the timeout duration for reading data, in milliseconds.
 * If the value is <b>0</b>,the default value is used. The default value varies according to the application.
 * Generally, the default value is <b>1</b> second.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioReadBytes(struct DevHandle *handle, uint8_t *data, uint32_t addr,
    uint32_t size, uint32_t timeOut);

/**
 * @brief Incrementally writes a given length of data into the specified SDIO address.
 *
 * If the length of the data to write is greater than the size of a block, the data is written by block first,
 * and the remaining data that is smaller than one block is written by byte. Otherwise, data is written by byte.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 * @param data Indicates the pointer to the data to write.
 * @param addr Indicates the start address of the data to write.
 * @param size Indicates the length of the data to write.
 * @param timeOut Indicates the timeout duration for writing data, in milliseconds.
 * If the value is <b>0</b>, the default value is used. The default value varies according to the application.
 * Generally, the default value is <b>1</b> second.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioWriteBytes(struct DevHandle *handle, uint8_t *data, uint32_t addr,
    uint32_t size, uint32_t timeOut);

/**
 * @brief Reads a given length of data from the fixed SDIO address.
 *
 * If the length of the data to read is greater than the size of a block, the data is read by block,
 * and the remaining data that is smaller than one block is read by byte. Otherwise, data is read by byte.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 * @param data Indicates the pointer to the data to read.
 * @param addr Indicates the fixed address of the data to read.
 * @param size Indicates the length of the data to read.
 * @param timeOut Indicates the timeout duration for reading data, in milliseconds.
 * If the value is <b>0</b>, the default value is used. The default value varies according to the application.
 * Generally, the default value is <b>1</b> second.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioReadBytesFromFixedAddr(struct DevHandle *handle, uint8_t *data,
    uint32_t addr, uint32_t size, uint32_t timeOut);

/**
 * @brief Writes a given length of data into the fixed SDIO address.
 *
 * If the length of the data to write is greater than the size of a block, the data is written by block first,
 * and the remaining data that is smaller than one block is written by byte. Otherwise, data is written by byte.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 * @param data Indicates the pointer to the data to write.
 * @param addr Indicates the fixed address of the data to write.
 * @param size Indicates the length of the data to write.
 * @param timeOut Indicates the timeout duration for writing data, in milliseconds.
 * If the value is <b>0</b>, the default value is used. The default value varies according to the application.
 * Generally, the default value is <b>1</b> second.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioWriteBytesToFixedAddr(struct DevHandle *handle, uint8_t *data,
    uint32_t addr, uint32_t size, uint32_t timeOut);

/**
 * @brief Reads a given length of data from the address space of SDIO function 0.
 *
 * Currently, only one byte of data can be read.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 * @param data Indicates the pointer to the data to read.
 * @param addr Indicates the start address of the data to read.
 * @param size Indicates the length of the data to read.
 * @param timeOut Indicates the timeout duration for reading data, in milliseconds.
 * If the value is <b>0</b>, the default value is used. The default value varies according to the application.
 * Generally, the default value is <b>1</b> second.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioReadBytesFromFunc0(struct DevHandle *handle, uint8_t *data,
    uint32_t addr, uint32_t size, uint32_t timeOut);

/**
 * @brief Writes a given length of data into the address space of SDIO function 0.
 *
 * Currently, only one byte of data can be written.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 * @param data Indicates the pointer to the data to write.
 * @param addr Indicates the start address of the data to write.
 * @param size Indicates the length of the data to write.
 * @param timeOut Indicates the timeout duration for writing data, in milliseconds.
 * If the value is <b>0</b>, the default value is used. The default value varies according to the application.
 * Generally, the default value is <b>1</b> second.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioWriteBytesToFunc0(struct DevHandle *handle, uint8_t *data,
    uint32_t addr, uint32_t size, uint32_t timeOut);

/**
 * @brief Sets the block size.
 *
 * If data to read or write is performed, use this function to set the block size.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 * @param blockSize Indicates the block size to be set. If the value is <b>0</b>, the default value is used.
 * The value ranges from <b>1</b> to <b>2048</b> bytes.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioSetBlockSize(struct DevHandle *handle, uint32_t blockSize);

/**
 * @brief Obtains common information.
 *
 * You can call this function to obtain the capabilities and private data of the I/O function.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 * @param info Indicates the pointer to the common information to be obtained.
 * For details, see {@link SdioCommonInfo}.
 * @param infoType Indicates the type of the common information to be obtained.
 * For details, see {@link SdioCommonInfoType}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioGetCommonInfo(struct DevHandle *handle, SdioCommonInfo *info, SdioCommonInfoType infoType);

/**
 * @brief Sets common information.
 *
 * You can call this function to set the maximum timeout duration and private data.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 * @param info Indicates the pointer to the common information to be set.
 * For details, see {@link SdioCommonInfo}.
 * @param infoType Indicates the type of the common information to be set.
 * For details, see {@link SdioCommonInfoType}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioSetCommonInfo(struct DevHandle *handle, SdioCommonInfo *info, SdioCommonInfoType infoType);

/**
 * @brief Flushes data.
 *
 * You can call this function when an SDIO needs to be reinitialized or an unexpected error occurs.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioFlushData(struct DevHandle *handle);

/**
 * @brief Claims a host exclusively.
 *
 * You can call this function to enable the SDIO module to exclusively claim a host
 * and then perform operations on the devices connected to the host. After performing required operations,
 * release the host by calling {@link SdioReleaseHost}.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 *
 * @since 1.0
 */
void SdioClaimHost(struct DevHandle *handle);

/**
 * @brief Releases the exclusively claimed host.
 *
 * This function is used in pair with {@link SdioClaimHost}.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 *
 * @since 1.0
 */
void SdioReleaseHost(struct DevHandle *handle);

/**
 * @brief Enables the SDIO device so that its register can be accessed.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioEnableFunc(struct DevHandle *handle);

/**
 * @brief Disables the SDIO device.
 *
 * This function is used in pair with {@link SdioEnableFunc}.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioDisableFunc(struct DevHandle *handle);

/**
 * @brief Claims an SDIO IRQ.
 *
 * When there is data, commands, or events, the IRQ function is executed.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 * @param irqHandler Indicates the pointer to the SDIO IRQ function. For details, see {@link SdioIrqHandler}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioClaimIrq(struct DevHandle *handle, SdioIrqHandler *irqHandler);

/**
 * @brief Releases an SDIO IRQ.
 *
 * This function is used in pair with {@link SdioClaimIrq}.
 *
 * @param handle Indicates the pointer to the device handle of the SDIO controller obtained by {@link SdioOpen}.
 *
 * @return Returns <b>0</b> if the operation is successful; returns a negative value if the operation fails.
 * @since 1.0
 */
int32_t SdioReleaseIrq(struct DevHandle *handle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* SDIO_IF_H */
/** @} */