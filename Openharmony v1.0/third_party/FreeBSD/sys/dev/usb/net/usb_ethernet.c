/* $FreeBSD: releng/11.4/sys/dev/usb/net/usb_ethernet.c 334757 2018-06-07 07:32:51Z hselasky $ */
/*-
 * Copyright (c) 2009 Andrew Thompson (thompsa@FreeBSD.org)
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

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/11.4/sys/dev/usb/net/usb_ethernet.c 334757 2018-06-07 07:32:51Z hselasky $");

#include <lwip/netifapi.h>

#include "implementation/global_implementation.h"
#include "net/usb_ethernet.h"

#define	USE_LWIP_BUFFER 0

static usb_proc_callback_t ue_attach_post_task;
static usb_proc_callback_t ue_tick_task;
static usb_proc_callback_t ue_start_task;
static usb_proc_callback_t ue_stop_task;

struct netif *pnetif_usb0 = NULL;

#define	IFQ_MAXLEN	50
int ifqmaxlen = IFQ_MAXLEN;

static void ue_init(struct los_eth_driver *sc,
				    unsigned char *enaddr,
				    int flags);
static void ue_start(struct los_eth_driver *sc,
				    struct eth_drv_sg *sg_list,
				    int sg_len,
				    int total_len,
				    UINTPTR key);
static void ue_watchdog(void *);
static void ue_start_task(struct usb_proc_msg *_task);

/*
 * Return values:
 *	0: success
 * Else: device has been detached
 */
uint8_t
uether_pause(struct usb_ether *ue, unsigned int _ticks)
{
	if (usb_proc_is_gone(&ue->ue_tq)) {
		/* nothing to do */
		return (1);
	}
	usb_pause_mtx(ue->ue_mtx, _ticks);
	return (0);
}

static void
ue_queue_command(struct usb_ether *ue,
			    usb_proc_callback_t *fn,
			    struct usb_proc_msg *t0, struct usb_proc_msg *t1)
{
	struct usb_ether_cfg_task *task;

	UE_LOCK_ASSERT(ue, MA_OWNED);

	if (usb_proc_is_gone(&ue->ue_tq)) {
		return;		/* nothing to do */
	}
	/*
	 * NOTE: The task cannot get executed before we drop the
	 * "sc_mtx" mutex. It is safe to update fields in the message
	 * structure after that the message got queued.
	 */
	task = (struct usb_ether_cfg_task *)
	    usb_proc_msignal(&ue->ue_tq, t0, t1);

	/* Setup callback and self pointers */
	task->hdr.pm_callback = fn;
	task->ue = ue;

	/*
	 * Start and stop must be synchronous!
	 */
	if ((fn == ue_start_task) || (fn == ue_stop_task))
		usb_proc_mwait(&ue->ue_tq, t0, t1);
}

void *
uether_getsc(struct usb_ether *ue)
{
	return (ue->ue_sc);
}

int
uether_ifattach(struct usb_ether *ue)
{
	int ret = EFAULT;

	/* check some critical parameters */
	if ((ue->ue_dev == NULL) ||
	    (ue->ue_udev == NULL) ||
	    (ue->ue_mtx == NULL) ||
	    (ue->ue_methods == NULL))
		return (EINVAL);

	if (LOS_EventInit(&ue->ue_event) != LOS_OK) {
		device_printf(ue->ue_dev, "event init fail\n");
		goto error;
	}

	ret = usb_proc_create(&ue->ue_tq, ue->ue_mtx,
	    device_get_nameunit(ue->ue_dev), USB_PRI_MED);
	if (ret)
	{
		device_printf(ue->ue_dev, "could not setup taskqueue\n");
		(void)LOS_EventDestroy(&ue->ue_event);
		goto error;
	}

	/* fork rest of the attach code */
	UE_LOCK(ue);
	ue_queue_command(ue, ue_attach_post_task,
	    &ue->ue_sync_task[0].hdr,
	    &ue->ue_sync_task[1].hdr);
	UE_UNLOCK(ue);

error:
	return (ret);
}

void
uether_ifattach_wait(struct usb_ether *ue)
{

	UE_LOCK(ue);
	usb_proc_mwait(&ue->ue_tq,
	    &ue->ue_sync_task[0].hdr,
	    &ue->ue_sync_task[1].hdr);
	UE_UNLOCK(ue);
}

