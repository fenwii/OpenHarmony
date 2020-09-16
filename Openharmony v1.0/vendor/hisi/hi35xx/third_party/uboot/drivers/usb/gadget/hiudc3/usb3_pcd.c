#include "usb3.h"
#include "usb3_hw.h"
#include "usb3_drv.h"
#include "usb3_prot.h"
#include "usb3_pcd.h"
#include <common.h>
#include <linux/string.h>

extern void usb3_bulk_out_transfer(void *dev);

const struct usb_interface_descriptor
intf = {
	sizeof(struct usb_interface_descriptor), /* bLength */
	UDESC_INTERFACE, /* bDescriptorType */

	0, /* bInterfaceNumber */
	0, /* bAlternateSetting */
	2, /* bNumEndpoints */
	USB_CLASS_VENDOR_SPEC, /* bInterfaceClass */
	USB_SC_VENDOR_SPEC, /* bInterfaceSubClass */
	USB_PR_VENDOR_SPEC, /* bInterfaceProtocol */
	0, /* iInterface */
};

/* Two endpoint descriptors: bulk-in, bulk-out. */

const struct usb_ss_ep_comp_descriptor
ep_comp = {
	sizeof(struct usb_ss_ep_comp_descriptor), /* bLength */
	UDESC_SS_USB_COMPANION, /* bDescriptorType */
	0, /* bMaxBurst */
	0, /* bmAttributes */
	0, /* wBytesPerInterval */
};

const struct usb_endpoint_descriptor
hs_bulk_in = {
	sizeof(struct usb_endpoint_descriptor), /* bLength */
	UDESC_ENDPOINT, /* bDescriptorType */

	UE_DIR_IN | USB3_BULK_IN_EP, /* bEndpointAddress */
	USB_ENDPOINT_XFER_BULK, /* bmAttributes */
	0x200, /* wMaxPacketSize: 512 of high-speed */
	0, /* bInterval */
};

const struct usb_endpoint_descriptor
hs_bulk_out = {
	sizeof(struct usb_endpoint_descriptor), /* bLength */
	UDESC_ENDPOINT, /* bDescriptorType */

	UE_DIR_OUT | USB3_BULK_OUT_EP, /* bEndpointAddress */
	USB_ENDPOINT_XFER_BULK, /* bmAttributes */
	0x200, /* wMaxPacketSize: 512 of high-speed */
	1, /* bInterval */
};

const struct usb_endpoint_descriptor
ss_bulk_in = {
	sizeof(struct usb_endpoint_descriptor), /* bLength */
	UDESC_ENDPOINT, /* bDescriptorType */

	UE_DIR_IN | USB3_BULK_IN_EP, /* bEndpointAddress */
	USB_ENDPOINT_XFER_BULK, /* bmAttributes */
	0x400, /* wMaxPacketSize: 1024 of super-speed */
	0, /* bInterval */
};

const struct usb_endpoint_descriptor
ss_bulk_out = {
	sizeof(struct usb_endpoint_descriptor), /* bLength */
	UDESC_ENDPOINT, /* bDescriptorType */

	UE_DIR_OUT | USB3_BULK_OUT_EP, /* bEndpointAddress */
	USB_ENDPOINT_XFER_BULK, /* bmAttributes */
	0x400, /* wMaxPacketSize: 1024 of super-speed */
	0, /* bInterval */
};

/** The BOS Descriptor */

const struct usb_dev_cap_20_ext_desc
cap1 = {
	sizeof(struct usb_dev_cap_20_ext_desc),	/* bLength */
	UDESC_DEVICE_CAPABILITY,		/* bDescriptorType */
	USB_DEVICE_CAPABILITY_20_EXTENSION,	/* bDevCapabilityType */
	0x2,				/* bmAttributes */
};

const struct usb_dev_cap_ss_usb
cap2 = {
	sizeof(struct usb_dev_cap_ss_usb),	/* bLength */
	UDESC_DEVICE_CAPABILITY,		/* bDescriptorType */
	USB_DEVICE_CAPABILITY_SS_USB,		/* bDevCapabilityType */
	0x0,					/* bmAttributes */
	(USB_DC_SS_USB_SPEED_SUPPORT_SS |
	    USB_DC_SS_USB_SPEED_SUPPORT_HIGH),   /* wSpeedsSupported */
	0x2,					/* bFunctionalitySupport */
	/* @todo set these to correct value */
	0xa,					/* bU1DevExitLat */
	0x100,				/* wU2DevExitLat */
};

const struct usb_dev_cap_container_id
cap3 = {
	sizeof(struct usb_dev_cap_container_id),/* bLength */
	UDESC_DEVICE_CAPABILITY,		/* bDescriptorType */
	USB_DEVICE_CAPABILITY_CONTAINER_ID,	/* bDevCapabilityType */
	0,					/* bReserved */
	/* @todo Create UUID */
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, /* containerID */
};

const struct wusb_bos_desc
bos = {
	sizeof(struct wusb_bos_desc),		/* bLength */
	UDESC_BOS,				/* bDescriptorType */
	(sizeof(struct wusb_bos_desc)	/* wTotalLength */
	    + sizeof(cap1) + sizeof(cap2) + sizeof(cap3)),
	3,					/* bNumDeviceCaps */
};

usb3_pcd_ep_t *usb3_get_out_ep(usb3_pcd_t *pcd, uint32_t ep_num)
{
	if (ep_num == 0) {
		return &pcd->ep0;
	} else {
		return &pcd->out_ep;
	}
}

