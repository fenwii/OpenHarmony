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

#define _HI3559A_V100                   0x3559A100LL
#define _HI3559AV100_MASK               0xFFFFFFFFFFLL

/* -------------------------------------------------------------------- */
/* Communication Register and flag used by bootrom */
/* -------------------------------------------------------------------- */
#define REG_START_FLAG                  (SYS_CTRL_REG_BASE + REG_SC_GEN1)
#define START_MAGIC                     0x444f574e
#define SELF_BOOT_TYPE_USBDEV           0x2
#define CP_STEP1_ADDR                   0x08040000
#define PCIE_SLAVE_BOOT_CTL_REG         0x0134
#define DDR_INIT_DOWNLOAD_OK_FLAG       0xDCDFF001 /* step1:Ddrinit Code Download Finished Flag:  DCDFF001 */
#define DDR_INIT_EXCUTE_OK_FLAG         0xDCEFF002 /* step2:Ddrinit Code Excute Finished Flag:    DCEFF002 */
#define UBOOT_DOWNLOAD_OK_FLAG          0xBCDFF003 /* step3:Boot Code Download Finished Flag:     BCDFF003 */

/* -------------------------------------------------------------------- */
/* System Control */
/* -------------------------------------------------------------------- */
#define SYS_CTRL_REG_BASE               0x12020000
#define REG_BASE_SCTL                   SYS_CTRL_REG_BASE
#define REG_SC_CTRL                     0x0000
#define REG_SC_SYSRES                   0x0004
#define REG_PERISTAT                    0x0030
#define REG_SYSSTAT                     0x008c
#define get_spi_nor_addr_mode(_reg)     (((_reg) >> 10) & 0x1)
#define get_spi_device_type(_reg)       (((_reg) >> 9) & 0x1)
#define get_sys_boot_mode(_reg)         (((_reg) >> 4) & 0x3)
#define BOOT_FROM_SPI                   0
#define BOOT_FROM_NAND                  1
#define BOOT_FROM_EMMC                  2
#define BOOT_FROM_UFS                   3

#define REG_SC_GEN0                     0x0138
#define REG_SC_GEN1                     0x013c
#define REG_SC_GEN2                     0x0140
#define REG_SC_GEN3                     0x0144
#define REG_SC_GEN4                     0x0148
#define REG_SC_GEN9                     0x0154
#define REG_SC_GEN20                    0x0090

/* -------------------------------------------------------------------- */
/* CPU SUBSYS */
/* -------------------------------------------------------------------- */
#define REG_CRG_CLUSTER0_CLK_RST	0x00cc /* CPU SUBSYS clock and reset control */
#define CLUSTER0_GLB_SRST_REQ           (0x1 << 21)
#define REG_PERI_CPU_RVBARADDR_A53UP    0x12030004
#define REG_PERI_CPU_RVBARADDR_SOC      0x1d830020
#define CLUSTER2_GLB_SRST_REQ           (0x1 << 28)
#define CLUSTER2_GLB_CKEN               (0x1 << 27)

/* -------------------------------------------------------------------- */
/* CRG */
/* -------------------------------------------------------------------- */
#define CRG_REG_BASE                    0x12010000

/* -------------------------------------------------------------------- */
/* Peripheral Control REG */
/* -------------------------------------------------------------------- */
#define MISC_REG_BASE                   0x12030000

/* -------------------------------------------------------------------- */
/* IO configuration REG:mux and driver */
/* -------------------------------------------------------------------- */
#define IO_CONFIG_REG_BASE              0x1F000000

/* -------------------------------------------------------------------- */
/* TIMER */
/* -------------------------------------------------------------------- */
#define TIMER0_REG_BASE                 0x12000000
#define REG_TIMER_RELOAD                0x0
#define REG_TIMER_VALUE                 0x4
#define REG_TIMER_CONTROL               0x8
#define CFG_TIMER_CLK                   3000000
#define CFG_TIMERBASE                   TIMER0_REG_BASE
/* enable timer.32bit, periodic,mask irq, 1 divider. */
#define CFG_TIMER_CTRL                  0xC2

/* -------------------------------------------------------------------- */
/* UART */
/* -------------------------------------------------------------------- */
#define UART0_REG_BASE                  0x12100000
#define UART1_REG_BASE                  0x12101000
#define UART2_REG_BASE                  0x12102000
#define UART3_REG_BASE                  0x12103000

/* -------------------------------------------------------------------- */
/* DDRC */
/* -------------------------------------------------------------------- */
#define STACK_TRAINING                  0x08009000
#define DDRC0_REG_BASE                  0x12060000
#define DDR_MEM_BASE                    0x40000000
#define REG_SC_DDRT0                    0x0090

