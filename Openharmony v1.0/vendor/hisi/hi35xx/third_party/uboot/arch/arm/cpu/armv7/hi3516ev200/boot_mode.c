/*
 * boot_mode.c
 *
 * Boot media related.
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

int get_boot_media(void)
{
	unsigned int reg_val, boot_mode, spi_device_mode;
	int boot_media;

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

