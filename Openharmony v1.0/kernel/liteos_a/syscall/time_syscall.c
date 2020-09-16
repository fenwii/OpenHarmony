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

#include "errno.h"
#include "unistd.h"
#include "limits.h"
#include "utime.h"
#include "time.h"
#include "user_copy.h"
#include "sys/times.h"
#include "los_memory.h"
#include "los_strncpy_from_user.h"

#ifdef LOSCFG_FS_VFS
int SysUtime(const char *path, const struct utimbuf *ptimes)
{
    int ret;
    char *spath = NULL;
    struct utimbuf sptimes;

    if (path == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    spath = LOS_MemAlloc(m_aucSysMem0, PATH_MAX + 1);
    if (spath == NULL) {
        errno = ENOMEM;
        return -ENOMEM;
    }

    ret = LOS_StrncpyFromUser(spath, path, PATH_MAX + 1);
    if (ret == -EFAULT) {
        LOS_MemFree(m_aucSysMem0, spath);
        return ret;
    } else if (ret > PATH_MAX) {
        LOS_MemFree(m_aucSysMem0, spath);
        PRINT_ERR("%s[%d], path exceeds maxlen: %d\n", __FUNCTION__, __LINE__, PATH_MAX);
        return -ENAMETOOLONG;
    }
    spath[ret] = '\0';

    if (ptimes && LOS_ArchCopyFromUser(&sptimes, ptimes, sizeof(struct utimbuf))) {
        LOS_MemFree(m_aucSysMem0, spath);
        errno = EFAULT;
        return -EFAULT;
    }

    ret = utime(spath, ptimes ? &sptimes : NULL);
    if (ret < 0) {
        ret = -get_errno();
    }

    LOS_MemFree(m_aucSysMem0, spath);

    return ret;
}
#endif

time_t SysTime(time_t *tloc)
{
    int ret;
    time_t stloc;

    ret = time(tloc ? &stloc : NULL);
    if (ret < 0) {
        return -get_errno();
    }

    if (tloc && LOS_ArchCopyToUser(tloc, &stloc, sizeof(time_t))) {
        errno = EFAULT;
        ret = -EFAULT;
    }

    return ret;
}

int SysSetiTimer(int which, const struct itimerval *value, struct itimerval *ovalue)
{
    int ret;
    struct itimerval svalue;
    struct itimerval sovalue;

    if (value == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    if (LOS_ArchCopyFromUser(&svalue, value, sizeof(struct itimerval))) {
        errno = EFAULT;
        return -EFAULT;
    }

    ret = setitimer(which, &svalue, &sovalue);
    if (ret < 0) {
        return -get_errno();
    }

    if (ovalue && LOS_ArchCopyToUser(ovalue, &sovalue, sizeof(struct itimerval))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysGetiTimer(int which, struct itimerval *value)
{
    int ret;
    struct itimerval svalue;

    if (value == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    ret = getitimer(which, &svalue);
    if (ret < 0) {
        return -get_errno();
    }

    if (LOS_ArchCopyToUser(value, &svalue, sizeof(struct itimerval))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysTimerCreate(clockid_t clockID, struct sigevent *evp, timer_t *timerID)
{
    int ret;
    timer_t stimerID;
    struct sigevent sevp;

    if (timerID == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    if (evp && LOS_ArchCopyFromUser(&sevp, evp, sizeof(struct sigevent))) {
        errno = EFAULT;
        return -EFAULT;
    }

    ret = timer_create(clockID, evp ? &sevp : NULL, &stimerID);
    if (ret < 0) {
        return -get_errno();
    }

    if (LOS_ArchCopyToUser(timerID, &stimerID, sizeof(timer_t))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysTimerGettime(timer_t timerID, struct itimerspec *value)
{
    int ret;
    struct itimerspec svalue;

    if (value == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    ret = timer_gettime(timerID, &svalue);
    if (ret < 0) {
        return -get_errno();
    }

    if (LOS_ArchCopyToUser(value, &svalue, sizeof(struct itimerspec))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysTimerSettime(timer_t timerID, int flags, const struct itimerspec *value, struct itimerspec *oldValue)
{
    int ret;
    struct itimerspec svalue;
    struct itimerspec soldValue;

    if (value == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    if (LOS_ArchCopyFromUser(&svalue, value, sizeof(struct itimerspec))) {
        errno = EFAULT;
        return -EFAULT;
    }

    ret = timer_settime(timerID, flags, &svalue, &soldValue);
    if (ret < 0) {
        return -get_errno();
    }

    if (oldValue && LOS_ArchCopyToUser(oldValue, &soldValue, sizeof(struct itimerspec))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysTimerGetoverrun(timer_t timerID)
{
    int ret;

    ret = timer_getoverrun(timerID);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysTimerDelete(timer_t timerID)
{
    int ret;

    ret = timer_delete(timerID);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysClockSettime(clockid_t clockID, const struct timespec *tp)
{
    int ret;
    struct timespec stp;

    if (tp == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    if (LOS_ArchCopyFromUser(&stp, tp, sizeof(struct timespec))) {
        errno = EFAULT;
        return -EFAULT;
    }

    ret = clock_settime(clockID, &stp);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysClockGettime(clockid_t clockID, struct timespec *tp)
{
    int ret;
    struct timespec stp;

    if (tp == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    ret = clock_gettime(clockID, &stp);
    if (ret < 0) {
        return -get_errno();
    }

    if (LOS_ArchCopyToUser(tp, &stp, sizeof(struct timespec))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysClockGetres(clockid_t clockID, struct timespec *tp)
{
    int ret;
    struct timespec stp;

    if (tp == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    ret = clock_getres(clockID, &stp);
    if (ret < 0) {
        return -get_errno();
    }

    if (LOS_ArchCopyToUser(tp, &stp, sizeof(struct timespec))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysClockNanoSleep(clockid_t clk, int flags, const struct timespec *req, struct timespec *rem)
{
    int ret;
    struct timespec sreq;
    struct timespec srem;

    if (!req || LOS_ArchCopyFromUser(&sreq, req, sizeof(struct timespec))) {
        errno = EFAULT;
        return -EFAULT;
    }

    ret = clock_nanosleep(clk, flags, &sreq, rem ? &srem : NULL);
    if (ret < 0) {
        return -get_errno();
    }

    if (rem && LOS_ArchCopyToUser(rem, &srem, sizeof(struct timespec))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysNanoSleep(const struct timespec *rqtp, struct timespec *rmtp)
{
    int ret;
    struct timespec srqtp;
    struct timespec srmtp;

    if (!rqtp || LOS_ArchCopyFromUser(&srqtp, rqtp, sizeof(struct timespec))) {
        errno = EFAULT;
        return -EFAULT;
    }

    ret = nanosleep(&srqtp, rmtp ? &srmtp : NULL);
    if (ret < 0) {
        return -get_errno();
    }

    if (rmtp && LOS_ArchCopyToUser(rmtp, &srmtp, sizeof(struct timespec))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

clock_t SysTimes(struct tms *buf)
{
    clock_t ret;
    struct tms sbuf;

    ret = times(buf ? &sbuf : NULL);

    if (buf && LOS_ArchCopyToUser(buf, &sbuf, sizeof(struct tms))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysClockSettime64(clockid_t clockID, const struct timespec64 *tp)
{
    int ret;
    struct timespec t;
    struct timespec64 stp;

    if (tp == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    if (LOS_ArchCopyFromUser(&stp, tp, sizeof(struct timespec64))) {
        errno = EFAULT;
        return -EFAULT;
    }

    if (stp.tv_sec > UINT32_MAX) {
        errno = ENOSYS;
        return -ENOSYS;
    }
    t.tv_sec = stp.tv_sec;
    t.tv_nsec = stp.tv_nsec;

    ret = clock_settime(clockID, &t);
    if (ret < 0) {
        return -get_errno();
    }
    return ret;
}

int SysClockGettime64(clockid_t clockID, struct timespec64 *tp)
{
    int ret;
    struct timespec t;
    struct timespec64 stp;

    if (tp == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    ret = clock_gettime(clockID, &t);
    if (ret < 0) {
        return -get_errno();
    }

    stp.tv_sec = t.tv_sec;
    stp.tv_nsec = t.tv_nsec;

    if (LOS_ArchCopyToUser(tp, &stp, sizeof(struct timespec64))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysClockGetres64(clockid_t clockID, struct timespec64 *tp)
{
    int ret;
    struct timespec t;
    struct timespec64 stp;

    if (tp == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    ret = clock_getres(clockID, &t);
    if (ret < 0) {
        return -get_errno();
    }

    stp.tv_sec = t.tv_sec;
    stp.tv_nsec = t.tv_nsec;

    if (LOS_ArchCopyToUser(tp, &stp, sizeof(struct timespec64))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysClockNanoSleep64(clockid_t clk, int flags, const struct timespec64 *req, struct timespec64 *rem)
{
    int ret;
    struct timespec rq;
    struct timespec rm;
    struct timespec64 sreq;
    struct timespec64 srem;

    if (!req || LOS_ArchCopyFromUser(&sreq, req, sizeof(struct timespec64))) {
        errno = EFAULT;
        return -EFAULT;
    }

    if (req != NULL) {
        rq.tv_sec = (sreq.tv_sec > UINT32_MAX) ? UINT32_MAX : sreq.tv_sec;
        rq.tv_nsec = sreq.tv_nsec;
    }

    ret = clock_nanosleep(clk, flags, &rq, rem ? &rm : NULL);
    if (ret < 0) {
        return -get_errno();
    }

    if (rem != NULL) {
        srem.tv_sec = rm.tv_sec;
        srem.tv_nsec = rm.tv_nsec;
        if (LOS_ArchCopyToUser(rem, &srem, sizeof(struct timespec64))) {
            errno = EFAULT;
            return -EFAULT;
        }
    }

    return ret;
}

int SysTimerGettime64(timer_t timerID, struct itimerspec64 *value)
{
    int ret;
    struct itimerspec val;
    struct itimerspec64 svalue;

    if (value == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    ret = timer_gettime(timerID, &val);
    if (ret < 0) {
        return -get_errno();
    }

    svalue.it_interval.tv_sec = val.it_interval.tv_sec;
    svalue.it_interval.tv_nsec = val.it_interval.tv_nsec;
    svalue.it_value.tv_sec = val.it_value.tv_sec;
    svalue.it_value.tv_nsec = val.it_value.tv_nsec;

    if (LOS_ArchCopyToUser(value, &svalue, sizeof(struct itimerspec64))) {
        errno = EFAULT;
        return -EFAULT;
    }

    return ret;
}

int SysTimerSettime64(timer_t timerID, int flags, const struct itimerspec64 *value, struct itimerspec64 *oldValue)
{
    int ret;
    struct itimerspec val;
    struct itimerspec oldVal;
    struct itimerspec64 svalue;
    struct itimerspec64 soldValue;

    if (value == NULL) {
        errno = EINVAL;
        return -EINVAL;
    }

    if (LOS_ArchCopyFromUser(&svalue, value, sizeof(struct itimerspec64))) {
        errno = EFAULT;
        return -EFAULT;
    }

    if (svalue.it_interval.tv_sec > UINT32_MAX || svalue.it_value.tv_sec > UINT32_MAX) {
        errno = ENOSYS;
        return -ENOSYS;
    }

    val.it_interval.tv_sec = svalue.it_interval.tv_sec;
    val.it_interval.tv_nsec = svalue.it_interval.tv_nsec;
    val.it_value.tv_sec = svalue.it_value.tv_sec;
    val.it_value.tv_nsec = svalue.it_value.tv_nsec;

    ret = timer_settime(timerID, flags, &val, oldValue ? &oldVal : NULL);
    if (ret < 0) {
        return -get_errno();
    }

    if (oldValue != NULL) {
        soldValue.it_interval.tv_sec = oldVal.it_interval.tv_sec;
        soldValue.it_interval.tv_nsec = oldVal.it_interval.tv_nsec;
        soldValue.it_value.tv_sec = oldVal.it_value.tv_sec;
        soldValue.it_value.tv_nsec = oldVal.it_value.tv_nsec;

        if (LOS_ArchCopyToUser(oldValue, &soldValue, sizeof(struct itimerspec64))) {
            errno = EFAULT;
            return -EFAULT;
        }
    }

    return ret;
}
