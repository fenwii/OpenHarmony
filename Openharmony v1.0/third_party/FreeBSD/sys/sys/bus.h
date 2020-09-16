/*-
 * Copyright (c) 1997,1998,2003 Doug Rabson
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
 *
 * $FreeBSD: releng/11.4/sys/sys/bus.h 350034 2019-07-16 15:28:41Z avg $
 */

#ifndef _SYS_BUS_H_
#define _SYS_BUS_H_

#include <limits.h>
#include <sys/types.h>
#include <arm/include/_bus.h>
#include <sys/module.h>
#include <sys/queue.h>
#include <los_hwi.h>

typedef struct device   *device_t;

typedef uint32_t   u_int32_t;

/**
 * @brief State of the device.
 */
typedef enum device_state {
	DS_NOTPRESENT = 10,             /**< @brief not probed or probe failed */
	DS_ALIVE = 20,                  /**< @brief probe succeeded */
	DS_ATTACHING = 25,              /**< @brief currently attaching */
	DS_ATTACHED = 30,               /**< @brief attach method called */
	DS_BUSY = 40                    /**< @brief device is open */
} device_state_t;

/**
 *  * @brief Device information exported to userspace.
 *   */
struct u_device {
	uintptr_t       dv_handle;
	uintptr_t       dv_parent;

	char            dv_name[32];            /**< @brief Name of device in tree. */
	char            dv_desc[32];            /**< @brief Driver description */
	char            dv_drivername[32];      /**< @brief Driver name */
	char            dv_pnpinfo[128];        /**< @brief Plug and play info */
	char            dv_location[128];       /**< @brief Where is the device? */
	uint32_t        dv_devflags;            /**< @brief API Flags for device */
	uint16_t        dv_flags;               /**< @brief flags for dev state */
	device_state_t  dv_state;               /**< @brief State of attachment */
	/* XXX more driver info? */
};

/* Flags exported via dv_flags. */
#define DF_ENABLED      0x01            /* device should be probed/attached */
#define DF_FIXEDCLASS   0x02            /* devclass specified at create time */
#define DF_WILDCARD     0x04            /* unit was originally wildcard */
#define DF_DESCMALLOCED 0x08            /* description was malloced */
#define DF_QUIET        0x10            /* don't print verbose attach message */
#define DF_DONENOMATCH  0x20            /* don't execute DEVICE_NOMATCH again */
#define DF_EXTERNALSOFTC 0x40           /* softc not allocated by us */
#define DF_REBID        0x80            /* Can rebid after attach */
#define DF_SUSPENDED    0x100           /* Device is suspended. */

#define	SYS_RES_IRQ	1	/* interrupt lines */
#define	SYS_RES_DRQ	2	/* isa dma lines */
#define	SYS_RES_MEMORY	3	/* i/o memory */
#define	SYS_RES_IOPORT	4	/* i/o ports */

#include <sys/kobj.h>

/**
 * @brief A device driver (included mainly for compatibility with
 * FreeBSD 4.x).
 */
typedef struct kobj_class	driver_t;

/**
 * @brief A device class
 *
 * The devclass object has two main functions in the system. The first
 * is to manage the allocation of unit numbers for device instances
 * and the second is to hold the list of device drivers for a
 * particular bus type. Each devclass has a name and there cannot be
 * two devclasses with the same name. This ensures that unique unit
 * numbers are allocated to device instances.
 *
 * Drivers that support several different bus attachments (e.g. isa,
 * pci, pccard) should all use the same devclass to ensure that unit
 * numbers do not conflict.
 *
 * Each devclass may also have a parent devclass. This is used when
 * searching for device drivers to allow a form of inheritance. When
 * matching drivers with devices, first the driver list of the parent
 * device's devclass is searched. If no driver is found in that list,
 * the search continues in the parent devclass (if any).
 */
typedef struct devclass		*devclass_t;

/**
 * @brief A device method
 */
#define device_method_t		kobj_method_t

