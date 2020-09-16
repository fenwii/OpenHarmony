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

 * Description: DDR training implement
 */

#include "ddr_training_impl.h"
#include "ddr_interface.h"
#include <compiler.h>

#define __common__

unsigned int ddr_read(unsigned addr)
{
	return (*(volatile unsigned int *)((uintptr_t)(addr)));
}

void ddr_write(unsigned val, unsigned addr)
{
	(*(volatile unsigned int *)((uintptr_t)(addr))) = (val);
}

void* ddrtr_memcpy(void *dst, const void *src, unsigned int len)
{
	const char *s = src;
	char *d = dst;

	while (len--)
		*d++ = *s++;
	return dst;
}

void* ddrtr_memset(void *b, int c, unsigned int len)
{
	char *bp = b;

	while (len--)
		*bp++ = (unsigned char)c;
	return b;
}

int ddr_training_by_dmc(struct ddr_cfg_st *cfg)
{
	if (cfg->cmd_st) {
#ifdef DDR_TRAINING_CMD
		return ddr_training_cmd_func(cfg);
#endif
	} else {
		return ddr_training_boot_func(cfg);
	}
	return 0;
}

int ddr_training_by_rank(struct ddr_cfg_st *cfg)
{
	int result = 0;
	int i;

	DDR_PHY_SWITCH_RANK(cfg->cur_phy, cfg->rank_idx);

	for (i = 0; i < cfg->phy[cfg->phy_idx].dmc_num; i++) {
		cfg->dmc_idx = i;
		cfg->cur_dmc = cfg->phy[cfg->phy_idx].dmc[i].addr;
		cfg->cur_pattern = cfg->phy[cfg->phy_idx].dmc[i].ddrt_pattern;
		result += ddr_training_by_dmc(cfg);
	}
	return result;
}

int ddr_training_by_phy(struct ddr_cfg_st *cfg)
{
	int result = 0;
	int i;
	unsigned int phy_mask = 1 << (cfg->phy_idx);
	unsigned int rank_num = cfg->phy[cfg->phy_idx].rank_num;
	for (i = 0; i < rank_num; i++) {
		cfg->rank_idx = i;
		cfg->cur_item = cfg->phy[cfg->phy_idx].rank[i].item;
		if (ddr_training_check_bypass(cfg, phy_mask))
			continue;
		result += ddr_training_by_rank(cfg);
	}
	return result;
}

int ddr_training_all(struct ddr_cfg_st *cfg)
{
	int result = 0;
	int i;
	for (i = 0; i < cfg->phy_num; i++) {
		cfg->phy_idx = i;
		cfg->cur_phy = cfg->phy[i].addr;
		result += ddr_training_by_phy(cfg);
	}
	return result;
}

/* DDR training phy/dmc/dram_type config init */
void ddr_training_cfg_set_dmc(struct ddr_cfg_st *cfg)
{
	unsigned int ddrt_pattern;

	if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[0].dram_type) {
		cfg->phy[0].dmc_num = 2;
		ddrt_pattern = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDRT_PATTERN);
		cfg->phy[0].dmc[0].addr = DDR_REG_BASE_DMC0;
		cfg->phy[0].dmc[0].ddrt_pattern = ddrt_pattern & 0xffff;
		cfg->phy[0].dmc[0].byte_num = ddr_phy_get_byte_num(DDR_REG_BASE_DMC0);
		cfg->phy[0].dmc[1].addr = DDR_REG_BASE_DMC1;
		cfg->phy[0].dmc[1].ddrt_pattern = ddrt_pattern >> 16;
		cfg->phy[0].dmc[1].byte_num = ddr_phy_get_byte_num(DDR_REG_BASE_DMC1);
		cfg->phy[0].total_byte_num = cfg->phy[0].dmc[0].byte_num + cfg->phy[0].dmc[1].byte_num;
	} else {
		cfg->phy[0].dmc_num = 1;
		cfg->phy[0].dmc[0].addr = DDR_REG_BASE_DMC0;
		cfg->phy[0].dmc[0].ddrt_pattern = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDRT_PATTERN);
		cfg->phy[0].dmc[0].byte_num = ddr_phy_get_byte_num(DDR_REG_BASE_DMC0);
		cfg->phy[0].total_byte_num = cfg->phy[0].dmc[0].byte_num;
	}
	DDR_INFO("phy[0] total_byte_num[%x] dram_type[%x]", cfg->phy[0].total_byte_num, cfg->phy[0].dram_type);

#ifdef DDR_REG_BASE_PHY1
	if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[1].dram_type) {
		cfg->phy[1].dmc_num = 2;
		ddrt_pattern = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDRT_PATTERN_SEC);
		cfg->phy[1].dmc[0].addr = DDR_REG_BASE_DMC2;
		cfg->phy[1].dmc[0].ddrt_pattern = ddrt_pattern & 0xffff;
		cfg->phy[1].dmc[0].byte_num = ddr_phy_get_byte_num(DDR_REG_BASE_DMC2);
		cfg->phy[1].dmc[1].addr = DDR_REG_BASE_DMC3;
		cfg->phy[1].dmc[1].ddrt_pattern = ddrt_pattern >> 16;
		cfg->phy[1].dmc[1].byte_num = ddr_phy_get_byte_num(DDR_REG_BASE_DMC3);
		cfg->phy[1].total_byte_num = cfg->phy[1].dmc[0].byte_num + cfg->phy[1].dmc[1].byte_num;
	} else {
		cfg->phy[1].dmc_num = 1;
		cfg->phy[1].dmc[0].addr = DDR_REG_BASE_DMC1;
		cfg->phy[1].dmc[0].ddrt_pattern = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDRT_PATTERN_SEC);
		cfg->phy[1].dmc[0].byte_num = ddr_phy_get_byte_num(DDR_REG_BASE_DMC1);
		cfg->phy[1].total_byte_num = cfg->phy[1].dmc[0].byte_num;
	}
	DDR_INFO("phy[1] total_byte_num[%x] dram_type[%x]", cfg->phy[1].total_byte_num, cfg->phy[1].dram_type);
#endif
}
void ddr_training_cfg_set_rank(struct ddr_cfg_st *cfg)
{
	cfg->phy[0].rank_num = 1;
	cfg->phy[0].rank[0].item = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG);
	cfg->phy[0].rank[0].item_hw = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_HW_PHY0_RANK0);

	cfg->phy[0].rank[1].item = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG_SEC);
	cfg->phy[0].rank[1].item_hw = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_HW_PHY0_RANK1);

	if (ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_HW_PHY0_RANK1)) {
		cfg->phy[0].rank_num = 2;
	}

	DDR_INFO("Rank number PHY0 [%x]", cfg->phy[0].rank_num);
	DDR_INFO("HW training item PHY0[%x = %x][%x = %x]",
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_HW_PHY0_RANK0), cfg->phy[0].rank[0].item_hw,
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_HW_PHY0_RANK1), cfg->phy[0].rank[1].item_hw);

#ifdef DDR_REG_BASE_PHY1
	cfg->phy[1].rank_num = 1;
	cfg->phy[1].rank[0].item = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG);
	cfg->phy[1].rank[0].item_hw = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_HW_PHY1_RANK0);

	cfg->phy[1].rank[1].item = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG_SEC);
	cfg->phy[1].rank[1].item_hw = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_HW_PHY1_RANK1);


	if (ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_HW_PHY1_RANK1)) {
		cfg->phy[1].rank_num = 2;
	}

	DDR_INFO("Rank number PHY1[%x]", cfg->phy[1].rank_num);
	DDR_INFO("HW training item PHY1[%x = %x][%x = %x]",
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_HW_PHY1_RANK0), cfg->phy[1].rank[0].item_hw,
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_HW_PHY1_RANK1), cfg->phy[1].rank[1].item_hw);
#endif

	DDR_INFO("SW training item Rank0[%x = %x] Rank1[%x = %x]",
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG), cfg->phy[0].rank[0].item,
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG_SEC), cfg->phy[0].rank[1].item);
}

void ddr_training_cfg_set_phy(struct ddr_cfg_st *cfg)
{
	cfg->phy_num = DDR_PHY_NUM;
	cfg->phy[0].addr = DDR_REG_BASE_PHY0;
	cfg->phy[0].dram_type = ddr_read(DDR_REG_BASE_PHY0 + DDR_PHY_DRAMCFG)
		& PHY_DRAMCFG_TYPE_MASK;
#ifdef DDR_REG_BASE_PHY1
	cfg->phy[1].addr = DDR_REG_BASE_PHY1;
	cfg->phy[1].dram_type = ddr_read(DDR_REG_BASE_PHY1 + DDR_PHY_DRAMCFG)
		& PHY_DRAMCFG_TYPE_MASK;
#endif
}

void ddr_training_cfg_init(struct ddr_cfg_st *cfg)
{
	ddrtr_memset(cfg, 0, sizeof(struct ddr_cfg_st));
	ddr_training_cfg_set_phy(cfg);
	ddr_training_cfg_set_dmc(cfg);
	ddr_training_cfg_set_rank(cfg);
}

/* 2GHz CPU run 2000 "nop" in 1 ns */
static inline void ddr_training_delay(unsigned int cnt)
{
	while (cnt--)
		asm("nop");
}

/* set auto refresh */
void ddr_training_set_timing(unsigned int base_dmc, unsigned int timing)
{
	ddr_training_delay(DDR_AUTO_TIMING_DELAY);
	ddr_write(timing, base_dmc + DDR_DMC_TIMING2);
	/* need to delay 1 ns */
	ddr_training_delay(DDR_AUTO_TIMING_DELAY);
}

#ifdef DDR_TRAINING_STAT_CONFIG
/* Save training result in stat register */
static void ddr_training_save(unsigned int mask, unsigned int phy,
			      int byte, int dq)
{
	unsigned int stat;
	unsigned int phy_index;

	stat = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_STAT);
	/* only record the first error */
	if (stat)
		return;

	stat = mask;

	if (0 != phy) {
		phy_index = (DDR_REG_BASE_PHY0 == phy ?
			DDR_ERR_PHY0 : DDR_ERR_PHY1);
		stat |= phy_index;
	}

	if (-1 != byte)
		stat |= ((unsigned int)byte << DDR_ERR_BYTE_BIT);

	if (-1 != dq)
		stat |= ((unsigned int)dq << DDR_ERR_DQ_BIT);

	ddr_write(stat, DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_STAT);
}
#endif

/* Record error code in register */
void ddr_training_stat(unsigned int mask, unsigned int phy, int byte, int dq)
{
	ddr_training_error(mask, phy, byte, dq);
#ifdef DDR_TRAINING_STAT_CONFIG
	ddr_training_save(mask, phy, byte, dq);
#endif
}

/* Check DDR training item whether by pass */
int ddr_training_check_bypass(struct ddr_cfg_st *cfg, unsigned int mask)
{
	/* training item disable */
	if ((cfg->cur_item) & mask) {
		DDR_DEBUG("DDR training [%x] is disable, rank[%x] cfg[%x]",
			mask, cfg->rank_idx, cfg->cur_item);
		return DDR_TRUE;
	} else {
		return DDR_FALSE;
	}
}

#if !defined(DDR_TRAINING_CUT_CODE_CONFIG) || defined(DDR_TRAINING_CMD)
/**
 * Check PHY whether disable.
 * DDR_TRUE: PHY is disable.
 * DDR_FALSE: PHY is not disable.
 */
int ddr_training_phy_disable(int index)
{
	return 0;
}

/* Save register value before training */
void ddr_training_save_reg(struct ddr_cfg_st *cfg,
			   struct tr_relate_reg *relate_reg, unsigned int mask)
{
	unsigned int base_dmc = cfg->cur_dmc;
	unsigned int base_phy = cfg->cur_phy;

	/* save reg value */
	relate_reg->auto_ref_timing =
		ddr_read(base_dmc + DDR_DMC_TIMING2);
	relate_reg->power_down =
		ddr_read(base_dmc + DDR_DMC_CFG_PD);
	relate_reg->misc_scramb = ddr_read(base_phy + DDR_PHY_MISC);
	/* Static register have to read two times to get the right value. */
	relate_reg->ac_phy_ctl =
		ddr_read(base_phy + DDR_PHY_ACPHYCTL4);
	relate_reg->ac_phy_ctl =
		ddr_read(base_phy + DDR_PHY_ACPHYCTL4);

	/* set new value */
	switch (mask) {
	case DDR_BYPASS_WL_MASK:
	case DDR_BYPASS_LPCA_MASK:
		/* disable auto refresh */
		ddr_training_set_timing(base_dmc,
			relate_reg->auto_ref_timing & DMC_AUTO_TIMING_DIS);
		break;
	case DDR_BYPASS_GATE_MASK:
		/* disable auto refresh */
		ddr_training_set_timing(base_dmc,
			relate_reg->auto_ref_timing & DMC_AUTO_TIMING_DIS);

		if (!(ddr_read(base_phy + DDR_PHY_DRAMCFG) & PHY_DRAMCFG_MA2T)) /* set 1T */
			ddr_write(0x0, base_phy + DDR_PHY_ACPHYCTL4);
		break;
	case DDR_BYPASS_HW_MASK:
		if (!(ddr_read(base_phy + DDR_PHY_DRAMCFG) & PHY_DRAMCFG_MA2T)) /* set 1T */
			ddr_write(0x0, base_phy + DDR_PHY_ACPHYCTL4);
		break;
	default:
		break;
	}

	ddr_write(relate_reg->power_down & DMC_POWER_DOWN_DIS,
		base_dmc + DDR_DMC_CFG_PD);
	ddr_write(relate_reg->misc_scramb & PHY_MISC_SCRAMB_DIS,
		base_phy + DDR_PHY_MISC);

	DDR_DQSSWAP_SAVE_FUNC(relate_reg->swapdfibyte_en, base_phy);

	DDR_AXI_SAVE_FUNC(relate_reg);

	DDR_RNKVOL_SAVE_FUNC(relate_reg, base_dmc);

	/* save customer reg */
	DDR_TRAINING_SAVE_REG_FUNC((void *)relate_reg, mask);

	ddr_phy_cfg_update(base_phy);

	DDR_ASM_DSB();
}

/* Restore register value after training */
void ddr_training_restore_reg(struct ddr_cfg_st *cfg,
			      struct tr_relate_reg *relate_reg)
{
	unsigned int base_dmc = cfg->cur_dmc;
	unsigned int base_phy = cfg->cur_phy;

	/* enable auto refresh */
	ddr_training_set_timing(base_dmc, relate_reg->auto_ref_timing);
	ddr_write(relate_reg->power_down, base_dmc + DDR_DMC_CFG_PD);
	ddr_write(relate_reg->misc_scramb, base_phy + DDR_PHY_MISC);
	if (!(ddr_read(base_phy + DDR_PHY_DRAMCFG) & PHY_DRAMCFG_MA2T))
		ddr_write(relate_reg->ac_phy_ctl, base_phy + DDR_PHY_ACPHYCTL4);

	DDR_DQSSWAP_RESTORE_FUNC(relate_reg->swapdfibyte_en, base_phy);

	DDR_AXI_RESTORE_FUNC(relate_reg);

	DDR_RNKVOL_RESTORE_FUNC(relate_reg, base_dmc);

	/* restore customer reg */
	DDR_TRAINING_RESTORE_REG_FUNC((void *)relate_reg);

	ddr_phy_cfg_update(base_phy);

	DDR_ASM_DSB();
}

/* Switch AXI to DMC0/DMC1/DMC2/DMC3 for DDRT test */
void ddr_training_switch_axi(struct ddr_cfg_st *cfg)
{
	DDR_AXI_SWITCH_FUNC(cfg);

	DDR_RNKVOL_SET_FUNC(cfg);
}
#endif

#if defined(DDR_WL_TRAINING_CONFIG) || defined(DDR_MPR_TRAINING_CONFIG)

/* Excute DMC sfc command */
static void ddr_dmc_sfc_cmd(unsigned int base_dmc, unsigned int sfc_cmd,
			    unsigned int sfc_addr, unsigned int sfc_bank)
{
	unsigned int count = 0;

	/* set sfc cmd */
	DMC_SFC_CMD_WRITE(sfc_cmd, base_dmc + DDR_DMC_SFCCMD);
	/* set col and row */
	ddr_write(sfc_addr, base_dmc + DDR_DMC_SFCADDR);
	/* set bank */
	DMC_SFC_BANK_WRITE(sfc_bank, base_dmc + DDR_DMC_SFCBANK);
	/* excute cmd */
	ddr_write(0x1, base_dmc + DDR_DMC_SFCREQ);

	DDR_ASM_DSB();

	while (count < DDR_SFC_WAIT_TIMEOUT) { /* wait command finished */
		if (!(ddr_read(base_dmc + DDR_DMC_SFCREQ) & 0x1))
			break;

		count++;
	}

	if (count >= DDR_HWR_WAIT_TIMEOUT)
		DDR_ERROR("SFC cmd wait timeout.");
}
#endif

#if defined(DDR_HW_TRAINING_CONFIG) || defined(DDR_DCC_TRAINING_CONFIG)

/* Exit or enter auto self-refresh */
static int ddr_training_easr(unsigned int base_dmc, unsigned int sref_req)
{
	unsigned int count = DDR_HWR_WAIT_TIMEOUT;
	if (DDR_EXIT_SREF == sref_req) {
		/* Exit Auto-self refresh */
		ddr_write(DMC_CTRL_SREF_EXIT, base_dmc + DDR_DMC_CTRL_SREF);

		while (count--) {
			if (!(ddr_read(base_dmc + DDR_DMC_CURR_FUNC)
				& DMC_CURR_FUNC_IN_SREF_MASK))
				break;
		}
	} else if (DDR_ENTER_SREF == sref_req) {
		/* Enter Auto-self refresh */
		ddr_write(DMC_CTRL_SREF_ENTER, base_dmc + DDR_DMC_CTRL_SREF);

		while (count--) {
			if (ddr_read(base_dmc + DDR_DMC_CURR_FUNC)
				& DMC_CURR_FUNC_IN_SREF_MASK)
				break;
		}
	}

	if (count == 0xffffffff) {
		DDR_FATAL("SREF wait timeout.");
		ddr_training_stat(DDR_ERR_HW_RD_DATAEYE, -1, -1, -1);
		return -1;
	}
	return 0;
}

/* DDR hw/dcc training exit or enter auto self-refresh */
static int ddr_training_ctrl_easr(struct ddr_cfg_st *cfg, unsigned int sref_req)
{
	int result = 0;
	int i;
	struct ddr_phy_st *phy_st =  &cfg->phy[cfg->phy_idx];

	for (i = 0; i < phy_st->dmc_num; i++) {
		result += ddr_training_easr(phy_st->dmc[i].addr, sref_req);
	}

	return result;
}

static void ddr_training_save_timing(struct ddr_cfg_st *cfg, struct ddr_timing_st *timing_st)
{
	int i;
	struct ddr_phy_st *phy_st =  &cfg->phy[cfg->phy_idx];

	for (i = 0; i < phy_st->dmc_num; i++) {

		timing_st->val[i] = ddr_read(phy_st->dmc[i].addr + DDR_DMC_TIMING2);
		/* disable auto refresh */
		ddr_training_set_timing(phy_st->dmc[i].addr, timing_st->val[i] & DMC_AUTO_TIMING_DIS);
	}
}

static void ddr_training_restore_timing(struct ddr_cfg_st *cfg, struct ddr_timing_st *timing_st)
{
	int i;
	struct ddr_phy_st *phy_st =  &cfg->phy[cfg->phy_idx];
	for (i = 0; i < phy_st->dmc_num; i++) {
		ddr_training_set_timing(phy_st->dmc[i].addr, timing_st->val[i]);
	}
}
#endif /* DDR_HW_TRAINING_CONFIG ||  DDR_DCC_TRAINING_CONFIG*/

/**
 * Update delay setting in registers to PHY immediately.
 * Make delay setting take effect.
 */
void ddr_phy_cfg_update(unsigned int base_phy)
{
	unsigned int tmp;

	tmp = ddr_read(base_phy + DDR_PHY_MISC);
	tmp |= (1 << PHY_MISC_UPDATE_BIT);
	/* update new config to PHY */
	ddr_write(tmp, base_phy + DDR_PHY_MISC);
	tmp &= ~(1 << PHY_MISC_UPDATE_BIT);
	ddr_write(tmp, base_phy + DDR_PHY_MISC);
	tmp = ddr_read(base_phy + DDR_PHY_PHYINITCTRL);
	/* set 1 to issue PHY counter reset signal */
	tmp |= (1 << PHY_PHYCONN_RST_BIT);
	ddr_write(tmp, base_phy + DDR_PHY_PHYINITCTRL);
	/* set 0 to end the reset signal */
	tmp &= ~(1 << PHY_PHYCONN_RST_BIT);
	ddr_write(tmp, base_phy + DDR_PHY_PHYINITCTRL);

	DDR_ASM_DSB();
}

/* Set delay value of the bit delay line of the DATA block */
void ddr_phy_set_dq_bdl(struct ddr_cfg_st *cfg, unsigned int value)
{
	unsigned int val;
	unsigned int offset;
	unsigned int dq;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_index = cfg->cur_byte;
	unsigned int rank = cfg->rank_idx;

	dq = cfg->cur_dq & 0x7;
	if (DDR_MODE_WRITE == cfg->cur_mode) {
		if (dq < 4)
			offset = DDR_PHY_DXNWDQNBDL0(rank, byte_index);
		else
			offset = DDR_PHY_DXNWDQNBDL1(rank, byte_index);
	} else {
		if (dq < 4)
			offset = DDR_PHY_DXNRDQNBDL0(rank, byte_index);
		else
			offset = DDR_PHY_DXNRDQNBDL1(rank, byte_index);
	}

	dq &= 0x3;
	val = ddr_read(base_phy + offset);
	val &= ~(0xFF << (dq << 3));
	val |= ((PHY_BDL_MASK & value) << ((dq << 3) + PHY_BDL_DQ_BIT));
	ddr_write(val, base_phy + offset);

	ddr_phy_cfg_update(base_phy);
}

/* Get PHY DQ value */
unsigned int ddr_phy_get_dq_bdl(struct ddr_cfg_st *cfg)
{
	unsigned int val;
	unsigned int offset;
	unsigned int dq;
	unsigned int byte_index = cfg->cur_byte;
	unsigned int rank = cfg->rank_idx;

	dq = cfg->cur_dq & 0x7;
	if (DDR_MODE_WRITE == cfg->cur_mode) {
		if (dq < 4)
			offset = DDR_PHY_DXNWDQNBDL0(rank, byte_index);
		else
			offset = DDR_PHY_DXNWDQNBDL1(rank, byte_index);
	} else {
		if (dq < 4)
			offset = DDR_PHY_DXNRDQNBDL0(rank, byte_index);
		else
			offset = DDR_PHY_DXNRDQNBDL1(rank, byte_index);
	}

	dq &= 0x3;
	val = (ddr_read(cfg->cur_phy + offset) >> ((dq << 3) + PHY_BDL_DQ_BIT)) & PHY_BDL_MASK;

	return val;
}

/* Get byte number */
unsigned int ddr_phy_get_byte_num(unsigned int base_dmc)
{
	unsigned int byte_num;

	/* memery width -> byte number */
	byte_num = ((ddr_read(base_dmc + DDR_DMC_CFG_DDRMODE)
		>> DMC_MEM_WIDTH_BIT) & DMC_MEM_WIDTH_MASK) << 1;

	/* for codedex */
	if (byte_num > DDR_PHY_BYTE_MAX) {
		byte_num = DDR_PHY_BYTE_MAX;
		DDR_ERROR("get byte num fail");
	}

	return byte_num;
}


