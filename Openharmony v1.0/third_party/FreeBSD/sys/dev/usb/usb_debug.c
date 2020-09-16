/* $FreeBSD: releng/11.4/sys/dev/usb/usb_debug.c 331722 2018-03-29 02:50:57Z eadler $ */
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
 */

#include "implementation/global_implementation.h"
#ifdef LOSCFG_SHELL
#include "shcmd.h"
#endif


/*
 * Define this unconditionally in case a kernel module is loaded that
 * has been compiled with debugging options.
 */
int	usb_debug = 0;
#ifdef LOSCFG_USB_DEBUG
void
usb_debug_func(int level)
{
	usb_debug = level;
	PRINTK("The level of usb other class debug is %d\n", level);
}
DEBUG_MODULE(other, usb_debug_func);
#endif

/*------------------------------------------------------------------------*
 *	usb_dump_iface
 *
 * This function dumps information about an USB interface.
 *------------------------------------------------------------------------*/
void
usb_dump_iface(struct usb_interface *iface)
{
	if (iface == NULL) {
		return;
	}
	PRINTK(" iface=%p idesc=%p altindex=%d\n",
	    iface, iface->idesc, iface->alt_index);
}

/*------------------------------------------------------------------------*
 *	usb_dump_device
 *
 * This function dumps information about an USB device.
 *------------------------------------------------------------------------*/
void
usb_dump_device(struct usb_device *udev)
{
	if (udev == NULL) {
		return;
	}
	PRINTK(" bus=%p \n"
	    " address=%d config=%d depth=%d speed=%d self_powered=%d\n"
	    " power=%d langid=%d\n",
	    udev->bus,
	    udev->address, udev->curr_config_no, udev->depth, udev->speed,
	    udev->flags.self_powered, udev->power, udev->langid);
}

/*------------------------------------------------------------------------*
 *	usb_dump_queue
 *
 * This function dumps the USB transfer that are queued up on an USB endpoint.
 *------------------------------------------------------------------------*/
void
usb_dump_queue(struct usb_endpoint *ep)
{
	struct usb_xfer *xfer;
	usb_stream_t x;

	PRINTK("usb_dump_queue: endpoint=%p xfer: ", ep);
	for (x = 0; x != USB_MAX_EP_STREAMS; x++) {
		TAILQ_FOREACH(xfer, &ep->endpoint_q[x].head, wait_entry)
			PRINTK(" %p", xfer);
	}
	PRINTK("\n");
}

/*------------------------------------------------------------------------*
 *	usb_dump_endpoint
 *
 * This function dumps information about an USB endpoint.
 *------------------------------------------------------------------------*/
void
usb_dump_endpoint(struct usb_endpoint *ep)
{
	if (ep) {
		PRINTK("usb_dump_endpoint: endpoint=%p", ep);

		PRINTK(" edesc=%p isoc_next=%d toggle_next=%d",
		    ep->edesc, ep->isoc_next, ep->toggle_next);

		if (ep->edesc) {
			PRINTK(" bEndpointAddress=0x%02x",
			    ep->edesc->bEndpointAddress);
		}
		PRINTK("\n");
		usb_dump_queue(ep);
	} else {
		PRINTK("usb_dump_endpoint: endpoint=NULL\n");
	}
}

/*------------------------------------------------------------------------*
 *	usb_dump_xfer
 *
 * This function dumps information about an USB transfer.
 *------------------------------------------------------------------------*/
void
usb_dump_xfer(struct usb_xfer *xfer)
{
	struct usb_device *udev;
	PRINTK("usb_dump_xfer: xfer=%p\n", xfer);
	if (xfer == NULL) {
		return;
	}
	if (xfer->endpoint == NULL) {
		PRINTK("xfer %p: endpoint=NULL\n",
		    xfer);
		return;
	}
	udev = xfer->xroot->udev;
	PRINTK("xfer %p: udev=%p vid=0x%04x pid=0x%04x addr=%d "
	    "endpoint=%p ep=0x%02x attr=0x%02x\n",
	    xfer, udev,
	    UGETW(udev->ddesc.idVendor),
	    UGETW(udev->ddesc.idProduct),
	    udev->address, xfer->endpoint,
	    xfer->endpoint->edesc->bEndpointAddress,
	    xfer->endpoint->edesc->bmAttributes);
}

