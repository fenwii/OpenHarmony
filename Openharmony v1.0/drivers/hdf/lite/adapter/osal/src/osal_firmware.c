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

#include "osal_firmware.h"
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include "fs/file.h"
#include "hdf_log.h"
#include "osal_mem.h"

#define HDF_LOG_TAG osal_fw
#define HDF_FW_BLOCK_SIZE 64

struct OsalFwDesc {
    int32_t fd;
    uint8_t *buff;
    uint32_t offset;
    int32_t openFlag;
};

int32_t OsalRequestFirmware(struct OsalFirmware *fwPara, const char *fwName, void *device)
{
    struct OsalFwDesc *fw = NULL;
    uint8_t *base = NULL;
    struct stat fwStat;
    char path[PATH_MAX + 1] = {0};
    int32_t fd = -1;

    (void)device;
    if (fwPara == NULL || fwName == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    fwPara->fwSize = 0;
    fwPara->para = NULL;

    if (realpath(fwName, path) == NULL) {
        HDF_LOGE("%s file name is invalid\n", __func__);
        return HDF_FAILURE;
    }

    fd = open(path, O_RDONLY, S_IREAD);
    if (fd == -1) {
        HDF_LOGE("%s open file fail %d", __func__, errno);
        return HDF_FAILURE;
    }

    if (fstat(fd, &fwStat) == -1) {
        HDF_LOGE("%s fstat file fail %d", __func__, errno);
        close(fd);
        return HDF_FAILURE;
    }

    base = (uint8_t *)OsalMemCalloc(sizeof(*fw) + HDF_FW_BLOCK_SIZE);
    if (base == NULL) {
        HDF_LOGE("%s malloc fail", __func__);
        close(fd);
        return HDF_ERR_MALLOC_FAIL;
    }

    fw = (struct OsalFwDesc *)base;
    fw->fd = fd;
    fwPara->fwSize = (uint32_t)fwStat.st_size;

    fw->openFlag = true;
    fw->buff = base + sizeof(*fw);
    fw->offset = 0;

    fwPara->para = (void *)fw;

    return HDF_SUCCESS;
}

int32_t OsalSeekFirmware(struct OsalFirmware *fwPara, uint32_t offset)
{
    struct OsalFwDesc *fw = NULL;

    if (fwPara == NULL || offset >= fwPara->fwSize || fwPara->para == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    fw = (struct OsalFwDesc *)fwPara->para;
    fw->offset = offset;

    return HDF_SUCCESS;
}

int32_t OsalReadFirmware(struct OsalFirmware *fwPara, struct OsalFwBlock *block)
{
    int32_t readOffset;
    int32_t readSize;
    struct OsalFwDesc *fw = NULL;

    if (fwPara == NULL || fwPara->para == NULL || block == NULL) {
        HDF_LOGE("%s invalid param",  __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    fw = (struct OsalFwDesc *)fwPara->para;
    if (fw->openFlag == false) {
        HDF_LOGE("%s file do not open",  __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    block->data = fw->buff;
    block->endFlag = false;
    block->dataSize = HDF_FW_BLOCK_SIZE;

    if (fw->offset >= fwPara->fwSize) {
        HDF_LOGE("%s file offset invalid %d %d", __func__, fw->offset, fwPara->fwSize);
        return HDF_ERR_INVALID_PARAM;
    }

    if (fw->offset + block->dataSize >= fwPara->fwSize) {
        block->dataSize = fwPara->fwSize - fw->offset;
        block->endFlag = true;
    }

    if (fw->fd == -1) {
        HDF_LOGE("%s invalid file id",  __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    readOffset = lseek(fw->fd, fw->offset, SEEK_SET);
    if (readOffset != fw->offset) {
        HDF_LOGE("%s seek offset fail %d %d", __func__, readOffset, fw->offset);
        return HDF_FAILURE;
    }
    readSize = read(fw->fd, block->data, block->dataSize);
    if (readSize != block->dataSize) {
        HDF_LOGE("%s read file fail %d %d", __func__, readSize, block->dataSize);
        return HDF_FAILURE;
    }

    block->curOffset = fw->offset;
    fw->offset += block->dataSize;

    return HDF_SUCCESS;
}

int32_t OsalReleaseFirmware(struct OsalFirmware *fwPara)
{
    struct OsalFwDesc *fw = NULL;

    if (fwPara == NULL || fwPara->para == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    fw = (struct OsalFwDesc *)fwPara->para;
    if (fw->fd == -1) {
        HDF_LOGE("%s invalid file id",  __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    if (close(fw->fd) != 0) {
        HDF_LOGE("%s close fail %d",  __func__, errno);
        return HDF_FAILURE;
    }
    OsalMemFree(fwPara->para);
    fwPara->para = NULL;

    return HDF_SUCCESS;
}

