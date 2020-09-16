/*	$NetBSD: ucom.c,v 1.40 2001/11/13 06:24:54 lukem Exp $	*/

/*-
 * Copyright (c) 2001-2003, 2005, 2008
 *	Shunsuke Akiyama <akiyama@jp.FreeBSD.org>.
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
__FBSDID("$FreeBSD: releng/11.4/sys/dev/usb/serial/usb_serial.c 331722 2018-03-29 02:50:57Z eadler $");

/*-
 * Copyright (c) 1998, 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Lennart Augustsson (lennart@augustsson.net) at
 * Carlstedt Research & Technology.
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
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <unistd.h>
#include <los_queue.h>
#ifdef LOSCFG_NET_LWIP_SACK
#include <lwip/netif.h>
#include <lwip/dhcp.h>
#include <lwip/netifapi.h>
#endif
#include "implementation/global_implementation.h"
#include "fs/fs.h"

extern int ucom_modem(struct ucom_softc *sc, int sigon, int sigoff);

#undef USB_DEBUG_VAR
#define	USB_DEBUG_VAR   ucom_debug
#ifdef LOSCFG_USB_DEBUG
static int ucom_debug = 0;
void
serial_debug_func(int level)
{
	ucom_debug = level;
	PRINTK("The level of usb serial debug is %d\n", level);
}
DEBUG_MODULE(serial, serial_debug_func);
#endif

#define	UCOM_CONS_BUFSIZE 1024

static uint8_t *ucom_cons_rx_buf;
static uint8_t *ucom_cons_tx_buf;

static unsigned int ucom_cons_rx_low = 0;
static unsigned int ucom_cons_rx_high = 0;

static unsigned int ucom_cons_tx_low = 0;
static unsigned int ucom_cons_tx_high = 0;

static struct ucom_softc *ucom_cons_softc = NULL;

static int tx_worked = 0;

static usb_proc_callback_t ucom_cfg_start_transfers;
static usb_proc_callback_t ucom_cfg_open;
static usb_proc_callback_t ucom_cfg_close;
static usb_proc_callback_t ucom_cfg_line_state;
static usb_proc_callback_t ucom_cfg_status_change;

static int tty_fd = -1;

static void ucom_unit_free(int);
static int ucom_attach_tty(struct ucom_super_softc *, struct ucom_softc *);
static void ucom_detach_tty(struct ucom_super_softc *, struct ucom_softc *);
static void ucom_queue_command(struct ucom_softc *,
		    usb_proc_callback_t *, struct termios *pt,
		    struct usb_proc_msg *t0, struct usb_proc_msg *t1);
static void ucom_shutdown(struct ucom_softc *);
static void ucom_ring(struct ucom_softc *, uint8_t);
static void ucom_break(struct ucom_softc *, uint8_t);
static void ucom_dtr(struct ucom_softc *, uint8_t);
static void ucom_rts(struct ucom_softc *, uint8_t);
static void ucom_close(struct ucom_softc *sc);

static UINT32 u3g_tx_init(VOID);
static UINT32 u3g_tx_deinit(VOID);
static void ucom_tx_task(void);

static int tty_usb_open(struct file *filep);
static int tty_usb_close(struct file *filep);
static ssize_t tty_usb_read(struct file *filep, char *buffer, size_t buflen);
static ssize_t tty_usb_write(struct file *filep, const char *buffer, size_t buflen);

static const struct file_operations_vfs tty_usb_fops =
{
	tty_usb_open,	/* open */
	tty_usb_close,	/* close */
	tty_usb_read,	/* read */
	tty_usb_write,	/* write */
	NULL,			/* seek */
	NULL,			/* ioctl */
	NULL,			/* mmap */
#ifndef CONFIG_DISABLE_POLL
	NULL,			/* poll */
#endif
	NULL			/* unlink */
};

#define	UCOM_UNIT_MAX		128	/* maximum number of units */
#define	UCOM_TTY_PREFIX		"U"

static struct mtx ucom_mtx;
static int ucom_close_refs;

/*
 * Mark the unit number as not in use.
 */
static void
ucom_unit_free(int unit)
{
	return;
}

/*
 * Setup a group of one or more serial ports.
 *
 * The mutex pointed to by "mtx" is applied before all
 * callbacks are called back. Also "mtx" must be applied
 * before calling into the ucom-layer!
 */
int
ucom_attach(struct ucom_super_softc *ssc, struct ucom_softc *sc,
    int subunits, void *parent,
    const struct ucom_callback *callback, struct mtx *umtx)
{
	int subunit;
	int error;

	DPRINTFN(0, "\n");

	if ((sc == NULL) ||
	    (subunits <= 0) ||
	    (callback == NULL) ||
	    (umtx == NULL)) {
		return (EINVAL);
	}

	/* allocate a uniq unit number */
	ssc->sc_unit = 0;
	if (ssc->sc_unit == -1)
		return (ENOMEM);

	/* generate TTY name string */
	(void)snprintf_s(ssc->sc_ttyname, sizeof(ssc->sc_ttyname), sizeof(ssc->sc_ttyname) - 1,
	    UCOM_TTY_PREFIX "%d", ssc->sc_unit);

	/* create USB request handling process */
	error = usb_proc_create(&ssc->sc_tq, umtx, "ucom", USB_PRI_MED);
	if (error) {
		ucom_unit_free(ssc->sc_unit);
		return (error);
	}
	ssc->sc_subunits = subunits;
	ssc->sc_flag = UCOM_FLAG_ATTACHED |
	    UCOM_FLAG_FREE_UNIT;

	if (callback->ucom_free == NULL)
		ssc->sc_flag |= UCOM_FLAG_WAIT_REFS;

	/* increment reference count */
	ucom_ref(ssc);

	for (subunit = 0; subunit < ssc->sc_subunits; subunit++) {
		sc[subunit].sc_subunit = subunit;
		sc[subunit].sc_super = ssc;
		sc[subunit].sc_mtx = umtx;
		sc[subunit].sc_parent = parent;
		sc[subunit].sc_callback = callback;

		error = ucom_attach_tty(ssc, &sc[subunit]);
		if (error) {
			ucom_detach(ssc, &sc[0]);
			return (error);
		}
		/* increment reference count */
		ucom_ref(ssc);

		/* set subunit attached */
		sc[subunit].sc_flag = UCOM_FLAG_ATTACHED;
	}

	(void)u3g_tx_init();
	ucom_cons_rx_buf = (uint8_t *)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(UCOM_CONS_BUFSIZE));
	ucom_cons_tx_buf = (uint8_t *)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(UCOM_CONS_BUFSIZE));

	return (0);
}

