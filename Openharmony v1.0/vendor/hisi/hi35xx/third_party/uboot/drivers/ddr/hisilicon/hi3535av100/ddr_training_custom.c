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

#define CRG_REG_BASE 0x11010000U
#define PERI_CRG_DDRT 0x22A0U
#define PERI_CRG_DDRCKSEL 0x2280U

/* sysctrl offset address */
#define DDRT_CTRL 0x4030 /* DDRT control register */

/* register bit */
#define DDRTEST0_CKEN_BIT 4 /* DDRTEST0 clock gating configuration register */
#define DDRTEST0_SRST_REQ_BIT 0 /* soft reset request for DDRTEST0 */
#define DDRT0_MST_SEL_BIT 0 /* ddr p0 bus path selection control */
#define DDRT1_MST_SEL_BIT 1 /* ddr p1 bus path selection control */

/**
 * Do some prepare before copy code from DDR to SRAM.
 * Keep empty when nothing to do.
 */
void ddr_cmd_prepare_copy(void)
{
	return;
}

/**
 * Save site before DDR training command execute .
 * Keep empty when nothing to do.
 */
void ddr_cmd_site_save(void)
{
	return;
}

/**
 * Restore site after DDR training command execute.
 * Keep empty when nothing to do.
 */
void ddr_cmd_site_restore(void)
{
	return;
}

void ddr_training_save_reg_custom(void *reg, unsigned int mask)
{
	return;
}
void ddr_training_restore_reg_custom(void *reg)
{
	return;
}

/**
 * Save site before DDR training:include boot and command execute.
 * Keep empty when nothing to do.
 */
void ddr_boot_cmd_save(void *reg)
{
	struct tr_relate_reg *relate_reg = (struct tr_relate_reg *)reg;

	/* ddr bus path selection control */
	relate_reg->custom.ddr_ctrl = ddr_read(DDR_REG_BASE_SYSCTRL + DDRT_CTRL);
	ddr_write(relate_reg->custom.ddr_ctrl | (0x1 << DDRT0_MST_SEL_BIT) |
		(0x1 << DDRT1_MST_SEL_BIT), DDR_REG_BASE_SYSCTRL + DDRT_CTRL);

	/* turn on ddrt clock */
	relate_reg->custom.ddrt_clk_reg = ddr_read(CRG_REG_BASE + PERI_CRG_DDRT);
	/* enable ddrt0 clock */
	ddr_write(relate_reg->custom.ddrt_clk_reg | (0x1 << DDRTEST0_CKEN_BIT), CRG_REG_BASE + PERI_CRG_DDRT);
	__asm__ __volatile__("nop");
	/* disable ddrt0 soft reset */
	ddr_write(ddr_read(CRG_REG_BASE + PERI_CRG_DDRT) & (~(0x1 << DDRTEST0_SRST_REQ_BIT)), CRG_REG_BASE + PERI_CRG_DDRT);

	/* disable rdqs anti-aging */
	relate_reg->custom.phy0_age_compst_en = ddr_read(DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
	ddr_write((relate_reg->custom.phy0_age_compst_en & (~(0x1 << PHY_CFG_RX_AGE_COMPST_EN_BIT))),
		DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
#ifdef DDR_REG_BASE_PHY1
	relate_reg->custom.phy1_age_compst_en = ddr_read(DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
	ddr_write((relate_reg->custom.phy1_age_compst_en & (~(0x1 << PHY_CFG_RX_AGE_COMPST_EN_BIT))),
		DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
#endif
}

/**
 * Restore site after DDR training:include boot and command execute.
 * Keep empty when nothing to do.
 */
void ddr_boot_cmd_restore(void *reg)
{
	struct tr_relate_reg *relate_reg = (struct tr_relate_reg *)reg;

	/* restore ddr bus path selection */
	ddr_write(relate_reg->custom.ddr_ctrl, DDR_REG_BASE_SYSCTRL + DDRT_CTRL);
	/* restore ddrt clock */
	ddr_write(relate_reg->custom.ddrt_clk_reg, CRG_REG_BASE + PERI_CRG_DDRT);

	/* restore rdqs anti-aging */
	ddr_write(relate_reg->custom.phy0_age_compst_en, DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
#ifdef DDR_REG_BASE_PHY1
	ddr_write(relate_reg->custom.phy1_age_compst_en, DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
#endif
}

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
		freq = 24; /* 24MHz */
		break;
	case 0x001:
		freq = 450; /* 450MHz */
		break;
	case 0x011:
		freq = 300; /* 300MHz */
		break;
	case 0x100:
		freq = 297; /* 297MHz */
		break;
	default:
		freq = 300; /* 300MHz */
		break;
	}
	return freq;
}
#endif
