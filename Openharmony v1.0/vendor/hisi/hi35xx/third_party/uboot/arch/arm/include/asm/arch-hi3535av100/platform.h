#ifndef __HI_CHIP_REGS_H__
#define __HI_CHIP_REGS_H__

/* -------------------------------------------------------------------- */
/* Communication Register and flag used by bootrom */
/* -------------------------------------------------------------------- */
#define REG_START_FLAG			(SYS_CTRL_REG_BASE + REG_SC_GEN1)
#define START_MAGIC			(0x444f574e)
#define SELF_BOOT_TYPE_USBDEV           0x2
#define CP_STEP1_ADDR                   0x04010500
#define PCIE_SLAVE_BOOT_CTL_REG         0x0134
#define DDR_INIT_DOWNLOAD_OK_FLAG       0xDCDFF001 /* step1:Ddrinit Code Download Finished Flag:  DCDFF001 */
#define DDR_INIT_EXCUTE_OK_FLAG         0xDCEFF002 /* step2:Ddrinit Code Excute Finished Flag:    DCEFF002 */
#define UBOOT_DOWNLOAD_OK_FLAG          0xBCDFF003 /* step3:Boot Code Download Finished Flag:     BCDFF003 */

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

#define REG_SC_GEN0				0x0138
#define REG_SC_GEN1				0x013c
#define REG_SC_GEN2				0x0140
#define REG_SC_GEN3				0x0144
#define REG_SC_GEN4				0x0148
#define REG_SC_GEN9				0x0154
#define REG_SC_GEN20				0x0090

/* -------------------------------------------------------------------- */
/* CPU SUBSYS */
/* -------------------------------------------------------------------- */
#define REG_CRG_CLUSTER0_CLK_RST	0x0190 /* CPU SUBSYS clock and reset control*/
#define CLUSTER0_GLB_SRST_REQ	        (0x1 << 17)

#define REG_PERI_CPU_RVBARADDR_A53UP	0x11024004
#define REG_PERI_CPU_RVBARADDR_SOC	0x12030020

#define REG_CRG_CLUSTER1_CLK_RST	0x0194
#define CLUSTER1_GLB_SRST_REQ           (0x1 << 9)
#define CLUSTER1_GLB_CKEN               (0x1 << 8)

/* -------------------------------------------------------------------- */
/* CRG */
/* -------------------------------------------------------------------- */
#define CRG_REG_BASE			        0x11010000

/* -------------------------------------------------------------------- */
/* Peripheral Control REG */
/* -------------------------------------------------------------------- */
#define MISC_REG_BASE			        0x11024000

#define USB_CTRL6   0x194
#define U3_PORT_DISABLE  (0x1 << 12)

/* -------------------------------------------------------------------- */
/* IO configuration REG:mux and driver */
/* -------------------------------------------------------------------- */
#define AHB_IO_CONFIG_REG_BASE			0x11180000
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

#define UATR_IO_CFG_BASE			0x102f0000
#define UART0_RXD_IOCFG_OFST			0x20
#define UART0_TXD_IOCFG_OFST			0x24
/* -------------------------------------------------------------------- */
/* DDRC */
/* -------------------------------------------------------------------- */
#define STACK_TRAINING		 	        0x0401A000
#define DDRC0_REG_BASE			        0x11130000
#define DDR_MEM_BASE			        0x40000000

/* -------------------------------------------------------------------- */
/* FMC */
/* -------------------------------------------------------------------- */
#define FMC_REG_BASE			        0x10000000
#define FMC_MEM_BASE			        0x0f000000

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
#define mmc_clk_sel(_clk)			(((_clk) & 0x7) << 24)
#define MMC_CLK_SEL_MASK			(0x7 << 24)
#define GET_MMC_CLK_TYPE(_reg)			(((_reg) >> 24) & 0x7)
#define REG_SAVE_HCS				0x11020300

/* EMMC REG*/
#define EMMC_BASE_REG			        0x10020000
#define NO_EMMC_PHY				1

