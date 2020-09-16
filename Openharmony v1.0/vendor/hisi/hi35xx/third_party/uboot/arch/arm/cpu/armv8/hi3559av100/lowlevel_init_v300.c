/*
 * lowlevel_init_v300.c
 *
 * The file is Hardware initialization.
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
#include <config.h>
#include "ddr_interface.h"

#define HI_SYS_CTL_REG  SYS_CTRL_REG_BASE

#define OK 0
#define ERROR (-1)
#define DDR_CA0_OFST        0x88
#define DDR_CA1_OFST        0x8c
#define DDR_CA2_OFST        0x90
#define REG_BASE_DDRC           0x12060000

#define DDRC_CTRL_SREF_OFST     (0x8000 + 0x0)
#define DDRC_CFG_DDRMODE_OFST   (0x8000 + 0X50)
#define DDRC_CURR_FUNC_OFST     (0x8000 + 0x294)

#define DDRC1_CTRL_SREF_OFST    (0x9000 + 0x0)
#define DDRC1_CFG_DDRMODE_OFST  (0x9000 + 0X50)
#define DDRC1_CURR_FUNC_OFST    (0x9000 + 0x294)

#define DDRC2_CTRL_SREF_OFST    (0xa000 + 0x0)
#define DDRC2_CFG_DDRMODE_OFST  (0xa000 + 0X50)
#define DDRC2_CURR_FUNC_OFST    (0xa000 + 0x294)

#define DDRC3_CTRL_SREF_OFST    (0xb000 + 0x0)
#define DDRC3_CFG_DDRMODE_OFST  (0xb000 + 0X50)
#define DDRC3_CURR_FUNC_OFST    (0xb000 + 0x294)

#define DDRC_SELF_REFURBISH_MASK    0x1

/* [CUSTOM] DDR DMC0-DMC3 base register */
#define DDR_REG_BASE_DMC0       0x12068000
#define DDR_REG_BASE_DMC1       0x12069000
#define DDR_REG_BASE_DMC2       0x1206a000
#define DDR_REG_BASE_DMC3       0x1206b000
/* [CUSTOM] DDR PHY0-PHY1 base register */
#define DDR_REG_BASE_PHY0       0x1206c000
#define DDR_REG_BASE_PHY1       0x1206e000

#define DDR_PHY_DRAMCFG     0x2c    /* DRAM config register */
#define PHY_DRAMCFG_TYPE_MASK   0xf /* [3:0] */
#define PHY_DRAMCFG_TYPE_LPDDR4 0x6   /* [2:0] 110 LPDDR4 */
static inline void delay(unsigned int num)
{
	volatile unsigned int i;

	for (i = 0; i < (100 * num); i++) /* 100: Cycle */
		__asm__ __volatile__("nop");
}

static inline void dwb(void) /* drain write buffer */
{
}

static inline unsigned int readl(unsigned addr)
{
	unsigned int val;

	val = (*(volatile unsigned int *)(long)(addr));
	return val;
}

static inline void writel(unsigned val, unsigned addr)
{
	dwb();
	(*(volatile unsigned *)(long)(addr)) = (val);
	dwb();
}

#define REG_BASE_MISC       0x12030000
#ifdef DDR_SCRAMB_ENABLE

#define MISC_CTRL104_OFST   0x104
#define MISC_CTRL108_OFST   0x108
#define MISC_CTRL10C_OFST   0x10c

#define DDRC_0_CTRL_SREF_OFST   (0x8000 + 0x0)
#define DDRC_0_CURR_FUNC_OFST   (0x8000 + 0x294)
#define DDRC_1_CTRL_SREF_OFST   (0x9000 + 0x0)
#define DDRC_1_CURR_FUNC_OFST   (0x9000 + 0x294)
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
	delay(0x100);  /* delay 0x100 Cycle */
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA0_OFST), 0);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA1_OFST), 0);
}

#define REG_BASE_RNG_GEN        0x10230000
#define TRNG_DSTA_FIFO_DATA_OFST    0x204
#define TRNG_DATA_ST_OFST       0x208
#define HISEC_COM_TRNG_CTRL_OFST    0x200
#define REG_PERI_CRG101     0x0194

