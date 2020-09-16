/*
 * hifmc_nand_spl_ids.c
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

#include <linux/mtd/nand.h>
#include "hifmc100_nand.h"

/*****************************************************************************/
#define _768K           (_256K + _512K)

/*****************************************************************************/
struct nand_flash_special_dev {
	unsigned char id[_8B];
	int length;             /* length of id. */
	unsigned long long chipsize;
	struct nand_flash_dev *(*probe)(struct nand_flash_dev_ex *nand_dev);
	char *name;

	unsigned long pagesize;
	unsigned long erasesize;
	unsigned long oobsize;
	unsigned long options;
	unsigned int read_retry_type;

#define BBP_LAST_PAGE                    0x01
#define BBP_FIRST_PAGE                   0x02
	unsigned int badblock_pos;
	int flags;
};

/*****************************************************************************
 * this is nand probe function.
 *****************************************************************************/
static struct nand_flash_dev *hynix_probe_v02(
	struct nand_flash_dev_ex *nand_dev)
{
	unsigned char *id = nand_dev->ids;
	struct nand_flash_dev *type = &nand_dev->flash_dev;

	int pagesizes[]   = {_2K, _4K, _8K, 0};
	int oobsizes[]    = {128, 224, 448, 0, 0, 0, 0, 0};
	int blocksizes[]  = {_128K, _256K, _512K, _768K, _1M, _2M, 0, 0};

	/* get blocktype from 3th id's bit 4 and bit 5 */
	int blocktype = (((id[3] >> 5) & 0x04) | ((id[3] >> 4) & 0x03));
	/* get oobtype from 3th id's bit 2 and bit 4 */
	int oobtype   = (((id[3] >> 2) & 0x03) | ((id[3] >> 4) & 0x04));

	type->options   = 0;
	/* get pagesize from 3th id's bit 0 and bit 1 */
	type->pagesize  = pagesizes[(id[3] & 0x03)];
	type->erasesize = blocksizes[blocktype];
	nand_dev->oobsize = oobsizes[oobtype];

	return type;
}

/*****************************************************************************/
static struct nand_flash_dev *samsung_probe_v02(
	struct nand_flash_dev_ex *nand_dev)
{
	unsigned char *id = nand_dev->ids;
	struct nand_flash_dev *type = &nand_dev->flash_dev;

	int pagesizes[]   = {_2K, _4K, _8K, 0};
	int oobsizes[]    = {0, 128, 218, 400, 436, 0, 0, 0};
	int blocksizes[]  = {_128K, _256K, _512K, _1M, 0, 0, 0, 0};

	/* get blocktype from 3th id's bit 4 and bit 5 */
	int blocktype = (((id[3] >> 5) & 0x04) | ((id[3] >> 4) & 0x03));
	/* get oobtype from 3th id's bit 2 and bit 4 */
	int oobtype   = (((id[3] >> 4) & 0x04) | ((id[3] >> 2) & 0x03));

	type->options   = 0;
	/* get pagesize from 3th id's bit 0 and bit 1 */
	type->pagesize  = pagesizes[(id[3] & 0x03)];
	type->erasesize = blocksizes[blocktype];
	nand_dev->oobsize = oobsizes[oobtype];

	return type;
}

/*****************************************************************************/

#define DRV_VERSION     "1.40"

