/*
 * phy-usb-hi3531dv200.c
 *
 * Hi3531DV200 usb phy driver.
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
#ifdef CONFIG_TARGET_HI3531DV200
#include <asm/arch-hi3531dv200/platform.h>
#endif
#ifdef CONFIG_TARGET_HI3535AV100
#include <asm/arch-hi3535av100/platform.h>
#endif
#include <dm.h>
#include <usb.h>
#include <usb/xhci.h>
#include "phy-hisi-usb.h"

static uintptr_t xhci_base = 0;

int xhci_hcd_init(int index, struct xhci_hccr **hccr, struct xhci_hcor **hcor)
{
	if (index == 0)
		xhci_base = USB3_CTRL_REG_BASE;
	if (index == 1)
		xhci_base = USB2_CTRL_REG_BASE;

	*hccr = (struct xhci_hccr *)(xhci_base);
	*hcor = (struct xhci_hcor *)((uintptr_t) *hccr
			+ HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

void usb2_crg_config(void)
{
	unsigned int reg;

	/* ctrl1 rst*/
	reg = readl(USB2_CTRL1_CFG);
	reg |= USB2_1_SRST_REQ;
	writel(reg, USB2_CTRL1_CFG);
	udelay(U_LEVEL6);

	/* usb2 phy1 rst */
	reg = readl(USB2_PHY1_CFG);
	reg |= (USB2_PHY1_REQ | USB2_PHY1_TREQ | USB2_PHY1_APB_SRST_REQ);
	writel(reg, USB2_PHY1_CFG);
	udelay(U_LEVEL6);

	/* open usb2 phy1 clk */
	reg = readl(USB2_PHY1_CFG);
	reg |= USB2_PHY1_XTAL_CKEN;
	writel(reg, USB2_PHY1_CFG);
	udelay(U_LEVEL6);

	/* cancel usb2 phy1 rst */
	reg = readl(USB2_PHY1_CFG);
	reg &= ~(USB2_PHY1_REQ | USB2_PHY1_TREQ | USB2_PHY1_APB_SRST_REQ);
	writel(reg, USB2_PHY1_CFG);
	mdelay(U_LEVEL10);

	/* open utmi/ref/bus clk */
	reg = readl(USB2_CTRL1_CFG);
	reg |= USB2_1_BUS_CKEN;
	reg |= USB2_1_REF_CKEN;
	reg |= USB2_1_UTMI_CKEN;
	writel(reg, USB2_CTRL1_CFG);
	udelay(U_LEVEL6);

	/* cancel ctrl1 rst*/
	reg = readl(USB2_CTRL1_CFG);
	reg &= ~USB2_1_SRST_REQ;
	writel(reg, USB2_CTRL1_CFG);
	udelay(U_LEVEL6);
}

void usb2_phy_config(void)
{
	unsigned int reg;
	unsigned int trim_val;

	/* usb2 phy1 pll enable */
	reg = readl(USB2_PHY1_BASE + PHY_PLL_OFFSET);
	reg |= PHY_PLL_ENABLE;
	writel(reg, USB2_PHY1_BASE + PHY_PLL_OFFSET);
	udelay(U_LEVEL5);

	/* adeust the hstx mbias */
	reg = readl(USB2_PHY1_BASE + U2_ANA_CFG0);
	reg = ana_cfg0_val(reg);
	reg |= U2_1_HSTX_MBIAS;
	writel(reg, USB2_PHY1_BASE + U2_ANA_CFG0);
	udelay(U_LEVEL5);

	/* vdiscref sel==>560mV */
	reg = readl(USB2_PHY1_BASE + U2_ANA_CFG2);
	reg = ana_cfg2_val(reg);
	reg |= U2_1_VDISCREF_SEL;
	reg |= U2_TEST_TX;
	writel(reg, USB2_PHY1_BASE + U2_ANA_CFG2);
	udelay(U_LEVEL5);

	/* OTP usb2 phy1*/
	trim_val = readl(USB_SYS_CTRL_BASE);
	trim_val = usb2_1_trim_val(trim_val);
	if ((trim_val >= U2_TRIM_VAL_MIN) && (trim_val <= U2_TRIM_VAL_MAX)) {
		reg = readl(USB2_PHY1_BASE + U2_ANA_CFG2);
		reg = usb2_rt_trim_clr(reg);
		reg |= usb2_rt_trim_set(trim_val);
		writel(reg, USB2_PHY1_BASE + U2_ANA_CFG2);
		udelay(U_LEVEL5);
	}

	/* ATOP TEST bit */
	reg = readl(USB2_PHY1_BASE + U2_ANA_CFG3);
	reg = ana_cfg3_val(reg);
	reg |= U2_1_SLEW_RATE_OPT;
	writel(reg, USB2_PHY1_BASE + U2_ANA_CFG3);
	udelay(U_LEVEL5);

	/* vtxref sel==>430mV, enable fls edge mode */
	reg = readl(USB2_PHY1_BASE + U2_ANA_CFG4);
	reg = ana_cfg4_val(reg);
	reg |= U2_VTXREF_SEL;
	reg |= U2_FLS_EDGE_MODE;
	writel(reg, USB2_PHY1_BASE + U2_ANA_CFG4);
	udelay(U_LEVEL5);
}