#define BIT_TRNG_FIFO_DATA_CNT      0x8
#define TRNG_FIFO_DATA_CNT_MASK     0xff
#define TRNG_CTRL_DEF_VAL       0xa

#define TRNG_CLK_ENABLE     (0x1 << 13)
#define TRNG_DO_SRST        (0x1 << 12)
#define TRNG_CLK_DISABLE    ~(0x1 << 13)
#define TRNG_UNDO_SRST      ~(0x1 << 12)


/* get random number */
int get_random_num(void)
{
	unsigned int reg_val;

	do {
		reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DATA_ST_OFST);
	} while (!((reg_val >> BIT_TRNG_FIFO_DATA_CNT) &
				 TRNG_FIFO_DATA_CNT_MASK));

	reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DSTA_FIFO_DATA_OFST);

	return reg_val;
}

void trng_init(void)
{
	unsigned int reg_val;
	/* open rsa and trng clock */
	reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG101);
	reg_val |= TRNG_CLK_ENABLE;
	reg_set(CRG_REG_BASE + REG_PERI_CRG101, reg_val);

	/* set trng ctrl register */
	reg_set(REG_BASE_RNG_GEN + HISEC_COM_TRNG_CTRL_OFST,
			TRNG_CTRL_DEF_VAL);
}

void trng_deinit(void)
{
	unsigned int reg_val;

	/* close rsa and trng clock */
	reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG101);
	reg_val &= TRNG_CLK_DISABLE;
	reg_set(CRG_REG_BASE + REG_PERI_CRG101, reg_val);
}

int ddr_scramb(void)
{
	unsigned int random_num1;
	unsigned int random_num2;
	unsigned int reg_val[NUM_4] = {0, 0, 0, 0};
	unsigned int ddrc_isvalid[NUM_4] = {0, 0, 0, 0};

	/* read ddrc_cfg_ddrmode register,
	 * if value[3:0] is not 0x0 ,the channel is valid.
	 */
	ddrc_isvalid[NUM_0] =
		(reg_get(REG_BASE_DDRC + DDRC_CFG_DDRMODE_OFST) & 0xf) ? 1 : 0;
	ddrc_isvalid[NUM_1] =
		(reg_get(REG_BASE_DDRC + DDRC1_CFG_DDRMODE_OFST) & 0xf) ? 1 : 0;
	ddrc_isvalid[NUM_2] =
		(reg_get(REG_BASE_DDRC + DDRC2_CFG_DDRMODE_OFST) & 0xf) ? 1 : 0;
	ddrc_isvalid[NUM_3] =
		(reg_get(REG_BASE_DDRC + DDRC3_CFG_DDRMODE_OFST) & 0xf) ? 1 : 0;

	/* set ddrc to do self-refurbish */
	if (ddrc_isvalid[NUM_0])
		reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, 0x1);

	if (ddrc_isvalid[NUM_1])
		reg_set(REG_BASE_DDRC + DDRC1_CTRL_SREF_OFST, 0x1);

	if (ddrc_isvalid[NUM_2])
		reg_set(REG_BASE_DDRC + DDRC2_CTRL_SREF_OFST, 0x1);

	if (ddrc_isvalid[NUM_3])
		reg_set(REG_BASE_DDRC + DDRC3_CTRL_SREF_OFST, 0x1);

	/* wait the status of ddrc to be sef-refurbish */
	do {
		reg_val[NUM_0] = ddrc_isvalid[NUM_0] ? (reg_get(REG_BASE_DDRC +
						DDRC_CURR_FUNC_OFST) & 0x1) : 1;
		reg_val[NUM_1] = ddrc_isvalid[NUM_1] ? (reg_get(REG_BASE_DDRC +
						DDRC1_CURR_FUNC_OFST) & 0x1) : 1;
		reg_val[NUM_2] = ddrc_isvalid[NUM_2] ? (reg_get(REG_BASE_DDRC +
					 	DDRC2_CURR_FUNC_OFST) & 0x1) : 1;
		reg_val[NUM_3] = ddrc_isvalid[NUM_3] ? (reg_get(REG_BASE_DDRC +
					 	DDRC3_CURR_FUNC_OFST) & 0x1) : 1;
	} while (!(reg_val[NUM_0] & reg_val[NUM_1] & reg_val[NUM_2] & reg_val[NUM_3]));

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
	if (ddrc_isvalid[NUM_0])
		reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, (0x1 << 1));

	if (ddrc_isvalid[NUM_1])
		reg_set(REG_BASE_DDRC + DDRC1_CTRL_SREF_OFST, (0x1 << 1));

	if (ddrc_isvalid[NUM_2])
		reg_set(REG_BASE_DDRC + DDRC2_CTRL_SREF_OFST, (0x1 << 1));

	if (ddrc_isvalid[NUM_3])
		reg_set(REG_BASE_DDRC + DDRC3_CTRL_SREF_OFST, (0x1 << 1));

	/* wait the status of ddrc to be normal */
	do {
		reg_val[NUM_0] = ddrc_isvalid[NUM_0] ? (reg_get(REG_BASE_DDRC +
					 	DDRC_CURR_FUNC_OFST) & 0x1) : 0;
		reg_val[NUM_1] = ddrc_isvalid[NUM_1] ? (reg_get(REG_BASE_DDRC +
					 	DDRC1_CURR_FUNC_OFST) & 0x1) : 0;
		reg_val[NUM_2] = ddrc_isvalid[NUM_2] ? (reg_get(REG_BASE_DDRC +
					 	DDRC2_CURR_FUNC_OFST) & 0x1) : 0;
		reg_val[NUM_3] = ddrc_isvalid[NUM_3] ? (reg_get(REG_BASE_DDRC +
					 	DDRC3_CURR_FUNC_OFST) & 0x1) : 0;
	} while (reg_val[NUM_0] | reg_val[NUM_1] | reg_val[NUM_2] | reg_val[NUM_3]);

	return OK;
}

