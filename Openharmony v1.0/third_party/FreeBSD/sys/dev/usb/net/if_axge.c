/*-
 * Copyright (c) 2013-2014 Kevin Lo
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
__FBSDID("$FreeBSD: releng/11.4/sys/dev/usb/net/if_axge.c 331722 2018-03-29 02:50:57Z eadler $");

/*
 * ASIX Electronics AX88178A/AX88179 USB 2.0/3.0 gigabit ethernet driver.
 */

#include <lwip/netif.h>
#include <lwip/dhcp.h>
#include <lwip/netifapi.h>
#include <lwip/inet.h>

#include "implementation/global_implementation.h"
#include "usb_ethernet.h"
#include "if_axgereg.h"

static void axge_rx_frame(struct usb_ether *ue, struct usb_page_cache *pc, int actlen);
static void axge_miibus_statchg(struct axge_softc *sc, uint8_t link_status);

#define	IFF_DRV_OACTIVE  IFF_MASTER
#define	IFF_SIMPLEX	  IFF_SLAVE

#undef USB_DEBUG_VAR
#define	USB_DEBUG_VAR   axge_debug
#ifdef LOSCFG_USB_DEBUG
static int axge_debug = 0;
void
usb_axge_debug_func(int level)
{
	axge_debug = level;
	PRINTK("The level of usb axge debug is %d\n", level);
}
DEBUG_MODULE(axge, usb_axge_debug_func);
#endif

/*
 * Various supported device vendors/products.
 */
static const STRUCT_USB_HOST_ID axge_devs[] = {
	{ USB_VPI(0x0B95, 0x178A, AXE_FLAG_178A) },
};

static device_probe_t axge_probe;
static device_attach_t axge_attach;
static device_detach_t axge_detach;

static usb_callback_t axge_bulk_read_callback;
static usb_callback_t axge_bulk_write_callback;

static uether_fn_t axge_attach_post;
static uether_fn_t axge_init;
static uether_fn_t axge_stop;
static uether_fn_t axge_start;
static uether_fn_t axge_setmulti;
static uether_fn_t axge_setpromisc;
static uether_fn_t axge_tick;

static const struct usb_config axge_config[AXGE_N_TRANSFER] = {
	{ /* [AXGE_BULK_DT_WR] = */
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_OUT,
		.frames = 16,
		.bufsize = 16 * MCLBYTES,
		.flags = {.pipe_bof = 1,.force_short_xfer = 1,},
		.callback = axge_bulk_write_callback,
		.timeout = 10000,	/* 10 seconds */
	},
	{ /* [AXGE_BULK_DT_RD] = */
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_IN,
		.bufsize = 16 * MCLBYTES,	/* bytes */
		.flags = {.pipe_bof = 1,.short_xfer_ok = 1,},
		.callback = axge_bulk_read_callback,
		.timeout = 0,	/* no timeout */
	},
};

static const struct {
	uint8_t ctrl;
	uint8_t timer_l;
	uint8_t timer_h;
	uint8_t size;
	uint8_t ifg;
}__packed axge_bulk_size[] = {
	{ 7, 0x4f, 0x00, 0x12, 0xff },
	{ 7, 0x20, 0x03, 0x16, 0xff },
	{ 7, 0xae, 0x07, 0x18, 0xff },
	{ 7, 0xcc, 0x4c, 0x18, 0x08 }
};

static device_method_t axge_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe, axge_probe),
	DEVMETHOD(device_attach, axge_attach),
	DEVMETHOD(device_detach, axge_detach),
	DEVMETHOD_END
};

static driver_t axge_driver = {
	.name = "USB_AXGE",
	.methods = axge_methods,
	.size = sizeof(struct axge_softc),
};

static devclass_t axge_devclass;
DRIVER_MODULE(axge, uhub, axge_driver, axge_devclass, 0, 0);

static const struct usb_ether_methods axge_ue_methods = {
	.ue_attach_post = axge_attach_post,
	.ue_start = axge_start,
	.ue_init = axge_init,
	.ue_stop = axge_stop,
	.ue_setmulti = axge_setmulti,
	.ue_setpromisc = axge_setpromisc,
	.ue_tick = axge_tick,
};

static void
axge_write_mem(struct axge_softc *sc, uint8_t cmd, uint16_t index,
			    uint16_t val, void *buf, unsigned int len)
{
	struct usb_device_request req;

	req.bmRequestType = UT_WRITE_VENDOR_DEVICE;
	req.bRequest = cmd;
	USETW(req.wValue, val);
	USETW(req.wIndex, index);
	USETW(req.wLength, len);

	if (uether_do_request(&sc->sc_ue, &req, buf, 1000)) {
		/* Error ignored. */
	}
}

