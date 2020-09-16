#ifndef __USB3_HW_H__
#define __USB3_HW_H__

#include "usb3.h"

/****************************************************************************/
/* Core Global Registers */

/**
 * This enum represents the bit fields of the Core SoC Bus Configuration 0
 * Register (GSBUSCFG0).
 */
typedef enum gsbuscfg0_data {
	/** Bus Burst Len			<i>Access: R_W</i>.
	 * - 0:   single
	 * - 1:   incr
	 * - 3:   incr4
	 * - 7:   incr8
	 * - 15:  incr16
	 * - 31:  incr32  (non-AHB mode only)
	 * - 63:  incr64  (non-AHB mode only)
	 * - 127: incr128 (non-AHB mode only)
	 * - 255: incr256 (non-AHB mode only)
	 */
	USB3_SBUSCFG0_HBURSTLEN_BITS		= 0x000000ff,
	USB3_SBUSCFG0_HBURSTLEN_SHIFT		= 0,

	USB3_SBUSCFG0_INT_DMA_BURST_SINGLE	= 0,
	USB3_SBUSCFG0_INT_DMA_BURST_INCR    = 1,
	USB3_SBUSCFG0_INT_DMA_BURST_INCR4	= 3,
	USB3_SBUSCFG0_INT_DMA_BURST_INCR8	= 7,
	USB3_SBUSCFG0_INT_DMA_BURST_INCR16	= 15,
	USB3_SBUSCFG0_INT_DMA_BURST_INCR32	= 31,
	USB3_SBUSCFG0_INT_DMA_BURST_INCR64	= 63,
	USB3_SBUSCFG0_INT_DMA_BURST_INCR128	= 127,
	USB3_SBUSCFG0_INT_DMA_BURST_INCR256	= 255,

	/** Descriptor Write is Posted		<i>Access: R_W</i> */
	USB3_SBUSCFG0_DES_WR_POST_BIT		= 0x00000100,
	USB3_SBUSCFG0_DES_WR_POST_SHIFT		= 8,

	/** Data Write is Posted		<i>Access: R_W</i> */
	USB3_SBUSCFG0_DAT_WR_POST_BIT		= 0x00000200,
	USB3_SBUSCFG0_DAT_WR_POST_SHIFT		= 9,

	/** Descriptor Access is Big-Endian	<i>Access: R_W</i> */
	USB3_SBUSCFG0_DES_BIG_END_BIT		= 0x00000400,
	USB3_SBUSCFG0_DES_BIG_END_SHIFT		= 10,

	/** Data Access is Big-Endian		<i>Access: R_W</i> */
	USB3_SBUSCFG0_DAT_BIG_END_BIT		= 0x00000800,
	USB3_SBUSCFG0_DAT_BIG_END_SHIFT		= 11,

	/** Store and Forward Mode		<i>Access: R_W</i> */
	USB3_SBUSCFG0_STORE_AND_FORWARD_BIT	    = 0x00001000,
	USB3_SBUSCFG0_STORE_AND_FORWARD_SHIFT	= 12,

	/** Force Single Request		<i>Access: R_W</i> */
	USB3_SBUSCFG0_SING_REQ_BIT		    = 0x00004000,
	USB3_SBUSCFG0_SING_REQ_SHIFT		= 14,

	/** Descriptor Readback Enable		<i>Access: R_W</i> */
	USB3_SBUSCFG0_READ_AFTER_WRITE_BIT	    = 0x00008000,
	USB3_SBUSCFG0_READ_AFTER_WRITE_SHIFT	= 15,

	/** Descriptor Write Request Info	<i>Access: R_W</i> */
	USB3_SBUSCFG0_DES_WR_REQ_INFO_BITS	= 0x000f0000,
	USB3_SBUSCFG0_DES_WR_REQ_INFO_SHIFT	= 16,

	/** Data Write Request Info		<i>Access: R_W</i> */
	USB3_SBUSCFG0_DAT_WR_REQ_INFO_BITS	= 0x00f00000,
	USB3_SBUSCFG0_DAT_WR_REQ_INFO_SHIFT	= 20,

	/** Descriptor Read Request Info	<i>Access: R_W</i> */
	USB3_SBUSCFG0_DES_RD_REQ_INFO_BITS	= 0x0f000000,
	USB3_SBUSCFG0_DES_RD_REQ_INFO_SHIFT	= 24,

	/** Data Read Request Info		<i>Access: R_W</i> */
	USB3_SBUSCFG0_DAT_RD_REQ_INFO_BITS	= 0xf0000000,
	USB3_SBUSCFG0_DAT_RD_REQ_INFO_SHIFT	= 28,
} gsbuscfg0_data_t;

/**
 * This enum represents the bit fields of the Core SoC Bus Configuration 1
 * Register (GSBUSCFG1).
 */
typedef enum gsbuscfg1_data {
	/** OCP Address Space For Descriptor	<i>Access: R_W</i> */
	USB3_SBUSCFG1_DES_ADDR_SPC_BITS		= 0x0000000f,
	USB3_SBUSCFG1_DES_ADDR_SPC_SHIFT		= 0,

	/** OCP Address Space For Data		<i>Access: R_W</i> */
	USB3_SBUSCFG1_DAT_ADDR_SPC_BITS		= 0x000000f0,
	USB3_SBUSCFG1_DAT_ADDR_SPC_SHIFT		= 4,
} gsbuscfg1_data_t;

/**
 * This enum represents the bit fields of the Core Tx Threshold Control
 * Register (GTXTHRCFG).
 */
typedef enum gtxthrcfg_data {
	/** SoC Bus Transmit Threshold Length		<i>Access: R_W</i> */
	USB3_TXTHRCFG_SBUS_THR_LEN_BITS		= 0x000007ff,
	USB3_TXTHRCFG_SBUS_THR_LEN_SHIFT		= 0,

	/** SoC Bus Non-ISO Transmit Threshold Enable	<i>Access: R_W</i> */
	USB3_TXTHRCFG_SBUS_NON_ISO_THR_EN_BIT	= 0x00004000,
	USB3_TXTHRCFG_SBUS_NON_ISO_THR_EN_SHIFT	= 14,

	/** SoC Bus ISO Transmit Threshold Enable	<i>Access: R_W</i> */
	USB3_TXTHRCFG_SBUS_ISO_THR_EN_BIT	= 0x00008000,
	USB3_TXTHRCFG_SBUS_ISO_THR_EN_SHIFT	= 15,

	/** USB Transmit Threshold Length		<i>Access: R_W</i> */
	USB3_TXTHRCFG_USB_THR_LEN_BITS		= 0x1fff0000,
	USB3_TXTHRCFG_USB_THR_LEN_SHIFT		= 16,

	/** USB Non-ISO Transmit Threshold Enable	<i>Access: R_W</i> */
	USB3_TXTHRCFG_USB_NON_ISO_THR_EN_BIT	= 0x40000000,
	USB3_TXTHRCFG_USB_NON_ISO_THR_EN_SHIFT	= 30,

	/** USB ISO Transmit Threshold Enable		<i>Access: R_W</i> */
	USB3_TXTHRCFG_USB_ISO_THR_EN_BIT		= 0x80000000,
	USB3_TXTHRCFG_USB_ISO_THR_EN_SHIFT	= 31,
} gtxthrcfg_data_t;

/**
 * This enum represents the bit fields of the Core Rx Threshold Control
 * Register (GRXTHRCFG).
 */
typedef enum grxthrcfg_data {
	/** Receive Threshold Length		<i>Access: R_W</i> */
	USB3_RXTHRCTL_THR_LEN_BITS	= 0x07ff,
	USB3_RXTHRCTL_THR_LEN_SHIFT	= 0,

	/** Receive Threshold Enable		<i>Access: R_W</i> */
	USB3_RXTHRCTL_THR_EN_BIT		= 0x8000,
	USB3_RXTHRCTL_THR_EN_SHIFT	= 15,
} grxthrcfg_data_t;

/**
 * This enum represents the bit fields of the Core Control
 * Register (GCTL).
 */
typedef enum gctl_data {
	/** Disable Clock Gating		<i>Access: R_W</i> */
	USB3_GCTL_DSBL_CLCK_GTNG_BIT	= 0x00000001,
	USB3_GCTL_DSBL_CLCK_GTNG_SHIFT	= 0,

	/** Global Hibernation Enable		<i>Access: R_W</i> */
	USB3_GCTL_GBL_HIBER_EN_BIT	= 0x00000002,
	USB3_GCTL_GBL_HIBER_EN_SHIFT	= 1,

	/** U2Exit LFPS		                <i>Access: R_W</i> */
	USB3_GCTL_GBL_U2EXIT_LFPS	= 0x00000004,
	USB3_GCTL_GBL_U2EXIT_LFPS_SHIFT	= 2,

	/** Disable Scrambling			<i>Access: R_W</i> */
	USB3_GCTL_DIS_SCRAMBLE_BIT	= 0x00000008,
	USB3_GCTL_DIS_SCRAMBLE_SHIFT	= 3,

	/** Scale-down Mode			<i>Access: R_W</i> */
	USB3_GCTL_SCALE_DOWN_BITS	= 0x00000030,
	USB3_GCTL_SCALE_DOWN_SHIFT	= 4,

	/** RAM Clock Select			<i>Access: R_W</i> */
	USB3_GCTL_RAM_CLK_SEL_BITS	= 0x000000c0,
	USB3_GCTL_RAM_CLK_SEL_SHIFT	= 6,

	/** Debug Attach			<i>Access: R_W</i> */
	USB3_GCTL_DEBUG_ATTACH_BIT	= 0x00000100,
	USB3_GCTL_DEBUG_ATTACH_SHIFT	= 8,

	/** Loopback Enable			<i>Access: R_W</i> */
	USB3_GCTL_LPBK_EN_BIT		= 0x00000200,
	USB3_GCTL_LPBK_EN_SHIFT		= 9,

	/** Local Loopback Enable		<i>Access: R_W</i> */
	USB3_GCTL_LOCAL_LPBK_EN_BIT	= 0x00000400,
	USB3_GCTL_LOCAL_LPBK_EN_SHIFT	= 10,

	/** Core Soft Reset			<i>Access: R_W</i> */
	USB3_GCTL_CORE_SOFT_RST_BIT	= 0x00000800,
	USB3_GCTL_CORE_SOFT_RST_SHIFT	= 11,

	/** Port Capability Direction		<i>Access: R_W</i> */
	USB3_GCTL_PRT_CAP_DIR_BITS	= 0x00003000,
	USB3_GCTL_PRT_CAP_DIR_SHIFT	= 12,

	/** Port Capability Values */
	USB3_GCTL_PRT_CAP_HOST		= 1,
	USB3_GCTL_PRT_CAP_DEVICE		= 2,
	USB3_GCTL_PRT_CAP_OTG		= 3,

	/** Frame Scale Down			<i>Access: R_W</i> */
	USB3_GCTL_FRMSCLDWN_BITS		= 0x0000c000,
	USB3_GCTL_FRMSCLDWN_SHIFT	= 14,

	/** U2 Reset ECN			<i>Access: R_W</i> */
	USB3_GCTL_U2RSTECN_BIT		= 0x00010000,
	USB3_GCTL_U2RSTECN_SHIFT		= 16,

	/** Power Down Scale			<i>Access: R_W</i> */
	USB3_GCTL_PWR_DN_SCALE_BITS	= 0xfff80000,
	USB3_GCTL_PWR_DN_SCALE_SHIFT	= 19,
} gctl_data_t;

