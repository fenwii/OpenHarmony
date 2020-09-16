/*
 * hifmc100_spi_s25fl256s.c
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
/* SpanSion SPI Nor Flash "S25FL256S" Bank Address Register command */
#define SS_SPI_CMD_BRRD         0x16    /* Read Bank Register */
#define SS_SPI_CMD_BRWR         0x17    /* Write Bank Register */

/* Bank Address Register length(byte) */
#define SS_SPI_NOR_BR_LEN       1

/* Extended Address Enable bit[7] include in Bank Address Register */
#define SS_SPI_NOR_BR_EAE_SHIFT     7
#define SS_SPI_NOR_BR_EAE_MASK      (1 << SS_SPI_NOR_BR_EAE_SHIFT)
#define ss_spi_nor_get_eae_by_br(br)    (((br) & SS_SPI_NOR_BR_EAE_MASK) \
						>> SS_SPI_NOR_BR_EAE_SHIFT)

/*****************************************************************************/
static void spi_s25fl256s_set_cmd(struct hifmc_spi *spi)
{
	unsigned int regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	regval = fmc_cmd_cmd1(SS_SPI_CMD_BRWR);
	hifmc_write(host, FMC_CMD, regval);
	fmc_pr(AC_DBG, "\t  Set CMD[%#x]%#x\n", FMC_CMD, regval);

	regval = op_cfg_fm_cs(spi->chipselect);
	hifmc_write(host, FMC_OP_CFG, regval);
	fmc_pr(AC_DBG, "\t  Set OP_CFG[%#x]%#x\n", FMC_OP_CFG, regval);

	regval = fmc_data_num_cnt(SS_SPI_NOR_BR_LEN);
	hifmc_write(host, FMC_DATA_NUM, regval);
	fmc_pr(AC_DBG, "\t  Set DATA_NUM[%#x]%#x\n", FMC_DATA_NUM, regval);

	regval = fmc_op_cmd1_en(ENABLE)
		 | fmc_op_write_data_en(ENABLE)
		 | FMC_OP_REG_OP_START;
	hifmc_write(host, FMC_OP, regval);
	fmc_pr(AC_DBG, "\t  Set OP[%#x]%#x\n", FMC_OP, regval);

	fmc_cmd_wait_cpu_finish(host);
}
/*****************************************************************************/
/*
  enable 4byte address mode for SpanSion "s25fl256" SPI Nor
*/
static int spi_s25fl256s_entry_4addr(struct hifmc_spi *spi, int enable)
{
	unsigned char bank;
	const char *str[] = {"Disable", "Enable"};
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	fmc_pr(AC_DBG, "\t* Start SpanSion SPI Nor %s 4-byte mode.\n",
	       str[enable]);

	if (spi->addrcycle != SPI_NOR_4BYTE_ADDR_LEN) {
		fmc_pr(AC_DBG, "\t* Flash isn't support 4-byte mode.\n");
		return 0;
	}

	/* Read old Bank Register value */
	bank = spi_general_get_flash_register(spi, SS_SPI_CMD_BRRD);
	fmc_pr(AC_DBG, "\t  Read Bank Register[%#x]%#x\n", SS_SPI_CMD_BRRD,
	       bank);
	if (ss_spi_nor_get_eae_by_br(bank) == enable) {
		fmc_pr(AC_DBG, "\t* 4-byte was %sd, bank:%#x\n", str[enable],
		       bank);
		return 0;
	}

	/* Write new Bank Register value */
	if (enable)
		bank |= SS_SPI_NOR_BR_EAE_MASK;
	else
		bank &= ~SS_SPI_NOR_BR_EAE_MASK;
	writeb(bank, host->iobase);
	fmc_pr(AC_DBG, "\t  Write IO[%p]%#x\n", host->iobase,
	       *(unsigned char *)host->iobase);

	spi_s25fl256s_set_cmd(spi);

	spi->driver->wait_ready(spi);

	/* Check out Bank Register value */
	bank = spi_general_get_flash_register(spi, SS_SPI_CMD_BRRD);
	fmc_pr(AC_DBG, "\t  Read Bank Register[%#x]%#x\n", SS_SPI_CMD_BRRD,
	       bank);
	if (ss_spi_nor_get_eae_by_br(bank) != enable) {
		db_msg("Error: %s 4bytes failed! bank: %#x\n", str[enable],
		       bank);
		return bank;
	}

	fmc_pr(AC_DBG, "\t  %s 4byte success, bank:%#x.\n", str[enable], bank);
	fmc_pr(AC_DBG, "\t* End SpanSion SPI Nor %s 4-byte mode.\n",
	       str[enable]);

	return 0;
}

