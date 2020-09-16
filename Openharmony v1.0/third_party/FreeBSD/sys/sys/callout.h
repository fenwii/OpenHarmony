/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)callout.h	8.2 (Berkeley) 1/21/94
 * $FreeBSD: releng/11.4/sys/sys/callout.h 331722 2018-03-29 02:50:57Z eadler $
 */

#ifndef _SYS_CALLOUT_H_
#define _SYS_CALLOUT_H_

#include <sys/_callout.h>

#ifndef MSEC_PER_SEC
#define MSEC_PER_SEC    1000L
#endif

#ifndef NSEC_PER_USEC
#define NSEC_PER_USEC   1000L
#endif

#ifndef NSEC_PER_MSEC
#define NSEC_PER_MSEC   1000000L
#endif

#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC    1000000000L
#endif

void callout_init_mtx(struct callout* c, struct pthread_mutex* mtx, int flag);
void callout_reset(struct callout* c, int to_ticks, void (*func)(void *), void *arg);
void callout_stop(struct callout* c);
void callout_drain(struct callout* c);
void callout_pending(struct callout* c);

#endif /* _SYS_CALLOUT_H_ */
