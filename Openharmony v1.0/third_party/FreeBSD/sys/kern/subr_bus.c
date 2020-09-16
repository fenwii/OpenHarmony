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
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/11.4/sys/kern/subr_bus.c 351242 2019-08-19 23:57:37Z jhb $");

#include <sys/param.h>
#include <sys/kobj.h>
#include <sys/malloc.h>
#include <sys/queue.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include <sys/mutex.h>
#include "los_hwi.h"

#ifndef BOOTVERBOSE
#define BOOTVERBOSE     0
#endif
int     bootverbose = BOOTVERBOSE;

/*
 *  * Used to attach drivers to devclasses.
 *   */
typedef struct driverlink *driverlink_t;
struct driverlink {
	kobj_class_t    driver;
	TAILQ_ENTRY(driverlink) link;   /* list of drivers in devclass */
	int             pass;
	TAILQ_ENTRY(driverlink) passlink;
};

/*
 * Forward declarations
 */
typedef TAILQ_HEAD(devclass_list, devclass) devclass_list_t;
typedef TAILQ_HEAD(driver_list, driverlink) driver_list_t;
typedef TAILQ_HEAD(device_list, device) device_list_t;

struct devclass {
        TAILQ_ENTRY(devclass) link;
        devclass_t      parent;         /* parent in devclass hierarchy */
        driver_list_t   drivers;     /* bus devclasses store drivers for bus */
        char            *name;
        device_t        *devices;       /* array of devices indexed by unit */
        int             maxunit;        /* size of devices array */
        int             flags;
#define DC_HAS_CHILDREN         1
};

/**
 * @brief Implementation of device.
 */
struct device {
        /*
         * A device is a kernel object. The first field must be the
         * current ops table for the object.
         */
        KOBJ_FIELDS;

        /*
         * Device hierarchy.
         */
        TAILQ_ENTRY(device)     link;   /**< list of devices in parent */
        TAILQ_ENTRY(device)     devlink; /**< global device list membership */
        device_t        parent;         /**< parent of this device  */
        device_list_t   children;       /**< list of child devices */

        /*
         * Details of this device.
         */
        driver_t        *driver;        /**< current driver */
        devclass_t      devclass;       /**< current device class */
        int             unit;           /**< current unit number */
        char*           nameunit;       /**< name+unit e.g. foodev0 */
        char*           desc;           /**< driver specific description */
        int             busy;           /**< count of calls to device_busy() */
        device_state_t  state;          /**< current device state  */
        uint32_t        devflags;       /**< api level flags for device_get_flags() */
        u_int           flags;          /**< internal device flags  */
        u_int   order;                  /**< order from device_add_child_ordered() */
        void    *ivars;                 /**< instance variables  */
        void    *softc;                 /**< current driver's variables  */
};

static MALLOC_DEFINE(M_BUS, "bus", "Bus data structures");

#ifdef BUS_DEBUG
static int bus_debug = 1;

#define PDEBUG(a)       if (bus_debug) {PRINTK("%s:%d: ", __func__, __LINE__), PRINTK a; PRINTK("\n");}
#define DEVICENAME(d)   ((d)? device_get_name(d): "no device")
#define DRIVERNAME(d)   ((d)? d->name : "no driver")
#define DEVCLANAME(d)   ((d)? d->name : "no devclass")

/**
 * Produce the indenting, indent*2 spaces plus a '.' ahead of that to
 * prevent syslog from deleting initial spaces
 */
#define indentprintf(p) do { int iJ; PRINTK("."); for (iJ=0; iJ<indent; iJ++) PRINTK("  "); PRINTK p ; } while (0)

static void print_device_short(device_t dev, int indent);
static void print_device(device_t dev, int indent);
void print_device_tree_short(device_t dev, int indent);
void print_device_tree(device_t dev, int indent);
static void print_driver_short(driver_t *driver, int indent);
static void print_driver(driver_t *driver, int indent);
static void print_driver_list(driver_list_t drivers, int indent);
static void print_devclass_short(devclass_t dc, int indent);
static void print_devclass(devclass_t dc, int indent);
void print_devclass_list_short(void);
void print_devclass_list(void);

#else
/* Make the compiler ignore the function calls */
#define PDEBUG(a)                       /* nop */
#define DEVICENAME(d)                   /* nop */
#define DRIVERNAME(d)                   /* nop */
#define DEVCLANAME(d)                   /* nop */

#define print_device_short(d,i)         /* nop */
#define print_device(d,i)               /* nop */
#define print_device_tree_short(d,i)    /* nop */
#define print_device_tree(d,i)          /* nop */
#define print_driver_short(d,i)         /* nop */
#define print_driver(d,i)               /* nop */
#define print_driver_list(d,i)          /* nop */
#define print_devclass_short(d,i)       /* nop */
#define print_devclass(d,i)             /* nop */
#define print_devclass_list_short()     /* nop */
#define print_devclass_list()           /* nop */
#endif

static TAILQ_HEAD(,device)      bus_data_devices;
static int bus_data_generation = 1;

static kobj_method_t null_methods[] = {
        KOBJMETHOD_END
};

DEFINE_CLASS(null, null_methods, 0);

/*
 * Bus pass implementation
 */

static driver_list_t passes = TAILQ_HEAD_INITIALIZER(passes);
int bus_current_pass = BUS_PASS_ROOT;

/**
 * @brief Return the name of the device's devclass or @c NULL if there
 * is none.
 */
const char *
device_get_name(device_t dev)
{
	if (dev != NULL && dev->devclass)
		return (devclass_get_name(dev->devclass));
	return (NULL);
}

/**
 * @internal
 * @brief Register the pass level of a new driver attachment
 *
 * Register a new driver attachment's pass level.  If no driver
 * attachment with the same pass level has been added, then @p new
 * will be added to the global passes list.
 *
 * @param new           the new driver attachment
 */
static void
driver_register_pass(struct driverlink *new)
{
        struct driverlink *dl = NULL;

        /* We only consider pass numbers during boot. */
        if (bus_current_pass == BUS_PASS_DEFAULT)
                return;

        /*
         * Walk the passes list.  If we already know about this pass
         * then there is nothing to do.  If we don't, then insert this
         * driver link into the list.
         */
        TAILQ_FOREACH(dl, &passes, passlink) {
                if (dl->pass < new->pass)
                        continue;
                if (dl->pass == new->pass)
                        return;
                TAILQ_INSERT_BEFORE(dl, new, passlink);
                return;
        }
        TAILQ_INSERT_TAIL(&passes, new, passlink);
}

/**
 * @brief Raise the current bus pass
 *
 * Raise the current bus pass level to @p pass.  Call the BUS_NEW_PASS()
 * method on the root bus to kick off a new device tree scan for each
 * new pass level that has at least one driver.
 */
void
bus_set_pass(int pass)
{
        struct driverlink *dl = NULL;

        if (bus_current_pass > pass)
                panic("Attempt to lower bus pass level");

        TAILQ_FOREACH(dl, &passes, passlink) {
                /* Skip pass values below the current pass level. */
                if (dl->pass <= bus_current_pass)
                        continue;

                /*
                 * Bail once we hit a driver with a pass level that is
                 * too high.
                 */
                if (dl->pass > pass)
                        break;

                /*
                 * Raise the pass level to the next level and rescan
                 * the tree.
                 */
                bus_current_pass = dl->pass;
                BUS_NEW_PASS(root_bus);
        }

        /*
         * If there isn't a driver registered for the requested pass,
         * then bus_current_pass might still be less than 'pass'.  Set
         * it to 'pass' in that case.
         */
        if (bus_current_pass < pass)
                bus_current_pass = pass;
        KASSERT(bus_current_pass == pass, ("Failed to update bus pass level"));
}

/*
 * Devclass implementation
 */

static devclass_list_t devclasses = TAILQ_HEAD_INITIALIZER(devclasses);

/**
 * @internal
 * @brief Find or create a device class
 *
 * If a device class with the name @p classname exists, return it,
 * otherwise if @p create is non-zero create and return a new device
 * class.
 *
 * If @p parentname is non-NULL, the parent of the devclass is set to
 * the devclass of that name.
 *
 * @param classname     the devclass name to find or create
 * @param parentname    the parent devclass name or @c NULL
 * @param create        non-zero to create a devclass
 */
static devclass_t
devclass_find_internal(const char *classname, const char *parentname,
                       int create)
{
        devclass_t dc;

        PDEBUG(("looking for %s", classname));
        if (!classname)
                return (NULL);

        TAILQ_FOREACH(dc, &devclasses, link) {
                if (!strcmp(dc->name, classname))
                        break;
        }

        if (create && !dc) {
                dc = bsd_malloc(sizeof(struct devclass) + strlen(classname) + 1,
                    M_BUS, M_NOWAIT | M_ZERO);
                if (!dc)
                        return (NULL);
                dc->parent = NULL;
                dc->name = (char*) (dc + 1);
                if (strcpy_s(dc->name, strlen(classname) + 1, classname) != EOK) {
                        bsd_free(dc, M_BUS);
                        return (NULL);
                }
                TAILQ_INIT(&dc->drivers);
                TAILQ_INSERT_TAIL(&devclasses, dc, link);

                PDEBUG(("create dc %p, %s", dc, classname));
                bus_data_generation_update();
        }

        /*
         * If a parent class is specified, then set that as our parent so
         * that this devclass will support drivers for the parent class as
         * well.  If the parent class has the same name don't do this though
         * as it creates a cycle that can trigger an infinite loop in
         * device_probe_child() if a device exists for which there is no
         * suitable driver.
         */
        if (parentname && dc && !dc->parent &&
            strcmp(classname, parentname) != 0) {
                dc->parent = devclass_find_internal(parentname, NULL, TRUE);
                dc->parent->flags = (unsigned int)dc->parent->flags | DC_HAS_CHILDREN;
        }

        PDEBUG(("found dc %p, %s", dc, classname));
        return (dc);
}

/**
 * @brief Create a device class
 *
 * If a device class with the name @p classname exists, return it,
 * otherwise create and return a new device class.
 *
 * @param classname     the devclass name to find or create
 */
devclass_t
devclass_create(const char *classname)
{
        return (devclass_find_internal(classname, NULL, TRUE));
}

/**
 * @brief Find a device class
 *
 * If a device class with the name @p classname exists, return it,
 * otherwise return @c NULL.
 *
 * @param classname     the devclass name to find
 */
