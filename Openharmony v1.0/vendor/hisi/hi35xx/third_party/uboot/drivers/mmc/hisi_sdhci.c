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

#include <common.h>
#include <malloc.h>
#include <sdhci.h>
#include "mmc_private.h"

#define MIN_FREQ	400000
#define NOT_FOUND	(-1)
#define PHASE_SCALE	32
#define EDGE_TUNING_PHASE_STEP	4

static void hisi_enable_sample(struct sdhci_host *host);
static void hisi_set_drv_phase(struct sdhci_host *host,	unsigned int phase);
static void hisi_set_sampl_phase(struct sdhci_host *host, unsigned int phase);
static void hisi_wait_sampl_dll_slave_ready(struct sdhci_host *host);
static void hisi_enable_card_clk(struct sdhci_host *host);
static void hisi_disable_card_clk(struct sdhci_host *host);
static void hisi_enable_internal_clk(struct sdhci_host *host);
static void hisi_disable_internal_clk(struct sdhci_host *host);

#if defined(CONFIG_TARGET_HI3556AV100) || defined(CONFIG_TARGET_HI3519AV100)
#include <asm/arch-hi3556av100/platform.h>
#include "hisi_hi3556av100.c"
#endif

#if defined(CONFIG_TARGET_HI3559AV100) || defined(CONFIG_TARGET_HI3569V100)
#include <asm/arch-hi3559av100/platform.h>
#include "hisi_hi3559av100.c"
#endif

#ifdef CONFIG_TARGET_HI3516EV200
#include <asm/arch-hi3516ev200/platform.h>
#include "hisi_hi3516ev200.c"
#endif

#ifdef CONFIG_TARGET_HI3516EV300
#include <asm/arch-hi3516ev300/platform.h>
#include "hisi_hi3516ev300.c"
#endif

#ifdef CONFIG_TARGET_HI3518EV300
#include <asm/arch-hi3518ev300/platform.h>
#include "hisi_hi3518ev300.c"
#endif

#ifdef CONFIG_TARGET_HI3516DV200
#include <asm/arch-hi3516dv200/platform.h>
#include "hisi_hi3516dv200.c"
#endif

#ifdef CONFIG_TARGET_HI3531DV200
#include <asm/arch-hi3531dv200/platform.h>
#include "hisi_hi3531dv200.c"
#endif

#ifdef CONFIG_TARGET_HI3535AV100
#include <asm/arch-hi3531dv200/platform.h>
#include "hisi_hi3531dv200.c"
#endif

#ifdef CONFIG_TARGET_HI3521DV200
#include <asm/arch-hi3521dv200/platform.h>
#include "hisi_hi3521dv200.c"
#endif

#ifdef CONFIG_TARGET_HI3520DV500
#include <asm/arch-hi3521dv200/platform.h>
#include "hisi_hi3521dv200.c"
#endif

static void hisi_enable_card_clk(struct sdhci_host *host)
{
	u16 clk;

	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
}

static void hisi_disable_card_clk(struct sdhci_host *host)
{
	u16 clk;

	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	clk &= ~SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
}

static void hisi_enable_internal_clk(struct sdhci_host *host)
{
	u16 clk;
	u16 timeout = 20;

	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	clk |= SDHCI_CLOCK_INT_EN | SDHCI_CLOCK_PLL_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

	/* Wait max 20 ms */
	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	while (!(clk & SDHCI_CLOCK_INT_STABLE)) {
		if (timeout == 0) {
			printf("%s: Internal clock never stabilised.\n",
					__func__);
			return;
		}
		timeout--;
		udelay(1000); /* delay 1000us */
		clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	}
}

static void __maybe_unused hisi_disable_internal_clk(struct sdhci_host *host)
{
	u16 clk;

	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	clk &= ~SDHCI_CLOCK_INT_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
}

static void hisi_set_drv_phase(struct sdhci_host *host, unsigned int phase)
{
	uintptr_t crg_addr;
	unsigned int reg;

	crg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_DRV_DLL_CTRL : REG_SDIO0_DRV_DLL_CTRL;
	reg = readl(crg_addr);
	reg &= ~SDIO_DRV_PHASE_SEL_MASK;
	reg |= sdio_drv_sel(phase);
	writel(reg, crg_addr);
}

static void hisi_enable_sample(struct sdhci_host *host)
{
	unsigned int reg;

	reg = sdhci_readl(host, SDHCI_AT_CTRL);
	reg |= SDHCI_SAMPLE_EN;
	sdhci_writel(host, reg, SDHCI_AT_CTRL);
}

static void hisi_set_sampl_phase(struct sdhci_host *host, unsigned int phase)
{
	unsigned int reg;

	reg = sdhci_readl(host, SDHCI_AT_STAT);
	reg &= ~SDHCI_PHASE_SEL_MASK;
	reg |= phase;
	sdhci_writel(host, reg, SDHCI_AT_STAT);
}