/*****************************************************************************/
/*
 * samsung:  27nm need randomizer, 21nm need read retry;
 * micron:   25nm need read retry, datasheet will explain read retry.
 * toshaba   32nm need randomizer, 24nm need read retry.
 * hynix:    2xnm need read retry.
 *
 *      The special nand flash ID table version 1.39
 *
 * manufactory  |  type  |       name        |   ecc_type  | version_tag
 * Micron       |  MLC   |  MT29F64G08CBABA  |   40bit/1k  |  1.36
 * Micron       |  MLC   |  MT29F32G08CBADA  |   40bit/1k  |
 * Micron       |  SLC   |  MT29F8G08ABxBA   |   4bit/512  |
 * Micron       |  MLC   |  MT29F16G08CBABx  |   12bit/512 |
 * Micron       |  MLC   |  MT29F16G08CBACA  |   24bit/1k  |
 * Micron       |  MLC   |  MT29F32G08CBACA  |   24bit/1k  |
 * Micron       |  MLC   |  MT29F64G08CxxAA  |   24bit/1k  |
 * Micron       |  MLC   |  MT29F256G08CJAAA |   24bit/1k  |   2CE
 * Micron       |  MLC   |  MT29F256G08CMCBB |   24bit/1k  |
 * Micron       |  SLC   |  MT29F8G08ABACA   |   8bit/512  |
 * Micron       |  SLC   |  MT29F4G08ABAEA   |   8bit/512  |
 * Micron       |  SLC   |  MT29F2G08ABAFA   |   8bit/512  |
 * Micron       |  SLC   |  MT29F16G08ABACA  |   8bit/512  |
 * Toshiba      |  MLC   |  TC58NVG4D2FTA00  |   24bit/1k  |
 * Toshiba      |  MLC   |  TH58NVG6D2FTA20  |   24bit/1k  |   2CE
 * Toshiba      |  MLC   |  TC58NVG5D2HTA00  |   40bit/1k  |
 * Toshiba      |  MLC   |  TC58NVG6D2GTA00  |   40bit/1k  |
 * Toshiba      |  MLC   |  TC58NVG6DCJTA00  |             |
 * Toshiba      |  MLC   |  TC58TEG5DCJTA00  |             |
 * Toshiba      |  SLC   |  TC58NVG0S3HTA00  |   8bit/512  |
 * Toshiba      |  SLC   |  TC58NVG1S3HTA00  |   8bit/512  |
 * Toshiba      |  SLC   |  TC58NVG1S3ETA00  |   4bit/512  |
 * Toshiba      |  SLC   |  TC58NVG3S0FTA00  |   4bit/512  |
 * Toshiba      |  SLC   |  TC58NVG2S0FTA00  |   4bit/512  |
 * Toshiba      |  SLC   |  TH58NVG2S3HTA00  |   4bit/512  |
 * Toshiba      |  TLC   |  TC58NVG5T2JTA00  |   60bit/1k  |
 * Toshiba      |  TLC   |  TC58TEG5DCKTAx0  |   60bit/1k  |
 * Toshiba      |  MLC   |  Tx58TEGxDDKTAx0  |             |
 * Samsung      |  MLC   |  K9LB(HC/PD/MD)G08U0(1)D  |   8bit/512B  |
 * Samsung      |  MLC   |  K9GAG08U0E       |   24bit/1KB |
 * Samsung      |  MLC   |  K9LBG08U0E       |   24bit/1KB |
 * Samsung      |  MLC   |  K9G8G08U0C       |   24bit/1KB |
 * Samsung      |  MLC   |  K9GAG08U0F       |   24bit/1KB |
 * Samsung      |  MLC   |  K9LBG08U0M       |             |
 * Samsung      |  MLC   |  K9GBG08U0A       |   24bit/1KB |
 * Samsung      |  MLC   |  K9GBG08U0B       |   40bit/1KB |
 * Hynix        |  MLC   |  H27UAG8T2A       |             |
 * Hynix        |  MLC   |  H27UAG8T2B       |             |
 * Hynix        |  MLC   |  H27UBG8T2A       |             |
 * Hynix        |  MLC   |  H27UBG8T2BTR     |   24bit/1KB |
 * Hynix        |  MLC   |  H27UCG8T2A       |   40bit/1KB |
 * Hynix        |  MLC   |  H27UBG8T2C       |   40bit/1KB |
 * MISC         |  MLC   |  P1UAGA30AT-GCA   |   8bit/512  |
 * MISC         |  MLC   |  PSU8GA30AT-GIA/ASU8GA30IT-G30CA  |   4bit/512  |
 * MISC         |  SLC   |  PSU2GA30AT       |   1bit/512  |   1.36
 * Toshiba      |  SLC   |  TC58NVG2S0HTA00  |   24bit/1K  |   1.37
 * Toshiba      |  SLC   |  TC58NVG3S0HTA00  |   24bit/1K  |   1.37
 * Micron       |  SLC   |  MT29F2G08ABAEA   |   4bit/512 |
 * Spansion     |  SLC   | S34ML02G200TFI000     | 24bit/1K |
 * Spansion     |  SLC   | S34ML04G200TFI000     | 24bit/1K |  1.38
 * MXIC Macronix|  SLC   | MX30UF2G18AC 1.8V | 4bit/512 |  1.39
 * Spansion     |  SLC   | S34MS01G200TFI00 1.8V | 4bit/512 |  1.40
 * Spansion     |  SLC   | S34MS02G200TFI00 1.8V | 24bit/1K |  1.40
 * Spansion     |  SLC   | S34MS04G200TFI00 1.8V | 24bit/1K |  1.40
 *
 */
