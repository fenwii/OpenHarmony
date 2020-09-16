#include "usb3.h"
#include "usb3_hw.h"
#include "usb3_drv.h"
#include "sys.h"
#include "onchiprom.h"
#include "common.h"

#include <cpu_func.h>
#include <linux/string.h>
#include <malloc.h>
#include <linux/compat.h>
#include "../../../phy/hibvt/usb_hisi.h"

void usb3_handle_event(usb3_device_t *dev);
void usb3_enable_device_interrupts(usb3_device_t *dev);
void usb3_dis_flush_eventbuf_intr(usb3_device_t *dev);
void usb3_init_eventbuf(usb3_device_t *dev, uint32_t size, phys_addr_t dma_addr);
#define udelay_100us udelay
#define msleep udelay
void usb3_memset(void *buf, uint8_t value, uint32_t size)
{
	uint8_t *pbuf = (uint8_t *)buf;

	while (size--) {
		*pbuf++ = value;
	}
}

void usb3_memcpy(void *dst, void *src, uint32_t size)
{
	uint8_t *pdst = (uint8_t *)dst;
	uint8_t *psrc = (uint8_t *)src;

	if (psrc > pdst) {
		while (size--) {
			*pdst++ = *psrc++;
		}
	} else {
		pdst += size - 1;
		psrc += size - 1;
		while (size--) {
			*pdst-- = *psrc--;
		}
	}
}

uint32_t usb3_rd32(volatile uint32_t *addr)
{
	return *(volatile uint32_t *)(addr);
}
extern int usb_out_open;
void usb3_wr32(volatile uint32_t *addr, uint32_t val)
{
	*(volatile uint32_t *)(addr) = val;
    udelay(200);
}

uint32_t usb3_is_host_mode(usb3_device_t *dev)
{
	return usb3_rd32(&dev->core_global_regs->gsts) & 0x01;
}

void pcd_epinit(usb3_pcd_t *pcd)
{
	usb3_pcd_ep_t *ep;

	/* Init EP0 */
	do {
		ep = &pcd->ep0;

		ep->pcd = pcd;
		ep->stopped = 1;
		ep->is_in = 0;
		ep->active = 0;
		ep->phys = 0;
		ep->num = 0;
		ep->tx_fifo_num = 0;
		ep->out_ep_reg = &pcd->out_ep_regs[0];
		ep->in_ep_reg = &pcd->in_ep_regs[0];

		ep->type = USB3_EP_TYPE_CONTROL;
		ep->maxburst = 0;
		ep->maxpacket = 64;
		ep->send_zlp = 0;

		ep->req.length = 0;
		ep->req.actual = 0;

		pcd->ep0_req.length = 0;
		pcd->ep0_req.actual = 0;
	} while(0);

	/* Init EP1-OUT */
	do {
		ep = &pcd->out_ep;

		ep->pcd = pcd;
		ep->stopped = 1;
		ep->is_in = 0;
		ep->active = 0;
		ep->phys = USB3_BULK_OUT_EP << 1;
		ep->num = 1;
		ep->tx_fifo_num = 0;
		ep->out_ep_reg = &pcd->out_ep_regs[USB3_BULK_OUT_EP];

		/* Bulk EP is activated */
		ep->type = USB3_EP_TYPE_BULK;
		ep->maxburst = 0;
		ep->maxpacket = USB2_FS_MAX_PACKET_SIZE;
		ep->send_zlp = 0;

		ep->req.length = 0;
		ep->req.actual = 0;
	} while(0);

	/* Init EP1-IN */
	do {
		ep = &pcd->in_ep;

		ep->pcd = pcd;
		ep->stopped = 1;
		ep->is_in = 1;
		ep->active = 0;
		ep->phys = (USB3_BULK_IN_EP << 1) | 1;
		ep->num = 1;
		ep->tx_fifo_num = USB3_BULK_IN_EP;
		ep->in_ep_reg = &pcd->in_ep_regs[USB3_BULK_IN_EP];

		/* Bulk EP is activated */
		ep->type = USB3_EP_TYPE_BULK;
		ep->maxburst = 0;
		ep->maxpacket = USB2_FS_MAX_PACKET_SIZE;
		ep->send_zlp = 0;

		ep->req.length = 0;
		ep->req.actual = 0;
	} while(0);

	pcd->ep0state = EP0_IDLE;
}

