/*-
 * Copyright (c) 1997, 1998, 1999, 2000-2003
 *	Bill Paul <wpaul@windriver.com>.  All rights reserved.
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
 *	This product includes software developed by Bill Paul.
 * 4. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Bill Paul AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Bill Paul OR THE VOICES IN HIS HEAD
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/11.4/sys/dev/usb/net/if_axe.c 331722 2018-03-29 02:50:57Z eadler $");

/*
 * ASIX Electronics AX88172/AX88178/AX88778 USB 2.0 ethernet driver.
 * Used in the LinkSys USB200M and various other adapters.
 *
 * Manuals available from:
 * http://www.asix.com.tw/datasheet/mac/Ax88172.PDF
 * Note: you need the manual for the AX88170 chip (USB 1.x ethernet
 * controller) to find the definitions for the RX control register.
 * http://www.asix.com.tw/datasheet/mac/Ax88170.PDF
 *
 * Written by Bill Paul <wpaul@windriver.com>
 * Senior Engineer
 * Wind River Systems
 */

/*
 * The AX88172 provides USB ethernet supports at 10 and 100Mbps.
 * It uses an external PHY (reference designs use a RealTek chip),
 * and has a 64-bit multicast hash filter. There is some information
 * missing from the manual which one needs to know in order to make
 * the chip function:
 *
 * - You must set bit 7 in the RX control register, otherwise the
 *   chip won't receive any packets.
 * - You must initialize all 3 IPG registers, or you won't be able
 *   to send any packets.
 *
 * Note that this device appears to only support loading the station
 * address via autload from the EEPROM (i.e. there's no way to manaully
 * set it).
 *
 * (Adam Weinberger wanted me to name this driver if_gir.c.)
 */

/*
 * Ax88178 and Ax88772 support backported from the OpenBSD driver.
 * 2007/02/12, J.R. Oldroyd, fbsd@opal.com
 *
 * Manual here:
 * http://www.asix.com.tw/FrootAttach/datasheet/AX88178_datasheet_Rev10.pdf
 * http://www.asix.com.tw/FrootAttach/datasheet/AX88772_datasheet_Rev10.pdf
 */

#include <lwip/netif.h>
#include <lwip/dhcp.h>
#include <lwip/netifapi.h>
#include <lwip/inet.h>

#include "implementation/global_implementation.h"
#include "usb_ethernet.h"
#include "if_axereg.h"
#include "mii.h"

/*
 * AXE_178_MAX_FRAME_BURST
 * max frame burst size for Ax88178 and Ax88772
 * 0	2048 bytes
 * 1	4096 bytes
 * 2	8192 bytes
 * 3	16384 bytes
 * use the largest your system can handle without USB stalling.
 *
 * NB: 88772 parts appear to generate lots of input errors with
 * a 2K rx buffer and 8K is only slightly faster than 4K on an
 * EHCI port on a T42 so change at your own risk.
 */

#define	AXE_178_MAX_FRAME_BURST	1
#define	AXE_CSUM_FEATURES		(CSUM_IP | CSUM_TCP | CSUM_UDP)

#undef USB_DEBUG_VAR
#define	USB_DEBUG_VAR	axe_debug
#ifdef LOSCFG_USB_DEBUG
static int axe_debug = 0;
void
usb_axe_debug_func(int level)
{
	axe_debug = level;
	PRINTK("The level of usb axe debug is %d\n", level);
}
DEBUG_MODULE(axe, usb_axe_debug_func);
#endif

#define	IFF_DRV_OACTIVE  IFF_MASTER
#define	IFF_SIMPLEX		IFF_SLAVE

/*
 * Various supported device vendors/products.
 */
static const STRUCT_USB_HOST_ID axe_devs[] = {
	{ USB_VPI(0x0B95, 0x772B, AXE_FLAG_772B) },
	{ USB_VPI(0x0B95, 0x772A, AXE_FLAG_772A) },
};

static device_probe_t axe_probe;
static device_attach_t axe_attach;
static device_detach_t axe_detach;

static usb_callback_t axe_bulk_read_callback;
static usb_callback_t axe_bulk_write_callback;

static int axe_miibus_writereg(struct axe_softc *sc, int reg, int val);
static uint16_t axe_miibus_readreg(struct axe_softc *sc, int reg);

static uether_fn_t axe_attach_post;
static uether_fn_t axe_init;
static uether_fn_t axe_stop;
static uether_fn_t axe_start;
static uether_fn_t axe_setmulti;
static uether_fn_t axe_setpromisc;
static uether_fn_t axe_tick;

static void axe_cmd(struct axe_softc *, int, int, int, void *);
static void axe_ax88178_init(struct axe_softc *);
static void axe_ax88772_init(struct axe_softc *);
static void axe_ax88772_phywake(struct axe_softc *);
static void axe_ax88772b_init(struct axe_softc *);
static int axe_get_phyno(struct axe_softc *, int);
static int axe_rx_frame(struct usb_ether *, struct usb_page_cache *, int);
static int axe_rxeof(struct usb_ether *, struct usb_page_cache *,
				    unsigned int offset, unsigned int, struct axe_csum_hdr *);
