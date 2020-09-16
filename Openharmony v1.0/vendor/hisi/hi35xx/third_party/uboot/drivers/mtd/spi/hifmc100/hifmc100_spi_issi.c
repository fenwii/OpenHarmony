/*
 * hifmc100_spi_issi.c
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

#define SPI_NOR_ISSI_QE_SHIFT      6
#define SPI_NOR_ISSI_SRWD_MASK      (1 << 7)
#define SPI_NOR_ISSI_QE_MASK        (1 << SPI_NOR_ISSI_QE_SHIFT)
#define spi_nor_issi_get_qe(sr)        (((sr) & SPI_NOR_ISSI_QE_MASK) \
						>> SPI_NOR_ISSI_QE_SHIFT)

static void spi_issi_set_cmd(struct hifmc_spi *spi)
{
	unsigned int reg;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	reg = fmc_cmd_cmd1(SPI_CMD_WRSR);
	hifmc_write(host, FMC_CMD, reg);
	fmc_pr(QE_DBG, "\t|-Set CMD[%#x]%#x\n", FMC_CMD, reg);

	reg = op_cfg_fm_cs(spi->chipselect) | OP_CFG_OEN_EN;
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(QE_DBG, "\t|-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	reg = fmc_data_num_cnt(SPI_NOR_SR_LEN);
	hifmc_write(host, FMC_DATA_NUM, reg);
	fmc_pr(QE_DBG, "\t|-Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, reg);

	reg = fmc_op_cmd1_en(ENABLE) |
		fmc_op_write_data_en(ENABLE) |
		FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, reg);
	fmc_pr(QE_DBG, "\t|-Set OP[%#x]%#x\n", FMC_OP, reg);

	fmc_cmd_wait_cpu_finish(host);
}

static int spi_issi_qe_enable(struct hifmc_spi *spi)
{
	unsigned char config;
	unsigned char op;

	const char *str[] = {"Disable", "Enable"};
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	op = spi_is_quad(spi);

	fmc_pr(QE_DBG, "\t*-Start SPI Nor %s Quad.\n", str[op]);

	config = spi_general_get_flash_register(spi, SPI_CMD_RDSR);
	fmc_pr(QE_DBG, "\t|-Read Config Register[%#x]%#x\n", SPI_CMD_RDSR,
	       config);
	if (op == spi_nor_issi_get_qe(config)) {
		fmc_pr(QE_DBG, "\t* Quad was %sd, config:%#x\n", str[op],
		       config);
		return op;
	}

	spi->driver->write_enable(spi);

	config = spi_general_get_flash_register(spi, SPI_CMD_RDSR);
	config &= ~SPI_NOR_ISSI_SRWD_MASK;

	if (op)
		config |= SPI_NOR_ISSI_QE_MASK;
	else
		config &= ~SPI_NOR_ISSI_QE_MASK;
	writeb(config, host->iobase);
	fmc_pr(QE_DBG, "\t|-Write IO[%p]%#x\n", host->iobase,
	       *(unsigned short *)host->iobase);

	spi_issi_set_cmd(spi);

	spi->driver->wait_ready(spi);

	config = spi_general_get_flash_register(spi, SPI_CMD_RDSR);
	if (op == spi_nor_issi_get_qe(config)) {
		fmc_pr(QE_DBG, "\t|-%s Quad success, config: %#x\n", str[op],
		       config);
	} else {
		db_msg("Error: %s Quad failed! reg: %#x\n", str[op], config);
	}

	fmc_pr(QE_DBG, "\t* End SPI Nor %s Quad.\n", str[op]);

	return op;
}