usb3_pcd_ep_t *usb3_get_in_ep(usb3_pcd_t *pcd, uint32_t ep_num)
{
	if (ep_num == 0) {
		return &pcd->ep0;
	} else {
		return &pcd->in_ep;
	}
}

usb3_pcd_ep_t *usb3_get_ep_by_addr(usb3_pcd_t *pcd, uint16_t index)
{
	uint32_t ep_num = UE_GET_ADDR(index);

	if (UE_GET_DIR(index) == UE_DIR_IN) {
		return usb3_get_in_ep(pcd, ep_num);
	} else {
		return usb3_get_out_ep(pcd, ep_num);
	}
}


void usb3_ep_clear_stall(usb3_pcd_t *pcd, usb3_pcd_ep_t *ep)
{
	usb3_dev_ep_regs_t *ep_reg;

	if (ep->is_in) {
		ep_reg = ep->in_ep_reg;
	} else {
		ep_reg = ep->out_ep_reg;
	}

	usb3_dep_cstall(pcd, ep_reg);
}


uint32_t usb3_get_device_speed(usb3_pcd_t *pcd)
{
	uint32_t dsts;
	uint32_t speed = USB_SPEED_UNKNOWN;

	dsts = usb3_rd32(&pcd->dev_global_regs->dsts);

	switch ((dsts >> USB3_DSTS_CONNSPD_SHIFT) &
		(USB3_DSTS_CONNSPD_BITS >> USB3_DSTS_CONNSPD_SHIFT)) {
	case USB3_SPEED_HS_PHY_30MHZ_OR_60MHZ:
		speed = USB_SPEED_HIGH;
		break;

	case USB3_SPEED_FS_PHY_30MHZ_OR_60MHZ:
	case USB3_SPEED_FS_PHY_48MHZ:
		speed = USB_SPEED_FULL;
		break;

	case USB3_SPEED_LS_PHY_6MHZ:
		speed = USB_SPEED_LOW;
		break;

	case USB3_SPEED_SS_PHY_125MHZ_OR_250MHZ:
		speed = USB_SPEED_SUPER;
		break;
	}

	return speed;
}

void usb3_pcd_set_speed(usb3_pcd_t *pcd, int speed)
{
	/* Set the MPS of EP0 based on the connection speed */
	switch (speed) {
	case USB_SPEED_SUPER:
		pcd->ep0.maxpacket = 512;
		pcd->in_ep.maxpacket  = USB3_MAX_PACKET_SIZE;
		pcd->out_ep.maxpacket = USB3_MAX_PACKET_SIZE;
		break;

	case USB_SPEED_HIGH:
		pcd->ep0.maxpacket = 64;
		pcd->in_ep.maxpacket  = USB2_HS_MAX_PACKET_SIZE;
		pcd->out_ep.maxpacket = USB2_HS_MAX_PACKET_SIZE;
		break;

	case USB_SPEED_FULL:
		pcd->ep0.maxpacket = 64;
		pcd->in_ep.maxpacket  = USB2_FS_MAX_PACKET_SIZE;
		pcd->out_ep.maxpacket = USB2_FS_MAX_PACKET_SIZE;
		break;

	case USB_SPEED_LOW:
		pcd->ep0.maxpacket = 8;
		pcd->in_ep.maxpacket  = 0;
		pcd->out_ep.maxpacket = 0;
		break;
	}
}

void usb3_ep_set_stall(usb3_pcd_t *pcd, usb3_pcd_ep_t *ep)
{
	usb3_dev_ep_regs_t *ep_reg;

	if (ep->is_in) {
		ep_reg = ep->in_ep_reg;
	} else {
		ep_reg = ep->out_ep_reg;
	}

	usb3_dep_sstall(pcd, ep_reg);
}

static void ep0_do_stall(usb3_pcd_t *pcd)
{
	usb3_pcd_ep_t *ep0 = &pcd->ep0;

	/* Stall EP0 IN & OUT simultanelusly */
	ep0->is_in = 1;
	usb3_ep_set_stall(pcd, ep0);
	ep0->is_in = 0;
	usb3_ep_set_stall(pcd, ep0);

	/* Prepare for the next setup transfer */
	ep0->stopped = 1;
	pcd->ep0state = EP0_IDLE;
	usb3_ep0_out_start(pcd);
}

static void do_clear_halt(usb3_pcd_t *pcd, usb3_pcd_ep_t *ep)
{
	usb3_ep_clear_stall(pcd, ep);

	if (ep->stopped) {
		ep->stopped = 0;
	}
}

void usb3_pcd_ep_enable(usb3_pcd_t *pcd, usb3_pcd_ep_t *ep)
{
	/*
	 * Activate the EP
	 */
	ep->stopped = 0;
	ep->xfer_started = 0;

	/* Set initial data PID. */
	if (ep->type == USB3_EP_TYPE_BULK)
		ep->data_pid_start = 0;

	usb3_ep_activate(pcd, ep);
}

static void usb3_do_get_status(usb3_pcd_t *pcd)
{
	usb_device_request_t ctrl = pcd->ep0_setup_pkt->req;
	uint8_t *status = pcd->ep0_status_buf;
	usb3_pcd_ep_t *ep;

	if (ctrl.wLength != 2) {
		ep0_do_stall(pcd);
		return;
	}

	switch (UT_GET_RECIPIENT(ctrl.bmRequestType)) {
	case UT_DEVICE:
		*status = 0; /* Bus powered */

		if (pcd->speed == USB_SPEED_SUPER) {
			if (pcd->state == USB3_STATE_CONFIGURED) {
				if (usb3_u1_enabled(pcd))
					*status |= 1 << 2;

				if (usb3_u2_enabled(pcd))
					*status |= 1 << 3;

				*status |= pcd->ltm_enable << 4;
			}
		}

		*(status + 1) = 0;
		break;

	case UT_INTERFACE:
		*status = 0;
		*(status + 1) = 0;
		break;

	case UT_ENDPOINT:
		ep = usb3_get_ep_by_addr(pcd, ctrl.wIndex);

		/* @todo check for EP stall */
		*status = ep->stopped;
		*(status + 1) = 0;
		break;

	default:
		ep0_do_stall(pcd);
		return;
	}

	pcd->ep0_req.bufdma = status;
	pcd->ep0_req.length = 2;
	pcd->ep0_req.actual = 0;
	usb3_ep0_start_transfer(pcd, &pcd->ep0_req);
}