#define NF_BOOTBW_MASK				(1 << 11)
#define REG_BASE_PERI_CTRL			REG_BASE_SCTL
#define REG_BASE_IO_CONFIG			IO_CONFIG_REG_BASE

/* SDIO0 REG */
#define REG_SDIO0_CRG				REG_EMMC_CRG
#define SDIO0_BASE_REG			        EMMC_BASE_REG

/*--------------------------------------------------------------------- */
/* HIGMAC */
/* -------------------------------------------------------------------- */
#define HIGMAC0_IOBASE			0x10290000
#define HIGMAC1_IOBASE			0x102A0000

/* Ethernet MAC0 MAC_IF CRG register offset */
#define REG_ETH0_MACIF_CRG              0x37c0
/* Ethernet MAC0 MAC_If CRG register bit map*/
#define BIT_MACIF0_RST                  BIT(0)
#define BIT_GMACIF0_CLK_EN              BIT(4)
#define BIT_RMII0_CLKSEL_PAD            BIT(12)

/* Ethernet MAC0 GSF CRG register offset */
#define REG_ETH0_GSF_CRG                0x37c4
/* Ethernet MAC0 GSF CRG register bit map*/
#define BIT_GMAC0_RST                   BIT(0)
#define BIT_GMAC0_CLK_EN                BIT(4)

/* Ethernet MAC0 PHY CRG register offset */
#define REG_ETH0_PHY_CRG                0x37cc
/* Ethernet MAC0 PHY CRG register bit map*/
#define BIT_EXT_PHY0_RST		BIT(0)
#define BIT_EXT_PHY0_CLK_SELECT		BIT(12)


/* Ethernet MAC1 MAC_IF CRG register offset */
#define REG_ETH1_MACIF_CRG              0x3800
/* Ethernet MAC1 MAC_If CRG register bit map*/
#define BIT_MACIF1_RST                  BIT(0)
#define BIT_GMACIF1_CLK_EN              BIT(4)
#define BIT_RMII1_CLKSEL_PAD            BIT(12)

/* Ethernet MAC1 GSF CRG register offset */
#define REG_ETH1_GSF_CRG                0x3804
/* Ethernet MAC1 GSF CRG register bit map*/
#define BIT_GMAC1_RST                   BIT(0)
#define BIT_GMAC1_CLK_EN                BIT(4)

/* Ethernet MAC1 PHY CRG register offset */
#define REG_ETH1_PHY_CRG                0x380c
/* Ethernet MAC1 PHY CRG register bit map*/
#define BIT_EXT_PHY1_RST		BIT(0)
#define BIT_EXT_PHY1_CLK_SELECT		BIT(12)

#define PHY0_CLK_25M			0
#define PHY0_CLK_50M			BIT_EXT_PHY0_CLK_SELECT
#define PHY1_CLK_25M			0
#define PHY1_CLK_50M			BIT_EXT_PHY1_CLK_SELECT

#define HIGMAC_MACIF0_CTRL		(HIGMAC0_IOBASE + 0x300c)
#define HIGMAC_MACIF1_CTRL		(HIGMAC1_IOBASE + 0x300c)
#define HIGMAC_DUAL_MAC_CRF_ACK_TH	(HIGMAC0_IOBASE + 0x3004)

/* Configure higmac pinout parameters in software */
#define CFG_NET_PINCTRL

/* MDIO0 pinctrl phyical addr */
#define PHY_ADDR_MDCK0			0x017C70138
#define PHY_ADDR_MDIO0			0x017C7013C
/* MDIO1 pinctrl phyical addr */
#define PHY_ADDR_MDCK1			0x017C701E0
#define PHY_ADDR_MDIO1			0x017C70200

/* PHY0 pinctrl phyical addr */
#define PHY_ADDR_EPHY0_CLK		0x017C7011C
#define PHY_ADDR_EPHY0_RSTN		0x017C7014C
/* PHY1 pinctrl phyical addr */
#define PHY_ADDR_EPHY1_CLK		0x017C701F0
#define PHY_ADDR_EPHY1_RSTN		0x017C701DC

