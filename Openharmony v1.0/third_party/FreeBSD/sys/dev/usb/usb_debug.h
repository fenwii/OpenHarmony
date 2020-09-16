/* $FreeBSD: releng/11.4/sys/dev/usb/usb_debug.h 331722 2018-03-29 02:50:57Z eadler $ */
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

/* This file contains various factored out debug macros. */

#ifndef _USB_DEBUG_H_
#define	_USB_DEBUG_H_

/* Declare global USB debug variable. */
extern int usb_debug;

/* Check if USB debugging is enabled. */
#ifdef USB_DEBUG_VAR
#ifdef LOSCFG_USB_DEBUG
#define	DPRINTFN(n,fmt,...) do {		\
  if ((USB_DEBUG_VAR) >= (n)) {			\
    PRINTK("%s: " fmt,				\
	   __FUNCTION__ ,##__VA_ARGS__);	\
  }						\
} while (0)
#define	DPRINTF(...)	DPRINTFN(1, __VA_ARGS__)
#else
#define	DPRINTF(...) do { } while (0)
#define	DPRINTFN(...) do { } while (0)
#endif
/* usb_debug shell command supports the following modules print level control */
/*
 * 	composite,	about composite.c
 * 	dwc_pcd,	about dwc_otg_pcd.c
 * 	dwc_intr,	about dwc_ptg_pcd_intr.c
 * 	ehci,		about ehci.c
 * 	fmass,		about f_mass_storage.c
 * 	axe,		about if_axe.c
 * 	cdce,		about if_cdce.c
 * 	urndis,		about if_urndis.c
 * 	u3g,		about u3g.c
 * 	umass,		about umass.c
 * 	controller,	about usb_controller.c
 * 	uhub,		about usb_hub.c
 * 	process,	about usb_process.c
 * 	serial,		about usb_serial.c
 * 	other,		about bsd_kernel.c/linux_usb.c/usb_device.c/usb_request.c/usb_transfer.c
 */

/* For example: usb_debug modules level */
#endif

struct usb_interface;
struct usb_device;
struct usb_endpoint;
struct usb_xfer;

void usb_dump_iface(struct usb_interface *iface);
void usb_dump_device(struct usb_device *udev);
void usb_dump_queue(struct usb_endpoint *ep);
void usb_dump_endpoint(struct usb_endpoint *ep);
void usb_dump_xfer(struct usb_xfer *xfer);

#ifdef LOSCFG_USB_DEBUG
extern unsigned int usb_port_reset_delay;
extern unsigned int usb_port_root_reset_delay;
extern unsigned int usb_port_reset_recovery;
extern unsigned int usb_port_powerup_delay;
extern unsigned int usb_port_resume_delay;
extern unsigned int usb_set_address_settle;
extern unsigned int usb_resume_delay;
extern unsigned int usb_resume_wait;
extern unsigned int usb_resume_recovery;
extern unsigned int usb_extra_power_up_time;
#else
#define usb_port_reset_delay		USB_PORT_RESET_DELAY
#define usb_port_root_reset_delay	USB_PORT_ROOT_RESET_DELAY
#define usb_port_reset_recovery		USB_PORT_RESET_RECOVERY
#define usb_port_powerup_delay		USB_PORT_POWERUP_DELAY
#define usb_port_resume_delay		USB_PORT_RESUME_DELAY
#define usb_set_address_settle		USB_SET_ADDRESS_SETTLE
#define usb_resume_delay		USB_RESUME_DELAY
#define usb_resume_wait			USB_RESUME_WAIT
#define usb_resume_recovery		USB_RESUME_RECOVERY
#define usb_extra_power_up_time		USB_EXTRA_POWER_UP_TIME
#endif

#endif					/* _USB_DEBUG_H_ */