static void usb3_do_clear_feature(usb3_pcd_t *pcd)
{
	usb_device_request_t ctrl = pcd->ep0_setup_pkt->req;
	usb3_pcd_ep_t *ep;

	switch (UT_GET_RECIPIENT(ctrl.bmRequestType)) {
	case UT_DEVICE:
		switch (ctrl.wValue) {
		case UF_DEVICE_REMOTE_WAKEUP:
			break;

		case UF_TEST_MODE:
			/* @todo Add CLEAR_FEATURE for TEST modes. */
			break;

		case UF_U1_ENABLE:
			if (pcd->speed != USB_SPEED_SUPER ||
			    pcd->state != USB3_STATE_CONFIGURED) {
				ep0_do_stall(pcd);
				return;
			}
			usb3_disable_u1(pcd);
			break;

		case UF_U2_ENABLE:
			if (pcd->speed != USB_SPEED_SUPER ||
			    pcd->state != USB3_STATE_CONFIGURED) {
				ep0_do_stall(pcd);
				return;
			}
			usb3_disable_u2(pcd);
			break;

		case UF_LTM_ENABLE:
			if (pcd->speed != USB_SPEED_SUPER ||
			    pcd->state != USB3_STATE_CONFIGURED ||
			    ctrl.wIndex != 0) {
				ep0_do_stall(pcd);
				return;
			}
			pcd->ltm_enable = 0;
			break;

		default:
			ep0_do_stall(pcd);
			return;
		}
		break;

	case UT_INTERFACE:
		/* if FUNCTION_SUSPEND ... */
		if (ctrl.wValue) {
			ep0_do_stall(pcd);
			return;
		}
        break;

	case UT_ENDPOINT:
		ep = usb3_get_ep_by_addr(pcd, ctrl.wIndex);
		if (ctrl.wValue != UF_ENDPOINT_HALT) {
			ep0_do_stall(pcd);
			return;
		}
		do_clear_halt(pcd, ep);
		break;
	}

	pcd->ep0.is_in = 1;
	pcd->ep0state = EP0_IN_WAIT_NRDY;
}

static void usb3_do_set_feature(usb3_pcd_t *pcd)
{
	usb_device_request_t ctrl = pcd->ep0_setup_pkt->req;
	usb3_pcd_ep_t *ep;

	switch (UT_GET_RECIPIENT(ctrl.bmRequestType)) {
	case UT_DEVICE:
		switch (ctrl.wValue) {
		case UF_DEVICE_REMOTE_WAKEUP:
			break;

		case UF_TEST_MODE:
			break;

		case UF_DEVICE_B_HNP_ENABLE:
			break;

		case UOTG_NTF_HOST_REL:
			break;

		case UOTG_B3_RSP_ENABLE:
			break;

		case UF_DEVICE_A_HNP_SUPPORT:
			/* RH port supports HNP */
			break;

		case UF_DEVICE_A_ALT_HNP_SUPPORT:
			/* other RH port does */
			break;

		case UF_U1_ENABLE:
			if (pcd->speed != USB_SPEED_SUPER ||
			    pcd->state != USB3_STATE_CONFIGURED) {
				ep0_do_stall(pcd);
				return;
			}
			usb3_enable_u1(pcd);
			break;

		case UF_U2_ENABLE:
			if (pcd->speed != USB_SPEED_SUPER ||
			    pcd->state != USB3_STATE_CONFIGURED) {
				ep0_do_stall(pcd);
				return;
			}
			usb3_enable_u2(pcd);
			break;

		case UF_LTM_ENABLE:
			if (pcd->speed != USB_SPEED_SUPER ||
			    pcd->state != USB3_STATE_CONFIGURED ||
			    ctrl.wIndex != 0) {
				ep0_do_stall(pcd);
				return;
			}
			pcd->ltm_enable = 1;
			break;

		default:
			ep0_do_stall(pcd);
			return;
		}
		break;

	case UT_INTERFACE:
		/* if FUNCTION_SUSPEND ... */
		if (ctrl.wValue) {
			ep0_do_stall(pcd);
			return;
		}
        break;

	case UT_ENDPOINT:
		ep = usb3_get_ep_by_addr(pcd, ctrl.wIndex);
		if (ctrl.wValue != UF_ENDPOINT_HALT) {
			ep0_do_stall(pcd);
			return;
		}
		ep->stopped = 1;
		usb3_ep_set_stall(pcd, ep);
		break;
	}

	pcd->ep0.is_in = 1;
	pcd->ep0state = EP0_IN_WAIT_NRDY;
}

static void usb3_do_set_address(usb3_pcd_t *pcd)
{
	usb_device_request_t ctrl = pcd->ep0_setup_pkt->req;

	if (ctrl.bmRequestType == UT_DEVICE) {
		usb3_set_address(pcd, ctrl.wValue);
		pcd->ep0.is_in = 1;
		pcd->ep0state = EP0_IN_WAIT_NRDY;
		if (ctrl.wValue) {
			pcd->state = USB3_STATE_ADDRESSED;
		} else {
			pcd->state = USB3_STATE_DEFAULT;
		}
	}
}

