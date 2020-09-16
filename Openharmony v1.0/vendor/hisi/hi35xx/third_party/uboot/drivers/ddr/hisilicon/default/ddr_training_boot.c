/*
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

* Description:Special function for ddr training when power up.
*/

#include "ddr_training_impl.h"
#include "ddr_interface.h"

#ifdef DDR_TRAINING_UART_CONFIG
extern void uart_early_put_hex(int hex);
extern void uart_early_putc(int chr);
#endif

/* Save DDR tarining result */
void ddr_result_data_save(struct ddr_cfg_st *cfg, struct training_data *training)
{
	/* nothing to do when ddr training on power up */
}

void ddr_lpca_data_save(struct ca_data_st *data)
{
	/* nothing to do when ddr training on power up */
}

/* Get DDRT test address */
unsigned int ddr_ddrt_get_test_addr(void)
{
	return DDRT_CFG_TEST_ADDR_BOOT;
}

#ifdef DDR_TRAINING_UART_CONFIG
#ifdef DDR_TRAINING_MINI_LOG_CONFIG
/* Display DDR training error when boot */
void ddr_training_error(unsigned int mask, unsigned int phy, int byte, int dq)
{
	uart_early_putc('E');
	uart_early_put_hex(mask);
	uart_early_putc('P');
	uart_early_put_hex(phy);
	uart_early_putc('B');
	uart_early_put_hex(byte);
	uart_early_putc('D');
	uart_early_put_hex(dq);
}
void ddr_training_start(void)
{
	uart_early_putc('D');
	uart_early_putc('D');
	uart_early_putc('R');
}
void ddr_training_suc(void)
{
	uart_early_putc('S');
}
#else
/* Define string to print */
void ddr_training_local_str(void)
{
	asm volatile(
		"str_wl:\n\t"
		".asciz \"WL\"\n\t"
		".align 2\n\t"

		"str_hwg:\n\t"
		".asciz \"HWG\"\n\t"
		".align 2\n\t"

		"str_gate:\n\t"
		".asciz \"Gate\"\n\t"
		".align 2\n\t"

		"str_ddrt:\n\t"
		".asciz \"DDRT\"\n\t"
		".align 2\n\t"

		"str_hwrd:\n\t"
		".asciz \"HWRD\"\n\t"
		".align 2\n\t"

		"str_mpr:\n\t"
		".asciz \"MPR\"\n\t"
		".align 2\n\t"

		"str_dataeye:\n\t"
		".asciz \"Dataeye\"\n\t"
		".align 2\n\t"

		"str_lpca:\n\t"
		".asciz \"LPCA\"\n\t"
		".align 2\n\t"

		"str_err:\n\t"
		".asciz \" Err:\"\n\t"
		".align 2\n\t"

		"str_phy:\n\t"
		".asciz \"Phy\"\n\t"
		".align 2\n\t"

		"str_byte:\n\t"
		".asciz \"Byte\"\n\t"
		".align 2\n\t"

		"str_dq:\n\t"
		".asciz \"DQ\"\n\t"
		".align 2\n\t"

		"str_ddrtr_start:\n\t"
		".asciz \"\r\\nDDRTR \"\n\t"
		".align 2\n\t"

		"str_ddrtr_suc:\n\t"
		".asciz \"Suc\"\n\t"
		".align 2\n\t"
		);
}

/* Display DDR training error when boot */
void ddr_training_error(unsigned int mask, unsigned int phy, int byte, int dq)
{
	uart_early_putc('\r');
	uart_early_putc('\n');
	/* error type */
	switch (mask) {
	case DDR_ERR_WL:
		asm volatile(
				"adr	r0, str_wl\n\t"
				"bl	uart_early_puts"
			    );
		break;
	case DDR_ERR_HW_GATING:
		asm volatile(
				"adr	r0, str_hwg\n\t"
				"bl	uart_early_puts"
			    );
		break;
	case DDR_ERR_GATING:
		asm volatile(
				"adr	r0, str_gate\n\t"
				"bl	uart_early_puts"
			    );
		break;
	case DDR_ERR_DDRT_TIME_OUT:
		asm volatile(
				"adr	r0, str_ddrt\n\t"
				"bl	uart_early_puts"
			    );
		break;
	case DDR_ERR_HW_RD_DATAEYE:
		asm volatile(
				"adr	r0, str_hwrd\n\t"
				"bl	uart_early_puts"
			    );
		break;
	case DDR_ERR_MPR:
		asm volatile(
				"adr	r0, str_mpr\n\t"
				"bl	uart_early_puts"
			    );
		break;
	case DDR_ERR_DATAEYE:
		asm volatile(
				"adr	r0, str_dataeye\n\t"
				"bl	uart_early_puts"
			    );
		break;
	case DDR_ERR_LPCA:
		asm volatile(
				"adr	r0, str_lpca\n\t"
				"bl	uart_early_puts"
			    );
		break;
	default:
		break;
	}

	/* error string */
	asm volatile(
			"adr	r0, str_err\n\t"
			"bl	uart_early_puts"
		    );

	/* error phy */
	if (0 != phy) {
		asm volatile(
				"adr	r0, str_phy\n\t"
				"bl	uart_early_puts"
			    );
		uart_early_put_hex(phy);
	}

	/* error byte */
	if (-1 != byte) {
		asm volatile(
				"adr	r0, str_byte\n\t"
				"bl	uart_early_puts"
			    );
		uart_early_put_hex(byte);
	}

	/* error dq */
	if (-1 != dq) {
		asm volatile(
				"adr	r0, str_dq\n\t"
				"bl	uart_early_puts"
			    );
		uart_early_put_hex(dq);
	}
}

/* Display DDR training start when boot */
void ddr_training_start(void)
{
	asm volatile(
			"push	{lr}\n\t"
			"adr	r0, str_ddrtr_start\n\t"
			"bl	uart_early_puts\n\t"
			"pop	{lr}"
		    );
}

/* Display DDR training result when boot */
void ddr_training_suc(void)
{
	asm volatile(
			"push	{lr}\n\t"
			"adr	r0, str_ddrtr_suc\n\t"
			"bl	uart_early_puts\n\t"
			"pop	{lr}"
		    );
}
#endif /* DDR_TRAINING_CUT_CODE_CONFIG */
#else
void ddr_training_error(unsigned int mask, unsigned int phy, int byte, int dq)
{
	return;
}
void ddr_training_suc(void)
{
	return;
}
void ddr_training_start(void)
{
	return;
}
#endif /* DDR_TRAINING_UART_CONFIG */
