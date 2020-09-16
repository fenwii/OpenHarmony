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

#include "nativeapi_fs_impl.h"
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <securec.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "nativeapi_config.h"

#define BUFFER_SIZE 512

static bool IsValidPath(const char *path)
{
    if ((path == NULL) || !strlen(path) || (strlen(path) > FILE_NAME_MAX_LEN)) {
        return false;
    }
    if (strpbrk(path, "\"*+,:;<=>\?[]|\x7F")) {
        return false;
    }
    return true;
}

static int GetRealPath(const char* originPath, char* trustPath, size_t tPathLen)
{
    if (realpath(originPath, trustPath) != NULL) {
        return NATIVE_SUCCESS;
    }
    if (errno == ENOENT) {
        if (strncpy_s(trustPath, tPathLen, originPath, strlen(originPath)) == EOK) {
            return NATIVE_SUCCESS;
        }
    }
    return ERROR_CODE_GENERAL;
}

static int RmdirRecursive(const char* fileName)
{
    if (!IsValidPath(fileName)) {
        return ERROR_CODE_PARAM;
    }
    int ret = ERROR_CODE_GENERAL;
    DIR *fileDir = opendir(fileName);
    if (fileDir == NULL) {
        return ret;
    }
    struct dirent *dir = readdir(fileDir);
    struct stat info = { 0 };
    char* fullPath = (char *)malloc(FILE_NAME_MAX_LEN + 1);
    if (fullPath == NULL) {
        closedir(fileDir);
        return ret;
    }
    while (dir != NULL) {
        if (memset_s(fullPath, FILE_NAME_MAX_LEN + 1, 0x0, FILE_NAME_MAX_LEN + 1) != EOK) {
            free(fullPath);
            closedir(fileDir);
            return ret;
        }
        if (sprintf_s(fullPath, FILE_NAME_MAX_LEN + 1, "%s/%s", fileName, dir->d_name) < 0) {
            free(fullPath);
            closedir(fileDir);
            return ret;
        }
        if (stat(fullPath, &info) != 0) {
            free(fullPath);
            closedir(fileDir);
            return ret;
        }
        if (S_ISDIR(info.st_mode)) {
            ret = RmdirRecursive(fullPath);
        } else {
            ret = unlink(fullPath);
        }
        if (ret != NATIVE_SUCCESS) {
            free(fullPath);
            closedir(fileDir);
            return ret;
        }
        dir = readdir(fileDir);
    }
    free(fullPath);
    closedir(fileDir);
    return rmdir(fileName);
}

static int MakeParent(const char* path, char* firstPath, size_t fPathLen, int* dirNum)
{
    char* fullPath = (char *)malloc(strlen(path) + 1);
    if (fullPath == NULL) {
        return ERROR_CODE_GENERAL;
    }
    if (strcpy_s(fullPath, strlen(path) + 1, path) != EOK) {
        free(fullPath);
        return ERROR_CODE_GENERAL;
    }
    int ret = NATIVE_SUCCESS;
    if (AccessImpl(fullPath) != NATIVE_SUCCESS) {
        char *sep = strrchr(fullPath, '/');
        if (sep != NULL) {
            *sep = 0;
            MakeParent(fullPath, firstPath, fPathLen, dirNum);
            *sep = '/';
        }
        (*dirNum)++;
        if (*dirNum > DIR_LEVEL) {
            free(fullPath);
            return ERROR_CODE_PARAM;
        }
        ret = mkdir(fullPath, S_IRUSR | S_IWUSR | S_IXUSR);
        if ((ret == NATIVE_SUCCESS) && (*dirNum == 1)) {
            if ((strcpy_s(firstPath, fPathLen, fullPath) != EOK)) {
                free(fullPath);
                return ERROR_CODE_GENERAL;
            }
        }
    }
    free(fullPath);
    return ret;
}

static int MkdirRecursive(const char* path)
{
    char* firstPath = (char *)malloc(FILE_NAME_MAX_LEN + 1);
    if (firstPath == NULL) {
        return ERROR_CODE_GENERAL;
    }
    if (memset_s(firstPath, FILE_NAME_MAX_LEN + 1, 0x0, FILE_NAME_MAX_LEN + 1) != EOK) {
        free(firstPath);
        return ERROR_CODE_GENERAL;
    }
    int dirNum = 0;
    int ret = MakeParent(path, firstPath, FILE_NAME_MAX_LEN + 1, &dirNum);
    if (ret != NATIVE_SUCCESS) {
        RmdirRecursive(firstPath);
    }
    free(firstPath);
    return ret;
}

