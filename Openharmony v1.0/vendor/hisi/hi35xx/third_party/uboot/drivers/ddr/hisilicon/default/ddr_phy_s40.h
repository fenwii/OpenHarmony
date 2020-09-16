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

/* register offset address */
/* base address: DDR_REG_BASE_PHY0 DDR_REG_BASE_PHY1 */
/* control the initialization of the PHY */
#define DDR_PHY_PHYINITCTRL	0x4
#define DDR_PHY_PHYINITSTATUS	0x8	/* Read Data Eye Calibration Error*/
#define DDR_PHY_IMPSTATUS	0x28    /* This register specify the ZQ calibration result. */
#define DDR_PHY_DRAMCFG		0x2c    /* DRAM config register */
#define DDR_PHY_MODEREG01	0x64	/* Extend Mode Register 01 */
#define DDR_PHY_MODEREG23	0x68	/* Extend Mode Register 23 */
/* update delay setting in registers to PHY */
#define DDR_PHY_MISC		0x70
#define DDR_PHY_SWTMODE		0xa0	/* S/W training mode */
/* issue one DQS pulse from PHY to DRAM */
#define DDR_PHY_SWTWLDQS	0xa4
#define DDR_PHY_SWTRLT		0xa8	/* S/W training result*/
/* Host vref. [5:0]range [17:12]refsel */
#define DDR_PHY_IOCTL2		0xB4
#define DDR_PHY_VREFTCTRL	0xc0    /* VREF Training Control Register. */
#define DDR_PHY_DVRFTCTRL	0xC4    /* DRAM VREF Training */
/* AC command bit delay line setting */
#define DDR_PHY_ACCMDBDL2	0x128
#define DDR_PHY_IMP_CTRL1	0x170   /* AC/DX ZQ selection */
#define DDR_PHY_IMP_STATUS1	0x174   /* AC ZCAL status */
#define DDR_PHY_ACPHYCTL4	0x180  /* AC block PHY control register*/
/* AC block PHY control register */
#define DDR_PHY_ACPHYCTL7	0x18C

/* WR DQ0-DQ3 [4:0] [12:8] [20:16] [28:24] delay value of the bit delay line
   on write path */
#define DDR_PHY_DXNWDQNBDL0(m, n)	(0x210 + ((m) << 10) + ((n) << 7))
/* WR DQ4-DQ7 [6:0] [14:8] [22:16] [30:24] */
#define DDR_PHY_DXNWDQNBDL1(m, n)	(0x214 + ((m) << 10) + ((n) << 7))
/* WR DM [6:0] the delay value of the bit delay line on DQM */
#define DDR_PHY_DXNWDQNBDL2(m, n)	(0x218 + ((m) << 10) + ((n) << 7))
/* RD DQ0-DQ3 [6:0] [14:8] [22:16] [30:24] delay value of the bit delay line
 on read path */
#define DDR_PHY_DXNRDQNBDL0(m, n)	(0x21C + ((m) << 10) + ((n) << 7))
/* RD DQ4-DQ7 [6:0] [14:8] [22:16] [30:24] delay value of the bit delay line
 on read path */
#define DDR_PHY_DXNRDQNBDL1(m, n)	(0x220 + ((m) << 10) + ((n) << 7))
/* [6:0]RD DM*/
#define DDR_PHY_DXNRDQNBDL2(m, n)	(0x224 + ((m) << 10) + ((n) << 7))


/* [CUSTOM] */
#define DDR_PHY_DXNOEBDL(m, n)	(0x228 + ((m) << 10) + ((n) << 7))
/* [8:0] rdqs_bdl [24:16]rdqs_cyc.
phase shift of the Read DQS to create 90 degree delays*/
#define DDR_PHY_DXNRDQSDLY(n)	(0x22C + ((n) << 7))
/* [6:0] the delay value of delay applied on WDQS for write leveling */
#define DDR_PHY_DXWDQSDLY(m, n)	(0x230 + ((m) << 10) + ((n) << 7))
/* WR DQ phase BIT 12:8 */
#define DDR_PHY_DXNWDQDLY(m, n)	(0x234 + ((m) << 10) + ((n) << 7))
/* [CUSTOM] rddqs gating*/
#define DDR_PHY_DXNRDQSGDLY(m, n)	(0x240 + ((m) << 10) + ((n) << 7))
/* read boundary  right 8:0 left 24:16 */
#define DDR_PHY_DXNRDBOUND(n)	(0x250 + ((n) << 7))
/* write boundary  right 4:0 left 20:16 */
#define DDR_PHY_DXNWDBOUND(n)	(0x254 + ((n) << 7))

