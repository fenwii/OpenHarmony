/*
 * hi3519av100.c
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
#include <command.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include <spi_flash.h>
#include <linux/mtd/mtd.h>
#include <nand.h>
#include <netdev.h>
#include <mmc.h>
#include <sdhci.h>
#include <blk.h>
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
	/* [5:4] 00b - boot from spi device */
	case BOOT_FROM_SPI:
		boot_media = BOOT_MEDIA_SPIFLASH;
		break;
	/* [5:4] 01b - boot from spi nand device */
	case BOOT_FROM_SPI_NAND:
		boot_media = BOOT_MEDIA_NAND;
		break;
	/* [5:4] 01b - boot from Nand device */
	case BOOT_FROM_NAND:
		boot_media = BOOT_MEDIA_NAND;
		break;
	/* [5:4] 10b - boot from emmc */
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


#define UBOOT_DATA_ADDR     0x21000000UL
#define UBOOT_DATA_SIZE     0x80000UL
int data_to_spiflash(void)
{
	static struct spi_flash *flash = NULL;
	void *buf = NULL;
	unsigned int val;

	/* 0:bus  0:cs  1000000:max_hz  0x3:spi_mode */
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
#if defined(CONFIG_MMC)
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

#define REG_BASE_GPIO4          0x045f4000
#define GPIO4_3_DATA_OFST       0x20
#define GPIO_DIR_OFST       0x400

int is_bare_program(void)
{
	return 1;
}

#if (CONFIG_AUTO_UPDATE == 1)
int is_auto_update(void)
{
#if (defined CONFIG_AUTO_SD_UPDATE) || (defined CONFIG_AUTO_USB_UPDATE)
	/* to add some judgement if neccessary */
	unsigned int  val[NUM_3];

	writel(0, REG_BASE_GPIO4 + GPIO_DIR_OFST);

	val[NUM_0] = readl(REG_BASE_GPIO4 + GPIO4_3_DATA_OFST);
	if (val[NUM_0])
		return 0;

	udelay(10000); /* delay 10000 us */
	val[NUM_1] = readl(REG_BASE_GPIO4 + GPIO4_3_DATA_OFST);
	udelay(10000); /* delay 10000 us */
	val[NUM_2] = readl(REG_BASE_GPIO4 + GPIO4_3_DATA_OFST);
	udelay(10000); /* delay 10000 us */

	if (val[NUM_0] == val[NUM_1] && val[NUM_1] == val[NUM_2] && val[NUM_0] == NUM_0)
		return 1;    /* update enable */
	else
		return 0;

#else
	return 0;
#endif
}
#endif /* CONFIG_AUTO_UPDATE */

int misc_init_r(void)
{
#ifdef CONFIG_RANDOM_ETHADDR
	random_init_r();
#endif
	env_set("verify", "n");

	/* bare chip program flag */
	if (is_bare_program())
		bare_chip_program = 1;
	else
		bare_chip_program = 0;

#if (CONFIG_AUTO_UPDATE == 1)
	/* auto update flag */
	if (is_auto_update())
		auto_update_flag = 1;
	else
		auto_update_flag = 0;

#ifdef CFG_MMU_HANDLEOK
	dcache_stop();
#endif

#ifdef CFG_MMU_HANDLEOK
	dcache_start();
#endif

#endif

#if (CONFIG_AUTO_UPDATE == 1)
	if (auto_update_flag)
		do_auto_update();
#endif

	if (bare_chip_program && !auto_update_flag)
		save_bootdata_to_flash();
	return 0;
}

int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gd->bd->bi_arch_number = MACH_TYPE_HI3519AV100;
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
	 * Under uboot, 0xffffffff is set to load register,]
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

#ifdef CONFIG_HIGMACV300_ETH
	rc = higmac_initialize(bis);