void usb3_crg_config(void)
{
	unsigned int reg;

	/* USB3 disable */
	reg = readl(MISC_REG_BASE + USB_CTRL6);
	reg |= U3_PORT_DISABLE;
	writel(reg, MISC_REG_BASE + USB_CTRL6);
	udelay(U_LEVEL6);

	/* usb2 phy0 rst */
	reg = readl(USB2_PHY0_CFG);
	reg |= (USB2_PHY0_REQ | USB2_PHY0_TREQ | USB2_PHY0_APB_SRST_REQ);
	writel(reg, USB2_PHY0_CFG);
	udelay(U_LEVEL6);

	/* usb2 phy2 rst */
	reg = readl(USB2_PHY2_CFG);
	reg |= (USB2_PHY2_REQ | USB2_PHY2_TREQ | USB2_PHY2_APB_SRST_REQ);
	writel(reg, USB2_PHY2_CFG);
	udelay(U_LEVEL6);

	/* open usb2 phy0 clk */
	reg = readl(USB2_PHY0_CFG);
	reg |= USB2_PHY0_XTAL_CKEN;
	writel(reg, USB2_PHY0_CFG);
	udelay(U_LEVEL6);

	/* open usb2 phy2 clk */
	reg = readl(USB2_PHY2_CFG);
	reg |= USB2_PHY2_XTAL_CKEN;
	writel(reg, USB2_PHY2_CFG);
	udelay(U_LEVEL6);

	/* cancel usb2 phy0 rst */
	reg = readl(USB2_PHY0_CFG);
	reg &= ~(USB2_PHY0_REQ | USB2_PHY0_TREQ | USB2_PHY0_APB_SRST_REQ);
	writel(reg, USB2_PHY0_CFG);
	mdelay(U_LEVEL10);

	/* cancel usb2 phy2 rst */
	reg = readl(USB2_PHY2_CFG);
	reg &= ~(USB2_PHY2_REQ | USB2_PHY2_TREQ | USB2_PHY2_APB_SRST_REQ);
	writel(reg, USB2_PHY2_CFG);
	mdelay(U_LEVEL10);

	/* open combphy0 clk */
	reg = readl(USB3_COMBPHY_CFG);
	reg |= COMBPHY0_REF_CKEN;
	writel(reg, USB3_COMBPHY_CFG);
	udelay(U_LEVEL6);

	/* cancel combphy0 rst */
	reg = readl(USB3_COMBPHY_CFG);
	reg &= ~COMBPHY0_SRST_REQ;
	writel(reg, USB3_COMBPHY_CFG);
	udelay(U_LEVEL5);

	/* open pipe/suspend/ref/bus clk */
	reg = readl(USB3_PHY_CFG);
	reg |= USB3_BUS_CKEN;
	reg |= USB3_REF_CKEN;
	reg |= USB3_SUSPEND_CKEN;
	reg |= USB3_UTMI_CKEN;
	reg |= USB3_PIPE_CKEN;
	writel(reg, USB3_PHY_CFG);
	udelay(U_LEVEL6);

	/* open utmi clk */
	reg = readl(USB2_CTRL0_CFG);
	reg |= USB2_0_UTMI_CKEN;
	writel(reg, USB2_CTRL0_CFG);
	udelay(U_LEVEL6);

	/* cancel ctrl0 rst */
	reg = readl(USB3_PHY_CFG);
	reg &= ~USB3_SRST_REQ;
	writel(reg, USB3_PHY_CFG);
	udelay(U_LEVEL6);
}

