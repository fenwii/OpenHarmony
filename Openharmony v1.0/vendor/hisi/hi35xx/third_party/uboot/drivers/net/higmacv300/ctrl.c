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
 * Description: Control higmac register
 */

#include "util.h"
#include "higmac.h"
#include "ctrl.h"

#if defined(CONFIG_TARGET_HI3531DV200) || defined(CONFIG_TARGET_HI3535AV100)
void higmac_set_macif(struct higmac_netdev_local *ld, int mode, unsigned int speed)
{
	void __iomem *p = (void __iomem *)CRG_REG_BASE;
	unsigned long v;

	/* enable change: port_mode */
	higmac_writel_bits(ld, 1, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);
	if (speed == SPEED_MODE_1000M)
		speed = 5; /* regval is 5 for 1000M */
	higmac_writel_bits(ld, speed, PORT_MODE, BITS_PORT_MODE);
	/* disable change: port_mode */
	higmac_writel_bits(ld, 0, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);

	/* soft reset mac_if */
	if (ld->index) {
#if GMAC_AT_LEAST_2PORT
		v = readl(p + REG_ETH1_MACIF_CRG);
		v |= BIT_MACIF1_RST;
		writel(v, p + REG_ETH1_MACIF_CRG);
#endif
	} else {
		v = readl(p + REG_ETH0_MACIF_CRG);
		v |= BIT_MACIF0_RST;
		writel(v, p + REG_ETH0_MACIF_CRG);
	}

	/* config mac_if */
	if (ld->index) {
#if GMAC_AT_LEAST_2PORT
		writel(mode, HIGMAC_MACIF1_CTRL);
#endif
	} else {
		writel(mode, HIGMAC_MACIF0_CTRL);
	}

	if (ld->index) {
#if GMAC_AT_LEAST_2PORT
		v = readl(p + REG_ETH1_MACIF_CRG);
		v &= ~BIT_MACIF1_RST;
		writel(v, p + REG_ETH1_MACIF_CRG);
#endif
	} else {
		v = readl(p + REG_ETH0_MACIF_CRG);
		v &= ~BIT_MACIF0_RST;
		writel(v, p + REG_ETH0_MACIF_CRG);
	}
}
#else
void higmac_set_macif(struct higmac_netdev_local *ld, int mode, unsigned int speed)
{
	void __iomem *p = (void __iomem *)CRG_REG_BASE;
	unsigned long v;

	/* enable change: port_mode */
	higmac_writel_bits(ld, 1, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);
	if (speed == SPEED_MODE_1000M)
		speed = 5; /* regval is 5 for 1000M */
	higmac_writel_bits(ld, speed, PORT_MODE, BITS_PORT_MODE);
	/* disable change: port_mode */
	higmac_writel_bits(ld, 0, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);

	/* soft reset mac_if */
	v = readl(p + REG_ETH_CRG);
	if (ld->index) {
#if GMAC_AT_LEAST_2PORT
		v |= BIT_MACIF1_RST;
#endif
	} else {
		v |= BIT_MACIF0_RST;
	}
	writel(v, p + REG_ETH_CRG);

	/* config mac_if */
	if (ld->index) {
#if GMAC_AT_LEAST_2PORT
		writel(mode, HIGMAC_MACIF1_CTRL);
#endif
	} else {
		writel(mode, HIGMAC_MACIF0_CTRL);
	}

	v = readl(p + REG_ETH_CRG);
	if (ld->index) {
#if GMAC_AT_LEAST_2PORT
		v &= ~BIT_MACIF1_RST;
#endif
	} else {
		v &= ~BIT_MACIF0_RST;
	}
	writel(v, p + REG_ETH_CRG);
}
#endif

