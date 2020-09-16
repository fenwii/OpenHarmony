/*
 * hifmc_spi_ids.h
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

#ifndef __HIFMC_SPI_IDS_H__
#define __HIFMC_SPI_IDS_H__

#include "hifmc_common.h"
/*****************************************************************************/
#define INFINITE			0xFFFFFFFF

/*****************************************************************************/
#define SPI_IF_READ_STD		 	0x01
#define SPI_IF_READ_FAST		0x02
#define SPI_IF_READ_DUAL		0x04
#define SPI_IF_READ_DUAL_ADDR	   	0x08
#define SPI_IF_READ_QUAD		0x10
#define SPI_IF_READ_QUAD_ADDR	   	0x20
#define SPI_IF_READ_QUAD_DTR		0x40

#define SPI_IF_WRITE_STD		0x01
#define SPI_IF_WRITE_DUAL	  	0x02
#define SPI_IF_WRITE_DUAL_ADDR	  	0x04
#define SPI_IF_WRITE_QUAD	   	0x08
#define SPI_IF_WRITE_QUAD_ADDR	  	0x10

#define SPI_IF_ERASE_SECTOR_4K	  	0x01
#define SPI_IF_ERASE_SECTOR_32K	 	0x02
#define SPI_IF_ERASE_SECTOR_64K	 	0x04
#define SPI_IF_ERASE_SECTOR_128K	0x08
#define SPI_IF_ERASE_SECTOR_256K	0x10

/*****************************************************************************/
#define HIFMC_SPI_NOR_SUPPORT_READ  (SPI_IF_READ_STD | \
					SPI_IF_READ_FAST | \
					SPI_IF_READ_DUAL | \
					SPI_IF_READ_DUAL_ADDR | \
					SPI_IF_READ_QUAD | \
					SPI_IF_READ_QUAD_ADDR | \
					SPI_IF_READ_QUAD_DTR)

#define HIFMC_SPI_NOR_SUPPORT_WRITE (SPI_IF_WRITE_STD | \
					SPI_IF_WRITE_DUAL | \
					SPI_IF_WRITE_DUAL_ADDR | \
					SPI_IF_WRITE_QUAD | \
					SPI_IF_WRITE_QUAD_ADDR)

#define HIFMC_SPI_NOR_STR_MAX_DUMMY	 7
#define HIFMC_SPI_NOR_DTR_MAX_DUMMY	 12

/******************************************************************************/
#define HIFMC_SPI_NAND_SUPPORT_READ (SPI_IF_READ_STD | \
					SPI_IF_READ_FAST | \
					SPI_IF_READ_DUAL | \
					SPI_IF_READ_DUAL_ADDR | \
					SPI_IF_READ_QUAD | \
					SPI_IF_READ_QUAD_ADDR)

#define HIFMC_SPI_NAND_SUPPORT_WRITE	(SPI_IF_WRITE_STD | SPI_IF_WRITE_QUAD)

#define HIFMC_SPI_NAND_SUPPORT_MAX_DUMMY	8

/*****************************************************************************/
#define SPI_CMD_READ_STD	0x03  /* Standard read cache */
#define SPI_CMD_READ_STD4B	0x13  /* Standard read cache 4byte mode */
#define SPI_CMD_READ_FAST	0x0B  /* Higher speed read cache */
#define SPI_CMD_READ_FAST4B	0x0C  /* Higher speed read cache 4byte mode */
#define SPI_CMD_READ_DUAL	0x3B  /* 2 IO read cache only date */
#define SPI_CMD_READ_DUAL4B	0x3C  /* 2 IO read cache only date 4byte mode */
#define SPI_CMD_READ_DUAL_ADDR	0xBB  /* 2 IO read cache date&addr */
#define SPI_CMD_READ_DUAL_ADDR4B 0xBC /* 2 IO read cache date&addr 4byte mode */
#define SPI_CMD_READ_QUAD	0x6B  /* 4 IO read cache only date */
#define SPI_CMD_READ_QUAD4B	0x6C  /* 4 IO read cache only date 4byte mode */
#define SPI_CMD_READ_QUAD_ADDR	0xEB  /* 4 IO read cache date&addr */
#define SPI_CMD_READ_QUAD_ADDR4B 0xEC /* 4 IO read cache date&addr 4byte mode */
#define SPI_CMD_READ_QUAD_DTR	0xED /* 4DTR MODE */
#define SPI_CMD_READ_QUAD_DTR4B	0xEE /* 4DTR MODE 4byte mode */
#define SPI_CMD_READ_QUAD_DTR4B_WINBOND	0xEC /* 4DTR MODE */

