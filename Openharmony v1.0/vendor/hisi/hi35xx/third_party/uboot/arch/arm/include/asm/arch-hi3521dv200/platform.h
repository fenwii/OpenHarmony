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
 */

#ifndef __HI_CHIP_REGS_H__
#define __HI_CHIP_REGS_H__

/* -------------------------------------------------------------------- */
/* Communication Register and flag used by bootrom */
/* -------------------------------------------------------------------- */
#define RAM_START_ADRS          		0x04010500
#define STACK_TRAINING		 	        0x0401A000
#define REG_START_FLAG      			(SYS_CTRL_REG_BASE + REG_SC_GEN1)
#define START_MAGIC				(0x444f574e)
#define SELF_BOOT_TYPE_USBDEV           	0x2
#define CP_STEP1_ADDR           		0x04010500


/* -------------------------------------------------------------------- */
/* System Control */
/* -------------------------------------------------------------------- */
#define SYS_CTRL_REG_BASE			0x11020000
#define REG_BASE_SCTL				SYS_CTRL_REG_BASE
#define REG_SC_CTRL				0x0000
#define REG_SC_SYSRES				0x0004
#define REG_PERISTAT				0x0030
#define REG_SYSSTAT				0x0018
#define EMMC_BOOT_8BIT				(0x1 << 11)
#define NF_BOOTBW_MASK				EMMC_BOOT_8BIT
#define BOOT_SEL_SHIFT				2
#define REG_PERI_EMMC_STAT			0x0404
#define mmc_boot_clk_sel(val)           	((val) & 0x3)
#define MMC_BOOT_CLK_50M                	0x2
#define EMMC_NORMAL_MODE			(0x1 << 3)
#define get_spi_nor_addr_mode(_reg)		(((_reg) >> 11) & 0x1)
#define get_spi_device_type(_reg)		(((_reg) >> 2) & 0x1)
#define get_sys_boot_mode(_reg)			(((_reg) >> 2) & 0x3)
#define BOOT_FROM_SPI				0
#define BOOT_FROM_SPI_NAND			1
#define BOOT_FROM_NAND				2
#define BOOT_FROM_EMMC				3

#define REG_SC_GEN0         0x0138
#define REG_SC_GEN1         0x013c
#define REG_SC_GEN2         0x0140
#define REG_SC_GEN3         0x0144
#define REG_SC_GEN4         0x0148
#define REG_SC_GEN9         0x0154


/* -------------------------------------------------------------------- */
/* CRG */
/* -------------------------------------------------------------------- */
#define CRG_REG_BASE			        0x11010000

/* -------------------------------------------------------------------- */
/* Peripheral Control REG */
/* -------------------------------------------------------------------- */
#define MISC_REG_BASE			        0x11024000


/* -------------------------------------------------------------------- */
/* IO configuration REG:mux and driver */
/* -------------------------------------------------------------------- */
#define AHB_IO_CONFIG_REG_BASE			0x102f0000
#define HP_IO_CONFIG_REG_BASE			0x10ff0000
#define IO_CONFIG_REG_BASE			AHB_IO_CONFIG_REG_BASE

/* -------------------------------------------------------------------- */
/* TIMER */
/* -------------------------------------------------------------------- */
#define TIMER0_REG_BASE			        0x11000000
#define REG_TIMER_RELOAD		        0x0
#define REG_TIMER_VALUE			        0x4
#define REG_TIMER_CONTROL		        0x8
#define CFG_TIMER_CLK                   	(3000000)
#define CFG_TIMERBASE                   	TIMER0_REG_BASE
/* enable timer.32bit, periodic,mask irq, 1 divider.*/
#define CFG_TIMER_CTRL                  	0xC2

/* -------------------------------------------------------------------- */
/* UART */
/* -------------------------------------------------------------------- */
#define UART0_REG_BASE			        0x11040000
#define UART1_REG_BASE			        0x11041000
#define UART2_REG_BASE			        0x11042000
#define UART3_REG_BASE			        0x11043000

/* -------------------------------------------------------------------- */
/* DDRC */
/* -------------------------------------------------------------------- */
#define DDRC0_REG_BASE			        0x11130000
#define DDR_MEM_BASE			        0x40000000

/* -------------------------------------------------------------------- */
/* FMC */
/* -------------------------------------------------------------------- */
#define FMC_REG_BASE			        0x10000000
#define FMC_MEM_BASE			        0x0f000000
#define FMC_TEXT_ADRS           		FMC_MEM_BASE

/* FMC CRG register offset */
#define REG_FMC_CRG				0x3f40