int higmac_hw_set_macaddress(struct higmac_netdev_local *ld, const unsigned char *mac,
		  int len)
{
	unsigned long reg;

	if (len < MAC_LEN)
		return -1;

	reg = mac[1] | (mac[0] << 8); /* mac 0 [8:15], mac 1 [0:7] */
	higmac_writel(ld, reg, STATION_ADDR_HIGH);
	/* mac 2 [24:31], mac 3 [16:23], mac 4 [8:15], mac 5 [0:7] */
	reg = mac[5] | (mac[4] << 8) | (mac[3] << 16) | (mac[2] << 24);
	higmac_writel(ld, reg, STATION_ADDR_LOW);

	return 0;
}

int higmac_hw_get_macaddress(struct higmac_netdev_local *ld, unsigned char *mac,
		  int len)
{
	unsigned long reg;

	if (len < MAC_LEN)
		return -1;

	reg = higmac_readl(ld, STATION_ADDR_HIGH);
	mac[0] = (reg >> 8) & 0xff; /* mac[0] [8:15] bit */
	mac[1] = reg & 0xff; /* mac[1] [0:7] bit */

	reg = higmac_readl(ld, STATION_ADDR_LOW);
	mac[2] = (reg >> 24) & 0xff; /* mac[2] [24:31] bit */
	mac[3] = (reg >> 16) & 0xff; /* mac[3] [16:23] bit */
	mac[4] = (reg >> 8) & 0xff; /* mac[4] [8:15] bit */
	mac[5] = reg & 0xff; /* mac[5] [0:7] bit */      

	return 0;
}

static inline int _higmac_read_irqstatus(struct higmac_netdev_local *ld)
{
	int status;

	status = higmac_readl(ld, STATUS_PMU_INT);

	return status;
}

int higmac_clear_irqstatus(struct higmac_netdev_local *ld, int irqs)
{
	int status;

	higmac_writel(ld, irqs, RAW_PMU_INT);
	status = _higmac_read_irqstatus(ld);

	return status;
}

int higmac_glb_preinit_dummy(struct higmac_netdev_local *ld)
{
	/* drop packet enable */
	higmac_writel(ld, 0x3F, REC_FILT_CONTROL);
	higmac_writel_bits(ld, 0, REC_FILT_CONTROL, BIT_BC_DROP_EN);

	/* clear all interrupt status */
	higmac_clear_irqstatus(ld, RAW_INT_ALL_MASK);

	/* disable interrupts */
	higmac_writel(ld, ~RAW_INT_ALL_MASK, ENA_PMU_INT);

	return 0;
}

#if defined(CONFIG_TARGET_HI3531DV200) || defined(CONFIG_TARGET_HI3535AV100)
void higmac_external_phy_reset(void)
{
	unsigned int v;

#ifdef	HIGAMC_USE_GPIO_RESET_PHY
	/* use GPIO0_1 to reset external phy */
	/* Set Direction output */
	v = readl(HIGMAC_RESET_GPIO_BASE + HIGMAC_RESET_GPIO_DIR_OFS);
	v |= HIGMAC_RESET_GPIO_DIR_OUT;
	writel(v, HIGMAC_RESET_GPIO_BASE + HIGMAC_RESET_GPIO_DIR_OFS);

	/* Set GPIO0_1 to 1 */
	writel(HIGMAC_RESET_GPIO_VALUE, HIGMAC_RESET_GPIO_BASE
			+ HIGMAC_RESET_GPIO_DATA_OFS);
	udelay(50000); /* wait 50000us */
	/* Set GPIO0_1=0 to reset phy */
	writel(~HIGMAC_RESET_GPIO_VALUE, HIGMAC_RESET_GPIO_BASE
			+ HIGMAC_RESET_GPIO_DATA_OFS);
	udelay(200000); /* wait 200000us */

	/* Set GPIO0_1=1 to cancel reset phy */
	writel(HIGMAC_RESET_GPIO_VALUE, HIGMAC_RESET_GPIO_BASE
			+ HIGMAC_RESET_GPIO_DATA_OFS);
	udelay(50000); /* wait 50000us */
#else
	/* use CRG register to reset external phy */
	v = readl(CRG_REG_BASE + REG_ETH0_PHY_CRG);
	v |= BIT_EXT_PHY0_RST; /* reset */
	writel(v, CRG_REG_BASE + REG_ETH0_PHY_CRG);
#if GMAC_AT_LEAST_2PORT
	v = readl(CRG_REG_BASE + REG_ETH1_PHY_CRG);
	v |= BIT_EXT_PHY1_RST;
	writel(v, CRG_REG_BASE + REG_ETH1_PHY_CRG);
#endif

	udelay(50 * 1000); /* wait 50 * 1000us for phy reset time */

	v = readl(CRG_REG_BASE + REG_ETH0_PHY_CRG);
	v &= ~BIT_EXT_PHY0_RST; /* undo reset */
	writel(v, CRG_REG_BASE + REG_ETH0_PHY_CRG);
#if GMAC_AT_LEAST_2PORT
	v = readl(CRG_REG_BASE + REG_ETH1_PHY_CRG);
	v &= ~BIT_EXT_PHY1_RST;
	writel(v, CRG_REG_BASE + REG_ETH1_PHY_CRG);
#endif

	udelay(60 * 1000); /* wait 60 * 1000us for future MDIO operation */
#endif
}

