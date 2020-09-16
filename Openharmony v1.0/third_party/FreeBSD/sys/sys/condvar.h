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
 *
 * $FreeBSD: releng/11.4/sys/sys/condvar.h 331722 2018-03-29 02:50:57Z eadler $
 */

#ifndef	_SYS_CONDVAR_H_
#define	_SYS_CONDVAR_H_

#include <sys/mutex.h>
#include <pthread.h>

#define cv pthread_cond

#define cv_init(cvd,desc)               (void)pthread_cond_init(cvd, NULL)
#define cv_destroy(cvd)                 (void)pthread_cond_destroy(cvd)

extern int cv_timedwait(struct cv *condvar, struct mtx *mtx, int tw_ms);
extern int cv_signal(pthread_cond_t *cond);
extern int cv_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
extern int cv_broadcast(pthread_cond_t *cond);

#endif	/* _SYS_CONDVAR_H_ */