#endif /* DDR_SCRAMB_ENABLE */

#ifdef SVB_ENABLE

#define HI_PMC_CTL_REG      0x12030000
#define HPM_CORE_VOL_REG    (HI_PMC_CTL_REG + 0x60)
#define HPM_GPU_VOL_REG     (HI_PMC_CTL_REG + 0x64)
#define HPM_MDA_VOL_REG     (HI_PMC_CTL_REG + 0x68)
#define HPM_CPU_VOL_REG     (HI_PMC_CTL_REG + 0x6c)
#define CYCLE_NUM       8
#define HPM_CPU_REG0    0x1208
#define HPM_CPU_REG1    0x120c
#define HPM_MDA_REG0    0x1218
#define HPM_MDA_REG1    0x121c
#define HPM_GPU_REG0    0x1228
#define HPM_GPU_REG1    0x122C
#define HPM_CORE_REG0   0x1238
#define HPM_CORE_REG1   0x123c

#define HMP_CLK_REG     0x1201019c
#define CPU_ISO_REG     0x1d821104

#define TSENSOR_CTRL    0x70
#define TSENSOR_STATUS0 0X78

#define OTP_CPU_IF_REG       0x10250000
#define OTP_HPM_CORE_OFFSET  0x0028
#define OTP_HPM_MDA_OFFSET   0x002c
#define OTP_HPM_GPU_OFFSET   0x0030
#define OTP_HPM_CPU_OFFSET   0x0034
#define OTP_IDDQ_SENSORHUB_OFFSET     0x004c

#define SYSCTRL_BASE_REG     0x12020000
#define HPM_CORE_STORAGE_REG 0x300
#define HPM_MDA_STORAGE_REG  0x304
#define HPM_GPU_STORAGE_REG  0x308
#define HPM_CPU_STORAGE_REG  0x30c


/* physical max/min */
#define CORE_VOLT_MAX    943
#define CORE_VOLT_MIN    603

#define MDA_VOLT_MAX     935
#define MDA_VOLT_MIN     603

#define GPU_VOLT_MAX     943
#define GPU_VOLT_MIN     603

#define CPU_VOLT_MAX     1078
#define CPU_VOLT_MIN     597