static void ddr_rdqs_sync_rdm(struct ddr_cfg_st *cfg, int offset)
{
	unsigned int rdqnbdl;
	int rdm;

	rdqnbdl = ddr_read(cfg->cur_phy + DDR_PHY_DXNRDQNBDL2(cfg->rank_idx, cfg->cur_byte));
	rdm = (rdqnbdl >> PHY_RDM_BDL_BIT) & PHY_RDM_BDL_MASK;
	rdm += offset;
	rdm = (rdm < 0 ? 0 : rdm);
	rdm = (rdm > PHY_RDM_BDL_MASK ? PHY_RDM_BDL_MASK : rdm);
	rdqnbdl = rdqnbdl & (~(PHY_RDM_BDL_MASK << PHY_RDM_BDL_BIT));
	ddr_write(rdqnbdl | ((unsigned int)rdm << PHY_RDM_BDL_BIT), cfg->cur_phy + DDR_PHY_DXNRDQNBDL2(cfg->rank_idx, cfg->cur_byte));
}

static void ddr_rdqs_sync_rank_rdq(struct ddr_cfg_st *cfg, int offset)
{
	int dq_val;
	int i;

	/* sync other rank rdm */
	ddr_rdqs_sync_rdm(cfg, offset);

	/* sync other rank rdq */
	DDR_DEBUG("Before sync rank[%x] byte[%x] dq[%x = %x][%x = %x] offset[%x]",
		cfg->rank_idx, cfg->cur_byte,
		cfg->cur_phy + DDR_PHY_DXNRDQNBDL0(cfg->rank_idx, cfg->cur_byte),
		ddr_read(cfg->cur_phy + DDR_PHY_DXNRDQNBDL0(cfg->rank_idx, cfg->cur_byte)),
		cfg->cur_phy + DDR_PHY_DXNRDQNBDL1(cfg->rank_idx, cfg->cur_byte),
		ddr_read(cfg->cur_phy + DDR_PHY_DXNRDQNBDL1(cfg->rank_idx, cfg->cur_byte)), offset);

	for (i = 0; i < DDR_PHY_BIT_NUM; i++) {
		cfg->cur_dq = i;
		dq_val = (int)ddr_phy_get_dq_bdl(cfg);
		dq_val += offset;
		dq_val = (dq_val < 0 ? 0 : dq_val);
		dq_val = (dq_val > PHY_BDL_MASK ? PHY_BDL_MASK : dq_val);
		ddr_phy_set_dq_bdl(cfg, dq_val);
	}

	DDR_DEBUG("After sync rank[%x] byte[%x] dq[%x = %x][%x = %x]",
		cfg->rank_idx, cfg->cur_byte,
		cfg->cur_phy + DDR_PHY_DXNRDQNBDL0(cfg->rank_idx, cfg->cur_byte),
		ddr_read(cfg->cur_phy + DDR_PHY_DXNRDQNBDL0(cfg->rank_idx, cfg->cur_byte)),
		cfg->cur_phy + DDR_PHY_DXNRDQNBDL1(cfg->rank_idx, cfg->cur_byte),
		ddr_read(cfg->cur_phy + DDR_PHY_DXNRDQNBDL1(cfg->rank_idx, cfg->cur_byte)));
}

static void ddr_bdl_adj(struct ddr_cfg_st *cfg)
{
	int i;
	int value_num = 10;
	unsigned int rank = cfg->rank_idx;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_idx = cfg->cur_byte;
	unsigned int bdl[value_num];
	unsigned int min = 0xffffffff;
	unsigned int dq03, dq47, rdm, rdqs;

	dq03 = ddr_read(base_phy + DDR_PHY_DXNRDQNBDL0(rank, byte_idx));
	dq47 = ddr_read(base_phy + DDR_PHY_DXNRDQNBDL1(rank, byte_idx));
	rdm = ddr_read(base_phy + DDR_PHY_DXNRDQNBDL2(rank, byte_idx));
	rdqs = ddr_read(base_phy + DDR_PHY_DXNRDQSDLY(byte_idx));

	bdl[0] = (dq03 >> PHY_BDL_DQ0_BIT) & PHY_BDL_MASK;
	bdl[1] = (dq03 >> PHY_BDL_DQ1_BIT) & PHY_BDL_MASK;
	bdl[2] = (dq03 >> PHY_BDL_DQ2_BIT) & PHY_BDL_MASK;
	bdl[3] = (dq03 >> PHY_BDL_DQ3_BIT) & PHY_BDL_MASK;
	bdl[4] = (dq47 >> PHY_BDL_DQ0_BIT) & PHY_BDL_MASK;
	bdl[5] = (dq47 >> PHY_BDL_DQ1_BIT) & PHY_BDL_MASK;
	bdl[6] = (dq47 >> PHY_BDL_DQ2_BIT) & PHY_BDL_MASK;
	bdl[7] = (dq47 >> PHY_BDL_DQ3_BIT) & PHY_BDL_MASK;
	bdl[8] = (rdm >> PHY_RDM_BDL_BIT) & PHY_RDM_BDL_MASK;
	bdl[9] = (rdqs >> PHY_RDQS_BDL_BIT) & PHY_RDQS_BDL_MASK;

	for (i = 0; i < value_num; i++) {
		if (bdl[i] < min)
			min = bdl[i];
	}

	dq03 = ((bdl[0] - min) << PHY_BDL_DQ0_BIT) | ((bdl[1] - min) << PHY_BDL_DQ1_BIT) |
			((bdl[2] - min) << PHY_BDL_DQ2_BIT) | ((bdl[3] - min) << PHY_BDL_DQ3_BIT);
	dq47 = ((bdl[4] - min) << PHY_BDL_DQ0_BIT) | ((bdl[5] - min) << PHY_BDL_DQ1_BIT) |
			((bdl[6] - min) << PHY_BDL_DQ2_BIT) | ((bdl[7] - min) << PHY_BDL_DQ3_BIT);
	rdm = (rdm & (~(PHY_RDM_BDL_MASK << PHY_RDM_BDL_BIT))) | ((bdl[8] - min) << PHY_RDM_BDL_BIT);
	rdqs = (rdqs & (~(PHY_RDQS_BDL_MASK << PHY_RDQS_BDL_BIT))) | ((bdl[9] - min) << PHY_RDQS_BDL_BIT);

	ddr_write(dq03, base_phy + DDR_PHY_DXNRDQNBDL0(rank, byte_idx));
	ddr_write(dq47, base_phy + DDR_PHY_DXNRDQNBDL1(rank, byte_idx));
	ddr_write(rdm, base_phy + DDR_PHY_DXNRDQNBDL2(rank, byte_idx));
	ddr_write(rdqs, base_phy + DDR_PHY_DXNRDQSDLY(byte_idx));
}

#define __ddrt__
#ifdef DDR_DDRT_SPECIAL_CONFIG
/* Some special DDRT need read register repeatedly */
static unsigned int ddr_ddrt_read(unsigned int addr)
{
	int times = 0;
	unsigned int data0, data1, data2;
	do {
		data0 = ddr_read(addr);
		data1 = ddr_read(addr);
		data2 = ddr_read(addr);
		times++;
	} while (((data0 != data1) || (data1 != data2))
			&& (times < DDRT_READ_TIMEOUT));

	if (times >= DDRT_READ_TIMEOUT) {
		DDR_FATAL("DDRT wait timeout.");
		ddr_training_stat(DDR_ERR_DDRT_TIME_OUT, 0, -1, -1);
	}

	return data0;
}

/* Some special DDRT need write twice register */
static void ddr_ddrt_write(unsigned int data, unsigned int addr)
{
	unsigned int tmp;
	tmp = ddr_read(addr);
	ddr_write(data, addr);
	ddr_write(data, addr);
}
#endif /* DDR_DDRT_SPECIAL_CONFIG */

static unsigned int ddr_get_rank_size(struct ddr_cfg_st *cfg)
{
	unsigned int base_dmc = cfg->cur_dmc;
	unsigned int rnkvol;
	unsigned int mem_bank, mem_row, mem_col, mem_width;
	unsigned int size;

	mem_width = (ddr_read(base_dmc + DDR_DMC_CFG_DDRMODE) >> DMC_MEM_WIDTH_BIT) & DMC_MEM_WIDTH_MASK;
	rnkvol = ddr_read(base_dmc + DDR_DMC_CFG_RNKVOL(0));
	mem_bank = (rnkvol >> DMC_RNKVOL_MEM_BANK_BIT) & DMC_RNKVOL_MEM_BANK_MASK;
	mem_row = (rnkvol >> DMC_RNKVOL_MEM_ROW_BIT) & DMC_RNKVOL_MEM_ROW_MASK;
	mem_col = rnkvol & DMC_RNKVOL_MEM_COL_MASK;

	size = 1UL << ((mem_bank + 2) + (mem_row + 11) + (mem_col + 8) + mem_width);
	DDR_DEBUG("rank size[%x]", size);

	return size;
}

/* Init DDRT register before DDRT test */
void ddr_ddrt_init(struct ddr_cfg_st *cfg, unsigned int mode)
{
	unsigned int mem_width;
	unsigned int mem_config;
	unsigned int offset = 0;

	if (1 == cfg->rank_idx)
		offset = ddr_get_rank_size(cfg);

	DDR_TRAINING_DDRT_PREPARE_FUNC();

	mem_width = ((ddr_read(cfg->cur_dmc + DDR_DMC_CFG_DDRMODE)
				>> DMC_MEM_WIDTH_BIT) & DMC_MEM_WIDTH_MASK);
	mem_config = ((mem_width - 1) << DDRT_DDR_MEM_WIDTH)
				| DDRT_DDR_COL_WIDTH | DDRT_DDR_ROW_WIDTH
				| DDRT_DDR_BANK_WIDTH;
	/* DDRT SDRAM config */
	DDRT_REG_WRITE(mem_config, DDR_REG_BASE_DDRT + DDRT_MEM_CONFIG);
	/* DDR Address Base */
	DDRT_REG_WRITE(DDRT_GET_TEST_ADDR(DDRT_CFG_BASE_ADDR),
		DDR_REG_BASE_DDRT + DDRT_DDR_BASE_ADDR);
	/* DDRT test DDR using space */
	DDRT_REG_WRITE(DDRT_GET_TEST_ADDR(ddr_ddrt_get_test_addr() + offset),
		DDR_REG_BASE_DDRT + DDRT_ADDR);
	DDRT_REG_WRITE(DDRT_CFG_SEED, DDR_REG_BASE_DDRT + DDRT_SEED);

	if (DDR_DDRT_MODE_GATE == mode) {
		/* Read or Write Once */
		DDRT_REG_WRITE(DDRT_CFG_BURST_CFG_GATE,
			DDR_REG_BASE_DDRT + DDRT_BURST_CONFIG);
		DDRT_REG_WRITE(0x0,  DDR_REG_BASE_DDRT + DDRT_BURST_NUM);
		DDRT_REG_WRITE(0x0,  DDR_REG_BASE_DDRT + DDRT_ADDR_NUM);
		DDRT_REG_WRITE(0x0,  DDR_REG_BASE_DDRT + DDRT_LOOP_NUM);
		DDRT_REG_WRITE(DDRT_CFG_REVERSED,
			DDR_REG_BASE_DDRT + DDRT_REVERSED_DQ);
	} else {
		/* reversed data form register init table */
		/* 128bit BURST4 */
		DDRT_REG_WRITE(DDRT_CFG_BURST_CFG_DATAEYE,
			DDR_REG_BASE_DDRT + DDRT_BURST_CONFIG);
		DDRT_REG_WRITE(cfg->phy[cfg->phy_idx].dmc[cfg->dmc_idx].ddrt_pattern,
			DDR_REG_BASE_DDRT + DDRT_REVERSED_DQ);
		DDRT_REG_WRITE(DDRT_CFG_BURST_NUM,
			DDR_REG_BASE_DDRT + DDRT_BURST_NUM);
		DDRT_REG_WRITE(DDRT_CFG_ADDR_NUM,
			DDR_REG_BASE_DDRT + DDRT_ADDR_NUM);
		DDRT_REG_WRITE(DDRT_CFG_LOOP_NUM,
			DDR_REG_BASE_DDRT + DDRT_LOOP_NUM);
	}

	DDR_DEBUG("DDRT ADDR[%x = %x]", (DDR_REG_BASE_DDRT + DDRT_ADDR),
		ddr_read(DDR_REG_BASE_DDRT + DDRT_ADDR));
}

/**
 * ddr_ddrt_test
 * @mask : DDRT option mask.
 * @byte : DDR byte index.
 * @dq   : DDR dq index.
 *
 * DDRT test. Support read_only mode and write_read_compare mode.
 * Success return 0, fail return -1.
 */
int ddr_ddrt_test(unsigned int mask, int byte, int dq)
{
	unsigned int regval;
	unsigned int err_ovfl;
	unsigned int err_cnt;
	unsigned int dq_num;
	unsigned int dq_tmp;
	unsigned int times = 0;

	DDRT_REG_WRITE(mask | DDRT_CFG_START, DDR_REG_BASE_DDRT + DDRT_OP);
	DDRT_REG_WRITE(0, DDR_REG_BASE_DDRT + DDRT_STATUS);

	DDR_ASM_DSB();

	do {
		regval = DDRT_REG_READ(DDR_REG_BASE_DDRT + DDRT_STATUS);
		times++;
	} while ((!(regval & DDRT_TEST_DONE_MASK))
			&& (times < DDRT_WAIT_TIMEOUT));

	if (times >= DDRT_WAIT_TIMEOUT) {
		DDR_FATAL("DDRT wait timeout.");
		ddr_training_stat(DDR_ERR_DDRT_TIME_OUT, 0, -1, -1);
		return -1;
	}

	/* DDRT_READ_ONLY_MODE */
	if (DDRT_READ_ONLY_MODE == (mask & DDRT_TEST_MODE_MASK))
		return 0;   /* return when DDRT finish */

	/* DDRT_WR_COMPRARE_MODE No error occurred, test pass. */
	if (regval & DDRT_TEST_PASS_MASK)
		return 0;

	if (-1 != dq) { /* check for dq */
		dq_num = ((unsigned int)byte << 3) + dq;
		err_ovfl = DDRT_REG_READ(DDR_REG_BASE_DDRT
			+ DDRT_DQ_ERR_OVFL) & (1 << dq_num);
		if (err_ovfl)
			return -1;

		if (dq > 3)
			dq_tmp = (unsigned int)(dq - 4) << 3;
		else
			dq_tmp = (unsigned int)dq << 3;
		err_cnt = DDRT_REG_READ(DDR_REG_BASE_DDRT
			+ DDRT_DQ_ERR_CNT(((unsigned int)byte << 1) + ((unsigned int)dq >> 2)));
		err_cnt = err_cnt & (0xff << dq_tmp);
		if (err_cnt)
			return -1;
	} else if (-1 != byte) { /* check for byte */
		err_ovfl = DDRT_REG_READ(DDR_REG_BASE_DDRT
			+ DDRT_DQ_ERR_OVFL) & (0xff << ((unsigned int)byte << 3));
		if (err_ovfl)
			return -1;

		err_cnt  = DDRT_REG_READ(DDR_REG_BASE_DDRT
				+ DDRT_DQ_ERR_CNT((unsigned int)byte << 1));
		err_cnt += DDRT_REG_READ(DDR_REG_BASE_DDRT
				+ DDRT_DQ_ERR_CNT(((unsigned int)byte << 1) + 1));
		if (err_cnt)
			return -1;
	}

	return 0;
}

/* Check ddrt test result. Success return 0, fail return -1 */
static int ddr_ddrt_check(struct ddr_cfg_st *cfg)
{
	unsigned int byte_index_to_dmc = cfg->cur_byte;

	/* ddrt test the byte relate to dmc, make sure not overflow */
	if (cfg->cur_byte >= (cfg->dmc_idx << 1))
		byte_index_to_dmc = cfg->cur_byte - (cfg->dmc_idx << 1);

	DDRT_REG_WRITE(0, DDR_REG_BASE_DDRT + DDRT_REVERSED_DQ);
	if (ddr_ddrt_test(DDRT_WR_COMPRARE_MODE | DDRT_PATTERM_PRBS9,
		byte_index_to_dmc, cfg->cur_dq))
		return -1;

	DDRT_REG_WRITE(cfg->cur_pattern, DDR_REG_BASE_DDRT + DDRT_REVERSED_DQ);
	if (ddr_ddrt_test(DDRT_WR_COMPRARE_MODE | DDRT_PATTERM_PRBS11,
		byte_index_to_dmc, cfg->cur_dq))
		return -1;

	return 0;
}

#define __dataeye_adjust__
#ifdef DDR_TRAINING_ADJUST_CONFIG
static unsigned int ddr_adjust_get_average(struct ddr_cfg_st *cfg)
{
	unsigned int dq0_3, dq4_7, val;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_index = cfg->cur_byte;
	unsigned int rank = cfg->rank_idx;

	if (DDR_MODE_WRITE == cfg->cur_mode)
		return (ddr_read(base_phy + DDR_PHY_DXNWDQNBDL2(rank, byte_index))
			>> PHY_WDM_BDL_BIT) & PHY_BDL_MASK;

	/* read */
	dq0_3 = ddr_read(base_phy + DDR_PHY_DXNRDQNBDL0(rank, byte_index));
	dq4_7 = ddr_read(base_phy + DDR_PHY_DXNRDQNBDL1(rank, byte_index));

	val = ((dq0_3 >> PHY_BDL_DQ0_BIT) & PHY_BDL_MASK)
		+ ((dq0_3 >> PHY_BDL_DQ1_BIT) & PHY_BDL_MASK)
		+ ((dq0_3 >> PHY_BDL_DQ2_BIT) & PHY_BDL_MASK)
		+ ((dq0_3 >> PHY_BDL_DQ3_BIT) & PHY_BDL_MASK)
		+ ((dq4_7 >> PHY_BDL_DQ0_BIT) & PHY_BDL_MASK)
		+ ((dq4_7 >> PHY_BDL_DQ1_BIT) & PHY_BDL_MASK)
		+ ((dq4_7 >> PHY_BDL_DQ2_BIT) & PHY_BDL_MASK)
		+ ((dq4_7 >> PHY_BDL_DQ3_BIT) & PHY_BDL_MASK);

	val = val >> 3;
	return val;
}

/**
 * ddr_adjust_trend_check
 * @accel : Return a value to adjust quickly.
 *
 * Check dataeye DQ window on left or right or middle.
 */
static unsigned int ddr_adjust_trend_check(struct ddr_cfg_st *cfg, int *accel)
{
	unsigned int dq_bdl = 0;
	unsigned int size;

	/* 32 BDL middle[13, 17]. 128 BDL middle[40, 56] */
	/* 1 Phase = (DDR_BDL_PHASE_TRANSFORM) BDL */
	size = DDR_BDL_PHASE_TRANSFORM >> 1;

	dq_bdl =  ddr_adjust_get_average(cfg);

	/* increase adjust step to accelerate */
	if (accel) {
		if (dq_bdl > PHY_DQ_BDL_MIDDLE)
			*accel = dq_bdl - PHY_DQ_BDL_MIDDLE;
		else if (dq_bdl < PHY_DQ_BDL_MIDDLE)
			*accel = PHY_DQ_BDL_MIDDLE - dq_bdl;

		DDR_INFO("byte[%x] bdl[%x] middle[%x] accel[%x] rdqs[%x]",
			cfg->cur_byte, dq_bdl, PHY_DQ_BDL_MIDDLE, *accel,
			(ddr_read(cfg->cur_phy + DDR_PHY_DXNRDQSDLY(cfg->cur_byte))
			>> PHY_RDQS_BDL_BIT) & PHY_RDQS_BDL_MASK);
	}

	/* window on left */
	if (dq_bdl < (PHY_DQ_BDL_MIDDLE - size))
		return DDR_WIN_LEFT;
	/* on right */
	else if (dq_bdl > (PHY_DQ_BDL_MIDDLE + size))
		return DDR_WIN_RIGHT;
	else
		return DDR_WIN_MIDDLE;
}

/* Check adjust value whether valid */
static int ddr_adjust_check_val(int val, unsigned int mode)
{
	if (DDR_MODE_READ == mode) {
		if (val < 0 || val > PHY_RDQS_BDL_MASK)
			return DDR_FALSE;
	} else {
		if (val < 0 || val > PHY_WDQ_PHASE_MASK)
			return DDR_FALSE;
	}

	return DDR_TRUE;
}

/* Get value which need to adjust */
static int ddr_adjust_get_val(struct ddr_cfg_st *cfg)
{
	if (DDR_MODE_READ == cfg->cur_mode)
		return (ddr_read(cfg->cur_phy + DDR_PHY_DXNRDQSDLY(cfg->cur_byte))
		>> PHY_RDQS_BDL_BIT) & PHY_RDQS_BDL_MASK;
	else
		return (ddr_read(cfg->cur_phy + DDR_PHY_DXNWDQDLY(cfg->rank_idx, cfg->cur_byte))
		>> PHY_WDQ_PHASE_BIT) & PHY_WDQ_PHASE_MASK;
}

static void ddr_rdqs_sync(struct ddr_cfg_st *cfg, int val)
{
	unsigned int rdqsdly;
	unsigned int cur_rank = cfg->rank_idx;
	int old, offset;

	rdqsdly = ddr_read(cfg->cur_phy + DDR_PHY_DXNRDQSDLY(cfg->cur_byte));
	old = (rdqsdly >> PHY_RDQS_BDL_BIT) & PHY_RDQS_BDL_MASK;
	offset = val - old;

	/* sync rdm */
	ddr_rdqs_sync_rank_rdq(cfg, offset);

	if (1 == cfg->phy[cfg->phy_idx].rank_num) {
		DDR_DEBUG("Rank number[%x] not need sync another rank", cfg->phy[cfg->phy_idx].rank_num);
		return;
	}

	/* sync other rank rdm and rdq */
	cfg->rank_idx = DDR_SUPPORT_RANK_MAX - 1 - cur_rank; /* switch to another rank */
	ddr_rdqs_sync_rank_rdq(cfg, offset);
	cfg->rank_idx = cur_rank; /* resotre to cur rank */
}

static void ddr_set_rdqs(struct ddr_cfg_st *cfg, int val)
{
	unsigned int delay;
	delay = ddr_read(cfg->cur_phy + DDR_PHY_DXNRDQSDLY(cfg->cur_byte));

	DDR_PHY_RDQS_SYNC_RDM(cfg, val);

	/* clear rdqs bdl */
	delay = delay & (~(PHY_RDQS_BDL_MASK << PHY_RDQS_BDL_BIT));

	ddr_write(delay | ((unsigned int)val << PHY_RDQS_BDL_BIT),
		cfg->cur_phy + DDR_PHY_DXNRDQSDLY(cfg->cur_byte));
}

/* Set value which need to adjust */
static void ddr_adjust_set_val(struct ddr_cfg_st *cfg, int val)
{
	unsigned int delay;
	if (DDR_MODE_READ == cfg->cur_mode) {
		ddr_set_rdqs(cfg, val);
	} else {
		delay = ddr_read(cfg->cur_phy + DDR_PHY_DXNWDQDLY(cfg->rank_idx, cfg->cur_byte));
		/* clear wdq phase */
		delay = delay & (~(PHY_WDQ_PHASE_MASK << PHY_WDQ_PHASE_BIT));

		ddr_write(delay | ((unsigned int)val << PHY_WDQ_PHASE_BIT),
			cfg->cur_phy + DDR_PHY_DXNWDQDLY(cfg->rank_idx, cfg->cur_byte));
	}

	ddr_phy_cfg_update(cfg->cur_phy);
}

