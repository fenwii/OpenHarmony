/*
 * hifmc_spi_nor_ids.c
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
#include <common.h>
#include <asm/io.h>
#include <linux/mtd/mtd.h>
#include "hifmc100.h"

#if defined(CONFIG_TARGET_HI3562V100) || defined(CONFIG_TARGET_HI3566V100)
#define CONFIG_AUTOMOTIVE_GRADE
#endif
/*****************************************************************************/
struct spi_nor_info *spiinfo;

/*****************************************************************************/
set_read_std(0, INFINITE, 33);
set_read_std(0, INFINITE, 40);
set_read_std(0, INFINITE, 50);
set_read_std4b(0, INFINITE, 50);
set_read_std(0, INFINITE, 54);
set_read_std4b(0, INFINITE, 54);
set_read_std(0, INFINITE, 55);
set_read_std4b(0, INFINITE, 55);
set_read_std(0, INFINITE, 66);
set_read_std4b(0, INFINITE, 66);
set_read_std(0, INFINITE, 80);

set_read_fast(1, INFINITE, 55);
set_read_fast(1, INFINITE, 80);
set_read_fast4b(1, INFINITE, 80);
set_read_fast(1, INFINITE, 86);
set_read_fast(1, INFINITE, 100);
set_read_fast(1, INFINITE, 104);
set_read_fast4b(1, INFINITE, 104);
set_read_fast(1, INFINITE, 108);
set_read_fast4b(1, INFINITE, 108);
set_read_fast(1, INFINITE, 112);
set_read_fast(1, INFINITE, 133);
set_read_fast4b(1, INFINITE, 133);

set_read_dual(1, INFINITE, 55);
set_read_dual(1, INFINITE, 64);
set_read_dual(1, INFINITE, 80);
set_read_dual4b(1, INFINITE, 80);
set_read_dual(1, INFINITE, 84);
set_read_dual(1, INFINITE, 104);
set_read_dual4b(1, INFINITE, 104);
set_read_dual(1, INFINITE, 108);
set_read_dual4b(1, INFINITE, 108);
set_read_dual(1, INFINITE, 112);
set_read_dual(1, INFINITE, 133);
set_read_dual4b(1, INFINITE, 133);

set_read_dual_addr(1, INFINITE, 80);
set_read_dual_addr4b(1, INFINITE, 80);
set_read_dual_addr4b(1, INFINITE, 108);
set_read_dual_addr(2, INFINITE, 84);
set_read_dual_addr4b(2, INFINITE, 84);
set_read_dual_addr(2, INFINITE, 108);
set_read_dual_addr(1, INFINITE, 104);
set_read_dual_addr4b(1, INFINITE, 104);
set_read_dual_addr(1, INFINITE, 108);
set_read_dual_addr(1, INFINITE, 112);
set_read_dual_addr(1, INFINITE, 133);
set_read_dual_addr4b(1, INFINITE, 133);
set_read_dual_addr4b(2, INFINITE, 133);

set_read_quad(1, INFINITE, 80);
set_read_quad4b(1, INFINITE, 80);
set_read_quad(1, INFINITE, 84);
set_read_quad(1, INFINITE, 104);
set_read_quad4b(1, INFINITE, 104);
set_read_quad(1, INFINITE, 108);
set_read_quad4b(1, INFINITE, 108);
set_read_quad(1, INFINITE, 112);
set_read_quad(1, INFINITE, 133);
set_read_quad4b(1, INFINITE, 133);

set_read_quad_addr(3, INFINITE, 80);
set_read_quad_addr4b(3, INFINITE, 80);
set_read_quad_addr(5, INFINITE, 84);
set_read_quad_addr4b(5, INFINITE, 84);
set_read_quad_addr(5, INFINITE, 108);
set_read_quad_addr(3, INFINITE, 104);
set_read_quad_addr4b(3, INFINITE, 104);
set_read_quad_addr(3, INFINITE, 108);
set_read_quad_addr4b(3, INFINITE, 108);
set_read_quad_addr4b(5, INFINITE, 125);
set_read_quad_addr(3, INFINITE, 112);
set_read_quad_addr(3, INFINITE, 133);
set_read_quad_addr(3, INFINITE, 72);
set_read_quad_addr4b(3, INFINITE, 133);

#ifdef CONFIG_DTR_MODE_SUPPORT
set_read_quad_dtr(8, INFINITE, 80);
set_read_quad_dtr4b(10, INFINITE, 100);
set_read_quad_dtr(10, INFINITE, 100);
#endif
/*****************************************************************************/
set_write_std(0, 256, 33);
set_write_std(0, 256, 55);
set_write_std(0, 256, 80);
set_write_std4b(0, 256, 80);
set_write_std(0, 256, 86);
set_write_std(0, 256, 100);
set_write_std(0, 256, 104);
set_write_std4b(0, 256, 104);
set_write_std(0, 256, 108);
set_write_std(0, 256, 112);
set_write_std(0, 256, 133);
set_write_std4b(0, 256, 120);
set_write_std4b(0, 256, 133);

set_write_dual(0, 256, 75);
set_write_dual4b(0, 256, 75);
set_write_dual(0, 256, 108);
set_write_dual4b(0, 256, 133);

set_write_dual_addr(0, 256, 75);
set_write_dual_addr4b(0, 256, 75);
set_write_dual_addr(0, 256, 108);
set_write_dual_addr4b(0, 256, 133);

set_write_quad(0, 256, 55);
set_write_quad(0, 256, 80);
set_write_quad4b(0, 256, 80);
set_write_quad(0, 256, 104);
set_write_quad(0, 256, 108);
set_write_quad(0, 256, 112);
set_write_quad(0, 256, 133);
set_write_quad4b(0, 256, 133);

/* As Micron MT25Q(and MIXC) and N25Q have different QUAD I/O write code,
 * but they have the same ID, so we cannot compatiable it. User can open
 * by theirselves. */
set_write_quad_addr(0, 256, 33);
set_write_quad_addr(0, 256, 80);
set_write_quad_addr(0, 256, 104);
set_write_quad_addr4b(0, 256, 104);
set_write_quad_addr(0, 256, 108);
set_write_quad_addr4b(0, 256, 108);
set_write_quad_addr4b(0, 256, 120);
set_write_quad_addr(0, 256, 133);
set_write_quad_addr4b(0, 256, 133);
/*****************************************************************************/
set_erase_sector_64k(0, _64K, 33);
set_erase_sector_64k(0, _64K, 55);
set_erase_sector_64k(0, _64K, 50);
set_erase_sector_64k(0, _64K, 80);
set_erase_sector_64k4b(0, _64K, 80);
set_erase_sector_64k(0, _64K, 86);
set_erase_sector_64k(0, _64K, 100);
set_erase_sector_64k(0, _64K, 104);
set_erase_sector_64k4b(0, _64K, 104);
set_erase_sector_64k(0, _64K, 108);
set_erase_sector_64k4b(0, _64K, 108);
set_erase_sector_64k4b(0, _64K, 120);
set_erase_sector_64k(0, _64K, 112);
set_erase_sector_64k(0, _64K, 133);
set_erase_sector_64k4b(0, _64K, 133);

/*****************************************************************************/
#include "hifmc100_spi_general.c"
static struct spi_drv spi_driver_general = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_general_entry_4addr,
	.qe_enable = spi_general_qe_enable,
};

static struct spi_drv spi_driver_no_qe = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_general_entry_4addr,
	.qe_enable = spi_do_not_qe_enable,
};

#include "hifmc100_spi_s25fl256s.c"
static struct spi_drv spi_driver_s25fl256s = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_s25fl256s_entry_4addr,
	.qe_enable = spi_general_qe_enable,
};

#include "hifmc100_spi_w25q256fv.c"
static struct spi_drv spi_driver_w25q256fv = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_w25q256fv_entry_4addr,
	.qe_enable = spi_w25q256fv_qe_enable,
};