static void axe_csum_cfg(struct usb_ether *);

static const struct usb_config axe_config[AXE_N_TRANSFER] = {
	{ /* [AXE_BULK_DT_WR] = */
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_OUT,
		.frames = USB_AXE_MAX_FRAMES,
		.bufsize = USB_AXE_MAX_FRAMES * MCLBYTES,
		.flags = {.pipe_bof = 1,.force_short_xfer = 1,},
		.callback = axe_bulk_write_callback,
		.timeout = 10000,	/* 10 seconds */
	},
	{ /* [AXE_BULK_DT_RD] = */
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_IN,
		.bufsize = 16 * MCLBYTES,	/* bytes */
		.flags = {.pipe_bof = 1,.short_xfer_ok = 1,},
		.callback = axe_bulk_read_callback,
		.timeout = 0,	/* no timeout */
	},
};

static const struct ax88772b_mfb ax88772b_mfb_table[] = {
	{ 0x8000, 0x8001, 2048 },
	{ 0x8100, 0x8147, 4096 },
	{ 0x8200, 0x81EB, 6144 },
	{ 0x8300, 0x83D7, 8192 },
	{ 0x84C0, 0x861E, 16384 },
	{ 0x8500, 0x8666, 20480 },
	{ 0x8600, 0x87AE, 24576 },
	{ 0x8700, 0x851E, 32768 }
};

static device_method_t axe_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe, axe_probe),
	DEVMETHOD(device_attach, axe_attach),
	DEVMETHOD(device_detach, axe_detach),
	DEVMETHOD_END
};

static driver_t axe_driver = {
	.name = "USB_AXE",
	.methods = axe_methods,
	.size = sizeof(struct axe_softc),
};

static devclass_t axe_devclass;
DRIVER_MODULE(axe, uhub, axe_driver, axe_devclass, 0, 0);

static const struct usb_ether_methods axe_ue_methods = {
	.ue_attach_post = axe_attach_post,
	.ue_start = axe_start,
	.ue_init = axe_init,
	.ue_stop = axe_stop,
	.ue_setmulti = axe_setmulti,
	.ue_setpromisc = axe_setpromisc,
	.ue_tick = axe_tick,
};

static void
axe_cmd(struct axe_softc *sc, int cmd, int index, int val, void *buf)
{
	struct usb_device_request req;
	usb_error_t err;

	AXE_LOCK_ASSERT(sc, MA_OWNED);

	req.bmRequestType = (AXE_CMD_IS_WRITE(cmd) ?
	    UT_WRITE_VENDOR_DEVICE :
	    UT_READ_VENDOR_DEVICE);
	req.bRequest = AXE_CMD_CMD(cmd);
	USETW(req.wValue, val);
	USETW(req.wIndex, index);
	USETW(req.wLength, AXE_CMD_LEN(cmd));

	err = uether_do_request(&sc->sc_ue, &req, buf, 10000);
	if (err != USB_ERR_NORMAL_COMPLETION) {
		dprintf("Fatal Error in function [%s]! err:%d\n", __FUNCTION__, err);
	}
}

static uint16_t
axe_miibus_readreg(struct axe_softc *sc, int reg)
{
	uint16_t val;

	axe_cmd(sc, AXE_CMD_MII_OPMODE_SW, 0, 0, NULL);
	axe_cmd(sc, AXE_CMD_MII_READ_REG, reg, 0x10, &val);
	axe_cmd(sc, AXE_CMD_MII_OPMODE_HW, 0, 0, NULL);

	val = le16toh(val);
	if (AXE_IS_772(sc) && reg == MII_BMSR) {
		/*
		 * BMSR of AX88772 indicates that it supports extended
		 * capability but the extended status register is
		 * revered for embedded ethernet PHY. So clear the
		 * extended capability bit of BMSR.
		 */
		val &= ~BMSR_EXTCAP;
	}
	return (val);
}

static int
axe_miibus_writereg(struct axe_softc *sc, int reg, int val)
{
	val = htole32(val);

	axe_cmd(sc, AXE_CMD_MII_OPMODE_SW, 0, 0, NULL);
	axe_cmd(sc, AXE_CMD_MII_WRITE_REG, reg, 0x10, &val);
	axe_cmd(sc, AXE_CMD_MII_OPMODE_HW, 0, 0, NULL);
	return (0);
}

