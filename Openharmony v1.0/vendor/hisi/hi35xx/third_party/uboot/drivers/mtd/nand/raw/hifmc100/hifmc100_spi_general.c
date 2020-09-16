/*
 * hifmc100_spi_general.c
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

/*
 * Send set/get features command to SPI Nand flash
 */
/*****************************************************************************/
void spi_nand_set_cmd(struct hifmc_host *host, u_char op, u_char addr,
				u_char val)
{
	unsigned int reg;

	reg = fmc_cmd_cmd1(op ? SPI_CMD_SET_FEATURE : SPI_CMD_GET_FEATURES);
	hifmc_write(host, FMC_CMD, reg);
	fmc_pr(FT_DBG, "\t||||-Set CMD[%#x]%#x\n", FMC_CMD, reg);

	hifmc_write(host, FMC_ADDRL, addr);
	fmc_pr(FT_DBG, "\t||||-Set ADDRL[%#x]%#x\n", FMC_ADDRL, addr);

	reg = op_cfg_fm_cs(host->cmd_op.cs) | OP_CFG_OEN_EN |
		op_cfg_addr_num(FEATURES_OP_ADDR_NUM);
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(FT_DBG, "\t||||-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	reg = fmc_data_num_cnt(FEATURES_DATA_LEN);
	hifmc_write(host, FMC_DATA_NUM, reg);
	fmc_pr(FT_DBG, "\t||||-Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, reg);

	reg = fmc_op_cmd1_en(ENABLE) | fmc_op_addr_en(ENABLE) |
		FMC_OP_REG_OP_START;

	if (op == SET_OP) {
		reg |= fmc_op_write_data_en(ENABLE);
		writeb(val, host->iobase);
		fmc_pr(FT_DBG, "\t||||-Write IO[%p]%#x\n", host->iobase,
		       *(u_char *)host->iobase);
	} else {
		reg |= fmc_op_read_data_en(ENABLE);
	}

	hifmc_write(host, FMC_OP, reg);
	fmc_pr(FT_DBG, "\t||||-Set OP[%#x]%#x\n", FMC_OP, reg);

	fmc_cmd_wait_cpu_finish(host);
}
/*****************************************************************************/
unsigned char spi_nand_feature_op(struct hifmc_spi *spi, unsigned char op,
					unsigned char addr, unsigned char val)
{
	unsigned int reg = 0;
	const char *str[] = {"Get", "Set"};
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	if ((op == GET_OP) && (addr == STATUS_ADDR)) {
		fmc_pr(SR_DBG, "\n\t\t|*-Start Get Status\n");

		reg = op_cfg_fm_cs(host->cmd_op.cs) | OP_CFG_OEN_EN;
		hifmc_write(host, FMC_OP_CFG, reg);
		fmc_pr(SR_DBG, "\t\t||-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

		reg = fmc_op_read_status_en(ENABLE) | FMC_OP_REG_OP_START;
		hifmc_write(host, FMC_OP, reg);
		fmc_pr(SR_DBG, "\t\t||-Set OP[%#x]%#x\n", FMC_OP, reg);

		fmc_cmd_wait_cpu_finish(host);

		val = hifmc_read(host, FMC_STATUS);
		fmc_pr(SR_DBG, "\t\t|*-End Get Status, result: %#x\n", val);

		return val;
	}

	fmc_pr(FT_DBG, "\t|||*-Start %s feature, addr[%#x]\n", str[op], addr);

	hifmc100_ecc0_switch(host, ENABLE);

	spi_nand_set_cmd(host, op, addr, val);

	if (op == GET_OP) {
		val = readb(host->iobase);
		fmc_pr(FT_DBG, "\t||||-Read IO[%p]%#x\n", host->iobase,
		       *(u_char *)host->iobase);
	}

	hifmc100_ecc0_switch(host, DISABLE);

	fmc_pr(FT_DBG, "\t|||*-End %s Feature[%#x]:%#x\n", str[op], addr, val);

	return val;
}

/*****************************************************************************/
/*
 * Read status[C0H]:[0]bit OIP, judge whether the device is busy or not
 */
static int spi_general_wait_ready(struct hifmc_spi *spi)
{
	unsigned char status;
	/* just get a big number, so move left 12 bits */
	unsigned int deadline = 1 << 12;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	do {
		status = spi_nand_feature_op(spi, GET_OP, STATUS_ADDR, 0);
		if (!(status & STATUS_OIP_MASK)) {
			if ((host->cmd_op.l_cmd == NAND_CMD_ERASE2) &&
				(status & STATUS_E_FAIL_MASK)) {
				return status;
			}
			if ((host->cmd_op.l_cmd == NAND_CMD_PAGEPROG) &&
				(status & STATUS_P_FAIL_MASK)) {
				return status;
			}
			return 0;
		}

		udelay(1); /* delay 1 us */
	} while (deadline--);

	db_msg("Error: SPI Nand wait ready timeout, status: %#x\n", status);

	return 1;
}

/*****************************************************************************/
/*
 * Send write enable cmd to SPI Nand, status[C0H]:[2]bit WEL must be set 1
 */
static int spi_general_write_enable(struct hifmc_spi *spi)
{
	unsigned int reg;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	if (WE_DBG)
		printf("\n");
	fmc_pr(WE_DBG, "\t|*-Start Write Enable\n");

	reg = spi_nand_feature_op(spi, GET_OP, STATUS_ADDR, 0);
	if (reg & STATUS_WEL_MASK) {
		fmc_pr(WE_DBG, "\t||-Write Enable was opened! reg: %#x\n",
		       reg);
		return 0;
	}

	reg = hifmc_read(host, FMC_GLOBAL_CFG);
	fmc_pr(WE_DBG, "\t||-Get GLOBAL_CFG[%#x]%#x\n", FMC_GLOBAL_CFG, reg);
	if (reg & FMC_GLOBAL_CFG_WP_ENABLE) {
		reg &= ~FMC_GLOBAL_CFG_WP_ENABLE;
		hifmc_write(host, FMC_GLOBAL_CFG, reg);
		fmc_pr(WE_DBG, "\t||-Set GLOBAL_CFG[%#x]%#x\n",
		       FMC_GLOBAL_CFG, reg);
	}

	reg = fmc_cmd_cmd1(SPI_CMD_WREN);
	hifmc_write(host, FMC_CMD, reg);
	fmc_pr(WE_DBG, "\t||-Set CMD[%#x]%#x\n", FMC_CMD, reg);

	reg = op_cfg_fm_cs(host->cmd_op.cs) | OP_CFG_OEN_EN;
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(WE_DBG, "\t||-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	reg = fmc_op_cmd1_en(ENABLE) | FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, reg);
	fmc_pr(WE_DBG, "\t||-Set OP[%#x]%#x\n", FMC_OP, reg);

	fmc_cmd_wait_cpu_finish(host);

#if WE_DBG
	spi->driver->wait_ready(spi);

	reg = spi_nand_feature_op(spi, GET_OP, STATUS_ADDR, 0);
	if (reg & STATUS_WEL_MASK) {
		fmc_pr(WE_DBG, "\t||-Write Enable success. reg: %#x\n", reg);
	} else {
		db_msg("Error: Write Enable failed! reg: %#x\n", reg);
		return reg;
	}
#endif

	fmc_pr(WE_DBG, "\t|*-End Write Enable\n");
	return 0;
}

/*****************************************************************************/
/*
 * judge whether SPI Nand support QUAD read/write or not
 */
static int spi_is_quad(struct hifmc_spi *spi)
{
	const char *if_str[] = {"STD", "DUAL", "DIO", "QUAD", "QIO"};

	fmc_pr(QE_DBG, "\t\t|||*-SPI read iftype: %s write iftype: %s\n",
			if_str[spi->read->iftype], if_str[spi->write->iftype]);

	if ((spi->read->iftype == IF_TYPE_QUAD) 		||
			(spi->read->iftype == IF_TYPE_QIO) 	||
			(spi->write->iftype == IF_TYPE_QUAD) 	||
			(spi->write->iftype == IF_TYPE_QIO))
		return 1;

	return 0;
}

/*****************************************************************************/
/*
 * Send set features cmd to SPI Nand, feature[B0H]:[0]bit QE would be set
 */
static int spi_general_qe_enable(struct hifmc_spi *spi)
{
	unsigned int reg;
	unsigned int op;

	const char *str[] = {"Disable", "Enable"};

	fmc_pr(QE_DBG, "\t||*-Start SPI Nand flash QE\n");

	op = spi_is_quad(spi);

	fmc_pr(QE_DBG, "\t|||*-End Quad check, SPI Nand %s Quad.\n", str[op]);

	reg = spi_nand_feature_op(spi, GET_OP, FEATURE_ADDR, 0);
	fmc_pr(QE_DBG, "\t|||-Get [%#x]feature: %#x\n", FEATURE_ADDR, reg);
	if ((reg & FEATURE_QE_ENABLE) == op) {
		fmc_pr(QE_DBG, "\t||*-SPI Nand quad was %sd!\n", str[op]);
		return op;
	}

	if (op == ENABLE)
		reg |= FEATURE_QE_ENABLE;
	else
		reg &= ~FEATURE_QE_ENABLE;

	spi_nand_feature_op(spi, SET_OP, FEATURE_ADDR, reg);
	fmc_pr(QE_DBG, "\t|||-SPI Nand %s Quad\n", str[op]);

	spi->driver->wait_ready(spi);

	reg = spi_nand_feature_op(spi, GET_OP, FEATURE_ADDR, 0);
	if ((reg & FEATURE_QE_ENABLE) == op)
		fmc_pr(QE_DBG, "\t|||-SPI Nand %s Quad succeed!\n", str[op]);
	else
		db_msg("Error: %s Quad failed! reg: %#x\n", str[op], reg);

	fmc_pr(QE_DBG, "\t||*-End SPI Nand %s Quad.\n", str[op]);

	return op;
}

/****************************************************************************/
/* some spi nand flash don't QUAD enable */
static int spi_do_not_qe_enable(struct hifmc_spi *spi)
{
	return 0;
}