/* Add or delete value to adjust */
static void ddr_adjust_change_val(unsigned int dir, int *val,
				  int step, unsigned int mode)
{
	if (DDR_MODE_READ == mode) {
		if (DDR_WIN_RIGHT == dir)
			(*val) = (*val) + step;
		else
			(*val) = (*val) - step;
	} else {
		/* decrease wdq phase, window move to right */
		if (DDR_WIN_RIGHT == dir)
				(*val) = (*val) - step;
			else
				(*val) = (*val) + step;
	}
}

/**
 * ddr_adjust_move_win
 * @dir : move direction. DDR_TRUE move to right, DDR_FALSE move to left.
 *
 * Move window to specified direction until the best DQ bdl beyond the midline.
 */
static void ddr_adjust_move_win(struct ddr_cfg_st *cfg,
				struct training_data *training,
				int step, unsigned int dir)
{
	int cur_val, def_val;
	int i;
	int accel;
	int trend;
	unsigned int max_value;

	max_value = (DDR_MODE_WRITE == cfg->cur_mode ?
		PHY_WDQ_PHASE_MASK : PHY_RDQS_BDL_MASK);

	def_val = ddr_adjust_get_val(cfg);
	cur_val = def_val;
	for (i = 0; i <= max_value; i++) {
		accel = step;
		/* write mode no need to accelerate */
		if (DDR_MODE_WRITE == cfg->cur_mode)
			trend = ddr_adjust_trend_check(cfg, 0);
		else
			trend = ddr_adjust_trend_check(cfg, &accel);

		if (DDR_WIN_MIDDLE == trend || dir == trend) {
			DDR_DEBUG("Move byte[%x] window to middle suc", cfg->cur_byte);
			break;
		}

		ddr_adjust_change_val(dir, &cur_val, accel, cfg->cur_mode);
		if (DDR_FALSE == ddr_adjust_check_val(cur_val, cfg->cur_mode)) {
			DDR_WARNING("Move byte[%x] to middle fail. value[%x]",
						cfg->cur_byte, cur_val);
			break;
		}

		DDR_DEBUG("Byte[%x] mode[%x] set value[%x]",
			cfg->cur_byte, cfg->cur_mode, cur_val);
		ddr_adjust_set_val(cfg, cur_val);
		if (ddr_dataeye_deskew(cfg, training)) {
			ddr_adjust_set_val(cfg, def_val);
			/* MUST deskew dataeye after restore rdqs */
			ddr_dataeye_deskew(cfg, training);
			DDR_ERROR("Byte[%x] deskew fail, restore[%x]",
					cfg->cur_byte, def_val);
			break;
		}
	}
}

/* Adjust specified byte winodw to middle */
static void ddr_adjust_byte(struct ddr_cfg_st *cfg, struct training_data *training)
{
	unsigned int trend = ddr_adjust_trend_check(cfg, 0);

	/* window on left, move to right */
	if (DDR_WIN_LEFT == trend)
		ddr_adjust_move_win(cfg, training, DDR_DQS_ADJ_STEP, DDR_WIN_RIGHT);
	/* window on right, move to left */
	else if (DDR_WIN_RIGHT == trend)
		ddr_adjust_move_win(cfg, training, DDR_DQS_ADJ_STEP, DDR_WIN_LEFT);
	/* window on middle, no need to move */
	else
		DDR_DEBUG("Byte[%x] mode[%x] win on middle.",
			cfg->cur_byte, cfg->cur_mode);
}

/**
 * Adjust PHY dataeye. On normal case,
 * read dateeye window on left after read dataeye hardware training,
 * write dataeye window on left after write leveling training.
 *
 */
void ddr_adjust_dataeye(struct ddr_cfg_st *cfg, struct training_data *training)
{
	int i;

	/* dataeye adjust disable */
	if (ddr_training_check_bypass(cfg, DDR_BYPASS_DATAEYE_ADJ_MASK))
		return;

	DDR_DEBUG("DDR dataeye adjust PHY[%x][%x] DMC[%x][%x] Rank[%x]",
		cfg->phy_idx, cfg->cur_phy, cfg->dmc_idx, cfg->cur_dmc, cfg->rank_idx);

	if (DDR_FALSE == cfg->adjust)
		return;

	for (i = 0; i < GET_BYTE_NUM(cfg); i++) {
		cfg->cur_byte = i + (cfg->dmc_idx << 1); /* byte index accord to phy */
		ddr_adjust_byte(cfg, training);
	}
}
#else
#define ddr_adjust_dataeye(cfg, training)
#endif /* DDR_TRAINING_ADJUST_CONFIG */

#define __dataeye_training__
#ifdef DDR_DATAEYE_TRAINING_CONFIG
/* Check dataeye dq */
int ddr_dataeye_check_dq(struct ddr_cfg_st *cfg)
{
	if (DDR_CHECK_TYPE_DDRT == cfg->dq_check_type)
		return ddr_ddrt_check(cfg);
	else if (DDR_CHECK_TYPE_MPR == cfg->dq_check_type)
		return ddr_mpr_check(cfg);
	else
		DDR_ERROR("DDR dataeye dq check type not set.");

	return 0;
}

/* Check dq whether valid and set mask to reduce search time */
static int ddr_dataeye_check_dir(unsigned int direction, unsigned int left,
				 unsigned int right, unsigned int *mask,
				 struct ddr_cfg_st *cfg)
{
	int result = 0;

	result = ddr_dataeye_check_dq(cfg);
	switch (direction) {
	case DDR_FIND_DQ_BOTH:
		*mask = DDR_FIND_DQ_LEFT | DDR_FIND_DQ_RIGHT;
		break;
	case DDR_FIND_DQ_LEFT:
		if (result) {
			/* ddr test error, search opposite side */
			*mask = DDR_FIND_DQ_RIGHT;
		} else {		/* ddr test ok */
			ddr_phy_set_dq_bdl(cfg, left);
			if (!ddr_dataeye_check_dq(cfg))
				/* test ok, go on search this side */
				*mask = DDR_FIND_DQ_LEFT;
		}
		break;
	case DDR_FIND_DQ_RIGHT:
		if (result) {  /* ddr test error, search opposite side */
			*mask = DDR_FIND_DQ_LEFT;
		} else {		/* ddr test ok */
			ddr_phy_set_dq_bdl(cfg, right);
			if (!ddr_dataeye_check_dq(cfg))
				/* test OK, go on search this side */
				*mask = DDR_FIND_DQ_RIGHT;
		}
		break;
	default:
		break;
	}

	return result;
}

/* Binary search the valid dq bdl */
static void ddr_dataeye_search_dq(unsigned int left, unsigned int right,
				  int *target, unsigned int direction,
				  struct ddr_cfg_st *cfg)

{
	unsigned int middle;
	unsigned int mask = 0;

	middle = left + ((right - left) >> 1);

	ddr_phy_set_dq_bdl(cfg, middle);
	if (!ddr_dataeye_check_dir(direction, left, right, &mask, cfg)) { /* test ok */
		*target = (int)middle;
		return;
	}

	if (left == middle || middle == right)  /* not found */
		return;

	/* find left side */
	if (DDR_FIND_DQ_LEFT & mask)
		ddr_dataeye_search_dq(left, middle, target, direction, cfg);

	/* find right side */
	if (DDR_FIND_DQ_RIGHT & mask)
		ddr_dataeye_search_dq(middle, right, target, direction, cfg);

	return;
}

/* Find DQ valid range */
static void ddr_dataeye_find_dq(struct ddr_cfg_st *cfg,
				struct training_data *training)
{
	int cur_dq, left_dq, right_dq, def_dq;
	unsigned int dq_num;
	unsigned int win_num;

	dq_num = (cfg->cur_byte << 3) + cfg->cur_dq;
	def_dq = (int)ddr_phy_get_dq_bdl(cfg);
	cur_dq = def_dq;

	/* check default dq */
	if (ddr_dataeye_check_dq(cfg)) {
		/* test error */
		cur_dq = -1;
		ddr_dataeye_search_dq(0, PHY_BDL_MASK, &cur_dq,
			DDR_FIND_DQ_BOTH, cfg);
		DDR_DEBUG("DQ[%x] def[%x] nok, find new value[%x]",
			dq_num, def_dq, cur_dq);
		if (-1 == cur_dq) {  /* no valid dq */
			training->ddr_bit_result[dq_num] = 0;
			training->ddr_bit_best[dq_num]   = 0;
			/* restore default value */
			ddr_phy_set_dq_bdl(cfg, def_dq);
			DDR_WARNING("DQ[%x] not found dq. restore[%x]", dq_num, def_dq);
			return;
		}
	}

	/* find the left boundary */
	left_dq = cur_dq;
	ddr_dataeye_search_dq(0, cur_dq, &left_dq,
		DDR_FIND_DQ_LEFT, cfg);
	while (left_dq > 0) {
		left_dq--;
		ddr_phy_set_dq_bdl(cfg, left_dq);
		if (ddr_dataeye_check_dq(cfg)) {
			/* test error */
			left_dq++;
			break;
		}
	}

	/* find the right boundary */
	right_dq = cur_dq;
	ddr_dataeye_search_dq(cur_dq, PHY_BDL_MASK, &right_dq,
		DDR_FIND_DQ_RIGHT, cfg);
	while (right_dq < PHY_BDL_MASK) {
		right_dq++;
		ddr_phy_set_dq_bdl(cfg, right_dq);
		if (ddr_dataeye_check_dq(cfg)) {
			/* test error */
			right_dq--;
			break;
		}
	}

	/* reset dq */
	ddr_phy_set_dq_bdl(cfg, def_dq);

	/**
	 * 0 1 2 3 4 5 6 7 8 9
	 * x x - - - - - x x x
	 *     |       |
	 * left_dq   right_dq
	 *
	 * so left_dq = 2, right_dq = 6
	 */
	/* set result */
	win_num = right_dq - left_dq + 1;
	training->ddr_bit_result[dq_num] = ((unsigned int)left_dq << DDR_DATAEYE_RESULT_BIT
		| (unsigned int)right_dq);
	training->ddr_bit_best[dq_num] = (win_num << DDR_DATAEYE_RESULT_BIT)
		| ((win_num >> 1) + (unsigned int)left_dq);

	DDR_INFO("DQ[%x] range: left[%x] right[%x] best[%x] mode[%x] rank[%x]", dq_num,
		left_dq, right_dq, training->ddr_bit_best[dq_num], cfg->cur_mode, cfg->rank_idx);
}

/* DDR dataeye training one byte */
int ddr_dataeye_deskew(struct ddr_cfg_st *cfg, struct training_data *training)
{
	unsigned int dq_num;
	unsigned int loop_times = 0;
	unsigned int win_num, dq_sum;
	unsigned int def_dq, best_dq;
	int i;
	unsigned int byte_index = cfg->cur_byte;

	dq_sum = 0;
	training->ddr_win_sum = 0;
	for (i = 0; i < DDR_PHY_BIT_NUM; i++) {
		cfg->cur_dq = i;
		dq_num = (byte_index << 3) + i;
		def_dq = ddr_phy_get_dq_bdl(cfg);
		ddr_dataeye_find_dq(cfg, training);
		win_num = training->ddr_bit_best[dq_num] >> DDR_DATAEYE_RESULT_BIT;
		best_dq = training->ddr_bit_best[dq_num] & DDR_DATAEYE_RESULT_MASK;
		/* check window number */
		if (win_num < DDR_DATAEYE_WIN_NUM) {
			if (loop_times < DDR_LOOP_TIMES_LMT) {
				loop_times++;
				i--;
				continue;
			} else {
				if (win_num == 0) {
					DDR_WARNING("Byte[%x] DQ[%x] no win.", byte_index, dq_num);
					/* restore default value */
					ddr_phy_set_dq_bdl(cfg, def_dq);
					ddr_training_stat(DDR_ERR_DATAEYE, cfg->cur_phy, byte_index, i);
					continue;
				}
			}
		}

		loop_times = 0;
		ddr_phy_set_dq_bdl(cfg, best_dq);
		dq_sum = dq_sum + best_dq;
		training->ddr_win_sum = training->ddr_win_sum + win_num;
	}

	dq_sum = dq_sum >> 3;

	/* only DDR_MODE_WRITE need to set */
	if (DDR_MODE_WRITE == cfg->cur_mode)
		ddr_write((dq_sum & PHY_BDL_MASK) << PHY_WDM_BDL_BIT, cfg->cur_phy
			+ DDR_PHY_DXNWDQNBDL2(cfg->rank_idx, byte_index));

	ddr_phy_cfg_update(cfg->cur_phy);
	return 0;
}

/* DDR write or read dataeye training */
static int ddr_dataeye_process(struct ddr_cfg_st *cfg,
			       struct training_data *training)
{
	int result = 0;
	int i;

	/* dataeye training */
	for (i = 0; i < GET_BYTE_NUM(cfg); i++) {
		cfg->cur_byte = i + (cfg->dmc_idx << 1); /* byte index accord to phy */
		result += ddr_dataeye_deskew(cfg, training);
	}

	if (result) {
		result = -1;
		DDR_ERROR("PHY[%x] mode[%x] dataeye training fail", cfg->cur_phy, cfg->cur_mode);
	} else {
		/* dataeye training result adjust */
		ddr_adjust_dataeye(cfg, training);
	}

	/* save training result to printf */
	ddr_result_data_save(cfg, training);

	return result;
}

/* DDR dataeye training */
int ddr_dataeye_training(struct ddr_cfg_st *cfg)
{
	struct training_data tmp_result;
	struct training_data *training = &tmp_result;
	int result_read, result_write;

	DDR_DEBUG("DDR dataeye training PHY[%x][%x] DMC[%x][%x] Rank[%x]",
		cfg->phy_idx, cfg->cur_phy, cfg->dmc_idx, cfg->cur_dmc, cfg->rank_idx);

	/* write dataeye training */
	cfg->cur_mode = DDR_MODE_WRITE;
	ddrtr_memset(training, 0, sizeof(struct training_data));
	result_write = ddr_dataeye_process(cfg, training);

	/* read dataeye training */
	cfg->cur_mode = DDR_MODE_READ;
	ddrtr_memset(training, 0, sizeof(struct training_data));
	result_read = ddr_dataeye_process(cfg, training);

	if (result_read || result_write)
		return -1;
	else
		return 0;
}

int ddr_dataeye_training_func(struct ddr_cfg_st *cfg)
{
	struct tr_relate_reg relate_reg;
	int result;

	/* dataeye training disable */
	if (ddr_training_check_bypass(cfg, DDR_BYPASS_DATAEYE_MASK))
		return 0;

	ddr_training_save_reg(cfg, &relate_reg, DDR_BYPASS_DATAEYE_MASK);
	ddr_training_switch_axi(cfg);
	ddr_ddrt_init(cfg, DDR_DDRT_MODE_DATAEYE);
	cfg->adjust = DDR_DATAEYE_NORMAL_ADJUST;
	cfg->dq_check_type = DDR_CHECK_TYPE_DDRT;
	result = ddr_dataeye_training(cfg);
	ddr_training_restore_reg(cfg, &relate_reg);

	return result;
}
#else
int ddr_dataeye_training_func(struct ddr_cfg_st *cfg)
{
	DDR_WARNING("Not support DDR dataeye training.");
	return 0;
}
#endif  /* DDR_DATAEYE_TRAINING_CONFIG */

#define __hardware_training__
#ifdef DDR_HW_TRAINING_CONFIG
#ifdef DDR_HW_READ_ADJ_CONFIG
/**
 * Adjust rdqs and dq after hw read training.
 * When define DDR_TRAINING_ADJUST_DISABLE, MUST define DDR_HW_READ_ADJ_CONFIG.
 */
static void ddr_hw_read_adj(struct ddr_cfg_st *cfg)
{
	int i;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_num = cfg->phy[cfg->phy_idx].total_byte_num;

	DDR_DEBUG("DDR hw read adjust.");
	/* check hw read adjust bypass bit */
	if (ddr_training_check_bypass(cfg, DDR_BYPASS_HW_ADJ_MASK))
		return;

	/* assume read dataeye window on left */
	for (i = 0; i < byte_num; i++) {
		ddr_write(ddr_read(base_phy + DDR_PHY_DXNRDQNBDL0(cfg->rank_idx, i))
			+ (PHY_DQ_MIDDLE_VAL << PHY_BDL_DQ_BIT),
			base_phy + DDR_PHY_DXNRDQNBDL0(cfg->rank_idx, i));
		ddr_write(ddr_read(base_phy + DDR_PHY_DXNRDQNBDL1(cfg->rank_idx, i))
			+ (PHY_DQ_MIDDLE_VAL << PHY_BDL_DQ_BIT),
			base_phy + DDR_PHY_DXNRDQNBDL1(cfg->rank_idx, i));
		ddr_write(ddr_read(base_phy + DDR_PHY_DXNRDQSDLY(i))
			+ (PHY_RDQS_MIDDLE_VAL << PHY_RDQS_BDL_BIT),
			base_phy + DDR_PHY_DXNRDQSDLY(i));
	}
}
#else
static void ddr_hw_read_adj(struct ddr_cfg_st *cfg) {}
#endif /* DDR_HW_READ_ADJ_CONFIG */

static void ddr_training_get_rdqs(struct ddr_cfg_st *cfg, struct ddr_bdl_st *rdqs)
{
	unsigned int i;
	unsigned int byte_num = cfg->phy[cfg->phy_idx].total_byte_num;
	unsigned int base_phy = cfg->cur_phy;

	for(i = 0; i < byte_num; i++) {
		rdqs->bdl[i] = ddr_read(base_phy + DDR_PHY_DXNRDQSDLY(i));
	}
}

static void ddr_training_set_rdqs(struct ddr_cfg_st *cfg, struct ddr_bdl_st *rdqs)
{
	unsigned int i;
	unsigned int byte_num = cfg->phy[cfg->phy_idx].total_byte_num;
	unsigned int base_phy = cfg->cur_phy;

	for (i = 0; i < byte_num; i++) {
		ddr_write(rdqs->bdl[i], base_phy + DDR_PHY_DXNRDQSDLY(i));
	}
}

static void ddr_hw_training_adjust_rdqs(struct ddr_cfg_st *cfg, struct rdqs_data_st *rdqs_st)
{
	unsigned int i;
	unsigned int byte_num = cfg->phy[cfg->phy_idx].total_byte_num;
	unsigned int rdqs_rank0, rdqs_rank1;
	unsigned int cur_rank = cfg->rank_idx;
	int offset;

	for (i = 0; i < byte_num; i++) {
		/* struct rdqs_data_st store the whole register value */
		rdqs_rank0 = (rdqs_st->rank[0].bdl[i] >> PHY_RDQS_BDL_BIT) & PHY_RDQS_BDL_MASK;
		rdqs_rank1 = (rdqs_st->rank[1].bdl[i] >> PHY_RDQS_BDL_BIT) & PHY_RDQS_BDL_MASK;

		cfg->cur_byte = i;
		if (rdqs_rank0 > rdqs_rank1) {
			offset = rdqs_rank0 - rdqs_rank1;
			ddr_write(rdqs_st->rank[0].bdl[i], cfg->cur_phy+ DDR_PHY_DXNRDQSDLY(i));
			cfg->rank_idx = 1; /* switch to rank1 for sync rank1 rdq */
		} else {
			offset = rdqs_rank1 - rdqs_rank0;
			ddr_write(rdqs_st->rank[1].bdl[i], cfg->cur_phy+ DDR_PHY_DXNRDQSDLY(i));
			cfg->rank_idx = 0; /* switch to rank0 for sync rank0 rdq */
		}
		ddr_rdqs_sync_rank_rdq(cfg, offset);
	}

	cfg->rank_idx = cur_rank; /* restore to current rank */

	ddr_phy_cfg_update(cfg->cur_phy);
}

/* DDR HW training process */
static int ddr_hw_training_process(struct ddr_cfg_st *cfg, unsigned int item)
{
	unsigned int count = DDR_HWR_WAIT_TIMEOUT;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int init_ctrl = ddr_read(base_phy + DDR_PHY_PHYINITCTRL);

	if (!item)
		return 0;

	DDR_DEBUG("base_phy[%x] itme[%x]", base_phy, item);
	/* hardware training enable */
	ddr_write(item | PHY_PHYINITCTRL_INIT_EN | init_ctrl, base_phy + DDR_PHY_PHYINITCTRL);

	if (item & PHY_PHYINITCTRL_DRAM_RST) {
		if (ddr_training_ctrl_easr(cfg, DDR_EXIT_SREF))
			return -1;
	}

	count = DDR_HWR_WAIT_TIMEOUT;
	/* auto cleared to 0 after training finished */
	while (count--) {
		if (!(ddr_read(base_phy + DDR_PHY_PHYINITCTRL)
			& PHY_PHYINITCTRL_MASK))
			break;
	}

	if (count == 0xffffffff) {
		DDR_FATAL("HWR wait timeout.");
		ddr_training_stat(DDR_ERR_HW_RD_DATAEYE, base_phy, item, ddr_read(base_phy + DDR_PHY_PHYINITSTATUS)); /* TODO: */
		return -1;
	}

	if (ddr_read(base_phy + DDR_PHY_PHYINITSTATUS)) {
		DDR_FATAL("Phy[%x] hw[%x] failed[%x]", base_phy, item, ddr_read(base_phy + DDR_PHY_PHYINITSTATUS));
		ddr_training_stat(DDR_ERR_HW_RD_DATAEYE, base_phy, item, ddr_read(base_phy + DDR_PHY_PHYINITSTATUS)); /* TODO: */
		return -1;
	}
	return 0;
}

/* Dataeye hardware training */
int ddr_hw_dataeye_read(struct ddr_cfg_st *cfg)
{
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_num = cfg->phy[cfg->phy_idx].total_byte_num;

	unsigned int i;
	int result;

	ddr_training_cfg_init(cfg);
	/* clear */
	for (i = 0; i < byte_num; i++) {
		ddr_write(0, base_phy + DDR_PHY_DXNRDQNBDL0(cfg->rank_idx, i));
		ddr_write(0, base_phy + DDR_PHY_DXNRDQNBDL1(cfg->rank_idx, i));
		ddr_write(0, base_phy + DDR_PHY_DXNRDQSDLY(i));
	}

	ddr_phy_cfg_update(base_phy);

	result = ddr_hw_training_process(cfg, PHY_PHYINITCTRL_RDET_EN);

	ddr_hw_read_adj(cfg);

	return result;
}