static void usb3_do_set_config(usb3_pcd_t *pcd)
{
	usb_device_request_t ctrl = pcd->ep0_setup_pkt->req;
	uint16_t wvalue = ctrl.wValue;
	usb3_pcd_ep_t *ep;

	if (ctrl.bmRequestType != (UT_WRITE | UT_STANDARD |
		UT_DEVICE)) {
		ep0_do_stall(pcd);
		return;
	}

	if (!wvalue ||(wvalue == CONFIG_VALUE)) {
		pcd->new_config = wvalue;
		/* Set new configuration */
		if (wvalue) {
			/* Activate bulk in endpoint */
			ep = &pcd->in_ep;
			usb3_pcd_ep_enable(pcd, ep);

			/* Activate bulk out endpoint */
			ep = &pcd->out_ep;
			usb3_pcd_ep_enable(pcd, ep);

			/* Prepare for next bulk transfer */
			usb3_bulk_out_transfer((void *)pcd);
			usb3_bulk_in_transfer((void *)pcd, "start download process.");
			pcd->state = USB3_STATE_CONFIGURED;
		} else {
			pcd->state = USB3_STATE_ADDRESSED;
		}

		pcd->ep0.is_in = 1;
		pcd->ep0state = EP0_IN_WAIT_NRDY;
	} else {
		ep0_do_stall(pcd);
	}
}

static void usb3_do_get_config(usb3_pcd_t *pcd)
{
	usb_device_request_t ctrl = pcd->ep0_setup_pkt->req;
	uint8_t *status = pcd->ep0_status_buf;

	if (ctrl.bmRequestType != (UT_READ | UT_STANDARD |
			UT_DEVICE)) {
		ep0_do_stall(pcd);
		return;
	}

	/* Notify host the current config value */
	*status = pcd->new_config;

	pcd->ep0_req.bufdma = status;
	pcd->ep0_req.length = 1;
	pcd->ep0_req.actual = 0;
	usb3_ep0_start_transfer(pcd, &pcd->ep0_req);
}

