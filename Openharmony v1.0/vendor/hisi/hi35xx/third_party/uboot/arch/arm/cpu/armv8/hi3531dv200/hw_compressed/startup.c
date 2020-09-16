/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General Public License as published by the
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
/*
 * SCTLR_EL1/SCTLR_EL2/SCTLR_EL3 bits definitions
 */
#define CR_M            (1 << 0)        /* MMU enable                   */
#define CR_A            (1 << 1)        /* Alignment abort enable       */
#define CR_C            (1 << 2)        /* Dcache enable                */
#define CR_SA           (1 << 3)        /* Stack Alignment Check Enable */
#define CR_I            (1 << 12)       /* Icache enable                */
#define CR_WXN          (1 << 19)       /* Write Permision Imply XN     */
#define CR_EE           (1 << 25)       /* Exception (Big) Endian       */


/******************************************************************************/
extern void uart_early_init(void);
extern void uart_early_puts(const char *ss);
extern void reset_cpu(unsigned long addr);
/******************************************************************************/
const uintptr_t IMAGE_ENTRY = (CONFIG_SYS_TEXT_BASE);

extern unsigned char input_data[];
extern unsigned char input_data_end[];
extern unsigned long _start;

/******************************************************************************/
#define error(_s)               uart_early_puts(_s)
#define putstr(_s)              uart_early_puts(_s)

#define large_malloc(_n)        malloc(_n)
#define large_free(_n)          free(_n)

/******************************************************************************/
/*
 * this value will be (_armboot_start - CONFIG_SYS_MALLOC_LEN)
 */
static long malloc_start_lzma;

/******************************************************************************/
static void *malloc(unsigned int size)
{
	void *ptr = (void *)(uintptr_t)malloc_start_lzma;
	malloc_start_lzma += size;

	if (malloc_start_lzma >= (uintptr_t)&_start)
		return NULL;

	return ptr;
}
/******************************************************************************/
static void free(void *ptr)
{
}
/******************************************************************************/

#include "unlzma.c"

extern void __asm_invalidate_icache_all(void);
extern void __asm_invalidate_dcache_all(void);
extern void __asm_invalidate_l3_dcache(void);

void invalidate_icache_all(void);
void dcache_enable(void);
void dcache_disable(void);

/******************************************************************************/
void start_armboot(void)
{
	unsigned char *pdst = (unsigned char *)IMAGE_ENTRY;
	unsigned int image_data_len = input_data_end - input_data;

	malloc_start_lzma = ((uintptr_t)&_start - CONFIG_SYS_MALLOC_LEN);
	uart_early_init();

	dcache_enable();

	if (input_data[0] == 0x5D) {
		uart_early_puts("\nUncompress");
		decompress(input_data, image_data_len, pdst);
		uart_early_puts("Ok\r\n");
	} else {
		int *s = (int *)input_data;
		int *d = (int *)pdst;
		unsigned int len = ((image_data_len + 3) >> 2);
		while (len--)
			*d++ = *s++;
	}

	dcache_disable();

	void (*uboot)(void);
	uboot = (void (*))CONFIG_SYS_TEXT_BASE;
	invalidate_icache_all();
	uboot();
}

/******************************************************************************/
void hang(void)
{
	uart_early_puts("### ERROR ### Please RESET the board ###\n");
	for (;;)
		;
}

static inline unsigned int current_el(void)
{
	unsigned int el;
	asm volatile("mrs %0, CurrentEL" : "=r" (el) : : "cc");
	return el >> 2;
}

static inline void set_sctlr(unsigned int val)
{
	unsigned int el;

	el = current_el();
	if (el == 1)
		asm volatile("msr sctlr_el1, %0" : : "r" (val) : "cc");
	else if (el == 2)
		asm volatile("msr sctlr_el2, %0" : : "r" (val) : "cc");
	else
		asm volatile("msr sctlr_el3, %0" : : "r" (val) : "cc");

	asm volatile("isb");
}

static inline unsigned int get_sctlr(void)
{
	unsigned int el, val;

	el = current_el();
	if (el == 1)
		asm volatile("mrs %0, sctlr_el1" : "=r" (val) : : "cc");
	else if (el == 2)
		asm volatile("mrs %0, sctlr_el2" : "=r" (val) : : "cc");
	else
		asm volatile("mrs %0, sctlr_el3" : "=r" (val) : : "cc");

	return val;
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
