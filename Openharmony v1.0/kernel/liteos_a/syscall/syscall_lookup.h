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

/* SYSCALL_HAND_DEF must be defined before including this file. */
/* SYSCALL_HAND_DEF(id, fun, rtype, narg); note if we have 64bit arg, narg should be ARG_NUM_7 */
#ifdef LOSCFG_FS_VFS
SYSCALL_HAND_DEF(__NR_read, SysRead, ssize_t, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_write, SysWrite, ssize_t, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_open, SysOpen, int, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_close, SysClose, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_creat, SysCreat, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_unlink, SysUnlink, int, ARG_NUM_1)

#ifdef LOSCFG_KERNEL_DYNLOAD
SYSCALL_HAND_DEF(__NR_execve, SysExecve, int, ARG_NUM_3)
#endif

SYSCALL_HAND_DEF(__NR_chdir, SysChdir, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_chmod, SysChmod, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_lseek, SysLseek, off_t, ARG_NUM_7) /* current only support 32bit max 4G file */
SYSCALL_HAND_DEF(__NR_mount, SysMount, int, ARG_NUM_5)
SYSCALL_HAND_DEF(__NR_umount, SysUmount, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_access, SysAccess, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_sync, SysSync, void, ARG_NUM_0)
SYSCALL_HAND_DEF(__NR_rename, SysRename, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_mkdir, SysMkdir, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_rmdir, SysRmdir, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_dup, SysDup, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_pipe, SysPipe, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_umount2, SysUmount2, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_ioctl, SysIoctl, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_fcntl, SysFcntl, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_dup2, SysDup2, int, ARG_NUM_2)
SYSCALL_HAND_DEF(82, SysSelect, int, ARG_NUM_5)
SYSCALL_HAND_DEF(__NR_truncate, SysTruncate, int, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_ftruncate, SysFtruncate, int, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_statfs, SysStatfs, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_stat, SysStat, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_lstat, SysLstat, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_fstat, SysFstat, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_fsync, SysFsync, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR__llseek, SysLseek64, off64_t, ARG_NUM_5) /* current only support 32bit max 4G file */
SYSCALL_HAND_DEF(__NR__newselect, SysSelect, int, ARG_NUM_5)
SYSCALL_HAND_DEF(__NR_readv, SysReadv, ssize_t, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_writev, SysWritev, ssize_t, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_poll, SysPoll, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_prctl, SysPrctl, int, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_pread64, SysPread64, ssize_t, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_pwrite64, SysPwrite64, ssize_t, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_getcwd, SysGetcwd, char *, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_sendfile, SysSendFile, ssize_t, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_truncate64, SysTruncate64, int, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_ftruncate64, SysFtruncate64, int, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_stat64, SysStat, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_lstat64, SysLstat, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_fstat64, SysFstat64, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_fcntl64, SysFcntl64, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_sendfile64, SysSendFile, ssize_t, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_preadv, SysPreadv, ssize_t, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_pwritev, SysPwritev, ssize_t, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_fallocate, SysFallocate64, int, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_getdents64, SysGetdents64, int, ARG_NUM_3)

#ifdef LOSCFG_FS_FAT
SYSCALL_HAND_DEF(__NR_format, SysFormat, int, ARG_NUM_3)
#endif

SYSCALL_HAND_DEF(__NR_unlinkat, SysUnlinkat, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_renameat, SysRenameat, int, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_openat, SysOpenat, int, ARG_NUM_7)
SYSCALL_HAND_DEF(__NR_mkdirat, SysMkdirat, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_statfs64, SysStatfs64, int, ARG_NUM_3)
#ifdef LOSCFG_DEBUG_VERSION
SYSCALL_HAND_DEF(__NR_dumpmemory, LOS_DumpMemRegion, void, ARG_NUM_1)
#endif
SYSCALL_HAND_DEF(__NR_mkfifo, SysMkFifo, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_mqclose, SysMqClose, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_realpath, SysRealpath, char *, ARG_NUM_2)

#ifdef LOSCFG_SHELL
SYSCALL_HAND_DEF(__NR_shellexec, SysShellExec, UINT32, ARG_NUM_2)
#endif

