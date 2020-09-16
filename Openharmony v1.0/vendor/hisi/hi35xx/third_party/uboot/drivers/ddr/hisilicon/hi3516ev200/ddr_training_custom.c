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

#include "ddr_interface.h"
#include "ddr_training_impl.h"

#define CRG_REG_BASE            0x12010000U
#define PERI_CRG_DDRT           0x198U
#define PERI_CRG_DDRCKSEL       0x80U
/* [SYSCTRL]RAM Retention control register 0 */
#define SYSCTRL_MISC_CTRL4      0x8010U

static struct tr_relate_reg relate_reg;
static struct tr_relate_reg *reg = &relate_reg;

/**
 * Do some prepare before copy code from DDR to SRAM.
 * Keep empty when nothing to do.
 */
void ddr_cmd_prepare_copy(void) { return; }

/**
 * Save site before DDR training command execute .
 * Keep empty when nothing to do.
 */
void ddr_cmd_site_save(void)
{
	/* select ddrt bus path */
	reg->custom.ive_ddrt_mst_sel = ddr_read(DDR_REG_BASE_SYSCTRL + SYSCTRL_MISC_CTRL4);
	ddr_write(reg->custom.ive_ddrt_mst_sel & 0xffffffdf, DDR_REG_BASE_SYSCTRL + SYSCTRL_MISC_CTRL4);

	/* turn on ddrt clock */
	reg->custom.ddrt_clk_reg = ddr_read(CRG_REG_BASE + PERI_CRG_DDRT);
	/* enable ddrt0 clock */
	ddr_write(reg->custom.ddrt_clk_reg | (1U << 1), CRG_REG_BASE + PERI_CRG_DDRT);
	__asm__ __volatile__("nop");
	/* disable ddrt0 soft reset */
	ddr_write(ddr_read(CRG_REG_BASE + PERI_CRG_DDRT) & (~(1U << 0)), CRG_REG_BASE + PERI_CRG_DDRT);

	/* disable rdqs anti-aging */
	reg->custom.phy0_age_compst_en = ddr_read(DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
	ddr_write((reg->custom.phy0_age_compst_en & 0x7fffffff), DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
#ifdef DDR_REG_BASE_PHY1
	reg->custom.phy1_age_compst_en = ddr_read(DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
	ddr_write((reg->custom.phy1_age_compst_en & 0x7fffffff), DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
#endif
}

/**
 * Restore site after DDR training command execute.
 * Keep empty when nothing to do.
 */
void ddr_cmd_site_restore(void)
{
	/* restore ddrt bus path */
	ddr_write(reg->custom.ive_ddrt_mst_sel, DDR_REG_BASE_SYSCTRL + SYSCTRL_MISC_CTRL4);

	/* restore ddrt clock */
	ddr_write(reg->custom.ddrt_clk_reg, CRG_REG_BASE + PERI_CRG_DDRT);

	/* restore rdqs anti-aging */
	ddr_write(reg->custom.phy0_age_compst_en, DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
#ifdef DDR_REG_BASE_PHY1
	ddr_write(reg->custom.phy1_age_compst_en, DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
#endif
}

void ddr_training_save_reg_custom(void *reg, unsigned int mask) { return; }
void ddr_training_restore_reg_custom(void *reg) { return; }

/**
 * DDR clock select.
 * For ddr osc training.
 */
#ifdef DDR_PCODE_TRAINING_CONFIG
int ddr_get_cksel(void)
{
	int freq;
	unsigned int ddr_cksel;
	ddr_cksel = (ddr_read(CRG_REG_BASE + PERI_CRG_DDRCKSEL) >> 0x3) & 0x7;
	switch (ddr_cksel) {
	case 0x000:
		/* 24MHz */
		freq = 24;
		break;
	case 0x001:
		/* 450MHz */
		freq = 450;
		break;
	case 0x011:
		/* 300MHz */
		freq = 300;
		break;
	case 0x100:
		/* 297MHz */
		freq = 297;
		break;
	default:
		freq = 300;
		break;
	}
	return freq;
}
#endif