/* -------------------------------------------------------------------- */
/* FMC */
/* -------------------------------------------------------------------- */
#define FMC_REG_BASE                    0x10000000
#define FMC_MEM_BASE                    0x14000000

/* FMC CRG register offset */
#define REG_FMC_CRG                     0x0170

#define fmc_clk_sel(_clk)               (((_clk) & 0x7) << 2)
#define FMC_CLK_SEL_MASK                (0x7 << 2)
#define get_fmc_clk_type(_reg)          (((_reg) >> 2) & 0x7)

/* SDR/DDR clock */
#define FMC_CLK_24M                     0
#define FMC_CLK_75M                     1
#define FMC_CLK_125M                    2
#define FMC_CLK_150M                    3
#define FMC_CLK_200M                    4
/* Only DDR clock */
#define FMC_CLK_250M                    5
#define FMC_CLK_300M                    6
#define FMC_CLK_400M                    7

#define FMC_CLK_ENABLE                  (0x1 << 1)
#define FMC_SOFT_RST_REQ                (0x1 << 0)

/*--------------------------------------------------------------------- */
/* EMMC / SD */
/* -------------------------------------------------------------------- */
#define REG_SDIO0_CRG                   (CRG_REG_BASE + 0x1ec)

/* eMMC CRG register offset */
#define REG_EMMC_CRG                    (CRG_REG_BASE + 0x1a8)
#define mmc_clk_sel(_clk)               (((_clk) & 0x7) << 24)
#define MMC_CLK_SEL_MASK                (0x7 << 24)
#define get_mmc_clk_type(_reg)          (((_reg) >> 24) & 0x7)

/* SDIO0 REG */
#define SDIO0_BASE_REG                  0x10100000

/* SDIO1 REG */
#define SDIO1_BASE_REG                  0x10110000

/* EMMC REG */
#define EMMC_BASE_REG                   0x100F0000
#define EMMC_PHY_BASE               0x10290000

#define NF_BOOTBW_MASK                  (1 << 10)
#define REG_BASE_PERI_CTRL              REG_BASE_SCTL
#define REG_BASE_IO_CONFIG              IO_CONFIG_REG_BASE

#define MMC_IOMUX_START_ADDR            0xF8
#define MMC_IOMUX_END_ADDR              0x13C
#define MMC_IOMUX_CTRL_MASK             (1<<0 | 1<<1)
#define MMC_IOMUX_CTRL                  (1<<1)

/* -------------------------------------------------------------------- */
/* UFS */
/* -------------------------------------------------------------------- */
#define PERI_CRG96                      0x180 /* UFS/eMMC clock and reset control */
#define BIT_UFS_AXI_SRST_REQ            (0x1 << 11)
#define BIT_UFS_SRST_REQ                (0x1 << 12)
#define BIT_UFS_CLK_EN                  (0x1 << 13)

#define MISC_CTRL17                     0x44
#define UFS_EN                          0x1
#define DA_UFS_REFCLK_OEN               (0x1 << 3)
#define DA_UFS_RST_OEN                  (0x1 << 10)
#define EMMC_ISO_EN                     (0x1 << 16)
#define RG_EMMC_LHEN_IN                 (0x3f << 17)
#define MISC_CTRL18                     0x48
#define MISC_CTRL36                     0x0090
#define MISC_CTRL37                     0x0094

#define BIT_UFS_PAD_RESET               (0x1 << 15)
#define BIT_DA_UFS_RESET_DS2            (0x1 << 14)
#define BIT_DA_UFS_RESET_DS1            (0x1 << 13)
#define BIT_DA_UFS_RESET_DS0            (0x1 << 12)
#define BIT_DA_UFS_RESET_SL             (0x1 << 11)
#define BIT_DA_UFS_RESET_OEN            (0x1 << 10)
#define BIT_DA_UFS_RESET_PS             (0x1 << 9)
#define BIT_DA_UFS_RESET_PE             (0x1 << 8)
#define BIT_DA_UFS_REFCLK_DS2           (0x1 << 7)
#define BIT_DA_UFS_REFCLK_DS1           (0x1 << 6)
#define BIT_DA_UFS_REFCLK_DS0           (0x1 << 5)
#define BIT_DA_UFS_REFCLK_SL            (0x1 << 4)
#define BIT_DA_UFS_REFCLK_OEN           (0x1 << 3)
#define BIT_DA_UFS_REFCLK_PS            (0x1 << 2)
#define BIT_DA_UFS_REFCLK_PE            (0x1 << 1)
#define BIT_UFS_ENABLE                  (0x1 << 0)

#define MASK_DA_UFS_RESET_DS            (0x7 << 12)
#define MASK_DA_UFS_REFCLK_DS           (0x7 << 5)

