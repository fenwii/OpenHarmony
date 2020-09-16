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

#ifndef _LOS_SYSCALL_H
#define _LOS_SYSCALL_H

#include "los_typedef.h"
#include "los_task.h"
#include "los_mux.h"
#include "syscall.h"
#ifdef LOSCFG_KERNEL_DYNLOAD
#include "los_exec_elf.h"
#endif
#include "sys/times.h"
#include "sys/utsname.h"
#include "sys/shm.h"
#include "poll.h"
#include "utime.h"
#include "mqueue.h"
#include "time.h"
#include "sys/time.h"
#include "sys/stat.h"
#ifdef LOSCFG_FS_VFS
#include "sys/socket.h"
#include "dirent.h"
#endif

/* process */
extern unsigned int SysGetGroupId(void);
extern unsigned int SysGetTid(void);
extern void SysSchedYield(int type);
extern int SysSchedGetScheduler(int id, int flag);
extern int SysSchedSetScheduler(int id, int policy, int prio, int flag);
extern int SysSchedGetParam(int id, int flag);
extern int SysSchedSetParam(int id, unsigned int prio, int flag);
extern int SysSetProcessPriority(int which, int who, unsigned int prio);
extern int SysGetProcessPriority(int which, int who);
extern int SysSchedGetPriorityMin(int policy);
extern int SysSchedGetPriorityMax(int policy);
extern int SysSchedRRGetInterval(int pid, struct timespec *tp);
extern int SysWait(int pid, USER int *status, int options, void *rusage);
extern int SysFork(void);
extern unsigned int SysGetPID(void);
extern unsigned int SysGetPPID(void);
extern int SysSetGroupID(unsigned int gid);
extern int SysGetGroupID(void);
extern int SysGetUserID(void);
extern int SysGetEffUserID(void);
extern int SysGetEffGID(void);
extern int SysSetUserID(int uid);
extern int SysGetRealEffSaveUserID(int *ruid, int *euid, int *suid);
extern int SysGetRealEffSaveGroupID(int *rgid, int *egid, int *sgid);
extern int SysSetRealEffUserID(int ruid, int euid);
extern int SysSetRealEffGroupID(int rgid, int egid);
extern int SysSetRealEffSaveGroupID(int rgid, int egid, int sgid);
extern int SysSetRealEffSaveUserID(int ruid, int euid, int suid);
extern int SysGetGroups(int size, int list[]);
extern int SysSetGroups(int size, int list[]);
extern int SysGetCurrProcessGroupID(void);
extern int SysGetProcessGroupID(unsigned int pid);
extern int SysSetProcessGroupID(unsigned int pid, unsigned int gid);
extern unsigned int SysCreateUserThread(const TSK_ENTRY_FUNC func, const UserTaskParam *userParam, bool joinable);
extern int SysSetThreadArea(const char *area);
extern char *SysGetThreadArea(void);
extern int SysUserThreadSetDeatch(unsigned int taskID);
extern int SysUserThreadDetach(unsigned int taskID);
extern int SysThreadJoin(unsigned int taskID);
extern void SysUserExitGroup(int status);
extern void SysThreadExit(int status);
extern int SysFutex(const unsigned int *uAddr, unsigned int flags, int val,
                    unsigned int absTime, const unsigned int *newUserAddr);
extern mqd_t SysMqOpen(const char *mqName, int openFlag, mode_t mode, struct mq_attr *attr);
extern int SysMqClose(mqd_t personal);
extern int SysMqGetSetAttr(mqd_t mqd, const struct mq_attr *new, struct mq_attr *old);
extern int SysMqUnlink(const char *mqName);
extern int SysMqSend(mqd_t personal, const char *msgPtr, size_t msgLen, unsigned int msgPrio);
extern int SysMqTimedSend(mqd_t personal, const char *msg, size_t msgLen, unsigned int msgPrio,
                          const struct timespec *absTimeout);
extern ssize_t SysMqTimedReceive(mqd_t personal, char *msg, size_t msgLen, unsigned int *msgPrio,
                                 const struct timespec *absTimeout);
extern int SysSigAction(int sig, const sigaction_t *restrict sa, sigaction_t *restrict old, size_t sigsetsize);
extern int SysSigprocMask(int how, const sigset_t_l *restrict set, sigset_t *restrict old, size_t sigsetsize);
extern int SysKill(pid_t pid, int sig);
extern int SysPthreadKill(pid_t pid, int sig);
extern int SysSigTimedWait(const sigset_t *set, siginfo_t *info,
                           const struct timespec *timeoutsize_t, size_t sigsetsize);
