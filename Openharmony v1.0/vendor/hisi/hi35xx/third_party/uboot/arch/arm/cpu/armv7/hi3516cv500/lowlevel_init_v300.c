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

#include <compiler.h>
#include <asm/arch/platform.h>
#include <config.h>
#include <ddr_interface.h>
#include <hicpu_common.h>

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

	val = (*(volatile unsigned int *)((uintptr_t)(addr)));
	return val;
}

static inline void writel(unsigned val, unsigned addr)
{
	dwb();
	(*(volatile unsigned int *)((uintptr_t)(addr))) = val;
	dwb();
}

#define REG_BASE_RNG_GEN	0x10090000
#define TRNG_DSTA_FIFO_DATA_OFST	0x204
#define TRNG_DATA_ST_OFST	0x208
#define BIT_TRNG_FIFO_DATA_CNT	0x8
#define TRNG_FIFO_DATA_CNT_MASK	0xff
#define REG_PERI_CRG104		0x1a0
#define TRNG_CLK_ENABLE		(0x1<<3)
#define TRNG_CLK_DISABLE	~(0x1<<3)
#define TRNG_CTRL_DEF_VAL	0xa
#define HISEC_COM_TRNG_CTRL_OFST 0x200

#define REG_BASE_MISC	0x12030000
#define DDR_CA0_OFST	0x28
#define DDR_CA1_OFST	0x2C
#define DDR_CA2_OFST	0x30

#define REG_BASE_DDRC	0x12060000
#define DDRC_CTRL_SREF_OFST	(0x8000 + 0x0)
#define DDRC_CFG_DDRMODE_OFST	(0x8000 + 0x50)
#define DDRC_CURR_FUNC_OFST	(0x8000 + 0x294)

#define DDRC_CHANNEL_VALID_MASK		0xf
#define DDRC_SELF_REFURBISH_MASK	0x1

#define DDRC_SELF_REFURBISH_EN		0x1
#define DDRC_SELF_REFURBISH_EXIT	(0x1 << 1)

#undef reg_get
#undef reg_set
#define reg_get(addr) readl(addr)
#define reg_set(addr, val) writel(val, (unsigned int)(addr))

#define hpm_formula(hpm, temp)  ((hpm) + 6 + ((((unsigned int)(temp) - 70) * 205) >> 10))
#define temperature_formula(val)  (((((val) - 136) * 1704) >> 13) - 40)
#define svb_formula(val) ((((1050000 - (val)) * 31) & 0xffff0000) + 0x0c75)

#define  CHIP_3516DV300  0x3516D300
#define  CHIP_3516C500  0x3516C500
#define  CHIP_3559V200  0x35590200
#define  CHIP_3556V200  0x35560200
#define  CHIP_3516A300  0x3516A300

void trng_init(void)
{
	unsigned int reg_val;
	/* open rsa and trng clock */
	reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG104);
	reg_val |= TRNG_CLK_ENABLE;
	reg_set(CRG_REG_BASE + REG_PERI_CRG104, reg_val);

	/* set trng ctrl register */
	reg_set(REG_BASE_RNG_GEN + HISEC_COM_TRNG_CTRL_OFST,
			TRNG_CTRL_DEF_VAL);
}

void trng_deinit(void)
{
	unsigned int reg_val;

	/* close rsa and trng clock */
	reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG104);
	reg_val &= TRNG_CLK_DISABLE;
	reg_set(CRG_REG_BASE + REG_PERI_CRG104, reg_val);
}
/* get random number */
static int get_random_num(void)
{
	unsigned int reg_val;

	do {
		reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DATA_ST_OFST);
	} while (!((reg_val >> BIT_TRNG_FIFO_DATA_CNT) &
					TRNG_FIFO_DATA_CNT_MASK));

	reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DSTA_FIFO_DATA_OFST);

	return reg_val;
}