void higmac_init_phy(void)
{
	uintptr_t p;
	volatile unsigned int v;

	p = (unsigned long)(CRG_REG_BASE);

	v = readl(p + REG_ETH0_PHY_CRG);

	/* phy clk select 25MHz */
	v &= ~BIT_EXT_PHY0_CLK_SELECT;
	v |= PHY0_CLK_25M;
	writel(v, p + REG_ETH0_PHY_CRG);
#if GMAC_AT_LEAST_2PORT
	v = readl(p + REG_ETH1_PHY_CRG);
	v &= ~BIT_EXT_PHY1_CLK_SELECT;
	v |= PHY1_CLK_25M;
	writel(v, p + REG_ETH1_PHY_CRG);
#endif	
}

void higmac_soft_reset_eth(void)
{
	uintptr_t p;
	volatile unsigned int v;

	p = (unsigned long)(CRG_REG_BASE);
	
	/* soft reset */
	v = readl(p + REG_ETH0_GSF_CRG);
	v |= BIT_GMAC0_RST;
	writel(v, p + REG_ETH0_GSF_CRG);
#if GMAC_AT_LEAST_2PORT
	v = readl(p + REG_ETH1_GSF_CRG);
	v |= BIT_GMAC1_RST;
	writel(v, p + REG_ETH1_GSF_CRG);
#endif

	udelay(100); /* wait 100us */

	v = readl(p + REG_ETH0_GSF_CRG);
	v &= ~BIT_GMAC0_RST;
	writel(v, p + REG_ETH0_GSF_CRG);
#if GMAC_AT_LEAST_2PORT
	v = readl(p + REG_ETH1_GSF_CRG);
	v &= ~BIT_GMAC1_RST;
	writel(v, p + REG_ETH1_GSF_CRG);
#endif
}


