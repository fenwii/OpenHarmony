/*
 * hifmc100_nand.c
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

#include "hifmc100_nand.h"
#include <common.h>
#include <malloc.h>
#include <asm/io.h>
#include <errno.h>

/*****************************************************************************/
static struct hifmc_host fmc_host = {
	.chip = NULL,
};

/*****************************************************************************/
static void hifmc100_dma_transfer(struct hifmc_host *host, int todev)
{
	unsigned int reg;
	char *op = todev ? "write" : "read";

	fmc_pr(DMA_DB, "\t\t *-Start %s page dma transfer\n", op);
	/* get hight 32 bits addr */
	reg = (host->dma_buffer & FMC_DMA_SADDRH_MASK) >> 32;
	hifmc_write(host, FMC_DMA_SADDRH_D0, reg);
	fmc_pr(DMA_DB, "\t\t |-Set ADDR0[%#x]%#x\n", FMC_DMA_SADDRH_D0, reg);

	reg = (unsigned int)host->dma_buffer;
	hifmc_write(host, FMC_DMA_SADDR_D0, reg);
	fmc_pr(DMA_DB, "\t\t |-Set ADDR0[%#x]%#x\n", FMC_DMA_SADDR_D0, reg);

	reg += FMC_DMA_ADDR_OFFSET;
	hifmc_write(host, FMC_DMA_SADDR_D1, reg);
	fmc_pr(DMA_DB, "\t\t |-Set ADDR1[%#x]%#x\n", FMC_DMA_SADDR_D1, reg);

	reg += FMC_DMA_ADDR_OFFSET;
	hifmc_write(host, FMC_DMA_SADDR_D2, reg);
	fmc_pr(DMA_DB, "\t\t |-Set ADDR2[%#x]%#x\n", FMC_DMA_SADDR_D2, reg);

	reg += FMC_DMA_ADDR_OFFSET;
	hifmc_write(host, FMC_DMA_SADDR_D3, reg);
	fmc_pr(DMA_DB, "\t\t |-Set ADDR3[%#x]%#x\n", FMC_DMA_SADDR_D3, reg);
	/* get hight 32 bits addr */
	reg = (host->dma_oob & FMC_DMA_SADDRH_MASK) >> 32;
	hifmc_write(host, FMC_DMA_SADDRH_OOB, reg);

	reg = (unsigned int)host->dma_oob;
	hifmc_write(host, FMC_DMA_SADDR_OOB, reg);
	fmc_pr(DMA_DB, "\t\t |-Set OOB[%#x]%#x\n", FMC_DMA_SADDR_OOB, reg);

	if (host->ecctype == NAND_ECC_0BIT) {
		hifmc_write(host, FMC_DMA_LEN, fmc_dma_len_set(host->oobsize));
		fmc_pr(DMA_DB, "\t\t |-Set LEN[%#x]%#x\n", FMC_DMA_LEN, reg);
	}
	reg = fmc_op_read_data_en(ENABLE) | fmc_op_write_data_en(ENABLE);
	hifmc_write(host, FMC_OP, reg);
	fmc_pr(DMA_DB, "\t\t |-Set OP[%#x]%#x\n", FMC_OP, reg);

	reg = FMC_DMA_AHB_CTRL_DMA_PP_EN | FMC_DMA_AHB_CTRL_BURST16_EN |
	      FMC_DMA_AHB_CTRL_BURST8_EN | FMC_DMA_AHB_CTRL_BURST4_EN;
	hifmc_write(host, FMC_DMA_AHB_CTRL, reg);
	fmc_pr(DMA_DB, "\t\t |-Set AHBCTRL[%#x]%#x\n", FMC_DMA_AHB_CTRL, reg);

	reg = op_cfg_fm_cs(host->cmd_op.cs) | op_cfg_addr_num(host->addr_cycle);
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(DMA_DB, "\t\t |-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	reg = OP_CTRL_DMA_OP_READY;
	if (todev)
		reg |= op_ctrl_rw_op(todev);
	hifmc_write(host, FMC_OP_CTRL, reg);
	fmc_pr(DMA_DB, "\t\t |-Set OP_CTRL[%#x]%#x\n", FMC_OP_CTRL, reg);

	fmc_dma_wait_cpu_finish(host);

	fmc_pr(DMA_DB, "\t\t *-End %s page dma transfer\n", op);

	return;
}

/*****************************************************************************/
static void hifmc100_send_cmd_write(struct hifmc_host *host)
{
	unsigned int reg;

	fmc_pr(WR_DBG, "\t|*-Start send page programme cmd\n");

	if (*host->bbm != 0xFF && *host->bbm != 0x00)
		printf("WARNING: attempt to write an invalid bbm. " \
		       "page: 0x%08x, mark: 0x%02x,\n",
		       get_page_index(host), *host->bbm);

	if (ecc0_flag == 1) {
		host->enable_ecc_randomizer(host, DISABLE, DISABLE);
		hifmc_write(host, FMC_DMA_LEN, oobsize_real);
	} else {
		host->enable_ecc_randomizer(host, ENABLE, ENABLE);
	}

	reg = host->addr_value[1];
	hifmc_write(host, FMC_ADDRH, reg);
	fmc_pr(WR_DBG, "\t||-Set ADDRH[%#x]%#x\n", FMC_ADDRH, reg);

	reg = host->addr_value[0] & 0xffff0000;
	hifmc_write(host, FMC_ADDRL, reg);
	fmc_pr(WR_DBG, "\t||-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);

	reg = fmc_cmd_cmd2(NAND_CMD_PAGEPROG) | fmc_cmd_cmd1(NAND_CMD_SEQIN);
	hifmc_write(host, FMC_CMD, reg);
	fmc_pr(WR_DBG, "\t||-Set CMD[%#x]%#x\n", FMC_CMD, reg);

	if (ecc0_flag != 1)
		*host->epm = 0x0000;

#ifndef CONFIG_SYS_DCACHE_OFF
	flush_dcache_range(host->dma_buffer,
			   host->dma_buffer + host->pagesize + host->oobsize);
#endif

	hifmc100_dma_transfer(host, RW_OP_WRITE);

	if (ecc0_flag == 1)
		host->enable_ecc_randomizer(host, ENABLE, ENABLE);

	fmc_pr(WR_DBG, "\t|*-End send page read cmd\n");
}

/*****************************************************************************/
static void hifmc100_send_cmd_read(struct hifmc_host *host)
{
	unsigned int reg;

	fmc_pr(RD_DBG, "\t*-Start send page read cmd\n");

	host->page_status = 0;

	if (ecc0_flag == 1 && (host->cmd_op.l_cmd != NAND_CMD_READOOB)) {
		host->enable_ecc_randomizer(host, DISABLE, DISABLE);
		hifmc_write(host, FMC_DMA_LEN, oobsize_real);
	} else {
		host->enable_ecc_randomizer(host, ENABLE, ENABLE);
		reg = host->nand_cfg;
		hifmc_write(host, FMC_CFG, reg);
		fmc_pr(RD_DBG, "\t|-Set CFG[%#x]%#x\n", FMC_CFG, reg);
	}
	reg = FMC_INT_CLR_ALL;
	hifmc_write(host, FMC_INT_CLR, reg);
	fmc_pr(RD_DBG, "\t|-Set INT_CLR[%#x]%#x\n", FMC_INT_CLR, reg);

	reg = host->addr_value[1];
	hifmc_write(host, FMC_ADDRH, reg);
	fmc_pr(RD_DBG, "\t|-Set ADDRH[%#x]%#x\n", FMC_ADDRH, reg);

	reg = host->addr_value[0] & 0xffff0000;
	hifmc_write(host, FMC_ADDRL, reg);
	fmc_pr(RD_DBG, "\t|-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);

	reg = fmc_cmd_cmd2(NAND_CMD_READSTART) | fmc_cmd_cmd1(NAND_CMD_READ0);
	hifmc_write(host, FMC_CMD, reg);
	fmc_pr(RD_DBG, "\t|-Set CMD[%#x]%#x\n", FMC_CMD, reg);

#ifndef CONFIG_SYS_DCACHE_OFF
	invalidate_dcache_range(host->dma_buffer,
			host->dma_buffer + host->pagesize + host->oobsize);
#endif

	hifmc100_dma_transfer(host, RW_OP_READ);

#ifndef CONFIG_SYS_DCACHE_OFF
	invalidate_dcache_range(host->dma_buffer,
			host->dma_buffer + host->pagesize + host->oobsize);
#endif

	if (hifmc_read(host, FMC_INT) & FMC_INT_ERR_INVALID)
		host->page_status |= HIFMC100_PS_UC_ECC;

	if (ecc0_flag == 1 && (host->cmd_op.l_cmd != NAND_CMD_READOOB))
		host->enable_ecc_randomizer(host, ENABLE, ENABLE);

	fmc_pr(RD_DBG, "\t*-End send page read cmd\n");
}

/*****************************************************************************/
static void hifmc100_send_cmd_erase(struct hifmc_host *host)
{
	unsigned int reg;

	fmc_pr(ER_DBG, "\t *-Start send cmd erase\n");

	/* Don't case the read retry config */
	host->enable_ecc_randomizer(host, DISABLE, DISABLE);

	reg = host->addr_value[0];
	hifmc_write(host, FMC_ADDRL, reg);
	fmc_pr(ER_DBG, "\t |-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);

	reg = fmc_cmd_cmd2(NAND_CMD_ERASE2) | fmc_cmd_cmd1(NAND_CMD_ERASE1);
	hifmc_write(host, FMC_CMD, reg);
	fmc_pr(ER_DBG, "\t |-Set CMD[%#x]%#x\n", FMC_CMD, reg);

	reg = op_cfg_fm_cs(host->cmd_op.cs) |
	      op_cfg_addr_num(host->addr_cycle);
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(ER_DBG, "\t |-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	/* need to config WAIT_READY_EN */
	reg = fmc_op_wait_ready_en(ENABLE) |
	      fmc_op_cmd1_en(ENABLE) |
	      fmc_op_cmd2_en(ENABLE) |
	      fmc_op_addr_en(ENABLE) |
	      FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, reg);
	fmc_pr(ER_DBG, "\t |-Set OP[%#x]%#x\n", FMC_OP, reg);

	fmc_cmd_wait_cpu_finish(host);

	fmc_pr(ER_DBG, "\t |*-End send cmd erase\n");
}

/*****************************************************************************/
static void hifmc100_ecc_randomizer(struct hifmc_host *host, int ecc_en,
				int randomizer_en)
{
	unsigned int old_reg = 0;
	unsigned int reg = 0;
	unsigned int change = 0;
	char *ecc_op = ecc_en ? "Quit" : "Enter";
	char *rand_op = randomizer_en ? "Enable" : "Disable";

	if (is_randomizer(host)) {
		reg = old_reg = hifmc_read(host, FMC_GLOBAL_CFG);
		if (randomizer_en)
			reg |= FMC_GLOBAL_CFG_RANDOMIZER_EN;
		else
			reg &= ~FMC_GLOBAL_CFG_RANDOMIZER_EN;

		if (old_reg != reg) {
			fmc_pr(EC_DBG, "\t |*-Start %s randomizer\n", rand_op);
			fmc_pr(EC_DBG, "\t ||-Get global CFG[%#x]%#x\n",
			       FMC_GLOBAL_CFG, old_reg);
			hifmc_write(host, FMC_GLOBAL_CFG, reg);
			fmc_pr(EC_DBG, "\t ||-Set global CFG[%#x]%#x\n",
			       FMC_GLOBAL_CFG, reg);
			change++;
		}
	}

	old_reg = hifmc_read(host, FMC_CFG);
	reg = (ecc_en ? host->nand_cfg : host->nand_cfg_ecc0);

	if (old_reg != reg) {
		fmc_pr(EC_DBG, "\t |%s-Start %s ECC0 mode\n",
						change ? "|" : "*", ecc_op);
		fmc_pr(EC_DBG, "\t ||-Get CFG[%#x]%#x\n", FMC_CFG, old_reg);
		hifmc_write(host, FMC_CFG, reg);
		fmc_pr(EC_DBG, "\t ||-Set CFG[%#x]%#x\n", FMC_CFG, reg);
		change++;
	}

	if (EC_DBG && change)
		fmc_pr(EC_DBG, "\t |*-End randomizer and ECC0 mode config\n");
}

/*****************************************************************************/
static void hifmc100_send_cmd_status(struct hifmc_host *host)
{
	unsigned int regval;

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);

	regval = op_cfg_fm_cs(host->cmd_op.cs);
	hifmc_write(host, FMC_OP_CFG, regval);

	regval = fmc_op_read_status_en(ENABLE) | FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, regval);

	fmc_cmd_wait_cpu_finish(host);
}

/*****************************************************************************/
static void hifmc100_send_cmd_readid(struct hifmc_host *host)
{
	unsigned int reg;

	fmc_pr(BT_DBG, "\t *-Start read nand flash ID\n");

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);

	reg = fmc_data_num_cnt(host->cmd_op.data_no);
	hifmc_write(host, FMC_DATA_NUM, reg);
	fmc_pr(BT_DBG, "\t |-Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, reg);

	reg = fmc_cmd_cmd1(NAND_CMD_READID);
	hifmc_write(host, FMC_CMD, reg);
	fmc_pr(BT_DBG, "\t |-Set CMD[%#x]%#x\n", FMC_CMD, reg);

	reg = 0;
	hifmc_write(host, FMC_ADDRL, reg);
	fmc_pr(BT_DBG, "\t |-Set ADDRL[%#x]%#x\n", FMC_ADDRL, reg);

	reg = op_cfg_fm_cs(host->cmd_op.cs) |
		  op_cfg_addr_num(READ_ID_ADDR_NUM);
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(BT_DBG, "\t |-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	reg = fmc_op_cmd1_en(ENABLE) |
	      fmc_op_addr_en(ENABLE) |
	      fmc_op_read_data_en(ENABLE) |
	      FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, reg);
	fmc_pr(BT_DBG, "\t |-Set OP[%#x]%#x\n", FMC_OP, reg);

	host->addr_cycle = 0x0;

	fmc_cmd_wait_cpu_finish(host);

	fmc_pr(BT_DBG, "\t *-End read nand flash ID\n");
}

/*****************************************************************************/
static void hifmc100_send_cmd_reset(struct hifmc_host *host)
{
	unsigned int reg;

	fmc_pr(BT_DBG, "\t *-Start reset nand flash\n");

	reg = fmc_cmd_cmd1(NAND_CMD_RESET);
	hifmc_write(host, FMC_CMD, reg);
	fmc_pr(BT_DBG, "\t |-Set CMD[%#x]%#x\n", FMC_CMD, reg);

	reg = op_cfg_fm_cs(host->cmd_op.cs);
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(BT_DBG, "\t |-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	reg = fmc_op_cmd1_en(ENABLE) |
			fmc_op_wait_ready_en(ENABLE) |
			FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, reg);
	fmc_pr(BT_DBG, "\t |-Set OP[%#x]%#x\n", FMC_OP, reg);

	fmc_cmd_wait_cpu_finish(host);

	fmc_pr(BT_DBG, "\t *-End reset nand flash\n");
}

/*****************************************************************************/
static unsigned char hifmc100_read_byte(struct mtd_info *mtd)
{
	unsigned char value = 0;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	if (host->cmd_op.l_cmd == NAND_CMD_READID) {
		value = readb(chip->IO_ADDR_R + host->offset);
		host->offset++;
		if (host->cmd_op.data_no == host->offset)
			host->cmd_op.l_cmd = 0;
		return value;
	}

	if (host->cmd_op.cmd == NAND_CMD_STATUS) {
		value = hifmc_read(host, FMC_STATUS);
		if (host->cmd_op.l_cmd == NAND_CMD_ERASE1)
			fmc_pr(ER_DBG, "\t*-Erase WP status: %#x\n", value);
		if (host->cmd_op.l_cmd == NAND_CMD_PAGEPROG)
			fmc_pr(WR_DBG, "\t*-Write WP status: %#x\n", value);
		return value;
	}

	if (host->cmd_op.l_cmd == NAND_CMD_READOOB) {
		value = readb(host->dma_oob + host->offset);
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
static void hifmc100_write_buf(struct mtd_info *mtd,
				const u_char *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

#ifdef HIFMC100_NAND_SUPPORT_REG_WRITE
	if (buf == chip->oob_poi)
		memcpy((char *)host->iobase + host->pagesize, buf, len);
	else
		memcpy((char *)host->iobase, buf, len);
#else
	if (buf == chip->oob_poi)
		memcpy((char *)host->dma_oob, buf, len);
	else
		memcpy((char *)host->dma_buffer, buf, len);
#endif
	return;
}

/*****************************************************************************/
static void hifmc100_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

#ifdef HIFMC100_NAND_SUPPORT_REG_READ
	if (buf == chip->oob_poi)
		memcpy(buf, (char *)host->iobase + host->pagesize, len);
	else
		memcpy(buf, (char *)host->iobase, len);
#else
	if (buf == chip->oob_poi)
		memcpy(buf, (char *)host->dma_oob, len);
	else
		memcpy(buf, (char *)host->dma_buffer, len);
#endif
	return;
}

/*****************************************************************************/
static void hifmc100_select_chip(struct mtd_info *mtd, int chipselect)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	if (chipselect < 0)
		return;

	if (chipselect > CONFIG_SYS_MAX_NAND_DEVICE)
		db_bug("Error: Invalid chip select: %d\n", chipselect);

	host->cmd_op.cs = chipselect;
	if (host->mtd != mtd)
		host->mtd = mtd;

	switch (chip->state) {
	case FL_ERASING:
		host->cmd_op.l_cmd = NAND_CMD_ERASE1;
		if (ER_DBG)
			printf("\n");
		fmc_pr(ER_DBG, "\t*-Erase chip: %d\n", chipselect);
		break;
	case FL_WRITING:
		host->cmd_op.l_cmd = NAND_CMD_PAGEPROG;
		if (WR_DBG)
			printf("\n");
		fmc_pr(WR_DBG, "\t*-Write chip: %d\n", chipselect);
		break;
	case FL_READING:
		host->cmd_op.l_cmd = NAND_CMD_READ0;
		if (RD_DBG)
			printf("\n");
		fmc_pr(RD_DBG, "\t*-Read chip: %d\n", chipselect);
		break;
	default:
		break;
	}
}


/*****************************************************************************/
static int hifmc100_dev_ready(struct mtd_info *mtd)
{
	return 0x1;
}

/*****************************************************************************/
/*
 * 'host->epm' only use the first oobfree[0] field, it looks very simple, But...
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
/* ecc/pagesize get from NAND controller */
static struct nand_config_info hifmc100_nand_hw_auto_config_table[] = {
	{NAND_PAGE_16K, NAND_ECC_64BIT, 1824 /* 1824 */, &nand_ecc_default},
	{NAND_PAGE_16K, NAND_ECC_40BIT, 1200 /* 1152 */, &nand_ecc_default},
	{NAND_PAGE_16K, NAND_ECC_0BIT,  32,          &nand_ecc_default},

	{NAND_PAGE_8K, NAND_ECC_64BIT, 928 /* 928 */,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_40BIT, 600 /* 592 */,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_24BIT, 368 /* 368 */,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_0BIT,  32,          &nand_ecc_default},

	{NAND_PAGE_4K, NAND_ECC_24BIT, 200 /* 200 */,  &nand_ecc_default},
#ifdef CONFIG_FS_MAY_NOT_YAFFS2
	{NAND_PAGE_4K, NAND_ECC_16BIT,  128 /* 128 */,  &nand_ecc_default},
#endif
	{NAND_PAGE_4K, NAND_ECC_8BIT,  128 /* 88 */,   &nand_ecc_default},
	{NAND_PAGE_4K, NAND_ECC_0BIT,  32,           &nand_ecc_default},

	{NAND_PAGE_2K, NAND_ECC_24BIT, 128 /* 116 */, &nand_ecc_default},
#ifndef CONFIG_SUPPORT_YAFFS
	{NAND_PAGE_2K, NAND_ECC_16BIT,  64 /* 64 */, &nand_ecc_default},
#endif
	{NAND_PAGE_2K, NAND_ECC_8BIT,  64  /* 60 */,  &nand_ecc_default},
	{NAND_PAGE_2K, NAND_ECC_0BIT,  32,          &nand_ecc_default},

	{0,     0,      0,  NULL},
};

/*****************************************************************************/
/*
 *  0 - This NAND NOT support randomizer
 *  1 - This NAND support randomizer.
 */
static int hifmc100_nand_support_randomizer(u_int pageisze, u_int ecctype)
{
	switch (pageisze) {
	case _8K:
		return (ecctype >= NAND_ECC_24BIT && ecctype <= NAND_ECC_80BIT);
	case _16K:
		return (ecctype >= NAND_ECC_40BIT && ecctype <= NAND_ECC_80BIT);
	case _32K:
		return (ecctype >= NAND_ECC_40BIT && ecctype <= NAND_ECC_80BIT);
	default:
		return 0;
	}
}

/*****************************************************************************/
/* used the best correct arithmetic. */
static struct nand_config_info *hifmc100_get_config_type_info(
	struct nand_config_info *config, struct mtd_info *mtd)
{
	struct nand_config_info *best = NULL;

	for (; config->layout; config++) {
		if (match_page_type_to_size(config->pagetype) != mtd->writesize)
			continue;

		if (mtd->oobsize < config->oobsize)
			continue;

		if (!best || (best->ecctype < config->ecctype))
			best = config;
	}

	return best;
}

/*****************************************************************************/
static unsigned int hifmc100_get_ecc_reg(struct hifmc_host *host,
				struct nand_config_info *info)
{
	struct mtd_info *mtd = host->mtd;

	host->ecctype = info->ecctype;
	fmc_pr(BT_DBG, "\t |-Save best EccType %d(%s)\n", host->ecctype,
	       match_ecc_type_to_str(info->ecctype));

	mtd->ecc_strength = host->ecctype;

	return fmc_cfg_ecc_type(match_ecc_type_to_reg(info->ecctype));
}

/*****************************************************************************/
static unsigned int hifmc100_get_page_reg(struct hifmc_host *host,
				struct nand_config_info *info)
{
	host->pagesize = match_page_type_to_size(info->pagetype);
	fmc_pr(BT_DBG, "\t |-Save best PageSize %d(%s)\n", host->pagesize,
	       match_page_type_to_str(info->pagetype));

	return fmc_cfg_page_size(match_page_type_to_reg(info->pagetype));
}

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
static void hifmc100_set_fmc_cfg_reg(struct hifmc_host *host,
				struct nand_config_info *type_info)
{
	unsigned int page_reg, ecc_reg, block_reg, reg_fmc_cfg;

	ecc_reg = hifmc100_get_ecc_reg(host, type_info);
	page_reg = hifmc100_get_page_reg(host, type_info);
	block_reg = hifmc100_get_block_reg(host, type_info);

	if (hifmc100_nand_support_randomizer(host->pagesize, host->ecctype))
		host->flags |= NAND_RANDOMIZER;

	/* Save value of FMC_CFG and FMC_CFG_ECC0 to turn on/off ECC */
	reg_fmc_cfg = hifmc_read(host, FMC_CFG);
	reg_fmc_cfg &= ~(PAGE_SIZE_MASK | ECC_TYPE_MASK | BLOCK_SIZE_MASK);
	reg_fmc_cfg |= ecc_reg | page_reg | block_reg;
	host->nand_cfg = reg_fmc_cfg;
	host->nand_cfg_ecc0 = (host->nand_cfg & ~ECC_TYPE_MASK) | ECC_TYPE_0BIT;
	fmc_pr(BT_DBG, "\t|-Save FMC_CFG[%#x]: %#x and FMC_CFG_ECC0: %#x\n",
	       FMC_CFG, host->nand_cfg, host->nand_cfg_ecc0);

	/* pass pagesize and ecctype to kernel when spiflash startup. */
	host->enable_ecc_randomizer(host, ENABLE, ENABLE);

	/*
	 * If it want to support the 'read retry' feature, the 'randomizer'
	 * feature must be support first.
	 */
	host->read_retry = NULL;

	if (host->read_retry && !is_randomizer(host)) {
		db_bug(ERSTR_HARDWARE
		       "This Nand flash need to enable 'randomizer' feature. "
		       "Please configure hardware randomizer PIN.");
	}
}

/*****************************************************************************/
static void hifmc100_set_oob_info(struct mtd_info *mtd,
				struct nand_config_info *info)
{
	int buffer_len;
	long long align_mask;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	/* oobsize_real for ecc0 read and write */
	oobsize_real = mtd->oobsize;

	if (info->ecctype != NAND_ECC_0BIT)
		mtd->oobsize = info->oobsize;
	mtd->oobavail = HIFMC100_NAND_OOBSIZE_FOR_YAFFS;

	host->oobsize = mtd->oobsize;

	if (mtd->writesize > NAND_MAX_PAGESIZE
	    || mtd->oobsize > NAND_MAX_OOBSIZE) {
		db_bug(ERSTR_DRIVER
		       "Driver does not support this Nand Flash. Please " \
		       "increase NAND_MAX_PAGESIZE and NAND_MAX_OOBSIZE.\n");
		return;
	}

	buffer_len = host->pagesize + host->oobsize;

	host->buforg = kmalloc(buffer_len + FMC_DMA_ALIGN, GFP_KERNEL);
	if (!host->buforg) {
		db_bug(ERSTR_DRIVER "Error: Can't malloc memory for hifmc100 driver.\n");
		return;
	}

	/* DMA need 32 bytes alignment */
	align_mask = FMC_DMA_ALIGN - 1;
	host->dma_buffer = ((long)(host->buforg + align_mask)) & ~align_mask;
	host->buffer = (char *)host->dma_buffer;
	memset(host->buffer, 0xff, buffer_len);
	host->dma_oob = host->dma_buffer + host->pagesize;

	chip->ecc.layout = info->layout;

	host->bbm = (unsigned char *)(host->buffer + host->pagesize
				      + HIFMC100_BAD_BLOCK_POS);

	/* EB bits locate in the bottom two of CTRL(30) */
	host->epm = (unsigned short *)(host->buffer + host->pagesize
				+ chip->ecc.layout->oobfree[0].offset + EB_NORMAL);

#ifndef CONFIG_SUPPORT_YAFFS
	if (best->ecctype == NAND_ECC_16BIT) {
		if (host->pagesize == _2K)
			/* EB bits locate in the bottom two of CTRL(4) */
			host->epm = (u_short *)(host->buffer + host->pagesize
			 + chip->ecc.layout->oobfree[0].offset + EB_2K_16_BIT);
		else if (host->pagesize == _4K)
			/* EB bit locate in the bottom two of CTRL(14) */
			host->epm = (u_short *)(host->buffer + host->pagesize
			 + chip->ecc.layout->oobfree[0].offset + EB_4K_16_BIT);
	}
#endif
}

/*****************************************************************************/
static int hifmc100_set_config_info(struct mtd_info *mtd)
{
	struct nand_config_info *type_info = NULL;
	struct nand_config_info *config = hifmc100_nand_hw_auto_config_table;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	fmc_pr(BT_DBG, "\t*-Start config Block Page OOB and Ecc\n");

	type_info = hifmc100_get_config_type_info(config, mtd);
	if (!type_info)
		db_bug(ERSTR_DRIVER " the pagesize(%d) and oobsize(%d).\n",
		       mtd->writesize, mtd->oobsize);

	fmc_pr(BT_DBG, "\t|-PageSize %s EccType %s OobSize %d\n",
	       nand_page_name(type_info->pagetype),
	       nand_ecc_name(type_info->ecctype), type_info->oobsize);

	/* Set the page_size, ecc_type, block_size of FMC_CFG[0x0] register */
	hifmc100_set_fmc_cfg_reg(host, type_info);

	hifmc100_set_oob_info(mtd, type_info);

	if (mtd->writesize != host->pagesize) {
		unsigned int shift = 0;
		unsigned int writesize = mtd->writesize;

		while (writesize > host->pagesize) {
			writesize >>= 1;
			shift++;
		}
		chip->chipsize = chip->chipsize >> shift;
		mtd->erasesize = mtd->erasesize >> shift;
		mtd->writesize = host->pagesize;
		printf("Nand divide into 1/%d\n", (1 << shift));
	}

	return 0;
}
/******************************************************************************/
static void hifmc100_cmdfunc(struct mtd_info *mtd, unsigned int command,
				int column, int page_addr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct hifmc_host *host = chip->priv;

	host->cmd_op.cmd = command & 0xff;

	switch (command) {
	case NAND_CMD_READOOB:
		host->offset = 0; /* same command as read */
	case NAND_CMD_READ0:
		host->cmd_op.l_cmd = command & 0xff;
		/* get addr low 16 bits */
		host->addr_value[0] = page_addr << 16;
		/* get addr hight 16 bits */
		host->addr_value[1] = page_addr >> 16;
		host->send_cmd_readstart(host);
		break;

	case NAND_CMD_ERASE1:
		host->cmd_op.l_cmd = command & 0xff;
		host->addr_cycle = 3; /* block addr have 3*8 bits */
		host->addr_value[0] = page_addr;
		host->send_cmd_erase(host);
		break;

	case NAND_CMD_READSTART:
	case NAND_CMD_ERASE2:
		break;

	case NAND_CMD_SEQIN:
		host->addr_value[0] = page_addr << 16; /* get addr low 16 bits */
		host->addr_value[1] = page_addr >> 16; /* get addr hight 16 bits */
		break;

	case NAND_CMD_PAGEPROG:
		host->offset = 0;
		host->send_cmd_pageprog(host);
		break;

	case NAND_CMD_STATUS:
		host->send_cmd_status(host);
		host->enable_ecc_randomizer(host, ENABLE, ENABLE);
		break;

	case NAND_CMD_READID:
		host->offset = 0;
		host->cmd_op.l_cmd = command & 0xff;
		memset((u_char *)(chip->IO_ADDR_R), 0, MAX_NAND_ID_LEN);
		host->cmd_op.data_no = MAX_NAND_ID_LEN;
		host->send_cmd_readid(host);
		host->enable_ecc_randomizer(host, ENABLE, ENABLE);
		break;

	case NAND_CMD_RESET:
		host->cmd_op.l_cmd = command & 0xff;
		host->send_cmd_reset(host);
		chip->dev_ready(mtd);
		break;

	default:
#ifdef CONFIG_HIFMC_DEBUG
		printf("%s not support command 0x%08x:\n", mtd->name, command);
#endif
		break;
	}
}
/*****************************************************************************/
static void hifmc100_chip_init(struct nand_chip *chip)
{
	memset((char *)chip->IO_ADDR_R, 0xff, NAND_BUFFER_LEN);

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
static void hifmc100_host_hook(struct hifmc_host *host)
{
	unsigned int reg;

	host->addr_cycle = 0;
	host->addr_value[0] = 0;
	host->addr_value[1] = 0;
	host->cache_addr_value[0] = ~0;
	host->cache_addr_value[1] = ~0;
	host->flags |= NAND_HW_AUTO;

	host->send_cmd_pageprog = hifmc100_send_cmd_write;
	host->send_cmd_status = hifmc100_send_cmd_status;
	host->send_cmd_readstart = hifmc100_send_cmd_read;
	host->send_cmd_erase = hifmc100_send_cmd_erase;
	host->send_cmd_readid = hifmc100_send_cmd_readid;
	host->send_cmd_reset = hifmc100_send_cmd_reset;

	/*
	 * check if start from nand.
	 * This register REG_SYSSTAT is set in start.S
	 * When start in NAND (Auto), the ECC/PAGESIZE driver don't detect.
	 */
	host->flags |= NAND_HW_AUTO;
	reg = readl(SYS_CTRL_REG_BASE + REG_SYSSTAT);
	fmc_pr(BT_DBG, "\t |-Read SYSTEM STATUS CFG[%#x]%#x\n", REG_SYSSTAT,
	       reg);
	if (get_sys_boot_mode(reg) == BOOT_FROM_NAND) {
		host->flags |= NAND_CONFIG_DONE;
		fmc_pr(BT_DBG, "\t |-Auto config pagesize and ecctype\n");
	}

	host->enable_ecc_randomizer = hifmc100_ecc_randomizer;
}

/*****************************************************************************/
static int hifmc100_host_init(struct hifmc_host *host)
{
	unsigned int reg;
	unsigned int flash_type;

	fmc_pr(BT_DBG, "\t *-Start nand host init\n");

	host->regbase = (void __iomem *)CONFIG_HIFMC_REG_BASE;

	reg = hifmc_read(host, FMC_CFG);
	fmc_pr(BT_DBG, "\t |-Read FMC CFG[%#x]%#x\n", FMC_CFG, reg);
	flash_type = (reg & FLASH_SEL_MASK) >> FLASH_SEL_SHIFT;
	if (flash_type != FLASH_TYPE_NAND) {
		db_msg("Error: Flash type isn't Nand flash. reg[%#x]\n", reg);
		reg |= fmc_cfg_flash_sel(FLASH_TYPE_NAND);
		fmc_pr(BT_DBG, "\t |-Change flash type to Nand flash\n");
	}

	if ((reg & OP_MODE_MASK) == OP_MODE_BOOT) {
		reg |= fmc_cfg_op_mode(OP_MODE_NORMAL);
		fmc_pr(BT_DBG, "\t |-Controller enter normal mode\n");
	}
	hifmc_write(host, FMC_CFG, reg);
	fmc_pr(BT_DBG, "\t |-Set CFG[%#x]%#x\n", FMC_CFG, reg);

	host->nand_cfg = reg;
	host->nand_cfg_ecc0 = (reg & ~ECC_TYPE_MASK) | ECC_TYPE_0BIT;

	reg = hifmc_read(host, FMC_GLOBAL_CFG);
	fmc_pr(BT_DBG, "\t |-Read global CFG[%#x]%#x\n", FMC_GLOBAL_CFG, reg);
	if (reg & FMC_GLOBAL_CFG_RANDOMIZER_EN) {
		host->flags &= ~NAND_RANDOMIZER;
		fmc_pr(BT_DBG, "\t |-Default disable randomizer\n");
		reg &= ~FMC_GLOBAL_CFG_RANDOMIZER_EN;
		hifmc_write(host, FMC_GLOBAL_CFG, reg);
		fmc_pr(BT_DBG, "\t |-Set global CFG[%#x]%#x\n", FMC_GLOBAL_CFG,
		       reg);
	}

#ifdef CONFIG_NAND_EDO_MODE
	/* enable EDO node */
	reg = hifmc_read(host, FMC_GLOBAL_CFG);
	hifmc_write(host, FMC_GLOBAL_CFG, set_nand_edo_mode_en(reg));
#endif
	/* ecc0_flag for ecc0 read/write */
	ecc0_flag = 0;
	hifmc100_host_hook(host);

	fmc_pr(BT_DBG, "\t *-End nand host init\n");

	return 0;
}

/*****************************************************************************/
int board_nand_init(struct nand_chip *chip)
{
	struct hifmc_host *host = &fmc_host;

	/* boot flash type check */
	if (get_boot_media() != BOOT_MEDIA_NAND) {
		printf("Error: Boot flash type isn't Nand flash.\n");
		return -ENODEV;
	}

	/* spi nand is initialized */
	if (host->version == HIFMC_VER_100) {
		printf("Host was initialized.\n");
		return 0;
	}

	/* Hifmc ip version check */
	if (hifmc_ip_ver_check())
		db_bug("Error: hifmc IP version unknown!\n");

	/* hifmc host init */
	memset((char *)host, 0, sizeof(struct hifmc_host));
	if (hifmc100_host_init(host)) {
		db_msg("Error: Nand host init failed!\n");
		return -EFAULT;
	}
	host->version = readl(CONFIG_HIFMC_REG_BASE + FMC_VERSION);
	host->chip = chip;

	hifmc_write(host, FMC_PND_PWIDTH_CFG, pwidth_cfg_rw_hcnt(RW_H_WIDTH) |
			pwidth_cfg_r_lcnt(R_L_WIDTH) |
			pwidth_cfg_w_lcnt(W_L_WIDTH));

	/* enable system clock */
	hifmc100_nand_controller_enable(ENABLE);

	chip->priv = host;
	hifmc100_chip_init(chip);

	hifmc_spl_ids_register();
	nand_oob_resize = hifmc100_set_config_info;

	return 0;
}

/*****************m***********************************************************/
void *hifmc100_nand_get_host(void)
{
	return ((fmc_host.chip) ? (void *)&fmc_host : NULL);
}

/*****************************************************************************/
static int hifmc100_nand_get_ecctype(void)
{
	if (!fmc_host.chip) {
		printf("Nand flash uninitialized.\n");
		return -1;
	}

	return match_ecc_type_to_yaffs(fmc_host.ecctype);
}

/*****************************************************************************/
int nand_get_ecctype(void)
{
	return hifmc100_nand_get_ecctype();
}

/*****************************************************************************/
int hifmc100_nand_get_rr_param(char *param)
{
	int ret = 0;

	if ((fmc_host.read_retry->type == NAND_RR_HYNIX_BG_CDIE) ||
	    (fmc_host.read_retry->type == NAND_RR_HYNIX_CG_ADIE)) {
		ret = 64; /* len: 64 bytes */
		memcpy(param, fmc_host.rr_data, ret);
	}
	return ret;
}