#include "hifmc100_spi_mx25l25635e.c"
static struct spi_drv spi_driver_mx25l25635e = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_general_entry_4addr,
	.qe_enable = spi_mx25l25635e_qe_enable,
#ifdef CONFIG_DTR_MODE_SUPPORT
	.dtr_set_device =
	spi_mxic_output_driver_strength_set,
#endif
};

static struct spi_drv spi_driver_f25l64q = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_general_entry_4addr,
	.qe_enable = spi_mx25l25635e_qe_enable,
};

#include "hifmc100_spi_gd25qxxx.c"
static struct spi_drv spi_driver_gd25qxxx = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_general_entry_4addr,
	.qe_enable = spi_gd25qxxx_qe_enable,
};

#include "hifmc100_spi_micron.c"
static struct spi_drv spi_driver_micron = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_micron_entry_4addr,
	.qe_enable = spi_do_not_qe_enable,
};

#include "hifmc100_spi_xtx.c"
static struct spi_drv spi_driver_xtx = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_general_entry_4addr,
	.qe_enable = spi_xtx_qe_enable,
};

#include "hifmc100_spi_puya.c"
static struct spi_drv spi_driver_puya = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_puya_entry_4addr,
	.qe_enable = spi_puya_qe_enable,
};


#include "hifmc100_spi_issi.c"
static struct spi_drv spi_driver_issi = {
	.wait_ready = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.entry_4addr = spi_s25fl256s_entry_4addr,
	.qe_enable = spi_issi_qe_enable,
};
/*****************************************************************************/
#define SPI_NOR_ID_TBL_VER     "1.0"

/* ****** SPI Nor ID Table ****************************************************
 * 	Manufacturer     Chip Name           Chipsize    Block   Vol  Operation
 * 1.0  Macronix/MXIC   MX25L1606E		2M	64K 	3V3
 *      Macronix/MXIC   MX25V1635F		2M	64K 	3V3
 *      Macronix/MXIC   MX25L6436F		8M	64K 	3V3
 *      Macronix/MXIC   MX25R6435F	  8M	64K  1V8/3V3 Add 14chips
 *      Macronix/MXIC   MX25U6435F		8M	64K 	1V8
 *      Macronix/MXIC   MX25U12835F		16M	64K     1V8
 *      Macronix/MXIC   MX25F128XXX		16M	64K     3V3
 *      Macronix/MXIC   MX25U25635F/45G     	32M	64K 	1V8 25645G-DTR
 *      Macronix/MXIC   MX25L(256/257)      	32M	64K     3V3 25645G-DTR
 *      Macronix/MXIC   MX25U51245G		64M	64K 	1V8 51245G-DTR
 *      Macronix/MXIC   MX25L51245G		64M	64K	3V3
 * 	Macronix/MXIC	MX66U1G45GM		128M	64K	1V8
 *      Spansion    	S25FL129P1		16M	64K 	3V3
 *      Spansion    	S25FL256S		32M	64K 	3V3
 *      Micron      	N25Q064A		8M	64K     3V3
 *      Micron      	N25QL064A		8M	64K     3V3
 *      Micron      	N25Q128A11/MT25QU128AB  16M	64K     1V8
 *      Micron      	N25QL128A		16M	64K     3V3
 *      Micron      	MT25QU256A		32M	64K     1V8
 *      Micron      	MT25QL256A		32M	64K     3V3
 *      Winbond     	W25Q16(B/C)V/S25FL016K  2M	64K     3V3
 *      Winbond     	W25Q32(B/F)V        	4M	64K     3V3
 *      Winbond     	W25Q32FW		4M	64K     1V8
 *      Winbond     	W25Q64FW		8M	64K     1V8
 *      Winbond     	W25Q64FV(SPI)/W25Q64JV_IQ   8M	64K     3V3
 *      Winbond     	W25Q128FW		16M	64K     1V8
 *      Winbond     	W25Q128(B/F)V       	16M	64K     3V3
 *      Winbond     	W25Q128JV_IM        	16M	64K     3V3 DTR
 *      Winbond     	W25Q256JWEIQ        	32M	64K     1V8
 *      Winbond         W25Q256JWFIM        	32M	64K     1V8
 *      Winbond         W25Q256JV-IQ		32M	64K     3V3
 *      ESMT/CFEON  	EN25Q32B		4M	64K     3V3
 *      ESMT/CFEON  	EN25Q64			8M	64K     3V3
 *      ESMT/CFEON  	EN25Q128		16M	64K     3V3
 *      ESMT/CFEON  	F25L64QA		8M	64K     3V3
 *      GD		GD25Q64			8M	64K     3V3
 *      GD		GD25LQ128		16M	64K     1V8
 *      GD		GD25Q128		16M	64K     3V3
 *      GD		GD25LQ64C		8M	64K     1V8
 *      GD		GD25Q32			4M	64K     3V3
 *      GD		GD25Q16C		2M	64K     3V3
 *      Paragon     	PN25F16S		2M	64K     3V3
 *      Paragon     	PN25F32S		4M	64K     3V3
 *      XMC		XM25QH64AHIG        	8M	64K 	3V3
 *      XMC		XM25QH128A		16M	64K 	3V3
 *      XMC		XM25QH128B		16M	64K 	3V3
 *	XTX		XT25F128BSSI/HGU	16M	64K	3V3
 *	XTX		XM25QH64		8M	64K	3V3
 *      Puya		P25Q128H-SUH-IT		16M	64K	3V3
 *      FM		FM25Q64-SOB-T-G		8M	64K	3V3
 *      FM		FM25Q128-SOB-T-G	16M	64K	3V3
 *      HUAHONG		H25S64			8M	64K	3V3
 *      HUAHONG		H25S128			16M	64K	3V3
 *	ISSI		IS25WP512M-RMLA3	64M	64k	1V8
 *****************************************************************************/
static struct spi_nor_info hifmc_spi_nor_info_table[] = {
	/* name     id  id_len  chipsize(Bytes) erasesize  */
	{
		"MX25L1606E",  {0xc2, 0x20, 0x15}, 3, _2M,    _64K, 3,
		{
			/* dummy clock:1 byte, read size:INFINITE bytes,
			 * clock frq:33MHz */
			&read_std(0, INFINITE, 33), /* 33MHz */
			&read_fast(1, INFINITE, 86), /* 86MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			0
		},
		{
			/* dummy clock:0 byte, write size:256 bytes,
			 * clock frq:86MHz */
			&write_std(0, 256, 86), /* 86MHz */
			0
		},
		{
			/* dummy clock:0byte, erase size:64K,
			 * clock frq:86MHz */
			&erase_sector_64k(0, _64K, 86), /* 86MHz */
			0
		},
		&spi_driver_no_qe,
	},