/**
 * This enum represents the bit fields of the Core Interrupt Mask
 * Register (GEVTEN).
 */
typedef enum gevten_data {
	/** ULPI Carkit Event Enable		<i>Access: R_W</i> */
	USB3_GEVTEN_ULPI_CK_EVT_EN_BIT	= 0x00000001,
	USB3_GEVTEN_ULPI_CK_EVT_SHIFT	= 0,

	/** I2C Event Enable			<i>Access: R_W</i> */
	USB3_GEVTEN_I2C_EVT_EN_BIT	= 0x00000002,
	USB3_GEVTEN_I2C_EVT_EN_SHIFT	= 1,
} gevten_data_t;

/**
 * This enum represents the bit fields of the Core Status
 * Register (GSTS).
 */
typedef enum gsts_data {
	/** Current Mode			<i>Access: RO</i>.
	 * - 0: Device Mode
	 * - 1: Host Mode
	 * - 2: DRD Mode
	 */
	USB3_GSTS_CURMODE_BITS		= 0x00000003,
	USB3_GSTS_CURMODE_SHIFT		= 0,

	USB3_GSTS_DEVICE_MODE		= 0,
	USB3_GSTS_HOST_MODE		= 1,
	USB3_GSTS_DRD_MODE		= 2,

	/** Bus Error Address Valid		<i>Access: RO</i> */
	USB3_GSTS_BUS_ERR_ADDR_VLD_BIT	= 0x00000010,
	USB3_GSTS_BUS_ERR_ADDR_VLD_SHIFT	= 4,

	/** CSR Timeout */
	USB3_GSTS_CSR_TIMEOUT_BIT	= 0x00000020,
	USB3_GSTS_CSR_TIMEOUT_SHIFT	= 5,

	/** Device Interrupt Pending */
	USB3_GSTS_DEV_EVT_PENDING_BIT	= 0x00000040,
	USB3_GSTS_DEV_EVT_PENDING_SHIFT	= 6,

	/** Host Interrupt Pending */
	USB3_GSTS_HOST_EVT_PENDING_BIT	= 0x00000080,
	USB3_GSTS_HOST_EVT_PENDING_SHIFT	= 7,

	/** ADP Interrupt Pending */
	USB3_GSTS_ADP_EVT_PENDING_BIT	= 0x00000100,
	USB3_GSTS_ADP_EVT_PENDING_SHIFT	= 8,

	/** BC Interrupt Pending */
	USB3_GSTS_BC_EVT_PENDING_BIT	= 0x00000200,
	USB3_GSTS_BC_EVT_PENDING_SHIFT	= 9,

	/** OTG Interrupt Pending */
	USB3_GSTS_OTG_EVT_PENDING_BIT	= 0x00000400,
	USB3_GSTS_OTG_EVT_PENDING_SHIFT	= 10,

	/** Current BELT Value			<i>Access: RO</i> */
	USB3_GSTS_CBELT_BITS		= 0xfff00000,
	USB3_GSTS_CBELT_SHIFT		= 20,
} gsts_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 0
 * Register (GHWPARAMS0).
 */
typedef enum ghwparams0_data {
	USB3_HWP0_MODE_BITS		= 0x00000007,
	USB3_HWP0_MODE_SHIFT		= 0,

	USB3_HWP0_MBUS_TYPE_BITS		= 0x00000038,
	USB3_HWP0_MBUS_TYPE_SHIFT	= 3,

	USB3_HWP0_SBUS_TYPE_BITS		= 0x000000c0,
	USB3_HWP0_SBUS_TYPE_SHIFT	= 6,

	USB3_HWP0_MDWIDTH_BITS		= 0x0000ff00,
	USB3_HWP0_MDWIDTH_SHIFT		= 8,

	USB3_HWP0_SDWIDTH_BITS		= 0x00ff0000,
	USB3_HWP0_SDWIDTH_SHIFT		= 16,

	USB3_HWP0_AWIDTH_BITS		= 0x3f000000,
	USB3_HWP0_AWIDTH_SHIFT		= 24,
} ghwparams0_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 1
 * Register (GHWPARAMS1).
 */
typedef enum ghwparams1_data {
	USB3_HWP1_IDWIDTH_M1_BITS		= 0x00000007,
	USB3_HWP1_IDWIDTH_M1_SHIFT		= 0,

	USB3_HWP1_BURSTWIDTH_M1_BITS		= 0x00000038,
	USB3_HWP1_BURSTWIDTH_M1_SHIFT		= 3,

	USB3_HWP1_DATAINFOWIDTH_BITS		= 0x000001c0,
	USB3_HWP1_DATAINFOWIDTH_SHIFT		= 6,

	USB3_HWP1_REQINFOWIDTH_BITS		= 0x00000e00,
	USB3_HWP1_REQINFOWIDTH_SHIFT		= 9,

	USB3_HWP1_ASPACEWIDTH_BITS		= 0x00007000,
	USB3_HWP1_ASPACEWIDTH_SHIFT		= 12,

	USB3_HWP1_DEV_NUM_INT_BITS		= 0x001f8000,
	USB3_HWP1_DEV_NUM_INT_SHIFT		= 15,

	USB3_HWP1_NUM_RAMS_BITS			= 0x00600000,
	USB3_HWP1_NUM_RAMS_SHIFT			= 21,

	USB3_HWP1_SPRAM_TYP_BIT			= 0x00800000,
	USB3_HWP1_SPRAM_TYP_SHIFT		= 23,

	USB3_HWP1_EN_PWROPT_BITS			= 0x03000000,
	USB3_HWP1_EN_PWROPT_SHIFT		= 24,

	USB3_EN_PWROPT_NONE		= 0,
	USB3_EN_PWROPT_CLK_GATING_ONLY	= 1,
	USB3_EN_PWROPT_HIBERNATION	= 2,

	USB3_HWP1_MAC_PHY_CLKS_SYNC_BIT		= 0x04000000,
	USB3_HWP1_MAC_PHY_CLKS_SYNC_SHIFT	= 26,

	USB3_HWP1_MAC_RAM_CLKS_SYNC_BIT		= 0x08000000,
	USB3_HWP1_MAC_RAM_CLKS_SYNC_SHIFT	= 27,

	USB3_HWP1_RAM_BUS_CLKS_SYNC_BIT		= 0x10000000,
	USB3_HWP1_RAM_BUS_CLKS_SYNC_SHIFT	= 28,

	USB3_HWP1_RM_OPT_FEATURES_BIT		= 0x40000000,
	USB3_HWP1_RM_OPT_FEATURES_SHIFT		= 30,
} ghwparams1_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 2
 * Register (GHWPARAMS2).
 */
typedef enum ghwparams2_data {
	USB3_HWP2_USERID_BITS	= 0xffffffff,
	USB3_HWP2_USERID_SHIFT	= 0,
} ghwparams2_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 3
 * Register (GHWPARAMS3).
 */
typedef enum ghwparams3_data {
	USB3_HWP3_SSPHY_IFC_BITS		= 0x00000003,
	USB3_HWP3_SSPHY_IFC_SHIFT	= 0,

	USB3_HWP3_HSPHY_IFC_BITS		= 0x0000000c,
	USB3_HWP3_HSPHY_IFC_SHIFT	= 2,

	USB3_HWP3_FSPHY_IFC_BITS		= 0x00000030,
	USB3_HWP3_FSPHY_IFC_SHIFT	= 4,

	USB3_HWP3_HSPHY_DWIDTH_BITS	= 0x000000c0,
	USB3_HWP3_HSPHY_DWIDTH_SHIFT	= 6,

	USB3_HWP3_VEND_CTL_IFC_BIT	= 0x00000400,
	USB3_HWP3_VEND_CTL_IFC_SHIFT	= 10,

	USB3_HWP3_ULPI_CARKIT_BIT	= 0x00000800,
	USB3_HWP3_ULPI_CARKIT_SHIFT	= 11,

	USB3_HWP3_NUM_EPS_BITS		= 0x0003f000,
	USB3_HWP3_NUM_EPS_SHIFT		= 12,

	USB3_HWP3_NUM_IN_EPS_BITS	= 0x007c0000,
	USB3_HWP3_NUM_IN_EPS_SHIFT	= 18,

	USB3_HWP3_TOT_XFR_RSRC_BITS	= 0x7f800000,
	USB3_HWP3_TOT_XFR_RSRC_SHIFT	= 23,
} ghwparams3_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 4
 * Register (GHWPARAMS4).
 */
typedef enum ghwparams4_data {
	USB3_HWP4_TRBS_PER_XFER_BITS	= 0x0000003f,
	USB3_HWP4_TRBS_PER_XFER_SHIFT	= 0,

	USB3_HWP4_HIBER_SPAD_BITS	= 0x0001e000,
	USB3_HWP4_HIBER_SPAD_SHIFT	= 13,

	USB3_HWP4_NUM_SS_USB_INST_BITS	= 0x001e0000,
	USB3_HWP4_NUM_SS_USB_INST_SHIFT	= 17,

	USB3_HWP4_EN_ISOC_SUPT_BIT	= 0x00800000,
	USB3_HWP4_EN_ISOC_SUPT_SHIFT	= 23,

	USB3_HWP4_BMU_PTL_DEPTH_BITS	= 0x0f000000,
	USB3_HWP4_BMU_PTL_DEPTH_SHIFT	= 24,

	USB3_HWP4_BMU_LSP_DEPTH_BITS	= 0xf0000000,
	USB3_HWP4_BMU_LSP_DEPTH_SHIFT	= 28,
} ghwparams4_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 5
 * Register (GHWPARAMS5).
 */
typedef enum ghwparams5_data {
	USB3_HWP5_BMU_BUSGM_DEPTH_BITS	= 0x0000000f,
	USB3_HWP5_BMU_BUSGM_DEPTH_SHIFT	= 0,

	USB3_HWP5_RXQ_FIFO_DEPTH_BITS	= 0x000003f0,
	USB3_HWP5_RXQ_FIFO_DEPTH_SHIFT	= 4,

	USB3_HWP5_TXQ_FIFO_DEPTH_BITS	= 0x0000fc00,
	USB3_HWP5_TXQ_FIFO_DEPTH_SHIFT	= 10,

	USB3_HWP5_DWQ_FIFO_DEPTH_BITS	= 0x003f0000,
	USB3_HWP5_DWQ_FIFO_DEPTH_SHIFT	= 16,

	USB3_HWP5_DFQ_FIFO_DEPTH_BITS	= 0x0fc00000,
	USB3_HWP5_DFQ_FIFO_DEPTH_SHIFT	= 22,
} ghwparams5_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 6
 * Register (GHWPARAMS6).
 */
