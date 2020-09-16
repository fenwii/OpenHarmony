/*
 * sample_hi3559av100.c
 *
 * This just a sample for i2c operation.
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
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <asm/io.h>
#include <linux/errno.h>
#include <i2c.h>
/* I2C0 */
#define IO_CONFIG_REG26     0x1F000068
#define IO_CONFIG_REG27     0x1F00006C
/* I2C1 */
#define IO_CONFIG_REG31     0x1F00007C
#define IO_CONFIG_REG32     0x1F000080

#define I2C10_EN_MASK           BIT(1)
#define I2C_EN_MASK           (BIT(1) | BIT(0))

/* Configure pin multiplexing,this is just an example */
static int hibvt_i2c_iomux_config(unsigned int i2c_num)
{
	unsigned int val;
	switch (i2c_num) {
	case 0: /* 0 layer */
		val = readl(IO_CONFIG_REG26);
		val |= I2C_EN_MASK;
		writel(val, IO_CONFIG_REG26);
		val = readl(IO_CONFIG_REG27);
		val |= I2C_EN_MASK;
		writel(val, IO_CONFIG_REG27);
		break;
	case 1: /* 1 layer */
		val = readl(IO_CONFIG_REG31);
		val |= I2C_EN_MASK;
		writel(val, IO_CONFIG_REG31);
		val = readl(IO_CONFIG_REG32);
		val |= I2C_EN_MASK;
		writel(val, IO_CONFIG_REG32);
		break;
	case 11: /* 11 layer */
		break;
	default:
		return 1;
	}
	return 0;
}

#define I2C_SPEED_100K  100000
int hibvt_i2c_sample(unsigned int i2c_num)
{
	unsigned char client_addr;
	unsigned int reg_addr;
	int reg_width;
	int length = 1;
	unsigned char *buffer;
	int ret = 0;

	buffer = malloc(length);
	if (!buffer)
		return 1;

	switch (i2c_num) {
	case 0: /* 0 layer */
		client_addr = 0x34;
		reg_addr = 0xE07A;
		reg_width = 2; /* 2: reg width  */
		buffer[0] = 0x10;
		break;
	case 1: /* 1 layer */
		client_addr = 0x34;
		reg_addr = 0xE07A;
		reg_width = 2; /* 2: reg width  */
		buffer[0] = 0x24;
		break;
	case 11: /* 11 layer */
		client_addr = 0xb4;
		reg_addr = 0x31;
		reg_width = 1;
		buffer[0] = 0x24;
		break;
	default:
		goto fail;
	}

	ret = hibvt_i2c_iomux_config(i2c_num);
	if (ret) {
		printf("pin multiplexing fail!\n");
		goto fail;
	}

	i2c_init(I2C_SPEED_100K, i2c_num);

	ret = i2c_write(client_addr, reg_addr, reg_width, buffer, length);
	if (ret) {
		printf("i2c write fail!\n");
		goto fail;
	}

	ret = i2c_read(client_addr, reg_addr, reg_width, buffer, length);
	if (ret) {
		printf("i2c read fail!\n");
		goto fail;
	}
	/* The data in the buffer is the data obtained from the I2c_num. */
	/* Todo something */
	printf("addr:0x%x,value:0x%x\n", reg_addr, buffer[0]);

fail:
	free(buffer);
	return ret;
}

