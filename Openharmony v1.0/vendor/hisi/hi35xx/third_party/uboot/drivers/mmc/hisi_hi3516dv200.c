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
 * Description: SDHCI controller platform adaptation.
 */

#define SDIO_DRV_DLL_SRST_REQ		(0x1 << 29)
#define SDIO_CLK_EN			(0x1 << 28)
#define SDIO_SRST_REQ			(0x1 << 27)
#define SDIO_CLK_SEL			(0x7 << 24)
#define SDIO_CLK_SEL_400K		(0x1 << 24)

#define REG_EMMC_DRV_DLL_STATUS		(CRG_REG_BASE + 0x210)
#define REG_SDIO0_DRV_DLL_STATUS	REG_EMMC_DRV_DLL_STATUS
#define REG_SDIO1_DRV_DLL_STATUS	(CRG_REG_BASE + 0x228)
#define SDIO_DRV_DLL_LOCK		BIT(15)
#define SDIO_DRV_DLL_READY		BIT(14)

#define REG_EMMC_SAMPL_DLL_STATUS	(CRG_REG_BASE + 0x208)
#define REG_SDIO0_SAMPL_DLL_STATUS	REG_EMMC_SAMPL_DLL_STATUS
#define REG_SDIO1_SAMPL_DLL_STATUS	(CRG_REG_BASE + 0x224)
#define SDIO_SAMPL_DLL_SLAVE_READY	BIT(0)

#define REG_EMMC_SAMPL_DLL_CTRL		(CRG_REG_BASE + 0x1f4)
#define REG_SDIO0_SAMPL_DLL_CTRL	REG_EMMC_SAMPL_DLL_CTRL
#define REG_SDIO1_SAMPL_DLL_CTRL	(CRG_REG_BASE + 0x22c)
#define SDIO_SAMPL_DLL_SLAVE_EN		BIT(16)

#define REG_EMMC_SAMPLB_DLL_CTRL	(CRG_REG_BASE + 0x1f8)
#define REG_SDIO0_SAMPLB_DLL_CTRL	REG_EMMC_SAMPLB_DLL_CTRL
#define REG_SDIO1_SAMPLB_DLL_CTRL	(CRG_REG_BASE + 0x21c)
#define SDIO_SAMPLB_DLL_CLK_MASK	(0x1f << 0)
#define sdio_samplb_sel(phase)		((phase) << 0)

#define REG_EMMC_DRV_DLL_CTRL		(CRG_REG_BASE + 0x1fc)
#define REG_SDIO0_DRV_DLL_CTRL		REG_EMMC_DRV_DLL_CTRL
#define REG_SDIO1_DRV_DLL_CTRL		(CRG_REG_BASE + 0x220)
#define SDIO_DRV_PHASE_SEL_MASK		(0x1f << 24)
#define sdio_drv_sel(phase)		((phase) << 24)

#define REG_EMMC_DS_DLL_CTRL		(CRG_REG_BASE + 0x200)
#define EMMC_DS_DLL_MODE_SSEL		BIT(13)
#define EMMC_DS_DLL_SSEL_MASK		0x7f

#define REG_EMMC_DS180_DLL_CTRL		(CRG_REG_BASE + 0x204)
#define EMMC_DS180_DLL_BYPASS		BIT(15)
#define REG_EMMC_DS180_DLL_STATUS	(CRG_REG_BASE + 0x218)
#define EMMC_DS180_DLL_READY		BIT(0)

#define IO_CFG_SR			BIT(10)
#define IO_CFG_PULL_DOWN		BIT(9)
#define IO_CFG_PULL_UP			BIT(8)
#define IO_CFG_DRV_STR_MASK		(0xf << 4)
#define io_cfg_drv_str_sel(str)		((str) << 4)

