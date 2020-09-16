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
 * @addtogroup Core
 * @{
 *
 * @brief Provides OpenHarmony Driver Foundation (HDF) APIs.
 *
 * The HDF implements driver framework capabilities such as driver loading, service management,
 * and driver message model. You can develop drivers based on the HDF.
 *
 * @since 1.0
 */

/**
 * @file hdf_sbuf.h
 *
 * @brief Defines functions related to a <b>HdfSBuf</b>. The HDF provides data serialization and deserialization
 * capabilities for data transmission between user-mode applications and kernel-mode drivers.
 *
 * @since 1.0
 */

#ifndef HDF_SBUF_H
#define HDF_SBUF_H

#include <stdio.h>
#include <stdbool.h>
#include "hdf_cstring.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Defines a <b>HdfSBuf</b>.
 *
 * @since 1.0
 */
struct HdfSBuf {
    size_t writePos; /**< Current write position */
    size_t readPos; /**< Current read position */
    size_t capacity; /**< Storage capacity, at most 512 KB. */
    uint8_t *data; /**< Pointer to data storage */
    bool isBind; /**< Whether to bind the externally transferred pointer for data storage */
};

/**
 * @brief Writes a data segment to a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param data Indicates the pointer to the data segment to write.
 * @param writeSize Indicates the size of the data segment to write. The maximum value is 512 KB.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufWriteBuffer(struct HdfSBuf *sbuf, const void *data, uint32_t writeSize);

/**
 * @brief Writes a 64-bit unsigned integer to a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the 64-bit unsigned integer to write.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufWriteUint64(struct HdfSBuf *sbuf, uint64_t value);

/**
 * @brief Writes a 32-bit unsigned integer to a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the 32-bit unsigned integer to write.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufWriteUint32(struct HdfSBuf *sbuf, uint32_t value);

/**
 * @brief Writes a 16-bit unsigned integer to a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the 16-bit unsigned integer to write.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufWriteUint16(struct HdfSBuf *sbuf, uint16_t value);

/**
 * @brief Writes an 8-bit unsigned integer to a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the 8-bit unsigned integer to write.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufWriteUint8(struct HdfSBuf *sbuf, uint8_t value);

/**
 * @brief Writes a 64-bit signed integer to a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the 64-bit signed integer to write.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufWriteInt64(struct HdfSBuf *sbuf, int64_t value);

/**
 * @brief Writes a 32-bit signed integer to a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the 32-bit signed integer to write.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufWriteInt32(struct HdfSBuf *sbuf, int32_t value);

/**
 * @brief Writes a 16-bit signed integer to a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the 16-bit signed integer to write.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufWriteInt16(struct HdfSBuf *sbuf, int16_t value);

/**
 * @brief Writes an 8-bit signed integer to a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the 8-bit signed integer to write.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufWriteInt8(struct HdfSBuf *sbuf, int8_t value);

/**
 * @brief Writes a string to a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the pointer to the string to write.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufWriteString(struct HdfSBuf *sbuf, const char *value);

/**
 * @brief Reads a data segment from a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param data Indicates the double pointer to the data read. The data read is stored in <b>*data</b>,
 * which is requested by the caller. The memory pointed to by <b>*data</b> is managed by the <b>SBuf</b>
 * and they share the same lifecycle.
 * @param readSize Indicates the pointer to the size of the data read.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufReadBuffer(struct HdfSBuf *sbuf, const void **data, uint32_t *readSize);

/**
 * @brief Reads a 64-bit unsigned integer from a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the pointer to the 64-bit unsigned integer read, which is requested by the caller.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufReadUint64(struct HdfSBuf *sbuf, uint64_t *value);

/**
 * @brief Reads a 32-bit unsigned integer from a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the pointer to the 32-bit unsigned integer read, which is requested by the caller.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufReadUint32(struct HdfSBuf *sbuf, uint32_t *value);

/**
 * @brief Reads a 16-bit unsigned integer from a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the pointer to the 16-bit unsigned integer read, which is requested by the caller.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufReadUint16(struct HdfSBuf *sbuf, uint16_t *value);

/**
 * @brief Reads an 8-bit unsigned integer from a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the pointer to the 8-bit unsigned integer read, which is requested by the caller.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufReadUint8(struct HdfSBuf *sbuf, uint8_t *value);

/**
 * @brief Reads a 64-bit signed integer from a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the pointer to the 64-bit signed integer read, which is requested by the caller.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufReadInt64(struct HdfSBuf *sbuf, int64_t *value);

/**
 * @brief Reads a 32-bit signed integer from a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the pointer to the 32-bit signed integer read, which is requested by the caller.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufReadInt32(struct HdfSBuf *sbuf, int32_t *value);

/**
 * @brief Reads a 16-bit signed integer from a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the pointer to the 16-bit signed integer read, which is requested by the caller.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufReadInt16(struct HdfSBuf *sbuf, int16_t *value);

/**
 * @brief Reads an 8-bit signed integer from a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @param value Indicates the pointer to the 8-bit signed integer read, which is requested by the caller.
 * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
 *
 * @since 1.0
 */
bool HdfSbufReadInt8(struct HdfSBuf *sbuf, int8_t *value);

/**
 * @brief Reads a string from a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @return Returns the pointer to the string read if the operation is successful; returns <b>NULL</b> otherwise.
 * The memory pointed to by this pointer is managed by the <b>SBuf</b> and they share the same lifecycle.
 *
 * @since 1.0
 */
const char *HdfSbufReadString(struct HdfSBuf *sbuf);

/**
 * @brief Obtains the pointer to the data stored in a<b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @return Returns the pointer to the data stored in the target <b>SBuf</b>.
 *
 * @since 1.0
 */
uint8_t *HdfSbufGetData(const struct HdfSBuf *sbuf);

/**
 * @brief Clears the data stored in a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 *
 * @since 1.0
 */
void HdfSbufFlush(struct HdfSBuf *sbuf);

/**
 * @brief Obtains the capacity of a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @return Returns the <b>SBuf</b> capacity.
 * @since 1.0
 */
size_t HdfSbufGetCapacity(const struct HdfSBuf *sbuf);

/**
 * @brief Obtains the size of the data stored in a <b>SBuf</b>.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 * @return Returns the data size.
 *
 * @since 1.0
 */
size_t HdfSbufGetDataSize(const struct HdfSBuf *sbuf);

/**
 * @brief Obtains a <b>SBuf</b> instance.
 *
 * @param capacity Indicates the initial capacity of the<b>SBuf</b>.
 * @return Returns the <b>SBuf</b> instance.
 *
 * @since 1.0
 */
struct HdfSBuf *HdfSBufObtain(size_t capacity);

/**
 * @brief Obtains a <b>SBuf</b> instance of the default capacity (256 bytes).
 *
 * @return Returns the <b>SBuf</b> instance.
 *
 * @since 1.0
 */
struct HdfSBuf *HdfSBufObtainDefaultSize(void);

/**
 * @brief Creates a <b>SBuf</b> instance with the specified data and size.
 * The pointer to the data stored in the <b>SBuf</b> is released by the caller,
 * and the written data size should not exceed the specified value of <b>size</b>.
 *
 * @param base Indicates the base of the data to use.
 * @param size Indicates the size of the data to use.
 * @return Returns the <b>SBuf</b> instance.
 *
 * @since 1.0
 */
struct HdfSBuf *HdfSBufBind(uintptr_t base, size_t size);

/**
 * @brief Releases a <b>SBuf </b>.
 *
 * @param sbuf Indicates the pointer to the <b>SBuf</b> to release.
 *
 * @since 1.0
 */
void HdfSBufRecycle(struct HdfSBuf *sbuf);

/**
 * @brief Creates a <b>SBuf</b> instance with an original <b>SBuf</b>.
 * This function moves the data stored in the original <b>SBuf</b> to the new one without memory copy.
 *
 * @param sbuf Indicates the pointer to the original <b>SBuf</b>.
 * @return Returns the new <b>SBuf</b> instance.
 *
 * @since 1.0
 */
struct HdfSBuf *HdfSBufMove(struct HdfSBuf *sbuf);

/**
 * @brief Creates a <b>SBuf</b> instance with an original <b>SBuf</b>.
 * This function copies the data stored in the original <b>SBuf</b> to the new one.
 *
 * @param sbuf Indicates the pointer to the original <b>SBuf</b>.
 * @return Returns the new <b>SBuf</b> instance.
 *
 * @since 1.0
 */
struct HdfSBuf *HdfSBufCopy(const struct HdfSBuf *sbuf);

/**
 * @brief Transfers the data ownership to a <b>SBuf</b>. Once the <b>SBuf</b> is released,
 * the bound data memory is also released. This function is used together with {@link HdfSBufBind}.
 *
 * @param sbuf Indicates the pointer to the target <b>SBuf</b>.
 *
 * @since 1.0
 */
void HdfSbufTransDataOwnership(struct HdfSBuf *sbuf);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HDF_SBUF_H */
/** @} */
