/*-
 * Copyright (c) 2010 Hans Petter Selasky. All rights reserved.
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
#include "controller/xhci.h"
#include "controller/xhcireg.h"

extern void *ioremap(unsigned long phys_addr, unsigned int size);
extern void iounmap(void *addr);

static device_probe_t xhci_pci_probe;
static device_attach_t xhci_pci_attach;
static device_detach_t xhci_pci_detach;
static usb_take_controller_t xhci_pci_take_controller;

static device_method_t xhci_device_methods[] = {
        /* device interface */
        DEVMETHOD(device_probe, xhci_pci_probe),
        DEVMETHOD(device_attach, xhci_pci_attach),
        DEVMETHOD(device_detach, xhci_pci_detach),
        DEVMETHOD(device_suspend, bus_generic_suspend),
        DEVMETHOD(device_resume, bus_generic_resume),
        DEVMETHOD(device_shutdown, bus_generic_shutdown),
        DEVMETHOD(usb_take_controller, xhci_pci_take_controller),

        DEVMETHOD_END
};

static driver_t xhci_driver = {
        .name = "xhci",
        .methods = xhci_device_methods,
        .size = sizeof(struct xhci_softc),
};

static devclass_t xhci_devclass;

DRIVER_MODULE(xhci, nexus, xhci_driver, xhci_devclass, NULL, NULL);

static const char *
xhci_pci_match(device_t self)
{
	(void)self;
	return ("XHCI (generic) USB 3.0 controller");
}

static int
xhci_pci_probe(device_t self)
{
	const char *desc = xhci_pci_match(self);

	if (desc) {
		device_set_desc(self, desc);
		return (BUS_PROBE_DEFAULT);
	} else {
		return (ENXIO);
	}
}

static int
xhci_pci_attach(device_t self)
{
	struct resource *res;
	struct xhci_softc *sc = device_get_softc(self);;
	int err = ENXIO;
	uint8_t usedma32 = 0;
	int unit = device_get_unit(self);

	usb_debug("+\n");

	res = bus_alloc_resource_any(self, SYS_RES_MEMORY, &unit, 0);
	if (res == NULL) {
		goto error;
	}

	sc->sc_io_res = ioremap(res->start, res->count);
	if (!sc->sc_io_res) {
		goto error;
	}
	sc->sc_io_tag = (void *)sc->sc_io_res;
	sc->sc_io_hdl = (uintptr_t)sc->sc_io_res;
	sc->sc_io_size = res->count;
	usb_debug("bus_setup_intr\n");

	res = bus_alloc_resource_any(self, SYS_RES_IRQ, &unit, 0);
	if (res == NULL) {
		goto error;
	}

	sc->sc_irq_res = res;
	err = bus_setup_intr(res->start, 0, (driver_intr_t *)xhci_interrupt, sc);
	if (err) {
		goto error;
	}

	usb_debug("xhci_init\n");
	HiUsb3StartHcd();
	if (xhci_init(sc, self, usedma32)) {
		device_printf(self, "Could not initialize softc\n");
		goto error;
	}
	callout_init_mtx(&sc->sc_callout, &sc->sc_bus.bus_mtx, 0);

	usb_debug("add child to usbus\n");
	sc->sc_bus.bdev = device_add_child(self, "usbus", -1);
	if (sc->sc_bus.bdev == NULL) {
		device_printf(self, "Could not add USB device\n");
		goto error;
	}
	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);

	usb_debug("xhci halt and start controller\n");
	err = xhci_halt_controller(sc);

	if (err == 0)
		err = xhci_start_controller(sc);

	usb_debug("device_probe_and_attach bus_dev\n");
	if (err == 0)
		err = device_probe_and_attach(sc->sc_bus.bdev);

	if (err) {
		device_printf(self, "XHCI halt/start/probe failed err=%d\n", err);
		goto error;
	}

	usb_debug("-\n");

	return (0);
error:
	device_printf(self, "XHCI halt/start/probe failed err=%d\n", err);
	if (sc) {
		iounmap((void *)sc->sc_io_res);
	}
	(void)xhci_pci_detach(self);
	return (err);
}

static int
xhci_pci_detach(device_t self)
{

	struct xhci_softc *sc = device_get_softc(self);

	/* during module unload there are lots of children leftover */
	(void)device_delete_children(self);

	callout_drain(&sc->sc_callout);
	(void)xhci_halt_controller(sc);
	(void)xhci_reset_controller(sc);

	// release resouce
	if (sc->sc_irq_res) {
		(void)bus_teardown_intr(sc->sc_irq_res->start, sc);
		sc->sc_irq_res = NULL;
	}
	if (sc->sc_io_res) {
		iounmap((void *)sc->sc_io_res);
		sc->sc_io_res = NULL;
		sc->sc_io_tag = NULL;
		sc->sc_io_hdl = (uintptr_t)NULL;
		sc->sc_io_size = 0;
	}

	xhci_uninit(sc);

	return (0);
}

static int
xhci_pci_take_controller(device_t self)
{
	struct xhci_softc *sc = device_get_softc(self);
	uint32_t cparams;
	uint32_t eecp;
	uint32_t eec;
	uint16_t to;
	uint8_t bios_sem;

	cparams = XREAD4(sc, capa, XHCI_HCSPARAMS0);

	eec = (uint32_t)(-1);

	/* Synchronise with the BIOS if it owns the controller. */
	for (eecp = XHCI_HCS0_XECP(cparams) << 2; (eecp != 0) && XHCI_XECP_NEXT(eec);
	    eecp += (XHCI_XECP_NEXT(eec) << 2)) {
		eec = XREAD4(sc, capa, eecp);

		if (XHCI_XECP_ID(eec) != XHCI_ID_USB_LEGACY)
			continue;
		bios_sem = XREAD1(sc, capa, eecp +
		    XHCI_XECP_BIOS_SEM);
		if (bios_sem == 0)
			continue;
		device_printf(sc->sc_bus.bdev, "waiting for BIOS "
		    "to give up control\n");
		XWRITE1(sc, capa, eecp +
		    XHCI_XECP_OS_SEM, 1);
		to = 500;
		while (1) {
			bios_sem = XREAD1(sc, capa, eecp +
			    XHCI_XECP_BIOS_SEM);
			if (bios_sem == 0)
				break;

			if (--to == 0) {
				device_printf(sc->sc_bus.bdev,
				    "timed out waiting for BIOS\n");
				break;
			}
			usb_pause_mtx(NULL, hz / 100);	/* wait 10ms */
		}
	}
	return (0);
}

int
hixhci_init(void)
{
	DPRINTF("hixhci_init");
	return driver_module_handler(NULL, MOD_LOAD, &xhci_nexus_driver_mod);
}

void
hixhci_exit(void)
{
	DPRINTF("hixhci_exit");
	(void)driver_module_handler(NULL, MOD_UNLOAD, &xhci_nexus_driver_mod);
}
