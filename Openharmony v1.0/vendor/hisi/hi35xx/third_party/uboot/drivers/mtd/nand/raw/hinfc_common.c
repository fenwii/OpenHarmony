/*
 * hinfc_common.c
 *
 * The Flash Memory Controller Device Driver for hisilicon
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

#include <hinfc_common.h>
#include <match_table.h>

/*****************************************************************************/
struct nand_flash_dev *(*get_flash_type)(
	struct mtd_info *mtd,
	struct nand_chip *chip,
	unsigned char *id) = NULL;

int (*nand_oob_resize)(struct mtd_info *mtd) = NULL;

/*****************************************************************************/
#if defined(CONFIG_NAND_FLASH_HISNFC100) ||\
	defined(CONFIG_NAND_FLASH_HINFC610) ||\
	defined(CONFIG_HIFMC_SPI_NAND) ||\
	defined(CONFIG_HIFMC_NAND)
static struct match_type_str ecc2name[] = {
	{NAND_ECC_0BIT,  "none"     },
	{NAND_ECC_8BIT,  "4bit/512" },
	{NAND_ECC_16BIT, "8bit/512" },
	{NAND_ECC_24BIT, "24bit/1K" },
	{NAND_ECC_28BIT, "28bit/1K" },
	{NAND_ECC_40BIT, "40bit/1K" },
	{NAND_ECC_42BIT, "42bit/1K" },
	{NAND_ECC_64BIT, "64bit/1K" },
};

const char *nand_ecc_name(int type)
{
	return type2str(ecc2name, ARRAY_SIZE(ecc2name), type, "unknown");
}

/*****************************************************************************/
static struct match_type_str page2name[] = {
	{ NAND_PAGE_512B, "512" },
	{ NAND_PAGE_2K,   "2K" },
	{ NAND_PAGE_4K,   "4K" },
	{ NAND_PAGE_8K,   "8K" },
	{ NAND_PAGE_16K,  "16K" },
	{ NAND_PAGE_32K,  "32K" },
};

const char *nand_page_name(int type)
{
	return type2str(page2name, ARRAY_SIZE(page2name), type, "unknown");
}

/*****************************************************************************/
static struct match_reg_type page2size[] = {
	{ _512B, NAND_PAGE_512B },
	{ _2K, NAND_PAGE_2K },
	{ _4K, NAND_PAGE_4K },
	{ _8K, NAND_PAGE_8K },
	{ _16K, NAND_PAGE_16K },
	{ _32K, NAND_PAGE_32K },
};

int nandpage_size2type(int size)
{
	return reg2type(page2size, ARRAY_SIZE(page2size), size, NAND_PAGE_2K);
}

int nandpage_type2size(int size)
{
	return type2reg(page2size, ARRAY_SIZE(page2size), size, NAND_PAGE_2K);
}
#endif

/*****************************************************************************/
#define ET_ECC_NONE	0x00
#define ET_ECC_4BIT	0x02
#define ET_ECC_8BIT	0x03
#define ET_ECC_24BIT	0x04
#define ET_ECC_40BIT1K	0x05
#define ET_ECC_64BIT1K	0x06

static struct match_reg_type ecc_yaffs_type_t[] = {
	{ET_ECC_NONE,		NAND_ECC_0BIT},
	{ET_ECC_4BIT,		NAND_ECC_8BIT},
	{ET_ECC_8BIT,		NAND_ECC_16BIT},
	{ET_ECC_24BIT,		NAND_ECC_24BIT},
	{ET_ECC_40BIT1K,	NAND_ECC_40BIT},
	{ET_ECC_64BIT1K,	NAND_ECC_64BIT}
};

unsigned char match_ecc_type_to_yaffs(unsigned char type)
{
	return type2reg(ecc_yaffs_type_t, ARRAY_SIZE(ecc_yaffs_type_t), type,
			ET_ECC_4BIT);
}

/*****************************************************************************/
static struct match_t page_table[] = {
	{NAND_PAGE_2K,	PAGE_SIZE_2KB,	"2K"},
	{NAND_PAGE_4K,	PAGE_SIZE_4KB,	"4K"},
	{NAND_PAGE_8K,	PAGE_SIZE_8KB,	"8K"},
	{NAND_PAGE_16K,	PAGE_SIZE_16KB,	"16K"},
};

unsigned char match_page_reg_to_type(unsigned char reg)
{
	return match_reg_to_type(page_table, ARRAY_SIZE(page_table), reg,
				 NAND_PAGE_2K);
}

unsigned char match_page_type_to_reg(unsigned char type)
{
	return match_type_to_reg(page_table, ARRAY_SIZE(page_table), type,
				 PAGE_SIZE_2KB);
}

const char *match_page_type_to_str(unsigned char type)
{
	return match_type_to_data(page_table, ARRAY_SIZE(page_table), type,
				  "unknown");
}

/*****************************************************************************/
static struct match_t ecc_table[] = {
	{NAND_ECC_0BIT,		ECC_TYPE_0BIT,	"none"},
	{NAND_ECC_8BIT,		ECC_TYPE_8BIT,	"4bit/512"},
	{NAND_ECC_16BIT,	ECC_TYPE_16BIT,	"8bit/512"},
	{NAND_ECC_24BIT,	ECC_TYPE_24BIT,	"24bit/1K"},
	{NAND_ECC_28BIT,	ECC_TYPE_28BIT,	"28bit/1K"},
	{NAND_ECC_40BIT,	ECC_TYPE_40BIT,	"40bit/1K"},
	{NAND_ECC_64BIT,	ECC_TYPE_64BIT,	"64bit/1K"},
};

unsigned char match_ecc_reg_to_type(unsigned char reg)
{
	return match_reg_to_type(ecc_table, ARRAY_SIZE(ecc_table), reg,
				 NAND_ECC_8BIT);
}

unsigned char match_ecc_type_to_reg(unsigned char type)
{
	return match_type_to_reg(ecc_table, ARRAY_SIZE(ecc_table), type,
				 ECC_TYPE_8BIT);
}

const char *match_ecc_type_to_str(unsigned char type)
{
	return match_type_to_data(ecc_table, ARRAY_SIZE(ecc_table), type,
				  "unknown");
}

/*****************************************************************************/
static struct match_t page_type_size_table[] = {
	{NAND_PAGE_2K,	_2K,	NULL},
	{NAND_PAGE_4K,	_4K,	NULL},
	{NAND_PAGE_8K,	_8K,	NULL},
	{NAND_PAGE_16K,	_16K,	NULL},
};

unsigned char match_page_size_to_type(unsigned int size)
{
	return match_reg_to_type(page_type_size_table,
			ARRAY_SIZE(page_type_size_table), size, NAND_PAGE_2K);
}

unsigned int match_page_type_to_size(unsigned char type)
{
	return match_type_to_reg(page_type_size_table,
				 ARRAY_SIZE(page_type_size_table), type, _2K);
}
