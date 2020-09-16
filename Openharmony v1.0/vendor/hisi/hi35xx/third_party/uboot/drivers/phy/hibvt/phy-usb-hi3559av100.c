/*
 *
 * phy-hi3559av100-usb.c
 *
 * usb phy driver special for hi3559av100
 *
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <asm/arch-hi3559av100/platform.h>
#include <dm.h>
#include <usb.h>
#include <usb/xhci.h>
#include "phy-hisi-usb.h"

#define SYS_STAT			0x8c
#define COMBPHY_MODE_MASK	(0x3 << 0)
#define PCIE_X2				(0x0 << 0)
#define PCIE_X1				(0x1 << 0)
#define USB3				(0x2 << 0)

#define USB_PORT0			0x38
#define P0_U3_PORT_DISABLE	(0x1 << 3)
#define USB_PORT1			0x3c
#define P1_U3_PORT_DISABLE	(0x1 << 3)

#define USB2_PHY_MASK			(0xf << 4)
#define PORT_CAP_DIR			(0x3 << 12)
#define PORT_SET_HOST			(0x1 << 12)
#define PORT_DISABLE_SUSPEND	(0x1 << 17)

#define XHCI_USB3OFFSET			16
#define COMBPHY_MODE_REG_OFFSET	12
static uintptr_t xhci_base = 0;

int xhci_hcd_init(int index, struct xhci_hccr **hccr, struct xhci_hcor **hcor)
{
	if ((hccr == NULL) || (hcor == NULL))
		return -EINVAL;

	if (index == 0)
		xhci_base = USB3_CTRL_REG_BASE;
	if (index == 1)
		xhci_base = USB3_CTRL_REG_BASE_1;

	*hccr = (struct xhci_hccr *)(xhci_base);
	*hcor = (struct xhci_hcor *)((uintptr_t) *hccr +
				HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

void usb3_eye_config(void)
{
	int reg;

	/* Port0 usb2 phy0 misc ctrl */
	reg = readl(MISC_REG_BASE + USB2_PHY0_CTRL);
	reg &= ~USB2_PHY_MASK;
	reg |= USB2_PHY_VREF; /* [7:4] -> (eye vref = 4%) */
	reg |= USB2_PHY_PRE; /* [13:12] -> (pre electric = 3x) */
	writel(reg, MISC_REG_BASE + USB2_PHY0_CTRL);
	udelay(U_LEVEL4);

	/* Port1 usb2 phy1 misc ctrl */
	reg = readl(MISC_REG_BASE + USB2_PHY1_CTRL);
	reg &= ~USB2_PHY_MASK;
	reg |= USB2_PHY_VREF; /* [7:4] -> (eye vref = 4%) */
	reg |= USB2_PHY_PRE; /* [13:12] -> (pre electric = 3x) */
	writel(reg, MISC_REG_BASE + USB2_PHY1_CTRL);
	udelay(U_LEVEL4);

	/* Port0 TX swing comp => 0x1101 */
	writel(P0_TX_SWING_COMP_CFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P0_TX_SWING_COMP_RCFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P0_TX_SWING_COMP_VAL, MISC_REG_BASE + USB3_COMB_PHY);
	udelay(U_LEVEL4);

	/* Port0 termination trim => 0x0000 */
	writel(P0_TX_TERMINATION_TRIM_CFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P0_TX_TERMINATION_TRIM_RCFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P0_TX_TERMINATION_TRIM_VAL, MISC_REG_BASE + USB3_COMB_PHY);
	udelay(U_LEVEL4);

	/* Port1 TX swing comp => 0x1101 */
	writel(P1_TX_SWING_COMP_CFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P1_TX_SWING_COMP_RCFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P1_TX_SWING_COMP_VAL, MISC_REG_BASE + USB3_COMB_PHY);
	udelay(U_LEVEL4);

	/* Port1 termination trim => 0x0000 */
	writel(P1_TX_TERMINATION_TRIM_CFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P1_TX_TERMINATION_TRIM_RCFG, MISC_REG_BASE + USB3_COMB_PHY);
	writel(P1_TX_TERMINATION_TRIM_VAL, MISC_REG_BASE + USB3_COMB_PHY);
	udelay(U_LEVEL4);
}

void phy_hiusb_init_ctrler(unsigned long usb3_offset)
{
	unsigned int reg;
	/* config U3 Controller USB3_0 PHY OUTPUT */
	reg = readl(USB3_CTRL_CFG);
	reg &= ~(USB3_VCC_SRST_REQ << usb3_offset);
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL8);

	reg = readl(xhci_base + REG_GUSB3PIPECTL0);
	reg |= PCS_SSP_SOFT_RESET;
	writel(reg, xhci_base + REG_GUSB3PIPECTL0);
	udelay(U_LEVEL6);

	reg = readl(xhci_base + REG_GCTL);
	reg &= ~PORT_CAP_DIR;
	reg |= PORT_SET_HOST; /* [13:12] 01: Host; 10: Device; 11: OTG */
	writel(reg, xhci_base + REG_GCTL);
	udelay(U_LEVEL2);

	reg = readl(xhci_base + REG_GUSB3PIPECTL0);
	reg &= ~PCS_SSP_SOFT_RESET;
	reg &= ~PORT_DISABLE_SUSPEND; /* disable suspend */
	writel(reg, xhci_base + REG_GUSB3PIPECTL0);
	udelay(U_LEVEL2);

	reg &= CLEAN_USB3_GTXTHRCFG;
	reg |= USB_TXPKT_CNT_SEL;
	reg |= USB_TXPKT_CNT;
	reg |= USB_MAXTX_BURST_SIZE;
	writel(reg, xhci_base + GTXTHRCFG);
	udelay(U_LEVEL2);
	writel(reg, xhci_base + GRXTHRCFG);
	udelay(U_LEVEL2);
}