#define DDR_PHY_CORNER_DETECTOR 0x104C  /* cfg of corner detector */

#define DDR_VREF_HOST_VAL_MAX             (0x1f)        /* 78.75%*VDDIO */
#define DDR_VREF_HOST_VAL_MIN             (0x0)         /* 40.00%*VDDIO */

/* register mask */
#define PHY_BDL_MASK			0x1f	/* [4:0] */
#define PHY_WDQS_PHASE_MASK		0xf	    /* [11:8] */
#define PHY_RDQS_BDL_MASK		0x7f	/* [CUSTOM] [6:0] rdqsbdl*/
#define PHY_RDQSG_PHASE_MASK		0x3f	/* [14:9] rdqsgtxbdl */
#define PHY_RDM_BDL_MASK		0x7f	/* [6:0] */
/* hardware gate training result */
#define PHY_INITSTATUS_GT_MASK		0x20
#define PHY_SWTRLT_WL_MASK		0xf
#define PHY_SWTRLT_GATE_MASK	0xf
#define PHY_WDQ_PHASE_MASK		0x1f
#define PHY_PHYINITCTRL_MASK		0xffff	/* [15:0] all stat */
/* Read Data Eye Calibration Error */
#define PHY_PHYINITSTATUS_RDET_ERR	0x100
#define PHY_ACPHY_DCLK_MASK		0x7	/* cp1p_dclk0 mask */
#define PHY_ACPHY_DRAMCLK_MASK		0x1	/* halft_dramclk0 mask */
#define PHY_VRFTRES_HVREF_MASK	0x1f /* [4:0] */
#define PHY_VRFTRES_RXDIFFCAL_MASK	0xf /* [24:21] */
#define PHY_ACADDR_BDL_MASK		0x7f /* [6:0] */
#define PHY_DRAMCFG_TYPE_MASK   0xf /* [3:0] */
#define PHY_OSC_START_MASK		0x1 /* [0] */
#define PHY_OSC_RPT_VLD_MASK	0x1 /* [15] */
#define PHY_OSC_CNT_RDATA_MASK	0xffff /* [31:16] */
#define PHY_ZCODE_PDRV_MASK		0x3f   /* [21:16] */
#define PHY_ACCTL_PDRV_LATCH_MASK	0x3f   /* [29:24] */

/* register bit */
#define PHY_MISC_UPDATE_BIT	20	/* [CUSTOM] delay config update bit */
#define PHY_PHYCONN_RST_BIT	15	/* issue reset signal to PHY counter */
#define PHY_RDQSG_PHASE_BIT	8	/* [CUSTOM] */
#define PHY_RDQSG_TX_BDL_BIT	16	/* [22:16] rdqsgtxbdl */
#define PHY_WDQS_PHASE_BIT	8
#define PHY_WDQS_BDL_BIT	0
#define PHY_WDQ_PHASE_BIT	8
#define PHY_WDM_BDL_BIT		0
/* [20:16] Write DQS Output Enable Delay Control */
#define PHY_WDQSOE_BDL_BIT	16
#define PHY_OEN_BDL_BIT		0
/* Mode Register 1. Defines the MR3/MR9 of the mode register */
#define PHY_MODEREG01_MR1_BIT	16
#define PHY_ACADDRBDL_ADDR1_BIT		16 /* [16] ADDR1 delay line */
/* Bit delay line setting of CS1 */
#define PHY_ACCMD_CS0_BIT		0
#define PHY_ACCMD_CS1_BIT		16
#define PHY_ACPHY_DCLK0_BIT		6	/* [8:6] cp1p_dclk0 */
#define PHY_ACPHY_DCLK1_BIT		9	/* [11:9] ck2p_dclk1 */
#define PHY_ACPHY_DRAMCLK0_BIT		25	/* [25] halft_dramclk0 */
#define PHY_ACPHY_DRAMCLK1_BIT		24	/* [24] halft_dramclk1 */
#define PHY_ACPHY_DRAMCLK_EXT_BIT	3 /* [3] halft_dramclk0 */
#define PHY_SWTMODE_SW_GTMODE_BIT	1 /* [1] SW gate training */
#define PHY_VREFS_MRS_ENTER_BIT		31 /* [31] */
#define PHY_OSC_RPT_VLD				15 /* [15] */
#define PHY_OSC_CNT_RDATA_BIT		16 /* [31:16] */
#define PHY_ZCODE_PDRV_BIT			16 /* [21:16] */
#define PHY_ACCTL_PDRV_LATCH_BIT	24 /* [29:24] */
#define PHY_AC_VDDQ_CAL_EN_BIT		8  /* [8] AC ZQ calibration enable */
#define PHY_CFG_RX_AGE_COMPST_EN_BIT 31 /* Enable rdqs age compensation function */
/* BDL register bit */
#define PHY_BDL_DQ_BIT    0
#define PHY_BDL_DQ0_BIT   0
#define PHY_BDL_DQ1_BIT   8
#define PHY_BDL_DQ2_BIT   16
#define PHY_BDL_DQ3_BIT   24
#define PHY_RDM_BDL_BIT   0
#define PHY_RDQS_BDL_BIT  0