/* curve max/min; voltage curve:  v = (b - a * hpm)/10 */
#define CORE_CURVE_VLOT_MAX    900
#define CORE_CURVE_VLOT_MIN    840
#define CORE_CURVE_B           13200
#define CORE_CURVE_A           12

#define MEDIA_CURVE_VLOT_MAX   880
#define MEDIA_CURVE_VLOT_MIN   780
#define MEDIA_CURVE_B          12210
#define MEDIA_CURVE_A          11

#define GPU_CURVE_VLOT_MAX     950
#define GPU_CURVE_VLOT_MIN     858
#define GPU_CURVE_B            14180
#define GPU_CURVE_A            14

#define CPU_CURVE_VLOT_MAX     988
#define CPU_CURVE_VLOT_MIN     888
#define CPU_CURVE_B            15180
#define CPU_CURVE_A            14

#define temperature_formula(val)  (((((val) - 116) * 165) / 806) - 40)
#define duty_formula(max, min, val) (((max - val) * 416 + \
				 (max - min + 1) / 2) / (max - min) - 1)
#define volt_regval_formula(val) (((val) << 16) + ((416 - 1) << 4) + 0x5)

static unsigned hpm_value_avg(unsigned int *val, unsigned int num)
{
	unsigned int i;
	unsigned tmp = 0;

	for (i = 0; i < num; i++)
		tmp += val[i];

	return (tmp / CYCLE_NUM) >> NUM_2;
}

static void get_hpm_value(unsigned int *hpm_core, unsigned int *hpm_cpu,
				unsigned int *hpm_gpu, unsigned int *hpm_mda)
{
	int i;
	unsigned int temp;
	unsigned int core_value[NUM_4] = {0, 0, 0, 0};
	unsigned int mda_value[NUM_4] = {0, 0, 0, 0};
	unsigned int cpu_value[NUM_4] = {0, 0, 0, 0};
	unsigned int gpu_value[NUM_4] = {0, 0, 0, 0};

	for (i = 0; i < CYCLE_NUM; i++) {
		/*  (at least 16us*4) */
		delay(NUM_5);
		/* cpu */
		temp = readl(HI_PMC_CTL_REG + HPM_CPU_REG0);
		cpu_value[NUM_1] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		cpu_value[NUM_0] += temp & 0x3ff;
		temp = readl(HI_PMC_CTL_REG + HPM_CPU_REG1);
		cpu_value[NUM_3] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		cpu_value[NUM_2] += temp & 0x3ff;

		/* mda */
		temp = readl(HI_PMC_CTL_REG + HPM_MDA_REG0);
		mda_value[NUM_1] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		mda_value[NUM_0] += temp & 0x3ff;
		temp = readl(HI_PMC_CTL_REG + HPM_MDA_REG1);
		mda_value[NUM_3] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		mda_value[NUM_2] += temp & 0x3ff;

		/* gpu */
		temp = readl(HI_PMC_CTL_REG + HPM_GPU_REG0);
		gpu_value[NUM_1] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		gpu_value[NUM_0] += temp & 0x3ff;
		temp = readl(HI_PMC_CTL_REG + HPM_GPU_REG1);
		gpu_value[NUM_3] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		gpu_value[NUM_2] += temp & 0x3ff;

		/* core */
		temp = readl(HI_PMC_CTL_REG + HPM_CORE_REG0);
		core_value[NUM_1] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		core_value[NUM_0] += temp & 0x3ff;
		temp = readl(HI_PMC_CTL_REG + HPM_CORE_REG1);
		core_value[NUM_3] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		core_value[NUM_2] += temp & 0x3ff;
	}

	*hpm_core = hpm_value_avg(core_value, NUM_4);
	*hpm_mda = hpm_value_avg(mda_value, NUM_4);
	*hpm_cpu = hpm_value_avg(cpu_value, NUM_4);
	*hpm_gpu = hpm_value_avg(gpu_value, NUM_4);
}