	{
		"MX25L6436F",  {0xc2, 0x20, 0x17}, 3, _8M,    _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 133), /* 133MHz */
			&read_dual(1, INFINITE, 133), /* 133MHz */
			&read_dual_addr(1, INFINITE, 133), /* 133MHz */
			&read_quad(1, INFINITE, 133), /* 133MHz */
			&read_quad_addr(3, INFINITE, 133), /* 133MHz */
			0
		},

		{
			&write_std(0, 256, 133), /* 133MHz */
			&write_quad_addr(0, 256, 133), /* 133MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 133), /* 133MHz */
			0
		},
		&spi_driver_mx25l25635e,
	},
	/* MX25L51245G  3.3V */
	{
		"MX25L51245G",  {0xc2, 0x20, 0x1a}, 3, _64M,    _64K, 4,
		{
			&read_std4b(0, INFINITE, 66),
			&read_fast4b(1, INFINITE, 133),
			&read_dual4b(1, INFINITE, 133),
			&read_dual_addr4b(1, INFINITE, 133),
			&read_quad4b(1, INFINITE, 133),
			&read_quad_addr4b(3, INFINITE, 133),
			0
		},

		{
			&write_std4b(0, 256, 133),
			&write_quad_addr4b(0, 256, 133),
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 133),
			0
		},
		&spi_driver_mx25l25635e,
	},

	/* MX25V1635F  3.3V */
	{
		"MX25V1635F",  {0xc2, 0x23, 0x15}, 3, _2M,    _64K, 3,
		{
			&read_std(0, INFINITE, 33), /* 33MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(3, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 33), /* 33MHz */
			&write_quad_addr(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_mx25l25635e,
	},

	/* MX25R6435F Wide Voltage Range 1.65~3.6V */
	{
		"MX25R6435F", {0xc2, 0x28, 0x17}, 3, _8M, _64K, 3,
		{
			&read_std(0, INFINITE, 33), /* 33MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(3, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 33), /* 33MHz */
			&write_quad_addr(0, 256, 33), /* 33MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 33), /* 33MHz */
			0
		},
		&spi_driver_mx25l25635e,
	},

	/* MX25U1633F, 1.65-2.0V */
	{
		"MX25U1633F", {0xc2, 0x25, 0x35}, 3, _2M, _64K, 3,
		{
			&read_std(0, INFINITE, 33), /* 33MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(3, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 33), /* 33MHz */
			&write_quad_addr(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_mx25l25635e,
	},

	/* MX25U6435F, 1.65-2.0V */
	{
		"MX25U6435F", {0xc2, 0x25, 0x37}, 3, _8M, _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 108), /* 108MHz */
			&read_dual(1, INFINITE, 108), /* 108MHz */
			&read_dual_addr(1, INFINITE, 108), /* 108MHz */
			&read_quad(1, INFINITE, 108), /* 108MHz */
			&read_quad_addr(3, INFINITE, 108), /* 108MHz */
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad_addr(0, 256, 108), /* 108MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 108), /* 108MHz */
			0
		},
		&spi_driver_mx25l25635e,
	},

	/* MX25U12835F, 1.65-2.0V */
	{
		"MX25U12835F", {0xc2, 0x25, 0x38}, 3, _16M, _64K, 3,
		{
			&read_std(0, INFINITE, 55), /* 55MHz */
			&read_fast(1, INFINITE, 108), /* 108MHz */
			&read_dual(1, INFINITE, 108), /* 108MHz */
			&read_dual_addr(1, INFINITE, 108), /* 108MHz */
			&read_quad(1, INFINITE, 108), /* 108MHz */
			&read_quad_addr(3, INFINITE, 108), /* 108MHz */
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad_addr(0, 256, 108), /* 108MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 108), /* 108MHz */
			0
		},
		&spi_driver_mx25l25635e,
	},

	{
		"MX25L128XX", {0xc2, 0x20, 0x18}, 3, _16M, _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_dual_addr(1, INFINITE, 104), /* 104MHz */
			&read_quad(1, INFINITE, 104), /* 104MHz */
			&read_quad_addr(3, INFINITE, 104), /* 104MHz */
#ifdef CONFIG_DTR_MODE_SUPPORT
			&read_quad_dtr(10, INFINITE, 100 /* 84 */), /* 100MHz */
#endif
			0
		},

		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad_addr(0, 256, 104), /* 104MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_mx25l25635e,
	},

	/* MX25U25635F/MX25U25645G, 1.65-2.0V */
	{
		"MX25U25635F/45G", {0xc2, 0x25, 0x39}, 3, _32M, _64K, 4,
		{
			&read_std4b(0, INFINITE, 55), /* 55MHz */
			&read_fast4b(1, INFINITE, 108), /* 108MHz */
			&read_dual4b(1, INFINITE, 108), /* 108MHz */
			&read_dual_addr4b(1, INFINITE, 108), /* 108MHz */
			&read_quad4b(1, INFINITE, 108), /* 108MHz */
			&read_quad_addr4b(3, INFINITE, 108), /* 108MHz */
#ifdef CONFIG_DTR_MODE_SUPPORT
			&read_quad_dtr4b(10, INFINITE, 100), /* 100MHz */
#endif
			0
		},

		{
			&write_std4b(0, 256, 80), /* 80MHz */
			&write_quad_addr4b(0, 256, 108), /* 108MHz */
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 108), /* 108MHz */
			0
		},
		&spi_driver_mx25l25635e,
	},

	/* MX25L25635F/MX25L25645G/MX25L25735F/MX25L25635E, 3.3V */
	{
		"MX25L(256/257)XX",
		{0xc2, 0x20, 0x19}, 3, _32M, _64K, 4,
		{
			&read_std4b(0, INFINITE, 50), /* 50MHz */
			&read_fast4b(1, INFINITE, 80 /* 84 */), /* 80MHz */
			&read_dual4b(1, INFINITE, 80 /* 84 */), /* 80MHz */
			&read_dual_addr4b(1, INFINITE, 80 /* 84 */), /* 80MHz */
			&read_quad4b(1, INFINITE, 80 /* 84 */), /* 80MHz */
			&read_quad_addr4b(3, INFINITE, 80 /* 84 */), /* 80MHz */
#ifdef CONFIG_DTR_MODE_SUPPORT
			&read_quad_dtr4b(10, INFINITE, 100 /* 84 */), /* 100MHz */
#endif
			0
		},

		{
			&write_std4b(0, 256, 120 /* 133 */), /* 120MHz */
			&write_quad_addr4b(0, 256, 120 /* 133 */), /* 120MHz */
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 120 /* 133 */), /* 120MHz */
			0
		},
		&spi_driver_mx25l25635e,
	},

	/* MX25U51245G, 1.65-2.0V */
	{
		"MX25U51245G", {0xc2, 0x25, 0x3a}, 3, _64M, _64K, 4,
		{
			&read_std4b(0, INFINITE, 66), /* 66MHz */
			&read_fast4b(1, INFINITE, 104), /* 104MHz */
			&read_dual4b(1, INFINITE, 104), /* 104MHz */
			&read_dual_addr4b(1, INFINITE, 104), /* 104MHz */
			&read_quad4b(1, INFINITE, 104), /* 104MHz */
			&read_quad_addr4b(3, INFINITE, 104), /* 104MHz */
#ifdef CONFIG_DTR_MODE_SUPPORT
			&read_quad_dtr4b(10, INFINITE, 100), /* 100MHz */
#endif
			0
		},

		{
			&write_std4b(0, 256, 104), /* 104MHz */
			&write_quad_addr4b(0, 256, 104), /* 104MHz */
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_mx25l25635e,
	},
	/* MX66U1G45GM, 1.65-2.0V */
	{
		"MX66U1G45GM", {0xc2, 0x25, 0x3b}, 3, _128M, _64K, 4,
		{
			&read_std4b(0, INFINITE, 50),
			&read_fast4b(1, INFINITE, 133),
			&read_dual4b(1, INFINITE, 133),
			&read_dual_addr4b(1, INFINITE, 133),
			&read_quad4b(1, INFINITE, 133),
			&read_quad_addr4b(3, INFINITE, 133),
			0
		},

		{
			&write_std4b(0, 256, 133),
			&write_quad_addr4b(0, 256, 133),
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 133),
			0
		},
		&spi_driver_mx25l25635e,
	},
	/* Spansion/Cypress  S25FL129P1 3.3V */
	{
		"S25FL129P1",
		{0x01, 0x20, 0x18, 0x4d, 0x01, 0x80}, 6, (_64K * _256B),  _64K,  3,
		{
			&read_std(0, INFINITE, 40), /* 40MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 64), /* 64MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(3, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_general,
	},

	/* Spansion/Cypress S25FL256S 3.3V */
	{
		"S25FL256S", {0x01, 0x02, 0x19, 0x4d, 0x01, 0x80}, 6, _32M,  _64K,  4,
		{
			&read_std4b(0, INFINITE, 50),  /* 50MHz */
			&read_fast4b(1, INFINITE, 133), /* 133MHz */
			&read_dual4b(1, INFINITE, 104),  /* 104MHz */
			&read_dual_addr4b(1, INFINITE, 104),  /* 104MHz */
			&read_quad4b(1, INFINITE, 104),  /* 104MHz */
			&read_quad_addr4b(3, INFINITE, 104),  /* 104MHz */
			0
		},

		{
			&write_std4b(0, 256, 104),  /* 104MHz */
			&write_quad4b(0, 256, 80),  /* 80MHz */
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 104),  /* 104MHz */
			0
		},
		&spi_driver_s25fl256s,
	},

	/* Micron  N25Q064A 1.8V */
	{
		"N25Q064A",   {0x20, 0xbb, 0x17}, 3, (_64K * _128B), _64K, 3,
		{
			&read_std(0, INFINITE, 54),  /* 54MHz */
			&read_fast(1, INFINITE, 108), /* 108MHz */
			&read_dual(1, INFINITE, 108), /* 108MHz */
			&read_dual_addr(2, INFINITE, 108),
			&read_quad(1, INFINITE, 108), /* 108MHz */
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_dual(0, 256, 108), /* 108MHz */
			&write_dual_addr(0, 256, 108), /* 108MHz */
			&write_quad(0, 256, 108), /* 108MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 108), /* 108MHz */
			0
		},
		&spi_driver_general,
	},

	/* Micron "N25Q128A11/MT25QU128AB" 1.8V */
	{
		"(MT)N25Q(U)128A",   {0x20, 0xbb, 0x18}, 3,
		(_64K * _256B), _64K, 3,
		{
			&read_std(0, INFINITE, 54),   /* 54MHz */
			&read_fast(1, INFINITE, 108), /* 108MHz */
			&read_dual(1, INFINITE, 108), /* 108MHz */
			&read_dual_addr(2, INFINITE, 108),  /* 108MHz */
			&read_quad(1, INFINITE, 108), /* 108MHz */
			&read_quad_addr(5, INFINITE, 108), /* 108MHz */
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_dual(0, 256, 108), /* 108MHz */
			&write_dual_addr(0, 256, 108), /* 108MHz */
			&write_quad(0, 256, 108), /* 108MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 108), /* 108MHz */
			0
		},
		&spi_driver_micron,
	},

	/* Micron  N25QL064A 3.3V */
	{
		"N25QL064A",   {0x20, 0xba, 0x17}, 3, (_64K * _128B), _64K, 3,
		{
			&read_std(0, INFINITE, 54),     /* 54MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(2, INFINITE, 84), /* 84MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(5, INFINITE, 84), /* 84MHz */
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_dual(0, 256, 75), /* 75MHz */
			&write_dual_addr(0, 256, 75), /* 75MHz */
			&write_quad(0, 256, 80),  /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 50),   /* 50MHz */
			0
		},
		&spi_driver_micron,
	},

	/* Micron  MT(N)25QL128A 3.3V */
	{
		"N25QL128A",   {0x20, 0xba, 0x18}, 3, (_64K * _256B), _64K, 3,
		{
			&read_std(0, INFINITE, 54),   /* 54MHz */
			&read_fast(1, INFINITE, 108), /* 108MHz */
			&read_dual(1, INFINITE, 84),   /* 84MHz */
			&read_dual_addr(2, INFINITE, 84),  /* 84MHz */
			&read_quad(1, INFINITE, 84), /* 84MHz */
			&read_quad_addr(5, INFINITE, 84), /* 84MHz */
			0
		},

		{
			&write_std(0, 256, 108), /* 108MHz */
			&write_dual(0, 256, 108), /* 108MHz */
			&write_dual_addr(0, 256, 108), /* 108MHz */
			&write_quad(0, 256, 108), /* 108MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 108), /* 108MHz */
			0
		},
		&spi_driver_micron,
	},

	/* Micron MT25QL256A 3.3V */
	{
		"MT25QL256A", {0x20, 0xba, 0x19, 0x10, 0x44}, 5, (_64K * _512B), _64K, 4,
		{
			&read_std4b(0, INFINITE, 54), /* 54MHz */
			&read_fast4b(1, INFINITE, 133), /* 133MHz */
			&read_dual4b(1, INFINITE, 133), /* 133MHz */
			&read_dual_addr4b(2, INFINITE, 133), /* 133MHz */
			&read_quad4b(1, INFINITE, 133), /* 133MHz */
			&read_quad_addr4b(5, INFINITE, 125), /* 125MHz */
			0
		},

		{
			&write_std4b(0, 256, 133), /* 133MHz */
			&write_dual4b(0, 256, 133), /* 133MHz */
			&write_dual_addr4b(0, 256, 133), /* 133MHz */
			&write_quad4b(0, 256, 133), /* 133MHz */
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 133), /* 133MHz */
			0
		},
		&spi_driver_micron,
	},

	/* Micron "MT25QU256A" 1.8V */
	{
		"MT25QU256A",   {0x20, 0xbb, 0x19}, 3, (_64K * _512B), _64K, 4,
		{
			&read_std4b(0, INFINITE, 54), /* 54MHz */
			&read_fast4b(1, INFINITE, 80), /* 80MHz */
			&read_dual4b(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr4b(2, INFINITE, 84), /* 84MHz */
			&read_quad4b(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr4b(5, INFINITE, 84), /* 84MHz */
			0
		},

		{
			&write_std4b(0, 256, 80), /* 80MHz */
			&write_dual4b(0, 256, 75), /* 75MHz */
			&write_dual_addr4b(0, 256, 75), /* 75MHz */
			&write_quad4b(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_micron,
	},

	/* Winbond -- w25x "blocks" are 64K, "sectors" are 4KiB */
	{
		"W25Q16JV-IQ/S25FL016K",
		{0xef, 0x40, 0x15}, 3, (_64K * _32B), _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_general,
	},

	{
		"W25Q32(B/F)V", {0xef, 0x40, 0x16}, 3, (_64K * _64B), _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_general,
	},

	/* winbond w25q32fw is 1.8v */
	{
		"W25Q32FW",  {0xef, 0x60, 0x16}, 3, _4M,  _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 133), /* 133MHz */
			&read_dual(1, INFINITE, 133), /* 133MHz */
			&read_quad(1, INFINITE, 133), /* 133MHz */
			&read_quad_addr(3, INFINITE, 133), /* 133MHz */
			0
		},

		{
			&write_std(0, 256, 133), /* 133MHz */
			&write_quad(0, 256, 133), /* 133MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 133), /* 133MHz */
			0
		},
		&spi_driver_w25q256fv,
	},

	{
		"W25Q64FV(SPI)/W25Q64JV_IQ",  {0xef, 0x40, 0x17}, 3, _8M,   _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_general,
	},

	/* winbond w25q64fw is 1.8v */
	{
		"W25Q64FW",  {0xef, 0x60, 0x17}, 3, _8M,   _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(3, INFINITE, 104), /* 104MHz */
			0
		},

		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_w25q256fv,
	},

	/* winbond w25q128fw is 1.8v */
	{
		"W25Q128FW",  {0xef, 0x60, 0x18}, 3, _16M,   _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(3, INFINITE, 104), /* 104MHz */
			0
		},

		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_w25q256fv,
	},

	{
		"W25Q128(B/F)V", {0xEF, 0x40, 0x18}, 3, _16M, _64K, 3,
		{
			&read_std(0, INFINITE, 33), /* 33MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_quad(1, INFINITE, /* 70 */ 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad(0, 256, /* 70 */ 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_w25q256fv,
	},

	/* "W25Q128JV_IM" can support DTR mode 80MHz */
	{
		"W25Q128JV_IM", {0xEF, 0x70, 0x18}, 3, _16M, _64K, 3,
		{
			&read_std(0, INFINITE, 33), /* 33MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_quad(1, INFINITE, /* 70 */80), /* 80MHz */
#ifdef CONFIG_DTR_MODE_SUPPORT
			&read_quad_dtr(8, INFINITE, 80), /* 80MHz */
#endif
			0
		},

		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad(0, 256, /* 70 */ 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_w25q256fv,
	},

	/* Winbond W25Q256(F/J)V-IQ */
	{
		"W25Q256(F/J)V-IQ", {0xEF, 0x40, 0x19}, 3, _32M, _64K, 4,
#ifdef CONFIG_AUTOMOTIVE_GRADE
		{
			&read_std(0, INFINITE, 50),  /* 50MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(3, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad(0, 256, 80),  /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 104),  /* 104MHz */
			0
		},
#else
		{
			&read_std4b(0, INFINITE, 50),  /* 50MHz */
			&read_fast4b(1, INFINITE, 80), /* 80MHz */
			&read_dual4b(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr4b(1, INFINITE, 80), /* 80MHz */
			&read_quad4b(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr4b(3, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std4b(0, 256, 80), /* 80MHz */
			&write_quad4b(0, 256, 80),  /* 80MHz */
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 104),  /* 104MHz */
			0
		},
#endif
		&spi_driver_w25q256fv,
	},
	/* Winbond W25Q256JW-IQ  1.8V */
	{
		"W25Q256JW-IQ", {0xEF, 0x60, 0x19}, 3, _32M, _64K, 4,
		{
			&read_std4b(0, INFINITE, 50),
			&read_fast4b(1, INFINITE, 133),
			&read_dual4b(1, INFINITE, 133),
			&read_dual_addr4b(1, INFINITE, 133),
			&read_quad4b(1, INFINITE, 133),
			&read_quad_addr4b(3, INFINITE, 133),
			0
		},

		{
			&write_std4b(0, 256, 133),
			&write_quad4b(0, 256, 133),
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 133),
			0
		},
		&spi_driver_w25q256fv,
	},
	/* Winbond W25Q256JWFIM  1.8V */
	{
		"W25Q256JWFIM", {0xEF, 0x80, 0x19}, 3, _32M, _64K, 4,
		{
			&read_std4b(0, INFINITE, 50),  /* 50MHz */
			&read_fast4b(1, INFINITE, 133), /* 133MHz */
			&read_dual4b(1, INFINITE, 133), /* 133MHz */
			&read_dual_addr4b(1, INFINITE, 133), /* 133MHz */
			&read_quad4b(1, INFINITE, 133), /* 133MHz */
			&read_quad_addr4b(3, INFINITE, 133), /* 133MHz */
			0
		},

		{
			&write_std4b(0, 256, 133), /* 133MHz */
			&write_quad4b(0, 256, 133), /* 133MHz */
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 133), /* 133MHz */
			0
		},
		&spi_driver_w25q256fv,
	},

	/* ESMT/CFEON */
	{
		"EN25Q32B", {0x1c, 0x30, 0x16}, 3, (_64K * _64B),  _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			/* &read_quad(3, INFINITE, 80), */
			0
		},

		{
			&write_std(0, 256, 80 /* 104 */), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 80 /* 104 */), /* 80MHz */
			0
		},
		&spi_driver_general,
	},

	{
		"EN25Q64", {0x1c, 0x30, 0x17}, 3, (_64K * _128B),  _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 100), /* 100MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_no_qe,
	},

	/* CFEON EN25QH64A 3.3V */
	{
		"EN25QH64A", {0x1c, 0x70, 0x17}, 3, (_64K * _128B),  _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_dual_addr(1, INFINITE, 104), /* 104MHz */
#ifndef CONFIG_CLOSE_SPI_8PIN_4IO
			&read_quad(1, INFINITE, 104), /* 104MHz */
			&read_quad_addr(3, INFINITE, 104), /* 104MHz */
#endif
			0
		},

		{
			&write_std(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_no_qe,
	},

	{
		"EN25Q128", {0x1c, 0x30, 0x18}, 3, (_64K * _256B),  _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std(0, 256, 104), /* 104MHz */
			0
		},

		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_no_qe,
	},

	/* ESMT */
	{
		"F25L64QA", {0x8C, 0x41, 0x17}, 3, (_64K * _128B),  _64K, 3,
		{
			&read_std(0, INFINITE, 66), /* 66MHz */
			&read_fast(1, INFINITE, /* 66 */100), /* 100MHz */
			&read_dual(1, INFINITE, /* 66 */80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			0
		},
		{
			&write_std(0, 256, /* 66 */100), /* 100MHz */
			&write_quad(0, 256, 80), /* 80MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, /* 66 */100), /* 100MHz */
			0
		},
		&spi_driver_f25l64q,
	},

	/* GD GD25LQ128 1.8V */
	{
		"GD25LQ128", {0xC8, 0x60, 0x18}, 3, _16M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80), /* 80MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(3, INFINITE, 80), /* 80MHz */
			0
		},
		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad(0, 256, 80), /* 80MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_gd25qxxx,
	},

	{
		"GD25Q256", {0xC8, 0x40, 0x19}, 3, _32M,  _64K, 4,
		{
			&read_std4b(0, INFINITE, 50), /* 50MHz */
			&read_fast4b(1, INFINITE, 80), /* 80MHz */
			&read_dual4b(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr4b(1, INFINITE, 80), /* 80MHz */
			&read_quad4b(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr4b(3, INFINITE, 80), /* 80MHz */
			0
		},

		{
			&write_std4b(0, 256, 80), /* 80MHz */
			&write_quad4b(0, 256, 80), /* 80MHz */
			0
		},

		{
			&erase_sector_64k4b(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_gd25qxxx,
	},

	{
		"GD25Q128/GD25Q127", {0xC8, 0x40, 0x18}, 3, _16M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80), /* 80MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_dual_addr(1, INFINITE, 104), /* 104MHz */
			&read_quad(1, INFINITE, 104), /* 104MHz */
			&read_quad_addr(3, INFINITE, 104), /* 104MHz */
			0
		},
		{
			&write_std(0, 256, 100), /* 100MHz */
			&write_quad(0, 256, 80), /* 80MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 100), /* 100MHz */
			0
		},
		&spi_driver_gd25qxxx,
	},

	{
		"GD25Q64", {0xC8, 0x40, 0x17}, 3, _8M,  _64K, 3,
		{
			&read_std(0, INFINITE, 66),  /* 66MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			0
		},
		{
			&write_std(0, 256, 100),  /* 100MHz */
			&write_quad(0, 256, 80),  /* 80MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 100),  /* 100MHz */
			0
		},
		&spi_driver_gd25qxxx,
	},

	{
		"GD25Q16C", {0xC8, 0x40, 0x15}, 3, _2M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80), /* 80MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(3, INFINITE, 80), /* 80MHz */
			0
		},
		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad(0, 256, 80),  /* 80MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_gd25qxxx,
	},

	/* GD GD25LQ16C 1.65~2.1V */
	{
		"GD25LQ16C", {0xC8, 0x60, 0x15}, 3, _2M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80), /* 80MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_dual_addr(1, INFINITE, 104), /* 104MHz */
			&read_quad(1, INFINITE, 104), /* 104MHz */
			&read_quad_addr(3, INFINITE, 104), /* 104MHz */
			0
		},
		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad(0, 256, 104),  /* 104MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_gd25qxxx,
	},

	/* GD GD25LQ64C 1.8V */
	{
		"GD25LQ64C", {0xC8, 0x60, 0x17}, 3, _8M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80), /* 80MHz */
			&read_fast(1, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 80), /* 80MHz */
			&read_dual_addr(1, INFINITE, 80), /* 80MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			&read_quad_addr(3, INFINITE, 80), /* 80MHz */
			0
		},
		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad(0, 256, 80),  /* 80MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_gd25qxxx,
	},

	{
		"GD25Q32", {0xC8, 0x40, 0x16}, 3, _4M,  _64K, 3,
		{
			&read_std(0, INFINITE, 66),  /* 66MHz */
			&read_quad(1, INFINITE, 80), /* 80MHz */
			0
		},
		{
			&write_std(0, 256, 100),  /* 100MHz */
			&write_quad(0, 256, 80),  /* 80MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 100),  /* 100MHz */
			0
		},
		&spi_driver_gd25qxxx,
	},

	/* Paragon 3.3V */
	{
		"PN25F16S", {0xe0, 0x40, 0x15}, 3, _2M,  _64K, 3,
		{
			&read_std(0, INFINITE, 55), /* 55MHz */
			&read_fast(1, INFINITE, 108), /* 108MHz */
			&read_dual(1, INFINITE, 108), /* 108MHz */
			&read_dual_addr(1, INFINITE, 108), /* 108MHz */
			0
		},
		{
			&write_std(0, 256, 108),  /* 108MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 108), /* 108MHz */
			0
		},
		&spi_driver_general,
	},

	{
		"PN25F32S", {0xe0, 0x40, 0x16}, 3, _4M,  _64K, 3,
		{
			&read_std(0, INFINITE, 55), /* 55MHz */
			&read_fast(1, INFINITE, 108), /* 108MHz */
			&read_dual(1, INFINITE, 108), /* 108MHz */
			&read_dual_addr(1, INFINITE, 108), /* 108MHz */
			&read_quad(1, INFINITE, 108), /* 108MHz */
			&read_quad_addr(3, INFINITE, 108), /* 108MHz */
			0
		},
		{
			&write_std(0, 256, 108),  /* 108MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 108), /* 108MHz */
			0
		},
		&spi_driver_general,
	},

	/* XMC */
	{
		"XM25QH64AHIG", {0x20, 0x70, 0x17}, 3, _8M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80), /* 80MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_dual_addr(1, INFINITE, 104), /* 104MHz */
			&read_quad(1, INFINITE, 104), /* 104MHz */
			&read_quad_addr(3, INFINITE, 104), /* 104MHz */
			0
		},
		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad(0, 256, 104),  /* 104MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_no_qe,
	},

	/* XMC 3.3v */
	{
		"XM25QH128A", {0x20, 0x70, 0x18}, 3, _16M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80), /* 80MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_dual_addr(1, INFINITE, 104), /* 104MHz */
			&read_quad(1, INFINITE, 104), /* 104MHz */
			&read_quad_addr(3, INFINITE, 104), /* 104MHz */
			0
		},
		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad(0, 256, 104),  /* 104MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_no_qe,
	},

	/* XMC */
	{
		"XM25QH64B", {0x20, 0x60, 0x17}, 3, _8M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80), /* 80MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_dual_addr(1, INFINITE, 104), /* 104MHz */
			&read_quad(1, INFINITE, 104), /* 104MHz */
			&read_quad_addr(3, INFINITE, 104), /* 104MHz */
			0
		},
		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad(0, 256, 104),  /* 104MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_no_qe,
	},

	/* XMC 3.3v */
	{
		"XM25QH128B", {0x20, 0x60, 0x18}, 3, _16M,  _64K, 3,
		{
			&read_std(0, INFINITE, 50), /* 50MHz */
			&read_fast(1, INFINITE, 104), /* 104MHz */
			&read_dual(1, INFINITE, 104), /* 104MHz */
			&read_dual_addr(1, INFINITE, 104), /* 104MHz */
			&read_quad(1, INFINITE, 104), /* 104MHz */
			&read_quad_addr(3, INFINITE, 104), /* 104MHz */
			0
		},
		{
			&write_std(0, 256, 104), /* 104MHz */
			&write_quad(0, 256, 104),  /* 104MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 104), /* 104MHz */
			0
		},
		&spi_driver_no_qe,
	},

	/* XTX 3.3v */
	{
		"XT25F128BSSI/HGU", {0x0B, 0x40, 0x18}, 3, _16M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 108), /* 108MHz */
			&read_dual_addr(1, INFINITE, 108), /* 108MHz */
			&read_quad(1, INFINITE, 108), /* 108MHz */
			&read_quad_addr(3, INFINITE, 72),  /* 72MHz */
			0
		},
		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad(0, 256, 80),  /* 80MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_xtx,
	},

	{
		"XT25F64BSSI/HGU-S", {0x0B, 0x40, 0x17}, 3, _8M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80), /* 80MHz */
			&read_dual(1, INFINITE, 108), /* 108MHz */
			&read_dual_addr(1, INFINITE, 108), /* 108MHz */
			&read_quad(1, INFINITE, 84),  /* 84MHz */
			&read_quad_addr(3, INFINITE, 72),  /* 72MHz */
			0
		},
		{
			&write_std(0, 256, 80), /* 80MHz */
			&write_quad(0, 256, 80),  /* 80MHz */
			0
		},
		{
			&erase_sector_64k(0, _64K, 80), /* 80MHz */
			0
		},
		&spi_driver_xtx,
	},

	/* Puya Semiconductor 3.3V */
	{
		"P25Q128H", {0x85, 0x60, 0x18}, 3, _16M,  _64K, 3,
		{
			&read_std(0, INFINITE, 80),
			&read_fast(1, INFINITE, 104),
			&read_dual(1, INFINITE, 104),
			&read_dual_addr(1, INFINITE, 104),
			&read_quad(1, INFINITE, 104),
			&read_quad_addr(3, INFINITE, 104),
			0
		},
		{
			&write_std(0, 256, 104),
			&write_quad(0, 256, 104),
			0
		},
		{
			&erase_sector_64k(0, _64K, 104),
			0
		},
		&spi_driver_puya,
	},

	/* FM 3.3V */
	{
		"FM25Q64-SOB-T-G", {0xa1, 0x40, 0x17}, 3, _8M,  _64K, 3,
		{
			&read_std(0, INFINITE, 66),
			&read_fast(1, INFINITE, 104),
			&read_dual(1, INFINITE, 104),
			&read_dual_addr(1, INFINITE, 104),
			&read_quad(1, INFINITE, 104),
			&read_quad_addr(3, INFINITE, 104),
			0
		},
		{
			&write_std(0, 256, 104),
			&write_quad(0, 256, 104),
			0
		},
		{
			&erase_sector_64k(0, _64K, 104),
			0
		},
		&spi_driver_general,
	},

	/* FM 3.3V */
	{
		"FM25Q128A-SOB-T-G", {0xa1, 0x40, 0x18}, 3, _16M,  _64K, 3,
		{
			&read_std(0, INFINITE, 50),
			&read_fast(1, INFINITE, 104),
			&read_dual(1, INFINITE, 104),
			&read_dual_addr(1, INFINITE, 104),
			&read_quad(1, INFINITE, 104),
			&read_quad_addr(3, INFINITE, 104),
			0
		},
		{
			&write_std(0, 256, 104),
			&write_quad(0, 256, 104),
			0
		},
		{
			&erase_sector_64k(0, _64K, 104),
			0
		},
		&spi_driver_general,
	},

	/* HUAHONG 3.3V */
	{
		"H25S64", {0x68, 0x40, 0x17}, 3, _8M,  _64K, 3,
		{
			&read_std(0, INFINITE, 55),
			&read_fast(1, INFINITE, 55),
			&read_dual(1, INFINITE, 55),
			&read_dual_addr(1, INFINITE, 108),
			&read_quad(1, INFINITE, 108),
			&read_quad_addr(3, INFINITE, 108),
			0
		},
		{
			&write_std(0, 256, 55),
			&write_quad(0, 256, 55),
			0
		},
		{
			&erase_sector_64k(0, _64K, 55),
			0
		},
		&spi_driver_w25q256fv,
	},

	{
		"H25S128", {0x68, 0x40, 0x18}, 3, _16M,  _64K, 3,
		{
			&read_std(0, INFINITE, 55),
			&read_fast(1, INFINITE, 55),
			&read_dual(1, INFINITE, 55),
			&read_dual_addr(1, INFINITE, 108),
			&read_quad(1, INFINITE, 108),
			&read_quad_addr(3, INFINITE, 108),
			0
		},
		{
			&write_std(0, 256, 55),
			&write_quad(0, 256, 55),
			0
		},
		{
			&erase_sector_64k(0, _64K, 55),
			0
		},
		&spi_driver_w25q256fv,
	},

	/* ISSI 1V8 */
	{
		"IS25WP512M-RMLA3", {0x9d, 0x70, 0x1a}, 3, _64M,  _64K, 4,
		{
			&read_std(0, INFINITE, 50),
			&read_fast(1, INFINITE, 112),
			&read_dual(1, INFINITE, 112),
			&read_dual_addr(1, INFINITE, 112),
			&read_quad(1, INFINITE, 112),
			&read_quad_addr(3, INFINITE, 112),
			0
		},
		{
			&write_std(0, 256, 112),
			&write_quad(0, 256, 112),
			0
		},
		{
			&erase_sector_64k(0, _64K, 112),
			0
		},
		&spi_driver_issi,
	},
	{0, {0}, 0, 0, 0, 0, {0}, {0}, {0}, NULL},
};