#define SPI_CMD_WRITE_STD	0x02 /* Standard page program */
#define SPI_CMD_WRITE_STD4B	0x12 /* Standard page program 4byte mode */
#define SPI_CMD_WRITE_DUAL	0xA2 /* 2 IO program only date */
#define SPI_CMD_WRITE_DUAL4B	0xA2 /* 2 IO program only date 4byte mode */
#define SPI_CMD_WRITE_DUAL_ADDR	 0xD2 /* 2 IO program date&addr */
#define SPI_CMD_WRITE_DUAL_ADDR4B 0xD2 /* 2 IO program date&addr 4byte mode */
#define SPI_CMD_WRITE_QUAD	0x32 /* 4 IO program only date */
#define SPI_CMD_WRITE_QUAD4B	0x34 /* 4 IO program only date 4byte mode */
#define SPI_CMD_WRITE_QUAD_ADDR	 0x38 /* 4 IO program date&addr */
#define SPI_CMD_WRITE_QUAD_ADDR4B 0x3E /* 4 IO program date&addr 4byte mode */

#define SPI_CMD_SE_4K	0x20 /* 4KB sector Erase */
#define SPI_CMD_SE_4K4B	0x21 /* 4KB sector Erase 4byte mode */
#define SPI_CMD_SE_32K	0x52 /* 32KB sector Erase */
#define SPI_CMD_SE_32K4B 0x5C /* 32KB sector Erase 4byte mode */
#define SPI_CMD_SE_64K	0xD8 /* 64KB sector Erase */
#define SPI_CMD_SE_64K4B 0xDC /* 64KB sector Erase 4byte mode */
#define SPI_CMD_SE_128K	 0xD8 /* 128KB sector Erase */
#define SPI_CMD_SE_128K4B 0xD8 /* 128KB sector Erase 4byte mode */
#define SPI_CMD_SE_256K	 0xD8 /* 256KB sector Erase */
#define SPI_CMD_SE_256K4B 0xD8 /* 256KB sector Erase 4byte mode */

/*****************************************************************************/
#define set_read_std(_dummy_, _size_, _clk_) \
	static struct spi_op read_std_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_STD, SPI_CMD_READ_STD, _dummy_, _size_, _clk_ }

#define set_read_std4b(_dummy_, _size_, _clk_) \
	static struct spi_op read_std4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_STD, SPI_CMD_READ_STD4B, _dummy_, _size_, _clk_ }

#define set_read_fast(_dummy_, _size_, _clk_) \
	static struct spi_op read_fast_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_FAST, SPI_CMD_READ_FAST, _dummy_, _size_, _clk_ }

#define set_read_fast4b(_dummy_, _size_, _clk_) \
	static struct spi_op read_fast4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_FAST, SPI_CMD_READ_FAST4B, _dummy_, _size_, _clk_ }

#define set_read_dual(_dummy_, _size_, _clk_) \
	static struct spi_op read_dual_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_DUAL, SPI_CMD_READ_DUAL, _dummy_, _size_, _clk_ }

#define set_read_dual4b(_dummy_, _size_, _clk_) \
	static struct spi_op read_dual4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_DUAL, SPI_CMD_READ_DUAL4B, _dummy_, _size_, _clk_ }

#define set_read_dual_addr(_dummy_, _size_, _clk_) \
	static struct spi_op read_dual_addr_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_DUAL_ADDR, SPI_CMD_READ_DUAL_ADDR, _dummy_, _size_, _clk_ }

#define set_read_dual_addr4b(_dummy_, _size_, _clk_) \
	static struct spi_op read_dual_addr4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_DUAL_ADDR, SPI_CMD_READ_DUAL_ADDR4B, _dummy_, _size_, _clk_ }

