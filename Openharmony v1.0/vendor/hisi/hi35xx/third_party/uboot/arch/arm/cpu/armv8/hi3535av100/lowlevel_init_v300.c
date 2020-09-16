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
 */

#include <asm/arch/platform.h>
#include <config.h>
#include <compiler.h>
#include "ddr_training_impl.h"

#define HI_SYS_CTL_REG  SYS_CTRL_REG_BASE

#define OK 0
#define ERROR -1
#define DDR_CA0_OFST        0x24
#define DDR_CA1_OFST        0x28
#define DDR_CA2_OFST        0x2c
#define REG_BASE_DDRC           0x11130000

#define DDRC_CTRL_SREF_OFST     0x8000 + 0x0
#define DDRC_CFG_DDRMODE_OFST   0x8000 + 0X50
#define DDRC_CURR_FUNC_OFST     0x8000 + 0x294

#define DDRC1_CTRL_SREF_OFST    0x9000 + 0x0
#define DDRC1_CFG_DDRMODE_OFST  0x9000 + 0X50
#define DDRC1_CURR_FUNC_OFST    0x9000 + 0x294

#define DDRC2_CTRL_SREF_OFST    0xa000 + 0x0
#define DDRC2_CFG_DDRMODE_OFST  0xa000 + 0X50
#define DDRC2_CURR_FUNC_OFST    0xa000 + 0x294

#define DDRC3_CTRL_SREF_OFST    0xb000 + 0x0
#define DDRC3_CFG_DDRMODE_OFST  0xb000 + 0X50
#define DDRC3_CURR_FUNC_OFST    0xb000 + 0x294

#define DDRC_SELF_REFURBISH_MASK    (0x1)

static inline void delay(unsigned int num)
{
	volatile unsigned int i;

	for (i = 0; i < (100 * num); i++)
		__asm__ __volatile__("nop");
}

extern void reset_cpu(unsigned long addr);

static inline void DWB(void) /* drain write buffer */
{
}

static inline unsigned int readl(unsigned addr)
{
	unsigned int val;

	val = (*(volatile unsigned int *)(uintptr_t)(addr));
	return val;
}

static inline void writel(unsigned val, unsigned addr)
{
	DWB();
	(*(volatile unsigned *)(uintptr_t)(addr)) = val;
	DWB();
}

#define REG_BASE_MISC		0x11024000

#ifdef DDR_SCRAMB_ENABLE

#undef reg_get
#define reg_get(addr) (*(volatile unsigned int *)((long)addr))

#undef reg_set
#define reg_set(addr, val) (*(volatile unsigned int *)((long)addr) = (val))
void ddr_scramb_start(unsigned int random1, unsigned int random2)
{

	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA0_OFST), random1);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA1_OFST), random2);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA2_OFST), 0);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA2_OFST), 0x10);
	delay(0x100);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA0_OFST), 0);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA1_OFST), 0);
}

#define REG_BASE_RNG_GEN		0x10130000
#define TRNG_DSTA_FIFO_DATA_OFST	0x204
#define TRNG_DATA_ST_OFST		0x208
#define HISEC_COM_TRNG_CTRL_OFST	0x200

#define BIT_TRNG_FIFO_DATA_CNT		0x8
#define TRNG_FIFO_DATA_CNT_MASK		0xff
#define TRNG_CTRL_DEF_VAL		0xa

#define REG_PERI_CRG_TRNG		0x2d80
#define TRNG_CLK_ENABLE			(0x1 << 4)
#define TRNG_DO_SRST			(0x1 << 0)
#define TRNG_CLK_DISABLE		~(0x1 << 4)
#define TRNG_UNDO_SRST			~(0x1 << 0)

/* get random number */
int get_random_num(void)
{
	unsigned int reg_val = 0;

	do {
		reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DATA_ST_OFST);

	} while (!((reg_val >> BIT_TRNG_FIFO_DATA_CNT) &
		TRNG_FIFO_DATA_CNT_MASK));

	reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DSTA_FIFO_DATA_OFST);

	return reg_val;
}