#define REG_IO_CFG_BASE			0x100C0000
/* EMMC_IOCFG */
#define IO_CFG_EMMC_DATA_LINE_COUNT	8
#define REG_CTRL_EMMC_CLK		0x0014
#define REG_CTRL_EMMC_CMD		0x0018
#define REG_CTRL_EMMC_DATA0		0x001c
#define REG_CTRL_EMMC_DATA1		0x0028
#define REG_CTRL_EMMC_DATA2		0x0024
#define REG_CTRL_EMMC_DATA3		0x0020
#define REG_CTRL_EMMC_DATA4		0x0030
#define REG_CTRL_EMMC_DATA5		0x0034
#define REG_CTRL_EMMC_DATA6		0x0038
#define REG_CTRL_EMMC_DATA7		0x003c
#define REG_CTRL_EMMC_DS		0x0058
#define REG_CTRL_EMMC_RST		0x005c
static unsigned int io_emmc_data_reg[IO_CFG_EMMC_DATA_LINE_COUNT] = {
	REG_CTRL_EMMC_DATA0, REG_CTRL_EMMC_DATA1,
	REG_CTRL_EMMC_DATA2, REG_CTRL_EMMC_DATA3,
	REG_CTRL_EMMC_DATA4, REG_CTRL_EMMC_DATA5,
	REG_CTRL_EMMC_DATA6, REG_CTRL_EMMC_DATA7
};

#define IO_CFG_SDIO0_DATA_LINE_COUNT	4
#define REG_CTRL_SDIO0_CLK		0x0040
#define REG_CTRL_SDIO0_CMD		0x0044
#define REG_CTRL_SDIO0_DATA0		0x0048
#define REG_CTRL_SDIO0_DATA1		0x004C
#define REG_CTRL_SDIO0_DATA2		0x0050
#define REG_CTRL_SDIO0_DATA3		0x0054
static unsigned int io_sdio0_data_reg[IO_CFG_SDIO0_DATA_LINE_COUNT] = {
	REG_CTRL_SDIO0_DATA0, REG_CTRL_SDIO0_DATA1,
	REG_CTRL_SDIO0_DATA2, REG_CTRL_SDIO0_DATA3
};

#define CLK_100K	100000
#define CLK_400K	400000
#define CLK_25M		25000000
#define CLK_50M		50000000
#define CLK_90M		90000000
#define CLK_112M	112000000
#define CLK_150M	150000000
#define CLK_198M	198000000

static void hisi_dll_reset_assert(struct sdhci_host *host)
{
	uintptr_t crg_addr;
	unsigned int reg;

	crg_addr = REG_EMMC_CRG;
	reg = readl(crg_addr);
	reg |= SDIO_DRV_DLL_SRST_REQ;
	writel(reg, crg_addr);
}

static void hisi_dll_reset_deassert(struct sdhci_host *host)
{
	uintptr_t crg_addr;
	unsigned int reg;

	crg_addr = REG_EMMC_CRG;
	reg = readl(crg_addr);
	reg &= ~SDIO_DRV_DLL_SRST_REQ;
	writel(reg, crg_addr);
}

static void hisi_set_crg(struct sdhci_host *host, unsigned int clk)
{
	uintptr_t crg_addr;
	unsigned int sel, reg;
	unsigned int clk_mux[] = {
		CLK_100K, CLK_400K, CLK_25M, CLK_50M,
		CLK_90M, CLK_112M, CLK_150M, CLK_198M
	};

	crg_addr = REG_EMMC_CRG;
	reg = readl(crg_addr);
	reg &= ~MMC_CLK_SEL_MASK;

	if (clk <= MIN_FREQ) {
		sel = 1;
	} else {
		for (sel = 0x6; sel > 0; sel--) {
			if (clk >= clk_mux[sel])
				break;
		}
	}

	reg |= mmc_clk_sel(sel);
	writel(reg, crg_addr);
}

static void hisi_wait_ds180_dll_ready(void)
{
	unsigned int reg;
	unsigned int timeout = 20;

	do {
		reg = readl(REG_EMMC_DS180_DLL_STATUS);
		if (reg & EMMC_DS180_DLL_READY)
			return;

		udelay(1000); /* delay 1000us */
		timeout--;
	} while (timeout > 0);

	printf("DS180 DLL master not ready.\n");
}

