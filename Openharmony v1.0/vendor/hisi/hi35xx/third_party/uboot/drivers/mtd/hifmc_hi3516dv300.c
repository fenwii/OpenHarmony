/*
 * hifmc_hi3516dv300.c
 *
 * The Flash Memory Controller v100 Device Driver for hisilicon
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

#include <common.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include <hifmc_common.h>

#include "hifmc_spi_ids.h"

#define REG_IO_BASE 0x10ff0000
static void hi3516dv300_spi_io_config(void)
{
	/* set pad ctrl reg for spi */
	writel(0x6a1, REG_IO_BASE + 0x0);   /* sfc_clk */
	writel(0x4e1, REG_IO_BASE + 0x4);   /* sfc_mosi_io3 */
	writel(0x4e1, REG_IO_BASE + 0x8);   /* sfc_wp_io2 */
	writel(0x4e1, REG_IO_BASE + 0xc);   /* sfc_miso_io1 */
	writel(0x5e1, REG_IO_BASE + 0x10);  /* sfc_csn */
	writel(0x4e1, REG_IO_BASE + 0x14);  /* sfc_hold_io0 */
}

/*****************************************************************************/
void hifmc_set_fmc_system_clock(struct spi_op *op, int clk_en)
{
	unsigned int old_val;
	unsigned int regval;

	old_val = regval = readl(CRG_REG_BASE + REG_FMC_CRG);

	regval &= ~FMC_CLK_SEL_MASK;

	if (op && op->clock) {
		regval |= op->clock & FMC_CLK_SEL_MASK;
		fmc_pr(DTR_DB, "\t|||*-get the setting clock value: %#x\n",
			op->clock);
	} else {
		regval |= fmc_clk_sel(FMC_CLK_24M); /* Default Clock */
		hi3516dv300_spi_io_config();
	}
	if (clk_en)
		regval |= FMC_CLK_ENABLE;
	else
		regval &= ~FMC_CLK_ENABLE;

	if (regval != old_val) {
		fmc_pr(DTR_DB, "\t|||*-setting system clock [%#x]%#x\n",
			REG_FMC_CRG, regval);
		writel(regval, (CRG_REG_BASE + REG_FMC_CRG));
	}
}

/*****************************************************************************/
void hifmc_get_fmc_best_2x_clock(unsigned int *clock)
{
	int ix;
	unsigned int clk_reg;
	unsigned int clk_type;
	const char *str[] = {"12", "50", "75", "81.5", "100", "128.5"};

	unsigned int sys_2x_clk[] = {
		clk_2x(24), fmc_clk_sel(FMC_CLK_24M),
		clk_2x(100), fmc_clk_sel(FMC_CLK_100M),
		clk_2x(150), fmc_clk_sel(FMC_CLK_150M),
		clk_2x(163), fmc_clk_sel(FMC_CLK_163M),
		clk_2x(200), fmc_clk_sel(FMC_CLK_200M),
		clk_2x(257), fmc_clk_sel(FMC_CLK_257M),
		0,      0,
	};

	clk_type = FMC_CLK_24M;
	clk_reg = fmc_clk_sel(clk_type);
	fmc_pr(QE_DBG, "\t|||*-matching flash clock %d\n", *clock);
	for (ix = 0; sys_2x_clk[ix]; ix += _2B) {
		if (*clock < sys_2x_clk[ix])
			break;
		clk_reg = sys_2x_clk[ix + 1];
		clk_type = get_fmc_clk_type(clk_reg);
		fmc_pr(QE_DBG, "\t||||-select system clock: %sMHz\n",
			str[clk_type]);
	}
#ifdef CONFIG_DTR_MODE_SUPPORT
	fmc_pr(DTR_DB, "best system clock for SDR.\n");
#endif
	fmc_pr(QE_DBG, "\t|||*-matched best system clock: %sMHz\n",
		str[clk_type]);
	*clock = clk_reg;
}

#ifdef CONFIG_DTR_MODE_SUPPORT
/*****************************************************************************/
void hifmc_get_fmc_best_4x_clock(unsigned int *clock)
{
	int ix;
	unsigned int clk_reg;
	unsigned int clk_type;
	char *const str[] = {"6", "25", "37.5", "40.75", "50", "64.25", "75", "99"};

	unsigned int sys_4x_clk[] = {
		clk_4x(24), fmc_clk_sel(FMC_CLK_24M),
		clk_4x(100), fmc_clk_sel(FMC_CLK_100M),
		clk_4x(150), fmc_clk_sel(FMC_CLK_150M),
		clk_4x(163), fmc_clk_sel(FMC_CLK_163M),
		clk_4x(200), fmc_clk_sel(FMC_CLK_200M),
		clk_4x(257), fmc_clk_sel(FMC_CLK_257M),
		clk_4x(300), fmc_clk_sel(FMC_CLK_300M),
		clk_4x(396), fmc_clk_sel(FMC_CLK_396M),
		0,      0,
	};

	clk_type = FMC_CLK_24M;
	clk_reg = fmc_clk_sel(clk_type);
	fmc_pr(DTR_DB, "\t|||*-matching flash clock %d\n", *clock);
	for (ix = 0; sys_4x_clk[ix]; ix += _2B) {
		if (*clock < sys_4x_clk[ix])
			break;
		clk_reg = sys_4x_clk[ix + 1];
		clk_type = get_fmc_clk_type(clk_reg);
		fmc_pr(DTR_DB, "\t||||-select system clock: %sMHz\n",
			str[clk_type]);
	}
	fmc_pr(DTR_DB, "best system clock for DTR.\n");
	fmc_pr(DTR_DB, "\t|||*-matched best system clock: %sMHz\n",
		str[clk_type]);
	*clock = clk_reg;
}
/*****************************************************************************/
#endif/* CONFIG_DTR_MODE_SUPPORT */
