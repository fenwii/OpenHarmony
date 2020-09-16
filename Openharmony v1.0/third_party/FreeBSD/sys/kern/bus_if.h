/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   bus_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

/**
 * @defgroup BUS bus - KObj methods for drivers of devices with children
 * @brief A set of methods required device drivers that support
 * child devices.
 * @{
 */

#ifndef _bus_if_h_
#define _bus_if_h_

/** @brief Unique descriptor for the BUS_ALLOC_RESOURCE() method */
extern struct kobjop_desc bus_alloc_resource_desc;
/** @brief A function implementing the BUS_ALLOC_RESOURCE() method */
typedef struct resource * bus_alloc_resource_t(device_t _dev, device_t _child,
                                               int _type, int *_rid,
                                               rman_res_t _start,
                                               rman_res_t _end,
                                               rman_res_t _count, u_int _flags);
/**
 * @brief Allocate a system resource
 *
 * This method is called by child devices of a bus to allocate resources.
 * The types are defined in <machine/resource.h>; the meaning of the
 * resource-ID field varies from bus to bus (but @p *rid == 0 is always
 * valid if the resource type is). If a resource was allocated and the
 * caller did not use the RF_ACTIVE to specify that it should be
 * activated immediately, the caller is responsible for calling
 * BUS_ACTIVATE_RESOURCE() when it actually uses the resource.
 *
 * @param _dev		the parent device of @p _child
 * @param _child	the device which is requesting an allocation
 * @param _type		the type of resource to allocate
 * @param _rid		a pointer to the resource identifier
 * @param _start	hint at the start of the resource range - pass
 *			@c 0 for any start address
 * @param _end		hint at the end of the resource range - pass
 *			@c ~0 for any end address
 * @param _count	hint at the size of range required - pass @c 1
 *			for any size
 * @param _flags	any extra flags to control the resource
 *			allocation - see @c RF_XXX flags in
 *			<sys/rman.h> for details
 *
 * @returns		the resource which was allocated or @c NULL if no
 *			resource could be allocated
 */

static __inline struct resource * BUS_ALLOC_RESOURCE(device_t _dev,
                                                     device_t _child, int _type,
                                                     int *_rid,
                                                     rman_res_t _start,
                                                     rman_res_t _end,
                                                     rman_res_t _count,
                                                     u_int _flags)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_alloc_resource);
	return ((bus_alloc_resource_t *) _m)(_dev, _child, _type, _rid, _start, _end, _count, _flags);
}
/** @brief Unique descriptor for the BUS_CHILD_PNPINFO_STR() method */
extern struct kobjop_desc bus_child_pnpinfo_str_desc;
/** @brief A function implementing the BUS_CHILD_PNPINFO_STR() method */
typedef int bus_child_pnpinfo_str_t(device_t _dev, device_t _child, char *_buf,
                                    size_t _buflen);

/**
 * @brief Returns the pnp info for this device.
 *
 * Return it as a string.  If the storage is insufficient for the
 * string, then return EOVERFLOW.
 *
 * The string must be formatted as a space-separated list of
 * name=value pairs.  Names may only contain alphanumeric characters,
 * underscores ('_') and hyphens ('-').  Values can contain any
 * non-whitespace characters.  Values containing whitespace can be
 * quoted with double quotes ('"').  Double quotes and backslashes in
 * quoted values can be escaped with backslashes ('\').
 *
 * @param _dev		the parent device of @p _child
 * @param _child	the device which is being examined
 * @param _buf		the address of a buffer to receive the pnp
 *			string
 * @param _buflen	the size of the buffer pointed to by @p _buf
 */

static __inline int BUS_CHILD_PNPINFO_STR(device_t _dev, device_t _child,
                                          char *_buf, size_t _buflen)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_child_pnpinfo_str);
	return ((bus_child_pnpinfo_str_t *) _m)(_dev, _child, _buf, _buflen);
}

/** @brief Unique descriptor for the BUS_CHILD_LOCATION_STR() method */
extern struct kobjop_desc bus_child_location_str_desc;
/** @brief A function implementing the BUS_CHILD_LOCATION_STR() method */
typedef int bus_child_location_str_t(device_t _dev, device_t _child, char *_buf,
                                     size_t _buflen);
