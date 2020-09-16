/*
 * phy-usb-hi3521dv200.c
 *
 * Hi3521DV200 usb phy driver.
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
#include <asm/arch-hi3521dv200/platform.h>
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

void usb2_phy0_config(void)
{
	unsigned int reg;
	unsigned int trim_val;

	/* usb2 phy0 pll enable */
	reg = readl(USB2_PHY0_BASE + PHY_PLL_OFFSET);
	reg |= PHY_PLL_ENABLE;
	writel(reg, USB2_PHY0_BASE + PHY_PLL_OFFSET);
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

	/* rg_hstx_mbias: 4'b0011==>4'b1011 */
	reg = readl(USB2_PHY0_BASE + RG_HSTX_MBIAS);
	reg &= ~RG_HSTX_MBIAS_MASK;
	reg |= RG_HSTX_MBIAS_VAL;
	writel(reg, USB2_PHY0_BASE + RG_HSTX_MBIAS);
	udelay(U_LEVEL5);

	/* TX TEST bit Chirp KJ: 1'b0==>1'b1 */
	reg = readl(USB2_PHY0_BASE + TX_TEST_BIT);
	reg |= TX_TEST_BIT_VAL;
	writel(reg, USB2_PHY0_BASE + TX_TEST_BIT);
	udelay(U_LEVEL5);

	/* disconnect reference voltage sel: 3'b001==>3'b011 */
	reg = readl(USB2_PHY0_BASE + DISC_REF_VOL_SEL);
	reg &= ~DISC_REF_VOL_SEL_MASK;
	reg |= DISC_REF_VOL_SEL_VAL;
	writel(reg, USB2_PHY0_BASE + DISC_REF_VOL_SEL);
	udelay(U_LEVEL5);

	/* slew rate option: 2b'00==>2b'01 */
	reg = readl(USB2_PHY0_BASE + SLEW_RATE_OPTION);
	reg &= ~SLEW_RATE_OPTION_MASK;
	reg |= SLEW_RATE_OPTION_VAL;
	writel(reg, USB2_PHY0_BASE + SLEW_RATE_OPTION);
	udelay(U_LEVEL5);

	/* TX reference voltage sel: 4'100==>4'110 */
	reg = readl(USB2_PHY0_BASE + TX_REF_VOL_SEL);
	reg &= ~TX_REF_VOL_SEL_MASK;
	reg |= TX_REF_VOL_SEL_VAL;
	writel(reg, USB2_PHY0_BASE + TX_REF_VOL_SEL);
	udelay(U_LEVEL5);

	/* rg_fls_edge_mode: 1'b0==>1'b1 */
	reg = readl(USB2_PHY0_BASE + RG_FL_EDGE_MODE);
	reg |= RG_FL_EDGE_MODE_VAL;
	writel(reg, USB2_PHY0_BASE + RG_FL_EDGE_MODE);
	udelay(U_LEVEL5);
}

void usb2_phy1_config(void)
{
	unsigned int reg;
	unsigned int trim_val;

	/* usb2 phy1 pll enable */
	reg = readl(USB2_PHY1_BASE + PHY_PLL_OFFSET);
	reg |= PHY_PLL_ENABLE;
	writel(reg, USB2_PHY1_BASE + PHY_PLL_OFFSET);
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

	/* rg_hstx_mbias: 4'b0011==>4'b1011 */
	reg = readl(USB2_PHY1_BASE + RG_HSTX_MBIAS);
	reg &= ~RG_HSTX_MBIAS_MASK;
	reg |= RG_HSTX_MBIAS_VAL;
	writel(reg, USB2_PHY1_BASE + RG_HSTX_MBIAS);
	udelay(U_LEVEL5);

	/* TX TEST bit Chirp KJ: 1'b0==>1'b1 */
	reg = readl(USB2_PHY1_BASE + TX_TEST_BIT);
	reg |= TX_TEST_BIT_VAL;
	writel(reg, USB2_PHY1_BASE + TX_TEST_BIT);
	udelay(U_LEVEL5);

	/* disconnect reference voltage sel: 3'b001==>3'b011 */
	reg = readl(USB2_PHY1_BASE + DISC_REF_VOL_SEL);
	reg &= ~DISC_REF_VOL_SEL_MASK;
	reg |= DISC_REF_VOL_SEL_VAL;
	writel(reg, USB2_PHY1_BASE + DISC_REF_VOL_SEL);
	udelay(U_LEVEL5);

	/* slew rate option: 2b'00==>2b'01 */
	reg = readl(USB2_PHY1_BASE + SLEW_RATE_OPTION);
	reg &= ~SLEW_RATE_OPTION_MASK;
	reg |= SLEW_RATE_OPTION_VAL;
	writel(reg, USB2_PHY1_BASE + SLEW_RATE_OPTION);
	udelay(U_LEVEL5);

	/* TX reference voltage sel: 4'100==>4'110 */
	reg = readl(USB2_PHY1_BASE + TX_REF_VOL_SEL);
	reg &= ~TX_REF_VOL_SEL_MASK;
	reg |= TX_REF_VOL_SEL_VAL;
	writel(reg, USB2_PHY1_BASE + TX_REF_VOL_SEL);
	udelay(U_LEVEL5);

	/* rg_fls_edge_mode: 1'b0==>1'b1 */
	reg = readl(USB2_PHY1_BASE + RG_FL_EDGE_MODE);
	reg |= RG_FL_EDGE_MODE_VAL;
	writel(reg, USB2_PHY1_BASE + RG_FL_EDGE_MODE);
	udelay(U_LEVEL5);
}

