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

#ifndef GRAPHIC_LITE_FILE_H
#define GRAPHIC_LITE_FILE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef _LITEOS
#include <fcntl.h>
#include <sys/types.h>
#else
#include "mc_fs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define FILE_SEEK_CUR 1
#define FILE_SEEK_END 2
#define FILE_SEEK_SET 0

#define DEFAULT_FILE_PERMISSION 0666 // default file permission when creat file
#define UI_NAME_MAX 256                 // max path length

#define FILE_RET_OK 0
#define FILE_RET_FAIL (-1)

#ifdef _LITEOS
#define _O_BINARY 0

typedef long off_t;
#endif

typedef struct FileStatInfo_ {
#ifndef _LITEOS
    uint32_t dev;
    uint16_t ino;
    uint16_t mode;
    int16_t nlink;
    int16_t uid;
    int16_t gid;
    uint32_t rdev;
    off_t size;
    int64_t atime;
    int64_t mtime;
    int64_t ctime;
#else
    char attr;
    unsigned short date;
    unsigned short time;
    int size; /* total size, in bytes */
#endif
} FileStatInfo;

typedef struct FileDirentInfo_ {
    uint16_t ino;            /* inode number */
    off_t off;               /* not an offset; see NOTES */
    uint16_t reclen;         /* length of this record */
    uint8_t type;            /* type of file; not supported by all filesystem types */
    char name[UI_NAME_MAX + 1]; /* filename */
} FileDirentInfo;

typedef struct FileOperations_ {
    int32_t (*open)(const char* path, int32_t oflag);
    int32_t (*close)(int32_t handle);
    int32_t (*write)(int32_t handle, const void* buf, uint32_t nbyte);
    int32_t (*read)(int32_t handle, void* buf, uint32_t nbyte);
    off_t (*lseek)(int32_t handle, off_t offset, int32_t whence);
    int32_t (*unlink)(const char* path);
    int32_t (*fstat)(int32_t handle, FileStatInfo* buf);
    int32_t (*stat)(const char* path, FileStatInfo* buf);
    int32_t (*fsync)(int32_t handle);
    int32_t (*fdatasync)(int32_t handle);
    int32_t (*mkdir)(const char* path);
    void* (*opendir)(const char* path);
    int32_t (*readdir)(void* dirp, FileDirentInfo* dirInfo);
    int32_t (*closedir)(void* dirp);
    int32_t (*rmdir)(const char* path);
    int32_t (*rename)(const char* oldName, const char* newName);
} FileOperations;

extern FileOperations* g_fileOp;

/**
 * @brief init file operations
 *
 */
void FileInit();

/**
 * @brief set file operations by different file system.
 *
 * @param [in] op file system operation.
 */
static inline void SetFileOp(FileOperations* op)
{
    g_fileOp = op;
}

/**
 * @brief open file
 *
 * @param [in] path file path.
 * @param [in] oflags open file flag. if creat file, default file permission
 *             0666 in linux file, _S_IREAD | _S_IWRITE in win file.
 * @return file fd.
 */
