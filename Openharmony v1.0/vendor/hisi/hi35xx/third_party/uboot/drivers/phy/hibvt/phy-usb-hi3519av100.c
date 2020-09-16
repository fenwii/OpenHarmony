/*
 *
 * phy-hi3519av100-usb.c
 *
 * usb phy driver special for hi3519av100
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
#include <asm/arch-hi3519av100/platform.h>
#include <dm.h>
#include <usb.h>
#include <usb/xhci.h>
#include "phy-hisi-usb.h"

/* offset 0x184 */
#define USB2_PHY0_CKEN		(0x1 << 5)
#define USB2_PHY1_CKEN		(0x1 << 4)
#define USB2_PHY0_PORT_TREQ	(0x1 << 3)
#define USB2_PHY1_PORT_TREQ	(0x1 << 2)
#define USB2_PHY0_REQ		(0x1 << 1)
#define USB2_PHY1_REQ		(0x1 << 0)

/* offset 0x188 */
#define COMBPHY0_REF_CKEN	(0x1 << 8)
#define COMBPHY_SRST_REQ	(0x1 << 0)

/* offset 0x190 */
#define USB3_PCLK_OCC_SEL	(0x1 << 30)
#define USB3_UTMI_CKSEL		(0x1 << 29)
#define USB3_VCC_SRST_REQ	(0x1 << 16)
#define USB2_UTMI_CKSEL		(0x1 << 13)
#define USB2_VCC_SRST_REQ	(0x1 << 0)

#define USB_PORT0			0x38
#define U3_PORT_DISABLE		(0x1 << 3)

#define GTXTHRCFG			0xc108
#define GRXTHRCFG			0xc10c
#define REG_GCTL			0xc110

#define PORT_CAP_DIR		(0x3 << 12)
#define DEFAULT_HOST_MOD	(0x1 << 12)

#define PERI_USB3_GTXTHRCFG	0x2310000

#define REG_GUSB3PIPECTL0	0xc2c0
#define PCS_SSP_SOFT_RESET	(0x1 << 31)
#define SUSPEND_USB3_SS_PHY	(0x1 << 17)
#define USB3_TX_MARGIN		(0x7 << 3)
#define USB3_TX_MARGIN_VAL	(0x2 << 3)

#define USB2_PHY0				0x24
#define USB2_PHY0_TXVREFTUNE	(0xf << 4)
#define USB2_PHY0_VREF_VAL		(0x5 << 4)
#define USB2_PHY0_TXPRE			(0x3 << 12)
#define USB2_PHY0_PRE_VAL		(0x1 << 12)

#define USB2_PHY1				0x30
#define USB2_PHY1_TXVREFTUNE	(0xf << 4)
#define USB2_PHY1_VREF_VAL		(0x5 << 4)
#define USB2_PHY1_TXPRE			(0x3 << 12)
#define USB2_PHY1_PRE_VAL		(0x1 << 12)

#define USB3_DEF_CRG		0x1f010000
#define USB3_DEF_CFG_MASK	0xffff0000
#define USB2_DEF_CRG		0x00001301
#define USB2_DEF_CFG_MASK	0x0000ffff

#define PCIE_USB3_MASK		(0x3 << 12)
#define get_combphy_mode(p)	(((p) & PCIE_USB3_MASK) >> 12)
#define USB3				0x1
#define PCIE_X1				0x0

static uintptr_t xhci_base = 0;