/* allocating space for eth_driver */
static struct los_eth_driver *
if_alloc(void)
{
	struct los_eth_driver *sc;
	struct eth_drv_sc *drv_sc;

	sc = (struct los_eth_driver *)zalloc(sizeof(struct los_eth_driver));
	if (sc == NULL) {
		return (NULL);
	}

	drv_sc = (struct eth_drv_sc *)zalloc(sizeof(struct eth_drv_sc));
	if (drv_sc == NULL) {
		free(sc);
		return (NULL);
	}

	drv_sc->funs = (struct eth_hwr_funs*)zalloc(sizeof(struct eth_hwr_funs));
	if (drv_sc->funs == NULL) {
		PRINTK("could not allocate eth_hwr_funs\n");
		free(sc);
		free(drv_sc);
		return (NULL);
	}
	sc->driver_context = drv_sc;

	return (sc);
}

static void
if_free(struct los_eth_driver * sc)
{
	struct eth_drv_sc *drv_sc;
	if (sc == NULL) {
		return;
	}

	drv_sc = (struct eth_drv_sc *)sc->driver_context;
	if (drv_sc != NULL) {
		if (drv_sc->funs) {
			free(drv_sc->funs);
			drv_sc->funs = NULL;
		}
		free(drv_sc);
		sc->driver_context = NULL;
		free(sc);
	}
}

void
ue_recv(struct los_eth_driver *sc,struct eth_drv_sg *sg_list,int sg_len)
{
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)sc->driver_context;
	struct usb_ether *ue = (struct usb_ether *)drv_sc->driver_private;
	struct pbuf *m;
	UINT32 bytes_in_buffer;
	UINT32 bytes_in_list;
	UINT32 bytes_needed_list;
	UINT32 buffer_pos = 0;
	UINT8 *sg_buf;
	UINT8 *hw_rxbuf;
	int i;
	int ret;

	IF_DEQUEUE(&ue->ue_rxq, m);
	if (m == NULL) {
		PRINTK("no buffer! can not happen!\n");
		/* Delete the space */
		return;
	}

	for(i = 0; i < sg_len; ++i) {
		bytes_in_list = 0;
		while (bytes_in_list < sg_list[i].len) {
			bytes_needed_list = sg_list[i].len - bytes_in_list;
			bytes_in_buffer = m->len;
			bytes_in_buffer -= buffer_pos;

			sg_buf	 = (UINT8 *)(sg_list[i].buf);
			hw_rxbuf = (UINT8 *)(m->payload);
			if (bytes_needed_list < bytes_in_buffer) {
				if (sg_buf != NULL) {
					ret = memcpy_s(&sg_buf[bytes_in_list], bytes_needed_list,
						(UINT8 *)&hw_rxbuf[buffer_pos], bytes_needed_list);
					if (ret != EOK) {
						goto END;
					}
				}
				bytes_in_list += bytes_needed_list;
				buffer_pos += bytes_needed_list;
			} else {
				if (sg_buf != NULL) {
					ret = memcpy_s(&sg_buf[bytes_in_list], bytes_needed_list,
						(UINT8 *)&hw_rxbuf[buffer_pos], bytes_in_buffer);
					if (ret != EOK) {
						goto END;
					}
				}

				bytes_in_list += bytes_in_buffer;
				buffer_pos = 0;
			}
		}
	}

END:
	uether_freebuf(m);
}

int
ue_can_send(struct los_eth_driver *sc)
{
	(void)sc;
	return (true);
}

static const char usb_eth_name[3] = "ue";

static void
ue_attach_post_task(struct usb_proc_msg *_task)
{
	struct usb_ether_cfg_task *task =
	    (struct usb_ether_cfg_task *)_task;
	struct usb_ether *ue = task->ue;
	struct los_eth_driver *sc;
	struct eth_drv_sc *drv_sc;
	int error;

	UE_UNLOCK(ue);

	callout_init_mtx(&ue->ue_watchdog, ue->ue_mtx, 0);

	error = 0;
	sc = if_alloc();
	if (sc == NULL) {
		device_printf(ue->ue_dev, "could not allocate eth_drv_sc\n");
		goto fail;
	}

	drv_sc = (struct eth_drv_sc *)sc->driver_context;
	drv_sc->driver_private = ue;
	drv_sc->dev_name = usb_eth_name;
	if (ue->ue_methods->ue_attach_post_sub != NULL) {
		ue->ue_drv_sc = sc;
		error = ue->ue_methods->ue_attach_post_sub(ue);
	} else {
		drv_sc->funs->send = ue_start;
		drv_sc->funs->can_send = ue_can_send;
		drv_sc->funs->start = ue_init;
		drv_sc->funs->recv = ue_recv;
		drv_sc->funs->eth_drv = &eth_drv_funs_usb;
		ue->ue_drv_sc = sc;
	}

	if (error) {
		device_printf(ue->ue_dev, "attaching PHYs failed\n");
		goto fail;
	}

	(drv_sc->funs->eth_drv->init)(sc, ue->ue_eaddr);

	if (LOS_EventWrite(&ue->ue_event, 0x01) != LOS_OK) {
		device_printf(ue->ue_dev, "event write fail\n");
		goto fail;
	}

	pnetif_usb0 = &sc->ac_if;

	UE_LOCK(ue);
	return;

fail:

	if (ue->ue_drv_sc != NULL) {
		if_free(sc);
		ue->ue_drv_sc = NULL;
	}
	UE_LOCK(ue);
	return;
}