static void hisi_mmc_priv_init(struct sdhci_host *host)
{
	unsigned short ctrl;
	unsigned int reg;

	ctrl = sdhci_readw(host, SDHCI_MSHC_CTRL);
	ctrl &= ~SDHCI_CMD_CONFLIT_CHECK;
	sdhci_writew(host, ctrl, SDHCI_MSHC_CTRL);

	reg = sdhci_readl(host, SDHCI_AXI_MBIIU_CTRL);
	reg |= SDHCI_GM_WR_OSRC_LMT | SDHCI_GM_RD_OSRC_LMT;
	reg &= ~SDHCI_UNDEFL_INCR_EN;
	sdhci_writel(host, reg, SDHCI_AXI_MBIIU_CTRL);

	reg  = sdhci_readl(host, SDHCI_MULTI_CYCLE);
	reg &= ~SDHCI_CMD_DLY_EN;
	reg |= SDHCI_EDGE_DETECT_EN | SDHCI_DATA_DLY_EN;
	sdhci_writel(host, reg, SDHCI_MULTI_CYCLE);
}

static void hisi_set_drv_str(unsigned int offset, unsigned int pull_up,
				unsigned int pull_down, unsigned int sr,
				unsigned int drv_str)
{
	unsigned int reg;
	const uintptr_t crg_addr = REG_IO_CFG_BASE + offset;

	reg = readl(crg_addr);
	reg &= ~(IO_CFG_PULL_UP | IO_CFG_PULL_DOWN |
		 IO_CFG_DRV_STR_MASK | IO_CFG_SR);
	reg |= (pull_up ? IO_CFG_PULL_UP : 0);
	reg |= (pull_down ? IO_CFG_PULL_DOWN : 0);
	reg |= (sr ? IO_CFG_SR : 0);
	reg |= io_cfg_drv_str_sel(drv_str);
	writel(reg, crg_addr);
}

static int sd_hardware_init(void)
{
	unsigned int reg;

	/* clk enable */
	reg = readl(REG_EMMC_CRG);
	reg |= SDIO_CLK_EN;
	writel(reg, REG_EMMC_CRG);

	/* reset assert */
	reg = readl(REG_EMMC_CRG);
	reg |= SDIO_SRST_REQ | SDIO_DRV_DLL_SRST_REQ;
	writel(reg, REG_EMMC_CRG);
	udelay(25); /* delay 25us */

	/* reset deassert */
	reg &= ~SDIO_SRST_REQ;
	writel(reg, REG_EMMC_CRG);
	udelay(1); /* delay 1us */

	udelay(5000); /* delay 5000us */

	return 0;
}

static int emmc_hardware_init(void)
{
	unsigned int reg;

	/* eMMC clk enable */
	reg = readl(REG_EMMC_CRG);
	reg |= SDIO_CLK_EN;
	writel(reg, REG_EMMC_CRG);

	/* eMMC reset assert */
	reg = readl(REG_EMMC_CRG);
	reg |= SDIO_SRST_REQ | SDIO_DRV_DLL_SRST_REQ;
	writel(reg, REG_EMMC_CRG);
	udelay(25); /* delay 25us */

	/* select 400K clk */
	reg = readl(REG_EMMC_CRG);
	reg &= ~SDIO_CLK_SEL;
	reg |= SDIO_CLK_SEL_400K;
	writel(reg, REG_EMMC_CRG);
	udelay(25); /* delay 25us */

	/* eMMC reset deassert */
	reg = readl(REG_EMMC_CRG);
	reg &= ~SDIO_SRST_REQ;
	writel(reg, REG_EMMC_CRG);
	udelay(1); /* delay 1us */

	return 0;
}

