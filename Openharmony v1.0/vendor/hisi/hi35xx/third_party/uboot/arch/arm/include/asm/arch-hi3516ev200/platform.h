/*
 * platform.h
 *
 * Register and variable declaration of the chip.
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

#ifndef __HI_CHIP_REGS_H__
#define __HI_CHIP_REGS_H__

#define _HI3516E_V200           0x003516e200LL
#define _HI3516EV200_MASK       0xFFFFFFFFFFLL

/* -------------------------------------------------------------------- */
#define RAM_START_ADRS          0x04010500
#define STACK_TRAINING          0x0401A000

/* -------------------------------------------------------------------- */
#define FMC_REG_BASE            0x10000000

/* -------------------------------------------------------------------- */
#define REG_BASE_SF             0x10040000

/* -------------------------------------------------------------------- */
#define EMMC_REG_BASE           0x10010000
#define SDIO1_REG_BASE          0x10020000

/* -------------------------------------------------------------------- */
#define USB3_CTRL_REG_BASE      0x10030000

/* -------------------------------------------------------------------- */
#define HIUSB_OHCI_BASE         0x10030000

/* -------------------------------------------------------------------- */
#define DDRC0_REG_BASE          0x11330000

/* -------------------------------------------------------------------- */
#define TIMER0_REG_BASE         0x12000000
#define TIMER1_REG_BASE         0x12000020
#define TIMER2_REG_BASE         0x12001000
#define TIMER3_REG_BASE         0x12001020

#define REG_TIMER_RELOAD        0x0
#define REG_TIMER_VALUE         0x4
#define REG_TIMER_CONTROL       0x8

#define CFG_TIMER_CLK           3000000
#define CFG_TIMERBASE           TIMER0_REG_BASE

/* enable timer.32bit, periodic,mask irq, 1 divider. */
#define CFG_TIMER_CTRL          0xC2

/* -------------------------------------------------------------------- */
/* Clock and Reset Generator REG */
/* -------------------------------------------------------------------- */
#define CRG_REG_BASE            0x12010000

#define REG_CRG80           0x0140
#define REG_CRG81           0x0144
#define REG_CRG91           0x016c
#define REG_CRG110          0x01b8

/* USB 2.0 CRG Control register offset */
#define REG_USB2_CTRL       REG_CRG80

/* FMC CRG register offset */
#define REG_FMC_CRG         REG_CRG81
#define FMC_SRST            (0x1 << 0)
#define FMC_CLK_ENABLE      (0x1 << 1)
#define FMC_CLK_SEL_MASK    (0x7 << 2)
#define FMC_CLK_SEL_SHIFT   0x2
/* SDR/DDR clock */
#define FMC_CLK_24M         0x0
#define FMC_CLK_100M        0x1
#define FMC_CLK_150M        0x2

#define FMC_CLK_200M        0x3

/* Only DDR clock */
#define FMC_CLK_300M        0x4
#define FMC_CLK_360M        0x5

#define fmc_clk_sel(_clk) \
	(((_clk) << FMC_CLK_SEL_SHIFT) & FMC_CLK_SEL_MASK)
#define get_fmc_clk_type(_reg) \
	(((_reg) & FMC_CLK_SEL_MASK) >> FMC_CLK_SEL_SHIFT)

/* Ethernet CRG register offset */
#define REG_ETH_CRG         REG_CRG91
#define REG_ETH_MAC_IF      0x8c

/* Uart CRG register offset */
#define REG_UART_CRG            REG_CRG110
#define uart_clk_sel(_clk)      (((_clk) & 0x3) << 18)
#define UART_CLK_SEL_MASK       (0x3 << 18)
#define UART_CLK_APB            0
#define UART_CLK_24M            1
#define UART_CLK_2M         2

/* SDIO0 CRG register offset */
#define REG_SDIO0_CRG           (CRG_REG_BASE + 0x238)

/* eMMC CRG register offset */
#define REG_EMMC_CRG            (CRG_REG_BASE + 0x1f4)
#define mmc_clk_sel(_clk)       (((_clk) & 0x7) << 24)
#define MMC_CLK_SEL_MASK        (0x7 << 24)
#define get_mmc_clk_type(_reg)      (((_reg) >> 24) & 0x7)

/* -------------------------------------------------------------------- */
/* System Control REG */
/* -------------------------------------------------------------------- */
#define SYS_CTRL_REG_BASE       0x12020000
#define REG_BASE_SCTL           SYS_CTRL_REG_BASE
#define REG_SC_SYSSTAT          0x8c
#define spi_input_sle(x)        (((x) >> 16) & 0x1)

/* System Control register offset */
#define REG_SC_CTRL         0x0000
#define sc_ctrl_timer0_clk_sel(_clk)    (((_clk) & 0x1) << 16)
#define TIMER0_CLK_SEL_MASK     (0x1 << 16)
#define TIMER_CLK_3M            0
#define TIMER_CLK_BUS           1
#define SC_CTRL_REMAP_CLEAR     (0x1 << 8)