extern int SysPause(void);
extern int SysSigPending(sigset_t_l *setl);
extern int SysSigSuspend(sigset_t_l *setl);
extern int SysMkFifo(const char *pathName, mode_t mode);

/* net */
#ifdef LOSCFG_NET_LWIP_SACK
extern int SysSocket(int domain, int type, int protocol);
extern int SysBind(int s, const struct sockaddr *name, socklen_t namelen);
extern int SysConnect(int s, const struct sockaddr *name, socklen_t namelen);
extern int SysListen(int sockfd, int backlog);
extern int SysAccept(int socket, struct sockaddr *address, socklen_t *addressLen);
extern int SysGetSockName (int s, struct sockaddr *name, socklen_t *namelen);
extern int SysGetPeerName (int s, struct sockaddr *name, socklen_t *namelen);
extern ssize_t SysSend(int s, const void *dataptr, size_t size, int flags);
extern ssize_t SysSendTo(int s, const void *dataptr, size_t size, int flags,
                         const struct sockaddr *to, socklen_t tolen);
extern ssize_t SysRecv(int socket, void *buffer, size_t length, int flags);
extern ssize_t SysRecvFrom(int socket, void *buffer, size_t length, int flags,
                           struct sockaddr *address, socklen_t *addressLen);
extern int SysShutdown(int socket, int how);
extern int SysSetSockOpt(int socket, int level, int optName,
                         const void *optValue, socklen_t optLen);
extern int SysGetSockOpt(int sockfd, int level, int optName,
                         void *optValue, socklen_t *optLen);
extern ssize_t SysSendMsg(int s, const struct msghdr *message, int flags);
extern ssize_t SysRecvMsg(int s, struct msghdr *message, int flags);
#endif

/* vmm */
extern void *SysMmap(void *addr, size_t size, int prot, int flags, int fd, size_t offset);
extern int SysMunmap(void *addr, size_t size);
extern int SysMprotect(vaddr_t vaddr, size_t len, int prot);
extern vaddr_t SysMremap(vaddr_t old_address, size_t old_size, size_t new_size, int flags, vaddr_t new_addr);
extern void *SysBrk(void *addr);
extern int SysShmGet(key_t key, size_t size, int shmflg);
extern void *SysShmAt(int shmid, const void *shmaddr, int shmflg);
extern int SysShmCtl(int shmid, int cmd, struct shmid_ds *buf);
extern int SysShmDt(const void *shmaddr);

/* misc */
extern int SysUname(struct utsname *name);

/* time */
extern int SysNanoSleep(const struct timespec *rqtp, struct timespec *rmtp);
extern clock_t SysTimes(struct tms *buf);
extern time_t SysTime(time_t *tloc);
extern int SysSetiTimer(int which, const struct itimerval *value, struct itimerval *ovalue);
extern int SysGetiTimer(int which, struct itimerval *value);
extern int SysTimerCreate(clockid_t clockID, struct sigevent *evp, timer_t *timerID);
extern int SysTimerGettime(timer_t timerID, struct itimerspec *value);
extern int SysTimerGetoverrun(timer_t timerID);
extern int SysTimerDelete(timer_t timerID);
extern int SysClockSettime(clockid_t clockID, const struct timespec *tp);
extern int SysClockGettime(clockid_t clockID, struct timespec *tp);
extern int SysClockGetres(clockid_t clockID, struct timespec *tp);
extern int SysClockNanoSleep(clockid_t clk, int flags, const struct timespec *req, struct timespec *rem);
extern int SysUtime(const char *path, const struct utimbuf *ptimes);
extern int SysTimerSettime(timer_t timerID, int flags, const struct itimerspec *value, struct itimerspec *oldValue);

extern int SysClockSettime64(clockid_t clockID, const struct timespec64 *tp);
extern int SysClockGettime64(clockid_t clockID, struct timespec64 *tp);
extern int SysClockGetres64(clockid_t clockID, struct timespec64 *tp);
extern int SysClockNanoSleep64(clockid_t clk, int flags, const struct timespec64 *req, struct timespec64 *rem);
extern int SysTimerGettime64(timer_t timerID, struct itimerspec64 *value);
extern int SysTimerSettime64(timer_t timerID, int flags, const struct itimerspec64 *value, struct itimerspec64 *oldValue);

/* filesystem */
#ifdef LOSCFG_FS_VFS
typedef int (*PollFun)(struct pollfd *fds, nfds_t nfds, int timeout);
extern int do_open(int dirfd, const char *path, int oflags, ...);
extern int do_unlink(int dirfd, const char *pathname);
extern int do_mkdir(int dirfd, const char *pathname, mode_t mode);
extern int do_rmdir(int dirfd, const char *pathname);
extern int do_rename(int oldfd, const char *oldpath, int newfd, const char *newpath);
extern int do_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
    struct timeval *timeout, PollFun poll);