void higmac_sys_init(void)
{
	uintptr_t p;
	volatile unsigned int v;

	p = (unsigned long)(CRG_REG_BASE);

	higmac_init_phy();

	/* enable clk */
	v = readl(p + REG_ETH0_GSF_CRG);
	v |= BIT_GMAC0_CLK_EN;
	writel(v, p + REG_ETH0_GSF_CRG);

	v = readl(p + REG_ETH0_MACIF_CRG);
	v |= BIT_GMACIF0_CLK_EN;
	writel(v, p + REG_ETH0_MACIF_CRG);

#if GMAC_AT_LEAST_2PORT
	v = readl(p + REG_ETH1_GSF_CRG);
	v |= BIT_GMAC1_CLK_EN;
	writel(v, p + REG_ETH1_GSF_CRG);

	v = readl(p + REG_ETH1_MACIF_CRG);
	v |= BIT_GMACIF1_CLK_EN;
	writel(v, p + REG_ETH1_MACIF_CRG);
#endif

#ifdef CONFIG_HIGMAC_RMII0_CLK_USE_EXTERNAL_PAD
	v = readl(p + REG_ETH0_MACIF_CRG);
	if (higmac_board_info[0].phy_intf == INTERFACE_MODE_RMII)
		v |= BIT_RMII0_CLKSEL_PAD; /* rmii select pad clk */
	writel(v, p + REG_ETH0_MACIF_CRG);
#endif
#if GMAC_AT_LEAST_2PORT
#ifdef CONFIG_HIGMAC_RMII1_CLK_USE_EXTERNAL_PAD
	v = readl(p + REG_ETH1_MACIF_CRG);
	if (higmac_board_info[1].phy_intf == INTERFACE_MODE_RMII)
		v |= BIT_RMII1_CLKSEL_PAD; /* rmii select pad clk */
	writel(v, p + REG_ETH1_MACIF_CRG);
#endif
#endif

	higmac_soft_reset_eth();

	writel(0xe, HIGMAC_DUAL_MAC_CRF_ACK_TH);

	higmac_external_phy_reset();
}
#else
void higmac_external_phy_reset(void)
{
	unsigned int v;

#ifdef HIGAMC_USE_GPIO_RESET_PHY
	/* use GPIO0_1 to reset external phy */
	/* Set Direction output */
	v = readl(HIGMAC_RESET_GPIO_BASE + HIGMAC_RESET_GPIO_DIR_OFS);
	v |= HIGMAC_RESET_GPIO_DIR_OUT;
	writel(v, HIGMAC_RESET_GPIO_BASE + HIGMAC_RESET_GPIO_DIR_OFS);

	/* Set GPIO0_1 value 1 */
	writel(HIGMAC_RESET_GPIO_VALUE, HIGMAC_RESET_GPIO_BASE
			+ HIGMAC_RESET_GPIO_DATA_OFS);
	udelay(50000); /* wait 50000us */
	/* Set GPIO0_1=0 to reset phy */
	writel(~HIGMAC_RESET_GPIO_VALUE, HIGMAC_RESET_GPIO_BASE
			+ HIGMAC_RESET_GPIO_DATA_OFS);
	udelay(200000); /* wait 200000us */

	/* Set GPIO0_1=1 to cancel reset phy */
	writel(HIGMAC_RESET_GPIO_VALUE, HIGMAC_RESET_GPIO_BASE
			+ HIGMAC_RESET_GPIO_DATA_OFS);
	udelay(50000); /* wait 50000us */
#else
	/* use CRG register to reset external phy */
	v = readl(CRG_REG_BASE + REG_ETH_CRG);
	v |= BIT_EXT_PHY0_RST; /* reset */
#if GMAC_AT_LEAST_2PORT
	v |= BIT_EXT_PHY1_RST;
#endif
	writel(v, CRG_REG_BASE + REG_ETH_CRG);

	udelay(50 * 1000); /* wait 50 * 1000us for phy reset time */

	v = readl(CRG_REG_BASE + REG_ETH_CRG);
	v &= ~BIT_EXT_PHY0_RST; /* undo reset */
#if GMAC_AT_LEAST_2PORT
	v &= ~BIT_EXT_PHY1_RST;
#endif
	writel(v, CRG_REG_BASE + REG_ETH_CRG);

	udelay(60 * 1000); /* wait 60 * 1000us for future MDIO operation */
#endif
}