/*
 * The following function will do nothing if the structure pointed to
 * by "ssc" and "sc" is zero or has already been detached.
 */
void
ucom_detach(struct ucom_super_softc *ssc, struct ucom_softc *sc)
{
	int subunit;

	if (!(ssc->sc_flag & UCOM_FLAG_ATTACHED))
		return;		/* not initialized */
	usb_proc_drain(&ssc->sc_tq);

	for (subunit = 0; subunit < ssc->sc_subunits; subunit++) {
		if (sc[subunit].sc_flag & UCOM_FLAG_ATTACHED) {

			ucom_detach_tty(ssc, &sc[subunit]);

			/* avoid duplicate detach */
			sc[subunit].sc_flag &= ~UCOM_FLAG_ATTACHED;
		}
	}

	tty_fd = -1;

	(void)u3g_tx_deinit();

	usb_proc_free(&ssc->sc_tq);

	free(ucom_cons_rx_buf);
	free(ucom_cons_tx_buf);
	ucom_cons_rx_buf = NULL;
	ucom_cons_tx_buf = NULL;

	(void)ucom_unref(ssc);

	if (ssc->sc_flag & UCOM_FLAG_WAIT_REFS)
		ucom_drain(ssc);

	/* make sure we don't detach twice */
	ssc->sc_flag &= ~UCOM_FLAG_ATTACHED;

	ucom_cons_softc = NULL;
}

void
ucom_drain(struct ucom_super_softc *ssc)
{
	mtx_lock(&ucom_mtx);
	while (ssc->sc_refs > 0) {
		PRINTK("ucom: Waiting for a TTY device to close.\n");
		usb_pause_mtx(&ucom_mtx, hz);
	}
	mtx_unlock(&ucom_mtx);
}

void
ucom_drain_all(void *arg)
{
	mtx_lock(&ucom_mtx);
	while (ucom_close_refs > 0) {
		PRINTK("ucom: Waiting for all detached TTY "
		    "devices to have open fds closed.\n");
		usb_pause_mtx(&ucom_mtx, hz);
	}
	mtx_unlock(&ucom_mtx);
}

static int
ucom_attach_tty(struct ucom_super_softc *ssc, struct ucom_softc *sc)
{
	int ret;

	ret = snprintf_s(sc->sc_name, TTY_NAME_LEN, TTY_NAME_LEN - 1, "/dev/ttyUSB%d", sc->sc_subunit);
	if (ret < 0) {
		usb_err("snprintf_s failed\n");
		return (-1);
	}
	(void)register_driver(sc->sc_name, &tty_usb_fops, 0666, sc);
	DPRINTF("unit %d subunit %d is console",
	    ssc->sc_unit, sc->sc_subunit);

	if (ucom_cons_softc == NULL) {
		ucom_cons_softc = sc;

		UCOM_MTX_LOCK(ucom_cons_softc);
		ucom_cons_rx_low = 0;
		ucom_cons_rx_high = 0;
		ucom_cons_tx_low = 0;
		ucom_cons_tx_high = 0;
		UCOM_MTX_UNLOCK(ucom_cons_softc);
	}

	return (0);
}

static void
ucom_detach_tty(struct ucom_super_softc *ssc, struct ucom_softc *sc)
{
	/* the config thread has been stopped when we get here */

	UCOM_MTX_LOCK(sc);
	sc->sc_flag |= UCOM_FLAG_GONE;
	sc->sc_flag &= ~(UCOM_FLAG_HL_READY | UCOM_FLAG_LL_READY);
	ucom_close(sc);	/* close, if any */
	UCOM_MTX_UNLOCK(sc);

	(void)unregister_driver(sc->sc_name);

	UCOM_MTX_LOCK(sc);
	/*
	 * make sure that read and write transfers are stopped
	 */
	if (sc->sc_callback->ucom_stop_read)
		(sc->sc_callback->ucom_stop_read) (sc);
	if (sc->sc_callback->ucom_stop_write)
		(sc->sc_callback->ucom_stop_write) (sc);
	UCOM_MTX_UNLOCK(sc);
}

void
ucom_set_pnpinfo_usb(struct ucom_super_softc *ssc, device_t dev)
{
	char buf[64];
	uint8_t iface_index;
	struct usb_attach_arg *uaa;

	(void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "ttyname=" UCOM_TTY_PREFIX
	    "%d ttyports=%d", ssc->sc_unit, ssc->sc_subunits);

	/* Store the PNP info in the first interface for the device */
	uaa = (struct usb_attach_arg *)device_get_ivars(dev);
	iface_index = uaa->info.bIfaceIndex;

	if (usbd_set_pnpinfo(uaa->device, iface_index, buf) != 0)
		device_printf(dev, "Could not set PNP info\n");

	/*
	 * The following information is also replicated in the PNP-info
	 * string which is registered above:
	 */

}