static void start_hpm(unsigned int *hpm_core, unsigned int *hpm_cpu,
			unsigned int *hpm_gpu, unsigned int *hpm_mda)
{
	/* open hmp clock */
	writel(0x7ff0000, HMP_CLK_REG);
	/* cpu  */
	writel(0x60020001, HI_PMC_CTL_REG + 0x1200);
	/* mda  */
	writel(0x60020001, HI_PMC_CTL_REG + 0x1210);
	/* gpu  */
	writel(0x60020001, HI_PMC_CTL_REG + 0x1220);
	/* core  */
	writel(0x60020001, HI_PMC_CTL_REG + 0x1230);

	get_hpm_value(hpm_core, hpm_cpu, hpm_gpu, hpm_mda);

	/* close hpm clock */
	writel(0x0, HMP_CLK_REG);
}

static void adjust_hpm(unsigned int *hpm_core, unsigned int *hpm_cpu,
			unsigned int *hpm_gpu, unsigned int *hpm_mda,
			int temperature)
{
	unsigned int otp_hpm_core = readl(OTP_CPU_IF_REG + OTP_HPM_CORE_OFFSET);
	unsigned int otp_hpm_cpu  = readl(OTP_CPU_IF_REG + OTP_HPM_CPU_OFFSET);
	unsigned int otp_hpm_gpu  = readl(OTP_CPU_IF_REG + OTP_HPM_GPU_OFFSET);
	unsigned int otp_hpm_mda  = readl(OTP_CPU_IF_REG + OTP_HPM_MDA_OFFSET);

	if (temperature <= 0) { /* 0: the temperature min */
		*hpm_cpu  -= NUM_6;
		*hpm_mda  -= NUM_3;
		*hpm_gpu  -= NUM_6;
		*hpm_core -= NUM_4;
	} else if (temperature > 70) { /* 70: the temperature max */
		*hpm_cpu  += NUM_5;
		*hpm_mda  += NUM_3;
		*hpm_gpu  += NUM_2;
		*hpm_core += NUM_2;
	}

	if (otp_hpm_core)
		if (*hpm_core > (otp_hpm_core + 10)) /* 10: Increment */
			*hpm_core = otp_hpm_core - NUM_5;

	if (otp_hpm_cpu)
		if (*hpm_cpu > (otp_hpm_cpu + 15)) /* 15: Increment */
			*hpm_cpu = otp_hpm_cpu;

	if (otp_hpm_gpu)
		if (*hpm_gpu > (otp_hpm_gpu + 15)) /* 15: Increment */
			*hpm_gpu = otp_hpm_gpu;

	if (otp_hpm_mda)
		if (*hpm_mda > (otp_hpm_mda + 15)) /* 15: Increment */
			*hpm_mda = otp_hpm_mda;
}


static void save_hpm(unsigned int hpm_core, unsigned int hpm_cpu,
				unsigned int hpm_gpu, unsigned int hpm_mda)
{
	writel(hpm_mda, SYSCTRL_BASE_REG + HPM_MDA_STORAGE_REG);
	writel(hpm_gpu, SYSCTRL_BASE_REG + HPM_GPU_STORAGE_REG);
	writel(hpm_cpu, SYSCTRL_BASE_REG + HPM_CPU_STORAGE_REG);
}

static unsigned int calc_volt_regval(unsigned int volt_val,
					unsigned int volt_max,
					unsigned int volt_min)
{
	unsigned int reg_val;
	unsigned int duty;

	if (volt_val >= volt_max)
		volt_val = volt_max - 1;

	if (volt_val <= volt_min)
		volt_val = volt_min + 1 ;

	duty = duty_formula(volt_max, volt_min, volt_val);
	reg_val = volt_regval_formula(duty);

	return reg_val;
}

static void set_hpm_core_volt(unsigned int hpm_core_value, int delta_v)
{
	unsigned int volt_val;
	unsigned int reg_val;

	volt_val = (CORE_CURVE_B - CORE_CURVE_A * hpm_core_value) / NUM_10 + delta_v;
	if (volt_val > CORE_CURVE_VLOT_MAX)
		volt_val = CORE_CURVE_VLOT_MAX;
	else if (volt_val < CORE_CURVE_VLOT_MIN)
		volt_val = CORE_CURVE_VLOT_MIN;

	reg_val = calc_volt_regval(volt_val, CORE_VOLT_MAX, CORE_VOLT_MIN);

	writel(reg_val, HPM_CORE_VOL_REG);
}