/* RGMII0 pinctrl phyical addr */
#define PHY_ADDR_RGMII0_TXCKOUT	0x017C7012C
#define PHY_ADDR_RGMII0_TXD0	0x017C70114
#define PHY_ADDR_RGMII0_TXD1	0x017C70118
#define PHY_ADDR_RGMII0_TXD2	0x017C70120
#define PHY_ADDR_RGMII0_TXD3	0x017C70124
#define PHY_ADDR_RGMII0_TXEN	0x017C70128
#define PHY_ADDR_RGMII0_RXCK	0x017C70154
#define PHY_ADDR_RGMII0_RXD0	0x017C70144
#define PHY_ADDR_RGMII0_RXD1	0x017C70140
#define PHY_ADDR_RGMII0_RXD2	0x017C70134
#define PHY_ADDR_RGMII0_RXD3	0x017C70130
#define PHY_ADDR_RGMII0_RXDV	0x017C70150

/* RGMII1 pinctrl phyical addr */
#define PHY_ADDR_RGMII1_TXCKOUT	0x017C70218
#define PHY_ADDR_RGMII1_TXD0	0x017C7020C
#define PHY_ADDR_RGMII1_TXD1	0x017C70214
#define PHY_ADDR_RGMII1_TXD2	0x017C701F4
#define PHY_ADDR_RGMII1_TXD3	0x017C70208
#define PHY_ADDR_RGMII1_TXEN	0x017C70210
#define PHY_ADDR_RGMII1_RXCK	0x017C701EC
#define PHY_ADDR_RGMII1_RXD0	0x017C701E4
#define PHY_ADDR_RGMII1_RXD1	0x017C70204
#define PHY_ADDR_RGMII1_RXD2	0x017C701FC
#define PHY_ADDR_RGMII1_RXD3	0x017C701F8
#define PHY_ADDR_RGMII1_RXDV	0x017C701E8

/* RMII0 pinctrl phyical addr */
#define PHY_ADDR_RMII0_CLK		0x017C7012C
#define PHY_ADDR_RMII0_TXD0		0x017C70114
#define PHY_ADDR_RMII0_TXD1		0x017C70118
#define PHY_ADDR_RMII0_TXEN		0x017C70128
#define PHY_ADDR_RMII0_RXD0		0x017C70144
#define PHY_ADDR_RMII0_RXD1		0x017C70140
#define PHY_ADDR_RMII0_RXDV		0x017C70150

/* RMII1 pinctrl phyical addr */
#define PHY_ADDR_RMII1_CLK		0x017C70218
#define PHY_ADDR_RMII1_TXD0		0x017C7020C
#define PHY_ADDR_RMII1_TXD1		0x017C70214
#define PHY_ADDR_RMII1_TXEN		0x017C70210
#define PHY_ADDR_RMII1_RXD0		0x017C701E4
#define PHY_ADDR_RMII1_RXD1		0x017C70204
#define PHY_ADDR_RMII1_RXDV		0x017C701E8

/* MDIO0 config value */
#define VALUE_MDCK0				0x1002
#define VALUE_MDIO0				0x1002
/* MDIO1 config value */
#define VALUE_MDCK1				0x1022
#define VALUE_MDIO1				0x1032

/* PHY0 config value */
#define VALUE_EPHY0_CLK			0x1012
#define VALUE_EPHY0_RSTN		0x1002
/* PHY1 config value */
#define VALUE_EPHY1_CLK			0x1002
#define VALUE_EPHY1_RSTN		0x1002

/* RGMII0 config value */
#define VALUE_RGMII0_TXCKOUT	0x1042
#define VALUE_RGMII0_TXD0		0x1052
#define VALUE_RGMII0_TXD1		0x1052
#define VALUE_RGMII0_TXD2		0x1052
#define VALUE_RGMII0_TXD3		0x1052
#define VALUE_RGMII0_TXEN		0x1052
#define VALUE_RGMII0_RXCK		0x1002
#define VALUE_RGMII0_RXD0		0x1002
#define VALUE_RGMII0_RXD1		0x1002
#define VALUE_RGMII0_RXD2		0x1002
#define VALUE_RGMII0_RXD3		0x1002
#define VALUE_RGMII0_RXDV		0x1002

