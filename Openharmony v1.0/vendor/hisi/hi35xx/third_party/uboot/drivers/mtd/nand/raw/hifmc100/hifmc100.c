/*
 * hifmc100.c
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

#include "hifmc100.h"
#include <common.h>
#include <asm/io.h>
#include <errno.h>
#include <malloc.h>
#include <match_table.h>
#include <asm/arch/platform.h>

/*****************************************************************************/
void hifmc100_ecc0_switch(struct hifmc_host *host, unsigned char op)
{
	unsigned int config;
#if EC_DBG
	unsigned int cmp_cfg;

	config = hifmc_read(host, FMC_CFG);
	fmc_pr(EC_DBG, "\t *-Get CFG[%#x]%#x\n", FMC_CFG, config);

	if (op)
		cmp_cfg = host->fmc_cfg;
	else
		cmp_cfg = host->fmc_cfg_ecc0;

	if (cmp_cfg != config)
		db_msg("Warning: FMC config[%#x] is different.\n",
		       cmp_cfg);
#endif

	if (op == ENABLE) {
		config = host->fmc_cfg_ecc0;
	} else if (op == DISABLE) {
		config = host->fmc_cfg;
	} else {
		db_msg("Error: Invalid opcode: %d\n", op);
		return;
	}

	hifmc_write(host, FMC_CFG, config);
	fmc_pr(EC_DBG, "\t *-Set CFG[%#x]%#x\n", FMC_CFG, config);
}

/*****************************************************************************/
static u32 select_addr_of(unsigned char only_oob, struct hifmc_host *host)
{
	unsigned int addr_of = 0;

	if (only_oob)
		switch (host->ecctype) {
		case NAND_ECC_8BIT:
			addr_of = REG_CNT_ECC_8BIT_OFFSET;
			break;

		case NAND_ECC_16BIT:
			addr_of = REG_CNT_ECC_16BIT_OFFSET;
			break;

		case NAND_ECC_24BIT:
			addr_of = REG_CNT_ECC_24BIT_OFFSET;
			break;

		case NAND_ECC_0BIT:
		default:
			break;
		}
	return addr_of;
}

static void set_dma_addr_reg(struct hifmc_host *host)
{
	unsigned int reg;

	reg = host->dma_buffer;
	hifmc_write(host, FMC_DMA_SADDR_D0, reg);
	fmc_pr(DMA_DB, "\t|-Set DMA_SADDR_D0[%#x]%#x\n", FMC_DMA_SADDR_D0, reg);
	/* get hight 32 bits */
	reg = ((unsigned long)host->dma_buffer & FMC_DMA_SADDRH_MASK) >> 32;
	hifmc_write(host, FMC_DMA_SADDRH_D0, reg);
	fmc_pr(DMA_DB, "\t|-Set DMA_SADDRH_D0[%#x]%#x\n", FMC_DMA_SADDRH_D0, reg);
	reg = host->dma_oob;
	hifmc_write(host, FMC_DMA_SADDR_OOB, reg);
	fmc_pr(DMA_DB, "\t|-Set DMA_SADDR_OOB[%#x]%#x\n", FMC_DMA_SADDR_OOB,
	       reg);
	/* get hight 32 bits */
	reg = ((unsigned long)host->dma_oob & FMC_DMA_SADDRH_MASK) >> 32;
	hifmc_write(host, FMC_DMA_SADDRH_OOB, reg);
	fmc_pr(DMA_DB, "\t|-Set DMA_SADDRH_OOB[%#x]%#x\n", FMC_DMA_SADDRH_OOB,
	       reg);
}