void trng_init(void)
{
	unsigned int reg_val = 0;

	/* open trng clock */
	reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG_TRNG);
	reg_val |= TRNG_CLK_ENABLE;
	reg_val &= TRNG_UNDO_SRST;
	reg_set(CRG_REG_BASE + REG_PERI_CRG_TRNG, reg_val);

	/* set trng ctrl register */
	reg_set(REG_BASE_RNG_GEN + HISEC_COM_TRNG_CTRL_OFST,
			TRNG_CTRL_DEF_VAL);
}

void trng_deinit(void)
{
	unsigned int reg_val = 0;

	/* close trng clock */
	reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG_TRNG);
	reg_val &= TRNG_CLK_DISABLE;
	reg_set(CRG_REG_BASE + REG_PERI_CRG_TRNG, reg_val);
}

int ddr_scramb(void)
{
	unsigned int random_num1 = 0;
	unsigned int random_num2 = 0;
	unsigned int reg_val[4] = {0,0,0,0};
	unsigned int ddrca_val[4] = {0, 0, 0, 0};
	unsigned int ddrc_isvalid[4] = {0,0,0,0};

	/* read ddrc_cfg_ddrmode register,
	 * if value[3:0] is not 0x0 ,the channel is valid.
	 */
	ddrc_isvalid[0] = (reg_get(REG_BASE_DDRC + DDRC_CFG_DDRMODE_OFST) & 0xf)?1:0;
	ddrc_isvalid[1] = (reg_get(REG_BASE_DDRC + DDRC1_CFG_DDRMODE_OFST)& 0xf)?1:0;
	ddrc_isvalid[2] = (reg_get(REG_BASE_DDRC + DDRC2_CFG_DDRMODE_OFST)& 0xf)?1:0;
	ddrc_isvalid[3] = (reg_get(REG_BASE_DDRC + DDRC3_CFG_DDRMODE_OFST)& 0xf)?1:0;

	/* set ddrc to do self-refurbish */
	if(ddrc_isvalid[0])
		reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, 0x1);
	if(ddrc_isvalid[1])
		reg_set(REG_BASE_DDRC + DDRC1_CTRL_SREF_OFST, 0x1);
	if(ddrc_isvalid[2])
		reg_set(REG_BASE_DDRC + DDRC2_CTRL_SREF_OFST, 0x1);
	if(ddrc_isvalid[3])
		reg_set(REG_BASE_DDRC + DDRC3_CTRL_SREF_OFST, 0x1);

	/* wait the status of ddrc to be sef-refurbish */
	do {
		reg_val[0] = ddrc_isvalid[0]?(reg_get(REG_BASE_DDRC + DDRC_CURR_FUNC_OFST) & 0x1):1;
		reg_val[1] = ddrc_isvalid[1]?(reg_get(REG_BASE_DDRC + DDRC1_CURR_FUNC_OFST) & 0x1):1;
		reg_val[2] = ddrc_isvalid[2]?(reg_get(REG_BASE_DDRC + DDRC2_CURR_FUNC_OFST) & 0x1):1;
		reg_val[3] = ddrc_isvalid[3]?(reg_get(REG_BASE_DDRC + DDRC3_CURR_FUNC_OFST) & 0x1):1;

	} while (!(reg_val[0] & reg_val[1] & reg_val[2] & reg_val[3]));


	if (ddrc_isvalid[0]) {
		ddrca_val[0] = reg_get(REG_BASE_DDRC + 0x8164);
		reg_set(REG_BASE_DDRC + 0x8184, ddrca_val[0]);

		ddrca_val[1] = reg_get(REG_BASE_DDRC + 0x8168);
		reg_set(REG_BASE_DDRC + 0x8188, ddrca_val[1]);

		ddrca_val[2] = reg_get(REG_BASE_DDRC + 0x816c);
		reg_set(REG_BASE_DDRC + 0x8048, ddrca_val[2]);
	}

	if (ddrc_isvalid[1]) {
		ddrca_val[0] = reg_get(REG_BASE_DDRC + 0x9164);
		reg_set(REG_BASE_DDRC + 0x9184, ddrca_val[0]);

		ddrca_val[1] = reg_get(REG_BASE_DDRC + 0x9168);
		reg_set(REG_BASE_DDRC + 0x9188, ddrca_val[1]);

		ddrca_val[2] = reg_get(REG_BASE_DDRC + 0x916c);
		reg_set(REG_BASE_DDRC + 0x9048, ddrca_val[2]);
	}

	if (ddrc_isvalid[2]) {
		ddrca_val[0] = reg_get(REG_BASE_DDRC + 0xa164);
		reg_set(REG_BASE_DDRC + 0xa184, ddrca_val[0]);

		ddrca_val[1] = reg_get(REG_BASE_DDRC + 0xa168);
		reg_set(REG_BASE_DDRC + 0xa188, ddrca_val[1]);

		ddrca_val[2] = reg_get(REG_BASE_DDRC + 0xa16c);
		reg_set(REG_BASE_DDRC + 0xa048, ddrca_val[2]);
	}

	if (ddrc_isvalid[3]) {
		ddrca_val[0] = reg_get(REG_BASE_DDRC + 0xb164);
		reg_set(REG_BASE_DDRC + 0xb184, ddrca_val[0]);

		ddrca_val[1] = reg_get(REG_BASE_DDRC + 0xb168);
		reg_set(REG_BASE_DDRC + 0xb188, ddrca_val[1]);

		ddrca_val[2] = reg_get(REG_BASE_DDRC + 0xb16c);
		reg_set(REG_BASE_DDRC + 0xb048, ddrca_val[2]);
	}

	trng_init();
	/* get random number */
	random_num1 = get_random_num();
	random_num2 = get_random_num();

	/* start ddr scrambling */
	ddr_scramb_start(random_num1, random_num2);

	/* clear random number */
	(void)get_random_num();
	(void)get_random_num();
	(void)get_random_num();
	(void)get_random_num();
	trng_deinit();

	/* set ddrc to exit self-refurbish */
	if(ddrc_isvalid[0])
		reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, (0x1<<1));
	if(ddrc_isvalid[1])
		reg_set(REG_BASE_DDRC + DDRC1_CTRL_SREF_OFST, (0x1<<1));
	if(ddrc_isvalid[2])
		reg_set(REG_BASE_DDRC + DDRC2_CTRL_SREF_OFST, (0x1<<1));
	if(ddrc_isvalid[3])
		reg_set(REG_BASE_DDRC + DDRC3_CTRL_SREF_OFST, (0x1<<1));

	/* wait the status of ddrc to be normal */
	do {
		reg_val[0] = ddrc_isvalid[0]?(reg_get(REG_BASE_DDRC + DDRC_CURR_FUNC_OFST) & 0x1):0;
		reg_val[1] = ddrc_isvalid[1]?(reg_get(REG_BASE_DDRC + DDRC1_CURR_FUNC_OFST) & 0x1):0;
		reg_val[2] = ddrc_isvalid[2]?(reg_get(REG_BASE_DDRC + DDRC2_CURR_FUNC_OFST) & 0x1):0;
		reg_val[3] = ddrc_isvalid[3]?(reg_get(REG_BASE_DDRC + DDRC3_CURR_FUNC_OFST) & 0x1):0;
	} while (reg_val[0] | reg_val[1] | reg_val[2] | reg_val[3]);

	return OK;
}

