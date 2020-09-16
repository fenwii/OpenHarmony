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

#ifdef _WIN32

#include "win_file.h"

FileOperations g_winFileOp = {
    WinOpen,
    WinClose,
    WinWrite,
    WinRead,
    WinSeek,
    WinUnlink,
    WinStatFD,
    WinStat,
    WinSync,
    WinDataSync,
    WinMakeDir,
    NULL,
    NULL,
    NULL,
    WinRemoveDir,
    WinRename,
};

void WinFileInit()
{
    SetFileOp(&g_winFileOp);
}

int32_t WinOpen(const char* path, int32_t oflag)
{
    return _open(path, oflag, _S_IREAD | _S_IWRITE);
}

int32_t WinClose(int32_t handle)
{
    return _close(handle);
}

int32_t WinWrite(int32_t handle, const void* buf, uint32_t nbyte)
{
    return _write(handle, buf, nbyte);
}

int32_t WinRead(int32_t handle, void* buf, uint32_t nbyte)
{
    return _read(handle, buf, nbyte);
}

off_t WinSeek(int32_t handle, off_t offset, int32_t whence)
{
    return _lseek(handle, offset, whence);
}

int32_t WinUnlink(const char* path)
{
    return _unlink(path);
}

int32_t WinStatFD(int32_t handle, FileStatInfo* buf)
{
    if (buf == NULL) {
        return FILE_RET_FAIL;
    }
    struct stat fileStat = {0};
    int32_t ret = fstat(handle, &fileStat);
    if (ret == 0) {
        buf->dev = fileStat.st_dev;
        buf->ino = fileStat.st_ino;
        buf->mode = fileStat.st_mode;
        buf->nlink = fileStat.st_nlink;
        buf->uid = fileStat.st_uid;
        buf->gid = fileStat.st_gid;
        buf->rdev = fileStat.st_rdev;
        buf->size = fileStat.st_size;
        buf->atime = fileStat.st_atime;
        buf->mtime = fileStat.st_mtime;
        buf->ctime = fileStat.st_ctime;
    }
    return ret;
}

int32_t WinStat(const char* path, FileStatInfo* buf)
{
    if (buf == NULL) {
        return FILE_RET_FAIL;
    }
    struct stat fileStat = {0};
    int32_t ret = stat(path, &fileStat);
    if (ret == 0) {
        buf->dev = fileStat.st_dev;
        buf->ino = fileStat.st_ino;
        buf->mode = fileStat.st_mode;
        buf->nlink = fileStat.st_nlink;
        buf->uid = fileStat.st_uid;
        buf->gid = fileStat.st_gid;
        buf->rdev = fileStat.st_rdev;
        buf->size = fileStat.st_size;
        buf->atime = fileStat.st_atime;
        buf->mtime = fileStat.st_mtime;
        buf->ctime = fileStat.st_ctime;
    }
    return ret;
}

int32_t WinSync(int32_t handle)
{
    return _commit(handle);
}

int32_t WinDataSync(int32_t handle)
{
    return _commit(handle);
}

int32_t WinMakeDir(const char* path)
{
    return _mkdir(path);
}

int32_t WinRemoveDir(const char* path)
{
    return _rmdir(path);
}

int32_t WinRename(const char* oldName, const char* newName)
{
    return rename(oldName, newName);
}

#endif // _WIN32
