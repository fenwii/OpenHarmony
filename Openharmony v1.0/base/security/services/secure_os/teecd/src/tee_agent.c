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

#include "tee_agent.h"
#include <dirent.h>
#include <errno.h>     /* for errno */
#include <fcntl.h>
#include <pthread.h>
#include <securec.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h> /* for ioctl */
#include <sys/mman.h>  /* for mmap */
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/time.h>
#include <sys/types.h> /* for open close */
#include <unistd.h>
#include "secfile_load_agent.h"
#include "tc_ns_client.h"
#include "tcu_authentication.h"
#include "tee_ca_daemon.h"
#include "tee_client_api.h"
#include "tee_log.h"
#include "teec_compat.h"

/* open file list head */
static struct OpenedFile *g_firstFile = (struct OpenedFile *)NULL;

/* record the current g_userId */
static uint32_t g_userId;
static void SetCurrentUserId(uint32_t id)
{
    g_userId = id;
}

static uint32_t GetCurrentUserId(void)
{
    return g_userId;
}

#define UID_MAX_LEN 16

/* add to tail */
static int AddOpenFile(FILE *pFile)
{
    struct OpenedFile *newFile = (struct OpenedFile *)malloc(sizeof(struct OpenedFile));
    if (newFile == NULL) {
        tloge("malloc OpenedFile failed\n");
        return -1;
    }
    newFile->file = pFile;

    if (g_firstFile == NULL) {
        g_firstFile   = newFile;
        newFile->next = newFile;
        newFile->prev = newFile;
    } else {
        if (g_firstFile->prev == NULL) {
            tloge("the tail is null\n");
            free(newFile);
            return -1;
        }
        g_firstFile->prev->next = newFile;
        newFile->prev           = g_firstFile->prev;
        newFile->next           = g_firstFile;
        g_firstFile->prev       = newFile;
    }
    return 0;
}

static void DelOpenFile(struct OpenedFile *file)
{
    struct OpenedFile *next = NULL;

    if (file == NULL) {
        return;
    }
    next = file->next;

    if (file == next) { /* only 1 node */
        g_firstFile = NULL;
    } else {
        if (file->next == NULL || file->prev == NULL) {
            tloge("the next or the prev is null\n");
            return;
        }
        if (file == g_firstFile) {
            g_firstFile = file->next;
        }
        next->prev       = file->prev;
        file->prev->next = next;
    }
}

static int FindOpenFile(int fd, struct OpenedFile **file)
{
    struct OpenedFile *p = g_firstFile;
    int findFlag         = 0;

    if (p == NULL) {
        return findFlag;
    }

    do {
        if (p->file != NULL) {
            if (fileno(p->file) == fd) {
                findFlag = 1;
                break;
            }
        }
        p = p->next;
    } while (p != g_firstFile && p != NULL);

    if (!findFlag) {
        p = NULL;
    }
    if (file != NULL) {
        *file = p;
    }
    return findFlag;
}

/* smc dev */
static int g_fsFd   = -1;
static int g_miscFd = -1;

/*
 * path:file or dir to change own
 * flag: 0(dir);1(file)
 */
static void ChownSecStorageDataToSystem(const char *path, int flag)
{
    if (path == NULL) {
        return;
    }
    /* check path is SEC_STORAGE_ROOT_DIR or SEC_STORAGE_DATA_DIR,
     * we only need to change SEC_STORAGE_DATA_DIR from root to system
     */
    if (strstr(path, "sec_storage_data")) {
        int ret = chown(path, AID_SYSTEM, AID_SYSTEM);
        if (ret < 0) {
            tloge("chown erro\n");
        }
        if (flag) {
            ret = chmod(path, S_IRUSR | S_IWUSR);
        } else {
            ret = chmod(path, S_IRUSR | S_IWUSR | S_IXUSR);
        }
        if (ret < 0) {
            tloge("chmod erro\n");
        }
    }
}

static int CheckPathLen(const char *path, size_t pathLen)
{
    uint32_t i = 0;

    while (i < pathLen && path[i] != '\0') {
        i++;
    }
    if (i >= pathLen) {
        tloge("path is too long\n");
        return -1;
    }
    return 0;
}

/*
 * path:file path name.
 * e.g. sec_storage_data/app1/sub1/fileA.txt
 * then CreateDir will make dir sec_storage_data, app1 and sub1.
 */
static int CreateDir(const char *path, size_t pathLen)
{
    int32_t ret;

    ret = CheckPathLen(path, pathLen);
    if (ret) {
        return -1;
    }

    char *pathTemp = strdup(path);
    char *position  = pathTemp;

    if (pathTemp == NULL) {
        tloge("strdup error\n");
        return -1;
    }

    if (strncmp(pathTemp, "/", 1) == 0) {
        position++;
    } else if (strncmp(pathTemp, "./", strlen("./")) == 0) {
        position += strlen("./");
    }

    for (; *position != '\0'; ++position) {
        if (*position == '/') {
            *position = '\0';

            if (access(pathTemp, F_OK) == 0) {
                *position = '/';
                continue;
            }

            if (mkdir(pathTemp, ROOT_DIR_PERM) != 0) {
                tloge("mkdir %s fail\n", pathTemp);
                free(pathTemp);
                pathTemp = NULL;
                (void)pathTemp;
                return -1;
            }

            ChownSecStorageDataToSystem(pathTemp, 0);
            tlogv("for %s\n", pathTemp);
            *position = '/';
        }
    }

    free(pathTemp);
    pathTemp = NULL;
    (void)pathTemp;
    return 0;
}

