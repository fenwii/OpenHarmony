/*
 * hifmc100.h
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

#ifndef __HIFMC100_H__
#define __HIFMC100_H__

#include <nand.h>
#include <hifmc_common.h>
#include <hinfc_common.h>
#include "../../../hifmc_spi_ids.h"
#include <cpu_func.h>

/*****************************************************************************/
/* These macroes are for debug only, reg option is slower then dma option */
#undef HIFMC100_SPI_NAND_SUPPORT_REG_READ
#undef HIFMC100_SPI_NAND_SUPPORT_REG_WRITE

/*****************************************************************************/
#define REG_CNT_HIGH_BLOCK_NUM_SHIFT        10

#define REG_CNT_BLOCK_NUM_MASK          0x3ff
#define REG_CNT_BLOCK_NUM_SHIFT         22

#define REG_CNT_PAGE_NUM_MASK           0x3f
#define REG_CNT_PAGE_NUM_SHIFT          16

#define REG_CNT_WRAP_MASK           0xf
#define REG_CNT_WRAP_SHIFT          12

#define REG_CNT_ECC_OFFSET_MASK         0xfff
#define REG_CNT_ECC_8BIT_OFFSET         1054
#define REG_CNT_ECC_16BIT_OFFSET        1056
#define REG_CNT_ECC_24BIT_OFFSET        1082

#define ERR_STR_DRIVER "Driver does not support this configure "
#define ERR_STR_CHECK "Please make sure the hardware configuration is correct"

/*****************************************************************************/
#define SPI_NAND_MAX_PAGESIZE           4096
#define SPI_NAND_MAX_OOBSIZE            256

#define HIFMC100_BUFFER_LEN (SPI_NAND_MAX_PAGESIZE + SPI_NAND_MAX_OOBSIZE)

#define HIFMC100_ADDR_CYCLE_MASK        0x2

/*****************************************************************************/
struct hifmc_host {
	struct mtd_info *mtd;
	struct nand_chip *chip;
	struct hifmc_spi spi[CONFIG_SPI_NAND_MAX_CHIP_NUM];
	struct hifmc_cmd_op cmd_op;

	void __iomem *iobase;
	void __iomem *regbase;

	unsigned int fmc_cfg;
	unsigned int fmc_cfg_ecc0;

	unsigned int offset;

	struct device *dev;

	/* This is maybe an un-aligment address, only for malloc or free */
	char *buforg;
	char *buffer;

	long dma_buffer;
	long dma_oob;

	unsigned int addr_cycle;
	unsigned int addr_value[2]; /* 2 addr */
	unsigned int cache_addr_value[2]; /* 2 addr */

	unsigned int column;
	unsigned int block_page_mask;

	unsigned int ecctype;
	unsigned int pagesize;
	unsigned int oobsize;

	int add_partition;

	/* BOOTROM read two bytes to detect the bad block flag */
#define HIFMC_BAD_BLOCK_POS     0
	unsigned char *bbm; /* nand bad block mark */
	unsigned short *epm;    /* nand empty page mark */

	unsigned int uc_er;

	void (*send_cmd_pageprog)(struct hifmc_host *host);
	void (*send_cmd_status)(struct hifmc_host *host);
	void (*send_cmd_readstart)(struct hifmc_host *host);
	void (*send_cmd_erase)(struct hifmc_host *host);
	void (*send_cmd_readid)(struct hifmc_host *host);
	void (*send_cmd_reset)(struct hifmc_host *host);
	void (*set_system_clock)(struct spi_op *op, int clk_en);
};

/*****************************************************************************/
void hifmc100_ecc0_switch(struct hifmc_host *host, unsigned char op);

int hifmc100_host_init(struct hifmc_host *host);

void hifmc100_spi_nand_init(struct hifmc_host *host);

/*****************************************************************************/
void hifmc_spi_nand_ids_register(void);
unsigned char spi_nand_feature_op(struct hifmc_spi *spi, unsigned char op,
				unsigned char addr, unsigned char val);
/*****************************************************************************/

#endif /* End of __HIFMC100_H__ */
