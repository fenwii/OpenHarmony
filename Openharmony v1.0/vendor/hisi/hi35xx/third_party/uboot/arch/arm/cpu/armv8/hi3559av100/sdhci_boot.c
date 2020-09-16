/*
 * sdhci_boot.c
 *
 * This file is only for emmc start.
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

#define DELAY_US        1000

#define MMC_BLK_SZ      512
#define CP_STEP1_SIZE   0x8000

#define SDHCI_BUFFER            0x20
#define SDHCI_INT_STATUS        0x30
#define SDHCI_INT_DATA_AVAIL    0x00000020
#define SDHCI_INT_ERROR_MASK    0xFFFF8000

#define debug_printf(fmt, args...) ;

static inline void delay(unsigned int cnt)
{
	while (cnt--)
		__asm__ __volatile__("nop");
}

static inline unsigned int sdhci_readl(unsigned addr)
{
	return *((volatile unsigned *)(uintptr_t)(EMMC_BASE_REG + addr));
}

static inline void sdhci_writel(unsigned val, unsigned addr)
{
	(*(volatile unsigned *)(uintptr_t)(EMMC_BASE_REG + addr)) = (val);
}

static void sdhci_read_block_pio(void *data_addr, unsigned int block)
{
	unsigned int offset = sizeof(unsigned int);
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

static int sdhci_check_int_status(unsigned int mask, unsigned int timeout)
{
	unsigned int reg;

	timeout *= 1000; /* ms is converted to us multiplied by 1000 */
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

		delay(DELAY_US);
	}

	return 0;
}

static void copy_step1_to_ddr(unsigned int *dst, unsigned int *src, unsigned int size)
{
	unsigned int cycle = size / sizeof(unsigned int);
	unsigned int i;

	for (i = 0; i < cycle; i++)
		*dst++ = *src++;
}

static int sdhci_read_boot_data(void *data_addr, unsigned int data_size)
{
	const unsigned int timeout = 2000; /* 2s timeout: 2000000 * 1us */
	unsigned int blocks = 0;
	unsigned int read_block;
	int ret;

	if (data_size <= CP_STEP1_SIZE) {
		copy_step1_to_ddr((void *)data_addr, (void *)CP_STEP1_ADDR, data_size);
		return 0;
	} else {
		copy_step1_to_ddr((void *)data_addr, (void *)CP_STEP1_ADDR, CP_STEP1_SIZE);
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
			return -1;
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