devclass_t
devclass_find(const char *classname)
{
        return (devclass_find_internal(classname, NULL, FALSE));
}

/**
 * @brief Register that a device driver has been added to a devclass
 *
 * Register that a device driver has been added to a devclass.  This
 * is called by devclass_add_driver to accomplish the recursive
 * notification of all the children classes of dc, as well as dc.
 * Each layer will have BUS_DRIVER_ADDED() called for all instances of
 * the devclass.
 *
 * We do a full search here of the devclass list at each iteration
 * level to save storing children-lists in the devclass structure.  If
 * we ever move beyond a few dozen devices doing this, we may need to
 * reevaluate...
 *
 * @param dc            the devclass to edit
 * @param driver        the driver that was just added
 */
static void
devclass_driver_added(devclass_t dc, driver_t *driver)
{
        devclass_t parent;
        int i;

        /*
         * Call BUS_DRIVER_ADDED for any existing busses in this class.
         */
        for (i = 0; i < dc->maxunit; i++)
                if (dc->devices[i] && device_is_attached(dc->devices[i]))
                        BUS_DRIVER_ADDED(dc->devices[i], driver);

        /*
         * Walk through the children classes.  Since we only keep a
         * single parent pointer around, we walk the entire list of
         * devclasses looking for children.  We set the
         * DC_HAS_CHILDREN flag when a child devclass is created on
         * the parent, so we only walk the list for those devclasses
         * that have children.
         */
        if (!((unsigned int)dc->flags & DC_HAS_CHILDREN))
                return;
        parent = dc;
        TAILQ_FOREACH(dc, &devclasses, link) {
                if (dc->parent == parent)
                        devclass_driver_added(dc, driver);
        }
}

/**
 * @brief Add a device driver to a device class
 *
 * Add a device driver to a devclass. This is normally called
 * automatically by DRIVER_MODULE(). The BUS_DRIVER_ADDED() method of
 * all devices in the devclass will be called to allow them to attempt
 * to re-probe any unmatched children.
 *
 * @param dc            the devclass to edit
 * @param driver        the driver to register
 */
int
devclass_add_driver(devclass_t dc, driver_t *driver, int pass, devclass_t *dcp)
{
        driverlink_t dl = NULL;
        const char *parentname = NULL;

        PDEBUG(("%s +", DRIVERNAME(driver)));

        /* Don't allow invalid pass values. */
        if (pass <= BUS_PASS_ROOT)
                return (EINVAL);

        dl = bsd_malloc(sizeof *dl, M_BUS, M_NOWAIT|M_ZERO);
        if (!dl)
                return (ENOMEM);

        /*
         * Compile the driver's methods. Also increase the reference count
         * so that the class doesn't get freed when the last instance
         * goes. This means we can safely use static methods and avoids a
         * double-free in devclass_delete_driver.
         */
        kobj_class_compile((kobj_class_t) driver);

        /*
         * If the driver has any base classes, make the
         * devclass inherit from the devclass of the driver's
         * first base class. This will allow the system to
         * search for drivers in both devclasses for children
         * of a device using this driver.
         */
        if (driver->baseclasses)
                parentname = driver->baseclasses[0]->name;
        else
                parentname = NULL;
        *dcp = devclass_find_internal(driver->name, parentname, TRUE);

        dl->driver = driver;
        TAILQ_INSERT_TAIL(&dc->drivers, dl, link);
        driver->refs++;         /* XXX: kobj_mtx */
        dl->pass = pass;
        driver_register_pass(dl);

        devclass_driver_added(dc, driver);
        bus_data_generation_update();
        PDEBUG(("%s -", DRIVERNAME(driver)));
        return (0);
}

/**
 * @brief Register that a device driver has been deleted from a devclass
 *
 * Register that a device driver has been removed from a devclass.
 * This is called by devclass_delete_driver to accomplish the
 * recursive notification of all the children classes of busclass, as
 * well as busclass.  Each layer will attempt to detach the driver
 * from any devices that are children of the bus's devclass.  The function
 * will return an error if a device fails to detach.
 *
 * We do a full search here of the devclass list at each iteration
 * level to save storing children-lists in the devclass structure.  If
 * we ever move beyond a few dozen devices doing this, we may need to
 * reevaluate...
 *
 * @param busclass      the devclass of the parent bus
 * @param dc            the devclass of the driver being deleted
 * @param driver        the driver being deleted
 */
static int
devclass_driver_deleted(devclass_t busclass, devclass_t dc, driver_t *driver)
{
        devclass_t parent;
        device_t dev;
        int error, i;

        /*
         * Disassociate from any devices.  We iterate through all the
         * devices in the devclass of the driver and detach any which are
         * using the driver and which have a parent in the devclass which
         * we are deleting from.
         *
         * Note that since a driver can be in multiple devclasses, we
         * should not detach devices which are not children of devices in
         * the affected devclass.
         */
        for (i = 0; i < dc->maxunit; i++) {
                if (dc->devices[i]) {
                        dev = dc->devices[i];
                        if (dev->driver == driver && dev->parent &&
                            dev->parent->devclass == busclass) {
                                if ((error = device_detach(dev)) != 0)
                                        return (error);
                                BUS_PROBE_NOMATCH(dev->parent, dev);
                                // devnomatch(dev);
                                dev->flags |= DF_DONENOMATCH;
                        }
                }
        }

        /*
         * Walk through the children classes.  Since we only keep a
         * single parent pointer around, we walk the entire list of
         * devclasses looking for children.  We set the
         * DC_HAS_CHILDREN flag when a child devclass is created on
         * the parent, so we only walk the list for those devclasses
         * that have children.
         */
        if (!((unsigned int)busclass->flags & DC_HAS_CHILDREN))
                return (0);
        parent = busclass;
        TAILQ_FOREACH(busclass, &devclasses, link) {
                if (busclass->parent == parent) {
                        error = devclass_driver_deleted(busclass, dc, driver);
                        if (error)
                                return (error);
                }
        }
        return (0);
}

/**
 * @brief Delete a device driver from a device class
 *
 * Delete a device driver from a devclass. This is normally called
 * automatically by DRIVER_MODULE().
 *
 * If the driver is currently attached to any devices,
 * devclass_delete_driver() will first attempt to detach from each
 * device. If one of the detach calls fails, the driver will not be
 * deleted.
 *
 * @param dc            the devclass to edit
 * @param driver        the driver to unregister
 */
int
devclass_delete_driver(devclass_t busclass, driver_t *driver)
{
        devclass_t dc = devclass_find(driver->name);
        driverlink_t dl = NULL;
        int error;

        PDEBUG(("%s from devclass %s", driver->name, DEVCLANAME(busclass)));

        if (!dc)
                return (0);

        /*
         * Find the link structure in the bus' list of drivers.
         */
        TAILQ_FOREACH(dl, &busclass->drivers, link) {
                if (dl->driver == driver)
                        break;
        }

        if (!dl) {
                PDEBUG(("%s not found in %s list", driver->name,
                    busclass->name));
                return (ENOENT);
        }

        error = devclass_driver_deleted(busclass, dc, driver);
        if (error != 0)
                return (error);

        TAILQ_REMOVE(&busclass->drivers, dl, link);
        bsd_free(dl, M_BUS);

        /* XXX: kobj_mtx */
        driver->refs--;
        if (driver->refs == 0)
                kobj_class_free((kobj_class_t) driver);

        bus_data_generation_update();
        return (0);
}

/**
 * @brief Quiesces a set of device drivers from a device class
 *
 * Quiesce a device driver from a devclass. This is normally called
 * automatically by DRIVER_MODULE().
 *
 * If the driver is currently attached to any devices,
 * devclass_quiesece_driver() will first attempt to quiesce each
 * device.
 *
 * @param dc            the devclass to edit
 * @param driver        the driver to unregister
 */
static int
devclass_quiesce_driver(devclass_t busclass, driver_t *driver)
{
        devclass_t dc = devclass_find(driver->name);
        driverlink_t dl = NULL;
        device_t dev;
        int i;
        int error;

        PDEBUG(("%s from devclass %s", driver->name, DEVCLANAME(busclass)));

        if (!dc)
                return (0);

        /*
         * Find the link structure in the bus' list of drivers.
         */
        TAILQ_FOREACH(dl, &busclass->drivers, link) {
                if (dl->driver == driver)
                        break;
        }

        if (!dl) {
                PDEBUG(("%s not found in %s list", driver->name,
                    busclass->name));
                return (ENOENT);
        }

        /*
         * Quiesce all devices.  We iterate through all the devices in
         * the devclass of the driver and quiesce any which are using
         * the driver and which have a parent in the devclass which we
         * are quiescing.
         *
         * Note that since a driver can be in multiple devclasses, we
         * should not quiesce devices which are not children of
         * devices in the affected devclass.
         */
        for (i = 0; i < dc->maxunit; i++) {
                if (dc->devices[i]) {
                        dev = dc->devices[i];
                        if (dev->driver == driver && dev->parent &&
                            dev->parent->devclass == busclass) {
                                if ((error = device_quiesce(dev)) != 0)
                                        return (error);
                        }
                }
        }

        return (0);
}

/**
 * @internal
 */
static driverlink_t
devclass_find_driver_internal(devclass_t dc, const char *classname)
{
        driverlink_t dl = NULL;

        PDEBUG(("%s in devclass %s", classname, DEVCLANAME(dc)));

        TAILQ_FOREACH(dl, &dc->drivers, link) {
                if (!strcmp(dl->driver->name, classname))
                        return (dl);
        }

        PDEBUG(("not found"));
        return (NULL);
}

/**
 * @brief Return the name of the devclass
 */
const char *
devclass_get_name(devclass_t dc)
{
        return (dc->name);
}

/**
 * @brief Find a device given a unit number
 *
 * @param dc            the devclass to search
 * @param unit          the unit number to search for
 *
 * @returns             the device with the given unit number or @c
 *                      NULL if there is no such device
 */
device_t
devclass_get_device(devclass_t dc, int unit)
{
        if (dc == NULL || unit < 0 || unit >= dc->maxunit)
                return (NULL);
        return (dc->devices[unit]);
}

/**
 * @brief Find the softc field of a device given a unit number
 *
 * @param dc            the devclass to search
 * @param unit          the unit number to search for
 *
 * @returns             the softc field of the device with the given
 *                      unit number or @c NULL if there is no such
 *                      device
 */
