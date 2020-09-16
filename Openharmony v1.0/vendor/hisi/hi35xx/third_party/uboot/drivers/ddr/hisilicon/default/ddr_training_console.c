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

 * Description:DDR training console
 */

#include "ddr_interface.h"
#include "ddr_training_impl.h"

#define __ddr_training_console__
#ifdef DDR_TRAINING_CONSOLE_CONFIG

#define DDR_UART_BASE_REG               0x12090000
#define UART_PL01x_FR                   0x18	 /*  Flag register (Read only). */
#define UART_PL01x_FR_RXFE              0x10
#define UART_PL01x_DR                   0x00	 /*  Data read or written from the interface. */
#define UART_PL01x_ECR                  0x04	 /*  Error clear register (Write). */

#define isprint(c)  ((c) >= ' ' && (c) <= '~')
#define isspace(c)  ((c) == ' ' || ((c) >= '\t' && (c) <= '\r'))
#define isdigit(c)  ((c) >= '0' && (c) <= '9')
#define isxdigit(c)	(isdigit(c) \
			  || ((c) >= 'A' && (c) <= 'F') \
			  || ((c) >= 'a' && (c) <= 'f'))
#define CMD(_p, _c0, _c1, _do_cmd) \
	if (_p[0] == _c0 && _p[1] == _c1) { \
		if (!_do_cmd(_p + 2)) \
			continue; \
	}

/* DDR console get char */
static int ddr_console_getc(void)
{
	unsigned int data;

	/* Wait until there is data in the FIFO */
	while (ddr_read(DDR_UART_BASE_REG + UART_PL01x_FR) & UART_PL01x_FR_RXFE) {
	}

	data = ddr_read(DDR_UART_BASE_REG + UART_PL01x_DR);

	/* Check for an error flag */
	if (data & 0xFFFFFF00) {
		/* Clear the error */
		ddr_write(0xFFFFFFFF, DDR_UART_BASE_REG + UART_PL01x_ECR);
		return -1;
	}
	return (int) data;
}

/* DDR read line */
static char *ddr_readline(char *str, int len)
{
	unsigned int c;
	char *p = str;
	while (len > 0) {
		c = ddr_console_getc();
		switch (c) {
		case '\r':
		case '\n':
			*p = '\0';
			DDR_PUTC('\r');
			DDR_PUTC('\n');
			return str;
		case 0x08:
		case 0x7F:
			if (p > str) {
				p--;
				len++;
				DDR_PUTC('\b');
				DDR_PUTC(' ');
				DDR_PUTC('\b');
			}
			break;
		default:
			if (isprint(c)) {
				(*p++) = (char)c;
				len--;
				DDR_PUTC(c);
			}
			break;
		}
	}
	(*--p) = '\0';
	return str;
}

/* HEX to INT */
static int hex2int(char **ss, unsigned int *n)
{
	unsigned char *s = (unsigned char *)(*ss);

	while (isspace(*s)) s++;

	if (!(*s))
		return -1;

	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		s += 2;

	for ((*n) = 0; isxdigit(*s); s++) {
		(*n) = ((*n) << 4);
		if ((*s) >= '0' && (*s) <= '9')
			(*n) |= ((*s) - '0');
		else if ((*s) >= 'a' && (*s) <= 'f')
			(*n) |= ((*s) + 10 - 'a');
		else if ((*s) >= 'A' && (*s) <= 'F')
			(*n) |= ((*s) + 10 - 'A');
	}

	if (isspace(*s) || !(*s)) {
		while (isspace(*s)) s++;
		(*ss) = (char *)s;
		return 0;
	}

	return -2;
}
/**
 * DDR do memory write.
 * mw address value [count]
 */
static int ddr_do_memory_write(char *cmd)
{
	unsigned int address;
	unsigned int value;
	unsigned int count = 4;

	if (hex2int(&cmd, &address))
		return -1;

	if (hex2int(&cmd, &value))
		return -1;

	if ((*cmd) && hex2int(&cmd, &count))
		return -1;

	if (address & 0x03 || count & 0x03) {
		DDR_INFO("parameter should align with 4 bytes.\n");
		return -1;
	}
	for (;count > 0; count -= 4, address += 4)
		ddr_write(value, address);
	return 0;
}
/**
 * DDR do memory display.
 * md address [count]
 */
static int ddr_do_memory_display(char *cmd)
{
	unsigned int ix;
	unsigned int loop;
	unsigned int address;
	unsigned int count = 64;

	if (hex2int(&cmd, &address))
		return -1;

	if ((*cmd) && hex2int(&cmd, &count))
		return -1;

	if (count < 4)
		count = 4;

	address &= ~0x03;
	loop = (count & ~0x03);

	while (loop > 0) {

		DDR_PUTC('0');
		DDR_PUTC('x');
		DDR_PUT_HEX(address);
		DDR_PUTC(':');

		for (ix = 0;
			ix < 4 && loop > 0;
			ix++, loop -= 4, address += 4) {

			DDR_PUTC(' '); DDR_PUT_HEX(ddr_read(address));
		}
		DDR_PUTC('\r');
		DDR_PUTC('\n');
	}
	return 0;
}

#ifdef DDR_TRAINING_CMD
extern struct ddr_training_result_st ddrt_result_sram;
#endif
static int ddr_do_sw_training(char *cmd)
{
	int result;
	struct ddr_cfg_st ddr_cfg;
	struct ddr_cfg_st *cfg = &ddr_cfg;

	ddr_training_cfg_init(cfg);
#ifdef DDR_TRAINING_CMD
	cfg->res_st = (void *)&ddrt_result_sram;
#endif
	result = ddr_training_all(cfg);

	result += ddr_dcc_training_func(cfg);

	return 0;
}

static int ddr_do_hw_training(char *cmd)
{
	int result;

	result = ddr_hw_training_func();

	return 0;
}

/* Do DDR training console if sw training or hw training fail */
static int ddr_training_console(void *args)
{
	char str[256];
	char *p = NULL;
	unsigned int cmd=0;

	while (1) {
		DDR_PUTC('d');
		DDR_PUTC('d');
		DDR_PUTC('r');
		DDR_PUTC('#');

		p = ddr_readline(str, sizeof(str));

		while (isspace(*p)) p++;
		if (p[0] == 'q')
			break;
		CMD(p, 'm', 'w', ddr_do_memory_write) else
		CMD(p, 'm', 'd', ddr_do_memory_display) else
		CMD(p, 's', 'w', ddr_do_sw_training) else
		CMD(p, 'h', 'w', ddr_do_hw_training)

	}

	return 0;
}
#else
static int ddr_training_console(void *args)
{
	DDR_WARNING("Not support DDR training console.");
	return 0;
}
#endif /* DDR_TRAINING_CONSOLE_CONFIG */

int ddr_training_console_if(void *args)
{
	return DDR_TRAINING_CONSOLE(args);
}