static void hisi_emmc_set_ioconfig(struct sdhci_host *host)
{
	int i;

	switch (host->mmc->selected_mode) {
	case MMC_HS_400:
	case MMC_HS_400_ES:
		hisi_set_drv_str(REG_CTRL_EMMC_CLK, 0, 1, 0, 0x3);  /* set drv level 3 */
		hisi_set_drv_str(REG_CTRL_EMMC_CMD, 1, 0, 0, 0x4);  /* set drv level 4 */
		for (i = 0; i < IO_CFG_EMMC_DATA_LINE_COUNT; i++)
			hisi_set_drv_str(io_emmc_data_reg[i], 1, 0, 0, 0x4); /* set drv level 4 */

		hisi_set_drv_str(REG_CTRL_EMMC_DS, 0, 1, 1, 0x3);   /* set drv level 3 */
		hisi_set_drv_str(REG_CTRL_EMMC_RST, 1, 0, 1, 0x3);  /* set drv level 3 */
		break;
	case MMC_HS_200:
		hisi_set_drv_str(REG_CTRL_EMMC_CLK, 0, 1, 0, 0x2);  /* set drv level 2 */
		hisi_set_drv_str(REG_CTRL_EMMC_CMD, 1, 0, 1, 0x4);  /* set drv level 4 */
		for (i = 0; i < IO_CFG_EMMC_DATA_LINE_COUNT; i++)
			hisi_set_drv_str(io_emmc_data_reg[i], 1, 0, 1, 0x4); /* set drv level 4 */

		hisi_set_drv_str(REG_CTRL_EMMC_RST, 1, 0, 1, 0x3);  /* set drv level 3 */
		break;
	case MMC_HS:
	case MMC_HS_52:
		hisi_set_drv_str(REG_CTRL_EMMC_CLK, 0, 1, 1, 0x4);  /* set drv level 4 */
		hisi_set_drv_str(REG_CTRL_EMMC_CMD, 1, 0, 1, 0x6);  /* set drv level 6 */
		for (i = 0; i < IO_CFG_EMMC_DATA_LINE_COUNT; i++)
			hisi_set_drv_str(io_emmc_data_reg[i], 1, 0, 1, 0x6); /* set drv level 6 */

		hisi_set_drv_str(REG_CTRL_EMMC_RST, 1, 0, 1, 0x3);  /* set drv level 3 */
		break;
	case MMC_LEGACY:
	default:
		hisi_set_drv_str(REG_CTRL_EMMC_CLK, 0, 1, 1, 0x5);  /* set drv level 5 */
		hisi_set_drv_str(REG_CTRL_EMMC_CMD, 1, 0, 1, 0x6);  /* set drv level 6 */
		for (i = 0; i < IO_CFG_EMMC_DATA_LINE_COUNT; i++)
			hisi_set_drv_str(io_emmc_data_reg[i], 1, 0, 1, 0x6); /* set drv level 6 */

		hisi_set_drv_str(REG_CTRL_EMMC_RST, 1, 0, 1, 0x3);  /* set drv level 3 */
		break;
	}
}

static void hisi_sd_set_ioconfig(struct sdhci_host *host)
{
	int i;

	switch (host->mmc->selected_mode) {
	case SD_HS:
		hisi_set_drv_str(REG_CTRL_SDIO0_CLK, 0, 1, 1, 0x5);  /* set drv level 5 */
		hisi_set_drv_str(REG_CTRL_SDIO0_CMD, 1, 0, 1, 0x7);  /* set drv level 7 */
		for (i = 0; i < IO_CFG_SDIO0_DATA_LINE_COUNT; i++)
			hisi_set_drv_str(io_sdio0_data_reg[i], 1, 0, 1, 0x7); /* set drv level 7 */
		break;
	case SD_LEGACY:
	default:
		hisi_set_drv_str(REG_CTRL_SDIO0_CLK, 0, 1, 1, 0x7);  /* set drv level 7 */
		hisi_set_drv_str(REG_CTRL_SDIO0_CMD, 1, 0, 1, 0x7);  /* set drv level 7 */
		for (i = 0; i < IO_CFG_SDIO0_DATA_LINE_COUNT; i++)
			hisi_set_drv_str(io_sdio0_data_reg[i], 1, 0, 1, 0x7); /* set drv level 7 */
		break;
	}
}