void *
devclass_get_softc(devclass_t dc, int unit)
{
        device_t dev;

        dev = devclass_get_device(dc, unit);
        if (!dev)
                return (NULL);

        return (device_get_softc(dev));
}

/**
 * @brief Get a list of devices in the devclass
 *
 * An array containing a list of all the devices in the given devclass
 * is allocated and returned in @p *devlistp. The number of devices
 * in the array is returned in @p *devcountp. The caller should free
 * the array using @c free(p, M_TEMP), even if @p *devcountp is 0.
 *
 * @param dc            the devclass to examine
 * @param devlistp      points at location for array pointer return
 *                      value
 * @param devcountp     points at location for array size return value
 *
 * @retval 0            success
 * @retval ENOMEM       the array allocation failed
 */
int
devclass_get_devices(devclass_t dc, device_t **devlistp, int *devcountp)
{
        int count, i;
        device_t *list;

        count = devclass_get_count(dc);
        list = bsd_malloc(count * sizeof(device_t), M_TEMP, M_NOWAIT|M_ZERO);
        if (!list)
                return (ENOMEM);

        count = 0;
        for (i = 0; i < dc->maxunit; i++) {
                if (dc->devices[i]) {
                        list[count] = dc->devices[i];
                        count++;
                }
        }

        *devlistp = list;
        *devcountp = count;

        return (0);
}

/**
 * @brief Get a list of drivers in the devclass
 *
 * An array containing a list of pointers to all the drivers in the
 * given devclass is allocated and returned in @p *listp.  The number
 * of drivers in the array is returned in @p *countp. The caller should
 * free the array using @c free(p, M_TEMP).
 *
 * @param dc            the devclass to examine
 * @param listp         gives location for array pointer return value
 * @param countp        gives location for number of array elements
 *                      return value
 *
 * @retval 0            success
 * @retval ENOMEM       the array allocation failed
 */
int
devclass_get_drivers(devclass_t dc, driver_t ***listp, int *countp)
{
        driverlink_t dl = NULL;
        driver_t **list = NULL;
        int count;

        count = 0;
        TAILQ_FOREACH(dl, &dc->drivers, link)
                count++;
        list = bsd_malloc(count * sizeof(driver_t *), M_TEMP, M_NOWAIT);
        if (list == NULL)
                return (ENOMEM);

        count = 0;
        TAILQ_FOREACH(dl, &dc->drivers, link) {
                list[count] = dl->driver;
                count++;
        }
        *listp = list;
        *countp = count;

        return (0);
}

/**
 * @brief Get the number of devices in a devclass
 *
 * @param dc            the devclass to examine
 */
int
devclass_get_count(devclass_t dc)
{
        int count, i;

        count = 0;
        for (i = 0; i < dc->maxunit; i++)
                if (dc->devices[i])
                        count++;
        return (count);
}

/**
 * @brief Get the maximum unit number used in a devclass
 *
 * Note that this is one greater than the highest currently-allocated
 * unit.  If a null devclass_t is passed in, -1 is returned to indicate
 * that not even the devclass has been allocated yet.
 *
 * @param dc            the devclass to examine
 */
int
devclass_get_maxunit(devclass_t dc)
{
        if (dc == NULL)
                return (-1);
        return (dc->maxunit);
}

/**
 * @brief Find a free unit number in a devclass
 *
 * This function searches for the first unused unit number greater
 * that or equal to @p unit.
 *
 * @param dc            the devclass to examine
 * @param unit          the first unit number to check
 */
int
devclass_find_free_unit(devclass_t dc, int unit)
{
        if (dc == NULL)
                return (unit);
        while (unit < dc->maxunit && dc->devices[unit] != NULL)
                unit++;
        return (unit);
}

/**
 * @brief Set the parent of a devclass
 *
 * The parent class is normally initialised automatically by
 * DRIVER_MODULE().
 *
 * @param dc            the devclass to edit
 * @param pdc           the new parent devclass
 */
void
devclass_set_parent(devclass_t dc, devclass_t pdc)
{
        dc->parent = pdc;
}

/**
 * @brief Get the parent of a devclass
 *
 * @param dc            the devclass to examine
 */
devclass_t
devclass_get_parent(devclass_t dc)
{
        return (dc->parent);
}

/**
 * @internal
 * @brief Allocate a unit number
 *
 * On entry, @p *unitp is the desired unit number (or @c -1 if any
 * will do). The allocated unit number is returned in @p *unitp.

 * @param dc            the devclass to allocate from
 * @param unitp         points at the location for the allocated unit
 *                      number
 *
 * @retval 0            success
 * @retval EEXIST       the requested unit number is already allocated
 * @retval ENOMEM       memory allocation failure
 */
static int
devclass_alloc_unit(devclass_t dc, device_t dev, int *unitp)
{
    int unit = *unitp;

    PDEBUG(("unit %d in devclass %s", unit, DEVCLANAME(dc)));

    /* Ask the parent bus if it wants to wire this device. */
    if (unit == -1)
        BUS_HINT_DEVICE_UNIT(device_get_parent(dev), dev, dc->name, &unit);

    /* If we were given a wired unit number, check for existing device */
    /* XXX imp XXX */
    if (unit != -1) {
        if (unit >= 0 && unit < dc->maxunit && dc->devices[unit] != NULL) {
            if (bootverbose)
                printf("%s: %s%d already exists; skipping it\n", dc->name, dc->name, *unitp);
            return (EEXIST);
        }
    } else {
        /* Unwired device, find the next available slot for it */
        unit = 0;
        for (unit = 0;; unit++) {
            /* If this device slot is already in use, skip it. */
            if (unit < dc->maxunit && dc->devices[unit] != NULL)
                continue;

            break;
        }
    }
    PDEBUG(("mid: unit %d in devclass %s", unit, DEVCLANAME(dc)));
    /*
     * We've selected a unit beyond the length of the table, so let's
     * extend the table to make room for all units up to and including
     * this one.
     */
    if (unit >= dc->maxunit) {
        device_t *newlist, *oldlist;
        int newsize;

        oldlist = dc->devices;
        newsize = roundup((unit + 1), MINALLOCSIZE / sizeof(device_t));
        newlist = bsd_malloc(sizeof(device_t) * newsize, M_BUS, M_NOWAIT);
		PDEBUG(("oldlist %p, newlist %p, newsize %d", oldlist, newlist, newsize));
        if (!newlist)
            return (ENOMEM);
		PDEBUG(("start memcpy, size %d", sizeof(device_t) * dc->maxunit));
        if (oldlist != NULL)
            (void)memcpy_s(oldlist, sizeof(device_t) * dc->maxunit, newlist, sizeof(device_t) * dc->maxunit);
        PDEBUG(("start memset, maxunit %d, size %d", dc->maxunit, sizeof(device_t) * (newsize - dc->maxunit)));
        (void)memset_s(newlist + dc->maxunit, sizeof(device_t) * (newsize - dc->maxunit), 0,
                       sizeof(device_t) * (newsize - dc->maxunit));
        dc->devices = newlist;
        dc->maxunit = newsize;
        if (oldlist != NULL)
            bsd_free(oldlist, M_BUS);
    }
    PDEBUG(("now: unit %d in devclass %s", unit, DEVCLANAME(dc)));

    *unitp = unit;
    return (0);
}

/**
 * @internal
 */
static void
device_set_desc_internal(device_t dev, const char* desc, int copy)
{
	if (dev->desc && (dev->flags & DF_DESCMALLOCED)) {
		bsd_free(dev->desc, M_BUS);
		dev->flags &= ~DF_DESCMALLOCED;
		dev->desc = NULL;
	}

	if (copy && desc) {
		dev->desc = bsd_malloc(strlen(desc) + 1, M_BUS, M_NOWAIT);
		if (dev->desc) {
			if (strcpy_s(dev->desc, strlen(desc) + 1, desc) != EOK) {
				PDEBUG("desc internal copy desc failed!\n");
			}
			dev->flags |= DF_DESCMALLOCED;
		}
	} else {
		/* Avoid a -Wcast-qual warning */
		dev->desc = (char *)(uintptr_t) desc;
	}

	bus_data_generation_update();
}

/**
 * @brief Set the device's description
 *
 * The value of @c desc should be a string constant that will not
 * change (at least until the description is changed in a subsequent
 * call to device_set_desc() or device_set_desc_copy()).
 */
void
device_set_desc(device_t dev, const char* desc)
{
	device_set_desc_internal(dev, desc, FALSE);
}

/**
 * @brief Set the device's description
 *
 * The string pointed to by @c desc is copied. Use this function if
 * the device description is generated, (e.g. with sprintf()).
 */
void
device_set_desc_copy(device_t dev, const char* desc)
{
        device_set_desc_internal(dev, desc, TRUE);
}

/**
 * @brief Return the device's description string
 */
const char *
device_get_desc(device_t dev)
{
        return (dev->desc);
}

/**
 * @brief Return the device's softc field
 *
 * The softc is allocated and zeroed when a driver is attached, based
 * on the size field of the driver.
 */
void *
device_get_softc(device_t dev)
{
        return (dev->softc);
}

/**
 * @brief Set the device's softc field
 *
 * Most drivers do not need to use this since the softc is allocated
 * automatically when the driver is attached.
 */
void
device_set_softc(device_t dev, void *softc)
{
        if (dev->softc && !(dev->flags & DF_EXTERNALSOFTC))
                bsd_free(dev->softc, M_BUS_SC);
        dev->softc = softc;
        if (dev->softc)
                dev->flags |= DF_EXTERNALSOFTC;
        else
                dev->flags &= ~DF_EXTERNALSOFTC;
}

/**
 * @brief Free claimed softc
 *
 * Most drivers do not need to use this since the softc is freed
 * automatically when the driver is detached.
 */
void
device_free_softc(void *softc)
{
        bsd_free(softc, M_BUS_SC);
}

/**
 * @brief Claim softc
 *
 * This function can be used to let the driver free the automatically
 * allocated softc using "device_free_softc()". This function is
 * useful when the driver is refcounting the softc and the softc
 * cannot be freed when the "device_detach" method is called.
 */
void
device_claim_softc(device_t dev)
{
        if (dev->softc)
                dev->flags |= DF_EXTERNALSOFTC;
        else
                dev->flags &= ~DF_EXTERNALSOFTC;
}