static void usb3_do_get_descriptor(usb3_pcd_t *pcd)
{
	usb_device_request_t ctrl = pcd->ep0_setup_pkt->req;
	usb3_device_t *usb3_dev = pcd->usb3_dev;
	uint8_t dt = ctrl.wValue >> 8;
	uint8_t index = (uint8_t)ctrl.wValue;
	uint16_t len = ctrl.wLength;
	uint8_t *buf = pcd->ep0_status_buf;
	uint16_t value = 0;

	if (ctrl.bmRequestType != (UT_READ | UT_STANDARD |
			UT_DEVICE)) {
		ep0_do_stall(pcd);
		return;
	}

	switch (dt) {
	case UDESC_DEVICE:
        {
		struct usb_device_descriptor *dev =
			(struct usb_device_descriptor *)usb3_dev->dev_desc;

		dev->bLength = sizeof(struct usb_device_descriptor);
		dev->bDescriptorType = UDESC_DEVICE;

		dev->bDeviceClass = 0;
		dev->bDeviceSubClass = 0;
		dev->bDeviceProtocol = 0;

		if (pcd->speed == USB_SPEED_SUPER) {
			dev->bcdUSB = 0x300;
			dev->bMaxPacketSize0 = 9; // NOTE! 2 ^ 9 = 512 for USB3
		} else if (pcd->speed == USB_SPEED_HIGH) {
			dev->bcdUSB = 0x0200;
			dev->bMaxPacketSize0 = pcd->ep0.maxpacket;
		} else {
			dev->bcdUSB = 0x0110;
			dev->bMaxPacketSize0 = pcd->ep0.maxpacket;
		}

		dev->idVendor = HUAWEI_VENDOR_ID;
		dev->idProduct = 0xD001;
	//	dev->idProduct = HUAWEI_PRODUCT_ID;
		dev->bcdDevice = 0x0100;

		dev->iManufacturer = STRING_MANUFACTURER;
		dev->iProduct = STRING_PRODUCT;
		dev->iSerialNumber = 0;

		dev->bNumConfigurations = 1;

		value = sizeof(struct usb_device_descriptor);
		usb3_memcpy((void *)buf, (void *)dev, value);
	}
	break;

	case UDESC_DEVICE_QUALIFIER:
	{
		struct usb_qualifier_descriptor *qual =
			(struct usb_qualifier_descriptor *)buf;
		struct usb_device_descriptor *dev =
			(struct usb_device_descriptor *)usb3_dev->dev_desc;

		qual->bLength = sizeof(*qual);
		qual->bDescriptorType = UDESC_DEVICE_QUALIFIER;
		qual->bcdUSB = dev->bcdUSB;
		qual->bDeviceClass = dev->bDeviceClass;
		qual->bDeviceSubClass = dev->bDeviceSubClass;
		qual->bDeviceProtocol = dev->bDeviceProtocol;
		qual->bMaxPacketSize0 = dev->bMaxPacketSize0;
		qual->bNumConfigurations = 1;
		qual->bRESERVED = 0;

		value = sizeof(usb_qualifier_descriptor_t);
        }
        break;

	case UDESC_CONFIG:
        {
		struct usb_config_descriptor *config =
			(struct usb_config_descriptor *)buf;

		config->bLength = sizeof(*config);
		config->bDescriptorType = UDESC_CONFIG;
		config->bNumInterfaces = 1;
		config->bConfigurationValue = CONFIG_VALUE;
		config->iConfiguration = 0;
		config->bmAttributes = USB_CONFIG_ATT_ONE;

		if (pcd->speed == USB_SPEED_SUPER) {
			config->bMaxPower = USB_CONFIG_VBUS_DRAW / 8;
		} else {
			config->bMaxPower = USB_CONFIG_VBUS_DRAW / 2;
		}

		buf += sizeof(*config);
		usb3_memcpy((void *)buf, (void *)&intf, sizeof(intf));
		buf += sizeof(intf);

		switch (pcd->speed) {
		case USB_SPEED_SUPER:
			usb3_memcpy((void *)buf, (void *)&ss_bulk_in, sizeof(ss_bulk_in));
			buf += sizeof(ss_bulk_in);
			usb3_memcpy((void *)buf, (void *)&ep_comp, sizeof(ep_comp));
			buf += sizeof(ep_comp);
			usb3_memcpy((void *)buf, (void *)&ss_bulk_out, sizeof(ss_bulk_out));
			buf += sizeof(ss_bulk_out);
			usb3_memcpy((void *)buf, (void *)&ep_comp, sizeof(ep_comp));

			config->wTotalLength = sizeof(*config) + sizeof(intf)
				+ sizeof(ss_bulk_in) + sizeof(ep_comp)
				+ sizeof(ss_bulk_out) + sizeof(ep_comp);
			break;

		default: /* HS/FS */
		{
			struct usb_endpoint_descriptor *endp =
				(struct usb_endpoint_descriptor *)buf;

			usb3_memcpy((void *)buf, (void *)&hs_bulk_in, sizeof(hs_bulk_in));
			(endp++)->wMaxPacketSize = pcd->in_ep.maxpacket;
			buf += sizeof(hs_bulk_in);
			usb3_memcpy((void *)buf, (void *)&hs_bulk_out, sizeof(hs_bulk_out));
			(endp++)->wMaxPacketSize = pcd->out_ep.maxpacket;
		}
			config->wTotalLength = sizeof(*config) + sizeof(intf)
				+ sizeof(hs_bulk_in) + sizeof(hs_bulk_out);
			break;
		}
		value = config->wTotalLength;
	}
	break;

	case UDESC_STRING:
        {
		switch (index) {
		case STRING_LANGUAGE:
			buf[0] = 0x04;
			buf[1] = UDESC_STRING;
			buf[2] = 0x09;
			buf[3] = 0x04;

			value = 0x04;
			break;

		case STRING_MANUFACTURER:
			buf[0] = usb3_dev->string_manu_len + 2;
			buf[1] = UDESC_STRING;
			usb3_memcpy((void *)(buf+2), (void *)usb3_dev->string_manu,
				usb3_dev->string_manu_len);

			value = usb3_dev->string_manu_len + 2;
			break;

		case STRING_PRODUCT:
			buf[0] = usb3_dev->string_prod_len + 2;
			buf[1] = UDESC_STRING;

			usb3_memcpy((void *)(buf+2), (void *)usb3_dev->string_prod,
				usb3_dev->string_prod_len);

			value = usb3_dev->string_prod_len + 2;
			break;

		default:
			ep0_do_stall(pcd);
			return;
		}
	}
	break;

	case UDESC_BOS:
		if (pcd->speed != USB_SPEED_SUPER) {
		/*
			* The USB compliance test (USB 2.0 Command Verifier)
			* issues this request. We should not run into the
			* default path here. But return for now until
			* the superspeed support is added.
			*/
		}

		value = bos.wTotalLength;

		usb3_memcpy((void *)buf, (void *)&bos, sizeof(bos));
		buf += sizeof(bos);
		usb3_memcpy((void *)buf, (void *)&cap1, sizeof(cap1));
		buf += sizeof(cap1);
		usb3_memcpy((void *)buf, (void *)&cap2, sizeof(cap2));
		buf += sizeof(cap2);
		usb3_memcpy((void *)buf, (void *)&cap3, sizeof(cap3));

		break;

	default:
		ep0_do_stall(pcd);
		return;
	}

	pcd->ep0_req.bufdma = pcd->ep0_status_buf;
	pcd->ep0_req.length = value < len ? value : len;
	pcd->ep0_req.actual = 0;
	usb3_ep0_start_transfer(pcd, &pcd->ep0_req);
}

void usb3_do_setup(usb3_pcd_t *pcd)
{
	usb_device_request_t ctrl = pcd->ep0_setup_pkt->req;
	usb3_pcd_ep_t *ep0 = &pcd->ep0;
	uint16_t wlength;

	wlength = ctrl.wLength;

	ep0->stopped = 0;
	ep0->three_stage = 1;

	if (ctrl.bmRequestType & UE_DIR_IN) {
		ep0->is_in = 1;
		pcd->ep0state = EP0_IN_DATA_PHASE;
	} else {
		ep0->is_in = 0;
		pcd->ep0state = EP0_OUT_DATA_PHASE;
	}

	if (wlength == 0) {
		ep0->is_in = 1;
		pcd->ep0state = EP0_IN_WAIT_NRDY;
		ep0->three_stage = 0;
	}

	if ((UT_GET_TYPE(ctrl.bmRequestType)) != UT_STANDARD) {
		ep0_do_stall(pcd);
		return;
	}

	switch (ctrl.bRequest) {
	case UR_GET_STATUS:
		usb3_do_get_status(pcd);
		break;

	case UR_CLEAR_FEATURE:
		usb3_do_clear_feature(pcd);
		break;

	case UR_SET_FEATURE:
		usb3_do_set_feature(pcd);
		break;

	case UR_SET_ADDRESS:
		usb3_do_set_address(pcd);
		break;

	case UR_SET_CONFIG:
		usb3_do_set_config(pcd);

		/* Must wait until SetConfig before accepting U1/U2 link
		 * control, otherwise we have problems with VIA hubs
		 */
		usb3_accept_u1(pcd);
		usb3_accept_u2(pcd);

		usb_info("usb enum done\n");

        pcd->ltm_enable = 0;
		break;

	case UR_GET_CONFIG:
		usb3_do_get_config(pcd);
		break;

	case UR_GET_DESCRIPTOR:
		usb3_do_get_descriptor(pcd);
		break;

	case UR_SET_SEL:
		/* For now this is a no-op */
		pcd->ep0_req.bufdma = pcd->ep0_status_buf;
		pcd->ep0_req.length = USB3_STATUS_BUF_SIZE;
		pcd->ep0_req.actual = 0;
		ep0->send_zlp = 0;
		usb3_ep0_start_transfer(pcd, &pcd->ep0_req);
		break;

	case UR_SET_ISOC_DELAY:
		/* For now this is a no-op */
		pcd->ep0.is_in = 1;
		pcd->ep0state = EP0_IN_WAIT_NRDY;
		break;

	default:
		ep0_do_stall(pcd);
		break;
	}
}

