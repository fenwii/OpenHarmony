#include "usb3.h"
#include "usb3_drv.h"
#include "usb3_pcd.h"
#include "usb3_prot.h"
#include "onchiprom.h"

#include <common.h>
#include <linux/string.h>

#define USTART  0xFA
#define UHEAD   0xFE
#define UDATA   0xDA
#define UTAIL   0xED
#define UCMD    0XAB
#define UREQ    0XFB


char uACK[2] = {0xAA,'\0'};
char uNAK[2] = {0x55,'\0'};
char tx_state[200];
static phys_addr_t  rx_addr;
static uint32_t  rx_length;
extern int usb_connected;
int usb_out_open = 0;

void usb3_bulk_out_transfer_cmd(void *dev)
{
	usb3_pcd_t *pcd = (usb3_pcd_t *)dev;
	usb3_pcd_ep_t *ep = &pcd->out_ep;
	usb3_pcd_req_t *req = &ep->req;

	memset(pcd->ss_bulk_buf, 0x0, USB3_BULK_BUF_SIZE);
	/* req->actual = 0; */
	req->length = ep->maxpacket;
	req->bufdma =  pcd->ss_bulk_buf;
	req->complete = usb3_handle_protocol;
	usb3_ep_start_transfer(pcd, ep);

	return;
}

void usb3_handle_data(void *dev)
{
	usb3_pcd_t *pcd = (usb3_pcd_t *)dev;
	usb3_pcd_ep_t *ep = &pcd->out_ep;
	usb3_pcd_req_t *req = &ep->req;

	if (req->actual > rx_length) {
		req->actual = rx_length;
	}

	rx_addr += req->actual;
	rx_length -= req->actual;

	if (rx_length > 0) {
		usb3_bulk_out_transfer_data(dev);
	} else {
		usb3_bulk_out_transfer_cmd(dev);
	}
}

int usb3_bulk_out_transfer_data(void *dev)
{
	usb3_pcd_t *pcd = (usb3_pcd_t *)dev;
	usb3_pcd_ep_t *ep = &pcd->out_ep;
	usb3_pcd_req_t *req = &ep->req;

	/* req->actual = 0; */

	/* For DWC3 controller,If CHN=0 and HWO=0 for the TRB, this field represents the total remaining Buffer
	 * Descriptor buffer size in bytes. Valid Range: 0 bytes to (16 MB - 1 byte).
	 * The hardware decrements this field to represent the remaining buffer size after data is
	 * transferred.
	 * Note: for bulk transfer, max length = 16MB - maxpacket;
	 * */
	if(rx_length >= (USB3_DSCSTS_XFRCNT_MAX - ep->maxpacket)) {
		req->length = USB3_DSCSTS_XFRCNT_MAX - ep->maxpacket;
	} else {
		req->length = rx_length;
	}

	req->bufdma = (uint8_t *)rx_addr;
	req->complete = usb3_handle_data;

	usb3_ep_start_transfer(pcd, ep);

	return USB_NO_ERR;
}

void udc_puts(const char *s)
{
	if (strlen(s) > 200)
		return;
	else {
		if (usb_out_open == 1) {
			strcat(tx_state, s);
		}
	}
}

typedef int (*USB3_HANDLE_REQUEST)(uint8_t * const buff, unsigned int * bufflen);
USB3_HANDLE_REQUEST handle_request = NULL;
void SetUSB3CallBackFunc(USB3_HANDLE_REQUEST func)
{
	handle_request = func;
}

void usb3_handle_protocol(void *dev)
{
	usb3_pcd_t *pcd = (usb3_pcd_t *)dev;
	int ret;
	char *buf = (char *)pcd->ss_bulk_buf;

	if (buf[0]==USTART) {
		usb3_bulk_out_transfer_cmd(pcd);
		usb3_bulk_in_transfer(dev, uACK);
	} else if(buf[0]==UHEAD) {
		rx_addr = (buf[5] <<24)|(buf[6] <<16)|(buf[7] <<8)|(buf[8]);
		rx_length =(buf[1]<<24)|(buf[2] <<16)|(buf[3] <<8)|(buf[4]);
		if (rx_addr == rx_length) {
			usb3_bulk_out_transfer_cmd(pcd);
			usb_connected = 1;
			usb_out_open = 1;
		} else {
			usb3_bulk_out_transfer_data(pcd);
		}
		usb3_bulk_in_transfer(dev, uACK);
		return;

	} else if(buf[0]==UCMD) {
		strcat(tx_state, " ");

#if 0
		usb_out_open = 0;
		puts ((const char *)(buf+3) ? (const char *)(buf+3) : "NULL");
		puts ("\n");
#endif
		usb_out_open = 1;
		ret = run_command(buf+3,0);
		if (ret) {
			usb3_bulk_in_transfer(dev, "[EOT](ERROR)\r\n");
		} else {
			strcat(tx_state, "[EOT](OK)\r\n");
			usb3_bulk_out_transfer_cmd(pcd);
			usb3_bulk_in_transfer(dev, tx_state);
			memset(tx_state, 0, 200);
		}
	} else if (buf[0]==UTAIL) {
		if(rx_length>0) {
			usb3_bulk_out_transfer_cmd(pcd);
			usb3_bulk_in_transfer(dev, uNAK);
		} else {
			usb3_bulk_in_transfer(dev, uACK);
			usb3_bulk_out_transfer_cmd(pcd);
		}
	} else if (buf[0]==UREQ) {
		usb_out_open = 0;
		if (handle_request != NULL) {
			usb3_pcd_ep_t *ep = &pcd->in_ep;
			usb3_pcd_req_t *req = &ep->req;

			memset(req->bufdma, 0, 512);
			req->length = 0;
			ret = (*handle_request)(req->bufdma, &req->length);

			/* req->actual = 0; */
			extern void usb_tx_status_complete(void *dev);
			req->complete = usb_tx_status_complete;
			usb3_ep_start_transfer(pcd, ep);

			usb3_bulk_out_transfer_cmd(pcd);
		}
	}
}
