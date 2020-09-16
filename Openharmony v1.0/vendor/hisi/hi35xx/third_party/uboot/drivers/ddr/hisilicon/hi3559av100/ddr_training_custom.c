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

#define CRG_REG_BASE 0x12010000U
#define PERI_CRG83   0x14CU

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
	unsigned int ddrt_clk_reg;

	/* turn on ddrt clock */
	ddrt_clk_reg = ddr_read(CRG_REG_BASE + PERI_CRG83);
	ddrt_clk_reg |= (1U << 1);	/* enable ddrt0 clock */
	ddr_write(ddrt_clk_reg, CRG_REG_BASE + PERI_CRG83);
	__asm__ __volatile__("nop");
	ddrt_clk_reg = ddr_read(CRG_REG_BASE + PERI_CRG83);
	ddrt_clk_reg &= ~(1U << 0);	/* disable ddrt0 soft reset */
	ddr_write(ddrt_clk_reg, CRG_REG_BASE + PERI_CRG83);
}

/**
 * Restore site after DDR training command execute.
 * Keep empty when nothing to do.
 */
void ddr_cmd_site_restore(void)
{
	unsigned int ddrt_clk_reg;

	/* turn off ddrt clock */
	ddrt_clk_reg = ddr_read(CRG_REG_BASE + PERI_CRG83);
	ddrt_clk_reg |= (1U << 0);	/* eable ddrt0 soft reset */
	ddr_write(ddrt_clk_reg, CRG_REG_BASE + PERI_CRG83);
	__asm__ __volatile__("nop");
	ddrt_clk_reg = ddr_read(CRG_REG_BASE + PERI_CRG83);
	ddrt_clk_reg &= ~(1U << 1);	/* disable ddrt0 clock */
	ddr_write(ddrt_clk_reg, CRG_REG_BASE + PERI_CRG83);
}

void ddr_training_save_reg_custom(void *reg, unsigned int mask) { return; }
void ddr_training_restore_reg_custom(void *reg) { return; }