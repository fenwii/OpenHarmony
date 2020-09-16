/*
 * hifmc100_os.c
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

#include "hifmc100_os.h"
#include <common.h>

/*****************************************************************************/
static struct hifmc_host hifmc100_host = {
	.chip = NULL,
};

/*****************************************************************************/
static void hifmc100_driver_probe(struct nand_chip *chip, unsigned char cs)
{
	int ret = 0;
	struct hifmc_host *host = &hifmc100_host;

	fmc_pr(BT_DBG, "\t*-Start SPI Nand flash driver probe\n");

	if (!host->chip) {
		/* Hifmc ip version check */
		if (hifmc_ip_ver_check())
			db_bug("Error: hifmc IP version unknown!\n");

		/* Hifmc current SPI device type check */
		hifmc_dev_type_switch(FLASH_TYPE_SPI_NAND);

		/* Hifmc SPI nand init */
		memset((char *)host, 0, sizeof(struct hifmc_host));
		ret = hifmc100_host_init(host);
		if (ret) {
			db_msg("Error: Host init failed, result: %d\n", ret);
			/* Change SPI device type to default */
			hifmc_dev_type_switch(FLASH_TYPE_DEFAULT);
			return;
		}
	} else {
		fmc_pr(BT_DBG, "\t*-SPI Nand host is initialized.\n");
	}

	host->cmd_op.cs = cs;
	host->chip = chip;
	hifmc100_spi_nand_init(host);

	fmc_pr(BT_DBG, "\t*-End SPI Nand flash driver probe.\n");

	return;
}

/*****************************************************************************/
static int hifmc100_spi_nand_pre_probe(struct nand_chip *chip)
{
	uint8_t nand_maf_id;
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct hifmc_host *host = chip->priv;

	/* Reset the chip first */
	host->send_cmd_reset(host);
	chip->dev_ready(mtd);

	/* Check the ID */
	host->offset = 0;
	memset((unsigned char *)(chip->IO_ADDR_R), 0, 0x10);
	host->send_cmd_readid(host);
	nand_maf_id = readb(chip->IO_ADDR_R);
	if (nand_maf_id == 0x00 || nand_maf_id == 0xff) {
		printf("Cannot found a valid SPI Nand Device\n");
		return 1;
	}

	return 0;
}

/*****************************************************************************/
int board_nand_init(struct nand_chip *chip)
{
	unsigned char chip_num = CONFIG_SPI_NAND_MAX_CHIP_NUM;
	static unsigned char cs = 0;
	unsigned char *hifmc_cs = NULL;

	for (cs = 0; chip_num && (cs < CONFIG_HIFMC_MAX_CS_NUM); cs++) {
		hifmc_cs = get_cs_number(cs);
		if (*hifmc_cs) {
			fmc_pr(BT_DBG, "\t\t*-Current CS(%d) is occupied.\n",
			       cs);
			continue;
		}

		hifmc100_driver_probe(chip, cs);
		chip_num--;
	}

	if (chip_num)
		return 1;

	if (hifmc100_spi_nand_pre_probe(chip))
		return 1;

	return 0;
}

/*****************************************************************************/
static int hifmc100_spi_nand_get_ecctype(void)
{
	struct hifmc_host *host = &hifmc100_host;

	if (!host->chip) {
		printf("SPI Nand flash uninitialized.\n");
		return -1;
	}

	return match_ecc_type_to_yaffs(hifmc100_host.ecctype);
}

/*****************************************************************************/
int nand_get_ecctype(void)
{
	return hifmc100_spi_nand_get_ecctype();
}