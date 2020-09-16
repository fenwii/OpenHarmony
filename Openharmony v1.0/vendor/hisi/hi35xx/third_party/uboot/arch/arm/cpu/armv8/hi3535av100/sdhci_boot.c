/*
 * sdhci_boot.c
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

/*
 * this file is only for emmc start.
 */

#include <config.h>
#include <asm/arch/platform.h>
#include <compiler.h>

#define DELAY_US		1000

#define MMC_BLK_SZ		512
#define CP_STEP1_SIZE	0x7800

/*
 * Controller registers
 */
#define SDHCI_DMA_ADDRESS       0x00
#define SDHCI_BLOCK_SIZE        0x04
#define SDHCI_BLOCK_COUNT       0x06
#define SDHCI_ARGUMENT          0x08

#define SDHCI_TRANSFER_MODE     0x0C
#define  SDHCI_TRNS_DMA         0x0001
#define  SDHCI_TRNS_BLK_CNT_EN  0x0002
#define  SDHCI_TRNS_READ        0x0010
#define  SDHCI_TRNS_MULTI       0x0020

#define SDHCI_COMMAND           0x0E
#define  SDHCI_CMD_RESP_NONE    0x0000
#define  SDHCI_CMD_RESP_LONG    0x0001
#define  SDHCI_CMD_RESP_SHORT   0x0002
#define  SDHCI_CMD_CRC          0x0008
#define  SDHCI_CMD_DATA         0x0020

#define SDHCI_RESPONSE          0x10
#define SDHCI_BUFFER            0x20

#define SDHCI_PRESENT_STATE     0x24
#define  SDHCI_PSTATE_DAT_0     0x00100000

#define SDHCI_HOST_CONTROL      0x28
#define  SDHCI_CTRL_4BITBUS     0x02
#define  SDHCI_CTRL_8BITBUS     0x20

#define SDHCI_POWER_CONTROL     0x29
#define  SDHCI_POWER_ON         0x01
#define  SDHCI_POWER_180        0x0A
#define  SDHCI_POWER_300        0x0C
#define  SDHCI_POWER_330        0x0E

#define SDHCI_CLOCK_CONTROL     0x2C
#define  SDHCI_CLOCK_INT_EN     0x0001
#define  SDHCI_CLOCK_INT_STABLE 0x0002
#define  SDHCI_CLOCK_CARD_EN    0x0004

#define SDHCI_TIMEOUT_CONTROL   0x2E

#define SDHCI_SOFTWARE_RESET    0x2F
#define  SDHCI_RESET_ALL        0x01
#define  SDHCI_RESET_CMD        0x02
#define  SDHCI_RESET_DATA       0x04

#define SDHCI_INT_STATUS        0x30
#define  SDHCI_INT_RESPONSE     0x00000001
#define  SDHCI_INT_DATA_END     0x00000002
#define  SDHCI_INT_DMA          0x00000008
#define  SDHCI_INT_DATA_AVAIL   0x00000020
#define  SDHCI_INT_NORMAL_MASK  0x00007FFF
#define  SDHCI_INT_ERROR_MASK   0xFFFF8000

#define SDHCI_INT_ENABLE        0x34

#define SDHCI_EMMC_CTRL         0x52C
#define  SDHCI_CARD_IS_EMMC     0x0001

#define SDHCI_BOOT_CTRL         0x52E
#define  MAN_BOOT_EN            0x0001
#define  VALIDATE_BOOT          0x0080

#define SDHCI_EMMC_HW_RESET     0x534

#define sdhci_make_cmd(idx, param)   ((((idx) & 0xFF) << 8) | ((param) & 0xFF))
#define sdhci_make_blksz(dma, blksz) ((((dma) & 0x7) << 12) | ((blksz) & 0xFFF))

#define MMC_CMD_GO_IDLE_STATE       0
#define MMC_CMD_SEND_OP_COND        1
#define MMC_CMD_ALL_SEND_CID        2
#define MMC_CMD_SET_RELATIVE_ADDR   3
#define MMC_CMD_SWITCH              6
#define MMC_CMD_SELECT_CARD         7
#define MMC_CMD_SEND_CSD            9
#define MMC_CMD_STOP_TRANSMISSION   12
#define MMC_CMD_SET_BLOCKLEN        16
#define MMC_CMD_READ_SINGLE_BLOCK   17
#define MMC_CMD_READ_MULTIPLE_BLOCK 18
#define MMC_CMD_SET_BLOCK_COUNT     23

