/*
 * hifmc_common.c
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

/*****************************************************************************/
#include <hifmc_common.h>
#include <common.h>
#include <asm/io.h>
#include <errno.h>

#define BUFF_LEN			20

/*****************************************************************************/
static unsigned char hifmc_current_dev_type = FLASH_TYPE_DEFAULT;
static unsigned char hifmc_boot_dev_type = FLASH_TYPE_DEFAULT;

/*****************************************************************************/
unsigned char hifmc_ip_user;
unsigned char hifmc_cs_user[CONFIG_HIFMC_MAX_CS_NUM];

/*****************************************************************************/
void *get_hifmc_ip(void)
{
	return &hifmc_ip_user;
}
/*****************************************************************************/
unsigned char *get_cs_number(unsigned char cs)
{
	return hifmc_cs_user + cs;
}
/*****************************************************************************/
int hifmc_ip_ver_check(void)
{
	unsigned int hifmc_ip_ver;

	fmc_pr(FMC_INFO, "Check Flash Memory Controller v100 ...");
	hifmc_ip_ver = readl(CONFIG_HIFMC_REG_BASE + FMC_VERSION);
	if (hifmc_ip_ver != HIFMC_VER_100) {
		printf("\n");
		return -EFAULT;
	}
	fmc_pr(FMC_INFO, " Found\n");

	return 0;
}

/*****************************************************************************/
void hifmc_dev_type_switch(unsigned char type)
{
	unsigned int reg, spi_device_type, flash_type;
	const char *str[] = {"SPI nor", "SPI nand", "Nand", "Boot"};

	if (hifmc_current_dev_type == type)
		return;

	fmc_pr(BT_DBG, "\t|*-Start switch current device type\n");

	if (type > FLASH_TYPE_DEFAULT) {
		fmc_pr(BT_DBG, "\t||-Switch unknown device type %d\n", type);
		return;
	}

	if (hifmc_boot_dev_type == FLASH_TYPE_DEFAULT) {
		reg = readl((void *)(SYS_CTRL_REG_BASE + REG_SYSSTAT));
		fmc_pr(BT_DBG, "\t||-Get system STATUS[%#x]%#x\n",
		       SYS_CTRL_REG_BASE + REG_SYSSTAT, reg);
		hifmc_boot_dev_type = get_spi_device_type(reg);
		fmc_pr(BT_DBG, "\t||-Init boot device type to %s flash\n",
		       str[hifmc_boot_dev_type]);
	}

	if (type == FLASH_TYPE_DEFAULT)
		spi_device_type = hifmc_boot_dev_type;
	else
		spi_device_type = type;

	fmc_pr(BT_DBG, "\t||-Switch type to %s flash\n", str[type]);
	reg = readl((void *)(CONFIG_HIFMC_REG_BASE + FMC_CFG));
	fmc_pr(BT_DBG, "\t||-Get HIFMC CFG[%#x]%#x\n", FMC_CFG, reg);
	flash_type = (reg & FLASH_SEL_MASK) >> FLASH_SEL_SHIFT;
	if (spi_device_type != flash_type) {
		reg &= ~FLASH_SEL_MASK;
		reg |= fmc_cfg_flash_sel(spi_device_type);
		writel(reg, (void *)(CONFIG_HIFMC_REG_BASE + FMC_CFG));
		fmc_pr(BT_DBG, "\t||-Set HIFMC CFG[%#x]%#x\n", FMC_CFG, reg);
	}
	hifmc_current_dev_type = spi_device_type;

	fmc_pr(BT_DBG, "\t|*-End switch current device type\n");
}

/*****************************************************************************/
char *ulltostr(unsigned long long size)
{
	int ix;
	static char buffer[BUFF_LEN];
	char *fmt[] = {"%u", "%uK", "%uM", "%uG", "%uT"};
	/* 4 size type ,0x3ff Obtains the lower six bits*/
	for (ix = 0; (ix < 4) && !(size & 0x3FF) && size; ix++)
		size = (size >> 10); /* byte to kb, right left 10 */

	sprintf(buffer, fmt[ix], size);
	return buffer;
}

/*****************************************************************************/
void debug_register_dump(void)
{
	unsigned int ix;
	unsigned long base = CONFIG_HIFMC_REG_BASE;

	printf("Register dump:");
	/* 0x98  Register length , 4 is Byte */
	for (ix = 0; ix <= 0x98; ix += 0x04) {
		if (!(ix & 0x0F))
			printf("\n0x%08lX: ", base + ix);
		printf("%08X ", readl((void *)(uintptr_t)(base + ix)));
	}
	printf("\n");
}
/*****************************************************************************/
/* REG_SYSSTAT 0: 3 Bytes address boot mode; 1: 4Bytes address boot mode */
unsigned int get_fmc_boot_mode(void)
{
	unsigned int regval;
	unsigned int boot_mode;
	regval = readl(SYS_CTRL_REG_BASE + REG_SYSSTAT);
	boot_mode = get_spi_nor_addr_mode(regval);
	return boot_mode;
}