static void
ucom_queue_command(struct ucom_softc *sc,
    usb_proc_callback_t *fn, struct termios *pt,
    struct usb_proc_msg *t0, struct usb_proc_msg *t1)
{
	struct ucom_super_softc *ssc = sc->sc_super;
	struct ucom_param_task *task;

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (usb_proc_is_gone(&ssc->sc_tq)) {
		DPRINTF("proc is gone\n");
		return;		/* nothing to do */
	}
	/*
	 * NOTE: The task cannot get executed before we drop the
	 * "sc_mtx" mutex. It is safe to update fields in the message
	 * structure after that the message got queued.
	 */
	task = (struct ucom_param_task *)
	    usb_proc_msignal(&ssc->sc_tq, t0, t1);

	/* Setup callback and softc pointers */
	task->hdr.pm_callback = fn;
	task->sc = sc;

	/*
	 * Make a copy of the termios. This field is only present if
	 * the "pt" field is not NULL.
	 */
	if (pt != NULL)
		task->termios_copy = *pt;

	/*
	 * Closing the device should be synchronous.
	 */
	if (fn == ucom_cfg_close)
		usb_proc_mwait(&ssc->sc_tq, t0, t1);

	/*
	 * In case of multiple configure requests,
	 * keep track of the last one!
	 */
	if (fn == ucom_cfg_start_transfers)
		sc->sc_last_start_xfer = &task->hdr;
}

static void
ucom_shutdown(struct ucom_softc *sc)
{
}

/*
 * Return values:
 *	0: normal
 * else: taskqueue is draining or gone
 */
uint8_t
ucom_cfg_is_gone(struct ucom_softc *sc)
{
	struct ucom_super_softc *ssc = sc->sc_super;

	return (usb_proc_is_gone(&ssc->sc_tq));
}

static void
ucom_cfg_start_transfers(struct usb_proc_msg *_task)
{
	struct ucom_cfg_task *task =
	    (struct ucom_cfg_task *)_task;
	struct ucom_softc *sc = task->sc;

	if (!(sc->sc_flag & UCOM_FLAG_LL_READY)) {
		return;
	}
	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		/* TTY device closed */
		return;
	}

	if (_task == sc->sc_last_start_xfer)
		sc->sc_flag |= UCOM_FLAG_GP_DATA;

	if (sc->sc_callback->ucom_start_read) {
		(sc->sc_callback->ucom_start_read) (sc);
	}
	if (sc->sc_callback->ucom_start_write) {
		(sc->sc_callback->ucom_start_write) (sc);
	}
}

void
ucom_start_transfers(struct ucom_softc *sc)
{
	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		return;
	}
	/*
	 * Make sure that data transfers are started in both
	 * directions:
	 */
	if (sc->sc_callback->ucom_start_read) {
		(sc->sc_callback->ucom_start_read) (sc);
	}
	if (sc->sc_callback->ucom_start_write) {
		(sc->sc_callback->ucom_start_write) (sc);
	}
}

static void
ucom_cfg_open(struct usb_proc_msg *_task)
{
	struct ucom_cfg_task *task =
	    (struct ucom_cfg_task *)_task;
	struct ucom_softc *sc = task->sc;

	DPRINTF("\n");

	if (sc->sc_flag & UCOM_FLAG_LL_READY) {

		/* already opened */

	} else {

		sc->sc_flag |= UCOM_FLAG_LL_READY;

		if (sc->sc_callback->ucom_cfg_open) {
			(sc->sc_callback->ucom_cfg_open) (sc);

			/* wait a little */
			usb_pause_mtx(sc->sc_mtx, hz / 10);
		}
	}
}

int
ucom_open(struct ucom_softc *sc)
{
	int error;

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (sc->sc_flag & UCOM_FLAG_GONE) {
		return (ENXIO);
	}
	if (sc->sc_flag & UCOM_FLAG_HL_READY) {
		/* already opened */
		return (0);
	}
	DPRINTF("sc = %p\n", sc);

	if (sc->sc_callback->ucom_pre_open) {
		/*
		 * give the lower layer a chance to disallow TTY open, for
		 * example if the device is not present:
		 */
		error = (sc->sc_callback->ucom_pre_open) (sc);
		if (error) {
			PRINT_ERR("error %d\n",error);
			return (error);
		}
	}
	sc->sc_flag |= UCOM_FLAG_HL_READY;

	/* Disable transfers */
	sc->sc_flag &= ~UCOM_FLAG_GP_DATA;

	sc->sc_lsr = 0;
	sc->sc_msr = 0;
	sc->sc_mcr = 0;

	/* reset programmed line state */
	sc->sc_pls_curr = 0;
	sc->sc_pls_set = 0;
	sc->sc_pls_clr = 0;

	/* reset jitter buffer */
	sc->sc_jitterbuf_in = 0;
	sc->sc_jitterbuf_out = 0;

	ucom_queue_command(sc, ucom_cfg_open, NULL,
	    &sc->sc_open_task[0].hdr,
	    &sc->sc_open_task[1].hdr);

	/* Queue transfer enable command last */
	ucom_queue_command(sc, ucom_cfg_start_transfers, NULL,
	    &sc->sc_start_task[0].hdr,
	    &sc->sc_start_task[1].hdr);

	(void)ucom_modem(sc, SER_DTR | SER_RTS, 0);

	ucom_ring(sc, 0);

	ucom_break(sc, 0);

	return (0);
}

static void
ucom_cfg_close(struct usb_proc_msg *_task)
{
	struct ucom_cfg_task *task =
	    (struct ucom_cfg_task *)_task;
	struct ucom_softc *sc = task->sc;

	DPRINTF("\n");

	if (sc->sc_flag & UCOM_FLAG_LL_READY) {
		sc->sc_flag &= ~UCOM_FLAG_LL_READY;
		if (sc->sc_callback->ucom_cfg_close)
			(sc->sc_callback->ucom_cfg_close) (sc);
	} else {
		/* already closed */
	}
}