/**
 * @brief Driver interrupt filter return values
 *
 * If a driver provides an interrupt filter routine it must return an
 * integer consisting of oring together zero or more of the following
 * flags:
 *
 *      FILTER_STRAY    - this device did not trigger the interrupt
 *      FILTER_HANDLED  - the interrupt has been fully handled and can be EOId
 *      FILTER_SCHEDULE_THREAD - the threaded interrupt handler should be
 *                        scheduled to execute
 *
 * If the driver does not provide a filter, then the interrupt code will
 * act is if the filter had returned FILTER_SCHEDULE_THREAD.  Note that it
 * is illegal to specify any other flag with FILTER_STRAY and that it is
 * illegal to not specify either of FILTER_HANDLED or FILTER_SCHEDULE_THREAD
 * if FILTER_STRAY is not specified.
 */
#define FILTER_STRAY            0x01
#define FILTER_HANDLED          0x02
#define FILTER_SCHEDULE_THREAD  0x04

/**
 * @brief Driver interrupt service routines
 *
 * The filter routine is run in primary interrupt context and may not
 * block or use regular mutexes.  It may only use spin mutexes for
 * synchronization.  The filter may either completely handle the
 * interrupt or it may perform some of the work and defer more
 * expensive work to the regular interrupt handler.  If a filter
 * routine is not registered by the driver, then the regular interrupt
 * handler is always used to handle interrupts from this device.
 *
 * The regular interrupt handler executes in its own thread context
 * and may use regular mutexes.  However, it is prohibited from
 * sleeping on a sleep queue.
 */
typedef int driver_filter_t(void*);
typedef void driver_intr_t(int, void*);

/**
 * @brief This structure is deprecated.
 *
 * Use the kobj(9) macro DEFINE_CLASS to
 * declare classes which implement device drivers.
 */
struct driver {
	KOBJ_CLASS_FIELDS;
};


typedef   uint64_t      rman_res_t;
/*
 * Definitions for drivers which need to keep simple lists of resources
 * for their child devices.
 */
/*
 * The public (kernel) view of struct resource
 *
 * NB: Changing the offset/size/type of existing fields in struct resource
 * NB: breaks the device driver ABI and is strongly FORBIDDEN.
 * NB: Appending new fields is probably just misguided.
 */

struct resource {
	rman_res_t	start;		/**< @brief start of resource range */
	rman_res_t	end;		/**< @brief end of resource range */
	rman_res_t	count;			/**< @brief count within range */
};

/**
 * @brief An entry for a single resource in a resource list.
 */
struct resource_list_entry {
	STAILQ_ENTRY(resource_list_entry) link;
	int	type;			/**< @brief type argument to alloc_resource */
	int	rid;			/**< @brief resource identifier */
	int	flags;			/**< @brief resource flags */
	struct	resource *res;		/**< @brief the real resource when allocated */
};
STAILQ_HEAD(resource_list, resource_list_entry);

#define	RLE_RESERVED		0x0001	/* Reserved by the parent bus. */
#define	RLE_ALLOCATED		0x0002	/* Reserved resource is allocated. */
#define	RLE_PREFETCH		0x0004	/* Resource is a prefetch range. */

void	resource_list_init(struct resource_list *rl);
void	resource_list_free(struct resource_list *rl);
struct resource_list_entry *
	resource_list_add(struct resource_list *rl,
			  int type, int rid,
			  rman_res_t start, rman_res_t end, rman_res_t count);
struct resource_list_entry*
	resource_list_find(struct resource_list *rl,
			   int type, int rid);

typedef void (*add_res_callback_t)(const char *devclass_name, int type, int unit, rman_res_t start, rman_res_t end,
	rman_res_t count);
void machine_resource_init(add_res_callback_t callback);

/*
 * The root bus, to which all top-level busses are attached.
 */
extern device_t root_bus;
extern devclass_t root_devclass;
void    root_bus_configure(void);

extern device_t nexus;

