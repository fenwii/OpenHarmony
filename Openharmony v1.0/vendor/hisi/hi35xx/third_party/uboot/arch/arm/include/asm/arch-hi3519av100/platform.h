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

/* -------------------------------------------------------------------- */
#define RAM_START_ADRS          0x04240000

/* -------------------------------------------------------------------- */
#define FMC_REG_BASE            0x04020000

/* -------------------------------------------------------------------- */
#define GSF_REG_BASE            0x040E0000

/* -------------------------------------------------------------------- */
#define USB3_CTRL_REG_BASE      0X04110000

/* -------------------------------------------------------------------- */
#define USB2_CTRL_REG_BASE      0X04120000

#define TIMER0_REG_BASE         0x04500000
#define TIMER1_REG_BASE         0x04500000
#define TIMER2_REG_BASE         0x04501000
#define TIMER3_REG_BASE         0x04501000
#define TIMER4_REG_BASE         0x04502000
#define TIMER5_REG_BASE         0x04502000
#define TIMER6_REG_BASE         0x04503000
#define TIMER7_REG_BASE         0x04503000
#define TIMER8_REG_BASE         0x04504000
#define TIMER9_REG_BASE         0x04504000
#define TIMER10_REG_BASE        0x04505000
#define TIMER11_REG_BASE        0x04505000

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
#define CRG_REG_BASE            0x04510000

#define PERI_CRG102         0x0198
#define UART_CKSEL_24M          (1 << 29)

#define REG_CRG92           0x0170
#define REG_CRG_CLUSTER0_CLK_RST	0x00cc
#define CLUSTER0_GLB_SRST_REQ       (0x1 << 21)

/* USB CRG register offset */
#define PERI_CRG97      0x184
#define PERI_CRG98      0x188
#define PERI_CRG100     0x190

#define USB2_PHY_CFG    (CRG_REG_BASE + PERI_CRG97)
#define USB3_COMBPHY_CFG    (CRG_REG_BASE + PERI_CRG98)
#define USB3_CTRL_CFG   (CRG_REG_BASE + PERI_CRG100)
/* FMC CRG register offset */
#define REG_FMC_CRG         REG_CRG92
#define fmc_clk_sel(_clk)       (((_clk) & 0x7) << 2)
#define FMC_CLK_SEL_MASK        (0x7 << 2)
#define get_fmc_clk_type(_reg)      (((_reg) >> 2) & 0x7)
/* SDR/DDR clock */
#define FMC_CLK_24M         0
#define FMC_CLK_75M         1
#define FMC_CLK_125M            2
#define FMC_CLK_150M            3
#define FMC_CLK_200M            4
#define FMC_CLK_250M            5
/* Only DDR clock */
#define FMC_CLK_300M            6
#define FMC_CLK_400M            7
#define FMC_CLK_ENABLE          (0x1 << 1)
#define FMC_SOFT_RST_REQ        (0x1 << 0)

/* SDIO0 CRG register offset */
#define REG_SDIO0_CRG           (CRG_REG_BASE + 0x1ec)

/* eMMC CRG register offset */
#define REG_EMMC_CRG            (CRG_REG_BASE + 0x1a8)
#define mmc_clk_sel(_clk)       (((_clk) & 0x7) << 24)
#define MMC_CLK_SEL_MASK        (0x7 << 24)
#define get_mmc_clk_type(_reg)      (((_reg) >> 8) & 0x7)

/* -------------------------------------------------------------------- */
/* System Control REG */
/* -------------------------------------------------------------------- */
#define SYS_CTRL_REG_BASE       0x04520000
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

#define REG_PERISTAT            0x0030
#define mmc_boot_clk_sel(val)    (((val) >> 8) & 0x3)
#define MMC_BOOT_CLK_50M    0x2