void usb2_phy0_config(void)
{
	unsigned int reg;
	unsigned int trim_val;

	/* usb2 phy0 pll enable */
	reg = readl(USB2_PHY0_BASE + PHY_PLL_OFFSET);
	reg |= PHY_PLL_ENABLE;
	writel(reg, USB2_PHY0_BASE + PHY_PLL_OFFSET);
	udelay(U_LEVEL5);

	/* adjust the hstx mbias */
	reg = readl(USB2_PHY0_BASE + U2_ANA_CFG0);
	reg = ana_cfg0_val(reg);
	reg |= U2_0_HSTX_MBIAS;
	writel(reg, USB2_PHY0_BASE + U2_ANA_CFG0);
	udelay(U_LEVEL5);

	/* vdiscref sel==>560mV */
	reg = readl(USB2_PHY0_BASE + U2_ANA_CFG2);
	reg = ana_cfg2_val(reg);
	reg |= U2_0_VDISCREF_SEL;
	reg |= U2_TEST_TX;
	writel(reg, USB2_PHY0_BASE + U2_ANA_CFG2);
	udelay(U_LEVEL5);

	/* OTP usb2 phy0*/
	trim_val = readl(USB_SYS_CTRL_BASE);
	trim_val = usb2_0_trim_val(trim_val);
	if ((trim_val >= U2_TRIM_VAL_MIN) && (trim_val <= U2_TRIM_VAL_MAX)) {
		reg = readl(USB2_PHY0_BASE + U2_ANA_CFG2);
		reg = usb2_rt_trim_clr(reg);
		reg |= usb2_rt_trim_set(trim_val);
		writel(reg, USB2_PHY0_BASE + U2_ANA_CFG2);
		udelay(U_LEVEL5);
	}

	/* ATOP TEST bit */
	reg = readl(USB2_PHY0_BASE + U2_ANA_CFG3);
	reg = ana_cfg3_val(reg);
	reg |= U2_0_SLEW_RATE_OPT;
	writel(reg, USB2_PHY0_BASE + U2_ANA_CFG3);
	udelay(U_LEVEL5);

	/* vtxref sel==>430mV, enable fls edge mode */
	reg = readl(USB2_PHY0_BASE + U2_ANA_CFG4);
	reg = ana_cfg4_val(reg);
	reg |= U2_VTXREF_SEL;
	reg |= U2_FLS_EDGE_MODE;
	writel(reg, USB2_PHY0_BASE + U2_ANA_CFG4);
	udelay(U_LEVEL5);
}

