/*
 * hifmc100_spi_w25q256fv.c
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
#define W25Q256FV_CR_4BYTE_MASK     0x1

#define WB_SPI_NOR_SR_ADS_MASK  1
#define wb_spi_nor_get_4byte_by_sr(sr)  ((sr) & WB_SPI_NOR_SR_ADS_MASK)

#define SPI_CMD_FIRST_RESET_4ADDR  0x66
#define SPI_CMD_SECOND_RESET_4ADDR 0x99

/****************************************************************************/
static void spi_w25q256fv_set_cmd(struct hifmc_spi *spi, u8 cmd)
{
	unsigned int regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	regval = fmc_cmd_cmd1(cmd);
	hifmc_write(host, FMC_CMD, regval);
	fmc_pr(AC_DBG, "\t  Set CMD[%#x]%#x\n", FMC_CMD, regval);

	regval = op_cfg_fm_cs(spi->chipselect) | OP_CFG_OEN_EN;
	hifmc_write(host, FMC_OP_CFG, regval);
	fmc_pr(AC_DBG, "\t  Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, regval);

	regval = fmc_op_cmd1_en(ENABLE) | FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, regval);
	fmc_pr(AC_DBG, "\t  Set OP[%#x]%#x\n", FMC_OP, regval);

	fmc_cmd_wait_cpu_finish(host);
}
/****************************************************************************/
static int spi_w25q256fv_entry_4addr(struct hifmc_spi *spi, int enable)
{
	unsigned char status;
	const char *str[] = {"Disable", "Enable"};

	fmc_pr(AC_DBG, "\t* Start W25Q256FV SPI Nor %s 4-byte mode.\n",
	       str[enable]);

	if (spi->addrcycle != SPI_NOR_4BYTE_ADDR_LEN) {
		fmc_pr(AC_DBG, "\t* W25Q(128/256)FV not support 4B mode.\n");
		return 0;
	}

	status = spi_general_get_flash_register(spi, SPI_CMD_RDSR3);
	fmc_pr(AC_DBG, "\t  Read Status Register-3[%#x]:%#x\n", SPI_CMD_RDSR3,
	       status);
	if (wb_spi_nor_get_4byte_by_sr(status) == enable) {
		fmc_pr(AC_DBG, "\t* 4-byte was %sd, reg:%#x\n", str[enable],
		       status);
		return 0;
	}

	if (enable) {
		spi_w25q256fv_set_cmd(spi, SPI_CMD_EN4B);

		spi->driver->wait_ready(spi);

		status = spi_general_get_flash_register(spi, SPI_CMD_RDSR3);
		fmc_pr(AC_DBG, "\t  Get Status Register 3[%#x]:%#x\n",
		       SPI_CMD_RDSR3, status);
		if (status & W25Q256FV_CR_4BYTE_MASK) {
			fmc_pr(AC_DBG, "\t  Enter 4-byte success, reg[%#x]\n",
			       status);
		} else {
			db_msg("Error: Enter 4-byte failed! [%#x]\n", status);
		}
	} else {
		/* reset cmd */
		spi_w25q256fv_set_cmd(spi, SPI_CMD_FIRST_RESET_4ADDR);

		spi_w25q256fv_set_cmd(spi, SPI_CMD_SECOND_RESET_4ADDR);

		fmc_pr(AC_DBG, "\tnow W25Q256FV start software reset\n");

		udelay(30); /* delay 30 us */
	}

	fmc_pr(AC_DBG, "\t* End W25Q256FV enter 4-byte mode.\n");

	return 0;
}

/****************************************************************************/
static void spi_w25q256fv_set_op(struct hifmc_spi *spi)
{
	unsigned int regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	regval = fmc_cmd_cmd1(SPI_CMD_WRSR2);
	hifmc_write(host, FMC_CMD, regval);
	fmc_pr(QE_DBG, "\t  Set CMD[%#x]%#x\n", FMC_CMD, regval);

	regval = op_cfg_fm_cs(spi->chipselect) | OP_CFG_OEN_EN;
	hifmc_write(host, FMC_OP_CFG, regval);
	fmc_pr(QE_DBG, "\t  Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, regval);

	regval = fmc_data_num_cnt(SPI_NOR_SR_LEN);
	hifmc_write(host, FMC_DATA_NUM, regval);
	fmc_pr(QE_DBG, "\t  Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, regval);

	regval = fmc_op_cmd1_en(ENABLE) |
		 fmc_op_write_data_en(ENABLE) |
		 FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, regval);
	fmc_pr(QE_DBG, "\t  Set OP[%#x]%#x\n", FMC_OP, regval);

	fmc_cmd_wait_cpu_finish(host);
}

/****************************************************************************/
/*
   enable QE bit if QUAD read write is supported by W25Q(128/256)FV
*/
static int spi_w25q256fv_qe_enable(struct hifmc_spi *spi)
{
	unsigned char status, op;
	const char *str[] = {"Disable", "Enable"};
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	op = spi_is_quad(spi);

	fmc_pr(QE_DBG, "\t* Start SPI Nor W25Q(128/256)FV %s Quad.\n", str[op]);

	status = spi_general_get_flash_register(spi, SPI_CMD_RDSR2);
	fmc_pr(QE_DBG, "\t  Read Status Register-2[%#x]%#x\n", SPI_CMD_RDSR2,
	       status);
	if (op == spi_nor_get_qe_by_cr(status)) {
		fmc_pr(QE_DBG, "\t* Quad was %s status:%#x\n", str[op], status);
		goto QE_END;
	}

	spi->driver->write_enable(spi);

	if (op)
		status |= SPI_NOR_CR_QE_MASK;
	else
		status &= ~SPI_NOR_CR_QE_MASK;

	writeb(status, host->iobase);
	fmc_pr(QE_DBG, "\t  Write IO[%p]%#x\n", host->iobase,
	       *(unsigned char *)host->iobase);

	/* There is new cmd for Write Status Register 2 by W25Q(128/256)FV */
	spi_w25q256fv_set_op(spi);

	/* wait the flash have switched quad mode success */
	spi->driver->wait_ready(spi);

	status = spi_general_get_flash_register(spi, SPI_CMD_RDSR2);
	fmc_pr(QE_DBG, "\t  Read Status Register-2[%#x]:%#x\n",
	       SPI_CMD_RDSR2, status);
	if (op == spi_nor_get_qe_by_cr(status)) {
		fmc_pr(QE_DBG, "\t  %s Quad success. status:%#x\n",
		       str[op], status);
	} else {
		db_msg("Error: %s Quad failed! reg:%#x\n", str[op],
		       status);
	}
QE_END:
	/* Enable the reset pin when working on dual mode for 8PIN */
	if (!op)
		spi_nor_reset_pin_enable(spi, ENABLE);

	fmc_pr(QE_DBG, "\t* End SPI Nor W25Q(128/256)FV %s Quad.\n", str[op]);

	return op;
}

