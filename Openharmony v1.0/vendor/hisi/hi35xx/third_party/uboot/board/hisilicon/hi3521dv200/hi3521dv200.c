/*
 * hi3521dv200.c
 *
 * The board init for hisilicon
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
#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include <spi_flash.h>
#include <linux/mtd/mtd.h>
#include <nand.h>
#include <netdev.h>
#include <mmc.h>
#include <asm/sections.h>
#include <sdhci.h>
#include <hicpu_common.h>
#include <asm/mach-types.h>

#ifndef CONFIG_SYS_DCACHE_OFF
void enable_caches(void)
{
	/* Enable D-cache. I-cache is already enabled in start.S */
	dcache_enable();
}
#endif
static int boot_media = BOOT_MEDIA_UNKNOWN;


#if defined(CONFIG_SHOW_BOOT_PROGRESS)
void show_boot_progress(int progress)
{
	printf("Boot reached stage %d\n", progress);
}
#endif

#define COMP_MODE_ENABLE ((unsigned int)0x0000EAEF)

static inline void delay(unsigned long loops)
{
	__asm__ volatile("1:\n"
			"subs %0, %1, #1\n"
			"bne 1b" : "=r"(loops) : "0"(loops));
}

/* get uboot start media. */
int get_boot_media(void)
{
    return boot_media;
}

int get_text_base(void)
{
    return CONFIG_SYS_TEXT_BASE;
}

static void boot_flag_init(void)
{
	unsigned int regval, boot_mode;

	/* get boot mode */
	regval = __raw_readl(SYS_CTRL_REG_BASE + REG_SYSSTAT);
	boot_mode = get_sys_boot_mode(regval);

	switch (boot_mode) {
		/* [3:2] 00b - boot from Spi Nor device */
		case BOOT_FROM_SPI:
			boot_media = BOOT_MEDIA_SPIFLASH;
			break;
		/* [3:2] 01b - boot from Spi Nand device */
		case BOOT_FROM_SPI_NAND:
			boot_media = BOOT_MEDIA_NAND;
			break;
		/* [3:2] 11b - boot from emmc */
		case BOOT_FROM_EMMC:
			boot_media = BOOT_MEDIA_EMMC;
			break;
		default:
			boot_media = BOOT_MEDIA_UNKNOWN;
			break;
	}
}

int board_early_init_f(void)
{
	return 0;
}

int is_auto_update(void)
{
#if (defined CONFIG_AUTO_USB_UPDATE)
	/* to add some judgement if neccessary */
	return 1;/* update enable */

#else
	return 0;
#endif
}

int misc_init_r(void)
{
#ifdef CONFIG_RANDOM_ETHADDR
	random_init_r();
#endif
	env_set("verify", "n");

#if (CONFIG_AUTO_UPDATE == 1)
	/* auto update flag */
	if (is_auto_update())
		do_auto_update();
#endif
	return 0;
}

int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gd->bd->bi_arch_number = MACH_TYPE_HI3521DV200;
	gd->bd->bi_boot_params = CFG_BOOT_PARAMS;

	boot_flag_init();

	return 0;
}

int dram_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gd->ram_size = PHYS_SDRAM_1_SIZE;
	return 0;
}

void reset_cpu(ulong addr)
{
	writel(0x12345678, REG_BASE_SCTL + REG_SC_SYSRES);
	while (1);
}

int timer_init(void)
{
	/*
	 **Under uboot, 0xffffffff is set to load register,
	 ** timer_clk = BUSCLK/2/256.
	 ** e.g. BUSCLK = 50M, it will roll back after 0xffffffff/timer_clk
	 ** = 43980s = 12hours
	 **/
	__raw_writel(0, CFG_TIMERBASE + REG_TIMER_CONTROL);
	__raw_writel(~0, CFG_TIMERBASE + REG_TIMER_RELOAD);

	/*32 bit, periodic*/
	__raw_writel(CFG_TIMER_CTRL, CFG_TIMERBASE + REG_TIMER_CONTROL);

	return 0;
}

int board_eth_init(bd_t *bis)
{
	int rc = 0;

#ifdef CONFIG_HISFV300_ETH
	rc = hieth_initialize(bis);
#endif

	return rc;
}

#ifdef CONFIG_GENERIC_MMC
int board_mmc_init(bd_t *bis)
{
	int ret = 0;

#ifdef CONFIG_HISI_SDHCI
#ifdef CONFIG_EMMC
	ret = hisi_sdhci_add_port(0, EMMC_BASE_REG, MMC_TYPE_MMC);
	if (!ret) {
		ret = hisi_mmc_init(0);
		if (ret)
			printf("No EMMC device found !\n");
	}
#endif

#ifdef CONFIG_AUTO_SD_UPDATE
	ret = hisi_sdhci_add_port(1, SDIO0_BASE_REG, MMC_TYPE_SD);
	if (ret)
		return ret;

	ret = hisi_mmc_init(0);
	if (ret)
		printf("No SD device found !\n");
#endif
#endif
	return ret;
}
#endif
#ifdef CONFIG_ARMV7_NONSEC
void smp_set_core_boot_addr(unsigned long addr, int corenr)
{
}

void smp_kick_all_cpus(void)
{
}

void smp_waitloop(unsigned previous_address)
{
}
#endif

