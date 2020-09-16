/*
 * himci_boot.c
 *
 * This file is only for emmc boot.
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

#include <config.h>
#include <asm/arch/platform.h>
#include <compiler.h>

#ifndef CONFIG_ASIC
#define DELAY_US        10
#else
#define DELAY_US        1000
#endif

#define MMC_BLK_SZ      512

/* mmc.h */
#define MMC_CMD_GO_IDLE_STATE       0
#define MMC_CMD_SEND_OP_COND        1
#define MMC_CMD_ALL_SEND_CID        2
#define MMC_CMD_SET_RELATIVE_ADDR   3
#define MMC_CMD_SET_DSR         4
#define MMC_CMD_SWITCH          6
#define MMC_CMD_SELECT_CARD     7
#define MMC_CMD_SEND_EXT_CSD        8
#define MMC_CMD_SEND_CSD        9
#define MMC_CMD_SEND_CID        10
#define MMC_CMD_STOP_TRANSMISSION   12
#define MMC_CMD_SEND_STATUS     13
#define MMC_CMD_SET_BLOCKLEN        16
#define MMC_CMD_READ_SINGLE_BLOCK   17
#define MMC_CMD_READ_MULTIPLE_BLOCK 18
#define MMC_CMD_WRITE_SINGLE_BLOCK  24
#define MMC_CMD_WRITE_MULTIPLE_BLOCK    25
#define MMC_CMD_APP_CMD         55
#define SD_CMD_SEND_IF_COND     8
#define SD_CMD_APP_SEND_OP_COND     41
#define SD_CMD_APP_SET_BUS_WIDTH    6

#define OCR_BUSY        0x80000000
#define OCR_HCS         0x40000000

#define MMC_VDD_32_33       0x00100000  /* VDD voltage 3.2 ~ 3.3 */
#define MMC_VDD_33_34       0x00200000  /* VDD voltage 3.3 ~ 3.4 */

#define MMC_SWITCH_MODE_WRITE_BYTE  0x03 /* Set target byte to value */

#define EXT_CSD_BUS_WIDTH   183 /* R/W */
#define EXT_CSD_HS_TIMING   185 /* R/W */

#define EXT_CSD_BUS_WIDTH_1 0   /* Card is in 1 bit mode */
#define EXT_CSD_BUS_WIDTH_4 1   /* Card is in 4 bit mode */
#define EXT_CSD_BUS_WIDTH_8 2   /* Card is in 8 bit mode */

static inline void delay(unsigned int cnt)
{
	while (cnt--)
		__asm__ __volatile__("nop");
}

#ifdef CONFIG_SDHCI
#define SDHCI_BUFFER            0x20
#define SDHCI_INT_STATUS        0x30
#define SDHCI_INT_DATA_AVAIL    0x00000020
#define SDHCI_INT_ERROR_MASK    0xFFFF8000

#define debug_printf(fmt, args...) ;

static inline unsigned int sdhci_readl(unsigned addr)
{
	uintptr_t reg_addr  = EMMC_BASE_REG + addr;

	return *((volatile unsigned *) (reg_addr));
}

static inline void sdhci_writel(unsigned val, unsigned addr)
{
	uintptr_t reg_addr  = EMMC_BASE_REG + addr;

	(*(volatile unsigned *) (reg_addr)) = (val);
}

static void sdhci_read_block_pio(void *data_addr, unsigned int block)
{
	const unsigned int offset = sizeof(unsigned int);
	unsigned int size;
	unsigned char *buf;

	size = MMC_BLK_SZ;
	buf = (unsigned char *)data_addr + MMC_BLK_SZ * block;
	while (size) {
		*(unsigned int *)buf = sdhci_readl(SDHCI_BUFFER);
		buf += offset;
		size -= offset;
	}
}

int sdhci_check_int_status(unsigned int mask, unsigned int timeout)
{
	unsigned int reg;

	for (;;) {
		reg = sdhci_readl(SDHCI_INT_STATUS);
		if (reg & mask)
			break;
		if (!(--timeout)) {
			debug_printf("wait int status time out, reg = 0x%x, mask = 0x%x\n",
						 reg, mask);
			return -1;
		}
		if (reg & SDHCI_INT_ERROR_MASK) {
			debug_printf("int err: reg = 0x%x\n", reg);
			return -1;
		}

		delay(1000 * DELAY_US); /* ms converted to us multiplied by 1000 */
	}

	return 0;
}

static void copy_step1_to_ddr(unsigned int *dst, unsigned int *src, unsigned int size)
{
	const unsigned int cycle = size / sizeof(unsigned int);
	unsigned int i;

	for (i = 0; i < cycle; i++)
		*dst++ = *src++;
}

#define CP_STEP1_SIZE 0x6000
int sdhci_read_boot_data(void *data_addr, unsigned int data_size)
{
	const unsigned int timeout = 2000; /* 2s timeout: 2000000 * 1us */
	unsigned int blocks = 0;
	unsigned int read_block;
	int ret;

	if (data_size <= CP_STEP1_SIZE) {
		copy_step1_to_ddr((void *)data_addr, (void *)RAM_START_ADRS, data_size);
		return 0;
	} else {
		copy_step1_to_ddr((void *)data_addr, (void *)RAM_START_ADRS, CP_STEP1_SIZE);
		data_addr += CP_STEP1_SIZE;
		data_size -= CP_STEP1_SIZE;
	}

	if (data_size % MMC_BLK_SZ) {
		debug_printf("sdhci_read_boot_data error\n");
		debug_printf("data_size:%d not round by block size\n", data_size);
		read_block = data_size / MMC_BLK_SZ + 1;
	} else {
		read_block = data_size / MMC_BLK_SZ;
	}

	while (1) {
		ret = sdhci_check_int_status(SDHCI_INT_DATA_AVAIL, timeout);
		if (ret) {
			debug_printf("wait data available int time out\n");
			return ret;
		}

		sdhci_writel(SDHCI_INT_DATA_AVAIL, SDHCI_INT_STATUS);
		sdhci_read_block_pio(data_addr, blocks);

		blocks++;
		if (blocks == read_block)
			break;
	}

	return 0;
}

void emmc_boot_read(void *ptr, unsigned int size)
{
	sdhci_read_boot_data(ptr, size);
}
#endif