static int DoCopyFile(int fdSrc, int fdDest)
{
    char *dataBuf = (char *)malloc(BUFFER_SIZE);
    if (dataBuf == NULL) {
        return ERROR_CODE_GENERAL;
    }
    int nLen = read(fdSrc, dataBuf, BUFFER_SIZE);
    while (nLen > 0) {
        if (write(fdDest, dataBuf, nLen) != nLen) {
            free(dataBuf);
            return ERROR_CODE_IO;
        }
        nLen = read(fdSrc, dataBuf, BUFFER_SIZE);
    }
    free(dataBuf);
    if (nLen < 0) {
        return ERROR_CODE_IO;
    }
    return NATIVE_SUCCESS;
}

int StatImpl(const char *path, struct stat *buf)
{
    if (!IsValidPath(path) || (buf == NULL)) {
        return ERROR_CODE_PARAM;
    }
    int ret = stat(path, buf);
    if (ret != NATIVE_SUCCESS) {
        return (-errno);
    }
    return NATIVE_SUCCESS;
}

int DeleteFileImpl(const char* src)
{
    if (!IsValidPath(src)) {
        return ERROR_CODE_PARAM;
    }
    int ret = unlink(src);
    if (ret != NATIVE_SUCCESS) {
        return (-errno);
    }
    return NATIVE_SUCCESS;
}