static int
axe_setmedium(struct axe_softc *sc)
{
	uint16_t val = AXE_178_MEDIA_RX_EN | AXE_178_MEDIA_MAGIC;
	uint16_t bmcr;
	int b100 = 0;
	int bfull = 0;

	bmcr = axe_miibus_readreg(sc, 0);

	if (bmcr & 0x2000) { /* 100Mbps */
		val |= AXE_178_MEDIA_100TX;
		b100 = 1;
	}

	if (bmcr & 0x100) { /* full-duplex */
		val |= AXE_MEDIA_FULL_DUPLEX | AXE_178_MEDIA_TXFLOW_CONTROL_EN | AXE_178_MEDIA_RXFLOW_CONTROL_EN;
		bfull = 1;
	}

	if (b100)
		PRINTK("- 100Mbps/");
	else
		PRINTK("- 10Mbps/");

	if (bfull)
		PRINTK("Full\n");
	else
		PRINTK("Half\n");

	axe_cmd(sc, AXE_CMD_WRITE_MEDIA, 0, val, NULL);
	return (0);
}

static void
axe_setmulti(struct usb_ether *ue)
{
}

static int
axe_get_phyno(struct axe_softc *sc, int sel)
{
	int phyno;

	switch (AXE_PHY_TYPE(sc->sc_phyaddrs[sel])) {
	case PHY_TYPE_100_HOME:
	case PHY_TYPE_GIG:
		phyno = AXE_PHY_NO(sc->sc_phyaddrs[sel]);
		break;
	case PHY_TYPE_SPECIAL:
		/* FALLTHROUGH */
	case PHY_TYPE_RSVD:
		/* FALLTHROUGH */
	case PHY_TYPE_NON_SUP:
		/* FALLTHROUGH */
	default:
		phyno = -1;
		break;
	}

	return (phyno);
}

static void
axe_uether_pause(struct usb_ether * usbe, unsigned int t_ick)
{
	(void) uether_pause(usbe, t_ick);
}

#define	AXE_GPIO_WRITE(x, y)	do { \
	axe_cmd(sc, AXE_CMD_WRITE_GPIO, 0, (x), NULL); \
	axe_uether_pause(ue, (y)); \
} while (0)

static void
axe_ax88178_init(struct axe_softc *sc)
{
	struct usb_ether *ue;
	int gpio0, ledmode, phymode;
	uint16_t eeprom, val;

	ue = &sc->sc_ue;
	axe_cmd(sc, AXE_CMD_SROM_WR_ENABLE, 0, 0, NULL);
	/* XXX magic */
	axe_cmd(sc, AXE_CMD_SROM_READ, 0, 0x0017, &eeprom);
	eeprom = le16toh(eeprom);
	axe_cmd(sc, AXE_CMD_SROM_WR_DISABLE, 0, 0, NULL);

	/* if EEPROM is invalid we have to use to GPIO0 */
	if (eeprom == 0xffff) {
		phymode = AXE_PHY_MODE_MARVELL;
		gpio0 = 1;
		ledmode = 0;
	} else {
		phymode = eeprom & 0x7f;
		gpio0 = (eeprom & 0x80) ? 0 : 1;
		ledmode = eeprom >> 8;
	}

	/* Program GPIOs depending on PHY hardware. */
	switch (phymode) {
	case AXE_PHY_MODE_MARVELL:
		if (gpio0 == 1) {
			AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM | AXE_GPIO0_EN,
			    hz / 32);
			AXE_GPIO_WRITE(AXE_GPIO0_EN | AXE_GPIO2 | AXE_GPIO2_EN,
			    hz / 32);
			AXE_GPIO_WRITE(AXE_GPIO0_EN | AXE_GPIO2_EN, hz / 4);
			AXE_GPIO_WRITE(AXE_GPIO0_EN | AXE_GPIO2 | AXE_GPIO2_EN,
			    hz / 32);
		} else {
			AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM | AXE_GPIO1 |
			    AXE_GPIO1_EN, hz / 3);
			if (ledmode == 1) {
				AXE_GPIO_WRITE(AXE_GPIO1_EN, hz / 3);
				AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN,
				    hz / 3);
			} else {
				AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN |
				    AXE_GPIO2 | AXE_GPIO2_EN, hz / 32);
				AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN |
				    AXE_GPIO2_EN, hz / 4);
				AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN |
				    AXE_GPIO2 | AXE_GPIO2_EN, hz / 32);
			}
		}
		break;
	case AXE_PHY_MODE_CICADA:
	case AXE_PHY_MODE_CICADA_V2:
	case AXE_PHY_MODE_CICADA_V2_ASIX:
		if (gpio0 == 1)
			AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM | AXE_GPIO0 |
			    AXE_GPIO0_EN, hz / 32);
		else
			AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM | AXE_GPIO1 |
			    AXE_GPIO1_EN, hz / 32);
		break;
	case AXE_PHY_MODE_AGERE:
		AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM | AXE_GPIO1 |
		    AXE_GPIO1_EN, hz / 32);
		AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN | AXE_GPIO2 |
		    AXE_GPIO2_EN, hz / 32);
		AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN | AXE_GPIO2_EN, hz / 4);
		AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN | AXE_GPIO2 |
		    AXE_GPIO2_EN, hz / 32);
		break;
	case AXE_PHY_MODE_REALTEK_8211CL:
	case AXE_PHY_MODE_REALTEK_8211BN:
	case AXE_PHY_MODE_REALTEK_8251CL:
		val = gpio0 == 1 ? AXE_GPIO0 | AXE_GPIO0_EN :
		    AXE_GPIO1 | AXE_GPIO1_EN;
		AXE_GPIO_WRITE(val, hz / 32);
		AXE_GPIO_WRITE(val | AXE_GPIO2 | AXE_GPIO2_EN, hz / 32);
		AXE_GPIO_WRITE(val | AXE_GPIO2_EN, hz / 4);
		AXE_GPIO_WRITE(val | AXE_GPIO2 | AXE_GPIO2_EN, hz / 32);
		if (phymode == AXE_PHY_MODE_REALTEK_8211CL) {
			(void) axe_miibus_writereg(sc, 0x1F, 0x0005);
			(void) axe_miibus_writereg(sc, 0x0C, 0x0000);
			val = axe_miibus_readreg(sc, 0x0001);
			(void) axe_miibus_writereg(sc, 0x01, val | 0x0080);
			(void) axe_miibus_writereg(sc, 0x1F, 0x0000);
		}
		break;
	default:
		/* Unknown PHY model or no need to program GPIOs. */
		break;
	}

	/* soft reset */
	axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0, AXE_SW_RESET_CLEAR, NULL);
	axe_uether_pause(ue, hz / 4);

	axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0,
		AXE_SW_RESET_PRL | AXE_178_RESET_MAGIC, NULL);
	axe_uether_pause(ue, hz / 4);
	/* Enable MII/GMII/RGMII interface to work with external PHY. */
	axe_cmd(sc, AXE_CMD_SW_PHY_SELECT, 0, 0, NULL);
	axe_uether_pause(ue, hz / 4);

	axe_cmd(sc, AXE_CMD_RXCTL_WRITE, 0, 0, NULL);
}