#define set_read_quad(_dummy_, _size_, _clk_) \
	static struct spi_op read_quad_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_QUAD, SPI_CMD_READ_QUAD, _dummy_, _size_, _clk_ }

#define set_read_quad4b(_dummy_, _size_, _clk_) \
	static struct spi_op read_quad4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_QUAD, SPI_CMD_READ_QUAD4B, _dummy_, _size_, _clk_ }

#define set_read_quad_addr(_dummy_, _size_, _clk_) \
	static struct spi_op read_quad_addr_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_QUAD_ADDR, SPI_CMD_READ_QUAD_ADDR, _dummy_, _size_, _clk_ }

#define set_read_quad_addr4b(_dummy_, _size_, _clk_) \
	static struct spi_op read_quad_addr4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_QUAD_ADDR, SPI_CMD_READ_QUAD_ADDR4B, _dummy_, _size_, _clk_ }

#ifdef CONFIG_DTR_MODE_SUPPORT
#define set_read_quad_dtr(_dummy_, _size_, _clk_) \
	static struct spi_op read_quad_dtr_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_QUAD_DTR, SPI_CMD_READ_QUAD_DTR, _dummy_, _size_, _clk_ }

#define set_read_quad_dtr4b(_dummy_, _size_, _clk_) \
	static struct spi_op read_quad_dtr4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_QUAD_DTR, SPI_CMD_READ_QUAD_DTR4B, _dummy_, _size_, _clk_ }

#define set_read_quad_dtr4b_winbond(_dummy_, _size_, _clk_) \
	static struct spi_op read_quad_dtr_winbond_##_dummy_##_size_##_clk_ = \
	{SPI_IF_READ_QUAD_DTR, SPI_CMD_READ_QUAD_DTR4B_WINBOND, \
		_dummy_, _size_, _clk_ }
#endif

/*****************************************************************************/
#define set_write_std(_dummy_, _size_, _clk_) \
	static struct spi_op write_std_##_dummy_##_size_##_clk_ = { \
	SPI_IF_WRITE_STD, SPI_CMD_WRITE_STD, _dummy_, _size_, _clk_ }

#define set_write_std4b(_dummy_, _size_, _clk_) \
	static struct spi_op write_std4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_WRITE_STD, SPI_CMD_WRITE_STD4B, _dummy_, _size_, _clk_ }

#define set_write_dual(_dummy_, _size_, _clk_) \
	static struct spi_op write_dual_##_dummy_##_size_##_clk_ = { \
	SPI_IF_WRITE_DUAL, SPI_CMD_WRITE_DUAL, _dummy_, _size_, _clk_ }

#define set_write_dual4b(_dummy_, _size_, _clk_) \
	static struct spi_op write_dual4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_WRITE_DUAL, SPI_CMD_WRITE_DUAL4B, _dummy_, _size_, _clk_ }

#define set_write_dual_addr(_dummy_, _size_, _clk_) \
	static struct spi_op write_dual_addr_##_dummy_##_size_##_clk_ = { \
SPI_IF_WRITE_DUAL_ADDR, SPI_CMD_WRITE_DUAL_ADDR, _dummy_, _size_, _clk_ }

#define set_write_dual_addr4b(_dummy_, _size_, _clk_) \
	static struct spi_op write_dual_addr4b_##_dummy_##_size_##_clk_ = { \
SPI_IF_WRITE_DUAL_ADDR, SPI_CMD_WRITE_DUAL_ADDR4B, _dummy_, _size_, _clk_ }

#define set_write_quad(_dummy_, _size_, _clk_) \
	static struct spi_op write_quad_##_dummy_##_size_##_clk_ = { \
	SPI_IF_WRITE_QUAD, SPI_CMD_WRITE_QUAD, _dummy_, _size_, _clk_ }

#define set_write_quad4b(_dummy_, _size_, _clk_) \
	static struct spi_op write_quad4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_WRITE_QUAD, SPI_CMD_WRITE_QUAD4B, _dummy_, _size_, _clk_ }

#define set_write_quad_addr(_dummy_, _size_, _clk_) \
	static struct spi_op write_quad_addr_##_dummy_##_size_##_clk_ = { \