/* DDR HW training control */
int ddr_hw_training_ctl(struct ddr_cfg_st *cfg)
{
	int byte_idx;
	int result = 0;
	unsigned int temp = 0;
	unsigned int item = cfg->cur_item;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_num = cfg->phy[cfg->phy_idx].total_byte_num;
	unsigned int dvrft_ctrl = ddr_read(base_phy + DDR_PHY_DVRFTCTRL);
	struct rdqs_data_st *rdqs_st = (struct rdqs_data_st *)cfg->res_st;

	if (!item || !rdqs_st)
		return 0;

	ddr_phy_cfg_update(base_phy);
	/* NOTE: not support array when boot */
	result += ddr_hw_training_process(cfg, item & PHY_HW_GP_CNT_RESET_START);
	result += ddr_hw_training_process(cfg, item & PHY_HW_GP_PLL);

	/* save rdqs bdl after PHY_PHYINITCTRL_DLYMEAS_EN */
	if (0 == cfg->rank_idx)
		ddr_training_get_rdqs(cfg, &rdqs_st->origin);

	for (byte_idx = 0; byte_idx < byte_num; byte_idx++) {
		cfg->cur_byte = byte_idx;
		ddr_bdl_adj(cfg);
	}

	if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[cfg->phy_idx].dram_type) {
		temp = ddr_read(base_phy + 0x64);
		ddr_write(temp & 0x0fffffff, base_phy + 0x64); /* ca odt disable */

		result += ddr_hw_training_process(cfg, item & PHY_HW_GP_DRAM_RESET);
		ddr_write(temp, base_phy + 0x64); /* restore */

		temp = ddr_read(base_phy + 0x48);
		ddr_write(temp & 0xfffffffe, base_phy + 0x48); /* todo rank0 */

		result += ddr_hw_training_process(cfg, item & PHY_HW_GP_VREF_AC);

		ddr_write(temp | 0x1, base_phy + 0x48); /* rank1 */

		result += ddr_hw_training_process(cfg, item & PHY_HW_GP_VREF_AC);

		ddr_write(temp, base_phy + 0x48); /* restore */

		/* ddr_training_delay(10000); */
		result += ddr_hw_training_process(cfg, item & PHY_PHYINITCTRL_DRAM_INIT_EN);
	} else {
#ifdef DDR_WRITE_DM_DISABLE
		if (PHY_DRAMCFG_TYPE_DDR4 == cfg->phy[cfg->phy_idx].dram_type) {
			temp = ddr_read(base_phy + 0xe0);
			ddr_write((temp & 0xFBFFFFFF) | 0x8000000, base_phy + 0xe0); /* write dm disable */
		}
#endif
		result += ddr_hw_training_process(cfg, item & PHY_HW_GP_DRAM_RESET);
	}
	result += ddr_hw_training_process(cfg, item & PHY_PHYINITCTRL_CAT_EN);

	result += ddr_hw_training_process(cfg, item & PHY_HW_GP_CS);

	ddr_write(dvrft_ctrl & (~PHY_DVRFTCTRL_PDAEN_EN),
		base_phy + DDR_PHY_DVRFTCTRL);
	/* DDR_PHY_VREFTCTRL 31bit:1 do vref dram set twice */
	ddr_write((ddr_read(base_phy + DDR_PHY_VREFTCTRL)
		& (~(0x1 << PHY_VREFS_MRS_ENTER_BIT)))
		| (0x1 << PHY_VREFS_MRS_ENTER_BIT),
		base_phy + DDR_PHY_VREFTCTRL);
	result += ddr_hw_training_process(cfg, item & PHY_HW_GP_VREF_DQ);
	result += ddr_hw_training_process(cfg, item & PHY_HW_GP_VREF_DQ);
	/* DDR_PHY_VREFTCTRL 31bit:0 do vref dram set once */
	ddr_write(ddr_read(base_phy + DDR_PHY_VREFTCTRL)
		& (~(0x1 << PHY_VREFS_MRS_ENTER_BIT)),
		base_phy + DDR_PHY_VREFTCTRL);
	result += ddr_hw_training_process(cfg, item & PHY_HW_GP_VREF_DQ);
	ddr_write(dvrft_ctrl, base_phy + DDR_PHY_DVRFTCTRL);

	result += ddr_hw_training_process(cfg, item & PHY_HW_GP_NORMAL);

#ifdef DDR_WRITE_DM_DISABLE
	unsigned int temp1 = 0;
	if (PHY_DRAMCFG_TYPE_DDR4 == cfg->phy[cfg->phy_idx].dram_type) {
		ddr_write(temp, base_phy + 0xe0); /* restore */
		temp = ddr_read(base_phy + 0x1e0);
		temp1 = ddr_read(base_phy + 0x2c);
		ddr_write(0x05555555, base_phy + 0x1e0); /* inti MR5 */
		ddr_write(temp1 | 0x00004000 , base_phy + 0x2c); /* write dm disable */
		result += ddr_hw_training_process(cfg, item & PHY_PHYINITCTRL_DRAM_INIT_EN);
		ddr_write(temp, base_phy + 0x1e0); /* restore */
		ddr_write(temp1, base_phy + 0x2c); /* restore */
	}
#endif
	ddr_phy_cfg_update(base_phy);

	return result;
}

static int ddr_hw_training_by_rank(struct ddr_cfg_st *cfg)
{
	DDR_DEBUG("PHY[%x][%x] Rank[%x] itme[%x]",
		cfg->phy_idx, cfg->cur_phy, cfg->rank_idx, cfg->cur_item);

	/* 0:PHY_TRAINCTRL0_DTR_RANK0, 1:PHY_TRAINCTRL0_DTR_RANK1 */
	DDR_PHY_SWITCH_RANK(cfg->cur_phy, cfg->rank_idx);
	return ddr_hw_training_ctl(cfg);
}

static int ddr_hw_training_by_phy(struct ddr_cfg_st *cfg)
{
	int result = 0;
	int i;
	struct rdqs_data_st rdqs_data;
	struct rdqs_data_st *rdqs_st = &rdqs_data;
	struct ddr_timing_st timing_st;
	unsigned int rank_num = cfg->phy[cfg->phy_idx].rank_num;

	cfg->res_st = rdqs_st;

	/* disable auto refresh */
	ddr_training_save_timing(cfg, &timing_st);

	for (i = 0; i < rank_num; i++) {
		cfg->rank_idx = i;
		cfg->cur_item = cfg->phy[cfg->phy_idx].rank[i].item_hw;

		result += ddr_hw_training_by_rank(cfg);

		if (DDR_SUPPORT_RANK_MAX != rank_num)
			break;

		/* save rank rdqs bdl */
		ddr_training_get_rdqs(cfg, &(rdqs_st->rank[i]));

		/* restore PHY_PHYINITCTRL_DLYMEAS_EN rdqs before training next rank */
		if ((rank_num - 1) != i)
			ddr_training_set_rdqs(cfg, &(rdqs_st->origin));
	}

	if (DDR_SUPPORT_RANK_MAX == rank_num) {
		ddr_hw_training_adjust_rdqs(cfg, rdqs_st);
	}

	/* restore auto refresh */
	ddr_training_restore_timing(cfg, &timing_st);

	cfg->res_st = 0;

	return result;
}

/* DDR hardware training */
int ddr_hw_training(struct ddr_cfg_st *cfg)
{
	int result = 0;
	int i;
	struct tr_relate_reg reg;

	/* save customer reg */
	DDR_TRAINING_SAVE_REG_FUNC(&reg, 0x1);
	ddr_boot_cmd_save_func(&reg);

	for (i = 0; i < cfg->phy_num; i++) {
		cfg->phy_idx = i;
		cfg->cur_phy = cfg->phy[i].addr;
		result += ddr_hw_training_by_phy(cfg);
	}
	/* restore customer reg */
	DDR_TRAINING_RESTORE_REG_FUNC(&reg);
	ddr_boot_cmd_restore_func(&reg);

	return result;
}
#endif /* DDR_HW_TRAINING_CONFIG */

#define __mpr_training__
#ifdef DDR_MPR_TRAINING_CONFIG
/* Switch MPR function */
static void ddr_mpr_switch(unsigned int base_dmc, int val)
{
	unsigned int sfc_cmd;
	if (DDR_TRUE == val)
		sfc_cmd = (DMC_CMD_MRS_MR3 << DMC_SFC_CMD_MRS_BIT)
			| DMC_CMD_TYPE_LMR;
	else
		sfc_cmd = DMC_CMD_TYPE_LMR;

	ddr_dmc_sfc_cmd(base_dmc, sfc_cmd, 0x0, DMC_BANK_MR3);

	/* clear */
	if (DDR_FALSE == val) {
		ddr_write(0x0, base_dmc + DDR_DMC_SFCBANK);
		ddr_write(0x0, base_dmc + DDR_DMC_SFCREQ);
	}
}

/* Judge MPR data */
static int ddr_mpr_judge(unsigned int data1, unsigned int data2,
			 unsigned int data3, unsigned int data4,
			 unsigned int dq_index)
{
	/* check byte */
	if (-1 == dq_index) {
		if (DDR_MPR_BYTE_MASK == data1 && 0x0 == data2
			&& DDR_MPR_BYTE_MASK == data3 && 0x0 == data4)
			return 0;
		else
			return -1;
	} else {
		/* check DQ */
		data1 = (data1 >> dq_index) & DDR_MPR_BIT_MASK;
		data2 = (data2 >> dq_index) & DDR_MPR_BIT_MASK;
		data3 = (data3 >> dq_index) & DDR_MPR_BIT_MASK;
		data4 = (data4 >> dq_index) & DDR_MPR_BIT_MASK;
		if (DDR_MPR_BIT_MASK == data1 && 0x0 == data2
			&& DDR_MPR_BIT_MASK == data3 && 0x0 == data4)
			return 0;
		else
			return -1;
	}
}

/* Extract MPR read data to judge */
static int ddr_mpr_extract(struct ddr_cfg_st *cfg,
			   unsigned int offset0, unsigned int offset1,
			   unsigned int offset2, unsigned int offset3)
{
	unsigned int data1, data2, data3, data4;
	unsigned int base_dmc = cfg->cur_dmc;
	unsigned int byte_index = cfg->cur_byte;

	data1 = ddr_read(base_dmc + offset0);  /* [127:96] or [255:224] */
	data2 = ddr_read(base_dmc + offset1);  /* [95:64] or [223:192] */
	data3 = ddr_read(base_dmc + offset2);  /* [63:32] or [191:160] */
	data4 = ddr_read(base_dmc + offset3);  /* [31:0] or [159:128] */

	DDR_INFO("byte[%x] data[%x=%x][%x=%x][%x=%x][%x=%x]",
		byte_index,
		base_dmc + offset0, data1, base_dmc + offset1, data2,
		base_dmc + offset2, data3, base_dmc + offset3, data4);

	if (DDR_PHY_BYTE_MAX == GET_BYTE_NUM(cfg)) {
		/* four byte: data1[0xFFFFFFFF] data2[0x00000000]
		data3[0xFFFFFFFF] data4[0x00000000] */
		data1 = (data1 >> (byte_index << 3)) & DDR_MPR_BYTE_MASK;
		data2 = (data2 >> (byte_index << 3)) & DDR_MPR_BYTE_MASK;
		data3 = (data3 >> (byte_index << 3)) & DDR_MPR_BYTE_MASK;
		data4 = (data4 >> (byte_index << 3)) & DDR_MPR_BYTE_MASK;
	} else {
		/* two byte: data1[0xFFFF0000] data2[0xFFFF0000]
		data3[0xFFFF0000] data4[0xFFFF0000] */
		data1 = ((data1 >> DDR_MPR_BYTE_BIT) >> (byte_index << 3))
				& DDR_MPR_BYTE_MASK;
		data2 = (data2 >> (byte_index << 3)) & DDR_MPR_BYTE_MASK;
		data3 = ((data3 >> DDR_MPR_BYTE_BIT) >> (byte_index << 3))
				& DDR_MPR_BYTE_MASK;
		data4 = (data4 >> (byte_index << 3)) & DDR_MPR_BYTE_MASK;
		if (ddr_mpr_judge(data1, data2, data3, data4, cfg->cur_dq))
			return -1;

		/* two byte need to swap data and check again */
		data1 = ((ddr_read(base_dmc + DDR_DMC_SFC_RDATA1)
				>> DDR_MPR_BYTE_BIT) >> (byte_index << 3))
				& DDR_MPR_BYTE_MASK;
		data2 = (ddr_read(base_dmc + DDR_DMC_SFC_RDATA0)
				>> (byte_index << 3)) & DDR_MPR_BYTE_MASK;
		data3 = ((ddr_read(base_dmc + DDR_DMC_SFC_RDATA3)
			>> DDR_MPR_BYTE_BIT) >> (byte_index << 3))
			& DDR_MPR_BYTE_MASK;
		data4 = (ddr_read(base_dmc + DDR_DMC_SFC_RDATA2)
			>> (byte_index << 3)) & DDR_MPR_BYTE_MASK;
	}

	return ddr_mpr_judge(data1, data2, data3, data4, cfg->cur_dq);
}

/* Check MPR read data */
int ddr_mpr_check(struct ddr_cfg_st *cfg)
{
	/* read data */
	ddr_dmc_sfc_cmd(cfg->cur_dmc, DMC_CMD_TYPE_READ, 0x0, 0x0);
	return DMC_MPR_CHECK_BIT_0_127(cfg);
}

/* Find RDQ via MPR */
static int ddr_mpr_find_rdq(struct ddr_cfg_st *cfg)
{
	struct training_data tmp_result;
	struct training_data *training = &tmp_result;
	unsigned int dq_num;
	unsigned int win_num;
	unsigned int def_dq, best_dq;
	unsigned int byte_index, dq_index;

	/* find rdq via mpr */
	cfg->dq_check_type = DDR_CHECK_TYPE_MPR;

	/* find rdq */
	for (byte_index = 0;
		byte_index < GET_BYTE_NUM(cfg); byte_index++) {
		for (dq_index = 0; dq_index < DDR_PHY_BIT_NUM; dq_index++) {
			dq_num = (byte_index << 3) + dq_index;
			def_dq = ddr_phy_get_dq_bdl(cfg);
			ddr_dataeye_find_dq(cfg, training);
			win_num = training->ddr_bit_best[dq_num]
				>> DDR_DATAEYE_RESULT_BIT;
			best_dq = training->ddr_bit_best[dq_num]
				& DDR_DATAEYE_RESULT_MASK;
			if (win_num > 0)
				ddr_phy_set_dq_bdl(cfg, best_dq);
			else {
				/* In normal case, not reach here */
				/* restore default value */
				ddr_phy_set_dq_bdl(cfg, def_dq);

				DDR_FATAL("PHY[%x] Byte[%x] DQ[%x] MPR fail",
					cfg->cur_phy, byte_index, dq_index);
				ddr_training_stat(DDR_ERR_MPR, cfg->cur_phy,
					byte_index, dq_index);
				return -1;
			}
		}
	}

	return 0;

}

/* Find RDQS via MPR */
static int ddr_mpr_find_rdqs(struct ddr_cfg_st *cfg)
{
	unsigned int rdqs_start = 0;
	unsigned int rdqs_end   = PHY_RDQS_BDL_MASK;
	unsigned int rdqs_mid;
	unsigned int val, delay;
	unsigned int count = 0;
	int found = DDR_FALSE;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_index = cfg->cur_byte;

	/* set rdq to middle value */
	ddr_write(PHY_DQ_MIDDLE_VAL << PHY_BDL_DQ_BIT, base_phy + DDR_PHY_DXNRDQNBDL0(cfg->rank_idx, byte_index));
	ddr_write(PHY_DQ_MIDDLE_VAL << PHY_BDL_DQ_BIT, base_phy + DDR_PHY_DXNRDQNBDL1(cfg->rank_idx, byte_index));

	/* clear rdqs */
	delay    = ddr_read(base_phy + DDR_PHY_DXNRDQSDLY(byte_index)) >> PHY_RDQS_BDL_BIT;
	rdqs_mid = delay;   /* if not found, restore default value */
	delay    = delay & (~PHY_RDQS_BDL_MASK);

	/* find rdqs */
	for (val = 0; val <= PHY_RDQS_BDL_MASK; val++) {
		ddr_write(delay | (val << PHY_RDQS_BDL_BIT),
			base_phy + DDR_PHY_DXNRDQSDLY(byte_index));
		ddr_phy_cfg_update(base_phy);
		/* check ok */
		if (!ddr_mpr_check(cfg)) {
			if (DDR_FALSE == found) {
				rdqs_start = val; /* found start value */
				count++;
				if (DDR_MPR_RDQS_FIND_TIMES == count)
					found = DDR_TRUE;
			}
		} else {
			if (DDR_TRUE == found) {
				rdqs_end = val;  /* found end value */
				break;
			}
		}
	}

	if (DDR_TRUE == found) {
		rdqs_mid = ((rdqs_end - rdqs_start) >> 1) + rdqs_start;
		DDR_INFO("PHY[%x] Byte[%x] rdqs_middle[%x]",
				base_phy, byte_index, rdqs_mid);
		DDR_INFO("rdqs_start[%x] rdqs_end[%x]",
				rdqs_start, rdqs_end);
	} else {
		DDR_FATAL("PHY[%x] Byte[%x] not find RDQS, restore.",
			base_phy, byte_index);
		ddr_training_stat(DDR_ERR_MPR, base_phy,
					byte_index, -1);
	}

	ddr_write(delay | (rdqs_mid << PHY_RDQS_BDL_BIT), base_phy + DDR_PHY_DXNRDQSDLY(byte_index));
	ddr_phy_cfg_update(base_phy);

	return ((DDR_TRUE == found) ? 0 : -1);
}

/* Multi Purpose Register(MPR) */
int ddr_mpr_training(struct ddr_cfg_st *cfg)
{
	int i;
	int result = 0;
	unsigned int byte_num = GET_BYTE_NUM(cfg);
	unsigned int mr0;
	unsigned int sfc_cmd;
	unsigned int base_dmc = cfg->cur_dmc;
	unsigned int base_phy = cfg->cur_phy;

	DDR_DEBUG("DDR MPR training.");

	/* set DDR bust */
	if (DDR_PHY_BYTE_MAX == byte_num) {
		mr0 = (ddr_read(base_phy + DDR_PHY_MODEREG01)
			& DMC_MRS_MASK)
			& (~DMC_MR0_BL_MASK);
		sfc_cmd = ((mr0 | DMC_MR0_BL_BUST4)
			<< DMC_SFC_CMD_MRS_BIT)
			| DMC_CMD_TYPE_LMR;
		ddr_dmc_sfc_cmd(base_dmc, sfc_cmd, 0x0, 0x0);
	}

	/* precharge all */
	ddr_dmc_sfc_cmd(base_dmc, DMC_CMD_TYPE_PRECHARGE_ALL, 0x0, 0x0);

	/* enable MPR */
	ddr_mpr_switch(base_dmc, DDR_TRUE);

	/* find rdqs */
	for (i = 0; i < byte_num; i++)
		result += ddr_mpr_find_rdqs(cfg);

	/* find rdq */
	if (!result)
		result = ddr_mpr_find_rdq(cfg);

	/* disable MPR */
	ddr_mpr_switch(base_dmc, DDR_FALSE);

	/* restore DDR bust */
	if (DDR_PHY_BYTE_MAX == byte_num) {
		mr0 = (ddr_read(base_phy + DDR_PHY_MODEREG01)
			& DMC_MRS_MASK);
		sfc_cmd = (mr0 << DMC_SFC_CMD_MRS_BIT)
			| DMC_CMD_TYPE_LMR;
		ddr_dmc_sfc_cmd(base_dmc, sfc_cmd, 0x0, 0x0);
	}
	return result;
}

int ddr_mpr_training_func(struct ddr_cfg_st *cfg)
{
	struct tr_relate_reg relate_reg;
	int result = 0;

	/* MPR training disable */
	if (ddr_training_check_bypass(cfg, DDR_BYPASS_MPR_MASK))
		return 0;

	ddr_training_save_reg(cfg, &relate_reg, DDR_BYPASS_MPR_MASK);
	result = ddr_mpr_training(cfg);
	ddr_training_restore_reg(cfg, &relate_reg);

	return result;
}
#endif /* DDR_MPR_TRAINING_CONFIG */

#define __vref_training__
#ifdef DDR_VREF_TRAINING_CONFIG
#ifdef DDR_VREF_WITHOUT_BDL_CONFIG
/* Save dataeye dq bdl before vref training */
static void ddr_vref_save_bdl(struct ddr_cfg_st *cfg, struct tr_dq_data *dq_data)
{
	int i;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int rank = cfg->rank_idx;
	unsigned int byte_index;

	for (i = 0; i < GET_BYTE_NUM(cfg); i++) {
		byte_index = i + (cfg->dmc_idx << 1); /* byte index accord to phy */
		if (DDR_MODE_WRITE == cfg->cur_mode) {
			dq_data->dq03[i] = ddr_read(base_phy + DDR_PHY_DXNWDQNBDL0(rank, byte_index));
			dq_data->dq47[i] = ddr_read(base_phy + DDR_PHY_DXNWDQNBDL1(rank, byte_index));
			dq_data->wdm[i] = ddr_read(base_phy + DDR_PHY_DXNWDQNBDL2(rank, byte_index));
		} else {
			dq_data->dq03[i] = ddr_read(base_phy + DDR_PHY_DXNRDQNBDL0(rank, byte_index));
			dq_data->dq47[i] = ddr_read(base_phy + DDR_PHY_DXNRDQNBDL1(rank, byte_index));
		}
	}
}

/* Restore dataeye dq bdl after vref training */
static void ddr_vref_restore_bdl(struct ddr_cfg_st *cfg, struct tr_dq_data *dq_data)
{
	int i;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int rank = cfg->rank_idx;
	unsigned int byte_index;

	for (i = 0; i < GET_BYTE_NUM(cfg); i++) {
		byte_index = i + (cfg->dmc_idx << 1); /* byte index accord to phy */
		if (DDR_MODE_WRITE == cfg->cur_mode) {
			ddr_write(dq_data->dq03[i], base_phy + DDR_PHY_DXNWDQNBDL0(rank, byte_index));
			ddr_write(dq_data->dq47[i], base_phy + DDR_PHY_DXNWDQNBDL1(rank, byte_index));
			ddr_write(dq_data->wdm[i], base_phy + DDR_PHY_DXNWDQNBDL2(rank, byte_index));
		} else {
			ddr_write(dq_data->dq03[i], base_phy + DDR_PHY_DXNRDQNBDL0(rank, byte_index));
			ddr_write(dq_data->dq47[i], base_phy + DDR_PHY_DXNRDQNBDL1(rank, byte_index));
		}
	}
}
#else
static void ddr_vref_save_bdl(struct ddr_cfg_st *cfg, struct tr_dq_data *dq_data)
{
}
static void ddr_vref_restore_bdl(struct ddr_cfg_st *cfg, struct tr_dq_data *dq_data)
{
}
#endif /* DDR_VREF_WITHOUT_BDL_CONFIG */

/* Set DDR Vref value */
static void ddr_vref_set(struct ddr_cfg_st *cfg, unsigned int val)
{
	if (DDR_MODE_READ == cfg->cur_mode) { /* HOST vref */
		DDR_PHY_VREF_HOST_SET(cfg->cur_phy, cfg->rank_idx, GET_BYTE_NUM(cfg), cfg->cur_byte, val); /* TODO */
	} else {	  /* DRAM vref */
		unsigned int auto_ref_timing =
			ddr_read(cfg->cur_dmc + DDR_DMC_TIMING2);
		/* disable auto refresh */
		ddr_training_set_timing(cfg->cur_dmc,
			auto_ref_timing & DMC_AUTO_TIMING_DIS);

		/* DDR_PHY_VREFTCTRL 31bit:1 do vref dram set twice */
		ddr_write((ddr_read(cfg->cur_phy + DDR_PHY_VREFTCTRL)
			& (~(0x1 << PHY_VREFS_MRS_ENTER_BIT)))
			| (0x1 << PHY_VREFS_MRS_ENTER_BIT),
			cfg->cur_phy + DDR_PHY_VREFTCTRL);
		DDR_PHY_VREF_DRAM_SET(cfg->cur_phy, val, cfg->cur_byte);
		DDR_PHY_VREF_DRAM_SET(cfg->cur_phy, val, cfg->cur_byte);
		/* DDR_PHY_VREFTCTRL 31bit:0 do vref dram set once */
		ddr_write(ddr_read(cfg->cur_phy + DDR_PHY_VREFTCTRL)
			& (~(0x1 << PHY_VREFS_MRS_ENTER_BIT)),
			cfg->cur_phy + DDR_PHY_VREFTCTRL);
		DDR_PHY_VREF_DRAM_SET(cfg->cur_phy, val, cfg->cur_byte);

		/* enable auto refresh */
		ddr_training_set_timing(cfg->cur_dmc, auto_ref_timing);
	}
	DDR_INFO("byte[%x] mode[%x] set vref [%x]", cfg->cur_byte, cfg->cur_mode, val);
}

