/*-
 * Copyright 1998 Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby
 * granted, provided that both the above copyright notice and this
 * permission notice appear in all copies, that both the above
 * copyright notice and this permission notice appear in all
 * supporting documentation, and that the name of M.I.T. not be used
 * in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.  M.I.T. makes
 * no representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied
 * warranty.
 *
 * THIS SOFTWARE IS PROVIDED BY M.I.T. ``AS IS''.  M.I.T. DISCLAIMS
 * ALL EXPRESS OR IMPLIED WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT
 * SHALL M.I.T. BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/*
 * This code implements a `root nexus' for Arm Architecture
 * machines.  The function of the root nexus is to serve as an
 * attachment point for both processors and buses, and to manage
 * resources which are common to all of them.  In particular,
 * this code implements the core resource managers for interrupt
 * requests, DMA requests (which rightfully should be a part of the
 * ISA code but it's easier to do it here for now), I/O port addresses,
 * and I/O memory address space.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/11.4/sys/arm/arm/nexus.c 308382 2016-11-06 18:40:12Z gonzo $");

#include <sys/kobj.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include "device_if.h"
#include "bus_if.h"
#include <sys/malloc.h>
#include <sys/module.h>
#ifdef LOSCFG_DRIVERS_HDF_USB
#include "hdf_usb.h"
#endif

struct devclass_res {
	TAILQ_ENTRY(devclass_res) link;
	struct resource_list    nx_resources;
	char* devclass_name;
};
TAILQ_HEAD(devclass_res_list, devclass_res);
static struct devclass_res_list devclass_resources;

static	int nexus_probe(device_t);
static	int nexus_attach(device_t);
static	int nexus_print_child(device_t, device_t);
static	struct resource *nexus_alloc_resource(device_t, device_t, int, int *,
    rman_res_t, rman_res_t, rman_res_t, u_int);

static device_method_t nexus_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe,		nexus_probe),
	DEVMETHOD(device_attach,	nexus_attach),
	/* Bus interface */
	DEVMETHOD(bus_print_child,	nexus_print_child),
	DEVMETHOD(bus_add_child,	bus_generic_add_child),
	DEVMETHOD(bus_alloc_resource,	nexus_alloc_resource),

	{ 0, 0 }
};

static devclass_t nexus_devclass;
static driver_t nexus_driver = {
	"nexus",
	nexus_methods,
	1			/* no softc */
};
EARLY_DRIVER_MODULE(nexus, root, nexus_driver, nexus_devclass, 0, 0,
    BUS_PASS_BUS + BUS_PASS_ORDER_EARLY);

static struct resource_list *get_resource_list(const char *devclass_name)
{
	struct devclass_res *dr = NULL;
	if (devclass_name == NULL) {
		return (NULL);
	}
	TAILQ_FOREACH(dr, &devclass_resources, link) {
		if (!strcmp(dr->devclass_name, devclass_name)) {
			break;
		}
	}
	if (dr == NULL) {
		dr = malloc(sizeof(struct devclass_res) + strlen(devclass_name) + 1);
		if (dr == NULL) {
			return (NULL);
		}
		dr->devclass_name = (char *)(dr + 1);
		(void)strcpy_s(dr->devclass_name, strlen(devclass_name) + 1, devclass_name);
		resource_list_init(&dr->nx_resources);
		TAILQ_INSERT_TAIL(&devclass_resources, dr, link);
	}
	return (&dr->nx_resources);
}

static void add_resource(const char *devclass_name, int type, int unit, rman_res_t start, rman_res_t end,
	rman_res_t count)
{
	struct resource_list *res_list = get_resource_list(devclass_name);
	if (res_list == NULL) {
		return;
	}
	resource_list_add(res_list, type, unit, start, end, count);
}

int
nexus_init(void)
{
	TAILQ_INIT(&devclass_resources);
#ifdef LOSCFG_DRIVERS_HDF_USB
	UsbResourceInit(nexus, add_resource);
#endif
	machine_resource_init(add_resource);

	return driver_module_handler(NULL, MOD_LOAD, &nexus_root_driver_mod);
}

static int
nexus_probe(device_t dev)
{
	device_quiet(dev);	/* suppress attach message for neatness */

	return (BUS_PROBE_DEFAULT);
}

static int
nexus_attach(device_t dev)
{
	/*
	 * First, deal with the children we know about already
	 */
	bus_generic_probe(dev);
	bus_generic_attach(dev);

	return (0);
}

static int
nexus_print_child(device_t bus, device_t child)
{
	int retval = 0;

	retval += bus_print_child_header(bus, child);
	retval += printf("\n");

	return (retval);
}

/*
 * Allocate a resource on behalf of child.  NB: child is usually going to be a
 * child of one of our descendants, not a direct child of nexus0.
 * (Exceptions include footbridge.)
 */
static struct resource *
nexus_alloc_resource(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	devclass_t dc = device_get_devclass(child);
	struct resource_list *res_list = NULL;
	if (dc == NULL || rid == NULL) {
		return (NULL);
	}
	res_list = get_resource_list(devclass_get_name(dc));
	if (res_list == NULL) {
		return (NULL);
	}
	struct resource_list_entry *rle = resource_list_find(res_list, type, *rid);
	if (rle == NULL) {
		return(NULL);
	}
	return (rle->res);
}
