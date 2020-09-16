/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "menuconfig.h"
#ifdef LOSCFG_FS_VFS
#include "errno.h"
#include "unistd.h"
#include "fs/fd_table.h"
#include "fs/file.h"
#include "fs/fs.h"
#include "fs/fs_operation.h"
#include "sys/mount.h"
#include "los_task_pri.h"
#include "sys/utsname.h"
#include "sys/uio.h"
#include "poll.h"
#include "sys/prctl.h"
#include "los_exec_elf.h"
#include "los_syscall.h"
#include "dirent.h"
#include "user_copy.h"
#include "los_vm_map.h"
#include "los_memory.h"
#include "los_strncpy_from_user.h"
#include "fs_other.h"
#include "fs_file.h"
#include "capability_type.h"
#include "capability_api.h"

static int UserPathCopy(const char *userPath, char **pathBuf)
{
    int ret;

    *pathBuf = (char *)LOS_MemAlloc(OS_SYS_MEM_ADDR, PATH_MAX + 1);
    if (*pathBuf == NULL) {
        return -ENOMEM;
    }

    ret = LOS_StrncpyFromUser(*pathBuf, userPath, PATH_MAX + 1);
    if (ret < 0) {
        LOS_MemFree(OS_SYS_MEM_ADDR, *pathBuf);
        *pathBuf = NULL;
        return ret;
    } else if (ret > PATH_MAX) {
        LOS_MemFree(OS_SYS_MEM_ADDR, *pathBuf);
        *pathBuf = NULL;
        return -ENAMETOOLONG;
    }
    (*pathBuf)[ret] = '\0';

    return 0;
}

static int UserIovItemCheck(const struct iovec *iov, const int iovcnt)
{
    int i;
    for (i = 0; i < iovcnt; ++i) {
        if (iov[i].iov_len == 0) {
            continue;
        }

        if (!LOS_IsUserAddressRange((vaddr_t)(UINTPTR)iov[i].iov_base, iov[i].iov_len)) {
            return i;
        }
    }
    return iovcnt;
}

static int UserIovCopy(struct iovec **iovBuf, const struct iovec *iov, const int iovcnt, int *valid_iovcnt)
{
    int ret;
    int bufLen = iovcnt * sizeof(struct iovec);
    if (bufLen <= 0) {
        return -EINVAL;
    }

    *iovBuf = (struct iovec*)LOS_MemAlloc(OS_SYS_MEM_ADDR, bufLen);
    if (*iovBuf == NULL) {
        return -ENOMEM;
    }

    if (LOS_ArchCopyFromUser(*iovBuf, iov, bufLen) != 0) {
        LOS_MemFree(OS_SYS_MEM_ADDR, *iovBuf);
        return -EFAULT;
    }

    ret = UserIovItemCheck(*iovBuf, iovcnt);
    if (ret == 0) {
        LOS_MemFree(OS_SYS_MEM_ADDR, *iovBuf);
        return -EFAULT;
    }

    *valid_iovcnt = ret;
    return 0;
}

static int PollfdToSystem(struct pollfd *fds, nfds_t nfds, int **pollFdsBak)
{
    if ((nfds != 0 && fds == NULL) || (pollFdsBak == NULL)) {
        set_errno(EINVAL);
        return -1;
    }
    if (nfds == 0) {
        return 0;
    }
    int *pollFds = (int *)malloc(sizeof(int) * nfds);
    if (pollFds == NULL) {
        set_errno(ENOMEM);
        return -1;
    }
    for (int i = 0; i < nfds; ++i) {
        struct pollfd *p_fds = &fds[i];
        pollFds[i] = p_fds->fd;
        if (p_fds->fd < 0) {
            set_errno(EBADF);
            free(pollFds);
            return -1;
        }
        p_fds->fd = GetAssociatedSystemFd(p_fds->fd);
    }
    *pollFdsBak = pollFds;
    return 0;
}

static void RestorePollfd(struct pollfd *fds, nfds_t nfds, const int *pollFds)
{
    if ((fds == NULL) || (pollFds == NULL)) {
        return;
    }
    for (int i = 0; i < nfds; ++i) {
        struct pollfd *p_fds = &fds[i];
        p_fds->fd = pollFds[i];
    }
}

static int UserPoll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    int *pollFds = NULL;
    int ret = PollfdToSystem(fds, nfds, &pollFds);
    if (ret < 0) {
        return -1;
    }

    ret = poll(fds, nfds, timeout);

    RestorePollfd(fds, nfds, pollFds);

    free(pollFds);
    return ret;
}

static int FcntlDupFd(int fd, void *arg, int (*fcntl)(int, int, ...))
{
    int ret;
    int minFd = MIN_START_FD;
    int leastFd = (intptr_t)arg;

    if (CheckProcessFd(leastFd) != OK) {
        return -EINVAL;
    }
    int procFd = AllocLowestProcessFd(leastFd);
    if (procFd < 0) {
        return -EMFILE;
    }
    arg = (void *)minFd;

    ret = fcntl(fd, F_DUPFD, arg);
    if (ret < 0) {
        FreeProcessFd(procFd);
        return -get_errno();
    }
    AssociateSystemFd(procFd, ret);
    ret = procFd;

    return ret;
}