void usb3_os_get_trb(usb3_pcd_t *pcd, usb3_pcd_ep_t *ep,
			 usb3_pcd_req_t *req)
{
	/* If EP0, fill request with EP0 IN/OUT data TRB */
	if (ep == &pcd->ep0) {
		if (ep->is_in) {
			req->trb = pcd->ep0_in_desc;
			req->trbdma = (phys_addr_t)pcd->ep0_in_desc;
		} else {
			req->trb = pcd->ep0_out_desc;
			req->trbdma = (phys_addr_t)pcd->ep0_out_desc;
		}
	/* Else fill request with TRB from the non-EP0 allocation */
	} else {
		req->trb = ep->ep_desc;
		req->trbdma = (phys_addr_t)ep->ep_desc;
	}
}

void usb3_ep0_start_transfer(usb3_pcd_t *pcd, usb3_pcd_req_t *req)
{
	usb3_pcd_ep_t *ep0 = &pcd->ep0;
	usb3_dev_ep_regs_t *ep_reg;
	usb3_dma_desc_t *desc;
	phys_addr_t desc_dma;
	uint32_t desc_type, len;
	uint8_t tri;

	/* Get the DMA Descriptor (TRB) for this request */
	usb3_os_get_trb(pcd, ep0, req);
	desc = req->trb;
	desc_dma = req->trbdma;

	if (ep0->is_in) {
		/*
		 * Start DMA on EP0-IN
		 */
		ep_reg = ep0->in_ep_reg;

		/* DMA Descriptor (TRB) setup */
		len = req->length;

		if (pcd->ep0state == EP0_IN_STATUS_PHASE) {
			if (ep0->three_stage)
				desc_type = USB3_DSCCTL_TRBCTL_STATUS_3;
			else
				desc_type = USB3_DSCCTL_TRBCTL_STATUS_2;
		} else {
			desc_type = USB3_DSCCTL_TRBCTL_CTLDATA_1ST;
		}

		usb3_fill_desc(desc, (phys_addr_t)req->bufdma,
				   len, 0, desc_type,
				   USB3_DSCCTL_IOC_BIT | USB3_DSCCTL_ISP_BIT |
				   USB3_DSCCTL_LST_BIT, 1);
		/* Issue "DEPSTRTXFER" command to EP0-IN */
		tri = usb3_dep_startxfer(pcd, ep_reg, desc_dma, 0);
		ep0->tri_in = tri;
	} else {
		/*
		 * Start DMA on EP0-OUT
		 */
		ep_reg = ep0->out_ep_reg;

		/* DMA Descriptor (TRB) setup */
		len = (req->length + ep0->maxpacket - 1) &
			~(ep0->maxpacket - 1);

		if (pcd->ep0state == EP0_OUT_STATUS_PHASE) {
			if (ep0->three_stage)
				desc_type = USB3_DSCCTL_TRBCTL_STATUS_3;
			else
				desc_type = USB3_DSCCTL_TRBCTL_STATUS_2;
		} else {
			desc_type = USB3_DSCCTL_TRBCTL_CTLDATA_1ST;
		}

		usb3_fill_desc(desc, (phys_addr_t)req->bufdma,
				   len, 0, desc_type,
				   USB3_DSCCTL_IOC_BIT | USB3_DSCCTL_ISP_BIT |
				   USB3_DSCCTL_LST_BIT, 1);
		/* Issue "DEPSTRTXFER" command to EP0-OUT */
		tri = usb3_dep_startxfer(pcd, ep_reg, desc_dma, 0);
		ep0->tri_out = tri;
	}
}

static void ep0_continue_transfer(usb3_pcd_t *pcd, usb3_pcd_req_t *req)
{
	usb3_pcd_ep_t *ep0 = &pcd->ep0;
	usb3_dev_ep_regs_t *ep_reg;
	usb3_dma_desc_t *desc;
	phys_addr_t desc_dma;
	uint8_t tri;

	/* It can be called to send a 0-length packet after the end of a transfer, so the code here
	 * only supports that case.
	 */

	if (ep0->is_in) {
		desc = pcd->ep0_in_desc;
		desc_dma = (phys_addr_t)(pcd->ep0_in_desc);
		ep_reg = ep0->in_ep_reg;

		/* DMA Descriptor Setup */
		usb3_fill_desc(desc, (phys_addr_t)req->bufdma,
				   0, 0, USB3_DSCCTL_TRBCTL_NORMAL,
				   USB3_DSCCTL_IOC_BIT | USB3_DSCCTL_ISP_BIT |
				   USB3_DSCCTL_LST_BIT, 1);

		tri = usb3_dep_startxfer(pcd, ep_reg, desc_dma, 0);
		ep0->tri_in = tri;
	}
}