#define fmc_clk_sel(_clk)			(((_clk) & 0x7) << 12)
#define FMC_CLK_SEL_MASK			(0x7 << 12)
#define get_fmc_clk_type(_reg)			(((_reg) >> 12) & 0x7)

/* SDR/DDR clock */
#define FMC_CLK_24M				0
#define FMC_CLK_100M				1
#define FMC_CLK_150M				3
#define FMC_CLK_200M				4
#define FMC_CLK_257M				5
/* Only DDR clock */
#define FMC_CLK_300M				6
#define FMC_CLK_400M				7

#define FMC_CLK_ENABLE			        (0x1 << 4)
#define FMC_SOFT_RST_REQ		        (0x1 << 0)

/*--------------------------------------------------------------------- */
/* EMMC / SD */
/* -------------------------------------------------------------------- */
/* eMMC CRG register offset */
#define REG_EMMC_CRG				(CRG_REG_BASE + 0x34c0)
#define REG_SDIO0_CRG				REG_EMMC_CRG
#define mmc_clk_sel(_clk)			(((_clk) & 0x7) << 24)
#define MMC_CLK_SEL_MASK			(0x7 << 24)
#define REG_SAVE_HCS				0x11020300

#define EMMC_BASE_REG			        0x10020000
#define SDIO0_BASE_REG				EMMC_BASE_REG

/*--------------------------------------------------------------------- */
/* HIETH */
/* -------------------------------------------------------------------- */
#define REG_BASE_SF             0x102a0000
#define HIGMAC0_IOBASE          0x10290000
#define HIGMAC1_IOBASE          0x102A0000
/* Ethernet CRG register offset */
#define REG_ETH_CRG				0x37c8 /* PERI_CRG3572 */
#define REG_EXTFEPHY_CLK_RST	0x37cc
#define REG_INFEPHY_CLK_RST		0x37d0
#define REG_FEPHY_CTRL0			0x4218
#define REG_ETH0_CRG			REG_ETH_CRG


#define REG_ETH_MAC_IF			0x8c

/* Ethernet MAC CRG register bit map */
#define BIT_GSF_PUB_CLK_EN      0
#define BIT_GMAC0_RST           BIT(0)
#define BIT_GMAC0_CLK_EN        BIT(1)
#define BIT_GMAC1_RST           BIT(2)
#define BIT_GMAC1_CLK_EN        BIT(3)
#define BIT_MACIF0_RST          BIT(4)
#define BIT_GMACIF0_CLK_EN      BIT(5)
#define BIT_MACIF1_RST          BIT(6)
#define BIT_GMACIF1_CLK_EN      BIT(7)
#define BIT_RMII0_CLKSEL_PAD        BIT(8)
#define BIT_RMII1_CLKSEL_PAD        BIT(9)
#define BIT_EXT_PHY0_CLK_SELECT     BIT(12)
#define BIT_EXT_PHY1_CLK_SELECT     BIT(13)
#define BIT_EXT_PHY0_RST        BIT(14)
#define BIT_EXT_PHY1_RST        BIT(15)

#define PHY0_CLK_25M			0
#define PHY0_CLK_50M			BIT_EXT_PHY0_CLK_SELECT
#define PHY1_CLK_25M			0
#define PHY1_CLK_50M			BIT_EXT_PHY1_CLK_SELECT

#define HIGMAC_MACIF0_CTRL		(HIGMAC0_IOBASE + 0x300c)
#define HIGMAC_MACIF1_CTRL		(HIGMAC1_IOBASE + 0x300c)
#define HIGMAC_DUAL_MAC_CRF_ACK_TH	(HIGMAC0_IOBASE + 0x3004)

/* -------------------------------------------------------------------- */
/* USB */
/* -------------------------------------------------------------------- */
#define USB3_CTRL_REG_BASE		0x10300000
#define USB2_CTRL_REG_BASE		0x10340000
#define USB2_PHY2_BASE			0x10310000
#define USB2_PHY1_BASE			0x10350000
#define USB2_PHY0_BASE			0x10330000
#define USB_SYS_CTRL_BASE		0x11020444
#define USB_MISC_REG_BASE		0x110241c8

/* USB controller register offset and config */
#define GUSB2PHYCFG		0xc204
#define U2_FREECLK_EXISTS	(0x1 << 30)

/* USB CRG register offset and config */
#define	PERI_CRG3632		0x38c0
#define DEF_VAL_3632		0x10331
#define USB2_0_SRST_REQ     (0x1 << 0)
#define USB2_0_REF_CKEN     (0x1 << 5)
#define USB2_0_BUS_CKEN     (0x1 << 4)
#define USB2_0_UTMI_CKEN    (0x1 << 8)
#define USB2_2_UTMI_CKEN    (0x1 << 9)
#define USB2_0_FREECLK_CKSEL    (0x1 << 16)