/* value */
#define PHY_PHYINITCTRL_DVREFT_SYNC	0x40000 /* DRAM VREF Synchronize */
/* hw training item defined in PHYINITCTRL */
#define PHY_PHYINITCTRL_CTL_CKE_BYPASS	(1 << 31)	/* PACK's CKE bypass function enable. */
#define PHY_PHYINITCTRL_PIC_PHYUPD_REQ	(1 << 30)	/* PACK's DFI PHY UPDATAE request by SW. */
#define PHY_PHYINITCTRL_PIC_TDQSST		(1 << 29)	/* TDQSS training Enable. */
#define PHY_PHYINITCTRL_LP4_CHB_DIS		(1 << 28)	/* LPDDR4 channel-B disable. */
#define PHY_PHYINITCTRL_LP4_CHA_DIS		(1 << 27)	/* LPDDR4 channel-A disable. */
#define PHY_PHYINITCTRL_PIC_REFRET_SFT	(1 << 26)	/* Update delay line(switch op_sel) during tRFC. */
#define PHY_PHYINITCTRL_PIC_REFRET_WR	(1 << 25)	/* Retraining with MPC write during tRFC. */
#define PHY_PHYINITCTRL_PIC_REFRET_RD	(1 << 24)	/* Retraining with MPC read during tRFC. */
#define PHY_PHYINITCTRL_JTMT_EN			(1 << 23)	/* PLL Jitter Meter Enable. */
#define PHY_PHYINITCTRL_CST_EN			(1 << 22)	/* HW CS Traninig Enable. */
#define PHY_PHYINITCTRL_ACDVREFS_EN		(1 << 21)	/* DRAM VREF(AC) Synchronize Operations. */
#define PHY_PHYINITCTRL_ACHVREFT_EN		(1 << 20)	/* Host VREF(AC) Training Enable. */
#define PHY_PHYINITCTRL_ACDVREFT_EN		(1 << 19)	/* DRAM VREF(AC) Training Enable. */
#define PHY_PHYINITCTRL_DXDVREFS_EN		(1 << 18)	/* DRAM VREF(DQ) Synchronize Operations. */
#define PHY_PHYINITCTRL_HVREFT_EN		(1 << 17)	/* Host VREF(DQ) Training Enable. */
#define PHY_PHYINITCTRL_DVREFT_EN		(1 << 16)	/* DRAM VREF(DQ) Training Enable. */
#define PHY_PHYINITCTRL_PHYCONN_RST		(1 << 15)	/* PHY Counter Reset. */
#define PHY_PHYINITCTRL_PACK_RST		(1 << 14)	/* PACK Reset. */
#define PHY_PHYINITCTRL_PHY_RST			(1 << 13)	/* PHY Reset. */
#define PHY_PHYINITCTRL_DRAM_RST		(1 << 12)	/* DRAM Reset. */
#define PHY_PHYINITCTRL_CAT_EN			(1 << 11)	/* HW CA Traninig Enable. */
#define PHY_PHYINITCTRL_DRAM_INIT_EN	(1 << 10)	/* DRAM Initialization Enable. */
#define PHY_PHYINITCTRL_WDET_EN			(1 << 9)	/* Write Data Eye Training Enable. */
#define PHY_PHYINITCTRL_RDET_EN			(1 << 8)	/* Read Data Eye Training Enable. */
#define PHY_PHYINITCTRL_WL2_EN			(1 << 7)	/* Second Write Leveling Enable. */
#define PHY_PHYINITCTRL_GDST_EN			(1 << 6)	/* PHY Read Data Latch Train Enable. */
#define PHY_PHYINITCTRL_GT_EN			(1 << 5)	/* Gate Training Enable. */
#define PHY_PHYINITCTRL_WL_EN			(1 << 4)	/* Write Leveling Enable. */
#define PHY_PHYINITCTRL_ZCAL_EN			(1 << 3)	/* Impedance Calibration Enable. */
#define PHY_PHYINITCTRL_DLYMEAS_EN		(1 << 2)	/* Delay Measurement Enable. */
#define PHY_PHYINITCTRL_PLL_INIT_EN		(1 << 1)	/* PLL Initialization Enable. */
#define PHY_PHYINITCTRL_INIT_EN			(1 << 0)	/* PHY Initialization Enable. */