SYSCALL_HAND_DEF(30, SysUtime, int, ARG_NUM_2)
#endif

SYSCALL_HAND_DEF(__NR_exit, SysThreadExit, void, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_fork, SysFork, int, ARG_NUM_0)
SYSCALL_HAND_DEF(13, SysTime, time_t, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_getpid, SysGetPID, unsigned int, ARG_NUM_0)
SYSCALL_HAND_DEF(__NR_pause, SysPause, int, ARG_NUM_0)

SYSCALL_HAND_DEF(__NR_kill, SysKill, int, ARG_NUM_2)

SYSCALL_HAND_DEF(__NR_times, SysTimes, clock_t, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_brk, SysBrk, void *, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_setgid, SysSetGroupID, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_getgid, SysGetGroupID, int, ARG_NUM_0)
SYSCALL_HAND_DEF(__NR_setpgid, SysSetProcessGroupID, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_getppid, SysGetPPID, unsigned int, ARG_NUM_0)
SYSCALL_HAND_DEF(__NR_getpgrp, SysGetProcessGroupID, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_munmap, SysMunmap, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_getpriority, SysGetProcessPriority, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_setpriority, SysSetProcessPriority, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_setitimer, SysSetiTimer, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_getitimer, SysGetiTimer, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_wait4, SysWait, int, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_uname, SysUname, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_mprotect, SysMprotect, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_getpgid, SysGetProcessGroupID, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_sched_setparam, SysSchedSetParam, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_sched_getparam, SysSchedGetParam, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_sched_setscheduler, SysSchedSetScheduler, int, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_sched_getscheduler, SysSchedGetScheduler, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_sched_yield, SysSchedYield, void, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_sched_get_priority_max, SysSchedGetPriorityMax, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_sched_get_priority_min, SysSchedGetPriorityMin, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_sched_rr_get_interval, SysSchedRRGetInterval, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_nanosleep, SysNanoSleep, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_mremap, SysMremap, void *, ARG_NUM_5)
SYSCALL_HAND_DEF(__NR_umask, SysUmask, mode_t, ARG_NUM_1)

SYSCALL_HAND_DEF(__NR_rt_sigaction, SysSigAction, int, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_rt_sigprocmask, SysSigprocMask, int, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_rt_sigpending, SysSigPending, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_rt_sigtimedwait, SysSigTimedWait, int, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_rt_sigsuspend, SysSigSuspend, int, ARG_NUM_1)

SYSCALL_HAND_DEF(__NR_chown, SysChown, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_chown32, SysChown, int, ARG_NUM_3)
#ifdef LOSCFG_SECURITY_CAPABILITY
SYSCALL_HAND_DEF(__NR_ohoscapget, SysCapGet, UINT32, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_ohoscapset, SysCapSet, UINT32, ARG_NUM_1)
#endif

SYSCALL_HAND_DEF(__NR_mmap2, SysMmap, void*, ARG_NUM_6)
SYSCALL_HAND_DEF(__NR_getuid32, SysGetUserID, int, ARG_NUM_0)
SYSCALL_HAND_DEF(__NR_getgid32, SysGetGroupID, unsigned int, ARG_NUM_0)
SYSCALL_HAND_DEF(__NR_geteuid32, SysGetEffUserID, int, ARG_NUM_0)
SYSCALL_HAND_DEF(__NR_getegid32, SysGetEffGID, unsigned int, ARG_NUM_0)
SYSCALL_HAND_DEF(__NR_getresuid32, SysGetRealEffSaveUserID, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_getresgid32, SysGetRealEffSaveGroupID, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_setresuid32, SysSetRealEffSaveUserID, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_setresgid32, SysSetRealEffSaveGroupID, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_setreuid32, SysSetRealEffUserID, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_setregid32, SysSetRealEffGroupID, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_setgroups32, SysSetGroups, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_getgroups32, SysGetGroups, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_setuid32, SysSetUserID, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_setgid32, SysSetGroupID, int, ARG_NUM_1)

SYSCALL_HAND_DEF(__NR_gettid, SysGetTid, unsigned int, ARG_NUM_0)