#endif
	return rc;
}
#ifdef CONFIG_GENERIC_MMC
int board_mmc_init(bd_t *bis)
{
	int ret = 0;

#ifdef CONFIG_HISI_SDHCI

#if !defined(CONFIG_HIFMC) || defined(CONFIG_AUTO_SD_UPDATE)
	int dev_num = 0;
#endif

#ifndef CONFIG_HIFMC
	ret = hisi_sdhci_add_port(0, EMMC_BASE_REG, MMC_TYPE_MMC);
	if (!ret) {
		ret = hisi_mmc_init(dev_num);
		if (ret)
			printf("No EMMC device found !\n");
	}
	dev_num++;
#endif

#ifdef CONFIG_AUTO_SD_UPDATE
	if (is_auto_update()) {
		ret = hisi_sdhci_add_port(1, SDIO0_BASE_REG, MMC_TYPE_SD);
		if (ret)
			return ret;

		ret = hisi_mmc_init(dev_num);
		if (ret)
			printf("No SD device found !\n");
	}
#endif
#endif

	return ret;
}
#endif


#ifdef CONFIG_SECURE_SCHEME_ENABLE

/* macros to get secure register's offset address */
#define sec_rgn_map_ofst(region_idx) (0x1100 + 0x10 * (region_idx))
#define sec_rgn_map_ext_ofst(region_idx) (0x1200 + 0x10 * (region_idx))

#define sec_rgn_attrib_ofst(region_idx) (0x1104 + 0x10 * (region_idx))

#define sec_mid_wr_ofst(region_idx) (0x1108 + 0x10 * (region_idx))
#define sec_mid_wr_ext_ofst(region_idx) (0x1204 + 0x10 * (region_idx))

#define sec_mid_rd_ofst(region_idx) (0x110c + 0x10 * (region_idx))
#define sec_mid_rd_ext_ofst(region_idx) (0x1208 + 0x10 * (region_idx))

#define SEC_BYPASS_OFST         0x1004
#define SEC_INT_EN_OFST         0x1020

/* macros for register value */
#define SECURITY_ENABLE 0xff

#define SEC_INV_EN      (0x1 << 4)
#define SHARE_REGN_EN   (0xf)
#define SECUR_REGN_EN   (0xc)
#define NON_SEC_REGN_EN (0x3)

#define A53CPU0_MID     0xf
#define A53CPU1_MID     0x11
#define DSP_M0_MID      0x13
#define AVSP_M2_MID     0x18
#define DSP_M1_MID      0x1c

#define MID_HIGH_START_BIT  0x20
#define FMC_MID     0x21
#define EMMC_MID    0x28

#define IPCM_REGN_WR_MID_MASK   ((0x1 << A53CPU0_MID) | (0x1 << A53CPU1_MID))
#define IPCM_REGN_RD_MID_MASK   IPCM_REGN_WR_MID_MASK

#define DSP_REGN_WR_MID_MASK    ((0x1 << A53CPU0_MID) | (0x1 << DSP_M0_MID) | \
		(0x1 << AVSP_M2_MID) | (0x1 << DSP_M1_MID))
#define DSP_REGN_RD_MID_MASK    DSP_REGN_WR_MID_MASK

#define LITEOS_REGN_WR_MID_MASK (0x1 << A53CPU1_MID)
#define LITEOS_REGN_RD_MID_MASK LITEOS_REGN_WR_MID_MASK

#define LINUX_REGN_WR_MID_MASK  ((0x1 << A53CPU0_MID))
#define LINUX_REGN_RD_MID_MASK  LINUX_REGN_WR_MID_MASK

#define LINUX_REGN_WR_MID_HIGH_MASK ((0x1 << (FMC_MID - MID_HIGH_START_BIT)) | \
		(0x1 << (EMMC_MID - MID_HIGH_START_BIT)))
#define LINUX_REGN_RD_MID_HIGH_MASK LINUX_REGN_WR_MID_HIGH_MASK

#define REGN_CTRL_ENABLE        (0x1 << 31)

#define IPCM_REGN_HIGH_ADDR     0x2000  /* high 16 bit of address */
#define IPCM_REGN_SIZE          0x20    /* 0x20 * 64K Byte */

#define DSP_REGN_HIGH_ADDR      0x2020  /* high 16 bit of address */
#define DSP_REGN_SIZE           0x1e0   /* 0x1e0 * 64K Byte */

#define LITEOS_REGN_HIGH_ADDR   0x2200  /* high 16 bit of address */
#define LITEOS_REGN_SIZE        0x1000  /* 0x1000 * 64K Byte */

#define LINUX_REGN_HIGH_ADDR    0x3200  /* high 16 bit of address */
#define LINUX_REGN_SIZE         0x1000  /* 0x1000 * 64K Byte */

