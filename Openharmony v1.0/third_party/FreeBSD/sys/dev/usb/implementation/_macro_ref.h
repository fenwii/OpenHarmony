/*-
 * Copyright (c) 1982, 1986, 1989, 1993
 *    The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 *
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
 *    @(#)errno.h    8.5 (Berkeley) 1/21/94
 * $FreeBSD$
 */

#ifndef _MACRO_REF_H
#define	_MACRO_REF_H

#define	FREAD		0x0001
#define	FWRITE		0x0002

/* pseudo-errors returned inside kernel to modify return to process */
#define	EJUSTRETURN	(-2)		/* don't modify regs, just return */
#define	ENOIOCTL	(-3)		/* ioctl not handled by this layer */
#define	EDIRIOCTL	(-4)		/* do direct ioctl in GEOM */

/* Ref usb_transfer.c */
#define	WITNESS_WARN(flags, lock, fmt, ...)	(void)0

#ifndef MIN
#define MIN(a,b) (a < b ? a : b)
#endif

#ifndef MAX
#define MAX(a,b) (a > b ? a : b)
#endif

#define	put_unaligned_be16(p, v)	do {*((UINT8*)(p)) = (v >> 8); *((UINT8*)(p + 1)) = (v);}while(0);
#define	put_unaligned_be32(p, v)	do{put_unaligned_be16(p, (v >> 16)) ; put_unaligned_be16((p + 2), v);}while(0);

#define	get_unaligned_be16(p)   (((UINT8*)p)[0] << 8 | ((UINT8*)p)[1])
#define	get_unaligned_be32(p)   (((UINT8*)p)[0] << 24 | ((UINT8*)p)[1] << 16 |((UINT8*)p)[2] << 8 |((UINT8*)p)[3])

#endif