static void
axe_ax88772_init(struct axe_softc *sc)
{
	axe_cmd(sc, AXE_CMD_WRITE_GPIO, 0, 0x00b0, NULL);
	axe_uether_pause(&sc->sc_ue, hz / 16);

	if (sc->sc_phyno == AXE_772_PHY_NO_EPHY) {
		/* ask for the embedded PHY */
		axe_cmd(sc, AXE_CMD_SW_PHY_SELECT, 0, 0x01, NULL);
		axe_uether_pause(&sc->sc_ue, hz / 64);

		/* power down and reset state, pin reset state */
		axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0,
		    AXE_SW_RESET_CLEAR, NULL);
		axe_uether_pause(&sc->sc_ue, hz / 16);

		/* power down/reset state, pin operating state */
		axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0,
		    AXE_SW_RESET_IPPD | AXE_SW_RESET_PRL, NULL);
		axe_uether_pause(&sc->sc_ue, hz / 4);

		/* power up, reset */
		axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0, AXE_SW_RESET_PRL, NULL);

		/* power up, operating */
		axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0,
		    AXE_SW_RESET_IPRL | AXE_SW_RESET_PRL, NULL);
	} else {
		/* ask for external PHY */
		axe_cmd(sc, AXE_CMD_SW_PHY_SELECT, 0, 0x00, NULL);
		axe_uether_pause(&sc->sc_ue, hz / 64);

		/* power down internal PHY */
		axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0,
		    AXE_SW_RESET_IPPD | AXE_SW_RESET_PRL, NULL);
	}

	axe_uether_pause(&sc->sc_ue, hz / 4);
	axe_cmd(sc, AXE_CMD_RXCTL_WRITE, 0, 0, NULL);
}

static void
axe_ax88772_phywake(struct axe_softc *sc)
{
	if (sc->sc_phyno == AXE_772_PHY_NO_EPHY) {
		/* Manually select internal(embedded) PHY - MAC mode. */
		axe_cmd(sc, AXE_CMD_SW_PHY_SELECT, 0, AXE_SW_PHY_SELECT_SS_ENB |
		    AXE_SW_PHY_SELECT_EMBEDDED | AXE_SW_PHY_SELECT_SS_MII,
		    NULL);
		axe_uether_pause(&sc->sc_ue, hz / 32);
	} else {
		/*
		 * Manually select external PHY - MAC mode.
		 * Reverse MII/RMII is for AX88772A PHY mode.
		 */
		axe_cmd(sc, AXE_CMD_SW_PHY_SELECT, 0, AXE_SW_PHY_SELECT_SS_ENB |
		    AXE_SW_PHY_SELECT_EXT | AXE_SW_PHY_SELECT_SS_MII, NULL);
		axe_uether_pause(&sc->sc_ue, hz / 32);
	}
	/* Take PHY out of power down. */
	axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0, AXE_SW_RESET_IPPD |
	    AXE_SW_RESET_IPRL, NULL);
	axe_uether_pause(&sc->sc_ue, hz / 4);
	axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0, AXE_SW_RESET_IPRL, NULL);
	axe_uether_pause(&sc->sc_ue, hz);
	axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0, AXE_SW_RESET_CLEAR, NULL);
	axe_uether_pause(&sc->sc_ue, hz / 32);
	axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0, AXE_SW_RESET_IPRL, NULL);
	axe_uether_pause(&sc->sc_ue, hz / 32);
}

