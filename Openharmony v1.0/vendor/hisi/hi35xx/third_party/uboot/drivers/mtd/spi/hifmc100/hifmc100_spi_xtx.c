/*
 * hifmc100_spi_xtx.c
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
#define XTX_READ_SR_H 	0x35
#define XTX_READ_SR_L   0x05

/****************************************************************************/
static void spi_xtx_set_op(struct hifmc_spi *spi)
{
	unsigned int regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	regval = fmc_cmd_cmd1(SPI_CMD_WRSR);
	hifmc_write(host, FMC_CMD, regval);
	fmc_pr(QE_DBG, "\t  Set CMD[%#x]%#x\n", FMC_CMD, regval);

	regval = op_cfg_fm_cs(spi->chipselect) | OP_CFG_OEN_EN;
	hifmc_write(host, FMC_OP_CFG, regval);
	fmc_pr(QE_DBG, "\t  Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, regval);

	regval = fmc_data_num_cnt(sizeof(unsigned short));
	hifmc_write(host, FMC_DATA_NUM, regval);
	fmc_pr(QE_DBG, "\t  Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, regval);

	regval = fmc_op_cmd1_en(ENABLE) | fmc_op_write_data_en(ENABLE) |
		 FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, regval);
	fmc_pr(QE_DBG, "\t  Set OP[%#x]%#x\n", FMC_OP, regval);

	fmc_cmd_wait_cpu_finish(host);
}
/****************************************************************************/
/*
   enable QE bit if QUAD read write is supported by xtx's flash
*/
static int spi_xtx_qe_enable(struct hifmc_spi *spi)
{
	unsigned char status_h;
	unsigned char status_l;
	unsigned char op;
	unsigned short reg;
	const char *str[] = {"Disable", "Enable"};
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	op = spi_is_quad(spi);

	fmc_pr(QE_DBG, "\t* Start SPI Nor xtx %s Quad.\n", str[op]);

	status_h = spi_general_get_flash_register(spi, XTX_READ_SR_H);

	fmc_pr(QE_DBG, "\t  Read Status Register-h[%#x]%#x\n", XTX_READ_SR_H,
	       status_h);
	if (op == spi_nor_get_qe_by_cr(status_h)) {
		fmc_pr(QE_DBG, "\t* Quad was %s status:%#x\n", str[op], status_h);
		goto QE_END;
	}

	spi->driver->write_enable(spi);
	status_l = spi_general_get_flash_register(spi, XTX_READ_SR_L);

	if (op)
		status_h |= SPI_NOR_CR_QE_MASK;
	else
		status_h &= ~SPI_NOR_CR_QE_MASK;
	/* Move left to 8 bit to assign a value to the upper bits */
	reg = ((unsigned short)status_h << 8) | status_l;
	writew(reg, host->iobase);
	fmc_pr(QE_DBG, "\t  Write IO[%p]%#x\n", host->iobase,
	       *(unsigned short *)host->iobase);

	spi_xtx_set_op(spi);

	/* wait the flash have switched quad mode success */
	spi->driver->wait_ready(spi);

	status_h = spi_general_get_flash_register(spi, XTX_READ_SR_H);
	fmc_pr(QE_DBG, "\t  Read Status Register-h[%#x]:%#x\n",
	       XTX_READ_SR_H, status_h);
	if (op == spi_nor_get_qe_by_cr(status_h)) {
		fmc_pr(QE_DBG, "\t  %s Quad success. status_h:%#x\n",
		       str[op], status_h);
	} else {
		db_msg("Error: %s Quad failed! reg:%#x\n", str[op],
		       status_h);
	}
QE_END:
	return status_h;
}