SPI_IF_WRITE_QUAD_ADDR, SPI_CMD_WRITE_QUAD_ADDR, _dummy_, _size_, _clk_ }

#define set_write_quad_addr4b(_dummy_, _size_, _clk_) \
	static struct spi_op write_quad_addr4b_##_dummy_##_size_##_clk_ = { \
SPI_IF_WRITE_QUAD_ADDR, SPI_CMD_WRITE_QUAD_ADDR4B, _dummy_, _size_, _clk_ }

/*****************************************************************************/
#define set_erase_sector_4k(_dummy_, _size_, _clk_) \
	static struct spi_op erase_sector_4k_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_4K, SPI_CMD_SE_4K, _dummy_, _size_, _clk_ }

#define set_erase_sector_4k4b(_dummy_, _size_, _clk_) \
	static struct spi_op erase_sector_4k4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_4K, SPI_CMD_SE_4K4B, _dummy_, _size_, _clk_ }

#define set_erase_sector_32k(_dummy_, _size_, _clk_) \
	static struct spi_op erase_sector_32k_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_32K, SPI_CMD_SE_32K, _dummy_, _size_, _clk_ }

#define set_erase_sector_32k4b(_dummy_, _size_, _clk_) \
	static struct spi_op erase_sector_32k4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_32K, SPI_CMD_SE_32K4B, _dummy_, _size_, _clk_ }

#define set_erase_sector_64k(_dummy_, _size_, _clk_) \
	static struct spi_op erase_sector_64k_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_64K, SPI_CMD_SE_64K, _dummy_, _size_, _clk_ }

#define set_erase_sector_64k4b(_dummy_, _size_, _clk_) \
	static struct spi_op erase_sector_64k4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_64K, SPI_CMD_SE_64K4B, _dummy_, _size_, _clk_ }

#define set_erase_sector_128k(_dummy_, _size_, _clk_) \
	static struct spi_op erase_sector_128k_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_128K, SPI_CMD_SE_128K, _dummy_, _size_, _clk_ }

#define set_erase_sector_128k4b(_dummy_, _size_, _clk_) \
	static struct spi_op erase_sector_128k4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_128K, SPI_CMD_SE_128K4B, _dummy_, _size_, _clk_ }

#define set_erase_sector_256k(_dummy_, _size_, _clk_) \
	static struct spi_op erase_sector_256k_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_256K, SPI_CMD_SE_256K, _dummy_, _size_, _clk_ }

#define set_erase_sector_256k4b(_dummy_, _size_, _clk_) \
	static struct spi_op erase_sector_256k4b_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_256K, SPI_CMD_SE_256K4B, _dummy_, _size_, _clk_ }

/*****************************************************************************/
#define read_std(_dummy_, _size_, _clk_) read_std_##_dummy_##_size_##_clk_
#define read_std4b(_dummy_, _size_, _clk_) read_std4b_##_dummy_##_size_##_clk_
#define read_fast(_dummy_, _size_, _clk_) read_fast_##_dummy_##_size_##_clk_
#define read_fast4b(_dummy_, _size_, _clk_) \
					read_fast4b_##_dummy_##_size_##_clk_
#define read_dual(_dummy_, _size_, _clk_) read_dual_##_dummy_##_size_##_clk_
#define read_dual4b(_dummy_, _size_, _clk_) \
					read_dual4b_##_dummy_##_size_##_clk_
#define read_dual_addr(_dummy_, _size_, _clk_) \
		read_dual_addr_##_dummy_##_size_##_clk_
#define read_dual_addr4b(_dummy_, _size_, _clk_) \
		read_dual_addr4b_##_dummy_##_size_##_clk_
#define read_quad(_dummy_, _size_, _clk_) read_quad_##_dummy_##_size_##_clk_
#define read_quad4b(_dummy_, _size_, _clk_) \
					read_quad4b_##_dummy_##_size_##_clk_
#define read_quad_addr(_dummy_, _size_, _clk_) \
		read_quad_addr_##_dummy_##_size_##_clk_
