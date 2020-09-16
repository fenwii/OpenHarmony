/*
 * hi3518ev300.c
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
int get_boot_media(void)
{
	unsigned int reg_val, boot_mode, spi_device_mode;
	int boot_media = BOOT_MEDIA_UNKNOWN;

	reg_val = readl(SYS_CTRL_REG_BASE + REG_SYSSTAT);
	boot_mode = get_sys_boot_mode(reg_val);

	switch (boot_mode) {
	case BOOT_FROM_SPI:
		spi_device_mode = get_spi_device_type(reg_val);
		if (spi_device_mode)
			boot_media = BOOT_MEDIA_NAND;
		else
			boot_media = BOOT_MEDIA_SPIFLASH;
		break;
	case BOOT_FROM_EMMC:
		boot_media = BOOT_MEDIA_EMMC;
		break;
	default:
		boot_media = BOOT_MEDIA_UNKNOWN;
		break;
	}

	return boot_media;
}

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


int get_text_base(void)
{
	return CONFIG_SYS_TEXT_BASE;
}

static void boot_flag_init(void)
{
	unsigned int reg, boot_mode, spi_device_mode;

	/* get boot mode */
	reg = __raw_readl(SYS_CTRL_REG_BASE + REG_SYSSTAT);
	boot_mode = get_sys_boot_mode(reg);

	switch (boot_mode) {
	case BOOT_FROM_SPI:
		spi_device_mode = get_spi_device_type(reg);
		if (spi_device_mode)
			boot_media = BOOT_MEDIA_NAND;
		else
			boot_media = BOOT_MEDIA_SPIFLASH;
		break;
	case BOOT_FROM_EMMC:    /* emmc mode */
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

#define UBOOT_DATA_ADDR     0x41000000UL
#define UBOOT_DATA_SIZE     0x80000UL
int data_to_spiflash(void)
{
	static struct spi_flash *flash = NULL;
	void *buf = NULL;

	unsigned int val;

	/* 0:bus; 0:cs; 1000000:max_hz; 0x3:spi_mode */
	flash = spi_flash_probe(0, 0, 1000000, 0x3);
	if (!flash) {
		printf("Failed to initialize SPI flash\n");
		return -1;  /* -1:failed */
	}

	/* erase the address range. */
	printf("Spi flash erase...\n");
	val = spi_flash_erase(flash, NUM_0, UBOOT_DATA_SIZE);
	if (val) {
		printf("SPI flash sector erase failed\n");
		return 1; /* 1:failed */
	}

	buf = map_physmem((unsigned long)UBOOT_DATA_ADDR,
			UBOOT_DATA_SIZE, MAP_WRBACK);
	if (!buf) {
		puts("Failed to map physical memory\n");
		return 1; /* 1:failed */
	}

	/* copy the data from RAM to FLASH */
	printf("Spi flash write...\n");
	val = flash->write(flash, NUM_0, UBOOT_DATA_SIZE, buf);
	if (val) {
		printf("SPI flash write failed, return %u\n",
				val);
		unmap_physmem(buf, UBOOT_DATA_SIZE);
		return 1; /* 1:failed */
	}

	unmap_physmem(buf, UBOOT_DATA_SIZE);
	return 0; /* 0:success */
}

int data_to_nandflash(void)
{
	struct mtd_info *nand_flash = NULL;
	void *buf = NULL;
	size_t length = UBOOT_DATA_SIZE;
	unsigned int val;

	nand_flash = nand_info[0];

	printf("Nand flash erase...\n");
	val = nand_erase(nand_flash, 0, UBOOT_DATA_SIZE);
	if (val) {
		printf("Nand flash erase failed\n");
		return 1;
	}

	buf = map_physmem((unsigned long)UBOOT_DATA_ADDR,
			UBOOT_DATA_SIZE, MAP_WRBACK);
	if (!buf) {
		puts("Failed to map physical memory\n");
		return 1;
	}

	printf("Nand flash write...\n");
	val = nand_write(nand_flash, 0, &length, buf);
	if (val) {
		printf("Nand flash write failed, return %u\n",
				val);
		unmap_physmem(buf, UBOOT_DATA_SIZE);
		return 1;
	}

	unmap_physmem(buf, UBOOT_DATA_SIZE);
	return 0;
}

int data_to_emmc(void)
{
	struct mmc *mmc = find_mmc_device(0);
	void *buf = NULL;

	if (!mmc)
		return 1;

	(void)mmc_init(mmc);

	buf = map_physmem((unsigned long)UBOOT_DATA_ADDR,
			UBOOT_DATA_SIZE, MAP_WRBACK);
	if (!buf) {
		puts("Failed to map physical memory\n");
		return 1;
	}

	printf("MMC write...\n");
	blk_dwrite(mmc_get_blk_desc(mmc), 0, (UBOOT_DATA_SIZE >> NUM_9), buf);
	unmap_physmem(buf, UBOOT_DATA_SIZE);
	return 0;
}
int save_bootdata_to_flash(void)
{
	unsigned int sd_update_flag = 0;
	int ret = 0;
	sd_update_flag = readl(REG_BASE_SCTL + REG_SC_GEN4);
	if (sd_update_flag == START_MAGIC) {
#if defined(CONFIG_HIFMC)
		if (boot_media == BOOT_MEDIA_SPIFLASH) {
			ret = data_to_spiflash();
			if (ret != 0)
				return ret;
		}
		if (boot_media == BOOT_MEDIA_NAND) {
			ret = data_to_nandflash();
			if (ret != 0)
				return ret;
		}
#endif
#if defined(CONFIG_SUPPORT_EMMC_BOOT)
		if (boot_media == BOOT_MEDIA_EMMC) {
			ret = data_to_emmc();
			if (ret != 0)
				return ret;
		}
#endif

		printf("update success!\n");
	}

	return 0;
}

int auto_update_flag = 0;
int bare_chip_program = 0;

#define REG_BASE_GPIO0          0x120b0000
#define GPIO0_0_DATA_OFST       0x4
#define GPIO_DIR_OFST       0x400

/** upgrade status register address */
#define UPGRADE_STATUS_REG_ADDR 0x120F0048

typedef enum tagUPGRADE_STATUS_E {
	UPGRADE_STATUS_IDLE = 0,
	UPGRADE_STATUS_PROCESSING,
	UPGRADE_STATUS_FINISH,
	UPGRADE_STATUS_BUTT
} upgrade_status_e;

int is_bare_program(void)
{
	return 1;
}

int is_auto_update(void)
{
#if (defined CONFIG_AUTO_SD_UPDATE) || (defined CONFIG_AUTO_USB_UPDATE)
	/* to add some judgement if neccessary */
	unsigned int  val[NUM_3];

	unsigned int *puregval = (unsigned int *)UPGRADE_STATUS_REG_ADDR;
	if (((*puregval) & (UPGRADE_STATUS_PROCESSING)) != 0)
		return 1; /* update enable */

	writel(0, REG_BASE_GPIO0 + GPIO_DIR_OFST);

	val[NUM_0] = readl(REG_BASE_GPIO0 + GPIO0_0_DATA_OFST);
	if (val[NUM_0])
		return 0;

	udelay(10000); /* delay 10000 us */
	val[NUM_1] = readl(REG_BASE_GPIO0 + GPIO0_0_DATA_OFST);
	udelay(10000); /* delay 10000 us */
	val[NUM_2] = readl(REG_BASE_GPIO0 + GPIO0_0_DATA_OFST);
	udelay(10000); /* delay 10000 us */

	if (val[NUM_0] == val[NUM_1] && val[NUM_1] == val[NUM_2] && val[NUM_0] == NUM_0)
		return 1;    /* update enable */
	else
		return 0;

#else
	return 0;
#endif
}

void select_upgrade_dev(void)
{
#ifdef CONFIG_EMMC
	unsigned int uval = readl(UPGRADE_STATUS_REG_ADDR);
	unsigned int stor_dev = 0;
	unsigned int stor_paration = 0;
	stor_dev = (uval >> 16) & 0x03; /* 16,0x03: store dev */
	stor_paration = (uval >> 18) & 0x1f; /* 18,0x1f: store paration */
	if (((uval) & (UPGRADE_STATUS_PROCESSING)) != NUM_0) {
		/* the upgrade startup by linux application */
		if (stor_dev == NUM_0) {
			/* emmc */
			target_dev = NUM_0;
			target_paratition = stor_paration;
		} else {
			/* sd */
			target_dev = NUM_1;
		}
	} else {
		/* the upgrade startup by upgrade key on the board, os defaule upgrade style */
		target_dev = NUM_1;
	}

	printf("update dev is %d: paratition is %d\n", target_dev, target_paratition);
#endif
	return;
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
		auto_update_flag = NUM_1;
	else
		auto_update_flag = NUM_0;

	/* bare chip program flag */
	if (is_bare_program())
		bare_chip_program = NUM_1;
	else
		bare_chip_program = NUM_0;

#ifdef CFG_MMU_HANDLEOK
	dcache_stop();
#endif

#ifdef CFG_MMU_HANDLEOK
	dcache_start();
#endif

#endif

#if (CONFIG_AUTO_UPDATE == 1)
	int update_flag = -1; /* -1:default failed */
	if (auto_update_flag) {
		select_upgrade_dev();
		update_flag = do_auto_update();
		unsigned int *puregval = (unsigned int *)UPGRADE_STATUS_REG_ADDR;
		if (((*puregval) & (UPGRADE_STATUS_PROCESSING)) && (update_flag == NUM_0)) {
			printf("upgrade status: finish\n");
			*puregval = UPGRADE_STATUS_FINISH;
		}
	}
	if (bare_chip_program && !auto_update_flag)
		save_bootdata_to_flash();
	if (update_flag == NUM_0)
		do_reset(NULL, 0, 0, NULL);
#endif
	return 0;
}

int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gd->bd->bi_arch_number = MACH_TYPE_HI3518EV300;
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
	/* 0x12345678:writing any value will cause a reset. */
	writel(0x12345678, REG_BASE_SCTL + REG_SC_SYSRES);
	while (1);
}

int timer_init(void)
{
	/*
	 * Under uboot, 0xffffffff is set to load register,
	 * timer_clk equals BUSCLK/2/256.
	 * e.g. BUSCLK equals 50M, it will roll back after 0xffffffff/timer_clk
	 * 43980s equals 12hours
	 */
	__raw_writel(0, CFG_TIMERBASE + REG_TIMER_CONTROL);
	__raw_writel(~0, CFG_TIMERBASE + REG_TIMER_RELOAD);

	/* 32 bit, periodic */
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

#ifndef CONFIG_HIFMC
	ret = hisi_sdhci_add_port(0, EMMC_BASE_REG, MMC_TYPE_MMC);
	if (!ret) {
		ret = hisi_mmc_init(0);
		if (ret)
			printf("No EMMC device found !\n");
	}
#else

#ifdef CONFIG_AUTO_SD_UPDATE
	ret = hisi_sdhci_add_port(0, SDIO0_BASE_REG, MMC_TYPE_SD);
	if (ret)
		return ret;

	ret = hisi_mmc_init(0);
	if (ret)
		printf("No SD device found !\n");
#endif

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