#define PHY_HW_GP_PHY_RESET			(PHY_PHYINITCTRL_PHY_RST)
#define PHY_HW_GP_CNT_RESET_START	(PHY_PHYINITCTRL_PHYCONN_RST)
#define PHY_HW_GP_PLL				(PHY_PHYINITCTRL_PLL_INIT_EN | PHY_PHYINITCTRL_ZCAL_EN | PHY_PHYINITCTRL_DLYMEAS_EN)
#define PHY_HW_GP_DRAM_RESET		(PHY_PHYINITCTRL_DRAM_RST | PHY_PHYINITCTRL_DRAM_INIT_EN)
#define PHY_HW_GP_VREF_AC			(PHY_PHYINITCTRL_ACDVREFS_EN)
#define PHY_HW_GP_CS				(PHY_PHYINITCTRL_CST_EN)
#define PHY_HW_GP_VREF_DQ			(PHY_PHYINITCTRL_DVREFT_SYNC)
#define PHY_HW_GP_NORMAL			(PHY_PHYINITCTRL_WL_EN \
									| PHY_PHYINITCTRL_GT_EN \
									| PHY_PHYINITCTRL_GDST_EN \
									| PHY_PHYINITCTRL_WL2_EN \
									| PHY_PHYINITCTRL_RDET_EN \
									| PHY_PHYINITCTRL_WDET_EN \
									| PHY_PHYINITCTRL_DVREFT_EN \
									| PHY_PHYINITCTRL_HVREFT_EN \
									| PHY_PHYINITCTRL_PIC_TDQSST)
#define PHY_HW_GP_CNT_RESET_END	(PHY_PHYINITCTRL_PHYCONN_RST)

/* RDQS range[0, 0x1f],  middle value is 0x10 */
#define PHY_RDQS_MIDDLE_VAL		0x10
/* DQ range[0, 0x1f],  middle value is 0x10 */
#define PHY_DQ_MIDDLE_VAL		0x10101010
#define PHY_MISC_SCRAMB_DIS		0xfffeffff	/* scrambler disable */
/* NOTE: rdqsg_bdl is [5:0] in register manual, actual use [4:0] */
#define PHY_GATE_BDL_MAX        0x40 /* [4:0]rdqsg_bdl + [20:16]rdqsgtxbdl */
#define PHY_DVRFTCTRL_PDAEN_EN	0x80000000 /* pda enable */
/* [5] two cycle on address or command.(2T timing) */
#define PHY_DRAMCFG_MA2T		0x20

#define PHY_DRAMCFG_TYPE_DDR1 0x0     /* [2:0] 000 DDR1  */
#define PHY_DRAMCFG_TYPE_DDR2 0x1     /* [2:0] 001 DDR2 */
#define PHY_DRAMCFG_TYPE_DDR3 0x2     /* [2:0] 010 DDR3 */
#define PHY_DRAMCFG_TYPE_DDR3L 0x3    /* [2:0] 011 DDR3L */
#define PHY_DRAMCFG_TYPE_LPDDR1 0x4   /* [2:0] 100 LPDDR1 */
#define PHY_DRAMCFG_TYPE_LPDDR2 0x5   /* [2:0] 101 LPDDR2 */
#define PHY_DRAMCFG_TYPE_LPDDR3 0x5   /* [2:0] 101 LPDDR3 */
#define PHY_DRAMCFG_TYPE_LPDDR4 0x6   /* [2:0] 110 LPDDR4 */
#define PHY_DRAMCFG_TYPE_DDR4 0xa     /* [3] 1010 DDR4 */