static int CheckFileNameAndPath(const char *name, const char *path)
{
    if (name == NULL || path == NULL) {
        return -1;
    }

    if (strstr(name, FILE_NAME_INVALID_STR)) {
        tloge("Invalid file name(file name contain ..)\n");
        return -1;
    }

    return 0;
}

static int JoinFileNamePerso(const char *name, char *path, size_t pathLen)
{
    errno_t rc;

    rc = strncpy_s(path, pathLen, USER_DATA_DIR, sizeof(USER_DATA_DIR));
    if (rc != EOK) {
        tloge("strncpy_s failed %d\n", rc);
        return -1;
    }

    rc = strncat_s(path, pathLen, name, strlen(name));
    if (rc != EOK) {
        tloge("strncat_s failed %d\n", rc);
        return -1;
    }

    return 0;
}

static int JoinFileNameTransient(const char *name, char *path, size_t pathLen)
{
    errno_t rc;
    uint32_t userId = GetCurrentUserId();

    rc = strncpy_s(path, pathLen, USER_DATA_DIR, sizeof(USER_DATA_DIR));
    if (rc != EOK) {
        tloge("strncpy_s failed %d\n", rc);
        return -1;
    }

    if (userId != 0) {
        char userPath[UID_MAX_LEN] = { 0 };
        rc = snprintf_s(userPath, sizeof(userPath), sizeof(userPath) - 1, "%u/", userId);
        if (rc == -1) {
            tloge("snprintf_s failed %d\n", rc);
            return -1;
        }

        rc = strncat_s(path, pathLen, SFS_PARTITION_USER_SYMLINK, strlen(SFS_PARTITION_USER_SYMLINK));
        if (rc != EOK) {
            tloge("strncat_s failed %d\n", rc);
            return -1;
        }

        rc = strncat_s(path, pathLen, userPath, strlen(userPath));
        if (rc != EOK) {
            tloge("strncat_s failed %d\n", rc);
            return -1;
        }

        if (strlen(name) <= strlen(SFS_PARTITION_TRANSIENT)) {
            tloge("name length is too small\n");
            return -1;
        }
        rc = strncat_s(path, pathLen, name + strlen(SFS_PARTITION_TRANSIENT),
                       (strlen(name) - strlen(SFS_PARTITION_TRANSIENT)));
        if (rc != EOK) {
            tloge("strncat_s failed %d\n", rc);
            return -1;
        }
    } else {
        rc = strncat_s(path, pathLen, name, strlen(name));
        if (rc != EOK) {
            tloge("strncat_s failed %d\n", rc);
            return -1;
        }
    }

    return 0;
}

static int JoinFileNamePersistent(const char *name, char *path, size_t pathLen)
{
    errno_t rc;

    rc = strncpy_s(path, pathLen, ROOT_DIR, sizeof(ROOT_DIR));
    if (rc != EOK) {
        tloge("strncpy_s failed %d\n", rc);
        return -1;
    }

    rc = strncat_s(path, pathLen, name, strlen(name));
    if (rc != EOK) {
        tloge("strncat_s failed %d\n", rc);
        return -1;
    }

    return 0;
}

static int JoinFileNameDefault(const char *name, char *path, size_t pathLen)
{
    errno_t rc;

    rc = strncpy_s(path, pathLen, SEC_STORAGE_ROOT_DIR, sizeof(SEC_STORAGE_ROOT_DIR));
    if (rc != EOK) {
        tloge("strncpy_s failed %d\n", rc);
        return -1;
    }

    rc = strncat_s(path, pathLen, name, strlen(name));
    if (rc != EOK) {
        tloge("strncat_s failed %d\n", rc);
        return -1;
    }

    return 0;
}

/*
 * example for JoinFileName
 *
 * name                         userId        path
 * -------------------------------------------------------------------------
 * abc/def                      DC          /sec_storage/abc/def
 * sec_storage/abc/def          DC          /sec_storage/abc/def
 * sec_storage_data/abc/def     0           /data/sec_storage_data/abc/def
 * sec_storage_data/abc/def     1           /data/sec_storage_data/1/abc/def
 */
static int JoinFileName(const char *name, char *path, size_t pathLen)
{
    int ret;

    if (CheckFileNameAndPath(name, path)) {
        return -1;
    }

    /* If the path name does not start with sec_storage or sec_storage_data,
     * add sec_storage str for the path
     */
    if (name == strstr(name, SFS_PARTITION_TRANSIENT_PERSO) || name == strstr(name, SFS_PARTITION_TRANSIENT_PRIVATE)) {
        ret = JoinFileNamePerso(name, path, pathLen);
    } else if (name == strstr(name, SFS_PARTITION_TRANSIENT)) {
        ret = JoinFileNameTransient(name, path, pathLen);
    } else if (name == strstr(name, SFS_PARTITION_PERSISTENT)) {
        ret = JoinFileNamePersistent(name, path, pathLen);
    } else {
        ret = JoinFileNameDefault(name, path, pathLen);
    }

    tlogv("joined path is \"%s\"\n", path);
    return ret;
}

static bool IsValidFilePath(const char *path)
{
    if ((path == strstr(path, SEC_STORAGE_DATA_DIR)) || (path == strstr(path, SEC_STORAGE_DATA_USERS)) ||
        (path == strstr(path, SEC_STORAGE_ROOT_DIR))) {
        return true;
    }

    tloge("path is invalid %s\n", path);
    return false;
}

