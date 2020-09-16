/*-
 * Copyright (c) 2000 Jake Burkholder <jake@freebsd.org>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/11.4/sys/kern/kern_condvar.c 315386 2017-03-16 07:10:08Z mjg $");

#include <sys/condvar.h>
#include <sys/callout.h>
#include <time.h>
#include <los_event.h>

extern UINT32 OsEventWriteOnce(EVENT_CB_S *eventCb, UINT32 events);

int
cv_timedwait(struct cv *cv, struct mtx *mtx, int tw_ms)
{
	struct timespec abstime;

	abstime.tv_sec = tw_ms / MSEC_PER_SEC;
	abstime.tv_nsec = (tw_ms%MSEC_PER_SEC) * NSEC_PER_MSEC;
	return (pthread_cond_timedwait(cv, mtx, &abstime));
}

int
cv_signal(pthread_cond_t *cond)
{
	int ret;

	if (cond == NULL) {
		return (EINVAL);
	}
	ret = OsEventWriteOnce(&(cond->event), 0x01);

	if (ret != 0) {
		return (EINVAL);
	}

	return (ret);
}

int
cv_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
	int ret;

	if ((cond == NULL) || (mutex == NULL)) {
		return (EINVAL);
	}

	(void)pthread_mutex_lock(cond->mutex);
	if (cond->value == -1) {
		cond->value = 0;
		ret = LOS_EventInit(&(cond->event));
		if (ret != LOS_OK) {
			(void)pthread_mutex_unlock(cond->mutex);
			return (EINVAL);
		}
	}
	(void)pthread_mutex_unlock(cond->mutex);

	if (pthread_mutex_unlock(mutex) != ENOERR) {
		PRINTK("%s %d\n",__FUNCTION__,__LINE__);
	}

	ret = LOS_EventRead(&(cond->event), 0x0f, LOS_WAITMODE_OR | LOS_WAITMODE_CLR, LOS_WAIT_FOREVER);

	if (pthread_mutex_lock(mutex) != ENOERR) {
		PRINTK("%s %d\n",__FUNCTION__,__LINE__);
	}

	return (ret);
}

int
cv_broadcast(pthread_cond_t *cond)
{
	int ret;

	if (cond == NULL) {
		return (EINVAL);
	}

	ret = LOS_EventWrite(&(cond->event), 0x01);
	if (ret != 0) {
		return (EINVAL);
	}

	return (ret);
}