void usb3_ep_start_transfer(usb3_pcd_t *pcd, usb3_pcd_ep_t *ep)
{
	usb3_pcd_req_t *req = &ep->req;
	usb3_dev_ep_regs_t *ep_reg;
	usb3_dma_desc_t *desc;
	phys_addr_t desc_dma;
	uint32_t len;
	uint8_t tri;

	/* Get the TRB for this request */
	usb3_os_get_trb(pcd, ep, req);

	ep->send_zlp = 0;
	desc = req->trb;
	desc_dma = req->trbdma;

	if (ep->is_in) {
		/* For IN, TRB length is just xfer length */
		len = req->length;
	} else {
		/* For OUT, TRB length must be multiple of maxpacket */
		/* Must be power of 2, use cheap AND */
		len = (req->length + ep->maxpacket - 1)
			& ~(ep->maxpacket - 1);

		req->length = len;
	}

	/* DMA Descriptor Setup */
	usb3_fill_desc(desc, (phys_addr_t)req->bufdma,
			   len, 0, USB3_DSCCTL_TRBCTL_NORMAL,
			   USB3_DSCCTL_ISP_BIT | USB3_DSCCTL_IOC_BIT |
			   USB3_DSCCTL_LST_BIT, 1);

	if (ep->is_in) {
		/*
		 * Start DMA on EPn-IN
		 */
		ep_reg = ep->in_ep_reg;
		/* Issue "DEPSTRTXFER" command to EP */
		//			printf("\n########%s,%d\n",__func__,__LINE__);
		tri = usb3_dep_startxfer(pcd, ep_reg,
				desc_dma, 0);
		ep->tri_in = tri;
	} else {
		/*
		 * Start DMA on EPn-OUT
		 */
		ep_reg = ep->out_ep_reg;
#if 1
		if (ep->xfer_started) {
			/* Issue "DEPUPDTXFER" command to EP */
			usb3_dep_updatexfer(pcd, ep_reg,
						ep->tri_out);
		} else {
#endif
			/* Issue "DEPSTRTXFER" command to EP */
			tri = usb3_dep_startxfer(pcd, ep_reg,
						desc_dma, 0);
			ep->tri_out = tri;
			ep->xfer_started = 1;
		}
	}
}

void usb3_bulk_out_transfer(void *dev)
{
	usb3_pcd_t *pcd = (usb3_pcd_t *)dev;
	usb3_pcd_ep_t *ep = &pcd->out_ep;
	usb3_pcd_req_t *req = &ep->req;

	/* req->actual = 0; */
	req->length = ep->maxpacket;
	req->bufdma = pcd->ss_bulk_buf;
	req->complete = usb3_handle_protocol;

	usb3_ep_start_transfer(pcd, ep);

	return;
}

void usb3_bulk_out_continue_transfer(void *dev)
{
	usb3_pcd_t *pcd = (usb3_pcd_t *)dev;
	usb3_pcd_ep_t *ep = &pcd->out_ep;

	usb3_ep_start_transfer(pcd, ep);
}

void usb_tx_status_complete(void *dev)
{
}

void usb3_bulk_in_transfer(void *dev, const char *status)
{
	usb3_pcd_t *pcd = (usb3_pcd_t *)dev;
	usb3_pcd_ep_t *ep = &pcd->in_ep;
	usb3_pcd_req_t *req = &ep->req;
	int len;

	len = strlen(status)+1;
	memset(req->bufdma, 0, 512);
	memcpy(req->bufdma,status,len);
	req->length = len;

	/* req->actual = 0; */
	req->complete = usb_tx_status_complete;

	usb3_ep_start_transfer(pcd, ep);
}

static void ep0_complete_request(usb3_pcd_t *pcd, usb3_pcd_req_t *req,
				usb3_dma_desc_t *desc, int status)
{
	usb3_pcd_ep_t *ep = &pcd->ep0;

	if (!req)
		return;

	if (pcd->ep0state == EP0_OUT_DATA_PHASE ||
		pcd->ep0state == EP0_IN_DATA_PHASE) {
		if (ep->is_in) {
			if (usb3_get_xfercnt(desc) == 0) {
				pcd->ep0.is_in = 0;
				pcd->ep0state = EP0_OUT_WAIT_NRDY;
			}
		} else {
			pcd->ep0.is_in = 1;
			pcd->ep0state = EP0_IN_WAIT_NRDY;
		}
	}
}

static void setup_in_status_phase(usb3_pcd_t *pcd, void *buf)
{
	usb3_pcd_ep_t *ep0 = &pcd->ep0;

	if (pcd->ep0state == EP0_STALL) {
		return;
	}

	ep0->is_in = 1;
	pcd->ep0state = EP0_IN_STATUS_PHASE;

	pcd->ep0_req.bufdma = buf;
	pcd->ep0_req.length = 0;
	pcd->ep0_req.actual = 0;
	usb3_ep0_start_transfer(pcd, &pcd->ep0_req);
}

static void setup_out_status_phase(usb3_pcd_t *pcd, void *buf)
{
	usb3_pcd_ep_t *ep0 = &pcd->ep0;

	if (pcd->ep0state == EP0_STALL) {
		return;
	}

	ep0->is_in = 0;
	pcd->ep0state = EP0_OUT_STATUS_PHASE;

	pcd->ep0_req.bufdma = buf;
	pcd->ep0_req.length = 0;
	pcd->ep0_req.actual = 0;
	usb3_ep0_start_transfer(pcd, &pcd->ep0_req);
}