/* RGMII1 config value */
#define VALUE_RGMII1_TXCKOUT	0x1042
#define VALUE_RGMII1_TXD0		0x1052
#define VALUE_RGMII1_TXD1		0x1052
#define VALUE_RGMII1_TXD2		0x1052
#define VALUE_RGMII1_TXD3		0x1052
#define VALUE_RGMII1_TXEN		0x1052
#define VALUE_RGMII1_RXCK		0x1032
#define VALUE_RGMII1_RXD0		0x1032
#define VALUE_RGMII1_RXD1		0x1032
#define VALUE_RGMII1_RXD2		0x1032
#define VALUE_RGMII1_RXD3		0x1032
#define VALUE_RGMII1_RXDV		0x1032

/* RMII0 config value */
#define VALUE_RMII0_CLK			0x1053
#define VALUE_RMII0_TXD0		0x1052
#define VALUE_RMII0_TXD1		0x1052
#define VALUE_RMII0_TXEN		0x1052
#define VALUE_RMII0_RXD0		0x1032
#define VALUE_RMII0_RXD1		0x1032
#define VALUE_RMII0_RXDV		0x1032

/* RMII1 config value */
#define VALUE_RMII1_CLK			0x1053
#define VALUE_RMII1_TXD0		0x1052
#define VALUE_RMII1_TXD1		0x1052
#define VALUE_RMII1_TXEN		0x1052
#define VALUE_RMII1_RXD0		0x1032
#define VALUE_RMII1_RXD1		0x1032
#define VALUE_RMII1_RXDV		0x1032

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

/* USB CRG register offset and config */
#define	PERI_CRG3632		0x38c0
#define	USB2_0_UTMI_CKEN	(0x1 << 8)

#define	PERI_CRG3636		0x38d0
#define	USB2_PHY0_REQ		(0x1 << 0)
#define	USB2_PHY0_TREQ		(0x1 << 1)
#define	USB2_PHY0_APB_SRST_REQ	(0x1 << 2)
#define	USB2_PHY0_XTAL_CKEN	(0x1 << 4)

#define	PERI_CRG3640		0x38e0
#define	USB2_1_SRST_REQ		(0x1 << 0)
#define	USB2_1_BUS_CKEN		(0x1 << 4)
#define	USB2_1_REF_CKEN		(0x1 << 5)
#define	USB2_1_UTMI_CKEN	(0x1 << 8)

#define	PERI_CRG3644		0x38f0
#define	USB2_PHY1_REQ		(0x1 << 0)
#define	USB2_PHY1_TREQ		(0x1 << 1)
#define	USB2_PHY1_APB_SRST_REQ	(0x1 << 2)
#define	USB2_PHY1_XTAL_CKEN	(0x1 << 4)

#define	PERI_CRG3664		0x3940
#define	USB3_SRST_REQ		(0x1 << 0)
#define	USB3_BUS_CKEN		(0x1 << 4)
#define	USB3_REF_CKEN		(0x1 << 5)
#define	USB3_SUSPEND_CKEN	(0x1 << 6)
#define	USB3_UTMI_CKEN		(0x1 << 8)
#define	USB3_PIPE_CKEN		(0x1 << 12)

#define	PERI_CRG3672		0x3960
#define	USB2_PHY2_REQ		(0x1 << 0)
#define	USB2_PHY2_TREQ		(0x1 << 1)
#define	USB2_PHY2_APB_SRST_REQ	(0x1 << 2)
#define	USB2_PHY2_XTAL_CKEN	(0x1 << 4)

#define	PERI_CRG3676		0x3970
#define	COMBPHY0_SRST_REQ	(0x1 << 0)
#define	COMBPHY0_REF_CKEN	(0x1 << 4)

