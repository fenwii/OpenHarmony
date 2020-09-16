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

#include "mqueue.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "time_posix.h"
#include "user_copy.h"
#include "los_signal.h"
#include "los_strncpy_from_user.h"

mqd_t SysMqOpen(const char *mqName, int openFlag, mode_t mode, struct mq_attr *attr)
{
    mqd_t ret;
    int retValue;
    char kMqName[PATH_MAX + 1] = { 0 };

    retValue = LOS_StrncpyFromUser(kMqName, mqName, PATH_MAX);
    if (retValue < 0) {
        return retValue;
    }
    ret = mq_open(kMqName, openFlag, mode, attr);
    if (ret == -1) {
        return (mqd_t)-get_errno();
    }
    return ret;
}

int SysMqClose(mqd_t personal)
{
    int ret;

    ret = mq_close(personal);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysMqGetSetAttr(mqd_t mqd, const struct mq_attr *new, struct mq_attr *old)
{
    int ret;
    struct mq_attr knew, kold;

    if (new != NULL) {
        ret = LOS_ArchCopyFromUser(&knew, new, sizeof(struct mq_attr));
        if (ret != 0) {
            return -EFAULT;
        }
    }
    ret = mq_getsetattr(mqd, new ? &knew : NULL, old ? &kold : NULL);
    if (ret < 0) {
        return -get_errno();
    }
    if (old != NULL) {
        ret = LOS_ArchCopyToUser(old, &kold, sizeof(struct mq_attr));
        if (ret != 0) {
            return -EFAULT;
        }
    }
    return ret;
}

int SysMqUnlink(const char *mqName)
{
    int ret;
    int retValue;
    char kMqName[PATH_MAX + 1] = { 0 };

    retValue = LOS_StrncpyFromUser(kMqName, mqName, PATH_MAX);
    if (retValue < 0) {
        return retValue;
    }

    ret = mq_unlink(kMqName);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysMqTimedSend(mqd_t personal, const char *msg, size_t msgLen, unsigned int msgPrio,
                   const struct timespec *absTimeout)
{
    int ret;
    struct timespec timeout;
    char *msgIntr = NULL;

    if (absTimeout != NULL) {
        ret = LOS_ArchCopyFromUser(&timeout, absTimeout, sizeof(struct timespec));
        if (ret != 0) {
            return -EFAULT;
        }
    }
    if (msgLen == 0) {
        return -EINVAL;
    }
    msgIntr = (char *)malloc(msgLen);
    if (msgIntr == NULL) {
        return -ENOMEM;
    }
    ret = LOS_ArchCopyFromUser(msgIntr, msg, msgLen);
    if (ret != 0) {
        free(msgIntr);
        return -EFAULT;
    }
    ret = mq_timedsend(personal, msgIntr, msgLen, msgPrio, absTimeout ? &timeout : NULL);
    free(msgIntr);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

ssize_t SysMqTimedReceive(mqd_t personal, char *msg, size_t msgLen, unsigned int *msgPrio,
                          const struct timespec *absTimeout)
{
    int ret, receiveLen;
    struct timespec timeout;
    char *msgIntr = NULL;
    unsigned int kMsgPrio;

    if (absTimeout != NULL) {
        ret = LOS_ArchCopyFromUser(&timeout, absTimeout, sizeof(struct timespec));
        if (ret != 0) {
            return -EFAULT;
        }
    }
    if (msgLen == 0) {
        return -EINVAL;
    }
    msgIntr = (char *)malloc(msgLen);
    if (msgIntr == NULL) {
        return -ENOMEM;
    }
    receiveLen = mq_timedreceive(personal, msgIntr, msgLen, &kMsgPrio, absTimeout ? &timeout : NULL);
    if (receiveLen < 0) {
        free(msgIntr);
        return -get_errno();
    }

    if (msgPrio != NULL) {
        ret = LOS_ArchCopyToUser(msgPrio, &kMsgPrio, sizeof(unsigned int));
        if (ret != 0) {
            free(msgIntr);
            return -EFAULT;
        }
    }

    ret = LOS_ArchCopyToUser(msg, msgIntr, receiveLen);
    free(msgIntr);
    if (ret != 0) {
        return -EFAULT;
    }
    return receiveLen;
}

int SysSigAction(int sig, const sigaction_t *restrict sa, sigaction_t *restrict old, size_t sigsetsize)
{
    return OsSigAction(sig, sa, old);
}

int SysSigprocMask(int how, const sigset_t_l *restrict setl, sigset_t_l *restrict oldl, size_t sigsetsize)
{
    /* Let nxsig_procmask do all of the work */
    return OsSigprocMask(how, setl, oldl);
}

int SysKill(pid_t pid, int sig)
{
    return OsKillLock(pid, sig);
}

int SysPthreadKill(pid_t pid, int sig)
{
    return OsPthreadKill(pid, sig);
}

int SysSigTimedWait(const sigset_t_l *setl, siginfo_t *info, const struct timespec *timeout, size_t sigsetsize)
{
    sigset_t set;
    unsigned int tick;
    int retVal, ret;
    siginfo_t infoIntr;
    struct timespec timeoutIntr;

    retVal = LOS_ArchCopyFromUser(&set, &(setl->sig[0]), sizeof(sigset_t));
    if (retVal != 0) {
        return -EFAULT;
    }

    if (timeout == NULL) {
        tick = LOS_WAIT_FOREVER;
    } else {
        retVal = LOS_ArchCopyFromUser(&timeoutIntr, timeout, sizeof(struct timespec));
        if (retVal != 0) {
            return -EFAULT;
        }
        if (!ValidTimeSpec(&timeoutIntr)) {
            return -EINVAL;
        }
        tick = OsTimeSpec2Tick(&timeoutIntr);
    }
    ret = OsSigTimedWait(&set, &infoIntr, tick);
    if (ret < 0) {
        return ret;
    }
    if (info != NULL) {
        retVal = LOS_ArchCopyToUser(info, &infoIntr, sizeof(siginfo_t));
        if (retVal != 0) {
            return -EFAULT;
        }
    }
    return (ret == 0 ? infoIntr.si_signo : ret);
}

int SysPause(void)
{
    return OsPause();
}

int SysSigPending(sigset_t_l *setl)
{
    sigset_t set;
    int ret;

    ret = LOS_ArchCopyFromUser(&set, &(setl->sig[0]), sizeof(sigset_t));
    if (ret != 0) {
        return -EFAULT;
    }
    ret = OsSigPending(&set);
    if (ret != LOS_OK) {
        return ret;
    }
    ret = LOS_ArchCopyToUser(&(setl->sig[0]), &set, sizeof(sigset_t));
    if (ret != LOS_OK) {
        return -EFAULT;
    }
    return ret;
}

int SysSigSuspend(sigset_t_l *setl)
{
    sigset_t set;
    int retVal;

    retVal = LOS_ArchCopyFromUser(&set, &(setl->sig[0]), sizeof(sigset_t));
    if (retVal != 0) {
        return -EFAULT;
    }

    return OsSigSuspend(&set);
}

int SysMkFifo(const char *pathName, mode_t mode)
{
    int retValue;
    char kPathName[PATH_MAX + 1] = { 0 };

    retValue = LOS_StrncpyFromUser(kPathName, pathName, PATH_MAX);
    if (retValue < 0) {
        return retValue;
    }
    return mkfifo(kPathName, mode);
}