void
uether_ifdetach(struct usb_ether *ue)
{
	struct los_eth_driver *sc;
	struct eth_drv_sc *drv_sc;
	struct pbuf *m;

	/* wait for any post attach or other command to complete */
	usb_proc_drain(&ue->ue_tq);

	/* read "ifnet" pointer after taskqueue drain */
	sc = ue->ue_drv_sc;
	if (sc != NULL) {
		drv_sc = ( struct eth_drv_sc *)sc->driver_context;
		/* we are not running any more */
		UE_LOCK(ue);
		drv_sc->state &= ~IFF_DRV_RUNNING;
		UE_UNLOCK(ue);

		/* drain any callouts */
		callout_drain(&ue->ue_watchdog);

		/* detach ethernet */
		for (;;) {
			UE_LOCK(ue);
			IF_DEQUEUE(&(ue->ue_txq), m);
			UE_UNLOCK(ue);
			if (m == NULL)
				break;
			uether_freebuf(m);
		}
		for (;;) {
			UE_LOCK(ue);
			IF_DEQUEUE(&(ue->ue_rxq), m);
			UE_UNLOCK(ue);
			if (m == NULL)
				break;
			uether_freebuf(m);
		}

		(void)netifapi_dhcp_stop(&sc->ac_if);
		(void)netifapi_dhcp_cleanup(&sc->ac_if);
		(void)netifapi_netif_remove(&sc->ac_if);

		/* free interface instance */
		if_free(sc);
		ue->ue_drv_sc = NULL;
	}

	/* free taskqueue, if any */
	usb_proc_free(&ue->ue_tq);

	(void)LOS_EventDestroy(&ue->ue_event);
}

uint8_t
uether_is_gone(struct usb_ether *ue)
{
	return (usb_proc_is_gone(&ue->ue_tq));
}

static void
ue_init(struct los_eth_driver *sc,
		    unsigned char *enaddr,
		    int flags)
{
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)sc->driver_context;
	struct usb_ether *ue = (struct usb_ether *)drv_sc->driver_private;

	UE_LOCK(ue);
	ue_start_task(&ue->ue_sync_task[0].hdr);
	UE_UNLOCK(ue);
}

static void
ue_start_task(struct usb_proc_msg *_task)
{
	struct usb_ether_cfg_task *task =
	    (struct usb_ether_cfg_task *)_task;
	struct usb_ether *ue = task->ue;
	struct los_eth_driver *sc = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)sc->driver_context;

	UE_LOCK_ASSERT(ue, MA_OWNED);

	ue->ue_methods->ue_init(ue);

	if ((drv_sc->state & IFF_DRV_RUNNING) == 0)
		return;

	if (ue->ue_methods->ue_tick != NULL)
		callout_reset(&ue->ue_watchdog, hz, ue_watchdog, ue);
}

static void
ue_stop_task(struct usb_proc_msg *_task)
{
	struct usb_ether_cfg_task *task =
	    (struct usb_ether_cfg_task *)_task;
	struct usb_ether *ue = task->ue;

	UE_LOCK_ASSERT(ue, MA_OWNED);

	callout_stop(&ue->ue_watchdog);

	ue->ue_methods->ue_stop(ue);
}

