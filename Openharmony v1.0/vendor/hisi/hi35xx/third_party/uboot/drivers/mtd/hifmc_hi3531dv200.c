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

#define REG_IO_BASE_FMC 0x10ff0000

/* configure io for SPI interface
 * SPI NOR/SPI NAND 3V3 SDR
 *  Signal   |  Register   |   Value    | Level
 *  CLK      | 0x10FF0024  | 0x000002d1 |   3
 *  MOSI_IO0 | 0x10FF001C  | 0x000000d1 |   3
 *  MISO_IO1 | 0x10FF0028  | 0x000000d1	|   3
 *  WP_IO2   | 0x10FF0020  | 0x000000d1	|   3
 *  HOLD_IO3 | 0x10FF002C  | 0x000000d1	|   3
 *  SFC_CS0N | 0x10FF0030  | 0x00000031 |   1
 *  SFC_CS1N | 0x10FF0034  | 0x00000031 |   1
 */
#define REG_SPI_CLK		(REG_IO_BASE_FMC + 0x24)
#define REG_SPI_MOSI_IO0	(REG_IO_BASE_FMC + 0x1C)
#define REG_SPI_MISO_IO1	(REG_IO_BASE_FMC + 0x28)
#define REG_SPI_WP_IO2		(REG_IO_BASE_FMC + 0x20)
#define REG_SPI_HOLD_IO3	(REG_IO_BASE_FMC + 0x2c)
#define REG_SFC_CS0N		(REG_IO_BASE_FMC + 0x30)
#define REG_SFC_CS1N		(REG_IO_BASE_FMC + 0x34)

#define SPI_CLK_VAL		0x000002d1
#define SPI_MOSI_IO0_VAL	0x000000d1
#define SPI_MISO_IO1_VAL	0x000000d1
#define SPI_WP_IO2_VAL		0x000000d1
#define SPI_HOLD_IO3_VAL	0x000000d1
#define SPI_SFC_CS0N_VAL	0x00000031
#define SPI_SFC_CS1N_VAL	0x00000031

static void hi3531dv200_spi_io_config(void)
{
	static unsigned int io_config_flag = 1;

	if (!io_config_flag)
		return;

	writel(SPI_CLK_VAL, REG_SPI_CLK);
	writel(SPI_MOSI_IO0_VAL, REG_SPI_MOSI_IO0);
	writel(SPI_MISO_IO1_VAL, REG_SPI_MISO_IO1);
	writel(SPI_WP_IO2_VAL, REG_SPI_WP_IO2);
	writel(SPI_HOLD_IO3_VAL, REG_SPI_HOLD_IO3);
	writel(SPI_SFC_CS0N_VAL, REG_SFC_CS0N);
	writel(SPI_SFC_CS1N_VAL, REG_SFC_CS1N);

	io_config_flag = 0;
}

/*****************************************************************************/
void hifmc_set_fmc_system_clock(struct spi_op *op, int clk_en)
{
	unsigned int old_val, regval;

	old_val = regval = readl(CRG_REG_BASE + REG_FMC_CRG);

	regval &= ~FMC_CLK_SEL_MASK;

	if (op && op->clock) {
		regval |= op->clock & FMC_CLK_SEL_MASK;
		fmc_pr(DTR_DB, "\t|||*-get the setting clock value: %#x\n",
				op->clock);
	} else {
		regval |= fmc_clk_sel(FMC_CLK_24M);	/* Default Clock */
		hi3531dv200_spi_io_config();
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
	unsigned int clk_reg, clk_type;
	const char *str[] = {"12", "37.5", "62.5", "75", "100"};

#define CLK_2X(_clk)	(((_clk) + 1) >> 1)
	unsigned int sys_2X_clk[] = {
		CLK_2X(24),	fmc_clk_sel(FMC_CLK_24M),
		CLK_2X(100),	fmc_clk_sel(FMC_CLK_100M),
		CLK_2X(150),	fmc_clk_sel(FMC_CLK_150M),
		CLK_2X(200),	fmc_clk_sel(FMC_CLK_200M),
		0,		0,
	};
#undef CLK_2X

	clk_type = FMC_CLK_24M;
	clk_reg = fmc_clk_sel(clk_type);
	fmc_pr(QE_DBG, "\t|||*-matching flash clock %d\n", *clock);
	for (ix = 0; sys_2X_clk[ix]; ix += 2) {
		if (*clock < sys_2X_clk[ix])
			break;
		clk_reg = sys_2X_clk[ix + 1];
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
	unsigned int clk_reg, clk_type;
	char *const str[] = {"6", "9.25", "31.25", "37.5", "50",
		"62.5", "75", "100"};

#define CLK_4X(_clk)	(((_clk) + 1) >> 2)
	unsigned int sys_4X_clk[] = {
		CLK_4X(24),	fmc_clk_sel(FMC_CLK_24M),
		CLK_4X(100),	fmc_clk_sel(FMC_CLK_100M),
		CLK_4X(150),	fmc_clk_sel(FMC_CLK_150M),
		CLK_4X(200),	fmc_clk_sel(FMC_CLK_200M),
		CLK_4X(300),	fmc_clk_sel(FMC_CLK_300M),
		CLK_4X(400),	fmc_clk_sel(FMC_CLK_400M),
		0,		0,
	};
#undef CLK_4X
	clk_type = FMC_CLK_24M;
	clk_reg = fmc_clk_sel(clk_type);
	fmc_pr(DTR_DB, "\t|||*-matching flash clock %d\n", *clock);
	for (ix = 0; sys_4X_clk[ix]; ix += 2) {
		if (*clock < sys_4X_clk[ix])
			break;
		clk_reg = sys_4X_clk[ix + 1];
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