static void
ucom_close(struct ucom_softc *sc)
{
	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		DPRINTF("tp=%p already closed\n", sc);
		return;
	}
	ucom_shutdown(sc);

	ucom_queue_command(sc, ucom_cfg_close, NULL,
	    &sc->sc_close_task[0].hdr,
	    &sc->sc_close_task[1].hdr);

	sc->sc_flag &= ~(UCOM_FLAG_HL_READY | UCOM_FLAG_RTS_IFLOW);

	if (sc->sc_callback->ucom_stop_read) {
		(sc->sc_callback->ucom_stop_read) (sc);
	}

	ucom_cons_rx_low = 0;
	ucom_cons_rx_high = 0;

	ucom_cons_tx_low = 0;
	ucom_cons_tx_high = 0;

}

int
ucom_modem(struct ucom_softc *sc, int sigon, int sigoff)
{
	uint8_t onoff;

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		return (0);
	}
	if ((sigon == 0) && (sigoff == 0)) {

		if (sc->sc_mcr & SER_DTR) {
			sigon |= SER_DTR;
		}
		if (sc->sc_mcr & SER_RTS) {
			sigon |= SER_RTS;
		}
		if (sc->sc_msr & SER_CTS) {
			sigon |= SER_CTS;
		}
		if (sc->sc_msr & SER_DCD) {
			sigon |= SER_DCD;
		}
		if (sc->sc_msr & SER_DSR) {
			sigon |= SER_DSR;
		}
		if (sc->sc_msr & SER_RI) {
			sigon |= SER_RI;
		}
		return (sigon);
	}
	if (sigon & SER_DTR) {
		sc->sc_mcr |= SER_DTR;
	}
	if (sigoff & SER_DTR) {
		sc->sc_mcr &= ~SER_DTR;
	}
	if (sigon & SER_RTS) {
		sc->sc_mcr |= SER_RTS;
	}
	if (sigoff & SER_RTS) {
		sc->sc_mcr &= ~SER_RTS;
	}
	onoff = (sc->sc_mcr & SER_DTR) ? 1 : 0;
	ucom_dtr(sc, onoff);

	onoff = (sc->sc_mcr & SER_RTS) ? 1 : 0;
	ucom_rts(sc, onoff);

	return (0);
}

static void
ucom_cfg_line_state(struct usb_proc_msg *_task)
{
	struct ucom_cfg_task *task =
	    (struct ucom_cfg_task *)_task;
	struct ucom_softc *sc = task->sc;
	uint8_t notch_bits;
	uint8_t any_bits;
	uint8_t prev_value;
	uint8_t last_value;
	uint8_t mask;

	if (!(sc->sc_flag & UCOM_FLAG_LL_READY)) {
		return;
	}

	mask = 0;
	/* compute callback mask */
	if (sc->sc_callback->ucom_cfg_set_dtr)
		mask |= UCOM_LS_DTR;
	if (sc->sc_callback->ucom_cfg_set_rts)
		mask |= UCOM_LS_RTS;
	if (sc->sc_callback->ucom_cfg_set_break)
		mask |= UCOM_LS_BREAK;
	if (sc->sc_callback->ucom_cfg_set_ring)
		mask |= UCOM_LS_RING;

	/* compute the bits we are to program */
	notch_bits = (sc->sc_pls_set & sc->sc_pls_clr) & mask;
	any_bits = (sc->sc_pls_set | sc->sc_pls_clr) & mask;
	prev_value = sc->sc_pls_curr ^ notch_bits;
	last_value = sc->sc_pls_curr;

	/* reset programmed line state */
	sc->sc_pls_curr = 0;
	sc->sc_pls_set = 0;
	sc->sc_pls_clr = 0;

	/* ensure that we don't lose any levels */
	if (notch_bits & UCOM_LS_DTR)
		sc->sc_callback->ucom_cfg_set_dtr(sc,
		    (prev_value & UCOM_LS_DTR) ? 1 : 0);
	if (notch_bits & UCOM_LS_RTS)
		sc->sc_callback->ucom_cfg_set_rts(sc,
		    (prev_value & UCOM_LS_RTS) ? 1 : 0);
	if (notch_bits & UCOM_LS_BREAK)
		sc->sc_callback->ucom_cfg_set_break(sc,
		    (prev_value & UCOM_LS_BREAK) ? 1 : 0);
	if (notch_bits & UCOM_LS_RING)
		sc->sc_callback->ucom_cfg_set_ring(sc,
		    (prev_value & UCOM_LS_RING) ? 1 : 0);

	/* set last value */
	if (any_bits & UCOM_LS_DTR)
		sc->sc_callback->ucom_cfg_set_dtr(sc,
		    (last_value & UCOM_LS_DTR) ? 1 : 0);
	if (any_bits & UCOM_LS_RTS)
		sc->sc_callback->ucom_cfg_set_rts(sc,
		    (last_value & UCOM_LS_RTS) ? 1 : 0);
	if (any_bits & UCOM_LS_BREAK)
		sc->sc_callback->ucom_cfg_set_break(sc,
		    (last_value & UCOM_LS_BREAK) ? 1 : 0);
	if (any_bits & UCOM_LS_RING)
		sc->sc_callback->ucom_cfg_set_ring(sc,
		    (last_value & UCOM_LS_RING) ? 1 : 0);
}

static void
ucom_line_state(struct ucom_softc *sc,
    uint8_t set_bits, uint8_t clear_bits)
{
	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		return;
	}

	DPRINTF("on=0x%02x, off=0x%02x\n", set_bits, clear_bits);

	/* update current programmed line state */
	sc->sc_pls_curr |= set_bits;
	sc->sc_pls_curr &= ~clear_bits;
	sc->sc_pls_set |= set_bits;
	sc->sc_pls_clr |= clear_bits;

	/* defer driver programming */
	ucom_queue_command(sc, ucom_cfg_line_state, NULL,
	    &sc->sc_line_state_task[0].hdr,
	    &sc->sc_line_state_task[1].hdr);
}