#endif /* DDR_SCRAMB_ENABLE */

#define HPM_CORE_VOL_REG		0x11029000
#define HPM_CPU_VOL_REG			0x11029004

#define HMP_CLK_REG			0x11014A80
#define CPU_HPM_CTRL0_REG		0x1102B000
#define CORE_HPM_CTRL0_REG		0x1102B010
#define HPM_CPU_REG0			0x1102B008
#define HPM_CPU_REG1			0x1102B00c
#define HPM_CORE_REG0			0x1102B018
#define HPM_CORE_REG1			0x1102B01c
#define CYCLE_NUM			32
#define SVB_RECORD_REG0			0x11020340
#define SVB_RECORD_REG1			0x11020344

#define VOLTAGE_RECOED_REG		0x1102015C
#define SVB_VERSION_REG			0x11020168
#define SVB_VERSION			0x101
#define OTP_HPM_CORE_REG		0x11021504
#define OTP_HPM_CPU_REG			0x11021530
#define OTP_VOLTAGE_DELTA_CORE_REG	0x1102150C
#define OTP_VOLTAGE_DELTA_CPU_REG	0x11021518

#define TSENSOR_STATUS0			0X1102A008

static unsigned hpm_value_avg(unsigned int *val, unsigned int num)
{
	unsigned int i;
	unsigned tmp = 0;

	for (i = 0; i < num; i++)
		tmp += val[i] >> 2;

	return tmp >> 5;
}

