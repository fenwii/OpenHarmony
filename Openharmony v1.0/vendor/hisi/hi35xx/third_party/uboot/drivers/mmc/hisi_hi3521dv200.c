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

/* CRG register */
#define PERI_CRG_MMC_CLK	(CRG_REG_BASE + 0x34c0)
#define  CRG_CLK_SEL_SHIFT	24
#define  CRG_CLK_SEL_MASK	(0x7 << CRG_CLK_SEL_SHIFT)
#define  CRG_DLL_SRST_REQ	(1 << 16)
#define  CRG_CLK_EN		(1 << 0)
#define  CRG_AHB_CLK_EN		(2 << 0)

#define PERI_CRG_MMC_P4_DLL	(CRG_REG_BASE + 0x34c4)
#define  CRG_P4_DLL_SRST_REQ	(1 << 1)

#define PERI_CRG_MMC_DRV_DLL	(CRG_REG_BASE + 0x34c8)
#define  CRG_DRV_PHASE_SEL_SHIFT	15
#define  CRG_DRV_PHASE_SEL_MASK	(0x1F << 15)

#define PERI_CRG_MMC_STAT	(CRG_REG_BASE + 0x34d8)
#define  CRG_SAM_DLL_READY	(1 << 12)
#define  CRG_DS_DLL_READY	(1 << 10)
#define  CRG_P4_DLL_LOCKED	(1 << 9)

#define REG_EMMC_SAMPL_DLL_STATUS	PERI_CRG_MMC_STAT
#define REG_SDIO0_SAMPL_DLL_STATUS	PERI_CRG_MMC_STAT
#define  SDIO_SAMPL_DLL_SLAVE_READY	CRG_SAM_DLL_READY

#define REG_EMMC_DRV_DLL_CTRL		PERI_CRG_MMC_DRV_DLL
#define REG_SDIO0_DRV_DLL_CTRL		PERI_CRG_MMC_DRV_DLL
#define  SDIO_DRV_PHASE_SEL_MASK	CRG_DRV_PHASE_SEL_MASK
#define  sdio_drv_sel(phase)		((phase) << CRG_DRV_PHASE_SEL_SHIFT)

#define REG_EMMC_SAMPLB_DLL_CTRL	0x34d4
#define SDIO_SAMPLB_DLL_CLK_MASK	0xf
#define sdio_samplb_sel(phase)		(((phase) & 0xf) << 0)

/* eMMC io reg */
#define REG_IO_CFG_BASE		0x10FF0000
#define REG_MMC_D0_IO		0xd0
#define REG_MMC_D1_IO		0xd4
#define REG_MMC_D2_IO		0xd8
#define REG_MMC_D3_IO		0xdc
#define REG_MMC_CLK_IO		0xc8
#define REG_MMC_CMD_IO		0xcc
#define REG_MMC_RST_IO		0xc4
#define REG_MMC_D4_IO		0xec
#define REG_MMC_D6_IO		0xf0
#define REG_MMC_D5_IO		0xe0
#define REG_MMC_D7_IO		0xe4
#define REG_MMC_DQS_IO		0xf4

 /* IO CFG */
#define  IO_CFG_DRV_STR_MASK		(0xf << 4)
#define  io_cfg_drv_str_sel(str)	((str) << 4)
#define  IO_CFG_PULL_UP			(0x1 << 8)
#define  IO_CFG_PULL_DOWN		(0x1 << 9)
#define  IO_CFG_SR			(0x1 << 10)
#define  IO_CFG_SDIO_MASK		(IO_CFG_DRV_STR_MASK | IO_CFG_PULL_UP |\
					 IO_CFG_PULL_DOWN | IO_CFG_SR)
#define MMC_IO_MUX			0x1
#define SD_IO_MUX			0x2
#define IO_MUX_MASK			0x3
#define MMC_BUS_WIDTH_4_BIT		4
#define MMC_BUS_WIDTH_8_BIT		8
#define BOOT_FROM_NAND_FLAG		(0x1  << 2)
#define BOOT_FLAG_MASK			(0x3  << 2)
#define EMMC_BOOT_8BIT			(0x1  << 11)

#define IO_CLK				0
#define IO_CMD				1
#define IO_DATA				2
#define IO_RST				3
#define IO_DS				4
#define EMMC_IO_TYPE_NUM		5