#define IPCM_DDR_REGN_IDX       1
#define DSP_DDR_REGN_IDX        2
#define LITEOS_DDR_REGN_IDX     3
#define LINUX_DDR_REGN_IDX      4

static void ipcm_tzasc_init(void)
{
	/* Set the share access authority */
	writel(SEC_INV_EN | SHARE_REGN_EN,
			DDRC0_REG_BASE + sec_rgn_attrib_ofst(IPCM_DDR_REGN_IDX));

	/* Set the master id mask of write command */
	writel(IPCM_REGN_WR_MID_MASK,
			DDRC0_REG_BASE + sec_mid_wr_ofst(IPCM_DDR_REGN_IDX));
	writel(0, DDRC0_REG_BASE + sec_mid_wr_ext_ofst(IPCM_DDR_REGN_IDX));

	/* Set the master id mask of read command */
	writel(IPCM_REGN_RD_MID_MASK,
			DDRC0_REG_BASE + sec_mid_rd_ofst(IPCM_DDR_REGN_IDX));
	writel(0, DDRC0_REG_BASE + sec_mid_rd_ext_ofst(IPCM_DDR_REGN_IDX));

	/* Set the start address and enable bit */
	writel(REGN_CTRL_ENABLE | IPCM_REGN_HIGH_ADDR,
			DDRC0_REG_BASE +  sec_rgn_map_ofst(IPCM_DDR_REGN_IDX));

	/* Set the size of ipcm ddr region */
	writel(IPCM_REGN_SIZE, DDRC0_REG_BASE + sec_rgn_map_ext_ofst(
				IPCM_DDR_REGN_IDX));
}

static void dsp_tzasc_init(void)
{
	/* Set the share access authority */
	writel(SEC_INV_EN | SHARE_REGN_EN,
			DDRC0_REG_BASE + sec_rgn_attrib_ofst(DSP_DDR_REGN_IDX));

	/* Set the master id mask of write command */
	writel(DSP_REGN_WR_MID_MASK,
			DDRC0_REG_BASE + sec_mid_wr_ofst(DSP_DDR_REGN_IDX));
	writel(0, DDRC0_REG_BASE + sec_mid_wr_ext_ofst(DSP_DDR_REGN_IDX));

	/* Set the master id mask of read command */
	writel(DSP_REGN_RD_MID_MASK,
			DDRC0_REG_BASE + sec_mid_rd_ofst(DSP_DDR_REGN_IDX));
	writel(0, DDRC0_REG_BASE + sec_mid_rd_ext_ofst(DSP_DDR_REGN_IDX));

	/* Set the start address and enable bit */
	writel(REGN_CTRL_ENABLE | DSP_REGN_HIGH_ADDR,
			DDRC0_REG_BASE + sec_rgn_map_ofst(DSP_DDR_REGN_IDX));

	/* Set the size of dsp ddr region */
	writel(DSP_REGN_SIZE, DDRC0_REG_BASE +
			sec_rgn_map_ext_ofst(DSP_DDR_REGN_IDX));
}

static void liteos_tzasc_init(void)
{
	/* Set the secure access authority */
	writel(SEC_INV_EN | SECUR_REGN_EN,
			DDRC0_REG_BASE + sec_rgn_attrib_ofst(LITEOS_DDR_REGN_IDX));

	/* Set the master id mask of write command */
	writel(LITEOS_REGN_WR_MID_MASK,
			DDRC0_REG_BASE + sec_mid_wr_ofst(LITEOS_DDR_REGN_IDX));
	writel(0, DDRC0_REG_BASE + sec_mid_wr_ext_ofst(LITEOS_DDR_REGN_IDX));

	/* Set the master id mask of read command */
	writel(LITEOS_REGN_RD_MID_MASK,
			DDRC0_REG_BASE + sec_mid_rd_ofst(LITEOS_DDR_REGN_IDX));
	writel(0, DDRC0_REG_BASE + sec_mid_rd_ext_ofst(LITEOS_DDR_REGN_IDX));

	/* Set the start address and enable bit */
	writel(REGN_CTRL_ENABLE | LITEOS_REGN_HIGH_ADDR,
			DDRC0_REG_BASE + sec_rgn_map_ofst(LITEOS_DDR_REGN_IDX));

	/* Set the size of dsp ddr region */
	writel(LITEOS_REGN_SIZE,
			DDRC0_REG_BASE + sec_rgn_map_ext_ofst(LITEOS_DDR_REGN_IDX));
}