static void get_hpm_value(unsigned int *hpm_core, unsigned int *hpm_cpu)
{
	int i;
	unsigned int temp;
	unsigned int core_value[4];
	unsigned int cpu_value[4];

	core_value[0] = 0;
	core_value[1] = 0;
	core_value[2] = 0;
	core_value[3] = 0;

	cpu_value[0] = 0;
	cpu_value[1] = 0;
	cpu_value[2] = 0;
	cpu_value[3] = 0;

	for (i = 0; i < CYCLE_NUM; i++) {
		delay(24);

		/* cpu */
		temp = readl(HPM_CPU_REG0);
		cpu_value[1] += (temp >> 16) & 0x3ff;
		cpu_value[0] += temp & 0x3ff;
		temp = readl(HPM_CPU_REG1);
		cpu_value[3] += (temp >> 16) & 0x3ff;
		cpu_value[2] += temp & 0x3ff;

		/* core */
		temp = readl(HPM_CORE_REG0);
		core_value[1] += (temp >> 16) & 0x3ff;
		core_value[0] += temp & 0x3ff;
		temp = readl(HPM_CORE_REG1);
		core_value[3] += (temp >> 16) & 0x3ff;
		core_value[2] += temp & 0x3ff;
	}

	*hpm_core = hpm_value_avg(core_value,4);
	*hpm_cpu = hpm_value_avg(cpu_value, 4);
}


static void start_hpm(unsigned int *hpm_core, unsigned int *hpm_cpu)
{
	/* core */
	writel(0x60080001, CORE_HPM_CTRL0_REG);//0x60000201
	/* cpu  */
	writel(0x60080001, CPU_HPM_CTRL0_REG);

	delay(240); /*10ms*/

	get_hpm_value(hpm_core, hpm_cpu);
}

