/*
 * startup.c
 *
 * This file is used to initialize the board hardware.
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
#include <linux/kconfig.h>
#include <asm/io.h>
#include <compiler.h>
#include <hicpu_common.h>

/******************************************************************************/
const uintptr_t image_entry = (CONFIG_SYS_TEXT_BASE);

/******************************************************************************/
#define error(_s)               uart_early_puts(_s)
#define putstr(_s)              uart_early_puts(_s)

#include "hw_decompress.c"
#define GZIP_SIZE_OFFSET 0x4

#ifndef CONFIG_SYS_ICACHE_OFF
/* Invalidate entire I-cache and branch predictor array */
static void invalidate_icache_all(void)
{
	/*
	 * Invalidate all instruction caches to PoU.
	 * Also flushes branch target cache.
	 */
	asm volatile("mcr p15, 0, %0, c7, c5, 0" : : "r"(0));

	/* Invalidate entire branch predictor array */
	asm volatile("mcr p15, 0, %0, c7, c5, 6" : : "r"(0));

	/* Full system DSB - make sure that the invalidation is complete */
	dsb();

	/* ISB - make sure the instruction stream sees it */
	isb();
}
#else
static void invalidate_icache_all(void)
{
}
#endif

/******************************************************************************/
void start_armboot(void)
{
	unsigned char *pdst_l32 = NULL;
	unsigned int image_data_len;
	int pdst_len;
	int ret;
	int i;
	char *p = NULL;
	char *q = NULL;

	uart_early_init();
	uart_early_puts("\r\nUncompress ");

	/* use direct address mode */
	hw_dec_type = 0;
	/* init hw decompress IP */
	hw_dec_init();

	/* start decompress */
	pdst_l32 = (unsigned char *)(uintptr_t)image_entry;
	image_data_len = input_data_end - input_data;

	/* get dets length from compress image */
	p = (char *)&pdst_len;
	q = (char *)(input_data_end - GZIP_SIZE_OFFSET);
	for (i = 0; i < sizeof(int); i++)
		p[i] = q[i];

	ret = hw_dec_decompress(pdst_l32, &pdst_len, input_data, image_data_len, NULL);
	if (!ret) {
		uart_early_puts("Ok!");
	} else {
		uart_early_puts("Fail!");
		while (1) ;
	}
	/* uinit hw decompress IP */
	hw_dec_uinit();
	void (*uboot)(void);
	uboot = (void (*))CONFIG_SYS_TEXT_BASE;
	invalidate_icache_all();
	uboot();
}

/******************************************************************************/
void hang(void)
{
	uart_early_puts("### ERROR ### Please RESET the board ###\n");
	for (; ;) ;
}


void do_bad_sync(void)
{
	uart_early_puts("bad sync abort\r\n");
	uart_early_puts("Resetting CPU ...\r\n");
	reset_cpu(0);
}

void do_sync(void)
{
	uart_early_puts("sync abort\r\n");
	uart_early_puts("Resetting CPU ...\r\n");
	reset_cpu(0);
}

void do_bad_error(void)
{
	uart_early_puts("bad error\r\n");
	uart_early_puts("Resetting CPU ...\r\n");
	reset_cpu(0);
}

void do_error(void)
{
	uart_early_puts("error\r\n");
	uart_early_puts("Resetting CPU ...\r\n");
	reset_cpu(0);
}

void do_bad_fiq(void)
{
	uart_early_puts("bad fast interrupt request\r\n");
	uart_early_puts("Resetting CPU ...\r\n");
	reset_cpu(0);
}

void do_bad_irq(void)
{
	uart_early_puts("bad interrupt request\r\n");
	uart_early_puts("Resetting CPU ...\r\n");
	reset_cpu(0);
}

void do_fiq(void)
{
	uart_early_puts("fast interrupt request\r\n");
	uart_early_puts("Resetting CPU ...\r\n");
	reset_cpu(0);
}

void do_irq(void)
{
	uart_early_puts("interrupt request\r\n");
	uart_early_puts("Resetting CPU ...\r\n");
	reset_cpu(0);
}
