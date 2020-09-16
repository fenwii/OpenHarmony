/*
 * hifmc100_spi_gd25qxxx.c
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
#define GD_SPI_CMD_RDSR1        0x35    /* Read Status Register-1 */

/*****************************************************************************/
/*
 * enable QE bit if QUAD read write is supported by GD "25qxxx" SPI
 */
static void set_cmd(struct hifmc_spi *spi, u8 cmd, u8 len)
{
	struct hifmc_host *host = (struct hifmc_host *)spi->host;
	unsigned int regval;

	regval = fmc_cmd_cmd1(cmd);
	hifmc_write(host, FMC_CMD, regval);
	fmc_pr(QE_DBG, "\t|-Set CMD[%#x]%#x\n", FMC_CMD, regval);

	regval = op_cfg_fm_cs(spi->chipselect) | OP_CFG_OEN_EN;
	hifmc_write(host, FMC_OP_CFG, regval);
	fmc_pr(QE_DBG, "\t|-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, regval);

	regval = fmc_data_num_cnt(len);
	hifmc_write(host, FMC_DATA_NUM, regval);
	fmc_pr(QE_DBG, "\t|-Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, regval);

	regval = fmc_op_cmd1_en(ENABLE) |
		 fmc_op_write_data_en(ENABLE) |
		 FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, regval);
	fmc_pr(QE_DBG, "\t|-Set OP[%#x]%#x\n", FMC_OP, regval);

	fmc_cmd_wait_cpu_finish(host);

	spi->driver->wait_ready(spi);
}

static int gd_16pin_qe_enable(struct hifmc_spi *spi, int op)
{
	struct hifmc_host *host = (struct hifmc_host *)spi->host;
	unsigned char config;
	unsigned char status;
	const char *str[] = {"Disable", "Enable"};

	config = spi_general_get_flash_register(spi, GD_SPI_CMD_RDSR1);
	fmc_pr(QE_DBG, "\t|-Read GD SR-1[%#x], val: %#x\n", GD_SPI_CMD_RDSR1,
	       config);
	if (op && (op == spi_nor_get_qe_by_cr(config))) {
		fmc_pr(QE_DBG, "\t* Quad was %sd, status:%#x\n", str[op],
		       config);
		return op;
	}

	/* First, we enable/disable QE for 16Pin GD flash, use WRSR[01h] cmd */
	fmc_pr(QE_DBG, "\t|-First, 16Pin GD flash %s Quad.\n", str[op]);

	status = spi_general_get_flash_register(spi, SPI_CMD_RDSR);
	fmc_pr(QE_DBG, "\t|-Read Status Register[%#x]%#x\n", SPI_CMD_RDSR,
	       status);

	spi->driver->write_enable(spi);

	if (op)
		config |= SPI_NOR_CR_QE_MASK;
	else
		config &= ~SPI_NOR_CR_QE_MASK;
	writeb(status, host->iobase);
	writeb(config, host->iobase + SPI_NOR_SR_LEN);
	fmc_pr(QE_DBG, "\t|-Write IO[%p]%#x\n", host->iobase,
	       *(unsigned short *)host->iobase);

	set_cmd(spi, SPI_CMD_WRSR, SPI_NOR_SR_LEN + SPI_NOR_CR_LEN);

	config = spi_general_get_flash_register(spi, GD_SPI_CMD_RDSR1);
	fmc_pr(QE_DBG, "\t|-Read GD SR-1[%#x], val: %#x\n", GD_SPI_CMD_RDSR1,
	       config);
	if (op == spi_nor_get_qe_by_cr(config)) {
		fmc_pr(QE_DBG, "\t|-16P %s Quad success reg: %#x\n", str[op],
		       config);
		return op;
	} else {
		fmc_pr(QE_DBG, "\t|-16P %s Quad failed, reg: %#x\n", str[op],
		       config);
	}

	return 0;
}

static void gd_8pin_qe_enable(struct hifmc_spi *spi, int op)
{
	unsigned char config;
	unsigned char status;
	const char *str[] = {"Disable", "Enable"};
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	fmc_pr(QE_DBG, "\t|-Second, 8Pin GD flash %s Quad.\n", str[op]);

	status = spi_general_get_flash_register(spi, SPI_CMD_RDSR);
	fmc_pr(QE_DBG, "\t|-Read Status Register[%#x]:%#x\n", SPI_CMD_RDSR,
	       status);
	if (!(status & STATUS_WEL_MASK))
		spi->driver->write_enable(spi);

	config = spi_general_get_flash_register(spi, SPI_CMD_RDSR2);
	fmc_pr(QE_DBG, "\t|-Read SR-2[%#x], val: %#x\n", SPI_CMD_RDSR2,
	       config);

	if (op && (op == spi_nor_get_qe_by_cr(config))) {
		fmc_pr(QE_DBG, "\t* Quad was %sd, status:%#x\n", str[op],
		       config);
		return;
	}

	if (op)
		config |= SPI_NOR_CR_QE_MASK;
	else
		config &= ~SPI_NOR_CR_QE_MASK;

	writeb(config, host->iobase);
	fmc_pr(QE_DBG, "\t|-Write IO[%p]%#x\n", host->iobase,
	       *(unsigned char *)host->iobase);

	set_cmd(spi, SPI_CMD_WRSR2, SPI_NOR_CR_LEN);

	config = spi_general_get_flash_register(spi, SPI_CMD_RDSR2);
	fmc_pr(QE_DBG, "\t|-Read GD SR-2[%#x], val: %#x\n", SPI_CMD_RDSR2,
	       config);
	if (op == spi_nor_get_qe_by_cr(config))
		fmc_pr(QE_DBG, "\t|-8P %s Quad success, reg: %#x.\n", str[op],
		       config);
	else
		db_msg("Error: %s Quad failed, reg: %#x\n", str[op], config);

	return;
}

static int spi_gd25qxxx_qe_enable(struct hifmc_spi *spi)
{
	unsigned char op;
	const char *str[] = {"Disable", "Enable"};

	op = spi_is_quad(spi);

	fmc_pr(QE_DBG, "\t*-Start GD SPI nor %s Quad.\n", str[op]);

	/* First, we enable/disable QE for 16Pin GD flash, use WRSR[01h] cmd */
	if (gd_16pin_qe_enable(spi, op))
		goto QE_END;

	/* Second, we enable/disable QE for 8Pin GD flash, use WRSR2[31h] cmd */
	gd_8pin_qe_enable(spi, op);

QE_END:
	/* Enable the reset pin when working on dual mode for 8PIN */
	if (!op)
		spi_nor_reset_pin_enable(spi, ENABLE);

	fmc_pr(QE_DBG, "\t*-End GD SPI nor %s Quad end.\n", str[op]);
	return op;
}