void usb3_set_address(usb3_pcd_t *pcd, uint32_t addr)
{
	uint32_t dcfg;

	dcfg = usb3_rd32(&pcd->dev_global_regs->dcfg);
	dcfg &= ~USB3_DCFG_DEVADDR_BITS;
	dcfg |= addr << USB3_DCFG_DEVADDR_SHIFT;
	usb3_wr32(&pcd->dev_global_regs->dcfg, dcfg);
}

#define RAM_WIDTH       8
#define RAM_RX_DEPTH    4096
#define RAM_TX0_DEPTH   1024
#define RAM_TX1_DEPTH   2048
void usb3_set_tx_fifo_size(usb3_device_t *dev)
{
	usb3_core_global_regs_t *global_regs =
						dev->core_global_regs;
	uint32_t prev_start = 0;
	/* Set 1K for tx fifo0 */
	usb3_wr32(&global_regs->gtxfifosiz[0],
		 ((RAM_TX0_DEPTH / RAM_WIDTH) << USB3_FIFOSZ_DEPTH_SHIFT) |
		 (prev_start << USB3_FIFOSZ_STARTADDR_SHIFT));

	prev_start += RAM_TX0_DEPTH / RAM_WIDTH;
	/* Set 2K for tx fifo1 */
	usb3_wr32(&global_regs->gtxfifosiz[1],
		 ((RAM_TX1_DEPTH / RAM_WIDTH) << USB3_FIFOSZ_DEPTH_SHIFT) |
		 (prev_start << USB3_FIFOSZ_STARTADDR_SHIFT));
}

void usb3_set_rx_fifo_size(usb3_device_t *dev)
{
	usb3_core_global_regs_t *global_regs =
						dev->core_global_regs;
	/* Set 4K for rx fifo */
	usb3_wr32(&global_regs->grxfifosiz[0],
		 ((RAM_RX_DEPTH / RAM_WIDTH) << USB3_FIFOSZ_DEPTH_SHIFT));
}

void usb3_resume_usb2_phy(usb3_pcd_t *pcd)
{
	uint32_t usb2phycfg;

	usb2phycfg = usb3_rd32(&pcd->usb3_dev->core_global_regs->gusb2phycfg[0]);
	usb2phycfg |= USB3_USB2PHYCFG_SUS_PHY_BIT;
	usb3_wr32(&pcd->usb3_dev->core_global_regs->gusb2phycfg[0], usb2phycfg);
}

void usb3_resume_usb3_phy(usb3_pcd_t *pcd)
{
	uint32_t pipectl;

	pipectl = usb3_rd32(&pcd->usb3_dev->core_global_regs->gusb3pipectl[0]);
	pipectl |= USB3_PIPECTL_SUS_PHY_BIT;
	usb3_wr32(&pcd->usb3_dev->core_global_regs->gusb3pipectl[0],
			pipectl);
}

void usb3_accept_u1(usb3_pcd_t *pcd)
{
	uint32_t dctl;

	dctl = usb3_rd32(&pcd->dev_global_regs->dctl);
	dctl |= USB3_DCTL_ACCEPT_U1_EN_BIT;
	usb3_wr32(&pcd->dev_global_regs->dctl, dctl);
}

void usb3_accept_u2(usb3_pcd_t *pcd)
{
}

void usb3_enable_u1(usb3_pcd_t *pcd)
{
	uint32_t dctl;

	dctl = usb3_rd32(&pcd->dev_global_regs->dctl);
	dctl |= USB3_DCTL_INIT_U1_EN_BIT;
	usb3_wr32(&pcd->dev_global_regs->dctl, dctl);
}

void usb3_enable_u2(usb3_pcd_t *pcd)
{
}

void usb3_disable_u1(usb3_pcd_t *pcd)
{
}