#define read_quad_addr4b(_dummy_, _size_, _clk_) \
		read_quad_addr4b_##_dummy_##_size_##_clk_
#ifdef CONFIG_DTR_MODE_SUPPORT
#define read_quad_dtr(_dummy_, _size_, _clk_) \
		read_quad_dtr_##_dummy_##_size_##_clk_
#define read_quad_dtr4b(_dummy_, _size_, _clk_) \
		read_quad_dtr4b_##_dummy_##_size_##_clk_
#define read_quad_dtr4b_winbond(_dummy_, _size_, _clk_) \
		read_quad_dtr4b_winbond_##_dummy_##_size_##_clk_
#endif

/*****************************************************************************/
#define write_std(_dummy_, _size_, _clk_) write_std_##_dummy_##_size_##_clk_
#define write_std4b(_dummy_, _size_, _clk_) \
					write_std4b_##_dummy_##_size_##_clk_
#define write_dual(_dummy_, _size_, _clk_) write_dual_##_dummy_##_size_##_clk_
#define write_dual4b(_dummy_, _size_, _clk_) \
					write_dual4b_##_dummy_##_size_##_clk_
#define write_dual_addr(_dummy_, _size_, _clk_) \
		write_dual_addr_##_dummy_##_size_##_clk_
#define write_dual_addr4b(_dummy_, _size_, _clk_) \
		write_dual_addr4b_##_dummy_##_size_##_clk_
#define write_quad(_dummy_, _size_, _clk_) write_quad_##_dummy_##_size_##_clk_
#define write_quad4b(_dummy_, _size_, _clk_) \
					write_quad4b_##_dummy_##_size_##_clk_
#define write_quad_addr(_dummy_, _size_, _clk_) \
		write_quad_addr_##_dummy_##_size_##_clk_
#define write_quad_addr4b(_dummy_, _size_, _clk_) \
		write_quad_addr4b_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define erase_sector_4k(_dummy_, _size_, _clk_) \
		erase_sector_4k_##_dummy_##_size_##_clk_
#define erase_sector_4k4b(_dummy_, _size_, _clk_) \
		erase_sector_4k4b_##_dummy_##_size_##_clk_
#define erase_sector_32k(_dummy_, _size_, _clk_) \
		erase_sector_32k_##_dummy_##_size_##_clk_
#define erase_sector_32k4b(_dummy_, _size_, _clk_) \
		erase_sector_32k4b_##_dummy_##_size_##_clk_
#define erase_sector_64k(_dummy_, _size_, _clk_) \
		erase_sector_64k_##_dummy_##_size_##_clk_
#define erase_sector_64k4b(_dummy_, _size_, _clk_) \
		erase_sector_64k4b_##_dummy_##_size_##_clk_
#define erase_sector_128k(_dummy_, _size_, _clk_) \
		erase_sector_128k_##_dummy_##_size_##_clk_
#define erase_sector_128k4b(_dummy_, _size_, _clk_) \
		erase_sector_128k4b_##_dummy_##_size_##_clk_
#define erase_sector_256k(_dummy_, _size_, _clk_) \
		erase_sector_256k_##_dummy_##_size_##_clk_
#define erase_sector_256k4b(_dummy_, _size_, _clk_) \
		erase_sector_256k4b_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SPI_CMD_WREN			0x06 /* Write Enable */
#define SPI_CMD_WRDI			0x04 /* Write Disable */

/*****************************************************************************/
#define SPI_CMD_WRSR			0x01 /* Write Status Register */
#define SPI_CMD_WRSR2			0x31 /* Write Status Register-2 */
#define SPI_CMD_WRSR3			0x11 /* Write Status Register-3 */

#define SPI_CMD_RDSR			0x05 /* Read Status Register */
#define SPI_CMD_RDSR2			0x35 /* Read Status Register-2 */
#define SPI_CMD_RDSR3			0x15 /* Read Status Register-3 */

#define SPI_CMD_RDCR			0x35 /* Read Config Register */

#define SPI_CMD_RDID			0x9F /* Read Identification */

#define SPI_CMD_RD_SFDP			0x5A /* Read SFDP */
/*****************************************************************************/
#define SPI_CMD_GET_FEATURES		0x0F /* Get Features */
#define SPI_CMD_SET_FEATURE		0x1F /* Set Feature */

