#ifndef __USB3_H__
#define __USB3_H__

#include "asm/types.h"
#include "types.h"

#define UCONSTW(x)	{ (x) & 0xff, ((x) >> 8) & 0xff }
#define UCONSTDW(x)	{ (x) & 0xff, ((x) >> 8) & 0xff, \
			  ((x) >> 16) & 0xff, ((x) >> 24) & 0xff }

#define HUAWEI_VENDOR_ID        0x12D1
#define HUAWEI_PRODUCT_ID       0xD001
//#define HUAWEI_PRODUCT_ID       0x3609

#define STRING_LANGUAGE         0
#define STRING_MANUFACTURER     1
#define STRING_PRODUCT          2

#define USB_SPEED_UNKNOWN	    0x00
#define USB_SPEED_LOW		    0x01
#define USB_SPEED_FULL		    0x02
#define USB_SPEED_HIGH		    0x03
#define USB_SPEED_VARIABLE	    0x04
#define USB_SPEED_SUPER		    0x05

#define  UDESC_DEVICE		    0x01
#define  UDESC_CONFIG		    0x02
#define  UDESC_STRING		    0x03
#define  UDESC_INTERFACE	    0x04
#define  UDESC_ENDPOINT		    0x05
#define  UDESC_SS_USB_COMPANION	0x30
#define  UDESC_DEVICE_QUALIFIER	0x06
#define  UDESC_BOS		        0x0f
#define  UDESC_DEVICE_CAPABILITY 0x10

#define UT_GET_DIR(a) ((a) & 0x80)
#define UT_WRITE		0x00
#define UT_READ			0x80

#define UT_GET_TYPE(a) ((a) & 0x60)
#define UT_STANDARD		0x00
#define UT_CLASS		0x20
#define UT_VENDOR		0x40

#define UT_GET_RECIPIENT(a) ((a) & 0x1f)
#define UT_DEVICE		0x00
#define UT_INTERFACE    0x01
#define UT_ENDPOINT		0x02
#define UT_OTHER		0x03

#define UR_GET_STATUS		0x00
#define UR_CLEAR_FEATURE	0x01
#define UR_SET_FEATURE		0x03
#define UR_SET_ADDRESS		0x05
#define UR_GET_DESCRIPTOR	0x06
#define UR_SET_DESCRIPTOR	0x07
#define UR_GET_CONFIG		0x08
#define UR_SET_CONFIG		0x09
#define UR_GET_INTERFACE	0x0a
#define UR_SET_INTERFACE	0x0b
#define UR_SYNCH_FRAME		0x0c
#define UR_SET_SEL		    0x30
#define UR_SET_ISOC_DELAY	0x31

/* Feature numbers */
#define UF_ENDPOINT_HALT	        0
#define UF_DEVICE_REMOTE_WAKEUP	    1
#define UF_TEST_MODE		        2
#define UF_DEVICE_B_HNP_ENABLE	    3
#define UF_DEVICE_A_HNP_SUPPORT	    4
#define UF_DEVICE_A_ALT_HNP_SUPPORT 5
#define UF_FUNCTION_SUSPEND	0
#define UF_U1_ENABLE		48
#define UF_U2_ENABLE		49
#define UF_LTM_ENABLE		50

/* OTG feature selectors */
#define UOTG_B_HNP_ENABLE	    3
#define UOTG_A_HNP_SUPPORT	    4
#define UOTG_A_ALT_HNP_SUPPORT	5
#define UOTG_NTF_HOST_REL	    51
#define UOTG_B3_RSP_ENABLE	    52

#define UE_GET_DIR(a)	((a) & 0x80)
#define UE_SET_DIR(a,d)	((a) | (((d)&1) << 7))
#define UE_DIR_IN	0x80
#define UE_DIR_OUT	0x00
#define UE_ADDR		0x0f
#define UE_GET_ADDR(a)	((a) & UE_ADDR)

/** Maxpacket size for EP0, defined by USB3 spec */
#define USB3_MAX_EP0_SIZE	    512

/** Maxpacket size for any EP, defined by USB3 spec */
#define USB3_MAX_PACKET_SIZE	    1024
#define USB2_HS_MAX_PACKET_SIZE     512
#define USB2_FS_MAX_PACKET_SIZE     64

#define USB3_BULK_IN_EP         1
#define USB3_BULK_OUT_EP        1

typedef struct usb_device_request {
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} usb_device_request_t;

#pragma pack(1)
/** USB_DT_DEVICE: Device descriptor */
typedef struct usb_device_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;

	uint16_t bcdUSB;