void usb3_disable_u2(usb3_pcd_t *pcd)
{
	uint32_t dctl;

	dctl = usb3_rd32(&pcd->dev_global_regs->dctl);
	dctl &= ~USB3_DCTL_INIT_U2_EN_BIT;
	usb3_wr32(&pcd->dev_global_regs->dctl, dctl);
}

uint32_t usb3_u1_enabled(usb3_pcd_t *pcd)
{
	uint32_t dctl;

	dctl = usb3_rd32(&pcd->dev_global_regs->dctl);
	return !!(dctl & USB3_DCTL_INIT_U1_EN_BIT);
}

uint32_t usb3_u2_enabled(usb3_pcd_t *pcd)
{
	uint32_t dctl;

	dctl = usb3_rd32(&pcd->dev_global_regs->dctl);
	return !!(dctl & USB3_DCTL_INIT_U2_EN_BIT);
}

void usb3_dep_cstall(usb3_pcd_t *pcd,
			usb3_dev_ep_regs_t *ep_reg)
{
	/* Start the command */
	usb3_wr32(&ep_reg->depcmd,
		 USB3_EPCMD_CLR_STALL | USB3_EPCMD_ACT_BIT);

	/* Wait for command completion */
	handshake(pcd->usb3_dev, &ep_reg->depcmd, USB3_EPCMD_ACT_BIT, 0);
}

void usb3_dep_sstall(usb3_pcd_t *pcd,
			usb3_dev_ep_regs_t *ep_reg)
{
	/* Start the command */
	usb3_wr32(&ep_reg->depcmd,
		 USB3_EPCMD_SET_STALL | USB3_EPCMD_ACT_BIT);

	/* Wait for command completion */
	handshake(pcd->usb3_dev, &ep_reg->depcmd, USB3_EPCMD_ACT_BIT, 0);
}

uint32_t handshake(usb3_device_t *dev, volatile uint32_t *ptr,
		      uint32_t mask, uint32_t done)
{
	uint32_t usec = 1000;
	uint32_t result;

	do {
		result = usb3_rd32(ptr);
		if ((result & mask) == done) {
			return 1;
		}

		udelay_100us(1);
		usec -= 1;
	} while (usec > 0);

	return 0;
}

void usb3_fill_desc(usb3_dma_desc_t *desc, phys_addr_t dma_addr,
			uint32_t dma_len, uint32_t stream, uint32_t type,
			uint32_t ctrlbits, int own)
{
	dma_addr = map_to_dma_addr(dma_addr);

	desc->bptl = (phys_addr_t)(dma_addr & 0xffffffffU);
	desc->bpth = 0;
	desc->status &= ~USB3_DSCSTS_XFRCNT_BITS;
	desc->status |= ((dma_len << USB3_DSCSTS_XFRCNT_SHIFT)&USB3_DSCSTS_XFRCNT_BITS);
	/* Note: If type is 0, leave original control bits intact (for isoc) */
	if (type)
		desc->control = type << USB3_DSCCTL_TRBCTL_SHIFT;

	desc->control |= (stream << USB3_DSCCTL_STRMID_SOFN_SHIFT) | ctrlbits;

	/* Must do this last! */
	if (own)
		desc->control |= USB3_DSCCTL_HWO_BIT;
    flush_dcache_all();
}


void usb3_dep_startnewcfg(usb3_pcd_t *pcd,
			     usb3_dev_ep_regs_t *ep_reg,
			     uint32_t rsrcidx)
{
	/* Start the command */
	usb3_wr32(&ep_reg->depcmd,
		 (rsrcidx << USB3_EPCMD_XFER_RSRC_IDX_SHIFT) |
		 USB3_EPCMD_START_NEW_CFG | USB3_EPCMD_ACT_BIT);

	/* Wait for command completion */
	handshake(pcd->usb3_dev, &ep_reg->depcmd, USB3_EPCMD_ACT_BIT, 0);
}

