/*
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
 * Description: Hieth system operation
 */


#include <config.h>
#include "hieth.h"
#include "sys.h"

#if defined(CONFIG_GODBOX) || defined(CONFIG_GODBOX_V1)
#define HIETH_CRG_REG (REG_BASE_CRG + REG_PERI_CRG26)
#else
#define HIETH_CRG_REG (CRG_REG_BASE + REG_ETH_CRG)
#endif

#define ETH_SOFT_RESET bit(0)
#if defined(CONFIG_GODBOX) || defined(CONFIG_GODBOX_V1)
#define ETH_CLK_ENABLE bit(8)
#elif defined(CONFIG_TARGET_HI3521DV200) || defined(CONFIG_TARGET_HI3520DV500)
#define ETH_CLK_ENABLE bit(4)
#else
#define ETH_CLK_ENABLE bit(1)
#endif

#if defined(HISFV_RESET_PHY_BY_CRG)
#if defined(CONFIG_TARGET_HI3521DV200) || defined(CONFIG_TARGET_HI3520DV500)
#define ETH_EXTERNAL_PHY_RESET bit(0)
#else
#define ETH_EXTERNAL_PHY_RESET bit(3)
#endif
#endif

#if defined(CONFIG_TARGET_HI3521DV200) || defined(CONFIG_TARGET_HI3520DV500)
#define ETH_CORE_CLK_SELECT_54M bit(12)
#else
#define ETH_CORE_CLK_SELECT_54M bit(7)
#endif

#if defined(CONFIG_HI3520D)
#define HIETH_SYSCTL_REG       (SYS_CTRL_REG_BASE + PERIPHCTRL24)
#define ETH_INTERNAL_PHY_RESET bit(2)
#define HIETH_EFUSE_REG        (CRG_REG_BASE + EFUSE_CTRL_CRG)
#define HIETH_EFUSE_DATA_REG   (EFUSE_REG_BASE + EFUSE_DATA_SEL)
#elif defined(CONFIG_HI3536DV100)
#define HIETH_SYSCTL_REG        (MISC_REG_BASE + REG_FEPHY_CTRL1)
#define BIT_FEPHY_SEL           bit(5)
#define BIT_PHY_RMII_MODE       bit(8)
#define ETH_INTERNAL_PHY_RESET  bit(9)
#define ETH_INTERNAL_PHY_CLK_EN bit(10)
#endif

#if defined(CONFIG_TARGET_HI3516EV200)
#define HIETH_SYSCTL_REG        (SYS_CTRL_REG_BASE + MISC_CTRL9)
#define ETH_INTERNAL_PHY_RESET  bit(3)
#define ETH_INTERNAL_PHY_CLK_EN bit(2)
#endif

#if defined(CONFIG_TARGET_HI3521DV200) || defined(CONFIG_TARGET_HI3520DV500)
#define HIETH_SYSCTL_REG        (SYS_CTRL_REG_BASE + REG_FEPHY_CTRL0)
#define ETH_INTERNAL_PHY_RESET  bit(0)
#define ETH_INTERNAL_PHY_CLK_EN bit(4)
#endif

#if defined(CONFIG_TARGET_HI3521DV200) || defined(CONFIG_TARGET_HI3520DV500)
#define HIETH_CRG_INPHY_CLK_REG   (CRG_REG_BASE + REG_INFEPHY_CLK_RST)
#define HIETH_CRG_EXTPHY_CLK_REG  (CRG_REG_BASE + REG_EXTFEPHY_CLK_RST)
#else
#define HIETH_CRG_INPHY_CLK_REG   HIETH_CRG_REG
#define HIETH_CRG_EXTPHY_CLK_REG  HIETH_CRG_REG
#endif

#if defined(CONFIG_TARGET_HI3516EV300)
#define HIETH_SYSCTL_REG        (SYS_CTRL_REG_BASE + MISC_CTRL9)
#define ETH_INTERNAL_PHY_RESET  bit(3)
#define ETH_INTERNAL_PHY_CLK_EN bit(2)
#endif

#if defined(CONFIG_TARGET_HI3518EV300)
#define HIETH_SYSCTL_REG        (SYS_CTRL_REG_BASE + MISC_CTRL9)
#define ETH_INTERNAL_PHY_RESET  bit(3)
#define ETH_INTERNAL_PHY_CLK_EN bit(2)
#endif

#if defined(CONFIG_TARGET_HI3516DV200)
#define HIETH_SYSCTL_REG        (SYS_CTRL_REG_BASE + MISC_CTRL9)
#define ETH_INTERNAL_PHY_RESET  bit(3)
#define ETH_INTERNAL_PHY_CLK_EN bit(2)
#endif

#if defined(CONFIG_HI3536DV100)
static unsigned char hieth_use_fephy(void)
{
	return !(readl(HIETH_SYSCTL_REG) & BIT_FEPHY_SEL);
}
#endif

