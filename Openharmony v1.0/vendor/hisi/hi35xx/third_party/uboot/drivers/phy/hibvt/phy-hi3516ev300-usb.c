/*
 *
 * phy-hi3516ev300-usb.c
 *
 * usb phy driver special for hi3516ev300
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
#include <asm/arch-hi3516ev300/platform.h>
#include <dm.h>
#include <usb.h>
#include <usb/xhci.h>
#include "phy-hisi-usb.h"

/* offset 0x140 */
#define USB2_CTRL				0x140
#define USB2_CRG_DEFAULT_VAL	0x3b2f
#define USB2_UTMI_CKEN			(0x1 << 12)
#define USB2_PHY_APB_CKEN		(0x1 << 11)
#define USB2_REF_CKEN			(0x1 << 9)
#define USB2_BUS_CKEN			(0x1 << 8)
#define USB2_PHY_PLL_CKEN		(0x1 << 4)
#define USB2_PHY_XTAL_CKEN		(0x1 << 2)
#define USB2_FREECLK_CKSEL		(0x1 << 13)
#define USB2_PHY_APB_RST		(0x1 << 10)
#define USB2_VCC_SRST_REQ		(0x1 << 3)
#define USB2_PHY_REQ			(0x1 << 0)
#define USB2_PHY_PORT_TREQ		(0x1 << 1)


#define GTXTHRCFG				0xc108
#define GRXTHRCFG				0xc10c
#define REG_GCTL				0xc110
#define REG_GUSB3PIPECTL0		0xc2c0
#define PCS_SSP_SOFT_RESET		(0x1 << 31)

#define PORT_CAP_DIR			(0x3 << 12)
#define PORT_SET_HOST			(0x1 << 12)
#define PORT_DISABLE_SUSPEND	(0x1 << 17)


#define	USB2_G_TXTHRCFG			0x23100000
#define	USB2_G_RXTHRCFG			0x23100000

/* PHY base register */
#define USB2_PHY_BASE_REG		0x100D0000
#define RG_PLL_EN_MASK			0x0003
#define RG_PLL_EN_VAL			0x0003
#define PHY_PLL_OFFSET			0x0014

#define USB_VBUS_IO_CONFIG_REG	0x100c007C
#define USB_VBUS_IO_CONFIG_VAL	0x0431

#define USB_PWREN_CONFIG_REG	0x100c0080
#define USB_PWREN_CONFIG_VAL	0x1

/* PHY eye config */
#define HIXVP_PHY_ANA_CFG_0_OFFSET			0x00
#define HIXVP_PHY_PRE_DRIVE_MASK			(0xf << 24)
#define HIXVP_PHY_PRE_DRIVE_VAL				(0x4 << 24)
#define HIXVP_PHY_ANA_CFG_2_OFFSET			0x08
#define HIXVP_PHY_TX_TEST_BIT				(0x1 << 20)
#define HIXVP_PHY_DISCONNECT_REFERENCE_MASK	(0x7 << 16)
#define HIXVP_PHY_DISCONNECT_REFERENCE_VAL	(0x2 << 16)
#define HIXVP_PHY_ANA_CFG_4_OFFSET			0x10
#define HIXVP_PHY_TX_REFERENCE_MASK			(0x7 << 4)
#define HIXVP_PHY_TX_REFERENCE_VAL			(0x5 << 4)
#define HIXVP_PHY_SQUELCH_REFERENCE_MASK	(0x7 << 0)
#define HIXVP_PHY_SQUELCH_REFERENCE_VAL		(0x5 << 0)

/* PHY trim config */
#define USB_TRIM_BASE_REG					0x12028004
#define USB_TRIM_VAL_MASK					0x001F
#define USB_TRIM_VAL_MIN					0x0009
#define USB_TRIM_VAL_MAX					0x001D
#define USB2_TRIM_OFFSET					0x0008
#define USB2_TRIM_MASK						0x1f00
#define usb2_trim_val(a)					(((a) << 8) & USB2_TRIM_MASK)
#define USB2_TRIM_DEFAULT_VAL				0x000e

