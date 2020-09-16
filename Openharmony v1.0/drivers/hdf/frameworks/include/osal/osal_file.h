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
 * @file osal_file.h
 *
 * @brief Declares the file structures and interfaces.
 *
 * This file provides interfaces for opening, closing, reading, and writing a file, and setting the read/write offset.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OSAL_FILE_H
#define OSAL_FILE_H

#include "hdf_base.h"
#include <fcntl.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Opens a file in read-only mode.
 */
#define OSAL_O_RD_ONLY 0
/**
 * @brief Opens a file in write-only mode.
 */
#define OSAL_O_WR_ONLY 1
/**
 * @brief Opens a file in read and write mode.
 */
#define OSAL_O_RDWR 2

/**
 * @brief Defines the read permission for the owner.
 */
#define OSAL_S_IREAD 00400
/**
 * @brief Defines the write permission for the owner.
 */
#define OSAL_S_IWRITE 00200
/**
 * @brief Defines the execution permission for the owner.
 */
#define OSAL_S_IEXEC 00100

/**
 * @brief Defines the read permission for the group.
 */
#define OSAL_S_IRGRP 00040
/**
 * @brief Defines the write permission for the group.
 */
#define OSAL_S_IWGRP 00020
/**
 * @brief Defines the execution permission for the group.
 */
#define OSAL_S_IXGRP 00010

/**
 * @brief Defines the read permission for others.
 */
#define OSAL_S_IROTH 00004
/**
 * @brief Defines the write permission for others.
 */
#define OSAL_S_IWOTH 00002
/**
 * @brief Defines the execution permission for others.
 */
#define OSAL_S_IXOTH 00001

/**
 * @brief Defines the offset from the file header.
 */
#define OSAL_SEEK_SET 0
/**
 * @brief Defines the offset from the current position.
 */
#define OSAL_SEEK_CUR 1
/**
 * @brief Defines the offset from the end of the file.
 */
#define OSAL_SEEK_END 2

/**
 * @brief Declares a file type.
 */
typedef struct {
    void *realFile; /**< Pointer to a file object to access */
} OsalFile;

/**
 * @brief Opens a file.
 *
 * @param file Indicates the pointer to the file type {@link OsalFile}.
 * @param path Indicates the pointer to the name of the file to open.
 * @param flags Indicates the mode of opening the file. For details, see {@link OSAL_O_RD_ONLY}.
 * @param rights Indicates the permissions required for opening the file. For details, see {@link OSAL_S_IREAD}.
 *
 * @return Returns a value listed below: \n
 * HDF_STATUS | Description
 * ----------------------| -----------------------
 * HDF_SUCCESS | The operation is successful.
 * HDF_FAILURE | Failed to invoke the system function to open the file.
 * HDF_ERR_INVALID_PARAM | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t OsalFileOpen(OsalFile *file, const char *path, int flags, uint32_t rights);

/**
 * @brief Writes a file.
 *
 * @param file Indicates the pointer to the file type {@link OsalFile}.
 * @param string Indicates the pointer to the content to write.
 * @param length Indicates the length of the content to write.
 *
 * @return Returns a value listed below: \n
 * ssize_t | Description
 * -----------------------------------------| -----------------------
 * Greater than <b>0</b> | The length of the file content is successfully written.
 * HDF_FAILURE {@link HDF_STATUS} | Failed to invoke the system function to write the file.
 * HDF_ERR_INVALID_PARAM {@link HDF_STATUS} | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
ssize_t OsalFileWrite(OsalFile *file, const void *string, uint32_t length);

/**
 * @brief Closes a file.
 *
 * @param file Indicates the pointer to the file type {@link OsalFile}.
 *
 * @since 1.0
 * @version 1.0
 */
void OsalFileClose(OsalFile *file);

/**
 * @brief Reads a file.
 *
 * @param file Indicates the pointer to the file type {@link OsalFile}.
 * @param buf Indicates the pointer to the buffer for storing the content to read.
 * @param length Indicates the length of the content to read.
 *
 * @return Returns a value listed below: \n
 * ssize_t | Description
 * -----------------------------------------| -----------------------
 * Greater than <b>0</b> | The length of the file content is successfully read.
 * HDF_FAILURE {@link HDF_STATUS} | Failed to invoke the system function to read the file.
 * HDF_ERR_INVALID_PARAM {@link HDF_STATUS} | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
ssize_t OsalFileRead(OsalFile *file, void *buf, uint32_t length);

/**
 * @brief Sets the file read/write offset.
 *
 * @param file Indicates the pointer to the file type {@link OsalFile}.
 * @param offset Indicates the offset to set.
 * @param whence Indicates the position from which the offset is to set. For details, see {@link OSAL_SEEK_SET}.
 *
 * off_t | Description
 * -----------------------------------------| -----------------------
 * Greater than <b>0</b> | The offset is set.
 * HDF_FAILURE {@link HDF_STATUS} | Failed to invoke the system function to set the file offset.
 * HDF_ERR_INVALID_PARAM {@link HDF_STATUS} | Invalid parameter.
 *
 * @since 1.0
 * @version 1.0
 */
off_t OsalFileLseek(OsalFile *file, off_t offset, int32_t whence);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSAL_FILE_H */
/** @} */
