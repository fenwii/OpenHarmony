/*-
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.
 * Copyright (c) 2005, 2009 Robert N. M. Watson
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
 *	@(#)malloc.h	8.5 (Berkeley) 5/3/95
 * $FreeBSD: releng/11.4/sys/sys/malloc.h 331722 2018-03-29 02:50:57Z eadler $
 */

#ifndef _SYS_MALLOC_H_
#define	_SYS_MALLOC_H_

#include <sys/types.h>
#include <los_memory.h>

#define M_NOWAIT        0x0001          /* do not block */
#define M_WAITOK        0x0002          /* ok to block */
#define M_ZERO          0x0100          /* bzero the allocation */
#define M_NOVM          0x0200          /* don't ask VM for pages */
#define M_USE_RESERVE   0x0400          /* can alloc out of reserve memory */
#define M_NODUMP        0x0800          /* don't dump pages in this allocation */
#define M_FIRSTFIT      0x1000          /* Only for vmem, fast fit. */
#define M_BESTFIT       0x2000          /* Only for vmem, low fragmentation. */

#define M_MAGIC         877983977       /* time when first defined :-) */
#define MINALLOCSIZE    4

/*
 *  * Public data structure describing a malloc type.  Private data is hung off
 *   * of ks_handle to avoid encoding internal malloc(9) data structures in
 *    * modules, which will statically allocate struct malloc_type.
 *     */
struct malloc_type {
        struct malloc_type *ks_next;    /* Next in global chain. */
        u_long           ks_magic;      /* Detect programmer error. */
        const char      *ks_shortdesc;  /* Printable type name. */
        void            *ks_handle;     /* Priv. data, was lo_class. */
};


#define MALLOC_DEFINE(type, shortdesc, longdesc)                        \
        struct malloc_type type[1] = {                                  \
                { NULL, M_MAGIC, shortdesc, NULL }                      \
        };

#define bsd_malloc(size, type, flags)	zalloc(size)
#define bsd_free(addr, type)		free(addr)
#define bsd_strdup(p,x)			strdup(p)

#endif /* !_SYS_MALLOC_H_ */