/* start ddr cramb */
static void ddr_scramb_start(unsigned int random1, unsigned int random2)
{
	reg_set(REG_BASE_MISC + DDR_CA0_OFST, random1);
	reg_set(REG_BASE_MISC + DDR_CA1_OFST, random2);
	reg_set(REG_BASE_MISC + DDR_CA2_OFST, 0);
	reg_set(REG_BASE_MISC + DDR_CA2_OFST, 0x10);
	delay(1000); /* delay 1000ms */
	reg_set(REG_BASE_MISC + DDR_CA0_OFST, 0);
	reg_set(REG_BASE_MISC + DDR_CA1_OFST, 0);
}

/* execute ddr scramb */
static void ddr_scramb(void)
{
	unsigned int random_num1;
	unsigned int random_num2;
	unsigned int reg_val;
	unsigned int ddrc_isvalid;

	/* read ddrc_cfg_ddrmode register,
	 * if value[3:0] is not 0x0 ,the channel is valid.
	 */
	ddrc_isvalid = (reg_get(REG_BASE_DDRC + DDRC_CFG_DDRMODE_OFST) &
					DDRC_CHANNEL_VALID_MASK) ? 1 : 0;
	/* set ddrc to do self-refurbish */
	if (ddrc_isvalid)
		reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST,
						DDRC_SELF_REFURBISH_EN);

	/* wait the status of ddrc to be sef-refurbish */
	do {
		reg_val = ddrc_isvalid ? (reg_get(REG_BASE_DDRC +
			DDRC_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK) : 1;
	} while (!reg_val);

	trng_init();
	/* get random number */
	random_num1 = get_random_num();
	random_num2 = get_random_num();

	/* start ddr scrambling */
	ddr_scramb_start(random_num1, random_num2);

	/* clear random number */
	random_num1 = get_random_num();
	random_num2 = get_random_num();
	random_num1 = get_random_num();
	random_num2 = get_random_num();

	trng_deinit();

	/* set ddrc to exit self-refurbish */
	if (ddrc_isvalid)
		reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST,
					DDRC_SELF_REFURBISH_EXIT);

	/* wait the status of ddrc to be normal */
	do {
		reg_val = ddrc_isvalid ? (reg_get(REG_BASE_DDRC +
			DDRC_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK) : 0;
	} while (reg_val);
}

#define SVB_VER_REG	0x120200ac
#define SVB_VER_16CV500	0x10
#define SVB_VER_16DV300	0x10
#define SVB_VER_16AV300	0x01
#define SVB_VER_59V200	0x10
#define SVB_VER_56V200	0x10

#define RATIO_16CV500	1500
#define RATIO_16DV300	1500
#define RATIO_16AV300	1500
#define RATIO_59V200	1500
#define RATIO_56V200	1634

#define HI_PMC_CTL_REG 0x120300b0
#define OTP_HPM_CORE_REG 0x100a002c
#define HMP_CLK_REG 0x120101c0

#define HI_HPM_CTL_REG 0x120300d0

#define CYCLE_NUM 4

#define  HPM_CORE_REG0 0x120300d8
#define  HPM_CORE_REG1 0x120300dc

#define  HPM_CHECK_REG 0x12020098

#define TSENSOR_CTRL 0xb4
#define TSENSOR_STATUS0 0xbc

#define SYS_CHIP_ID 0x12020ee0

#define VMIN_CORE_16CV500 820000
#define VMAX_CORE_16CV500 980000
#define Y_16CV500 1267203

#define VMIN_CORE_16DV300 830000
#define VMAX_CORE_16DV300 990000
#define Y_16DV300 1274198

#define VMIN_CORE_16AV300 850000
#define VMAX_CORE_16AV300 1010000
#define Y_16AV300 1294198

#define VMIN_CORE_59V200 820000
#define VMAX_CORE_59V200 980000
#define Y_59V200 1264198

#define VMIN_CORE_56V200 810000
#define VMAX_CORE_56V200 1000000
#define Y_56V200 1309061

#define HPM_CORE_MIN 150
#define HPM_CORE_MAX 350

#define TEMPERATURE_MIN  (-40)
#define TEMPERATURE_MAX  125