static void set_addr_reg(unsigned int addr_of, struct hifmc_host *host)
{
	unsigned int reg;
	struct nand_chip *chip = host->chip;
	unsigned char pages_per_block_shift;
	unsigned int block_num;
	unsigned int block_num_h;
	unsigned int page_num;

	pages_per_block_shift = chip->phys_erase_shift - chip->page_shift;
	block_num = host->addr_value[1] >> pages_per_block_shift;
	block_num_h = block_num >> REG_CNT_HIGH_BLOCK_NUM_SHIFT;
	reg = fmc_addrh_set(block_num_h);
	hifmc_write(host, FMC_ADDRH, reg);
	fmc_pr(REG_DB, "|-Set ADDRH[%#x]%#x\n", FMC_ADDRH, reg);

	page_num = host->addr_value[1] - (block_num << pages_per_block_shift);
	reg = ((block_num & REG_CNT_BLOCK_NUM_MASK) << REG_CNT_BLOCK_NUM_SHIFT) |
	      ((page_num & REG_CNT_PAGE_NUM_MASK) << REG_CNT_PAGE_NUM_SHIFT) |
	      (addr_of & REG_CNT_ECC_OFFSET_MASK);
	hifmc_write(host, FMC_ADDRL, reg);
	fmc_pr(REG_DB, "|-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);
}

/****************************************************************************/
static void set_cs_addr_reg(enum OP op, unsigned char only_oob,
				struct hifmc_host *host)
{
	unsigned int reg;
	struct hifmc_spi *spi = host->spi;
	unsigned char iftype = 0;
	unsigned char dummy = 0;
	unsigned int addr_of = 0;

	reg = FMC_INT_CLR_ALL;
	hifmc_write(host, FMC_INT_CLR, reg);
	fmc_pr(WR_DBG, "|-Set INT_CLR[%#x]%#x\n", FMC_INT_CLR, reg);

	if (op == READ) {
		iftype  = spi->read->iftype;
		dummy   = spi->read->dummy;
		addr_of = select_addr_of(only_oob, host);
	} else if (op == WRITE) {
		iftype = spi->write->iftype;
	} else {
	    	iftype = spi->erase->iftype;
	}

	reg = op_cfg_fm_cs(host->cmd_op.cs) |
	      OP_CFG_OEN_EN |
	      op_cfg_mem_if_type(iftype) |
	      op_cfg_dummy_num(dummy);
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(REG_DB, "|-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	set_addr_reg(addr_of, host);
}

/*****************************************************************************/
static void hifmc100_send_cmd_pageprog(struct hifmc_host *host)
{
	unsigned int reg;
	struct hifmc_spi *spi = host->spi;
	unsigned char *hifmc_ip = NULL;
#ifndef CONFIG_SYS_DCACHE_OFF
	unsigned int dma_align_len;
#endif
	fmc_pr(WR_DBG, "\n*-Enter Dma page program!\n");

	hifmc_ip = get_hifmc_ip();
	if (*hifmc_ip) {
		printf("Warning: Hifmc IP is busy, Please try again.\n");
		udelay(1); /* delay 1 us */
		return;
	} else {
		hifmc_dev_type_switch(FLASH_TYPE_SPI_NAND);
		(*hifmc_ip)++;
	}

	reg = spi->driver->write_enable(spi);
	if (reg) {
		db_msg("Error: Dma program write enable failed! reg: %#x\n", reg);
		goto end;
	}

	host->set_system_clock(spi->write, ENABLE);

	if (ecc0_flag == 1) {
		hifmc100_ecc0_switch(host, ENABLE);
		hifmc_write(host, FMC_DMA_LEN, oobsize_real);
	}

	set_cs_addr_reg(WRITE, 0, host);

	if (ecc0_flag != 1)
		*host->epm = 0x0000;

#ifndef CONFIG_SYS_DCACHE_OFF
	dma_align_len = ((host->pagesize + host->oobsize +
	    CONFIG_SYS_CACHELINE_SIZE - 1) & ~(CONFIG_SYS_CACHELINE_SIZE - 1));
	flush_dcache_range(host->dma_buffer, host->dma_buffer + dma_align_len);
#endif

	set_dma_addr_reg(host);

	reg = op_ctrl_wr_opcode(spi->write->cmd) | op_ctrl_dma_op(OP_TYPE_DMA) |
		op_ctrl_rw_op(RW_OP_WRITE) | OP_CTRL_DMA_OP_READY;
	hifmc_write(host, FMC_OP_CTRL, reg);
	fmc_pr(WR_DBG, "|-Set OP_CTRL[%#x]%#x\n", FMC_OP_CTRL, reg);
	fmc_dma_wait_int_finish(host);

	if (ecc0_flag == 1)
		hifmc100_ecc0_switch(host, DISABLE);

	reg = spi->driver->wait_ready(spi);
	if (reg)
		db_msg("Error: Dma program wait ready failed! status: %#x\n", reg);

end:
	(*hifmc_ip)--;
	fmc_pr(WR_DBG, "*-End Dma page program!\n");
}
/*****************************************************************************/
static void hifmc100_send_cmd_readstart(struct hifmc_host *host)
{
	unsigned char only_oob = 0;
	unsigned int reg;
	struct hifmc_spi *spi = host->spi;
	unsigned char *hifmc_ip = NULL;
#ifndef CONFIG_SYS_DCACHE_OFF
	unsigned int dma_align_len;
#endif
	fmc_pr(RD_DBG, "\n\t*-Start Dma page read\n");

	hifmc_ip = get_hifmc_ip();
	if (*hifmc_ip) {
		printf("Warning: Hifmc IP is busy, Please try again.\n");
		udelay(1); /* delay 1 us */
		return;
	} else {
		hifmc_dev_type_switch(FLASH_TYPE_SPI_NAND);
		(*hifmc_ip)++;
	}

	host->set_system_clock(spi->read, ENABLE);

	if (ecc0_flag == 1 && (host->cmd_op.l_cmd != NAND_CMD_READOOB)) {
		hifmc100_ecc0_switch(host, ENABLE);
		hifmc_write(host, FMC_DMA_LEN, oobsize_real);
	}

	if (host->cmd_op.l_cmd == NAND_CMD_READOOB) {
		only_oob = 1;
		host->cmd_op.op_cfg = op_ctrl_rd_op_sel(RD_OP_READ_OOB);
	} else {
		host->cmd_op.op_cfg = op_ctrl_rd_op_sel(RD_OP_READ_ALL_PAGE);
	}

	set_cs_addr_reg(READ, only_oob, host);

#ifndef CONFIG_SYS_DCACHE_OFF
	dma_align_len = ((host->pagesize + host->oobsize +
		CONFIG_SYS_CACHELINE_SIZE - 1) & ~(CONFIG_SYS_CACHELINE_SIZE - 1));
	invalidate_dcache_range(host->dma_buffer, host->dma_buffer + dma_align_len);
#endif
	set_dma_addr_reg(host);

	reg = op_ctrl_rd_opcode(spi->read->cmd) |
			host->cmd_op.op_cfg | op_ctrl_dma_op(OP_TYPE_DMA) |
			op_ctrl_rw_op(RW_OP_READ) | OP_CTRL_DMA_OP_READY;
	hifmc_write(host, FMC_OP_CTRL, reg);
	fmc_pr(RD_DBG, "\t|-Set OP_CTRL[%#x]%#x\n", FMC_OP_CTRL, reg);
	fmc_dma_wait_int_finish(host);

	if (ecc0_flag == 1 && (host->cmd_op.l_cmd != NAND_CMD_READOOB))
		hifmc100_ecc0_switch(host, DISABLE);

#ifndef CONFIG_SYS_DCACHE_OFF
	invalidate_dcache_range(host->dma_buffer, host->dma_buffer + dma_align_len);
#endif

	(*hifmc_ip)--;
	fmc_pr(RD_DBG, "\t*-End Dma page read\n");
}

/*****************************************************************************/
static void hifmc100_send_cmd_erase(struct hifmc_host *host)
{
	unsigned int reg;
	struct hifmc_spi *spi = host->spi;
	unsigned char *hifmc_ip = NULL;

	if (ER_DBG)
		printf("\n");
	fmc_pr(ER_DBG, "\t*-Start send cmd erase!\n");

	hifmc_ip = get_hifmc_ip();
	if (*hifmc_ip) {
		printf("Warning: Hifmc IP is busy, Please try again.\n");
		udelay(1); /* delay 1 us */
		return;
	} else {
		hifmc_dev_type_switch(FLASH_TYPE_SPI_NAND);
		(*hifmc_ip)++;
	}

	reg = spi->driver->write_enable(spi);
	if (reg) {
		db_msg("Error: Erase write enable failed! reg: %#x\n", reg);
		goto end;
	}

	host->set_system_clock(spi->erase, ENABLE);

	reg = FMC_INT_CLR_ALL;
	hifmc_write(host, FMC_INT_CLR, reg);
	fmc_pr(ER_DBG, "\t|-Set INT_CLR[%#x]%#x\n", FMC_INT_CLR, reg);

	reg = spi->erase->cmd;
	hifmc_write(host, FMC_CMD, fmc_cmd_cmd1(reg));
	fmc_pr(ER_DBG, "\t|-Set CMD[%#x]%#x\n", FMC_CMD, reg);

	reg = fmc_addrl_block_h_mask(host->addr_value[1]) |
			fmc_addrl_block_l_mask(host->addr_value[0]);
	hifmc_write(host, FMC_ADDRL, reg);
	fmc_pr(ER_DBG, "\t|-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);

	reg = op_cfg_fm_cs(host->cmd_op.cs) | OP_CFG_OEN_EN |
		op_cfg_mem_if_type(spi->erase->iftype)      |
		op_cfg_addr_num(STD_OP_ADDR_NUM)            |
		op_cfg_dummy_num(spi->erase->dummy);

	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(ER_DBG, "\t|-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	reg = fmc_op_cmd1_en(ENABLE) | fmc_op_addr_en(ENABLE) |
		FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, reg);
	fmc_pr(ER_DBG, "\t|-Set OP[%#x]%#x\n", FMC_OP, reg);

	fmc_cmd_wait_cpu_finish(host);

	reg = spi->driver->wait_ready(spi);
	fmc_pr(ER_DBG, "\t|-Erase wait ready, reg: %#x\n", reg);
	if (reg)
		db_msg("Error: Erase wait ready fail! status: %#x\n", reg);

end:
	(*hifmc_ip)--;

	fmc_pr(ER_DBG, "\t*-End send cmd erase!\n");
}

/*****************************************************************************/
static void hifmc100_send_cmd_status(struct hifmc_host *host)
{
	unsigned char status;
	unsigned char addr = STATUS_ADDR;
	struct hifmc_spi *spi = host->spi;
	unsigned char *hifmc_ip = get_hifmc_ip();

	if (*hifmc_ip) {
		printf("Warning: Hifmc IP is busy, Please try again.\n");
		udelay(1); /* delay 1 us */
		return;
	} else {
		hifmc_dev_type_switch(FLASH_TYPE_SPI_NAND);
		(*hifmc_ip)++;
	}

	if (host->cmd_op.l_cmd == NAND_CMD_GET_FEATURES)
		addr = PROTECT_ADDR;

	status = spi_nand_feature_op(spi, GET_OP, addr, 0);
	fmc_pr((ER_DBG || WR_DBG), "\t*-Get status[%#x]: %#x\n", addr, status);

	(*hifmc_ip)--;
}

/*****************************************************************************/
static void hifmc100_send_cmd_readid(struct hifmc_host *host)
{
	unsigned int reg;

	fmc_pr(BT_DBG, "\t|*-Start send cmd read ID\n");

	hifmc100_ecc0_switch(host, ENABLE);

	reg = fmc_cmd_cmd1(SPI_CMD_RDID);
	hifmc_write(host, FMC_CMD, reg);
	fmc_pr(BT_DBG, "\t||-Set CMD[%#x]%#x\n", FMC_CMD, reg);

	reg = READ_ID_ADDR;
	hifmc_write(host, FMC_ADDRL, reg);
	fmc_pr(BT_DBG, "\t||-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);

	reg = op_cfg_fm_cs(host->cmd_op.cs) | OP_CFG_OEN_EN |
	      op_cfg_addr_num(READ_ID_ADDR_NUM);
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(BT_DBG, "\t||-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	reg = fmc_data_num_cnt(MAX_SPI_NAND_ID_LEN);
	hifmc_write(host, FMC_DATA_NUM, reg);
	fmc_pr(BT_DBG, "\t||-Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, reg);

	reg = fmc_op_cmd1_en(ENABLE) | fmc_op_addr_en(ENABLE) |
	      fmc_op_read_data_en(ENABLE) | FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, reg);
	fmc_pr(BT_DBG, "\t||-Set OP[%#x]%#x\n", FMC_OP, reg);

	host->addr_cycle = 0x0;

	fmc_cmd_wait_cpu_finish(host);

	hifmc100_ecc0_switch(host, DISABLE);

	fmc_pr(BT_DBG, "\t|*-End read flash ID\n");
}

/*****************************************************************************/
static void hifmc100_send_cmd_reset(struct hifmc_host *host)
{
	unsigned int reg;

	fmc_pr(BT_DBG, "\t|*-Start send cmd reset\n");

	reg = fmc_cmd_cmd1(SPI_CMD_RESET);
	hifmc_write(host, FMC_CMD, reg);
	fmc_pr(BT_DBG, "\t||-Set CMD[%#x]%#x\n", FMC_CMD, reg);

	reg = op_cfg_fm_cs(host->cmd_op.cs) | OP_CFG_OEN_EN;
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(BT_DBG, "\t||-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	reg = fmc_op_cmd1_en(ENABLE) | FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, reg);
	fmc_pr(BT_DBG, "\t||-Set OP[%#x]%#x\n", FMC_OP, reg);

	fmc_cmd_wait_cpu_finish(host);

	fmc_pr(BT_DBG, "\t|*-End send cmd reset\n");
}

/*****************************************************************************/
static unsigned char hifmc100_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;
	unsigned char value = 0;
	unsigned char ret_val = 0;

	if (host->cmd_op.l_cmd == NAND_CMD_READID) {
		value = readb(host->iobase + host->offset);
		host->offset++;
		if (host->cmd_op.data_no == host->offset)
			host->cmd_op.l_cmd = 0;
		return value;
	}

	if (host->cmd_op.cmd == NAND_CMD_STATUS) {
		value = hifmc_read(host, FMC_STATUS);
		if (host->cmd_op.l_cmd == NAND_CMD_GET_FEATURES) {
			fmc_pr((ER_DBG || WR_DBG), "\t\tRead BP status: %#x\n",
			       value);
			if (any_bp_enable(value))
				ret_val |= NAND_STATUS_WP;

			host->cmd_op.l_cmd = NAND_CMD_STATUS;
		}

		if (!(value & STATUS_OIP_MASK))
			ret_val |= NAND_STATUS_READY;

		if ((chip->state == FL_ERASING) &&
			(value & STATUS_E_FAIL_MASK)) {
			fmc_pr(ER_DBG, "\t\tGet erase status: %#x\n", value);
			ret_val |= NAND_STATUS_FAIL;
		}

		if ((chip->state == FL_WRITING) &&
			(value & STATUS_P_FAIL_MASK)) {
			fmc_pr(WR_DBG, "\t\tGet write status: %#x\n", value);
			ret_val |= NAND_STATUS_FAIL;
		}

		return ret_val;
	}

	if (host->cmd_op.l_cmd == NAND_CMD_READOOB) {
		value = readb((unsigned char *)
		   ((unsigned char *)(uintptr_t)host->dma_oob + host->offset));
		host->offset++;
		return value;
	}

	host->offset++;

	return readb(host->buffer + host->column + host->offset - 1);
}

/*****************************************************************************/
static unsigned short hifmc100_read_word(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	return readw(host->buffer + host->column + host->offset);
}

/*****************************************************************************/
static void hifmc100_write_buf(struct mtd_info *mtd, const u_char *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	if (buf == chip->oob_poi)
		memcpy((unsigned char *)(uintptr_t)host->dma_oob, buf, len);
	else
		memcpy((unsigned char *)(uintptr_t)host->dma_buffer, buf, len);
	return;
}

/*****************************************************************************/
static void hifmc100_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	if (buf == chip->oob_poi)
		memcpy(buf, (unsigned char *)(uintptr_t)host->dma_oob, len);
	else
		memcpy(buf, (unsigned char *)(uintptr_t)host->dma_buffer, len);
	return;
}

/*****************************************************************************/
static void hifmc100_select_chip(struct mtd_info *mtd, int chipselect)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	if (chipselect < 0)
		return;

	if (chipselect > CONFIG_SPI_NAND_MAX_CHIP_NUM)
		db_bug("Error: Invalid chipselect: %d\n", chipselect);

	if (host->mtd != mtd)
		host->mtd = mtd;

	if (!(chip->options & NAND_BROKEN_XD))
		if ((chip->state == FL_ERASING) || (chip->state == FL_WRITING))
			host->cmd_op.l_cmd = NAND_CMD_GET_FEATURES;
}

/******************************************************************************/
static void hifmc100_cmdfunc(struct mtd_info *mtd,
				unsigned int command,
				int column, int page_addr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	switch (command) {
	case NAND_CMD_RESET:
		host->send_cmd_reset(host);
		chip->dev_ready(mtd);
		break;
	case NAND_CMD_READID:
		host->offset = 0;
		host->cmd_op.l_cmd = command & 0xff;
		memset((u_char *)(host->iobase), 0, MAX_SPI_NAND_ID_LEN);
		host->cmd_op.data_no = MAX_SPI_NAND_ID_LEN;
		host->send_cmd_readid(host);
		break;
	case NAND_CMD_GET_FEATURES:
	case NAND_CMD_STATUS:
		host->cmd_op.l_cmd = command & 0xff;
		host->cmd_op.cmd = NAND_CMD_STATUS;
		host->send_cmd_status(host);
		break;
	case NAND_CMD_READOOB:
		host->offset = 0;
		host->cmd_op.l_cmd = command & 0xff;
		/* use same command as normal read */
		host->cmd_op.cmd = command & 0xff;
	case NAND_CMD_READ0:
		if (command == NAND_CMD_READ0)
			host->cmd_op.l_cmd = command & 0xff;
		host->addr_value[1] = page_addr;
		host->send_cmd_readstart(host);
		break;
	case NAND_CMD_SEQIN:
		host->addr_value[1] = page_addr;
		break;
	case NAND_CMD_PAGEPROG:
		host->offset = 0;
		host->send_cmd_pageprog(host);
		break;
	case NAND_CMD_ERASE1:
		host->cmd_op.l_cmd = command & 0xff;
		host->addr_value[0] = page_addr;
		/* page_addr to block_addr, move right 16 bits */
		host->addr_value[1] = (unsigned int)page_addr >> 16;
		/* erase operation need a seral of command sequences */
		host->send_cmd_erase(host);
		break;
	case NAND_CMD_ERASE2:
	case NAND_CMD_READSTART:
		break;
	default:
		printf("%s not support command 0x%08x:\n", mtd->name, command);
		break;
	}
}

/*****************************************************************************/
static int hifmc100_dev_ready(struct mtd_info *mtd)
{
	unsigned int reg = 0;
	/* just a big number, so move 12 bits */
	unsigned long deadline = 1 << 12;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	do {
		reg = op_cfg_fm_cs(host->cmd_op.cs) | OP_CFG_OEN_EN;
		hifmc_write(host, FMC_OP_CFG, reg);

		reg = fmc_op_read_status_en(ENABLE) | FMC_OP_REG_OP_START;
		hifmc_write(host, FMC_OP, reg);

		fmc_cmd_wait_cpu_finish(host);

		reg = hifmc_read(host, FMC_STATUS);
		if (!(reg & STATUS_OIP_MASK))
			return 1;

		udelay(1); /* delay 1 us */
	} while (deadline--);

#ifndef CONFIG_SYS_NAND_QUIET_TEST
	printf("Warning: Wait SPI nand ready timeout, status: %#x\n", reg);
#endif

	return 0;
}

/*****************************************************************************/
/*
 * 'host->epm' only use the first oobfree[0] field, it looks very simple, But..
 */
static struct nand_ecclayout nand_ecc_default = {
	.oobfree = {{2, 30} }
};

#ifdef CONFIG_FS_MAY_NOT_YAFFS2
static struct nand_ecclayout nand_ecc_2k16bit = {
	.oobfree = {{2, 6} }
};

static struct nand_ecclayout nand_ecc_4k16bit = {
	.oobfree = {{2, 14} }
};
#endif

/*****************************************************************************/
static struct nand_config_info hifmc_spi_nand_config_table[] = {
	{NAND_PAGE_4K,  NAND_ECC_24BIT, 200,    &nand_ecc_default},
#ifdef CONFIG_FS_MAY_NOT_YAFFS2
	{NAND_PAGE_4K,  NAND_ECC_16BIT, 128,    &nand_ecc_4k16bit},
#endif
	{NAND_PAGE_4K,  NAND_ECC_8BIT,  128,    &nand_ecc_default},
	{NAND_PAGE_4K,  NAND_ECC_0BIT,  32,     &nand_ecc_default},

	{NAND_PAGE_2K,  NAND_ECC_24BIT, 128,    &nand_ecc_default},
#ifdef CONFIG_FS_MAY_NOT_YAFFS2
	{NAND_PAGE_2K,  NAND_ECC_16BIT, 64,     &nand_ecc_2k16bit},
#endif
	{NAND_PAGE_2K,  NAND_ECC_8BIT,  64,     &nand_ecc_default},
	{NAND_PAGE_2K,  NAND_ECC_0BIT,  32,     &nand_ecc_default},

	{0,     0,      0,  NULL},
};

/*
 * Auto-sensed the page size and ecc type value. driver will try each of page
 * size and ecc type one by one till flash can be read and wrote accurately.
 * so the page size and ecc type is match adaptively without switch on the board
 */
static struct nand_config_info *hifmc100_get_config_type_info(struct mtd_info *mtd)
{
	struct nand_config_info *best = NULL;
	struct nand_config_info *info = hifmc_spi_nand_config_table;
	struct nand_chip *chip = mtd_to_nand(mtd);
	for (; info->layout; info++) {
		if (match_page_type_to_size(info->pagetype) != mtd->writesize)
			continue;

		if (mtd->oobsize < info->oobsize)
			continue;

		if (!best || (best->ecctype < info->ecctype))
			best = info;
	}
	/* All SPI NAND are small-page,SLC */
	chip->bits_per_cell = 1;
	return best;
}

/*****************************************************************************/
static void hifmc100_set_oob_info(struct mtd_info *mtd,
				struct nand_config_info *info)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	/* oobsize_real for ecc0 read and write */
	oobsize_real = mtd->oobsize;

	if (info->ecctype != NAND_ECC_0BIT)
		mtd->oobsize = info->oobsize;

	host->oobsize = mtd->oobsize;
	host->dma_oob = host->dma_buffer + host->pagesize;
	host->bbm = (u_char *)(host->buffer + host->pagesize
			       + HIFMC_BAD_BLOCK_POS);

	chip->ecc.layout = info->layout;

	/* EB bytes locate in the bottom two of CTRL(30) */
	host->epm = (u_short *)(host->buffer + host->pagesize
				+ chip->ecc.layout->oobfree[0].offset + EB_NORMAL);

#ifdef CONFIG_FS_MAY_NOT_YAFFS2

	if (best->ecctype == NAND_ECC_16BIT)
		if (host->pagesize == _2K)
			/* EB bits locate in the bottom two of CTRL(4) */
			host->epm = (u_short *)(host->buffer + host->pagesize
			 + chip->ecc.layout->oobfree[0].offset + EB_2K_16_BIT);
		else if (host->pagesize == _4K)
			/* EB bit locate in the bottom two of CTRL(14) */
			host->epm = (u_short *)(host->buffer + host->pagesize
			 + chip->ecc.layout->oobfree[0].offset + EB_4K_16_BIT);

#endif
}

/*****************************************************************************/
static unsigned int hifmc100_get_ecc_reg(struct hifmc_host *host,
				struct nand_config_info *info)
{
	host->ecctype = info->ecctype;

	return fmc_cfg_ecc_type(match_ecc_type_to_reg(info->ecctype));
}

/*****************************************************************************/
static unsigned int hifmc100_get_page_reg(struct hifmc_host *host,
				struct nand_config_info *info)
{
	host->pagesize = match_page_type_to_size(info->pagetype);

	return fmc_cfg_page_size(match_page_type_to_reg(info->pagetype));
}

/*****************************************************************************/
static unsigned int hifmc100_get_block_reg(struct hifmc_host *host,
				struct nand_config_info *info)
{
	unsigned int block_reg = 0;
	unsigned int page_per_block;
	struct mtd_info *mtd = host->mtd;

	host->block_page_mask = ((mtd->erasesize / mtd->writesize) - 1);
	page_per_block = mtd->erasesize / match_page_type_to_size(info->pagetype);
	switch (page_per_block) {
	case _64_PAGES:
		block_reg = BLOCK_SIZE_64_PAGE;
		break;
	case _128_PAGES:
		block_reg = BLOCK_SIZE_128_PAGE;
		break;
	case _256_PAGES:
		block_reg = BLOCK_SIZE_256_PAGE;
		break;
	case _512_PAGES:
		block_reg = BLOCK_SIZE_512_PAGE;
		break;
	default:
		db_msg("Can't support block %#x and page %#x size\n",
		       mtd->erasesize, mtd->writesize);
	}

	return fmc_cfg_block_size(block_reg);
}

/*****************************************************************************/
static void hifmc100_set_fmc_cfg_reg(struct mtd_info *mtd,
				struct nand_config_info *type_info)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;
	unsigned int page_reg, ecc_reg, block_reg, reg_fmc_cfg;

	ecc_reg = hifmc100_get_ecc_reg(host, type_info);
	page_reg = hifmc100_get_page_reg(host, type_info);
	block_reg = hifmc100_get_block_reg(host, type_info);

	reg_fmc_cfg = hifmc_read(host, FMC_CFG);
	reg_fmc_cfg &= ~(PAGE_SIZE_MASK | ECC_TYPE_MASK | BLOCK_SIZE_MASK);
	reg_fmc_cfg |= ecc_reg | page_reg | block_reg;
	hifmc_write(host, FMC_CFG, reg_fmc_cfg);

	/* max number of correctible bit errors per ecc step */
	mtd->ecc_strength = host->ecctype;

	/* Save value of FMC_CFG and FMC_CFG_ECC0 to turn on/off ECC */
	host->fmc_cfg = reg_fmc_cfg;
	host->fmc_cfg_ecc0 = (host->fmc_cfg & ~ECC_TYPE_MASK) | ECC_TYPE_0BIT;
	fmc_pr(BT_DBG, "\t|-Save FMC_CFG[%#x]: %#x and FMC_CFG_ECC0: %#x\n",
	       FMC_CFG, host->fmc_cfg, host->fmc_cfg_ecc0);
}

/*****************************************************************************/
static int hifmc100_set_config_info(struct mtd_info *mtd)
{
	struct nand_config_info *type_info = NULL;

	fmc_pr(BT_DBG, "\t*-Start match PageSize and EccType\n");

	type_info = hifmc100_get_config_type_info(mtd);
	if (!type_info)
		db_bug(ERR_STR_DRIVER "pagesize: %d and oobsize: %d.\n",
		       mtd->writesize, mtd->oobsize);

	/* Set the page_size, ecc_type, block_size of FMC_CFG[0x0] register */
	hifmc100_set_fmc_cfg_reg(mtd, type_info);

	fmc_pr(BT_DBG, "\t|- PageSize %s EccType %s OOB Size %d\n",
	       nand_page_name(type_info->pagetype),
	       nand_ecc_name(type_info->ecctype), type_info->oobsize);

	hifmc100_set_oob_info(mtd, type_info);

	fmc_pr(BT_DBG, "\t*-End match PageSize and EccType\n");

	return 0;
}

/*****************************************************************************/
static void hifmc100_chip_init(struct nand_chip *chip)
{
	if (!chip->IO_ADDR_R)
		chip->IO_ADDR_R = (void __iomem *)CONFIG_HIFMC_BUFFER_BASE;
	chip->IO_ADDR_W = chip->IO_ADDR_R;
	memset((char *)chip->IO_ADDR_R, 0xff, HIFMC100_BUFFER_LEN);

	chip->read_byte = hifmc100_read_byte;
	chip->read_word = hifmc100_read_word;
	chip->write_buf = hifmc100_write_buf;
	chip->read_buf = hifmc100_read_buf;

	chip->select_chip = hifmc100_select_chip;

	chip->cmdfunc = hifmc100_cmdfunc;
	chip->dev_ready = hifmc100_dev_ready;

	chip->chip_delay = FMC_CHIP_DELAY;

	chip->options = NAND_BBT_SCANNED | NAND_BROKEN_XD;

	chip->ecc.layout = NULL;
	chip->ecc.mode = NAND_ECC_NONE;
}

/*****************************************************************************/
int host_data_init(struct hifmc_host *host)
{
	unsigned long align_mask;

	host->addr_cycle = 0;
	host->addr_value[0] = 0;
	host->addr_value[1] = 0;
	host->cache_addr_value[0] = ~0;
	host->cache_addr_value[1] = ~0;

	fmc_pr(BT_DBG, "\t|||-Malloc memory for dma buffer\n");
	host->buforg = kmalloc((HIFMC100_BUFFER_LEN + FMC_DMA_ALIGN),
			       GFP_KERNEL);
	if (!host->buforg) {
		db_msg("Error: Can't malloc memory for SPI Nand driver.\n");
		return -ENOMEM;
	}
	memset(host->buforg, 0xff, HIFMC100_BUFFER_LEN + FMC_DMA_ALIGN);

	/* DMA need 32 bytes alignment */
	align_mask = FMC_DMA_ALIGN - 1;
	host->dma_buffer = (uintptr_t)(host->buforg + align_mask) & ~align_mask;

	host->buffer = (char *)(uintptr_t)host->dma_buffer;
	memset(host->buffer, 0xff, HIFMC100_BUFFER_LEN);

	host->send_cmd_pageprog = hifmc100_send_cmd_pageprog;
	host->send_cmd_status = hifmc100_send_cmd_status;
	host->send_cmd_readstart = hifmc100_send_cmd_readstart;
	host->send_cmd_erase = hifmc100_send_cmd_erase;
	host->send_cmd_readid = hifmc100_send_cmd_readid;
	host->send_cmd_reset = hifmc100_send_cmd_reset;
	host->set_system_clock = hifmc_set_fmc_system_clock;

	return 0;
}
/*****************************************************************************/
int hifmc100_host_init(struct hifmc_host *host)
{
	unsigned int reg;
	unsigned int flash_type;
	int ret;

	fmc_pr(BT_DBG, "\t||*-Start SPI Nand host init\n");
	host->iobase = (void __iomem *)CONFIG_HIFMC_BUFFER_BASE;
	host->regbase = (void __iomem *)CONFIG_HIFMC_REG_BASE;

	reg = hifmc_read(host, FMC_CFG);
	flash_type = (reg & FLASH_SEL_MASK) >> FLASH_SEL_SHIFT;
	if (flash_type != FLASH_TYPE_SPI_NAND) {
		db_msg("Error: Flash type isn't SPI Nand. reg: %#x\n", reg);
		return -ENODEV;
	}

	if ((reg & OP_MODE_MASK) == OP_MODE_BOOT) {
		reg |= fmc_cfg_op_mode(OP_MODE_NORMAL);
		hifmc_write(host, FMC_CFG, reg);
		fmc_pr(BT_DBG, "\t|||-Set CFG[%#x]%#x\n", FMC_CFG, reg);
	}

	host->fmc_cfg = reg;
	host->fmc_cfg_ecc0 = (reg & ~ECC_TYPE_MASK) | ECC_TYPE_0BIT;

	reg = hifmc_read(host, FMC_GLOBAL_CFG);
	if (reg & FMC_GLOBAL_CFG_WP_ENABLE) {
		reg &= ~FMC_GLOBAL_CFG_WP_ENABLE;
		hifmc_write(host, FMC_GLOBAL_CFG, reg);
	}

	ret = host_data_init(host);
	if (ret)
	    return ret;

	/* ecc0_flag for ecc0 read/write */
	ecc0_flag = 0;

	reg = timing_cfg_tcsh(CS_HOLD_TIME) |
	      timing_cfg_tcss(CS_SETUP_TIME) |
	      timing_cfg_tshsl(CS_DESELECT_TIME);
	hifmc_write(host, FMC_SPI_TIMING_CFG, reg);
	fmc_pr(BT_DBG, "\t|||-Set TIMING[%#x]%#x\n", FMC_SPI_TIMING_CFG, reg);

	reg = ALL_BURST_ENABLE;
	hifmc_write(host, FMC_DMA_AHB_CTRL, reg);
	fmc_pr(BT_DBG, "\t|||-Set DMA_AHB[%#x]%#x\n", FMC_DMA_AHB_CTRL, reg);

	fmc_pr(BT_DBG, "\t|||-Register SPI Nand ID table and ecc probe\n");
	hifmc_spi_nand_ids_register();
	nand_oob_resize = hifmc100_set_config_info;

	fmc_pr(BT_DBG, "\t||*-End SPI Nand host init\n");

	return 0;
}

/*****************************************************************************/
void hifmc100_spi_nand_init(struct hifmc_host *host)
{
	struct nand_chip *chip = host->chip;

	fmc_pr(BT_DBG, "\t|*-Start hifmc100 SPI Nand init\n");

	/* Set system clock and enable controller */
	fmc_pr(BT_DBG, "\t||-Set system clock and Enable Controller\n");
	if (host->set_system_clock)
		host->set_system_clock(NULL, ENABLE);

	/* Hifmc nand_chip struct init */
	fmc_pr(BT_DBG, "\t||-Hifmc100 struct nand_chip init\n");
	chip->priv = host;
	hifmc100_chip_init(chip);

	fmc_pr(BT_DBG, "\t|*-End hifmc100 SPI Nand init\n");
}