/* other */
#define PHY_RDQSG_PHASE_STEP	4 /* gate training phase step. */
#define PHY_GATE_PHASE_MARGIN	8 /* gate phase margin */
#define PHY_DQ_BDL_LEVEL	32 /* [CUSTOM] DQ BDL range */
#define PHY_DQ_BDL_MIDDLE	15 /* middle DQ BDL value */
#define PHY_RDQSG_PHASE_MAX	0x3c /* RDQSG phase max value */
#define PHY_ACPHY_CLK_MAX	0xf /* halft_dramclk0 + cp1p_dclk0 */
#define PHY_PCODE_MIN		0x14
#define PHY_PCODE_MAX		0x24
/**
 * DDR_BDL_PHASE_REL Calculation Method:
 * 1. Calculation How many picosecond to one phase.
 *    PICOSECOND : 1 second is (1000 * 1000 * 1000) picosecond
 *    WAVE       : 1 cycle is 2
 *    RATE       : DDR rate is 1600 Mbps, is (1600 * 1000) bps
 *    PHASE      : 1 wave is 16 phase
 *    phase = (((PICOSECOND * WAVE) / RATE) / PHASE)
 *          = (((1000 * 1000 * 1000 * 2) / (1600 * 1000)) / 16)
 *          = 78.125 ps.
 * 2. Calculation How many bdl to one phase.
 *    one BDL is 20 ps.
 *    result = phase/bdl = 78.125 / 20 = 3.9 approximately equal to 4
 * 3. 4 = 1 << 2, so the relation is 2.
 */
#ifndef DDR_BDL_PHASE_TRANSFORM
/* [CUSTOM] one Phase equal how much BDL. 1 phase = 4 bdl */
#define DDR_BDL_PHASE_TRANSFORM		4
#endif
#ifndef DDR_BDL_PHASE_REL
/* [CUSTOM] relation between BDL and Phase. 1 phase = 4 bdl, 4 = 1 << 2 */
#define DDR_BDL_PHASE_REL		2
#endif

#define DDR_VARIABLE_DECLARE(var)

#define DDR_VREF_GET_HOST_MAX(rank, val) \
	do { \
		if (0 == rank) \
			val = PHY_VRFTRES_HVREF_MASK; \
		else \
			val = PHY_VRFTRES_RXDIFFCAL_MASK; \
	} while (0)

#define DDR_PHY_VREF_HOST_SET(base_phy, rank, bytenum, byte_index, val) \
	ddr_write(((val & 0x7) << 12) | ((val >> 3) & 0x3), \
		base_phy + DDR_PHY_IOCTL2)

#define DDR_PHY_VREF_HOST_GET(base_phy, rank, byte_index, val) \
	do { \
		unsigned int ref_range; \
		unsigned int ref_sel; \
		val = ddr_read(base_phy + DDR_PHY_IOCTL2); \
		ref_range = val & 0x3; \
		ref_sel   = (val >> 12) & 0x7; \
		val = (ref_range << 3) | ref_sel; \
	} while (0)

#define DDR_PHY_VREF_HOST_DISPLAY \
	{0, 0, DDR_PHY_IOCTL2, 0, "Host Vref"},

#define DDR_PHY_VREF_HOST_DISPLAY_RANK1

#define DDR_PHY_VREF_HOST_DISPLAY_CMD(base_phy, rank, byte_num) \
	DDR_INFO("[%x = %x] Host Vref", \
		base_phy + DDR_PHY_IOCTL2, \
		ddr_read(base_phy + DDR_PHY_IOCTL2));

/* phy s40 not support DRAM vref */
#define DDR_PHY_VREF_DRAM_SET(base_phy, val, byte_index)
#define DDR_PHY_VREF_DRAM_GET(base_phy, val, byte_index)
#define DDR_PHY_VREF_DRAM_DISPLAY
#define DDR_PHY_VREF_DRAM_DISPLAY_CMD(base_phy, byte_num)

/* phy s40 not support Lowpower ddr ca */
#define DDR_PHY_ADDRPH_DISPLAY
#define DDR_PHY_ADDRBDL_DISPLAY
#define DDR_PHY_ADDRPH_DISPLAY_CMD(base_phy)
#define DDR_PHY_ADDRBDL_DISPLAY_CMD(base_phy)

/* phy s40 not support DDR4 */
#define DDR_PHY_RDQS_SYNC_RDM(cfg, val)

/* phy s40 not support dqs swap */
#define DDR_DQSSWAP_SAVE_FUNC(swapdfibyte_en, base_phy)
#define DDR_DQSSWAP_RESTORE_FUNC(swapdfibyte_en, base_phy)

/* phy s40 not support rank switch */
#define DDR_PHY_SWITCH_RANK(base_phy, val)

/* phy s40 not support DCC training */
#define DDR_PHY_DCC_DISPLAY
#define DDR_PHY_DCC_DISPLAY_CMD(base_phy)
