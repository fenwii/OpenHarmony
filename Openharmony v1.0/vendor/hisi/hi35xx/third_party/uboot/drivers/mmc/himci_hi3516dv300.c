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

#define REG_CRG82   0x0148
#define EMMC_CRG    REG_CRG82
#define EMMC_SRST   (1<<0)
#define EMMC_CLK_EN (1<<1)
#define EMMC_CLK_SEL_MASK   (0x3<<2)
#define EMMC_CLK_SEL_50M    0x2
#define EMMC_CLK_SEL_100M    0x1
#define EMMC_CLK_SEL_150M    0x0
#define EMMC_CLK_SEL_SHIFT  0x2

#define HIMCI_PHASE_SCALE       8

#define REG_CRG88   0x0160
#define SDIO0_CRG    REG_CRG88
#define SDIO0_SRST   (1<<0)
#define SDIO0_CLK_EN (1<<1)
#define SDIO0_CLK_SEL_MASK   (0x3<<2)
#define SDIO0_CLK_SEL_50M    0x2
#define SDIO0_CLK_SEL_SHIFT  0x2

/* eMMC pad ctrl reg */
#define REG_CTRL_EMMC_START     (0x10ff0000 + 0x0)
/* sdio0 pad ctrl reg */
#define REG_CTRL_SDIO0_START	(0x10ff0000 + 0x24)

static unsigned int pad_ctrl_start[] = {REG_CTRL_EMMC_START, REG_CTRL_SDIO0_START};

					/* clk   cmd   data0  data1  data2  data3 */
static unsigned int emmc_hs200_drv[] = {0x2b0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0};
static unsigned int emmc_hs_drv[] = {0x6b0, 0x5e0, 0x5e0, 0x5e0, 0x5e0, 0x5e0};
static unsigned int emmc_ds_drv[] = {0x6b0, 0x5f0, 0x5f0, 0x5f0, 0x5f0, 0x5f0};
//static unsigned int emmc_ds_400k_drv[] = {0x6c0, 0x5f0, 0x5f0, 0x5f0, 0x5f0, 0x5f0};

//static unsigned int sdio0_sdr104_drv[] = {0x250, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0};
//static unsigned int sdio0_sdr50_drv[] = {0x250, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0};
//static unsigned int sdio0_sdr25_drv[] = {0x650, 0x5d0, 0x5d0, 0x5d0, 0x5d0, 0x5d0};
//static unsigned int sdio0_sdr12_drv[] = {0x650, 0x5e0, 0x5e0, 0x5e0, 0x5e0, 0x5e0};
static unsigned int sdio0_hs_drv[] = {0x6d0, 0x5f0, 0x5f0, 0x5f0, 0x5f0, 0x5f0};
//static unsigned int sdio0_ds_drv[] = {0x650, 0x5e0, 0x5e0, 0x5e0, 0x5e0, 0x5e0};

static void hi_mci_set_drv_cap(struct mmc *mmc, unsigned int vdd)
{
	unsigned int i, j, start;
	unsigned int *pin_drv_cap = NULL;

	if (mmc->selected_mode == MMC_HS)
		pin_drv_cap = emmc_hs_drv;
	else if (mmc->selected_mode == MMC_HS_200)
		pin_drv_cap = emmc_hs200_drv;
	else
		pin_drv_cap = emmc_ds_drv;

	start = REG_CTRL_EMMC_START;

	for (i = start, j = 0; j < 6; i = i+4, j++) {
		unsigned int reg = himci_readl(i);
		/*
		 * [10]:SR
		 * [9]:internel pull down
		 * [8]:internel pull up
		 * [7:4]:
		 * */
		reg = reg & (~(0x7f0));
		reg |= pin_drv_cap[j];
		himci_writel(reg, i);
	}
}

#define DRV_PHASE_180   (0x4<<23)
#define DRV_PHASE_135   (0x3<<23)
#define DRV_PHASE_90    (0x2<<23)

