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

#include "app_file.h"
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "app_centraldirectory.h"

static int g_memoryPageSize = 0;
int InitVerify(FileRead *file, const char *filePath, int *handle)
{
    if (handle == NULL || file == NULL || filePath == NULL) {
        LOG_ERROR("file open error");
        return V_ERR_FILE_OPEN;
    }
    char *path = APPV_MALLOC(PATH_MAX + 1);
    if (path == NULL) {
        LOG_ERROR("path malloc error");
        return V_ERR_MALLOC;
    }
    if ((strlen(filePath) > PATH_MAX) || (NULL == realpath(filePath, path))) {
        APPV_FREE(path);
        LOG_ERROR("file path error");
        return V_ERR_FILE_OPEN;
    }
    *handle = open(path, O_RDONLY, 0);
    if (*handle < 0) {
        APPV_FREE(path);
        LOG_PRINT_STR("file open error %s", path);
        return V_ERR_FILE_OPEN;
    }
    if (g_memoryPageSize == 0) {
        g_memoryPageSize = sysconf(_SC_PAGESIZE);
    }
    if (g_memoryPageSize <= 0) {
        LOG_ERROR("MAP_FAILED %d", g_memoryPageSize);
        APPV_FREE(path);
        return V_ERR_FILE_STAT;
    }
    file->len = lseek(*handle, 0, SEEK_END);
    file->fp = *handle;
    APPV_FREE(path);
    return V_OK;
}

int HapMMap(int bufCapacity, int offset, MmapInfo *mmapInfo, const FileRead *file)
{
    if (mmapInfo == NULL || file == NULL || bufCapacity <= 0) {
        return MMAP_FAILED;
    }
    mmapInfo->mapAddr = (char*)(MAP_FAILED);
    if (file->fp == FILE_OPEN_FAIL_ERROR_NUM) {
        return FILE_IS_CLOSE;
    }
    if (offset < 0 || offset > file->len - bufCapacity) {
        return READ_OFFSET_OUT_OF_RANGE;
    }
    lseek(file->fp, offset, SEEK_SET);
    if (g_memoryPageSize == 0) {
        return MMAP_FAILED;
    }
    mmapInfo->mmapPosition = (offset / g_memoryPageSize) * g_memoryPageSize;
    mmapInfo->readMoreLen = (int)(offset - mmapInfo->mmapPosition);
    mmapInfo->mmapSize = bufCapacity + mmapInfo->readMoreLen;
    mmapInfo->mapAddr = (char*)(mmap(NULL, mmapInfo->mmapSize, PROT_READ,
        MAP_SHARED | MAP_POPULATE, file->fp, mmapInfo->mmapPosition));
    if (mmapInfo->mapAddr == MAP_FAILED) {
        LOG_ERROR("MAP_FAILED");
        return MMAP_FAILED;
    }
    return V_OK;
}

void HapMUnMap(char *mapAddr, int mmapSize)
{
    if (mapAddr == NULL || mmapSize <= 0) {
        return;
    }
    munmap(mapAddr, mmapSize);
}