int SysClose(int fd)
{
    int ret;

    /* Process fd convert to system global fd */
    int sysfd = DisassociateProcessFd(fd);

    ret = close(sysfd);
    if (ret < 0) {
        AssociateSystemFd(fd, sysfd);
        return -get_errno();
    }
    FreeProcessFd(fd);
    return ret;
}

ssize_t SysRead(int fd, void *buf, size_t nbytes)
{
    int ret;

    if (nbytes == 0) {
        return 0;
    }

    if (!LOS_IsUserAddressRange((vaddr_t)(UINTPTR)buf, nbytes)) {
        return -EFAULT;
    }

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    ret = read(fd, buf, nbytes);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

ssize_t SysWrite(int fd, const void *buf, size_t nbytes)
{
    int ret;

    if (nbytes == 0) {
        return 0;
    }

    if (!LOS_IsUserAddressRange((vaddr_t)(UINTPTR)buf, nbytes)) {
        return -EFAULT;
    }

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    ret = write(fd, buf, nbytes);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysOpen(const char *path, int oflags, ...)
{
    int ret;
    mode_t mode;
    char *pathRet = NULL;
    int procFd = -1;

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    procFd = AllocProcessFd();
    if (procFd  < 0) {
        ret = -EMFILE;
        goto OUT;
    }

    if ((unsigned int)oflags & O_DIRECTORY) {
        ret = do_opendir(pathRet, oflags);
        if (ret < 0) {
            ret = -get_errno();
        }
        goto OUT;
    }

#ifdef LOSCFG_FILE_MODE
    va_list ap;

    va_start(ap, oflags);
    mode = va_arg(ap, int);
    va_end(ap);
#else
    mode = 0666; /* 0666: File read-write properties. */
#endif

    ret = do_open(AT_FDCWD, (path ? pathRet : NULL), oflags, mode);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    if (ret >= 0) {
        AssociateSystemFd(procFd, ret);
        ret = procFd;
    } else {
        FreeProcessFd(procFd);
    }

    return ret;
}

int SysCreat(const char *pathname, mode_t mode)
{
    int ret = 0;
    char *pathRet = NULL;

    if (pathname != NULL) {
        ret = UserPathCopy(pathname, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    int procFd = AllocProcessFd();
    if (procFd  < 0) {
        ret = -EMFILE;
        goto OUT;
    }

    ret = open((pathname ? pathRet : NULL), O_CREAT | O_TRUNC | O_WRONLY, mode);
    if (ret < 0) {
        FreeProcessFd(procFd);
        ret = -get_errno();
    } else {
        AssociateSystemFd(procFd, ret);
        ret = procFd;
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysUnlink(const char *pathname)
{
    int ret;
    char *pathRet = NULL;

    if (pathname != NULL) {
        ret = UserPathCopy(pathname, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = do_unlink(AT_FDCWD, (pathname ? pathRet : NULL));
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysExecve(const char *fileName, char *const *argv, char *const *envp)
{
    return LOS_DoExecveFile(fileName, argv, envp);
}

int SysChdir(const char *path)
{
    int ret;
    char *pathRet = NULL;

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = chdir(path ? pathRet : NULL);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

off_t SysLseek(int fd, off_t offset, int whence)
{
    int ret;
    struct file *filep = NULL;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    /* Get the file structure corresponding to the file descriptor. */
    ret = fs_getfilep(fd, &filep);
    if (ret < 0) {
        /* The errno value has already been set */
        return (off_t)-get_errno();
    }

    /* libc seekdir function should set the whence to SEEK_SET, so we can discard
     * the whence argument here */
    if (filep->f_oflags & O_DIRECTORY) {
        /* defensive coding */
        if (filep->f_dir == NULL) {
            return (off_t)-EINVAL;
        }
        if (offset == 0) {
            rewinddir(filep->f_dir);
        } else {
            seekdir(filep->f_dir, offset);
        }
        ret = telldir(filep->f_dir);
        if (ret < 0) {
            return (off_t)-get_errno();
        }
        return ret;
    }

    /* Then let file_seek do the real work */
    ret = file_seek(filep, offset, whence);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

off64_t SysLseek64(int fd, int offsetHigh, int offsetLow, off64_t *result, int whence)
{
    off64_t ret;
    int retVal;
    struct file *filep = NULL;
    off64_t offset = ((off64_t)offsetHigh << 32) + (uint)offsetLow; /* 32: offsetHigh is high 32 bits */

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    /* Get the file structure corresponding to the file descriptor. */
    ret = fs_getfilep(fd, &filep);
    if (ret < 0) {
        /* The errno value has already been set */
        return (off64_t)-get_errno();
    }

    /* libc seekdir function should set the whence to SEEK_SET, so we can discard
     * the whence argument here */
    if (filep->f_oflags & O_DIRECTORY) {
        /* defensive coding */
        if (filep->f_dir == NULL) {
            return (off64_t)-EINVAL;
        }
        if (offsetLow == 0) {
            rewinddir(filep->f_dir);
        } else {
            seekdir(filep->f_dir, offsetLow);
        }
        ret = telldir(filep->f_dir);
        if (ret < 0) {
            return (off64_t)-get_errno();
        }
        goto out;
    }

    /* Then let file_seek do the real work */
    ret = file_seek64(filep, offset, whence);
    if (ret < 0) {
        return (off64_t)-get_errno();
    }

out:
    retVal = LOS_ArchCopyToUser(result, &ret, sizeof(off64_t));
    if (retVal != 0) {
        return -EFAULT;
    }

    return 0;
}

int SysMount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags,
             const void *data)
{
    int ret;
    char *sourceRet = NULL;
    char *targetRet = NULL;
    char fstypeRet[FILESYSTEM_TYPE_MAX + 1] = {0};

    if (!IsCapPermit(CAP_FS_MOUNT)) {
        return -EPERM;
    }

    if (target != NULL) {
        ret = UserPathCopy(target, &targetRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    if (filesystemtype != NULL) {
        ret = LOS_StrncpyFromUser(fstypeRet, filesystemtype, FILESYSTEM_TYPE_MAX + 1);
        if (ret < 0) {
            goto OUT;
        } else if (ret > FILESYSTEM_TYPE_MAX) {
            ret = -ENODEV;
            goto OUT;
        }

        if (strcmp(fstypeRet, "ramfs") && (source != NULL)) {
            ret = UserPathCopy(source, &sourceRet);
            if (ret != 0) {
                goto OUT;
            }
        }
    }

    ret = mount(sourceRet, targetRet, (filesystemtype ? fstypeRet : NULL), mountflags, data);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (sourceRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, sourceRet);
    }
    if (targetRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, targetRet);
    }
    return ret;
}

int SysUmount(const char *target)
{
    int ret;
    char *pathRet = NULL;

    if (!IsCapPermit(CAP_FS_MOUNT)) {
        return -EPERM;
    }

    if (target != NULL) {
        ret = UserPathCopy(target, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = umount(target ? pathRet : NULL);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysAccess(const char *path, int amode)
{
    int ret;
    struct stat buf;
    char *pathRet = NULL;

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = stat((path ? pathRet : NULL), &buf);
    if (ret != 0) {
        ret = -get_errno();
    }

    if (VfsPermissionCheck(buf.st_uid, buf.st_gid, buf.st_mode, amode)) {
        ret = -EACCES;
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }

    return ret;
}

int SysRename(const char *oldpath, const char *newpath)
{
    int ret;
    char *pathOldRet = NULL;
    char *pathNewRet = NULL;

    if (oldpath != NULL) {
        ret = UserPathCopy(oldpath, &pathOldRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    if (newpath != NULL) {
        ret = UserPathCopy(newpath, &pathNewRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = do_rename(AT_FDCWD, (oldpath ? pathOldRet : NULL), AT_FDCWD,
                    (newpath ? pathNewRet : NULL));
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathOldRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathOldRet);
    }
    if (pathNewRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathNewRet);
    }
    return ret;
}

int SysMkdir(const char *pathname, mode_t mode)
{
    int ret;
    char *pathRet = NULL;

    if (pathname != NULL) {
        ret = UserPathCopy(pathname, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = do_mkdir(AT_FDCWD, (pathname ? pathRet : NULL), mode);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysRmdir(const char *pathname)
{
    int ret;
    char *pathRet = NULL;

    if (pathname != NULL) {
        ret = UserPathCopy(pathname, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = do_rmdir(AT_FDCWD, (pathname ? pathRet : NULL));
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysDup(int fd)
{
    int ret = -1;

    int procFd = AllocProcessFd();
    if (procFd  < 0) {
        return -EMFILE;
    }

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    ret = dup(fd);
    if (ret < 0) {
        FreeProcessFd(procFd);
        return -get_errno();
    }

    AssociateSystemFd(procFd, ret);

    return procFd;
}

void SysSync(void)
{
    sync();
}

int SysUmount2(const char *target, int flags)
{
    if (flags != 0) {
        return -ENOSYS;
    }
    return SysUmount(target);
}

int SysIoctl(int fd, int req, void *arg)
{
    int ret;
    unsigned int size = _IOC_SIZE((unsigned int)req);
    unsigned int dir = _IOC_DIR((unsigned int)req);
    if ((size == 0) && (dir != _IOC_NONE)) {
        return -EINVAL;
    }

    if ((dir != _IOC_NONE) && (((void *)(uintptr_t)arg) == NULL)) {
        return -EINVAL;
    }

    if ((dir & _IOC_READ) || (dir & _IOC_WRITE)) {
        if (!LOS_IsUserAddressRange((uintptr_t)arg, size)) {
            return -EFAULT;
        }
    }

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    ret = ioctl(fd, req, arg);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysFcntl(int fd, int cmd, void *arg)
{
    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    if (cmd == F_DUPFD) {
        return FcntlDupFd(fd, arg, fcntl);
    }
    int ret = fcntl(fd, cmd, arg);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysPipe(int pipefd[2]) /* 2 : pipe fds for read and write */
{
    int ret;
    int pipeFdIntr[2] = {0}; /* 2 : pipe fds for read and write */

    int procFd0 = AllocProcessFd();
    if (procFd0 < 0) {
        return -EMFILE;
    }
    int procFd1 = AllocProcessFd();
    if (procFd1 < 0) {
        FreeProcessFd(procFd0);
        return -EMFILE;
    }

    ret = pipe(pipeFdIntr);
    if (ret < 0) {
        FreeProcessFd(procFd0);
        FreeProcessFd(procFd1);
        return -get_errno();
    }
    int sysPipeFd0 = pipeFdIntr[0];
    int sysPipeFd1 = pipeFdIntr[1];

    AssociateSystemFd(procFd0, sysPipeFd0);
    AssociateSystemFd(procFd1, sysPipeFd1);

    pipeFdIntr[0] = procFd0;
    pipeFdIntr[1] = procFd1;

    ret = LOS_ArchCopyToUser(pipefd, pipeFdIntr, sizeof(pipeFdIntr));
    if (ret != 0) {
        FreeProcessFd(procFd0);
        FreeProcessFd(procFd1);
        close(sysPipeFd0);
        close(sysPipeFd1);
        return -EFAULT;
    }
    return ret;
}

int SysDup2(int fd1, int fd2)
{
    int ret;
    int sysfd1 = GetAssociatedSystemFd(fd1);
    int sysfd2 = GetAssociatedSystemFd(fd2);

    /* Check if the param is valid, note that: socket fd is not support dup2 */
    if ((sysfd1 < 0) || (sysfd1 >= CONFIG_NFILE_DESCRIPTORS) || (CheckProcessFd(fd2) != OK)) {
        return -EBADF;
    }

    /* Handle special circumstances */
    if (fd1 == fd2) {
        return fd2;
    }

    ret = AllocSpecifiedProcessFd(fd2);
    if (ret != OK) {
        return ret;
    }

    /* close the sysfd2 in need */
    if (sysfd2 >= 0) {
        ret = close(sysfd2);
        if (ret < 0) {
            AssociateSystemFd(fd2, sysfd2);
            return -get_errno();
        }
    }

    files_refer(sysfd1);
    AssociateSystemFd(fd2, sysfd1);
    return fd2;
}

static int SelectParamCheckCopy(fd_set *readfds, fd_set *writefds, fd_set *exceptfds, fd_set **fdsBuf)
{
    fd_set *readfdsRet = NULL;
    fd_set *writefdsRet = NULL;
    fd_set *exceptfdsRet = NULL;

    *fdsBuf = (fd_set *)LOS_MemAlloc(OS_SYS_MEM_ADDR, sizeof(fd_set) * 3); /* 3: three param need check and copy */
    if (*fdsBuf == NULL) {
        return -ENOMEM;
    }

    readfdsRet = *fdsBuf;        /* LOS_MemAlloc 3 sizeof(fd_set) space,first use for readfds */
    writefdsRet = *fdsBuf + 1;   /* 1: LOS_MemAlloc 3 sizeof(fd_set) space,second use for writefds */
    exceptfdsRet = *fdsBuf + 2;  /* 2: LOS_MemAlloc 3 sizeof(fd_set) space,thired use for exceptfds */

    if (readfds != NULL) {
        if (LOS_ArchCopyFromUser(readfdsRet, readfds, sizeof(fd_set)) != 0) {
            LOS_MemFree(OS_SYS_MEM_ADDR, *fdsBuf);
            return -EFAULT;
        }
    }

    if (writefds != NULL) {
        if (LOS_ArchCopyFromUser(writefdsRet, writefds, sizeof(fd_set)) != 0) {
            LOS_MemFree(OS_SYS_MEM_ADDR, *fdsBuf);
            return -EFAULT;
        }
    }

    if (exceptfds != NULL) {
        if (LOS_ArchCopyFromUser(exceptfdsRet, exceptfds, sizeof(fd_set)) != 0) {
            LOS_MemFree(OS_SYS_MEM_ADDR, *fdsBuf);
            return -EFAULT;
        }
    }

    return 0;
}

int SysSelect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
    int ret;
    fd_set *fdsRet = NULL;
    fd_set *readfdsRet = NULL;
    fd_set *writefdsRet = NULL;
    fd_set *exceptfdsRet = NULL;
    struct timeval timeoutRet = {0};

    ret = SelectParamCheckCopy(readfds, writefds, exceptfds, &fdsRet);
    if (ret != 0) {
        return ret;
    }

    readfdsRet = fdsRet;        /* LOS_MemAlloc 3 sizeof(fd_set) space,first use for readfds */
    writefdsRet = fdsRet + 1;   /* 1: LOS_MemAlloc 3 sizeof(fd_set) space,second use for writefds */
    exceptfdsRet = fdsRet + 2;  /* 2: LOS_MemAlloc 3 sizeof(fd_set) space,thired use for exceptfds */

    if (timeout != NULL) {
        if (LOS_ArchCopyFromUser(&timeoutRet, timeout, sizeof(struct timeval)) != 0) {
            goto ERROUT;
        }
    }

    ret = do_select(nfds, (readfds ? readfdsRet : NULL), (writefds ? writefdsRet : NULL),
                 (exceptfds ? exceptfdsRet : NULL), (timeout ? (&timeoutRet) : NULL), UserPoll);
    if (ret < 0) {
        LOS_MemFree(OS_SYS_MEM_ADDR, fdsRet);
        return -get_errno();
    }

    if (readfds != NULL) {
        if (LOS_ArchCopyToUser(readfds, readfdsRet, sizeof(fd_set)) != 0) {
            goto ERROUT;
        }
    }

    if (writefds != NULL) {
        if (LOS_ArchCopyToUser(writefds, writefdsRet, sizeof(fd_set)) != 0) {
            goto ERROUT;
        }
    }

    if (exceptfds != 0) {
        if (LOS_ArchCopyToUser(exceptfds, exceptfdsRet, sizeof(fd_set)) != 0) {
            goto ERROUT;
        }
    }

    LOS_MemFree(OS_SYS_MEM_ADDR, fdsRet);
    return ret;

ERROUT:
    LOS_MemFree(OS_SYS_MEM_ADDR, fdsRet);
    return -EFAULT;
}

int SysTruncate(const char *path, off_t length)
{
    int ret;
    int fd = 0;
    char *pathRet = NULL;

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    fd = open((path ? pathRet : NULL), O_RDWR);
    if (fd < 0) {
        /* The errno value has already been set */
        ret = -get_errno();
        goto OUT;
    }

    ret = ftruncate(fd, length);
    close(fd);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysTruncate64(const char *path, off64_t length)
{
    int ret;
    int fd = 0;
    char *pathRet = NULL;

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    fd = open((path ? pathRet : NULL), O_RDWR);
    if (fd < 0) {
        /* The errno value has already been set */
        ret = -get_errno();
        goto OUT;
    }

    ret = ftruncate64(fd, length);
    close(fd);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysFtruncate(int fd, off_t length)
{
    int ret;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    ret = ftruncate(fd, length);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysStatfs(const char *path, struct statfs *buf)
{
    int ret;
    char *pathRet = NULL;
    struct statfs bufRet = {0};

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = statfs((path ? pathRet : NULL), (buf ? (&bufRet) : NULL));
    if (ret < 0) {
        ret = -get_errno();
        goto OUT;
    }

    ret = LOS_ArchCopyToUser(buf, &bufRet, sizeof(struct statfs));
    if (ret != 0) {
        ret = -EFAULT;
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysStatfs64(const char *path, size_t sz, struct statfs *buf)
{
    int ret;
    char *pathRet = NULL;
    struct statfs bufRet = {0};

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    if (sz != sizeof(*buf)) {
        ret = -EINVAL;
        goto OUT;
    }

    ret = statfs((path ? pathRet : NULL), (buf ? (&bufRet) : NULL));
    if (ret < 0) {
        ret = -get_errno();
        goto OUT;
    }

    ret = LOS_ArchCopyToUser(buf, &bufRet, sizeof(struct statfs));
    if (ret != 0) {
        ret = -EFAULT;
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysStat(const char *path, struct stat *buf)
{
    int ret;
    char *pathRet = NULL;
    struct stat bufRet = {0};

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = stat((path ? pathRet : NULL), (buf ? (&bufRet) : NULL));
    if (ret < 0) {
        ret = -get_errno();
        goto OUT;
    }

    ret = LOS_ArchCopyToUser(buf, &bufRet, sizeof(struct stat));
    if (ret != 0) {
        ret = -EFAULT;
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysLstat(const char *path, struct stat *buffer)
{
    int ret;
    char *pathRet = NULL;
    struct stat bufRet = {0};

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = stat((path ? pathRet : NULL), (buffer ? (&bufRet) : NULL));
    if (ret < 0) {
        ret = -get_errno();
        goto OUT;
    }

    ret = LOS_ArchCopyToUser(buffer, &bufRet, sizeof(struct stat));
    if (ret != 0) {
        ret = -EFAULT;
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysFstat(int fd, struct stat *buf)
{
    int ret;
    struct stat bufRet = {0};
    struct file *filep = NULL;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    ret = fs_getfilep(fd, &filep);
    if (ret < 0) {
        return -get_errno();
    }

    if (filep->f_oflags & O_DIRECTORY) {
        return -EBADF;
    }

    ret = stat(filep->f_path, (buf ? (&bufRet) : NULL));
    if (ret < 0) {
        return -get_errno();
    }

    ret = LOS_ArchCopyToUser(buf, &bufRet, sizeof(struct stat));
    if (ret != 0) {
        return -EFAULT;
    }

    return ret;
}

int SysStatx(int fd, const char *restrict path, int flag, unsigned mask, struct statx *restrict stx)
{
    return -ENOSYS;
}

int SysFsync(int fd)
{
    int ret;
    struct file *filep = NULL;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    /* Get the file structure corresponding to the file descriptor. */
    ret = fs_getfilep(fd, &filep);
    if (ret < 0) {
        /* The errno value has already been set */
        return -get_errno();
    }

    if (filep->f_oflags & O_DIRECTORY) {
        return -EBADF;
    }

    /* Perform the fsync operation */
    ret = file_fsync(filep);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

ssize_t SysReadv(int fd, const struct iovec *iov, int iovcnt)
{
    int ret;
    int valid_iovcnt = -1;
    struct iovec *iovRet = NULL;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);
    if ((iov == NULL) || (iovcnt <= 0) || (iovcnt > IOV_MAX)) {
        ret = vfs_readv(fd, iov, iovcnt, NULL);
        return -get_errno();
    }

    ret = UserIovCopy(&iovRet, iov, iovcnt, &valid_iovcnt);
    if (ret != 0) {
        return ret;
    }

    if (valid_iovcnt <= 0) {
        ret = -EFAULT;
        goto OUT;
    }

    ret = vfs_readv(fd, iovRet, valid_iovcnt, NULL);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    (void)LOS_MemFree(OS_SYS_MEM_ADDR, iovRet);
    return ret;
}

ssize_t SysWritev(int fd, const struct iovec *iov, int iovcnt)
{
    int ret;
    int valid_iovcnt = -1;
    struct iovec *iovRet = NULL;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);
    if ((iov == NULL) || (iovcnt <= 0) || (iovcnt > IOV_MAX)) {
        ret = writev(fd, iov, iovcnt);
        return -get_errno();
    }

    ret = UserIovCopy(&iovRet, iov, iovcnt, &valid_iovcnt);
    if (ret != 0) {
        return ret;
    }

    if (valid_iovcnt != iovcnt) {
        ret = -EFAULT;
        goto OUT_FREE;
    }

    ret = writev(fd, iovRet, valid_iovcnt);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT_FREE:
    (void)LOS_MemFree(OS_SYS_MEM_ADDR, iovRet);
    return ret;
}

int SysPoll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    int ret;
    struct pollfd *kfds = NULL;

    if ((nfds >= MAX_POLL_NFDS) || (nfds == 0) || (fds == NULL)) {
        return -EINVAL;
    }

    kfds = (struct pollfd *)malloc(sizeof(struct pollfd) * nfds);
    if (kfds != NULL) {
        if (LOS_ArchCopyFromUser(kfds, fds, sizeof(struct pollfd) * nfds) != 0) {
            ret = -EFAULT;
            goto OUT_KFD;
        }
    }

    int *pollFds = NULL;
    ret = PollfdToSystem(kfds, nfds, &pollFds);
    if (ret < 0) {
        ret = -get_errno();
        goto OUT_KFD;
    }

    ret = poll(kfds, nfds, timeout);
    if (ret < 0) {
        ret = -get_errno();
        goto OUT;
    }

    if (kfds != NULL) {
        RestorePollfd(kfds, nfds, pollFds);
        if (LOS_ArchCopyToUser(fds, kfds, sizeof(struct pollfd) * nfds) != 0) {
            ret = -EFAULT;
            goto OUT;
        }
    }

OUT:
    free(pollFds);
OUT_KFD:
    free(kfds);
    return ret;
}

int SysPrctl(int option, ...)
{
    unsigned long name;
    va_list ap;
    errno_t err;

    va_start(ap, option);
    if (option != PR_SET_NAME) {
        PRINT_ERR("%s: %d, no support option : 0x%x\n", __FUNCTION__, __LINE__, option);
        err = EOPNOTSUPP;
        goto ERROR;
    }

    name = va_arg(ap, unsigned long);
    err = OsSetCurrTaskName((const char *)(uintptr_t)name);
    if (err != LOS_OK) {
        goto ERROR;
    }

    va_end(ap);
    return ENOERR;

ERROR:
    va_end(ap);
    return -err;
}

ssize_t SysPread64(int fd, void *buf, size_t nbytes, off64_t offset)
{
    int ret, retVal;
    char *bufRet = NULL;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    if (nbytes == 0) {
        ret = pread64(fd, buf, nbytes, offset);
        if (ret < 0) {
            return -get_errno();
        } else {
            return ret;
        }
    }

    bufRet = (char *)LOS_MemAlloc(OS_SYS_MEM_ADDR, nbytes);
    if (bufRet == NULL) {
        return -ENOMEM;
    }

    ret = pread64(fd, (buf ? bufRet : NULL), nbytes, offset);
    if (ret < 0) {
        LOS_MemFree(OS_SYS_MEM_ADDR, bufRet);
        return -get_errno();
    }

    retVal = LOS_ArchCopyToUser(buf, bufRet, ret);
    if (retVal != 0) {
        LOS_MemFree(OS_SYS_MEM_ADDR, bufRet);
        return -EFAULT;
    }

    LOS_MemFree(OS_SYS_MEM_ADDR, bufRet);
    return ret;
}

ssize_t SysPwrite64(int fd, const void *buf, size_t nbytes, off64_t offset)
{
    int ret;
    char *bufRet = NULL;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    if (nbytes == 0) {
        ret = pwrite64(fd, buf, nbytes, offset);
        if (ret < 0) {
            return -get_errno();
        }
        return ret;
    }

    bufRet = (char *)LOS_MemAlloc(OS_SYS_MEM_ADDR, nbytes);
    if (bufRet == NULL) {
        return -ENOMEM;
    }

    if (buf != NULL) {
        ret = LOS_ArchCopyFromUser(bufRet, buf, nbytes);
        if (ret != 0) {
            LOS_MemFree(OS_SYS_MEM_ADDR, bufRet);
            return -EFAULT;
        }
    }

    ret = pwrite64(fd, (buf ? bufRet : NULL), nbytes, offset);
    if (ret < 0) {
        LOS_MemFree(OS_SYS_MEM_ADDR, bufRet);
        return -get_errno();
    }

    LOS_MemFree(OS_SYS_MEM_ADDR, bufRet);
    return ret;
}

char *SysGetcwd(char *buf, size_t n)
{
    char *ret = NULL;
    char *bufRet = NULL;
    int retVal;

    bufRet = (char *)LOS_MemAlloc(OS_SYS_MEM_ADDR, n);
    if (bufRet == NULL) {
        return (char *)(intptr_t)-ENOMEM;
    }
    (void)memset_s(bufRet, n, 0, n);

    ret = getcwd((buf ? bufRet : NULL), n);
    if (ret == NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, bufRet);
        return (char *)(intptr_t)-get_errno();
    }

    retVal = LOS_ArchCopyToUser(buf, bufRet, n);
    if (retVal != 0) {
        LOS_MemFree(OS_SYS_MEM_ADDR, bufRet);
        return (char *)(intptr_t)-EFAULT;
    }
    ret = buf;

    LOS_MemFree(OS_SYS_MEM_ADDR, bufRet);
    return ret;
}

ssize_t SysSendFile(int outfd, int infd, off_t *offset, size_t count)
{
    int ret, retVal;
    off_t offsetRet;

    retVal = LOS_ArchCopyFromUser(&offsetRet, offset, sizeof(off_t));
    if (retVal != 0) {
        return -EFAULT;
    }

    /* Process fd convert to system global fd */
    outfd = GetAssociatedSystemFd(outfd);
    infd = GetAssociatedSystemFd(infd);

    ret = sendfile(outfd, infd, (offset ? (&offsetRet) : NULL), count);
    if (ret < 0) {
        return -get_errno();
    }

    retVal = LOS_ArchCopyToUser(offset, &offsetRet, sizeof(off_t));
    if (retVal != 0) {
        return -EFAULT;
    }

    return ret;
}

int SysFtruncate64(int fd, off64_t length)
{
    int ret;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    ret = ftruncate64(fd, length);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysOpenat(int dirfd, const char *path, int oflags, ...)
{
    int ret;
    char *pathRet = NULL;
    mode_t mode;
#ifdef LOSCFG_FILE_MODE
    va_list ap;

    va_start(ap, oflags);
    mode = va_arg(ap, int);
    va_end(ap);
#else
    mode = 0666; /* 0666: File read-write properties. */
#endif

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    if (dirfd != AT_FDCWD) {
        /* Process fd convert to system global fd */
        dirfd = GetAssociatedSystemFd(dirfd);
    }

    ret = do_open(dirfd, (path ? pathRet : NULL), oflags, mode);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysMkdirat(int dirfd, const char *pathname, mode_t mode)
{
    int ret;
    char *pathRet = NULL;

    if (pathname != NULL) {
        ret = UserPathCopy(pathname, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    if (dirfd != AT_FDCWD) {
        /* Process fd convert to system global fd */
        dirfd = GetAssociatedSystemFd(dirfd);
    }

    ret = do_mkdir(dirfd, (pathname ? pathRet : NULL), mode);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysUnlinkat(int dirfd, const char *pathname, int flag)
{
    int ret;
    char *pathRet = NULL;

    if (pathname != NULL) {
        ret = UserPathCopy(pathname, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    if (dirfd != AT_FDCWD) {
        /* Process fd convert to system global fd */
        dirfd = GetAssociatedSystemFd(dirfd);
    }

    ret = unlinkat(dirfd, (pathname ? pathRet : NULL), flag);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysRenameat(int oldfd, const char *oldpath, int newdfd, const char *newpath)
{
    int ret;
    char *pathOldRet = NULL;
    char *pathNewRet = NULL;

    if (oldpath != NULL) {
        ret = UserPathCopy(oldpath, &pathOldRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    if (newpath != NULL) {
        ret = UserPathCopy(newpath, &pathNewRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    if (oldfd != AT_FDCWD) {
        /* Process fd convert to system global fd */
        oldfd = GetAssociatedSystemFd(oldfd);
    }
    if (newdfd != AT_FDCWD) {
        /* Process fd convert to system global fd */
        newdfd = GetAssociatedSystemFd(newdfd);
    }

    ret = do_rename(oldfd, (oldpath ? pathOldRet : NULL), newdfd, (newpath ? pathNewRet : NULL));
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathOldRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathOldRet);
    }
    if (pathNewRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathNewRet);
    }
    return ret;
}

int SysFallocate(int fd, int mode, off_t offset, off_t len)
{
    int ret;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    ret = fallocate(fd, mode, offset, len);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysFallocate64(int fd, int mode, off64_t offset, off64_t len)
{
    int ret;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    ret = fallocate64(fd, mode, offset, len);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

ssize_t SysPreadv(int fd, const struct iovec *iov, int iovcnt, off_t offset)
{
    int ret;
    int valid_iovcnt = -1;
    struct iovec *iovRet = NULL;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);
    if ((iov == NULL) || (iovcnt <= 0) || (iovcnt > IOV_MAX)) {
        ret = preadv(fd, iov, iovcnt, offset);
        return -get_errno();
    }

    ret = UserIovCopy(&iovRet, iov, iovcnt, &valid_iovcnt);
    if (ret != 0) {
        return ret;
    }

    if (valid_iovcnt <= 0) {
        ret = -EFAULT;
        goto OUT_FREE;
    }

    ret = preadv(fd, iovRet, valid_iovcnt, offset);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT_FREE:
    (void)LOS_MemFree(OS_SYS_MEM_ADDR, iovRet);
    return ret;
}

ssize_t SysPwritev(int fd, const struct iovec *iov, int iovcnt, off_t offset)
{
    int ret;
    int valid_iovcnt = -1;
    struct iovec *iovRet = NULL;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);
    if ((iov == NULL) || (iovcnt <= 0) || (iovcnt > IOV_MAX)) {
        ret = pwritev(fd, iov, iovcnt, offset);
        return -get_errno();
    }

    ret = UserIovCopy(&iovRet, iov, iovcnt, &valid_iovcnt);
    if (ret != 0) {
        return ret;
    }

    if (valid_iovcnt != iovcnt) {
        ret = -EFAULT;
        goto OUT_FREE;
    }

    ret = pwritev(fd, iovRet, valid_iovcnt, offset);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT_FREE:
    (void)LOS_MemFree(OS_SYS_MEM_ADDR, iovRet);
    return ret;
}

#ifdef LOSCFG_FS_FAT
int SysFormat(const char *dev, int sectors, int option)
{
    int ret;
    char *devRet = NULL;

    if (!IsCapPermit(CAP_FS_FORMAT)) {
        return -EPERM;
    }

    if (dev != NULL) {
        ret = UserPathCopy(dev, &devRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = format((dev ? devRet : NULL), sectors, option);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (devRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, devRet);
    }
    return ret;
}
#endif

int SysFstat64(int fd, struct stat64 *buf)
{
    int ret;
    struct stat64 bufRet = {0};

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    ret = fstat64(fd, (buf ? (&bufRet) : NULL));
    if (ret < 0) {
        return -get_errno();
    }

    ret = LOS_ArchCopyToUser(buf, &bufRet, sizeof(struct stat64));
    if (ret != 0) {
        return -EFAULT;
    }

    return ret;
}

int SysFcntl64(int fd, int cmd, void *arg)
{
    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    if (cmd == F_DUPFD) {
        return FcntlDupFd(fd, arg, fcntl64);
    }
    int ret = fcntl64(fd, cmd, arg);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysGetdents64(int fd, struct dirent *de_user, unsigned int count)
{
    if (!LOS_IsUserAddressRange((VADDR_T)de_user, count)) {
        return -EFAULT;
    }

    struct dirent *de_knl = NULL;

    /* Process fd convert to system global fd */
    fd = GetAssociatedSystemFd(fd);

    int ret = do_readdir(fd, &de_knl, count);
    if (ret < 0) {
        return ret;
    }
    if (de_knl != NULL) {
        int cpy_ret = LOS_ArchCopyToUser(de_user, de_knl, sizeof(*de_knl));
        if (cpy_ret != 0)
        {
            return -EFAULT;
        }
    }
    return ret;
}

char *SysRealpath(const char *path, char *resolved_path)
{
    char *pathRet = NULL;
    char *resolved_pathRet = NULL;
    char *result = NULL;
    int ret;

    if (resolved_path == NULL) {
        return (char *)(intptr_t)-EINVAL;
    }

    if (path != NULL) {
        ret = UserPathCopy(path, &pathRet);
        if (ret != 0) {
            result = (char *)(intptr_t)ret;
            goto OUT;
        }
    }

    resolved_pathRet = realpath((path ? pathRet : NULL), NULL);
    if (resolved_pathRet == NULL) {
        result = (char *)(intptr_t)-get_errno();
        goto OUT;
    }

    ret = LOS_ArchCopyToUser(resolved_path, resolved_pathRet, strlen(resolved_pathRet) + 1);
    if (ret != 0) {
        result = (char *)(intptr_t)-EFAULT;
        goto OUT;
    }
    result = resolved_path;

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    if (resolved_pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, resolved_pathRet);
    }
    return result;
}

int SysChmod(const char *pathname, mode_t mode)
{
    struct IATTR attr;
    attr.attr_chg_mode = mode;
    attr.attr_chg_valid = CHG_MODE; /* change mode */
    int ret;
    char *pathRet = NULL;

    if (pathname != NULL) {
        ret = UserPathCopy(pathname, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    ret = chattr((pathname ? pathRet : NULL), &attr);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}

int SysChown(const char *pathname, uid_t owner, gid_t group)
{
    struct IATTR attr = {0};
    attr.attr_chg_valid = 0;
    int ret;
    char *pathRet = NULL;

    if (pathname != NULL) {
        ret = UserPathCopy(pathname, &pathRet);
        if (ret != 0) {
            goto OUT;
        }
    }

    if (owner != (uid_t)-1) {
        attr.attr_chg_uid = owner;
        attr.attr_chg_valid |= CHG_UID;
    }
    if (group != (gid_t)-1) {
        attr.attr_chg_gid = group;
        attr.attr_chg_valid |= CHG_GID;
    }
    ret = chattr((pathname ? pathRet : NULL), &attr);
    if (ret < 0) {
        ret = -get_errno();
    }

OUT:
    if (pathRet != NULL) {
        LOS_MemFree(OS_SYS_MEM_ADDR, pathRet);
    }
    return ret;
}
#endif