typedef enum ghwparams6_data {
	USB3_HWP6_PSQ_FIFO_DEPTH_BITS	= 0x0000003f,
	USB3_HWP6_PSQ_FIFO_DEPTH_SHIFT	= 0,

	USB3_HWP6_EN_DBG_PORTS_BIT	= 0x00000040,
	USB3_HWP6_EN_DBG_PORTS_SHIFT	= 6,

	USB3_HWP6_EN_FPGA_BIT		= 0x00000080,
	USB3_HWP6_EN_FPGA_SHIFT		= 7,

	USB3_HWP6_EN_SRP_BIT		= 0x00000400,
	USB3_HWP6_EN_SRP_SHIFT		= 10,

	USB3_HWP6_EN_HNP_BIT		= 0x00000800,
	USB3_HWP6_EN_HNP_SHIFT		= 11,

	USB3_HWP6_EN_ADP_BIT		= 0x00001000,
	USB3_HWP6_EN_ADP_SHIFT		= 12,

	USB3_HWP6_EN_OTG_BIT		= 0x00002000,
	USB3_HWP6_EN_OTG_SHIFT		= 13,

	USB3_HWP6_EN_BC_BIT		= 0x00004000,
	USB3_HWP6_EN_BC_SHIFT		= 14,

	USB3_HWP6_EN_BUS_FILTERS_BIT	= 0x00008000,
	USB3_HWP6_EN_BUS_FILTERS_SHIFT	= 15,

	USB3_HWP6_RAM0_DEPTH_BITS	= 0xffff0000,
	USB3_HWP6_RAM0_DEPTH_SHIFT	= 16,
} ghwparams6_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 7
 * Register (GHWPARAMS7).
 */
typedef enum ghwparams7_data {
	USB3_HWP7_RAM1_DEPTH_BITS	= 0x0000ffff,
	USB3_HWP7_RAM1_DEPTH_SHIFT	= 0,

	USB3_HWP7_RAM2_DEPTH_BITS	= 0xffff0000,
	USB3_HWP7_RAM2_DEPTH_SHIFT	= 16,
} ghwparams7_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 8
 * Register (GHWPARAMS8).
 */
typedef enum ghwparams8_data {
	USB3_HWP8_DCACHE_DEPTH_BITS	= 0xffffffff,
	USB3_HWP8_DCACHE_DEPTH_SHIFT	= 0,
} ghwparams8_data_t;

/**
 * This enum represents the bit fields of the Debug Queue/FIFO Space
 * Register (GDBGFIFOSPACE).
 */
typedef enum gdbgfifospace_data {
	/** FIFO/Queue Select			<i>Access: R_W</i> */
	USB3_DBGFIFOSPACE_FIFO_QUEUE_SEL_BITS	= 0x000000ff,
	USB3_DBGFIFOSPACE_FIFO_QUEUE_SEL_SHIFT	= 0,

	/*   0 - 31  TxFIFO Number   */
	/*  32 - 63  RxFIFO Number   */
	/*  64 - 95  TxReqQ Number   */
	/*  96 - 127 RxReqQ Number   */
	/* 128 - 159 RxInfoQ Number  */
	/* 160       DescFetchQ      */
	/* 161       EventQ          */
	/* 162       ProtocolStatusQ */

	/** Space Available			<i>Access: R</i> */
	USB3_DBGFIFOSPACE_SPACE_AVAIL_BITS	= 0xffff0000,
	USB3_DBGFIFOSPACE_SPACE_AVAIL_SHIFT	= 16,
} gdbgfifospace_data_t;

/**
 * This enum represents the bit fields of the Debug LTSSM
 * Register (GDBGLTSSM).
 */
typedef enum gdbgltssm_data {
	/** Pipe Status				<i>Access: R</i> */
	USB3_DBGLTSSM_PIPE_STATUS_BITS		= 0x0003ffff,
	USB3_DBGLTSSM_PIPE_STATUS_SHIFT		= 0,

	/** LTDB SubState			<i>Access: R</i> */
	USB3_DBGLTSSM_LTDB_SUB_STATE_BITS	= 0x003c0000,
	USB3_DBGLTSSM_LTDB_SUB_STATE_SHIFT	= 18,

	/** LTDB State				<i>Access: R</i> */
	USB3_DBGLTSSM_LTDB_STATE_BITS		= 0x03c00000,
	USB3_DBGLTSSM_LTDB_STATE_SHIFT		= 22,

	/** LTDB Timeout			<i>Access: R</i> */
	USB3_DBGLTSSM_LTDB_TIMEOUT_BIT		= 0x04000000,
	USB3_DBGLTSSM_LTDB_TIMEOUT_SHIFT		= 26,
} gdbgltssm_data_t;

/**
 * This enum represents the bit fields of the Core USB2 PHY Configuration
 * Registers (GUSB2PHYCFGn).
 */
typedef enum gusb2phycfg_data {
	/** HS/FS Timeout Calibration			<i>Access: R_W</i> */
	USB3_USB2PHYCFG_TOUT_CAL_BITS		= 0x00000007,
	USB3_USB2PHYCFG_TOUT_CAL_SHIFT		= 0,

	/** UTMI+ PHY Intf Width (8-bit/16-bit) SelecT	<i>Access: R_W</i> */
	USB3_USB2PHYCFG_PHY_IF_BIT		= 0x00000008,
	USB3_USB2PHYCFG_PHY_IF_SHIFT		= 3,
	/*--------*/
	/** ULPI DDR Select				<i>Access: R_W</i> */
	USB3_USB2PHYCFG_DDR_SEL_BIT		= 0x00000008,
	USB3_USB2PHYCFG_DDR_SEL_SHIFT		= 3,

	/** UTMI+ / ULPI Select				<i>Access: R_W</i> */
	USB3_USB2PHYCFG_UTMI_ULPI_BIT		= 0x00000010,
	USB3_USB2PHYCFG_UTMI_ULPI_SHIFT		= 4,

	/** Full-speed Serial Interface Select		<i>Access: R_W</i> */
	USB3_USB2PHYCFG_FSINTF_BIT		= 0x00000020,
	USB3_USB2PHYCFG_FSINTF_SHIFT		= 5,

	/** Suspend USB2 Phy				<i>Access: R_W</i> */
	USB3_USB2PHYCFG_SUS_PHY_BIT		= 0x00000040,
	USB3_USB2PHYCFG_SUS_PHY_SHIFT		= 6,

	/** USB2.0 HS PHY/USB1.1 FS Serial Xcvr Select	<i>Access: R_W</i> */
	USB3_USB2PHYCFG_PHY_SEL_BIT		= 0x00000080,
	USB3_USB2PHYCFG_PHY_SEL_SHIFT		= 7,

	/** Enable UTMI Sleep				<i>Access: R_W</i> */
	USB3_USB2PHYCFG_ENBL_SLP_M_BIT		= 0x00000100,
	USB3_USB2PHYCFG_ENBL_SLP_M_SHIFT		= 8,

	/** USB2.0 Turnaround Time			<i>Access: R_W</i> */
	USB3_USB2PHYCFG_USB_TRD_TIM_BITS		= 0x00003c00,
	USB3_USB2PHYCFG_USB_TRD_TIM_SHIFT	= 10,

	/** PHY Low-power Clock Select			<i>Access: R_W</i> */
	USB3_USB2PHYCFG_PHY_LPWR_CLK_SEL_BIT	= 0x00004000,
	USB3_USB2PHYCFG_PHY_LPWR_CLK_SEL_SHIFT	= 14,

	/** ULPI Auto Resume				<i>Access: R_W</i> */
	USB3_USB2PHYCFG_ULPI_AUTO_RES_BIT	= 0x00008000,
	USB3_USB2PHYCFG_ULPI_AUTO_RES_SHIFT	= 15,

	/** ULPI Clock SuspendM				<i>Access: R_W</i> */
	USB3_USB2PHYCFG_ULPI_CLK_SUS_M_BIT	= 0x00010000,
	USB3_USB2PHYCFG_ULPI_CLK_SUS_M_SHIFT	= 16,

	/** ULPI External Vbus Drive			<i>Access: R_W</i> */
	USB3_USB2PHYCFG_ULPI_EXT_VBUS_DRV_BIT	= 0x00020000,
	USB3_USB2PHYCFG_ULPI_EXT_VBUS_DRV_SHIFT	= 17,

	/** ULPI External Vbus Indicator		<i>Access: R_W</i> */
	USB3_USB2PHYCFG_ULPI_EXT_VBUS_IND_BIT	= 0x00040000,
	USB3_USB2PHYCFG_ULPI_EXT_VBUS_IND_SHIFT	= 18,

	/** PHY Interrupt Number			<i>Access: R_W</i> */
	USB3_USB2PHYCFG_PHY_INTR_NUM_BITS	= 0x01f80000,
	USB3_USB2PHYCFG_PHY_INTR_NUM_SHIFT	= 19,

	/** OTG Interrupt Number			<i>Access: R_W</i> */
	USB3_USB2PHYCFG_OTG_INTR_NUM_BITS	= 0x7e000000,
	USB3_USB2PHYCFG_OTG_INTR_NUM_SHIFT	= 25,

	/** PHY Soft Reset				<i>Access: R_W</i> */
	USB3_USB2PHYCFG_PHY_SOFT_RST_BIT		= 0x80000000,
	USB3_USB2PHYCFG_PHY_SOFT_RST_SHIFT	= 31,
} gusb2phycfg_data_t;

/**
 * This enum represents the bit fields in the USB2 I2C Control
 * Registers (GUSB2I2CCTLn).
 */
typedef enum gusb2i2cctl_data {
	/** All bits are reserved */
	USB3_USB2I2C_RSVD_BITS		= 0xffffffff,
	USB3_USB2I2C_RSVD_SHIFT		= 0,
} gusb2i2cctl_data_t;

/**
 * This enum represents the bit fields in the USB2 Phy Vendor Control
 * Registers (GUSB2PHYACCn).
 */