static void
ucom_ring(struct ucom_softc *sc, uint8_t onoff)
{
	DPRINTF("onoff = %d\n", onoff);

	if (onoff)
		ucom_line_state(sc, UCOM_LS_RING, 0);
	else
		ucom_line_state(sc, 0, UCOM_LS_RING);
}

static void
ucom_break(struct ucom_softc *sc, uint8_t onoff)
{
	DPRINTF("onoff = %d\n", onoff);

	if (onoff)
		ucom_line_state(sc, UCOM_LS_BREAK, 0);
	else
		ucom_line_state(sc, 0, UCOM_LS_BREAK);
}

static void
ucom_dtr(struct ucom_softc *sc, uint8_t onoff)
{
	DPRINTF("onoff = %d\n", onoff);

	if (onoff)
		ucom_line_state(sc, UCOM_LS_DTR, 0);
	else
		ucom_line_state(sc, 0, UCOM_LS_DTR);
}

static void
ucom_rts(struct ucom_softc *sc, uint8_t onoff)
{
	DPRINTF("onoff = %d\n", onoff);

	if (onoff)
		ucom_line_state(sc, UCOM_LS_RTS, 0);
	else
		ucom_line_state(sc, 0, UCOM_LS_RTS);
}

static void
ucom_cfg_status_change(struct usb_proc_msg *_task)
{
	struct ucom_cfg_task *task =
	    (struct ucom_cfg_task *)_task;
	struct ucom_softc *sc = task->sc;
	uint8_t new_msr;
	uint8_t new_lsr;
	uint8_t onoff;
	uint8_t lsr_delta;

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (!(sc->sc_flag & UCOM_FLAG_LL_READY)) {
		return;
	}
	if (sc->sc_callback->ucom_cfg_get_status == NULL) {
		return;
	}
	/* get status */

	new_msr = 0;
	new_lsr = 0;

	(sc->sc_callback->ucom_cfg_get_status) (sc, &new_lsr, &new_msr);

	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		/* TTY device closed */
		return;
	}
	onoff = ((sc->sc_msr ^ new_msr) & SER_DCD);
	lsr_delta = (sc->sc_lsr ^ new_lsr);

	sc->sc_msr = new_msr;
	sc->sc_lsr = new_lsr;

	if (onoff) {
		onoff = (sc->sc_msr & SER_DCD) ? 1 : 0;
		DPRINTF("DCD changed to %d\n", onoff);
	}

	if ((lsr_delta & ULSR_BI) && (sc->sc_lsr & ULSR_BI)) {
		DPRINTF("BREAK detected\n");
	}

	if ((lsr_delta & ULSR_FE) && (sc->sc_lsr & ULSR_FE)) {
		DPRINTF("Frame error detected\n");
	}

	if ((lsr_delta & ULSR_PE) && (sc->sc_lsr & ULSR_PE)) {
		DPRINTF("Parity error detected\n");
	}
}

void
ucom_status_change(struct ucom_softc *sc)
{
	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (sc->sc_flag & UCOM_FLAG_CONSOLE)
		return;		/* not supported */

	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		return;
	}
	DPRINTF("\n");

	ucom_queue_command(sc, ucom_cfg_status_change, NULL,
	    &sc->sc_status_task[0].hdr,
	    &sc->sc_status_task[1].hdr);
}

static void
ucom_outwakeup(struct ucom_softc *sc)
{
	UCOM_MTX_ASSERT(sc, MA_OWNED);

	DPRINTF("sc = %p\n", sc);

	ucom_start_transfers(sc);
}

/*------------------------------------------------------------------------*
 *	ucom_get_data
 *
 * Return values:
 * 0: No data is available.
 * Else: Data is available.
 *------------------------------------------------------------------------*/
uint8_t
ucom_get_data(struct ucom_softc *sc, struct usb_page_cache *pc,
    uint32_t offset, uint32_t len, uint32_t *actlen)
{
	unsigned int temp;
	UCOM_MTX_ASSERT(sc, MA_OWNED);

	/* get total TX length */
	temp = ucom_cons_tx_high - ucom_cons_tx_low;
	temp %= UCOM_CONS_BUFSIZE;

	if (temp > len)
		temp = len;

	/* copy in data */
	if (temp > (UCOM_CONS_BUFSIZE - ucom_cons_tx_low)){
		unsigned int fisrt_len = (UCOM_CONS_BUFSIZE - ucom_cons_tx_low);
		usbd_copy_in(pc, offset, ucom_cons_tx_buf + ucom_cons_tx_low, fisrt_len);
		usbd_copy_in(pc, offset+fisrt_len, ucom_cons_tx_buf, temp-fisrt_len);
		PRINTK("len1 : %d ; len2 : %d \n", fisrt_len, temp);
	}else
		usbd_copy_in(pc, offset, ucom_cons_tx_buf + ucom_cons_tx_low, temp);

	/* update counters */
	ucom_cons_tx_low += temp;
	ucom_cons_tx_low %= UCOM_CONS_BUFSIZE;

	/* store actual length */

	*actlen = temp;

	return (temp ? 1 : 0);

}