/* System Status register offset */
#define REG_SYSSTAT         0x008c
/* bit[9]=0: PCI-E Master mode; bit[9]=1: PCI-E Slave mode */
#define get_pcie_slave_mode(_reg)   (((_reg) >> 9) & 0x1)
/* if bit[4]=0 SPI nor flash
 * bit[10]=0: 3-Byte address mode; bit[10]=1: 4-Byte address mode */
#define get_spi_nor_addr_mode(_reg) (((_reg) >> 10) & 0x1)
#define get_sys_boot_mode(_reg)     (((_reg) >> 4) & 0x3)
#define BOOT_FROM_SPI           0
#define BOOT_FROM_SPI_NAND      1
#define BOOT_FROM_NAND          2
#define BOOT_FROM_EMMC          3

/* bit[4]=0; SPI nor flash; bit[4]=1: SPI nand flash */
#define get_spi_device_type(_reg)   (((_reg) >> 4) & 0x1)

#define REG_SC_GEN20            0x0090
#define REG_SC_GEN0         0x0138
#define REG_SC_GEN1         0x013c
#define REG_SC_GEN2         0x0140
#define REG_SC_GEN3         0x0144
#define REG_SC_GEN4         0x0148
#define REG_SC_GEN9         0x0154

/* -------------------------------------------------------------------- */
#define UART5_REG_BASE          0x04545000
#define UART4_REG_BASE          0x04544000
#define UART3_REG_BASE          0x04543000
#define UART2_REG_BASE          0x04542000
#define UART1_REG_BASE          0x04541000
#define UART0_REG_BASE          0x04540000

/* -------------------------------------------------------------------- */
#define RTC_REG_BASE            0x04550000
#define IO_CONFIG_REG_BASE      0x045B0000
#define DDRC0_REG_BASE          0x04600000

/* -------------------------------------------------------------------- */
/* Peripheral Control REG */
/* -------------------------------------------------------------------- */
#define MISC_REG_BASE           0x04528000

#define MISC_CTRL17         0x0044
#define MISC_CTRL18         0x0048
/* base on needs #define MISC_CTRL20  0x0020
   base on needs #define MISC_CTRL28  0x0028
   base on needs #define MISC_CTRL36  0x0090
   base on needs #define MISC_CTRL37  0x0094 */

#define EMMC_ISO_EN         (0x1 << 16)
#define RG_EMMC_LHEN_IN         (0x3f << 17)

/* USB 2.0 MISC Control register offset */
#define REG_USB2_CTRL0          MISC_CTRL36
#define REG_USB2_CTRL1          MISC_CTRL37

/* ------------------------------------------------
 * GPIO reg base address
 *------------------------------------------------ */
#define GPIO15_REG_BASE         0x045FF000
#define GPIO14_REG_BASE         0x045FE000
#define GPIO13_REG_BASE         0x045FD000
#define GPIO12_REG_BASE         0x045FC000
#define GPIO11_REG_BASE         0x045FB000
#define GPIO10_REG_BASE         0x045FA000
#define GPIO9_REG_BASE          0x045F9000
#define GPIO8_REG_BASE          0x045F8000
#define GPIO7_REG_BASE          0x045F7000
#define GPIO6_REG_BASE          0x045F6000
#define GPIO5_REG_BASE          0x045F5000
#define GPIO4_REG_BASE          0x045F4000
#define GPIO3_REG_BASE          0x045F3000
#define GPIO2_REG_BASE          0x045F2000
#define GPIO1_REG_BASE          0x045F1000
#define GPIO0_REG_BASE          0x045F0000

/* -------------------------------------------------------------------- */
#define FMC_MEM_BASE            0x0F000000
#define DDR_MEM_BASE            0x20000000
#define FMC_TEXT_ADRS           FMC_MEM_BASE

/********** Communication Register and flag used by bootrom *************/
#define REG_START_FLAG          (SYS_CTRL_REG_BASE + REG_SC_GEN1)
#define START_MAGIC         0x444f574e
#define SELF_BOOT_TYPE_USBDEV   0x2

