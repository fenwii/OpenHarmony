/*
 * pmu-ACT88430QJ101-T.c
 *
 * The PMU ACT88430QJ101-T Driver for hisilicon
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
#include "i2c.h"
#include <div64.h>
#include "hisvb.h"
#include <ddr_training_impl.h>

#define I2C_PMU_DEV_ADDR    0xb4

#define MEDIA_ADDR      0x31
#define CORE_ADDR       0x41
#define CPU_ADDR        0x51
#define DDR_ADDR        0x62

#define I2C_PMU_DEBUG 0

static void i2c_pmu_set(unsigned char addr, unsigned char value)
{
	unsigned char chip = I2C_PMU_DEV_ADDR;
	unsigned char buffer = value;
#if (I2C_PMU_DEBUG == 1)
	unsigned char read_buf;
#endif

	i2c_write(chip, addr, 1, &buffer, 1);
#if (I2C_PMU_DEBUG == 1)
	i2c_read(chip, addr, 1, &read_buf, 1);
	uart_early_putc('r');
	uart_early_putc('d');
	uart_early_putc('=');
	uart_early_put_hex((int)read_buf);
	uart_early_putc('\r');
	uart_early_putc('\n');
	uart_early_putc('\0');
#endif
}

/*
 * transfer form: val equals (voltage(mV) - 600) / 9.3;
 */
static unsigned char voltage_to_pmu_unit(unsigned int voltage)
{
	unsigned int val;
	val = (voltage - 600) * 10; /* val equals (voltage(mV) - 600) * 10 */
	val = val / 93; /* val equals (voltage(mV) - 600) * 10 / 93 */

	return (unsigned char)val;
}

/*
 * To set the target power-domain with the given voltage(mV)
 */
void pmu_voltage_set(enum power_domain domain, unsigned int voltage)
{
	unsigned char value;

	value = voltage_to_pmu_unit(voltage);

	if (domain == DOMAIN_MEDIA)
		i2c_pmu_set(MEDIA_ADDR, value);
	else if (domain == DOMAIN_CORE)
		i2c_pmu_set(CORE_ADDR, value);
	else if (domain == DOMAIN_CPU)
		i2c_pmu_set(CPU_ADDR, value);
	else if (domain == DOMAIN_DDR)
		i2c_pmu_set(DDR_ADDR, 0x18);
	else
		uart_early_putc('?');
}

void i2c_pmu_init(void)
{
#if (I2C_PMU_DEBUG == 1)
	i2c_pmu_set(0x30, 0x83);
	i2c_pmu_set(0x40, 0x83);
	i2c_pmu_set(0x50, 0x83);

	i2c_pmu_set(0x72, 0x61);
	i2c_pmu_set(0x74, 0x10);
	i2c_pmu_set(0x89, 0x14);
	i2c_pmu_set(0x61, 0x18); /* config DDR IO */
#endif
}