static void hpm_check(unsigned int *hpm_core, unsigned int *hpm_cpu,
			int *temperature, unsigned int hpm_from_otp)
{
	union {
		struct {
			unsigned int sys_hpm_core : 9; /* [8..0]*/
			unsigned int reserved_0   : 7; /* [15..9]*/
			unsigned int sys_hpm_cpu  : 9; /* [24..16]*/
			unsigned int reserved_1   : 7; /* [31..25]*/
		} bits;
		unsigned int u32;
	} hpm_reg0; /*SVB_RECORD_REG0 0x11020340*/

	union {
		struct {
			signed char  temperature   : 8;		/* [7..0]*/
			unsigned int reserved_0    : 20;	/* [27..8]*/
			unsigned int temperature_err : 1;	/* [28]*/
			unsigned int hpm_cpu_err   : 1;		/* [29]*/
			unsigned int hpm_core_err  : 1;		/* [30]*/
			unsigned int from_otp      : 1;		/* [31]*/
		} bits;
		unsigned int u32;
	} hpm_reg1;	/*SVB_RECORD_REG1 0x11020344*/

	hpm_reg0.u32 = 0;
	hpm_reg1.u32 = 0;

	if (*hpm_core < 200) {
		*hpm_core = 200;
		hpm_reg1.bits.hpm_core_err = 1;
	}

	if (*hpm_core > 300) {
		*hpm_core = 300;
		hpm_reg1.bits.hpm_core_err = 1;
	}

	if (*hpm_cpu < 240) {
		*hpm_cpu = 240;
		hpm_reg1.bits.hpm_cpu_err = 1;
	}

	if (*hpm_cpu > 330) {
		*hpm_cpu = 330;
		hpm_reg1.bits.hpm_cpu_err = 1;
	}

	if (*temperature < -40) {
		*temperature = -40;
		hpm_reg1.bits.temperature_err = 1;
	}

	if (*temperature > 110) {
		*temperature = 110;
		hpm_reg1.bits.temperature_err = 1;
	}

	hpm_reg0.bits.sys_hpm_core = *hpm_core;
	hpm_reg0.bits.sys_hpm_cpu = *hpm_cpu;
	hpm_reg1.bits.temperature  = (signed char) *temperature;
	hpm_reg1.bits.from_otp     = hpm_from_otp;
	writel(hpm_reg0.u32, SVB_RECORD_REG0);
	writel(hpm_reg1.u32, SVB_RECORD_REG1);
}

static void voltage_check(double *pcore_mv, double *pcpu_mv, double core_delta_mv)
{
	short otp_voltage_delta_core;
	short otp_voltage_delta_cpu;

	union {
		struct {
			unsigned int voltage_core : 12; /* [11..0]*/
			unsigned int voltage_cpu  : 12; /* [23..12]*/
			unsigned int delta_core   : 8; /* [31..24]*/
		} bits;
		unsigned int u32;
	} voltage_reg;

	otp_voltage_delta_core = (short)(readl(OTP_VOLTAGE_DELTA_CORE_REG) & 0xffff);
	otp_voltage_delta_cpu = (short)(readl(OTP_VOLTAGE_DELTA_CPU_REG) & 0xffff);

	*pcore_mv += (double)otp_voltage_delta_core;
	*pcpu_mv  += (double)otp_voltage_delta_cpu;

	voltage_reg.u32 = 0;
	voltage_reg.bits.voltage_core = (unsigned int)*pcore_mv;
	voltage_reg.bits.voltage_cpu  = (unsigned int)*pcpu_mv;
	voltage_reg.bits.delta_core   = (unsigned int)core_delta_mv;

	writel(voltage_reg.u32, VOLTAGE_RECOED_REG);

}

static void set_hpm_core_volt(double mv)
{
	unsigned int svb_value;

	svb_value = ((unsigned int)((1078000 - mv * 1000) * 84) & 0xffff0000) + 0x19f5;

	writel(svb_value, HPM_CORE_VOL_REG);
}

static void set_hpm_cpu_volt(double mv)
{
	unsigned int svb_value;

	svb_value = ((unsigned int)((1078000 - mv * 1000) * 84) & 0xffff0000) + 0x19f5;

	writel(svb_value, HPM_CPU_VOL_REG);
}


static void get_temperature(int *temperature)
{
	int value = 0;

	value = (int)(readl(TSENSOR_STATUS0) & 0x3ff);
	*temperature = (int)(((value - 127) * 165) / 784.0 ) - 40;
}