typedef enum gusb2phyacc_data {
	/** Register Data			<i>Access: R_W</i> */
	USB3_USB2PHY_REGDATA_BITS	= 0x000000ff,
	USB3_USB2PHY_REGDATA_SHIFT	= 0,

	/** UTMI+ Vendor Ctrl Register Address	<i>Access: R_W</i> */
	USB3_USB2PHY_VCTRL_BITS		= 0x0000ff00,
	USB3_USB2PHY_VCTRL_SHIFT		= 8,
	/*--------*/
	/** ULPI Extended Register Address	<i>Access: R_W</i> */
	USB3_USB2PHY_EXTREGADDR_BITS	= 0x00003f00,
	USB3_USB2PHY_EXTREGADDR_SHIFT	= 8,

	/** Register Address			<i>Access: R_W</i> */
	USB3_USB2PHY_REGADDR_BITS	= 0x003f0000,
	USB3_USB2PHY_REGADDR_SHIFT	= 16,

	/** Register Write			<i>Access: R_W</i> */
	USB3_USB2PHY_REGWR_BIT		= 0x00400000,
	USB3_USB2PHY_REGWR_SHIFT		= 22,

	/** VStatus Busy			<i>Access: RO</i> */
	USB3_USB2PHY_VSTSBSY_BIT		= 0x00800000,
	USB3_USB2PHY_VSTSBSY_SHIFT	= 23,

	/** VStatus Done			<i>Access: R_SS_SC</i> */
	USB3_USB2PHY_VSTSDONE_BIT	= 0x01000000,
	USB3_USB2PHY_VSTSDONE_SHIFT	= 24,

	/** New Register Request		<i>Access: R_WS_SC</i> */
	USB3_USB2PHY_NEWREGREQ_BIT	= 0x02000000,
	USB3_USB2PHY_NEWREGREQ_SHIFT	= 25,

	/** Disable ULPI Drivers		<i>Access: R_WS_SC</i> */
	USB3_USB2PHY_DIS_ULPI_DRVR_BIT	= 0x04000000,
	USB3_USB2PHY_DIS_ULPI_DRVR_SHIFT	= 26,
} gusb2phyacc_data_t;

/**
 * This enum represents the bit fields of the USB3 Pipe Control
 * Registers (GUSB3PIPECTLn).
 */
typedef enum gusb3pipectl_data {
	/** Elastic Buffer Mode			<i>Access: R_W</i> */
	USB3_PIPECTL_ELAS_BUF_MODE_BIT		= 0x00000001,
	USB3_PIPECTL_ELAS_BUF_MODE_SHIFT		= 0,

	/** Tx De-Emphasis			<i>Access: R_W</i> */
	USB3_PIPECTL_TX_DEMPH_BITS		= 0x00000006,
	USB3_PIPECTL_TX_DEMPH_SHIFT		= 1,

	/** Tx Margin				<i>Access: R_W</i> */
	USB3_PIPECTL_TX_MARGIN_BITS		= 0x00000038,
	USB3_PIPECTL_TX_MARGIN_SHIFT		= 3,

	/** Tx Swing				<i>Access: R_W</i> */
	USB3_PIPECTL_TX_SWING_BIT		= 0x00000040,
	USB3_PIPECTL_TX_SWING_SHIFT		= 6,

	/** Port Operation Direction		<i>Access: R_W</i> */
	USB3_PIPECTL_PRT_OP_DIR_BITS		= 0x00000180,
	USB3_PIPECTL_PRT_OP_DIR_SHIFT		= 7,

	/** LFPS Filter				<i>Access: R_W</i> */
	USB3_PIPECTL_LFPS_FILTER_BIT		= 0x00000200,
	USB3_PIPECTL_LFPS_FILTER_SHIFT		= 9,

	/** P3 Exit Signal In P2		<i>Access: R_W</i> */
	USB3_PIPECTL_P3_EX_SIG_P2_BIT		= 0x00000400,
	USB3_PIPECTL_P3_EX_SIG_P2_SHIFT		= 10,

	/** P3-P2 Transitions OK		<i>Access: R_W</i> */
	USB3_PIPECTL_P3_P2_TRAN_OK_BIT		= 0x00000800,
	USB3_PIPECTL_P3_P2_TRAN_OK_SHIFT		= 11,

	/** LFPS P0 Align			<i>Access: R_W</i> */
	USB3_PIPECTL_LFPS_P0_ALGN_BIT		= 0x00001000,
	USB3_PIPECTL_LFPS_P0_ALGN_SHIFT		= 12,

	/** Pipe Data Width			<i>Access: R_W</i> */
	USB3_PIPECTL_DATA_WIDTH_BITS		= 0x00018000,
	USB3_PIPECTL_DATA_WIDTH_SHIFT		= 15,

	/** Suspend USB3 Phy			<i>Access: R_W</i> */
	USB3_PIPECTL_SUS_PHY_BIT			= 0x00020000,
	USB3_PIPECTL_SUS_PHY_SHIFT		= 17,

	/** PHY Soft Reset			<i>Access: R_W</i> */
	USB3_PIPECTL_PHY_SOFT_RST_BIT		= 0x80000000,
	USB3_PIPECTL_PHY_SOFT_RST_SHIFT		= 31,
} gusb3pipectl_data_t;

/**
 * This enum represents the bit fields in the FIFO Size Registers.
 */
typedef enum gfifosize_data {
	/** Depth				<i>Access: R_W</i> */
	USB3_FIFOSZ_DEPTH_BITS		= 0x0000ffff,
	USB3_FIFOSZ_DEPTH_SHIFT		= 0,

	/** Starting Address			<i>Access: RO or R_W</i> */
	USB3_FIFOSZ_STARTADDR_BITS	= 0xffff0000,
	USB3_FIFOSZ_STARTADDR_SHIFT	= 16,
} gfifosize_data_t;

/**
 * This enum represents the bit fields of the Event Buffer Size
 * Registers (GEVENTSIZn).
 */
typedef enum geventsiz_data {
	/** Event Buffer Size			<i>Access: R_W</i> */
	USB3_EVENTSIZ_SIZ_BITS		= 0x0000ffff,
	USB3_EVENTSIZ_SIZ_SHIFT		= 0,

	/** Event Interrupt Mask (1 == disable)	<i>Access: R_W</i> */
	USB3_EVENTSIZ_INT_MSK_BIT	= 0x80000000,
	USB3_EVENTSIZ_INT_MSK_SHIFT	= 31,
} geventsiz_data_t;

/**
 * This enum represents the bit fields of the Event Buffer Count
 * Registers (GEVENTCNTn).
 */
typedef enum geventcnt_data {
	/** Event Count				<i>Access: R_W</i> */
	USB3_EVENTCNT_CNT_BITS		= 0x0000ffff,
	USB3_EVENTCNT_CNT_SHIFT		= 0,
} geventcnt_data_t;

/**
 * This enum represents the bit fields of a generic Event Buffer entry.
 */
typedef enum gevent_data {
	/** Non-Endpoint Specific Event flag */
	USB3_EVENT_NON_EP_BIT			= 0x01,
	USB3_EVENT_NON_EP_SHIFT			= 0,

	/** Non-Endpoint Specific Event Type */
	USB3_EVENT_INTTYPE_BITS			= 0xfe,
	USB3_EVENT_INTTYPE_SHIFT			= 1,

	/** Non-Endpoint Specific Event Type values */
	USB3_EVENT_DEV_INT		= 0,	/** @< */
	USB3_EVENT_OTG_INT		= 1,	/** @< */
	USB3_EVENT_CARKIT_INT		= 3,	/** @< */
	USB3_EVENT_I2C_INT		= 4,
} gevent_data_t;

/**
 * This enum represents the non-generic bit fields of an Event Buffer entry
 * for Device Specific events (DEVT).
 */
typedef enum devt_data {
	/** Device Specific Event Type */
	USB3_DEVT_BITS				= 0x00000f00,
	USB3_DEVT_SHIFT				= 8,

	/** Device Specific Event Type values */
	USB3_DEVT_DISCONN		= 0,	/** @< */
	USB3_DEVT_USBRESET		= 1,	/** @< */
	USB3_DEVT_CONNDONE		= 2,	/** @< */
	USB3_DEVT_ULST_CHNG		= 3,	/** @< */
	USB3_DEVT_WKUP			= 4,	/** @< */
	USB3_DEVT_HIBER_REQ		= 5,	/** @< */
	USB3_DEVT_EOPF			= 6,	/** @< */
	USB3_DEVT_SOF			= 7,	/** @< */
	USB3_DEVT_ERRATICERR		= 9,	/** @< */
	USB3_DEVT_CMD_CMPL		= 10,	/** @< */
	USB3_DEVT_OVERFLOW		= 11,	/** @< */
	USB3_DEVT_VNDR_DEV_TST_RCVD	= 12,	/** @< */
	USB3_DEVT_INACT_TIMEOUT_RCVD	= 13,

	/** Event Information */
	USB3_DEVT_EVT_INFO_BITS			= 0xffff0000,
	USB3_DEVT_EVT_INFO_SHIFT			= 16,

	/** USB/Link State */
	USB3_DEVT_ULST_STATE_BITS		= 0x000f0000,
	USB3_DEVT_ULST_STATE_SHIFT		= 16,

	/** USB/Link State values in SS */
	USB3_LINK_STATE_U0		= 0,	/** @< */
	USB3_LINK_STATE_U1		= 1,	/** @< */
	USB3_LINK_STATE_U2		= 2,	/** @< */
	USB3_LINK_STATE_U3		= 3,	/** @< */
	USB3_LINK_STATE_SS_DIS		= 4,	/** @< */
	USB3_LINK_STATE_RX_DET		= 5,	/** @< */
	USB3_LINK_STATE_SS_INACT		= 6,	/** @< */
	USB3_LINK_STATE_POLL		= 7,	/** @< */
	USB3_LINK_STATE_RECOV		= 8,	/** @< */
	USB3_LINK_STATE_HRESET		= 9,	/** @< */
	USB3_LINK_STATE_CMPLY		= 10,	/** @< */
	USB3_LINK_STATE_LPBK		= 11,	/** @< */
	USB3_LINK_STATE_RESET		= 14,	/** @< */
	USB3_LINK_STATE_RESUME		= 15,

	/** USB/Link State values in HS/FS/LS */
	USB3_LINK_STATE_ON		    = 0,	/** @< */
	USB3_LINK_STATE_SLEEP		= 2,	/** @< */
	USB3_LINK_STATE_SUSPEND		= 3,	/** @< */
	USB3_LINK_STATE_EARLY_SUSPEND	= 5,

	USB3_DEVT_ULST_SS_BIT			= 0x00100000,
	USB3_DEVT_ULST_SS_SHIFT			= 20,

#define USB3_DEVT_HIBER_STATE_BITS	USB3_DEVT_ULST_STATE_BITS
#define USB3_DEVT_HIBER_STATE_SHIFT	USB3_DEVT_ULST_STATE_SHIFT

#define USB3_DEVT_HIBER_SS_BIT		USB3_DEVT_ULST_SS_BIT
#define USB3_DEVT_HIBER_SS_SHIFT    USB3_DEVT_ULST_SS_SHIFT

	USB3_DEVT_HIBER_HIRD_BITS		= 0x0f000000,
	USB3_DEVT_HIBER_HIRD_SHIFT		= 24,
} devt_data_t;

