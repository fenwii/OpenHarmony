/*
 * hifmc100_spi_mx25l25635e.c
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
/* MXIC QE(bit) include in Status Register */
#define MX_SPI_NOR_SR_QE_SHIFT  6
#define MX_SPI_NOR_SR_QE_MASK   (1 << MX_SPI_NOR_SR_QE_SHIFT)
#define mx_spi_nor_get_qe_by_sr(sr) (((sr) & MX_SPI_NOR_SR_QE_MASK) \
							>> MX_SPI_NOR_SR_QE_SHIFT)

/*****************************************************************************/
/*
 * enable QE bit if 4X R/W is supported by MXIC "25L(256/257)35(E/F)" SPI
 */
#ifndef CONFIG_DTR_MODE_SUPPORT
static void clear_dtr_mode(struct hifmc_spi *spi, unsigned char status)
{
	unsigned int regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;
	unsigned char config;
	unsigned short reg;

	config = spi_general_get_flash_register(spi, SPI_CMD_RDCR_MX);

	regval = hifmc_read(host, FMC_GLOBAL_CFG);
	if ((regval >> DTR_MODE_REQUEST_SHIFT) & 0x1) {
		regval &= (~(1 << DTR_MODE_REQUEST_SHIFT));
		regval = hifmc_write(host, FMC_GLOBAL_CFG, regval);
	}

	if (config & CR_DUMMY_CYCLE) {
		config &= (~CR_DUMMY_CYCLE);
		reg = ((unsigned short)config << SPI_NOR_CR_SHIFT) | status;
		writew(reg, host->iobase);
		spi->driver->write_enable(spi);
		hifmc100_op_reg(spi, SPI_CMD_WRSR, sizeof(unsigned short), fmc_op_write_data_en(ENABLE));
	}
}
#endif
/*****************************************************************************/
static void spi_mx25l25635e_set_cmd(struct hifmc_spi *spi)
{
	unsigned int regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	regval = fmc_cmd_cmd1(SPI_CMD_WRSR);
	hifmc_write(host, FMC_CMD, regval);
	fmc_pr(QE_DBG, "\t||-Set CMD[%#x]%#x\n", FMC_CMD, regval);

	regval = op_cfg_fm_cs(spi->chipselect) | OP_CFG_OEN_EN;
	hifmc_write(host, FMC_OP_CFG, regval);
	fmc_pr(QE_DBG, "\t||-Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, regval);

	regval = fmc_data_num_cnt(SPI_NOR_SR_LEN);
	hifmc_write(host, FMC_DATA_NUM, regval);
	fmc_pr(QE_DBG, "\t||-Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, regval);

	regval = fmc_op_cmd1_en(ENABLE) | fmc_op_write_data_en(ENABLE) |
			FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, regval);
	fmc_pr(QE_DBG, "\t||-Set OP[%#x]%#x\n", FMC_OP, regval);

	fmc_cmd_wait_cpu_finish(host);
}

/*****************************************************************************/
static int spi_mx25l25635e_qe_enable(struct hifmc_spi *spi)
{
	unsigned char status;
	unsigned char op;
	const char *str[] = {"Disable", "Enable"};
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	op = spi_is_quad(spi);

	fmc_pr(QE_DBG, "\t|*-Start MXIC SPI Nor %s Quad.\n", str[op]);

	status = spi_general_get_flash_register(spi, SPI_CMD_RDSR);
	fmc_pr(QE_DBG, "\t||-Read Status Register[%#x]%#x\n", SPI_CMD_RDSR,
	       status);

#ifndef CONFIG_DTR_MODE_SUPPORT
	clear_dtr_mode(spi, status);
#endif

	if (mx_spi_nor_get_qe_by_sr(status) == op) {
		fmc_pr(QE_DBG, "\t|*-Quad was %sd, status:%#x\n", str[op],
		       status);
		return op;
	}

	spi->driver->write_enable(spi);

	if (op)
		status |= MX_SPI_NOR_SR_QE_MASK;
	else
		status &= ~MX_SPI_NOR_SR_QE_MASK;

	writeb(status, host->iobase);
	fmc_pr(QE_DBG, "\t||-Write IO[%p]%#x\n", host->iobase,
	       *(unsigned char *)host->iobase);

	spi_mx25l25635e_set_cmd(spi);

	spi->driver->wait_ready(spi);

	status = spi_general_get_flash_register(spi, SPI_CMD_RDSR);
	if (mx_spi_nor_get_qe_by_sr(status) == op)
		fmc_pr(QE_DBG, "\t||-%s Quad success, status:%#x.\n", str[op],
		       status);
	else
		db_msg("Error: %s Quad failed! reg: %#x\n", str[op], status);

	fmc_pr(QE_DBG, "\t|*-End MXIC SPI Nor %s Quad.\n", str[op]);

	return op;
}

#ifdef CONFIG_DTR_MODE_SUPPORT
/*****************************************************************************/
void spi_mxic_set_reg(struct hifmc_spi *spi)
{
	unsigned int regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	regval = fmc_cmd_cmd1(SPI_CMD_WRSR);
	hifmc_write(host, FMC_CMD, regval);
	fmc_pr(DTR_DB, " Set CMD[%#x]%#x\n", FMC_CMD, regval);

	regval = op_cfg_fm_cs(spi->chipselect) | OP_CFG_OEN_EN;
	hifmc_write(host, FMC_OP_CFG, regval);
	fmc_pr(DTR_DB, " Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, regval);

	regval = fmc_data_num_cnt(SPI_NOR_SR_LEN + SPI_NOR_CR_LEN);
	hifmc_write(host, FMC_DATA_NUM, regval);
	fmc_pr(DTR_DB, " Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, regval);

	regval = fmc_op_cmd1_en(ENABLE) 	|
		fmc_op_write_data_en(ENABLE) 	|
		FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, regval);
	fmc_pr(DTR_DB, " Set OP[%#x]%#x\n", FMC_OP, regval);
}
/*****************************************************************************/
int spi_mxic_output_driver_strength_set(struct hifmc_spi *spi, int dtr_en)
{
	unsigned char status;
	unsigned char config;
	unsigned short reg;
	unsigned short val = 0;
	unsigned int ix;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	/************************************************************************/
	/* DC[1:0]  |  Numbers of Dummy clock cycles|  Quad IO DTR Read     */
	/*   00(default)|       6       |   54      */
	/*   01     |       6       |   54      */
	/*   10     |       8       |   70/80R      */
	/*   11     |       10      |   84/100R     */
	/************************************************************************/
	unsigned int str_dummy[] = {
		DTR_DUMMY_CYCLES_6,      dtr_rdcr_dc_mask(0),
		DTR_DUMMY_CYCLES_6,      dtr_rdcr_dc_mask(1),
		DTR_DUMMY_CYCLES_8,      dtr_rdcr_dc_mask(2),
		DTR_DUMMY_CYCLES_10,     dtr_rdcr_dc_mask(3),
		0,      0,
	};

	/* get the RDCR and RDSR */
	spi->driver->wait_ready(spi);

	/* setting the DC value to match high system clock */
	config = spi_general_get_flash_register(spi, SPI_CMD_RDCR_MX);
	fmc_pr(DTR_DB, "Get Config Register[%#x]\n", config);

	/* check the QE value */
	status = spi_general_get_flash_register(spi, SPI_CMD_RDSR);
	fmc_pr(DTR_DB, "Get Status Register[%#x]\n", status);

	reg = ((unsigned short)config << SPI_NOR_CR_SHIFT) | status;

	if (dtr_en == ENABLE) {
		/* setting DC value */
		fmc_pr(DTR_DB, "Get the dummy value[%#x]\n", spi->read->dummy);
		/* Only the element with an even number of arrays is required, so increase is 2 */
		for (ix = 0; str_dummy[ix]; ix += _2B) {
			if (spi->read->dummy < str_dummy[ix])
				break;
			val = (unsigned short)str_dummy[ix + 1];
		}
	} else {
		val = dtr_rdcr_dc_mask(0);
	}

	reg = dtr_rdcr_dc_bit_clr(reg) | (val << DTR_RDSR_DC_SHIFT);

	spi->driver->write_enable(spi);
	writew(reg, host->iobase);
	fmc_pr(DTR_DB, "Write IO[%p]%#x\n", host->iobase,
	       *(unsigned short *)host->iobase);
	spi_mxic_set_reg(spi);
	fmc_cmd_wait_cpu_finish(host);

	config = spi_general_get_flash_register(spi, SPI_CMD_RDCR_MX);
	if ((config >> DTR_RDCR_DC_SHIFT) != (unsigned char)val) {
		printf("* Set DC dummy fail.\n");
		return -1;
	}
	return 0;
}

unsigned int spi_mxic_check_spi_dtr_support(struct hifmc_spi *spi)
{
	unsigned int regval;
	unsigned int rd_sfdp_dummy = 1;
	unsigned int sfdp_addrcycle = 3;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	/* get the RDCR and RDSR */
	spi->driver->wait_ready(spi);

	/* Read the Serial Flash Discoverable Parameter (SFDP) */
	hifmc_write(host, FMC_CMD, SPI_CMD_RD_SFDP);
	fmc_pr(DTR_DB, "\t   Set CMD[%#x]%#x\n", FMC_CMD, SPI_CMD_RD_SFDP);

	regval = op_cfg_fm_cs(spi->chipselect) 		|
			OP_CFG_OEN_EN 			|
			op_cfg_addr_num(sfdp_addrcycle) |
			op_cfg_dummy_num(rd_sfdp_dummy);
	hifmc_write(host, FMC_OP_CFG, regval);
	fmc_pr(DTR_DB, "\t\t   Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, regval);

	regval = fmc_data_num_cnt(SFDP_BUF_LEN);
	hifmc_write(host, FMC_DATA_NUM, regval);
	fmc_pr(DTR_DB, "\t   Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, regval);

	regval = fmc_op_dummy_en(ENABLE) 		|
			fmc_op_cmd1_en(ENABLE) 		|
			fmc_op_addr_en(ENABLE) 		|
			fmc_op_read_data_en(ENABLE) 	|
			FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, regval);
	fmc_pr(DTR_DB, "\t   Set OP[%#x]%#x\n", FMC_OP, regval);

	fmc_cmd_wait_cpu_finish(host);

	regval = readb((char *)host->iobase + SFDP_DTR_BYTE_SHIFT);
	fmc_pr(DTR_DB, "\t the dtr_mode_support is: %#x\n", regval);

	/* get the DTR mode support bit */
	spi->dtr_mode_support = (regval >> SFDP_DTR_BIT_SHIFT)
				& SFDP_DTR_BIT_MASK;

	return spi->dtr_mode_support;
}
#endif /* CONFIG_DTR_MODE_SUPPORT */