static uint32_t GetRealFilePath(const char *originPath, char *trustPath, size_t tPathLen)
{
    char *retPath = realpath(originPath, trustPath);
    if (retPath == NULL) {
        /* the file may be not exist, will create after */
        if ((errno != ENOENT) && (errno != EACCES)) {
            tloge("realpath %s failed: %s\n", originPath, strerror(errno));
            return (uint32_t)errno;
        }
        /* check origin path */
        if (!IsValidFilePath(originPath)) {
            tloge("path %s is invalid\n", originPath);
            return ENFILE;
        }
        errno_t rc = strncpy_s(trustPath, tPathLen, originPath, strlen(originPath));
        if (rc != EOK) {
            tloge("strncpy_s failed %d\n", rc);
            return EPERM;
        }
    } else {
        /* check real path */
        if (!IsValidFilePath(trustPath)) {
            tloge("path %s is invalid\n", trustPath);
            return ENFILE;
        }
    }
    return 0;
}

static int UnlinkRecursive(const char *name);
static int UnlinkRecursiveDir(const char *name)
{
    int fail          = 0;
    char dn[PATH_MAX] = { 0 };
    errno_t rc;

    /* a directory, so open handle */
    DIR *dir = opendir(name);
    if (dir == NULL) {
        tloge("dir %s open failed\n", name);
        return -1;
    }

    /* recurse over components */
    errno = 0;

    struct dirent *de = readdir(dir);

    while (de != NULL) {
        if (!strncmp(de->d_name, "..", sizeof("..")) || !strncmp(de->d_name, ".", sizeof("."))) {
            de = readdir(dir);
            continue;
        }
        rc = snprintf_s(dn, sizeof(dn), sizeof(dn) - 1, "%s/%s", name, de->d_name);
        if (rc == -1) {
            tloge("snprintf_s failed %d\n", rc);
            fail = 1;
            break;
        }

        if (UnlinkRecursive(dn) < 0) {
            tloge("loop UnlinkRecursive() failed, there are read-only file\n");
            fail = 1;
            break;
        }
        errno = 0;
        de    = readdir(dir);
    }

    /* in case readdir or UnlinkRecursive failed */
    if (fail || errno < 0) {
        int save = errno;
        closedir(dir);
        errno = save;
        tloge("fail is %d, errno is %d\n", fail, errno);
        return -1;
    }

    /* close directory handle */
    if (closedir(dir) < 0) {
        tloge("closedir %s failed, errno is %d\n", name, errno);
        return -1;
    }

    /* delete target directory */
    if (rmdir(name) < 0) {
        tloge("rmdir %s failed, errno is %d\n", name, errno);
        return -1;
    }
    return 0;
}

static int UnlinkRecursive(const char *name)
{
    struct stat st;

    /* is it a file or directory? */
    if (lstat(name, &st) < 0) {
        tloge("lstat %s failed, errno is %x\n", name, errno);
        return -1;
    }

    /* a file, so unlink it */
    if (!S_ISDIR(st.st_mode)) {
        if (unlink(name) < 0) {
            tloge("unlink %s failed, errno is %d\n", name, errno);
            return -1;
        }
        return 0;
    }

    return UnlinkRecursiveDir(name);
}

static int IsFileExist(const char *name)
{
    struct stat statbuf;

    if (name == NULL) {
        return 0;
    }
    if (stat(name, &statbuf)) {
        if (errno == ENOENT) { /* file not exist */
            tloge("file stat failed\n");
            return 0;
        }
        return 1;
    }

    return 1;
}

static uint32_t DoOpenFile(const char *path, struct SecStorageType *transControl)
{
    char trustPath[PATH_MAX] = { 0 };

    uint32_t rRet = GetRealFilePath(path, trustPath, sizeof(trustPath));
    if (rRet) {
        tloge("get real path failed. err=%u\n", rRet);
        return rRet;
    }

    FILE *pFile = fopen(trustPath, transControl->Args.Open.mode);
    if (pFile == NULL) {
        tloge("open file(%s) with flag(%s) failed: %s\n", trustPath, transControl->Args.Open.mode, strerror(errno));
        return (uint32_t)errno;
    }

    ChownSecStorageDataToSystem(trustPath, 1);
    int ret = AddOpenFile(pFile);
    if (ret) {
        (void)fclose(pFile);
        pFile = NULL;
        tloge("add OpenedFile failed\n");
        return ENOMEM;
    }
    transControl->ret = fileno(pFile); /* return fileno */
    return 0;
}

static void OpenWork(struct SecStorageType *transControl)
{
    uint32_t error;
    char nameBuff[FILE_NAME_MAX_BUF] = { 0 };

    SetCurrentUserId(transControl->userId);

    tlogv("sec storage : open, file name:%s", (char *)(transControl->Args.Open.name));

    if (!JoinFileName((char *)(transControl->Args.Open.name), nameBuff, sizeof(nameBuff))) {
        if (transControl->cmd == SEC_CREATE) {
            /* create a exist file, remove it at first */
            errno_t rc =
                strncpy_s(transControl->Args.Open.mode, sizeof(transControl->Args.Open.mode), "w+", sizeof("w+"));
            if (rc != EOK) {
                tloge("strncpy_s failed %d\n", rc);
                error = ENOENT;
                goto ERROR;
            }
        } else {
            if (IsFileExist(nameBuff) == 0) {
                /* open a nonexist file, return fail */
                tloge("file(%s) not exist, open failed\n", nameBuff);
                error = ENOENT;
                goto ERROR;
            }
        }

        /* mkdir -p for new create files */
        if (CreateDir(nameBuff, sizeof(nameBuff))) {
            error = (uint32_t)errno;
            goto ERROR;
        }

        error = DoOpenFile(nameBuff, transControl);
        if (error) {
            goto ERROR;
        }
    } else {
        /* NEVER in this case */
        transControl->ret = -1;
    }
    return;

ERROR:
    transControl->ret   = -1;
    transControl->error = error;
    return;
}