void higmac_sys_init(void)
{
	unsigned long p;
	volatile unsigned int v;

	p = (unsigned long)(CRG_REG_BASE);

	v = readl((uintptr_t)(p + REG_ETH_CRG));

	/* phy clk select 25MHz */
	v &= ~BIT_EXT_PHY0_CLK_SELECT;
	v |= PHY0_CLK_25M;
#if GMAC_AT_LEAST_2PORT
	v &= ~BIT_EXT_PHY1_CLK_SELECT;
	v |= PHY1_CLK_25M;
#endif
	/* enable clk */
	v |= (BIT_GMAC0_CLK_EN | BIT_GMACIF0_CLK_EN);
#if GMAC_AT_LEAST_2PORT
	v |= BIT_GSF_PUB_CLK_EN;
	v |= (BIT_GMAC1_CLK_EN | BIT_GMACIF1_CLK_EN);
#endif

#ifdef CONFIG_HIGMAC_RMII0_CLK_USE_EXTERNAL_PAD
	if (higmac_board_info[0].phy_intf == INTERFACE_MODE_RMII)
		v |= BIT_RMII0_CLKSEL_PAD; /* rmii select pad clk */

#endif
#if GMAC_AT_LEAST_2PORT
#ifdef CONFIG_HIGMAC_RMII1_CLK_USE_EXTERNAL_PAD
	if (higmac_board_info[1].phy_intf == INTERFACE_MODE_RMII)
		v |= BIT_RMII1_CLKSEL_PAD; /* rmii select pad clk */
#endif
#endif

	writel(v, (uintptr_t)(p + REG_ETH_CRG));

	/* soft reset */
	v = readl((uintptr_t)(p + REG_ETH_CRG));
	v |= BIT_GMAC0_RST;
#if GMAC_AT_LEAST_2PORT
	v |= BIT_GMAC1_RST;
#endif
	writel(v, (uintptr_t)(p + REG_ETH_CRG));

	udelay(100); /* delay 100us */

	v = readl((uintptr_t)(p + REG_ETH_CRG));
	v &= ~BIT_GMAC0_RST;
#if GMAC_AT_LEAST_2PORT
	v &= ~BIT_GMAC1_RST;
#endif
	writel(v, (uintptr_t)(p + REG_ETH_CRG));

	writel(0xe, HIGMAC_DUAL_MAC_CRF_ACK_TH);

	higmac_external_phy_reset();
}
#endif

void higmac_sys_exit(void)
{
}

void higmac_sys_allstop(void)
{
}

int higmac_set_hwq_depth(struct higmac_netdev_local *ld)
{
	if (HIGMAC_HWQ_RX_FQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH) {
		BUG();
		return -1;
	}

	higmac_writel_bits(ld, 1, RX_FQ_REG_EN, \
		BITS_RX_FQ_DEPTH_EN);

	higmac_writel_bits(ld, HIGMAC_HWQ_RX_FQ_DEPTH << DESC_WORD_SHIFT,
		RX_FQ_DEPTH, BITS_RX_FQ_DEPTH);

	higmac_writel_bits(ld, 0, RX_FQ_REG_EN, \
		BITS_RX_FQ_DEPTH_EN);

	if (HIGMAC_HWQ_RX_BQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH) {
		BUG();
		return -1;
	}

	higmac_writel_bits(ld, 1, RX_BQ_REG_EN, \
		BITS_RX_BQ_DEPTH_EN);

	higmac_writel_bits(ld, HIGMAC_HWQ_RX_BQ_DEPTH << DESC_WORD_SHIFT,
		RX_BQ_DEPTH, BITS_RX_BQ_DEPTH);

	higmac_writel_bits(ld, 0, RX_BQ_REG_EN, \
		BITS_RX_BQ_DEPTH_EN);

	if (HIGMAC_HWQ_TX_BQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH) {
		BUG();
		return -1;
	}

	higmac_writel_bits(ld, 1, TX_BQ_REG_EN, \
		BITS_TX_BQ_DEPTH_EN);

	higmac_writel_bits(ld, HIGMAC_HWQ_TX_BQ_DEPTH << DESC_WORD_SHIFT,
		TX_BQ_DEPTH, BITS_TX_BQ_DEPTH);

	higmac_writel_bits(ld, 0, TX_BQ_REG_EN, \
		BITS_TX_BQ_DEPTH_EN);

	if (HIGMAC_HWQ_TX_RQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH) {
		BUG();
		return -1;
	}

	higmac_writel_bits(ld, 1, TX_RQ_REG_EN, \
		BITS_TX_RQ_DEPTH_EN);

	higmac_writel_bits(ld, HIGMAC_HWQ_TX_RQ_DEPTH << DESC_WORD_SHIFT,
		TX_RQ_DEPTH, BITS_TX_RQ_DEPTH);

	higmac_writel_bits(ld, 0, TX_RQ_REG_EN, \
		BITS_TX_RQ_DEPTH_EN);

	return 0;
}

