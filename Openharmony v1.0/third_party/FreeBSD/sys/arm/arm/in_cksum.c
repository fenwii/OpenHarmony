/* $NetBSD: in_cksum.c,v 1.7 1997/09/02 13:18:15 thorpej Exp $ */

/*-
 * Copyright (c) 1988, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1996
 *	Matt Thomas <matt@3am-software.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
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
 *	@(#)in_cksum.c	8.1 (Berkeley) 6/10/93
 */

#include "los_base.h"
#include "sys/types.h"

#define ADDCARRY(x)  (x > 65535 ? x -= 65535 : x)
#define REDUCE32                              \
    {                                      \
    q_util.q = sum;                              \
    sum = q_util.s[0] + q_util.s[1] + q_util.s[2] + q_util.s[3];      \
    }
#define REDUCE16                              \
    {                                      \
    q_util.q = sum;                              \
    l_util.l = q_util.s[0] + q_util.s[1] + q_util.s[2] + q_util.s[3]; \
    sum = l_util.s[0] + l_util.s[1];                  \
    ADDCARRY(sum);                              \
    }

union un_l_util {
    u_int16_t s[2];
    u_int32_t l;
};

union un_q_util {
    u_int16_t s[4];
    u_int32_t l[2];
    u_int64_t q;
};

/*do_cksum is implemented in in_cksum_arm.S*/
extern unsigned int do_cksum(const void * buf, int len);

static u_int64_t _do_cksum(const void *buf, int len)
{
    u_int64_t sum;
    union un_q_util q_util;

    sum = do_cksum(buf, len);
    REDUCE32;
    return (sum);
}

/* This function is for LWIP_CHKSUM */
unsigned short in_cksum(const void *buf, int len)
{
    u_int64_t sum = 0;
    union un_q_util q_util;
    union un_l_util l_util;

    if (((int)buf) & 1) {
        sum = _do_cksum(buf, len) << 8;
    } else {
        sum = _do_cksum(buf, len);
    }

    REDUCE16;
    return (unsigned short)(~sum & 0xffff);
}

/* This function is for LWIP_CHKSUM_COPY */
unsigned short in_cksum_copy(const void *src, void *dst, int len)
{
    u_int64_t sum = 0;
    union un_q_util q_util;
    union un_l_util l_util;
    int src_len = strlen(src);

    if (src_len >= len) {
        src_len = len;
    }
    if (memcpy_s(dst, len, src, src_len) != EOK) {
        return (unsigned short)(sum);
    }

    if (((long)dst) & 1) {
        sum = _do_cksum(dst, len) << 8;
    }else {
        sum = _do_cksum(dst, len);
    }

    REDUCE16;
    return (unsigned short)(~sum & 0xffff);
}

/*As usb_rtl8188eus used csum_partial, so wrapper this interface for usb_rtl8188*/
unsigned int csum_partial(const void *buf, int len, unsigned int wsum)
{
    u_int64_t sum = 0;
    union un_q_util q_util;

    if (((int)buf) & 1) {
        sum = _do_cksum(buf, len) << 8;
    } else {
        sum = _do_cksum(buf, len);
    }
    if(wsum > 0) {
        sum += (unsigned int)wsum;
        REDUCE32;
    }

    return (unsigned int)(sum);
}

/* Keep this function for compatible */
unsigned int csum_partial_copy_nocheck(const void *src, void *dst, int len, unsigned int wsum)
{
    u_int64_t sum = 0;
    union un_q_util q_util;
    int src_len = strlen(src);

    if (src_len >= len) {
        src_len = len;
    }
    if (memcpy_s(dst, len, src, src_len) != EOK) {
        return (unsigned int)(sum);
    }

    if (((int)dst) & 1) {
        sum = _do_cksum(dst, len) << 8;
    }else {
        sum = _do_cksum(dst, len);
    }

    if(wsum > 0) {
        sum += (unsigned int)wsum;
        REDUCE32;
    }

    return (unsigned int)(sum);
}