/*****************************************************************************/
static struct spi_nor_info *hifmc_spi_nor_serach_ids(u_char ids[], int len)
{
	struct spi_nor_info *info = hifmc_spi_nor_info_table;
	struct spi_nor_info *fit_info = NULL;

	if (len <= 0)
		return NULL;

	for (; info->name; info++) {
		if (memcmp(info->id, ids, info->id_len))
			continue;

		if ((fit_info == NULL) || (fit_info->id_len < info->id_len))
			fit_info = info;
	}
	return fit_info;
}

/*****************************************************************************/
static void hifmc_spi_nor_search_rw(struct spi_nor_info *info,
				struct spi_op *spiop_rw,
				u_int iftype,
				u_int max_dummy,
				int rw_type)
{
	int ix = 0;
	struct spi_op **spiop, **fitspiop;

	for (fitspiop = spiop = (rw_type ? info->write : info->read);
	     (*spiop) && ix < MAX_SPI_OP; spiop++, ix++)
		if (((*spiop)->iftype & iftype) &&
			((*spiop)->dummy <= max_dummy) &&
			((*fitspiop)->iftype < (*spiop)->iftype))
			fitspiop = spiop;

	memcpy(spiop_rw, (*fitspiop), sizeof(struct spi_op));
}

/*****************************************************************************/
static void hifmc_map_iftype_and_clock(struct hifmc_spi *spi)
{
	int ix;
	const int iftype_read[] = {
		SPI_IF_READ_STD,    IF_TYPE_STD,
		SPI_IF_READ_FAST,   IF_TYPE_STD,
		SPI_IF_READ_DUAL,   IF_TYPE_DUAL,
		SPI_IF_READ_DUAL_ADDR,  IF_TYPE_DIO,
		SPI_IF_READ_QUAD,   IF_TYPE_QUAD,
		SPI_IF_READ_QUAD_ADDR,  IF_TYPE_QIO,
#ifdef CONFIG_DTR_MODE_SUPPORT
		SPI_IF_READ_QUAD_DTR,   IF_TYPE_DTR,
#endif
		0,          0,
	};
	const int iftype_write[] = {
		SPI_IF_WRITE_STD,   IF_TYPE_STD,
		SPI_IF_WRITE_DUAL,  IF_TYPE_DUAL,
		SPI_IF_WRITE_DUAL_ADDR, IF_TYPE_DIO,
		SPI_IF_WRITE_QUAD,  IF_TYPE_QUAD,
		SPI_IF_WRITE_QUAD_ADDR, IF_TYPE_QIO,
		0,          0,
	};

	/* Only an even number of values is required,so increase length is 2 */
	for (ix = 0; iftype_write[ix]; ix += 2) {
		if (spi->write->iftype == iftype_write[ix]) {
			spi->write->iftype = iftype_write[ix + 1];
			break;
		}
	}
	hifmc_get_fmc_best_2x_clock(&spi->write->clock);

	/* Only an even number of values is required,so increase length is 2 */
	for (ix = 0; iftype_read[ix]; ix += 2) {
		if (spi->read->iftype == iftype_read[ix]) {
			spi->read->iftype = iftype_read[ix + 1];
			break;
		}
	}
#ifdef CONFIG_DTR_MODE_SUPPORT
	if (spi->dtr_mode_support)
		/* get the div4 clock */
		hifmc_get_fmc_best_4x_clock(&spi->read->clock);
	else
		hifmc_get_fmc_best_2x_clock(&spi->read->clock);
#else
	hifmc_get_fmc_best_2x_clock(&spi->read->clock);
#endif

	hifmc_get_fmc_best_2x_clock(&spi->erase->clock);
	spi->erase->iftype = IF_TYPE_STD;
}