void usb3_handle_ep0(usb3_pcd_t *pcd, usb3_pcd_req_t *req,
			 uint32_t event)
{
	usb3_pcd_ep_t *ep0 = &pcd->ep0;
	usb3_dma_desc_t *desc;
	uint32_t byte_count, len;
	uint32_t status;

	switch (pcd->ep0state) {
	case EP0_IN_DATA_PHASE:
		if (!req)
			req = &pcd->ep0_req;
		desc = pcd->ep0_in_desc;

		if (dwc_usb3_is_hwo(desc)) {
			goto out;
		}

		status = usb3_get_xfersts(desc);
		if (status & USB3_TRBRSP_SETUP_PEND) {
			/* Start of a new Control transfer */
			desc->status = 0;
		}

		byte_count = req->length - usb3_get_xfercnt(desc);
		req->actual += byte_count;
		req->bufdma += byte_count;

		if (req->actual < req->length) {
			/* IN CONTINUE, Stall EP0 */
			ep0_do_stall(pcd);
		} else if (ep0->send_zlp) {
			/* CONTINUE TRANSFER IN ZLP */
			ep0_continue_transfer(pcd, req);
			ep0->send_zlp = 0;
		} else {
			/* COMPLETE IN TRANSFER */
			ep0_complete_request(pcd, req, desc, 0);
		}

		break;

	case EP0_OUT_DATA_PHASE:
		if (!req)
			req = &pcd->ep0_req;
		desc = pcd->ep0_out_desc;

		if (dwc_usb3_is_hwo(desc)) {
			goto out;
		}

		status = usb3_get_xfersts(desc);
		if (status & USB3_TRBRSP_SETUP_PEND) {
			/* Start of a new Control transfer */
		}

		len = (req->length + ep0->maxpacket - 1) &
			~(ep0->maxpacket - 1);
		byte_count = len - usb3_get_xfercnt(desc);
		req->actual += byte_count;
		req->bufdma += byte_count;

		if (ep0->send_zlp) {
			/* CONTINUE TRANSFER OUT ZLP */
			ep0_continue_transfer(pcd, req);
			ep0->send_zlp = 0;

		} else {
			/* COMPLETE OUT TRANSFER */
			ep0_complete_request(pcd, req, desc, 0);
		}

		break;

	case EP0_IN_WAIT_NRDY:
	case EP0_OUT_WAIT_NRDY:
		if (ep0->is_in)
			setup_in_status_phase(pcd, pcd->ep0_setup_pkt);
		else
			setup_out_status_phase(pcd, pcd->ep0_setup_pkt);

		break;

	case EP0_IN_STATUS_PHASE:
	case EP0_OUT_STATUS_PHASE:
		if (ep0->is_in)
			desc = pcd->ep0_in_desc;
		else
			desc = pcd->ep0_out_desc;
		ep0_complete_request(pcd, req, desc, 0);

		pcd->ep0state = EP0_IDLE;
		ep0->stopped = 1;
		ep0->is_in = 0;	/* OUT for next SETUP */

		/* Prepare for more SETUP Packets */
		usb3_ep0_out_start(pcd);
		break;

	case EP0_STALL:
		break;

	case EP0_IDLE:
		break;
	}
out:
	return;
}

void usb3_os_handle_ep0(usb3_pcd_t *pcd, uint32_t event)
{
	usb3_pcd_req_t *req = NULL;

	if (pcd->ep0state == EP0_IDLE) {
		usb3_do_setup(pcd);
	} else {
		usb3_handle_ep0(pcd, req, event);
	}
}

void usb3_request_done(usb3_pcd_t *pcd, usb3_pcd_ep_t *ep,
			   usb3_pcd_req_t *req, int status)
{

	if (ep != &pcd->ep0)
		req->trb = NULL;
	if (req->complete)
		req->complete(pcd);

	req->actual = 0;

	return;
}
extern int usb_out_open;
int usb3_ep_complete_request(usb3_pcd_t *pcd,
                 usb3_pcd_ep_t *ep, uint32_t event)
{
	usb3_pcd_req_t *req = &ep->req;
	usb3_dma_desc_t *desc = req->trb;
	uint32_t byte_count;
	int error = USB_NO_ERR;

	ep->send_zlp = 0;

	if (!desc) {
		return USB_PROCESS_ERR;
	}
#if 0
	if (dwc_usb3_is_hwo(desc)) {
		return USB_PROCESS_ERR;
	}
#endif
	if (ep->is_in) {
		/* IN endpoint */
		if (usb3_get_xfercnt(desc) == 0) {
			req->actual += req->length;
		}
		/* Reset IN tri */
		ep->tri_in = 0;

		/* Complete the IN request */
		usb3_request_done(pcd, ep, req, 0);
	} else {   /* OUT endpoint */
		byte_count = req->length -
					usb3_get_xfercnt(desc);
		req->actual += byte_count;
		req->bufdma += byte_count;
		pcd->file_received += byte_count;
		/* Reset OUT tri */
		ep->tri_out = 0;

		/* OUT transfer complete or not */
		if ((byte_count < ep->maxpacket) ||
			(pcd->file_capacity <= pcd->file_received - FRAME_HEAD_LEN)) {
			/* Complete the OUT request */
			usb3_request_done(pcd, ep, req, 0);
		} else {
			usb3_bulk_out_continue_transfer((void *)pcd);
		}
	}

	return error;
}

