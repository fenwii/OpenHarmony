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

 * Description:DDR training control
 */

#include "ddr_interface.h"
#include "ddr_training_impl.h"

#ifdef DDR_SW_TRAINING_FUNC_PUBLIC
#ifdef DDR_TRAINING_CUT_CODE_CONFIG
/**
 * Cut ddr training control code for less SRAM.
 * Support DDRC500.
 * Support DDRC510 with one PHY.
 */
int ddr_sw_training_func(void)
{
	struct ddr_cfg_st ddr_cfg;
	struct ddr_cfg_st *cfg = &ddr_cfg;

	unsigned int base_dmc = DDR_REG_BASE_DMC0;
	unsigned int base_phy = DDR_REG_BASE_PHY0;
	int result = 0;
	unsigned int auto_ref_timing = ddr_read(base_dmc + DDR_DMC_TIMING2);
	unsigned int misc_scramb = ddr_read(base_phy + DDR_PHY_MISC);
	unsigned int dramcfg_ma2t = ddr_read(base_phy + DDR_PHY_DRAMCFG)
		& PHY_DRAMCFG_MA2T;
	unsigned int acphyctl;

	/* Static register have to read two times to get the right value. */
	acphyctl = ddr_read(base_phy + DDR_PHY_ACPHYCTL4);
	acphyctl = ddr_read(base_phy + DDR_PHY_ACPHYCTL4);

	DDR_VARIABLE_DECLARE(swapdfibyte_en);

	/* check sw ddr training enable */
	if (DDR_BYPASS_ALL_MASK == ddr_read(DDR_REG_BASE_SYSCTRL
		+ SYSCTRL_DDR_TRAINING_CFG))
		return 0;

	ddr_training_start();
	ddr_training_cfg_init(cfg);

#ifdef DDR_TRAINING_STAT_CONFIG
	/* clear stat register */
	ddr_write(0x0, DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_STAT);
#endif

	/* disable scramb */
	ddr_write(misc_scramb & PHY_MISC_SCRAMB_DIS,
		base_phy + DDR_PHY_MISC);

	/* disable rdqs swap */
	DDR_DQSSWAP_SAVE_FUNC(swapdfibyte_en, base_phy);

	/* check hardware gating */
	if (ddr_read(base_phy + DDR_PHY_PHYINITSTATUS)
		& PHY_INITSTATUS_GT_MASK) {
		DDR_FATAL("PHY[%x] hw gating fail.", base_phy);
		ddr_training_stat(DDR_ERR_HW_GATING,
			base_phy, -1, -1);
	}

#ifdef DDR_LPCA_TRAINING_CONFIG
	/* lpca */
	if (!ddr_training_check_bypass(cfg, DDR_BYPASS_LPCA_MASK)
		&& (PHY_DRAMCFG_TYPE_LPDDR3 ==
		(ddr_read(base_phy + DDR_PHY_DRAMCFG)
		& PHY_DRAMCFG_TYPE_LPDDR3))) {
		/* disable auto refresh */
		ddr_training_set_timing(base_dmc,
			auto_ref_timing & DMC_AUTO_TIMING_DIS);

		result += ddr_lpca_training(cfg);

		/* enable auto refresh */
		ddr_training_set_timing(base_dmc, auto_ref_timing);
	}
#endif

#ifdef DDR_WL_TRAINING_CONFIG
	/* write leveling */
	if (!ddr_training_check_bypass(cfg, DDR_BYPASS_WL_MASK)) {
		/* disable auto refresh */
		ddr_training_set_timing(base_dmc,
			auto_ref_timing & DMC_AUTO_TIMING_DIS);
		result += ddr_write_leveling(cfg);
		/* enable auto refresh */
		ddr_training_set_timing(base_dmc, auto_ref_timing);
	}
#endif

#ifdef DDR_DATAEYE_TRAINING_CONFIG
	/* dataeye */
	if (!ddr_training_check_bypass(cfg, DDR_BYPASS_DATAEYE_MASK)) {
		ddr_training_switch_axi(cfg);
		ddr_ddrt_init(cfg, DDR_DDRT_MODE_DATAEYE);
		result += ddr_dataeye_training(cfg);
	}
#endif

#ifdef DDR_HW_TRAINING_CONFIG
	/* hardware read */
	if (result && !ddr_training_check_bypass(cfg, DDR_BYPASS_HW_MASK)) {
		if (!dramcfg_ma2t) /* set 1T */
			ddr_write(0x0, base_phy + DDR_PHY_ACPHYCTL4);

		result = ddr_hw_dataeye_read(cfg);
		if (!dramcfg_ma2t) /* restore */
			ddr_write(acphyctl, base_phy + DDR_PHY_ACPHYCTL4);

		result += ddr_dataeye_training(cfg);
	}
#endif

#ifdef DDR_MPR_TRAINING_CONFIG
	/* mpr */
	if (result && !ddr_training_check_bypass(cfg, DDR_BYPASS_MPR_MASK)) {
		result = ddr_mpr_training(cfg);
		result += ddr_dataeye_training(cfg);
	}
#endif

#ifdef DDR_GATE_TRAINING_CONFIG
	/* gate */
	if (!ddr_training_check_bypass(cfg, DDR_BYPASS_GATE_MASK)) {
		ddr_training_switch_axi(cfg);
		ddr_ddrt_init(cfg, DDR_DDRT_MODE_GATE);
		/* disable auto refresh */
		ddr_training_set_timing(base_dmc,
			auto_ref_timing & DMC_AUTO_TIMING_DIS);

		if (!dramcfg_ma2t) /* set 1T */
			ddr_write(0x0, base_phy + DDR_PHY_ACPHYCTL4);

		result += ddr_gate_training(cfg);

		/* enable auto refresh */
		ddr_training_set_timing(base_dmc, auto_ref_timing);

		if (!dramcfg_ma2t) /* restore */
			ddr_write(acphyctl, base_phy + DDR_PHY_ACPHYCTL4);
	}
#endif

#ifdef DDR_VREF_TRAINING_CONFIG
	if (!ddr_training_check_bypass(cfg, DDR_BYPASS_VREF_MASK)) {
		ddr_training_switch_axi(cfg);
		ddr_ddrt_init(cfg, DDR_DDRT_MODE_DATAEYE);
		result += ddr_vref_training(cfg);
	}
#endif

	/* restore scramb */
	ddr_write(misc_scramb, base_phy + DDR_PHY_MISC);

	/* restore rdqs swap */
	DDR_DQSSWAP_RESTORE_FUNC(swapdfibyte_en, base_phy);

	if (!result)
		ddr_training_suc();
	return result;
}
#else
int ddr_training_boot_func(struct ddr_cfg_st *cfg)
{
	int result = 0;

	/* check hardware gating */
	if (ddr_read(cfg->cur_phy + DDR_PHY_PHYINITSTATUS)
		& PHY_INITSTATUS_GT_MASK) {
		DDR_FATAL("PHY[%x] hw gating fail.", cfg->cur_phy);
		ddr_training_stat(DDR_ERR_HW_GATING,
			cfg->cur_phy, -1, -1);
	}

	/* lpca */
	result = ddr_lpca_training_func(cfg);
	/* write leveling */
	result += ddr_wl_func(cfg);
	/* dataeye/gate/vref need switch axi */
	/* dataeye */
	result += ddr_dataeye_training_func(cfg);
#ifdef DDR_HW_TRAINING_CONFIG
	/* hardware read */
	if (result && !ddr_training_check_bypass(cfg, DDR_BYPASS_HW_MASK)) {
		struct tr_relate_reg relate_reg_ac;
		ddr_training_save_reg(cfg, &relate_reg_ac,
			DDR_BYPASS_HW_MASK);
		result = ddr_hw_dataeye_read(cfg);
		ddr_training_restore_reg(cfg, &relate_reg_ac);
		cfg->adjust = DDR_DATAEYE_ABNORMAL_ADJUST;
		result += ddr_dataeye_training(cfg);
	}
#endif
	/* mpr */
	result += ddr_mpr_training_func(cfg);
	/* gate */
	result += ddr_gating_func(cfg);
	/* vref */
	result += ddr_vref_training_func(cfg);

	return result;
}