/**
 * @brief Returns the location for this device.
 *
 * Return it as a string.  If the storage is insufficient for the
 * string, then return EOVERFLOW.
 *
 * The string must be formatted as a space-separated list of
 * name=value pairs.  Names may only contain alphanumeric characters,
 * underscores ('_') and hyphens ('-').  Values can contain any
 * non-whitespace characters.  Values containing whitespace can be
 * quoted with double quotes ('"').  Double quotes and backslashes in
 * quoted values can be escaped with backslashes ('\').
 *
 * @param _dev		the parent device of @p _child
 * @param _child	the device which is being examined
 * @param _buf		the address of a buffer to receive the location
 *			string
 * @param _buflen	the size of the buffer pointed to by @p _buf
 */

static __inline int BUS_CHILD_LOCATION_STR(device_t _dev, device_t _child,
                                           char *_buf, size_t _buflen)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_child_location_str);
	return ((bus_child_location_str_t *) _m)(_dev, _child, _buf, _buflen);
}

/** @brief Unique descriptor for the BUS_PRINT_CHILD() method */
extern struct kobjop_desc bus_print_child_desc;
/** @brief A function implementing the BUS_PRINT_CHILD() method */
typedef int bus_print_child_t(device_t _dev, device_t _child);

/**
 * @brief Print a description of a child device
 *
 * This is called from system code which prints out a description of a
 * device. It should describe the attachment that the child has with
 * the parent. For instance the TurboLaser bus prints which node the
 * device is attached to. See bus_generic_print_child() for more
 * information.
 *
 * @param _dev		the device whose child is being printed
 * @param _child	the child device to describe
 *
 * @returns		the number of characters output.
 */

static __inline int BUS_PRINT_CHILD(device_t _dev, device_t _child)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_print_child);
	return ((bus_print_child_t *) _m)(_dev, _child);
}

/** @brief Unique descriptor for the BUS_PROBE_NOMATCH() method */
extern struct kobjop_desc bus_probe_nomatch_desc;
/** @brief A function implementing the BUS_PROBE_NOMATCH() method */
typedef void bus_probe_nomatch_t(device_t _dev, device_t _child);
/**
 * @brief Print a notification about an unprobed child device.
 *
 * Called for each child device that did not succeed in probing for a
 * driver.
 *
 * @param _dev		the device whose child was being probed
 * @param _child	the child device which failed to probe
 */

static __inline void BUS_PROBE_NOMATCH(device_t _dev, device_t _child)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_probe_nomatch);
	((bus_probe_nomatch_t *) _m)(_dev, _child);
}

/** @brief Unique descriptor for the BUS_READ_IVAR() method */
extern struct kobjop_desc bus_read_ivar_desc;
/** @brief A function implementing the BUS_READ_IVAR() method */
typedef int bus_read_ivar_t(device_t _dev, device_t _child, int _index,
                            uintptr_t *_result);
/**
 * @brief Read the value of a bus-specific attribute of a device
 *
 * This method, along with BUS_WRITE_IVAR() manages a bus-specific set
 * of instance variables of a child device.  The intention is that
 * each different type of bus defines a set of appropriate instance
 * variables (such as ports and irqs for ISA bus etc.)
 *
 * This information could be given to the child device as a struct but
 * that makes it hard for a bus to add or remove variables without
 * forcing an edit and recompile for all drivers which may not be
 * possible for vendor supplied binary drivers.
 *
 * This method copies the value of an instance variable to the
 * location specified by @p *_result.
 *
 * @param _dev		the device whose child was being examined
 * @param _child	the child device whose instance variable is
 *			being read
 * @param _index	the instance variable to read
 * @param _result	a location to receive the instance variable
 *			value
 *
 * @retval 0		success
 * @retval ENOENT	no such instance variable is supported by @p
 *			_dev
 */

static __inline int BUS_READ_IVAR(device_t _dev, device_t _child, int _index,
                                  uintptr_t *_result)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_read_ivar);
	return ((bus_read_ivar_t *) _m)(_dev, _child, _index, _result);
}

/** @brief Unique descriptor for the BUS_WRITE_IVAR() method */
extern struct kobjop_desc bus_write_ivar_desc;
/** @brief A function implementing the BUS_WRITE_IVAR() method */
typedef int bus_write_ivar_t(device_t _dev, device_t _child, int _indx,
                             uintptr_t _value);
