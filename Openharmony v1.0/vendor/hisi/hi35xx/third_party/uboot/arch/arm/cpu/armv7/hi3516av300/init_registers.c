/*
 * init_registers.c
 *
 * The file is Parsing table initialization.
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

#include <asm/arch/platform.h>
#include <compiler.h>

#define W_WHETHER_WRITE     (1<<0)
#define W_WHETHER_PM        (1<<1)
#define W_WHETHER_BOOT_NORMAL   (1<<2)
#define W_BIT_OFFSET        3
#define W_BIT_MASK          (0x1f<<W_BIT_OFFSET)
#define W_REG_BIT_OFFSET    11
#define W_REG_BIT_MASK      (0x1f<<W_REG_BIT_OFFSET)

#define R_WHETHER_READ      (W_WHETHER_WRITE<<16)
#define R_WHETHER_PM        (W_WHETHER_PM<<16)
#define R_WHETHER_BOOT_NORMAL   (W_WHETHER_BOOT_NORMAL<<16)
#define R_BIT_OFFSET        (W_BIT_OFFSET + 16)
#define R_BIT_MASK          (W_BIT_MASK<<16)
#define R_REG_BIT_OFFSET    (W_REG_BIT_OFFSET + 16)
#define R_REG_BIT_MASK      (W_REG_BIT_MASK<<16)

#define RW_BIT_NUM	32

struct regentry {
	unsigned int reg_addr;
	unsigned int value;
	unsigned int delay;
	unsigned int attr;
};

static inline void dwb(void) /* drain write buffer */
{
}

static inline unsigned int readl(unsigned addr)
{
	unsigned int val;
	val = (*(volatile unsigned int *)((uintptr_t)(addr)));
	return val;
}

static inline void writel(unsigned val, unsigned addr)
{
	dwb();
	(*(volatile unsigned int *)((uintptr_t)(addr))) = val;
	dwb();
}

static inline void delay(void)
{
	__asm__ __volatile__("nop");
}

static void reg_read(struct regentry *reg, unsigned int *ret)
{
	unsigned int reg_val_r;
	unsigned int bit_start_r;
	unsigned int bit_num_r;

	bit_start_r = ((reg->attr & R_REG_BIT_MASK) >> R_REG_BIT_OFFSET);
	bit_num_r = ((reg->attr & R_BIT_MASK) >> R_BIT_OFFSET) + 1;
	reg_val_r = (*(volatile unsigned *)((uintptr_t)(reg->reg_addr)));

	if (bit_num_r != RW_BIT_NUM) {
		reg_val_r >>= bit_start_r;
		reg_val_r &= ((1 << bit_num_r) - 1);
	}

	*ret = ((reg_val_r == reg->value) ? 0 : 1);
}

static void reg_write(struct regentry *reg)
{
	unsigned int reg_val_w;
	unsigned int delay_2;
	unsigned int bit_start_w;
	unsigned int bit_num_w;

	delay_2 = reg->delay;
	bit_start_w = ((reg->attr & W_REG_BIT_MASK) >> W_REG_BIT_OFFSET);
	bit_num_w = ((reg->attr & W_BIT_MASK) >> W_BIT_OFFSET) + 1;
	reg_val_w = (*(volatile unsigned *)((uintptr_t)(reg->reg_addr)));

	if (bit_num_w == RW_BIT_NUM) {
		reg_val_w = reg->value;
	} else {
		reg_val_w &= (~(((1 << bit_num_w) - 1) << bit_start_w));
		reg_val_w |= (reg->value) << bit_start_w;
	}
	writel(reg_val_w, (uintptr_t)reg->reg_addr);

	do {
		delay();
	} while (delay_2--);
}

static void read_write(struct regentry *reg, unsigned int pm)
{
	unsigned int ret;
	unsigned int delay_1;

	ret = 0;
	delay_1 = reg->delay;

	if (pm) {
		if (reg->attr & W_WHETHER_PM) {
			reg_write(reg);
		} else if (reg->attr & R_WHETHER_PM) {
			do {
				reg_read(reg, &ret);
				delay();
			} while (ret);

			do {
				delay();
			} while (delay_1--);
		} else {
			do {
				delay();
			} while (delay_1--);
		}
	} else {
		if (reg->attr & W_WHETHER_BOOT_NORMAL) {
			reg_write(reg);
		} else if (reg->attr & R_WHETHER_BOOT_NORMAL) {
			do {
				reg_read(reg, &ret);
				delay();
			} while (ret);

			do {
				delay();
			} while (delay_1--);
		} else {
			do {
				delay();
			} while (delay_1--);
		}
	}
}

static void part_read_write(struct regentry *reg_table, unsigned int pm)
{
	unsigned int i;

	for (i = 0; ; i++) {
		if ((!reg_table[i].reg_addr) && (!reg_table[i].value) &&
			(!reg_table[i].delay) && (!reg_table[i].attr)) {
			goto main_end;
		}

		read_write(&reg_table[i], pm);
	}

main_end:
	delay();
}

/*
 * base - reg base address
 * pm   - is suspend
 *	  0 normal
 *	  1 pm
 */
void init_registers(unsigned long base, unsigned long pm)
{
	struct regentry *reg_table = (struct regentry *)((uintptr_t)(base));

	part_read_write(reg_table, pm);
}

