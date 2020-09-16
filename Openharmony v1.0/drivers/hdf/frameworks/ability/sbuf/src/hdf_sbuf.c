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

#include <securec.h>
#include "osal_mem.h"
#include "hdf_log.h"
#include "hdf_sbuf.h"

#define HDF_SBUF_GROW_SIZE_DEFAULT 256
#define HDF_SBUF_MAX_SIZE (512 * 1024) // 512kB
#define HDF_SBUF_ALIGN 4

static inline size_t HdfSbufGetAlignSize(size_t size)
{
    return (size + HDF_SBUF_ALIGN - 1) & (~(HDF_SBUF_ALIGN - 1));
}

static size_t HdfSbufGetLeftWriteSize(struct HdfSBuf *sbuf)
{
    return (sbuf->capacity < sbuf->writePos) ? 0 : (sbuf->capacity - sbuf->writePos);
}

static size_t HdfSbufGetLeftReadSize(struct HdfSBuf *sbuf)
{
    return (sbuf->writePos < sbuf->readPos) ? 0 : (sbuf->writePos - sbuf->readPos);
}

static bool HdfSbufWriteRollback(struct HdfSBuf *sbuf, uint32_t size)
{
    size_t alignSize = HdfSbufGetAlignSize(size);
    if (sbuf->writePos < alignSize) {
        return false;
    }

    sbuf->writePos -= alignSize;
    return true;
}

static bool HdfSbufReadRollback(struct HdfSBuf *sbuf, uint32_t size)
{
    size_t alignSize = HdfSbufGetAlignSize(size);
    if (sbuf->readPos < alignSize) {
        return false;
    }

    sbuf->readPos -= alignSize;
    return true;
}

uint8_t *HdfSbufGetData(const struct HdfSBuf *sbuf)
{
    if (sbuf == NULL) {
        HDF_LOGE("Get data is null, input sbuf is null");
        return NULL;
    }
    return (uint8_t *)sbuf->data;
}

void HdfSbufFlush(struct HdfSBuf *sbuf)
{
    if (sbuf != NULL) {
        sbuf->readPos = 0;
        sbuf->writePos = 0;
    }
}

size_t HdfSbufGetCapacity(const struct HdfSBuf *sbuf)
{
    return (sbuf != NULL) ? sbuf->capacity : 0;
}

size_t HdfSbufGetDataSize(const struct HdfSBuf *sbuf)
{
    return (sbuf != NULL) ? sbuf->writePos : 0;
}

static bool HdfSbufGrow(struct HdfSBuf *sbuf, uint32_t growSize)
{
    if (sbuf->isBind) {
        HDF_LOGE("%s: binded sbuf oom", __func__);
        return false;
    }

    uint32_t newSize = HdfSbufGetAlignSize(sbuf->capacity + growSize);
    if (newSize < sbuf->capacity) {
        HDF_LOGE("%s: grow size overflow", __func__);
        return false;
    }
    if (newSize > HDF_SBUF_MAX_SIZE) {
        HDF_LOGE("%s: buf size over limit", __func__);
        return false;
    }

    uint8_t *newData = OsalMemCalloc(newSize);
    if (newData == NULL) {
        HDF_LOGE("%s: oom", __func__);
        return false;
    }

    if (memcpy_s(newData, newSize, sbuf->data, sbuf->writePos) != EOK) {
        OsalMemFree(newData);
        return false;
    }

    OsalMemFree(sbuf->data);
    sbuf->data = newData;
    sbuf->capacity = newSize;

    return true;
}

static bool HdfSbufWrite(struct HdfSBuf *sbuf, const uint8_t *data, uint32_t size)
{
    if (sbuf == NULL || data == NULL) {
        return false;
    }

    if (size == 0) {
        return true;
    }

    size_t alignSize = HdfSbufGetAlignSize(size);
    // in case of desireCapacity overflow
    if (alignSize < size) {
        HDF_LOGE("desireCapacity is overflow");
        return false;
    }
    size_t writeableSize = HdfSbufGetLeftWriteSize(sbuf);
    if (alignSize > writeableSize) {
        size_t growSize = (alignSize > HDF_SBUF_GROW_SIZE_DEFAULT) ? (alignSize + HDF_SBUF_GROW_SIZE_DEFAULT) :
                          HDF_SBUF_GROW_SIZE_DEFAULT;
        if (!HdfSbufGrow(sbuf, growSize)) {
            return false;
        }
        writeableSize = HdfSbufGetLeftWriteSize(sbuf);
    }

    uint8_t *dest = sbuf->data + sbuf->writePos;
    if (memcpy_s(dest, writeableSize, data, size) != EOK) {
        return false; /* never hits */
    }

    sbuf->writePos += alignSize;
    return true;
}