static void CloseWork(struct SecStorageType *transControl)
{
    struct OpenedFile *selFile = NULL;

    tlogv("sec storage : close\n");

    if (FindOpenFile(transControl->Args.Close.fd, &selFile)) {
        int ret = fclose(selFile->file);
        if (ret == 0) {
            tlogv("close file(%d) success\n", transControl->Args.Close.fd);
            DelOpenFile(selFile);
            free(selFile);
            selFile = NULL;
            (void)selFile;
        } else {
            tloge("close file(%d) failed: %s\n", transControl->Args.Close.fd, strerror(errno));
            transControl->error = (uint32_t)errno;
        }
        transControl->ret = ret;
    } else {
        tloge("can't find opened file(fileno = %d)\n", transControl->Args.Close.fd);
        transControl->ret   = -1;
        transControl->error = EBADF;
    }
}

static void ReadWork(struct SecStorageType *transControl)
{
    struct OpenedFile *selFile = NULL;

    tlogv("sec storage : read count = %d\n", transControl->Args.Read.count);

    if (FindOpenFile(transControl->Args.Read.fd, &selFile)) {
        size_t count = fread((void *)(transControl->Args.Read.buffer), 1, transControl->Args.Read.count, selFile->file);
        transControl->ret = (int32_t)count;

        if (count < transControl->Args.Read.count) {
            if (feof(selFile->file)) {
                transControl->ret2 = 0;
                tlogv("read end of file\n");
            } else {
                transControl->ret2  = -1;
                transControl->error = (uint32_t)errno;
                tloge("read file failed: %s\n", strerror(errno));
            }
        } else {
            transControl->ret2 = 0;
            tlogv("read file success, content len=%lu\n", count);
        }
    } else {
        transControl->ret   = 0;
        transControl->ret2  = -1;
        transControl->error = EBADF;
        tloge("can't find opened file(fileno = %d)\n", transControl->Args.Read.fd);
    }
}

static void WriteWork(struct SecStorageType *transControl)
{
    struct OpenedFile *selFile = NULL;

    tlogv("sec storage : write count = %d\n", transControl->Args.Write.count);

    if (FindOpenFile(transControl->Args.Write.fd, &selFile)) {
        size_t count = fwrite((void *)(transControl->Args.Write.buffer), 1,
            transControl->Args.Write.count, selFile->file);
        if (count < transControl->Args.Write.count) {
            tloge("write file failed: %s\n", strerror(errno));
            transControl->ret   = (int32_t)count;
            transControl->error = (uint32_t)errno;
            return;
        }

        if (transControl->ret2 == SEC_WRITE_SSA) {
            if (fflush(selFile->file) != 0) {
                tloge("fflush file failed: %s\n", strerror(errno));
                transControl->ret   = 0;
                transControl->error = (uint32_t)errno;
            } else {
                transControl->ret = (int32_t)count;
            }
        } else {
            transControl->ret   = (int32_t)count;
            transControl->error = 0;
        }
    } else {
        tloge("can't find opened file(fileno = %d)\n", transControl->Args.Write.fd);
        transControl->ret   = 0;
        transControl->error = EBADF;
    }
}

static void SeekWork(struct SecStorageType *transControl)
{
    struct OpenedFile *selFile = NULL;

    tlogv("sec storage : seek offset=%d, whence=%d\n", transControl->Args.Seek.offset, transControl->Args.Seek.whence);

    if (FindOpenFile(transControl->Args.Seek.fd, &selFile)) {
        int ret = fseek(selFile->file, transControl->Args.Seek.offset, (int)transControl->Args.Seek.whence);
        if (ret) {
            tloge("seek file failed: %s\n", strerror(errno));
            transControl->error = (uint32_t)errno;
        } else {
            tlogv("seek file success\n");
        }
        transControl->ret = ret;
    } else {
        tloge("can't find opened file(fileno = %d)\n", transControl->Args.Seek.fd);
        transControl->ret   = -1;
        transControl->error = EBADF;
    }
}

static void RemoveWork(struct SecStorageType *transControl)
{
    char nameBuff[FILE_NAME_MAX_BUF] = { 0 };

    tlogv("sec storage : remove \"%s\"\n", (char *)(transControl->Args.Remove.name));

    SetCurrentUserId(transControl->userId);

    if (!JoinFileName((char *)(transControl->Args.Remove.name), nameBuff, sizeof(nameBuff))) {
        int ret = UnlinkRecursive(nameBuff);
        if (ret) {
            tloge("remove file failed: %s\n", strerror(errno));
            transControl->error = (uint32_t)errno;
        } else {
            tlogv("remove file success\n");
        }
        transControl->ret = ret;
    } else {
        transControl->ret = -1;
    }
}