static unsigned int reg_data_io[] = {
	REG_MMC_D0_IO, REG_MMC_D1_IO,
	REG_MMC_D2_IO, REG_MMC_D3_IO,
	REG_MMC_D4_IO, REG_MMC_D5_IO,
	REG_MMC_D6_IO, REG_MMC_D7_IO
};

static u32 hisi_mmc_io_cfg[][EMMC_IO_TYPE_NUM] = {
	[MMC_LEGACY] = {
		io_cfg_drv_str_sel(0xd) | IO_CFG_PULL_DOWN,
		io_cfg_drv_str_sel(0xe) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0xe) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0x3) | IO_CFG_PULL_UP
	},
	[MMC_HS] = {
		io_cfg_drv_str_sel(0xd) | IO_CFG_PULL_DOWN,
		io_cfg_drv_str_sel(0xe) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0xe) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0x3) | IO_CFG_PULL_UP
	},
	[SD_HS] = {
		io_cfg_drv_str_sel(0xd) | IO_CFG_PULL_DOWN,
		io_cfg_drv_str_sel(0xe) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0xe) | IO_CFG_PULL_UP
	},
	[MMC_HS_52] = {
		io_cfg_drv_str_sel(0xd) | IO_CFG_PULL_DOWN,
		io_cfg_drv_str_sel(0xe) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0xe) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0x3) | IO_CFG_PULL_UP
	},
	[MMC_HS_200] = {
		io_cfg_drv_str_sel(0x8) | IO_CFG_PULL_DOWN,
		io_cfg_drv_str_sel(0xc) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0xc) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0x3) | IO_CFG_PULL_UP
	},
	[MMC_HS_400] = {
		io_cfg_drv_str_sel(0x8) | IO_CFG_PULL_DOWN,
		io_cfg_drv_str_sel(0xa) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0xa) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0x3) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0x3)
	},
	[MMC_HS_400_ES] = {
		io_cfg_drv_str_sel(0x8) | IO_CFG_PULL_DOWN,
		io_cfg_drv_str_sel(0xa) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0xa) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0x3) | IO_CFG_PULL_UP,
		io_cfg_drv_str_sel(0x3)
	}
};

/* avaliable frequency */
#define CLK_400K	400000
#define CLK_24P75M	24750000
#define CLK_49P5M	49500000
#define CLK_99M		99000000
#define CLK_148P5M	148500000

/* sample drive phase */
#define DRIVE		0
#define SAMPLE		1
#define PHASE_TYPE_NUM	2

static u32 hisi_phase_cfg[][PHASE_TYPE_NUM] = {
	[MMC_LEGACY]     = { 16, 0 },
	[MMC_HS]     = { 16, 4 },
	[MMC_HS_52]  = { 16, 4 },
	[SD_HS]      = { 16, 4 },
	[MMC_HS_200]  = { 22, 0 },
#ifdef CONFIG_TARGET_HI3521DV200
	[MMC_HS_400]  = {  9, 0 },
	[MMC_HS_400_ES]  = {  9, 0 }
#else /* CONFIG_TARGET_HI3520DV500 */
	[MMC_HS_400]  = { 11, 0 },
	[MMC_HS_400_ES]  = {  11, 0 }
#endif
};

unsigned int get_ocr_from_bootrom(void)
{
	return readl(REG_SAVE_HCS);
}

void hisi_wait_drv_dll_lock(struct sdhci_host *host)
{
	/* doing nothing */
}

void hisi_enable_sampl_dll_slave(struct sdhci_host *host)
{
	/* doing nothing */
}

static void hisi_dll_reset_assert(void)
{
	const uintptr_t crg_addr =  PERI_CRG_MMC_P4_DLL;
	unsigned int reg;

	reg = readl(crg_addr);
	reg |= CRG_P4_DLL_SRST_REQ;
	writel(reg, crg_addr);
}

static void hisi_dll_reset_deassert(void)
{
	const uintptr_t crg_addr = PERI_CRG_MMC_P4_DLL;
	unsigned int reg;

	reg = readl(crg_addr);
	reg &= ~CRG_P4_DLL_SRST_REQ;
	writel(reg, crg_addr);
}

