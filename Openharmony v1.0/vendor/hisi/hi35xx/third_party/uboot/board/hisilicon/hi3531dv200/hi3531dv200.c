/*
 * hi3531dv200.c
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
#include <sdhci.h>
#include <asm/armv8/mmu.h>
#include <command.h>
#include <hicpu_common.h>
#include <asm/mach-types.h>

static struct mm_region hi3531dv200_mem_map[] = {
	{
		.virt = 0x0UL,
		.phys = 0x0UL,
		.size = 0x05000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			PTE_BLOCK_NON_SHARE
	},
	{
		.virt = 0x05000000UL,
		.phys = 0x05000000UL,
		.size = 0x40000000UL - 0x05000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			PTE_BLOCK_NON_SHARE | PTE_BLOCK_PXN | PTE_BLOCK_UXN
	},
	{
		.virt = 0x40000000UL,
		.phys = 0x40000000UL,
		.size = 0x200000000UL, /* PHYS_SDRAM_1_SIZE */
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			PTE_BLOCK_INNER_SHARE
	},
	{
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = hi3531dv200_mem_map;
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
	__asm__ volatile ("1:\n"
			"subs %0, %1, #1\n"
			"bne 1b" : "=r" (loops) : "0" (loops));
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

#define PCIE0_CLK_SRST_CTRL     0x3A40
#define PCIE1_CLK_SRST_CTRL     0x3A60
#define PCIE_TST_SRST_REQ_SEL   25
static void __arch_pcie0_tst_srst_req_sel(void *crg_base)
{
	unsigned int reg_val;

	reg_val = readl(crg_base + PCIE0_CLK_SRST_CTRL);
	reg_val |= (0x1 << PCIE_TST_SRST_REQ_SEL);
	writel(reg_val, crg_base + PCIE0_CLK_SRST_CTRL);
}

static void __arch_pcie1_tst_srst_req_sel(void *crg_base)
{
	unsigned int reg_val;

	reg_val = readl(crg_base + PCIE1_CLK_SRST_CTRL);
	reg_val |= (0x1 << PCIE_TST_SRST_REQ_SEL);
	writel(reg_val, crg_base + PCIE1_CLK_SRST_CTRL);
}

#define PHY1_PORTA_CLK_SRST_CTRL        0x3B70
#define PHY1_PORTB_CLK_SRST_CTRL        0x3B90
#define PHY2_PORTA_CLK_SRST_CTRL        0x3BB0
#define PHY2_PORTB_CLK_SRST_CTRL        0x3BD0
#define PHY_TST_SRST_REQ                1
static void __arch_phy1_porta_unreset(void *crg_base)
{
	unsigned int reg_val;

	reg_val = readl(crg_base + PHY1_PORTA_CLK_SRST_CTRL);
	reg_val &= ~(0x1 << PHY_TST_SRST_REQ);
	writel(reg_val, crg_base + PHY1_PORTA_CLK_SRST_CTRL);
}

static void __arch_phy1_portb_unreset(void *crg_base)
{
	unsigned int reg_val;

	reg_val = readl(crg_base + PHY1_PORTB_CLK_SRST_CTRL);
	reg_val &= ~(0x1 << PHY_TST_SRST_REQ);
	writel(reg_val, crg_base + PHY1_PORTB_CLK_SRST_CTRL);
}

static void __arch_phy2_porta_unreset(void *crg_base)
{
	unsigned int reg_val;

	reg_val = readl(crg_base + PHY2_PORTA_CLK_SRST_CTRL);
	reg_val &= ~(0x1 << PHY_TST_SRST_REQ);
	writel(reg_val, crg_base + PHY2_PORTA_CLK_SRST_CTRL);
}

static void __arch_phy2_portb_unreset(void *crg_base)
{
	unsigned int reg_val;

	reg_val = readl(crg_base + PHY2_PORTB_CLK_SRST_CTRL);
	reg_val &= ~(0x1 << PHY_TST_SRST_REQ);
	writel(reg_val, crg_base + PHY2_PORTB_CLK_SRST_CTRL);
}

#define PHY1_PARA_SET_REG       0x1cc
#define PHY2_PARA_SET_REG       0x1d0
static void __arch_phy1_porta_para_config(void *misc_base)
{
	writel(0x11100, misc_base + PHY1_PARA_SET_REG);
	udelay(1);
	writel(0x11101, misc_base + PHY1_PARA_SET_REG);
	udelay(1);
	writel(0x11100, misc_base + PHY1_PARA_SET_REG);
	writel(0x0, misc_base + PHY1_PARA_SET_REG);
}

static void __arch_phy1_portb_para_config(void *misc_base)
{
	writel(0x19100, misc_base + PHY1_PARA_SET_REG);
	udelay(1);
	writel(0x19101, misc_base + PHY1_PARA_SET_REG);
	udelay(1);
	writel(0x19100, misc_base + PHY1_PARA_SET_REG);
	writel(0x0, misc_base + PHY1_PARA_SET_REG);
}

static void __arch_phy2_porta_para_config(void *misc_base)
{
	writel(0x11100, misc_base + PHY2_PARA_SET_REG);
	udelay(1);
	writel(0x11101, misc_base + PHY2_PARA_SET_REG);
	udelay(1);
	writel(0x11100, misc_base + PHY2_PARA_SET_REG);
	writel(0x0, misc_base + PHY2_PARA_SET_REG);
}

static void __arch_phy2_portb_para_config(void *misc_base)
{
	writel(0x19100, misc_base + PHY2_PARA_SET_REG);
	udelay(1);
	writel(0x19101, misc_base + PHY2_PARA_SET_REG);
	udelay(1);
	writel(0x19100, misc_base + PHY2_PARA_SET_REG);
	writel(0x0, misc_base + PHY2_PARA_SET_REG);
}

#define PCIE_MODE_SHIFT         16
#define PCIE_MODE_MASK          0x7
static int __arch_get_ups_mode(void)
{
	unsigned int val;
	unsigned int mode;

	val = readl((uintptr_t)(SYS_CTRL_REG_BASE + REG_SYSSTAT));
	mode = (val >> PCIE_MODE_SHIFT) & PCIE_MODE_MASK;

	return mode;
}

static void __arch_pcie_set_phy_para(void)
{
	unsigned int ups_mode;
	void *misc_base_addr = (void *)(uintptr_t)MISC_REG_BASE;
	void *crg_base = (void *)(uintptr_t)CRG_REG_BASE;

	ups_mode = __arch_get_ups_mode();
	switch (ups_mode) {
	case NUM_0:
		__arch_phy1_porta_unreset(crg_base);
		__arch_phy1_portb_unreset(crg_base);
		__arch_phy2_porta_unreset(crg_base);
		__arch_phy2_portb_unreset(crg_base);

		__arch_pcie0_tst_srst_req_sel(crg_base);
		__arch_pcie1_tst_srst_req_sel(crg_base);

		__arch_phy1_porta_para_config(misc_base_addr);
		__arch_phy1_portb_para_config(misc_base_addr);
		__arch_phy2_porta_para_config(misc_base_addr);
		__arch_phy2_portb_para_config(misc_base_addr);
		break;
	case NUM_1:
		__arch_phy1_porta_unreset(crg_base);
		__arch_phy2_porta_unreset(crg_base);
		__arch_phy2_portb_unreset(crg_base);

		__arch_pcie0_tst_srst_req_sel(crg_base);
		__arch_pcie1_tst_srst_req_sel(crg_base);

		__arch_phy1_porta_para_config(misc_base_addr);
		__arch_phy2_porta_para_config(misc_base_addr);
		__arch_phy2_portb_para_config(misc_base_addr);
		break;
	case NUM_2:
		__arch_phy2_porta_unreset(crg_base);
		__arch_phy2_portb_unreset(crg_base);

		__arch_pcie1_tst_srst_req_sel(crg_base);

		__arch_phy2_porta_para_config(misc_base_addr);
		__arch_phy2_portb_para_config(misc_base_addr);
		break;
	case NUM_3:
		__arch_phy2_porta_unreset(crg_base);
		__arch_phy2_portb_unreset(crg_base);

		__arch_pcie0_tst_srst_req_sel(crg_base);
		__arch_pcie1_tst_srst_req_sel(crg_base);

		__arch_phy2_porta_para_config(misc_base_addr);
		__arch_phy2_portb_para_config(misc_base_addr);
		break;
	case NUM_4:
		__arch_phy2_porta_unreset(crg_base);
		__arch_pcie1_tst_srst_req_sel(crg_base);
		__arch_phy2_porta_para_config(misc_base_addr);
		break;
	default:
		break;
	}
}

int is_auto_update(void)
{
#if (defined CONFIG_AUTO_USB_UPDATE)
	/* to add some judgement if neccessary */
	return 1; /* update enable */

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
#endif /* CONFIG_AUTO_UPDATE */

	__arch_pcie_set_phy_para();

	return 0;
}

int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gd->bd->bi_arch_number = MACH_TYPE_HI3531DV200;
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
	while(1) ;
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

#ifdef CONFIG_HIGMACV300_ETH
	rc = higmac_initialize(bis);
#endif
	return rc;
}

#ifdef CONFIG_GENERIC_MMC
int board_mmc_init(bd_t *bis)
{
	int ret = 0;
	int dev_num = 0;

#ifdef CONFIG_EMMC
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
	return ret;
}
#endif