static void TruncateWork(struct SecStorageType *transControl)
{
    char nameBuff[FILE_NAME_MAX_BUF] = { 0 };

    tlogv("sec storage : truncate \"%s\", len=%d\n", (char *)(transControl->Args.Truncate.name),
          transControl->Args.Truncate.len);

    SetCurrentUserId(transControl->userId);

    if (!JoinFileName((char *)(transControl->Args.Truncate.name), nameBuff, sizeof(nameBuff))) {
        int ret = truncate(nameBuff, (long)transControl->Args.Truncate.len);
        if (ret) {
            tloge("truncate file failed: %s\n", strerror(errno));
            transControl->error = (uint32_t)errno;
        } else {
            tlogv("truncate file success\n");
        }
        transControl->ret = ret;
    } else {
        transControl->ret = -1;
    }
}

static void RenameWork(struct SecStorageType *transControl)
{
    char nameBuff[FILE_NAME_MAX_BUF]  = { 0 };
    char nameBuff2[FILE_NAME_MAX_BUF] = { 0 };

    SetCurrentUserId(transControl->userId);

    int joinRet1 = JoinFileName((char *)(transControl->Args.Rename.buffer), nameBuff, sizeof(nameBuff));
    int joinRet2 = JoinFileName((char *)(transControl->Args.Rename.buffer) + transControl->Args.Rename.oldNameLen,
                                nameBuff2, sizeof(nameBuff2));
    if (!joinRet1 && !joinRet2) {
        int ret = rename(nameBuff, nameBuff2);
        if (ret) {
            tloge("rename file failed: %s\n", strerror(errno));
            transControl->error = (uint32_t)errno;
        } else {
            tlogv("rename file success\n");
        }
        transControl->ret = ret;
    } else {
        transControl->ret = -1;
    }
}

#define MAXBSIZE 65536

static int DoCopy(int fromFd, int toFd)
{
    int ret;
    ssize_t rcount;
    ssize_t wcount;

    char *buf = (char *)malloc(MAXBSIZE * sizeof(char));
    if (buf == NULL) {
        tloge("malloc buf failed\n");
        return -1;
    }
    if (memset_s(buf, MAXBSIZE, 0, MAXBSIZE) != EOK) {
        tloge("memset buf failed\n");
        ret = -1;
        goto OUT;
    }

    rcount = read(fromFd, buf, MAXBSIZE);
    while (rcount > 0) {
        wcount = write(toFd, buf, (size_t)rcount);
        if (rcount != wcount || wcount == -1) {
            tloge("write file failed: %s\n", strerror(errno));
            ret = -1;
            goto OUT;
        }
        if (memset_s(buf, MAXBSIZE, 0, MAXBSIZE) != EOK) {
            tloge("memset buf failed\n");
            ret = -1;
            goto OUT;
        }
        rcount = read(fromFd, buf, MAXBSIZE);
    }

    if (rcount < 0) {
        tloge("read file failed: %s\n", strerror(errno));
        ret = -1;
        goto OUT;
    }

    /* fsync memory from kernel to disk */
    ret = fsync(toFd);
    if (ret != 0) {
        tloge("CopyFile:fsync file failed: %s\n", strerror(errno));
        goto OUT;
    }

OUT:
    free(buf);
    return ret;
}

static int CopyFile(const char *fromPath, const char *toPath)
{
    struct stat fromStat;
    char realFromPath[PATH_MAX] = { 0 };
    char realToPath[PATH_MAX]   = { 0 };

    uint32_t rRet = GetRealFilePath(fromPath, realFromPath, sizeof(realFromPath));
    if (rRet) {
        tloge("get real from path failed. err=%u\n", rRet);
        return -1;
    }

    rRet = GetRealFilePath(toPath, realToPath, sizeof(realToPath));
    if (rRet) {
        tloge("get real to path failed. err=%u\n", rRet);
        return -1;
    }

    int fromFd = open(realFromPath, O_RDONLY, 0);
    if (fromFd == -1) {
        tloge("open file %s failed: %s\n", realFromPath, strerror(errno));
        return -1;
    }

    int ret = fstat(fromFd, &fromStat);
    if (ret == -1) {
        tloge("stat file %s failed: %s\n", realFromPath, strerror(errno));
        close(fromFd);
        return ret;
    }

    int toFd = open(realToPath, O_WRONLY | O_TRUNC | O_CREAT, fromStat.st_mode);
    if (toFd == -1) {
        tloge("stat file %s failed: %s\n", realToPath, strerror(errno));
        close(fromFd);
        return -1;
    }

    ret = DoCopy(fromFd, toFd);
    if (ret != 0) {
        tloge("do copy from %s to %s failed\n", realFromPath, realToPath);
    } else {
        ChownSecStorageDataToSystem((char *)realToPath, 1);
    }

    close(fromFd);
    close(toFd);
    return ret;
}

static void CopyWork(struct SecStorageType *transControl)
{
    char fromPath[FILE_NAME_MAX_BUF] = { 0 };
    char toPath[FILE_NAME_MAX_BUF]   = { 0 };

    SetCurrentUserId(transControl->userId);

    int joinRet1 = JoinFileName((char *)(transControl->Args.Cp.buffer), fromPath, sizeof(fromPath));
    int joinRet2 = JoinFileName((char *)(transControl->Args.Cp.buffer) + transControl->Args.Cp.fromPathLen, toPath,
                                sizeof(toPath));
    if (!joinRet1 && !joinRet2) {
        int ret = CopyFile(fromPath, toPath);
        if (ret) {
            tloge("copy file failed: %s\n", strerror(errno));
            transControl->error = (uint32_t)errno;
        } else {
            tlogv("copy file success\n");
        }
        transControl->ret = ret;
    } else {
        transControl->ret = -1;
    }
}