void usb2_phy2_config(void)
{
	unsigned int reg;
	unsigned int trim_val;

	/* usb2 phy2 pll enable */
	reg = readl(USB2_PHY2_BASE + PHY_PLL_OFFSET);
	reg |= PHY_PLL_ENABLE;
	writel(reg, USB2_PHY2_BASE + PHY_PLL_OFFSET);
	udelay(U_LEVEL5);

	/* adjust the hstx mbias */
	reg = readl(USB2_PHY2_BASE + U2_ANA_CFG0);
	reg = ana_cfg0_val(reg);
	reg |= U2_2_HSTX_MBIAS;
	writel(reg, USB2_PHY2_BASE + U2_ANA_CFG0);
	udelay(U_LEVEL5);

	/* vdiscref sel==>540mV */
	reg = readl(USB2_PHY2_BASE + U2_ANA_CFG2);
	reg = ana_cfg2_val(reg);
	reg |= U2_2_VDISCREF_SEL;
	reg |= U2_TEST_TX;
	writel(reg, USB2_PHY2_BASE + U2_ANA_CFG2);
	udelay(U_LEVEL5);

	/* OTP usb2 phy2*/
	trim_val = readl(USB_SYS_CTRL_BASE);
	trim_val = usb2_2_trim_val(trim_val);
	if ((trim_val >= U2_TRIM_VAL_MIN) && (trim_val <= U2_TRIM_VAL_MAX)) {
		reg = readl(USB2_PHY2_BASE + U2_ANA_CFG2);
		reg = usb2_rt_trim_clr(reg);
		reg |= usb2_rt_trim_set(trim_val);
		writel(reg, USB2_PHY2_BASE + U2_ANA_CFG2);
		udelay(U_LEVEL5);
	}

	/* ATOP TEST bit */
	reg = readl(USB2_PHY2_BASE + U2_ANA_CFG3);
	reg = ana_cfg3_val(reg);
	reg |= U2_2_SLEW_RATE_OPT;
	writel(reg, USB2_PHY2_BASE + U2_ANA_CFG3);
	udelay(U_LEVEL5);

	reg = readl(USB2_PHY2_BASE + U2_ANA_CFG4);
	reg = ana_cfg4_val(reg);
	reg |= U2_VTXREF_SEL;
	reg |= U2_FLS_EDGE_MODE;
	writel(reg, USB2_PHY2_BASE + U2_ANA_CFG4);
	udelay(U_LEVEL5);
}

void usb3_phy_config(void)
{
	usb2_phy0_config();
	usb2_phy2_config();

	/* PI_CURRENT_TRIM ==>2'b00 to 2'b01 */
	writel(PI_CURRENT_TRIM_ENABLE, USB_MISC_REG_BASE);
	writel(PI_CURRENT_TRIM_VAL, USB_MISC_REG_BASE);
	writel(PI_CURRENT_TRIM_ENABLE, USB_MISC_REG_BASE);
	udelay(U_LEVEL5);

	/* TX_SWING_COMP ==>4'b1000 to 4b'1100 */
	writel(TX_SWING_COMP_ENABLE, USB_MISC_REG_BASE);
	writel(TX_SWING_COMP_VAL, USB_MISC_REG_BASE);
	writel(TX_SWING_COMP_ENABLE, USB_MISC_REG_BASE);
	udelay(U_LEVEL5);
}

void phy_hiusb_init(int index)
{
	unsigned long flags;

	local_irq_save(flags);

	switch (index) {
	case 0:
		usb3_crg_config();
		usb3_phy_config();
		break;
	case 1:
		usb2_crg_config();
		usb2_phy_config();
		break;
	default:
			break;
	}

	local_irq_restore(flags);
}

void usb2_disable(void)
{
	unsigned int reg;

	/* ctrl1 rst */
	reg = readl(USB2_CTRL1_CFG);
	reg |= USB2_1_SRST_REQ;
	writel(reg, USB2_CTRL1_CFG);
	udelay(U_LEVEL6);

	/* usb2 phy1 rst */
	reg = readl(USB2_PHY1_CFG);
	reg |= (USB2_PHY1_REQ | USB2_PHY1_TREQ);
	writel(reg, USB2_PHY1_CFG);
	udelay(U_LEVEL6);
}

void usb3_disable(void)
{
	unsigned int reg;

	/* ctrl0 rst */
	reg = readl(USB3_PHY_CFG);
	reg |= USB3_SRST_REQ;
	writel(reg, USB3_PHY_CFG);
	udelay(U_LEVEL6);

	/* usb2 phy0 rst */
	reg = readl(USB2_PHY0_CFG);
	reg |= (USB2_PHY0_REQ | USB2_PHY0_TREQ);
	writel(reg, USB2_PHY0_CFG);
	udelay(U_LEVEL6);

	/* usb2 phy2 rst */
	reg = readl(USB2_PHY2_CFG);
	reg |= (USB2_PHY2_REQ | USB2_PHY2_TREQ);
	writel(reg, USB2_PHY2_CFG);
	udelay(U_LEVEL6);
}

void xhci_hcd_stop(int index)
{
	switch (index) {
	case 0:
		usb3_disable();
		break;
	case 1:
		usb2_disable();
		break;
	default:
		break;
	}
}
