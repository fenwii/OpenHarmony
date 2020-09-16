/*
 * hisi_spi.h
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
#ifndef __HIFMC100_SPI_H__
#define __HIFMC100_SPI_H__

#include <spi_flash.h>
#include <linux/mtd/mtd.h>

struct spi_flash *hifmc100_spi_nor_probe(struct mtd_info_ex **);
struct mtd_info_ex *hifmc100_get_spi_nor_info(struct spi_flash *);

#endif

