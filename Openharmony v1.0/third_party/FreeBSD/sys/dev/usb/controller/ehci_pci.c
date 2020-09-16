/*-
 * Copyright (c) 1998 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Lennart Augustsson (augustss@carlstedt.se) at
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

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/11.4/sys/dev/usb/controller/ehci_pci.c 358017 2020-02-17 09:57:40Z hselasky $");

/*
 * USB Enhanced Host Controller Driver, a.k.a. USB 2.0 controller.
 *
 * The EHCI 1.0 spec can be found at
 * http://developer.intel.com/technology/usb/download/ehci-r10.pdf
 * and the USB 2.0 spec at
 * http://www.usb.org/developers/docs/usb_20.zip
 */

/* The low level controller code for EHCI has been split into
 * PCI probes and EHCI specific code. This was done to facilitate the
 * sharing of code between *BSD's
 */

#include "implementation/global_implementation.h"
#include "controller/ehci.h"
#include "controller/ehcireg.h"

static device_probe_t ehci_pci_probe;
static device_attach_t ehci_pci_attach;
static device_detach_t ehci_pci_detach;
static usb_take_controller_t ehci_pci_take_controller;

static void
hiehci_post_reset(struct ehci_softc *sc)
{
	uint32_t usb_mode;

	/* Force HOST mode */
	usb_mode = EOREAD4(sc, EHCI_USBMODE_NOLPM);
	usb_mode &= ~EHCI_UM_CM;
	usb_mode |= EHCI_UM_CM_HOST;
	EOWRITE4(sc, EHCI_USBMODE_NOLPM, usb_mode);
}

static const char *
ehci_pci_match(device_t self)
{
	return ("EHCI (generic) USB 2.0 controller");
}

static int
ehci_pci_probe(device_t self)
{
	const char *desc = ehci_pci_match(self);

	if (desc) {
		device_set_desc(self, desc);
		return (BUS_PROBE_DEFAULT);
	} else {
		return (ENXIO);
	}
}

static int
ehci_pci_attach(device_t self)
{
	struct resource *res;
	ehci_softc_t *sc = device_get_softc(self);
	int err = ENXIO;

	/* initialise some bus fields */
	sc->sc_bus.parent = self;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = EHCI_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;
	sc->sc_bus.dma_parent_tag[0].dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_bus,
	    USB_GET_DMA_TAG(dev), &ehci_iterate_hw_softc)) {
		err = ENOMEM;
		goto error0;
	}

	res = bus_alloc_resource_any(self, SYS_RES_MEMORY, &unit, 0);
	if (res == NULL) {
		goto error;
	}

	sc->sc_io_res = ioremap(res->start, res->count);
	if (!sc->sc_io_res) {
		goto error1;
	}

	sc->sc_io_tag = (void *)sc->sc_io_res;
	sc->sc_io_hdl = (bus_space_handle_t)sc->sc_io_res;
	sc->sc_io_size = res->count;

	sc->sc_flags |= EHCI_SCFLG_DONTRESET;

	/* Setup callbacks. */
	sc->sc_vendor_post_reset = hiehci_post_reset;
	sc->sc_vendor_get_port_speed = ehci_get_port_speed_portsc;

	sc->sc_bus.bdev = device_add_child(self, "usbus", -1);
	if (!sc->sc_bus.bdev) {
		device_printf(self, "Could not add USB device\n");
		goto error1;
	}
	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);

	/*
	 * ehci_pci_match will never return NULL if ehci_pci_probe
	 * succeeded
	 */
	device_set_desc(sc->sc_bus.bdev, ehci_pci_match(self));

	res = bus_alloc_resource_any(self, SYS_RES_IRQ, &unit, 0);
	if (res == NULL) {
		goto error;
	}
	sc->sc_irq_res = res;
	err = bus_setup_intr(res->start, 0, ehci_interrupt, sc);
	if (err) {
		goto error2;
	}

	ehci_pci_take_controller(self);

	hiusb_start_hcd();
	hiusb_device2host();

	err = ehci_init(sc);
	if (!err) {
		err = device_probe_and_attach(sc->sc_bus.bdev);
	}
	if (err) {
		device_printf(self, "ehci init failed err=%d\n", err);
		goto error;
	}

	return (0);

error:
	device_printf(self, "ehci attach failed err=%d\n", err);
	(void)ehci_pci_detach(self);
	return (err);
error2:
	if (sc->sc_io_res != NULL) {
		iounmap((void *)sc->sc_io_res);
		sc->sc_io_res = NULL;
	}
error1:
	(void)bus_teardown_intr(NUM_HAL_INTERRUPT_USB_EHCI, sc);
error0:
	usb_bus_mem_free_all(&sc->sc_bus, &ehci_iterate_hw_softc);
	device_printf(self, "ehci attach failed err=%d\n", err);
	return (err);
}

static int
ehci_pci_detach(device_t self)
{
	ehci_softc_t *sc = device_get_softc(self);

	/* during module unload there are lots of children leftover */
	(void)device_delete_children(dev);

	ehci_detach(sc);
	hiusb_stop_hcd();

	if (sc->sc_irq_res != NULL) {
		(void)bus_teardown_intr(sc->sc_irq_res->start, sc);
		sc->sc_irq_res = NULL;
	}
	if (sc->sc_io_res != NULL) {
		iounmap((void *)sc->sc_io_res);
		sc->sc_io_res = NULL;
		sc->sc_io_tag = NULL;
		sc->sc_io_hdl = (uintptr_t)NULL;
		sc->sc_io_size = 0;
	}
	usb_bus_mem_free_all(&sc->sc_bus, &ehci_iterate_hw_softc);

	return (0);
}

static int
ehci_pci_take_controller(device_t self)
{
	return (0);
}

static device_method_t ehci_pci_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe, ehci_pci_probe),
	DEVMETHOD(device_attach, ehci_pci_attach),
	DEVMETHOD(device_detach, ehci_pci_detach),
	DEVMETHOD(device_suspend, bus_generic_suspend),
	DEVMETHOD(device_resume, bus_generic_resume),
	DEVMETHOD(device_shutdown, bus_generic_shutdown),
	DEVMETHOD(usb_take_controller, ehci_pci_take_controller),

	DEVMETHOD_END
};

static driver_t ehci_driver = {
	.name = "ehci",
	.methods = ehci_pci_methods,
	.size = sizeof(struct ehci_softc),
};

static devclass_t ehci_devclass;

DRIVER_MODULE(ehci, nexus, ehci_driver, ehci_devclass, 0, 0);

int
hiehci_init(void)
{
	DPRINTF("hiehci_init");
	return driver_module_handler(NULL, MOD_LOAD, &ehci_nexus_driver_mod);
}

void
hiehci_exit(void)
{
	DPRINTF("hiehci_exit");
	(void)driver_module_handler(NULL, MOD_UNLOAD, &ehci_nexus_driver_mod);
}