void
ucom_put_data(struct ucom_softc *sc, struct usb_page_cache *pc,
    uint32_t offset, uint32_t len)
{
	unsigned int temp;
	UCOM_MTX_ASSERT(sc, MA_OWNED);

	/* get maximum RX length */
	temp = (UCOM_CONS_BUFSIZE - 1) - ucom_cons_rx_high + ucom_cons_rx_low;
	temp %= UCOM_CONS_BUFSIZE;

	if (temp > len)
		temp = len;

	/* limit RX length */
	if (temp > (UCOM_CONS_BUFSIZE - ucom_cons_rx_high)){
		unsigned int first_len = (UCOM_CONS_BUFSIZE - ucom_cons_rx_high);
		usbd_copy_out(pc, offset, ucom_cons_rx_buf + ucom_cons_rx_high, first_len);
		usbd_copy_out(pc, offset+first_len, ucom_cons_rx_buf, temp-first_len);
	/* copy out data */
	}else
		usbd_copy_out(pc, offset, ucom_cons_rx_buf + ucom_cons_rx_high, temp);

	/* update counters */
	ucom_cons_rx_high += temp;
	ucom_cons_rx_high %= UCOM_CONS_BUFSIZE;

	return;
}

/*------------------------------------------------------------------------*
 *	ucom_ref
 *
 * This function will increment the super UCOM reference count.
 *------------------------------------------------------------------------*/
void
ucom_ref(struct ucom_super_softc *ssc)
{
	mtx_lock(&ucom_mtx);
	ssc->sc_refs++;
	mtx_unlock(&ucom_mtx);
}

/*------------------------------------------------------------------------*
 *	ucom_free_unit
 *
 * This function will free the super UCOM's allocated unit
 * number. This function can be called on a zero-initialized
 * structure. This function can be called multiple times.
 *------------------------------------------------------------------------*/
static void
ucom_free_unit(struct ucom_super_softc *ssc)
{
	if (!(ssc->sc_flag & UCOM_FLAG_FREE_UNIT))
		return;

	ucom_unit_free(ssc->sc_unit);

	ssc->sc_flag &= ~UCOM_FLAG_FREE_UNIT;
}

/*------------------------------------------------------------------------*
 *	ucom_unref
 *
 * This function will decrement the super UCOM reference count.
 *
 * Return values:
 * 0: UCOM structures are still referenced.
 * Else: UCOM structures are no longer referenced.
 *------------------------------------------------------------------------*/
int
ucom_unref(struct ucom_super_softc *ssc)
{
	int retval;

	mtx_lock(&ucom_mtx);
	retval = (ssc->sc_refs < 2);
	ssc->sc_refs--;
	mtx_unlock(&ucom_mtx);

	if (retval)
		ucom_free_unit(ssc);

	return (retval);
}

static void
tx_data_copy_in(struct ucom_softc *sc, const void *tx_data, unsigned int len)
{
	unsigned int temp;
	int ret;

	UCOM_MTX_LOCK(sc);

	if(len > UCOM_CONS_BUFSIZE)
		len = UCOM_CONS_BUFSIZE;

	/* get maximum TX length */
	temp = (UCOM_CONS_BUFSIZE - 1) - ucom_cons_tx_high + ucom_cons_tx_low;
	temp %= UCOM_CONS_BUFSIZE;

	if (temp >= len)
		temp = len;

	/* limit RX length */
	if (temp > (UCOM_CONS_BUFSIZE - ucom_cons_tx_high)){
		temp = (UCOM_CONS_BUFSIZE - ucom_cons_tx_high);
		/* copy out data */
		ret = usbd_copy_from_user(ucom_cons_tx_buf + ucom_cons_tx_high, temp, tx_data, temp);
		if (ret != EOK) {
			UCOM_MTX_UNLOCK(sc);
			usb_err("memcpy_s failed!, ret:%d\n", ret);
			return;
		}
		ret = usbd_copy_from_user(ucom_cons_tx_buf, UCOM_CONS_BUFSIZE,
			    (const void *)((char *)tx_data + temp), len - temp);
		if (ret != EOK) {
			UCOM_MTX_UNLOCK(sc);
			usb_err("memcpy_s failed!, ret:%d\n", ret);
			return;
		}
	} else {
		ret = usbd_copy_from_user(ucom_cons_tx_buf + ucom_cons_tx_high,
			    UCOM_CONS_BUFSIZE - ucom_cons_tx_high, tx_data, len);
		if (ret != EOK) {
			UCOM_MTX_UNLOCK(sc);
			usb_err("memcpy_s failed!, ret:%d\n", ret);
			return;
		}
	}

	/* update counters */
	ucom_cons_tx_high += len;
	ucom_cons_tx_high %= UCOM_CONS_BUFSIZE;

	UCOM_MTX_UNLOCK(sc);
	return;
}

static UINT8 m_auc_ucom_handler_pool[sizeof(OS_MEMBOX_S) +
			    ((sizeof(ucom_handler_item_s) + 3) & (~3)) * 8];
static UINT32 m_uw_ucom_handler_queue;
static UINT32 g_u3g_tx_taskid = 0;
static UINT32 g_u3g_rx_taskid = 0;

static void
ucom_rx_task(void)
{
	char buffer[128] = {0};
	int length;
	int i;

	while (1) {
		if (tty_fd > 0) {
			length = read(tty_fd, buffer, 128);
			if (length > 0) {
				for (i = 0; i < length; i++) {
					printf("%c", *(buffer + i));
				}
				printf("\n");
			}
		}
		LOS_Msleep(50);
	}
}