static void hisi_wait_p4_dll_lock(void)
{
	const uintptr_t reg_addr = PERI_CRG_MMC_STAT;
	unsigned int timeout = 20;
	unsigned int reg;

	do {
		reg = readl(reg_addr);
		if (reg & CRG_P4_DLL_LOCKED)
			return;

		udelay(1000); /* delay 1000 us */
		timeout--;
	} while (timeout > 0);

	printf("sdhci-hisi: P4 DLL master not locked.\n");
}

static void hisi_wait_ds_dll_ready(void)
{
	const uintptr_t reg_addr = PERI_CRG_MMC_STAT;
	unsigned int timeout = 20;
	unsigned int reg;

	do {
		reg = readl(reg_addr);
		if (reg & CRG_DS_DLL_READY)
			return;

		udelay(1000); /* delay 1000 us */
		timeout--;
	} while (timeout > 0);

	printf("sdhci-hisi: DS DLL slave not ready.\n");
}

static void hisi_mmc_priv_init(struct sdhci_host *host)
{
	unsigned int reg;

	reg = sdhci_readl(host, SDHCI_AXI_MBIIU_CTRL);
	reg &= ~SDHCI_UNDEFL_INCR_EN;
	sdhci_writel(host, reg, SDHCI_AXI_MBIIU_CTRL);

	reg = sdhci_readl(host, SDHCI_EMMC_CTRL);
	reg |= SDHCI_CARD_IS_EMMC;
	sdhci_writel(host, reg, SDHCI_EMMC_CTRL);
}

static unsigned int get_mmc_bus_width(void)
{
	unsigned int sys_stat;
	unsigned int bus_width;

	sys_stat = readl(SYS_CTRL_REG_BASE + REG_SYSSTAT);

	if ((sys_stat & BOOT_FLAG_MASK) == BOOT_FROM_NAND_FLAG) {
		/* up to 4 bit mode support when spi nand start up */
		bus_width = MMC_BUS_WIDTH_4_BIT;
	} else {
		bus_width =  (sys_stat & EMMC_BOOT_8BIT) ?
			MMC_BUS_WIDTH_8_BIT : MMC_BUS_WIDTH_4_BIT;
	}

	return bus_width;
}

static void hisi_set_drv_str(unsigned int offset, unsigned int drv_str)
{
	unsigned int reg;
	const uintptr_t io_addr = REG_IO_CFG_BASE + offset;

	reg = readl(io_addr);
	reg &= ~IO_CFG_SDIO_MASK;
	reg |= drv_str;
	writel(reg, io_addr);
}

static void hisi_mmc_set_ioconfig(struct sdhci_host *host)
{
	unsigned int selected_mode = host->mmc->selected_mode;
	unsigned int bus_width;
	unsigned int i;

	bus_width = get_mmc_bus_width();

	hisi_set_drv_str(REG_MMC_CLK_IO, hisi_mmc_io_cfg[selected_mode][IO_CLK]);
	hisi_set_drv_str(REG_MMC_CMD_IO, hisi_mmc_io_cfg[selected_mode][IO_CMD]);
	for (i = 0; i < bus_width; i++)
		hisi_set_drv_str(reg_data_io[i],
				 hisi_mmc_io_cfg[selected_mode][IO_DATA]);
	hisi_set_drv_str(REG_MMC_RST_IO, hisi_mmc_io_cfg[selected_mode][IO_RST]);

	if (selected_mode == MMC_HS_400 ||
	    selected_mode == MMC_HS_400_ES)
		hisi_set_drv_str(REG_MMC_DQS_IO,
				 hisi_mmc_io_cfg[selected_mode][IO_DS]);

	sdhci_set_uhs_timing(host);
}

static void hisi_set_phase(struct sdhci_host *host)
{
	unsigned int drv_phase, sample_phase;
	unsigned int selected_mode = host->mmc->selected_mode;

	if (selected_mode == MMC_HS_400 ||
	    selected_mode == MMC_HS_200)
		sample_phase = host->tuning_phase;
	else
		sample_phase = hisi_phase_cfg[selected_mode][SAMPLE];

	drv_phase = hisi_phase_cfg[selected_mode][DRIVE];

	hisi_set_drv_phase(host, drv_phase);
	hisi_enable_sample(host);
	hisi_set_sampl_phase(host, sample_phase);

	udelay(25); /* delay 25us */
}