/* Get DDR Vref value */
static unsigned int ddr_vref_get(struct ddr_cfg_st *cfg)
{
	unsigned int val = 0;

	if (DDR_MODE_READ == cfg->cur_mode) {	/* HOST vref */
		DDR_PHY_VREF_HOST_GET(cfg->cur_phy, cfg->rank_idx, cfg->cur_byte, val);
	} else {      /* DRAM vref */
		DDR_PHY_VREF_DRAM_GET(cfg->cur_phy, val, cfg->cur_byte);
	}
	DDR_INFO("byte[%x] mode[%x] get vref [%x]", cfg->cur_byte, cfg->cur_mode, val);
	return val;
}

/* Get totol win number of training result */
static unsigned int ddr_vref_get_win(struct ddr_cfg_st *cfg,
	struct training_data *training, int vref)
{
	unsigned int vref_min = 0;
	unsigned int vref_max = DDR_VREF_DRAM_VAL_MAX;
	int vref_set;

	training->ddr_win_sum = 0;

    if (DDR_MODE_READ == cfg->cur_mode) {
		DDR_VREF_GET_HOST_MAX(cfg->rank_idx, vref_max);
    }

	if (vref < vref_min)
		vref_set = vref_min;
	else if (vref > vref_max)
		vref_set = vref_max;
	else
		vref_set = vref;

	ddr_vref_set(cfg, vref_set);

	ddr_dataeye_deskew(cfg, training);

	return training->ddr_win_sum;
}

/* Find the best vref which win number is max */
static unsigned int ddr_vref_find_best(struct ddr_cfg_st *cfg,
	struct training_data *training, unsigned int vref, int step)
{
	int cur_vref;
	unsigned int best_vref;
	unsigned int cur_win;
	unsigned int max_win;
	unsigned int lower_times = 0;
	unsigned int vref_min = 0;
	unsigned int vref_max = DDR_VREF_DRAM_VAL_MAX;

    if (DDR_MODE_READ == cfg->cur_mode) {
		DDR_VREF_GET_HOST_MAX(cfg->rank_idx, vref_max);
    }

	max_win   = 0;
	cur_vref  = vref + step;

	if (vref < vref_min)
		best_vref = vref_min;
	else if (vref > vref_max)
		best_vref = vref_max;
	else
		best_vref = vref;

	/* find parabola vertex */
	while (cur_vref >= vref_min
		&& cur_vref <= vref_max) {
		cur_win = ddr_vref_get_win(cfg, training, cur_vref);
		DDR_DEBUG("byte[%x] vref[%x] win[%x] mode[%x]",
			cfg->cur_byte, cur_vref, cur_win, cfg->cur_mode);
		if (cur_win < max_win) {
			lower_times++;
			if (DDR_VREF_COMPARE_TIMES == lower_times) {
				/* Continuous decline, mean found vertex */
				break;
			}
		} else {
			lower_times = 0;
			max_win =  cur_win;
			best_vref = cur_vref;
		}
		cur_vref = cur_vref + step;
	}

	return best_vref;
}

/* DDR Vref calibrate and set the best value */
static void ddr_vref_cal(struct ddr_cfg_st *cfg, struct training_data *training)
{
	unsigned int def_vref;
	unsigned int best_vref;
	unsigned int left_win;
	unsigned int right_win;

	def_vref  = ddr_vref_get(cfg);
	left_win  = ddr_vref_get_win(cfg, training, def_vref - DDR_VREF_COMPARE_STEP);
	right_win = ddr_vref_get_win(cfg, training, def_vref + DDR_VREF_COMPARE_STEP);

	DDR_DEBUG("byte[%x] default vref[%x] win[%x][%x] mode[%x]",
		cfg->cur_byte, def_vref, left_win, right_win, cfg->cur_mode);

	/* With vref increments, WIN number is a parabola.
	   So firstly determine the result on left or right. */
	/* parabola vertex */
	if (left_win < right_win) { /* the result on right */
		best_vref = ddr_vref_find_best(cfg, training, def_vref, 1);
	} else if (left_win > right_win) { /* the result on left */
		best_vref = ddr_vref_find_best(cfg, training, def_vref, -1);
	} else {
		/* when (left_win == right_win), check def_vref */
        unsigned int vref_max = DDR_VREF_DRAM_VAL_MAX;
        if (DDR_MODE_READ == cfg->cur_mode) {
            DDR_VREF_GET_HOST_MAX(cfg->rank_idx, vref_max);
        }

		if (def_vref < (vref_max >> 1))
			best_vref = ddr_vref_find_best(cfg, training, def_vref, 1);
		else
			best_vref = ddr_vref_find_best(cfg, training, def_vref, -1);
	}


	DDR_DEBUG("byte[%x] best vref[%x] mode[%x]",
		cfg->cur_byte, best_vref, cfg->cur_mode);
	ddr_vref_set(cfg, best_vref);
}

int ddr_vref_training(struct ddr_cfg_st *cfg)
{
	struct training_data tmp_result;
	struct training_data *training = &tmp_result;
	struct tr_dq_data dq_data;
	int result = 0;
	int i;

	DDR_DEBUG("DDR Vref[%x] training PHY[%x][%x] DMC[%x][%x] Rank[%x]",
		cfg->cur_mode, cfg->phy_idx, cfg->cur_phy, cfg->dmc_idx,
		cfg->cur_dmc, cfg->rank_idx);

	ddr_vref_save_bdl(cfg, &dq_data);
	ddrtr_memset(training, 0, sizeof(struct training_data));

	/* vref calibrate */
	if (DDR_MODE_READ == cfg->cur_mode) {
		/* only training byte0 and byte2 */
		for (i = 0; i < GET_BYTE_NUM(cfg); i++) {
			cfg->cur_byte = i + (cfg->dmc_idx << 1); /* byte index accord to phy */
			if (1 == cfg->cur_byte || 3 == cfg->cur_byte)
				continue;

			ddr_vref_cal(cfg, training);
		}
	} else {
		unsigned int dram_type = cfg->phy[cfg->phy_idx].dram_type;
		unsigned int bank_group = (ddr_read(cfg->cur_dmc
					+ DDR_DMC_CFG_RNKVOL(cfg->rank_idx)) >> DMC_CFG_MEM_BG_BIT)
					& DMC_CFG_MEM_BG_MASK;

		if (PHY_DRAMCFG_TYPE_LPDDR4 != dram_type
		&& PHY_DRAMCFG_TYPE_DDR4 != dram_type)
			return 0;

		if (PHY_DRAMCFG_TYPE_LPDDR4 == dram_type)
			bank_group = DMC_CFG_MEM_2BG; /* lpddr4 not training byte1 byte3 */

		for (i = 0; i < GET_BYTE_NUM(cfg); i++) {
			cfg->cur_byte = i + (cfg->dmc_idx << 1); /* byte index accord to phy */
			/* byte1 and byte3 bypass when 2 Bank Group */
			if ((DMC_CFG_MEM_2BG == bank_group)
				&& ((1 == i) || (3 == i)))
				continue;

			ddr_vref_cal(cfg, training);
		}
	}

#if !defined(DDR_VREF_WITHOUT_BDL_CONFIG) || defined(DDR_TRAINING_CMD)
	/* dataeye deskew again on best vref. */
	for (i = 0; i < GET_BYTE_NUM(cfg); i++) {
		cfg->cur_byte = i + (cfg->dmc_idx << 1); /* byte index accord to phy */
		result += ddr_dataeye_deskew(cfg, training);
	}
#endif

	ddr_vref_restore_bdl(cfg, &dq_data);

	ddr_result_data_save(cfg, training);

	return result;
}

int ddr_vref_training_func(struct ddr_cfg_st *cfg)
{
	struct tr_relate_reg relate_reg;
	int result = 0;

	ddr_training_save_reg(cfg, &relate_reg, DDR_BYPASS_VREF_HOST_MASK);
	ddr_training_switch_axi(cfg);
	ddr_ddrt_init(cfg, DDR_DDRT_MODE_DATAEYE);
	cfg->dq_check_type = DDR_CHECK_TYPE_DDRT;

	/* host vref training disable */
	if (!ddr_training_check_bypass(cfg, DDR_BYPASS_VREF_HOST_MASK)) {
		cfg->cur_mode = DDR_MODE_READ;
		result += ddr_vref_training(cfg);
	}

	/* dram vref training enable && DDR4 */
	if (!ddr_training_check_bypass(cfg, DDR_BYPASS_VREF_DRAM_MASK)) {
		cfg->cur_mode = DDR_MODE_WRITE;
		result += ddr_vref_training(cfg);
	}
	ddr_training_restore_reg(cfg, &relate_reg);

	return result;
}
#else
int ddr_vref_training_func(struct ddr_cfg_st *cfg)
{
	DDR_WARNING("Not support DDR vref training.");
	return 0;
}
#endif /* DDR_VREF_TRAINING_CONFIG */

#define __write_leveling__
#ifdef DDR_WL_TRAINING_CONFIG
static void ddr_bdl_add(unsigned int *raw, unsigned int val)
{
	if (((*raw) + val) > PHY_BDL_MASK)
		*raw = PHY_BDL_MASK;
	else
		*raw += val;
}

static void ddr_bdl_sub(unsigned int *raw, unsigned int val)
{
	if ((*raw) > val)
		*raw -= val;
	else
		*raw = 0;
}

/* DDR PHY DQ phase increase */
static void ddr_phase_inc(unsigned int *raw)
{
#if defined (DDR_PHY_T28_CONFIG) || defined(DDR_PHY_T16_CONFIG) \
		|| defined (DDR_PHY_T12_V100_CONFIG) || defined (DDR_PHY_T12_V101_CONFIG)
	if ((*raw) < (PHY_WDQS_PHASE_MASK - 1)) {
		if (((*raw) & 0x3) == 0x2)
			*raw += 0x2;
		else
			*raw += 0x1;
	}
#else
	if ((*raw) < PHY_WDQS_PHASE_MASK)
		*raw += 0x1;
#endif
}

/* DDR PHY DQ phase decrease */
static void ddr_phase_dec(unsigned int *raw)
{
#if defined (DDR_PHY_T28_CONFIG) || defined(DDR_PHY_T16_CONFIG) \
		|| defined (DDR_PHY_T12_V100_CONFIG) || defined (DDR_PHY_T12_V101_CONFIG)
	if ((*raw) > 0x1) {
		if (((*raw) & 0x3) == 0x3)
			*raw -= 0x2;
		else
			*raw -= 0x1;
	}
#else
	if ((*raw) > 0x0)
		*raw -= 0x1;
#endif
}

/* DQ bdl add or sub */
static void ddr_dq_bdl_operate(unsigned int base_phy,
	unsigned int addr_offset, unsigned int val, unsigned int is_add)
{
	unsigned int tmp;
	unsigned int dq_bdl[DDR_PHY_REG_DQ_NUM];
	int i;

	tmp = ddr_read(base_phy + addr_offset);
	dq_bdl[0] = (tmp >> PHY_BDL_DQ0_BIT)  & PHY_BDL_MASK;
	dq_bdl[1] = (tmp >> PHY_BDL_DQ1_BIT)  & PHY_BDL_MASK;
	dq_bdl[2] = (tmp >> PHY_BDL_DQ2_BIT) & PHY_BDL_MASK;
	dq_bdl[3] = (tmp >> PHY_BDL_DQ3_BIT) & PHY_BDL_MASK;

	for (i = 0; i < DDR_PHY_REG_DQ_NUM; i++) {
		if (is_add)
			ddr_bdl_add(&dq_bdl[i], val);
		else
			ddr_bdl_sub(&dq_bdl[i], val);
	}

	tmp = (dq_bdl[3] << PHY_BDL_DQ3_BIT) + (dq_bdl[2] << PHY_BDL_DQ2_BIT)
		+ (dq_bdl[1] << PHY_BDL_DQ1_BIT)  + (dq_bdl[0] << PHY_BDL_DQ0_BIT);
	ddr_write(tmp, base_phy + addr_offset);
}

/* Disable or enable DDR write leveling mode */
static void ddr_wl_switch(unsigned int base_dmc, unsigned int base_phy,
			int val)
{
	unsigned int mr1_raw;
	unsigned int sfc_cmd;
	unsigned int sfc_bank;

	/* Set Rank = 0, Cmd = MRS, No Precharch CMD */
	mr1_raw = ddr_read(base_phy + DDR_PHY_MODEREG01)
		>> PHY_MODEREG01_MR1_BIT;
	sfc_cmd  = DMC_CMD_TYPE_LMR;
	sfc_bank = DMC_BANK_MR1;

	if (DDR_TRUE == val) { /* enable DDR wl */
		/* Set A7 = 1 */
		sfc_cmd  += (mr1_raw | DMC_CMD_MRS_A7) << DMC_SFC_CMD_MRS_BIT;
	} else {

		/* Set A7 = 0 */
		sfc_cmd  += (mr1_raw & ((~DMC_CMD_MRS_A7) & DMC_CMD_MRS_MASK))
					<< DMC_SFC_CMD_MRS_BIT;
	}

	ddr_dmc_sfc_cmd(base_dmc, sfc_cmd, 0x0, sfc_bank);

	/* clear */
	if (DDR_FALSE == val) {
		ddr_write(0x0, base_dmc + DDR_DMC_SFCBANK);
		ddr_write(0x0, base_dmc + DDR_DMC_SFCREQ);
	}

	/* phy sw write leveling mode */
	ddr_write(val, base_phy + DDR_PHY_SWTMODE);
}

#ifdef DDR_WL_DATAEYE_ADJUST_CONFIG
/* Adjust dataeye WDQ after Write leveling */
static void ddr_wl_wdq_adjust(struct ddr_cfg_st *cfg,
	struct ddr_delay_st *wdqs_new, struct ddr_delay_st *wdqs_old)
{
	unsigned int val;
	int i;
	unsigned int phase_adj, bdl_adj = 0;  /* for write dataeye */
	unsigned int wdm_bdl;
	unsigned int wdq_phase;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_num = GET_BYTE_NUM(cfg);
	unsigned int rank_index = cfg->rank_idx;

	DDR_DEBUG("DDR WL write adjust.");

	/* check wl write adjust bypass bit */
	if (ddr_training_check_bypass(cfg, DDR_BYPASS_WL_ADJ_MASK))
		return;

	/* adjust wdq phase, wdq bdl, wdm bdl */
	for (i = 0; i < byte_num; i++) {
		if (wdqs_new->phase[i] == wdqs_old->phase[i]
		 && wdqs_new->bdl[i]   == wdqs_old->bdl[i]) {
			continue;
		}

		phase_adj = 0;
		wdq_phase = (ddr_read(base_phy + DDR_PHY_DXNWDQDLY(rank_index, i))
					>> PHY_WDQ_PHASE_BIT)
					& PHY_WDQ_PHASE_MASK;
		wdm_bdl  = (ddr_read(base_phy + DDR_PHY_DXNWDQNBDL2(rank_index, i))
					>> PHY_WDM_BDL_BIT)
					& PHY_BDL_MASK;

		if (wdqs_new->bdl[i] > wdqs_old->bdl[i]) {
			val = wdqs_new->bdl[i] - wdqs_old->bdl[i];
			phase_adj = val >> DDR_BDL_PHASE_REL;
			wdq_phase  = wdq_phase + phase_adj;

			if (wdq_phase > PHY_WDQ_PHASE_MASK)
				wdq_phase = PHY_WDQ_PHASE_MASK;

			/* adjust wdq bdl and dm bdl in opposite direction */
			bdl_adj  = phase_adj << DDR_BDL_PHASE_REL;
			ddr_dq_bdl_operate(base_phy, DDR_PHY_DXNWDQNBDL0(rank_index, i),
				bdl_adj, DDR_FALSE);
			ddr_dq_bdl_operate(base_phy, DDR_PHY_DXNWDQNBDL1(rank_index, i),
				bdl_adj, DDR_FALSE);
			ddr_bdl_sub(&wdm_bdl, bdl_adj);

		} else if (wdqs_new->bdl[i] < wdqs_old->bdl[i]) {
			val = wdqs_old->bdl[i] - wdqs_new->bdl[i];
			phase_adj = val >> DDR_BDL_PHASE_REL;
			wdq_phase = (wdq_phase > phase_adj)
				? (wdq_phase - phase_adj) : 0;

			/* adjust wdq bdl and dm bdl in opposite direction */
			bdl_adj  = phase_adj << DDR_BDL_PHASE_REL;
			ddr_dq_bdl_operate(base_phy, DDR_PHY_DXNWDQNBDL0(rank_index, i),
				bdl_adj, DDR_TRUE);
			ddr_dq_bdl_operate(base_phy, DDR_PHY_DXNWDQNBDL1(rank_index, i),
				bdl_adj, DDR_TRUE);
			ddr_bdl_add(&wdm_bdl, bdl_adj);
		}

		DDR_INFO("Byte[%x] WDQ adjust phase[%x] bdl[%x]",
			i, phase_adj, bdl_adj);

		ddr_write(wdq_phase << PHY_WDQ_PHASE_BIT,
					base_phy + DDR_PHY_DXNWDQDLY(rank_index, i));
		ddr_write(wdm_bdl << PHY_WDM_BDL_BIT, base_phy + DDR_PHY_DXNWDQNBDL2(rank_index, i));
	}

	ddr_phy_cfg_update(base_phy);
}
#endif /* DDR_WL_DATAEYE_ADJUST_CONFIG */

/* Sync WDQ phase, WDQ bdl, WDM bdl, OEN bdl, WDQ SOE bdl by WDQS value */
static void ddr_wl_bdl_sync(struct ddr_cfg_st *cfg,
	struct ddr_delay_st *wdqs_new, struct ddr_delay_st *wdqs_old)
{
	unsigned int tmp;
	unsigned int val;
	int i;

	unsigned int oen_bdl, wdqsoe_bdl, wdm_bdl;
	unsigned int wdq_phase;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_num = GET_BYTE_NUM(cfg);
	unsigned int rank_index = cfg->rank_idx;

	/* sync wdq phase, wdq bdl, wdm bdl, oen bdl, wdq soe bdl */
	for (i = 0; i < byte_num; i++) {
		if (wdqs_new->phase[i] == wdqs_old->phase[i]
		 && wdqs_new->bdl[i]   == wdqs_old->bdl[i]) {
			continue;
		}

		DDR_DEBUG("Byte[%x] new[%x][%x] old[%x][%x]", i,
			wdqs_new->phase[i],	wdqs_new->bdl[i],
			wdqs_old->phase[i], wdqs_old->bdl[i]);

		/* wdq phase */
		wdq_phase = (ddr_read(base_phy + DDR_PHY_DXNWDQDLY(rank_index, i))
					>> PHY_WDQ_PHASE_BIT)
					& PHY_WDQ_PHASE_MASK;
		/* always new_phase >= old_phase */
		wdq_phase = wdq_phase
			+ (wdqs_new->phase[i] - wdqs_old->phase[i]);

		/* bdl */
		tmp = ddr_read(base_phy + DDR_PHY_DXNOEBDL(rank_index, i));
		oen_bdl	 = (tmp >> PHY_OEN_BDL_BIT) & PHY_BDL_MASK;
		wdqsoe_bdl = (tmp >> PHY_WDQSOE_BDL_BIT) & PHY_BDL_MASK;
		wdm_bdl	 = (ddr_read(base_phy + DDR_PHY_DXNWDQNBDL2(rank_index, i))
			>> PHY_WDM_BDL_BIT) & PHY_BDL_MASK;

		if (wdqs_new->bdl[i] > wdqs_old->bdl[i]) {
			val = wdqs_new->bdl[i] - wdqs_old->bdl[i];
			ddr_dq_bdl_operate(base_phy,
				DDR_PHY_DXNWDQNBDL0(rank_index, i), val, DDR_TRUE);
			ddr_dq_bdl_operate(base_phy,
				DDR_PHY_DXNWDQNBDL1(rank_index, i), val, DDR_TRUE);
			ddr_bdl_add(&oen_bdl, val);
			ddr_bdl_add(&wdqsoe_bdl, val);
			ddr_bdl_add(&wdm_bdl, val);
		} else if (wdqs_new->bdl[i] < wdqs_old->bdl[i]) {
			val = wdqs_old->bdl[i] - wdqs_new->bdl[i];
			ddr_dq_bdl_operate(base_phy, DDR_PHY_DXNWDQNBDL0(rank_index, i),
						val, DDR_FALSE);
			ddr_dq_bdl_operate(base_phy, DDR_PHY_DXNWDQNBDL1(rank_index, i),
						val, DDR_FALSE);
			ddr_bdl_sub(&oen_bdl, val);
			ddr_bdl_sub(&wdqsoe_bdl, val);
			ddr_bdl_sub(&wdm_bdl, val);
		}

		if (wdq_phase > PHY_WDQ_PHASE_MASK)
			wdq_phase = PHY_WDQ_PHASE_MASK;

		ddr_write(wdq_phase << PHY_WDQ_PHASE_BIT,
			base_phy + DDR_PHY_DXNWDQDLY(rank_index, i));
		ddr_write((wdqsoe_bdl << PHY_WDQSOE_BDL_BIT) + (oen_bdl << PHY_OEN_BDL_BIT),
			base_phy + DDR_PHY_DXNOEBDL(rank_index, i));
		ddr_write((wdm_bdl << PHY_WDM_BDL_BIT), base_phy + DDR_PHY_DXNWDQNBDL2(rank_index, i));
	}

	ddr_phy_cfg_update(base_phy);
}

/**
 * Write leveling process.
 * WL depend default WDQS phase value in register init table.
 */
static int ddr_wl_process(struct ddr_cfg_st *cfg,
		unsigned int type, struct ddr_delay_st *wdqs)
{
	int i, j;
	unsigned int wl_result = 0;
	unsigned int length;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_num = GET_BYTE_NUM(cfg);

	if (DDR_DELAY_PHASE == type)
		length = PHY_WDQS_PHASE_MASK;
	else
		length = PHY_BDL_MASK;

	/* find WDQS phase or bdl, assume CLK Delay > DQS Delay */
	for (i = 0; i <= length; i++) {
		ddr_phy_cfg_update(base_phy);
		ddr_write(0x1, base_phy + DDR_PHY_SWTWLDQS);
		DDR_ASM_DSB();
		wl_result = ddr_read(base_phy + DDR_PHY_SWTRLT)
				& PHY_SWTRLT_WL_MASK;
		ddr_write(0x0, base_phy + DDR_PHY_SWTWLDQS);

		if ((wl_result & ((1 << byte_num) - 1)) == ((1 << byte_num) - 1))
			break;

		for (j = 0; j < byte_num; j++) {
			DDR_INFO("type[0x%x] byte[0x%x] phase[0x%x] bdl[0x%x] wl_result[0x%x]",
				type, j, wdqs->phase[j], wdqs->bdl[j], wl_result);
			if (!(wl_result & (1 << j))) {
				if (DDR_DELAY_PHASE == type)
					ddr_phase_inc(&wdqs->phase[j]);
				else
					wdqs->bdl[j] += DDR_WL_BDL_STEP;

			ddr_write((wdqs->phase[j] << PHY_WDQS_PHASE_BIT)
					+ (wdqs->bdl[j] << PHY_WDQS_BDL_BIT),
					base_phy + DDR_PHY_DXWDQSDLY(cfg->rank_idx, j));
			}
		}
	}

	if (i > length) {   /* wl error, not find wdqs delay */
		if (DDR_DELAY_BDL == type) {
			DDR_FATAL("PHY[%x] WL fail, result[%x]",
					base_phy, wl_result);
			for (j = 0; j < byte_num; j++)
				if (!(wl_result & (1 << j)))
					ddr_training_stat(DDR_ERR_WL,
						base_phy, j, -1);

		} else
			DDR_DEBUG("PHY[%x] WL not found phase, result[%x]",
					base_phy, wl_result);

		return -1;
	} else
		return 0;
}

