/*
 * emmc_boot.c
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
#include <himci_reg.h>
#include <compiler.h>

#define DELAY_US        1000
#define CP_STEP1_SIZE   0x6000

static void copy_step1_to_ddr(unsigned int *dst,
			      unsigned int *src,
			      unsigned int size)
{
	unsigned int i;

	for (i = 0; i < (size >> NUM_2); i++)
		*dst++ = *src++;
}

static inline unsigned int himci_readl(unsigned addr)
{
	return *((volatile unsigned *)(uintptr_t)(addr));
}

static inline void himci_writel(unsigned val, unsigned addr)
{
	(*(volatile unsigned *)(uintptr_t)(addr)) = val;
}

static inline void delay(unsigned int cnt)
{
	while (cnt--)
		__asm__ __volatile__("nop");
}

static void emmc_deinit(void)
{
	unsigned int mmc_base = EMMC_REG_BASE;
	unsigned int val;

	val = himci_readl(mmc_base + MCI_CTRL);
	val |= (CTRL_RESET | FIFO_RESET | DMA_RESET);
	himci_writel(val, mmc_base + MCI_CTRL);

	/* clear MMC host intr */
	himci_writel(ALL_INT_CLR, mmc_base + MCI_RINTSTS);
}

static void emmc_boot_mode_read(void *ptr, unsigned int size)
{
	unsigned int count;
	unsigned int val;
	unsigned int tmp_reg;
	unsigned int data;
	unsigned int *buf = NULL;

	if (size <= CP_STEP1_SIZE) {
		copy_step1_to_ddr(ptr, (void *)RAM_START_ADRS, size);
		return;
	}
	copy_step1_to_ddr(ptr, (void *)RAM_START_ADRS, CP_STEP1_SIZE);
	buf = (unsigned int *)(ptr + CP_STEP1_SIZE);
	size = (size - CP_STEP1_SIZE) >> NUM_2;

	while (size > 0) {
		tmp_reg = himci_readl(EMMC_REG_BASE + MCI_STATUS);
		count = (tmp_reg >> FIFO_COUNT) & FIFO_COUNT_MASK;

		if (count > size)
			count = size;

		/* start to read data */
		while (1) {
			val = (DCRC_INT_STATUS | FRUN_INT_STATUS |
				HLE_INT_STATUS | SBE_INT_STATUS | EBE_INT_STATUS);
			tmp_reg = himci_readl(EMMC_REG_BASE + MCI_RINTSTS);
			if (tmp_reg & val)
				return;

			if (tmp_reg & RXDR_INT_STATUS)
				break;
		}

		himci_writel(ALL_INT_CLR, EMMC_REG_BASE + MCI_RINTSTS);

		for (; count != 0; --count) {
			data = himci_readl(EMMC_REG_BASE + MCI_FIFO_START);

			*buf = data;
			buf++;
			--size;
		}
	}

	himci_writel(START_CMD | DISABLE_BOOT | STOP_ABORT_CMD,
						EMMC_REG_BASE + MCI_CMD);
	count = 1000; /* 1000: Cycle */
	do {
		delay(DELAY_US);
		count--;
		tmp_reg = himci_readl(EMMC_REG_BASE + MCI_CMD);
	} while ((tmp_reg & START_CMD) && count);

	count = 1000; /* 1000: Cycle */
	do {
		delay(DELAY_US);
		count--;
		tmp_reg = himci_readl(EMMC_REG_BASE + MCI_RINTSTS);
	} while (!(tmp_reg & DTO_INT_STATUS) && count);
}

static void emmc_boot_mode_deinit(void)
{
	unsigned int mmc_base = EMMC_REG_BASE;

	himci_writel(START_CMD | DISABLE_BOOT | STOP_ABORT_CMD, mmc_base + MCI_CMD);
}

void emmc_boot_read(void *ptr, unsigned int size)
{
	emmc_boot_mode_read(ptr, size);
	emmc_boot_mode_deinit();
	emmc_deinit();
}