int higmac_set_rx_fq_hwq_addr(struct higmac_netdev_local *ld,
		  phys_addr_t phy_addr)
{
	higmac_writel_bits(ld, 1, RX_FQ_REG_EN, \
		BITS_RX_FQ_START_ADDR_EN);

	higmac_writel(ld, (u32)phy_addr, RX_FQ_START_ADDR);
#if defined(CONFIG_64BIT)
	higmac_writel_bits(ld, (u32)((u64)phy_addr >> REG_BIT_WIDTH), RX_FQ_DEPTH,
		BITS_RX_FQ_ADDR_HI8);
#endif

	higmac_writel_bits(ld, 0, RX_FQ_REG_EN, \
		BITS_RX_FQ_START_ADDR_EN);

	return 0;
}

int higmac_set_rx_bq_hwq_addr(struct higmac_netdev_local *ld,
		  phys_addr_t phy_addr)
{
	higmac_writel_bits(ld, 1, RX_BQ_REG_EN, \
		BITS_RX_BQ_START_ADDR_EN);

	higmac_writel(ld, (u32)phy_addr, RX_BQ_START_ADDR);
#if defined(CONFIG_64BIT)
	higmac_writel_bits(ld, (u32)((u64)phy_addr >> REG_BIT_WIDTH), RX_BQ_DEPTH,
		BITS_RX_BQ_ADDR_HI8);
#endif

	higmac_writel_bits(ld, 0, RX_BQ_REG_EN, \
		BITS_RX_BQ_START_ADDR_EN);

	return 0;
}

int higmac_set_tx_bq_hwq_addr(struct higmac_netdev_local *ld,
		  phys_addr_t phy_addr)
{
	higmac_writel_bits(ld, 1, TX_BQ_REG_EN, \
		BITS_TX_BQ_START_ADDR_EN);

	higmac_writel(ld, (u32)phy_addr, TX_BQ_START_ADDR);
#if defined(CONFIG_64BIT)
	higmac_writel_bits(ld, (u32)((u64)phy_addr >> REG_BIT_WIDTH), TX_BQ_DEPTH,
		BITS_TX_BQ_ADDR_HI8);
#endif

	higmac_writel_bits(ld, 0, TX_BQ_REG_EN, \
		BITS_TX_BQ_START_ADDR_EN);

	return 0;
}

int higmac_set_tx_rq_hwq_addr(struct higmac_netdev_local *ld,
		  phys_addr_t phy_addr)
{
	higmac_writel_bits(ld, 1, TX_RQ_REG_EN, \
		BITS_TX_RQ_START_ADDR_EN);

	higmac_writel(ld, (u32)phy_addr, TX_RQ_START_ADDR);
#if defined(CONFIG_64BIT)
	higmac_writel_bits(ld, (u32)((u64)phy_addr >> REG_BIT_WIDTH), TX_RQ_DEPTH,
		BITS_TX_RQ_ADDR_HI8);
#endif

	higmac_writel_bits(ld, 0, TX_RQ_REG_EN, \
		BITS_TX_RQ_START_ADDR_EN);

	return 0;
}

void higmac_desc_enable(struct higmac_netdev_local *ld, u32 desc_ena)
{
	u32 old;

	old = higmac_readl(ld, DESC_WR_RD_ENA);
	higmac_writel(ld, old | desc_ena, DESC_WR_RD_ENA);
}