/**
 * Find WDQS delay, sync to WDQ delay and OE delay.
 * WL depend default WDQS phase value in register init table.
 */
int ddr_write_leveling(struct ddr_cfg_st *cfg)
{
	unsigned int i, tmp;
	struct ddr_delay_st wdqs_old;
	struct ddr_delay_st wdqs_new;
	int result = 0;

	unsigned int base_phy = cfg->cur_phy;
	unsigned int base_dmc = cfg->cur_dmc;
	unsigned int byte_num = GET_BYTE_NUM(cfg);
	unsigned int rank_index = cfg->rank_idx;

	DDR_DEBUG("DDR Write Leveling training.");

	/* init wdqs */
	for (i = 0; i < byte_num; i++) {
		tmp = ddr_read(base_phy + DDR_PHY_DXWDQSDLY(rank_index, i));

		wdqs_old.phase[i] = (tmp >> PHY_WDQS_PHASE_BIT)
					& PHY_WDQS_PHASE_MASK;
		wdqs_old.bdl[i] = (tmp >> PHY_WDQS_BDL_BIT) & PHY_BDL_MASK;

		wdqs_new.phase[i] = wdqs_old.phase[i];
		wdqs_new.bdl[i] = 0;

		/* clear wdqs bdl */
		ddr_write(wdqs_new.phase[i] << PHY_WDQS_PHASE_BIT,
				base_phy + DDR_PHY_DXWDQSDLY(rank_index, i));
	}

	/* enable sw write leveling mode */
	ddr_wl_switch(base_dmc, base_phy, DDR_TRUE);

	/* find first WDQS phase, assume CLK delay > DQS delay. */
	result = ddr_wl_process(cfg, DDR_DELAY_PHASE, &wdqs_new);

	/* check phase result */
	for (i = 0; i < byte_num; i++) {
		/* find phase error, keep max value to find bdl. */
		/* find phase ok, decrease to find bdl. */
		if (!result)
			ddr_phase_dec(&wdqs_new.phase[i]);

		ddr_write(wdqs_new.phase[i] << PHY_WDQS_PHASE_BIT,
			base_phy + DDR_PHY_DXWDQSDLY(rank_index, i));
	}

	/* find WDQS bdl */
	result = ddr_wl_process(cfg, DDR_DELAY_BDL, &wdqs_new);

	/* disable sw write leveling mode */
	ddr_wl_switch(base_dmc, base_phy, DDR_FALSE);

	if (result) {
		/* restore default value when find WDQS fail */
		for (i = 0; i < byte_num; i++) {
			tmp = (wdqs_old.phase[i] << PHY_WDQS_PHASE_BIT)
				+ (wdqs_old.bdl[i] << PHY_WDQS_BDL_BIT);
			ddr_write(tmp, base_phy + DDR_PHY_DXWDQSDLY(rank_index, i));
		}
		ddr_phy_cfg_update(base_phy);
		return -1;
	}

	/* sync delay */
	ddr_wl_bdl_sync(cfg, &wdqs_new, &wdqs_old);

#ifdef DDR_WL_DATAEYE_ADJUST_CONFIG
	/* adjust WDQ for dataeye */
	ddr_wl_wdq_adjust(cfg, &wdqs_new, &wdqs_old);
#endif
	return 0;
}

int ddr_wl_func(struct ddr_cfg_st *cfg)
{
	struct tr_relate_reg relate_reg;
	int result = 0;

	/* write leveling disable */
	if (ddr_training_check_bypass(cfg, DDR_BYPASS_WL_MASK))
		return 0;

	ddr_training_save_reg(cfg, &relate_reg, DDR_BYPASS_WL_MASK);

	result += ddr_write_leveling(cfg);

	ddr_training_restore_reg(cfg, &relate_reg);

	return result;
}
#else
int ddr_wl_func(struct ddr_cfg_st *cfg)
{
	DDR_WARNING("Not support DDR WL training.");
	return 0;
}
 #endif /* DDR_WL_TRAINING_CONFIG */

#define __gate_training__
#ifdef DDR_GATE_TRAINING_CONFIG
/* Find gate phase */
static int ddr_gate_find_phase(struct ddr_cfg_st *cfg,
						struct ddr_delay_st *rdqsg)
{
	int i;
	unsigned int base_phy = cfg->cur_phy;

	for (i = 0; i < GET_BYTE_NUM(cfg); i++) {
		for (rdqsg->phase[i] = PHY_RDQSG_PHASE_MAX;
			rdqsg->phase[i] > PHY_GATE_PHASE_MARGIN;
			rdqsg->phase[i] -= PHY_RDQSG_PHASE_STEP) {
			ddr_write(rdqsg->phase[i] << PHY_RDQSG_PHASE_BIT,
				base_phy + DDR_PHY_DXNRDQSGDLY(cfg->rank_idx, i));
			ddr_phy_cfg_update(base_phy);
			if (0 == ddr_ddrt_test(DDRT_WR_COMPRARE_MODE, i, -1))
				break;
		}
		if (rdqsg->phase[i] <= PHY_GATE_PHASE_MARGIN) {
			/* find gate phase fail */
			DDR_FATAL("find gate phase[%x] fail.",
				rdqsg->phase[i]);
			ddr_training_stat(DDR_ERR_GATING, base_phy, -1, -1);
			return -1;
		} else {
			/* decrease one setp to find bdl */
			rdqsg->phase[i] -= PHY_RDQSG_PHASE_STEP;
			ddr_write(rdqsg->phase[i] << PHY_RDQSG_PHASE_BIT,
				base_phy + DDR_PHY_DXNRDQSGDLY(cfg->rank_idx, i));
		}
	}

	ddr_phy_cfg_update(base_phy);
	return 0;
}

static int ddr_gate_find_bdl(struct ddr_cfg_st *cfg,
	struct ddr_delay_st *rdqsg)
{
	int i, j;
	unsigned int gate_result;
	unsigned int tmp;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_num = GET_BYTE_NUM(cfg);

	unsigned int swtmode = ddr_read(base_phy + DDR_PHY_SWTMODE);

	for (i = 0; i < byte_num; i++)
		rdqsg->bdl[i] = 0;

	/* enable phy sw gate training mode */
	ddr_write(swtmode | (1 << PHY_SWTMODE_SW_GTMODE_BIT),
		base_phy + DDR_PHY_SWTMODE);

	for (i = 0; i < PHY_GATE_BDL_MAX; i++) {
		ddr_phy_cfg_update(base_phy);
		ddr_ddrt_test(DDRT_READ_ONLY_MODE, -1, -1);
		gate_result = (ddr_read(base_phy + DDR_PHY_SWTRLT) >> 8)
					& PHY_SWTRLT_GATE_MASK;
		if (gate_result == ((1 << byte_num) - 1))
			break;

		for (j = 0; j < byte_num; j++) {
			if (!(gate_result & (1 << j))) {
				rdqsg->bdl[j] += DDR_GATE_BDL_STEP;
				if (rdqsg->bdl[j] > PHY_BDL_MASK) {
					tmp = ((rdqsg->bdl[j]
						- PHY_BDL_MASK - 1)
						<< PHY_RDQSG_TX_BDL_BIT)
						+ (rdqsg->phase[j]
						<< PHY_RDQSG_PHASE_BIT)
						+ (PHY_BDL_MASK - 1);
				} else {
					tmp = (rdqsg->phase[j]
						<< PHY_RDQSG_PHASE_BIT)
						+ rdqsg->bdl[j];
				}
				ddr_write(tmp,
					base_phy + DDR_PHY_DXNRDQSGDLY(cfg->rank_idx, j));
			}
		}
	}

	/* disable phy sw gate training mode */
	ddr_write(swtmode & (~(1 << PHY_SWTMODE_SW_GTMODE_BIT)),
		base_phy + DDR_PHY_SWTMODE);

	if (i == PHY_GATE_BDL_MAX) {  /* find gate bdl fail */
		DDR_FATAL("PHY[%x] find gate bdl fail. result[%x]",
				base_phy, gate_result);
		for (j = 0; j < byte_num; j++)
			if (!(gate_result & (1 << j)))
				ddr_training_stat(DDR_ERR_GATING,
					base_phy, j, -1);
		return -1;
	} else
		return 0;
}

int ddr_gate_training(struct ddr_cfg_st *cfg)
{
	unsigned int i, tmp;
	unsigned int byte_num;
	struct ddr_delay_st rdqsg;
	unsigned int def_delay[DDR_PHY_BYTE_MAX];
	int result;
	unsigned int base_phy = cfg->cur_phy;

	DDR_DEBUG("DDR Gate training.");

	byte_num = GET_BYTE_NUM(cfg);

	for (i = 0; i < byte_num; i++)
		def_delay[i] = ddr_read(base_phy + DDR_PHY_DXNRDQSGDLY(cfg->rank_idx, i));

	/* find phase first */
	result = ddr_gate_find_phase(cfg, &rdqsg);

	/* find bdl */
	if (!result)
		result = ddr_gate_find_bdl(cfg, &rdqsg);

	/* set new phase */
	if (!result) {
		for (i = 0; i < byte_num; i++) {
			rdqsg.phase[i] -= PHY_GATE_PHASE_MARGIN;
			tmp = ddr_read(base_phy + DDR_PHY_DXNRDQSGDLY(cfg->rank_idx, i));
			tmp &= ~(PHY_RDQSG_PHASE_MASK << PHY_RDQSG_PHASE_BIT);
			tmp |= rdqsg.phase[i] << PHY_RDQSG_PHASE_BIT;
			ddr_write(tmp, base_phy + DDR_PHY_DXNRDQSGDLY(cfg->rank_idx, i));
		}
	} else {
		/* restore default value */
		for (i = 0; i < byte_num; i++)
			ddr_write(def_delay[i],
			base_phy + DDR_PHY_DXNRDQSGDLY(cfg->rank_idx, i));
	}

	ddr_phy_cfg_update(base_phy);
	return 0; /* use default value and not reset */
}

int ddr_gating_func(struct ddr_cfg_st *cfg)
{
	struct tr_relate_reg relate_reg;
	int result = 0;

	/* gate training disable */
	if (ddr_training_check_bypass(cfg, DDR_BYPASS_GATE_MASK)) {
		/* check hardware gating */
		if (ddr_read(cfg->cur_phy + DDR_PHY_PHYINITSTATUS)
			& PHY_INITSTATUS_GT_MASK) {
			DDR_FATAL("PHY[%x] hw gating fail.", cfg->cur_phy);
			ddr_training_stat(DDR_ERR_HW_GATING,
				cfg->cur_phy, -1, -1);
			return -1;
		}
		return 0;
	}

	ddr_training_save_reg(cfg, &relate_reg, DDR_BYPASS_GATE_MASK);

	ddr_training_switch_axi(cfg);
	ddr_ddrt_init(cfg, DDR_DDRT_MODE_GATE);
	result += ddr_gate_training(cfg);

	ddr_training_restore_reg(cfg, &relate_reg);

	return result;
}
#else
int ddr_gating_func(struct ddr_cfg_st *cfg)
{
	DDR_WARNING("Not support DDR gate training.");
	return 0;
}
#endif /* DDR_GATE_TRAINING_CONFIG */

#define __ac_training__
#ifdef DDR_AC_TRAINING_CONFIG
/**
 * Get clk value.
 * Assume clk0 and clk1 is the same.
 */
static int ddr_ac_get_clk(unsigned int base_phy)
{
	unsigned int val;
	unsigned int ac_phy_ctl;
	/* Static register have to read two times to get the right value. */
	ac_phy_ctl = ddr_read(base_phy + DDR_PHY_ACPHYCTL7);
	ac_phy_ctl = ddr_read(base_phy + DDR_PHY_ACPHYCTL7);
	/* halft_dramclk0 */
	val = (ac_phy_ctl >> PHY_ACPHY_DRAMCLK0_BIT)
		& PHY_ACPHY_DRAMCLK_MASK;
	val = (val << PHY_ACPHY_DRAMCLK_EXT_BIT)
		| ((ac_phy_ctl >> PHY_ACPHY_DCLK0_BIT)
			& PHY_ACPHY_DCLK_MASK);
	return val;
}

/* Set clk0 and clk1 the same value */
static void ddr_ac_set_clk(unsigned int base_phy, unsigned int val)
{
	unsigned int ac_phy_ctl, dramclk, dclk;
	dclk       = val & PHY_ACPHY_DCLK_MASK;
	dramclk    = (val >> PHY_ACPHY_DRAMCLK_EXT_BIT)
		& PHY_ACPHY_DRAMCLK_MASK;
	/* Static register have to read two times to get the right value. */
	ac_phy_ctl = ddr_read(base_phy + DDR_PHY_ACPHYCTL7);
	ac_phy_ctl = ddr_read(base_phy + DDR_PHY_ACPHYCTL7);
	/* clear cp1p_dclk0 */
	ac_phy_ctl &= (~(PHY_ACPHY_DCLK_MASK << PHY_ACPHY_DCLK0_BIT));
	/* clear ck2p_dclk1 */
	ac_phy_ctl &= (~(PHY_ACPHY_DCLK_MASK << PHY_ACPHY_DCLK1_BIT));
	/* clear halft_dramclk0 */
	ac_phy_ctl &= (~(PHY_ACPHY_DRAMCLK_MASK << PHY_ACPHY_DRAMCLK0_BIT));
	/* clear halft_dramclk1 */
	ac_phy_ctl &= (~(PHY_ACPHY_DRAMCLK_MASK << PHY_ACPHY_DRAMCLK1_BIT));

	ac_phy_ctl |= (dclk << PHY_ACPHY_DCLK0_BIT);  /* set cp1p_dclk0 */
	ac_phy_ctl |= (dclk << PHY_ACPHY_DCLK1_BIT);  /* set cp2p_dclk1 */
	/* set halft_dramclk0 */
	ac_phy_ctl |= (dramclk << PHY_ACPHY_DRAMCLK0_BIT);
	/* set halft_dramclk1 */
	ac_phy_ctl |= (dramclk << PHY_ACPHY_DRAMCLK1_BIT);
	ddr_write(ac_phy_ctl, base_phy + DDR_PHY_ACPHYCTL7);
}

/**
 * Get cs bdl value.
 * Assume cs0 and cs 1 is the same.
 */
static int ddr_ac_get_cs(unsigned int base_phy)
{
	return (ddr_read(base_phy + DDR_PHY_ACCMDBDL2) >> 1) & PHY_BDL_MASK;
}

/* Set CS value */
static void ddr_ac_set_cs(unsigned int base_phy, unsigned int val)
{
	unsigned int ac_cmd_bdl;
	ac_cmd_bdl = ddr_read(base_phy + DDR_PHY_ACCMDBDL2);
	ac_cmd_bdl &= (~(PHY_BDL_MASK << PHY_ACCMD_CS0_BIT)); /* clear cs0_bdl */
	ac_cmd_bdl &= (~(PHY_BDL_MASK << PHY_ACCMD_CS1_BIT)); /* clear cs1_bdl */
	ac_cmd_bdl |= (val << PHY_ACCMD_CS0_BIT); /* set cs0_bdl */
	ac_cmd_bdl |= (val << PHY_ACCMD_CS1_BIT); /* set cs1_bdl */
	ddr_write(ac_cmd_bdl, base_phy + DDR_PHY_ACCMDBDL2);
}

static int ddr_ac_ddrt_test(unsigned int mask, unsigned int base_phy)
{
	unsigned int regval;
	unsigned int times = 0;

	DDRT_REG_WRITE(mask | DDRT_CFG_START, DDR_REG_BASE_DDRT + DDRT_OP);
	DDRT_REG_WRITE(0, DDR_REG_BASE_DDRT + DDRT_STATUS);

	do {
		regval = DDRT_REG_READ(DDR_REG_BASE_DDRT + DDRT_STATUS);
		times++;
	} while ((!(regval & DDRT_TEST_DONE_MASK))
			&& (times < DDRT_WAIT_TIMEOUT));

	if (times >= DDRT_WAIT_TIMEOUT) {
		DDR_FATAL("DDRT wait timeout.");
		ddr_training_stat(DDR_ERR_DDRT_TIME_OUT, base_phy, -1, -1);
		return -1;
	}

	/* DDRT_WRITE_ONLY_MODE */
	if (DDRT_WRITE_ONLY_MODE == (mask & DDRT_TEST_MODE_MASK))
		return 0;

	/* DDRT_READ_ONLY_MODE */
	if (regval & DDRT_TEST_PASS_MASK) /* No error occurred, test pass. */
		return 0;
	else
		return -1;

}

/* Check CS value */
static int ddr_ac_check_cs(unsigned int base_phy, unsigned int def_cs,
	unsigned int step)
{
	ddr_ac_set_cs(base_phy, def_cs + step);
	ddr_phy_cfg_update(base_phy);

	ddr_ac_ddrt_test(DDRT_WRITE_ONLY_MODE, base_phy);

	ddr_ac_set_cs(base_phy, def_cs); /* restore default to check */
	ddr_phy_cfg_update(base_phy);

	return ddr_ac_ddrt_test(DDRT_READ_ONLY_MODE, base_phy);
}

/* Check CLK value */
static int ddr_ac_check_clk(struct ddr_cfg_st *cfg, unsigned int def_clk,
	struct ddr_delay_st *def_phase,
	unsigned int step)
{
	int i;
	unsigned int wdqs_phase_range, wdq_phase_range, phase_range;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_num = GET_BYTE_NUM(cfg);

	/* set new value */
	ddr_ac_set_clk(base_phy, def_clk + step);
	for (i = 0; i < byte_num; i++) {
		wdqs_phase_range = PHY_WDQS_PHASE_MASK
			- ((def_phase->phase[i] >> PHY_WDQS_PHASE_BIT)
				& PHY_WDQS_PHASE_MASK);
		wdq_phase_range  = PHY_WDQ_PHASE_MASK
			- ((def_phase->bdl[i] >> PHY_WDQ_PHASE_BIT)
				& PHY_WDQ_PHASE_MASK);
		phase_range = (wdqs_phase_range < wdq_phase_range)
			? wdqs_phase_range : wdq_phase_range;
		phase_range = (phase_range < step) ? phase_range : step;

		ddr_write(def_phase->phase[i]
				+ (phase_range << PHY_WDQS_PHASE_BIT),
				base_phy + DDR_PHY_DXWDQSDLY(cfg->rank_idx, i));
		ddr_write(def_phase->bdl[i]
				+ (phase_range << PHY_WDQ_PHASE_BIT),
				base_phy + DDR_PHY_DXNWDQDLY(cfg->rank_idx, i));
	}
	ddr_phy_cfg_update(base_phy);

	ddr_ac_ddrt_test(DDRT_WRITE_ONLY_MODE, base_phy);

	/* restore default to check */
	ddr_ac_set_clk(base_phy, def_clk);
	for (i = 0; i < byte_num; i++) {
		ddr_write(def_phase->phase[i],
			base_phy + DDR_PHY_DXWDQSDLY(cfg->rank_idx, i));
		ddr_write(def_phase->bdl[i],
			base_phy + DDR_PHY_DXNWDQDLY(cfg->rank_idx, i));
	}
	ddr_phy_cfg_update(base_phy);

	return ddr_ac_ddrt_test(DDRT_READ_ONLY_MODE, base_phy);
}

/* Find CS difference */
static int ddr_ac_find_cs(unsigned int base_phy)
{
	unsigned int def_cs, step;

	def_cs = ddr_ac_get_cs(base_phy);
	for (step = 1; step <= (PHY_BDL_MASK - def_cs); step++) {
		if (ddr_ac_check_cs(base_phy, def_cs, step)) {
			DDR_DEBUG("PHY[%x] default cs[%x], find diff_cs[%x]",
					base_phy, def_cs, step);
			break;
		}
	}

	return step;
}

/* Find CLK difference */
static int ddr_ac_find_clk(struct ddr_cfg_st *cfg)
{
	int i;
	unsigned int def_clk, step;
	struct ddr_delay_st def_phase;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int byte_num = GET_BYTE_NUM(cfg);

	def_clk = ddr_ac_get_clk(base_phy);
	for (i = 0; i < byte_num; i++) {
		/* WDQS phase */
		def_phase.phase[i] = ddr_read(base_phy + DDR_PHY_DXWDQSDLY(cfg->rank_idx, i));
		/* WDQ phase */
		def_phase.bdl[i]   = ddr_read(base_phy + DDR_PHY_DXNWDQDLY(cfg->rank_idx, i));
	}

	for (step = 1; step <= (PHY_ACPHY_CLK_MAX - def_clk); step++) {
		if (ddr_ac_check_clk(cfg, def_clk, &def_phase, step)) {
			DDR_DEBUG("PHY[%x] default clk[%x], find diff_clk[%x]",
				base_phy, def_clk, step);
			break;
		}
	}

	return step;
}

/* DDR AC training */
int ddr_ac_training(struct ddr_cfg_st *cfg)
{
	unsigned int diff_cs, diff_clk;
	unsigned int clk_phase, cs_bdl, phase_tmp;
	unsigned int byte_num;
	unsigned int wdqs_phase, wdq_phase;
	unsigned int wdqs_phase_range, wdq_phase_range, phase_range;
	unsigned int def_clk, def_cs;
	int i;
	unsigned int base_phy = cfg->cur_phy;

	DDR_DEBUG("DDR AC training.");

	byte_num = GET_BYTE_NUM(cfg);

	diff_cs  = ddr_ac_find_cs(base_phy);            /* setup time(bdl) */
	diff_clk = ddr_ac_find_clk(cfg);                /* hold time(phase) */
	/* cs bdl transform to clk phase */
	phase_tmp = diff_cs >> DDR_BDL_PHASE_REL;

	if (diff_clk > phase_tmp) {
		clk_phase = (diff_clk - phase_tmp) >> 1;
		def_clk = ddr_ac_get_clk(base_phy);

		/* set new value */
		ddr_ac_set_clk(base_phy, def_clk + clk_phase);
		for (i = 0; i < byte_num; i++) {
			wdqs_phase = ddr_read(base_phy + DDR_PHY_DXWDQSDLY(cfg->rank_idx, i));
			wdq_phase  = ddr_read(base_phy + DDR_PHY_DXNWDQDLY(cfg->rank_idx, i));

			wdqs_phase_range = PHY_WDQS_PHASE_MASK
				- ((wdqs_phase >> PHY_WDQS_PHASE_BIT)
					& PHY_WDQS_PHASE_MASK);
			wdq_phase_range  = PHY_WDQ_PHASE_MASK
				- ((wdq_phase >> PHY_WDQ_PHASE_BIT)
					& PHY_WDQ_PHASE_MASK);
			phase_range = (wdqs_phase_range < wdq_phase_range)
				? wdqs_phase_range : wdq_phase_range;
			phase_range = (phase_range < clk_phase)
				? phase_range : clk_phase;
			ddr_write(wdqs_phase
					+ (phase_range << PHY_WDQS_PHASE_BIT),
					base_phy + DDR_PHY_DXWDQSDLY(cfg->rank_idx, i));
			ddr_write(wdq_phase
					+ (phase_range << PHY_WDQ_PHASE_BIT),
					base_phy + DDR_PHY_DXNWDQDLY(cfg->rank_idx, i));
		}
		DDR_DEBUG("PHY[%x] def clk[%x] add phase[%x]",
			base_phy, def_clk, clk_phase);
	} else {
		def_cs = ddr_ac_get_cs(base_phy);
		cs_bdl = 0;
		if (diff_cs > (diff_clk << DDR_BDL_PHASE_REL))
			cs_bdl = diff_cs - (diff_clk << DDR_BDL_PHASE_REL);

		ddr_ac_set_cs(base_phy, def_cs + cs_bdl);
		DDR_DEBUG("PHY[%x] def cs[%x] add bdl[%x]",
			base_phy, def_cs, cs_bdl);
	}

	ddr_phy_cfg_update(base_phy);
	return 0;
}