static void hisi_set_crg(struct sdhci_host *host, unsigned int clk)
{
	const uintptr_t crg_addr = PERI_CRG_MMC_CLK;
	unsigned int sel, reg;
	unsigned int clk_mux[] = {
		CLK_400K, CLK_24P75M, CLK_49P5M,
		CLK_99M, CLK_148P5M
	};

	for (sel = 0x4; sel > 0; sel--) {
		if (clk >= clk_mux[sel])
			break;
	}

	reg = readl(crg_addr);
	reg &= ~CRG_CLK_SEL_MASK;
	reg |= mmc_clk_sel(sel);
	writel(reg, crg_addr);
}

static int hisi_mmc_set_clk(struct sdhci_host *host, unsigned int clk)
{
	hisi_disable_card_clk(host);
	udelay(25); /* delay 25 us */
	hisi_disable_internal_clk(host);

	if (clk == 0)
		return 0;

	hisi_set_crg(host, clk);
	hisi_set_phase(host);

	udelay(5); /* delay 5 us */

	hisi_enable_internal_clk(host);

	if ((host->mmc->selected_mode == MMC_HS_400) ||
	    (host->mmc->selected_mode == MMC_HS_400_ES) ||
	    (host->mmc->selected_mode == MMC_HS_200)) {
		hisi_dll_reset_assert();
		hisi_dll_reset_deassert();
		hisi_wait_p4_dll_lock();
		hisi_wait_sampl_dll_slave_ready(host);
	}

	if ((host->mmc->selected_mode == MMC_HS_400) ||
	    (host->mmc->selected_mode == MMC_HS_400_ES))
		hisi_wait_ds_dll_ready();

	hisi_enable_card_clk(host);
	udelay(75); /* delay 75 us */

	return 0;
}

static void hisi_set_pin_mux(unsigned int offset, unsigned int pin_mux)
{
	unsigned int reg;
	const uintptr_t io_addr = REG_IO_CFG_BASE + offset;

	reg = readl(io_addr);
	reg &= ~IO_MUX_MASK;
	reg |= pin_mux;
	writel(reg, io_addr);
}

static void mmc_pin_mux_config(int is_emmc)
{
	unsigned int bus_width, pin_mux, i;

	if (is_emmc) {
		bus_width = get_mmc_bus_width();
		pin_mux = MMC_IO_MUX;
	} else {
		bus_width = MMC_BUS_WIDTH_4_BIT;
		pin_mux = SD_IO_MUX;
	}

	hisi_set_pin_mux(REG_MMC_CLK_IO, pin_mux);
	hisi_set_pin_mux(REG_MMC_CMD_IO, pin_mux);
	for (i = 0; i < bus_width; i++)
		hisi_set_pin_mux(reg_data_io[i], pin_mux);
	/* REG_MMC_RST_IO & SDIO_CARD_POWER_EN_N is the same pin */
	hisi_set_pin_mux(REG_MMC_RST_IO, pin_mux);

	if (bus_width == MMC_BUS_WIDTH_8_BIT)
		hisi_set_pin_mux(REG_MMC_DQS_IO, MMC_IO_MUX);
}

static void hisi_mmc_crg_init(void)
{
	unsigned int reg;

	/* eMMC clk enable */
	reg = readl(PERI_CRG_MMC_CLK);
	reg |= CRG_CLK_EN | CRG_AHB_CLK_EN;
	writel(reg, PERI_CRG_MMC_CLK);

	/* eMMC reset assert */
	reg = readl(PERI_CRG_MMC_CLK);
	reg |= CRG_DLL_SRST_REQ;
	writel(reg, PERI_CRG_MMC_CLK);
	udelay(25); /* delay 25us */

	/* eMMC reset deassert */
	reg = readl(PERI_CRG_MMC_CLK);
	reg &= ~CRG_DLL_SRST_REQ;
	writel(reg, PERI_CRG_MMC_CLK);
	udelay(1); /* delay 1us */
}

#define DEVICE_TYPE_EMMC	1
#define DEVICE_TYPE_SD	0

static int emmc_hardware_init(void)
{
	mmc_pin_mux_config(DEVICE_TYPE_EMMC);
	if (!get_ocr_from_bootrom())
		hisi_mmc_crg_init();
	return 0;
}

static int sd_hardware_init(void)
{
	mmc_pin_mux_config(DEVICE_TYPE_SD);
	hisi_mmc_crg_init();
	return 0;
}