/*
 * Useful functions for implementing busses.
 */
int     bus_generic_attach(device_t dev);

device_t
        bus_generic_add_child(device_t dev, u_int order, const char *name,
                              int unit);
int     bus_generic_child_present(device_t dev, device_t child);

int     bus_generic_detach(device_t dev);
void    bus_generic_driver_added(device_t dev, driver_t *driver);
int     bus_generic_get_domain(device_t dev, device_t child, int *domain);

void    bus_generic_new_pass(device_t dev);
int     bus_print_child_header(device_t dev, device_t child);
int     bus_print_child_domain(device_t dev, device_t child);
int     bus_print_child_footer(device_t dev, device_t child);
int     bus_generic_print_child(device_t dev, device_t child);
int     bus_generic_probe(device_t dev);
int     bus_generic_read_ivar(device_t dev, device_t child, int which,
                              uintptr_t *result);
int     bus_generic_resume(device_t dev);
int     bus_generic_resume_child(device_t dev, device_t child);

int     bus_generic_shutdown(device_t dev);
int     bus_generic_suspend(device_t dev);
int     bus_generic_suspend_child(device_t dev, device_t child);

int     bus_generic_write_ivar(device_t dev, device_t child, int which,
                               uintptr_t value);
int     bus_helper_reset_post(device_t dev, int flags);
int     bus_helper_reset_prepare(device_t dev, int flags);
int     bus_null_rescan(device_t dev);

struct	resource *bus_alloc_resource(device_t dev, int type, int *rid,
				     rman_res_t start, rman_res_t end,
				     rman_res_t count, u_int flags);
int     bus_generic_resume(device_t dev);
int     bus_generic_resume_child(device_t dev, device_t child);

int   bus_child_location_str(device_t child, char *buf, size_t buflen);

static __inline struct resource *
bus_alloc_resource_any(device_t dev, int type, int *rid, u_int flags)
{
	return (bus_alloc_resource(dev, type, rid, 0, ~0, 1, flags));
}

/*
 * Access functions for device.
 */
device_t	device_add_child(device_t dev, const char *name, int unit);
device_t	device_add_child_ordered(device_t dev, u_int order,
					 const char *name, int unit);
void	device_busy(device_t dev);
int	device_delete_child(device_t dev, device_t child);
int	device_delete_children(device_t dev);
int	device_attach(device_t dev);
int	device_detach(device_t dev);
void	device_disable(device_t dev);
void	device_enable(device_t dev);
device_t	device_find_child(device_t dev, const char *classname,
				  int unit);
const char	*device_get_desc(device_t dev);
devclass_t	device_get_devclass(device_t dev);
driver_t	*device_get_driver(device_t dev);
u_int32_t	device_get_flags(device_t dev);
device_t	device_get_parent(device_t dev);
int	device_get_children(device_t dev, device_t **listp, int *countp);
void	*device_get_ivars(device_t dev);
void	device_set_ivars(device_t dev, void *ivars);
const	char *device_get_name(device_t dev);
const	char *device_get_nameunit(device_t dev);
void	*device_get_softc(device_t dev);
device_state_t	device_get_state(device_t dev);
int	device_get_unit(device_t dev);
struct sysctl_ctx_list *device_get_sysctl_ctx(device_t dev);
struct sysctl_oid *device_get_sysctl_tree(device_t dev);
int	device_is_alive(device_t dev);	/* did probe succeed? */
int	device_is_attached(device_t dev);	/* did attach succeed? */
int	device_is_enabled(device_t dev);
int	device_is_suspended(device_t dev);
int	device_is_quiet(device_t dev);
device_t device_lookup_by_name(const char *name);
int	device_print_prettyname(device_t dev);
int	device_printf(device_t dev, const char *, ...) __printflike(2, 3);
int	device_probe(device_t dev);
int	device_probe_and_attach(device_t dev);
int	device_probe_child(device_t bus, device_t dev);
int	device_quiesce(device_t dev);
void	device_quiet(device_t dev);
void	device_set_desc(device_t dev, const char* desc);
void	device_set_desc_copy(device_t dev, const char* desc);
int	device_set_devclass(device_t dev, const char *classname);
int	device_set_devclass_fixed(device_t dev, const char *classname);
int	device_set_driver(device_t dev, driver_t *driver);
void	device_set_flags(device_t dev, u_int32_t flags);
void	device_set_softc(device_t dev, void *softc);
void	device_free_softc(void *softc);
void	device_claim_softc(device_t dev);
int	device_set_unit(device_t dev, int unit);	/* XXX DONT USE XXX */
int	device_shutdown(device_t dev);
void	device_unbusy(device_t dev);
void	device_verbose(device_t dev);