/**
 * @brief Get the device's ivars field
 *
 * The ivars field is used by the parent device to store per-device
 * state (e.g. the physical location of the device or a list of
 * resources).
 */
void *
device_get_ivars(device_t dev)
{

        KASSERT(dev != NULL, ("device_get_ivars(NULL, ...)"));
        return (dev->ivars);
}

/**
 * @brief Set the device's ivars field
 */
void
device_set_ivars(device_t dev, void * ivars)
{

        KASSERT(dev != NULL, ("device_set_ivars(NULL, ...)"));
        dev->ivars = ivars;
}

/**
 * @brief Return the device's state
 */
device_state_t
device_get_state(device_t dev)
{
        return (dev->state);
}

/**
 * @brief Set the DF_ENABLED flag for the device
 */
void
device_enable(device_t dev)
{
        dev->flags |= DF_ENABLED;
}

/**
 * @brief Clear the DF_ENABLED flag for the device
 */
void
device_disable(device_t dev)
{
        dev->flags &= ~DF_ENABLED;
}

/**
 * @brief Increment the busy counter for the device
 */
void
device_busy(device_t dev)
{
        if (dev->state < DS_ATTACHING)
                panic("device_busy: called for unattached device");
        if (dev->busy == 0 && dev->parent)
                device_busy(dev->parent);
        dev->busy++;
        if (dev->state == DS_ATTACHED)
                dev->state = DS_BUSY;
}

/**
 * @brief Decrement the busy counter for the device
 */
void
device_unbusy(device_t dev)
{
        if (dev->busy != 0 && dev->state != DS_BUSY &&
            dev->state != DS_ATTACHING)
                panic("device_unbusy: called for non-busy device %s",
                    device_get_nameunit(dev));
        dev->busy--;
        if (dev->busy == 0) {
                if (dev->parent)
                        device_unbusy(dev->parent);
                if (dev->state == DS_BUSY)
                        dev->state = DS_ATTACHED;
        }
}

/**
 * @brief Set the DF_QUIET flag for the device
 */
void
device_quiet(device_t dev)
{
        dev->flags |= DF_QUIET;
}

/**
 * @brief Clear the DF_QUIET flag for the device
 */
void
device_verbose(device_t dev)
{
        dev->flags &= ~DF_QUIET;
}

/**
 * @brief Return non-zero if the DF_QUIET flag is set on the device
 */
int
device_is_quiet(device_t dev)
{
        return ((dev->flags & DF_QUIET) != 0);
}

/**
 * @brief Return non-zero if the DF_ENABLED flag is set on the device
 */
int
device_is_enabled(device_t dev)
{
        return ((dev->flags & DF_ENABLED) != 0);
}

/**
 * @brief Return non-zero if the device was successfully probed
 */
int
device_is_alive(device_t dev)
{
        return (dev->state >= DS_ALIVE);
}

/**
 * @brief Return non-zero if the device currently has a driver
 * attached to it
 */
int
device_is_attached(device_t dev)
{
        return (dev->state >= DS_ATTACHED);
}

/**
 * @brief Return non-zero if the device is currently suspended.
 */
int
device_is_suspended(device_t dev)
{
        return ((dev->flags & DF_SUSPENDED) != 0);
}



/**
 * @brief Return a string containing the device's devclass name
 * followed by an ascii representation of the device's unit number
 * (e.g. @c "foo2").
 */
const char *
device_get_nameunit(device_t dev)
{
	return (dev->nameunit);
}

/**
 * @internal
 * @brief Add a device to a devclass
 *
 * A unit number is allocated for the device (using the device's
 * preferred unit number if any) and the device is registered in the
 * devclass. This allows the device to be looked up by its unit
 * number, e.g. by decoding a dev_t minor number.
 *
 * @param dc            the devclass to add to
 * @param dev           the device to add
 *
 * @retval 0            success
 * @retval EEXIST       the requested unit number is already allocated
 * @retval ENOMEM       memory allocation failure
 */
static int
devclass_add_device(devclass_t dc, device_t dev)
{
        int buflen, error;

        PDEBUG(("%s in devclass %s", DEVICENAME(dev), DEVCLANAME(dc)));

        buflen = snprintf(NULL, 0, "%s%d$", dc->name, INT_MAX);
        if (buflen < 0)
                return (ENOMEM);
        dev->nameunit = bsd_malloc(buflen, M_BUS, M_NOWAIT|M_ZERO);
        if (!dev->nameunit)
                return (ENOMEM);

        if ((error = devclass_alloc_unit(dc, dev, &dev->unit)) != 0) {
                bsd_free(dev->nameunit, M_BUS);
                dev->nameunit = NULL;
                return (error);
        }
        dc->devices[dev->unit] = dev;
        dev->devclass = dc;
        if (snprintf_s(dev->nameunit, buflen, buflen - 1, "%s%d", dc->name, dev->unit) < 0) {
                bsd_free(dev->nameunit, M_BUS);
                dev->nameunit = NULL;
                return (ENOMEM);
        }
        PDEBUG(("dev->nameunit : %s", dev->nameunit));

        return (0);
}

/**
 * @internal
 * @brief Delete a device from a devclass
 *
 * The device is removed from the devclass's device list and its unit
 * number is freed.

 * @param dc            the devclass to delete from
 * @param dev           the device to delete
 *
 * @retval 0            success
 */
static int
devclass_delete_device(devclass_t dc, device_t dev)
{
        if (!dc || !dev)
                return (0);

        PDEBUG(("%s in devclass %s", DEVICENAME(dev), DEVCLANAME(dc)));

        if (dev->devclass != dc || dc->devices[dev->unit] != dev)
                panic("devclass_delete_device: inconsistent device class");
        dc->devices[dev->unit] = NULL;
        if (dev->flags & DF_WILDCARD)
                dev->unit = -1;
        dev->devclass = NULL;
        bsd_free(dev->nameunit, M_BUS);
        dev->nameunit = NULL;

        return (0);
}

/**
 * @internal
 * @brief Make a new device and add it as a child of @p parent
 *
 * @param parent	the parent of the new device
 * @param name		the devclass name of the new device or @c NULL
 *			to leave the devclass unspecified
 * @parem unit		the unit number of the new device of @c -1 to
 *			leave the unit number unspecified
 *
 * @returns the new device
 */
static device_t
make_device(device_t parent, const char *name, int unit)
{
	device_t dev;
	devclass_t dc;

	PDEBUG(("%s at %s as unit %d", name, DEVICENAME(parent), unit));

	if (name) {
		dc = devclass_find_internal(name, NULL, TRUE);
		if (!dc) {
			printf("make_device: can't find device class %s\n",
			    name);
			return (NULL);
		}
	} else {
		dc = NULL;
	}

	dev = bsd_malloc(sizeof(struct device), 0, M_NOWAIT|M_ZERO);
	if (!dev)
		return (NULL);

	dev->parent = parent;
	TAILQ_INIT(&dev->children);
	kobj_init((kobj_t) dev, &null_class);
	dev->driver = NULL;
	dev->devclass = NULL;
	dev->unit = unit;
	dev->nameunit = NULL;
	dev->desc = NULL;
	dev->busy = 0;
	dev->devflags = 0;
	dev->flags = DF_ENABLED;
	dev->order = 0;
	if (unit == -1)
		dev->flags |= DF_WILDCARD;
	if (name) {
		dev->flags |= DF_FIXEDCLASS;
		if (devclass_add_device(dc, dev)) {
			kobj_delete((kobj_t) dev, NULL);
			return (NULL);
		}
	}
	dev->ivars = NULL;
	dev->softc = NULL;

	dev->state = DS_NOTPRESENT;

	PDEBUG(("bus_data_devices (%p) ", &bus_data_devices));
	TAILQ_INSERT_TAIL(&bus_data_devices, dev, devlink);
	bus_data_generation_update();

	PDEBUG(("%s at %s as unit %d success", name, DEVICENAME(parent), unit));
	return (dev);
}

/**
 * @internal
 * @brief Print a description of a device.
 */
static int
device_print_child(device_t dev, device_t child)
{
        int retval = 0;

        if (device_is_alive(child))
                retval += BUS_PRINT_CHILD(dev, child);
        else
                retval += device_printf(child, " not found\n");

        return (retval);
}

/**
 * @brief Create a new device
 *
 * This creates a new device and adds it as a child of an existing
 * parent device. The new device will be added after the last existing
 * child with order zero.
 *
 * @param dev		the device which will be the parent of the
 *			new child device
 * @param name		devclass name for new device or @c NULL if not
 *			specified
 * @param unit		unit number for new device or @c -1 if not
 *			specified
 *
 * @returns		the new device
 */
device_t
device_add_child(device_t dev, const char *name, int unit)
{
	return (device_add_child_ordered(dev, 0, name, unit));
}

/**
 * @brief Create a new device
 *
 * This creates a new device and adds it as a child of an existing
 * parent device. The new device will be added after the last existing
 * child with the same order.
 *
 * @param dev		the device which will be the parent of the
 *			new child device
 * @param order		a value which is used to partially sort the
 *			children of @p dev - devices created using
 *			lower values of @p order appear first in @p
 *			dev's list of children
 * @param name		devclass name for new device or @c NULL if not
 *			specified
 * @param unit		unit number for new device or @c -1 if not
 *			specified
 *
 * @returns		the new device
 */
device_t
device_add_child_ordered(device_t dev, u_int order, const char *name, int unit)
{
	device_t child;
	device_t place;

	PDEBUG(("%s at %s with order %u as unit %d",
	    name, DEVICENAME(dev), order, unit));
	KASSERT(name != NULL || unit == -1,
	    ("child device with wildcard name and specific unit number"));

	child = make_device(dev, name, unit);
	if (child == NULL)
		return (child);
	child->order = order;

	TAILQ_FOREACH(place, &dev->children, link) {
		if (place->order > order)
			break;
	}

	if (place) {
		/*
		 * The device 'place' is the first device whose order is
		 * greater than the new child.
		 */
		TAILQ_INSERT_BEFORE(place, child, link);
	} else {
		/*
		 * The new child's order is greater or equal to the order of
		 * any existing device. Add the child to the tail of the list.
		 */
		TAILQ_INSERT_TAIL(&dev->children, child, link);
	}

	bus_data_generation_update();
	PDEBUG(("%s at %s with order %u as unit %d success",
		name, DEVICENAME(dev), order, unit));
	return (child);
}