static void FileInfoWork(struct SecStorageType *transControl)
{
    struct OpenedFile *selFile = NULL;
    struct stat statBuff;

    tlogv("sec storage : file info\n");

    transControl->Args.Info.fileLen = transControl->Args.Info.curPos = 0;

    if (FindOpenFile(transControl->Args.Info.fd, &selFile)) {
        int ret = fstat(transControl->Args.Info.fd, &statBuff);
        if (ret == 0) {
            transControl->Args.Info.fileLen = (uint32_t)statBuff.st_size;
            transControl->Args.Info.curPos  = (uint32_t)ftell(selFile->file);
        } else {
            tloge("fstat file failed: %s\n", strerror(errno));
            transControl->error = (uint32_t)errno;
        }
        transControl->ret = ret;
    } else {
        transControl->ret   = -1;
        transControl->error = EBADF;
    }
}

static void FileAccessWork(struct SecStorageType *transControl)
{
    int ret;

    tlogv("sec storage : file access\n");

    if (transControl->cmd == SEC_ACCESS) {
        SetCurrentUserId(transControl->userId);

        char nameBuff[FILE_NAME_MAX_BUF] = { 0 };
        if (!JoinFileName((char *)(transControl->Args.Access.name), nameBuff, sizeof(nameBuff))) {
            ret = access(nameBuff, transControl->Args.Access.mode);
            if (ret < 0) {
                tloge("access file(%s) mode(%d) failed: %s\n", nameBuff, transControl->Args.Access.mode,
                      strerror(errno));
            }
            transControl->ret   = ret;
            transControl->error = (uint32_t)errno;
        } else {
            transControl->ret = -1;
        }
    } else {
        ret = access((char *)(transControl->Args.Access.name), transControl->Args.Access.mode);
        if (ret < 0) {
            tloge("access2 file(%s) mode(%d) failed: %s\n", (char *)transControl->Args.Access.name,
                  transControl->Args.Access.mode, strerror(errno));
        }
        transControl->ret   = ret;
        transControl->error = (uint32_t)errno;
    }
}

static void FsyncWork(struct SecStorageType *transControl)
{
    struct OpenedFile *selFile = NULL;

    tlogv("sec storage : file fsync\n");

    /* opened file */
    if (transControl->Args.Fsync.fd && FindOpenFile(transControl->Args.Fsync.fd, &selFile)) {
        /* first,flush memory from user to kernel */
        int ret = fflush(selFile->file);
        if (ret != 0) {
            tloge("fsync:fflush file failed: %s\n", strerror(errno));
            transControl->ret   = -1;
            transControl->error = (uint32_t)errno;
            return;
        }

        /* second,fsync memory from kernel to disk */
        int fd  = fileno(selFile->file);
        ret = fsync(fd);
        if (ret != 0) {
            tloge("fsync:fsync file failed: %s\n", strerror(errno));
            transControl->ret   = -1;
            transControl->error = (uint32_t)errno;
            return;
        }

        transControl->ret = 0;
        tlogv("fsync file(%d) success\n", transControl->Args.Fsync.fd);
    } else {
        tloge("can't find opened file(fileno = %d)\n", transControl->Args.Fsync.fd);
        transControl->ret   = -1;
        transControl->error = EBADF;
    }
}

static void DiskUsageWork(struct SecStorageType *transControl)
{
    struct statfs st;
    uint32_t dataRemain;
    uint32_t secStorageRemain;

    tlogv("sec storage : disk usage\n");

    if (statfs("/storage/data", &st) < 0) {
        tloge("statfs /data failed, err=%s\n", strerror(errno));
        goto ERROR;
    }

    dataRemain = (long)st.f_bfree * (long)st.f_bsize / K_BYTES;

    if (statfs("/storage/sec_storage", &st) < 0) {
        tloge("statfs /sec_storage failed, err=%s\n", strerror(errno));
        goto ERROR;
    }

    secStorageRemain = (long)st.f_bfree * (long)st.f_bsize / K_BYTES;

    transControl->ret                       = 0;
    transControl->Args.DiskUsage.data       = dataRemain;
    transControl->Args.DiskUsage.secStorage = secStorageRemain;
    return;

ERROR:
    transControl->ret   = -1;
    transControl->error = (uint32_t)errno;
}

static void DeleteAllWork(struct SecStorageType *transControl)
{
    int ret;
    char path[FILE_NAME_MAX_BUF] = { 0 };
    char *pathIn                 = (char *)(transControl->Args.DeleteAll.path);
    SetCurrentUserId(transControl->userId);

    tlogv("sec storage : delete path \"%s\" , userid:%d\n", (char *)(transControl->Args.DeleteAll.path),
          transControl->userId);

    ret = strncpy_s(path, FILE_NAME_MAX_BUF, USER_DATA_DIR, sizeof(USER_DATA_DIR));
    if (ret != EOK) {
        tloge("strncpy_s failed %d\n", ret);
        transControl->ret = -1;
        return;
    }

    ret = JoinFileNamePerso(pathIn, path, sizeof(path));
    if (ret != EOK) {
        tloge("join name failed %d\n", ret);
        transControl->ret = -1;
        return;
    }

    tlogv("sec storage : joint delete path \"%s\"\n", path);

    ret = UnlinkRecursive(path);
    if (ret) {
        tloge("delete file failed: %s\n", strerror(errno));
        transControl->error = (uint32_t)errno;
    } else {
        tloge("delete file success\n");
    }
    transControl->ret = ret;
}

