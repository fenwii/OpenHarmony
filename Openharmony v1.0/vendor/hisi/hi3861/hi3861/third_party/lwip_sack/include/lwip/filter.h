/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2019. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: declaration for socket filter
 * Author: none
 * Create: 2013
 */

#ifndef __LWIP_FILTER_H__
#define __LWIP_FILTER_H__

#include "lwip/opt.h"

#if LWIP_SOCK_FILTER

#include "lwip/pbuf.h"
#include "lwip/mem.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

/* @brief Defines codes of socket filter. */
struct sock_filter {
  u16_t code; /* compiler code */
  u8_t jt;    /* jump if true */
  u8_t jf;    /* jump if false */
  u32_t k;    /* misc field */
};

/* @brief Defines value types of SO_ATTACH_FILTER for setsockopt. */
struct sock_fprog {
  u16_t len;                    /* the length of the filter array */
  struct sock_filter *filter;   /* pointer of socket filter codes */
};

#define LSF_CLASS(code) ((code) & 0x07)
#define         LSF_LD          0x00
#define         LSF_LDX         0x01
#define         LSF_ST          0x02
#define         LSF_STX         0x03
#define         LSF_ALU         0x04
#define         LSF_JMP         0x05
#define         LSF_RET         0x06
#define         LSF_MISC        0x07

/* ld/ldx */
#define LSF_SIZE(code)  ((code) & 0x18)
#define         LSF_W           0x00
#define         LSF_H           0x08
#define         LSF_B           0x10
#define LSF_MODE(code)  ((code) & 0xe0)
#define         LSF_IMM         0x00
#define         LSF_ABS         0x20
#define         LSF_IND         0x40
#define         LSF_MEM         0x60
#define         LSF_LEN         0x80
#define         LSF_MSH         0xa0  /* unsupported */

/* alu/jmp */
#define LSF_OP(code)    ((code) & 0xf0)
#define         LSF_ADD         0x00
#define         LSF_SUB         0x10
#define         LSF_MUL         0x20
#define         LSF_DIV         0x30
#define         LSF_OR          0x40
#define         LSF_AND         0x50
#define         LSF_LSH         0x60
#define         LSF_RSH         0x70
#define         LSF_NEG         0x80
#define         LSF_JA          0x00
#define         LSF_JEQ         0x10
#define         LSF_JGT         0x20
#define         LSF_JGE         0x30
#define         LSF_JSET        0x40
#define LSF_SRC(code)   ((code) & 0x08)
#define         LSF_K           0x00
#define         LSF_X           0x08

/* ret - LSF_K and LSF_X also apply */
#define LSF_RVAL(code)  ((code) & 0x18)
#define         LSF_A           0x10

/* misc */
#define LSF_MISCOP(code) ((code) & 0xf8)
#define         LSF_TAX         0x00
#define         LSF_TXA         0x80

#ifndef LSF_MAXINSNS
#define LSF_MAXINSNS 128
#endif


/*
 * Number of scratch memory words for: LSF_ST and LSF_STX
 */
#define LSF_MEMWORDS 16

struct netconn;
s32_t sock_filter(struct netconn *conn, struct pbuf *pbuf);
u32_t sock_run_filter(struct pbuf *pbuf, struct sock_filter *filter, u16_t flen);
s32_t sock_attach_filter(struct sock_fprog *fprog, struct netconn *conn);
s32_t sock_detach_filter(struct netconn *conn);
s32_t sock_check_filter(struct sock_filter *filter, int len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LWIP_SOCK_FILTER */
#endif /* __LWIP_FILTER_H__ */