#define MMC_SWITCH_MODE_WRITE_BYTE  0x3
#define MMC_SWITCH_ACCESS_SHIFT     24
#define MMC_SWITCH_INDEX_SHIFT      16
#define MMC_SWITCH_VALUE_SHIFT      8

/* SDMA Configuration */
#define BOUNDARY_SIZE      		(512 * 1024) /* 512K */
#define BOUNDARY_ARG       		(0x7 << 12)  /* 512K */
#define MMC_SDMA_ENABLE			1

#define OCR_BUSY			0x80000000
#define OCR_HCS			0x40000000

#define debug_printf(fmt, args...) ;
#define reg_get(addr) (*(volatile unsigned int *)((uintptr_t)(addr)))

static unsigned int is_bootmode(void)
{
	return !(reg_get(REG_BASE_SCTL + REG_PERI_EMMC_STAT) & EMMC_NORMAL_MODE);
}

static unsigned int get_hcs(void)
{
	return reg_get(REG_SAVE_HCS) & OCR_HCS;
}

static inline void delay(unsigned int cnt)
{
	while (cnt--)
		__asm__ __volatile__("nop");
}

static inline unsigned int sdhci_readb(unsigned addr)
{
	return *((volatile unsigned char *) (uintptr_t)(EMMC_BASE_REG + addr));
}

static inline void sdhci_writeb(unsigned val, unsigned addr)
{
	(*(volatile unsigned char *) (uintptr_t)(EMMC_BASE_REG + addr)) = (val);
}

static inline unsigned int sdhci_readw(unsigned addr)
{
	return *((volatile unsigned short *) (uintptr_t)(EMMC_BASE_REG + addr));
}

static inline void sdhci_writew(unsigned val, unsigned addr)
{
	(*(volatile unsigned short *) (uintptr_t)(EMMC_BASE_REG + addr)) = (val);
}

static inline unsigned int sdhci_readl(unsigned addr)
{
	return *((volatile unsigned int *) (uintptr_t)(EMMC_BASE_REG + addr));
}

static inline void sdhci_writel(unsigned val, unsigned addr)
{
	(*(volatile unsigned int *) (uintptr_t)(EMMC_BASE_REG + addr)) = (val);
}

static int sdhci_read_block_pio(void *data_addr, unsigned int block)
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
	return 0;
}