/**
 * This enum represents the bit fields of an Event Buffer entry for
 * Endpoint Specific events (DEPEVT).
 */
typedef enum depevt_data {
	/** Endpoint Number */
	USB3_DEPEVT_EPNUM_BITS			= 0x0000003e,
	USB3_DEPEVT_EPNUM_SHIFT			= 1,

	/** Endpoint Event Type */
	USB3_DEPEVT_INTTYPE_BITS			= 0x000003c0,
	USB3_DEPEVT_INTTYPE_SHIFT		= 6,

	/** Endpoint Event Type values */
	USB3_DEPEVT_XFER_CMPL		    = 1,	/** @< */
	USB3_DEPEVT_XFER_IN_PROG		= 2,	/** @< */
	USB3_DEPEVT_XFER_NRDY		    = 3,	/** @< */
	USB3_DEPEVT_FIFOXRUN		    = 4,	/** @< */
	USB3_DEPEVT_STRM_EVT		    = 6,	/** @< */
	USB3_DEPEVT_EPCMD_CMPL		    = 7,

	/** Event Status for Start Xfer Command */
	USB3_DEPEVT_NO_MORE_RSCS_BIT		= 0x00001000,
	USB3_DEPEVT_NO_MORE_RSCS_SHIFT		= 12,
	USB3_DEPEVT_ISOC_TIME_PASSED_BIT    = 0x00002000,
	USB3_DEPEVT_ISOC_TIME_PASSED_SHIFT	= 13,

	/** Event Status for Stream Event */
	USB3_DEPEVT_STRM_EVT_BITS		= 0x0000f000,
	USB3_DEPEVT_STRM_EVT_SHIFT		= 12,

	/** Stream Event Status values */
	USB3_DEPEVT_STRM_FOUND		= 1,	/** @< */
	USB3_DEPEVT_STRM_NOT_FOUND	= 2,

	/** Event Status for Xfer Complete or Xfer In Progress Event */
	USB3_DEPEVT_BUS_ERR_BIT			= 0x00001000,
	USB3_DEPEVT_BUS_ERR_SHIFT		= 12,
	USB3_DEPEVT_SHORT_PKT_BIT		= 0x00002000,
	USB3_DEPEVT_SHORT_PKT_SHIFT		= 13,
	USB3_DEPEVT_IOC_BIT			    = 0x00004000,
	USB3_DEPEVT_IOC_SHIFT			= 14,
	USB3_DEPEVT_LST_BIT			    = 0x00008000,
	USB3_DEPEVT_LST_SHIFT			= 15,
#define USB3_DEPEVT_MISSED_ISOC_BIT	    USB3_DEPEVT_LST_BIT
#define USB3_DEPEVT_MISSED_ISOC_SHIFT	USB3_DEPEVT_LST_SHIFT

	/** Event Status for Xfer Not Ready Event */
	USB3_DEPEVT_CTRL_BITS			    = 0x00003000,
	USB3_DEPEVT_CTRL_SHIFT			    = 12,
	USB3_DEPEVT_XFER_ACTIVE_BIT		    = 0x00008000,
	USB3_DEPEVT_XFER_ACTIVE_SHIFT		= 15,

	/** Xfer Not Ready Event Status values */
	USB3_DEPEVT_CTRL_SETUP		= 0,	/** @< */
	USB3_DEPEVT_CTRL_DATA		= 1,	/** @< */
	USB3_DEPEVT_CTRL_STATUS		= 2,

	/** Stream ID */
	USB3_DEPEVT_STRM_ID_BITS			= 0xffff0000,
	USB3_DEPEVT_STRM_ID_SHIFT		    = 16,

	/** Isoc uFrame Number (for Xfer Not Ready on Isoc EP) */
	USB3_DEPEVT_ISOC_UFRAME_NUM_BITS    = 0xffff0000,
	USB3_DEPEVT_ISOC_UFRAME_NUM_SHIFT   = 16,

	/** Xfer Resource Index (for Start Xfer Command) */
	USB3_DEPEVT_XFER_RSC_IDX_BITS		= 0x007f0000,
	USB3_DEPEVT_XFER_RSC_IDX_SHIFT		= 16,

	/** Current Data Sequence Number (for Get Endpoint State Command) */
	USB3_DEPEVT_CUR_DAT_SEQ_NUM_BITS    = 0x001f0000,
	USB3_DEPEVT_CUR_DAT_SEQ_NUM_SHIFT	= 16,

	/** Flow Control State (for Get Endpoint State Command) */
	USB3_DEPEVT_FLOW_CTRL_BIT		= 0x00200000,
	USB3_DEPEVT_FLOW_CTRL_SHIFT		= 21,
} depevt_data_t;

/**
 * This enum represents the non-generic bit fields of an Event Buffer entry
 * for other Core events (GEVT).
 */
typedef enum gevt_data {
	/** PHY Port Number */
	USB3_GINT_PHY_PORT_BITS		= 0xf00,
	USB3_GINT_PHY_PORT_SHIFT		= 8,
} gevt_data_t;

/**
 * This struct represents the 32-bit register fields of the Event Buffer
 * Registers (GEVENTBUFn).
 */
typedef struct geventbuf_data {
	/** Event Buffer Address Register Low Word */
	volatile uint32_t geventadr_lo;

	/** Event Buffer Address Register High Word */
	volatile uint32_t geventadr_hi;

	/** Event Buffer Size Register.
	 * Fields defined in enum @ref geventsiz_data. */
	volatile uint32_t geventsiz;

	/** Event Buffer Count Register.
	 * Fields defined in enum @ref geventcnt_data. */
	volatile uint32_t geventcnt;
} geventbuf_data_t;

#define USB3_CORE_REG_BASE	0xC000

/**
 * Core Global Registers	<i>Offsets 100h-5FCh</i>.
 *
 * The dwc_usb3_core_global_regs structure defines the size
 * and relative field offsets for the Core Global Registers.
 */
typedef struct usb3_core_global_regs {

#define USB3_CORE_GLOBAL_REG_OFFSET	0x100

	/** Core BIU Configuration 0 Register	<i>Offset: 100h</i>.
	 * Fields defined in enum @ref gsbuscfg0_data. */
	volatile uint32_t gsbuscfg0;

	/** Core BIU Configuration 1 Register	<i>Offset: 104h</i>.
	 * Fields defined in enum @ref gsbuscfg1_data. */
	volatile uint32_t gsbuscfg1;

	/** Core Tx Threshold Control Register	<i>Offset: 108h</i>.
	 * Fields defined in enum @ref gtxthrcfg_data. */
	volatile uint32_t gtxthrcfg;

	/** Core Threshold Control Register	<i>Offset: 10Ch</i>.
	 * Fields defined in enum @ref grxthrcfg_data. */
	volatile uint32_t grxthrcfg;

	/** Core Control Register		<i>Offset: 110h</i>.
	 * Fields defined in enum @ref gctl_data. */
	volatile uint32_t gctl;

	/** Core Interrupt Mask Register	<i>Offset: 114h</i>.
	 * Fields defined in enum @ref gevten_data. */
	volatile uint32_t gevten;

	/** Core Status Register		<i>Offset: 118h</i>.
	 * Fields defined in enum @ref gsts_data. */
	volatile uint32_t gsts;

	/** reserved				<i>Offset: 11Ch</i> */
	volatile uint32_t reserved0;

#define USB3_CORE_GSNPSID_REG_OFFSET 0x120

	/** Synopsys ID Register		<i>Offset: 120h</i> */
	volatile uint32_t gsnpsid;

	/** General Purpose I/O Register	<i>Offset: 124h</i> */
	volatile uint32_t ggpio;

	/** User ID Register			<i>Offset: 128h</i> */
	volatile uint32_t guid;

	/** reserved				<i>Offset: 12Ch</i> */
	volatile uint32_t reserved1;

	/** Bus Error Address Register		<i>Offset: 130h</i> */
	volatile uint32_t gbuserraddrlo;

	/** Bus Error Address Register		<i>Offset: 134h</i> */
	volatile uint32_t gbuserraddrhi;

	/** reserved				<i>Offset: 138h-13Ch</i> */
	volatile uint32_t reserved2[2];

	/** Hardware Parameter 0 Register	<i>Offset: 140h</i>.
	 * Fields defined in enum @ref ghwparams0_data. */
	volatile uint32_t ghwparams0;

	/** Hardware Parameter 1 Register	<i>Offset: 144h</i>.
	 * Fields defined in enum @ref ghwparams1_data. */
	volatile uint32_t ghwparams1;

	/** Hardware Parameter 2 Register	<i>Offset: 148h</i>.
	 * Fields defined in enum @ref ghwparams2_data. */
	volatile uint32_t ghwparams2;

	/** Hardware Parameter 3 Register	<i>Offset: 14Ch</i>.
	 * Fields defined in enum @ref ghwparams3_data. */
	volatile uint32_t ghwparams3;

	/** Hardware Parameter 4 Register	<i>Offset: 150h</i>.
	 * Fields defined in enum @ref ghwparams4_data. */
	volatile uint32_t ghwparams4;

	/** Hardware Parameter 5 Register	<i>Offset: 154h</i>.
	 * Fields defined in enum @ref ghwparams5_data. */
	volatile uint32_t ghwparams5;

	/** Hardware Parameter 6 Register	<i>Offset: 158h</i>.
	 * Fields defined in enum @ref ghwparams6_data. */
	volatile uint32_t ghwparams6;

	/** Hardware Parameter 7 Register	<i>Offset: 15Ch</i>.
	 * Fields defined in enum @ref ghwparams7_data. */
	volatile uint32_t ghwparams7;

	/** Debug Queue/FIFO Space Register	<i>Offset: 160h</i>.
	 * Fields defined in enum @ref gdbgfifospace_data. */
	volatile uint32_t gdbgfifospace;

	/** Debug LTSSM Register		<i>Offset: 164h</i>.
	 * Fields defined in enum @ref gdbgltssm_data  */
	volatile uint32_t gdbgltssm;

	/** reserved				<i>Offset: 168h-1FCh</i> */
	volatile uint32_t reserved3[38];

	/** USB2 Configuration Registers	<i>Offset: 200h-23Ch</i>.
	 * Fields defined in enum @ref gusb2phycfg_data. */
	volatile uint32_t gusb2phycfg[16];

	/** USB2 I2C Access Registers		<i>Offset: 240h-27Ch</i>.
	 * Fields defined in enum @ref gusb2i2cctl_data. */
	volatile uint32_t gusb2i2cctl[16];

	/** USB2 PHY Vendor Control Registers	<i>Offset: 280h-2BCh</i>.
	 * Fields defined in enum @ref gusb2phyacc_data. */
	volatile uint32_t gusb2phyacc[16];

	/** USB3 Pipe Control Registers		<i>Offset: 2C0h-2FCh</i>.
	 * Fields defined in enum @ref gusb3pipectl_data. */
	volatile uint32_t gusb3pipectl[16];

	/** Transmit FIFO Size Registers	<i>Offset: 300h-37Ch</i>.
	 * Fields defined in enum @ref gfifosize_data. */
	volatile uint32_t gtxfifosiz[32];

	/** Receive FIFO Size Registers		<i>Offset: 380h-3FC0h</i>.
	 * Fields defined in enum @ref gfifosize_data. */
	volatile uint32_t grxfifosiz[32];

	/** Event Buffer Registers		<i>Offset: 400h-5FCh</i>.
	 * Fields defined in struct @ref geventbuf_data. */
	struct geventbuf_data geventbuf[32];

	/** Hardware Parameter 8 Register	<i>Offset: 600h</i>.
	 * Fields defined in enum @ref ghwparams8_data. */
	volatile uint32_t ghwparams8;
} usb3_core_global_regs_t;