int ddr_ac_training_func(struct ddr_cfg_st *cfg)
{
	int result = 0;
	struct tr_relate_reg relate_reg;

	/* AC training disable */
	if (ddr_training_check_bypass(cfg, DDR_BYPASS_AC_MASK))
		return 0;

	ddr_training_save_reg(cfg, &relate_reg, DDR_BYPASS_AC_MASK);

	ddr_training_switch_axi(cfg);
	ddr_ddrt_init(cfg, DDR_DDRT_MODE_DATAEYE);
	result += ddr_ac_training(cfg);

	ddr_training_restore_reg(cfg, &relate_reg);

	return result;
}
#else
int ddr_ac_training_func(struct ddr_cfg_st *cfg)
{
	DDR_WARNING("Not support DDR AC training.");
	return 0;
}
#endif /* DDR_AC_TRAINING_CONFIG */

#define __lpca_training__
#ifdef DDR_LPCA_TRAINING_CONFIG
/* Reset address bdl training data */
static void ddr_lpca_reset(struct ca_data_st *data)
{
	unsigned int index;
	for (index = 0; index < DDR_PHY_CA_MAX; index++) {
		data->left[index] = -1;
		data->right[index] = -1;
	}

	data->min = PHY_ACADDR_BDL_MASK;
	data->max = 0;
	data->done = 0;
}

/* Get ca bit relation */
static void ddr_lpca_get_bit(struct ca_data_st *data)
{
	unsigned int index;
	//unsigned int swap_sel;

	/* get ca bit in four register  */
	#if 0
	for (index = 0; index < (DDR_PHY_CA_REG_MAX - 1); index++) {
		ddr_write(index + 1, data->base_phy + DDR_PHY_CATSWAPINDEX);
		swap_sel = ddr_read(data->base_phy + DDR_PHY_CATSWAPSEL);

		data->bits[index * 2].bit_p =
			swap_sel & PHY_CATSWAPSEL_BIT_MASK;
		data->bits[index * 2].bit_n =
			(swap_sel >> 8) & PHY_CATSWAPSEL_BIT_MASK;
		data->bits[index * 2 + 1].bit_p =
			(swap_sel >> 16) & PHY_CATSWAPSEL_BIT_MASK;
		data->bits[index * 2 + 1].bit_n =
			(swap_sel >> 24) & PHY_CATSWAPSEL_BIT_MASK;
	}
	#else /* for HiMVPV200 */
	for (index = 0; index < (DDR_PHY_CA_REG_MAX - 1); index++) {
		data->bits[index * 2].bit_p =index*4+ 0;
		data->bits[index * 2].bit_n =index*4+ 1;
		data->bits[index * 2 + 1].bit_p =index*4+ 2;
		data->bits[index * 2 + 1].bit_n =index*4+ 3;
	}
	#endif

	/**
	 * set ca bit for ca4 and ca9
	 * ca4 = ca0, ca9 = ca5
	 */
	for (index = 8; index > 4; index--) {
		data->bits[index].bit_p = data->bits[index - 1].bit_p;
		data->bits[index].bit_n = data->bits[index - 1].bit_n;
	}

	data->bits[4].bit_p = data->bits[0].bit_p;
	data->bits[4].bit_n = data->bits[0].bit_n;
	data->bits[9].bit_p = data->bits[5].bit_p;
	data->bits[9].bit_n = data->bits[5].bit_n;

#if defined(DDR_TRAINING_CMD)
	for (index = 0; index < DDR_PHY_CA_MAX; index++) {
		DDR_INFO("CA[%x] bit_p[%x]", index, data->bits[index].bit_p);
		DDR_INFO("CA[%x] bit_n[%x]", index, data->bits[index].bit_n);
	}
#endif
}

/* Get address bdl default value */
static void ddr_lpca_get_def(struct ca_data_st *data)
{
	unsigned int index;

	for (index = 0; index < DDR_PHY_CA_REG_MAX; index++)
		data->def[index] = ddr_read(data->base_phy
			+ DDR_PHY_ACADDRBDL(index));
}

/* Restore address bdl default value */
static void ddr_lpca_restore_def(struct ca_data_st *data)
{
	unsigned int index;

	for (index = 0; index < DDR_PHY_CA_REG_MAX; index++)
		ddr_write(data->def[index], data->base_phy
			+ DDR_PHY_ACADDRBDL(index));

	ddr_phy_cfg_update(data->base_phy);
}

/* Set address bdl value */
static void ddr_lpca_set_bdl(unsigned int base_phy, unsigned int bdl)
{
	unsigned int index;
	for (index = 0; index < DDR_PHY_CA_REG_MAX; index++)
		ddr_write(bdl | (bdl << PHY_ACADDRBDL_ADDR1_BIT),
			base_phy + DDR_PHY_ACADDRBDL(index));

	ddr_phy_cfg_update(base_phy);
}

/* Update address bdl value with training result */
static void ddr_lpca_update_bdl(struct ca_data_st *data)
{
	unsigned int index;
	unsigned int addr0, addr1;

	for (index = 0; index < DDR_PHY_CA_REG_MAX; index++) {
		addr0 = (data->left[index * 2] + data->right[index * 2]) >> 1;
		addr1 = (data->left[index * 2 + 1]
			+ data->right[index * 2 + 1]) >> 1;
		ddr_write(addr0 | (addr1 << PHY_ACADDRBDL_ADDR1_BIT),
			data->base_phy + DDR_PHY_ACADDRBDL(index));
	}

	ddr_phy_cfg_update(data->base_phy);
}

/* Init data before training */
static void ddr_lpca_init(unsigned int base_dmc, unsigned int base_phy,
	struct ca_data_st *data)
{
	data->base_dmc = base_dmc;
	data->base_phy = base_phy;

	/* gat ca bit relation */
	ddr_lpca_get_bit(data);

	/* get ac addr bdl default value */
	ddr_lpca_get_def(data);

	/* reset training data */
	ddr_lpca_reset(data);
}

/* Display training result */
static void ddr_lpca_display(struct ca_data_st *data)
{
#if defined(DDR_TRAINING_CMD)
	unsigned int index;

	DDR_DEBUG("CA phase[%x = %x]",
			data->base_phy + DDR_PHY_ADDRPHBOUND,
			ddr_read(data->base_phy + DDR_PHY_ADDRPHBOUND));

	for (index = 0; index < DDR_PHY_CA_MAX; index++)
		DDR_DEBUG("CA[%x] left[%x] right[%x]",
			index, data->left[index], data->right[index]);

	DDR_DEBUG("min[%x] max[%x] done[%x]",
		data->min, data->max, data->done);
#endif
}

/* Wait lpca command done */
static void ddr_lpca_wait(volatile union U_PHY_CATCONFIG *ca)
{
	unsigned int count = 0;
	while (count < DDR_LPCA_WAIT_TIMEOUT) {
		if (1 == ca->bits.sw_cat_dqvalid) {
			ca->bits.sw_cat_dqvalid = 0; /* clear */
			break;
		}

		count++;
	}

	/* generally, count is 0 */
	if (count >= DDR_LPCA_WAIT_TIMEOUT)
		DDR_ERROR("LPCA wait timeout.");
}

/* Compare dq result and pattern */
static int ddr_lpca_compare(struct ca_bit_st *ca_bit,
	unsigned int dq_result, unsigned int pattern_p,
	unsigned int pattern_n, unsigned int index)
{
	if (((dq_result >> ca_bit->bit_p) & 0x1)
		!= ((pattern_p >> index) & 0x1))
		return -1;

	if (((dq_result >> ca_bit->bit_n) & 0x1)
		!= ((pattern_n >> index) & 0x1))
		return -1;

	return 0;
}

/* Check each CA whether pass */
static void ddr_lpca_check(struct ca_data_st *data, unsigned int bdl,
	unsigned int is_ca49)
{
	unsigned int dq_result = ddr_read(data->base_phy + DDR_PHY_PHYDQRESULT);
	unsigned int pattern_p = ddr_read(data->base_phy
		+ DDR_PHY_SWCATPATTERN_P) & PHY_CAT_PATTERN_MASK;
	unsigned int pattern_n = ddr_read(data->base_phy
		+ DDR_PHY_SWCATPATTERN_N) & PHY_CAT_PATTERN_MASK;
	unsigned int index;

	for (index = 0; index < DDR_PHY_CA_MAX; index++) {
		if (is_ca49) {
			if (4 != index && 9 != index)
				continue;
		} else {
			if (4 == index || 9 == index)
				continue;
		}

		/* compare result and pattern */
		if (!ddr_lpca_compare(&data->bits[index],
				dq_result, pattern_p, pattern_n, index)) {
			/* pass */
			if (-1 == data->left[index]) {
				data->left[index] = bdl;
				/* set min left bound */
				if (bdl < data->min)
					data->min = bdl;
			}

			/* unstable border value or abnormal value */
			if ((-1 != data->right[index])
				&& ((bdl - data->right[index]) > 1))
				DDR_WARNING("CA[%x] bdl[%x] right[%x] ph[%x]",
					index, bdl, data->right[index],
					ddr_read(data->base_phy
					+ DDR_PHY_ADDRPHBOUND));

			data->right[index] = bdl;
			data->done |= (0x1 << index);

			/* set max right bound */
			if (data->right[index] > data->max)
				data->max = data->right[index];
		}
	}
}

/* Excute lpca command and check result */
static void ddr_lpca_excute(struct ca_data_st *data, unsigned int bdl,
	unsigned int is_ca49)
{
	volatile union U_PHY_CATCONFIG *ca = (union U_PHY_CATCONFIG *)
		(data->base_phy + DDR_PHY_CATCONFIG);

	if (is_ca49)
		ca->bits.sw_cat_mrw48 = 1;
	else
		ca->bits.sw_cat_mrw41 = 1;

	ddr_lpca_wait(ca);
	ca->bits.sw_cat_cke_low = 1;
	ddr_lpca_wait(ca);
	ca->bits.sw_cat_strobe = 1;
	ddr_lpca_wait(ca);

	/* check PHYDQRESULT */
	ddr_lpca_check(data, bdl, is_ca49);

	ca->bits.sw_cat_cke_high = 1;
	ddr_lpca_wait(ca);
	ca->bits.sw_cat_mrw42 = 1;
	ddr_lpca_wait(ca);
}

/* Find address bdl */
static int ddr_lpca_find_bdl(struct ca_data_st *data)
{
	unsigned int bdl;

	for (bdl = 0; bdl <= PHY_ACADDR_BDL_MASK; bdl++) {
		/* update bdl */
		ddr_lpca_set_bdl(data->base_phy, bdl);

		/* ca0~ca3, ca5~ca8 */
		ddr_lpca_excute(data, bdl, DDR_FALSE);

		/* ca4, ca9 */
		ddr_lpca_excute(data, bdl, DDR_TRUE);
	}

	if (PHY_CAT_PATTERN_MASK == data->done)
		return 0;

	return -1;
}

/* Loop phase to find valid bdl and phase */
static int ddr_lpca_loop_phase(struct ca_data_st *data, int step)
{
	volatile union U_PHY_ADDRPHBOUND *ph = (union U_PHY_ADDRPHBOUND *)
		(data->base_phy + DDR_PHY_ADDRPHBOUND);
	unsigned int phase;
	unsigned int addrph_def = ph->bits.addrph_a;
	int addrph = addrph_def;

	for (phase = 0; phase <= PHY_ADDRPH_MASK; phase++) {
		/* reset ca training data */
		ddr_lpca_reset(data);

		/* find bdl */
		if (!ddr_lpca_find_bdl(data))
			return 0;

		addrph += step;
		if (addrph < 0 || addrph > PHY_ADDRPH_MASK)
			break;

		ph->bits.addrph_a = addrph;
		ddr_phy_cfg_update(data->base_phy);
	}

	/* restore default value */
	DDR_DEBUG("current phase[%x = %x], restore default[%x]",
		ph, *ph, addrph_def);
	ph->bits.addrph_a = addrph_def;
	return -1;
}

/* Find a valid phase */
static int ddr_lpca_find_phase(struct ca_data_st *data)
{
	/* increase default value to find */
	if (!ddr_lpca_loop_phase(data, 1))
		return 0;

	/* decrease default value to find */
	if (!ddr_lpca_loop_phase(data, -1))
		return 0;

	return -1;
}

/* Set step to adjust address window */
static int ddr_lpca_set_step(struct ca_data_st *data)
{
	/* max window, no need to found */
	if (0 == data->min && PHY_ACADDR_BDL_MASK == data->max)
		return 0;

	if (0 == data->min)
		return -1; /* window on left, move to right */
	else
		return 1; /* window on right, move to left */
}

/**
 * Adjust address window via change phase.
 * Increase phase, window will move to left.
 */
static void ddr_lpca_adjust(struct ca_data_st *data)
{
	int step = 0;
	volatile union U_PHY_ADDRPHBOUND *ph = (union U_PHY_ADDRPHBOUND *)
		(data->base_phy + DDR_PHY_ADDRPHBOUND);
	unsigned int phase;
	unsigned int addrph_last = ph->bits.addrph_a;
	int addrph_cur = addrph_last;

	/* set step to increase or decrease phase */
	step = ddr_lpca_set_step(data);

	if (!step)
		return;

	for (phase = 0; phase <= PHY_ADDRPH_MASK; phase++) {
		addrph_cur += step;
		if (addrph_cur < 0 || addrph_cur > PHY_ADDRPH_MASK)
			return;

		ph->bits.addrph_a = addrph_cur;
		ddr_phy_cfg_update(data->base_phy);

		/* reset ca training data */
		ddr_lpca_reset(data);

		if (ddr_lpca_find_bdl(data)) {
			/* not find bdl, restore last value */
			addrph_cur -= step;
			ddr_lpca_find_bdl(data);
			return;
		}

		/* max window: ------- */
		if (0 == data->min && PHY_ACADDR_BDL_MASK == data->max)
			return;

		/* last window: -----xx */
		if (0 == data->min && 1 == step) {
			/* last value is best */
			addrph_cur -= step;
			ph->bits.addrph_a = addrph_cur;
			ddr_phy_cfg_update(data->base_phy);
			ddr_lpca_reset(data);
			ddr_lpca_find_bdl(data);
			return;
		}

		/* best window: x-----x */
		if (0 < data->min && -1 == step)
			return;
	}
}

/* Low power DDR CA training */
int ddr_lpca_training(struct ddr_cfg_st *cfg)
{
	volatile union U_PHY_CATCONFIG *ca = (union U_PHY_CATCONFIG *)
		(cfg->cur_phy + DDR_PHY_CATCONFIG);

	struct ca_data_st data;
	int ret = -1;

	DDR_DEBUG("DDR LPCA training.");

	/* init data */
	ddr_lpca_init(cfg->cur_dmc, cfg->cur_phy, &data);

	/* enable sw ca training, wait 62.5ns */
	ca->bits.sw_cat_en = 1;

	/* find a valid phase first */
	ret = ddr_lpca_find_phase(&data);

	/* display training result */
	ddr_lpca_display(&data);

	if (ret) {
		/* restore default value when fail */
		ddr_lpca_restore_def(&data);
		DDR_ERROR("PHY[%x] found phase fail, result[%x].",
			cfg->cur_phy, data.done);
		ddr_training_stat(DDR_ERR_LPCA, cfg->cur_phy, -1, -1);
	} else {
		/* adjust window via phase */
		ddr_lpca_adjust(&data);
		ddr_lpca_display(&data);
		/* set training result */
		ddr_lpca_update_bdl(&data);
	}

	/* disable sw ca training */
	ca->bits.sw_cat_en = 0;

	/* save lpca result data to printf */
	ddr_lpca_data_save(&data);

	return ret;
}

int ddr_lpca_training_func(struct ddr_cfg_st *cfg)
{
	int result = 0;
	struct tr_relate_reg relate_reg;

	/* LPCA training disable */
	if (ddr_training_check_bypass(cfg, DDR_BYPASS_LPCA_MASK))
		return 0;

	ddr_training_save_reg(cfg, &relate_reg, DDR_BYPASS_LPCA_MASK);

	/* only lowpower ddr3 support */
	if (PHY_DRAMCFG_TYPE_LPDDR3 ==
		(ddr_read(cfg->cur_phy + DDR_PHY_DRAMCFG)
		& PHY_DRAMCFG_TYPE_LPDDR3))
		result += ddr_lpca_training(cfg);

	ddr_training_restore_reg(cfg, &relate_reg);

	return result;
}
#else
int ddr_lpca_training_func(struct ddr_cfg_st *cfg)
{
	DDR_WARNING("Not support LPDDR CA training.");
	return 0;
}
#endif /* DDR_LPCA_TRAINING_CONFIG */

/* s40/t28/t16 not support dcc training */
#define __dcc_training__
#ifdef DDR_DCC_TRAINING_CONFIG
/* Save two rank RDET result */
static void ddr_save_two_rank_bdl(struct ddr_cfg_st *cfg, struct dcc_data_st *dcc_data)
{
	unsigned int byte_idx;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int rank_idx = cfg->rank_idx;
	unsigned int byte_num = cfg->phy[cfg->phy_idx].total_byte_num;

	for (byte_idx = 0; byte_idx < byte_num; byte_idx++) {
		dcc_data->rank[rank_idx].dq03[byte_idx] = ddr_read(base_phy + DDR_PHY_DXNRDQNBDL0(rank_idx, byte_idx));
		dcc_data->rank[rank_idx].dq47[byte_idx] = ddr_read(base_phy + DDR_PHY_DXNRDQNBDL1(rank_idx, byte_idx));
		dcc_data->rank[rank_idx].rdm[byte_idx] = ddr_read(base_phy + DDR_PHY_DXNRDQNBDL2(rank_idx, byte_idx));
		dcc_data->rank[rank_idx].rdqs[byte_idx] = ddr_read(base_phy + DDR_PHY_DXNRDQSDLY(byte_idx));

		DDR_DEBUG("rank[%x] dq03[%x] dq47[%x] rdm[%x] rdqs[%x]", rank_idx,
			dcc_data->rank[rank_idx].dq03[byte_idx],
			dcc_data->rank[rank_idx].dq47[byte_idx],
			dcc_data->rank[rank_idx].rdm[byte_idx],
			dcc_data->rank[rank_idx].rdqs[byte_idx]);
	}
}

/* Restore two rank RDET result */
static void ddr_restore_two_rank_bdl(struct ddr_cfg_st *cfg, struct dcc_data_st *dcc_data)
{
	unsigned int byte_idx;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int rank_idx = cfg->rank_idx;
	unsigned int byte_num = cfg->phy[cfg->phy_idx].total_byte_num;

	for (byte_idx = 0; byte_idx < byte_num; byte_idx++) {
		ddr_write(dcc_data->rank[rank_idx].dq03[byte_idx], base_phy + DDR_PHY_DXNRDQNBDL0(rank_idx, byte_idx));
		ddr_write(dcc_data->rank[rank_idx].dq47[byte_idx], base_phy + DDR_PHY_DXNRDQNBDL1(rank_idx, byte_idx));
		ddr_write(dcc_data->rank[rank_idx].rdm[byte_idx], base_phy + DDR_PHY_DXNRDQNBDL2(rank_idx, byte_idx));
		ddr_write(dcc_data->rank[rank_idx].rdqs[byte_idx], base_phy + DDR_PHY_DXNRDQSDLY(byte_idx));
	}
}

/* DMC_CFG_SREF exit self-refresa enter powerdown */
static void ddr_exit_sref_enter_pd(struct ddr_cfg_st *cfg, struct dmc_cfg_sref_st *cfg_sref)
{
	int i;
	struct ddr_phy_st *phy_st =  &cfg->phy[cfg->phy_idx];

	for (i = 0; i < phy_st->dmc_num; i++) {
		cfg_sref->val[i] = ddr_read(phy_st->dmc[i].addr + DDR_DMC_CFG_SREF);
		ddr_write((cfg_sref->val[i] & (~DMC_CFG_INIT_XSREF_PD_MASK)) | DMC_CFG_INIT_XSREF_PD,
			phy_st->dmc[i].addr + DDR_DMC_CFG_SREF);
	}
}

/* Restore DMC_CFG_SREF config */
static void ddr_restore_sref_cfg(struct ddr_cfg_st *cfg, struct dmc_cfg_sref_st *cfg_sref)
{
	int i;
	struct ddr_phy_st *phy_st = &cfg->phy[cfg->phy_idx];

	for (i = 0; i < phy_st->dmc_num; i++) {
		ddr_write(cfg_sref->val[i], phy_st->dmc[i].addr + DDR_DMC_CFG_SREF);
	}
}

/* DCC RDET training */
static int ddr_dcc_dataeye_read(struct ddr_cfg_st *cfg)
{
	/* 0:PHY_TRAINCTRL0_DTR_RANK0, 1:PHY_TRAINCTRL0_DTR_RANK1 */
	DDR_PHY_SWITCH_RANK(cfg->cur_phy, cfg->rank_idx);
	return ddr_hw_training_process(cfg, PHY_PHYINITCTRL_RDET_EN);
}

/* Duty direction ctl */
static int ddr_dcc_ck_ctl(struct ddr_cfg_st *cfg, unsigned int ioctl21_def, unsigned int ctl_index)
{
	unsigned int ioctl21;
	if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[cfg->phy_idx].dram_type) {
		ioctl21 = (ioctl21_def & (~(1 << PHY_ACIOCTL21_CTL0_BIT))
							& (~(1 << PHY_ACIOCTL21_CTL1_BIT)))
							| (ctl_index << PHY_ACIOCTL21_CTL0_BIT)
							| (ctl_index << PHY_ACIOCTL21_CTL1_BIT);
		ddr_write(ioctl21, cfg->cur_phy + DDR_PHY_ACIOCTL21);
	} else {
		ioctl21 = (ioctl21_def & (~(1 << PHY_ACIOCTL21_CTL0_BIT)))
							| (ctl_index << PHY_ACIOCTL21_CTL0_BIT);
		ddr_write(ioctl21, cfg->cur_phy + DDR_PHY_ACIOCTL21);
	}
	return ioctl21;
}

/* Duty Correction */
static int ddr_dcc_correct_duty(struct ddr_cfg_st *cfg, unsigned int cur_duty, unsigned int duty_def)
{
	unsigned int ioctl21;
	if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[cfg->phy_idx].dram_type) {
		/* Correct CK0 & CK1 duty */
		ioctl21 = (duty_def & (~(PHY_ACIOCTL21_MASK << PHY_ACIOCTL21_CK0_BIT))
							& (~(PHY_ACIOCTL21_MASK << PHY_ACIOCTL21_CK1_BIT)))
							| (cur_duty << PHY_ACIOCTL21_CK0_BIT)
							| (cur_duty << PHY_ACIOCTL21_CK1_BIT);
		ddr_write(ioctl21, cfg->cur_phy + DDR_PHY_ACIOCTL21);
	} else {
		/* Correct CK0 duty */
		ioctl21 = (duty_def & (~(PHY_ACIOCTL21_MASK << PHY_ACIOCTL21_CK0_BIT)))
							| (cur_duty << PHY_ACIOCTL21_CK0_BIT);
		ddr_write(ioctl21, cfg->cur_phy + DDR_PHY_ACIOCTL21);
	}

	return ioctl21;
}