static void
axe_ax88772b_init(struct axe_softc *sc)
{
	struct usb_ether *ue = &sc->sc_ue;
	uint16_t eeprom;
	uint8_t *eaddr;
	uint8_t *tmp;
	uint8_t i;
	struct los_eth_driver *ifp = ue->ue_drv_sc;

	/* Reload EEPROM. */
	AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM, hz / 2);
	/*
	 * Save PHY power saving configuration(high byte) and
	 * clear EEPROM checksum value(low byte).
	 */
	axe_cmd(sc, AXE_CMD_SROM_READ, 0, AXE_EEPROM_772B_PHY_PWRCFG, &eeprom);
	sc->sc_pwrcfg = le16toh(eeprom) & 0xFF00;

	/*
	 * Auto-loaded default station address from internal ROM is
	 * 00:00:00:00:00:00 such that an explicit access to EEPROM
	 * is required to get real station address.
	 */
	eaddr = ue->ue_eaddr;
	ifp->ac_if.hwaddr_len = NETIF_MAX_HWADDR_LEN;
	tmp = (uint8_t *) ifp->ac_if.hwaddr;
	for (i = 0; i < NETIF_MAX_HWADDR_LEN / 2; i++) {
		axe_cmd(sc, AXE_CMD_SROM_READ, 0, AXE_EEPROM_772B_NODE_ID + i, &eeprom);
		eeprom = le16toh(eeprom);
		*eaddr++ = (uint8_t)(eeprom & 0xFF);
		*eaddr++ = (uint8_t)((eeprom >> 8) & 0xFF);
		*tmp++ = (uint8_t)(eeprom & 0xFF);
		*tmp++ = (uint8_t)((eeprom >> 8) & 0xFF);
	}
	axe_cmd(sc, AXE_178_CMD_WRITE_NODEID, 0, 0, ue->ue_eaddr);

	axe_attach_post(ue);

	/* Wakeup PHY. */
	axe_ax88772_phywake(sc);
	/* Stop MAC. */
	axe_cmd(sc, AXE_CMD_RXCTL_WRITE, 0, 0, NULL);

	ifp = ue->ue_drv_sc;
	ifp->ac_if.flags |= NETIF_FLAG_UP | NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET;
	ifp->ac_if.flags &= ~NETIF_FLAG_LINK_UP;
	sc->sc_flags &= ~AXE_FLAG_LINK;

	usbd_transfer_start(sc->sc_xfer[AXE_BULK_DT_RD]);
}

#undef	AXE_GPIO_WRITE

static void
axe_reset(struct axe_softc *sc)
{
	struct usb_config_descriptor *cd;
	usb_error_t err;

	cd = usbd_get_config_descriptor(sc->sc_ue.ue_udev);
	err = usbd_req_set_config(sc->sc_ue.ue_udev, &sc->sc_mtx,
							    cd->bConfigurationValue);
	if (err)
		DPRINTF("reset failed (ignored)\n");

	/* Wait a little while for the chip to get its brains in order. */
	axe_uether_pause(&sc->sc_ue, hz / 100);
	/* Reinitialize controller to achieve full reset. */
	if (sc->sc_flags & AXE_FLAG_178)
		axe_ax88178_init(sc);
	else if (sc->sc_flags & AXE_FLAG_772)
		axe_ax88772_init(sc);
	else if (sc->sc_flags & AXE_FLAG_772A)
		axe_ax88772b_init(sc);
	else if (sc->sc_flags & AXE_FLAG_772B)
		axe_ax88772b_init(sc);

	axe_cmd(sc, AXE_CMD_WRITE_MEDIA, 0,
		AXE_MEDIA_FULL_DUPLEX | AXE_178_MEDIA_TXFLOW_CONTROL_EN | AXE_178_MEDIA_RXFLOW_CONTROL_EN
		| AXE_178_MEDIA_RX_EN | AXE_178_MEDIA_MAGIC, NULL);
}