void usb3_dep_cfg(usb3_pcd_t *pcd,
		     usb3_dev_ep_regs_t *ep_reg,
		     uint32_t depcfg0, uint32_t depcfg1, uint32_t depcfg2)
{
	/* Set param 2 */
	usb3_wr32(&ep_reg->depcmdpar2, depcfg2);

	/* Set param 1 */
	usb3_wr32(&ep_reg->depcmdpar1, depcfg1);

	/* Set param 0 */
	usb3_wr32(&ep_reg->depcmdpar0, depcfg0); /* himm 0x1018c808 0x200 */

	/* Start the command */
	usb3_wr32(&ep_reg->depcmd,
		 USB3_EPCMD_SET_EP_CFG | USB3_EPCMD_ACT_BIT);

	/* Wait for command completion */
	handshake(pcd->usb3_dev, &ep_reg->depcmd, USB3_EPCMD_ACT_BIT, 0);
}

void usb3_dep_xfercfg(usb3_pcd_t *pcd,
			 usb3_dev_ep_regs_t *ep_reg,
			 uint32_t depstrmcfg)
{
	/* Set param 0 */
	usb3_wr32(&ep_reg->depcmdpar0, depstrmcfg);

	/* Start the command */
	usb3_wr32(&ep_reg->depcmd,
		 USB3_EPCMD_SET_XFER_CFG | USB3_EPCMD_ACT_BIT);

	/* Wait for command completion */
	handshake(pcd->usb3_dev, &ep_reg->depcmd, USB3_EPCMD_ACT_BIT, 0);
}

uint8_t usb3_dep_startxfer(usb3_pcd_t *pcd,
			   usb3_dev_ep_regs_t *ep_reg,
			   phys_addr_t dma_addr, uint32_t stream_or_uf)
{
	uint32_t depcmd;

	dma_addr = map_to_dma_addr(dma_addr);

	/* Set param 1 */
	usb3_wr32(&ep_reg->depcmdpar1, dma_addr & 0xffffffffU);

	/* Set param 0 */
	usb3_wr32(&ep_reg->depcmdpar0, 0);

	usb3_wr32(&ep_reg->depcmd,
		 (stream_or_uf << USB3_EPCMD_STR_NUM_OR_UF_SHIFT) |
		 USB3_EPCMD_START_XFER | USB3_EPCMD_ACT_BIT);

	/* Wait for command completion */
	handshake(pcd->usb3_dev, &ep_reg->depcmd, USB3_EPCMD_ACT_BIT, 0);

	depcmd = usb3_rd32(&ep_reg->depcmd);

	return (depcmd >> USB3_EPCMD_XFER_RSRC_IDX_SHIFT) &
	       (USB3_EPCMD_XFER_RSRC_IDX_BITS >> USB3_EPCMD_XFER_RSRC_IDX_SHIFT);
}

void usb3_dep_updatexfer(usb3_pcd_t *pcd,
			    usb3_dev_ep_regs_t *ep_reg,
			    uint32_t tri)
{
	/* Start the command */
	usb3_wr32(&ep_reg->depcmd,
		 (tri << USB3_EPCMD_XFER_RSRC_IDX_SHIFT) |
		 USB3_EPCMD_UPDATE_XFER | USB3_EPCMD_ACT_BIT);

	/* Wait for command completion */
	handshake(pcd->usb3_dev, &ep_reg->depcmd, USB3_EPCMD_ACT_BIT, 0);
}

void usb3_enable_ep(usb3_pcd_t *pcd, usb3_pcd_ep_t *ep)
{
	uint32_t ep_index_num, dalepena;

	ep_index_num = ep->num * 2;
	if (ep->is_in)
		ep_index_num += 1;

	dalepena = usb3_rd32(&pcd->dev_global_regs->dalepena);

	/* If we have already enabled this EP, leave it alone
	 * (shouldn't happen)
	 */
	if (dalepena & (1 << ep_index_num))
		return;

	dalepena |= 1 << ep_index_num;
	usb3_wr32(&pcd->dev_global_regs->dalepena, dalepena);
	return;
}