int xhci_hcd_init(int index, struct xhci_hccr **hccr, struct xhci_hcor **hcor)
{
	if ((hccr == NULL) || (hcor == NULL))
		return -EINVAL;

	if (index == 0)
		xhci_base = USB3_CTRL_REG_BASE;
	if (index == 1)
		xhci_base = USB2_CTRL_REG_BASE;

	*hccr = (struct xhci_hccr *)(xhci_base);
	*hcor = (struct xhci_hcor *)((uintptr_t) *hccr +
				HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

void hisi_usb_eye_config(void)
{
	unsigned int reg;

	/* port0 phy high-spped DC adjust: 0% --> 4% */
	/* port0 pre elec adjust: 0 --> 1x */
	reg = readl(MISC_REG_BASE + USB2_PHY0);
	reg &= ~USB2_PHY0_TXVREFTUNE;
	reg &= ~USB2_PHY0_TXPRE;
	reg |= USB2_PHY0_VREF_VAL;
	reg |= USB2_PHY0_PRE_VAL;
	writel(reg, MISC_REG_BASE + USB2_PHY0);
	udelay(U_LEVEL5);

	/* port1 phy high-spped DC adjust: 0% --> 4% */
	/* port1 pre elec adjust: 0 --> 1x */
	reg = readl(MISC_REG_BASE + USB2_PHY1);
	reg &= ~USB2_PHY1_TXVREFTUNE;
	reg &= ~USB2_PHY1_TXPRE;
	reg |= USB2_PHY1_VREF_VAL;
	reg |= USB2_PHY1_PRE_VAL;
	writel(reg, MISC_REG_BASE + USB2_PHY1);
	udelay(U_LEVEL5);

	/* usb3 Tx margin adjust: 0 --> 900mv */
	reg = readl(USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	reg &= ~USB3_TX_MARGIN;
	reg |= USB3_TX_MARGIN_VAL;
	writel(reg, USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
}

void hisi_usb_config(void)
{
	unsigned int reg;

	/* set usb2 CRG default val */
	reg = readl(USB3_CTRL_CFG);
	reg &= ~(USB2_DEF_CFG_MASK);
	reg |= USB2_DEF_CRG;
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL6);

	/* U2 vcc reset */
	reg = readl(USB3_CTRL_CFG);
	reg |= USB2_VCC_SRST_REQ;
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL5);

	/* release TPOR default release */
	reg = readl(USB2_PHY_CFG);
	reg &= ~USB2_PHY1_PORT_TREQ;
	writel(reg, USB2_PHY_CFG);
	udelay(U_LEVEL6);

	/* utmi clock sel */
	reg = readl(USB3_CTRL_CFG);
	reg &= ~USB2_UTMI_CKSEL;
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL6);

	/* open phy ref clk default open */
	reg = readl(USB2_PHY_CFG);
	reg |= USB2_PHY1_CKEN;
	writel(reg, USB2_PHY_CFG);
	udelay(U_LEVEL6);

	/* U2 phy reset release */
	reg = readl(USB2_PHY_CFG);
	reg &= ~USB2_PHY1_REQ;
	writel(reg, USB2_PHY_CFG);
	udelay(U_LEVEL6);

	/* config U2 Controller release */
	reg = readl(USB3_CTRL_CFG);
	reg &= ~USB2_VCC_SRST_REQ;
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL5);

	/* u2 port default host */
	reg = readl(USB2_CTRL_REG_BASE + REG_GCTL);
	reg &= ~PORT_CAP_DIR;
	reg |= DEFAULT_HOST_MOD;
	writel(reg, USB2_CTRL_REG_BASE + REG_GCTL);
	udelay(U_LEVEL2);
}

void hisi_usb3_init_crg_clk(void)
{
	int reg;

	/* set usb3 CRG default val */
	reg = readl(USB3_CTRL_CFG);
	reg &= ~(USB3_DEF_CFG_MASK);
	reg |= USB3_DEF_CRG;
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL6);

	/* disable port0 ss */
	reg = readl(MISC_REG_BASE + USB_PORT0);
	reg |= U3_PORT_DISABLE;
	writel(reg, MISC_REG_BASE + USB_PORT0);

	/*
	 * According to description of SYSSYAT register, different
	 * HW modes of COMBPHY require specific configurations.
	 */
	reg = readl(REG_BASE_SCTL + REG_SYSSTAT);
	if (get_combphy_mode(reg) == USB3) {
		/* combphy reset in USB3 mode */
		reg = readl(USB3_COMBPHY_CFG);
		reg |= COMBPHY_SRST_REQ;
		writel(reg, USB3_COMBPHY_CFG);
		udelay(U_LEVEL5);
	} else if (get_combphy_mode(reg) == PCIE_X1) {
		/* Choose clock from CRG in PCIE X1 mode */
		reg = readl(USB3_CTRL_CFG);
		reg |= USB3_PCLK_OCC_SEL;
		writel(reg, USB3_CTRL_CFG);
		udelay(U_LEVEL5);
	}

	/* release TPOR default release */
	reg = readl(USB2_PHY_CFG);
	reg &= ~USB2_PHY0_PORT_TREQ;
	writel(reg, USB2_PHY_CFG);
	udelay(U_LEVEL6);

	/* utmi clock sel */
	reg = readl(USB3_CTRL_CFG);
	reg &= ~USB3_UTMI_CKSEL;
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL6);

	/* open phy ref clk default open */
	reg = readl(USB2_PHY_CFG);
	reg |= USB2_PHY0_CKEN;
	writel(reg, USB2_PHY_CFG);
	udelay(U_LEVEL6);
}