static void hisi_wait_sampl_dll_slave_ready(struct sdhci_host *host)
{
	unsigned int reg;
	unsigned int timeout = 20;
	uintptr_t reg_addr;

	reg_addr = host->type == MMC_TYPE_MMC ?
		REG_EMMC_SAMPL_DLL_STATUS : REG_SDIO0_SAMPL_DLL_STATUS;
	do {
		reg = readl(reg_addr);
		if (reg & SDIO_SAMPL_DLL_SLAVE_READY)
			return;

		udelay(1000); /* delay 1000us */
		timeout--;
	} while (timeout > 0);

	printf("sdhci-hisi: SAMPL DLL slave not ready.\n");
}

static void hisi_enable_edge_tuning(struct sdhci_host *host)
{
	unsigned int reg;

	reg = readl(REG_EMMC_SAMPLB_DLL_CTRL);
	reg &= ~SDIO_SAMPLB_DLL_CLK_MASK;
	reg |= sdio_samplb_sel(8); /* sel 8 */
	writel(reg, REG_EMMC_SAMPLB_DLL_CTRL);

	reg = sdhci_readl(host, SDHCI_MULTI_CYCLE);
	reg |= SDHCI_EDGE_DETECT_EN;
	sdhci_writel(host, reg, SDHCI_MULTI_CYCLE);
}

static void hisi_disable_edge_tuning(struct sdhci_host *host)
{
	unsigned int reg;

	reg = sdhci_readl(host, SDHCI_MULTI_CYCLE);
	reg &= ~SDHCI_EDGE_DETECT_EN;
	sdhci_writel(host, reg, SDHCI_MULTI_CYCLE);
}

static void hisi_select_sampl_phase(struct sdhci_host *host, unsigned int phase)
{
	hisi_disable_card_clk(host);
	hisi_set_sampl_phase(host, phase);
	hisi_wait_sampl_dll_slave_ready(host);
	hisi_enable_card_clk(host);
	udelay(1);
}

static int hisi_send_tuning(struct sdhci_host *host, u32 opcode, int* cmd_error)
{
	int count, err;
	const int tuning_num = 1;

	count = 0;
	do {
		err = mmc_send_tuning(host->mmc, opcode, NULL);
		if (err)
			break;

		count++;
	} while (count < tuning_num);

	return err;
}

static int hisi_mmc_exec_tuning(struct sdhci_host *host, unsigned int opcode)
{
	unsigned int index, val;
	unsigned int edge_p2f, edge_f2p, start, end, phase;
	unsigned int fall, rise, fall_updat_flag;
	unsigned int found;
	unsigned int prev_found = 0;
	int err;
	int prev_err = 0;
	unsigned short ctrl;

	hisi_wait_drv_dll_lock(host);
	hisi_enable_sampl_dll_slave(host);
	hisi_enable_sample(host);
	hisi_enable_edge_tuning(host);
	host->is_tuning = 1;

	start = 0;
	end = PHASE_SCALE / EDGE_TUNING_PHASE_STEP;

	edge_p2f = start;
	edge_f2p = end;
	for (index = 0; index <= end; index++) {
		hisi_select_sampl_phase(host, index * EDGE_TUNING_PHASE_STEP);

		err = mmc_send_tuning(host->mmc, opcode, NULL);
		if (!err) {
			val = sdhci_readl(host, SDHCI_MULTI_CYCLE);
			found = val & SDHCI_FOUND_EDGE;
		} else {
			found = 1;
		}

		if (prev_found && !found)
			edge_f2p = index;
		else if (!prev_found && found)
			edge_p2f = index;

		if ((edge_p2f != start) && (edge_f2p != end))
			break;

		prev_found = found;
	}

	if ((edge_p2f == start) && (edge_f2p == end)) {
		printf("sdhci-hisi: tuning failed! can not found edge!\n");
		return -1;
	}

	hisi_disable_edge_tuning(host);

	start = edge_p2f * EDGE_TUNING_PHASE_STEP;
	end = edge_f2p * EDGE_TUNING_PHASE_STEP;
	if (end <= start)
		end += PHASE_SCALE;

	fall = start;
	rise = end;
	fall_updat_flag = 0;
	for (index = start; index <= end; index++) {
		hisi_select_sampl_phase(host, index % PHASE_SCALE);

		err = hisi_send_tuning(host, opcode, NULL);
		if (err)
			debug("sdhci-hisi: send tuning CMD%u fail! phase:%u err:%d\n",
				opcode, index, err);

		if (err && index == start) {
			if (!fall_updat_flag) {
				fall_updat_flag = 1;
				fall = start;
			}
		} else {
			if (!prev_err && err) {
				if (!fall_updat_flag) {
					fall_updat_flag = 1;
					fall = index;
				}
			}
		}

		if (prev_err && !err)
			rise = index;

		if (err && index == end)
			rise = end;

		prev_err = err;
	}

	phase = ((fall + rise) / 2 + PHASE_SCALE / 2) % PHASE_SCALE; /* 2 for cal average */

	printf("sdhci-hisi: tuning done! valid phase shift [%u, %u] Final Phase:%u\n",
			rise % PHASE_SCALE, fall % PHASE_SCALE, phase);

	host->tuning_phase = phase;
	hisi_select_sampl_phase(host, phase);

	ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	ctrl |= SDHCI_CTRL_TUNED_CLK;
	sdhci_writew(host, ctrl, SDHCI_HOST_CONTROL2);
	host->is_tuning = 0;

	return 0;
}

