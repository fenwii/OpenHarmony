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

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include "bus_if.h"


static struct resource *
null_alloc_resource(device_t dev, device_t child,
    int type, int *rid, rman_res_t start, rman_res_t end,
    rman_res_t count, u_int flags)
{
    return (0);
}
static device_t
null_add_child(device_t bus, int order, const char *name,
    int unit)
{
	panic("bus_add_child is not implemented");
	return NULL;
}

static int null_reset_post(device_t bus, device_t dev)
{
	return (0);
}

static int null_reset_prepare(device_t bus, device_t dev)
{
	return (0);
}

struct kobjop_desc bus_print_child_desc = {
	0, { &bus_print_child_desc, (kobjop_t)bus_generic_print_child }
};

struct kobjop_desc bus_probe_nomatch_desc = {
	0, { &bus_probe_nomatch_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc bus_read_ivar_desc = {
	0, { &bus_read_ivar_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc bus_write_ivar_desc = {
	0, { &bus_write_ivar_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc bus_child_deleted_desc = {
	0, { &bus_child_deleted_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc bus_child_detached_desc = {
	0, { &bus_child_detached_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc bus_driver_added_desc = {
	0, { &bus_driver_added_desc, (kobjop_t)bus_generic_driver_added }
};

struct kobjop_desc bus_add_child_desc = {
	0, { &bus_add_child_desc, (kobjop_t)null_add_child }
};

struct kobjop_desc bus_rescan_desc = {
	0, { &bus_rescan_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc bus_alloc_resource_desc = {
	0, { &bus_alloc_resource_desc, (kobjop_t)null_alloc_resource }
};

struct kobjop_desc bus_child_present_desc = {
        0, { &bus_child_present_desc, (kobjop_t)bus_generic_child_present }
};

struct kobjop_desc bus_child_pnpinfo_str_desc = {
	0, { &bus_child_pnpinfo_str_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc bus_child_location_str_desc = {
	0, { &bus_child_location_str_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc bus_hinted_child_desc = {
	0, { &bus_hinted_child_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc bus_hint_device_unit_desc = {
        0, { &bus_hint_device_unit_desc, (kobjop_t)kobj_error_method }
};

struct kobjop_desc bus_new_pass_desc = {
	0, { &bus_new_pass_desc, (kobjop_t)bus_generic_new_pass }
};

struct kobjop_desc bus_suspend_child_desc = {
	0, { &bus_suspend_child_desc, (kobjop_t)bus_generic_suspend_child }
};

struct kobjop_desc bus_resume_child_desc = {
	0, { &bus_resume_child_desc, (kobjop_t)bus_generic_resume_child }
};

struct kobjop_desc bus_get_domain_desc = {
	0, { &bus_get_domain_desc, (kobjop_t)bus_generic_get_domain }
};

struct kobjop_desc bus_reset_prepare_desc = {
	0, { &bus_reset_prepare_desc, (kobjop_t)null_reset_prepare }
};

struct kobjop_desc bus_reset_post_desc = {
	0, { &bus_reset_post_desc, (kobjop_t)null_reset_post }
};

struct kobjop_desc bus_reset_child_desc = {
	0, { &bus_reset_child_desc, (kobjop_t)kobj_error_method }
};