/* port for interrupt setup and teardown */
int bus_setup_intr(int irq, int flags, driver_intr_t *intr, void *arg);
int bus_teardown_intr(int irq, void *arg);

/*
 * Access functions for devclass.
 */
int		devclass_add_driver(devclass_t dc, driver_t *driver,
				    int pass, devclass_t *dcp);
devclass_t	devclass_create(const char *classname);
int		devclass_delete_driver(devclass_t busclass, driver_t *driver);
devclass_t	devclass_find(const char *classname);
const char	*devclass_get_name(devclass_t dc);
device_t	devclass_get_device(devclass_t dc, int unit);
void	*devclass_get_softc(devclass_t dc, int unit);
int	devclass_get_devices(devclass_t dc, device_t **listp, int *countp);
int	devclass_get_drivers(devclass_t dc, driver_t ***listp, int *countp);
int	devclass_get_count(devclass_t dc);
int	devclass_get_maxunit(devclass_t dc);
int	devclass_find_free_unit(devclass_t dc, int unit);
void	devclass_set_parent(devclass_t dc, devclass_t pdc);
devclass_t	devclass_get_parent(devclass_t dc);

/*
 * Functions for maintaining and checking consistency of
 * bus information exported to userspace.
 */
int     bus_data_generation_check(int generation);
void    bus_data_generation_update(void);

/**
 * Some convenience defines for probe routines to return.  These are just
 * suggested values, and there's nothing magical about them.
 * BUS_PROBE_SPECIFIC is for devices that cannot be reprobed, and that no
 * possible other driver may exist (typically legacy drivers who don't fallow
 * all the rules, or special needs drivers).  BUS_PROBE_VENDOR is the
 * suggested value that vendor supplied drivers use.  This is for source or
 * binary drivers that are not yet integrated into the FreeBSD tree.  Its use
 * in the base OS is prohibited.  BUS_PROBE_DEFAULT is the normal return value
 * for drivers to use.  It is intended that nearly all of the drivers in the
 * tree should return this value.  BUS_PROBE_LOW_PRIORITY are for drivers that
 * have special requirements like when there are two drivers that support
 * overlapping series of hardware devices.  In this case the one that supports
 * the older part of the line would return this value, while the one that
 * supports the newer ones would return BUS_PROBE_DEFAULT.  BUS_PROBE_GENERIC
 * is for drivers that wish to have a generic form and a specialized form,
 * like is done with the pci bus and the acpi pci bus.  BUS_PROBE_HOOVER is
 * for those busses that implement a generic device place-holder for devices on
 * the bus that have no more specific driver for them (aka ugen).
 * BUS_PROBE_NOWILDCARD or lower means that the device isn't really bidding
 * for a device node, but accepts only devices that its parent has told it
 * use this driver.
 */
#define BUS_PROBE_SPECIFIC	0	/* Only I can use this device */
#define BUS_PROBE_VENDOR	(-10)	/* Vendor supplied driver */
#define BUS_PROBE_DEFAULT	(-20)	/* Base OS default driver */
#define BUS_PROBE_LOW_PRIORITY	(-40)	/* Older, less desirable drivers */
#define BUS_PROBE_GENERIC	(-100)	/* generic driver for dev */
#define BUS_PROBE_HOOVER	(-1000000) /* Driver for any dev on bus */
#define BUS_PROBE_NOWILDCARD	(-2000000000) /* No wildcard device matches */