/* Duty Correction Control get win data */
static int ddr_dcc_get_win(struct dcc_data_st *dcc_data, int ck_index, int val_index)
{
	unsigned int win;
	unsigned int rdqsbdl_right;
	unsigned int rdqsbdl_left;
	rdqsbdl_right = dcc_data->ck[ck_index].val[val_index] >> PHY_DXNRDBOUND_RIGHT_BIT & PHY_DXNRDBOUND_MASK;
	rdqsbdl_left = dcc_data->ck[ck_index].val[val_index] >> PHY_DXNRDBOUND_LEFT_BIT & PHY_DXNRDBOUND_MASK;
	win = rdqsbdl_right - rdqsbdl_left;
	return win;
}

/* Duty Correction Control get the min win of two byte */
static int ddr_dcc_get_min_win(struct dcc_data_st *dcc_data, int ck_index)
{
	int i;
	unsigned int win_min;
	unsigned int cur_win;
	win_min = ddr_dcc_get_win(dcc_data, ck_index, 0);
	for (i = 0; i < DDR_CK_RESULT_MAX; i++) {
		cur_win = ddr_dcc_get_win(dcc_data, ck_index, i);
		DDR_DEBUG("CK win[%x] = [%x]", i, cur_win);
		if (cur_win < win_min) {
			win_min = cur_win;
		}
	}
	return win_min;
}

/* Duty Correction Control get ck0 min win */
static int ddr_dcc_get_ck0_win(struct ddr_cfg_st *cfg, struct dcc_data_st *dcc_data,
	int rank_index, unsigned int ck0_win_min)
{
	int ck_index = 0;
	unsigned int byte_index;
	unsigned int ck0_win;
	unsigned int byte_num = cfg->phy[cfg->phy_idx].total_byte_num;

	for (byte_index = 0; byte_index < (byte_num/2); byte_index++) {
		dcc_data->ck[ck_index].val[byte_index] = ddr_read(cfg->cur_phy + DDR_PHY_DXNRDBOUND(byte_index));
	}

	ck0_win = ddr_dcc_get_min_win(dcc_data, ck_index);

	if (ck0_win < ck0_win_min)
		ck0_win_min = ck0_win;

	return ck0_win_min;
}

/* Duty Correction Control get ck1 min win */
static int ddr_dcc_get_ck1_win(struct ddr_cfg_st *cfg, struct dcc_data_st *dcc_data,
	int rank_index, unsigned int ck1_win_min)
{
	int ck_index = 1;
	unsigned int byte_index;
	unsigned int ck1_win;
	unsigned int byte_num = cfg->phy[cfg->phy_idx].total_byte_num;

	for (byte_index = 2; byte_index < byte_num; byte_index++) {
		dcc_data->ck[ck_index].val[byte_index - 2] = ddr_read(cfg->cur_phy + DDR_PHY_DXNRDBOUND(byte_index));
	}

	ck1_win = ddr_dcc_get_min_win(dcc_data, ck_index);

	if (ck1_win < ck1_win_min)
		ck1_win_min = ck1_win;

	return ck1_win_min;
}

static void dcc_data_init(struct dcc_data_st *dcc_data)
{
	dcc_data->ck[0].win_min_ctl = 0xffffffff;
	dcc_data->ck[0].win_max_ctl = 0x0;
	dcc_data->ck[1].win_min_ctl = 0xffffffff;
	dcc_data->ck[1].win_max_ctl = 0x0;
	dcc_data->ck[0].idx_duty = 0;
	dcc_data->ck[0].idx_duty_ctl = 0;
	dcc_data->ck[0].idx_ctl = 0;
	dcc_data->ck[1].idx_duty = 0;
	dcc_data->ck[1].idx_duty_ctl = 0;
	dcc_data->ck[1].idx_ctl = 0;
	dcc_data->ck[0].BYPASS_CK_BIT = PHY_BYPASS_CK0_BIT;
	dcc_data->ck[0].ACIOCTL21_CTL_BIT = PHY_ACIOCTL21_CTL0_BIT;
	dcc_data->ck[0].ACIOCTL21_CK_BIT = PHY_ACIOCTL21_CK0_BIT;
	dcc_data->ck[1].BYPASS_CK_BIT = PHY_BYPASS_CK1_BIT;
	dcc_data->ck[1].ACIOCTL21_CTL_BIT = PHY_ACIOCTL21_CTL1_BIT;
	dcc_data->ck[1].ACIOCTL21_CK_BIT = PHY_ACIOCTL21_CK1_BIT;
}

/* dcc training get window by rank */
static int ddr_dcc_get_win_by_rank(struct ddr_cfg_st *cfg, struct dcc_data_st *dcc_data)
{
	int i;
	int result = 0;
	unsigned int rank_num = cfg->phy[cfg->phy_idx].rank_num;
	for (i = 0; i < rank_num; i++) {
		DDR_DEBUG("cur_rank = [%x]", i);
		cfg->rank_idx = i;
		/* RDET */
		result += ddr_dcc_dataeye_read(cfg);

		/* Get win */
		dcc_data->ck[0].win = ddr_dcc_get_ck0_win(cfg, dcc_data, i, dcc_data->ck[0].win);
		DDR_DEBUG("ck0 win = [%x]", dcc_data->ck[0].win);

		if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[cfg->phy_idx].dram_type) {
			dcc_data->ck[1].win = ddr_dcc_get_ck1_win(cfg, dcc_data, i, dcc_data->ck[1].win);
			DDR_DEBUG("ck1 win = [%x]", dcc_data->ck[1].win);
		}

		/* Restore two rank bdl */
		ddr_restore_two_rank_bdl(cfg, dcc_data);
	}
	return result;
}

/* ddr dcc training compare result */
static void ddr_dcc_compare_result(struct dcc_data_st *dcc_data, int ck_num,
	unsigned int base_phy, unsigned int gated_bypass_def, unsigned int ioctl21_def)
{
	int ck_idx;

	for (ck_idx = 0; ck_idx < ck_num; ck_idx++) {
		/* Config ck0 duty */
		if (dcc_data->ck[ck_idx].win_max_ctl - dcc_data->ck[ck_idx].win_min_ctl <= 2) {
			dcc_data->ck[ck_idx].def_bp = gated_bypass_def >> dcc_data->ck[ck_idx].BYPASS_CK_BIT & 0x1;
			dcc_data->ck[ck_idx].def_ctl = ioctl21_def >> dcc_data->ck[ck_idx].ACIOCTL21_CTL_BIT & 0x1;
			dcc_data->ck[ck_idx].def_duty = ioctl21_def >> dcc_data->ck[ck_idx].ACIOCTL21_CK_BIT & PHY_ACIOCTL21_MASK;

			gated_bypass_def = (gated_bypass_def & (~(1 << dcc_data->ck[ck_idx].BYPASS_CK_BIT)))
								| (dcc_data->ck[ck_idx].def_bp << dcc_data->ck[ck_idx].BYPASS_CK_BIT);
			ddr_write(gated_bypass_def, base_phy + DDR_PHY_AC_GATED_BYPASS);

			ioctl21_def = (ioctl21_def & (~(1 << dcc_data->ck[ck_idx].ACIOCTL21_CTL_BIT))
							& (~(PHY_ACIOCTL21_MASK << dcc_data->ck[ck_idx].ACIOCTL21_CK_BIT)))
							| (dcc_data->ck[ck_idx].def_ctl << dcc_data->ck[ck_idx].ACIOCTL21_CTL_BIT)
							| (dcc_data->ck[ck_idx].def_duty << dcc_data->ck[ck_idx].ACIOCTL21_CK_BIT);
			ddr_write(ioctl21_def, base_phy + DDR_PHY_ACIOCTL21);

			DDR_DEBUG("ck[%x] Final AC_GATED_BYPASS[%x]", ck_idx, gated_bypass_def);
			DDR_DEBUG("ck[%x] Final ACIOCTL21[%x]", ck_idx, ioctl21_def);
		} else {
			ioctl21_def = (ioctl21_def & (~(1 << dcc_data->ck[ck_idx].ACIOCTL21_CTL_BIT))
							& (~(PHY_ACIOCTL21_MASK << dcc_data->ck[ck_idx].ACIOCTL21_CK_BIT)))
							| (dcc_data->ck[ck_idx].idx_ctl << dcc_data->ck[ck_idx].ACIOCTL21_CTL_BIT)
							| (dcc_data->ck[ck_idx].idx_duty_ctl << dcc_data->ck[ck_idx].ACIOCTL21_CK_BIT);
			ddr_write(ioctl21_def, base_phy + DDR_PHY_ACIOCTL21);

			DDR_DEBUG("ck[%x] Final ACIOCTL21[%x]", ck_idx, ioctl21_def);
		}
	}
}

static int ddr_dcc_get_best_duty(struct ddr_cfg_st *cfg,
	struct dmc_cfg_sref_st *cfg_sref, struct dcc_data_st *dcc_data)
{
	int ck_idx;
	int ck_num;
	int result = 0;
	unsigned int cur_ctl;
	unsigned int cur_duty;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int ioctl21_def;
	unsigned int gated_bypass_def, gated_bypass_temp;

	if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[cfg->phy_idx].dram_type)
		ck_num = 2;
	else
		ck_num = 1;

	dcc_data_init(dcc_data);

	/* Save ck duty default config. Read two times to get the right static register value. */
	gated_bypass_def = ddr_read(base_phy + DDR_PHY_AC_GATED_BYPASS);
	gated_bypass_def = ddr_read(base_phy + DDR_PHY_AC_GATED_BYPASS);
	ioctl21_def = ddr_read(base_phy + DDR_PHY_ACIOCTL21);
	ioctl21_def = ddr_read(base_phy + DDR_PHY_ACIOCTL21);

	DDR_DEBUG("gated_bypass_def[%x] ioctl21_def[%x]", gated_bypass_def, ioctl21_def);

	/* DCC training exit self-refresa enter powerdown. */
	if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[cfg->phy_idx].dram_type)
		ddr_exit_sref_enter_pd(cfg, cfg_sref);

	/* DDR dcc training enter auto self-refresh. */
	if (ddr_training_ctrl_easr(cfg, DDR_ENTER_SREF))
		return -1;

	/* Enable ck0 & ck1 duty. */
	if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[cfg->phy_idx].dram_type) {
		gated_bypass_temp = gated_bypass_def | PHY_CK1_IOCTL_DUTY_EN | PHY_CK_IOCTL_DUTY_EN;
		ddr_write(gated_bypass_temp, base_phy + DDR_PHY_AC_GATED_BYPASS);
	} else {
		gated_bypass_temp = gated_bypass_def | PHY_CK_IOCTL_DUTY_EN;
		ddr_write(gated_bypass_temp, base_phy + DDR_PHY_AC_GATED_BYPASS);
	}
	DDR_DEBUG("Cur GATED_BYPASS[%x]", gated_bypass_temp);

	if (ddr_training_ctrl_easr(cfg, DDR_EXIT_SREF))
		return -1;

	for (cur_ctl = 0; cur_ctl < DDR_DUTY_CTL_NUM; cur_ctl++) {
		dcc_data->ck[0].win_min_duty = 0xffffffff;
		dcc_data->ck[0].win_max_duty = 0x0;
		dcc_data->ck[1].win_min_duty = 0xffffffff;
		dcc_data->ck[1].win_max_duty = 0x0;

		DDR_DEBUG("cur_ctl = [%x]", cur_ctl);

		if (ddr_training_ctrl_easr(cfg, DDR_ENTER_SREF))
			return -1;

		/* Correct CK duty dirrection control */
		dcc_data->ioctl21_tmp = ddr_dcc_ck_ctl(cfg, ioctl21_def, cur_ctl);

		if (ddr_training_ctrl_easr(cfg, DDR_EXIT_SREF))
			return -1;

		for (cur_duty = 0; cur_duty < DDR_DUTY_NUM; cur_duty += PHY_AC_IOCTL21_STEP) {
			dcc_data->ck[0].win = 0xffffffff;
			dcc_data->ck[1].win = 0xffffffff;

			DDR_DEBUG("cur_duty = [%x]", cur_duty);
			/* Correct ck0 and ck1 duty */
			if (ddr_training_ctrl_easr(cfg, DDR_ENTER_SREF))
				return -1;
			dcc_data->ioctl21_tmp = ddr_dcc_correct_duty(cfg, cur_duty, dcc_data->ioctl21_tmp);
			if (ddr_training_ctrl_easr(cfg, DDR_EXIT_SREF))
				return -1;
			DDR_DEBUG("Cur ACIOCTL21[%x]", dcc_data->ioctl21_tmp);

			result = ddr_dcc_get_win_by_rank(cfg, dcc_data);

			/* Get ck0/ck1 duty_win_min/duty_win_max/duty_index */
			for (ck_idx = 0; ck_idx < ck_num; ck_idx++) {
				if (dcc_data->ck[ck_idx].win < dcc_data->ck[ck_idx].win_min_duty)
					dcc_data->ck[ck_idx].win_min_duty = dcc_data->ck[ck_idx].win;

				if (dcc_data->ck[ck_idx].win > dcc_data->ck[ck_idx].win_max_duty) {
					dcc_data->ck[ck_idx].win_max_duty = dcc_data->ck[ck_idx].win;
					dcc_data->ck[ck_idx].idx_duty = cur_duty;
				}
				DDR_DEBUG("ck[%x] duty_win_min[%x] duty_win_max[%x] duty_index[%x]", ck_idx,
					dcc_data->ck[ck_idx].win_min_duty,
					dcc_data->ck[ck_idx].win_max_duty,
					dcc_data->ck[ck_idx].idx_duty);
			}
		}

		for (ck_idx = 0; ck_idx < ck_num; ck_idx++) {
		/* Get ck0/ck1 duty_win_min/duty_win_max/duty_index */
			if (dcc_data->ck[ck_idx].win_min_duty < dcc_data->ck[ck_idx].win_min_ctl)
				dcc_data->ck[ck_idx].win_min_ctl = dcc_data->ck[ck_idx].win_min_duty;

			if (dcc_data->ck[ck_idx].win_max_duty > dcc_data->ck[ck_idx].win_max_ctl) {
				dcc_data->ck[ck_idx].win_max_ctl = dcc_data->ck[ck_idx].win_max_duty;
				dcc_data->ck[ck_idx].idx_duty_ctl = dcc_data->ck[ck_idx].idx_duty;
				dcc_data->ck[ck_idx].idx_ctl = cur_ctl;
			}
			DDR_DEBUG("ck[%x] win_min_ctl[%x] win_max_ctl[%x] ctl_index0[%x] duty_ctl_idx0[%x]", ck_idx,
				dcc_data->ck[ck_idx].win_min_ctl,
				dcc_data->ck[ck_idx].win_max_ctl,
				dcc_data->ck[ck_idx].idx_ctl,
				dcc_data->ck[ck_idx].idx_duty_ctl);
		}
	}

	/* Config ck duty */
	/* DCC training exit self-refresa enter powerdown. */
	if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[cfg->phy_idx].dram_type)
		ddr_exit_sref_enter_pd(cfg, cfg_sref);

	/* DDR dcc training enter auto self-refresh. */
	if (ddr_training_ctrl_easr(cfg, DDR_ENTER_SREF))
		return -1;

	/* DDR dcc training compare result. */
	ddr_dcc_compare_result(dcc_data, ck_num, base_phy, gated_bypass_def, ioctl21_def);

	/* DDR dcc training exit auto self-refresh. */
	if (ddr_training_ctrl_easr(cfg, DDR_EXIT_SREF))
		return -1;

	return result;
}

#ifdef DDR_TRAINING_DEBUG
#define DDR_TRINING_BREAK_POINT(name) ddr_training_break_point(name)
#else
#define DDR_TRINING_BREAK_POINT(name)
#endif

void ddr_training_break_point(const char* name)
{
	DDR_INFO(name);
	ddr_training_console_if(0);
}

int ddr_dcc_training(struct ddr_cfg_st *cfg)
{
	int i;
	int result = 0;
	unsigned int rank_num = cfg->phy[cfg->phy_idx].rank_num;

	struct dmc_cfg_sref_st cfg_sref;
	struct ddr_timing_st timing_st;
	struct dcc_data_st dcc_st;
	struct dcc_data_st *dcc_data = &dcc_st;

	DDR_DEBUG("dram_type[%x]", cfg->phy[cfg->phy_idx].dram_type);

	DDR_DEBUG("rank num[%x]", rank_num);

	/* Save two rank DERT default result: rdq/rdqs/rdm/ bdl */
	for (i = 0; i < rank_num; i++) {
		cfg->rank_idx = i;
		ddr_save_two_rank_bdl(cfg, dcc_data);
	}

	/* Disable auto refresh */
	ddr_training_save_timing(cfg, &timing_st);

	/* Duty Correction Control training. */
	result += ddr_dcc_get_best_duty(cfg, &cfg_sref, dcc_data);

	/* Do DERT training again */
	for (i = 0; i < rank_num; i++) {
		cfg->rank_idx = i;
		dcc_data->item[i] = cfg->phy[cfg->phy_idx].rank[i].item_hw;
		cfg->phy[cfg->phy_idx].rank[i].item_hw = PHY_PHYINITCTRL_HVREFT_EN;
		DDR_DEBUG("item_hw[%x]=[%x]", i, cfg->phy[cfg->phy_idx].rank[i].item_hw);
	}

	result += ddr_hw_training_by_phy(cfg);

	for (i = 0; i < rank_num; i++) {
		cfg->rank_idx = i;
		cfg->phy[cfg->phy_idx].rank[i].item_hw = dcc_data->item[i];
	}

	/* Enable auto refresh */
	ddr_training_restore_timing(cfg, &timing_st);

	if (PHY_DRAMCFG_TYPE_LPDDR4 == cfg->phy[cfg->phy_idx].dram_type) {
		/* DCC restore DMC_CFG_SREF config. */
		ddr_restore_sref_cfg(cfg, &cfg_sref);
	}

	return result;
}

int ddr_dcc_training_func(struct ddr_cfg_st *cfg)
{
	int i;
	int result = 0;

	for (i = 0; i < cfg->phy_num; i++) {
		cfg->phy_idx = i;
		cfg->cur_phy = cfg->phy[i].addr;
		cfg->cur_item = cfg->phy[i].rank[0].item;

		if (ddr_training_check_bypass(cfg, 1 << (cfg->phy_idx)))
			continue;

		/* dpmc training disable */
		if (!ddr_training_check_bypass(cfg, DDR_BYPASS_DCC_MASK))
			result += ddr_dcc_training(cfg);
	}
	return result;
}

#else
int ddr_dcc_training_func(struct ddr_cfg_st *cfg)
{
	DDR_WARNING("Not support DCC training.");
	return 0;
}
#endif /* DDR_DCC_TRAINING_CONFIG */

#define __pcode_training__
#ifdef DDR_PCODE_TRAINING_CONFIG
/* Set pcode value to register IMPSTATUS and DDR_PHY_IMP_STATUS1 */
static void ddr_pcode_set_value(unsigned int base_phy, unsigned int pcode_value)
{
	unsigned int imp_ctrl1;

	ddr_write((ddr_read(base_phy + DDR_PHY_IMPSTATUS)
				& (~(PHY_ZCODE_PDRV_MASK << PHY_ZCODE_PDRV_BIT)))
				| (pcode_value << PHY_ZCODE_PDRV_BIT), base_phy + DDR_PHY_IMPSTATUS);
	DDR_DEBUG("cur IMPSTATUS [%x] = [%x]",
			base_phy + DDR_PHY_IMPSTATUS, ddr_read(base_phy + DDR_PHY_IMPSTATUS));

	imp_ctrl1 = ddr_read(base_phy + DDR_PHY_IMP_CTRL1);
	/* ac_vddq_cal_en set 0 */
	ddr_write(imp_ctrl1 & (~(0x1 << PHY_AC_VDDQ_CAL_EN_BIT)), base_phy + DDR_PHY_IMP_CTRL1);

	ddr_write((ddr_read(base_phy + DDR_PHY_IMP_STATUS1)
				& (~(PHY_ACCTL_PDRV_LATCH_MASK << PHY_ACCTL_PDRV_LATCH_BIT)))
				| (pcode_value << PHY_ACCTL_PDRV_LATCH_BIT), base_phy + DDR_PHY_IMP_STATUS1);
	DDR_DEBUG("cur IMP_STATUS1 [%x] = [%x]",
			base_phy + DDR_PHY_IMP_STATUS1, ddr_read(base_phy + DDR_PHY_IMP_STATUS1));

	/* restore ac_vddq_cal_en */
	ddr_write(imp_ctrl1, base_phy + DDR_PHY_IMP_CTRL1);
}

static int ddr_pcode_trainig_by_phy(struct ddr_cfg_st *cfg)
{
	unsigned int times = 0;
	unsigned int base_phy = cfg->cur_phy;
	unsigned int pcode_value;
	unsigned int osc_rpt_vld;
	unsigned int osc_cnt_rdata;
	int ddr_freq;

	/* test start */
	ddr_write(ddr_read(base_phy + DDR_PHY_CORNER_DETECTOR) | PHY_OSC_START_MASK,
					base_phy + DDR_PHY_CORNER_DETECTOR);

	do {
		osc_rpt_vld = (ddr_read(base_phy + DDR_PHY_CORNER_DETECTOR)
							>> PHY_OSC_RPT_VLD) & PHY_OSC_RPT_VLD_MASK;
		times++;
	} while ((!osc_rpt_vld)
			&& (times < DDRT_PCODE_WAIT_TIMEOUT));

	if (times >= DDRT_PCODE_WAIT_TIMEOUT) {
		DDR_FATAL("IO pcode training wait timeout.");
		return -1;
	}

	osc_cnt_rdata = (ddr_read(base_phy + DDR_PHY_CORNER_DETECTOR)
						>> PHY_OSC_CNT_RDATA_BIT)
						& PHY_OSC_CNT_RDATA_MASK;

	/* test stop */
	ddr_write(ddr_read(base_phy + DDR_PHY_CORNER_DETECTOR)
				& (~PHY_OSC_START_MASK), base_phy + DDR_PHY_CORNER_DETECTOR);

	ddr_freq = ddr_get_cksel();
	/* get pcode value */
	pcode_value = (490960 - (89 * osc_cnt_rdata * ddr_freq) / 300) / 10000;

	DDR_DEBUG("pcode value[%x]", pcode_value);
	if (pcode_value < PHY_PCODE_MIN) {
		pcode_value = PHY_PCODE_MIN;
	} else if (pcode_value > PHY_PCODE_MAX) {
		pcode_value = PHY_PCODE_MAX;
	}

	/* set pcode value */
	ddr_pcode_set_value(base_phy, pcode_value);
	return 0;
}

int ddr_pcode_training(struct ddr_cfg_st *cfg)
{
	struct tr_relate_reg relate_reg;
	int result = 0;
	int i;

	for (i = 0; i < cfg->phy_num; i++) {
		cfg->phy_idx = i;
		cfg->cur_phy = cfg->phy[i].addr;
		cfg->cur_item = cfg->phy[i].rank[0].item;

		if (ddr_training_check_bypass(cfg, 1 << (cfg->phy_idx)))
			continue;

		/* pcode training disable */
		if (ddr_training_check_bypass(cfg, DDR_BYPASS_PCODE_MASK))
			continue;

		ddr_training_save_reg(cfg, &relate_reg, DDR_BYPASS_PCODE_MASK);
		result += ddr_pcode_trainig_by_phy(cfg);
		ddr_training_restore_reg(cfg, &relate_reg);
	}

	return result;
}
#else
int ddr_pcode_training(struct ddr_cfg_st *cfg)
{
	DDR_WARNING("Not support DDR pcode training.");
	return 0;
}
#endif