/*****************************************************************************/
void hifmc_spi_nor_get_erase(struct spi_nor_info *info,
				struct spi_op *spiop_erase)
{
	int ix;

	spiop_erase->size = 0;
	for (ix = 0; ix < MAX_SPI_OP; ix++) {
		if (info->erase[ix] == NULL)
			break;
		if (info->erasesize == info->erase[ix]->size) {
			memcpy(&spiop_erase[ix], info->erase[ix],
			       sizeof(struct spi_op));
			break;
		}
	}
}

/*****************************************************************************/
static void switch_to_4byte(struct hifmc_spi *spi, u_char *ids, int len)
{
	unsigned char manu_id = 0;
	/* auto check fmc_addr_mode 3 bytes or 4 bytes */
	unsigned int start_up_addr_mode = get_fmc_boot_mode();

	if(len < 3){
		return;
	}

	manu_id = ids[0];
	if ((spi->addrcycle == SPI_NOR_3BYTE_ADDR_LEN)
			&& (start_up_addr_mode == SPI_NOR_ADDR_MODE_4_BYTES))
		printf("\nError!!! the flash's addres len is 3bytes and start \
			up address mode is 4bytes,please set the start up \
				address mode to 3bytes mode");
	if ((spi->addrcycle == SPI_NOR_4BYTE_ADDR_LEN)
			&& (start_up_addr_mode == SPI_NOR_ADDR_MODE_3_BYTES)) {
		switch (manu_id) {
		case MID_WINBOND:
#ifdef CONFIG_AUTOMOTIVE_GRADE
			if((ids[1] == 0x40) && (ids[2] == 0x19)) { /* W25Q256FV/W25Q256JV */
				spi->driver->entry_4addr(spi, ENABLE);
				break;
			}
#endif
		case MID_MXIC:
		case MID_MICRON:
			fmc_pr(BT_DBG, "\t|||-4-Byte Command Operation\n");
			break;
		default:
				fmc_pr(BT_DBG, "\t|||-start up: 3-Byte mode\n");
				spi->driver->entry_4addr(spi, ENABLE);
			break;
		}
	} else {
		fmc_pr(BT_DBG, "\t|||-start up: 4-Byte mode or 4-Byte Command\n");
	}
}