void higmac_desc_disable(struct higmac_netdev_local *ld, u32 desc_dis)
{
	u32 old;

	old = higmac_readl(ld, DESC_WR_RD_ENA);
	higmac_writel(ld, old & (~desc_dis), DESC_WR_RD_ENA);
}

void higmac_desc_flush(struct higmac_netdev_local *ld)
{
	higmac_writel_bits(ld, 1, STOP_CMD, BITS_TX_STOP_EN);
	while (higmac_readl_bits(ld, FLUSH_CMD, BITS_TX_FLUSH_FLAG) != 1);
	higmac_writel_bits(ld, 1, FLUSH_CMD, BITS_TX_FLUSH_CMD);
	while (higmac_readl_bits(ld, FLUSH_CMD, BITS_TX_FLUSH_FLAG) != 0);
	higmac_writel_bits(ld, 0, FLUSH_CMD, BITS_TX_FLUSH_CMD);
	higmac_writel_bits(ld, 0, STOP_CMD, BITS_TX_STOP_EN);

	higmac_writel_bits(ld, 1, STOP_CMD, BITS_RX_STOP_EN);
	while (higmac_readl_bits(ld, FLUSH_CMD, BITS_RX_FLUSH_FLAG) != 1);
	higmac_writel_bits(ld, 1, FLUSH_CMD, BITS_RX_FLUSH_CMD);
	while (higmac_readl_bits(ld, FLUSH_CMD, BITS_RX_FLUSH_FLAG) != 0);
	higmac_writel_bits(ld, 0, FLUSH_CMD, BITS_RX_FLUSH_CMD);
	higmac_writel_bits(ld, 0, STOP_CMD, BITS_RX_STOP_EN);
}

u32 higmac_readl(struct higmac_netdev_local *ld, u32 ofs)
{
	u32 reg = readl((uintptr_t)(ld->iobase + ofs));
	higmac_trace(HIGMAC_TRACE_ETH, "readl(0x%04X) = 0x%08X", ofs, reg);
	return reg;
}

void higmac_writel(struct higmac_netdev_local *ld, u32 v, u32 ofs)
{
	writel(v, (uintptr_t)(ld->iobase + ofs));
	higmac_trace(HIGMAC_TRACE_ETH, "writel(0x%04X) = 0x%08X", ofs, v);
}

u32 higmac_readl_bits(struct higmac_netdev_local *ld, u32 ofs, u32 bits_desc)
{
	u32 _bits_desc = bits_desc;
	u32 _shift = _bits_desc >> 16; /* shift 16 bit */
	u32 _mask = ((_bits_desc & 0x3F) < 32) ? /* 32bit register */
		(((1 << (_bits_desc & 0x3F)) - 1) << _shift) : 0xffffffff;
	u32 reg = (higmac_readl(ld, ofs) & _mask) >> _shift;
	return reg;
}

void higmac_writel_bits(struct higmac_netdev_local *ld, u32 v, u32 ofs, u32 bits_desc)
{
	u32 _bits_desc = bits_desc;
	u32 _shift = _bits_desc >> 16; /* shift 16 bit */
	u32 _reg = higmac_readl(ld, ofs);
	u32 _mask = ((_bits_desc & 0x3F) < 32) ? /* 32bit register */
		(((1 << (_bits_desc & 0x3F)) - 1) << _shift) : 0xffffffff;
	higmac_writel(ld, (_reg & (~_mask)) | ((v << _shift) & _mask), ofs);
}

void higmac_trace(int level, const char *fmt, ...)
{
	if (level >= HIGMAC_TRACE_LEVEL) {
		va_list args;
		va_start(args, fmt);
		printf("higmac_trace:");
		printf(fmt, args);
		printf("\n");
		va_end(args);
	}
}

void higmac_error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf("higmac:");
	printf(fmt, args);
	printf("\n");
	va_end(args);
}

void higmac_assert(bool cond)
{
	if (!cond)
		printf("Assert:higmac:%s:%d\n", __FILE__, __LINE__);
}