static void hisi_mmc_set_ioconfig(struct sdhci_host *host)
{
	unsigned int reg;

	if (host->type == MMC_TYPE_MMC) {
		reg = sdhci_readw(host, SDHCI_EMMC_CTRL);
		reg |= SDHCI_CARD_IS_EMMC;
		sdhci_writew(host, reg, SDHCI_EMMC_CTRL);

		hisi_emmc_set_ioconfig(host);
	} else {
		hisi_sd_set_ioconfig(host);
	}
	sdhci_set_uhs_timing(host);
}

static void hisi_set_phase(struct sdhci_host *host)
{
	unsigned int drv_phase, sample_phase;

	if (host->mmc->selected_mode == MMC_HS_400_ES ||
	    host->mmc->selected_mode == MMC_HS_400) {
		drv_phase = 10;   /* 10 for 112.5 degree */
		sample_phase = host->tuning_phase;
	} else if (host->mmc->selected_mode == MMC_HS_200) {
		drv_phase = 23;   /* 23 for 258.75 degree */
		sample_phase = host->tuning_phase;
	} else if (host->mmc->selected_mode == MMC_HS ||
		   host->mmc->selected_mode == MMC_HS_52) {
		drv_phase = 16;   /* 16 for 180 degree */
		sample_phase = 4; /* 4 for 45 degree */
	} else if (host->mmc->selected_mode == SD_HS) {
		drv_phase = 20;   /* 20 for 225 degree */
		sample_phase = 4; /* 4 for 45 degree */
	} else if (host->mmc->selected_mode == MMC_LEGACY ||
		   host->mmc->selected_mode == SD_LEGACY) {
		drv_phase = 16;   /* 16 for 180 degree */
		sample_phase = 0; /* 0 for degree */
	} else {
		drv_phase = 16;   /* 16 for 180 degree */
		sample_phase = 4; /* 4 for 45 degree */
	}

	hisi_set_drv_phase(host, drv_phase);
	hisi_enable_sample(host);
	hisi_set_sampl_phase(host, sample_phase);

	udelay(25); /* delay 25us */
}

static void hisi_wait_drv_dll_lock(struct sdhci_host *host)
{
	unsigned int timeout = 20;
	unsigned int reg;
	uintptr_t reg_addr;

	reg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_DRV_DLL_STATUS : REG_SDIO0_DRV_DLL_STATUS;
	do {
		reg = readl(reg_addr);
		if (reg & SDIO_DRV_DLL_LOCK)
			return;

		udelay(1000); /* delay 1000us */
		timeout--;
	} while (timeout > 0);

	printf("sdhci-hisi: DRV DLL master not locked.\n");
}

static void hisi_enable_sampl_dll_slave(struct sdhci_host *host)
{
	unsigned int reg;
	uintptr_t reg_addr;

	reg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_SAMPL_DLL_CTRL : REG_SDIO0_SAMPL_DLL_CTRL;
	reg = readl(reg_addr);
	reg |= SDIO_SAMPL_DLL_SLAVE_EN;
	writel(reg, reg_addr);
}

static int hisi_mmc_set_clk(struct sdhci_host *host, unsigned int clk)
{
	hisi_dll_reset_assert(host);
	udelay(25); /* delay 25us */
	hisi_set_crg(host, clk);
	hisi_set_phase(host);
	udelay(25); /* delay 25us */

	if (clk > MMC_HIGH_52_MAX_DTR) {
		hisi_enable_sampl_dll_slave(host);
		hisi_dll_reset_deassert(host);
	}

	hisi_enable_internal_clk(host);

	if (clk > MMC_HIGH_52_MAX_DTR) {
		hisi_wait_drv_dll_lock(host);
		hisi_wait_sampl_dll_slave_ready(host);
		hisi_wait_ds180_dll_ready();
	}

	hisi_enable_card_clk(host);
	udelay(100); /* delay 100us */

	return 0;
}