/* System soft reset register offset */
#define REG_SC_SYSRES           0x0004

/* System Status register offset */
#define REG_SYSSTAT         0x008c
/* bit[7]=0: 3-Byte address mode; bit[7]=1: 4-Byte address mode */
#define get_spi_nor_addr_mode(_reg) (((_reg) >> 7) & 0x1)
/* bit[6]=0; SPI nor flash; bit[6]=1: SPI nand flash */
#define get_spi_device_type(_reg)   (((_reg) >> 10) & 0x1)
/* bit[4]=0 SPI; bit[4]=1: EMMC */
#define get_sys_boot_mode(_reg)     (((_reg) >> 4) & 0x1)
#define BOOT_FROM_SPI           0
#define BOOT_FROM_SPI_NAND      1
#define BOOT_FROM_NAND          2
#define BOOT_FROM_EMMC          1
#define NF_BOOTBW_MASK          (1 << 11)


#define REG_SC_GEN0         0x0138
#define REG_SC_GEN1         0x013c
#define REG_SC_GEN2         0x0140
#define REG_SC_GEN3         0x0144
#define REG_SC_GEN4         0x0148
#define REG_SC_GEN9         0x0154

/********** Communication Register and flag used by bootrom *************/
#define REG_START_FLAG      (SYS_CTRL_REG_BASE + REG_SC_GEN1)
#define START_MAGIC         0x444f574e
#define SELF_BOOT_TYPE_USBDEV           0x2  /* debug */

/* -------------------------------------------------------------------- */
/* Peripheral Control REG */
/* -------------------------------------------------------------------- */
#define MISC_REG_BASE           0x12028000

#define MISC_CTRL17                     0x0044
#define MISC_CTRL18         0x48
#define MISC_CTRL7          0x001C
#define MISC_CTRL8          0x0020
#define MISC_CTRL9          0x0024

#define EMMC_ISO_EN         (0x1 << 16)
#define RG_EMMC_LHEN_IN         (0x3f << 17)

/* USB 2.0 MISC Control register offset */
#define REG_USB2_CTRL0          MISC_CTRL7
/* base on needs #define REG_USB2_CTRL1  MISC_CTRL9 */

/* FEPHY Control register offset */
#define REG_FEPHY_CTRL0               MISC_CTRL8
#define REG_FEPHY_CTRL1               MISC_CTRL9

/* -------------------------------------------------------------------- */
#define IO_CONFIG_REG_BASE      0x12050000

/* -------------------------------------------------------------------- */
#define UART0_REG_BASE          0x12040000
#define UART1_REG_BASE          0x12041000
#define UART2_REG_BASE          0x12042000

/* -------------------------------------------------------------------- */
#define GPIO0_REG_BASE          0x120B0000
#define GPIO1_REG_BASE          0x120B1000
#define GPIO2_REG_BASE          0x120B2000
#define GPIO3_REG_BASE          0x120B3000
#define GPIO4_REG_BASE          0x120B4000
#define GPIO5_REG_BASE          0x120B5000
#define GPIO6_REG_BASE          0x120B6000
#define GPIO7_REG_BASE          0x120B7000
#define GPIO8_REG_BASE          0x120B8000
#define GPIO9_REG_BASE          0x120B9000

#define FMC_MEM_BASE            0x14000000
#define FMC_TEXT_ADRS           FMC_MEM_BASE
#define DDR_MEM_BASE            0x40000000
#define HW_DEC_INTR              86
/*-----------------------------------------------------------------------
 * EMMC / SD
 * ----------------------------------------------------------------------*/
/* SDIO0 REG */
#define SDIO0_BASE_REG          0x10010000

/* EMMC REG */
#define EMMC_BASE_REG           0x10010000

#define REG_BASE_PERI_CTRL              REG_BASE_SCTL
#define REG_BASE_IO_CONFIG              IO_CONFIG_REG_BASE

#define MMC_IOMUX_START_ADDR            0xF8
#define MMC_IOMUX_END_ADDR              0x13C
#define MMC_IOMUX_CTRL_MASK             (1<<0 | 1<<1)
#define MMC_IOMUX_CTRL                  (1<<1)

#define SYSCNT_REG_BASE     0x12050000
#define SYSCNT_ENABLE_REG       0x0
#define SYSCNT_FREQ_REG         0x20
#define SYSCNT_FREQ         50000000

#define REG_BASE_SYSCNT SYSCNT_REG_BASE
#define CNTCR 0x0
#define CNTFID0 0x20

/* ---------------------------------------------------------*/
#define NUM_0					0
#define NUM_1					1
#define NUM_2					2
#define NUM_3					3
#define NUM_4					4
#define NUM_5					5
#define NUM_6					6
#define NUM_7					7
#define NUM_8					8
#define NUM_9					9

#endif /* End of __HI_CHIP_REGS_H__ */