static unsigned hpm_value_avg(unsigned int *val, int num)
{
	unsigned int i;
	unsigned tmp = 0;

	for (i = 0; i < num; i++)
		tmp += val[i] >> NUM_2;

	return tmp >> NUM_2;
}

static void get_hpm_value(unsigned int *hpm_core)
{
	int i;
	unsigned int temp;
	unsigned int core_value[NUM_4];

	core_value[NUM_0] = 0;
	core_value[NUM_1] = 0;
	core_value[NUM_2] = 0;
	core_value[NUM_3] = 0;

	for (i = 0; i < CYCLE_NUM; i++) {
		delay(100); /* delay 100ms */

		/* core */
		temp = readl(HPM_CORE_REG0);
		core_value[NUM_1] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		core_value[NUM_0] += temp & 0x3ff;
		temp = readl(HPM_CORE_REG1);
		core_value[NUM_3] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		core_value[NUM_2] += temp & 0x3ff;
	}

	*hpm_core = hpm_value_avg(core_value, NUM_4);
}

static void start_hpm(unsigned int *hpm_core)
{
	get_hpm_value(hpm_core);
}

static void hpm_check(unsigned int *hpm_core)
{
	union {
		struct {
			unsigned int reserved_0 : 16; /* [15..0] */
			unsigned int sys_hpm_core : 9; /* [24..16] */
			unsigned int reserved_1 : 1; /* [25] */
			unsigned int hpm_core_err : 1; /* [26] */
			unsigned int reserved_2 : 5; /* [27..31] */
		} bits;

		unsigned int u32;
	} sysboot10;

	sysboot10.u32 = readl(HPM_CHECK_REG);

	sysboot10.bits.sys_hpm_core = 0;
	sysboot10.bits.hpm_core_err = 0;

	if (*hpm_core < HPM_CORE_MIN) {
		*hpm_core = HPM_CORE_MIN;
		sysboot10.bits.hpm_core_err = 1;
	}
	if (*hpm_core > HPM_CORE_MAX) {
		*hpm_core = HPM_CORE_MAX;
		sysboot10.bits.hpm_core_err = 1;
	}

	sysboot10.bits.sys_hpm_core = *hpm_core;

	writel(sysboot10.u32, HPM_CHECK_REG);
}


static void set_hpm_core_volt(unsigned int hpm_core_value)
{
	unsigned long long mv1000;
	unsigned long long svb_value;
	unsigned int val = readl(SYS_CHIP_ID);
	int y_vol = Y_16AV300;
	int vmin_core = VMIN_CORE_16AV300;
	int vmax_core = VMAX_CORE_16AV300;
	int ratio = RATIO_16AV300;

	if (val == CHIP_3516DV300) {
		y_vol = Y_16DV300;
		vmin_core = VMIN_CORE_16DV300;
		vmax_core = VMAX_CORE_16DV300;
		ratio = RATIO_16DV300;
	} else if (val == CHIP_3516C500) {
		y_vol = Y_16CV500;
		vmin_core = VMIN_CORE_16CV500;
		vmax_core = VMAX_CORE_16CV500;
		ratio = RATIO_16CV500;
	} else if (val == CHIP_3559V200) {
		y_vol = Y_59V200;
		vmin_core = VMIN_CORE_59V200;
		vmax_core = VMAX_CORE_59V200;
		ratio = RATIO_59V200;
	} else if (val == CHIP_3556V200) {
		y_vol = Y_56V200;
		vmin_core = VMIN_CORE_56V200;
		vmax_core = VMAX_CORE_56V200;
		ratio = RATIO_56V200;
	} else if (val == CHIP_3516A300) {
		y_vol = Y_16AV300;
		vmin_core = VMIN_CORE_16AV300;
		vmax_core = VMAX_CORE_16AV300;
		ratio = RATIO_16AV300;
	}
	mv1000 = y_vol - ratio * hpm_core_value;

	if (mv1000 < vmin_core)
		mv1000 = vmin_core;
	if (mv1000 > vmax_core)
		mv1000 = vmax_core;

	val = readl(OTP_HPM_CORE_REG);

	mv1000 = (unsigned long long)((int)mv1000 +
				(int)((short int)(val >> 16)) * 1000); /* Move Right 16bit *1000 */

	svb_value = svb_formula(mv1000);

	writel((unsigned int)svb_value, HI_PMC_CTL_REG);
}