static bool HdfSbufRead(struct HdfSBuf *sbuf, uint8_t *data, uint32_t readSize)
{
    if (sbuf == NULL || data == NULL) {
        return false;
    }

    if (readSize == 0) {
        return true;
    }

    size_t alignSize = HdfSbufGetAlignSize(readSize);
    if (alignSize > HdfSbufGetLeftReadSize(sbuf)) {
        HDF_LOGE("Read out of buffer range");
        return false;
    }

    if (memcpy_s(data, readSize, sbuf->data + sbuf->readPos, readSize) != EOK) {
        return false; // never hits
    }
    sbuf->readPos += alignSize;
    return true;
}

bool HdfSbufWriteBuffer(struct HdfSBuf *sbuf, const void *data, uint32_t writeSize)
{
    if (sbuf == NULL) {
        HDF_LOGE("Write buffer failed, input param is invalid");
        return false;
    }
    if (data == NULL) {
        return HdfSbufWriteInt32(sbuf, 0);
    }

    if (!HdfSbufWriteInt32(sbuf, writeSize)) {
        return false;
    }
    if (!HdfSbufWrite(sbuf, data, writeSize)) {
        (void)HdfSbufWriteRollback(sbuf, sizeof(int32_t));
        return false;
    }

    return true;
}

/* return actual read size */
bool HdfSbufReadBuffer(struct HdfSBuf *sbuf, const void **data, uint32_t *readSize)
{
    if (sbuf == NULL || data == NULL || readSize == NULL) {
        HDF_LOGE("%s:input invalid", __func__);
        return false;
    }

    int buffSize = 0;
    if (!HdfSbufReadInt32(sbuf, &buffSize)) {
        return false;
    }

    if (buffSize == 0) {
        *data = NULL;
        *readSize = 0;
        return true;
    }
    size_t alignSize = HdfSbufGetAlignSize(buffSize);
    if (alignSize > HdfSbufGetLeftReadSize(sbuf)) {
        HDF_LOGE("%s:readBuff out of range", __func__);
        (void)HdfSbufReadRollback(sbuf, sizeof(int32_t));
        return false;
    }

    *data = sbuf->data + sbuf->readPos;
    *readSize = buffSize;
    sbuf->readPos += alignSize;
    return true;
}

bool HdfSbufWriteUint64(struct HdfSBuf *sbuf, uint64_t value)
{
    return HdfSbufWrite(sbuf, (uint8_t *)(&value), sizeof(value));
}

bool HdfSbufWriteUint32(struct HdfSBuf *sbuf, uint32_t value)
{
    return HdfSbufWrite(sbuf, (uint8_t *)(&value), sizeof(value));
}

bool HdfSbufWriteUint16(struct HdfSBuf *sbuf, uint16_t value)
{
    return HdfSbufWrite(sbuf, (uint8_t *)(&value), sizeof(value));
}

bool HdfSbufWriteUint8(struct HdfSBuf *sbuf, uint8_t value)
{
    return HdfSbufWrite(sbuf, (uint8_t *)(&value), sizeof(value));
}

bool HdfSbufWriteInt64(struct HdfSBuf *sbuf, int64_t value)
{
    return HdfSbufWrite(sbuf, (uint8_t *)(&value), sizeof(value));
}

bool HdfSbufWriteInt32(struct HdfSBuf *sbuf, int32_t value)
{
    return HdfSbufWrite(sbuf, (uint8_t *)(&value), sizeof(value));
}

bool HdfSbufWriteInt16(struct HdfSBuf *sbuf, int16_t value)
{
    return HdfSbufWrite(sbuf, (uint8_t *)(&value), sizeof(value));
}

bool HdfSbufWriteInt8(struct HdfSBuf *sbuf, int8_t value)
{
    return HdfSbufWrite(sbuf, (uint8_t *)(&value), sizeof(value));
}

bool HdfSbufWriteString(struct HdfSBuf *sbuf, const char *value)
{
    if (sbuf == NULL) {
        HDF_LOGE("%s:input null", __func__);
        return false;
    }

    return HdfSbufWriteBuffer(sbuf, value, value ? (strlen(value) + 1) : 0);
}

bool HdfSbufReadUint64(struct HdfSBuf *sbuf, uint64_t *value)
{
    return HdfSbufRead(sbuf, (uint8_t *)(value), sizeof(*value));
}

bool HdfSbufReadUint32(struct HdfSBuf *sbuf, uint32_t *value)
{
    return HdfSbufRead(sbuf, (uint8_t *)(value), sizeof(*value));
}

bool HdfSbufReadUint16(struct HdfSBuf *sbuf, uint16_t *value)
{
    return HdfSbufRead(sbuf, (uint8_t *)(value), sizeof(*value));
}

bool HdfSbufReadUint8(struct HdfSBuf *sbuf, uint8_t *value)
{
    return HdfSbufRead(sbuf, (uint8_t *)(value), sizeof(*value));
}

bool HdfSbufReadInt64(struct HdfSBuf *sbuf, int64_t *value)
{
    return HdfSbufRead(sbuf, (uint8_t *)(value), sizeof(*value));
}