extern int do_readdir(int fd, struct dirent **de, unsigned int count);
extern ssize_t preadv(int __fd, const struct iovec *__iov, int __count, off_t __offset);
extern ssize_t pwritev(int __fd, const struct iovec *__iov, int __count, off_t __offset);
extern int chattr(const char *pathname, struct IATTR *attr);

extern int SysClose(int fd);
extern ssize_t SysRead(int fd, void *buf, size_t nbytes);
extern ssize_t SysWrite(int fd, const void *buf, size_t nbytes);
extern int SysOpen(const char *path, int oflags, ...);
extern int SysCreat(const char *pathname, mode_t mode);
extern int SysUnlink( const char *pathname);
extern int SysExecve(const char *fileName, char *const *argv, char *const *envp);
extern int SysChdir(const char *path);
extern int SysChmod(const char *path, mode_t mode);
extern int SysChown(const char *pathname, uid_t owner, gid_t group);
extern off_t SysLseek(int fd, off_t offset, int whence);
extern off64_t SysLseek64(int fd, int offsetHigh, int offsetLow, off64_t *result, int whence);
extern int SysMount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags,
                    const void *data);
extern int SysUmount(const char *target);
extern int SysAccess(const char *path, int amode);
extern int SysRename(const char *oldpath, const char *newpath);
extern int SysMkdir(const char *pathname, mode_t mode);
extern int SysRmdir(const char *pathname);
extern int SysDup(int fd);
extern int SysUmount2(const char *target, int flags);
extern int SysIoctl(int fd, int req, void *arg);
extern int SysFcntl(int fd, int cmd, void *arg);
extern int SysDup2(int fd1, int fd2);
extern int SysSelect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
extern int SysTruncate(const char *path, off_t length);
extern int SysFtruncate(int fd, off_t length);
extern int SysStatfs(const char *path, struct statfs *buf);
extern int SysStatfs64(const char *path, size_t sz, struct statfs *buf);

extern int SysStat(const char *path, struct stat *buf);
extern int SysLstat(const char *path, struct stat *buffer);
extern int SysFstat(int fildes, struct stat *buf);
extern int SysStatx(int fd, const char *restrict path, int flag, unsigned mask, struct statx *restrict stx);
extern int SysFsync(int fd);
extern ssize_t SysReadv(int fd, const struct iovec *iov, int iovcnt);
extern ssize_t SysWritev(int fd, const struct iovec *iov, int iovcnt);
extern int SysPipe(int pipefd[2]); /* 2 : pipe fds for read and write */
extern int SysFormat(const char *dev, int sectors, int option);
extern int SysFstat64(int fd, struct stat64 *buf);
extern int SysFcntl64(int fd, int cmd, void *arg);
extern int SysPoll(struct pollfd *fds, nfds_t nfds, int timeout);
extern int SysPrctl(int option, ...);
extern ssize_t SysPread64(int fd, void *buf, size_t nbytes, off64_t offset);
extern ssize_t SysPwrite64(int fd, const void *buf, size_t nbytes, off64_t offset);
extern char *SysGetcwd(char *buf, size_t n);
extern ssize_t SysSendFile(int outfd, int infd, off_t *offset, size_t count);
extern int SysTruncate(const char *path, off_t length);
extern int SysTruncate64(const char *path, off64_t length);
extern int SysFtruncate64(int fd, off64_t length);
extern int SysOpenat(int dirfd, const char *path, int oflags, ...);
extern int SysMkdirat(int dirfd, const char *pathname, mode_t mode);
extern int SysUnlinkat(int dirfd, const char *pathname, int flag);
extern int SysRenameat(int oldfd, const char *oldpath, int newdfd, const char *newpath);
extern int SysFallocate(int fd, int mode, off_t offset, off_t len);
extern int SysFallocate64(int fd, int mode, off64_t offset, off64_t len);
extern ssize_t SysPreadv(int fd, const struct iovec *iov, int iovcnt, off_t offset);
extern ssize_t SysPwritev(int fd, const struct iovec *iov, int iovcnt, off_t offset);
extern void SysSync(void);
extern int SysGetdents64(int fd, struct dirent *de_user, unsigned int count);
extern int do_opendir(const char *path, int oflags);
extern char *SysRealpath(const char *path, char *resolvedPath);
extern int SysUmask(int mask);
extern int SysShellExec(const char *msgName, const char *cmdString);
#endif
#endif /* _LOS_SYSCALL_H */
