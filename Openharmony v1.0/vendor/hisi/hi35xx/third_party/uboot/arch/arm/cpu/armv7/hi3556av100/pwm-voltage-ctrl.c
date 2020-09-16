/*
 * pwm-voltage-ctrl.c
 *
 * This file functions PWM voltage control file.
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
#include "pwm-voltage-ctrl.h"

#define HI_PMC_CTL_REG      0x04528000

#define PMC_VOLT_CORE_REG   (HI_PMC_CTL_REG + 0x60)
#define PMC_VOLT_CPU_REG    (HI_PMC_CTL_REG + 0x64)
#define PMC_VOLT_MEDIA_REG  (HI_PMC_CTL_REG + 0x68)

#define core_voltage(val) ((943000 - (val) * 1000) * 80)
#define cpu_voltage(val) ((1000000 - (val) * 1000) * 68)
#define media_voltage(val) ((943000 - (val) * 1000) * 80)

unsigned int core_voltage_to_svb_unit(unsigned int voltage)
{
	unsigned int value = core_voltage(voltage);
	value &= 0xffff0000;
	value += 0x19f5; /* 0x19f5:Value Added */
	return value;
}

unsigned int cpu_voltage_to_svb_unit(unsigned int voltage)
{
	unsigned int value = cpu_voltage(voltage);
	value &= 0xffff0000;
	value += 0x19f5; /* 0x19f5:Value Added */
	return value;
}

unsigned int media_voltage_to_svb_unit(unsigned int voltage)
{
	unsigned int value = media_voltage(voltage);
	value &= 0xffff0000;
	value += 0x19f5; /* 0x19f5:Value Added */
	return value;
}

void pwm_voltage_set(enum power_domain domain, unsigned int voltage)
{
	unsigned int value;

	switch (domain) {
	case DOMAIN_MEDIA:
		value = media_voltage_to_svb_unit(voltage);
		writel(value, PMC_VOLT_MEDIA_REG);
		break;
	case DOMAIN_CORE:
		value = core_voltage_to_svb_unit(voltage);
		writel(value, PMC_VOLT_CORE_REG);
		break;
	case DOMAIN_CPU:
		value = cpu_voltage_to_svb_unit(voltage);
		writel(value, PMC_VOLT_CPU_REG);
		break;
	case DOMAIN_DDR:
		break;
	case DOMAIN_GPU:
		break;
	default:
		break;
	}

	/* all done, need to wait? */
}