void usb3_dis_usb2_suspend(usb3_pcd_t *pcd)
{
	uint32_t usb2phycfg;

	if (pcd->speed == USB_SPEED_SUPER)
		return;

	usb2phycfg = usb3_rd32(&pcd->usb3_dev->core_global_regs->gusb2phycfg[0]);
	usb2phycfg &= ~USB3_USB2PHYCFG_SUS_PHY_BIT;
	usb2phycfg &= ~USB3_USB2PHYCFG_ENBL_SLP_M_BIT;
	usb3_wr32(&pcd->usb3_dev->core_global_regs->gusb2phycfg[0], usb2phycfg);
}

void usb3_ep0_activate(usb3_pcd_t *pcd)
{
	uint32_t diepcfg0, doepcfg0, diepcfg1, doepcfg1;
	uint32_t diepcfg2 = 0, doepcfg2 = 0;
	usb3_dev_ep_regs_t *ep_reg;

	diepcfg0 = USB3_EP_TYPE_CONTROL << USB3_EPCFG0_EPTYPE_SHIFT;
	diepcfg1 = USB3_EPCFG1_XFER_CMPL_BIT | USB3_EPCFG1_XFER_IN_PROG_BIT | USB3_EPCFG1_XFER_NRDY_BIT | USB3_EPCFG1_EP_DIR_BIT;

	doepcfg0 = USB3_EP_TYPE_CONTROL << USB3_EPCFG0_EPTYPE_SHIFT;
	doepcfg1 = USB3_EPCFG1_XFER_CMPL_BIT | USB3_EPCFG1_XFER_IN_PROG_BIT | USB3_EPCFG1_XFER_NRDY_BIT;

	/* Default to MPS of 512 (will reconfigure after ConnectDone event) */
	diepcfg0 |= 512 << USB3_EPCFG0_MPS_SHIFT;
	doepcfg0 |= 512 << USB3_EPCFG0_MPS_SHIFT;

	diepcfg0 |= pcd->ep0.tx_fifo_num << USB3_EPCFG0_TXFNUM_SHIFT;

	/* Issue "DEPCFG" command to EP0-OUT */

	ep_reg = &pcd->out_ep_regs[0];
	usb3_dis_usb2_suspend(pcd); /* himm 0x1018c200 0x102400 */
	/* If core is version 1.09a or later */
	/* Must issue DEPSTRTNEWCFG command first */
	usb3_dep_startnewcfg(pcd, ep_reg, 0);

	usb3_dep_cfg(pcd, ep_reg, doepcfg0, doepcfg1, doepcfg2);

	/* Issue "DEPSTRMCFG" command to EP0-OUT */

	/* One stream */
	usb3_dep_xfercfg(pcd, ep_reg, 1);

	/* Issue "DEPCFG" command to EP0-IN */

	ep_reg = &pcd->in_ep_regs[0];
	usb3_dep_cfg(pcd, ep_reg, diepcfg0, diepcfg1, diepcfg2);

	/* Issue "DEPSTRMCFG" command to EP0-IN */

	/* One stream */
	usb3_dep_xfercfg(pcd, ep_reg, 1);

	pcd->ep0.active = 1;
}