/**
 * @brief Delete a device
 *
 * This function deletes a device along with all of its children. If
 * the device currently has a driver attached to it, the device is
 * detached first using device_detach().
 *
 * @param dev           the parent device
 * @param child         the device to delete
 *
 * @retval 0            success
 * @retval non-zero     a unit error code describing the error
 */
int
device_delete_child(device_t dev, device_t child)
{
        int error;
        device_t grandchild;

        PDEBUG(("%s from %s", DEVICENAME(child), DEVICENAME(dev)));

        /* detach parent before deleting children, if any */
        if ((error = device_detach(child)) != 0)
                return (error);

        /* remove children second */
        while ((grandchild = TAILQ_FIRST(&child->children)) != NULL) {
                error = device_delete_child(child, grandchild);
                if (error)
                        return (error);
        }

        if (child->devclass)
                devclass_delete_device(child->devclass, child);
        if (child->parent)
                BUS_CHILD_DELETED(dev, child);
        TAILQ_REMOVE(&dev->children, child, link);
        TAILQ_REMOVE(&bus_data_devices, child, devlink);
        kobj_delete((kobj_t) child, M_BUS);

        bus_data_generation_update();
        return (0);
}

/**
 * @brief Delete all children devices of the given device, if any.
 *
 * This function deletes all children devices of the given device, if
 * any, using the device_delete_child() function for each device it
 * finds. If a child device cannot be deleted, this function will
 * return an error code.
 *
 * @param dev           the parent device
 *
 * @retval 0            success
 * @retval non-zero     a device would not detach
 */
int
device_delete_children(device_t dev)
{
        device_t child;
        int error;

        PDEBUG(("Deleting all children of %s", DEVICENAME(dev)));

        error = 0;

        while ((child = TAILQ_FIRST(&dev->children)) != NULL) {
                error = device_delete_child(dev, child);
                if (error) {
                        PDEBUG(("Failed deleting %s", DEVICENAME(child)));
                        break;
                }
        }
        return (error);
}

/**
 * @brief Probe a device and attach a driver if possible
 *
 * calls device_probe() and attaches if that was successful.
 */
int
device_probe_and_attach(device_t dev)
{
	int error;

        PDEBUG(("+"));
	GIANT_REQUIRED;

	error = device_probe(dev);
	if (error == -1)
		return (0);
	else if (error != 0)
		return (error);

	//CURVNET_SET_QUIET(vnet0);
	error = device_attach(dev);
	//CURVNET_RESTORE();
        PDEBUG(("-"));
	return error;
}

/**
 * @brief Attach a device driver to a device
 *
 * This function is a wrapper around the DEVICE_ATTACH() driver
 * method. In addition to calling DEVICE_ATTACH(), it initialises the
 * device's sysctl tree, optionally prints a description of the device
 * and queues a notification event for user-based device management
 * services.
 *
 * Normally this function is only called internally from
 * device_probe_and_attach().
 *
 * @param dev           the device to initialise
 *
 * @retval 0            success
 * @retval ENXIO        no driver was found
 * @retval ENOMEM       memory allocation failure
 * @retval non-zero     some other unix error code
 */
int
device_attach(device_t dev)
{
        uint64_t attachtime;
        int error;
        PDEBUG(("+"));

        //if (resource_disabled(dev->driver->name, dev->unit)) {
        //        device_disable(dev);
        //        if (bootverbose)
        //                 device_printf(dev, "disabled via hints entry\n");
        //        return (ENXIO);
        //}

        //device_sysctl_init(dev);
        if (!device_is_quiet(dev))
                device_print_child(dev->parent, dev);
        // attachtime = get_cyclecount();
        dev->state = DS_ATTACHING;
        if ((error = DEVICE_ATTACH(dev)) != 0) {
                printf("device_attach: %s%d attach returned %d\n",
                    dev->driver->name, dev->unit, error);
                if (!(dev->flags & DF_FIXEDCLASS))
                        devclass_delete_device(dev->devclass, dev);
                (void)device_set_driver(dev, NULL);
                //device_sysctl_fini(dev);
                KASSERT(dev->busy == 0, ("attach failed but busy"));
                dev->state = DS_NOTPRESENT;
                return (error);
        }
        // attachtime = get_cyclecount() - attachtime;
        /*
         * 4 bits per device is a reasonable value for desktop and server
         * hardware with good get_cyclecount() implementations, but WILL
         * need to be adjusted on other platforms.
         */
#define RANDOM_PROBE_BIT_GUESS  4
        if (bootverbose)
                printf("random: harvesting attach, %zu bytes (%d bits) from %s%d\n",
                    sizeof(attachtime), RANDOM_PROBE_BIT_GUESS,
                    dev->driver->name, dev->unit);
        //random_harvest_direct(&attachtime, sizeof(attachtime),
        //    RANDOM_PROBE_BIT_GUESS, RANDOM_ATTACH);
        //device_sysctl_update(dev);
        if (dev->busy)
                dev->state = DS_BUSY;
        else
                dev->state = DS_ATTACHED;
        dev->flags &= ~DF_DONENOMATCH;
        //EVENTHANDLER_INVOKE(device_attach, dev);
        //devadded(dev);
        PDEBUG(("-"));
        return (0);
}

/**
 * @brief Probe a device, and return this status.
 *
 * This function is the core of the device autoconfiguration
 * system. Its purpose is to select a suitable driver for a device and
 * then call that driver to initialise the hardware appropriately. The
 * driver is selected by calling the DEVICE_PROBE() method of a set of
 * candidate drivers and then choosing the driver which returned the
 * best value. This driver is then attached to the device using
 * device_attach().
 *
 * The set of suitable drivers is taken from the list of drivers in
 * the parent device's devclass. If the device was originally created
 * with a specific class name (see device_add_child()), only drivers
 * with that name are probed, otherwise all drivers in the devclass
 * are probed. If no drivers return successful probe values in the
 * parent devclass, the search continues in the parent of that
 * devclass (see devclass_get_parent()) if any.
 *
 * @param dev		the device to initialise
 *
 * @retval 0		success
 * @retval ENXIO	no driver was found
 * @retval ENOMEM	memory allocation failure
 * @retval non-zero	some other unix error code
 * @retval -1		Device already attached
 */
int
device_probe(device_t dev)
{
	int error;

	GIANT_REQUIRED;
        PDEBUG(("+"));

	if (dev->state >= DS_ALIVE && (dev->flags & DF_REBID) == 0)
		return (-1);

	if (!(dev->flags & DF_ENABLED)) {
		if (bootverbose && device_get_name(dev) != NULL) {
			device_print_prettyname(dev);
			printf("not probed (disabled)\n");
		}
		return (-1);
	}
	if ((error = device_probe_child(dev->parent, dev)) != 0) {
		if (bus_current_pass == BUS_PASS_DEFAULT &&
		    !(dev->flags & DF_DONENOMATCH)) {
			BUS_PROBE_NOMATCH(dev->parent, dev);
			//devnomatch(dev);
			dev->flags |= DF_DONENOMATCH;
		}
		return (error);
	}
        PDEBUG(("-"));
	return (0);
}

/**
 * @brief Tells a driver to quiesce itself.
 *
 * This function is a wrapper around the DEVICE_QUIESCE() driver
 * method. If the call to DEVICE_QUIESCE() succeeds.
 *
 * @param dev           the device to quiesce
 *
 * @retval 0            success
 * @retval ENXIO        no driver was found
 * @retval ENOMEM       memory allocation failure
 * @retval non-zero     some other unix error code
 */
int
device_quiesce(device_t dev)
{

        PDEBUG(("%s", DEVICENAME(dev)));
        if (dev->state == DS_BUSY)
                return (EBUSY);
        if (dev->state != DS_ATTACHED)
                return (0);

        return (DEVICE_QUIESCE(dev));
}

/**
 * @brief Notify a device of system shutdown
 *
 * This function calls the DEVICE_SHUTDOWN() driver method if the
 * device currently has an attached driver.
 *
 * @returns the value returned by DEVICE_SHUTDOWN()
 */
int
device_shutdown(device_t dev)
{
        if (dev->state < DS_ATTACHED)
                return (0);
        return (DEVICE_SHUTDOWN(dev));
}

// bus
//
//
device_t
bus_generic_add_child(device_t dev, u_int order, const char *name, int unit)
{

        return (device_add_child_ordered(dev, order, name, unit));
}

/**
 * @brief Helper function for implementing DEVICE_PROBE()
 *
 * This function can be used to help implement the DEVICE_PROBE() for
 * a bus (i.e. a device which has other devices attached to it). It
 * calls the DEVICE_IDENTIFY() method of each driver in the device's
 * devclass.
 */
int
bus_generic_probe(device_t dev)
{
        devclass_t dc = dev->devclass;
        driverlink_t dl = NULL;
        PDEBUG(("+"));

        TAILQ_FOREACH(dl, &dc->drivers, link) {
                /*
                 * If this driver's pass is too high, then ignore it.
                 * For most drivers in the default pass, this will
                 * never be true.  For early-pass drivers they will
                 * only call the identify routines of eligible drivers
                 * when this routine is called.  Drivers for later
                 * passes should have their identify routines called
                 * on early-pass busses during BUS_NEW_PASS().
                 */
                if (dl->pass > bus_current_pass)
                        continue;
                DEVICE_IDENTIFY(dl->driver, dev);
        }

        PDEBUG(("-"));
        return (0);
}

/**
 * @brief Helper function for implementing DEVICE_ATTACH()
 *
 * This function can be used to help implement the DEVICE_ATTACH() for
 * a bus. It calls device_probe_and_attach() for each of the device's
 * children.
 */
int
bus_generic_attach(device_t dev)
{
        device_t child;

        PDEBUG(("+"));
        TAILQ_FOREACH(child, &dev->children, link) {
                device_probe_and_attach(child);
        }
        PDEBUG(("-"));
        return (0);
}

/**
 * @brief Helper function for implementing DEVICE_DETACH()
 *
 * This function can be used to help implement the DEVICE_DETACH() for
 * a bus. It calls device_detach() for each of the device's
 * children.
 */
int
bus_generic_detach(device_t dev)
{
        device_t child;
        int error;

        if (dev->state != DS_ATTACHED)
                return (EBUSY);

        /*
         * Detach children in the reverse order.
         * See bus_generic_suspend for details.
         */
        TAILQ_FOREACH_REVERSE(child, &dev->children, device_list, link) {
                if ((error = device_detach(child)) != 0)
                        return (error);
        }

        return (0);
}

