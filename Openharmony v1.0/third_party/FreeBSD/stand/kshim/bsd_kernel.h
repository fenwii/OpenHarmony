/* $FreeBSD: releng/11.4/stand/kshim/bsd_kernel.h 329183 2018-02-12 20:51:28Z kevans $ */
/*-
 * Copyright (c) 2011 Hans Petter Selasky. All rights reserved.
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

#ifndef _BSD_KERNEL_H_
#define	_BSD_KERNEL_H_

#include <los_typedef.h>
#include <stdint.h>

#define	_KERNEL
#include "sys/module.h"
#include "sys/bus.h"

#define	__FreeBSD_version 1000000

#define	rebooting 0
#define	M_USB 0
#define	M_USBDEV 0
#define	USB_PROC_MAX 3
#define	M_DEVBUF 1


#define	SYSCTL_DECL(...)
#define	SYSCTL_INT(...)
#define	TUNABLE_INT(...)
#define	EVENTHANDLER_DECLARE(...)
#define	EVENTHANDLER_INVOKE(...)
#define	SCHEDULER_STOPPED(x) (0)
#define	PI_SWI(...) (0)
#define	UNIQ_NAME(x) x
#define	UNIQ_NAME_STR(x) #x

#define	hz  LOSCFG_BASE_CORE_TICK_PER_SECOND
#ifndef PAGE_SIZE
#define	PAGE_SIZE 4096
#endif

typedef unsigned long bus_addr_t;
typedef unsigned long bus_size_t;

typedef void *bus_dmamap_t;
typedef void *bus_dma_tag_t;

typedef unsigned long bus_space_handle_t;

typedef struct bus_dma_segment {
	bus_addr_t	ds_addr;	/* DMA address */
	bus_size_t	ds_len;		/* length of transfer */
} bus_dma_segment_t;

typedef enum {
	BUS_DMA_LOCK	= 0x01,
	BUS_DMA_UNLOCK	= 0x02,
} bus_dma_lock_op_t;

extern struct mtx Giant;

#define CUR_TICKS (LOS_TickCountGet() & 0xFFFFFFFF)

#ifdef LOSCFG_USB_DEBUG
#define DEBUG_MODULE(name, func)        \
/*   static  */struct debug_module_data debug_##name##_mod = {  \
        func, #name, { 0, 0 } };

struct debug_module_data {
        void    (*callback) (int arg);
        const char *mod_name;
        TAILQ_ENTRY(debug_module_data) entry;
};

void debug_module_register(void *data);
void debug_module_unregister(void *data);
struct debug_module_data *get_debug_module(const char *modname);
void debug_module_dump(void);

#define usb_debug(fmt, ...) \
	dprintf("[USB_DEBUG]: In %s %d, " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define usb_debug(fmt, ...)
#endif

#define usb_err(fmt, ...) \
	dprintf("[USB_ERR]: In %s %d, " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);

#define	device_printf(dev, fmt,...) \
	dprintf("%s (%s): " fmt, __FUNCTION__, device_get_nameunit(dev), ##__VA_ARGS__)

#define	bus_get_dma_tag(...) (NULL)

/* BUS SPACE API */

void module_register(void *);
void module_unregister(void *);
/* USB */

typedef int usb_handle_request_t (device_t dev, const void *req, void **pptr, uint16_t *plen,
								    uint16_t offset, uint8_t *pstate);
typedef int usb_take_controller_t (device_t dev);

/* set some defaults */

#ifndef USB_POOL_SIZE
#define	USB_POOL_SIZE (1024*1024)	/* 1 MByte */
#endif

#ifndef	__DECONST
#define	__DECONST(type, var)	((type)(__uintptr_t)(const void *)(var))
#endif

/* BUS SPACE API */
void	bus_space_write_1(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset, uint8_t data);
void	bus_space_write_2(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset, uint16_t data);
void	bus_space_write_4(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset, uint32_t data);

uint8_t	bus_space_read_1(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset);
uint16_t bus_space_read_2(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset);
uint32_t bus_space_read_4(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset);

void	bus_space_read_multi_1(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset,
							    uint8_t *datap, bus_size_t count);
void	bus_space_read_multi_2(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset,
							    uint16_t *datap, bus_size_t count);
void	bus_space_read_multi_4(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset,
							    uint32_t *datap, bus_size_t count);

void	bus_space_write_multi_1(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset,
							    uint8_t *datap, bus_size_t count);
void	bus_space_write_multi_2(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset,
							    uint16_t *datap, bus_size_t count);
void	bus_space_write_multi_4(bus_space_tag_t t, bus_space_handle_t h, bus_size_t offset,
							    uint32_t *datap, bus_size_t count);

void	bus_space_read_region_1(bus_space_tag_t space, bus_space_handle_t handle, bus_size_t offset,
							    uint8_t *datap, bus_size_t count);
void	bus_space_write_region_1(bus_space_tag_t space, bus_space_handle_t handle, bus_size_t offset,
							    uint8_t *datap, bus_size_t count);
void	bus_space_read_region_4(bus_space_tag_t space, bus_space_handle_t handle, bus_size_t offset,
							    uint32_t *datap, bus_size_t count);
void	bus_space_write_region_4(bus_space_tag_t space, bus_space_handle_t handle, bus_size_t offset,
							    uint32_t *datap, bus_size_t count);

extern void devclass_module_dump(void);

#endif					/* _BSD_KERNEL_H_ */