#define SMP_PHASE_45    (0x1<<16)
#define SMP_PHASE_0     (0x0<<16)

static void hi_mci_set_default_phase(struct mmc *mmc)
{
	struct himci_host *host = mmc->priv;
	unsigned int phase_cfg = 0;
    unsigned int reg_value;
    if (host->base == EMMC_REG_BASE) {
        if (mmc->selected_mode == MMC_HS)
            phase_cfg = DRV_PHASE_180 | SMP_PHASE_45;
        else if (mmc->selected_mode == MMC_HS_200)
            phase_cfg = DRV_PHASE_135 | SMP_PHASE_0;
        else
            phase_cfg = DRV_PHASE_180 | SMP_PHASE_0;
    }
    if (host->base == SDIO0_REG_BASE) {
        phase_cfg = DRV_PHASE_135 | SMP_PHASE_45;
    }
	reg_value = himci_readl(host->base + MCI_UHS_REG_EXT);
	reg_value &= ~CLK_SMPL_PHS_MASK;
	reg_value &= ~CLK_DRV_PHS_MASK;
	reg_value |= phase_cfg;
	himci_writel(reg_value, host->base + MCI_UHS_REG_EXT);
}

extern void udelay(unsigned long usec);
static void hi_mci_sys_init(unsigned int dev_num, unsigned int freq)
{
	unsigned int tmp_reg;
    unsigned int *pin_drv_cap = NULL;
    unsigned int i,j,start;

	HIMCI_DEBUG_FUN("Function Call");

	if (dev_num == 1) {
		/* SDIO0 clock */
		tmp_reg = himci_readl(CRG_REG_BASE + SDIO0_CRG);
		tmp_reg &= ~SDIO0_CLK_SEL_MASK;
		tmp_reg |= SDIO0_CLK_SEL_50M << SDIO0_CLK_SEL_SHIFT;
		himci_writel(tmp_reg, CRG_REG_BASE + SDIO0_CRG);

		/* SDIO0 soft reset */
		tmp_reg |= SDIO0_SRST;
		himci_writel(tmp_reg, CRG_REG_BASE + SDIO0_CRG);
		udelay(100);
		tmp_reg &= ~SDIO0_SRST;
		tmp_reg |= SDIO0_CLK_EN;
		himci_writel(tmp_reg, CRG_REG_BASE + SDIO0_CRG);
		udelay(100);
		pin_drv_cap = sdio0_hs_drv;
	} else {
		/* EMMC clock */
		tmp_reg = himci_readl(CRG_REG_BASE + EMMC_CRG);
		tmp_reg &= ~EMMC_CLK_SEL_MASK;
		if (freq == 100000000)
			tmp_reg |= EMMC_CLK_SEL_100M << EMMC_CLK_SEL_SHIFT;
		else
			tmp_reg |= EMMC_CLK_SEL_50M << EMMC_CLK_SEL_SHIFT;
		himci_writel(tmp_reg, CRG_REG_BASE + EMMC_CRG);

		/* EMMC soft reset */
		tmp_reg |= EMMC_SRST;
		himci_writel(tmp_reg, CRG_REG_BASE + EMMC_CRG);
		udelay(100);
		tmp_reg &= ~EMMC_SRST;
		tmp_reg |= EMMC_CLK_EN;
		himci_writel(tmp_reg, CRG_REG_BASE + EMMC_CRG);
		udelay(100);
		pin_drv_cap = emmc_hs_drv;
	}

	start = pad_ctrl_start[dev_num];

	for (i = start, j = 0; j < 6; i = i+4, j++) {
		unsigned int reg = himci_readl(i);
		/*
		 * [10]:SR
		 * [9]:internel pull down
		 * [8]:internel pull up
		 * [7:4]:
		 * */
		reg = reg & (~(0x7f0));
		reg |= pin_drv_cap[j];
		himci_writel(reg, i);
	}
}

