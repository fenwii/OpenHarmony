/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2015 Mellanox Technologies, Ltd.
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
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/interrupt.h 352474 2019-09-18 07:24:33Z hselasky $
 */
#ifndef	_LINUX_INTERRUPT_H_
#define	_LINUX_INTERRUPT_H_

#include "linux/kernel.h"
#include "los_base.h"
#include "linux/workqueue.h"
#include "asm/hal_platform_ints.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define IRQ_RETVAL(x)    ((x) != IRQ_NONE)

/**
 * These correspond to the IORESOURCE_IRQ_* defines in
 * linux/ioport.h to select the interrupt line behaviour.
 */
#define IRQF_TRIGGER_LOW      0x00000008
#define IRQF_TRIGGER_HIGH     0x00000004
#define IRQF_TRIGGER_FALLING  0x00000002
#define IRQF_TRIGGER_RISING   0x00000001
#define IRQF_TRIGGER_NONE     0x00000000
#define IRQF_TRIGGER_MASK     (IRQF_TRIGGER_HIGH | IRQF_TRIGGER_LOW | \
                               IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)
#define IRQF_PROBE_SHARED     0x00000100

#define IRQ_DEFAULT_PRIORITY  0x0

typedef enum irqreturn {
    IRQ_NONE        = (0U << 0),  /* interrupt was not from this device. */
    IRQ_HANDLED     = (1U << 0),  /* interrupt was handled by this device. */
    IRQ_WAKE_THREAD = (1U << 1)   /* handler requests to wake the handler thread. */
} irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int, void *);
typedef void (*irq_bottom_half_handler_t)(struct work_struct *);

typedef struct irq_args {
    int         iIrq;
    void        *pDevId;
    const char  *pName;
} irq_args;

#define request_irq(irq, handler, flags, name, dev) \
    linux_request_irq(irq, handler, flags, name, dev)

#define free_irq(irq, dev_id) \
    linux_free_irq(irq, dev_id)

#define enable_irq(irq) \
    linux_enable_irq(irq)

#define disable_irq(irq) \
    linux_disable_irq(irq)

extern int linux_request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,
                const char *name, void *dev);
extern void linux_free_irq(unsigned int irq, void *dev_id);
extern void linux_enable_irq(unsigned int irq);
extern void linux_disable_irq(unsigned int irq);

#ifdef WORKQUEUE_SUPPORT_PRIORITY
extern bool irq_bottom_half(struct workqueue_struct *workQueue, irq_bottom_half_handler_t handler, void *data,
                     unsigned int pri);
#else
extern bool irq_bottom_half(struct workqueue_struct *workQueue, irq_bottom_half_handler_t handler, void *data);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LINUX_INTERRUPT_H_ */