static void
axe_attach_post(struct usb_ether *ue)
{
	struct axe_softc *sc = uether_getsc(ue);
	/*
	 * Load PHY indexes first. Needed by axe_xxx_init().
	 */
	axe_cmd(sc, AXE_CMD_READ_PHYID, 0, 0, sc->sc_phyaddrs);
	sc->sc_phyno = axe_get_phyno(sc, AXE_PHY_SEL_PRI);
	if (sc->sc_phyno == -1)
		sc->sc_phyno = axe_get_phyno(sc, AXE_PHY_SEL_SEC);
	if (sc->sc_phyno == -1) {
		device_printf(sc->sc_ue.ue_dev,
					    "no valid PHY address found, assuming PHY address 0\n");
		sc->sc_phyno = 0;
	}
	/*
	 * Fetch IPG values.
	 */
	if (sc->sc_flags & (AXE_FLAG_772A | AXE_FLAG_772B)) {
		/* Set IPG values. */
		sc->sc_ipgs[0] = 0x15;
		sc->sc_ipgs[1] = 0x16;
		sc->sc_ipgs[2] = 0x1A;
	} else
		axe_cmd(sc, AXE_CMD_READ_IPG012, 0, 0, sc->sc_ipgs);
}
/*
 * Probe for a AX88172 chip.
 */
static int
axe_probe(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);

	if (uaa->usb_mode != USB_MODE_HOST)
		return (ENXIO);
	if (uaa->info.bConfigIndex != AXE_CONFIG_IDX)
		return (ENXIO);
	if (uaa->info.bIfaceIndex != AXE_IFACE_IDX)
		return (ENXIO);
	return (usbd_lookup_id_by_uaa(axe_devs, sizeof(axe_devs), uaa));
}

static void
axe_miibus_statchg(struct axe_softc *sc, uint16_t link_status)
{
	struct usb_ether *ue = &sc->sc_ue;
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)ifp->driver_context;

	if (drv_sc->state & IFF_DRV_RUNNING) {
		if (link_status) {
			if (sc->sc_flags & AXE_FLAG_772A) {
				PRINTK("\nAX88772A Link Up ");
			}
			else if (sc->sc_flags & AXE_FLAG_772B) {
				PRINTK("\nAX88772B Link Up ");
			}

			(void) axe_setmedium(sc);
			axe_start(ue);

			ifp->ac_if.flags |= NETIF_FLAG_LINK_UP;
			(void)netifapi_netif_set_up(&ifp->ac_if);
		} else {
			if (sc->sc_flags & AXE_FLAG_772A)
				PRINTK("\nAX88772A Link Down\n");
			else if (sc->sc_flags & AXE_FLAG_772B)
				PRINTK("\nAX88772B Link Down\n");

			ifp->ac_if.flags &= ~NETIF_FLAG_LINK_UP;
		}
	}
}

/*
 * Attach the interface. Allocate softc structures, do ifmedia
 * setup and ethernet/BPF attach.
 */
static int
axe_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct axe_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;
	uint8_t iface_index;
	int error;
	sc->sc_flags = USB_GET_DRIVER_INFO(uaa);
	sc->sc_link_status = AXE_LINK_MASK;

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_RECURSE);

	iface_index = AXE_IFACE_IDX;
	error = usbd_transfer_setup(uaa->device, &iface_index, sc->sc_xfer,
		axe_config, AXE_N_TRANSFER, sc, &sc->sc_mtx);
	if (error) {
		device_printf(dev, "allocating USB transfers failed\n");
		goto detach;
	}

	ue->ue_sc = sc;
	ue->ue_dev = dev;
	ue->ue_udev = uaa->device;
	ue->ue_mtx = &sc->sc_mtx;
	ue->ue_methods = &axe_ue_methods;
	error = uether_ifattach(ue);
	if (error) {
		device_printf(dev, "could not attach interface\n");
		goto detach;
	}
	return (0);			/* success */

detach:
	(void) axe_detach(dev);
	return (ENXIO);			/* failure */
}

static int
axe_detach(device_t dev)
{
	struct axe_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;

	usbd_transfer_unsetup(sc->sc_xfer, AXE_N_TRANSFER);
	uether_ifdetach(ue);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}

#if (AXE_BULK_BUF_SIZE >= 0x10000)
#error "Please update axe_bulk_read_callback()!"
#endif