/****************************************************************************/
/* Device Global Registers */

/**
 * This enum represents the bit fields in the Device Configuration
 * Register (DCFG).
 */
typedef enum dcfg_data {
	/** Device Speed			<i>Access: R_W</i> */
	USB3_DCFG_DEVSPD_BITS		= 0x000007,
	USB3_DCFG_DEVSPD_SHIFT		= 0,

	/** Device Speed values */
	USB3_SPEED_HS_PHY_30MHZ_OR_60MHZ		= 0,	/** @< */
	USB3_SPEED_FS_PHY_30MHZ_OR_60MHZ		= 1,	/** @< */
	USB3_SPEED_LS_PHY_6MHZ			= 2,	/** @< */
	USB3_SPEED_FS_PHY_48MHZ			= 3,	/** @< */
	USB3_SPEED_SS_PHY_125MHZ_OR_250MHZ	= 4,

	/** Device Address			<i>Access: R_W</i> */
	USB3_DCFG_DEVADDR_BITS		= 0x0003f8,
	USB3_DCFG_DEVADDR_SHIFT		= 3,

	/** Periodic Frame Interval		<i>Access: R_W</i> */
	USB3_DCFG_PER_FR_INTVL_BITS	= 0x000c00,
	USB3_DCFG_PER_FR_INTVL_SHIFT	= 10,

	/** Periodic Frame Interval values */
	USB3_DCFG_PER_FR_INTVL_80		= 0,	/** @< */
	USB3_DCFG_PER_FR_INTVL_85		= 1,	/** @< */
	USB3_DCFG_PER_FR_INTVL_90		= 2,	/** @< */
	USB3_DCFG_PER_FR_INTVL_95		= 3,

	/** Device Interrupt Number		<i>Access: R_W</i> */
	USB3_DCFG_DEV_INTR_NUM_BITS	= 0x01f000,
	USB3_DCFG_DEV_INTR_NUM_SHIFT	= 12,

	/** Number of Receive Buffers		<i>Access: R_W</i> */
	USB3_DCFG_NUM_RCV_BUF_BITS	= 0x3e0000,
	USB3_DCFG_NUM_RCV_BUF_SHIFT	= 17,

	/** LPM Capable				<i>Access: R_W</i> */
	USB3_DCFG_LPM_CAP_BIT		= 0x400000,
	USB3_DCFG_LPM_CAP_SHIFT		= 22,
} dcfg_data_t;

/**
 * This enum represents the bit fields in the Device Control
 * Register (DCTL).
 */
typedef enum dctl_data {
	/** Soft Disconnect			<i>Access: R_W</i> */
	USB3_DCTL_SFT_DISCONN_BIT		= 0x00000001,
	USB3_DCTL_SFT_DISCONN_SHIFT		= 0,

	/** Test Control			<i>Access: R_W</i> */
	USB3_DCTL_TSTCTL_BITS			= 0x0000001e,
	USB3_DCTL_TSTCTL_SHIFT			= 1,

	/** USB/Link State Change Request	<i>Access: R_W</i> */
	USB3_DCTL_ULST_CHNG_REQ_BITS		= 0x000001e0,
	USB3_DCTL_ULST_CHNG_REQ_SHIFT		= 5,

	/** Requested Link State Transition/Action In SS Mode */
	USB3_LINK_STATE_REQ_NO_ACTION		= 0,
	USB3_LINK_STATE_REQ_SS_DISABLED		= 4,
	USB3_LINK_STATE_REQ_RX_DETECT		= 5,
	USB3_LINK_STATE_REQ_INACTIVE		= 6,
	USB3_LINK_STATE_REQ_RECOVERY		= 8,
	USB3_LINK_STATE_REQ_COMPLIANCE		= 10,
	USB3_LINK_STATE_REQ_LOOPBACK		= 11,
	USB3_LINK_STATE_REQ_HOST_MODE_ONLY	= 15,

	/** Requested Link State Transition/Action In HS/FS/LS Mode */
	USB3_LINK_STATE_REQ_REMOTE_WAKEUP	= 8,

	/** U1/U2 control			<i>Access: R_W</i> */
	USB3_DCTL_ACCEPT_U1_EN_BIT		= 0x00000200,
	USB3_DCTL_ACCEPT_U1_EN_SHIFT		= 9,
	USB3_DCTL_INIT_U1_EN_BIT			= 0x00000400,
	USB3_DCTL_INIT_U1_EN_SHIFT		= 10,
	USB3_DCTL_ACCEPT_U2_EN_BIT		= 0x00000800,
	USB3_DCTL_ACCEPT_U2_EN_SHIFT		= 11,
	USB3_DCTL_INIT_U2_EN_BIT			= 0x00001000,
	USB3_DCTL_INIT_U2_EN_SHIFT		= 12,

	/** Controller Save State		<i>Access: R_W</i> */
	USB3_DCTL_CSS_BIT			= 0x00010000,
	USB3_DCTL_CSS_SHIFT			= 16,

	/** Controller Restore State		<i>Access: R_W</i> */
	USB3_DCTL_CRS_BIT			= 0x00020000,
	USB3_DCTL_CRS_SHIFT			= 17,

	/** L1 Hibernation Enable		<i>Access: R_W</i> */
	USB3_DCTL_L1_HIBER_EN_BIT		= 0x00040000,
	USB3_DCTL_L1_HIBER_EN_RES_SHIFT		= 18,

	/** Keep Connect (for hibernation)	<i>Access: R_W</i> */
	USB3_DCTL_KEEP_CONNECT_BIT		= 0x00080000,
	USB3_DCTL_KEEP_CONNECT_SHIFT		= 19,

	/** LPM Response			<i>Access: R_W</i> */
	USB3_DCTL_APP_L1_RES_BIT			= 0x00800000,
	USB3_DCTL_APP_L1_RES_SHIFT		= 23,

	/* HIRD Threshold			<i>Access: R_W</i> */
	USB3_DCTL_HIRD_THR_BITS			= 0x1f000000,
	USB3_DCTL_HIRD_THR_SHIFT			= 24,

	/** Light Soft Reset			<i>Access: R_W</i> */
	USB3_DCTL_LSFT_RST_BIT			= 0x20000000,
	USB3_DCTL_LSFT_RST_SHIFT			= 29,

	/** Core Soft Reset			<i>Access: R_W</i> */
	USB3_DCTL_CSFT_RST_BIT			= 0x40000000,
	USB3_DCTL_CSFT_RST_SHIFT			= 30,

	/** Run/Stop				<i>Access: R_W</i> */
	USB3_DCTL_RUN_STOP_BIT			= 0x80000000,
	USB3_DCTL_RUN_STOP_SHIFT			= 31,
} dctl_data_t;

/**
 * This enum represents the bit fields of the Device Event Enable
 * Register (DEVTEN).
 */
typedef enum devten_data {
	/** Disconnect Detected Event Enable	<i>Access: R_W</i> */
	USB3_DEVTEN_DISCONN_BIT		= 0x0001,
	USB3_DEVTEN_DISCONN_SHIFT	= 0,

	/** USB Reset Enable			<i>Access: R_W</i> */
	USB3_DEVTEN_USBRESET_BIT		= 0x0002,
	USB3_DEVTEN_USBRESET_SHIFT	= 1,

	/** Connect Done Enable			<i>Access: R_W</i> */
	USB3_DEVTEN_CONNDONE_BIT		= 0x0004,
	USB3_DEVTEN_CONNDONE_SHIFT	= 2,

	/** USB/Link State Change Event Enable	<i>Access: R_W</i> */
	USB3_DEVTEN_ULST_CHNG_BIT	= 0x0008,
	USB3_DEVTEN_ULST_CHNG_SHIFT	= 3,

	/** Resume/Remote-Wakeup Event Enable	<i>Access: R_W</i> */
	USB3_DEVTEN_WKUP_BIT		= 0x0010,
	USB3_DEVTEN_WKUP_SHIFT		= 4,

	/** Hibernation Request Event Enable	<i>Access: R_W</i> */
	USB3_DEVTEN_HIBER_REQ_EVT_BIT	= 0x0020,
	USB3_DEVTEN_HIBER_REQ_EVT_SHIFT	= 5,

	/** End of Periodic Frame Event Enable	<i>Access: R_W</i> */
	USB3_DEVTEN_EOPF_BIT		= 0x0040,
	USB3_DEVTEN_EOPF_SHIFT		= 6,

	/** Start of (Micro)Frame Enable	<i>Access: R_W</i> */
	USB3_DEVTEN_SOF_BIT		= 0x0080,
	USB3_DEVTEN_SOF_SHIFT		= 7,

	/** Erratic Error Event Enable		<i>Access: R_W</i> */
	USB3_DEVTEN_ERRATICERR_BIT	= 0x0200,
	USB3_DEVTEN_ERRATICERR_SHIFT	= 9,

	/** U2 Inactivity Timeout Enable	<i>Access: R_W</i> */
	USB3_DEVTEN_INACT_TIMEOUT_BIT	= 0x2000,
	USB3_DEVTEN_INACT_TIMEOUT_SHIFT	= 13,
} devten_data_t;

/**
 * This enum represents the bit fields in the Device Status
 * Register (DSTS).
 */