void usb2_phy2_config(void)
{
	unsigned int reg;
	unsigned int trim_val;

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

	/* rg_hstx_mbias: 4'b0011==>4'b1011 */
	reg = readl(USB2_PHY2_BASE + RG_HSTX_MBIAS);
	reg &= ~RG_HSTX_MBIAS_MASK;
	reg |= RG_HSTX_MBIAS_VAL;
	writel(reg, USB2_PHY2_BASE + RG_HSTX_MBIAS);
	udelay(U_LEVEL5);

	/* TX TEST bit Chirp KJ: 1'b0==>1'b1 */
	reg = readl(USB2_PHY2_BASE + TX_TEST_BIT);
	reg |= TX_TEST_BIT_VAL;
	writel(reg, USB2_PHY2_BASE + TX_TEST_BIT);
	udelay(U_LEVEL5);

	/* disconnect reference voltage sel: 3'b001==>3'b011 */
	reg = readl(USB2_PHY2_BASE + DISC_REF_VOL_SEL);
	reg &= ~DISC_REF_VOL_SEL_MASK;
	reg |= DISC_REF_VOL_SEL_VAL;
	writel(reg, USB2_PHY2_BASE + DISC_REF_VOL_SEL);
	udelay(U_LEVEL5);

	/* slew rate option: 2b'00==>2b'01 */
	reg = readl(USB2_PHY2_BASE + SLEW_RATE_OPTION);
	reg &= ~SLEW_RATE_OPTION_MASK;
	reg |= SLEW_RATE_OPTION_VAL;
	writel(reg, USB2_PHY2_BASE + SLEW_RATE_OPTION);
	udelay(U_LEVEL5);

	/* TX reference voltage sel: 4'100==>4'110 */
	reg = readl(USB2_PHY2_BASE + TX_REF_VOL_SEL);
	reg &= ~TX_REF_VOL_SEL_MASK;
	reg |= TX_REF_VOL_SEL_VAL;
	writel(reg, USB2_PHY2_BASE + TX_REF_VOL_SEL);
	udelay(U_LEVEL5);

	/* rg_fls_edge_mode: 1'b0==>1'b1 */
	reg = readl(USB2_PHY2_BASE + RG_FL_EDGE_MODE);
	reg |= RG_FL_EDGE_MODE_VAL;
	writel(reg, USB2_PHY2_BASE + RG_FL_EDGE_MODE);
	udelay(U_LEVEL5);

}

void hisi_usb_ctrl_config(void)
{
	unsigned int reg;

	reg = readl(USB3_CTRL_REG_BASE + GUSB2PHYCFG);
	reg &= ~U2_FREECLK_EXISTS;
	writel(reg, USB3_CTRL_REG_BASE + GUSB2PHYCFG);
	udelay(U_LEVEL6);
}

void hisi_usb2_0_config(void)
{
	unsigned int reg;

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
	udelay(U_LEVEL10);

	/* cancel usb2 phy2 rst */
	reg = readl(USB2_PHY2_CFG);
	reg &= ~(USB2_PHY2_REQ | USB2_PHY2_TREQ | USB2_PHY2_APB_SRST_REQ);
	writel(reg, USB2_PHY2_CFG);
	udelay(U_LEVEL10);

	usb2_phy0_config();
	usb2_phy2_config();

	/* open clk */
	reg = readl(USB2_CTRL0_CFG);
	reg |= (USB2_0_REF_CKEN | USB2_0_BUS_CKEN | USB2_0_UTMI_CKEN
		| USB2_2_UTMI_CKEN | USB2_0_FREECLK_CKSEL);
	writel(reg, USB2_CTRL0_CFG);
	udelay(U_LEVEL6);

	/* cancel ctrl0 rst */
	reg = readl(USB2_CTRL0_CFG);
	reg &= ~USB2_0_SRST_REQ;
	writel(reg, USB2_CTRL0_CFG);
	udelay(U_LEVEL6);

	hisi_usb_ctrl_config();
}

void hisi_usb2_1_config(void)
{
	unsigned int reg;

	/* open usb2 phy1 clk */
	reg = readl(USB2_PHY1_CFG);
	reg |= USB2_PHY1_XTAL_CKEN;
	writel(reg, USB2_PHY1_CFG);
	udelay(U_LEVEL6);

	/* cancel usb2 phy1 rst */
	reg = readl(USB2_PHY1_CFG);
	reg &= ~(USB2_PHY1_REQ | USB2_PHY1_TREQ | USB2_PHY1_APB_SRST_REQ);
	writel(reg, USB2_PHY1_CFG);
	udelay(U_LEVEL10);

	usb2_phy1_config();

	/* open clk */
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

void ctrl0_disable(void)
{
	/* default value rewrite */
	writel(DEF_VAL_3632, USB2_CTRL0_CFG);
	writel(DEF_VAL_3636, USB2_PHY0_CFG);
	writel(DEF_VAL_3672, USB2_PHY2_CFG);
	udelay(U_LEVEL6);
}

void ctrl1_disable(void)
{
	/* default value rewrite */
	writel(DEF_VAL_3640, USB2_CTRL1_CFG);
	writel(DEF_VAL_3644, USB2_PHY1_CFG);
	udelay(U_LEVEL6);
}

void phy_hiusb_init(int index)
{
	unsigned long flags;

	local_irq_save(flags);

	switch (index) {
	case 0:
		ctrl0_disable();
		hisi_usb2_0_config();
		break;
	case 1:
		ctrl1_disable();
		hisi_usb2_1_config();
		break;
	default:
			break;
	}

	local_irq_restore(flags);
}
EXPORT_SYMBOL(phy_hiusb_init);

void xhci_hcd_stop(int index)
{
	switch (index) {
	case 0:
		ctrl0_disable();
		break;
	case 1:
		ctrl1_disable();
		break;
	default:
		break;
	}
}
EXPORT_SYMBOL(xhci_hcd_stop);