/**
 * @brief Write the value of a bus-specific attribute of a device
 *
 * This method sets the value of an instance variable to @p _value.
 *
 * @param _dev		the device whose child was being updated
 * @param _child	the child device whose instance variable is
 *			being written
 * @param _index	the instance variable to write
 * @param _value	the value to write to that instance variable
 *
 * @retval 0		success
 * @retval ENOENT	no such instance variable is supported by @p
 *			_dev
 * @retval EINVAL	the instance variable was recognised but
 *			contains a read-only value
 */

static __inline int BUS_WRITE_IVAR(device_t _dev, device_t _child, int _indx,
                                   uintptr_t _value)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_write_ivar);
	return ((bus_write_ivar_t *) _m)(_dev, _child, _indx, _value);
}

/** @brief Unique descriptor for the BUS_CHILD_DELETED() method */
extern struct kobjop_desc bus_child_deleted_desc;
/** @brief A function implementing the BUS_CHILD_DELETED() method */
typedef void bus_child_deleted_t(device_t _dev, device_t _child);
/**
 * @brief Notify a bus that a child was deleted
 *
 * Called at the beginning of device_delete_child() to allow the parent
 * to teardown any bus-specific state for the child.
 *
 * @param _dev		the device whose child is being deleted
 * @param _child	the child device which is being deleted
 */

static __inline void BUS_CHILD_DELETED(device_t _dev, device_t _child)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_child_deleted);
	((bus_child_deleted_t *) _m)(_dev, _child);
}

/** @brief Unique descriptor for the BUS_CHILD_DETACHED() method */
extern struct kobjop_desc bus_child_detached_desc;
/** @brief A function implementing the BUS_CHILD_DETACHED() method */
typedef void bus_child_detached_t(device_t _dev, device_t _child);
/**
 * @brief Notify a bus that a child was detached
 *
 * Called after the child's DEVICE_DETACH() method to allow the parent
 * to reclaim any resources allocated on behalf of the child.
 *
 * @param _dev		the device whose child changed state
 * @param _child	the child device which changed state
 */

static __inline void BUS_CHILD_DETACHED(device_t _dev, device_t _child)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_child_detached);
	((bus_child_detached_t *) _m)(_dev, _child);
}

/** @brief Unique descriptor for the BUS_DRIVER_ADDED() method */
extern struct kobjop_desc bus_driver_added_desc;
/** @brief A function implementing the BUS_DRIVER_ADDED() method */
typedef void bus_driver_added_t(device_t _dev, driver_t *_driver);
/**
 * @brief Notify a bus that a new driver was added
 *
 * Called when a new driver is added to the devclass which owns this
 * bus. The generic implementation of this method attempts to probe and
 * attach any un-matched children of the bus.
 *
 * @param _dev		the device whose devclass had a new driver
 *			added to it
 * @param _driver	the new driver which was added
 */

static __inline void BUS_DRIVER_ADDED(device_t _dev, driver_t *_driver)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_driver_added);
	((bus_driver_added_t *) _m)(_dev, _driver);
}

/** @brief Unique descriptor for the BUS_ADD_CHILD() method */
extern struct kobjop_desc bus_add_child_desc;
/** @brief A function implementing the BUS_ADD_CHILD() method */
typedef device_t bus_add_child_t(device_t _dev, u_int _order, const char *_name,
                                 int _unit);
/**
 * @brief Create a new child device
 *
 * For busses which use use drivers supporting DEVICE_IDENTIFY() to
 * enumerate their devices, this method is used to create new
 * device instances. The new device will be added after the last
 * existing child with the same order. Implementations of bus_add_child
 * call device_add_child_ordered to add the child and often add
 * a suitable ivar to the device specific to that bus.
 *
 * @param _dev		the bus device which will be the parent of the
 *			new child device
 * @param _order	a value which is used to partially sort the
 *			children of @p _dev - devices created using
 *			lower values of @p _order appear first in @p
 *			_dev's list of children
 * @param _name		devclass name for new device or @c NULL if not
 *			specified
 * @param _unit		unit number for new device or @c -1 if not
 *			specified
 */