/**
 * During boot, the device tree is scanned multiple times.  Each scan,
 * or pass, drivers may be attached to devices.  Each driver
 * attachment is assigned a pass number.  Drivers may only probe and
 * attach to devices if their pass number is less than or equal to the
 * current system-wide pass number.  The default pass is the last pass
 * and is used by most drivers.  Drivers needed by the scheduler are
 * probed in earlier passes.
 */
#define	BUS_PASS_ROOT		0	/* Used to attach root0. */
#define	BUS_PASS_BUS		10	/* Busses and bridges. */
#define	BUS_PASS_CPU		20	/* CPU devices. */
#define	BUS_PASS_RESOURCE	30	/* Resource discovery. */
#define	BUS_PASS_INTERRUPT	40	/* Interrupt controllers. */
#define	BUS_PASS_TIMER		50	/* Timers and clocks. */
#define	BUS_PASS_SCHEDULER	60	/* Start scheduler. */
#define	BUS_PASS_DEFAULT	INT_MAX /* Everything else. */

#define	BUS_PASS_ORDER_FIRST	0
#define	BUS_PASS_ORDER_EARLY	2
#define	BUS_PASS_ORDER_MIDDLE	5
#define	BUS_PASS_ORDER_LATE	7
#define	BUS_PASS_ORDER_LAST	9

extern int bus_current_pass;

void	bus_set_pass(int pass);

/**
 * Shorthands for constructing method tables.
 */
#define	DEVMETHOD	KOBJMETHOD
#define	DEVMETHOD_END	KOBJMETHOD_END

/*
 * Some common device interfaces.
 */
#include "device_if.h"
#include "bus_if.h"

struct	module;

int	driver_module_handler(struct module *, int, void *);

/**
 * Module support for automatically adding drivers to busses.
 */
struct driver_module_data {
	int		(*dmd_chainevh)(struct module *, int, void *);
	void		*dmd_chainarg;
	const char	*dmd_busname;
	kobj_class_t	dmd_driver;
	devclass_t	*dmd_devclass;
	int		dmd_pass;
};

#define	EARLY_DRIVER_MODULE_ORDERED(name, busname, driver, devclass,	\
    evh, arg, order, pass)						\
									\
/*static */struct driver_module_data name##_##busname##_driver_mod = {	\
	evh, arg,							\
	#busname,							\
	(kobj_class_t) &driver,						\
	&devclass,							\
	pass								\
};									\
									\
/*static */moduledata_t name##_##busname##_mod = {				\
	#busname "/" #name,						\
	driver_module_handler,						\
	&name##_##busname##_driver_mod					\
};									\
DECLARE_MODULE(name##_##busname, name##_##busname##_mod,		\
	       SI_SUB_DRIVERS, order)

#define	EARLY_DRIVER_MODULE(name, busname, driver, devclass, evh, arg, pass) \
	EARLY_DRIVER_MODULE_ORDERED(name, busname, driver, devclass,	\
	    evh, arg, SI_ORDER_MIDDLE, pass)

#define	DRIVER_MODULE_ORDERED(name, busname, driver, devclass, evh, arg,\
    order)								\
	EARLY_DRIVER_MODULE_ORDERED(name, busname, driver, devclass,	\
	    evh, arg, order, BUS_PASS_DEFAULT)

#define	DRIVER_MODULE(name, busname, driver, devclass, evh, arg)	\
	EARLY_DRIVER_MODULE(name, busname, driver, devclass, evh, arg,	\
	    BUS_PASS_DEFAULT)

/**
 * Generic ivar accessor generation macros for bus drivers
 */
#define __BUS_ACCESSOR(varp, var, ivarp, ivar, type)			\
									\