/*****************************************************************************/
static void spi_data_init(struct hifmc_spi *spi, struct spi_nor_info *spiinfo,
				unsigned char cs)
{
	spi->name = spiinfo->name;
	spi->chipselect = cs;
	spi->chipsize = spiinfo->chipsize;
	spi->erasesize = spiinfo->erasesize;
	spi->addrcycle = spiinfo->addrcycle;
	spi->driver = spiinfo->driver;
}
/*****************************************************************************/
static void mtd_data_set(struct mtd_info_ex *mtd, struct spi_nor_info *spiinfo,
				struct hifmc_spi *spi)
{
	if (mtd->type == 0) {
		mtd->type = MTD_NORFLASH;
		mtd->chipsize = spi->chipsize;
		mtd->erasesize = spi->erasesize;
		mtd->pagesize = 1;
		mtd->addrcycle = spi->addrcycle;

		if (spiinfo->id_len > sizeof(mtd->ids)) {
			printf("BUG! ID len out of range.\n");
			BUG();
		}

		mtd->id_length = spiinfo->id_len;
		memcpy(mtd->ids, spiinfo->id, spiinfo->id_len);
		strncpy(mtd->name, spi->name,
				sizeof(mtd->name));
		mtd->name[sizeof(mtd->name) - 1] = '\0';
	}
}
/*****************************************************************************/
static void hifmc_init_print(struct hifmc_spi *spi)
{
	const char *str[] = {"STD", "DUAL", "DIO", "QUAD", "QIO"};

	fmc_pr(FMC_INFO, "Block:%sB ", ulltostr(spi->erasesize));
	fmc_pr(FMC_INFO, "Chip:%sB ", ulltostr(spi->chipsize));
	fmc_pr(FMC_INFO, "Name:\"%s\"\n", spi->name);

	fmc_pr(BT_DBG, "\t|||-Read if: %s, cmd: %#X, clock reg: %#x\n",
			str[spi->read->iftype],
			spi->read->cmd, spi->read->clock);
	fmc_pr(BT_DBG, "\t|||-Write if: %s, cmd: %#X, clock reg: %#x\n",
			str[spi->write->iftype],
			spi->write->cmd, spi->write->clock);
	fmc_pr(BT_DBG, "\t|||-Erase if: %s, cmd: %#X, clock reg: %#x\n",
			str[spi->erase[0].iftype],
			spi->erase[0].cmd, spi->erase[0].clock);
}
/*****************************************************************************/
static void hifmc_spi_map_op(struct spi_nor_info *spiinfo, struct hifmc_spi *spi)
{
#ifdef CONFIG_DTR_MODE_SUPPORT
	if (spi->dtr_mode_support) {
		/* to match the best dummy/if_type/clock */
		hifmc_spi_nor_search_rw(spiinfo, spi->read,
				HIFMC_SPI_NOR_SUPPORT_READ,
				HIFMC_SPI_NOR_DTR_MAX_DUMMY, RW_OP_READ);
	} else {
		hifmc_spi_nor_search_rw(spiinfo, spi->read,
				HIFMC_SPI_NOR_SUPPORT_READ,
				HIFMC_SPI_NOR_STR_MAX_DUMMY, RW_OP_READ);
	}
#else
	/* to match the best dummy/if_type/clock */
	hifmc_spi_nor_search_rw(spiinfo, spi->read,
			HIFMC_SPI_NOR_SUPPORT_READ,
			HIFMC_SPI_NOR_STR_MAX_DUMMY, RW_OP_READ);
#endif
	hifmc_spi_nor_search_rw(spiinfo, spi->write,
			HIFMC_SPI_NOR_SUPPORT_WRITE,
			HIFMC_SPI_NOR_STR_MAX_DUMMY, RW_OP_WRITE);

	hifmc_spi_nor_get_erase(spiinfo, spi->erase);
	hifmc_map_iftype_and_clock(spi);
}
/*****************************************************************************/
int hifmc_spi_nor_probe(struct mtd_info_ex *mtd, struct hifmc_spi *spi)
{
	unsigned char cs = 0;
	unsigned char ids[MAX_SPI_NOR_ID_LEN] = {0};
	unsigned char  ix = 0;
	unsigned char len = 0;
	unsigned int total = 0;
	char buffer[TMP_BUF_LEN];
	unsigned char *hifmc_cs = NULL;

	mtd->numchips = 0;

	fmc_pr(FMC_INFO, "SPI Nor ID Table Version %s\n", SPI_NOR_ID_TBL_VER);

	for (cs = 0; cs < CONFIG_SPI_NOR_MAX_CHIP_NUM; cs++) {
		hifmc_cs = get_cs_number(cs);
		if (*hifmc_cs) {
			fmc_pr(BT_DBG, "\t|||-CS(%d) is occupied\n", cs);
			continue;
		}

		hifmc100_read_ids(spi, cs, ids);

		/* can't find spi flash device, for id 0-2 */
		if (!(ids[0] | ids[1] | ids[2]) ||
				((ids[0] & ids[1] & ids[2]) == 0xFF)) /* id 0-2 */
			continue;

		len = sprintf(buffer, "SPI Nor(cs %d) ID: %#x %#x %#x", cs,
				ids[0], ids[1], ids[2]); /* id 0-2 */

		spiinfo = hifmc_spi_nor_serach_ids(ids, MAX_SPI_NOR_ID_LEN);
		/* id 3-7th */
		for (ix = 3; (spiinfo) && (ix < spiinfo->id_len); ix++)
			len += sprintf(buffer + len, " %#x", ids[ix]);

		if (spiinfo) {
			fmc_pr(FMC_INFO, "%s\n", buffer);

			fmc_pr(BT_DBG, "\t|||-CS-%d found SPI nor flash: %s\n",
			       cs, spiinfo->name);

			spi_data_init(spi, spiinfo, cs);

#ifdef CONFIG_DTR_MODE_SUPPORT
			/* to check weather current device support DTR mode */
			hifmc_check_spi_dtr_support(spi, ids, MAX_SPI_NOR_ID_LEN);
#endif
			hifmc_spi_map_op(spiinfo, spi);

			spi->driver->qe_enable(spi);

			switch_to_4byte(spi, ids, MAX_SPI_NOR_ID_LEN);

			hifmc_init_print(spi);
			mtd_data_set(mtd, spiinfo, spi);

			mtd->numchips++;
			total += spi->chipsize;
			spi++;
			(*hifmc_cs)++;
		} else {
			printf("SPI Nor(cs %d) ID: %#x %#x %#x can't find"
			 " in the ID table !!!\n", cs, ids[0], ids[1], ids[2]);
		}
	}

	fmc_pr(BT_DBG, "\t||*-End probe SPI nor flash, num: %d\n",
			mtd->numchips);

	return mtd->numchips;
}