/**
 * @brief Helper function for implementing DEVICE_SHUTDOWN()
 *
 * This function can be used to help implement the DEVICE_SHUTDOWN()
 * for a bus. It calls device_shutdown() for each of the device's
 * children.
 */
int
bus_generic_shutdown(device_t dev)
{
        device_t child;

        /*
         * Shut down children in the reverse order.
         * See bus_generic_suspend for details.
         */
        TAILQ_FOREACH_REVERSE(child, &dev->children, device_list, link) {
                device_shutdown(child);
        }

        return (0);
}

/**
 * @brief Default function for suspending a child device.
 *
 * This function is to be used by a bus's DEVICE_SUSPEND_CHILD().
 */
int
bus_generic_suspend_child(device_t dev, device_t child)
{
        int     error;

        error = DEVICE_SUSPEND(child);

        if (error == 0)
                child->flags |= DF_SUSPENDED;

        return (error);
}

/**
 * @brief Default function for resuming a child device.
 *
 * This function is to be used by a bus's DEVICE_RESUME_CHILD().
 */
int
bus_generic_resume_child(device_t dev, device_t child)
{

        DEVICE_RESUME(child);
        child->flags &= ~DF_SUSPENDED;

        return (0);
}

/**
 * @brief Helper function for implementing DEVICE_SUSPEND()
 *
 * This function can be used to help implement the DEVICE_SUSPEND()
 * for a bus. It calls DEVICE_SUSPEND() for each of the device's
 * children. If any call to DEVICE_SUSPEND() fails, the suspend
 * operation is aborted and any devices which were suspended are
 * resumed immediately by calling their DEVICE_RESUME() methods.
 */
int
bus_generic_suspend(device_t dev)
{
        int             error;
        device_t        child;

        /*
         * Suspend children in the reverse order.
         * For most buses all children are equal, so the order does not matter.
         * Other buses, such as acpi, carefully order their child devices to
         * express implicit dependencies between them.  For such buses it is
         * safer to bring down devices in the reverse order.
         */
        TAILQ_FOREACH_REVERSE(child, &dev->children, device_list, link) {
                error = BUS_SUSPEND_CHILD(dev, child);
                if (error != 0) {
                        child = TAILQ_NEXT(child, link);
                        if (child != NULL) {
                                TAILQ_FOREACH_FROM(child, &dev->children, link)
                                        BUS_RESUME_CHILD(dev, child);
                        }
                        return (error);
                }
        }
        return (0);
}

/**
 * @brief Helper function for implementing DEVICE_RESUME()
 *
 * This function can be used to help implement the DEVICE_RESUME() for
 * a bus. It calls DEVICE_RESUME() on each of the device's children.
 */
int
bus_generic_resume(device_t dev)
{
        device_t        child;

        TAILQ_FOREACH(child, &dev->children, link) {
                BUS_RESUME_CHILD(dev, child);
                /* if resume fails, there's nothing we can usefully do... */
        }
        return (0);
}



/**
 * @brief Helper function for implementing BUS_PRINT_CHILD().
 *
 * This function prints the first part of the ascii representation of
 * @p child, including its name, unit and description (if any - see
 * device_set_desc()).
 *
 * @returns the number of characters printed
 */
int
bus_print_child_header(device_t dev, device_t child)
{
        int     retval = 0;

        if (device_get_desc(child)) {
                retval += device_printf(child, "<%s>", device_get_desc(child));
        } else {
                retval += printf("%s", device_get_nameunit(child));
        }

        return (retval);
}

/**
 * @brief Helper function for implementing BUS_PRINT_CHILD().
 *
 * This function prints the last part of the ascii representation of
 * @p child, which consists of the string @c " on " followed by the
 * name and unit of the @p dev.
 *
 * @returns the number of characters printed
 */
int
bus_print_child_footer(device_t dev, device_t child)
{
        return (printf(" on %s\n", device_get_nameunit(dev)));
}

/**
 * @brief Helper function for implementing BUS_PRINT_CHILD().
 *
 * This function prints out the VM domain for the given device.
 *
 * @returns the number of characters printed
 */
int
bus_print_child_domain(device_t dev, device_t child)
{
        int domain;

        /* No domain? Don't print anything */
        if (BUS_GET_DOMAIN(dev, child, &domain) != 0)
                return (0);

        return (printf(" numa-domain %d", domain));
}

/**
 * @brief Helper function for implementing BUS_PRINT_CHILD().
 *
 * This function simply calls bus_print_child_header() followed by
 * bus_print_child_footer().
 *
 * @returns the number of characters printed
 */
int
bus_generic_print_child(device_t dev, device_t child)
{
        int     retval = 0;

        retval += bus_print_child_header(dev, child);
        retval += bus_print_child_domain(dev, child);
        retval += bus_print_child_footer(dev, child);

        return (retval);
}

/**
 * @brief Helper function for implementing BUS_DRIVER_ADDED().
 *
 * This implementation of BUS_DRIVER_ADDED() simply calls the driver's
 * DEVICE_IDENTIFY() method to allow it to add new children to the bus
 * and then calls device_probe_and_attach() for each unattached child.
 */
void
bus_generic_driver_added(device_t dev, driver_t *driver)
{
        device_t child;
        PDEBUG(("+"));

        DEVICE_IDENTIFY(driver, dev);
        PDEBUG(("dev->children %p", dev->children));
        TAILQ_FOREACH(child, &dev->children, link) {
                if (child->state == DS_NOTPRESENT ||
                    (child->flags & DF_REBID))
                        device_probe_and_attach(child);
        }
        PDEBUG(("-"));
}

/**
 * @brief Helper function for implementing BUS_NEW_PASS().
 *
 * This implementing of BUS_NEW_PASS() first calls the identify
 * routines for any drivers that probe at the current pass.  Then it
 * walks the list of devices for this bus.  If a device is already
 * attached, then it calls BUS_NEW_PASS() on that device.  If the
 * device is not already attached, it attempts to attach a driver to
 * it.
 */
void
bus_generic_new_pass(device_t dev)
{
        driverlink_t dl = NULL;
        devclass_t dc;
        device_t child;

        dc = dev->devclass;
        TAILQ_FOREACH(dl, &dc->drivers, link) {
                if (dl->pass == bus_current_pass)
                        DEVICE_IDENTIFY(dl->driver, dev);
        }
        TAILQ_FOREACH(child, &dev->children, link) {
                if (child->state >= DS_ATTACHED)
                        BUS_NEW_PASS(child);
                else if (child->state == DS_NOTPRESENT)
                        device_probe_and_attach(child);
        }
}

// delete resouce and intr

/**
 * @brief Helper function for implementing BUS_CHILD_PRESENT().
 *
 * This simple implementation of BUS_CHILD_PRESENT() simply calls the
 * BUS_CHILD_PRESENT() method of the parent of @p dev.
 */
int
bus_generic_child_present(device_t dev, device_t child)
{
        return (BUS_CHILD_PRESENT(device_get_parent(dev), dev));
}

int
bus_generic_get_domain(device_t dev, device_t child, int *domain)
{

        if (dev->parent)
                return (BUS_GET_DOMAIN(dev->parent, dev, domain));

        return (ENOENT);
}

/**
 * @brief Helper function for implementing BUS_RESCAN().
 *
 * This null implementation of BUS_RESCAN() always fails to indicate
 * the bus does not support rescanning.
 */
int
bus_null_rescan(device_t dev)
{

        return (ENXIO);
}

/**
 * @brief Wrapper function for BUS_CHILD_PRESENT().
 *
 * This function simply calls the BUS_CHILD_PRESENT() method of the
 * parent of @p dev.
 */
int
bus_child_present(device_t child)
{
        return (BUS_CHILD_PRESENT(device_get_parent(child), child));
}

/**
 * @brief Wrapper function for BUS_GET_DOMAIN().
 *
 * This function simply calls the BUS_GET_DOMAIN() method of the
 * parent of @p dev.
 */
int
bus_get_domain(device_t dev, int *domain)
{
        return (BUS_GET_DOMAIN(device_get_parent(dev), dev, domain));
}

int
bus_data_generation_check(int generation)
{
	if (generation != bus_data_generation)
	return (1);

	/* XXX generate optimised lists here? */
	return (0);
}

void
bus_data_generation_update(void)
{
	bus_data_generation++;
}

/**
 * @brief Print the name of the device followed by a colon and a space
 *
 * @returns the number of characters printed
 */
int
device_print_prettyname(device_t dev)
{
	const char *name = device_get_name(dev);

	if (name == NULL)
		return (printf("unknown: "));
	return (printf("%s%d: ", name, device_get_unit(dev)));
}

/**
 * @brief Return the device's unit number.
 */
int
device_get_unit(device_t dev)
{
	return (dev->unit);
}

/**
 * @internal
 */
static driverlink_t
first_matching_driver(devclass_t dc, device_t dev)
{
	if (dev->devclass)
		return (devclass_find_driver_internal(dc, dev->devclass->name));
	return (TAILQ_FIRST(&dc->drivers));
}

/**
 * @internal
 */
static driverlink_t
next_matching_driver(devclass_t dc, device_t dev, driverlink_t last)
{
	if (dev->devclass) {
		driverlink_t dl;
		for (dl = TAILQ_NEXT(last, link); dl; dl = TAILQ_NEXT(dl, link))
			if (!strcmp(dev->devclass->name, dl->driver->name))
				return (dl);
		return (NULL);
	}
	return (TAILQ_NEXT(last, link));
}


/**
 * @brief Set the devclass of a device
 * @see devclass_add_device().
 */
int
device_set_devclass(device_t dev, const char *classname)
{
	devclass_t dc;
	int error;

	if (!classname) {
		if (dev->devclass)
			devclass_delete_device(dev->devclass, dev);
		return (0);
	}

	if (dev->devclass) {
		printf("device_set_devclass: device class already set\n");
		return (EINVAL);
	}

	dc = devclass_find_internal(classname, NULL, TRUE);
	if (!dc)
		return (ENOMEM);

	error = devclass_add_device(dc, dev);

	bus_data_generation_update();
	return (error);
}