#define USB_CLASS_COMM          0x02
#define USB_CLASS_VENDOR_SPEC   0xFF
#define USB_SC_VENDOR_SPEC      0xFF
#define USB_PR_VENDOR_SPEC      0xFF
	uint8_t  bDeviceClass;
	uint8_t  bDeviceSubClass;
	uint8_t  bDeviceProtocol;
	uint8_t  bMaxPacketSize0;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t  iManufacturer;
	uint8_t  iProduct;
	uint8_t  iSerialNumber;
	uint8_t  bNumConfigurations;
} usb_device_descriptor_t;

/* USB_DT_CONFIG: Config descriptor */
typedef struct usb_config_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;

	uint16_t wTotalLength;
	uint8_t  bNumInterfaces;
#define CONFIG_VALUE    1
	uint8_t  bConfigurationValue;
	uint8_t  iConfiguration;
#define USB_CONFIG_ATT_ONE      (1 << 7)
	uint8_t  bmAttributes;
#define USB_CONFIG_VBUS_DRAW    (0xFA)
	uint8_t  bMaxPower;
} usb_config_descriptor_t;

/* USB_DT_DEVICE_QUALIFIER: Device Qualifier descriptor */
typedef struct usb_qualifier_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;

	uint16_t bcdUSB;
	uint8_t  bDeviceClass;
	uint8_t  bDeviceSubClass;
	uint8_t  bDeviceProtocol;
	uint8_t  bMaxPacketSize0;
	uint8_t  bNumConfigurations;
	uint8_t  bRESERVED;
} usb_qualifier_descriptor_t;

/* USB_DT_INTERFACE: Interface descriptor */
typedef struct usb_interface_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;

	uint8_t  bInterfaceNumber;
	uint8_t  bAlternateSetting;
	uint8_t  bNumEndpoints;
	uint8_t  bInterfaceClass;
	uint8_t  bInterfaceSubClass;
	uint8_t  bInterfaceProtocol;
	uint8_t  iInterface;
} usb_interface_descriptor_t;

/* USB_DT_ENDPOINT: Endpoint descriptor */
typedef struct usb_endpoint_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;

	uint8_t  bEndpointAddress;
	uint8_t  bmAttributes;
#define USB_ENDPOINT_XFER_CONTROL	0x00
#define USB_ENDPOINT_XFER_ISOC		0x01
#define USB_ENDPOINT_XFER_BULK		0x02
#define USB_ENDPOINT_XFER_INT		0x03
	uint16_t wMaxPacketSize;
	uint8_t  bInterval;
} usb_endpoint_descriptor_t;

/* USB_DT_SS_ENDPOINT_COMP: SuperSpeed Endpoint Companion descriptor */
typedef struct usb_ss_ep_comp_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;

	uint8_t  bMaxBurst;
	uint8_t  bmAttributes;
	uint16_t wBytesPerInterval;
} usb_ss_ep_comp_descriptor_t;

/* WUSB BOS Descriptor (Binary device Object Store) */
typedef struct wusb_bos_desc {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t wTotalLength;
	uint8_t bNumDeviceCaps;
} wusb_bos_desc_t;

#define USB_DEVICE_CAPABILITY_20_EXTENSION	0x02
typedef struct usb_dev_cap_20_ext_desc {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDevCapabilityType;
#define USB_20_EXT_LPM				0x02
	uint32_t bmAttributes;
} usb_dev_cap_20_ext_desc_t;

#define USB_DEVICE_CAPABILITY_SS_USB		0x03
typedef struct usb_dev_cap_ss_usb {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDevCapabilityType;
#define USB_DC_SS_USB_LTM_CAPABLE		0x02
	uint8_t bmAttributes;
#define USB_DC_SS_USB_SPEED_SUPPORT_LOW		0x01
#define USB_DC_SS_USB_SPEED_SUPPORT_FULL	0x02
#define USB_DC_SS_USB_SPEED_SUPPORT_HIGH	0x04
#define USB_DC_SS_USB_SPEED_SUPPORT_SS		0x08
	uint32_t wSpeedsSupported;
	uint8_t bFunctionalitySupport;
	uint8_t bU1DevExitLat;
	uint32_t wU2DevExitLat;
} usb_dev_cap_ss_usb_t;

#define USB_DEVICE_CAPABILITY_CONTAINER_ID	0x04
typedef struct usb_dev_cap_container_id {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDevCapabilityType;
	uint8_t bReserved;
	uint8_t containerID[16];
} usb_dev_cap_container_id_t;
#pragma pack()

#endif /* __USB3_H__ */