/* Support DDRC510 with two PHY */
int ddr_sw_training_func(void)
{
	struct ddr_cfg_st ddr_cfg;
	struct ddr_cfg_st *cfg = &ddr_cfg;
	struct tr_relate_reg reg;
	int result = 0;

#ifdef SYSCTRL_DDR_TRAINING_VERSION_FLAG
	/* DDR training version flag */
	unsigned int tmp_reg = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_VERSION_FLAG);
	tmp_reg = (tmp_reg & 0xffff0000) | DDR_VERSION;
	ddr_write(tmp_reg, DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_VERSION_FLAG);
#endif

	/* check sw ddr training enable */
	if (DDR_BYPASS_ALL_MASK == ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG)
#ifdef SYSCTRL_DDR_TRAINING_CFG_SEC
	&& DDR_BYPASS_ALL_MASK == ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG_SEC)
#endif
	)
		return 0;

	ddr_training_start();

	/* save customer reg */
	ddr_boot_cmd_save_func(&reg);

#ifdef DDR_TRAINING_STAT_CONFIG
	/* clear stat register */
	ddr_write(0x0, DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_STAT);
#endif

	ddr_training_cfg_init(cfg);
	cfg->cmd_st = 0;

	result = ddr_training_all(cfg);
	result += ddr_dcc_training_func(cfg);

	if (!result)
		ddr_training_suc();
	else
		ddr_training_console_if(0);

	/* restore customer reg */
	ddr_boot_cmd_restore_func(&reg);

	return result;
}
#endif /* DDR_TRAINING_CUT_CODE_CONFIG */
#endif /* DDR_SW_TRAINING_FUNC_PUBLIC */

#ifdef DDR_PCODE_TRAINING_CONFIG
int ddr_pcode_training_func(void)
{
	struct ddr_cfg_st ddr_cfg;
	struct ddr_cfg_st *cfg = &ddr_cfg;

	ddr_training_cfg_init(cfg);
	return ddr_pcode_training(cfg);
}
#else
int ddr_pcode_training_func(void)
{
	DDR_WARNING("Not support DDR pcode training.");
	return 0;
}
#endif

#ifdef DDR_HW_TRAINING_CONFIG
int ddr_hw_training_func(void)
{
	struct ddr_cfg_st ddr_cfg;
	struct ddr_cfg_st *cfg = &ddr_cfg;

	ddr_training_cfg_init(cfg);
	return ddr_hw_training(cfg);
}
#else
int ddr_hw_training_func(void)
{
	DDR_WARNING("Not support DDR HW training.");
	return 0;
}
#endif /* DDR_HW_TRAINING_CONFIG */

int ddr_sw_training_if(void)
{
	return DDR_SW_TRAINING_FUNC();
}

int ddr_hw_training_if(void)
{
	return DDR_HW_TRAINING_FUNC();
}

int ddr_pcode_training_if(void)
{
	return DDR_PCODE_TRAINING_FUNC();
}