static __inline device_t BUS_ADD_CHILD(device_t _dev, u_int _order,
                                       const char *_name, int _unit)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_add_child);
	return ((bus_add_child_t *) _m)(_dev, _order, _name, _unit);
}

/** @brief Unique descriptor for the BUS_RESCAN() method */
extern struct kobjop_desc bus_rescan_desc;
/** @brief A function implementing the BUS_RESCAN() method */
typedef int bus_rescan_t(device_t _dev);
/**
 * @brief Rescan the bus
 *
 * This method is called by a parent bridge or devctl to trigger a bus
 * rescan.  The rescan should delete devices no longer present and
 * enumerate devices that have newly arrived.
 *
 * @param _dev		the bus device
 */

static __inline int BUS_RESCAN(device_t _dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_rescan);
	return ((bus_rescan_t *) _m)(_dev);
}

/** @brief Unique descriptor for the BUS_CHILD_PRESENT() method */
extern struct kobjop_desc bus_child_present_desc;
/** @brief A function implementing the BUS_CHILD_PRESENT() method */
typedef int bus_child_present_t(device_t _dev, device_t _child);
/**
 * @brief Is the hardware described by @p _child still attached to the
 * system?
 *
 * This method should return 0 if the device is not present.  It
 * should return -1 if it is present.  Any errors in determining
 * should be returned as a normal errno value.  Client drivers are to
 * assume that the device is present, even if there is an error
 * determining if it is there.  Busses are to try to avoid returning
 * errors, but newcard will return an error if the device fails to
 * implement this method.
 *
 * @param _dev          the parent device of @p _child
 * @param _child        the device which is being examined
 */

static __inline int BUS_CHILD_PRESENT(device_t _dev, device_t _child)
{
        kobjop_t _m;
        KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_child_present);
        return ((bus_child_present_t *) _m)(_dev, _child);
}

// delete resource and interrupt

/** @brief Unique descriptor for the BUS_HINTED_CHILD() method */
extern struct kobjop_desc bus_hinted_child_desc;
/** @brief A function implementing the BUS_HINTED_CHILD() method */
typedef void bus_hinted_child_t(device_t _dev, const char *_dname, int _dunit);
/**
 * @brief Notify a (bus) driver about a child that the hints mechanism
 * believes it has discovered.
 *
 * The bus is responsible for then adding the child in the right order
 * and discovering other things about the child.  The bus driver is
 * free to ignore this hint, to do special things, etc.  It is all up
 * to the bus driver to interpret.
 *
 * This method is only called in response to the parent bus asking for
 * hinted devices to be enumerated.
 *
 * @param _dev		the bus device
 * @param _dname	the name of the device w/o unit numbers
 * @param _dunit	the unit number of the device
 */

static __inline void BUS_HINTED_CHILD(device_t _dev, const char *_dname,
                                      int _dunit)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_hinted_child);
	((bus_hinted_child_t *) _m)(_dev, _dname, _dunit);
}

// delete dma

/** @brief Unique descriptor for the BUS_HINT_DEVICE_UNIT() method */
extern struct kobjop_desc bus_hint_device_unit_desc;
/** @brief A function implementing the BUS_HINT_DEVICE_UNIT() method */
typedef void bus_hint_device_unit_t(device_t _dev, device_t _child,
                                    const char *_name, int *_unitp);
/**
 * @brief Allow the bus to determine the unit number of a device.
 *
 * @param _dev		the parent device of @p _child
 * @param _child	the device whose unit is to be wired
 * @param _name		the name of the device's new devclass
 * @param _unitp	a pointer to the device's new unit value
 */

static __inline void BUS_HINT_DEVICE_UNIT(device_t _dev, device_t _child,
                                          const char *_name, int *_unitp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_hint_device_unit);
	((bus_hint_device_unit_t *) _m)(_dev, _child, _name, _unitp);
}

/** @brief Unique descriptor for the BUS_NEW_PASS() method */
extern struct kobjop_desc bus_new_pass_desc;
/** @brief A function implementing the BUS_NEW_PASS() method */
typedef void bus_new_pass_t(device_t _dev);
/**
 * @brief Notify a bus that the bus pass level has been changed
 *
 * @param _dev		the bus device
 */