typedef enum dsts_data {
	/** Connected Speed			<i>Access: RO</i>.
	 * (see enum @ref dcfg_data for values) */
	USB3_DSTS_CONNSPD_BITS		= 0x00000007,
	USB3_DSTS_CONNSPD_SHIFT		= 0,

	/** (Micro)Frame Number of Received SOF	<i>Access: RO</i> */
	USB3_DSTS_SOF_FN_BITS		= 0x0001fff8,
	USB3_DSTS_SOF_FN_SHIFT		= 3,

	/** RX Fifo Empty			<i>Access: RO</i> */
	USB3_DSTS_RXFIFO_EMPTY_BIT	= 0x00020000,
	USB3_DSTS_RXFIFO_EMPTY_SHIFT	= 17,

	/** USB/Link State			<i>Access: RO</i> */
	USB3_DSTS_USBLNK_STATE_BITS	= 0x003c0000,
	USB3_DSTS_USBLNK_STATE_SHIFT	= 18,

	/** USB/Link State values same as for devt_data_t */

	/** Device Controller Halted		<i>Access: RO</i> */
	USB3_DSTS_DEV_CTRL_HLT_BIT	= 0x00400000,
	USB3_DSTS_DEV_CTRL_HLT_SHIFT	= 22,

	/** Core Idle				<i>Access: RO</i> */
	USB3_DSTS_CORE_IDLE_BIT		= 0x00800000,
	USB3_DSTS_CORE_IDLE_SHIFT	= 23,

	/** Save State Status			<i>Access: RO</i> */
	USB3_DSTS_SSS_BIT		= 0x01000000,
	USB3_DSTS_SSS_SHIFT		= 24,

	/** Restore State Status		<i>Access: RO</i> */
	USB3_DSTS_RSS_BIT		= 0x02000000,
	USB3_DSTS_RSS_SHIFT		= 25,

	/** Save/Restore Error			<i>Access: RO</i> */
	USB3_DSTS_SRE_BIT		= 0x10000000,
	USB3_DSTS_SRE_SHIFT		= 28,

	/** Link-state Not Ready		<i>Access: RO</i> */
	USB3_DSTS_LNR_BIT		= 0x20000000,
	USB3_DSTS_LNR_SHIFT		= 29,
} dsts_data_t;

/**
 * This enum represents the bit fields in the Device Generic Command Parameter
 * Register (DGCMDPARn) for the various commands.
 */
typedef enum dgcmdpar_data {
	/** Force Link PM Accept
	 * (for USB3_DGCMD_XMIT_SET_LINK_FUNC_LMP command) */
	USB3_DGCMDPAR_FORCE_LINK_PM_ACCEPT_BIT	= 0x0001,
	USB3_DGCMDPAR_FORCE_LINK_PM_ACCEPT_SHIFT	= 0,

	/** Vendor Specific Test Select
	 * (for USB3_DGCMD_XMIT_VEND_DEV_TST_LMP command) */
	USB3_DGCMDPAR_VEND_SPEC_TST_BITS		= 0x00ff,
	USB3_DGCMDPAR_VEND_SPEC_TST_SHIFT	= 0,

	/** Interface Number (for USB3_DGCMD_XMIT_RMT_WKUP_SIG command) */
	USB3_DGCMDPAR_INTF_NUM_BITS		= 0x00ff,
	USB3_DGCMDPAR_INTF_NUM_SHIFT		= 0,

	/** Best Effort Latency Tolerance Value
	 * (for USB3_DGCMD_XMIT_LAT_TOL_MSG command) */
	USB3_DGCMDPAR_BELT_VALUE_BITS		= 0x03ff,
	USB3_DGCMDPAR_BELT_VALUE_SHIFT		= 0,

	/** Best Effort Latency Tolerance Scale
	 * (for USB3_DGCMD_XMIT_LAT_TOL_MSG command) */
	USB3_DGCMDPAR_BELT_SCALE_BITS		= 0x0c00,
	USB3_DGCMDPAR_BELT_SCALE_SHIFT		= 10,

	/** Latency Scale values (ns) */
	USB3_LATENCY_VALUE_MULT_1024	= 1,	/** @< */
	USB3_LATENCY_VALUE_MULT_32768	= 2,	/** @< */
	USB3_LATENCY_VALUE_MULT_1048576	= 3,

	/** Bus Interval Adjustment
	 * (for USB3_DGCMD_XMIT_BUS_INTVL_ADJ_MSG command) */
	USB3_DGCMDPAR_BUS_INTVL_ADJ_BITS		= 0xffff,
	USB3_DGCMDPAR_BUS_INTVL_ADJ_SHIFT	= 0,

	/** Bus Interval Adjustment values (units) */
	USB3_BUS_INTVL_ADJ_DEC_1		= 0xffff,	/** @< */
	USB3_BUS_INTVL_ADJ_DEC_32768	= 0x8000,	/** @< */
	USB3_BUS_INTVL_ADJ_INC_32767	= 0x7fff,	/** @< */
	USB3_BUS_INTVL_ADJ_NO_CHNG	= 0x0000,

	USB3_DGCMDPAR_HOST_ROLE_REQ_INITIATE	= 0x01,
	USB3_DGCMDPAR_HOST_ROLE_REQ_CONFIRM	= 0x02,
} dgcmdpar_data_t;

/**
 * This enum represents the bit fields in the Device Generic Command
 * Register (DGCMDn).
 */
typedef enum dgcmd_data {
	/** Command Type			<i>Access: R_W</i> */
	USB3_DGCMD_TYP_BITS			= 0x0ff,
	USB3_DGCMD_TYP_SHIFT			= 0,

	/** Command Type values */
	USB3_DGCMD_XMIT_SET_LINK_FUNC_LMP		= 1,	/** @< */
	USB3_DGCMD_SET_PERIODIC_PARAMS			= 2,	/** @< */
	USB3_DGCMD_XMIT_FUNC_WAKE_DEV_NOTIF		= 3,	/** @< */
	USB3_DGCMD_SET_SCRATCHPAD_ARRAY_ADR_LO		= 4,	/** @< */
	USB3_DGCMD_SET_SCRATCHPAD_ARRAY_ADR_HI		= 5,	/** @< */
	USB3_DGCMD_XMIT_HOST_ROLE_REQUEST		= 6,	/** @< */
	USB3_DGCMD_SET_EP_NRDY				= 12,	/** @< */
	USB3_DGCMD_RUN_SOC_BUS_LOOPBK_TST		= 16,	/** @< */

	/** Command Interrupt on Complete	<i>Access: R_W</i> */
	USB3_DGCMD_IOC_BIT			= 0x100,
	USB3_DGCMD_IOC_SHIFT			= 8,

	/** Command Active			<i>Access: R_W</i> */
	USB3_DGCMD_ACT_BIT			= 0x400,
	USB3_DGCMD_ACT_SHIFT			= 10,

	/** Command Status			<i>Access: R_W</i> */
	USB3_DGCMD_STS_BITS			= 0xf000,
	USB3_DGCMD_STS_SHIFT			= 12,

	/** Command Status values */
	USB3_DGCMD_STS_ERROR				= 15,
} dgcmd_data_t;

/**
 * This enum represents the bit fields in the Device Endpoint Mapping
 * Registers (DEPMAPn).
 */
typedef enum depmap_data {
	/** Resource Number			<i>Access: R_W / RO</i> */
	USB3_EPMAP_RES_NUM_BITS		= 0x1f,
	USB3_EPMAP_RES_NUM_SHIFT		= 0,
} depmap_data_t;

/**
 * Device Global Registers	<i>Offsets 700h-7FCh</i>.
 *
 * The following structures define the size and relative field offsets
 * for the Device Mode Global Registers.
 */
typedef struct usb3_dev_global_regs {

#define USB3_DEV_GLOBAL_REG_OFFSET	0x700

	/** Device Configuration Register		<i>Offset: 700h</i>.
	 * Fields defined in enum @ref dcfg_data. */
	volatile uint32_t dcfg;

	/** Device Control Register			<i>Offset: 704h</i>.
	 * Fields defined in enum @ref dctl_data. */
	volatile uint32_t dctl;

	/** Device All Endpoints Interrupt Mask Register <i>Offset: 708h</i>.
	 * Fields defined in enum @ref devten_data. */
	volatile uint32_t devten;

	/** Device Status Register			<i>Offset: 70Ch</i>.
	 * Fields defined in enum @ref dsts_data. */
	volatile uint32_t dsts;

	/** Device Generic Command Parameter Register	<i>Offset: 710h</i>.
	 * Fields defined in enum @ref dgcmdpar_data. */
	volatile uint32_t dgcmdpar;

	/** Device Generic Command Register		<i>Offset: 714h</i>.
	 * Fields defined in enum @ref dgcmd_data. */
	volatile uint32_t dgcmd;

	/** reserved				     <i>Offset: 718h-71Ch</i> */
	volatile uint32_t reserved[2];

	/** Device Active Logical Endpoint Enable Register <i>Offset: 720h</i>.
	 * One bit per logical endpoint, bit0=EP0 ... bit31=EP31. */
	volatile uint32_t dalepena;
} usb3_dev_global_regs_t;


/****************************************************************************/
/* Device Endpoint Specific Registers */

/**
 * This enum represents the bit fields in the Device Endpoint Command
 * Parameter 1 Register (DEPCMDPAR1n) for the Set Endpoint Configuration
 * (DEPCFG) command.
 */
typedef enum depcfgpar1_data {
	/** Interrupt number */
	USB3_EPCFG1_INTRNUM_BITS		= 0x0000003f,
	USB3_EPCFG1_INTRNUM_SHIFT	= 0,

	/** Stream Completed */
	USB3_EPCFG1_XFER_CMPL_BIT	= 0x00000100,
	USB3_EPCFG1_XFER_CMPL_SHIFT	= 8,

	/** Stream In Progress */
	USB3_EPCFG1_XFER_IN_PROG_BIT	= 0x00000200,
	USB3_EPCFG1_XFER_IN_PROG_SHIFT	= 9,

	/** Stream Not Ready */
	USB3_EPCFG1_XFER_NRDY_BIT	= 0x00000400,
	USB3_EPCFG1_XFER_NRDY_SHIFT	= 10,

	/** Rx FIFO Underrun / Tx FIFO Overrun */
	USB3_EPCFG1_FIFOXRUN_BIT		= 0x00000800,
	USB3_EPCFG1_FIFOXRUN_SHIFT	= 11,

	/** Back-to-Back Setup Packets Received	 */
	USB3_EPCFG1_SETUP_PNDG_BIT	= 0x00001000,
	USB3_EPCFG1_SETUP_PNDG_SHIFT	= 12,

	/** Endpoint Command Complete */
	USB3_EPCFG1_EPCMD_CMPL_BIT	= 0x00002000,
	USB3_EPCFG1_EPCMD_CMPL_SHIFT	= 13,

	/** Endpoint bInterval */
	USB3_EPCFG1_BINTERVAL_BITS	= 0x00ff0000,
	USB3_EPCFG1_BINTERVAL_SHIFT	= 16,

	/** Endpoint Stream Capability */
	USB3_EPCFG1_STRM_CAP_BIT		= 0x01000000,
	USB3_EPCFG1_STRM_CAP_SHIFT	= 24,

	/** Endpoint Direction */
	USB3_EPCFG1_EP_DIR_BIT		= 0x02000000,
	USB3_EPCFG1_EP_DIR_SHIFT		= 25,

	/** Endpoint Number */
	USB3_EPCFG1_EP_NUM_BITS		= 0x3c000000,
	USB3_EPCFG1_EP_NUM_SHIFT		= 26,
} depcfgpar1_data_t;

