/**
 * ddr_ddrc_v510.h
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
 *
 * DDRC V500 register define.
 */


/******** DMC **************************/
/* base address: DDR_REG_BASE_DMC0 DDR_REG_BASE_DMC1 */
/* register offset address */
#define DDR_DMC_CTRL_SREF		0X0     /* DDRC self-refresh control. */
#define DDR_DMC_CFG_SREF		0x20    /* DDRC self-refresh config. */
#define DDR_DMC_CFG_PD			0x28   /* PowerDown */
#define DDR_DMC_CFG_DDRMODE		0x50
#define DDR_DMC_CFG_SCRAMB		0x58   /* DDR scramb config */
#define DDR_DMC_CFG_RNKVOL(n)	(0x60 + ((n) << 2))
#define DDR_DMC_CFG_EMRS01		0xf0
#define DDR_DMC_TIMING2			0x108
#define DDR_DMC_SFCREQ			0xc
#define DDR_DMC_SFCCMD			0x210
#define DDR_DMC_SFCADDR			0x214   /* read col and row */
#define DDR_DMC_SFCBANK			0x218
#define DDR_DMC_CURR_FUNC		0x294
#ifndef DDR_DMC_SFC_RDATA0
#define DDR_DMC_SFC_RDATA0		0x4A8   /* SFC read data[31:0] */
#endif
#ifndef DDR_DMC_SFC_RDATA1
#define DDR_DMC_SFC_RDATA1		0x4AC   /* SFC read data[63:32] */
#endif
#ifndef DDR_DMC_SFC_RDATA2
#define DDR_DMC_SFC_RDATA2		0x4B0   /* SFC read data[95:64] */
#endif
#ifndef DDR_DMC_SFC_RDATA3
#define DDR_DMC_SFC_RDATA3		0x4B4   /* SFC read data[127:96] */
#endif
#ifndef DDR_DMC_SFC_RDATA4
#define DDR_DMC_SFC_RDATA4		0x4B8   /* SFC read data[159:128] */
#endif
#ifndef DDR_DMC_SFC_RDATA5
#define DDR_DMC_SFC_RDATA5		0x4BC   /* SFC read data[191:160] */
#endif
#ifndef DDR_DMC_SFC_RDATA6
#define DDR_DMC_SFC_RDATA6		0x4C0   /* SFC read data[223:192] */
#endif
#ifndef DDR_DMC_SFC_RDATA7
#define DDR_DMC_SFC_RDATA7		0x4C4   /* SFC read data[255:224] */
#endif

/* register mask */
#define DMC_CMD_MRS_MASK		0xffff
/* storing data bus width. [00]8bit, [01]16bit, [10]32bit, [11]64bit */
#define DMC_MEM_WIDTH_MASK		0x3
#define DMC_MRS_MASK			0xffff  /* [15:0] Mode Register mask */
#define DMC_MR0_BL_MASK			0x3
#define DMC_CFG_DRAM_TYPE_MASK	0xf /* [3:0]101:DDR2, 110:DDR3, 111:DDR4 */
#define DMC_CFG_MEM_BG_MASK		0x3 /* [11:10]0:1, 1:2, 2:4 Bank Group */
#define DMC_CURR_FUNC_IN_SREF_MASK		0x1
#define DMC_RNKVOL_MEM_BANK_MASK	0x3  /* [9:8] */
#define DMC_RNKVOL_MEM_ROW_MASK		0x7  /* [6:4] */
#define DMC_RNKVOL_MEM_COL_MASK		0x7  /* [2:0] */

/* register bit */
#define DMC_MEM_WIDTH_BIT		4       /* storing data bus width */
/* [CUSTOM] precharge disable/enable bit */
#define DMC_SFC_PRE_DIS_BIT		30
/* [CUSTOM] [29:12]config MR when LMR command */
#define DMC_SFC_CMD_MRS_BIT		12
#define DMC_SFC_RANK_BIT		16      /* [CUSTOM] [31:16]sfc_rank */
#define DMC_CFG_MEM_BG_BIT		10      /* [11:10] mem_bankgroup */
#define DMC_RNKVOL_MEM_BANK_BIT	8       /* [9:8] */
#define DMC_RNKVOL_MEM_ROW_BIT	4       /* [6:4] */

