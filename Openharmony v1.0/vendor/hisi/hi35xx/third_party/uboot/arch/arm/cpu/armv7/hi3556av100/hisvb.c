/*
 * hisvb.c
 *
 * The SVB Device Driver for hisilicon
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

#include "hisvb.h"
#include <asm/io.h>
#include <div64.h>
#include "pwm-voltage-ctrl.h"
#include <configs/hi3556av100.h>

#define SVB_VERSION 0x10

#define HI_PMC_CTL_REG          0x04528000
#define HPM_CORE_VOL_REG        (HI_PMC_CTL_REG + 0x60)
#define HPM_CPU_VOL_REG         (HI_PMC_CTL_REG + 0x64)
#define HPM_MDA_VOL_REG         (HI_PMC_CTL_REG + 0x68)
#define CYCLE_NUM               4
#define HPM_CPU_REG0            0x1208
#define HPM_CPU_REG1            0x120c
#define HPM_MDA_REG0            0x1228
#define HPM_MDA_REG1            0x122c
#define HPM_CORE_REG0           0x1218
#define HPM_CORE_REG1           0x121c

#define HMP_CLK_REG             0x0451019c

#define HPM_CHECK_REG           0x04520158
#define VERSION_REG             0x0452015c

#define OTP_HPM_CORE_REG        0x040b0028
#define OTP_HPM_MEDIA_REG	0x040b002c
#define OTP_HPM_CPU_REG         0x040b0034

#define TSENSOR_CTRL            0x70
#define TSENSOR_STATUS0         0X78

#define VMIN_CORE	760
#define VMAX_CORE	900

#define VMIN_CPU	       750
#define VMAX_CPU	950

#define VMIN_MEDIA	680
#define VMAX_MEDIA	845

#define FREFIX_MEDIA_VOLTAGE    900 /* 900mV */
#define FREFIX_CORE_VOLTAGE 900
#define FREFIX_CPU_VOLTAGE  900
#define FREFIX_DDR_IO_VOLTAGE   1100    /* 1100mv */

#define TEMPERATURE_MIN  (-70)
#define TEMPERATURE_MAX  150

#define HPM_CORE_MIN 300
#define HPM_CORE_MAX 480

#define HPM_CPU_MIN 300
#define HPM_CPU_MAX 480

#define HPM_MDA_MIN 300
#define HPM_MDA_MAX 480

#define temperature_formula(val) (((((val) - 116) * 210) >> 10) - 40)
#define adjust_value_formula(val) ((4835 - 154 * (val)) >> 10)
#define hpm_core_voltage(val) (1317500 - 1250 * (val))
#define hpm_media_voltage(val) (1080770 - 842 * (val))
#define hpm_cpu_voltage(val) (1389000 - 1400 * (val))

static inline void delay_cycles(unsigned int num)
{
	volatile unsigned int i;

	for (i = 0; i < (100 * num); i++) /* 100: Cycle */
		__asm__ __volatile__("nop");
}

static unsigned hpm_value_avg(const unsigned int *val, unsigned int num)
{
	unsigned int i;
	unsigned tmp = 0;

	for (i = 0; i < num; i++)
		tmp += val[i] >> 2; /* Move Right 2bit */

	return tmp >> 2; /* Move Right 2bit */
}

static void get_hpm_value(unsigned int *hpm_core,
			unsigned int *hpm_cpu, unsigned int *hpm_mda)
{
	int i;
	unsigned int temp;
	unsigned int core_value[NUM_4] = {0};
	unsigned int mda_value[NUM_4] = {0};
	unsigned int cpu_value[NUM_4] = {0};
	unsigned int mask = 0x3ff; /* 0x3ff: data mask */

	for (i = 0; i < CYCLE_NUM; i++) {
		delay_cycles(100); /* delay 100ms */

		/* cpu */
		temp = readl(HI_PMC_CTL_REG + HPM_CPU_REG0);
		cpu_value[NUM_1] += (temp >> 16) & mask; /* get hight 16 bits */
		cpu_value[NUM_0] += temp & mask;
		temp = readl(HI_PMC_CTL_REG + HPM_CPU_REG1);
		cpu_value[NUM_3] += (temp >> 16) & mask; /* get hight 16 bits */
		cpu_value[NUM_2] += temp & mask;

		/* mda */
		temp = readl(HI_PMC_CTL_REG + HPM_MDA_REG0);
		mda_value[NUM_1] += (temp >> 16) & mask; /* get hight 16 bits */
		mda_value[NUM_0] += temp & mask;
		temp = readl(HI_PMC_CTL_REG + HPM_MDA_REG1);
		mda_value[NUM_3] += (temp >> 16) & mask; /* get hight 16 bits */
		mda_value[NUM_2] += temp & mask;

		/* core */
		temp = readl(HI_PMC_CTL_REG + HPM_CORE_REG0);
		core_value[NUM_1] += (temp >> 16) & mask; /* get hight 16 bits */
		core_value[NUM_0] += temp & mask;
		temp = readl(HI_PMC_CTL_REG + HPM_CORE_REG1);
		core_value[NUM_3] += (temp >> 16) & mask; /* get hight 16 bits */
		core_value[NUM_2] += temp & mask;
	}

	*hpm_core = hpm_value_avg(core_value, NUM_4);
	*hpm_mda = hpm_value_avg(mda_value, NUM_4);
	*hpm_cpu = hpm_value_avg(cpu_value, NUM_4);
}