bool HdfSbufReadInt32(struct HdfSBuf *sbuf, int32_t *value)
{
    return HdfSbufRead(sbuf, (uint8_t *)(value), sizeof(*value));
}

bool HdfSbufReadInt16(struct HdfSBuf *sbuf, int16_t *value)
{
    return HdfSbufRead(sbuf, (uint8_t *)(value), sizeof(*value));
}

bool HdfSbufReadInt8(struct HdfSBuf *sbuf, int8_t *value)
{
    return HdfSbufRead(sbuf, (uint8_t *)(value), sizeof(*value));
}

const char *HdfSbufReadString(struct HdfSBuf *sbuf)
{
    if (sbuf == NULL) {
        HDF_LOGE("%s:input null", __func__);
        return NULL;
    }
    /* this length contains '\0' at the end.  */
    int32_t strLen = 0;
    if (!HdfSbufReadInt32(sbuf, &strLen) || strLen <= 0) {
        return NULL;
    }
    size_t alignSize = HdfSbufGetAlignSize(strLen);
    if (strLen > INT16_MAX || alignSize > HdfSbufGetLeftReadSize(sbuf)) {
        (void)HdfSbufReadRollback(sbuf, sizeof(int32_t));
        return NULL;
    }

    char *str = (char *)(sbuf->data + sbuf->readPos);
    sbuf->readPos += alignSize;
    /* force set '\0' at end of the string */
    str[strLen - 1] = '\0';
    return str;
}

struct HdfSBuf *HdfSBufObtainDefaultSize()
{
    return HdfSBufObtain(HDF_SBUF_GROW_SIZE_DEFAULT);
}

struct HdfSBuf *HdfSBufObtain(size_t capacity)
{
    if (capacity > HDF_SBUF_MAX_SIZE) {
        HDF_LOGE("%s: buf size over limit", __func__);
        return NULL;
    }
    struct HdfSBuf *sbuf = (struct HdfSBuf *)OsalMemAlloc(sizeof(struct HdfSBuf));
    if (sbuf == NULL) {
        HDF_LOGE("instance usbuf failure");
        return NULL;
    }

    sbuf->data = (uint8_t *)OsalMemCalloc(capacity);
    if (sbuf->data == NULL) {
        OsalMemFree(sbuf);
        HDF_LOGE("sbuf obtain oom, size=%u", (uint32_t)capacity);
        return NULL;
    }
    sbuf->capacity = capacity;
    sbuf->writePos = 0;
    sbuf->readPos = 0;
    sbuf->isBind = false;
    return sbuf;
}

struct HdfSBuf *HdfSBufBind(uintptr_t base, size_t size)
{
    /* require 4 byte alignment for base */
    if ((base & 0x3) != 0) {
        HDF_LOGE("Base is not align for 4-byte");
        return NULL;
    }
    struct HdfSBuf *sbuf = (struct HdfSBuf *)OsalMemAlloc(sizeof(struct HdfSBuf));
    if (sbuf == NULL) {
        HDF_LOGE("%s: oom", __func__);
        return NULL;
    }

    sbuf->data = (uint8_t *)base;
    sbuf->capacity = size;
    sbuf->writePos = size;
    sbuf->readPos = 0;
    sbuf->isBind = true;
    return sbuf;
}

struct HdfSBuf *HdfSBufCopy(const struct HdfSBuf *sbuf)
{
    if (sbuf == NULL || sbuf->data == NULL) {
        return NULL;
    }

    struct HdfSBuf *new = HdfSBufObtain(sbuf->capacity);
    if (new == NULL) {
        return NULL;
    }
    new->capacity = sbuf->capacity;
    new->readPos = 0;
    new->writePos = sbuf->writePos;
    if (memcpy_s(new->data, new->capacity, sbuf->data, sbuf->capacity) != EOK) {
        HdfSBufRecycle(new);
        return NULL;
    }

    return new;
}

struct HdfSBuf *HdfSBufMove(struct HdfSBuf *sbuf)
{
    if (sbuf == NULL) {
        return NULL;
    }

    struct HdfSBuf *new = OsalMemCalloc(sizeof(struct HdfSBuf));
    if (new == NULL) {
        return NULL;
    }
    new->capacity = sbuf->capacity;
    new->readPos = 0;
    new->writePos = sbuf->writePos;
    new->data = sbuf->data;

    sbuf->data = NULL;
    sbuf->capacity = 0;
    HdfSbufFlush(sbuf);

    return new;
}

void HdfSbufTransDataOwnership(struct HdfSBuf *sbuf)
{
    if (sbuf == NULL) {
        return;
    }

    sbuf->isBind = false;
}
void HdfSBufRecycle(struct HdfSBuf *sbuf)
{
    if (sbuf != NULL) {
        if (sbuf->data != NULL && !sbuf->isBind) {
            OsalMemFree(sbuf->data);
        }
        OsalMemFree(sbuf);
    }
}
