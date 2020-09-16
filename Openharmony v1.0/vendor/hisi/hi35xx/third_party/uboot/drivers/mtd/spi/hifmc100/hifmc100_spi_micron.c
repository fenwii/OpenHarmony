/*
 * hifmc100_spi_micron.c
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
#define SPI_CMD_FIRST_RESET_4ADDR  0x66
#define SPI_CMD_SECOND_RESET_4ADDR 0x99

#define SPI_CMD_FLAG_SR_MICRON  0x70  /* READ FLAG STATUS REGISTER */
#define SPI_CMD_RD_RDCR_MICRON  0xB5  /* READ NONVOLATILE CONFIGURATION
                                         REGISTER */
#define SPI_CMD_WR_RDCR_MICRON  0xB1 /* WRITE NONVOLATILE CONFIGURATION
                                         REGISTER */
#define SPI_NOR_ADS_MASK    0x1
#define spi_nor_get_4byte_by_flag_sr(sr)     ((sr) & SPI_NOR_ADS_MASK)

#define spi_nor_ads_set_4byte(cr)        ((cr) & (~SPI_NOR_ADS_MASK))
#define spi_nor_ads_get_4byte(cr)        ((cr) & SPI_NOR_ADS_MASK)
/****************************************************************************/
static int spi_micron_entry_4addr(struct hifmc_spi *spi, int enable)
{
	unsigned char status;
	unsigned int reg;
	const char *str[] = {"Disable", "Enable"};
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	fmc_pr(AC_DBG, "\t* Start SPI Nor %s 4-byte mode.\n",
	       str[enable]);

	if (spi->addrcycle != SPI_NOR_4BYTE_ADDR_LEN) {
		fmc_pr(AC_DBG, "\t* Not support 4B mode.\n");
		return 0;
	}

	status = spi_general_get_flash_register(spi, SPI_CMD_FLAG_SR_MICRON);
	fmc_pr(AC_DBG, "\t Read flag status register[%#x]:%#x\n",
	       SPI_CMD_FLAG_SR_MICRON, status);
	if (spi_nor_get_4byte_by_flag_sr(status) == enable) {
		fmc_pr(AC_DBG, "\t* 4-byte was %sd, reg:%#x\n", str[enable],
		       status);
		return 0;
	}

	spi->driver->write_enable(spi);

	if (enable)
		reg = SPI_CMD_EN4B;
	else
		reg = SPI_CMD_EX4B;
	hifmc_write(host, FMC_CMD, fmc_cmd_cmd1(reg));
	fmc_pr(AC_DBG, "\t  Set CMD[%#x]%#x\n", FMC_CMD, reg);

	reg = op_cfg_fm_cs(spi->chipselect) | OP_CFG_OEN_EN;
	hifmc_write(host, FMC_OP_CFG, reg);
	fmc_pr(AC_DBG, "\t  Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, reg);

	reg = fmc_op_cmd1_en(ENABLE) | FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, reg);
	fmc_pr(AC_DBG, "\t  Set OP[%#x]%#x\n", FMC_OP, reg);

	fmc_cmd_wait_cpu_finish(host);

	spi->driver->wait_ready(spi);

	status = spi_general_get_flash_register(spi,
						SPI_CMD_FLAG_SR_MICRON);
	fmc_pr(AC_DBG, "\t Read flag status register[%#x]:%#x\n",
	       SPI_CMD_FLAG_SR_MICRON, status);
	if (spi_nor_get_4byte_by_flag_sr(status) != enable) {
		db_msg("Error: %s 4-byte failed! SR3:%#x\n",
		       str[enable], status);
		return status;
	}

	fmc_pr(AC_DBG, "\t  %s 4-byte success, SR3:%#x\n", str[enable], status);
	fmc_pr(AC_DBG, "\t* End SPI Nor flash %s 4-byte mode.\n", str[enable]);

	return 0;
}