/*****************************************************************************/
#ifdef CONFIG_DTR_MODE_SUPPORT
void spi_dtr_to_sdr_switch(struct hifmc_spi *spi)
{
	unsigned int ix = 0;
	unsigned int spi_dtr_dummy;
	struct spi_op **spiop, **fitspiop;
	const int iftype_read[] = {
		SPI_IF_READ_QUAD,   IF_TYPE_QUAD,
		SPI_IF_READ_QUAD_ADDR,  IF_TYPE_QIO,
		0,          0,
	};

	/* the dummy in SDR mode is impossible equal to DTR */
	spi_dtr_dummy = spi->read->dummy;

	/* match the best clock and dummy value agian */
	for (fitspiop = spiop = spiinfo->read;
	     (*spiop) && ix < MAX_SPI_OP; spiop++, ix++)
		if (((*spiop)->iftype & HIFMC_SPI_NOR_SUPPORT_READ) &&
		((*spiop)->dummy != spi_dtr_dummy) &&
		((*fitspiop)->iftype < (*spiop)->iftype))
			fitspiop = spiop;

	memcpy(spi->read, (*fitspiop), sizeof(struct spi_op));

	/* to map the iftype and clock of SDR mode */
	/* Only an even number of values is required,so increase length is 2 */
	for (ix = 0; iftype_read[ix]; ix += 2) {
		if (spi->read->iftype == iftype_read[ix]) {
			spi->read->iftype = iftype_read[ix + 1];
			break;
		}
	}
	hifmc_get_fmc_best_2x_clock(&spi->read->clock);
}
#endif /* CONFIG_DTR_MODE_SUPPORT */