int CopyFileImpl(const char *src, const char *dest)
{
    if (!IsValidPath(src) || !IsValidPath(dest)) {
        return ERROR_CODE_PARAM;
    }
    char* realSrc = (char *)malloc(PATH_MAX);
    if (realSrc == NULL) {
        return ERROR_CODE_GENERAL;
    }
    if (GetRealPath(src, realSrc, PATH_MAX) != NATIVE_SUCCESS) {
        free(realSrc);
        return ERROR_CODE_GENERAL;
    }
    int fdSrc = open(realSrc, O_RDONLY, S_IRUSR);
    free(realSrc);
    realSrc = NULL;
    if (fdSrc < 0) {
        return (-errno);
    }
    char* realDest = (char *)malloc(PATH_MAX);
    if (realDest == NULL) {
        close(fdSrc);
        return ERROR_CODE_GENERAL;
    }
    if (GetRealPath(dest, realDest, PATH_MAX) != NATIVE_SUCCESS) {
        close(fdSrc);
        free(realDest);
        return ERROR_CODE_GENERAL;
    }
    int fdDest = open(realDest, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    free(realDest);
    realDest = NULL;
    if (fdDest < 0) {
        close(fdSrc);
        return (-errno);
    }
    int ret = DoCopyFile(fdSrc, fdDest);
    if (ret != NATIVE_SUCCESS) {
        unlink(dest);
    }
    close(fdSrc);
    close(fdDest);
    return ret;
}

int WriteTextFile(const char *fileName, const void *buf, size_t len, bool append)
{
    if (!IsValidPath(fileName) || (buf == NULL)) {
        return ERROR_CODE_PARAM;
    }
    char* resolvePath = (char *)malloc(PATH_MAX);
    if (resolvePath == NULL) {
        return ERROR_CODE_GENERAL;
    }
    if (GetRealPath(fileName, resolvePath, PATH_MAX) != NATIVE_SUCCESS) {
        free(resolvePath);
        return ERROR_CODE_GENERAL;
    }
    int fileHandle = -1;
    if (append) {
        fileHandle = open(resolvePath, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    } else {
        fileHandle = open(resolvePath, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    }
    free(resolvePath);
    if (fileHandle < 0) {
        return (-errno);
    }
    if (write(fileHandle, buf, len) != len) {
        close(fileHandle);
        return ERROR_CODE_IO;
    }
    close(fileHandle);
    return NATIVE_SUCCESS;
}

int WriteArrayFile(const char *fileName, const void *buf, size_t len, unsigned int position, bool append)
{
    if (!IsValidPath(fileName) || (buf == NULL)) {
        return ERROR_CODE_PARAM;
    }
    char* resolvePath = (char *)malloc(PATH_MAX);
    if (resolvePath == NULL) {
        return ERROR_CODE_GENERAL;
    }
    if (GetRealPath(fileName, resolvePath, PATH_MAX) != NATIVE_SUCCESS) {
        free(resolvePath);
        return ERROR_CODE_GENERAL;
    }
    int fileHandle = -1;
    if (append) {
        fileHandle = open(resolvePath, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
        free(resolvePath);
        resolvePath = NULL;
        if (fileHandle < 0) {
            return (-errno);
        }
    } else {
        fileHandle = open(resolvePath, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        free(resolvePath);
        resolvePath = NULL;
        if (fileHandle < 0) {
            return (-errno);
        }
        if (lseek(fileHandle, position, SEEK_SET) != position) {
            close(fileHandle);
            return ERROR_CODE_IO;
        }
    }
    if (write(fileHandle, buf, len) != len) {
        close(fileHandle);
        return ERROR_CODE_IO;
    }
    close(fileHandle);
    return NATIVE_SUCCESS;
}

int ReadFileImpl(const char *fileName, void* text, size_t len, unsigned int position, size_t* actualLen)
{
    if (!IsValidPath(fileName) || (text == NULL)) {
        return ERROR_CODE_PARAM;
    }
    char* resolvePath = (char *)malloc(PATH_MAX);
    if (resolvePath == NULL) {
        return ERROR_CODE_GENERAL;
    }
    if (GetRealPath(fileName, resolvePath, PATH_MAX) != NATIVE_SUCCESS) {
        free(resolvePath);
        return ERROR_CODE_GENERAL;
    }
    int fileHandle = open(resolvePath, O_RDONLY, S_IRUSR);
    free(resolvePath);
    resolvePath = NULL;
    if (fileHandle < 0) {
        return (-errno);
    }
    struct stat info = { 0 };
    if (fstat(fileHandle, &info) != 0) {
        close(fileHandle);
        return ERROR_CODE_IO;
    }
    if (position > info.st_size) {
        close(fileHandle);
        return ERROR_CODE_PARAM;
    }
    if (len == 0) {
        len = info.st_size - position;
    }
    if (lseek(fileHandle, position, SEEK_SET) != position) {
        close(fileHandle);
        return ERROR_CODE_IO;
    }
    int readLen = read(fileHandle, text, len);
    *actualLen = readLen;
    if (readLen < 0) {
        close(fileHandle);
        return ERROR_CODE_IO;
    }
    close(fileHandle);
    return NATIVE_SUCCESS;
}

int GetFileListImpl(const char* dirName, FileMetaInfo* fileList, unsigned int listNum)
{
    if (!IsValidPath(dirName) || (fileList == NULL)) {
        return ERROR_CODE_PARAM;
    }
    int ret = ERROR_CODE_GENERAL;
    DIR *fileDir = opendir(dirName);
    if (fileDir == NULL) {
        return ret;
    }
    int fileIndex = 0;
    struct dirent *dir = readdir(fileDir);
    struct stat fileStat = { 0 };
    char *fullFileName = (char *)malloc(FILE_NAME_MAX_LEN + 1);
    if (fullFileName == NULL) {
        goto EXIT;
    }
    while ((dir != NULL) && (fileIndex < listNum)) {
        if (memset_s(fullFileName, FILE_NAME_MAX_LEN + 1, 0x0, FILE_NAME_MAX_LEN + 1) != EOK) {
            goto EXIT;
        }
        if (sprintf_s(fullFileName, FILE_NAME_MAX_LEN + 1, "%s/%s", dirName, dir->d_name) < 0) {
            goto EXIT;
        }
        if (stat(fullFileName, &fileStat) != 0) {
            goto EXIT;
        }
        if (strcpy_s(fileList[fileIndex].fileName, FILE_NAME_MAX_LEN + 1, fullFileName) != EOK) {
            goto EXIT;
        }
        fileList[fileIndex].fileSize = fileStat.st_size;
        fileList[fileIndex].fileMtime = fileStat.st_mtime;
        fileList[fileIndex].fileMode = fileStat.st_mode;
        fileIndex++;
        dir = readdir(fileDir);
    }
    ret = NATIVE_SUCCESS;
EXIT:
    free(fullFileName);
    closedir(fileDir);
    return ret;
}

int GetFileNum(const char* dirName)
{
    int ret = AccessImpl(dirName);
    if (ret != NATIVE_SUCCESS) {
        return ret;
    }
    DIR *fileDir = opendir(dirName);
    if (fileDir == NULL) {
        return ERROR_CODE_PARAM;
    }
    struct dirent *dir = readdir(fileDir);
    int sum = 0;
    while (dir != NULL) {
        sum++;
        dir = readdir(fileDir);
    }
    closedir(fileDir);
    if (sum == 0) {
        return ERROR_CODE_IO;
    }
    return sum;
}

int AccessImpl(const char* fileName)
{
    if (!IsValidPath(fileName)) {
        return ERROR_CODE_PARAM;
    }
    if (access(fileName, F_OK) == F_OK) {
        return NATIVE_SUCCESS;
    }
    return (-errno);
}

int CreateDirImpl(const char* fileName, bool recursive)
{
    if (!IsValidPath(fileName)) {
        return ERROR_CODE_PARAM;
    }
    if (AccessImpl(fileName) == NATIVE_SUCCESS) {
        return NATIVE_SUCCESS;
    }
    if (recursive) {
        return MkdirRecursive(fileName);
    }
    int ret = mkdir(fileName, S_IRUSR | S_IWUSR | S_IXUSR);
    if (ret != NATIVE_SUCCESS) {
        return (-errno);
    }
    return NATIVE_SUCCESS;
}

int RemoveDirImpl(const char* fileName, bool recursive)
{
    int ret = AccessImpl(fileName);
    if (ret != NATIVE_SUCCESS) {
        return ret;
    }
    if (recursive) {
        return RmdirRecursive(fileName);
    }
    ret = rmdir(fileName);
    if (ret != NATIVE_SUCCESS) {
        return (-errno);
    }
    return NATIVE_SUCCESS;
}