static void
axge_write_cmd_1(struct axge_softc *sc, uint8_t cmd, uint16_t reg, uint8_t val)
{
	axge_write_mem(sc, cmd, 1, reg, &val, 1);
}

static void
axge_write_cmd_2(struct axge_softc *sc, uint8_t cmd, uint16_t index,
			    uint16_t reg, uint16_t val)
{
	uint8_t temp[2];

	USETW(temp, val);
	axge_write_mem(sc, cmd, index, reg, &temp, 2);
}


static int
axge_read_mem(struct axge_softc *sc, uint8_t cmd, uint16_t index,
			    uint16_t val, void *buf, int len)
{
	struct usb_device_request req;

	AXGE_LOCK_ASSERT(sc, MA_OWNED);

	req.bmRequestType = UT_READ_VENDOR_DEVICE;
	req.bRequest = cmd;
	USETW(req.wValue, val);
	USETW(req.wIndex, index);
	USETW(req.wLength, len);

	return (uether_do_request(&sc->sc_ue, &req, buf, 1000));
}

static uint8_t
axge_read_cmd_1(struct axge_softc *sc, uint8_t cmd, uint16_t reg)
{
	uint8_t val;

	(void)axge_read_mem(sc, cmd, 1, reg, &val, 1);
	return (val);
}

static uint16_t
axge_read_cmd_2(struct axge_softc *sc, uint8_t cmd, uint16_t index, uint16_t reg)
{
	uint8_t val[2];

	(void)axge_read_mem(sc, cmd, index, reg, &val, 2);
	return (UGETW(val));
}

static void
axge_chip_init(struct axge_softc *sc)
{
	/* Power up ethernet PHY. */
	axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_EPPRCR, 0);
	axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_EPPRCR, EPPRCR_IPRL);
	(void)uether_pause(&sc->sc_ue, hz / 4);
	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_CLK_SELECT,
				    AXGE_CLK_SELECT_ACS | AXGE_CLK_SELECT_BCS);
	(void)uether_pause(&sc->sc_ue, hz / 10);
}

static void
axge_csum_cfg(struct usb_ether *ue)
{
	struct axge_softc *sc = ue->ue_sc;
	uint8_t csum;

	csum = 0;
	csum |= CTCR_IP | CTCR_TCP | CTCR_UDP;
	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_CTCR, csum);

	csum = 0;
	csum |= CRCR_IP | CRCR_TCP | CRCR_UDP;
	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_CRCR, csum);
}

static void
axge_setmulti(struct usb_ether *ue)
{
	struct axge_softc *sc = ue->ue_sc;
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	uint16_t rxmode;

	rxmode = axge_read_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_RCR);
	if (ifp->ac_if.flags & (IFF_ALLMULTI | IFF_PROMISC)) {
		rxmode |= RCR_AMALL;
		axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_RCR, rxmode);
		return;
	}

	rxmode &= ~RCR_AMALL;
	axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_RCR, rxmode);
}

static void
axge_setpromisc(struct usb_ether *ue)
{
	struct axge_softc *sc = uether_getsc(ue);
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	uint16_t rxmode;

	rxmode = axge_read_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_RCR);

	if (ifp->ac_if.flags & IFF_PROMISC)
		rxmode |= RCR_PRO;
	else
		rxmode &= ~RCR_PRO;

	axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_RCR, rxmode);
	axge_setmulti(ue);
}

static void
axge_tick(struct usb_ether *ue)
{
	struct axge_softc *sc = uether_getsc(ue);
	uint8_t link_status;

	AXGE_LOCK_ASSERT(sc, MA_OWNED);

	link_status = axge_read_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_PLSR);

	if (sc->sc_link_status != (link_status & AXGE_LINK_MASK)) {
		axge_miibus_statchg(sc, link_status);
		sc->sc_link_status = link_status & AXGE_LINK_MASK;
	}
}

static void
axge_reset(struct axge_softc *sc)
{
	struct usb_config_descriptor *cd;
	usb_error_t err;

	cd = usbd_get_config_descriptor(sc->sc_ue.ue_udev);

	err = usbd_req_set_config(sc->sc_ue.ue_udev, &sc->sc_mtx,
							    cd->bConfigurationValue);
	if (err)
		DPRINTF("reset failed (ignored)\n");

	/* Wait a little while for the chip to get its brains in order. */
	(void)uether_pause(&sc->sc_ue, hz / 100);

	axge_chip_init(sc);
}