/**
 * This enum represents the bit fields in the Device Endpoint Command
 * Parameter 0 Register (DEPCMDPAR0n) for the Set Endpoint Configuration
 * (DWC_EPCMD_SET_EP_CFG) command.
 */
typedef enum depcfgpar0_data {
	/** Endpoint Type			<i>Access: R_W</i> */
	USB3_EPCFG0_EPTYPE_BITS			= 0x00000006,
	USB3_EPCFG0_EPTYPE_SHIFT        = 1,

	/** Endpoint Type values */
	USB3_EP_TYPE_CONTROL	        = 0,	/** @< */
	USB3_EP_TYPE_ISOC		        = 1,	/** @< */
	USB3_EP_TYPE_BULK		        = 2,	/** @< */
	USB3_EP_TYPE_INTR		        = 3,

	/** Maximum Packet Size			<i>Access: R_W</i> */
	USB3_EPCFG0_MPS_BITS			= 0x00003ff8,
	USB3_EPCFG0_MPS_SHIFT			= 3,

	/** Flow Control State			<i>Access: R_W</i> */
	USB3_EPCFG0_FLOW_CTRL_STATE_BIT		= 0x00010000,
	USB3_EPCFG0_FLOW_CTRL_STATE_SHIFT	= 16,

	/** Tx Fifo Number (IN endpoints only)	<i>Access: R_W</i> */
	USB3_EPCFG0_TXFNUM_BITS			    = 0x003e0000,
	USB3_EPCFG0_TXFNUM_SHIFT			= 17,

	/** Burst Size				<i>Access: R_W</i> */
	USB3_EPCFG0_BRSTSIZ_BITS			= 0x03c00000,
	USB3_EPCFG0_BRSTSIZ_SHIFT		    = 22,

	/** Data Sequence Num (old)		<i>Access: R_W</i> */
	USB3_EPCFG0_DSNUM_BITS			= 0x7c000000,
	USB3_EPCFG0_DSNUM_SHIFT			= 26,

	/** Ignore Data Sequence Num (old)	<i>Access: R_W</i> */
	USB3_EPCFG0_IGN_DSNUM_BIT		= 0x80000000,
	USB3_EPCFG0_IGN_DSNUM_SHIFT		= 31,

	/** Config Action (new)			<i>Access: R_W</i> */
	USB3_EPCFG0_CFG_ACTION_BITS		= 0xc0000000,
	USB3_EPCFG0_CFG_ACTION_SHIFT		= 30,

	/** Config Action values (new) */
	USB3_CFG_ACTION_INIT		= 0,	/** @< */
	USB3_CFG_ACTION_RESTORE		= 1,	/** @< */
	USB3_CFG_ACTION_MODIFY		= 2,
} depcfgpar0_data_t;

/**
 * This enum represents the bit fields in the Device Endpoint Command
 * Register (DEPCMDn).
 */
typedef enum depcmd_data {
	/** Command Type			<i>Access: R_W</i> */
	USB3_EPCMD_TYP_BITS		= 0x0ff,
	USB3_EPCMD_TYP_SHIFT		= 0,

	/** Command Type values */
	USB3_EPCMD_SET_EP_CFG	= 1,	/** @< */
	USB3_EPCMD_SET_XFER_CFG	= 2,	/** @< */
	USB3_EPCMD_GET_EP_STATE	= 3,	/** @< */
	USB3_EPCMD_SET_STALL	= 4,	/** @< */
	USB3_EPCMD_CLR_STALL	= 5,	/** @< */
	USB3_EPCMD_START_XFER	= 6,	/** @< */
	USB3_EPCMD_UPDATE_XFER	= 7,	/** @< */
	USB3_EPCMD_END_XFER	= 8,	/** @< */
	USB3_EPCMD_START_NEW_CFG	= 9,

	/** Command Interrupt on Complete	<i>Access: R_W</i> */
	USB3_EPCMD_IOC_BIT		= 0x100,
	USB3_EPCMD_IOC_SHIFT		= 8,

	/** Command Active			<i>Access: R_W</i> */
	USB3_EPCMD_ACT_BIT		= 0x400,
	USB3_EPCMD_ACT_SHIFT		= 10,

	/** High Priority / Force RM Bit	<i>Access: R_W</i> */
	USB3_EPCMD_HP_FRM_BIT		= 0x800,
	USB3_EPCMD_HP_FRM_SHIFT		= 11,

	/** Command Completion Status		<i>Access: R_W</i> */
	USB3_EPCMD_CMPL_STS_BITS		= 0xf000,
	USB3_EPCMD_CMPL_STS_SHIFT	= 12,

	/** Stream Number or uFrame (input)	<i>Access: R_W</i> */
	USB3_EPCMD_STR_NUM_OR_UF_BITS	= 0xffff0000,
	USB3_EPCMD_STR_NUM_OR_UF_SHIFT	= 16,

	/** Transfer Resource Index (output)	<i>Access: R_W</i> */
	USB3_EPCMD_XFER_RSRC_IDX_BITS	= 0x007f0000,
	USB3_EPCMD_XFER_RSRC_IDX_SHIFT	= 16,
} depcmd_data_t;

/**
 * Device Endpoint Specific Registers <i>Offsets 800h-9ECh for OUT,
 *						 810h-9FCh for IN</i>.
 * There will be one set of endpoint registers per logical endpoint
 * implemented.
 */
typedef struct usb3_dev_ep_regs {

#define USB3_DEV_OUT_EP_REG_OFFSET	0x800
#define USB3_DEV_IN_EP_REG_OFFSET	0x810
#define USB3_EP_REG_OFFSET		    0x20

	/** Device Endpoint Command Parameter 2 Register <i>Offset: 800h/810h +
	 *					(ep_num * 20h) + 00h</i> */
	volatile uint32_t depcmdpar2;

	/** Device Endpoint Command Parameter 1 Register <i>Offset: 800h/810h +
	 *					(ep_num * 20h) + 04h</i> */
	volatile uint32_t depcmdpar1;

	/** Device Endpoint Command Parameter 0 Register <i>Offset: 800h/810h +
	 *					(ep_num * 20h) + 08h</i> */
	volatile uint32_t depcmdpar0;

	/** Device Endpoint Command Register	<i>Offset: 800h/810h +
	 *					(ep_num * 20h) + 0Ch</i>.
	 * Fields defined in enum @ref depcmd_data. */
	volatile uint32_t depcmd;

	/** reserved				<i>Offset: 800h/810h +
	 *					(ep_num * 20h) + 10h-1Ch</i> */
	volatile uint32_t reserved[4];
} usb3_dev_ep_regs_t;


/****************************************************************************/
/* DMA Descriptor Specific Structures */

/**
 * This enum represents the bit fields in the DMA Descriptor
 * Status quadlet.
 */
typedef enum desc_sts_data {
	/** Transfer Count */
	USB3_DSCSTS_XFRCNT_MAX	= 0x1000000,	//16MB
	USB3_DSCSTS_XFRCNT_BITS	= 0x00ffffff,
	USB3_DSCSTS_XFRCNT_SHIFT	= 0,

	/** Packet Count Minus 1 (for HS IN transfers) */
	USB3_DSCSTS_PCM1_BITS	= 0x03000000,
	USB3_DSCSTS_PCM1_SHIFT	= 24,

	/** Transfer Request Block Response */
	USB3_DSCSTS_TRBRSP_BITS	= 0xf0000000,
	USB3_DSCSTS_TRBRSP_SHIFT	= 28,

	USB3_TRBRSP_MISSED_ISOC_IN	= 1,
	USB3_TRBRSP_SETUP_PEND		= 2,
	USB3_TRBRSP_XFER_IN_PROG		= 4,
} desc_sts_data_t;

/**
 * This enum represents the bit fields in the DMA Descriptor
 * Control quadlet.
 */
typedef enum desc_ctl_data {
	/** Hardware-Owned bit */
	USB3_DSCCTL_HWO_BIT		= 0x00000001,
	USB3_DSCCTL_HWO_SHIFT		= 0,

	/** Last Descriptor bit */
	USB3_DSCCTL_LST_BIT		= 0x00000002,
	USB3_DSCCTL_LST_SHIFT		= 1,

	/** Chain Buffer bit */
	USB3_DSCCTL_CHN_BIT		= 0x00000004,
	USB3_DSCCTL_CHN_SHIFT		= 2,

	/** Continue on Short Packet bit */
	USB3_DSCCTL_CSP_BIT		= 0x00000008,
	USB3_DSCCTL_CSP_SHIFT		= 3,

	/** Transfer Request Block Control field */
	USB3_DSCCTL_TRBCTL_BITS		= 0x000003f0,
	USB3_DSCCTL_TRBCTL_SHIFT		= 4,

	/** Transfer Request Block Control types */
	USB3_DSCCTL_TRBCTL_NORMAL		= 1,	/** @< */
	USB3_DSCCTL_TRBCTL_SETUP			= 2,	/** @< */
	USB3_DSCCTL_TRBCTL_STATUS_2		= 3,	/** @< */
	USB3_DSCCTL_TRBCTL_STATUS_3		= 4,	/** @< */
	USB3_DSCCTL_TRBCTL_CTLDATA_1ST		= 5,	/** @< */
	USB3_DSCCTL_TRBCTL_ISOC_1ST		= 6,	/** @< */
	USB3_DSCCTL_TRBCTL_ISOC			= 7,	/** @< */
	USB3_DSCCTL_TRBCTL_LINK			= 8,

	/** Interrupt on Short Packet bit */
	USB3_DSCCTL_ISP_BIT		        = 0x00000400,
	USB3_DSCCTL_ISP_SHIFT		    = 10,
#define USB3_DSCCTL_IMI_BIT	    USB3_DSCCTL_ISP_BIT
#define USB3_DSCCTL_IMI_SHIFT	USB3_DSCCTL_ISP_SHIFT

	/** Interrupt on Completion bit */
	USB3_DSCCTL_IOC_BIT		        = 0x00000800,
	USB3_DSCCTL_IOC_SHIFT		    = 11,

	/** Stream ID / SOF Number */
	USB3_DSCCTL_STRMID_SOFN_BITS	= 0x3fffc000,
	USB3_DSCCTL_STRMID_SOFN_SHIFT	= 14,
} desc_ctl_data_t;

/**
 * DMA Descriptor structure
 *
 * DMA Descriptor structure contains 4 quadlets:
 * Buffer Pointer Low address, Buffer Pointer High address, Status, and Control.
 */
typedef struct usb3_dma_desc {
	/** Buffer Pointer - Low address quadlet */
	uint32_t	bptl;

	/** Buffer Pointer - High address quadlet */
	uint32_t	bpth;

	/** Status quadlet. Fields defined in enum @ref desc_sts_data. */
	uint32_t	status;

	/** Control quadlet. Fields defined in enum @ref desc_ctl_data. */
	uint32_t	control;
} usb3_dma_desc_t;

#ifdef __cplusplus
}
#endif

#endif /* __USB3_HW_H__ */

