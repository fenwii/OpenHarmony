/*-
 * Copyright (c) 2007 Attilio Rao <attilio@freebsd.org>
 * Copyright (c) 2001 Jason Evans <jasone@freebsd.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice(s), this list of conditions and the following disclaimer as
 *    the first lines of this file unmodified other than the possible 
 *    addition of one or more copyright notices.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice(s), this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * $FreeBSD: releng/11.4/sys/sys/sx.h 331722 2018-03-29 02:50:57Z eadler $
 */

#ifndef	_SYS_SX_H_
#define	_SYS_SX_H_

#include <pthread.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* Ref. usb_device.c */
#define	sx pthread_mutex

#define	sx_init(sx, des)					(void)pthread_mutex_init(sx, 0)
#define	sx_init_flags(sx,des,flag)			(void)pthread_mutex_init(sx, 0)
#define	sx_destroy(sx)						(void)pthread_mutex_destroy(sx)
#define	sx_xlock(sx)						(void)pthread_mutex_lock(sx)
#define	sx_xunlock(sx)						(void)pthread_mutex_unlock(sx)

#define	sx_assert(sx, flag) do {	\
	if(!(sx))	\
		panic("share/exclusive assert at %s:%d", __FUNCTION__, __LINE__);	\
} while (0)

static inline int sx_xlocked(struct sx* sx)
{
	if (sx->owner == (void *)OsCurrTaskGet()) {
		return (1);
	}
	return (0);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* !_SYS_SX_H_ */
