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

#include "mc_file.h"

#ifdef _LITEOS
#include "securec.h"

FileOperations g_MCFileOp = {
    MCOpen,
    MCClose,
    MCWrite,
    MCRead,
    MCSeek,
    MCUnlink,
    MCStatFD,
    MCStat,
    MCSync,
    MCDataSync,
    MCMakeDir,
    MCOpenDir,
    MCReadDir,
    MCCloseDir,
    MCRemoveDir,
    MCRename,
};

void MCFileInit()
{
    SetFileOp(&g_MCFileOp);
}

int32_t MCOpen(const char* path, int32_t oflag)
{
    int32_t mode = DEFAULT_FILE_PERMISSION;
    return open(path, oflag, mode);
}

int32_t MCClose(int32_t handle)
{
    return close(handle);
}

int32_t MCWrite(int32_t handle, const void* buf, uint32_t nbyte)
{
    return write(handle, buf, nbyte);
}

const int32_t MAX_FRAGMENT_FOR_FILE = 3 * 1024; // 3: means 3k
int32_t MCRead(int32_t handle, void* buf, uint32_t nbyte)
{
    int32_t readSize = 0;
    uint8_t* readBuf = (uint8_t*)buf;
    while (nbyte >= MAX_FRAGMENT_FOR_FILE) {
        int32_t ret = read(handle, readBuf, MAX_FRAGMENT_FOR_FILE);
        if (ret != MAX_FRAGMENT_FOR_FILE) {
            return ret;
        }
        nbyte -= MAX_FRAGMENT_FOR_FILE;
        readSize += MAX_FRAGMENT_FOR_FILE;
        readBuf += MAX_FRAGMENT_FOR_FILE;
    }

    if (nbyte > 0) {
        int32_t ret = read(handle, readBuf, nbyte);
        if (ret != nbyte) {
            return ret;
        }
        readSize += nbyte;
    }

    return readSize;
}

off_t MCSeek(int32_t handle, off_t offset, int32_t whence)
{
    return lseek(handle, offset, whence);
}

int32_t MCUnlink(const char* path)
{
    return unlink(path);
}

int32_t MCStatFD(int32_t handle, FileStatInfo* buf)
{
    if (buf == NULL) {
        return FILE_RET_FAIL;
    }
    struct stat mcStat = {0};
    int32_t ret = fstat(handle, &mcStat);
    if (ret == 0) {
        buf->size = mcStat.st_size;
    }
    return ret;
}

int32_t MCStat(const char* path, FileStatInfo* buf)
{
    if (buf == NULL) {
        return FILE_RET_FAIL;
    }
    struct stat mcStat = {0};
    int32_t ret = stat(path, &mcStat);
    if (ret == 0) {
        buf->size = mcStat.st_size;
    }
    return ret;
}

int32_t MCSync(int32_t handle)
{
    return fsync(handle);
}

int32_t MCDataSync(int32_t handle)
{
    return FILE_RET_FAIL;
}

int32_t MCMakeDir(const char* path)
{
    return mkdir(path, DEFAULT_FILE_PERMISSION);
}

void* MCOpenDir(const char* path)
{
    return opendir(path);
}

int32_t MCReadDir(void* dirp, FileDirentInfo* dirInfo)
{
    dirent* ret = readdir((DIR*)dirp);
    if (ret != NULL) {
        if (sprintf_s(dirInfo->name, UI_NAME_MAX + 1, "%s", ret->d_name) < 0) {
            return FILE_RET_FAIL;
        }
        return FILE_RET_OK;
    }
    return FILE_RET_FAIL;
}

int32_t MCCloseDir(void* dirp)
{
    return closedir((DIR*)dirp);
}

int32_t MCRemoveDir(const char* path)
{
    return rmdir(path);
}

int32_t MCRename(const char* oldName, const char* newName)
{
    return FILE_RET_FAIL;
}

#endif