static void start_hpm(unsigned int *hpm_core, unsigned int *hpm_cpu,
					  unsigned int *hpm_mda)
{
	/* core */
	writel(0x60000201, HI_PMC_CTL_REG + 0x1210);

	/* mda  */
	writel(0x60000201, HI_PMC_CTL_REG + 0x1220);

	/* cpu  */
	writel(0x60000201, HI_PMC_CTL_REG + 0x1200);

	delay_cycles(500); /* delay 500ms */

	get_hpm_value(hpm_core, hpm_cpu, hpm_mda);

	*hpm_core = (unsigned int)(short)((short)(*hpm_core) +
			(short)((readl(OTP_HPM_CORE_REG) >> 16) & 0xffff)); /* Move Right 16bit */
	*hpm_mda  = (unsigned int)(short)((short)(*hpm_mda) +
			(short)((readl(OTP_HPM_MEDIA_REG) >> 16) & 0xffff)); /* Move Right 16bit */
	*hpm_cpu  = (unsigned int)(short)((short)(*hpm_cpu) +
			(short)((readl(OTP_HPM_CPU_REG) >> 16) & 0xffff)); /* Move Right 16bit */
}

/*
 * transfer form: voltage = 1307.5 - 1.25 * hpm  (mV)
 */
static unsigned int hpm_core_to_voltage(unsigned int hpm)
{
	unsigned int voltage = hpm_core_voltage(hpm);

	voltage >>= 10; /* 1000:conversion */
	voltage += 19;
	if (voltage < VMIN_CORE)
		voltage = VMIN_CORE;

	if (voltage > VMAX_CORE)
		voltage = VMAX_CORE;

	return voltage;
}

/*
 * transfer form: voltage = 1070.77 - 0.842 * hpm  (mV)
 */
static unsigned int hpm_media_to_voltage(unsigned int hpm)
{
	unsigned int voltage = hpm_media_voltage(hpm);
	int avsp_on;
	unsigned int svb_version = readl(VERSION_REG);

	voltage >>= 10; /* 1000:conversion */
	voltage += 19;

	avsp_on = ((svb_version >> 30) & 0x1); /* Move Right 30bit */
	if (avsp_on)
		voltage += 50; /* 50: Adjust the voltage */

	if (voltage < VMIN_MEDIA)
		voltage = VMIN_MEDIA;

	if (voltage > VMAX_MEDIA)
		voltage = VMAX_MEDIA;

	return voltage;
}

static unsigned int hpm_cpu_to_voltage(unsigned int hpm)
{
	unsigned int voltage = hpm_cpu_voltage(hpm);
	int intacc_on;
	unsigned int svb_version = readl(VERSION_REG);

	voltage >>= 10; /* 1000:conversion */
	voltage += 19;

	intacc_on = (svb_version >> 31) & 0x1; /* Move Right 31bit */
	if (intacc_on)
		voltage += 40; /* 40: Adjust the voltage */

	if (voltage < VMIN_CPU)
		voltage = VMIN_MEDIA;

	if (voltage > VMAX_CPU)
		voltage = VMAX_CPU;

	return voltage;
}