#if defined(INNER_PHY) && defined(CONFIG_HI3520D)
void set_efuse_unread(void)
{
	u32 reg_value;

	reg_value = readl(HIETH_EFUSE_REG);
	reg_value |= 0x1;
	writel(reg_value, HIETH_EFUSE_REG);

	reg_value = readl(HIETH_EFUSE_DATA_REG);
	reg_value |= 0x1;
	writel(reg_value, HIETH_EFUSE_DATA_REG);

	mdelay(300); /* delay 300ms */

	reg_value = readl(HIETH_EFUSE_REG);
	reg_value &= ~0x1;
	writel(reg_value, HIETH_EFUSE_REG);
}
#else
void set_efuse_unread(void)
{
}
#endif

#ifdef INNER_PHY
void set_inner_phy_addr(u32 phy_addr)
{
	u32 reg_value;

#if defined(CONFIG_HI3536DV100)
	if (!hieth_use_fephy())
		phy_addr += 1;
#endif
	reg_value = readl(HIETH_SYSCTL_REG);
	reg_value &= ~0x1f;
	phy_addr &= 0x1f;
	reg_value |= phy_addr;
	writel(reg_value, HIETH_SYSCTL_REG);
}
#else
void set_inner_phy_addr(u32 phyaddr)
{
}
#endif

#if defined(INNER_PHY) && defined(CONFIG_HI3520D)
void revise_led_shine(void)
{
#define MDIO_RWCTRL      0x1100
#define tmp_mdio_ready() \
	(readl(REG_BASE_SF + MDIO_RWCTRL) & bit(15))

	unsigned int reg_value;
	/* select page 7 */
	do {
		reg_value = 0x0007235f;
		writel(reg_value, REG_BASE_SF + MDIO_RWCTRL);
		udelay(10); /* delay 10us */
	} while (!tmp_mdio_ready());

	/* enable LED modify function */
	do {
		reg_value = 0xc03c2353;
		writel(reg_value, REG_BASE_SF + MDIO_RWCTRL);
		udelay(10); /* delay 10us */
	} while (!tmp_mdio_ready());

	/* set green LED shine all the while when link up,
	 * yellow LED blink when data coming
	 */
	do {
		reg_value = 0x00382351;
		writel(reg_value, REG_BASE_SF + MDIO_RWCTRL);
		udelay(10); /* delay 10us */
	} while (!tmp_mdio_ready());

	return;
}
#else
void revise_led_shine(void)
{
}
#endif

#if defined(INNER_PHY) && defined(CONFIG_HI3520D)
void set_phy_valtage(void)
{
#define MDIO_RWCTRL      0x1100
#define tmp_mdio_ready() \
	(readl(REG_BASE_SF + MDIO_RWCTRL) & bit(15))

	unsigned int reg_value;
	/* select page 1 */
	do {
		reg_value = 0x0001235f;
		writel(reg_value, REG_BASE_SF + MDIO_RWCTRL);
		udelay(10); /* delay 10us */
	} while (!tmp_mdio_ready());

	/* set fe-phy in lower valtage */
	do {
		reg_value = 0x94482352;
		writel(reg_value, REG_BASE_SF + MDIO_RWCTRL);
		udelay(10); /* delay 10us */
	} while (!tmp_mdio_ready());

	/* select page 0 */
	do {
		reg_value = 0x0000235f;
		writel(reg_value, REG_BASE_SF + MDIO_RWCTRL);
		udelay(10); /* delay 10us */
	} while (!tmp_mdio_ready());
}
#else
void set_phy_valtage(void)
{
}
#endif

static void hieth_reset(int rst)
{
	u32 val;

	val = _readl(HIETH_CRG_REG);
	if (rst) {
		val |= ETH_SOFT_RESET;
	} else {
		val &= ~ETH_SOFT_RESET;
	}
	_writel(val, HIETH_CRG_REG);

	udelay(100); /* delay 100us */
}

static inline void hieth_clk_ena(void)
{
	u32 val = _readl(HIETH_CRG_REG);
	val |= (ETH_CORE_CLK_SELECT_54M | ETH_CLK_ENABLE);
	_writel(val, HIETH_CRG_REG);
}

static inline void hieth_clk_dis(void)
{
	u32 val = _readl(HIETH_CRG_REG);
	val &= ~ETH_CLK_ENABLE;
	_writel(val, HIETH_CRG_REG);
}

#if defined(CONFIG_HI3536DV100) || defined(INNER_PHY)
static void hieth_fephy_trim(void)
{
	/* To simplify internal FEPHY trim process,
	 * we just delay 300ms to wait FEPHY auto-trim completed.
	 * Not read trim data from EFUSE register.
	 */
	mdelay(350); /* delay 350ms */
}
#endif