static void
axge_attach_post(struct usb_ether *ue)
{
	struct axge_softc *sc = uether_getsc(ue);

	/* Initialize controller and get station address. */
	axge_chip_init(sc);
	(void)axge_read_mem(sc, AXGE_ACCESS_MAC, NETIF_MAX_HWADDR_LEN, AXGE_NIDR,
					    ue->ue_eaddr, NETIF_MAX_HWADDR_LEN);
}
/*
 * Probe for a AX88172 chip.
 */
static int
axge_probe(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);

	if (uaa->usb_mode != USB_MODE_HOST)
		return (ENXIO);
	if (uaa->info.bConfigIndex != AXGE_CONFIG_IDX)
		return (ENXIO);
	if (uaa->info.bIfaceIndex != AXGE_IFACE_IDX)
		return (ENXIO);

	return (usbd_lookup_id_by_uaa(axge_devs, sizeof(axge_devs), uaa));
}

/*
 * Attach the interface. Allocate softc structures, do ifmedia
 * setup and ethernet/BPF attach.
 */
static int
axge_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct axge_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;
	uint8_t iface_index;
	int error;
	sc->sc_flags = USB_GET_DRIVER_INFO(uaa);
	sc->sc_link_status = AXGE_LINK_MASK;

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_RECURSE);

	iface_index = AXGE_IFACE_IDX;
	error = usbd_transfer_setup(uaa->device, &iface_index, sc->sc_xfer,
							    axge_config, AXGE_N_TRANSFER, sc, &sc->sc_mtx);
	if (error) {
		device_printf(dev, "allocating USB transfers failed\n");
		goto detach;
	}
	ue->ue_sc = sc;
	ue->ue_dev = dev;
	ue->ue_udev = uaa->device;
	ue->ue_mtx = &sc->sc_mtx;
	ue->ue_methods = &axge_ue_methods;
	error = uether_ifattach(ue);
	if (error) {
		device_printf(dev, "could not attach interface\n");
		goto detach;
	}
	return (0);			/* success */

detach:
	(void) axge_detach(dev);
	return (ENXIO);			/* failure */
}

static int
axge_detach(device_t dev)
{
	struct axge_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;

	usbd_transfer_unsetup(sc->sc_xfer, AXGE_N_TRANSFER);
	uether_ifdetach(ue);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}

static void
axge_miibus_statchg(struct axge_softc *sc, uint8_t link_status)
{
	struct usb_ether *ue = &sc->sc_ue;
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	uint8_t tmp[5];
	uint16_t val = 0;

	if (link_status & AXGE_LINK_MASK) {
		val = MSR_RE;
		if (link_status & IFM_1000_T) {
			val |= MSR_GM | MSR_EN_125MHZ;
			if (link_status & PLSR_USB_SS)
				(void)memcpy_s(tmp, sizeof(tmp), &axge_bulk_size[0], sizeof(axge_bulk_size[0]));
			else if (link_status & PLSR_USB_HS)
				(void)memcpy_s(tmp, sizeof(tmp), &axge_bulk_size[1], sizeof(axge_bulk_size[1]));
			else
				(void)memcpy_s(tmp, sizeof(tmp), &axge_bulk_size[3], sizeof(axge_bulk_size[3]));
		}
		else if (link_status & IFM_100_TX) {
			val |= MSR_PS;
			if (link_status & (PLSR_USB_SS | PLSR_USB_HS))
				(void)memcpy_s(tmp, sizeof(tmp), &axge_bulk_size[2], sizeof(axge_bulk_size[2]));
			else
				(void)memcpy_s(tmp, sizeof(tmp), &axge_bulk_size[3], sizeof(axge_bulk_size[3]));
		}
		else if (link_status & IFM_10_T) {
			(void)memcpy_s(tmp, sizeof(tmp), &axge_bulk_size[3], sizeof(axge_bulk_size[3]));
		}
		else {
			PRINT_WARN("%s, link_status:%x\n", __FUNCTION__, link_status);
			return;
		}

		/* Rx bulk configuration. */
		axge_write_mem(sc, AXGE_ACCESS_MAC, 5, AXGE_RX_BULKIN_QCTRL, tmp, 5);
		axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_MSR, val);

		ifp->ac_if.flags |= NETIF_FLAG_LINK_UP;

		(void)netifapi_netif_set_up(&ifp->ac_if);
		PRINTK("AX88178A Link Up\n");
	}
	else {
		ifp->ac_if.flags &= ~NETIF_FLAG_LINK_UP;
		PRINTK("AX88178A Link Down\n");
	}
}