static void set_hpm_mda_volt(unsigned int hpm_mda_value, int delta_v)
{
	unsigned int volt_val;
	unsigned int reg_val;

	volt_val = (MEDIA_CURVE_B - MEDIA_CURVE_A * hpm_mda_value) / NUM_10 + delta_v;
	if (volt_val > MEDIA_CURVE_VLOT_MAX)
		volt_val = MEDIA_CURVE_VLOT_MAX;
	else if (volt_val < MEDIA_CURVE_VLOT_MIN)
		volt_val = MEDIA_CURVE_VLOT_MIN;

	reg_val = calc_volt_regval(volt_val, MDA_VOLT_MAX, MDA_VOLT_MIN);

	writel(reg_val, HPM_MDA_VOL_REG);
}
static void set_hpm_gpu_volt(unsigned int hpm_gpu_value, int delta_v)
{
	unsigned int volt_val;
	unsigned int reg_val;

	volt_val = (GPU_CURVE_B - GPU_CURVE_A * hpm_gpu_value) / NUM_10 + delta_v;
	if (volt_val > GPU_CURVE_VLOT_MAX)
		volt_val = GPU_CURVE_VLOT_MAX;
	else if (volt_val < GPU_CURVE_VLOT_MIN)
		volt_val = GPU_CURVE_VLOT_MIN;

	reg_val = calc_volt_regval(volt_val, GPU_VOLT_MAX, GPU_VOLT_MIN);

	writel(reg_val, HPM_GPU_VOL_REG);
}
static void set_hpm_cpu_volt(unsigned int hpm_cpu_value, int delta_v)
{
	unsigned int volt_val;
	unsigned int reg_val;

	volt_val = (CPU_CURVE_B - CPU_CURVE_A * hpm_cpu_value) / NUM_10 + delta_v;
	if (volt_val > CPU_CURVE_VLOT_MAX)
		volt_val = CPU_CURVE_VLOT_MAX;
	else if (volt_val < CPU_CURVE_VLOT_MIN)
		volt_val = CPU_CURVE_VLOT_MIN;

	reg_val = calc_volt_regval(volt_val, CPU_VOLT_MAX, CPU_VOLT_MIN);

	writel(reg_val, HPM_CPU_VOL_REG);
}

static void get_delta_v(int *core_delta_v, int *cpu_delta_v, int *gpu_delta_v,
						int *mda_delta_v)
{
	unsigned int value = readl(OTP_CPU_IF_REG + OTP_IDDQ_SENSORHUB_OFFSET);

	/* core:bit 16-19,
	   bit19 equal to 1 means negative, equal to 0 means positive,
	   bit 16-18 is the  absolute delta_v */
	int flag =  value & 0x00080000 ? -1 : 1;
	*core_delta_v = flag * (int)((value >> BIT_16) & 0x7) * NUM_10; /* 0x7: Mask */

	/* media:bit 20-23 */
	flag =  value & 0x00800000 ? -1 : 1;
	*mda_delta_v = flag * (int)((value >> BIT_20) & 0x7)  * NUM_10; /* 0x7: Mask */

	/* gpu:bit 24-27 */
	flag =  value & 0x08000000 ? -1 : 1;
	*gpu_delta_v = flag * (int)((value >> BIT_24) & 0x7)  * NUM_10; /* 0x7: Mask */

	/* cpu:bit 28-31 */
	flag =  value & 0x80000000 ? -1 : 1;
	*cpu_delta_v = flag * (int)((value >> BIT_28) & 0x7)  * NUM_10; /* 0x7: Mask */
}