void phy_hiusb_init_clk_ctrler(unsigned long usb2_offset,
		  unsigned long usb3_offset, unsigned int cbp_mode)
{
	unsigned int reg;
	/* USB3 VCC reset */
	reg = readl(USB3_CTRL_CFG);
	reg |= (USB3_VCC_SRST_REQ << usb3_offset);
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL8);

	/* disable port0 ss */
	reg = readl(MISC_REG_BASE + USB_PORT0);
	reg |= P0_U3_PORT_DISABLE;
	writel(reg, MISC_REG_BASE + USB_PORT0);

	/* disable port1 ss */
	reg = readl(MISC_REG_BASE + USB_PORT1);
	reg |= P1_U3_PORT_DISABLE;
	writel(reg, MISC_REG_BASE + USB_PORT1);

	/* release TPOR default release */
	reg = readl(USB2_PHY_CFG);
	reg &= ~(USB2_PHY_PORT_TREQ << usb2_offset);
	writel(reg, USB2_PHY_CFG);
	udelay(U_LEVEL6);

	/* utmi clock sel */
	reg = readl(USB3_CTRL_CFG);
	reg &= ~(USB3_UTMI_CKSEL << usb3_offset);
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL6);

	/* open phy ref clk default open */
	reg = readl(USB2_PHY_CFG);
	reg |= (USB2_PHY_CKEN << usb2_offset);
	writel(reg, USB2_PHY_CFG);
	udelay(U_LEVEL6);

	/* U2 phy reset release */
	reg = readl(USB2_PHY_CFG);
	reg &= ~(USB2_PHY_REQ << usb2_offset);
	writel(reg, USB2_PHY_CFG);
	udelay(U_LEVEL6);

	/* Release the specific configuration of COMBPHY. */
	reg = readl(USB3_COMBPHY_CFG);
	if (cbp_mode == PCIE_X1)
		/* only release combphy1...port1 */
		reg &= ~(COMBPHY_SRST_REQ);
	else if (cbp_mode == USB3)
		reg &= ~(COMBPHY_SRST_REQ >> usb3_offset);

	writel(reg, USB3_COMBPHY_CFG);
	udelay(U_LEVEL5);

	phy_hiusb_init_ctrler(usb3_offset);
}

void phy_hiusb_init(int index)
{
	unsigned long flags, usb2_offset, usb3_offset;
	unsigned int reg, cbp_mode;

	local_irq_save(flags);

	if (index == 0) {
		xhci_base = USB3_CTRL_REG_BASE;
		usb2_offset = 1;
		usb3_offset = XHCI_USB3OFFSET;
	}
	if (index == 1) {
		xhci_base = USB3_CTRL_REG_BASE_1;
		usb2_offset = 0;
		usb3_offset = 0;
	}

	/* Get combphy mode */
	cbp_mode = readl(SYS_CTRL_REG_BASE + SYS_STAT);
	cbp_mode = cbp_mode >> COMBPHY_MODE_REG_OFFSET;
	cbp_mode &= COMBPHY_MODE_MASK;

	/*
	 * According to description of SYSSYAT register, different
	 * HW modes of COMBPHY require specific configurations.
	 */
	reg = readl(USB3_COMBPHY_CFG);
	switch (cbp_mode) {
	case PCIE_X2:
		reg = readl(USB3_CTRL_CFG);
		reg |= (USB3_0_PCLK_OCC_SEL | USB3_1_PCLK_OCC_SEL);
		writel(reg, USB3_CTRL_CFG);
		break;
	case PCIE_X1:
		/* Only reset combphy1...port1 */
		reg |= COMBPHY_SRST_REQ;
		reg |= COMBPHY_REF_CKEN;
		writel(reg, USB3_COMBPHY_CFG);
		udelay(U_LEVEL5);

		reg = readl(USB3_CTRL_CFG);
		reg |= USB3_0_PCLK_OCC_SEL;
		writel(reg, USB3_CTRL_CFG);
		break;
	case USB3:
		reg |= (COMBPHY_SRST_REQ >> usb3_offset);
		reg |= (COMBPHY_REF_CKEN >> usb3_offset);
		writel(reg, USB3_COMBPHY_CFG);
		break;
	default:
		break;
	}
	udelay(U_LEVEL5);

	phy_hiusb_init_clk_ctrler(usb2_offset, usb3_offset, cbp_mode);

	usb3_eye_config();

	local_irq_restore(flags);
}

void xhci_hcd_stop(int index)
{
	unsigned long usb3_offset;
	unsigned int reg, cbp_mode;

	if (index == 0)
		usb3_offset = XHCI_USB3OFFSET;

	if (index == 1)
		usb3_offset = 0;

	/* Get combphy mode */
	cbp_mode = readl(SYS_CTRL_REG_BASE + SYS_STAT);
	cbp_mode = cbp_mode >> COMBPHY_MODE_REG_OFFSET;
	cbp_mode &= COMBPHY_MODE_MASK;

	reg = readl(USB3_COMBPHY_CFG);
	if (cbp_mode == PCIE_X1)
        /* Only reset combphy1...port1 */
		reg |= COMBPHY_SRST_REQ;
	else if (cbp_mode == USB3)
		reg |= (COMBPHY_SRST_REQ >> usb3_offset);

	writel(reg, USB3_COMBPHY_CFG);
	udelay(U_LEVEL5);

	reg = readl(USB3_CTRL_CFG);
	reg |= (USB3_VCC_SRST_REQ << usb3_offset);
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL8);
}