/* register value */
#define DMC_BANK_MR1			1
#define DMC_BANK_MR3			0x3
#define DMC_CMD_TYPE_LMR		0x2
#define DMC_CMD_TYPE_READ		0x5      /* read  */
#define DMC_CMD_TYPE_PRECHARGE_ALL	0x6      /* precharge all */
#define DMC_CMD_MRS_MR3			0x4      /* MR3 = 0x4 */
#define DMC_CMD_MRS_A7			0x80
/* value 1 means exexute command. cmd_rank[0] control DDR RANK0 */
#define DMC_CMD_RANK0			0x1
#define DMC_MR0_BL_BUST8		0x0      /* BC8 (fixed) */
#define DMC_MR0_BL_BUST4		0x2      /* BC4 (fixed) */
#define DMC_AUTO_TIMING_DIS		0xfffff000 /* auto refresh disable */
#define DMC_POWER_DOWN_DIS		0xfffffffe /* powerDown disable */
#define DMC_SCRAMB_DIS			0xffffbfff /* [14] scramb disable */
/* [4] scramb_seed_type, [2:0] scramb_seed_sort */
#define DMC_SCRAMB_CFG			0xffffffe8
#define DMC_CFG_DRAM_TYPE_DDR4	0x7        /* DDR4 */
#define DMC_CFG_DRAM_TYPE_LPDDR4	0x8        /* LPDDR4 */
#define DMC_CFG_MEM_2BG			0x1        /* 2 Bank Group */
#define DMC_CTRL_SREF_ENTER		0x1        /* 1 Enter Auto-self refresh */
#define DMC_CTRL_SREF_EXIT		0x2        /* 2 Exit Auto-self refresh */

#ifndef DDR_PHY_NUM
#define DDR_PHY_NUM             2 /* phy number */
#endif

#ifndef DDR_DMC_PER_PHY_MAX
#define DDR_DMC_PER_PHY_MAX     1
#endif

#ifndef DDR_RANK_NUM
#define DDR_RANK_NUM            1 /* rank number */
#endif

#define DMC_SFC_CMD_WRITE(sfc_cmd, addr) \
		ddr_write(sfc_cmd | (1 << DMC_SFC_PRE_DIS_BIT), addr)
#define DMC_SFC_BANK_WRITE(sfc_bank, addr) \
		ddr_write(sfc_bank | (DMC_CMD_RANK0 << DMC_SFC_RANK_BIT), addr)

#define DMC_MPR_CHECK_BIT_0_127(cfg) \
		ddr_mpr_extract(cfg, \
			DDR_DMC_SFC_RDATA3, DDR_DMC_SFC_RDATA2, \
			DDR_DMC_SFC_RDATA1, DDR_DMC_SFC_RDATA0)
#define DMC_MPR_CHECK_BIT_128_255(cfg) \
		ddr_mpr_extract(cfg, \
			DDR_DMC_SFC_RDATA7, DDR_DMC_SFC_RDATA6, \
			DDR_DMC_SFC_RDATA5, DDR_DMC_SFC_RDATA4)

/* dmc scramb */
#define DMC_SAVE_SCRAMB(relate_reg, i, base_dmc) \
	do { \
		relate_reg->dmc_scramb[i] = \
			ddr_read(base_dmc + DDR_DMC_CFG_DDRMODE); \
		relate_reg->dmc_scramb_cfg[i] = \
			ddr_read(base_dmc + DDR_DMC_CFG_SCRAMB); \
	} while (0)