static void
axe_bulk_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct axe_softc *sc = usbd_xfer_softc(xfer);
	struct usb_ether *ue = &sc->sc_ue;
	struct usb_page_cache *pc;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);
	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		pc = usbd_xfer_get_frame(xfer, 0);
		(void) axe_rx_frame(ue, pc, actlen);
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
axe_rx_frame(struct usb_ether *ue, struct usb_page_cache *pc, int actlen)
{
	struct axe_softc *sc = ue->ue_sc;
	struct axe_sframe_hdr hdr;
	struct axe_csum_hdr csum_hdr;
	int error, len, pos;

	pos = 0;
	len = 0;
	error = 0;

	if ((sc->sc_flags & AXE_FLAG_STD_FRAME) != 0) {
		while (pos < actlen) {
			if ((int)(pos + sizeof(hdr)) > actlen) {
				/* too little data */
				error = EINVAL;
				break;
			}

			usbd_copy_out(pc, pos, &hdr, sizeof(hdr));
			if ((hdr.len ^ hdr.ilen) != sc->sc_lenmask) {
				/* we lost sync */
				error = EINVAL;
				break;
			}
			pos += sizeof(hdr);
			len = le16toh(hdr.len);
			if (pos + len > actlen) {
				/* invalid length */
				error = EINVAL;
				break;
			}
			(void) axe_rxeof(ue, pc, pos, len, NULL);
			pos += len + (len % 2);
		}
	} else if ((sc->sc_flags & AXE_FLAG_CSUM_FRAME) != 0) {
		while (pos < actlen) {
			if ((int)(pos + sizeof(csum_hdr)) > actlen) {
				/* too little data */
				error = EINVAL;
				break;
			}
			usbd_copy_out(pc, pos, &csum_hdr, sizeof(csum_hdr));

			csum_hdr.len = le16toh(csum_hdr.len);
			csum_hdr.ilen = le16toh(csum_hdr.ilen);
			csum_hdr.cstatus = le16toh(csum_hdr.cstatus);
			if ((AXE_CSUM_RXBYTES(csum_hdr.len) ^
			    AXE_CSUM_RXBYTES(csum_hdr.ilen)) !=
			    sc->sc_lenmask) {
				/* we lost sync */
				error = EINVAL;
				break;
			}
			/*
			 * Get total transferred frame length including
			 * checksum header.  The length should be multiple
			 * of 4.
			 */
			len = sizeof(csum_hdr) + AXE_CSUM_RXBYTES(csum_hdr.len);
			len = (len + 3) & ~3;
			if (pos + len > actlen) {
				/* invalid length */
				error = EINVAL;
				break;
			}
			(void) axe_rxeof(ue, pc, pos + sizeof(csum_hdr),
				AXE_CSUM_RXBYTES(csum_hdr.len), &csum_hdr);
			pos += len;
		}
	} else {
		(void)axe_rxeof(ue, pc, 0, actlen, NULL);
	}
	return (error);
}

static int
axe_rxeof(struct usb_ether *ue, struct usb_page_cache *pc, unsigned int offset,
		    unsigned int len, struct axe_csum_hdr *csum_hdr)
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

#if ((AXE_BULK_BUF_SIZE >= 0x10000) || (AXE_BULK_BUF_SIZE < (MCLBYTES+4)))
#error "Please update axe_bulk_write_callback()!"
#endif

static void
axe_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct axe_softc *sc = usbd_xfer_softc(xfer);
	struct axe_sframe_hdr hdr;
	struct usb_ether *ue = &(sc->sc_ue);
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)ifp->driver_context;
	struct usb_page_cache *pc;
	uint16_t txlen;
	int nframes, pos;
	struct pbuf *p;
	uint8_t ustat;

	ustat = USB_GET_STATE(xfer);