static void set_volt(unsigned int hpm_core, unsigned int hpm_cpu,
				unsigned int hpm_gpu, unsigned int hpm_mda)
{
	int  core_delta_v;
	int  cpu_delta_v;
	int  gpu_delta_v;
	int  mda_delta_v;
	get_delta_v(&core_delta_v, &cpu_delta_v, &gpu_delta_v, &mda_delta_v);

	set_hpm_core_volt(hpm_core, core_delta_v);
	set_hpm_mda_volt(hpm_mda, mda_delta_v);
	set_hpm_cpu_volt(hpm_cpu, cpu_delta_v);
	set_hpm_gpu_volt(hpm_gpu, gpu_delta_v);

	delay(280); /* delay 280ms */
}

static void power_on_avsp(void)
{
	unsigned int tmp = readl(REG_BASE_MISC + 0xb0);
	tmp |= (0x1 << 17); /* Move Left 17 bit */
	writel(tmp, REG_BASE_MISC + 0xb0);
	tmp &= (~(0x1 << 16)); /* Move Left 16 bit */
	writel(tmp, REG_BASE_MISC + 0xb0);
}


static void power_down_avsp(void)
{
	unsigned int tmp = readl(REG_BASE_MISC + 0xb0);
	tmp |= (0x1 << 16); /* Move Left 16 bit */
	writel(tmp, REG_BASE_MISC + 0xb0);
	tmp &= (~(0x1 << 17)); /* Move Left 17 bit */
	writel(tmp, REG_BASE_MISC + 0xb0);
}


static void disisolate_cpu(void)
{
	unsigned int tmp = readl(CPU_ISO_REG);
	tmp &= (~(0x1 << NUM_3));
	writel(tmp, CPU_ISO_REG);
}

static void isolate_cpu(void)
{
	unsigned int tmp = readl(CPU_ISO_REG);
	tmp |= (0x1 << NUM_3);
	writel(tmp, CPU_ISO_REG);
}

static void get_temperature(int *temperature)
{
	int value;

	value = readl(REG_BASE_MISC + TSENSOR_STATUS0);
	value = value & 0x3ff;

	*temperature = temperature_formula(value);
}

static void start_svb(void)
{
	unsigned int hpm_core;
	unsigned int hpm_cpu;
	unsigned int hpm_gpu;
	unsigned int hpm_mda;
	int          temperature;

	/* avsp power on and  disisolate cpu a73 */
	disisolate_cpu();
	power_on_avsp();

	/* get hpm */
	start_hpm(&hpm_core, &hpm_cpu, &hpm_gpu, &hpm_mda);

	/* avsp power down and isolate cpu a73 */
	power_down_avsp();
	isolate_cpu();

	get_temperature(&temperature);

	adjust_hpm(&hpm_core, &hpm_cpu, &hpm_gpu, &hpm_mda, temperature);

	set_volt(hpm_core, hpm_cpu, hpm_gpu, hpm_mda);

	save_hpm(hpm_core, hpm_cpu, hpm_gpu, hpm_mda);

#define SVB_VER_REG         0x12020150
#define SVB_VER             0x30303030

	/* add SVB VER */
	writel(SVB_VER, SVB_VER_REG);
}
#endif

void start_ddr_training(unsigned int base)
{
#ifdef SVB_ENABLE
	start_svb();
#endif

	/* ddr hw training */
	ddr_hw_training_if();

	ddr_cmd_site_save();
	/* ddr sw training */
	ddr_sw_training_if();
	ddr_cmd_site_restore();

	/* the value should config after trainning, or
	  it will cause chip compatibility problems */
	if ((readl(DDR_REG_BASE_PHY0 + DDR_PHY_DRAMCFG) &
		PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
		writel(0x401, DDR_REG_BASE_DMC0 + 0x28);
		writel(0x401, DDR_REG_BASE_DMC1 + 0x28);
	} else {
		writel(0x401, DDR_REG_BASE_DMC0 + 0x28);
	}
	if ((readl(DDR_REG_BASE_PHY1 + DDR_PHY_DRAMCFG) &
		PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
		writel(0x401, DDR_REG_BASE_DMC2 + 0x28);
		writel(0x401, DDR_REG_BASE_DMC3 + 0x28);
	} else {
		writel(0x401, DDR_REG_BASE_DMC1 + 0x28);
	}
#ifdef DDR_SCRAMB_ENABLE
	/* enable ddr scramb */
	ddr_scramb();
#endif
}