#define DMC_DISABLE_SCRAMB(relate_reg, i, base_dmc) \
	do { \
		ddr_write(relate_reg->dmc_scramb[i] & DMC_SCRAMB_DIS, \
			base_dmc + DDR_DMC_CFG_DDRMODE); \
		ddr_write(relate_reg->dmc_scramb_cfg[i] & DMC_SCRAMB_CFG, \
			base_dmc + DDR_DMC_CFG_SCRAMB); \
	} while (0)

#define DMC_RESTORE_SCRAMB(relate_reg, i, base_dmc) \
	do { \
		ddr_write(relate_reg->dmc_scramb[i], \
			base_dmc + DDR_DMC_CFG_DDRMODE); \
		ddr_write(relate_reg->dmc_scramb_cfg[i], \
			base_dmc + DDR_DMC_CFG_SCRAMB); \
	} while (0)

/******** AXI **************************/
/**
 *              DMC -- PHY
 *             /
 * DDRT -- AXI
 *             \
 *              DMC -- PHY
 */
/* base address: DDR_REG_BASE_AXI */
/* register offset address */
#define DDR_AXI_REGION_ATTRIB0           0x104  /* region 0 */
#define DDR_AXI_REGION_ATTRIB1           0x114  /* region 1 */

/* register mask */
#define AXI_REGION_ATTRIB_CH_MASK        0xfffffff0 /* channel mask */

/* register value */
/* Map to the single channel, independent address */
#define AXI_RNG_ATTR_CH_MODE             0x4
#define AXI_RNG_ATTR_CH_START_0          0x0
#define AXI_RNG_ATTR_CH_START_1          0x1
#define AXI_RNG_NUM			             2   /* region number */

/********data define************************************/
struct ddr_ddrc_data {
	unsigned int region_attrib[AXI_RNG_NUM];
};

#define DDR_AXI_SAVE_FUNC(relate_reg) \
	do { \
		relate_reg->ddrc.region_attrib[0]   = \
			ddr_read(DDR_REG_BASE_AXI + DDR_AXI_REGION_ATTRIB0); \
		relate_reg->ddrc.region_attrib[1]   = \
			ddr_read(DDR_REG_BASE_AXI + DDR_AXI_REGION_ATTRIB1); \
	} while (0)

#define DDR_AXI_RESTORE_FUNC(relate_reg) \
	do { \
		ddr_write(relate_reg->ddrc.region_attrib[0], \
			DDR_REG_BASE_AXI + DDR_AXI_REGION_ATTRIB0); \
		ddr_write(relate_reg->ddrc.region_attrib[1], \
			DDR_REG_BASE_AXI + DDR_AXI_REGION_ATTRIB1); \
	} while (0)

#define DDR_AXI_SWITCH_FUNC(cfg) \
	do { \
		unsigned int ch_start = (cfg->phy_idx == 0 ? \
			AXI_RNG_ATTR_CH_START_0 : AXI_RNG_ATTR_CH_START_1); \
		ddr_write((ddr_read(DDR_REG_BASE_AXI + DDR_AXI_REGION_ATTRIB0) \
			& AXI_REGION_ATTRIB_CH_MASK) \
			| AXI_RNG_ATTR_CH_MODE | ch_start, \
			DDR_REG_BASE_AXI + DDR_AXI_REGION_ATTRIB0); \
		ddr_write((ddr_read(DDR_REG_BASE_AXI + DDR_AXI_REGION_ATTRIB1) \
			& AXI_REGION_ATTRIB_CH_MASK) \
			| AXI_RNG_ATTR_CH_MODE | ch_start, \
			DDR_REG_BASE_AXI + DDR_AXI_REGION_ATTRIB1); \
	} while (0)

#define DDR_RNKVOL_SET_FUNC(cfg)

/* ddrc v510 not support two rank */
#define DDR_RNKVOL_SAVE_FUNC(relate_reg, base_dmc)
#define DDR_RNKVOL_RESTORE_FUNC(relate_reg, base_dmc)