static void
axge_bulk_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct axge_softc *sc = usbd_xfer_softc(xfer);
	struct usb_ether *ue = &sc->sc_ue;
	struct usb_page_cache *pc;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);
	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		pc = usbd_xfer_get_frame(xfer, 0);
		axge_rx_frame(ue, pc, actlen);
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		uether_rxflush(ue);
		return;

	default:			/* Error */
		DPRINTF("bulk read error, %s\n", usbd_errstr(error));

		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		return;
	}
}

static int
axge_rxeof(struct usb_ether *ue, struct usb_page_cache *pc, unsigned int offset,
	unsigned int len, uint32_t pkt_hdr)
{
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	struct pbuf *m = pbuf_alloc(PBUF_RAW, len+ETH_PAD_SIZE, PBUF_RAM);
	struct pbuf *p;

	if (len < ETHER_HDR_LEN) {
		(void)pbuf_free(m);
		return (EINVAL);
	}

#if ETH_PAD_SIZE
	/* drop the padding word */
	if (pbuf_header(m, -ETH_PAD_SIZE)) {
		PRINTK("[AXE_ERROR]axe_rxeof : pbuf_header drop failed\n");
		(void)pbuf_free(m);
		return (EINVAL);
	}
#endif

	for (p = m; p != NULL; p = p->next)
		usbd_copy_out(pc, offset, p->payload, p->len);

#if ETH_PAD_SIZE
	/* reclaim the padding word */
	if (pbuf_header(m, ETH_PAD_SIZE)) {
		PRINTK("[AXE_ERROR]axe_rxeof : pbuf_header drop failed\n");
		(void)pbuf_free(m);
		return (EINVAL);
	}
#endif

	driverif_input(&ifp->ac_if, m);
	return (0);
}

static void
axge_rx_frame(struct usb_ether *ue, struct usb_page_cache *pc, int actlen)
{
	uint32_t pos;
	uint32_t pkt_cnt;
	uint32_t rxhdr;
	uint32_t pkt_hdr;
	uint32_t hdr_off;
	uint32_t pktlen;

	/* verify we have enough data */
	if (actlen < (int)sizeof(rxhdr))
		return;

	pos = 0;

	usbd_copy_out(pc, actlen - sizeof(rxhdr), &rxhdr, sizeof(rxhdr));
	rxhdr = le32toh(rxhdr);

	pkt_cnt = (uint16_t)rxhdr;
	hdr_off = (uint16_t)(rxhdr >> 16);

	while (pkt_cnt--) {
		/* verify the header offset */
		if ((int)(hdr_off + sizeof(pkt_hdr)) > actlen) {
			DPRINTF("End of packet headers\n");
			break;
		}
		if ((int)pos >= actlen) {
			DPRINTF("Data position reached end\n");
			break;
		}
		usbd_copy_out(pc, hdr_off, &pkt_hdr, sizeof(pkt_hdr));

		pkt_hdr = le32toh(pkt_hdr);
		pktlen = (pkt_hdr >> 16) & 0x1fff;
		if (pkt_hdr & (AXGE_RXHDR_CRC_ERR | AXGE_RXHDR_DROP_ERR)) {
			DPRINTF("Dropped a packet\n");
		}
		if (pktlen >= 6 && (int)(pos + pktlen) <= actlen) {
			(void)axge_rxeof(ue, pc, pos, pktlen, pkt_hdr);
		} else {
			DPRINTF("Invalid packet pos=%d len=%d\n",
				    (int)pos, (int)pktlen);
		}
		pos += (pktlen + 7) & ~7;
		hdr_off += sizeof(pkt_hdr);
	}
}

static void
axge_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct axge_softc *sc = usbd_xfer_softc(xfer);
	struct usb_ether *ue = &(sc->sc_ue);
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)ifp->driver_context;
	struct usb_page_cache *pc;
	uint16_t txlen;
	uint32_t nframes, pos;
	struct pbuf *p;
	uint8_t ustat;
	uint32_t txhdr;

	ustat = USB_GET_STATE(xfer);
