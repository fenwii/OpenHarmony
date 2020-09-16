/*
 * hifmc_hi3519av100.c
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

/* This define just for Padctrl, PHY and DC configuration
 * of nand flash */
#define REG_BASE_MISC       0x04528000
#define PHY_INIT_EN         0x1
#define PHY_ZCAL_EN         (0x1 << 3)

#define EMMC_PHY_IOCTL_RONSEL_1_0   (EMMC_PHY_BASE + 0x264)
#define EMMC_PHY_IOCTL_OD_RONSEL_2  (EMMC_PHY_BASE + 0x268)

#define REG_IO_CFG_0_BASE   0x04058000
#define IO_CFG_REG46            0xb8
#define IO_CFG_REG47            0xbc
#define IO_CFG_REG48            0xc0

static void hi3519av100_nand_io_config(void)
{
	writel(0x7ff, EMMC_PHY_IOCTL_RONSEL_1_0);
	writel(0x7ff, EMMC_PHY_IOCTL_OD_RONSEL_2);
	writel(0x451, REG_IO_CFG_0_BASE + IO_CFG_REG46);
	writel(0x451, REG_IO_CFG_0_BASE + IO_CFG_REG47);
	writel(0x451, REG_IO_CFG_0_BASE + IO_CFG_REG48);
}

/*****************************************************************************/
void hifmc100_nand_controller_enable(int enable)
{
	unsigned int old_val;
	unsigned int regval;

	old_val = regval = readl(CRG_REG_BASE + REG_FMC_CRG);

	regval &= ~FMC_CLK_SEL_MASK;
	regval |= fmc_clk_sel(FMC_CLK_200M);

	if (enable)
		regval |= FMC_CLK_ENABLE;
	else
		regval &= ~FMC_CLK_ENABLE;

	regval &= ~FMC_SOFT_RST_REQ;
	if (regval != old_val)
		writel(regval, (CRG_REG_BASE + REG_FMC_CRG));

	hi3519av100_nand_io_config();
}

/* configure io for spi controller, just for hi3519av100 */
static void hi3519av100_spi_io_config(void)
{
	writel(0x4f0, EMMC_PHY_IOCTL_RONSEL_1_0);
	writel(0x4f0, EMMC_PHY_IOCTL_OD_RONSEL_2);
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
		hi3519av100_spi_io_config();
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
	const char *str[] = {"12", "37.5", "62.5", "75", "100"};

	unsigned int sys_2x_clk[] = {
		clk_2x(24), fmc_clk_sel(FMC_CLK_24M),
		clk_2x(75), fmc_clk_sel(FMC_CLK_75M),
		clk_2x(125), fmc_clk_sel(FMC_CLK_125M),
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
	char *const str[] = {"6", "9.25", "31.25", "37.5", "50",
				"62.5", "75", "100" };
	unsigned int sys_4x_clk[] = {
		clk_4x(24), fmc_clk_sel(FMC_CLK_24M),
		clk_4x(75), fmc_clk_sel(FMC_CLK_75M),
		clk_4x(125), fmc_clk_sel(FMC_CLK_125M),
		clk_4x(150), fmc_clk_sel(FMC_CLK_150M),
		clk_4x(200), fmc_clk_sel(FMC_CLK_200M),
		clk_4x(250), fmc_clk_sel(FMC_CLK_250M),
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