#if defined(CONFIG_HI3536DV100)
void hieth_set_crg_phy_mode(unsigned char is_rmii_mode)
{
	u32 val;

	val = readl(HIETH_CRG_REG);
	if (is_rmii_mode) {
		val |= BIT_PHY_RMII_MODE;
	} else {
		val &= ~BIT_PHY_RMII_MODE;
	}
	writel(val, HIETH_CRG_REG);
}
#endif

static void hieth_reset_internal_phy(void)
{
#ifdef INNER_PHY
	u32 rst;

#if defined(CONFIG_HI3536DV100)
	if (!hieth_use_fephy()) {
		return;
	}
#endif
	/* disable MDCK clock to make sure FEPHY reset success */
	hieth_clk_dis();

	rst = readl(HIETH_CRG_INPHY_CLK_REG);
	rst |= ETH_INTERNAL_PHY_CLK_EN;
	/* internal FEPHY only support MII mode */
#if defined(CONFIG_HI3536DV100)
	rst &= ~BIT_PHY_RMII_MODE;
#endif
	writel(rst, HIETH_CRG_INPHY_CLK_REG);
	udelay(10); /* delay 10us */

	rst = _readl(HIETH_CRG_INPHY_CLK_REG);
	rst |= ETH_INTERNAL_PHY_RESET;
	_writel(rst, HIETH_CRG_INPHY_CLK_REG);
	/* delay at least 10ms */
	mdelay(15); /* delay 15ms */

	rst = _readl(HIETH_CRG_INPHY_CLK_REG);
	rst &= ~ETH_INTERNAL_PHY_RESET;
	_writel(rst, HIETH_CRG_INPHY_CLK_REG);
	/* delay at least 15ms for MDIO operation */
	mdelay(20); /* delay 20ms */

	hieth_clk_ena();
	/* delay 5ms after enable MDCK to make sure FEPHY trim safe */
	mdelay(5); /* delay 5ms */
	hieth_fephy_trim();
#endif
}

static void hieth_reset_external_phy_by_crg(void)
{
#if defined(HISFV_RESET_PHY_BY_CRG)
	u32 v;

	/************************************************/
	/* reset external phy with default reset pin */
	v = readl(HIETH_CRG_EXTPHY_CLK_REG);
	v |= ETH_EXTERNAL_PHY_RESET;
	writel(v, HIETH_CRG_EXTPHY_CLK_REG);

	mdelay(50); /* delay 50ms */

	/* then, cancel reset, and should delay some time */
	v = readl(HIETH_CRG_EXTPHY_CLK_REG);
	v &= ~ETH_EXTERNAL_PHY_RESET;
	writel(v, HIETH_CRG_EXTPHY_CLK_REG);

	mdelay(50); /* delay 50ms */
#endif
}

static void hieth_reset_external_phy_by_gpio(void)
{
#ifdef HISFV_RESET_GPIO_EN
	unsigned int val;
	/* gpiox[x] set to reset, then delay 200ms */
	val = __raw_readw(HISFV_RESET_GPIO_BASE + HISFV_RESET_GPIO_DIR);
	val |= (HISFV_RESET_GPIO_DIR_OUT << HISFV_RESET_GPIO_BIT);
	__raw_writew(val, HISFV_RESET_GPIO_BASE + HISFV_RESET_GPIO_DIR);
	__raw_writew(HISFV_RESET_GPIO_DATA,
				 HISFV_RESET_GPIO_BASE +
				 (4 << HISFV_RESET_GPIO_BIT)); /* offset addr 4 */

	mdelay(200); /* delay 200ms */

	/* then,cancel reset,and should delay 200ms */
	val = __raw_readw(HISFV_RESET_GPIO_BASE + HISFV_RESET_GPIO_DIR);
	val |= (HISFV_RESET_GPIO_DIR_OUT << HISFV_RESET_GPIO_BIT);
	__raw_writew(val, HISFV_RESET_GPIO_BASE + HISFV_RESET_GPIO_DIR);
	__raw_writew(((!HISFV_RESET_GPIO_DATA) << HISFV_RESET_GPIO_BIT),
				 HISFV_RESET_GPIO_BASE +
				 (4 << HISFV_RESET_GPIO_BIT)); /* offset addr 4 */

	mdelay(20); /* delay 20ms */
#endif
}

static void hieth_phy_reset(void)
{
	hieth_reset_internal_phy();
	hieth_reset_external_phy_by_crg();
	hieth_reset_external_phy_by_gpio();
}

static void hieth_funsel_config(void)
{
}

static void hieth_funsel_restore(void)
{
}

/**************************************************/
void hieth_sys_startup(void)
{
	hieth_clk_ena();
	/* undo reset */
	hieth_reset(0);
}

void hieth_sys_allstop(void)
{
}

void hieth_sys_init(void)
{
	hieth_funsel_config();
	hieth_sys_allstop();
	hieth_clk_ena();
	hieth_reset(1);
	hieth_reset(0);
	hieth_phy_reset();
	revise_led_shine();
}

void hieth_sys_exit(void)
{
	hieth_funsel_restore();
	hieth_sys_allstop();
}