static void
ue_start(struct los_eth_driver *sc,
			    struct eth_drv_sg *sg_list,
			    int sg_len,
			    int total_len,
			    UINTPTR key)
{
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)sc->driver_context;
	struct usb_ether *ue = (struct usb_ether *)drv_sc->driver_private;
	struct pbuf *m;
	int len = 0;
	int i;
	int ret;

	m = uether_newbuf(total_len);
	if (m == NULL) {
		return;
	}

	for (i = 0; i < sg_len; i++) {
		ret = memcpy_s((void *)((char *)m->payload + len), (size_t)(total_len - len),
					    (const void *)(sg_list[i].buf), sg_list[i].len);
		if (ret != EOK) {
			uether_freebuf(m);
			return;
		}
		len += sg_list[i].len;
	}

	UE_LOCK(ue);
	if ((drv_sc->state & IFF_DRV_RUNNING) == 0) {
		UE_UNLOCK(ue);
		uether_freebuf(m);
		return;
	}
	IF_ENQUEUE(&(ue->ue_txq), m);

	ue->ue_methods->ue_start(ue);
	UE_UNLOCK(ue);
}

static void
ue_watchdog(void *arg)
{
	struct usb_ether *ue = (struct usb_ether *)arg;
	struct los_eth_driver *sc = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)sc->driver_context;

	if ((drv_sc->state & IFF_DRV_RUNNING) == 0)
		return;

	ue_queue_command(ue, ue_tick_task,
	    &ue->ue_tick_task[0].hdr,
	    &ue->ue_tick_task[1].hdr);

	callout_reset(&ue->ue_watchdog, hz, ue_watchdog, ue);
}

static void
ue_tick_task(struct usb_proc_msg *_task)
{
	struct usb_ether_cfg_task *task =
	    (struct usb_ether_cfg_task *)_task;
	struct usb_ether *ue = task->ue;
	struct los_eth_driver *sc = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)sc->driver_context;

	if ((drv_sc->state & IFF_DRV_RUNNING) == 0)
		return;

	ue->ue_methods->ue_tick(ue);
}

#if USE_LWIP_BUFFER
struct pbuf *
uether_newbuf(int length)
{
	struct pbuf *m_new;
	m_new = pbuf_alloc(PBUF_RAW, length, PBUF_RAM);

	if (m_new == NULL) {
		PRINTK("pbuf_alloc fail\n");
		return (NULL);
	}
#if ETH_PAD_SIZE
	pbuf_header(m_new, -ETH_PAD_SIZE); /* drop the padding word */
#endif

	return (m_new);
}
#else
struct pbuf *
uether_newbuf(int length)
{
	struct pbuf *m_new = (struct pbuf *)zalloc(sizeof(struct pbuf));
	if (m_new == NULL) {
		PRINTK("pbuf_alloc fail\n");
		return (NULL);
	}
	m_new->payload = memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(length));
	if (m_new->payload == NULL) {
		PRINTK("pbuf_alloc fail\n");
		free(m_new);
		return (NULL);
	}
	(void)memset_s(m_new->payload, SKB_DATA_ALIGN(length), 0, SKB_DATA_ALIGN(length));

	m_new->len = length;

	return (m_new);
}

void
uether_freebuf(struct pbuf *buf)
{
	if(buf != NULL) {
		if(buf->payload) {
			free(buf->payload);
			buf->payload = NULL;
		}
		free(buf);
	}
}
#endif
int
uether_rxmbuf(struct usb_ether *ue, struct pbuf *m, unsigned int len)
{
	UE_LOCK_ASSERT(ue, MA_OWNED);

	m->len = len;

	/* enqueue for later when the lock can be released */
	IF_ENQUEUE(&(ue->ue_rxq), m);
	ue->ue_rxq.ifq_head->tot_len += len;
	return (0);
}

#if USE_LWIP_BUFFER
void
uether_rxflush(struct usb_ether *ue)
{
	struct netif *netif = &(ue->ue_drv_sc->ac_if);
	struct pbuf *m = ue->ue_rxq.ifq_head;
	int tot_len = 0;
	struct pbuf *q;

	UE_LOCK_ASSERT(ue, MA_OWNED);

	PRINTK("uether_rxflush \n");
	for (q = m; q != NULL; q = q->next) {
		tot_len += q->len;
	}
	m->tot_len = tot_len;

#if ETH_PAD_SIZE
	pbuf_header(m, ETH_PAD_SIZE); /* drop the padding word */
#endif

	/*
	 * The USB xfer has been resubmitted so its safe to unlock now.
	 */
	UE_UNLOCK(ue);

	driverif_input(netif, m);
	UE_LOCK(ue);
}
#else
void
uether_rxflush(struct usb_ether *ue)
{
	struct los_eth_driver *sc = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)sc->driver_context;
	struct pbuf *m;

	UE_LOCK_ASSERT(ue, MA_OWNED);
	for (;;) {
		m = ue->ue_rxq.ifq_head;
		if (m == NULL)
			break;

		(drv_sc->funs->eth_drv->recv)(sc, m->len);
	}
}
#endif
