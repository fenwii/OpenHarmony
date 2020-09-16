/* $FreeBSD: releng/11.4/sys/dev/usb/net/usb_ethernet.h 334757 2018-06-07 07:32:51Z hselasky $ */
/*-
 * Copyright (c) 2008 Hans Petter Selasky. All rights reserved.
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
 * $FreeBSD: releng/11.4/sys/dev/usb/net/usb_ethernet.h 334757 2018-06-07 07:32:51Z hselasky $
 */

#ifndef _USB_ETHERNET_H_
#define	_USB_ETHERNET_H_

#include "net/usb_eth_drv.h"

/* FreeBSD net Interface flags */
#define	IFF_DRV_RUNNING	0x40	/* (d) resources allocated */

#ifndef	MCLSHIFT
#define	MCLSHIFT	11	/* convert bytes to mbuf clusters */
#endif					/* MCLSHIFT */

#define	MCLBYTES	(1 << MCLSHIFT)	/* size of an mbuf cluster */

/*
 * Structure defining a queue for a network interface.
 */
struct	ifqueue {
	struct	pbuf *ifq_head;
	struct	pbuf *ifq_tail;
	int	ifq_len;
};

#define	UE_LOCK(_ue)	mtx_lock((_ue)->ue_mtx)
#define	UE_UNLOCK(_ue)	mtx_unlock((_ue)->ue_mtx)
#define	UE_LOCK_ASSERT(_ue, t)	mtx_assert((_ue)->ue_mtx, t)

#define	IF_ENQUEUE(ifq, m) do {				 \
	if ((ifq)->ifq_tail == NULL)			 \
		(ifq)->ifq_head = m;				 \
	else									 \
		(ifq)->ifq_tail->next = m;			 \
	(ifq)->ifq_tail = m;					 \
	(ifq)->ifq_len++;						 \
} while (0)

#define	IF_DEQUEUE(ifq, m) do {						 \
	(m) = (ifq)->ifq_head;							 \
	if (m) {										 \
		if (((ifq)->ifq_head = (m)->next) == NULL)	 \
			(ifq)->ifq_tail = NULL;					 \
		(m)->next = NULL;							 \
		(ifq)->ifq_len--;							 \
	}												 \
} while (0)

#define	IF_PREPEND(ifq, m)						\
do {											\
	(m)->next = (ifq)->ifq_head;				\
	if ((ifq)->ifq_tail == NULL)				\
		(ifq)->ifq_tail = (m);					\
	(ifq)->ifq_head = (m);						\
	(ifq)->ifq_len++;							\
} while (0)

struct usb_ether;
struct usb_device_request;

typedef void (uether_fn_t)(struct usb_ether *);

struct usb_ether_methods {
	uether_fn_t		*ue_attach_post;
	uether_fn_t		*ue_start;
	uether_fn_t		*ue_init;
	uether_fn_t		*ue_stop;
	uether_fn_t		*ue_setmulti;
	uether_fn_t		*ue_setpromisc;
	uether_fn_t		*ue_tick;
	int				(*ue_attach_post_sub)(struct usb_ether *);
};

struct usb_ether_cfg_task {
	struct usb_proc_msg hdr;
	struct usb_ether *ue;
};

struct usb_ether {
	/* NOTE: the "ue_ifp" pointer must be first --hps */
	struct los_eth_driver 	*ue_drv_sc;
	EVENT_CB_S 				ue_event;
	struct mtx 				*ue_mtx;
	const struct usb_ether_methods *ue_methods;
	void 					*ue_sc;
	struct usb_device 		*ue_udev; /* used by uether_do_request() */
	device_t 				ue_dev;
	device_t 				ue_miibus;

	struct usb_process	ue_tq;
	struct ifqueue		ue_rxq;
	struct ifqueue		ue_txq;
	struct callout		ue_watchdog;
	struct usb_ether_cfg_task	ue_sync_task[2];
	struct usb_ether_cfg_task	ue_media_task[2];
	struct usb_ether_cfg_task	ue_multi_task[2];
	struct usb_ether_cfg_task	ue_promisc_task[2];
	struct usb_ether_cfg_task	ue_tick_task[2];

	int			ue_unit;

	/* ethernet address from eeprom */
	uint8_t		ue_eaddr[NETIF_MAX_HWADDR_LEN];
};

#define	uether_do_request(ue,req,data,timo) \
    usbd_do_request_proc((ue)->ue_udev,&(ue)->ue_tq,req,data,0,NULL,timo)

uint8_t		uether_pause(struct usb_ether *, unsigned int);
void		*uether_getsc(struct usb_ether *);
int			uether_ifattach(struct usb_ether *);
void		uether_ifattach_wait(struct usb_ether *);
void		uether_ifdetach(struct usb_ether *);
struct pbuf	*uether_newbuf(int length);
void		uether_freebuf(struct pbuf *buf);
int			uether_rxmbuf(struct usb_ether *, struct pbuf *,
		    unsigned int);
void		uether_rxflush(struct usb_ether *);
uint8_t		uether_is_gone(struct usb_ether *);
#endif					/* _USB_ETHERNET_H_ */