void hisi_sdhci_set_host_caps(struct sdhci_host *host)
{
	host->host_caps = MMC_MODE_HS | MMC_MODE_HS_52MHz |
			  MMC_MODE_HS200 | MMC_MODE_4BIT;

#if defined(CONFIG_TARGET_HI3531DV200) || defined(CONFIG_TARGET_HI3535AV100) ||\
	defined(CONFIG_TARGET_HI3521DV200) || defined(CONFIG_TARGET_HI3520DV500)
	if (get_mmc_bus_width() == MMC_BUS_WIDTH_8_BIT)
		host->host_caps |= MMC_MODE_HS400_ES |
			MMC_MODE_HS400 | MMC_MODE_8BIT;
#elif !(defined(CONFIG_TARGET_HI3516EV200) || defined(CONFIG_TARGET_HI3518EV300))
	host->host_caps |= MMC_MODE_HS400_ES | MMC_MODE_HS400 |
			   MMC_MODE_8BIT;
#endif
}

int hisi_sdhci_add_port(int index, uintptr_t regbase, u32 type)
{
	struct sdhci_host *host = NULL;

	if (type == MMC_TYPE_MMC)
		emmc_hardware_init();
	else
		sd_hardware_init();

	host = calloc(1, sizeof(struct sdhci_host));
	if (host == NULL) {
		puts("sdhci_host malloc fail!\n");
		return -ENOMEM;
	}

	host->name = "hisi-sdhci";
	host->index = index;
	host->type = type;
	host->ioaddr = (void *)regbase;
	host->quirks = 0;
	host->set_clock = hisi_mmc_set_clk;
	host->priv_init = hisi_mmc_priv_init;
	host->set_control_reg = hisi_mmc_set_ioconfig;
#ifdef MMC_SUPPORTS_TUNING
	host->execute_tuning = hisi_mmc_exec_tuning;
#endif
	hisi_sdhci_set_host_caps(host);
	add_sdhci(host, CONFIG_HISI_SDHCI_MAX_FREQ, MIN_FREQ);
	return 0;
}

static void print_mmcinfo(struct mmc *mmc)
{
	printf("MMC/SD Card:\n");
	printf("    MID:         0x%x\n", mmc->cid[0] >> 24); /* bit24 - 31 */
	printf("    Read Block:  %d Bytes\n", mmc->read_bl_len);
	printf("    Write Block: %d Bytes\n", mmc->write_bl_len);
	printf("    Chip Size:   %s Bytes (%s)\n",
			ultohstr(mmc->capacity),
			mmc->high_capacity ? "High Capacity" : "Low Capacity");
	printf("    Name:        \"%c%c%c%c%c\"\n",
			mmc->cid[0] & 0xff,           /* bit0   -  7 */
			(mmc->cid[1] >> 24),          /* bit24 - 32 */
			(mmc->cid[1] >> 16) & 0xff,   /* bit16 - 23 */
			(mmc->cid[1] >> 8) & 0xff,    /* bit8   - 15 */
			mmc->cid[1] & 0xff);          /* bit0   -  7 */

	printf("    Chip Type:   %s\n"
			"    Version:     %d.%d\n",
			IS_SD(mmc) ? "SD" : "MMC",
			EXTRACT_SDMMC_MAJOR_VERSION(mmc->version),
			EXTRACT_SDMMC_MINOR_VERSION(mmc->version));

	printf("    Speed:       %sHz\n", ultohstr(mmc->clock));
	printf("    Bus Width:   %dbit\n", mmc->bus_width);
	printf("    Mode:        %s\n", mmc->strobe_enhanced ? "HS400ES" :
			mmc->selected_mode == MMC_HS_400 ? "HS400" :
			mmc->selected_mode == MMC_HS_200 ? "HS200" : "HS");
}

int hisi_mmc_init(int dev_num)
{
	struct mmc *mmc = find_mmc_device(dev_num);
	int ret;

	if (mmc == NULL) {
		printf("mmc device not found!!\n");
		return -EINVAL;
	}

#if defined(CONFIG_TARGET_HI3531DV200) || defined(CONFIG_TARGET_HI3535AV100) || \
	defined(CONFIG_TARGET_HI3521DV200) || defined(CONFIG_TARGET_HI3520DV500)
	mmc->dev_num = dev_num;
	mmc->ocr_from_bootrom = dev_num == 0 ? get_ocr_from_bootrom() : 0;
	writel(0, REG_SAVE_HCS); /* clear flag reg */
	printf("mmc->ocr_from_bootrom 0x%08x\n", mmc->ocr_from_bootrom);
#endif
	ret = mmc_init(mmc);
	if (ret)
		return ret;

	if (!IS_SD(mmc)) {
		print_mmcinfo(mmc);
		return mmc_set_boot_config(mmc);
	}

	return 0;
}

void printf_mmc(int dev_num)
{
	struct mmc *mmc = find_mmc_device(dev_num);

	if (mmc != NULL)
		print_mmcinfo(mmc);
}
