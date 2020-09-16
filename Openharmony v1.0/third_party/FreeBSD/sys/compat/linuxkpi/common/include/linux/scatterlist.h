/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2017 Mellanox Technologies, Ltd.
 * Copyright (c) 2015 Matthew Dillon <dillon@backplane.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/scatterlist.h 345939 2019-04-05 11:32:57Z hselasky $
 */
#ifndef	_LINUX_SCATTERLIST_H_
#define	_LINUX_SCATTERLIST_H_

#include "linux/kernel.h"
#include "los_printf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef unsigned long dma_addr_t;
typedef unsigned long ulong;
typedef unsigned int uint;

typedef struct scatterlist {
#ifdef CONFIG_DEBUG_SG
    ulong   sg_magic;
#endif
    ulong   page_link;
    uint    offset;
    uint    length;
    dma_addr_t      dma_address;
#ifdef CONFIG_NEED_SG_DMA_LENGTH
    uint    dma_length;
#endif
} scatterlist_t;

#define COMPAT_SG_MAGIC    0x87654321

/*
 * sg_mark_end - Mark the end of the scatterlist
 * Param:
 *    psg---SG entryScatterlist
 *
 * Description: Marks the passed in sg entry as the termination point for the psg table.
 *              A call to sg_next() on this entry will return NULL.
 *
 */
static inline void sg_mark_end(scatterlist_t *psg)
{
#ifdef CONFIG_DEBUG_SG
    BUG_ON(psg->sg_magic != COMPAT_SG_MAGIC);
#endif
    /* Set termination bit, clear potential chain bit */
    psg->page_link |= 0x02U;
    psg->page_link &= ~0x01U;
}

static inline void sg_init_table(scatterlist_t *psgl, unsigned int nents)
{
    (void)memset_s(psgl, sizeof(*psgl) * nents, 0, sizeof(*psgl) * nents);

    sg_mark_end(&psgl[nents - 1]);
}

static inline void sg_set_buf(scatterlist_t *psg, const void *buf, unsigned int buflen)
{
    psg->dma_address = VMM_TO_DMA_ADDR((uintptr_t)buf);
    psg->offset = 0;
    psg->length = buflen;
}

static inline void sg_init_one(scatterlist_t *psg, const void *buf, unsigned int buflen)
{
    sg_init_table(psg, 1);
    sg_set_buf(psg, buf, buflen);
}

#define SG_MAGIC    COMPAT_SG_MAGIC
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LINUX_SCATTERLIST_H_ */
