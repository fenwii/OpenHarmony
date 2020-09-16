/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   usb_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _usb_if_h_
#define _usb_if_h_

/** @brief Unique descriptor for the USB_HANDLE_REQUEST() method */
extern struct kobjop_desc usb_handle_request_desc;
/** @brief A function implementing the USB_HANDLE_REQUEST() method */
typedef int usb_handle_request_t(device_t dev, const void *req,
                                 /* pointer to the device request */ void **pptr, /* data pointer */ uint16_t *plen, /* maximum transfer length */ uint16_t offset, /* data offset */ uint8_t *pstate);

static __inline int USB_HANDLE_REQUEST(device_t dev, const void *req,
                                       /* pointer to the device request */ void **pptr, /* data pointer */ uint16_t *plen, /* maximum transfer length */ uint16_t offset, /* data offset */ uint8_t *pstate)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,usb_handle_request);
	return ((usb_handle_request_t *) _m)(dev, req, pptr, plen, offset, pstate);
}

/** @brief Unique descriptor for the USB_TAKE_CONTROLLER() method */
extern struct kobjop_desc usb_take_controller_desc;
/** @brief A function implementing the USB_TAKE_CONTROLLER() method */
typedef int usb_take_controller_t(device_t dev);

static __inline int USB_TAKE_CONTROLLER(device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,usb_take_controller);
	return ((usb_take_controller_t *) _m)(dev);
}

#endif /* _usb_if_h_ */