static __inline type varp ## _get_ ## var(device_t dev)			\
{									\
	uintptr_t v;							\
	int e;								\
	e = BUS_READ_IVAR(device_get_parent(dev), dev,			\
	    ivarp ## _IVAR_ ## ivar, &v);				\
	if (e != 0) {							\
		device_printf(dev, "failed to read ivar "		\
		    __XSTRING(ivarp ## _IVAR_ ## ivar) " on bus %s, "	\
		    "error = %d\n",					\
		    device_get_nameunit(device_get_parent(dev)), e);	\
	}								\
	return ((type) v);						\
}									\
									\
static __inline void varp ## _set_ ## var(device_t dev, type t)		\
{									\
	uintptr_t v = (uintptr_t) t;					\
	int e;								\
	e = BUS_WRITE_IVAR(device_get_parent(dev), dev,			\
	    ivarp ## _IVAR_ ## ivar, v);				\
	if (e != 0) {							\
		device_printf(dev, "failed to write ivar "		\
		    __XSTRING(ivarp ## _IVAR_ ## ivar) " on bus %s, "	\
		    "error = %d\n",					\
		    device_get_nameunit(device_get_parent(dev)), e);	\
	}								\
}

/**
 * Shorthand macros, taking resource argument
 * Generated with sys/tools/bus_macro.sh
 */

#define bus_barrier(r, o, l, f) \
	bus_space_barrier((r)->r_bustag, (r)->r_bushandle, (o), (l), (f))
#define bus_read_1(r, o) \
	bus_space_read_1((r)->r_bustag, (r)->r_bushandle, (o))
#define bus_read_multi_1(r, o, d, c) \
	bus_space_read_multi_1((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_region_1(r, o, d, c) \
	bus_space_read_region_1((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_set_multi_1(r, o, v, c) \
	bus_space_set_multi_1((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_set_region_1(r, o, v, c) \
	bus_space_set_region_1((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_write_1(r, o, v) \
	bus_space_write_1((r)->r_bustag, (r)->r_bushandle, (o), (v))
#define bus_write_multi_1(r, o, d, c) \
	bus_space_write_multi_1((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_write_region_1(r, o, d, c) \
	bus_space_write_region_1((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_stream_1(r, o) \
	bus_space_read_stream_1((r)->r_bustag, (r)->r_bushandle, (o))
#define bus_read_multi_stream_1(r, o, d, c) \
	bus_space_read_multi_stream_1((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_region_stream_1(r, o, d, c) \
	bus_space_read_region_stream_1((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_set_multi_stream_1(r, o, v, c) \
	bus_space_set_multi_stream_1((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_set_region_stream_1(r, o, v, c) \
	bus_space_set_region_stream_1((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_write_stream_1(r, o, v) \
	bus_space_write_stream_1((r)->r_bustag, (r)->r_bushandle, (o), (v))
#define bus_write_multi_stream_1(r, o, d, c) \
	bus_space_write_multi_stream_1((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_write_region_stream_1(r, o, d, c) \
	bus_space_write_region_stream_1((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_2(r, o) \
	bus_space_read_2((r)->r_bustag, (r)->r_bushandle, (o))
#define bus_read_multi_2(r, o, d, c) \
	bus_space_read_multi_2((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_region_2(r, o, d, c) \
	bus_space_read_region_2((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_set_multi_2(r, o, v, c) \
	bus_space_set_multi_2((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_set_region_2(r, o, v, c) \
	bus_space_set_region_2((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_write_2(r, o, v) \
	bus_space_write_2((r)->r_bustag, (r)->r_bushandle, (o), (v))
#define bus_write_multi_2(r, o, d, c) \
	bus_space_write_multi_2((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_write_region_2(r, o, d, c) \
	bus_space_write_region_2((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_stream_2(r, o) \
	bus_space_read_stream_2((r)->r_bustag, (r)->r_bushandle, (o))
#define bus_read_multi_stream_2(r, o, d, c) \
	bus_space_read_multi_stream_2((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_region_stream_2(r, o, d, c) \
	bus_space_read_region_stream_2((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_set_multi_stream_2(r, o, v, c) \
	bus_space_set_multi_stream_2((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_set_region_stream_2(r, o, v, c) \
	bus_space_set_region_stream_2((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_write_stream_2(r, o, v) \
	bus_space_write_stream_2((r)->r_bustag, (r)->r_bushandle, (o), (v))
#define bus_write_multi_stream_2(r, o, d, c) \
	bus_space_write_multi_stream_2((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_write_region_stream_2(r, o, d, c) \
	bus_space_write_region_stream_2((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_4(r, o) \
	bus_space_read_4((r)->r_bustag, (r)->r_bushandle, (o))
#define bus_read_multi_4(r, o, d, c) \
	bus_space_read_multi_4((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_region_4(r, o, d, c) \
	bus_space_read_region_4((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_set_multi_4(r, o, v, c) \
	bus_space_set_multi_4((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_set_region_4(r, o, v, c) \
	bus_space_set_region_4((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_write_4(r, o, v) \
	bus_space_write_4((r)->r_bustag, (r)->r_bushandle, (o), (v))
#define bus_write_multi_4(r, o, d, c) \
	bus_space_write_multi_4((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_write_region_4(r, o, d, c) \
	bus_space_write_region_4((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_stream_4(r, o) \
	bus_space_read_stream_4((r)->r_bustag, (r)->r_bushandle, (o))
#define bus_read_multi_stream_4(r, o, d, c) \
	bus_space_read_multi_stream_4((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_region_stream_4(r, o, d, c) \
	bus_space_read_region_stream_4((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_set_multi_stream_4(r, o, v, c) \
	bus_space_set_multi_stream_4((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_set_region_stream_4(r, o, v, c) \
	bus_space_set_region_stream_4((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_write_stream_4(r, o, v) \
	bus_space_write_stream_4((r)->r_bustag, (r)->r_bushandle, (o), (v))
#define bus_write_multi_stream_4(r, o, d, c) \
	bus_space_write_multi_stream_4((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_write_region_stream_4(r, o, d, c) \
	bus_space_write_region_stream_4((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_8(r, o) \
	bus_space_read_8((r)->r_bustag, (r)->r_bushandle, (o))
#define bus_read_multi_8(r, o, d, c) \
	bus_space_read_multi_8((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_region_8(r, o, d, c) \
	bus_space_read_region_8((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_set_multi_8(r, o, v, c) \
	bus_space_set_multi_8((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_set_region_8(r, o, v, c) \
	bus_space_set_region_8((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_write_8(r, o, v) \
	bus_space_write_8((r)->r_bustag, (r)->r_bushandle, (o), (v))
#define bus_write_multi_8(r, o, d, c) \
	bus_space_write_multi_8((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_write_region_8(r, o, d, c) \
	bus_space_write_region_8((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_stream_8(r, o) \
	bus_space_read_stream_8((r)->r_bustag, (r)->r_bushandle, (o))
#define bus_read_multi_stream_8(r, o, d, c) \
	bus_space_read_multi_stream_8((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_read_region_stream_8(r, o, d, c) \
	bus_space_read_region_stream_8((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_set_multi_stream_8(r, o, v, c) \
	bus_space_set_multi_stream_8((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_set_region_stream_8(r, o, v, c) \
	bus_space_set_region_stream_8((r)->r_bustag, (r)->r_bushandle, (o), (v), (c))
#define bus_write_stream_8(r, o, v) \
	bus_space_write_stream_8((r)->r_bustag, (r)->r_bushandle, (o), (v))
#define bus_write_multi_stream_8(r, o, d, c) \
	bus_space_write_multi_stream_8((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))
#define bus_write_region_stream_8(r, o, d, c) \
	bus_space_write_region_stream_8((r)->r_bustag, (r)->r_bushandle, (o), (d), (c))

#endif /* !_SYS_BUS_H_ */