/* PHY svb config */
#define USB_SVB_BASE_REG					0x12020158
#define USB_SVB_OFFSET						0x00
#define USB_SVB_MASK						(0x0f << 24)
#define USB_SVB_PREDEV_5_MIN				0x2bc
#define USB_SVB_PREDEV_5_MAX_4_MIN			0x32a
#define USB_SVB_PREDEV_4_MAX_3_MIN			0x398
#define USB_SVB_PREDEV_3_MAX_2_MIN			0x3ca
#define USB_SVB_PREDEV_2_MAX				0x44c
#define USB_SVB_PREDEV_5_PHY_VAL			(0x05 << 24)
#define USB_SVB_PREDEV_4_PHY_VAL			(0x04 << 24)
#define USB_SVB_PREDEV_3_PHY_VAL			(0x03 << 24)
#define USB_SVB_PREDEV_2_PHY_VAL			(0x02 << 24)
static uintptr_t xhci_base = 0;

int xhci_hcd_init(int index, struct xhci_hccr **hccr, struct xhci_hcor **hcor)
{
	if ((hccr == NULL) || (hcor == NULL))
		return -EINVAL;

	xhci_base = USB3_CTRL_REG_BASE;

	*hccr = (struct xhci_hccr *)(xhci_base);
	*hcor = (struct xhci_hcor *)((uintptr_t) *hccr +
				HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

void usb2_eye_config(void)
{
	unsigned int reg;
	/* HSTX pre-drive strength */
	reg = readl(USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_0_OFFSET);
	reg &= ~HIXVP_PHY_PRE_DRIVE_MASK;
	reg |= HIXVP_PHY_PRE_DRIVE_VAL;
	writel(reg, USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_0_OFFSET);

	/* TX test bit */
	reg = readl(USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_2_OFFSET);
	reg |= HIXVP_PHY_TX_TEST_BIT;
	writel(reg, USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_2_OFFSET);

	/* Disconnect reference voltage sel */
	reg = readl(USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_2_OFFSET);
	reg &= ~HIXVP_PHY_DISCONNECT_REFERENCE_MASK;
	reg |= HIXVP_PHY_DISCONNECT_REFERENCE_VAL;
	writel(reg, USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_2_OFFSET);

	/* TX reference voltage sel */
	reg = readl(USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_4_OFFSET);
	reg &= ~HIXVP_PHY_TX_REFERENCE_MASK;
	reg |= HIXVP_PHY_TX_REFERENCE_VAL;
	writel(reg, USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_4_OFFSET);

	/* Squlech reference voltage sel */
	reg = readl(USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_4_OFFSET);
	reg &= ~HIXVP_PHY_SQUELCH_REFERENCE_MASK;
	reg |= HIXVP_PHY_SQUELCH_REFERENCE_VAL;
	writel(reg, USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_4_OFFSET);
}

void usb2_trim_config(void)
{
	unsigned int ret;
	unsigned int reg;
	unsigned int trim_val;

	ret = readl(USB_TRIM_BASE_REG);
	trim_val = (ret & USB_TRIM_VAL_MASK); /* get usb trim value */
	reg = readl(USB2_PHY_BASE_REG + USB2_TRIM_OFFSET);
	reg &= ~USB2_TRIM_MASK;
	/* set trim value to HiXVPV100 phy */
	if ((trim_val >= USB_TRIM_VAL_MIN) && (trim_val <= USB_TRIM_VAL_MAX))
		reg |= usb2_trim_val(trim_val);
	else
		reg |= usb2_trim_val(USB2_TRIM_DEFAULT_VAL);

	writel(reg, USB2_PHY_BASE_REG + USB2_TRIM_OFFSET);
}

void usb2_svb_config(void)
{
	unsigned int ret;
	unsigned int reg;

	ret = readl(USB_SVB_BASE_REG);
	reg = readl(USB2_PHY_BASE_REG + USB_SVB_OFFSET);
	reg &= ~USB_SVB_MASK;
	/* set svb value to HiXVPV100 phy */
	if ((ret >= USB_SVB_PREDEV_5_MIN) && (ret < USB_SVB_PREDEV_5_MAX_4_MIN))
		reg |= USB_SVB_PREDEV_5_PHY_VAL;
	else if ((ret >= USB_SVB_PREDEV_5_MAX_4_MIN) && (ret < USB_SVB_PREDEV_4_MAX_3_MIN))
		reg |= USB_SVB_PREDEV_4_PHY_VAL;
	else if ((ret >= USB_SVB_PREDEV_4_MAX_3_MIN) && (ret <= USB_SVB_PREDEV_3_MAX_2_MIN))
		reg |= USB_SVB_PREDEV_3_PHY_VAL;
	else if ((ret > USB_SVB_PREDEV_3_MAX_2_MIN) && (ret <= USB_SVB_PREDEV_2_MAX))
		reg |= USB_SVB_PREDEV_2_PHY_VAL;
	else
		reg |= USB_SVB_PREDEV_4_PHY_VAL;

	writel(reg, USB2_PHY_BASE_REG + USB_SVB_OFFSET);
}
void phy_hiusb_init_crg_clk(int index)
{
	unsigned int reg;
	/* set usb2 CRG default val */
	reg = USB2_CRG_DEFAULT_VAL;
	writel(reg, CRG_REG_BASE + USB2_CTRL);
	udelay(U_LEVEL6);

	/* open UTMI clk */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg |= USB2_UTMI_CKEN;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	/* open phy apb clk */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg |= USB2_PHY_APB_CKEN;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	/* open ctrl ref clk */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg |= USB2_REF_CKEN;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	/* open bus clk */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg |= USB2_BUS_CKEN;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	/* open phy pll clk */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg |= USB2_PHY_PLL_CKEN;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	/* open phy xtal clk */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg |= USB2_PHY_XTAL_CKEN;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	/* freeclk_cksel_free */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg |= USB2_FREECLK_CKSEL;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	udelay(U_LEVEL5);
}

void phy_hiusb_init(int index)
{
	unsigned int reg;

	/* VBUS config */
	reg = USB_VBUS_IO_CONFIG_VAL;
	writel(reg, USB_VBUS_IO_CONFIG_REG);

	reg = USB_PWREN_CONFIG_VAL;
	writel(reg, USB_PWREN_CONFIG_REG);

	/* init crg and clk */
	phy_hiusb_init_crg_clk(index);

	/* release phy apb */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg &= ~USB2_PHY_APB_RST;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	udelay(U_LEVEL5);

	/* por noreset */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg &= ~USB2_PHY_REQ;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	reg = readl(USB2_PHY_BASE_REG + PHY_PLL_OFFSET);
	reg &= ~RG_PLL_EN_MASK;
	reg |= RG_PLL_EN_VAL;
	writel(reg, USB2_PHY_BASE_REG + PHY_PLL_OFFSET);

	udelay(U_LEVEL10);

	/* cancel TPOR */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg &= ~USB2_PHY_PORT_TREQ;
	writel(reg, CRG_REG_BASE + USB2_CTRL);
	udelay(U_LEVEL6);

	/* vcc reset */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg &= ~USB2_VCC_SRST_REQ;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	/* USB2 Controller configs */
	reg = readl(USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	reg |= PCS_SSP_SOFT_RESET;
	writel(reg, USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	udelay(U_LEVEL2);

	reg = readl(USB3_CTRL_REG_BASE + REG_GCTL);
	reg &= ~PORT_CAP_DIR;
	reg |= PORT_SET_HOST; /* [13:12] 01: Host; 10: Device; 11: OTG */
	writel(reg, USB3_CTRL_REG_BASE + REG_GCTL);
	udelay(U_LEVEL2);

	reg = readl(USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	reg &= ~PCS_SSP_SOFT_RESET;
	reg &= ~PORT_DISABLE_SUSPEND; /* disable suspend */
	writel(reg, USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	udelay(U_LEVEL2);

	writel(USB2_G_TXTHRCFG, USB3_CTRL_REG_BASE + GTXTHRCFG);
	writel(USB2_G_RXTHRCFG, USB3_CTRL_REG_BASE + GRXTHRCFG);
	udelay(U_LEVEL2);

	/* USB2 eye config */
	usb2_eye_config();

	/* USB2 trim config */
	usb2_trim_config();

	/* USB2 svb config */
	usb2_svb_config();
}
EXPORT_SYMBOL(phy_hiusb_init);

void xhci_hcd_stop(int index)
{
	unsigned int reg;

	/* por noreset */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg |= USB2_PHY_REQ;
	writel(reg, CRG_REG_BASE + USB2_CTRL);

	udelay(U_LEVEL10);

	/* cancel TPOR */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg |= USB2_PHY_PORT_TREQ;
	writel(reg, CRG_REG_BASE + USB2_CTRL);
	udelay(U_LEVEL6);

	/* vcc reset */
	reg = readl(CRG_REG_BASE + USB2_CTRL);
	reg |= USB2_VCC_SRST_REQ;
	writel(reg, CRG_REG_BASE + USB2_CTRL);
}
EXPORT_SYMBOL(xhci_hcd_stop);

