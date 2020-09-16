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

#define _HI3516D_V300           0x003516d300LL
#define _HI3516AV300_MASK       0xFFFFFFFFFFLL

/* -------------------------------------------------------------------- */
#define RAM_START_ADRS          0x04010500
#define STACK_TRAINING          0x0401a000

/* -------------------------------------------------------------------- */
#define FMC_REG_BASE            0x10000000

/* -------------------------------------------------------------------- */
#define REG_BASE_SF             0x10010000

/* -------------------------------------------------------------------- */
#define EMMC_REG_BASE           0x10100000
#define SDIO0_REG_BASE          0x100F0000

/* -------------------------------------------------------------------- */
#define USB3_CTRL_REG_BASE      0x100E0000

/* -------------------------------------------------------------------- */
#define DDRC0_REG_BASE          0x11250000

/* -------------------------------------------------------------------- */
#define TIMER0_REG_BASE         0x12000000
#define TIMER1_REG_BASE         0x12000020
#define TIMER2_REG_BASE         0x12001000
#define TIMER3_REG_BASE         0x12001020
#define TIMER4_REG_BASE         0x12002000
#define TIMER5_REG_BASE         0x12002020
#define TIMER6_REG_BASE         0x12003000
#define TIMER7_REG_BASE         0x12003020

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
#define FMC_CLK_163M        0x3
#define FMC_CLK_200M        0x4
#define FMC_CLK_257M        0x5
/* Only DDR clock */
#define FMC_CLK_300M        0x6
#define FMC_CLK_396M        0x7

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

/* -------------------------------------------------------------------- */
/* System Control REG */
/* -------------------------------------------------------------------- */
#define SYS_CTRL_REG_BASE       0x12020000
#define REG_BASE_SCTL           SYS_CTRL_REG_BASE

/* System Control register offset */
#define REG_SC_CTRL         0x0000
#define sc_ctrl_timer0_clk_sel(_clk)    (((_clk) & 0x1) << 16)
#define TIMER0_CLK_SEL_MASK     (0x1 << 16)
#define TIMER_CLK_3M            0
#define TIMER_CLK_BUS           1
#define SC_CTRL_REMAP_CLEAR     (0x1 << 8)

/* System soft reset register offset */
#define REG_SC_SYSRES           0x0004

#define REG_PERISTAT                    0x0030
#define mmc_boot_clk_sel(val)           (((val) >> 8) & 0x3)
#define MMC_BOOT_CLK_50M                0x2

/* System Status register offset */
#define REG_SYSSTAT         0x008c
/* bit[7]=0: 3-Byte address mode; bit[7]=1: 4-Byte address mode */
#define get_spi_nor_addr_mode(_reg) (((_reg) >> 7) & 0x1)
/* bit[6]=0; SPI nor flash; bit[6]=1: SPI nand flash */
#define get_spi_device_type(_reg)   (((_reg) >> 6) & 0x1)
/* bit[4]=0 SPI; bit[4]=1: EMMC */
#define get_sys_boot_mode(_reg)     (((_reg) >> 4) & 0x1)
#define BOOT_FROM_SPI           0
#define BOOT_FROM_NAND          2 /* NOT SUPPORT */
#define BOOT_FROM_EMMC          1
#define NF_BOOTBW_MASK          0

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
#define MISC_REG_BASE           0x12030000

#define MISC_CTRL8          0x0020
#define MISC_CTRL9          0x0024

/* USB 2.0 MISC Control register offset */
#define REG_USB2_CTRL0          MISC_CTRL8
#define REG_USB2_CTRL1          MISC_CTRL9

/* -------------------------------------------------------------------- */
#define IO_CONFIG_REG_BASE      0x12040000

/* -------------------------------------------------------------------- */
#define UART0_REG_BASE          0x120A0000
#define UART1_REG_BASE          0x120A1000
#define UART2_REG_BASE          0x120A2000
#define UART3_REG_BASE          0x120A3000

/* -------------------------------------------------------------------- */
#define GPIO0_REG_BASE          0x120D0000
#define GPIO1_REG_BASE          0x120D1000
#define GPIO2_REG_BASE          0x120D2000
#define GPIO3_REG_BASE          0x120D3000
#define GPIO4_REG_BASE          0x120D4000
#define GPIO5_REG_BASE          0x120D5000
#define GPIO6_REG_BASE          0x120D6000
#define GPIO7_REG_BASE          0x120D7000
#define GPIO8_REG_BASE          0x120D8000
#define GPIO9_REG_BASE          0x120D9000
#define GPIO10_REG_BASE         0x120DA000

#define FMC_MEM_BASE            0x14000000
#define FMC_TEXT_ADRS           FMC_MEM_BASE
#define DDR_MEM_BASE            0x80000000

#define HW_DEC_INTR              86

/*---------------------------------------------------------
 * Syscounter registers
 *---------------------------------------------------------*/
#define SYSCNT_REG_BASE     0x12040000
#define SYSCNT_ENABLE_REG       0x0
#define SYSCNT_FREQ_REG         0x20
#define SYSCNT_FREQ         50000000

#define REG_BASE_SYSCNT 0x12040000
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

