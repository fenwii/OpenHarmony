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

#include "pthread.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

int pthread_mutexattr_init(pthread_mutexattr_t *attr)
{
    unsigned int ret = LOS_MuxAttrInit(attr);
    if (ret != LOS_OK) {
        return (int)ret;
    }

#if defined POSIX_MUTEX_DEFAULT_INHERIT
    attr->protocol    = PTHREAD_PRIO_INHERIT;
#elif defined POSIX_MUTEX_DEFAULT_PROTECT
    attr->protocol    = PTHREAD_PRIO_PROTECT;
#else
    attr->protocol    = PTHREAD_PRIO_NONE;
#endif
    attr->type = PTHREAD_MUTEX_NORMAL;
    return LOS_OK;
}

int pthread_mutexattr_destroy(pthread_mutexattr_t *attr)
{
    return LOS_MuxAttrDestroy(attr);
}

int pthread_mutexattr_setprotocol(pthread_mutexattr_t *attr, int protocol)
{
    return LOS_MuxAttrSetProtocol(attr, protocol);
}

int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *attr, int *protocol)
{
    return LOS_MuxAttrGetProtocol(attr, protocol);
}

int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *attr, int prioceiling)
{
    return LOS_MuxAttrSetPrioceiling(attr, prioceiling);
}

int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *attr, int *prioceiling)
{
    return LOS_MuxAttrGetPrioceiling(attr, prioceiling);
}

int pthread_mutex_setprioceiling(pthread_mutex_t *mutex, int prioceiling, int *oldPrioceiling)
{
    return LOS_MuxSetPrioceiling(mutex, prioceiling, oldPrioceiling);
}

int pthread_mutex_getprioceiling(const pthread_mutex_t *mutex, int *prioceiling)
{
    return LOS_MuxGetPrioceiling(mutex, prioceiling);
}

int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *outType)
{
    return LOS_MuxAttrGetType(attr, outType);
}

int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type)
{
    return LOS_MuxAttrSetType(attr, type);
}

/* Initialize mutex. If mutexAttr is NULL, use default attributes. */
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexAttr)
{
    unsigned int ret = LOS_MuxInit(mutex, mutexAttr);
    if ((ret == LOS_OK) && (mutexAttr == NULL)) {
#if defined POSIX_MUTEX_DEFAULT_INHERIT
        mutex->attr.protocol    = PTHREAD_PRIO_INHERIT;
#elif defined POSIX_MUTEX_DEFAULT_PROTECT
        mutex->attr.protocol    = PTHREAD_PRIO_PROTECT;
#else
        mutex->attr.protocol    = PTHREAD_PRIO_NONE;
#endif
        mutex->attr.type = PTHREAD_MUTEX_NORMAL;
    }

    return (int)ret;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    return LOS_MuxDestroy(mutex);
}

/* Lock mutex, waiting for it if necessary. */
int pthread_mutex_lock(pthread_mutex_t *mutex)
{
    return LOS_MuxLock(mutex, LOS_WAIT_FOREVER);
}

int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
    return LOS_MuxTrylock(mutex);
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    return LOS_MuxUnlock(mutex);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