static UINT32
u3g_tx_init(VOID)
{
	TSK_INIT_PARAM_S stappTask;
	UINT32 ret;

	(void)memset_s(&stappTask, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
	stappTask.pfnTaskEntry = (TSK_ENTRY_FUNC)ucom_tx_task;
	stappTask.uwStackSize  = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
	stappTask.pcName =		 "u3g_tx_Task";
	stappTask.usTaskPrio =	 9;
	stappTask.uwResved   =	 LOS_TASK_STATUS_DETACHED;
	ret = LOS_TaskCreate(&g_u3g_tx_taskid, &stappTask);
	if (ret != LOS_OK) {
		PRINT_ERR("Create ucom_tx_task error!\n");
		return (ret);
	}

	(void)memset_s(&stappTask, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
	stappTask.pfnTaskEntry = (TSK_ENTRY_FUNC)ucom_rx_task;
	stappTask.uwStackSize  = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
	stappTask.pcName =		 "u3g_rx_Task";
	stappTask.usTaskPrio =	 9;
	stappTask.uwResved   =	 LOS_TASK_STATUS_DETACHED;
	ret = LOS_TaskCreate(&g_u3g_rx_taskid, &stappTask);
	if (ret != LOS_OK) {
		PRINT_ERR("Create ucom_rx_task error!\n");
		return (ret);
	}

	return (0);
}

static UINT32
u3g_tx_deinit(VOID)
{
	UINT32 ret;

	ret = LOS_TaskDelete(g_u3g_tx_taskid);
	if (ret != LOS_OK) {
		return (ret);
	}

	ret = LOS_TaskDelete(g_u3g_rx_taskid);
	if (ret != LOS_OK) {
		return (ret);
	}

	ret = LOS_QueueDelete(m_uw_ucom_handler_queue);
	if (ret != LOS_OK) {
		return (ret);
	}

	return (LOS_OK);
}

static void
ucom_tx_task(void)
{
	ucom_handler_item_s *p_ucom_tx_handler;
	UINT32 ret;
	int err;

	ret = LOS_MemboxInit(m_auc_ucom_handler_pool, sizeof(m_auc_ucom_handler_pool),
						    sizeof(ucom_handler_item_s));
	if (ret != LOS_OK) {
		PRINTK("%s error!\n", __FUNCTION__);
		return;
	}

	ret = LOS_QueueCreate(NULL, 8, &m_uw_ucom_handler_queue, 0, sizeof(ucom_handler_item_s));
	if (ret != LOS_OK) {
		PRINTK("%s error!\n", __FUNCTION__);
		return;
	}

	tx_worked = 1;
	for ( ; ; ) {
		ret = LOS_QueueRead(m_uw_ucom_handler_queue, &p_ucom_tx_handler,
							    sizeof(ucom_handler_item_s), LOS_WAIT_FOREVER);
		if (ret == LOS_OK) {
			if (p_ucom_tx_handler != NULL) {
				if (tty_fd < 0) {
					PRINTK("Please open ttyUBS0 first!\n");
				} else {
					err = write(tty_fd, p_ucom_tx_handler->p_ucom_tx_data,
							    p_ucom_tx_handler->length);
					if (err < 0) {
					}
				}
				if (p_ucom_tx_handler->p_ucom_tx_data != NULL) {
					free(p_ucom_tx_handler->p_ucom_tx_data);
					p_ucom_tx_handler->p_ucom_tx_data = NULL;
				}
				if (p_ucom_tx_handler != NULL) {
					(void)LOS_MemboxFree(m_auc_ucom_handler_pool,
									    p_ucom_tx_handler);
					p_ucom_tx_handler = NULL;
				}
			}
		}
	}
}

extern struct netif *pnetif_usb0;
#ifdef LOSCFG_NET_LWIP_SACK
uint32_t
u3g_write_from_shell(int argc, const char **argv)
{
	ucom_handler_item_s *p_ucom_tx_handler;
	char *buf;
	int ret;
	size_t len;

	if (tx_worked == 0) {
		PRINTK("u3g : no usb 3g/4g modem worked!\n");
		return (LOS_NOK);
	}

	if (argv == NULL) {
		PRINTK("u3g : please enter AT command!\n");
		return (LOS_NOK);
	}

	if (argc > 1) {
		PRINTK("u3g : only one argc supported!\n");
		return (LOS_NOK);
	}

	if (((argv[0][0]=='A') && (argv[0][1]=='T')) || ((argv[0][0]=='a') && (argv[0][1]=='t'))) {
		p_ucom_tx_handler = (ucom_handler_item_s *)LOS_MemboxAlloc(m_auc_ucom_handler_pool);
		if (p_ucom_tx_handler != NULL) {
			len = strlen(argv[0]);
			if (len == 0) {
				(void)LOS_MemboxFree(m_auc_ucom_handler_pool, p_ucom_tx_handler);
				return (LOS_NOK);
			}

			buf = (char *)malloc(len + 2);
			if (buf == NULL) {
				(void)LOS_MemboxFree(m_auc_ucom_handler_pool, p_ucom_tx_handler);
				return (LOS_NOK);
			}

			ret = memcpy_s(buf, (len + 2), argv[0], len);
			if (ret != EOK) {
				free(buf);
				(void)LOS_MemboxFree(m_auc_ucom_handler_pool, p_ucom_tx_handler);
				return (LOS_NOK);
			}
			buf[len] = 0xd;
			buf[len+1] = 0xa;

			p_ucom_tx_handler->length = len + 2;
			p_ucom_tx_handler->p_ucom_tx_data = (void *)buf;
			if (LOS_QueueWrite(m_uw_ucom_handler_queue, p_ucom_tx_handler,
				    sizeof(UINT32), LOS_NO_WAIT)) {
				(void)LOS_MemboxFree(m_auc_ucom_handler_pool, p_ucom_tx_handler);
			}
		}
	} else if (strcmp("dhcp", argv[0]) == 0) {
		(void)netifapi_dhcp_start(pnetif_usb0);
		while (netifapi_dhcp_is_bound(pnetif_usb0) == 0) {
			(void)sleep(1);
		}
		dprintf("\n----- DHCP success -----\n");
	} else if (strcmp("open", argv[0]) == 0) {
		tty_fd = open("/dev/ttyUSB0", O_RDWR);
		if (tty_fd < 0) {
			PRINTK("open /dev/ttyUSB0 error! errno %d\n", tty_fd);
			return (LOS_NOK);
		}
	} else if (strcmp("close", argv[0]) == 0) {
		if (tty_fd > 0) {
			(void)close(tty_fd);
			tty_fd = -1;
		} else {
			PRINTK("please first open /dev/ttyUSB0\n");
			return (LOS_NOK);
		}
	} else {
		PRINTK("u3g : please enter AT command!\n");
		return (LOS_NOK);
	}

	return (LOS_OK);
}
#endif

UINT8 m_auc_tty_usb_handler_pool[sizeof(OS_MEMBOX_S) +
	    ((sizeof(ucom_handler_item_s) + 3) & (~3)) * 8];
UINT32 m_uw_tty_usb_handler_queue;
pthread_mutex_t tty_usb_mutex;

static int
tty_usb_queue_init(void)
{
	UINT32 ret;

	(void)pthread_mutex_init(&tty_usb_mutex, NULL);

	ret = LOS_MemboxInit(m_auc_tty_usb_handler_pool,
						    sizeof(m_auc_tty_usb_handler_pool), sizeof(ucom_handler_item_s));
	if (ret != LOS_OK) {
		dprintf("%s error!\n", __FUNCTION__);
		return (EINVAL);
	}

	ret = LOS_QueueCreate(NULL, 8, &m_uw_tty_usb_handler_queue,
			    0, sizeof(ucom_handler_item_s));
	if (ret != LOS_OK) {
		dprintf("%s error!\n", __FUNCTION__);
		return (EINVAL);
	}

	return (ENOERR);
}

static void
tty_usb_queue_delete(void)
{
	(void)LOS_QueueDelete(m_uw_tty_usb_handler_queue);
}

static int
tty_usb_write_wait(void)
{
	ucom_handler_item_s *ptty_usb_write_handler;
	UINT32 ret;
	unsigned int write_len = 0;

	(void)pthread_mutex_lock(&tty_usb_mutex);

	ret = LOS_QueueRead(m_uw_tty_usb_handler_queue, &ptty_usb_write_handler,
						    sizeof(ucom_handler_item_s), LOS_WAIT_FOREVER);
	if (ret == LOS_OK) {
		if (ptty_usb_write_handler != NULL) {
			write_len = ptty_usb_write_handler->length;
			(VOID)LOS_MemboxFree(m_auc_tty_usb_handler_pool, ptty_usb_write_handler);
		}
	}
	(void)pthread_mutex_unlock(&tty_usb_mutex);

	return ((int)write_len);
}

static int
tty_usb_open(struct file *filep)
{
	struct ucom_softc *sc = (struct ucom_softc *)filep->f_inode->i_private;
	int ret;

	UCOM_MTX_LOCK(sc);
	if(tty_usb_queue_init() != ENOERR) {
		UCOM_MTX_UNLOCK(sc);
		return (-EINVAL);
	}

	ret = -ucom_open(sc);
	UCOM_MTX_UNLOCK(sc);

	return (ret);
}

static int
tty_usb_close(struct file *filep)
{
	struct ucom_softc *sc = (struct ucom_softc *)filep->f_inode->i_private;

	UCOM_MTX_LOCK(sc);
	tty_usb_queue_delete();
	ucom_close(sc);
	UCOM_MTX_UNLOCK(sc);

	return (0);
}

static ssize_t
tty_usb_read(struct file *filep, char *buffer, size_t buflen)
{
	struct ucom_softc *sc = (struct ucom_softc *)filep->f_inode->i_private;
	int read_len = -1;
	int ret;
	UCOM_MTX_LOCK(sc);

	if (ucom_cons_rx_low != ucom_cons_rx_high) {
		unsigned int temp;

		/* get total TX length */
		temp = ucom_cons_rx_high - ucom_cons_rx_low;
		temp %= UCOM_CONS_BUFSIZE;

		if (temp > buflen)
			temp = buflen;

		/* copy in data */
		if (temp > (UCOM_CONS_BUFSIZE - ucom_cons_rx_low)) {
			unsigned int fisrt_len = (UCOM_CONS_BUFSIZE - ucom_cons_rx_low);
			ret = usbd_copy_to_user(buffer, buflen, ucom_cons_rx_buf + ucom_cons_rx_low, fisrt_len);
			if (ret != EOK) {
				UCOM_MTX_UNLOCK(sc);
				usb_err("memcpy_s failed!, ret:%d\n", ret);
				return (0);
			}
			ret = usbd_copy_to_user(buffer + fisrt_len, (buflen - fisrt_len),
									ucom_cons_rx_buf, temp - fisrt_len);
			if (ret != EOK) {
				UCOM_MTX_UNLOCK(sc);
				usb_err("memcpy_s failed!, ret:%d\n", ret);
				return (0);
			}
			PRINTK("len1 : %d ; len2 : %d \n", fisrt_len, temp);
		}else {
			ret = usbd_copy_to_user(buffer, buflen, ucom_cons_rx_buf + ucom_cons_rx_low, temp);
			if (ret != EOK) {
				UCOM_MTX_UNLOCK(sc);
				usb_err("memcpy_s failed!, ret:%d\n", ret);
				return (0);
			}
		}

		/* update counters */
		ucom_cons_rx_low += temp;
		ucom_cons_rx_low %= UCOM_CONS_BUFSIZE;

		/* store actual length */
		read_len = temp;
	}
	/* start USB transfers */
	ucom_outwakeup(sc);

	UCOM_MTX_UNLOCK(sc);
	return (read_len);
}

static ssize_t
tty_usb_write(struct file *filep, const char *buffer, size_t buflen)
{
	struct ucom_softc *sc = (struct ucom_softc *)filep->f_inode->i_private;

	tx_data_copy_in(sc, (void *)buffer, buflen);
	ucom_outwakeup(sc);

	return (tty_usb_write_wait());
}

#undef USB_DEBUG_VAR
