/*
 * soc.c
 *
 * Files related to system startup.
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

#include "soc.h"
#include <config.h>
#include <common.h>
#include <asm/arch/platform.h>
#include <asm/sections.h>
#include <asm/io.h>

void s_init(void)
{
	unsigned int blank_zone_start;

	blank_zone_start = get_blank_start();
	init_registers(blank_zone_start, 0);

#ifdef CONFIG_DDR_TRAINING_V2
	start_ddr_training(REG_BASE_SCTL);
#endif
}

void load_image(void)
{
	unsigned int len = (unsigned int)&__bss_start -
					(unsigned int)__image_copy_start;

	switch (get_boot_media()) {
#ifdef CONFIG_SUPPORT_EMMC_BOOT
	case BOOT_MEDIA_EMMC:
		emmc_boot_read(__image_copy_start, len);
		break;
#endif
	case BOOT_MEDIA_NAND:
	case BOOT_MEDIA_SPIFLASH:
		memcpy_32((void *)__image_copy_start, (void *)FMC_MEM_BASE, len);
		break;
	default:
		break;
	}
}

void enable_syscounter(int hz)
{
	writel(hz, REG_BASE_SYSCNT + CNTFID0);
	writel(1, REG_BASE_SYSCNT + CNTCR);
}