#define USB2_CTRL0_CFG		(CRG_REG_BASE + PERI_CRG3632)
#define USB2_PHY0_CFG		(CRG_REG_BASE + PERI_CRG3636)
#define USB2_CTRL1_CFG		(CRG_REG_BASE + PERI_CRG3640)
#define USB2_PHY1_CFG		(CRG_REG_BASE + PERI_CRG3644)
#define USB3_PHY_CFG		(CRG_REG_BASE + PERI_CRG3664)
#define USB2_PHY2_CFG		(CRG_REG_BASE + PERI_CRG3672)
#define USB3_COMBPHY_CFG	(CRG_REG_BASE + PERI_CRG3676)

/* USB PHY register offset and config */
#define	PHY_PLL_OFFSET		0x14
#define	PHY_PLL_ENABLE		(0x3 << 0)

#define U2_ANA_CFG0		0x0
#define HSTX_MBIAS_MASK	(0xf << 0)
#define ana_cfg0_val(p)	((p) & (~HSTX_MBIAS_MASK))
#define U2_2_HSTX_MBIAS	(0x3 << 0)
#define U2_1_HSTX_MBIAS	(0xb << 0)
#define U2_0_HSTX_MBIAS	(0xb << 0)

#define U2_ANA_CFG2		0x8
#define VDISCREF_SEL_MASK	(0x7 << 16)
#define ana_cfg2_val(p)	((p) & (~VDISCREF_SEL_MASK))
#define U2_2_VDISCREF_SEL	(0x2 << 16)
#define U2_1_VDISCREF_SEL	(0x5 << 16)
#define U2_0_VDISCREF_SEL	(0x5 << 16)
#define U2_TEST_TX		(0x1 << 20)

#define U2_TRIM_VAL_MIN	0x09
#define U2_TRIM_VAL_MAX	0x1d
#define RT_TRIM_VAL_MASK	0x1f
#define usb2_2_trim_val(p)	(((p) >> 10) & RT_TRIM_VAL_MASK)
#define usb2_1_trim_val(p)	(((p) >> 5) & RT_TRIM_VAL_MASK)
#define usb2_0_trim_val(p)	(((p) >> 0) & RT_TRIM_VAL_MASK)

#define usb2_rt_trim_clr(p)	((p) & (~(RT_TRIM_VAL_MASK << 8)))
#define usb2_rt_trim_set(p)	((p) << 8)

#define U2_ANA_CFG3		0xc
#define SLEW_RATE_OPT_MASK	(0x3 << 20)
#define ana_cfg3_val(p)	((p) & (~SLEW_RATE_OPT_MASK))
#define U2_2_SLEW_RATE_OPT	(0x1 << 20)
#define U2_1_SLEW_RATE_OPT	(0x1 << 20)
#define U2_0_SLEW_RATE_OPT	(0x1 << 20)

#define U2_ANA_CFG4		0x10
#define VTXREF_SEL_MASK	(0x7 << 4)
#define ana_cfg4_val(p)	((p) & (~VTXREF_SEL_MASK))
#define U2_VTXREF_SEL		(0x6 << 4)
#define U2_FLS_EDGE_MODE	(0x1 << 13)

#define PI_CURRENT_TRIM_ENABLE 0x11100
#define PI_CURRENT_TRIM_VAL    0x11101
#define TX_SWING_COMP_ENABLE   0xc1200
#define TX_SWING_COMP_VAL      0xc1201

/* -------------------------------------------------------------------- */
/* PCIE */
/* -------------------------------------------------------------------- */
#define SYS_SATA			0x8c
#define PCIE_MODE			12

#define PERI_CRG98			0x188
#define phy0_srs_req			0
#define phy0_srs_req_sel		1
#define phy1_srs_req			16
#define phy1_srs_req_sel		17

#define MISC_CTRL5			0x14

/* -------------------------------------------------------------------- */
/* GZIP */
/* -------------------------------------------------------------------- */
#define HW_DEC_INTR             (183)

/* --------------------------------------------------------- */
#define NUM_0                                   0
#define NUM_1                                   1
#define NUM_2                                   2
#define NUM_3                                   3
#define NUM_4                                   4
#define NUM_5                                   5
#define NUM_6                                   6
#define NUM_7                                   7
#define NUM_8                                   8
#define NUM_9                                   9

#endif /* End of __HI_CHIP_REGS_H__ */