static void linux_tzasc_init(void)
{
	/* Set the non-secure access authority */
	writel(SEC_INV_EN | NON_SEC_REGN_EN,
			DDRC0_REG_BASE + sec_rgn_attrib_ofst(LINUX_DDR_REGN_IDX));

	/* Set the master id mask of write command */
	writel(LINUX_REGN_WR_MID_MASK,
			DDRC0_REG_BASE + sec_mid_wr_ofst(LINUX_DDR_REGN_IDX));
	writel(LINUX_REGN_WR_MID_HIGH_MASK,
			DDRC0_REG_BASE + sec_mid_wr_ext_ofst(LINUX_DDR_REGN_IDX));

	/* Set the master id mask of read command */
	writel(LINUX_REGN_RD_MID_MASK,
			DDRC0_REG_BASE + sec_mid_rd_ofst(LINUX_DDR_REGN_IDX));
	writel(LINUX_REGN_RD_MID_HIGH_MASK,
			DDRC0_REG_BASE + sec_mid_rd_ext_ofst(LINUX_DDR_REGN_IDX));

	/* Set the start address and enable bit */
	writel(REGN_CTRL_ENABLE | LINUX_REGN_HIGH_ADDR,
			DDRC0_REG_BASE + sec_rgn_map_ofst(LINUX_DDR_REGN_IDX));

	/* Set the size of dsp ddr region */
	writel(LINUX_REGN_SIZE, DDRC0_REG_BASE + sec_rgn_map_ext_ofst(
				LINUX_DDR_REGN_IDX));
}

static int tzasc_init(void)
{
	/*
	 * Set IPCM ddr region attribution(0x20000000 ~ 0x20200000)*]
	 * */
	ipcm_tzasc_init();

	/*
	 * Set DSP ddr region attribution(0x20200000 ~ 0x22000000)*]
	 * */
	dsp_tzasc_init();

	/*
	 * Set Liteos ddr region attribution(0x22000000 ~ 0x10000000)*]
	 * */
	liteos_tzasc_init();

	/*
	 * Set Linux ddr region attribution(0x32000000 ~ 0x10000000)*]
	 * */
	linux_tzasc_init();

	/* Disable interrupt */
	writel(0, DDRC0_REG_BASE + SEC_INT_EN_OFST);

	/* Enable security */
	writel(SECURITY_ENABLE, DDRC0_REG_BASE + SEC_BYPASS_OFST);

	return 0;
}
#endif

static int start_a53cpu1(cmd_tbl_t *cmdtp,
		int flag, int argc, char *const argv[])
{
	unsigned int addr;

	if (argc < NUM_2)
		return CMD_RET_USAGE;

#ifdef CONFIG_SECURE_SCHEME_ENABLE
	tzasc_init();
#endif
	addr = simple_strtoul(argv[NUM_1], NULL, 16); /* 16:base */
	printf("## Starting A53 at 0x%08X ...\n", addr);
	/* start up a53 */
	{
		unsigned int start_phys = 0;
		unsigned int crg_phys = 0x04510000; /* 0x04510000:crg base */
		unsigned int regval;

		/* 0xe51ff004 = "ldr  pc, [pc, #-4]" */
		writel(0xe51ff004, start_phys);
		/* 0x4:next addr value will be the "go_a53" addr */
		writel(addr, (start_phys + 0x4));

		asm("dsb");
		asm("isb");

		/* clear the slave cpu reset */
		regval = readl(crg_phys + 0xcc);
		regval &= ~(0x1 << 5); /* 0x1 5:corel soft reset request */
		regval &= ~(0x1 << 25); /* 0x1 25:cluster1 soft reset request */
		writel(regval, (crg_phys + 0xcc));
	}
	return 0;
}

U_BOOT_CMD(
		go_a53cpu1, CONFIG_SYS_MAXARGS, 1,  start_a53cpu1,
		"start a53-cpu1 at address 'addr'",
		"addr [arg ...]\n    - start a53 application at address 'addr'\n"
		"      passing 'arg' as arguments"
	  );