SYSCALL_HAND_DEF(__NR_tkill, SysPthreadKill, int, ARG_NUM_2)

SYSCALL_HAND_DEF(__NR_futex, SysFutex, int, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_exit_group, SysUserExitGroup, void, ARG_NUM_1)
SYSCALL_HAND_DEF(254, SysSetThreadArea, int, ARG_NUM_1)
SYSCALL_HAND_DEF(255, SysGetThreadArea, char *, ARG_NUM_0)
SYSCALL_HAND_DEF(__NR_timer_create, SysTimerCreate, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_timer_settime32, SysTimerSettime, int, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_timer_gettime32, SysTimerGettime, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_timer_getoverrun, SysTimerGetoverrun, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_timer_delete, SysTimerDelete, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_clock_settime32, SysClockSettime, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_clock_gettime32, SysClockGettime, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_clock_getres_time32, SysClockGetres, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_clock_nanosleep_time32, SysClockNanoSleep, int, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_mq_open, SysMqOpen, mqd_t, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_mq_unlink, SysMqUnlink, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_mq_timedsend, SysMqTimedSend, int, ARG_NUM_5)
SYSCALL_HAND_DEF(__NR_mq_timedreceive, SysMqTimedReceive, ssize_t, ARG_NUM_5)
SYSCALL_HAND_DEF(__NR_mq_getsetattr, SysMqGetSetAttr, int, ARG_NUM_3)

#ifdef LOSCFG_NET_LWIP_SACK
SYSCALL_HAND_DEF(__NR_socket, SysSocket, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_bind, SysBind, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_connect, SysConnect, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_listen, SysListen, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_accept, SysAccept, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_getsockname, SysGetSockName, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_getpeername, SysGetPeerName, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_send, SysSend, ssize_t, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_sendto, SysSendTo, ssize_t, ARG_NUM_6)
SYSCALL_HAND_DEF(__NR_recv, SysRecv, ssize_t, ARG_NUM_4)
SYSCALL_HAND_DEF(__NR_recvfrom, SysRecvFrom, ssize_t, ARG_NUM_6)
SYSCALL_HAND_DEF(__NR_shutdown, SysShutdown, int, ARG_NUM_2)
SYSCALL_HAND_DEF(__NR_setsockopt, SysSetSockOpt, int, ARG_NUM_5)
SYSCALL_HAND_DEF(__NR_getsockopt, SysGetSockOpt, int, ARG_NUM_5)
SYSCALL_HAND_DEF(__NR_sendmsg, SysSendMsg, ssize_t, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_recvmsg, SysRecvMsg, ssize_t, ARG_NUM_3)
#endif

SYSCALL_HAND_DEF(__NR_shmat, SysShmAt, void *, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_shmdt, SysShmDt, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_shmget, SysShmGet, int, ARG_NUM_3)
SYSCALL_HAND_DEF(__NR_shmctl, SysShmCtl, int, ARG_NUM_3)

SYSCALL_HAND_DEF(__NR_statx, SysStatx, int, ARG_NUM_5)
SYSCALL_HAND_DEF(403, SysClockGettime64, int, ARG_NUM_2)
SYSCALL_HAND_DEF(404, SysClockSettime64, int, ARG_NUM_2)
SYSCALL_HAND_DEF(406, SysClockGetres64, int, ARG_NUM_2)
SYSCALL_HAND_DEF(407, SysClockNanoSleep64, int, ARG_NUM_4)
SYSCALL_HAND_DEF(408, SysTimerGettime64, int, ARG_NUM_2)
SYSCALL_HAND_DEF(409, SysTimerSettime64, int, ARG_NUM_4)

/* LiteOS customized syscalls, not compatible with ARM EABI */
SYSCALL_HAND_DEF(__NR_pthread_set_detach, SysUserThreadSetDeatch, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_pthread_join, SysThreadJoin, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_pthread_deatch, SysUserThreadDetach, int, ARG_NUM_1)
SYSCALL_HAND_DEF(__NR_creat_user_thread, SysCreateUserThread, unsigned int, ARG_NUM_3)
