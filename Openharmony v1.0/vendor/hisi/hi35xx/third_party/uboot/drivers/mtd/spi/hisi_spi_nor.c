/*
 * hisi_spi_nor.c
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
#include <malloc.h>
#include <asm/io.h>
#include <spi_flash.h>
#include <errno.h>
#include <linux/mtd/mtd.h>
#include "hisi_spi.h"


/*****************************************************************************/
static struct spi_flash *spiflash;
static struct mtd_info_ex *spiinfo_ex;
/*****************************************************************************/

struct spi_flash *spi_flash_probe(unsigned int bus, unsigned int cs,
				unsigned int max_hz, unsigned int spi_mode)
{
	if (get_boot_media() != BOOT_MEDIA_SPIFLASH) {
		puts("Boot Media isn't SPI Nor\n");
		return NULL;
	}

	if (spiflash)
		return spiflash;

#ifdef CONFIG_HIFMC_SPI_NOR
	spiflash = hifmc100_spi_nor_probe(&spiinfo_ex);
	spiflash->erase_size = spiinfo_ex->erasesize;
#endif

	return spiflash;
}
/*****************************************************************************/

struct mtd_info_ex *get_spiflash_info(void)
{
	if (spiinfo_ex)
		return spiinfo_ex;

#ifdef CONFIG_HIFMC_SPI_NOR
	spiinfo_ex = hifmc100_get_spi_nor_info(spiflash);
#endif

	return spiinfo_ex;
}
/*****************************************************************************/

void spi_flash_free(struct spi_flash *flash)
{
}
/*****************************************************************************/

#ifdef CONFIG_SPI_BLOCK_PROTECT
void spi_flash_lock(unsigned char cmp, unsigned char level, unsigned char op)
{
	cmp = BP_CMP_BOTTOM;

	if (spiflash->lock)
		spiflash->lock(cmp, level, op);

	return;
}
/*****************************************************************************/
#endif /* CONFIG_SPI_BLOCK_PROTECT */