#ifdef LOSCFG_USB_DEBUG
unsigned int usb_port_reset_delay	= USB_PORT_RESET_DELAY;
unsigned int usb_port_root_reset_delay	= USB_PORT_ROOT_RESET_DELAY;
unsigned int usb_port_reset_recovery	= USB_PORT_RESET_RECOVERY;
unsigned int usb_port_powerup_delay	= USB_PORT_POWERUP_DELAY;
unsigned int usb_port_resume_delay	= USB_PORT_RESUME_DELAY;
unsigned int usb_set_address_settle	= USB_SET_ADDRESS_SETTLE;
unsigned int usb_resume_delay		= USB_RESUME_DELAY;
unsigned int usb_resume_wait		= USB_RESUME_WAIT;
unsigned int usb_resume_recovery	= USB_RESUME_RECOVERY;
unsigned int usb_extra_power_up_time	= USB_EXTRA_POWER_UP_TIME;

#ifdef LOSCFG_DRIVERS_USB_HOST_EHCI
extern struct debug_module_data debug_ehci_mod;
#endif
#ifdef LOSCFG_DRIVERS_USB_ETHERNET
extern struct debug_module_data debug_axe_mod;
extern struct debug_module_data debug_axge_mod;
#endif
#ifdef LOSCFG_DRIVERS_USB_4G_MODEM
extern struct debug_module_data debug_cdce_mod;
#endif
#ifdef LOSCFG_DRIVERS_USB_RNDIS_HOST
extern struct debug_module_data debug_urndis_mod;
#endif
#if defined(LOSCFG_DRIVERS_USB_SERIAL) || defined(LOSCFG_DRIVERS_USB_4G_MODEM)
extern struct debug_module_data debug_u3g_mod;
extern struct debug_module_data debug_serial_mod;
#endif
#ifdef LOSCFG_DRIVERS_USB_MASS_STORAGE
extern struct debug_module_data debug_umass_mod;
#endif
#ifdef LOSCFG_DRIVERS_USB_HOST_DRIVER
extern struct debug_module_data debug_controller_mod;
extern struct debug_module_data debug_uhub_mod;
extern struct debug_module_data debug_process_mod;
#endif

static struct debug_module_data *debug_mode_list[] = {
#ifdef LOSCFG_DRIVERS_USB_HOST_EHCI
	&debug_ehci_mod,
#endif
#ifdef LOSCFG_DRIVERS_USB_ETHERNET
	&debug_axe_mod,
	&debug_axge_mod,
#endif
#ifdef LOSCFG_DRIVERS_USB_4G_MODEM
	&debug_cdce_mod,
#endif
#ifdef LOSCFG_DRIVERS_USB_RNDIS_HOST
	&debug_urndis_mod,
#endif
#if defined(LOSCFG_DRIVERS_USB_SERIAL) || defined(LOSCFG_DRIVERS_USB_4G_MODEM)
	&debug_u3g_mod,
	&debug_serial_mod,
#endif
#ifdef LOSCFG_DRIVERS_USB_MASS_STORAGE
	&debug_umass_mod,
#endif
#ifdef LOSCFG_DRIVERS_USB_HOST_DRIVER
	&debug_controller_mod,
	&debug_uhub_mod,
	&debug_process_mod,
#endif
	&debug_other_mod,
	NULL
};

void
usb_debug_module_regsiter(void)
{
	uint32_t i;
	struct debug_module_data* mod;
	for (i = 0; (mod = debug_mode_list[i]) && (mod != NULL); i++) {
		debug_module_register(mod);
	}
}

void
usb_debug_module_unregsiter(void)
{
	uint32_t i;
	struct debug_module_data* mod;
	for (i = 0; (mod = debug_mode_list[i]) && (mod != NULL); i++) {
		debug_module_unregister(mod);
	}
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
void
usb_debug_shell_cmd(uint32_t argc, char **argv)
{
	uint32_t level = 0;
	char *str;
	struct debug_module_data* mod;

	if (argc != 2) {
		PRINTK("Usage: usb_debug module level\n");
		PRINTK("Modules:\n");
		debug_module_dump();
		return;
	}

	str = argv[0];
	level = strtoul(argv[1], 0, 0);

	mod = get_debug_module(str);
	if (mod == NULL) {
		PRINTK("The module is not supported!\n");
		return;
	}

	if (mod->callback)
		mod->callback(level);
}

SHELLCMD_ENTRY(usb_debug_shellcmd, CMD_TYPE_EX, "usb_debug", 0, (CmdCallBackFunc)usb_debug_shell_cmd);
#endif
#endif
