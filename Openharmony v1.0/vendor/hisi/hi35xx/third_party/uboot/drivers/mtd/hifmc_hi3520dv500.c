/*
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

#define REG_IO_BASE_FMC HP_IO_CONFIG_REG_BASE

/* SFC_IOCFG */
#define SFC_MOSI_IO_0_REG		0xec
#define SFC_WP_IO_2_REG			0xf0
#define SFC_CLK_REG		        0xe8
#define SFC_MISO_IO_1_REG		0xe0
#define SFC_HOLD_IO_3_REG		0xe4
#define SFC_CS_0_N_REG			0xf4

static void hi3520dv500_io_config_spi_sfc(void)
{
    /* set pad ctrl reg for spi */
    writel(0xc0, REG_IO_BASE_FMC + SFC_MOSI_IO_0_REG);    /* sfc_mosi_io0 */
    writel(0xc0, REG_IO_BASE_FMC + SFC_WP_IO_2_REG);      /* sfc_wp_io2 */
    writel(0x2b0, REG_IO_BASE_FMC + SFC_CLK_REG);		  /* sfc_clk */
    writel(0xc0, REG_IO_BASE_FMC + SFC_MISO_IO_1_REG);    /* sfc_miso_io1 */
    writel(0xc0, REG_IO_BASE_FMC + SFC_HOLD_IO_3_REG);    /* sfc_hold_io3 */
    writel(0x60, REG_IO_BASE_FMC + SFC_CS_0_N_REG);		  /* sfc_cs0n */
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
		hi3520dv500_io_config_spi_sfc();
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
	const char *str[] = {"12", "50", "75", "100"};

	unsigned int sys_2x_clk[] = {
		clk_2x(24), fmc_clk_sel(FMC_CLK_24M),
		clk_2x(100), fmc_clk_sel(FMC_CLK_100M),
		clk_2x(150), fmc_clk_sel(FMC_CLK_150M),
		clk_2x(200), fmc_clk_sel(FMC_CLK_200M),
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
	char *const str[] = {"6", "25", "37.5", "50", "75", "100"};

	unsigned int sys_4x_clk[] = {
		clk_4x(24), fmc_clk_sel(FMC_CLK_24M),
		clk_4x(100), fmc_clk_sel(FMC_CLK_100M),
		clk_4x(150), fmc_clk_sel(FMC_CLK_150M),
		clk_4x(200), fmc_clk_sel(FMC_CLK_200M),
		/* TODO 250M */
		clk_4x(300), fmc_clk_sel(FMC_CLK_300M),
		clk_4x(400), fmc_clk_sel(FMC_CLK_400M),
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