static void get_temperature(int *temperature)
{
	unsigned int value;

	value = readl(REG_BASE_MISC + TSENSOR_STATUS0);
	value = value & 0x3ff;

	*temperature = temperature_formula(value);

	if (*temperature < TEMPERATURE_MIN)
		*temperature = TEMPERATURE_MIN;
	else if (*temperature > TEMPERATURE_MAX)
		*temperature = TEMPERATURE_MAX;
}

static void adjust_hpm(unsigned int *hpm_core, int temperature)
{
	/* 280 70: hpm_core and temperature Threshold */
	if ((*hpm_core >= 280) && ((unsigned int)temperature >= 70))
		*hpm_core = hpm_formula(*hpm_core, temperature);
	/* 260 25: hpm_core and temperature Threshold */
	else if ((*hpm_core >= 260) && ((unsigned int)temperature < 25))
		*hpm_core = *hpm_core - NUM_4;
}

void start_svb(void)
{
	unsigned int hpm_core = 0;
	int temperature = 0;
	unsigned int chip_id = readl(SYS_CHIP_ID);

	/* add SVB VER */
	unsigned int tmp_reg = readl(SVB_VER_REG);

	if (chip_id == 0x3516D300)
		tmp_reg = (tmp_reg & 0xff00ffff) | (SVB_VER_16DV300 << 16); /* Move Left 16bit */
	else if (chip_id == 0x3516C500)
		tmp_reg = (tmp_reg & 0xff00ffff) | (SVB_VER_16CV500 << 16); /* Move Left 16bit */
	else if (chip_id == 0x35590200)
		tmp_reg = (tmp_reg & 0xff00ffff) | (SVB_VER_59V200 << 16); /* Move Left 16bit */
	else if (chip_id == 0x35560200)
		tmp_reg = (tmp_reg & 0xff00ffff) | (SVB_VER_56V200 << 16); /* Move Left 16bit */
	else if (chip_id == 0x3516A300)
		tmp_reg = (tmp_reg & 0xff00ffff) | (SVB_VER_16AV300 << 16); /* Move Left 16bit */

	writel(tmp_reg, SVB_VER_REG);
	get_temperature(&temperature);
	start_hpm(&hpm_core);
	adjust_hpm(&hpm_core, temperature);
	hpm_check(&hpm_core);
	set_hpm_core_volt(hpm_core);
	delay(200); /* delay 200ms */
}

/* [CUSTOM] DDR PHY0-PHY1 base register */
#define DDR_REG_BASE_PHY0	0x1206c000

/* [CUSTOM] DDR DMC0-DMC3 base register */
#define DDR_REG_BASE_DMC0	0x12068000
#define DDR_REG_BASE_DMC1	0x12069000

#ifdef DDR_REG_BASE_PHY1
#define DDR_REG_BASE_DMC2	0x1206a000
#define DDR_REG_BASE_DMC3	0x1206b000
#endif

#define DDR_PHY_DRAMCFG     0x2c    /* DRAM config register */
#define PHY_DRAMCFG_TYPE_MASK   0xf /* [3:0] */
#define PHY_DRAMCFG_TYPE_LPDDR4 0x6   /* [2:0] 110 LPDDR4 */

void start_ddr_training(unsigned int base)
{
	start_svb();

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
#ifdef DDR_REG_BASE_PHY1
	if ((readl(DDR_REG_BASE_PHY1 + DDR_PHY_DRAMCFG) &
		PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
		writel(0x401, DDR_REG_BASE_DMC2 + 0x28);
		writel(0x401, DDR_REG_BASE_DMC3 + 0x28);
	} else {
		writel(0x401, DDR_REG_BASE_DMC1 + 0x28);
	}
#endif
	/* enable ddr scramb */
	ddr_scramb();
}
