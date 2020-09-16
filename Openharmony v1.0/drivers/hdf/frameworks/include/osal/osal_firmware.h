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
 * @addtogroup OSAL
 * @{
 *
 * @brief Defines the structures and interfaces for the Operating System Abstraction Layer (OSAL) module.
 *
 * The OSAL module harmonizes OS interface differences and provides unified OS interfaces externally,
 * including the memory management, thread, mutex, spinlock, semaphore, timer, file, interrupt, time,
 * atomic, firmware, and I/O operation modules.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file osal_firmware.h
 *
 * @brief Declares firmware structures and interfaces.
 *
 * This file provides operations such as requesting and reading a firmware file, setting the offset for reading
 * a firmware file, and releasing a firmware file. The firmware file can be read in split mode.
 * The size of the firmware block to read each time is defined by the macro {@link HDF_FW_BLOCK_SIZE}.
 * The firmware file is requested by calling {@link OsalRequestFirmware}, the firmware block is read from
 * the firmware file by calling {@link OsalReadFirmware}, and the firmware block can also be randomly read
 * at a specified position by calling {@link OsalSeekFirmware}.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OSAL_FIRMWARE_H
#define OSAL_FIRMWARE_H

#include "hdf_base.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Defines the data structure for operating a firmware file.
 */
struct OsalFirmware {
    uint32_t fwSize; /**< Firmware file size, which is returned by calling {@link OsalRequestFirmware}. */
    void *para; /**< Pointer to a firmware file, which is returned by calling {@link OsalRequestFirmware}.
                 * You do not need to allocate space.
                 */
};

/**
 * @brief Defines the data structure for reading a firmware file.
 *
 * This structure declares the firmware block to read each time. The firmware file can be read in split mode.
 */
struct OsalFwBlock {
    uint8_t *data; /**< Firmware content read this time. You do not need to allocate space. */
    bool endFlag; /**< Whether the firmware file is read completely */
    uint32_t dataSize; /**< Firmware block size read this time */
    int32_t curOffset; /**< Offset in the firmware file */
};

/**
 * @brief Requests a firmware file based on its name and device information.
 *
 * @param fw Indicates the pointer to the firmware file {@link OsalFirmware}, which cannot be empty.
 * @param fwName Indicates the pointer to the firmware file name, which cannot be empty.
 * @param device Indicates the pointer to the information about the device that requests the firmware file.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 * HDF_ERR_MALLOC_FAIL | Memory allocation fails.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalRequestFirmware(struct OsalFirmware *fw, const char *fwName, void *device);

/**
 * @brief Reads a firmware file.
 *
 * @param fw Indicates the pointer to the firmware file {@link OsalFirmware}.
 * @param block Indicates the pointer to the firmware block to read. For details, see {@link OsalFwBlock}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalSeekFirmware(struct OsalFirmware *fw, uint32_t offset);

/**
 * @brief Releases a firmware file.
 *
 * After the firmware file is read, this function is called to release the firmware file.
 *
 * @param fw Indicates the pointer to the firmware file {@link OsalFirmware}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalReadFirmware(struct OsalFirmware *fw, struct OsalFwBlock *block);

/**
 * Release firmware resource
 *
 * @param : fw Firmware parameter, see detail in OsalFirmware
 *          block Firmware data block, see detail in hdf_FWBlock
 * @return : true or false
 */
int32_t OsalReleaseFirmware(struct OsalFirmware *fw);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_FIRMWARE_H */
/** @} */