static int IsUserDataReady(void)
{
    if (access(SEC_STORAGE_DATA_DIR, F_OK) == 0) {
        tlogv("userdata is ready from path: %s\n", SEC_STORAGE_DATA_DIR);
        return 1;
    }
    tloge("userdata is not ready from path: %s\n", SEC_STORAGE_DATA_DIR);
    return 0;
}

typedef void (*FsWorkFunc)(struct SecStorageType *transControl);
typedef struct {
    FsCmdType cmd;
    FsWorkFunc fn;
} FsWorkTbl;

static const FsWorkTbl g_fsWorkTbl[] = {
    { SEC_OPEN, OpenWork },           { SEC_CLOSE, CloseWork },
    { SEC_READ, ReadWork },           { SEC_WRITE, WriteWork },
    { SEC_SEEK, SeekWork },           { SEC_REMOVE, RemoveWork },
    { SEC_TRUNCATE, TruncateWork },   { SEC_RENAME, RenameWork },
    { SEC_CREATE, OpenWork },         { SEC_INFO, FileInfoWork },
    { SEC_ACCESS, FileAccessWork },   { SEC_ACCESS2, FileAccessWork },
    { SEC_FSYNC, FsyncWork },         { SEC_CP, CopyWork },
    { SEC_DISKUSAGE, DiskUsageWork }, { SEC_DELETE_ALL, DeleteAllWork },
};

static void *FsWorkThread(void *control)
{
    struct SecStorageType *transControl = NULL;
    int ret;

    if (control == NULL) {
        return NULL;
    }
    transControl = (struct SecStorageType *)control;

    if (g_fsFd == -1) {
        tloge("fs is not open\n");
        return NULL;
    }

    transControl->magic = AGENT_FS_ID;
    while (1) {
        tlogv("++ fs agent loop ++\n");
        ret = ioctl(g_fsFd, (int)TC_NS_CLIENT_IOCTL_WAIT_EVENT, AGENT_FS_ID);
        if (ret) {
            tloge("fs agent  wait event failed\n");
            break;
        }

        tlogv("fs agent wake up and working!!\n");

        if (IsUserDataReady() == 0) {
            transControl->ret = -1;
            tloge("do secure storage while userdata is not ready, skip!\n");
            goto FILE_WORK_DONE;
        }

        if ((transControl->cmd < SEC_MAX) && (g_fsWorkTbl[transControl->cmd].fn != NULL)) {
            g_fsWorkTbl[transControl->cmd].fn(transControl);
        } else {
            tloge("fs agent error cmd:transControl->cmd=%x\n", transControl->cmd);
        }

    FILE_WORK_DONE:
        Barriers();
        transControl->magic = AGENT_FS_ID;
        Barriers();
        ret = ioctl(g_fsFd, (int)TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, AGENT_FS_ID);
        if (ret) {
            tloge("fs agent send reponse failed\n");
            break;
        }
        tlogv("-- fs agent loop --\n");
    }

    return NULL;
}

static void GetTimeWork(struct MiscControlType *transControl)
{
    struct timeval timeVal;

    if (gettimeofday(&timeVal, NULL) == 0) {
        transControl->ret                  = 0;
        transControl->Args.GetTime.seconds = timeVal.tv_sec;
        transControl->Args.GetTime.millis  = (timeVal.tv_usec / USEC_PER_MSEC);
        struct tm *tstruct                 = NULL;

        tstruct = localtime(&(timeVal.tv_sec));
        if (tstruct != NULL) {
            /* year(from 1900) months(0~11) days hour min second */
            errno_t rc = snprintf_s(transControl->Args.GetTime.timeStr, sizeof(transControl->Args.GetTime.timeStr),
                sizeof(transControl->Args.GetTime.timeStr) - 1, "%04d-%02d-%02d %02d:%02d:%02d.%03d ",
                tstruct->tm_year + TIME_START_YEAR, tstruct->tm_mon + 1, tstruct->tm_mday, tstruct->tm_hour,
                tstruct->tm_min, tstruct->tm_sec, (int)(timeVal.tv_usec / USEC_PER_MSEC));
            if (rc == -1) {
                transControl->ret = -1;
                tloge("snprintf_s error %d\n", rc);
            }
        } else {
            tloge("get localtiem error\n");
        }
    } else {
        transControl->ret                  = -1;
        transControl->Args.GetTime.seconds = 0;
        transControl->Args.GetTime.millis  = 0;
    }
}

static void *MiscWorkThread(void *control)
{
    struct MiscControlType *transControl = NULL;

    if (control == NULL) {
        return NULL;
    }
    transControl = (struct MiscControlType *)control;

    if (g_miscFd == -1) {
        tloge("misc file is not open\n");
        return NULL;
    }

    transControl->magic = AGENT_MISC_ID;
    while (1) {
        tlogv("++ misc agent loop ++\n");
        int ret = ioctl(g_miscFd, (int)TC_NS_CLIENT_IOCTL_WAIT_EVENT, AGENT_MISC_ID);
        if (ret) {
            tloge("misc agent wait event failed\n");
            break;
        }

        tlogv("misc agent wake up and working!!\n");
        switch (transControl->cmd) {
            case SEC_GET_TIME:
                tlogv("sec get time of day\n");
                GetTimeWork(transControl);
                break;
            default:
                tloge("misc agent error cmd\n");
                break;
        }
        Barriers();
        transControl->magic = AGENT_MISC_ID;
        Barriers();
        ret = ioctl(g_miscFd, (int)TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, AGENT_MISC_ID);
        if (ret) {
            tloge("misc agent send reponse failed\n");
            break;
        }
        tlogv("-- misc agent loop --\n");
    }

    return NULL;
}