static __inline void BUS_NEW_PASS(device_t _dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_new_pass);
	((bus_new_pass_t *) _m)(_dev);
}

/** @brief Unique descriptor for the BUS_SUSPEND_CHILD() method */
extern struct kobjop_desc bus_suspend_child_desc;
/** @brief A function implementing the BUS_SUSPEND_CHILD() method */
typedef int bus_suspend_child_t(device_t _dev, device_t _child);
/**
 * @brief Suspend a given child
 *
 * @param _dev		the parent device of @p _child
 * @param _child	the device to suspend
 */

static __inline int BUS_SUSPEND_CHILD(device_t _dev, device_t _child)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_suspend_child);
	return ((bus_suspend_child_t *) _m)(_dev, _child);
}

/** @brief Unique descriptor for the BUS_RESUME_CHILD() method */
extern struct kobjop_desc bus_resume_child_desc;
/** @brief A function implementing the BUS_RESUME_CHILD() method */
typedef int bus_resume_child_t(device_t _dev, device_t _child);
/**
 * @brief Resume a given child
 *
 * @param _dev		the parent device of @p _child
 * @param _child	the device to resume
 */

static __inline int BUS_RESUME_CHILD(device_t _dev, device_t _child)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_resume_child);
	return ((bus_resume_child_t *) _m)(_dev, _child);
}

/** @brief Unique descriptor for the BUS_GET_DOMAIN() method */
extern struct kobjop_desc bus_get_domain_desc;
/** @brief A function implementing the BUS_GET_DOMAIN() method */
typedef int bus_get_domain_t(device_t _dev, device_t _child, int *_domain);
/**
 * @brief Get the VM domain handle for the given bus and child.
 *
 * @param _dev		the bus device
 * @param _child	the child device
 * @param _domain	a pointer to the bus's domain handle identifier
 */

static __inline int BUS_GET_DOMAIN(device_t _dev, device_t _child, int *_domain)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_get_domain);
	return ((bus_get_domain_t *) _m)(_dev, _child, _domain);
}


/** @brief Unique descriptor for the BUS_RESET_PREPARE() method */
extern struct kobjop_desc bus_reset_prepare_desc;
/** @brief A function implementing the BUS_RESET_PREPARE() method */
typedef int bus_reset_prepare_t(device_t _dev, device_t _child);
/**
 * @brief Prepares the given child of the bus for reset
 *
 * Typically bus detaches or suspends children' drivers, and then
 * calls this method to save bus-specific information, for instance,
 * PCI config space, which is damaged by reset.
 *
 * The bus_helper_reset_prepare() helper is provided to ease
 * implementing bus reset methods.
 *
 * @param _dev		the bus device
 * @param _child	the child device
 */

static __inline int BUS_RESET_PREPARE(device_t _dev, device_t _child)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_reset_prepare);
	return ((bus_reset_prepare_t *) _m)(_dev, _child);
}

/** @brief Unique descriptor for the BUS_RESET_POST() method */
extern struct kobjop_desc bus_reset_post_desc;
/** @brief A function implementing the BUS_RESET_POST() method */
typedef int bus_reset_post_t(device_t _dev, device_t _child);
/**
 * @brief Restores the child operations after the reset
 *
 * The bus_helper_reset_post() helper is provided to ease
 * implementing bus reset methods.
 *
 * @param _dev		the bus device
 * @param _child	the child device
 */

static __inline int BUS_RESET_POST(device_t _dev, device_t _child)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_reset_post);
	return ((bus_reset_post_t *) _m)(_dev, _child);
}

/** @brief Unique descriptor for the BUS_RESET_CHILD() method */
extern struct kobjop_desc bus_reset_child_desc;
/** @brief A function implementing the BUS_RESET_CHILD() method */
typedef int bus_reset_child_t(device_t _dev, device_t _child, int _flags);
/**
 * @brief Performs reset of the child
 *
 * @param _dev		the bus device
 * @param _child	the child device
 * @param _flags	DEVF_RESET_ flags
 */

static __inline int BUS_RESET_CHILD(device_t _dev, device_t _child, int _flags)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)_dev)->ops,bus_reset_child);
	return ((bus_reset_child_t *) _m)(_dev, _child, _flags);
}

#endif /* _bus_if_h_ */