static void hpm_check(unsigned int *hpm_core, unsigned int *hpm_cpu,
		      unsigned int *hpm_mda, unsigned int hpm_from_otp)
{
	union {
		struct {
			unsigned int sys_hpm_mda : 9; /* [8..0] */
			unsigned int sys_hpm_cpu : 9; /* [17..9] */
			unsigned int sys_hpm_core : 9; /* [26..18] */
			unsigned int from_otp : 1; /* [27] */
			unsigned int hpm_mda_err : 1; /* [28] */
			unsigned int hpm_cpu_err : 1; /* [29] */
			unsigned int hpm_core_err : 1; /* [30] */
			unsigned int svb_56a : 1; /* [31] */
		} bits;

		unsigned int u32;
	} sysboot10;

	sysboot10.u32 = 0;

	if (*hpm_core < HPM_CORE_MIN) {
		*hpm_core = HPM_CORE_MIN;
		sysboot10.bits.hpm_core_err = 1;
	}

	if (*hpm_core > HPM_CORE_MAX) {
		*hpm_core = HPM_CORE_MAX;
		sysboot10.bits.hpm_core_err = 1;
	}

	if (*hpm_cpu < HPM_CPU_MIN) {
		*hpm_cpu = HPM_CPU_MIN;
		sysboot10.bits.hpm_cpu_err = 1;
	}

	if (*hpm_cpu > HPM_CPU_MAX) {
		*hpm_cpu = HPM_CPU_MAX;
		sysboot10.bits.hpm_cpu_err = 1;
	}

	if (*hpm_mda < HPM_MDA_MIN) {
		*hpm_mda = HPM_MDA_MIN;
		sysboot10.bits.hpm_mda_err = 1;
	}

	if (*hpm_mda > HPM_MDA_MAX) {
		*hpm_mda = HPM_MDA_MAX;
		sysboot10.bits.hpm_mda_err = 1;
	}

	sysboot10.bits.sys_hpm_core = *hpm_core;
	sysboot10.bits.sys_hpm_cpu = *hpm_cpu;
	sysboot10.bits.sys_hpm_mda = *hpm_mda;
	sysboot10.bits.from_otp = hpm_from_otp;

	sysboot10.bits.svb_56a = 1;
	writel(sysboot10.u32, HPM_CHECK_REG);
}

static void adjust_hpm(unsigned int *hpm_core, unsigned int *hpm_cpu,
		       unsigned int *hpm_mda, int temperature)
{
	int adjust_value;

	adjust_value = adjust_value_formula(temperature);

	*hpm_core -= adjust_value;
	*hpm_cpu -= adjust_value;
	*hpm_mda -= adjust_value;
}

static void get_chip_temperature(int *temperature)
{
	int value;

	value = readl(HI_PMC_CTL_REG + TSENSOR_STATUS0);
	value = value & 0x3ff; /* 0x3ff: mask */

	*temperature = temperature_formula(value);

	if (*temperature > TEMPERATURE_MAX)
		*temperature = TEMPERATURE_MAX;

	if (*temperature < TEMPERATURE_MIN)
		*temperature = TEMPERATURE_MIN;
}

/*
 * Note: the output voltages should be stable before this function returns.
 */
void svb_preset(void)
{
#define I2C_PMU_DEBUG 0
#if (I2C_PMU_DEBUG == 1)
	pmu_voltage_set(DOMAIN_MEDIA, FREFIX_MEDIA_VOLTAGE);
	pmu_voltage_set(DOMAIN_CORE, FREFIX_CORE_VOLTAGE);
	pmu_voltage_set(DOMAIN_CPU, FREFIX_CPU_VOLTAGE);
	pmu_voltage_set(DOMAIN_DDR, FREFIX_DDR_IO_VOLTAGE);
#endif
}

/*
 * Please make sure this function is called BEFORE DDR-training.
 */
void svb_start(void)
{
	unsigned int hpm_core;
	unsigned int hpm_cpu;
	unsigned int hpm_mda;
	unsigned int svb_version;
	int temperature;

	unsigned int voltage;

	/* Set SVB software version to version-reg */
	svb_version = readl(VERSION_REG);
	svb_version &= 0xff00ffff;
	svb_version |= (SVB_VERSION << 16); /* Move Left 16bit */
	writel(svb_version, VERSION_REG);

	/* hmp clock enable */
	writel(0xfff0000, HMP_CLK_REG);
	/* get hmp value from register */
	start_hpm(&hpm_core, &hpm_cpu, &hpm_mda);

	get_chip_temperature(&temperature);

	adjust_hpm(&hpm_core, &hpm_cpu, &hpm_mda, temperature);

	hpm_check(&hpm_core, &hpm_cpu, &hpm_mda, 0);

	/*
	 * Start adjust the voltage of each domain.
	 */
	voltage = hpm_core_to_voltage(hpm_core);
#ifdef I2C_PMU_ENABLE
	pmu_voltage_set(DOMAIN_CORE, voltage);
#else
	pwm_voltage_set(DOMAIN_CORE, voltage);
#endif

	voltage = hpm_media_to_voltage(hpm_mda);
#ifdef I2C_PMU_ENABLE
	pmu_voltage_set(DOMAIN_MEDIA, voltage);
#else
	pwm_voltage_set(DOMAIN_MEDIA, voltage);
#endif

	voltage = hpm_cpu_to_voltage(hpm_cpu);
#ifdef I2C_PMU_ENABLE
	pmu_voltage_set(DOMAIN_CPU, voltage);
#else
	pwm_voltage_set(DOMAIN_CPU, voltage);
#endif
	/*
	 * Need to wait for a little while after voltage adjust!
	 */
	delay_cycles(280); /* delay 280ms */
}