/*--------------------------------------------------------------------- */
/* HIGMAC */
/* -------------------------------------------------------------------- */
#define HIGMAC0_IOBASE          0x101C0000
#define HIGMAC1_IOBASE          0x101E0000
/* Ethernet CRG register offset */
#define REG_ETH_CRG         0x174
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

#define PHY0_CLK_25M            0
#define PHY0_CLK_50M            BIT_EXT_PHY0_CLK_SELECT
#define PHY1_CLK_25M            0
#define PHY1_CLK_50M            BIT_EXT_PHY1_CLK_SELECT

#define HIGMAC_MACIF0_CTRL      (HIGMAC0_IOBASE + 0x300c)
#define HIGMAC_MACIF1_CTRL      (HIGMAC1_IOBASE + 0x300c)
#define HIGMAC_DUAL_MAC_CRF_ACK_TH  (HIGMAC0_IOBASE + 0x3004)

/* -------------------------------------------------------------------- */
/* USB */
/* -------------------------------------------------------------------- */
#define USB3_CTRL_REG_BASE      0x12300000
#define USB3_CTRL_REG_BASE_1    0x12310000

/* USB CRG register offset and config */
#define PERI_CRG97              0x184
#define USB2_PHY_CKEN           (0x1<<4)
#define USB2_PHY_PORT_TREQ      (0x1<<2)
#define USB2_PHY_REQ            (0x1<<0)

#define PERI_CRG98              0x188
#define COMBPHY_REF_CKEN        (0x1<<24)
#define COMBPHY_SRST_REQ        (0x1<<16)

#define PERI_CRG100             0x190
#define USB3_VCC_SRST_REQ       (0x1<<0)
#define USB3_UTMI_CKSEL         (0x1<<13)
#define USB3_1_PCLK_OCC_SEL     (0x1<<14)
#define USB3_0_PCLK_OCC_SEL     (0x1<<30)

#define USB2_PHY_CFG        (CRG_REG_BASE + PERI_CRG97)
#define USB3_COMBPHY_CFG    (CRG_REG_BASE + PERI_CRG98)
#define USB3_CTRL_CFG       (CRG_REG_BASE + PERI_CRG100)

/* USB CTRL register offset and config */
#define GTXTHRCFG               0xc108
#define GRXTHRCFG               0xc10c
#define REG_GCTL                0xc110

#define USB_TXPKT_CNT_SEL       (0x1<<29)
#define USB_TXPKT_CNT           (0x11<<24)
#define USB_MAXTX_BURST_SIZE    (0x1<<20)
#define CLEAN_USB3_GTXTHRCFG    0x0

#define REG_GUSB3PIPECTL0       0xc2c0
#define PCS_SSP_SOFT_RESET      (0x1 << 31)

/* USB EYE diagram para offset and config */
#define USB3_COMB_PHY           0x14
#define P0_TX_SWING_COMP_CFG    0xd13
#define P0_TX_SWING_COMP_RCFG   0xd53
#define P0_TX_SWING_COMP_VAL    0xd13

#define P0_TX_TERMINATION_TRIM_CFG  0x14
#define P0_TX_TERMINATION_TRIM_RCFG 0x54
#define P0_TX_TERMINATION_TRIM_VAL  0x14

#define P1_TX_SWING_COMP_CFG    0xd33
#define P1_TX_SWING_COMP_RCFG   0xd73
#define P1_TX_SWING_COMP_VAL    0xd33

#define P1_TX_TERMINATION_TRIM_CFG  0x34
#define P1_TX_TERMINATION_TRIM_RCFG 0x74
#define P1_TX_TERMINATION_TRIM_VAL  0x34

#define USB2_PHY0_CTRL  0x24
#define USB2_PHY1_CTRL  0x30
#define USB2_PHY_VREF   (0x5 << 4)
#define USB2_PHY_PRE    (0x3 << 12)

/* -------------------------------------------------------------------- */
/* HW DECOMPRESS */
/* -------------------------------------------------------------------- */
#define GZIP_REG_BASE           0x11330000
#define HW_DEC_INTR     86
/* -------------------------------------------------------------------- */
/* PCIE */
/* -------------------------------------------------------------------- */
#define SYS_SATA        0x8c
#define PCIE_MODE       12

#define PERI_CRG98      0x188
#define PHY0_SRS_REQ            0
#define PHY0_SRS_REQ_SEL        1
#define PHY1_SRS_REQ            16
#define PHY1_SRS_REQ_SEL        17

#define MISC_CTRL5          0x14

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
#define NUM_10					10

#define BIT_16				16
#define BIT_20				20
#define BIT_24				24
#define BIT_28				28

#endif /* End of __HI_CHIP_REGS_H__ */