void usb3_ep_activate(usb3_pcd_t *pcd, usb3_pcd_ep_t *ep)
{
	usb3_dev_ep_regs_t *ep_reg, *ep0_reg;
	uint32_t depcfg0, depcfg1, depcfg2 = 0;

	/*
	 * Get the appropriate EP registers
	 */
	if (ep->is_in)
		ep_reg = ep->in_ep_reg;
	else
		ep_reg = ep->out_ep_reg;

	/* If this is first EP enable (ie. start of a new configuration) */
	if (!pcd->eps_enabled) {
		pcd->eps_enabled = 1;

		/* NOTE: When setting a new configuration, we must issue a
		 * "DEPCFG" command to physical EP1 (logical EP0-IN) first.
		 * This resets the core's Tx FIFO mapping table
		 */
		depcfg0 = USB3_EP_TYPE_CONTROL << USB3_EPCFG0_EPTYPE_SHIFT;
		depcfg0 |= USB3_CFG_ACTION_MODIFY << USB3_EPCFG0_CFG_ACTION_SHIFT;
		depcfg1 = USB3_EPCFG1_XFER_CMPL_BIT | USB3_EPCFG1_XFER_NRDY_BIT
			| USB3_EPCFG1_EP_DIR_BIT;

		switch (pcd->speed) {
		case USB_SPEED_SUPER:
			depcfg0 |= 512 << USB3_EPCFG0_MPS_SHIFT;
			break;

		case USB_SPEED_HIGH:
		case USB_SPEED_FULL:
			depcfg0 |= 64 << USB3_EPCFG0_MPS_SHIFT;
			break;

		case USB_SPEED_LOW:
			depcfg0 |= 8 << USB3_EPCFG0_MPS_SHIFT;
			break;
		}

		ep0_reg = &pcd->in_ep_regs[0];
		usb3_dep_cfg(pcd, ep0_reg, depcfg0, depcfg1, 0);

		/* If core is version 1.09a or later */
		/* Must issue DEPSTRTNEWCFG command first */
		ep0_reg = &pcd->out_ep_regs[0];
		usb3_dep_startnewcfg(pcd, ep0_reg, 2);
	}

	/*
	 * Issue "DEPCFG" command to EP
	 */
	depcfg0 = ep->type << USB3_EPCFG0_EPTYPE_SHIFT;
	depcfg0 |= ep->maxpacket << USB3_EPCFG0_MPS_SHIFT;

	if (ep->is_in) {
		depcfg0 |= ep->tx_fifo_num << USB3_EPCFG0_TXFNUM_SHIFT;
	}

	depcfg0 |= ep->maxburst << USB3_EPCFG0_BRSTSIZ_SHIFT;

	depcfg1 = ep->num << USB3_EPCFG1_EP_NUM_SHIFT;

	if (ep->is_in)
		depcfg1 |= USB3_EPCFG1_EP_DIR_BIT;

	depcfg1 |= USB3_EPCFG1_XFER_CMPL_BIT;

	usb3_dep_cfg(pcd, ep_reg, depcfg0, depcfg1, depcfg2);

	/*
	 * Issue "DEPSTRMCFG" command to EP
	 */
	/* Setting 1 stream resource */
	usb3_dep_xfercfg(pcd, ep_reg, 1);

	/* Enable EP in DALEPENA reg */
	usb3_enable_ep(pcd, ep);

	ep->active = 1;
}

void usb3_ep0_out_start(usb3_pcd_t *pcd)
{
	usb3_dev_ep_regs_t *ep_reg;
	usb3_dma_desc_t *desc;
	uint32_t desc_dma;
	uint8_t tri;

	/* Get the SETUP packet DMA Descriptor (TRB) */
	desc = pcd->ep0_setup_desc;
	desc_dma = (phys_addr_t)pcd->ep0_setup_desc;

	/* DMA Descriptor setup */
	usb3_fill_desc(desc, (phys_addr_t)pcd->ep0_setup_pkt,
			   pcd->ep0.maxpacket,
			   0, USB3_DSCCTL_TRBCTL_SETUP, USB3_DSCCTL_IOC_BIT |
			   USB3_DSCCTL_ISP_BIT | USB3_DSCCTL_LST_BIT, 1);

	ep_reg = &pcd->out_ep_regs[0];

	/* Issue "DEPSTRTXFER" command to EP0-OUT */
	tri = usb3_dep_startxfer(pcd, ep_reg, desc_dma, 0);
	pcd->ep0.tri_out = tri;
}