tr_setup:
	switch (ustat) {
	case USB_ST_TRANSFERRED:
		DPRINTFN(11, "transfer complete\n");
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
			if (AXE_IS_178_FAMILY(sc)) {
				hdr.len = htole16(txlen);
				hdr.ilen = ~hdr.len;
				usbd_copy_in(pc, pos, &hdr, sizeof(hdr));
				pos += sizeof(hdr);
				usbd_copy_in(pc, pos, p->payload, txlen);
				pos += txlen;
			} else {
				usbd_copy_in(pc, pos, p->payload, txlen);
				pos += txlen;
			}

			/* Set frame length. */
			usbd_xfer_set_frame_len(xfer, nframes, pos);

			uether_freebuf(p);
			nframes++;
			if (nframes >= USB_AXE_MAX_FRAMES)
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
		DPRINTFN(11, "transfer error, %s\n",
			    usbd_errstr(error));
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
axe_start(struct usb_ether *ue)
{
	struct axe_softc *sc = ue->ue_sc;

	/*
	 * start the USB transfers, if not already started:
	 */
	usbd_transfer_start(sc->sc_xfer[AXE_BULK_DT_WR]);
	usbd_transfer_start(sc->sc_xfer[AXE_BULK_DT_RD]);
}

static void
axe_csum_cfg(struct usb_ether *ue)
{
	(void)ue;
}

static void
axe_init(struct usb_ether *ue)
{
	struct axe_softc *sc = uether_getsc(ue);
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)ifp->driver_context;
	uint16_t rxmode;

	drv_sc->state = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;

	AXE_LOCK_ASSERT(sc, MA_OWNED);
	if ((drv_sc->state & IFF_DRV_RUNNING) != 0)
		return;

	/* Cancel pending I/O */
	axe_stop(ue);
	axe_reset(sc);

	/* Set MAC address and transmitter IPG values. */
	if (AXE_IS_178_FAMILY(sc)) {
		axe_cmd(sc, AXE_178_CMD_READ_NODEID, 0, 0, ue->ue_eaddr);
		axe_cmd(sc, AXE_178_CMD_WRITE_IPG012, sc->sc_ipgs[2],
			    (sc->sc_ipgs[1] << 8) | (sc->sc_ipgs[0]), NULL);
	} else {
		axe_cmd(sc, AXE_178_CMD_READ_NODEID, 0, 0, ue->ue_eaddr);
		axe_cmd(sc, AXE_172_CMD_WRITE_IPG0, 0, sc->sc_ipgs[0], NULL);
		axe_cmd(sc, AXE_172_CMD_WRITE_IPG1, 0, sc->sc_ipgs[1], NULL);
		axe_cmd(sc, AXE_172_CMD_WRITE_IPG2, 0, sc->sc_ipgs[2], NULL);
	}
	if (AXE_IS_178_FAMILY(sc)) {
		sc->sc_flags &= ~(AXE_FLAG_STD_FRAME | AXE_FLAG_CSUM_FRAME);
		sc->sc_lenmask = AXE_HDR_LEN_MASK;
		sc->sc_flags |= AXE_FLAG_STD_FRAME;
	}
	/* Configure TX/RX checksum offloading. */
	axe_csum_cfg(ue);
	if (sc->sc_flags & AXE_FLAG_772B) {
		/* AX88772B uses different maximum frame burst configuration. */
		axe_cmd(sc, AXE_772B_CMD_RXCTL_WRITE_CFG,
			    ax88772b_mfb_table[AX88772B_MFB_16K].threshold,
			    ax88772b_mfb_table[AX88772B_MFB_16K].byte_cnt, NULL);
	}

	/* Enable receiver, set RX mode. */
	rxmode = (AXE_RXCMD_ALLMULTI | AXE_RXCMD_MULTICAST | AXE_RXCMD_ENABLE);
	if (AXE_IS_178_FAMILY(sc)) {
		if (sc->sc_flags & AXE_FLAG_772B) {
			/*
			 * Select RX header format type 1.  Aligning IP
			 * header on 4 byte boundary is not needed when
			 * checksum offloading feature is not used
			 * because we always copy the received frame in
			 * RX handler.  When RX checksum offloading is
			 * active, aligning IP header is required to
			 * reflect actual frame length including RX
			 * header size.
			 */
			rxmode |= AXE_772B_RXCMD_HDR_TYPE_1;
		} else {
			/*
			 * Default Rx buffer size is too small to get
			 * maximum performance.
			 */
			if (sc->sc_flags & AXE_FLAG_772A)
				rxmode |= AXE_178_RXCMD_MFB_16384;
		}
	} else {
		rxmode |= AXE_172_RXCMD_UNICAST;
	}

	/* If we want promiscuous mode, set the allframes bit. */
	if (drv_sc->state & IFF_PROMISC)
		rxmode |= AXE_RXCMD_PROMISC;

	if (drv_sc->state & IFF_BROADCAST)
		rxmode |= AXE_RXCMD_BROADCAST;

	axe_cmd(sc, AXE_CMD_RXCTL_WRITE, 0, rxmode, NULL);

	/* Load the multicast filter. */
	axe_setmulti(ue);

	usbd_xfer_set_stall(sc->sc_xfer[AXE_BULK_DT_WR]);
	usbd_xfer_set_stall(sc->sc_xfer[AXE_BULK_DT_RD]);

	drv_sc->state |= IFF_DRV_RUNNING;
	ifp->ac_if.link_layer_type = ETHERNET_DRIVER_IF;
}

static void
axe_setpromisc(struct usb_ether *ue)
{
	struct axe_softc *sc = uether_getsc(ue);
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)ifp->driver_context;
	uint16_t rxmode;

	axe_cmd(sc, AXE_CMD_RXCTL_READ, 0, 0, &rxmode);

	rxmode = le16toh(rxmode);

	if (drv_sc->state & IFF_PROMISC) {
		rxmode |= AXE_RXCMD_PROMISC;
	} else {
		rxmode &= ~AXE_RXCMD_PROMISC;
	}

	axe_cmd(sc, AXE_CMD_RXCTL_WRITE, 0, rxmode, NULL);
	axe_setmulti(ue);
}

static void
axe_tick(struct usb_ether *ue)
{
	struct axe_softc *sc = uether_getsc(ue);
	uint16_t link_status;

	AXE_LOCK_ASSERT(sc, MA_OWNED);

	link_status = axe_miibus_readreg(sc, MII_BMSR) & AXE_LINK_MASK;
	if (sc->sc_link_status != link_status) {
		axe_miibus_statchg(sc, link_status);
		sc->sc_link_status = link_status;
	}
}

static void
axe_stop(struct usb_ether *ue)
{
	struct axe_softc *sc = uether_getsc(ue);
	struct los_eth_driver *ifp = ue->ue_drv_sc;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc *)ifp->driver_context;

	AXE_LOCK_ASSERT(sc, MA_OWNED);
	drv_sc->state &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->sc_flags &= ~AXE_FLAG_LINK;
	/*
	 * stop all the transfers, if not already stopped:
	 */
	usbd_transfer_stop(sc->sc_xfer[AXE_BULK_DT_WR]);
	usbd_transfer_stop(sc->sc_xfer[AXE_BULK_DT_RD]);
}

#undef USB_DEBUG_VAR