static struct nand_flash_special_dev nand_flash_special_table[] = {

	/************************* 1.8V MXIC Macronix **************************/
	{       /* SLC 4bit/512 1.8V */
		.name      = "MX30UF2G18AC",
		.id        = {0xC2, 0xAA, 0x90, 0x15, 0x06},
		.length    = _5B,
		.chipsize  = _256M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _64B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},

	/****************************** Spansion *******************************/

	{      /* SLC S34ML02G200TFI000 */
		.name      = "S34ML02G200TFI000",
		.id        = {0x01, 0xDA, 0x90, 0x95, 0x46, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _256M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _128B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},

	{      /* SLC S34ML04G200TFI000 */
		.name      = "S34ML04G200TFI000",
		.id        = {0x01, 0xDC, 0x90, 0x95, 0x56, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _512M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _128B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},

	{      /* SLC S34MS02G200TFI00 1.8V */
		.name      = "S34MS02G200TFI00",
		.id        = {0x01, 0xAA, 0x90, 0x15, 0x46, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _256M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _128B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},

	{      /* SLC S34MS04G200TFI00 1.8V */
		.name      = "S34MS04G200TFI00",
		.id        = {0x01, 0xAC, 0x90, 0x15, 0x56, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _512M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _128B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},

	/****************************** Micron *******************************/

	{        /* MLC 40bit/1k */
		.name      = "MT29F64G08CBABA",
		.id        = {0x2C, 0x64, 0x44, 0x4B, 0xA9, 0x00, 0x00, 0x00},
		.length    = _8B,
		.chipsize  = _8G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _2M,
		.oobsize   = _744B,
		.options   = 0,
		.read_retry_type = NAND_RR_MICRON,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = NAND_RANDOMIZER | NAND_SYNCHRONOUS | NAND_ASYNCHRONOUS,
	},
	{        /* MLC 40bit/1k */
		.name      = "MT29F32G08CBADA",
		.id        = {0x2C, 0x44, 0x44, 0x4B, 0xA9, 0x00, 0x00, 0x00},
		.length    = _8B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _2M,
		.oobsize   = _744B,
		.options   = 0,
		.read_retry_type = NAND_RR_MICRON,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	{        /* SLC 4bit/512 */
		.name      = "MT29F8G08ABxBA",
		.id        = {0x2C, 0x38, 0x00, 0x26, 0x85, 0x00, 0x00, 0x00},
		.length    = _8B,
		.chipsize  = _1G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _512K,
		.oobsize   = _224B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{        /* MLC 12bit/512 */
		.name      = "MT29F16G08CBABx",
		.id        = {0x2C, 0x48, 0x04, 0x46, 0x85, 0x00, 0x00, 0x00},
		.length    = _8B,
		.chipsize  = _2G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _1M,
		.oobsize   = _224B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{        /* MLC 24bit/1k */
		.name      = "MT29F16G08CBACA",
		.id        = {0x2C, 0x48, 0x04, 0x4A, 0xA5, 0x00, 0x00, 0x00},
		.length    = _8B,
		.chipsize  = _2G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _1M,
		.oobsize   = _224B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{        /* MLC 24bit/1k */
		.name      = "MT29F32G08CBACA",
		.id        = {0x2C, 0x68, 0x04, 0x4A, 0xA9, 0x00, 0x00, 0x00},
		.length    = _8B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _1M,
		.oobsize   = _224B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{        /* MLC 24bit/1k */
		.name      = "MT29F64G08CxxAA",
		.id        = {0x2C, 0x88, 0x04, 0x4B, 0xA9, 0x00, 0x00, 0x00},
		.length    = _8B,
		.chipsize  = _8G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _2M,
		.oobsize   = _448B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	{        /* MLC 24bit/1k 2CE */
		.name      = "MT29F256G08CJAAA",
		.id        = {0x2C, 0xA8, 0x05, 0xCB, 0xA9, 0x00, 0x00, 0x00},
		.length    = _8B,
		.chipsize  = _16G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _2M,
		.oobsize   = _448B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	{        /* MLC 40bit/1k */
		.name      = "MT29F256G08CMCBB",
		.id        = {0x2C, 0x64, 0x44, 0x4B, 0xA9, 0x00, 0x00, 0x00},
		.length    = _8B,
		.chipsize  = _8G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _2M,
		.oobsize   = _744B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{        /* SLC 8bit/512 */
		.name      = "MT29F8G08ABACA",
		.id        = {0x2C, 0xD3, 0x90, 0xA6, 0x64, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _1G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _256K,
		.oobsize   = _224B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{        /* SLC 8bit/512 */
		.name      = "MT29F4G08ABAEA",
		.id        = {0x2C, 0xDC, 0x90, 0xA6, 0x54, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _512M,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _256K,
		.oobsize   = _224B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{        /* SLC 8bit/512 */
		.name      = "MT29F2G08ABAFA",
		.id        = {0x2C, 0xDA, 0x90, 0x95, 0x04, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _256M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _224B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{      /* SLC MT29F2G08ABAEA */
		.name      = "MT29F2G08ABAEA",
		.id        = {0x2C, 0xDA, 0x90, 0x95, 0x06, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _256M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _64B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{        /* SLC 8bit/512 */
		.name      = "MT29F16G08ABACA",
		.id        = {0x2C, 0x48, 0x00, 0x26, 0xA9, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _2G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _512K,
		.oobsize   = _224B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},

	/****************************** Toshaba *******************************/

	{       /* MLC 24bit/1k 32nm */
		.name      = "TC58NVG4D2FTA00",
		.id        = {0x98, 0xD5, 0x94, 0x32, 0x76, 0x55, 0x00, 0x00},
		.length    = _6B,
		.chipsize  = _2G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _1M,
		.oobsize   = _448B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{       /* MLC 24bit/1k 32nm 2CE */
		.name      = "TH58NVG6D2FTA20",
		.id        = {0x98, 0xD7, 0x94, 0x32, 0x76, 0x55, 0x00, 0x00},
		.length    = _6B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _1M,
		.oobsize   = _448B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{       /* MLC 40bit/1k 24nm */
		.name      = "TC58NVG5D2HTA00 24nm",
		.id        = {0x98, 0xD7, 0x94, 0x32, 0x76, 0x56, 0x08, 0x00},
		.length    = _6B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _1M,
		.oobsize   = _640B,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_24NM,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	{       /* MLC 40bit/1k */
		.name      = "TC58NVG6D2GTA00",
		.id        = {0x98, 0xDE, 0x94, 0x82, 0x76, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _8G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _2M,
		.oobsize   = _640B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{       /* MLC 19nm */
		.name      = "TC58NVG6DCJTA00 19nm",
		.id        = {0x98, 0xDE, 0x84, 0x93, 0x72, 0x57, 0x08, 0x04},
		.length    = _8B,
		.chipsize  = _8G,
		.probe     = NULL,
		.pagesize  = _16K,
		.erasesize = _4M,
		.oobsize   = _1280B,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_24NM,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	{       /* MLC 19nm */
		.name      = "TC58TEG5DCJTA00 19nm",
		.id        = {0x98, 0xD7, 0x84, 0x93, 0x72, 0x57, 0x08, 0x04},
		.length    = _6B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _16K,
		.erasesize = _4M,
		.oobsize   = _1280B,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_24NM,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER | NAND_SYNCHRONOUS | NAND_ASYNCHRONOUS,
	},
	{       /* SLC 8bit/512 */
		.name      = "TC58NVG0S3HTA00",
		.id        = {0x98, 0xF1, 0x80, 0x15, 0x72, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _128M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _128B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		/*
		 * Datasheet: read one column of any page in each block. If the
		 * data of the column is 00 (Hex), define the block as a bad
		 * block.
		 */
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{       /* SLC 8bit/512 */
		.name      = "TC58NVG1S3HTA00",
		.id        = {0x98, 0xDA, 0x90, 0x15, 0x76, 0x16, 0x08, 0x00},
		.length    = _7B,
		.chipsize  = _256M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _128B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{       /* SLC 4bit/512 */
		.name      = "TC58NVG1S3ETA00",
		.id        = {0x98, 0xDA, 0x90, 0x15, 0x76, 0x14, 0x03, 0x00},
		.length    = _7B,
		.chipsize  = _256M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _64B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{       /* SLC 4bit/512 */
		.name      = "TC58NVG3S0FTA00",
		.id        = {0x98, 0xD3, 0x90, 0x26, 0x76, 0x15, 0x02, 0x08},
		.length    = _8B,
		.chipsize  = _1G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _256K,
		.oobsize   = _232B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{       /* SLC 24bit/1k */
		.name      = "TC58NVG3S0HTA00",
		.id        = {0x98, 0xD3, 0x91, 0x26, 0x76, 0x16, 0x08, 0x00},
		.length    = _8B,
		.chipsize  = _1G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _256K,
		.oobsize   = _256B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{       /* SLC 24bit/1k */
		.name      = "TC58NVG2S0HTA00",
		.id        = {0x98, 0xDC, 0x90, 0x26, 0x76, 0x16, 0x08, 0x00},
		.length    = _8B,
		.chipsize  = _512M,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _256K,
		.oobsize   = _256B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{       /* SLC 4bit/512 */
		.name      = "TC58NVG2S0FTA00",
		.id        = {0x98, 0xDC, 0x90, 0x26, 0x76, 0x15, 0x01, 0x08},
		.length    = _8B,
		.chipsize  = _512M,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _256K,
		.oobsize   = _224B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{       /* SLC 4bit/512 */
		.name      = "TH58NVG2S3HTA00",
		.id        = {0x98, 0xDC, 0x91, 0x15, 0x76},
		.length    = _5B,
		.chipsize  = _512M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _128B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE,
		.flags = 0,
	},
	{       /* TLC 60bit/1k 19nm */
		.name      = "TC58NVG5T2JTA00 19nm TLC",
		/* datasheet says 6 ids id data, but really has 8 ids. */
		.id        = {0x98, 0xD7, 0x98, 0x92, 0x72, 0x57, 0x08, 0x10},
		.length    = _6B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _4M,
		.oobsize   = _1K,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_24NM,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	{ /* TLC 60bit/1k 19nm */
		.name      = "TC58TEG5DCKTAx0 19nm MLC",
		/* datasheet says 6 ids id data, but really has 8 ids. */
		.id    = {0x98, 0xD7, 0x84, 0x93, 0x72, 0x50, 0x08, 0x04},
		.length    = _6B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _16K,
		.erasesize = _4M,
		.oobsize   = _1280B,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_19NM,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	{
		.name      = "Tx58TEGxDDKTAx0 19nm MLC",
		.id    = {0x98, 0xDE, 0x94, 0x93, 0x76, 0x50},
		.length    = _6B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _16K,
		.erasesize = _4M,
		.oobsize   = _1280B,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_19NM,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	/******************************* Samsung ******************************/
	{       /* MLC 8bit/512B */
		.name     = "K9LB(HC/PD/MD)G08U0(1)D",
		.id       = {0xEC, 0xD7, 0xD5, 0x29, 0x38, 0x41, 0x00, 0x00},
		.length   = _6B,
		.chipsize = _4G,
		.probe    = samsung_probe_v02,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_LAST_PAGE,
		.flags = 0,
	},
	{       /* MLC 24bit/1KB */
		.name      = "K9GAG08U0E",
		.id        = {0xEC, 0xD5, 0x84, 0x72, 0x50, 0x42, 0x00, 0x00},
		.length    = _6B,
		.chipsize  = _2G,
		.probe     = samsung_probe_v02,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{       /* MLC 24bit/1KB */
		.name     = "K9LBG08U0E",
		.id       = {0xEC, 0xD7, 0xC5, 0x72, 0x54, 0x42, 0x00, 0x00},
		.length   = _6B,
		.chipsize = _4G,
		.probe    = samsung_probe_v02,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{       /* MLC 24bit/1KB */
		.name     = "K9G8G08U0C",
		.id       = {0xEC, 0xD3, 0x84, 0x72, 0x50, 0x42, 0x00, 0x00},
		.length   = _6B,
		.chipsize = _1G,
		.probe    = samsung_probe_v02,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{        /* MLC 24bit/1k */
		.name      = "K9GAG08U0F",
		.id        = {0xEC, 0xD5, 0x94, 0x76, 0x54, 0x43, 0x00, 0x00},
		.length    = _6B,
		.chipsize  = _2G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _1M,
		.oobsize   = _512B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{        /* MLC */
		.name      = "K9LBG08U0M",
		.id        = {0xEC, 0xD7, 0x55, 0xB6, 0x78, 0x00, 0x00, 0x00},
		.length    = _5B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _512K,
		.oobsize   = _128B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_LAST_PAGE,
		.flags = 0,
	},
	{        /* MLC 24bit/1k */
		.name      = "K9GBG08U0A 20nm",
		.id        = {0xEC, 0xD7, 0x94, 0x7A, 0x54, 0x43, 0x00, 0x00},
		.length    = _6B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _1M,
		.oobsize   = _640B,
		.options   = 0,
		.read_retry_type = NAND_RR_SAMSUNG,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	{        /* MLC 40bit/1k */
		.name      = "K9GBG08U0B",
		.id        = {0xEC, 0xD7, 0x94, 0x7E, 0x64, 0x44, 0x00, 0x00},
		.length    = _6B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _1M,
		.oobsize   = _1K,
		.options   = 0,
		.read_retry_type = NAND_RR_SAMSUNG,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER,
	},

	/*********************************** Hynix ****************************/
	{       /* MLC */
		.name     = "H27UAG8T2A",
		.id       = {0xAD, 0xD5, 0x94, 0x25, 0x44, 0x41, },
		.length   = _6B,
		.chipsize = _2G,
		.probe    = hynix_probe_v02,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{       /* MLC */
		.name     = "H27UAG8T2B",
		.id       = {0xAD, 0xD5, 0x94, 0x9A, 0x74, 0x42, },
		.length   = _6B,
		.chipsize = _2G,
		.probe    = hynix_probe_v02,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{       /* MLC */
		.name     = "H27UBG8T2A",
		.id       = {0xAD, 0xD7, 0x94, 0x9A, 0x74, 0x42, },
		.length   = _6B,
		.chipsize = _4G,
		.probe    = hynix_probe_v02,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{       /* MLC 24bit/1K, 26nm TODO: Need read retry, chip is EOS */
		.name      = "H27UBG8T2BTR 26nm",
		.id        = {0xAD, 0xD7, 0x94, 0xDA, 0x74, 0xC3, },
		.length    = _6B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _2M,
		.oobsize   = _640B,
		.options   = 0,
		.read_retry_type = NAND_RR_HYNIX_BG_BDIE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	{        /* MLC 40bit/1k */
		.name      = "H27UCG8T2A",
		.id        = {0xAD, 0xDE, 0x94, 0xDA, 0x74, 0xC4, },
		.length    = _6B,
		.chipsize  = _8G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _2M,
		.oobsize   = _640B,
		.options   = 0,
		.read_retry_type = NAND_RR_HYNIX_CG_ADIE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER,
	},
	{        /* MLC 40bit/1k */
		.name      = "H27UBG8T2C",
		.id        = {0xAD, 0xD7, 0x94, 0x91, 0x60, 0x44, },
		.length    = _6B,
		.chipsize  = _4G,
		.probe     = NULL,
		.pagesize  = _8K,
		.erasesize = _2M,
		.oobsize   = _640B,
		.options   = 0,
		.read_retry_type = NAND_RR_HYNIX_BG_CDIE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = NAND_RANDOMIZER,
	},

	/********************** MISC ******************************************/
	{        /* MLC 8bit/512 */
		.name      = "P1UAGA30AT-GCA",
		.id        = {0xC8, 0xD5, 0x14, 0x29, 0x34, 0x01, },
		.length    = _6B,
		.chipsize  = _2G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _512K,
		.oobsize   = _218B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{       /* MLC 4bit/512 */
		/*
		 * PowerFlash ASU8GA30IT-G30CA ID and MIRA PSU8GA30AT-GIA ID
		 * are the same ID
		 */
		.name      = "PSU8GA30AT-GIA/ASU8GA30IT-G30CA",
		.id        = {0xC8, 0xD3, 0x90, 0x19, 0x34, 0x01, },
		.length    = _6B,
		.chipsize  = _1G,
		.probe     = NULL,
		.pagesize  = _4K,
		.erasesize = _256K,
		.oobsize   = _218B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{        /* SLC 1bit/512 */
		.name      = "PSU2GA30AT",
		.id       = {0x7F, 0x7F, 0x7F, 0x7F, 0xC8, 0xDA, 0x00, 0x15, },
		.length    = _8B,
		.chipsize  = _256M,
		.probe     = NULL,
		.pagesize  = _2K,
		.erasesize = _128K,
		.oobsize   = _64B,
		.options   = 0,
		.read_retry_type = NAND_RR_NONE,
		.badblock_pos    = BBP_FIRST_PAGE | BBP_LAST_PAGE,
		.flags = 0,
	},
	{{0}, 0, 0, 0, 0, 0, 0, 0, 0},
};

struct nand_flash_dev_ex g_nand_dev;
/*****************************************************************************/
struct nand_flash_dev *hifmc_get_spl_flash_type(struct mtd_info *mtd,
				struct nand_chip *chip, unsigned char *id)
{
	struct nand_flash_special_dev *spl_dev = nand_flash_special_table;
	struct nand_flash_dev *type = &g_nand_dev.flash_dev;
	struct nand_flash_dev_ex *nand_dev = &g_nand_dev;

	fmc_pr(BT_DBG, "\t *-Start find special nand flash\n");

	printf("Nand ID: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X " \
	       "0x%02X\n", id[0], id[1], id[2], id[3], id[4],  \
		   				id[5], id[6], id[7]);

	for (; spl_dev->length; spl_dev++) {
		if (memcmp(id, spl_dev->id, spl_dev->length))
			continue;

		fmc_pr(BT_DBG, "\t |-Found special Nand flash: %s\n",
		       spl_dev->name);

		if (spl_dev->probe) {
			type = spl_dev->probe((struct nand_flash_dev_ex *)id);
		} else {
			type->options   = spl_dev->options;
			type->pagesize  = spl_dev->pagesize;
			type->erasesize = spl_dev->erasesize;
			type->oobsize = spl_dev->oobsize;
		}

		type->name = spl_dev->name;
		type->id_len = spl_dev->length;
		memcpy(type->id, id, type->id_len);
		type->chipsize = (unsigned long)(byte_to_mb(spl_dev->chipsize));
		fmc_pr(BT_DBG, "\t |-Save struct nand_flash_dev info\n");

		memcpy(nand_dev->ids, id, MAX_NAND_ID_LEN);
		nand_dev->oobsize = type->oobsize;
		nand_dev->flags = spl_dev->flags;
		nand_dev->read_retry_type = spl_dev->read_retry_type;
		fmc_pr(BT_DBG, "\t |-Save struct nand_dev_t information\n");

		mtd->size = spl_dev->chipsize;

		return type;
	}
	nand_dev->read_retry_type = NAND_RR_NONE;

	chip->cmdfunc(mtd, NAND_CMD_READID, 0x00, -1);
	chip->read_byte(mtd);
	chip->read_byte(mtd);

	fmc_pr(BT_DBG, "\t *-Not found special nand flash\n");

	return NULL;
}

/*****************************************************************************/
void hifmc_spl_ids_register(void)
{
	printf("Special NAND id table Version %s\n", DRV_VERSION);
	get_flash_type = hifmc_get_spl_flash_type;
}