/**
 * @brief Detach a driver from a device
 *
 * This function is a wrapper around the DEVICE_DETACH() driver
 * method. If the call to DEVICE_DETACH() succeeds, it calls
 * BUS_CHILD_DETACHED() for the parent of @p dev, queues a
 * notification event for user-based device management services and
 * cleans up the device's sysctl tree.
 *
 * @param dev		the device to un-initialise
 *
 * @retval 0		success
 * @retval ENXIO	no driver was found
 * @retval ENOMEM	memory allocation failure
 * @retval non-zero	some other unix error code
 */
int
device_detach(device_t dev)
{
	int error;

	GIANT_REQUIRED;

	PDEBUG(("%s", DEVICENAME(dev)));
	if (dev->state == DS_BUSY)
		return (EBUSY);
	if (dev->state == DS_ATTACHING) {
		device_printf(dev, "device in attaching state! Deferring detach.\n");
		return (EBUSY);
	}
	if (dev->state != DS_ATTACHED)
		return (0);

	if ((error = DEVICE_DETACH(dev)) != 0) {
		return (error);
	}

	if (!device_is_quiet(dev))
		device_printf(dev, "detached\n");
	if (dev->parent) {
		PDEBUG(("BUS_CHILD_DETACHED %s", DEVICENAME(dev->parent)));
		BUS_CHILD_DETACHED(dev->parent, dev);
	}

	if (!(dev->flags & DF_FIXEDCLASS)) {
		PDEBUG(("devclass_delete_device"));
		devclass_delete_device(dev->devclass, dev);
	}

	device_verbose(dev);
	dev->state = DS_NOTPRESENT;
	(void)device_set_driver(dev, NULL);

	return (0);
}

/**
 * @brief Return the parent of a device
 */
device_t
device_get_parent(device_t dev)
{
	return (dev->parent);
}

/**
 * @brief Print the name of the device followed by a colon, a space
 * and the result of calling vprintf() with the value of @p fmt and
 * the following arguments.
 *
 * @returns the number of characters printed
 */
int
device_printf(device_t dev, const char * fmt, ...)
{
	va_list ap;
	int retval;

	retval = device_print_prettyname(dev);
	va_start(ap, fmt);
	retval += vprintf(fmt, ap);
	va_end(ap);
	return (retval);
}

/**
 * @brief Set the driver of a device
 *
 * @retval 0		success
 * @retval EBUSY	the device already has a driver attached
 * @retval ENOMEM	a memory allocation failure occurred
 */
int
device_set_driver(device_t dev, driver_t *driver)
{
	if (dev->state >= DS_ATTACHED)
		return (EBUSY);

	if (dev->driver == driver)
		return (0);

	if (dev->softc && !(dev->flags & DF_EXTERNALSOFTC)) {
		bsd_free(dev->softc, M_BUS_SC);
		dev->softc = NULL;
	}
	device_set_desc(dev, NULL);
	kobj_delete((kobj_t) dev, NULL);
	dev->driver = driver;
	if (driver) {
		kobj_init((kobj_t) dev, (kobj_class_t) driver);
		if (!(dev->flags & DF_EXTERNALSOFTC) && driver->size > 0) {
			dev->softc = bsd_malloc(driver->size, M_BUS_SC,
			    M_NOWAIT | M_ZERO);
			if (!dev->softc) {
				kobj_delete((kobj_t) dev, NULL);
				kobj_init((kobj_t) dev, &null_class);
				dev->driver = NULL;
				return (ENOMEM);
			}
		}
	} else {
		kobj_init((kobj_t) dev, &null_class);
	}

	bus_data_generation_update();
	return (0);
}

/**
 * @internal
 */
int
device_probe_child(device_t dev, device_t child)
{
	devclass_t dc;
	driverlink_t best = NULL;
	driverlink_t dl = NULL;
	int result, pri = 0;
	int hasclass = (child->devclass != NULL);

	GIANT_REQUIRED;

	dc = dev->devclass;
	if (!dc)
		panic("device_probe_child: parent device has no devclass");

	/*
	 * If the state is already probed, then return.  However, don't
	 * return if we can rebid this object.
	 */
	if (child->state == DS_ALIVE && (child->flags & DF_REBID) == 0)
		return (0);

	for (; dc; dc = dc->parent) {
		for (dl = first_matching_driver(dc, child);
		     dl;
		     dl = next_matching_driver(dc, child, dl)) {
			/* If this driver's pass is too high, then ignore it. */
			if (dl->pass > bus_current_pass)
				continue;

			PDEBUG(("Trying %s", DRIVERNAME(dl->driver)));
			result = device_set_driver(child, dl->driver);
			if (result == ENOMEM)
				return (result);
			else if (result != 0)
				continue;
			if (!hasclass) {
				if (device_set_devclass(child,
				    dl->driver->name) != 0) {
					char const * devname =
					    device_get_name(child);
					if (devname == NULL)
						devname = "(unknown)";
					printf("driver bug: Unable to set "
					    "devclass (class: %s "
					    "devname: %s)\n",
					    dl->driver->name,
					    devname);
					(void)device_set_driver(child, NULL);
					continue;
				}
			}

			/* Fetch any flags for the device before probing. */
			// resource_int_value(dl->driver->name, child->unit,
			    // "flags", &child->devflags);
                        PDEBUG(("start DEVICE_PROBE"));
			result = DEVICE_PROBE(child);

			/* Reset flags and devclass before the next probe. */
			child->devflags = 0;
			if (!hasclass)
				(void)device_set_devclass(child, NULL);

			/*
			 * If the driver returns SUCCESS, there can be
			 * no higher match for this device.
			 */
			if (result == 0) {
				best = dl;
				pri = 0;
				break;
			}

			/*
			 * Reset DF_QUIET in case this driver doesn't
			 * end up as the best driver.
			 */
			device_verbose(child);

                        PDEBUG(("probe result: %d", result));
			/*
			 * Probes that return BUS_PROBE_NOWILDCARD or lower
			 * only match on devices whose driver was explicitly
			 * specified.
			 */
			if (result <= BUS_PROBE_NOWILDCARD &&
			    !(child->flags & DF_FIXEDCLASS)) {
				result = ENXIO;
			}

			/*
			 * The driver returned an error so it
			 * certainly doesn't match.
			 */
			if (result > 0) {
				(void)device_set_driver(child, NULL);
				continue;
			}

			/*
			 * A priority lower than SUCCESS, remember the
			 * best matching driver. Initialise the value
			 * of pri for the first match.
			 */
			if (best == NULL || result > pri) {
				best = dl;
				pri = result;
				continue;
			}
		}
		/*
		 * If we have an unambiguous match in this devclass,
		 * don't look in the parent.
		 */
		if (best && pri == 0)
			break;
	}

	/*
	 * If we found a driver, change state and initialise the devclass.
	 */
	/* XXX What happens if we rebid and got no best? */
	if (best) {
                PDEBUG(("in best"));
		/*
		 * If this device was attached, and we were asked to
		 * rescan, and it is a different driver, then we have
		 * to detach the old driver and reattach this new one.
		 * Note, we don't have to check for DF_REBID here
		 * because if the state is > DS_ALIVE, we know it must
		 * be.
		 *
		 * This assumes that all DF_REBID drivers can have
		 * their probe routine called at any time and that
		 * they are idempotent as well as completely benign in
		 * normal operations.
		 *
		 * We also have to make sure that the detach
		 * succeeded, otherwise we fail the operation (or
		 * maybe it should just fail silently?  I'm torn).
		 */
		if (child->state > DS_ALIVE && best->driver != child->driver)
			if ((result = device_detach(dev)) != 0)
				return (result);

		/* Set the winning driver, devclass, and flags. */
		if (!child->devclass) {
			result = device_set_devclass(child, best->driver->name);
			if (result != 0)
				return (result);
		}
		result = device_set_driver(child, best->driver);
		if (result != 0)
			return (result);
		// resource_int_value(best->driver->name, child->unit,
		    // "flags", &child->devflags);

		if (pri < 0) {
			/*
			 * A bit bogus. Call the probe method again to make
			 * sure that we have the right description.
			 */
			DEVICE_PROBE(child);
#if 0
			child->flags |= DF_REBID;
#endif
		} else
			child->flags &= ~DF_REBID;
		child->state = DS_ALIVE;

		bus_data_generation_update();
                PDEBUG(("-"));
		return (0);
	}

        PDEBUG(("ENXIO -"));
	return (ENXIO);
}


/**
 * @brief Return the current devclass for the device or @c NULL if
 * there is none.
 */
devclass_t
device_get_devclass(device_t dev)
{
	return (dev->devclass);
}

/**
 * @brief Initialise a resource list.
 *
 * @param rl		the resource list to initialise
 */
void
resource_list_init(struct resource_list *rl)
{
	STAILQ_INIT(rl);
}

/**
 * @brief Reclaim memory used by a resource list.
 *
 * This function frees the memory for all resource entries on the list
 * (if any).
 *
 * @param rl		the resource list to free
 */
void
resource_list_free(struct resource_list *rl)
{
	struct resource_list_entry *rle;

	while ((rle = STAILQ_FIRST(rl)) != NULL) {
		if (rle->res)
			bsd_free(rle->res, M_BUS);
		STAILQ_REMOVE_HEAD(rl, link);
		bsd_free(rle, M_BUS);
	}
}

/**
 * @brief Add or modify a resource entry.
 *
 * If an existing entry exists with the same type and rid, it will be
 * modified using the given values of @p start, @p end and @p
 * count. If no entry exists, a new one will be created using the
 * given values.  The resource list entry that matches is then returned.
 *
 * @param rl		the resource list to edit
 * @param type		the resource entry type (e.g. SYS_RES_MEMORY)
 * @param rid		the resource identifier
 * @param start		the start address of the resource
 * @param end		the end address of the resource
 * @param count		XXX end-start+1
 */
struct resource_list_entry *
resource_list_add(struct resource_list *rl, int type, int rid,
    rman_res_t start, rman_res_t end, rman_res_t count)
{
	struct resource_list_entry *rle;

	rle = resource_list_find(rl, type, rid);
	if (!rle) {
		rle = bsd_malloc(sizeof(struct resource_list_entry), M_BUS,
		    M_NOWAIT);
		if (!rle)
			panic("resource_list_add: can't record entry");
		STAILQ_INSERT_TAIL(rl, rle, link);
		rle->type = type;
		rle->rid = rid;
		rle->res = NULL;
		rle->flags = 0;
	}

	if (rle->res)
		panic("resource_list_add: resource entry is busy");

	rle->res = bsd_malloc(sizeof(struct resource), M_BUS, M_NOWAIT);
	if (rle->res == NULL) {
		panic("resource_list_add: resource is busy");
	}
	rle->res->start = start;
	rle->res->end = end;
	rle->res->count = count;
	return (rle);
}