void usb3_core_dev_init(usb3_device_t *dev)
{
	usb3_core_global_regs_t *global_regs = dev->core_global_regs;
	usb3_pcd_t *pcd = &dev->pcd;
	usb3_dev_global_regs_t *dev_global_regs = pcd->dev_global_regs;
	uint32_t temp_t;

	/* Soft-reset the core */
	do {
		temp_t = usb3_rd32(&dev_global_regs->dctl);
		temp_t &= ~USB3_DCTL_RUN_STOP_BIT;
		temp_t |= USB3_DCTL_CSFT_RST_BIT;
		usb3_wr32(&dev_global_regs->dctl, temp_t);
		do {
			udelay_100us(1);
			temp_t = usb3_rd32(&dev_global_regs->dctl);
		} while(temp_t & USB3_DCTL_CSFT_RST_BIT);

		/* Wait for at least 3 PHY clocks */
		msleep(1);
	} while(0);

	pcd->link_state = 0;

	/* Set Turnaround Time = 9 (8-bit UTMI+ / ULPI) */
	temp_t = usb3_rd32(&global_regs->gusb2phycfg[0]);
	temp_t &= ~USB3_USB2PHYCFG_USB_TRD_TIM_BITS;
	temp_t |= 9 << USB3_USB2PHYCFG_USB_TRD_TIM_SHIFT;
	usb3_wr32(&global_regs->gusb2phycfg[0], temp_t);

	temp_t = 0x13802004;
	usb3_wr32(&global_regs->gctl, temp_t);

	usb_info("evnt buffer addr: 0x%x\n", dev->event_buf);

	usb3_init_eventbuf(dev, USB3_EVENT_BUF_SIZE, (phys_addr_t)dev->event_buf);
	dev->event_ptr = dev->event_buf;

	/* Set speed to Super */
	temp_t = usb3_rd32(&pcd->dev_global_regs->dcfg);
	temp_t &= ~(USB3_DCFG_DEVSPD_BITS << USB3_DCFG_DEVSPD_SHIFT);
    temp_t |= USB3_SPEED_HS_PHY_30MHZ_OR_60MHZ
				<< USB3_DCFG_DEVSPD_SHIFT;
	usb3_wr32(&pcd->dev_global_regs->dcfg, temp_t);

	/* If LPM enable was requested */
	temp_t = usb3_rd32(&pcd->dev_global_regs->dcfg);
	temp_t |= USB3_DCFG_LPM_CAP_BIT;
	usb3_wr32(&pcd->dev_global_regs->dcfg, temp_t);/*himm 0x1018c700 0x480804*/

	/* Set Nump */
	temp_t = usb3_rd32(&pcd->dev_global_regs->dcfg);
	temp_t &= ~USB3_DCFG_NUM_RCV_BUF_BITS;
	temp_t |= 16 << USB3_DCFG_NUM_RCV_BUF_SHIFT;
	usb3_wr32(&pcd->dev_global_regs->dcfg, temp_t);

	usb3_set_address(pcd, 0);

	/* disable Phy suspend */
	usb3_resume_usb3_phy(pcd);
	usb3_resume_usb2_phy(pcd);/*himm 0x1018c200 0x102540*/
	/* Enable Global and Device interrupts */
	usb3_enable_device_interrupts(dev);

	/* Activate EP0 */
	usb3_ep0_activate(pcd);

	/* Start EP0 to receive SETUP packets */
	usb3_ep0_out_start(pcd);

	/* Enable EP0-OUT/IN in DALEPENA register */
	usb3_wr32(&pcd->dev_global_regs->dalepena, 3);

	/* Set Run/Stop bit */
	temp_t = usb3_rd32(&pcd->dev_global_regs->dctl);
	temp_t |= USB3_DCTL_RUN_STOP_BIT;
	usb3_wr32(&pcd->dev_global_regs->dctl, temp_t);
}

void usb3_pcd_init(usb3_device_t *dev)
{
	usb3_pcd_t *pcd = &dev->pcd;

	pcd->usb3_dev = dev;
	pcd->speed = USB_SPEED_UNKNOWN;

	/* Initialize EP structures */
	pcd_epinit(pcd);

	/* Initialize the Core (also enables interrupts and sets Run/Stop bit) */
	usb3_core_dev_init(dev);
}