#define SPI_CMD_PAGE_READ		0x13 /* Page Read to Cache */

#define SPI_CMD_RESET			0xff /* Reset the device */

/*****************************************************************************/
#define SPI_CMD_EN4B	0xB7 /* enter 4 bytes mode and set 4 byte bit as '1' */
#define SPI_CMD_EX4B	0xE9 /* exit 4 bytes mode and clear 4 byte bit */

/*****************************************************************************/
#define MAX_SPI_OP		  8

/*****************************************************************************/
/* SPI general operation parameter */
struct spi_op {
	unsigned char iftype;
	unsigned char cmd;
	unsigned char dummy;
	unsigned int size;
	unsigned int clock;
};

struct spi_drv;

/* SPI interface all operation */
struct hifmc_spi {
	char *name;
	unsigned int chipselect;
	unsigned long long chipsize;
	unsigned int erasesize;
#define SPI_NOR_3BYTE_ADDR_LEN  3   /* address len 3Bytes */
#define SPI_NOR_4BYTE_ADDR_LEN  4   /* address len 4Bytes for 32MB */
	unsigned int addrcycle;

	struct spi_op read[1];
	struct spi_op write[1];
	struct spi_op erase[MAX_SPI_OP];

	void *host;

	struct spi_drv *driver;
#ifdef CONFIG_DTR_MODE_SUPPORT
	unsigned int dtr_mode_support;
	/* @dtr_cookie: Some device must set some registers when wants to
	 * work on DTR mode, so this cookie tells us to set s.th */
	unsigned int dtr_cookie;
#define DTR_MODE_SET_NONE 0x0   /* Need not set anything */
#define DTR_MODE_SET_ODS  0x1   /* Need to set output driver strength */
#endif
};

/* SPI interface special operation function hook */
struct spi_drv {
	int (*wait_ready)(struct hifmc_spi *spi);
	int (*write_enable)(struct hifmc_spi *spi);
	int (*qe_enable)(struct hifmc_spi *spi);
	int (*bus_prepare)(struct hifmc_spi *spi, int op);
	int (*entry_4addr)(struct hifmc_spi *spi, int en);
#ifdef CONFIG_DTR_MODE_SUPPORT
	int (*dtr_set_device)(struct hifmc_spi *spi, int dtr_en);
#endif
};
#ifndef MAX_SPI_NAND_ID_LEN
#define MAX_SPI_NAND_ID_LEN 1
#endif
struct spi_nand_info {
	char *name;
	unsigned char id[MAX_SPI_NAND_ID_LEN];
	unsigned char id_len;
	unsigned long long chipsize;
	unsigned int erasesize;
	unsigned int pagesize;
	unsigned int oobsize;
#define BBP_LAST_PAGE	   0x01
#define BBP_FIRST_PAGE	  0x02
	unsigned int badblock_pos;
	struct spi_op *read[MAX_SPI_OP];
	struct spi_op *write[MAX_SPI_OP];
	struct spi_op *erase[MAX_SPI_OP];
	struct spi_drv *driver;
};

#ifndef MAX_SPI_NOR_ID_LEN
#define MAX_SPI_NOR_ID_LEN 8
#endif

struct spi_nor_info {
	char *name;
	unsigned char id[MAX_SPI_NOR_ID_LEN];
	unsigned int id_len;
	unsigned long chipsize;
	unsigned int erasesize;
	unsigned int addrcycle;
	struct spi_op *read[MAX_SPI_OP];
	struct spi_op *write[MAX_SPI_OP];
	struct spi_op *erase[MAX_SPI_OP];
	struct spi_drv *driver;
};

/*****************************************************************************/
void hifmc_set_fmc_system_clock(struct spi_op *op, int clk_en);

void hifmc_get_fmc_best_2x_clock(unsigned int *clock);
#ifdef CONFIG_DTR_MODE_SUPPORT
void hifmc_get_fmc_best_4x_clock(unsigned int *clock);
#endif
/*****************************************************************************/

#endif /* End of __HIFMC_SPI_IDS_H__ */