static int sdhci_check_int_status(unsigned int mask, unsigned int timeout)
{
	unsigned int reg;

	timeout *= 1000; /* ms is converted to us multiplied by 1000 */
	for (;;) {
		reg = sdhci_readl(SDHCI_INT_STATUS);
		if (reg & mask) {
			break;
		}
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

static int sdhci_boot_read(void *data_addr, unsigned int read_block)
{
	const unsigned int timeout = 2000; /* 2s timeout: 2000000 * 1us */
	int ret;
	unsigned int blocks = 0;

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

static int mmc_send_cmd(unsigned int cmd, unsigned int arg)
{
	const unsigned int timeout = 3000; /* 3s timeout: 3000000 * 1us */

	sdhci_writel(0xFFFFFFFF, SDHCI_INT_STATUS);
	sdhci_writel(arg, SDHCI_ARGUMENT);
	sdhci_writew(cmd, SDHCI_COMMAND);

	if (sdhci_check_int_status(SDHCI_INT_RESPONSE, timeout)) {
		debug_printf("send cmd error\n");
		return -1;
	}

	return 0;
}

static void mmc_read_cmd(unsigned long int start_addr, unsigned int src,
		unsigned int size, unsigned int dma)
{
	unsigned int cmd, hcs;
	unsigned short mode;

	/* Send CMD16 to set blocksize */
	cmd = sdhci_make_cmd(MMC_CMD_SET_BLOCKLEN, SDHCI_CMD_CRC |
				SDHCI_CMD_RESP_SHORT);
	mmc_send_cmd(cmd, MMC_BLK_SZ);

	/* set data timeout */
	sdhci_writeb(0xE, SDHCI_TIMEOUT_CONTROL);

	/* set host count */
	sdhci_writew(size, SDHCI_BLOCK_COUNT);

	/* Send CMD23 to set blockcount */
	cmd = sdhci_make_cmd(MMC_CMD_SET_BLOCK_COUNT,
	            SDHCI_CMD_CRC | SDHCI_CMD_RESP_SHORT);
	mmc_send_cmd(cmd, size);

	/* set transfer mode */
	mode = SDHCI_TRNS_READ | SDHCI_TRNS_MULTI | SDHCI_TRNS_BLK_CNT_EN;
	if (dma)
		mode |= SDHCI_TRNS_DMA;

	sdhci_writew(mode, SDHCI_TRANSFER_MODE);

	/* set SDMA address */
	if (dma)
		sdhci_writel(start_addr, SDHCI_DMA_ADDRESS);

	/* Send CMD18 for multiple block read */
	hcs = get_hcs();
	if (hcs) {
		cmd = sdhci_make_cmd(MMC_CMD_READ_MULTIPLE_BLOCK,
	                SDHCI_CMD_CRC | SDHCI_CMD_RESP_SHORT | SDHCI_CMD_DATA);
		mmc_send_cmd(cmd, src / MMC_BLK_SZ);
	} else {
		cmd = sdhci_make_cmd(MMC_CMD_READ_MULTIPLE_BLOCK,
	                SDHCI_CMD_CRC | SDHCI_CMD_RESP_SHORT | SDHCI_CMD_DATA);
		mmc_send_cmd(cmd, src);
	}
}

static int sdhci_normal_read_sdma(void *dst, unsigned int src, unsigned int size)
{
	unsigned int stat;
	unsigned int timeout;
	unsigned long int start_addr;

	start_addr = (uintptr_t)dst;

	/* set host block size 512 */
	sdhci_writew(MMC_BLK_SZ | BOUNDARY_ARG, SDHCI_BLOCK_SIZE);

	mmc_read_cmd(start_addr, src, size, MMC_SDMA_ENABLE);

	sdhci_writel(SDHCI_INT_RESPONSE, SDHCI_INT_STATUS);

	timeout = 300000; /* 3s timeout: 300000 * 10us */
	do {
		stat = sdhci_readl(SDHCI_INT_STATUS);
		if (stat & SDHCI_INT_ERROR_MASK) {
			debug_printf("interrupt error\n");
			return -1;
		}

		if (stat & SDHCI_INT_DMA) {
			sdhci_writel(SDHCI_INT_DMA, SDHCI_INT_STATUS);
			start_addr &= ~(BOUNDARY_SIZE - 1);
			start_addr += BOUNDARY_SIZE;
			sdhci_writel(start_addr, SDHCI_DMA_ADDRESS);
		}

		if (timeout > 0) {
			delay(10 * DELAY_US); /* delay 10us */
			timeout -= 1;
		} else {
			debug_printf("read timeout!\n");
			return -1;
		}
	} while (!(stat & SDHCI_INT_DATA_END));

	sdhci_writel(SDHCI_INT_DATA_END, SDHCI_INT_STATUS);

	return 0;
}

static void copy_step1_to_ddr(unsigned int *dst, unsigned int *src, unsigned int size)
{
	unsigned int cycle = size / sizeof(unsigned int);
	unsigned int i;

	for (i = 0; i < cycle; i++)
		*dst++ = *src++;
}

static int emmc_read_boot_data(void *data_addr, unsigned int data_size)
{
	unsigned int read_block;
	int bootmode;

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

	bootmode = is_bootmode();
	if (bootmode)
		return sdhci_boot_read(data_addr, read_block);

	return sdhci_normal_read_sdma(data_addr, CP_STEP1_SIZE, read_block);
}

int emmc_boot_read(void *ptr, unsigned int size)
{
	int ret;

	ret = emmc_read_boot_data(ptr, size);
	return ret;
}