#define	PERI_CRG3636		0x38d0
#define	DEF_VAL_3636		0x153
#define	USB2_PHY0_REQ		(0x1 << 0)
#define	USB2_PHY0_TREQ		(0x1 << 1)
#define	USB2_PHY0_APB_SRST_REQ	(0x1 << 2)
#define	USB2_PHY0_XTAL_CKEN	(0x1 << 4)

#define	PERI_CRG3640		0x38e0
#define	DEF_VAL_3640		0x10131
#define	USB2_1_SRST_REQ		(0x1 << 0)
#define	USB2_1_BUS_CKEN		(0x1 << 4)
#define	USB2_1_REF_CKEN		(0x1 << 5)
#define	USB2_1_UTMI_CKEN	(0x1 << 8)

#define	PERI_CRG3644		0x38f0
#define	DEF_VAL_3644		0x153
#define	USB2_PHY1_REQ		(0x1 << 0)
#define	USB2_PHY1_TREQ		(0x1 << 1)
#define	USB2_PHY1_APB_SRST_REQ	(0x1 << 2)
#define	USB2_PHY1_XTAL_CKEN	(0x1 << 4)

#define	PERI_CRG3672		0x3960
#define	DEF_VAL_3672		0x153
#define	USB2_PHY2_REQ		(0x1 << 0)
#define	USB2_PHY2_TREQ		(0x1 << 1)
#define	USB2_PHY2_APB_SRST_REQ	(0x1 << 2)
#define	USB2_PHY2_XTAL_CKEN	(0x1 << 4)

#define USB2_CTRL0_CFG		(CRG_REG_BASE + PERI_CRG3632)
#define USB2_PHY0_CFG		(CRG_REG_BASE + PERI_CRG3636)
#define USB2_CTRL1_CFG		(CRG_REG_BASE + PERI_CRG3640)
#define USB2_PHY1_CFG		(CRG_REG_BASE + PERI_CRG3644)
#define USB2_PHY2_CFG		(CRG_REG_BASE + PERI_CRG3672)

/* USB PHY register offset and config */
#define PHY_PLL_OFFSET		0x0014
#define	PHY_PLL_ENABLE		(0x3 << 0)

#define	RG_HSTX_MBIAS		0x0
#define	RG_HSTX_MBIAS_MASK	(0xf << 0)
#define	RG_HSTX_MBIAS_VAL	(0xb << 0)

#define	TX_TEST_BIT			0x8
#define	TX_TEST_BIT_VAL		(0x1 << 20)

#define	DISC_REF_VOL_SEL	0x8
#define	DISC_REF_VOL_SEL_MASK	(0x7 << 16)
#define	DISC_REF_VOL_SEL_VAL	(0x5 << 16)

#define	SLEW_RATE_OPTION	0xc
#define	SLEW_RATE_OPTION_MASK	(0x3 << 20)
#define	SLEW_RATE_OPTION_VAL	(0x1 << 20)

#define	TX_REF_VOL_SEL		0x10
#define	TX_REF_VOL_SEL_MASK	(0x7 << 4)
#define	TX_REF_VOL_SEL_VAL	(0x6 << 4)

#define	RG_FL_EDGE_MODE		0x10
#define	RG_FL_EDGE_MODE_VAL	(0x1 << 13)

#define U2_ANA_CFG2		0x8

#define U2_TRIM_VAL_MIN	0x09
#define U2_TRIM_VAL_MAX	0x1d
#define RT_TRIM_VAL_MASK	0x1f
#define usb2_2_trim_val(p)	(((p) >> 10) & RT_TRIM_VAL_MASK)
#define usb2_1_trim_val(p)	(((p) >> 5) & RT_TRIM_VAL_MASK)
#define usb2_0_trim_val(p)	(((p) >> 0) & RT_TRIM_VAL_MASK)

#define usb2_rt_trim_clr(p)	((p) & (~(RT_TRIM_VAL_MASK << 8)))
#define usb2_rt_trim_set(p)	((p) << 8)

/* -------------------------------------------------------------------- */
/* SYSCNT */
/* -------------------------------------------------------------------- */
#define SYSCNT_REG_BASE     	0x11050000
#define SYSCNT_ENABLE_REG       0x0
#define SYSCNT_FREQ_REG         0x20
#define SYSCNT_FREQ         	50000000

#define REG_BASE_SYSCNT SYSCNT_REG_BASE
#define CNTCR 0x0
#define CNTFID0 0x20

#endif /* End of __HI_CHIP_REGS_H__ */