static int AgentInit(unsigned int id, uint8_t **control)
{
    int ret;
    struct AgentIoctlArgs args = { 0 };

    if (control == NULL) {
        return -1;
    }
    int fd = open(TC_NS_CLIENT_DEV_NAME, O_RDWR);
    if (fd < 0) {
        tloge("open tee client dev failed, fd is %d\n", fd);
        return -1;
    }

    /* register agent */
    args.id         = id;
    args.bufferSize = TRANS_BUFF_SIZE;
    ret             = ioctl(fd, (int)TC_NS_CLIENT_IOCTL_REGISTER_AGENT, &args);
    if (ret) {
        (void)close(fd);
        tloge("ioctl failed\n");
        return -1;
    }

    *control = (uint8_t *)args.buffer;
    return fd;
}

static void AgentExit(unsigned int id, int fd)
{
    int ret;

    if (fd == -1) {
        return;
    }

    ret = ioctl(fd, (int)TC_NS_CLIENT_IOCTL_UNREGISTER_AGENT, id);
    if (ret) {
        tloge("ioctl failed\n");
    }

    (void)close(fd);
}

enum LateInitIndex {
    FS_LATE_INIT = 0x1,
};

#define SLEEP_TIME (100 * 1000 * 1000)
static void *InitLateWorkThread(void *dummy)
{
    unsigned int index            = 0;
    struct timespec ts;
    ts.tv_sec  = 0;
    ts.tv_nsec = SLEEP_TIME;

    (void)dummy;
    tlogd("now start to late init\n");

    int fd = open(TC_NS_CLIENT_DEV_NAME, O_RDWR);
    if (fd < 0) {
        tloge("open tee client dev failed, fd is %d\n", fd);
        return NULL;
    }
    while (true) {
        nanosleep(&ts, NULL);
        if (IsUserDataReady() == 1) {
            index = FS_LATE_INIT;
            break;
        }
        tloge("userdata is not ready, sleep!\n");
    }

    int ret = ioctl(fd, (int)TC_NS_CLIENT_IOCTL_LATEINIT, index);
    if (ret) {
        tloge("failed to set late init.\n");
    }

    close(fd);
    return NULL;
}

static struct SecStorageType *g_fsControl                = NULL;
static struct MiscControlType *g_miscControl             = NULL;
static struct SecAgentControlType *g_secLoadAgentControl = NULL;

static int g_fsThreadFlag = 0;

static int ProcessAgentInit(void)
{
    int ret;

    g_fsThreadFlag = 1;
    g_fsFd = AgentInit(AGENT_FS_ID, (uint8_t **)(&g_fsControl));
    if (g_fsFd < 0) {
        tloge("fs agent init failed\n");
        g_fsThreadFlag = 0;
    }

    g_miscFd = AgentInit(AGENT_MISC_ID, (uint8_t **)(&g_miscControl));
    if (g_miscFd < 0) {
        tloge("misc agent init failed\n");
        goto ERROR1;
    }

    ret = AgentInit(SECFILE_LOAD_AGENT_ID, (uint8_t **)(&g_secLoadAgentControl));
    if (ret < 0) {
        tloge("secfile load agent init failed\n");
        goto ERROR2;
    }

    SetSecLoadAgentFd(ret);
    tloge("processAgent init ok\n");

    return 0;
ERROR2:
    AgentExit(AGENT_MISC_ID, g_miscFd);
    g_miscFd      = -1;
    g_miscControl = NULL;

ERROR1:
    if (g_fsThreadFlag == 1) {
        AgentExit(AGENT_FS_ID, g_fsFd);
        g_fsFd         = -1;
        g_fsControl    = NULL;
        g_fsThreadFlag = 0;
    }
    return -1;
}

static void ProcessAgentExit(void)
{
    if (g_fsThreadFlag == 1) {
        AgentExit(AGENT_FS_ID, g_fsFd);
        g_fsFd      = -1;
        g_fsControl = NULL;
    }

    AgentExit(AGENT_MISC_ID, g_miscFd);
    g_miscFd      = -1;
    g_miscControl = NULL;

    AgentExit(SECFILE_LOAD_AGENT_ID, GetSecLoadAgentFd());
    SetSecLoadAgentFd(-1);
    g_secLoadAgentControl = NULL;
}

int main(int argc, char **argv)
{
    pthread_t fsThread               = (pthread_t)-1;
    pthread_t secfileLoadAgentThread = (pthread_t)-1;
    pthread_t miscThread             = (pthread_t)-1;
    pthread_t lateInitThread         = (pthread_t)-1;

    TcuAuthentication();

    int ret = ProcessAgentInit();
    if (ret) {
        return ret;
    }

    if (g_fsThreadFlag == 1) {
        (void)pthread_create(&fsThread, NULL, FsWorkThread, g_fsControl);
        tloge("FsWorkThread create ok\n");
    }

    (void)pthread_create(&secfileLoadAgentThread, NULL, SecfileLoadAgentThread, g_secLoadAgentControl);

    (void)pthread_create(&miscThread, NULL, MiscWorkThread, g_miscControl);
    (void)pthread_create(&lateInitThread, NULL, InitLateWorkThread, NULL);

    (void)pthread_join(lateInitThread, NULL);
    if (g_fsThreadFlag == 1) {
        (void)pthread_join(fsThread, NULL);
    }
    (void)pthread_join(secfileLoadAgentThread, NULL);
    (void)pthread_join(miscThread, NULL);

    ProcessAgentExit();
    return 0;
}