void usb3_common_init(usb3_device_t *dev, volatile uint8_t *base)
{
	usb3_pcd_t *pcd;

	dev->core_global_regs = (usb3_core_global_regs_t *)(base + USB3_CORE_GLOBAL_REG_OFFSET);

	pcd = &dev->pcd;

	pcd->dev_global_regs = (usb3_dev_global_regs_t *)(base + USB3_DEV_GLOBAL_REG_OFFSET);
	pcd->out_ep_regs = (usb3_dev_ep_regs_t *)(base + USB3_DEV_OUT_EP_REG_OFFSET);
	pcd->in_ep_regs = (usb3_dev_ep_regs_t *)(base + USB3_DEV_IN_EP_REG_OFFSET);
}

void usb3_init(usb3_device_t *dev)
{
	/* Init the PCD (also enables interrupts and sets Run/Stop bit) */
	usb3_pcd_init(dev);
}

static uint8_t string_manu[]= {'H',0,'i',0,'s',0,'l',0,'i',0,'c',0,'o',0,'n',0};
static uint8_t string_prod[]= {'H',0,'i',0,'U',0,'S',0,'B',0,'B',0,'u',0,'r',0,'n',0};
int usb3_driver_init(void)
{
	usb3_device_t *usb3_dev;
	struct usb_device_descriptor *usb3_dev_desc;

	usb3_dev = malloc(sizeof(usb3_device_t));
	if (!usb3_dev) {
		debug("usb3_dev: out of memory\n");
		return -ENOMEM;
	}
	usb3_memset((void *)usb3_dev, 0, sizeof(usb3_device_t));
	usb3_dev_desc = malloc(sizeof(struct usb_device_descriptor));
	usb3_pcd_t *pcd = &usb3_dev->pcd;
	usb3_pcd_ep_t *ep = &pcd->in_ep;
	usb3_pcd_req_t *req = &ep->req;
	req->bufdma = (uint8_t *)malloc(512);
	usb_info("size of usb3_dev %d\n", sizeof(*usb3_dev));
	usb3_dev->base = (volatile uint8_t *)USB3_CTRL_REG_BASE;
	usb3_dev->string_manu_len = sizeof(string_manu);
	usb3_dev->string_prod_len = sizeof(string_prod);
	usb3_dev->dev_desc = usb3_dev_desc;
	memcpy(usb3_dev->string_manu, string_manu, usb3_dev->string_manu_len);
	memcpy(usb3_dev->string_prod, string_prod, usb3_dev->string_prod_len);
	usb3_dev->pcd.ep0_setup_desc = (usb3_dma_desc_t *)
				((phys_addr_t)(usb3_dev->pcd.ep0_setup + 15) & (uint32_t)(~15));
	usb3_dev->pcd.ep0_in_desc = (usb3_dma_desc_t *)
				((phys_addr_t)(usb3_dev->pcd.ep0_in + 15) & (uint32_t)(~15));
	usb3_dev->pcd.ep0_out_desc = (usb3_dma_desc_t *)
				((phys_addr_t)(usb3_dev->pcd.ep0_out + 15) & (uint32_t)(~15));
	usb3_dev->pcd.in_ep.ep_desc = (usb3_dma_desc_t *)
				((phys_addr_t)(usb3_dev->pcd.in_ep.epx_desc + 15) & (uint32_t)(~15));
	usb3_dev->pcd.out_ep.ep_desc = (usb3_dma_desc_t *)
				((phys_addr_t)(usb3_dev->pcd.out_ep.epx_desc + 15) & (uint32_t)(~15));

	/* Release usb3.0 controller */

	phy_hiusb_init(0);

	/* Get usb3.0 version number */
	usb3_dev->snpsid = usb3_rd32((volatile uint32_t *)
		(usb3_dev->base + USB3_CORE_REG_BASE + USB3_CORE_GSNPSID_REG_OFFSET));

	/* Initialize usb3.0 core */
	usb3_common_init(usb3_dev, usb3_dev->base + USB3_CORE_REG_BASE);

	/* Initialize usb3.0 pcd */
	usb3_init(usb3_dev);

	usb_info("usb init done\n");
	for (;;)
		usb3_handle_event(usb3_dev);

}

/*
 * Interface func for download the mirror, address from return.
 */
void udc_connect(void)
{
	dcache_disable();
	usb3_driver_init();
	dcache_enable();
}
EXPORT_SYMBOL(udc_connect);