tr_setup:
	switch (ustat) {
	case USB_ST_TRANSFERRED:
		drv_sc->state &= ~IFF_DRV_OACTIVE;
		/* FALLTHROUGH */

	case USB_ST_SETUP:
		if (drv_sc->state & IFF_DRV_OACTIVE)
			return;

		UE_LOCK(ue);
		IF_DEQUEUE(&(ue->ue_txq), p);
		UE_UNLOCK(ue);

		nframes = 0;
		while (p) {
			txlen = p->len;
			if (txlen <= 0)
				break;

			usbd_xfer_set_frame_offset(xfer, nframes * MCLBYTES, nframes);
			pos = 0;
			pc = usbd_xfer_get_frame(xfer, nframes);

			txhdr = htole32(txlen);
			usbd_copy_in(pc, 0, &txhdr, sizeof(txhdr));
			txhdr = 0;
			txhdr = htole32(txhdr);
			usbd_copy_in(pc, 4, &txhdr, sizeof(txhdr));
			pos += 8;
			usbd_copy_in(pc, pos, p->payload, txlen);
			pos += txlen;
			if ((pos % usbd_xfer_max_framelen(xfer)) == 0)
				txhdr |= 0x80008000;

			/* Set frame length. */
			usbd_xfer_set_frame_len(xfer, nframes, pos);

			uether_freebuf(p);
			nframes++;
			if (nframes >= 16)
				break;

			UE_LOCK(ue);
			IF_DEQUEUE(&(ue->ue_txq), p);
			UE_UNLOCK(ue);
		}
		if (nframes != 0) {
			usbd_xfer_set_frames(xfer, nframes);
			usbd_transfer_submit(xfer);
			drv_sc->state |= IFF_DRV_OACTIVE;
		}
		break;

	default:			/* Error */
		drv_sc->state &= ~IFF_DRV_OACTIVE;
		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			ustat = USB_ST_SETUP;
			goto tr_setup;
		}
		break;
	}
}

static void
axge_start(struct usb_ether *ue)
{
	struct axge_softc *sc = ue->ue_sc;

	/*
	 * start the USB transfers, if not already started:
	 */
	usbd_transfer_start(sc->sc_xfer[AXGE_BULK_DT_WR]);
	usbd_transfer_start(sc->sc_xfer[AXGE_BULK_DT_RD]);
}

static void
axge_init(struct usb_ether *ue)
{
	struct axge_softc *sc = uether_getsc(ue);
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)ifp->driver_context;
	uint16_t rxmode;

	drv_sc->state = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;

	AXGE_LOCK_ASSERT(sc, MA_OWNED);
	if ((drv_sc->state & IFF_DRV_RUNNING) != 0)
		return;

	/* Cancel pending I/O */
	axge_stop(ue);
	axge_reset(sc);

	/* Set MAC address. */
	ifp->ac_if.hwaddr_len = NETIF_MAX_HWADDR_LEN;
	(void)axge_read_mem(sc, AXGE_ACCESS_MAC, 6, AXGE_NIDR, ifp ->ac_if.hwaddr, 6);

	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_PWLLR, 0x34);
	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_PWLHR, 0x52);

	ifp->ac_if.flags |= NETIF_FLAG_UP | NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET;

	/* Configure TX/RX checksum offloading. */
	axge_csum_cfg(ue);

	/* Configure RX settings. */
	rxmode = (RCR_AM | RCR_SO | RCR_DROP_CRCE);

	/* If we want promiscuous mode, set the allframes bit. */
	if (ifp->ac_if.flags & IFF_PROMISC)
		rxmode |= RCR_PRO;

	if (ifp->ac_if.flags & IFF_BROADCAST)
		rxmode |= RCR_AB;

	axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_RCR, rxmode);

	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_MMSR,
				    MMSR_PME_TYPE | MMSR_PME_POL | MMSR_RWMP);

	/* Load the multicast filter. */
	axge_setmulti(ue);

	drv_sc->state |= IFF_DRV_RUNNING;
}

static void
axge_stop(struct usb_ether *ue)
{
	struct axge_softc *sc = uether_getsc(ue);
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)ifp->driver_context;

	AXGE_LOCK_ASSERT(sc, MA_OWNED);
	drv_sc->state &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->sc_flags &= ~AXE_FLAG_LINK;
	/*
	 * stop all the transfers, if not already stopped:
	 */
	usbd_transfer_stop(sc->sc_xfer[AXGE_BULK_DT_WR]);
	usbd_transfer_stop(sc->sc_xfer[AXGE_BULK_DT_RD]);
}

#undef USB_DEBUG_VAR