static void get_ate_hpm(unsigned int *pate_hpm_core, unsigned int *pate_hpm_cpu)
{
	*pate_hpm_core = (unsigned int)(readl(OTP_HPM_CORE_REG) & 0xffff);
	*pate_hpm_cpu  = (unsigned int)(readl(OTP_HPM_CPU_REG) & 0xffff);
}

static void start_svb(double *pcore_mv, double *pcpu_mv)
{
	unsigned int ate_hpm_core;
	unsigned int ate_hpm_cpu;
	unsigned int hpm_core;
	unsigned int hpm_cpu;
	int temperature_delta;
	double core_delta_mv;
	int temperature;
	unsigned int hpm_from_otp;
	unsigned int version;

	version = readl(SVB_VERSION_REG);
	version = (version & 0x0000FFFF) | (SVB_VERSION << 16);
	writel(version, SVB_VERSION_REG);

	get_temperature(&temperature);
	get_ate_hpm(&ate_hpm_core,&ate_hpm_cpu);

	if ((!ate_hpm_core) || (!ate_hpm_cpu)) {
    	set_hpm_core_volt(900);
    	set_hpm_cpu_volt(1000);

		/* open hmp clock */
		writel(0x10, HMP_CLK_REG);
		start_hpm(&hpm_core, &hpm_cpu);
		hpm_from_otp = 0;
	} else {
		/*ATE SVB transfer to board SVB*/
		hpm_core = ate_hpm_core - 5;
		hpm_cpu = ate_hpm_cpu - 12;
		hpm_from_otp = 1;
	}

	hpm_check(&hpm_core, &hpm_cpu, &temperature, hpm_from_otp);

	/******************************** CORE ********************************/
	*pcore_mv = 1330 - 1.533 * hpm_core;
	temperature_delta = 110 - temperature;
	if (temperature_delta > 85)
		temperature_delta = 85;
	core_delta_mv = ((((double)hpm_core - 200) / 3.3) + 30.0) * ((double)temperature_delta / 85.0);
	/******************************** CPU *********************************/
	*pcpu_mv = 1728.384 - 2.545 * hpm_cpu; /*svb001*/
	if (*pcpu_mv > 1050)
		*pcpu_mv = 1050;
	if (*pcpu_mv < 910)
		*pcpu_mv = 910;

	voltage_check(pcore_mv, pcpu_mv, core_delta_mv);
	set_hpm_core_volt(*pcore_mv - core_delta_mv);
	set_hpm_cpu_volt(*pcpu_mv);

	/* delay 10ms do not delete */
	delay(240);
}

static void end_svb(const double *pcore_mv,const double *pcpu_mv)
{
	set_hpm_core_volt(*pcore_mv);

	/* delay 10ms do not delete */
	delay(120);
}

void start_ddr_training(unsigned int base)
{
	double core_mv;
	double cpu_mv;

	start_svb(&core_mv, &cpu_mv);

	/* ddr hw training */
	ddr_hw_training_if();

	/* ddr sw training */
	ddr_sw_training_if();

	/*the value should config after trainning, or
	  it will cause chip compatibility problems */
	if ((readl(DDR_REG_BASE_PHY0 + DDR_PHY_DRAMCFG)
		& PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
		writel(0x401, DDR_REG_BASE_DMC0 + 0x28);
		writel(0x401, DDR_REG_BASE_DMC1 + 0x28);
	} else
		writel(0x401, DDR_REG_BASE_DMC0 + 0x28);

	if ((readl(DDR_REG_BASE_PHY1 + DDR_PHY_DRAMCFG)
		& PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
		writel(0x401, DDR_REG_BASE_DMC2 + 0x28);
		writel(0x401, DDR_REG_BASE_DMC3 + 0x28);
	} else
		writel(0x401, DDR_REG_BASE_DMC1 + 0x28);

#ifdef DDR_SCRAMB_ENABLE
	/* enable ddr scramb */
	ddr_scramb();
#endif

	end_svb(&core_mv, &cpu_mv);
}