static inline int32_t FileOpen(const char* path, int32_t oflag)
{
    if (g_fileOp != NULL && g_fileOp->open != NULL) {
        return g_fileOp->open(path, oflag);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief close file
 *
 * @param [in] handle file handle.
 * @return close result, 0 OK, -1 fail.
 */
static inline int32_t FileClose(int32_t handle)
{
    if (g_fileOp != NULL && g_fileOp->close != NULL) {
        return g_fileOp->close(handle);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief write buf in file
 *
 * @param [in] handle file handle.
 * @param [in] buf buffer to write.
 * @param [in] nbyte count of buffer.
 * @return count of buf write in file.
 */
static inline int32_t FileWrite(int32_t handle, const void* buf, uint32_t nbyte)
{
    if (g_fileOp != NULL && g_fileOp->write != NULL) {
        return g_fileOp->write(handle, buf, nbyte);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief read buf from file.
 *
 * @param [in] handle file handle.
 * @param [in] buf buffer to read.
 * @param [in] nbyte count of buffer.
 * @return count of buf read in file.
 */
static inline int32_t FileRead(int32_t handle, void* buf, uint32_t nbyte)
{
    if (g_fileOp != NULL && g_fileOp->read != NULL) {
        return g_fileOp->read(handle, buf, nbyte);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief move file read/write position
 *
 * @param [in] handle file handle.
 * @param [in] offset number to move.
 * @param [in] whence mode @see FILE_SEEK_SET, FILE_SEEK_CUR, FILE_SEEK_END.
 * @return the offset location as measured in bytes from the beginning of the file,
 *         -1 is on error.
 */
static inline off_t FileSeek(int32_t handle, off_t offset, int32_t whence)
{
    if (g_fileOp != NULL && g_fileOp->lseek != NULL) {
        return g_fileOp->lseek(handle, offset, whence);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief unlink file
 *
 * @param [in] path file path.
 * @return unlink result, 0 OK, -1 is on error.
 */
static inline int32_t FileUnlink(const char* path)
{
    if (g_fileOp != NULL && g_fileOp->unlink != NULL) {
        return g_fileOp->unlink(path);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief get file stat by fd
 *
 * @param [in] handle file handle.
 * @param [out] buf file stat info.
 * @return fstat result, 0 OK, -1 is on error.
 */
static inline int32_t FileFdStat(int32_t handle, FileStatInfo* buf)
{
    if (g_fileOp != NULL && g_fileOp->fstat != NULL) {
        return g_fileOp->fstat(handle, buf);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief get file stat by path
 *
 * @param [in] handle file handle.
 * @param [out] buf file stat info.
 * @return stat result, 0 OK, -1 is on error..
 */
static inline int32_t FileStat(const char* path, FileStatInfo* buf)
{
    if (g_fileOp != NULL && g_fileOp->stat != NULL) {
        return g_fileOp->stat(path, buf);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief sync data into file
 *
 * @param [in] handle file handle.
 * @return fsync result, 0 OK, -1 is on error.
 */
static inline int32_t FileSync(int32_t handle)
{
    if (g_fileOp != NULL && g_fileOp->fsync != NULL) {
        return g_fileOp->fsync(handle);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief sync data into file
 *
 * @param [in] handle file handle.
 * @return fdatasync result, 0 OK, -1 is on error.
 */
static inline int32_t FileDataSync(int32_t handle)
{
    if (g_fileOp != NULL && g_fileOp->fdatasync != NULL) {
        return g_fileOp->fdatasync(handle);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief make path
 *
 * @param [in] path file path.
 * @return mkdir result, 0 OK, -1 is on error.
 */
static inline int32_t FileMakeDir(const char* path)
{
    if (g_fileOp != NULL && g_fileOp->mkdir != NULL) {
        return g_fileOp->mkdir(path);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief open path
 *
 * @param [in] path file path.
 * @return returns a pointer to the directory stream.
 */
static inline void* FileOpenDir(const char* path)
{
    if (g_fileOp != NULL && g_fileOp->opendir != NULL) {
        return g_fileOp->opendir(path);
    }
    return NULL;
}

/**
 * @brief read path
 *
 * @param [in] dirp pointer to the directory stream.
 * @param [out] dirInfo  dir info.
 * @return readdir result, 0 OK, -1 is on error.
 */
static inline int32_t FileReadDir(void* dirp, FileDirentInfo* dirInfo)
{
    if (g_fileOp != NULL && g_fileOp->readdir != NULL) {
        return g_fileOp->readdir(dirp, dirInfo);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief close dir
 *
 * @param [in] dirp pointer to the directory stream.
 * @return closedir result, 0 OK, -1 -1 is on error.
 */
static inline int32_t FileCloseDir(void* dirp)
{
    if (g_fileOp != NULL && g_fileOp->closedir != NULL) {
        return g_fileOp->closedir(dirp);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief remove dir
 *
 * @param [in] path file path.
 * @return rmdir result, 0 OK, -1 is on error.
 */
static inline int32_t FileRemoveDir(const char* path)
{
    if (g_fileOp != NULL && g_fileOp->rmdir != NULL) {
        return g_fileOp->rmdir(path);
    }
    return FILE_RET_FAIL;
}

/**
 * @brief rename file
 *
 * @param [in] oldName old file path.
 * @param [in] newName new file path.
 * @return rename result, 0 OK, -1 is on error.
 */
static inline int32_t FileRename(const char* oldName, const char* newName)
{
    if (g_fileOp != NULL && g_fileOp->rename != NULL) {
        return g_fileOp->rename(oldName, newName);
    }
    return FILE_RET_FAIL;
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // GRAPHIC_LITE_FILE_H