/**
 * @brief Find a resource entry by type and rid.
 *
 * @param rl		the resource list to search
 * @param type		the resource entry type (e.g. SYS_RES_MEMORY)
 * @param rid		the resource identifier
 *
 * @returns the resource entry pointer or NULL if there is no such
 * entry.
 */
struct resource_list_entry *
resource_list_find(struct resource_list *rl, int type, int rid)
{
	struct resource_list_entry *rle = NULL;

	STAILQ_FOREACH(rle, rl, link) {
		if (rle->type == type && rle->rid == rid)
			return (rle);
	}
	return (NULL);
}

/**
 * @brief Wrapper function for BUS_ALLOC_RESOURCE().
 *
 * This function simply calls the BUS_ALLOC_RESOURCE() method of the
 * parent of @p dev.
 */
struct resource *
bus_alloc_resource(device_t dev, int type, int *rid, rman_res_t start,
    rman_res_t end, rman_res_t count, u_int flags)
{
	struct resource *res = NULL;

	if (dev->parent == NULL)
		return (NULL);
	res = BUS_ALLOC_RESOURCE(dev->parent, dev, type, rid, start, end,
	    count, flags);
	return (res);
}

// root driver
static int
root_print_child(device_t dev, device_t child)
{
        int     retval = 0;

        retval += bus_print_child_header(dev, child);
        retval += printf("\n");

        return (retval);
}

static kobj_method_t root_methods[] = {
	/* Device interface */
	KOBJMETHOD(device_shutdown,     bus_generic_shutdown),
	KOBJMETHOD(device_suspend,      bus_generic_suspend),
	KOBJMETHOD(device_resume,       bus_generic_resume),

				        /* Bus interface */
	KOBJMETHOD(bus_print_child,     root_print_child),

	KOBJMETHOD_END
};

static driver_t root_driver = {
	"root",
	root_methods,
	1,                      /* no softc */
};

device_t        root_bus;
devclass_t      root_devclass;

static int
root_bus_module_handler(module_t mod, int what, void* arg)
{
        PDEBUG(("+"));
        switch (what) {
        case MOD_LOAD:
                TAILQ_INIT(&bus_data_devices);
                kobj_class_compile((kobj_class_t) &root_driver);
                root_bus = make_device(NULL, "root", 0);
                root_bus->desc = "System root bus";
                kobj_init((kobj_t) root_bus, (kobj_class_t) &root_driver);
                root_bus->driver = &root_driver;
                root_bus->state = DS_ATTACHED;
                root_devclass = devclass_find_internal("root", NULL, FALSE);
                //devinit();
                return (0);

        case MOD_SHUTDOWN:
                device_shutdown(root_bus);
                return (0);
        default:
                return (EOPNOTSUPP);
        }
        PDEBUG(("-"));

        return (0);
}

/**
 * @brief Automatically configure devices
 *
 * This function begins the autoconfiguration process by calling
 * device_probe_and_attach() for each child of the @c root0 device.
 */
void
root_bus_configure(void)
{
	PDEBUG(("+"));
        root_bus_module_handler(NULL, MOD_LOAD, NULL);

	/* Eventually this will be split up, but this is sufficient for now. */
	bus_set_pass(BUS_PASS_DEFAULT);
	PDEBUG(("-"));
}

/**
 * @brief Module handler for registering device drivers
 *
 * This module handler is used to automatically register device
 * drivers when modules are loaded. If @p what is MOD_LOAD, it calls
 * devclass_add_driver() for the driver described by the
 * driver_module_data structure pointed to by @p arg
 */
int
driver_module_handler(module_t mod, int what, void *arg)
{
        struct driver_module_data *dmd = NULL;
        devclass_t bus_devclass;
        kobj_class_t driver;
        int error, pass;

        PDEBUG(("+"));

        dmd = (struct driver_module_data *)arg;
        bus_devclass = devclass_find_internal(dmd->dmd_busname, NULL, TRUE);
        if (bus_devclass == NULL) {
                PDEBUG(("-"));
                return EINVAL;
        }

        error = 0;

        switch (what) {
        case MOD_LOAD:
                if (dmd->dmd_chainevh)
                        error = dmd->dmd_chainevh(mod,what,dmd->dmd_chainarg);

                pass = dmd->dmd_pass;
                driver = dmd->dmd_driver;
                PDEBUG(("Loading module: driver %s on bus %s (pass %d)",
                    DRIVERNAME(driver), dmd->dmd_busname, pass));
                error = devclass_add_driver(bus_devclass, driver, pass,
                    dmd->dmd_devclass);
                break;

        case MOD_UNLOAD:
                PDEBUG(("Unloading module: driver %s from bus %s",
                    DRIVERNAME(dmd->dmd_driver),
                    dmd->dmd_busname));
                error = devclass_delete_driver(bus_devclass,
                    dmd->dmd_driver);

                if (!error && dmd->dmd_chainevh)
                        error = dmd->dmd_chainevh(mod,what,dmd->dmd_chainarg);
                break;
        case MOD_QUIESCE:
                PDEBUG(("Quiesce module: driver %s from bus %s",
                    DRIVERNAME(dmd->dmd_driver),
                    dmd->dmd_busname));
                error = devclass_quiesce_driver(bus_devclass,
                    dmd->dmd_driver);

                if (!error && dmd->dmd_chainevh)
                        error = dmd->dmd_chainevh(mod,what,dmd->dmd_chainarg);
                break;
        default:
                error = EOPNOTSUPP;
                break;
        }
        PDEBUG(("-"));

        return (error);
}

#ifdef BUS_DEBUG

/* the _short versions avoid iteration by not calling anything that prints
 * more than oneliners. I love oneliners.
 */

static void
print_device_short(device_t dev, int indent)
{
        if (!dev)
                return;

        indentprintf(("device %d: <%s> %sparent,%schildren,%s%s%s%s%s,%sivars,%ssoftc,busy=%d\n",
            dev->unit, dev->desc,
            (dev->parent? "":"no "),
            (TAILQ_EMPTY(&dev->children)? "no ":""),
            (dev->flags&DF_ENABLED? "enabled,":"disabled,"),
            (dev->flags&DF_FIXEDCLASS? "fixed,":""),
            (dev->flags&DF_WILDCARD? "wildcard,":""),
            (dev->flags&DF_DESCMALLOCED? "descmalloced,":""),
            (dev->flags&DF_REBID? "rebiddable,":""),
            (dev->ivars? "":"no "),
            (dev->softc? "":"no "),
            dev->busy));
}

static void
print_device(device_t dev, int indent)
{
        if (!dev)
                return;

        print_device_short(dev, indent);

        indentprintf(("Parent:\n"));
        print_device_short(dev->parent, indent+1);
        indentprintf(("Driver:\n"));
        print_driver_short(dev->driver, indent+1);
        indentprintf(("Devclass:\n"));
        print_devclass_short(dev->devclass, indent+1);
}

void
print_device_tree_short(device_t dev, int indent)
/* print the device and all its children (indented) */
{
        device_t child;

        if (!dev)
                return;

        print_device_short(dev, indent);

        TAILQ_FOREACH(child, &dev->children, link) {
                print_device_tree_short(child, indent+1);
        }
}

void
print_device_tree(device_t dev, int indent)
/* print the device and all its children (indented) */
{
        device_t child;

        if (!dev)
                return;

        print_device(dev, indent);

        TAILQ_FOREACH(child, &dev->children, link) {
                print_device_tree(child, indent+1);
        }
}

static void
print_driver_short(driver_t *driver, int indent)
{
        if (!driver)
                return;

        indentprintf(("driver %s: softc size = %zd\n",
            driver->name, driver->size));
}

static void
print_driver(driver_t *driver, int indent)
{
        if (!driver)
                return;

        print_driver_short(driver, indent);
}

static void
print_driver_list(driver_list_t drivers, int indent)
{
        driverlink_t driver = NULL;

        TAILQ_FOREACH(driver, &drivers, link) {
                print_driver(driver->driver, indent);
        }
}

static void
print_devclass_short(devclass_t dc, int indent)
{
        if ( !dc )
                return;

        indentprintf(("devclass %s: max units = %d\n", dc->name, dc->maxunit));
}

static void
print_devclass(devclass_t dc, int indent)
{
        int i;

        if ( !dc )
                return;

        print_devclass_short(dc, indent);
        indentprintf(("Drivers:\n"));
        print_driver_list(dc->drivers, indent+1);

        indentprintf(("Devices:\n"));
        for (i = 0; i < dc->maxunit; i++)
                if (dc->devices[i])
                        print_device(dc->devices[i], indent+1);
}

void
print_devclass_list_short(void)
{
        devclass_t dc;

        printf("Short listing of devclasses, drivers & devices:\n");
        TAILQ_FOREACH(dc, &devclasses, link) {
                print_devclass_short(dc, 0);
        }
}

void
print_devclass_list(void)
{
        devclass_t dc;

        printf("Full listing of devclasses, drivers & devices:\n");
        TAILQ_FOREACH(dc, &devclasses, link) {
                print_devclass(dc, 0);
        }
}

#endif

/* port for interrupt setup and teardown */
int
bus_setup_intr(int irq, int flags, driver_intr_t *intr, void *arg)
{
        int ret;
        HwiIrqParam irqParam = {0};

        if (OS_INT_ACTIVE) {
                return OS_ERRNO_HWI_INTERR;
        }

        irqParam.swIrq  = irq;
        irqParam.pDevId = arg;

        ret = LOS_HwiCreate(irq, 0, (HWI_MODE_T)flags, (HWI_PROC_FUNC)intr, &irqParam);
        if (ret == LOS_OK) {
                HalIrqUnmask(irq);
        }
        return ret;
}
int
bus_teardown_intr(int irq, void *arg)
{
    HwiIrqParam irqParam = {0};

    if (OS_INT_ACTIVE) {
        return -1;
    }

    irqParam.swIrq  = irq;
    irqParam.pDevId = arg;

    return LOS_HwiDelete(irq, &irqParam);
}