/* --------------------------------------------------------------------
 * DDR Training
 * -------------------------------------------------------------------- */
#define STACK_TRAINING          0x04209000
#define REG_SC_DDRT0            0x0090
#define NORMAL_BOOTMODE_OFFSET          9
#define NORMAL_BOOTMODE_MASK            3

/* --------------------------------------------------------------------------
 * PCIE slave start up
 *------------------------------------------------------------------------- */
#define PCIE_SLV_STACK          0x0420A000
#define PCIE_SLV_DDR_INIT_FLG       0x8080
#define HI3556AV100_SYSBOOT9        0x154
#define HI3556AV100_BOOT_FLAG       0x134
#define HI3556AV100_SYSBOOT10       0x158

/*--------------------------------------------------------------------------
* Cci register definations
 *--------------------------------------------------------------------------*/
#define CCI_PORT_CTRL_0         0x04D01000
#define CCI_PORT_CTRL_1         0x04D02000
#define CCI_CTRL_STATUS         0x04D0000c
#define CCI_ENABLE_REQ          0x3

/*--------------------------------------------------------------------------
 * gzip registers
 *-------------------------------------------------------------------------*/
#define GZIP_REG_BASE           0x04790000
#define REG_SNAPSHOT_IMAGE_MAGIC    0x045200a4
#define REG_SNAPSHOT_IMAGE_START    0x045200a8
#define REG_SNAPSHOT_IMAGE_SIZE     0x045200ac

#define HW_DEC_INTR     86
/*-----------------------------------------------------------------------
 * EMMC / SD
 * ----------------------------------------------------------------------*/
/* SDIO0 REG */
#define SDIO0_BASE_REG          0x040C0000

/* SDIO1 REG */
#define SDIO1_BASE_REG          0x040D0000

/* EMMC REG */
#define EMMC_BASE_REG           0x04030000
#define EMMC_PHY_BASE           0x04048000

#define NF_BOOTBW_MASK                  (1 << 10)
#define REG_BASE_PERI_CTRL              REG_BASE_SCTL
#define REG_BASE_IO_CONFIG              IO_CONFIG_REG_BASE

#define MMC_IOMUX_START_ADDR            0xF8
#define MMC_IOMUX_END_ADDR              0x13C
#define MMC_IOMUX_CTRL_MASK             (1<<0 | 1<<1)
#define MMC_IOMUX_CTRL                  (1<<1)

/* HIGMAC REG */
#define HIGMAC0_IOBASE          0x040E0000
/* Ethernet CRG register offset */
#define REG_ETH_CRG         0x174
/* Ethernet MAC CRG register bit map */
#define BIT_GMAC0_RST           BIT(0)
#define BIT_GMAC0_CLK_EN        BIT(1)
#define BIT_MACIF0_RST          BIT(4)
#define BIT_GMACIF0_CLK_EN      BIT(5)
#define BIT_RMII0_CLKSEL_PAD        BIT(8)
#define BIT_EXT_PHY0_CLK_SELECT     BIT(12)
#define BIT_EXT_PHY0_RST        BIT(14)

#define PHY0_CLK_25M            0
#define PHY0_CLK_50M            BIT_EXT_PHY0_CLK_SELECT

#define HIGMAC_MACIF0_CTRL      (HIGMAC0_IOBASE + 0x300c)
#define HIGMAC_DUAL_MAC_CRF_ACK_TH  (HIGMAC0_IOBASE + 0x3004)

/*---------------------------------------------------------
 * Syscounter registers
 *---------------------------------------------------------*/
#define SYSCNT_REG_BASE     0x04c40000
#define SYSCNT_ENABLE_REG       0x0
#define SYSCNT_FREQ_REG         0x20
#define SYSCNT_FREQ         24000000

/* --------------------------------------------------------- */
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
