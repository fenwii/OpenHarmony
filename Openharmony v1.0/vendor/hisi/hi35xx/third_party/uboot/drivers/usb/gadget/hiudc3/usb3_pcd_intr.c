#include "usb3_drv.h"
#include "usb3_pcd.h"

static void handle_usb_reset_intr(usb3_pcd_t *pcd)
{
	usb3_pcd_ep_t *ep;

	/* Clear stall on each EP */
	ep = &pcd->in_ep;
	if (ep->stopped)
		usb3_ep_clear_stall(pcd, ep);

	ep = &pcd->out_ep;
	if (ep->stopped)
		usb3_ep_clear_stall(pcd, ep);

	/* Set Device Address to 0 */
	usb3_set_address(pcd, 0);

	pcd->ltm_enable = 0;
}

static void handle_connect_done_intr(usb3_pcd_t *pcd)
{
	usb3_pcd_ep_t *ep0 = &pcd->ep0;
	uint32_t diepcfg0, doepcfg0, diepcfg1, doepcfg1;
	usb3_dev_ep_regs_t *ep_reg;
	int speed;

	ep0->stopped = 0;
	speed = usb3_get_device_speed(pcd);
	pcd->speed = speed;

	usb3_pcd_set_speed(pcd, speed);

	/*
	 * Set the MPS of EP0 based on the connection speed
	 */
	diepcfg0 = USB3_EP_TYPE_CONTROL << USB3_EPCFG0_EPTYPE_SHIFT;
	diepcfg0 |= USB3_CFG_ACTION_MODIFY << USB3_EPCFG0_CFG_ACTION_SHIFT;
	diepcfg1 = USB3_EPCFG1_XFER_CMPL_BIT | USB3_EPCFG1_XFER_IN_PROG_BIT | USB3_EPCFG1_XFER_NRDY_BIT |
		   USB3_EPCFG1_EP_DIR_BIT;

	doepcfg0 = USB3_EP_TYPE_CONTROL << USB3_EPCFG0_EPTYPE_SHIFT;
	doepcfg0 |= USB3_CFG_ACTION_MODIFY << USB3_EPCFG0_CFG_ACTION_SHIFT;
	doepcfg1 = USB3_EPCFG1_XFER_CMPL_BIT | USB3_EPCFG1_XFER_IN_PROG_BIT | USB3_EPCFG1_XFER_NRDY_BIT;

	switch (speed) {
	case USB_SPEED_SUPER:
		diepcfg0 |= 512 << USB3_EPCFG0_MPS_SHIFT;
		doepcfg0 |= 512 << USB3_EPCFG0_MPS_SHIFT;
		break;

	case USB_SPEED_HIGH:
	case USB_SPEED_FULL:
		diepcfg0 |= 64 << USB3_EPCFG0_MPS_SHIFT;
		doepcfg0 |= 64 << USB3_EPCFG0_MPS_SHIFT;
		break;

	case USB_SPEED_LOW:
		diepcfg0 |= 8 << USB3_EPCFG0_MPS_SHIFT;
		doepcfg0 |= 8 << USB3_EPCFG0_MPS_SHIFT;
		break;
	}

	diepcfg0 |= ep0->tx_fifo_num << USB3_EPCFG0_TXFNUM_SHIFT;

	/* Issue "DEPCFG" command to EP0-OUT */
	ep_reg = &pcd->out_ep_regs[0];
	usb3_dep_cfg(pcd, ep_reg, doepcfg0, doepcfg1, 0);

	/* Issue "DEPCFG" command to EP0-IN */
	ep_reg = &pcd->in_ep_regs[0];
	usb3_dep_cfg(pcd, ep_reg, diepcfg0, diepcfg1, 0);

	pcd->state = USB3_STATE_DEFAULT;
}

int usb3_handle_ep_intr(usb3_pcd_t *pcd, uint32_t physep, uint32_t event)
{
	usb3_pcd_ep_t *ep;
	int epnum, is_in;
	int error = USB_NO_ERR;

	/* Physical Out EPs are even, physical In EPs are odd */
	is_in = physep & 1;
	epnum = (physep >> 1) & 0xf;

	/* Get EP pointer */
	if (is_in) {
		ep = usb3_get_in_ep(pcd, epnum);
	} else {
		ep = usb3_get_out_ep(pcd, epnum);
	}
//printf("\n##########%s,%d,event=0x%x\n",__func__,__LINE__,event);
	switch (event & USB3_DEPEVT_INTTYPE_BITS) {
	case USB3_DEPEVT_XFER_CMPL << USB3_DEPEVT_INTTYPE_SHIFT:
		ep->xfer_started = 0;

		/* Complete the transfer */
		if (0 == epnum) {
			usb3_os_handle_ep0(pcd, event);
		} else {
//printf("\n##########%s,%d,event=0x%x\n",__func__,__LINE__,event);
			error = usb3_ep_complete_request(pcd, ep, event);
		}
		break;

	case USB3_DEPEVT_XFER_NRDY << USB3_DEPEVT_INTTYPE_SHIFT:
		if (0 == epnum) {
			switch (pcd->ep0state) {
			case EP0_IN_WAIT_NRDY:
				if (is_in) {
					usb3_os_handle_ep0(pcd, event);
				}
				break;
			case EP0_OUT_WAIT_NRDY:
				if (!is_in) {
					usb3_os_handle_ep0(pcd, event);
				}
				break;
			default:
				break;
			}
		}
		break;
	}

	return error;
}

void usb3_handle_dev_intr(usb3_pcd_t *pcd, uint32_t event)
{
	uint32_t dint = (event >> USB3_DEVT_SHIFT) &
			(USB3_DEVT_BITS >> USB3_DEVT_SHIFT);

	switch (dint) {
	case USB3_DEVT_USBRESET:
		handle_usb_reset_intr(pcd);
		break;

	case USB3_DEVT_CONNDONE:
		handle_connect_done_intr(pcd);
		break;
	}
}