void hisi_usb3_config(void)
{
	unsigned int reg;

	/* init crg and clk */
	hisi_usb3_init_crg_clk();

	/* U2 phy reset release */
	reg = readl(USB2_PHY_CFG);
	reg &= ~USB2_PHY0_REQ;
	writel(reg, USB2_PHY_CFG);
	udelay(U_LEVEL6);

	/* Release the specific configuration of COMBPHY. */
	reg = readl(REG_BASE_SCTL + REG_SYSSTAT);
	if (get_combphy_mode(reg) == USB3) {
		/* open ref CKEN */
		reg = readl(USB3_COMBPHY_CFG);
		reg |= COMBPHY0_REF_CKEN;
		writel(reg, USB3_COMBPHY_CFG);
		udelay(U_LEVEL5);

		reg = readl(USB3_COMBPHY_CFG);
		reg &= ~COMBPHY_SRST_REQ;
		writel(reg, USB3_COMBPHY_CFG);
		udelay(U_LEVEL5);
	}

	/* config U3 Controller USB3_0 PHY OUTPUT */
	reg = readl(USB3_CTRL_CFG);
	reg &= ~USB3_VCC_SRST_REQ;
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL6);

	reg = readl(USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	reg |= PCS_SSP_SOFT_RESET;
	writel(reg, USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	udelay(U_LEVEL6);

	/* u3 port default host */
	reg = readl(USB3_CTRL_REG_BASE + REG_GCTL);
	reg &= ~PORT_CAP_DIR;
	reg |= DEFAULT_HOST_MOD;
	writel(reg, USB3_CTRL_REG_BASE + REG_GCTL);
	udelay(U_LEVEL2);

	reg = readl(USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	reg &= ~PCS_SSP_SOFT_RESET;
	reg &= ~SUSPEND_USB3_SS_PHY; /* disable suspend */
	writel(reg, USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
	udelay(U_LEVEL2);

	writel(PERI_USB3_GTXTHRCFG, USB3_CTRL_REG_BASE + GTXTHRCFG);
	udelay(U_LEVEL2);
}

void phy_hiusb_init(int index)
{
	if (index)
		hisi_usb_config();
	else
		hisi_usb3_config();

	hisi_usb_eye_config();
}
EXPORT_SYMBOL(phy_hiusb_init);

void xhci_hcd_stop(int index)
{
	unsigned int reg;

	/* U2 vcc reset */
	reg = readl(USB3_CTRL_CFG);
	reg |= USB2_VCC_SRST_REQ;
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL5);

	/* U3 vcc reset */
	reg = readl(USB3_CTRL_CFG);
	reg |= USB3_VCC_SRST_REQ;
	writel(reg, USB3_CTRL_CFG);
	udelay(U_LEVEL5);

	reg = readl(REG_BASE_SCTL + REG_SYSSTAT);
	if (get_combphy_mode(reg) == USB3) {
		/* combphy reset */
		reg = readl(USB3_COMBPHY_CFG);
		reg |= COMBPHY_SRST_REQ;
		writel(reg, USB3_COMBPHY_CFG);
		udelay(U_LEVEL5);
	}
}
EXPORT_SYMBOL(xhci_hcd_stop);
