/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "app_centraldirectory.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "app_common.h"
#include "mbedtls/base64.h"
#include "mbedtls/md.h"
#include "mbedtls/pk.h"
#include "mbedtls/x509_crt.h"
#include "mbedtls_pkcs7.h"
#include "securec.h"

void HapPutByte(const HapBuf *hapBuffer, int offset, char value)
{
    if (hapBuffer == NULL || hapBuffer->buffer == NULL) {
        return;
    }
    if ((offset >= 0) && (hapBuffer->len - offset >= (int)(sizeof(value)))) {
        *(char *)((char *)hapBuffer->buffer + offset) = value;
    }
    return;
}

void HapPutData(const HapBuf *hapBuffer, int offset, const unsigned char *data, int len)
{
    if (hapBuffer == NULL || hapBuffer->buffer == NULL) {
        return;
    }
    if ((data != NULL) && (offset >= 0) && len > 0 && ((hapBuffer->len - offset) >= len)) {
        if (memcpy_s((hapBuffer->buffer + offset), (hapBuffer->len - offset), data, len) != EOK) {
            LOG_ERROR("memcpy_s fail");
        }
    }
}

void HapSetInt32(const HapBuf *buffer, int offset, int value)
{
    if (value < 0 || value > INT_MAX) {
        LOG_ERROR("int32 value of out range: %d", value);
        return;
    }
    if (buffer == NULL || buffer->buffer == NULL) {
        return;
    }
    if ((offset >= 0) && ((buffer->len - offset) >= (int)(sizeof(value)))) {
        HapPutInt32((unsigned char *)buffer->buffer + offset, buffer->len - offset, (int)(value));
    }
    return;
}

bool CreateHapBuffer(HapBuf *hapBuffer, int len)
{
    if (hapBuffer == NULL || len <= 0) {
        LOG_ERROR("create buf fail, buf is null");
        return false;
    }
    hapBuffer->buffer = APPV_MALLOC(len);
    if (hapBuffer->buffer == NULL) {
        LOG_ERROR("create buf fail");
        return false;
    }
    hapBuffer->len = len;
    return true;
}

void ClearHapBuffer(HapBuf *hapBuffer)
{
    if (hapBuffer == NULL || hapBuffer->buffer == NULL) {
        return;
    }
    (void)memset_s(hapBuffer->buffer, hapBuffer->len, 0, hapBuffer->len);
    APPV_FREE(hapBuffer->buffer);
    hapBuffer->len = 0;
}

static bool GetEocd(const FileRead *hapFile, HapEocd *hapEocd, int *eocdOffset)
{
    MmapInfo mmapInfo = {0};
    if (hapFile->len <= sizeof(MinEocd)) {
        return false;
    }
    int ret = HapMMap(hapFile->len, 0, &mmapInfo, hapFile);
    if (ret != V_OK) {
        LOG_ERROR("mmap not ok");
        return false;
    }
    char *fileStart = (char *)(mmapInfo.mapAddr + mmapInfo.readMoreLen);
    if (HapGetShort((unsigned char*)fileStart + hapFile->len - sizeof(short), sizeof(short)) == 0 &&
        HapGetInt((unsigned char*)fileStart + hapFile->len - sizeof(MinEocd), sizeof(int)) == HAP_EOCD_MAGIC) {
        if (memcpy_s(&hapEocd->eocdHead, sizeof(MinEocd),
            fileStart + hapFile->len - sizeof(MinEocd), sizeof(char) * sizeof(MinEocd)) != EOK) {
            HapMUnMap(mmapInfo.mapAddr, mmapInfo.mmapSize);
            LOG_ERROR("copy error");
            return false;
        }
        HapMUnMap(mmapInfo.mapAddr, mmapInfo.mmapSize);
        *eocdOffset = hapFile->len - sizeof(MinEocd);
        return true;
    }
    // only a few haps have comment and use this branch
    int maxReadLen = ((unsigned int)(hapFile->len - sizeof(MinEocd)) > UINT16_MAX_VALUE) ?
        UINT16_MAX_VALUE : (hapFile->len - sizeof(MinEocd));
    fileStart += hapFile->len - sizeof(MinEocd) - maxReadLen;
    LOG_INFO("maxReadLen %d", maxReadLen);
    for (int i = 0; i < maxReadLen; i++) {
        if ((HapGetShort((unsigned char*)fileStart + i + sizeof(MinEocd) - sizeof(short),
            sizeof(short)) == (maxReadLen - i)) &&
            (HapGetInt((unsigned char*)fileStart + i, sizeof(int)) == HAP_EOCD_MAGIC)) {
            if (memcpy_s(&hapEocd->eocdHead, sizeof(MinEocd),
                fileStart + i, sizeof(char) * sizeof(MinEocd)) != EOK) {
                HapMUnMap(mmapInfo.mapAddr, mmapInfo.mmapSize);
                LOG_ERROR("copy error");
                return false;
            }
            HapMUnMap(mmapInfo.mapAddr, mmapInfo.mmapSize);
            LOG_INFO("comment num %d", maxReadLen - i);
            *eocdOffset = hapFile->len - sizeof(MinEocd) - (maxReadLen - i);
            return true;
        }
    }
    LOG_ERROR("can not find eocd");
    HapMUnMap(mmapInfo.mapAddr, mmapInfo.mmapSize);
    return false;
}

bool FindSignature(const FileRead *hapFile, SignatureInfo *signInfo)
{
    if (hapFile == NULL || signInfo == NULL) {
        return false;
    }
    int eocdOffset = 0;
    HapEocd hapEocd = {0};
    if (!GetEocd(hapFile, &hapEocd, &eocdOffset)) {
        LOG_ERROR("find Eocd fail");
        return false;
    }
    signInfo->hapEocdOffset = eocdOffset;
    signInfo->hapEocdSize = hapFile->len - eocdOffset;
    signInfo->hapCoreDirOffset = HapGetInt((unsigned char*)(&(hapEocd.eocdHead.coreDirOffset)), sizeof(int));
    if (signInfo->hapCoreDirOffset <= 0 || signInfo->hapCoreDirOffset >= eocdOffset ||
        signInfo->hapEocdSize <= 0 || signInfo->hapEocdOffset <= 0) {
        LOG_ERROR("core dir error");
        return false;
    }
    return true;
}

int ReadFileFullyFromOffset(const HapBuf *buffer, int offset, const FileRead *file)
{
    if (buffer == NULL || buffer->buffer == NULL || file == NULL) {
        return DEST_BUFFER_IS_NULL;
    }
    if (offset < 0 || offset > file->len) {
        return READ_OFFSET_OUT_OF_RANGE;
    }
    lseek(file->fp, offset, SEEK_SET);
    int readLen = read(file->fp, buffer->buffer, buffer->len);
    if (readLen != buffer->len) {
        LOG_ERROR("file read error %d --- %d", readLen, buffer->len);
        return READ_OFFSET_OUT_OF_RANGE;
    }
    return buffer->len;
}
