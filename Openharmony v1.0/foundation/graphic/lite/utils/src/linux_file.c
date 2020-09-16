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

#if defined __linux__ || defined __LITEOS__

#include "linux_file.h"
#include "securec.h"

FileOperations g_linuxFileOp = {
    LinuxOpen,
    LinuxClose,
    LinuxWrite,
    LinuxRead,
    LinuxSeek,
    LinuxUnlink,
    LinuxStatFD,
    LinuxStat,
    LinuxSync,
    LinuxDataSync,
    LinuxMakeDir,
    LinuxOpenDir,
    LinuxReadDir,
    LinuxCloseDir,
    LinuxRemoveDir,
    LinuxRename,
};

void LinuxFileInit()
{
    SetFileOp(&g_linuxFileOp);
}

int32_t LinuxOpen(const char* path, int32_t oflag)
{
    int32_t mode = DEFAULT_FILE_PERMISSION;
    return open(path, oflag, mode);
}

int32_t LinuxClose(int32_t handle)
{
    return close(handle);
}

int32_t LinuxWrite(int32_t handle, const void* buf, uint32_t nbyte)
{
    return write(handle, buf, nbyte);
}

int32_t LinuxRead(int32_t handle, void* buf, uint32_t nbyte)
{
    return read(handle, buf, nbyte);
}

off_t LinuxSeek(int32_t handle, off_t offset, int32_t whence)
{
    return lseek(handle, offset, whence);
}

int32_t LinuxUnlink(const char* path)
{
    return unlink(path);
}

int32_t LinuxStatFD(int32_t handle, FileStatInfo* buf)
{
    if (buf == NULL) {
        return FILE_RET_FAIL;
    }
    struct stat mcStat = {0};
    int32_t ret = fstat(handle, &mcStat);
    if (ret == 0) {
        buf->dev = mcStat.st_dev;
        buf->ino = mcStat.st_ino;
        buf->mode = mcStat.st_mode;
        buf->nlink = mcStat.st_nlink;
        buf->uid = mcStat.st_uid;
        buf->gid = mcStat.st_gid;
        buf->rdev = mcStat.st_rdev;
        buf->size = mcStat.st_size;
        buf->atime = mcStat.st_atime;
        buf->mtime = mcStat.st_mtime;
        buf->ctime = mcStat.st_ctime;
    }
    return ret;
}

int32_t LinuxStat(const char* path, FileStatInfo* buf)
{
    if (buf == NULL) {
        return FILE_RET_FAIL;
    }
    struct stat mcStat = {0};
    int32_t ret = stat(path, &mcStat);
    if (ret == 0) {
        buf->dev = mcStat.st_dev;
        buf->ino = mcStat.st_ino;
        buf->mode = mcStat.st_mode;
        buf->nlink = mcStat.st_nlink;
        buf->uid = mcStat.st_uid;
        buf->gid = mcStat.st_gid;
        buf->rdev = mcStat.st_rdev;
        buf->size = mcStat.st_size;
        buf->atime = mcStat.st_atime;
        buf->mtime = mcStat.st_mtime;
        buf->ctime = mcStat.st_ctime;
    }
    return ret;
}

int32_t LinuxSync(int32_t handle)
{
    return fsync(handle);
}

int32_t LinuxDataSync(int32_t handle)
{
    return fdatasync(handle);
}

int32_t LinuxMakeDir(const char* path)
{
    return mkdir(path, DEFAULT_FILE_PERMISSION);
}

void* LinuxOpenDir(const char* path)
{
    return opendir(path);
}

int32_t LinuxReadDir(void* dirp, FileDirentInfo* dirInfo)
{
    struct dirent* ret = readdir((DIR*)dirp);
    if (ret != NULL) {
        dirInfo->ino = ret->d_ino;
        dirInfo->off = ret->d_off;
        dirInfo->reclen = ret->d_reclen;
        dirInfo->type = ret->d_type;
        if (sprintf_s(dirInfo->name, UI_NAME_MAX + 1, "%s", ret->d_name) < 0) {
            return -1;
        }
        return 0;
    }
    return -1; // TO DO for errno
}

int32_t LinuxCloseDir(void* dirp)
{
    return closedir((DIR*)dirp);
}

int32_t LinuxRemoveDir(const char* path)
{
    return rmdir(path);
}

int32_t LinuxRename(const char* oldName, const char* newName)
{
    return rename(oldName, newName);
}

#endif
