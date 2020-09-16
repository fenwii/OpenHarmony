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

#include "osal_file.h"
#include "fs/file.h"
#include "unistd.h"
#include "limits.h"
#include "sys/stat.h"
#include "hdf_log.h"

#define HDF_LOG_TAG osal_file

int32_t OsalFileOpen(OsalFile *file, const char *path, int flags, uint32_t rights)
{
    int32_t fd = -1;
    char pathName[PATH_MAX + 1] = {0};

    if (file == NULL || path == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    file->realFile = (void *)(uintptr_t)fd;

    if (realpath(path, pathName) == NULL) {
        HDF_LOGE("%s file name is invalid\n", __func__);
        return HDF_FAILURE;
    }

    fd = open(pathName, flags, rights);
    if (fd < 0) {
        HDF_LOGE("%s open file fail %d %d %d", __func__, flags, rights, errno);
        return HDF_FAILURE;
    }

    file->realFile = (void *)(uintptr_t)fd;
    return HDF_SUCCESS;
}

ssize_t OsalFileWrite(OsalFile *file, const void *string, uint32_t length)
{
    ssize_t ret;

    if (file == NULL || (int32_t)(uintptr_t)file->realFile == -1 || string == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = write((int32_t)(uintptr_t)file->realFile, string, length);
    if (ret < 0) {
        HDF_LOGE("%s write file fail %d %d", __func__, length, errno);
        return HDF_FAILURE;
    }

    return ret;
}

void OsalFileClose(OsalFile *file)
{
    if (file == NULL || (int32_t)(uintptr_t)file->realFile == -1) {
        HDF_LOGE("%s invalid param", __func__);
        return;
    }

    close((int32_t)(uintptr_t)file->realFile);
    file->realFile = (void *)(uintptr_t)-1;
}

ssize_t OsalFileRead(OsalFile *file, void *buf, uint32_t length)
{
    ssize_t ret;

    if (file == NULL || (int32_t)(uintptr_t)file->realFile == -1 || buf == NULL) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = read((int32_t)(uintptr_t)file->realFile, buf, length);
    if (ret < 0) {
        HDF_LOGE("%s read file fail %d %d", __func__, length, errno);
        return HDF_FAILURE;
    }

    return ret;
}

off_t OsalFileLseek(OsalFile *file, off_t offset, int32_t whence)
{
    off_t ret;

    if (file == NULL || (int32_t)(uintptr_t)file->realFile == -1) {
        HDF_LOGE("%s invalid param", __func__);
        return HDF_ERR_INVALID_PARAM;
    }

    ret = lseek((int32_t)(uintptr_t)file->realFile, offset, whence);
    if (ret < 0) {
        HDF_LOGE("%s lseek file fail %d %d %d", __func__, offset, whence, errno);
        return HDF_FAILURE;
    }

    return ret;
}

